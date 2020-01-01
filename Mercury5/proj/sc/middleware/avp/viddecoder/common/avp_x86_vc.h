#ifndef X86_VC_H
#define X86_VC_H

#include <stdint.h>
#include <mmintrin.h>  // MMX
#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
#include <tmmintrin.h> // Supplemental Streaming SIMD Extensions 3 (SSSE3)
//#include <smmintrin.h> // Streaming SIMD Extensions 4 (SSE4) 

#define EMPTY_EMMS _asm { emms }

// 4.   Special Compute Operations

// dual arithmetic operations
#define DSPIDUALADD(a, b) _mm_cvtsi64_si32(_mm_adds_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))
#ifndef DSPIDUALSUB
#define DSPIDUALSUB(a, b) _mm_cvtsi64_si32(_mm_subs_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))
#endif
#ifdef _X86_OPT_2_
#define DSPIDUALMUL(a, b) _mm_cvtsi64_si32(_mm_mullo_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))
#else
#define DSPIDUALMUL(a, b) ((ICLIPI((((int32)(a))>>16)*(((int32)(b))>>16), 32767)<<16) | ((ICLIPI((int32)((short)((a)&0xffff))*(int32)((short)((b)&0xffff)), 32767)&0xffff)))
#endif
// dual shifting operations
#define DUALASR(a,i)    _mm_cvtsi64_si32(_mm_srai_pi16(_mm_cvtsi32_si64(a), i))
// dual clipping operations
#define DUALICLIPI(x,c) _mm_cvtsi64_si32(_mm_min_pi16(_mm_max_pi16(_mm_cvtsi32_si64(x), _mm_set_pi16(-(c)-1,-(c)-1,-(c)-1,-(c)-1)), _mm_set_pi16(c,c,c,c)))
// old
//#define DUALUCLIPI(x,c) ((MIN(MAX(/*(int32)*/((x)>>16), 0), c)<<16) | (MIN(MAX((int32)((short)((x)&0xffff)), 0), c)&0xffff))
// new
#ifndef DUALUCLIPI
#ifdef _X86_OPT_2_
#define DUALUCLIPI(x,c) _mm_cvtsi64_si32(_mm_min_pi16(_mm_max_pi16(_mm_cvtsi32_si64(x), _mm_setzero_si64()), _mm_set_pi16(c,c,c,c)))
#else
#define DUALUCLIPI(x,c) (((uint32)MIN((uint16)MAX(((short)(((int32)(x))>>16)), 0), (uint16)c)<<16) | (MIN((uint16)MAX(((short)((x)&0xffff)), 0), (uint16)c)&0xffff))
#endif
#endif
// byte packing operations
#define PACKBYTES(a, b) ((((a)&0x000000ff)<<8) | ((b)&0x000000ff))
#define MERGEMSB(a,b) ((((uint32)(a))&0xFF000000L) | ((((uint32)(a))&0x00FF0000L) >> 8) | ((((uint32)(b))&0xFF000000L) >> 8) | ((((uint32)(b))&0x00FF0000L) >> 16))
#define MERGELSB(a,b)   ( (((a)&0x0000ff00)<<16) | (((a)&0x000000ff)<<8) | (((b)&0x0000ff00)<<8) | ((b)&0x000000ff) )
#define PACK16MSB(a, b) (((a)&0xffff0000) | (((uint32)(b))>>16))
#define PACK16LSB(a, b) (((a)<<16) | ((b)&0xffff))
#define MERGEDUAL16LSB(a,b) ( (((a)&0x00ff0000)<<8) | (((a)&0x000000ff)<<16) | (((b)&0x00ff0000)>>8) | ((b)&0x000000ff) )
// byte select operations
#define UBYTESEL(a, i)  ((uint32)((uchar)((a)>>(((i)&3)<<3))))  // unsign extended
#define UBYTESEL_INST32(a, i)  ((uint32)((uchar)((a)>>(((i)&3)<<3))))
#define UBYTESEL_INST16(a, i)  ((uint32)((uchar)((a)>>(((i)&3)<<3))))
#define IBYTESEL(a, i)  (int32)((char)(((a)>>(((i)&3)<<3))&0xff))  // sign extended
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

