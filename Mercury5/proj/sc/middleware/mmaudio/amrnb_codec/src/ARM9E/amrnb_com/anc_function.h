#ifndef __AMRNB_COMMON_FUNCTION_INCLUDE_FILE__
#define __AMRNB_COMMON_FUNCTION_INCLUDE_FILE__



void Log2 (
    Word32 L_x,        /* (i) : input value                                 */
    Word32 *exponent,  /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word32 *fraction   /* (o) : Fractional part of Log2. (range: 0<=val<1)*/
);


Word32 Inv_sqrt (      /* (o) : output value   (range: 0<=val<1)            */
    Word32 L_x           /* (i) : input value    (range: 0<=val<=7fffffff)    */
);



Word32 Pow2 (          /* (o) : result       (range: 0<=val<=0x7fffffff)    */
    Word16 exponent,   /* (i) : Integer part.      (range: 0<=val<=30)      */
    Word16 fraction    /* (i) : Fractional part.  (range: 0.0<=val<1.0)     */
);


void gc_pred_reset (gc_predState *st);



Word32 sqrt_l_exp (/* o : output value,                        Q31 */
    Word32 L_x,    /* i : input value,                         Q31 */
    Word32 *exp    /* o : right shift to be applied to result, Q0  */
);



void Log2_norm (
    Word32 L_x,         /* (i) : input value (normalized)                    */
    Word32 exp,         /* (i) : norm_l (L_x)                                */
    Word32 *exponent,   /* (o) : Integer part of Log2.   (range: 0<=val<=30) */
    Word32 *fraction    /* (o) : Fractional part of Log2. (range: 0<=val<1)  */
);
 


 
#endif

