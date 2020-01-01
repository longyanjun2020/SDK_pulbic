/*
 * Copyright 2002-2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file AamsVmCtl.h
 *  JVM Control JBI
 */
/**
 * @addtogroup JVM_Control_JBI
 * @{
 */
#ifndef ___AAMS_VM_CTL_H
#define ___AAMS_VM_CTL_H

#include "JkTypes.h"
#include "JkTypesVmCtl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Starts the JVM and a Java application.
 *  @param vmId
 *         An identifier of the JVM instance.
 *         Designate an integer of 1 or above, defined in the native system.
 *         Use the value designated here to identify the JVM instance in other
 *         functions also.
 *  @param heapSize
 *         The size (in bytes) of the memory space the JVM can use as Java heap
 *         A size up to 16 megabytes can be designated. If a larger value is
 *         designated, the behavior is not guaranteed.
 *  @param heapAddr
 *         A pointer to the memory area that the JVM can use as Java heap.
 *  @param appInfo
 *         A pointer to the structure #JKT_MIDP_Application holding information about
 *         the Java application
 *  @param vmEventHandler
 *         A pointer to the event handler (callback function) for JVM event
 *         notification.
 *         The vmId parameter of this event handler takes the same value as vmId of
 *         #AamsVmStartMIDP().
 *         If it is not necessary for the native system to be notified of JVM state
 *         transitions, designate JK_NULL.
 *  @param vmParamCount
 *         The number of parameters passed to the JVM.
 *         Ordinarily 0 is designated.
 *         A value of 1 or above may be designated for the purpose of checking
 *         JVM behavior.
 *  @param vmParams
 *         A pointer to the memory location of the parameter string array to be passed
 *         to the JVM. Ordinarily JK_NULL is designated.
 *         For checking JVM behavior, values may be designated in the format below. <br>
 *         <pre>
 * static const JKUTF8Char *vmParams[] = {
 *   "-option_a",
 *   "-option_xyz"
 * };
 *         </pre>
 *         <small>
 *         Note: The above "-option_a" or "-option_xyz" do not actually exist as options.
 *         </small>
 *  @param vmParamLens
 *         A pointer to the memory area holding an array of byte counts for strings
 *         passed to the JVM. Ordinarily JK_NULL is designated.
 *         For checking JVM behavior, values may be designated in the format below. <br>
 * <pre>
 * static const JKSint32 vmParamLens[] = {
 *   9,         <-- "-option_a" character count
 *   11         <-- "-option_xyz" character count
 * };
 * </pre>
 *
 *  @return
 *         One of the following values (succeeded): <br>
 *         - #JK_VMEXIT_OK_VOLUNTARY: JVM and application exited voluntarily
 *         - #JK_VMEXIT_OK_REQUESTED: JVM exited on request by the native system
 *         - #JK_VMEXIT_OK_TCKCONTINUE: Normal exit in TCK continuous testing
 *         .
 *         Negative value: Error code (failed) <br>
 *         If the JVM terminated abnormally, one of the following values is returned. <br>
 *         - #JK_VMREQUEST_ERROR_ILLEGAL_ARGUMENT
 *         - #JK_VMREQUEST_ERROR_BAD_STATE
 *         - #JK_VMEXIT_ERROR_OUTOFMEMORY
 *         - #JK_VMEXIT_ERROR_VMKILLED
 *         - #JK_VMEXIT_INTERNALERROR_RUNNING_ALREADY
 *         - #JK_VMEXIT_INTERNALERROR_FATAL_ERROR
 *         .
 *
 *  When this function is called, the JVM and Java application are both started.
 *  The CPU context calling this function becomes the JVM context.
 *
 *  When the JVM starts normally, the JVM event #JK_VMEVENT_VMSTARTED is notified to
 *  the native system from the JVM task context.
 *
 *  The function does not return until the JVM exits.
 *  At the time this function returns, the JVM and Java application will already have
 *  completed their exit processing.
 *
 *  The contents of the Java heap memory area that is indicated by the <i>heapAddr</i> 
 *  parameter must be held until this function returns, including the time the JVM 
 *  is in suspended state. 
 *
 *  Upon return from this function, free the resources that were made available to
 *  JBlend by the native system.
 *
 *  If this function is called again while it is executing, it fails, 
 *  returning #JK_VMREQUEST_ERROR_BAD_STATE as an error code.  
 *  That is, only one JVM instance can be created.
 *
 *  Even when the JVM is forcibly terminated, this function returns to its caller.
 *
 *  When TCK testing is executed, information about the TCK start-up application supplied 
 *  by Aplix and about the TCK test program must be set as follows in the JKT_MIDP_Application 
 *  structure indicated by the <i>appIinfo</i> parameter.
 *
 * @htmlonly
 * <blockquote>
 * @endhtmlonly
 *  <dl>
 *   <dt><b>jarSize, jarAddr, jarRead, className, classNameLen</b></dt>
 *    <dd>Information about the JAR file of the TCK start-up application
 *    </dd>
 *   <dt><b>jadSize, jadAddr, jadRead</b></dt>
 *    <dd>Information about the JAD file of the TCK start-up application
 *    </dd>
 *   <dt><b>trusted</b></dt>
 *    <dd>
 *    Information indicating whether the TCK test application is 
 *    a trusted MIDlet
 *    </dd>
 *   <dt><b>tckparam</b></dt>
 *    <dd>
 *    A pointer to the T_AM_TCK structure containing information
 *    about the TCK test program downloaded by the native system <br>
 *    </dd>
 *  </dl> 
 * @htmlonly
 * </blockquote>
 * @endhtmlonly
 *
 * When TCK testing is executed, the following settings must be made in
 * the members of the T_AM_TCK structure indicated by <i>appInfo->tckparam</i>.
 * @htmlonly
 * <blockquote>
 * @endhtmlonly
 * <dl>
 *  <dt><b>jarBuf</b></dt>
 *   <dd>A pointer to the buffer holding JAR file data downloaded by the native system
 *   </dd>
 *  <dt><b>jarLen </b></dt>
 *   <dd>The size of the JAR file data indicated by <i>jarBuf</i>.
 *   </dd>
 *  <dt><b>jarMax </b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>infoBuf </b></dt>
 *   <dd>A pointer to the buffer holding JAD file data downloaded from the TCK server by the native system
 *   </dd>
 *  <dt><b>infoLen </b></dt>
 *   <dd>The size of the JAD file data indicated by <i>infoBuf</i>.
 *   </dd>
 *  <dt><b>infoMax</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>jarUrlBuf</b></dt>
 *   <dd>A pointer to the buffer holding the URL string (with '\0' termination) 
 *       of the JAR file designated in the MIDlet attribute MIDlet-Jar-Url in 
 *       the JAD file downloaded by the native system.<br>
 *       Sample URL string: http://localhost:8088/test1.jar
 *   </dd>
 *  <dt><b>jarUrlBufMax</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>classNameBuf</b></dt>
 *   <dd>A pointer to the buffer holding the start-up class name (with '\0' termination) 
 *       designated in the MIDlet attribute MIDlet-1 in 
 *       the JAD file downloaded by the native system.<br>
 *       Sample class name string: com.sun.tck.midp.javatest.agent.MIDletAgent
 *   </dd>
 *  <dt><b>classNameBufMax</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>outer_loop</b></dt>
 *   <dd>JK_TRUE
 *   </dd>
 * </dl>
 * @htmlonly
 * </blockquote>
 * @endhtmlonly
 *
 * @see AamsVmStop() @see AamsVmSuspendR2() @see AamsVmResume() @see AamsVmKill()
 * @internal @see JkSysGetPermissionInfo()
 */
