/**
* @file VideoFsmItf.h
*
* This header file defines the interfaces of Video States
*
*/

#ifndef __VIDEOFSMITF_H__
#define __VIDEOFSMITF_H__

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
typedef enum VideoStates_e_
{
    VIDEO_STATE__IDLE,
    VIDEO_STATE__INIT,
    VIDEO_STATE__OPEN,
    VIDEO_STATE__PLAY,
    VIDEO_STATE__PAUSED,
    VIDEO_STATE__NUM
} VideoStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t VideoFSM_Init(void *pCusData);
void VideoFSM_Uninit(StateMachineHandle_t pHandle);
bool Video_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VIDEOFSMITF_H__

