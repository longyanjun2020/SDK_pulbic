//==============================================================================
//
//  File        : pCam_audio.h
//  Description : INCLUDE File for Firmware USB PCam Audio System
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _PCAM_AUDIO_H_
#define _PCAM_AUDIO_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "includes_fw.h"

#if (USB_EN)&&(SUPPORT_UVC_FUNC)&&(SUPPORT_UAC)

#include "mmpf_audio_ctl.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

extern MMP_BOOL gbUacTxStarted;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern MMP_ERR MMPF_UAC_Start(void);
extern MMP_ERR MMPF_UAC_Stop(void);
extern MMP_ERR MMPF_UAC_SetSampleRate(void);
extern MMP_ERR MMPF_UAC_SetVolume(void);
extern MMP_ERR MMPF_UAC_SetMute(void);
extern void MMPF_UAC_RecIntHandler(MMP_SHORT *in, MMP_ULONG samples);

#endif // (USB_EN)&&(SUPPORT_UVC_FUNC)&&(SUPPORT_UAC)
#endif // _PCAM_AUDIO_H_

