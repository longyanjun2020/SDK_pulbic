/**
* @file    mae_widget_common.h
* @brief   his header file defines some definitions of interface and the definition of IBase interface
* 
* @version $Id: mae_widget_common.h 34134 2009-06-23 07:19:22Z bill.pan $
*/

#ifndef __MAE_WIDGET_COMMON_H__
#define __MAE_WIDGET_COMMON_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_log.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_font_base.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"

#if defined(__FEATURE_MGL__)
#include "mgl_Utility_common.h"
#include "mgl_Scene_NodeMgr.h"
#endif

/*=============================================================*/
// type and define
/*=============================================================*/

#define ABS(_v)	(((_v)<0)?(-(_v)):(_v))

#define CEIL(_N,_D)	(((_N)+(_D)-1)/(_D))	// a ceil function, _N, _D shall bigger than zero
//#define ISEMPTYRECT(_RectPtr)	(((_RectPtr)->w <= 0)||((_RectPtr)->h <= 0))

#define EXISTRECT(_RectPtr)	(((_RectPtr)->w > 0)&&((_RectPtr)->h > 0))

#define IS_XY_INSIDE(_x, _y, _pRect) \
	(((_pRect)->x <= (_x))&& \
	((_pRect)->y <= (_y))&& \
	(((_pRect)->x + (_pRect)->w) > (_x))&& \
	(((_pRect)->y + (_pRect)->h) > (_y)))

typedef struct {
	RGBColor_t TextColor;		///< rgb text color.
	RGBColor_t OutlineColor;    ///< rgb text outline color.
} WdgTxtColor_t;

typedef struct {
	FontType_t     FontType;	///< font type
	FontCategory_t FontCate;	///< font category
} WdgFontStyle_t;

#if defined(__FEATURE_MGL__)

#define RGBColorToColor4f(_RGBColor, _Color4f) \
    mgl_Color4f_Set(_Color4f, \
    (mgl_float)(RED_FROM_RGBCOLOR(_RGBColor)/(mgl_float)255), \
    (mgl_float)(GREEN_FROM_RGBCOLOR(_RGBColor)/(mgl_float)255), \
    (mgl_float)(BLUE_FROM_RGBCOLOR(_RGBColor)/(mgl_float)255), \
    (mgl_float)(ALPHA_FROM_RGBCOLOR(_RGBColor))/(mgl_float)255) 

#endif

/*=============================================================*/
// functions
/*=============================================================*/



//calculate intersection
boolean CalcIntersectRect(Rect_t *pDst, const Rect_t *pSrc1, const Rect_t *pSrc2);


//free data function
void WidgetDataFree(void *pData, IBase *pOwner);

u8 Widget_TransferAlignType( u8 u8TextAlign );

#define Widget_DrawHLine(nNodeId, pDisp, x, y, len, nColor, b3D) \
    Widget_DrawLine(nNodeId, pDisp, x, y, x+len-1, y, nColor, DISP_BRUSH_SMALL, DISP_SOLID_LINE, b3D)

#define Widget_DrawVLine(nNodeId, pDisp, x, y, len, nColor, b3D) \
    Widget_DrawLine(nNodeId, pDisp, x, y, x, y+len-1, nColor, DISP_BRUSH_SMALL, DISP_SOLID_LINE, b3D)

IDispCanvas * Widget_CreateDispCanvas(IBase* pOwner, u16 w, u16 h,ColorScheme_t nColorScheme, boolean bCreateAlphaMask);

#if defined(__FEATURE_MGL__)
/*
Release the resource of the given RawDataId of the NodeId.
*/
void Widget_ReleaseSingleRawData(mgl_u32 nNodeId, mgl_u32 *pRawDataId);
/*
Release the resource of the given ImgId of the NodeId.
*/
void Widget_ReleaseSingleImgData(mgl_u32 nNodeId, mgl_u32 nImgId);

#endif

typedef IWidget* (*WdgCreateFn)(void);
typedef IWidget* (*WdgCreateFnParam)(u32);

IWidget* WdgPreCreateForWnd
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID,
 WdgCreateFn         pfnCreate
);

IWidget* WdgPreCreateForWndParam
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID,
 WdgCreateFnParam    pfnCreate,
 u32                 nParam
 );

IWidget* WdgCreateForWnd
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID,
 WdgCreateFn         pfnCreate
 );

IWidget* WdgCreateForWndParam
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID,
 WdgCreateFnParam    pfnCreate,
 u32                 nParam
 );


