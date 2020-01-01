/**
* @file    mmi_wdg_pick.h
* @version $Id: mmi_wdg_pick.h 6201 2008-01-09 14:27:58Z paul.ouyang $
* @brief   Pick Widget
*<Description>
*
*    Pick widget is a kind of decorator widget. It draws two arrows and a item widget horizontally.
*    The layout sketch is as follow.  It uses two arrows to inform whether there is any other
*     item can be choose. It is a horizontal layout, like a Scroll-indicator horizontal, but it can
*    only show one item (that is, highlight item). AP can set an item widget to pick, such as: Text
*    widget, Image widget ... and so on. If the AP does not set the item widget, Pick widget in the
*    created, it already creates a Text widget to be the item widget.
*
*        ex:
*        +-------------------------------------------+
*        |    /|  |                            | |\  |
*        |    \|  |       Item Widget          | |/  |
*        |-----|-------------------------------|-----|
*              ^ arrow image
*
*
*/

#ifndef __MMI_WDG_PICK_H__
#define __MMI_WDG_PICK_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/

/** PfnWdgPickFocusChange
* @brief      CB register by "WdgPickRegisterFocusChangeCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pFocusChangeData  The info of focus change, refer to FocusChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgPickFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData, IWidget *pWidget);


/** PfnWdgPickFocusSelect
* @brief      CB register by "WdgPickRegisterFocusSelectCb"
*             and will be trigger when the Focus of widget is changed; Ex,click arrows or press "Action Key"
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nFocusIndex       The nth focus Index
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgPickFocusSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFocusIndex, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgPickCreateForWnd
* @brief        Create Pick Widget and set the Pick value for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    bDirectToogle       TRUE: When receive Action key it will toggle pick item directly,
*                                   FALSE: Do Not direct toggle pick item.
*
* @retval       The pointer of Pick         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgPickCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    boolean                 bDirectToogle
);

/*=============================================================*/
/** WdgPickCreate
* @brief        Create Pick widget
*
* @retval       The pointer of Pick         Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgPickCreate
(
    void
);

/** WdgPickSetData
* @brief        Set display data for Pick widget By String.
*               Specific data for Pick widget.
*
* @param[in]    pWDGPick         Pointer to the Pick widget
* @param[in]    ppStrArray       nItemNum point of string array.
* @param[in]    nItemNum         number of display data
* @param[in]    pfFree           Free CB function for free data allocate by User while widget destroy.
* @param[in]    pOwner           Shall be an IBase interface object to keep the return object.
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgPickSetData
(
    IWidget             *pWDGPick,
    MAE_WChar           **ppStrArray,
    u32                 nItemNum,
    PfnDataFree         pfFree,
    IBase               *pOwner
);

/** WdgPickSetDataByID
* @brief        Set display data for Pick widget By String ID.
*               Specific data for Pick widget.
*
* @param[in]    pWDGPick         Pointer to the Pick widget
* @param[in]    pStrIDArray      nItemNum string ID array.
* @param[in]    nItemNum         number of display data
*
* @retval       MAE_RET_SUCCESS  Success
* @retval       others           Failed
*
*/
MAE_Ret WdgPickSetDataByID
(
    IWidget             *pWDGPick,
    u32                 *pStrIDArray,
    u32                 nItemNum
);

/*=============================================================*/

/** WdgPickSetDirectToogle
* @brief        Set Pick Widget DirectToogle status
*
* @param[in]    pWDGPick            Pointer to the Pick Widget
* @param[in]    bDirectToogle       TRUE: When receive Action key it will toggle pick item directly,
*                                   FALSE: Do Not direct toggle pick item.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgPickSetDirectToogle
(
    IWidget             *pWDGPick,
    boolean             bDirectToogle

)
{
    return WdgCommonSetProperty(pWDGPick, PROP_PICKWDG_DIRECT_TOGGLE, (u32)bDirectToogle);
}

/** WdgPickSetTextColor
* @brief        Set text color of widget.
*
* @param[in]    pWDGPick            Pointer to the Pick Widget
* @param[in]    TextColor            RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       void
*
*/
__INLINE void WdgPickSetTextColor
(
    IWidget             *pWDGPick,
    RGBColor_t          TextColor
)
{
    WdgCommonSetProperty(pWDGPick, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (u32)(TextColor));
}

