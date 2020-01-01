/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Exposes all srs_limiter APIs
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_common/std_fxp/include/srs_limiter_api.h#4 $
 *  $Author: oscarh $
 *  $Date: 2010/09/21 $
 *	
********************************************************************************/

#ifndef __SRS_LIMITER_API_H__
#define __SRS_LIMITER_API_H__

#include "srs_limiter_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

SRSLimiterObj	SRS_CreateLimiterObj(void *pBuf);

void	SRS_InitLimiterObj8k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj11k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj16k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj22k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj24k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj32k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj44k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj48k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj88k(SRSLimiterObj lmtObj);
void	SRS_InitLimiterObj96k(SRSLimiterObj lmtObj);

void	SRS_LimiterProcessMono(SRSLimiterObj lmtObj, srs_int32 *audioIO, int blockSize);
void	SRS_LimiterProcessStereo(SRSLimiterObj lmtObj, SRSStereoCh *audioIO, int blockSize);

SRSResult	SRS_SetLimiterMinimalGain(SRSLimiterObj lmtObj, srs_int32 minGain); //limit: I32.2
srs_int32	SRS_GetLimiterMinimalGain(SRSLimiterObj lmtObj);

void	SRS_SetLimiterEnable(SRSLimiterObj lmtObj, int enable);
int		SRS_GetLimiterEnable(SRSLimiterObj lmtObj);

void	SRS_SetLimiterControlDefaults(SRSLimiterObj lmtObj);


#ifdef __cplusplus
}
#endif /*__cplusplus*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*__SRS_LIMITER_API_H__*/
