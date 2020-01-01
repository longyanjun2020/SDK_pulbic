#ifndef _zm_memory_h_
#define _zm_memory_h_

#include "zm_typedef.h"

/*
 * 获取应用平台自身使用空间
 */
zm_extern zm_void* zm_memory_pool_create(zm_int* pool_size);

/*
 * 释放应用平台自身使用空间
 */
zm_extern zm_void  zm_memory_pool_destroy(zm_void* ptr);

#endif//_zm_memory_h_
