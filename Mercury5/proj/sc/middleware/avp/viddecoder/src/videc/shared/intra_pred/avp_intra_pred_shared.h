#include "avp_common.h"

#ifdef INTRA_LEFT_TOP
#define P_I  UBYTESEL(l_pix, 0)
#define P_J  UBYTESEL(l_pix, 1)
#define P_K  UBYTESEL(l_pix, 2)
#define P_L  UBYTESEL(l_pix, 3)
#define P_ABCD CONVPUINTXTOUINT32(pTop)
#define P_X  upper_left
#else
#define P_I  pCurr[-1]
#define P_J  pCurr[-1+stride]
#define P_K  pCurr[-1+FACTOR_2(stride)]
#define P_L  pCurr[-1+FACTOR_3(stride)]
#define P_ABCD CONVPUINTXTOUINT32(pCurr-stride)
#define P_X  pCurr[-1-stride]
#endif

#define P_M  pCurr[-1+FACTOR_4(stride)]
#define P_N  pCurr[-1+FACTOR_5(stride)]
#define P_O  pCurr[-1+FACTOR_6(stride)]
#define P_P  pCurr[-1+FACTOR_7(stride)]


#define O_ABCD CONVPUINTXTOUINT32(pCurr)
#define O_EFGH CONVPUINTXTOUINT32(pCurr+stride)
#define O_IJKL CONVPUINTXTOUINT32(pCurr+FACTOR_2(stride))
#define O_MNOP CONVPUINTXTOUINT32(pCurr+FACTOR_3(stride))

#ifdef _AG_S32_
#define BILINEAR_4PEL_121(in1, in2, in3) \
    ((in1&0xfcfcfcfc)>>2) +  FACTOR_2((in2&0xfcfcfcfc)>>2) + ((in3&0xfcfcfcfc)>>2) + ((((in1&0x03030303)+FACTOR_2(in2&0x03030303)+(in3&0x03030303)+0x02020202) >> 2) & 0x03030303);
#define BILINEAR_8PEL_121_121(in1, in2, in3, in4, in5, in6) \
    ((in1&0xf8f8f8f8)>>3) +  FACTOR_2((in2&0xf8f8f8f8)>>3) + ((in3&0xf8f8f8f8)>>3) + ((in4&0xf8f8f8f8)>>3) +  FACTOR_2((in5&0xf8f8f8f8)>>3) + ((in6&0xf8f8f8f8)>>3) + ((((in1&0x07070707)+FACTOR_2(in2&0x07070707)+(in3&0x07070707)+(in4&0x07070707)+FACTOR_2(in5&0x07070707)+(in6&0x07070707)+0x04040404) >> 3) & 0x07070707);
#endif

#ifdef _AG_S32_
#define SUM_4_U8(a) UBYTESEL(a, 0)+UBYTESEL(a, 1)+UBYTESEL(a, 2)+UBYTESEL(a, 3)
#else
#define SUM_4_U8(a) IFIR8UI(a, 0x01010101)
#endif

#define intra_4x4_pred_mode2_avc(pCurr, stride, blk_avail, l_pix) \
{ \
    uint32 DCBA, LKJI; \
    uint32 s0 = 0; \
    uint32 sum; \
    int block_available_left, block_available_up; \
\
    block_available_left = (blk_avail >> 6) & 1; \
    block_available_up   = (blk_avail >> 1) & 1; \
\
    if (block_available_up) { \
        DCBA = P_ABCD; \
        s0 += SUM_4_U8(DCBA); \
    } \
    if (block_available_left) { \
        LKJI = P_L+P_K+P_J+P_I; \
        s0 += LKJI; \
    } \
\
    if (block_available_up & block_available_left) { \
        s0 = (s0 + 4) >> 3; \
    } else if (block_available_up | block_available_left) { \
        s0 = (s0 + 2) >> 2; \
    } else { \
        s0 = 0x80; \
    } \
\
    sum = IBYTEDUP0(s0); \
\
    O_ABCD = \
    O_EFGH = \
    O_IJKL = \
    O_MNOP = sum; \
}

#define intra_4x4_pred_mode0_avc(pCurr, stride, blk_avail, pTop) \
{ \
    O_ABCD = \
    O_EFGH = \
    O_IJKL = \
    O_MNOP = P_ABCD; \
}

#define intra_4x4_pred_mode1_avc(pCurr, stride, blk_avail, l_pix) \
{ \
    O_ABCD = IBYTEDUP0(P_I); \
    O_EFGH = IBYTEDUP0(P_J); \
    O_IJKL = IBYTEDUP0(P_K); \
    O_MNOP = IBYTEDUP0(P_L); \
}

#ifdef INTRA_LEFT_TOP
#define get_CBAM() \
    CBAM = PACK_U24_U8(DCBA, upper_left);
#else // INTRA_LEFT_TOP
#ifdef _UAMEM_ACCESS_
#define get_CBAM() \
    CBAM = CONVPUINTXTOUINT32(pCurr-stride-1);
#else
#define get_CBAM() \
    CBAM = PACK_U24_U8(DCBA, P_X);
#endif
#endif // INTRA_LEFT_TOP

