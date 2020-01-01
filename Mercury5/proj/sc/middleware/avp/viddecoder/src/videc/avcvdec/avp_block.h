#ifndef BLOCK_H
#define BLOCK_H

#include "avp_common.h"

#ifdef CCIR656_CLIP
#define itrans_l_y(a, b, c)  itrans_l(a, b, c, 0)
#define itrans_l_c(a, b, c)  itrans_l(a, b, c, 1)
#define itrans_dc_y(a, b, c) itrans_dc(a, b, c, 0)
#define itrans_dc_c(a, b, c) itrans_dc(a, b, c, 1)
typedef void (*p_itrans)(short* block, uchar* dst, int stride, int type);
void ATTR_INST16 itrans_l(short* block, uchar* dst, int stride, int type);
void ATTR_INST16 itrans_dc(short* block, uchar* dst, int stride, int type);
#define ITRANS_ARG_C(a, b, c) a, b, c, 1
#else
#define itrans_l_y  itrans_l
#define itrans_l_c  itrans_l
#define itrans_dc_y itrans_dc
#define itrans_dc_c itrans_dc
typedef void (*p_itrans)(short* block, uchar* dst, int stride);
void ATTR_INST16 itrans_l(short* block, uchar* dst, int stride);
void ATTR_INST16 itrans_dc(short* block, uchar* dst, int stride);
#define ITRANS_ARG_C(a, b, c) a, b, c
#endif


uint32 ATTR_INST16 itrans_2(short* block, int32 coef, int32 bit_offset);

#ifdef SUPPORT_AVC2
void itrans_8x8(short* block, uchar* dst, int stride);
void itrans_8x8_dc(short* block, uchar* dst, int stride);
#endif

#endif
