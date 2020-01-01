/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 *@file JkUDP.h
 *  Datagram Connection JSI
 */
/**
 * @addtogroup UDP_Connection_JSI
 * @{
 */
#ifndef __JK_UDP_H
#define __JK_UDP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesUDP.h"


/**
 * Gets the maximum number of simultaneous datagram socket connections.
 * @return Return the maximum number of sockets that can be connected
 *         at the same time in the native system.
 *
 * This function is called only once, at JVM startup.
 *
 * JBlend will not request the creation or connection of a datagram socket
 * if it would exceed the limit returned by this function for simultaneous
 * datagram socket connections.
 */
JKSint32 JkUdpGetMaxSessions( void );

/**
 * Creates a datagram socket.
 * @param address
 *      A pointer to a buffer holding the string of the host name in the URL
 *      which a MIDlet designates in the URL parameter of
 *      <code>javax.microedition.io.Connector.open</code> method.
 *      If the host name in the URL is omitted, #JK_NULL is set.
 *      The string does not terminate with '\0'. This pointer remains valid
 *      until the function returns control to JBlend.
 * @param addressLength
 *      The length in bytes of the host name designated in the parameter passed to 
 *      <code>javax.microedition.io.Connector.open</code> method.
 * @param  port
 *      The local port number for receiving data.
 * @return
 *      Return a handle uniquely identifying the created datagram socket,
 *      or #JK_INVALID_HANDLE in case of error.
 *
 * JBlend calls this function to create a datagram socket using the port number
 * designated in the <i>port</i> parameter.  Assign and return a handle value
 * uniquely identifying the created datagram socket, enabling other functions 
 * to designate the datagram socket when performing operations on it.
 * The handle should remain valid until #JkUdpClose() is called.
 *
 * JBlend sets -1 as the value of the <i>port</i> parameter when a MIDlet 
 * makes the following URL designation in the <i>name</i> parameter of 
 * <code>javax.microedition.io.Connector.open</code> method.
 * - Neither a host name nor a port number has been designated.
 * - Both a host name and a port number have been designated. 
 *
 * In this case, create a datagram socket assigning an appropriate
 * port number in the native system.
 *
 * When this function is called, make the necessary preparations in the
 * native system for datagram socket communication.
 * But, the processing likely to block JBlend processing for an extended
 * period must not perform in this function.
 */
JKUdpHandle JkUdpOpen( const JKSint8* address, JKSint32 addressLength, JKSint32 port );

/**
 * Sets up a datagram socket connection.
 * @param  socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @return
 *      Return #JK_UDP_SUCCESS if the operation succeeds.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * In the native system, connect to the datagram socket designated
 * in the <i>socket</i> parameter, enabling communication on that connection.
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the connection processing. After requesting connection processing by
 * the separate task, return control to JBlend, putting  #JK_UDP_SUCCESS
 * in the return value. If an error occurs before requesting connection
 * processing by the separate task, return control to JBlend putting
 * #JK_UDP_ERROR_OTHER in the return value.
 *
 * If #JK_UDP_SUCCESS is passed as the return value, call 
 *  #AmNotifyUdpEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>The connection processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_UDP_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by #JkUdpClose().</dt>
 * <dt>The connection failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_CONNECT
 *     <li><i>result</i>: #JK_UDP_ERROR_OTHER
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyUdpEvent() may be called either in this function or from the
 * separate task. If after requesting connection processing by a separate
 * task, the connection is successfully set up before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifyUdpEvent() before passing control to JBlend.
 *
 * If a value other than #JK_UDP_SUCCESS is returned, do not make event
 * notification by  #AmNotifyUdpEvent().
 */
JKSint32 JkUdpConnect( JKUdpHandle socket );

