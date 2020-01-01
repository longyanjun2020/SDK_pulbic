/**
 * Copyright 2004-2007 Aplix Corporation. All rights reserved.
 */
/**
 * @file AMFileConnectionEvent.h
 *   FileConnection JBI
 */
/**
 * @addtogroup Module_FileConnection_JBI
 * @{
 */

#ifndef ___AM_FILECONNECTION_EVENT_H
#define ___AM_FILECONNECTION_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif



#include "JkFileConnectionCommon.h"


/**
 *  Event types indicating the type of change to the root structure.
 */
typedef JKSint32	AmFileConnectionRootChangedType;

   /**
    *  A constant indicating that a file system root has been added to the device.
    */
#define JK_FILECONNECTION_ROOT_ADDED	0
   /**
    *  A constant indicating that a file system root has been removed from the device.
    */
#define JK_FILECONNECTION_ROOT_REMOVED		1


/**
 * Notifies JBlend that a root on the device has changed.
 * 
 * @param type 
 *        The type of change. Set either of the following values. 
 *        - #JK_FILECONNECTION_ROOT_ADDED
 *        - #JK_FILECONNECTION_ROOT_REMOVED
 *        .
 * @param rootName
 *        A pointer to the structure holding the name string of the changed root. 
 * @return 
 *       0: The event was successfully queued. <br>
 *       A negative value: The event could not be queued because the event queue is full.
 * 
 * After JkFileConnectionStartRootChangeNotification() is called, the native system must start watching
 * the root structure, and when a change is detected, must call this function to notify JBlend of the
 * root name and the kind of change.  
 * 
 * If #JK_NULL is designated in <i>rootName</i>, this function fails and returns a negative value.
 * 
 * If this function returns a negative value when a value other than #JK_NULL was designated in <i>rootName</i>, 
 * the native system should wait for a time and then call this function again. 
 * 
 * This function may be called even while the JVM is stopped. Events notified during that
 * time are put in the event queue, but are not processed until the JVM resumes. Since
 * this may result in the event queue becoming full, the native system must make 
 * provision for such a possibility.
 * 
 * It is possible even before JkFileConnectionStartRootChangeNotification() is called to start watching for root structure changes and to
 * make event notification when a change occurs. While this will not cause problems with the behavior
 * of the JVM itself, queueing of an event may fail if no event queue has been created.
 *
 * The string passed via the <i>rootName</i> parameter must remain valid until JkFileConnectionFreeName() is called. 
 * JBlend calls JkFileConnectionFreeName() when the root change event is processed in the JVM task.
 * @see JkFileConnectionStartRootChangeNotification()
 * @see JkFileConnectionFreeName()
 * 
 */
JKSint32 AmNotifyFileConnectionRootChangedEvent(AmFileConnectionRootChangedType type,JKFileConnectionString* rootName);


/**
 * Notifies JBlend of an event indicating completion of asynchronous stream processing. 
 *
 * @param event 
 *        A pointer to the event array. 
 * @param size 
 *        The number of elements in the event array.
 * @return 
 *       0: The event was successfully queued. <br>
 *       A negative value: The event could not be queued because the event queue is full.
 *
 * The device manufacturer may implement the following functions to perform their processing asynchronously. 
 * - JkFileConnectionReadBytes()
 * - JkFileConnectionSkipBytes()
 * - JkFileConnectionWriteBytes()
 * . 
 * If any of the above functions is implemented as asynchronous processing and returns 
 * #JK_FILECONNECTION_ASYNC_FUNCTION, the present function must be called to perform event
 * notification of the asynchronous processing result. The event format is as defined for
 * each of the above functions.
 *
 * If #JK_NULL is designated in the <i>event</i> parameter, or if an invalid <i>size</i> is
 * designated, this function fails and returns a negative value.
 * 
 * If this function returns a negative value when a value other than #JK_NULL was designated in <i>event</i>, 
 * the native system should wait for a time and then call this function again. 
 * 
 * This function may be called even while the JVM is stopped. Events notified during that
 * time are put in the event queue, but are not processed until the JVM resumes. Since
 * this may result in the event queue becoming full, the native system must make 
 * provision for such a possibility.
 * 
 * @see JkFileConnectionReadBytes()
 * @see JkFileConnectionSkipBytes()
 * @see JkFileConnectionWriteBytes()
 */
JKSint32 AmNotifyFileConnectionAsyncFunctionEvent(JKSint32* event,JKSint32 size);



#ifdef __cplusplus
}
#endif

#endif /* ___AM_FILECONNECTION_EVENT_H */

/**
 * @} end of group
 */

