#ifndef _SBC_ENCODER_INCLUDE_MAC_HEADER_FILE_
#define _SBC_ENCODER_INCLUDE_MAC_HEADER_FILE_

#if defined(__MIPS_4KE__) || defined(WIN32)
//on MIPS4KE, compiler will use mull/mfhi only
//L_tmp += (S64)dd*xx; compiler will use madd instruction

#define AMULL_31(dst,x, y) \
{ \
   S64 lo64; \
   lo64 = ((S64)x * (S64)y); \
   dst = (int)(lo64 >> 32); \
   dst = dst+dst; \
}

#define L_tmp_DEFINE S64 L_tmp

#define AMUL16x16(Rd,Rm,Rs) \
{ \
   Rd = (S64)Rm*Rs; \
}

#define AMAC16x16(Rd,Rm,Rs,Rn) \
{ \
   Rd = Rn+(S64)Rm*Rs; \
}

#elif defined(__ARM9E_GNU__)


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

#define AMULL_31(dst,x, y) \
{ \
   arm9e_smull_hi(dst,x,y); \
   dst = dst+dst; \
}
#define L_tmp_DEFINE int L_tmp
#define  AMUL16x16 arm9e_dsp_smulbb
#define  AMAC16x16 arm9e_dsp_smlabb

#elif defined(__ARM9E_RVDS22__)


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

#define AMULL_31(dst,x, y) \
{ \
   arm9e_smull_hi(dst,x,y); \
   dst = dst+dst; \
}
#define L_tmp_DEFINE int L_tmp
#define  AMUL16x16 arm9e_dsp_smulbb
#define  AMAC16x16 arm9e_dsp_smlabb

#elif defined(__ARM9E_WINCE__)

#include <Armintr.h>

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

#define AMULL_31(dst,x, y) \
{ \
   arm9e_smull_hi(dst,x,y); \
   dst = dst+dst; \
}
#define L_tmp_DEFINE int L_tmp
#define  AMUL16x16 arm9e_dsp_smulbb
#define  AMAC16x16 arm9e_dsp_smlabb

#else



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



#define AMULL_31(dst,x, y) \
{ \
   arm9e_smull_hi(dst,x,y); \
   dst = dst+dst; \
}

#define L_tmp_DEFINE int L_tmp
#define  AMUL16x16 arm9e_dsp_smulbb
#define  AMAC16x16 arm9e_dsp_smlabb

#endif




#endif

