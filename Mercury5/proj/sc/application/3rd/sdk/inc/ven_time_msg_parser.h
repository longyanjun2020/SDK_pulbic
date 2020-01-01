/**
 *
 * @file    ven_time_msg_parser.h.
 * @brief   This file implement the message parser for time related msg
 * @author  Code Lin
 * @version $Id: ven_time_msg_parser.h 40108 2009-09-12 12:04:25Z code.lin $
 *
 */

#ifndef __VEN_TIME_MSG_PARSER_H__
#define __VEN_TIME_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_time_setTime_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_time_setTimeZone_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_TIME_MSG_PARSER_H__
