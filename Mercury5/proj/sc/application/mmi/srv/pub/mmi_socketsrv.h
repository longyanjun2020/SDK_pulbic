/**
* @file mmi_socketsrv.h
*
* Class Id: CLSID_SOCKETSRV
*
* @version $Id$
*/
#ifndef __MMI_SOCKETSRV_H__
#define __MMI_SOCKETSRV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "ms_socket_cmn.h"

/*-------------------------------------------------------------------------*/
/**
 * ISOCKETSRV Interfaces
 */
#define INHERIT_ISOCKETSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(ISOCKETSRV);

#define ISocket_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), ISOCKETSRV)->QueryInterface(pICntlr, id, pp, po)
#define ISocket_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), ISOCKETSRV)->HandleEvent(pICntlr, e, p1, p2)
MAE_Ret SocketSrvNew(MAE_ClsId nId, void **ppObj);

typedef void* SrvSocketHdl_t;

typedef enum
{
    SRV_NETWORK_STATUS_DATALINK_CLOSE_BY_PEER = MSERV_NETWORK_STATUS_DATALINK_CLOSE_BY_PEER,
    SRV_NETWORK_STATUS_INVALID = MSERV_NETWORK_STATUS_INVALID,
}SrvSocketNetworkStatus_e;

/// originally re-defined

typedef MservSocketNetworkProfile_t SrvSocketNetworkProfile_t;
typedef MservSocketQueryDatalink_t SrvSocketQueryDatalink_t;
typedef MservSocketTrafficStatus_t SrvSocketTrafficStatus_t;
typedef MservSocketBearer_e SrvSocketBearer_e;
typedef Mserv_socket_status_rsp_info_t SrvSocketBearerStatusInfo_t;
typedef MservSocketBearerInfo_t SrvSocketBearerInfo_t;
typedef MservSocketQueryBearerStatusInfo_t SrvSocketQueryBearerStatusInfo_t;
/// used for set/get socket option's parameter level
#define SRV_SOL_SOCKET (MSERV_SOL_SOCKET)
#define SRV_SOL_IP     (MSERV_SOL_IP)
#define SRV_SOL_TCP    (MSERV_SOL_TCP)
#define SRV_SOL_UDP    (MSERV_SOL_UDP)

/// used for set/get socket option's parameter optname
#define SRV_SO_KEEPALIVE (MSERV_SO_KEEPALIVE)
#define SRV_SO_LINGER    (MSERV_SO_LINGER)
#define SRV_SO_SNDBUF    (MSERV_SO_SNDBUF)
#define SRV_SO_RCVBUF    (MSERV_SO_RCVBUF)
#define SRV_TCP_NODELAY  (MSERV_TCP_NODELAY)

/// used for shutdown socket
#define SRV_SD_RECV    (MSERV_SD_RECV)
#define SRV_SD_SEND    (MSERV_SD_SEND)
#define SRV_SD_BOTH    (MSERV_SD_BOTH)

