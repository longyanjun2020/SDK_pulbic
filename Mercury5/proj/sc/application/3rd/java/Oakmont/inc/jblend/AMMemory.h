/*
 * Copyright 2000-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMMemory.h
 *   Java Heap JBI
 */
/**
 * @addtogroup Java_Heap_JBI
 * @{
 */
#ifndef ___AM_MEMORY_H
#define ___AM_MEMORY_H

#include <JkTypes.h>
#include "JkTypesMemory.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *   Allocates memory space from the Java heap.
 *   @param size The size (in bytes) of the space to be allocated
 *   @return Not #JK_NULL: A pointer to the allocated memory location (succeeded) <br>
 *           #JK_NULL: Could not allocate space from the Java heap (failed) 
 *
 *   This function allocates memory space of the designated size from the Java heap. <br>
 *   Space allocated with this function has a fixed location in the Java heap and 
 *   can easily cause the Java heap to become fragmented.
 *   For long-term memory allocation, use #AmMemAlloc() instead of this function.
 * @see AmMemFreePointer()
 */
void* AmMemAllocPointer(JKSint32 size);

/**
 *   Frees memory space allocated by #AmMemAllocPointer().
 *   @param p A pointer to the memory area to be freed.
 *
 *   This function frees the memory space allocated in the Java heap by 
 *   #AmMemAllocPointer().
 * @see AmMemAllocPointer()
 */
void AmMemFreePointer(void *p);

/**
 *   Allocates memory space from the Java heap and returns its handle.
 *   @param size The size (in bytes) of the space to be allocated
 *   @return Not #JK_INVALID_HANDLE: A handle identifying the memory space (succeeded) <br>
 *           #JK_INVALID_HANDLE: Memory could not be allocated from the Java heap (failed)
 *
 *   This function allocates memory space of the designated size from the Java heap.
 *   Before memory allocated by this function can be accessed, the memory space must 
 *   be locked by calling #AmMemLock().
 * @see AmMemFree() @see AmMemLock() @see AmMemUnlock()
 */
JKMemHandle AmMemAlloc(JKSint32 size);

/**
 *   Frees the memory space allocated by #AmMemAlloc().
 *   @param handle The handle identifying the memory space to be freed.
 *
 *   This function frees memory space allocated from the Java heap by #AmMemAlloc(). <br>
 *   Before memory is freed by this function, it must be unlocked by calling 
 *   AmMemUnlock(). If it was locked more than once, AmMemUnlock() must be called 
 *   for as many times as AmMemLock() was called.
 * @see AmMemAlloc() @see AmMemLock() @see AmMemUnlock()
 */
void AmMemFree( JKMemHandle handle );

/**
 *   Locks memory space allocated by #AmMemAlloc() and obtains a pointer to the 
 *   allocated space.
 *   @param handle 
 *          The handle of the memory to be locked. Designate the value 
 *          returned by #AmMemAlloc().
 *   @return 
 *          Not #JK_NULL: A pointer to the locked memory space (succeeded) <br>
 *          #JK_NULL: Could not lock memory space (failed) 
 *   
 *   This function locks a memory space allocated by #AmMemAlloc() and obtains a
 *   pointer to the memory location.<br>
 *   When this function locks a space, the lock count managed by JBlend is 
 *   incremented by 1. The function can be called multiple times, so long as the 
 *   lock count does not exceed 14.
 * @see AmMemAlloc() @see AmMemUnlock()
 */
void* AmMemLock( JKMemHandle handle );

/**
 *   Unlocks the space locked by #AmMemLock().
 *   @param handle The handle of the memory to be locked.
 *
 *   This function unlocks a memory space locked by #AmMemLock().
 *   When the space is unlocked, the pointer returned by #AmMemLock() is no longer 
 *   valid.
 *
 *   Use this function paired with AmMemLock().<br>
 *   When this function is called, the lock count managed by JBlend is 
 *   decremented by 1.<br>
 *   This function cannot be called when the memory space is not locked.
 * @see AmMemAlloc() @see AmMemFree() @see AmMemLock()
 */
void AmMemUnlock( JKMemHandle handle );

#ifdef __cplusplus
}
#endif

#endif

/** @} end of group */
