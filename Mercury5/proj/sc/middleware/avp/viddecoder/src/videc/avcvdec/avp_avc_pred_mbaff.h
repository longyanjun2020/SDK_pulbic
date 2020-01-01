#ifndef AVC_PRED_MBAFF_H
#define AVC_PRED_MBAFF_H

#include "avp_defines.h"
#include "avp_mbuffer.h"

//int  intrapred(AVC_HANDLE *hp, int i4,int j4, int stride, uint8 predmode);
//void intrapred_chroma(AVC_HANDLE *hp, int uv, uint8 predmode);
//int  intrapred_luma_16x16(AVC_HANDLE *hp, uint8 predmode);

extern void (*intra_pred_4x4_mbaff[9])(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode0_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode1_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode2_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode3_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode4_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode5_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode6_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode7_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode8_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);

extern void (*intra_pred_16x16_mbaff[4])(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_16x16_VERT_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_16x16_HOR_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_16x16_DC_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_16x16_PLANE_mbaff(AVC_HANDLE* hp, uchar* pCurr, int stride);

extern void (*intra_pred_chroma_mbaff[4])(AVC_HANDLE* hp, uchar* pCurr_u, uchar* pCurr_v,int stride);
void intra_pred_chroma_DC_mbaff(AVC_HANDLE* hp, uchar* pCurr_u,uchar* pCurr_v, int stride);
void intra_pred_chroma_HOR_mbaff(AVC_HANDLE* hp, uchar* pCurr_u, uchar* pCurr_v, int stride);
void intra_pred_chroma_VERT_mbaff(AVC_HANDLE* hp, uchar* pCurr_u, uchar* pCurr_v, int stride);
void intra_pred_chroma_PLANE_mbaff(AVC_HANDLE* hp, uchar* pCurr_u, uchar* pCurr_v, int stride);

#ifdef SUPPORT_AVC2
/*********************************************************************************/
/* The below is high-profile tools */
/*********************************************************************************/
extern void (*intra_pred_8x8_mbaff[9])(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode0_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode1_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode2_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode3_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode4_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode5_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode6_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode7_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_8x8_mode8_mbaff(AVC_HANDLE *hp, uchar* pCurr, int stride, int blk_x, int blk_y);
#endif

#endif
