#ifndef __SOCKET_CMDRSPITF_H__
#define __SOCKET_CMDRSPITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_Rsp.h"
#include "SockMgrPlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/// pro-active event
typedef enum
{
    SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_PEER = 0XF0, 
	SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_PREEMPT,
	SOCKMGR_RSP_ID__SOCKET_CLOSE_BY_TCP,
	SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_IP_EXIPRED, /// datalink is closed due to ip address expired
    SOCKMGR_RSP_ID__BEARER_AVAILABLE_DATALINK,
    SOCKMGR_RSP_ID__BEARER_NO_CONNECTED_SOCKET,
	SOCKMGR_RSP_ID__COMMAND_TIMEOUT,
	SOCKMGR_RSP_ID__NUM,
	SOCKMGR_RSP_ID__INVALID,
}SocketCmdProRspId_e;

typedef struct
{
    bool bStatus;
    SockMgr_Bearer_e eBearer;
}SocketCmdProRspBearerInfo_t;

typedef struct
{
	/// datalink related
	///   SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_PEER
	///   SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_PREEMPT
	///   SOCKMGR_RSP_ID__DATALINK_CLOSE_BY_IP_EXIPRED
	/// socket related
	///   SOCKMGR_RSP_ID__SOCKET_CLOSE_BY_TCP
	/// bearer related
	///   SOCKMGR_RSP_ID__BEARER_AVAILABLE_DATALINK
	///   SOCKMGR_RSP_ID__BEARER_NO_CONNECTED_SOCKET
    SocketCmdProRspId_e eRspId;
	union
	{
        SockMgr_ConnHdl_t hConn;                 /// datalink related
        SockMgr_SocketHdl_t hSocket;             /// socket related
        SocketCmdProRspBearerInfo_t sBearerInfo; /// bearer related
	}RspData_u;
}SocketCmdProRspInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/



#endif/* __SOCKET_CMDRSPITF_H__ */
