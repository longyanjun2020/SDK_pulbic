/**
 * @file    mmi_wdg_scrollbar.h
 * @brief   This file defines the interface of scrollbar widget.
 *
 *
 *  The purpose of ScrollBar widget is to provide the scroll bar for the window.
 *  There are several styles of ScrollBar widget by setting ScrollBarStyle_e
 *  element, such as SCROLL_STYLE_V_RIGHT referring to Vertical Right scroll
 *  bar. Moreover, scroll bar can be put both vertically and horizontally by only creating
 *  one Scroll Bar widget, using bitwise operation to assign ScrollBarStyle_e value.
 *
 *
 *          ex: The Horizontal Down scroll bar
 *           +----------------------------------------------+
 *           |                                              |
 *           |                                              |
 *           |  ******|&|********************************  ||
 *           +----------------------------------------------+
 *                        ^ &:indicator, *:horizontal bar
 */

#ifndef __MMI_WDG_SCROLLBAR_H__
#define __MMI_WDG_SCROLLBAR_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/

//Vertical Scrollbar Style
enum e_Scrollbar_V_Style
{
  //SCROLL_V_START=0x00,
  SCROLL_V_NONE=0x00,  //No Vertical Scroller
  SCROLL_V_RIGHT,      //The Vertical Scroller will be drawn on the right side of the content
  SCROLL_V_LEFT,       //The Vertical Scroller will be drawn on the left side of the content
  SCROLL_V_TOTAL,
  SCROLL_V_MASK=0x0F,
};

//Horizontal Scrollbar Style
enum e_Scrollbar_H_Style
{
  //SCROLL_H_START=0x00,
  SCROLL_H_NONE=0x00,   //No Horizontal Scroller
  SCROLL_H_BOTTOM=0x10,    //The Horizontal Scroller will be drawn at the bottom of the content
  SCROLL_H_TOP=0x20,    //The Horizontal Scroller will be drawn at the top of the content
  SCROLL_H_TOTAL=0x30,
  SCROLL_H_MASK=0xF0,
};

#define SCROLL_PRESS_NONE  0
#define SCROLL_PRESS_DOWN  1
#define SCROLL_PRESS_STYLE 2

/** ScrollBarInd_Imgs_t
*
* @brief    
*           pImg_Start:               
*           pImg_Repeat:
*           pImg_Center:
*           pImg_End:
*
*/
typedef struct{
    IImage *pImg_Start[SCROLL_PRESS_STYLE];    /*[None, Down]*/
    IImage *pImg_Repeat[SCROLL_PRESS_STYLE];   /*[None, Down]*/
    IImage *pImg_Center[SCROLL_PRESS_STYLE];   /*[None, Down]*/
    IImage *pImg_End[SCROLL_PRESS_STYLE];      /*[None, Down]*/
}ScrollBarInd_Imgs_t;

/** ScrollArrow_Imgs_t
*
* @brief    
*           pImg_Arrow_Previous:               
*           pImg_Arrow_Next:
*
*/
typedef struct{
    IImage *pImg_Arrow_Previous[SCROLL_PRESS_STYLE];   /*[None, Down]*/
    IImage *pImg_Arrow_Next[SCROLL_PRESS_STYLE];       /*[None, Down]*/
}ScrollArrow_Imgs_t;

/** ScrollArrow_Imgs_t
*
* @brief    
*           ClrBorder:               
*           ClrFill:
*           Flags:               
*           Ver_Width:             
*           Hor_Height:
*
*/
typedef struct{
    RGBColor_t ClrBorder;
    RGBColor_t ClrFill;
    u32 Flags;
    u16 Ver_Width;
    u16 Hor_Height;
}ScrollBarRectInfo;

#if defined(SCROLLBAR_INDICATOR_MIN_HEIGHT)
#define SCROLL_INDICATOR_MIN_HEIGHT     SCROLLBAR_INDICATOR_MIN_HEIGHT
#else
#define SCROLL_INDICATOR_MIN_HEIGHT     (3)
#endif

#if defined(SCROLLBAR_INDICATOR_MIN_WIDTH)
#define SCROLL_INDICATOR_MIN_WIDTH      SCROLLBAR_INDICATOR_MIN_WIDTH
#else
#define SCROLL_INDICATOR_MIN_WIDTH      (3)
#endif