#ifdef _AG_S32_
#define intra_4x4_pred_mode4_avc(pCurr, stride, blk_avail, l_pix, pToP, upper_left) \
{ \
    uint32 DCBA, CBAM, BAMI, AMIJ, MIJK, IJKL; \
    uint32 dcba, ponm; \
 \
    DCBA = P_ABCD; \
    get_CBAM(); \
    BAMI = PACK_U24_U8(CBAM, P_I) ; \
    AMIJ = PACK_U24_U8(BAMI, P_J) ; \
    MIJK = PACK_U24_U8(AMIJ, P_K) ; \
    IJKL = PACK_U24_U8(MIJK, P_L) ; \
 \
    ponm = BILINEAR_4PEL_121(IJKL, MIJK, AMIJ); \
    dcba = BILINEAR_4PEL_121(BAMI, CBAM, DCBA); \
    \
    O_ABCD = dcba; \
    O_EFGH = FUNSHIFT2(dcba>>8, ponm); \
    O_IJKL = FUNSHIFT3(dcba>>8, ponm); \
    O_MNOP = ponm; \
}
#elif defined(_TM5250_)
//#ifdef _TM5250_ 
#define intra_4x4_pred_mode4_avc(pCurr, stride, blk_avail, l_pix, pToP, upper_left) \
{ \
    uint32 DCBA, CBAM, BAMI, AMIJ, MIJK, IJKL; \
    uint32 db, ca, be, ai, em; \
    uint32 dcba, cbae, baei, aeim; \
 \
    DCBA = P_ABCD; \
    /*CBAM = CONVPUINTXTOUINT32(pCurr-stride-1); */\
    get_CBAM(); \
 \
    BAMI = PACK16LSB(DCBA, PACKBYTES(CBAM, P_I)); \
    AMIJ = PACK16LSB(CBAM, PACKBYTES(P_I, P_J)); \
    MIJK = PACK16LSB(PACKBYTES(CBAM, P_I), PACKBYTES(P_J, P_K)); \
    IJKL = PACK16LSB(PACKBYTES(P_I, P_J), PACKBYTES(P_K, P_L)); \
 \
    em = BILINEAR2(IJKL, MIJK); \
    ai = BILINEAR2(MIJK, AMIJ); \
    ca = BILINEAR2(BAMI, CBAM); \
    db = BILINEAR2(CBAM, DCBA); \
 \
    be = BILINEAR2(AMIJ, BAMI); \
    aeim = MERGEODD(ai, em); \
    baei = MERGEODD(be, ai); \
    cbae = MERGEODD(ca, be); \
    dcba = MERGEODD(db, ca); \
 \
    O_ABCD = dcba; \
    O_EFGH = cbae; \
    O_IJKL = baei; \
    O_MNOP = aeim; \
}
#else // _TM5250_ 
#define intra_4x4_pred_mode4_avc(pCurr, stride, blk_avail, l_pix, pTop, upper_left) \
{ \
    uint32 DCBA, CBAM, BAMI, AMIJ, MIJK, IJKL, OOJK, OOIJ, OOKL, OOMI; \
    uint32 db, ca, be, ai, em; \
    uint32 dcba, cbae, baei, aeim; \
 \
    DCBA = P_ABCD; \
    OOIJ = PACKBYTES(P_I, P_J); \
    OOKL = PACKBYTES(P_K, P_L); \
    IJKL = PACK16LSB(OOIJ, OOKL);/*make_uint32(P_I, P_J, P_K, P_L); */\
 \
    /*CBAM = FUNSHIFT1(DCBA, SWAPBYTES(P_X)); */\
    get_CBAM(); \
    OOJK = PACKBYTES(P_J, P_K);\
    OOMI = PACKBYTES(CBAM, P_I); \
    BAMI = PACK16LSB(DCBA, OOMI); /*FUNSHIFT1(CBAM, IJKL); */\
    AMIJ = PACK16LSB(CBAM, OOIJ);/*FUNSHIFT2(CBAM, IJKL); */\
    MIJK = PACK16LSB(OOMI, OOJK); /*FUNSHIFT3(CBAM, IJKL); */\
    \
    em = BILINEAR2(IJKL, MIJK); \
    ai = BILINEAR2(MIJK, AMIJ); \
    ca = BILINEAR2(BAMI, CBAM); \
    db = BILINEAR2(CBAM, DCBA); \
    \
    be = BILINEAR2(AMIJ, BAMI);/*FUNSHIFT2(db, em); */\
    aeim = MERGEODD(ai, em); \
    baei = MERGEODD(be, ai); \
    cbae = MERGEODD(ca, be); \
    dcba = MERGEODD(db, ca); \
 \
    O_ABCD = dcba; \
    O_EFGH = cbae; \
    O_IJKL = baei; \
    O_MNOP = aeim; \
}
#endif // _TM5250_ 

#ifdef _AG_S32_
#define intra_4x4_pred_mode5_avc(pCurr, stride, blk_avail, l_pix, pTop, upper_left) \
{ \
    /*
    a b c d
    e f g h
    i a b c
    m e f g
    */ \
    uint32 MIJK, DCBA, CBAM, BAMI, AMIJ; \
    uint32 dcba, hgfe, feim; \
    \
    DCBA = P_ABCD; \
    get_CBAM(); \
    BAMI = PACK_U24_U8(CBAM, P_I); \
    AMIJ = PACK_U24_U8(BAMI, P_J); \
    MIJK = PACK_U24_U8(AMIJ, P_K); \
    \
    dcba = QUADAVG(CBAM, DCBA); \
    hgfe = BILINEAR_4PEL_121(BAMI, CBAM, DCBA); \
    feim = BILINEAR_4PEL_121(MIJK, AMIJ, BAMI); \
    \
    O_ABCD = dcba; \
    O_EFGH = hgfe; \
    O_IJKL = FUNSHIFT1(dcba, feim<<16); \
    O_MNOP = FUNSHIFT1(hgfe, feim<<24); \
}
#elif 1
#define intra_4x4_pred_mode5_avc(pCurr, stride, blk_avail, l_pix, pTop, upper_left) \
{ \
    /*
    a b c d
    e f g h
    i a b c
    m e f g
    */ \
    uint32 MIJK, DCBA; \
    uint32 CBAM, BAMI; \
    uint32 ge, hf, i, m, dcba, hgfe, cbai, gfem; \
    uint32 OOMI, OOJK, OOIJ; \
    \
    OOJK = PACKBYTES(P_J, P_K); \
    OOIJ = PACKBYTES(P_I, P_J); \
    OOMI = PACKBYTES(P_X, P_I); \
    MIJK = make_uint32(P_X, P_I, P_J, P_K); \
    DCBA = P_ABCD; \
    \
    CBAM = FUNSHIFT1(DCBA, MIJK); \
    BAMI = FUNSHIFT2(DCBA, MIJK); \
    \
    m = BILINEAR2(OOIJ, OOJK); \
    i = BILINEAR2(OOMI, OOIJ); \
    ge = BILINEAR2(CBAM, BAMI); \
    hf = BILINEAR2(DCBA, CBAM); \
    dcba = QUADAVG(CBAM, DCBA); \
    hgfe = MERGEODD(hf, ge); \
    cbai = FUNSHIFT1(dcba, SWAPBYTES(i)); \
    gfem = MERGEODD(ge, PACK16LSB(hf, m)); \
    \
    O_ABCD = dcba; \
    O_EFGH = hgfe; \
    O_IJKL = cbai; \
    O_MNOP = gfem; \
    /*printf("IN 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x OUT 0x%x 0x%x 0x%x 0x%x\n", (int)P_I, (int)P_J, (int)P_K, (int)P_L, (int)P_X, P_ABCD, O_ABCD, O_EFGH, O_IJKL, O_MNOP);*/ \
}
#else
#define intra_4x4_pred_mode5_avc(pCurr, stride, blk_avail, l_pix, pTop, upper_left) \
{ \
    uint32 DCBA; \
    uint32 BA,CB,AM,DC; \
    uint32 MI,IJ,JK; \
    uint32 ba,dc,im,fe,hg; \
    uint32 dcba, hgfe,i,m; \
    uint32 OOOM,OOOI,OOOJ,OOOK; \
 \
    DCBA = P_ABCD; \
    OOOM = P_X; \
 \
    BA = MERGELSB(0, DCBA); \
    DC = MERGEMSB(0, DCBA); \
    CB = FUNSHIFT2(DC, BA); \
    AM = PACK16LSB(BA,OOOM);  \
 \
    OOOI = P_I; \
    OOOJ = P_J; \
    OOOK = P_K; \
 \
    MI = PACK16LSB(OOOM,OOOI);     \
    IJ = PACK16LSB(OOOI,OOOJ); \
    JK = PACK16LSB(OOOJ,OOOK); \
 \
    ba = AM + BA + 0x00010001; \
    dc = CB + DC + 0x00010001; \
    fe = ADD_121(MI,AM,BA)+0x00020002; \
    hg = ADD_121(BA,CB,DC)+0x00020002; \
    im = ADD_121(MI,IJ,JK)+0x00020002; \
 \
    ba = DUALASR(ba, 1); \
    dc = DUALASR(dc, 1); \
    fe = DUALASR(fe, 2); \
    hg = DUALASR(hg, 2); \
    im = DUALASR(im, 2); \
    m  = MERGELSB(0, im); \
    i  = MERGEMSB(0, im); \
 \
    dcba = MERGEDUAL16LSB(dc,ba); \
    hgfe = MERGEDUAL16LSB(hg,fe); \
 \
    O_ABCD = dcba; \
    O_EFGH = hgfe; \
    O_IJKL = FUNSHIFT1(dcba,0)|i; \
    O_MNOP = FUNSHIFT1(hgfe,0)|m; \
}
#endif

