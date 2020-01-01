#ifndef COMMON_H
#define COMMON_H

//#include "mvc_types.h"
#include "swvenc_deftypes.h"
#define _AG_S32_

#if defined(WIN32)
#define _X86_  // disable this if you would like to simulate other platform
#endif

// select ISA mapping
#ifdef __ARMCC_VERSION
#include "arm9e_rvct.h" //"armdsp.h" // ARM9 with RealView
#endif

#if defined(WINCE) && defined(ARM9)
#include "arm9e_wm6.h" //"inline_fns.h"  // ARM9 with Windows Mobile Compiler
#endif

#ifdef _X86_
//#define _X86_OPT_
//#define _X86_OPT_2_ // specific for x86 opt, not sure if conformance can be passed
#include "x86_vc.h" // X86 with VC


#include "aeon_simd_gcc.h"
//#define _AG_V32_
//#define _AG_V64_
#endif

#ifdef _MIPS_
#include "mips32_gcc.h" //<mips/mips32.h>
#endif

#ifdef _AEON
#include "aeon_gcc.h"
#ifdef AEONDEV_V1
#define _AEON_V64_
#endif

#ifdef _AEON_V64_
#include "swvenc_aeon-simd.h"
#define _AG_V64_
#define USE_QMEM
#define HAS_QMEM
#endif
#endif

#ifdef _TM5250_
#if !defined(_AG_S32_)
#define _UAMEM_ACCESS_ //unaligned memory access
#endif
#define _TM3_ISA_
#endif

#ifdef _TM3270_
#define _TM4_ISA_
#endif

///////////////////////////////////////////////////////////

#define ASSERT_NOT_ON_DEFAULT   default: MY_ASSERT(0, 0);

#ifndef EMPTY_EMMS
#define EMPTY_EMMS
#endif

#ifndef ATTR_INSTMODE
#define ATTR_INSTMODE
#endif

#ifndef SHORT_BRANCH_NEVER
#define SHORT_BRANCH_NEVER
#endif

#ifdef __TCS__
#include "tm_tcs.h"
#define _AG_V32_
#else //!__TCS__

#include <assert.h> //assert()

//define for debug message
#ifdef _DEBUG
#include <stdio.h>
#define DBGMSG(x)    printf x
#else
#define DBGMSG(x)
#endif

#ifndef RESTRICT
#if defined(__GNUC__)
#define RESTRICT __restrict__
#else
#define RESTRICT
#endif
#endif

#ifndef ALIGN16
#if defined(__GNUC__)
#define ALIGN16 __attribute__((aligned(16)))
#define ALIGN8  __attribute__((aligned(8)))
#elif defined(_MSC_VER)
#define ALIGN16 __declspec(align(16))
#define ALIGN8  __declspec(align(8))
#endif
#endif

#ifndef SMLABB
#define SMLABB(x, y, a) (((x)*(y))+(a))
#endif

#ifndef ATTR_INST16
#define ATTR_INST16
#endif

#ifndef ATTR_NOINST16
#define ATTR_NOINST16
#endif

#ifndef ATTR_INST16_M2
#define ATTR_INST16_M2
#endif

#ifndef ATTR_INST16_M3
#define ATTR_INST16_M3
#endif

#ifndef LOAD32U
#define LOAD32U(dst, src, imm) do { \
    ((uint8 *) (dst))[0] = ((const uint8 *) (src))[(imm) + 0]; \
    ((uint8 *) (dst))[1] = ((const uint8 *) (src))[(imm) + 1]; \
    ((uint8 *) (dst))[2] = ((const uint8 *) (src))[(imm) + 2]; \
    ((uint8 *) (dst))[3] = ((const uint8 *) (src))[(imm) + 3]; \
} while (0)
#endif

#ifndef LOAD32A
#define LOAD32A(dst, src) *(uint32 *) (dst) = *(const uint32 *) (src)
#endif

///////////////////////////////////////////////////////////////////
#ifndef MAX
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#endif

// 2.   Compute Operations: arithmetic operations
#define IMAX(a,b)       ((( int32)(a)) > (( int32)(b)) ? (a) : (b))
#define IMIN(a,b)       ((( int32)(a)) < (( int32)(b)) ? (a) : (b))
#define UMAX(a,b)       (((uint32)(a)) > ((uint32)(b)) ? (a) : (b)) // need to check
#define UMIN(a,b)       (((uint32)(a)) < ((uint32)(b)) ? (a) : (b)) // need to check
#ifndef IABS
#define IABS(a)         ((a)>0 ? (a) : -(a))
#endif
#define INEG(a)         (-(a))
// logical operations
#define BITANDINV(a,b)  ((a) & (~(b)))  // need to check
//#define ROL(a,b)      // need to check
#define ROL(a,b)       ((((uint32)(a))<<(b)) | ((((uint32)(a))>>(32-b)) & ((1<<b)-1)) ) //erica
// sign extension operations
#define SEX8(a)  ((int32)(int8)(a))
#define SEX16(a) ((int32)(int16)(a))
#define ZEX8(a)  ((uint32)(uint8)(a))
#define ZEX16(a) ((uint32)(uint16)(a))
// 3.   Immediate Operations
// logical operations
//#define ASLI
#define ROLI(a,b)       ((((uint32)(a))<<(b)) | ((((uint32)(a))>>(32-b)) & ((1<<b)-1)) ) //erica
#define ASR(a,i)        (((int32)(a))>>(i))
//#define ASRI
#define LSRI(a,i)       (((uint32)(a))>>(i))    // compiler probably use this instruction automatically
//#define LSLI
// arithmetic operations
//#define IADDI
//#define ISUBI
// signed comparison operations
#define IGTRI(i, a)     ((a) > (i) ? 1 : 0)
//#define IGEQI
//#define IEQLI
//#define INEQI
//#define ILESI
//#define ILEQI
// unsigned comparison operations
//#define UGTRI
//#define UGEQI
//#define UEQLI
//#define UNEQI
//#define ULESI
//#define ULEQI
// 4.   Special Compute Operations
// clipped arithmetic operations
//#define DSPIADD
//#define DSPISUB
//#define DSPUADD
//#define DSPUSUB
//#define DSPIMUL
//#define DSPUMUL
//#define DSPIABS
// carry and borrow operations
#define CARRY(a, b) (((((uint64)((uint32)(a))) + ((uint64)((uint32)(b)))) & ((uint64)(0xffffffff00000000))) ? 1 : 0)
//#define BORROW
// special multiply operations
#define IMULM(a, b) ((int32)((((int64)(a)) * ((int64)(b))) >> 32))
#define IMUL (a, b) ((int32)(((int32)(a)) * ((int32)(b))))
//#define UMULM
// dual arithmetic operations
#if 1
#ifndef DSPIDUALABS
#define DSPIDUALABS(a)    ((IABS(((int32)(a))>>16)<<16) | IABS((int16)(a)))
#endif

