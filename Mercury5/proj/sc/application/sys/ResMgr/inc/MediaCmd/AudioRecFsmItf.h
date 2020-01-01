/**
* @file AudioRecFsmItf.h
*
* This header file defines the interfaces of audio states
*
*/

#ifndef __AUDIORECFSMITF_H__
#define __AUDIORECFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaFsm.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum AudioRecStates_e_
{
    AUDIO_REC_STATE__IDLE,
    AUDIO_REC_STATE__INIT,
    AUDIO_REC_STATE__RECORDER_INIT,
    AUDIO_REC_STATE__RECORD,
	AUDIO_REC_STATE__PLAY,
    AUDIO_REC_STATE__NUM
} AudioRecStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t AudioRecFSM_Init(void *pCusData);
void AudioRecFSM_Uninit(StateMachineHandle_t pHandle);
bool AudioRec_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__AUDIORECFSMITF_H__

