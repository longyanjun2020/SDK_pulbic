/*
 * Copyright 2000-2005 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypes.h
 * Primitive Data Types
 */
/**
 * @defgroup Common_Types Primitive Data Types
 * Defines primitive data types used in JBlend.
 * @par Include file :
 * @#include "JkTypes.h"
 */
/**
 * @addtogroup Common_Types
 * @{
 */

#ifndef ___JKTYPES_H
#define ___JKTYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  Alias of int
 */
typedef int            JKSint;

/**
 *  Alias of unsigned int
 */
typedef unsigned int   JKUint;

/**
 *   32-bit signed integer
 */
typedef signed long         JKSint32;

/**
 *   32-bit unsigned integer
 */
typedef unsigned long       JKUint32;

/**
 *   16-bit signed integer
 */
typedef signed short        JKSint16;

/**
 *   16-bit unsigned integer
 */
typedef unsigned short      JKUint16;

/**
 *   8-bit signed integer
 */
typedef signed char         JKSint8;

/**
 *   8-bit unsigned integer
 */
typedef unsigned char       JKUint8;

/**
 *   Unicode character
 */
typedef JKUint16            JKWChar;

/**
 *   UTF-8 character
 */
typedef JKUint8             JKUTF8Char;

/**
 *   Boolean type
 */
typedef int                 JKBool;


/**
 *   JKBool False
 */
#define JK_FALSE            0

/**
 *   JKBool True
 */
#define JK_TRUE             1

/**
 *   Handle type
 */
typedef const void*         JKHandle;

/**
 *   Invalid handle
 */
#define JK_INVALID_HANDLE   ((JKHandle)0xFFFFFFFF)

/**
 *   NULL
 */
#ifndef __cplusplus
#define JK_NULL             ((void *)0)
#else
#define JK_NULL             0
#endif

/**
 *   Abort
 */
#define JK_ABORT 2


/**
 *   Double-precision floating-point number
 */
typedef double JKDouble;
/**
 *   Single-precision floating-point number
 */
typedef float  JKFloat;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___JKTYPES_H */

/**
 * @} end of group
 */
