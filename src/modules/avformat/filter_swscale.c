/*
 * filter_swscale.c -- image scaling filter
 * Copyright (C) 2008-2009 Ushodaya Enterprises Limited
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <framework/mlt_filter.h>
#include <framework/mlt_frame.h>
#include <framework/mlt_factory.h>
#include <framework/mlt_producer.h>


// ffmpeg Header files
#include <avformat.h>
#include <swscale.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if LIBAVUTIL_VERSION_INT < (50<<16)
#define PIX_FMT_RGB32 PIX_FMT_RGBA32
#define PIX_FMT_YUYV422 PIX_FMT_YUV422
#endif

static inline int convert_mlt_to_av_cs( mlt_image_format format )
{
	int value = 0;

	switch( format )
	{
		case mlt_image_rgb24:
			value = PIX_FMT_RGB24;
			break;
		case mlt_image_rgb24a:
		case mlt_image_opengl:
			value = PIX_FMT_RGB32;
			break;
		case mlt_image_yuv422:
			value = PIX_FMT_YUYV422;
			break;
		case mlt_image_yuv420p:
			value = PIX_FMT_YUV420P;
			break;
		case mlt_image_none:
			fprintf( stderr, "Invalid format...\n" );
			break;
	}

	return value;
}

static int filter_scale( mlt_frame this, uint8_t **image, mlt_image_format *format, int iwidth, int iheight, int owidth, int oheight )
{
	// Get the properties
	mlt_properties properties = MLT_FRAME_PROPERTIES( this );

	// Get the requested interpolation method
	char *interps = mlt_properties_get( properties, "rescale.interp" );

	// Convert to the SwScale flag
	int interp = SWS_BILINEAR;
	if ( strcmp( interps, "nearest" ) == 0 || strcmp( interps, "neighbor" ) == 0 )
		interp = SWS_POINT;
	else if ( strcmp( interps, "tiles" ) == 0 || strcmp( interps, "fast_bilinear" ) == 0 )
		interp = SWS_FAST_BILINEAR;
	else if ( strcmp( interps, "bilinear" ) == 0 )
		interp = SWS_BILINEAR;
	else if ( strcmp( interps, "bicubic" ) == 0 )
		interp = SWS_BICUBIC;
	else if ( strcmp( interps, "bicublin" ) == 0 )
		interp = SWS_BICUBLIN;
	else if ( strcmp( interps, "gauss" ) == 0 )
		interp = SWS_GAUSS;
	else if ( strcmp( interps, "sinc" ) == 0 )
		interp = SWS_SINC;
	else if ( strcmp( interps, "hyper" ) == 0 || strcmp( interps, "lanczos" ) == 0 )
		interp = SWS_LANCZOS;
	else if ( strcmp( interps, "spline" ) == 0 )
		interp = SWS_SPLINE;
	interp |= SWS_ACCURATE_RND;

	// Determine the bytes per pixel
	int bpp;
	switch ( *format )
	{
		case mlt_image_yuv422:
			bpp = 2;
			interp |= SWS_FULL_CHR_H_INP;
			break;
		case mlt_image_rgb24:
			bpp = 3;
			interp |= SWS_FULL_CHR_H_INT;
			break;
		case mlt_image_rgb24a:
		case mlt_image_opengl:
			bpp = 4;
			interp |= SWS_FULL_CHR_H_INT;
			break;
		default:
			// XXX: we only know how to rescale packed formats
			return 1;
	}
#ifdef USE_MMX
	interp |= SWS_CPU_CAPS_MMX;
#endif
#ifdef USE_SSE
	interp |= SWS_CPU_CAPS_MMX2;
#endif

	// Convert the pixel formats
	int avformat = convert_mlt_to_av_cs( *format );

	// Fill out the AVPictures
	AVPicture input;
	AVPicture output;
	uint8_t *outbuf = mlt_pool_alloc( owidth * ( oheight + 1 ) * bpp );
	avpicture_fill( &input, *image, avformat, iwidth, iheight );
	avpicture_fill( &output, outbuf, avformat, owidth, oheight );

	// Get the cached swscale context
	mlt_producer producer = mlt_frame_get_original_producer( this );
	mlt_properties prod_props = MLT_PRODUCER_PROPERTIES( mlt_producer_cut_parent( producer ) );
	struct SwsContext *context = mlt_properties_get_data( prod_props, "swscale.context", NULL );

	// Create the context and output image
	owidth = owidth > 5120 ? 5120 : owidth;
	struct SwsContext *new_context = sws_getCachedContext( context, iwidth, iheight, avformat, owidth, oheight, avformat, interp, NULL, NULL, NULL);
	if ( !new_context )
	{
		owidth = owidth > 2048 ? 2048 : owidth;
		new_context = sws_getCachedContext( context, iwidth, iheight, avformat, owidth, oheight, avformat, interp, NULL, NULL, NULL);
	}
	if ( new_context != context )
		mlt_properties_set_data( properties, "swscale.context", new_context, 0, NULL, NULL );
	if ( new_context )
	{
		// Perform the scaling
		sws_scale( new_context, input.data, input.linesize, 0, iheight, output.data, output.linesize);
	
		// Now update the frame
		mlt_properties_set_data( properties, "image", output.data[0], owidth * ( oheight + 1 ) * bpp, ( mlt_destructor )mlt_pool_release, NULL );
		mlt_properties_set_int( properties, "width", owidth );
		mlt_properties_set_int( properties, "height", oheight );
	
		// Return the output
		*image = output.data[0];
	
		// Scale the alpha channel only if exists and not correct size
		int alpha_size = 0;
		mlt_properties_get_data( properties, "alpha", &alpha_size );
		if ( alpha_size > 0 && alpha_size != ( owidth * oheight ) )
		{
			// Create the context and output image
			uint8_t *alpha = mlt_frame_get_alpha_mask( this );
			if ( alpha )
			{
				context = mlt_properties_get_data( prod_props, "swscale.context2", NULL );
				new_context = sws_getCachedContext( context, iwidth, iheight, avformat, owidth, oheight, avformat, interp, NULL, NULL, NULL);
				if ( new_context != context )
					mlt_properties_set_data( prod_props, "swscale.context2", new_context, 0, NULL, NULL );

				avformat = PIX_FMT_GRAY8;
				avpicture_fill( &input, alpha, avformat, iwidth, iheight );
				outbuf = mlt_pool_alloc( owidth * oheight );
				avpicture_fill( &output, outbuf, avformat, owidth, oheight );
	
				// Perform the scaling
				sws_scale( new_context, input.data, input.linesize, 0, iheight, output.data, output.linesize);
	
				// Set it back on the frame
				mlt_properties_set_data( MLT_FRAME_PROPERTIES( this ), "alpha", output.data[0], owidth * oheight, mlt_pool_release, NULL );
			}
		}
	
		return 0;
	}
	else
	{
		return 1;
	}
}

static void filter_close( mlt_filter filter )
{
	struct SwsContext *context = mlt_properties_get_data( MLT_FILTER_PROPERTIES(filter), "swscale.context", NULL );
	sws_freeContext( context );
	context = mlt_properties_get_data( MLT_FILTER_PROPERTIES(filter), "swscale.context2", NULL );
	sws_freeContext( context );
}

/** Constructor for the filter.
*/

mlt_filter filter_swscale_init( mlt_profile profile, void *arg )
{
	// Test to see if swscale accepts the arg as resolution
	if ( arg )
	{
		int width = (int) arg;
		struct SwsContext *context = sws_getContext( width, width, PIX_FMT_RGB32, 64, 64, PIX_FMT_RGB32, SWS_BILINEAR, NULL, NULL, NULL);
		if ( context )
			sws_freeContext( context );
		else
			return NULL;
	}		

	// Create a new scaler
	mlt_filter this = mlt_factory_filter( profile, "rescale", NULL );
	
	// If successful, then initialise it
	if ( this != NULL )
	{
		// Get the properties
		mlt_properties properties = MLT_FILTER_PROPERTIES( this );

		// Set the inerpolation
		mlt_properties_set( properties, "interpolation", "bilinear" );

		// Set the method
		mlt_properties_set_data( properties, "method", filter_scale, 0, NULL, NULL );

		this->close = filter_close;
	}

	return this;
}
