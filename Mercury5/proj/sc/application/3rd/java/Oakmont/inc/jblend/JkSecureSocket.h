/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkSecureSocket.h
 *  Secure Connection JSI
 */
/**
 * @addtogroup Secure_Connection_JSI
 * @{
 */

#ifndef ___JKSECURESOCKET_H
#define ___JKSECURESOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSecureSocket.h"

/**
 *         Gets the maximum number of simultaneous secure socket connections.
 * @return Return the maximum number of sockets that can be connected
 *         at the same time in the native system.
 *
 * This function is called only once, at JVM startup.
 *
 * JBlend will not request the creation or connection of a secure
 * socket if it would exceed the limit returned by this function for
 * simultaneous secure socket connections.
 */
JKSint32 JkSecureSocketGetMaxSessions(void);

/**
 *         Creates a secure socket.
 * @param  address
 *         A pointer to the buffer holding the string indicating a remote address.
 *         The string is not terminated by '\0'. This pointer remains valid
 *         until the function returns control to JBlend.
 * @param  addressLength
 *         The length in bytes of the remote address string held in the
 *         buffer pointed to by the <i>address</i> parameter.
 * @param  port
 *         The remote port number.
 * @return Return a handle uniquely identifying the created secure socket,
 *         or  #JK_INVALID_HANDLE in case of error.
 *
 * JBlend calls this function to create a secure socket that connects to
 * the remote end which is indicated by the <i>port</i> and <i>address</i> parameter.
 * Assign and return a handle value
 * uniquely identifying the created secure socket, enabling other functions to
 * designate the secure socket when performing operations on it. The handle should
 * remain valid until #JkSecureSocketClose() is called.
 *
 * When this function is called, make the necessary preparations in the native
 * system for secure socket communication. Note that processing likely to
 * block JBlend processing for an extended period must not be performed in this
 * function.
 */
JKSecureSocketHandle JkSecureSocketOpen(const JKSint8 *address, JKSint32 addressLength, JKSint32 port);

/**
 *         Sets up a secure socket connection.
 * @param  socket
 *         The handle of the secure socket. The return value of
 *         JkSecureSocketOpen() is designated.
 * @return If the connection succeeds, return #JK_SECURESOCKET_SUCCESS.
 *         In case of error, return either of the following error codes
 *         as appropriate.
 *           - #JK_SECURESOCKET_ERROR_TIMEOUT
 *           - #JK_SECURESOCKET_ERROR_OTHER
 *           .
 *
 * In the native system, connect the secure socket designated in the
 * <i>socket</i> parameter to the remote end and establish an SSL session,
 * enabling communication on that connection.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the connection processing. After requesting connection processing by
 * the separate task, return control to JBlend, using #JK_SECURESOCKET_SUCCESS
 * as the return value. 
 * If an error occurred before connection processing by the separate task could
 * be requested, return one of the error codes below depending on the error cause. 
 *   - #JK_SECURESOCKET_ERROR_TIMEOUT
 *   - #JK_SECURESOCKET_ERROR_OTHER
 *   .
 *
 * If #JK_SECURESOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySecureSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Socket connection and SSL session establishment succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_SECURESOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkSecureSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SECURESOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_SECURESOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>SSL session establishment failed because the server sent an invalid server certificate.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SECURESOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: One of the following error codes as appropriate
 *         - #JK_SECURESOCKET_ERROR_CERT_BAD_EXTENSIONS
 *         - #JK_SECURESOCKET_ERROR_CERT_CHAIN_TOO_LONG
 *         - #JK_SECURESOCKET_ERROR_CERT_EXPIRED
 *         - #JK_SECURESOCKET_ERROR_CERT_UNAUTHORIZED_INTERMEDIATE_CA
 *         - #JK_SECURESOCKET_ERROR_CERT_MISSING_SIGNATURE
 *         - #JK_SECURESOCKET_ERROR_CERT_NOT_YET_VALID
 *         - #JK_SECURESOCKET_ERROR_CERT_SITENAME_MISMATCH
 *         - #JK_SECURESOCKET_ERROR_CERT_UNRECOGNIZED_ISSUER
 *         - #JK_SECURESOCKET_ERROR_CERT_UNSUPPORTED_SIGALG
 *         - #JK_SECURESOCKET_ERROR_CERT_INAPPROPRIATE_KEY_USAGE
 *         - #JK_SECURESOCKET_ERROR_CERT_BROKEN_CHAIN
 *         - #JK_SECURESOCKET_ERROR_CERT_ROOT_CA_EXPIRED
 *         - #JK_SECURESOCKET_ERROR_CERT_UNSUPPORTED_PUBLIC_KEY_TYPE
 *         - #JK_SECURESOCKET_ERROR_CERT_VERIFICATION_FAILED
 *         .
 *      If there were multiple errors, pass the most noteworthy error code.
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_SECURESOCKET_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySecureSocketEvent() may be called either in this function or
 * from the separate task. If after requesting connection processing by a
 * separate task, the connection is successfully set up before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifySecureSocketEvent() before passing control to
 * JBlend.
 *
 * If a value other than #JK_SECURESOCKET_SUCCESS is returned, do not make event
 * notification by  #AmNotifySecureSocketEvent().
 *
 * If the connection and SSL session establishment succeeded and
 * #JK_SECURESOCKET_SUCCESS is returned, JBlend assumes that the <code>SecureConnection</code>
 * security information and server certificate information can be acquired.
 * In the native system, enable acquisition of security information and
 * server certificate information using the following JSI functions, during the interval
 * after event notification to JBlend until #JkSecureSocketClose() is called.
 *
 * <ul>
 * <li>All the JSI functions defined in @ref Secure_Connection_Cert_JSI
 * <li>JkSecureSocketGetProtocol()
 * <li>JkSecureSocketGetCipherSuite()
 * </ul>
 *
 * If an event is passed because of a server certificate error, JBlend calls
 * all the JSI functions defined in @ref Secure_Connection_Cert_JSI and gets
 * information about the invalid server certificate. The native system must pass
 * the server certificate information to JBlend.
 *
 */
