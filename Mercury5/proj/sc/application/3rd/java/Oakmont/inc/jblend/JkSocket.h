/**
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkSocket.h
 *  Socket Connection JSI
 */
/**
 * @addtogroup Socket_Connection_JSI
 * @{
 */
#ifndef __SOCKET_JK_SOCKET_H
#define __SOCKET_JK_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSocket.h"

/**
 *         Gets the maximum number of simultaneous socket connections. 
 * @return Return the maximum number of sockets that can be connected 
 *         at the same time in the native system.
 *
 * This function is called only once, at JVM startup. 
 *
 * JBlend will not request the creation or connection of a 
 * socket if it would exceed the limit returned by this function for 
 * simultaneous socket connections.
 */
JKSint32 JkSocketGetMaxSessions(void);

/**
 *         Creates a socket.
 * @param  address 
 *         A pointer to a buffer holding the remote IP address or host name. 
 *         The string is not terminated by '\0'. This pointer remains valid 
 *         until the function returns control to JBlend.
 * @param  addressLength 
 *         The length (number of characters) of the remote IP address or host name
 * @param  port 
 *         The remote port number
 * 
 * @return Return a handle uniquely identifying the created socket, or 
 *         #JK_INVALID_HANDLE in case of error. 
 * 
 * JBlend calls this function to create a socket using the port number 
 * designated in the <i>port</i> parameter.  Assign and return a handle value 
 * uniquely identifying the created socket, enabling other functions to 
 * designate the socket when performing operations on it. The handle should 
 * remain valid until #JkSocketClose() is called.
 * 
 * When this function is called, make the necessary preparations in the 
 * native system for socket connection, but do not yet make the actual 
 * socket connection. 
 */
JKSocketHandle JkSocketOpen(const JKSint8* address, JKSint32 addressLength, JKSint32 port);

/**
 *                Sets up a socket connection.
 * @param  socket The handle of the socket. The value returned by #JkSocketOpen() 
 *                is designated. 
 * @return        If the connection succeeds, return #JK_SOCKET_SUCCESS. 
 *                In case of error, return either of the following error codes 
 *                as appropriate.
 *                - #JK_SOCKET_ERROR_TIMEOUT
 *                - #JK_SOCKET_ERROR_OTHER
 *                .
 *
 * In the native system, connect the socket designated in the <i>socket</i> 
 * parameter to the remote host, enabling communication on that connection. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the connection processing. After requesting connection processing by 
 * the separate task, return control to JBlend, putting #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before processing by the separate task could be requested, 
 * return control to JBlend passing as the return value an appropriate error code of 
 * those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>The connection was successful.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>The connection failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySocketEvent() may be called either in this function or from the 
 * separate task. If after requesting connection processing by a separate 
 * task, the connection is successfully set up before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifySocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifySocketEvent().
 */
JKSint32 JkSocketConnect(JKSocketHandle socket);

/**
 *                   Sends data to a socket in connected state. 
 * @param socket     The handle of the socket. The value returned by #JkSocketOpen() 
 *                   is designated. 
 * @param data       A pointer to the buffer holding the data to be sent. This 
 *                   pointer remains valid until the result of this function call 
 *                   is notified to JBlend in an event. 
 * @param dataLength The size of send data (in octets). 
 * @return           Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *                   In case of error, return either of the following error codes 
 *                   as appropriate.
 *                   - #JK_SOCKET_ERROR_TIMEOUT
 *                   - #JK_SOCKET_ERROR_OTHER
 *                   .
 *
 * In the native system, send the data indicated by the <i>data</i> parameter 
 * to the socket connection remote end. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the transmission processing. After requesting transmission processing by 
 * the separate task, return control to JBlend, putting  #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before send processing by the separate task could be 
 * requested, return control to JBlend passing as the return value an appropriate
 * error code of those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Send processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: The size of data actually sent
 *   </ul>
 * If the value passed in the <i>result</i> parameter is less than the send size
 * requested by #JkSocketSend(), JBlend repeats the cycle of calling this
 * function and waiting for an event, until sending of all data is complete. 
 * </dd>
 * <p>
 * <dt>The connection was closed by the peer, or was already closed.</dt>
 * <dt>The processing was canceled by #JkSocketClose().
 * <dt>#JkSocketShutdown() was called passing #JK_SOCKET_SHUTDOWN_SEND in
 * the <i>how</i> parameter, canceling send processing.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Sending failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySocketEvent() may be called either in this function or from the 
 * separate task. If after requesting transmission processing by a separate 
 * task, the transmission is successfully performed before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifySocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifySocketEvent().
 *
 * This function is never called again for the same socket until its result 
 * is returned. It may, however, be called for a different socket.
 */
JKSint32 JkSocketSend(JKSocketHandle socket, const JKUint8* data, JKSint32 dataLength);

