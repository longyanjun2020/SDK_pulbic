#ifndef AEON_SIMD_GCC_H
#define AEON_SIMD_GCC_H


#include <mmintrin.h>  // MMX
#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
// need SSE3 for _mm_abs_pi16
#include <tmmintrin.h> // Supplemental Streaming SIMD Extensions 3 (SSE3)
//#include <smmintrin.h> // Streaming SIMD Extensions 4 (SSE4)

#define EMPTY_EMMS _asm { emms }

extern __m64  v0,  v1,  v2,  v3,  v4,  v5,  v6,  v7,  v8,  v9, v10, v11, v12, v13, v14, v15;
extern __m64 v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v30, v31;

#define v00 v0
#define v01 v1
#define v02 v2
#define v03 v3
#define v04 v4
#define v05 v5
#define v06 v6
#define v07 v7
#define v08 v8
#define v09 v9

// little endian
#define ENDIAN_B8 0
#define ENDIAN_W4 0
//#define ENDIAN_B8 0x7
//#define ENDIAN_W4 0x3


/*
OP#
*/

#define OP1_ADD     MV_ADD //0
#define OP1_SUB     MV_SUB //1
#define OP1_ABS(a1, a2, a3)     MV_ABS(a1, a2) //2
#define OP1_SLL     MV_SLL //3
#define OP1_AND     MV_AND //4
#define OP1_OR      MV_OR  //5
#define OP1_XOR     MV_XOR //6

#define OP2_ADD     MV_ADD //0
#define OP2_SUB     MV_SUB //1
#define OP2_SRA     MV_SRA //2
#define OP2_SRL     MV_SRL //3

#define OP3_ADD     MV_ADD //0
#define OP3_SUB     MV_SUB //1

#define OP4_ADD     MV_ADD //0
#define OP4_SUB     MV_SUB //1

#define OP5_ADD     MV_ADD //0
#define OP5_SUB     MV_SUB //1
#define OP5_AVG     MV_AVGU //2
#define OP5_SRA     MV_SRA //3
#define OP5_SRL     MV_SRL //4
#define OP5_SLL     MV_SLL //5
#define OP5_AND     MV_AND //6
#define OP5_OR      MV_OR  //7
#define OP5_XOR     MV_XOR //8


#define MV_ADD(vD,vA,vB)    vD = _mm_add_pi16(vA, vB)
#define MV_ADDU(vD,vA,vB)   MV_ADD(vD,vA,vB)
#define MV_ADD_B(vD,vA,vB)  vD = _mm_add_pi8(vA, vB)
#define MV_ADDU_B(vD,vA,vB) MV_ADD_B(vD,vA,vB)

#define MV_SUB(vD,vA,vB)    vD = _mm_sub_pi16(vA, vB)
#define MV_SUBU(vD,vA,vB)   MV_SUB(vD,vA,vB)
#define MV_SUB_B(vD,vA,vB)  vD = _mm_sub_pi8(vA, vB)
#define MV_SUBU_B(vD,vA,vB) MV_SUB_B(vD,vA,vB)

#define MV_AVG(vD,vA,vB)    vD = _mm_set_pi16(((int16)_mm_extract_pi16(vA, 3)+(int16)_mm_extract_pi16(vB, 3)+1)>>1, \
                                              ((int16)_mm_extract_pi16(vA, 2)+(int16)_mm_extract_pi16(vB, 2)+1)>>1, \
                                              ((int16)_mm_extract_pi16(vA, 1)+(int16)_mm_extract_pi16(vB, 1)+1)>>1, \
                                              ((int16)_mm_extract_pi16(vA, 0)+(int16)_mm_extract_pi16(vB, 0)+1)>>1)
