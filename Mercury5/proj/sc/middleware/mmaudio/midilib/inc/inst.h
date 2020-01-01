#if ! defined( DEVICE_inst_h )
#define DEVICE_inst_h
/*****************************************************************************/
/* DEVICE_inst_h                                                             */
/* inst.h                                                                    */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/
//#define __inline
//#pragma inline(	MUL16x16s15, 	MUL16x16s14,	MUL16x16s12,	MUL16x16s13,	MUL16x16s09,	MUL16x16s08,	MUL16x16s10,	MUL32x16s10,	MUL32x16s12,	MUL32x16s13,	MUL32x16s14,	MUL32x16s15 )

//#include <assert.h> //ccc unmark

#ifdef __GNUC__
#define __inline    static __inline __attribute__ ((always_inline))
#endif

#ifdef __aeon__

#include <machine/spr_defs.h>
#undef L_MULL

/* signed 32x32 to signed 64-bit multiply */
#define L_MULL(a, b)                        \
({  int _hi_, _lo_, _a_ = a, _b_ = b;       \
    __asm__ volatile ("l.mul\t%0,%1,%2"  \
        : "=r"(_lo_)                        \
        : "r"(_a_), "r"(_b_)                \
    );                                      \
    __asm__ volatile ("b.mfspr1\t%0,%1\t# hi32;" \
        : "=r"(_hi_)                        \
        : "K"(0x2803)                       \
    );                                      \
    ((long long)_hi_<<32)|(unsigned)_lo_;})

#define L_MULL_ASR(a, b, n)                 \
({  int _hi_, _lo_, _a_ = a, _b_ = b;       \
    __asm__ volatile ("l.mul\t%0,%1,%2"  \
        : "=r"(_lo_)                        \
        : "r"(_a_), "r"(_b_)                \
    );                                      \
   __asm__ volatile ("b.mfspr1\t%0,%1\t# hi32;" \
        : "=r"(_hi_)                        \
        : "K"(0x2803)                       \
    );                                      \
    _lo_ >>= n;                             \
    _hi_ <<= (32-n);                        \
    _lo_ | _hi_; })

#endif  // __aeon__

__inline
long
MUL16x16s15(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 15 );
}
__inline
long
MUL16x16s14(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 14 );
}
__inline
long
MUL16x16s12(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 12 );
}
__inline
long
MUL16x16s13(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 13 );
}
__inline
long
MUL16x16s09(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 9 );
}
__inline
long
MUL16x16s08(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 8 );
}
__inline
long
MUL16x16s10(
    short           sa,
    short           sb
)
{
    return ( ( (long)( (short)sa * (short)sb ) ) >> 10 );
}

/*---------------------------------------------------------------------------*/

__inline
long
MUL32x16s10(
    long            la,
    short           sb
)
{
#ifndef __aeon__
    register unsigned int    isNeg = 0;
    register unsigned short  ah;
    register unsigned short  al;
    register unsigned short  b;
    register unsigned long   ul;

    if ( la < 0 )
    {
        la = -la;
        isNeg = ( ~ isNeg );
    }
    ah = (unsigned short)( la >> 16 );
    al = (unsigned short)( la & 0x0000FFFF );

    if ( sb < 0 )
    {
        sb = (short)( - sb );
        isNeg = ( ~ isNeg );
    }
    b = sb;

    ul = ( ( (long)( ah * b ) ) << 6 ) + ( ( (long)( al * b ) ) >> 10 );

    return ( isNeg ? - ( (long)ul ) : (long)ul );
#else
    return (long)L_MULL_ASR(la,sb,10);
#endif
}

/*---------------------------------------------------------------------------*/

