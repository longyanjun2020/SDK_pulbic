/**
 *
 * @file    ven_editor_msg_parser.h
 * @brief   This file provide the message parser for editor related msg
 * @author  Alison.Chen
 * @version $Id: ven_editor_msg_parser.h 15633 2008-10-28 03:55:31Z steve.lee $
 *
 */


#ifndef __VEN_EDITOR_MSG_PARSER_H__
#define __VEN_EDITOR_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_editor_datetime_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_editor_edit_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_EDITOR_MSG_PARSER_H__