JKSint32 JkSecureSocketConnect(JKSecureSocketHandle socket);

/**
 *         Sends data to a secure socket in connected state.
 * @param  socket
 *         The handle of the secure socket. The return value of
 *         JkSecureSocketOpen() is designated.
 * @param  data
 *         A pointer to the buffer holding the data to be sent. This
 *         pointer remains valid until the result of this function
 *         call is notified to JBlend in an event.
 * @param  dataLength
 *         The size of send data (in bytes).
 * @return Return #JK_SECURESOCKET_SUCCESS if the operation succeeds.
 *         In case of error, return either of the following error
 *         codes as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * In the native system, send the data indicated by the <i>data</i> parameter 
 * to the secure socket connection remote end.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the transmission processing. After requesting transmission processing by
 * the separate task, return control to JBlend, using #JK_SECURESOCKET_SUCCESS
 * as the return value. 
 * If an error occurred before send processing by the separate task could be 
 * requested, return one of the error codes below depending on the error cause.
 *   - #JK_SECURESOCKET_ERROR_TIMEOUT
 *   - #JK_SECURESOCKET_ERROR_OTHER
 *   .
 *
 * If #JK_SECURESOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySecureSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Send processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: The size of data actually sent
 *   </ul>
 * If the value passed in <i>result</i> is smaller than the send size requested by
 * #JkSecureSocketSend(), JBlend repeats the cycle of calling this function and
 * waiting for an event, until all data sending is complete. 
 * </dd>
 * <p>
 * <dt>The connection was closed by the peer, or was already closed.</dt>
 * <dt>The processing was canceled by #JkSecureSocketClose().</dt>
 * <dt>#JkSecureSocketShutdown() was called passing #JK_SECURESOCKET_SHUTDOWN_SEND
 * in the <i>how</i> parameter, canceling the processing. </dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: #JK_SECURESOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SEND
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #JK_SECURESOCKET_ERROR_TIMEOUT
 *       - #JK_SECURESOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySecureSocketEvent() may be called either in this function or from
 * the separate task. If after requesting transmission processing by a separate
 * task, the transmission is successfully performed before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifySecureSocketEvent() before passing control to
 * JBlend.
 *
 * If a value other than #JK_SECURESOCKET_SUCCESS is returned, do not make event
 * notification by  #AmNotifySecureSocketEvent().
 *
 * This function is never called again for the same secure socket until its
 * result is returned. It may, however, be called for a different secure socket.
*/
JKSint32 JkSecureSocketSend(JKSecureSocketHandle socket, const JKUint8 *data, JKSint32 dataLength);