#ifndef DSPIDUALADD
#define DSPIDUALADD(a, b) ((ICLIPI((((int32)(a))>>16)+(((int32)(b))>>16), 32767)<<16) | ((ICLIPI((int32)((short)((a)&0xffff))+(int32)((short)((b)&0xffff)), 32767)&0xffff)))
#endif

#ifndef DSPIDUALSUB
#define DSPIDUALSUB(a, b) ((ICLIPI((((int32)(a))>>16)-(((int32)(b))>>16), 32767)<<16) | ((ICLIPI((int32)((short)((a)&0xffff))-(int32)((short)((b)&0xffff)), 32767)&0xffff)))
#endif

#else // faster, need to test before enabling
#define DSPIDUALABS(a)    (IABS((int32)((a)&0xffff0000)) | IABS(SEX16(a)))
#define DSPIDUALADD(a, b) ((ICLIPI(((int32)((a)&0xffff0000))+((int32)((b)&0xffff0000)), 0x7fff0000)) | ((ICLIPI((int32)SEX16((a)&0xffff)+(int32)SEX16((b)&0xffff), 0x7fff)&0xffff)))
#define DSPIDUALSUB(a, b) ((ICLIPI(((int32)((a)&0xffff0000))-((int32)((b)&0xffff0000)), 0x7fff0000)) | ((ICLIPI((int32)SEX16((a)&0xffff)-(int32)SEX16((b)&0xffff), 0x7fff)&0xffff)))
#endif

#ifndef DSPIDUALMUL
#define DSPIDUALMUL(a, b) ((ICLIPI((((int32)(a))>>16)*(((int32)(b))>>16), 32767)<<16) | ((ICLIPI((int32)((short)((a)&0xffff))*(int32)((short)((b)&0xffff)), 32767)&0xffff)))
#endif

// dual shifting operations
#ifndef DUALASR
#define DUALASR(a,i)    ((((int32)(a)>>(i))&0xffff0000) | (((int32)((short)((a)&0xffff))>>(i))&0xffff))
#endif
// dual clipping operations
#ifndef DUALICLIPI
#define DUALICLIPI(x,c) ((MIN(MAX(((int32)(short)((x)>>16)), -(c)-1), c)<<16) | (MIN(MAX((int32)((short)((x)&0xffff)), -(c)-1), c)&0xffff))
#endif
// old
//#define DUALUCLIPI(x,c) ((MIN(MAX(/*(int32)*/((x)>>16), 0), c)<<16) | (MIN(MAX((int32)((short)((x)&0xffff)), 0), c)&0xffff))
// new
#ifndef DUALUCLIPI
#define DUALUCLIPI(x,c) (((uint32)MIN((uint16)MAX(((short)(((int32)(x))>>16)), 0), (uint16)c)<<16) | (MIN((uint16)MAX(((short)((x)&0xffff)), 0), (uint16)c)&0xffff))
#endif
#ifndef PACKBYTES
// byte packing operations
#define PACKBYTES(a, b) ((((a)&0x000000ff)<<8) | ((b)&0x000000ff))
#endif

#ifndef MERGEMSB
#define MERGEMSB(a,b) ((((uint32)(a))&0xFF000000L) | ((((uint32)(a))&0x00FF0000L) >> 8) | ((((uint32)(b))&0xFF000000L) >> 8) | ((((uint32)(b))&0x00FF0000L) >> 16))
#endif

#ifndef MERGELSB
#define MERGELSB(a,b)   ( (((a)&0x0000ff00)<<16) | (((a)&0x000000ff)<<8) | (((b)&0x0000ff00)<<8) | ((b)&0x000000ff) )
#endif

#ifndef PACK16MSB
#define PACK16MSB(a, b) (((a)&0xffff0000) | (((uint32)(b))>>16))
#endif

#ifndef PACK16LSB
#define PACK16LSB(a, b) (((a)<<16) | ((b)&0xffff))
#endif

#ifndef MERGEDUAL16LSB
#define MERGEDUAL16LSB(a,b) ( (((a)&0x00ff0000)<<8) | (((a)&0x000000ff)<<16) | (((b)&0x00ff0000)>>8) | ((b)&0x000000ff) )
#endif
// byte select operations
#ifndef UBYTESEL
#define UBYTESEL(a, i)  ((uint32)(((a)>>(((i)&3)<<3))&0xff))  // unsign extended
#endif

#ifndef UBYTESEL_0
#define UBYTESEL_0(a) UBYTESEL(a, 0)
#endif

#ifndef UBYTESEL_1
#define UBYTESEL_1(a) UBYTESEL(a, 1)
#endif

#ifndef UBYTESEL_2
#define UBYTESEL_2(a) UBYTESEL(a, 2)
#endif

