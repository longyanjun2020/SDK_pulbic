/**
*
* @file    ms_sdk.h
* @brief   This file provide the message parser for socket related msg
* @author  Edward.Yeh
* @version $Id$
*
*/


#ifndef __MS_SDK_H__
#define __MS_SDK_H__

#include "ven_common_def.h"

/// Now, create socket can be created in caller task.
/// We needn't handle create socket request in mserv task.
/// void ven_socket_craete_socket_req(ven_msg_t MsgID, vm_msg_t *pMessage);

void ven_socket_connect_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_send_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_sendto_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_recv_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_recvfrom_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_regRecvCB_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_regRecvFromCB_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_send_receive_ready_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_setsockopt_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_getsockopt_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_shutdown_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_socket_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_gethostbyname_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_ping_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_query_datalink_available_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_ping_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_create_datalink_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_datalink_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_regStatusCB_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_deregStatusCB_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_create_datalink_ex_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_datalink_ex_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_all_datalinks_ex_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_reg_statuscb_ex_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_dereg_statuscb_ex_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_bind_req(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__MS_SDK_H__
