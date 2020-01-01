/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkServerSocket.h
 *  Server Socket Connection JSI
 */
/**
 * @addtogroup Server_Socket_Connection_JSI
 * @{
 */
#ifndef __SOCKET_JK_SERVERSOCKET_H
#define __SOCKET_JK_SERVERSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSocket.h"
#include "JkTypesServerSocket.h"

/**
 *         Gets the maximum number of simultaneous server socket acceptance. 
 * @return Return the maximum number of server sockets that can be accepted 
 *         at the same time in the native system.
 *
 * This function is called only once, at JVM startup. 
 *
 * JBlend will not request the creation or acceptance of a 
 * server socket if it would exceed the limit returned by this function for 
 * simultaneous server socket acceptance.
 *
 */
JKSint32 JkServerSocketGetMaxSessions(void);

/**
 *             Creates a server socket.
 * @param port The port number.
 * @return     Return a handle uniquely identifying the created server socket, or 
 *             #JK_INVALID_HANDLE in case of error. 
 *
 * JBlend calls this function to create a server socket using the port 
 * number designated in the <i>port</i> parameter.  Assign and return a handle 
 * value uniquely identifying the created socket, enabling other functions to 
 * designate the server socket when performing operations on it. The handle 
 * should remain valid until #JkServerSocketClose() is called.
 * 
 * When a MIDlet designates "socket://:" in the URL parameter of the 
 * <code>Connector</code> class <code>open()</code> method, JBlend 
 * designates -1 in the <i>port</i> parameter. In the native system, create a 
 * server socket assigning an appropriate port number. 
 *
 * At the time this function is called, do not yet start server socket acceptance
 * or acceptance preparation. 
*/
JKServerSocketHandle JkServerSocketOpen(JKSint32 port);


/**
 *               Performs server socket acceptance preparation.
 * @param socket The handle of the server socket. The value returned by 
 *               #JkServerSocketOpen() is designated. 
 * @return       If the operation succeeds, return #JK_SOCKET_SUCCESS. 
 *               In case of error, return either of the following error codes 
 *                as appropriate.
 *                - #JK_SOCKET_ERROR_TIMEOUT
 *                - #JK_SOCKET_ERROR_OTHER
 *                .
 *
 * In the native system, perform acceptance preparation for the server socket 
 * designated in the <i>socket</i> parameter. Address assignment, resource 
 * allocation for connection acceptance, etc. should be performed in this 
 * function. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the acceptance preparation processing. After requesting acceptance preparation by 
 * the separate task, return control to JBlend, putting  #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before acceptance preparation processing by the separate
 * task could be requested, return control to JBlend passing as the return value 
 * an appropriate error code of those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 *  #AmNotifyServerSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Acceptance preparation processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SERVER_SOCKET_EVENT_TYPE_LISTEN
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by  #JkServerSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SERVER_SOCKET_EVENT_TYPE_LISTEN
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Acceptance preparation processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SERVER_SOCKET_EVENT_TYPE_LISTEN
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyServerSocketEvent() may be called either in this function or from the 
 * separate task. If after requesting acceptance preparation by a separate 
 * task, the connection is successfully set up before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifyServerSocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifyServerSocketEvent().
 *
 * Do not start server socket acceptance processing at the time this function is called. 
 *
 */
JKSint32 JkServerSocketListen(JKServerSocketHandle socket);

/**
 *                      Gets the server socket local IP address. 
 * @param socket        The handle of the server socket.
 *                      The value returned by #JkServerSocketOpen() is designated. 
 * @param address       A pointer to the buffer for putting the local IP address.
 *                      Do not append '\0' as string termination. This pointer 
 *                      remains valid until the function returns control to JBlend.
 * @param addressLength The size (in bytes) of the buffer indicated by the <i>address</i>
 *                      parameter.
 * @return              Return the length in byte of the string 
 *                      put in the buffer indicated by the <i>address</i> parameter.
 *                      In case of error, return either of the following error 
 *                      codes as appropriate. 
 *                      - #JK_SOCKET_ERROR_TIMEOUT
 *                      - #JK_SOCKET_ERROR_OTHER
 *                      .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkServerSocketOpen() and until #JkServerSocketClose() is 
 * called.
 */
JKSint32 JkServerSocketGetLocalAddress(JKServerSocketHandle socket,  JKSint8* address, JKSint32 addressLength);

/**
 *               Gets the server socket local port number. 
 * @param socket The handle of the server socket.
 *               The value returned by #JkServerSocketOpen() is designated. 
 * @return       Return the port number (0 < n <= 65535) used by the server socket.
 *               In case of error, return either of the following error 
 *               codes as appropriate. 
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkServerSocketOpen() and until #JkServerSocketClose() is 
 * called.
 */
