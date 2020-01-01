/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS Definition types, constants...
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_definition_def.h#2 $
 *  $Author: oscarh $
 *  $Date: 2011/02/14 $
********************************************************************************/
#ifndef __SRS_DEFINITION_DEF_H__
#define __SRS_DEFINITION_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSDefinitionObj{int _;} *SRSDefinitionObj;

#define SRS_DEFINITION_OBJ_SIZE		(sizeof(_SRSDefinitionObj_t)+8)
#define SRS_DEFINITION_WORKSPACE_SIZE(blockSize)	(sizeof(srs_int32)*(blockSize)+8)

#define SRS_DEFINITION_IWL	1

///////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal use:
typedef struct
{
	int							Enable;				//Master enable, 0: disabled, non-zero: enabled
	srs_int16					InputGain;			//I16.SRS_DEFINITION_IWL
	srs_int16					OutputGain;			//I16.SRS_DEFINITION_IWL
	srs_int16					BypassGain;			//I16.SRS_DEFINITION_IWL	
	srs_int16					Factor;				//I16.SRS_DEFINITION_IWL
	const srs_int16				*DefFilter;
} _SRSDefinitionSettings_t;

typedef struct
{
	srs_int32					FilterState[2];
} _SRSDefinitionState_t;

typedef struct
{
	_SRSDefinitionSettings_t		Settings;
	_SRSDefinitionState_t			State;
} _SRSDefinitionObj_t;

#endif //__SRS_DEFINITION_DEF_H__
