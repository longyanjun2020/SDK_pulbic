#ifndef FILTER_H
#define FILTER_H

#define avc_EMC_4_00(X, b_y) \
    assert(b_y>0 && (b_y&1)==0); \
    y = b_y; \
    do { \
    y-=2; \
    ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
    ldst[s4] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
    ldst += s3; \
    lsrc += s1; \
    ldst2[0] = FUNSHIFT##X(lsrc2[1], lsrc2[0]); \
    ldst2[s4] = FUNSHIFT##X(lsrc2[s2+1], lsrc2[s2]); \
    ldst2 += s3; \
    lsrc2 += s1; \
    } while (y != 0);

#define FILTER_H0V0_x_n_ual(pSrc, pDst, X, h, v, src_stride, dst_stride) \
{ \
    int y = v; \
    int x = h; \
    int s1, s2, s3, d1, d2, d3; \
    const uint32 *RESTRICT lsrc = (uint32 *) (pSrc); \
    uint32 *RESTRICT ldst = (uint32 *) (pDst); \
    s1 = (src_stride)>>2; \
    s2 = (src_stride)>>1; \
    s3 = s1 + s2; \
    d1 = (dst_stride)>>2; \
    d2 = (dst_stride)>>1; \
    d3 = d1 + d2; \
    for (y=v; y!=0; y-=4, ldst += dst_stride, lsrc += src_stride) { \
REENTRY##X: \
        ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
        ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
        ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
        ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
        if (x==4) \
            continue; \
        ldst[1] = FUNSHIFT##X(lsrc[2], lsrc[1]); \
        ldst[d1+1] = FUNSHIFT##X(lsrc[s1+2], lsrc[s1+1]); \
        ldst[d2+1] = FUNSHIFT##X(lsrc[s2+2], lsrc[s2+1]); \
        ldst[d3+1] = FUNSHIFT##X(lsrc[s3+2], lsrc[s3+1]); \
        if (x==8) \
            continue; \
        if (x==0) { \
            x = 16; \
            ldst -= 2; \
            lsrc -= 2; \
            continue; \
        } \
        x = 0; \
        ldst += 2; \
        lsrc += 2; \
        goto REENTRY##X; \
    } \
}

#define FILTER_H0V0_x_n_al(pSrc, pDst, h, v, src_stride, dst_stride) \
{ \
    int x, y = v; \
    do { \
        for (x = 0; x < h; x += 4) { \
            LOAD32A((int32 *) (pDst + x), pSrc + x); \
        } \
        pSrc += src_stride; \
        pDst += dst_stride; \
    } while (--y); \
}

#if defined(_UAMEM_ACCESS_) //|| defined(_MIPS_)
#define FILTER_H0V0_x_n(pSrc, pDst, h, v, src_stride, dst_stride) \
    FILTER_H0V0_x_n_ual(pSrc, pDst, 4, h, v, src_stride, dst_stride);
#else
#define FILTER_H0V0_x_n(pSrc, pDst, h, v, src_stride, dst_stride) \
{ \
    int x, y = v; \
    do { \
        x = h; \
        do { \
            x -= 4; \
            LOAD32U(*(uint32 *)(pDst + x), pSrc + x, 0); \
        } while (x); \
        pSrc += src_stride; \
        pDst += dst_stride; \
    } while (--y); \
}
#endif

#ifdef _AG_S32_
#define FILTER_H0V0_16xn FILTER_H0V0_x_n
#define FILTER_H0V0_8xn FILTER_H0V0_x_n
#define FILTER_H0V0_4xn FILTER_H0V0_x_n

#else //_AG_S32_

#define FILTER_H0V0_16xn_ual(pSrc, pDst, X, h, v, src_stride, dst_stride) \
{ \
    int y = v; \
    int s1, s2, s3, d1, d2, d3; \
    const uint32 *RESTRICT lsrc = (uint32 *) (pSrc); \
    uint32 *RESTRICT ldst = (uint32 *) (pDst); \
    s1 = (src_stride)>>2; \
    s2 = (src_stride)>>1; \
    s3 = s1 + s2; \
    d1 = (dst_stride)>>2; \
    d2 = (dst_stride)>>1; \
    d3 = d1 + d2; \
    do { \
        ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
        ldst[1] = FUNSHIFT##X(lsrc[2], lsrc[1]); \
        ldst[2] = FUNSHIFT##X(lsrc[3], lsrc[2]); \
        ldst[3] = FUNSHIFT##X(lsrc[4], lsrc[3]); \
        ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
        ldst[d1+1] = FUNSHIFT##X(lsrc[s1+2], lsrc[s1+1]); \
        ldst[d1+2] = FUNSHIFT##X(lsrc[s1+3], lsrc[s1+2]); \
        ldst[d1+3] = FUNSHIFT##X(lsrc[s1+4], lsrc[s1+3]); \
        ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
        ldst[d2+1] = FUNSHIFT##X(lsrc[s2+2], lsrc[s2+1]); \
        ldst[d2+2] = FUNSHIFT##X(lsrc[s2+3], lsrc[s2+2]); \
        ldst[d2+3] = FUNSHIFT##X(lsrc[s2+4], lsrc[s2+3]); \
        ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
        ldst[d3+1] = FUNSHIFT##X(lsrc[s3+2], lsrc[s3+1]); \
        ldst[d3+2] = FUNSHIFT##X(lsrc[s3+3], lsrc[s3+2]); \
        ldst[d3+3] = FUNSHIFT##X(lsrc[s3+4], lsrc[s3+3]); \
        ldst += dst_stride; \
        lsrc += src_stride; \
        y -= 4; \
    } while (y != 0); \
}

#if defined(_UAMEM_ACCESS_) //|| defined(_MIPS_)
#define FILTER_H0V0_16xn(pSrc, pDst, h, v, src_stride, dst_stride) \
    FILTER_H0V0_16xn_ual(pSrc, pDst, 4, h, v, src_stride, dst_stride);
#else
#define FILTER_H0V0_16xn(pSrc, pDst, h, v, src_stride, dst_stride) \
{ \
    int t = (int)pSrc&0x3; \
    if (t == 0) { \
        FILTER_H0V0_16xn_ual(((int)pSrc/*^t*/), pDst, 4, h, v, src_stride, dst_stride); \
    } else if (t == 1) { \
        FILTER_H0V0_16xn_ual(((int)pSrc^t), pDst, 3, h, v, src_stride, dst_stride); \
    } else if (t == 2) { \
        FILTER_H0V0_16xn_ual(((int)pSrc^t), pDst, 2, h, v, src_stride, dst_stride); \
    } else { \
        FILTER_H0V0_16xn_ual(((int)pSrc^t), pDst, 1, h, v, src_stride, dst_stride); \
    } \
}
#endif

#define FILTER_H0V0_8xn_ual(pSrc, pDst, X, h, v, src_stride, dst_stride) \
{ \
    int y = v; \
    int s1, s2, s3, d1, d2, d3; \
    const uint32 *RESTRICT lsrc = (uint32 *) (pSrc); \
    uint32 *RESTRICT ldst = (uint32 *) (pDst); \
    \
    s1 = (src_stride)>>2; \
    s2 = (src_stride)>>1; \
    s3 = s1 + s2; \
    d1 = (dst_stride)>>2; \
    d2 = (dst_stride)>>1; \
    d3 = d1 + d2; \
    do { \
        ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
        ldst[1] = FUNSHIFT##X(lsrc[2], lsrc[1]); \
        ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
        ldst[d1+1] = FUNSHIFT##X(lsrc[s1+2], lsrc[s1+1]); \
        ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
        ldst[d2+1] = FUNSHIFT##X(lsrc[s2+2], lsrc[s2+1]); \
        ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
        ldst[d3+1] = FUNSHIFT##X(lsrc[s3+2], lsrc[s3+1]); \
        ldst += dst_stride; \
        lsrc += src_stride; \
        y -= 4; \
    } while (y != 0); \
}

#if defined(_UAMEM_ACCESS_) //|| defined(_MIPS_)
#define FILTER_H0V0_8xn(pSrc, pDst, h, v, src_stride, dst_stride) \
    FILTER_H0V0_8xn_ual(pSrc, pDst, 4, h, v, src_stride, dst_stride);
#else
#define FILTER_H0V0_8xn(pSrc, pDst, h, v, src_stride, dst_stride) \
{ \
    int t = (int)pSrc&0x3; \
    if (t == 0) { \
        FILTER_H0V0_8xn_ual((int)pSrc/*^t*/, pDst, 4, h, v, src_stride, dst_stride); \
    } else if (t == 1) { \
        FILTER_H0V0_8xn_ual((int)pSrc^t, pDst, 3, h, v, src_stride, dst_stride); \
    } else if (t == 2) { \
        FILTER_H0V0_8xn_ual((int)pSrc^t, pDst, 2, h, v, src_stride, dst_stride); \
    } else { \
        FILTER_H0V0_8xn_ual((int)pSrc^t, pDst, 1, h, v, src_stride, dst_stride); \
    } \
}
#endif

#define FILTER_H0V0_4xn_ual(pSrc, pDst, X, h, v, src_stride, dst_stride) \
{ \
    int y = v; \
    int s1, s2, s3, d1, d2, d3; \
    const uint32 *RESTRICT lsrc = (uint32 *) (pSrc); \
    uint32 *RESTRICT ldst = (uint32 *) (pDst); \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    do { \
        ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
        ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
        ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
        ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
        ldst += dst_stride; \
        lsrc += src_stride; \
        y -= 4; \
    } while (y != 0); \
}

#if defined(_UAMEM_ACCESS_) //|| defined(_MIPS_)
#define FILTER_H0V0_4xn(pSrc, pDst, h, v, src_stride, dst_stride) \
    FILTER_H0V0_4xn_ual(pSrc, pDst, 4, h, v, src_stride, dst_stride);
#else
#define FILTER_H0V0_4xn(pSrc, pDst, h, v, src_stride, dst_stride) \
{ \
    int t = (int)src&0x3; \
    if (t == 0) { \
        FILTER_H0V0_4xn(((int)src/*^t*/), dst, 4, h, v, stride, stride); \
    } else if (t == 1) { \
        FILTER_H0V0_4xn(((int)src^t), dst, 3, h, v, stride, stride); \
    } else if (t == 2) { \
        FILTER_H0V0_4xn(((int)src^t), dst, 2, h, v, stride, stride); \
    } else { \
        FILTER_H0V0_4xn(((int)src^t), dst, 1, h, v, stride, stride); \
    } \
}
#endif
#endif //_AG_S32_

/***************************************************/

#define AVC_8PEL_PACKBYTES(pos, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12) \
    p1 = PACKBYTES(*(pos+in2), *(pos+in1)); \
    p2 = PACKBYTES(*(pos+in4), *(pos+in3)); \
    p3 = PACKBYTES(*(pos+in6), *(pos+in5)); \
    p4 = PACKBYTES(*(pos+in8), *(pos+in7)); \
    p5 = PACKBYTES(*(pos+in10), *(pos+in9)); \
    p6 = PACKBYTES(*(pos+in12), *(pos+in11)); 

#define AVC_16PEL_PACKBYTES(pos, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, \
                            in11, in12, in13, in14, in15, in16, in17, in18, in19, in20) \
    p1 = PACKBYTES(*(pos+in2), *(pos+in1)); \
    p2 = PACKBYTES(*(pos+in4), *(pos+in3)); \
    p3 = PACKBYTES(*(pos+in6), *(pos+in5)); \
    p4 = PACKBYTES(*(pos+in8), *(pos+in7)); \
    p5 = PACKBYTES(*(pos+in10), *(pos+in9)); \
    p6 = PACKBYTES(*(pos+in12), *(pos+in11)); \
    p7 = PACKBYTES(*(pos+in14), *(pos+in13)); \
    p8 = PACKBYTES(*(pos+in16), *(pos+in15)); \
    p9 = PACKBYTES(*(pos+in18), *(pos+in17)); \
    p10 = PACKBYTES(*(pos+in20), *(pos+in19)); 

#define AVC_8PEL_PACK16LSB(in1, in2, in3, in4, in5, in6, in7) \
    in1 = PACK16LSB(in2, in1);\
    in2 = PACK16LSB(in3, in2);\
    in3 = PACK16LSB(in4, in3);\
    in4 = PACK16LSB(in5, in4);\
    in5 = PACK16LSB(in6, in5);\
    in6 = PACK16LSB(in7, in6);

#define AVC_16PEL_PACK16LSB(in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11) \
    in1 = PACK16LSB(in2, in1);\
    in2 = PACK16LSB(in3, in2);\
    in3 = PACK16LSB(in4, in3);\
    in4 = PACK16LSB(in5, in4);\
    in5 = PACK16LSB(in6, in5);\
    in6 = PACK16LSB(in7, in6);\
    in7 = PACK16LSB(in8, in7);\
    in8 = PACK16LSB(in9, in8);\
    in9 = PACK16LSB(in10, in9);\
    in10 = PACK16LSB(in11, in10);

#define AVC_8PEL_FILTERING(in1, in2, in3, in4, in5, in6, out1, out2, out3, out4, coef1, coef2, coef3, coef4) \
    temp_out1 = IFIR8UI(in1, coef4)+IFIR8UI(in2, coef1); \
    temp_out2 = IFIR8UI(in1, coef2)+IFIR8UI(in3, coef3); \
    out1 = PACK16LSB(temp_out2, temp_out1); \
    temp_out2 = IFIR8UI(in2, coef4)+IFIR8UI(in3, coef1); \
    temp_out3 = IFIR8UI(in2, coef2)+IFIR8UI(in4, coef3); \
    out2 = PACK16LSB(temp_out3, temp_out2); \
    temp_out3 = IFIR8UI(in3, coef4)+IFIR8UI(in4, coef1); \
    temp_out4 = IFIR8UI(in3, coef2)+IFIR8UI(in5, coef3); \
    out3 = PACK16LSB(temp_out4, temp_out3); \
    tmp = IFIR8UI(in4, coef4)+IFIR8UI(in5, coef1); \
    temp_out4 = IFIR8UI(in4, coef2)+IFIR8UI(in6, coef3); \
    out4 = PACK16LSB(temp_out4, tmp);

#define AVC_16PEL_FILTERING(in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, \
                            out1, out2, out3, out4, out5, out6, out7, out8, coef1, coef2, coef3, coef4) \
    temp_out1 = IFIR8UI(in1, coef4)+IFIR8UI(in2, coef1); \
    temp_out2 = IFIR8UI(in1, coef2)+IFIR8UI(in3, coef3); \
    out1 = PACK16LSB(temp_out2, temp_out1); \
    temp_out2 = IFIR8UI(in2, coef4)+IFIR8UI(in3, coef1); \
    temp_out3 = IFIR8UI(in2, coef2)+IFIR8UI(in4, coef3); \
    out2 = PACK16LSB(temp_out3, temp_out2); \
    temp_out3 = IFIR8UI(in3, coef4)+IFIR8UI(in4, coef1); \
    temp_out4 = IFIR8UI(in3, coef2)+IFIR8UI(in5, coef3); \
    out3 = PACK16LSB(temp_out4, temp_out3); \
    temp_out4 = IFIR8UI(in4, coef4)+IFIR8UI(in5, coef1); \
    temp_out5 = IFIR8UI(in4, coef2)+IFIR8UI(in6, coef3); \
    out4 = PACK16LSB(temp_out5, temp_out4); \
    temp_out5 = IFIR8UI(in5, coef4)+IFIR8UI(in6, coef1); \
    temp_out6 = IFIR8UI(in5, coef2)+IFIR8UI(in7, coef3); \
    out5 = PACK16LSB(temp_out6, temp_out5); \
    temp_out6 = IFIR8UI(in6, coef4)+IFIR8UI(in7, coef1); \
    temp_out7 = IFIR8UI(in6, coef2)+IFIR8UI(in8, coef3); \
    out6 = PACK16LSB(temp_out7, temp_out6); \
    temp_out7 = IFIR8UI(in7, coef4)+IFIR8UI(in8, coef1); \
    temp_out8 = IFIR8UI(in7, coef2)+IFIR8UI(in9, coef3); \
    out7 = PACK16LSB(temp_out8, temp_out7); \
    tmp = IFIR8UI(in8, coef4)+IFIR8UI(in9, coef1); \
    temp_out8 = IFIR8UI(in8, coef2)+IFIR8UI(in10, coef3); \
    out8 = PACK16LSB(temp_out8, tmp);

#define AVC_16PEL_PACKBYTES_NEW(pos, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, pos2, in12) \
    p1 = PACKBYTES(*(pos+in2), *(pos+in1)); \
    p2 = PACKBYTES(*(pos+in4), *(pos+in3)); \
    p3 = PACKBYTES(*(pos+in6), *(pos+in5)); \
    p4 = PACKBYTES(*(pos+in8), *(pos+in7)); \
    p5 = PACKBYTES(*(pos+in10), *(pos+in9)); \
    p6 = PACKBYTES(*(pos2+in4), *(pos+in11)); \
    p7 = PACKBYTES(*(pos2+in6), *(pos2+in5)); \
    p8 = PACKBYTES(*(pos2+in8), *(pos2+in7)); \
    p9 = PACKBYTES(*(pos2+in10), *(pos2+in9)); \
    p10 = PACKBYTES(*(pos2+in12), *(pos2+in11)); 

#define SPLITE_4BYTES(dst1, dst2, dst3, dst4, in1) \
    dst1 = (uchar)UBYTESEL(in1, 0); \
    dst2 = (uchar)UBYTESEL(in1, 1); \
    dst3 = (uchar)UBYTESEL(in1, 2); \
    dst4 = (uchar)UBYTESEL(in1, 3);

#define RV_HPEL_4PEL_VALUE_64(in1, in2) \
    in1 = DUALUCLIPI(DUALASR(DUALIADD(in1, 0x00200020), 6), 255); \
    in2 = DUALUCLIPI(DUALASR(DUALIADD(in2, 0x00200020), 6), 255); \
    in1 = MERGEDUAL16LSB(in2, in1); 

#define RV_HPEL_4PEL_VALUE_32(in1, in2) \
    in1 = DUALUCLIPI(DUALASR(DUALIADD(in1, 0x00100010), 5), 255); \
    in2 = DUALUCLIPI(DUALASR(DUALIADD(in2, 0x00100010), 5), 255); \
    in1 = MERGEDUAL16LSB(in2, in1); 


#define AVC_SECOND_FILTER_BYI16(a, b, c, d, e, f, ans) \
    m1 = DUALIADD(a, f); \
    m2 = DUALIADD(b, e); \
    m3 = DUALIADD(c, d); \
    m1 = DUALASR(DSPIDUALSUB(m1, m2),2); \
    m2 = DSPIDUALSUB(m3, m2); \
    m3 = DUALIADD(m3, 0x00200020); \
    m1 = DUALASR(DUALIADD(m1, m2), 2); \
    ans = DUALUCLIPI(DUALASR(DUALIADD(m1, m3), 6),255);

#define RV_FILTER_H2V0(a, b, c, d, e, f, ans) \
    m1 = DUALIADD(a, f); \
    m2 = DUALIADD(b, e); \
    m3 = DUALIADD(c, d); \
    m3 = DUALISUB(DUALASL(m3, 2), m2); \
    m3 = DUALIADD(DUALASL(m3, 2), m3); \
    ans = DUALUCLIPI(DUALASR(DUALIADD(DUALIADD(m1, m3), 0x00100010), 5), 255);

//coef_1_m5_20_0, coef_52_m5_1_0, coef_0_1_m5_20, coef_0_52_m5_1
#define RV_FILTER_H1V0(a, b, c, d, e, f, ans) \
    m1 = DUALIADD(a, f); \
    m2 = DUALIADD(b, e); \
    m3 = DUALIADD((c<<3)+(c<<2)+c, (d<<2)+d); \
    m2 = DUALIADD(DUALASL(m2, 2), m2); \
    m3 = DUALISUB(DUALASL(m3, 2), m2); \
    ans = DUALUCLIPI(DUALASR(DUALIADD(DUALIADD(m1, m3), 0x00200020), 6), 255);

#define RV_FILTER_H3V0(a, b, c, d, e, f, ans) \
    m1 = DUALIADD(a, f); \
    m2 = DUALIADD(b, e); \
    m3 = DUALIADD((c<<2)+c, (d<<3)+(d<<2)+d); \
    m2 = DUALIADD(DUALASL(m2, 2), m2); \
    m3 = DUALISUB(DUALASL(m3, 2), m2); \
    ans = DUALUCLIPI(DUALASR(DUALIADD(DUALIADD(m1, m3), 0x00200020), 6), 255);

#define RV_HPEL_12PEL_VALUE_32(t1, t2, t3, t4, t5, t6) \
    t1 = DUALUCLIPI(DUALASR(DUALIADD(t1, 0x00100010), 5), 255); \
    t2 = DUALUCLIPI(DUALASR(DUALIADD(t2, 0x00100010), 5), 255); \
    t3 = DUALUCLIPI(DUALASR(DUALIADD(t3, 0x00100010), 5), 255); \
    t4 = DUALUCLIPI(DUALASR(DUALIADD(t4, 0x00100010), 5), 255); \
    t5 = DUALUCLIPI(DUALASR(DUALIADD(t5, 0x00100010), 5), 255); \
    t6 = DUALUCLIPI(DUALASR(DUALIADD(t6, 0x00100010), 5), 255);

#define RV_HPEL_16PEL_VALUE_32(t1, t2, t3, t4, t5, t6, t7, t8) \
    t1 = DUALUCLIPI(DUALASR(DUALIADD(t1, 0x00100010), 5), 255); \
    t2 = DUALUCLIPI(DUALASR(DUALIADD(t2, 0x00100010), 5), 255); \
    t3 = DUALUCLIPI(DUALASR(DUALIADD(t3, 0x00100010), 5), 255); \
    t4 = DUALUCLIPI(DUALASR(DUALIADD(t4, 0x00100010), 5), 255); \
    t5 = DUALUCLIPI(DUALASR(DUALIADD(t5, 0x00100010), 5), 255); \
    t6 = DUALUCLIPI(DUALASR(DUALIADD(t6, 0x00100010), 5), 255); \
    t7 = DUALUCLIPI(DUALASR(DUALIADD(t7, 0x00100010), 5), 255); \
    t8 = DUALUCLIPI(DUALASR(DUALIADD(t8, 0x00100010), 5), 255);
    
#define RV_HPEL_16PEL_VALUE_64(t1, t2, t3, t4, t5, t6, t7, t8) \
    t1 = DUALUCLIPI(DUALASR(DUALIADD(t1, 0x00200020), 6), 255); \
    t2 = DUALUCLIPI(DUALASR(DUALIADD(t2, 0x00200020), 6), 255); \
    t3 = DUALUCLIPI(DUALASR(DUALIADD(t3, 0x00200020), 6), 255); \
    t4 = DUALUCLIPI(DUALASR(DUALIADD(t4, 0x00200020), 6), 255); \
    t5 = DUALUCLIPI(DUALASR(DUALIADD(t5, 0x00200020), 6), 255); \
    t6 = DUALUCLIPI(DUALASR(DUALIADD(t6, 0x00200020), 6), 255); \
    t7 = DUALUCLIPI(DUALASR(DUALIADD(t7, 0x00200020), 6), 255); \
    t8 = DUALUCLIPI(DUALASR(DUALIADD(t8, 0x00200020), 6), 255);

#define RV_HPEL_8PEL_VALUE_32(t1, t2, t3, t4) \
    t1 = DUALUCLIPI(DUALASR(DUALIADD(t1, 0x00100010), 5), 255); \
    t2 = DUALUCLIPI(DUALASR(DUALIADD(t2, 0x00100010), 5), 255); \
    t3 = DUALUCLIPI(DUALASR(DUALIADD(t3, 0x00100010), 5), 255); \
    t4 = DUALUCLIPI(DUALASR(DUALIADD(t4, 0x00100010), 5), 255);

#define RV_HPEL_8PEL_VALUE_64(t1, t2, t3, t4) \
    t1 = DUALUCLIPI(DUALASR(DUALIADD(t1, 0x00200020), 6), 255); \
    t2 = DUALUCLIPI(DUALASR(DUALIADD(t2, 0x00200020), 6), 255); \
    t3 = DUALUCLIPI(DUALASR(DUALIADD(t3, 0x00200020), 6), 255); \
    t4 = DUALUCLIPI(DUALASR(DUALIADD(t4, 0x00200020), 6), 255);
    
#define RV_H2V0_4PEL_VALUE(t11, t21, t31, t41, t51, t61, t12, t22, t32, t42, t52, t62) \
    d1 = RV_FILTER_H2V0(t11, t21, t31, t41, t51, t61, d1); \
    d2 = RV_FILTER_H2V0(t12, t22, t32, t42, t52, t62, d2); \
    r1 = MERGEDUAL16LSB(d2, d1);

#define RV_H1V0_4PEL_VALUE(t11, t21, t31, t41, t51, t61, t12, t22, t32, t42, t52, t62) \
    d1 = RV_FILTER_H1V0(t11, t21, t31, t41, t51, t61, d1); \
    d2 = RV_FILTER_H1V0(t12, t22, t32, t42, t52, t62, d2); \
    r1 = MERGEDUAL16LSB(d2, d1);

#define RV_H3V0_4PEL_VALUE(t11, t21, t31, t41, t51, t61, t12, t22, t32, t42, t52, t62) \
    d1 = RV_FILTER_H3V0(t11, t21, t31, t41, t51, t61, d1); \
    d2 = RV_FILTER_H3V0(t12, t22, t32, t42, t52, t62, d2); \
    r1 = MERGEDUAL16LSB(d2, d1);

#ifdef _UAMEM_ACCESS_
#define RV_HQV0_16xn(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int32 y; \
    const uchar *RESTRICT start = src; \
    uint32 * RESTRICT a1; \
    uint32 * RESTRICT a2; \
    uint32 * RESTRICT a3; \
    uint32 * RESTRICT a4; \
    uint32 * RESTRICT a5; \
    uint32 * RESTRICT a6; \
    uint32 /*p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, */t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2/*, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8*/; \
    \
    y = 0; \
    a1 = (uint32 * RESTRICT)(start-2); \
    a2 = (uint32 * RESTRICT)(start+2); \
    a3 = (uint32 * RESTRICT)(start+6); \
    a4 = (uint32 * RESTRICT)(start+10); \
    a5 = (uint32 * RESTRICT)(start+14); \
    a6 = (uint32 * RESTRICT)(start+15); \
    dst -= dst_stride; \
    do { \
        if (y!=0) { \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
            CONVUINTXTOUINT32(dst[8]) = t5; \
            CONVUINTXTOUINT32(dst[12]) = t7; \
        } \
        AVC_16PEL_FILTERING_2(a1[0], FUNSHIFT2(a2[0], a1[0]), a2[0], FUNSHIFT2(a3[0], a2[0]), \
                              a2[0], FUNSHIFT2(a3[0], a2[0]), a3[0], FUNSHIFT2(a4[0], a3[0]), \
                              a3[0], FUNSHIFT2(a4[0], a3[0]), a4[0], FUNSHIFT2(a5[0], a4[0]), \
                              a4[0], FUNSHIFT2(a5[0], a4[0]), a5[0], a6[0], \
                              t1, t2, t3, t4, t5, t6, t7, t8, coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        FIRST_FILTER_TYPE(t3, t4); \
        FIRST_FILTER_TYPE(t5, t6); \
        FIRST_FILTER_TYPE(t7, t8); \
        if (y==(v)) break; \
        start += src_stride; \
        dst += dst_stride; \
        y++; \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+10); \
        a5 = (uint32 * RESTRICT)(start+14); \
        a6 = (uint32 * RESTRICT)(start+15); \
    } while (y < v); \
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3; \
    CONVUINTXTOUINT32(dst[8]) = t5; \
    CONVUINTXTOUINT32(dst[12]) = t7;