#ifndef UBYTESEL_3
#define UBYTESEL_3(a) UBYTESEL(a, 3)
#endif

#ifndef IBYTESEL
#define IBYTESEL(a, i)  SEX8(((a)>>(((i)&3)<<3)))  // sign extended
#endif

#ifndef UBYTESEL_VAR
#define UBYTESEL_VAR UBYTESEL  // unsign extended
#endif

#ifndef IBYTESEL_VAR
#define IBYTESEL_VAR IBYTESEL  // sign extended
#endif

// sum of products operations
#define UFIR8UU(a, b) \
    (((uint32)(((uint32)((a)&0xff000000))>>24)*(uint32)(((uint32)((b)&0xff000000))>>24)) + \
     ((uint32)(((uint32)((a)&0x00ff0000))>>16)*(uint32)(((uint32)((b)&0x00ff0000))>>16)) + \
     ((uint32)(((uint32)((a)&0x0000ff00))>>8) *(uint32)(((uint32)((b)&0x0000ff00))>>8)) + \
     ((uint32)( (uint32)((a)&0x000000ff)    ) *(uint32)( (uint32)((b)&0x000000ff)    )))

//bug: assume that 0<b<128; o/w it should be interpreted as a negative value
#define /*int32*/ IFIR8UI(/*uint32*/ a, /*int32*/ b) \
    (((int32)(((uint32)((a)&0xff000000))>>24)*(char)(((int32)((b)&0xff000000))>>24)) + \
     ((int32)(((uint32)((a)&0x00ff0000))>>16)*(char)(((int32)((b)&0x00ff0000))>>16)) + \
     ((int32)(((uint32)((a)&0x0000ff00))>>8) *(char)(((int32)((b)&0x0000ff00))>>8)) + \
     ((int32)( (uint32)((a)&0x000000ff)    ) *(char)( (int32)((b)&0x000000ff)    )))
//#define IFIR8II

#ifndef IFIR16
#define IFIR16(a, b)    (int32) ((((int32)a)>>16)*(((int32)b)>>16) + (int32)(((short)a)*((short)b)))
#endif

//#define UFIR16
// sum of differences operations
//#define UME8II
//#define UME8UU
// special byte shift operations
#ifndef FUNSHIFT1
#define FUNSHIFT1(a,b)  (((a)<<8)  | (((uint32)(b))>>24))
#endif

#ifndef FUNSHIFT2
#define FUNSHIFT2(a,b)  (((a)<<16) | (((uint32)(b))>>16))
#endif

#ifndef FUNSHIFT3
#define FUNSHIFT3(a,b)  (((a)<<24) | (((uint32)(b))>>8 ))
#endif
// clip operations
#ifndef ICLIPI
#define ICLIPI(x, c)    MIN(MAX((int)(x), -(c)-1), (c))
#endif
#ifndef UCLIPI
#define UCLIPI(x, c)    MIN(MAX((int)(x), 0), (c))
#endif
//#define UCLIPU
// quad arithmetic operations
#define QUADUMULMSB(a,b) \
((uint32)((uint16)((uint16)(((a)&0xFF000000)>>24)) * ((uint16)(((b)&0xFF000000)>>24)) & 0xFF00) << 16) | \
((uint32)((uint16)((uint16)(((a)&0x00FF0000)>>16)) * ((uint16)(((b)&0x00FF0000)>>16)) & 0xFF00) << 8 ) | \
((uint32)((uint16)((uint16)(((a)&0x0000FF00)>>8 )) * ((uint16)(((b)&0x0000FF00)>>8 )) & 0xFF00)      ) | \
((uint32)((uint16)((uint16)(((a)&0x000000FF)    )) * ((uint16)(((b)&0x000000FF)    )) & 0xFF00) >> 8 )

#ifndef QUADAVG
#define QUADAVG(a,b)  (((a) | (b)) - ((((a) ^ (b)) & 0xFEFEFEFE) >> 1))
#endif

#ifndef QUADAVG0
#define QUADAVG0(a,b) (((a) & (b)) + ((((a) ^ (b)) & 0xFEFEFEFE) >> 1))
#endif

#define DSPUQUADADDUI(r1, r2)   \
((UCLIPI( ((int32)( (r1)     &0x000000ff)) +((int32)(int8)( (r2)     &0x000000ff)), 255)    ) | \
 (UCLIPI( ((int32)(((r1)>> 8)&0x000000ff)) +((int32)(int8)(((r2)>> 8)&0x000000ff)), 255)<< 8) | \
 (UCLIPI( ((int32)(((r1)>>16)&0x000000ff)) +((int32)(int8)(((r2)>>16)&0x000000ff)), 255)<<16) | \
 (UCLIPI( ((int32)(((r1)>>24)&0x000000ff)) +((int32)(int8)(((r2)>>24)&0x000000ff)), 255)<<24) )

//#define DSPUQUADADDUI(a,b) ((UCLIPI((((uint32)(a)&0xff000000)>>24)+(((uint32)(b)&0xff000000)>>24),255)<<24) | (UCLIPI((((uint32)(a)&0x00ff0000)+((char)((uint32)(b)&0x00ff0000))>>16),255)<<16) | (UCLIPI((((uint32)(a)&0x0000ff00)+((uint32)(b)&0x0000ff00))>>8,255)<<8) | UCLIPI(((uint32)(a)&0x000000ff)+((uint32)(b)&0x000000ff),255))

#ifndef QUADUMAX
#define QUADUMAX(a, b)  ((((uint32)(a)&0xff000000)>((uint32)(b)&0xff000000) ? ((uint32)(a)&0xff000000) : ((uint32)(b)&0xff000000)) | (((uint32)(a)&0x00ff0000)>((uint32)(b)&0x00ff0000) ? ((uint32)(a)&0x00ff0000) : ((uint32)(b)&0x00ff0000)) | (((uint32)(a)&0x0000ff00)>((uint32)(b)&0x0000ff00) ? ((uint32)(a)&0x0000ff00) : ((uint32)(b)&0x0000ff00)) | (((uint32)(a)&0x000000ff)>((uint32)(b)&0x000000ff) ? ((uint32)(a)&0x000000ff) : ((uint32)(b)&0x000000ff)))
#endif

