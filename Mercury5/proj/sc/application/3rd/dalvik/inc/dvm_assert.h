#ifndef DVM_ASSERT_H
#define DVM_ASSERT_H

#include "java_def.h"

//#define NDEBUG

#undef assert

#ifdef NDEBUG           /* required by ANSI standard */
#define assert(__e) ((void)0)
#else
//# define assert(__e) ((__e) ? (void)0 : __newlib_assert_fail (__FILE__, __LINE__, __FUNCTION__, #__e))
# define assert(__e) ((__e) ? (void)0 : vm_dbgError(_JAVATASK, ("["__FILE__ ":%d] dalvik backtrace assertion"), __LINE__ ))
#endif

#endif
