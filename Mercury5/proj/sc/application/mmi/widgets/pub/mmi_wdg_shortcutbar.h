/**
* @file    mmi_wdg_shortcutbar.h
* @version $Id: mmi_wdg_shortcutbar.h 41085 2009-09-22 15:14:03Z ryan.chou $
* @brief
* <Description>
*
*    If AP wants to show some useful widgets in one area, and let users decide
*    whether they appear or hide in the window, Shortcut Bar widget can achieve 
*    this need. AP can place widgets, especially like Time widget which users 
*    sometimes need in the Shortcut Bar widget. When users want to get the time, 
*    they can click the Shortcut Bar widget to show up Time widget. In other 
*    words, they can choose hide Shortcut Bar widget when they don't need. 
*    In addition, widgets placed in Shortcut Bar widget also can drop to other 
*    positions, even the screen.
*
*
*     ex: Shortcut Bar widget
*     +---------+------------+          
*     | +---+   |            |
*     | |W1 |   |            |
*     | +---+   |            |
*     | +---+   |            |
*     | |W2 |   |            |
*     | +---+   |            |
*     | +---+   |            |
*     | |W3 |   |            |
*     | +---+   |            |
*     | Shortcut|            |
*     |   Bar   |            |  
*     +---------+------------+          
*              || drop Widget 1 to the screen.
*              \/
*     +----------+------------+          
*     |          |            |
*     |          |            |
*     |          |   +---+    |
*     | +---+    |   | W1|    |
*     | | W2|    |   +---+    |
*     | +---+    |            |
*     | +---+    |            |
*     | | W3|    |            |
*     | +---+    |            |
*     | Shortcut |            |
*     |   Bar    |            |  
*     +----------+------------+     
*     
*
*/
#ifndef __MMI_WDG_SHORTCUTBAR_H__
#define __MMI_WDG_SHORTCUTBAR_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/
// less than 0x80 means widget at shortcut bar,  >=0x80 means at desktop.
#define SHORTCUTBARWDG_ORDER_DESKTOP		0x80

// don't need to add compile option for shortcut item id
#define SHORTCUTITEM(WIDGETID, IMAGEID)    WIDGETID

#define SHORTCUTBAR_ITMES_TIME \
    SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_CALENDAR,  SHORTCUTS_LIST_CALENDAR_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_TODOLIST, SHORTCUTS_LIST_TODOLIST_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_DIGCLOCK, SHORTCUTS_LIST_DIGITAL_CLOCK_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_ANACLOCK, SHORTCUTS_LIST_CLOCK_ICON)

#define SHORTCUTBAR_ITMES_IMAGE \
    SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_MPLAYER,  SHORTCUTS_LIST_MUSIC_PLAYER_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_FMRADIO,  SHORTCUTS_LIST_FM_RADIO_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_MAP,      SHORTCUTS_LIST_MAP_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_GAME,     SHORTCUTS_LIST_GAME_ICON)\
	,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_LIVEWALLPAPER,	 SHORTCUTS_LIST_LIVEWALLPAPER_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_PET,      SHORTCUTS_LIST_PET_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_QQ,       SHORTCUTS_LIST_QQ_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_NOTE,     SHORTCUTS_LIST_NOTE_ICON)\
    ,SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_PROFILE,  SHORTCUTS_LIST_PROFILES_ICON)

#define SHORTCUTBAR_ITMES_CONTAINTER \
    SHORTCUTITEM(SHORTCUTBAR_ITEMWDG_OPERATOR, SHORTCUTS_LIST_OPERATOR_ICON)

enum
{
	SHORTCUTBAR_ITMES_TIME

	,SHORTCUTBAR_ITMES_IMG_START
    ,SHORTCUTBAR_ITMES_IMG_START_DUMMY = (SHORTCUTBAR_ITMES_IMG_START - 1)
	,SHORTCUTBAR_ITMES_IMAGE
    ,SHORTCUTBAR_ITMES_IMG_END_DUMMY
    ,SHORTCUTBAR_ITMES_IMG_END = (SHORTCUTBAR_ITMES_IMG_END_DUMMY - 1)

