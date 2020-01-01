/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS Definition public APIs header file
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_definition_api.h#4 $
 *  $Author: oscarh $
 *  $Date: 2010/09/21 $
********************************************************************************/

#ifndef __SRS_DEFINITION_API_H__
#define __SRS_DEFINITION_API_H__

#include "srs_typedefs.h"
#include "srs_fxp.h"
#include "srs_definition_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

SRSDefinitionObj	SRS_CreateDefinitionObj(void *pBuf);
void		SRS_InitDefinitionObj8k(SRSDefinitionObj focusObj);	
void		SRS_InitDefinitionObj11k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj16k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj22k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj24k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj32k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj44k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj48k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj88k(SRSDefinitionObj focusObj);
void		SRS_InitDefinitionObj96k(SRSDefinitionObj focusObj);

void		SRS_SetDefinitionControlDefaults(SRSDefinitionObj defObj);

void		SRS_DefinitionProcess(SRSDefinitionObj defObj, srs_int32 *audioIO, int blockSize);
void		SRS_Definition(SRSDefinitionObj defObj, srs_int32 *audioIO, int blockSize, void *ws);


void		SRS_SetDefinitionEnable(SRSDefinitionObj defObj, int enable);
int			SRS_GetDefinitionEnable(SRSDefinitionObj defObj);
SRSResult	SRS_SetDefinitionInputGain(SRSDefinitionObj defObj, srs_int16 gain);
srs_int16	SRS_GetDefinitionInputGain(SRSDefinitionObj defObj);
SRSResult	SRS_SetDefinitionOutputGain(SRSDefinitionObj defObj, srs_int16 gain);
srs_int16	SRS_GetDefinitionOutputGain(SRSDefinitionObj defObj);
SRSResult	SRS_SetDefinitionBypassGain(SRSDefinitionObj defObj, srs_int16 gain);
srs_int16	SRS_GetDefinitionBypassGain(SRSDefinitionObj defObj);
SRSResult	SRS_SetDefinitionFactor(SRSDefinitionObj defObj, srs_int16 factor);
srs_int16	SRS_GetDefinitionFactor(SRSDefinitionObj defObj);

#ifdef __cplusplus
}
#endif /*__cplusplus*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#endif //__SRS_DEFINITION_API_H__
