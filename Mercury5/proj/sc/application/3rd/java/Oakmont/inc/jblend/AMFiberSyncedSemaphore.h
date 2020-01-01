/*
 * Copyright 2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMFiberSyncedSemaphore.h
 * Fiber Synced Semaphore JBI
 */

#ifndef __AM_FIBERSYNCEDSEMAPHORE_H
#define __AM_FIBERSYNCEDSEMAPHORE_H

#include "JkTypesFiber.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_Synced_Semaphore_JBI Fiber Synced Semaphore JBI
 *
 * @{
 *  Interface for operating a Synchronized Semaphore
 *
 *  The functions in this interface can be used to interact with 
 *  a Synchronized Semaphore within the associated Synchronized Object 
 *  Pool.
 *
 *  The memory resources used in the Fiber Synchronized Semaphore object 
 *  are provided through the @ref Fiber_Synced_Object_Pool_JBI functions. 
 *  Refer to the #AmFiberSyncedObjectPoolCreate() function for more 
 *  details.
 * 
 *  @par Warning: 
 *  The Fiber Synced Semaphore JBI is <b>not</b> thread-safe.
 */

/**
 *  Gets the Synchronized Semaphore value.
 * 
 *  @param hFiberSyncedSemaphore
 *   A valid Synchronized Semaphore handle.
 *  @param pulValue
 *   A pointer to a buffer to receive the value of the Synchronized Semaphore. 
 * 
 *  @return
 *   - #JK_RESULT_FIBER_OK<br>
 *     if the function succeeds.
 *   - #JK_RESULT_FIBER_BAD_PARAM<br>
 *     when an invalid parameter is supplied.
 * 
 *  <p>
 *  The memory referenced by the <i>pulValue</i> pointer is updated with 
 *  the value of the @ref Fiber_Synced_Semaphore_JBI "Synchronized Semaphore" 
 *  specified by <i>hFiberSyncedSemaphore</i>. 
 * 
 *  @par Invocation:
 *  This function may be called from a @ref Fiber_JBI "Fiber", thread or 
 *  process context. See the Fiber Service @ref 
 *  section_invocation_conditions "invocation rules" for details.
 *
 */

long AmFiberSyncedSemaphoreGetValue( JKFiberSyncedSemaphoreHandle hFiberSyncedSemaphore, unsigned long *pulValue );

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_FIBERSYNCEDSEMAPHORE_H */
