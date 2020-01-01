/*
* Copyright (C) 2000-2010 Beijing Komoxo Inc.
* All rights reserved.
*/

#ifdef __MMI_SCRIPT_EASY__

#ifndef __KMX_FONT_H
#define __KMX_FONT_H

#include "mae_interface_def.h"
#include "mae_bitmap.h"
#include "mae_font_base.h"

#include "mmi_mae_font_kmx.h"

#define INHERIT_IKmxFont(IName)           \
    INHERIT_IBase(IName);                 \
    MAERet_t (*DrawText) (IName *pThis, IBitmap *pDst, u32 fontCate, u32 fontSize, u32 fontType, int x, int y, \
                          const MAE_WChar *pcText, int nChars, RGBColor_t fg, RGBColor_t bg, const Rect_t *prcClip);      \
    MAERet_t (*MeasureText) (IName *pThis, u32 fontCate, u32 fontSize, u32 fontType, const MAE_WChar *pcText, u32 nChars, \
                          u32 nMaxWidth, u32 *pnFits, u32 *pnPixels);      \
    MAERet_t (*GetInfo) (IName *pThis, u32 fontCate, u32 fontSize, u32 fontType, FontInfo_t *pinfo);     \
    u32 (*GetFontSize) (IName *pThis);                                    \
    MAERet_t (*SetTextColor) (IName *pThis, RGBColor_t text_color);       \
    MAERet_t (*SetBold) (IName *pThis, unsigned char bold);               \
    MAERet_t (*SetItalic) (IName *pThis, unsigned char italic);           \
    MAERet_t (*SetUnderline) (IName *pThis, unsigned char underline);     \
    MAERet_t (*SetBorder) (IName *pThis, boolean bValue, RGBColor_t rgb); \
    MAERet_t (*SetMultiline) (IName *pThis, boolean bValue);              \
    MAERet_t (*SetMarkup) (IName *pThis, boolean bValue)

DEFINE_INTERFACE(IKmxFont);

typedef struct
{
    DECLARE_FUNCTBL(IKmxFont);
    u32 RefCnt;
    SeDeviceContext dc;
} KmxFont_t;


MAE_Ret KmxFont_New(MAE_ClsId ClsID, void **ppObj);  /* ClsID is reserved */
u32 KmxFont_Release(IKmxFont *pIKmxFont);

#define IKmxFont_DrawText(pIKmxFont, pDst, fontCate, fontSize, fontType, x, y, pcText, nChars, fg, bg, prcClip) \
      GET_FUNCTBL(pIKmxFont,IKmxFont)->DrawText(pIKmxFont, pDst, fontCate, fontSize, fontType, x, y, pcText, nChars, fg, bg, prcClip)

#define IKmxFont_MeasureText(pIKmxFont, fontCate, fontSize, fontType, pcText, nChars, nMaxWidth, pnFits, pnPixels) \
      GET_FUNCTBL(pIKmxFont,IKmxFont)->MeasureText(pIKmxFont, fontCate, fontSize, fontType, pcText, nChars, nMaxWidth, pnFits, pnPixels)

#define IKmxFont_GetInfo(pIKmxFont, fontCate, fontSize, fontType, pinfo) \
      GET_FUNCTBL(pIKmxFont,IKmxFont)->GetInfo(pIKmxFont, fontCate, fontSize, fontType, pinfo)


#endif /* __KMX_FONT_H */
#endif/*__MMI_SCRIPT_EASY__*/

