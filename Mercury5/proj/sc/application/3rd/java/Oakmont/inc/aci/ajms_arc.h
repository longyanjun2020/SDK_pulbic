/*
 * Copyright 2002-2005 Aplix Corporation. All rights reserved.
 */
/**
 * @file ajms_arc.h
 * VM Runtime Control ACI
 */


#ifndef AJMS_ARC_HEADER
#define AJMS_ARC_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include "ajms_common.h"

/** @addtogroup ams_vm_runtime_control_aci
 *  @{
 */

/*
 *
 *  Interfaces listed in the group are used for application runtime control,
 *  including these functionalities:
 *
 *       - Launch an installed midlet suite.
 *       - Launch an non-installed midlet suite.
 *       - Check current VM state.
 *       - Suspend/Resume VM.
 *       - Standby/Wakeup VM.
 *       - Terminate VM.
 *       - Set VM parameters.
 *       .
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup VM_State_Code JVM State Code
 * Defines JVM state codes.
 *
 * @par Include file 
 * \#include ajsc_arc.h
 * @{
 */
 
/**
 * @name JVM State Code
 * The current JVM state is acquirable via ajms_arc_getState() as one of the following values.
 * @{
 */
/**
 * JVM state: JVM is in non-existent state.
 */
#define AJSC_VMSTATE_NONE         (0)
/**
 * JVM state: JVM is now starting.
 */
#define AJSC_VMSTATE_STARTING     (1)
/**
 * Reserved VM state ID for future use.
 */
#define AJSC_VMSTATE_RESERVED     (2)
/**
 * JVM state: JVM has started and is now running.
 */
#define AJSC_VMSTATE_STARTED      (3)
/**
 * JVM state: JVM is being suspended.
 */
#define AJSC_VMSTATE_SUSPENDING   (4)
/**
 * JVM state: JVM is suspended.
 */
#define AJSC_VMSTATE_SUSPENDED    (5)
/**
 * JVM state: JVM is resuming.
 */
#define AJSC_VMSTATE_RESUMING     (6)
/**
 * JVM state: JVM is being destroyed.
 */
#define AJSC_VMSTATE_DESTROYING   (7)
/**
 * JVM state: JVM is being killed.
 */
#define AJSC_VMSTATE_KILLING      (8)

/** @} */
/** @} */

/**
 * @addtogroup VM_Event_Code JVM Event Code
 * Defines JVM event codes.
 *
 * @par Include file 
 * \#include ajms_arc.h
 * @{
 */

/**
 * @name JVM Event
 * @{
 * JVM events are passed via the #AJMS_VmEventHandler function type handler which has been passed to 
 * ajms_arc_runApp(), ajms_arc_runAppEx1(), or ajms_arc_startTck().
 */
/**
 * JVM event: JVM started.
 */
#define AJMS_VMEVENT_VM_STARTED                     (1)
/**
 * JVM event: JVM suspended operation.
 */
#define AJMS_VMEVENT_VM_SUSPENDED                   (2)
/**
 * JVM event: JVM resumed.
 */
#define AJMS_VMEVENT_VM_RESUMED                     (3)
/**
 * JVM event: JVM stopped.
 */
#define AJMS_VMEVENT_VM_STOPPED                     (4)
/**
 * JVM event: JVM is ready to draw.
 */
#define AJMS_VMEVENT_VM_PAINTREADY                  (10)
/** @} */

/**
 * @name Application Event
 * @{
 * Application events are passed via the #AJMS_VmEventHandler function type handler which has been passed to 
 * ajms_arc_runApp(), ajms_arc_runAppEx1(), or ajms_arc_startTck().
 */
/**
 * JVM event: Java application completed start-up processing.
 *
 * This JVM event is passed to the native system after the JVM has started and the Java application has completed its start-up processing, 
 * i.e., the processing of the <code>javax.microedition.midlet.MIDlet</code> class <code>startApp</code> method overridden 
 * by the application. 
 *
 * If processing does not complete, such as when the <code>startApp</code> method processing goes into an endless loop, 
 * this event is not passed.
 */
#define AJMS_VMEVENT_APP_STARTED                    (20)
/**
 * JVM event: A Java application completed suspension processing.
 *
 * This JVM event is passed to the native system when the Java application has completed suspension processing, 
 * i.e., the processing of the <code>javax.microedition.midlet.MIDlet</code> class <code>pauseApp</code> method overridden 
 * by the application. 
 *
 * If processing does not complete, such as when the <code>pauseApp</code> method processing goes into an endless loop, 
 * this event is not passed.
 */
