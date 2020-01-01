#ifndef __HE_AAC_DECODER_SBR_MAC_INCLUDE_FILE__
#define __HE_AAC_DECODER_SBR_MAC_INCLUDE_FILE__


//---------------------------------------
//---------------------------------------
#ifdef __ARM9E_GNU__
#define CLZ(A,cz) \
{ \
   __asm volatile("clz %0, %1": "=r"(cz): "r"(A)); \
} 
#elif defined(__ARM9E_RVDS22__)
#define CLZ(A,cz) \
{ \
   __asm { \
      clz   cz,A; \
   } \
} 
#elif defined(__ARM9E_WINCE__)
#define CLZ(A,cz) \
{ \
   cz = _CountLeadingZeros(A); \
} 
#else
#define CLZ(A,cz) \
{ \
   int _a1_ = (A); \
   if(_a1_==0) \
     cz = 32; \
   else \
   { \
      cz=0; \
      while(_a1_>0) \
      { \
         cz++; \
         _a1_ <<= 1;\
      } \
   } \
} 
#endif
//---------------------------------------
//---------------------------------------
#ifdef __ARM9E_GNU__
#define SMULL_15(A, B, C) \
{ \
   int hi; \
   int b1 = (B); \
   asm volatile("smull %0, %1, %2, %3": "=r"(C),"=r"(hi): "r"(A), "r"(b1)); \   
   asm volatile("mov %0, %1, lsr %2": "=r"(C): "r"(C), "i"(15)); \
   asm volatile("orr %0, %1, %2, lsl %3": "=r"(C): "r"(C), "r"(hi),"i"(17)); \   
} 

#elif defined(__ARM9E_RVDS22__)
#define SMULL_15(A, B, C) \
{ \
   int hi; \
   int b1 = (B); \
   __asm { \
      smull   C,hi,A,b1; \
      mov     C,C,lsr 15; \
      orr     C,C,hi,lsl 17; \
   } \
} 

#elif defined(__ARM9E_WINCE__)
#define SMULL_15(A, B, C) \
{ \
   C = (int)(((int64_t)(A)*(int64_t)(B))>>15); \
} 
#else
//64<=32*32
#define SMULL_15(A, B, C) \
{ \
   C = (int)(((int64_t)(A)*(int64_t)(B))>>15); \
}
#endif

#define SMULL_32(A, B, C) \
{ \
   arm9e_smull_hi(C,A,B); \
}
//---------------------------------------
//---------------------------------------
#define SMULWT_16(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwt(C,_a1_,_b1_); \
} 

#define SMULWB_16(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwb(C,_a1_,_b1_); \
} 
#if 1
#define SMLAWT_16(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smlawt(C,_a1_,_b1_,C); \
}

#define SMLAWB_16(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smlawb(C,_a1_,_b1_,C); \
} 
#else

#define SMLAWT_16(A, B, C) \
{ \
   arm9e_dsp_smlawt(C,A,B,C); \
}

#define SMLAWB_16(A, B, C) \
{ \
   arm9e_dsp_smlawb(C,A,B,C); \
} 
#endif
#define SMULWT_15(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwt(C,_a1_,_b1_); \
   arm9e_dsp_qadd(C,C,C); \
} 
#define SMULWB_15(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwb(C,_a1_,_b1_); \
   arm9e_dsp_qadd(C,C,C); \
} 
#define SMULWB_14(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwb(C,_a1_,_b1_); \
   C = C << 2; \
} 
#define SMULWT_12(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwt(C,_a1_,_b1_); \
   C = C << 4; \
} 

#define SMULWB_12a(A, B, C) \
{ \
   arm9e_dsp_smulwb(C,A,B); \
   C = C << 4; \
} 

#define SMULWB_12(A, B, C) \
{ \
   int _a1_ = (A); \
   int _b1_ = (B); \
   arm9e_dsp_smulwb(C,_a1_,_b1_); \
   C = C << 4; \
} 
#define SMLAWT4_16(A, B, C, D) \
{ \
   int _c1_ = (C); \
   arm9e_dsp_smlawt(D,A,B,_c1_); \
}
#define SMLAWB4_16(A, B, C, D) \
{ \
   int _c1_ = (C); \
   arm9e_dsp_smlawb(D,A,B,_c1_); \
}

//-----------------------------------------------
//-----------------------------------------------