#else
#define RV_HQV0_16xn(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int32 y; \
    const uchar *RESTRICT start = src; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8; \
 \
    y = 0; \
    AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
    AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
    do { \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        FIRST_FILTER_TYPE(t3, t4); \
        FIRST_FILTER_TYPE(t5, t6); \
        FIRST_FILTER_TYPE(t7, t8); \
        CONVUINTXTOUINT32(dst[0]) = t1; \
        CONVUINTXTOUINT32(dst[4]) = t3; \
        CONVUINTXTOUINT32(dst[8]) = t5; \
        CONVUINTXTOUINT32(dst[12]) = t7; \
        if (y==(v-1)) break; \
        start += src_stride; \
        dst += dst_stride; \
        y++; \
        AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
    } while (y < v);
#endif

#ifdef _UAMEM_ACCESS_
#define RV_HQV0_8xn(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int y; \
    const uchar *RESTRICT start1 = src-2; \
    const uchar *RESTRICT start2 = src+2; \
    const uchar *RESTRICT start3 = src+6; \
    const uchar *RESTRICT start4 = src+7; \
    uint32 a1, a2, a3, a4; \
    uint32 temp_out1, temp_out2; \
    uint32 t1, t2, t3, t4, tmp; \
 \
    y = 0; \
    a1 = *(uint32 * RESTRICT)(start1); \
    a2 = *(uint32 * RESTRICT)(start2); \
    a3 = *(uint32 * RESTRICT)(start3); \
    a4 = *(uint32 * RESTRICT)(start4); \
    dst -= dst_stride; \
    do { \
        if (y!=0) { \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
        } \
        AVC_8PEL_FILTERING_2(a1, FUNSHIFT2(a2, a1), a2, FUNSHIFT2(a3, a2), \
                             a2, FUNSHIFT2(a3, a2), a3, a4, t1, t2, t3, t4, coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        FIRST_FILTER_TYPE(t3, t4); \
        start1 += src_stride; \
        start2 += src_stride; \
        start3 += src_stride; \
        start4 += src_stride; \
        dst += dst_stride; \
        if (y==(v-1)) break; \
        a1 = *(uint32 * RESTRICT)(start1); \
        a2 = *(uint32 * RESTRICT)(start2); \
        a3 = *(uint32 * RESTRICT)(start3); \
        a4 = *(uint32 * RESTRICT)(start4); \
        y++; \
    } while (y < v); \
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3;
#else
#define RV_HQV0_8xn(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int32 y; \
    const uchar *RESTRICT start = src; \
    uint32 p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4; \
    \
    y = 0; \
    do { \
        AVC_8PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(start+10)); \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        FIRST_FILTER_TYPE(t3, t4); \
        CONVUINTXTOUINT32(dst[0]) = t1; \
        CONVUINTXTOUINT32(dst[4]) = t3; \
        start += src_stride; \
        dst += dst_stride; \
        y++; \
    } while (y < v);
#endif

#define RV_H0VQ_nx16(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8; \
    const uchar * RESTRICT src2; \
    int s16 = FACTOR_16(src_stride), s8 = FACTOR_8(src_stride), s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d16 = FACTOR_16(dst_stride), d8 = FACTOR_8(dst_stride), d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    \
    src2 = src+s8; \
    for (x = 0; x < h; x++) { \
        AVC_16PEL_PACKBYTES_NEW(src+x, -s2, -s, 0, s, s2, s2+s, s4, s4+s, s4+s2, s8-s, s8, src2+x, s8+s);  \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(src2+x+s8+s2));  \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, \
            coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
        FIRST_FILTER_TYPE(t3, t4); \
        SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d8-d], t3); \
        FIRST_FILTER_TYPE(t5, t6); \
        SPLITE_4BYTES(dst[d8], dst[d8+d], dst[d8+d2], dst[d8+d2+d], t5); \
        FIRST_FILTER_TYPE(t7, t8);  \
        SPLITE_4BYTES(dst[d8+d4], dst[d8+d4+d], dst[d16-d2], dst[d16-d], t7); \
        dst += 1; \
    }

#define RV_H0VQ_nx8(src, dst, h, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE) \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4; \
    int s8 = FACTOR_8(src_stride), s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d8 = FACTOR_8(dst_stride), d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    \
    for (x=0; x<h; x++) { \
        AVC_8PEL_PACKBYTES(src+x, -s2, -s, 0, s, s2, s2+s, s4, s4+s, s4+s2, s8-s, s8, s8+s);  \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(src+x+s8+s2));  \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t1, t2); \
        SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
        FIRST_FILTER_TYPE(t3, t4); \
        SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d8-d], t3); \
        dst += 1; \
    };

#ifdef _UAMEM_ACCESS_
#define RV_HQVQ_16xn(src, dst, v, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE, SECOND_FILTER_TYPE) \
    int x, y; \
    uint32 /*p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, */d1, d2, r1, m1, m2, m3, tmp; \
    uint32 temp_out1, temp_out2/*, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8*/; \
    int32 t[48]; \
    const uchar * RESTRICT start = src-(src_stride<<1); \
    uint32 * RESTRICT a1; \
    uint32 * RESTRICT a2; \
    uint32 * RESTRICT a3; \
    uint32 * RESTRICT a4; \
    uint32 * RESTRICT a5; \
    uint32 * RESTRICT a6; \
    uint32 s1, s2, s3, s4; \
    int swap, x0 = 0, x1 = 8, x2 = 16, x3 = 24, x4 = 32, x5 = 40; \
    a1 = (uint32 * RESTRICT)(start-2); \
    a2 = (uint32 * RESTRICT)(start+2); \
    a3 = (uint32 * RESTRICT)(start+6); \
    a4 = (uint32 * RESTRICT)(start+10); \
    a5 = (uint32 * RESTRICT)(start+14); \
    a6 = (uint32 * RESTRICT)(start+15); \
    x = 0; \
    do { \
        y = x << 3; \
        start += src_stride; \
        AVC_16PEL_FILTERING_2(a1[0], FUNSHIFT2(a2[0], a1[0]), a2[0], FUNSHIFT2(a3[0], a2[0]), \
                              a2[0], FUNSHIFT2(a3[0], a2[0]), a3[0], FUNSHIFT2(a4[0], a3[0]), \
                              a3[0], FUNSHIFT2(a4[0], a3[0]), a4[0], FUNSHIFT2(a5[0], a4[0]), \
                              a4[0], FUNSHIFT2(a5[0], a4[0]), a5[0], a6[0], \
                              t[y], t[y+1], t[y+2], t[y+3], t[y+4], t[y+5], t[y+6], t[y+7], coef1, coef2, coef3, coef4); \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+10); \
        a5 = (uint32 * RESTRICT)(start+14); \
        a6 = (uint32 * RESTRICT)(start+15); \
        x++; \
        FIRST_FILTER_TYPE(t[y], t[y+1], t[y+2], t[y+3], t[y+4], t[y+5], t[y+6], t[y+7]); \
    } while (x<6); \
    y = 0; \
    do { \
        SECOND_FILTER_TYPE(t[x0], t[x1], t[x2], t[x3], t[x4], t[x5], \
                            t[x0+1], t[x1+1], t[x2+1], t[x3+1], t[x4+1], t[x5+1]); \
        CONVUINTXTOUINT32(dst[0]) = r1; \
        SECOND_FILTER_TYPE(t[x0+2], t[x1+2], t[x2+2], t[x3+2], t[x4+2], t[x5+2], \
                            t[x0+3], t[x1+3], t[x2+3], t[x3+3], t[x4+3], t[x5+3]); \
        CONVUINTXTOUINT32(dst[4]) = r1; \
        SECOND_FILTER_TYPE(t[x0+4], t[x1+4], t[x2+4], t[x3+4], t[x4+4], t[x5+4], \
                            t[x0+5], t[x1+5], t[x2+5], t[x3+5], t[x4+5], t[x5+5]); \
        CONVUINTXTOUINT32(dst[8]) = r1; \
        SECOND_FILTER_TYPE(t[x0+6], t[x1+6], t[x2+6], t[x3+6], t[x4+6], t[x5+6], \
                            t[x0+7], t[x1+7], t[x2+7], t[x3+7], t[x4+7], t[x5+7]); \
        CONVUINTXTOUINT32(dst[12]) = r1; \
        y++; \
        if (y==v) break; \
        swap = x0; x0 = x1;  x1 = x2; x2 = x3; x3 = x4; x4 = x5; x5 = swap; \
        dst += dst_stride; \
        s1 = FUNSHIFT2(a2[0], a1[0]); \
        s2 = FUNSHIFT2(a3[0], a2[0]); \
        s3 = FUNSHIFT2(a4[0], a3[0]); \
        s4 = FUNSHIFT2(a5[0], a4[0]); \
        AVC_16PEL_FILTERING_2(a1[0], s1, a2[0], s2, a2[0], s2, a3[0], s3, \
                            a3[0], s3, a4[0], s4, a4[0], s4, a5[0], a6[0], \
                            t[x5], t[x5+1], t[x5+2], t[x5+3], t[x5+4], t[x5+5], t[x5+6], t[x5+7], coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[x5], t[x5+1], t[x5+2], t[x5+3], t[x5+4], t[x5+5], t[x5+6], t[x5+7]); \
        start += src_stride; \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+10); \
        a5 = (uint32 * RESTRICT)(start+14); \
        a6 = (uint32 * RESTRICT)(start+15); \
    } while (y<v);

#else
#define RV_HQVQ_16xn(src, dst, v, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE, SECOND_FILTER_TYPE) \
    int x, y; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, d1, d2, r1, m1, m2, m3, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8; \
    int32 t[48]; \
    const uchar * RESTRICT start = src-(src_stride<<1); \
    int swap, x0 = 0, x1 = 8, x2 = 16, x3 = 24, x4 = 32, x5 = 40; \
    for (x = 0 ; x < 5; x++) { \
        y = x << 3; \
        AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t[y], t[y+1], t[y+2], t[y+3], t[y+4], t[y+5], t[y+6], t[y+7], \
                            coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[y], t[y+1], t[y+2], t[y+3], t[y+4], t[y+5], t[y+6], t[y+7]); \
        start += src_stride; \
    } \
    AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
    AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
    for (y = 0; y < v; y++) { \
        start += src_stride; \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, \
        t[x5], t[x5+1], t[x5+2], t[x5+3], t[x5+4], t[x5+5], t[x5+6], t[x5+7], coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[x5], t[x5+1], t[x5+2], t[x5+3], t[x5+4], t[x5+5], t[x5+6], t[x5+7]); \
        SECOND_FILTER_TYPE(t[x0], t[x1], t[x2], t[x3], t[x4], t[x5], \
                           t[x0+1], t[x1+1], t[x2+1], t[x3+1], t[x4+1], t[x5+1]); \
        CONVUINTXTOUINT32(dst[0]) = r1; \
        SECOND_FILTER_TYPE(t[x0+2], t[x1+2], t[x2+2], t[x3+2], t[x4+2], t[x5+2], \
                           t[x0+3], t[x1+3], t[x2+3], t[x3+3], t[x4+3], t[x5+3]); \
        CONVUINTXTOUINT32(dst[4]) = r1; \
        SECOND_FILTER_TYPE(t[x0+4], t[x1+4], t[x2+4], t[x3+4], t[x4+4], t[x5+4], \
                           t[x0+5], t[x1+5], t[x2+5], t[x3+5], t[x4+5], t[x5+5]); \
        CONVUINTXTOUINT32(dst[8]) = r1; \
        SECOND_FILTER_TYPE(t[x0+6], t[x1+6], t[x2+6], t[x3+6], t[x4+6], t[x5+6], \
                           t[x0+7], t[x1+7], t[x2+7], t[x3+7], t[x4+7], t[x5+7]); \
        CONVUINTXTOUINT32(dst[12]) = r1; \
        AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
        swap = x0; x0 = x1; x1 = x2; x2 = x3; x3 = x4; x4 = x5; x5 = swap; \
        dst += dst_stride; \
    } 
#endif

#ifdef _UAMEM_ACCESS_
#define RV_HQVQ_8xn(src, dst, v, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE, SECOND_FILTER_TYPE) \
{ \
    int x, y; \
    uint32 /*p1, p2, p3, p4, p5, p6, */d1, d2, r1, m1, m2, m3, tmp; \
    int32 t[24]; \
    const uchar * RESTRICT start = src-(src_stride<<1); \
    uint32 * RESTRICT a1; \
    uint32 * RESTRICT a2; \
    uint32 * RESTRICT a3; \
    uint32 * RESTRICT a4; \
    uint32 temp_out1, temp_out2; \
    int32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    int32 t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23; \
    /*uint32 s1, s2, s3, s4; */\
    x=0; \
    y=0; \
    a1 = (uint32 * RESTRICT)(start-2); \
    a2 = (uint32 * RESTRICT)(start+2); \
    a3 = (uint32 * RESTRICT)(start+6); \
    a4 = (uint32 * RESTRICT)(start+7); \
    do { \
        start += src_stride; \
        AVC_8PEL_FILTERING_2(a1[0], FUNSHIFT2(a2[0], a1[0]), a2[0], FUNSHIFT2(a3[0], a2[0]), \
                            a2[0], FUNSHIFT2(a3[0], a2[0]), a3[0], a4[0], t[y], t[y+1], t[y+2], t[y+3], \
                            coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[y], t[y+1], t[y+2], t[y+3]); \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+7); \
        x++; \
        y=x<<2; \
    } while (x<6); \
    y = 0; \
    t0  = t[0];  t1  = t[1];  t2  = t[2];  t3  = t[3];  t4  = t[4];  \
    t5  = t[5];  t6  = t[6];  t7  = t[7];  t8  = t[8];  t9  = t[9];  \
    t10 = t[10]; t11 = t[11]; t12 = t[12]; t13 = t[13]; t14 = t[14]; \
    t15 = t[15]; t16 = t[16]; t17 = t[17]; t18 = t[18]; t19 = t[19]; \
    t20 = t[20]; t21 = t[21]; t22 = t[22]; t23 = t[23]; \
    do { \
        SECOND_FILTER_TYPE(t0, t4, t8, t12, t16, t20, \
                            t1, t5, t9, t13, t17, t21); \
        CONVUINTXTOUINT32(dst[0]) = r1; \
        SECOND_FILTER_TYPE(t2, t6, t10, t14, t18, t22, \
                            t3, t7, t11, t15, t19, t23); \
        CONVUINTXTOUINT32(dst[4]) = r1; \
        y++; \
        if (y==v) break; \
        dst += dst_stride; \
        t0 = t4; t4 = t8; t8 = t12; t12 = t16; t16 = t20; \
        t1 = t5; t5 = t9; t9 = t13; t13 = t17; t17 = t21; \
        t2 = t6; t6 = t10; t10 = t14; t14 = t18; t18 = t22; \
        t3 = t7; t7 = t11; t11 = t15; t15 = t19; t19 = t23; \
        start += src_stride; \
        AVC_8PEL_FILTERING_2(a1[0], FUNSHIFT2(a2[0], a1[0]), a2[0], FUNSHIFT2(a3[0], a2[0]), \
                            a2[0], FUNSHIFT2(a3[0], a2[0]), a3[0], a4[0], t20, t21, t22, t23, \
                            coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t20, t21, t22, t23); \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+7); \
    } while (y<v); \
}
#else
#define RV_HQVQ_8xn(src, dst, v, src_stride, dst_stride, coef1, coef2, coef3, coef4, FIRST_FILTER_TYPE, SECOND_FILTER_TYPE) \
    int x, y; \
    uint32 p1, p2, p3, p4, p5, p6, d1, d2, r1, m1, m2, m3, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4; \
    int32 t[48]; \
    const uchar * RESTRICT start = src-(src_stride<<1); \
    int swap, x0 = 0, x1 = 8, x2 = 16, x3 = 24, x4 = 32, x5 = 40; \
    for (x = 0 ; x < 5; x++) { \
        y = x << 3; \
        AVC_8PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(start+10)); \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t[y], t[y+1], t[y+2], t[y+3], coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[y], t[y+1], t[y+2], t[y+3]); \
        start += src_stride; \
    } \
    AVC_8PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); \
    AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(start+10)); \
    for (y = 0; y < v; y++) { \
        start += src_stride; \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t[x5], t[x5+1], t[x5+2], t[x5+3], coef1, coef2, coef3, coef4); \
        FIRST_FILTER_TYPE(t[x5], t[x5+1], t[x5+2], t[x5+3]); \
        SECOND_FILTER_TYPE(t[x0], t[x1], t[x2], t[x3], t[x4], t[x5], \
        t[x0+1], t[x1+1], t[x2+1], t[x3+1], t[x4+1], t[x5+1]); \
        CONVUINTXTOUINT32(dst[0]) = r1; \
        SECOND_FILTER_TYPE(t[x0+2], t[x1+2], t[x2+2], t[x3+2], t[x4+2], t[x5+2], \
        t[x0+3], t[x1+3], t[x2+3], t[x3+3], t[x4+3], t[x5+3]); \
        CONVUINTXTOUINT32(dst[4]) = r1; \
        AVC_8PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(start+10)); \
        swap = x0; x0 = x1; x1 = x2; x2 = x3; x3 = x4; x4 = x5; x5 = swap; \
        dst += dst_stride; \
    } 
#endif

/*****************************************************************************/


#ifdef _UAMEM_ACCESS_

#if 0 // remove one load by FUNSHIFT3
#define FILTER_BILINEAR_8(lsrc, tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    tmp += stride; \
    lsrc[1] = (uint32 * RESTRICT)(tmp); \
    lsrc[5] = (uint32 * RESTRICT)(tmp+4); \
    lsrc[7] = (uint32 * RESTRICT)(tmp+5); \
    m[0] = PACK16LSB(lsrc[0][0], lsrc[1][0]); \
    m[1] = PACK16LSB(FUNSHIFT3(lsrc[4][0], lsrc[0][0]), FUNSHIFT3(lsrc[5][0], lsrc[1][0])); \
    m[2] = PACK16MSB(lsrc[0][0], lsrc[1][0]); \
    m[3] = PACK16MSB(FUNSHIFT3(lsrc[4][0], lsrc[0][0]), FUNSHIFT3(lsrc[5][0], lsrc[1][0])); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    m[4] = PACK16LSB(lsrc[4][0], lsrc[5][0]); \
    m[5] = PACK16LSB(lsrc[6][0], lsrc[7][0]); \
    m[6] = PACK16MSB(lsrc[4][0], lsrc[5][0]); \
    m[7] = PACK16MSB(lsrc[6][0], lsrc[7][0]); \
    t5 = IFIR8UI(m[4], coef); \
    t6 = IFIR8UI(m[5], coef); \
    t7 = IFIR8UI(m[6], coef); \
    t8 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
    dst += dst_stride; \
    tmp += stride; \
    lsrc[0] = (uint32 * RESTRICT)(tmp); \
    lsrc[4] = (uint32 * RESTRICT)(tmp+4); \
    lsrc[6] = (uint32 * RESTRICT)(tmp+5); \
    m[4] = PACK16LSB(lsrc[1][0], lsrc[0][0]); \
    m[5] = PACK16LSB(FUNSHIFT3(lsrc[5][0], lsrc[1][0]), FUNSHIFT3(lsrc[4][0], lsrc[0][0])); \
    m[6] = PACK16MSB(lsrc[1][0], lsrc[0][0]); \
    m[7] = PACK16MSB(FUNSHIFT3(lsrc[5][0], lsrc[1][0]), FUNSHIFT3(lsrc[4][0], lsrc[0][0])); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    m[0] = PACK16LSB(lsrc[5][0], lsrc[4][0]); \
    m[1] = PACK16LSB(lsrc[7][0], lsrc[6][0]); \
    m[2] = PACK16MSB(lsrc[5][0], lsrc[4][0]); \
    m[3] = PACK16MSB(lsrc[7][0], lsrc[6][0]); \
    t5 = IFIR8UI(m[0], coef); \
    t6 = IFIR8UI(m[1], coef); \
    t7 = IFIR8UI(m[2], coef); \
    t8 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
    dst += dst_stride;
#else
#define FILTER_BILINEAR_8(lsrc, tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    tmp += stride; \
    lsrc[1] = (uint32 * RESTRICT)(tmp); \
    lsrc[3] = (uint32 * RESTRICT)(tmp+1); \
    lsrc[5] = (uint32 * RESTRICT)(tmp+4); \
    lsrc[7] = (uint32 * RESTRICT)(tmp+5); \
    m[0] = PACK16LSB(lsrc[0][0], lsrc[1][0]); \
    m[1] = PACK16LSB(lsrc[2][0], lsrc[3][0]); \
    m[2] = PACK16MSB(lsrc[0][0], lsrc[1][0]); \
    m[3] = PACK16MSB(lsrc[2][0], lsrc[3][0]); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    m[4] = PACK16LSB(lsrc[4][0], lsrc[5][0]); \
    m[5] = PACK16LSB(lsrc[6][0], lsrc[7][0]); \
    m[6] = PACK16MSB(lsrc[4][0], lsrc[5][0]); \
    m[7] = PACK16MSB(lsrc[6][0], lsrc[7][0]); \
    t5 = IFIR8UI(m[4], coef); \
    t6 = IFIR8UI(m[5], coef); \
    t7 = IFIR8UI(m[6], coef); \
    t8 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
    dst += dst_stride; \
    tmp += stride; \
    lsrc[0] = (uint32 * RESTRICT)(tmp); \
    lsrc[2] = (uint32 * RESTRICT)(tmp+1); \
    lsrc[4] = (uint32 * RESTRICT)(tmp+4); \
    lsrc[6] = (uint32 * RESTRICT)(tmp+5); \
    m[4] = PACK16LSB(lsrc[1][0], lsrc[0][0]); \
    m[5] = PACK16LSB(lsrc[3][0], lsrc[2][0]); \
    m[6] = PACK16MSB(lsrc[1][0], lsrc[0][0]); \
    m[7] = PACK16MSB(lsrc[3][0], lsrc[2][0]); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    m[0] = PACK16LSB(lsrc[5][0], lsrc[4][0]); \
    m[1] = PACK16LSB(lsrc[7][0], lsrc[6][0]); \
    m[2] = PACK16MSB(lsrc[5][0], lsrc[4][0]); \
    m[3] = PACK16MSB(lsrc[7][0], lsrc[6][0]); \
    t5 = IFIR8UI(m[0], coef); \
    t6 = IFIR8UI(m[1], coef); \
    t7 = IFIR8UI(m[2], coef); \
    t8 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
    dst += dst_stride;
