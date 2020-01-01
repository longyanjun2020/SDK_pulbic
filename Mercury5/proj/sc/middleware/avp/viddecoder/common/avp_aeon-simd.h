#ifndef __AEON_SIMD_H
#define __AEON_SIMD_H
/*
  SIMD Registers
 */

//NOTE: Currently compiler doesn't do register allocation.  User must use
//      physical register as defined below, which is tokenized and literally
//      emitted to assembly file        //ToDo:

enum VectorRegister
{
    v0,
    v1,
    v2,
    v3,
    v4,
    v5,
    v6,
    v7,
    v8,
    v9,
    v10,
    v11,
    v12,
    v13,
    v14,
    v15,
    v16,
    v17,
    v18,
    v19,
    v20,
    v21,
    v22,
    v23,
    v24,
    v25,
    v26,
    v27,
    v28,
    v29,
    v30,
    v31
};

/*
  SIMD/ASIC Helper Macro
 */

#define __MV___VVV(mnemonic, vD,vA,vB)      \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA "," #vB ";\t#__ASM__" \
        : :                                 \
    );                                      \
    })

#define __MV___VVI(mnemonic, vD,vA,imm)     \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA ",%0;\t#__ASM__" \
        :                                   \
        : "K"(imm)                          \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___VVVI(mnemonic, vD,vA,vB,imm) \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA "," #vB ",%0;\t#__ASM__" \
        :                                   \
        : "K"(imm)                          \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___RVI(mnemonic, rD,vA,imm)     \
({ __asm__ volatile (mnemonic "\t%0," #vA ",%1;\t#__ASM__" \
        : "=r"(rD)                          \
        : "K"(imm)                          \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___VRI(mnemonic, vD,rA,imm)     \
({ __asm__ volatile (mnemonic "\t" #vD ",%0,%1;\t#__ASM__" \
        :                                   \
        : "r"(rA), "K"(imm)                 \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___RV(mnemonic, rD,vA)          \
({ __asm__ volatile (mnemonic "\t%0," #vA ";\t#__ASM__" \
        : "=r"(rD)                          \
        :                                   \
    );                                      \
    })

#define __MV___VVVV(mnemonic, vD,vA,vB,vC)  \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA "," #vB "," #vC ";\t#__ASM__" \
        : :                                 \
    );                                      \
    })

#define __MV___VVVVI(mnemonic, vD,vA,vB,vC,imm)  \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA "," #vB "," #vC ",%0;\t#__ASM__" \
        :                                   \
        : "K"(imm)                          \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___VVVVII(mnemonic, vD,vA,vB,vC,imm,jmm)  \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA "," #vB "," #vC ",%0,%1;\t#__ASM__" \
        :                                   \
        : "K"(imm), "K"(jmm)                \
    );                                      \
    })                  //ToDo: check imm range

#define __MV___VV(mnemonic, vD,vA)          \
({ __asm__ volatile (mnemonic "\t" #vD "," #vA ";\t#__ASM__" \
        : :                                 \
    );                                      \
    })

#define __MV_LD(mnemonic, vD,rA,imm16)      \
 {  __asm__ volatile (mnemonic "\t" #vD ",%1(%0);\t#__ASM__" \
        :                                   \
        : "r"(rA), "K"(imm16)               \
    ); }                //ToDo: check 3-LSB is zero

#define __MV_SD(mnemonic, rA,imm16,vSRC)    \
 {  __asm__ volatile (mnemonic "\t%1(%0)," #vSRC ";\t#__ASM__" \
        :                                   \
        : "r"(rA), "K"(imm16)               \
    ); }                //ToDo: check 3-LSB is zero

#define __C8___V_RI(mnemonic,vD,rA,imm16)   \
 {  __asm__ volatile (mnemonic "\t" #vD ",%0,%1;\t#__ASM__"   \
        :                                   \
        : "r"(rA), "K"(imm16)               \
    ); }                //ToDo: check 4-LSB is zero

#define __C8___RIV(mnemonic,rA,imm16,vSRC)  \
 {  __asm__ volatile (mnemonic "\t%0," #vSRC ",%1;\t#__ASM__"  \
        :                                   \
        : "r"(rA), "K"(imm16)               \
    ); }                //ToDo: check 4-LSB is zero

#define __C8___R_RI(mnemonic, rA, uimm12)   \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0,%1,%2;\t#__ASM__"   \
        : "=r"(_result_)                    \
        : "r"(rA), "K"(uimm12)              \
    );                                      \
    _result_;})         //ToDo: "K" isn't 12-bit

