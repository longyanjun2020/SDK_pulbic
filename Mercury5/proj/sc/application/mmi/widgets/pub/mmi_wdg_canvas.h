/**
 * @file    mmi_wdg_canvas.h
 * @author  alison.chen@mstarsemi.com
 * 
 * @version $Id: mmi_wdg_canvas.h 4291 2007-11-19 03:56:54Z alison.chen $
 *
 *
 * @brief   
 *
 */
 
#ifndef __MMI_WDG_CANVAS_H__
#define __MMI_WDG_CANVAS_H__
/* ===========================================================*/
// Description
/* ===========================================================*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"

///MAE Pub Header
#include "mmi_mae_bitmap_types.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
	TransparentType_t tTransType;
	union
	{
		RGBColor_t  tTransColor;		// the color key, for TRANS_COLOR type
		u8 nTransparency;					// the transparency (0~255), for TRANSPARENCY type
	}TransData_u;
}CanvasTransparentInfo_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
/** WdgCanvasCreateForWnd
* @brief        Create Canvas widget and set size  for Window
*
* @param[in]    hWin       The window handle
* @param[in]    pPos          A pointer of widget position; can't be NULL.
* @param[in]    pSize         A pointer of widget size; NULL means default value.
* @param[in]    nWdgId        The widget unique ID of window
*
* @retval       The pointer of Canvas   Success.
* @retval       NULL                 Failed.
*
*/
IWidget* WdgCanvasCreateForWnd
(
    HWIN          hWin,
    Pos_t                *pPos,
    WidgetSize_t         *pSize,
    u16                  nWdgId
);

/** WdgCanvasCreate
* @brief        Create Canvas widget
*
* @retval       The pointer of Canvas    Success.
* @retval       NULL                  Failed.
*
*/
IWidget* WdgCanvasCreate
(
    void
);

/** CanvasWdgCreateBuffer
* @brief        Create the canvas buffer, if the canvas buffer already exist, must destroy it first.
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nWidth     The width of canvas
* @param[in]    nHeight    The height of canvas
* @param[in]    pTransInfo   The transparent type of this buffer,  
*											NULL means use default setting (TRANS_COLOR + RGBCOLOR_OSD_TRANS)
*											pTransInfo->tTransType = TRANS_NONE / TRANS_COLOR / TRANS_ALPHA / TRANSPARENCY
*
* @retval       MAE_RET_SUCCESS				create success
* @retval       MAE_RET_BAD_PARAM		parameter is wrong
* @retval       MAE_RET_FAILED					canvas already exist
* @retval       MAE_RET_OUT_OF_MEMORY		out of memory
*
*/
MAE_Ret CanvasWdgCreateBuffer(IWidget *pWdg, u16 nWidth, u16 nHeight, CanvasTransparentInfo_t *pTransInfo);

/** CanvasWdgDestroyBuffer
* @brief        Destroy the canvas buffer
*
* @param[in]    pWdg       The canvas widget pointer
*
*/
void CanvasWdgDestroyBuffer(IWidget *pWdg);

/*=============================================================*/
// setting functions
/*=============================================================*/
/** CanvasWdgSetDrawArea
* @brief        Set the draw area in canvas, all draw operation will not over this area, NULL means entire canvas
*					default is entire canvas
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc          The draw area in canvas, NULL means entire canvas
*
*/
void CanvasWdgSetDrawArea(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgSetViewport
* @brief        Set the region to be displayed in canvas, the region will align to (0, 0) of the widget position
*					default is entire canvas
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc          The region to be displayed in canvas, NULL means entire canvas
*
*/
void CanvasWdgSetViewport(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgSetFgColor
* @brief        Set foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nClr          The color
*
*/
__INLINE void CanvasWdgSetFgColor(IWidget *pWdg, RGBColor_t nClr)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_FG_COLOR, (u32)nClr);
}

/** CanvasWdgSetBgColor
* @brief        Set background color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nClr          The color
*
*/
__INLINE void CanvasWdgSetBgColor(IWidget *pWdg, RGBColor_t nClr)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_BG_COLOR, (u32)nClr);
}