#define MV_AVGU(vD,vA,vB)   vD = _mm_set_pi16(((uint16)_mm_extract_pi16(vA, 3)+(uint16)_mm_extract_pi16(vB, 3)+1)>>1, \
                                              ((uint16)_mm_extract_pi16(vA, 2)+(uint16)_mm_extract_pi16(vB, 2)+1)>>1, \
                                              ((uint16)_mm_extract_pi16(vA, 1)+(uint16)_mm_extract_pi16(vB, 1)+1)>>1, \
                                              ((uint16)_mm_extract_pi16(vA, 0)+(uint16)_mm_extract_pi16(vB, 0)+1)>>1)
//#define MV_AVGU(vD,vA,vB)   vD = _mm_avg_pu16(vA, vB)

#define MV_AVG_B(vD,vA,vB) { \
    int a, b; \
    int x0, x1, x2, x3, x4, x5, x6, x7; \
    a = _mm_extract_pi16(vA, 0); \
    b = _mm_extract_pi16(vB, 0); \
    x0 = (((int8)(a&0xff)) + ((int8)(b&0xff)) + 1)>>1; \
    x1 = (((int8)((a>>8)&0xff)) + ((int8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 1); \
    b = _mm_extract_pi16(vB, 1); \
    x2 = (((int8)(a&0xff)) + ((int8)(b&0xff)) + 1)>>1; \
    x3 = (((int8)((a>>8)&0xff)) + ((int8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 2); \
    b = _mm_extract_pi16(vB, 2); \
    x4 = (((int8)(a&0xff)) + ((int8)(b&0xff)) + 1)>>1; \
    x5 = (((int8)((a>>8)&0xff)) + ((int8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 3); \
    b = _mm_extract_pi16(vB, 3); \
    x6 = (((int8)(a&0xff)) + ((int8)(b&0xff)) + 1)>>1; \
    x7 = (((int8)((a>>8)&0xff)) + ((int8)((b>>8)&0xff)) + 1)>>1; \
 \
    vD = _mm_set_pi8(x7, x6, x5, x4, x3, x2, x1, x0); \
}

#define MV_AVGU_B(vD,vA,vB) { \
    int a, b; \
    int x0, x1, x2, x3, x4, x5, x6, x7; \
    a = _mm_extract_pi16(vA, 0); \
    b = _mm_extract_pi16(vB, 0); \
    x0 = (((uint8)(a&0xff)) + ((uint8)(b&0xff)) + 1)>>1; \
    x1 = (((uint8)((a>>8)&0xff)) + ((uint8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 1); \
    b = _mm_extract_pi16(vB, 1); \
    x2 = (((uint8)(a&0xff)) + ((uint8)(b&0xff)) + 1)>>1; \
    x3 = (((uint8)((a>>8)&0xff)) + ((uint8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 2); \
    b = _mm_extract_pi16(vB, 2); \
    x4 = (((uint8)(a&0xff)) + ((uint8)(b&0xff)) + 1)>>1; \
    x5 = (((uint8)((a>>8)&0xff)) + ((uint8)((b>>8)&0xff)) + 1)>>1; \
    a = _mm_extract_pi16(vA, 3); \
    b = _mm_extract_pi16(vB, 3); \
    x6 = (((uint8)(a&0xff)) + ((uint8)(b&0xff)) + 1)>>1; \
    x7 = (((uint8)((a>>8)&0xff)) + ((uint8)((b>>8)&0xff)) + 1)>>1; \
    \
    vD = _mm_set_pi8(x7, x6, x5, x4, x3, x2, x1, x0); \
}

//#define MV_AVGU_B(vD,vA,vB) vD = _mm_avg_pu8(vA, vB)

//#define MV_ABS(vD,vA)  vD = _mm_adds_pu16(_mm_subs_pu16(vA, _mm_setzero_si64()), _mm_subs_pu16(_mm_setzero_si64(), vA))
#define MV_ABS(vD,vA)     vD = _mm_abs_pi16(vA)
#define MV_SRA(vD,vA,vB)  vD = _mm_set_pi16((int16)_mm_extract_pi16(vA, 3)>>IMIN(_mm_extract_pi16(vB, 3)&0xf, 8), \
                                            (int16)_mm_extract_pi16(vA, 2)>>IMIN(_mm_extract_pi16(vB, 2)&0xf, 8), \
                                            (int16)_mm_extract_pi16(vA, 1)>>IMIN(_mm_extract_pi16(vB, 1)&0xf, 8), \
                                            (int16)_mm_extract_pi16(vA, 0)>>IMIN(_mm_extract_pi16(vB, 0)&0xf, 8))

#define MV_SRL(vD,vA,vB)  vD = _mm_set_pi16((uint16)_mm_extract_pi16(vA, 3)>>IMIN(_mm_extract_pi16(vB, 3)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 2)>>IMIN(_mm_extract_pi16(vB, 2)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 1)>>IMIN(_mm_extract_pi16(vB, 1)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 0)>>IMIN(_mm_extract_pi16(vB, 0)&0xf, 8))

#define MV_SLL(vD,vA,vB)  vD = _mm_set_pi16((uint16)_mm_extract_pi16(vA, 3)<<IMIN(_mm_extract_pi16(vB, 3)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 2)<<IMIN(_mm_extract_pi16(vB, 2)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 1)<<IMIN(_mm_extract_pi16(vB, 1)&0xf, 8), \
                                            (uint16)_mm_extract_pi16(vA, 0)<<IMIN(_mm_extract_pi16(vB, 0)&0xf, 8))

#define MV_AND(vD,vA,vB)  vD = _mm_and_si64(vA, vB)
#define MV_OR(vD,vA,vB)   vD = _mm_or_si64(vA, vB)
#define MV_XOR(vD,vA,vB)  vD = _mm_xor_si64(vA, vB)

#define MV_SEQ(vD,vA,vB)  vD = _mm_cmpeq_pi16(vA, vB)
#define MV_SEQ_B(vD,vA,vB)  vD = _mm_cmpeq_pi8(vA, vB)

#define MV_SLT(vD,vA,vB)  vD = _mm_cmpgt_pi16(vB, vA)
//_mm_or_si64(_mm_cmpgt_pi16(vA, vB), _mm_cmpeq_pi16(vA, vB)); vD = _mm_xor_si64(vD, _mm_cmpeq_pi8(vA, vA))
#define MV_SLTU(vD,vA,vB) vD = _mm_xor_si64(_mm_cmpeq_pi16(_mm_subs_pu16(vB, vA), _mm_setzero_si64()), _mm_cmpeq_pi16(vA, vA))
//_mm_or_si64(_mm_cmpeq_pi16(_mm_subs_pu16(vB, vA), _mm_setzero_si64()), _mm_cmpeq_pi16(vA, vB))
//_mm_set_pi16(0-((uint16)_mm_extract_pi16(vA, 3)<(uint16)_mm_extract_pi16(vB, 3)), \
//                                            0-((uint16)_mm_extract_pi16(vA, 2)<(uint16)_mm_extract_pi16(vB, 2)), \
//                                            0-((uint16)_mm_extract_pi16(vA, 1)<(uint16)_mm_extract_pi16(vB, 1)), \
//                                            0-((uint16)_mm_extract_pi16(vA, 0)<(uint16)_mm_extract_pi16(vB, 0))) 
#define MV_SLT_B(vD,vA,vB)  vD = _mm_cmpgt_pi8(vB, vA)
//_mm_cmpeq_pi8(_mm_subs_pi8(vA, vB), _mm_setzero_si64())
// not supported
#define MV_SLTU_B(vD,vA,vB) vD = _mm_xor_si64(_mm_cmpeq_pi8(_mm_subs_pu8(vB, vA), _mm_setzero_si64()), _mm_cmpeq_pi16(vA, vA))
//_mm_or_si64(_mm_cmpeq_pi8(_mm_subs_pu8(vB, vA), _mm_setzero_si64()), _mm_cmpeq_pi8(vA, vB))
//_mm_subs_pu8(vA, vB)


// not supported
#define MV_TEXTNZ(vD,vA) vD = _mm_xor_si64(_mm_cmpeq_pi16(_mm_srli_pi16(vA, 8), _mm_setzero_si64()), _mm_cmpeq_pi8(vA, vA))
// not supported
#define MV_LZC(vD,vA) { \
    uint32 x0, x1, x2, x3; \
    uint32 idx0, idx1, idx2, idx3; \
    uint32 z0, z1, z2, z3; \
    uint32 zeroflag; \
    x0 = (uint16)_mm_extract_pi16(vA, 0); \
    idx0 = 0; \
    zeroflag = 1; \
    while(zeroflag && (idx0 < 17)){ \
        z0 = idx0; \
        zeroflag = ((x0>>(15-idx0)) == 0); \
        idx0++; \
    } \
    x1 = (uint16)_mm_extract_pi16(vA, 1); \
    idx1 = 0; \
    zeroflag = 1; \
    while(zeroflag && (idx1 < 17)){ \
        z1 = idx1; \
        zeroflag = ((x1>>(15-idx1)) == 0); \
        idx1++; \
    } \
    x2 = (uint16)_mm_extract_pi16(vA, 2); \
    idx2 = 0; \
    zeroflag = 1; \
    while(zeroflag && (idx2 < 17)){ \
        z2 = idx2; \
        zeroflag = ((x2>>(15-idx2)) == 0); \
        idx2++; \
    } \
    x3 = (uint16)_mm_extract_pi16(vA, 3); \
    idx3 = 0; \
    zeroflag = 1; \
    while(zeroflag && (idx3 < 17)){ \
        z3 = idx3; \
        zeroflag = ((x3>>(15-idx3)) == 0); \
        idx3++; \
    } \
    vD = _mm_set_pi16(z3, z2, z1, z0); \
}

#define MV_RAND(vD,vA)  vD = _mm_cvtsi32_si64(_mm_extract_pi16(vA, 0) & _mm_extract_pi16(vA, 1) & _mm_extract_pi16(vA, 2) & _mm_extract_pi16(vA, 3))
#define MV_ROR(vD,vA)   vD = _mm_cvtsi32_si64(_mm_extract_pi16(vA, 0) | _mm_extract_pi16(vA, 1) | _mm_extract_pi16(vA, 2) | _mm_extract_pi16(vA, 3))

#define MV_MIN(vD,vA,vB)  vD = _mm_min_pi16(vA, vB)
#define MV_MINU(vD,vA,vB) vD = _mm_set_pi16(UMIN((uint16)_mm_extract_pi16(vA, 3), (uint16)_mm_extract_pi16(vB, 3)), \
                                            UMIN((uint16)_mm_extract_pi16(vA, 2), (uint16)_mm_extract_pi16(vB, 2)), \
                                            UMIN((uint16)_mm_extract_pi16(vA, 1), (uint16)_mm_extract_pi16(vB, 1)), \
                                            UMIN((uint16)_mm_extract_pi16(vA, 0), (uint16)_mm_extract_pi16(vB, 0))) 
#define MV_MAX(vD,vA,vB)  vD = _mm_max_pi16(vA, vB)
#define MV_MAXU(vD,vA,vB) vD = _mm_set_pi16(UMAX((uint16)_mm_extract_pi16(vA, 3), (uint16)_mm_extract_pi16(vB, 3)), \
                                            UMAX((uint16)_mm_extract_pi16(vA, 2), (uint16)_mm_extract_pi16(vB, 2)), \
                                            UMAX((uint16)_mm_extract_pi16(vA, 1), (uint16)_mm_extract_pi16(vB, 1)), \
                                            UMAX((uint16)_mm_extract_pi16(vA, 0), (uint16)_mm_extract_pi16(vB, 0))) 

#define MV_CLIP3U(vD,vA,vB,vC)  MV_MAXU(vD,vA,vB); MV_MINU(vD,vC,vD)
#define MV_CLIP3(vD,vA,vB,vC)  vD = _mm_min_pi16(vC, _mm_max_pi16(vA, vB))
#define MV_DUP(vD,vA,uimm4)  vD = _mm_set1_pi16(_mm_extract_pi16(vA, ((uimm4)&0x3)^ENDIAN_W4))
#define MV_UPCKL(vD,vA)  vD = _mm_unpacklo_pi8(vA, _mm_setzero_si64())
#define MV_UPCKH(vD,vA)  vD = _mm_unpackhi_pi8(vA, _mm_setzero_si64())

#define MV_CAT(vD,vA,vB,uimm3)  vD = _mm_or_si64(_mm_slli_si64(vB, uimm3*8), _mm_srli_si64(vA, (8-uimm3)*8))

#define MV_MFV(rD,vA,uimm5)     MVC_ASSERT((uimm5&1)==0); rD = SEX16(_mm_extract_pi16(vA, uimm5>>1))
#define MV_MFVU(rD,vA,uimm5)    MVC_ASSERT((uimm5&1)==0); rD = ZEX16(_mm_extract_pi16(vA, uimm5>>1))
#define MV_MFV_B(rD,vA,uimm5)   rD = SEX8(_mm_extract_pi16(vA, (uimm5)>>1)>>(((uimm5)&1)<<3))
#define MV_MFVU_B(rD,vA,uimm5)  rD = ZEX8(_mm_extract_pi16(vA, (uimm5)>>1)>>(((uimm5)&1)<<3))
#define MV_MTV(vD,rA,uimm5) { \
    if ((uimm5>>3)&1) \
        vD = _mm_insert_pi16(vD, rA, 3); \
    if ((uimm5>>2)&1) \
        vD = _mm_insert_pi16(vD, rA, 2); \
    if ((uimm5>>1)&1) \
        vD = _mm_insert_pi16(vD, rA, 1); \
    if ((uimm5>>0)&1) \
        vD = _mm_insert_pi16(vD, rA, 0); \
}

#define MV_MMK(rD,vA)  rD =   ((((int16)_mm_extract_pi16(vA, 3))<0)<<3) \
                            | ((((int16)_mm_extract_pi16(vA, 2))<0)<<2) \
                            | ((((int16)_mm_extract_pi16(vA, 1))<0)<<1) \
                            | ((((int16)_mm_extract_pi16(vA, 0))<0)<<0)

#define MV_PCKX(vD,vA,vB,vC) { \
    int c, c1; \
    int x0, x1, x2, x3, x4, x5, x6, x7; \
 \
    c = _mm_extract_pi16(vC, 0); \
    c1 = c&0xff; \
    x0 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x0 = x0 >> ((c1&1)<<3); \
    c1 = c>>8; \
    x1 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x1 = x1 >> ((c1&1)<<3); \
 \
    c = _mm_extract_pi16(vC, 1); \
    c1 = c&0xff; \
    x2 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x2 = x2 >> ((c1&1)<<3); \
    c1 = c>>8; \
    x3 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x3 = x3 >> ((c1&1)<<3); \
 \
    c = _mm_extract_pi16(vC, 2); \
    c1 = c&0xff; \
    x4 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x4 = x4 >> ((c1&1)<<3); \
    c1 = c>>8; \
    x5 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x5 = x5 >> ((c1&1)<<3); \
 \
    c = _mm_extract_pi16(vC, 3); \
    c1 = c&0xff; \
    x6 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x6 = x6 >> ((c1&1)<<3); \
    c1 = c>>8; \
    x7 = _m_to_int(_mm_srl_si64(MUX(c1>>3, vB, vA), _mm_set_pi32(0, ((c1>>1)&3)<<4))); \
    x7 = x7 >> ((c1&1)<<3); \
 \
    vD = _mm_set_pi8(x7, x6, x5, x4, x3, x2, x1, x0); \
}

#define MV_SACC(vD,vA,vB,vC) { \
    __m64 vT; \
    MV_SLL(vD, vA, _mm_set1_pi16(1)); \
    MV_SLT(vT, vC, _mm_setzero_si64()); \
    MV_AND(vT, vT, vB); \
    MV_ADD(vD, vD, vT); \
}

