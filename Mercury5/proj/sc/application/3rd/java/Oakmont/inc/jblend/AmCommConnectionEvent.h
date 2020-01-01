/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file AmCommConnectionEvent.h
 *  CommConnection JBI
 */
/**
 * @addtogroup Comm_Connection_JBI
 * @{
 */

#ifndef ___AM_COMM_EVENT_H
#define ___AM_COMM_EVENT_H

#include "JkTypesCommConnection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Notifies JBlend of an event occurring in serial communication. 
 *
 * @param handle The handle of the serial connection. Designate the handle of the serial connection in which the event has occurred.
 *
 * @param event  The type of the event. Designate one of the following types based on the JSI function causing the event notification. 
 *              <dl>
 *               <dt>#JkCommConnect()
 *                <dd>#JK_COMM_EVENT_CONNECT</dd>
 *               <dt>#JkCommRead()
 *                <dd>#JK_COMM_EVENT_READ</dd>
 *               <dt>#JkCommWrite()
 *                <dd>#JK_COMM_EVENT_WRITE</dd>
 *               <dt>#JkCommDisconnect()
 *                <dd>#JK_COMM_EVENT_DISCONNECT</dd>
 *               <dt><b>Disconnection of the Communication Line</b><br>
 *                <dd>#JK_COMM_EVENT_STATECHANGED</dd>
 *              </dl>
 *
 * @param result The result of the event. Designate one of the following types based on the JSI function causing the event notification.
 *             <dl>
 *             <dt>#JkCommConnect()
 *              <dd>Designate #JK_COMM_RESULT_SUCCESS or an appropriate error code if it failed.
 *              </dd>
 *             <dt>#JkCommRead()
 *              <dd>Designate the size (in bytes) of actually received data or an appropriate error code if it failed.
 *              </dd>
 *             <dt>#JkCommWrite()
 *              <dd>Designate the size (in bytes) of actually sent data or an appropriate error code if it failed.
 *              </dd>
 *             <dt>#JkCommDisconnect()
 *              <dd>Designate #JK_COMM_RESULT_SUCCESS or an appropriate error code if it failed.
 *              </dd>
 *             <dt><b>Disconnection of the Communication Line</b>
 *              <dd>Designate #JK_COMM_RESULT_DISCONNECTED when the native system detects the disconnection of the communication line.
 *              </dd>
 *             </dl>
 *
 * When the native system detects the disconnection of the communication line while it is not processing any of 
 * #JkCommConnect(), #JkCommRead(), #JkCommWrite() or #JkCommDisconnect(), it must notify JBlend of the disconnection 
 * by using this function, passing #JK_COMM_EVENT_STATECHANGED in the <i>event</i> parameter and 
 * #JK_COMM_RESULT_DISCONNECTED in the <i>result</i> parameter.
 *
 */
void AmNotifyCommEvent(JKCommHandle handle, JKSint32 event, JKSint32 result);

#ifdef __cplusplus
}
#endif

#endif /* ___AM_COMM_EVENT_H */

/**
 * @} end of group
 */
