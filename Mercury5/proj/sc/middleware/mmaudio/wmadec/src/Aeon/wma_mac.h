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

#elif __aeon__


#define MAX_SPRS_PER_GRP_BITS (11)
#define SPRGROUP_MAC	(5<< MAX_SPRS_PER_GRP_BITS)
#define SPR_AMACCFG   (SPRGROUP_MAC + 13)
#define __l_mtspr1__(spr,val)                               \
    __asm__ volatile ("l.mtspr\tr0,%0,%1" : : "r"(val), "K"(spr))
#define L_MTSPR1(_spr_register_16bit_const_, _val_)         \
    __l_mtspr1__(_spr_register_16bit_const_, _val_)


static __inline void mstar_aeon_hardware_init(void)
{
  L_MTSPR1(SPR_AMACCFG, 1); // enable AMAC 
}



#ifdef __aeon__
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift

#define awd_clz1(ain,aout) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
   aout = 31-aout; \
} 
#define awd_clz2(ain,aout) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(aout):"r"(ain)); \
   aout = 15-aout; \
} 
#define awd_labs(aout,ain) \
{ \
   asm volatile("l.abs %0,%1":"=r"(aout):"r"(ain)); \
}
#else
#define awd_clz1(ain,aout) \
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
#define awd_clz2(ain,aout) \
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
#define awd_labs(aout,ain) aout = (ain < 0)?(-ain):(ain)


#endif



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
#define GET_MACR_RND_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_RND_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a0_low_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280b)); \
}

#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a1_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280c)); \
}

#define AMULL(Dst,A,B) \
{ \
   asm volatile("l.amull %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
#define AMULLU(Dst,A,B) \
{ \
   asm volatile("l.amullu %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
#define GET_MACR_a0a1_30(dst0,dst1,a,b,c,d) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
	asm volatile("l.amul a1,%0,%1"::"r"(c),"r"(d));\
	asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst0): "i"(AMACR_SHR), "i"(30)); \
	asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst1): "i"(AMACR_SHR), "i"(30)); \
}
#define GET_MACR_a0a1_31(dst0,dst1,a,b,c,d) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
	asm volatile("l.amul a1,%0,%1"::"r"(c),"r"(d));\
	asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst0): "i"(AMACR_SHR), "i"(31)); \
	asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst1): "i"(AMACR_SHR), "i"(31)); \
}
#define GET_MACR_a0a1_32(dst0,dst1,a,b,c,d) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
	asm volatile("l.amul a1,%0,%1"::"r"(c),"r"(d));\
	asm volatile("b.mfspr1 %0, %1":"=r"(dst0):"i"(0x280a)); \
	asm volatile("b.mfspr1 %0, %1":"=r"(dst1):"i"(0x280c)); \
}

