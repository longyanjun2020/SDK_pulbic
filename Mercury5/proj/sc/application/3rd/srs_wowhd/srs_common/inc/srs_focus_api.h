/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  FOCUS public APIs header file
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_focus_api.h#3 $
 *  $Author: oscarh $
 *  $Date: 2010/09/21 $
********************************************************************************/

#ifndef __SRS_FOCUS_API_H__
#define __SRS_FOCUS_API_H__

#include "srs_typedefs.h"
#include "srs_fxp.h"
#include "srs_focus_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

SRSFocusObj	SRS_CreateFocusObj(void *pBuf);
void		SRS_InitFocusObj8k(SRSFocusObj focusObj);	
void		SRS_InitFocusObj11k(SRSFocusObj focusObj);
void		SRS_InitFocusObj16k(SRSFocusObj focusObj);
void		SRS_InitFocusObj22k(SRSFocusObj focusObj);
void		SRS_InitFocusObj24k(SRSFocusObj focusObj);
void		SRS_InitFocusObj32k(SRSFocusObj focusObj);
void		SRS_InitFocusObj44k(SRSFocusObj focusObj);
void		SRS_InitFocusObj48k(SRSFocusObj focusObj);
void		SRS_InitFocusObj88k(SRSFocusObj focusObj);
void		SRS_InitFocusObj96k(SRSFocusObj focusObj);

void		SRS_SetFocusControlDefaults(SRSFocusObj focusObj);

void		SRS_FocusProcess(SRSFocusObj focusObj, srs_int32 *audioIO, int blockSize);
void		SRS_Focus(SRSFocusObj focusObj, srs_int32 *audioIO, int blockSize, void *ws);

void		SRS_SetFocusEnable(SRSFocusObj focusObj, int enable);
int			SRS_GetFocusEnable(SRSFocusObj focusObj);
SRSResult 	SRS_SetFocusInputGain(SRSFocusObj focusObj, srs_int16 gain);
srs_int16 	SRS_GetFocusInputGain(SRSFocusObj focusObj);
SRSResult 	SRS_SetFocusOutputGain(SRSFocusObj focusObj, srs_int16 gain);
srs_int16 	SRS_GetFocusOutputGain(SRSFocusObj focusObj);
SRSResult 	SRS_SetFocusBypassGain(SRSFocusObj focusObj, srs_int16 gain);
srs_int16 	SRS_GetFocusBypassGain(SRSFocusObj focusObj);
SRSResult 	SRS_SetFocusFactor(SRSFocusObj focusObj, srs_int16 factor);
srs_int16 	SRS_GetFocusFactor(SRSFocusObj focusObj);

#ifdef __cplusplus
}
#endif /*__cplusplus*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif //__SRS_FOCUS_API_H__
