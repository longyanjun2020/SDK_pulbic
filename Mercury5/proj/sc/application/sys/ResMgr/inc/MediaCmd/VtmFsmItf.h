/**
* @file VtmFsmItf.h
*
* This header file defines the interfaces of video telephony states
*
*/

#ifndef __VTMFSMITF_H__
#define __VTMFSMITF_H__

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
typedef enum VtmStates_e_
{
    VTM_STATE__IDLE,
    VTM_STATE__INIT,
    VTM_STATE__OPEN,
    VTM_STATE__PLAY,
    VTM_STATE__RECORD,
    VTM_STATE__NUM
} VtmStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t VtmFSM_Init(void *pCusData);
void VtmFSM_Uninit(StateMachineHandle_t pHandle);
bool Vtm_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VTMFSMITF_H__