/**
 *                   Receives data from a socket in connected state. 
 * @param socket     The handle of the socket. The value returned by 
 *                   #JkSocketOpen() is designated. 
 * @param data       A pointer to the buffer for putting the received data. This 
 *                   pointer remains valid until the result of this function call 
 *                   is notified to JBlend in an event. 
 * @param dataLength The size (in octets) of the buffer indicated by the 
 *                   <i>data</i> parameter.
 * @return           Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *                   In case of error, return either of the following error codes 
 *                   as appropriate.
 *                   - #JK_SOCKET_ERROR_TIMEOUT
 *                   - #JK_SOCKET_ERROR_OTHER
 *                   .
 *
 * In the native system, put the data received from the socket connection 
 * remote end to the buffer pointed to by the <i>data</i> parameter.
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the receipt processing. After requesting receipt processing by 
 * the separate task, return control to JBlend, putting  #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before receive processing by the separate task could 
 * be requested, return control to JBlend passing as the return value an 
 * appropriate error code of those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Receive processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: The size of data actually received
 *   </ul>
 * It does not matter if the data size passed in the <i>result</i> parameter
 * is smaller than the receive data size requested by #JkSocketReceive().
 * </dd>
 * <p>
 * <dt>The connection was already closed by the peer.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: 0
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkSocketClose().</dt>
 * <dt>#JkSocketShutdown() was called passing #JK_SOCKET_SHUTDOWN_RECEIVE in
 * the <i>how</i> parameter, canceling receive processing.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Receipt failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySocketEvent() may be called either in this function or from the 
 * separate task. If after requesting receipt processing by a separate 
 * task, the receipt is successfully performed before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifySocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifySocketEvent().
 *
 * This function is never called again for the same socket until its result 
 * is returned. It may, however, be called for a different socket.
 */
JKSint32 JkSocketReceive(JKSocketHandle socket, JKUint8* data, JKSint32 dataLength);

/**
 *                Gets the size of received data that can be acquired 
 *                without I/O blocking.
 * @param socket  The handle of the socket. The value returned by #JkSocketOpen() 
 *                is designated. 
 * @return        Return the size of received data that JBlend can acquire 
 *                without I/O blocking. In case of error, return either of the 
 *                following error codes as appropriate. 
 *                - #JK_SOCKET_ERROR_TIMEOUT
 *                - #JK_SOCKET_ERROR_OTHER
 *                .
 *
 * This function should return control to JBlend as quickly as possible, to 
 * avoid blocking JBlend processing for an extended period.
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 */

JKSint32 JkSocketAvailable(JKSocketHandle socket);

/**
 *                      Gets a socket connection remote address.
 * @param socket        The handle of the socket. The value returned by 
 *                      #JkSocketOpen() is designated. 
 * @param address       A pointer to the buffer holding the remote IP address 
 *                      or host name. Do not append '\0' as string termination.
 *                      This pointer remains valid until the function returns 
 *                      control to JBlend.
 * @param addressLength The size (in bytes) of the buffer indicated by the <i>address</i>
 *                      parameter.
 * @return              Return the length in bytes of the string 
 *                      put in the buffer indicated by the <i>address</i> parameter.
 *                      In case of error, return either of the following error 
 *                      codes as appropriate. 
 *                      - #JK_SOCKET_ERROR_TIMEOUT
 *                      - #JK_SOCKET_ERROR_OTHER
 *                      .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 */

JKSint32 JkSocketGetAddress(JKSocketHandle socket, JKSint8* address, JKSint32 addressLength);

/**
 *               Gets the socket connection remote port number. 
 * @param socket The handle of the socket. The value returned by #JkSocketOpen() 
 *               is designated. 
 * @return       Return the remote port number (0 < n <= 65535).
 *               In case of error, return either of the following error 
 *               codes as appropriate. 
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 */
JKSint32 JkSocketGetPort(JKSocketHandle socket);

/**
 *                      Gets a socket connection local IP address. 
 * @param socket        The handle of the socket. The value returned by 
 *                      #JkSocketOpen() is designated. 
 * @param address       A pointer to a buffer for putting the IP address. 
 * @param addressLength The size in bytes of the buffer pointed to by the 
 *                      <i>address</i> parameter.
 * @return              Return the length in bytes of the string 
 *                      put in the buffer indicated by the <i>address</i> parameter.
 *                      In case of error, return either of the following error 
 *                      codes as appropriate. 
 *                      - #JK_SOCKET_ERROR_TIMEOUT
 *                      - #JK_SOCKET_ERROR_OTHER
 *                      .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 */
JKSint32 JkSocketGetLocalAddress(JKSocketHandle socket,  JKSint8* address, JKSint32 addressLength);

