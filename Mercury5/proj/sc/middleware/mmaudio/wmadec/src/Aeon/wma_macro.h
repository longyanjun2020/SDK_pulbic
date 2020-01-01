#ifndef __WMA_DECODER_MACRO_INCLUDE_FILE__
#define __WMA_DECODER_MACRO_INCLUDE_FILE__

#include "wma_mac.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))


#define CHECK_POWER_OF_TWO(x) ((((x)-1) & (x)) == 0)

#define MULT_HI32_SHIFT(a, b, bits) ((tWMA_I32)(((tWMA_I64)(a)*(tWMA_I64)(b))>>bits))


// Coefficents type (output of inverse quantization, transformed by DCT and overlapped/added)
// Range is +/- 2^26 with five fractional bits
#define ABS_COEF(a) wma_abs(a)

/*
static INLINE double WMA_Fabs(double f)
{
    if (f < 0.0f)
        return  (-(f));
    else
        return f;
}
*/

#   define COEF_FRAC_SCALE (1<<TRANSFORM_FRACT_BITS)
#   define COEF_FROM_FLOAT(flt) ((CoefType)((flt)*COEF_FRAC_SCALE))

#   define FRAC_FROM_RATIO(a, b, bits) (DIVI64BYU32((tWMA_I64)(a)<<(bits), (b)))

// bits-per-sample type

#   define WBPS_BITS 27
#   define WBPS(x) (WMA_U32)((x)*(1<<WBPS_BITS))
//#   define FLOAT_FROM_WBPS(x) ((Float)(x)/(1<<WBPS_BITS))

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion 

#   define BP2_FRAC_BITS 30
#   define BP2_FRAC_SCALE NF2BP2  //0x40000000
#   define BP2_FROM_FLOAT(flt) ((BP2Type)((flt)*BP2_FRAC_SCALE))
//#   define FLOAT_FROM_BP2(bp2) ((bp2)/((Float)BP2_FRAC_SCALE))
#   define BP2_FROM_BP1(bp1) ((bp1)>>1)

#   define MULT_ADD2_BP2(a,b,c,d) (MULT_HI_DWORD_DOWN(a,b) + MULT_HI_DWORD_DOWN(c,d))

// Fractional type with range -1.0 <= x < 1.0 used by DCT Trig Recurrsion

#   define BP1_FRAC_BITS 31
#   define BP1_FRAC_SCALE NF2BP1
#   define BP1_FROM_FLOAT(flt) ((BP1Type)(flt*BP1_FRAC_SCALE))

//#   define MULT_XBP1(a,b) ( ((XBP1Type)(((a)>>32))<<1) * ((XBP1Type)((b)>>32)) )

//#   define MAX40BITVAL ((tWMA_I64)0xfffffffff0)
#   define LOG2MAX40BITVAL (39)
//#   define MAX32BITVAL ((tWMA_I32)0x7ffffff0)
#   define LOG2MAX32BITVAL (30)


//#   define MAXINTVAL_FFT MAX32BITVAL
//#   define MAXINTVAL_FFT_LOG2 (LOG2MAX32BITVAL)  //LOG2(MAXINTVAL_FFT)
//#   define MULT_CBP2(a,b) MULT_HI_DWORD_DOWN(a,b)

#   ifdef FUSED_MUL_ADD
#       define MULT_ADD2_CBP2(a,b,c,d) MULT_ADD2_BP2(a,b,c,d)
#   else
#       define MULT_ADD2_CBP2(a,b,c,d) (MULT_HI_DWORD_DOWN(a,b) + MULT_HI_DWORD_DOWN(c,d))
#   endif


// Channel transform
#   define CH_FRAC_BITS (30)

//#ifdef HIGHBIT_CH
//#   define MAXINTVAL_CH MAX40BITVAL
//#   define MAXINTVAL_CH_LOG2 (LOG2MAX40BITVAL)   //LOG2_64(MAXINTVAL_CH)
//#   define MULT_CH(a,b) (multHi64(b, a, CH_FRAC_BITS))
//#   define MULT_CH_SQRT2(a) (multHi64((a), INT_SQRT2, INT_SQRT2_BITS))
//#else
//#   define MAXINTVAL_CH MAX32BITVAL
//#   define MAXINTVAL_CH_LOG2 (LOG2MAX32BITVAL)   //LOG2(MAXINTVAL_CH)
//#   define MULT_CH(a,b) MULT_HI32_SHIFT(b, a, CH_FRAC_BITS)
//#   define MULT_CH_SQRT2(a) MULT_HI32_SHIFT(a, INT_SQRT2, INT_SQRT2_BITS)
//#endif


// fix-point binary points conversion factors
// convert float or double to BP1 integer ( -1.0 <= x < +1.0 )
#define NF2BP1 0x7FFFFFFF
// convert float or double to BP2 integer ( -2.0 <= x < +2.0 )
#define NF2BP2 0x40000000

// Fraction is stored at 2^32 (BP0)
#define UBP0_FROM_FLOAT(x) ((WMA_U32)(x*4294967296.0F))

    // Some utility functions with obvious meaning
