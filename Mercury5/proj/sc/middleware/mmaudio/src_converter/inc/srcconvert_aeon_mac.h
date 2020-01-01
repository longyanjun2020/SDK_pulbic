#ifndef _SRCCONVERT_AEON_MAC_INCLUDE_FILE_ 
#define _SRCCONVERT_AEON_MAC_INCLUDE_FILE_


#ifdef __aeon__
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift
#define DCACHE_LINE     16
#endif

#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift

extern S64 srcconverter_macr_a0,srcconverter_macr_a1;

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
   srcconverter_macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   srcconverter_macr_a1 = 0; \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(srcconverter_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(srcconverter_macr_a1>>n); \
}

//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_RND_a0(dst,n) \
{ \
   dst = (int)((srcconverter_macr_a0+(1<<(n-1)))>>n); \
}
#define GET_MACR_RND_a0_nop GET_MACR_RND_a0

#define GET_MACR_a0_nop GET_MACR_a0
#define GET_MACR_a1_nop GET_MACR_a1

#define GET_MACR_a0_high(dst) \
{ \
   dst = (int)(srcconverter_macr_a0>>32); \
}
#define GET_MACR_a0_high_nop GET_MACR_a0_high


#define AMULL(rd,ra,rb) \
{ \
   rd = (int)((S64)(ra)*(S64)(rb)); \
}

#define AMULL_a0(A,B) \
{ \
   srcconverter_macr_a0 = ((S64)(A)*(S64)(B)); \
}
#define AMACL_a0(a,b) \
{ \
   srcconverter_macr_a0 += ((S64)(a)*(S64)(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   srcconverter_macr_a0 -= ((S64)(a)*(S64)(b)); \
}

#define AMULL_a1(A,B) \
{ \
   srcconverter_macr_a1 = ((S64)(A)*(S64)(B)); \
}

#define AMACL_a1(a,b) \
{ \
   srcconverter_macr_a1 += ((S64)(a)*(S64)(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   srcconverter_macr_a1 -= ((S64)(a)*(S64)(b)); \
}


#endif


#ifdef __aeon__
#define AMUL_WL_a0(a,b) \
{ \
   asm volatile("l.amul_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMUL_WH_a0(a,b) \
{ \
   asm volatile("l.amul_wh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMUL_WL_a1(a,b) \
{ \
   asm volatile("l.amul_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMUL_WH_a1(a,b) \
{ \
   asm volatile("l.amul_wh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMAC_WL_a0(a,b) \
{ \
   asm volatile("l.amac_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMAC_WH_a0(a,b) \
{ \
   asm volatile("l.amac_wh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMAC_WL_a1(a,b) \
{ \
   asm volatile("l.amac_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMAC_WH_a1(a,b) \
{ \
   asm volatile("l.amac_wh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSB_WL_a0(a,b) \
{ \
   asm volatile("l.amsb_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSB_WH_a0(a,b) \
{ \
   asm volatile("l.amsb_wh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMSB_WL_a1(a,b) \
{ \
   asm volatile("l.amsb_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSB_WH_a1(a,b) \
{ \
   asm volatile("l.amsb_wh a1,%0,%1"::"r"(a),"r"(b)); \
}

#else
#define AMUL_WL_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMUL_WH_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMUL_WL_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMUL_WH_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMAC_WL_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMAC_WH_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMAC_WL_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMAC_WH_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMSB_WL_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSB_WH_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSB_WL_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   srcconverter_macr_a1 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSB_WH_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   srcconverter_macr_a1 -= ((S64)(a)*(S64)(bx)); \
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
   int max = (1<<(T-1))-1; \
   int min = -(1<<(T-1)); \
   if ((int)(rA) > max) \
      (rD) = max; \
   else if ((int)(rA) < min) \
      (rD) = min; \
   else \
      (rD) = (rA); \
}
#endif


//--------------------------------------------------------
//--------------------------------------------------------

#define IML_N_ML0_a0(x,y) \
{ \
   int u1; \
   MOVHI(u1,y); \
   AMULL_a0(x,u1); \
}
#define IML_N_MLA_a0(x,y) \
{ \
   int u1; \
   MOVHI(u1,y); \
   AMACL_a0(x,u1); \
} 

#define IML_N_ML0_a1(x,y) \
{ \
   int u1; \
   MOVHI(u1,y); \
   AMULL_a1(x,u1); \
}

#define IML_N_MLA_a1(x,y) \
{ \
   int u1; \
   MOVHI(u1,y); \
   AMACL_a1(x,u1); \
} 


#endif

