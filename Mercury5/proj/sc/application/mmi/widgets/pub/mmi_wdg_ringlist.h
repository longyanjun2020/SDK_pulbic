/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*    The functions and operations of Ring-List widget are the almost same as List widget,
*    the only difference is the way of display items. Ring-List widget always places the
*    highlight item on the center. There are horizontal and vertical two types of Ring-List
*    widget sketched below. In Horizontal Ring-List widget, each item can be set the width;
*    In the Vertical Ring-List widget, each item can be set the height. In addition, Ring-List
*    widget can let the width/height of highlight item to differ from other unfocused items.
*    Ring-List widget also can be set the Padding, Border and Background color/image.
*
*
*       ex: Horizontal Ring-List widget
*       +------------------------+
*       |  Item  |  Item |  Item |
*       |   1    |    2  |    3  |
*       +------------------------+
*                     ^ Item 2 is the focused item.
*
*
*         ex: Vertical Ring-List widget
*             +------------+
*              |    Item 1 |
*              |-----------|
*              |    Item 2 |  <- Item 2 is the focused item.
*              |-----------|
*              |    Item 3 |
*              +-----------+
*
*/

#ifndef __MMI_WDG_RINGLIST_H__
#define __MMI_WDG_RINGLIST_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"


/*=============================================================*/
// type and define
/*=============================================================*/
enum {
	RINGLIST_TOUCH_MOVE_STYLE_NONE = 0,
	RINGLIST_TOUCH_MOVE_STYLE_MOVE_LOCATION,
	RINGLIST_TOUCH_MOVE_STYLE_END
};
typedef u8 RingListTSMoveStyle_t;
//FOR Property PROP_RINGLIST_WDG_TOUCH_MOVE_STYLE

/** WdgRingListCfgData_t
*
* @brief    bNoWrap:        Set True or False for wrap or not.
*           LayoutStyle:    Set VERTICAL, HORIZONTAL or BOTH.
*           nItemWidth:     Set list item width in pixel.
*           nItemHeight:    Set list item height in pixel.
*           nItemRowGap:    Set gap between items.
*
*/
typedef struct
{
    boolean                 bNoWrap;
    WdgLayoutStyle_t        LayoutStyle;
    u16                     nItemWidth;
    u16                     nItemHeight;
    u16                     nItemRowGap;
}WdgRingListCfgData_t;

/** PfnWdgRingListFocusChang
* @brief      CB register by "PfnWdgRingListFocusChang"
*             and will be trigger when the focus of widget is changed
*
* @param[in]  pApplet        The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData       User data ap developer setting when register CB.
* @param[in]  nEvtCode       Widget Event Code, only useful for softkey event
* @param[in]  pFocusData     The info can get when focus changed, refer to FocusChangeData_t
* @param[in]  pIWidget       The widget instance
*
*/
typedef void (*PfnWdgRingListFocusChang) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData,IWidget *pWidget);

/** PfnWdgRingListRollingStart
* @brief      CB register by "PfnWdgRingListRollingStart"
*             and will be trigger when notify rolling started.
*
* @param[in]  pApplet         The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData        User data ap developer setting when register CB.
* @param[in]  nEvtCode        Widget Event Code, only useful for softkey event
* @param[in]  nReserve        Reserve for enhancement in the future
* @param[in]  pIWidget        The widget instance
*
*/
typedef void (*PfnWdgRingListRollingStart) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgRingListRollingFinish
* @brief      CB register by "PfnWdgRingListRollingFinish"
*             and will be trigger when notify rolling finished.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nHighLightIdx     The index of highlighted element, zero base.
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgRingListRollingFinish) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nHighLightIdx, IWidget *pWidget);

/** PfnWdgRingListItemChange
* @brief      CB register by "PfnWdgRingListItemChange"
*             and will be trigger when items has changed.
*
* @param[in]  pApplet       The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData      User data ap developer setting when register CB.
* @param[in]  nEvtCode      Widget Event Code, only useful for softkey event
* @param[in]  nReserve      Reserve for enhancement in the future
* @param[in]  pIWidget      The widget instance
*
*/
typedef void (*PfnWdgRingListItemChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgRingListCreateForWnd
* @brief        Ring-list widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pData           Widget Common Data, refer to WdgRingListCfgData_t.
*                               If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Ringlist pointer   Success.
* @retval       NULL                              Failed.
*
*/
IWidget* WdgRingListCreateForWnd
(
    HWIN                hWin,
    Pos_t                      *pPos,
    WidgetSize_t               *pSize,
    u16                        nWidgetID,
    WdgRingListCfgData_t       *pData
);

/*=============================================================*/
/** WdgRingListCreate
* @brief        Create Ring-list widget
*
* @retval       The pointer of Ring-list   Success.
* @retval       NULL                       Failed.
*
*/
IWidget* WdgRingListCreate
(
    void
);

/** WdgRingListSetLayoutStyle
* @brief         Get the widget's layout style
*
* @param[in]     pWDGRinglist        The pointer of IWidget interface object
* @param[in]     nWdgLayoutStyle     A value of WdgLayoutStyle_t with result of the widget's layout style
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetLayoutStyle
(
    IWidget             *pWDGRinglist,
    WdgLayoutStyle_t    nWdgLayoutStyle
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_LAYOUT_STYLE, (u32)nWdgLayoutStyle);
}

/** WdgRingListSetFocusedIndex
* @brief         Set the index of focused element
*
* @param[in]     pWDGRinglist   The pointer of IWidget interface object
* @param[in]     nFocusIdx      The index of focused element, zero base(means the index start from 0).
*
* @retval       void
*
*/
__INLINE void WdgRingListSetFocusedIndex
(
    IWidget              *pWDGRinglist,
    s32                  nFocusIdx
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_FOCUS_INDEX, (u32)nFocusIdx);
}

/** WdgRingListSetItemWidth
* @brief         Set the width of item in pixels
*
* @param[in]     pWDGRinglist    The pointer of IWidget interface object
* @param[in]     nItemWidth      The width of item in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetItemWidth
(
    IWidget              *pWDGRinglist,
    u16                  nItemWidth
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_ITEM_WIDTH, (u32)nItemWidth);
}

/** WdgRingListSetItemHeight
* @brief         Set the height of item in pixels
*
* @param[in]     pWDGRinglist   The pointer of IWidget interface object
* @param[in]     nItemHeight    The height of item in pixels
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetItemHeight
(
    IWidget              *pWDGRinglist,
    u16                  nItemHeight
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_ITEM_HEIGHT, (u32)nItemHeight);
}

/** WdgRingListSetSelitemSize
* @brief         Set the selected item size
*
* @param[in]     pWDGRinglist  The pointer of IWidget interface object
* @param[in]     pItemSize     Item size in pixels to be set.
*
* @retval        void
*
*/
__INLINE void WdgRingListSetSelitemSize
(
    IWidget              *pWDGRinglist,
    u16                  pItemSize
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_SEL_ITEMSIZE, (u32)pItemSize);
}

/** WdgRingListSetRowGap
* @brief         Set row gap in pixel between every item.
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
* @param[in]     nItemRowGap       The space in pixels between row items
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetRowGap
(
    IWidget              *pWDGRinglist,
    u16                  nItemRowGap
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_WDG_ROW_GAP, (u32)nItemRowGap);
}

/** WdgRingListSetColGap
* @brief         Set column gap in pixel between every item.
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
* @param[in]     nItemColGap       The space in pixels between column items
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetColGap
(
    IWidget              *pWDGRinglist,
    u16                  nItemColGap
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_WDG_COL_GAP, (u32)nItemColGap);
}

/** WdgRingListSetFocusedItemBgColor
* @brief         Set the background color for focused item widget
*
* @param[in]     pWDGRinglist    The pointer of IWidget interface object
* @param[in]     nRBgColor       RGBColor_t value. the return value of MAKE_RGB()
*
* @retval       void
*
*/
__INLINE void WdgRingListSetFocusedItemBgColor
(
    IWidget             *pWDGRinglist,
    RGBColor_t          nRBgColor
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_FCS_ITEM_BG_COLOR, (u32)nRBgColor);
}

/** WdgRingListSetFocusedItemBgImage
* @brief         Set the background image for focused item widget
*
* @param[in]     pWDGRinglist   The pointer of IWidget interface object
* @param[in]     pImage         An image object pointer.
*
* @retval        void
*
*/
__INLINE void WdgRingListSetFocusedItemBgImage
(
    IWidget                 *pWDGRinglist,
    IImage                  *pImage
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_FCS_ITEM_BG_IMAGE, (u32)pImage);
}

/** WdgRingListSetNoWrap
* @brief         Set No Wrap property
*
* @param[in]     pWDGRinglist    The pointer of IWidget interface object
* @param[in]     bNoWrap         The No Wrap property
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgRingListSetNoWrap
(
    IWidget                 *pWDGRinglist,
    boolean                 bNoWrap
)
{
    return WdgCommonSetProperty(pWDGRinglist, PROP_RINGLIST_WDG_NO_WRAP, (u32)bNoWrap);
}

/** WdgRingListSetEnableRolling
* @brief         Set enable rolling
*
* @param[in]     pWDGRinglist     The pointer of IWidget interface object
* @param[in]     bEnableRolling   Enable or disable Rolling
*
* @retval        void
*
*/
__INLINE void WdgRingListSetEnableRolling
(
    IWidget                 *pWDGRinglist,
    boolean                 bEnableRolling
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_RINGLIST_WDG_ENABLE_ROLLING, (u32)bEnableRolling);
}

/** WdgRingListSetTouchMoveStyle
* @brief         Set the touch move style
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to set
* @param[in]     nTSMoveStyle      The touch move style
*
* @retval        void
*
*/
__INLINE void WdgRingListSetTouchMoveStyle
(
    IWidget                 *pWDGRinglist,
    RingListTSMoveStyle_t   nTSMoveStyle
)
{
    WdgCommonSetProperty(pWDGRinglist, PROP_RINGLIST_WDG_TOUCH_MOVE_STYLE, (u32)nTSMoveStyle);
}