/**
 *         Receives data from a secure socket in connected state.
 * @param  socket
 *         The handle of the secure socket. The return value of
 *         JkSecureSocketOpen() is designated.
 * @param  data
 *         A pointer to a buffer for putting the received data.
 *         This pointer remains valid until the result of this
 *         function is passed to JBlend in an event.
 * @param  dataLength
 *         The size (in bytes) of the buffer indicated by the
 *         <i>data</i> parameter.
 * @return Return #JK_SECURESOCKET_SUCCESS if the operation succeeds.
 *         In case of error, return either of the following error codes
 *         as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * In the native system, put the data received from the secure socket connection
 * remote end to the buffer pointed to by the <i>data</i> parameter.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the receipt processing. After requesting receipt processing by
 * the separate task, return control to JBlend, using #JK_SECURESOCKET_SUCCESS
 * as the return value. 
 * If an error occurred before receive processing by the separate task could
 * be requested, return one of the error codes below depending on the error cause.
 *   - #JK_SECURESOCKET_ERROR_TIMEOUT
 *   - #JK_SECURESOCKET_ERROR_OTHER
 *   .
 *
 * If #JK_SECURESOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySecureSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Receive processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: The size of data actually received
 *   </ul>
 * It does not matter if the data size passed in the <i>result</i> parameter
 * is smaller than the receive data size requested by #JkSecureSocketReceive().
 * </dd>
 * <p>
 * <dt>The connection was closed by the peer, or was already closed.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: 0
 *   </ul>
 * </dd>
 * <dt>#JkSecureSocketShutdown() was called passing 
 * #JK_SECURESOCKET_SHUTDOWN_RECEIVE in the <i>how</i> parameter, canceling the 
 * processing. </dt>
 * <dt>The processing was canceled by #JkSecureSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: #JK_SECURESOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_RECEIVE
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #JK_SECURESOCKET_ERROR_TIMEOUT
 *       - #JK_SECURESOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySecureSocketEvent() may be called either in this function or from the
 * separate task. If after requesting receipt processing by a separate
 * task, the receipt is successfully performed before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifySecureSocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SECURESOCKET_SUCCESS is returned, do not make event
 * notification by  #AmNotifySecureSocketEvent().
 *
 * This function is never called again for the same socket until its result
 * is returned. It may, however, be called for a different socket.
 */
JKSint32 JkSecureSocketReceive(JKSecureSocketHandle socket, JKUint8 *data, JKSint32 dataLength);

/**
 *         Gets the size of received data that can be acquired
 *         without I/O blocking.
 * @param  socket
 *         The handle of the secure socket. The value returned by
 *         #JkSecureSocketOpen() is designated.
 * @return Return the size of received data that JBlend can acquire
 *         without I/O blocking. In case of error, return either of the
 *         following error codes as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * This function should return control to JBlend as quickly as possible, to
 * avoid blocking JBlend processing for an extended period.
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 *  #JkSecureSocketClose() is called.
 */
JKSint32 JkSecureSocketAvailable(JKSecureSocketHandle socket);

/**
 *         Shuts down a secure socket.
 * @param  socket
 *         The handle of the secure socket. The value returned by
 *         #JkSecureSocketOpen() is designated.
 * @param  how
 *         The direction of communication to be shut down. One of the
 *         following values is designated.
 *          - #JK_SECURESOCKET_SHUTDOWN_SEND
 *          - #JK_SECURESOCKET_SHUTDOWN_RECEIVE
 *          - #JK_SECURESOCKET_SHUTDOWN_BOTH
 *          .
 * @return Return #JK_SECURESOCKET_SUCCESS if the operation succeeds.
 *         In case of error, return either of the following error codes
 *         as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * JBlend calls this function with the <i>how</i> parameter set to
 * the values shown in the table below, in response to the invocation of
 * the <code>close</code> method of <code>InputStream</code> or
 * <code>OutputStream</code>. In the native system, shut down the
 * secure socket communication for the direction(s) designated in the <i>how</i>
 * parameter.
 *
 * <table border="1">
 * <tr><td><code>InputStream##close<code></td><td>#JK_SECURESOCKET_SHUTDOWN_RECEIVE</td></tr>
 * <tr><td><code>OutputStream##close<code></td><td>#JK_SECURESOCKET_SHUTDOWN_SEND</td></tr>
 * <tr><td>(*)<code>SecureConnection##close</code></td><td>#JK_SECURESOCKET_SHUTDOWN_BOTH</td></tr>
 * </table>
 * (*)When <code>SecureConnection</code> is closed in the state where neither
 * <code>InputStream</code> nor <code>OutputStream</code> is opened.
 *
 * This function is called during the time after the calling of #JkSecureSocketConnect()
 * and until #JkSecureSocketClose() is called.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the shut down processing. After requesting shut down processing by
 * the separate task, return control to JBlend, using  #JK_SECURESOCKET_SUCCESS
 * as the return value. 
 * If an error occurred before shutdown processing by the separate task could be
 * requested, return one of the error codes below depending on the error cause.
 *   - #JK_SECURESOCKET_ERROR_TIMEOUT
 *   - #JK_SECURESOCKET_ERROR_OTHER
 *   .
 *
 * If #JK_SECURESOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySecureSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Shutdown succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #JK_SECURESOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkSecureSocketClose().</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: #JK_SECURESOCKET_ERROR_OTHER
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_SHUTDOWN
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #JK_SECURESOCKET_ERROR_TIMEOUT
 *       - #JK_SECURESOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifySecureSocketEvent() may be called either in this function or from the
 * separate task. If after requesting shut down processing by a separate
 * task, the shut down is successfully performed before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifySecureSocketEvent() before passing control to JBlend.
 *
 * If a value other than #JK_SECURESOCKET_SUCCESS is returned, do not make event
 * notification by  #AmNotifySecureSocketEvent().
 *
 * According to the MIDP 2.0 specification, it is recommended that the
 * blocking of the Java thread which is performing send operation or
 * receive operation should be released if the <code>InputStream</code>
 * or <code>OutputStream</code> <code>close</code> method is called
 * in the middle of the operation by other Java thread.
 * In secure socket shutdown operation, the blocking behavior of the Java thread
 * which is performing send operation or receive operation depends on that
 * of the native system.
 */
