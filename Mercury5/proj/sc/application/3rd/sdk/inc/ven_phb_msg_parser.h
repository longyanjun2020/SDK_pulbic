/**
 *
 * @file    ven_phb_msg_parser.h
 * @brief   This file provide the message parser for phonebook related message
 * @author  Alison.Chen
 * @version $Id: ven_phb_msg_parser.h 29112 2009-04-22 13:08:58Z steve.lee $
 *
 */


#ifndef __VEN_PHB_MSG_PARSER_H__
#define __VEN_PHB_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_phb_browse_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_addContact_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_writeContact_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_deleteContact_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_saveContactByHandle_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_findFirst_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_findNext_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_getMemStatus_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_NumberFuzzySearch_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_phb_register_ready_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
#endif //__VEN_PHB_MSG_PARSER_H__
