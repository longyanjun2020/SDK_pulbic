/*
 * Copyright 2006-2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesFiber.h
 * Fiber Types JBI
 */

#ifndef __JKTYPES_FIBER_H
#define __JKTYPES_FIBER_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup Fiber_Types_JBI Fiber Types JBI
 * @{
 * Type definitions and defines related to the JBlend Fiber Service.
 */

/**
 * @name Result Code
 * @{
 */

/**
 *  Success.
 */
#define JK_RESULT_FIBER_OK                           (0)

/**
 *  General error code.
 */
#define JK_RESULT_FIBER_ERROR                       (-1)

/**
 *  A bad parameter was specified.
 */
#define JK_RESULT_FIBER_BAD_PARAM                   (-2)

/**
 *  The function was called with the object in a bad state.
 */
#define JK_RESULT_FIBER_BAD_STATE                   (-3)

/**
 *  The function is busy and cannot complete the request.
 */
#define JK_RESULT_FIBER_BUSY                        (-4)

/**
 *  A low memory condition was detected.
 */
#define JK_RESULT_FIBER_NO_MEMORY                   (-5)


    /**
 *  The function could not complete due to a Fiber deep sleep condition.
 */
#define JK_RESULT_FIBER_SLEEP_DEEP                  (-7)

/**
 *  A Fiber's sleep cycle was interrupted by another Fiber or system event.
 */
#define JK_RESULT_FIBER_SLEEP_INTERRUPTED           (-8)

/**
 * @internal
 *                  (not documented)
 *  A Fiber synchronization on an object was abandoned.
 */
#define JK_RESULT_FIBER_SYNC_ABANDONED              (-9)

/**
 *  A Fiber synchronization on an object was interrupted by another Fiber or 
 *  system event.
 */
#define JK_RESULT_FIBER_SYNC_INTERRUPTED            (-10)

/**
 *  A Fiber synchronization error timed-out.
 */
#define JK_RESULT_FIBER_SYNC_TIMEOUT                (-11)

/**
 *  The search for an internal object failed.
 */
#define JK_RESULT_FIBER_ITEM_NOT_FOUND              (-12)

/**
 *  A synchronization object has already been signaled.
 */
#define JK_RESULT_FIBER_SYNC_ALREADY_SIGNALED       (-13)

/**
 *  A synchronized section registration attempt succeeded.
 */
#define JK_RESULT_FIBER_SYNC_SECTION_REGISTERED     (-14)

/**
 *  A stack overflow condition was detected.
 */
#define JK_RESULT_FIBER_STACK_OVERFLOW_DETECTED     (-15)

/**
 *  A requested feature is not enabled in the module.
 */
#define JK_RESULT_FIBER_UNSUPPORTED_FEATURE         (-16)

/**
 *  A recipient Fiber is not in a state which allows Synchronized Section 
 *  assignment.
 */
#define JK_RESULT_FIBER_SYNC_ASSIGN_BAD_STATE       (-17)

/**
 *  A Synchronized Section is recursively locked with a lock-count greater than 
 *  one (1).
 */
#define JK_RESULT_FIBER_SYNC_SECTION_TIGHT_LOCKED   (-18)

/**
 *  A recipient Fiber cannot be notified of the Synchronized Section 
 *  assignment.
 */
#define JK_RESULT_FIBER_SYNC_ASSIGN_NOTIFY_FAILURE  (-19)

/**
 *  An attempt to suspend the Fiber would push its suspend counter greater than
 *  #JK_FIBER_SUSPEND_COUNT_LIMIT.
 */
#define JK_RESULT_FIBER_SUSPEND_COUNT_OVERFLOW      (-20)

/**
 *  An attempt to setup a new Fiber context failed.
 */
#define JK_RESULT_FIBER_CONTEXT_SETUP_FAILURE       (-21)

/**
 *  An attempt to switch from one context to another failed.
 */
#define JK_RESULT_FIBER_CONTEXT_SWITCH_FAILURE      (-22)

/**
 * @}
 */

/**
 *  A handle to a @ref Fiber_JBI "Fiber" object.
 */
typedef JKHandle    JKFiberHandle;

/**
 *  A handle to a @ref Fiber_Pool_JBI "Fiber Pool" object.
 */
typedef JKHandle    JKFiberPoolHandle;

/**
 *  A handle to a @ref Fiber_Scheduler_JBI "Fiber Scheduler" object.
 */

typedef JKHandle    JKFiberSchedulerHandle;

/**
 *  A handle to a @ref Fiber_Synced_Object_JBI "Fiber Synced Object".
 */

typedef JKHandle    JKFiberSyncedObjectHandle;

/**
 *  A handle to a @ref Fiber_Synced_Object_Pool_JBI "Fiber Synced Object Pool" 
 *  object.
 */

typedef JKHandle    JKFiberSyncedObjectPoolHandle;

/**
 *  A handle to a @ref Fiber_Synced_Object_JBI "Fiber Synced Object" derived 
 *  Event object.
 */

typedef JKHandle    JKFiberSyncedEventHandle;

/**
 *  A handle to a @ref Fiber_Synced_Object_JBI "Fiber Synced Object" derived 
 *  Section object.
 */

typedef JKHandle    JKFiberSyncedSectionHandle;

/**
 *  A handle to a @ref Fiber_Synced_Object_JBI "Fiber Synced Object" derived 
 *  Semaphore object.
 */

typedef JKHandle    JKFiberSyncedSemaphoreHandle;

/**
 *  A 64-bit wide time sample in milliseconds.
 */
typedef struct _JKT_Time_ms {
    /**
     *  The top 32-bits of a time sample.
     */
    unsigned long   m_ulHigh;

    /**
     *  The bottom 32-bits of a time sample.
     */
	unsigned long   m_ulLow;
} JKT_Time_ms;

/**
 *  The time statistics for a Fiber or Fiber Scheduler object.
 */
typedef struct _JKT_Fiber_TimeStatistics {
    /**
     *  The total active time the Fiber (or Fiber Scheduler) has spent 
     *  running on the CPU.
     *
     *  @par Warning:
     *  It is possible for the value of this variable to roll-over when 
     *  the Fiber has occupied the CPU for a combined total time of 
     *  approximately 584,554,531 years (64-bits worth of milliseconds).
     * 
     */
    JKT_Time_ms     m_ullActiveTime;

    /**
     *  The average time the Fiber (or Fiber Scheduler) has spent running 
     *  on the CPU per allocated time-slice.
     */
    JKT_Time_ms     m_ullAverageTime;

    /**
     *  The most recent start time of the Fiber (or Fiber Scheduler) 
     *  running on the CPU. This is not the same as the first time the 
     *  Fiber (or Fiber Scheduler) was run on the CPU.
     */
    JKT_Time_ms     m_ullStartTime;

    /**
     *  The last time marker obtained for the Fiber running on the 
     *  CPU. This data is not maintained for the Fiber Scheduler.
     */
    JKT_Time_ms     m_ullLastTime;
} JKT_Fiber_TimeStatistics;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __JKTYPES_FIBER_H */
