/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 *@file AMUDPEvent.h
 *  UDP Datagram Connection JBI
 */
/**
 * @addtogroup UDP_Connection_JBI
 * @{
 */

#ifndef __AM_UDP_EVENT_H
#define __AM_UDP_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesUDP.h"

/**
 * Notifies JBlend of the events of setup, sending, destroying a socket
 * for UDP Datagram Connection.
 * @param socket
 *      The datagram socket.
 *      Designate the handle of the datagram socket for which the event occurred.
 * @param type
 *      The event type. Designate one of the following types based
 *      on the JSI causing the event notification to be made.
 *      <dl>
 *      <dt>#JkUdpConnect()</dt>
 *      <dd>#JK_UDP_EVENT_TYPE_CONNECT</dd>
 *      <dt>#JkUdpSendTo()</dt>
 *      <dd>#JK_UDP_EVENT_TYPE_SENDTO</dd>
 *      <dt>#JkUdpClose()</dt>
 *      <dd>#JK_UDP_EVENT_TYPE_CLOSE</dd>
 *      </dl>
 * @param result
 *      Designate #JK_UDP_SUCCESS if the operation succeeded.
 *      If the operation failed or if #JkUdpClose() was called canceling the
 *      processing, designate #JK_UDP_ERROR_OTHER.
 */
void AmNotifyUdpEvent( JKUdpHandle socket, JKSint32 type, JKSint32 result );

/**
 * Notifies JBlend of the event of receiving for UDP Datagram Connection.
 * @param socket
 *      The datagram socket.
 *      Designate the handle of the datagram socket for which the event occurred.
 * @param result
 *      Designate the size in bytes of actually received data if the operation
 *      succeeded.
 *      If the operation failed or if #JkUdpClose() was called canceling the
 *      processing, designate #JK_UDP_ERROR_OTHER.
 * @param addrLen
 *      Designate the length in bytes of the remote IP address
 *      or host name stored in the buffer pointed to by the <i>addressBuf</i> 
 *      parameter of #JkUdpReceiveFrom() if the operation succeeded. 
 *      If the operation failed or if #JkUdpClose() was called canceling the
 *      processing, designate any value.
 * @param port
 *      Designate the port number of the remote end if the operation succeeded.
 *      If the operation failed or if #JkUdpClose() was called canceling the
 *      processing, designate any value.
 *
 * By this function, notify JBlend of the result of receive processing of 
 * #JkUdpReceiveFrom(). 
 * If #JK_UDP_ERROR_OTHER is assigned to the <i>result</i> parameter, the values assigned
 * to the <i>addrLen</i> and <i>port</i> parameters are ignored.
 */
void AmNotifyUdpReceived( JKUdpHandle socket, JKSint32 result, JKSint32 addrLen, JKSint32 port );


/**
 * Notifies JBlend of the event of checking the validity of a host name.
 * @param result
 *      Designate #JK_TRUE if the host name is valid,
 *      or #JK_FALSE if it is invalid or the operation failed.
 *
 * By this function, notify JBlend of the result of checking the validity of a 
 * host name by #JkUdpQueryHostname.
 *
 */
void AmPostUdpQueryResult( JKBool result );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
