/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JKWirelessMessagingTypedef.h
 *  Primitive Data Types Header File
 */
/**
 * @addtogroup WMA_Base_Types
 *
 * @{
 */

#ifndef ___JKTYPES_H

#ifndef ___JKWIRELESSMESSAGING_TYPEDEF_H
#define ___JKWIRELESSMESSAGING_TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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
 *   Boolean type
 */
typedef int                 JKBool;

/**
 *   False
 */
#define JK_FALSE            0

/**
 *   True
 */
#define JK_TRUE             1

/**
 *   Handle type
 */
typedef const void*         JKHandle;

/**
 *   NULL
 */
#define JK_NULL             ((void *)0)

/**
 *   Invalid handle.
 */
#define JK_INVALID_HANDLE    ((JKHandle)0xFFFFFFFF)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___JKWIRELESSMESSAGING_TYPEDEF_H */

#endif /* !___JK_TYPES_H */


/** @} end of group */
