
#pragma once

#include "../framework/mlt_defines.h"

#ifdef __cplusplus
extern "C"
{
#endif
MLT_DECLSPEC int nanosleep( const struct timespec * rqtp, struct timespec * rmtp );
#ifdef __cplusplus
}
#endif
