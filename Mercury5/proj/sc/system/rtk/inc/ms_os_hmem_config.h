/** @file ms_os_hmem_config.h
 * @author Piazza.Lo
 * @date 05/18/2009
 *
 * Handle based OS memory interface.
 */

#ifndef __MS_OS_HMEM_CONFIG_H__
#define __MS_OS_HMEM_CONFIG_H__

//Un-implementate.
#define MS_HMEM_USE_RBTREE 0

#if defined(__SDK_SIMULATION__) || !defined(__KERNEL_DEBUG__)
#define MS_HMEM_DIAGNOSE 0
#else
#define MS_HMEM_DIAGNOSE 1
#endif

#define MS_HMEM_UNITTEST 0

#define MS_HMEM_RANDOM_TEST 0

#if defined(__SDK_SIMULATION__)
#define MS_HMEM_VMALLOC 0
#else
#define MS_HMEM_VMALLOC 1
#endif

#endif //__MS_OS_HMEM_CONFIG_H__