#endif
#else
#define FILTER_BILINEAR_8(tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    m[1] = PACKBYTES(tmp[1], tmp[0]); \
    m[3] = PACKBYTES(tmp[2], tmp[1]); \
    m[5] = PACKBYTES(tmp[3], tmp[2]); \
    m[7] = PACKBYTES(tmp[4], tmp[3]); \
    m[9] = PACKBYTES(tmp[5], tmp[4]); \
    m[11] = PACKBYTES(tmp[6], tmp[5]); \
    m[13] = PACKBYTES(tmp[7], tmp[6]); \
    m[15] = PACKBYTES(tmp[8], tmp[7]); \
    tmp += stride; \
    t1 = IFIR8UI(PACK16LSB(m[0], m[1]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[2], m[3]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[4], m[5]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[6], m[7]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    t1 = IFIR8UI(PACK16LSB(m[8], m[9]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[10], m[11]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[12], m[13]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[14], m[15]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride; \
    m[0] = PACKBYTES(tmp[1], tmp[0]); \
    m[2] = PACKBYTES(tmp[2], tmp[1]); \
    m[4] = PACKBYTES(tmp[3], tmp[2]); \
    m[6] = PACKBYTES(tmp[4], tmp[3]); \
    m[8] = PACKBYTES(tmp[5], tmp[4]); \
    m[10] = PACKBYTES(tmp[6], tmp[5]); \
    m[12] = PACKBYTES(tmp[7], tmp[6]); \
    m[14] = PACKBYTES(tmp[8], tmp[7]); \
    tmp += stride; \
    t1 = IFIR8UI(PACK16LSB(m[1], m[0]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[3], m[2]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[5], m[4]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[7], m[6]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    t1 = IFIR8UI(PACK16LSB(m[9], m[8]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[11], m[10]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[13], m[12]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[15], m[14]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride;
#endif


#define avc_coef1 ((((int32) 1<<24)&0xff000000) | (((int32)(-5)<<16)&0x00ff0000) | (((int32)20<<8)&0x0000ff00))
#define avc_coef2 ((((int32)20<<24)&0xff000000) | (((int32)(-5)<<16)&0x00ff0000) | (((int32) 1<<8)&0x0000ff00))
#define avc_coef3 ((((int32) 1<<16)&0x00ff0000) | (((int32)(-5)<< 8)&0x0000ff00) | (((int32)20   )&0x000000ff))
#define avc_coef4 ((((int32)20<<16)&0x00ff0000) | (((int32)(-5)<< 8)&0x0000ff00) | (((int32) 1   )&0x000000ff))

#define coef1_1 ((((int32) 1<<24)&0xff000000) | (((int32)(-5)<<16)&0x00ff0000) | (((int32)20<<8)&0x0000ff00) | (((int32)16)&0x000000ff))
#define coef2_1 ((((int32)20<<24)&0xff000000) | (((int32)(-5)<<16)&0x00ff0000) | (((int32) 1<<8)&0x0000ff00)) 
#define coef3_1 ((((int32) 1<<16)&0x00ff0000) | (((int32)(-5)<< 8)&0x0000ff00) | (((int32)20   )&0x000000ff) | (((int32)16<<24)&0xff000000))
#define coef4_1 ((((int32)20<<16)&0x00ff0000) | (((int32)(-5)<< 8)&0x0000ff00) | (((int32) 1   )&0x000000ff))

#define AVC_4PEL_FILTERING_NEW(in1, in2, in3, in4, in5, in6, in7, in8, out1, out2) \
    out1 = IFIR8UI(in1, coef4_1)+IFIR8UI(in5, coef1_1); \
    out2 = IFIR8UI(in2, coef2_1)+IFIR8UI(in6, coef3_1); \
    out1 = PACK16LSB(out2, out1); \
    tmp = IFIR8UI(in3, coef4_1)+IFIR8UI(in7, coef1_1); \
    out2 = IFIR8UI(in4, coef2_1)+IFIR8UI(in8, coef3_1); \
    out2 = PACK16LSB(out2, tmp);

#define AVC_HPEL_4PEL_VALUE_NEW(in1, in2) \
    in1 = DUALUCLIPI(DUALASR(in1, 5), 255); \
    in2 = DUALUCLIPI(DUALASR(in2, 5), 255); \
    in1 = MERGEDUAL16LSB(in2, in1); 
    
#ifdef _UAMEM_ACCESS_
#define FILTER_H2V0_8xn(src, dst, h, v, src_stride, dst_stride) \
{ \
    int y; \
    const uchar *RESTRICT start = src; \
    const uchar *RESTRICT start1, *RESTRICT start2, *RESTRICT start3, *RESTRICT start4; \
    const uchar *RESTRICT start5, *RESTRICT start6, *RESTRICT start7, *RESTRICT start8; \
    uint32 /*p1, p2, p3, p4, p5, p6, */t1, t2, t3, t4, tmp; \
    uint32 /** RESTRICT */a1; \
    uint32 /** RESTRICT */a2; \
    uint32 /** RESTRICT */a3; \
    uint32 /** RESTRICT */a4; \
    uint32 /** RESTRICT */a5; \
    uint32 /** RESTRICT */a6; \
    uint32 /** RESTRICT */a7; \
    uint32 /** RESTRICT */a8; \
    uint32 c=0x01010101; \
    y = 0; \
    start1 = src-2; \
    start2 = src; \
    start3 = src+1; \
    start4 = src+3; \
    start5 = src+2; \
    start6 = src+4; \
    start7 = src+5; \
    start8 = src+7; \
    a1 = *(uint32 * RESTRICT)(start1); \
    a2 = *(uint32 * RESTRICT)(start2); \
    a3 = *(uint32 * RESTRICT)(start3); \
    a4 = *(uint32 * RESTRICT)(start4); \
    a5 = *(uint32 * RESTRICT)(start5); \
    dst -= dst_stride; \
    do { \
        a6 = *(uint32 * RESTRICT)(start6); \
        a7 = *(uint32 * RESTRICT)(start7); \
        a8 = *(uint32 * RESTRICT)(start8); \
        if (y!=0) { \
            AVC_HPEL_4PEL_VALUE_NEW(t1, t2); \
            AVC_HPEL_4PEL_VALUE_NEW(t3, t4); \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
        } \
        AVC_4PEL_FILTERING_NEW(a1, a1, a2, a2, FUNSHIFT1(a3, c), FUNSHIFT3(c, a3), FUNSHIFT1(a4, c), FUNSHIFT3(c, a4), t1, t2); \
        AVC_4PEL_FILTERING_NEW(a5, a5, a6, a6, FUNSHIFT1(a7, c), FUNSHIFT3(c, a7), FUNSHIFT1(a8, c), FUNSHIFT3(c, a8), t3, t4); \
        if (y==v) break; \
        y++; \
        dst += dst_stride; \
        start1 += src_stride; \
        start2 += src_stride; \
        start3 += src_stride; \
        start4 += src_stride; \
        start5 += src_stride; \
        start6 += src_stride; \
        start7 += src_stride; \
        start8 += src_stride; \
        a1 = *(uint32 * RESTRICT)(start1); \
        a2 = *(uint32 * RESTRICT)(start2); \
        a3 = *(uint32 * RESTRICT)(start3); \
        a4 = *(uint32 * RESTRICT)(start4); \
        a5 = *(uint32 * RESTRICT)(start5); \
    } while (y < v);\
    AVC_HPEL_4PEL_VALUE_NEW(t1, t2); \
    AVC_HPEL_4PEL_VALUE_NEW(t3, t4); \
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3; \
}
#else
#define FILTER_H2V0_8xn(src, dst, h, v, src_stride, dst_stride) \
{ \
    int y; \
    const uchar *RESTRICT start = src; \
    uint32 p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4; \
    y = 0; \
    dst -= dst_stride; \
    do { \
        AVC_8PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(start+10)); \
        start += src_stride; \
        if (y != 0) { \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
        } \
        dst += dst_stride; \
        y++; \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        AVC_HPEL_4PEL_VALUE(t1, t2); \
        AVC_HPEL_4PEL_VALUE(t3, t4); \
    } while (y < v);\
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3; \
}
#endif

#define AVC_4PEL_FILTERING(in1, in2, in3, in4, out1, out2, coef1, coef2, coef3, coef4) \
    temp_out1 = IFIR8UI(in1, coef4)+IFIR8UI(in2, coef1); \
    temp_out2 = IFIR8UI(in1, coef2)+IFIR8UI(in3, coef3); \
    out1 = PACK16LSB(temp_out2, temp_out1); \
    tmp = IFIR8UI(in2, coef4)+IFIR8UI(in3, coef1); \
    temp_out2 = IFIR8UI(in2, coef2)+IFIR8UI(in4, coef3); \
    out2 = PACK16LSB(temp_out2, tmp);

#define AVC_4PEL_FILTERING_2(in1, in2, in3, in4, out1, out2, coef1, coef2, coef3, coef4) \
    temp_out1 = IFIR8UI(in1, coef4)+IFIR8UI(in2, coef1); \
    temp_out2 = IFIR8UI(in1, coef2)+IFIR8UI(in3, coef3); \
    out1 = PACK16LSB(temp_out2, temp_out1); \
    tmp = IFIR8UI(in2, coef4)+IFIR8UI(in3, coef1); \
    temp_out2 = IFIR8UI(in2, coef2)+IFIR8UI(in4, coef1); \
    out2 = PACK16LSB(temp_out2, tmp);

#define AVC_8PEL_FILTERING_2(in1, in2, in3, in4, in5, in6, in7, in8, out1, out2, out3, out4, coef1, coef2, coef3, coef4) \
    AVC_4PEL_FILTERING(in1, in2, in3, in4, out1, out2, coef1, coef2, coef3, coef4); \
    AVC_4PEL_FILTERING_2(in5, in6, in7, in8, out3, out4, coef1, coef2, coef3, coef4);

#define AVC_16PEL_FILTERING_2(in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, in16, \
    out1, out2, out3, out4, out5, out6, out7, out8, coef1, coef2, coef3, coef4) \
    AVC_4PEL_FILTERING(in1, in2, in3, in4, out1, out2, coef1, coef2, coef3, coef4); \
    AVC_4PEL_FILTERING(in5, in6, in7, in8, out3, out4, coef1, coef2, coef3, coef4); \
    AVC_4PEL_FILTERING(in9, in10, in11, in12, out5, out6, coef1, coef2, coef3, coef4); \
    AVC_4PEL_FILTERING_2(in13, in14, in15, in16, out7, out8, coef1, coef2, coef3, coef4);

#define AVC_HPEL_4PEL_VALUE(in1, in2) \
    in1 = DUALUCLIPI(DUALASR(DUALIADD(in1, 0x00100010), 5), 255); \
    in2 = DUALUCLIPI(DUALASR(DUALIADD(in2, 0x00100010), 5), 255); \
    in1 = MERGEDUAL16LSB(in2, in1); 


#ifdef _UAMEM_ACCESS_
// 10/31 with preload, 8/33 without preload
#define FILTER_H2V0_16xn(src, dst, h, v, src_stride, dst_stride) \
{ \
    int y; \
    const uchar *RESTRICT start = src; \
    uint32 /*p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, */t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2; \
    uint32 * RESTRICT a1; \
    uint32 * RESTRICT a2; \
    uint32 * RESTRICT a3; \
    uint32 * RESTRICT a4; \
    uint32 * RESTRICT a5; \
    uint32 * RESTRICT a6; \
    y = 0; \
    dst -= dst_stride; \
    a1 = (uint32 * RESTRICT)(start-2); \
    a2 = (uint32 * RESTRICT)(start+2); \
    a3 = (uint32 * RESTRICT)(start+6); \
    a4 = (uint32 * RESTRICT)(start+10); \
    a5 = (uint32 * RESTRICT)(start+14); \
    a6 = (uint32 * RESTRICT)(start+15); \
    do { \
        if (y != 0) { \
            AVC_HPEL_4PEL_VALUE(t1, t2); \
            AVC_HPEL_4PEL_VALUE(t3, t4); \
            AVC_HPEL_4PEL_VALUE(t5, t6); \
            AVC_HPEL_4PEL_VALUE(t7, t8); \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
            CONVUINTXTOUINT32(dst[8]) = t5; \
            CONVUINTXTOUINT32(dst[12]) = t7; \
        } \
        dst += dst_stride; \
        AVC_16PEL_FILTERING_2(a1[0], FUNSHIFT2(a2[0], a1[0]), a2[0], FUNSHIFT2(a3[0], a2[0]), \
                              a2[0], FUNSHIFT2(a3[0], a2[0]), a3[0], FUNSHIFT2(a4[0], a3[0]), \
                              a3[0], FUNSHIFT2(a4[0], a3[0]), a4[0], FUNSHIFT2(a5[0], a4[0]), \
                              a4[0], FUNSHIFT2(a5[0], a4[0]), a5[0], a6[0], t1, t2, t3, t4, t5, t6, t7, t8, \
                              avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        y++; \
        if (y==v) \
            break; \
        start += src_stride; \
        a1 = (uint32 * RESTRICT)(start-2); \
        a2 = (uint32 * RESTRICT)(start+2); \
        a3 = (uint32 * RESTRICT)(start+6); \
        a4 = (uint32 * RESTRICT)(start+10); \
        a5 = (uint32 * RESTRICT)(start+14); \
        a6 = (uint32 * RESTRICT)(start+15); \
    } while (y < v);\
    AVC_HPEL_4PEL_VALUE(t1, t2); \
    AVC_HPEL_4PEL_VALUE(t3, t4); \
    AVC_HPEL_4PEL_VALUE(t5, t6); \
    AVC_HPEL_4PEL_VALUE(t7, t8); \
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3; \
    CONVUINTXTOUINT32(dst[8]) = t5; \
    CONVUINTXTOUINT32(dst[12]) = t7; \
}
#else
#define FILTER_H2V0_16xn(src, dst, h, v, src_stride, dst_stride) \
{ \
    int y; \
    const uchar *RESTRICT start = src; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8; \
    y = 0; \
    dst -= dst_stride; \
    do { \
        AVC_16PEL_PACKBYTES(start, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(start+18)); \
        if (y != 0) { \
            CONVUINTXTOUINT32(dst[0]) = t1; \
            CONVUINTXTOUINT32(dst[4]) = t3; \
            CONVUINTXTOUINT32(dst[8]) = t5; \
            CONVUINTXTOUINT32(dst[12]) = t7; \
        } \
        dst += dst_stride; \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, t1, t2, t3, t4, t5, t6, t7, t8, \
                            avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        y++; \
        start += src_stride; \
        AVC_HPEL_4PEL_VALUE(t1, t2); \
        AVC_HPEL_4PEL_VALUE(t3, t4); \
        AVC_HPEL_4PEL_VALUE(t5, t6); \
        AVC_HPEL_4PEL_VALUE(t7, t8); \
    } while (y < v);\
    CONVUINTXTOUINT32(dst[0]) = t1; \
    CONVUINTXTOUINT32(dst[4]) = t3; \
    CONVUINTXTOUINT32(dst[8]) = t5; \
    CONVUINTXTOUINT32(dst[12]) = t7; \
}
#endif

#if 1//def _UAMEM_ACCESS_ // always aligned
#define FILTER_H0V2_nx8(src, dst, h, v, src_stride, dst_stride) \
{ \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, t1=0, t2=0, t3=0, t4=0, tmp; \
    int s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    const uchar *RESTRICT src2 = src+s4; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4 ; \
    x = 0; \
    dst -= 1; \
    p1 = PACKBYTES(*(src2+x-(s4+s)), *(src2+x-(s4+s2))); \
    p2 = PACKBYTES(*(src2+x-(s2+s)), *(src2+x-s4)); \
    p3 = PACKBYTES(*(src2+x-s), *(src2+x-s2)); \
    p4 = PACKBYTES(*(src2+x+s), *(src2+x+0)); \
    do { \
        p5 = PACKBYTES(*(src2+x+(s2+s)), *(src2+x+s2)); \
        p6 = PACKBYTES(*(src2+x+(s4+s)), *(src2+x+s4)); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(src2+x+(s4+s2))); \
        if (x != 0) { \
            AVC_HPEL_4PEL_VALUE(t1, t2); \
            AVC_HPEL_4PEL_VALUE(t3, t4); \
            SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
            SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d4+d2+d], t3); \
        } \
        dst += 1; \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        x++; \
        p1 = PACKBYTES(*(src2+x-(s4+s)), *(src2+x-(s4+s2))); \
        p2 = PACKBYTES(*(src2+x-(s2+s)), *(src2+x-s4)); \
        p3 = PACKBYTES(*(src2+x-s), *(src2+x-s2)); \
        p4 = PACKBYTES(*(src2+x+s), *(src2+x+0)); \
    } while (x < h); \
    AVC_HPEL_4PEL_VALUE(t1, t2); \
    AVC_HPEL_4PEL_VALUE(t3, t4); \
    SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
    SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d4+d2+d], t3); \
}
#else
#define FILTER_H0V2_nx8(src, dst, h, v, src_stride, dst_stride) \
{ \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, t1=0, t2=0, t3=0, t4=0, tmp; \
    int s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    const uchar *RESTRICT src2 = src+s4; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4; \
    x = 0; \
    dst -= 1; \
    do { \
        AVC_8PEL_PACKBYTES(src2+x, -(s4+s2), -(s4+s), -s4, -(s2+s), -s2, -s, 0, s, s2, (s2+s), s4, (s4+s)); \
        AVC_8PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, *(src2+x+(s4+s2))); \
        if (x != 0) { \
            AVC_HPEL_4PEL_VALUE(t1, t2); \
            AVC_HPEL_4PEL_VALUE(t3, t4); \
            SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
            SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d4+d2+d], t3); \
        } \
        dst += 1; \
        AVC_8PEL_FILTERING(p1, p2, p3, p4, p5, p6, t1, t2, t3, t4, avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        x++; \
    } while (x < h); \
    AVC_HPEL_4PEL_VALUE(t1, t2); \
    AVC_HPEL_4PEL_VALUE(t3, t4); \
    SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
    SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d4+d2+d], t3); \
}
#endif

#if 1 //def _UAMEM_ACCESS_ // always aligned
#define FILTER_H0V2_nx16(src, dst, h, v, src_stride, dst_stride) \
{ \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10; \
    uint32 t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8 ; \
    int s16 = FACTOR_16(src_stride), s8 = FACTOR_8(src_stride), s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d16 = FACTOR_16(dst_stride), d8 = FACTOR_8(dst_stride), d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    const uchar *RESTRICT src2 = src+s8; \
    x = 0 ; \
    p1 = PACKBYTES(*(src+x-s), *(src+x-s2)); \
    p2 = PACKBYTES(*(src+x+s), *(src+x+0)); \
    p3 = PACKBYTES(*(src+x+s2+s), *(src+x+s2)); \
    p4 = PACKBYTES(*(src+x+s4+s), *(src+x+s4)); \
    p5 = PACKBYTES(*(src+x+s8-s), *(src+x+s4+s2)); \
    p6 = PACKBYTES(*(src2+x+s), *(src+x+s8)); \
    p7 = PACKBYTES(*(src2+x+s2+s), *(src2+x+s2)); \
    do {\
        p8 = PACKBYTES(*(src2+x+s4+s), *(src2+x+s4)); \
        p9 = PACKBYTES(*(src2+x+s8-s), *(src2+x+s4+s2)); \
        p10 = PACKBYTES(*(src2+x+s8+s), *(src2+x+s8)); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(src2+x+s8+s2)); \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, \
                            t1, t2, t3, t4, t5, t6, t7, t8, avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        AVC_HPEL_4PEL_VALUE(t1, t2); \
        SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
        AVC_HPEL_4PEL_VALUE(t3, t4); \
        SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d8-d], t3); \
        AVC_HPEL_4PEL_VALUE(t5, t6); \
        SPLITE_4BYTES(dst[d8], dst[d8+d], dst[d8+d2], dst[d8+d2+d], t5); \
        AVC_HPEL_4PEL_VALUE(t7, t8);  \
        SPLITE_4BYTES(dst[d8+d4], dst[d8+d4+d], dst[d16-d2], dst[d16-d], t7); \
        dst += 1; \
        x++; \
        p1 = PACKBYTES(*(src+x-s), *(src+x-s2)); \
        p2 = PACKBYTES(*(src+x+s), *(src+x+0)); \
        p3 = PACKBYTES(*(src+x+s2+s), *(src+x+s2)); \
        p4 = PACKBYTES(*(src+x+s4+s), *(src+x+s4)); \
        p5 = PACKBYTES(*(src+x+s8-s), *(src+x+s4+s2)); \
        p6 = PACKBYTES(*(src2+x+s), *(src+x+s8)); \
        p7 = PACKBYTES(*(src2+x+s2+s), *(src2+x+s2)); \
    } while (x<h); \
}
#else
#define FILTER_H0V2_nx16(src, dst, h, v, src_stride, dst_stride) \
{ \
    int x; \
    uint32 p1, p2, p3, p4, p5, p6, p7, p8, p9, p10; \
    uint32 t1, t2, t3, t4, t5, t6, t7, t8, tmp; \
    uint32 temp_out1, temp_out2, temp_out3, temp_out4, temp_out5, temp_out6, temp_out7, temp_out8 ; \
    int s16 = FACTOR_16(src_stride), s8 = FACTOR_8(src_stride), s4 = FACTOR_4(src_stride), s2 = FACTOR_2(src_stride), s = src_stride; \
    int d16 = FACTOR_16(dst_stride), d8 = FACTOR_8(dst_stride), d4 = FACTOR_4(dst_stride), d2 = FACTOR_2(dst_stride), d = dst_stride; \
    const uchar *RESTRICT src2 = src+s8; \
    for (x = 0; x < h; x++) {\
        AVC_16PEL_PACKBYTES_NEW(src+x, -s2, -s, 0, s, s2, s2+s, s4, s4+s, s4+s2, s8-s, s8, src2+x, s8+s); \
        AVC_16PEL_PACK16LSB(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, *(src2+x+s8+s2)); \
        AVC_16PEL_FILTERING(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, \
                            t1, t2, t3, t4, t5, t6, t7, t8, avc_coef1, avc_coef2, avc_coef3, avc_coef4); \
        AVC_HPEL_4PEL_VALUE(t1, t2); \
        SPLITE_4BYTES(dst[0], dst[d], dst[d2], dst[d2+d], t1); \
        AVC_HPEL_4PEL_VALUE(t3, t4); \
        SPLITE_4BYTES(dst[d4], dst[d4+d], dst[d4+d2], dst[d8-d], t3); \
        AVC_HPEL_4PEL_VALUE(t5, t6); \
        SPLITE_4BYTES(dst[d8], dst[d8+d], dst[d8+d2], dst[d8+d2+d], t5); \
        AVC_HPEL_4PEL_VALUE(t7, t8);  \
        SPLITE_4BYTES(dst[d8+d4], dst[d8+d4+d], dst[d16-d2], dst[d16-d], t7); \
        dst += 1; \
    } \
}
#endif

/*********************************************************************************/
#define wmv3_QF4_new_2(dst, reg_a, reg_b, reg_c, reg_d, shift, rounding, factor) \
    tt1 = IFIR8UI(reg_a, factor);\
    tt2 = IFIR8UI(reg_b, factor);\
    tt3 = PACK16LSB(tt2, tt1);\
    tt3 = DUALASR(DUALIADD(tt3, rounding), shift);\
    tt3 = DUALUCLIPI(tt3, 255);\
    tt1 = IFIR8UI(reg_c, factor);\
    tt2 = IFIR8UI(reg_d, factor);\
    tt4 = PACK16LSB(tt2, tt1);\
    tt4 = DUALASR(DUALIADD(tt4, rounding), shift);\
    tt4 = DUALUCLIPI(tt4, 255);\
    dst = MERGEDUAL16LSB(tt4, tt3);

#define RV_PACK8_tm5250(src) \
    d1 = *(src); \
    d2 = *(src+1); \
    d3 = *(src+2); \
    reg0 = d1; \
    reg1 = FUNSHIFT3(d2, d1); \
    reg2 = FUNSHIFT2(d2, d1); \
    reg3 = FUNSHIFT1(d2, d1); \
    reg4 = d2; \
    reg5 = FUNSHIFT3(d3, d2); \
    reg6 = FUNSHIFT2(d3, d2); \
    reg7 = FUNSHIFT1(d3, d2);

#define RV_PACK8_tm3260(src) \
    reg0 = make_uint32(*(src+2), *(src+1), *(src), *(src-1)); \
    reg1 = make_uint32(*(src+3), *(src+2), *(src+1), *(src)); \
    reg2 = make_uint32(*(src+4), *(src+3), *(src+2), *(src+1)); \
    reg3 = make_uint32(*(src+5), *(src+4), *(src+3), *(src+2)); \
    reg4 = make_uint32(*(src+6), *(src+5), *(src+4), *(src+3)); \
    reg5 = make_uint32(*(src+7), *(src+6), *(src+5), *(src+4)); \
    reg6 = make_uint32(*(src+8), *(src+7), *(src+6), *(src+5)); \
    reg7 = make_uint32(*(src+9), *(src+8), *(src+7), *(src+6));

#define RV_PACK16_tm5250(src) \
    d1 = *(src); \
    d2 = *(src+1); \
    d3 = *(src+2); \
    d4 = *(src+3); \
    d5 = *(src+4); \
    reg0 = d1; \
    reg1 = FUNSHIFT3(d2, d1); \
    reg2 = FUNSHIFT2(d2, d1); \
    reg3 = FUNSHIFT1(d2, d1); \
    reg4 = d2; \
    reg5 = FUNSHIFT3(d3, d2); \
    reg6 = FUNSHIFT2(d3, d2); \
    reg7 = FUNSHIFT1(d3, d2); \
    reg8 = d3; \
    reg9 = FUNSHIFT3(d4, d3); \
    reg10= FUNSHIFT2(d4, d3); \
    reg11= FUNSHIFT1(d4, d3); \
    reg12= d4; \
    reg13= FUNSHIFT3(d5, d4); \
    reg14= FUNSHIFT2(d5, d4); \
    reg15= FUNSHIFT1(d5, d4);

#define RV_PACK16_tm3260(src) \
    reg0 = make_uint32(*(src+2), *(src+1), *(src), *(src-1)); \
    reg1 = make_uint32(*(src+3), *(src+2), *(src+1), *(src)); \
    reg2 = make_uint32(*(src+4), *(src+3), *(src+2), *(src+1)); \
    reg3 = make_uint32(*(src+5), *(src+4), *(src+3), *(src+2)); \
    reg4 = make_uint32(*(src+6), *(src+5), *(src+4), *(src+3)); \
    reg5 = make_uint32(*(src+7), *(src+6), *(src+5), *(src+4)); \
    reg6 = make_uint32(*(src+8), *(src+7), *(src+6), *(src+5)); \
    reg7 = make_uint32(*(src+9), *(src+8), *(src+7), *(src+6)); \
    reg8 = make_uint32(*(src+10), *(src+9), *(src+8), *(src+7)); \
    reg9 = make_uint32(*(src+11), *(src+10), *(src+9), *(src+8)); \
    reg10 = make_uint32(*(src+12), *(src+11), *(src+10), *(src+9)); \
    reg11 = make_uint32(*(src+13), *(src+12), *(src+11), *(src+10)); \
    reg12 = make_uint32(*(src+14), *(src+13), *(src+12), *(src+11)); \
    reg13 = make_uint32(*(src+15), *(src+14), *(src+13), *(src+12)); \
    reg14 = make_uint32(*(src+16), *(src+15), *(src+14), *(src+13)); \
    reg15 = make_uint32(*(src+17), *(src+16), *(src+15), *(src+14));

#define matrixTranspose( i1,  i2,  i3,  i4,  o1,  o2,  o3,  o4) \
{ \
    int tmp; \
    o1 = MERGEMSB(i1, i2); \
    o2 = MERGEMSB(i3, i4); \
    o3 = MERGELSB(i1, i2); \
    o4 = MERGELSB(i3, i4); \
    tmp = PACK16MSB(o1,o2); \
    o2 = PACK16LSB(o1,o2); \
    o1 = tmp; \
    tmp = PACK16MSB(o3,o4); \
    o4 = PACK16LSB(o3,o4); \
    o3 = tmp; \
}

