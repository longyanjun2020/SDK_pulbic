/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  ParametricEQ public APIs header file
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_parametriceq_api.h#6 $
 *  $Author: oscarh $
 *  $Date: 2011/02/14 $
********************************************************************************/

#ifndef __SRS_PARAMETRICEQ_API_H__
#define __SRS_PARAMETRICEQ_API_H__

#include "srs_typedefs.h"
#include "srs_fxp.h"
#include "srs_parametriceq_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

/*APIs*/
SRSParametricEqObj SRS_CreateParametricEqObj(void* pBuf);
SRSResult	SRS_InitParametricEqObj(SRSParametricEqObj peqObj, int nBands, const void *filterCoefs, SRSFilterWl filterWl);
void		SRS_SetParametricEqControlDefaults(SRSParametricEqObj peqObj);
SRSResult	SRS_ParametricEq16Process(SRSParametricEqObj peqObj, srs_int32 *audioIO, int blockSize);
SRSResult	SRS_ParametricEq32Process(SRSParametricEqObj peqObj, srs_int32 *audioIO, int blockSize);

SRSResult	SRS_ParametricEq16(SRSParametricEqObj peqObj, srs_int32 *audioIO, int blockSize);
SRSResult	SRS_ParametricEq32(SRSParametricEqObj peqObj, srs_int32 *audioIO, int blockSize);

int			SRS_GetParametricEqNumOfBands(SRSParametricEqObj peqObj);
int			SRS_GetParametricEqBandEnable(SRSParametricEqObj peqObj, int bandIndex);
SRSResult	SRS_SetParametricEqBandEnable(SRSParametricEqObj peqObj, int bandIndex, int enable);

int			SRS_GetParametricEqMasterEnable(SRSParametricEqObj peqObj);
void		SRS_SetParametricEqMasterEnable(SRSParametricEqObj peqObj, int enable);

srs_int16	SRS_GetParametricEqInputGain(SRSParametricEqObj peqObj);
void		SRS_SetParametricEqInputGain(SRSParametricEqObj peqObj, srs_int16 gain);

srs_int16	SRS_GetParametricEqOutputGain(SRSParametricEqObj peqObj);
void		SRS_SetParametricEqOutputGain(SRSParametricEqObj peqObj, srs_int16 gain);

srs_int16	SRS_GetParametricEqBypassGain(SRSParametricEqObj peqObj);
void		SRS_SetParametricEqBypassGain(SRSParametricEqObj peqObj, srs_int16 gain);



#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__SRS_PARAMETRICEQ_API_H__*/