#ifdef _AG_S32_
#define intra_4x4_pred_mode6_avc(pCurr, stride, blk_avail, l_pix, pTop) \
{ \
    /*
    a b c d
    e f a b
    i j e f
    m n i j */ \
    uint32 DCBA, CBAM, BAMI, AMIJ, MIJK, IJKL; \
    uint32 aeim, bfjn, dcbf; \
     \
    DCBA = P_ABCD; \
    get_CBAM(); \
    BAMI = PACK_U24_U8(CBAM, P_I) ; \
    AMIJ = PACK_U24_U8(BAMI, P_J) ; \
    MIJK = PACK_U24_U8(AMIJ, P_K) ; \
    IJKL = PACK_U24_U8(MIJK, P_L) ; \
    \
    aeim = QUADAVG(MIJK, IJKL); \
    bfjn = BILINEAR_4PEL_121(IJKL, MIJK, AMIJ); \
    dcbf = BILINEAR_4PEL_121(AMIJ, BAMI, CBAM); \
    \
    O_ABCD = FUNSHIFT1(dcbf>>8, aeim); \
    O_EFGH = MERGEMSB(bfjn, aeim); \
    O_IJKL = MERGELSB(bfjn>>8, aeim>>8); \
    O_MNOP = MERGELSB(bfjn, aeim); \
}
#else
#define intra_4x4_pred_mode6_avc(pCurr, stride, blk_avail, l_pix, pTop) \
{ \
    uint32 IJKL, CBAM, ojon, bafe, jinm, feji, dcba, DCBA, BABA, odoc; \
    uint32 JKJK, ojoi, IJJK, AXXI, IJIJ, ofoe, XIIJ, OOIJ, OOKL, OOJK, OOXI, oboa, XIXI, onom, JKKL, KLKL; \
 \
    OOIJ = PACKBYTES(P_I, P_J); \
    OOKL = PACKBYTES(P_K, P_L); \
    IJKL = PACK16LSB(OOIJ, OOKL); \
    OOJK = PACKBYTES(P_J, P_K); \
    DCBA = P_ABCD; \
    get_CBAM(); \
    OOXI = PACKBYTES(CBAM, P_I); \
 \
    JKJK = PACK16LSB(OOJK, OOJK); \
    IJJK = PACK16LSB(OOIJ, OOJK); \
    AXXI = PACK16LSB(CBAM, OOXI); \
    IJIJ = PACK16LSB(OOIJ, OOIJ); \
    XIIJ = PACK16LSB(OOXI, OOIJ); \
    XIXI = PACK16LSB(OOXI, OOXI); \
    JKKL = PACK16LSB(OOJK, OOKL); \
    KLKL = PACK16LSB(OOKL, OOKL); \
    BABA = PACK16LSB(DCBA, DCBA); \
 \
    onom = BILINEAR2(JKKL, KLKL); \
    ojon = BILINEAR2(JKJK, IJKL); \
    ofoe = BILINEAR2(XIIJ, IJIJ); \
    ojoi = BILINEAR2(IJJK, JKJK); \
    oboa = BILINEAR2(AXXI, XIXI);\
    odoc = BILINEAR2(CBAM, BABA); \
 \
    dcba = MERGEDUAL16LSB(odoc, oboa); \
    bafe = MERGEDUAL16LSB(oboa, ofoe); \
    jinm = MERGEDUAL16LSB(ojoi, onom); \
    feji = MERGEDUAL16LSB(ofoe, ojoi); \
    \
    O_ABCD = dcba; \
    O_EFGH = bafe; \
    O_IJKL = feji; \
    O_MNOP = jinm; \
}
#endif

#ifdef INTRA_LEFT_TOP
#define CB1_ABCD() CONVPUINTXTOUINT32(pTop_u)
#define CR1_ABCD() CONVPUINTXTOUINT32(pTop_v)
#define CB2_ABCD() CONVPUINTXTOUINT32(pTop_u+4)
#define CR2_ABCD() CONVPUINTXTOUINT32(pTop_v+4)
#else
#define CB1_ABCD() CONVPUINTXTOUINT32(pCurr_u-stride)
#define CR1_ABCD() CONVPUINTXTOUINT32(pCurr_v-stride)
#define CB2_ABCD() CONVPUINTXTOUINT32(pCurr_u-stride/*+4*/)
#define CR2_ABCD() CONVPUINTXTOUINT32(pCurr_v-stride/*+4*/)
#endif

#define intra_chroma_16x16_pred_VERT(pCurr_u, pCurr_v, stride, blk_avail, pTop_u, pTop_v) \
{ \
    CONVPUINTXTOUINT32(pCurr_u)   =   \
    CONVPUINTXTOUINT32(pCurr_u+stride)  = \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride))  =     \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_4(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_5(stride))  = \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_6(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_7(stride)) = CB1_ABCD(); \
 \
    pCurr_u += 4; \
    CONVPUINTXTOUINT32(pCurr_u)   =   \
    CONVPUINTXTOUINT32(pCurr_u+stride)  = \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride))  =     \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_4(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_5(stride))  = \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_6(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_7(stride)) = CB2_ABCD(); \
 \
    CONVPUINTXTOUINT32(pCurr_v)   =   \
    CONVPUINTXTOUINT32(pCurr_v+stride)  = \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride))  =     \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_4(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_5(stride))  = \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_6(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_7(stride)) = CR1_ABCD(); \
 \
    pCurr_v += 4; \
    CONVPUINTXTOUINT32(pCurr_v)   =   \
    CONVPUINTXTOUINT32(pCurr_v+stride)  = \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride))  =     \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_4(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_5(stride))  = \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_6(stride))  =   \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_7(stride)) = CR2_ABCD(); \
}


