//
// #############################################################################
//
//                  <<< MSTAR SEMICONDUCTOR CONFIDENTIAL >>>
//
//    The information contained in this file is the property of MSTAR
//    SEMICONDUCTOR.  Except as specifically authorized in writing by
//    MSTAR SEMICONDUCTOR, the user of this file shall keep information
//    contained herein confidential and shall protect same in whole or in part
//    from disclosure and dissemination to third parties and use for internal
//    evaluation, operation or maintenance purposes within MSTAR SEMICONDUCTOR
//    only. Without prior written consent of MSTAR SEMICONDUCTOR, you may not
//    reproduce, represent, or download through any means, the information
//    contained herein in any way or in any form for a purpose other that the
//    use for internal evaluation, operation or maintenance within
//    MSTAR SEMICONDUCTOR.
//
//              (c) STEPMIND S.A.         2002-2006
//              (c) MSTAR SEMICONDUCTOR   2006-2009
//
//                          All Rights Reserved
//
// #############################################################################


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//  Module      :   Ccure substitute
//
//  File        :   CCSTUBS.H
//
//  Purpose     :   replaces a subset of Ccure's debug-pregnant APIs with their
//                  do-noting-special variants, plus provide some vanilla stuff
//                  like TRUE / FALSE, B0, B1 etc...
//
//  Usage       :   compile some Ccure-enabled source files in a 'naked'
//                  environment
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _AUDIOAEC_CCSTUBS_H_
#define _AUDIOAEC_CCSTUBS_H_

#include <stdlib.h>

//  ASM stubs first
#ifdef  __ASM
# define ROM_111             1
# define ROM_DECL(name)      name
# define ROM_111_FUNC(name)  name
#else //  !__ASM

//  dummy stubs for the lazy cases (e.g. ARM code inspection)
typedef unsigned       char       u8,  U8;
typedef unsigned short int       u16, U16;
typedef unsigned       int       u32, U32, uint, UINT;
typedef signed         char       s8,  S8;
typedef signed   short int       s16, S16;
typedef signed         int       s32, S32;

typedef U8      U1;   typedef  S8   S1;
typedef U8      U2;   typedef  S8   S2;
typedef U8      U3;   typedef  S8   S3;
typedef U8      U4;   typedef  S8   S4;
typedef U8      U5;   typedef  S8   S5;
typedef U8      U6;   typedef  S8   S6;
typedef U8      U7;   typedef  S8   S7;
typedef U16     U9;   typedef  S16  S9;
typedef U16     U10;  typedef  S16  S10;
typedef U16     U11;  typedef  S16  S11;
typedef U16     U12;  typedef  S16  S12;
typedef U16     U13;  typedef  S16  S13;
typedef U16     U14;  typedef  S16  S14;
typedef U16     U15;  typedef  S16  S15;
typedef U32     U17;  typedef  S32  S17;
typedef U32     U18;  typedef  S32  S18;
typedef U32     U19;  typedef  S32  S19;
typedef U32     U20;  typedef  S32  S20;
typedef U32     U21;  typedef  S32  S21;
typedef U32     U22;  typedef  S32  S22;
typedef U32     U23;  typedef  S32  S23;
typedef U32     U24;  typedef  S32  S24;
typedef U32     U25;  typedef  S32  S25;
typedef U32     U26;  typedef  S32  S26;
typedef U32     U27;  typedef  S32  S27;
typedef U32     U28;  typedef  S32  S28;
typedef U32     U29;  typedef  S32  S29;
typedef U32     U30;  typedef  S32  S30;
typedef U32     U31;  typedef  S32  S31;

typedef   int   BOOL;

#if defined(FALSE)
#undef  FALSE
#endif
#define FALSE   0

#if defined(TRUE)
#undef  TRUE
#endif
#define TRUE    1

#if defined(OFF)
#undef  OFF
#endif
#define OFF 0

#if defined(ON)
#undef  ON
#endif
#define ON  1

#ifndef NULL
# define NULL ((void*)0)
#endif

#define ALL_TO_1(_len_)            (((1u << ((_len_) - 1)) << 1) - 1)
#define COUNT(x)                   (sizeOf(x)/sizeOf(*(x)))
#define sizeOfMember(type,member)   sizeOf(((type *)0)->member)
#define MEMBER_COUNT(type, member)                                        \
              (sizeOfMember(type,member)/sizeOfMember(type,member[0]))
#define NIL(x)                      ((void)(x))
#define VACUUM(x)                   do { NIL(x); } while(FALSE)

