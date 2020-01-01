/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS Limiter types, constants
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_common/std_fxp/include/srs_limiter_def.h#1 $
 *  $Author: oscarh $
 *  $Date: 2010/09/21 $
 *	
********************************************************************************/
#ifndef __SRS_LIMITER_DEF_H__
#define __SRS_LIMITER_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSLimiterObj{int _;} *SRSLimiterObj;

#define SRS_LIMITER_OBJ_SIZE	(sizeof(_SRSLimiterObj_t)+8)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	int			Enable;
	srs_int32	MinimalGain;	//[0.25, 1], I32.2. minimal value of LevelGain
	srs_int16	Decay;		//I16.-15
} _SRSLimiterSettings_t;

typedef struct
{
	srs_int32	LevelGain;	//the gain to be applied, adjusted sample by sample, I32.2
} _SRSLimiterState_t;

typedef struct
{
	_SRSLimiterSettings_t	Settings;
	_SRSLimiterState_t		State;
} _SRSLimiterObj_t;

#endif //__SRS_LIMITER_DEF_H__