#define AJMS_VMEVENT_APP_PAUSED                     (21)
/**
 * JVM event: Java application completed resumption processing.
 * 
 * This JVM event is passed to the native system after the JVM has resumed and the Java application has completed its resumption processing,
 * i.e., the processing of the <code>javax.microedition.midlet.MIDlet</code> class <code>startApp</code> method overridden 
 * by the application. 
 *
 * If processing does not complete, such as when the <code>startApp</code> method processing goes into an endless loop, 
 * this event is not passed. 
 */
#define AJMS_VMEVENT_APP_RESUMED                    (22)
/**
 * JVM event: Java application completed exit processing.
 * 
 * This JVM event is passed to the native system when the <code>javax.microedition.midlet.MIDlet</code> class 
 * <code>destroyApp</code> method overridden by the Java application returns.
 *
 * If processing does not complete, such as when the <code>destroyApp</code> method processing goes into an endless loop, 
 * this event is not passed. 
 */
#define AJMS_VMEVENT_APP_DESTROYED                  (23)
/** @} */


/**
 * @name JVM Exit Code
 * @{
 * JVM exit codes are passed via the #AJMS_VmEventHandler function type handler which has been passed to 
 * ajms_arc_runApp(), ajms_arc_runAppEx1(), or ajms_arc_startTck().
 */
/**
 * JVM event: JVM stopped normally voluntarily.
 */
#define AJMS_VMEXIT_OK_VOLUNTARY                    (100)
/**
 * JVM event: JVM stopped normally in response to a stop request.
 */
#define AJMS_VMEXIT_OK_REQUESTED                    (101)
/**
 * JVM event: JVM stopped normally with an indication that TCK testing continues.
 */
#define AJMS_VMEXIT_OK_TCKCONTINUE                  (102)
/**
 * JVM event: JVM stopped abnormally with an out of memory error.
 */
#define AJMS_VMEXIT_ERROR_OUTOFMEMORY               (103)
/**
 * JVM event: JVM stopped abnormally by forcible termination.
 */
#define AJMS_VMEXIT_ERROR_VMKILLED                  (104)
/**
 * JVM event: JVM stopped abnormally because a JVM is already running.
 */
#define AJMS_VMEXIT_INTERNALERROR_RUNNING_ALREADY   (105)
/**
 * JVM event: JVM stopped abnormally due to a fatal error.
 */
#define AJMS_VMEXIT_INTERNALERROR_FATAL_ERROR       (106)
/**
 * JVM event: JVM stopped abnormally due to an illegal argument.
 */
#define AJMS_VMEXIT_ERROR_ILLEGAL_ARGUMENT          (107)
/**
 * JVM event: JVM stopped abnormally due to a bad state error.
 */
#define AJMS_VMEXIT_ERROR_BAD_STATE                 (108)
/**
 * JVM event: The final event of the events passed after JVM exits.
 */
#define AJMS_VMEXIT_TERMINATED                      (200)
/** @} */


/**
 * @name TCK Event
 * @{
 * TCK events are passed via the #AJMS_VmEventHandler function type handler which has been passed to 
 * ajms_arc_startTck().
 */
/**
 * TCK event: TCK initialized.
 */
#define AJMS_TCKEVENT_STARTED                       (900)
/**
 * TCK event: JAD file downloaded.
 */
#define AJMS_TCKEVENT_JAD_DOWNLOADED                (901)
/**
 * TCK event: JAD file checked.
 */
#define AJMS_TCKEVENT_JAD_CHECKED                   (902)
/**
 * TCK event: JAR file downloaded.
 */
#define AJMS_TCKEVENT_JAR_DOWNLOADED                (903)
/**
 * TCK event: Test case installed.
 */
#define AJMS_TCKEVENT_INSTALLED                     (904)
/**
 * TCK event: Test case executed; JVM terminated.
 */
#define AJMS_TCKEVENT_VM_TERMINATED                 (905)
/**
 * TCK event: TCK completed successfully.
 */
#define AJMS_TCKEVENT_EXITED_NORMALLY               (910)
/**
 * TCK event: An error occurred during TCK process.
 */
#define AJMS_TCKEVENT_EXITED_WITH_ERROR             (911)
/** @} */

/** @} */

