/**
* @file CameraFsmItf.h
*
* This header file defines the interfaces of Camera States
*
*/

#ifndef __CAMERAFSMITF_H__
#define __CAMERAFSMITF_H__

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
typedef enum CameraStates_e_
{
    CAMERA_STATE__IDLE,
    CAMERA_STATE__INIT,
    CAMERA_STATE__OPEN,
    CAMERA_STATE__PREVIEW,
    CAMERA_STATE__CAPTURE,
    CAMERA_STATE__RECORD,
    CAMERA_STATE__NUM
} CameraStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t CameraFSM_Init(void *pCusData);
void CameraFSM_Uninit(StateMachineHandle_t pHandle);
bool Camera_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__CAMERAFSMITF_H__