#ifndef QUADUMIN
#define QUADUMIN(a, b)  ((((uint32)(a)&0xff000000)<((uint32)(b)&0xff000000) ? ((uint32)(a)&0xff000000) : ((uint32)(b)&0xff000000)) | (((uint32)(a)&0x00ff0000)<((uint32)(b)&0x00ff0000) ? ((uint32)(a)&0x00ff0000) : ((uint32)(b)&0x00ff0000)) | (((uint32)(a)&0x0000ff00)<((uint32)(b)&0x0000ff00) ? ((uint32)(a)&0x0000ff00) : ((uint32)(b)&0x0000ff00)) | (((uint32)(a)&0x000000ff)<((uint32)(b)&0x000000ff) ? ((uint32)(a)&0x000000ff) : ((uint32)(b)&0x000000ff)))
#endif

// various special compute operations
#define IZERO(t, v)     ((t)==0 ? 0 : (v))
#define INONZERO(t, v)  ((t)!=0 ? 0 : (v))
#define IAVGONEP(a, b)  ((int32)((((int64)(a))+((int64)(b))+1)>>1))
#define IFLIP(t, a)     ((t)==0 ? (a) : -(a))

// 9. Special Compiler Custom_ops
// data-cache copyback and invalidate commands
//#define COPYBACK
//#define INVALIDATE
//#define PREFETCH
//#define ALLOCATE
// mux between two values
#define MUX(c, a, b)    ((c) ? (a) : (b))
//#define FMUX(a,b,c)
#ifndef PREFD
#define PREFD(op, loc) ((void) 0)
#endif


#ifndef DUALASL
#define DUALASL(a,i)    (((int32)((a)&0xffff0000)<<(i)) | (((short)((a)&0xffff)<<(i))&0xffff))
#endif

//notice
#define QUADICLIPI(r1, r2) \
(((ICLIPI((int32)(int8)( (r1)     &0x000000ff),(int8)( (r2)     &0x000000ff))&0xff)    ) | \
 ((ICLIPI((int32)(int8)(((r1)>> 8)&0x000000ff),(int8)(((r2)>> 8)&0x000000ff))&0xff)<< 8) | \
 ((ICLIPI((int32)(int8)(((r1)>>16)&0x000000ff),(int8)(((r2)>>16)&0x000000ff))&0xff)<<16) | \
 ((ICLIPI((int32)(int8)(((r1)>>24)&0x000000ff),(int8)(((r2)>>24)&0x000000ff))&0xff)<<24) )

#define QUADUCLIPI(r1, r2) \
((UCLIPI((int32)(int8)( (r1)     &0x000000ff),(int8)( (r2)     &0x000000ff))    ) | \
 (UCLIPI((int32)(int8)(((r1)>> 8)&0x000000ff),(int8)(((r2)>> 8)&0x000000ff))<< 8) | \
 (UCLIPI((int32)(int8)(((r1)>>16)&0x000000ff),(int8)(((r2)>>16)&0x000000ff))<<16) | \
 (UCLIPI((int32)(int8)(((r1)>>24)&0x000000ff),(int8)(((r2)>>24)&0x000000ff))<<24) )

#define QUADUMAXBYTE(r1) \
(((((r1&0x000000ff)>((r1&0x0000ff00)>>8))?(r1&0x000000ff):((r1&0x0000ff00)>>8))> \
((((r1&0x00ff0000)>>16)>((r1>>24)&0x000000ff))?((r1&0x00ff0000)>>16):((r1>>24)&0x000000ff)))? \
(((r1&0x000000ff)>((r1&0x0000ff00)>>8))?(r1&0x000000ff):((r1&0x0000ff00)>>8)): \
((((r1&0x00ff0000)>>16)>((r1>>24)&0x000000ff))?((r1&0x00ff0000)>>16):((r1>>24)&0x000000ff)))& \
0x000000ff

#define QUADUMINBYTE(r1) \
(((((r1&0x000000ff)<((r1&0x0000ff00)>>8))?(r1&0x000000ff):((r1&0x0000ff00)>>8))< \
((((r1&0x00ff0000)>>16)<((r1>>24)&0x000000ff))?((r1&0x00ff0000)>>16):((r1>>24)&0x000000ff)))? \
(((r1&0x000000ff)<((r1&0x0000ff00)>>8))?(r1&0x000000ff):((r1&0x0000ff00)>>8)): \
((((r1&0x00ff0000)>>16)<((r1>>24)&0x000000ff))?((r1&0x00ff0000)>>16):((r1>>24)&0x000000ff)))& \
0x000000ff

#define QUADULEQ(a, b) ((((uint8)(a))<=((uint8)(b))) | ((((uint8)((a)>>8))<=((uint8)((b)>>8)))<<8) | \
((((uint8)((a)>>16))<=((uint8)((b)>>16)))<<16) | ((((uint8)((a)>>24))<=((uint8)((b)>>24)))<<24))

#ifndef DSPIQUADADD
#define DSPIQUADADD(r1, r2)   \
(((ICLIPI( ((int32)(int8)( (r1)     &0x000000ff)) +((int32)(int8)( (r2)     &0x000000ff)) ,127)&0x000000ff )    ) | \
 ((ICLIPI( ((int32)(int8)(((r1)>> 8)&0x000000ff)) +((int32)(int8)(((r2)>> 8)&0x000000ff)) ,127)&0x000000ff )<< 8) | \
 ((ICLIPI( ((int32)(int8)(((r1)>>16)&0x000000ff)) +((int32)(int8)(((r2)>>16)&0x000000ff)) ,127)&0x000000ff )<<16) | \
 ((ICLIPI( ((int32)(int8)(((r1)>>24)&0x000000ff)) +((int32)(int8)(((r2)>>24)&0x000000ff)) ,127)&0x000000ff )<<24) )