#define __C8___RIR(mnemonic, rA, uimm12, val) \
 {  unsigned _v_ = val;                     \
    __asm__ volatile (mnemonic "\t%0,%1,%2;\t#__ASM__"   \
        :                                   \
        : "r"(rA), "r"(_v_), "K"(uimm12)    \
    ); }                //ToDo: "K" isn't 12-bit

#define __C8_____(mnemonic)                 \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0;\t#__ASM__"   \
        : "=r"(_result_)                    \
        :                                   \
    );                                      \
    _result_;})

#define __C8___I_(mnemonic, uimm5)          \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0,%1;\t#__ASM__"   \
        : "=r"(_result_)                    \
        : "K"(uimm5)                        \
    );                                      \
    _result_;})

#define __C8___R_(mnemonic, rA)             \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0,%1;\t#__ASM__"   \
        : "=r"(_result_)                    \
        : "r"(rA)                           \
    );                                      \
    _result_;})

#define __C8___R1_(mnemonic)             \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0,r1,0;\t#__ASM__"   \
        : "=r"(_result_)                    \
    );                                      \
    _result_;})

#define __C8___R9_(mnemonic)             \
({  unsigned _result_;                      \
    __asm__ volatile (mnemonic "\t%0,r9,0;\t#__ASM__"   \
        : "=r"(_result_)                    \
    );                                      \
    _result_;})

/*
  OP#
 */

#define OP1_ADD     0
#define OP1_SUB     1
#define OP1_ABS     2
#define OP1_SLL     3
#define OP1_AND     4
#define OP1_OR      5
#define OP1_XOR     6

#define OP2_ADD     0
#define OP2_SUB     1
#define OP2_SRA     2
#define OP2_SRL     3

#define OP3_ADD     0
#define OP3_SUB     1

#define OP4_ADD     0
#define OP4_SUB     1

#define OP5_ADD     0
#define OP5_SUB     1
#define OP5_AVG     2
#define OP5_SRA     3
#define OP5_SRL     4
#define OP5_SLL     5
#define OP5_AND     6
#define OP5_OR      7
#define OP5_XOR     8

/*
  SIMD Instructions
 */

//NOTE: Currently thes macro needs physical register in string form,
//      and all macro doesn't return value.
//ToDo: Future macro will be able to take C vector variable, and some
//      will return vector or register variable.  When these happen,
//      all macro below will be renamed to lower-case counterparts of
//      the same name.

#define MV_ADD(vD,vA,vB)  __MV___VVV("mv.add", vD,vA,vB)
#define MV_ADDU(vD,vA,vB)  __MV___VVV("mv.addu", vD,vA,vB)
#define MV_ADD_B(vD,vA,vB)  __MV___VVV("mv.add.b", vD,vA,vB)
#define MV_ADDU_B(vD,vA,vB)  __MV___VVV("mv.addu.b", vD,vA,vB)

#define MV_SUB(vD,vA,vB)  __MV___VVV("mv.sub", vD,vA,vB)
#define MV_SUBU(vD,vA,vB)  __MV___VVV("mv.subu", vD,vA,vB)
#define MV_SUB_B(vD,vA,vB)  __MV___VVV("mv.sub.b", vD,vA,vB)
#define MV_SUBU_B(vD,vA,vB)  __MV___VVV("mv.subu.b", vD,vA,vB)

#define MV_AVG(vD,vA,vB)  __MV___VVV("mv.avg", vD,vA,vB)
#define MV_AVGU(vD,vA,vB)  __MV___VVV("mv.avgu", vD,vA,vB)
#define MV_AVG_B(vD,vA,vB)  __MV___VVV("mv.avg.b", vD,vA,vB)
#define MV_AVGU_B(vD,vA,vB)  __MV___VVV("mv.avgu.b", vD,vA,vB)

#define MV_ABS(vD,vA)  __MV___VV("mv.abs", vD,vA)

#define MV_SADDL(vD,vA,vB)  __MV___VVV("mv.saddl", vD,vA,vB)
#define MV_SADDH(vD,vA,vB)  __MV___VVV("mv.saddh", vD,vA,vB)

#define MV_MULU_B(vD,vA,vB)  __MV___VVV("mv.mulu.b", vD,vA,vB)

#define MV_SRA(vD,vA,vB)  __MV___VVV("mv.sra", vD,vA,vB)
#define MV_SRL(vD,vA,vB)  __MV___VVV("mv.srl", vD,vA,vB)
#define MV_SLL(vD,vA,vB)  __MV___VVV("mv.sll", vD,vA,vB)

#define MV_AND(vD,vA,vB)  __MV___VVV("mv.and", vD,vA,vB)
#define MV_OR(vD,vA,vB)  __MV___VVV("mv.or", vD,vA,vB)
#define MV_XOR(vD,vA,vB)  __MV___VVV("mv.xor", vD,vA,vB)

