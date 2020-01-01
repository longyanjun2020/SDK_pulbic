#ifndef INTRA_PRED_HARDWARE_H
#define INTRA_PRED_HARDWARE_H

//#define NANOBLAZE
#ifdef NANOBLAZE
#include "avp_nb.h"
#define READ_INT8(a) GET_BITSI(a, 8)

#if 1
#define READ_INT16(a, b) \
{ \
    GET_BITSI(a, 8); \
    GET_BITSI(b, 8); \
    a = (a<<8) | b; \
}
#else
#define READ_INT16(a, b) \
{ \
    GET_BITSI(a, 8); \
    GET_BITSI(b, 8); \
    a = (b<<8) | a; \
}
#endif
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
#define MIN(a,b)        ((a) < (b) ? (a) : (b))
#define MUX(c, a, b)    ((c) ? (a) : (b))
#define UCLIPI(x, c) MIN(MAX((int16)(x), 0), (c))
#define FACTOR_2(a) ((a)+(a))
#define FACTOR_3(a) (((a)<<1)+(a))
#define FACTOR_4(a) ((a)<<2)
#define FACTOR_5(a) (((a)<<2)+(a))
#define FACTOR_7(a) (((a)<<3)-(a))
#define FACTOR_8(a) ((a)<<3)
#define FACTOR_17(a) (((a)<<4)+(a))

int16 intra_pred4x4_avc(int16 stride, int16 blk_avail, int16 pred_mode);
int16 decode_intra_pred_avc(int16 i);
int16 intra_pred16x16_avc(int16 stride, int16 blk_avail, int16 pred_mode);
int16 intra_pred_chroma_avc(int16 stride, int16 blk_avail, int16 pred_mode);
int16 intra_pred8x8_avc(int16 stride, int16 blk_avail, int16 pred_mode);
#else
/*
#include "avp_common.h"
int init_intra_pred();
int Finish_intra_pred();
int dump_intra_pred4x4_input(unsigned char* pCurr, int stride, int blk_avail, int pred_mode);
int dump_intra_pred16x16_input(unsigned char* pCurr, int stride, int blk_avail, int pred_mode);
int dump_intra_pred_chroma_input(unsigned char* pCb, unsigned char* pCr, int stride, int blk_avail, int pred_mode);
int dump_intra_pred_golden(unsigned char* pCurr, int stride, int size);
int16 intra_pred4x4_avc(unsigned char* pCurr, int16 stride, int16 blk_avail, int16 pred_mode);
int16 intra_pred16x16_avc(unsigned char* pCurr, int16 stride, int16 blk_avail, int16 pred_mode);
int16 intra_pred_chroma_avc(unsigned char* pCurr, int16 stride, int16 blk_avail, int16 pred_mode);
int16 intra_pred8x8_avc(unsigned char* pCurr, int16 stride, int16 blk_avail, int16 pred_mode);
*/
#endif

#endif