/** WdgRingListSetDecoratorWdg

* @brief         Set the widget which is decorated by Ringlist widget
*
* @param[in]     pWDGRinglist    The Ringlist widget which want to be set
* @param[in]     pChild          The widget which is decorated by Ringlist widget.
*
* @retval        None.
*
*/

void WdgRingListSetDecoratorWdg
(
    IWidget                 *pWDGRinglist,
    IWidget                 *pChild
);

/** WdgRingListGetLayoutStyle
* @brief         Get the widget's layout style
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        WdgLayoutStyle_t  result of the widget's layout style
*
*/
WdgLayoutStyle_t WdgRingListGetLayoutStyle
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetFocusedIndex
* @brief         Get the index of focused element
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        s32               result of the index of focused element, zero base(means the index start from 0).
*
*/
s32 WdgRingListGetFocusedIndex
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetItemWidth
* @brief         Get the width of item in pixels
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        u16               result of the width of item in pixels
*
*/
u16 WdgRingListGetItemWidth
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetItemHeight
* @brief         Get the height of item in pixels
*
* @param[in]  pWDGRinglist   The pointer of IWidget interface object
*
* @retval     u16            result of the height of item in pixels
*
*/
u16 WdgRingListGetItemHeight
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetSelItemSize
* @brief         Get the selected item size
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        u16               result of item size in pixels.
*
*/
u16 WdgRingListGetSelItemSize
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetRowGap
* @brief         Get row gap in pixel between every item.
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        u16               result of the space in pixels between row items
*
*
*/
u16 WdgRingListGetRowGap
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetColGap
* @brief         Get column gap in pixel between every item.
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        u16               result of the space in pixels between column items
*/
u16 WdgRingListGetColGap
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListGetFocusedItemBgColor
* @brief         Get the background color for focused item widget
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        RGBColor_t            result of the background color for focused item widget
*
*/
RGBColor_t WdgRingListGetFocusedItemBgColor
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListIsNoWrap
* @brief         Get No Wrap property
*
* @param[in]     pWDGRinglist      The pointer of IWidget interface object
*
* @retval        boolean           result of the No Wrap
*/
boolean WdgRingListIsNoWrap
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListgetDecoratoredWdg

* @brief         Get the widget which is decorated by Ringlist widget
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to be set
*
* @retval        None.
*/

IWidget *WdgRingListgetDecoratoredWdg
(
    IWidget                 *pWDGRinglist
);

/** WdgRingListRegFocusedChangeCb
* @brief         Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListRegFocusedChangeCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListFocusChang pfn,
    void                    *pUserData
);


/** WdgRingListRegRollingStartCb
* @brief         Register callback:  For RingList widget CB will be triggered to notify rolling started.
*
* @param[in]     pWDGRinglist    The Ringlist widget which want to set callback
* @param[in]     pfn             callback function
* @param[in]     pUserData        User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListRegRollingStartCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListRollingStart pfn,
    void                    *pUserData
);


/** WdgRingListRegRollingFinishCb
* @brief         Register callback: For RingList widget CB will be triggered to notify rolling finished.
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListRegRollingFinishCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListRollingFinish pfn,
    void                    *pUserData
);


/** WdgRingListRegItemChangeCb
* @brief         Register item change callback: CB will be triggered while items has changed.
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to set callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListRegItemChangeCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListItemChange pfn,
    void                    *pUserData
);

/** WdgRingListDeregFocusedChangeCb
* @brief         Deregister callback for changing focus item: CB will be triggered if focus item changed
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to unregister callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListDeregFocusedChangeCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListFocusChang pfn,
    void                    *pUserData
);

/** WdgRingListDeregRollingStartCb
* @brief         Deregister callback:  For RingList widget CB will be triggered to notify rolling started.
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to deregister callback
* @param[in]     pfn               callback function
* @param[in]    pUserData           User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListDeregRollingStartCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListRollingStart pfn,
    void                    *pUserData
);


/** WdgRingListDeregRollingFinishCb
* @brief         Deregister callback: For RingList widget CB will be triggered to notify rolling finished.
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to deregister callback
* @param[in]     pfn               callback function
* @param[in]    pUserData           User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListDeregRollingFinishCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListRollingFinish pfn,
    void                    *pUserData
);

/** WdgRingListDeregItemChangeCb
* @brief         Deregister item change callback; CB will be triggered while items has changed.
*
* @param[in]     pWDGRinglist      The Ringlist widget which want to deregister callback
* @param[in]     pfn               callback function
* @param[in]     pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgRingListDeregItemChangeCb
(
    IWidget                 *pWDGRinglist,
    PfnWdgRingListItemChange pfn,
    void                    *pUserData
);


#endif //__MMI_WDG_RINGLIST_H__
/*=============================================================*/
// end of file
