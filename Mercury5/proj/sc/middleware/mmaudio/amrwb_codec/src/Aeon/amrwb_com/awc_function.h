#ifndef __AMR_WB_COMMON_FUNCTION_INCLUDE_FILE__
#define __AMR_WB_COMMON_FUNCTION_INCLUDE_FILE__

void awb_Set_zero(
     Word16 x[],                           /* (o)    : vector to clear     */
     Word16 L                              /* (i)    : length of vector    */
);
Word16 D_UTIL_norm_s (Word16 var1);
void Copy16(Word16 x[],Word16 y[]);
void Copy30(Word16 *src, Word16 *dst);
Word16 D_UTIL_norm_l (Word32 L_var1);
void Reorder_isf(
     Word16 * isf,           /* (i/o) Q15: ISF in the frequency domain (0..0.5) */
     Word16 min_dist,        /* (i) Q15  : minimum distance to keep             */
     Word16 n                /* (i)      : number of ISF                        */
);
Word32 D_UTIL_Pow2(                               /* (o) Q0  : result       (range: 0<=val<=0x7fffffff) */
     Word16 exponant,                      /* (i) Q0  : Integer part.      (range: 0<=val<=30)   */
     Word16 fraction                       /* (i) Q15 : Fractionnal part.  (range: 0.0<=val<1.0) */
);
void D_UTIL_Isqrt_n(
     Word32 * frac,                        /* (i/o) Q31: normalized value (1.0 < frac <= 0.5) */
     Word16 * exp                          /* (i/o)    : exponent (value = frac x 2^exponent) */
);

#endif


