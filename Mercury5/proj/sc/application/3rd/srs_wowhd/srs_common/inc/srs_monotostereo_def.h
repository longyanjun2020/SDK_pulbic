/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS MonoToStereo types, constants
 *
 *	Author: Zesen Zhuang
 *
 *$Id: //srstech/srs_common/std_fxp/include/srs_monotostereo_def.h#1 $
 *$Author: oscarh $
 *$Date: 2010/09/21 $
********************************************************************************/
#ifndef __SRS_MONOTOSTEREO_DEF_H__
#define __SRS_MONOTOSTEREO_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSMonoToStereoObj{int _;} * SRSMonoToStereoObj;

#define SRS_MONOTOSTEREO_OBJ_SIZE		(sizeof(_SRSMonoToStereoObj_t)+8)

#define SRS_MONOTOSTEREO_GAIN_IWL		1		//iwl for inputgain

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	srs_int16					InputGain;	//I16.SRS_MONOTOSTEREO_GAIN_IWL
} _SRSMonoToStereoSettings_t;

typedef struct
{
	srs_int32					FilterState[6];
} _SRSMonoToStereoState_t;

typedef struct
{
	_SRSMonoToStereoSettings_t		Settings;
	_SRSMonoToStereoState_t			State;
} _SRSMonoToStereoObj_t;

#endif //__SRS_MONOTOSTEREO_DEF_H__
