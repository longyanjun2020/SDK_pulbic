/**
 * @file    mmi_wdg_canvas_priv.h
 * @author  alison.chen@mstarsemi.com
 * 
 * @version $Id: mmi_wdg_canvas_priv.h 4291 2007-11-19 03:56:54Z alison.chen $
 *
 *
 * @brief   
 *
 */

#ifndef __MMI_WDG_CANVAS_PRIV_H__
#define __MMI_WDG_CANVAS_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"
#include "mmi_wdg_canvas.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	 WidgetBaseEx_t WdgBase;	// the basic structure
	 IBitmap *pCanvasBmp;		// the canvas bmp
	 IDisplay *pDisp;						// the display instance
	 Rect_t	tViewportRc;					// the viewport of canvas
	 RGBColor_t	nFgClr;				// the foreground color
	 RGBColor_t	nBgClr;			// the background color
	 RGBColor_t	nLineClr;		// the line and border color
	 RGBColor_t	nFontClr;			// the font color
	 RGBColor_t	nFontOutlineClr;			// the font outline color
	 FontType_t	nFontType;		// the font type
	 FontCategory_t nFontCate;	// the font category
	 CanvasTransparentInfo_t tTransInfo;	// the transparent type
	 DisplayDottedType_e nLineType;	// the line type
	 u8 nBrushSize;						// the brush size
} WdgCanvas_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret CanvasWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgCanvasDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _WdgCanvasConstructor(WdgCanvas_t*);
static void _WdgCanvasDestructor(WdgCanvas_t *pThis);

static void _WdgCanvasDefDraw(WdgCanvas_t *pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static boolean _WdgCanvasSetProperty(WdgCanvas_t *pThis, u32 P1, u32 P2);
static void _WdgCanvasInvalidate(WdgCanvas_t *pThis);

#endif //__MMI_WDG_CANVAS_PRIV_H__
/*=============================================================*/
// end of file
