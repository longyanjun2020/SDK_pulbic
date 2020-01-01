#ifndef __SOCKET_CMD_ITF_H__
#define __SOCKET_CMD_ITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformDefines.h"
#include "ResMgr_CmdItf.h"
#include "SockMgrDSPortItf.h"
#include "SockMgrConflictMgrItf.h"
#include "SockMgrBearerMgrItf.h"
#include "SockMgrComMediaMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SocketCmdHdl_t ;

typedef enum
{
	SOCKET_CMD_ATTR_DEAD_CMD           = 0X01, /// indicate the command is dead
	SOCKET_CMD_ATTR_LIVE_CMD           = 0X02, /// initial state for socket command
	SOCKET_CMD_ATTR_EXEC_CMD           = 0X04, /// indicate the command is executing
    ////////////////////////////////////////////// the above attributes are exclusive
	SOCKET_CMD_ATTR_INTERRUPTED        = 0X08, /// indicate the command is interrupt by socket manager
	SOCKET_CMD_ATTR_WAIT_TIMEOUT_CMD   = 0X10, /// indicate the command is trigger timer
	SOCKET_CMD_ATTR_DELAY_EXEC         = 0X20, /// indicate the command is treated as executing but still keep in queue
	SOCKET_CMD_ATTR_DONTCARE           = 0XFF, /// don't care
    SOCKET_CMD_ATTR_ALL                = 0XFF,
}SocketCmd_Attr_e;

typedef enum
{
	SOCKET_CMD_TYPE__PLAY_E,
	SOCKET_CMD_TYPE__STOP_E,
	SOCKET_CMD_TYPE__NUM,
}SocketCmd_Type_e;

typedef enum
{
	SOCKET_CMD_REQ__CREATECONNECTION_E = 0,		  /// SOCKET_CMD_TYPE__PLAY_E
	SOCKET_CMD_REQ__DESTROYCONNECTION_E,		  /// SOCKET_CMD_TYPE__STOP_E
    SOCKET_CMD_REQ__DESTROYALLCONNECTION_E,		  /// SOCKET_CMD_TYPE__STOP_E
	SOCKET_CMD_REQ__OPENSOCKET_E,		          /// SOCKET_CMD_TYPE__PLAY_E
	SOCKET_CMD_REQ__CLOSESOCKET_E,	              /// SOCKET_CMD_TYPE__STOP_E
	SOCKET_CMD_REQ__NUM,
}SocketCmd_Req_e;

typedef enum
{
	SOCKET_CMD_RSP__CREATECONNECTION_E = 0,		/// SOCKET_CMD_TYPE__PLAY_E
	SOCKET_CMD_RSP__DESTROYCONNECTION_E,		/// SOCKET_CMD_TYPE__STOP_E
    SOCKET_CMD_RSP__DESTROYALLCONNECTION_E,		/// SOCKET_CMD_TYPE__STOP_E
	SOCKET_CMD_RSP__OPENSOCKET_E,				/// SOCKET_CMD_TYPE__PLAY_E
	SOCKET_CMD_RSP__CLOSESOCKET_E,				/// SOCKET_CMD_TYPE__STOP_E
	SOCKET_CMD_RSP__NUM,
}SockMgr_SocketCmdRsp_e;

typedef enum
{
	SOCKMGR_SOCKETCMD_INEXEC__NO_ERROR = 0,
    SOCKMGR_SOCKETCMD_INEXEC__INVALID_PARAM,
    SOCKMGR_SOCKETCMD_INEXEC__CANT_RESOLVE_CONFLICT,
	SOCKMGR_SOCKETCMD_INEXEC__DATALINK_HAS_ACTIVATED,
	SOCKMGR_SOCKETCMD_INEXEC__UNACCEPT,
	SOCKMGR_SOCKETCMD_INEXEC__MERGED,
	SOCKMGR_SOCKETCMD_INEXEC__RESOURCE_NOT_ENOUGH,
    SOCKMGR_SOCKETCMD_INEXEC__NUM,
}SocketCmd_InExecErrCode_e;

