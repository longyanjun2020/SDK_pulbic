#ifndef __MAE_3DEFFECT_COMMON_H__
#define __MAE_3DEFFECT_COMMON_H__

#if defined(__FEATURE_MGL__)
#include "mgl_core_matrix.h"

void _3deffect_common_rotateX(Matrix4x4Float *pModelView, mgl_float value);
void _3deffect_common_rotateY(Matrix4x4Float *pModelView, mgl_float value);
void _3deffect_common_rotateZ(Matrix4x4Float *pModelView, mgl_float value);

void _3deffect_common_drawBgImage(mgl_u32 nodeID, u32 nWallpaperId);
void _3deffect_common_drawBgImageByUrl(mgl_u32 nodeID, MAE_WChar *pWpUrl);
void _3deffect_common_DrawImage(IBITMAP *pCanvasBitmap, IBITMAP *pSrcBmp, Rect_t *pDispRect,
					            s32 dstX, s32 dstY, s32 dstW, s32 dstH);

#endif
#endif