JKSint32 AamsVmStartMIDP(JKSint32 vmId,
                         JKSint32 heapSize, void *heapAddr,
                         const JKT_MIDP_Application * appInfo,
                         JKVmEventHandler vmEventHandler,
                         JKSint32 vmParamCount,
                         const JKUTF8Char **vmParams, const JKSint32 *vmParamLens);

/**
 *  Requests JVM and Java application termination.
 *  @param vmId
 *         The identifier of the JVM instance.
 *         Designate the same value as that set in the vmId parameter when
 *         #AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         One of the following error codes indicating failure: <br>
 *         - #JK_VMREQUEST_ERROR_ILLEGAL_ARGUMENT
 *         - #JK_VMREQUEST_ERROR_BAD_STATE
 *         .
 *
 *  This function requests termination of the JVM and Java application and 
 *  immediately returns to the caller.
 *
 *  This function can be called under either of the following conditions 
 *  after #AamsVmStartMIDP() is called.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMSTARTED 
 *    is issued.
 *  - The JVM is in suspended state after the JVM event #JK_VMEVENT_VMSUSPENDED 
 *    is issued.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMRESUMED 
 *    is issued.
 *  .
 *  When this function is called without the condition being met,
 *  it fails and returns the #JK_VMREQUEST_ERROR_BAD_STATE error code.
 *
 *  If this function is called from another CPU context before return has been made
 *  from a previous call, the subsequent call is not processed but fails
 *  immediately, returning #JK_VMREQUEST_ERROR_BAD_STATE as an error code.
 *
 *  When the JVM terminates normally, the JVM event #JK_VMEVENT_VMSTOPPED is notified to
 *  the native system.
 *  The native system should then free the resources it had made available for use by JBlend.
 *  When freeing of resources ends,
 *  the function #AamsVmStartMIDP() in the JVM context completes, returning #JK_VMEXIT_OK_REQUESTED.
 *
 *  If after this function is called, #JK_VMEVENT_VMSTOPPED is not notified
 *  within the time specified in the native system, call #AamsVmKill() to force termination
 *  of the JVM task.
 *
 *  When an exit request is made by calling #AamsVmStop() while the JVM is suspended,
 *  it is first of all resumed. The JVM event #JK_VMEVENT_VMRESUMED is therefore
 *  notified prior to #JK_VMEVENT_VMSTOPPED.
 *  Java application resumption processing (the <code>javax.microedition.midlet.MIDlet</code> class
 *  <code>startApp</code> method overridden by the application) is not performed at this time.
 *  The application exit processing (the <code>MIDlet</code> class <code>destroyApp</code> method) is executed.
 *  If the JVM task is sleeping during the suspended state, wake up the JVM task prior
 *  to issuing the exit request.
 * @see AamsVmStartMIDP() @see AamsVmKill()
 */
