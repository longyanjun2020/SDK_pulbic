#ifndef __HE_AAC_DECODER_SBR_MAC_INCLUDE_FILE__
#define __HE_AAC_DECODER_SBR_MAC_INCLUDE_FILE__


//#define DIV_R(A, B) (((int64_t)A << REAL_BITS_14)/B)
//#define DIV_C(A, B) (((int64_t)A << COEF_BITS)/B)
//#define DIV_29(A, B) (((int64_t)A << 29)/B)

//#define Q2_BITS 22
//#define Q2_PRECISION (1 << Q2_BITS)
//#define Q2_CONST(A) (((A) >= 0) ? ((int)((A)*(Q2_PRECISION)+0.5)) : ((int)((A)*(Q2_PRECISION)-0.5)))


//---------------------------------------
//---------------------------------------


//---------------------------------------
//---------------------------------------
#define SMULL_32_a0(A, B) AMULL_a0(A,B)
#define SMULL_32_a1(A, B) AMULL_a1(A,B)

//---------------------------------------
//---------------------------------------

//-------------------------
#define SMULWT_16_a0(A, B) AMULWT_a0(A,B)
#define SMULWB_16_a0(A, B) AMULWB_a0(A,B)
#define SMULWT_16_a1(A, B) AMULWT_a1(A,B)
#define SMULWB_16_a1(A, B) AMULWB_a1(A,B)
#define SMULWT_16_a2(A, B) AMULWT_a2(A,B)
#define SMULWB_16_a2(A, B) AMULWB_a2(A,B)
//-------------------------
#define SMLAWT_16_a0(A, B) AMACWT_a0(A,B)
#define SMLAWB_16_a0(A, B) AMACWB_a0(A,B)
#define SMLAWT_16_a1(A, B) AMACWT_a1(A,B)
#define SMLAWB_16_a1(A, B) AMACWB_a1(A,B)
//-------------------------
#define SMSBWT_16_a0(A, B) AMSBWT_a0(A,B)
#define SMSBWB_16_a0(A, B) AMSBWB_a0(A,B)

#define SMSBWT_16_a1(A, B) AMSBWT_a1(A,B)
#define SMSBWB_16_a1(A, B) AMSBWB_a1(A,B)



//-----------------------------------------------
//-----------------------------------------------
#define corr_mula_a0(r1, r2, r3, r4) \
{ \
   SMULWT_16_a0(r1, r2); \
   SMLAWT_16_a0(r3, r4); \
}
#define corr_mula_a1(r1, r2, r3, r4) \
{ \
   SMULWT_16_a1(r1, r2); \
   SMLAWT_16_a1(r3, r4); \
}

#define corr_muls_a0(r1, r2, r3, r4) \
{ \
   SMULWT_16_a0(r1, r2); \
   SMLAWT_16_a0(-r3, r4); \
}
#define corr_muls_a1(r1, r2, r3, r4) \
{ \
   SMULWT_16_a1(r1, r2); \
   SMLAWT_16_a1(-r3, r4); \
}

#define corr_mula3_a0(r1,  r2,  r3,  r4,  r5,  r6) \
{ \
   SMULWT_16_a0(r1, r2); \
   SMLAWT_16_a0(r3, r4); \
   SMLAWT_16_a0(r5, r6); \
}
#define corr_mula3_a1(r1,  r2,  r3,  r4,  r5,  r6) \
{ \
   SMULWT_16_a1(r1, r2); \
   SMLAWT_16_a1(r3, r4); \
   SMLAWT_16_a1(r5, r6); \
}

#define corr_mula4_a0( r1,  r2,  r3,  r4,  r5,  r6,  r7,  r8) \
{ \
   SMULWT_16_a0(r1, r2); \
   SMLAWT_16_a0(r3, r4); \
   SMLAWT_16_a0(r5, r6); \
   SMLAWT_16_a0(r7, r8); \
}
#define corr_mula4_a1( r1,  r2,  r3,  r4,  r5,  r6,  r7,  r8) \
{ \
   SMULWT_16_a1(r1, r2); \
   SMLAWT_16_a1(r3, r4); \
   SMLAWT_16_a1(r5, r6); \
   SMLAWT_16_a1(r7, r8); \
}

//-----------------------------------------------
//-----------------------------------------------
#define hfadj_mla_32_a0( r1,  r2,  r3,  r4) \
{ \
   SMLAWT_16_a0(r1, r2); \
   SMLAWT_16_a0(r3, r4); \
}



#ifdef PS_DEC

/* Complex multiplication */
#define ComplexMult(y1, y2, x1, x2, c) \
{ \
   AMULWT_a0(x1, c); \
   AMACWB_a0(x2, c); \
   AMULWT_a1(x2, c); \
   AMACWB_a1((-x1), c); \
   GET_MACR_a0(L_tmp,15); \
   y1 = L_tmp; \
   GET_MACR_a1(L_tmp,15); \
   y2 = L_tmp; \
}

#define ComplexMult1(y1, y2, x1, x2, x3, x4, c1, c2) \
{ \
   AMULWT_a0(x1, c1); \
   AMACWB_a0(x2, c1); \
   AMACWT_a0(x3, c2); \
   AMULWT_a1(x2, c1); \
   AMACWB_a1((-x1), c1); \
   AMACWT_a1(x4, c2); \
   GET_MACR_a0(L_tmp,15); \
   y1 = L_tmp; \
   GET_MACR_a1(L_tmp,15); \
   y2 = L_tmp; \
}



#endif
#endif



