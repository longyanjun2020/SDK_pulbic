#ifndef __AMR_NB_DECODER_MAC_INCLUDE_FILE__
#define __AMR_NB_DECODER_MAC_INCLUDE_FILE__



#ifdef __aeon__
//---------------------------------------------------------

// aeon MAC hardware initial function

#define MAX_SPRS_PER_GRP_BITS (11)
#define SPRGROUP_MAC (5<< MAX_SPRS_PER_GRP_BITS)
#define SPR_AMACCFG   (SPRGROUP_MAC + 13)
#ifdef __AEONR2__
#define __l_mtspr1__(spr,val)                               \
    __asm__ volatile ("b.mtspr1\t%0,%1" : : "r"(val), "K"(spr))
#else
#define __l_mtspr1__(spr,val)                               \
    __asm__ volatile ("l.mtspr\tr0,%0,%1" : : "r"(val), "K"(spr))
#endif
#define L_MTSPR1(_spr_register_16bit_const_, _val_)         \
    __l_mtspr1__(_spr_register_16bit_const_, _val_)

// enable AMAC 
#define Mstar_amrnb_aeon_hardware_init L_MTSPR1(SPR_AMACCFG, 1);
#else    
#define Mstar_amrnb_aeon_hardware_init
#endif

#define AMACR_KEEP   0x10   //
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift


enum amac_round_mode_e
{
   amac_round_to_infinity = 0,
   amac_round_away_from_zero = 1
};

enum amac_saturate_mode_e
{
   amac_saturate_to_64bit_before_shift = 0,
   amac_saturate_to_64bit_after_shift = 1,
   amac_saturate_to_32bit_after_shift = 2,
   amac_saturate_to_16bit_after_shift = 3
};

#ifdef __aeon__
#define set_reg_volatile2(a,b)      __asm__ ("0:" : : "r"(a),"r"(b)); 
#define set_reg_volatile3(a,b,c)    __asm__ ("0:" : : "r"(a),"r"(b),"r"(c)); 
#define set_reg_volatile4(a,b,c,d)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d)); 
#define set_reg_volatile5(a,b,c,d,e)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e)); 
#define set_reg_volatile8(a,b,c,d,e,f,g,h)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f),"r"(g),"r"(h)); 
#define set_reg_volatile10(a,b,c,d,e,f,g,h,i,j)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f),"r"(g),"r"(h),"r"(i),"r"(j)); 
#else
#define set_reg_volatile2(a,b)
#define set_reg_volatile3(a,b,c)
#define set_reg_volatile4(a,b,c,d)
#define set_reg_volatile5(a,b,c,d,e)
#define set_reg_volatile8(a,b,c,d,e,f,g,h)
#define set_reg_volatile10(a,b,c,d,e,f,g,h,i,j)
#endif


#ifdef __aeon__

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
   Dst = (int)((S64)(A)*(S64)(B)); \
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

#define CLR_MACR_a2 \
{ \
   asm volatile("l.amul a2,r0,r0"); \
}
#define CLR_MACR_a3 \
{ \
   asm volatile("l.amul a3,r0,r0"); \
}

#define GET_MACR_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a2(dst,n) \
{ \
   asm volatile("l.amacr %0, a2, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a3(dst,n) \
{ \
   asm volatile("l.amacr %0, a3, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR), "i"(n)); \
}
#define GET_MACR_RND_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_RND_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_RND_a2(dst,n) \
{ \
   asm volatile("l.amacr %0, a2, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
#define GET_MACR_RND_a3(dst,n) \
{ \
   asm volatile("l.amacr %0, a3, %1, %2": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND), "i"(n)); \
}
//-----------------------------------------------
//-----------------------------------------------
#ifdef __AEONR2__

#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a2_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2821)); \
}
#define GET_MACR_a3_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2823)); \
}
#define GET_MACR_a0_hi(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280A)); \
}

#define GET_MACR_a1_hi(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280c)); \
}

#else

#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a2_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2821)); \
}
#define GET_MACR_a3_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2823)); \
}

#define GET_MACR_a0_hi(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280A)); \
}


#define GET_MACR_a1_hi(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280c)); \
}
#endif


