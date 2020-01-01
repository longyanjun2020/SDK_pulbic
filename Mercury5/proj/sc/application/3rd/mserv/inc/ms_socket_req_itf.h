#ifndef __MS_SOCKET_REQ_ITF_H__
#define __MS_SOCKET_REQ_ITF_H__

#include "ms_prim.hc"
#include "ms_socket_cmn.h"
#include "ms_socket_msg_def.h"

typedef void (*MservWrapperCB)(u32 UserData, u32 RspData);

u32  Mserv_AllocSem(void);
bool Mserv_check_appid(u32 uAppId);
void Mserv_FreeSem(u32 uSemId);
void Mserv_fill_sync_struct(u32 uAppId, Mserv_AsyncReq_BodyBase_t *psSyncStruct, u32 uSemId);
void Mserv_fill_async_struct(u32 uAppId, Mserv_AsyncReq_BodyBase_t *psASyncStruct, void *pfnAsyncCb, u32 uUserData);

void Mserv_create_datalink_req(Mserv_socket_create_datalink_ex_req_t *psReq);
void Mserv_close_datalink_req(Mserv_socket_close_datalink_req_t *psReq);
void Mserv_gethostbyname_req(Mserv_socket_gethostbyname_req_t *psReq, u8 *ti);
void Mserv_ping_req(Mserv_socket_ping_req_t *psReq, u8 *ti);
void Mserv_socket_reg_recvcb_req(Mserv_socket_regRecvCB_req_t *psReq);
void Mserv_socket_reg_recvfromcb_req(Mserv_socket_regRecvFromCB_req_t *psReq);
void Mserv_socket_bind_req(Mserv_socket_bind_req_t *psReq);
void Mserv_socket_connect_req(Mserv_socket_connect_req_t *psReq);
void Mserv_socket_send_req(Mserv_socket_send_req_t *psReq);
void Mserv_socket_close_req(Mserv_socket_closesocket_req_t *psReq);
void Mserv_socket_sendto_req(Mserv_socket_sendto_req_t *psReq);
void Mserv_socket_shutdown_req(Mserv_socket_shutdown_req_t *psReq);
void Mserv_socket_getsockopt_req(Mserv_socket_getsockopt_req_t *psReq);
void Mserv_socket_setsockopt_req(Mserv_socket_setsockopt_req_t *psReq);
void Mserv_close_all_datalink_req(Mserv_socket_close_all_datalinks_ex_req_t *psReq);
void Mserv_socket_query_bearer_Status_req(Mserv_socket_query_bearer_status_req *psReq); 
void Mserv_socket_reg_bearerstatuscb_req(Mserv_socket_regBearerStatusCB_req_t *psReq);
void Mserv_socket_dereg_bearerstatuscb_req(Mserv_socket_deregBearerStatusCB_req_t *psReq);
void Mserv_socket_reg_networkstatuscb_req(Mserv_socket_regNetworkStatusCB_req_t *psReq);
void Mserv_socket_dereg_networkstatuscb_req(Mserv_socket_deregNetworkStatusCB_req_t *psReq);
void Mserv_query_datalink_available_req(Mserv_socket_query_datalink_req_t *psReq);
void Mserv_socket_reg_data_traffic_cb_req(Mserv_socket_regDataTrafficStatusCB_req_t *psReq);
void Mserv_socket_dereg_data_traffic_cb_req(Mserv_socket_deregDataTrafficStatusCB_req_t *psReq);
void Mserv_socket_query_data_traffic_status_req(Mserv_socket_queryDataTrafficStatus_req_t *psReq);
void Mserv_socket_statistic_query_req(Mserv_socket_statistic_query_req_t *psReq, u8 *pnTi);
void Mserv_socket_statistic_reset_all_req(Mserv_socket_statistic_reset_all_req_t *psReq, u8 *pnTi);
void Mserv_socket_get_ip_info_req(Mserv_socket_getIPInfo_req *psReq);
#endif/* __MS_SOCKET_REQ_ITF_H__ */