#define GET_MACR_a0_30(dst,a,b) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(30)); \
}
#define GET_MACR_a1_30(dst,a,b) \
{ \
    asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(30)); \
}
#define GET_MACR_a0_31(dst,a,b) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	 asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(31)); \
}
#define GET_MACR_a1_31(dst,a,b) \
{ \
    asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(31)); \
}
#define GET_MACR_a0_32(dst,a,b) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a1_32(dst,a,b) \
{ \
    asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280c)); \
}
#define GET_MACR_a0_32U(dst,a,b) \
{ \
    asm volatile("l.amulu a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a1_32U(dst,a,b) \
{ \
    asm volatile("l.amulu a1,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
	asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280c)); \
}
#define GET_MACR_a0_32I_HILO(dst_hi,dst_lo,a,b) \
{ \
    asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
    asm volatile("b.mfspr1 %0, %1":"=r"(dst_lo):"i"(0x2809)); \
	 asm volatile("b.mfspr1 %0, %1":"=r"(dst_hi):"i"(0x280a)); \
}
#define GET_MACR_a1_32I_HILO(dst_hi,dst_lo,a,b) \
{ \
    asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
    asm volatile("b.mfspr1 %0, %1":"=r"(dst_lo):"i"(0x280b)); \
	 asm volatile("b.mfspr1 %0, %1":"=r"(dst_hi):"i"(0x280c)); \
}
#define GET_MACR_a0_32U_HILO(dst_hi,dst_lo,a,b) \
{ \
    asm volatile("l.amulu a0,%0,%1"::"r"(a),"r"(b));\
    asm volatile("l.nop"); \
    asm volatile("b.mfspr1 %0, %1":"=r"(dst_lo):"i"(0x2809)); \
	 asm volatile("b.mfspr1 %0, %1":"=r"(dst_hi):"i"(0x280a)); \
}
#define AMULL_a0(a,b) \
{ \
   asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULL_a1(a,b) \
{ \
   asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACL_a0(A,B) \
{ \
   asm volatile("l.amac a0,%0,%1"::"r"(A),"r"(B)); \
}
#define AMACL_a1(A,B) \
{ \
   asm volatile("l.amac a1,%0,%1"::"r"(A),"r"(B)); \
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
//-----------------------------------------------
//-----------------------------------------------
#define ABSA(Dst,A,B) \
{ \
    asm volatile("l.bsa  %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
#define ABSL(Dst,A,B) \
{ \
    asm volatile("l.bsl  %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
}
//-----------------------------------------------
//-----------------------------------------------


#else


#define SET_MACR(rh,rl) \
{ \
   macr_a0 = (((tWMA_I64)rh)<<32) | (rl); \
}

#define SMULL_high(dst,a,b) \
{ \
   dst = (int)(((tWMA_I64)(a)*(tWMA_I64)(b)) >> 32); \
}
#define USMULL_high(dst,a,b) \
{ \
   dst = (unsigned int)(((tWMA_U64)(a)*(tWMA_U64)(b)) >> 32); \
} 
#define SMULL_64_30(dst,a,b) \
{ \
   dst = (int)(((tWMA_I64)(a)*(tWMA_I64)(b)) >> 30); \
}
#define SMULL_64_31(dst,a,b) \
{ \
   dst = (int)(((tWMA_I64)(a)*(tWMA_I64)(b)) >> 31); \
}
#define SMULL(A,B) \
{ \
   macr_a0 = ((tWMA_I64)(A)*(tWMA_I64)(B)); \
}
#define SMACL(A,B) \
{ \
   macr_a0 += ((tWMA_I64)(A)*(tWMA_I64)(B)); \
}
#define SMSBL(A,B) \
{ \
   macr_a0 -= ((tWMA_I64)(A)*(tWMA_I64)(B)); \
}

#define GET_MACR_n(dst,n) \
{ \
   dst = (int)(macr_a0>>n); \
}
#define GET_MACR_15(dst) \
{ \
   dst = (int)(macr_a0>>15); \
}
#define GET_MACR_30(dst) \
{ \
   dst = (int)(macr_a0>>30); \
}
#define GET_MACR_high(dst) \
{ \
   dst = (int)(macr_a0>>32); \
}

#define GET_MACR_low(dst) \
{ \
   dst = (int)(macr_a0); \
}

#define GET_MACR_a0_32I_HILO(dst_hi,dst_lo,a,b) \
{ \
   dst_hi = (unsigned int)(((tWMA_I64)(a)*(tWMA_I64)(b)) >> 32);       \
   dst_hi = (unsigned int) ((((tWMA_I64)(a)*(tWMA_I64)(b)) << 32)>>32); \
}   

#define GET_MACR_a1_32I_HILO(dst_hi,dst_lo,a,b) \
{ \
   dst_hi = (unsigned int)(((tWMA_I64)(a)*(tWMA_I64)(b)) >> 32);       \
   dst_hi = (unsigned int) ((((tWMA_I64)(a)*(tWMA_I64)(b)) << 32)>>32); \
}   

#define GET_MACR_a0_32U_HILO(dst_hi,dst_lo,a,b) \
{ \
   dst_hi = (unsigned int)(((tWMA_U64)(a)*(tWMA_U64)(b)) >> 32);       \
   dst_hi = (unsigned int) ((((tWMA_U64)(a)*(tWMA_U64)(b)) << 32)>>32); \
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
