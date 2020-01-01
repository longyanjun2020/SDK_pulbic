#ifndef AVC_PRED_H
#define AVC_PRED_H

#include "avp_defines.h"
#include "avp_mbuffer.h"

#ifdef INTRA_LEFT_TOP
//extern void (*intra_pred_4x4[9])(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void intra_pred_mode0(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode1(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode2(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode3(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode4(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode5(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode6(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode7(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);
void intra_pred_mode8(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix, uchar *pTop, uchar upper_left);

//extern void (*intra_pred_16x16[4])(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_16x16_VERT(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uint32 l_pix3, uint32 l_pix4, uchar *pTop, uchar upper_left);
void intra_pred_16x16_HOR(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uint32 l_pix3, uint32 l_pix4, uchar *pTop, uchar upper_left);
void intra_pred_16x16_DC(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uint32 l_pix3, uint32 l_pix4, uchar *pTop, uchar upper_left);
void intra_pred_16x16_PLANE(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uint32 l_pix3, uint32 l_pix4, uchar *pTop, uchar upper_left);

//extern void (*intra_pred_8x8[4])(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_chroma_DC(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail, uint32 l_pix_u1, uint32 l_pix_u2, uint32 l_pix_v1, uint32 l_pix_v2, uchar *pTop_u, uchar *pTop_v, uchar upper_left_u, uchar upper_left_v);
void intra_pred_chroma_HOR(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail, uint32 l_pix_u1, uint32 l_pix_u2 , uint32 l_pix_v1, uint32 l_pix_v2, uchar *pTop_u, uchar *pTop_v, uchar upper_left_u, uchar upper_left_v);
void intra_pred_chroma_VERT(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail, uint32 l_pix_u1, uint32 l_pix_u2 , uint32 l_pix_v1, uint32 l_pix_v2, uchar *pTop_u, uchar *pTop_v, uchar upper_left_u, uchar upper_left_v);
void intra_pred_chroma_PLANE(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail, uint32 l_pix_u1, uint32 l_pix_u2 , uint32 l_pix_v1, uint32 l_pix_v2, uchar *pTop_u, uchar *pTop_v, uchar upper_left_u, uchar upper_left_v);

#ifdef SUPPORT_AVC2
/*********************************************************************************/
/* The below is high-profile tools */
/*********************************************************************************/
void intra_pred_8x8_mode0(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode1(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode2(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode3(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode4(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode5(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode6(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode7(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
void intra_pred_8x8_mode8(uchar* RESTRICT pCurr, int stride, int blk_avail, uint32 l_pix1, uint32 l_pix2, uchar *pTop, uchar upper_left);
#endif

#else // INTRA_LEFT
//extern void (*intra_pred_4x4[9])(AVC_HANDLE* hp, uchar* pCurr, int stride, int blk_x, int blk_y);
void ATTR_INST16 intra_pred_mode0(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode1(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode2(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode3(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode4(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode5(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode6(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode7(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_mode8(uchar* RESTRICT pCurr, int stride, int blk_avail);

//extern void (*intra_pred_16x16[4])(AVC_HANDLE* hp, uchar* pCurr, int stride);
void ATTR_INST16 intra_pred_16x16_VERT(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_16x16_HOR(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_16x16_DC(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_16x16_PLANE(uchar* RESTRICT pCurr, int stride, int blk_avail);

//extern void (*intra_pred_8x8[4])(AVC_HANDLE* hp, uchar* pCurr, int stride);
void intra_pred_chroma_DC(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail);
void intra_pred_chroma_HOR(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail);
void ATTR_INST16 intra_pred_chroma_VERT(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail);
void intra_pred_chroma_PLANE(uchar* RESTRICT pCurr_u, uchar* RESTRICT pCurr_v, int stride, int blk_avail);

#ifdef SUPPORT_AVC2
/*********************************************************************************/
/* The below is high-profile tools */
/*********************************************************************************/
void intra_pred_8x8_mode0(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode1(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode2(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode3(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode4(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode5(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode6(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode7(uchar* RESTRICT pCurr, int stride, int blk_avail);
void intra_pred_8x8_mode8(uchar* RESTRICT pCurr, int stride, int blk_avail);
#endif
#endif // INTRA_LEFT
#endif
