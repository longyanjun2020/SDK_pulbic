#ifndef MIPS32_GCC_H
#define MIPS32_GCC_H

#include <stdint.h>
#ifndef MIPS16E

#ifdef _AG_DSP_ASE_
typedef signed char v4i8 __attribute__ ((vector_size(4)));
typedef short v2q15 __attribute__ ((vector_size(4)));
typedef long long a64;
typedef int q31;
typedef short q15;

#define ADDQ_PH(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_addq_ph((v2q15)(a), (v2q15)(b)); \
    (unsigned int) out_; \
})

#define SUBQ_PH(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_subq_ph((v2q15)(a), (v2q15)(b)); \
    (unsigned int) out_; \
})

#define PRECRQ_QB_PH(a, b) \
({ \
    v4i8 out_; \
    out_ = __builtin_mips_precrq_qb_ph((v2q15)(a), (v2q15)(b)); \
    (unsigned int) out_; \
})

#define PRECRQ_PH_W(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_precrq_ph_w((q31)(a), (q31)(b)); \
    (unsigned int) out_; \
})

#define PRECEU_PH_QBR(a) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_preceu_ph_qbr((v4i8)(a)); \
    (unsigned int) out_; \
})

#define PRECEU_PH_QBL(a) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_preceu_ph_qbl((v4i8)(a)); \
    (unsigned int) out_; \
})

#define SHRA_PH(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_shra_ph((v2q15)(a), (b)); \
    (unsigned int) out_; \
})

#define REPL_PH(a) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_repl_ph(a); \
    (unsigned int) out_; \
})

#define PACKRL_PH(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_packrl_ph((v2q15)(a), (v2q15)(b)); \
    (unsigned int) out_; \
})

#define DPAQ_S_W_PH(a, b, c) \
({ \
    a64 out_; \
    out_ = __builtin_mips_dpaq_s_w_ph((a64)(a), (v2q15)(b), (v2q15)(c)); \
    (long long) out_; \
})

#define REPL_QB(a) \
({ \
    v4i8 out_; \
    out_ = __builtin_mips_repl_qb(a); \
    (unsigned int)out_; \
})

#define PICK_PH(a, b) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_pick_ph((v2q15)(a), (v2q15)(b)); \
    (unsigned int) out_; \
})

#define CMP_LT_PH(a, b) __builtin_mips_cmp_lt_ph((v2q15)(a), (v2q15)(b))

#define DUALUCLIPI(a, b) \
({ \
    uint32 out; \
    uint32 c_0 = IHALFWORDDUP(0); \
    uint32 c_max = IHALFWORDDUP(b); \
    \
    CMP_LT_PH(c_0, a); \
    (a) = PICK_PH((a), c_0); \
    CMP_LT_PH(c_max, a); \
    (out) = PICK_PH(c_max, (a)); \
    out; \
})

#define PRECEU_PH_QBRA(rt) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_preceu_ph_qbra((v4i8)rt); \
    (unsigned int) out_; \
})

#define PRECEU_PH_QBLA(rt) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_preceu_ph_qbla((v4i8)rt); \
    (unsigned int) out_; \
})

#define MULEQ_S_W_PHL(rs, rt) \
({ \
    q31 out_; \
    out_ = __builtin_mips_muleq_s_w_phl ((v2q15)rs, (v2q15)rt); \
    (int) out_; \
})

#define MULEQ_S_W_PHR(rs, rt) \
({ \
    q31 out_; \
    out_ = __builtin_mips_muleq_s_w_phr ((v2q15)(rs), (v2q15)(rt)); \
    (int) out_; \
})


#define IHALFWORDDUP(a) REPL_PH(a)

#define DSPIDUALABS(rt) \
({ \
    v2q15 out_; \
    out_ = __builtin_mips_absq_s_ph((v2q15)rt); \
    (unsigned int) out_; \
})

#define CMP_AND_PICK_PH(a, b) \
({ \
    UINT32 out_; \
    UINT32 c_0 = IHALFWORDDUP(0); \
    CMP_LT_PH(a, b); \
    out_ = PICK_PH(a, c_0); \
    out_; \
})