/**
 *               Gets the socket connection local port number. 
 * @param socket The handle of the socket. The value returned by #JkSocketOpen() 
 *               is designated. 
 * @return       Return the port number (0 < n <= 65535).
 *               In case of error, return either of the following error 
 *               codes as appropriate. 
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 */
JKSint32 JkSocketGetLocalPort(JKSocketHandle socket);

/**
 *               Sets options controlling socket behavior. 
 * @param socket The handle of the socket. The value returned by 
 *               #JkSocketOpen() is designated. 
 * @param option The option to be set. Any of the following is designated.
 *               - #JK_SOCKET_OPTION_DELAY
 *               - #JK_SOCKET_OPTION_KEEPALIVE
 *               - #JK_SOCKET_OPTION_LINGER
 *               - #JK_SOCKET_OPTION_RCVBUF
 *               - #JK_SOCKET_OPTION_SNDBUF
 *               .
 * @param value The value to be set in the option designated by the <i>option</i> parameter.
 * @return      Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *              In case of error, return either of the following error codes 
 *              as appropriate.
 *              - #JK_SOCKET_ERROR_TIMEOUT
 *              - #JK_SOCKET_ERROR_OTHER
 *              .
 *
 * In the native system, set the designated socket option for the socket 
 * designated in the <i>socket</i> parameter. Set the <i>value</i> parameter 
 * for the option indicated by the <i>option</i> parameter as follows.
 * <dl>
 *   <dt>#JK_SOCKET_OPTION_DELAY
 *   <dd>Sets the Nagle algorithm to enabled (1) or disabled (0).</dd>
 *   <dt>#JK_SOCKET_OPTION_KEEPALIVE
 *   <dd>Sets the KEEPALIVE function to enabled (1) or disabled (0).</dd>
 *   <dt>#JK_SOCKET_OPTION_LINGER
 *   <dd>Sets linger time (in seconds).<br>
 *     Treat <i>value</i>=0 as no linger time.</dd>
 *   <dt>#JK_SOCKET_OPTION_RCVBUF
 *   <dd>Sets the data receive buffer size (in octets).</dd>
 *   <dt>#JK_SOCKET_OPTION_SNDBUF
 *   <dd>Sets the data send buffer size (in octets).</dd>
 * </dl>
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 *
 * The initial settings of socket options are implementation dependent. 
 */
JKSint32 JkSocketSetOption(JKSocketHandle socket, JKSint32 option, JKSint32 value);

/**
 *               Gets the settings for options controlling socket behavior. 
 * @param socket The handle of the socket. The value returned by #JkSocketOpen() 
 *               is designated. 
 * @param option The option to be get. Any of the following is designated.
 *               - #JK_SOCKET_OPTION_DELAY
 *               - #JK_SOCKET_OPTION_KEEPALIVE
 *               - #JK_SOCKET_OPTION_LINGER
 *               - #JK_SOCKET_OPTION_RCVBUF
 *               - #JK_SOCKET_OPTION_SNDBUF
 *               .
 * @return       If the operation succeeds, return the current setting for 
 *               the option designated by the <i>option</i> parameter.  Return
 *               values for each of the options indicated in the <i>option</i> 
 *               parameter as follows. <br><br>
 *         <dl>
 *         <dt> #JK_SOCKET_OPTION_DELAY
 *           <dd>Return whether the Nagle algorithm is enabled (1) or disabled (0).
 *           </dd>
 *         <dt> #JK_SOCKET_OPTION_KEEPALIVE
 *           <dd>Return whether the KEEPALIVE function is enabled (1) or disabled (0).
 *           </dd>
 *         <dt> #JK_SOCKET_OPTION_LINGER
 *           <dd>Return the linger time (in seconds). If there is no linger 
 *               time, return 0.
 *           </dd>
 *         <dt> #JK_SOCKET_OPTION_RCVBUF
 *           <dd>Return the data receive buffer size (in octets).
 *           </dd>
 *         <dt> #JK_SOCKET_OPTION_SNDBUF
 *           <dd>Return the data send buffer size (in octets).
 *           </dd>
 *         </dl><br>
 *         In case of error, return either of the following error codes 
 *         as appropriate.
 *         - #JK_SOCKET_ERROR_TIMEOUT
 *         - #JK_SOCKET_ERROR_OTHER
 *         .
 *
 * This function is called in response to requests from a MIDlet during the 
 * time after the calling of #JkSocketConnect() and until #JkSocketClose() is 
 * called.
 *
 * The initial settings of socket options are implementation dependent. 
 */
JKSint32 JkSocketGetOption(JKSocketHandle socket, JKSint32 option);

