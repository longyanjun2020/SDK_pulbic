/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  FOCUS types, constants
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_focus_def.h#2 $
 *  $Author: oscarh $
 *  $Date: 2011/02/14 $
********************************************************************************/
#ifndef __SRS_FOCUS_DEF_H__
#define __SRS_FOCUS_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSFocusObj{int _;} *SRSFocusObj;

#define SRS_FOCUS_OBJ_SIZE		(sizeof(_SRSFocusObj_t)+8)
#define SRS_FOCUS_WORKSPACE_SIZE(blockSize)	(sizeof(srs_int32)*(blockSize)+8)

#define SRS_FOCUS_IWL	1


////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	int							Enable;				//Master enable, 0: disabled, non-zero: enabled
	srs_int16					InputGain;			//I16.SRS_FOCUS_IWL
	srs_int16					OutputGain;			//I16.SRS_FOCUS_IWL
	srs_int16					BypassGain;			//I16.SRS_FOCUS_IWL	
	srs_int16					Factor;				//I16.SRS_FOCUS_IWL
	const srs_int16				*FocusFilter;
} _SRSFocusSettings_t;

typedef struct
{
	srs_int32					FilterState;
} _SRSFocusState_t;

typedef struct
{
	_SRSFocusSettings_t			Settings;
	_SRSFocusState_t			State;
} _SRSFocusObj_t;

#endif //__SRS_FOCUS_DEF_H__
