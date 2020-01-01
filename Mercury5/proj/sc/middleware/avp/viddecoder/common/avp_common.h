#ifndef COMMON_H
#define COMMON_H

/*lint -emacro(504, SH_PLUS32) */
/*lint -emacro(514, idiv2) */

#include "avp_mvc_types.h"

#define _AG_S32_

#if defined(WIN32)
#define _X86_  // disable this if you would like to simulate other platform
#endif

// select ISA mapping
#ifdef __ARMCC_VERSION
#include "avp_arm9e_rvct.h" //"armdsp.h" // ARM9 with RealView
#endif

#if defined(WINCE) && defined(ARM9)
#include "avp_arm9e_wm6.h" //"inline_fns.h"  // ARM9 with Windows Mobile Compiler
#endif

#if defined(_X86_) && defined(_MSC_VER)
//#define _X86_OPT_
//#define _X86_OPT_2_ // specific for x86 opt, not sure if conformance can be passed
#include "avp_x86_vc.h" // X86 with VC


#include "avp_aeon_simd_gcc.h"
//#define _AG_V32_
//#define _AG_V64_
//#define CCIR656_CLIP
//#define CCIR656_CLIP_CHECK
#endif

#ifdef _MIPS_
#ifdef __mips_dsp
#define _AG_DSP_ASE_
#endif
#include "avp_mips32_gcc.h" //<mips/mips32.h>
#endif

#ifdef _AEON
#include "avp_aeon_gcc.h"
#ifdef AEONDEV_V1
#define _AEON_V64_
#endif

#ifdef _AEON_V64_
#include "avp_aeon-simd.h"
//#define _AG_V64_
//#define CCIR656_CLIP
//#define CCIR656_CLIP_CHECK
//#define _R2_DMA_
#define USE_QMEM
#define HAS_QMEM
#endif
#endif

#ifdef _TM5250_
#if !defined(_AG_S32_)
#define _UAMEM_ACCESS_ // unaligned memory access
#endif
#define _TM3_ISA_
#endif

#ifdef _TM3270_
#define _TM4_ISA_
#endif

///////////////////////////////////////////////////////////

#ifndef EMPTY_EMMS
#define EMPTY_EMMS
#endif

#ifndef SHORT_BRANCH_NEVER
#define SHORT_BRANCH_NEVER
#endif

#ifdef __TCS__
#include "avp_tm_tcs.h"
#define _AG_V32_
#else //!__TCS__

#ifndef UNUSED
#if defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif

#ifndef RESTRICT
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define RESTRICT __restrict__
#else
#define RESTRICT
#endif
#endif

#ifndef INLINE
#ifdef __ARMCC_VERSION
#define INLINE __inline
#elif defined(__GNUC__)
#define INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE
#endif
#endif

#ifndef DECL_ALIGN
#ifdef __ARMCC_VERSION
#define DECL_ALIGN(x) __attribute__((aligned(x)))
#elif defined(__GNUC__)
#define DECL_ALIGN(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
#define DECL_ALIGN(x) __declspec(align(x))
#else
#define DECL_ALIGN(x)
#endif
#endif

#ifndef LIKELY
#ifdef __GNUC__
#define LIKELY(x)     __builtin_expect(!!(x), 1)
#else
#define LIKELY(x)     (x)
#endif
#endif

#ifndef UNLIKELY
#ifdef __GNUC__
#define UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#define UNLIKELY(x)     (x)
#endif
#endif

/* macro for pointer alignment to ground, n must be power of 2 */
#define ALIGN_PTR_GROUND(p, n)  ((void *) (((intptr_t) (p)) & -(n)))

/* macro for pointer alignment, n must be power of 2 */
#define ALIGN_PTR(p, n)  ((void *) (((intptr_t) (p) + ((n) - 1)) & -(n)))

#ifndef ATTR_INST16
#define ATTR_INST16
#endif

#ifndef ATTR_INST16_M2
#define ATTR_INST16_M2
#endif

#ifndef ATTR_INST16_M3
#define ATTR_INST16_M3
#endif

