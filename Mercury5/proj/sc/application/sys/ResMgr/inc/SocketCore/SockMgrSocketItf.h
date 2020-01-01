#ifndef _SOCKMGR_SOCKET_ITF_H_
#define _SOCKMGR_SOCKET_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrFsmItf.h"
#include "SockMgrResItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

#define SOCKMGR_SOCKET_ATTR__NONE             (0X00)
#define SOCKMGR_SOCKET_ATTR__INTERRUPTED      (0X01)
#define SOCKMGR_SOCKET_ATTR__DESTROY_DIRECTLY (0X02)
#define SOCKMGR_SOCKET_ATTR__DESTROY_EARLY    (0X04)
#define SOCKMGR_SOCKET_ATTR__DESTROY_MERGED   (0X08)

typedef enum
{
	SOCKETREQ_CONN = 0,
	SOCKETREQ_SEND,
	SOCKETREQ_SENDTO,
	SOCKETREQ_RECV,
	SOCKETREQ_RECVFROM,
	SOCKETREQ_CLOSE,
	SOCKETREQ_SETOPT,
	SOCKETREQ_GETOPT,
	SOCKETREQ_SHUTDOWN,
	SOCKETREQ_TOTAL_NO
}SocketReqType_e;

typedef struct _SockMgr_SocketCreateData_t_
{
	u8 uSocketType;        /// mapping to mserv MSERV_MIC_NET_SOCKET_TYPE_UDP/MSERV_MIC_NET_SOCKET_TYPE_TCP
	u8 uSDKVersion;        /// mapping to mserv NET_SDK_VER_1/NET_SDK_VER_2
	ResMgr_AppId_e eAp;    /// mapping to vendor app id
    void *pvSocketWrapper; /// mapping to socket wrapper
}SockMgr_SocketCreateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_SocketHdl_t SockMgr_SocketFactory_CreateSocket
(
  SockMgr_SocketCreateData_t *psSocketCreateData
);

void SockMgr_SocketFactory_DestroySocket
(
  SockMgr_SocketHdl_t hSocket, 
  ResMgr_AppId_e eAp
);

SockMgr_FSMHdl_t SockMgr_Socket_GetSocketFSM
(
  SockMgr_SocketHdl_t hSocket
);

SockMgr_DataLinkHdl_t SockMgr_Socket_GetParentDataLink
(
  SockMgr_SocketHdl_t hSocket
);

SockMgr_ConnHdl_t SockMgr_Socket_GetConnection
(
  SockMgr_SocketHdl_t hSocket
);

void SockMgr_Socket_SetAsNonExpiredSocket
(
  SockMgr_SocketHdl_t hSocket, 
  SockMgr_DataLinkHdl_t hParentDataLink
);

void SockMgr_Socket_SetAsExpiredSocket
(
  SockMgr_SocketHdl_t hSocket
);

bool SockMgr_Socket_IsSocketExpired
(
  SockMgr_SocketHdl_t hSocket
);

ResMgr_AppId_e SockMgr_Socket_GetOwnerApId
(
  SockMgr_SocketHdl_t hSocket
);

bool SockMgr_Socket_IsCreatedByExt
(
  SockMgr_SocketHdl_t hSocket
);

bool SockMgr_Socket_IsValidSocket
(
  SockMgr_SocketHdl_t hSocket
);

void SockMgr_Socket_ReInit
(
  SockMgr_SocketHdl_t hSocket
);

void SockMgr_Socket_SetAttr
(
  SockMgr_SocketHdl_t hSocket,
  u8 uAttr
);

bool SockMgr_Socket_CheckAttr
(
  SockMgr_SocketHdl_t hSocket,
  u8 uAttr
);

void SockMgr_Socket_ReSetAttr
(
  SockMgr_SocketHdl_t hSocket,
  u8 uAttr
);


#ifdef _SOCKMGR_DEBUG_MODE_
void SockMgr_Socket_ShowSocketInfo
(
  SockMgr_SocketHdl_t hSocket
);
#endif /* _SOCKMGR_DEBUG_MODE_ */


#endif/* _SOCKMGR_SOCKET_ITF_H_ */
