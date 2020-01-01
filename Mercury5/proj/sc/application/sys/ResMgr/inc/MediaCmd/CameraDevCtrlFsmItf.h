/**
* @file CameraDevCtrlFsmItf.h
*
* This header file defines the interfaces of Camera Device Ctrl States
*
*/

#ifndef __CAMERADEVCTRLFSMITF_H__
#define __CAMERADEVCTRLFSMITF_H__

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
typedef enum CameraDevStates_e_
{
    CAMERA_DEV_STATE__IDLE,
    CAMERA_DEV_STATE__NUM
} CameraDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t CameraDevFSM_Init(void *pCusData);
void CameraDevFSM_Uninit(StateMachineHandle_t pHandle);
bool CameraDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VIDEODEVCTRLFSMITF_H__

