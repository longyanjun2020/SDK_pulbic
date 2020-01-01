/**
*
* @file    ven_socket_msg_parser.h
* @brief   This file provide the message parser for socket related msg
* @author  Edward.Yeh
* @version $Id: ven_socket_msg_parser.h 29063 2009-04-22 05:25:36Z sata.yeh $
*
*/


#ifndef __VEN_SOCKET_MSG_PARSER_H__
#define __VEN_SOCKET_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_socket_ping_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_gethostbyname_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_closesocket_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_connect_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_send_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_sendto_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_recv_notify(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_recvfrom_notify(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_create_datalink_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_datalink_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_status_indication(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_status_indication_ex(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_create_datalink_ex_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_datalink_ex_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_socket_close_all_datalinks_ex_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_SETTING_MSG_PARSER_H__
