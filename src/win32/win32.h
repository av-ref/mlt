
#pragma once

#include "../framework/mlt_defines.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern MLT_DECLSPEC   int nanosleep( const struct timespec * rqtp, struct timespec * rmtp );
extern MLT_DECLSPEC   FILE* win32_fopen(const char *filename_utf8, const char *mode_utf8);

#ifdef __cplusplus
}
#endif