/** WdgPickSetFocusIndex
* @brief        Set Pick widget focus index
*
* @param[in]    pWDGPick          The pointer of IWidget interface object
* @param[in]    nIndex            The Focus index of Pick widget
*
* @retval       void
*
*/
__INLINE void WdgPickSetFocusIndex
(
    IWidget                 *pWDGPick,
    u32                     nIndex
)
{
    WdgCommonSetProperty(pWDGPick, PROP_FOCUS_INDEX, (u32)nIndex);
}

/** WdgPickSetArrowInside
* @brief        Set arrow inside or outside of the item widget.
*
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    bInside           TRUE: Arrow is inside of item widget.
*                                 FALSE: Arrow is outside of item widget.
*
* @retval       void
*
*/
__INLINE void WdgPickSetArrowInside
(
    IWidget                 *pWDGPick,
    boolean                 bInside
)
{
    WdgCommonSetProperty(pWDGPick, PROP_SCLIND_WDG_ARROW_POSITION, (u32)bInside);
}

/** WdgPickSetInvisibleIfDisable
* @brief        Set arrow to be invisible if it is disable
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    bInvisible        The invisible status
*                                 TRUE  : Arrow is invisible if it is disable.
*                                 FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
* @retval      void
*
*/
__INLINE void WdgPickSetInvisibleIfDisable
(
    IWidget                 *pWDGPick,
    boolean                 bInvisible
)
{
    WdgCommonSetProperty(pWDGPick, PROP_SCLIND_WDG_INVISIBLE_IF_DISABLE, (u32)bInvisible);
}

/** WdgPickSetArrowWidth
* @brief        Set widget's arrow width in pixel
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    nWidth            The arrow width in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       void
*
*/
__INLINE void WdgPickSetArrowWidth
(
    IWidget                 *pWDGPick,
    u16                     nWidth,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowWidth(pWDGPick, nWidth, eDirection);
}


/** WdgPickSetArrowHeight
* @brief        Set widget's arrow height in pixel
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    nHeight           The arrow height in pixel
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       void
*
*/
__INLINE void WdgPickSetArrowHeight
(
    IWidget                 *pWDGPick,
    u16                     nHeight,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowHeight(pWDGPick, nHeight, eDirection);
}


/** WdgPickSetArrowActiveImg
* @brief        Set arrow active image
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    pActiveImage      The arrow active image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       void
*
*/
__INLINE void WdgPickSetArrowActiveImg
(
    IWidget                 *pWDGPick,
    IBitmap                 *pActiveImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowActiveImg(pWDGPick, pActiveImage, eDirection);
}

