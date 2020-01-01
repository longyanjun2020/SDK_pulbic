/**
 * @file mmi_mae_font.h
 *
 * @version $Id: mmi_mae_font.h 1643 2009-08-24 09:22:48Z bill.pan $
 */
#ifndef __MMI_MAE_FONT_H__
#define __MMI_MAE_FONT_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_font_forward.h"
#include "mmi_mae_graphic_forward.h"

#define INHERIT_IFont(IName) \
	INHERIT_IBase(IName); \
	u32     (*DrawText)      (IFont*, u32,u32, IBITMAP*, s32, s32, const u16*, u32, RGBColor_t, RGBColor_t, const Rect_t*, u32); \
	MAE_Ret (*MeasureText)   (IFont*, u32,u32, const u16*, u32, u32, u32*, u32*, u32, u32, boolean); \
	MAE_Ret (*MeasurePartialText) (IFont*, u32, u32, const u16*, u32, u32, u32, u32, u32*, u32*, u32, u32, boolean); \
	MAE_Ret (*GetInfo)       (IFont*, u32, u32, u32, FontInfo*)

DEFINE_INTERFACE(IFont);

#define IFONT_QueryInterface(p1,id,pp,pOwner)   GET_FUNCTBL(p1,IFont)->QueryInterface(p1,id,pp,pOwner)

/** 
 * MAE_Ret IFONT_DrawText(IFont        *pIFont,
 *                        u32           FontCat,
 *                        IBitmap      *pDst,
 *                        s32           x,
 *                        s32           y,
 *                        const u16    *pcText,
 *                        u32           nChars,
 *                        RGBColor_t    fg,
 *                        RGBColor_t    outline,
 *                        const Rect_t *pRect,
 *                        u32           Type)
 *
 *  @brief  This function draws the given text on the given bitmap.
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category
 *  @param  pDst             Pointer to the destination IBitmap
 *  @param  x                Start X coordinate
 *  @param  y                Start Y coordinate
 *  @param  pcText           Pointer to text string to draw
 *  @param  nChars           Number of charaters in the given text string
 *  @param  fg               Text color
 *  @param  outline          Outline color of the text
 *  @param  pRect            Client area to constrain the drawing
 *  @param  Type             Font type
 *
 *  @retval MAE_RET_SUCCESS        Success
 *  @retval MAE_RET_BAD_PARAM      Wrong parameter(s)
 *  @retval MAE_RET_FAILED         Other errors
 *
 */
#define IFONT_DrawText(_pIFont,_FontCat, FontSize,_pDst,_x,_y,_pcText,_nChars,_fg,_outline,_pRect,_Type) \
			GET_FUNCTBL(_pIFont,IFont)->DrawText(_pIFont,_FontCat,FontSize,_pDst,_x,_y,_pcText,_nChars,_fg,_outline,_pRect,_Type)

/** 
 * MAE_Ret IFONT_MeasureText(IFont        *pIFont,
 *                           u32           FontCat,
 *                           const u16    *pcText,
 *                           u32           nChars,
 *                           u32           nMaxWidth,
 *                           u32          *pnFits,
 *                           u32          *pnPixels, 
 *                           u32           Type)
 *
 *  @brief  This function measures pixel width of the given text
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category
 *  @param  pcText           Pointer to text string to draw
 *  @param  nChars           Number of charaters in the given text string
 *  @param  nMaxWidth        Max pixels to fit in
 *  @param  pnFits           Number of chars can fit in given width
 *  @param  pnPixels         Number of pixels of visible chars' width
 *  @param  Type             Font type
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 */
#define IFONT_MeasureText(_pIFont,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type) \
			GET_FUNCTBL(_pIFont,IFont)->MeasureText(_pIFont,_FontCat,FontSize, _pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,FALSE,FALSE)

/** 
 * MAE_Ret IFONT_MeasurePartialText(IFont        *pIFont,
 *                               u32           FontCat,
 *                               const u16    *pcText,
 *                               u32           nChars,
 *                               u32           nMaxWidth,
 *                               u32          *pnFits,
 *                               u32          *pnPixels, 
 *                               u32           Type)
 *
 *  @brief  This function measures pixel width of the partial string of the given text
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category
 *  @param  pcText           Pointer to text string to draw
 *  @param  nChars           Number of charaters in the given text string
 *  @param  nOffset          Starting offset to measure text
 *  @param  nSubLen          length of Meausere text
 *  @param  nMaxWidth        Max pixels to fit in
 *  @param  pnFits           Number of chars can fit in given width
 *  @param  pnPixels         Number of pixels of visible chars' width
 *  @param  Type             Font type
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 *
 *  @note If bSkip is TRUE, all unsupported chars will be ignore.
 */
