/**
* @file TaskStgr_DevMediatorItf.h
*
* This header file defines the interfaces of asynchronous strategier 
* device mediator 
*/

#ifndef __TASKSTGR_DEVMEDIATORITF_H__
#define __TASKSTGR_DEVMEDIATORITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_DevMediator.h"
#include "ResMgr_CmdMgrStgrItf.h"
#include "ResMgr_Evt.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void TaskStgr_OnStatusChanged(CmdMgrStgrHdl_t pHandle, ResMgr_EvtHdl_t pEvtHdl);
void TaskStgr_RegMediator(CmdMgrStgrHdl_t pHandle, ResMgr_EvtHdl_t pEvtHdl);
void TaskStgr_DeregMediator(CmdMgrStgrHdl_t pHandle, ResMgr_EvtHdl_t pEvtHdl);

#endif //__TASKSTGR_DEVMEDIATORITF_H__