#   define DIV2(a) ((a)>>1)
#   define MUL2(a) ((a)<<1)



//****************************************************************************
//         Types, constants related to LPC.
//         Lot of these could be moved to constants.h or lpcConst.h for cleanliness
//****************************************************************************
#   define FRACT_BITS_LSP 30
#   define LSP_SCALE (1<<FRACT_BITS_LSP)
#   define LSP_FROM_FLOAT(a) ((LpType)((a)*LSP_SCALE))
#   define MULT_LSP(a,b) (tWMA_I32)((((tWMA_I64)(a))*((tWMA_I64)(b)))>>FRACT_BITS_LSP)
// MULT_LSP may be redefined by processor specific code in macros_cpu.h
//  LP, used for P, Q, and LPC values
#define FRACT_BITS_LP 27
#   define LP_SCALE (1<<FRACT_BITS_LP)
#   define LP_FROM_FLOAT(a) ((LpType)((a)*LP_SCALE))
#define FRACT_BITS_LP_SPEC 25
#   define LP_SPEC_SCALE (1<<FRACT_BITS_LP_SPEC)
#   define LP_SPEC_FROM_FLOAT(a) ((LpSpecType)((a)*LP_SPEC_SCALE))
#   define LP_SPEC_FROM_LP(a) ((LpSpecType)((a)>>(FRACT_BITS_LP-FRACT_BITS_LP_SPEC)))

//               We see weight factor values upto 64.53440857: 7 bits enough to cover integer part, 
//               leaving upto 25 bits for fraction. However, only 21 bits of fraction are generated 
//               upstream, making other 4 bits zero, even if used.

#define WEIGHTFACTOR_FRACT_BITS     21

#   define WEIGHT_FROM_FLOAT(a) ((WeightType)((a)*(1<<WEIGHTFACTOR_FRACT_BITS)))

// convert float or double to BP2 integer ( -2.0 <= x < +2.0 )
#define NF2BP2LPC 0x40000000

// Fractional Type with range -2.0 <= x < 2.0 used by FFT Trig Recurrsion 

#   define BP2LPC_FRAC_BITS 30
#   define BP2LPC_FRAC_SCALE NF2BP2LPC
#   define BP2LPC_FROM_FLOAT(flt) ((tWMA_I32)((flt)*BP2LPC_FRAC_SCALE))

#   define BP2LPC_FROM_BP1(bp1) ((bp1)>>1)
#   define BP2LPC_FROM_BP2(bp2) (bp2)

#   define MULT_BP2LPC(a,b) MULT_HI_DWORD_DOWN((a),(b))

// Fraction is stored at 2^32 (BP0)
#define UBP0_FROM_FLOAT_LPC(x) ((WMA_U32)(x*4294967296.0F))

#   define DIV2LPC(a) ((a)>>1)
#   define MUL2LPC(a) ((a)<<1)

//Trig Recursion Type
#if !defined(REF_64_TRIGLPC) && !defined(REF_EXACT_TRIGLPC)//32 bit trig recursion
#      define TR2LPC_TYPE tWMA_I32
#      define MULT_TR2LPCX  MULT_BP2LPCX
#      define TR2LPC_FROM_FLOAT(flt) (BP2LPC_FROM_FLOAT(flt))

#      define TR2LPC_FROM_BP2(bp2) (BP2LPC_FROM_BP2(bp2))
#      define TR2LPC_FROM_BP1(bp1) (BP2LPC_FROM_BP1(bp1))
#      define BP2LPC_FROM_TR2LPC(tr2) (tr2)
#else//FOR 64 bit trig recursion
#      define TR2LPC_TYPE XBP2LPCType
#      define MULT_TR2LPCX MULT_XBP2LPCX
#      define TR2LPC_FROM_FLOAT(flt) (XBP2LPC_FROM_FLOAT(flt))

