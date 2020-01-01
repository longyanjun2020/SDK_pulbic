#ifndef _AAC_DECODER_MAC_INCLUDE_FILE
#define _AAC_DECODER_MAC_INCLUDE_FILE
 
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

#ifdef __aeon__
#define set_reg_volatile2(a,b)      __asm__ ("0:" : : "r"(a),"r"(b)); 
#define set_reg_volatile3(a,b,c)    __asm__ ("0:" : : "r"(a),"r"(b),"r"(c)); 
#define set_reg_volatile4(a,b,c,d)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d)); 
#define set_reg_volatile5(a,b,c,d,e)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e)); 
#define set_reg_volatile6(a,b,c,d,e,f)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f)); 
#define set_reg_volatile8(a,b,c,d,e,f,g,h)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f),"r"(g),"r"(h)); 
#define set_reg_volatile10(a,b,c,d,e,f,g,h,i,j)  __asm__ ("0:" : : "r"(a),"r"(b),"r"(c),"r"(d),"r"(e),"r"(f),"r"(g),"r"(h),"r"(i),"r"(j)); 
#else
#define set_reg_volatile2(a,b)
#define set_reg_volatile3(a,b,c)
#define set_reg_volatile4(a,b,c,d)
#define set_reg_volatile5(a,b,c,d,e)
#define set_reg_volatile6(a,b,c,d,e,f)
#define set_reg_volatile8(a,b,c,d,e,f,g,h)
#define set_reg_volatile10(a,b,c,d,e,f,g,h,i,j)
#endif

#ifdef __aeon__
//clz: count leading zero
//output= 0(0x80000000),1,2,...,31(0x00000001),0(0x00000000)
//fl1: find last one
//output=32(0x80000000),31,30,...,1(0x00000001),32(0x00000000)
//clz() = 32-fl1()
#define CLZ(A,cz) \
{ \
   asm volatile("l.fl1 %0,%1":"=r"(cz):"r"(A)); \
   cz = 32-cz; \
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
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a2(dst,n) \
{ \
   asm volatile("l.amacr %0, a2, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#ifdef __AEONR2__
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}

#define GET_MACR_a1_nop(dst,n) \
{ \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(dst): "i"(AMACR_SHR), "i"(n)); \
}
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a0_high_nop(dst) \
{ \
   asm volatile("b.mfspr1 %0, %1":"=r"(dst):"i"(0x280a)); \
}
#else
//-----------------------------------------------
//-----------------------------------------------
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
#define GET_MACR_a0_high(dst) \
{ \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280a)); \
}
#define GET_MACR_a0_high_nop(dst) \
{ \
   asm volatile("l.nop"); \
   asm volatile("l.mfspr %0, r0, %1":"=r"(dst):"i"(0x280a)); \
}

#endif

#define GET_MACR_add_a0(dst,n) \
{ \
   int tmp; \
   asm volatile("l.amacr %0, a0, %1, %2": "=r"(tmp): "i"(AMACR_SHR), "i"(n)); \
   dst += tmp; \
}

#define GET_MACR_add_a1(dst,n) \
{ \
   int tmp; \
   asm volatile("l.amacr %0, a1, %1, %2": "=r"(tmp): "i"(AMACR_SHR), "i"(n)); \
   dst += tmp; \
}