#else
#define CLR_MACR_a0 \
{ \
   amrnb_macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   amrnb_macr_a1 = 0; \
}
#define CLR_MACR_a2 \
{ \
   amrnb_macr_a2 = 0; \
}
#define CLR_MACR_a3 \
{ \
   amrnb_macr_a3 = 0; \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(amrnb_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(amrnb_macr_a1>>n); \
}
#define GET_MACR_a2(dst,n) \
{ \
   dst = (int)(amrnb_macr_a2>>n); \
}

#define GET_MACR_a3(dst,n) \
{ \
   dst = (int)(amrnb_macr_a3>>n); \
}

#define GET_MACR_RND_a0(dst,n) \
{ \
   dst = (int)((amrnb_macr_a0+(1<<(n-1)))>>n); \
}

#define GET_MACR_RND_a1(dst,n) \
{ \
   dst = (int)((amrnb_macr_a1+(1<<(n-1)))>>n); \
}
#define GET_MACR_RND_a2(dst,n) \
{ \
   dst = (int)((amrnb_macr_a2+(1<<(n-1)))>>n); \
}

#define GET_MACR_RND_a3(dst,n) \
{ \
   dst = (int)((amrnb_macr_a3+(1<<(n-1)))>>n); \
}

#define GET_MACR_a0_low(dst) \
{ \
   dst = (int)(amrnb_macr_a0); \
}
#define GET_MACR_a1_low(dst) \
{ \
   dst = (int)(amrnb_macr_a1); \
}
#define GET_MACR_a2_low(dst) \
{ \
   dst = (int)(amrnb_macr_a2); \
}
#define GET_MACR_a3_low(dst) \
{ \
   dst = (int)(amrnb_macr_a3); \
}
#define GET_MACR_a0_hi(dst) \
{ \
   dst = (int)(amrnb_macr_a0>>32); \
}
#define GET_MACR_a1_hi(dst) \
{ \
   dst = (int)(amrnb_macr_a1>>32); \
}
#endif




#ifdef __aeon__
#define ALNOP   asm volatile("l.nop")
#ifdef __AEONR2__
#define LNOP
#else
#define LNOP   asm volatile("l.nop")
#endif
#else
#define LNOP
#define ALNOP
#endif

#define GET_MACR_RND_a0_nop(dst,n) \
{ \
   LNOP; \
   GET_MACR_RND_a0(dst,n); \
}

#define GET_MACR_a0_low_nop(dst) \
{ \
   LNOP; \
   GET_MACR_a0_low(dst);\
}

#define GET_MACR_a1_low_nop(dst) \
{ \
   LNOP; \
   GET_MACR_a1_low(dst); \
}

#define GET_MACR_a0_nop(dst,n) \
{ \
   LNOP; \
   GET_MACR_a0(dst,n); \
}

#define GET_MACR_a1_nop(dst,n) \
{ \
   LNOP; \
   GET_MACR_a1(dst,n); \
}

#define GET_MACR_a0_hi_nop(dst) \
{ \
   LNOP; \
   GET_MACR_a0_hi(dst); \
}


#ifdef __aeon__
#define AMULL_a0(a,b) \
{ \
   asm volatile("l.amul a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULL_a1(a,b) \
{ \
   asm volatile("l.amul a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULL_a2(a,b) \
{ \
   asm volatile("l.amul a2,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULL_a3(a,b) \
{ \
   asm volatile("l.amul a3,%0,%1"::"r"(a),"r"(b)); \
}

#define AMACL_a0(A,B) \
{ \
   asm volatile("l.amac a0,%0,%1"::"r"(A),"r"(B)); \
}
#define AMACL_a1(A,B) \
{ \
   asm volatile("l.amac a1,%0,%1"::"r"(A),"r"(B)); \
}
#define AMACL_a2(A,B) \
{ \
   asm volatile("l.amac a2,%0,%1"::"r"(A),"r"(B)); \
}
#define AMACL_a3(A,B) \
{ \
   asm volatile("l.amac a3,%0,%1"::"r"(A),"r"(B)); \
}
#define AMSBL_a0(A,B) \
{ \
   asm volatile("l.amsb a0,%0,%1"::"r"(A),"r"(B)); \
}
#define AMSBL_a1(A,B) \
{ \
   asm volatile("l.amsb a1,%0,%1"::"r"(A),"r"(B)); \
}
#define AMSBL_a2(A,B) \
{ \
   asm volatile("l.amsb a2,%0,%1"::"r"(A),"r"(B)); \
}
#define AMSBL_a3(A,B) \
{ \
   asm volatile("l.amsb a3,%0,%1"::"r"(A),"r"(B)); \
}
#else

#define AMULL_a0(A,B) \
{ \
   amrnb_macr_a0 = ((S64) (A)* (S64)(B)); \
}

#define AMULL_a1(A,B) \
{ \
   amrnb_macr_a1 = ((S64) (A)* (S64) (B)); \
}
#define AMULL_a2(A,B) \
{ \
   amrnb_macr_a2 = ((S64) (A)* (S64)(B)); \
}

#define AMULL_a3(A,B) \
{ \
   amrnb_macr_a3 = ((S64) (A)* (S64) (B)); \
}
#define AMACL_a0(A,B) \
{ \
   amrnb_macr_a0 += ((S64)(A)*(S64)(B)); \
}

#define AMACL_a1(A,B) \
{ \
   amrnb_macr_a1 += ((S64)(A)*(S64)(B)); \
}
#define AMACL_a2(A,B) \
{ \
   amrnb_macr_a2 += ((S64)(A)*(S64)(B)); \
}

#define AMACL_a3(A,B) \
{ \
   amrnb_macr_a3 += ((S64)(A)*(S64)(B)); \
}
#define AMSBL_a0(A,B) \
{ \
   amrnb_macr_a0 -= ((S64)(A)*(S64)(B)); \
}

#define AMSBL_a1(A,B) \
{ \
   amrnb_macr_a1 -= ((S64)(A)*(S64)(B)); \
}
#define AMSBL_a2(A,B) \
{ \
   amrnb_macr_a2 -= ((S64)(A)*(S64)(B)); \
}

#define AMSBL_a3(A,B) \
{ \
   amrnb_macr_a3 -= ((S64)(A)*(S64)(B)); \
}
#endif


#ifdef __aeon__

#define AMULWB_a0(a,b) \
{ \
   asm volatile("l.amul_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWT_a0(a,b) \
{ \
   asm volatile("l.amul_wh a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWB_a1(a,b) \
{ \
   asm volatile("l.amul_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWT_a1(a,b) \
{ \
   asm volatile("l.amul_wh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWB_a0(a,b) \
{ \
   asm volatile("l.amac_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWT_a0(a,b) \
{ \
   asm volatile("l.amac_wh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMACWB_a1(a,b) \
{ \
   asm volatile("l.amac_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMACWT_a1(a,b) \
{ \
   asm volatile("l.amac_wh a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWB_a0(a,b) \
{ \
   asm volatile("l.amsb_wl a0,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWT_a0(a,b) \
{ \
   asm volatile("l.amsb_wh a0,%0,%1"::"r"(a),"r"(b)); \
}

#define AMSBWB_a1(a,b) \
{ \
   asm volatile("l.amsb_wl a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBWT_a1(a,b) \
{ \
   asm volatile("l.amsb_wh a1,%0,%1"::"r"(a),"r"(b)); \
}

#else

#define AMULWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a0 = ((S64)(a)*(S64)(bx)); \
}
#define AMULWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a1 = ((S64)(a)*(S64)(bx)); \
}
#define AMULWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMACWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a0 += ((S64)(a)*(S64)(bx)); \
}
#define AMACWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMACWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a1 += ((S64)(a)*(S64)(bx)); \
}
#define AMACWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}
#define AMSBWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   amrnb_macr_a1 -= ((S64)(a)*(S64)(bx)); \
}
#define AMSBWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   amrnb_macr_a1 -= ((S64)(a)*(S64)(bx)); \
}

#endif





#ifdef __aeon__

#define ASAT(rD,rA,T) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#define ASATU(rD,rA,T) \
{ \
   asm volatile("l.satu %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#else

//------------------------------------------------------------
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
#endif

#ifdef __aeon__
//l.srari rD,rA,L 
#define ARND_SHIFT(aout,ain,L) \
{ \
   asm volatile("l.srari %0,%1,%2":"=r"(aout):"r"(ain),"i"(L)); \
}
#else
#define ARND_SHIFT(aout,ain,L) \
{ \
   aout = (ain+(1<<(L-1))) >> L; \
}

#endif

#ifdef __aeon__
#define AMUL_ADD_HX(rD,rA,rB) \
{ \
   asm volatile("l.uladdh  %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
}
#else
#define AMUL_ADD_HX(rD,rA,rB) \
{ \
   int A_hi = ((int)rA)>>16; \
   int A_lo = (((int)rA)<<16)>>16; \
   int B_hi = ((int)rB)>>16; \
   int B_lo = (((int)rB)<<16)>>16; \
   rD = A_hi * B_hi + A_lo * B_lo; \
}
#endif

#ifdef __aeon__
#define AMAX(rd,ra,rb) \
{ \
   asm volatile("l.max  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define AMIN(rd,ra,rb) \
{ \
   asm volatile("l.min  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}

#else
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
#endif


#ifdef __aeon__
#define AABS(rD,rA) \
{ \
   asm volatile("l.abs %0,%1":"=r"(rD):"r"(rA)); \
} 
#else
#define AABS(rD,rA) \
{ \
   rD = (rA < 0)?(-rA):(rA); \
}
#endif

#ifdef __aeon__
#define ABSA(rd,ra,rb) \
   { \
   asm volatile("l.bsa  %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#define ABSA_S(rD,rA,rB) \
{ \
   asm volatile("b.bsa_s %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
} 
#else

#define ABSA(rd,ra,rb) \
{ \
   if ((rb) >= 0) \
      (rd) = (ra) >> (rb); \
   else \
      (rd) = (ra) << (-(rb)); \
}

#define ABSA_S(rD,rA,rB) \
{ \
    int shift = (rB); \
    if (shift >= 0) \
    { \
        if ((shift) >= 32) \
            (rD) = ((rA) >= 0)? 0 : -1; \
        else \
            (rD) = (int)(rA) >> (shift); \
    } \
    else \
    { \
        shift = -(rB); \
        if (shift >= 32) \
        { \
            if ((int)(rA) > 0) \
                (rD) = 0x7fffffff; \
            else if ((int)(rA) < 0) \
                (rD) = 0x80000000; \
            else \
                (rD) = 0; \
        } \
        else \
        { \
            if ((((int)(rA) << shift) >> shift) != (rA)) { \
                (rD) = (unsigned int)0x7fffffff + (((unsigned int)(rA)) >> 31);  \
            } else { \
                (rD) = (int)(rA) << shift; \
            } \
        } \
    } \
}

#endif


#ifdef __aeon__

#define AADD32_S(rD,rA,rB) \
{ \
   asm volatile("b.add_s %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
} 

#define AADD16_S(rD,rA,rB) \
{ \
   asm volatile("b.addp_s %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
} 

#define ASUB32_S(rD,rA,rB) \
{ \
   asm volatile("b.sub_s %0,%1,%2":"=r"(rD):"r"(rA),"r"(rB)); \
} 

#else

#define AADD32_S(rD,rA,rB) \
{ \
   (rD) = (rA) + (rB); \
   if (((rA) & 0x80000000) == ((rB) & 0x80000000)) \
   if (((rD) & 0x80000000) != ((rA) & 0x80000000)) \
   { \
      (rD) = ((rA) & 0x80000000)? 0x80000000 : 0x7fffffff; \
   } \
}

#define AADD16_S(rD,rA,rB) \
{ \
   short a_lo = (short)rA; \
   short a_hi = (short)(rA>>16); \
   short b_lo = (short)rB; \
   short b_hi = (short)(rB>>16); \
   int hi; \
   int lo = (int)a_lo + b_lo; \
   if ((a_lo & 0x8000) == (b_lo & 0x8000)) \
       if ((lo & 0x8000) != (a_lo & 0x8000)) \
       { \
           lo = (a_lo & 0x8000)? 0x8000 : 0x7fff; \
       } \
   hi = (int)a_hi + b_hi; \
   if ((a_hi & 0x8000) == (b_hi & 0x8000)) \
       if ((hi & 0x8000) != (a_hi & 0x8000)) \
       { \
           hi = (a_hi & 0x8000)? 0x8000 : 0x7fff; \
       } \
   rD = (unsigned short)lo | (((int)hi)<<16); \
}


#define ASUB32_S(rD,rA,rB) \
{ \
   (rD) = (rA) - (rB); \
   if (((rA) & 0x80000000) != ((rB) & 0x80000000)) \
   if (((rD) & 0x80000000) != ((rA) & 0x80000000)) \
   { \
      (rD) = ((rA) & 0x80000000)? 0x80000000 : 0x7fffffff; \
   } \
}
#endif

#ifdef __aeon__
#define AEXTU(rD,rA,T,rB) \
{ \
   asm volatile("b.extu %0,%1,%2,%3":"=r"(rD):"r"(rA),"i"(T),"r"(rB)); \
} 
#else
#define AEXTU(rD,rA,T,rB) \
{ \
   rD = ((unsigned int)rA << (32-(T+rB))) >> (32-T); \
}

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
//ACLZ:     : ,0(negative)  , 1(0x40000000), 2(0x20000000),...,31(0x00000001),32(0x00000000)
//aeon l.fl1: 32(0x80000000),31(0x40000000),30(0x20000000),..., 1(0x00000001), 0(0x00000000)
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

#define AFL1(aout,_ain) \
{ \
   int ain = _ain; \
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
#define GET_MACR_RND_SAT_a0e(dst,n,rnd,sat) \
{ \
   asm volatile("l.amacr_ex %0, a0, %1, %2, %3, %4": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND|AMACR_SAT), "i"(n),"i"(rnd),"i"(sat)); \
}

#define GET_MACR_RND_SAT_a1e(dst,n,rnd,sat) \
{ \
   asm volatile("l.amacr_ex %0, a1, %1, %2, %3, %4": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_RND|AMACR_SAT), "i"(n),"i"(rnd),"i"(sat)); \
}

#define GET_MACR_SAT_a0e(dst,n,sat) \
{ \
   asm volatile("l.amacr_ex %0, a0, %1, %2, %3, %4": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_SAT), "i"(n),"i"(0),"i"(sat)); \
}

#define GET_MACR_SAT_a1e(dst,n,sat) \
{ \
   asm volatile("l.amacr_ex %0, a1, %1, %2, %3, %4": "=r"(dst): "i"(AMACR_KEEP|AMACR_SHR|AMACR_SAT), "i"(n),"i"(0),"i"(sat)); \
}

#else
#define GET_MACR_RND_SAT_e(ap,dst,n,Z,rnd,sat) \
{ \
   S64 t;  \
   int L = (n); \
   if(ap==0)  \
      t = amrnb_macr_a0; \
   else  \
      t = amrnb_macr_a1; \
   if ((Z & AMACR_RND) && L!=0) \
   { \
      if(rnd == amac_round_to_infinity) \
         t += 1LL<<(L-1); \
      else  \
      { \
         if (t>=0) \
            t += 1LL<<(L-1); \
         else \
            t -= 1LL<<(L-1); \
      } \
   } \
   if(Z & AMACR_SHR) \
      t >>= L; \
   if ((Z & AMACR_SAT) && sat != amac_saturate_to_64bit_before_shift) \
   { \
      int N = (sat == amac_saturate_to_64bit_after_shift)? 64 : \
              (sat == amac_saturate_to_32bit_after_shift)? 32 : 16; \
      if(t != (t << (64-N) >> (64-N))) \
         t = t>=0? (1LL<<(N-1))-1 : ~((1LL<<(N-1))-1); \
   } \
   dst = (int)(t); \
}

#define GET_MACR_RND_SAT_a0e(dst,n,rnd,sat) \
{ \
   GET_MACR_RND_SAT_e(0,dst,n,(AMACR_KEEP|AMACR_SHR|AMACR_RND|AMACR_SAT),rnd,sat); \
}

#define GET_MACR_RND_SAT_a1e(dst,n,rnd,sat) \
{ \
   GET_MACR_RND_SAT_e(1,dst,n,(AMACR_KEEP|AMACR_SHR|AMACR_RND|AMACR_SAT),rnd,sat); \
}

#define GET_MACR_SAT_a0e(dst,n,sat) \
{ \
   GET_MACR_RND_SAT_e(0,dst,n,(AMACR_KEEP|AMACR_SHR|AMACR_SAT),0,sat); \
}

#define GET_MACR_SAT_a1e(dst,n,sat) \
{ \
   GET_MACR_RND_SAT_e(1,dst,n,(AMACR_KEEP|AMACR_SHR|AMACR_SAT),0,sat); \
}
#endif


#ifdef __aeon__
#define AEXP(rD,rA) \
{ \
   asm volatile("l.exp %0, %1": "=r"(rD): "r"(rA)); \
}
#define AEXP16(rD,rA) \
{ \
   asm volatile("l.exp16 %0, %1": "=r"(rD): "r"(rA)); \
}
#else
#define AEXP(rD,rA) \
{ \
   int r = rA; \
   if (r<0) \
      r = ~r; \
   AFL1(rD,r); \
   rD = 31-rD; \
}

#define AEXP16(rD,rA) \
{ \
   int r = rA; \
   if (r<0) \
      r = ~r; \
   AFL1(rD,r); \
   rD = 15-rD; \
}
#endif

static INLINE Word16 add (Word16 var1, Word16 var2)
{
    Word32 L_sum;

    L_sum = (Word32) var1 + var2;
    ASAT(L_sum,L_sum,16);
    return (Word16)L_sum;
}

static INLINE Word16 sub (Word16 var1, Word16 var2)
{
    Word32 L_diff;

    L_diff = (Word32) var1 - var2;
    ASAT(L_diff,L_diff,16);
    return (Word16)L_diff;
}
/*
static INLINE Word16 shl (Word16 var1, Word16 var2)
{
   int dst;
   ABSA_S(dst,(Word32)var1,(Word32)(-var2));
   return (Word16)dst;
}
static INLINE Word16 shr (Word16 var1, Word16 var2)
{
   int dst;
   ABSA_S(dst,(Word32)var1,(Word32)(var2));
   return (Word16)dst;
}*/


static INLINE Word16 shl (Word16 var1, Word16 var2)
{
   Word32 result;

   if(var2 < 0)
   {
      result = var1 >> (-var2);
   }
   else
   {
      result = var1 << var2;
      ASAT(result,result,16);
      //if(((result << 16)>>16) != result)
      //   result = (var1 > 0) ? MAX_16 : MIN_16;
    }
    return (Word16)result; 
}


static INLINE Word16 shr (Word16 var1, Word16 var2)
{
   Word32 result;

   if (var2 < 0)
   {
      result = var1 << var2;
      ASAT(result,result,16);
      //if(((result << 16)>>16) != result)
      //   result = (var1 > 0) ? MAX_16 : MIN_16;   
   }
   else
   {
      result = var1 >> var2;
   }

   return (Word16)result; 
}


static INLINE Word32 L_add (Word32 L_var1, Word32 L_var2)
{
   int dst;
   AADD32_S(dst,L_var1,L_var2);
   return dst;
}

static INLINE Word32 L_sub (Word32 L_var1, Word32 L_var2)
{
   int dst;
   ASUB32_S(dst,L_var1,L_var2);
   return dst;
}

static INLINE Word16 L_round (Word32 L_var1)
{
    Word16 var_out;
    Word32 L_rounded;
    
    AADD32_S(L_rounded,L_var1,0x00008000L);
    var_out = (Word16) (L_rounded >> 16);
    return (var_out);
}

static INLINE Word32 L_shl (Word32 L_var1, Word16 var2)
{
   int dst;
   ABSA_S(dst,L_var1,(Word32)(-var2));
   return dst;
}
static INLINE Word32 L_shr (Word32 L_var1, Word16 var2)
{
   int dst;
   ABSA_S(dst,L_var1,(Word32)(var2));
   return dst;
}

static INLINE Word16 norm_s (Word16 var1)
{
   int dst;
   if(var1 == 0)
      dst = 0;
   else
   {
      AEXP16(dst,(Word32)var1);
   }
   return (Word16)dst;
}

static INLINE Word16 norm_l (Word32 L_var1)
{
   int dst;
   if(L_var1 == 0)
      dst = 0;
   else
   {
      AEXP(dst,L_var1);
   }
   return dst;
}


#endif 