#define MV_RND(vD,vA,uimm5)    vD = _mm_add_pi16(_mm_sra_pi16(vA, _mm_set_pi32(0, uimm5)), MUX(uimm5==0, _mm_setzero_si64(), _mm_and_si64(_mm_srl_si64(vA, _mm_set_pi32(0, uimm5-1)), _mm_set1_pi16(1))))
#define MV_RNDU(vD,vA,uimm5)   vD = _mm_add_pi16(_mm_srl_pi16(vA, _mm_set_pi32(0, uimm5)), MUX(uimm5==0, _mm_setzero_si64(), _mm_and_si64(_mm_srl_si64(vA, _mm_set_pi32(0, uimm5-1)), _mm_set1_pi16(1))))
#define MV_RND_B(vD,vA,uimm5) { \
    int c, c1; \
    int x0, x1, x2, x3, x4, x5, x6, x7; \
    \
    c = _mm_extract_pi16(vA, 0); \
    c1 = SEX8(c&0xff); \
    x0 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = SEX8(c>>8); \
    x1 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 1); \
    c1 = SEX8(c&0xff); \
    x2 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = SEX8(c>>8); \
    x3 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 2); \
    c1 = SEX8(c&0xff); \
    x4 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = SEX8(c>>8); \
    x5 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 3); \
    c1 = SEX8(c&0xff); \
    x6 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = SEX8(c>>8); \
    x7 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    vD = _mm_set_pi8(x7, x6, x5, x4, x3, x2, x1, x0); \
}
//vD = _mm_add_pi8(_mm_sra_pi8(vA, _mm_set_pi32(0, uimm5)), MUX(uimm5==0, _mm_setzero_si64(), _mm_and_si64(_mm_srl_si64(vA, _mm_set_pi32(0, uimm5-1)), _mm_set1_pi8(1))))

