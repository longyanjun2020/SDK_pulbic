#ifndef _QUANTIZE_H_
#define _QUANTIZE_H_
#include "swvenc_deftypes.h"
#include "swvenc_h263venc.h"

extern const short gDcScalar[2][32];

// Quant
void _sw263v_QuantAndDequantIntra_H263(SW263V_t* ctx, MBINFO_t* pMbInfo, int16 *dstDQ, int16 *src, short dc_scalar, int block);
void _sw263v_QuantAndDequantInter_H263(SW263V_t* ctx, MBINFO_t* pMbInfo, int16 *dstDQ, int16 *src, Bool* dc_only, int is4x4, int block);

#endif //_QUANTIZE_H_
