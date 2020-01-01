/**
* @file MediaFsmItf.h
*
* This header file defines the APIs of media state machines
*
*/

#ifndef __MEDIAFSMITF_H__
#define __MEDIAFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaCmdItf.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* MediaStateMachineHandle_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
MediaStateMachineHandle_t MediaFSM_Init(MediaResInfo_e eResInfo, void *pCusData);
void MediaFSM_Uninit(MediaStateMachineHandle_t pHandle);
bool MediaFSM_IsWaitRsp(MediaStateMachineHandle_t pHandle);
void MediaFSM_HandleEvt(MediaStateMachineHandle_t pHandle, void *pEvt, void *pRetParam);
bool MediaFSM_IsActAcceptable(MediaStateMachineHandle_t pHandle, u16 uAction);
bool MediaFSM_IsActExecutable(u16 uAction, MediaResInfo_e eResInfo);
void MediaFSM_SetWaitRsp(MediaStateMachineHandle_t pHandle);
void MediaFSM_ClearWaitRsp(MediaStateMachineHandle_t pHandle);
u16 MediaFSM_ReportState(MediaStateMachineHandle_t pHandle);
#endif //__MEDIAFSMITF_H__

