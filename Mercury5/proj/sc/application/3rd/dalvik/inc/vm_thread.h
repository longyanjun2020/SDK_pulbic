/*
 * Copyright 2010 MStarSemi. All Rights Reserved.
 * $Id$
 */

#ifndef _VM_THREAD_H_
#define _VM_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * initialises a mutex.
 *
 * @return the mutex ID or -1 if fail to intialize a mutex.
 */
int vm_thread_mutex_init();

/**
 * Lock the mutex. If the mutex is already locked, the calling
 * thread blocks until the mutex becomes available
 *
 * @param the mutex ID.
 * @return 0 if successful.
 **/
int vm_thread_mutex_lock(int mutex);

/**
 * Unlock the mutex. 
 *
 * @param the mutex ID.
 * @return 0 if successful.
 **/
int vm_thread_mutex_unlock(int mutex);

/**
 * Destroys the mutex. 
 *
 * @param the mutex ID.
 * @return 0 if successful.
 **/
int vm_thread_mutex_destroy(int mutex);

/**
 * initialises a condition variable .
 *
 * @return the condition ID or -1 if fail to intialize a condition.
 */
int vm_thread_cond_init();

/**
 * Block on the given condition variable. it must be called with mutex locked
 * by the calling thread. 
 *
 * @param the condition ID.
 * @param the mutex ID.
 * @return 0 if successful.
 **/
int vm_thread_cond_wait(int cond, int mutex);

/**
 * Unblocks the thread that are blocked on the specified condition variable.
 *
 * @param the condition ID.
 * @return 0 if successful.
 **/
int vm_thread_cond_signal(int cond);

/**
 * Destroys the given condition variable. 
 *
 * @param the condition ID.
 * @return 0 if successful.
 **/
int vm_thread_cond_destroy(int cond);

#ifdef __cplusplus
}
#endif

#endif // _JNI_MMAPI_H_