/**
* @file AudioFsmItf.h
*
* This header file defines the interfaces of audio states
*
*/

#ifndef __AUDIOFSMITF_H__
#define __AUDIOFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaFsm.h"
#include "MediaCmd.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum AudioStates_e_
{
    AUDIO_STATE__IDLE,
    AUDIO_STATE__INIT,
    AUDIO_STATE__PLAY,
    AUDIO_STATE__PAUSED,
    AUDIO_STATE__RESTART,
    AUDIO_STATE__SPEECH,
    AUDIO_STATE__SEEK,
    AUDIO_STATE__NUM
} AudioStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t AudioFSM_Init(void *pCusData);
void AudioFSM_Uninit(StateMachineHandle_t pHandle);
bool Audio_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);
bool Audio_NeedLoopPlay(MediaCmd_t *pPlayCmd);


#endif //__AUDIOFSMITF_H__