#ifdef __AEONR2__
#define AMULL(rd,ra,rb) \
{ \
   asm volatile("l.mul %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#else
#define AMULL(rd,ra,rb) \
{ \
   asm volatile("l.amull %0,%1,%2":"=r"(rd):"r"(ra),"r"(rb)); \
}
#endif

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
#define AMULWB_a2(a,b) \
{ \
   asm volatile("l.amul_wl a2,%0,%1"::"r"(a),"r"(b)); \
}
#define AMULWT_a2(a,b) \
{ \
   asm volatile("l.amul_wh a2,%0,%1"::"r"(a),"r"(b)); \
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
#define CLR_MACR_a0 \
{ \
   aad_macr_a0 = 0; \
}
#define CLR_MACR_a1 \
{ \
   aad_macr_a1 = 0; \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_a0(dst,n) \
{ \
   dst = (int)(aad_macr_a0>>n); \
}

#define GET_MACR_a1(dst,n) \
{ \
   dst = (int)(aad_macr_a1>>n); \
}
#define GET_MACR_a2(dst,n) \
{ \
   dst = (int)(aad_macr_a2>>n); \
}
//-----------------------------------------------
//-----------------------------------------------
#define GET_MACR_add_a0(dst,n) \
{ \
   dst += (int)(aad_macr_a0>>n); \
}

#define GET_MACR_add_a1(dst,n) \
{ \
   dst += (int)(aad_macr_a1>>n); \
}


#define GET_MACR_a0_nop GET_MACR_a0
#define GET_MACR_a1_nop GET_MACR_a1

#define GET_MACR_a0_high(dst) \
{ \
   dst = (int)(aad_macr_a0>>32); \
}
#define GET_MACR_a0_high_nop GET_MACR_a0_high


#define AMULL(rd,ra,rb) \
{ \
   rd = (int)((int64_t)(ra)*(int64_t)(rb)); \
}

#define AMULL_a0(A,B) \
{ \
   aad_macr_a0 = ((int64_t)(A)*(int64_t)(B)); \
}
#define AMACL_a0(a,b) \
{ \
   aad_macr_a0 += ((int64_t)(a)*(int64_t)(b)); \
}
#define AMSBL_a0(a,b) \
{ \
   aad_macr_a0 -= ((int64_t)(a)*(int64_t)(b)); \
}
#define AMULL_a1(A,B) \
{ \
   aad_macr_a1 = ((int64_t)(A)*(int64_t)(B)); \
}

#define AMACL_a1(a,b) \
{ \
   aad_macr_a1 += ((int64_t)(a)*(int64_t)(b)); \
}
#define AMSBL_a1(a,b) \
{ \
   aad_macr_a1 -= ((int64_t)(a)*(int64_t)(b)); \
}
#define AMULWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a0 = ((S64)(a)*(S64)(bx)); \
}
#define AMULWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a0 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a1 = ((S64)(a)*(S64)(bx)); \
}
#define AMULWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a1 = ((S64)(a)*(S64)(bx)); \
}

#define AMULWB_a2(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a2 = ((S64)(a)*(S64)(bx)); \
}
#define AMULWT_a2(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a2 = ((S64)(a)*(S64)(bx)); \
}


#define AMACWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a0 += ((S64)(a)*(S64)(bx)); \
}
#define AMACWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a0 += ((S64)(a)*(S64)(bx)); \
}

#define AMACWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a1 += ((S64)(a)*(S64)(bx)); \
}
#define AMACWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a1 += ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a0(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}
#define AMSBWT_a0(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a0 -= ((S64)(a)*(S64)(bx)); \
}

#define AMSBWB_a1(a,b) \
{ \
   int bx; \
   bx = (b<<16)>>16; \
   aad_macr_a1 -= ((S64)(a)*(S64)(bx)); \
}
#define AMSBWT_a1(a,b) \
{ \
   int bx; \
   bx = (b)>>16; \
   aad_macr_a1 -= ((S64)(a)*(S64)(bx)); \
}

#endif

#ifdef __aeon__
#define GET_HIMACR_a0(dest) \
{ \
    asm volatile("l.mfspr %0, r0, %1":"=r"(dest):"i"(0x280a)); \
}
#define GET_HIMACR_a1(dest) \
{ \
    asm volatile("l.mfspr %0, r0, %1":"=r"(dest):"i"(0x280c)); \
}
#else
#define GET_HIMACR_a0(dst) \
{ \
   dst = (int)(aad_macr_a0>>32); \
}
#define GET_HIMACR_a1(dst) \
{ \
   dst = (int)(aad_macr_a1>>32); \
}
#endif


#ifdef USE_AMAC_32x32
#define il_BF_MAD2_a0(a,b,c,d) \
{ \
   AMULL_a0(a,b); \
   AMACL_a0(c,d); \
}

#define il_BF_MSU2_a0(a,b,c,d) \
{ \
   AMULL_a0(a,b); \
   AMSBL_a0(c,d); \
}


#define il_BF_MAD2_a1(a,b,c,d) \
{ \
   AMULL_a1(a,b); \
   AMACL_a1(c,d); \
}


#define il_BF_MSU2_a1(a,b,c,d) \
{ \
   AMULL_a1(a,b); \
   AMSBL_a1(c,d); \
}

#else
#define il_BF_MAD2_a0(a,b,c) \
{ \
   AMULWB_a0(a,c); \
   AMACWT_a0(b,c); \
}

