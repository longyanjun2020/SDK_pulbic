/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  The header file defines SRS fixed-point related data types and macros
 *
 *	Author: Oscar Huang
 *
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_fxp.h#2 $
 *  $Author: oscarh $
 *  $Date: 2010/06/02 $
********************************************************************************/

#ifndef __SRS_FXP_H__
#define __SRS_FXP_H__

#include "srs_typedefs.h"

typedef enum
{
	SRS_RND_INF,				// Rounding to infinity, (a.k.a round to nearest)
	SRS_TRN_ZERO				// Truncation to zero (a.k.a magnitude truncation, floating to integer conversion in C uses this mode)
} SRSQuantizationMode;

#define _SIGNED_HALF(val)	((val)>=0? 0.5:-0.5)

#define _MININTVAL(wl)		((srs_int64)~0<<((wl)-1))		//min value of the integer with word length wl
#define _MAXINTVAL(wl)		(~_MININTVAL(wl))				//max value of the integer with word length wl

#define _CLIP(val, wl)		((val)> _MAXINTVAL(wl)? _MAXINTVAL(wl):((val)<_MININTVAL(wl)? _MININTVAL(wl):val))

#define _FLOAT_VAL_OF_FXP_REP(val, wl, iwl)		((val)*((srs_int64)1<<((wl)-(iwl))))

#define SRS_FXP16(val, iwl)		((srs_int16)_CLIP(_FLOAT_VAL_OF_FXP_REP(val, 16, iwl) + _SIGNED_HALF(val), 16))		//convert to 16-bit fxp with SRS_RND_INF mode
#define SRS_FXP32(val, iwl)		((srs_int32)_CLIP(_FLOAT_VAL_OF_FXP_REP(val, 32, iwl) + _SIGNED_HALF(val), 32))		//convert to 32-bit fxp with SRS_RND_INF mode


#endif //__SRS_FXP_H__