#ifndef LOAD32U
#define LOAD32U(dst, src, imm) do {                                 \
    const uint8 * RESTRICT src_l = (const uint8 *) (src);           \
    uint32 t0_, t1_, t2_, t3_;                                      \
    t0_ = src_l[(imm) + 0];                                         \
    t1_ = src_l[(imm) + 1];                                         \
    t0_ = t0_ | (t1_ << 8);                                         \
    t2_ = src_l[(imm) + 2];                                         \
    t3_ = src_l[(imm) + 3];                                         \
    t2_ = t2_ | (t3_ << 8);                                         \
    dst = t0_ | (t2_ << 16);                                        \
} while (0)
#endif

#ifndef STORE32U
#define STORE32U(dst, src, imm) do {                             \
    const uint8 * RESTRICT src_l = (const uint8 *) (&(src));     \
    uint8 * RESTRICT dst_l = (uint8 *) (dst);                    \
    dst_l[(imm) + 0] = src_l[0];                                 \
    dst_l[(imm) + 1] = src_l[1];                                 \
    dst_l[(imm) + 2] = src_l[2];                                 \
    dst_l[(imm) + 3] = src_l[3];                                 \
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
#define IABS(a)         ((a) > 0 ? (a) : -(a))
#endif
#define ADDSUB(a, b)    ((a) > 0 ? (a) + (b) : ((a) < 0 ? (a) - (b) : 0))

#define INEG(a)         (-(a))
// logical operations
//#define ROL(a,b)      // need to check
#define ROL(a,b)       ((((uint32)(a))<<(b)) | ((((uint32)(a))>>(32-b)) & ((1<<b)-1)) )
// sign extension operations
#define SEX8(a)  ((int32)(int8)(a))
#define SEX16(a) ((int32)(int16)(a))
#define ZEX8(a)  ((uint32)(uint8)(a))
#define ZEX16(a) ((uint32)(uint16)(a))
// 3.   Immediate Operations
// logical operations
//#define ASLI
#ifndef ROLI
#define ROLI(a,b)       ((((uint32)(a))<<(b)) | ((((uint32)(a))>>(32-b)) & ((1<<b)-1)) )
#endif
#define ASR(a,i)        (((int32)(a))>>(i))
#define LSRI(a,i)       (((uint32)(a))>>(i))    // compiler probably use this instruction automatically
// special multiply operations
#define IMUL (a, b) ((int32)(((int32)(a)) * ((int32)(b))))

#ifndef SMLABB
#define SMLABB(x, y, a) (((x) * (y)) + (a))
#endif

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

#ifndef FUNSHIFT_VAR
#define FUNSHIFT_VAR(a, b, offset_a, offset_b)  (((a) << (offset_a)) | (((uint32)(b)) >> (offset_b)))
#endif

// clip operations
#ifndef ICLIPI
#define ICLIPI(x, c)    MIN(MAX((int)(x), -(c)-1), (c))
#endif
#ifndef UCLIPI
#define UCLIPI(x, c)    MIN(MAX((int)(x), 0), (c))
#endif
#ifndef SAT32
#define SAT32(x, c)    MIN(MAX((int64)(x), -(c)-1), (c))
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

#define BILINEAR1(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+1)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+1)>>2)&0x000000ff)<<16)
//stanley 20040907
#define BILINEAR2(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+2)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+2)>>2)&0x000000ff)<<16)

#define UCLIP8IASR8ADD(r1, r2) UCLIPI((((int32)(r1+r2))>>8),255)

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

#define FUNSHIFT0(a, b)     (a)
#define FUNSHIFT4(a, b)     (b)

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

#ifndef IHALFWORDDUP
#define IHALFWORDDUP(a) PACK16LSB(a, a)
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

#define MUL_0_1(f, q) MUX((f)&1, q, 0)
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

#ifndef UCLIPI_255
#define UCLIPI_255(x) UCLIPI(x, 255)
#endif

#ifndef ICLIPI_2047
#define ICLIPI_2047(x) ICLIPI(x, 2047)
#endif

#ifndef ROLI_24
#define ROLI_24(x) ROLI(x, 24)
#endif