JKSint32 JkSecureSocketShutdown(JKSecureSocketHandle socket, JKSint32 how);

/**
 *         Disconnects a connected secure socket and destroys the secure socket.
 * @param  socket
 *         The handle of the secure socket. The value returned by
 *         #JkSecureSocketOpen() is designated.
 * @return Return #JK_SECURESOCKET_SUCCESS if the operation succeeds.
 *         In case of error, return either of the following error codes
 *         as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * In the native system, disconnect the secure socket from the remote end, then
 * destroy the secure socket and free its resources.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the disconnection and destruction processing. After requesting
 * disconnection and destruction processing by the separate task,
 * return control to JBlend, using  #JK_SECURESOCKET_SUCCESS
 * as the return value. 
 * If an error occurred before socket disconnect and destroy processing by the 
 * separate task could be requested, return one of the error codes below depending 
 * on the error cause.
 *   - #JK_SECURESOCKET_ERROR_TIMEOUT
 *   - #JK_SECURESOCKET_ERROR_OTHER
 *   .
 *
 * If #JK_SECURESOCKET_SUCCESS is passed as the return value, call 
 * #AmNotifySecureSocketEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Socket disconnect and destroy processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #JK_SECURESOCKET_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed.</dt>
 * <dd>Pass parameter values to #AmNotifySecureSocketEvent() as follows.
 *   <ul>
 *     <li><i>type</i>: #JK_SECURESOCKET_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: One of the following error codes depending on the error cause
 *       - #JK_SECURESOCKET_ERROR_TIMEOUT
 *       - #JK_SECURESOCKET_ERROR_OTHER
 *       .
 *   </ul>
 * </dd>
 * </dl>
 * #AmNotifySecureSocketEvent() may be called either in this function or from the
 * separate task. If after requesting disconnection and destruction processing
 * by a separate task, the disconnection and destruction is successfully
 * performed before control is passed from this function to JBlend,
 * there is no problem with making event notification by #AmNotifySecureSocketEvent()
 * before passing control to JBlend.
 *
 * If a value other than #JK_SECURESOCKET_SUCCESS is returned, do not make event
 * notification by  #AmNotifySecureSocketEvent().
 *
 * If communication (e.g., data sending/receipt) is in progress when this
 * function is called, cut off the communication with the remote end.
 *
 * If at the time this function is called, the processing result for the 
 * functions indicated below has not yet been notified, make event 
 * notification also for the result of processing requested by these 
 * functions.
 * <ul>
 * <li>JkSecureSocketConnect()
 * <li>JkSecureSocketSend()
 * <li>JkSecureSocketReceive()
 * <li>JkSecureSocketShutdown()
 * </ul>
 *
 */
JKSint32 JkSecureSocketClose(JKSecureSocketHandle socket);