#define MV_RNDU_B(vD,vA,uimm5) { \
    int c, c1; \
    int x0, x1, x2, x3, x4, x5, x6, x7; \
    \
    c = _mm_extract_pi16(vA, 0); \
    c1 = ZEX8(c&0xff); \
    x0 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = ZEX8(c>>8); \
    x1 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 1); \
    c1 = ZEX8(c&0xff); \
    x2 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = ZEX8(c>>8); \
    x3 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 2); \
    c1 = ZEX8(c&0xff); \
    x4 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = ZEX8(c>>8); \
    x5 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    c = _mm_extract_pi16(vA, 3); \
    c1 = ZEX8(c&0xff); \
    x6 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    c1 = ZEX8(c>>8); \
    x7 = MUX(uimm5==0, c1, (c1+(1<<(uimm5-1)))>>uimm5); \
    \
    vD = _mm_set_pi8(x7, x6, x5, x4, x3, x2, x1, x0); \
}
//vD = _mm_add_pi8(_mm_srl_pi8(vA, _mm_set_pi32(0, uimm5)), MUX(uimm5==0, _mm_setzero_si64(), _mm_and_si64(_mm_srl_si64(vA, _mm_set_pi32(0, uimm5-1)), _mm_set1_pi8(1))))

#define MV_OPT(vD,vA,vB,vC,op1_uimm3,op2_uimm2)  \
{ \
    __m64 vT; \
    op1_uimm3(vT,vA,vB); \
    op2_uimm2(vD,vT,vC); \
}