/// define callbacks
typedef void (*SrvSocketCreateDatalinkCB)(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketCloseDatalinkCB)(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketConnectCB)(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketSendCB)(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketSendToCB)(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketDestroySocketCB)(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketCloseAllDatalinkCB)(IBase *piCaller, MservSocketBearer_e bearer, void *pvUserData, MAE_Ret nResult);
typedef void (*SrvSocketRecvCB)(IBase *piCaller, SrvSocketHdl_t hSockets, u8 *buf, s32 len, void *pvUserData);
typedef void (*SrvSocketRecvFromCB)(IBase *piCaller, SrvSocketHdl_t hSocket, u8 *buf, s32 len, struct sockaddr *from, s32 fromlen, void *pvUserData);
typedef void (*SrvSocketGetHostByNameCB)(IBase *piCaller, u8 ti, struct hostent *host, void *pvUserData);
typedef void (*SrvSocketBearerStatusCB)(IBase *piCaller, void *pvUserData, SrvSocketBearerStatusInfo_t *pinfo);
typedef void (*SrvSocketNetworkStatusCB)(IBase *piCaller, void *pvUserData, SrvSocketNetworkStatus_e eStatus);
typedef void (*SrvSocketPingCB)(IBase *piCaller, void *pvUserData ,u8 ti, MAE_Ret nResult);
typedef void (*SrvSocketTrafficStatusChangeCB)(IBase *piCaller, SrvSocketBearerInfo_t sBearerInfo, SrvSocketTrafficStatus_t sStatus, void *pvUserData);
typedef void (*SrvSocketStatisticQueryCB)(IBase *piCaller, SrvSocketBearerInfo_t sBearerInfo, void *pvUserData, u8 nTi, u32 nBytes, MAE_Ret nResult);
typedef void (*SrvSocketStatisticResetCB)(IBase *piCaller, SrvSocketBearerInfo_t sBearerInfo, void *pvUserData, u8 nTi, MAE_Ret nResult);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  SOCKET Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/// BSD socket like APIs
MAE_Ret SocketSrvCreateDatalink(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketNetworkProfile_t *psNetworkProfile);
MAE_Ret SocketSrvCreateDatalinkAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketNetworkProfile_t *psNetworkProfile, SrvSocketCreateDatalinkCB pfnCreateDatalinkCb, void *pUserData);
MAE_Ret SocketSrvCloseDatalink(ISOCKETSRV *piSocketSrv, IBase* piCaller);
MAE_Ret SocketSrvCloseDatalinkAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketCloseDatalinkCB pfnCloseDatalinkCb, void *pUserData);
MAE_Ret SocketSrvCreateSocket(ISOCKETSRV *piSocketSrv, IBase* piCaller,s32 af, s32 type, s32 protocol, SrvSocketHdl_t *phSocket);
MAE_Ret SocketSrvGetHostByName(ISOCKETSRV *piSocketSrv, IBase* piCaller, const u8 *name, struct hostent *host);
MAE_Ret SocketSrvGetHostByNameAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, const u8 *name, u8 *ti, struct hostent *host, SrvSocketGetHostByNameCB pfnGetHostByNameCb, void *pUserData);
MAE_Ret SocketSrvPingAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, const u8 *uIpAddress, u8 *ti, SrvSocketPingCB pfnPingCb, void *pUserData);
MAE_Ret SocketSrvSocketConnect(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const struct sockaddr *name, s32 namelen);
MAE_Ret SocketSrvSocketBind(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const struct sockaddr *name, s32 namelen);
MAE_Ret SocketSrvSocketConnectAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const struct sockaddr *name, s32 namelen, SrvSocketConnectCB pfnConnectCb, void *pUserData);
MAE_Ret SocketSrvSocketSend(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const u8  *buf, s32 len, s32 flags);
MAE_Ret SocketSrvSocketSendAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const u8  *buf, s32 len, s32 flags, SrvSocketSendCB pfnSendCb, void *pUserData);
MAE_Ret SocketSrvSocketRegRecvCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, s32 flags, SrvSocketRecvCB pfnRecvCb, void *pUserData);
MAE_Ret SocketSrvSocketRegRecvFromCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, s32 flags, SrvSocketRecvFromCB pfnRecvFromCb, void *pUserData);
MAE_Ret SocketSrvSocketClose(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket);
MAE_Ret SocketSrvSocketCloseAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, SrvSocketDestroySocketCB pfnCloseCb, void *pUserData);
MAE_Ret SocketSrvSocketSendTo(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const u8 *buf, s32 len, s32 flags, const struct sockaddr *to, s32 tolen);
MAE_Ret SocketSrvSocketSendToAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketHdl_t hSocket, const u8  *buf, s32 len, s32 flags, const struct sockaddr *to, s32 tolen, SrvSocketSendToCB pfnSendToCb, void *pUserData);
MAE_Ret SocketSrvSocketShutdown(ISOCKETSRV *piSocketSrv, IBase *piCaller, SrvSocketHdl_t hSocket, s32 how);
MAE_Ret SocketSrvSocketSuspend(ISOCKETSRV *piSocketSrv, IBase *piCaller, SrvSocketHdl_t hSocket);
MAE_Ret SocketSrvSocketResume(ISOCKETSRV *piSocketSrv, IBase *piCaller, SrvSocketHdl_t hSocket);
MAE_Ret SocketSrvGetSockOpt(ISOCKETSRV *piSocketSrv, IBase *piCaller, SrvSocketHdl_t hSocket, s32 level, s32 optname, s8* optval, s32* optlen);
MAE_Ret SocketSrvSetSockOpt(ISOCKETSRV *piSocketSrv, IBase *piCaller, SrvSocketHdl_t hSocket, s32 level, s32 optname, s8* optval, s32 optlen);
MAE_Ret SocketSrvCloseAllDatalinkAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearer_e eBearer, SrvSocketCloseAllDatalinkCB pfnCloseAllDatalinkCb, void *pUserData);
MAE_Ret SocketSrvCloseAllDatalink(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearer_e eBearer);
MAE_Ret SocketSrvQueryDatalinkAvailable(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketNetworkProfile_t *psNetworkProfile, u8 *pModId, bool *pAvailable);
MAE_Ret SocketSrvQueryBearerStatus(ISOCKETSRV *piSocketSrv, IBase* piCaller,SrvSocketBearerInfo_t *psBearerInfo, SrvSocketQueryBearerStatusInfo_t *psBearerStatusInfo);
MAE_Ret SocketSrvRegBearerStatusCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketBearerStatusCB pfnBearerStatusCb, void *pUserData);
MAE_Ret SocketSrvDeRegBearerStatusCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketBearerStatusCB pfnBearerStatusCb);
MAE_Ret SocketSrvRegNetworkStatusCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketNetworkStatusCB pfnNetworkStatusCb, void *pUserData);
MAE_Ret SocketSrvDeRegNetworkStatusCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketNetworkStatusCB pfnNetworkStatusCb);
MAE_Ret SocketSrvRegDataTrafficCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketTrafficStatusChangeCB pfnDataTrafficCb, void *pvUserData);
MAE_Ret SocketSrvDeRegDataTrafficCb(ISOCKETSRV *piSocketSrv, IBase* piCaller, SrvSocketTrafficStatusChangeCB pfnDataTrafficCb);
MAE_Ret SocketSrvQueryDataTrafficStatus(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *pBearerInfo, MservSocketTrafficStatus_t *psStatus);
MAE_Ret SocketSrvHasTraffic(SrvSocketTrafficStatus_t sStatus, boolean *pbHas);
MAE_Ret SocketSrvStatisticTotalRxBytesAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);
MAE_Ret SocketSrvStatisticTotalTxBytesAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);
MAE_Ret SocketSrvStatisticLastRxBytesAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);
MAE_Ret SocketSrvStatisticLastTxBytesAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);
MAE_Ret SocketSrvStatisticResetAllAsync(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticResetCB pfnStatisticResetCb);
MAE_Ret SocketSrvGetIPInfo(ISOCKETSRV *piSocketSrv, IBase* piCaller, MservSocketBearerInfo_t *pBearerInfo, const MservSocketIPInfo_t *cpsIPInfo);

#endif /* __MMI_SOCKETSRV_H__ */