#define CMP_AND_PICK_PH2(a, b) \
({ \
    UINT32 out_; \
    UINT32 c_0 = IHALFWORDDUP(0); \
    CMP_LT_PH(a, c_0); \
    out_ = PICK_PH(c_0, b); \
    out_; \
})

#define ADDQ_S_PH           __builtin_mips_addq_s_ph
#define ADDQ_S_W            __builtin_mips_addq_s_w
#define ADDU_QB             __builtin_mips_addu_qb
#define ADDU_S_QB           __builtin_mips_addu_s_qb
#define SUBQ_S_PH           __builtin_mips_subq_s_ph
#define SUBQ_S_W            __builtin_mips_subq_s_w
#define SUBU_QB             __builtin_mips_subu_qb
#define SUBU_S_QB           __builtin_mips_subu_s_qb
#define ADDSC               __builtin_mips_addsc
#define ADDWC               __builtin_mips_addwc
#define MODSUB              __builtin_mips_modsub
#define RADDU_W_QB          __builtin_mips_raddu_w_qb
#define ABSQ_S_W            __builtin_mips_absq_s_w
#define PRECRQ_RS_PH_W      __builtin_mips_precrq_rs_ph_w
#define PRECRQU_S_QB_PH     __builtin_mips_precrqu_s_qb_ph
#define PRECRQ_W_PHL        __builtin_mips_preceq_w_phl
#define PRECRQ_W_PHR        __builtin_mips_preceq_w_phr
#if 0  // not ready
v2q15 __builtin_mips_precequ_ph_qbl (v4i8)
v2q15 __builtin_mips_precequ_ph_qbr (v4i8)
v2q15 __builtin_mips_precequ_ph_qbla (v4i8)
v2q15 __builtin_mips_precequ_ph_qbra (v4i8)
v4i8 __builtin_mips_shll_qb (v4i8, imm0_7)
v4i8 __builtin_mips_shll_qb (v4i8, i32)
v2q15 __builtin_mips_shll_ph (v2q15, imm0_15)
v2q15 __builtin_mips_shll_ph (v2q15, i32)
v2q15 __builtin_mips_shll_s_ph (v2q15, imm0_15)
v2q15 __builtin_mips_shll_s_ph (v2q15, i32)
q31 __builtin_mips_shll_s_w (q31, imm0_31)
q31 __builtin_mips_shll_s_w (q31, i32)
v4i8 __builtin_mips_shrl_qb (v4i8, imm0_7)
v4i8 __builtin_mips_shrl_qb (v4i8, i32)
v2q15 __builtin_mips_shra_ph (v2q15, i32)
v2q15 __builtin_mips_shra_r_ph (v2q15, imm0_15)
v2q15 __builtin_mips_shra_r_ph (v2q15, i32)
q31 __builtin_mips_shra_r_w (q31, imm0_31)
q31 __builtin_mips_shra_r_w (q31, i32)
v2q15 __builtin_mips_muleu_s_ph_qbl (v4i8, v2q15)
v2q15 __builtin_mips_muleu_s_ph_qbr (v4i8, v2q15)
v2q15 __builtin_mips_mulq_rs_ph (v2q15, v2q15)
a64 __builtin_mips_dpau_h_qbl (a64, v4i8, v4i8)
a64 __builtin_mips_dpau_h_qbr (a64, v4i8, v4i8)
a64 __builtin_mips_dpsu_h_qbl (a64, v4i8, v4i8)
a64 __builtin_mips_dpsu_h_qbr (a64, v4i8, v4i8)
#endif

#define DPAQ_SA_L_W         __builtin_mips_dpaq_sa_l_w
#define DPSQ_S_W_PH         __builtin_mips_dpsq_s_w_ph
#define DPSQ_SA_L_W         __builtin_mips_dpsq_sa_l_w

