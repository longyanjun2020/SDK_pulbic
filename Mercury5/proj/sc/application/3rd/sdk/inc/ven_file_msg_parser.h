/**
 *
 * @file    ven_file_msg_parser.h
 * @brief   This file provide the message parser for setting related msg
 * @author  Jorena.Ku
 * @version $Id: ven_file_msg_parser.h 26275 2009-03-20 09:55:07Z code.lin $
 *
 */


#ifndef __VEN_FILE_MSG_PARSER_H__
#define __VEN_FILE_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_file_browse_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_file_select_folder_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_file_sync_folder_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_file_async_operation_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_FILE_MSG_PARSER_H__
