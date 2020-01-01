#ifndef __MP3_ENC_MAC_INCLUDE_FILE__
#define __MP3_ENC_MAC_INCLUDE_FILE__


#define AMACR_KEEP  0x10 
#define AMACR_CLR   8   // clear
#define AMACR_RND   4   // round
#define AMACR_SAT   2   // saturate
#define AMACR_SHR   1   // shift
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
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_KEEP), "i"(n)); \
}

#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR|AMACR_KEEP), "i"(n)); \
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
#define AMACL_a1(a,b) \
{ \
   asm volatile("l.amac a1,%0,%1"::"r"(a),"r"(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   asm volatile("l.amsb a1,%0,%1"::"r"(a),"r"(b)); \
}

#define SPR_AMACCFG   ((5<<11)+13)

#ifdef __AEONR2__
#define enable_amac(spr,val)                               \
    __asm__ volatile ("b.mtspr1\t%0,%1" : : "r"(val), "K"(spr))
#else

#define enable_amac(spr,val)                               \
    __asm__ volatile ("l.mtspr\tr0,%0,%1" : : "r"(val), "K"(spr))
#endif



#define mp3e_aeon_amac_init enable_amac(SPR_AMACCFG, 1)


#else
#define CLR_MACR_a0 \
{ \
   mp3e_macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   mp3e_macr_a1 = 0; \
}

#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(mp3e_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(mp3e_macr_a1>>n); \
}

#define AMULL_a0(A,B) \
{ \
   mp3e_macr_a0 = ((S64)(A)*(S64)(B)); \
}
#define AMACL_a0(a,b) \
{ \
   mp3e_macr_a0 += ((S64)(a)*(S64)(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   mp3e_macr_a0 -= ((S64)(a)*(S64)(b)); \
}

#define AMULL_a1(A,B) \
{ \
   mp3e_macr_a1 = ((S64)(A)*(S64)(B)); \
}

#define AMACL_a1(a,b) \
{ \
   mp3e_macr_a1 += ((S64)(a)*(S64)(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   mp3e_macr_a1 -= ((S64)(a)*(S64)(b)); \
}

#define mp3e_aeon_amac_init
static S64 mp3e_macr_a0,mp3e_macr_a1;

#endif


#endif

