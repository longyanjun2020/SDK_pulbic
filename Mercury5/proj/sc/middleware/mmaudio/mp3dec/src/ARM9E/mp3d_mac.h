#ifndef _MP3_DECODER_MAC_INCLUDE_FILE_ 
#define _MP3_DECODER_MAC_INCLUDE_FILE_

#ifdef __ARM9E_GNU__
#define MP3D_MEM_ALIGN
#elif defined(__ARM9E_RVDS22__)
//#define DCACHE_LINE     16
//#define MP3D_MEM_ALIGN  __attribute__((aligned(DCACHE_LINE)))
#define MP3D_MEM_ALIGN
#elif defined(__ARM9E_WINCE__)
#define MP3D_MEM_ALIGN
#else
#define MP3D_MEM_ALIGN
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifdef __ARM9E_GNU__

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

#define arm9e_dsp_qdadd(Rd,Rm,Rn) \
{ \
   asm volatile("qdadd %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}

#define arm9e_dsp_qdsub(Rd,Rm,Rn) \
{ \
   asm volatile("qdsub %0, %1, %2": "=r"(Rd): "r"(Rm), "r"(Rn)); \
}

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

#define arm9e_dsp_qadd(Rd,Rm,Rn) \
{ \
   __asm { \
      qadd     Rd,Rm,Rn; \
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

#define arm9e_smull_hi(Rdhi,Rm,Rs)     Rdhi = (int)_MulHigh(Rm,Rs)
#define arm9e_dsp_smulwb(Rd,Rm,Rs)     Rd = _SmulWLo_SW_SL(Rm,Rs)
#define arm9e_dsp_smulwt(Rd,Rm,Rs)     Rd = _SmulWHi_SW_SL(Rm,Rs)
#define arm9e_dsp_smlawb(Rd,Rm,Rs,Rn)  Rd = _SmulAddWLo_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_smlawt(Rd,Rm,Rs,Rn)  Rd = _SmulAddWHi_SW_SL(Rn,Rm,Rs)
#define arm9e_dsp_qadd(Rd,Rm,Rn)       Rd = _AddSatInt(Rm,Rn)
#define arm9e_dsp_qdadd(Rd,Rm,Rn)      Rd = _DAddSatInt(Rm,Rn)
#define arm9e_dsp_qdsub(Rd,Rm,Rn)      Rd = _DSubSatInt(Rm,Rn)
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

#define arm9e_dsp_qadd(Rd,Rm,Rn) \
{ \
   Rd = Rm+Rn; \
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

//-------------------------------------------------------
//-------------------------------------------------------
#define MUL_DEQ(A,B,D) arm9e_smull_hi(D,A,B)
#define MAR_DEQ(dst) arm9e_dsp_qadd(dst,dst,dst)
//--------------------------------------------------------
//--------------------------------------------------------
#define dct_f_mul_b(x,y,dst) \
{ \
   arm9e_dsp_smulwb(dst,x,y); \
   arm9e_dsp_qadd(dst,dst,dst); \
}
#define dct_f_mul_t(x,y,dst) \
{ \
   arm9e_dsp_smulwt(dst,x,y); \
   arm9e_dsp_qadd(dst,dst,dst); \
}


//--------------------------------------------------------
//--------------------------------------------------------
#define iml_f_mul_b dct_f_mul_b 
#define iml_f_mul_t dct_f_mul_t 

//--------------------------------------------------------
//--------------------------------------------------------
#define IML_N_ML0_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define IML_N_MLA_b(x,y,dst) arm9e_dsp_smlawb(dst,x,y,dst) 
#define IML_N_MLA_t(x,y,dst) arm9e_dsp_smlawt(dst,x,y,dst) 
#define IML_N_MLZ(dst) arm9e_dsp_qadd(dst,dst,dst)


//--------------------------------------------------------
//for ms coding
//--------------------------------------------------------
#define STO_MS_MUL_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define STO_MS_MAR(dst) arm9e_dsp_qadd(dst,dst,dst)
//--------------------------------------------------------
//--------------------------------------------------------
#define STO_IS_MUL_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define STO_IS_MUL_t(x,y,dst) arm9e_dsp_smulwt(dst,x,y)
#define STO_IS_MAR(dst) arm9e_dsp_qadd(dst,dst,dst)


//--------------------------------------------------------
//--------------------------------------------------------
#define ALI_F_ML0_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define ALI_F_MLA_t(x,y,dst) arm9e_dsp_smlawt(dst,x,y,dst) 
#define ALI_F_MLZ(dst) arm9e_dsp_qadd(dst,dst,dst)

//--------------------------------------------------------
//--------------------------------------------------------
#define IMS_F_ML0_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define IMS_F_ML0_t(x,y,dst) arm9e_dsp_smulwt(dst,x,y)
#define IMS_F_MLA_b(x,y,dst) arm9e_dsp_smlawb(dst,x,y,dst) 
#define IMS_F_MLA_t(x,y,dst) arm9e_dsp_smlawt(dst,x,y,dst) 
#define IMS_F_MLZ(dst) arm9e_dsp_qadd(dst,dst,dst)
//--------------------------------------------------------
//--------------------------------------------------------
#define SYN_F_ML0_b(x,y,dst) arm9e_dsp_smulwb(dst,x,y)
#define SYN_F_ML0_t(x,y,dst) arm9e_dsp_smulwt(dst,x,y)
#define SYN_F_MLA_b(x,y,dst) arm9e_dsp_smlawb(dst,x,y,dst) 
#define SYN_F_MLA_t(x,y,dst) arm9e_dsp_smlawt(dst,x,y,dst) 
#define SYN_F_MLZ(dst) arm9e_dsp_qadd(dst,dst,dst)


#endif