/**
 *               Shuts down a socket.
 * @param socket The handle of the socket. The value returned by #JkSocketOpen() 
 *               is designated. 
 * @param how    The direction of communication to be shut down. One of the 
 *               following values is designated.
 *               - #JK_SOCKET_SHUTDOWN_SEND
 *               - #JK_SOCKET_SHUTDOWN_RECEIVE
 *               - #JK_SOCKET_SHUTDOWN_BOTH
 *               .
 * @return       Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *               In case of error, return either of the following error codes 
 *               as appropriate.
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * JBlend calls this function with the <i>how</i> parameter set to
 * the values shown in the table below, in response to the invocation of 
 * the <code>close</code> method of <code>InputStream</code> or 
 * <code>OutputStream</code>. In the native system, shut down the 
 * socket communication for the direction(s) designated in the <i>how</i>
 * parameter.
 * 
 * <table border="1">
 * <tr><td><code>InputStream#close<code></td><td> #JK_SOCKET_SHUTDOWN_RECEIVE</td></tr>
 * <tr><td><code>OutputStream#close<code></td><td> #JK_SOCKET_SHUTDOWN_SEND</td></tr>
 * <tr><td>(*)<code>SocketConnection#close</code></td><td> #JK_SOCKET_SHUTDOWN_BOTH</td></tr>
 * </table>
 * (*)When SocketConnection is closed in the state where neither 
 * <code>InputStream</code> nor <code>OutputStream</code> is opened. 
 *
 * This function is called during the time after the calling of #JkSocketConnect() 
 * and until #JkSocketClose() is called.
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the shutdown processing. After requesting shutdown processing by 
 * the separate task, return control to JBlend, putting #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before shutdown processing by the separate task could 
 * be requested, return control to JBlend passing as the return value an 
 * appropriate error code of those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Shutdown succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #JK_SOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Shutdown failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySocketEvent() may be called either in this function or from the 
 * separate task. If after requesting shut down processing by a separate 
 * task, the shut down is successfully performed before control is passed 
 * from this function to JBlend, there is no problem with making event 
 * notification by #AmNotifySocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifySocketEvent().
 *
 * According to the MIDP 2.0 specification, it is recommended that the 
 * blocking of the Java thread which is performing send operation or 
 * receive operation should be released if the <code>InputStream</code> 
 * or <code>OutputStream</code> <code>close</code> method is called 
 * in the middle of the operation by other Java thread.
 * In socket shutdown operation, the blocking behavior of the Java thread 
 * which is performing send operation or receive operation depends on that
 * of the native system.
 */
JKSint32 JkSocketShutdown(JKSocketHandle socket, JKSint32 how);

/**
 *               Disconnects a connected socket and destroys the socket. 
 * @param socket The handle of the socket. The value returned by #JkSocketOpen() 
 *               is designated. 
 * @return       Return #JK_SOCKET_SUCCESS if the operation succeeds. 
 *               In case of error, return either of the following error codes 
 *               as appropriate.
 *               - #JK_SOCKET_ERROR_TIMEOUT
 *               - #JK_SOCKET_ERROR_OTHER
 *               .
 *
 * In the native system, disconnect the socket from the remote end, then 
 * destroy the socket and free its resources. 
 *
 * If the processing by this function is likely to block JBlend 
 * processing for an extended period, control should be returned to 
 * JBlend as soon as possible, and a separate task used to perform 
 * the disconnection and destruction processing. After requesting 
 * disconnection and destruction processing by the separate task, 
 * return control to JBlend, putting #JK_SOCKET_SUCCESS 
 * in the return value. 
 * If an error occurred before socket disconnect and destroy processing by the
 * separate task could be requested, return control to JBlend passing as the
 * return value an appropriate error code of those named starting with JK_SOCKET_ERROR_.
 *
 * If #JK_SOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Socket disconnect and destroy processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #JK_SOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed.</dt>
 * <dd>Pass parameter values to #AmNotifySocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: An appropriate error code named starting with JK_SOCKET_ERROR_
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySocketEvent() may be called either in this function or from the 
 * separate task. If after requesting disconnection and destruction processing 
 * by a separate task, the disconnection and destruction is successfully 
 * performed before control is passed from this function to JBlend, 
 * there is no problem with making event notification by #AmNotifySocketEvent() 
 * before passing control to JBlend.
 *
 * If a value other than #JK_SOCKET_SUCCESS is returned, do not make event 
 * notification by  #AmNotifySocketEvent().
 *
 * If communication (e.g., data sending/receipt) is in progress when this 
 * function is called, cut off the communication with the remote end.
 *
 * If at the time this function is called, the processing result for the 
 * functions indicated below has not yet been notified, make event 
 * notification also for the result of processing requested by these 
 * functions.
 * <ul>
 * <li>JkSocketConnect() 
 * <li>JkSocketSend() 
 * <li>JkSocketReceive() 
 * <li>JkSocketShutdown() 
 * </ul>
 *
 */
JKSint32 JkSocketClose(JKSocketHandle socket);

#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */
