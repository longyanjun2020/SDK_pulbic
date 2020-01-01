/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS WOWHD types, constants
 *
 *	Author: Zesen Zhuang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_wowhd/std_fxp/include/srs_wowhd_def.h#3 $
 *  $Author: zesenz $
 *  $Date: 2010/11/22 $
 *
********************************************************************************/

#ifndef __SRS_WOWHD_DEF_H__
#define __SRS_WOWHD_DEF_H__

#include "srs_typedefs.h"
#include "srs_srs3d_def.h"
#include "srs_definition_def.h"
#include "srs_focus_def.h"
#include "srs_limiter_def.h"
#include "srs_sa_trubass_def.h"


#define SRS_WOWHD_GAIN_IWL	1

/*Data type definition here:*/
typedef  struct _SRSWowhdObj{int _;} *SRSWowhdObj;

#define SRS_WOWHD_OBJ_SIZE					(sizeof(_SRSWowhdObj_t)+SRS_SRS3D_OBJ_SIZE+SRS_SA_TRUBASS_OBJ_SIZE+2*SRS_DEFINITION_OBJ_SIZE+2*SRS_FOCUS_OBJ_SIZE+SRS_LIMITER_OBJ_SIZE)
#define SRS_WOWHD_WORKSPACE_SIZE(blksize)	(sizeof(srs_int32)*6*(blksize)+40)

///////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:


typedef struct
{
	int							Enable;				//enable, 0: disabled, non-zero: enabled
	srs_int16					InputGain;			//input gain
	srs_int16					OutputGain;			//output gain
	srs_int16					BypassGain;			//bypass gain

} _SRSWowhdSettings_t;



typedef struct
{
	_SRSWowhdSettings_t		Settings;
	SRSSrs3dObj				Srs3dObj;
	SRSDefinitionObj		LDefObj;
	SRSDefinitionObj		RDefObj;
	SRSFocusObj				LFocusObj;
	SRSFocusObj				RFocusObj;
	SRSLimiterObj			LmtObj;
	SRSSATruBassObj			TrubObj;

} _SRSWowhdObj_t;


#endif //__SRS_WOWHD_DEF_H__