#define MV_SEQ(vD,vA,vB)  __MV___VVV("mv.seq", vD,vA,vB)
#define MV_SEQ_B(vD,vA,vB)  __MV___VVV("mv.seq.b", vD,vA,vB)

#define MV_SLT(vD,vA,vB)  __MV___VVV("mv.slt", vD,vA,vB)
#define MV_SLTU(vD,vA,vB)  __MV___VVV("mv.sltu", vD,vA,vB)
#define MV_SLT_B(vD,vA,vB)  __MV___VVV("mv.slt.b", vD,vA,vB)
#define MV_SLTU_B(vD,vA,vB)  __MV___VVV("mv.sltu.b", vD,vA,vB)

#define MV_TEXTNZ(vD,vA)  __MV___VV("mv.textnz", vD,vA)
#define MV_LZC(vD,vA)  __MV___VV("mv.lzc", vD,vA)

#define MV_RAND(vD,vA)  __MV___VV("mv.rand", vD,vA)
#define MV_ROR(vD,vA)  __MV___VV("mv.ror", vD,vA)

#define MV_MIN(vD,vA,vB)  __MV___VVV("mv.min", vD,vA,vB)
#define MV_MINU(vD,vA,vB)  __MV___VVV("mv.minu", vD,vA,vB)
#define MV_MAX(vD,vA,vB)  __MV___VVV("mv.max", vD,vA,vB)
#define MV_MAXU(vD,vA,vB)  __MV___VVV("mv.maxu", vD,vA,vB)

#define MV_CLIP3U(vD,vA,vB,vC)  __MV___VVVV("mv.clip3u", vD,vA,vB,vC)
#define MV_CLIP3(vD,vA,vB,vC)  __MV___VVVV("mv.clip3", vD,vA,vB,vC)
#define MV_DUP(vD,vA,uimm4)  __MV___VVI("mv.dup", vD,vA,uimm4)
#define MV_UPCKL(vD,vA)  __MV___VV("mv.upckl", vD,vA)
#define MV_UPCKH(vD,vA)  __MV___VV("mv.upckh", vD,vA)

#define MV_CAT(vD,vA,vB,uimm3)  __MV___VVVI("mv.cat", vD,vA,vB,uimm3)

#define MV_MFV(rD,vA,uimm5)  __MV___RVI("mv.mfv", rD,vA,uimm5)
#define MV_MFVU(rD,vA,uimm5)  __MV___RVI("mv.mfvu", rD,vA,uimm5)
#define MV_MFV_B(rD,vA,uimm5)  __MV___RVI("mv.mfv.b", rD,vA,uimm5)
#define MV_MFVU_B(rD,vA,uimm5)  __MV___RVI("mv.mfvu.b", rD,vA,uimm5)
#define MV_MFVW(rD,vA)  __MV___RV("mv.mfvw", rD,vA)

#define MV_MTV(vD,rA,uimm5)  __MV___VRI("mv.mtv", vD,rA,uimm5)
#define MV_MTVW(vD,rA,uimm5)  __MV___VRI("mv.mtvw", vD,rA,uimm5)

#define MV_MMK(rD,vA)  __MV___RV("mv.mmk", rD,vA)

#define MV_PCKX(vD,vA,vB,vC)  __MV___VVVV("mv.pckx", vD,vA,vB,vC)
#define MV_SACC(vD,vA,vB,vC)  __MV___VVVV("mv.sacc", vD,vA,vB,vC)

#define MV_RND(vD,vA,uimm5)  __MV___VVI("mv.rnd", vD,vA,uimm5)
#define MV_RNDU(vD,vA,uimm5)  __MV___VVI("mv.rndu", vD,vA,uimm5)
#define MV_RND_B(vD,vA,uimm5)  __MV___VVI("mv.rnd.b", vD,vA,uimm5)
#define MV_RNDU_B(vD,vA,uimm5)  __MV___VVI("mv.rndu.b", vD,vA,uimm5)

#define MV_OPT(vD,vA,vB,vC,op1_uimm3,op2_uimm2)  __MV___VVVVII("mv.opt", vD,vA,vB,vC,op1_uimm3,op2_uimm2)
#define MV_OPC(vD,vA,vB,vC,op3_uimm1,op4_uimm1)  __MV___VVVVII("mv.opc", vD,vA,vB,vC,op3_uimm1,op4_uimm1)
#define MV_OPV(vD,vA,vB,vC,op5_uimm5)  __MV___VVVVI("mv.opv", vD,vA,vB,vC,op5_uimm5)
#define MV_OPM(vD,vA,vB,vC)  __MV___VVVV("mv.opm", vD,vA,vB,vC)

