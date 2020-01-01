#ifndef __MP3_ENC_MAC_INCLUDE_FILE__
#define __MP3_ENC_MAC_INCLUDE_FILE__



#if defined(__ARM9E_GNU__)

#define arm9e_clz(Rd,Rm) \
{ \
   asm volatile("clz %0, %1": "=r"(Rd): "r"(Rm)); \
}

#define arm9e_smull(Rdhi,Rdlo,Rm,Rs) \
{ \
   asm volatile("smull %0, %1, %2, %3": "=r"(Rdlo),"=r"(Rdhi): "r"(Rm), "r"(Rs)); \
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

#define arm9e_dsp_smulbb(Rd,Rm,Rs) \
{ \
   asm volatile("smulbb %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rs)); \
} 

#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn) \
{ \
   asm volatile("smlabb %0, %1, %2, %3": "=r"(Rd): "r"(Rm), "r"(Rs), "r"(Rn)); \
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

#define arm9e_clz(Rd,Rm) \
{ \
   __asm { \
      clz   Rd,Rm; \
   } \
}


#define arm9e_smull(Rdhi,Rdlo,Rm,Rs) \
{ \
   __asm { \
      smull   Rdlo,Rdhi,Rm,Rs; \
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
#define arm9e_dsp_smulbb(Rd,Rm,Rs) \
{ \
   __asm { \
      smulbb   Rd,Rm,Rs; \
   } \
} 

#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn) \
{ \
   __asm { \
      smlabb   Rd,Rm,Rs,Rn; \
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
#include <cmnintrin.h>

#define arm9e_clz(Rd,Rm)  Rd = _CountLeadingZeros(Rm)

#define arm9e_smull(Rdhi,Rdlo,Rm,Rs) \
{ \
   S64 Rd = ((S64)(Rm) * (Rs)); \
   Rdlo = (unsigned int)Rd; \
   Rdhi = (int)(Rd>>32); \
}

#define arm9e_smull_hi(Rdhi,Rm,Rs)     Rdhi = (int)_MulHigh(Rm,Rs)
#define arm9e_dsp_smulwb(Rd,Rm,Rs)     Rd = _SmulWLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smulwt(Rd,Rm,Rs)     Rd = _SmulWHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)  Rd = _SmulAddWLo_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn)  Rd = _SmulAddWHi_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_smulbb(Rd,Rm,Rs)     Rd = _SmulLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn)  Rd = _SmulAddLo_SW_SL(Rn,Rm,Rs)

#define arm9e_dsp_qadd(Rd,Rm,Rn)       Rd = _AddSatInt(Rm,Rn)
#define arm9e_dsp_qsub(Rd,Rm,Rn)       Rd = _SubSatInt(Rm,Rn)
#define arm9e_dsp_qdadd(Rd,Rm,Rn)      Rd = _DAddSatInt(Rm,Rn)
#define arm9e_dsp_qdsub(Rd,Rm,Rn)      Rd = _DSubSatInt(Rm,Rn)

#else

//arm9e_clz:  0(negative)  , 1(0x40000000), 2(0x20000000),...,31(0x00000001),32(0x00000000)
#define arm9e_clz(Rd,Rm) \
{ \
   int _Rm = Rm; \
   if(_Rm==0) \
      Rd = 32; \
   else if(_Rm < 0) \
      Rd = 0; \
   else \
   { \
      for(Rd = 0; _Rm < (unsigned int) 0x80000000; Rd++) \
      { \
         _Rm <<= 1; \
      } \
   } \
}

#define arm9e_smull(Rdhi,Rdlo,Rm,Rs) \
{ \
   S64 Rd = ((S64)(Rm) * (Rs)); \
   Rdlo = (unsigned int)Rd; \
   Rdhi = (int)(Rd>>32); \
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

#define arm9e_dsp_smulbb(Rd,Rm,Rs) \
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = (int)((Rmc) * (Rsc)); \
} 

#define arm9e_dsp_smlabb(Rd,Rm,Rs,Rn) \
{ \
   int Rsc = ((Rs)<<16)>>16; \
   int Rmc = ((Rm)<<16)>>16; \
   Rd = Rn + ((Rmc) * (Rsc)); \
} 

#define arm9e_dsp_qadd(Rd,Rm,Rn) \
{ \
   Rd = Rm+Rn; \
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

#endif


#define SCLZ    arm9e_clz

#define SMULL_WT(Rd,Rm,Rs) arm9e_dsp_smulwt(Rd,Rm,Rs)
#define SMACL_WT(Rd,Rm,Rs) arm9e_dsp_smlawt(Rd,Rm,Rs,Rd)
#define SMSBL_WT(Rd,Rm,Rs) \
{  \
   int _Rm_ = -Rm; \
   arm9e_dsp_smlawt(Rd,_Rm_,Rs,Rd); \
}

#define SMULL_WB(Rd,Rm,Rs) arm9e_dsp_smulwb(Rd,Rm,Rs)
#define SMACL_WB(Rd,Rm,Rs) arm9e_dsp_smlawb(Rd,Rm,Rs,Rd)

#define SMSBL_WB(Rd,Rm,Rs) \
{  \
   int _Rm_ = -Rm; \
   arm9e_dsp_smlawb(Rd,_Rm_,Rs,Rd); \
}


#define SMULL_HIGH(Rd,Rm,Rs)  arm9e_smull_hi(Rd,Rm,Rs)

#define SMULL_MACR_n(Rd,Rm,Rs,n) \
{ \
   unsigned int Rdlo; \
   int Rdhi; \
   arm9e_smull(Rdhi,Rdlo,Rm,Rs); \
   Rd = (Rdhi << (32-n)) | (Rdlo >> n); \
}

#ifdef USING_MAC_32x32
#define SMULL_WB_HIGH SMULL_HIGH
#else
#define SMULL_WB_HIGH SMULL_WB  
#endif

#endif

