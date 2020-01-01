/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesSocket.h
 *  SocketConnection data types and constants
 */

#ifndef __SOCKET_JK_TYPES_SOCKET_H
#define __SOCKET_JK_TYPES_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 * @addtogroup Socket_Connection_Data_Types
 * @{
 */

/**
 *   Socket handle type
 */
typedef JKHandle JKSocketHandle;

/**
 *  Values returned by the individual functions
 */
/**
 * Succeeded.
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySocketEvent(), or as the
 *  return value of the following @ref Socket_Connection_JSI functions.
 * <ul>
 *  <li> #JkSocketConnect()
 *  <li> #JkSocketSend()
 *  <li> #JkSocketReceive()
 *  <li> #JkSocketSetOption()
 *  <li> #JkSocketShutdown()
 *  <li> #JkSocketClose()
 * </ul>
*/
#define JK_SOCKET_SUCCESS       0

/**
 * Error code: Canceled due to timeout
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySocketEvent(), or as the
 *  return code of @ref Socket_Connection_JSI functions other than 
 *  #JkSocketOpen() and #JkSocketGetMaxSessions().
 */
#define JK_SOCKET_ERROR_TIMEOUT         -20000

/**
 * Error code: An internal error occurred
 *
 *  Passed in the <i>result</i> parameter of #AmNotifySocketEvent(), or as the
 *  return code of @ref Socket_Connection_JSI functions other than 
 *  #JkSocketOpen() and #JkSocketGetMaxSessions().
 */
#define JK_SOCKET_ERROR_OTHER           -30000

/**
 * Shut down receive direction only.\ This is designated in the <i>how</i>
 * parameter of #JkSocketShutdown().
*/
#define JK_SOCKET_SHUTDOWN_RECEIVE      1

/**
 * Shut down send direction only.\ This is designated in the <i>how</i>
 * parameter of #JkSocketShutdown().
*/
#define JK_SOCKET_SHUTDOWN_SEND         2

/**
 * Shut down both send and receive directions.\ This is designated in the <i>how</i>
 * parameter of #JkSocketShutdown().
*/
#define JK_SOCKET_SHUTDOWN_BOTH         3

/**
 * Designate Nagle algorithm use as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSocketGetOption() 
 * and #JkSocketSetOption().
*/
#define JK_SOCKET_OPTION_DELAY          1

/**
 * Designate whether to send a KEEPALIVE signal as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSocketGetOption() 
 * and #JkSocketSetOption().
*/
#define JK_SOCKET_OPTION_KEEPALIVE      2

/**
 * Designate linger time as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSocketGetOption() 
 * and #JkSocketSetOption().
*/
#define JK_SOCKET_OPTION_LINGER         3

/**
 * Designate the receive buffer size as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSocketGetOption() 
 * and #JkSocketSetOption().
*/
#define JK_SOCKET_OPTION_RCVBUF         4

/**
 * Designate the send buffer size as a socket option.\ This 
 * is designated in the <i>option</i> parameter of #JkSocketGetOption() 
 * and #JkSocketSetOption().
*/
#define JK_SOCKET_OPTION_SNDBUF         5

/**
 *  A connection result notification event.\ This is used for notifying the 
 *  result of #JkSocketConnect() processing.
*/
#define JK_SOCKET_EVENT_TYPE_CONNECT        1

/**
 *  A send result notification event.\ This is used for notifying the 
 *  result of #JkSocketSend() processing.
*/
#define JK_SOCKET_EVENT_TYPE_SEND           2

/**
 *  A receive result notification event.\ This is used for notifying the 
 *  result of #JkSocketReceive() processing.
*/
#define JK_SOCKET_EVENT_TYPE_RECEIVE        3

/**
 *  A shut down result notification event.\ This is used for notifying the 
 *  result of #JkSocketShutdown() processing.
*/
#define JK_SOCKET_EVENT_TYPE_SHUTDOWN       4

/**
 *  A socket disconnect/destroy result notification event.\ This is used 
 *  for notifying the result of #JkSocketClose() processing. 
*/
#define JK_SOCKET_EVENT_TYPE_CLOSE          5

#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */
