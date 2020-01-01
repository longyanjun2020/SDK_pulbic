#ifdef __TTS__
#ifndef __MMI_SRV_STGR_H__
#define __MMI_SRV_STGR_H__

#include "DataStructItf.h"
#include "mmi_mae_common_def.h"

#define SRVSTGR_TRAVERSE_MSG_NONE   (0X00)
#define SRVSTGR_TRAVERSE_MSG_DELETE (0X01)

#define SRVSTGR_EXEC_PLAY_AGAIN (0XEF)

#define SRVSTGR_RSP_DELETE_REQ  (0X01)
#define SRVSTGR_RSP_DELETE_RSP  (0X02)
#define SRVSTGR_RSP_DELETE_PLAY (0X04)


typedef void* SrvStgrHdl_t;
typedef void* SrvStgrCmdHdl_t;

typedef void (*SrvStgrCmdDataFreeCB)(void *pvCmdData);

typedef enum
{
    SrvStgr_MsgType_Req,
    SrvStgr_MsgType_Rsp,
    SrvStgr_MsgType_Unknown,
    SrvStgr_MsgType_Num,
}SRVSTGR_MSGTYPE_e;

typedef enum
{
    SRVSTGR_CheckExec_Res_Executable = 0,
    SRVSTGR_CheckExec_Res_Busy,
    SRVSTGR_CheckExec_Res_InExecutable,
    SRVSTGR_CheckExec_Res_Failed,
    SRVSTGR_CheckExec_Res_Num,
}SRVSTGR_CHECKEXEC_RES_e;

typedef enum
{
    SRVSTGR_MsgPurge_Res_None = 0,
    SRVSTGR_MsgPurge_Res_DelCurMsg,
    SRVSTGR_MsgPurge_Res_DelWaitMsg,
    SRVSTGR_MsgPurge_Res_DelBothMsg,
    SRVSTGR_MsgPurge_Res_Stop,
    SRVSTGR_MsgPurge_Res_Num,
} SRVSTGR_MSGPURGE_RES_e;

/// service strategier interface
typedef SRVSTGR_MSGTYPE_e (*SrvStgr_MsgClassifierCB)(SrvStgrHdl_t hSrvStgr, void *pvMsg);
typedef u32 (*SrvStgr_HandleRspMsgCB)(SrvStgrHdl_t hSrvStgr, void *pvRspMsg);
typedef void (*SrvStgr_FreeExecMsgCB)(void *pvMsg);
typedef void (*SrvStgr_FreeAbortMsgCB)(void *pvMsg);
typedef void (*SrvStgr_SetRelatedMsgBusyCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg);
typedef void (*SrvStgr_IsRelatedMsgBusyCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg);
typedef u16 (*SrvStgr_CheckMsgPurgeableCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg, void *pvNextMsg);
typedef SRVSTGR_CHECKEXEC_RES_e (*SrvStgr_IsExecutableCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg);
typedef SRVSTGR_CHECKEXEC_RES_e (*SrvStgr_PreExecMsgCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg);
typedef SRVSTGR_CHECKEXEC_RES_e (*SrvStgr_ExecMsgCB)(void *pvCurMsg);
typedef SRVSTGR_CHECKEXEC_RES_e (*SrvStgr_PostExecMsgCB)(SrvStgrHdl_t hSrvStgr, void *pvCurMsg);
typedef void (*SrvStgr_InfoAppCB)(SrvStgrHdl_t hSrvStgr, void *pvRspMsg);
typedef void*(*SrvStgr_RetrieveReqMsgCB)(SrvStgrHdl_t hSrvStgr, void *pvRspMsg);
typedef void (*SrvStgr_UninitDataCB)(SrvStgrHdl_t hSrvStgr);
typedef void (*SrvStgr_DestroyCmdCB)(SrvStgrHdl_t hSrvStgr, void *pvCurCmd);

