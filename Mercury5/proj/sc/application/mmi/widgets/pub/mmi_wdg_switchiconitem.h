/**
* @file    mmi_wdg_switchiconitem.h
* @version $Id: mmi_wdg_switchiconitem.h 32377 2009-06-02 10:50:34Z elvis.chen $
* @brief   
* <Description>
*     Switch-Icon-Item widget is a decorator widget.  It could decorate a widget
*     (as an Item widget), and draw a Switch-Icon in the left (or right) of Item
*     widget. Switch-Icon of the location (left/right) is decided by the Icon Style.
*
*     In Check/Radio/Activate style:
*          +----------------------+
*          |+----++--------------+|      SI wdg: SwitchIcon widget
*          || SI ||    item      ||
*          ||wdg ||    widget    ||
*          |+----++--------------+|
*          +----------------------+
*
*     In Mark/Camera Mark style:
*          +----------------------+
*          |+--------------++----+|      SI wdg: SwitchIcon widget
*          ||       item   ||  SI||
*          ||     widget   || wdg||
*          |+--------------++----+|
*          +----------------------+
*/
#ifndef __MMI_WDG_SWITCHICONITEM_H__
#define __MMI_WDG_SWITCHICONITEM_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_wdg_switchicon.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** SwitchIconItemData_t
*
* @brief    bCheck:             Displaying activated icon when TRUE, else displaying deactivated icon
*           ItemDataIsModel:    indicate if pItemData is a model
*           pItemData:          the data for item widget
*           bVisible:           indicate if icon is visible or not
*
*/
typedef struct {
	boolean bCheck;				///< Displaying activated icon when TRUE, else displaying deactivated icon
	boolean ItemDataIsModel;	///< indicate if pItemData is a model
	void *pItemData;			///< the data for item widget
	boolean bVisible;			///< indicate if icon is visible or not
} SwitchIconItemData_t;

/** WdgSwitchIconItemIcon_t
*
* @brief    nAlignment:         the alignment of Icon
*           nIconWidth:         the width of Icon
*           nIconHeight:        the height of Icon
*           nIconPosition:      the icon position
*
*/
typedef struct
{
    u32                     nAlignment;         //the alignment of Icon
    u16                     nIconWidth;         //the width of Icon
    u16                     nIconHeight;        //the height of Icon
    Icon_Pos_et             nIconPosition;      //the icon position
}WdgSwitchIconItemIcon_t;

/** WdgSwitchIconItemData_t
*
* @brief    bCheck:                 Displaying activated icon when TRUE, else displaying deactivated icon
*           ItemDataIsModel:        indicate if pItemData is a model
*           nTextID:                the text ID data
*           nImageID:               the text ID data
*           nImageID:               indicate if icon is visible or not
*
*/
typedef struct
{
    boolean                 bCheck;             //< Displaying activated icon when TRUE, else displaying deactivated icon
    boolean                 ItemDataIsModel;    //< indicate if pItemData is a model
    u32                     nTextID;            //< the text ID data
    u32                     nImageID;           //< the image ID data
    boolean                 bVisible;           //< indicate if icon is visible or not
}WdgSwitchIconItemData_t;


/*=============================================================*/
// functions
/*=============================================================*/

/** PfnWdgSwitchIconItemSwitchingNotify
* @brief      CB register by "WdgSwitchIconItemRegisterSwitchingNotifyCb"
*             and will be trigger when the widget is switching by release touch.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  bCheck            Widget,be checked or not
* @param[in]  pReserve          The widget instance reserved for future (Please do NOT use now)
*
*/
typedef void (*PfnWdgSwitchIconItemSwitchingNotify) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bCheck, IWidget *pReserve);