/**
 *        Gets a secure socket connection remote address.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param address
 *        A pointer to the buffer holding the remote IP address
 *        or host name. Do not append '\0' as string termination.
 *        This pointer remains valid until the function returns
 *        control to JBlend.
 * @param addressLength
 *        The size (in bytes) of the buffer indicated by the
 *        <i>address</i> parameter.
 * @return
 *        Return the length in bytes of the string put in the
 *        buffer indicated by the <i>address</i> parameter.
 *        In case of error, return either of the following error
 *        codes as appropriate.
 *          - #JK_SECURESOCKET_ERROR_TIMEOUT
 *          - #JK_SECURESOCKET_ERROR_OTHER
 *          .
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 */
JKSint32 JkSecureSocketGetAddress(JKSecureSocketHandle socket, JKSint8 *address, JKSint32 addressLength);

/**
 *        Gets the secure socket connection remote port number.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @return
 *        Return the remote port number (0 < n <= 65535).
 *        In case of error, return either of the following error
 *        codes as appropriate.
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 */
JKSint32 JkSecureSocketGetPort(JKSecureSocketHandle socket);

/**
 *        Gets a secure socket connection local IP address.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param address
 *        A pointer to a buffer for putting the IP address.
 *        Do not append '\0' as string termination.
 *        This pointer remains valid until the function returns
 *        control to JBlend.
 * @param addressLength
 *        The size (in bytes) of the buffer indicated by the
 *        <i>address</i> parameter.
 * @return
 *        Return the length in bytes of the string
 *        put in the buffer indicated by the <i>address</i>
 *        parameter.
 *        In case of error, return either of the following error
 *        codes as appropriate.
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 */
JKSint32 JkSecureSocketGetLocalAddress(JKSecureSocketHandle socket, JKSint8 *address, JKSint32 addressLength);

/**
 *        Gets the secure socket connection local port number.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @return
 *        Return the port number (0 < n <= 65535).
 *        In case of error, return either of the following error
 *        codes as appropriate.
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 */
JKSint32 JkSecureSocketGetLocalPort(JKSecureSocketHandle socket);

/**
 *        Gets the settings for options controlling secure socket
 *        behavior.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param option
 *        The option to be returned. Any of the following is designated.
 *         - #JK_SECURESOCKET_OPTION_DELAY
 *         - #JK_SECURESOCKET_OPTION_KEEPALIVE
 *         - #JK_SECURESOCKET_OPTION_LINGER
 *         - #JK_SECURESOCKET_OPTION_RCVBUF
 *         - #JK_SECURESOCKET_OPTION_SNDBUF
 *         .
 * @return
 *        If the operation succeeds, return the current setting for
 *        the option designated by the <i>option</i> parameter.  Return
 *        values for each of the options indicated in the <i>option</i>
 *        parameter as follows. <br><br>
 *         <dl>
 *         <dt> #JK_SECURESOCKET_OPTION_DELAY
 *           <dd>Return whether the Nagle algorithm is enabled (1) or
 *               disabled (0).
 *           </dd>
 *         <dt> #JK_SECURESOCKET_OPTION_KEEPALIVE
 *           <dd>Return whether the KEEPALIVE function is enabled (1)
 *               or disabled (0).
 *           </dd>
 *         <dt> #JK_SECURESOCKET_OPTION_LINGER
 *           <dd>Return the linger time (in seconds).
 *               If the linger operation is disabled, return 0.
 *           </dd>
 *         <dt> #JK_SECURESOCKET_OPTION_RCVBUF
 *           <dd>Return the data receive buffer size (in bytes).
 *           </dd>
 *         <dt> #JK_SECURESOCKET_OPTION_SNDBUF
 *           <dd>Return the data send buffer size (in bytes).
 *           </dd>
 *         </dl><br>
 *         In case of error, return either of the following error codes
 *         as appropriate.
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 *
 * The initial settings of secure socket options are implementation dependent.
 */
JKSint32 JkSecureSocketGetOption(JKSecureSocketHandle socket, JKSint32 option);

