/**
 * \file    mae_font_ext.h
 * \brief   The document describes the IFontExt interface
 *
 * @version
 */

#ifndef __MAE_FONT_EXT_H__
#define __MAE_FONT_EXT_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_font.h"

/******************************/
/*        DEFINITION          */
/******************************/

#define INHERIT_IFontExt(IName) \
	INHERIT_IBase(IName); \
	u32     (*DrawText)      (IFontExt*, u32, u32, IBITMAP*, s32, s32, const u16*, u32, RGBColor_t, RGBColor_t, const Rect_t*, u32); \
	MAE_Ret (*MeasureText)   (IFontExt*, u32, u32,const u16*, u32, u32, u32*, u32*, u32, u32, boolean); \
	MAE_Ret (*MeasurePartialText) (IFontExt*, u32,u32, const u16*, u32, u32, u32, u32, u32*, u32*, u32, u32, boolean); \
	MAE_Ret (*GetInfo)       (IFontExt*, u32, u32,u32, FontInfo*); \
	MAE_Ret (*SetFontBase)   (IFontExt*, FontBase_t*); \
	FontBase_t* (*GetFontBase)   (IFontExt*)

DEFINE_INTERFACE(IFontExt);

#define IFONTEXT_QueryInterface(p1,id,pp,pOwner)   GET_FUNCTBL(p1,IFontExt)->QueryInterface(p1,id,pp,pOwner)
#define IFONTEXT_DrawText(_pIFontExt,_FontCat,FontSize,_pDst,_x,_y,_pcText,_nChars,_fg,_outline,_pRect,_Type) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->DrawText(_pIFontExt,_FontCat,FontSize,_pDst,_x,_y,_pcText,_nChars,_fg,_outline,_pRect,_Type)
#define IFONTEXT_MeasureText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->MeasureText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,FALSE,FALSE)
#define IFONTEXT_MeasurePartialText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->MeasurePartialText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,FALSE,FALSE)
#define IFONTEXT_MeasureTextEx(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->MeasureText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr)
#define IFONTEXT_MeasurePartialTextEx(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->MeasurePartialText(_pIFontExt,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr)
#define IFONTEXT_GetInfo(_pIFontExt,_FontCat,FontSize,_pinfo) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->GetInfo(_pIFontExt,_FontCat,FontSize,0,_pinfo)
#define IFONTEXT_GetInfoEx(_pIFontExt,_FontCat,FontSize,_FontType,_pinfo) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->GetInfo(_pIFontExt,_FontCat,FontSize,_FontType,_pinfo)
#define IFONTEXT_SetFontBase(_pIFontExt,_pFontBase) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->SetFontBase(_pIFontExt,_pFontBase)
#define IFONTEXT_GetFontBase(_pIFontExt) \
			GET_FUNCTBL(_pIFontExt,IFontExt)->GetFontBase(_pIFontExt)

/* Macros */
#define IFONT_TO_IFONTEXT(p) ((IFontExt*)p)
#define IFONTEXT_TO_IFONT(p) ((IFont*)p)


#endif /* __MAE_FONT_EXT_H__ */

