/**
* @file VideoChatFsmItf.h
*
* This header file defines the interfaces of Video Chat States
*
*/
#ifndef __VENDOR_SMALLROM__
#ifndef __VIDEOCHATFSMITF_H__
#define __VIDEOCHATFSMITF_H__

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
typedef enum VideoChatStates_e_
{
    VIDEOCHAT_STATE__IDLE,
    VIDEOCHAT_STATE__INIT,
    VIDEOCHAT_STATE__OPEN,
    VIDEOCHAT_STATE__PREVIEW,
    VIDEOCHAT_STATE__NUM
} VideoChatStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t VideoChatFSM_Init(void *pCusData);
void VideoChatFSM_Uninit(StateMachineHandle_t pHandle);
bool VideoChat_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VIDEOCHATFSMITF_H__
#endif
