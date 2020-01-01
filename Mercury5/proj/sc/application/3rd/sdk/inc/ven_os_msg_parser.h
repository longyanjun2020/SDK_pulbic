/**
 *
 * @file    ven_os_msg_parser.h
 * @brief   This file provide the message parser for os message
 * @author  Roger Lai
 * @version $Id
 *
 */


#ifndef __VEN_OS_MSG_PARSER_H__
#define __VEN_OS_MSG_PARSER_H__

#include "ven_common_def.h"
#include "sys_rtk_vmoshi.h"

void ven_os_msg_parser(void* pMessage);
void ven_os_msg_ind(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_OS_MSG_PARSER_H__

