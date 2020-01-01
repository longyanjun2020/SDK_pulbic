/*
 * Copyright 2003-2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesVmCtl.h
 *  JVM Control Data Types and Constants
 */
/**
 * @addtogroup JVM_Control_Data_Types_and_Constants
 * @{
 */
#ifndef ___AAMS_VM_CTL_TYPES_H
#define ___AAMS_VM_CTL_TYPES_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  A native system request was accepted.
 */
#define JK_VMREQUEST_OK  0

/**
 *  An illegal argument was designated.
 */
#define JK_VMREQUEST_ERROR_ILLEGAL_ARGUMENT  -1

/**
 *  The requested operation cannot be performed in this state.
 */
#define JK_VMREQUEST_ERROR_BAD_STATE  -2

/**
 *  The JVM exited on request by a Java application.
 */
#define JK_VMEXIT_OK_VOLUNTARY  0

/**
 *  The JVM exited on request by the native system.
 */
#define JK_VMEXIT_OK_REQUESTED  1

/**
 *  The JVM exited during continuous TCK testing.
 */
#define JK_VMEXIT_OK_TCKCONTINUE  2

/**
 *  The JVM terminated due to lack of memory.
 */
#define JK_VMEXIT_ERROR_OUTOFMEMORY  (-10)

/**
 *  The JVM was forcibly terminated.
 */
#define JK_VMEXIT_ERROR_VMKILLED  (-11)


/**
 *   JVM internal error: The JVM is already running.
 */
#define JK_VMEXIT_INTERNALERROR_RUNNING_ALREADY            (-108)


/**
 *   JVM internal error: Miscellaneous error
 */
#define JK_VMEXIT_INTERNALERROR_FATAL_ERROR                (-127)


/**
 *  The lowest-numbered error code indicating JVM abnormal termination
 *  caused by #AmPlatformNotifyError().
 */
#define JK_VMEXIT_PLATFORMERROR_LOWEST  (-0x7FFFFFFF)

/**
 *  The highest-numbered error code indicating JVM abnormal termination
 *  caused by #AmPlatformNotifyError().
 */
#define JK_VMEXIT_PLATFORMERROR_HIGHEST  (32767 + JK_VMEXIT_PLATFORMERROR_LOWEST)

/**
 *  The JVM started.
 *
 *  This is a JVM event notified when the JVM starts up normally after 
 *  the native system calls AamsVmStartMIDP() requesting the start of the JVM and
 *  a Java application.
 */
#define JK_VMEVENT_VMSTARTED  1

/**
 *  The JVM suspended operation.
 *
 *  This is a JVM event notified when the JVM has executed suspension processing as
 *  requested by the native system in AamsVmSuspend().
 *  When the JVM task is suspended by a system call or the like, receive this JVM
 *  event before suspending.
 */
#define JK_VMEVENT_VMSUSPENDED  2

/**
 *  The JVM resumed operation.
 *
 *  This is a JVM event notified when the JVM has executed resumption processing as
 *  requested by the native system in AamsVmResume().
 */
#define JK_VMEVENT_VMRESUMED  3

/**
 *  The JVM stopped.
 *
 *  This is a JVM event notified at the time JVM stop processing is completed,
 *  after the native system requested stoppage by #AamsVmStop().
 *
 *  After receiving the JVM event, the native system can free the resources that
 *  were used by JBlend via the native system, even before
 *  #AamsVmStartMIDP() returns to its caller.
 *  If the processing for freeing of resources may involve the calling of
 *  #AmPlatformNotifyError(), free resources after this JVM event is
 *  received rather than after #AamsVmStartMIDP() returns to its caller.
 *
 *  After this JVM event is notified, in no case does JBlend call a
 *  JSI.
 *  The function #AamsVmStartMIDP() immediately returns to its caller.
 */
#define JK_VMEVENT_VMSTOPPED  4

/**
 *   The JVM is ready to draw.
 *
 *   This is a JVM event notified when the JVM has completed preparations for drawing.
 *   If the Java trademark logo or other animation is displayed while starting the
 *   JVM, stop the animation when this JVM event is notified.
 *   This event is notified when preparations for drawing are complete.
 *   The timing for the start of drawing thereafter is up to the Java application.
 */
#define JK_VMEVENT_VMPAINTREADY  10

