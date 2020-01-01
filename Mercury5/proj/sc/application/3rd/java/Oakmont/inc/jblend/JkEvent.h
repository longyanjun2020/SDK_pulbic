/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkEvent.h
 * Event Synchronization
 */
/**
 * @addtogroup Module_Event_Sync
 * @{
 */

#ifndef ___SYS_JK_EVENT_H
#define ___SYS_JK_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * Event waiting completed normally
 */
#define JK_EVENT_OK         0

/**
 * Event waiting timed out
 */
#define JK_EVENT_TIMEOUT    -1

/**
 * Waits for an event to occur.
 *
 * @param timeout Timeout interval (in milliseconds)
 * @return        If an event occurs during the wait time, return #JK_EVENT_OK.
 *                If the wait times out, return #JK_EVENT_TIMEOUT.
 *
 * If no event is being held at the time this function is called, release the CPU execute
 * privilege of the CPU context calling this function and enter waiting state in the
 * function until a new event occurs or the function times out.
 *
 * When a function is called for event notification by the native system to the JVM task,
 * #JkEventNotify() is called.  After #JkEventNotify() is called, grant the CPU execute
 * privilege to the CPU context in waiting state while JkEventWait() is executing, and
 * resume execution.
 * Return #JK_EVENT_OK as the JkEventWait() return value in this case.
 *
 * If the function times out with no event occurring during the waiting state, acquire the
 * CPU execute privilege and return #JK_EVENT_TIMEOUT.
 *
 * If #JkEventNotify() was called before this function and an event occurrence state is
 * being held, return #JK_EVENT_OK without entering waiting state.
 * Clear the event occurrence state at this time.
 *
 * The device manufacturer must implement JkEventWait() in accord with the 
 * timer resolution.
 * Moreover, the timeout duration when JkEventWait() times out must be no 
 * longer than the timeout duration passed in a parameter.
 * Exceeding the designated time will lower the precision of the <code>
 * java.lang.Thread.sleep</code> method.
 * Aplix recommends implementing as follows.
 * - Make the timeout resolution of JkEventWait() the same as the 
 *   JkTimeGetCurrentTick() resolution.
 * - Adjust the JkEventWait() timeout duration based on the equation below, 
 *   where <i>timeout</i> is the value designated in the <i>timeout</i>
 *   parameter of JkEventWait().
 * <pre>
 * Actual timeout duration 
 *       = <i>timeout</i> - (<i>timeout</i> % JkEventWait() timeout resolution) 
 * </pre>
 * If, for example, the time resolution returned by JkEventWait() is 40 ms,
 * <i>JkEventWait</i>(50) times out in 40 ms and <i>JkEventWait</i>(30) times out in 0 ms.
 * 
 *  @par For compliance with JTWI 1.0:
 *  The timeout interval as set in the timeout parameter must be detected with a 
 *  resolution of 40 ms or better.
 * 
 *
 * @see JkEventNotify()
 */

JKSint32 JkEventWait( JKUint32 timeout );

/**
 * Notifies of an event occurrence.
 *
 * If this function is called when the JVM task context is in waiting state inside the
 * #JkEventWait() function, grant the CPU execute privilege to the JVM task context and
 * return control to the caller of #JkEventWait().
 * Clear the event occurrence state in this case.
 *
 * If this function is called when the JVM task context is not in waiting state inside the
 * #JkEventWait() function, hold the event occurrence state. Then even if JkEventWait() is
 * called thereafter, return #JK_EVENT_OK without going to waiting state.
 *
 *
 * @see JkEventWait()
 */
void JkEventNotify( void );

/**
 * Clears the event occurrence state.
 *
 * When no event has occurred, so long as no new event is notified by #JkEventNotify(),
 * the next time #JkEventWait() is called go to event waiting state.
 * @see JkEventNotify() , JkEventWait()
 */
void JkEventClear( void );


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