typedef void (*SocketCmd_InExecHandler)(SocketCmdHdl_t hSocketCmd);
typedef void (*SocketCmd_ReSetCmdHandler)(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd);
typedef void (*SocketCmd_TerminateInfoApp)(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd, ResMgr_RspHdl_t hRspCmd);
typedef bool (*SocketCmd_NeedRetry)(SocketCmdHdl_t hSocketCmd);
typedef void (*SocketCmd_FakeInfoApp)(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd);
typedef bool (*SocketCmd_FindCmdMatchingCB)(void *pvUserData, SocketCmd_Req_e eReqType, SockMgr_ResCheckInfo_t *psResCheckInfo);
typedef void (*SocketCmd_TimeOutHandler)(CmdMgrStgrHdl_t hCmdStgr, SocketCmdHdl_t hSocketCmd);

typedef struct
{
    ResMgrCmdCusParm_t sResMgrCmdCusParam;
    SocketCmd_InExecHandler ErrHandler;
	SocketCmd_ReSetCmdHandler ReSetHandler;
    SocketCmd_TerminateInfoApp TerminateInfoApp;
	SocketCmd_NeedRetry NeedRetry;
	SocketCmd_FakeInfoApp FakeInfoApp;
	SocketCmd_TimeOutHandler CmdTimeOutHandler;
}SockMgrCmdCusParam_t;

typedef struct
{
	SockMgr_ResCheckInfo_t sResCheckInfo;
	SockMgrCmdCusParam_t sSockMgrCmdCusParam;
}SocketCmdCusParam_t;

typedef struct
{
	SockMgr_BearerHdl_t hBearer;
	SockMgr_ComMediaHdl_t hComMedia;
	SockMgr_DataLinkHdl_t hDataLink;
	SockMgr_ConnHdl_t hConn;
}SocketCmd_ConnectionResInfo_t;

typedef struct
{
	SockMgr_BearerHdl_t hBearer;
	SockMgr_ComMediaHdl_t hComMedia;
	SockMgr_DataLinkHdl_t hDataLink;
	SockMgr_SocketHdl_t hSocket;
}SocketCmd_SocketResInfo_t;

typedef struct
{
	union
	{
		SocketCmd_ConnectionResInfo_t sConnectionResInfo;
        SocketCmd_SocketResInfo_t sSocketResInfo;
	}uOccupyResInfo;
}SocketCmd_OccupyResInfo_t;

typedef struct
{
    SockMgr_CtnrHdl_t hConflictBearerCandidates;
	SockMgr_CtnrHdl_t hConflictComMediaCandidates;
	SockMgr_CtnrHdl_t hConflictDataLinkCandidates;
}SocketCmd_ConnectionConflictInfo_t;

typedef struct
{
	SockMgr_CtnrHdl_t hConflictSocketCandidates;
}SocketCmd_SocketConflictInfo_t;

typedef struct
{
	union
	{
        SocketCmd_ConnectionConflictInfo_t sConnectionConflictInfo;
        SocketCmd_SocketConflictInfo_t sSocketConflictInfo;
	}uConflictInfo;
}SocketCmd_ResConflictInfo_t;

typedef struct
{
	SocketCmd_Attr_e eAttribute;
	ResMgr_AppId_e eApOwner;
	SocketCmd_Req_e eCmdReq;
	union
	{
		SockMgr_ConnHdl_t hConn;
		SockMgr_SocketHdl_t hSocket;
	}uQueryParam;
}SocketCmdQueryInfo_t;

typedef enum
{
    SOCKET_CMD_ABORT_ACTION_DESTROY_ALL_CONNECTIONS_E = 0,
    SOCKET_CMD_ABORT_ACTION_DATALINK_CLOSE_BY_PEER_E,
    SOCKET_CMD_UTIL_NUM,
}SocketCmdAbort_e;

typedef struct
{
    SockMgr_DataLinkHdl_t hDataLink;
    ResMgr_CmdHdl_t hRspCmd;
    CmdMgrStgrHdl_t hCmdMgrStgr;
    SocketCmdHdl_t hSocketCmd;
}SocketCmdUtil_DataLinkCloseByPeer_t;

typedef SocketCmdUtil_DataLinkCloseByPeer_t SocketCmdUtil_DestroyAllConnections_t;

typedef struct
{
    SocketCmdAbort_e eAction;
    union
    {
        SocketCmdUtil_DataLinkCloseByPeer_t sDataLinkCloseByPeer;
        SocketCmdUtil_DestroyAllConnections_t sDestroyAllConnections;
    }AbortData_u;
}SocketCmdAbortData_t;

