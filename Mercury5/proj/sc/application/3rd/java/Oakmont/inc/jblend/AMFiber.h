/*
 * Copyright 2006-2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMFiber.h
 * Fiber JBI
 */

#ifndef __AM_FIBER_H
#define __AM_FIBER_H

#include "JkTypesFiber.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_JBI Fiber JBI
 * @{
 *  An interface for operating a Fiber.
 *
 *  The functions in this interface can be used to manage Fiber object 
 *  state, access Fiber object information and synchronize execution of 
 *  individual Fiber objects.
 *
 *  The memory resources used in the Fiber object are provided through the 
 *  @ref Fiber_Pool_JBI functions. Refer to the 
 *  #AmFiberPoolCreateFiber() and #AmFiberPoolCreate() functions for more 
 *  details.
 * 
 *  @par Note:
 *  All Fiber objects within the same Fiber Pool must execute within the 
 *  same thread or process context. 
 *
 *  @par Warning: 
 *  The Fiber JBI is <b>not</b> thread-safe.
 */

/**
 *  Gets the time statistics for the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param psTimeStatistics
 *   A pointer to a Fiber time statistics object.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The @ref JKT_Fiber_TimeStatistics "time statistics" referenced by the 
 *  <i>psTimeStatistics</i> pointer are updated with the latest 
 *  information available for the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 * 
 *  Fibers may access the time statistics of other Fibers.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context. 
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberGetTimeStatistics( JKFiberHandle hFiber, JKT_Fiber_TimeStatistics *psTimeStatistics );

/**
 *  Gets the context value associated with the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param pulContext
 *   A pointer to a context buffer.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The memory referenced by the <i>pulContext</i> pointer is updated with 
 *  the context value for the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 * 
 *  The initial value of the context associated with the Fiber is 
 *  <code>0x00000000</code> when it is created via the
 *  #AmFiberPoolCreateFiber() function.
 *
 *  Fibers may access the context value associated with other Fibers.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberPoolCreateFiber
 * 
 */

long AmFiberGetContext( JKFiberHandle hFiber, unsigned long *pulContext );

/**
 *  Sets the context value associated with the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param ulContext
 *   A context value to be stored in the Fiber object.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The context value for the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i> is updated with the contents of <i>ulContext</i>. 
 * 
 *  The value of <i>ulContext</i> can be any value and is defined by the 
 *  Fiber object owner. The context is not used internally by the Fiber 
 *  Service library.
 *
 *  Fibers may set the context value associated with other Fibers.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSetContext( JKFiberHandle hFiber, unsigned long ulContext );

/**
 *  Gets the scheduling priority associated with the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param pschPriority
 *   A pointer to a scheduling priority buffer.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The memory referenced by the <i>pschPriority</i> pointer is updated with 
 *  the scheduling priority for the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 * 
 *  All Fibers created using #AmFiberPoolCreateFiber() will have a @ref 
 *  JK_FIBER_PRIORITY_DEFAULT "default" scheduling priority applied. 
 * 
 *  Fibers may access the scheduling priority of other Fibers.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberSetPriority
 * 
 */

long AmFiberGetPriority( JKFiberHandle hFiber, signed char *pschPriority );

/**
 * @name Fiber Execution Priority
 * @{
 */

/**
 *  The maximum Fiber priority permitted.
 */
#define JK_FIBER_PRIORITY_LIMIT_HIGH                (20)

/**
 *  The minimum Fiber priority permitted.
 */
#define JK_FIBER_PRIORITY_LIMIT_LOW                 (-20)

/**
 *  The default Fiber priority.
 */
#define JK_FIBER_PRIORITY_DEFAULT                   (0)

/**
 * @}
 */

/**
 *  Sets the scheduling priority associated with the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param schPriority
 *   A scheduling priority to be applied to the Fiber object.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The scheduling priority for the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i> is updated with the contents of <i>schPriority</i>. 
 * 
 *  Valid values for the <i>schPriority</i> parameter are between 
 *  #JK_FIBER_PRIORITY_LIMIT_HIGH and #JK_FIBER_PRIORITY_LIMIT_LOW 
 *  inclusive.
 * 
 *  The scheduling priority changes will not affect the Fiber until the 
 *  next @ref Fiber_Scheduler_JBI "Fiber Scheduler" loop. This means that 
 *  Fiber's scheduling priority can change multiple times before the 
 *  impact to scheduling is observed.
 *
 *  Fibers may change their own scheduling priority and that of other 
 *  Fibers. 
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberPoolCreateFiber, AmFiberGetPriority
 *
 */

long AmFiberSetPriority( JKFiberHandle hFiber, signed char schPriority );

/**
 * @name Fiber State
 * @{
 */

/**
 *  The Fiber is offline. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_OFFLINE                      (0x00)

/**
 * @internal
 *                  (not documented)
 *  The Fiber is in an invalid state. A Fiber may enter this state 
 *  during the startup sequence if there is a failure.
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_INVALID                      (0x01)

/**
 *  The Fiber is ready to start. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_READY                        (0x02)

/**
 *  The Fiber is started but not yet running. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_STARTED                      (0x03)

/**
 *  The Fiber is stopped. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_STOPPED                      (0x04)

/**
 *  The Fiber actively running. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_RUNNING                      (0x05)

/**
 *  The Fiber is sleeping. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_SLEEPING                     (0x06)

/**
 *  The Fiber is suspended. 
 *  See the @ref page_state_transition "Fiber state transition" 
 *  documentation for more details.
 */
#define JK_FIBER_STATE_SUSPENDED                    (0x07)

/**
 * @internal
 *                  (not documented)
 *  The Fiber is in the process of executing the #JK_FIBER_TICKER 
 *  function. No processing in the context of the Fiber should occur 
 *  during this state. See the @ref 
 *  page_state_transition "Fiber state transition" documentation for more 
 *  details.
 */
#define JK_FIBER_STATE_TRANSIENT                    (0x08)

/**
 * @}
 */

/**
 *  A reserved Fiber state structure for future expansion. This structure 
 *  is used to describe Fibers in either
 *  @ref JK_FIBER_STATE_OFFLINE "offline",
 *  @ref JK_FIBER_STATE_STARTED "started",
 *  @ref JK_FIBER_STATE_RUNNING "running" or
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended" states. 
 */
typedef struct _JKT_Fiber_State_Reserved {
    /**
     *  A reserved parameter block for future expansion.
     */
    unsigned long   m_ulReserved;
} JKT_Fiber_State_Reserved;

/**
 * @internal
 *                  (not documented)
 *  An invalid Fiber state structure. This structure 
 *  is used to describe Fibers in an
 *  @ref JK_FIBER_STATE_INVALID "invalid" state.
 */
typedef struct _JKT_Fiber_State_Invalid {
    /**
     * @internal
     *                  (not documented)
     *  An error code describing the cause of the invalid Fiber state.
     */
    unsigned long   m_lErrorCode;
} JKT_Fiber_State_Invalid;


/**
 * @name Fiber Exit Style
 * @{
 */

/**
 *  The Fiber exited under its own control.
 */
#define JK_FIBER_EXIT_STYLE_SELF                    (0x00000001)

/**
 *  The Fiber exited at the command of another Fiber, the Fiber Pool or 
 *  the externally controlling Fiber, thread or process context.
 */
#define JK_FIBER_EXIT_STYLE_FORCED                  (0x00000002)

/**
 * @}
 */

/**
 *  A stopped Fiber state structure. This structure 
 *  is used to describe Fibers in either
 *  @ref JK_FIBER_STATE_READY "ready" or
 *  @ref JK_FIBER_STATE_STOPPED "stopped" states. 
 */
typedef struct _JKT_Fiber_State_Stopped {
    /**
     *  An exit code returned by a Fiber (or on behalf of a Fiber) when it 
     *  stopped.
     */
    long            m_lExitCode;

    /**
     *  One of the @ref JK_FIBER_EXIT_STYLE_SELF "JK_FIBER_EXIT_STYLE_XXX" 
     *  indicators.
     */
    unsigned long   m_ulExitStyle;
} JKT_Fiber_State_Stopped;

/**
 * @name Fiber Sleep Mode
 * @{
 */

/**
 *  The Fiber has entered a light sleep cycle which may be interrupted by 
 *  the #AmFiberResume() function.
 */
#define JK_FIBER_SLEEP_MODE_LIGHT                   (0x00000000)

/**
 *  The Fiber has entered a deep sleep cycle or suspension which may 
 *  <b>not</b> be interrupted by the #AmFiberResume() function.
 */
#define JK_FIBER_SLEEP_MODE_DEEP                    (0x00000001)

/**
 *  The bit-field mask used to access the sleep mode configuration.
 */
#define JK_FIBER_SLEEP_MODE_MASK                    (JK_FIBER_SLEEP_MODE_LIGHT | JK_FIBER_SLEEP_MODE_DEEP)

/**
 *  The bit-field position (zero-based offset) of the sleep mode 
 *  configuration.
 */
#define JK_FIBER_SLEEP_MODE_POS                     (0x00)

/**
 * @}
 */

/**
 * @name Fiber Sleep Type
 * @{
 */

/**
 *  The Fiber has entered a normal sleep cycle.
 */
#define JK_FIBER_SLEEP_TYPE_NORMAL                  (0x00000000)

/**
 *  The Fiber has entered a sleep cycle as part of an #AmFiberJoin() 
 *  process.
 */
#define JK_FIBER_SLEEP_TYPE_ENTWINED                (0x00000002)

/**
 *  The Fiber has entered a sleep cycle as part of an 
 *  #AmFiberEventWait() process.
 */
#define JK_FIBER_SLEEP_TYPE_EVENT                   (0x00000004)

/**
 *  The Fiber has entered a sleep cycle as part of an 
 *  #AmFiberSectionEnter() process.
 */
#define JK_FIBER_SLEEP_TYPE_SECTION                 (0x00000008)

/**
 *  The bit-field mask used to access the sleep cycle state.
 */
#define JK_FIBER_SLEEP_TYPE_MASK                    (JK_FIBER_SLEEP_TYPE_NORMAL | JK_FIBER_SLEEP_TYPE_ENTWINED | JK_FIBER_SLEEP_TYPE_EVENT | JK_FIBER_SLEEP_TYPE_SECTION)

/**
 *  The bit-field position (zero-based offset) of the sleep cycle state.
 */
#define JK_FIBER_SLEEP_TYPE_POS                     (0x01)

/**
 * @}
 */

/**
 *  A sleeping Fiber state structure. This structure 
 *  is used to describe Fibers in a
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping" state.
 */
typedef struct _JKT_Fiber_State_Sleeping {
    /**
     *  A bit-wise OR'ing of @ref 
     *  JK_FIBER_SLEEP_TYPE_NORMAL "JK_FIBER_SLEEP_TYPE_XXX" and 
     *  @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX" values.
     */
    unsigned long   m_ulFlags;

    /**
     *  The time tick at which the Fiber will be awakened.
     * 
     *  @par Warning:
     *  It is possible for the value of this variable to roll-over when 
     *  the <i>ulDuration</i> added to the time tick returned from the
     *  @ref JK_FIBER_TICKER "tick function" when the Fiber was put to 
     *  sleep is greater than what can be stored in a #JKT_Time_ms 
     *  variable. 
     */
    JKT_Time_ms     m_ullSleepTime;
} JKT_Fiber_State_Sleeping;

/**
 *  A Fiber state structure.
 */
typedef struct _JKT_Fiber_State {
    /**
     *  The current @ref JK_FIBER_STATE_OFFLINE "state" of the Fiber 
     *  object.
     */
    unsigned char   m_uchState;

    /**
     *  A union of the #JKT_Fiber_State_Reserved, 
     *  #JKT_Fiber_State_Stopped and 
     *  #JKT_Fiber_State_Sleeping. Use of the appropriate union member
     *  depends on the value of the <i>m_uchState</i>.
     */
    union {
        /**
         * @internal
         *                  (not documented)
         *  A reserved Fiber state structure.
         */
        JKT_Fiber_State_Reserved    m_sReserved;

        /**
         * @internal
         *                  (not documented)
         *  A state structure for Fibers in an @ref 
         *  _JKT_Fiber_State_Invalid "invalid" state.
         */
        JKT_Fiber_State_Invalid     m_sInvalid;

        /**
         * @internal
         *                  (not documented)
         *  A state structure for Fibers in either @ref 
         *  _JKT_Fiber_State_Stopped "stopped" or @ref 
         *  _JKT_Fiber_State_Stopped "ready "states.
         */
        JKT_Fiber_State_Stopped     m_sStopped;

        /**
         * @internal
         *                  (not documented)
         *  A state structure for Fibers in an @ref 
         *  _JKT_Fiber_State_Sleeping "sleeping" state.
         */
        JKT_Fiber_State_Sleeping    m_sSleeping;
    } u;
} JKT_Fiber_State;

/**
 *  Gets the current Fiber state.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param psFiberState
 *   A pointer to a Fiber state structure.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The current state information for the @ref Fiber_JBI "Fiber", 
 *  specified by <i>hFiber</i>, is copied into the structure referenced 
 *  by <i>psFiberState</i>. 
 * 
 *  Fibers may query their own state and that of other Fibers. See the 
 *  @ref page_state_transition "Fiber state transition" documentation for 
 *  more details.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 * 
 */

long AmFiberGetState( JKFiberHandle hFiber, JKT_Fiber_State *psFiberState );

/**
 *  Fiber start or stop main.
 * 
 *  @param pvData
 *    A pointer the Fiber start or stop data respectively.
 *  @return
 *    When the function is a Fiber start function, the return value 
 *    is obtainable through the AmFiberGetState() or AmFiberJoin() function 
 *    as the exit code.
 * 
 *  <p>
 *  Regardless of its use as a Fiber start (via <i>pfStart</i>) or stop 
 *  (via <i>pfStop</i>) function, this function type is used as the main 
 *  entry point to the Fiber execution context passed to the 
 *  AmFiberStart() function.
 * 
 *  Calls to this function will operate with the stack allocated to the 
 *  Fiber during creation by #AmFiberPoolCreateFiber(). The stack will be 
 *  cleared before each function invocation.
 * 
 *  The <i>pvData</i> parameter will receive either the AmFiberStart() function 
 *  <i>pvStartData</i> or <i>pvStopData</i> parameter value depending on the Fiber start or 
 *  stop execution mode in use.
 * 
 *  Once executing, the Fiber function holds control of the CPU until it 
 *  yields processing time back to the @ref Fiber_Scheduler_JBI 
 *  "Fiber Scheduler". Yields can occur through calls to #AmFiberStop(), 
 *  #AmFiberSleep(), #AmFiberYield(), #AmFiberJoin, #AmFiberEventWait() 
 *  and #AmFiberSectionEnter() when operating as a Fiber <i>pfStart</i> 
 *  function. Fiber <i>pfStop</i> functions are not permitted to yield.
 * 
 *  @see AmFiberStart
 */

typedef long ( * JK_FIBER_FUNCTION ) ( void *pvData );

/**
 *  Starts a Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param pfStart
 *   A pointer to the function used when the Fiber is executed.
 *  @param pvStartData
 *   A pointer provided to the <i>pfStart</i> function when the 
 *   Fiber is executed. This parameter may be JK_NULL.
 *  @param pfStop
 *   A pointer to the function used when the Fiber is stopped. This 
 *   parameter may be JK_NULL.
 *  @param pvStopData
 *   A pointer provided to the <i>pfStop</i> function when the 
 *   Fiber is stopped. This parameter may be JK_NULL.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in the @ref JK_FIBER_STATE_READY "ready"
 *     state or invalid thread (or process) context execution is detected.
 * 
 *  <p>
 *  This function starts the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>. As a result of this function call, the function 
 *  specified by <i>pfStart</i> will be called during the next Fiber 
 *  Scheduler invocation with its own execution context and 
 *  stack. The <i>pfStart</i> function will receive the value of the 
 *  <i>pvStartData</i> parameter during execution. Likewise, the 
 *  <i>pfStop</i> function will receive the value of <i>pvStopData</i> 
 *  during execution.
 * 
 *  The values of <i>pvStartData</i> and <i>pvStopData</i> can be any 
 *  value and are defined by the Fiber object owner. The pointers are not 
 *  used internally by the Fiber Service library.
 * 
 *  If the <i>pfStop</i> parameter points to a stop function, that 
 *  function will be called during Fiber finalization. Otherwise, Fiber 
 *  finalization will occur without interruption.
 * 
 *  The intention of the Fiber stop function is to allow for cleanup of 
 *  the Fiber state regardless of how the Fiber was @ref 
 *  JK_FIBER_EXIT_STYLE_SELF "terminated".
 * 
 *  Fibers may use this function to start other Fibers.
 * 
 *  @par Optimization:
 *  If the Fiber stop function is used, please make all efforts to 
 *  minimize the amount of code and CPU time consumed by the function. 
 *  Delays in @ref AmFiberPoolDestroy "Fiber Pool shutdown" can occur if 
 *  care is not taken in the implementation of this function.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber (other than itself), thread 
 *  or process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberPoolDestroy
 * 
 */

long AmFiberStart( JKFiberHandle hFiber, JK_FIBER_FUNCTION pfStart, void *pvStartData, JK_FIBER_FUNCTION pfStop, void *pvStopData );

/**
 *  Stops a Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param lExitCode
 *   The value of the exit code for the Fiber.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state or invalid thread 
 *     or process context execution is detected.
 * 
 *  <p>
 *  This function stops the @ref Fiber_JBI "Fiber", specified by 
 *  <i>hFiber</i>, and sets its exit code to the value specified by 
 *  the <i>lExitCode</i> parameter.
 *
 *  There are two Fiber exit styles: @ref 
 *  JK_FIBER_EXIT_STYLE_SELF "self termination" and @ref 
 *  JK_FIBER_EXIT_STYLE_FORCED "forced termination".
 * 
 *  When the object handle is specified in the target <i>hFiber</i> 
 *  parameter matches that of the calling Fiber, the execution context 
 *  will switch to the @ref Fiber_Scheduler_JBI "Fiber Scheduler". This 
 *  immediately terminates the Fiber and changes it to the @ref 
 *  JK_FIBER_STATE_STOPPED "stopped" state. This is called @ref 
 *  JK_FIBER_EXIT_STYLE_SELF "self termination".
 * 
 *  Additionally, cases where a Fiber simply exits from its @ref 
 *  JK_FIBER_FUNCTION "start" function are also considered self 
 *  termination. When this happens, the return value of the Fiber start 
 *  function is used as the exit code for the Fiber.
 * 
 *  Conversely, Fibers may use this function to stop other Fibers. When 
 *  this function is called by a Fiber other than the one specified by 
 *  the target <i>hFiber</i> parameter, the state of the target Fiber will 
 *  transition to a @ref JK_FIBER_STATE_STOPPED "stopped" state. This 
 *  is called @ref JK_FIBER_EXIT_STYLE_FORCED "forced termination".
 * 
 *  In both exit styles, the target Fiber will never be scheduled for 
 *  execution again and the finalization process will commence. See 
 *  the #AmFiberPoolCreateFiber function for details regarding the 
 *  finalization  processes which may apply to the Fiber. 
 * 
 *  Any resources like @ref Fiber_Synced_Object_JBI "synchronized objects" 
 *  held by the Fiber will be released.
 * 
 *  Valid states for the target Fiber are 
 *  @ref JK_FIBER_STATE_STARTED "started", 
 *  @ref JK_FIBER_STATE_RUNNING "running", 
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended", 
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping", and  
 *  @ref JK_FIBER_STATE_STOPPED "stopped". 
 *  This function will return an error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  these requirements.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context. 
 *  When called from a Fiber, the function call must originate on the 
 *  thread or process which hosts the @ref Fiber_Pool_JBI "Fiber Pool".
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberStop( JKFiberHandle hFiber, long lExitCode );

/**
 * @name Fiber Suspend Count
 * @{
 */

/**
 *  Defines the maximum number of suspend references that can be applied to a Fiber.
 */
#define JK_FIBER_SUSPEND_COUNT_LIMIT                (0xFFFFFFFF)

/**
 * @}
 */

/**
 *  Suspends a Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param pulSuspendCount
 *   A pointer to a buffer which will receive the Fiber suspend 
 *   count. This parameter may be JK_NULL.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state or invalid thread 
 *     or process context execution is detected.
 *   - #JK_RESULT_FIBER_SUSPEND_COUNT_OVERFLOW
 *     when the Fiber suspend count limit would be exceeded. In
 *     this condition, the suspend count is not increased further.
 * 
 *  <p>
 *  This function suspends the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 *
 *  There are two Fiber suspension styles: self suspension and forced 
 *  suspension.
 * 
 *  When the object handle is specified in the target <i>hFiber</i> 
 *  parameter matches that of the calling Fiber, the execution context 
 *  will switch to the @ref Fiber_Scheduler_JBI "Fiber Scheduler". This 
 *  immediately @ref JK_FIBER_STATE_SUSPENDED "suspends" the Fiber. This 
 *  is called self suspension.
 * 
 *  Conversely, Fibers may use this function to suspend other Fibers. When 
 *  this function is called by a Fiber other than the one specified by 
 *  the target <i>hFiber</i> parameter, the state of the target Fiber will 
 *  transition to a @ref JK_FIBER_STATE_SUSPENDED "suspended" state. 
 *  This is called forced suspension.
 * 
 *  In both suspension styles, the target Fiber will never be scheduled 
 *  for execution again unless the #AmFiberResume() function is called 
 *  using its handle as the target. Suspended Fibers can be stopped at any 
 *  time via #AmFiberStop() or #AmFiberPoolDestroy().
 * 
 *  Fiber suspension will only occur when the suspend count for the target 
 *  Fiber is zero (0). Subsequent calls on an already suspended Fiber will 
 *  simply increase the suspend count.
 * 
 *  Upon successful return or the occurrence of 
 *  #JK_RESULT_FIBER_SUSPEND_COUNT_OVERFLOW the value of the Fiber suspend 
 *  reference count associated with <i>hFiber</i> will be stored in 
 *  <i>pulSuspendCount</i>. The value provided in <i>pulSuspendCount</i> 
 *  may be set to #JK_NULL if the data is not needed.
 * 
 *  Valid states for the target Fiber are 
 *  @ref JK_FIBER_STATE_RUNNING "running" and 
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  these requirements.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context. 
 *  When called from a Fiber, the function call must originate on the 
 *  thread or process which hosts the @ref Fiber_Pool_JBI "Fiber Pool".
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberResume, AmFiberStop, AmFiberPoolDestroy
 * 
 */

long AmFiberSuspend( JKFiberHandle hFiber, unsigned long *pulSuspendCount );

/**
 *  Resumes a Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param pulSuspendCount
 *   A pointer to a buffer which will receive the Fiber suspend 
 *   count. This parameter may be JK_NULL.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state or invalid thread 
 *     or process context execution is detected.
 *   - #JK_RESULT_FIBER_SLEEP_DEEP<br>
 *     when the Fiber has been put to sleep using the 
 *     #JK_FIBER_SLEEP_MODE_DEEP flag, or the Fiber is attempting to 
 *     re-gain lock on a Synchronized Section Object via 
 *     AmFiberSectionSynchronize().
 *
 *  <p>
 *  This function resumes the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 *
 *  Fibers may use this function to resume other @ref 
 *  JK_FIBER_STATE_SLEEPING "sleeping" or @ref 
 *  JK_FIBER_STATE_SUSPENDED "suspended" Fibers. When this function is 
 *  called, the state of the target Fiber will transition to the @ref 
 *  JK_FIBER_STATE_RUNNING "running" state.
 * 
 *  The target Fiber will be scheduled for execution again unless the 
 *  #AmFiberStop() function targeting the Fiber or the 
 *  #AmFiberPoolDestroy() function is called before its context execution 
 *  resumes.
 * 
 *  Fiber resume will only occur when the suspend count for the target Fiber
 *  is zero (0). Calls on an suspended Fiber with a suspend count greater
 *  than one (1) will simply decrease its suspend count.
 * 
 *  Upon successful return, the value of the Fiber suspend reference count
 *  associated with <i>hFiber</i> will be stored in <i>pulSuspendCount</i>.
 *  The value provided in <i>pulSuspendCount</i> may be set to #JK_NULL 
 *  if the data is not needed.
 *
 *  Valid states for the target Fiber are 
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping",  
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended" and
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  these requirements.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber (other than the suspended 
 *  Fiber itself), thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberStop, AmFiberPoolDestroy
 * 
 */

long AmFiberResume( JKFiberHandle hFiber, unsigned long *pulSuspendCount );

/**
 *  Resumes a Fiber without regard to its suspend reference count.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state or invalid thread 
 *     or process context execution is detected.
 *   - #JK_RESULT_FIBER_SLEEP_DEEP<br>
 *     when the Fiber has been put to sleep using the 
 *     #JK_FIBER_SLEEP_MODE_DEEP flag, or the Fiber is attempting to 
 *     re-gain lock on a Synchronized Section Object via 
 *     AmFiberSectionSynchronize().
 *
 *  <p>
 *  This function resumes the @ref Fiber_JBI "Fiber" specified by 
 *  <i>hFiber</i>.
 *
 *  Fibers may use this function to resume other @ref 
 *  JK_FIBER_STATE_SLEEPING "sleeping" or @ref 
 *  JK_FIBER_STATE_SUSPENDED "suspended" Fibers. When this function is 
 *  called, the state of the target Fiber will transition to the @ref 
 *  JK_FIBER_STATE_RUNNING "running" state.
 * 
 *  The target Fiber will be scheduled for execution again unless the 
 *  #AmFiberStop() function targeting the Fiber or the 
 *  #AmFiberPoolDestroy() function is called before its context execution 
 *  resumes.
 * 
 *  Upon successful return from this function, the target Fiber's suspend
 *  count will be zero (0).
 * 
 *  Valid states for the target Fiber are 
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping",  
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended" and
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  these requirements.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber (other than the suspended 
 *  Fiber itself), thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberResume, AmFiberStop, AmFiberPoolDestroy
 * 
 */

long AmFiberContinue( JKFiberHandle hFiber );

/**
 *  Puts a Fiber to sleep.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param ulFlags
 *   Attributes controlling the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to stay sleeping.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state or invalid thread 
 *     or process context execution is detected.
 *   - #JK_RESULT_FIBER_SLEEP_INTERRUPTED<br>
 *     when the Fiber's sleep was interrupted by #AmFiberResume().
 *
 *  <p>
 *  This function places a @ref Fiber_JBI "Fiber", specified by 
 *  <i>hFiber</i>, into a @ref JK_FIBER_STATE_SLEEPING "sleep" state.
 *
 *  Valid values for <i>ulFlags</i> are either the 
 *  #JK_FIBER_SLEEP_MODE_LIGHT flag or the #JK_FIBER_SLEEP_MODE_DEEP flag.
 *  All other values are ignored.
 * 
 *  If the #JK_FIBER_SLEEP_MODE_LIGHT flag is specified, the target Fiber 
 *  can be awakened using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this sleep interruption 
 *  feature and allows the Fiber to complete a natural sleep cycle 
 *  (assuming it is not stopped beforehand).
 * 
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  sleep duration of <code>0x00000000</code> is effectively the same as 
 *  @ref AmFiberYield "yielding" the Fiber execution context to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler". A sleep duration of 
 *  <code>0xFFFFFFFF</code> is <b>not</b> the same as @ref 
 *  AmFiberSuspend "suspending" the Fiber since it will eventually wake up 
 *  in about 50 days and depending on the <i>ulFlags</i> parameter 
 *  value, may not be resumed via the #AmFiberResume() function.
 * 
 *  There are two Fiber sleep styles: self sleep and forced sleep.
 * 
 *  When the object handle is specified in the target <i>hFiber</i> 
 *  parameter matches that of the calling Fiber, the execution context 
 *  will switch to the @ref Fiber_Scheduler_JBI "Fiber Scheduler". This 
 *  immediately puts the Fiber to @ref JK_FIBER_STATE_SLEEPING "sleep". 
 *  This is called self sleeping.
 * 
 *  Conversely, Fibers may use this function to put other Fibers to sleep. 
 *  When this function is called by a Fiber other than the one specified by 
 *  the target <i>hFiber</i> parameter, the state of the target Fiber will 
 *  transition to a @ref JK_FIBER_STATE_SLEEPING "sleeping" state. 
 *  This is called forced sleeping.
 * 
 *  In both sleep styles, the target Fiber will never be scheduled 
 *  for execution again unless the #AmFiberResume() function is called 
 *  using its handle as the target or the @ref
 *  Fiber_Scheduler_JBI "Fiber Scheduler" determines that it is time to 
 *  wake it up. Sleeping Fibers can be stopped at any time via 
 *  #AmFiberStop() or #AmFiberPoolDestroy().
 * 
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Important:
 *  For performance reasons, instead of using this function with a 
 *  <i>ulDuration</i> of <code>0x00000000</code>, consider using the
 *  #AmFiberYield(). Additionally, if the Fiber can be suspended (instead 
 *  of simply put to sleep for a very long time) consider using the 
 *  #AmFiberSuspend() function. Putting a Fiber to sleep is more costly on 
 *  performance than using these two functions in their respective 
 *  situations. This is especially true when suspending a Fiber instead of 
 *  putting it to sleep for a long time.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context. 
 *  When called from a Fiber, the function call must originate on the 
 *  thread or process which hosts the @ref Fiber_Pool_JBI "Fiber Pool".
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberYield, AmFiberSuspend, AmFiberResume, AmFiberStop, 
 *  AmFiberPoolDestroy 
 * 
 */

long AmFiberSleep( JKFiberHandle hFiber, unsigned long ulFlags, unsigned long ulDuration );

/**
 *  Yields execution of the Fiber.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context, specified by <i>hFiber</i>, to the @ref
 *  Fiber_Scheduler_JBI "Fiber Scheduler".
 *
 *  When the object handle is specified in the target <i>hFiber</i> 
 *  parameter matches that of the calling Fiber, the execution context 
 *  will switch to the @ref Fiber_Scheduler_JBI "Fiber Scheduler". This 
 *  keeps the Fiber in the @ref JK_FIBER_STATE_RUNNING "running" state 
 *  while allowing other Fibers to be scheduled.
 *  
 *  Fibers may <b>not</b> use this function to yield other Fibers 
 *  (theoretically because their execution contexts are not on the CPU).
 * 
 *  The target Fiber will be scheduled for execution again unless it is
 *  stopped via the #AmFiberStop() or #AmFiberPoolDestroy() functions 
 *  before the next context execution cycle.
 * 
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberStop, AmFiberPoolDestroy
 * 
 */

long AmFiberYield( JKFiberHandle hFiber );

/**
 * @name Fiber Synchronization Method
 * @{
 */

/**
 *  The Fiber will block by sleeping during an attempt to engage a 
 *  Synchronized Object.
 */
#define JK_FIBER_SYNC_METHOD_SLEEP                  (0x00000000)

/**
 *  The Fiber will first test, and instead, <b>not</b> block during 
 *  an attempt to engage a Synchronized Object.
 */
#define JK_FIBER_SYNC_METHOD_TEST_ONLY              (0x00000004)

/**
 *  The bit-field mask used to access the synchronization method
 *  settings.
 */
#define JK_FIBER_SYNC_METHOD_MASK                   (JK_FIBER_SYNC_METHOD_SLEEP | JK_FIBER_SYNC_METHOD_TEST_ONLY)

/**
 *  The bit-field position (zero-based offset) of the synchronization 
 *  method settings.
 */
#define JK_FIBER_SYNC_METHOD_POS                    (0x02)

/**
 * @}
 */

/**
 *  Suspends execution of one Fiber until another Fiber terminates.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hFiberTarget
 *   A valid join target Fiber object handle.
 *  @param plExitCode
 *   A pointer to a buffer which will receive the exit code from the 
 *   <i>hFiberTarget</i> Fiber after it terminates. This parameter may be 
 *   JK_NULL.
 *  @param ulFlags
 *   Attributes controlling the synchronization method and potentially 
 *   the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the join to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber or the join target Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the join process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the join process is interrupted by #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the join period expires without the join target Fiber 
 *     terminating.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context specified by <i>hFiber</i> to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" for a period of time, as 
 *  indicated via the <i>ulDuration</i> parameter, during which the 
 *  join target Fiber specified by the <i>hFiberTarget</i> parameter will 
 *  hopefully terminate. The error code #JK_RESULT_FIBER_SYNC_TIMEOUT 
 *  is returned, signaling a join failure, if the join target Fiber does 
 *  not terminate before the <i>ulDuration</i> parameter expires.
 * 
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags and 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags. All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  join process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber join process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the join 
 *  would occur, then the function will return #JK_RESULT_FIBER_BUSY. 
 * 
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 *
 *  The following flags apply when a blocked join is performed by putting 
 *  the Fiber to @ref JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the 
 *  #JK_FIBER_SLEEP_MODE_LIGHT flag is specified (default), the target 
 *  Fiber join process can be interrupted using the #AmFiberResume() 
 *  function. Use of the #JK_FIBER_SLEEP_MODE_DEEP flag counters this 
 *  join interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  Fibers may <b>not</b> use this function to join another Fiber to yet 
 *  another. As an example, Fiber "A" cannot force target Fiber "B" to sleep 
 *  while waiting for the join target Fiber "A" to terminate. Only when the 
 *  object handle specified in the target <i>hFiber</i> parameter matches 
 *  that of the calling Fiber, will a join process be initiated.
 * 
 *  If the join target Fiber is 
 *  @ref JK_FIBER_STATE_STARTED "started", 
 *  @ref JK_FIBER_STATE_RUNNING "running", 
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended" or
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping" then it will be entwined with 
 *  the target Fiber. If not, the function will return an error 
 *  of #JK_RESULT_FIBER_BAD_STATE. 
 * 
 *  Entwining is the process of locking the target Fiber to the join 
 *  target Fiber and then switching the execution context of the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler". Target Fibers can be 
 *  disconnected from their respective join target Fiber if they are @ref 
 *  AmFiberStop "stopped" or @ref AmFiberResume "awakened".
 * 
 *  When the join succeeds, whereby the join target Fiber has terminated, 
 *  the target Fiber is awakened and scheduled for execution. In this 
 *  case, if the <i>plExitCode</i> is pointing to a buffer, the memory 
 *  referenced will be updated with the exit code of the join target Fiber.
 * 
 *  When the join fails, whereby the join target Fiber has <b>not</b> 
 *  terminated, the target Fiber is instead simply awakened and scheduled 
 *  for execution; either naturally by the Fiber Scheduler or via the 
 *  #AmFiberResume() function. In this case, if the <i>plExitCode</i> is 
 *  pointing to a buffer, the memory referenced will be set to 
 *  <code>0x00000000</code>.
 * 
 *  Regardless of the result of the join process, there is the 
 *  potential for the target Fiber to be removed from the scheduling queue 
 *  if it is stopped via the #AmFiberStop() or #AmFiberPoolDestroy() 
 *  functions before the next context execution cycle.
 * 
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberStop, AmFiberPoolDestroy, AmFiberResume
 * 
 */

long AmFiberJoin( JKFiberHandle hFiber, JKFiberHandle hFiberTarget, long *plExitCode, unsigned long ulFlags, unsigned long ulDuration );

/**
 *  Enters a synchronized section.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedSection
 *   A valid Synchronized Section object handle.
 *  @param ulFlags
 *   Attributes controlling the synchronization method and potentially 
 *   the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the synchronization to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the synchronization process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the synchronization process is interrupted by #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the synchronization period expires without gaining a lock on 
 *     the Synchronized Section object.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context specified by <i>hFiber</i> to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" for a period of time, as 
 *  indicated via the <i>ulDuration</i> parameter, if a lock on the
 *  @ref Fiber_Synced_Object_Pool_JBI "Synchronized Section" object 
 *  specified by the <i>hSyncedSection</i> parameter cannot be obtained. 
 *  Upon synchronization failure, the error code
 *  #JK_RESULT_FIBER_SYNC_TIMEOUT is returned indicating that the Synchronized
 *  Section object was not unlocked before the <i>ulDuration</i> parameter 
 *  expired.
 *
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags and 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags. All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  synchronization process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber synchronization process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the 
 *  synchronization would occur, then the function will return 
 *  #JK_RESULT_FIBER_BUSY.
 *
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 * 
 *  The following flags apply when a blocked synchronization is 
 *  performed by putting the Fiber to @ref 
 *  JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the #JK_FIBER_SLEEP_MODE_LIGHT 
 *  flag is specified (default), the target Fiber synchronization process 
 *  can be interrupted using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this synchronization 
 *  interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  In order to gain exclusive lock on a Synchronized Section object, no 
 *  other Fiber can be in the same section. If the lock is open, the 
 *  target Fiber will successfully gain immediate exclusive control of the 
 *  Synchronized Section object. Control of the Synchronized Section 
 *  object is not released until either the #AmFiberSectionExit(), 
 *  #AmFiberStop() or the #AmFiberPoolDestroy() functions are called on 
 *  the target Fiber.
 *
 *  When synchronization succeeds, the target Fiber will be scheduled for 
 *  execution again after the lock on the Synchronized Section object is 
 *  established. Any Fiber owning the lock on the Synchronized Section 
 *  object can repeatedly enter the same section with this function. An 
 *  equal number of calls to the #AmFiberSectionExit() function are 
 *  required to ensure proper release of the Synchronized Section object.
 * 
 *  The Synchronized Section object may also be unlocked and then 
 *  re-locked by another Fiber before the lock is granted to the blocking
 *  target Fiber. In such a case, the target Fiber will continue to wait 
 *  in slumber.
 * 
 *  When synchronization fails, whereby the Synchronized Section object 
 *  has <b>not</b> been locked by the target Fiber in time, the target 
 *  Fiber is instead simply awakened and scheduled for execution; either 
 *  naturally by the Fiber Scheduler or via the #AmFiberResume() 
 *  function.
 * 
 *  Regardless of the result of the synchronization process, there is the 
 *  potential for the target Fiber to be removed from the scheduling queue 
 *  if it is stopped via the #AmFiberStop() or #AmFiberPoolDestroy() 
 *  functions before the next context execution cycle.
 *
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberSectionExit, AmFiberStop, AmFiberPoolDestroy, 
 *  AmFiberResume
 * 
 */

long AmFiberSectionEnter( JKFiberHandle hFiber, JKFiberSyncedSectionHandle hSyncedSection, unsigned long ulFlags, unsigned long ulDuration );

/**
 * @name Fiber Synchronized Section Assignment Method
 * @{
 */

/**
 *  Requires that the target Fiber receive notification that it as been assigned 
 *  ownership of a Synchronized Object.
 */
#define JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY          (0x00000000)

/**
 *  Requires that the target Fiber NOT receive notification that it as been 
 *  assigned ownership of a Synchronized Object.
 */
#define JK_FIBER_SYNC_ASSIGN_METHOD_QUIET           (0x00000020)

/**
 *  The bit-field mask used to access the Synchronized Section assignment method
 *  settings.
 */
#define JK_FIBER_SYNC_ASSIGN_METHOD_MASK            (JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY | JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Section 
 *   assignment method settings.
 */
#define JK_FIBER_SYNC_ASSIGN_METHOD_POS             (0x05)

/**
 * @}
 */

/**
 * @name Fiber Synchronized Section Recipient Condition
 * @{
 */

/**
 *  The receiving Fiber may be in running condition when assigning it a 
 *  Synchronized Section. The state of the Fiber must be #JK_FIBER_STATE_RUNNING.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_RUNNING           (0x00000100)

/**
 *  The receiving Fiber may be in sleeping condition when assigning it a 
 *  Synchronized Section. The state of the Fiber must be 
 *  #JK_FIBER_STATE_SLEEPING without blocking on any other Synchronized Object.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_SLEEPING          (0x00000200)

/**
 *  The receiving Fiber may be in suspended condition when assigning it a 
 *  Synchronized Section. The state of the Fiber must be 
 *  #JK_FIBER_STATE_SUSPENDED without blocking on any other Synchronized Object.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_SUSPENDED         (0x00000400)

/**
 *  The receiving Fiber may be in dormant condition when assigning it a 
 *  Synchronized Section. The state of the Fiber must be either
 *  #JK_FIBER_STATE_SLEEPING or #JK_FIBER_STATE_SUSPENDED while blocking on at 
 *  least one Synchronized Object.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_BLOCKED           (0x00000800)

/**
 *  The bit-field mask used to access the Synchronized Section assignment 
 *  condition settings.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_MASK              (JK_FIBER_SYNC_ASSIGN_COND_RUNNING | JK_FIBER_SYNC_ASSIGN_COND_SLEEPING | JK_FIBER_SYNC_ASSIGN_COND_SUSPENDED | JK_FIBER_SYNC_ASSIGN_COND_BLOCKED)

/**
 *  The bit-field position (zero-based offset) of the Synchronized Section 
 *  assignment condition settings.
 */
#define JK_FIBER_SYNC_ASSIGN_COND_POS               (0x08)

/**
 * @}
 */

/**
 *  Enters another Fiber into a synchronized section.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hFiberRecipient
 *   A valid recipient Fiber object handle.
 *  @param hSyncedSection
 *   A valid Synchronized Section object handle.
 *  @param ulFlags
 *   Attributes controlling the synchronization method and potentially 
 *   the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the synchronization to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the target Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the synchronization process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the synchronization process is interrupted by #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the synchronization period expires without gaining a lock on 
 *     the Synchronized Section object.
 *   - #JK_RESULT_FIBER_UNSUPPORTED_FEATURE<br>
 *     when an unsupported feature has been requested.
 *   - #JK_RESULT_FIBER_SYNC_SECTION_TIGHT_LOCKED<br>
 *     when a Synchronized Section cannot be assigned because of a high 
 *     lock-count.
 *   - #JK_RESULT_FIBER_SYNC_ASSIGN_BAD_STATE<br>
 *     when the recipient Fiber is not in a state which allows Synchronized 
 *     Section assignment.
 *   - #JK_RESULT_FIBER_SYNC_ASSIGN_NOTIFY_FAILURE<br>
 *     when the recipient Fiber cannot be notified of the Synchronized Section 
 *     assignment.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context specified by <i>hFiber</i> to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" for a period of time, as 
 *  indicated via the <i>ulDuration</i> parameter, if a lock on the
 *  @ref Fiber_Synced_Object_Pool_JBI "Synchronized Section" object 
 *  specified by the <i>hSyncedSection</i> parameter cannot be obtained to 
 *  allow its assignment to the <i>hFiberRecipient</i> Fiber. The error code 
 *  #JK_RESULT_FIBER_SYNC_TIMEOUT is returned, indicating a synchronization 
 *  failure, if the Synchronized Section object is not unlocked before the 
 *  <i>ulDuration</i> parameter expires.
 *
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags, 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags,
 *  @ref JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY "JK_FIBER_SYNC_ASSIGN_METHOD_XXX" 
 *  flags and the 
 *  @ref JK_FIBER_SYNC_ASSIGN_COND_RUNNING "JK_FIBER_SYNC_ASSIGN_COND_XXX" flags.
 *  All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  synchronization process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber synchronization process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the 
 *  synchronization would occur, then the function will return 
 *  #JK_RESULT_FIBER_BUSY. If the Synchronized Section is not owned, the 
 *  object assignment procedure is engaged.
 * 
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 * 
 *  The following flags apply when a blocked synchronization is 
 *  performed by putting the Fiber to @ref 
 *  JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the #JK_FIBER_SLEEP_MODE_LIGHT 
 *  flag is specified (default), the target Fiber synchronization process 
 *  can be interrupted using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this synchronization 
 *  interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  In order to gain exclusive lock on a Synchronized Section object, no 
 *  other Fiber can be in the same section. In the basic use-model, if the lock 
 *  is open, the target Fiber will successfully gain immediate exclusive 
 *  control of the Synchronized Section object and immediately assign it to the 
 *  recipient Fiber. Once assigned, control of the Synchronized Section object 
 *  is not released until either the #AmFiberSectionExit(), #AmFiberStop() or 
 *  the #AmFiberPoolDestroy() functions are called on the recipient Fiber.
 *
 *  When synchronization succeeds, the target Fiber will be scheduled for 
 *  execution again after the lock on the Synchronized Section object is 
 *  established. At that time, the assignment of the Synchronized Section
 *  to the recipient Fiber can continue.
 * 
 *  Before the and the recipient Fiber will receive control of the 
 *  Synchronized Object, the recipient Fiber's condition is checked against the
 *  @ref JK_FIBER_SYNC_ASSIGN_COND_RUNNING "JK_FIBER_SYNC_ASSIGN_COND_XXX" flags. 
 *  The flags in a logical OR manner to determine what condition the recipient 
 *  Fiber can be in before assigning it the Synchronized Section. As an 
 *  example, assignment could be permitted to a recipient Fiber only if it is 
 *  either @ref JK_FIBER_STATE_RUNNING "running" or 
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping" but not blocked on a Synchronized 
 *  Object by ORing together the #JK_FIBER_SYNC_ASSIGN_COND_RUNNING and 
 *  #JK_FIBER_SYNC_ASSIGN_COND_SLEEPING flags. If the condition flags 
 *  do not permit assignment, the error #JK_RESULT_FIBER_SYNC_ASSIGN_BAD_STATE 
 *  is returned.
 * 
 *  After assignment of a Synchronized Section to the recipient Fiber has 
 *  occurred, a notification process may commence. A notification is issued to 
 *  the recipient Fiber indicating that it has been assigned and entered into a 
 *  Synchronized Section when the #JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY flag is 
 *  specified (default). This process is muted by specifying the 
 *  #JK_FIBER_SYNC_ASSIGN_METHOD_QUIET flag.
 * 
 *  It is important to note that assignment of a Synchronized Section to the 
 *  recipient Fiber does not require that the Synchronized Section be owned by 
 *  any Fiber prior to this function call. Attempting to assign a Synchronized 
 *  Section where <i>hFiber</i> equals <i>hFiberRecipient</i> will result in 
 *  the function returning #JK_RESULT_FIBER_BAD_PARAM.
 * 
 *  If the target Fiber attempting to assign the Synchronized Object to the 
 *  recipient Fiber currently owns the Synchronized Section, the assignment can 
 *  only occur if the lock-count on the Synchronized Section is one (1). If the 
 *  section has been @ref AmFiberSectionEnter "entered" more than once 
 *  recursively, the error #JK_RESULT_FIBER_SYNC_SECTION_TIGHT_LOCKED is 
 *  returned.
 *
 *  If the Synchronized Section is owned by a Fiber other than the 
 *  target Fiber, the lock on the Synchronized Section must be granted first to 
 *  the target Fiber before transfer of ownership to the recipient Fiber. The 
 *  condition of the recipient Fiber is evaluated only <b>after</b> the 
 *  target Fiber claims ownership (temporarily through this function or 
 *  otherwise) of the Synchronized Section.
 * 
 *  If the recipient Fiber already owns the Synchronized Section, the result 
 *  #JK_RESULT_FIBER_OK is returned without attempting synchronization, 
 *  there will be no attempt to @ref JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY "notify" 
 *  the recipient Fiber (if required via <i>ulFlags</i>) and the condition of 
 *  the recipient Fiber is not checked.
 * 
 *  If the recipient Fiber is blocked trying to access the same Synchronized 
 *  Section which is being assigned in <i>hSyncedSection</i>, the assignment 
 *  will only proceed when the #JK_FIBER_SYNC_ASSIGN_COND_BLOCKED flag is set. 
 *  In this condition, the recipient Fiber is not notified of the assignment and 
 *  the #JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY flag is ignored.
 * 
 *  Upon successful assignment of Synchronized Section ownership to the 
 *  recipient Fiber, the target Fiber should <b>not</b> call 
 *  #AmFiberSectionExit. The target Fiber will implicitly exit from the 
 *  Synchronized Section during the assignment process.
 * 
 *  Any Fiber owning the lock on the Synchronized Section object can repeatedly 
 *  enter the same section with this function. An equal number of calls to the 
 *  #AmFiberSectionExit() function are required to ensure proper release of the 
 *  Synchronized Section object.
 *
 *  The Synchronized Section object may also be unlocked and then re-locked 
 *  by another Fiber before the lock is granted to the blocking
 *  target Fiber. In such a case, the target Fiber will continue to wait 
 *  in slumber.
 * 
 *  When synchronization fails, whereby the Synchronized Section object 
 *  has <b>not</b> been locked by the target Fiber in time, the target 
 *  Fiber is instead simply awakened and scheduled for execution; either 
 *  naturally by the Fiber Scheduler or via the #AmFiberResume() 
 *  function.
 * 
 *  Regardless of the result of the synchronization process, there is the 
 *  potential for the target Fiber to be removed from the scheduling queue 
 *  if it is stopped via the #AmFiberStop() or #AmFiberPoolDestroy() 
 *  functions before the next context execution cycle.
 *
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Important:
 *  The current implementation does not support recipient Fiber
 *  @ref JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY "notification". As 
 *  a result, only the #JK_FIBER_SYNC_ASSIGN_METHOD_QUIET flag may be used. If  
 *  #JK_FIBER_SYNC_ASSIGN_METHOD_NOTIFY is used, the error
 *  #JK_RESULT_FIBER_UNSUPPORTED_FEATURE is returned.
 * 
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberSectionExit, AmFiberStop, AmFiberPoolDestroy, 
 *  AmFiberResume
 * 
 */

long AmFiberSectionAssign( JKFiberHandle hFiber, JKFiberHandle hFiberRecipient, JKFiberSyncedSectionHandle hSyncedSection, unsigned long ulFlags, unsigned long ulDuration );

/**
 *  Links a synchronized section to a synchronized event.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedSection
 *   A valid Synchronized Section object handle.
 *  @param hSyncedEvent
 *   A valid Synchronized Event object handle.
 *  @param ulFlags
 *   Attributes controlling the event synchronization method and 
 *   potentially the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the event synchronization to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the event synchronization process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the event synchronization process is interrupted by 
 *     #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the synchronization period expires without the Synchronized 
 *     Event being signaled.
 *   - #JK_RESULT_FIBER_SYNC_SECTION_TIGHT_LOCKED<br>
 *     when a Synchronized Section cannot be unlocked because of a high 
 *     lock-count.
 *
 *  <p>
 *  This function releases the lock on the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Section" object, specified 
 *  by the <i>hSyncedSection</i> parameter, which is held by the target 
 *  @ref Fiber_JBI "Fiber" specified by <i>hFiber</i>. The Synchronized 
 *  Section object lock should have been previously obtained through the 
 *  use of the #AmFiberSectionEnter() function. The error 
 *  #JK_RESULT_FIBER_BAD_PARAM is returned if the target Fiber does not 
 *  hold a lock on the Synchronized Section object. If the section has 
 *  been @ref AmFiberSectionEnter "entered" more than once recursively, the 
 *  error #JK_RESULT_FIBER_SYNC_SECTION_TIGHT_LOCKED is returned.
 * 
 *  Once the lock on the <i>hSyncedSection</i> object is released, this 
 *  function will yield the target Fiber execution context specified by 
 *  <i>hFiber</i> to the @ref Fiber_Scheduler_JBI "Fiber Scheduler" for a 
 *  period of time, as indicated via the <i>ulDuration</i> parameter, if 
 *  the @ref Fiber_Synced_Object_Pool_JBI "Synchronized Event" object 
 *  specified by the <i>hSyncedEvent</i> parameter is not @ref 
 *  AmFiberEventSignal "signaled". Upon synchronization failure, the error 
 *  code #JK_RESULT_FIBER_SYNC_TIMEOUT is returned indicating that the 
 *  Synchronized Event object was not signaled before the <i>ulDuration</i> 
 *  parameter expired.
 * 
 *  Regardless of whether or not the Synchronized Event object has been
 *  signaled in time (or if it was simply @ref 
 *  JK_FIBER_SYNC_METHOD_TEST_ONLY "tested"), the function will 
 *  attempt to re-gain control of the <i>hSyncedSection</i> object before 
 *  returning to the caller. During this synchronization, the target Fiber 
 *  execution context may be @ref JK_FIBER_STATE_SUSPENDED "suspended" 
 *  until the lock on the Synchronized Section is granted again. The Fiber 
 *  <b>cannot</b> be @ref AmFiberResume "resumed" during this period.
 * 
 *  The common use-model for this function assumes that another Fiber is 
 *  using the same <i>hSyncedSection</i> to protect data which requires 
 *  atomic access. In this model, the atomic data is modified by one Fiber 
 *  which sends the signal to other Fibers indicating the modification 
 *  is complete. This signal is sent via the #AmFiberEventSignal() 
 *  function while the lock on the common Synchronized Section is held. 
 *  After the lock on the Synchronized Section is released by the Fiber 
 *  which modified the atomic data, the other Fibers (which have been 
 *  signaled) will acquire the lock one at a time and examine the value of 
 *  the atomic data. Each Fiber will in turn be granted access to the 
 *  atomic data as the preceding Fiber releases its lock on the 
 *  <i>hSyncedSection</i>. This use model also assumes that a @ref 
 *  JK_FIBER_SE_TYPE_PULSE "pulse" type Synchronization Event is used, 
 *  although it is not mandatory.
 *
 *  An attempt to use this function in different Fibers each with 
 *  different <i>hSyncedSection</i> parameters and the same 
 *  <i>hSyncedEvent</i> parameter will result in the error 
 *  #JK_RESULT_FIBER_BAD_PARAM. This check only occurs when actually 
 *  attempting to synchronize on a Synchronized Event object.
 * 
 *  The following parameter descriptions only apply to the 
 *  process of Synchronized Event synchronization. There are currently no 
 *  options available to control the behaviour of the Synchronized Section 
 *  re-locking procedure.
 *
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags and 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags. All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  synchronization process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber synchronization process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the 
 *  synchronization would occur, then the function will return 
 *  #JK_RESULT_FIBER_BUSY.
 *
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 * 
 *  The following flags apply when a blocked synchronization is 
 *  performed by putting the Fiber to @ref 
 *  JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the #JK_FIBER_SLEEP_MODE_LIGHT 
 *  flag is specified (default), the target Fiber synchronization process 
 *  can be interrupted using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this synchronization 
 *  interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  Regardless of the result of the synchronization process, there 
 *  is the potential for the target Fiber to be removed from the 
 *  scheduling queue if it is stopped via the #AmFiberStop() or 
 *  #AmFiberPoolDestroy() functions before the next context execution 
 *  cycle.
 *
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberEventSignal, AmFiberResume, AmFiberStop, AmFiberPoolDestroy
 * 
 */

long AmFiberSectionSynchronize( JKFiberHandle hFiber, JKFiberSyncedSectionHandle hSyncedSection, JKFiberSyncedEventHandle hSyncedEvent, unsigned long ulFlags, unsigned long ulDuration );

/**
 *  Exits a synchronized section.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedSection
 *   A valid Synchronized Section object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *
 *  <p>
 *  This function releases the lock on the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Section" object, specified 
 *  by the <i>hSyncedSection</i> parameter, which is held by the target 
 *  @ref Fiber_JBI "Fiber" specified by <i>hFiber</i>. The Synchronized 
 *  Section object lock should have been previously obtained through the 
 *  use of the #AmFiberSectionEnter() function. The error 
 *  #JK_RESULT_FIBER_BAD_PARAM is returned if the target Fiber does not 
 *  hold a lock on the Synchronized Section object.
 *
 *  Fibers may <b>not</b> use this function to cause another Fiber to 
 *  release its lock on a Synchronized Section object. As an example, 
 *  Fiber "A" cannot force target Fiber "B" to release its lock on 
 *  Synchronized Section "C". Only when the object handle 
 *  specified in the target <i>hFiber</i> parameter matches 
 *  that of the calling Fiber, will the synchronization process be 
 *  finalized.
 * 
 *  When the target Fiber has released the lock on the Synchronized 
 *  Section object, including unwinding any recursive entries into the 
 *  section, it is automatically re-locked by another blocking Fiber, if 
 *  one exists.
 * 
 *  The target Fiber should take care to clear its lock on all owned 
 *  Synchronized Section objects before it exits or attempts to stop. If the 
 *  target Fiber is @ref #AmFiberStop() "stopped" all held Synchronized 
 *  Section objects will be released automatically and re-assigned 
 *  to other potentially blocking Fibers.
 * 
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberSectionEnter, AmFiberStop, AmFiberPoolDestroy, 
 *  AmFiberResume
 *
 */

long AmFiberSectionExit( JKFiberHandle hFiber, JKFiberSyncedSectionHandle hSyncedSection );

/**
 *  Puts a Fiber to sleep until a Synchronized Event object is signaled.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedEvent
 *   A valid Synchronized Event object handle.
 *  @param ulFlags
 *   Attributes controlling the synchronization method and potentially 
 *   the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the synchronization to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the synchronization process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the synchronization process is interrupted by #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the synchronization period expires without the Synchronized 
 *     Event being signaled.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context specified by <i>hFiber</i> to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" for a period of time, as 
 *  indicated via the <i>ulDuration</i> parameter, if the
 *  @ref Fiber_Synced_Object_Pool_JBI "Synchronized Event" object 
 *  specified by the <i>hSyncedEvent</i> parameter is not @ref 
 *  AmFiberEventSignal "signaled". Upon synchronization failure, the error
 *  code #JK_RESULT_FIBER_SYNC_TIMEOUT is returned indicating that the
 *  Synchronized Event object was not signaled before the <i>ulDuration</i> 
 *  parameter expired.
 *
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags and 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags. All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  synchronization process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber synchronization process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the 
 *  synchronization would occur, then the function will return 
 *  #JK_RESULT_FIBER_BUSY.
 *
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 *
 *  The following flags apply when a blocked synchronization is 
 *  performed by putting the Fiber to @ref 
 *  JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the #JK_FIBER_SLEEP_MODE_LIGHT 
 *  flag is specified (default), the target Fiber synchronization process 
 *  can be interrupted using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this synchronization 
 *  interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  Fibers may <b>not</b> use this function to cause another Fiber to 
 *  attempt to wait on a Synchronized Event object. As an example, Fiber "A" 
 *  cannot force target Fiber "B" to sleep while waiting for the 
 *  Synchronized Event "C" to be signaled. Only when the object handle 
 *  specified in the target <i>hFiber</i> parameter matches that of the 
 *  calling Fiber, will the synchronization process be initiated.
 * 
 *  The Synchronized Event object must be signaled in order to complete 
 *  a synchronization cycle. If the Synchronized Event object is already 
 *  signaled, the Fiber will continue execution without delay. If not, the 
 *  target Fiber will immediately switch execution context to the Fiber 
 *  Scheduler and go to @ref JK_FIBER_STATE_SLEEPING "sleep".
 * 
 *  Following this condition, when synchronization succeeds, the target 
 *  Fiber will be scheduled for execution again after the Synchronized 
 *  Event object is signaled. Additionally, any other Fiber also blocking 
 *  on the Synchronized Event object will also be scheduled for 
 *  execution.
 * 
 *  When synchronization fails, whereby the Synchronized Event object has 
 *  <b>not</b> been signaled in time, the target Fiber is instead simply 
 *  awakened and scheduled for execution; either naturally by the Fiber 
 *  Scheduler or via the #AmFiberResume() function.
 * 
 *  Regardless of the result of the synchronization process, there is the 
 *  potential for the target Fiber to be removed from the scheduling queue 
 *  if it is stopped via the #AmFiberStop() or #AmFiberPoolDestroy() 
 *  functions before the next context execution cycle.
 *
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberEventSignal, AmFiberStop, AmFiberPoolDestroy, 
 *  AmFiberResume
 * 
 */

long AmFiberEventWait( JKFiberHandle hFiber, JKFiberSyncedEventHandle hSyncedEvent, unsigned long ulFlags, unsigned long ulDuration );

/**
 * @name Fiber Signal Method
 * @{
 */

/**
 *  The signal notification for a Synchronized Object is broadcast 
 *  to all Fiber blocked on the Synchronized Object state.
 */
#define JK_FIBER_SIGNAL_METHOD_BROADCAST            (0x00000000)

/**
 *  The signal notification for a Synchronized Object is applied
 *  exclusively to a single Fiber blocked on the Synchronized Object 
 *  state.
 * 
 *  @par Note:
 *  This flag does not guarantee which blocked Fiber will be impacted
 *  by the event if multiple Fibers are blocked on the Synchronization 
 *  Object.
 */
#define JK_FIBER_SIGNAL_METHOD_EXCLUSIVE            (0x00000008)

/**
 *  The bit-field mask used to access the signal method settings.
 */
#define JK_FIBER_SIGNAL_METHOD_MASK                 (JK_FIBER_SIGNAL_METHOD_BROADCAST | JK_FIBER_SIGNAL_METHOD_EXCLUSIVE)

/**
 *  The bit-field position (zero-based offset) of the signal method 
 *  settings.
 */
#define JK_FIBER_SIGNAL_METHOD_POS                  (0x03)

/**
 * @}
 */

/**
 *  Signals a Synchronized Event object.
 * 
 *  @param hFiber
 *   The handle of the Fiber calling this function, or JK_NULL
 *   if this function is not called from a Fiber.
 *  @param hSyncedEvent
 *   A valid Synchronized Event object handle.
 *  @param ulFlags
 *   Attributes controlling the method in which the Synchronized Object is signaled.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *
 *  <p>
 *  This function signals the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Event" object 
 *  specified by the <i>hSyncedEvent</i> parameter. The Synchronized Event 
 *  object will remain signaled until a @ref Fiber_JBI "Fiber" attempts 
 *  to wait on it using the #AmFiberEventWait() function.
 *
 *  Valid values for <i>ulFlags</i> may be either of the 
 *  #JK_FIBER_SIGNAL_METHOD_BROADCAST (default) or 
 *  #JK_FIBER_SIGNAL_METHOD_EXCLUSIVE flags. All other values are ignored.
 * 
 *  When a @ref Fiber_Synced_Object_Pool_JBI "Synchronized Event" object 
 *  is signaled using a @ref #JK_FIBER_SIGNAL_METHOD_BROADCAST "broadcast" 
 *  flag, all the Fibers waiting on that object are awakened. In cases 
 *  where the object is signaled @ref 
 *  #JK_FIBER_SIGNAL_METHOD_EXCLUSIVE "exclusively", only one Fiber will 
 *  be awakened.
 * 
 *  In cases where this function is <b>not</b> called from a @ref 
 *  Fiber_JBI "Fiber", the value of <i>hFiber</i> may be set to JK_NULL.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberEventWait
 * 
 */

long AmFiberEventSignal( JKFiberHandle hFiber, JKFiberSyncedEventHandle hSyncedEvent, unsigned long ulFlags );

/**
 *  Resets the signal of a Synchronized Event object.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedEvent
 *   A valid Synchronized Event object handle.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *
 *  <p>
 *  This function resets the signal of a @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Event" object 
 *  specified by the <i>hSyncedEvent</i> parameter. The Synchronized Event 
 *  object will remain unsignaled until the function #AmFiberEventSignal() 
 *  is called with it as a parameter.
 * 
 *  Use of this function may not be required in all circumstances 
 *  depending on the attributes of the Synchronized Event object. See 
 *  the #AmFiberSyncedObjectCreate() function for details related to @ref 
 *  JK_FIBER_SE_RESET_AUTO "auto reset" of Synchronized Event objects.
 *
 *  Attempting to reset a @ref JK_FIBER_SE_TYPE_PULSE "pulse type" 
 *  Synchronized Event object will <b>not</b> result in error.
 *
 *  In cases where this function is <b>not</b> called from a @ref 
 *  Fiber_JBI "Fiber", the value of <i>hFiber</i> may be set to JK_NULL.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberEventSignal, AmFiberSyncedObjectCreate
 * 
 */

long AmFiberEventReset( JKFiberHandle hFiber, JKFiberSyncedEventHandle hSyncedEvent );

/**
 *  Puts a Fiber to sleep until a Synchronized Semaphore object is signaled.
 * 
 *  @param hFiber
 *   A valid Fiber object handle.
 *  @param hSyncedSemaphore
 *   A valid Synchronized Semaphore object handle.
 *  @param ulFlags
 *   Attributes controlling the synchronization method and potentially 
 *   the sleep cycle.
 *  @param ulDuration
 *   A period of time, expressed in milliseconds, to sleep while waiting 
 *   for the synchronization to complete.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber is not in a valid state.
 *   - #JK_RESULT_FIBER_BUSY<br>
 *     when the <i>ulFlags</i> parameter is set to @ref 
 *     JK_FIBER_SYNC_METHOD_TEST_ONLY "test" if the target Fiber would 
 *     block to complete the synchronization process.
 *   - #JK_RESULT_FIBER_SYNC_INTERRUPTED<br>
 *     when the synchronization process is interrupted by #AmFiberResume().
 *   - #JK_RESULT_FIBER_SYNC_TIMEOUT<br>
 *     when the synchronization period expires without the Synchronized 
 *     Semaphore being signaled.
 *
 *  <p>
 *  This function yields the target @ref Fiber_JBI "Fiber" execution 
 *  context specified by <i>hFiber</i> to the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" for a period of time, as 
 *  indicated via the <i>ulDuration</i> parameter, if the
 *  @ref Fiber_Synced_Object_Pool_JBI "Synchronized Semaphore" object 
 *  specified by the <i>hSyncedSemaphore</i> parameter is not @ref 
 *  AmFiberSemaphoreRelease "signaled". The Synchronized Semaphore object
 *  will remain signaled as long as its value is greater than zero (0). 
 * 
 *  The value of the Synchronized Semaphore is decremented by one upon
 *  successful return from this function. Upon synchronization failure, the 
 *  error code #JK_RESULT_FIBER_SYNC_TIMEOUT is returned indicating that the 
 *  Synchronized Semaphore object was not signaled before the <i>ulDuration</i>
 *  parameter expired.
 * 
 *  Valid values for <i>ulFlags</i> include either of the 
 *  @ref JK_FIBER_SYNC_METHOD_SLEEP "JK_FIBER_SYNC_METHOD_XXX" flags and 
 *  either of the @ref JK_FIBER_SLEEP_MODE_LIGHT "JK_FIBER_SLEEP_MODE_XXX"
 *  flags. All other values are ignored.
 * 
 *  If the #JK_FIBER_SYNC_METHOD_SLEEP flag is specified (default), the 
 *  target Fiber will go to sleep as part of the normal Fiber 
 *  synchronization process. If the #JK_FIBER_SYNC_METHOD_TEST_ONLY flag is 
 *  specified, the target Fiber will simply test the condition needed to 
 *  engage the Fiber synchronization process. In this case, the @ref 
 *  JK_FIBER_SLEEP_MODE_LIGHT "Fiber Sleep Mode" flags are ignored. If the 
 *  synchronization would occur, then the function will return 
 *  #JK_RESULT_FIBER_BUSY.
 *
 *  Valid values for the <i>ulDuration</i> parameter may be anything. A 
 *  synchronization duration of <code>0x00000000</code> may not seem very 
 *  practical but does support a few limited use cases. A synchronization 
 *  duration of <code>0xFFFFFFFF</code> is <b>not</b> the same as an 
 *  infinite wait because the Fiber will eventually wake up in about 50
 *  days. This value will be used only when the 
 *  #JK_FIBER_SYNC_METHOD_SLEEP flag has been set.
 *
 *  The following flags apply when a blocked synchronization is 
 *  performed by putting the Fiber to @ref 
 *  JK_FIBER_SYNC_METHOD_SLEEP "sleep". If the #JK_FIBER_SLEEP_MODE_LIGHT 
 *  flag is specified (default), the target Fiber synchronization process 
 *  can be interrupted using the #AmFiberResume() function. Use of the 
 *  #JK_FIBER_SLEEP_MODE_DEEP flag counters this synchronization 
 *  interruption feature and allows the Fiber to complete a natural 
 *  synchronization cycle (assuming it is not stopped beforehand).
 * 
 *  Fibers may <b>not</b> use this function to cause another Fiber to 
 *  attempt to wait on a Synchronized Semaphore object. As an example, Fiber "A" 
 *  cannot force target Fiber "B" to sleep while waiting for the 
 *  Synchronized Semaphore "C" to be signaled. Only when the object handle 
 *  specified in the target <i>hFiber</i> parameter matches that of the 
 *  calling Fiber, will the synchronization process be initiated.
 * 
 *  The Synchronized Semaphore object must be signaled in order to complete 
 *  a synchronization cycle. If the Synchronized Semaphore object is already 
 *  signaled, the Fiber will continue execution without delay. If not, the 
 *  target Fiber will immediately switch execution context to the Fiber 
 *  Scheduler and go to @ref JK_FIBER_STATE_SLEEPING "sleep".
 * 
 *  Following this condition, when synchronization succeeds, the target 
 *  Fiber will be scheduled for execution again after the Synchronized 
 *  Semaphore object is signaled. Additionally, any other Fiber also blocking 
 *  on the Synchronized Semaphore object will also be scheduled for 
 *  execution.
 * 
 *  When synchronization fails, whereby the Synchronized Semaphore object has 
 *  <b>not</b> been signaled in time, the target Fiber is instead simply 
 *  awakened and scheduled for execution; either naturally by the Fiber 
 *  Scheduler or via the #AmFiberResume() function.
 * 
 *  Regardless of the result of the synchronization process, there is the 
 *  potential for the target Fiber to be removed from the scheduling queue 
 *  if it is stopped via the #AmFiberStop() or #AmFiberPoolDestroy() 
 *  functions before the next context execution cycle.
 *
 *  The only valid state for the target Fiber is
 *  @ref JK_FIBER_STATE_RUNNING "running". This function will return an 
 *  error of #JK_RESULT_FIBER_BAD_STATE if the target Fiber does not match 
 *  this requirement.
 *
 *  @par Invocation:
 *  This function may be called <b>only</b> from the target Fiber. See the 
 *  Fiber Service @ref section_invocation_conditions "invocation rules" 
 *  for details.
 *
 *  @see
 *  AmFiberSemaphoreRelease, AmFiberStop, AmFiberPoolDestroy, 
 *  AmFiberResume
 * 
 */

long AmFiberSemaphoreWait( JKFiberHandle hFiber, JKFiberSyncedSemaphoreHandle hSyncedSemaphore, unsigned long ulFlags, unsigned long ulDuration );

/**
 *  Increments the value of a Synchronized Semaphore object.
 * 
 *  @param hFiber
 *   The handle of the Fiber calling this function, or JK_NULL
 *   if this function is not called from a Fiber.
 *  @param hSyncedSemaphore
 *   A valid Synchronized Semaphore object handle.
 *  @param pulCount
 *   Indicating the value by which the Synchronized Semaphore is incremented.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *
 *  <p>
 *  This function increases the count of the @ref 
 *  Fiber_Synced_Object_Pool_JBI "Synchronized Semaphore" object 
 *  specified by the <i>hSyncedSemaphore</i> parameter. The Synchronized 
 *  Semaphore object will remain signaled as long as its count remains 
 *  positive. If there are @ref Fiber_JBI "Fibers" 
 *  @ref AmFiberSemaphoreWait "waiting" on the Synchronized Semaphore to 
 *  become positive, this function will resume one or more of them
 *  depending on the value referenced by <i>pulCount</i>. The Synchronized 
 *  Semaphore value will be decremented by one for each Fiber activated 
 *  accordingly until the object is no longer signaled.
 *
 *  The value referenced by <i>pulCount</i> will increment the value of the 
 *  Synchronized Semaphore up to, but not beyond, the limit value set for the 
 *  object. If the value of the Synchronized Semaphore object would breach the
 *  maximum value, the function returns #JK_RESULT_FIBER_BAD_PARAM without any 
 *  changes being made to the object state.
 * 
 *  In cases where this function is <b>not</b> called from a @ref 
 *  Fiber_JBI "Fiber", the value of <i>hFiber</i> may be set to JK_NULL.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 *  @see
 *  AmFiberSemaphoreWait
 * 
 */

long AmFiberSemaphoreRelease( JKFiberHandle hFiber, JKFiberSyncedSemaphoreHandle hSyncedSemaphore, unsigned long *pulCount );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_FIBER_H */
