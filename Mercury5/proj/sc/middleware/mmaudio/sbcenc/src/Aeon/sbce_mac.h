#ifndef _SBC_ENCODER_INCLUDE_MAC_HEADER_FILE_
#define _SBC_ENCODER_INCLUDE_MAC_HEADER_FILE_


#define AMACR_KEEP 16   // keep
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift

#ifdef __aeon__
#define MAX_SPRS_PER_GRP_BITS (11)
#define SPRGROUP_MAC	(5<< MAX_SPRS_PER_GRP_BITS)
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

#define mstar_aeon_hardware_init L_MTSPR1(SPR_AMACCFG, 1)

#else
#define mstar_aeon_hardware_init 
#endif



#if defined(__aeon__) 


#define GET_MACR_a0(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a0_low(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x2809)); \
}


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


#else


#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(sbce_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(sbce_macr_a1>>n); \
}

#define GET_MACR_a0_low(dst) \
{ \
   dst = (int)(sbce_macr_a0); \
}

#define AMULL_a0(A,B) \
{ \
   sbce_macr_a0 = ((S64)(A)*(S64)(B)); \
}
#define AMACL_a0(a,b) \
{ \
   sbce_macr_a0 += ((S64)(a)*(S64)(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   sbce_macr_a0 -= ((S64)(a)*(S64)(b)); \
}
#define AMULL_a1(A,B) \
{ \
   sbce_macr_a1 = ((S64)(A)*(S64)(B)); \
}
static S64 sbce_macr_a0,sbce_macr_a1;



#endif




#endif