/** PfnWdgSwitchIconItemWidgetDataChange
* @brief      CB register by "WdgSwitchIconItemRegisterDataChangeCb"
*             and will be trigger when the widget is switching by release touch.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam          The data word param (NOT use now)
* @param[in]  pReserve          The widget instance reserved for future (Please do NOT use now)
*
*/
typedef void (*PfnWdgSwitchIconItemWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pReserve);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgSwitchIconItemCreateForWnd
* @brief        SwitchIcon item widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    nStyle              The style of Icon;refer to Icon_Style_et.
*
* @retval       The pointer of SwitchIcon item pointer  Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgSwitchIconItemCreateForWnd
(
    HWIN                     hWin,
    Pos_t                           *pPos,
    WidgetSize_t                    *pSize,
    u16                             nWidgetID,
    Icon_Style_et                   nStyle
);
/*=============================================================*/
/** WdgSwitchIconItemCommonSetIcon
* @brief
*
* @param[in]    pWDGSwitchIconItem    The SwitchIconItem widget which want to be set
* @param[in]    pIcon                 The pointer of WdgSwitchIconItemIcon_t
*
* @retval       MAE_RET_SUCCESS       Success.
* @retval       MAE_RET_BAD_PARAM     Failed. pIcon is NULL
* @retval       MAE_RET_FAILED        Failed.

*
*/
MAE_Ret WdgSwitchIconItemCommonSetIcon
(
    IWidget                     *pWDGSwitchIconItem,
    WdgSwitchIconItemIcon_t     *pIcon
);
/*=============================================================*/
/** WdgSwitchIconItemCreate
* @brief        Create SwitchIconItem widget
*
* @retval       The pointer of SwitchIconItem   Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgSwitchIconItemCreate
(
    void
);
/*=============================================================*/
/** WdgSwitchIconItemSetIconWidth
* @brief        Set the width of Icon
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nIconWidth              the width of Icon
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconItemSetIconWidth
(
    IWidget                 *pWDGSwitchIconItem,
    u16                     nIconWidth
)
{
    return WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SII_WDG_ICON_WIDTH, (u32)nIconWidth);
}

/** WdgSwitchIconItemSetIconHeight
* @brief        Set the height of Icon
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nIconHeight             the height of Icon
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconItemSetIconHeight
(
    IWidget                 *pWDGSwitchIconItem,
    u16                     nIconHeight
)
{
    return WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SII_WDG_ICON_HEIGHT, (u32)nIconHeight);
}

/** WdgSwitchIconItemSetIconAlignment
* @brief        Set the alignment of Icon
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nAlignment              the alignment of Icon; refer to WdgAlignment_e
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconItemSetIconAlignment
(
    IWidget                 *pWDGSwitchIconItem,
    WdgAlignment_e          nAlignment
)
{
    return WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SII_WDG_ICON_ALIGNMENT, (u32)nAlignment);
}

/** WdgSwitchIconItemSetIconStyle
* @brief        Set the style of Icon
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nStyle                  the style of Icon;refer to Icon_Style_et.
*                                       PS, Only Support Four Styles as Below
*                                       (1), SWITCH_ICON_STYLE_CHECK:
*                                       (2), SWITCH_ICON_STYLE_MARK.
*                                       (3), SWITCH_ICON_STYLE_ACTIVATE:
*                                       (4), SWITCH_ICON_STYLE_RADIO:
*                                       (5), SWITCH_ICON_STYLE_CAMERA_MARK:
*                                       (6), SWITCH_ICON_STYLE_HIDE_ICON:
*                                       (7), SWITCH_ICON_STYLE_GRIDMARK:
*                                       (8), SWITCH_ICON_STYLE_TOTAL:
*                                       (9), SWITCH_ICON_STYLE_MASK:
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconItemSetIconStyle
(
    IWidget                 *pWDGSwitchIconItem,
    Icon_Style_et           nStyle
)
{
    return WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SWITCH_WDG_ICON_STYLE, (u32)nStyle);
}

/** WdgSwitchIconItemSetIconPosition
* @brief        set the icon position
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nIconPosition           the icon position, refer to Icon_Pos_et.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconItemSetIconPosition
(
    IWidget                 *pWDGSwitchIconItem,
    Icon_Pos_et             nIconPosition
)
{
    return WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SII_WDG_ICON_POS, (u32)nIconPosition);
}

/** WdgSwitchIconItemSetFcsItemBGColor
* @brief        set the focused item background color
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    nFcsItemBGColor         focused item background color
*
* @retval       None
*
*/
__INLINE void WdgSwitchIconItemSetFcsItemBGColor
(
    IWidget                 *pWDGSwitchIconItem,
    RGBColor_t              nFcsItemBGColor
)
{
    WdgCommonSetProperty(pWDGSwitchIconItem, PROP_FCS_ITEM_BG_COLOR, (u32)nFcsItemBGColor);
}

/** WdgSwitchIconItemSetFcsItemBGImage
* @brief        set the focused item background image
*
* @param[in]    pWDGSwitchIconItem      Pointer to the SwitchIconItem widget
* @param[in]    pBGImage                background image
*
* @retval       None
*
*/
__INLINE void WdgSwitchIconItemSetFcsItemBGImage
(
    IWidget                 *pWDGSwitchIconItem,
    IImage                  *pBGImage
)
{
    WdgCommonSetProperty(pWDGSwitchIconItem, PROP_FCS_ITEM_BG_IMAGE, (u32)pBGImage);
}