typedef void (*SocketCmd_TraverseCB)(void *pvSocketCmd, void *pvUserData);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

void SocketCmd_ReInitPlayCmd
(
 SocketCmdHdl_t hSocketCmd
);

ResMgr_ExecCheckRes_e SocketCmd_PlayIsExec
(
  CmdMgrStgrHdl_t pStgrHdl,
  ResMgr_CmdHdl_t pCurCmdHdl
);

ResMgr_ExecCheckRes_e SocketCmd_StopIsExec
(
 CmdMgrStgrHdl_t hCmdMgrStgr,
 ResMgr_CmdHdl_t hCmd
);

ResMgr_ExecCheckRes_e SocketCmd_ReSetIsExec
(
 CmdMgrStgrHdl_t hCmdMgrStgr,
 ResMgr_CmdHdl_t hCmd
);

ResMgr_CmdPreExecRes_e SocketCmd_PlayPreExec
(
  CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl
);

ResMgr_MergeRes_e SocketCmd_PlayMerger
(
  CmdMgrStgrHdl_t pStgrHdl, 
  ResMgr_CmdHdl_t pCurCmdHdl, 
  ResMgr_CmdHdl_t pWaitCmdHdl
);

ResMgr_PostExecRes_e SocketCmd_PlayPostExec
(
  CmdMgrStgrHdl_t hCmdMgrStgr,
  ResMgr_CmdHdl_t hCmd
);

ResMgr_CmdPreExecRes_e SocketCmd_StopPreExec
(
  CmdMgrStgrHdl_t hCmdMgrStgr,
  ResMgr_CmdHdl_t hCmd
);

ResMgr_PostExecRes_e SocketCmd_StopPostExec
(
 CmdMgrStgrHdl_t hCmdMgrStgr,
 ResMgr_CmdHdl_t hCmd
);

void SocketCmd_PlayAbort
(
 CmdMgrStgrHdl_t pStgrHdl,
 ResMgr_CmdHdl_t pCurCmdHdl
);

void SocketCmd_StopAbort
(
 CmdMgrStgrHdl_t pStgrHdl,
 ResMgr_CmdHdl_t pCurCmdHdl
);

u16 SocketCmd_PlayHandleRsp
(
  CmdMgrStgrHdl_t pStgrHdl,
  ResMgr_CmdHdl_t pCurCmdHdl
);

u16 SocketCmd_StopHandleRsp
(
  CmdMgrStgrHdl_t pStgrHdl,
  ResMgr_CmdHdl_t pCurCmdHdl
);

void SocketCmd_StopResetWaitable
(
  ResMgr_CmdHdl_t pCurCmdHdl,
  ResMgr_CmdHdl_t hRspCmd
);

bool SocketCmd_IsValidPlayParam
(
  SocketCmdHdl_t hSocketCmd
);

bool SocketCmd_IsValidStopParam
(
   SocketCmdHdl_t hSocketCmd
);

bool SocketCmd_IsStopCmdNeedWait
(
   SocketCmdHdl_t hSocketCmd
);

void SocketCmd_InfoApp
(
  CmdMgrStgrHdl_t hCmdStgr,
  SocketCmdHdl_t hSocketCmd,
  ResMgr_CmdHdl_t hRspCmd
);

void SocketCmd_PlayFakeInfoApp
( 
  CmdMgrStgrHdl_t pStgrHdl, 
  ResMgr_CmdHdl_t pCurCmdHdl
);

u16 SocketCmd_HandleProRsp
(
  SocketCmdHdl_t hSocketCmd,
  ResMgr_CmdHdl_t hRspCmd
);

void SocketCmd_TraverseSocketCmd
(
    SocketCmd_TraverseCB cbTraverseSocketCmd,
    void *pvUserData
);
void SocketCmd_Terminate
(
  SocketCmdHdl_t hSocketCmd
);

bool SocketCmd_QuerySocketCmd
(
  SocketCmdQueryInfo_t *psQueryInfo,
  SocketCmdHdl_t *phSocketCmd
);

bool SocketCmd_FindSocketCmd
(
  void *pvMatchData,
  SocketCmd_FindCmdMatchingCB pfnMatchCb,
  SocketCmdHdl_t *phSocketCmd
);

/// CUS DATA
void *SocketCmd_GetCusData
(
  SocketCmdHdl_t hSocketCmd
);