#if defined(__G3D_MMI__)
void Widget_DrawLine(mgl_s32 nNodeId, IDisplay *pDisp, s32 x1, s32 y1, s32 x2, s32 y2, RGBColor_t nColor, u8 nBrushSize, DisplayDottedType_e nType, boolean b3D);
void Widget_FillRect(mgl_s32 nNodeId, IDisplay *pDisp, const Rect_t *pRect, RGBColor_t nColor, boolean b3D);
void Widget_FillRectWithBorder(mgl_s32 nNodeId, IDisplay *pDisp, const Rect_t *pRect, RGBColor_t nBorderColor, u32 nXBorder, u32 nYBorder, RGBColor_t nFillColor, boolean b3D);
void Widget_DrawRectBorder(mgl_s32 nNodeId, IDisplay *pDisp, const Rect_t *pRect, RGBColor_t nColor, u32 nXBorder, u32 nYBorder, boolean b3D);
void Widget_FillEllipse(mgl_s32 nNodeId, IDisplay *pDisp, const Ellipse_t *ptEllipse, RGBColor_t nColor, boolean b3D);
void Widget_FillEllipseWithBorder(mgl_s32 nNodeId, IDisplay *pDisp, const Ellipse_t *ptEllipse, RGBColor_t nBorderColor, u32 nBorderPix, RGBColor_t nFillColor, boolean b3D);
void Widget_DrawEllipseBorder(mgl_s32 nNodeId, IDisplay *pDisp, const Ellipse_t *ptEllipse, RGBColor_t nColor, u32 nBorderPix, boolean b3D);

/*
	Draw colorful text
	If pRawDataId==NULL, the RawData will be released after drawing,
	otherwise RawData id will be stored in *pRawDataId.
	if pColorsis NULL and nNumColor is 0, default text color will be used.
*/
void Widget_DrawColorfulDispText(IWidget *pWdg,
                             mgl_s32 nNodeId,
                             mgl_u32 *pRawDataId,
                             IDisplay *pDisp,
                             u32 FontCat,
                             s32 FontSize,
                             const u16 *pText,
                             s32 Chars,
                             s32 x,
                             s32 y,
                             const Rect_t *pRect,
                             u32 Types,
                             u32 *pColors,
                             u8 nNumColor,
                             RGBColor_t nBgColor,
                             boolean b3D);

void Widget_DrawColorfulText(IWidget *pWdg,
                             mgl_s32 nNodeId,
                             mgl_u32 *pRawDataId,
                             IDisplay *pDisp,
                             u32 FontCat,
                             s32 FontSize,
                             const u16 *pText,
                             s32 Chars,
                             s32 x,
                             s32 y,
                             const Rect_t *pRect,
                             u32 Types,
                             u32 *pColors,
                             u8 nNumColor,
                             RGBColor_t nBgColor,
                             boolean b3D);

/*
Draw text
If pRawDataId==NULL, the RawData will be released after drawing,
otherwise RawData id will be stored in *pRawDataId.
*/
void Widget_DrawDispText(IWidget *pWdg,
                       mgl_s32 nNodeId,
                       mgl_u32 *pRawDataId,
                       IDisplay *pDisp,
					   s32 FontCat,
					   s32 FontSize,
                       const u16 *pText,
                       s32 Chars,
                       s32 x,
                       s32 y,
                       const Rect_t *pRect,
                       u32 Types,
                       RGBColor_t nBgColor,
                       boolean b3D);

void Widget_DrawText(IWidget *pWdg,
                       mgl_s32 nNodeId,
                       mgl_u32 *pRawDataId,
                       IDisplay *pDisp,
					   s32 FontCat,
					   s32 FontSize,
                       const u16 *pText,
                       s32 Chars,
                       s32 x,
                       s32 y,
                       const Rect_t *pRect,
                       u32 Types,
                       RGBColor_t nBgColor,
                       boolean b3D);

/*
Draw a Rawdata ID or IBitmap
Rawdata ID is only supported in 3D
pnRawDataId is both for input and output.
If pnRawDataId == NULL, this function will release texture
else RawData ID will be stored in *pnRawDataId.
If pnRawDataId is not NULL and *pnRawDataId is valid, this function will 
use *pnRawDataId to draw instead of creating a new ID
*/
void Widget_DrawBmp(IWidget *pWdg, mgl_s32 nNodeId, mgl_u32 *pnRawDataId, IDisplay *pDisp, Rect_t *pDstRc, IBitmap *pBmp, Rect_t *pSrcRc, boolean b3D);

/*
Draw a Rawdata ID or IImage
Rawdata ID is only supported in 3D
pnRawDataId is both for input and output.
If pnRawDataId == NULL, this function will release texture
else RawData ID will be stored in *pnRawDataId.
If pnRawDataId is not NULL and *pnRawDataId is valid, this function will 
use *pnRawDataId to draw instead of creating a new ID
*/
void Widget_DrawImg(IWidget *pWdg, mgl_s32 nNodeId, mgl_u32 *pnRawDataId, IDisplay *pDisp, Rect_t *pDstRc, IImage *pImg, Rect_t *pSrcRc, boolean b3D);

/*
Draw a texture or IBitmap to 3D
If bReleaseRawData == TRUE, this function will release texture and return 0.
else RawData ID will be returned.
*/
mgl_u32 Widget_DrawBmpOn3D(mgl_s32 nImgNodeId, mgl_u32 nRawDataId, IBitmap *pBmp, s32 x, s32 y, Rect_t *pSrcRc, boolean bReleaseRawData);
mgl_u32 Widget_DrawBmpOn3D_Stretch(mgl_s32 nImgNodeId, mgl_u32 nRawDataId, IBitmap *pBmp, Rect_t *pDstRc, Rect_t *pSrcRc, boolean bReleaseRawData);

