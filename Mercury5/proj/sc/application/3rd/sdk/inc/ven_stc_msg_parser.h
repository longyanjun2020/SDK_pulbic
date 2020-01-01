/**
 * @file ven_app_msg_parser.h
 *
 * @brief This file defines the app state control related message parsers
 *
 * @version $Id: ven_stc_msg_parser.h 15633 2008-10-28 03:55:31Z steve.lee $
 *
 */
#ifndef __VEN_APP_MSG_PARSER_H__
#define __VEN_APP_MSG_PARSER_H__

#include "ven_stc_msgt.h"


void ven_stc_handle_start_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_stop_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_suspend_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_resume_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_background_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_foreground_req(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_start_cnf(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_stc_handle_status_change_cnf(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif /* __VEN_APP_MSG_PARSER_H__ */