/**
 * @addtogroup Application_Runtime_Control_ACI JVM Runtime Control ACI
 * An interface for controlling the JVM lifecycle.
 * This interface is implemented in AJSC.
 *
 * @par Include file 
 * \#include ajms_arc.h
 * @{
 */

/**
 *        The function type of the state notification callback for application runtime control.
 * @param eventType
 *        The event type.
 *        One of the following values is passed.
 *        - JVM state changes during the JVM lifecycle.
 *            - #AJMS_VMEVENT_VM_STARTED
 *            - #AJMS_VMEVENT_VM_SUSPENDED
 *            - #AJMS_VMEVENT_VM_RESUMED
 *            - #AJMS_VMEVENT_VM_STOPPED
 *            - #AJMS_VMEVENT_VM_PAINTREADY
 *            .
 *        - Application state changes during the application lifecycle.
 *            - #AJMS_VMEVENT_APP_STARTED
 *            - #AJMS_VMEVENT_APP_PAUSED
 *            - #AJMS_VMEVENT_APP_RESUMED
 *            - #AJMS_VMEVENT_APP_DESTROYED
 *            .
 *        - JVM exit code when JVM stops normally.
 *            - #AJMS_VMEXIT_OK_VOLUNTARY
 *            - #AJMS_VMEXIT_OK_REQUESTED
 *            - #AJMS_VMEXIT_OK_TCKCONTINUE
 *            .
 *        - JVM exit code when JVM stops abnormally.
 *            - #AJMS_VMEXIT_ERROR_OUTOFMEMORY
 *            - #AJMS_VMEXIT_ERROR_VMKILLED
 *            - #AJMS_VMEXIT_INTERNALERROR_RUNNING_ALREADY
 *            - #AJMS_VMEXIT_INTERNALERROR_FATAL_ERROR
 *            - #AJMS_VMEXIT_ERROR_ILLEGAL_ARGUMENT
 *            - #AJMS_VMEXIT_ERROR_BAD_STATE
 *            .
 *        - The final JVM event for ajms_arc_runApp() and ajms_arc_runAppEx1().
 *            - #AJMS_VMEXIT_TERMINATED
 *            .
 *        - TCK event that can occur only when calling ajms_arc_startTck().
 *            - #AJMS_TCKEVENT_STARTED
 *            - #AJMS_TCKEVENT_JAD_DOWNLOADED
 *            - #AJMS_TCKEVENT_JAD_CHECKED
 *            - #AJMS_TCKEVENT_JAR_DOWNLOADED
 *            - #AJMS_TCKEVENT_INSTALLED
 *            - #AJMS_TCKEVENT_VM_TERMINATED
 *            - #AJMS_TCKEVENT_EXITED_NORMALLY
 *            - #AJMS_TCKEVENT_EXITED_WITH_ERROR
 *            .
 *        .
 * <p>
 * A callback function of this type should be passed via a parameter to ajms_arc_runApp(), ajms_arc_runAppEx1() and ajms_arc_startTck().
 * The callback function is to be implemented by the device manufacturer.
 *
 * The callback function is called in the KVE thread context to indicate the state transitions.
 *
 * @see ajms_arc_runApp(), ajms_arc_runAppEx1(), ajms_arc_startTck()
 */
typedef void (*AJMS_VmEventHandler) (AJ_S32 eventType);

/** @} */

/*-----------------------------------------------------------------------------
 * Global Functions Prototype
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup Application_Runtime_Control_ACI
 * @{
 */

/**
 * Queries the current JVM state.
 *
 * @retval #AJSC_VMSTATE_NONE
 * @retval #AJSC_VMSTATE_STARTING
 * @retval #AJSC_VMSTATE_RESERVED
 * @retval #AJSC_VMSTATE_STARTED
 * @retval #AJSC_VMSTATE_SUSPENDING
 * @retval #AJSC_VMSTATE_SUSPENDED
 * @retval #AJSC_VMSTATE_RESUMING
 * @retval #AJSC_VMSTATE_DESTROYING
 * @retval #AJSC_VMSTATE_KILLING
 */
AJ_S32 ajms_arc_getState(void);

