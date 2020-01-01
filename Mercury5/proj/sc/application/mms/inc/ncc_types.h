/*
 * NCC types define header file
 */

#ifndef __NCC_TYPES_H__
#define __NCC_TYPES_H__

#include "vm_types.ht"
#include <crtl_core.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef LOCAL
#define LOCAL static
#endif

#ifndef NCC_LOCAL
#define NCC_LOCAL LOCAL
#endif

#ifndef NCC_INLINE
#define NCC_INLINE
#endif

#define NCC_DEBUG_ON

#ifdef NCC_DEBUG_ON
#include "ven_dbg.h"
#include "sys_vm_dbg.ho"

#define NCC_DBG_LEVEL (VEN_DBG_GROUP_0 | VEN_DBG_LEVEL_0)
#define NCC_KERNEL_DEBUG(_LEVEL_, _format_, ...) ven_dbg_trace(_LEVEL_, _format_, ##__VA_ARGS__)

#if defined(__cplusplus)
extern "C" {
#endif

    void NCCPort_os_traceStr(char *str, ...);

#if defined(__cplusplus)
}
#endif

#else
/* empty macro definition */
#define NCC_DBG_LEVEL
#define NCC_KERNEL_DEBUG(_LEVEL_, _format_, ...) 
#endif

#ifdef NCC_ASSERT_ON
#define NCC_KERNEL_ASSERT(_X_) assert(_X_)
#else
#define NCC_KERNEL_ASSERT(_X_)
#endif

#ifndef UNUSED
#if defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

#define NCC_MMS             1
#define NCC_BROWSER         2
#define NCC_JVM             3
#define NCC_EMAIL           4
#define NCC_QQ              5
#define NCC_STREAMING       6
#define NCC_APP_ACCOUNT     7

#ifndef MMS_DUAL_SIM_SUPPORT
#define MMS_DUAL_SIM_SUPPORT
#endif

#endif //__NCC_TYPES_H__