#      define TR2LPC_FROM_BP2(bp2) (XBP2LPC_FROM_BP2(bp2))
#      define TR2LPC_FROM_BP1(bp1) (XBP2LPC_FROM_BP1(bp1))
#      define BP2LPC_FROM_TR2LPC(tr2) (BP2LPC_FROM_XBP2LPC(tr2))
#endif

    //****************************************************************************
    // quick and dirty rand generator, assuming low word multiply, only works for 
    // 32-bit machines see Numerical Recipes p.284.  
    // Note this is the referenced generator but the 24-bit or 16-bit versions can
    // be used for compliance comparisions with 24-bit or 16-bit implementations.
    //****************************************************************************
    static INLINE tWMA_I32 quickRand(tRandState* ptRandState)
    {
        const WMA_U32 a = 1664525;
        const WMA_U32 c = 1013904223;
        tWMA_I32 iTemp, iTemp1;
        //a*x + c has to be done with unsigned 32 bit
        ptRandState->uiRand =  a * ptRandState->uiRand + c;

        // uiRand values starting from a 0 seed are: 0x3c6ef35f, 0x47502932, 0xd1ccf6e9, 0xaaf95334, 0x6252e503, 0x9f2ec686, 0x57fe6c2d, ...

        // do not change the above - this reference generator has been extensively tested and has excellent randomness properties
        // a truism in the world of random number generator theory and practice is:
        // "any change, no matter how small, can and will change the properties of the generator and must be fully tested"
        // In case you don't know, it can easily take a person-month to fully test a generator.
    
        // Notwithstanding the above, it is fair to take a function of a random number to shape its range or distribution.
        // This we do below to give it a triangular distrbution between -2.5 and 2.5 to roughly approximate a Guassian distribution.

        // cast and shift to make the range (-1, 1) with Binary Point 3.
        iTemp = ((tWMA_I32)(ptRandState->uiRand)) >> 2; 

        // *1.25 to make the range (-1.25, 1.25) 
        iTemp += (iTemp>>2);
    
        // Difference of two random numbers gives a triangle distribution and a range of (-2.5, 2.5)
        // it also gives a serial correlation of -0.5 at lag 1.  But all the other lags have normally small correlations.
        iTemp1 = iTemp - ptRandState->iPrior;

        // Save first term of this difference for next time.
        ptRandState->iPrior = iTemp;

        //return -2.5 to 2.5 with Binary Point = 3 with a triangle distribution
        return iTemp1;
    }

    static INLINE void RandStateClear(tRandState* ptRandState) {
        ptRandState->iPrior = 0;
        ptRandState->uiRand = 0;
    }



// Bring in platform-independent macros
//#   define MULT_HI_DWORDN(a,b,N) (tWMA_I32)((((tWMA_I64)(a))*((tWMA_I64)(b)))>>(32-(N)))
//#   define MULT_HI_DWORDM(a,b,M) MULT_HI_DWORDN(a,b,M)

// Unsigned version of multiply
//#   define MULT_HI_UDWORD(a,b) (WMA_U32)((((tWMA_U64)(a))*((tWMA_U64)(b)))>>32)

#if 0
#ifdef FUSED_MUL_ADD
//  provide a more accurate reference path for implementations that have fused multiply-accumulate
#   define MULT_ADD2_HI_DWORD_DOWN(a,b,c,d) (tWMA_I32)(( (((tWMA_I64)(a))*((tWMA_I64)(b))) + (((tWMA_I64)(c))*((tWMA_I64)(d))) )>>30)
#   define MULT_ADD2_HI_DWORD(a,b,c,d) (tWMA_I32)(( (((tWMA_I64)(a))*((tWMA_I64)(b))) + (((tWMA_I64)(c))*((tWMA_I64)(d))) )>>32)
#   define MULT_ADD2_HI_DWORDN(a,b,c,d,N) (tWMA_I32)(( (((tWMA_I64)(a))*((tWMA_I64)(b))) + (((tWMA_I64)(c))*((tWMA_I64)(d))) )>>(32-(N)))
#   define MULT_ADD2_HI_UDWORD(a,b,c,d) (WMA_U32)(( (((tWMA_U64)(a))*((tWMA_U64)(b))) + (((tWMA_U64)(c))*((tWMA_U64)(d))) )>>32)
#else //FUSED_MUL_ADD
//  otherwise, truncate to 32-bits between each multiply.
#   define MULT_ADD2_HI_DWORD_DOWN(a,b,c,d) (MULT_HI_DWORD_DOWN(a,b) + MULT_HI_DWORD_DOWN(c,d))
#   define MULT_ADD2_HI_DWORD(a,b,c,d) (MULT_HI_DWORD(a,b) + MULT_HI_DWORD(c,d))
#   define MULT_ADD2_HI_DWORDN(a,b,c,d,N) ((MULT_HI_DWORDN(a,b,N) + MULT_HI_DWORDN(c,d,N))
#   define MULT_ADD2_HI_UDWORD(a,b,c,d) (MULT_HI_UDWORD(a,b) + MULT_HI_UDWORD(c,d))
#endif //FUSED_MUL_ADD
#endif

// Bring in platform-independent macros
#define MULT_HI_DWORD_DOWN(a,b) (tWMA_I32)((((tWMA_I64)(a))*((tWMA_I64)(b)))>>30)

#define MULT_HI_DWORD(a,b) (tWMA_I32)((((tWMA_I64)(a))*((tWMA_I64)(b)))>>32)

#define MULT_HI_UDWORD(a,b) (WMA_U32)((((tWMA_U64)(a))*((tWMA_U64)(b)))>>32)


static INLINE tWMA_I32 DIVI64BYU32(tWMA_I64 a, WMA_U32 b) {
    return (tWMA_I32)((a)/(b));
}

/*
static INLINE tWMA_I32   ROUNDF(float f)
{
    if (f < 0.0f)
        return (tWMA_I32) (f - 0.5f);
    else
        return (tWMA_I32) (f + 0.5f);
}
*/
static INLINE tWMA_I32   ROUNDINT(int f)
{
    if (f < 0)
        return (int) (f -4);
    else
        return (int) (f + 4);
}

//---------------------------------------------------------------------------
/*
static INLINE tWMA_I32   ROUNDD(double f)
{
// The following definition is added to suppress SH4 build warnings on SH4
// when -Qfast is used.
    if (f < 0.0f)
        return (tWMA_I32) (f - 0.5f);
    else
        return (tWMA_I32) (f + 0.5f);
}
*/