JKSint32 JkServerSocketGetLocalPort(JKServerSocketHandle socket);

/**
 *               Starts server socket acceptance. 
 * @param socket The handle of the server socket.
 *               The value returned by #JkServerSocketOpen() is designated. 
 * @return       Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *               In case of error, return either of the following error codes 
 *               as appropriate.
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * In the native system, start acceptance processing of the socket connection 
 * request for the server socket designated by the <i>socket</i> parameter. 
 * If there is a connection request by a client for a server socket 
 * in accept state, create a socket for the connection and connect to it. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the acceptance processing. After requesting acceptance processing by 
 * the separate task, return control to JBlend, putting  #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before acceptance processing by the separate task
 * could be requested, return control to JBlend passing as the return value 
 * an appropriate error code of those named starting with JK_SOCKET_ERROR_.
 *
 * When a client requests connection to a server socket in accept 
 * state, create a socket and assign to it a unique handle value, similarly 
 * to when #JkSocketOpen() is called. Then connect the socket in the same 
 * way as when #JkSocketConnect() is called. The handle assigned to the 
 * connected socket should remain valid until #JkSocketClose() is called 
 * for that socket.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 *  #AmNotifyServerSocketAccepted() at the time of any of the following 
 * occasions and notify JBlend of the result.
 * <dl>
 * <dt>Socket connection succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketAccepted() as follows.
 *   <ul>
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *     <li><i>server</i>: The server socket handle value
 *     <li><i>client</i>: The handle value of the socket connected to the 
 *                        client 
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by  #JkServerSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketAccepted() as follows.
 *   <ul>
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *     <li><i>server</i>: The server socket handle value
 *     <li><i>client</i>: Any value
 *   </ul>
 * </dd>
 * <p>
 * <dt>Socket connection failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketAccepted() as follows.
 *   <ul>
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *     <li><i>server</i>: The server socket handle value
 *     <li><i>client</i>: Any value
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyServerSocketAccepted() may be called either in this function or 
 * from the separate task. If after requesting connection processing by a 
 * separate task, the connection is successfully set up before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifyServerSocketAccepted() before passing control to 
 * JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifyServerSocketAccepted().
 *
 * If the socket is connected successfully, then in the case of a socket 
 * returned in the <i>client</i> parameter of #AmNotifyServerSocketAccepted(), 
 * JBlend continues processing on the assumption that #JkSocketOpen() 
 * and #JkSocketConnect() have been called for that socket and the processing 
 * of both functions has succeeded.
 *
 * This function is never called again for the same server socket until its result 
 * is returned. It may, however, be called for a different server socket.
 */
JKSint32 JkServerSocketAccept(JKServerSocketHandle socket);

/**
 *               Closes a server socket.
 * @param socket The handle of the server socket.
 *               The value returned by #JkServerSocketOpen() is designated. 
 * @return       Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *               In case of error, return either of the following error codes 
 *               as appropriate.
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * In the native system, if the server socket is in accept state, stop 
 * the acceptance processing, then destroy the server socket and release 
 * its resources. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, using a separate task to perform 
 * the closure processing (acceptance cancelation and socket destroy 
 * processing). 
 * After requesting closure processing by the separate task, return 
 * control to JBlend, putting  #JK_SOCKET_SUCCESS in the return 
 * value. 
 * If an error occurred before closure processing by the separate task could 
 * be requested, return control to JBlend passing as the return value an 
 * appropriate error code of those named starting with JK_SOCKET_ERROR_. 
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 *  #AmNotifyServerSocketEvent() at the time of any of the following 
 * occasions and notify JBlend of the result.
 * <dl>
 * <dt>Acceptance cancelation and socket destroy processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SERVER_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed.</dt>
 * <dd>Pass parameter values to #AmNotifyServerSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SERVER_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyServerSocketEvent() may be called either in this function or from the 
 * separate task. If after requesting closure processing by a separate task, the 
 * operation is successfully completed before control is passed from this 
 * function to JBlend, there is no problem with making event notification 
 * by #AmNotifyServerSocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifyServerSocketEvent().
 *
 * If at the time this function is called, the processing result for the 
 * functions indicated below has not yet been notified, make event 
 * notification also for the result of processing requested by these 
 * functions.
 * <ul>
 * <li>JkServerSocketListen() 
 * <li>JkServerSocketAccept() 
 * </ul>
 *
*/
JKSint32 JkServerSocketClose(JKServerSocketHandle socket);

#ifdef __cplusplus
}
#endif

#endif
