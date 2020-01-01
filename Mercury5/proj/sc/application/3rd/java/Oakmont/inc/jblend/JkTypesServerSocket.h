/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesServerSocket.h
 *  ServerSocketConnection data types and constants
 */

#ifndef __SOCKET_JK_TYPES_SERVER_SOCKET_H
#define __SOCKET_JK_TYPES_SERVER_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * @addtogroup Server_Socket_Connection_Data_Types
 * @{
 */

/**
 * Server socket handle type
 */
typedef JKHandle JKServerSocketHandle;

/**
 *  A acceptance preparation result notification event.\ This 
 *  is used for notifying the result of JkServerSocketListen() processing.
*/
#define JK_SERVER_SOCKET_EVENT_TYPE_LISTEN      1001

/**
 *  A closure result notification event.\ This 
 *  is used for notifying the result of JkServerSocketClose() processing.
*/
#define JK_SERVER_SOCKET_EVENT_TYPE_CLOSE       1002


#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */
