/**
* @file    mmi_wdg_basicbitmap_priv.h
* @version $Id: mmi_wdg_basicbitmap_priv.h 20863 2009-01-19 10:59:56Z paul.ouyang $
* 
* @brief   This file defines CLSID_BASICBITMAPWIDGET class which is a kind of Widget object.
*
*<Class Description>
*    Basic bitmap widget is a widget for drawing some basic graphic like line, rectangle, circle.
*
*    The basic bitmap widget default brush and filled color is RGBCOLOR_BLACK and graphic type is WDG_BASIC_BITMAP_NONE.
*    Application can change the widget graphic type by set property "PROP_BASICBMP_WDG_GRAPHIC_TYPE".
*    If a widget width of horizontal line is larger than brush width, the horizontal will be draw on the center of the widget.
*
*    Application can use IWIDGET_SetSize() to change the size of graphic.
*    Set property "PROP_BASICBMP_WDG_ROTATE" is only supported in ABS container.
*
*
*/

#ifndef __MMI_WDG_BASICBITMAP_PRIV_H__
#define __MMI_WDG_BASICBITMAP_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"    
#include "mae_widgetbase.h"
#include "mmi_mae_widget.h"


/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    u8 nDisplayBrushSize;
    u16 nPixel;
} _BasicBmpWdgBrushInf_t;

typedef struct 
{
    WidgetBaseEx_t WdgBase;  //WidgetBase_t to WidgetBaseEx_t
    Wdg_BasicBitmapGraphicType_et eGraphicType;
    Wdg_BasicBitmapBrushType_et eBrush;
    Wdg_BasicBitmapRotateType_et eRotate;
    RGBColor_t nDrawLineColor;
    RGBColor_t nFilledColor;
    boolean bIsFilled;
} WdgBasicBmp_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret BasicBitmapWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgBasicBmpDefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _WdgBasicBmpConstructor(WdgBasicBmp_t *pThis);

static void _WdgBasicBmpDestructor(WdgBasicBmp_t *pThis);

///for IWidget interface

static void _WdgBasicBmpGetPreferredSize(IWidget *pWdg, WidgetSize_t *pSize);
static void _WdgBasicBmpDraw(IWidget *pWdg, IDispCanvas *pIDispCanvas, s32 x, s32 y);

///other internal functions

static boolean _WdgBasicBmpRotateAndSetPos( WdgBasicBmp_t *pThis, Wdg_BasicBitmapRotateType_et eRotate );
static boolean _WdgBasicBmpDrawHLine( WdgBasicBmp_t *pThis, IDispCanvas *pIDispCanvas, Rect_t sWidgetRect, boolean b3D );
static boolean _WdgBasicBmpDrawVLine( WdgBasicBmp_t *pThis, IDispCanvas *pIDispCanvas, Rect_t sWidgetRect, boolean b3D );
static boolean _WdgBasicBmpDrawSLine( WdgBasicBmp_t *pThis, IDispCanvas *pIDispCanvas, Rect_t sWidgetRect, boolean bAnti, boolean b3D );
static boolean _WdgBasicBmpDrawRectangle( WdgBasicBmp_t *pThis, IDispCanvas *pIDispCanvas, Rect_t sWidgetRect, boolean b3D );
static boolean _WdgBasicBmpDrawCircle( WdgBasicBmp_t *pThis, IDispCanvas *pIDispCanvas, Rect_t sWidgetRect, boolean b3D );

#endif //__MMI_WDG_BASICBITMAP_PRIV_H__
/*=============================================================*/
// end of file
