/**
 *
 * @file    ven_socket_stmsg.h
 * @brief   This file defines the structures for the socket module message
 * @author  Edward.Yeh
 * @version $Id: ven_socket_stmsg.h 29063 2009-04-22 05:25:36Z sata.yeh $
 *
 */

#ifndef __VEN_SOCKET_STMSG_H__
#define __VEN_SOCKET_STMSG_H__

#include "ven_setting_stmsg.h"
#include "ven_socket.h"
#include "ms_socket_msg_def.h"

#define VEN_HOSTNAME_LEN MSERV_HOSTNAME_LEN

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_QUERY_DATALINK_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_query_datalink_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef Mserv_socket_query_datalink_req_t iVen_socket_query_datalink_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETHOSTBYNAME_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : gethostbyname                                               */
/*                                                                          */
/*  Structure : iVen_socket_gethostbyname_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check callback function's prototype
/// ven_socket_gethostbyname_cbfunc_t/MservSocketGetHostByNameCB
typedef Mserv_socket_gethostbyname_req_t iVen_socket_gethostbyname_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETHOSTBYNAME_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : gethostbyname                                               */
/*                                                                          */
/*  Structure : iVen_socket_gethostbyname_rsp_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check callback function's prototype
/// ven_socket_gethostbyname_cbfunc_t/MservSocketGetHostByNameCB
typedef Mserv_socket_gethostbyname_rsp_t iVen_socket_gethostbyname_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATESOCKET_REQ                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_createsocket_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mservn_socket_createsocket_req_t iVen_socket_createsocket_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATESOCKET_RSP                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_createsocket_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_createsocket_rsp_t iVen_socket_createsocket_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSESOCKET_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_closesocket_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketCloseSocketCB/ven_socket_closesocket_cbfunc_t
typedef Mserv_socket_closesocket_req_t iVen_socket_closesocket_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSESOCKET_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_close_socket_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketCloseSocketCB/ven_socket_closesocket_cbfunc_t
typedef Mserv_socket_closesocket_rsp_t iVen_socket_closesocket_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CONNECT_REQ                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_connect_req_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketConnectCB/ven_socket_connect_cbfunc_t
typedef Mserv_socket_connect_req_t iVen_socket_connect_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CONNECT_RSP                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_connect_rsp_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketConnectCB/ven_socket_connect_cbfunc_t
typedef Mserv_socket_connect_rsp_t iVen_socket_connect_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REGRECVCB_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regRecvCB_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketRecvCB/ven_socket_recv_cbfunc_t
typedef Mserv_socket_regRecvCB_req_t iVen_socket_regRecvCB_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECV_NOTIFY                                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recv_notify_t                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketRecvCB/ven_socket_recv_cbfunc_t
typedef Mserv_socket_recv_notify_t iVen_socket_recv_notify_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REGRECVFROMCB_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regRecvFromCB_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketRecvFromCB/ven_socket_recvfrom_cbfunc_t
typedef Mserv_socket_regRecvFromCB_req_t iVen_socket_regRecvFromCB_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECVFROM_NOTIFY                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recvfrom_notify_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketRecvFromCB/ven_socket_recvfrom_cbfunc_t
typedef Mserv_socket_recvfrom_notify_t iVen_socket_recvfrom_notify_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SEND_REQ                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_send_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketSendCB/ven_socket_send_cbfunc_t
typedef Mserv_socket_send_req_t iVen_socket_send_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SEND_RSP                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_send_rsp_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketSendCB/ven_socket_send_cbfunc_t
typedef Mserv_socket_send_rsp_t iVen_socket_send_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SENDTO_REQ                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_sendto_req_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketSendToCB/ven_socket_sendto_cbfunc_t
typedef Mserv_socket_sendto_req_t iVen_socket_sendto_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SENDTO_RSP                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_sendto_rsp_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback
/// MservSocketSendToCB/ven_socket_sendto_cbfunc_t
typedef Mserv_socket_sendto_rsp_t iVen_socket_sendto_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATE_DATALINK_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : create_datalink                                             */
/*                                                                          */
/*  Structure : iVen_socket_create_datalink_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback & return code
/// MservSocketCreateDatalinkCB/ven_socket_create_datalink_cbfunc_t
typedef Mserv_socket_create_datalink_req_t iVen_socket_create_datalink_req_t;
typedef Mserv_socket_create_datalink_ex_req_t iVen_socket_create_datalink_ex_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CREATE_DATALINK_RSP                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : create_datalink                                             */
/*                                                                          */
/*  Structure : iVen_socket_create_datalink_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback & return code
/// MservSocketCreateDatalinkCB/ven_socket_create_datalink_cbfunc_t
typedef Mserv_socket_create_datalink_rsp_t iVen_socket_create_datalink_rsp_t;
typedef iVen_socket_create_datalink_rsp_t iVen_socket_create_datalink_ex_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSE_DATALINK_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     : close_datalink                                              */
/*                                                                          */
/*  Structure : iVen_socket_close_datalink_req_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback & return code
/// MservSocketCloseDatalinkCB/ven_socket_close_datalink_cbfunc_t
typedef Mserv_socket_close_datalink_req_t iVen_socket_close_datalink_req_t;
typedef iVen_socket_close_datalink_req_t iVen_socket_close_datalink_ex_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSE_DATALINK_RSP                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MSERV to Vendor task                                        */
/*                                                                          */
/*  Scope     : close_datalink                                              */
/*                                                                          */
/*  Structure : iVen_socket_close_datalink_rsp_t                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type & callback & return code
/// MservSocketCloseDatalinkCB/ven_socket_close_datalink_cbfunc_t
typedef Mserv_socket_close_datalink_rsp_t iVen_socket_close_datalink_rsp_t;
typedef iVen_socket_close_datalink_rsp_t iVen_socket_close_datalink_ex_rsp_t;

/// check socket's type & callback & return code & bearer
/// MservSocketCloseAllDatalinkCB/ven_socket_close_all_datalinks_ex_cbfunc_t
typedef Mserv_socket_close_all_datalinks_ex_rsp_t iVen_socket_close_all_datalinks_ex_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECEIVE_READY_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_receiveReady_req_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_receiveReady_ind_t iVen_socket_receiveReady_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECV_REQ                                   */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recv_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_recv_req_t iVen_socket_recv_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_RECVFROM_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_recvfrom_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_recvfrom_req_t iVen_socket_recvfrom_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SETSOCKOPT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_setsockopt_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_setsockopt_req_t iVen_socket_setsockopt_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_GETSOCKOPT_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_getsockopt_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_getsockopt_req_t iVen_socket_getsockopt_req_t;

