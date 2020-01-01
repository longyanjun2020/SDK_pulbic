/**
 *
 * @file    ven_cc_msg_parser.h
 * @brief   This file provide the message parser for call control related message
 * @author  Alison.Chen
 * @version $Id: ven_cc_msg_parser.h 15633 2008-10-28 03:55:31Z steve.lee $
 *
 */


#ifndef __VEN_CC_MSG_PARSER_H__
#define __VEN_CC_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_cc_make_call_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cc_make_call_get_call_id_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cc_get_call_status_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cc_register_incoming_call_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cc_register_call_log_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cc_send_DTMF_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_PHB_MSG_PARSER_H__