#if 0 // not ready
a64 __builtin_mips_mulsaq_s_w_ph (a64, v2q15, v2q15)
a64 __builtin_mips_maq_s_w_phl (a64, v2q15, v2q15)
a64 __builtin_mips_maq_s_w_phr (a64, v2q15, v2q15)
a64 __builtin_mips_maq_sa_w_phl (a64, v2q15, v2q15)
a64 __builtin_mips_maq_sa_w_phr (a64, v2q15, v2q15)
i32 __builtin_mips_bitrev (i32)
i32 __builtin_mips_insv (i32, i32)
v2q15 __builtin_mips_repl_ph (i32)
void __builtin_mips_cmpu_eq_qb (v4i8, v4i8)
void __builtin_mips_cmpu_lt_qb (v4i8, v4i8)
void __builtin_mips_cmpu_le_qb (v4i8, v4i8)
i32 __builtin_mips_cmpgu_eq_qb (v4i8, v4i8)
i32 __builtin_mips_cmpgu_lt_qb (v4i8, v4i8)
i32 __builtin_mips_cmpgu_le_qb (v4i8, v4i8)
void __builtin_mips_cmp_eq_ph (v2q15, v2q15)
void __builtin_mips_cmp_le_ph (v2q15, v2q15)
v4i8 __builtin_mips_pick_qb (v4i8, v4i8)
i32 __builtin_mips_extr_w (a64, imm0_31)
i32 __builtin_mips_extr_w (a64, i32)
i32 __builtin_mips_extr_r_w (a64, imm0_31)
i32 __builtin_mips_extr_s_h (a64, i32)
i32 __builtin_mips_extr_rs_w (a64, imm0_31)
i32 __builtin_mips_extr_rs_w (a64, i32)
i32 __builtin_mips_extr_s_h (a64, imm0_31)
i32 __builtin_mips_extr_r_w (a64, i32)
i32 __builtin_mips_extp (a64, imm0_31)
i32 __builtin_mips_extp (a64, i32)
i32 __builtin_mips_extpdp (a64, imm0_31)
i32 __builtin_mips_extpdp (a64, i32)
a64 __builtin_mips_shilo (a64, imm_n32_31)
a64 __builtin_mips_shilo (a64, i32)
a64 __builtin_mips_mthlip (a64, i32)
void __builtin_mips_wrdsp (i32, imm0_63)
i32 __builtin_mips_rddsp (imm0_63)
i32 __builtin_mips_lbux (void *, i32)
i32 __builtin_mips_lhx (void *, i32)
i32 __builtin_mips_lwx (void *, i32)
i32 __builtin_mips_bposge32 (void)
#endif

#endif // _AG_DSP_ASE_

#define CLSAME(a, b) __builtin_clz ((a) ^ (b))
#define SWAPBYTES(r1) \
({ \
    uint32_t out; \
    __asm__ ("wsbh %0, %1": "=r" (out) : "r" (r1)); \
    __asm__ ("rotr %0, %1, 16": "=r" (out) : "r" (out)); \
    out; \
})

#define SWAPBYTESHALFWORD(x) \
({ \
    uint32_t out; \
    __asm__ ("wsbh %0, %1": "=r" (out) : "r" (x)); \
    out; \
})

#define INS(t, v, pos, size) ({ \
    uint32_t out = (t); \
    __asm__ ("ins %0, %1, %2, %3": "+r" (out) : "r" (v), "i" (pos), "i" (size)); \
    out; \
})

#define EXT(x, pos, size) \
({ \
    uint32_t out; \
    __asm__ ("ext %0, %1, %2, %3": "=r" (out) : "r" (x), "i" (pos), "i" (size)); \
    out; \
})

#define PACKBYTES_INST32(a, b) (INS(b, a, 8, 8) & 0xffff)
#define PACKBYTES_INST16(a, b) ((((a)&0x000000ff)<<8) | ((b)&0x000000ff))
#define PACKBYTES(a, b) (INS(b, a, 8, 8) & 0xffff)