/** CanvasWdgSetLineColor
* @brief        Set line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nClr          The color
*
*/
__INLINE void CanvasWdgSetLineColor(IWidget *pWdg, RGBColor_t nClr)
{
	WdgCommonSetProperty(pWdg, PROP_CANVAS_WDG_LINE_COLOR, (u32)nClr);
}

/** CanvasWdgSetTextColor
* @brief        Set text color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nClr          The color
*
*/
__INLINE void CanvasWdgSetTextColor(IWidget *pWdg, RGBColor_t nClr)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_TEXT_COLOR, (u32)nClr);
}

/** CanvasWdgSetOutlineColor
* @brief        Set text outline color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nClr          The color
*
*/
__INLINE void CanvasWdgSetOutlineColor(IWidget *pWdg, RGBColor_t nClr)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_TEXT_OUTLINE_COLOR, (u32)nClr);
}

/** CanvasWdgSetFontType
* @brief        Set font type
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    FT          The font type
*
*/
__INLINE void CanvasWdgSetFontType(IWidget *pWdg, FontType_t FT)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_FONT_TYPE, (u32)FT);
}

/** CanvasWdgSetFontCategory
* @brief        Set font category
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    FC          The font category
*
*/
__INLINE void CanvasWdgSetFontCategory(IWidget *pWdg, FontCategory_t FC)
{
	WdgCommonSetProperty(pWdg, PROP_WDG_FONT_CATE, (u32)FC);
}

/** CanvasWdgSetLineType
* @brief        Set line type
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nType       The line type
*
*/
__INLINE void CanvasWdgSetLineType(IWidget *pWdg, DisplayDottedType_e nType)
{
	WdgCommonSetProperty(pWdg, PROP_CANVAS_WDG_LINE_TYPE, (u32)nType);
}

/** CanvasWdgSetBrushSize
* @brief        Set brush size
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    nSize       The brush size (in pixels), max: DISP_BRUSH_MAX (30)
*
*/
__INLINE void CanvasWdgSetBrushSize(IWidget *pWdg, u8 nSize)
{
	WdgCommonSetProperty(pWdg, PROP_CANVAS_WDG_BRUSH_SIZE, (u32)nSize);
}

/*=============================================================*/
// graphics functions
/*=============================================================*/
/** CanvasWdgDrawString, CanvasWdgDrawStringById
* @brief        Draw string, 
*                  depends on:text color, outline color, font type, font category
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pStr			The string to be draw
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
*/
void CanvasWdgDrawString(IWidget *pWdg, MAE_WChar *pStr, s32 x, s32 y);
void CanvasWdgDrawStringById(IWidget *pWdg, u32 nStrId, s32 x, s32 y);

/** CanvasWdgDrawHighlightString, CanvasWdgDrawHighlightStringById
* @brief        Draw string and highlight background, 
*					depends on: background color, text color, outline color, font type, font category
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pStr			The string to be draw
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
*/
void CanvasWdgDrawHighlightString(IWidget *pWdg, MAE_WChar *pStr, s32 x, s32 y);
void CanvasWdgDrawHighlightStringById(IWidget *pWdg, u32 nStrId, s32 x, s32 y);

/** CanvasWdgDrawPoint
* @brief        Draw a point with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    x				The x position
* @param[in]    y				The y position
*
*/
void CanvasWdgDrawPoint(IWidget *pWdg, u32 x, u32 y);

/** CanvasWdgDrawLine
* @brief        Draw a line with line color
*					depends on: line color, brush size, line type
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    x1			The x position of p1
* @param[in]    y1			The y position of p1
* @param[in]    x2			The x position of p2
* @param[in]    y2			The y position of p2
*
*/
void CanvasWdgDrawLine(IWidget *pWdg, s32 x1, s32 y1, s32 x2, s32 y2);

/** CanvasWdgDrawRect
* @brief        Draw a rectangle (only border)
*					depends on: line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
*
*/
void CanvasWdgDrawRect(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgFillRect
* @brief        Fill a rectangle with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
*
*/
void CanvasWdgFillRect(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgFillRectWithBorder
* @brief        Fill a rectangle with foreground color and border with line color
*					depends on: foreground color, line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
*
*/
void CanvasWdgFillRectWithBorder(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgDrawRoundRect
* @brief        Draw a round rectangle (only border)
*					depends on: line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
* @param[in]    rx				The x radius of round corner, cannot be 0
* @param[in]    ry				The y radius of round corner, cannot be 0
*
*/
void CanvasWdgDrawRoundRect(IWidget *pWdg, Rect_t *pRc, u32 rx, u32 ry);

/** CanvasWdgFillRoundRect
* @brief        Fill a round rectangle with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
* @param[in]    rx				The x radius of round corner, cannot be 0
* @param[in]    ry				The y radius of round corner, cannot be 0
*
*/
void CanvasWdgFillRoundRect(IWidget *pWdg, Rect_t *pRc, u32 rx, u32 ry);

/** CanvasWdgDrawRoundRect
* @brief        Fill a round rectangle with foreground color and border with line color
*					depends on: foreground color, line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc			The rectangle
* @param[in]    rx				The x radius of round corner, cannot be 0
* @param[in]    ry				The y radius of round corner, cannot be 0
*
*/
void CanvasWdgFillRoundRectWithBorder(IWidget *pWdg, Rect_t *pRc, u32 rx, u32 ry);

/** CanvasWdgDrawTriangle
* @brief        Draw a triangle (only border)
*					depends on: line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pTriangle	The triangle
*
*/
void CanvasWdgDrawTriangle(IWidget *pWdg, Triangle_t *pTriangle);

/** CanvasWdgFillTriangle
* @brief         Fill a triangle with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pTriangle	The triangle
*
*/
void CanvasWdgFillTriangle(IWidget *pWdg, Triangle_t *pTriangle);

/** CanvasWdgFillTriangleWithBorder
* @brief        Fill a triangle with foreground color and border with line color
*					depends on: foreground color, line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pTriangle	The triangle
*
*/
void CanvasWdgFillTriangleWithBorder(IWidget *pWdg, Triangle_t *pTriangle);

/** CanvasWdgDrawEllipse
* @brief        Draw a Ellipse (only border)
*					depends on: line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pEllipse		The elllipse, the rx,ry of pEllipse cannot be smaller than 0
*
*/
void CanvasWdgDrawEllipse(IWidget *pWdg, Ellipse_t *pEllipse);

/** CanvasWdgFillEllipse
* @brief        Fill a Ellipse with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pEllipse		The elllipse, the rx,ry of pEllipse cannot be smaller than 0
*
*/
void CanvasWdgFillEllipse(IWidget *pWdg, Ellipse_t *pEllipse);

/** CanvasWdgFillEllipseWithBorder
* @brief        Fill a Ellipse with foreground color and border with line color
*					depends on: foreground color, line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pEllipse		The elllipse, the rx,ry of pEllipse cannot be smaller than 0
*
*/
void CanvasWdgFillEllipseWithBorder(IWidget *pWdg, Ellipse_t *pEllipse);

/** CanvasWdgDrawArc
* @brief        Draw a Arc (only border)
*					depends on: line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pArc			The Arc, the rx,ry of pArc cannot be smaller than 0
*
*/
void CanvasWdgDrawArc(IWidget *pWdg, Arc_t *pArc);

/** CanvasWdgFillArc
* @brief        Fill a Arc with foreground color
*					depends on: foreground color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pArc			The Arc, the rx,ry of pArc cannot be smaller than 0
*
*/
void CanvasWdgFillArc(IWidget *pWdg, Arc_t *pArc);

/** CanvasWdgFillArcWithBorder
* @brief        Fill a Arc with foreground color and border with line color
*					depends on: foreground color, line color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pArc			The Arc, the rx,ry of pArc cannot be smaller than 0
*
*/
void CanvasWdgFillArcWithBorder(IWidget *pWdg, Arc_t *pArc);

/** CanvasWdgDrawImage
* @brief        Draw entire image, the image must be decoded done.
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pImg       The IImage pointer
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
* @retval       MAE_RET_SUCCESS			Draw success
* @retval       MAE_RET_BAD_PARAM	The parameter is wrong
* @retval       MAE_RET_NOT_READY		The image is not decoded done.
*
*/
MAE_Ret CanvasWdgDrawImage(IWidget *pWdg, IImage *pImg, s32 x, s32 y);
MAE_Ret CanvasWdgDrawImageById(IWidget *pWdg, u32 nImgId, s32 x, s32 y);

/** CanvasWdgDrawPartialImage
* @brief        Draw partial image, the image must be decoded done.
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pImg       The IImage pointer
* @param[in]    pRcSrc     The partial area of the image
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
* @retval       MAE_RET_SUCCESS			Draw success
* @retval       MAE_RET_BAD_PARAM	The parameter is wrong
* @retval       MAE_RET_NOT_READY		The image is not decoded done.
*
*/
MAE_Ret CanvasWdgDrawPartialImage(IWidget *pWdg, IImage *pImg, Rect_t *pRcSrc, s32 x, s32 y);
MAE_Ret CanvasWdgDrawPartialImageById(IWidget *pWdg, u32 nImgId, Rect_t *pRcSrc, s32 x, s32 y);

/** CanvasWdgDrawScaledImage
* @brief        Draw scaled image, the partial image area will be scaled to fit destination area
*					the image must be decoded done.
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pImg       The IImage pointer
* @param[in]    pRcSrc     The partial area of the image
* @param[in]    pRcDst     The destination area of canvas
*
* @retval       MAE_RET_SUCCESS			Draw success
* @retval       MAE_RET_BAD_PARAM	The parameter is wrong
* @retval       MAE_RET_NOT_READY		The image is not decoded done.
*
*/
MAE_Ret CanvasWdgDrawScaledImage(IWidget *pWdg, IImage *pImg, Rect_t *pRcSrc, Rect_t *pRcDst);
MAE_Ret CanvasWdgDrawScaledImageById(IWidget *pWdg, u32 nImgId, Rect_t *pRcSrc, Rect_t *pRcDst);

/** CanvasWdgDrawBitmap
* @brief        Draw entire Bitmap
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pBmp       The Bitmap pointer
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
*/
void CanvasWdgDrawBitmap(IWidget *pWdg, IBitmap *pBmp, s32 x, s32 y);

/** CanvasWdgDrawPartialBitmap
* @brief        Draw partial bitmap
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pBmp       The IBitmap pointer
* @param[in]    pRcSrc     The partial area of the image
* @param[in]    x				The draw start x position
* @param[in]    y				The draw start y position
*
*/
void CanvasWdgDrawPartialBitmap(IWidget *pWdg, IBitmap *pBmp, Rect_t *pRcSrc, s32 x, s32 y);

/** CanvasWdgDrawScaledBitmap
* @brief        Draw scaled bitmap, the partial bitmap area will be scaled to fit destination area
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pBmp       The IBitmap pointer
* @param[in]    pRcSrc     The partial area of the Bitmap
* @param[in]    pRcDst     The destination area of canvas
*
*/
MAE_Ret CanvasWdgDrawScaledBitmap(IWidget *pWdg, IBitmap *pBmp, Rect_t *pRcSrc, Rect_t *pRcDst);

/** CanvasWdgClear
* @brief        Clear the area of canvas, 
*					if the type is TRANS_COLOR --> fill transparent color,
*					otherwise --> fill background color
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc		    The area to be cleared, NULL means entire canvas
*
*/
void CanvasWdgClear(IWidget *pWdg, Rect_t *pRc);

/** CanvasWdgFadeout
* @brief        Fadeout the area of canvas
*
* @param[in]    pWdg       The canvas widget pointer
* @param[in]    pRc		    The area to be cleared, NULL means entire canvas
* @param[in]    tFdoLevel The fadeout level, refer to FadeoutLevel_t 
*
*/
//void CanvasWdgFadeout(IWidget *pWdg, Rect_t *pRc, FadeoutLevel_t tFdoLevel);

//void CanvasWdgSaveAsBmpFile(IWidget*pWdg, MAE_WChar *pPath);

#endif //__MMI_WDG_CANVAS_H__
/*=============================================================*/
// end of file
