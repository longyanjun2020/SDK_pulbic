 /*
 * Copyright 2005-2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_memory.h#1 $
 */

#ifndef __COMMON_MEMORYREDEF_H__
#define __COMMON_MEMORYREDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>

/**
 * prototype malloc function
 * \param  size  how many bytes need to malloc.
  * \return Return a pointer to the allocate memory if success;otherwise return NULL.
 */
void *  common_memoryMalloc(int32_t size);

/**
 * prototype free function
 * \param  ptr  address of buffer
 * \return
 */
void common_memoryFree(void * ptr);

/**
 * How many bytes used
 * \return memory size used
 */
int32_t common_memoryUsedMemSize(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_MALLOC_H__ */
