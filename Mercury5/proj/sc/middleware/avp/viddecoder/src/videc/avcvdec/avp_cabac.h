
/*!
 ***************************************************************************
 * \file
 *    cabac.h
 *
 * \brief
 *    Headerfile for entropy coding routines
 *
 * \author
 *    Detlev Marpe                                                         \n
 *    Copyright (C) 2000 HEINRICH HERTZ INSTITUTE All Rights Reserved.
 *
 * \date
 *    21. Oct 2000 (Changes by Tobias Oelbaum 28.08.2001)
 ***************************************************************************
 */

#ifndef CABAC_H
#define CABAC_H

#include "avp_common.h"
#include "avp_avcPrivate.h"
#include "avp_defines.h"
#include "avp_videc_s.h"
#include "avp_ctx.h"

// I_MB_TYPE
// bit 0: skip bit
#define I_MB_BIT_INTRA16x16            0x1    //0
// bit 1: PCM
#define I_MB_BIT_PCM                   0x2
// bit 2: Intra16x16PredMode0
#define I_MB_BIT_INTRA16X16PREDNODE0   0x4
// bit 3: Intra16x16PredMode1
#define I_MB_BIT_INTRA16X16PREDNODE1   0x8
// bit 4(~7): luma_coded
#define I_MB_BIT_LUMA_CODED            0x10   //0xf0  //4
// bit 8: chroma cbp0
#define I_MB_BIT_CHROMA_CBP0           0x100
// bit 9: chroma cbp1
#define I_MB_BIT_CHROMA_CBP1           0x200

#define I_MB_PCM                       (I_MB_BIT_PCM | I_MB_BIT_INTRA16x16)
//used for ken in define MB_TYPE_OPTIMIZE

//int ae_v(int bs/*,SyntaxElement *sym*/);
int ae_v_I_MB_type(AVC_HANDLE *hp, avc_header* hdra, PBUF* RESTRICT pbuf);
int ae_v_P_skip_mb_type(/*AVC_HANDLE *hp,*/ avc_header *hdra, int mb_xpos, PBUF* RESTRICT pbuf);
//int ae_v_P_MB_type(avc_header* hdra, PBUF* RESTRICT pbuf);
int ae_v_B_skip_mb_type(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
#if 1
int ae_v_B_B8_type_CABAC(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
#else
int ae_v_B_B8_type_CABAC(avc_header *hdra, PBUF *RESTRICT pbuf);
#endif
int ae_v_I4_I8_PredMode(avc_header *hdra, PBUF* RESTRICT pbuf);
int ae_v_CIPredMode_CABAC(/*AVC_HANDLE *hp,*/ avc_header *hdra, int mb_xpos, PBUF* RESTRICT pbuf);
int ae_v_CBP_CABAC(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
int ae_v_Dquant_CABAC(BITSBUF *bs, avc_header *hdra, PBUF* RESTRICT pbuf);

#ifdef SUPPORT_AVC2
int ae_v_transform_size(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
#endif

void read_significance_map_coeff_DC(avc_header *hdra, BiContextTypePtr ctx_head, int i_1, BITSBUF *bs, /*int type,*/ int16 *RESTRICT coeff, const uint8 *RESTRICT scan, PBUF *RESTRICT pbuf);

int read_significance_map_coeff_AC(avc_header *hdra, BITSBUF *bs, int type, int16*RESTRICT coeff, const uint8 *RESTRICT scan,
                                   uint32 dequant_line, PBUF *RESTRICT pbuf
#ifdef SUPPORT_AVC2
                                   , uint8* ptMatrix
#endif
                                          );

#ifdef SUPPORT_AVC2
int read_significance_map_coeff_8x8(avc_header *hdra, BITSBUF *bs, int16 *RESTRICT coeff, const uint8 *RESTRICT scan,
                                   uint32 dequant_line_0, uint32 dequant_line_1, PBUF *RESTRICT pbuf, uint8* ptMatrix);
#endif

unsigned int biari_decode_symbol(DecodingEnvironment *de_cabac, BiContextTypePtr bi_ct, PBUF *RESTRICT pbuf);
unsigned int unary_exp_golomb_mv_decode(BITSBUF *bs, DecodingEnvironment *de_cabac, BiContextTypePtr ctx, PBUF *RESTRICT pbuf);

int ae_v_P_B8_type_CABAC(avc_header *hdra, PBUF* RESTRICT pbuf);
int ae_v_MVD_CABAC(/*AVC_HANDLE *hp,*/ avc_header *hdra, BITSBUF *bs, u8pair *mvd, int blk_x, int blk_y, PBUF* RESTRICT pbuf);
//int ae_v_RefFrame_CABAC(AVC_HANDLE *hp, avc_header *hdra, /*int bs,*/ int blk_x, int blk_y);
int ae_v_RefFrame_CABAC(AVC_HANDLE *hp, avc_header *hdra, int blk_x, int blk_y, PBUF* RESTRICT pbuf);
int ae_v_RefFrame_B_CABAC(AVC_HANDLE *hp, avc_header *hdra, int8* refframe_array, int blk_x, int blk_y, PBUF* RESTRICT pbuf);

////////////////////// for MBAFF //////////////////////////////
int ae_v_field_CABAC_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
int ae_v_MVD_CABAC_mbaff(/*AVC_HANDLE *hp,*/ avc_header *hdra, BITSBUF *bs, u8pair *mvd, int blk_x, int blk_y, PBUF *RESTRICT pbuf);
int ae_v_P_skip_mb_type_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
int ae_v_B_skip_field(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
int ae_v_B_mb_type(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
int ae_v_CIPredMode_CABAC_mbaff(/*AVC_HANDLE *hp,*/ avc_header* hdra, int mb_xpos, PBUF *RESTRICT pbuf);
int ae_v_RefFrame_CABAC_mbaff(AVC_HANDLE *hp, avc_header *hdra, int blk_x, int blk_y, PBUF *RESTRICT pbuf);
int ae_v_RefFrame_B_CABAC_mbaff(AVC_HANDLE *hp, avc_header *hdra, int8* refframe_array, int blk_x, int blk_y, PBUF *RESTRICT pbuf);
int ae_v_CBP_CABAC_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
int ae_v_I_MB_type_mbaff(AVC_HANDLE *hp, avc_header* hdra, PBUF *RESTRICT pbuf);
#ifdef SUPPORT_AVC2
int ae_v_transform_size_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF *RESTRICT pbuf);
#endif

#endif  // CABAC_H
