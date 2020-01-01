/*
 *  Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkVmTimer.h
 *  Timer Event Notification
 */
/**
 * @addtogroup Module_Timer_Event
 * @{
 */

#ifndef ___JKVMTIMER_H
#define ___JKVMTIMER_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  The type of the event handler for notifying JBlend of timer events.
 * 
 *  The event handler is not a function to be implemented by the device manufacturer. 
 *  A function address of this event handler type is passed in a parameter to #JkSetVmTimerHandler().
 * @see JkSetVmTimerHandler()
 */
typedef void (*JK_TIMER_HANDLER)(void);

/**
 *  Sets an event handler for timer event notification.
 *
 * @param handler
 *  An event handler for timer event notification to JBlend.
 * @param recommended_interval
 *  The recommended interval (in ms) for timer event notification. 
 * @return
 *  Return the actual interval (in ms) by which the native system notifies JBlend of timer events. 
 *  
 *  In the native system, when a value other than #JK_NULL is passed in the handler parameter,
 *  store that value as the event handler function address, and  until this function is called 
 *  again, call the event handler from a native task at regular intervals to notify JBlend of
 *  timer events.
 *  The event handler simply makes event notification and immediately returns to its caller. 
 *  While the JVM is suspended, timer event notification may be either continued or suspended. 
 *  
 *  In the native system, clear the stored function address when #JK_NULL is passed 
 *  in the <i>handler</i> parameter.
 *  
 *  The interval for timer event notification may be different from that designated in the
 *  <i>recommended_interval</i> parameter, but should be as close to the designated interval as possible.
 *
 *  
 *  Calling of an event handler in hardware interrupt processing is permissible.
 * @see JK_TIMER_HANDLER
 */
JKSint JkSetVmTimerHandler(const JK_TIMER_HANDLER handler, JKSint recommended_interval);

#ifdef __cplusplus
}
#endif

#endif /* ___JKVMTIMER_H */

/**
 * @} end of group
 */