/**
 * Destroys the datagram socket.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @return
 *      Return #JK_UDP_SUCCESS if the operation succeeds.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * In the native system, destroy the datagram socket and free its resources.
 * If this function is called during the data send and receive processing,
 * abort the ongoing processing.
 * 
 *
 * If this function is called during the communication processing 
 * such as data send and receive processing, abort the processing.
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, a control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the disconnection and destruction processing. After requesting
 * disconnection and destruction processing by the separate task,
 * return control to JBlend, putting  #JK_UDP_SUCCESS
 * in the return value. If an error occurs before requesting
 * disconnection and destruction processing by the separate task,
 * return control to JBlend putting #JK_UDP_ERROR_OTHER in the
 * return value.
 *
 * If #JK_UDP_SUCCESS is passed as the return value, call 
 *  #AmNotifyUdpEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Socket disconnect and destroy processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #JK_UDP_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>Processing failed.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_CLOSE
 *     <li><i>result</i>: #JK_UDP_ERROR_OTHER
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyUdpEvent() may be called either in this function or from the
 * separate task. If after requesting disconnection and destruction processing
 * by a separate task, the disconnection and destruction is successfully
 * performed before control is passed from this function to JBlend,
 * there is no problem with making event notification by #AmNotifyUdpEvent()
 * before passing control to JBlend.
 *
 * If a value other than #JK_UDP_SUCCESS is returned, do not make event
 * notification by  #AmNotifyUdpEvent().
 *
 * If at the time this function is called, the processing result for the 
 * functions indicated below has not yet been notified, make event 
 * notification also for the result of processing requested by these 
 * functions.
 * <ul>
 * <li>JkUdpConnect()
 * <li>JkUdpSendTo()
 * <li>JkUdpReceiveFrom()
 * </ul>
 */
JKSint32 JkUdpClose( JKUdpHandle socket );

/**
 * Sends data to the designated address.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @param data
 *      A pointer to a buffer holding the data to be sent.
 *      This pointer remains valid until the result of this function is
 *      passed to JBlend in an event.
 * @param dataLength
 *      The size in bytes of the send data.
 * @param address
 *      A pointer to a buffer holding the remote IP address or host name.
 *      The string does not terminate with '\0'. This pointer remains valid
 *      until the result of this function is passed to JBlend 
 *      in an event.
 * @param addressLength
 *      The length in bytes of the remote IP address or
 *      host name.
 * @param port
 *      The remote port number
 * @return
 *      Return #JK_UDP_SUCCESS if the operation succeeds.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 *
 * In the native system, send the data pointed to by the <i>data</i> parameter
 * to the address designated by the <i>address</i> and the <i>port</i> 
 * parameters using the datagram socket.
 *
 *
 * If the processing by this function is likely to block JBlend processing
 * for an extended period, control should be returned to JBlend as soon as
 * possible, and a separate task used to perform the transmission processing.
 * After requesting transmission processing by the separate task,
 * return control to JBlend, putting  #JK_UDP_SUCCESS in the return value.
 * If an error occurs before requesting transmission processing
 * by the separate task, return control to JBlend putting #JK_UDP_ERROR_OTHER
 * in the return value.
 *
 * If #JK_UDP_SUCCESS is passed as the return value, call 
 *  #AmNotifyUdpEvent() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Send processing succeeded.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_SENDTO
 *     <li><i>result</i>: #JK_UDP_SUCCESS
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by  #JkUdpClose().</dt>
 * <dt>Sending failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to #AmNotifyUdpEvent() as follows.
 *   <ul>
 *     <li><i>type</i>:  #JK_UDP_EVENT_TYPE_SENDTO
 *     <li><i>result</i>: #JK_UDP_ERROR_OTHER
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyUdpEvent() may be called either in this function or from the
 * separate task. If after requesting transmission processing by a separate
 * task, the transmission is successfully performed before control is passed
 * from this function to JBlend, there is no problem with making event
 * notification by #AmNotifyUdpEvent() before passing control to JBlend.
 *
 * If a value other than #JK_UDP_SUCCESS is returned, do not make event
 * notification by  #AmNotifyUdpEvent().
 *
 * This function is never called again for the same datagram socket until
 * its result is returned.
 * It may, however, be called for a different datagram socket.
 */
JKSint32 JkUdpSendTo( JKUdpHandle socket, const JKUint8 *data, JKSint32 dataLength, const JKSint8 *address, JKSint32 addressLength, JKSint32 port );