#define il_BF_MSU2_a0(a,b,c) \
{ \
   AMULWB_a0(a,c); \
   AMSBWT_a0(b,c); \
}


#define il_BF_MAD2_a1(a,b,c) \
{ \
   AMULWB_a1(a,c); \
   AMACWT_a1(b,c); \
}


#define il_BF_MSU2_a1(a,b,c) \
{ \
   AMULWB_a1(a,c); \
   AMSBWT_a1(b,c); \
}
#endif

#define il_MUL_DEQ(a,b,dest) \
{ \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(dest,31); \
}

//------------------------------------
//b coefficient < 2, so we scale 2^14 to coefficient;
#define il_IS_MUL(a,b,dest) \
{ \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(dest,31); \
}


//------------------------------------
//TNS
//------------------------------------
#define MAC_TNS_LPC1(a,b,c,dest)  \
{ \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(dest,31); \
   dest += c; \
}


#define MAC_TNS_LPC2(a,b,y)  \
{ \
   int tmp; \
   AMULL_a0(a,b); \
   GET_MACR_a0_high_nop(tmp); \
   y += tmp; \
}




//------------------------------------
//PNS
//------------------------------------
#define AMULL_14(a,b,dest) \
{ \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(dest,14); \
}

#define AMULL_15(a,b,dest) \
{ \
   int tmp; \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(tmp,15); \
   dest += tmp; \
}

/*#define AMULL_30(a,b,dest) \
{ \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(dest,30); \
}*/

/*#define AMACL_30(a,b,dest) \
{ \
   int tmp; \
   AMULL_a0(a,b); \
   GET_MACR_a0_nop(tmp,30); \
   dest += tmp; \
}*/


#ifdef __aeon__
#define ASAT(rD,rA,T) \
{ \
   asm volatile("l.sat %0,%1,%2":"=r"(rD):"r"(rA),"i"(T)); \
}
#else
#define ASAT(rD,rA,T) \
{ \
   int max = (1<<(T-1))-1; \
   int min = -(1<<(T-1)); \
   if ((int)(rA) > max) \
      (rD) = max; \
   else if ((int)(rA) < min) \
      (rD) = min; \
   else \
      (rD) = (rA); \
}
#endif

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

#define pns_rand(seed) \
{ \
   AMULL(seed,seed,1664525); \
   seed += 1013904223; \
}

//--------------------------------------------------
//--------------------------------------------------
#ifdef __aeon__
static INLINE int norm_log(int x,int *nor_var)
{
   int exp;// the position of first '1'+ 1
   unsigned int xx = x;
 
   for(exp = 32; xx < 0x80000000; exp--) 
       xx <<= 1;

   *nor_var = xx & 0x7fffffff;
   return exp;
}
#else
static INLINE int norm_log(int x,int *nor_var)
{
   int exp;// the position of first '1'+ 1
   unsigned int xx = x;
 
   for(exp = 32; xx < 0x80000000; exp--) 
       xx <<= 1;

   *nor_var = xx & 0x7fffffff;
   return exp;
}
#endif




static INLINE void aac_byte_align(void)
{
   pad->frame_left -= (pad->ado_cache_left & 0x07);
   pad->ado_cache_left &= 0xf8;
}

static INLINE void aac_bit_flush(int len)
{
   pad->ado_cache_left -= len;
   pad->frame_left -= len;
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static INLINE int aac_append_cache(void)
{
   
   if(pad->buf_left==0)   //是否這兩行code可以被deleted.
      aac_next_granule();

   pad->ado_cache = (pad->ado_cache<<8) | ((*pad->ado_cache_ptr++) & 0x00ff);
   pad->ado_cache_left += 8;
   pad->buf_left--;

   return 1;
}

//-------------------------------------------------------------------------
// aac_bit_view len = 0 ~ 23
//-------------------------------------------------------------------------
static INLINE unsigned int aac_bit_view(int len)
{
   unsigned int val;
   
   if(len > pad->frame_left)
   {
      if(pad->ado_cache_left < len)
      {
         int bn = (pad->frame_left-pad->ado_cache_left)>>3;
         while(bn > 0 && pad->ado_cache_left <= 24)
         {
            aac_append_cache(); 
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
      aac_append_cache();  
   }
   val = (pad->ado_cache >> (pad->ado_cache_left-len)) & ((1<<len)-1);   
   return val;
}





#endif



