/**
* @file    mmi_wdg_switchicon.h
* @version $Id: mmi_wdg_switchicon.h 32377 2009-06-02 10:50:34Z elvis.chen $
*
* @brief   This file defines CLSID_SWITCHICONWIDGET class which is a kind of Widget object.
*
*         Switch Icon Widget is used for on/off, marked/unmarked... application.
*         It uses two icons (images) to display the Active/Inactive status.
*
*           Ex,
*           -------                        --------
*           |     | Set check state        |    / |
*           |     |        -->             |\  /  |
*           |     |                        | \/   |
*           -------                        --------
*
*          Switch-Icon widget supports six types of pre-defined. They are:
*          (1) Check (SWITCH_ICON_STYLE_CHECK)
*          (2) Mark (SWITCH_ICON_STYLE_MARK)
*          (3) Activate (SWITCH_ICON_STYLE_ACTIVATE)
*          (4) Radio (SWITCH_ICON_STYLE_RADIO)
*          (5) Camera Mark (SWITCH_ICON_STYLE_CAMERA_MARK)
*          (6) Grid Mark (SWITCH_ICON_STYLE_GRIDMARK)
*          (7) HIDE (SWITCH_ICON_STYLE_HIDE_ICON).
*          (8) Total (SWITCH_ICON_STYLE_TOTAL)
*          (9) MASK (SWITCH_ICON_STYLE_MASK)
*
*          and the default is Check.
*/

#ifndef __MMI_WDG_SWITCHICON_H__
#define __MMI_WDG_SWITCHICON_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_windowmgr.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgSwitchIconSwitchingNotify
* @brief      CB register by "WdgSwitchIconRegisterSwitchingNotifyCb"
*             and will be trigger when the widget is switching by release touch.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  bCheck            Widget,be checked or not
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgSwitchIconSwitchingNotify) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bCheck, IWidget *pWidget);

/** PfnWdgSwitchIconWidgetDataChange
* @brief      CB register by "WdgSwitchIconRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed; Ex,WdgSwitchIconSetDataByID, WdgSwitchIconSetData
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam          The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgSwitchIconWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);


typedef struct
{
    Icon_Style_e            nIconStyle;         //the style of Icon
    IImage                  *pActiveIcon;    //the active icon IMG
    IImage                  *pInactiveIcon;  //the inactive icon IMG
}WdgSwitchIconAttr_t;

typedef struct
{
    Icon_Style_et            nIconStyle;         //the style of Icon
    u32                     nActiveIconID;      //the active icon IMG ID
    u32                     nInactiveIconID;    //the inactive icon IMG ID
}WdgSwitchIconAttrId_t;

typedef struct
{
    IImage                  *pActiveIcon;    //the active icon IMG
    IImage                  *pInactiveIcon;  //the inactive icon IMG
}WdgSwitchIconData_t;

typedef struct
{
    u32                     nActiveIconID;      //the active icon IMG ID
    u32                     nInactiveIconID;    //the inactive icon IMG ID
}WdgSwitchIconDataId_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgSwitchIconCreateForWnd
* @brief        SwitchIcon widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    pAttr               The pointer of WdgSwitchIconAttr_t
*
* @retval       The pointer of SwitchIcon pointer       Success.
* @retval       NULL                                    Failed.
*
*/
IWidget* WdgSwitchIconCreateForWnd
(
    HWIN                     hWin,
    Pos_t                           *pPos,
    WidgetSize_t                    *pSize,
    u16                             nWidgetID,
    WdgSwitchIconAttr_t             *pAttr
);
/*=============================================================*/
/** WdgSwitchIconCreate
* @brief        Create SwitchIcon widget
*
* @retval       The pointer of SwitchIcon       Success.
* @retval       NULL                            Failed.
*
*/
IWidget* WdgSwitchIconCreate
(
    void
);

/** WdgSwitchIconSetData
* @brief        Set Specific data to widget for display
*
*
* @param[in]    pWDGSwitchIcon      The SwitchIcon widget which want to be set
* @param[in]    pAttr               The pointer of WdgSwitchIconData_t
*                                   Specific data for SwitchIcon widget.
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_BAD_PARAM   Failed. pAttr is NULL
* @retval       MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgSwitchIconSetData
(
    IWidget                 *pWDGSwitchIcon,
    WdgSwitchIconData_t     *pAttr
);

/** WdgSwitchIconSetDataByID
* @brief        Set Specific data by ID to widget for display
*
* @param[in]    pWDGSwitchIcon      The SwitchIcon widget which want to be set
* @param[in]    pAttr               The pointer of WdgSwitchIconDataId_t
*                                   Specific data for SwitchIcon widget.
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_BAD_PARAM   Failed. pAttr is NULL
* @retval       MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgSwitchIconSetDataByID
(
    IWidget                 *pWDGSwitchIcon,
    WdgSwitchIconDataId_t   *pAttr
);
/*=============================================================*/
/** WdgSwitchIconSetIconStyle
* @brief        Set the style of Icon
*
* @param[in]    pWDGSwitchIcon    Pointer to the SwitchIcon widget
* @param[in]    nIconStyle        the style of Icon:refer to mmi_mmi_mae_widget_properties.h
*
* @retval        None
*
*/
__INLINE void WdgSwitchIconSetIconStyle
(
    IWidget                 *pWDGSwitchIcon,
    Icon_Style_e            nIconStyle
)
{
    WdgCommonSetProperty(pWDGSwitchIcon, PROP_SWITCH_WDG_ICON_STYLE, (u32)nIconStyle);
}

/** WdgSwitchIconSetIconStyle
* @brief        Set the check status
*
* @param[in]    pWDGSwitchIcon    Pointer to the SwitchIcon widget
* @param[in]    bCheck            TRUE : Active Status.
*                                 FALSE : InActive Status.
*
* @retval       MAE_RET_SUCCESS   Success.
* @retval       MAE_RET_FAILED    DataMdl is NULL.
*
*/
MAE_Ret WdgSwitchIconSetCheck
(
    IWidget *pWDGSwitchIcon,
    boolean bCheck
);

/** WdgSwitchIconGetCheck
* @brief        Get the check status
*
* @param[in]    pWDGSwitchIcon    Pointer to the SwitchIcon widget
* @param[in]    pbCheck            TRUE : Active Status.
*                                  FALSE : InActive Status.
*
* @retval       MAE_RET_SUCCESS   Success.
* @retval       MAE_RET_FAILED    DataMdl is NULL.
*
*/
MAE_Ret WdgSwitchIconGetCheck
(
    IWidget *pWDGSwitchIcon,
    boolean *pbCheck
);

/** WdgSwitchIconSetActiveIcon
* @brief        Set the active icon
*
* @param[in]    pWDGSwitchIcon    Pointer to the SwitchIcon widget
* @param[in]    pActiveIcon       The active icon
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconSetActiveIcon
(
    IWidget                 *pWDGSwitchIcon,
    IImage                  *pActiveIcon
)
{
    return WdgCommonSetProperty(pWDGSwitchIcon, PROP_SWITCH_WDG_ACTIVE_ICON_IMG, (u32)pActiveIcon);
}

/** WdgSwitchIconSetInActiveIcon
* @brief        Set the inactive icon
*
* @param[in]    pWDGSwitchIcon    Pointer to the SwitchIcon widget
* @param[in]    pInactiveIcon     The inactive icon
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSwitchIconSetInActiveIcon
(
    IWidget                 *pWDGSwitchIcon,
    IImage                  *pInactiveIcon
)
{
    return WdgCommonSetProperty(pWDGSwitchIcon, PROP_SWITCH_WDG_INACTIVE_ICON_IMG, (u32)pInactiveIcon);
}

/** WdgSwitchIconRegisterSwitchingNotifyCb
* @brief        Register callback : For switch icon widget.
*               when the widget is switching by release touch;CB will be triggered to notify switching.
*
* @param[in]    pWDGSwitchIcon    The SwitchIcon widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSwitchIconRegisterSwitchingNotifyCb
(
    IWidget                         *pWDGSwitchIcon,
    PfnWdgSwitchIconSwitchingNotify pfn,
    void                            *pUserData
);

/** WdgSwitchIconRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while widget data be changed.
*
* @param[in]    pWDGSwitchIcon    The SwitchIcon widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSwitchIconRegisterDataChangeCb
(
    IWidget                             *pWDGSwitchIcon,
    PfnWdgSwitchIconWidgetDataChange pfn,
    void                                *pUserData
);

/** WdgSwitchIconDeregisterSwitchingNotifyCb
* @brief        Deregister callback : For switch icon widget, CB will be triggered to notify switching.
*
* @param[in]    pWDGSwitchIcon    The SwitchIconItem widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSwitchIconDeregisterSwitchingNotifyCb
(
    IWidget                         *pWDGSwitchIcon,
    PfnWdgSwitchIconSwitchingNotify pfn,
    void                            *pUserData
);

/** WdgSwitchIconDeregisterDataChangeCb
* @brief        Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGSwitchIcon       The SwitchIcon widget which want to set callback
* @param[in]    pfn                  callback function
* @param[in]    pUserData             User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgSwitchIconDeregisterDataChangeCb
(
    IWidget                             *pWDGSwitchIcon,
    PfnWdgSwitchIconWidgetDataChange pfn,
    void                                *pUserData
);


#endif //__MMI_WDG_SWITCHICON_H__
/*=============================================================*/
// end of file
