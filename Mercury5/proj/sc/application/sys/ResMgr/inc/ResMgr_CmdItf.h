/**
* @file ResMgr_CmdItf.h
*
* This header file defines the interface of resource manager command.
*
*/

#ifndef __RESMGR_CMDITF_H__
#define __RESMGR_CMDITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CmdMgrStgrItf.h"

/*=============================================================*/
// Macro Declarations
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ResMgr_CmdPreExecRes_e_
{
    RES_MGR_CMD_PRE_EXEC__SUCCESS,
    RES_MGR_CMD_PRE_EXEC__BUSY,
    RES_MGR_CMD_PRE_EXEC__FAILED,
    RES_MGR_CMD_PRE_EXEC__NUM
} ResMgr_CmdPreExecRes_e;

typedef enum ResMgr_ExecCheckRes_e_
{
    RES_MGR_EXEC_CHECK__EXECUTABLE,
    /*
        If current command is busy, it means command manager is busy waiting for response or
        application confirmation. All later commands in queue will not be executed to prevent
        execute commands w/ incorrect order
    */
    RES_MGR_EXEC_CHECK__BUSY,
    /*
        If current command is pending, it means current command is auto resume, current resource
        owner or later commands have higher priority. Command manager will transverse next
        command and execute it.
    */
    RES_MGR_EXEC_CHECK__PENDING,
    /*
        If current command is rejected, it means the command is rejected by state machine
        or has lower priority w/ no resume. Command manager will destroy command.
    */
    RES_MGR_EXEC_CHECK__INEXECUTABLE,
    RES_MGR_EXEC_CHECK__FORCE_DROP,
    RES_MGR_EXEC_CHECK__WAIT_APPSTOP_PENDING,
    RES_MGR_EXEC_CHECK__WAIT_APPSTOP_DROP,
    RES_MGR_EXEC_CHECK__NUM
} ResMgr_ExecCheckRes_e;

typedef enum ResMgr_ExecRes_e_
{
    RES_MGR_CMD_EXEC__SUCCESS,
    RES_MGR_CMD_EXEC__BUSY,
    RES_MGR_CMD_EXEC__SKIP,
    RES_MGR_CMD_EXEC__FAILED,
    RES_MGR_CMD_EXEC__NUM
} ResMgr_ExecRes_e;

typedef enum ResMgr_PostExecRes_e_
{
    RES_MGR_CMD_POST_EXEC__SUCCESS,
    RES_MGR_CMD_POST_EXEC__FAILED,
    RES_MGR_CMD_POST_EXEC__NUM
} ResMgr_PostExecRes_e;

typedef enum ResMgr_MergeRes_e_
{
    RES_MGR_CMD_MERGE_RES__NONE,
    RES_MGR_CMD_MERGE_RES__DEL_CUR_CMD,
    RES_MGR_CMD_MERGE_RES__DEL_WAIT_CMD,
    RES_MGR_CMD_MERGE_RES__DEL_BOTH_CMD,
    RES_MGR_CMD_MERGE_RES__STOP,
    RES_MGR_CMD_MERGE_RES__NUM
} ResMgr_MergeRes_e;

typedef enum ResMgr_CusCmdType_e_
{
    RES_MGR_CUS_CMD_TYPE__CHECK_EXEC,
    RES_MGR_CUS_CMD_TYPE__PRE_EXEC,
    RES_MGR_CUS_CMD_TYPE__PRE_EXEC_EXT,
    RES_MGR_CUS_CMD_TYPE__POST_EXEC,
    RES_MGR_CUS_CMD_TYPE__OPTIMIZE_CMD,
    RES_MGR_CUS_CMD_TYPE__GET_CMD_OUTPUT,
    RES_MGR_CUS_CMD_TYPE__NUM
} ResMgr_CusCmdType_e;

typedef ResMgr_ExecCheckRes_e (*ResMgr_IsExecutable)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef ResMgr_MergeRes_e (*ResMgr_IsMergable)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pWaitCmdHdl);
typedef ResMgr_CmdPreExecRes_e (*ResMgr_PreExecCmd)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef ResMgr_CmdHdl_t (*ResMgr_CusFunc)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CusCmdType_e eCusCmdType);
typedef s16 (*ResMgr_ExecCmd)(ResMgr_CmdHdl_t pCurCmdHdl);
typedef ResMgr_ExecRes_e (*ResMgr_ParseExecRes)(s16 sResult);
typedef ResMgr_PostExecRes_e (*ResMgr_PostExecCmd)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef s16 (*ResMgr_TerminateCmd)(ResMgr_CmdHdl_t pCurCmdHdl);
typedef u16 (*ResMgr_HandleRsp)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_RspHdl_t pRspHdl);
typedef void (*ResMgr_InformApp)(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
typedef void (*ResMgr_FreeCmd) (ResMgr_CmdHdl_t pCmdHdl);
typedef void (*ResMgr_UpdateCusData) (ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
typedef void (*ResMgr_FreeCusData) (void *pCusData);
typedef void (*ResMgr_GetCusData) (void *pSrcCusData, void *pRspData, void **ppDestCusData);
typedef void (*ResMgr_DenyCmd)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef void (*ResMgr_MergeCmd)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef void (*ResMgr_HandleExecFailed)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
typedef bool (*ResMgr_IsCmdRemovable)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

typedef struct ResMgrCmdItf_t_
{
    ResMgr_IsExecutable IsExecutable;
    ResMgr_PreExecCmd PreExecCmd;
    ResMgr_PostExecCmd PostExecCmd;
    ResMgr_HandleRsp HandleRsp;
    ResMgr_IsMergable IsMergable;
    ResMgr_MergeCmd MergeCmd;
    ResMgr_DenyCmd DenyCmd;
    ResMgr_HandleExecFailed HandleExecFailed;
    ResMgr_IsCmdRemovable IsCmdRemovable;
} ResMgrCmdItf_t;

typedef struct ResMgrCmdCusParm_t_
{
    ResMgr_CusFunc CusFunc;
    ResMgr_ExecCmd ExecCmd;
    ResMgr_ParseExecRes ParseResult;
    ResMgr_TerminateCmd TerminateCmd;
    ResMgr_InformApp InformApp;
    ResMgr_UpdateCusData UpdateCusData;
    ResMgr_FreeCusData FreeCusData;
    ResMgr_GetCusData GetCusData;
} ResMgrCmdCusParm_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
void ResMgr_InitCmd
(
    ResMgr_CmdHdl_t pCmdHdl,
    ResMgr_ResCategory_e eResCategory,
    ResMgrCmdItf_t *pCmdItf,
    ResMgrCmdCusParm_t *pCmdCusParm,
    void *pCusData
);

void ResMgr_DestroyCmd(ResMgr_CmdHdl_t pCmdHdl);

#endif //__RESMGR_CMDITF_H__