#define MV_OPC(vD,vA,vB,vC,op3_uimm1,op4_uimm1)  \
{ \
    __m64 vTa; \
    __m64 vTb; \
    vD = _mm_cmpgt_pi16(_mm_setzero_si64(), vC); \
    op3_uimm1(vTa, vA, vB); \
    op4_uimm1(vTb, vA, vB); \
    vD = _mm_or_si64(_mm_and_si64(vD, vTb), _mm_and_si64(_mm_xor_si64(vD,_mm_cmpeq_pi16(vA, vA)), vTa)); \
}

#define MV_OPV(vD,vA,vB,vC,op5_uimm5) \
{ \
    __m64 vT; \
    vD = _mm_cmpgt_pi16(_mm_setzero_si64(), vC); \
    op5_uimm5(vT, vA, vB); \
    vD = _mm_or_si64(_mm_and_si64(vD, vA), _mm_and_si64(_mm_xor_si64(vD,_mm_cmpeq_pi16(vA, vA)), vT)); \
}

#define MV_OPM(vD,vA,vB,vC) { \
    __m64 vT; \
    vT = _mm_cmpgt_pi16(_mm_setzero_si64(), vC); \
    vD = _mm_or_si64(_mm_and_si64(vT, vA), _mm_and_si64(_mm_xor_si64(vT,_mm_cmpeq_pi16(vA, vA)), vB)); \
}