/**
 * Receives data from a datagram socket.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @param data
 *      A pointer to a buffer for putting the received data.
 *      This pointer remains valid until the result of this function is passed to JBlend
 *      in an event.
 * @param dataLength
 *      The size in bytes of the buffer indicated by the <i>data</i> parameter.
 * @param address
 *      A pointer to a buffer for putting the IP address or host name of
 *      the sender of the received data.
 *      Do not append '\0' as string termination. This pointer remains valid
 *      until the result of this function is passed to JBlend 
 *      in an event.
 * @param addressLength
 *      The size in bytes of the buffer indicated by the <i>address</i> 
 *      parameter.
 * @return
 *      Return #JK_UDP_SUCCESS if the operation succeeds.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * In the native system, put the data received in the datagram socket
 * to the buffer pointed to by the <i>data</i> parameter.
 * If the size of data received is larger than the size of the buffer, 
 * store a part of data of the buffer size and discard the rest of data.
 * And store the remote IP address or the host name in the buffer pointed to by
 * the <i>address</i> parameter.
 *
 *
 * If the processing by this function is likely to block JBlend
 * processing for an extended period, control should be returned to
 * JBlend as soon as possible, and a separate task used to perform
 * the receive processing. After requesting receive processing by
 * the separate task, return control to JBlend, putting  #JK_UDP_SUCCESS
 * in the return value. If an error occurs before requesting receive
 * processing by the separate task, return control to JBlend putting
 * #JK_UDP_ERROR_OTHER in the return value.
 *
 * When #JK_UDP_SUCCESS is returned, call #AmNotifyUdpReceived() after
 * the receive processing is completed, whether successfully or not,
 * to notify JBlend of the result.
 * If the receive operation succeeds, assign the data shown below to 
 * each parameter of #AmNotifyUdpReceived().
 *
 * If #JK_UDP_SUCCESS is passed as the return value, call 
 *   #AmNotifyUdpReceived() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Receive processing succeeded.</dt>
 * <dd>Pass parameter values to  #AmNotifyUdpReceived() as follows.
 *   <ul>
 *     <li><i>result</i>: The size of data actually received
 *     <li><i>addrLen</i>: The size in bytes of the address stored in the <i>address</i> parameter
 *     <li><i>port</i>: The port number of the remote end
 *   </ul>
 * </dd>
 * <p>
 * <dt>The processing was canceled by  #JkUdpClose().</dt>
 * <dt>Receipt failed for a reason other than the above.</dt>
 * <dd>Pass parameter values to  #AmNotifyUdpReceived() as follows.
 *   <ul>
 *     <li><i>result</i>: #JK_UDP_ERROR_OTHER
 *     <li><i>addrLen</i>: Any value
 *     <li><i>port</i>: Any value
 *   </ul>
 * </dd>
 * </dl>
 *
 * #AmNotifyUdpReceived() may be called either in this function or from the
 * separate task. If after requesting receive processing by a separate
 * task, the receipt is successfully performed before control is passed
 * from this function to JBlend, there is no problem with making an event
 * notification by #AmNotifyUdpReceived() before passing control to JBlend.
 *
 * If a value other than #JK_UDP_SUCCESS is returned, do not make event
 * notification by  #AmNotifyUdpReceived().
 *
 * This function is never called again for the same datagram socket until
 * its result is returned.
 * It may, however, be called for a different datagram socket.
 */
JKSint32 JkUdpReceiveFrom( JKUdpHandle socket, JKUint8 *data, JKSint32 dataLength,
                            JKSint8 *address, JKSint32 addressLength);

/**
 * Gets a datagram socket connection local IP address.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @param address
 *      A pointer to a buffer for putting the IP address.
 *      Do not append '\0' as string termination. The pointer remains valid
 *      until the function returns control to JBlend.
 * @param addressLength
 *      The size in bytes of the buffer pointed to by the <i>address</i> 
 *      parameter.
 * @return
 *      Return the length in bytes of the string put in the buffer indicated
 *      by the <i>address</i> parameter.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkUdpConnect() and until #JkUdpClose() is
 * called.
 */
JKSint32 JkUdpGetLocalAddress( JKUdpHandle socket, JKSint8 *address, JKSint32 addressLength );

/**
 * Gets the datagram socket connection local port number.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @return
 *      Return the port number (0 < n <= 65535).
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * This function is called in response to requests from a MIDlet during the
 * time after the calling of #JkUdpConnect() and until #JkUdpClose() is
 * called.
 */