/*
Draw a texture or IImage to 3D
If bReleaseRawData == TRUE, this function will release texture and return 0.
else RawData ID will be returned.
*/
mgl_u32 Widget_DrawImgOn3D(mgl_s32 nImgNodeId, mgl_u32 nRawDataId, IImage *pImg, s32 x, s32 y, Rect_t *pSrcRc, boolean bReleaseRawData);
MAE_Ret Widget_DrawImgOn3DEx(mgl_s32 nImgNodeId, mgl_u32 nRawDataId, IImage *pImg, s32 x, s32 y, Rect_t *pSrcRc, boolean bReleaseRawData, mgl_u32 *pRawDataId);

/*
Draw fadeout effect on the given rectangle.
*/
void Widget_DrawFadeout(mgl_s32 nImgNodeId, Rect_t *pFadeoutRc,  u8 nAlpha);

#else

#define Widget_DrawLine(nNodeId, pDisp, x1, y1, x2, y2, nColor, nBrushSize, nType, b3D) \
    IDISPLAY_DrawLine(pDisp, x1, y1, x2, y2, nBrushSize, nType)

#define Widget_FillRect(nNodeId, pDisp, pRect, nColor, b3D) \
    IDISPLAY_DrawRect(pDisp, pRect, nColor, nColor, DRAW_RECT_FILL)

#define Widget_FillRectWithBorder(nNodeId, pDisp, pRect, nBorderColor, nXBorder, nYBorder, nFillColor, b3D) \
    IDISPLAY_DrawRect(pDisp, pRect, nBorderColor, nFillColor, DRAW_RECT_FILL_BORDER)

#define Widget_DrawRectBorder(nNodeId, pDisp, pRect, nColor, nXBorder, nYBorder, b3D) \
    IDISPLAY_DrawRect(pDisp, pRect, nColor, nColor, DRAW_RECT_BORDER)

#define Widget_FillEllipse(nNodeId,pDisp,pEllipse,nColor,b3D) \
    IDISPLAY_DrawEllipse(pDisp,pEllipse,nColor,nColor,DRAW_ELLIPSE_FILL)

#define Widget_FillEllipseWithBorder(nNodeId,pDisp,pEllipse,nBorderColor,nBorderPix,nFillColor,b3D) \
    IDISPLAY_DrawEllipse(pDisp,pEllipse,nBorderColor,nFillColor,DISP_DRAWTYPE_FILL_BOLDER)

#define Widget_DrawEllipseBorder(nNodeId,pDisp,pEllipse,nColor,nBorderPix,b3D) \
    IDISPLAY_DrawEllipse(pDisp,pEllipse,nColor,nColor,DRAW_ELLIPSE_BORDER)

#define Widget_DrawDispText(pWdg, nNodeId, pRawDataId, pDisp, FontCat, FontSize, pText, Chars, x, y, pRect, Types, nBgColor, b3D) \
    IDISPLAY_DrawDispText(pDisp, FontCat, FontSize, pText, Chars, x, y, pRect, Types)

#define Widget_DrawText(pWdg, nNodeId, pRawDataId, pDisp, FontCat, FontSize, pText, Chars, x, y, pRect, Types, nBgColor, b3D) \
    IDISPLAY_DrawText(pDisp, FontCat, FontSize, pText, Chars, x, y, pRect, Types)

#define Widget_DrawBmp(pWdg, nNodeId, pnRawDataId, pDisp, pDstRc, pBmp, pSrcRc, b3D) \
    IDISPLAY_BitBlt(pDisp, pDstRc, pBmp, pSrcRc, ROP_COPYSRC)

#define Widget_DrawImg(pWdg, nNodeId, pnRawDataId, pDisp, pDstRc, pImg, pSrcRc, b3D) \
    IIMAGE_Draw(pImg, (pDstRc)->x, (pDstRc)->y, pDisp)

#define Widget_DrawColorfulDispText(pWdg, nNodeId, pRawDataId, pDisp, FontCat, FontSize, pText, Chars, x, y, pDrawRect, Types, pColors, nNumColor, nBgColor, b3D) \
	IDISPLAY_DrawColorfulDispText(pDisp,FontCat,FontSize,pText,Chars,x,y,pDrawRect,Types, pColors, nNumColor)

#define Widget_DrawColorfulText(pWdg, nNodeId, pRawDataId, pDisp, FontCat, FontSize, pText, Chars, x, y, pDrawRect, Types, pColors, nNumColor, nBgColor, b3D) \
	IDISPLAY_DrawColorfulText(pDisp,FontCat,FontSize,pText,Chars,x,y,pDrawRect,Types, pColors, nNumColor)

#endif
#endif //__MAE_WIDGET_COMMON_H__
/*=============================================================*/
// end of file
