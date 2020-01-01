#ifndef __MS_SOCKET_MSG_H__
#define __MS_SOCKET_MSG_H__

#include "ms_socket_msg_def.h"

typedef union
{
	Mserv_socket_create_datalink_ex_req_t Mserv_Mic_Srv_CreateDatalinkReq;
	Mserv_socket_create_datalink_ex_rsp_t Mserv_Mic_Srv_CreateDatalinkRsp;
    Mserv_socket_close_datalink_ex_req_t Mserv_Mic_Srv_CloseDatalinkReq;
    Mserv_socket_close_datalink_ex_rsp_t Mserv_Mic_Srv_CloseDatalinkRsp;
    Mserv_socket_ping_req_t Mserv_Mic_Srv_PingReg;
    Mserv_socket_ping_rsp_t Mserv_Mic_Srv_PingRsp;
    Mserv_socket_gethostbyname_req_t Mserv_Mic_Srv_GetHostByNameReq;
    Mserv_socket_gethostbyname_rsp_t Mserv_Mic_Srv_GetHostByNameRsp;
    Mserv_socket_bind_req_t Mserv_Mic_Srv_BindSocketReq;
    Mserv_socket_connect_req_t Mserv_Mic_Srv_ConnectSocketReq;
    Mserv_socket_connect_rsp_t Mserv_Mic_Srv_ConnectSocketRsp;
    Mserv_socket_regRecvCB_req_t Mserv_Mic_Srv_RegRecvCbReq;
    Mserv_socket_recv_notify_t   Mserv_Mic_Srv_RecvNotify;
    Mserv_socket_regRecvFromCB_req_t Mserv_Mic_Srv_RegRecvFromCbReq;
    Mserv_socket_recvfrom_notify_t   Mserv_Mic_Srv_RecvFromNotify;
    Mserv_socket_send_req_t Mserv_Mic_Srv_SendReq;
    Mserv_socket_send_rsp_t Mserv_Mic_Srv_SendRsp;
    Mserv_socket_closesocket_req_t Mserv_Mic_Srv_CloseSocketReq;
    Mserv_socket_closesocket_rsp_t Mserv_Mic_Srv_CloseSocketRsp;
    Mserv_socket_sendto_req_t Mserv_Mic_Srv_SendToReq;
    Mserv_socket_sendto_rsp_t Mserv_Mic_Srv_SendToRsp;
    Mserv_socket_shutdown_req_t Mserv_Mic_Srv_ShutdownReq;
    Mserv_socket_receiveReady_ind_t Mserv_Mic_Srv_RecvReadyInd;
    Mserv_socket_getsockopt_req_t Mserv_Mic_Srv_GetSockOptReq;
    Mserv_socket_setsockopt_req_t Mserv_Mic_Srv_SetSockOptReq;
    Mserv_socket_close_all_datalinks_ex_req_t Mserv_Mic_Srv_CloseAllDatalinkReq;
    Mserv_socket_close_all_datalinks_ex_rsp_t Mserv_Mic_Srv_CloseAllDatalinkRsp;
    Mserv_socket_regBearerStatusCB_req_t Mserv_Mic_Srv_RegBearerStatusCbReq;
    Mserv_socket_deregBearerStatusCB_req_t Mserv_Mic_Srv_DeRegBearerStatusCbReq;
    Mserv_socket_regNetworkStatusCB_req_t Mserv_Mic_Srv_RegNetworkStatusCbReq;
    Mserv_socket_deregNetworkStatusCB_req_t Mserv_Mic_Srv_DeRegNetworkStatusCbReq;
    Mserv_socket_cmd_timeout_ind_t Mserv_Mic_Srv_Cmd_Timeout_Ind;
    Mserv_socket_query_datalink_req_t Mserv_Mic_Srv_QueryDatalinkAvailableReq;
    Mserv_socket_bearer_status_ind_t Mserv_Mic_Srv_Ind;
    Mserv_socket_data_traffic_status_ind_t Mserv_Mic_Srv_DataTrafficStatusChange;
    Mserv_socket_regDataTrafficStatusCB_req_t Mserv_Mic_Srv_RegDataTrafficCb;
    Mserv_socket_deregDataTrafficStatusCB_req_t Mserv_Mic_Srv_DeRegDataTrafficCb;
    Mserv_socket_queryDataTrafficStatus_req_t Mserv_Mic_Srv_QueryDataTrafficStatus;
    Mserv_socket_statistic_query_req_t Mserv_Mic_Srv_StatisticQueryReq;
    Mserv_socket_statistic_query_rsp_t Mserv_Mic_Srv_StatisticQueryRsp;
    Mserv_socket_statistic_reset_all_req_t Mserv_Mic_Srv_StatisticResetAllReq;
    Mserv_socket_statistic_reset_all_rsp_t Mserv_Mic_Srv_StatisticResetAllRsp;
    Mserv_socket_getIPInfo_req Mserv_Mic_Srv_GetIPInfo;
}vm_msgBody_t;

#endif/* __MS_SOCKET_MSG_H__ */
