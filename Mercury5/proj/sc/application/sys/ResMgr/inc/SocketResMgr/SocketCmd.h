#ifndef __SOCKET_CMD_H__
#define __SOCKET_CMD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SocketCmdItf.h"
#include "ResMgr_Cmd.h"
#include "SockMgrPlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
	ResMgr_Cmd_t sResMgrCmd;
	SocketCmd_InExecHandler ErrHandler;
	SocketCmd_ReSetCmdHandler ReSetHandler;
	SocketCmd_TerminateInfoApp TerminateInfoApp;
	SocketCmd_NeedRetry NeedRetry;
	SocketCmd_FakeInfoApp FakeInfoApp;
	SocketCmd_TimeOutHandler CmdTimeOutHandler;
	SocketCmd_Req_e eCmdReq;
	SocketCmd_Type_e eCmdType;
	SockMgr_ResCheckInfo_t sResCheckInfo;
	union
	{
		SocketCmd_OccupyResInfo_t sOccupyResInfo;
		SocketCmd_ResConflictInfo_t sResConflictInfo;
	}uResInfo;
	SocketCmd_Attr_e eAttribute;
	SockMgr_TimeId_t sTimerId;
	u32 uCmdData;
	SocketCmd_InExecErrCode_e eInExecErrCode;
#ifdef __RES_MGR_DEBUG__
    u8 uSuccessCnt;
    u8 uFailedCnt;
#endif/* __RES_MGR_DEBUG__ */
}SocketCmd_t;

#ifdef __RES_MGR_DEBUG__

#define SOCKET_CMD_HISTORY_TBL_SIZE (100)
typedef enum
{
    SOCKET_CMD_ID_CREATE_CONNECTION_REQ_E = 0XFF00,
    SOCKET_CMD_ID_DESTROY_CONNECTION_REQ_E,
    SOCKET_CMD_ID_DESTROY_ALL_CONNECTIONS_REQ_E,
    SOCKET_CMD_ID_OPEN_SOCKET_REQ_E,
    SOCKET_CMD_ID_CLOSE_SOCKET_REQ_E,
    SOCKET_CMD_ID_CREATE_CONNECTION_RSP_E,
    SOCKET_CMD_ID_DESTROY_CONNECTION_RSP_E,
    SOCKET_CMD_ID_DESTROY_ALL_CONNECTIONS_RSP_E,
    SOCKET_CMD_ID_OPEN_SOCKET_RSP_E,
    SOCKET_CMD_ID_CLOSE_SOCKET_RSP_E,
    SOCKET_CMD_ID_DATALINK_CLOSE_BY_PEER_IND_E,
    SOCKET_CMD_ID_DATALINK_CLOSE_BY_PREEMPT_IND_E,
    SOCKET_CMD_ID_DATALINK_CLOSE_BY_IP_EXPIRE_IND_E,
    SOCKET_CMD_ID_SOCKET_CLOSE_BY_TCP_E,
    SOCKET_CMD_ID_BEARER_DATALINK_AVAILABLE_E,
    SOCKET_CMD_ID_BEARER_NO_CONNECTED_SOCKET_E,
    SOCKET_CMD_ID_CTRL_REQ_LISTENER_E,
    SOCKET_CMD_ID_CTRL_DEREQ_LISTENER_E,
    SOCKET_CMD_ID_CTRL_UPDATE_BEARER_E,
}SocketCmd_HistroyOpType_e;

typedef struct
{
	u32 uUserData;
    u32 uConn;
}SocketCmd_History_DataLink_t;

typedef struct
{
	u32 uUserData;
	u32 uSocket;
}SocketCmd_History_Socket_t;

typedef union
{
    SocketCmd_History_DataLink_t sDataLink;
	SocketCmd_History_Socket_t sSocket;
}SocketCmd_History_Data_t;

typedef struct
{
    SocketCmd_HistroyOpType_e eOpType;
    u8 uRspId;
    u8 uAppId;
    u16 uExecRes;
    void *pData;
	SocketCmd_History_Data_t sData;
}SocketCmd_History_Item_t;

typedef struct
{
    u16 uLastFocusIdx;
    SocketCmd_History_Item_t sItems[SOCKET_CMD_HISTORY_TBL_SIZE];
}SocketCmd_HistoryTbl_t;

#endif/* __RES_MGR_DEBUG__ */

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/// use when call SocketCmd_TraverseSocketCmd
///     SockMgr_QueryConnectionNonExpiredSockets_t
// void SocketCmd_TermintateNonExpiredSocket(void *pvSocketCmd, void *pvUserData);

bool SocketCmd_TerminateOpenSocketCmds(SockMgr_ConnHdl_t hConn);

#endif/* __SOCKET_CMD_H__ */
