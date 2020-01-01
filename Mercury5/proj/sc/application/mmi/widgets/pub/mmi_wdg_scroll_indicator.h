/**
* @file    mmi_wdg_scroll_indicator.h
* @version $Id: mmi_wdg_scroll_indicator.h 39576 2009-09-07 08:54:00Z steve.lee $
* @brief
*<Description>
*    Scroll-indicator widget and Scroll-bar widget are very similar, which is also a decorator
*    widget. It is mainly used in list menu to tell whether there are any more informations.
*    Scroll-indicator widget can support with List widget, Grid widget, MFL container,
*    Viewport widget, and Input widget. Scroll-indicator widget can display the horizontal
*    and vertical scroll bar at the same time. AP can change arrow images by setting
*    properties. In addition List Widget also supports Padding, Border, and Background
*    color/image.
*
* Horizontal type:
*        -----------------------------------------------
*        | /|  |                                 | |\  |
*        | \|  |       Item Widget               | |/  |
*        |-----|---------------------------------|-----|
*
* Vertical type:
*        +---------------------+-
*        |        /\           |
*        |       /__\          |
*        +---------------------+-
*        |    Item Widget      |
*        +---------------------+-
*        |       \--/          |
*        |        \/           |
*        +---------------------+-
*
*/

#ifndef __MMI_WDG_SCROLL_INDICATOR_H__
#define __MMI_WDG_SCROLL_INDICATOR_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum {
	ARROW_BEGIN = 0,
	ARROW_LEFT = ARROW_BEGIN,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_END,
	ARROW_NUM = ARROW_END
};
typedef u8 _ArrowDir_t;

/** WdgScrlIndCfgData_t
*
* @brief
*           bInside:
*           pDecoratorWdg:
*           pSize:
*           eLayoutStyle:
*
*/
typedef struct
{
    boolean                 bInside;
    IWidget                 *pDecoratorWdg;
    WidgetSize_t            *pSize;
    WdgLayoutStyle_e        eLayoutStyle;
}WdgScrlIndCfgData_t;


/*=============================================================*/
// functions
/*=============================================================*/
/*=============================================================*/
//Common Function
/** WdgScrlIndCreateForWnd
* @brief        Basic Scroll Indicator widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pData           Widget Common Data, refer to WdgScrlIndCfgData_t.
*                               If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Scroll Indicator pointer     Success.
* @retval       NULL                                        Failed.
*
*/
IWidget* WdgScrlIndCreateForWnd
(
    HWIN                     hWin,
    Pos_t                           *pPos,
    WidgetSize_t                    *pSize,
    u16                             nWidgetID,
    WdgScrlIndCfgData_t             *pData
);
/*=============================================================*/
/** WdgScrlIndCreate
* @brief        Create Scroll Indicator widget
*
* @retval       The pointer of Scroll Indicator pointer     Success.
* @retval       NULL                                        Failed.
*
*/
IWidget* WdgScrlIndCreate
(
    void
);