/**
 * Requests execution of a Java application.
 * @param suiteId
 *        The identifier of the MIDlet suite to be launched.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param midletId
 *        The index of the MIDlet in the specified MIDlet suite. 
 *        - When <i>midletId</i> is a value between 0 and the value returned by ajms_ab_getMidletListCount() - 1, 
 *          AJSC launches the corresponding MIDlet.
 *        - When <i>midletId</i> is a value between the value returned by ajms_ab_getMidletListCount() and 255, 
 *          this function fails.
 *        - When <i>midletId</i> is a value outside the range from 0 to 255, 
 *          AJSC triggers the internal MIDlet selector for the user to choose a MIDlet of the MIDlet suite.
 * @param vmEventHandler
 *        The address of the JVM state notification callback function.
 *        This address must remain valid until the #AJMS_VMEXIT_TERMINATED event is passed via this callback function.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds in sending a launch request.
 * @retval #AJMS_ERR_INTERNAL
 *         if the function fails.
 *
 * Use this function to run a MIDlet suite stored in the AJSC Java application repository.
 *
 * This function only sends a launch request to the KVE thread by using kjava_sys_sendAction() and returns to the caller. 
 *
 * The callback function @ref AJMS_VmEventHandler "vmEventHandler" is called in the KVE thread context to notify the native system of state 
 * transition events of the JVM and Java application.
 * The following events are issued in the following order when the application normally starts.
 * -# #AJMS_VMEVENT_VM_STARTED
 * -# #AJMS_VMEVENT_VM_PAINTREADY
 * -# #AJMS_VMEVENT_APP_STARTED
 * .
 * If a certain time elapses after the AMS calls ajms_arc_runApp() and these notifications have not been made, 
 * call ajms_arc_terminateApp() to force termination. 
 * The timeout time should be decided in the native system based on factors such as CPU performance and storage file access speed. 
 *
 */
AJ_S32 ajms_arc_runApp(
                const AJ_S32 suiteId,
                const AJ_S32 midletId,
                AJMS_VmEventHandler vmEventHandler);

/**
 * Requests suspension of the running Java application.
 * @retval #AJMS_ERR_NONE     if suspension is requested to the KVE thread normally.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * Use this function to suspend the MIDlet currently running in the KVE thread.
 * 
 * When the application is normally suspended, the following events are issued in the following order
 * via @ref AJMS_VmEventHandler "vmEventHandler" passed to ajms_arc_runApp() or ajms_arc_runAppEx1().
 * -# #AJMS_VMEVENT_APP_PAUSED
 * -# #AJMS_VMEVENT_VM_SUSPENDED
 * .
 * If a certain time elapses after the AMS calls ajms_arc_suspendApp() and these event notifications have not been made, 
 * call ajms_arc_terminateApp() to force termination. 
 * The timeout time should be decided in the native system based on factors such as CPU performance and storage file access speed. 
 *
*/
AJ_S32 ajms_arc_suspendApp(void);


/**
 * Requests resumption of the suspended Java application.
 * @retval #AJMS_ERR_NONE     if resumption is requested to the KVE thread normally.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * Use this function to resume the Java application currently pausing in the KVE thread.
 *
 * When the application is normally resumed, the following events are issued in the following order
 * via @ref AJMS_VmEventHandler "vmEventHandler" passed to ajms_arc_runApp() or ajms_arc_runAppEx1().
 * -# #AJMS_VMEVENT_VM_RESUMED
 * -# #AJMS_VMEVENT_APP_RESUMED
 * .
 * If a certain time elapses after the AMS calls ajms_arc_resumeApp() and these event notifications have not been made, 
 * call ajms_arc_terminateApp() to force termination. 
 * The timeout time should be decided in the native system based on factors such as CPU performance and storage file access speed. 
 *
 */
AJ_S32 ajms_arc_resumeApp(void);

/**
 * Requests termination of the JVM and Java application.
 * @retval #AJMS_ERR_NONE     if termination is requested to the KVE thread normally.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * Use this function to terminate the Java application currently running or pausing in the KVE thread.
 *
 * When the application is normally terminated, the following events are issued in the following order
 * via @ref AJMS_VmEventHandler "vmEventHandler" passed to ajms_arc_runApp() or ajms_arc_runAppEx1().
 * @htmlonly <blockquote> @endhtmlonly
 * @par If the application is in the running state.
 * -# #AJMS_VMEVENT_APP_DESTROYED
 * -# #AJMS_VMEVENT_VM_STOPPED
 * .
 * @par If the application is in the suspended state.
 * -# #AJMS_VMEVENT_VM_RESUMED 
 * -# #AJMS_VMEVENT_APP_DESTROYED
 * -# #AJMS_VMEVENT_VM_STOPPED
 * .
 * @htmlonly </blockquote> @endhtmlonly
 *
 */
