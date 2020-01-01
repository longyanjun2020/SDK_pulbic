#ifndef DEC4X4T_H
#define DEC4X4T_H

#include "avp_rvtypes.h"
/*
 * 4x4 transform coefficients encoding.
 *
 * We attempt to group most frequently used combinations of events
 * (values of coefficients) into units called descriptors.
 *
 * Thus, for each block we will use a 4x4 descriptor
 * that combines most probable values of 4 lowest-frequency
 * coefficients with indicators of non-zero elements in
 * the remaining (high-frequency) 2x2 sub-blocks.
 *
 * In turn, if any of these 2x2 sub-blocks is coded, it is being
 * represented by another descriptor, combining the most probable
 * values of each of the coefficients.
 *
 * If any of the coefficints is larger than levels included
 * in the descriptor, it is being encoded separately as
 * <level + sign> pair, where level is the (relative) absolute
 * value of the coefficient, and sign is a bit indicating whether
 * the coefficient is positive or negative.
 */
//#define USE_DECOMP_TABLE

/* extra level descriptor: */
#define MAX_EXTRA_LEVEL 23
#define MAX_EXTRA_BITS  8

/* abs. value (level) of quantized transform coefficients: */
#define MAX_LEVEL       (MAX_EXTRA_LEVEL + (1 << (MAX_EXTRA_BITS+1)) ) // 23 + 1<<(8+1) = 23 + 512 = 535

/* the number of level_dsc codewords: */
#define MAX_LEVEL_DSC   (MAX_EXTRA_LEVEL+MAX_EXTRA_BITS+1) //23+8+1=32

/*
 * Block descriptors and level thresholds:
 *
 * 2x2 block descriptor:     l0 values:
 *                             0 -> l0 = 0
 *  l0 | l1                    1 -> abs(l0) = 1
 *  ---+---                    2 -> abs(l0) = 2
 *  l2 | l3                    3 -> abs(l0) >= 3
 *
 * 4x4 block descriptor:     l1..3 values:
 *                             0 -> lx = 0
 *  l0 | l1 |                  1 -> abs(lx) = 1
 *  ---+----|   l4             2 -> abs(lx) >= 2
 *  l2 | l3 |
 *  --------+---------       l4..6 values:
 *          |                  0 -> lx = 0
 *    l5    |   l6             1 -> lx != 0
 *          |                      -> 2x2 descriptor to follow
 */
#define MAX_0_LEVEL     4
#define MAX_123_LEVEL   3
#define MAX_456_LEVEL   2

/* the number of 2x2 descriptor codewords: */
#define MAX_2x2_DSC             \
        (MAX_0_LEVEL * MAX_123_LEVEL * MAX_123_LEVEL * MAX_123_LEVEL)   /* 108 */

/* 4x4 descriptor: */
#define MAX_4x4_DSC             \
        (MAX_0_LEVEL * MAX_123_LEVEL * MAX_123_LEVEL * MAX_123_LEVEL \
            * MAX_456_LEVEL * MAX_456_LEVEL * MAX_456_LEVEL)            /* 864 */

/*
 * 8x8 block descriptors.
 *
 * These are the additional codewords that indicate which of
 * the 4x4 blocks in the 8x8 region are actually coded.
 */
#define MAX_8x8_DSC 16

/*
 * CBP macroblock descriptor:
 *
 *    y0  | y1    yi values:
 *        |         0 -> the corresponding 8x8 luma block not coded
 *  ------+------   1 -> 8x8 descriptor to follow
 *    y2  | y3
 *        |
 *  +             ci values:
 *     c0 | c1      0 -> cr[i] = 0 and cb[i] = 0
 *     ---+---      1 -> (cr[i] = 0 & cb[i] != 0) or (cr[i] != 0 & cb[i] = 0)
 *     c2 | c3         -> 1 bit to follow
 *                  2 -> cr[i]!=0 and cb[i]!=0
 */
#define MAX_CBP     (16*3*3*3*3)    /* 1296 */

/*
 * QP range partition
 *
 * In order to reduce # of tables, we partition
 * the range of all possible qp values into a set of
 * regions (which, in turn will be associated with the
 * corresponding set of tables).
 */