JKSint32 AamsVmStop(JKSint32 vmId);

/**
 *  Requests suspension of the Java application but keeping the JVM in Running state.
 *  @param vmId
 *         The identifier of the JVM instance.
 *         Designate the same value as that set in the <i>vmId</i> parameter when AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         #JK_VMREQUEST_ERROR_BAD_STATE: failed <br>
 *
 *  This function requests suspension of the Java application and immediately returns to the caller.
 *  When JBlend detects the request it executes the Java application suspension 
 *  processing (the <code>javax.microedition.midlet.MIDlet</code> class 
 *  <code>pauseApp</code> method overridden by the application).
 *  When the application suspension processing is completed, JBlend passes a #JK_VMEVENT_APPPAUSED event to the native system.
 *  After the Java application is suspended, no state transition occurs in the JVM, which continues in Running state. 
 *
 *  This function can be called under either of the following conditions 
 *  after AamsVmStartMIDP() is called.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMSTARTED issued.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMRESUMED issued.
 *  .
 *  When this function is called without the condition above being met,
 *  for example when the JVM is in suspended state, 
 *  the function fails and returns the #JK_VMREQUEST_ERROR_BAD_STATE error code.
 *
 *  This function fails and returns the #JK_VMREQUEST_ERROR_BAD_STATE error code also in the following cases.
 *  The error code may be ignored in these cases.
 *  - After this function is called, it is called again before the JVM event #JK_VMEVENT_APPPAUSED is passed.
 *  - The Java application is already suspended.
 *  - This function is called during the interval between <code>MIDlet@#notifyPaused</code> method calling by the Java application and #JK_VMEVENT_APPPAUSED event notification. 
 *  - This function is called during the interval between AamsVmSuspendR2() calling by the native system and #JK_VMEVENT_VMSUSPENDED event notification. 
 *  - This function is called during the interval between AamsVmStop() calling by the native system and #JK_VMEVENT_VMSTOPPED event notification. 
 *  .
 *
 *  During the interval between the calling of this function and notification of the
 *  JVM event #JK_VMEVENT_APPPAUSED, it is allowable to request JVM suspension by calling
 *  AamsVmSuspendR2(), as when, for example, a request for JVM suspension by the 
 *  user is detected.
 *  
 *  To resume a Java application suspended by invoking this function, call AamsVmResumeForeMIDlet().
 *
 *  This function is implemented in JBlend for MIDP 2.1.
 *
 *  Ordinarily, use AamsVmSuspendR2() to suspend a Java application.
 *  Call this function only when it is necessary to keep the JVM in Running state, as in testing with the JDTS. 
 * @see AamsVmStartMIDP() @see AamsVmSuspendR2() @see AamsVmStop() @see AamsVmResumeForeMIDlet()
 */