/****************************************************************************/
/*  Message :       I_VEN_SOCKET_SHUTDOWN_REQ                               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_shutdown_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check socket's type
typedef Mserv_socket_shutdown_req_t iVen_socket_shutdown_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_REG_STATUS_CB_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_regStatusCB_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check callback & return code
/// MservSocketStatusCB/ven_socket_status_cbfunc_t
typedef Mserv_socket_regNetworkStatusCB_req_t iVen_socket_regStatusCB_req_t;
typedef iVen_socket_regStatusCB_req_t iVen_socket_deregStatusCB_req_t;

/// check callback & return code
/// MservSocketStatusExCB/ven_socket_status_cbfunc_ex_t
typedef Mserv_socket_regBearerStatusCB_req_t iVen_socket_regStatusCB_ex_req_t;

/// check callback & return code
/// MservSocketStatusExCB/ven_socket_status_cbfunc_ex_t
typedef Mserv_socket_deregBearerStatusCB_req_t iVen_socket_deregStatusCB_ex_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_STATUS_INDICATION                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_status_indication_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check callback & return code
/// MservSocketStatusCB/ven_socket_status_cbfunc_t
typedef Mserv_socket_network_status_indication_t iVen_socket_status_indication_t;

/// double check
/// check callback & return code & ven_socket_status_rsp_info_ex_t
/// MservSocketStatusExCB/ven_socket_status_cbfunc_ex_t
typedef Mserv_socket_bearer_status_indication_t iVen_socket_status_indication_ex_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_CLOSE_ALL_DATALINKS                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_close_all_datalinks_ex_req_t                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
/// check bearer type & return code
/// MservSocketCloseAllDatalinkCB/ven_socket_close_all_datalinks_ex_cbfunc_t
typedef Mserv_socket_close_all_datalinks_ex_req_t iVen_socket_close_all_datalinks_ex_req_t;


/****************************************************************************/
/*  Message :       I_VEN_SOCKET_PING                                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MSERV                                        */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_socket_ping_req_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

/// check callback & return code
/// MservSocketPingCB/ven_socket_ping_cbfunc_t
typedef Mserv_socket_ping_req_t iVen_socket_ping_req_t;
typedef Mserv_socket_ping_rsp_t iVen_socket_ping_rsp_t;

typedef Mserv_socket_bind_req_t iVen_socket_bind_req_t;

#endif //__VEN_SOCKET_STMSG_H__