#define MUT_MAL_t(x, y, dst) \
{ \
   int _x1_ = (x); \
   arm9e_dsp_smlawt(dst,_x1_,y,dst); \
} 


#define MUT_MUL_b(x, y, dst) arm9e_dsp_smulwb(dst,x,y); 

#define MUT_MLZ(dst) arm9e_dsp_qadd(dst,dst,dst)

//-----------------------------------------------
//-----------------------------------------------
#if defined(__ARM9E_RVDS22__) || defined(__AM9E_GNU__)
#pragma arm
#endif
static INLINE int corr_mla(int acc, int r1, int r2, int r3, int r4)
{
   int tmp = acc;
   SMLAWT_16(r1, r2, tmp);
   SMLAWT_16(r3, r4, tmp);
   return (int)(tmp);
}

static INLINE int corr_mula(int r1, int r2, int r3, int r4)
{
   int tmp;
   SMULWT_16(r1, r2, tmp);
   SMLAWT_16(r3, r4, tmp);
   return (int)(tmp);
}

static INLINE int corr_mula3(int r1, int r2, int r3, int r4, int r5, int r6)
{
   int tmp;
   SMULWT_16(r1, r2, tmp);
   SMLAWT_16(r3, r4, tmp);
   SMLAWT_16(r5, r6, tmp);
   return (int)(tmp);
}

static INLINE int corr_mula4(int r1, int r2, int r3, int r4, int r5, int r6, int r7, int r8)
{
   int tmp;
   SMULWT_16(r1, r2, tmp);
   SMLAWT_16(r3, r4, tmp);
   SMLAWT_16(r5, r6, tmp);
   SMLAWT_16(r7, r8, tmp);
   return (int)(tmp);
}


//-----------------------------------------------
//-----------------------------------------------
static INLINE int hfadj_mla_32(int r1, int r2, int r3, int r4, int prev)
{
   int tmp = prev;
   SMLAWT_16(r1, r2, tmp);
   SMLAWT_16(r3, r4, tmp);
   return (int)(tmp);
}
#if defined(__ARM9E_RVDS22__) || defined(__AM9E_GNU__)
#pragma thumb
#endif


#ifdef PS_DEC

#if defined(__ARM9E_RVDS22__) || defined(__AM9E_GNU__)
#pragma arm
#endif
static INLINE int ps_mula(int r1, int r2, int c)
{
   int tmp;
   arm9e_dsp_smulwt(tmp, r1, c);
   arm9e_dsp_smlawb(tmp, r2, c, tmp);
   return (int)(tmp);
}

static INLINE int ps_mula_1(int r1, int r2, int aac)
{
   int tmp = aac;
   arm9e_dsp_smlawt(tmp, r1, r1, tmp);
   arm9e_dsp_smlawt(tmp, r2, r2, tmp);
   return (int)(tmp);
}

static INLINE int ps_mula3(int r1, int r2, int r3, int c1, int c2)
{
   int tmp;
   arm9e_dsp_smulwt(tmp, r1, c1);
   arm9e_dsp_smlawb(tmp, r2, c1, tmp);
   arm9e_dsp_smlawt(tmp, r3, c2, tmp);
   return (int)(tmp);
}

static INLINE int ps_mula_32(int r1, int r2, int r3, int r4)
{
   int tmp;
   arm9e_dsp_smulwt(tmp, r1, r2);
   arm9e_dsp_smlawt(tmp, r3, r4, tmp);
   return tmp;
}


static INLINE int ps_mla_32(int r1, int r2, int r3, int r4, int prev)
{
   int tmp = prev;
   arm9e_dsp_smlawt(tmp, r1, r2, tmp);
   arm9e_dsp_smlawt(tmp, r3, r4, tmp);
   return tmp;
}


/* Complex multiplication */
static INLINE void ComplexMult(int *y1, int *y2,
    int x1, int x2, int c)
{
   *y1 = ps_mula(x1,  x2, c)<<1;
   *y2 = ps_mula(x2, -x1, c)<<1;
}

static INLINE void ComplexMult1(int *y1, int *y2,
    int x1, int x2, int x3, int x4, int c1, int c2)
{
   *y1 = ps_mula3(x1,  x2, x3, c1, c2)<<1;
   *y2 = ps_mula3(x2, -x1, x4, c1, c2)<<1;
}

#if defined(__ARM9E_RVDS22__) || defined(__AM9E_GNU__)
#pragma thumb
#endif

#endif
#endif