JKSint32 JkUdpGetLocalPort( JKUdpHandle socket );

/**
 * Gets the nominal length of a datagram.
 * @param socket
 *      The handle of the datagram socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @return
 *      Return the nominal length of a datagram.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * This function is called in response to the requests from a MIDlet from the
 * time #JkUdpConnect() is called until #JkUdpClose() is called.
 */
JKSint32 JkUdpGetNominalLength( JKUdpHandle socket );

/**
 * Gets the maximum length of a datagram.
 * 
 * @param socket
 *      The handle of the socket.
 *      The value returned by #JkUdpOpen() is designated.
 * @return
 *      Return the maximum length which a datagram can have.
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * This function is called in response to the requests from a MIDlet from the
 * time #JkUdpConnect() is called until #JkUdpClose() is called.
 */
JKSint32 JkUdpGetMaximumLength( JKUdpHandle socket );

/**
 * Checks the validity of the remote host name of the destination.
 * @param host
 *      A pointer to a buffer holding the host name. 
 *      The string does not terminate with '\0'. 
 *      The pointer remains valid until the result of the function is passed to JBlend 
 *      in an event. 
 *
 * @param hostLength
 *      The length in bytes of the remote host name.
 *
 * @return
 *      Return #JK_UDP_SUCCESS if the operation succeeds.<br>
 *      Return #JK_UDP_UNSUPPORTED_FUNCTION if the native system does not 
 *      support this function.<br>
 *      In case of error, return #JK_UDP_ERROR_OTHER.
 *
 * This function is called by JBlend when a MIDlet currently running calls
 * the following methods.
 * - <code>UDPDatagramConnection.newDatagram(byte[] buf, int size, String addr)</code>
 * - <code>UDPDatagramConnection.newDatagram(int size, String addr)</code>
 * - <code>Datagram.setAddress(Datagram reference)</code>
 * - <code>Datagram.setAddress(String addr)</code>
 *
 * The <i>host</i> parameter is the remote host name of the 
 * destination which is included in the address designated to the methods 
 * listed above. 
 * In the native system, check the validity of the host name 
 * which the <i>host</i> parameter holds, for example, by DNS name resolution.
 * This function might be called by JBlend whether a datagram socket is
 * created by #JkUdpOpen() or not.
 *
 * If the processing by this function is likely to block JBlend processing for
 * an extended period, control should be returned to JBlend as soon as 
 * possible, and a separate task used to perform the check processing.
 * After invoking a separate task, pass #JK_UDP_SUCCESS as a return value
 * and return control to JBlend.
 * If the native system does not support this function, or if an error occurs
 * before it requests check processing to a separate task, return control 
 * to JBlend returning an appropriate error code.
 *
 * If #JK_UDP_SUCCESS is passed as the return value, call 
 *  #AmPostUdpQueryResult() at the time of any of the following occasions
 * and notify JBlend of the result.
 * <dl>
 * <dt>Host name validity was confirmed.</dt>
 * <dd>Pass parameter values to #AmPostUdpQueryResult() as follows.
 *   <ul>
 *     <li><i>result</i>: #JK_TRUE
 *   </ul>
 * </dd>
 * <p>
 * <dt>Host name is invalid.</dt>
 * <dd>Pass parameter values to #AmPostUdpQueryResult() as follows.
 *   <ul>
 *     <li><i>result</i>: #JK_FALSE
 *   </ul>
 *   When #JK_FALSE is returned in the <i>result</i> parameter, JBlend 
 *   throws <code>java.lang.IllegalArgumentException</code>.
 * </dd>
 * </dl>
 *
 * #AmPostUdpQueryResult() can be called either in this function or in
 * a separate task. 
 * After requesting the check processing to a separate task,
 * if this processing is successfully performed before control is returned to 
 * JBlend from this function, #AmPostUdpQueryResult() can be called to make an 
 * event notification before control is returned to JBlend.
 * If a value other than #JK_UDP_SUCCESS is returned, do not make an event
 * notification by #AmPostUdpQueryResult().
 */
JKSint32 JkUdpQueryHostname( const JKSint8 *host, JKSint32 hostLength );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