#define MV_LDV(vD,rA,imm16)   MVC_ASSERT((((uint32)(rA)+imm16)&0x7)==0); /*if (((uint32)(rA)+imm16)>(QM_MEM+QM_BANK_SIZE) || ((uint32)(rA)+imm16)<(QM_MEM)) vm_dbgTrace(_CUSAVP, "QMEM check %s %d\n", __FUNCTION__, __LINE__);*/ vD = *(__m64*)((uint32)(rA)+imm16)
#define MV_SDV(rA,imm16,vS)   MVC_ASSERT((((uint32)(rA)+imm16)&0x7)==0); /*if (((uint32)(rA)+imm16)>(QM_MEM+QM_BANK_SIZE) || ((uint32)(rA)+imm16)<(QM_MEM)) vm_dbgTrace(_CUSAVP, "QMEM check %s %d\n", __FUNCTION__, __LINE__);*/ *(__m64*)((uint32)(rA)+imm16) = vS

#define MV_SADDL(vD, vA, vB) { \
    __m64 vT; \
    vT = _mm_add_pi16(_mm_unpacklo_pi8(vA, _mm_setzero_si64()), vB); \
    vD = _mm_packs_pu16(vT, _mm_unpackhi_pi8(vD, _mm_setzero_si64())); \
}