#endif

#ifndef DSPIQUADSUB
#define DSPIQUADSUB(r1, r2)   \
(((ICLIPI( ((int32)(int8)( (r1)     &0x000000ff)) -((int32)(int8)( (r2)     &0x000000ff)) ,127)&0x000000ff )    ) | \
 ((ICLIPI( ((int32)(int8)(((r1)>> 8)&0x000000ff)) -((int32)(int8)(((r2)>> 8)&0x000000ff)) ,127)&0x000000ff )<< 8) | \
 ((ICLIPI( ((int32)(int8)(((r1)>>16)&0x000000ff)) -((int32)(int8)(((r2)>>16)&0x000000ff)) ,127)&0x000000ff )<<16) | \
 ((ICLIPI( ((int32)(int8)(((r1)>>24)&0x000000ff)) -((int32)(int8)(((r2)>>24)&0x000000ff)) ,127)&0x000000ff )<<24) )
#endif

#define DUALIMULM(r1, r2) \
( \
(((((int32)((int16)((r1)&0x0000FFFF))) * ((int32)((int16)((r2)&0x0000FFFF)))) >> 16) & 0x0000FFFF) | \
((((int32)((int16)((r1)>>16))) * ((int32)((int16)((r2)>>16)))) & 0xFFFF0000) \
)

#ifndef DSPUQUADABSSUB
#define DSPUQUADABSSUB(r1, r2) \
(IABS((int32)(((r1)&0xff)-((r2)&0xff)))&0xff) | \
((IABS((int32)((((r1<<16)>>24)&0xff)-(((r2<<16)>>24)&0xff)))&0xff)<<8) | \
((IABS((int32)((((r1<<8)>>24)&0xff)-(((r2<<8)>>24)&0xff)))&0xff)<<16) | \
((IABS((int32)(((r1>>24)&0xff)-((r2>>24)&0xff)))&0xff)<<24)
#endif

#ifndef DSPUQUADABSSUBI
#define DSPUQUADABSSUBI DSPUQUADABSSUB
#endif
/*#define DSPUQUADABSSUBI(r1, r2) \
(IABS((int32)(int8)((r1)&0xff)-(int32)(int8)((r2)&0xff))&0xff) | \
((IABS(((int32)(int8)((r1<<16)>>24))-((int32)(int8)((r2<<16)>>24)))&0xff)<<8) | \
((IABS(((int32)(int8)((r1<<8)>>24))-((int32)(int8)((r2<<8)>>24)))&0xff)<<16) | \
((IABS((int32)(int8)(r1>>24)-(int32)(int8)(r2>>24))&0xff)<<24)
*/
//notice
#ifndef DSPUQUADSUB
#define DSPUQUADSUB(r1, r2) \
( (UCLIPI(((int32)(uint8)(((r1)    )&0xff))-((int32)(uint8)(((r2)    )&0xff)),255)&0xff) | \
 ((UCLIPI(((int32)(uint8)(((r1)>> 8)&0xff))-((int32)(uint8)(((r2)>> 8)&0xff)),255)&0xff)<<8) | \
 ((UCLIPI(((int32)(uint8)(((r1)>>16)&0xff))-((int32)(uint8)(((r2)>>16)&0xff)),255)&0xff)<<16) | \
 ((UCLIPI(((int32)(uint8)(((r1)>>24)&0xff))-((int32)(uint8)(((r2)>>24)&0xff)),255)&0xff)<<24) )
#endif

#ifndef DSPUQUADADD
#define DSPUQUADADD(r1, r2) \
( (UCLIPI(((uint32)(uint8)(((r1)    )&0xff))+((uint32)(uint8)(((r2)    )&0xff)),255)&0xff) | \
 ((UCLIPI(((uint32)(uint8)(((r1)>> 8)&0xff))+((uint32)(uint8)(((r2)>> 8)&0xff)),255)&0xff)<<8) | \
 ((UCLIPI(((uint32)(uint8)(((r1)>>16)&0xff))+((uint32)(uint8)(((r2)>>16)&0xff)),255)&0xff)<<16) | \
 ((UCLIPI(((uint32)(uint8)(((r1)>>24)&0xff))+((uint32)(uint8)(((r2)>>24)&0xff)),255)&0xff)<<24) )
#endif

//#define MERGEODD(r1, r2) (((r2)&0x000000FF) | (((r1)&0x000000FF)<<8) | ((r2)&0x00FF0000) | (((r1)&0xFF0000)<<8))
#ifndef MERGEODD
#define MERGEODD(r1, r2) (((r2)&0x00FF00FF) | (((r1)&0x00FF00FF)<<8))
#endif

#ifndef SWAPBYTES
#define SWAPBYTES(r1) ((((r1)&0x000000ff)<<24) | (((r1)&0x0000ff00)<<8) | (((r1)&0x00ff0000)>>8) | (((r1)>>24)&0x000000ff))
#endif

//#define BILINEAR1(r1, r2)
//((r1)&0x03030303) + ((r2)&0x03030303) + 0x00010001
//stanley 20040907
#define BILINEAR1(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+1)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+1)>>2)&0x000000ff)<<16)
//stanley 20040907
#define BILINEAR2(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+2)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+2)>>2)&0x000000ff)<<16)

#define UCLIP8IASR8ADD(r1, r2) UCLIPI((((int32)(r1+r2))>>8),255)
#define ADDSUB(a, b) (a>0) ? a+b : ((a<0) ? a-b : 0 )

