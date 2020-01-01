/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */


/**
 * @file AMSocketEvent.h
 *  Socket Connection JBI
 */
/**
 * @addtogroup Socket_Connection_JBI
 * @{
 */
#ifndef __SOCKET_AM_SOCKET_H
#define __SOCKET_AM_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSocket.h"

/**
 *               Notifies socket events to JBlend.
 * @param socket The socket. Designate the handle of the socket for which 
 *               the event occurred.
 * @param type   The event type. Designate one of the following types based 
 *               on the JSI causing the event notification to be made. 
 *             <dl>
 *              <dt>#JkSocketConnect()
 *               <dd>#JK_SOCKET_EVENT_TYPE_CONNECT</dd>
 *              <dt>#JkSocketSend()
 *               <dd>#JK_SOCKET_EVENT_TYPE_SEND</dd>
 *              <dt>#JkSocketReceive()
 *               <dd>#JK_SOCKET_EVENT_TYPE_RECEIVE</dd>
 *              <dt>#JkSocketShutdown()
 *               <dd>#JK_SOCKET_EVENT_TYPE_SHUTDOWN</dd>
 *              <dt>#JkSocketClose()
 *               <dd>#JK_SOCKET_EVENT_TYPE_CLOSE</dd>
 *             </dl>
 *
 * @param result Designate the following results based on the JSI causing the 
 *               event notification to be made. 
 *             <dl>
 *             <dt>#JkSocketConnect()
 *              <dd>Designate JK_SOCKET_SUCCESS if the operation succeeded.
 *             If the operation failed, designate an appropriate error code 
 *             of those named starting with JK_SOCKET_ERROR_.
 *              </dd>
 *             <dt>#JkSocketSend()
 *              <dd>Designate the size (in octets) of actually sent data.
 *             If the operation failed, designate an appropriate error code 
 *             of those named starting with JK_SOCKET_ERROR_.
 *              </dd>
 *             <dt>#JkSocketReceive()
 *              <dd>Designate the size (in octets) of actually received data.
 *             If the operation failed, designate an appropriate error code 
 *             of those named starting with JK_SOCKET_ERROR_.
 *              </dd>
 *             <dt>#JkSocketShutdown()
 *              <dd>Designate JK_SOCKET_SUCCESS if the operation succeeded.
 *             If the operation failed, designate an appropriate error code 
 *             of those named starting with JK_SOCKET_ERROR_.
 *              </dd>
 *             <dt>#JkSocketClose()
 *              <dd>Designate JK_SOCKET_SUCCESS if the operation succeeded.
 *             If the operation failed, designate an appropriate error code 
 *             of those named starting with JK_SOCKET_ERROR_.
 *              </dd>
 *             </dl>
*/
void AmNotifySocketEvent(JKSocketHandle socket, JKSint32 type, JKSint32 result);


#ifdef __cplusplus
}
#endif
#endif

/**
 * @}
 */
