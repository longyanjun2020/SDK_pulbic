/**
* @file TaskStgrCmdHandlerItf.h
*
* This header file defines the interfaces of media task command
* tStgr
*/

#ifndef __TASKSTGRCMDHANDLERITF_H__
#define __TASKSTGRCMDHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "MediaTaskStgrItf.h"
#include "MediaCmdItf.h"
#include "ResMgr_Evt.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct TaskStgr_AppMbx_t_
{
    u32 uMbxId;
} TaskStgr_AppMbx_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
__SLDPM_FREE__ void TaskStgr_HandleTaskCmd(CmdMgrStgrHdl_t pHandle, ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ u16 TaskStgr_ExecNextCmd(CmdMgrStgrHdl_t pHandle, ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ void TaskStgr_FetchNextCmd(CmdMgrStgrHdl_t pHandle);
__SLDPM_FREE__ void TaskStgr_RegAppMbx(CmdMgrStgrHdl_t pHandle, ResMgr_EvtHdl_t pEvtHdl);
__SLDPM_FREE__ u32 TaskStgr_GetAppMbxByAppId(ResMgr_AppId_e eAppId);

#endif //__TASKSTGRCMDHANDLERITF_H__

