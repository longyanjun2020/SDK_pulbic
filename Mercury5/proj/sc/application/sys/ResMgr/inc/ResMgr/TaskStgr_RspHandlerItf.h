/**
* @file MediaTaskStgr.h
*
* This header file defines the interfaces of media task command
* tStgr
*/

#ifndef __TASKSTGRRSPHANDLERITF_H__
#define __TASKSTGRRSPHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "MediaTaskStgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define TASK_STGR_HANDLE_RSP_RET__NONE              0x0000
#define TASK_STGR_HANDLE_RSP_RET__PLAY_AGAIN        0x0001

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void TaskStgr_HandleTaskRsp(CmdMgrStgrHdl_t pHandle, ResMgr_RspHdl_t pRspHdl);

#endif //__TASKSTGRRSPHANDLERITF_H__

