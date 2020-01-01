#ifndef __GCK_MAC_INCLUDE_FILE__
#define __GCK_MAC_INCLUDE_FILE__

#include "coder.h"

#ifdef _aeon_mac_
S64 macr_a0,macr_a1;  //MAC use
int temp_mac;

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
#else
static __inline void mstar_aeon_hardware_init(void)
{

}
#endif


#ifdef _aeon_mac_
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

#ifdef _aeon_mac_

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
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280b)); \
}

#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x2809)); \
}
#define GET_MACR_a1_low(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280b)); \
}
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("b.mfspr1 %0,%1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a1_high(dst) \
{ \
   asm volatile("b.mfspr1 %0,%1":"=r"(dst):"i"(0x280c)); \
}
//asm volatile("l.nop"); \for AEONR2 , we can ignore this
#define GET_MACR_a0_high_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0,%1":"=r"(dst):"i"(0x280a)); \
}
//asm volatile("l.nop"); \for AEONR2 , we can ignore this
#define GET_MACR_a1_high_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0,%1":"=r"(dst):"i"(0x280c)); \
}
#define AMULL(Dst,A,B) \
{ \
   asm volatile("l.amull %0,%1,%2":"=r"(Dst):"r"(A),"r"(B)); \
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
#define CLR_MACR_a0 \
{ \
   macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   macr_a1 = 0; \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(macr_a1>>n); \
}

#define GET_MACR_RND_a0(dst,n) \
{ \
   dst = (int)((macr_a0+(1<<(n-1)))>>n); \
}

#define GET_MACR_RND_a1(dst,n) \
{ \
   dst = (int)((macr_a1+(1<<(n-1)))>>n); \
}

#define GET_MACR_a0_low(dst) \
{ \
   dst = (int)(macr_a0); \
}
#define GET_MACR_a1_low(dst) \
{ \
   dst = (int)(macr_a1); \
}
#define GET_MACR_a0_high(dst) \
{ \
   dst = (int)(macr_a0>>32); \
}
#define GET_MACR_a1_high(dst) \
{ \
	dst = (int)(macr_a1>>32); \
}
#define GET_MACR_RND_a0_nop GET_MACR_RND_a0
#define GET_MACR_a0_low_nop GET_MACR_a0_low
#define GET_MACR_a1_low_nop GET_MACR_a1_low
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0_nop GET_MACR_a0
#define GET_MACR_a1_nop GET_MACR_a1
#define GET_MACR_a0_high_nop GET_MACR_a0_high
#define GET_MACR_a1_high_nop GET_MACR_a1_high

#define AMULL(Dst,A,B) \
{ \
   Dst = (int)((S64)(A)*(S64)(B)); \
}

#define AMULL_a0(A,B) \
{ \
   macr_a0 = ((S64)(A)*(S64)(B)); \
}

#define AMULL_a1(A,B) \
{ \
   macr_a1 = ((S64)(A)*(S64)(B)); \
}

#define AMACL_a0(A,B) \
{ \
   macr_a0 += ((S64)(A)*(S64)(B)); \
}

#define AMACL_a1(A,B) \
{ \
   macr_a1 += ((S64)(A)*(S64)(B)); \
}
#define AMSBL_a0(A,B) \
{ \
   macr_a0 -= ((S64)(A)*(S64)(B)); \
}

#define AMSBL_a1(A,B) \
{ \
   macr_a1 -= ((S64)(A)*(S64)(B)); \
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


#ifdef _aeon_mac_
#define D_LIMIT_16BITS(x) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(x):"r"(x),"i"(16)); \
}
#define D_LIMIT_24BITS(x) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(x):"r"(x),"i"(24)); \
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

#else
// 16Bit boundary check
#define D_LIMIT_16BITS(x) \
if ( x > MAX_16 )         \
{    x = MAX_16;}         \
else if ( x < MIN_16 )    \
{    x = MIN_16;}

#define D_LIMIT_24BITS(x) \
if ( x > 8388607 )         \
{    x = 8388607;}         \
else if ( x < (-8388608) )    \
{    x = (-8388608);}

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

#endif
#endif