#define MERGEMSB_INST16(a,b) ((((uint32_t)(a))&0xFF000000L) | ((((uint32_t)(a))&0x00FF0000L) >> 8) | ((((uint32_t)(b))&0xFF000000L) >> 8) | ((((uint32_t)(b))&0x00FF0000L) >> 16))
#define MERGEMSB_INST32(a,b)   MERGELSB(a>>16, b>>16)
#define MERGELSB_INST16(a,b)   ( (((a)&0x0000ff00)<<16) | (((a)&0x000000ff)<<8) | (((b)&0x0000ff00)<<8) | ((b)&0x000000ff) )
#define MERGELSB_INST32(a,b)   INS(INS(INS(b, a, 16, 16), b, 8, 16), a, 8, 8)
#define MERGELSB(a,b)   INS(INS(INS(b, a, 16, 16), b, 8, 16), a, 8, 8)
#define MERGEMSB(a,b)   MERGELSB(a>>16, b>>16)

#define PACK16MSB_INST32(a, b) INS(a, (((uint32_t)(b))>>16),  0, 16)
#define PACK16MSB_INST16(a, b) (((a)&0xffff0000) | (((uint32_t)(b))>>16))
#define PACK16MSB(a, b) PACK16MSB_INST32(a, b)

#define PACK16LSB_INST32(a, b) INS(b, a, 16, 16)
#define PACK16LSB_INST16(a, b) (((a)<<16) | ((b)&0xffff))
#define PACK16LSB(a, b) PACK16LSB_INST32(a, b)

#define MERGEDUAL16LSB_INST32(a,b)  INS(INS(INS(b, a, 8, 24), a, 16, 8), b>>16, 8, 8)
#define MERGEDUAL16LSB_INST16(a,b) ( (((a)&0x00ff0000)<<8) | (((a)&0x000000ff)<<16) | (((b)&0x00ff0000)>>8) | ((b)&0x000000ff) )
#define MERGEDUAL16LSB(a, b) MERGEDUAL16LSB_INST32(a,b)

#define UBYTESEL_VAR(a, i)  ((uint32_t)(((a)>>(((i)&3)<<3))&0xff))  // unsign extended
#define IBYTESEL_VAR(a, i)  SEX8(((a)>>(((i)&3)<<3)))  // sign extended

#define UBYTESEL_0(a) EXT(a, 0, 8)
#define UBYTESEL_1(a) EXT(a, 8, 8)
#define UBYTESEL_2(a) EXT(a, 16, 8)
#define UBYTESEL_3(a) EXT(a, 24, 8)
#define UBYTESEL_INST32(a, b) UBYTESEL_##b(a)

#define UBYTESEL_0_INST16(a) ((a)&0x0ff)
#define UBYTESEL_1_INST16(a) (((a)>>8)&0x0ff)
#define UBYTESEL_2_INST16(a) (((a)>>16)&0x0ff)
#define UBYTESEL_3_INST16(a) (((a)>>24)&0x0ff)
#define UBYTESEL_INST16(a, b) UBYTESEL_##b##_INST16(a)

#define UBYTESEL(a, b) UBYTESEL_INST32(a, b)

#define IBYTESEL_0(a) SEX8(EXT(a, 0, 8))
#define IBYTESEL_1(a) SEX8(EXT(a, 8, 8))
#define IBYTESEL_2(a) SEX8(EXT(a, 16, 8))
#define IBYTESEL_3(a) SEX8(EXT(a, 24, 8))
#define IBYTESEL(a, b) IBYTESEL_##b(a)

#define FUNSHIFT1_INST32(a,b)  INS((((uint32_t)(b))>>24), a,  8, 24)
#define FUNSHIFT2_INST32(a,b)  INS((((uint32_t)(b))>>16), a, 16, 16)
#define FUNSHIFT3_INST32(a,b)  INS((((uint32_t)(b))>> 8), a, 24,  8)

#define FUNSHIFT1_INST16(a, b)   (((a)<<8)  | (((uint32_t)(b))>>24))
#define FUNSHIFT2_INST16(a, b)   (((a)<<16) | (((uint32_t)(b))>>16))
#define FUNSHIFT3_INST16(a, b)   (((a)<<24) | (((uint32_t)(b))>>8 ))
#define FUNSHIFT1(a, b) FUNSHIFT1_INST32(a, b)
#ifdef _AG_DSP_ASE_
#define FUNSHIFT2(a, b) PACKRL_PH(a, b)
#else
#define FUNSHIFT2(a, b) FUNSHIFT2_INST32(a, b)
#endif
#define FUNSHIFT3(a, b) FUNSHIFT3_INST32(a, b)

