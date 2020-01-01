/**
 * @file mmi_mae_display.h
 *
 * IDISPLAY interface
 *
 * @version $Id: mmi_mae_display.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */
#ifndef __MMI_MAE_DISPLAY_H__
#define __MMI_MAE_DISPLAY_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_display_types.h"
#include "mmi_mae_font_forward.h"

#ifdef __DISP_ML_MMI__
#define INHERIT_IDisplay(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret    (*SetProperty)      (IName*, u32, u32); \
	MAE_Ret    (*GetProperty)      (IName*, u32, void*); \
	MAE_Ret    (*SetDestination)   (IName*, IBITMAP*,IBase*); \
	IBITMAP*   (*GetDestination)   (IName*, IBASE*); \
	IFONT*     (*SetFont)          (IName*, IFONT*, IBase*); \
	MAE_Ret    (*GetFontInfo)      (IName*, u32, u32,u32, FontInfo*); \
	void       (*DrawRect)         (IName*, const Rect_t*, RGBColor_t, RGBColor_t, u32); \
	void       (*DrawLine)         (IName*, s32, s32, s32, s32, u8, DisplayDottedType_e); \
	MAE_Ret    (*MeasureText)      (IName*, u32,u32, const u16*, u32, u32, u32*, u32*, u32, boolean); \
	u32        (*DrawDispText)     (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32); \
	u32        (*DrawText)         (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32); \
	u32        (*DrawDispTextToBitmap) (IName*, IBITMAP*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
	u32        (*DrawTextToBitmap) (IName*, IBITMAP*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
	u32        (*DrawColorfulDispText) (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
	u32        (*DrawColorfulText) (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
	IBITMAP*   (*GetDeviceBitmap)  (IName*, IBase*); \
	IBITMAP*   (*CreateBitmap)     (IName*, u16, u16, IBase*); \
	RGBColor_t (*SetColor)         (IName*, u32, RGBColor_t); \
	void       (*ClearScreen)      (IName*); \
	void       (*Update)           (IName*, u32); \
	MAE_Ret    (*BitBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t); \
	void       (*DrawEllipse)      (IName*, const Ellipse_t*, RGBColor_t, RGBColor_t, u32); \
	void       (*DrawArc)          (IName*, const Arc_t*, RGBColor_t, RGBColor_t, u32); \
	MAERet_t   (*FadeOut)          (IName*, const Rect_t*, FadeoutLevel_t, Mae_FadeoutSourceType_e); \
	void       (*DrawTriangle)          (IName*, const Triangle_t*, RGBColor_t, RGBColor_t,u32);\
	MAERet_t   (*Set3DMode)     (IName*, boolean);\
	boolean      (*Get3DMode)     (IName*);\
    MAERet_t   (*SetG3DBuffer)     (IName*, G3DInfo_t*);\
    IBITMAP*   (*GetG3DBuffer)     (IName*);\
	MAERet_t   (*CreateLayer)      (IName*, DisplayLayer_e, u32, u32, u32); \
	MAERet_t   (*ReleaseLayer)     (IName*, DisplayLayer_e); \
	MAERet_t   (*SetCurrentLayer)  (IName*, DisplayLayer_e); \
	MAERet_t   (*SetLayerOffset)   (IName*, DisplayLayer_e, s32, s32); \
	MAERet_t   (*SetLayerVisible)  (IName*, DisplayLayer_e, u8); \
	MAERet_t   (*ReleaseAllLayer)  (IName*); \
	MAERet_t   (*GetLayerCARect) (IName*, Rect_t*, DisplayLayer_e); \
	MAE_Ret    (*StretchBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t); \
	MAE_Ret    (*PerspectiveBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t, u16)
#else
#define INHERIT_IDisplay(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret    (*SetProperty)      (IName*, u32, u32); \
	MAE_Ret    (*GetProperty)      (IName*, u32, void*); \
	MAE_Ret    (*SetDestination)   (IName*, IBITMAP*,IBase*); \
	IBITMAP*   (*GetDestination)   (IName*, IBase*); \
	IFONT*     (*SetFont)          (IName*, IFONT*, IBase*); \
	MAE_Ret    (*GetFontInfo)      (IName*, u32, u32,u32, FontInfo*); \
	void       (*DrawRect)         (IName*, const Rect_t*, RGBColor_t, RGBColor_t, u32); \
	void       (*DrawLine)         (IName*, s32, s32, s32, s32, u8, DisplayDottedType_e); \
	MAE_Ret    (*MeasureText)      (IName*, u32,u32, const u16*, u32, u32, u32*, u32*, u32, boolean); \
	u32        (*DrawDispText)     (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32); \
	u32        (*DrawText)         (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32); \
    u32        (*DrawDispTextToBitmap) (IName*, IBITMAP*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
    u32        (*DrawTextToBitmap) (IName*, IBITMAP*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
    u32        (*DrawColorfulDispText) (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
    u32        (*DrawColorfulText) (IName*, u32,u32, const u16*, s32, s32, s32, const Rect_t*, u32, u32*, u8); \
	IBITMAP*   (*GetDeviceBitmap)  (IName*, IBase*); \
	IBITMAP*   (*CreateBitmap)     (IName*, u16, u16, IBase*); \
	RGBColor_t (*SetColor)         (IName*, u32, RGBColor_t); \
	void       (*ClearScreen)      (IName*); \
	void       (*Update)           (IName*, u32); \
	MAE_Ret    (*BitBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t); \
	void       (*DrawEllipse)      (IName*, const Ellipse_t*, RGBColor_t, RGBColor_t, u32); \
	void       (*DrawArc)          (IName*, const Arc_t*, RGBColor_t, RGBColor_t, u32); \
	MAERet_t   (*FadeOut)          (IName*, const Rect_t*, FadeoutLevel_t, Mae_FadeoutSourceType_e); \
	void   (*DrawTriangle)          (IName*, const Triangle_t*, RGBColor_t, RGBColor_t,u32); \
	MAERet_t   (*Set3DMode)     (IName*, boolean);\
	boolean      (*Get3DMode)     (IName*);\
	MAE_Ret    (*StretchBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t); \
	MAE_Ret    (*PerspectiveBlt)           (IName*, const Rect_t*, const IBITMAP*, const Rect_t*, RasterOp_t, u16)
#endif
DEFINE_INTERFACE(IDisplay);

/**
 *  IDISPLAY_QueryInterface(IDisplay *pDisp, MAE_IId id, void **ppObj, IBase *pOwner)
 *
 *  @brief  Inherit addref from IBase to query interface.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  id              [in]Interface ID to query, supports IID_DISPLAY and IID_BASE only
 *  @param  ppObj           [out]Reference to a pointer to a function table if this interface is supported
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS Success
 *  @retval MAE_RET_NOT_SUPPORTED Not support this interface
 *
 */
#define IDISPLAY_QueryInterface(pDisp,id,ppObj,pOwner) GET_FUNCTBL(pDisp,IDisplay)->QueryInterface(pDisp,id,ppObj,pOwner)

/**
 *  IDISPLAY_SetDestination(IDisplay *pDisp, IBitmap *pBmpDst, IBase *pOwner)
 *
 *  @brief  This function sets new destination bitmap to IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pBmpDst         [in]Pointer to new destination IBitmap Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS   Success
 *  @retval MAE_RET_FAILED    Get BmpInfo of pBmpDst error
 *  @retval MAE_RET_BAD_PARAM Error parameter(s)
 *
 *  Note:
 *    If pBmpDst is NULL, system destination IBitmap will be set to IDisplay.
 *    IBITMAP_AddRef will be called on new destinateion bitmap.
 *    IBITMAP_Release will be called on old destinateion bitmap.
 *
 */
#define IDISPLAY_SetDestination(pDisp,pBmpDst,pOwner) GET_FUNCTBL(pDisp,IDisplay)->SetDestination(pDisp,pBmpDst,pOwner)

/**
 *  IDISPLAY_SetFont(IDisplay *pDisp, IFont *pFont, IBase *pOwner)
 *
 *  @brief  This function sets new IFont to the IDisplay. The previous IFont will be returned.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pFont           [in]Pointer to new IFont Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Pointer to IFont    Success
 *  @retval NULL                Any error occurs
 *
 */
#define IDISPLAY_SetFont(pDisp,pFont,pOwner) GET_FUNCTBL(pDisp,IDisplay)->SetFont(pDisp,pFont,pOwner)

/**
 *  IDISPLAY_DrawRect(IDisplay *pDisp, const Rect_t *pRect, RGBColor_t ClrBorder, RGBColor_t ClrFill, u32 Flags)
 *
 *  @brief  This function draws a retangle to the IDisplay
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pRect           [in]Pointer to the rectangle to draw
 *  @param  ClrBorder       [in]Color for border of the rectangle
 *  @param  ClrFill         [in]Color for filling the rectangle
 *  @param  Flags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
#define IDISPLAY_DrawRect(pDisp,pRect,ClrBorder,ClrFill,Flags) GET_FUNCTBL(pDisp,IDisplay)->DrawRect(pDisp,pRect,ClrBorder,ClrFill,Flags)

/**
 *  IDISPLAY_DrawHLine(IDisplay *pDisp, s32 x, s32 y, s32 len)
 *
 *  @brief  This function draws a horizontal line on the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  len             [in]Length of the line
 *
 */
#define IDISPLAY_DrawHLine(pDisp,x,y,len) GET_FUNCTBL(pDisp,IDisplay)->DrawLine(pDisp,x,y,x+len-1,y,DISP_BRUSH_SMALL,DISP_SOLID_LINE)

/**
 *  IDISPLAY_DrawVLine(IDisplay *pDisp, s32 x, s32 y, s32 len)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  len             [in]Length of the line
 *
 */
#define IDISPLAY_DrawVLine(pDisp,x,y,len) GET_FUNCTBL(pDisp,IDisplay)->DrawLine(pDisp,x,y,x,y+len-1,DISP_BRUSH_SMALL,DISP_SOLID_LINE)

/**
 *  IDISPLAY_DrawLine(IDisplay *pDisp, s32 x1, s32 y1, s32 x2, s32 y2, u8 nBrushSize, DisplayDottedType_t eType)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  x1              [in]Start x
 *  @param  y1              [in]Start y
 *  @param  x2              [in]End x
 *  @param  y2              [in]End y
 *  @param  nBrushSize     [in]Brush size
 *  @param  eType          [in]Dotted line type
 *
 */
#define IDISPLAY_DrawLine(pDisp,x1,y1,x2,y2,nBrushSize, eType) GET_FUNCTBL(pDisp,IDisplay)->DrawLine(pDisp,x1,y1,x2,y2,nBrushSize,eType)

/**
 *  IDISPLAY_GetFontInfo(IDisplay *pDisp, u32 FontSize, FontInfo *pInfo)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  FontSize        [in]Font size
 *  @param  pInfo           [out]Pointer of FontInfo to store info
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *  @retval Others              Reference to IFONT_GetInfo();
 *
 */
#define IDISPLAY_GetFontInfo(pDisp,FontCate,FontSize,pInfo) GET_FUNCTBL(pDisp,IDisplay)->GetFontInfo(pDisp,FontCate,FontSize,0,pInfo)

/**
 *  IDISPLAY_GetFontInfoEx(IDisplay *pDisp, u32 FontSize, u32 FontType, FontInfo *pInfo)
 *
 *  @brief  This function draws a vertical line on the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  FontSize        [in]Font size
 *  @param  FontType        [in]Font Type
 *  @param  pInfo           [out]Pointer of FontInfo to store info
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *  @retval Others              Reference to IFONT_GetInfo();
 *
 */
#define IDISPLAY_GetFontInfoEx(pDisp,FontCate,FontSize,FontType,pInfo) GET_FUNCTBL(pDisp,IDisplay)->GetFontInfo(pDisp,FontCate,FontSize,FontType,pInfo)

/**
 *  MAE_Ret IDISPLAY_MeasureText(IDisplay *pDisp,
 *                               u32 FontSize,
 *                               const u16 *pText,
 *                               u32 len,
 *                               u32 MaxWidth,
 *                               u32 *pFits,
 *                               u32 *pPixels,
 *                               u32 Types)
 *
 *  @brief  This function counts how many charaters can be drawn in the given
 *          width and how many pixels can be drawn with such charaters.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  FontSize        [in]Font size
 *  @param  pText           [in]Pointer to text buffer
 *  @param  len             [in]String length of the text buffer
 *  @param  MaxWidth        [in]Width to fit in
 *  @param  pFits           [out]Number of charater in pText can fit
 *  @param  pPixels         [out]Width of fit charaters in pixels
 *  @param  Types           [in]Types of the text
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_FAILED      Any error occurs
 *
 *  Note:
 *    If MaxWidth is set to 0, this function will calculate the length of
 *    entire string of pText.
 *
 */
#define IDISPLAY_MeasureText(pDisp,nFontCate,nFontSize,pText,Chars,MaxWidth,pFits,pPixels,Types)  GET_FUNCTBL(pDisp,IDisplay)->MeasureText(pDisp,nFontCate,nFontSize,pText,Chars,MaxWidth,pFits,pPixels,Types,FALSE)
#define IDISPLAY_MeasureTextEx(pDisp,nFontCate, FontSize,pText,Chars,MaxWidth,pFits,pPixels,Types,bDispStr)  GET_FUNCTBL(pDisp,IDisplay)->MeasureText(pDisp,nFontCate,FontSize,pText,Chars,MaxWidth,pFits,pPixels,Types,bDispStr)

/**
 *  MAE_Ret IDISPLAY_DrawText(IDisplay *pDisp,
 *                            s32 FontSize,
 *                            const u16 *pText,
 *                            s32 len,
 *                            s32 x,
 *                            s32 y,
 *                            const Rect_t *pRect,
 *                            u32 Types)
 *
 *  @brief  This function draws text to the given region.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  FontSize        [in]Font size
 *  @param  pText           [in]Pointer to text buffer
 *  @param  len             [in]String length of the text buffer
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  pRect           [in]Pointer to the region for draw
 *  @param  Types           [in]Types of the text
 *
 *  @retval Reference to the return value of IFONT_DrawText.
 *
 */
#define IDISPLAY_DrawDispText(pDisp,FontCate,FontSize,pText,len,x,y,pRect,Types)     GET_FUNCTBL(pDisp,IDisplay)->DrawDispText(pDisp,FontCate,FontSize,pText,len,x,y,pRect,Types)
#define IDISPLAY_DrawText(pDisp,FontCate,FontSize,pText,len,x,y,pRect,Types)     GET_FUNCTBL(pDisp,IDisplay)->DrawText(pDisp,FontCate,FontSize,pText,len,x,y,pRect,Types)
#define IDISPLAY_DrawDispTextToBitmap(pDisp,pBitmap,FontCate,FontSize,pText,len,x,y,pRect,Types)     GET_FUNCTBL(pDisp,IDisplay)->DrawDispTextToBitmap(pDisp,pBitmap,FontCate,FontSize,pText,len,x,y,pRect,Types,NULL,0)
#define IDISPLAY_DrawTextToBitmap(pDisp,pBitmap,FontCate,FontSize,pText,len,x,y,pRect,Types)     GET_FUNCTBL(pDisp,IDisplay)->DrawTextToBitmap(pDisp,pBitmap,FontCate,FontSize,pText,len,x,y,pRect,Types,NULL,0)

/**
 *  MAE_Ret IDISPLAY_DrawColorfulText(IDisplay *pDisp,
 *                            u32 FontCat,
 *				u32 FontSize,
 *                            const u16 *pText,
 *                            s32 len,
 *                            s32 x,
 *                            s32 y,
 *                            const Rect_t *pRect,
 *                            u32 Types,
 *                            u32 *pColors,
 *                            u8  nNumColor)
 *
 *  @brief  This function draws text to the given region with random color for each character.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  FontCat        [in]Font category
 *  @param  FontSize        [in]Font size
 *  @param  pText           [in]Pointer to text buffer
 *  @param  len             [in]String length of the text buffer
 *  @param  x               [in]Start x
 *  @param  y               [in]Start y
 *  @param  pRect           [in]Pointer to the region for draw
 *  @param  Types           [in]Types of the text
 *  @param  pColors         [in]Color Table for random color
 *  @param  nNumColor       [in]Number of the colors in color table
 *
 *  @retval Reference to the return value of IFONT_DrawColorText.
 *
 */
#define IDISPLAY_DrawColorfulDispText(pDisp,FontCat,FontSize,pText,len,x,y,pRect,Types, pColors, nNumColor)     GET_FUNCTBL(pDisp,IDisplay)->DrawColorfulDispText(pDisp,FontCat,FontSize,pText,len,x,y,pRect,Types, pColors, nNumColor)
#define IDISPLAY_DrawColorfulText(pDisp,FontCat,FontSize,pText,len,x,y,pRect,Types, pColors, nNumColor)     GET_FUNCTBL(pDisp,IDisplay)->DrawColorfulText(pDisp,FontCat,FontSize,pText,len,x,y,pRect,Types, pColors, nNumColor)
#define IDISPLAY_DrawColorfulDispTextToBitmap(pDisp,pBitmap,FontCat,FontSize,pText,len,x,y,pRect,Types,pColors,nNumColor)     GET_FUNCTBL(pDisp,IDisplay)->DrawDispTextToBitmap(pDisp,pBitmap,FontCat,FontSize,pText,len,x,y,pRect,Types,pColors,nNumColor)
#define IDISPLAY_DrawColorfulTextToBitmap(pDisp,pBitmap,FontCat,FontSize,pText,len,x,y,pRect,Types,pColors,nNumColor)     GET_FUNCTBL(pDisp,IDisplay)->DrawTextToBitmap(pDisp,pBitmap,FontCat,FontSize,pText,len,x,y,pRect,Types,pColors,nNumColor)

/**
 *  IDISPLAY_GetDeviceBitmap(IDisplay *pDisp, IBase* pOwner)
 *
 *  @brief  This function returns device IBitmap.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to the device IBitmap.
 *
 */
#define IDISPLAY_GetDeviceBitmap(pDisp,pOwner)     GET_FUNCTBL(pDisp,IDisplay)->GetDeviceBitmap(pDisp,pOwner)

/**
 *  IDISPLAY_GetDestination(IDisplay *pDisp, IBase* pOwner)
 *
 *  @brief  This function returns current destination IBitmap.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to current destination IBitmap.
 *
 */
#define IDISPLAY_GetDestination(pDisp,pOwner)      GET_FUNCTBL(pDisp,IDisplay)->GetDestination(pDisp,pOwner)

/**
 *  IDISPLAY_CreateBitmap(IDisplay *pDisp, u16 w, u16 h, IBase* pOwner)
 *
 *  @brief  This function creates a new IBitmap with given width and height.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  w               [in]width of new IBitmap
 *  @param  h               [in]height of new IBitmap
 *  @param  pOwner          [in]Instance of the object who uses this interface, for reference check.
 *
 *  @retval Ponter to new created IBitmap.
 *
 */
#define IDISPLAY_CreateBitmap(pDisp,w,h,pOwner)  GET_FUNCTBL(pDisp,IDisplay)->CreateBitmap(pDisp,w,h,pOwner)

/**
 *  IDISPLAY_SetColor(IDisplay *pDisp, u32 nItemId, RGBColor_t clr)
 *
 *  @brief  This function set the color of specified color item. Previous color value of the specified item will be returned.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  nItemId         [in]Item ID, use ids defined in ColorItemId_tag
 *  @param  clr             [in]Color value to set
 *
 *  @retval Previous color value of the specified item.
 *
 */
#define IDISPLAY_SetColor(pDisp,nItemId,clr)         GET_FUNCTBL(pDisp,IDisplay)->SetColor(pDisp,nItemId,clr)

/**
 *  IDISPLAY_ClearScreen(IDisplay *pDisp)
 *
 *  @brief  This function clears display bitmap with background color.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *
 */
#define IDISPLAY_ClearScreen(pDisp)            GET_FUNCTBL(pDisp,IDisplay)->ClearScreen(pDisp)

/**
 *  IDISPLAY_SetCARect(IDisplay *pDisp, const Rect_t *pRcCA)
 *
 *  @brief  This function sets client area of the screen.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pRcCA           [in]Pointer to struct Rect of new client area
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pRcCA is NULL
 *
 */
__INLINE MAE_Ret IDISPLAY_SetCARect(IDisplay *pDisp, const Rect_t *pRcCA)
{
	return GET_FUNCTBL(pDisp,IDisplay)->SetProperty(pDisp, DISP_PROP_CLIENTAREA, (u32)pRcCA);
}

/**
 *  IDISPLAY_GetCARect(IDisplay *pDisp, Rect_t *pRcCA)
 *
 *  @brief  This function gets client area of the screen.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pRcCA           [out]Pointer to the memory to store struct Rect of client area
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pRcCA is NULL
 *
 *  Note:
 *    If the pRcCA is NULL, the client area will be reset to whole bitmap
 *
 */
__INLINE MAE_Ret IDISPLAY_GetCARect(IDisplay *pDisp, const Rect_t *pRcCA)
{
	return GET_FUNCTBL(pDisp,IDisplay)->GetProperty(pDisp, DISP_PROP_CLIENTAREA, (void*)pRcCA);
}

/**
 *  IDISPLAY_SetDispMode(IDisplay *pDisp, const DisplayMode_t nDispMode)
 *
 *  @brief  This function sets display mode of the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  nDispMode        [in]New display mode
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp is NULL
 *
 */
__INLINE MAE_Ret IDISPLAY_SetDispMode(IDisplay *pDisp, const DisplayMode_e nDispMode)
{
	return GET_FUNCTBL(pDisp,IDisplay)->SetProperty(pDisp,DISP_PROP_DISPMODE,(u32)nDispMode);
}

/**
 *  IDISPLAY_GetDispMode(IDisplay *pDisp, DisplayMode_t *pDispMode)
 *
 *  @brief  This function gets current display mode of the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDispMode       [out]Pointer to the memory to store display mode
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispMode is NULL
 *
 */
__INLINE MAE_Ret IDISPLAY_GetDispMode(IDisplay *pDisp, const DisplayMode_e *pDispMode)
{
	return GET_FUNCTBL(pDisp,IDisplay)->GetProperty(pDisp,DISP_PROP_DISPMODE,(void*)pDispMode);
}

/**
 *  IDISPLAY_GetDisplayId(IDisplay *pDisp, MAE_DispId_t *pDispId)
 *
 *  @brief  This function can get current display id which specifies that the display object is
 *          displayed in main display or sub display.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDispId         [out]Pointer to the memory to store display id
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispId is NULL
 *
 */
__INLINE MAERet_t IDISPLAY_GetDispId(IDisplay *pDisp, MAE_DispId_t *pDispId)
{
	return GET_FUNCTBL(pDisp,IDisplay)->GetProperty(pDisp,DISP_PROP_DISPID,(void*)pDispId);
}

/**
 *  IDISPLAY_Update(IDisplay *pDisp, u32 Type)
 *
 *  @brief  This function updates the screen if the IBitmap in the given IDisplay is device bitmap.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  Type            reserved
 *
 *  @retval MAE_RET_SUCCESS      Success
 *  @retval MAE_RET_BAD_PARAM    If given pDisp or pDispMode is NULL
 *
 */
#define IDISPLAY_Update(pDisp,Type)              GET_FUNCTBL(pDisp,IDisplay)->Update(pDisp,Type)

/**
 *  IDISPLAY_BitBlt(IDisplay *pDisp,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  RasterOp_t nRopCode)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others          Refer to IBITMAP_Bitblt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
#define IDISPLAY_BitBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode) GET_FUNCTBL(pDisp,IDisplay)->BitBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode)

/**
 *  IDISPLAY_DrawEllipse(IDisplay *pDisp, const Ellipse_t *pEllipse, RGBColor_t ClrBorder, RGBColor_t ClrFill, u32 Flags)
 *
 *  @brief  This function draws a ellipse to the IDisplay
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pEllipse        [in]Pointer to the ellipse to draw
 *  @param  ClrBorder       [in]Color for border of the ellipse
 *  @param  ClrFill         [in]Color for filling the ellipse
 *  @param  Flags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
#define IDISPLAY_DrawEllipse(pDisp,pEllipse,ClrBorder,ClrFill,Flags) GET_FUNCTBL(pDisp,IDisplay)->DrawEllipse(pDisp,pEllipse,ClrBorder,ClrFill,Flags)

/**
 *  IDISPLAY_DrawArc(IDisplay *pDisp, const Ellipse_t *pEllipse, s32 ry, u16 startAngle, u16 endAngle, RGBColor_t ClrBorder, RGBColor_t ClrFill, u32 Flags)
 *
 *  @brief  This function draws a ellipse to the IDisplay
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pEllipse        [in]Pointer to the ellipse to draw
 *  @param  startAngle      [in]Start angle
 *  @param  endAngle        [in]End angle
 *  @param  ClrBorder       [in]Color for border of the ellipse
 *  @param  ClrFill         [in]Color for filling the ellipse
 *  @param  Flags			[in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
 *
 */
#define IDISPLAY_DrawArc(pDisp,pArc,ClrBorder,ClrFill,Flags) GET_FUNCTBL(pDisp,IDisplay)->DrawArc(pDisp,pArc,ClrBorder,ClrFill,Flags)

/**
 *  IDISPLAY_FadeOut(IDisplay *pDisp,
 *                   const Rect_t *pDstRc,
 *                   FadeoutLevel_t FadeoutLevel)
 *
 *  @brief  This function make the fadeout effect to display buffer according to the destination rectangle and fadeout level.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  FadeoutLevel    [in]Fadeout level, reference to mmi_mae_graphic.h
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval MAE_RET_SUCCESS      Successfully.
 *
 *  Note:
 *
 */
#define IDISPLAY_FadeOut(pDisp,pDstRc,FadeoutLevel,eSourceType) \
	GET_FUNCTBL(pDisp,IDisplay)->FadeOut(pDisp,pDstRc,FadeoutLevel,eSourceType)

/**
 *  IDISPLAY_DrawTriangle(IDisplay *pDisp,
 *                            const Triangle_t *pTriangle,
 *                            RGBColor_t u32ClrBorder,
 *                            RGBColor_t u32ClrFill,
 *                            u32 u32Flags)
 *
 *  @brief  This function draws a triangle to the IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pTriangle      [in]Pointer to the triangle to draw
 *  @param  ClrBorder     [in]Color for border of the ellipse
 *  @param  ClrFill           [in]Color for filling the ellipse
 *  @param  Flags		  [in]Drawing type, can be DRAW_RECT_BORDER, DRAW_RECT_FILL, DRAW_RECT_FILL_BORDER, or DRAW_RECT_INVERT
  *
 *  Note:
 *
 */
#define IDISPLAY_DrawTriangle(pDisp,pTriangle,u32ClrBorder,u32ClrFill,u32Flags) \
	GET_FUNCTBL(pDisp,IDisplay)->DrawTriangle(pDisp,pTriangle,u32ClrBorder,u32ClrFill,u32Flags)

/**
 *  IDISPLAY_StretchBlt(IDisplay *pDisp,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  nRopCode)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others          Refer to IBITMAP_StretchBlt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
#define IDISPLAY_StretchBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode) GET_FUNCTBL(pDisp,IDisplay)->StretchBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode)

/**
 *  IDISPLAY_PerspectiveBlt(IDisplay *pDisp,
 *                  const Rect_t *pDstRc,
 *                  const IBitmap *pIBmpSrc,
 *                  const Rect_t *pSrcRc,
 *                  nRopCode,
 *                  u16)
 *
 *  @brief  This function draws the given IBitmap to IDisplay.
 *
 *  @param  pDisp           [in]Pointer to the IDisplay Object
 *  @param  pDstRc          [in]Region on destination to draw
 *  @param  pIBmpSrc        [in]Pointer to source IBitmap
 *  @param  pSrcRc          [in]Region on source bitmap to draw
 *  @param  nRopCode        [in]Raster operation type
 *  @param  nDir          [in]Perspective directioin
 *
 *  @retval MAE_RET_BAD_PARAM    If any given pointer is NULL
 *  @retval others          Refer to IBITMAP_StretchBlt
 *
 *  Note:
 *    If the w in pDstRc is 0, then w will be set to width of the IDisplay.
 *    If the h in pDstRc is 0, then h will be set to height of the IDisplay.
 *
 */
#define IDISPLAY_PerspectiveBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode,nDir) GET_FUNCTBL(pDisp,IDisplay)->PerspectiveBlt(pDisp,pDstRc,pIBmpSrc,pSrcRc,nRopCode,nDir)

/**
*  Display_EnableUpdate(MAEDispId_t nDispID)
*
*  @brief  This function enables display to update screen
*
*  @param  nDispID            [in]ID of display to set
*
*  @retval MAE_RET_SUCCESS     Successful
*  @retval MAE_RET_BAD_PARAM   Error display ID
*/
MAE_Ret Display_EnableUpdate(MAEDispId_t nDispID);

/**
*  Display_DisableUpdate(MAEDispId_t nDispID)
*
*  @brief  This function disables display to update screen
*
*  @param  nDispID            [in]ID of display to set
*
*  @retval MAE_RET_SUCCESS     Successful
*  @retval MAE_RET_BAD_PARAM   Error display ID
*/
MAE_Ret Display_DisableUpdate(MAEDispId_t nDispID);

/**
 *  Display_UpdateDevice(MAEDispId_t id, boolean bPartial)
 *
 *  @brief  This function forces display to update screen
 *
 *  @param  nDispID            [in]ID of display to set
 *  @param  bPartial          [in]If do partial update
 *
 */
void Display_UpdateDevice(MAEDispId_t nDispID, boolean bPartial);

/**
 *  Display_UpdateDeviceEx(MAEDispId_t id, boolean bPartial, boolean bIsFire)
 *
 *  @brief  This function forces display to update screen
 *
 *  @param  nDispID            [in]ID of display to set
 *  @param  bPartial          [in]If do partial update
 *  @param  bIsFire          [in]If fire screen
 *
 */
void Display_UpdateDeviceEx(MAEDispId_t nDispID, boolean bPartial, boolean bIsFire);

/**
 *  Display_ForceUpdateScreen(MAEDispId_t id, boolean bPartial)
 *
 *  @brief  This function forces display to redraw applets and update screen (
 *
 *  @param  None            
 *
 */
void Display_ForceUpdateScreen(void);

/**
 *  Display_LastUpdateIs3DMode(void)
 *
 *  @brief  This function returns if the last update mode is 3D (TRUE) or 2D (FALSE)
 *
 *  @param  None            
 *
 *  @retval TRUE     3D
 *  @retval FALSE   2D
 */
boolean Display_LastUpdateIs3DMode(void);

/**
 *  Display_EnableDoubleBuffer(boolean bDisable)
 *
 *  @brief  This function set enable/disable the double buffer behavior
 *
 *  @param  None            
 *
 */
void Display_EnableDoubleBuffer(boolean bEnable);

/**
 *  Display_IsDoubleBufferEnable(void)
 *
 *  @brief  This function disable the double buffer behavior
 *
 *  @param  None            
 *  @retval   TRUE/FALSE     Enable or not
 */
boolean Display_IsDoubleBufferEnable(void);

/** 
 *  Display_Set3DDirtyArea(IDisplay *pDisp, Rect_t *pDirtyRc)
 *
 *  @brief  This function set 3d dirty area
 *   
 *  @param  pDisp             [in]Pointer to the IDisplay Object
 *  @param  pDirtyRc          [in]Rect of dirty area
 *
 */
void Display_Set3DDirtyArea(IDisplay *pDisp, Rect_t *pDirtyRc);

/**
 *  Display_SetOSDEnableAlphaMask( MAE_DispId_t nDispId, boolean bIsEnable )
 *
 *  @brief  To enable/disable camera/videoplayer/camcorder app to using alpha mask, give each pixel alpha value by alpha mask
 *
 *  @param  nClsId			     [in] applet class ID
 *  @param  nDispId              [in] display screen ID
 *  @param  bIsEnable            [in] enable/disable OSD per pixel alpha blending
 *  @retval 
 *
 *  Note:
 *
 */
MAE_Ret Display_SetOSDEnableAlphaMask( u16 nClsId, MAE_DispId_t nDispId, boolean bIsEnable );

/**
 *  Display_GetOSDEnableAlphaMask( MAE_DispId_t nDispId )
 *
 *  @brief  To get camera/videoplayer/camcorder app is using alpha mask or not
 *
 *  @param  nDispId              [in] display screen ID
 *
 *  @retval TRUE				[out]OSD is per pixel alpha blending
 *          FALSE				[out]OSD is NOT per pixel alpha blending
 *
 *  Note:
 *
 */
boolean Display_GetOSDEnableAlphaMask( MAE_DispId_t nDispId );

/**
 *  Display_SetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency )
 *
 *  @brief  To set Transparency value to camera/videoplayer/camcorder app, give each pixel alpha value by transparency
 *
 *  @param  nDispId              [in] display screen ID
 *  @param  nTransparency        [in] OSD global alpha blending value
 *
 *  @retval 
 *
 *  Note: the default transparency is 255 ( Opaque fully)
 *
 */
MAE_Ret Display_SetOSDTransparency( MAE_DispId_t nDispId, u8 nTransparency );

/**
 *  Display_GetScreenUpdateTime(void)
 *
 *  @brief  To get full screen update time in ms
 *
 *  @param  None
  *
 *  @retval screen update time
 *
  *
 */
u32 Display_GetScreenUpdateTime(void);


#ifdef __DISP_ML_MMI__

/**
 *  IDISPLAY_CreateLayer(IDisplay *pDisp,
 *                       DisplayLayer_t layer,
 *                       u32 width,
 *                       u32 height)
 *
 *  @brief  This function is to create layer according paramter layer.
 *
 *  @param  pDisp         [in]Pointer to the IDisplay Object
 *  @param  layer         [in]Identicate which layer
 *  @param width          [in]the width of created layer
 *  @param height        [in]the height of created layer
 *  @param format        [in]the format of created layer  (565 with color key, or ARGB888)
 *
 *  @note
 *
 */
#define IDISPLAY_CreateLayer(pDisp,layer,width,height,format) GET_FUNCTBL(pDisp,IDisplay)->CreateLayer(pDisp,layer,width,height,format)
/**
 *  IDISPLAY_ReleaseLayer(IDisplay *pDisp,
 *                        DisplayLayer_t layer)
 *
 *  @brief  This function is to release layer according paramter layer.
 *
 *  @param  pDisp         [in]Pointer to the IDisplay Object
 *  @param  layer         [in]Identicate which layer
 *
 *  @note
 *
 */
#define IDISPLAY_ReleaseLayer(pDisp,layer) GET_FUNCTBL(pDisp,IDisplay)->ReleaseLayer(pDisp,layer)
/**
 *  IDISPLAY_SetCurrentLayer(IDisplay *pDisp,
 *                           DisplayLayer_t layer)
 *
 *  @brief  This function is to set current layer according paramter layer.
 *
 *  @param  pDisp         [in]Pointer to the IDisplay Object
 *  @param  layer         [in]Identicate which layer
 *
 *  @note
 *
 */
#define IDISPLAY_SetCurrentLayer(pDisp,layer)  GET_FUNCTBL(pDisp,IDisplay)->SetCurrentLayer(pDisp,layer)
/**
 *  IDISPLAY_SetLayerOffset(IDisplay *pDisp,
 *                          DisplayLayer_t layer,
 *                          u32 x,
 *                          u32 y)
 *
 *  @brief  This function is to set the offset of the given layer
 *
 *  @param  pDisp         [in]Pointer to the IDisplay Object
 *  @param  layer         [in]Identicate which layer
 *  @param  x             [in]x offset of the layer
 *  @param  y             [in]y offset of the layer
 *
 *  @note
 *
 */
#define IDISPLAY_SetLayerOffset(pDisp,layer,x,y)  GET_FUNCTBL(pDisp,IDisplay)->SetLayerOffset(pDisp,layer,x,y)
/**
 *  IDISPLAY_SetLayerVisible(IDisplay *pDisp,
 *                          DisplayLayer_t layer,
 *                          u8 bVisible)
 *
 *  @brief  This function is to set the offset of the given layer
 *
 *  @param  pDisp         [in]Pointer to the IDisplay Object
 *  @param  layer         [in]Identicate which layer
 *  @param  bVisible             [in]layer visible flag
 *
 *  @note
 *
 */
#define IDISPLAY_SetLayerVisible(pDisp,layer,bVisible) GET_FUNCTBL(pDisp,IDisplay)->SetLayerVisible(pDisp,layer,bVisible)

/**
*  IDISPLAY_ReleaseAllLayer(IDisplay *pDisp)
*
*  @brief  This function is to merge all layer to base layer
*
*  @param  pDisp         [in]Pointer to the IDisplay Object

*  @note
*
*/
#define IDISPLAY_ReleaseAllLayer(pDisp) GET_FUNCTBL(pDisp,IDisplay)->ReleaseAllLayer(pDisp)

#define IDISPLAY_GetLayerCARect(pDisp,pRc,nLayer) GET_FUNCTBL(pDisp,IDisplay)->GetLayerCARect(pDisp,pRc,nLayer)

/**
*  IDISPLAY_SetG3DBuffer(IDisplay *pDisp,
*                        G3DInfo_t *pG3Dinfo)
*
*  @brief  This function set G3D info to IDisplay.
*
*  @param  pDisp         [in]Pointer to the IDisplay Object
*  @param  pG3Dinfo        [in]Pointer to G3D information
*
*  @note   If pG3Dinfo->pData is not NULL, G3D layer will be enable.
*          If pG3Dinfo->pData is NULL, G3D layer will be disable.
*
*/
#define IDISPLAY_SetG3DBuffer(pDisp,pG3Dinfo) \
    GET_FUNCTBL(pDisp,IDisplay)->SetG3DBuffer(pDisp,pG3Dinfo)

/**
*  IDISPLAY_GetG3DBuffer(IDisplay *pDisp)
*
*  @brief  This function get IBitmap of G3D layer.
*
*  @param  pDisp         [in]Pointer to the IDisplay Object
*
*  @retval Ponter to IBitmap of G3D layer.
*
*  @note
*
*/
#define IDISPLAY_GetG3DBuffer(pDisp) \
    GET_FUNCTBL(pDisp,IDisplay)->GetG3DBuffer(pDisp)

#endif  // end __DISP_ML_MMI__


/**
*  IDISPLAY_Set3DMode(IDisplay *pDisp, boolean bIsOn)
*
*  @brief  This function only set the 3D Mode flag
*
*  @param  pDisp         [in]Pointer to the IDisplay Object
*  @param  bIsOn		[in]TRUE:IsOn / FALSE:IsClose
*
*  @retval MAE_RET_SUCCES/MAE_RET_FAILED
*
*  @note
*
*/
#define IDISPLAY_Set3DMode(pDisp, bIsOn) \
    GET_FUNCTBL(pDisp,IDisplay)->Set3DMode(pDisp, bIsOn)

/**
*  IDISPLAY_Get3DMode(IDisplay *pDisp)
*
*  @brief  This function  get the 3D mode flag
*
*  @param  pDisp         [in]Pointer to the IDisplay Object
*
*  @retval TRUE:IsOn / FALSE:IsClose
*
*  @note
*
*/
#define IDISPLAY_Get3DMode(pDisp) \
    GET_FUNCTBL(pDisp,IDisplay)->Get3DMode(pDisp)

/**
 *  Display_GetDPM( MAE_DispId_t nDispId)
 *
 *  @brief  To get the amount of pixels per 10 Centimeters.
 *
 *  @param  nDispId              [in] display screen ID
 *
 *  @retval the amount of pixels per 10 centimeters
 *
 *
 */
u32 Display_GetDPM( MAE_DispId_t nDispId );


#define IDISPLAY_CvrtToAbsRect(pDisp,pRc)   GET_FUNCTBL(pDisp,IDisplay)->GetProperty(pDisp, DISP_PROP_CVRT_TO_ABS_RECT, (void*)pRc)

#define IDISPLAY_CvrtFromAbsRect(pDisp,pRc) GET_FUNCTBL(pDisp,IDisplay)->GetProperty(pDisp, DISP_PROP_CVRT_FROM_ABS_RECT, (void*)pRc)

#endif /* __MAE_DISPLAY_H__ */