AJ_S32 ajms_arc_terminateApp(void);

/**
 * @internal
 *        Requests the JVM and Java application to change to standby mode.
 * @retval #AJMS_ERR_NONE     The suspend request was sent normally.
 * @retval #AJMS_ERR_INTERNAL Failed to transfer VM state.
 *
 * @see AJMS_VmEventHandler
 */
AJ_S32 ajms_arc_standbyApp(void);

/**
 * @internal
 * Requests the JVM and Java application to wake up from standby mode.
 * @retval #AJMS_ERR_NONE     The suspend request was sent normally.
 * @retval #AJMS_ERR_INTERNAL Failed to transfer VM state.
 *
 * @see AJMS_VmEventHandler
 */
AJ_S32 ajms_arc_wakeupApp(void);

/**
 *        Requests execution of a Java application passed in buffers.
 * @param jadSize
 *        The size (in bytes) of the Jad file.
 * @param jadAddr
 *        A pointer to the buffer holding the Jad file.
 *        If #AJ_NULL is passed, the Jad file will be read by the callback
 *        function designated in the parameter <i>jadRead</i>.
 * @param jadRead
 *        A pointer to the stream function (callback function) for reading the Jad file. 
 *        If #AJ_NULL is designated, the Jad file in the buffer designated
 *        in the parameter <i>jadAddr</i> is referenced.
 * @param jarSize
 *        The size (in bytes) of the JAR file
 * @param jarAddr
 *        A pointer to the buffer holding the Jar file.
 *        If #AJ_NULL is passed, the JAR file will be read by the callback function
 *        designated in the  parameter <i>jarRead</i>.
 * @param jarRead
 *        A pointer to the stream function (callback function) for reading the Jar file.
 *        If #AJ_NULL is designated, the JAR file in the buffer designated in the
 *        parameter <i>jarAddr</i> is referenced.
 * @param vmEventHandler
 *        The address of the JVM state notification callback function.
 *        This address must remain valid until the #AJMS_VMEXIT_TERMINATED event is passed via this callback function.
 * @retval #AJMS_ERR_NONE     if the function succeeds in sending a launch request.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * This is an alternative way to execute Java applications. 
 * It allows the native system to run a java application without installation. 
 * However, the Java application is executed as an application in the #AJMS_PCS_DOMAIN_UNSPECIFIED 
 * protection domain and the persistent data (e.g., <code>RecordStore</code>) for the Java application 
 * is not preserved after execution.
 *
 * This function only sends a launch request to the KVE thread by using kjava_sys_sendAction() and returns to the caller. 
 *
 * The callback function @ref AJMS_VmEventHandler "vmEventHandler" is called in the KVE thread context to notify the native system of state 
 * transition events of the JVM and Java application.
 * The following events are issued in the following order when the application normally starts.
 * -# #AJMS_VMEVENT_VM_STARTED
 * -# #AJMS_VMEVENT_VM_PAINTREADY
 * -# #AJMS_VMEVENT_APP_STARTED
 * .
 * If a certain time elapses after the AMS calls ajms_arc_runApp() and these notifications have not been made, 
 * call ajms_arc_terminateApp() to force termination. 
 * The timeout time should be decided in the native system based on factors such as CPU performance and storage file access speed. 
 *
 */
AJ_S32  ajms_arc_runAppEx1(
                const AJ_S32                      jadSize,
                const AJ_U8                      *jadAddr,
                AJMS_Reader                       jadRead,
                const AJ_S32                      jarSize,
                const AJ_U8                      *jarAddr,
                AJMS_Reader                       jarRead,
                AJMS_VmEventHandler               vmEventHandler);

