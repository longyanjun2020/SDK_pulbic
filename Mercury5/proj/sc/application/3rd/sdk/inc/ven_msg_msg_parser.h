/**
 *
 * @file    ven_msg_msg_parser.h
 * @brief   This file provide the message parser for message related msg
 * @author  Alison.Chen
 * @version $Id: ven_msg_msg_parser.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */


#ifndef __VEN_MSG_MSG_PARSER_H__
#define __VEN_MSG_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_msg_send_sms_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_incoming_msg_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_get_received_sms_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_open_editor_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_srv_ready_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_get_srv_ready_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_get_sim_capacity_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_sms_get_num_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_sms_get_header_list_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_mms_send_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_delete_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_sms_backup_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_sms_restore_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_msg_sms_add_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_MSG_MSG_PARSER_H__