#define wmv3_CopyBlockQV_16_16_Template(src, dst, stride, dst_stride, rounding, shift, factor, v)\
{ \
    const uint32 * RESTRICT lSrc = (uint32 *) (src-stride); \
    uint32 * RESTRICT lDst = (uint32 *) dst; \
    int lStride = stride >> 2; \
    int dStride = dst_stride >> 2; \
    int32 tt1, tt2, tt3, tt4; \
    int y = 0; \
    \
    uint32 blk_1_H0, blk_1_H1, blk_1_H2, blk_1_H3;\
    uint32 blk_2_H0, blk_2_H1, blk_2_H2, blk_2_H3;\
    uint32 blk_3_H0, blk_3_H1, blk_3_H2, blk_3_H3;\
    uint32 blk_4_H0, blk_4_H1, blk_4_H2, blk_4_H3;\
    \
    uint32 blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0; \
    uint32 blk_5_H0, blk_6_H0, blk_7_H0, blk_8_H0; \
    \
    blk_1_H0 = lSrc[0]; \
    blk_1_H1 = lSrc[lStride]; \
    blk_1_H2 = lSrc[FACTOR_2(lStride)]; \
    \
    blk_2_H0 = lSrc[1]; \
    blk_2_H1 = lSrc[lStride+1]; \
    blk_2_H2 = lSrc[FACTOR_2(lStride)+1]; \
    \
    blk_3_H0 = lSrc[2]; \
    blk_3_H1 = lSrc[lStride+2]; \
    blk_3_H2 = lSrc[FACTOR_2(lStride)+2]; \
    \
    blk_4_H0 = lSrc[3]; \
    blk_4_H1 = lSrc[lStride+3]; \
    blk_4_H2 = lSrc[FACTOR_2(lStride)+3]; \
    \
    blk_1_H3 = lSrc[FACTOR_3(lStride)]; \
    blk_2_H3 = lSrc[FACTOR_3(lStride)+1]; \
    blk_3_H3 = lSrc[FACTOR_3(lStride)+2]; \
    blk_4_H3 = lSrc[FACTOR_3(lStride)+3]; \
    matrixTranspose(blk_1_H0, blk_1_H1, blk_1_H2, blk_1_H3, blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0); \
    blk_1_H0 = blk_h0v0; \
    blk_1_H1 = blk_h0v1; \
    blk_1_H2 = blk_h0v2; \
    blk_1_H3 = blk_h0v3; \
    matrixTranspose(blk_2_H0, blk_2_H1, blk_2_H2, blk_2_H3, blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0); \
    blk_2_H0 = blk_h0v0; \
    blk_2_H1 = blk_h0v1; \
    blk_2_H2 = blk_h0v2; \
    blk_2_H3 = blk_h0v3; \
    matrixTranspose(blk_3_H0, blk_3_H1, blk_3_H2, blk_3_H3, blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0); \
    blk_3_H0 = blk_h0v0; \
    blk_3_H1 = blk_h0v1; \
    blk_3_H2 = blk_h0v2; \
    blk_3_H3 = blk_h0v3; \
    matrixTranspose(blk_4_H0, blk_4_H1, blk_4_H2, blk_4_H3, blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0); \
    blk_4_H0 = blk_h0v0; \
    blk_4_H1 = blk_h0v1; \
    blk_4_H2 = blk_h0v2; \
    blk_4_H3 = blk_h0v3; \
    lSrc += FACTOR_3(lStride); \
    \
    do { \
        y++; \
        wmv3_QF4_new_2(lDst[0], blk_1_H0, blk_1_H1, blk_1_H2, blk_1_H3, shift, rounding, factor);\
        wmv3_QF4_new_2(lDst[1], blk_2_H0, blk_2_H1, blk_2_H2, blk_2_H3, shift, rounding, factor);\
        wmv3_QF4_new_2(lDst[2], blk_3_H0, blk_3_H1, blk_3_H2, blk_3_H3, shift, rounding, factor);\
        wmv3_QF4_new_2(lDst[3], blk_4_H0, blk_4_H1, blk_4_H2, blk_4_H3, shift, rounding, factor);\
        lDst += dStride; \
        lSrc += lStride; \
        blk_5_H0 = lSrc[0]; \
        blk_1_H0 = FUNSHIFT1(blk_1_H0, blk_5_H0<<24); \
        blk_1_H1 = FUNSHIFT1(blk_1_H1, blk_5_H0<<16); \
        blk_1_H2 = FUNSHIFT1(blk_1_H2, blk_5_H0<<8 ); \
        blk_1_H3 = FUNSHIFT1(blk_1_H3, blk_5_H0    ); \
        blk_6_H0 = lSrc[1]; \
        blk_2_H0 = FUNSHIFT1(blk_2_H0, blk_6_H0<<24); \
        blk_2_H1 = FUNSHIFT1(blk_2_H1, blk_6_H0<<16); \
        blk_2_H2 = FUNSHIFT1(blk_2_H2, blk_6_H0<<8 ); \
        blk_2_H3 = FUNSHIFT1(blk_2_H3, blk_6_H0    ); \
        blk_7_H0 = lSrc[2]; \
        blk_3_H0 = FUNSHIFT1(blk_3_H0, blk_7_H0<<24); \
        blk_3_H1 = FUNSHIFT1(blk_3_H1, blk_7_H0<<16); \
        blk_3_H2 = FUNSHIFT1(blk_3_H2, blk_7_H0<<8 ); \
        blk_3_H3 = FUNSHIFT1(blk_3_H3, blk_7_H0    ); \
        blk_8_H0 = lSrc[3]; \
        blk_4_H0 = FUNSHIFT1(blk_4_H0, blk_8_H0<<24); \
        blk_4_H1 = FUNSHIFT1(blk_4_H1, blk_8_H0<<16); \
        blk_4_H2 = FUNSHIFT1(blk_4_H2, blk_8_H0<<8 ); \
        blk_4_H3 = FUNSHIFT1(blk_4_H3, blk_8_H0    ); \
    } while (y<v); \
}

#define wmv3_CopyBlockQV_8_8_Template(src, dst, stride, dst_stride, rounding, shift, factor, v) \
{ \
    const uint32 * RESTRICT lSrc = (uint32 *) (src-stride); \
    uint32 * RESTRICT lDst = (uint32 *) dst; \
    int lStride = stride >> 2; \
    int dStride = dst_stride >> 2; \
    int32 tt1, tt2, tt3, tt4; \
    int y=0; \
    \
    uint32 blk_1_H0, blk_1_H1, blk_1_H2, blk_1_H3; \
    uint32 blk_2_H0, blk_2_H1, blk_2_H2, blk_2_H3; \
    uint32 blk_3_H0; \
    uint32 blk_4_H0; \
    \
    uint32 blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0; \
    uint32 blk_h1v3, blk_h1v2, blk_h1v1, blk_h1v0; \
    \
    blk_1_H0 = lSrc[0]; \
    blk_1_H1 = lSrc[lStride]; \
    blk_1_H2 = lSrc[FACTOR_2(lStride)]; \
    \
    blk_2_H0 = lSrc[1]; \
    blk_2_H1 = lSrc[lStride+1]; \
    blk_2_H2 = lSrc[FACTOR_2(lStride)+1]; \
    lSrc += FACTOR_3(lStride); \
    blk_1_H3 = lSrc[0]; \
    blk_2_H3 = lSrc[1]; \
    matrixTranspose(blk_1_H0, blk_1_H1, blk_1_H2, blk_1_H3, blk_h0v3, blk_h0v2, blk_h0v1, blk_h0v0); \
    matrixTranspose(blk_2_H0, blk_2_H1, blk_2_H2, blk_2_H3, blk_h1v3, blk_h1v2, blk_h1v1, blk_h1v0); \
    \
    do { \
        y++; \
        wmv3_QF4_new_2(lDst[0], blk_h0v0, blk_h0v1, blk_h0v2, blk_h0v3, shift, rounding, factor);\
        wmv3_QF4_new_2(lDst[1], blk_h1v0, blk_h1v1, blk_h1v2, blk_h1v3, shift, rounding, factor);\
        \
        lSrc += lStride; \
        lDst += (dStride); \
        blk_3_H0 = lSrc[0]; \
        blk_4_H0 = lSrc[1]; \
        blk_h0v0 = FUNSHIFT1(blk_h0v0, blk_3_H0<<24); \
        blk_h0v1 = FUNSHIFT1(blk_h0v1, blk_3_H0<<16); \
        blk_h0v2 = FUNSHIFT1(blk_h0v2, blk_3_H0<<8 ); \
        blk_h0v3 = FUNSHIFT1(blk_h0v3, blk_3_H0    ); \
        blk_h1v0 = FUNSHIFT1(blk_h1v0, blk_4_H0<<24); \
        blk_h1v1 = FUNSHIFT1(blk_h1v1, blk_4_H0<<16); \
        blk_h1v2 = FUNSHIFT1(blk_h1v2, blk_4_H0<<8 ); \
        blk_h1v3 = FUNSHIFT1(blk_h1v3, blk_4_H0    ); \
    } while (y<v); \
}

#define s0               0
#define d0               0
#define DST_STRIDE_ny(y) d##y
//#define DST_STRIDE_nx(x)    x

#define wmv3_CopyBlockQV_Template_by8(pSrc, pDst, stride, dstride, bx, by, rounding, shift, factor)\
{ \
    uint32 sleft;\
    int32  tmp0;\
    int x;\
    int s1, s2, s3, s4, s5, s6, s7, s8, s9;\
    int d1, d2, d3, d4, d5, d6, d7, d8, d9;\
    int rnd = rounding;\
    \
    s1 = stride;\
    s2 = s1 + s1;\
    s3 = s2 + s1;\
    s4 = s2 + s2;\
    s5 = s3+s2;\
    s6 = s3+s3;\
    s7 = s4+s3;\
    s8 = s4+s4;\
    s9 = s4+s5;\
    \
    d1 = dstride;\
    d2 = d1 + d1;\
    d3 = d2 + d1;\
    d4 = d2 + d2;\
    d5 = d3+d2;\
    d6 = d3+d3;\
    d7 = d4+d3;\
    d8 = d4+d4;\
    d9 = d4+d5;\
    \
    x = 0;\
    do {\
        x++;\
        sleft = make_uint32(pSrc[-s1], pSrc[0], pSrc[s1], pSrc[s2]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(0)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[0], pSrc[s1], pSrc[s2], pSrc[s3]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(1)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s1], pSrc[s2], pSrc[s3], pSrc[s4]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(2)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s2], pSrc[s3], pSrc[s4], pSrc[s5]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(3)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s3], pSrc[s4], pSrc[s5], pSrc[s6]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(4)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s4], pSrc[s5], pSrc[s6], pSrc[s7]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(5)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s5], pSrc[s6], pSrc[s7], pSrc[s8]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(6)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        sleft = make_uint32(pSrc[s6], pSrc[s7], pSrc[s8], pSrc[s9]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(7)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
        \
        pSrc += 1;\
        pDst += 1;\
    } while (x<bx); \
}

#define wmv3_CopyBlockQV_Template_by16(pSrc, pDst, stride, dstride, bx, by, rounding, shift, factor)\
{ \
    uint32 sleft;\
    int32  tmp0;\
    int x;\
    int s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17;\
    int d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17;\
    int rnd = rounding;\
    s1 = stride;\
    s2 = s1 + s1;\
    s3 = s2 + s1;\
    s4 = s2 + s2;\
    s5 = s3+s2;\
    s6 = s3+s3;\
    s7 = s4+s3;\
    s8 = s4+s4;\
    s9 = s4+s5;\
	s10 = s5+s5;\
	s11 = s5+s6;\
	s12 = s6+s6;\
	s13 = s6+s7;\
	s14 = s7+s7;\
	s15 = s7+s8;\
	s16 = s8+s8;\
	s17 = s8+s9;\
\
    d1 = dstride;\
    d2 = d1 + d1;\
    d3 = d2 + d1;\
    d4 = d2 + d2;\
    d5 = d3+d2;\
    d6 = d3+d3;\
    d7 = d4+d3;\
    d8 = d4+d4;\
    d9 = d4+d5;\
    d10 = d5+d5;\
    d11 = d5+d6;\
    d12 = d6+d6;\
    d13 = d6+d7;\
    d14 = d7+d7;\
    d15 = d7+d8;\
    d16 = d8+d8;\
    d17 = d8+d9;\
\
    x=0;\
    do {\
        x++;\
        sleft = make_uint32(pSrc[-s1], pSrc[0], pSrc[s1], pSrc[s2]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(0)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[0], pSrc[s1], pSrc[s2], pSrc[s3]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(1)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s1], pSrc[s2], pSrc[s3], pSrc[s4]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(2)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s2], pSrc[s3], pSrc[s4], pSrc[s5]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(3)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s3], pSrc[s4], pSrc[s5], pSrc[s6]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(4)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s4], pSrc[s5], pSrc[s6], pSrc[s7]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(5)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s5], pSrc[s6], pSrc[s7], pSrc[s8]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(6)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s6], pSrc[s7], pSrc[s8], pSrc[s9]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(7)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s7], pSrc[s8], pSrc[s9], pSrc[s10]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(8)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s8], pSrc[s9], pSrc[s10], pSrc[s11]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(9)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s9], pSrc[s10], pSrc[s11], pSrc[s12]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(10)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s10], pSrc[s11], pSrc[s12], pSrc[s13]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(11)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s11], pSrc[s12], pSrc[s13], pSrc[s14]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(12)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s12], pSrc[s13], pSrc[s14], pSrc[s15]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(13)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s13], pSrc[s14], pSrc[s15], pSrc[s16]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(14)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        sleft = make_uint32(pSrc[s14], pSrc[s15], pSrc[s16], pSrc[s17]);\
        tmp0 = IFIR8UI(sleft, factor);\
        pDst[DST_STRIDE_ny(15)] = UCLIPI((tmp0 + rnd) >> shift, 255);\
\
        pSrc += 1;\
        pDst += 1;\
    } while (x<bx); \
}

#ifdef _UAMEM_ACCESS_
#define RV8_HQV0_8xn(src, dst, src_stride, dst_stride, v, coef, shift, rounding) \
{ \
    uint32 * RESTRICT lDst; \
    const uint32 * RESTRICT lSrc; \
    int lStride = src_stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 d1, d2, d3; \
    uint32 reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7; \
    int32  tt1, tt2, tt3, tt4; \
    int y; \
    \
    lDst = (uint32 *) dst; \
    lSrc = (uint32 *) (src-1); \
    RV_PACK8_tm5250(lSrc); \
    y=0; \
    do { \
        y+=4; \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK8_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK8_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK8_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK8_tm5250(lSrc); \
    } while (y<v); \
}
#else

#define RV8_HQV0_8xn(src, dst, src_stride, dst_stride, v, coef, shift, rounding) \
{ \
    uint32 * RESTRICT lDst; \
    int dStride = dst_stride >> 2; \
    uint32 reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7; \
    int32  tt1, tt2, tt3, tt4; \
    int y; \
    \
    lDst = (uint32 *) dst; \
    \
    RV_PACK8_tm3260(src); \
    y=0; \
    do { \
        y+=4; \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK8_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK8_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK8_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK8_tm3260(src); \
    } while (y<v); \
}
#endif

#ifdef _UAMEM_ACCESS_
#define RV8_HQV0_16xn(src, dst, src_stride, dst_stride, v, coef, shift, rounding) \
{ \
    uint32 * RESTRICT lDst; \
    const uint32 * RESTRICT lSrc; \
    int lStride = src_stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 d1, d2, d3, d4, d5; \
    uint32 reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7; \
    uint32 reg8, reg9, reg10, reg11, reg12, reg13, reg14, reg15; \
    int32  tt1, tt2, tt3, tt4; \
    int y; \
    \
    lDst = (uint32 *) dst; \
    lSrc = (uint32 *) (src-1); \
    RV_PACK16_tm5250(lSrc); \
    y=0; \
    do { \
        y+=4; \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK16_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK16_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK16_tm5250(lSrc); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        lSrc += lStride; \
        lDst += dStride;  \
        RV_PACK16_tm5250(lSrc); \
    } while (y<v); \
}
#else
#define RV8_HQV0_16xn(src, dst, src_stride, dst_stride, v, coef, shift, rounding) \
{ \
    uint32 * RESTRICT lDst; \
    int dStride = dst_stride >> 2; \
    uint32 reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7; \
    uint32 reg8, reg9, reg10, reg11, reg12, reg13, reg14, reg15; \
    int32  tt1, tt2, tt3, tt4; \
    int y; \
    \
    lDst = (uint32 *) dst; \
    \
    RV_PACK16_tm3260(src); \
    y=0; \
    do { \
        y+=4; \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK16_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK16_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK16_tm3260(src); \
        wmv3_QF4_new_2(lDst[0], reg0, reg1, reg2, reg3, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[1], reg4, reg5, reg6, reg7, shift, rounding, coef);  \
        wmv3_QF4_new_2(lDst[2], reg8, reg9, reg10, reg11, shift, rounding, coef); \
        wmv3_QF4_new_2(lDst[3], reg12, reg13, reg14, reg15, shift, rounding, coef); \
        src += src_stride; \
        lDst += dStride;  \
        RV_PACK16_tm3260(src); \
    } while (y<v); \
}
#endif
    

/*******************************************************************************/
//Chroma 4xn
#define RV_H0V0_4(lsrc, ldst, X) \
    ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
    ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
    ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
    ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); 

#ifdef _UAMEM_ACCESS_
#define RV_H0V0_4xn(pSrc, pDst, src_stride, dst_stride) \
    const uint32 *RESTRICT lsrc = (uint32 *) pSrc; \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    int s1, s2, s3, d1, d2, d3; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    \
    ldst[0] = lsrc[0]; \
    ldst[d1] = lsrc[s1]; \
    ldst[d2] = lsrc[s2]; \
    ldst[d3] = lsrc[s3];
#else
#define RV_H0V0_4xn(pSrc, pDst, src_stride, dst_stride) \
    int t = (int)pSrc&0x3; \
    const uint32 *RESTRICT lsrc = (uint32 *) ((int)pSrc&0xfffffffc); \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    int s1, s2, s3, d1, d2, d3; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    if (t == 0) {  \
        RV_H0V0_4(lsrc, ldst, 4); \
    } else if (t == 1) { \
        RV_H0V0_4(lsrc, ldst, 3); \
    } else if (t == 2) { \
        RV_H0V0_4(lsrc, ldst, 2); \
    } else { \
        RV_H0V0_4(lsrc, ldst, 1); \
    }
#endif

#ifdef _TM5250_
#define Copy4H1_tmp(src, dst, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t4, t5, t8, t9; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR1(t4,t0); \
        t9 = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        lSrc += lStride;         \
        lDst += dStride; \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR1(t4,t0); \
        t9 = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        lSrc += lStride;         \
        lDst += dStride; \
    } while (dy < 4);  \
}
#else
#define Copy4H1_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy; \
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);     \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    int t = (int) src & 0x3 ;\
    for (dy = 0; dy < 4; dy++) {                   \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);  \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        lDst[0] = MERGEODD(t9,t8);\
        lSrc += lStride; \
        lDst += dStride; \
    } \
}
#endif

#ifdef _TM5250_
#define Copy4H3_tmp(src, dst, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t4, t5, t8, t9; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        t2 = FUNSHIFT2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t1,t1); \
        t5  = MERGEODD(t2,t2); \
        t8  = BILINEAR1(t4,t0); \
        t9  = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8); \
        lSrc += lStride; \
        lDst += dStride; \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        t2 = FUNSHIFT2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t1,t1); \
        t5  = MERGEODD(t2,t2); \
        t8  = BILINEAR1(t4,t0); \
        t9  = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8); \
        lSrc += lStride; \
        lDst += dStride; \
    } while (dy < 4); \
}
#else
#define Copy4H3_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy; \
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);     \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    int t = (int) src & 0x3; \
    for (dy = 0; dy < 4; dy++) { \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t1,t1);             /*3 3 1 1*/           \
        t5  = MERGEODD((t1>>8),(t1>>8));   /*4 4 2 2*/           \
        t8  = BILINEAR1(t4,t0); \
        t9  = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8); \
        lSrc += lStride; \
        lDst += dStride; \
    } \
}
#endif

#ifdef _TM5250_
#define Copy4V1_tmp(src, dst, Stride, dst_stride) \
{\
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t4, t5, t6, t7, t12, t13; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
        dy++; \
        lSrc += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
    } while (dy < 4); \
}
#else
#define Copy4V1_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t4, t5, t6, t7, t12, t13; \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc); \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    int t = (int) src & 0x3; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    for (dy = 0; dy < 4; dy++) { \
        lSrc += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2; \
        lDst += dStride; \
    } \
}
#endif

#ifdef _TM5250_
#define Copy4V3_tmp(src, dst, Stride, dst_stride) \
{\
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t4, t5, t6, t7, t12, t13; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t2,t0);             /*v1  1 v0  0            */  \
        t5  = MERGELSB(t2,t2);             /*v1 v1 v0 v0            */  \
        t6  = MERGEMSB(t2,t0);             /*v3  3 v2  2            */  \
        t7  = MERGEMSB(t2,t2);             /*v3 v3 v2 v2            */  \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
        dy++; \
        lSrc += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t2,t0);             /*v1  1 v0  0            */  \
        t5  = MERGELSB(t2,t2);             /*v1 v1 v0 v0            */  \
        t6  = MERGEMSB(t2,t0);             /*v3  3 v2  2            */  \
        t7  = MERGEMSB(t2,t2);             /*v3 v3 v2 v2            */  \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
    } while (dy < 4);\
}
#else
#define Copy4V3_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15; \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc); \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    int t = (int) src & 0x3; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    for (dy = 0; dy < 4; dy++) { \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t2,t0);             /*v1  1 v0  0            */  \
        t5  = MERGELSB(t2,t2);             /*v1 v1 v0 v0            */  \
        t6  = MERGEMSB(t2,t0);             /*v3  3 v2  2            */  \
        t7  = MERGEMSB(t2,t2);             /*v3 v3 v2 v2            */  \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2; \
        t1 = t3; \
        lDst += dStride; \
    } \
}
#endif

#ifdef _TM5250_
#define Copy4H2_tmp(src, dst, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG(t0,t1); \
        lSrc += lStride; \
        lDst += dStride; \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG(t0,t1); \
        lSrc += lStride; \
        lDst += dStride; \
    } while (dy < 4);\
}
#else
#define Copy4H2_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy; \
    int t; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t1; \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc); \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    t = (int) src & 0x3; \
    for (dy = 0; dy < 4; dy++) { \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
    lDst[0] = QUADAVG(t0,t1); \
    lSrc  = lSrc + lStride; \
    lDst += dStride; \
    } \
}
#endif

#ifdef _TM5250_
#define Copy4V2_tmp(src, dst, Stride, dst_stride) \
{ \
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]);  \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG0(t0,t2); \
        t0 = t2; \
        lDst += dStride; \
        dy++; \
        lSrc += lStride;\
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG0(t0,t2); \
        t0 = t2; \
        lDst += dStride; \
    } while (dy < 4); \
}
#else
#define Copy4V2_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    int t = (int) src & 0x3; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]); \
    for (dy = 0; dy < 4; dy++) { \
    lSrc += lStride; \
    t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]); \
    lDst[0] = QUADAVG0(t0,t2); \
    t0=t2; \
    t1=t3; \
    lDst += dStride; \
    } \
}
#endif

#define avc_CopyBlkEFunc_4_1(tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    m[1] = PACKBYTES(tmp[1], tmp[0]); \
    m[3] = PACKBYTES(tmp[2], tmp[1]); \
    m[5] = PACKBYTES(tmp[3], tmp[2]); \
    m[7] = PACKBYTES(tmp[4], tmp[3]); \
    tmp += stride; \
    t1 = IFIR8UI(PACK16LSB(m[0], m[1]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[2], m[3]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[4], m[5]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[6], m[7]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride; \
    m[0] = PACKBYTES(tmp[1], tmp[0]); \
    m[2] = PACKBYTES(tmp[2], tmp[1]); \
    m[4] = PACKBYTES(tmp[3], tmp[2]); \
    m[6] = PACKBYTES(tmp[4], tmp[3]); \
    tmp += stride; \
    t1 = IFIR8UI(PACK16LSB(m[1], m[0]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[3], m[2]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[5], m[4]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[7], m[6]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride;

#define avc_CopyBlkEFunc_4_UAMEM(lsrc, tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    lsrc[1] = (uint32 * RESTRICT)(tmp+stride); \
    lsrc[3] = (uint32 * RESTRICT)(tmp+stride+1); \
    m[0] = PACK16LSB(lsrc[0][0], lsrc[1][0]); \
    m[1] = PACK16LSB(lsrc[2][0], lsrc[3][0]); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    m[2] = PACK16MSB(lsrc[0][0], lsrc[1][0]); \
    m[3] = PACK16MSB(lsrc[2][0], lsrc[3][0]); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    dst += dst_stride; \
    tmp += stride_mul2; \
    lsrc[0] = (uint32 * RESTRICT)(tmp); \
    lsrc[2] = (uint32 * RESTRICT)(tmp+1); \
    m[4] = PACK16LSB(lsrc[1][0], lsrc[0][0]); \
    m[5] = PACK16LSB(lsrc[3][0], lsrc[2][0]); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    m[6] = PACK16MSB(lsrc[1][0], lsrc[0][0]); \
    m[7] = PACK16MSB(lsrc[3][0], lsrc[2][0]); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    dst += dst_stride;

#ifdef _UAMEM_ACCESS_
#define RV_HQVQ_4xn(pSrc, pDst, src_stride, dst_stride, coef, rounding, shift) \
{ \
    uint32 s[8]; \
    int t1, t2, t3, t4; \
    const uint32 *RESTRICT lsrc[4]; \
    int stride_mul2 = src_stride<<1; \
    \
    lsrc[0] = (uint32 * RESTRICT)pSrc; \
    lsrc[2] = (uint32 * RESTRICT)(pSrc+1); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
}
#else
#define RV_HQVQ_4xn(pSrc, pDst, src_stride, dst_stride, coef, rounding, shift) \
{ \
    uint32 s[8]; \
    int t1, t2, t3, t4; \
    uchar * RESTRICT tmp; \
    \
    s[0] = PACKBYTES(pSrc[1], pSrc[0]); \
    s[2] = PACKBYTES(pSrc[2], pSrc[1]); \
    s[4] = PACKBYTES(pSrc[3], pSrc[2]); \
    s[6] = PACKBYTES(pSrc[4], pSrc[3]); \
    tmp = pSrc+src_stride; \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
}
#endif


/*******************************************************************************/
//erin
//Chroma 8xn
#define RV_H0V0_8(lsrc, ldst, X) \
    ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
    ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
    ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
    ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); 

#ifdef _UAMEM_ACCESS_
#define RV_H0V0_8xn(pSrc, pDst, src_stride, dst_stride) \
    const uint32 *RESTRICT lsrc = (uint32 *) pSrc; \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    int s1, s2, s3, d1, d2, d3; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    \
    ldst[0] = lsrc[0]; \
    ldst[d1] = lsrc[s1]; \
    ldst[d2] = lsrc[s2]; \
    ldst[d3] = lsrc[s3]; \
    ldst[1] = lsrc[1]; \
    ldst[d1+1] = lsrc[s1+1]; \
    ldst[d2+1] = lsrc[s2+1]; \
    ldst[d3+1] = lsrc[s3+1]; \
    lsrc += src_stride; \
    ldst += dst_stride; \
    ldst[0] = lsrc[0]; \
    ldst[d1] = lsrc[s1]; \
    ldst[d2] = lsrc[s2]; \
    ldst[d3] = lsrc[s3]; \
    ldst[1] = lsrc[1]; \
    ldst[d1+1] = lsrc[s1+1]; \
    ldst[d2+1] = lsrc[s2+1]; \
    ldst[d3+1] = lsrc[s3+1];
#else
#define RV_H0V0_8xn(pSrc, pDst, src_stride, dst_stride) \
    int t = (int)pSrc&0x3; \
    const uint32 *RESTRICT lsrc = (uint32 *) ((int)pSrc&0xfffffffc); \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    int s1, s2, s3, d1, d2, d3; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    if (t == 0) {  \
        RV_H0V0_8(lsrc, ldst, 4); \
    } else if (t == 1) { \
        RV_H0V0_8(lsrc, ldst, 3); \
    } else if (t == 2) { \
        RV_H0V0_8(lsrc, ldst, 2); \
    } else { \
        RV_H0V0_8(lsrc, ldst, 1); \
    }
#endif

#ifdef _UAMEM_ACCESS_
#define RV8_HQVQ_8xn(pSrc, pDst, src_stride, dst_stride, coef, rounding, shift) \
    uint32 s[8]; \
    int t1, t2, t3, t4; \
    const uint32 *RESTRICT lsrc[4]; \
    int stride_mul2 = src_stride<<1; \
    int i = 8; \
    \
    lsrc[0] = (uint32 * RESTRICT)pSrc; \
    lsrc[2] = (uint32 * RESTRICT)(pSrc+1); \
    do { \
        avc_CopyBlkEFunc_8_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        avc_CopyBlkEFunc_8_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        i -= 4; \
    } while (i>0);

#else
#define RV8_HQVQ_8xn(pSrc, pDst, src_stride, dst_stride, coef, rounding, shift) \
    uint32 s[8]; \
    int t1, t2, t3, t4; \
    uchar * RESTRICT tmp; \
    \
    s[0] = PACKBYTES(pSrc[1], pSrc[0]); \
    s[2] = PACKBYTES(pSrc[2], pSrc[1]); \
    s[4] = PACKBYTES(pSrc[3], pSrc[2]); \
    s[6] = PACKBYTES(pSrc[4], pSrc[3]); \
    tmp = pSrc+src_stride; \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift);
#endif

/*******************************************************************************/

//Chroma 4xn UV-merged
#define FILTER_C_H0V0_4xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, X) \
{ \
    const uint32 *RESTRICT lsrc = (uint32 *) pSrc; \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    const uint32 *RESTRICT lsrc2 = (uint32 *) pSrc2; \
    uint32 *RESTRICT ldst2 = (uint32 *) pDst2; \
    int s1, s2, s3, d1, d2, d3; \
    int y = 0; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    \
    ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
    ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
    ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
    ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
    ldst2[0] = FUNSHIFT##X(lsrc2[1], lsrc2[0]); \
    ldst2[d1] = FUNSHIFT##X(lsrc2[s1+1], lsrc2[s1]); \
    ldst2[d2] = FUNSHIFT##X(lsrc2[s2+1], lsrc2[s2]); \
    ldst2[d3] = FUNSHIFT##X(lsrc2[s3+1], lsrc2[s3]); \
}


#define FILTER_C_H1V0_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, BILINEAR_X) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t4, t5, t8, t9; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    dy = 0; \
    do { \
        dy+=2; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        lDst2[0] = MERGEODD(t9,t8);\
        lSrc2 += lStride; \
        lDst2 += dStride; \
        \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        lDst2[0] = MERGEODD(t9,t8);\
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < 4);  \
}

#define FILTER_C_H3V0_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, A3, BILINEAR_X) \
{\
    int dy;\
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t4, t5, t8, t9; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t2 = FUNSHIFT##A3(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t1,t1); \
        t5  = MERGEODD(t2,t2); \
        t8  = BILINEAR_X(t4,t0); \
        t9  = BILINEAR_X(t5,t1); \
        lDst[0] = MERGEODD(t9,t8); \
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t2 = FUNSHIFT##A3(lSrc2[1], lSrc2[0]); \
        t4  = MERGEODD(t1,t1); \
        t5  = MERGEODD(t2,t2); \
        t8  = BILINEAR_X(t4,t0); \
        t9  = BILINEAR_X(t5,t1); \
        lDst2[0] = MERGEODD(t9,t8); \
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < 4); \
}

