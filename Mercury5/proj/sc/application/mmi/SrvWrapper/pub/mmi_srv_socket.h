/**
* @file    mmi_srv_socket.h
* @brief   
*          
*/

#ifndef __MMI_SRV_SOCKET_H__
#define __MMI_SRV_SOCKET_H__



#include "mmi_srv_client_commondefine.h"
#include "mmi_socketsrv.h"


/// socket related APIs
MAE_Ret SrvSocketCreateDatalinkAsync(SrvSocketNetworkProfile_t *psNetworkProfile, SrvSocketCreateDatalinkCB pfnSocketCreateDatalinkCb, void *pvUserData);
MAE_Ret SrvSocketDestroyDatalinkAsync(SrvSocketCloseDatalinkCB pfnSocketDestroyDatalinkCb, void *pvUserData);
MAE_Ret SrvSocketCreateSocket(s32 af,s32 type, s32 protocol, SrvSocketHdl_t *phSocket);
MAE_Ret SrvSocketConnectAsync(SrvSocketHdl_t hSocket, const struct sockaddr  *name, s32 namelen, SrvSocketConnectCB pfnSocketConnectCb, void *pvUserData);
MAE_Ret SrvSocketBind(SrvSocketHdl_t hSocket, const struct sockaddr  *name, s32 namelen);
MAE_Ret SrvSocketSendAsync(SrvSocketHdl_t hSocket, const u8  *buf, s32 len, s32 flags, SrvSocketSendCB pfnSocketSendCb, void *pvUserData);
MAE_Ret SrvSocketSendToAsync(SrvSocketHdl_t hSocket, const u8  *buf, s32 len, s32 flags, const struct sockaddr *to, s32 tolen, SrvSocketSendToCB pfnSendToCb, void *pvUserData);
MAE_Ret SrvSocketRegRecvCB(SrvSocketHdl_t hSocket, s32 flags, SrvSocketRecvCB pfnRecvCb, void *pvUserData);
MAE_Ret SrvSocketRegRecvFromCB(SrvSocketHdl_t hSocket, s32 flags, SrvSocketRecvFromCB pfnRecvFromCb, void *pvUserData);
MAE_Ret SrvSocketDestroySocket(SrvSocketHdl_t hSocket);
MAE_Ret SrvSocketDestroySocketAsync(SrvSocketHdl_t hSocket, SrvSocketDestroySocketCB pfnSocketDestroyCb, void *pvUserData);
MAE_Ret SrvSocketCloseAllDatalinkAsync(SrvSocketBearer_e eBearer, SrvSocketCloseAllDatalinkCB pfnSocketCloseAllCb, void *pvUserData);
MAE_Ret SrvSocketGetSockOpt(SrvSocketHdl_t hSocket, s32 level, s32 optname, s8* optval, s32* optlen);
MAE_Ret SrvSocketSetSockOpt(SrvSocketHdl_t hSocket, s32 level, s32 optname, s8* optval, s32 optlen);
MAE_Ret SrvSocketShutdown(SrvSocketHdl_t hSocket, s32 how);
MAE_Ret SrvSocketSuspend(SrvSocketHdl_t hSocket);
MAE_Ret SrvSocketResume(SrvSocketHdl_t hSocket);
MAE_Ret SrvSocketPingAsync(const s8 *sIpAddress, u8 *puTi, void *pvUserData, SrvSocketPingCB pfnPingCb);
MAE_Ret SrvSocketQueryBearerStatus(SrvSocketBearerInfo_t *psBearerInfo, SrvSocketQueryBearerStatusInfo_t *psBearerStatusInfo);
MAE_Ret SrvSocketRegBearerStatusListener(SrvSocketBearerStatusCB pfnBearerStatusCb, void *pvUserData);
MAE_Ret SrvSocketDeRegBearerStatusListener(SrvSocketBearerStatusCB pfnBearerStatusCb);
MAE_Ret SrvSocketRegNetworkStatusListener(SrvSocketNetworkStatusCB pfnNetworkStatusCb, void *pvUserData);
MAE_Ret SrvSocketDeRegNetworkStatusListener(SrvSocketNetworkStatusCB pfnNetworkStatusCb);
MAE_Ret SrvSocket_gethostbyname(const u8 *name, struct hostent *host);
MAE_Ret SrvSocket_gethostbyname_Async(const u8 *name, u8 *ti, struct hostent *host, SrvSocketGetHostByNameCB pfnGetHostByNameCb, void *pvUserData);
MAE_Ret SrvSocketQueryDatalinkAvailable(SrvSocketNetworkProfile_t *psNetworkProfile, u8 *pModId, u8 *pAvailable);
MAE_Ret SrvSocketQueryTrafficStatus(SrvSocketBearerInfo_t *pBearerInfo, SrvSocketTrafficStatus_t *psStatus);
MAE_Ret SrvSocketRegTrafficStatusChangeListener(SrvSocketTrafficStatusChangeCB pfnStatusChangeCb, void *pvUserData);
MAE_Ret SrvSocketDeRegTrafficStatusChangeListener(SrvSocketTrafficStatusChangeCB pfnStatusChangeCb);
MAE_Ret SrvSocketHasTraffic(SrvSocketTrafficStatus_t sStatus, boolean *pbHas);