JKSint32 AamsVmPauseForeMIDlet(JKSint32 vmId);

/**
 *  Requests resumption of a Java application that was suspended with the JVM kept in Running state.
 *  @param vmId
 *         The identifier of the JVM instance.
 *         Designate the same value as that set in the <i>vmId</i> parameter when AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         #JK_VMREQUEST_ERROR_BAD_STATE: failed <br>
 * 
 *  This function can be used only when the JVM is running and the Java application is in suspended state.
 *  This function requests resumption of the suspended Java application and immediately returns to the caller.
 *  When JBlend detects the request it executes the Java application resumption 
 *  processing (the <code>javax.microedition.midlet.MIDlet</code> class 
 *  <code>startApp</code> method overridden by the application).
 *  When the application suspension processing is completed, JBlend passes a #JK_VMEVENT_APPRESUMED event to the native system.
 *  No state transition occurs in the JVM.
 *
 *  Use this function paired with AamsVmPauseForeMIDlet().
 *  This function can be invoked if the JVM is running after AamsVmPauseForeMIDlet() was called.
 *  It can be called during the interval from AamsVmPauseForeMIDlet() invocation to 
 *  #JK_VMEVENT_APPPAUSED notification, in which case resumption processing is performed immediately 
 *  after the Java application is suspended.
 *
 *  If invoked while the Java application is running or while the JVM is suspended, this function 
 *  fails and the #JK_VMREQUEST_ERROR_BAD_STATE error code is returned.
 *  
 *  This function fails and returns the #JK_VMREQUEST_ERROR_BAD_STATE error code also in the following cases.
 *  The error code may be ignored in these cases.
 *  - After this function is called, it is called again before the JVM event #JK_VMEVENT_APPRESUMED is passed.
 *  - The Java application is already resumed.
 *  - This function is called during the interval between <code>MIDlet@#notifyPaused</code> method 
 *    calling by the Java application and #JK_VMEVENT_APPPAUSED event notification. 
 *  - This function is called during the interval between AamsVmSuspendR2() 
 *    calling by the native system and #JK_VMEVENT_VMSUSPENDED event notification. 
 *  - This function is called during the interval between AamsVmResume() 
 *    calling by the native system and #JK_VMEVENT_APPRESUMED event notification. 
 *  - This function is called during the interval between AamsVmStop() 
 *    calling by the native system and #JK_VMEVENT_VMSTOPPED event notification. 
 *  .
 *  
 *  While the Java application is suspended as a result of calling AamsVmPauseForeMIDlet(),
 *  if AamsVmSuspendR2() is invoked suspending the JVM, then when the JVM is resumed by calling
 *  AamsVmResume(), the Java application will also be resumed. Calling this function is
 *  unnecessary in such a case.
 * 
 *  This function is implemented in JBlend for MIDP 2.1.
 * @see AamsVmStartMIDP() @see AamsVmSuspendR2() @see AamsVmResume @see AamsVmStop() @see AamsVmPauseForeMIDlet()
 */
