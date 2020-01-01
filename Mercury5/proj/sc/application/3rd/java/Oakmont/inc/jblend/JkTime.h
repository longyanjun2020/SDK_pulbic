/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTime.h
 * Time Information Acquisition
 */
/**
 * @addtogroup Module_Time
 * @{
 */

#ifndef ___SYS_JK_TIME_H
#define ___SYS_JK_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *   Gets the elapsed time.
 *
 *  @param high
 *      A pointer to the memory area for storing the higher 32 bits.
 *  @param low
 *      A pointer to the memory area for storing the lower 32 bits.
 *
 *  Store the elapsed time (monotonic increasing value) in millisecond
 *  as a 64-bit value to the arguments <i>high</i> and <i>low</i>.
 *  It is recommended that the elapsed time starts from 0.
 *  Because this function is called by an arbitrary timing after JVM starts, 
 *  it is necessary to begin the count before JVM starts.
 *  
 *  The JVM presupposes that the value obtained by this function increases
 *  monotonically.
 *  However, if this function is called until the next time the elapsed 
 *  time is actually updated, it is OK to pass the caller the same value 
 *  as the previous function call. For an example, if the time resolution 
 *  is 10 milliseconds, this function passes the caller a same value at 
 *  every calls in the period after the time is updated until 10 
 *  milliseconds elapses.
 *
 *  In case of JVM suspension, the elapsed time may stop increasing.
 *  However, when JVM restarts, the elapsed time needs to be updated as if
 *  it were continuously increased during the JVM suspension.
 *  Even if the system time has been changed in JVM suspension, 
 *  the JkTimeGetCurrentTick() return value must increase monotonically in 
 *  time order regardless of the changes.
 *
 *  The JVM controls the thread using the value returned by this function.
 *  Since the accuracy of the elapsed time influences the accuracy of
 *  JVM execution directly, this value should be acquired with the highest
 *  possible accuracy.
 *  It is recommended that the accuracy ranges within 10 milliseconds.
 *
 *  @par For compliance with JTWI 1.0:
 *  The elapsed time returned by this function must have a resolution of 40 ms or better. 
 */
void JkTimeGetCurrentTick( JKUint32 *high, JKUint32 *low );

/**
 *   Gets the current time.
 *
 *  @param high
 *      A pointer to the memory area for storing the higher 32 bits.
 *  @param low
 *      A pointer to the memory area for storing the lower 32 bits.
 *
 *  Store the current time (the elapsed time from 00:00:00.000,
 *  January 1, 1970 of Greenwich mean time (GMT)) in millisecond
 *  as a 64-bit value to the arguments <i>high</i> and <i>low</i>.
 *  It is not required to compensate for summer time (daylight saving time).
 *
 *  Put 0, when the current time of the system has not been set.
 *  In case the current time of the system is changed during JVM suspension,
 *  put the changed value after JVM is resumed.
 *
 *  Since the accuracy of the current time acquired by this function
 *  influences the accuracy of the value obtained by 
 *  <code>java.lang.System.currentTimeMills</code> method, this value should be 
 *  acquired with the highest possible accuracy.
 *  It is recommended that the resolution ranges within 100 milliseconds.
 *  <!-- 2.09.00ˆÈ~‚ÅˆÈ‰º‚Ì‚æ‚¤‚ÉC³‚·‚é—\’èB‚»‚Ìê‡A
 *  JkTimeGetCurrentTick()‚Ì“¯—l‚Ì•\Œ»‚àl—¶‚É“ü‚ê‚é‚±‚ÆB
 *  Time resolution should preferably be no greater than 100 milliseconds.
 *  It is recommended that time resolution be no greater than 100 
 *  milliseconds.
 *  -->
 */
void JkTimeGetCurrentTime( JKUint32 *high, JKUint32 *low );


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
