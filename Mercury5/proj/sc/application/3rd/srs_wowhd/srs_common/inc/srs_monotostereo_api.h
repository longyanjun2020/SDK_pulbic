/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  The header file exposes all mono to stereo lib APIs
 *
 *	Author: Zesen Zhuang
 *
 *$Id: //srstech/srs_common/std_fxp/include/srs_monotostereo_api.h#4 $
 *$Author: oscarh $
 *$Date: 2010/09/21 $
********************************************************************************/


#ifndef __SRS_MONOTOSTEREO_API_H__
#define __SRS_MONOTOSTEREO_API_H__

#include "srs_typedefs.h"
#include "srs_fxp.h"
#include "srs_monotostereo_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

SRSMonoToStereoObj	SRS_CreateMonoToStereoObj(void *pBuf);
void		SRS_InitMonoToStereoObj(SRSMonoToStereoObj m2stereoObj);	
void		SRS_MonoToStereo(SRSMonoToStereoObj m2stereoObj, srs_int32 *input, SRSStereoCh *output, int blockSize);

void		SRS_SetMonoToStereoInputGain(SRSMonoToStereoObj m2stereoObj, srs_int16 gain); //gain iwl: SRS_MONOTOSTEREO_GAIN_IWL
srs_int16	SRS_GetMonoToStereoInputGain(SRSMonoToStereoObj m2stereoObj);


#ifdef __cplusplus
}
#endif /*__cplusplus*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /*__SRS_MONOTOSTEREO_API_H__*/