#ifdef INTRA_LEFT_TOP
#define intra_chroma_16x16_pred_HOR_get_leftpix1() \
    r1_u = IBYTEDUP0(UBYTESEL(l_pix_u1, 0)); \
    r2_u = IBYTEDUP0(UBYTESEL(l_pix_u1, 1)); \
    r3_u = IBYTEDUP0(UBYTESEL(l_pix_u1, 2)); \
    r4_u = IBYTEDUP0(UBYTESEL(l_pix_u1, 3)); \
    r1_v = IBYTEDUP0(UBYTESEL(l_pix_v1, 0)); \
    r2_v = IBYTEDUP0(UBYTESEL(l_pix_v1, 1)); \
    r3_v = IBYTEDUP0(UBYTESEL(l_pix_v1, 2)); \
    r4_v = IBYTEDUP0(UBYTESEL(l_pix_v1, 3));

#define intra_chroma_16x16_pred_HOR_get_leftpix2() \
    r1_u = IBYTEDUP0(UBYTESEL(l_pix_u2, 0)); \
    r2_u = IBYTEDUP0(UBYTESEL(l_pix_u2, 1)); \
    r3_u = IBYTEDUP0(UBYTESEL(l_pix_u2, 2)); \
    r4_u = IBYTEDUP0(UBYTESEL(l_pix_u2, 3)); \
    r1_v = IBYTEDUP0(UBYTESEL(l_pix_v2, 0)); \
    r2_v = IBYTEDUP0(UBYTESEL(l_pix_v2, 1)); \
    r3_v = IBYTEDUP0(UBYTESEL(l_pix_v2, 2)); \
    r4_v = IBYTEDUP0(UBYTESEL(l_pix_v2, 3));

#else // INTRA_LEFT_TOP
#define intra_chroma_16x16_pred_HOR_get_leftpix1() \
    r1_u = IBYTEDUP0(pCurr_u[-1]); \
    r2_u = IBYTEDUP0(pCurr_u[-1+stride]); \
    r3_u = IBYTEDUP0(pCurr_u[-1+FACTOR_2(stride)]); \
    r4_u = IBYTEDUP0(pCurr_u[-1+FACTOR_3(stride)]); \
    r1_v = IBYTEDUP0(pCurr_v[-1]); \
    r2_v = IBYTEDUP0(pCurr_v[-1+stride]); \
    r3_v = IBYTEDUP0(pCurr_v[-1+FACTOR_2(stride)]); \
    r4_v = IBYTEDUP0(pCurr_v[-1+FACTOR_3(stride)]);

#define intra_chroma_16x16_pred_HOR_get_leftpix2() \
    r1_u = IBYTEDUP0(pCurr_u[-5]); \
    r2_u = IBYTEDUP0(pCurr_u[-5+stride]); \
    r3_u = IBYTEDUP0(pCurr_u[-5+FACTOR_2(stride)]); \
    r4_u = IBYTEDUP0(pCurr_u[-5+FACTOR_3(stride)]); \
    r1_v = IBYTEDUP0(pCurr_v[-5]); \
    r2_v = IBYTEDUP0(pCurr_v[-5+stride]); \
    r3_v = IBYTEDUP0(pCurr_v[-5+FACTOR_2(stride)]); \
    r4_v = IBYTEDUP0(pCurr_v[-5+FACTOR_3(stride)]);
#endif // INTRA_LEFT_TOP

#define intra_chroma_16x16_pred_HOR(pCurr_u, pCurr_v, stride, blk_avail, l_pix_u1, l_pix_u2, l_pix_v1, l_pix_v2) \
{ \
    uint32 r1_u, r2_u, r3_u, r4_u,r1_v, r2_v, r3_v, r4_v; \
    \
    intra_chroma_16x16_pred_HOR_get_leftpix1(); \
    CONVPUINTXTOUINT32(pCurr_u)    = r1_u; \
    CONVPUINTXTOUINT32(pCurr_u+stride)   = r2_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride))   = r3_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride))   = r4_u; \
    pCurr_u += 4; \
    CONVPUINTXTOUINT32(pCurr_u)  = r1_u; \
    CONVPUINTXTOUINT32(pCurr_u+stride) = r2_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride)) = r3_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride)) = r4_u; \
    \
    CONVPUINTXTOUINT32(pCurr_v)    = r1_v; \
    CONVPUINTXTOUINT32(pCurr_v+stride)   = r2_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride))   = r3_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride))   = r4_v; \
    pCurr_v += 4; \
    CONVPUINTXTOUINT32(pCurr_v)  = r1_v; \
    CONVPUINTXTOUINT32(pCurr_v+stride) = r2_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride)) = r3_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride)) = r4_v; \
 \
    pCurr_u+=FACTOR_4(stride); \
    pCurr_v+=FACTOR_4(stride); \
 \
    intra_chroma_16x16_pred_HOR_get_leftpix2(); \
    CONVPUINTXTOUINT32(pCurr_u)  = r1_u; \
    CONVPUINTXTOUINT32(pCurr_u+stride) = r2_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride)) = r3_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride)) = r4_u; \
    pCurr_u -= 4; \
    CONVPUINTXTOUINT32(pCurr_u)  = r1_u; \
    CONVPUINTXTOUINT32(pCurr_u+stride) = r2_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_2(stride)) = r3_u; \
    CONVPUINTXTOUINT32(pCurr_u+FACTOR_3(stride)) = r4_u; \
    \
    CONVPUINTXTOUINT32(pCurr_v)    = r1_v; \
    CONVPUINTXTOUINT32(pCurr_v+stride)   = r2_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride))   = r3_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride))   = r4_v; \
    pCurr_v -= 4; \
    CONVPUINTXTOUINT32(pCurr_v)  = r1_v; \
    CONVPUINTXTOUINT32(pCurr_v+stride) = r2_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_2(stride)) = r3_v; \
    CONVPUINTXTOUINT32(pCurr_v+FACTOR_3(stride)) = r4_v; \
}

