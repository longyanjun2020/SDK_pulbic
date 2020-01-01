/**
 *
 * @file    ven_cam_msg_parser.h
 *
 * @brief   This file provide the message parser for camera/camcorder related message
 *
 * @author  steve.lee
 *
 * @version $Id: ven_cam_msg_parser.h 34154 2009-06-23 09:06:12Z code.lin $
 *
 */


#ifndef __VEN_CAM_MSG_PARSER_H__
#define __VEN_CAM_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_cam_open_camera_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_close_camera_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_start_preview_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_stop_preview_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_capture_image_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_convert_image_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_cam_launch_app_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);

#endif //__VEN_CAM_MSG_PARSER_H__