/**
 *  The Java application completed start-up processing.
 *
 *  This JVM event is notified after the JVM has started and the Java application
 *  has completed its start-up processing. 
 *  It is notified when processing of the javax.microedition.midlet.MIDlet class
 *  startApp() method overridden by the application has completed.
 *  If processing does not complete, such as when the startApp() method processing
 *  goes into an endless loop, this event is not notified.
 *  No particular processing is required in the native system when this event is
 *  notified.
 */
#define JK_VMEVENT_APPSTARTED  20

/**
 *  The Java application completed suspension processing.
 *
 *  This JVM event is notified when the Java application has completed suspension
 *  processing. 
 *  It is notified when processing of the javax.microedition.midlet.MIDlet class
 *  pauseApp() method overridden by the application has completed.
 *  If processing does not complete, such as when the pauseApp() method processing
 *  goes into an endless loop, this event is not notified.
 *  No particular processing is required in the native system when this event is
 *  notified.
 */
#define JK_VMEVENT_APPPAUSED  21

/**
 *  The Java application completed resumption processing.
 *
 *  This JVM event is notified after the JVM has resumed and the Java application
 *  has completed its resumption processing. 
 *  It is notified when processing of the javax.microedition.midlet.MIDlet class
 *  startApp() method overridden by the application has completed.
 *  If processing does not complete, such as when the startApp() method processing
 *  goes into an endless loop, this event is not notified.
 *  No particular processing is required in the native system when this event is
 *  notified.
 */
#define JK_VMEVENT_APPRESUMED  22

/**
 *  The Java application completed exit processing.
 *
 *  This JVM event is notified when the Java application completes its exit processing. 
 *  It is notified when processing of the javax.microedition.midlet.MIDlet class
 *  destroyApp() method overridden by the application has completed.
 *  If processing does not complete, such as when the destroyApp() method processing
 *  goes into an endless loop, this event is not notified.
 *  No particular processing is required in the native system when this event is
 *  notified.
 */
#define JK_VMEVENT_APPDESTROYED  23




/**
 */
#define JK_VMEVENT_APPRESUMEREQUEST 25

/**
 *  The data type of the JVM event type
 *
 *  This is used as the type of the vmEventType parameter with #JKVmEventHandler.
 *  The values that can be designated are defined by the following symbols.
 *   - #JK_VMEVENT_VMSTARTED
 *   - #JK_VMEVENT_VMSUSPENDED
 *   - #JK_VMEVENT_VMRESUMED
 *   - #JK_VMEVENT_VMSTOPPED
 *   - #JK_VMEVENT_VMPAINTREADY
 *   - #JK_VMEVENT_APPSTARTED
 *   - #JK_VMEVENT_APPPAUSED
 *   - #JK_VMEVENT_APPRESUMED
 *   - #JK_VMEVENT_APPDESTROYED
 *   .
 *  The general name for these event types is "JVM event."
 */
typedef JKSint32 JKVmEventType;

/**
 *  The function type of the event handler for receiving JVM events.
 *  @param vmId
 *   The identifier of the JVM instance. 
 *   This is the value passed in the vmId parameter to #AamsVmStartMIDP().
 *  @param vmEventType
 *   The JVM event type.
 *   A value defined for JVM events is designated.
 *  @param vmEventParam
 *   This is information associated with a JVM event.
 *   Only when #JK_VMEVENT_VMSTOPPED is designated in the vmEventType parameter,
 *   the same value as the #AmVmStartMIDP() return value is designated. The
 *   value when another JVM event is designated is indeterminate.
 *
 *  This type is the type of the callback function by which JBlend makes JVM
 *  event notification.
 *
 *  Designate the function of this type as a parameter in #AamsVmStartMIDP().
 *  JBlend calls back the designated function at the time of a state transition.
 *
 *  Since the function of this type is called back in the JVM task, do not
 *  call #AamsVmSuspend() or other functions requesting JVM state
 *  transitions in this function.
 * @see AamsVmStartMIDP()
 */
typedef void (*JKVmEventHandler) (JKSint32 vmId, JKVmEventType vmEventType, JKSint32 vmEventParam);

