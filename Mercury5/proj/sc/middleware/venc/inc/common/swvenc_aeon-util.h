#ifndef AEON_UTIL_H
#define AEON_UTIL_H

#include "swvenc_common.h"
#include "swvenc_deftypes.h"


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

        uint32 u32[4];
    };
} mv_reg;

typedef union vec32_u {
    uint32 u32;
    int32  i32;
    uint16 u16[2];
    int16  i16[2];
    uint8  u8 [4];
    int8   i8 [4];
} vec32_ut;

typedef union vec64_u {
    uint64 u64;
    int64  i64;
    uint32 u32[2];
    int32  i32[2];
    uint16 u16[4];
    int16  i16[4];
    uint8  u8 [8];
    int8   i8 [8];
} vec64_ut;


typedef struct aeon_const_s {
    uint64 pack32lo;
    uint64 pack32hi;
    uint64 pack16lo;
    uint64 pack16hi;
    uint64 packw2b;
    uint64 align8[9];
    uint64 pack1; // shortcut for unpacking unaligned position
    uint64 pack2;
    uint64 transpose1;
    uint64 transpose2;
    uint64 pack8hi;
    uint64 pack8lo;
    uint64 scratch[2];
} aeon_const_st;

extern const aeon_const_st aeon_c;

#ifdef USE_QMEM
#define QM_LOCAL_TMP_BASE ((uint8 *) (qm_dma_addr_cpu + QM_BANK_SIZE - sizeof(aeon_const_st)))
#define aeon_tmp ((uint8 *) ((void*)(QM_LOCAL_TMP_BASE - 8)))
#define aeon_tmp16 ((uint16 *) ((void*)(QM_LOCAL_TMP_BASE - 8*2 - 8)))
#define aeon_tmp64 ((uint64 *) ((void*)(QM_LOCAL_TMP_BASE - 8*6)))

#define aeon_tmp16_dct ((uint16 *) ((void*)(QM_LOCAL_TMP_BASE - 2*8*8*2)))
#define aeon_tmp32_dct ((uint32 *) ((void*)(QM_LOCAL_TMP_BASE - 2*8*8*2 - 4*8*4)))

#include "swvenc_aeon_2ddma.h"

void copyblk2qmem(uint8 *dst, const uint8 *src, int w, int h, int s);
void copyblk2dram(uint8 *dst, const uint8 *src, int w, int h, int s);

#ifdef HAS_QMEM

#define QM_CONST_ADDR ((aeon_const_st *) ((void*)((uint8 *) qm_dma_addr_cpu + QM_BANK_SIZE - sizeof(aeon_const_st))))
#define QM_CONST(x) (QM_CONST_ADDR->x)

#ifdef _R2_DMA_
#define INIT_QMEM() { \
    VQM_OWENER_SEL(); \
    VQMEM_EN(); \
    DMA2D_ENABLE(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, (uint8 *)&aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
    QM_SWAP_BANK(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, (uint8 *)&aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
}

#define DEINIT_QMEM() { \
    VQMEM_DI(); \
    DMA2D_DISABLE(); \
}
#else
#define INIT_QMEM() { \
    DMA2D_ENABLE(); \
    QM_RESET(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, &aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
    QM_SWAP_BANK(); \
    copyblk2qmem((uint8 *) QM_CONST_ADDR, &aeon_c, sizeof(aeon_const_st), 1, sizeof(aeon_const_st)); \
}
#define DEINIT_QMEM()
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

#include "aeon-simd.h"

#define VectorRegister2VEC(vA)                      \
({                                                  \
    MV_SDV(QM_CONST(scratch), 0/*imm16*/, vA);      \
    (vec64_ut) QM_CONST(scratch[0]);})

#define print_mvreg_V4HI(head,v)    print_vec64_u16(head, VectorRegister2VEC(v), v)
#define print_mvreg_V8QI(head,v)    print_vec64_u8 (head, VectorRegister2VEC(v), v)

#endif

void print_vec64_u16(char *head, vec64_ut v, int msb_id);
void print_vec64_u8 (char *head, vec64_ut v, int msb_id);

#ifdef AEON_SIM_QMEM_DEBUG
void diag_prinf_qmem(uint8* start, uint8 stride, uint8 height, uint8 data_type);
#endif

#endif
