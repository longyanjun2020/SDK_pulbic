//==============================================================================
//
//  File        : statemoviepbfunc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEMOVIEPBFUNC_H_
#define _STATEMOVIEPBFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MOVPB_MAX_SPEED			 (8)
#define MOVPB_MIN_SPEED			 (2)

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL 	MoviePBMode_Start(void);

void 		StateMoviePlaybackMode( UINT32 ulEvent );
void 		MovPBFunc_SetOSDShowStatus(AHC_BOOL state);
AHC_BOOL 	MovPBFunc_GetOSDShowStatus(void);
AHC_BOOL 	MovPBTimer_Start(UINT32 ulTime);
AHC_BOOL 	MovPBTimer_Stop(void);
AHC_BOOL    MovPBAdjVolumeTimer_Stop(void);
void        MovPBFunc_SetOSDShowStatus(AHC_BOOL state);
void 		MovPBTimer_ResetCounter(void);
void 		MovPB_SDMMC_Change(void);
//void 		PlaybackMode_SDMMC_In(void);
//void 		PlaybackMode_SDMMC_Out(void);

void 		StateAudioPlaybackMode(UINT32 ulEvent);
AHC_BOOL 	AudioPBMode_Start(void);
void 		AudioPBMode_Update(void);
void 		MoviePBMode_Update(void);
void 		PhotoPBMode_Update(void);
void 		PhotoPB_SDMMC_Change(void);
void		MovPBFunc_ResetPlaySpeed(void);

#endif //_STATEMOVIEPBFUNC_H_
