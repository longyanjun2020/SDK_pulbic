/*
 *  Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkCpuCache.h 
 *  Cache Operation JSI
 */
/**
 * @addtogroup Cache_Operation_JSI
 * @{
 */

#ifndef ___JKCPUCACHE_H
#define ___JKCPUCACHE_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Initializes the CPU cache.
 *  
 *  This function is called once only, at JVM startup. If there is 
 *  initialization processing that must be performed for the sake of 
 *  operations on the CPU cache, implement the processing in this function. 
 *  If no initialization is necessary, create a empty function.
 */
void JkCpuCache_initialize(void);

/**
 *  Flushes the instruction cache.
 * 
 * @param start
 *    A pointer to the memory area to be flushed.
 * @param size
 *    The size (in bytes) of the memory area to be flushed.
 * 
 *  Flush the amount of CPU instruction cache indicated in the <i>size</i> parameter, starting from the 
 *  location indicated by the pointer designated in the <i>start</i> parameter.
 *  
 *  Complete the flush processing inside this function.
 */
void JkCpuCache_flushIcache(void *start, JKSint32 size);

#ifdef __cplusplus
}
#endif

#endif /* ___JKCPUCACHE_H */

/** @} end of group */