#define TRACEWMA_EXIT(wmaResult, action) \
{ \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                                goto exit;                                                      \
}

#define ASSERTWMA_EXIT(wmaResult, action) \
{ \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                goto exit;                                                      \
                            } \
}

#define CHECKWMA_EXIT(wmaResult) \
{ \
                            if (WMA_FAILED(wmaResult))                                          \
                                goto exit;                                                      \
}

#define TRACEWMA_RET(wmaResult, action) \
                            (wmaResult) = (action);                                             \
                            if (WMA_FAILED(wmaResult))                                          \
                            {                                                                   \
                                return (wmaResult);                                  \
                            } 

#define CHECKWMA_ALLOC(wmaResult, p) \
    if (NULL == p) \
    { \
        TRACEWMA_EXIT(wmaResult, WMA_E_OUTOFMEMORY); \
    }



    // FastFloat
    // FastFloat is a quick way of handling values that exceed tWMA_I32 range without incurring
    // the expense of floating point emulation on integer only platforms.
    // real value = iFraction * pow( 2, -iFracBits )
    // In debugger, iFraction*1.0F/(1<<iFracBits) works if 0<=iFracBits<31

    // Normalize a FastFloat

static INLINE  void Norm4FastFloat( FastFloat* pfflt )
    {   // use the faster Norm4FastFloatU when you know the value is positive
        register UInt uiF = wma_abs(pfflt->iFraction);
        register Int iFB = 0;

        if ( uiF == 0 )
        {
            pfflt->iFracBits = 0;
            return;
        }
        while ( uiF < 0x20000000 )
        {
            uiF <<= 2;
            iFB +=  2;
        }
        if ( uiF < 0x40000000 )
        {
            iFB +=  1;
        }
        pfflt->iFraction <<= iFB;
        pfflt->iFracBits  += iFB;
    }

static INLINE  void Norm4FastFloatU( FastFloat* pfflt )
    {   // same as above when we know value is positive (which we often do)
        register UInt uiF = pfflt->iFraction;
        register Int iFB = 0;
        while ( uiF < 0x20000000 )
        {
            uiF  <<= 2;
            iFB +=  2;
        }
        if ( uiF < 0x40000000 )
        {
            uiF  <<= 1;
            iFB +=  1;
        }
        pfflt->iFraction = uiF;
        pfflt->iFracBits += iFB;
    }


USE_MIPS32 static INLINE FastFloat ffltMultiply( FastFloat ffltA, FastFloat ffltB )
{
    FastFloat ffltP;

#ifdef __MIPS_4KE__
            SMULL_64_31(ffltP.iFraction, ffltA.iFraction, ffltB.iFraction);
#elif __wma_aeon_mac__
            GET_MACR_a0_31(ffltP.iFraction, ffltA.iFraction, ffltB.iFraction);
#else     
    ffltP.iFraction = MULT_HI( ffltA.iFraction, ffltB.iFraction );
#endif    
    ffltP.iFracBits = (ffltA.iFracBits + ffltB.iFracBits - 31);
    Norm4FastFloat( &ffltP );
    return ffltP;
}
#   define FASTFLOAT_MULT(a,b) ffltMultiply((a),(b))

static INLINE FastFloat ffltfltMultiply30(FastFloat ffltA, Int B)
{
    FastFloat ffltP;
    ffltP.iFracBits = ffltA.iFracBits;
#ifdef __MIPS_4KE__
    SMULL_64_30(ffltP.iFraction, ffltA.iFraction, B);
#elif __wma_aeon_mac__
    GET_MACR_a0_30(ffltP.iFraction, ffltA.iFraction, B);
#else
    ffltP.iFraction = (int)(((tWMA_I64)(ffltA.iFraction)*(tWMA_I64)(B)) >> 30);
#endif    
    Norm4FastFloat(&ffltP);

    return ffltP;
}

static INLINE  FastFloat ffltAdd( FastFloat ffltA, FastFloat ffltB )
{
    FastFloat ffltP;
    Int iShift;

    if (wma_abs(ffltA.iFraction) > 0x3FFFFFFF)
    {
        ffltA.iFraction >>= 1;
        ffltA.iFracBits--;
    }
    if (wma_abs(ffltB.iFraction) > 0x3FFFFFFF)
    {
        ffltB.iFraction >>= 1;
        ffltB.iFracBits--;
    }

    if ((ffltA.iFracBits >= ffltB.iFracBits && ffltB.iFraction != 0) ||
        ffltA.iFraction == 0)
    {
        iShift = ffltA.iFracBits-ffltB.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltB.iFracBits;
        ffltP.iFraction = ffltB.iFraction + (ffltA.iFraction>>iShift);
    }
    else
    {
        iShift = ffltB.iFracBits-ffltA.iFracBits;
        iShift = min(iShift, 31);
        ffltP.iFracBits = ffltA.iFracBits;
        ffltP.iFraction = ffltA.iFraction + (ffltB.iFraction>>iShift);
    }

    Norm4FastFloat(&ffltP);

    return ffltP;
}