#define PLANEMODE_4PEL_VALUE(pos) \
    tmp1 = plane; \
    tmp2 = tmp1+ib; \
    t1 = DUALUCLIPI(DUALASR(PACK16LSB(tmp2, tmp1), 5),255); \
    tmp1 = tmp2+ib; \
    tmp2 = tmp1+ib; \
    t2 = DUALUCLIPI(DUALASR(PACK16LSB(tmp2, tmp1), 5),255); \
    CONVUINTXTOUINT32(pos) = MERGEDUAL16LSB(t2,t1);


#ifdef INTRA_LEFT_TOP
#define intra_pred_16x16_PLANE_avc_get_leftpix() \
    iaa = (UBYTESEL(DCBA3,3)+UBYTESEL(l_pix4, 3))<<4; \
    JI0 = MERGEDUAL16LSB(UBYTESEL(l_pix1, 0), UBYTESEL(DCBA0, 0)); \
    LK0 = MERGEDUAL16LSB(UBYTESEL(l_pix1, 2), UBYTESEL(l_pix1, 1)); \
    JI1 = MERGEDUAL16LSB(UBYTESEL(l_pix2, 0), UBYTESEL(l_pix1, 3)); \
    LK1 = MERGEDUAL16LSB(UBYTESEL(l_pix2, 2), UBYTESEL(l_pix2, 1)); \
    JI2 = MERGEDUAL16LSB(UBYTESEL(l_pix3, 1), UBYTESEL(l_pix3, 0)); \
    LK2 = MERGEDUAL16LSB(UBYTESEL(l_pix3, 3), UBYTESEL(l_pix3, 2)); \
    JI3 = MERGEDUAL16LSB(UBYTESEL(l_pix4, 1), UBYTESEL(l_pix4, 0)); \
    LK3 = MERGEDUAL16LSB(UBYTESEL(l_pix4, 3), UBYTESEL(l_pix4, 2));

#define intra_pred_16x16_PLANE_avc_get_toppix() \
    DCBA0 = CONVPUINTXTOUINT32(pTop-1); \
    DCBA1 = CONVPUINTXTOUINT32(pTop+3); \
    DCBA2 = CONVPUINTXTOUINT32(pTop+8); \
    DCBA3 = CONVPUINTXTOUINT32(pTop+12);

#else // INTRA_LEFT_TOP
#ifdef _UAMEM_ACCESS_
#define intra_pred_16x16_PLANE_avc_get_toppix() \
    DCBA0 = CONVPUINTXTOUINT32(pCurr-stride-1); \
    DCBA1 = CONVPUINTXTOUINT32(pCurr-stride+3); \
    DCBA2 = CONVPUINTXTOUINT32(pCurr-stride+8); \
    DCBA3 = CONVPUINTXTOUINT32(pCurr-stride+12);
#else
#define intra_pred_16x16_PLANE_avc_get_toppix() \
    DCBA0 = FUNSHIFT1(P_ABCD, CONVPUINTXTOUINT32(pCurr-stride-4)); \
    DCBA1 = FUNSHIFT1(CONVPUINTXTOUINT32(pCurr-stride+4), P_ABCD); \
    DCBA2 = CONVPUINTXTOUINT32(pCurr-stride+8); \
    DCBA3 = CONVPUINTXTOUINT32(pCurr-stride+12);    
#endif

#define intra_pred_16x16_PLANE_avc_get_leftpix() \
	iaa = (UBYTESEL(DCBA3,3)+pCurr[FACTOR_15(stride)])<<4; \
	JI0 = MERGEDUAL16LSB(pCurr[0], UBYTESEL(DCBA0, 0)); \
	LK0 = MERGEDUAL16LSB(pCurr[FACTOR_2(stride)], pCurr[stride]); \
	JI1 = MERGEDUAL16LSB(pCurr[FACTOR_4(stride)], pCurr[FACTOR_3(stride)]); \
	LK1 = MERGEDUAL16LSB(pCurr[FACTOR_6(stride)], pCurr[FACTOR_5(stride)]); \
	JI2 = MERGEDUAL16LSB(pCurr[FACTOR_9(stride)], pCurr[FACTOR_8(stride)]); \
	LK2 = MERGEDUAL16LSB(pCurr[FACTOR_11(stride)], pCurr[FACTOR_10(stride)]); \
	JI3 = MERGEDUAL16LSB(pCurr[FACTOR_13(stride)], pCurr[FACTOR_12(stride)]); \
	LK3 = MERGEDUAL16LSB(pCurr[FACTOR_15(stride)], pCurr[FACTOR_14(stride)]);

#endif // INTRA_LEFT_TOP

//#define CCIR656_CLIP
#ifdef CCIR656_CLIP
#define CLIP_LOW 16
#define CLIP_HIGH_C 240
#define UCLIPI_D(x, y) CLIP3(CLIP_LOW, y, x)
#else
#define CLIP_LOW 0
#define CLIP_HIGH_C 255
#define UCLIPI_D(x, c) UCLIPI(x, c)
#endif

#ifdef _AG_S32_
#define PLANE_MODE(pos, plane_val, ib_val) \
    *((pos) + 0) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 1) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 2) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 3) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 4) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 5) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 6) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val; \
    *((pos) + 7) = UCLIPI_D((plane_val) >> 5, CLIP_HIGH_C); \
    plane_val += ib_val;