#define IFIR16(a, b)    _mm_cvtsi64_si32(_mm_madd_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

//#define UFIR16
// sum of differences operations
//#define UME8II
//#define UME8UU
// special byte shift operations
#define FUNSHIFT1(a,b)  (((a)<<8)  | (((uint32)(b))>>24))
#define FUNSHIFT2(a,b)  (((a)<<16) | (((uint32)(b))>>16))
#define FUNSHIFT3(a,b)  (((a)<<24) | (((uint32)(b))>>8 ))
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


#define DSPUQUADADDUI(r1, r2)   \
((UCLIPI( ((int32)( (r1)     &0x000000ff)) +((int32)(int8)( (r2)     &0x000000ff)), 255)    ) | \
 (UCLIPI( ((int32)(((r1)>> 8)&0x000000ff)) +((int32)(int8)(((r2)>> 8)&0x000000ff)), 255)<< 8) | \
 (UCLIPI( ((int32)(((r1)>>16)&0x000000ff)) +((int32)(int8)(((r2)>>16)&0x000000ff)), 255)<<16) | \
 (UCLIPI( ((int32)(((r1)>>24)&0x000000ff)) +((int32)(int8)(((r2)>>24)&0x000000ff)), 255)<<24) )

//#define DSPUQUADADDUI(a,b) ((UCLIPI((((uint32)(a)&0xff000000)>>24)+(((uint32)(b)&0xff000000)>>24),255)<<24) | (UCLIPI((((uint32)(a)&0x00ff0000)+((char)((uint32)(b)&0x00ff0000))>>16),255)<<16) | (UCLIPI((((uint32)(a)&0x0000ff00)+((uint32)(b)&0x0000ff00))>>8,255)<<8) | UCLIPI(((uint32)(a)&0x000000ff)+((uint32)(b)&0x000000ff),255))

#define QUADUMAX(a, b)  _mm_cvtsi64_si32(_mm_max_pu8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define QUADUMIN(a, b)  _mm_cvtsi64_si32(_mm_min_pu8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#ifdef _TM3260_

#define DUALASL(a,i)    _mm_cvtsi64_si32(_mm_slli_pi16(_mm_cvtsi32_si64(a), i))

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

#define DSPIQUADADD(a, b) _mm_cvtsi64_si32(_mm_adds_pi8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DSPIQUADSUB(a, b) _mm_cvtsi64_si32(_mm_subs_pi8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DSPUQUADABSSUB(r1, r2) _mm_cvtsi64_si32(_mm_adds_pu8(_mm_subs_pu8(_mm_cvtsi32_si64(r1),_mm_cvtsi32_si64(r2)),_mm_subs_pu8(_mm_cvtsi32_si64(r2),_mm_cvtsi32_si64(r1))))

/*#define DSPUQUADABSSUBI(r1, r2) \
(IABS((int32)(int8)((r1)&0xff)-(int32)(int8)((r2)&0xff))&0xff) | \
((IABS(((int32)(int8)((r1<<16)>>24))-((int32)(int8)((r2<<16)>>24)))&0xff)<<8) | \
((IABS(((int32)(int8)((r1<<8)>>24))-((int32)(int8)((r2<<8)>>24)))&0xff)<<16) | \
((IABS((int32)(int8)(r1>>24)-(int32)(int8)(r2>>24))&0xff)<<24)
*/

//notice
#define DSPUQUADSUB(a, b) _mm_cvtsi64_si32(_mm_subs_pu8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DSPUQUADADD(a, b) _mm_cvtsi64_si32(_mm_adds_pu8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

