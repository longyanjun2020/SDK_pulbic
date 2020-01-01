/**
 *
 * @file    ven_setting_msg_parser.h
 * @brief   This file provide the message parser for setting related msg
 * @author  Jorena.Ku
 * @version $Id: ven_setting_msg_parser.h 36962 2009-07-31 13:59:22Z code.lin $
 *
 */


#ifndef __VEN_SETTING_MSG_PARSER_H__
#define __VEN_SETTING_MSG_PARSER_H__

#include "ven_common_def.h"

//void ven_setting_msg_parser(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getFileStr_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_setURL_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getVolume_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getVibration_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getNetworkProfile_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getNetworkProfile_ex_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_setNetworkProfile_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getSelectSIM_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getDefaultSIM_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getCurrentLanguage_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getSIMStatus_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_setting_getKeypadTone_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
#endif //__VEN_SETTING_MSG_PARSER_H__
