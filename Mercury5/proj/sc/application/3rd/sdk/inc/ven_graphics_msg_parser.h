/**
 *
 * @file    ven_graphics_msg_parser.h
 * @brief   This file provide the message parser for graphics related msg
 * @author  steve.lee
 * @version $Id: ven_graphics_msg_parser.h 17965 2008-12-10 07:07:49Z steve.lee $
 *
 */


#ifndef __VEN_GRAPHICS_MSG_PARSER_H__
#define __VEN_GRAPHICS_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_graphics_set_sbvis_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_graphics_get_sbvis_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_graphics_set_display_mode_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);


#endif //__VEN_MSG_MSG_PARSER_H__