#define RVC_MAX_QP  31
#define MAX_INTRA_QP_REGIONS 5
#define MAX_INTER_QP_REGIONS 7

/* max. # of bits that can be retrieved at no extra cost: */
#define BS_MAXTRYBITS   16

/* maximum code length: */
#define MAX_DEPTH   16
#if MAX_DEPTH > BS_MAXTRYBITS
#error "BS_TRYBITS() must be able to process the longest codeword!!!"
#endif

/*
 * A set of compression/decompression tables for each
 * quantization range and frame type (intra/inter) modes:
 */

/* 4x4 descriptor tables: */
typedef struct {
    uint16 base [MAX_DEPTH];       // 0: unused, MAX_DEPTH: endpoint
    uint16 offset[MAX_DEPTH];      // 0: unused, MAX_DEPTH: unused
    unsigned short symbol [MAX_4x4_DSC];  //864
} _4x4_DSC_DECODE_TABLE; //2*16+2*16+2*864 = 1792 bytes

/* 2x2 descriptor table: */
typedef struct {
    uint16 base [MAX_DEPTH];
    uint16 offset[MAX_DEPTH];
    unsigned char symbol [MAX_2x2_DSC]; /* Flawfinder: ignore 108*/
} _2x2_DSC_DECODE_TABLE; //2*16+2*16+108 = 172 bytes

/* extra large levels table: */
typedef struct {
    uint16 base [MAX_DEPTH];
    uint16 offset[MAX_DEPTH];
    unsigned char symbol [MAX_LEVEL_DSC]; /* Flawfinder: ignore 32*/
} LEVEL_DSC_DECODE_TABLE; //2*16+2*16+32 = 96 bytes

/* CBP encoding/decoding tables: */
typedef struct
{
    /* CBP main descriptor: */
    struct {
        uint16 base [MAX_DEPTH];
        uint16 offset[MAX_DEPTH];
        unsigned short symbol [MAX_CBP];  // 1296
    } cbp; //2*16+2*16+2*1296 = 2656 bytes

    /* 8x8 descriptors: */
    struct {
        uint16 base [MAX_DEPTH];
        uint16 offset[MAX_DEPTH];
        unsigned char symbol [MAX_8x8_DSC]; /* Flawfinder: ignore 16 */
    } _8x8_dsc [4]; /* context = # of encoded 8x8 blocks - 1 */
    //2*16+2*16+16 = 80
} CBP_DECODE_TABLE;

/* combined encoding/decoding tables: */
typedef struct
{
    /* cbp tables: */
    CBP_DECODE_TABLE cbp [2];         /* 2 types of intra CBPs   */
	/* 1, if normal intra macroblock 2, if DC-removed intra macroblock */
    /* luma descriptors: */
    struct {
        _4x4_DSC_DECODE_TABLE _4x4_dsc[3]; /* 3 types of intra luma blocks!!! */
        _2x2_DSC_DECODE_TABLE _2x2_dsc[2];
    } luma;
    /* chroma descriptors: */
    struct {
        _4x4_DSC_DECODE_TABLE _4x4_dsc;
        _2x2_DSC_DECODE_TABLE _2x2_dsc[2];
    } chroma;
    /* extra levels: */
    LEVEL_DSC_DECODE_TABLE level_dsc;

} INTRA_DECODE_TABLES;

typedef struct
{
    /* cbp table: */
    CBP_DECODE_TABLE cbp;
    /* luma descriptors: */
    struct {
        _4x4_DSC_DECODE_TABLE _4x4_dsc;
        _2x2_DSC_DECODE_TABLE _2x2_dsc[2];
    } luma;
    /* chroma descriptors: */
    struct {
        _4x4_DSC_DECODE_TABLE _4x4_dsc;
        _2x2_DSC_DECODE_TABLE _2x2_dsc[2];
    } chroma;
    /* extra levels: */
    LEVEL_DSC_DECODE_TABLE level_dsc;

} INTER_DECODE_TABLES;

extern const uint8 intra_qp_to_idx[RVC_MAX_QP + 1];
extern const uint8 inter_qp_to_idx[RVC_MAX_QP + 1];

#endif