/**
 *        Sets the JVM parameters.
 * @param vmParamCount
 *        The number of parameters passed to the JVM.
 *        Ordinarily 0 is designated.
 *        A value of 1 or above may be designated for the purpose of checking JVM behavior.
 * @param vmParams
 *        A pointer to the memory location of the parameter string array to be passed to the JVM. 
 *        Ordinarily #AJ_NULL is designated.
 *        For checking JVM behavior, values may be designated in the format below: 
 * @code
 * static const AJ_U8 *vmParams[] =
 * {
 *  "-a_option",
 *  "-some_option"
 * };
 * @endcode
 * @param vmParamLens
 *        A pointer to the memory area holding an array of byte counts for strings passed to the JVM. 
 *        Ordinarily #AJ_NULL is designated.
 *        For checking JVM behavior, values may be designated in the format below: 
 * @code
 * static const AJ_U8 vmParamLens[] =
 * {
 *  9,    <-- "-a_option" character count
 *  12    <--"-some_option" character count
 * };
 * @endcode
 * @retval #AJMS_ERR_NONE     if the function succeeds.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * All the parameters are passed to the JVM during the next JVM lifecycle. 
 * To clean the parameters before JVM startup, call <b>ajms_arc_setParam(0, AJ_NULL, AJ_NULL)</b>.
 */
AJ_S32  ajms_arc_setParam(
                AJ_S32         vmParamCount,
                const AJ_U8  **vmParams,
                const AJ_S32  *vmParamLens);

/** @} */
/** @} */


/** 
 * @addtogroup ajms_arc_tck
 * An interface for performing an automated TCK testing loop.
 * This interface is implemented in AJSC.
 *
 * @par Include file 
 * \#include ajms_arc.h
 * @{
 */

/**
 *        Starts an automatic TCK loop.
 * @param tckUrl 
 *        A UTF-8 encoded NUL terminated character string representing the TCK server and the JAD file. 
 *        A typical TCK URL looks like this:
 *        @code
 *        "http://tck.aplix.co.jp:8000/test/getNextApp.jad"
 *        @endcode
 *        Here, <code>http://tck.aplix.co.jp</code> is the value set for <b>JavaTest Host Name</b> in the TCK server configuration. 
 *        <code>8000</code> is the value set for <b>TCK Server Port</b>.
 * @param vmEventHandler 
 *        The address of the JVM state notification callback function.
 *        This address must remain valid until the JVM terminates.
 *
 * @retval #AJMS_ERR_NONE     if the function succeeds in sending a launch request.
 * @retval #AJMS_ERR_INTERNAL if the function fails.
 *
 * This function only sends a launch request to the KVE thread by using kjava_sys_sendAction() and returns to the caller.
 *
 * The request triggers an automatic TCK testing loop.
 * Note that this cannot be used for OTA TCK testing.
 *
 * Note that JAD/JAR download over HTTP during the TCK loop is performed by means of @ref kjava_sys_http KSIs.
 * This means you need to have implemented a workable HTTP network communication feature when using ajms_arc_startTck().
 *
 * The callback function @ref AJMS_VmEventHandler "vmEventHandler" is called in the KVE thread context to notify the native system of state 
 * transition events of the JVM and Java application. 
 *
 * When the TCK loop is executed, in addition to the events when an application is executed, 
 * the following events are passed via the callback function {@link #AJMS_VmEventHandler vmEventHandler}.
 *
 * <ol>
 * <li> #AJMS_TCKEVENT_STARTED
 * <li> #AJMS_TCKEVENT_JAD_DOWNLOADED
 * <li> #AJMS_TCKEVENT_JAD_CHECKED
 * <li> #AJMS_TCKEVENT_JAR_DOWNLOADED
 * <li> #AJMS_TCKEVENT_INSTALLED
 * <li> #AJMS_TCKEVENT_VM_TERMINATED
 * <li> #AJMS_TCKEVENT_EXITED_NORMALLY or #AJMS_TCKEVENT_EXITED_WITH_ERROR
 * </ol>
 * 
 * Each of events indicates the progress of the TCK loop.
 * 
 * - The event 1 (#AJMS_TCKEVENT_STARTED) is issued only once when the TCK loop starts.
 * - When a TCK test application is executed normally, all the events 2 to 6 are issued. 
 *   This is repeated for all the test applications.
 * - After #AJMS_TCKEVENT_INSTALLED is issued until #AJMS_TCKEVENT_VM_TERMINATED is issued, 
 *   JVM events for the launched TCK test application are issued in usual manner.
 * - When all the test applications have been finished normally, #AJMS_TCKEVENT_EXITED_NORMALLY is issued indicating normal completion.
 * - If an error occurs in a step, events to be issued after that step are not issued and 
 *   finally #AJMS_TCKEVENT_EXITED_WITH_ERROR is issued indicating the failure.
 *
 *
 */
AJ_S32  ajms_arc_startTck(const char* tckUrl, AJMS_VmEventHandler vmEventHandler);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AJMS_OTA_HEADER */