#ifndef QUADSUB
#define QUADSUB(r1, r2) \
((((int32)( r1     &0x000000ff))-((int32)(r2&0x000000ff)))&0x000000ff) | \
((((int32)((r1>> 8)&0x000000ff)-(int32)((r2>>8)&0x000000ff))&0x000000ff)<<8) | \
((((int32)((r1>>16)&0x000000ff)-(int32)((r2>>16)&0x000000ff))&0x000000ff)<<16) | \
((((int32)((r1>>24)&0x000000ff)-(int32)((r2>>24)&0x000000ff))&0x000000ff)<<24)
#endif

#ifndef QUADADD
#define QUADADD(r1, r2) \
((((int32)(r1&0x000000ff))+((int32)(r2&0x000000ff)))&0x000000ff) | \
((((int32)((r1>>8)&0x000000ff)+(int32)((r2>>8)&0x000000ff))&0x000000ff)<<8) | \
((((int32)((r1>>16)&0x000000ff)+(int32)((r2>>16)&0x000000ff))&0x000000ff)<<16) | \
((((int32)((r1>>24)&0x000000ff)+(int32)((r2>>24)&0x000000ff))&0x000000ff)<<24)
#endif

// floating point instruction
#define UFLOATRZ(a) ((float)(uint32)(a))

#ifndef CLSAME
#define CLSAME(a, b) MUX((((a)^(b))>>31)&1, 0, \
                     MUX((((a)^(b))>>30)&1, 1, \
                     MUX((((a)^(b))>>29)&1, 2, \
                     MUX((((a)^(b))>>28)&1, 3, \
                     MUX((((a)^(b))>>27)&1, 4, \
                     MUX((((a)^(b))>>26)&1, 5, \
                     MUX((((a)^(b))>>25)&1, 6, \
                     MUX((((a)^(b))>>24)&1, 7, \
                     MUX((((a)^(b))>>23)&1, 8, \
                     MUX((((a)^(b))>>22)&1, 9, \
                     MUX((((a)^(b))>>21)&1, 10, \
                     MUX((((a)^(b))>>20)&1, 11, \
                     MUX((((a)^(b))>>19)&1, 12, \
                     MUX((((a)^(b))>>18)&1, 13, \
                     MUX((((a)^(b))>>17)&1, 14, \
                     MUX((((a)^(b))>>16)&1, 15, \
                     MUX((((a)^(b))>>15)&1, 16, \
                     MUX((((a)^(b))>>14)&1, 17, \
                     MUX((((a)^(b))>>13)&1, 18, \
                     MUX((((a)^(b))>>12)&1, 19, \
                     MUX((((a)^(b))>>11)&1, 20, \
                     MUX((((a)^(b))>>10)&1, 21, \
                     MUX((((a)^(b))>> 9)&1, 22, \
                     MUX((((a)^(b))>> 8)&1, 23, \
                     MUX((((a)^(b))>> 7)&1, 24, \
                     MUX((((a)^(b))>> 6)&1, 25, \
                     MUX((((a)^(b))>> 5)&1, 26, \
                     MUX((((a)^(b))>> 4)&1, 27, \
                     MUX((((a)^(b))>> 3)&1, 28, \
                     MUX((((a)^(b))>> 2)&1, 29, \
                     MUX((((a)^(b))>> 1)&1, 30, \
                     MUX((((a)^(b))>> 0)&1, 31, 32))))))))))))))))))))))))))))))))
#endif

#ifdef _TM5250_
#define DUALADDSUB(a, b) ( ((MUX( ((((int32)(a))>>16)>0), ((((int32)(a))>>16)+(((int32)(b))>>16)), MUX(((((int32)(a))>>16)<0), ((((int32)(a))>>16)-(((int32)(b))>>16)),0) ))<<16) \
                         | ((MUX( ((int32)((short)((a)&0xffff)))>0, ((int32)((short)((a)&0xffff))+(int32)((short)((b)&0xffff))), MUX(((int32)((short)((a)&0xffff)))<0, ((int32)((short)((a)&0xffff))-(int32)((short)((b)&0xffff))), 0)))&0xffff) )

#ifndef DUALIADD
#define DUALIADD(a, b) (((a)&0xffff0000)+((b)&0xffff0000)) | (((a)+(b))&0xffff)
#endif

#ifndef DUALIMAX
#define DUALIMAX(a, b) PACK16LSB(((((int)a)>>16)) > ((((int)b)>>16)) ? ((((int)a)>>16)):((((int)b)>>16)), (((short)(((int)a)&0xffff)) > ((short)(((int)b)&0xffff)) ? ((int32)((short)(((int)a)&0xffff))):(int32)((short)(((int)b)&0xffff))))
#endif

#ifndef DUALIMIN
#define DUALIMIN(a, b) PACK16LSB(((((int)a)>>16)) < ((((int)b)>>16)) ? ((((int)a)>>16)):((((int)b)>>16)), (((short)(((int)a)&0xffff)) < ((short)(((int)b)&0xffff)) ? ((int32)((short)(((int)a)&0xffff))):(int32)((short)(((int)b)&0xffff))))
#endif

#ifndef DUALISUB
#define DUALISUB(a, b) (((a)&0xffff0000)-((b)&0xffff0000)) | (((a)-(b))&0xffff)
#endif

#ifndef DUALLSR
#define DUALLSR(a, i) ((((uint32)(a)>>(i))&0xffff0000) | ((uint32)(((uint16)a)&0xffff)>>(i)))
#endif

#define SWAPBITS(a)   assert(0)

#ifndef ALLOCD_SET
#define ALLOCD_SET(a, b, c) \
{ \
    int i=0; \
    int32 *add=(int32 *)((int32)(&(((char *)c)[a]))&0xffffffc0); \
    do { \
        *add = b; \
        i += 1; \
        add += 1; \
    } while(i<16); \
}
#endif

#define DINVALID(a, b)

