#ifndef __AMR_WB_COMMON_MAC_INCLUDE_FILE__
#define __AMR_WB_COMMON_MAC_INCLUDE_FILE__


#ifdef __aeon__
#define AMACR_KEEP   0x10   // clear
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift
#endif


#ifdef __aeon__
#define ACLZ_32(ain,aout) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
   aout = 31-aout; \
} 
#define ACLZ_16(ain,aout) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
   aout = 15-aout; \
} 
//ACLZ:     : ,0(negative) , 1, 2,   ,31,          ,32(0)
//aeon l.fl1: 32(0x80000000),31,30,...,1(0x00000001),0(0x00000000)
#define ACLZ(aout,ain) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
   aout = 32-aout; \
} 

#define AFL1(aout,ain) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
} 
#else

#define ACLZ(aout,ain) \
{ \
   if(ain==0) \
      aout = 32; \
   else if(ain < 0) \
      aout = 0; \
   else \
   { \
      for(aout = 0; ain < (unsigned int) 0x80000000; aout++) \
      { \
         ain <<= 1; \
      } \
   } \
}

#define AFL1(aout,ain) \
{ \
   aout = 32; \
   do { \
      if ((int)ain<0) \
          break; \
      aout--; \
      ain <<= 1; \
   }while (aout); \
} 

#define ACLZ_32(ain,aout) \
{ \
   aout = 0; \
   if(ain < 0x00008000L) \
   { \
      ain <<= 16; \
      aout = 16; \
   } \
   while(ain < 0x40000000L) \
   { \
      ain <<= 1; \
      aout++; \
   } \
}


#define ACLZ_16(ain,aout) \
{ \
   aout = 0; \
   if(ain < 0x80) \
   { \
      ain <<= 8; \
      aout = 8; \
   } \
   while(ain < 0x4000) \
   { \
      ain <<= 1; \
      aout++; \
   } \
}



#endif

#ifdef __aeon__
#ifdef __AEONR2__
#define AMULL(Dst,A,B) \
{ \
   asm volatile("l.mul %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
#else
#define AMULL(Dst,A,B) \
{ \
   asm volatile("l.amull %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
#endif
#else
#define AMULL(Dst,A,B) \
{ \
   Dst = (int)((int64_t)(A)*(int64_t)(B)); \
}
#endif


#ifdef __aeon__

#define CLR_MACR_a0 \
{ \
   asm volatile("l.amul a0,r0,r0"); \
}

#define GET_MACR_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}
#define GET_MACR_RND_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#ifdef __AEONR2__
#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a0_low_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}

#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#else
#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a0_low_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2809)); \
}

#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280a)); \
}
#endif


#define AMULL_a0(a,b) \
{ \
   asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMACL_a0(A,B) \
{ \
   asm volatile("l.amac a0,%0,%1"::"r"(A),"r"(B)); \
}

#define AMSBL_a0(A,B) \
{ \
   asm volatile("l.amsb a0,%0,%1"::"r"(A),"r"(B)); \
}
#else
#define CLR_MACR_a0 \
{ \
   macr_a0 = 0; \
}

#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(macr_a0>>n); \
}


#define GET_MACR_RND_a0(dst,n) \
{ \
   dst = (int)((macr_a0+(1<<(n-1)))>>n); \
}

#define GET_MACR_a0_low(dst) \
{ \
   dst = (int)(macr_a0); \
}

#define GET_MACR_a0_high(dst) \
{ \
   dst = (int)(macr_a0>>32); \
}

#define GET_MACR_RND_a0_nop GET_MACR_RND_a0
#define GET_MACR_a0_low_nop GET_MACR_a0_low

#define GET_MACR_a0_nop GET_MACR_a0

#define AMULL_a0(A,B) \
{ \
   macr_a0 = ((int64_t)(A)*(int64_t)(B)); \
}

#define AMACL_a0(A,B) \
{ \
   macr_a0 += ((int64_t)(A)*(int64_t)(B)); \
}

#define AMSBL_a0(A,B) \
{ \
   macr_a0 -= ((int64_t)(A)*(int64_t)(B)); \
}

#endif

#ifdef __aeon__
//-----------------------------------------------
//-----------------------------------------------
#define CLR_MACR_a1 \
{ \
   asm volatile("l.amul a1,r0,r0"); \
}


#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_RND_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#ifdef __AEONR2__
#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1_low_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280b)); \
}

#define GET_MACR_a1_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280c)); \
}

#else
#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1_low_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280b)); \
}

#define GET_MACR_a1_high(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280c)); \
}

#endif



#define AMULL_a1(a,b) \
{ \
   asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b)); \
}

#define AMACL_a1(A,B) \
{ \
   asm volatile("l.amac a1,%0,%1"::"r"(A),"r"(B)); \
}