#define FILTER_C_H3V0_4xn_new(src, dst, src2, dst2, Stride, dst_stride, A1, A2, BILINEAR_X) \
{\
    int dy; \
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);     \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) ((int)src2&0xfffffffc);     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    int t = (int) src & 0x3; \
    for (dy = 0; dy < 4; dy++) { \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t1,t1);             /*3 3 1 1*/           \
        t5  = MERGEODD((t1>>8),(t1>>8));   /*4 4 2 2*/           \
        t8  = BILINEAR_X(t4,t0); \
        t9  = BILINEAR_X(t5,t1); \
        lDst[0] = MERGEODD(t9,t8); \
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t4  = MERGEODD(t1,t1);             /*3 3 1 1*/           \
        t5  = MERGEODD((t1>>8),(t1>>8));   /*4 4 2 2*/           \
        t8  = BILINEAR_X(t4,t0); \
        t9  = BILINEAR_X(t5,t1); \
        lDst2[0] = MERGEODD(t9,t8); \
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } \
}

#define FILTER_C_H0V1_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, BILINEAR_X) \
{\
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t4, t5, t6, t7, t12, t13; \
    uint32 x0, x2, x4, x5, x6, x7, x12, x13; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);  \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride; \
        lSrc2 += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t0,t0);              \
        t5  = MERGELSB(t2,t0);             \
        t6  = MERGEMSB(t0,t0);             \
        t7  = MERGEMSB(t2,t0);             \
        t12 = BILINEAR_X(t5,t4);\
        t13 = BILINEAR_X(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);  \
        x4  = MERGELSB(x0,x0);                  \
        x5  = MERGELSB(x2,x0);                 \
        x6  = MERGEMSB(x0,x0);                 \
        x7  = MERGEMSB(x2,x0);                 \
        x12 = BILINEAR_X(x5,x4);\
        x13 = BILINEAR_X(x7,x6);\
        lDst2[0] = MERGEDUAL16LSB(x13,x12);\
        x0 = x2;\
        lDst2 += dStride; \
        \
    } while (dy < 4); \
}

#define FILTER_C_H0V3_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, BILINEAR_X) \
{\
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t4, t5, t6, t7, t12, t13; \
    uint32 x0, x2, x4, x5, x6, x7, x12, x13; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);  \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
        t4  = MERGELSB(t2,t0);              \
        t5  = MERGELSB(t2,t2);              \
        t6  = MERGEMSB(t2,t0);              \
        t7  = MERGEMSB(t2,t2);              \
        t12 = BILINEAR_X(t5,t4);\
        t13 = BILINEAR_X(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        lDst += dStride; \
        lSrc2 += lStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);  \
        x4  = MERGELSB(x2,x0);             \
        x5  = MERGELSB(x2,x2);             \
        x6  = MERGEMSB(x2,x0);             \
        x7  = MERGEMSB(x2,x2);             \
        x12 = BILINEAR_X(x5,x4);\
        x13 = BILINEAR_X(x7,x6);\
        lDst2[0] = MERGEDUAL16LSB(x13,x12);\
        x0 = x2;\
        lDst2 += dStride; \
    } while (dy < 4); \
}

#define FILTER_C_H2V0_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, QUADAVG_X) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG_X(t0,t1); \
        lSrc += lStride; \
        lDst += dStride; \
        t2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t3 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        lDst2[0] = QUADAVG_X(t2,t3); \
        lSrc2 += lStride; \
        lDst2 += dStride; \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG_X(t0,t1); \
        lSrc += lStride; \
        lDst += dStride; \
        t2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t3 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        lDst2[0] = QUADAVG_X(t2,t3); \
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < 4); \
}

#define FILTER_C_H0V2_4xn(src, dst, src2, dst2, Stride, dst_stride, A1, QUADAVG_X) \
{ \
    int dy; \
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t2, t1, t3; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);  \
    t1 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);  \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        lDst[0] = QUADAVG_X(t0,t2); \
        t0 = t2; \
        lDst += dStride; \
        lSrc2 += lStride;\
        t3 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        lDst2[0] = QUADAVG_X(t1,t3); \
        t1 = t3; \
        lDst2 += dStride; \
    } while (dy < 4); \
}

#ifdef _UAMEM_ACCESS_
#define FILTER_C_HQVQ_4xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, coef, rounding, shift) \
{ \
    uint32 s[8], r[8]; \
    int t1, t2, t3, t4; \
    const uint32 *RESTRICT lsrc[4]; \
    const uint32 *RESTRICT lsrc2[4]; \
    int stride_mul2 = src_stride<<1; \
    \
    lsrc[0] = (uint32 * RESTRICT)pSrc; \
    lsrc[2] = (uint32 * RESTRICT)(pSrc+1); \
    lsrc2[0] = (uint32 * RESTRICT)pSrc2; \
    lsrc2[2] = (uint32 * RESTRICT)(pSrc2+1); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc2, pSrc2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
    avc_CopyBlkEFunc_4_UAMEM(lsrc2, pSrc2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
}
#else
#define FILTER_C_HQVQ_4xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, coef, rounding, shift) \
{ \
    uint32 s[8], r[8]; \
    int t1, t2, t3, t4; \
    const uchar * RESTRICT tmp; \
    const uchar * RESTRICT tmp2; \
    \
    s[0] = PACKBYTES(pSrc[1], pSrc[0]); \
    s[2] = PACKBYTES(pSrc[2], pSrc[1]); \
    s[4] = PACKBYTES(pSrc[3], pSrc[2]); \
    s[6] = PACKBYTES(pSrc[4], pSrc[3]); \
    r[0] = PACKBYTES(pSrc2[1], pSrc2[0]); \
    r[2] = PACKBYTES(pSrc2[2], pSrc2[1]); \
    r[4] = PACKBYTES(pSrc2[3], pSrc2[2]); \
    r[6] = PACKBYTES(pSrc2[4], pSrc2[3]); \
    tmp = pSrc+src_stride; \
    tmp2 = pSrc2+src_stride; \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    avc_CopyBlkEFunc_4_1(tmp2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
    avc_CopyBlkEFunc_4_1(tmp2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
}
#endif

/*********************************************************************************************************/

//Chroma 8xn UV-merged
//erin
/*
#define FILTER_C_H0V0_8xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, X) \
{ \
    uint32 *RESTRICT lsrc = (uint32 *) pSrc; \
    uint32 *RESTRICT ldst = (uint32 *) pDst; \
    uint32 *RESTRICT lsrc2 = (uint32 *) pSrc2; \
    uint32 *RESTRICT ldst2 = (uint32 *) pDst2; \
    int s1, s2, s3, d1, d2, d3; \
    int y = 0; \
    \
    s1 = src_stride>>2; \
    s2 = src_stride>>1; \
    s3 = s1 + s2; \
    d1 = dst_stride>>2; \
    d2 = dst_stride>>1; \
    d3 = d1 + d2; \
    do { \
        ldst[0] = FUNSHIFT##X(lsrc[1], lsrc[0]); \
        ldst[d1] = FUNSHIFT##X(lsrc[s1+1], lsrc[s1]); \
        ldst[d2] = FUNSHIFT##X(lsrc[s2+1], lsrc[s2]); \
        ldst[d3] = FUNSHIFT##X(lsrc[s3+1], lsrc[s3]); \
        ldst2[0] = FUNSHIFT##X(lsrc2[1], lsrc2[0]); \
        ldst2[d1] = FUNSHIFT##X(lsrc2[s1+1], lsrc2[s1]); \
        ldst2[d2] = FUNSHIFT##X(lsrc2[s2+1], lsrc2[s2]); \
        ldst2[d3] = FUNSHIFT##X(lsrc2[s3+1], lsrc2[s3]); \
        ldst[1] = FUNSHIFT##X(lsrc[2], lsrc[1]); \
        ldst[d1+1] = FUNSHIFT##X(lsrc[s1+2], lsrc[s1+1]); \
        ldst[d2+1] = FUNSHIFT##X(lsrc[s2+2], lsrc[s2+1]); \
        ldst[d3+1] = FUNSHIFT##X(lsrc[s3+2], lsrc[s3+1]); \
        ldst2[1] = FUNSHIFT##X(lsrc2[2], lsrc2[1]); \
        ldst2[d1+1] = FUNSHIFT##X(lsrc2[s1+2], lsrc2[s1+1]); \
        ldst2[d2+1] = FUNSHIFT##X(lsrc2[s2+2], lsrc2[s2+1]); \
        ldst2[d3+1] = FUNSHIFT##X(lsrc2[s3+2], lsrc2[s3+1]); \
        lsrc += src_stride; \
        lsrc2 += src_stride; \
        ldst += dst_stride; \
        ldst2 += dst_stride; \
        y+=4; \
    } while (y < 8); \
}
*/
#if 0
#define FILTER_C_H0V0_8xn_ual(src, dst, src2, dst2, src_stride, dst_stride, X, v) \
{ \
    int dy, j;\
    int lStride = src_stride >> 2;\
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src+lStride;            \
    uint32 *RESTRICT lDst2 = (uint32 *) dst+lStride;            \
    int num = (v>>1)-1; \
    j = 0; \
    do { \
        dy = 0; \
        lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
        lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
        lDst2[0] = FUNSHIFT##X(lSrc2[1], lSrc2[0]);                      \
        lDst2[1] = FUNSHIFT##X(lSrc2[2], lSrc2[1]);                      \
        lSrc += FACTOR_2(lStride);                             \
        lDst += FACTOR_2(lStride); \
        lSrc2 += FACTOR_2(lStride);                             \
        lDst2 += FACTOR_2(lStride); \
        do { \
            dy++; \
            lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
            lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
            lDst2[0] = FUNSHIFT##X(lSrc2[1], lSrc2[0]);                      \
            lDst2[1] = FUNSHIFT##X(lSrc2[2], lSrc2[1]);                      \
            lSrc += FACTOR_2(lStride);                             \
            lDst += FACTOR_2(lStride); \
            lSrc2 += FACTOR_2(lStride);                             \
            lDst2 += FACTOR_2(lStride); \
        } while (dy != num); \
        j++; \
        lSrc = (uint32 *) src2;                     \
        lDst = (uint32 *) dst2;                     \
        lSrc2 = (uint32 *) src2+lStride;                     \
        lDst2 = (uint32 *) dst2+lStride;                     \
    } while(j<2); \
}
#else
#define FILTER_C_H0V0_8xn_ual(src, dst, src2, dst2, src_stride, dst_stride, X, v) \
{ \
    int dy;\
    int lStride = src_stride >> 2;\
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src+lStride;            \
    uint32 *RESTRICT lDst2 = (uint32 *) dst+lStride;            \
    \
    uint32 *RESTRICT lSrc_v = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst_v = (uint32 *) dst2;                     \
    uint32 *RESTRICT lSrc2_v = (uint32 *) src2+lStride;                     \
    uint32 *RESTRICT lDst2_v = (uint32 *) dst2+lStride;                     \
    int num = (v>>1)-1; \
    dy = 0; \
    lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
    lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
    lDst2[0] = FUNSHIFT##X(lSrc2[1], lSrc2[0]);                      \
    lDst2[1] = FUNSHIFT##X(lSrc2[2], lSrc2[1]);                      \
    lDst_v[0] = FUNSHIFT##X(lSrc_v[1], lSrc_v[0]);                      \
    lDst_v[1] = FUNSHIFT##X(lSrc_v[2], lSrc_v[1]);                      \
    lDst2_v[0] = FUNSHIFT##X(lSrc2_v[1], lSrc2_v[0]);                      \
    lDst2_v[1] = FUNSHIFT##X(lSrc2_v[2], lSrc2_v[1]);                      \
    lSrc += FACTOR_2(lStride);                             \
    lDst += FACTOR_2(lStride); \
    lSrc2 += FACTOR_2(lStride);                             \
    lDst2 += FACTOR_2(lStride); \
    lSrc_v += FACTOR_2(lStride);                             \
    lDst_v += FACTOR_2(lStride); \
    lSrc2_v += FACTOR_2(lStride);                             \
    lDst2_v += FACTOR_2(lStride); \
    do { \
        dy++; \
        lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
        lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
        lDst2[0] = FUNSHIFT##X(lSrc2[1], lSrc2[0]);                      \
        lDst2[1] = FUNSHIFT##X(lSrc2[2], lSrc2[1]);                      \
        lDst_v[0] = FUNSHIFT##X(lSrc_v[1], lSrc_v[0]);                      \
        lDst_v[1] = FUNSHIFT##X(lSrc_v[2], lSrc_v[1]);                      \
        lDst2_v[0] = FUNSHIFT##X(lSrc2_v[1], lSrc2_v[0]);                      \
        lDst2_v[1] = FUNSHIFT##X(lSrc2_v[2], lSrc2_v[1]);                      \
        lSrc += FACTOR_2(lStride);                             \
        lDst += FACTOR_2(lStride); \
        lSrc2 += FACTOR_2(lStride);                             \
        lDst2 += FACTOR_2(lStride); \
        lSrc_v += FACTOR_2(lStride);                             \
        lDst_v += FACTOR_2(lStride); \
        lSrc2_v += FACTOR_2(lStride);                             \
        lDst2_v += FACTOR_2(lStride); \
    } while (dy != num);\
}
#endif
#ifdef _UAMEM_ACCESS_
#define FILTER_C_H0V0_8xn(Src, Dst, Src2, Dst2, src_stride, dst_stride, X, v) \
    FILTER_C_H0V0_8xn_ual(Src, Dst, Src2, Dst2, src_stride, dst_stride, 4, v)
#else
#define FILTER_C_H0V0_8xn(Src, Dst, Src2, Dst2, src_stride, dst_stride, X, v) \
{ \
    int t = (int)Src&0x3; \
    if (t == 0) { \
        FILTER_C_H0V0_8xn_ual(Src, Dst, Src2, Dst2, src_stride, dst_stride, 4, 8); \
    } else if (t == 1) { \
        FILTER_C_H0V0_8xn_ual(((int)Src&0xfffffffc), Dst, ((int)Src2&0xfffffffc), Dst2, src_stride, dst_stride, 3, 8); \
    } else if (t == 2) { \
        FILTER_C_H0V0_8xn_ual(((int)Src&0xfffffffc), Dst, ((int)Src2&0xfffffffc), Dst2, src_stride, dst_stride, 2, 8); \
    } else if (t == 3) { \
        FILTER_C_H0V0_8xn_ual(((int)Src&0xfffffffc), Dst, ((int)Src2&0xfffffffc), Dst2, src_stride, dst_stride, 1, 8); \
    } \
}
#endif

#define FILTER_C_H1V0_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, BILINEAR_X, v) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        t4  = MERGEODD(t0,t0);             \
        t5  = MERGEODD(t1,t1);             \
        t6  = MERGEODD(t2,t2);             \
        t7  = MERGEODD(t3,t3);             \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        t10 = BILINEAR_X(t6,t2); \
        t11 = BILINEAR_X(t7,t3); \
        lDst[0] = MERGEODD(t9,t8);\
        lDst[1] = MERGEODD(t11,t10);\
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
        t4  = MERGEODD(t0,t0);            \
        t5  = MERGEODD(t1,t1);            \
        t6  = MERGEODD(t2,t2);            \
        t7  = MERGEODD(t3,t3);            \
        t8 = BILINEAR_X(t4,t0); \
        t9 = BILINEAR_X(t5,t1); \
        t10 = BILINEAR_X(t6,t2); \
        t11 = BILINEAR_X(t7,t3); \
        lDst2[0] = MERGEODD(t9,t8);\
        lDst2[1] = MERGEODD(t11,t10);\
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < v);  \
}

#define FILTER_C_H3V0_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, BILINEAR_X, v) \
{\
    int dy;\
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        t4  = MERGEODD(t1,t1);                      \
        t5  = MERGEODD((t1>>8),(t1>>8));            \
        t6  = MERGEODD(t3,t3);                      \
        t7  = MERGEODD((t3>>8),(t3>>8));            \
        t8  = BILINEAR_X(t4,t0);\
        t9  = BILINEAR_X(t5,t1);\
        t10 = BILINEAR_X(t6,t2);\
        t11 = BILINEAR_X(t7,t3);\
        lDst[0] = MERGEODD(t9,t8); \
        lDst[1] = MERGEODD(t11,t10);\
        lSrc += lStride; \
        lDst += dStride; \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
        t4  = MERGEODD(t1,t1);                     \
        t5  = MERGEODD((t1>>8),(t1>>8));           \
        t6  = MERGEODD(t3,t3);                     \
        t7  = MERGEODD((t3>>8),(t3>>8));           \
        t8  = BILINEAR_X(t4,t0);\
        t9  = BILINEAR_X(t5,t1);\
        t10 = BILINEAR_X(t6,t2);\
        t11 = BILINEAR_X(t7,t3);\
        lDst2[0] = MERGEODD(t9,t8); \
        lDst2[1] = MERGEODD(t11,t10);\
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < v); \
}