JKSint32 AamsVmResumeForeMIDlet(JKSint32 vmId);


/**
 *  Requests JVM suspension.
 *  @param vmId
 *         The identifier of the JVM instance.
 *         Designate the same value as that set in the vmId parameter when
 *         #AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         #JK_VMREQUEST_ERROR_BAD_STATE: failed
 *
 *  This function requests suspension of the JVM and Java application and 
 *  immediately returns to the caller.
 *
 *  This function can be called under either of the following conditions 
 *  after #AamsVmStartMIDP() is called.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMSTARTED 
 *    issued.
 *  - The JVM is in running state after the JVM event #JK_VMEVENT_VMRESUMED 
 *    issued.
 *  .
 *  When this function is called without the condition above being met,
 *  for example when the JVM is in suspended state, 
 *  the function fails and returns the #JK_VMREQUEST_ERROR_BAD_STATE error code.
 *
 *  This function can be used only when the JVM is in running state.
 *  It can be called after notification of the JVM events #JK_VMEVENT_VMSTARTED or
 *  #JK_VMEVENT_VMRESUMED.
 *
 *  When JBlend detects the request in the JVM task, it
 *  executes the Java application suspension processing (the
 *  <code>javax.microedition.midlet.MIDlet</code>
 *  class <code>pauseApp</code> method overridden by the
 *  application), then it executes JVM suspension processing.
 *  At the timing of Java application suspension completion and
 *  JVM application suspension completion, JBlend notifies the native system
 *  of the JVM events #JK_VMEVENT_APPPAUSED and #JK_VMEVENT_VMSUSPENDED respectively.
 *
 *  Before the event handler that has received #JK_VMEVENT_VMSUSPENDED 
 *  returns to the caller, the native system must put the JVM task 
 *  in the state that the task does not run.
 *  The typical method of performing this is to issue a system call causing 
 *  the JVM task to sleep in the event handler.
 *  As long as it can put the JVM task in sleeping state before the 
 *  event handler returns to the caller, the issue of the system call 
 *  can be from a task separate from the JVM task.
 *
 *  If after this function is called, #JK_VMEVENT_VMSUSPENDED is not notified within
 *  the time specified in the native system, call #AamsVmKill() to force
 *  termination of the JVM task.
 *
 *  When this function is called a second time before the JVM event
 *  #JK_VMEVENT_VMSUSPENDED
 *  has been notified, only the first function call is processed.
 *  Subsequent calls fail, returning an error code.
 *  During the interval from the calling of this function until the JVM event
 *  #JK_VMEVENT_VMSUSPENDED
 *  is notified, even if a resume request is detected from the user,
 *  ignore it or hold it; do not call #AamsVmKill() to resume the JVM.
 *
 * If this function is called after the native system has invoked AamsVmPauseForeMIDlet() 
 * suspending only the Java application, JBlend skips the calling of the 
 * <code>javax.microedition.midlet.MIDlet</code> class <code>pauseApp</code> method overridden by the Java 
 * application, and does not issue the JVM event #JK_VMEVENT_APPPAUSED.
 */
JKSint32 AamsVmSuspendR2(JKSint32 vmId);