    ,SHORTCUTBAR_ITMES_CONTAINER_START
    ,SHORTCUTBAR_ITMES_CONTAINER_START_DUMMY = (SHORTCUTBAR_ITMES_CONTAINER_START - 1)
    ,SHORTCUTBAR_ITMES_CONTAINTER
    ,SHORTCUTBAR_ITMES_CONTAINTER_END_DUMMY
    ,SHORTCUTBAR_ITMES_CONTAINTER_END = (SHORTCUTBAR_ITMES_CONTAINTER_END_DUMMY - 1)

	,SHORTCUTBAR_ITEMWDG_NUM
};

/** ShortCutBar_ItemIcon_t
*
* @brief    u8ItemId:    
*           IconID:     
*
*/
typedef struct{
	u8 u8ItemId;    //e.g. Update the Dog icon, the Item ID is SHORTCUTBAR_ITEMWDG_PET
	u32 IconID;
} ShortCutBar_ItemIcon_t;

/** WdgShortCutBarNwName_t
*
* @brief    pNetworkName:           the pointer of network name
*           pSlaveNetworkName:      the pointer of slave network name
*
*/
typedef struct
{
    MAE_WChar               *pNetworkName;      //the pointer of network name
    MAE_WChar               *pSlaveNetworkName; //the pointer of slave network name

}WdgShortCutBarNwName_t;


enum
{
    SHORTCUTBAR_ICON_ANIM_SHOW,
    SHORTCUTBAR_ICON_ANIM_HIDE,
    SHORTCUTBAR_ICON_ANIM_SLIDE_UP,
    SHORTCUTBAR_ICON_ANIM_SLIDE_DOWN,
    SHORTCUTBAR_ICON_ANIM_SLIDE_UP_DONE,
    SHORTCUTBAR_ICON_ANIM_SLIDE_DOWN_DONE,
    SHORTCUTBAR_ICON_ANIM_SHAKE_START,
    SHORTCUTBAR_ICON_ANIM_SHAKE_DONE,
    SHORTCUTBAR_ICON_ANIM_SCROLL,
    SHORTCUTBAR_ICON_ANIM_SCROLL_DONE,
};

typedef u16 Shortcutbar_Icon_Anim_e;


/** PfnWdgShortCutBarIconMoveOut
* @brief      CB register by "WdgShortCutBarRegisterIconMoveOutCb"
*             and will be trigger when Shortcut icon is moved out event.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pShortcutData     Icon moveout relative info; refer to ShortMoveData_t.
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgShortCutBarIconMoveOut) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortcutData, IWidget *pWidget);

/** PfnWdgShortCutBarIconEvent
* @brief      CB register by "WdgShortCutBarRegisterIconEventCb"
*             and will be trigger when Shortcut icon is moved out event.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pShortcutData     Icon moveout relative info; refer to ShortMoveData_t.
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgShortCutBarIconEvent) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);

/*=============================================================*/
// Interface functions
/*=============================================================*/
/** WdgShortCutBarCreateForWnd
* @brief        Create ShortCutBar widget and set size
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
*
* @retval       The pointer of ShortCutBar  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgShortCutBarCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID
);

/** WdgShortCutBarCreate
* @brief        Create ShortCutBar widget
*
* @retval       The pointer of ShortCutBar  Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgShortCutBarCreate
(
    void
);

/** WdgShortCutBarSetReleaseIn
* @brief        Set the release in
*
* @param[in]    pWDGShortCutBar     Pointer to the ShortCutBar widget
* @param[in]    pReleaseInMoveData  the shortcut bar move data
*
* @retval       None
*
*/
__INLINE void WdgShortCutBarSetReleaseIn
(
    IWidget                 *pWDGShortCutBar,
    ShortMoveData_t         *pReleaseInMoveData
)
{
    WdgCommonSetProperty(pWDGShortCutBar, PROP_SHORTCUTBAR_WDG_RELEASEIN, (u32)pReleaseInMoveData);
}

