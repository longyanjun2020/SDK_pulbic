/* reference ven_primitem.h */
/* Primitives send FROM MServ */
#define MS_OUT_PRIM_ITEMS \

/* Primitives send TO MServ */
#define MS_IN_PRIM_ITEMS \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTBYNAME_REQ,          ven_socket_gethostbyname_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATESOCKET_REQ,           NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSESOCKET_REQ,            ven_socket_close_socket_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CONNECT_REQ,                ven_socket_connect_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SEND_REQ,                   ven_socket_send_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SENDTO_REQ,                 ven_socket_sendto_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REGRECVCB_REQ,              ven_socket_regRecvCB_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REGRECVFROMCB_REQ,          ven_socket_regRecvFromCB_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECEIVE_READY_IND,          ven_socket_send_receive_ready_ind), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECV_REQ,                   ven_socket_recv_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECVFROM_REQ,               ven_socket_recvfrom_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_REQ,        ven_socket_create_datalink_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_EX_REQ,     ven_socket_create_datalink_ex_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_REQ,         ven_socket_close_datalink_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_EX_REQ,      ven_socket_close_datalink_ex_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_ALL_DATALINKS_EX_REQ, ven_socket_close_all_datalinks_ex_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REG_STATUS_CB_REQ,          ven_socket_regStatusCB_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_DEREG_STATUS_CB_REQ,        ven_socket_deregStatusCB_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REG_STATUS_CB_EX_REQ,       ven_socket_reg_statuscb_ex_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_DEREG_STATUS_CB_EX_REQ,     ven_socket_dereg_statuscb_ex_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SETSOCKOPT_REQ,             ven_socket_setsockopt_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSOCKOPT_REQ,             ven_socket_getsockopt_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SHUTDOWN_REQ,               ven_socket_shutdown_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_HTONL_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_HTONS_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_ADDR_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_NTOA_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_ATON_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_NTOHL_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_NTOHS_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTBYADDR_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTNAME_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSERVBYPORT_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSERVBYNAME_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETPROTOBYNUMBER_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETPROTOBYNAME_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_QUERY_DATALINK_REQ,         ven_socket_query_datalink_available_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_BIND_REQ,                   ven_socket_bind_req), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_PING_REQ,                   ven_socket_ping_req), \

#define SOCKET_MSG_START I_VEN_SOCKET_GETHOSTBYNAME_REQ
#define SOCKET_MSG_END I_VEN_SOCKET_PING_REQ

#define MS_IN_PRIM_SRV_ITEMS    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CREATE_DATALINK_REQ, _Mserv_socket_srv_create_datalink_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_DATALINK_REQ, _Mserv_socket_srv_close_datalink_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_GETHOSTBYNAME_REQ, _Mserv_socket_srv_gethostbyname_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CONNECT_REQ, _Mserv_socket_srv_connect_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SEND_REQ, _Mserv_socket_srv_send_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SENDTO_REQ, _Mserv_socket_srv_sendto_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_RECV_REQ, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_RECV_NOTIFY, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_REG_RECVCB_REQ, _Mserv_socket_srv_reg_recvcb_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_RECVFROM_REQ, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_RECVFROM_NOTIFY, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_REG_RECVFROMCB_REQ, _Mserv_socket_srv_reg_recvfromcb_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SETSOCKOPT_REQ, _Mserv_socket_srv_setsockopt_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_GETSOCKOPT_REQ, _Mserv_socket_srv_getsockopt_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SHUTDOWN_REQ, _Mserv_socket_srv_shutdown_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_REQ, _Mserv_socket_srv_close_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_RECV_READY_REQ, _Mserv_socket_srv_recv_ready_req_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_ALL_DATALINK_REQ, _Mserv_socket_srv_close_all_datalink_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_QUERY_BEARER_STATUS_REQ, _Mserv_socket_srv_query_bearer_status_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_REG_BEARER_STATUS_CB_REQ, _Mserv_socket_srv_reg_bearer_status_cb_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_DEREG_BEARER_STATUS_CB_REQ, _Mserv_socket_srv_dereg_bearer_status_cb_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_REG_NETWORK_STATUS_CB_REQ, _Mserv_socket_srv_reg_network_status_cb_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_DEREG_NETWORK_STATUS_CB_REQ, _Mserv_socket_srv_dereg_network_status_cb_req_hdlr),    \
	MAKE_PRIM_ITEM(I_MSERV_SOCKET_BEARER_STATUS_CHANGE_IND, _Mserv_socket_srv_bearerstatuschange_ind_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_BIND_REQ, _Mserv_socket_srv_bind_req_hdlr),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_PING_REQ, _Mserv_socket_srv_ping_req_hdlr),	\
	MAKE_PRIM_ITEM(I_MSERV_SOCKET_COMMAND_TIMEOUT_INDICATION, _Mserv_socket_srv_cmd_timeout_ind_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_QUERY_DATALINK_REQ, _Mserv_socket_srv_query_datalink_req_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_REG_DATA_TRAFFIC_CB_REQ, _Mserv_socket_srv_RegDataTrafficListener_req_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_DE_REG_DATA_TRAFFIC_CB_REQ, _Mserv_socket_srv_DeRegDataTrafficListener_req_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_QUREY_DATA_TRAFFIC_REQ, _Mserv_socket_srv_QueryDataTraffi_req_hdlr), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_DATA_TRAFFIC_PERIODIC_CHECK_IND, _Mserv_socket_srv_DataTrafficPeriodicChecker_ind_hdlr),  \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_STATISTIC_QUERY_REQ, _Mserv_socket_srv_StatisticQuery_req_hdlr),  \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_STATISTIC_RESET_ALL_REQ, _Mserv_socket_srv_StatisticResetAll_req_hdlr),  \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_GET_IP_INFO_REQ, _Mserv_socket_srv_get_ip_info_req_hdlr),  \

#define MS_OUT_PRIM_SRV_ITEMS    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CREATE_DATALINK_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_DATALINK_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_GETHOSTBYNAME_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CONNECT_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SEND_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_SENDTO_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_CLOSE_ALL_DATALINK_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_BEARER_STATUS_INDICATION, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_NETWORK_STATUS_INDICATION, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_PING_RSP, NULL), \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_DATA_TRAFFIC_STATUS_CHANGE_IND, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_STATISTIC_QUERY_RSP, NULL),    \
    MAKE_PRIM_ITEM(I_MSERV_SOCKET_STATISTIC_RESET_ALL_RSP, NULL),    \


#define SOCKET_SRV_START I_MSERV_SOCKET_CREATE_DATALINK_REQ
#define SOCKET_SRV_END   I_MSERV_SOCKET_LAST