#   define FASTFLOAT_ADD(a,b) ffltAdd((a),(b))

#ifndef FLT_MAX
#define FLT_MAX         3.402823466e+38F        /* max value */
#endif
#ifndef FLT_MIN
#define FLT_MIN         1.175494351e-38F        /* min positive value */
#endif

typedef struct temp_64
{
   unsigned int quotient;
   unsigned int remainder;
}temp_64;

static INLINE tWMA_I64 divide64_I64 (tWMA_I64 dividend, int divisor) //actually , this function is worked under unsigned int64
{
    temp_64 tmp; 
    unsigned int i, dividend32_hi, dividend32_lo, time_hi;
    tWMA_I64 ret_value;
    
    if(dividend ==0 || divisor ==0)
    return 0;
    
    dividend32_hi = (unsigned int) (dividend >> 32);
    dividend32_lo = (unsigned int) (dividend);
    
    tmp.quotient = dividend32_hi / divisor;
    tmp.remainder = dividend32_hi % divisor;
    time_hi = tmp.quotient;
    
    for (i=0 ; i < 32 ; i++)
    {
        tmp.remainder = (tmp.remainder<<1) + ((dividend32_lo & 0x80000000) >>31); //+ one low bit value;
        tmp.quotient  = (tmp.quotient<<1) + (tmp.remainder / divisor);
        tmp.remainder = tmp.remainder % divisor;
        dividend32_lo <<= 1;
    }
    
    ret_value = ( ((tWMA_I64) time_hi) <<32) | ((tWMA_I64) tmp.quotient);
    return ret_value;
}

#if 0
static INLINE FastFloat FastFloatFromFloat(Float flt) {
        FastFloat fflt;
        Float fltScale = (Float)(1<<(31-24));
        fflt.iFracBits = 24;

        // perform a bounds-check on the
        // incoming floating-point value.
        if( FLT_MAX < flt ) 
           flt = FLT_MAX;
        if( FLT_MIN > flt ) 
           flt = FLT_MIN;

        while( flt <= -fltScale || fltScale <= flt )
        {
            fflt.iFracBits -= 1;
            fltScale *= 2;
        }

        if( 0 > fflt.iFracBits )
            fflt.iFraction = (tWMA_I32)(flt/(1<<-fflt.iFracBits));
        else
            fflt.iFraction = (tWMA_I32)(flt*(1<<fflt.iFracBits));

        // sign check!
        Norm4FastFloat( &fflt );
        return fflt;
    }   
#endif
static INLINE tWMA_I32 LOG2(WMA_U32 i)
{   // returns n where n = log2(2^n) = log2(2^(n+1)-1)
    WMA_U32 iLog2 = 0;
    while ((i >> iLog2) > 1)
        iLog2++;

    return iLog2;
}


#   define FASTFLOAT_FROM_FLOAT(flt) FastFloatFromFloat(flt)
//#   define DOUBLE_FROM_FASTFLOAT(fflt) ((double)fflt.iFraction/(1<<fflt.iFracBits))


static INLINE FastFloat FastFloatFromU64(tWMA_U64 u64, Int cExp) 
    {
        FastFloat fflt;
        WMA_U32 uiMSF = (WMA_U32)(u64>>32);
        Int iExp = 0;
        if ( uiMSF==0 ) {
            iExp = 32;
            uiMSF = (WMA_U32)u64;
        }
        if (uiMSF==0) {
            fflt.iFracBits = 0;
            fflt.iFraction = 0;
            return fflt;
        }
        // normalize the most significant fractional part
        while( (uiMSF & 0xF0000000)==0 ) {
            iExp += 3;
            uiMSF <<= 3;
        }
        while( (uiMSF & 0xC0000000)==0 ) {
            iExp++;
            uiMSF <<= 1;
        }
        // number of fractional bits
        fflt.iFracBits = iExp+cExp-32;
#if defined(PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING)
        fflt.iFraction = (WMA_U32)((u64<<iExp)>>32);
#else
        fflt.iFraction = (iExp>32) ? (WMA_U32)(u64<<(iExp-32)) : (WMA_U32)(u64>>(32-iExp));
#endif
        return fflt;
    }   
#define FASTFLOAT_FROM_U64(u64,exp) FastFloatFromU64(u64,exp)


//#define DOUBLE_FROM_QUANTSTEPTYPE(qst) DOUBLE_FROM_FASTFLOAT(qst)


static INLINE WMA_U8 WMA_get_nHdrBits(CAudioObjectDecoder* hWMA)
{
    const CAudioObject *pau = hWMA->pau;
    if (pau->m_iVersion <= 2)
    {
        if (pau->m_fAllowSuperFrame)
            return (WMA_U8) (pau->m_cBitPackedFrameSize + NBITS_FRM_CNT + NBITS_PACKET_CNT + 3);
    }
		return 0;
}