//stanley 20040907
//#define MERGEODD(r1, r2) (((r2)&0x000000FF) | (((r1)&0x000000FF)<<8) | ((r2)&0x00FF0000) | (((r1)&0xFF0000)<<8))
//stanley 20040908
//#define SWAPBYTES(r1) ((((r1)&0x000000ff)<<24) | (((r1)&0x0000ff00)<<8) | (((r1)&0x00ff0000)>>8) | (((r1)>>24)&0x000000ff))
//#include "avp_intrin.h" // VC9
//#define SWAPBYTES _byteswap_ulong
#define SWAPBYTES swapbytes
static __inline uint32 swapbytes(uint32 r1)
{
    register uint32 c = r1;
    __asm mov eax, c __asm bswap eax __asm mov c, eax
    return c;
}

//stanley 20040907
#define BILINEAR1(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+1)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+1)>>2)&0x000000ff)<<16)
//stanley 20040907
#define BILINEAR2(r1, r2)   (((((r1)&0x000000ff) + ((r2)&0x000000ff) + ((r1>>8)&0x000000ff) + ((r2>>8)&0x000000ff)+2)>>2)&0x000000ff)| \
(((( ((r1>>16)&0x000000ff) + ((r2>>16)&0x000000ff) + ((r1>>24)&0x000000ff) + ((r2>>24)&0x000000ff)+2)>>2)&0x000000ff)<<16)

#define UCLIP8IASR8ADD(r1, r2) UCLIPI((((int32)(r1+r2))>>8),255)
#define ADDSUB(a, b) (a>0) ? a+b : ((a<0) ? a-b : 0 )

#define QUADSUB(a, b) _mm_cvtsi64_si32(_mm_sub_pi8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define QUADADD(a, b) _mm_cvtsi64_si32(_mm_add_pi8(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#endif

// floating point instruction
#define UFLOATRZ(a) ((float)(uint32)(a))

#ifdef _TM5250_

#define DUALADDSUB(a, b) ( ((MUX( ((((int32)(a))>>16)>0), ((((int32)(a))>>16)+(((int32)(b))>>16)), MUX(((((int32)(a))>>16)<0), ((((int32)(a))>>16)-(((int32)(b))>>16)),0) ))<<16) \
                         | ((MUX( ((int32)((short)((a)&0xffff)))>0, ((int32)((short)((a)&0xffff))+(int32)((short)((b)&0xffff))), MUX(((int32)((short)((a)&0xffff)))<0, ((int32)((short)((a)&0xffff))-(int32)((short)((b)&0xffff))), 0)))&0xffff) )

#define DUALIADD(a, b) _mm_cvtsi64_si32(_mm_add_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DUALIMAX(a, b) _mm_cvtsi64_si32(_mm_max_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DUALIMIN(a, b) _mm_cvtsi64_si32(_mm_min_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DUALISUB(a, b) _mm_cvtsi64_si32(_mm_sub_pi16(_mm_cvtsi32_si64(a), _mm_cvtsi32_si64(b)))

#define DUALLSR(a, i) _mm_cvtsi64_si32(_mm_srli_pi16(_mm_cvtsi32_si64(a), i))

#define ALLOCD_SET(a, b, c) \
{ \
    int i=0; \
    int32 *add=(int32 *)((int32)(&(((char *)c)[a]))&0xffffffc0); \
    do { \
        *add = b; \
        i += 1; \
        add += 1; \
    } while (i<16); \
}
#define DINVALID(a, b)

#else // _TM5250_
// emulation for tm5250 instructions
#define DUALIADD(a, b) DSPIDUALADD(a, b)
#define DUALISUB(a, b) DSPIDUALSUB(a, b)

#endif // _TM5250_

#ifdef _M_IX86
#define SH_PLUS32(a)    (a)
#endif

#define LOAD32U(dst, src, imm) dst = *(const uint32_t *) ((const uint8_t *) (src) + (imm))

#endif
