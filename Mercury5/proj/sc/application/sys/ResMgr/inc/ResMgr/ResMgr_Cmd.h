/**
* @file ResMgr_Cmd.h
*
* This header file defines the data structure of resource manager command.
*
*/

#ifndef __RESMGR_CMD_H__
#define __RESMGR_CMD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdItf.h"

/*=============================================================*/
// Macro Declarations
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_Cmd_t_
{
    ResMgr_ResCategory_e eResCategory;
    ResMgr_AppId_e eAppId;
    ResMgr_IsExecutable IsExecutable;
    ResMgr_IsMergable IsMergable;
    ResMgr_PreExecCmd PreExecCmd;
    ResMgr_CusFunc CusFunc;
    ResMgr_ExecCmd ExecCmd;
    ResMgr_ParseExecRes ParseResult;
    ResMgr_PostExecCmd PostExecCmd;
    ResMgr_TerminateCmd TerminateCmd;
    ResMgr_HandleRsp HandleRsp;
    ResMgr_MergeCmd MergeCmd;
    ResMgr_DenyCmd DenyCmd;
    ResMgr_HandleExecFailed HandleExecFailed;
    ResMgr_IsCmdRemovable IsCmdRemovable;
    ResMgr_InformApp InformApp;
    ResMgr_UpdateCusData UpdateCusData;
    ResMgr_FreeCusData FreeCusData;
    ResMgr_GetCusData GetCusData;
    void *pCusData;
} ResMgr_Cmd_t;

typedef struct ResMgr_CmdCreator_t_
{
    ResMgr_FreeCmd FreeCmd;
} ResMgr_CmdCreator_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_CMD_H__

