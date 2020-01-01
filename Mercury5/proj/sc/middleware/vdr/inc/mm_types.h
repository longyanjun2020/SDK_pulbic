///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file MM_Types.h
/// @brief Gereral data type definition.
/// @author MStar Semiconductor Inc.
///
/// Define the general data types.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _MM_TYPES_H_
#define _MM_TYPES_H_


// for u8, u16 ... etc
#ifdef __RTK_OS__
#include "vm_types.ht"
#else
typedef unsigned int    Primitive;
//typedef unsigned char   bool;
typedef unsigned char   u8;
typedef signed   char   s8;
typedef          char   ascii;
typedef unsigned short  u16;
typedef          short  s16;
typedef unsigned int    u32;
typedef          int    s32;
typedef unsigned long long u64;
typedef 	 long long s64;
#endif

#ifndef __BOOL_defined
#define  __BOOL_defined
// definition for BOOL
typedef unsigned char       BOOL;
#endif

#ifndef true
// definition for true
#define true                (1)
// definition for false
#define false               (0)
#endif

#endif // #ifndef _MM_TYPES_H_

