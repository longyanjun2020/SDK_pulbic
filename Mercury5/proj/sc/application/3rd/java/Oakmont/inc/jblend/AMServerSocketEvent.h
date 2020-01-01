/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */


/**
 * @file AMServerSocketEvent.h
 *  Server Socket Connection JBI
 */
/**
 * @addtogroup Server_Socket_Connection_JBI
 * @{
 */
#ifndef __SOCKET_AM_SERVERSOCKET_H
#define __SOCKET_AM_SERVERSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSocket.h"
#include "JkTypesServerSocket.h"


/**
 *               Notifies server socket events to JBlend. 
 * @param server The server socket.
 *               Designate the handle of the server socket where the event occurred. 
 * @param type   The event type. Designate one of the following types based on the 
 *               JSI causing the event notification to be made. 
 *               <dl>
 *                <dt>#JkServerSocketListen()
 *                 <dd>#JK_SERVER_SOCKET_EVENT_TYPE_LISTEN</dd>
 *                <dt>#JkServerSocketClose()
 *                 <dd>#JK_SERVER_SOCKET_EVENT_TYPE_CLOSE</dd>
 *               </dl>
 * @param result Designate the following results based on the JSI causing the 
 *               event notification to be made. 
 *               <dl>
 *                <dt>#JkServerSocketListen()
 *                  <dd>Designate #JK_SOCKET_SUCCESS if the operation succeeded.
 *                      If the operation failed, designate an appropriate error 
 *                      code of those named starting with JK_SOCKET_ERROR_.</dd>
 *               <dt>#JkServerSocketClose()
 *                  <dd>Designate #JK_SOCKET_SUCCESS if the operation succeeded.
 *                      If the operation failed, designate an appropriate error 
 *                      code of those named starting with JK_SOCKET_ERROR_.</dd>
 *               </dl>
*/
void AmNotifyServerSocketEvent(JKServerSocketHandle socket, JKSint32 type, JKSint32 result);

/**
 *               Notifies JBlend of an event related to server socket 
 *               acceptance processing. 
 * @param server The server socket.
 *               Designate the handle of the server socket where the event occurred. 
 * @param result If a successful connection was made to the client, designate 
 *                #JK_SOCKET_SUCCESS.
 *               In case of error, return either of the following error codes 
 *               as appropriate.
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 * @param client Designate the handle of the socket connecting to the client, 
 *               or #JK_INVALID_HANDLE in case of error.
 *
 * Use this function to notify JBlend of the acceptance result for a 
 * server socket put in accept state by JkServerSocketAccept().
*/
void AmNotifyServerSocketAccepted(JKServerSocketHandle server, JKSint32 result, JKSocketHandle client);


#ifdef __cplusplus
}
#endif
#endif

/**
 * @}
 */

