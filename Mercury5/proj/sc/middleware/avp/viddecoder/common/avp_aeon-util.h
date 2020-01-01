#ifndef AEON_UTIL_H
#define AEON_UTIL_H

#include "avp_common.h"
#include "avp_mvc_types.h"

#define VEC_NOP(x) MV_OR(x, x, x)
#ifdef _R2_DMA_
#define VEC_NOP_LD_DELAY(x)  MV_OR(x, x, x)
#else
#define VEC_NOP_LD_DELAY(x)  MV_OR(x, x, x)
#endif
#ifdef _AEON_V64_
typedef struct 
{
    union 
    {
        struct __attribute__((__packed__))
        {
            unsigned char u8_0_0  : 8;
            unsigned char u8_0_1  : 8;
            
            unsigned char u8_1_0  : 8;
            unsigned char u8_1_1  : 8;
            
            unsigned char u8_2_0  : 8;
            unsigned char u8_2_1  : 8;
            
            unsigned char u8_3_0  : 8;
            unsigned char u8_3_1  : 8;
            
            unsigned char u8_0_2  : 8;
            unsigned char u8_1_2  : 8;
            unsigned char u8_2_2  : 8;
            unsigned char u8_3_2  : 8;
            
            unsigned short u4_0    : 4;
            unsigned short u4_1    : 4;
            unsigned short u4_2    : 4;
            unsigned short u4_3    : 4;
            unsigned short dummy  : 16;
        } spr_def;
        struct __attribute__((__packed__))
        {
            unsigned short u0  : 16;
            unsigned short u1  : 16;
            unsigned short u2  : 16;
            unsigned short u3  : 16;
            
            unsigned char u8_0_2  : 8;
            unsigned char u8_1_2  : 8;
            unsigned char u8_2_2  : 8;
            unsigned char u8_3_2  : 8;
            
            unsigned short u4_0    : 4;
            unsigned short u4_1    : 4;
            unsigned short u4_2    : 4;
            unsigned short u4_3    : 4;
            unsigned short dummy  : 16;
        } spr_def_2;
        
        uint32_t u32[4];
    };
} mv_reg;

void print_vec_28(int vec);

#else

#define print_vec_28(v)

#endif

typedef struct aeon_const_s {
    uint64 pack32lo;
    uint64 pack32hi;
    uint64 pack16lo;
    uint64 pack16hi;
    uint64 packw2b;
    uint64 align8[9];
    uint64 pack1; // shortcut for unpacking unaligned position
    uint64 pack2;
    uint64 scratch[2];
    uint64 transpose1;
    uint64 transpose2;
    uint64 pack8hi;
    uint64 pack8low;
} aeon_const_st;

extern const aeon_const_st aeon_c;

#ifdef USE_QMEM

#include "avp_aeon_2ddma.h"

void copyblk2qmem(uint8 *dst, const uint8 *src, int w, int h, int s);
void copyblk2dram(uint8 *dst, const uint8 *src, int w, int h, int s);

#ifdef HAS_QMEM