#else
// emulation for tm5250 instructions
#ifndef DUALIADD
#define DUALIADD(a, b) DSPIDUALADD(a, b)
#endif
#ifndef DUALISUB
#define DUALISUB(a, b) DSPIDUALSUB(a, b)
#endif

#endif

#ifdef _TM3270_

#define DSPUDUALABSSUBI(a, b)
#define DUALIAVG(a, b)
#define DUALIFLIP(a, b)
#define DUALILEQ(a, b)
#define MERGEDUAL16MSB(a, b)
#define MERGEEVEN(a, b)
#define QUADIMAX(a, b)
#define QUADIMIN(a, b)
#define TWOSLOT_LD32D(d1, d2, a, imm)
#define TWOSLOT_LD32R(d1, d2, a, b)
#define TWOSLOT_LD32X(d1, d2, a, b)
#define TWOSLOT_PACKLSBYTES(d1, d2, a, b, c, d)
#define TWOSLOT_PACKMSBYTES(d1, d2, a, b, c, d)
#define UME16II(a, b)
// video ase
#define DUALISCALEUI_RMINF(a, b)
#define DUALISCALEUI_RNINT(a, b)
#define DUALISCALEUI_RNINTZ(a, b)
#define DUALISCALEUI_RZ(a, b)
#define ISCALEFIR8UI(a, b)
#define ISCALEFIR16(a, b)
#define LD_FRAC8(a, b)
#define LD_FRAC16(a, b)
#define LD_PACKFRAC8(a, b)
#define LD_PACKFRAC16(a, b)
#define TWOSLOT_DUALIMEDIAN(a, b, c)
#define TWOSLOT_DUALIMIX(d1, d2, a, b, c, d)
#define TWOSLOT_DUALISCALEMIX(a, b, c, d)
#define TWOSLOT_IFIR8UI(a, b, c, d)
#define TWOSLOT_IFIR16(a, b, c, d)
#define TWOSLOT_ISCALEFIR8UI(a, b, c, d)
#define TWOSLOT_ISCALEFIR16(a, b, c, d)
#define TWOSLOT_QUADIMEDIAN(a, b, c, d)
#define TWOSLOT_QUADIMIXUI(d1, d2, a, b, c, d)
#define TWOSLOT_QUADISCALEMIXUI(a, b, c, d)
#define TWOSLOT_QUADUMEDIAN(a, b, c)
#define TWOSLOT_QUADUSCALEMIXUI(a, b, c, d)
#define USCALEFIR8UI(a, b)

// cabac decoding operation
#define TWOSLOT_CABAC_CTX(d1, d2, a, b, c, d)
#define TWOSLOT_CABAC_EQP(d1, d2, a, b, c)
#define TWOSLOT_CABAC_FIN_CTX(a, b, c)
#define TWOSLOT_CABAC_FIN_STR(d1, d2, a, b)
#define TWOSLOT_CABAC_STR(d1, d2, a, b, c, d)

#endif
///////////////////////////////////////////////////////////////////

// combination of customized ops
#define QUADUCLIPU(c, min, max) QUADUMIN(QUADUMAX(c, min), max)

#ifndef LSR8
#define LSR8(a)  (((uint32)(a))>>8)
#endif

#ifndef LSR16
#define LSR16(a) (((uint32)(a))>>16)
#endif

#ifndef LSR24
#define LSR24(a) (((uint32)(a))>>24)
#endif

#ifndef LSL8
#define LSL8(a)  (((uint32)(a))<<8)
#endif

#ifndef LSL16
#define LSL16(a) (((uint32)(a))<<16)
#endif

#ifndef LSL24
#define LSL24(a) (((uint32)(a))<<24)
#endif

#endif //__TCS__

#ifndef LSHIFTR32
#define LSHIFTR32(a, b) (MUX((uint32)(b)>=0x20, 0, (a)>>(b)))
#endif

#ifndef LSHIFTL32
#define LSHIFTL32(a, b) (MUX((uint32)(b)>=0x20, 0, (a)<<(b)))
#endif

#ifndef SH_PLUS32
#define SH_PLUS32(a) (32 + (a))
#endif

// IEEE 745 format SEE...EM...M
//                 01    89   31
#define GETUSPEXP(a) ((a)>>23)

#define make_uint32(a,b,c,d) (PACK16LSB(PACK_2_U8((a), (b)), PACK_2_U8((c), (d))))
#define make_uint32_inst16(a, b, c, d) (((a)<<24) | ((b)<<16) | ((c)<<8) | (d))
#define make_uint32_inst32(a, b, c, d) (PACK16LSB(PACK_2_U8((a), (b)), PACK_2_U8((c), (d))))
//#ifdef _TM3260_
#define BSWAP SWAPBYTES
//#else
//#define BSWAP(a) PACK16LSB(PACKBYTES(a, UBYTESEL(a,1)),PACKBYTES(UBYTESEL(a,2), UBYTESEL(a,3)))
//#endif

#define FUNSHIFT0(a, b)   a
#define FUNSHIFT4(a, b)   b

#ifndef CLIP3
#define CLIP3(a, b, c) (((int)(c))<(a) ? (a) : ((int)(c))>(b) ? (b) : (c))
#endif

#ifdef _TM5250_
#define DUALIADDX  DUALIADD
#define DUALISUBX  DUALISUB
#else
#define DUALIADDX  DSPIDUALADD
#define DUALISUBX  DSPIDUALSUB
#endif

#ifndef IBYTEDUP0
#define IBYTEDUP0(x) PACK16LSB(MERGELSB(x,x), MERGELSB(x,x))
#endif

#ifndef IBYTEDUP1
#define IBYTEDUP1(x) PACK16MSB(MERGELSB(x,x), MERGELSB(x,x))
#endif

