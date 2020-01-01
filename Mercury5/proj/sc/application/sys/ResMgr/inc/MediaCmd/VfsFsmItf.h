/**
* @file VfsFsmItf.h
*
* This header file defines the interfaces of VFS States
*
*/

#ifndef __VFSFSMITF_H__
#define __VFSFSMITF_H__

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
typedef enum VfsStates_e_
{
    VFS_STATE__IDLE,
    VFS_STATE__INIT,
    VFS_STATE__NUM
} VfsStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t VfsFSM_Init(void *pCusData);
void VfsFSM_Uninit(StateMachineHandle_t pHandle);
bool Vfs_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VFSFSMITF_H__

