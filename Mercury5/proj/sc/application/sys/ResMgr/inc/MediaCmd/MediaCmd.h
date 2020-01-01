/**
* @file MediaCmd.h
*
* This header file defines the interfaces of Media Commands
*
*/

#ifndef __MEDIACMD_H__
#define __MEDIACMD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "MediaCmdItf.h"
#include "MediaFsmItf.h"
#include "ResMgr_Cmd.h"
#include "DListItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct MediaCmdBindInfo_t_
{
    union
    {
        /* Slave command list for master command */
        DList_t *pSlaveCmdList;
        /* Pointer to master command handle for slave command */
        struct MediaCmd_t_ *pMasterCmd;
    } tBindInfo;
} MediaCmdBindInfo_t;

typedef struct MediaCmd_t_
{
    ResMgr_Cmd_t tResMgrCmd;

    /* The command type. Generalized into setup, play, exec, stop, etc. */
    MediaCmdType_e eMediaCmdType;

    /* The command action type */
    MediaCmdActType_e eActType;

    /* The command suspend type. It can be automatic suspend or interactive suspend */
    MediaCmdSuspend_e eSuspendType;

    /* The command resume type. It can be automatic resume or no resume. */
    MediaCmdResume_e eResume;

    /* The command resource info. It's used to remap the command required resource. */
    MediaResInfo_e eResInfo;

    /* The native attribute of media command */
    u32 uAttribute;

    /* The extend attribute of media command */
    u32 uAttributeExt;

    /* The list of binding slave commands */
    MediaCmdBindInfo_t tBindCmdInfo;

    /* Pointer to the command's state machine. It's initialized when command is executed. */
    MediaStateMachineHandle_t pMediaFsmHdl;

    /* The synchronous mode of the command */
    bool bSync;
} MediaCmd_t;

#ifdef __RES_MGR_DEBUG__
#define MAX_HISTORY_ITEM_NUM 200

typedef enum MediaCmdHistoryOpType_e_
{
    MEDIA_CMD_HISTORY_TYPE__AP_REQ,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_REQ,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_STOP_REQ,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_DENY_CNF,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_CNF,
    MEDIA_CMD_HISTORY_TYPE__DRIVER_CNF,
    MEDIA_CMD_HISTORY_TYPE__DRIVER_NOTIFY,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_EXEC_FAIL_CNF,
    MEDIA_CMD_HISTORY_TYPE__RESMGR_MERGE_CMD_CNF
} MediaCmdHistoryOpType_e;

typedef struct MediaCmdHistoryItem_t_
{
    u8 eOpType;
    u8 uId;
    u8 uAppId;
    u8 uExecRes;
    void *pData;
} MediaCmdHistoryItem_t;

typedef struct MediaCmdHistoryTab_t_
{
    u32 uLastRecIdx;
    MediaCmdHistoryItem_t aResMgrCmdHistory[MAX_HISTORY_ITEM_NUM];
} MediaCmdHistoryTab_t;

//extern MediaCmdHistoryTab_t tResMgrCmdHistoryTab;

__SLDPM_FREE__ void Media_RecordCmdHistory(MediaCmdHistoryOpType_e eOpType, u32 uId, ResMgr_AppId_e eAppId, ResMgr_ExecRes_e eExecRes, void *pData);
#endif

typedef void (*MediaCmdExecFunc)(CmdMgrStgrHdl_t pStgrHdl, MediaCmd_t *pMediaCmd);

void Media_UnBindMasterCmd(MediaCmd_t *pCurCmd, MediaCmd_t *pMasterCmd);
void Media_SetBTStatusChangeStatus(ResMgr_CmdHdl_t pMasterCmdHdl, u32 nFinishStatus);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIACMD_H__