#define MV_LDV(vD,rA,imm16)  __MV_LD("mv.ldv", vD,rA,imm16)
#define MV_SDV(rA,imm16,vSRC)  __MV_SD("mv.sdv", rA,imm16,vSRC)

#define MV_LDW(vD,rA,imm16)  __MV_LD("mv.ldw", vD,rA,imm16)
#define MV_SDW(rA,imm16,vSRC)  __MV_SD("mv.sdw", rA,imm16,vSRC)

#define MAX_SPRS_PER_GRP_BITS (11)
#define SPRGROUP_SYS      (0<< MAX_SPRS_PER_GRP_BITS)
#define SPR_SIMD        (SPRGROUP_SYS + 256)
#define SPR_SIMD_ACC0 (SPR_SIMD + 0)
#define SPR_SIMD_ACC1 (SPR_SIMD + 1)
#define SPR_SIMD_ACC2 (SPR_SIMD + 2)
#define SPR_SIMD_ACC3 (SPR_SIMD + 3)
#define SPR_SIMD_ACC4 (SPR_SIMD + 4)
#define SPR_SIMD_ACC5 (SPR_SIMD + 5)
#define SPR_SIMD_ACC6 (SPR_SIMD + 6)
#define SPR_SIMD_ACC7 (SPR_SIMD + 7)

//for v0~v7 28bits*4 usage
#define SPR_GRP_SIMD            13
#define SPR_GRP_SIMD_OFFSET     (SPR_GRP_SIMD<<11)
#define SPR_SIMD_MVREG0_L       (SPR_GRP_SIMD_OFFSET + 0)
#define SPR_SIMD_MVREG0_H       (SPR_GRP_SIMD_OFFSET +32)
#define SPR_SIMD_MVREG0_G       (SPR_GRP_SIMD_OFFSET +64)
#define SPR_SIMD_MVREG0_GH      (SPR_GRP_SIMD_OFFSET +72)

#define MTSPR(_spr_,  _value_) \
    ({                                                        \
    __asm__ __volatile__ ("l.mtspr\t\t%0,%1,0"           \
    : : "r" (_spr_), "r" (_value_));           \
    })                                                    


#define MFSPR(_spr_)                        \
    ({                                                        \
    unsigned long _value_;                                  \
    __asm__ __volatile__ ("l.mfspr\t\t%0,%1,0"            \
    : "=r" (_value_) : "r" (_spr_));                      \
_value_;})                              


#define AEON_MFSPR(_spr_group_5bit_, _spr_register_11bit_)       \
({  unsigned _result_;                                      \
    asm volatile ("l.mfspr %0, %1, %2;"                     \
        : "=r"(_result_)                                    \
        : "r"(_spr_group_5bit_), "K"(_spr_register_11bit_)  \
    );                                                      \
    _result_;})

/*
  ASIC Instructions
 */

//NOTE: All ASIC instructions except for the first two (PS*1) access conventional register,
//      and it happens that most of these macro produce value (ie. it can be used at
//      right-hand-side,  eg. X = c8_mfasic(Y, 0), where X and Y can be conventioanl C
//      variable of 32-bit in size
//
//      PS*1: There naming remain upper-case (just like MV_* macros) to remind user that vecto
//            argument may be modified
//

#define C8_MFASICV(vD,rA,imm16)  __C8___V_RI("c8.mfasicv", vD,rA,imm16)
#define C8_MTASICV(rA,imm16,vSRC)  __C8___RIV("c8.mtasicv", rA,imm16,vSRC)

#define c8_mfasic(rA, uimm12)  __C8___R_RI("c8.mfasic", rA, uimm12)
#define c8_mtasic(rA, uimm12, val)  __C8___RIR("c8.mtasic", rA, uimm12, val)
#define c8_asicgbi(uimm5)  __C8___I_("c8.asicgbi", uimm5)
#define c8_asicsbi(uimm5)  __C8___I_("c8.asicsbi", uimm5)
#define c8_asicgb(rA)  __C8___R_("c8.asicgb", rA)
#define c8_asicsb(rA)  __C8___R_("c8.asicsb", rA)
#define c8_asicue()  __C8_____("c8.asicue");
#define c8_asicse()  __C8_____("c8.asicse");
#define c8_asiclo()  __C8_____("c8.asiclo");
#define c8_asiclz()  __C8_____("c8.asiclz");
#define c8_asicsf()  __C8_____("c8.asicsf");
#define c8_asicff()  __C8_____("c8.asicff");
#define c8_asices()  __C8_____("c8.asices");

#define get_sp() __C8___R1_("l.ori");
#define get_lr() __C8___R9_("l.ori");

#endif // __AEON_SIMD_H