#ifndef PRECRQ_PH_W
#define PRECRQ_PH_W(rs, rt)         (((rs)&0xffff0000) | (((rt)&0xffff0000)>>16))
#endif

#ifndef PRECRQ_QB_PH
#define PRECRQ_QB_PH(rs, rt)        (((rs)&0xff000000)) | (((rs)&0x0000ff00) << 8) | (((rt)&0xff000000) >> 16) | (((rt)&0x0000ff00) >> 8)
#endif

#ifndef PRECEU_PH_QBR
#define PRECEU_PH_QBR(rt)           (((rt)&0x0000ff00) << 8) | (((rt)&0x000000ff))
#endif

#ifndef PRECEU_PH_QBL
#define PRECEU_PH_QBL(rt)           (((rt)&0xff000000) >> 8) | (((rt)&0x00ff0000) >> 16)
#endif

#ifndef PRECEU_PH_QBRA
#define PRECEU_PH_QBRA(rt)          ((rt)&0x00ff00ff)
#endif

#ifndef PRECEU_PH_QBLA
#define PRECEU_PH_QBLA(rt)          (((rt)>>8)&0x00ff00ff)
#endif

#ifndef SHRA_PH
#define SHRA_PH(rt, sa)             ((int)((short)(((rt)&0xffff0000) >> 16) >> sa) << 16) | ((int)((short)((rt)&0x0000ffff) >> sa) & 0x0000ffff)
#endif

#ifndef PACKRL_PH
#define PACKRL_PH(rs, rt)           (((rs)&0x0000ffff) << 16) | (((rt)&0xffff0000) >> 16)
#endif

#ifndef ADDQ_PH
#define ADDQ_PH(rs, rt)             ((int)((short)(((rs) >> 16)&0x0000ffff) + (short)(((rt) >> 16)&0x0000ffff)) << 16) | \
                                    ((int)((short)(((rs)      )&0x0000ffff) + (short)(((rt)      )&0x0000ffff)) & 0x0000ffff )
#endif

#ifndef SUBQ_PH
#define SUBQ_PH(rs, rt)             ((int)((short)(((rs) >> 16)&0x0000ffff) - (short)(((rt) >> 16)&0x0000ffff)) << 16) | \
                                    ((int)((short)(((rs)      )&0x0000ffff) - (short)(((rt)      )&0x0000ffff)) & 0x0000ffff )
#endif

#ifndef DPAQ_S_W_PH

#define DPAQ_S_W_PH(ac, rs, rt)     ((ac) + ((int64)SAT32((((int64)((short)((rs)>>   16)) * (int64)((short)((rt)>>   16))) << 1), 0x7fffffff) +  \
                                             (int64)SAT32((((int64)((short)((rs)&0xffff)) * (int64)((short)((rt)&0xffff))) << 1), 0x7fffffff)))
#endif

#ifndef MULEQ_S_W_PHL
#define MULEQ_S_W_PHL(rs, rt)      SAT32((((int64)((short)((rs)>>   16)) * (int64)((short)((rt)>>   16))) << 1), 0x7fffffff)
#endif

#ifndef MULEQ_S_W_PHR
#define MULEQ_S_W_PHR(rs, rt)      SAT32((((int64)((short)((rs)&0xffff)) * (int64)((short)((rt)&0xffff))) << 1), 0x7fffffff)
#endif

#ifndef CMP_AND_PICK_PH
#define CMP_AND_PICK_PH(a, b)       PACK16LSB((((INT32)(a)) >> 16)         < (((INT32)(b)) >> 16)          ? ((INT32)(a)) >> 16           : 0, \
                                              (INT32)(short)((a) & 0xFFFF) < (INT32)(short)((b) & 0xFFFF)  ? (INT32)(short)((a) & 0xFFFF) : 0);
#endif

#ifndef CMP_AND_PICK_PH2
#define CMP_AND_PICK_PH2(a, b)       PACK16LSB((((INT32)(a)) >> 16)           >= (0)  ? ((INT32)(b)) >> 16           : 0, \
                                                 (INT32)(short)((a) & 0xFFFF) >= (0)  ? (INT32)(short)((b) & 0xFFFF) : 0);
#endif

#endif // COMMON_H