/** WdgScrlIndSetArrowInside
* @brief        Set arrow inside or outside of the item widget.
*
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    bInside           TRUE: Arrow is inside of item widget.
*                                 FALSE: Arrow is outside of item widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgScrlIndSetArrowInside
(
    IWidget                 *pWDGScrlInd,
    boolean                 bInside
)
{
     return WdgCommonSetProperty(pWDGScrlInd, PROP_SCLIND_WDG_ARROW_POSITION, (u32)bInside);
}

/** WdgScrlIndSetInvisibleIfDisable
* @brief        Set arrow to be invisible if it is disable
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    bInvisible        The invisible status
*                                 TRUE  : Arrow is invisible if it is disable.
*                                 FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetInvisibleIfDisable
(
    IWidget                 *pWDGScrlInd,
    boolean                 bInvisible
)
{
     WdgCommonSetProperty(pWDGScrlInd, PROP_SCLIND_WDG_INVISIBLE_IF_DISABLE, (u32)bInvisible);
}

/** WdgScrlIndSetArrowWidth
* @brief        Set Scroll Indicator widget's arrow width in pixel
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    nWidth            The arrow width in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetArrowWidth
(
    IWidget             *pWDGScrlInd,
    u16                 nWidth,
    Direction_e         eDirection
)
{
     WdgCommonSetArrowWidth(pWDGScrlInd, nWidth, eDirection);
}

/** WdgScrlIndSetLeftArrowWidth
* @brief        Set Scroll Indicator widget's left arrow width in pixel
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    nWidth            The arrow width in pixel
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetLeftArrowWidth
(
    IWidget             *pWDGScrlInd,
    u32                 nWidth
)
{
     WdgCommonSetProperty(pWDGScrlInd, PROP_SCLIND_WDG_LEFT_ARROW_WIDTH, nWidth);
}

/** WdgScrlIndSetRightArrowWidth
* @brief        Set Scroll Indicator widget's right arrow width in pixel
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    nWidth            The arrow width in pixel
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetRightArrowWidth
(
    IWidget             *pWDGScrlInd,
    u32                 nWidth
)
{
     WdgCommonSetProperty(pWDGScrlInd, PROP_SCLIND_WDG_RIGHT_ARROW_WIDTH, nWidth);
}

/** WdgScrlIndSetArrowHeight
* @brief        Set Scroll Indicator widget's arrow height in pixel
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    nHeight           The arrow height in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetArrowHeight
(
    IWidget             *pWDGScrlInd,
    u16                 nHeight,
    Direction_e         eDirection
)
{
     WdgCommonSetArrowHeight(pWDGScrlInd, nHeight, eDirection);
}

/** WdgScrlIndSetArrowActiveImg
* @brief        Set arrow active image
*
* @param[in]    pWDGScrlInd     The scroll indicator widget which want to be set
* @param[in]    pActiveImage    The arrow active image
* @param[in]    eDirection      The arrow type we want to set, refer to Direction_e.
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetArrowActiveImg
(
    IWidget                 *pWDGScrlInd,
    IBitmap                 *pActiveImage,
    Direction_e             eDirection
)
{
     WdgCommonSetArrowActiveImg(pWDGScrlInd, pActiveImage, eDirection);
}

/** WdgScrlIndSetArrowInActiveImg
* @brief        Set arrow inactive image
*
* @param[in]    pWDGScrlInd      The scroll indicator widget which want to be set
* @param[in]    pInActiveImage   The arrow inactive image
* @param[in]    eDirection       The arrow type we want to set, refer to Direction_e.
*
* @retval       None
*
*/
__INLINE void WdgScrlIndSetArrowInActiveImg
(
    IWidget                 *pWDGScrlInd,
    IBitmap                 *pInActiveImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowInActiveImg(pWDGScrlInd, pInActiveImage, eDirection);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgScrlIndSetLeftArrowPressedImg
* @brief        Set image when arrow be pressed
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    pPressedImage     The arrow pressed image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       None
*/
__INLINE void WdgScrlIndSetArrowPressedImg
(
    IWidget                 *pWDGScrlInd,
    IBitmap                 *pPressedImage,
    Direction_e             eDirection
)
{
     WdgCommonSetArrowPressedImg(pWDGScrlInd, pPressedImage, eDirection);
}

#endif //__TOUCH_SCREEN_MMI__


/** WdgScrlIndSetLayoutStyle
* @brief        Set Scroll Indicator widget's layout style
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    eWdgLayoutStyle   The widget layout style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgScrlIndSetLayoutStyle
(
    IWidget                 *pWDGScrlInd,
    WdgLayoutStyle_e        eWdgLayoutStyle
)
{
     return WdgCommonSetProperty(pWDGScrlInd, PROP_LAYOUT_STYLE, (u32)eWdgLayoutStyle);
}


/** WdgScrlIndSetDecoratorWidget
* @brief        Set the widget which is decorated by scroll indicator widget
*               To decorate other widget that size is bigger than region we can use scroll Indicator to browse it.
*               Ex, A view of picture is large than cell phone screen.
*               Ex, To decorate viewport widget with image.
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be set
* @param[in]    pChild            The widget which is decorated by scroll indicator widget.
*
* @retval        None.
*
*/
void WdgScrlIndSetDecoratorWidget
(
    IWidget                 *pWDGScrlInd,
    IWidget                 *pChild
);

/** WdgScrlIndGetArrowPosition
* @brief        Get position info of arrow, inside or outside of the item widget.
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be gotten
*
* @retval       TRUE: Arrow is inside of item widget.
* @retval       FALSE: Arrow is outside of item widget.
*
*/
boolean WdgScrlIndGetArrowInside
(
    IWidget                 *pWDGScrlInd
);

/** WdgScrlIndGetInvisibleIfDisable
* @brief        Get arrow invisible status when it is disable
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be gotten
*
* @retval       TRUE  : Arrow is invisible if it is disable.
* @retval       FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
*/
boolean WdgScrlIndGetInvisibleIfDisable
(
    IWidget                 *pWDGScrlInd
);

/** WdgScrlIndGetArrowWidth
* @brief        Get arrow width of widget
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be gotten
* @param[out]   pWidth            The arrow width
* @param[in]    eDirection        The arrow type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgScrlIndGetArrowWidth
(
    IWidget              *pWDGScrlInd,
    u16                  *pWidth,
    Direction_e          eDirection
)
{
    return WdgCommonGetArrowWidth(pWDGScrlInd, pWidth, eDirection);
}

/** WdgScrlIndGetArrowHeight
* @brief         Get arrow height of widget
*
* @param[in]     pWDGScrlInd       The scroll indicator widget which want to be gotten
* @param[out]    pHeight           The arrow height
* @param[in]     eDirection        The arrow type
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgScrlIndGetArrowHeight
(
    IWidget              *pWDGScrlInd,
    u16                  *pHeight,
    Direction_e          eDirection
)
{
    return WdgCommonGetArrowHeight(pWDGScrlInd, pHeight, eDirection);
}

/** WdgScrlIndGetLayoutStyle
* @brief        Get Scroll Indicator widget's layout style
*
* @param[in]    pWDGScrlInd       The scroll indicator widget which want to be gotten
* @param[out]   pWdgLayoutStyle   The widget layout style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgScrlIndGetLayoutStyle
(
    IWidget                 *pWDGScrlInd,
    WdgLayoutStyle_e        *pWdgLayoutStyle
)
{
    return WdgCommonGetProperty(pWDGScrlInd, PROP_LAYOUT_STYLE, (u32 *)pWdgLayoutStyle);
}

/** WdgScrlIndGetObjDecoratorWidget
* @brief        Get the widget which is decorated by scroll indicator widget
*
* @param[in]    pWDGScrlInd  The scroll indicator widget which want to be set
*
* @retval       The widget which is decorated by scroll indicator widget..
*
*/
IWidget* WdgScrlIndGetObjDecoratorWidget
(
    IWidget                *pWDGScrlInd
);

typedef void (*PfnWdgScrollIndScrollFinish) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pWidget);

__SLDPM_FREE__ MAE_Ret WdgScrollIndRegisterScrollFinishCb
(
    IWidget                        *pWDGList,
    PfnWdgScrollIndScrollFinish    pfn,
    void                           *pUserData
);
#endif //__MMI_WDG_SCROLL_INDICATOR_H__
/*=============================================================*/
// end of file