#define IFONT_MeasurePartialText(_pIFont,_FontCat, FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type) \
            GET_FUNCTBL(_pIFont,IFont)->MeasurePartialText(_pIFont,_FontCat,FontSize, _pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,FALSE,FALSE) 


/** 
 * MAE_Ret IFONT_MeasureTextEx(IFont        *pIFont,
 *                             u32           FontCat,
 *                             const u16    *pcText,
 *                             u32           nChars,
 *                             u32           nMaxWidth,
 *                             u32          *pnFits,
 *                             u32          *pnPixels, 
 *                             u32           Type,
 *                             u32           bSkip,
                               boolean       bDispStr)
 *
 *  @brief  This function measures pixel width of the given text
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category
 *  @param  pcText           Pointer to text string to draw
 *  @param  nChars           Number of charaters in the given text string
 *  @param  nMaxWidth        Max pixels to fit in
 *  @param  pnFits           Number of chars can fit in given width
 *  @param  pnPixels         Number of pixels of visible chars' width
 *  @param  Type             Font type
 *  @param  bSkip            If skip unsupported chars
 *  @param  bDispStr         The strings is already handled by bidi and is a display form string
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 *
 *  @note If bSkip is TRUE, all unsupported chars will be ignore.
 */
#define IFONT_MeasureTextEx(_pIFont,_FontCat,FontSize,_pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr) \
			GET_FUNCTBL(_pIFont,IFont)->MeasureText(_pIFont,_FontCat,FontSize, _pcText,_nChars,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr)

/** 
 * MAE_Ret IFONT_MeasurePartialTextEx(IFont        *pIFont,
 *                                 u32           FontCat,
 *                                 const u16    *pcText,
 *                                 u32           nChars,
 *                                 u32           nMaxWidth,
 *                                 u32          *pnFits,
 *                                 u32          *pnPixels, 
 *                                 u32           Type,
 *                                 u32           bSkip,
                                   boolean       bDispStr)
 *
 *  @brief  This function measures pixel width of the partial string of the given text
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category
 *  @param  pcText           Pointer to text string to draw
 *  @param  nChars           Number of charaters in the given text string
 *  @param  nOffset          Starting offset to measure text
 *  @param  nSubLen          length of Meausere text
 *  @param  nMaxWidth        Max pixels to fit in
 *  @param  pnFits           Number of chars can fit in given width
 *  @param  pnPixels         Number of pixels of visible chars' width
 *  @param  Type             Font type
 *  @param  bSkip            If skip unsupported chars
 *  @param  bDispStr         The strings is already handled by bidi and is a display form string
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 *
 *  @note If bSkip is TRUE, all unsupported chars will be ignore.
 */
#define IFONT_MeasurePartialTextEx(_pIFont,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr) \
            GET_FUNCTBL(_pIFont,IFont)->MeasurePartialText(_pIFont,_FontCat,FontSize,_pcText,_nChars,_nOffset,_nSubLen,_nMaxWidth,_pnFits,_pnPixels,_Type,_bSkip,_bDispStr) 

/** 
 * MAE_Ret IFONT_GetInfo(IFont        *pIFont,
 *                       u32           FontCat,
 *                       FontInfo     *pinfo)
 *
 *  @brief  This function gets font info of the given font category
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category to query
 *  @param  pinfo            pointer to memory of FontInfo for return
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 */
#define IFONT_GetInfo(_pIFont,_FontCat,FontSize,_pinfo) \
			GET_FUNCTBL(_pIFont,IFont)->GetInfo(_pIFont,_FontCat,FontSize, 0,_pinfo)

/** 
 * MAE_Ret IFONT_GetInfoEx(IFont        *pIFont,
 *                         u32           FontCat,
 *                         u32           FontType
 *                         FontInfo     *pinfo)
 *
 *  @brief  This function gets font info of the given font category
 *   
 *  @param  pIFont           Pointer to the IFont Object
 *  @param  FontCat          Font category to query
 *  @param  FontType         Font type
 *  @param  pinfo            pointer to memory of FontInfo for return
 *
 *  @retval MAE_RET_SUCCESS       Success
 *  @retval MAE_RET_BAD_PARAM     Wrong parameter(s)
 *  @retval MAE_RET_NOT_SUPPORTED Unsupported
 */
#define IFONT_GetInfoEx(_pIFont,_FontCat,FontSize,_FontType,_pinfo) \
			GET_FUNCTBL(_pIFont,IFont)->GetInfo(_pIFont,_FontCat,FontSize,_FontType,_pinfo)

#endif /* __MAE_FONT_H__ */
