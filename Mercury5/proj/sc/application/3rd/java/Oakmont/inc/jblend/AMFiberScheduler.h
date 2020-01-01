/*
 * Copyright 2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMFiberScheduler.h
 * Fiber Scheduler JBI
 */

#ifndef __AM_FIBERSCHEDULER_H
#define __AM_FIBERSCHEDULER_H

#include "JkTypesFiber.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_Scheduler_JBI Fiber Scheduler JBI
 *
 * @{
 *  An interface for scheduling a Fiber.
 *
 *  The functions in this interface can be used to interact with 
 *  the Fiber Scheduler object and execute active Fibers within the 
 *  associated Fiber Pool.
 *
 *  The memory resources used in the Fiber Scheduler object are provided 
 *  through the #AmFiberPoolCreate() function.
 * 
 *  @par Note:
 *  All Fiber objects within the same Fiber Pool must execute within the 
 *  same thread or process context. As such, use of the Fiber Scheduler 
 *  object should also occur on the same thread or process which is 
 *  hosting the Fiber Pool.
 *
 *  @par Warning: 
 *  The Fiber Scheduler JBI functions are <b>not</b> thread-safe.
 */

/**
 *  Gets the handle for the currently executing Fiber.
 * 
 *  @param hFiberScheduler
 *   A valid Fiber Scheduler object handle.
 *  @param phFiber
 *   A pointer to a Fiber object handle buffer. 
 *  @param ulFlags
 *   Reserved for future use. Always specify <code>0x00000000</code> for 
 *   this parameter.
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber Scheduler is in a bad state.
 * 
 *  <p>
 *  The memory referenced by the <i>phFiber</i> pointer is updated with 
 *  the handle to the currently executing @ref Fiber_JBI "Fiber" on the  
 *  @ref Fiber_Scheduler_JBI "Fiber Scheduler" associated with the 
 *  <i>hFiberScheduler</i> parameter.
 * 
 *  The value of the memory referenced by the <i>phFiber</i> parameter 
 *  will be JK_NULL in cases where this function is called from outside 
 *  of the @ref Fiber_Pool_JBI "Fiber Pool's" execution context.
 * 
 *  Fibers may access their own handle via this function.
 * 
 *  @par Invocation:
 *  This function may be called from a Fiber, thread or process context.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSchedulerGetActiveFiber( JKFiberSchedulerHandle hFiberScheduler, JKFiberHandle *phFiber, unsigned long ulFlags );

/**
 *  Gets the time statistics for the Fiber Scheduler.
 * 
 *  @param hFiberScheduler
 *   A valid Fiber Scheduler object handle.
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
 *  information available for the @ref 
 *  Fiber_Scheduler_JBI "Fiber Scheduler" specified by 
 *  <i>hFiberScheduler</i>.
 * 
 *  Fibers may access the time statistics of the Fiber Scheduler.
 * 
 *  @par Invocation:
 *  This function may be called from a @ref Fiber_JBI "Fiber", thread or 
 *  process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSchedulerGetTimeStatistics( JKFiberSchedulerHandle hFiberScheduler, JKT_Fiber_TimeStatistics *psTimeStatistics );


/**
 * @name Fiber Scheduler Execution Cycle
 * @{
 */


/**
 *  The minimum number of milliseconds that the #AmFiberSchedulerRun()
 *  should execute within.
 */
#define JK_FIBERSCHEDULER_CYCLE_DURATION_MIN        (0x0000000A) /*     10 ms   */

/**
 *  The maximum number of milliseconds that the #AmFiberSchedulerRun()
 *  should execute within.
 */
#define JK_FIBERSCHEDULER_CYCLE_DURATION_MAX        (0xFFFFFFFF) /*   49.7 days */

/**
 *  The default number of milliseconds that the #AmFiberSchedulerRun()
 *  is recommended to execute within. <i>This is only a recommendation and 
 *  may be tuned to match system performance and CPU loading requirements.</i>
 */
#define JK_FIBERSCHEDULER_CYCLE_DURATION_DEFAULT    (0x0000003C) /*     60 ms   */

/**
 * @}
 */

/**
 *  Runs the Fiber Scheduler to allow execution of Fibers contexts on the 
 *  CPU.
 * 
 *  @param hFiberScheduler
 *   A valid Fiber Scheduler object handle.
 *  @param pulDuration
 *   A pointer to a buffer containing the duration within which the Fiber 
 *   Scheduler should execute Fibers in the attached Fiber Pool. An 
 *   output value of this function is to set the buffer referenced by this 
 *   parameter with a period of time until which this function should be 
 *   called next. 
 * 
 * @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 *   - #JK_RESULT_FIBER_BAD_STATE<br>
 *     when the Fiber Scheduler is in a bad state.
 *   - #JK_RESULT_FIBER_STACK_OVERFLOW_DETECTED<br>
 *     when a Fiber stack overflow condition is detected.
 * 
 *  <p>
 *  This function uses the @ref Fiber_Scheduler_JBI "Fiber Scheduler" 
 *  specified by the <i>hFiberScheduler</i> parameter to schedule and 
 *  execute @ref Fiber_JBI "Fiber" contexts within the scope of the 
 *  associated @ref Fiber_Pool_JBI "Fiber Pool".
 * 
 *  Valid values for the buffer referenced by the <i>pulDuration</i> 
 *  parameter are between #JK_FIBERSCHEDULER_CYCLE_DURATION_MIN and 
 *  #JK_FIBERSCHEDULER_CYCLE_DURATION_MAX inclusive. The value of the 
 *  buffer referenced by <i>pulDuration</i> should not be used if the 
 *  function returns an error.
 * 
 *  During execution of this function, Fibers will be scheduled according 
 *  to their priority and current state. Only active Fibers which are
 *  @ref JK_FIBER_STATE_STARTED "started",
 *  @ref JK_FIBER_STATE_RUNNING "running" or
 *  @ref JK_FIBER_STATE_STOPPED "stopped" may receive execution 
 *  time on the CPU. If there is no active Fiber (all are @ref 
 *  JK_FIBER_STATE_SUSPENDED "suspended", none are @ref 
 *  JK_FIBER_STATE_SLEEPING "sleeping" or none have been @ref 
 *  AmFiberStart "started"), the buffer referenced by <i>pulDuration</i> 
 *  will receive the value of #JK_FIBERSCHEDULER_CYCLE_DURATION_MAX.
 * 
 *  If there is at least one @ref JK_FIBER_STATE_SLEEPING "sleeping" 
 *  Fiber, then the period of time remaining before it can be awakened 
 *  will be returned in the buffer referenced by <i>pulDuration</i>.
 *  Specifically, the shortest remaining period of all the 
 *  @ref JK_FIBER_STATE_SLEEPING "sleeping" Fibers will be 
 *  returned. @ref JK_FIBER_STATE_SUSPENDED "Suspended" Fibers do not 
 *  influence this value.
 * 
 *  @par Optimization:
 *  There is no need to call this function more frequently than recommended 
 *  by the return value placed in the buffer referenced by 
 *  <i>pulDuration</i>. Doing so would unnecessarily spend CPU cycles and 
 *  consume power. Conversely, if there is a key-press or other
 *  system event which must be handled in a time-sensitive manner by a 
 *  @ref JK_FIBER_STATE_SUSPENDED "suspended" Fiber, make sure to issue a 
 *  call to this function once the event is processed for consumption by 
 *  the Fiber Pool and the Fiber @ref AmFiberResume "resumed".
 *  
 *  @par Note:
 *  As with any cooperatively scheduled system, it is almost certain that 
 *  there will be occasions where an overrun on the duration provided to 
 *  this function will occur. Do not use the call duration of this 
 *  function to build other time-sensive algorithmic dependencies. This is 
 *  a limitation inherent in cooperative multitasking. There is no 
 *  preemptive, platform independent, mechanism available in this API set 
 *  which enables time-sensitive function call durations. It is the 
 *  responsibility of the architect and developer using the Fiber Service 
 *  API to take care that Fibers will not keep the Fiber Scheduler or 
 *  other Fibers in the system from getting enough CPU time.
 *
 *  @par Invocation:
 *  This function may be called from a Fiber within a different (host) 
 *  Fiber Pool or directly from a thread or process. The function call 
 *  must originate on the thread or process which hosts the Fiber Pool.
 *  See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSchedulerRun( JKFiberSchedulerHandle hFiberScheduler, unsigned long *pulDuration );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_FIBERSCHEDULER_H */