#define intra_pred_16x16_PLANE_avc(pCurr, stride, blk_avail, rounding, l_pix1, l_pix2, l_pix3, l_pix4, pTop) \
{  \
    int ih, iv; \
    uint32 ib,ic,iaa;  \
    int i; \
    uint32 DCBA0,DCBA1,DCBA2,DCBA3; \
    int32 plane; \
    int32 o_plane; \
  \
    intra_pred_16x16_PLANE_avc_get_toppix(); \
    ih = FACTOR_1(UBYTESEL(DCBA2, 0)-UBYTESEL(DCBA1, 3)) + \
         FACTOR_2(UBYTESEL(DCBA2, 1)-UBYTESEL(DCBA1, 2)) + \
         FACTOR_3(UBYTESEL(DCBA2, 2)-UBYTESEL(DCBA1, 1)) + \
         FACTOR_4(UBYTESEL(DCBA2, 3)-UBYTESEL(DCBA1, 0)) + \
         FACTOR_5(UBYTESEL(DCBA3, 0)-UBYTESEL(DCBA0, 3)) + \
         FACTOR_6(UBYTESEL(DCBA3, 1)-UBYTESEL(DCBA0, 2)) + \
         FACTOR_7(UBYTESEL(DCBA3, 2)-UBYTESEL(DCBA0, 1)) + \
         FACTOR_8(UBYTESEL(DCBA3, 3)-UBYTESEL(DCBA0, 0)); \
 \
    pCurr--; \
    iv = FACTOR_1(pCurr[FACTOR_8(stride)]-pCurr[FACTOR_6(stride)]) + \
         FACTOR_2(pCurr[FACTOR_9(stride)]-pCurr[FACTOR_5(stride)]) + \
         FACTOR_3(pCurr[FACTOR_10(stride)]-pCurr[FACTOR_4(stride)]) + \
         FACTOR_4(pCurr[FACTOR_11(stride)]-pCurr[FACTOR_3(stride)]) + \
         FACTOR_5(pCurr[FACTOR_12(stride)]-pCurr[FACTOR_2(stride)]) + \
         FACTOR_6(pCurr[FACTOR_13(stride)]-pCurr[stride]) + \
         FACTOR_7(pCurr[FACTOR_14(stride)]-pCurr[0]) + \
         FACTOR_8(pCurr[FACTOR_15(stride)]-pCurr[-stride]); \
 \
    iaa = (UBYTESEL(DCBA3,3)+pCurr[FACTOR_15(stride)])<<4; \
    ib=(FACTOR_5(ih)+rounding/*+32*/)>>6;  \
    ic=(FACTOR_5(iv)+rounding/*+32*/)>>6; \
 \
    o_plane = (iaa-FACTOR_7(ib+ic) + 16); \
 \
    pCurr++; \
 \
    for (i=0;i< 16;i++) { \
        plane = o_plane; \
        PLANE_MODE(pCurr, plane, ib); \
        PLANE_MODE(pCurr+8, plane, ib); \
        pCurr += stride; \
        o_plane += ic; \
    } \
}
#elif defined(_TM5250_)
#define intra_pred_16x16_PLANE_avc(pCurr, stride, blk_avail, rounding, l_pix1, l_pix2, l_pix3, l_pix4, pTop) \
{  \
    int ih, iv; \
    uint32 ib,ic,iaa;  \
    int i; \
    uint32 DCBA0,DCBA1,DCBA2,DCBA3; \
    uint32 BA0,BA1,BA2,BA3,DC0,DC1,DC2,DC3; \
    uint32 ba0,dc0,ba1,dc1,ba2,dc2,ba3,dc3; \
    uint32 JI0,LK0,JI1,LK1,JI2,LK2,JI3,LK3; \
    uint32 ji0,lk0,ji1,lk1,ji2,lk2,ji3,lk3; \
    int32 plane; \
    int32 o_plane; \
    uint32 t1, t2, tmp1, tmp2; \
  \
    /*DCBA0 = CONVPUINTXTOUINT32(pCurr-stride-1); \
    DCBA1 = CONVPUINTXTOUINT32(pCurr-stride+3); \
    DCBA2 = CONVPUINTXTOUINT32(pCurr-stride+8); \
    DCBA3 = CONVPUINTXTOUINT32(pCurr-stride+12); */\
    intra_pred_16x16_PLANE_avc_get_toppix(); \
    BA0 = MERGELSB(0, DCBA0); \
    DC0 = MERGEMSB(0, DCBA0); \
    BA1 = MERGELSB(0, DCBA1); \
    DC1 = MERGEMSB(0, DCBA1); \
    BA2 = MERGELSB(0, DCBA2); \
    DC2 = MERGEMSB(0, DCBA2); \
    BA3 = MERGELSB(0, DCBA3); \
    DC3 = MERGEMSB(0, DCBA3); \
    ba0 = IFIR16(BA0,0x00070008); \
    dc0 = IFIR16(DC0,0x00050006); \
    ba1 = IFIR16(BA1,0x00030004); \
    dc1 = IFIR16(DC1,0x00010002); \
    ba2 = IFIR16(BA2,0x00020001); \
    dc2 = IFIR16(DC2,0x00040003); \
    ba3 = IFIR16(BA3,0x00060005); \
    dc3 = IFIR16(DC3,0x00080007); \
    ih = ((ba2+dc2)-(ba1+dc1))+((ba3+dc3)-(ba0+dc0)); \
 \
    pCurr--; \
    /*iaa = (UBYTESEL(DCBA3,3)+pCurr[FACTOR_15(stride)])<<4; \
    JI0 = MERGEDUAL16LSB(pCurr[0], UBYTESEL(DCBA0, 0)); \
    LK0 = MERGEDUAL16LSB(pCurr[FACTOR_2(stride)], pCurr[stride]); \
    JI1 = MERGEDUAL16LSB(pCurr[FACTOR_4(stride)], pCurr[FACTOR_3(stride)]); \
    LK1 = MERGEDUAL16LSB(pCurr[FACTOR_6(stride)], pCurr[FACTOR_5(stride)]); \
    JI2 = MERGEDUAL16LSB(pCurr[FACTOR_9(stride)], pCurr[FACTOR_8(stride)]); \
    LK2 = MERGEDUAL16LSB(pCurr[FACTOR_11(stride)], pCurr[FACTOR_10(stride)]); \
    JI3 = MERGEDUAL16LSB(pCurr[FACTOR_13(stride)], pCurr[FACTOR_12(stride)]); \
    LK3 = MERGEDUAL16LSB(pCurr[FACTOR_15(stride)], pCurr[FACTOR_14(stride)]); */\
    intra_pred_16x16_PLANE_avc_get_leftpix(); \
 \
    ji0 = IFIR16(JI0,0x00070008); \
    lk0 = IFIR16(LK0,0x00050006); \
    ji1 = IFIR16(JI1,0x00030004); \
    lk1 = IFIR16(LK1,0x00010002); \
    ji2 = IFIR16(JI2,0x00020001); \
    lk2 = IFIR16(LK2,0x00040003); \
    ji3 = IFIR16(JI3,0x00060005); \
    lk3 = IFIR16(LK3,0x00080007); \
    iv = ((ji2+lk2)-(ji1+lk1))+((ji3+lk3)-(ji0+lk0)); \
 \
    ib=(FACTOR_5(ih)+rounding/*+32*/)>>6;  \
    ic=(FACTOR_5(iv)+rounding/*+32*/)>>6; \
 \
    o_plane = (iaa-FACTOR_7(ib+ic) + 16); \
 \
    pCurr++; \
 \
    for (i=0;i< 16;i++) {		 \
        plane = o_plane; \
        PLANEMODE_4PEL_VALUE(pCurr[0]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[4]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[8]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[12]); \
        pCurr += stride; \
     \
        o_plane += ic; \
    } \
}
#else // _TM5250
#define intra_pred_16x16_PLANE_avc(pCurr, stride, blk_avail, rounding, l_pix1, l_pix2, l_pix3, l_pix4, pTop) \
{ \
    int ih, iv; \
    uint32 ib,ic,iaa;  \
    int i; \
    uint32 DCBA0,DCBA1,DCBA2,DCBA3; \
    uint32 BA0,BA1,BA2,BA3,DC0,DC1,DC2,DC3; \
    uint32 ba0,dc0,ba1,dc1,ba2,dc2,ba3,dc3; \
    uint32 JI0,LK0,JI1,LK1,JI2,LK2,JI3,LK3; \
    uint32 ji0,lk0,ji1,lk1,ji2,lk2,ji3,lk3; \
    int32 plane; \
    int32 o_plane; \
    uint32 t1, t2, tmp1, tmp2; \
 \
    /*DCBA0 = FUNSHIFT1(P_ABCD, CONVPUINTXTOUINT32(pCurr-stride-4)); \
    DCBA1 = FUNSHIFT1(CONVPUINTXTOUINT32(pCurr-stride+4), P_ABCD); \
    DCBA2 = CONVPUINTXTOUINT32(pCurr-stride+8); \
    DCBA3 = CONVPUINTXTOUINT32(pCurr-stride+12); */\
    intra_pred_16x16_PLANE_avc_get_toppix(); \
    BA0 = MERGELSB(0, DCBA0); \
    DC0 = MERGEMSB(0, DCBA0); \
    BA1 = MERGELSB(0, DCBA1); \
    DC1 = MERGEMSB(0, DCBA1); \
    BA2 = MERGELSB(0, DCBA2); \
    DC2 = MERGEMSB(0, DCBA2); \
    BA3 = MERGELSB(0, DCBA3); \
    DC3 = MERGEMSB(0, DCBA3); \
    ba0 = IFIR16(BA0,0x00070008); \
    dc0 = IFIR16(DC0,0x00050006); \
    ba1 = IFIR16(BA1,0x00030004); \
    dc1 = IFIR16(DC1,0x00010002); \
    ba2 = IFIR16(BA2,0x00020001); \
    dc2 = IFIR16(DC2,0x00040003); \
    ba3 = IFIR16(BA3,0x00060005); \
    dc3 = IFIR16(DC3,0x00080007); \
    ih = ((ba2+dc2)-(ba1+dc1))+((ba3+dc3)-(ba0+dc0)); \
 \
    pCurr--; \
    /*iaa=(pCurr[-stride+15+1]+pCurr[FACTOR_15(stride)])<<4; \
    JI0 = MERGEDUAL16LSB(pCurr[0], pCurr[-stride]); \
    LK0 = MERGEDUAL16LSB(pCurr[FACTOR_2(stride)], pCurr[stride]); \
    JI1 = MERGEDUAL16LSB(pCurr[FACTOR_4(stride)], pCurr[FACTOR_3(stride)]); \
    LK1 = MERGEDUAL16LSB(pCurr[FACTOR_6(stride)], pCurr[FACTOR_5(stride)]); \
    JI2 = MERGEDUAL16LSB(pCurr[FACTOR_9(stride)], pCurr[FACTOR_8(stride)]); \
    LK2 = MERGEDUAL16LSB(pCurr[FACTOR_11(stride)], pCurr[FACTOR_10(stride)]); \
    JI3 = MERGEDUAL16LSB(pCurr[FACTOR_13(stride)], pCurr[FACTOR_12(stride)]); \
    LK3 = MERGEDUAL16LSB(pCurr[FACTOR_15(stride)], pCurr[FACTOR_14(stride)]); */\
    intra_pred_16x16_PLANE_avc_get_leftpix(); \
 \
    ji0 = IFIR16(JI0,0x00070008); \
    lk0 = IFIR16(LK0,0x00050006); \
    ji1 = IFIR16(JI1,0x00030004); \
    lk1 = IFIR16(LK1,0x00010002); \
    ji2 = IFIR16(JI2,0x00020001); \
    lk2 = IFIR16(LK2,0x00040003); \
    ji3 = IFIR16(JI3,0x00060005); \
    lk3 = IFIR16(LK3,0x00080007); \
    iv = ((ji2+lk2)-(ji1+lk1))+((ji3+lk3)-(ji0+lk0)); \
 \
    ib=(FACTOR_5(ih)+rounding/*+32*/)>>6;  \
    ic=(FACTOR_5(iv)+rounding/*+32*/)>>6; \
 \
    o_plane = (iaa-FACTOR_7(ib+ic) + 16); \
 \
    pCurr++; \
 \
    for (i=0;i< 16;i++) {		 \
        plane = o_plane; \
        PLANEMODE_4PEL_VALUE(pCurr[0]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[4]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[8]); \
        plane = tmp2+ib; \
        PLANEMODE_4PEL_VALUE(pCurr[12]); \
        pCurr += stride; \
     \
        o_plane += ic; \
    } \
}
#endif // _TM5250_