/**
 *        Sets options controlling secure socket behavior.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param option
 *        The option to be set. Any of the following is designated.
 *         - #JK_SECURESOCKET_OPTION_DELAY
 *         - #JK_SECURESOCKET_OPTION_KEEPALIVE
 *         - #JK_SECURESOCKET_OPTION_LINGER
 *         - #JK_SECURESOCKET_OPTION_RCVBUF
 *         - #JK_SECURESOCKET_OPTION_SNDBUF
 *         .
 * @param value
 *        The value to be set in the option designated by the
 *        <i>option</i> parameter.
 * @return
 *        Return #JK_SECURESOCKET_SUCCESS if the operation succeeds.
 *        In case of error, return either of the following error codes
 *        as appropriate.
 *         - #JK_SECURESOCKET_ERROR_TIMEOUT
 *         - #JK_SECURESOCKET_ERROR_OTHER
 *         .
 *
 * In the native system, set the designated socket option for the secure socket
 * designated in the <i>socket</i> parameter. Set the <i>value</i> parameter
 * for the option indicated by the <i>option</i> parameter as follows.
 * <dl>
 *   <dt>#JK_SECURESOCKET_OPTION_DELAY
 *   <dd>Sets the Nagle algorithm to enabled (1) or disabled (0).</dd>
 *   <dt>#JK_SECURESOCKET_OPTION_KEEPALIVE
 *   <dd>Sets the KEEPALIVE function to enabled (1) or disabled (0).</dd>
 *   <dt>#JK_SECURESOCKET_OPTION_LINGER
 *   <dd>Sets linger time (in seconds).<br>
 *       If <i>value</i>=0, disable linger operation.</dd>
 *   <dt>#JK_SECURESOCKET_OPTION_RCVBUF
 *   <dd>Sets the data receive buffer size (in bytes).</dd>
 *   <dt>#JK_SECURESOCKET_OPTION_SNDBUF
 *   <dd>Sets the data send buffer size (in bytes).</dd>
 * </dl>
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkSecureSocketConnect() and until
 * #JkSecureSocketClose() is called.
 *
 */
JKSint32 JkSecureSocketSetOption(JKSecureSocketHandle socket, JKSint32 option, JKSint32 value);

/**
 *        Gets the name of the protocol used for communication.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @return
 *        Return either of the following codes if the operation succeeds.<br>
 *        SSL protocol Version 3.0 :<br>&nbsp;&nbsp;&nbsp;&nbsp;
 *            #JK_SECURITY_INFO_PROTOCOL_SSL<br>
 *        TLS protocol Version 1.0 (RFC2818) or
 *        WAP TLS Profile and Tunneling Specification :<br>&nbsp;&nbsp;&nbsp;&nbsp;
 *            #JK_SECURITY_INFO_PROTOCOL_TLS<br>
 *        In case of error, return #JK_SECURESOCKET_ERROR_OTHER.
 *
 * This function is called to get the name of the communication protocol
 * used for the designated secure socket connection.
 */
JKSint32 JkSecureSocketGetProtocol(JKSecureSocketHandle socket);

/**
 *        Gets the CipherSuite used for communication.
 * @param socket
 *        The handle of the secure socket. The value returned by
 *        #JkSecureSocketOpen() is designated.
 * @param data
 *        If a value other than #JK_NULL (length=0) is designated, put the name of
 *        the CipherSuite in the memory area indicated by the <i>data</i> parameter.
 * @param length
 *        The maximum length in characters of the name string
 *        that can be put in the buffer indicated by the <i>data</i>
 *        parameter.
 * @return
 *      - If the <i>data</i> parameter is #JK_NULL (length=0), return the
 *        number of characters in the CipherSuite character string (not
 *        including termination code).
 *      - If <i>data</i> is not #JK_NULL (length=0), and the CipherSuite was
 *         successfully obtained and stored, return #JK_SECURESOCKET_SUCCESS;
 *        if the CipherSuite could not be obtained, return
 *        #JK_SECURESOCKET_ERROR_OTHER.
 *      .
 *
 * This function is called to get the security information CipherSuite used on
 * the designated secure socket.
 * When the MIDlet calls the <code>SecurityInfo\#getCipherSuite</code> method,
 * JBlend returns the name string acquired by this function without modification.
 *
 * As the CipherSuite, store a string defined in the CipherSuite definition
 * table in Appendix C. CipherSuite definitions, in RFC2246 "The TLS Protocol
 * Version 1.0."
 * If a protocol other than TLS 1.0 is used, choose a CipherSuite from the
 * CipherSuite definition table that corresponds to the combination of key
 * exchange, cipher and hash used.
 * If the combination of key exchange, cipher and hash is not found in the
 * CipherSuite definition table, store a string consisting of upper-case
 * letters and numerals in the format, "(key exchange)_(cipher)_(hash)."
 */
JKSint32 JkSecureSocketGetCipherSuite(JKSecureSocketHandle socket, JKWChar *data, JKSint32 length);


#ifdef __cplusplus
}
#endif

#endif  /* ___JKSECURESOCKET_H */

/**
 * @} end of group
 */