#define COPY_KSDATAFORMAT_SUBTYPE_PCM(guid)\
     (guid)->Data1       = 0x01;\
     (guid)->Data2       = 0x00;\
     (guid)->Data3       = 0x10;\
     (guid)->Data4[0] = 0x80;\
     (guid)->Data4[1] = 0x00;\
     (guid)->Data4[2] = 0x00;\
     (guid)->Data4[3] = 0xaa;\
     (guid)->Data4[4] = 0x00;\
     (guid)->Data4[5] = 0x38;\
     (guid)->Data4[6] = 0x9b;\
     (guid)->Data4[7] = 0x71;


static INLINE void ibstrmFlush (CWMAInputBitStream* pibstrm) 
                        { pibstrm->m_dwBitsLeft -= (pibstrm->m_dwBitsLeft % 8); } 
static INLINE void ibstrmSuppressPacketLoss (CWMAInputBitStream *pibstrm) {pibstrm->m_fSuppressPacketLoss = WMAB_TRUE;}    
static INLINE UInt ibstrmBitsLeft (const CWMAInputBitStream* pibstrm) {return pibstrm->m_dwBitsLeft;}
static INLINE Int  ibstrmBufLen (const CWMAInputBitStream* pibstrm) {return pibstrm->m_cbBuflen;}
//static INLINE void ibstrmSetGetMoreData(CWMAInputBitStream *pibs, PFNGETMOREDATA pfnGetMoreData)
//                        { pibs->m_pfnGetMoreData = pfnGetMoreData; }
//static INLINE void ibstrmSetUserData(CWMAInputBitStream *pibs, void* pUser) 
//                        { pibs->m_pUser = pUser; }
static INLINE WMA_U32  ibstrmGetPacketHeader(CWMAInputBitStream *pibs) 
                        { return pibs->m_dwHeaderBuf; }
static INLINE void ibstrmSetPacketHeader(CWMAInputBitStream *pibs, WMA_U32 iVal) 
                        { pibs->m_dwHeaderBuf = iVal; }
static INLINE WMA_U32  ibstrmGetPacketHeaderT(CWMAInputBitStream *pibs) 
                        { return pibs->m_dwHeaderBufTemp; }
static INLINE void ibstrmSetPacketHeaderT(CWMAInputBitStream *pibs, WMA_U32 iVal) 
                        { pibs->m_dwHeaderBufTemp = iVal; }
static INLINE void ibstrmSetPrevPacketNum(CWMAInputBitStream *pibs, WMA_U32 iVal)
                        { pibs->m_iPrevPacketNum = iVal; }

static INLINE Int iResampleIndex( Int iRecon, const MaskResampleInfo MRI )
{  // return resampled linear index suitable for frame that was last updated with MaskQ
   // equvilent to iRecon shifted left or right by (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET)
   return ( (((iRecon) << MRI.iMaskResampleRatioPow) >> MASKQ_RESAMPLE_OFFSET) );
}

static INLINE Int iUnResampleIndex( Int iResampled, const MaskResampleInfo MRI )
{  // return the reverse of iResampleIndex()
   // that is, convert from resampled indexes of MaskQ or WeightFactor to natural index for the current frame
    if (MRI.iMaskResampleRatioPow > MASKQ_RESAMPLE_OFFSET){
      // Rounding for down shift 
      // Although V4 did not round when resampling, this inverse funtion needs to round ???
        return (iResampled + (1<<(MRI.iMaskResampleRatioPow-(MASKQ_RESAMPLE_OFFSET+1)))) >> (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET);
        // return iResampled >> (MRI.iMaskResampleRatioPow-MASKQ_RESAMPLE_OFFSET);
    } else {
        return iResampled << (MASKQ_RESAMPLE_OFFSET-MRI.iMaskResampleRatioPow);
    }
}


//*****************************************************************************************
// Look up (10^(1/16)) ^ iMaskQ
//*****************************************************************************************
static INLINE FastFloat ffltMaskPower10( Int iMaskQ )
{  // (10^(1/16)) ^ iMaskQ
   FastFloat fflt;
    if ( iMaskQ <= 0 )
   {
      if (iMaskQ <= -MASK_MINUS_POWER_TABLE_SIZE)
         iMaskQ = -(MASK_MINUS_POWER_TABLE_SIZE-1);

      fflt.iFraction = rgiMaskMinusPower10[ -iMaskQ ];   // with MASK_POWER_FRAC_BITS==28 fractional bits
      fflt.iFracBits = MASK_POWER_FRAC_BITS+(-iMaskQ>>2);

   }
   else
   {
      if (iMaskQ >= MASK_PLUS_POWER_TABLE_SIZE)
         iMaskQ = MASK_PLUS_POWER_TABLE_SIZE;

      fflt.iFraction = rgiMaskPlusPower10[ iMaskQ-1 ];   // with MASK_POWER_FRAC_BITS==28 fractional bits
      fflt.iFracBits = MASK_POWER_FRAC_BITS-(iMaskQ>>2);
   }
   return fflt;
}


//******************************************************************************************
//******************************************************************************************
// prvScanForNextBarkIndex scans for the next resampled bark index and then returns its unresampled linear index
//   iRecon and iHighLimit are linear indexes in the current frames natural scale.
//   iBarkResampled is the bark index in the resampled bark scale (appropriate for the frame when the MaskQ's were last updated)
//   rgiBarkIndex is the resampled bark index scale from that last updated MaskQ subframe