#define dbgStronglyTyped(type)
#define dbgStrongObjectType(type)
#define dbgStackSign(type,ptr)      NIL(ptr)
#define dbgSign(type,ptr)           NIL(ptr)
#define dbgValidatePtr(ptr)         NIL(ptr)
#define _dbgValidatePtr(ptr,nm,fl)  NIL(ptr)
#define dbgValidatePtr_(ptr)        NIL(ptr)
#define dbgCheckPtr(type,ptr)       NIL(ptr)
#define dbgPtr(type,ptr)            (ptr)

#define dbgAssert(cond)             NIL(0)
#define dbgAssertPrint(cond,args)   NIL(0)
#define dbgCheckPoint(cond)         NIL(0)

#define dbgRegisterSourceFile()     NIL(0)
#define dbgRegisterType(foo)        NIL(0)

#define DBGT_ASSRT(text)

#define flEnter(id,hint)            NIL(0)
#define flLeave(id)                 NIL(0)

#define UNUSED_PARAMETER(x)         NIL(x)
#define DBG_RUN_TIME_TYPE

#define PUBLIC
#define INTERNAL
#define PRIVATE   static

#define START_PROTO
#define END_PROTO

#define BEGIN_CODE
#define END_CODE

#define _cp_fileLine_
#define _FL(fl)
#define FILE_LINE                   _FILE_LINE(__FILE_NUMBER__,__LINE__)
#define FILE_LINE_(n)               _FILE_LINE(__FILE_NUMBER__,__LINE__+(n))
#define _FILE_LINE(f,l)             ((U32)((((U32)(f))<<15)|((l)<<1)))

#define sizeOf(typeOrObject)        ((int)sizeof(typeOrObject))
#define offsetOf(type,member)       ((int)(&((type *)0)->member))

#define libPrintf                   printf
#define memcopy                     memcpy
#if defined(_WIN32)
void *memcpy(void *dest,const void *src,unsigned int count);
#endif /* _WIN32 */

#define GHS                         'G'
#define MSVISUAL                    'M'
#define ADS                         'A'
#define GNU                         'B'

#ifdef  _MSC_VER
# define  COMPILER                  MSVISUAL
# pragma  warning(disable : 4127 4706 4214 4201 4115 4514 4032 4244)
#endif

#ifdef __ghs__
# define  COMPILER                  GHS
# define  INLINE                    __inline
# define  clz32                     __CLZ32
  extern unsigned int __CLZ32(unsigned int Rm);
#endif

#if defined(__GNUC__) && defined(__mips__)
# define  COMPILER                  GNU
# define  INLINE                    __inline
//# define  clz32                   __CLZ32
#endif

#if defined(__GNUC__) && defined(__AEONR2__)
# define  COMPILER                  GNU
# define  INLINE                    __inline
//# define  clz32                     __CLZ32
#endif

#if defined(UPGRADE_CEVAX)
# define INLINE                     __inline__
#endif /* UPGRADE_CEVAX */

#if defined(UPGRADE_DSP_R2)
#define INLINE                      __inline
#endif /* UPGRADE_DSP_R2 */

typedef void AGENT_t;

//  say all of these are here (bogus, but this is what a stub is about)
#define __STANDARD_H__
#define __CCBASE_H__

#endif  //  __ASM

//  vanilla
#define B0                    0x00000001u
#define B1                    0x00000002u
#define B2                    0x00000004u
#define B3                    0x00000008u
#define B4                    0x00000010u
#define B5                    0x00000020u
#define B6                    0x00000040u
#define B7                    0x00000080u
#define B8                    0x00000100u
#define B9                    0x00000200u
#define B10                   0x00000400u
#define B11                   0x00000800u
#define B12                   0x00001000u
#define B13                   0x00002000u
#define B14                   0x00004000u
#define B15                   0x00008000u
#define B16                   0x00010000u
#define B17                   0x00020000u
#define B18                   0x00040000u
#define B19                   0x00080000u
#define B20                   0x00100000u
#define B21                   0x00200000u
#define B22                   0x00400000u
#define B23                   0x00800000u
#define B24                   0x01000000u
#define B25                   0x02000000u
#define B26                   0x04000000u
#define B27                   0x08000000u
#define B28                   0x10000000u
#define B29                   0x20000000u
#define B30                   0x40000000u
#define B31                   0x80000000u

#define PASS(id,hint)
//#define PASS(id,hint)       printf("%d %s \n",id, hint);

//  these are really crude...
#define fatalError                    (void)
#define memAlloc(owner,bytes)         malloc(bytes)
#define memReleaseRef(owner,ptr)      free(ptr)
#define intMin(i,j)                   ((i)<(j)?(i):(j))

#endif/*_AUDIOAEC_CCSTUBS_H_*/