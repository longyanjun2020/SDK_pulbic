#ifndef ARM9E_WM6_H
#define ARM9E_WM6_H

static __inline int16 extract_h(int32 x)
{
    return (int16) (x >> 16);
}

static __inline int16 extract_l(int32 x)
{
    return (int16) x;
}

/*static __inline int16 UCLIPI(int16 x, int16 c)
{
    if (x < 0) return 0;
    if (x > c) return c;
    return x;
}*/

static __inline int32 DUALUCLIPI(int32 x, int16 c) 
{
    int16 hi, lo;
    int32 result;
    hi = extract_h(x);
    lo = extract_l(x);
    hi = UCLIPI(hi, c);
    lo = UCLIPI(lo, c);
    //__asm {
    //    orr result, lo, hi, lsl #16;    
    //}
    result = lo + (hi<<16);
    return result;       
}

static __inline int32 DSPIDUALSUB(int32 x, int32 y)
{
    int32 hi_x, hi_y, lo_x, lo_y;
    int16 tmp1, tmp2;
    int32 result, hi, lo;
    hi_x = (int32)(x>>16);
    hi_y = (int32)(y>>16);
    lo_x = (int32)((int16)x);
    lo_y = (int32)((int16)y);
    //__asm {
    //    qsub hi, hi_x, hi_y;
    //    qsub lo, lo_x, lo_y;        
    //}
    hi = _DSubSatInt(hi_x, hi_y);
    lo = _DSubSatInt(lo_x, lo_y);
    result = (hi<<16) | (lo&0xffff);
    return result;
}

static __inline int32 ICLIPI(int32 x, int16 c) 
{
    if (x < (-c-1)) return (-c-1);
    if (x > c) return c;
    return x;
}

static __inline int32 UCLIPI(int32 x, int16 c) 
{
#if 1
    if (x < 0) x = 0;
    if (x > c) x = c;
#else
    if (x < 0) return 0;
    if (x > c) return c;
#endif
    return x;
}

static __inline int32 IABS(int32 x) 
{
	if (x >= 0)
		return x;
	else
		return -x;
}

#define CLIP3 clip3
static __inline int32 clip3(int32 min, int32 max, int32 x) 
{
    if (x < (min)) 
        return (min);
    else if (x > (max)) 
        return (max);
    else
        return x;
}

//maybe "_CountLeadingZeros"
#define CLSAME(codoword, pattern) CLZ((codeword) ^ (pattern))

#define SMULTT(a, b)    _SmulHi_SW_SL(a, b)
#define SMULBB(a, b)    _SmulLo_SW_SL(a, b)
#define SMULTB(a, b)    _SmulHiLo_SW_SL(a, b)
#define SMULBT(a, b)    _SmulLoHi_SW_SL(a, b)

#define SMLATT(x, y, a) _SmulAddHi_SW_SL(a, x, y)
#define SMLABB(x, y, a) _SmulAddLo_SW_SL(a, x, y)
#define SMLATB(x, y, a) _SmulAddHiLo_SW_SL(a, x, y)
#define SMLABT(x, y, a) _SmulAddLoHi_SW_SL(a, x, y)

#define IFIR16(a, b)    SMLABB((a), (b), SMULTT((a), (b)))

#define LSHIFTR32(a, b) ((a) >> (b))
#define LSHIFTL32(a, b) ((a) << (b))

#endif