#ifndef IBYTEDUP2
#define IBYTEDUP2(x) PACK16LSB(MERGEMSB(x,x), MERGEMSB(x,x))
#endif

#ifndef IBYTEDUP3
#define IBYTEDUP3(x) PACK16MSB(MERGEMSB(x,x), MERGEMSB(x,x))
#endif

#define FACTOR_0(a) 0
#define FACTOR_1(a) (a)
//#define FACTOR_2(a) ((a)<<1)
#define FACTOR_2(a) ((a)+(a))
//#define FACTOR_3(a) (((a)<<1)+(a))
#define FACTOR_3(a) ((a)+(a)+(a))
#define FACTOR_4(a) ((a)<<2)
#define FACTOR_5(a) (((a)<<2)+(a))
//#define FACTOR_6(a) (((a)<<2)+((a)<<1))
#define FACTOR_6(a) (((a)<<2)+((a)+(a)))
#define FACTOR_7(a) (((a)<<3)-(a))
#define FACTOR_8(a) ((a)<<3)
#define FACTOR_9(a) (((a)<<3)+(a))
//#define FACTOR_10(a) (((a)<<3)+((a)<<1))
#define FACTOR_10(a) (((a)<<3)+((a)+(a)))
//#define FACTOR_11(a) (((a)<<3)+((a)<<1)+(a))
#define FACTOR_11(a) (((a)<<3)+((a)+(a))+(a))
#define FACTOR_12(a) (((a)<<3)+((a)<<2))
#define FACTOR_13(a) (((a)<<3)+((a)<<2)+(a))
//#define FACTOR_14(a) (((a)<<4)-((a)<<1))
#define FACTOR_14(a) (((a)<<4)-((a)+(a)))
#define FACTOR_15(a) (((a)<<4)-(a))
#define FACTOR_16(a) ((a)<<4)
#define FACTOR_17(a) (((a)<<4)+(a))
#define FACTOR_20(a) (((a)<<4)+((a)<<2))
#define FACTOR_25(a) (((a)<<4)+((a)<<3)+a)
#define FACTOR_32(a) ((a)<<5)
#define FACTOR_48(a) (((a)<<5)+((a)<<4))

#define CONVUINTXTOUINT32(x) (*(uint32*)(&(x)))
#define CONVPUINTXTOUINT32(x) (*(uint32*)(x))
#define CONVUINTXTOUINT16(x) (*(uint16*)(&(x)))
#define CONVPUINTXTOUINT16(x) (*(uint16*)(x))

#define CONVUINTXTOPUINT32(x) (uint32*)(&(x))
#define CONVUINTXTOPUINT16(x) (uint16*)(&(x))
#define CONVUINTXTOPUINT8(x) (uint8*)(&(x))
#define CONVPUINTXTOPINT32(x) ((int32*)(&(x)))
#define CONVPUINTXTOPINT16(x) ((int16*)(&(x)))
#define CONVPUINTXTOPINT8(x) ((int8*)(&(x)))

#define MUL_0_1(f, q) MUX(f&1, q, 0)
//#define MUL_0_3(f, q) (MUX(f&2, q+q, 0) + MUX(f&1, q, 0))
#define MUL_0_3(f, q) ((f)*(q))


#ifndef PACK_2_U16
#define PACK_2_U16(a, b) (((a) << 16) | (b))
#endif

#ifndef PACK_2_U8
#define PACK_2_U8(a, b)  (((a) << 8) | (b))
#endif

#ifndef PACK_U24_U8
#define PACK_U24_U8(a, b) (((a) << 8) | (b))
#endif

#ifndef PACK_U8_U24
#define PACK_U8_U24(a, b) (((a) << 24) | (b))
#endif

#ifndef _B1
#define _B1(x) (x)
#endif

#ifndef MEDIAN3
#define MEDIAN3(a, b, c) IMIN(IMAX(IMIN((a), (b)), (c)), IMAX((a), (b)))
#endif

#ifndef MEDIAN4
#define MEDIAN4(a, b, c, d) (((a)+(b)+(c)+(d)-IMIN(IMIN(IMIN((a),(b)),(c)),(d))-IMAX(IMAX(IMAX((a),(b)),(c)),(d)))/2)
#endif

#define SWAP2(type, a, b) \
{ \
    type swap_tmp; swap_tmp = a; a = b; b = swap_tmp; \
}

#ifndef idiv
#define idiv(a, b) ((a)/(b))
#endif

#define idiv2(a) (((a)+((a)<0))>>1)

/* CLIP x (signed) to a ... b */
//#define myCLIP(x, a, b)   ((int32) UCLIPI((uint32)((x)-(a)), (uint32)((b)-(a)))+(a))
#define myCLIP(x, a, b)    IMAX(IMIN(x, b), a)
#define myDUALCLIP(x, a, b)  DUALIMAX(DUALIMIN(x, b), a)
#define myUCLIP(x, a, b)   (UCLIPI(((x)-(a)), ((b)-(a)))+(a))

#define csosmoDUALICLIPI(x, a, b) DSPIDUALADD(DUALUCLIPI(DSPIDUALSUB(x,a), DSPIDUALSUB(b,a)),a)

//#define myDUALUCLIP(x, a, b)    DSPIDUALADD(DUALUCLIPI(DSPIDUALSUB(x,a), DSPIDUALSUB(b,a)),a)
//#define myDUALUCLIP(x, a, b)    DSPIDUALADD(DUALUCLIPI(DSPIDUALSUB(x,a), DSPIDUALSUB(b,a)),a)

#define myDUALUCLIP(x, a, b)    DSPIDUALADD(PACK16LSB(UCLIPI(((int)DSPIDUALSUB(x,a))>>16, PACK16MSB(0, DSPIDUALSUB(b,a))), DUALUCLIPI((int16)DSPIDUALSUB(x,a), DSPIDUALSUB(b,a))),a)

#endif // COMMON_H
