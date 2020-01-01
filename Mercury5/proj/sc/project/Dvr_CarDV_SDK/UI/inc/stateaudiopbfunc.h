//==============================================================================
//
//  File        : StateAudioPBFunc.h
//  Description : INCLUDE File for the StateAudioPBFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEAUDIOPBFUNC_H_
#define _STATEAUDIOPBFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void AudPBTimer_ResetCounter(void);
void AudPBTimer_ISR(void *tmr, void *arg);
AHC_BOOL AudPBTimer_Start(UINT32 ulTime);
AHC_BOOL AudPBTimer_Stop(void);
void AudPBFunc_ResetPlaySpeed(void);
void AudPBFunc_SDMMC_Out(void);
AHC_BOOL AudioPBMode_Start(void);
void AudioPBMode_Update(void);
void StateAudioPlaybackMode(UINT32 ulEvent);
//AHC_BOOL  StateAudioPlaybackModeInitFromMenu(void* pData);


#endif //_STATEAUDIOPBFUNC_H_

