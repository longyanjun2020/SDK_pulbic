/**
* @file    mmi_if_socket.h
* @brief   This file defines the interface to parse messages from mserv task.
* @author  li-wei.cheng
*
*/
#ifndef __MMI_IF_SOCKET_H__
#define __MMI_IF_SOCKET_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_socket_msg_parser(IBase* pRecipient, struct vm_msg*);

#endif/* __MMI_IF_SOCKET_H__ */
