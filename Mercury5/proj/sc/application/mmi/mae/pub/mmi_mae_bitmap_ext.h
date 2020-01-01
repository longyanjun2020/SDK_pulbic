/**
 * \file    mmi_mae_bitmap_ext.h
 * \brief   The document describes the IBitmapExt interface
 *
 * @version $Id: mmi_mae_bitmap_ext.h $
 */
#ifndef __MMI_MAE_BITMAP_EXT_H__
#define __MMI_MAE_BITMAP_EXT_H__

#include "mmi_mae_bitmap.h"
#include "mmi_mae_forward.h"

typedef void (*PfnMAE_BitMapReleaseNotify)(IBITMAPEXT*, IBASE*);
typedef struct
{
	PfnMAE_BitMapReleaseNotify	 pfnReleaseFnNotify;
	IBase *pObj;
}BitmapReleaseNtfyElmnt_t;


#define INHERIT_IBitmapExt(IName) \
    INHERIT_IBitmap(IName); \
	MAE_Ret     (*BltInEx) (IName *pIBmp, const Rect_t *pDstRc, IBitmap *pIBmpSrc, const Rect_t *pSrcRc, RasterOp_t nRop, u32 nType); \
	MAE_Ret     (*BltInFadeOut)(IName *pIBmp, const Rect_t*, IBitmap*, const Rect_t*, FadeoutLevel_t nLevel); \
	MAE_Ret     (*DimensionSwitch) (IName *pIBmp); \
	MAE_Ret     (*GetDirtyArea)(IName *pIBmp, Rect_t *pDrtRc); \
	MAE_Ret     (*SetDirtyArea)(IName *pIBmp, Rect_t *pDrtRc);\
	MAE_Ret		(*RegReleaseNotify)(IName *pIBmp, PfnMAE_BitMapReleaseNotify pfnNotify, IBase* pObj);\
	MAE_Ret		(*DeregReleaseNotify)(IName *pIBmp, PfnMAE_BitMapReleaseNotify pfnNotify, IBase* pObj);\
	BitmapBase_t *(*GetBitmapBase)(IName *pIBmp);\
	MAE_Ret     (*SetPalette) (IName*,RGBColor_t *, u32);\
	MAE_Ret     (*ConvertFormat) (IName*, const Rect_t*, IBitmap*, const Rect_t*);\
	MAE_Ret		(*GenerateAlphaMask) (IName*, u8*, u32, u32)


DEFINE_INTERFACE(IBitmapExt);

/* Extension functions of IBitmap */
#define IBITMAP_BltInEx(pIbmp,pDstRc,pSrc,pSrcRc,nRop,t) \
        GET_FUNCTBL(pIbmp,IBitmapExt)->BltInEx(pIbmp,pDstRc,pSrc,pSrcRc,nRop,t)

/* Functions of IBitmapExt */
#define IBITMAPEXT_BltInFadeOut(pIbmp,pDstRc,pSrc,pSrcRc,nLevel) \
        GET_FUNCTBL(pIbmp,IBitmapExt)->BltInFadeOut(pIbmp,pDstRc,pSrc,pSrcRc,nLevel)
#define IBITMAPEXT_BltInWithMask(pIbmp,pDstRc,pSrc,pSrcRc,t,pm) \
        GET_FUNCTBL(pIbmp,IBitmapExt)->BltInWithMask(pIbmp,pDstRc,pSrc,pSrcRc,t,pm)
#define IBITMAPEXT_DimensionSwitch(pIbmp) GET_FUNCTBL(pIbmp,IBitmapExt)->DimensionSwitch(pIbmp)
#define IBITMAPEXT_GetDirtyArea(pIbmp, pRc) GET_FUNCTBL(pIbmp,IBitmapExt)->GetDirtyArea(pIbmp, pRc)
#define IBITMAPEXT_SetDirtyArea(pIbmp, pRc) GET_FUNCTBL(pIbmp,IBitmapExt)->SetDirtyArea(pIbmp, pRc)

#define IBITMAPEXT_RegReleaseNotify(pIbmp, pfnNotify, pObj) GET_FUNCTBL(pIbmp,IBitmapExt)->RegReleaseNotify(pIbmp, pfnNotify, pObj)
#define IBITMAPEXT_DeregReleaseNotify(pIbmp, pfnNotify, pObj) GET_FUNCTBL(pIbmp,IBitmapExt)->DeregReleaseNotify(pIbmp, pfnNotify, pObj)

#define IBITMAPEXT_GetBitmapBase(pIbmp) GET_FUNCTBL(pIbmp,IBitmapExt)->GetBitmapBase(pIbmp)

#define IBITMAPEXT_SetPalette(pIbmp,pColor,nCnt) GET_FUNCTBL(pIbmp,IBitmapExt)->SetPalette(pIbmp,pColor,nCnt)

#define IBITMAPEXT_ConvertFormat(pIbmp,pDstRc,pSrc,pSrcRc) GET_FUNCTBL(pIbmp,IBitmapExt)->ConvertFormat(pIbmp,pDstRc,pSrc,pSrcRc)
#define IBITMAPEXT_GenerateAlphaMask(pIbmp,pMsk,stride,size) GET_FUNCTBL(pIbmp,IBitmapExt)->GenerateAlphaMask(pIbmp,pMsk,stride,size)

/* Macros */
#define IBITMAP_TO_IBITMAPEXT(p) ((IBitmapExt*)p)
#define IBITMAPEXT_TO_IBITMAP(p) ((IBitmap*)p)

#endif /* __MMI_MAE_BITMAP_EXT_H__ */
