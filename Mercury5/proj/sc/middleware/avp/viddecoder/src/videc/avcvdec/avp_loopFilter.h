#ifndef  LOOPFILTER_H
#define  LOOPFILTER_H

#include "avp_common.h"
#include "avp_avcPrivate.h"
#include "avp_defines.h"

#define DIR_VERT   1//0
#define DIR_HORI   0//1


#ifdef AVC_ROW_DEBLOCK
void avc_filter_mb_row(AVC_HANDLE *hp, avc_header *hdra, int by);
#endif

void ATTR_INST16 DeblockFrame(AVC_HANDLE *hp, avc_header *hdra, uint8 **imgYUV);

void DeblockFrame_mbaff(AVC_HANDLE *hp, avc_header *hdra, uint8 **imgYUV);

#ifdef MB_GETSTRENGTH
void GetStrength_ALL(avc_header *hdra, uint8 * RESTRICT ref_idx_row, mvpair * RESTRICT mv_row,
                     int mb_width, int MbQ_cbp_blk, int field_mb,
                     uint32 * RESTRICT StrengthVH, int MbP_cbp_blk, int MbP2_cbp_blk,
                     int mb_type, int leftmb_type, int topmb_type);
#else
void ATTR_INST16_M2 GetStrength_ALL(StorablePicture *listX[][ALLOC_STOREABLE_PIC_POOL],
                     uint8 * RESTRICT list0_refIdxArr, mvpair * RESTRICT list0_mv,
                     uint8 * RESTRICT list1_refIdxArr, mvpair * RESTRICT list1_mv,
                     int mb_width, int MbQ_cbp_blk, int field_mb,
                     uint32 * RESTRICT StrengthVH, int MbP_cbp_blk, int MbP2_cbp_blk,
                     int mb_type, int leftmb_type, int topmb_type);
#endif
void ATTR_INST16_M2 GetStrength_B_ALL(StorablePicture *listX[][ALLOC_STOREABLE_PIC_POOL],
                     uint8 * RESTRICT list0_refIdxArr, mvpair * RESTRICT list0_mv,
                     uint8 * RESTRICT list1_refIdxArr, mvpair * RESTRICT list1_mv,
                     int mb_width, int MbQ_cbp_blk, int field_mb,
                     uint32 * RESTRICT StrengthVH, int MbP_cbp_blk, int MbP2_cbp_blk,
                     int mb_type, int leftmb_type, int topmb_type);
void LoopfilterMB(AVC_HANDLE *hp, avc_header *RESTRICT hdra);

#endif
