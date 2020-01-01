//==============================================================================
//
//  File        : ahc_adas.h
//  Description : INCLUDE File for the AHC ADAS function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_ADAS_H_
#define _AHC_ADAS_H_

#include "ahc_common.h"

AHC_BOOL AHC_GetMotionDetectionStatus(void);
AHC_BOOL AHC_SetMotionDetectionStatus(AHC_BOOL bEn);
AHC_BOOL AHC_EnableMotionDetection(AHC_BOOL bEn);
void AHC_SetMotionDtcWinCfg(UINT8 ubWindowNum_X, UINT8 ubWindowNum_Y);
AHC_BOOL AHC_GetMotionDtcSensitivity(UINT8 *pubMvTh, UINT8 *pubCntTh);
int AHC_SetMotionDtcSensitivity(UINT8 ubMvTh, UINT8 ubCntTh);
UINT32 AHC_GetVMDRecTimeLimit(void);
UINT32 AHC_GetVMDShotNumber(void);
void AHC_AdjustVMDPreviewRes(int *w, int *h);
UINT16 AHC_VMDGetMotionCnt(void);
UINT8 AHC_VMDGetMotionRatio(void);
AHC_BOOL	AHC_EnableADAS(AHC_BOOL bEn);
AHC_BOOL	AHC_IsADASEnabled( void );

AHC_BOOL AHC_EnableADAS(AHC_BOOL bEn);
AHC_BOOL AHC_IsADASEnabled(void);

AHC_BOOL Menu_SetMotionDtcSensitivity(UINT8 val);

#endif // _AHC_ADAS_H_