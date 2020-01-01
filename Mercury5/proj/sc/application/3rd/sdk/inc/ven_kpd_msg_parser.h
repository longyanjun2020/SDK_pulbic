/**
 *
 * @file    ven_kpd_msg_parser.h
 * @brief   This file provide the message parser for keypad message
 * @author  Steve.Lee
 * @version $Id: ven_kpd_msg_parser.h 15943 2008-11-05 08:30:23Z steve.lee $
 *
 */


#ifndef __VEN_KPD_MSG_PARSER_H__
#define __VEN_KPD_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_kpd_input_ind(void* pMessage, bool bBacklightOn);
void ven_kpd_resetKpdContext(void);

#endif //__VEN_KPD_MSG_PARSER_H__
