#ifndef _APP_MAC_H_ 
#define _APP_MAC_H_
#include "app_datatype.h"
//#define __aeon__
//#define __AEONR2__
#ifdef __aeon__
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift

#define DCACHE_LINE     16
#define MP3D_MEM_ALIGN  __attribute__((aligned(DCACHE_LINE)))
#else

#define MP3D_MEM_ALIGN
#endif

#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift

#if defined(__aeon__) || defined(__AEONR2__)
//clz: count leading zero
//output= 0(0x80000000),1,2,...,31(0x00000001),0(0x00000000)
//fl1: find last one
//output=32(0x80000000),31,30,...,1(0x00000001),32(0x00000000)
//clz() = 32-fl1()
#define CLZ(A,cz) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(cz):"r"(A)); \
   cz = 32-cz; \
} 
#else
#define CLZ(A,cz) \
{ \
   tS32 a1 = (A); \
   if(a1==0) \
    {\
     cz = 32; \
    }\
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


#ifdef __aeon__

#define CLR_MACR_a0 \
{ \
   asm volatile("l.amul a0,r0,r0"); \
}
#define CLR_MACR_a1 \
{ \
   asm volatile("l.amul a1,r0,r0"); \
}
#define GET_MACR_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}


#ifdef __AEONR2__
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}

#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a0_high_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}

#define AMULL(rd,ra,rb) \
{ \
   asm volatile("b.mul %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define MOVHI(dst,imm) \
{ \
   asm volatile("b.movhi %0,%1":"=r"(dst):"i"(imm)); \
}

#define GET_MACR_RND_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_RND_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}

#else
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a0_high_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280a)); \
}

#define AMULL(rd,ra,rb) \
{ \
   asm volatile("l.amull %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}

#define MOVHI(dst,imm) \
{ \
   asm volatile("l.movhi %0,%1":"=r"(dst):"i"(imm)); \
}

#endif



#define AMULL_a0(a,b) \
{ \
   asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACL_a0(a,b) \
{ \
   asm volatile("l.amac a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   asm volatile("l.amsb a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULL_a1(a,b) \
{ \
   asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACL_a1(a,b) \
{ \
   asm volatile("l.amac a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   asm volatile("l.amsb a1,%0,%1"::"r"(a),"r"(b)); \
}

#else

#define MOVHI(dst,imm) \
{ \
   dst = imm << 16; \
}

#define CLR_MACR_a0 \
{ \
   app_macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   app_macr_a1 = 0; \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(app_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(app_macr_a1>>n); \
}

//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_RND_a0(dst,n) \
{ \
   dst = (int)((app_macr_a0+(1<<(n-1)))>>n); \
}
#define GET_MACR_RND_a1(dst,n) \
{ \
   dst = (int)((app_macr_a1+(1<<(n-1)))>>n); \
}

#define GET_MACR_RND_a0_nop GET_MACR_RND_a0

#define GET_MACR_a0_nop GET_MACR_a0
#define GET_MACR_a1_nop GET_MACR_a1

#define GET_MACR_a0_high(dst) \
{ \
   dst = (int)(app_macr_a0>>32); \
}
#define GET_MACR_a0_high_nop GET_MACR_a0_high


#define AMULL(rd,ra,rb) \
{ \
   rd = (int)((tS64)(ra)*(tS64)(rb)); \
}

#define AMULL_a0(A,B) \
{ \
   app_macr_a0 = ((tS64)(A)*(tS64)(B)); \
}
#define AMACL_a0(a,b) \
{ \
   app_macr_a0 += ((tS64)(a)*(tS64)(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   app_macr_a0 -= ((tS64)(a)*(tS64)(b)); \
}

#define AMULL_a1(A,B) \
{ \
   app_macr_a1 = ((tS64)(A)*(tS64)(B)); \
}

#define AMACL_a1(a,b) \
{ \
   app_macr_a1 += ((tS64)(a)*(tS64)(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   app_macr_a1 -= ((tS64)(a)*(tS64)(b)); \
}

#endif

#ifdef __aeon__
#define ASAT(rD,rA,T) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#else
#define ASAT(rD,rA,T) \
{ \
   tS32 max = (1<<(T-1))-1; \
   tS32 min = -(1<<(T-1)); \
   if ((tS32)(rA) > max) \
      (rD) = max; \
   else if ((tS32)(rA) < min) \
      (rD) = min; \
   else \
      (rD) = (rA); \
}
#endif

#endif

