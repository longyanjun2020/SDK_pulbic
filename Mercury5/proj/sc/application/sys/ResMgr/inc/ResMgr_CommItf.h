/**
* @file ResMgr_CommItf.h
*
* This header file defines the interfaces of communication interfaces
* of resource manager
*/

#ifndef __RESMGR_COMMITF_H__
#define __RESMGR_COMMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void (*ResMgr_Send)(u32 uTypeMsg, void *pMsgBody, u32 uSrcId, u32 uDestId);
typedef ResMgr_ErrorCode_e (*ResMgr_SendWithThd)(u32 uTypeMsg, void *pMsgBody, u32 uSrcId, u32 uDestId);

typedef struct ResMgrCommItf_t_
{
    ResMgr_Send Send;
    ResMgr_SendWithThd SendWithThd;	//With flow control
    ResMgr_TaskId_e eTaskId;
    u32 uSrcMbxId;
    u32 uDestMbxId;
} ResMgrCommItf_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__RESMGR_COMMITF_H__

