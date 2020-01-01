/**
* @file VideoDevCtrlFsmItf.h
*
* This header file defines the interfaces of Video Device Ctrl States
*
*/

#ifndef __VIDEODEVCTRLFSMITF_H__
#define __VIDEODEVCTRLFSMITF_H__

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
typedef enum VideoDevStates_e_
{
    VIDEO_DEV_STATE__IDLE,
    VIDEO_DEV_STATE__NUM
} VideoDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t VideoDevFSM_Init(void *pCusData);
void VideoDevFSM_Uninit(StateMachineHandle_t pHandle);
bool VideoDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VIDEODEVCTRLFSMITF_H__