#define FILTER_C_H0V1_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, BILINEAR_X, v) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    x1 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t4  = MERGELSB(t0,t0);                      \
        t5  = MERGELSB(t2,t0);                      \
        t6  = MERGEMSB(t0,t0);                      \
        t7  = MERGEMSB(t2,t0);                      \
        t8  = MERGELSB(t1,t1);                      \
        t9  = MERGELSB(t3,t1);                      \
        t10 = MERGEMSB(t1,t1);                      \
        t11 = MERGEMSB(t3,t1);                      \
        t12 = BILINEAR_X(t5,t4);                     \
        t13 = BILINEAR_X(t7,t6);                     \
        t14 = BILINEAR_X(t9,t8);                     \
        t15 = BILINEAR_X(t11,t10);                   \
        lDst[0] = MERGEDUAL16LSB(t13,t12);          \
        lDst[1] = MERGEDUAL16LSB(t15,t14);          \
        t0 = t2;                                    \
        t1 = t3;                                    \
        lDst += dStride; \
        \
        lSrc2  += lStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);            \
        x3 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);            \
        x4  = MERGELSB(x0,x0);                  \
        x5  = MERGELSB(x2,x0);                  \
        x6  = MERGEMSB(x0,x0);                  \
        x7  = MERGEMSB(x2,x0);                  \
        x8  = MERGELSB(x1,x1);                  \
        x9  = MERGELSB(x3,x1);                  \
        x10 = MERGEMSB(x1,x1);                  \
        x11 = MERGEMSB(x3,x1);                  \
        x12 = BILINEAR_X(x5,x4);                 \
        x13 = BILINEAR_X(x7,x6);                 \
        x14 = BILINEAR_X(x9,x8);                 \
        x15 = BILINEAR_X(x11,x10);               \
        lDst2[0] = MERGEDUAL16LSB(x13,x12);          \
        lDst2[1] = MERGEDUAL16LSB(x15,x14);          \
        x0 = x2;\
        x1 = x3;\
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H0V3_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, BILINEAR_X, v) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    x1 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t4  = MERGELSB(t2,t0);              \
        t5  = MERGELSB(t2,t2);              \
        t6  = MERGEMSB(t2,t0);              \
        t7  = MERGEMSB(t2,t2);              \
        t8  = MERGELSB(t3,t1);              \
        t9  = MERGELSB(t3,t3);              \
        t10 = MERGEMSB(t3,t1);              \
        t11 = MERGEMSB(t3,t3);              \
        t12 = BILINEAR_X(t5,t4);\
        t13 = BILINEAR_X(t7,t6);\
        t14 = BILINEAR_X(t9,t8);\
        t15 = BILINEAR_X(t11,t10);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        lDst[1] = MERGEDUAL16LSB(t15,t14);\
        t0 = t2;\
        t1 = t3;\
        lDst += dStride; \
        \
        lSrc2  += lStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        x3 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        x4  = MERGELSB(x2,x0);           \
        x5  = MERGELSB(x2,x2);           \
        x6  = MERGEMSB(x2,x0);           \
        x7  = MERGEMSB(x2,x2);           \
        x8  = MERGELSB(x3,x1);           \
        x9  = MERGELSB(x3,x3);           \
        x10 = MERGEMSB(x3,x1);           \
        x11 = MERGEMSB(x3,x3);           \
        x12 = BILINEAR_X(x5,x4);\
        x13 = BILINEAR_X(x7,x6);\
        x14 = BILINEAR_X(x9,x8);\
        x15 = BILINEAR_X(x11,x10);\
        lDst2[0] = MERGEDUAL16LSB(x13,x12);\
        lDst2[1] = MERGEDUAL16LSB(x15,x14);\
        x0 = x2;\
        x1 = x3;\
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H2V0_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, A2, QUADAVG_X, v) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3;        \
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2;                   \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                   \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        lDst[0] = QUADAVG_X(t0,t1); \
        lDst[1] = QUADAVG_X(t2,t3); \
        lSrc += lStride;                             \
        lDst += dStride; \
        \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
        lDst2[0] = QUADAVG_X(t0,t1); \
        lDst2[1] = QUADAVG_X(t2,t3); \
        lSrc2 += lStride;                             \
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H0V2_8xn(src, dst, src2, dst2, Stride, dst_stride, A1, QUADAVG_X, v) \
{ \
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7;\
    uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    t4 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    t5 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        lDst[0] = QUADAVG_X(t0,t2); \
        lDst[1] = QUADAVG_X(t1,t3); \
        t0=t2;\
        t1=t3;\
        lDst += dStride; \
        \
        lSrc2 += lStride;\
        t6 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t7 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        lDst2[0] = QUADAVG_X(t4,t6); \
        lDst2[1] = QUADAVG_X(t5,t7); \
        t4=t6;\
        t5=t7;\
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H2V2_8xn(Src, Dst, Src2, Dst2, Stride, A1, A2, BILINEAR_X, v) \
{ \
    int dy;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11; \
    uint32 *RESTRICT lSrc1;  \
    uint32 *RESTRICT lSrc2;  \
    uint32 *RESTRICT lSrc = (uint32 *) Src; \
    uint32 *RESTRICT lDst = (uint32 *) Dst; \
    uint32 *RESTRICT lSrc_2 = (uint32 *) Src2; \
    uint32 *RESTRICT lDst_2 = (uint32 *) Dst2; \
    int lStride = Stride >> 2; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
    t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
    x0 = FUNSHIFT##A1(lSrc_2[1], lSrc_2[0]);                      \
    x1 = FUNSHIFT##A2(lSrc_2[1], lSrc_2[0]);                      \
    x2 = FUNSHIFT##A1(lSrc_2[2], lSrc_2[1]);                      \
    x3 = FUNSHIFT##A2(lSrc_2[2], lSrc_2[1]);                      \
    dy = 0; \
    do { \
        dy++;    \
        lSrc1 = lSrc + lStride;     \
        t4 = FUNSHIFT##A1(lSrc1[1], lSrc1[0]);                      \
        t5 = FUNSHIFT##A2(lSrc1[1], lSrc1[0]);                      \
        t6 = FUNSHIFT##A1(lSrc1[2], lSrc1[1]);                      \
        t7 = FUNSHIFT##A2(lSrc1[2], lSrc1[1]);                      \
        t8 = BILINEAR_X(t0,t4); \
        t10 = BILINEAR_X(t1,t5); \
        t9 = BILINEAR_X(t2,t6); \
        t11 = BILINEAR_X(t3,t7); \
        lDst[0] = MERGEODD(t10,t8); \
        lDst[1] = MERGEODD(t11,t9);         \
        t0 = t4;                                    \
        t1 = t5;                                    \
        t2 = t6;                                    \
        t3 = t7;                                    \
        lSrc  = lSrc1;                              \
        lDst += lStride;\
        \
        lSrc2 = lSrc_2 + lStride;     \
        x4 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        x5 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        x6 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
        x7 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
        x8 = BILINEAR_X(x0,x4); \
        x10 = BILINEAR_X(x1,x5); \
        x9 = BILINEAR_X(x2,x6); \
        x11 = BILINEAR_X(x3,x7); \
        lDst_2[0] = MERGEODD(x10,x8); \
        lDst_2[1] = MERGEODD(x11,x9);         \
        x0 = x4;                                    \
        x1 = x5;                                    \
        x2 = x6;                                    \
        x3 = x7;                                    \
        lSrc_2  = lSrc2;                              \
        lDst_2 += lStride;\
    } while (dy < v); \
}


#define avc_CopyBlkEFunc_8_1(tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    m[1] = PACKBYTES(tmp[1], tmp[0]); \
    m[3] = PACKBYTES(tmp[2], tmp[1]); \
    m[5] = PACKBYTES(tmp[3], tmp[2]); \
    m[7] = PACKBYTES(tmp[4], tmp[3]); \
    t1 = IFIR8UI(PACK16LSB(m[0], m[1]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[2], m[3]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[4], m[5]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[6], m[7]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    m[9] = PACKBYTES(tmp[5], tmp[4]); \
    m[11] = PACKBYTES(tmp[6], tmp[5]); \
    m[13] = PACKBYTES(tmp[7], tmp[6]); \
    m[15] = PACKBYTES(tmp[8], tmp[7]); \
    t1 = IFIR8UI(PACK16LSB(m[8], m[9]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[10], m[11]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[12], m[13]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[14], m[15]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride; \
    tmp += stride; \
    m[0] = PACKBYTES(tmp[1], tmp[0]); \
    m[2] = PACKBYTES(tmp[2], tmp[1]); \
    m[4] = PACKBYTES(tmp[3], tmp[2]); \
    m[6] = PACKBYTES(tmp[4], tmp[3]); \
    t1 = IFIR8UI(PACK16LSB(m[1], m[0]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[3], m[2]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[5], m[4]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[7], m[6]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t2,t1); \
    m[8] = PACKBYTES(tmp[5], tmp[4]); \
    m[10] = PACKBYTES(tmp[6], tmp[5]); \
    m[12] = PACKBYTES(tmp[7], tmp[6]); \
    m[14] = PACKBYTES(tmp[8], tmp[7]); \
    t1 = IFIR8UI(PACK16LSB(m[9], m[8]), coef); \
    t2 = IFIR8UI(PACK16LSB(m[11], m[10]), coef); \
    t3 = IFIR8UI(PACK16LSB(m[13], m[12]), coef); \
    t4 = IFIR8UI(PACK16LSB(m[15], m[14]), coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t2 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t2,t1); \
    dst += dst_stride; \
    tmp += stride;

#define avc_CopyBlkEFunc_8_UAMEM(lsrc, tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF) \
    lsrc[1] = (uint32 * RESTRICT)(tmp+stride); \
    lsrc[3] = (uint32 * RESTRICT)(tmp+stride+1); \
    m[0] = PACK16LSB(lsrc[0][0], lsrc[1][0]); \
    m[1] = PACK16LSB(lsrc[2][0], lsrc[3][0]); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    m[2] = PACK16MSB(lsrc[0][0], lsrc[1][0]); \
    m[3] = PACK16MSB(lsrc[2][0], lsrc[3][0]); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    m[0] = PACK16LSB(lsrc[0][1], lsrc[1][1]); \
    m[1] = PACK16LSB(lsrc[2][1], lsrc[3][1]); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    m[2] = PACK16MSB(lsrc[0][1], lsrc[1][1]); \
    m[3] = PACK16MSB(lsrc[2][1], lsrc[3][1]); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t3,t1); \
    dst += dst_stride; \
    tmp += stride_mul2; \
    lsrc[0] = (uint32 * RESTRICT)(tmp); \
    lsrc[2] = (uint32 * RESTRICT)(tmp+1); \
    m[4] = PACK16LSB(lsrc[1][0], lsrc[0][0]); \
    m[5] = PACK16LSB(lsrc[3][0], lsrc[2][0]); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    m[6] = PACK16MSB(lsrc[1][0], lsrc[0][0]); \
    m[7] = PACK16MSB(lsrc[3][0], lsrc[2][0]); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    m[4] = PACK16LSB(lsrc[1][1], lsrc[0][1]); \
    m[5] = PACK16LSB(lsrc[3][1], lsrc[2][1]); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    m[6] = PACK16MSB(lsrc[1][1], lsrc[0][1]); \
    m[7] = PACK16MSB(lsrc[3][1], lsrc[2][1]); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t3,t1); \
    dst += dst_stride;

#ifdef _UAMEM_ACCESS_
#define HxVx_8_n(src, src2, dst, dst2, Stride, rounding, f1, f2, f3, f4, shift, v) \
{ \
    int dy; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11; \
    uint32 *RESTRICT lSrc1; \
    uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    uint32 *RESTRICT lSrc2; \
    uint32 *RESTRICT lSrc_2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst_2 = (uint32 *) dst2; \
    int lStride = Stride >> 2; \
    uint32 p_rounding; \
    t0 = MERGEODD(0, FUNSHIFT4(lSrc[1], lSrc[0])); \
    t1 = MERGEODD(0, FUNSHIFT3(lSrc[1], lSrc[0])); \
    t2 = MERGEODD(0, FUNSHIFT2(lSrc[1], lSrc[0])); \
    \
    t3 = MERGEODD(0, FUNSHIFT4(lSrc[2], lSrc[1])); \
    t4 = MERGEODD(0, FUNSHIFT3(lSrc[2], lSrc[1])); \
    t5 = MERGEODD(0, FUNSHIFT2(lSrc[2], lSrc[1])); \
    \
    x0 = MERGEODD(0, FUNSHIFT4(lSrc_2[1], lSrc_2[0])); \
    x1 = MERGEODD(0, FUNSHIFT3(lSrc_2[1], lSrc_2[0])); \
    x2 = MERGEODD(0, FUNSHIFT2(lSrc_2[1], lSrc_2[0])); \
    \
    x3 = MERGEODD(0, FUNSHIFT4(lSrc_2[2], lSrc_2[1])); \
    x4 = MERGEODD(0, FUNSHIFT3(lSrc_2[2], lSrc_2[1])); \
    x5 = MERGEODD(0, FUNSHIFT2(lSrc_2[2], lSrc_2[1])); \
    \
    dy = 0; \
    p_rounding = PACK16LSB(rounding, rounding);  \
LOOP:\
    dy++; \
    lSrc1 = lSrc + lStride; \
    t6 = MERGEODD(0, FUNSHIFT4(       0, lSrc1[0])); \
    t7 = MERGEODD(0, FUNSHIFT3(       0, lSrc1[0])); \
    t8 = MERGEODD(0, FUNSHIFT2(lSrc1[1], lSrc1[0]));  \
    /*t0 = (FACTOR_##f1(t0)+FACTOR_##f2(t1)+FACTOR_##f3(t6)+FACTOR_##f4(t7)+p_rounding)>>shift; \
    t1 = (FACTOR_##f1(t1)+FACTOR_##f2(t2)+FACTOR_##f3(t7)+FACTOR_##f4(t8)+p_rounding)>>shift; */\
    t0 = (DSPIDUALMUL(t0, f1)+DSPIDUALMUL(t1, f2)+DSPIDUALMUL(t6, f3)+DSPIDUALMUL(t7, f4)+p_rounding)>>shift; \
    t1 = (DSPIDUALMUL(t1, f1)+DSPIDUALMUL(t2, f2)+DSPIDUALMUL(t7, f3)+DSPIDUALMUL(t8, f4)+p_rounding)>>shift; \
    lDst[0] = MERGEODD(t1,t0); \
    \
    t9  = MERGEODD(0, FUNSHIFT4(       0, lSrc1[1])); \
    t10 = MERGEODD(0, FUNSHIFT3(       0, lSrc1[1])); \
    t11 = MERGEODD(0, FUNSHIFT2(lSrc1[2], lSrc1[1])); \
    \
    /*t3 = (FACTOR_##f1(t3)+FACTOR_##f2(t4)+FACTOR_##f3(t9)+FACTOR_##f4(t10)+p_rounding)>>shift; \
    t4 = (FACTOR_##f1(t4)+FACTOR_##f2(t5)+FACTOR_##f3(t10)+FACTOR_##f4(t11)+p_rounding)>>shift; */\
    t3 = (DSPIDUALMUL(t3, f1)+DSPIDUALMUL(t4, f2)+DSPIDUALMUL(t9, f3)+DSPIDUALMUL(t10, f4)+p_rounding)>>shift; \
    t4 = (DSPIDUALMUL(t4, f1)+DSPIDUALMUL(t5, f2)+DSPIDUALMUL(t10, f3)+DSPIDUALMUL(t11, f4)+p_rounding)>>shift; \
    lDst[1] = MERGEODD(t4,t3); \
    t0 = t6;                    \
    t1 = t7;                    \
    t2 = t8;                    \
    t3 = t9;                    \
    t4 = t10;                   \
    t5 = t11;                   \
    lSrc  = lSrc1;              \
    lDst += lStride;        \
    \
    lSrc2 = lSrc_2 + lStride; \
    x6 = MERGEODD(0, FUNSHIFT4(       0, lSrc2[0])); \
    x7 = MERGEODD(0, FUNSHIFT3(       0, lSrc2[0])); \
    x8 = MERGEODD(0, FUNSHIFT2(lSrc2[1], lSrc2[0]));  \
    /*x0 = (FACTOR_##f1(x0)+FACTOR_##f2(x1)+FACTOR_##f3(x6)+FACTOR_##f4(x7)+p_rounding)>>shift; \
    x1 = (FACTOR_##f1(x1)+FACTOR_##f2(x2)+FACTOR_##f3(x7)+FACTOR_##f4(x8)+p_rounding)>>shift; */\
    x0 = (DSPIDUALMUL(x0, f1)+DSPIDUALMUL(x1, f2)+DSPIDUALMUL(x6, f3)+DSPIDUALMUL(x7, f4)+p_rounding)>>shift; \
    x1 = (DSPIDUALMUL(x1, f1)+DSPIDUALMUL(x2, f2)+DSPIDUALMUL(x7, f3)+DSPIDUALMUL(x8, f4)+p_rounding)>>shift; \
    lDst_2[0] = MERGEODD(x1,x0); \
    \
    x9  = MERGEODD(0, FUNSHIFT4(       0, lSrc2[1])); \
    x10 = MERGEODD(0, FUNSHIFT3(       0, lSrc2[1])); \
    x11 = MERGEODD(0, FUNSHIFT2(lSrc2[2], lSrc2[1])); \
    \
    /*x3 = (FACTOR_##f1(x3)+FACTOR_##f2(x4)+FACTOR_##f3(x9)+FACTOR_##f4(x10)+p_rounding)>>shift; \
    x4 = (FACTOR_##f1(x4)+FACTOR_##f2(x5)+FACTOR_##f3(x10)+FACTOR_##f4(x11)+p_rounding)>>shift; */\
    x3 = (DSPIDUALMUL(x3, f1)+DSPIDUALMUL(x4, f2)+DSPIDUALMUL(x9, f3)+DSPIDUALMUL(x10, f4)+p_rounding)>>shift; \
    x4 = (DSPIDUALMUL(x4, f1)+DSPIDUALMUL(x5, f2)+DSPIDUALMUL(x10, f3)+DSPIDUALMUL(x11, f4)+p_rounding)>>shift; \
    lDst_2[1] = MERGEODD(x4,x3); \
    if (dy>=v) \
        return; \
    x0 = x6;                    \
    x1 = x7;                    \
    x2 = x8;                    \
    x3 = x9;                    \
    x4 = x10;                   \
    x5 = x11;                   \
    lSrc_2  = lSrc2;              \
    lDst_2 += lStride;        \
    goto LOOP;                      \
}
#else
#define HxVx_8_n(src, src2, dst, dst2, Stride, rounding, f1, f2, f3, f4, shift, v) \
{ \
    int dy; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    uint32 *RESTRICT lDst_2 = (uint32 *) dst2; \
    const uchar *RESTRICT src_t; \
    const uchar *RESTRICT src2_t; \
    int lStride = Stride >> 2; \
    uint32 p_rounding; \
    \
    t0 = PACK16LSB(*(src+2), *(src+0)); \
    t1 = PACK16LSB(*(src+3), *(src+1)); \
    t2 = PACK16LSB(*(src+4), *(src+2)); \
    \
    t3 = PACK16LSB(*(src+6), *(src+4)); \
    t4 = PACK16LSB(*(src+7), *(src+5)); \
    t5 = PACK16LSB(*(src+8), *(src+6)); \
    \
    x0 = PACK16LSB(*(src2+2), *(src2+0)); \
    x1 = PACK16LSB(*(src2+3), *(src2+1)); \
    x2 = PACK16LSB(*(src2+4), *(src2+2)); \
    \
    x3 = PACK16LSB(*(src2+6), *(src2+4)); \
    x4 = PACK16LSB(*(src2+7), *(src2+5)); \
    x5 = PACK16LSB(*(src2+8), *(src2+6)); \
    \
    dy = 0; \
    p_rounding = PACK16LSB(rounding, rounding);  \
LOOP:\
    dy++; \
    src_t = src + Stride; \
    \
    t6 = PACK16LSB(*(src_t+2), *(src_t+0)); \
    t7 = PACK16LSB(*(src_t+3), *(src_t+1)); \
    t8 = PACK16LSB(*(src_t+4), *(src_t+2)); \
    /*t0 = (FACTOR_##f1(t0)+FACTOR_##f2(t1)+FACTOR_##f3(t6)+FACTOR_##f4(t7)+p_rounding)>>shift; \
    t1 = (FACTOR_##f1(t1)+FACTOR_##f2(t2)+FACTOR_##f3(t7)+FACTOR_##f4(t8)+p_rounding)>>shift; */\
    t0 = (DSPIDUALMUL(t0, f1)+DSPIDUALMUL(t1, f2)+DSPIDUALMUL(t6, f3)+DSPIDUALMUL(t7, f4)+p_rounding)>>shift; \
    t1 = (DSPIDUALMUL(t1, f1)+DSPIDUALMUL(t2, f2)+DSPIDUALMUL(t7, f3)+DSPIDUALMUL(t8, f4)+p_rounding)>>shift; \
    lDst[0] = MERGEODD(t1,t0); \
    \
    t9  = PACK16LSB(*(src_t+6), *(src_t+4)); \
    t10 = PACK16LSB(*(src_t+7), *(src_t+5)); \
    t11 = PACK16LSB(*(src_t+8), *(src_t+6)); \
    \
    /*t3 = (FACTOR_##f1(t3)+FACTOR_##f2(t4)+FACTOR_##f3(t9)+FACTOR_##f4(t10)+p_rounding)>>shift; \
    t4 = (FACTOR_##f1(t4)+FACTOR_##f2(t5)+FACTOR_##f3(t10)+FACTOR_##f4(t11)+p_rounding)>>shift; */\
    t3 = (DSPIDUALMUL(t3, f1)+DSPIDUALMUL(t4, f2)+DSPIDUALMUL(t9, f3)+DSPIDUALMUL(t10, f4)+p_rounding)>>shift; \
    t4 = (DSPIDUALMUL(t4, f1)+DSPIDUALMUL(t5, f2)+DSPIDUALMUL(t10, f3)+DSPIDUALMUL(t11, f4)+p_rounding)>>shift; \
    lDst[1] = MERGEODD(t4,t3); \
    t0 = t6;                    \
    t1 = t7;                    \
    t2 = t8;                    \
    t3 = t9;                    \
    t4 = t10;                   \
    t5 = t11;                   \
    src = src_t; \
    lDst += lStride;        \
    \
    src2_t = src2 + Stride; \
    x6 = PACK16LSB(*(src2_t+2), *(src2_t+0)); \
    x7 = PACK16LSB(*(src2_t+3), *(src2_t+1)); \
    x8 = PACK16LSB(*(src2_t+4), *(src2_t+2)); \
    /*x0 = (FACTOR_##f1(x0)+FACTOR_##f2(x1)+FACTOR_##f3(x6)+FACTOR_##f4(x7)+p_rounding)>>shift; \
    x1 = (FACTOR_##f1(x1)+FACTOR_##f2(x2)+FACTOR_##f3(x7)+FACTOR_##f4(x8)+p_rounding)>>shift; */\
    x0 = (DSPIDUALMUL(x0, f1)+DSPIDUALMUL(x1, f2)+DSPIDUALMUL(x6, f3)+DSPIDUALMUL(x7, f4)+p_rounding)>>shift; \
    x1 = (DSPIDUALMUL(x1, f1)+DSPIDUALMUL(x2, f2)+DSPIDUALMUL(x7, f3)+DSPIDUALMUL(x8, f4)+p_rounding)>>shift; \
    lDst_2[0] = MERGEODD(x1,x0); \
    \
    x9  = PACK16LSB(*(src2_t+6), *(src2_t+4)); \
    x10 = PACK16LSB(*(src2_t+7), *(src2_t+5)); \
    x11 = PACK16LSB(*(src2_t+8), *(src2_t+6)); \
    \
    /*x3 = (FACTOR_##f1(x3)+FACTOR_##f2(x4)+FACTOR_##f3(x9)+FACTOR_##f4(x10)+p_rounding)>>shift; \
    x4 = (FACTOR_##f1(x4)+FACTOR_##f2(x5)+FACTOR_##f3(x10)+FACTOR_##f4(x11)+p_rounding)>>shift; */\
    x3 = (DSPIDUALMUL(x3, f1)+DSPIDUALMUL(x4, f2)+DSPIDUALMUL(x9, f3)+DSPIDUALMUL(x10, f4)+p_rounding)>>shift; \
    x4 = (DSPIDUALMUL(x4, f1)+DSPIDUALMUL(x5, f2)+DSPIDUALMUL(x10, f3)+DSPIDUALMUL(x11, f4)+p_rounding)>>shift; \
    lDst_2[1] = MERGEODD(x4,x3); \
    if (dy>=v) \
    return; \
    x0 = x6;                    \
    x1 = x7;                    \
    x2 = x8;                    \
    x3 = x9;                    \
    x4 = x10;                   \
    x5 = x11;                   \
    src2 = src2_t; \
    lDst_2 += lStride;        \
    goto LOOP;                      \
}

#endif

#define HxVx_8_n_v2(src, src2, dst, dst2, Stride, rounding, f1, f2, f3, f4, shift, A1, A2, t, v) \
{ \
    int dy; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11; \
    uint32 *RESTRICT lSrc1; \
    uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    uint32 *RESTRICT lSrc2; \
    uint32 *RESTRICT lSrc_2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst_2 = (uint32 *) dst2; \
    int lStride = Stride >> 2; \
    uint32 p_rounding; \
    t0 = MERGEODD(0, FUNSHIFT##A1(lSrc[1], lSrc[0])); \
    t1 = MERGEODD(0, FUNSHIFT##A2(lSrc[1], lSrc[0])); \
    t2 = MERGEODD(0, FUNSHIFT##A2(lSrc[1], lSrc[0]) >> 8); \
    \
    t3 = MERGEODD(0, FUNSHIFT##A1(lSrc[2], lSrc[1])); \
    t4 = MERGEODD(0, FUNSHIFT##A2(lSrc[2], lSrc[1])); \
    t5 = MERGEODD(0, FUNSHIFT##A2(lSrc[2], lSrc[1]) >> 8); \
    \
    x0 = MERGEODD(0, FUNSHIFT##A1(lSrc_2[1], lSrc_2[0])); \
    x1 = MERGEODD(0, FUNSHIFT##A2(lSrc_2[1], lSrc_2[0])); \
    x2 = MERGEODD(0, FUNSHIFT##A2(lSrc_2[1], lSrc_2[0]) >> 8); \
    \
    x3 = MERGEODD(0, FUNSHIFT##A1(lSrc_2[2], lSrc_2[1])); \
    x4 = MERGEODD(0, FUNSHIFT##A2(lSrc_2[2], lSrc_2[1])); \
    x5 = MERGEODD(0, FUNSHIFT##A2(lSrc_2[2], lSrc_2[1]) >> 8); \
    \
    dy = 0; \
    p_rounding = PACK16LSB(rounding, rounding);  \
LOOP##t:\
    dy++; \
    lSrc1 = lSrc + lStride; \
    t6 = MERGEODD(0, FUNSHIFT##A1(lSrc1[1], lSrc1[0])); \
    t7 = MERGEODD(0, FUNSHIFT##A2(lSrc1[1], lSrc1[0])); \
    t8 = MERGEODD(0, FUNSHIFT##A2(lSrc1[1], lSrc1[0]) >> 8); \
    t0 = (FACTOR_##f1(t0)+FACTOR_##f2(t1)+FACTOR_##f3(t6)+FACTOR_##f4(t7)+p_rounding)>>shift; \
    t1 = (FACTOR_##f1(t1)+FACTOR_##f2(t2)+FACTOR_##f3(t7)+FACTOR_##f4(t8)+p_rounding)>>shift; \
    lDst[0] = MERGEODD(t1,t0); \
    \
    t9  = MERGEODD(0, FUNSHIFT##A1(lSrc1[2], lSrc1[1])); \
    t10 = MERGEODD(0, FUNSHIFT##A2(lSrc1[2], lSrc1[1])); \
    t11 = MERGEODD(0, FUNSHIFT##A2(lSrc1[2], lSrc1[1]) >> 8); \
    \
    t3 = (FACTOR_##f1(t3)+FACTOR_##f2(t4)+FACTOR_##f3(t9)+FACTOR_##f4(t10)+p_rounding)>>shift; \
    t4 = (FACTOR_##f1(t4)+FACTOR_##f2(t5)+FACTOR_##f3(t10)+FACTOR_##f4(t11)+p_rounding)>>shift; \
    lDst[1] = MERGEODD(t4,t3); \
    t0 = t6;                    \
    t1 = t7;                    \
    t2 = t8;                    \
    t3 = t9;                    \
    t4 = t10;                   \
    t5 = t11;                   \
    lSrc  = lSrc1;              \
    lDst += lStride;        \
    \
    lSrc2 = lSrc_2 + lStride; \
    x6 = MERGEODD(0, FUNSHIFT##A1(lSrc2[1], lSrc2[0])); \
    x7 = MERGEODD(0, FUNSHIFT##A2(lSrc2[1], lSrc2[0])); \
    x8 = MERGEODD(0, FUNSHIFT##A2(lSrc2[1], lSrc2[0]) >> 8); \
    x0 = (FACTOR_##f1(x0)+FACTOR_##f2(x1)+FACTOR_##f3(x6)+FACTOR_##f4(x7)+p_rounding)>>shift; \
    x1 = (FACTOR_##f1(x1)+FACTOR_##f2(x2)+FACTOR_##f3(x7)+FACTOR_##f4(x8)+p_rounding)>>shift; \
    lDst_2[0] = MERGEODD(x1,x0); \
    \
    x9  = MERGEODD(0, FUNSHIFT##A1(lSrc2[2], lSrc2[1])); \
    x10 = MERGEODD(0, FUNSHIFT##A2(lSrc2[2], lSrc2[1])); \
    x11 = MERGEODD(0, FUNSHIFT##A2(lSrc2[2], lSrc2[1]) >> 8); \
    \
    x3 = (FACTOR_##f1(x3)+FACTOR_##f2(x4)+FACTOR_##f3(x9)+FACTOR_##f4(x10)+p_rounding)>>shift; \
    x4 = (FACTOR_##f1(x4)+FACTOR_##f2(x5)+FACTOR_##f3(x10)+FACTOR_##f4(x11)+p_rounding)>>shift; \
    lDst_2[1] = MERGEODD(x4,x3); \
    if (dy>=v) \
        return; \
    x0 = x6;                    \
    x1 = x7;                    \
    x2 = x8;                    \
    x3 = x9;                    \
    x4 = x10;                   \
    x5 = x11;                   \
    lSrc_2  = lSrc2;              \
    lDst_2 += lStride;        \
    goto LOOP##t;                      \
}
    
#ifdef _UAMEM_ACCESS_
#define FILTER_C_HQVQ_8xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, coef, rounding, shift, v) \
{ \
    uint32 s[8], r[8]; \
    int t1, t2, t3, t4; \
    uint32 *RESTRICT lsrc[4]; \
    uint32 *RESTRICT lsrc2[4]; \
    int stride_mul2 = src_stride<<1; \
    int i = v; \
    \
    lsrc[0] = (uint32 * RESTRICT)pSrc; \
    lsrc[2] = (uint32 * RESTRICT)(pSrc+1); \
    lsrc2[0] = (uint32 * RESTRICT)pSrc2; \
    lsrc2[2] = (uint32 * RESTRICT)(pSrc2+1); \
    do { \
        avc_CopyBlkEFunc_8_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        avc_CopyBlkEFunc_8_UAMEM(lsrc2, pSrc2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
        avc_CopyBlkEFunc_8_UAMEM(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        avc_CopyBlkEFunc_8_UAMEM(lsrc2, pSrc2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
        i -= 4; \
    } while (i>0); \
}

#else
#define FILTER_C_HQVQ_8xn(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, coef, rounding, shift, v) \
{ \
    uint32 s[16], r[16]; \
    int t1, t2, t3, t4; \
    const uchar * RESTRICT tmp; \
    const uchar * RESTRICT tmp2; \
    const uint32 *RESTRICT lsrc[4]; \
    const uint32 *RESTRICT lsrc2[4]; \
    int stride_mul2 = src_stride<<1; \
    int i = v; \
    \
    s[0] = PACKBYTES(pSrc[1], pSrc[0]); \
    s[2] = PACKBYTES(pSrc[2], pSrc[1]); \
    s[4] = PACKBYTES(pSrc[3], pSrc[2]); \
    s[6] = PACKBYTES(pSrc[4], pSrc[3]); \
    s[8] = PACKBYTES(pSrc[5], pSrc[4]); \
    s[10] = PACKBYTES(pSrc[6], pSrc[5]); \
    s[12] = PACKBYTES(pSrc[7], pSrc[6]); \
    s[14] = PACKBYTES(pSrc[8], pSrc[7]); \
    r[0] = PACKBYTES(pSrc2[1], pSrc2[0]); \
    r[2] = PACKBYTES(pSrc2[2], pSrc2[1]); \
    r[4] = PACKBYTES(pSrc2[3], pSrc2[2]); \
    r[6] = PACKBYTES(pSrc2[4], pSrc2[3]); \
    r[8] = PACKBYTES(pSrc2[5], pSrc2[4]); \
    r[10] = PACKBYTES(pSrc2[6], pSrc2[5]); \
    r[12] = PACKBYTES(pSrc2[7], pSrc2[6]); \
    r[14] = PACKBYTES(pSrc2[8], pSrc2[7]); \
    tmp = pSrc+src_stride; \
    tmp2 = pSrc2+src_stride; \
    do { \
        avc_CopyBlkEFunc_8_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        avc_CopyBlkEFunc_8_1(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        avc_CopyBlkEFunc_8_1(tmp2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
        avc_CopyBlkEFunc_8_1(tmp2, pDst2, coef, src_stride, dst_stride, r, rounding, shift); \
        i -= 4; \
    } while (i>0); \
}

#endif

/***********************************************************************************************/

#ifdef _TM5250_
#define Copy8H1_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;     \
    const uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]);                      \
        \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t8 = BILINEAR1(t4,t0); \
        t9 = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        if (h==4) \
            goto NEXT_ITER; \
        t2 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT3(lSrc[2], lSrc[1]);                      \
        t6  = MERGEODD(t2,t2);             /*6 6 4 4  */    \
        t7  = MERGEODD(t3,t3);             /*7 7 5 5  */    \
        t10 = BILINEAR1(t6,t2); \
        t11 = BILINEAR1(t7,t3); \
        lDst[1] = MERGEODD(t11,t10);\
NEXT_ITER: \
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    } while (dy < v);                      \
}
#else
#define Copy8H1_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride>>2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    int t = (int) src & 0x3 ;\
    for (dy = 0; dy < 8; dy++) {                   \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        /*t0  = lSrc[0];                     //3 2 1 0 */   \
        /*t1  = FUNSHIFT3(lSrc[1], lSrc[0]); //4 3 2 1 */   \
        /*t2  = lSrc[1];                     //7 6 5 4 */   \
        /*t3  = FUNSHIFT3(lSrc[2], lSrc[1]); //8 7 6 5 */   \
        t4  = MERGEODD(t0,t0);             /*2 2 0 0  */    \
        t5  = MERGEODD(t1,t1);             /*3 3 1 1  */    \
        t6  = MERGEODD(t2,t2);             /*6 6 4 4  */    \
        t7  = MERGEODD(t3,t3);             /*7 7 5 5  */    \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        t10 = BILINEAR1(t6,t2);\
        t11 = BILINEAR1(t7,t3);\
        lDst[0] = MERGEODD(t9,t8);\
        lDst[1] = MERGEODD(t11,t10);\
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    }                       \
}
#endif

#ifdef _TM5250_
#define Copy8H2_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG(t0,t1); \
        if (h==4) \
            goto NEXT_ITER; \
        t2 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT3(lSrc[2], lSrc[1]);                      \
        lDst[1] = QUADAVG(t2,t3); \
NEXT_ITER: \
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    } while (dy < v);\
}
#else
#define Copy8H2_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int t;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    t = (int) src & 0x3;\
    for (dy = 0; dy < 8; dy++) {                   \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        lDst[0] = QUADAVG(t0,t1);\
        lDst[1] = QUADAVG(t2,t3);\
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    }\
}
#endif

#ifdef _TM5250_
#define Copy8H3_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT3(lSrc[1], lSrc[0]);                      \
        t4  = MERGEODD(t1,t1);             /*3 3 1 1*/           \
        t5  = MERGEODD((t1>>8),(t1>>8));   /*4 4 2 2*/           \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        lDst[0] = MERGEODD(t9,t8);\
        if (h==4) \
            goto NEXT_ITER; \
        t2 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT3(lSrc[2], lSrc[1]);                      \
        t6  = MERGEODD(t3,t3);             /*7 7 5 5*/           \
        t7  = MERGEODD((t3>>8),(t3>>8));   /*8 8 6 6*/           \
        t10 = BILINEAR1(t6,t2);\
        t11 = BILINEAR1(t7,t3);\
        lDst[1] = MERGEODD(t11,t10);\
NEXT_ITER: \
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    } while (dy < v);             \
}
#else
#define Copy8H3_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    int t = (int) src & 0x3;\
    for (dy = 0; dy < 8; dy++) {                   \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
        t4  = MERGEODD(t1,t1);             /*3 3 1 1*/           \
        t5  = MERGEODD((t1>>8),(t1>>8));   /*4 4 2 2*/           \
        t6  = MERGEODD(t3,t3);             /*7 7 5 5*/           \
        t7  = MERGEODD((t3>>8),(t3>>8));   /*8 8 6 6*/           \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        t10 = BILINEAR1(t6,t2);\
        t11 = BILINEAR1(t7,t3);\
        lDst[0] = MERGEODD(t9,t8);\
        lDst[1] = MERGEODD(t11,t10);\
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
    }\
}
#endif

#ifdef _TM5250_
#define Copy8V1_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        if (h==4) \
            goto NEXT_ITER; \
        t3 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        t8  = MERGELSB(t1,t1);             /*5  5 4  4     */         \
        t9  = MERGELSB(t3,t1);             /*v5 5 v5 4    */        \
        t10 = MERGEMSB(t1,t1);             /*7  7 6  6     */       \
        t11 = MERGEMSB(t3,t1);             /*v7 7 v6 6     */   \
        t14 = BILINEAR2(t9,t8);\
        t15 = BILINEAR2(t11,t10);\
        lDst[1] = MERGEDUAL16LSB(t15,t14);\
        t1 = t3;\
NEXT_ITER: \
        lDst += dStride; \
    } while (dy < v);\
}
#else
#define Copy8V1_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) ((int)src&0xfffffffc);                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    int t = (int) src & 0x3;\
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    for (dy = 0; dy < 8; dy++) {                   \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t8  = MERGELSB(t1,t1);             /*5  5 4  4     */         \
        t9  = MERGELSB(t3,t1);             /*v5 5 v5 4    */        \
        t10 = MERGEMSB(t1,t1);             /*7  7 6  6     */       \
        t11 = MERGEMSB(t3,t1);             /*v7 7 v6 6     */   \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        t14 = BILINEAR2(t9,t8);\
        t15 = BILINEAR2(t11,t10);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        lDst[1] = MERGEDUAL16LSB(t15,t14);\
        t0 = t2;\
        t1 = t3;\
        lDst += dStride; \
    }\
}
#endif

#ifdef _TM5250_
#define Copy8V2_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7;\
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG0(t0,t2); \
        t0=t2;\
        if (h==4) \
            goto NEXT_ITER; \
        t3 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        lDst[1] = QUADAVG0(t1,t3); \
        t1=t3;\
NEXT_ITER: \
        lDst += dStride; \
    } while (dy < v);\
}
#else
#define Copy8V2_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = Stride >> 2;\
    uint32 t0, t1, t2, t3;\
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    int t = (int) src & 0x3;\
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    for (dy = 0; dy < 8; dy++) {                   \
        lSrc += lStride;\
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        lDst[0] = QUADAVG0(t0,t2);\
        lDst[1] = QUADAVG0(t1,t3);\
        t0=t2;\
        t1=t3;\
        lDst += dStride; \
    }\
}
#endif

#ifdef _TM5250_
#define Copy8V3_tmp(src, dst, h, v, Stride, dst_stride) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    t0 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT4(lSrc[1], lSrc[0]);                      \
        t4  = MERGELSB(t2,t0);             /*v1  1 v0  0            */  \
        t5  = MERGELSB(t2,t2);             /*v1 v1 v0 v0            */  \
        t6  = MERGEMSB(t2,t0);             /*v3  3 v2  2            */  \
        t7  = MERGEMSB(t2,t2);             /*v3 v3 v2 v2            */  \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        if (h==4) \
            goto NEXT_ITER; \
        t3 = FUNSHIFT4(lSrc[2], lSrc[1]);                      \
        t8  = MERGELSB(t3,t1);             /*v5  5 v5  4            */  \
        t9  = MERGELSB(t3,t3);             /*v5 v5 v4 v4            */  \
        t10 = MERGEMSB(t3,t1);             /*v7  7 v6  6            */  \
        t11 = MERGEMSB(t3,t3);             /*v7 v7 v6 v6            */  \
        t14 = BILINEAR2(t9,t8);\
        t15 = BILINEAR2(t11,t10);\
        lDst[1] = MERGEDUAL16LSB(t15,t14);\
        t1 = t3;\
NEXT_ITER: \
        lDst += dStride; \
    } while (dy < v);\
}
#else
#define Copy8V3_tmp(src, dst, Stride, dst_stride, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
    for (dy = 0; dy < 8; dy++) {                   \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t4  = MERGELSB(t2,t0);             /*v1  1 v0  0            */  \
        t5  = MERGELSB(t2,t2);             /*v1 v1 v0 v0            */  \
        t6  = MERGEMSB(t2,t0);             /*v3  3 v2  2            */  \
        t7  = MERGEMSB(t2,t2);             /*v3 v3 v2 v2            */  \
        t8  = MERGELSB(t3,t1);             /*v5  5 v5  4            */  \
        t9  = MERGELSB(t3,t3);             /*v5 v5 v4 v4            */  \
        t10 = MERGEMSB(t3,t1);             /*v7  7 v6  6            */  \
        t11 = MERGEMSB(t3,t3);             /*v7 v7 v6 v6            */  \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        t14 = BILINEAR2(t9,t8);\
        t15 = BILINEAR2(t11,t10);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        lDst[1] = MERGEDUAL16LSB(t15,t14);\
        t0 = t2;\
        t1 = t3;\
        lDst += dStride; \
    }\
}
#endif

#ifdef _UAMEM_ACCESS_
#define FILTER_BILINEAR_8_SHARE(lsrc, tmp, dst, coef, stride, dst_stride, m, ADD_COEF, SHIFT_COEF, h, A) \
    lsrc[1] = (uint32 * RESTRICT)(tmp+stride); \
    lsrc[3] = (uint32 * RESTRICT)(tmp+stride+1); \
    m[0] = PACK16LSB(lsrc[0][0], lsrc[1][0]); \
    m[1] = PACK16LSB(lsrc[2][0], lsrc[3][0]); \
    m[2] = PACK16MSB(lsrc[0][0], lsrc[1][0]); \
    m[3] = PACK16MSB(lsrc[2][0], lsrc[3][0]); \
    t1 = IFIR8UI(m[0], coef); \
    t2 = IFIR8UI(m[1], coef); \
    t3 = IFIR8UI(m[2], coef); \
    t4 = IFIR8UI(m[3], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    if (h==4) goto NEXT_ITER##A; \
    lsrc[5] = (uint32 * RESTRICT)(tmp+stride+4); \
    lsrc[7] = (uint32 * RESTRICT)(tmp+stride+5); \
    m[4] = PACK16LSB(lsrc[4][0], lsrc[5][0]); \
    m[5] = PACK16LSB(lsrc[6][0], lsrc[7][0]); \
    m[6] = PACK16MSB(lsrc[4][0], lsrc[5][0]); \
    m[7] = PACK16MSB(lsrc[6][0], lsrc[7][0]); \
    t5 = IFIR8UI(m[4], coef); \
    t6 = IFIR8UI(m[5], coef); \
    t7 = IFIR8UI(m[6], coef); \
    t8 = IFIR8UI(m[7], coef); \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
NEXT_ITER##A: \
    dst += dst_stride; \
    tmp += stride_mul2; \
    lsrc[0] = (uint32 * RESTRICT)(tmp); \
    lsrc[2] = (uint32 * RESTRICT)(tmp+1); \
    m[4] = PACK16LSB(lsrc[1][0], lsrc[0][0]); \
    m[5] = PACK16LSB(lsrc[3][0], lsrc[2][0]); \
    m[6] = PACK16MSB(lsrc[1][0], lsrc[0][0]); \
    m[7] = PACK16MSB(lsrc[3][0], lsrc[2][0]); \
    t1 = IFIR8UI(m[4], coef); \
    t2 = IFIR8UI(m[5], coef); \
    t3 = IFIR8UI(m[6], coef); \
    t4 = IFIR8UI(m[7], coef); \
    t1 = (PACK16LSB(t2,t1)+ADD_COEF)>>SHIFT_COEF; \
    t3 = (PACK16LSB(t4,t3)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[0]) = MERGEDUAL16LSB(t3,t1); \
    if (h==4) goto NEXT_ITER2##A; \
    lsrc[4] = (uint32 * RESTRICT)(tmp+4); \
    lsrc[6] = (uint32 * RESTRICT)(tmp+5); \
    m[0] = PACK16LSB(lsrc[5][0], lsrc[4][0]); \
    m[1] = PACK16LSB(lsrc[7][0], lsrc[6][0]); \
    m[2] = PACK16MSB(lsrc[5][0], lsrc[4][0]); \
    m[3] = PACK16MSB(lsrc[7][0], lsrc[6][0]); \
    t5 = IFIR8UI(m[0], coef); \
    t6 = IFIR8UI(m[1], coef); \
    t7 = IFIR8UI(m[2], coef); \
    t8 = IFIR8UI(m[3], coef); \
    t5 = (PACK16LSB(t6,t5)+ADD_COEF)>>SHIFT_COEF; \
    t7 = (PACK16LSB(t8,t7)+ADD_COEF)>>SHIFT_COEF; \
    CONVUINTXTOUINT32(dst[4]) = MERGEDUAL16LSB(t7,t5); \
NEXT_ITER2##A: \
    dst += dst_stride;
#endif

#ifdef _UAMEM_ACCESS_
#define RV_C_HQVQ_8xn(pSrc, pDst, h, v, src_stride, dst_stride, coef, rounding, shift) \
    uint32 s[16]; \
    int t1, t2, t3, t4, t5, t6, t7, t8; \
    const uint32 *RESTRICT lsrc[8]; \
    int stride_mul2 = src_stride<<1; \
    int i=v; \
    \
    lsrc[0] = (uint32 * RESTRICT)pSrc; \
    lsrc[2] = (uint32 * RESTRICT)(pSrc+1); \
    lsrc[4] = (uint32 * RESTRICT)(pSrc+4); \
    lsrc[6] = (uint32 * RESTRICT)(pSrc+5); \
    do { \
        /*FILTER_BILINEAR_8_SHARE(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift, h, i);*/ \
        FILTER_BILINEAR_8(lsrc, pSrc, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
        i -= 2; \
    } while (i>0);
#else
#define RV_C_HQVQ_8xn(pSrc, pDst, h, v, src_stride, dst_stride, coef, rounding, shift) \
    uint32 s[16]; \
    int t1, t2, t3, t4, t5, t6, t7, t8; \
    uchar * RESTRICT tmp; \
    \
    s[0] = PACKBYTES(pSrc[1], pSrc[0]); \
    s[2] = PACKBYTES(pSrc[2], pSrc[1]); \
    s[4] = PACKBYTES(pSrc[3], pSrc[2]); \
    s[6] = PACKBYTES(pSrc[4], pSrc[3]); \
    s[8] = PACKBYTES(pSrc[5], pSrc[4]); \
    s[10] = PACKBYTES(pSrc[6], pSrc[5]); \
    s[12] = PACKBYTES(pSrc[7], pSrc[6]); \
    s[14] = PACKBYTES(pSrc[8], pSrc[7]); \
    tmp = pSrc+src_stride; \
    FILTER_BILINEAR_8(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    FILTER_BILINEAR_8(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    FILTER_BILINEAR_8(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift); \
    FILTER_BILINEAR_8(tmp, pDst, coef, src_stride, dst_stride, s, rounding, shift);
#endif

/******************************************************************************************/
#if 1
#define FILTER_C_H0V0_xy(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, h, v, X) \
{ \
    int dy;\
    /*int v = PACK16MSB(0, xy); */\
    int lStride = src_stride >> 2;\
    const uint32 *RESTRICT lSrc = (uint32 *) pSrc;                     \
    uint32 *RESTRICT lDst = (uint32 *) pDst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) pSrc+lStride;            \
    uint32 *RESTRICT lDst2 = (uint32 *) pDst+lStride;            \
    \
    const uint32 *RESTRICT lSrc_v = (uint32 *) pSrc2;                     \
    uint32 *RESTRICT lDst_v = (uint32 *) pDst2;                     \
    const uint32 *RESTRICT lSrc2_v = (uint32 *) pSrc2+lStride;                     \
    uint32 *RESTRICT lDst2_v = (uint32 *) pDst2+lStride;                     \
    dy = 0; \
    do { \
        dy+=2; \
        lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
        lDst2[0] = FUNSHIFT##X(lSrc2[1], lSrc2[0]);                      \
        lDst_v[0] = FUNSHIFT##X(lSrc_v[1], lSrc_v[0]);                      \
        lDst2_v[0] = FUNSHIFT##X(lSrc2_v[1], lSrc2_v[0]);                      \
        if (h == 8) { \
            lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
            lDst2[1] = FUNSHIFT##X(lSrc2[2], lSrc2[1]);                      \
            lDst_v[1] = FUNSHIFT##X(lSrc_v[2], lSrc_v[1]);                      \
            lDst2_v[1] = FUNSHIFT##X(lSrc2_v[2], lSrc2_v[1]);                      \
        } \
        lSrc += FACTOR_2(lStride);                             \
        lDst += FACTOR_2(lStride); \
        lSrc2 += FACTOR_2(lStride);                             \
        lDst2 += FACTOR_2(lStride); \
        lSrc_v += FACTOR_2(lStride);                             \
        lDst_v += FACTOR_2(lStride); \
        lSrc2_v += FACTOR_2(lStride);                             \
        lDst2_v += FACTOR_2(lStride); \
    } while (dy != v);\
}
#else
#define FILTER_C_H0V0_xy(pSrc, pDst, pSrc2, pDst2, src_stride, dst_stride, h, v, X) \
{ \
    int dy;\
    int lStride = src_stride >> 2;\
    const uint32 *RESTRICT lSrc = (uint32 *) pSrc;                     \
    uint32 *RESTRICT lDst = (uint32 *) pDst;                     \
    \
    const uint32 *RESTRICT lSrc_v = (uint32 *) pSrc2;                     \
    uint32 *RESTRICT lDst_v = (uint32 *) pDst2;                     \
    dy = 0; \
    do { \
        dy+=1; \
        lDst[0] = FUNSHIFT##X(lSrc[1], lSrc[0]);                      \
        lDst_v[0] = FUNSHIFT##X(lSrc_v[1], lSrc_v[0]);                      \
        if (h == 8) { \
            lDst[1] = FUNSHIFT##X(lSrc[2], lSrc[1]);                      \
            lDst_v[1] = FUNSHIFT##X(lSrc_v[2], lSrc_v[1]);                      \
        } \
        lSrc += lStride;                             \
        lDst += lStride; \
        lSrc_v += lStride;                             \
        lDst_v += lStride; \
    } while (dy != v);\
}
#endif

#define FILTER_C_H1V0_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]); \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]); \
        t4  = MERGEODD(t0,t0);             \
        t5  = MERGEODD(t1,t1);             \
        t8 = BILINEAR1(t4,t0); \
        t9 = BILINEAR1(t5,t1); \
        lDst[0] = MERGEODD(t9,t8);\
        \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]); \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]); \
        t4  = MERGEODD(t0,t0);            \
        t5  = MERGEODD(t1,t1);            \
        t8 = BILINEAR1(t4,t0); \
        t9 = BILINEAR1(t5,t1); \
        lDst2[0] = MERGEODD(t9,t8);\
        \
        if (h == 8) { \
            t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
            t6  = MERGEODD(t2,t2);             \
            t7  = MERGEODD(t3,t3);             \
            t10 = BILINEAR1(t6,t2); \
            t11 = BILINEAR1(t7,t3); \
            lDst[1] = MERGEODD(t11,t10);\
            \
            t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
            t6  = MERGEODD(t2,t2);            \
            t7  = MERGEODD(t3,t3);            \
            t10 = BILINEAR1(t6,t2); \
            t11 = BILINEAR1(t7,t3); \
            lDst2[1] = MERGEODD(t11,t10);\
        } \
        lSrc += lStride; \
        lDst += dStride; \
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < v);  \
}

#define FILTER_C_H3V0_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2; \
    int dStride = dst_stride >> 2; \
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11; \
    const uint32 *RESTRICT lSrc = (uint32 *) src; \
    uint32 *RESTRICT lDst = (uint32 *) dst; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2; \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2; \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        t4  = MERGEODD(t1,t1);                      \
        t5  = MERGEODD((t1>>8),(t1>>8));            \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        lDst[0] = MERGEODD(t9,t8); \
        \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        t4  = MERGEODD(t1,t1);                     \
        t5  = MERGEODD((t1>>8),(t1>>8));           \
        t8  = BILINEAR1(t4,t0);\
        t9  = BILINEAR1(t5,t1);\
        lDst2[0] = MERGEODD(t9,t8); \
        \
        if (h == 8) { \
            t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
            t6  = MERGEODD(t3,t3);                      \
            t7  = MERGEODD((t3>>8),(t3>>8));            \
            t10 = BILINEAR1(t6,t2);\
            t11 = BILINEAR1(t7,t3);\
            lDst[1] = MERGEODD(t11,t10);\
            t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
            t6  = MERGEODD(t3,t3);                     \
            t7  = MERGEODD((t3>>8),(t3>>8));           \
            t10 = BILINEAR1(t6,t2);\
            t11 = BILINEAR1(t7,t3);\
            lDst2[1] = MERGEODD(t11,t10);\
        } \
        lSrc += lStride; \
        lDst += dStride; \
        lSrc2 += lStride; \
        lDst2 += dStride; \
    } while (dy < v); \
}

#define FILTER_C_H0V1_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    if (h == 8) { \
        t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        x1 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    } \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t4  = MERGELSB(t0,t0);             /*1  1 0  0   */          \
        t5  = MERGELSB(t2,t0);             /*v1 1 v0 0    */        \
        t6  = MERGEMSB(t0,t0);             /*3  3 2  2    */        \
        t7  = MERGEMSB(t2,t0);             /*v3 3 v2 2     */       \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        \
        lSrc2  += lStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        x4  = MERGELSB(x0,x0);             /*1  1 0  0   */          \
        x5  = MERGELSB(x2,x0);             /*v1 1 v0 0    */        \
        x6  = MERGEMSB(x0,x0);             /*3  3 2  2    */        \
        x7  = MERGEMSB(x2,x0);             /*v3 3 v2 2     */       \
        x12 = BILINEAR2(x5,x4);\
        x13 = BILINEAR2(x7,x6);\
        lDst2[0] = MERGEDUAL16LSB(x13,x12);\
        x0 = x2;\
        \
        if (h == 8) { \
            t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t8  = MERGELSB(t1,t1);             /*5  5 4  4     */         \
            t9  = MERGELSB(t3,t1);             /*v5 5 v5 4    */        \
            t10 = MERGEMSB(t1,t1);             /*7  7 6  6     */       \
            t11 = MERGEMSB(t3,t1);             /*v7 7 v6 6     */   \
            t14 = BILINEAR2(t9,t8);\
            t15 = BILINEAR2(t11,t10);\
            lDst[1] = MERGEDUAL16LSB(t15,t14);\
            t1 = t3;\
            \
            x3 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            x8  = MERGELSB(x1,x1);             /*5  5 4  4     */         \
            x9  = MERGELSB(x3,x1);             /*v5 5 v5 4    */        \
            x10 = MERGEMSB(x1,x1);             /*7  7 6  6     */       \
            x11 = MERGEMSB(x3,x1);             /*v7 7 v6 6     */   \
            x14 = BILINEAR2(x9,x8);\
            x15 = BILINEAR2(x11,x10);\
            lDst2[1] = MERGEDUAL16LSB(x15,x14);\
            x1 = x3;\
        } \
        lDst += dStride; \
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H0V3_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;        \
    uint32 x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    x0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    if (h == 8) { \
        t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        x1 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    } \
    dy = 0; \
    do { \
        dy++; \
        lSrc  += lStride; \
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t4  = MERGELSB(t2,t0);            \
        t5  = MERGELSB(t2,t2);            \
        t6  = MERGEMSB(t2,t0);            \
        t7  = MERGEMSB(t2,t2);            \
        t12 = BILINEAR2(t5,t4);\
        t13 = BILINEAR2(t7,t6);\
        lDst[0] = MERGEDUAL16LSB(t13,t12);\
        t0 = t2;\
        \
        lSrc2  += lStride; \
        x2 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        x4  = MERGELSB(x2,x0);           \
        x5  = MERGELSB(x2,x2);           \
        x6  = MERGEMSB(x2,x0);           \
        x7  = MERGEMSB(x2,x2);           \
        x12 = BILINEAR2(x5,x4);\
        x13 = BILINEAR2(x7,x6);\
        lDst2[0] = MERGEDUAL16LSB(x13,x12);\
        x0 = x2;\
        \
        if (h == 8) { \
            t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t8  = MERGELSB(t3,t1);          \
            t9  = MERGELSB(t3,t3);          \
            t10 = MERGEMSB(t3,t1);          \
            t11 = MERGEMSB(t3,t3);          \
            t14 = BILINEAR2(t9,t8);\
            t15 = BILINEAR2(t11,t10);\
            lDst[1] = MERGEDUAL16LSB(t15,t14);\
            t1 = t3;\
            \
            x3 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            x8  = MERGELSB(x3,x1);           \
            x9  = MERGELSB(x3,x3);           \
            x10 = MERGEMSB(x3,x1);           \
            x11 = MERGEMSB(x3,x3);           \
            x14 = BILINEAR2(x9,x8);\
            x15 = BILINEAR2(x11,x10);\
            lDst2[1] = MERGEDUAL16LSB(x15,x14);\
            x1 = x3;\
        } \
        lDst += dStride; \
        lDst2 += dStride; \
    } while (dy < v); \
}
#ifdef _AG_S32_
#define FILTER_C_H2V0_xy(src, dst, src2, dst2, Stride, dst_stride, h, v, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    /*int v = PACK16MSB(0, xy); */\
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG(t0,t1); \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        lDst2[0] = QUADAVG(t0,t1); \
        \
        if (h == 8) { \
            t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
            lDst[1] = QUADAVG(t2,t3); \
            t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
            lDst2[1] = QUADAVG(t2,t3); \
        } \
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
        lSrc2  = lSrc2 + lStride;                             \
        lDst2 += dStride; \
    } while (dy < v);\
}
#define FILTER_C_H0V2_xy(src, dst, src2, dst2, Stride, dst_stride, h, v, A1) \
{ \
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7;\
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t4 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    if (h == 8) { \
        t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t5 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    } \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        lSrc2 += lStride;\
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG0(t0,t2); \
        t0=t2;\
        t6 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        lDst2[0] = QUADAVG0(t4,t6); \
        t4=t6;\
        \
        if (h == 8) { \
            t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            lDst[1] = QUADAVG0(t1,t3); \
            t1=t3;\
            \
            t7 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            lDst2[1] = QUADAVG0(t5,t7); \
            t5=t7;\
        } \
        lDst += dStride; \
        lDst2 += dStride; \
    } while (dy < v);\
}
#else
#define FILTER_C_H2V0_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1, A2) \
{\
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3;        \
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    dy = 0; \
    do { \
        dy++; \
        t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        t1 = FUNSHIFT##A2(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG(t0,t1); \
        t0 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        t1 = FUNSHIFT##A2(lSrc2[1], lSrc2[0]);                      \
        lDst2[0] = QUADAVG(t0,t1); \
        \
        if (h == 8) { \
            t2 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            t3 = FUNSHIFT##A2(lSrc[2], lSrc[1]);                      \
            lDst[1] = QUADAVG(t2,t3); \
            t2 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            t3 = FUNSHIFT##A2(lSrc2[2], lSrc2[1]);                      \
            lDst2[1] = QUADAVG(t2,t3); \
        } \
        lSrc  = lSrc + lStride;                             \
        lDst += dStride; \
        lSrc2  = lSrc2 + lStride;                             \
        lDst2 += dStride; \
    } while (dy < v);\
}

#define FILTER_C_H0V2_xy(src, dst, src2, dst2, Stride, dst_stride, xy, A1) \
{ \
    int dy;\
    int lStride = Stride >> 2;\
    int dStride = dst_stride >> 2;\
    uint32 t0, t1, t2, t3, t4, t5, t6, t7;\
    const uint32 *RESTRICT lSrc = (uint32 *) src;                     \
    uint32 *RESTRICT lDst = (uint32 *) dst;                     \
    const uint32 *RESTRICT lSrc2 = (uint32 *) src2;                     \
    uint32 *RESTRICT lDst2 = (uint32 *) dst2;                     \
    int h = PACK16LSB(0, xy); \
    /*int v = PACK16MSB(0, xy); */\
    int v = h; \
    t0 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
    t4 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
    if (h == 8) { \
        t1 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
        t5 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
    } \
    dy = 0; \
    do { \
        dy++; \
        lSrc += lStride;\
        lSrc2 += lStride;\
        t2 = FUNSHIFT##A1(lSrc[1], lSrc[0]);                      \
        lDst[0] = QUADAVG0(t0,t2); \
        t0=t2;\
        t6 = FUNSHIFT##A1(lSrc2[1], lSrc2[0]);                      \
        lDst2[0] = QUADAVG0(t4,t6); \
        t4=t6;\
        \
        if (h == 8) { \
            t3 = FUNSHIFT##A1(lSrc[2], lSrc[1]);                      \
            lDst[1] = QUADAVG0(t1,t3); \
            t1=t3;\
            \
            t7 = FUNSHIFT##A1(lSrc2[2], lSrc2[1]);                      \
            lDst2[1] = QUADAVG0(t5,t7); \
            t5=t7;\
        } \
        lDst += dStride; \
        lDst2 += dStride; \
    } while (dy < v);\
}
#endif

/*********************************************************************************************************/
#define wmv3_Bilinear_QF8(dst0, dst1, s01, s23, s45, s67, t01, t23, t45, t67, shift) \
    tt1 = s01 + t01 + p_rounding;\
    tt1 = DUALASR(tt1, shift);\
    tt2 = s23 + t23 + p_rounding;\
    tt2 = DUALASR(tt2, shift);\
    dst0 = MERGEDUAL16LSB(tt2, tt1);\
    tt3 = s45 + t45 + p_rounding;\
    tt3 = DUALASR(tt3, shift);\
    tt4 = s67 + t67 + p_rounding;\
    tt4 = DUALASR(tt4, shift);\
    dst1 = MERGEDUAL16LSB(tt4, tt3);

#ifdef _UAMEM_ACCESS_
#define wmv3_UV_QF0(Src, Dst, Src2, Dst2, rnd) \
    int32  p_rounding, tt1, tt2, tt3, tt4;\
    uint32 sleft, right;\
    int y;\
    uint32 * RESTRICT lDst;\
    uint32 * RESTRICT lDst2;\
    const uint32 *RESTRICT lSrc = (uint32 *) Src; \
    const uint32 *RESTRICT lSrc2 = (uint32 *) Src2; \
    lDst = (uint32 *) Dst;\
    lDst2 = (uint32 *) Dst2;\
    p_rounding = rnd;\
    p_rounding = PACK16LSB(p_rounding, p_rounding);
#else
#define wmv3_UV_QF0(Src, Dst, Src2, Dst2, rnd) \
    int32  p_rounding, tt1, tt2, tt3, tt4;\
    uint32 sleft, right;\
    int y;\
    uint32 * RESTRICT lDst;\
    uint32 * RESTRICT lDst2;\
    uchar * RESTRICT pSrc;\
    uchar * RESTRICT pSrc2;\
    pSrc = Src;\
    pSrc2 = Src2;\
    lDst = (uint32 *) Dst;\
    lDst2 = (uint32 *) Dst2;\
    p_rounding = rnd;\
    p_rounding = PACK16LSB(p_rounding, p_rounding);
#endif

#ifdef _UAMEM_ACCESS_
#define wmv3_HxVx_8_n(Src, Dst, Src2, Dst2, Stride, rounding, shift, f1, f2, f3, f4, v) \
{ \
    int lStride = Stride >> 2;   \
    int v0, v1, v2, v3, v4, v5, v6, v7, v8;   \
    int u01, u23, u45, u67;   \
    int v01, v23, v45, v67;   \
    int w01, w23, w45, w67;   \
    int a0, a1, a2, a3, a4, a5, a6, a7, a8;   \
    int b01, b23, b45, b67;   \
    int a01, a23, a45, a67;   \
    int c01, c23, c45, c67;   \
    wmv3_UV_QF0(Src, Dst, Src2, Dst2, rounding); \
    \
    /*v01 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc[0])));   \
    v23 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])));   \
    v45 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc[1])));   \
    v67 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc[2], lSrc[1])));   \
    \
    a01 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc2[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])));   \
    a23 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc2[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])));   \
    a45 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc2[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc2[1])));   \
    a67 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc2[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc2[2], lSrc2[1])));   */\
    \
    v01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[0])), f2);   \
    v23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])), f2);   \
    v45 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[1])), f2);   \
    v67 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[2], lSrc[1])), f2);   \
    \
    a01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])), f2);   \
    a23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])), f2);   \
    a45 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[1])), f2);   \
    a67 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[2], lSrc2[1])), f2);   \
    \
    y = 0; \
    do { \
        lSrc += lStride;   \
        /*u01 = FACTOR_##f3(v01);   \
        u23 = FACTOR_##f3(v23);   \
        u45 = FACTOR_##f3(v45);   \
        u67 = FACTOR_##f3(v67);   \
        v01 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc[0])));   \
        v23 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])));   \
        v45 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc[1])));   \
        v67 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc[2], lSrc[1])));   \
        w01 = FACTOR_##f4(v01);   \
        w23 = FACTOR_##f4(v23);   \
        w45 = FACTOR_##f4(v45);   \
        w67 = FACTOR_##f4(v67);   */\
        u01 = DSPIDUALMUL(v01, f3);   \
        u23 = DSPIDUALMUL(v23, f3);   \
        u45 = DSPIDUALMUL(v45, f3);   \
        u67 = DSPIDUALMUL(v67, f3);   \
        v01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[0])), f2);   \
        v23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])), f2);   \
        v45 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[1])), f2);   \
        v67 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[2], lSrc[1])), f2);   \
        w01 = DSPIDUALMUL(v01, f4);   \
        w23 = DSPIDUALMUL(v23, f4);   \
        w45 = DSPIDUALMUL(v45, f4);   \
        w67 = DSPIDUALMUL(v67, f4);   \
        wmv3_Bilinear_QF8(lDst[0], lDst[1], u01, u23, u45, u67, w01, w23, w45, w67, shift);   \
        lDst += lStride;   \
        \
        lSrc2 += lStride;   \
        /*b01 = FACTOR_##f3(a01);   \
        b23 = FACTOR_##f3(a23);   \
        b45 = FACTOR_##f3(a45);   \
        b67 = FACTOR_##f3(a67);   \
        a01 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc2[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])));   \
        a23 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc2[0]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])));   \
        a45 = FACTOR_##f1(MERGELSB(0, FUNSHIFT4(0, lSrc2[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT3(0, lSrc2[1])));   \
        a67 = FACTOR_##f1(MERGELSB(0, FUNSHIFT2(0, lSrc2[1]))) +  FACTOR_##f2(MERGELSB(0, FUNSHIFT1(lSrc2[2], lSrc2[1])));   \
        c01 = FACTOR_##f4(a01);   \
        c23 = FACTOR_##f4(a23);   \
        c45 = FACTOR_##f4(a45);   \
        c67 = FACTOR_##f4(a67);   */\
        b01 = DSPIDUALMUL(a01, f3);   \
        b23 = DSPIDUALMUL(a23, f3);   \
        b45 = DSPIDUALMUL(a45, f3);   \
        b67 = DSPIDUALMUL(a67, f3);   \
        a01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])), f2);   \
        a23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])), f2);   \
        a45 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[1])), f2);   \
        a67 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[1])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[2], lSrc2[1])), f2);   \
        c01 = DSPIDUALMUL(a01, f4);   \
        c23 = DSPIDUALMUL(a23, f4);   \
        c45 = DSPIDUALMUL(a45, f4);   \
        c67 = DSPIDUALMUL(a67, f4);   \
        wmv3_Bilinear_QF8(lDst2[0], lDst2[1], b01, b23, b45, b67, c01, c23, c45, c67, shift);   \
        lDst2 += lStride;   \
        y++; \
        if (y == v) \
            break; \
    } while (y < v); \
}
#else
#define wmv3_HxVx_8_n(Src, Dst, Src2, Dst2, Stride, rounding, shift, f1, f2, f3, f4, v) \
{ \
    int lStride = Stride >> 2;   \
    int v0, v1, v2, v3, v4, v5, v6, v7, v8;   \
    int u01, u23, u45, u67;   \
    int v01, v23, v45, v67;   \
    int w01, w23, w45, w67;   \
    int a0, a1, a2, a3, a4, a5, a6, a7, a8;   \
    int b01, b23, b45, b67;   \
    int a01, a23, a45, a67;   \
    int c01, c23, c45, c67;   \
    wmv3_UV_QF0(Src, Dst, Src2, Dst2, rounding); \
    \
    v0 = pSrc[0];   \
    v1 = pSrc[1];   \
    v2 = pSrc[2];   \
    v3 = pSrc[3];   \
    v4 = pSrc[4];   \
    v5 = pSrc[5];   \
    v6 = pSrc[6];   \
    v7 = pSrc[7];   \
    v8 = pSrc[8];   \
    /*v01 = FACTOR_##f1(PACK16LSB(v1, v0)) +  FACTOR_##f2(PACK16LSB(v2, v1));   \
    v23 = FACTOR_##f1(PACK16LSB(v3, v2)) +  FACTOR_##f2(PACK16LSB(v4, v3));   \
    v45 = FACTOR_##f1(PACK16LSB(v5, v4)) +  FACTOR_##f2(PACK16LSB(v6, v5));   \
    v67 = FACTOR_##f1(PACK16LSB(v7, v6)) +  FACTOR_##f2(PACK16LSB(v8, v7));   */\
    v01 = DSPIDUALMUL(PACK16LSB(v1, v0), f1) +  DSPIDUALMUL(PACK16LSB(v2, v1), f2);   \
    v23 = DSPIDUALMUL(PACK16LSB(v3, v2), f1) +  DSPIDUALMUL(PACK16LSB(v4, v3), f2);   \
    v45 = DSPIDUALMUL(PACK16LSB(v5, v4), f1) +  DSPIDUALMUL(PACK16LSB(v6, v5), f2);   \
    v67 = DSPIDUALMUL(PACK16LSB(v7, v6), f1) +  DSPIDUALMUL(PACK16LSB(v8, v7), f2);   \
    \
    a0 = pSrc2[0];   \
    a1 = pSrc2[1];   \
    a2 = pSrc2[2];   \
    a3 = pSrc2[3];   \
    a4 = pSrc2[4];   \
    a5 = pSrc2[5];   \
    a6 = pSrc2[6];   \
    a7 = pSrc2[7];   \
    a8 = pSrc2[8];   \
    /*a01 = FACTOR_##f1(PACK16LSB(a1, a0)) + FACTOR_##f2(PACK16LSB(a2, a1));   \
    a23 = FACTOR_##f1(PACK16LSB(a3, a2)) + FACTOR_##f2(PACK16LSB(a4, a3));   \
    a45 = FACTOR_##f1(PACK16LSB(a5, a4)) + FACTOR_##f2(PACK16LSB(a6, a5));   \
    a67 = FACTOR_##f1(PACK16LSB(a7, a6)) + FACTOR_##f2(PACK16LSB(a8, a7));   */\
    a01 = DSPIDUALMUL(PACK16LSB(a1, a0), f1) +  DSPIDUALMUL(PACK16LSB(a2, a1), f2);   \
    a23 = DSPIDUALMUL(PACK16LSB(a3, a2), f1) +  DSPIDUALMUL(PACK16LSB(a4, a3), f2);   \
    a45 = DSPIDUALMUL(PACK16LSB(a5, a4), f1) +  DSPIDUALMUL(PACK16LSB(a6, a5), f2);   \
    a67 = DSPIDUALMUL(PACK16LSB(a7, a6), f1) +  DSPIDUALMUL(PACK16LSB(a8, a7), f2);   \
    \
    y = 0; \
    do { \
        pSrc += Stride;   \
        /*u01 = FACTOR_##f3(v01);   \
        u23 = FACTOR_##f3(v23);   \
        u45 = FACTOR_##f3(v45);   \
        u67 = FACTOR_##f3(v67);   */\
        u01 = DSPIDUALMUL(v01, f3);   \
        u23 = DSPIDUALMUL(v23, f3);   \
        u45 = DSPIDUALMUL(v45, f3);   \
        u67 = DSPIDUALMUL(v67, f3);   \
        v0 = pSrc[0];   \
        v1 = pSrc[1];   \
        v2 = pSrc[2];   \
        v3 = pSrc[3];   \
        v4 = pSrc[4];   \
        v5 = pSrc[5];   \
        v6 = pSrc[6];   \
        v7 = pSrc[7];   \
        v8 = pSrc[8];   \
        /*v01 = FACTOR_##f1(PACK16LSB(v1, v0)) +  FACTOR_##f2(PACK16LSB(v2, v1));   \
        v23 = FACTOR_##f1(PACK16LSB(v3, v2)) +  FACTOR_##f2(PACK16LSB(v4, v3));   \
        v45 = FACTOR_##f1(PACK16LSB(v5, v4)) +  FACTOR_##f2(PACK16LSB(v6, v5));   \
        v67 = FACTOR_##f1(PACK16LSB(v7, v6)) +  FACTOR_##f2(PACK16LSB(v8, v7));   \
        w01 = FACTOR_##f4(v01);   \
        w23 = FACTOR_##f4(v23);   \
        w45 = FACTOR_##f4(v45);   \
        w67 = FACTOR_##f4(v67);   */\
        v01 = DSPIDUALMUL(PACK16LSB(v1, v0), f1) +  DSPIDUALMUL(PACK16LSB(v2, v1), f2);   \
        v23 = DSPIDUALMUL(PACK16LSB(v3, v2), f1) +  DSPIDUALMUL(PACK16LSB(v4, v3), f2);   \
        v45 = DSPIDUALMUL(PACK16LSB(v5, v4), f1) +  DSPIDUALMUL(PACK16LSB(v6, v5), f2);   \
        v67 = DSPIDUALMUL(PACK16LSB(v7, v6), f1) +  DSPIDUALMUL(PACK16LSB(v8, v7), f2);   \
        w01 = DSPIDUALMUL(v01, f4);   \
        w23 = DSPIDUALMUL(v23, f4);   \
        w45 = DSPIDUALMUL(v45, f4);   \
        w67 = DSPIDUALMUL(v67, f4);   \
        wmv3_Bilinear_QF8(lDst[0], lDst[1], u01, u23, u45, u67, w01, w23, w45, w67, shift);   \
        lDst += lStride;   \
        \
        pSrc2 += Stride;   \
        /*b01 = FACTOR_##f3(a01);   \
        b23 = FACTOR_##f3(a23);   \
        b45 = FACTOR_##f3(a45);   \
        b67 = FACTOR_##f3(a67);   */\
        b01 = DSPIDUALMUL(a01, f3);   \
        b23 = DSPIDUALMUL(a23, f3);   \
        b45 = DSPIDUALMUL(a45, f3);   \
        b67 = DSPIDUALMUL(a67, f3);   \
        a0 = pSrc2[0];   \
        a1 = pSrc2[1];   \
        a2 = pSrc2[2];   \
        a3 = pSrc2[3];   \
        a4 = pSrc2[4];   \
        a5 = pSrc2[5];   \
        a6 = pSrc2[6];   \
        a7 = pSrc2[7];   \
        a8 = pSrc2[8];   \
        /*a01 = FACTOR_##f1(PACK16LSB(a1, a0)) + FACTOR_##f2(PACK16LSB(a2, a1));   \
        a23 = FACTOR_##f1(PACK16LSB(a3, a2)) + FACTOR_##f2(PACK16LSB(a4, a3));   \
        a45 = FACTOR_##f1(PACK16LSB(a5, a4)) + FACTOR_##f2(PACK16LSB(a6, a5));   \
        a67 = FACTOR_##f1(PACK16LSB(a7, a6)) + FACTOR_##f2(PACK16LSB(a8, a7));   \
        c01 = FACTOR_##f4(a01);   \
        c23 = FACTOR_##f4(a23);   \
        c45 = FACTOR_##f4(a45);   \
        c67 = FACTOR_##f4(a67);   */\
        a01 = DSPIDUALMUL(PACK16LSB(a1, a0), f1) + DSPIDUALMUL(PACK16LSB(a2, a1), f2);   \
        a23 = DSPIDUALMUL(PACK16LSB(a3, a2), f1) + DSPIDUALMUL(PACK16LSB(a4, a3), f2);   \
        a45 = DSPIDUALMUL(PACK16LSB(a5, a4), f1) + DSPIDUALMUL(PACK16LSB(a6, a5), f2);   \
        a67 = DSPIDUALMUL(PACK16LSB(a7, a6), f1) + DSPIDUALMUL(PACK16LSB(a8, a7), f2);   \
        c01 = DSPIDUALMUL(a01, f4);   \
        c23 = DSPIDUALMUL(a23, f4);   \
        c45 = DSPIDUALMUL(a45, f4);   \
        c67 = DSPIDUALMUL(a67, f4);   \
        wmv3_Bilinear_QF8(lDst2[0], lDst2[1], b01, b23, b45, b67, c01, c23, c45, c67, shift);   \
        lDst2 += lStride;   \
        y++; \
        if (y == v) \
        break; \
    } while (y < v); \
}
#endif

