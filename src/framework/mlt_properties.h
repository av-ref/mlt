/**
 * \file mlt_properties.h
 * \brief Properties class declaration
 * \see mlt_properties_s
 *
 * Copyright (C) 2003-2016 Meltytech, LLC
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MLT_PROPERTIES_H
#define MLT_PROPERTIES_H
#include "mlt_defines.h"
#include "mlt_types.h"
#include "mlt_events.h"
#include <stdio.h>

/** \brief Properties class
 *
 * Properties is a combination list/dictionary of name/::mlt_property pairs.
 * It is also a base class for many of the other MLT classes.
 */

struct mlt_properties_s
{
	void *child; /**< \private the object of a subclass */
	void *local; /**< \private instance object */

	/** the destructor virtual function */
	mlt_destructor close;
	void *close_object;  /**< the object supplied to the close virtual function */
};

extern MLT_DECLSPEC int mlt_properties_init( mlt_properties, void *child );
extern MLT_DECLSPEC mlt_properties mlt_properties_new( );
extern MLT_DECLSPEC int mlt_properties_set_lcnumeric( mlt_properties, const char *locale );
extern MLT_DECLSPEC const char* mlt_properties_get_lcnumeric( mlt_properties self );
extern MLT_DECLSPEC mlt_properties mlt_properties_load( const char *file );
extern MLT_DECLSPEC int mlt_properties_preset( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_inc_ref( mlt_properties self );
extern MLT_DECLSPEC int mlt_properties_dec_ref( mlt_properties self );
extern MLT_DECLSPEC int mlt_properties_ref_count( mlt_properties self );
extern MLT_DECLSPEC void mlt_properties_mirror( mlt_properties self, mlt_properties that );
extern MLT_DECLSPEC int mlt_properties_inherit( mlt_properties self, mlt_properties that );
extern MLT_DECLSPEC int mlt_properties_pass( mlt_properties self, mlt_properties that, const char *prefix );
extern MLT_DECLSPEC void mlt_properties_pass_property( mlt_properties self, mlt_properties that, const char *name );
extern MLT_DECLSPEC int mlt_properties_pass_list( mlt_properties self, mlt_properties that, const char *list );
extern MLT_DECLSPEC int mlt_properties_set( mlt_properties self, const char *name, const char *value );
extern MLT_DECLSPEC int mlt_properties_set_or_default( mlt_properties self, const char *name, const char *value, const char *def );
extern MLT_DECLSPEC int mlt_properties_parse( mlt_properties self, const char *namevalue );
extern MLT_DECLSPEC char *mlt_properties_get( mlt_properties self, const char *name );
extern MLT_DECLSPEC char *mlt_properties_get_name( mlt_properties self, int index );
extern MLT_DECLSPEC char *mlt_properties_get_value( mlt_properties self, int index );
extern MLT_DECLSPEC void *mlt_properties_get_data_at( mlt_properties self, int index, int *size );
extern MLT_DECLSPEC int mlt_properties_get_int( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_set_int( mlt_properties self, const char *name, int value );
extern MLT_DECLSPEC int64_t mlt_properties_get_int64( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_set_int64( mlt_properties self, const char *name, int64_t value );
extern MLT_DECLSPEC double mlt_properties_get_double( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_set_double( mlt_properties self, const char *name, double value );
extern MLT_DECLSPEC mlt_position mlt_properties_get_position( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_set_position( mlt_properties self, const char *name, mlt_position value );
extern MLT_DECLSPEC int mlt_properties_set_data( mlt_properties self, const char *name, void *value, int length, mlt_destructor, mlt_serialiser );
extern MLT_DECLSPEC void *mlt_properties_get_data( mlt_properties self, const char *name, int *length );
extern MLT_DECLSPEC int mlt_properties_rename( mlt_properties self, const char *source, const char *dest );
extern MLT_DECLSPEC int mlt_properties_count( mlt_properties self );
extern MLT_DECLSPEC void mlt_properties_dump( mlt_properties self, FILE *output );
extern MLT_DECLSPEC void mlt_properties_debug( mlt_properties self, const char *title, FILE *output );
extern MLT_DECLSPEC int mlt_properties_save( mlt_properties, const char * );
extern MLT_DECLSPEC int mlt_properties_dir_list( mlt_properties, const char *, const char *, int );
extern MLT_DECLSPEC void mlt_properties_close( mlt_properties self );
extern MLT_DECLSPEC int mlt_properties_is_sequence( mlt_properties self );
extern MLT_DECLSPEC mlt_properties mlt_properties_parse_yaml( const char *file );
extern MLT_DECLSPEC char *mlt_properties_serialise_yaml( mlt_properties self );
extern MLT_DECLSPEC void mlt_properties_lock( mlt_properties self );
extern MLT_DECLSPEC void mlt_properties_unlock( mlt_properties self );

extern MLT_DECLSPEC char *mlt_properties_get_time( mlt_properties, const char* name, mlt_time_format );
extern MLT_DECLSPEC char *mlt_properties_frames_to_time( mlt_properties, mlt_position, mlt_time_format );
extern MLT_DECLSPEC mlt_position mlt_properties_time_to_frames( mlt_properties, const char* time );

extern MLT_DECLSPEC mlt_color mlt_properties_get_color( mlt_properties, const char* name );
extern MLT_DECLSPEC int mlt_properties_set_color( mlt_properties, const char* name, mlt_color value );

extern MLT_DECLSPEC char* mlt_properties_anim_get( mlt_properties self, const char *name, int position, int length );
extern MLT_DECLSPEC int mlt_properties_anim_set( mlt_properties self, const char *name, const char *value, int position, int length );
extern MLT_DECLSPEC int mlt_properties_anim_get_int( mlt_properties self, const char *name, int position, int length );
extern MLT_DECLSPEC int mlt_properties_anim_set_int( mlt_properties self, const char *name, int value, int position, int length, mlt_keyframe_type keyframe_type );
extern MLT_DECLSPEC double mlt_properties_anim_get_double( mlt_properties self, const char *name, int position, int length );
extern MLT_DECLSPEC int mlt_properties_anim_set_double( mlt_properties self, const char *name, double value, int position, int length, mlt_keyframe_type keyframe_type );
extern MLT_DECLSPEC mlt_animation mlt_properties_get_animation( mlt_properties self, const char *name );

extern MLT_DECLSPEC int mlt_properties_set_rect( mlt_properties self, const char *name, mlt_rect value );
extern MLT_DECLSPEC mlt_rect mlt_properties_get_rect( mlt_properties self, const char *name );
extern MLT_DECLSPEC int mlt_properties_anim_set_rect( mlt_properties self, const char *name, mlt_rect value, int position, int length, mlt_keyframe_type keyframe_type );
extern MLT_DECLSPEC mlt_rect mlt_properties_anim_get_rect( mlt_properties self, const char *name, int position, int length );

extern MLT_DECLSPEC int mlt_properties_from_utf8( mlt_properties properties, const char *name_from, const char *name_to );
extern MLT_DECLSPEC int mlt_properties_to_utf8( mlt_properties properties, const char *name_from, const char *name_to );
#endif
