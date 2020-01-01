/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SOS cascaded IIR filter APIs
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id$
 *  $Author$
 *  $Date$
********************************************************************************/
#ifndef __SRS_IIR_API_H__
#define __SRS_IIR_API_H__

#include "srs_iir_def.h"

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

/*APIs*/
SRSIirObj		SRS_CreateIirObj(void* pBuf, int order, const void *filterCoefs, SRSFilterWl filterWl);
SRSResult		SRS_InitIirObj(SRSIirObj iirObj);

void			SRS_SetIirControlDefaults(SRSIirObj iirObj);
void			SRS_SetIirEnable(SRSIirObj iirObj, int enable);

int				SRS_GetIirEnable(SRSIirObj iirObj);

void			SRS_IirProcess(SRSIirObj iirObj, srs_int32 *audioIO, int blockSize);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //__SRS_IIR_API_H__