/**
 *  The type of the stream function for reading byte data.
 *  @param buffer
 *         A pointer to the buffer for storing read data.
 *  @param offset
 *         The position from which to read, designated as the offset (in bytes) from
 *         the head.
 *  @param size
 *         The size (in bytes) to be read.
 *  @return
 *         If the read operation succeeds, return the numnber of bytes (above 0)
 *         actually read.<br>
 *         If it failed, return a negative value.
 *
 *  This is the type of the callback function used by JBlend to read the
 *  application descriptor (JAD file) data and JAR file.
 *
 *  If the size of read data is less than the requested size, JBlend retries
 *  reading the remaining data.
 *  If the size returned as read data is greater than the requested size,
 *  JBlend treats this result as an error.
 * @see JKT_MIDP_Application
 */
typedef JKSint32 (*JKVmStreamReader) (void *buffer, JKSint32 offset, JKSint32 size);

/**
 * A structure type for containing information for TCK testing.
 *
 * This structure type is used for passing information about a TCK test application 
 * in parameters of #AamsVmStartMIDP() and #AmTckGetDescriptor(). See the descriptions 
 * of these two functions for details of the values set in the structure members. 
 * @see AamsVmStartMIDP(), AmTckGetDescriptor()
 */
typedef struct {
   /**
    * TCK mode
    * 
    * Set 0 in this memeber. 
    * This member is reserved for future use, and is currently not used.
    */
    JKSint        tckMode;
   /**
    * TCK host URL
    *
    * Set JK_NULL in this memeber. 
    * This member is reserved for future use, and is currently not used.
    */
    const JKSint8 *tckHost;
   /**
    * A pointer to the buffer holding the JAR file.
    */
    JKSint8       *jarBuf;
   /**
    * The size in bytes of the JAR file data indicated by <i>jarBuf</i>.
    */
    JKUint        jarLen;
   /**
    * The size in bytes of the buffer indicated by <i>jarBuf</i>.
    */
    JKUint        jarMax;
   /**
    * A pointer to the buffer holding the JAD file data.
    */
    JKSint8       *infoBuf;
   /**
    * The size in bytes of the JAD file data indicated by <i>infoBuf</i>.
    */
    JKUint        infoLen;
   /**
    * The size in bytes of the buffer indicated by <i>infoBuf</i>.
    */
    JKUint        infoMax;
   /**
    * A pointer to the buffer holding the URL string of the JAR file.
    *
    * A pointer to the buffer holding the URL string (with '\0' termination) of
    * the JAR file designated in the MIDlet attribute MIDlet-Jar-Url.
    */
    JKSint8       *jarUrlBuf;
   /**
    * The size in bytes of the buffer indicated by <i>jarUrlBuf</i>.
    */
    JKUint        jarUrlBufMax;
   /**
    * A pointer to the buffer holding the start-up class name.
    *
    * A pointer to the buffer holding the start-up class name string 
    * (with '\0' termination) designated in the MIDlet attribute MIDlet-1.
    */
    JKSint8       *classNameBuf;
   /**
    * The size in bytes of the buffer indicated by <i>classNameBuf</i>.
    */
    JKUint        classNameBufMax;
   /**
    * The method of TCK test program execution.
    *
    * Ordinarily JK_TRUE is to be designated. 
    * Designate JK_FALSE if the inner loop method is to be used for TCK test program execution.
    */
    JKBool        outer_loop;
} T_AM_TCK;

