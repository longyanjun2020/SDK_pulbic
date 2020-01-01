/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMSecureSocketEvent.h
 *  Secure Connection JBI
 */
/**
 * @addtogroup Secure_Connection_JBI
 * @{
 */
#ifndef ___AMSECURESOCKETEVENT_H
#define ___AMSECURESOCKETEVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesSecureSocket.h"

/**
 *        Notifies JBlend of an event occurring in secure socket communication.
 * @param socket
 *        The secure socket connection. Designate the handle
 *        of the secure socket connection in which the event has
 *        occurred.
 * @param type
 *        The type of the event. Designate one of the following
 *        types based on the JSI function causing the event
 *        notification.
 *        <dl>
 *         <dt>#JkSecureSocketConnect()
 *          <dd>#JK_SECURESOCKET_EVENT_TYPE_CONNECT</dd>
 *         <dt>#JkSecureSocketSend()
 *          <dd>#JK_SECURESOCKET_EVENT_TYPE_SEND</dd>
 *         <dt>#JkSecureSocketReceive()
 *          <dd>#JK_SECURESOCKET_EVENT_TYPE_RECEIVE</dd>
 *         <dt>#JkSecureSocketShutdown()
 *          <dd>#JK_SECURESOCKET_EVENT_TYPE_SHUTDOWN</dd>
 *         <dt>#JkSecureSocketClose()
 *          <dd>#JK_SECURESOCKET_EVENT_TYPE_CLOSE</dd>
 *        </dl>
 *
 * @param result
 *        The result of the event. Designate one of the following
 *        types based on the JSI function causing the event
 *        notification.
 *        <dl>
 *         <dt>#JkSecureSocketConnect()
 *          <dd>Designate #JK_SECURESOCKET_SUCCESS if the operation succeeded. 
 *              If the operation failed, designate one of the following values as appropriate. <br>
 *               - #JK_SECURESOCKET_ERROR_TIMEOUT
 *               - #JK_SECURESOCKET_ERROR_OTHER
 *               - an appropriate error code of those named starting with #JK_SECURESOCKET_ERROR_CERT_
 *               .
 *          </dd>
 *         <dt>#JkSecureSocketSend()
 *          <dd>Designate the size (in bytes) of data actually sent if the operation succeeded.
 *              If the operation failed, designate one of the following values as appropriate. <br>
 *               - #JK_SECURESOCKET_ERROR_TIMEOUT
 *               - #JK_SECURESOCKET_ERROR_OTHER
 *               .
 *          </dd>
 *         <dt>#JkSecureSocketReceive()
 *          <dd>Designate the size (in bytes) of data actually received if the operation succeeded.
 *              If the operation failed, designate one of the following values as appropriate. <br>
 *               - #JK_SECURESOCKET_ERROR_TIMEOUT
 *               - #JK_SECURESOCKET_ERROR_OTHER
 *               .
 *          </dd>
 *         <dt>#JkSecureSocketShutdown()
 *          <dd>Designate #JK_SECURESOCKET_SUCCESS if the operation succeeded.
 *              If the operation failed, designate one of the following values as appropriate. <br>
 *               - #JK_SECURESOCKET_ERROR_TIMEOUT
 *               - #JK_SECURESOCKET_ERROR_OTHER
 *               .
 *          </dd>
 *         <dt>#JkSecureSocketClose()
 *          <dd>Designate #JK_SECURESOCKET_SUCCESS  if the operation succeeded.
 *              If the operation failed, designate one of the following values as appropriate. <br>
 *               - #JK_SECURESOCKET_ERROR_TIMEOUT
 *               - #JK_SECURESOCKET_ERROR_OTHER
 *               .
 *          </dd>
 *         </dl>
 */
void AmNotifySecureSocketEvent(JKSecureSocketHandle socket, JKSint32 type, JKSint32 result);

#ifdef __cplusplus
}
#endif

#endif  /* ___AMSECURESOCKETEVENT_H */

/**
 * @} end of group
 */