#define MERGEODD(a, b) INS(INS(b, a, 8, 8), a>>16, 24, 8)

#define SH_PLUS32(a)    (a)

// OP=>  0: load, 1: store, 4:load_stream, 5: store_stream, 6:load_retain, 7: store_retain
/*#define PREFD(OP, LOC) \
    __asm__ ("pref %0,%1" : : "i" (OP), "m" (LOC));*/

#define D_INVALID(OP, LOC) \
    __asm__ ("cache %0,%1" : : "n" (OP), "m" (LOC));

#define PACK_2_U16_INST32(a, b) INS(b, a, 16, 16)
#define PACK_2_U16_INST16(a, b) (((a) << 16) | (b))
#define PACK_2_U16(a, b) PACK_2_U16_INST32(a, b)

#define PACK_U24_U8_INST32(a, b) INS(b, a, 8, 24)
#define PACK_U24_U8_INST16(a, b) (((a) << 8) | (b))
#define PACK_U24_U8(a, b) PACK_U24_U8_INST32(a, b)

#define PACK_2_U8_INST32(a, b)  INS(b, a, 8, 8)
#define PACK_2_U8_INST16(a, b)  (((a) << 8) | (b))
#define PACK_2_U8(a, b)  PACK_2_U8_INST32(a, b)

#define PACK_U8_U24(a, b) INS(b, a, 24, 8)

#define IBYTEDUP0_INST32(a) INS(INS(a, a, 8, 8), INS(a, a, 8, 8), 16, 16)
#define IBYTEDUP0_INST16(a) (((a)&0xff) << 24) | (((a)&0xff) << 16) | (((a)&0xff) << 8) | (((a)&0xff) << 0)
#ifdef _AG_DSP_ASE_
#define IBYTEDUP0(a) REPL_QB(a)
#else
#define IBYTEDUP0(a) INS(INS(a, a, 8, 8), INS(a, a, 8, 8), 16, 16)
#endif
#define IBYTEDUP1(a) IBYTEDUP0((a)>>8)
#define IBYTEDUP2(a) IBYTEDUP0((a)>>16)
#define IBYTEDUP3(a) IBYTEDUP0((a)>>24)
#endif

#define CLIP3(min_val, max_val, x) MIN(MAX((int)(x), min_val), (max_val))

#define LOAD32U(dst, src, imm) \
do { \
    uint32_t t32; \
    __asm__ ("lwr %0, %2(%1)": "=r" (t32) : "r" (src), "i" ((imm))); \
    __asm__ ("lwl %0, %2(%1)": "=r" (t32) : "r" (src), "i" ((imm) + 3), "0" (t32)); \
    dst = t32; \
} while(0)

#define STORE32U(dst, src, imm) \
do { \
    __asm__ ("swr %1, %0": "=m" (*(uint32_t*)(dst + (imm)    )) : "r" (src)); \
    __asm__ ("swl %1, %0": "=m" (*(uint32_t*)(dst + (imm) + 3)) : "r" (src)); \
} while(0)

#define IABS iabs
static __inline int32_t iabs(int32_t x)
{
    return ((x)>0 ? (x) : -(x));
}

/*#define UCLIPI uclipi
static __inline uint32 uclipi(int32 x, uint32 c)
{
    if (x < 0) return 0;
    if (x > c) return c;
    return x;
}*/

#ifdef CONFIG_SMALL

#define MIPS_M2
//#define MIPS_M3

#ifdef MIPS_M2
#define ATTR_INST16_M2 __attribute__((mips16))
#define ATTR_INST16_M3
#elif defined(MIPS_M3)
#define ATTR_INST16_M2
#define ATTR_INST16_M3 __attribute__((mips16))
#endif

#define ATTR_INST16 __attribute__((mips16))

#endif // CONFIG_SMALL

#endif
