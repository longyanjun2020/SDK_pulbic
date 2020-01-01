#ifndef IDCT_H
#define IDCT_H

#ifndef WIN32
#ifndef __stdcall
#define __stdcall
#endif
#endif

void __stdcall idct_Z0(int16 *P);
void __stdcall idct_23002_2(int16 *P);
void __stdcall idct_23002_2_dc(int16 *P);
void divx_idct_generic_addblock(int16 *P, uchar *Dst, int width, int isIntra, int lpos
#ifdef _MINLPOS_IDCT_
                                , int iscol_first
#endif
                                );
void idct_23002_2_addblock(int16 *P, uchar *Dst, int stride, int isIntra, int lpos);
void spark_idct(int16 *P);
void jpeg_idct_ifast_addblock(int16 *coef_block, uchar *Dst, int width, int isIntra, int lpos);


#ifdef _REF_IDCT_
//if verified by MPEG-4 RefSW, use idct_mpeg4_ref()
//if verified by H.263 RefSW, use idct_mpeg2_init() and idct_mpeg2_ref()
#define idct_func           idct_mpeg4_ref
#elif defined(_23002_IDCT_)
#define idct_func           idct_23002_2
#define idct_addblock_func  idct_23002_2_addblock
#define IDCT_ADDBLOCK
#elif defined(_SPARK_IDCT_)
#define idct_func           spark_idct
#elif defined(IJG_AAN_IDCT)
#define idct_addblock_func  jpeg_idct_ifast_addblock
#define IDCT_ADDBLOCK
#elif defined(_DIVX_IDCT_)
#define idct_func           divx_idct_generic_c
#define idct_addblock_func  divx_idct_generic_addblock
#define IDCT_ADDBLOCK
#elif defined(_FFDSHOW_IDCT_)
#define idct_func           ffdshow_idct
#elif defined(_JPD_IDCT_CMODEL_)
#define idct_init_func      gen_table
#define idct_func           jpd_idct8x8
#elif defined(AAN_MMX2)
#define idct_init_func      AanIDct_Init_MMX2
#define idct_func           AanTLPBIDCT_MMX2
#endif

#ifdef idct_init_func
#define NEED_IDCT_INIT
#endif

#endif  // IDCT_H