static INLINE Int prvScanForNextBarkIndex( const Int iRecon, Int* piBarkResampled, const int iHighLimit, 
                                const Int* const rgiBarkIndexResampled, const MaskResampleInfo MRI )
{   //Scan for the next resampled bark index
   Int iNextBarkIndex, iBarkResampled, iReconResampled;
   iReconResampled = iResampleIndex(iRecon, MRI);
    while ( iReconResampled >= rgiBarkIndexResampled [*piBarkResampled+1]) 
      ++(*piBarkResampled);
   iBarkResampled = *piBarkResampled;
   if ( iBarkResampled >= MRI.cValidBarkBandLatestUpdate )
   {
      return( MRI.cValidBarkBandLatestUpdate );
   }
   iNextBarkIndex = iUnResampleIndex( rgiBarkIndexResampled [iBarkResampled + 1], MRI );
    if (iNextBarkIndex > iHighLimit) 
      iNextBarkIndex = iHighLimit;
   return iNextBarkIndex;
}


//static const tWMA_I32 cDitherFactorMR = 0x28F5C28F;     // BARK 0.02 * 2^35 (but I am not sure how to derive the 35)
#define cDitherFactorMR ((int)0x28F5C28F)

//****************************************************************************
// Normalize a dynamically scaled unsigned int 
//****************************************************************************
static INLINE void NormUInt( UInt* puiValue, Int* pcFracBits, const UInt uiTarget ){
    const UInt uiTarget2 = uiTarget>>1;
    register UInt uiV = *puiValue;
    register Int cFB = *pcFracBits;
  
    if (uiV == 0) return; // useful if asserts are disabled

    while ( uiV < uiTarget2 )
    {
        uiV <<= 2;        
        cFB += 2;
    }
    if ( uiV < uiTarget )
    {
        uiV <<= 1;        
        cFB += 1;
    }
    *puiValue = uiV;
    *pcFracBits = cFB;
}

//****************************************************************************
// Align a dynamically scaled int to a particular binary point position
//****************************************************************************
static INLINE Int Align2FracBits( const Int iValue, const Int cFracBits, const Int cAlignFracBits )
{
    const Int iShift = cFracBits-cAlignFracBits;

    if (iShift < 0) {
        return (iValue << -iShift);
    } else if (iShift < 32) { 
        return (iValue >> iShift);
    } else {
        return 0;
    }
}



#ifndef FFLT_SQRT_RATIO
  static  INLINE FastFloat ffltSqrtRatio( FastFloat fflt1, FastFloat fflt2 )
    {
            tWMA_U64 u64Ratio;
            //tWMA_U64 test_val; 
            FastFloat fflt;
            Int iMSF8;
            WMA_U32 uiMSF;
            WMA_U32 uiFrac1;
            Int iExp = 0;
            utemp_64 tmp;
#if defined (__MIPS_4KE__) || (__wma_aeon_mac__)        
    WMA_U32 dst1;
#endif
                         
            if ( fflt2.iFraction==0 ) {

                fflt.iFraction = 0x7FFFFFFF;
                fflt.iFracBits = 0;
                return fflt;
            }
            //// fflt1.iFraction*0.5F/(1<<(fflt1.iFracBits-1))
            //// fflt2.iFraction*0.5F/(1<<(fflt2.iFracBits-1))
            //u64Ratio = (((tWMA_U64)fflt1.iFraction)<<32)/fflt2.iFraction;  //divdi3
            u64Ratio = (tWMA_U64) divide64_I64( (((tWMA_I64)fflt1.iFraction)<<32), fflt2.iFraction);
            //if (test_val != u64Ratio)
            //printf("Error ...................\n"); 
            
            uiMSF = (WMA_U32)(u64Ratio>>32);
            if ( uiMSF==0 ) {
                iExp = 32;
                uiMSF = (WMA_U32)u64Ratio;
            }

            // normalize the most significant fractional part
            while( (uiMSF & 0xF0000000)==0 ) {
                iExp += 4;
                uiMSF <<= 4;
            }
            while( (uiMSF & 0x80000000)==0 ) {
                iExp++;
                uiMSF <<= 1;
            }
            // discard the most significant one bit (it's presence is built into g_InvQuadRootFraction)
            iExp++;
            // get all 32 bits from source
            
#           if defined(PLATFORM_OPTIMIZE_MINIMIZE_BRANCHING)
                uiMSF = (WMA_U32)((u64Ratio<<iExp)>>32);
#           else
                //uiMSF = (iExp>32) ? (WMA_U32)(u64Ratio<<(iExp-32)) : (WMA_U32)(u64Ratio>>(32-iExp));
                if (iExp>32)
                uiMSF = (WMA_U32)(u64Ratio<<(iExp-32)); 
                else
                {
                   tmp.hi = (unsigned int) (u64Ratio >>32);
                   tmp.lo = (unsigned int) (u64Ratio & 0x00000000ffffffff);
                   tmp.hi = tmp.hi << (iExp);
                   tmp.lo = tmp.lo >> (32-iExp);
                   uiMSF = tmp.hi | tmp.lo;
                }
#           endif

            // split into top SQRT_FRACTION_TABLE_LOG2_SIZE==8 bits for fractional lookup and bottom bits for interpolation
            iMSF8 = uiMSF>>(32-SQRT_FRACTION_TABLE_LOG2_SIZE);
            uiMSF <<= SQRT_FRACTION_TABLE_LOG2_SIZE;
            // lookup and interpolate
            uiFrac1  = g_SqrtFraction[iMSF8++];   // BP2         
            
#ifdef __MIPS_4KE__
    USMULL_high(dst1, uiMSF, g_SqrtFraction[iMSF8] - uiFrac1 );
    uiFrac1 += dst1;
#elif __wma_aeon_mac__
    GET_MACR_a0_32U(dst1, uiMSF,  g_SqrtFraction[iMSF8] - uiFrac1);
    uiFrac1 += dst1;
#else              
            uiFrac1 += MULT_HI_UDWORD( uiMSF,  g_SqrtFraction[iMSF8] - uiFrac1 );
#endif      
            // adjust by sqrt(1/2) if expoenent is odd
            if ( (iExp+fflt1.iFracBits-fflt2.iFracBits) & 1 ) {
                // multiply by 1/sqrt(2) and adjust fracbits by 1/2
#ifdef __MIPS_4KE__
    USMULL_high(uiFrac1, uiFrac1, UBP0_FROM_FLOAT(0.70710678118654752440084436210485));
#elif __wma_aeon_mac__
    GET_MACR_a0_32U(uiFrac1, uiFrac1, UBP0_FROM_FLOAT(0.70710678118654752440084436210485));
#else                  
                uiFrac1 = MULT_HI_UDWORD( uiFrac1, UBP0_FROM_FLOAT(0.70710678118654752440084436210485) );
#endif                        
                fflt.iFracBits = ((fflt1.iFracBits-(fflt2.iFracBits+1))>>1)+(iExp-3);
            } else {
                fflt.iFracBits = ((fflt1.iFracBits-fflt2.iFracBits)>>1)+(iExp-3);
            }
            fflt.iFraction = uiFrac1>>1;    // make sure sign is positive
            //// fflt.iFraction*0.5F/(1<<(fflt.iFracBits-1))
            Norm4FastFloatU( &fflt );
            return fflt;
    }
