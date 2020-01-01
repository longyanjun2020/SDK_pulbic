/**
* @file AudioDevCtrlFsmItf.h
*
* This header file defines the interfaces of Audio Device Ctrl States
*
*/

#ifndef __AUDIODEVCTRLFSMITF_H__
#define __AUDIODEVCTRLFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum AudioDevStates_e_
{
    AUDIO_DEV_STATE__IDLE,
    AUDIO_DEV_STATE__NUM
} AudioDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t AudioDevFSM_Init(void *pCusData);
void AudioDevFSM_Uninit(StateMachineHandle_t pHandle);
bool AudioDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__AUDIODEVCTRLFSMITF_H__