/** ScrollBarStyle_e
*
* @brief    ScrollBarStyle_e:  Scrollbar style.
*
*/
typedef enum
{
    SCROLL_STYLE_V_NONE   = 0x00,   //No Vertical ScrollBar
    SCROLL_STYLE_H_NONE   = 0x00,   //No Horizontal ScrollBar
    SCROLL_STYLE_V_RIGHT,           //The Vertical ScrollBar will be drawn on the right side of the content
    SCROLL_STYLE_V_LEFT,            //The Vertical ScrollBar will be drawn on the left side of the content
    SCROLL_STYLE_V_TOTAL,
    SCROLL_STYLE_V_MASK   = 0x0F,
    SCROLL_STYLE_H_BOTTOM = 0x10,   //The Horizontal ScrollBar will be drawn on the bottom of the content
    SCROLL_STYLE_H_TOP       = 0x20,//The Horizontal ScrollBar will be drawn on the top of the content
    SCROLL_STYLE_H_TOTAL  = 0x30,
    SCROLL_STYLE_H_MASK    = 0xF0
} ScrollBarStyle_e;
typedef u8 ScrollBarStyle_t;
/** ScrollBarOption_e
*
* @brief    ScrollBarOption_e:  Indicate vertical or horizontal scrollbar.
*
*/
typedef enum
{
    SCROLL_OPTION_VERTICAL       = 0x00,   //Set vertical bar style
    SCROLL_OPTION_HORIZONTAL     = 0x01    //Set horizontal bar style
} ScrollBarOption_e;

/** WdgScrollDataType_e
*
* @brief    WdgScrollDataType_e:  The scroll bar display type.
*
*/
typedef enum
{
    WDG_SCROLL_DATA_TYPE_VIEW_RANGE = SCROLL_DATA_TYPE_VIEW_RANGE,
    WDG_SCROLL_DATA_TYPE_ITEM_NUMBER = SCROLL_DATA_TYPE_ITEM_NUMBER
} WdgScrollDataType_e;

/** WdgScrollBarCfgData_t
*
* @brief    pDecoratorWdg:  The widget be decorator(usually : Text, list, viewport, input, MflContainer and ViewerContainer).
*           eScrollStyle:   Scrollbar Scroll Style.
*
*/
typedef struct
{
    IWidget                 *pDecoratorWdg;
    ScrollBarStyle_e         eScrollStyle;
}WdgScrollBarCfgData_t;

/** WdgScrollBarDisplayData_t
*
* @brief    nIndSize:       Size of Indicator item
*                           (Horizontal : the height of Horizontal Indicator item).
*                           (Vertical   : the width of Vertical Indicator item).
*
*           nBarSize:       Size of Scroll Bar
*                           (Horizontal : the height of Horizontal Scroll Bar).
*                           (Vertical   : the width of Vertical Scroll Bar).
*
*           nVisibleRange:  Visible range of the scroll bar.
*                           (Horizontal : the width of Indicator item).
*                           (Vertical   : the height of Indicator item).
*
*           nTotalRange:    Total range of the scroll bar.
*                           (Horizontal : the total width of Horizontal Scroll Bar).
*                           (Vertical   : the total height of Vertical Scroll Bar).
*
*               Ex: The child of the scroll bar widget is a image widget, with an 150 pixel width image,
*                   But the child size width (the width of child widget visible area) is only 100 pixel, and now it show the 20~119 pixel
*                   =>Total Range: 150
*                   =>Visible Range: 100
*                   =>Current Position: 20
*                   =>bFocus Item: FALSE
*
*           pTrackFocus: scroll track the focus item or not.
*
*               Original Scroll:
*               ----------------------------
*               |   (4)   |  (5)   |  (6)  |
*               |         |        |       |
*               |         | (focus | (last |
*               |         |  item  |  item)|
*               ----------------------------
*               |********|&&&&|************|
*               ----------------------------
*
*               TRUE : focus from (5) to (6) ==> scroll indicator moving when focus change even in the same page as below.
*               ----------------------------
*               |*********************|&&&&|
*               ----------------------------
*
*               False: focus from (5) to (6) ==> scroll indicator stay when focus change in the same page.
*               ----------------------------
*               |*********|&&&&|***********|
*               ----------------------------
*
*           pBarBmps:       Relative Bitmaps of Scroll Bar.
*           pIndBmps:       Relative Bitmaps of Indicator item.
*           pArrowBmps:     Relative Bitmaps of Scroll Arrow.
*
*               Example,
*
*               ---------------------------------
*               |   (4)   |  (5)    |  (6)    |OO|
*               |         |         |         |OO| <OO: Vertical Bar
*               |  item   |  item   |  item   |OO|
*               |         |         |         |--|
*               |   4th   |   5th   |   6th   |$$| <$$: Vertical Indicator
*               |         |         |         |--|
*               |         |(focus   | (last   |OO|
*               |         |  item ) |  item)  |OO|
*               |         |         |         |OO|
*               ---------------------------|-----|
*               |******************** |&&&|******|
*               ---------------------------|-----|
*                ^                    ^
*                *: Horizontal Bar  &&&: Horizontal Indicator (not at the end of the scroll)
*/
typedef struct
{
    boolean     pTrackFocus;

    u16         nIndSize;
    u16         nBarSize;

    u32         nVisibleRange;
    u32         nTotalRange;

    ScrollBarInd_Imgs_t     *pBarBmps;
    ScrollBarInd_Imgs_t     *pIndBmps;
    ScrollArrow_Imgs_t      *pArrowBmps;
}WdgScrollBarDisplayData_t;

/** WdgScrollData_t
*
* @brief    u32TotalSize:       Number of total items / Number of total pixels
*           u32CurrentPos:      A zero-based index for current position / Coordinate for current position
*           u32VisibleSize:     Number of items in the visible range / Number of pixels in the visible range
*           eType:              Indicate nTotal,nPos and nVisible are used for pixels or item number
*           bVertical:          Vertical or Horizontal. TRUE=> Vertical scroll data, FALSE => Horizontal scroll data
*
*/
typedef struct
{
    u32                 u32TotalSize;          ///< Number of total items / Number of total pixels
    u32                 u32CurrentPos;         ///< A zero-based index for current position / Coordinate for current position
    u32                 u32VisibleSize;        ///< Number of items in the visible range / Number of pixels in the visible range
    WdgScrollDataType_e eType; ///< Indicate nTotal,nPos and nVisible are used for pixels or item number
    boolean             bVertical;         ///< Vertical or Horizontal. TRUE=> Vertical scroll data, FALSE => Horizontal scroll data
} WdgScrollData_t;

/** WdgScrollStep_t
*
* @brief    u16Step:       Number of step item
*           bVertical:     Vertical or Horizontal. TRUE=> Vertical scroll change data, FALSE => Horizontal scroll change data
*
*/
typedef struct
{
    u16     u16Step;       ///< Number of step item
    boolean bVertical; ///< Vertical or Horizontal. TRUE=> Vertical scroll change data, FALSE => Horizontal scroll change data
} WdgScrollStep_t;

/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
//Common Function

/** WdgScrollBarCreateForWnd
* @brief        ScrollBar widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pData           Widget Common Data, refer to WdgScrollBarCfgData_t.
*
* @retval       The pointer of ScrollBar pointer        Success.
* @retval       NULL                                    Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgScrollBarCreateForWnd
(
    HWIN                hWin,
    Pos_t                      *pPos,
    WidgetSize_t               *pSize,
    u16                         nWidgetID,
    WdgScrollBarCfgData_t      *pData
);

/** WdgScrollBarCommonSetDisplay
* @brief        ScrollBar widget Set Common Display Function
*
* @param[in]    pWDGScrollBar     The scrollbar widget will be destroyed
* @param[in]    eStyle            Vertical or Horizontal ScrollBar want to set.
* @param[in]    pDisplayData      Common Display Data of ScrollBar, refer to WdgScrollBarDisplayData_t.
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret WdgScrollBarCommonSetDisplay
(
    IWidget                     *pWDGScrollBar,
    ScrollBarOption_e            eStyle,
    WdgScrollBarDisplayData_t   *pDisplayData
);

/*=============================================================*/
/** WdgScrollBarCreate
* @brief        Create ScrollBar widget
*
* @retval       The pointer of ScrollBar        Success.
* @retval       NULL                            Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgScrollBarCreate
(
    void
);

//Set Function
/** WdgScrollBarSetStyle
* @brief        Set ScrollBar widget scroll style
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be set
* @param[in]    eScrollStyle        The scroll style which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgScrollBarSetStyle
(
    IWidget                 *pWDGScrollBar,
    ScrollBarStyle_e        eScrollStyle
);

/** WdgScrollBarSetBorderColor
* @brief        Set ScrollBar widget bar border color
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    tBorderColor    The bar border color which will be set to the scrollbar widget.
*
* @retval      void
*
*/
void WdgScrollBarSetBorderColor
(
    IWidget     *pWDGScrollBar,
    RGBColor_t  tBorderColor
);

/** WdgScrollBarSetBarFillColor
* @brief        Set ScrollBar widget bar fill color
*
* @param[in]    pWDGScrollBar     The scrollbar widget which want to be set
* @param[in]    tFillColor        The bar fill color which will be set to the scrollbar widget.
*
* @retval      void
*
*/
void WdgScrollBarSetBarFillColor
(
    IWidget     *pWDGScrollBar,
    RGBColor_t  tFillColor
);

/** WdgScrollBarSetRectFlag
* @brief        Set ScrollBar widget bar rect flag
*
* @param[in]    pWDGScrollBar      The scrollbar widget which want to be set
* @param[in]    nFlag              The bar rect flag which will be set to the scrollbar widget,
*                                  refer to DRAW_RECT_BORDER ~ DRAW_RECT_TOTAL.
*
* @retval       void
*
*/
void WdgScrollBarSetRectFlag
(
    IWidget     *pWDGScrollBar,
    u32         nFlag
);

/** WdgScrollBarSetIndBorderColor
* @brief        Set ScrollBar widget indicator border color
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    tBorderColor    The indicator border color which will be set to the scrollbar widget.
*
* @retval       void
*
*/
void WdgScrollBarSetIndBorderColor
(
    IWidget     *pWDGScrollBar,
    RGBColor_t  tBorderColor
);

/** WdgScrollBarSetIndFillColor
* @brief        Set ScrollBar widget indicator fill color
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be set
* @param[in]    tFillColor          The indicator fill color which will be set to the scrollbar widget.
*
* @retval       void
*
*/
void WdgScrollBarSetIndFillColor
(
    IWidget     *pWDGScrollBar,
    RGBColor_t  tFillColor
);

/** WdgScrollBarSetIndRectFlag
* @brief        Set ScrollBar widget indicator rect flag
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be set
* @param[in]    nFlag               The indicator rect flag which will be set to the scrollbar widget.
*                                   refer to DRAW_RECT_BORDER ~ DRAW_RECT_TOTAL.
*
* @retval       void
*
*/
void WdgScrollBarSetIndRectFlag
(
    IWidget     *pWDGScrollBar,
    u32         nFlag
);

/** WdgScrollBarSetHorBarBmps
* @brief        Set ScrollBar widget horizontal bar bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pHorBarBmps     The horizontal bar bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetHorBarBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollBarInd_Imgs_t     *pHorBarBmps
);

/** WdgScrollBarSetHorIndBmps
* @brief        Set ScrollBar widget horizontal indicator bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pHorIndBmps     The horizontal indicator bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetHorIndBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollBarInd_Imgs_t     *pHorIndBmps
);

/** WdgScrollBarSetHorArrowBmps
* @brief        Set ScrollBar widget horizontal arrow bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pHorArrowBmps   The horizontal arrow bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgScrollBarSetHorArrowBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollArrow_Imgs_t      *pHorArrowBmps
);

/** WdgScrollBarSetHorTsAbility
* @brief        Set ScrollBar widget horizontal ability to update the position of scroll indicator according to touched position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bEnable         The horizontal ability which will be set to the scrollbar widget.
*
* @retval       void
*/
void WdgScrollBarSetHorTsAbility
(
    IWidget     *pWDGScrollBar,
    boolean     bEnable
);

/** WdgScrollBarSetHorRange
* @brief        Set ScrollBar widget horizontal total range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nTotalRange     The horizontal total range which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgScrollBarSetHorRange
(
    IWidget     *pWDGScrollBar,
    u32         nTotalRange
);

/** WdgScrollBarSetHorVisibleRange
* @brief        Set ScrollBar widget horizontal visible range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nVisibleRange   The horizontal visible range which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetHorVisibleRange
(
    IWidget     *pWDGScrollBar,
    u32         nVisibleRange
);

/** WdgScrollBarSetHorCurPos
* @brief        Set ScrollBar widget horizontal current position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nCurrentPos     The horizontal current position which will be set to the scrollbar widget.
*
* @retval       void
*
*/
void WdgScrollBarSetHorCurPos
(
    IWidget     *pWDGScrollBar,
    u32         nCurrentPos
);

/** WdgScrollBarSetKeepHorScrollSpace
* @brief        Set if the horizontal scrollbar widget keeps the width or not
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bKeep           The horizontal scrollbar widget keeps the width or not
*
* @retval       void
*
*/
void WdgScrollBarSetKeepHorScrollSpace
(
    IWidget     *pWDGScrollBar,
    boolean     bKeep
);

/** WdgScrollBarSetHorbarHeight
* @brief        Set ScrollBar widget horizontal bar rect height
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nHeight         The horizontal bar rect height which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgScrollBarSetHorbarHeight
(
    IWidget     *pWDGScrollBar,
    u16         nHeight
);

/** WdgScrollBarSetHorIndHeight
* @brief        Set ScrollBar widget horizontal indicator rect height
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nHeight         The horizontal indicator rect height which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetHorIndHeight
(
    IWidget     *pWDGScrollBar,
    u16         nHeight
);

/** WdgScrollBarSetHorHandleFocusEvent
* @brief        Set ScrollBar widget horizontal handle focus event type
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bHdlFcsEvt          if TRUE check Focus change event, if FALSE check Scroll Change event
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/

MAE_Ret WdgScrollBarSetHorHandleFocusEvent
(
    IWidget     *pWDGScrollBar,
    boolean	bHdlFcsEvt
);

/** WdgScrollBarSetVerBarBmps
* @brief        Set ScrollBar widget vertical bar bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pVerBarBmps     The vertical bar bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetVerBarBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollBarInd_Imgs_t     *pVerBarBmps
);

/** WdgScrollBarSetVerIndBmps
* @brief        Set ScrollBar widget vertical indicator bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pVerIndBmps     The vertical indicator bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetVerIndBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollBarInd_Imgs_t     *pVerIndBmps
);

/** WdgScrollBarSetVerArrowBmps
* @brief        Set ScrollBar widget vertical arrow bmps
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    pVerArrowBmps   The vertical arrow bmps which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetVerArrowBmps
(
    IWidget                 *pWDGScrollBar,
    ScrollArrow_Imgs_t      *pVerArrowBmps
);

/** WdgScrollBarSetVerTsAbility
* @brief        Set ScrollBar widget vertical ability to update the position of scroll indicator accroding to touched position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bEnable         The vertical ability which will be set to the scrollbar widget.
*
* @retval       void
*
*/
void WdgScrollBarSetVerTsAbility
(
    IWidget     *pWDGScrollBar,
    boolean     bEnable
);

/** WdgScrollBarSetVerRange
* @brief        Set ScrollBar widget vertical total range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nTotalRange     The vertical total range which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgScrollBarSetVerRange
(
    IWidget     *pWDGScrollBar,
    u32         nTotalRange
);

/** WdgScrollBarSetVerVisibleRange
* @brief        Set ScrollBar widget vertical visible range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nVisibleRange   The vertical visible range which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetVerVisibleRange
(
    IWidget     *pWDGScrollBar,
    u32         nVisibleRange
);

/** WdgScrollBarSetVerCurPos
* @brief        Set ScrollBar widget vertical current position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nCurrentPos     The vertical current position which will be set to the scrollbar widget.
*
* @retval       void
*
*/
void WdgScrollBarSetVerCurPos
(
    IWidget     *pWDGScrollBar,
    u32         nCurrentPos
);

/** WdgScrollBarSetKeepVerScrollSpace
* @brief        Set if the vertical scrollbar widget keeps the width or not
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bKeep           The vertical scrollbar widget keeps the width or not
*
* @retval       void
*
*/
void WdgScrollBarSetKeepVerScrollSpace
(
    IWidget     *pWDGScrollBar,
    boolean     bKeep
);

/** WdgScrollBarSetVerBarWidth
* @brief        Set ScrollBar widget vertical bar rect width
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nWidth          The vertical bar rect width which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgScrollBarSetVerBarWidth
(
    IWidget     *pWDGScrollBar,
    u16         nWidth
);

/** WdgScrollBarSetVerIndWidth
* @brief        Set ScrollBar widget vertical indicator rect width
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    nWidth          The vertical indicator width which will be set to the scrollbar widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/

MAE_Ret WdgScrollBarSetVerIndWidth
(
    IWidget     *pWDGScrollBar,
    u16         nWidth
);

/** WdgScrollBarSetVerHandleFocusEvent
* @brief        Set ScrollBar widget vertical handle focus event type
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be set
* @param[in]    bHdlFcsEvt          if TRUE check Focus change event, if FALSE check Scroll Change event
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/

MAE_Ret WdgScrollBarSetVerHandleFocusEvent
(
    IWidget     *pWDGScrollBar,
    boolean	bHdlFcsEvt
);

/** WdgScrollBarSetDecoratorWdg
* @brief        Set the widget which is decorated by scrollbar widget
*               To decorate other widget that size is bigger than region we can use scrollbar to browse it.
*               Ex, A view of picture is large than cell phone screen.
*               Ex, To decorate viewport widget with image.
*
* @param[in]    pWDGScrollBar         The scrollbar widget which want to be set
* @param[in]    pChild                The widget which is decorated by scrollbar widget.
*
* @retval       None.
*/
__SLDPM_FREE__ void WdgScrollBarSetDecoratorWdg
(
    IWidget                 *pWDGScrollBar,
    IWidget                 *pChild
);

//Get Function
/** WdgScrollBarGetStyle
* @brief        Get ScrollBar widget scroll style
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       ScrollBarStyle_e    The scroll style which will be gotten from the scrollbar widget.
*
*/
ScrollBarStyle_e WdgScrollBarGetStyle
(
    IWidget                 *pWDGScrollBar
);