__inline
long
MUL32x16s12(
    long            la,
    short           sb
)
{
#ifndef __aeon__
    register unsigned int    isNeg = 0;
    register unsigned short  ah;
    register unsigned short  al;
    register unsigned short  b;
    register unsigned long   ul;

    if ( la < 0 )
    {
        la = -la;
        isNeg = ( ~ isNeg );
    }
    ah = (unsigned short)( la >> 16 );
    al = (unsigned short)( la & 0x0000FFFF );

    if ( sb < 0 )
    {
        sb = (short)( - sb );
        isNeg = ( ~ isNeg );
    }
    b = sb;

    ul = ( ( (long)( ah * b ) ) << 4 ) + ( ( (long)( al * b ) ) >> 12 );

    return ( isNeg ? - ( (long)ul ) : (long)ul );
#else
    return (long)L_MULL_ASR(la,sb,12);
#endif
}

/*---------------------------------------------------------------------------*/

__inline
long
MUL32x16s13(
    long            la,
    short           sb
)
{
#ifndef __aeon__
    register unsigned int    isNeg = 0;
    register unsigned short  ah;
    register unsigned short  al;
    register unsigned short  b;
    register unsigned long   ul;

    if ( la < 0 )
    {
        la = -la;
        isNeg = ( ~ isNeg );
    }
    ah = (unsigned short)( la >> 16 );
    al = (unsigned short)( la & 0x0000FFFF );

    if ( sb < 0 )
    {
        sb = (short)( - sb );
        isNeg = ( ~ isNeg );
    }
    b = sb;

    ul = ( ( (long)( ah * b ) ) << 3 ) + ( ( (long)( al * b ) ) >> 13 );

    return ( isNeg ? - ( (long)ul ) : (long)ul );
#else
    return (long)L_MULL_ASR(la,sb,13);
#endif
}

/*---------------------------------------------------------------------------*/

#ifndef __aeon__ //for B3 simulator
__inline long MUL32x16s14( long a, long b )
{
	//assert((short)b == b);
	return (long)(((long long)a*b) >> 14);
}
#else //for G1
#ifdef _MSC_VER
__inline long MUL32x16s14( long a, long b )
{
	//assert((short)b == b);
	return (long)(((__int64)a*b) >> 14);
}
#else
__inline
long
MUL32x16s14(
    long            la,
    short           sb
)
{
#ifndef __aeon__
    register unsigned int    isNeg = 0;
    register unsigned short  ah;
    register unsigned short  al;
    register unsigned short  b;
    register unsigned long   ul;

    if ( la < 0 )
    {
        la = -la;
        isNeg = ( ~ isNeg );
    }
    ah = (unsigned short)( la >> 16 );
    al = (unsigned short)( la & 0x0000FFFF );

    if ( sb < 0 )
    {
        sb = (short)( - sb );
		isNeg = ( ~ isNeg );
    }
    b = sb;

    ul = ( ( (long)( ah * b ) ) << 2 ) + ( ( (long)( al * b ) ) >> 14 );

    return ( isNeg ? - ( (long)ul ) : (long)ul );
#else
    return (long)L_MULL_ASR(la,sb,14);
#endif
}
#endif
/*---------------------------------------------------------------------------*/
#endif
__inline
long
MUL32x16s15(
    long            la,
    short           sb
)
{
#ifndef __aeon__
    register unsigned int    isNeg = 0;
    register unsigned short  ah;
    register unsigned short  al;
    register unsigned short  b;
    register unsigned long   ul;

    if ( la < 0 )
    {
        la = -la;
        isNeg = ( ~ isNeg );
    }
    ah = (unsigned short)( la >> 16 );
    al = (unsigned short)( la & 0x0000FFFF );

    if ( sb < 0 )
    {
        sb = (short)( - sb );
        isNeg = ( ~ isNeg );
    }
    b = sb;

    ul = ( ( (long)( ah * b ) ) << 1 ) + ( ( (long)( al * b ) ) >> 15 );

    return ( isNeg ? - ( (long)ul ) : (long)ul );
#else
    return (long)L_MULL_ASR(la,sb,15);
#endif
}

/*****************************************************************************/
#endif  /* ! defined( DEVICE_inst_h ) */