/** SrvSocketStatasticTotalTxBytesAsync
@brief  The interface is used to query total transmit(tx) bytes on specific bearer.
        TCP/IP header size is also included.

@param[in]      psBearerInfo            Bearer information.
@param[in]      pvUserData              Indicate the user data in the parameter list of the response callback             
@param[out]     pnTi                    Transaction Id
@param[in]      pfnStatisticQueryCb     Response callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_OUT_OF_MEMORY          Can't execute the operation due to out of memory.
@retval  MAE_RET_BAD_PARAM              If incoming parameter is invalid.
@retval  MAE_RET_FAILED                 If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support statistic functions. 
*/
MAE_Ret SrvSocketStatisticTotalTxBytesAsync(SrvSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);

/** SrvSocketStatisticTotalRxBytesAsync
@brief  The interface is used to query total received(rx) bytes on specific bearer.
        TCP/IP header size is also included.

@param[in]      psBearerInfo            Bearer information.
@param[in]      pvUserData              Indicate the user data in the parameter list of the response callback             
@param[out]     pnTi                    Transaction Id
@param[in]      pfnStatisticQueryCb     Response callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_OUT_OF_MEMORY          Can't execute the operation due to out of memory.
@retval  MAE_RET_BAD_PARAM              If incoming parameter is invalid.
@retval  MAE_RET_FAILED                 If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support statistic functions. 
*/
MAE_Ret SrvSocketStatisticTotalRxBytesAsync(SrvSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);

/** SrvSocketStatisticLastTxBytesAsync
@brief  The interface is used to query last transmit(tx) bytes on specific bearer.
        TCP/IP header size is also included.

@param[in]      psBearerInfo            Bearer information.
@param[in]      pvUserData              Indicate the user data in the parameter list of the response callback             
@param[out]     pnTi                    Transaction Id
@param[in]      pfnStatisticQueryCb     Response callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_OUT_OF_MEMORY          Can't execute the operation due to out of memory.
@retval  MAE_RET_BAD_PARAM              If incoming parameter is invalid.
@retval  MAE_RET_FAILED                 If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support statistic functions. 
*/
MAE_Ret SrvSocketStatisticLastTxBytesAsync(SrvSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);

/** SrvSocketStatisticTotalRxBytesAsync
@brief  The interface is used to query last received(rx) bytes on specific bearer.
        TCP/IP header size is also included.

@param[in]      psBearerInfo            Bearer information.
@param[in]      pvUserData              Indicate the user data in the parameter list of the response callback             
@param[out]     pnTi                    Transaction Id
@param[in]      pfnStatisticQueryCb     Response callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_OUT_OF_MEMORY          Can't execute the operation due to out of memory.
@retval  MAE_RET_BAD_PARAM              If incoming parameter is invalid.
@retval  MAE_RET_FAILED                 If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support statistic functions. 
*/
MAE_Ret SrvSocketStatisticLastRxBytesAsync(SrvSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb);


/** SrvSocketStatisticTotalRxBytesAsync
@brief  The interface is used to reset statistic data bytes on specific bearer

@param[in]      psBearerInfo            Bearer information.
@param[in]      pvUserData              Indicate the user data in the parameter list of the response callback             
@param[out]     pnTi                    Transaction Id
@param[in]      pfnStatisticQueryCb     Response callback

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_OUT_OF_MEMORY          Can't execute the operation due to out of memory.
@retval  MAE_RET_BAD_PARAM              If incoming parameter is invalid.
@retval  MAE_RET_FAILED                 If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support statistic functions. 
*/
MAE_Ret SrvSocketStatisticResetAllAsync(SrvSocketBearerInfo_t *psBearerInfo, void *pvUserData, u8 *pnTi, SrvSocketStatisticResetCB pfnStatisticResetCb);


MAE_Ret SrvSocketGetIPInfo(SrvSocketBearerInfo_t *pBearerInfo, const MservSocketIPInfo_t *cpsIPInfo);

/// Utility
u32 SrvSocket_htonl(u32 hostlong);
u16 SrvSocket_htons(u16 hostshort);
u32 SrvSocket_inet_addr(const s8 *cp);
void SrvSocket_inet_ntoa(struct in_addr in, s8 *ipstr);
s32 SrvSocket_inet_aton(const s8 *s, struct in_addr *addr);
u32 SrvSocket_ntohl(u32 netlong);
u16 SrvSocket_ntohs(u16 netshort);
struct hostent *SrvSocket_gethostbyaddr(const u8  *addr, s32 len, s32 type);
struct hostent *SrvSocketAllocHostent(void);
void SrvSocketFreeHostent(struct hostent *phost);
MAE_Ret SrvSocket_gethostname(u8 *name, s32 namelen);
struct servent *SrvSocket_getservbyport(s32 port, const u8  *proto);
struct servent *SrvSocket_getservbyname(const u8 *name, const u8 *proto);
struct protoent *SrvSocket_getprotobynumber(s32 proto);
struct protoent *SrvSocket_getprotobyname(const u8 *name);
const MservSocketIPInfo_t *SrvSocketAllocIPInfo(void);
void SrvSocketFreeIPInfo(const MservSocketIPInfo_t *cpsIPInfo);

#endif //__MMI_SRV_SOCKET_H__
