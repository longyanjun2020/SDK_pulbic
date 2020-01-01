/**
 * Copyright 2002-2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMNativeExtEvent.h
 *   Native Event JBI
 */
/**
 * @addtogroup Module_AM_Native_Ext_Event
 * @{
 */

#ifndef ___AM_NATIVEEXTEVENT_H
#define ___AM_NATIVEEXTEVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *  Passes an event which is defined by the native system to the Java class.
 *
 *  @param queueID The ID of an event queue. Designate the value returned by the 
 *                 {@link NativeExtEventReceiver#setNativeExtEventListenerR2 setNativeExtEventListenerR2} method
 *                 of the {@link NativeExtEventReceiver} class.
 *  @param event  A pointer to the JKSint32 type array holding the
 *                event information. The number of array elements
 *                should be 1 to 5.
 *  @param length The number of elements in the array designated
 *                by the event parameter. Designate a value between 1 and 5.
 *  @return       #JK_TRUE if the operation succeeds;<br>
 *                #JK_FALSE if the operation fails.
 *
 * When this function is called, JBlend puts the event information
 * in the event queue managed by
 * <code>{@link NativeExtEventReceiver com.jblned.io.NativeExtEventReceiver}
 * </code> class.
 *
 *  When an event is put in the event queue, the
 *  <code>
 *  {@link NativeExtEventListener#receiveNativeExtEvent receiveNativeExtEvent}
 *  </code> method of
 *  <code>{@link NativeExtEventListener NativeExtEventListener}</code>
 *  registered in
 *  <code>{@link NativeExtEventReceiver NativeExtEventReceiver}</code>
 *  is called.
 *
 *  It is assumed that event information is stored in the array designated by
 *  the event parameter in order, in the elements from index 0 to (length - 1).
 *  These elements are stored in the same order in the <code>int</code> array passed as a
 *  parameter to <code>
 *  {@link NativeExtEventListener#receiveNativeExtEvent receiveNativeExtEvent(int[],int)}
 *  </code>.
 *  The value designated in the <i>length</i> parameter is likewise passed
 *  transparently as event information to <code>
 *  {@link NativeExtEventListener#receiveNativeExtEvent receiveNativeExtEvent}
 *  </code>.
 *
 *  A dedicated event queue for native system-specific events does not exist initially.
 *  It is created when a <code>{@link NativeExtEventListener}</code> is
 *  registered with <code>{@link NativeExtEventReceiver}</code> using <code>
 *  {@link NativeExtEventReceiver#setNativeExtEventListenerR2 setNativeExtEventListenerR2}
 *  </code>.
 *
 */
JKBool AmNativeExtEventNotifyR2(JKSint32 queueID, const JKSint32* event, JKSint32 length);


#ifdef __cplusplus
}
#endif

#endif /* ___AM_NATIVEEXTEVENT_H */

/**
 * @} end of group
 */
