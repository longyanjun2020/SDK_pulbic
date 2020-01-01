/*
 * iqserver_cmd_handle.h
 *
 *  Created on: Feb 06, 2018
 *      Author: jeffrey.chou
 */

#ifndef _IQSERVER_CMD_HANDLE_H_
#define _IQSERVER_CMD_HANDLE_H_

#include <iqserver_type.h>

int ParseAndHandleCmd(IQ_CMD_HEADER_S CmdHeader, char* CmdData, int CmdLength, char* GetBuf, int *GetBufLength);

#endif
