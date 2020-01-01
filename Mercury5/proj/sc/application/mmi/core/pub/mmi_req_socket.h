/**
 * @file    mmi_req_socket.h
* @brief   The file handles all the message request function to MServ task
* @author  li-wei.cheng
 * 
 */
#ifndef __MMI_REQ_SOCKET_H__
#define __MMI_REQ_SOCKET_H__

#include "ms_socket_cmn.h"
#include "mmi_mae_common_def.h"
#include "mmi_srv_socket.h"

MAE_Ret mmi_socket_create_datalink_req(u32 uAppId, SrvSocketNetworkProfile_t *psNetworkProfile);
MAE_Ret mmi_socket_create_datalink_async_req(u32 uAppId, SrvSocketNetworkProfile_t *psNetworkProfile, SrvSocketCreateDatalinkCB pfnCreateDatalinkCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_close_datalink_req(u32 uAppId);
MAE_Ret mmi_socket_close_datalink_async_req(u32 uAppId, SrvSocketCloseDatalinkCB pfnCloseDatalinkCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_close_all_datalink_req(u32 uAppId, MservSocketBearer_e eBearer);
MAE_Ret mmi_socket_close_all_datalink_async_req(u32 uAppId, MservSocketBearer_e eBearer, SrvSocketCloseAllDatalinkCB pfnCloseAllDatalinkCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_gethostbyname_req(u32 uAppId, const u8 *name, struct hostent *host);
MAE_Ret mmi_socket_gethostbyname_async_req(u32 uAppId, const u8 *name, u8 *ti, struct hostent *host, SrvSocketGetHostByNameCB pfnGetHostByNameCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_ping_async_req(u32 uAppId, const u8 *uIpAddress, u8 *ti, SrvSocketPingCB pfnPingCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_bind_socket_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const struct sockaddr *name, s32 namelen);
MAE_Ret mmi_socket_connect_socket_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const struct sockaddr *name, s32 namelen);
MAE_Ret mmi_socket_connect_socket_async_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const struct sockaddr *name, s32 namelen, SrvSocketConnectCB pfnConnectSocketCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_send_socket_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const u8  *buf, s32 len, s32 flags);
MAE_Ret mmi_socket_send_socket_async_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const u8  *buf, s32 len, s32 flags, SrvSocketSendCB pfnSendSocketCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_reg_recvcb_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, s32 flags, SrvSocketRecvCB pfnRecvCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_reg_recvfromcb_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, s32 flags, SrvSocketRecvFromCB pfnRecvFromCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_close_socket_req(u32 uAppId, Mserv_socket_t *psSocketWrapper);
MAE_Ret mmi_socket_close_socket_async_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, SrvSocketDestroySocketCB pfnCloseSocketCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_sendto_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const u8  *buf, s32 len, s32 flags, const struct sockaddr *to, s32 tolen);
MAE_Ret mmi_socket_sendto_async_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, const u8 *buf, s32 len, s32 flags, const struct sockaddr *to, s32 tolen, SrvSocketSendToCB pfnSendToCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_shutdown_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, s32 how);
MAE_Ret mmi_socket_suspend_req(u32 uAppId, Mserv_socket_t *psSocketWrapper);
MAE_Ret mmi_socket_resume_req(u32 uAppId, Mserv_socket_t *psSocketWrapper);
MAE_Ret mmi_socket_getsockopt_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, s32 level, s32 optname, s8* optval, s32* optlen);
MAE_Ret mmi_socket_setsockopt_req(u32 uAppId, Mserv_socket_t *psSocketWrapper, s32 level, s32 optname, s8* optval, s32 optlen);
MAE_Ret mmi_socket_reg_bearer_status_req(u32 uAppId, SrvSocketBearerStatusCB pfnBearerStatusCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_dereg_bearer_status_req(u32 uAppId, SrvSocketBearerStatusCB pfnBearerStatusCb);
MAE_Ret mmi_socket_query_bearer_status_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, SrvSocketQueryBearerStatusInfo_t *psBearerStatusInfo);
MAE_Ret mmi_socket_reg_network_status_req(u32 uAppId, SrvSocketNetworkStatusCB pfnNetworkStatusCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_dereg_network_status_req(u32 uAppId, SrvSocketNetworkStatusCB pfnNetworkStatusCb);
MAE_Ret mmi_socket_query_datalink_available_req(u32 uAppId, SrvSocketNetworkProfile_t *psNetworkProfile, u8 *pModId, bool *pAvailable);
MAE_Ret mmi_socket_reg_data_traffic_status_cb_req(u32 uAppId, SrvSocketTrafficStatusChangeCB pfnDataTrafficCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_dereg_data_traffic_status_cb_req(u32 uAppId, SrvSocketTrafficStatusChangeCB pfnDataTrafficCb);
MAE_Ret mmi_socket_query_data_traffic_status_req(u32 uAppId, MservSocketBearerInfo_t *pBearerInfo, MservSocketTrafficStatus_t *psStatus);
MAE_Ret mmi_socket_statistic_query_total_tx_bytes_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_statistic_query_total_rx_bytes_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_statistic_query_last_tx_bytes_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_statistic_query_last_rx_bytes_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, u8 *pnTi, SrvSocketStatisticQueryCB pfnStatisticQueryCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_statistic_reset_all_req(u32 uAppId, MservSocketBearerInfo_t *psBearerInfo, u8 *pnTi, SrvSocketStatisticResetCB pfnStatisticResetCb, u32 uCbUserData, void *pfnCBWrapper, u32 uCbWrapperUserData);
MAE_Ret mmi_socket_get_ip_info_req(u32 uAppId, MservSocketBearerInfo_t *pBearerInfo, const MservSocketIPInfo_t *cpIPInfo);

#endif /* __MMI_REQ_SOCKET_H__ */
