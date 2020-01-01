#ifndef __AMR_WB_CODEC_COMMON_MAC_INCLUDE_FILE__
#define __AMR_WB_CODEC_COMMON_MAC_INCLUDE_FILE__

extern S64 amrwb_macr_a0;

#ifdef __MIPS_4KE__
#define ACLZ_32(aout,ain) \
{ \
   asm volatile("clz %0,%1":"=r"(aout):"r"(ain)); \
   aout = aout+1; \
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


 
#endif

#define AMULL(Dst,A,B) \
{ \
   Dst = (A)*(B); \
}


#ifdef __MIPS_4KE__

#if 0
#define CLR_MACR_a0 \
{ \
   asm volatile("MTHI $0"); \
   asm volatile("MTLO $0"); \
}
#else
#define CLR_MACR_a0 \
{ \
   asm volatile("mult $0,$0"); \
}
#endif

#if 0
#define GET_MACR64_SHIFT(dst,n) \
{ \
   int dst_lo; \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   dst = (dst<<(32-n))+ ((dst_lo>>n) & ((1<<(32-n))-1)); \
}
#else
#define GET_MACR64_SHIFT(dst,n) \
{ \
   int dst_lo; \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(32-n)); \
   asm volatile("srl %0,%1,%2": "=r" (dst_lo) : "r"(dst_lo), "i"(n)); \
   asm volatile("or %0,%1,%2": "=r" (dst) : "r"(dst), "r"(dst_lo)); \
}
#endif
#define GET_MACR_low(dst) \
{ \
   asm volatile("mflo %0": "=r" (dst) : ); \
}

#define GET_MACR_high(dst) \
{ \
   asm volatile("mfhi %0": "=r" (dst) : ); \
}

#define AMULL_a0(A,B) \
{ \
   asm volatile("mult %0, %1": : "r" (A), "r" (B)); \
}

#define AMACL_a0(A,B) \
{ \
   asm volatile("madd %0, %1": : "r" (A), "r" (B)); \
}

#define AMSBL_a0(A,B) \
{ \
   asm volatile("msub %0, %1": : "r" (A), "r" (B)); \
}



#else
#define CLR_MACR_a0 \
{ \
   amrwb_macr_a0 = 0; \
}

#define GET_MACR64_SHIFT(dst,n) \
{ \
   dst = (int)(amrwb_macr_a0>>n); \
}

#define GET_MACR_low(dst) \
{ \
   dst = (int)(amrwb_macr_a0); \
}

#define GET_MACR_high(dst) \
{ \
   dst = (int)(amrwb_macr_a0>>32); \
}

#define AMULL_a0(A,B) \
{ \
   amrwb_macr_a0 = ((int64_t)(A)*(int64_t)(B)); \
}

#define AMACL_a0(A,B) \
{ \
   amrwb_macr_a0 += ((int64_t)(A)*(int64_t)(B)); \
}

#define AMSBL_a0(A,B) \
{ \
   amrwb_macr_a0 -= ((int64_t)(A)*(int64_t)(B)); \
}

#endif

#define GET_MACR_SHIFT_RND(dst,n) \
{ \
   GET_MACR_low(dst); \
   dst = (dst+(1<<(n-1)))>>n; \
}

#define GET_MACR_SHIFT(dst,n) \
{ \
   GET_MACR_low(dst); \
   dst = (dst)>>n; \
}

#define D_UTIL_random(seed_out,seed_in) \
{ \
   seed_out = (short)(seed_in * 31821L + 13849L); \
}


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
if ( x > MAX_16 )         \
    x = MAX_16; \
else if ( x < MIN_16 )    \
    x = MIN_16; \
}
#define ARND_SHIFT_n(aout,ain,shift,rnd) \
{ \
   aout = (ain+rnd) >> shift; \
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

#define D_UTIL_L_extract(L_32, hi, lo) \
{ \
    hi = (L_32>>16); \
   lo = ((L_32 >>1) & 0x7fff); \
}
#if 1
#define Mpy_32_16(L_32, var1, var2) \
{ \
   L_32 = (var1) & 0xfffffffe; \
   AMULL_a0(L_32,((var2)<<16)); \
   GET_MACR_high(L_32); \
   L_32 = L_32<<1; \
}

#else
#define Mpy_32_16(L_32, var1, var2) \
{ \
   L_32 = (var1) & 0xfffffffe; \
   AMULL_a0(L_32,(var2)); \
   GET_MACR_a0(L_32,16); \
   L_32 = L_32<<1; \
}
#endif

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
   D_UTIL_L_extract(var1, hi1, lo1);  \
   D_UTIL_L_extract(var2, hi2, lo2); \
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
   D_UTIL_L_extract(var1, hi1, lo1);  \
   D_UTIL_L_extract(var2, hi2, lo2); \
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
   GET_MACR_high(L_32); \
   L_32=L_32<<1; \
}
#endif



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

#define Mpy_32_2(hi1, lo1, hi2, lo2)  ((Word32)(((hi1 * hi2) + ((hi1 * lo2) >> 15) + ((lo1 * hi2) >> 15))<<1))

#define div_short(L_out, var1,  var2) \
{ \
   L_out = ((var1) <<15)/(var2); \
   if(L_out > 32767) \
      L_out = 32767; \
}

#endif



#include "arm_mac.h"
