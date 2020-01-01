#ifndef __MS_SOCKET_RSP_ITF_H__
#define __MS_SOCKET_RSP_ITF_H__

#include "ms_socket_cmn.h"

void Mserv_create_datalink_rsp(s8 nRetCode, void *pUserData);
void Mserv_close_datalink_rsp(s8 nRetCode, void *pUserData);
void Mserv_close_all_datalink_rsp(s8 nRetCode, void *pUserData);
void Mserv_socket_gethostbyname_rsp(u8 ti, struct hostent *phost, void *pUserData);
void Mserv_socket_bind_rsp(SOCKET s, s8 result, void* pUserData);
void Mserv_socket_ping_rsp(u8 ti, s8 result, void* pUserData);
void Mserv_socket_connect_socket_rsp(SOCKET s, s8 result, void* pUserData);
void Mserv_socket_reg_recvcb_rsp(SOCKET s, u8 *buf, u_int len, void *pUserData, void *pLinkMsg);
void Mserv_socket_sync_recv_rsp(SOCKET s, u8 *buf, u_int len, void *pUserData, void *pLinkMsg);
void Mserv_socket_recv_rsp(SOCKET s, u8 *buf, u_int len, void *pUserData, void *pLinkMsg);
void Mserv_socket_sync_recvfrom_rsp(SOCKET s, u8 *buf, u_int len, struct sockaddr *from, int fromlen, void *pUserData, void *pLinkMsg);
void Mserv_socket_reg_recvfromcb_rsp(SOCKET s, u8 *buf, u_int len, struct sockaddr *from, int fromlen, void *pUserData, void *pLinkMsg);
void Mserv_socket_recvfrom_rsp(SOCKET s, u8 *buf, u_int len, struct sockaddr *from, int fromlen, void *pUserData, void *pLinkMsg);
void Mserv_socket_send_rsp(SOCKET s, s8 result, void* pUserData);
void Mserv_socket_sendto_rsp(SOCKET s, s8 result, void* pUserData);
void Mserv_socket_setsockopt_rsp(SOCKET s, s8 status, void* pUserData);
void Mserv_socket_getsockopt_rsp(SOCKET s, s32 level, s32 optname, s8* optval, s32 optlen, s8 status, void* pUserData);
void Mserv_socket_shutdown_rsp(SOCKET s, s8 status, void* pUserData);
void Mserv_socket_close_socket_rsp(SOCKET s, s8 result, void* pUserData);
void Mserv_socket_bearer_status_rsp(u32 uApId, Mserv_Callback_Info_t *CbInfo, void *pfnStatusCb, void *pvUserData, Mserv_socket_status_rsp_info_t *pinfo);
void Mserv_socket_network_status_rsp(s8 nRetCode, void *pUserData);
void Mserv_socket_data_traffic_status_rsp(MservSocketBearerInfo_t *psBearerInfo, MservSocketTrafficStatus_t sStatus, void *pvUserData);
void Mserv_socket_statistic_query_rsp(s8 nRetCode, u32 nBytes, void *pvReqMsg);
void Mserv_socket_statistic_reset_all_rsp(s8 nRetCode, void *pvReqMsg);

#endif/* __MS_SOCKET_RSP_ITF_H__ */
