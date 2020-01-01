/**
* \file    mae_bitmap_priv.h
* \brief   The document describes the private data structure used in mae_bitmap.c
*
* @version $Id: mae_bitmap_priv.h 291 2009-02-27 13:08:01Z kenny.wu $
*/
#ifndef __MAE_BITMAP_PRIV_H__
#define __MAE_BITMAP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mae_bitmap_ext.h"

typedef struct
{
	DECLARE_FUNCTBL(IBitmap);
	u32         nRefCnt;
	BitmapBase_t *pBitmapBase;
	boolean     bNeedFreeBase;  ///< If the BitmapBase is manually insert, set to FALSE
	BitmapReleaseNtfyElmnt_t *pReleaseNtfyData; ///<Object relase call back function

	///< reserved field which will be used if the instance is loaded into the resource cache
	///< it's the search key to identify stored instances in cache
	u32	aRCId[2];

}_Bitmap_t;

extern const u8 g_nBitMask[];
extern const u8 g_nRGB16_5to8[];
extern const u8 g_nRGB16_6to8[];
extern const u8 g_nAlpha8[];

/* General functions of all bmp format */
u32 Bmp_AddRef(IBitmapExt *pIbmp);
u32 Bmp_Release(IBitmapExt *pIbmp);
MAE_Ret Bmp_QueryInterface(IBitmapExt *pIbmp, MAE_IId nIId, void **ppObj, IBase*);
MAE_Ret Bmp_GetInfo(IBitmapExt *pIBmp, BitmapInfo *pInfo);
MAE_Ret Bmp_GetPixel(IBitmapExt *pIBmp, u32 x, u32 y, RGBColor_t *pColor);
MAE_Ret Bmp_SetPixel(IBitmapExt *pIBmp, u32 x, u32 y, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret Bmp_SetPixels(IBitmapExt *pIBmp, u32 nCnt, Point_t *pPoint, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret Bmp_GetTransInfo(IBitmapExt *pIBmp, TransparentInfo_t *pInfo);
MAE_Ret Bmp_SetTransInfo(IBitmapExt *pIBmp, TransparentInfo_t *pInfo);
MAE_Ret Bmp_GetTransType(IBitmapExt *pIBmp, u32 *pType);
MAE_Ret Bmp_SetTransType(IBitmapExt *pIBmp, u32 nType);
MAE_Ret Bmp_GetTransColor(IBitmapExt *pIBmp, RGBColor_t *pColor);
MAE_Ret Bmp_SetTransColor(IBitmapExt *pIBmp, RGBColor_t *pColor);
MAE_Ret Bmp_GetTransMask(IBitmapExt *pIBmp, u8 **ppMask, u32 *pSize);
//static s32 _Bmp_GetTransMaskSize(IBitmapExt *pIBmp, u32 *pSize);
MAE_Ret Bmp_SetTransMask(IBitmapExt *pIBmp, u32 nType, u8 *pMask, u32 nSize);
MAE_Ret Bmp_CreateAlphaMask(IBitmapExt *pIBmp, u8 nInitValue);
MAE_Ret Bmp_GetTransparency(IBitmapExt *pIBmp, u8 *pTransparency);
MAE_Ret Bmp_SetTransparency(IBitmapExt *pIBmp, u8 nTransparency);
MAE_Ret Bmp_DrawHLine(IBitmapExt *pIBmp, u32 x, u32 y, u32 nLen, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret Bmp_DrawVLine(IBitmapExt *pIBmp, u32 x, u32 y, u32 nLen, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret Bmp_FillRect(IBitmapExt *pIBmp, const Rect_t *pRect, RGBColor_t nColor, RasterOp_t nRop);
MAE_Ret Bmp_BltIn(IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop);
MAE_Ret Bmp_BltInEx(IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType);
MAE_Ret Bmp_BltInFadeOut (IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, FadeoutLevel_t nLevel);
MAE_Ret Bmp_DimensionSwitch(IBitmapExt * pIBmp);
MAE_Ret Bmp_GetDirtyArea(IBitmapExt *pIBmp, Rect_t *pDrtRc);
MAE_Ret Bmp_SetDirtyArea(IBitmapExt *pIBmp, Rect_t *pDrtRc);
MAE_Ret Bmp_GetDib(IBitmapExt *pIBmp, void **ppObj);

MAE_Ret Bmp_RegisterReleaseNotify(IBitmapExt *pIBmp, PfnMAE_BitMapReleaseNotify pfnNotify, IBase* pObj);
MAE_Ret Bmp_DeregisterReleaseNotify(IBitmapExt *pIBmp, PfnMAE_BitMapReleaseNotify pfnNotify, IBase* pObj);

BitmapBase_t* Bmp_GetBitmapBase(IBitmapExt *pIBmp);

MAE_Ret Bmp_SetPalette(IBitmapExt *pIBmp, RGBColor_t *pPalette, u32 nCnt);
MAE_Ret Bmp_ConvertFormat(IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc);
MAE_Ret Bmp_GenerateAlphaMask(IBitmapExt *pIBmp, u8 *pMsk, u32 stride, u32 size);
MAE_Ret Bmp_SetGradientAlphaMask(IBitmapExt *pIBmp, u32 nDir, u8 nMaxAlpha, u8 nMinAlpha);

MAE_Ret Bmp_StretchBlt(IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType);
MAE_Ret Bmp_PerspectiveBlt(IBitmapExt *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType, u16 nDir);

/* Utilities */
void Bmp_Free(_Bitmap_t*);

#endif //__MAE_BITMAP_PRIV_H__