/**
 *  A structure indicating information about a Java application.
 *
 * @if PRECHECK_APPLICATION
 *  This is a data structure passed as a parameter with AamsVmStartMIDP() 
 *  and AamsCheckApplication() to give information about the Java application to be run. 
 * @else
 *  This is a data structure passed as a parameter with AamsVmStartMIDP()
 *  to give information about the Java application to be run. 
 * @endif
 *  Be sure to set values in the following members.
 *  - The jarSize member
 *  - Either the jarAddr member or jarRead member
 *  .
 *  A value must be set in either of the structure members jarAddr or jarRead.
 *  If values are set in both structure members, the value set in jarAddr is valid.
 *  Be sure to set a value in the structure member jarSize as well.
 *
 *  If a JAD file exists, set a value in either of the structure members jadAddr or
 *  jadRead, as well as in the structure member jadSize.
 *
 *  If a JAD file exists, be sure to set values in the following members.
 *  - The jadSize member
 *  - Either the jadAddr member or jadRead member.
 *  .
 *  If values are set in both structure members, the value set in jadAddr is valid. 
 *  A value must be set in the structure member jadSize as well.
 *  Use UTF-8 as the JAD file character encoding.
 *
 *  If no designation is made in a structure member, set 0 for an integer type
 *  member or JK_NULL for a pointer type member.
 *
 * <small>
 * <b>Notes: </b><br>
 * The Java application to be run must exist in the device before the JVM is
 * started. Some possible ways in which it can be stored include the following.
 *  - Stored in a contiguous area in flash ROM or other storage built into the device
 *  - Stored in a non-contiguous area in flash ROM or other storage built into the
 *    device (stored in the file system or equivalent)
 *  - Stored in a contiguous area of RAM in the device
 *  - Stored in a non-contiguous area of RAM in the device (stored in the file
 *    system or equivalent)
 *  .
 * Choose either of the following methods of designating the Java application JAR
 * file when the JVM is started so as to allow for any of the above possibilities.
 * - Designate in the structure member jarAddr a pointer to the memory area where
 *   the JAR file is stored, and designate JK_NULL in the structure member jarRead.
 * - Designate in the structure member jarRead a pointer to the stream function for
 *   reading from the JAR file, and designate JK_NULL in the structure member jarAddr.
 * .
 * Similarly, there are two ways of designating a JAD file.
 * - Designate in the structure member jadAddr a pointer to the memory area where
 *   the JAD file is stored, and designate JK_NULL in the structure member jadRead.
 * - Designate in the structure member jadRead a pointer to the stream function for
 *   reading from the JAD file, and designate JK_NULL in the structure member jadAddr.
 * .
 * </small>
 * @see AamsVmStartMIDP()
 */
typedef struct JKT_MIDP_Application {
   /**
    *  The size (in bytes) of the Java application JAR file
    */
    JKSint32 jarSize;
   /**
    *  A pointer to the memory area holding the JAR file for the application to be
    *  started.
    *
    *  If JK_NULL is set, the JAR file will be read by the callback function
    *  set in the structure member #jarRead.
    */
    const void *jarAddr;
   /**
    *  A pointer to the stream function (callback function) for reading the JAR file.
    *
    *  If JK_NULL is set, the JAR file in the memory location set in the structure
    *  member #jarAddr is referenced.
    */
    JKVmStreamReader jarRead;
   /**
    *  A pointer to the memory area holding the class name string of the Java
    *  application to be started.
    *
    *  Normally JK_NULL is set. When JK_NULL is set, the JVM searches for the class name 
    *  in both, the JAD file, and the manifest file which is contained in the JAR file.
    *  Then when the <code>startApp</code> method of the <code>javax.microedition.midlet.MIDlet</code> class overriding that class is called, the Java application starts running.
    *  If there is more than one Java application included, a menu screen for
    *  selecting from these is displayed. 
    *
    *  By setting the class name along with the package name in this member, the Java 
    *  application of the set class name can be started without performing the above 
    *  search.
    */
    const JKUTF8Char *className;
   /**
    *  The size (in bytes) of the class name character string for the Java application
    *  to be started.
    */
    JKSint32 classNameLen;
   /**
    *  The size (in bytes) of the Java application JAD file
    */
    JKSint32 jadSize;
   /**
    *  A pointer to the memory area holding the JAD file for the Java application to be
    *  started.
    *
    *  If JK_NULL is set, the JAD file will be read by the callback function
    *  set in the structure member #jadRead.
    */
    const void *jadAddr;
   /**
    *  A pointer to the stream function (callback function) for reading the JAD file.
    *
    *  If JK_NULL is set, the JAD file in the memory location set in the
    *  structure member #jadAddr is referenced.
    */
    JKVmStreamReader jadRead;
   /**
    *  Information indicating whether the Java application is a trusted MIDlet suite.
    *
    *  Set either of the following values.
    *  - JK_TRUE: A trusted MIDlet suite
    *  - JK_FALSE: An untrusted MIDlet suite
    */
    JKBool trusted;
   /**
    * A pointer to the T_AM_TCK structure containing necessary parameters for executing TCK testing.
    *
    * Set #JK_NULL when launching an ordinary Java application rather than a TCK test application.
    */
    T_AM_TCK *tckparam;
} JKT_MIDP_Application;

#ifdef __cplusplus
}
#endif

#endif /* ___AAMS_VM_CTL_TYPES_H */
