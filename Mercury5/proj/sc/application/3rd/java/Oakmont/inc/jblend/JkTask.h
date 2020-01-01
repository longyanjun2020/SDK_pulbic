/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTask.h
 * Task Mutual Exclusion Functions
 */

#ifndef ___SYS_JK_TASK_H
#define ___SYS_JK_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * @addtogroup Module_Task_Mutual_Exclusion
 * @{
 */

/**
 * Gets a semaphore.
 *
 * This function is used by JBlend for mutual exclusion control.
 *
 * When this function is called, get a semaphore.
 * The type of semaphore used should be a binary semaphore, namely, one that only
 * the task that acquired it can execute. Accordingly, if a semaphore has already
 * been acquired when this function is called, lock the CPU context that called
 * this function inside the function. Then at the time #JkTaskReleaseSemaphore()
 * is called, release the locked CPU context and return to the caller of
 * JkTaskGetSemaphore().
 *
 * #JkTaskReleaseSemaphore() is called for as many times as this function was
 * called, requesting release of the semaphore.
 *
 * The semaphore used by this function must be created ahead of time, before the
 * Java execution environment is started.
 * In the initial state when a semaphore is created, no owner should exist.
 *
 * @see JkTaskReleaseSemaphore()
 */
void JkTaskGetSemaphore( void );

/**
 * Releases a semaphore.
 *
 * Release the semaphore acquired by #JkTaskGetSemaphore().
 * If #JkTaskGetSemaphore() is called a second time before this function is called,
 * lock the calling CPU context.
 *
 * @see JkTaskGetSemaphore()
 */
void JkTaskReleaseSemaphore( void );
/**
 * @} end of group
 */


#ifdef __cplusplus
}
#endif

#endif