#define QM_CONST_ADDR ((aeon_const_st *) ((uint8 *) qm_dma_addr_cpu + QM_BANK_SIZE - sizeof(aeon_const_st)))
#define QM_CONST(x) (QM_CONST_ADDR->x)
#ifdef _R2_DMA_
#define INIT_QMEM() { \
    vm_dbgTrace(_CUSAVP, "1 VQM_OWENER_SEL\n"); \
    VQM_OWENER_SEL(); \
    vm_dbgTrace(_CUSAVP, "1 REG_VQMEM_BASE\n"); \
    REG_VQMEM_BASE(); \
    vm_dbgTrace(_CUSAVP, "1 REG_VQMEM_MASK\n"); \
    REG_VQMEM_MASK(); \
    vm_dbgTrace(_CUSAVP, "1 VQMEM_EN\n"); \
    VQMEM_EN(); \
    vm_dbgTrace(_CUSAVP, "1 DMA2D_ENABLE\n"); \
    DMA2D_ENABLE(); \
    vm_dbgTrace(_CUSAVP, "1 copyblk2qmem\n"); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, &aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
    vm_dbgTrace(_CUSAVP, "1 QM_SWAP_BANK\n"); \
    QM_SWAP_BANK(); \
    vm_dbgTrace(_CUSAVP, "2 copyblk2qmem\n"); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, &aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
}
#else
#define INIT_QMEM() { \
    DMA2D_ENABLE(); \
    QM_RESET(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, (const uint8*)&aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
    QM_SWAP_BANK(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, (const uint8*)&aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
}
#endif

#else // HAS_QMEM

#define QM_CONST(x) (aeon_c.x)
#define INIT_QMEM() QM_RESET()

#endif

#else // USE_QMEM

#define copyblk2qmem(a, b, c, d, e) // nothing
#define copyblk2dram(a, b, c, d, e) // nothing
#define QM_CONST(x) (aeon_c.x)
#define INIT_QMEM() // nothing

#endif // USE_QMEM



#define NO_MSB -1
#define MSB_v0 0
#define MSB_v1 1
#define MSB_v2 2
#define MSB_v3 3
#define MSB_v4 4
#define MSB_v5 5
#define MSB_v6 6
#define MSB_v7 7
#define MSB_v8 NO_MSB
#define MSB_v9 NO_MSB
#define MSB_v10 NO_MSB
#define MSB_v11 NO_MSB
#define MSB_v12 NO_MSB
#define MSB_v13 NO_MSB
#define MSB_v14 NO_MSB
#define MSB_v15 NO_MSB
#define MSB_v16 NO_MSB
#define MSB_v17 NO_MSB
#define MSB_v18 NO_MSB
#define MSB_v19 NO_MSB
#define MSB_v20 NO_MSB
#define MSB_v21 NO_MSB
#define MSB_v22 NO_MSB
#define MSB_v23 NO_MSB
#define MSB_v24 NO_MSB
#define MSB_v25 NO_MSB
#define MSB_v26 NO_MSB
#define MSB_v27 NO_MSB
#define MSB_v28 NO_MSB
#define MSB_v29 NO_MSB
#define MSB_v30 NO_MSB
#define MSB_v31 NO_MSB

#ifdef _X86_

#define VEC2MSB(v) \
   ((&v == &v0) ? 0 : \
    (&v == &v1) ? 1 : \
    (&v == &v2) ? 2 : \
    (&v == &v3) ? 3 : \
    (&v == &v4) ? 4 : \
    (&v == &v5) ? 5 : \
    (&v == &v6) ? 6 : \
    (&v == &v7) ? 7 : 8) \

#define print_mvreg_V4HI(head,v) \
{ \
    vec64_ut temp; \
    *(__m64 *) &temp = v; \
    print_vec64_u16(head, temp, VEC2MSB(v)); \
}

#define print_mvreg_V8QI(head,v) \
{ \
    vec64_ut temp; \
    *(__m64 *) &temp = v; \
    print_vec64_u8(head, temp, VEC2MSB(v)); \
}

#elif defined(_AEON)

#include "avp_aeon-simd.h"

#define VectorRegister2VEC(vA)                      \
({                                                  \
    MV_SDV(QM_CONST(scratch), 0/*imm16*/, vA);      \
    (vec64_ut) QM_CONST(scratch[0]);})

#define print_mvreg_V4HI(head,v)    print_VEC_V4HI(head, VectorRegister2VEC(v), MSB_##v)
#define print_mvreg_V8QI(head,v)    print_VEC_V8QI(head, VectorRegister2VEC(v), MSB_##v)

#endif

void print_vec64_u16(char *head, vec64_ut v, int msb_id);
void print_vec64_u8 (char *head, vec64_ut v, int msb_id);

#endif
