/*
 * Copyright 2002-2005 Aplix Corporation. All rights reserved.
 */

#ifdef SUPPORT_AMS_EXTENSION_LIBRARY

#ifndef AJSC_FIBER_H
#define AJSC_FIBER_H

#include "JkTypes.h"
#include "JkTypesFiber.h"
#include "AMFiber.h"
#include "AMFiberPool.h"
#include "AMFiberScheduler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AjscFiberResource_Tag
{
    JKFiberHandle	           m_hAjscFiber;
    JKT_Fiber_Stack            m_TAjscFiberStack;
    JKBool                     isUsed;
} AjscFiberResource;

typedef JKHandle AjscFiberResourceHandle;

/*-----------------------------------------------------------------------------
 * Internal Function(s) Prototype
 *----------------------------------------------------------------------------*/

JKBool ajsc_fiber_init(void);

void ajsc_fiber_fini(void);

int ajsc_fiber_schedule_run(void);

AjscFiberResourceHandle ajsc_fiber_create(void);

int ajsc_fiber_start(AjscFiberResourceHandle ajscFiberResourceHandle,JK_FIBER_FUNCTION pfStart, void *pvStartData, JK_FIBER_FUNCTION pfStop, void *pvStopData );

int ajsc_fiber_yield(AjscFiberResourceHandle ajscFiberResourceHandle);

int ajsc_fiber_destroy(AjscFiberResourceHandle ajscFiberResourceHandle);




#ifdef __cplusplus
}
#endif

#endif /* AJSC_FIBER_H */

#else
#ifndef AJSC_FIBER_HEADER
#define AJSC_FIBER_HEADER

/**
 *  @file ajsc_fiber.h
 *  Fiber Service (Event-driven) ACI
 */

#ifdef __cplusplus
extern "C"{
#endif

#include "aj_type.h"

/** 
 *  @addtogroup Fiber_Service_ACI
 *  @{
 * 
 * AJSC is designed for use with both of multi-thread environment and single-threaded environment.
 * By default, Fiber Service is disabled.
 * To use Fiber Service operations, a library customization request needs to be submitted.
 *
 *
 * @par Include file 
 * \#include ajsc_fiber.h
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 * Initializes the AJSC cooperative multi-tasking environment for running the KVE thread function.
 * @retval 0 
 *         if the environment is initialized successfully.
 * @retval "A negative value"
 *         if an error occurred in initialization.
 *
 * The AJSC cooperative multi-tasking environment initialization should be done when the handset has been turned on. 
 * In other words, it should be called one and only once during handset lifecycle.
 */
AJ_RESULT ajsc_fiber_init(void);

/**
 * Activates the Fiber Scheduler and run active Fibers for designated time.
 * @param duration
 *        A pointer to the buffer holding the duration in milliseconds 
 *        within which the Fiber Scheduler should execute Fibers.
 * @return 
 *        The period of time in milliseconds until which this function should be called next.
 *
 * 
 * All the processing to be performed in the KVE thread in multi-threaded environment are performed in this function.
 * This function switches to the separate CPU context (hereafter denoted KVE context) created for the KVE thread precessing.
 * All the native system functions to be called from the KVE thread is called inside the KVE context.
 * Namely, most of KSI functions are called in the KVE context.
 *
 * Calling this function means allocating some CPU time for the KVE thread.
 * The native system must call this function repeatedly to make the thread to perform its processing.
 *
 * The KVE thread processing in this function interrupts itself voluntarily and then ajsc_fiber_run() returns.
 * The next time ajsc_fiber_run() is called, the KVE context processing resumes from the point of interruption.
 * Namely, returning of ajsc_fiber_run() does not mean completion of the thread function.
 * 
 * A return value of 0 means that the native system should call this function again as soon as possible. 
 * If all the processing in the KVE context are suspended, this function returns 65535 (0xffff).
 *
 * When an asynchronous function is called in the KVE context, 
 * the native system must perform the processing after this function returns, i.e., outside the function context.
 * When the asynchronous processing is completed, call the ACI function for notifying AJSC of processing result, then 
 * call this function. The result is processed inside the KVE context.
 *
 * When an event that should be passed to the KVE thread occurs, 
 * call the ACI function for passing the event then call this function 
 * even if the period this function previously returned has not yet expired.
 * This is necessary for improving response performance.
 * The events here include completion of an asynchronous KSI function processing
 * as well as input from the user, e.g., key event.
 * 
 */
AJ_RESULT ajsc_fiber_run(unsigned long *duration);

/**
 * Yields execution of the current context to release CPU cycles.
 * @retval 0 if the function succeeds.
 * @retval 1 if the function fails.
 * <p>
 * 
 * This function is for use in a function (e.g., a KSI function) called from the KVE context scheduled in ajsc_fiber_run().
 * When this function is called, ajsc_fiber_run() returns to the caller.
 * The next time ajsc_fiber_run() is called, the KVE context starts execution from the point ajsc_fiber_yield() returns.
 *
 * This mechanism makes it possible for a synchronous KSI function to perform its processing asynchronously.
 * That is, a KSI function by calling ajsc_fiber_yield() can yields its CPU cycles without completing its processing.
 * After ajsc_fiber_run() returns, the native system may complete the request processing.
 * Then when ajsc_fiber_run() is called next, the KSI function can return to its caller.
 * In this scenario, the KSI function still looks working as a synchronous function.
 *
 */
AJ_RESULT ajsc_fiber_yield(void);

/**
 * Puts the current context to sleep for a designated time.
 * @param timeout
 *        A period of time, expressed in milliseconds, to stay sleeping.
 * @retval 0 
 *         if the function succeeds.
 * @retval "A negative value" 
 *         if the function fails.
 * <p>
 * 
 * This function is for use in a function (e.g., a KSI function) called from the KVE context scheduled in ajsc_fiber_run().
 * When this function is called, the function context is not scheduled again until the designated timeout time expires.
 *
 * As a consequence of calling this function, ajsc_fiber_run() returns to the caller.
 * 
 */
AJ_RESULT ajsc_fiber_sleep(unsigned long timeout);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AJSC_FIBER_HEADER */
#endif /*SUPPORT_AMS_EXTENSION_LIBRARY*/
