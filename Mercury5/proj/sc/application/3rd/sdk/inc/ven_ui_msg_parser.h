/**
 *
 * @file    ven_ui_msg_parser.h
 *
 * @brief   This file provide the message parser for UI related message
 *
 * @author  steve.lee
 *
 * @version $Id: ven_ui_msg_parser.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */


#ifndef __VEN_UI_MSG_PARSER_H__
#define __VEN_UI_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_ui_show_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_set_interrupt_level_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_set_backlight_behavior_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_get_backlight_info_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_backlight_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_get_applet_status_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_ui_enable_launch_keyguard_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif /* __VEN_UI_MSG_PARSER_H__ */

