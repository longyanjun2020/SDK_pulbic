/**
 *
 * @file    ven_sensor_msg_parser.h
 * @brief   This file provide the message parser for sensor related msg
 * @author  Mansun Lee
 * @version
 *
 */


#ifndef __VEN_SENSOR_MSG_PARSER_H__
#define __VEN_SENSOR_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_sen_gsensor_reg_notify_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_gsensor_reg_notify_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_gsensor_get_devinfo_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_gsensor_reg_motion_listener_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_gsensor_reg_motion_listener_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_gsensor_get_last_motion_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_sen_btapp_send_file_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);


#endif

