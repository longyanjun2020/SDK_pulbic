/*!
*  @file mmi_mae_bitmap_base.h
*
*  @This file contains the IBITMAP API.
*
*  @author SteveLee@MStar
*  @version $Id: mmi_mae_bitmap_base.h 291 2009-02-27 13:08:01Z kenny.wu $
*/

#ifndef __MMI_MAE_BITMAP_BASE_H__
#define __MMI_MAE_BITMAP_BASE_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_dib_forward.h"
#include "mmi_mae_bitmap_forward.h"
#include "mmi_mae_graphic_forward.h"

/******************************/
/*        DEFINITION          */
/******************************/



/* Bmp create/free functions */
MAE_Ret BITMAPBASE_NewFromBmpinfo(BitmapBase_t **ppBmp, BitmapInfo *pInfo);
void BITMAPBASE_Release(BitmapBase_t *pBmp);
/* Bmp API */
MAE_Ret BITMAPBASE_GetInfo(BitmapBase_t *pBmp, BitmapInfo *pinfo);
MAE_Ret BITMAPBASE_GetPixel(BitmapBase_t *pBmp, u32 x, u32 y, RGBColor_t *pColor);
MAE_Ret BITMAPBASE_SetPixel(BitmapBase_t *pBmp, u32 x, u32 y, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret BITMAPBASE_SetPixels(BitmapBase_t *pBmp, u32 nCnt, Point_t *pPoint, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret BITMAPBASE_GetTransType(BitmapBase_t *pBmp, u32 *pType);
MAE_Ret BITMAPBASE_SetTransType(BitmapBase_t *pBmp, u32 nType);
MAE_Ret BITMAPBASE_GetTransColor(BitmapBase_t *pBmp, RGBColor_t *pColor);
MAE_Ret BITMAPBASE_SetTransColor(BitmapBase_t *pBmp, RGBColor_t *pColor);
MAE_Ret BITMAPBASE_GetTransMask(BitmapBase_t *pBmp, u8 **ppMask, u32 *pSize);
//static s32 _BmpBase_GetTransMaskSize(BitmapBase *pBmp, u32 *pSize);
MAE_Ret BITMAPBASE_SetTransMask(BitmapBase_t *pBmp, u32 nBits, u8 *pMask, u32 nSize);
MAE_Ret BITMAPBASE_CreateAlphaMask(BitmapBase_t *pBmp, u8 nInitValue);
MAE_Ret BITMAPBASE_GetTransparency(BitmapBase_t *pBmp, u8 *pTransparency);
MAE_Ret BITMAPBASE_SetTransparency(BitmapBase_t *pBmp, u8 nTransparency);
MAE_Ret BITMAPBASE_DrawHLine(BitmapBase_t *pBmp, u32 x, u32 y, u32 nLen, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret BITMAPBASE_DrawVLine(BitmapBase_t *pBmp, u32 x, u32 y, u32 nLen, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret BITMAPBASE_FillRect(BitmapBase_t *pBmp, const Rect_t *pRect, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret BITMAPBASE_BltIn(BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop);
MAE_Ret BITMAPBASE_BltInEx(BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType);
MAE_Ret BITMAPBASE_BltInFadeOut (BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc, FadeoutLevel_t nLevel);
MAE_Ret BITMAPBASE_DimensionSwitch(BitmapBase_t * pBmp);
MAE_Ret BITMAPBASE_GetDirtyArea(BitmapBase_t *pBmp, Rect_t *pDrtRc);
MAE_Ret BITMAPBASE_SetDirtyArea(BitmapBase_t *pBmp, Rect_t *pDrtRc);

MAE_Ret BITMAPBASE_NewFromDib(BitmapBase_t **ppBmp, pDIB pDib);
MAE_Ret BITMAPBASE_NewFromDibEx(BitmapBase_t **ppBmp, pDIB pDib, boolean bFreeDib);
MAE_Ret BITMAPBASE_GetDib(BitmapBase_t *pBmp, void **ppObj);

MAE_Ret BITMAPBASE_ConvertFormat(BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc);
MAE_Ret BITMAPBASE_ChangeFormat(BitmapBase_t *pBmpDst, BitmapBase_t *pBmpSrc);
MAE_Ret BITMAPBASE_GenerateAlphaMask(BitmapBase_t *pBmp, u8 *pMsk, u32 stride, u32 size);
MAE_Ret BITMAPBASE_SetGradientAlphaMask(BitmapBase_t *pBmp, u32 nDir, u8 nMaxAlpha, u8 nMinAlpha);

MAE_Ret BITMAPBASE_StretchBlt(BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType);
MAE_Ret BITMAPBASE_PerspectiveBlt(BitmapBase_t *pBmp, const Rect_t *pDstRc, BitmapBase_t *pBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType, u16 nDir);

MAE_Ret BITMAPBASE_BltL8ToBmp(BitmapBase_t *pDst, Rect_t *pDstRc, u8* plain, u16 width, u16 pitch, u16 height, Rect_t *pSrcRc, RGBColor_t ClrFG);
void BITMAPBASE_SetPalette(BitmapBase_t *pBmp, RGBColor_t *pPalette, u32 cnt);

#endif //__MAE_BITMAP_BASE_H__

