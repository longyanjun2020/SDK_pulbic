#ifndef __WMA_DECODER_MAC_INCLUDE_FILE__
#define __WMA_DECODER_MAC_INCLUDE_FILE__


#ifdef __MIPS_4KE__
//clz: count leading zero
//output= 0(0x80000000),1,2,...,31(0x00000001),0(0x00000000)
//fl1: find last one
//output=32(0x80000000),31,30,...,1(0x00000001),32(0x00000000)
//clz() = 32-fl1()
#define CLZ(A,cz) \
{ \
   asm volatile("clz %0,%1":"=r"(cz):"r"(A)); \
} 


#else
#define CLZ(A,cz) \
{ \
   int a1 = (A); \
   if(a1==0) \
     cz = 32; \
   else \
   { \
      cz=0; \
      while(a1>0) \
      { \
         cz++; \
         a1 <<= 1;\
      } \
   } \
} 

#endif


#ifdef __MIPS_4KE__



#define SET_MACR(rh,rl) \
{ \
   asm volatile("MTHI %0":: "r"(rh)); \
   asm volatile("MTLO %0":: "r"(rl)); \
}
#define SMULL_high(dst,a,b) \
{ \
   asm volatile("mult %0, %1": : "r" (a), "r" (b)); \
   asm volatile("mfhi %0": "=r" (dst) : ); \
} 
#define USMULL_high(dst,a,b) \
{ \
   asm volatile("multu %0, %1": : "r" (a), "r" (b)); \
   asm volatile("mfhi %0": "=r" (dst) : ); \
} 
/*
#define SMULL_64_30(dst,a,b) \
{ \
   int dst_lo; \
   asm volatile("mult %0, %1": : "r" (a), "r" (b)); \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(2)); \
   asm volatile("srl %0,%1,%2": "=r" (dst_lo) : "r"(dst_lo), "i"(30)); \
   asm volatile("or %0,%1,%2": "=r" (dst) : "r"(dst), "r"(dst_lo)); \
} 
*/
#define SMULL_64_30(dst,a,b) \
{ \
   asm volatile("mult %0, %1": : "r" (a), "r" (b)); \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(2)); \
} 

#define SMULL_64_31(dst,a,b) \
{ \
   asm volatile("mult %0, %1": : "r" (a), "r" (b)); \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(1)); \
} 


#define SMULL(A,B) \
{ \
   asm volatile("mult %0, %1": : "r" (A), "r" (B)); \
}
#define SMACL(A,B) \
{ \
   asm volatile("madd %0, %1": : "r" (A), "r" (B)); \
}
#define SMSBL(A,B) \
{ \
   asm volatile("msub %0, %1": : "r" (A), "r" (B)); \
}

#define GET_MACR_n(dst,n) \
{ \
   int dst_lo; \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   asm volatile("sllv %0,%1,%2": "=r" (dst) : "r"(dst), "r"(32-n)); \
   asm volatile("srlv %0,%1,%2": "=r" (dst_lo) : "r"(dst_lo), "r"(n)); \
   asm volatile("or %0,%1,%2": "=r" (dst) : "r"(dst), "r"(dst_lo)); \
}

#define GET_MACR_15(dst) \
{ \
   int dst_lo; \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(17)); \
   asm volatile("srl %0,%1,%2": "=r" (dst_lo) : "r"(dst_lo), "i"(15)); \
   asm volatile("or %0,%1,%2": "=r" (dst) : "r"(dst), "r"(dst_lo)); \
}

#define GET_MACR_30(dst) \
{ \
   int dst_lo; \
   asm volatile("mfhi %0": "=r" (dst) : ); \
   asm volatile("mflo %0": "=r" (dst_lo) : ); \
   asm volatile("sll %0,%1,%2": "=r" (dst) : "r"(dst), "i"(2)); \
   asm volatile("srl %0,%1,%2": "=r" (dst_lo) : "r"(dst_lo), "i"(30)); \
   asm volatile("or %0,%1,%2": "=r" (dst) : "r"(dst), "r"(dst_lo)); \
}
#define GET_MACR_high(dst) \
{ \
   asm volatile("mfhi %0": "=r" (dst) : ); \
}

#define GET_MACR_low(dst) \
{ \
   asm volatile("mflo %0": "=r" (dst) : ); \
}
#else



#define SET_MACR(rh,rl) \
{ \
   wma_macr_a0 = (((I64)rh)<<32) | (rl); \
}

#define SMULL_high(dst,a,b) \
{ \
   dst = (int)(((I64)(a)*(I64)(b)) >> 32); \
}
#define USMULL_high(dst,a,b) \
{ \
   dst = (unsigned int)(((U64)(a)*(U64)(b)) >> 32); \
} 
#define SMULL_64_30(dst,a,b) \
{ \
   dst = (int)(((I64)(a)*(I64)(b)) >> 30); \
}
#define SMULL_64_31(dst,a,b) \
{ \
   dst = (int)(((I64)(a)*(I64)(b)) >> 31); \
}
#define SMULL(A,B) \
{ \
   wma_macr_a0 = ((I64)(A)*(I64)(B)); \
}
#define SMACL(A,B) \
{ \
   wma_macr_a0 += ((I64)(A)*(I64)(B)); \
}
#define SMSBL(A,B) \
{ \
   wma_macr_a0 -= ((I64)(A)*(I64)(B)); \
}

#define GET_MACR_n(dst,n) \
{ \
   dst = (int)(wma_macr_a0>>n); \
}
#define GET_MACR_15(dst) \
{ \
   dst = (int)(wma_macr_a0>>15); \
}
#define GET_MACR_30(dst) \
{ \
   dst = (int)(wma_macr_a0>>30); \
}
#define GET_MACR_high(dst) \
{ \
   dst = (int)(wma_macr_a0>>32); \
}

#define GET_MACR_low(dst) \
{ \
   dst = (int)(wma_macr_a0); \
}
#endif


#define SMUL_MAC(a,b,c,d,dest) \
{ \
   SMULL(a,b); \
   SMACL(c,d); \
   GET_MACR_high(dest); \
   dest = dest<<1; \
}

#define SMUL_MSB(a,b,c,d,dest) \
{ \
   SMULL(a,b); \
   SMSBL(c,d); \
   GET_MACR_high(dest); \
   dest = dest<<1; \
}

//--------------------------------------------------
//--------------------------------------------------

static INLINE int norm_log(int x,int *nor_var)
{
   int exp;
   CLZ(x,exp);
   *nor_var = (x<<exp) & 0x7fffffff;
   exp = 32-exp;
   return exp;
}


#define SATURATION16(it,flt,mn,mx) \
    if (flt < mn) \
        it = mn; \
    else if (flt > mx) \
        it = mx; \
    else \
        it = flt;
        
#define MULT_HI(a,b) (MULT_HI_DWORD(a,b)<<1)


#define wma_abs(a)   (((a)<0)?(-(a)): (a))



#endif