#define MV_SADDH(vD, vA, vB) { \
    __m64 vT; \
    vT = _mm_add_pi16(_mm_unpackhi_pi8(vA, _mm_setzero_si64()), vB); \
    vD = _mm_packs_pu16(_mm_unpacklo_pi8(vD, _mm_setzero_si64()), vT); \
}

#define MV_MULU_B(vD, vA, vB) \
    vD = _mm_mullo_pi16(_mm_and_si64(vA, _mm_set1_pi16(0x00ff)), _mm_and_si64(vB, _mm_set1_pi16(0x00ff)))

#define MV_MFVW(rD,vA)     rD = _m_to_int(vA)
//#define MV_MFVW(rD,vA,uimm4)     rD = _m_to_int(MUX(uimm4&0xc, _mm_srli_si64(vA, 32), vA))
//#define MV_MTVW(vD,rA)     vD = _m_from_int(rA)
#define MV_MTVW(vD,rA,uimm4)     vD = MUX(uimm4&0xc, _mm_unpacklo_pi32(vD, _m_from_int(rA)), _mm_unpacklo_pi32(_m_from_int(rA), _mm_srli_si64(vD, 32)))

#define MV_LDW(vD,rA,imm16)   MVC_ASSERT((((uint32)(rA)+imm16)&0x3)==0); vD = _m_from_int(*(uint32*)((uint32)(rA)+imm16))
#define MV_SDW(rA,imm16,vS)   MVC_ASSERT((((uint32)(rA)+imm16)&0x3)==0); *(uint32*)((uint32)(rA)+imm16) = _m_to_int(vS)

#endif