#   define FFLT_SQRT_RATIO(fflt1,fflt2) ffltSqrtRatio(fflt1,fflt2)
#endif

/*
#define DOUBLE(fPad2X, x) \
((fPad2X) ? ((x)<<pau->m_iAdjustSizeShiftFactor) : (x))
#define AU_HALF_OR_DOUBLE(fHalf, fPad2X, x) \
((fHalf) ? ((x)>>pau->m_iAdjustSizeShiftFactor) : ((fPad2X) ? ((x)<<pau->m_iAdjustSizeShiftFactor) : (x)))
*/

static INLINE tWMA_I32 *prvAdvancePCMPointer(const tWMA_I32 *pCurrentPos,
                                const Int nBytePerSample,
                                const Int iOffset)
{
    return (tWMA_I32 *) (((WMA_U8*) pCurrentPos) + (nBytePerSample * iOffset));
}

#define MULT_QUANT(iLevel,ffltQuantizer) MULT_HI(((iLevel)<<16),ffltQuantizer.iFraction)

//#define MAXINTVAL_IQ MAX32BITVAL
//#define MAXINTVAL_IQ_LOG2 (LOG2MAX32BITVAL)   //LOG2(MAXINTVAL_IQ)

#define SCALE_COEF_RECON(iCR) (iShift<0) ? (iCR)<<-iShift : (iCR)>>iShift
#define MAKE_MASK_FOR_SCALING(iFB) iShift=iFB+(16-31-TRANSFORM_FRACT_BITS)


// ===========================================================
/*
static INLINE
void prvSaveCurChannels(CAudioObject *pau)
{
    if (pau)
    {
        pau->m_cSaveChannel     = pau->m_cChannel;
        pau->m_nSaveChannelMask = pau->m_nChannelMask;
    }
}
*/
/*
static INLINE
void prvRestoreCurChannels(CAudioObject *pau)
{
    if (pau)
    {
        pau->m_cChannel     = pau->m_cSaveChannel;
        pau->m_nChannelMask = pau->m_nSaveChannelMask;
    }
}
*/
/*
static INLINE
void prvSetOrigChannels(CAudioObject *pau)
{
    if (pau)
    {
        pau->m_cChannel     = pau->m_cOrigChannel;
        pau->m_nChannelMask = pau->m_nOrigChannelMask;
    }
}
*/
/*
static INLINE
void prvSetCodedChannels(CAudioObject *pau)
{
    if (pau)
    {
        pau->m_cChannel     = pau->m_cCodedChannel;
        pau->m_nChannelMask = pau->m_nCodedChannelMask;
    }
}
*/
#endif