#define wmv3_Bilinear_QF4(dst0, s01, s23, t01, t23, shift) \
    tt1 = s01 + t01 + p_rounding;\
    tt1 = DUALASR(tt1, shift);\
    tt2 = s23 + t23 + p_rounding;\
    tt2 = DUALASR(tt2, shift);\
    dst0 = MERGEDUAL16LSB(tt2, tt1);

#ifdef _UAMEM_ACCESS_
#define wmv3_HxVx_4_n(Src, Dst, Src2, Dst2, Stride, rounding, shift, f1, f2, f3, f4, v) \
{ \
    int lStride = Stride >> 2;   \
    int u01, u23;   \
    int v01, v23;   \
    int w01, w23;   \
    int b01, b23;   \
    int a01, a23;   \
    int c01, c23;   \
    wmv3_UV_QF0(Src, Dst, Src2, Dst2, rounding); \
    \
    v01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[0])), f2);   \
    v23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])), f2);   \
    \
    a01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])), f2);   \
    a23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])), f2);   \
    \
    y = 0; \
    do { \
        lSrc += lStride;   \
        u01 = DSPIDUALMUL(v01, f3);   \
        u23 = DSPIDUALMUL(v23, f3);   \
        v01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc[0])), f2);   \
        v23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc[1], lSrc[0])), f2);   \
        w01 = DSPIDUALMUL(v01, f4);   \
        w23 = DSPIDUALMUL(v23, f4);   \
        wmv3_Bilinear_QF4(lDst[0], u01, u23, w01, w23, shift);   \
        lDst += lStride;   \
        \
        lSrc2 += lStride;   \
        b01 = DSPIDUALMUL(a01, f3);   \
        b23 = DSPIDUALMUL(a23, f3);   \
        a01 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT4(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT3(0, lSrc2[0])), f2);   \
        a23 = DSPIDUALMUL(MERGELSB(0, FUNSHIFT2(0, lSrc2[0])), f1) +  DSPIDUALMUL(MERGELSB(0, FUNSHIFT1(lSrc2[1], lSrc2[0])), f2);   \
        c01 = DSPIDUALMUL(a01, f4);   \
        c23 = DSPIDUALMUL(a23, f4);   \
        wmv3_Bilinear_QF4(lDst2[0], b01, b23, c01, c23, shift);   \
        lDst2 += lStride;   \
        y++; \
        if (y == v) \
            break; \
    } while (y < v); \
}
#else
#define wmv3_HxVx_4_n(Src, Dst, Src2, Dst2, Stride, rounding, shift, f1, f2, f3, f4, v) \
{ \
    int lStride = Stride >> 2;   \
    int v0, v1, v2, v3, v4;   \
    int u01, u23;   \
    int v01, v23;   \
    int w01, w23;   \
    int a0, a1, a2, a3, a4;   \
    int b01, b23;   \
    int a01, a23;   \
    int c01, c23;   \
    wmv3_UV_QF0(Src, Dst, Src2, Dst2, rounding); \
    \
    v0 = pSrc[0];   \
    v1 = pSrc[1];   \
    v2 = pSrc[2];   \
    v3 = pSrc[3];   \
    v4 = pSrc[4];   \
    v01 = DSPIDUALMUL(PACK16LSB(v1, v0), f1) +  DSPIDUALMUL(PACK16LSB(v2, v1), f2);   \
    v23 = DSPIDUALMUL(PACK16LSB(v3, v2), f1) +  DSPIDUALMUL(PACK16LSB(v4, v3), f2);   \
    \
    a0 = pSrc2[0];   \
    a1 = pSrc2[1];   \
    a2 = pSrc2[2];   \
    a3 = pSrc2[3];   \
    a4 = pSrc2[4];   \
    a01 = DSPIDUALMUL(PACK16LSB(a1, a0), f1) +  DSPIDUALMUL(PACK16LSB(a2, a1), f2);   \
    a23 = DSPIDUALMUL(PACK16LSB(a3, a2), f1) +  DSPIDUALMUL(PACK16LSB(a4, a3), f2);   \
    \
    y = 0; \
    do { \
        pSrc += Stride;   \
        u01 = DSPIDUALMUL(v01, f3);   \
        u23 = DSPIDUALMUL(v23, f3);   \
        v0 = pSrc[0];   \
        v1 = pSrc[1];   \
        v2 = pSrc[2];   \
        v3 = pSrc[3];   \
        v4 = pSrc[4];   \
        v01 = DSPIDUALMUL(PACK16LSB(v1, v0), f1) +  DSPIDUALMUL(PACK16LSB(v2, v1), f2);   \
        v23 = DSPIDUALMUL(PACK16LSB(v3, v2), f1) +  DSPIDUALMUL(PACK16LSB(v4, v3), f2);   \
        w01 = DSPIDUALMUL(v01, f4);   \
        w23 = DSPIDUALMUL(v23, f4);   \
        wmv3_Bilinear_QF4(lDst[0], u01, u23, w01, w23, shift);   \
        lDst += lStride;   \
        \
        pSrc2 += Stride;   \
        b01 = DSPIDUALMUL(a01, f3);   \
        b23 = DSPIDUALMUL(a23, f3);   \
        a0 = pSrc2[0];   \
        a1 = pSrc2[1];   \
        a2 = pSrc2[2];   \
        a3 = pSrc2[3];   \
        a4 = pSrc2[4];   \
        a01 = DSPIDUALMUL(PACK16LSB(a1, a0), f1) + DSPIDUALMUL(PACK16LSB(a2, a1), f2);   \
        a23 = DSPIDUALMUL(PACK16LSB(a3, a2), f1) + DSPIDUALMUL(PACK16LSB(a4, a3), f2);   \
        c01 = DSPIDUALMUL(a01, f4);   \
        c23 = DSPIDUALMUL(a23, f4);   \
        wmv3_Bilinear_QF4(lDst2[0], b01, b23, c01, c23, shift);   \
        lDst2 += lStride;   \
        y++; \
        if (y == v) \
        break; \
    } while (y < v); \
}
#endif
/***********************************************************************************/
#define avc_CopyBlkEFunc_4_1_BILINEAR(tmp, dst, stride, dst_stride, s, BILINEAR_X) \
    s[1] = CONVPUINTXTOUINT32(tmp); \
    s[3] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride; \
    s[0] = CONVPUINTXTOUINT32(tmp); \
    s[2] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride;

