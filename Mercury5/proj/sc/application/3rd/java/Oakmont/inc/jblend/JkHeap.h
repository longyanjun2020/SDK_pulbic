/*
 *  Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkHeap.h 
 *  Heap JSI
 */
/**
 * @addtogroup Heap_JSI
 * @{
 */

#ifndef ___JKHEAP_H
#define ___JKHEAP_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if 1

void* JkHeapAllocChunk(JKSint32 size);
void JkHeapFreeChunk(void* heapChunk);
void JkHeapFreeAllChunk(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ___JKHEAP_H */

/** @} end of group */
