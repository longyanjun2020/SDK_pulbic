/**
 *
 * @file    ven_drv_msg_parser.h
 * @brief   This file provides the message parser for drv related msg
 * @author  Steve.Lee
 * @version $Id: ven_drv_msg_parser.h 25432 2009-03-11 12:47:57Z steve.lee $
 *
 */


#ifndef __VEN_DRV_MSG_PARSER_H__
#define __VEN_DRV_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_drv_acs_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_drv_usb_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_drv_backlight_ind(ven_msg_t MsgID, vm_msg_t *pMessage);


#endif //__VEN_DRV_MSG_PARSER_H__