/** WdgShortCutBarSetReleaseOut
* @brief        Set the release out
*
* @param[in]    pWDGShortCutBar     Pointer to the ShortCutBar widget
* @param[in]    pReleaseOutMoveData the shortcut bar move data
*
* @retval       None
*
*/
__INLINE void WdgShortCutBarSetReleaseOut
(
    IWidget                 *pWDGShortCutBar,
    ShortMoveData_t         *pReleaseOutMoveData
)
{
    WdgCommonSetProperty(pWDGShortCutBar, PROP_SHORTCUTBAR_WDG_RELEASEOUT, (u32)pReleaseOutMoveData);
}

/** WdgShortCutBarSetNetworkName
* @brief        Set network name
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pNetworkName      the pointer of network name
*
* @retval       None
*
*/
__INLINE void WdgShortCutBarSetNetworkName
(
    IWidget                 *pWDGShortCutBar,
    MAE_WChar               *pNetworkName
)
{
    WdgCommonSetProperty(pWDGShortCutBar, PROP_SHORTCUTBAR_WDG_NETWORK_NAME, (u32)pNetworkName);
}

/** WdgShortCutBarSetSlaveNetworkName
* @brief        Set slave network name
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pSlaveNetworkName the pointer of slave network name
*
* @retval       None
*
*/
__INLINE void WdgShortCutBarSetSlaveNetworkName
(
    IWidget                 *pWDGShortCutBar,
    MAE_WChar               *pSlaveNetworkName
)
{
    WdgCommonSetProperty(pWDGShortCutBar, PROP_SHORTCUTBAR_WDG_SLAVE_NETWORK_NAME, (u32)pSlaveNetworkName);
}

/** WdgShortCutBarSetUpdateIcon
* @brief        Update the Icon
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pIcon             the structure pointer of shortcut bar item icon
*
* @retval       None
*
*/
__INLINE void WdgShortCutBarSetUpdateIcon
(
    IWidget                 *pWDGShortCutBar,
    ShortCutBar_ItemIcon_t  *pIcon
)
{
    WdgCommonSetProperty(pWDGShortCutBar, PROP_SHORTCUTBAR_WDG_UPDATE_ICON, (u32)pIcon);
}

/** WdgShortCutBarRegisterIconMoveOutCb
* @brief        Register Icon Move Out callback;
*               CB will be triggered while shortcut Icon Move Out.
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgShortCutBarRegisterIconMoveOutCb
(
    IWidget                         *pWDGShortCutBar,
    PfnWdgShortCutBarIconMoveOut    pfn,
    void                            *pUserData
);

/** WDG_SlideSwitch_DeregisterIconMoveOutCb
* @brief        Deregister callback
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgShortCutBarDeregisterIconMoveOutCb
(
    IWidget                         *pWDGShortCutBar,
    PfnWdgShortCutBarIconMoveOut    pfn,
    void                            *pUserData
);

/** WdgShortCutBarRegisterIconEventCb
* @brief        Register Icon Move Out callback;
*               CB will be triggered while shortcut icon status change.
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgShortCutBarRegisterIconEventCb
(
    IWidget                         *pWDGShortCutBar,
    PfnWdgShortCutBarIconEvent    pfn,
    void                            *pUserData
);

/** WDG_SlideSwitch_DeregisterIconEventCb
* @brief        Deregister callback
*
* @param[in]    pWDGShortCutBar   Pointer to the ShortCutBar widget
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgShortCutBarDeregisterIconEventCb
(
    IWidget                         *pWDGShortCutBar,
    PfnWdgShortCutBarIconEvent    pfn,
    void                            *pUserData
);

#endif //__MMI_WDG_SHORTCUTBAR_H__
/*=============================================================*/
// end of file
