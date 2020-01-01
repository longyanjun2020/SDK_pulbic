/*
    types.h:	VALUE TYPE

    Copyright(c) FAITH,INC. 2007    All Rights Reserved.

    $Revision: 1.4 $

*/
#ifndef SYSTEM_TYPES_H___
#define SYSTEM_TYPES_H___


#ifdef __cplusplus
#define BEGIN_C_DECLS	extern "C" {
#define END_C_DECLS		}
#else /* __cplusplus */
#define BEGIN_C_DECLS
#define END_C_DECLS
#endif /* __cplusplus */

#ifndef FSOFT_TYPE_DEFINITION__
#define FSOFT_TYPE_DEFINITION__

#ifndef NULL
#define NULL                 0
#endif

#if 0
#define TRUE   1
#define FALSE  0
#endif

typedef signed char          s_8;
typedef unsigned char        u_8;
typedef short                s_16;
typedef unsigned short       u_16;
typedef long                 s_32;
typedef unsigned long        u_32;
#if defined(_MSC_VER)&&(_MSC_VER == 1200)
typedef __int64              s_64;
#else
typedef long long            s_64;
#endif
typedef int                  int_t;
typedef unsigned int         uint_t;
typedef void*                fhandle_t;
typedef u_32                 fresult_t;
typedef u_32                 fsize_t;
typedef s_32                 fssize_t;
typedef s_32                 foff_t;
typedef u_32                 ftime_t;
typedef s_8                  fchar_t;

#define MAX_VALUE_FSIZE      ((fsize_t)0xFFFFFFFF)
#define MAX_VALUE_FSSIZE     ((fssize_t)0x7FFFFFFF)
#define MAX_VALUE_FOFF       ((foff_t)0x7FFFFFFF)
#define MAX_VALUE_FTIME      ((ftime_t)0xFFFFFFFF)

typedef union {
	u_32          val;
	void*         ptr;
	const void*   cptr;
} fparam_t;

#define FRESULT_IS_ERROR(param)        ((param) >> 31)
#define FRESULT_MAKE_ERROR(status)     ((fresult_t)((1<<31) | ((status)&0x7FFFFFFF)))
#define FRESULT_MAKE_SUCCESS(status)   ((fresult_t)((status)&0x7FFFFFFF))

#endif /* FSOFT_TYPE_DEFINITION__ */

#endif /* SYSTEM_TYPES_H___ */