typedef struct
{
    SrvStgr_MsgClassifierCB pfnSrvClassifierCb;
    SrvStgr_HandleRspMsgCB pfnSrvHandleRspCb;
    SrvStgr_FreeExecMsgCB pfnSrvFreeExecMsgCb;
    SrvStgr_FreeAbortMsgCB pfnSrvFreeAbortMsgCb;
    SrvStgr_IsRelatedMsgBusyCB pfnSrvIsRelatedMsgBusyCb;
    SrvStgr_SetRelatedMsgBusyCB pfnSrvSetRelatedMsgBusyCb;
    SrvStgr_CheckMsgPurgeableCB pfnSrvCheckMsgPurgeableCb;
    SrvStgr_IsExecutableCB pfnSrvIsExecCb;
    SrvStgr_PreExecMsgCB pfnSrvPreExecCb;
    SrvStgr_PostExecMsgCB pfnSrvPostExecCb;
    SrvStgr_RetrieveReqMsgCB pfnSrvRetrieveReqMsgCb;
    SrvStgr_DestroyCmdCB pfnSrvDestroyCmdCb;
}SrvStgrCmnItf_t;

typedef void (*SrvStgr_InfoAbortCB)(SrvStgrHdl_t hSrvStgr, void *pvMsg);

typedef struct
{
    SrvStgr_ExecMsgCB pfnSrvExecCb;
    SrvStgr_InfoAbortCB pfnSrvInfoAbortCb;
    SrvStgr_InfoAppCB pfnSrvInfoAppCb;
}SrvStgrCusItf_t;

typedef struct
{
    void *pvCheckBusyData;
    void *pvOwnerSrv;
    void *pvCurMsg;
    void *pvPurgedMsg;
}SrvStgrInitData_t;

typedef struct
{
    SrvStgrCmnItf_t sCmnItf;
    SrvStgrCusItf_t sCusItf;
    DataStruct_t *psCmdQueue;
    SrvStgrInitData_t sData;
}SrvStgr_t;

typedef struct
{
    u32 uCmdType;
    SrvStgrCmdDataFreeCB pfnCmdDataFreeCb;
    u32 uAttribute;
    void *pvCmdData;
    void *pvSrvStgr;
}SrvStgrCmd_t;

void SrvStgr_Init(SrvStgrHdl_t hSrvStgr, SrvStgrCmnItf_t *psCmnItf, SrvStgrCusItf_t *psCusItf, SrvStgrInitData_t *psInitData);
void SrvStgr_Uninit(SrvStgrHdl_t hSrvStgr, SrvStgr_UninitDataCB pfnUninitDataCb);
boolean SrvStgr_Parser(SrvStgrHdl_t hSrvStgr, void *pvMsg);
void SrvStgr_HandleReq(SrvStgrHdl_t hSrvStgr, void *pvReqMsg);
void SrvStgr_HandleRsp(SrvStgrHdl_t hSrvStgr, void *pvRspMsg);
SrvStgrCmdHdl_t SrvStgr_CmdCreate(SrvStgrHdl_t hSrvStgr, u32 uCmdType, void *pvCmdData, SrvStgrCmdDataFreeCB pfnCmdDataFreeCb);
void SrvStgr_CmdDestroy(SrvStgrCmdHdl_t hSrvStgrCmd);
u16 SrvStgr_CmdNumInQueue(SrvStgrHdl_t hSrvStgr);
void SrvStgr_AddCmd(SrvStgrHdl_t hSrvStgr, void *pvReqMsg);
void SrvStgr_FetchNextCmd(SrvStgrHdl_t hSrvStgr);
boolean SrvStgr_IsPurgeable(SrvStgrHdl_t hSrvStgr, void *pvMsg);
boolean SrvStgr_FindPurgeableMsg(SrvStgrHdl_t hSrvStgr);

#endif/* __MMI_SRV_STGR_H__ */
#endif/* __TTS__ */