#ifdef INTRA_LEFT_TOP
#define intra_pred_16x16_DC_avc_get_leftpix() \
    LKJI0 = UBYTESEL(l_pix1, 3) + UBYTESEL(l_pix1, 2) + UBYTESEL(l_pix1, 1) + UBYTESEL(l_pix1, 0); \
    LKJI1 = UBYTESEL(l_pix2, 3) + UBYTESEL(l_pix2, 2) + UBYTESEL(l_pix2, 1) + UBYTESEL(l_pix2, 0); \
    LKJI2 = UBYTESEL(l_pix3, 3) + UBYTESEL(l_pix3, 2) + UBYTESEL(l_pix3, 1) + UBYTESEL(l_pix3, 0); \
    LKJI3 = UBYTESEL(l_pix4, 3) + UBYTESEL(l_pix4, 2) + UBYTESEL(l_pix4, 1) + UBYTESEL(l_pix4, 0);

#define intra_pred_16x16_DC_avc_get_toppix() \
    DCBA0=P_ABCD; \
    DCBA1=CONVPUINTXTOUINT32(pTop+4); \
    DCBA2=CONVPUINTXTOUINT32(pTop+8); \
    DCBA3=CONVPUINTXTOUINT32(pTop+12);
     
#else
#define intra_pred_16x16_DC_avc_get_leftpix() \
    LKJI0 = pCurr[FACTOR_3(stride)] +pCurr[FACTOR_2(stride)] +pCurr[stride]+ pCurr[0]; \
    LKJI1 = pCurr[FACTOR_7(stride)] +pCurr[FACTOR_6(stride)] +pCurr[FACTOR_5(stride)] +pCurr[FACTOR_4(stride)]; \
    LKJI2 = pCurr[FACTOR_11(stride)]+pCurr[FACTOR_10(stride)]+pCurr[FACTOR_9(stride)] +pCurr[FACTOR_8(stride)]; \
    LKJI3 = pCurr[FACTOR_15(stride)]+pCurr[FACTOR_14(stride)]+pCurr[FACTOR_13(stride)]+pCurr[FACTOR_12(stride)];

