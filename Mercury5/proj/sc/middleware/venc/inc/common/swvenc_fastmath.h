#ifndef _FAST_MATH_H_
#define _FAST_MATH_H_

#ifdef WIN32
#include <stdlib.h>
#endif

#ifdef WIN32
#define ABS abs
#else
#define ABS iabs
static ALWAYSINLINE int32 iabs(int32 x)
{
    return ((x)>0 ? (x) : -(x));
}
//#define ABS(a)               ((a)>0 ? (a) : -(a))
#endif


#define FACTOR_0(a) 0
#define FACTOR_1(a) (a)
#define FACTOR_2(a) ((a)+(a))
#define FACTOR_3(a) ((a)+(a)+(a))
#define FACTOR_4(a) ((a)<<2)
#define FACTOR_5(a) (((a)<<2)+(a))
#define FACTOR_6(a) (((a)<<2)+((a)+(a)))
#define FACTOR_7(a) (((a)<<3)-(a))

#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define MIN(a,b)        ((a) < (b) ? (a) : (b))

#ifdef _MIPS_
#include <mips/mips32.h>
#define INS(t, v, pos, size)    _mips32r2_ins(t, v, pos, size)
#define EXT(x, pos, size)		_mips32r2_ext(x, pos, size)
#define SWAPBYTES(r1)			_mips32r2_bswapw(r1)
#define PACK_2_U8(a, b)  INS(b, a, 8, 8)
#define PACK16LSB(a, b)  INS(b, a, 16, 16)
#else
#define PACK_2_U8(a, b)  (((a) << 8) | (b))
#define PACK16LSB(a, b) (((a)<<16) | ((b)&0xffff))
#endif

#define UCLIPI(x, c) MIN(MAX((int)(x), 0), (c))
#define make_uint32(a,b,c,d) (PACK16LSB(PACK_2_U8((a), (b)), PACK_2_U8((c), (d))))
#define MUX(c, a, b)    ((c) ? (a) : (b))

#endif // _FAST_MATH_H_
