/**
 *
 * @file    ven_rfid_msg_parser.h.
 * @brief   This file implement the message parser for RFID related msg
 * @author Bruce.wu
 *
 * @version $Id: ven_rfid_msg_parser.h  $
 *
 */

#ifndef __VEN_RFID_MSG_PARSER_H__
#define __VEN_RFID_MSG_PARSER_H__

//#ifdef __RFID_SDK_SUPPORT__

#include "ven_common_def.h"


void ven_rfid_cmd_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

void ven_rfid_listener_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

//#endif// __RFID_SDK_SUPPORT__
#endif //__VEN_RFID_MSG_PARSER_H__
