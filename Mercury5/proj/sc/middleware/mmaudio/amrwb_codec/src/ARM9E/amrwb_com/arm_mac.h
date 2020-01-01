 

#ifdef __ARM9E_GNU__

#define arm9e_dsp_smultt(Rd,Rm,Rs)     \
{ \
   asm volatile("smultt %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}
#define arm9e_dsp_smultb(Rd,Rm,Rs)     \
{ \
   asm volatile("smultb %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}
#define arm9e_dsp_smulbb(Rd,Rm,Rs)     \
{ \
   asm volatile("smulbb %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}
#define arm9e_dsp_smulbt(Rd,Rm,Rs)     \
{ \
   asm volatile("smulbt %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}
#define arm9e_dsp_smlatt(Rd,Rm,Rs,Rn)  \
{ \
   asm volatile("smlatt %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}
#define arm9e_dsp_smlatb(Rd,Rm,Rs,Rn)  \
{ \
   asm volatile("smlatb %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}
#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn)  \
{ \
   asm volatile("smlabb %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}
#define arm9e_dsp_smlabt(Rd,Rm,Rs,Rn)  \
{ \
   asm volatile("smlabt %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}

#define arm9e_smull_hi(Rdhi,Rm,Rs) \
{ \
   int Rdlo; \
   asm volatile("smull %0, %1, %2, %3": "=r"(Rdlo),"=r"(Rdhi): "r"(Rm), "r"(Rs)); \
   Rdlo = Rdlo; \
}

#define arm9e_dsp_smulwb(Rd,Rm,Rs) \
{ \
   asm volatile("smulwb %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}

#define arm9e_dsp_smulwt(Rd,Rm,Rs) \
{ \
   asm volatile("smulwt %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
}

#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)\
{ \
   asm volatile("smlawb %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}

#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn) \
{ \
   asm volatile("smlawt %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
}

#define arm9e_dsp_qadd(Rd,Rm,Rn) \
{ \
   asm volatile("qadd %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}
#define arm9e_dsp_qsub(Rd,Rm,Rn) \
{ \
   asm volatile("qsub %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}

#define arm9e_dsp_qdadd(Rd,Rm,Rn) \
{ \
   asm volatile("qdadd %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}

#define arm9e_dsp_qdsub(Rd,Rm,Rn) \
{ \
   asm volatile("qdsub %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}

#elif defined(__ARM9E_RVDS22__) 

#define arm9e_dsp_smultt(Rd,Rm,Rs)\
{ \
   __asm { \
      smultt   Rd,Rm,Rs; \
   } \
} 

#define arm9e_dsp_smultb(Rd,Rm,Rs)\
{ \
   __asm { \
      smultb   Rd,Rm,Rs; \
   } \
} 
#define arm9e_dsp_smulbb(Rd,Rm,Rs)\
{ \
   __asm { \
      smulbb  Rd,Rm,Rs; \
   } \
} 
#define arm9e_dsp_smulbt(Rd,Rm,Rs)\
{ \
   __asm { \
      smulbt   Rd,Rm,Rs; \
   } \
} 


#define arm9e_dsp_smlatt(Rd,Rm,Rs,Rn)\
{ \
   __asm { \
      smlatt   Rd,Rm,Rs,Rn; \
   } \
} 

#define arm9e_dsp_smlatb(Rd,Rm,Rs,Rn)\
{ \
   __asm { \
      smlatb   Rd,Rm,Rs,Rn; \
   } \
} 
#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn)\
{ \
   __asm { \
      smlabb   Rd,Rm,Rs,Rn; \
   } \
} 
#define arm9e_dsp_smlabt(Rd,Rm,Rs,Rn)\
{ \
   __asm { \
      smlabt   Rd,Rm,Rs,Rn; \
   } \
} 

#define arm9e_smull_hi(Rdhi,Rm,Rs) \
{ \
   int Rdlo; \
   __asm { \
      smull   Rdlo,Rdhi,Rm,Rs; \
   } \
   Rdlo = Rdlo; \
}
#define arm9e_dsp_smulwb(Rd,Rm,Rs) \
{ \
   __asm { \
      smulwb   Rd,Rm,Rs; \
   } \
} 

#define arm9e_dsp_smulwt(Rd,Rm,Rs) \
{ \
   __asm { \
      smulwt   Rd,Rm,Rs; \
   } \
} 

#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)\
{ \
   __asm { \
      smlawb   Rd,Rm,Rs,Rn; \
   } \
} 

#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn) \
{ \
   __asm { \
      smlawt   Rd,Rm,Rs,Rn; \
   } \
} 

#define arm9e_dsp_qadd(Rd,Rm,Rn) \
{ \
   __asm { \
      qadd     Rd,Rm,Rn; \
   } \
}
#define arm9e_dsp_qsub(Rd,Rm,Rn) \
{ \
   __asm { \
      qsub     Rd,Rm,Rn; \
   } \
}
#define arm9e_dsp_qdadd(Rd,Rm,Rn) \
{ \
   __asm { \
      qdadd     Rd,Rm,Rn; \
   } \
}
#define arm9e_dsp_qdsub(Rd,Rm,Rn) \
{ \
   __asm { \
      qdsub     Rd,Rm,Rn; \
   } \
}
#elif defined(__ARM9E_WINCE__)

#include <Armintr.h>

#define arm9e_dsp_smultt(Rd,Rm,Rs)     Rd = _SmulHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smultb(Rd,Rm,Rs)     Rd = _SmulHiLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smulbb(Rd,Rm,Rs)     Rd = _SmulLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smulbt(Rd,Rm,Rs)     Rd = _SmulLoHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smlatt(Rd,Rm,Rs,Rn)  Rd = _SmulAddHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smlatb(Rd,Rm,Rs,Rn)  Rd = _SmulAddHiLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn)  Rd = _SmulAddLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smlabt(Rd,Rm,Rs,Rn)  Rd = _SmulAddLoHi_SW_SL(Rm,Rs)
#define arm9e_smull_hi(Rdhi,Rm,Rs)     Rdhi = (int)_MulHigh(Rm,Rs)
#define arm9e_dsp_smulwb(Rd,Rm,Rs)     Rd = _SmulWLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smulwt(Rd,Rm,Rs)     Rd = _SmulWHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)  Rd = _SmulAddWLo_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn)  Rd = _SmulAddWHi_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_qadd(Rd,Rm,Rn)       Rd = _AddSatInt(Rm,Rn)
#define arm9e_dsp_qsub(Rd,Rm,Rn)       Rd = _SubSatInt(Rm,Rn)
#define arm9e_dsp_qdadd(Rd,Rm,Rn)      Rd = _DAddSatInt(Rm,Rn)
#define arm9e_dsp_qdsub(Rd,Rm,Rn)      Rd = _DSubSatInt(Rm,Rn)

#else


#define arm9e_dsp_smultt(Rd,Rm,Rs)\
{ \
   int Rsc = (Rs)>>16; \
   int Rmc = (Rm)>>16; \
   Rd = Rmc * Rsc; \
} 

#define arm9e_dsp_smultb(Rd,Rm,Rs)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = (Rm)>>16; \
   Rd = Rmc * Rsc; \
} 

#define arm9e_dsp_smulbb(Rd,Rm,Rs)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = Rmc * Rsc; \
} 

#define arm9e_dsp_smulbt(Rd,Rm,Rs)\
{ \
   int Rsc = (Rs)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = Rmc * Rsc; \
} 

 
#define arm9e_dsp_smlatt(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = (Rs)>>16; \
   int Rmc = (Rm)>>16; \
   Rd = Rn + Rmc * Rsc; \
} 

#define arm9e_dsp_smlatb(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = (Rm)>>16; \
   Rd = Rn + Rmc * Rsc; \
} 

#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = Rn + Rmc * Rsc; \
} 

#define arm9e_dsp_smlabt(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = (Rs)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = Rn + Rmc * Rsc; \
} 


#define arm9e_smull_hi(Rdhi,Rm,Rs) \
{ \
   Rdhi = (int)(((S64)(Rm) * (Rs))>>32); \
}
#define arm9e_dsp_smulwb(Rd,Rm,Rs) \
{ \
   int Rsc = ((Rs)<<16)>>16; \
   Rd = (int)(((S64)(Rm) * (Rsc))>>16); \
} 

#define arm9e_dsp_smulwt(Rd,Rm,Rs) \
{ \
   int Rsc = (Rs)>>16; \
   Rd = (int)(((S64)(Rm) * (Rsc))>>16); \
} 

#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   Rd = Rn+(int)(((S64)(Rm) * (Rsc))>>16); \
} 

#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn) \
{ \
   int Rsc = (Rs)>>16; \
   Rd = Rn+(int)(((S64)(Rm) * (Rsc))>>16); \
} 
 

#define arm9e_dsp_qadd(Rd,Rm,Rn)                             \
{                                                            \
   int Rdc = Rm+Rn;                                          \
   if ((Rm & 0x80000000) == (Rn & 0x80000000))               \
   {                                                         \
      if ((Rdc & 0x80000000) != (Rm & 0x80000000))           \
      {                                                      \
          Rd = (Rm & 0x80000000)? 0x80000000 : 0x7fffffff;   \
      }                                                      \
      else                                                   \
      {                                                      \
          Rd = Rdc;                                          \
      }                                                      \
   }                                                         \
   else                                                      \
   {                                                         \
       Rd = Rdc;                                             \
   }                                                         \
}

#define arm9e_dsp_qsub(Rd,Rm,Rn) \
{ \
   Rd = Rm-Rn; \
}
#define arm9e_dsp_qdadd(Rd,Rm,Rn) \
{ \
   Rd = Rm+2*Rn; \
}
#define arm9e_dsp_qdsub(Rd,Rm,Rn) \
{ \
   Rd = Rm-2*Rn; \
}

#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)\
{ \
   int Rsc = ((Rs)<<16)>>16; \
   Rd = Rn+(int)(((S64)(Rm) * (Rsc))>>16); \
} 

#endif

 
#define arm9e_dsp_smlabb_sat(Rd,Rm,Rs,Rn)\
{ \
   int Rdd;                     \
   arm9e_dsp_smulbb(Rdd,Rm,Rs); \
   arm9e_dsp_qadd(Rd,Rdd,Rn);   \
} 

 

#define Mpy_32_16(L_32, var1, var2) \
{ \
   L_32 = (var1) & 0xfffffffe; \
   AMULL_a0(L_32,((var2)<<16)); \
   GET_MACR_high(L_32); \
   L_32 = L_32<<1; \
}