/// Read Only
void SocketCmd_GetResCheckInfo
(
  SocketCmdHdl_t hSocketCmd,
  SockMgr_ResCheckInfo_t *psResCheckInfo
);

void SocketCmd_SetOccupyResInfo
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_OccupyResInfo_t *psOccupyResInfo
);

void SocketCmd_GetOccupyResInfo
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_OccupyResInfo_t *psOccupyResInfo
);

void SocketCmd_ReSetOccupyResInfo
(
  SocketCmdHdl_t hSocketCmd
);

void SocketCmd_SetResConflictInfo
(
    SocketCmdHdl_t hSocketCmd,
  SocketCmd_ResConflictInfo_t *psResConflictInfo
);

void SocketCmd_GetResConflictInfo
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_ResConflictInfo_t *psResConflictInfo
);

void SocketCmd_ReSetResConflictInfo
(
  SocketCmdHdl_t hSocketCmd
);

// GET CMD TYPE
SocketCmd_Req_e SocketCmd_GetCmdReq
(
  SocketCmdHdl_t hSocketCmd
);

SocketCmd_Req_e SocketCmd_GetOppositeCmdReq
(
  SocketCmdHdl_t hSocketCmd
);

SocketCmd_Type_e SocketCmd_GetCmdType
(
  SocketCmdHdl_t hSocketCmd
);

// OCCUPY RES & REL RES
bool SocketCmd_OccupyRes
(
  SocketCmdHdl_t hSocketCmd
);

bool SocketCmd_ReleaseRes
(
  SocketCmdHdl_t hSocketCmd
);

void SocketCmd_DestroyExtRes
(
  SocketCmdHdl_t hSocketCmd
);

/// ATTRIBUTE
void SocketCmd_SetAttr
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_Attr_e eAttribute
);

void SocketCmd_ReSetAttr
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_Attr_e eAttribute
);

bool SocketCmd_CheckAttr
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_Attr_e eAttribute
);

ResMgr_AppId_e SocketCmd_GetCmdOwnerId
(
  SocketCmdHdl_t hSocketCmd
);

SocketCmd_InExecErrCode_e SocketCmd_GetInExecErrCode
(
  SocketCmdHdl_t hSocketCmd
);

void SocketCmd_SetInExecErrCode
(
  SocketCmdHdl_t hSocketCmd,
  SocketCmd_InExecErrCode_e eInExecErrCode
);

bool SocketCmd_IsValid
(
  SocketCmdHdl_t hSocketCmd
);

SockMgr_TimeId_t SocketCmd_GetTimerId
(
  SocketCmdHdl_t hSocketCmd
);

void SocketCmd_SetTimerId
(
  SocketCmdHdl_t hSocketCmd,
  SockMgr_TimeId_t sTimerId
);

void SocketCmd_TimerOutCb
(
  SockMgr_TimeId_t sTimerId,
  u32 uUserData
); 

void SocketCmdUtil_CheckNotify
(
  CmdMgrStgrHdl_t hSocketStgr,
  SocketCmdHdl_t hSocketCmd,
  ResMgr_CmdHdl_t hRspCmd
);

void SocketCmdUtil_NotifyHasConnectedSocket
(
  CmdMgrStgrHdl_t hSocketStgr,
  SockMgr_Bearer_e eBearer
);

void SocketCmdUtil_NotifyAvaliableDataLink
(
  CmdMgrStgrHdl_t hSocketStgr,
  SockMgr_Bearer_e eBearer
);


void SocketCmdUtil_AbortCmdHandler
(
  SocketCmdAbortData_t *psAbortData
);

bool SocketCmdUtil_IsAnySocketConnect
(
  CmdMgrStgrHdl_t hSocketStgr, 
  SockMgr_Bearer_e eBearer
);


#ifdef __RES_MGR_DEBUG__

void SocketCmd_HistoryTbl_RecordReqCmd(SocketCmdHdl_t hSocketCmd);
void SocketCmd_HistoryTbl_RecordRspCmd(ResMgr_CmdHdl_t hRspCmd);
void SocketCmd_HistoryTbl_RecordCtrlCmd(ResMgr_CmdHdl_t hRspCmd);

#endif/* __RES_MGR_DEBUG__ */

#endif/* __SOCKET_CMD_ITF_H__ */