/** WdgScrollBarGetBorderColor
* @brief        Get ScrollBar widget bar border color
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval      RGBColor_t           The bar border color which will be gotten from the scrollbar widget.
*
*/
RGBColor_t WdgScrollBarGetBorderColor
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetBarFillColor
* @brief        Get ScrollBar widget bar fill color
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       RGBColor_t.         The bar fill color which will be gotten from the scrollbar widget.
*
*/
RGBColor_t WdgScrollBarGetBarFillColor
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetBarRectFlag
* @brief        Get ScrollBar widget bar rect flag
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       u32                 The bar rect flag which will be gotten from the scrollbar widget.
*
*/
u32 WdgScrollBarGetBarRectFlag
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetIndBorderColor
* @brief        Get ScrollBar widget indicator border color
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       RGBColor_t          The indicator border color which will be gotten from the scrollbar widget.
*
*/
RGBColor_t WdgScrollBarGetIndBorderColor
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetIndFillColor
* @brief        Get ScrollBar widget indicator fill color
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       RGBColor_t          The indicator fill color which will be gotten from the scrollbar widget.
*
*/
RGBColor_t WdgScrollBarGetIndFillColor
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetIndRectFlag
* @brief        Get ScrollBar widget indicator rect flag
*
* @param[in]    pWDGScrollBar       The scrollbar widget which want to be gotten
*
* @retval       u32                 The indicator rect flag which will be gotten from the scrollbar widget.
*/
u32 WdgScrollBarGetIndRectFlag
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarIsHorTsAbility
* @brief        Get ScrollBar widget horizontal ability to update the position of scroll indicator accroding to touched position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       boolean         The horizontal ability which will be gotten from the scrollbar widget.
*
*/
boolean WdgScrollBarIsHorTsAbility
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollbarGetHorTotalRange
* @brief        Get ScrollBar widget horizontal total range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32             The horizontal total range which will be gotten from the scrollbar widget.
*/
u32 WdgScrollbarGetHorTotalRange
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollbarGetHorVisibleRange
* @brief        Get ScrollBar widget horizontal visible range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32             The horizontal visible range which will be gotten from the scrollbar widget.
*
*/
u32 WdgScrollbarGetHorVisibleRange
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetHorCurPos
* @brief        Get ScrollBar widget horizontal current position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32             The horizontal current position which will be gotten from the scrollbar widget.
*
*/
u32 WdgScrollBarGetHorCurPos
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetHorBarHeight
* @brief        Get ScrollBar widget horizontal bar rect height
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u16             The horizontal bar rect height which will be gotten from the scrollbar widget.
*
*/
u16 WdgScrollBarGetHorBarHeight
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetHorIndHeight
* @brief        Get ScrollBar widget horizontal indicator rect height
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u16             The horizontal indicator rect height which will be gotten from the scrollbar widget
*
*/
u16 WdgScrollBarGetHorIndHeight
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarIsVerTsAbility
* @brief        Get ScrollBar widget vertical ability to update the position of scroll indicator according to touched position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       boolean         The vertical ability which will be gotten from the scrollbar widget.
*/
boolean WdgScrollBarIsVerTsAbility
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetVerTotalRange
* @brief        Get ScrollBar widget vertical total range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32             The vertical total range which will be gotten from the scrollbar widget.
*
*/
u32 WdgScrollBarGetVerTotalRange
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetVerVisibleRange
* @brief        Get ScrollBar widget vertical visible range
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32              The vertical visible range which will be gotten from the scrollbar widget.
*
*/
u32 WdgScrollBarGetVerVisibleRange
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetVerCurPos
* @brief        Get ScrollBar widget vertical current position
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u32             The vertical current position which will be gotten from the scrollbar widget.
*/
u32 WdgScrollBarGetVerCurPos
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetVerBarWidth
* @brief        Get ScrollBar widget vertical bar rect width
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u16             The vertical bar rect width which will be gotten from the scrollbar widget
*
*/
__SLDPM_FREE__ u16 WdgScrollBarGetVerBarWidth
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetVerIndWidth
* @brief        Get ScrollBar widget vertical indicator rect width
*
* @param[in]    pWDGScrollBar   The scrollbar widget which want to be gotten
*
* @retval       u16             The vertical indicator rect width which will be gotten from the scrollbar widget
*
*/
u16 WdgScrollBarGetVerIndWidth
(
    IWidget     *pWDGScrollBar
);

/** WdgScrollBarGetDecoratorWidget
* @brief        Get the widget which is decorated by scrollbar widget
*
* @param[in]    pWDGScrollBar  The scrollbar widget which want to be set
*
* @return       The widget which is decorated by scrollbar widget
*/

IWidget*  WdgScrollBarGetDecoratorWidget
(
    IWidget                 *pWDGScrollBar
);

/** WdgScrollBarUpdateScrollData
* @brief  Update the scroll data of the widget
* @param[in]  pWdgScrollBar  The scrollbar widget which want to be set
* @param[in]  psScrollData  The update data.
*/

void WdgScrollBarUpdateScrollData(IWidget *pWdgScrollBar, WdgScrollData_t *psScrollData);

/** WdgScrollBarSetStepChange
* @brief  Update the scroll data of the widget
* @param[in]  pWdgScrollBar  The scrollbar widget which want to be set
* @param[in]  psStep  The update data.
*/

void WdgScrollBarSetStepChange(IWidget *pWdgScrollBar, WdgScrollStep_t *psStep);

typedef void (*PfnWdgScrollbarScrollFinish) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pWidget);

__SLDPM_FREE__ MAE_Ret WdgScrollbarRegisterScrollFinishCb
(
    IWidget                   *pWDGList,
    PfnWdgScrollbarScrollFinish    pfn,
    void                      *pUserData
);
#endif //__MMI_WDG_SCROLLBAR_H__
/*=============================================================*/
// end of file