/** WdgSwitchIconItemSetDecoratorWidget
* @brief        Set the widget you want to combine with  SwitchIconItem widget.
*               To decorate Item with a check icon.
*               Ex, To decorate text widget, with a check icon.
*
* @param[in]    pWDGSwitchIconItem          The SwitchIconItem widget which want to be set
* @param[in]    pChild                  The widget which is decorated by SwitchIconItem widget.
*
* @retval       None.
*
*/
void WdgSwitchIconItemSetDecoratorWidget
(
    IWidget                 *pWDGSwitchIconItem,
    IWidget                 *pChild
);

/** WdgSwitchIconItemSetCheck
* @brief        Set the check status
*
* @param[in]    pWDGSwitchIconItem      The SwitchIconItem widget which want to be set
* @param[in]    bCheck                  TRUE : Active Status.
*                                       FALSE : InActive Status.
*
* @retval       MAE_RET_SUCCESS         Success
* @retval       others                  Failed
*
*/
MAE_Ret WdgSwitchIconItemSetCheck
(
    IWidget                 *pWDGSwitchIconItem,
    boolean                 bCheck
);

/** WdgSwitchIconItemGetCheck
* @brief        Get the check status
*
* @param[in]    pWDGSwitchIconItem          The SwitchIconItem widget which want to be set
* @param[in]    pbCheck                 TRUE : Active Status.
*                                       FALSE : InActive Status.
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_FAILED          DataMdl is NULL.
*
*/
MAE_Ret WdgSwitchIconItemGetCheck
(
    IWidget *pWDGSwitchIconItem,
    boolean *pbCheck
);

/** WdgSwitchIconItemSetVisible
* @brief        Set the check icon visibility
*
* @param[in]    pWDGSwitchIconItem      The SwitchIconItem widget which want to be set
* @param[in]    bVisible                  TRUE : Icon Item is visible.
*                                       FALSE : Icon Item is invisible.
*
* @retval       None
*
*/
__INLINE void WdgSwitchIconItemSetVisible
(
    IWidget                 *pWDGSwitchIconItem,
    boolean                 bVisible
)
{
    WdgCommonSetProperty(pWDGSwitchIconItem, PROP_SII_WDG_ICON_VISIBLE, (boolean)bVisible);
}

/*=============================================================*/
/** WdgSwitchIconItemGetObjDecoratorWidget
* @brief        Get the widget you combine with SwitchIconItem widget.
*
* @param[in]    pWDGSwitchIconItem          The SwitchIconItem widget which want to be set
*
* @retval       The widget which is decorated by SwitchIconItem widget..
*
*/
IWidget* WdgSwitchIconItemGetObjDecoratorWidget
(
    IWidget                 *pWDGSwitchIconItem
);

/** WdgSwitchIconItemRegisterSwitchingNotifyCb
* @brief        Register callback : For switch icon widget,
*               CB and will be trigger when the widget is switching by release touch
*
* @param[in]    pWDGSwitchIconItem    The SwitchIconItem widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSwitchIconItemRegisterSwitchingNotifyCb
(
    IWidget                             *pWDGSwitchIconItem,
    PfnWdgSwitchIconItemSwitchingNotify pfn,
    void                                *pUserData
);

/** WdgSwitchIconItemRegisterDataChangeCb
* @brief        Register data change callback;
*               CB will be triggered while when the data of widget is changed;
*
* @param[in]    pWDGSwitchIconItem    The SwitchIconItem widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSwitchIconItemRegisterDataChangeCb
(
    IWidget                                 *pWDGSwitchIconItem,
    PfnWdgSwitchIconItemWidgetDataChange pfn,
    void                                    *pUserData
);

/** WdgSwitchIconItemDeregisterSwitchingNotifyCb
* @brief        Deregister callback : For switch icon widget, CB will be triggered to notify switching.
*
* @param[in]    pWDGSwitchIconItem    The text widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSwitchIconItemDeregisterSwitchingNotifyCb
(
    IWidget                             *pWDGSwitchIconItem,
    PfnWdgSwitchIconItemSwitchingNotify pfn,
    void                                *pUserData
);

/** WdgSwitchIconItemDeregisterDataChangeCb
* @brief        Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGSwitchIconItem    The SwitchIconItem widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSwitchIconItemDeregisterDataChangeCb
(
    IWidget                                 *pWDGSwitchIconItem,
    PfnWdgSwitchIconItemWidgetDataChange pfn,
    void                                    *pUserData
);


#endif //__MMI_WDG_SWITCHICONITEM_H__
/*=============================================================*/
// end of file