/**
 *  Requests JVM and a Java application resumption
 *  @param vmId
 *         The identifier of the JVM instance.
 *         Designate the same value as that set in the vmId parameter when
 *         #AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         #JK_VMREQUEST_ERROR_BAD_STATE: failed <br>
 *
 *  This function can be used only when the JVM is in suspended state. 
 *  This function performs processing for resuming the suspended JVM and 
 *  returns to the caller.
 *  When resumption processing is completed, the native system task is 
 *  notified of the #JK_VMEVENT_VMRESUMED JVM event.
 *
 *  Use this function paired with #AamsVmSuspendR2().
 *  It can be called after notification of the JVM event #JK_VMEVENT_VMSUSPENDED.
 *  If the JVM is in running state when this function is called, 
 *  the function fails, returning the #JK_VMREQUEST_ERROR_BAD_STATE error code.
 *
 *  If this function has been called, and then is called again before the JVM event
 *  #JK_VMEVENT_VMRESUMED is notified, only the processing for the first call is
 *  executed. The #JK_VMREQUEST_ERROR_BAD_STATE error code is returned immediately 
 *  for subsequent calls indicating failure.
 *
 *  The contents of the Java heap memory area must be same state as when the JVM was
 *  suspended before this function is called.
 *
 *  If the JVM task was put in sleeping state when the JVM was suspended, wake it up
 *  using an RTOS system call before calling #AamsVmResume().
 *
 *  If after this function is called, the JVM event #JK_VMEVENT_VMRESUMED is not
 *  notified within the time specified in the native system, call
 *  #AamsVmKill() to force termination of the JVM task.
 *
 *  If the screen display was modified while the JVM was suspended and cannot be
 *  restored when the JVM resumes, notify a screen update event.
 *  To notify a screen update event, call #AmNotifyRepaintEvent() prior to calling
 *  #AamsVmResume().
 *  When the JVM resumes, the drawing functions defined in the Java application will
 *  be called by the JVM.
 *
 *  If the Java application suspension processing was executed before the JVM was
 *  suspended, then when the JVM is resumed by this function, the application
 *  resumption processing (the <code>javax.microedition.midlet.MIDlet</code> class <code>startApp</code>
 *  method overridden by the Java application) is executed.
 * @see AmNotifyRepaintEvent() @see AamsVmStartMIDP() @see AamsVmKill() @see AamsVmSuspendR2()
 */
JKSint32 AamsVmResume(JKSint32 vmId);

/**
 *  Forcibly terminates the JVM.
 *
 *  @param vmId
 *         The identifier of the JVM instance to be terminated.
 *         Designate the same value as that set in the vmId parameter when
 *         #AamsVmStartMIDP() was called.
 *  @return
 *         #JK_VMREQUEST_OK: succeeded<br>
 *         #JK_VMREQUEST_ERROR_BAD_STATE: failed <br>
 *
 *  This function can be used any time after #AamsVmStartMIDP() is called.
 *
 *  Call this function when JVM event notification fails to be made within the time
 *  specified in the native system following the calling of #AamsVmSuspendR2() or other
 *  functions requesting a JVM state transition.
 *
 *  When this function is called, #AamsVmStartMIDP() terminates, returning the error
 *  code #JK_VMEXIT_ERROR_VMKILLED.
 *  After this function returns, in the native system free the resources that were made
 *  available for use by JBlend.
 *  If forced termination occurs during storage file access, the storage file state
 *  will become abnormal. For this reason storage files that were in use by a Java
 *  application must be initialized.
 *
 *  When this function is called, #AamsVmStartMIDP() returns immediately to its
 *  caller. 
 *  In the following cases, however, it is conceivable that AamsVmStartMIDP() 
 *  will not return to its caller. 
 *  - A JSI function takes a long time until returning to JBlend.
 *  - A long time is necessary for the processing in a third party library
 *    (e.g. 3D graphics engine) directly called from JBlend and control does
 *    not return to JBlend immediately.
 *  - JBlend internal processing, such as GC, takes a long time.
 *  .
 *  
 *  If AamsVmStartMIDP() does not return immediately, delete the CPU context
 *  of the JVM task by using a system call.
 * @see AamsVmStartMIDP()
 */
JKSint32 AamsVmKill(JKSint32 vmId);




#ifdef __cplusplus
}
#endif

#endif
/** @} end of group */