#define avc_CopyBlkEFunc_8_1_BILINEAR(tmp, dst, stride, dst_stride, s, BILINEAR_X) \
    s[1] = CONVPUINTXTOUINT32(tmp); \
    s[3] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    s[5] = CONVPUINTXTOUINT32(tmp+4); \
    s[7] = CONVPUINTXTOUINT32(tmp+5); \
    t1 = BILINEAR_X(s[4], s[5]); \
    t2 = BILINEAR_X(s[6], s[7]); \
    CONVUINTXTOUINT32(dst[4]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride; \
    s[0] = CONVPUINTXTOUINT32(tmp); \
    s[2] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    s[4] = CONVPUINTXTOUINT32(tmp+4); \
    s[6] = CONVPUINTXTOUINT32(tmp+5); \
    t1 = BILINEAR_X(s[4], s[5]); \
    t2 = BILINEAR_X(s[6], s[7]); \
    CONVUINTXTOUINT32(dst[4]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride; \
    s[1] = CONVPUINTXTOUINT32(tmp); \
    s[3] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    s[5] = CONVPUINTXTOUINT32(tmp+4); \
    s[7] = CONVPUINTXTOUINT32(tmp+5); \
    t1 = BILINEAR_X(s[4], s[5]); \
    t2 = BILINEAR_X(s[6], s[7]); \
    CONVUINTXTOUINT32(dst[4]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride; \
    s[0] = CONVPUINTXTOUINT32(tmp); \
    s[2] = CONVPUINTXTOUINT32(tmp+1); \
    t1 = BILINEAR_X(s[0], s[1]); \
    t2 = BILINEAR_X(s[2], s[3]); \
    CONVUINTXTOUINT32(dst[0]) = MERGEODD(t2, t1); \
    s[4] = CONVPUINTXTOUINT32(tmp+4); \
    s[6] = CONVPUINTXTOUINT32(tmp+5); \
    t1 = BILINEAR_X(s[4], s[5]); \
    t2 = BILINEAR_X(s[6], s[7]); \
    CONVUINTXTOUINT32(dst[4]) = MERGEODD(t2, t1); \
    dst += dst_stride; \
    tmp += stride;
#endif
