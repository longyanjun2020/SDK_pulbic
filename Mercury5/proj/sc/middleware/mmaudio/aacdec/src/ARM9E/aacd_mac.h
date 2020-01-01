#ifndef _AAC_DECODER_MAC_INCLUDE_FILE
#define _AAC_DECODER_MAC_INCLUDE_FILE


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


/*static INLINE int arm9e_dsp_smlawb(int A, int B, int C)    //((A[31:0] * B[15:0])>>16)+C[31:0]
{
   B <<= 16;
   B >>= 16;
   return (int)(((int64_t)(A)*(int64_t)(B)) >> 16)+C;
}*/
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



#define il_BF_MAD2_t(a,b,c,dest) \
do { \
   arm9e_dsp_smulwb(dest,a,c); \
   arm9e_dsp_smlawt(dest,b,c,dest); \
   arm9e_dsp_qadd(dest,dest,dest); \
} while(0)

//can't use qsub to replace with sub
#define il_BF_MSU2_t(a,b,c,dest) \
do { \
   int s; \
   arm9e_dsp_smulwb(dest,a,c); \
   arm9e_dsp_smulwt(s,b,c); \
   dest = dest-s; \
   arm9e_dsp_qadd(dest,dest,dest); \
} while(0)

#define il_BF_MAD2(a,b,c,dest) \
do { \
   int s; \
   arm9e_dsp_smulwb(s,a,c); \
   arm9e_dsp_smlawt(s,b,c,s); \
   arm9e_dsp_qadd(s,s,s); \
   dest = s; \
} while(0)
 
//can't use qsub to replace with sub
#define il_BF_MSU2(a,b,c,dest) \
do { \
   int s,d; \
   arm9e_dsp_smulwb(d,a,c); \
   arm9e_dsp_smulwt(s,b,c); \
   s = d - s; \
   arm9e_dsp_qadd(s,s,s); \
   dest = s; \
} while(0)



#define il_MLA_CH2(a,b,c,dest) \
do { \
   int s; \
   arm9e_dsp_smulwb(s,a,b); \
   arm9e_dsp_qadd(s,s,c); \
   dest = s; \
} while(0)

#define il_MLA_CL2(a,b,c,dest) \
do { \
   int s; \
   arm9e_dsp_smulwt(s,a,b); \
   arm9e_dsp_qadd(s,s,c); \
   dest = s; \
} while(0)



#define il_MUL_DH2(a,b,dest) \
do { \
   int s; \
   arm9e_dsp_smulwb(s,a,b); \
   dest = s; \
} while(0)

#define il_MUL_DL2(a,b,dest) \
do { \
   int s; \
   arm9e_dsp_smulwt(s,a,b); \
   dest = s; \
} while(0)


#define il_MUL_DEQ(a,b,dest) \
do { \
   arm9e_smull_hi(dest,a,b); \
   arm9e_dsp_qadd(dest,dest,dest); \
} while(0)

#define il_IS_MUL(a,b,dest) \
do { \
   arm9e_dsp_smulwt(dest,a,b); \
   arm9e_dsp_qadd(dest,dest,dest); \
} while(0)


//can't use qdadd to replace with c=a+(b*2)
#define MAC_TNS_LPC1(a,b,c,dest)  \
do { \
   arm9e_smull_hi(dest,a,b); \
   dest = c+(dest<<1); \
} while(0)


#define MAC_TNS_LPC2(a,b,y)  \
do { \
   int hi; \
   arm9e_smull_hi(hi,a,b); \
   y += hi; \
} while(0)




//------------------------------------
//PNS
//------------------------------------
#define AMULL_14(a,b,dest) \
{ \
   arm9e_dsp_smulwb(dest,a,b); \
   dest = dest << 2;\
} 
//the a1 of AMULL_15 is only short register
//can't use qdadd to replace with c=a+(b*2)
#define AMULL_15(a,b,dest) \
{ \
   int s; \
   arm9e_dsp_smulwb(s,a,b); \
   dest = dest+(s<<1); \
} 
#define AMULL_30(a,b,dest) \
{ \
   arm9e_smull_hi(dest,a,b); \
   dest = dest << 2;\
} 
#define AMACL_30(a,b,dest) \
{ \
   int hi; \
   arm9e_smull_hi(hi,a,b); \
   dest += (hi<<2); \
} 


static INLINE int DIV28_14(int b) 
{  
   int a,i,exp;
   unsigned int xx;
   int q;

   a = (1<<28);
   xx = b;
   for(exp = 32; xx < 0x80000000; exp--) 
       xx <<= 1;
   q = 0;
   for(i=28-exp;i >=0 ;i--)
   {
      if(a > (b<<i))
      {
         q += (1<<i);
         a -= (b<<i);
      }
   }
   return q;
}


//--------------------------------------------------
// must use 32 * 32 multiplication
//--------------------------------------------------
#define pns_rand(seed) \
{ \
   seed = (int)(((unsigned int)1664525 * (unsigned int)(seed)) + (unsigned int)1013904223); \
} while(0) 
//--------------------------------------------------
//--------------------------------------------------
static INLINE int norm_log(int x,int *nor_var)
{
   int exp;// the position of first '1'+ 1
   unsigned int xx = x;
 
   for(exp = 32; xx < 0x80000000; exp--) 
       xx <<= 1;

   *nor_var = xx & 0x7fffffff;
   return exp;
}


static INLINE void aac_byte_align(aac_dec *pad)
{
   pad->frame_left -= (pad->ado_cache_left & 0x07);
   pad->ado_cache_left &= 0xf8;
}

static INLINE void aac_bit_flush(aac_dec *pad,int len)
{
   pad->ado_cache_left -= len; 
   pad->frame_left -= len;
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static INLINE int aac_append_cache(aac_dec *pad)
{
   
   if(pad->buf_left==0)   //是否這兩行code可以被deleted.
      aac_next_granule(pad);

   pad->ado_cache = (pad->ado_cache<<8) | ((*pad->ado_cache_ptr++) & 0x00ff);
   pad->ado_cache_left += 8;
   pad->buf_left--;

   return 1;
}

//-------------------------------------------------------------------------
// aac_bit_view len = 0 ~ 23
//-------------------------------------------------------------------------
static INLINE unsigned int aac_bit_view(aac_dec *pad,int len)
{
   unsigned int val;
   
   if(len > pad->frame_left)
   {
      if(pad->ado_cache_left < len)
      {
         int bn = (pad->frame_left-pad->ado_cache_left)>>3;
         while(bn > 0 && pad->ado_cache_left <= 24)
         {
            aac_append_cache(pad); 
            bn--;
         }
         val = (pad->ado_cache << (len-pad->ado_cache_left)) & ((1<<len)-1);
      }
      else
         val = (pad->ado_cache >> (pad->ado_cache_left-len)) & ((1<<len)-1);  //impossible 
      return val;
   }

   while(pad->ado_cache_left < len)
   {
      aac_append_cache(pad);  
   }
   val = (pad->ado_cache >> (pad->ado_cache_left-len)) & ((1<<len)-1);   
   return val;
}





#endif