/** WdgPickSetArrowInActiveImg
* @brief        Set arrow inactive image
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    pInActiveImage    The arrow inactive image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval       void
*
*/
__INLINE void WdgPickSetArrowInActiveImg
(
    IWidget                 *pWDGPick,
    IBitmap                 *pInActiveImage,
    Direction_e             eDirection
)
{
   WdgCommonSetArrowInActiveImg(pWDGPick, pInActiveImage, eDirection);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgPickSetLeftArrowPressedImg
* @brief        Set image when arrow be pressed
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    pPressedImage     The arrow pressed image
* @param[in]    eDirection        The arrow type we want to set, refer to Direction_e.
*
* @retval      void
*/
__INLINE void WdgPickSetArrowPressedImg
(
    IWidget                 *pWDGPick,
    IBitmap                 *pPressedImage,
    Direction_e             eDirection
)
{
    WdgCommonSetArrowPressedImg(pWDGPick, pPressedImage, eDirection);
}

#endif //__TOUCH_SCREEN_MMI__

/** WdgPickSetLayoutStyle
* @brief        Set widget's layout style
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[in]    eWdgLayoutStyle   The widget layout style
*
* @retval       void
*/
__INLINE void WdgPickSetLayoutStyle
(
    IWidget                 *pWDGPick,
    WdgLayoutStyle_e        eWdgLayoutStyle
)
{
   WdgCommonSetProperty(pWDGPick, PROP_LAYOUT_STYLE, (u32)eWdgLayoutStyle);
}

/*=============================================================*/

/**WdgPickGetDirectToggle
* @brief        Get Pick Widget DirectToggle status
*
* @param[in]    pWDGPick            Pointer to the Pick Widget
*
* @retval       boolean             TRUE: When receive Action key it will toggle pick item directly,
*                                   FALSE: Do Not direct toggle pick item.
*
*/
boolean WdgPickGetDirectToggle
(
    IWidget                 *pWDGPick
);

/** WdgPickGetFocusIndex
* @brief        Get Pick widget focused index
*
* @param[in]    pWDGPick   The pointer of IWidget interface object
*
* @retval       u32        The Focus index of Pick widget
*
*/
u32 WdgPickGetFocusIndex
(
    IWidget                 *pWDGPick
);

/** WdgPickGetArrowPosition
* @brief        Get position info of arrow, inside or outside of the item widget.
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
*
* @retval       boolean    TRUE: Arrow is inside of item widget.
*                          FALSE: Arrow is outside of item widget.
*
*/
boolean WdgPickGetArrowInside
(
    IWidget                 *pWDGPick
);

/** WdgPickGetInvisibleIfDisable
* @brief        Get arrow invisible status when it is disable
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
*
* @retval       boolean           TRUE  : Arrow is invisible if it is disable.
*                                 FALSE : Arrow is "Bitmap"(ARROW_IMG_TYPE_DISABLE) if it is disable.
*
*/
boolean WdgPickGetInvisibleIfDisable
(
    IWidget                 *pWDGPick
);

/** WdgPickGetArrowWidth
* @brief        Get arrow width of widget
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
* @param[out]   pWidth            The arrow width
* @param[in]    eDirection        The arrow type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgPickGetArrowWidth
(
    IWidget                 *pWDGPick,
    u16                     *pWidth,
    Direction_e             eDirection
)
{
    return WdgCommonGetArrowWidth(pWDGPick, pWidth, eDirection);
}

/** WdgPickGetArrowHeight
* @brief         Get arrow height of widget
*
* @param[in]     pWDGPick          Pointer to the Pick Widget
* @param[out]    pHeight           The arrow height
* @param[in]     eDirection        The arrow type
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgPickGetArrowHeight
(
    IWidget                 *pWDGPick,
    u16                     *pHeight,
    Direction_e             eDirection
)
{
    return WdgCommonGetArrowHeight(pWDGPick, pHeight, eDirection);
}

/** WdgPickGetLayoutStyle
* @brief        Get widget's layout style
*
* @param[in]    pWDGPick          Pointer to the Pick Widget
*
* @retval       WdgLayoutStyle_e  The widget layout style
*
*/
WdgLayoutStyle_e WdgPickGetLayoutStyle
(
    IWidget                 *pWDGPick
);

/*=============================================================*/
/** WdgPickRegisterFocusChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGPick          The Pick widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPickRegisterFocusChangeCb
(
    IWidget                 *pWDGPick,
    PfnWdgPickFocusChange   pfn,
    void                    *pUserData
);

/** WdgPickRegisterFocusSelectCb
* @brief        Register callback for selecting item; CB will be triggered if item selected
*
* @param[in]    pWDGPick          The Pick widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPickRegisterFocusSelectCb
(
    IWidget                 *pWDGPick,
    PfnWdgPickFocusSelect   pfn,
    void                    *pUserData
);

/** WdgPickDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item
*
* @param[in]    pWDGPick          The Pick widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPickDeregisterFocusChangeCb
(
    IWidget                 *pWDGPick,
    PfnWdgPickFocusChange   pfn,
    void                    *pUserData
);

/** WdgPickDeregisterFocusSelectCb
* @brief        Deregister callback for selecting item
*
* @param[in]    pWDGPick          The Pick widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgPickDeregisterFocusSelectCb
(
    IWidget                 *pWDGPick,
    PfnWdgPickFocusSelect   pfn,
    void                    *pUserData
);

/** WdgPickSetObjAsPickItem
* @brief        Set widget like Text widget, Image widget or ... be the item of Pick Widget
*
* @param[in]    pWDGPick          The Pick widget
* @param[in]    pWDGPickItem      The widget set to be the item of Pick Widget
*
* @retval       None.
*
*/
void WdgPickSetObjAsPickItem
(
    IWidget                 *pWDGPick,
    IWidget                 *pWDGPickItem
);

/** WdgPickGetObjDecoratorWidget
* @brief        Get the item of Pick Widget, might be Text widget, Image widget or ...
*
* @param[in]    pWDGPick          The Pick widget
*
* @retval       The item of Pick Widget, might be Text widget, Image widget..
*
*/
IWidget* WdgPickGetObjDecoratorWidget
(
    IWidget                 *pWDGPick
);

#endif /* __MMI_WDG_PICK_H__ */
/*=============================================================*/
// end of file