#define intra_pred_16x16_DC_avc_get_toppix() \
    DCBA0=P_ABCD; \
    DCBA1=CONVPUINTXTOUINT32(pCurr-stride+4); \
    DCBA2=CONVPUINTXTOUINT32(pCurr-stride+8); \
    DCBA3=CONVPUINTXTOUINT32(pCurr-stride+12);

#endif

#define intra_pred_16x16_DC_avc(pCurr, stride, blk_avail, l_pix1, l_pix2, l_pix3, l_pix4, pTop) \
{ \
    uint32 DCBA0,DCBA1,DCBA2,DCBA3; \
    uint32 LKJI0; \
    uint32 LKJI1; \
    uint32 LKJI2; \
    uint32 LKJI3; \
    uint8 i; \
    uint32 sum = 0; \
    int up_avail, left_avail; \
 \
    up_avail = MUX(blk_avail&0x2, 1, 0); \
    left_avail = MUX(blk_avail&0x40, 1, 0); \
 \
    if (up_avail) {  \
        intra_pred_16x16_DC_avc_get_toppix(); \
        sum =  SUM_4_U8(DCBA0)+SUM_4_U8(DCBA1) \
            +  SUM_4_U8(DCBA2)+SUM_4_U8(DCBA3); \
    } \
    pCurr--; \
    if (left_avail) {       \
        intra_pred_16x16_DC_avc_get_leftpix(); \
        sum += LKJI0+LKJI1+LKJI2+LKJI3; \
    } \
 \
    if (up_avail & left_avail) \
        sum = (sum + 16) >> 5;         /* no edge*/ \
    else if (up_avail | left_avail) \
        sum = (sum + 8) >> 4;          /* upper or left edge */ \
    else \
        sum = 128; \
 \
    sum = IBYTEDUP0(sum); \
 \
    pCurr++; \
 \
	for (i=0;i<16;i++) { \
        O_ABCD =  \
        CONVPUINTXTOUINT32(pCurr+4) = \
        CONVPUINTXTOUINT32(pCurr+8) = \
        CONVPUINTXTOUINT32(pCurr+12) = sum; \
        pCurr += stride; \
	} \
}

#define intra_pred_16x16_VERT_avc_get_toppix \
    intra_pred_16x16_DC_avc_get_toppix

#define intra_pred_16x16_VERT_avc(pCurr, stride, blk_avail, pTop) \
{ \
    int j;  \
    uint32 DCBA0,DCBA1,DCBA2,DCBA3; \
 \
    /*tmp0 = P_ABCD; \
    tmp1 = CONVPUINTXTOUINT32(pCurr-stride+4); \
    tmp2 = CONVPUINTXTOUINT32(pCurr-stride+8); \
    tmp3 = CONVPUINTXTOUINT32(pCurr-stride+12); */\
    intra_pred_16x16_VERT_avc_get_toppix(); \
 \
    for (j=0;j<16;j++) {    \
        O_ABCD = DCBA0; \
        CONVPUINTXTOUINT32(pCurr+4) = DCBA1; \
        CONVPUINTXTOUINT32(pCurr+8) = DCBA2; \
        CONVPUINTXTOUINT32(pCurr+12) = DCBA3; \
        pCurr += stride; \
    }		 \
}

#ifdef INTRA_LEFT_TOP
#define intra_pred_16x16_HOR_avc_16pix(src, l_pix, byte_num) \
    CONVPUINTXTOUINT32(src) = CONVPUINTXTOUINT32(src+4) = \
    CONVPUINTXTOUINT32(src+8) = CONVPUINTXTOUINT32(src+12) = IBYTEDUP0(UBYTESEL(l_pix, byte_num));

#define intra_pred_16x16_HOR_avc(pCurr, stride, blk_avail, l_pix1, l_pix2, l_pix3, l_pix4) \
{ \
    /*O_ABCD = IBYTEDUP0(UBYTESEL(l_pix1, 0)); \    
    O_EFGH = IBYTEDUP0(UBYTESEL(l_pix1, 1)); \
    O_IJKL = IBYTEDUP0(UBYTESEL(l_pix1, 2)); \
    O_MNOP = IBYTEDUP0(UBYTESEL(l_pix1, 3)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_4(stride)) = IBYTEDUP0(UBYTESEL(l_pix2, 0)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_5(stride)) = IBYTEDUP0(UBYTESEL(l_pix2, 1)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_6(stride)) = IBYTEDUP0(UBYTESEL(l_pix2, 2)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_7(stride)) = IBYTEDUP0(UBYTESEL(l_pix2, 3)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_8(stride)) = IBYTEDUP0(UBYTESEL(l_pix3, 0)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_9(stride)) = IBYTEDUP0(UBYTESEL(l_pix3, 1)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_10(stride)) = IBYTEDUP0(UBYTESEL(l_pix3, 2)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_11(stride)) = IBYTEDUP0(UBYTESEL(l_pix3, 3)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_12(stride)) = IBYTEDUP0(UBYTESEL(l_pix4, 0)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_13(stride)) = IBYTEDUP0(UBYTESEL(l_pix4, 1)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_14(stride)) = IBYTEDUP0(UBYTESEL(l_pix4, 2)); \
    CONVPUINTXTOUINT32(pCurr+FACTOR_15(stride)) = IBYTEDUP0(UBYTESEL(l_pix4, 3)); */\
    intra_pred_16x16_HOR_avc_16pix(pCurr, l_pix1, 0); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+stride, l_pix1, 1); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_2(stride), l_pix1, 2); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_3(stride), l_pix1, 3); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_4(stride), l_pix2, 0); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_5(stride), l_pix2, 1); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_6(stride), l_pix2, 2); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_7(stride), l_pix2, 3); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_8(stride), l_pix3, 0); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_9(stride), l_pix3, 1); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_10(stride), l_pix3, 2); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_11(stride), l_pix3, 3); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_12(stride), l_pix4, 0); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_13(stride), l_pix4, 1); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_14(stride), l_pix4, 2); \
    intra_pred_16x16_HOR_avc_16pix(pCurr+FACTOR_15(stride), l_pix4, 3); \
}
#else
#define intra_pred_16x16_HOR_avc(pCurr, stride, blk_avail) \
{ \
    int j; \
    uint32 temp; \
    \
    for (j=0;j<16;j++) {		 \
        temp = *(pCurr-1); \
        temp = IBYTEDUP0(temp); \
        O_ABCD    = \
        CONVPUINTXTOUINT32(pCurr+4)  = \
        CONVPUINTXTOUINT32(pCurr+8)  = \
        CONVPUINTXTOUINT32(pCurr+12) = temp; \
        pCurr += stride; \
    }	 \
}
#endif
