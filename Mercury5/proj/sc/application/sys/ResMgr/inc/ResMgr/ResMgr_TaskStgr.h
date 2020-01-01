/**
* @file ResMgr_TaskStgr.h
*
* This header file defines the interface of resource manager task
* strategier
*/

#ifndef __RESMGR_TASKSTGR_H__
#define __RESMGR_TASKSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdMgrStgrItf.h"
#include "ResMgr_AsyncStgr.h"
#include "ListenerItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_TaskStgr_t_
{
    ResMgr_AsyncStgr_t tAsyncStgr;
} ResMgr_TaskStgr_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
void ResMgrTaskStgr_Init(CmdMgrStgrHdl_t pHandle, CmdMgrStgrExtItf_t const *pExtInterface, ResMgrCommItf_t *pCommItf, ResMgrAsyncItf_t const *pAsyncItf);
void ResMgrTaskStgr_Uninit(CmdMgrStgrHdl_t pHandle);
void ResMgrTaskStgr_Send(CmdMgrStgrHdl_t pHandle, u32 uDestMbx, u32 uTypeMsg, void *pMsgBody);

#endif //__RESMGR_TASKSTGR_H__