#define AMSBL_a1(A,B) \
{ \
   asm volatile("l.amsb a1,%0,%1"::"r"(A),"r"(B)); \
}



#define AMULWB_a0(a,b) \
{ \
   asm volatile("l.amul_lh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWT_a0(a,b) \
{ \
   asm volatile("l.amul_hh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWB_a1(a,b) \
{ \
   asm volatile("l.amul_lh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWT_a1(a,b) \
{ \
   asm volatile("l.amul_hh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWB_a0(a,b) \
{ \
   asm volatile("l.amac_lh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWT_a0(a,b) \
{ \
   asm volatile("l.amac_hh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMACWB_a1(a,b) \
{ \
   asm volatile("l.amac_lh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWT_a1(a,b) \
{ \
   asm volatile("l.amac_hh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWB_a0(a,b) \
{ \
   asm volatile("l.amsb_lh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWT_a0(a,b) \
{ \
   asm volatile("l.amsb_hh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMSBWB_a1(a,b) \
{ \
   asm volatile("l.amsb_lh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWT_a1(a,b) \
{ \
   asm volatile("l.amsb_hh a1,%0,%1"::"r"(a),"r"(b)); \
}

#else

#define CLR_MACR_a1 \
{ \
   macr_a1 = 0; \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(macr_a1>>n); \
}

#define GET_MACR_RND_a1(dst,n) \
{ \
   dst = (int)((macr_a1+(1<<(n-1)))>>n); \
}

#define GET_MACR_a1_low(dst) \
{ \
   dst = (int)(macr_a1); \
}

#define GET_MACR_a1_high(dst) \
{ \
   dst = (int)(macr_a1>>32); \
}

#define GET_MACR_a1_low_nop GET_MACR_a1_low
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a1_nop GET_MACR_a1

#define AMULL_a1(A,B) \
{ \
   macr_a1 = ((int64_t)(A)*(int64_t)(B)); \
}

#define AMACL_a1(A,B) \
{ \
   macr_a1 += ((int64_t)(A)*(int64_t)(B)); \
}

#define AMSBL_a1(A,B) \
{ \
   macr_a1 -= ((int64_t)(A)*(int64_t)(B)); \
}

#define AMULWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMACWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMACWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMACWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMACWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSBWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   macr_a1 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSBWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   macr_a1 -= ((S64)(a)*(S64)(bx)); \
}

#endif




#define D_UTIL_random(seed_out,seed_in) \
{ \
   seed_out = (short)(seed_in * 31821L + 13849L); \
}

#ifdef __aeon__
#define ASAT(rD,rA,T) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#define ASATU(rD,rA,T) \
{ \
   asm volatile("l.satu %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#define D_UTIL_saturate(x) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(x):"r"(x),"i"(16)); \
}
//l.srari rD,rA,L 
#define ARND_SHIFT(aout,ain,L) \
{ \
   asm volatile("l.srari %0,%1,%2":"=r"(aout):"r"(ain),"i"(L)); \
}

#define AMUL_ADD_HX(rD,rA,rB) \
{ \
   asm volatile("l.uladdh  %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
}

#define AMAX(rd,ra,rb) \
{ \
   asm volatile("l.max  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define AMIN(rd,ra,rb) \
{ \
   asm volatile("l.min  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define ABSA(rd,ra,rb) \
   { \
   asm volatile("l.bsa  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define AABS(aout,ain) \
{ \
   asm volatile("l.abs %0,%1":"=r"(aout):"r"(ain)); \
} 


#else
#define ASAT(rD,rA,T) \
{ \
   int max = (1<<(T-1))-1; \
   int min = -(1<<(T-1)); \
   if ((int)rA > max) \
      rD = max; \
   else if ((int)rA < min) \
      rD = min; \
   else \
      rD = rA; \
}

#define ASATU(rD,rA,T) \
{ \
   unsigned int max = (1<<(T-1))-1; \
   if ((unsigned int)rA > max) \
      rD = max; \
   else \
      rD = rA; \
}

// 16Bit boundary check
#define D_UTIL_saturate(x) \
{ \
if ( x > MAX_16 ) \
    {x = MAX_16;} \
else if ( x < MIN_16 ) \
    {x = MIN_16;} \
}

#define D_UTIL_saturate32_a1(d) \
{ \
if ( macr_a1 > MAX_32 ) \
    d = MAX_32; \
else if ( macr_a1 < MIN_32 ) \
    d = MIN_32; \
else \
    d = (int)macr_a1; \
}

#define ARND_SHIFT(aout,ain,L) \
{ \
   aout = (ain+(1<<(L-1))) >> L; \
}
#define AMUL_ADD_HX(rD,rA,rB) \
{ \
   int A_hi = ((int)rA)>>16; \
   int A_lo = (((int)rA)<<16)>>16; \
   int B_hi = ((int)rB)>>16; \
   int B_lo = (((int)rB)<<16)>>16; \
   rD = A_hi * B_hi + A_lo * B_lo; \
}
#define AMAX(rd,ra,rb) \
{ \
   if((ra)>=(rb)) \
      (rd) = (ra); \
   else \
      (rd) = (rb); \
}
#define AMIN(rd,ra,rb) \
{ \
   if((ra)<=(rb)) \
      (rd) = (ra); \
   else \
      (rd) = (rb); \
}

#define ABSA(rd,ra,rb) \
{ \
   if ((rb) >= 0) \
      (rd) = (ra) >> (rb); \
   else \
      (rd) = (ra) << (-(rb)); \
}

#define AABS(aout,ain) aout = (ain < 0)?(-ain):(ain)

#endif


// 32 = 32*15
//#define D_UTIL_mpy_32_16(hi,lo,n) ((Word32)(((hi * n) + ((lo * n) >> 15))<<1))

// 32 = 32x32
//#define D_UTIL_mpy_32(hi1, lo1, hi2, lo2)  ((Word32)(((hi1 * hi2) + ((hi1 * lo2) >> 15) + ((lo1 * hi2) >> 15))<<1))

#define L_Extract(L_32,hi,lo) \
{ \
   hi = (L_32 >> 16); \
   lo = ((L_32 >>1) & 0x7fff); \
}


#define Mpy_32_16(L_32, var1, var2) \
{ \
   L_32 = var1 & 0xfffffffe; \
   AMULL_a0(L_32,var2); \
   GET_MACR_a0_nop(L_32,16); \
   L_32 = L_32<<1; \
}


#define L_Composition(L_32, hi,  lo) \
{ \
   L_32 = (hi << 16) + (lo << 1); \
}


/*****************************************************************************
 *   Multiply two 32 bit integers (DPF). The result is divided by 2**31      *
 *   L_32 = (hi1*hi2)<<1 + ( (hi1*lo2)>>15 + (lo1*hi2)>>15 )<<1              *

 *****************************************************************************
*/
#define BIT_EXACT_MPY32
#ifdef BIT_EXACT_MPY32
#define Mpy_32(L_32, var1, var2) \
{ \
   Word32 hi1, lo1, hi2, lo2; \
   Word32 L_tmpn; \
   L_Extract(var1, hi1, lo1);  \
   L_Extract(var2, hi2, lo2); \
   AMULL(L_32,hi1,hi2); \
   L_32 = L_32 << 1; \
   AMULL(L_tmpn,hi1,lo2) \
   L_tmpn = L_tmpn >> 15; \
   L_32 = L_32 + (L_tmpn << 1); \
   AMULL(L_tmpn,hi2,lo1) \
   L_tmpn = L_tmpn >> 15; \
   L_32 = L_32 + (L_tmpn << 1); \
}
/*
#define Mpy_32(L_32, var1, var2) \
{ \
   Word32 hi1, lo1, hi2, lo2; \
   Word32 L_tmpn; \
   L_Extract(var1, hi1, lo1);  \
   L_Extract(var2, hi2, lo2); \
   L_32 = hi1 * hi2; \
   L_32 = L_32 << 1; \
   L_tmpn = hi1 * lo2; \
   L_tmpn = L_tmpn >> 15; \
   L_32 = L_32 + (L_tmpn << 1); \
   L_tmpn = hi2 * lo1; \
   L_tmpn = L_tmpn >> 15; \
   L_32 = L_32 + (L_tmpn << 1); \
}*/
#else


#define Mpy_32(L_32, var1, var2) \
{ \
   AMULL_a0(var1,var2); \
   GET_MACR_a0_nop(L_32,31); \
}
#endif

#define awe_Random(seed) \
{ \
   AMULL(seed,seed,31821L); \
   seed = (Word16)(seed + 13849L); \
}

#define sat_add(L_var_out, L_var1, L_var2) \
{ \
   int x=L_var1,y=L_var2; \
   L_var_out = L_var1 + L_var2; \
   if(((x ^ y) & MIN_32) == 0) \
   { \
      if((L_var_out ^ x) & MIN_32) \
         L_var_out = (x < 0) ? MIN_32 : MAX_32; \
   } \
}

#define div_short(L_out, var1,  var2) \
{ \
   L_out = ((var1) <<15)/(var2); \
   if(L_out > 32767) \
      L_out = 32767; \
}

#define D_UTIL_L_extract(L_32, hi, lo) \
{ \
    hi = (L_32>>16); \
    lo = (L_32 >> 1) & 0x7fff; \
}

#define Mpy_32_2(hi1, lo1, hi2, lo2)  ((Word32)(((hi1 * hi2) + ((hi1 * lo2) >> 15) + ((lo1 * hi2) >> 15))<<1))

#endif

