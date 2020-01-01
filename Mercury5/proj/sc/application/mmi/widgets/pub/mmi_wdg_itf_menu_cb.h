#ifndef __MMI_WDG_ITF_MENU_CB_H__
#define __MMI_WDG_ITF_MENU_CB_H__
/* ===========================================================*/
// Description
/* ===========================================================*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_menu.h"
#include "mmi_mae_menumodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*PfnWdgMenuTitleDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TitleDataChangeData_t *pTitleDataChangeData, IWidget *pWidget);
typedef void (*PfnWdgMenuTitleVisibleChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TitleElmntVisibleChangeData_t *pTitleElmntVisibleChangeData, IWidget *pWidget);

// List: EVT_VIEWMDL_FOCUS_SELECT <--> Menu: softkey -> EVT_MENUWIDGET_SELECT
typedef void (*PfnWdgMenuMenuSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuMenuBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
typedef void (*PfnWdgMenuMenuLongPress)(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

// List: EVT_VIEWMDL_FOCUS_CHANGE <--> Menu: EVT_MENUWIDGET_ON_FOCUS
typedef void (*PfnWdgMenuOnFocus) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuMarkedNumberChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
typedef void (*PfnWdgMenuLessMarkedBounds) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
typedef void (*PfnWdgMenuExceedMarkedBounds) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
typedef void (*PfnWdgMenuSizeChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
typedef void (*PfnWdgMenuSoftkeyAct) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuTouchNoItem) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
typedef void (*PfnWdgMenuWidgetItemChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
typedef void (*PfnWdgMenuWidgetFlagChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MenuModelFlagChangeData_t *pMenuFlagChangeData, IWidget *pWidget);
typedef void (*PfnWdgMenuSoftkeyCancel) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuMenuReqLayer2) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuBackToLayer1) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuLayer2SoftkeyCancel) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuLayer2MenuSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuLayer2OnFocus) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
typedef void (*PfnWdgMenuLayer2SoftkeyAct) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
typedef void (*PfnWdgMenuScrollDone)(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
// List: EVT_VIEWMDL_BOUNDS_TOP <--> Menu: EVT_MENUWIDGET_BOUNDS_TOP
typedef void (*PfnWdgMenuBoundTop) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);

// List: EVT_VIEWMDL_BOUNDS_BTM<--> Menu: EVT_MENUWIDGET_BOUNDS_BTM
typedef void (*PfnWdgMenuBoundBottom) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);

/*=============================================================*/
/** WdgMenuRegisterScrollFinishCb
* @brief        Register callback : For handling change the title.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterScrollFinishCb
(
    IWidget                      *pWDGMenu,
    PfnWdgMenuScrollDone         pfn,
    void                         *pUserData
);

/** WdgMenuDeregisterScrollFinishCb
* @brief        Register callback : For handling change the title.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterScrollFinishCb
(
    IWidget                      *pWDGMenu,
    PfnWdgMenuScrollDone         pfn,
    void                         *pUserData
);

/** WdgMenuRegisterTitleDataChangeCb
* @brief        Register callback : For handling change the title.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterTitleDataChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTitleDataChange pfn,
    void                    *pUserData
);


/** WdgMenuRegisterTitleVisibleChangeCb
* @brief        Register callback : For handling change the title.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterTitleVisibleChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTitleVisibleChange pfn,
    void                    *pUserData
);


/** WdgMenuRegisterMenuSelectCb
* @brief        Register callback : When user touches/presses the softkey to be set as SK_SELECT/SK_CHANGE/SK_OK, and the menu is the normal menu, the option menu of second layer, or first layer item without second option menu.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterMenuSelectCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMenuSelect pfn,
    void                    *pUserData
);


/** WDG_Menu_RegisterMenuRequestOption2CB
* @brief        Register callback : When user touches/presses the softkey to be set as SK_SELECT/SK_CHANGE/SK_OK, and the menu is the option menu with second option menu in first layer touched/pressed.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterMenuReqLayer2Cb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMenuReqLayer2 pfn,
    void                    *pUserData
);


/** WdgMenuRegisterMenuBackCb
* @brief        Register callback : When user touches/presses the softkey to be set as SK_BACK, and the menu is the normal menu, the option menu of first layer.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterMenuBackCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMenuBack    pfn,
    void                    *pUserData
);

/** WDG_Menu_RegisterBackToOption1CB
* @brief        Register callback : When user touches/presses the softkey to be set as SK_BACK, and the menu is the option menu of second layer.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterBackToLayer1Cb
(
    IWidget *pWDGMenu,
    PfnWdgMenuBackToLayer1 pfn,
    void                    *pUserData
);

/** WdgMenuRegisterOnFocusCb
* @brief        Register callback : When the menu widget is focused or the user changes the highlight item.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterOnFocusCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuOnFocus pfn,
    void                    *pUserData
);


/** WdgMenuRegisterMarkedNumberChangeCb
* @brief        Register callback : CB will be triggered when total marked number is changed
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterMarkedNumberChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMarkedNumberChange pfn,
    void                    *pUserData
);

/** WdgMenuRegisterLayer2MarkedNumberChangeCb
* @brief        Register callback : CB will be triggered when total marked number is changed
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterLayer2MarkedNumberChangeCb
(
 IWidget                 *pWDGMenu,
 PfnWdgMenuMarkedNumberChange pfn,
 void                    *pUserData
 );

/** WdgMenuRegisterLessMarkedBoundsCb
* @brief        Register callback : CB will be triggered when total marked number is less than minimum mark number
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgMenuRegisterLessMarkedBoundsCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLessMarkedBounds pfn,
    void                    *pUserData
);


/** WdgMenuRegisterExceedMarkedBoundsCb
* @brief        Register callback : CB will be triggered when total marked number is more than maximum mark number
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterExceedMarkedBoundsCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuExceedMarkedBounds pfn,
    void                    *pUserData
);


/** WdgMenuRegisterSizeChangeCb
* @brief        Register callback : CB will be triggered when the size is changed
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterSizeChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuSizeChange pfn,
    void                    *pUserData
);

/** WdgMenuRegisterSoftkeyActCb
* @brief        Register callback : CB will be triggered when softkey is pressed ex, OK, Stop, Save...
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterSoftkeyActCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuSoftkeyAct pfn,
    void                    *pUserData
);

MAE_Ret WdgMenuRegisterItemChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuWidgetItemChange pfn,
    void                    *pUserData
);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgMenuRegisterTouchNoItemCb
* @brief        Register callback : CB will be triggered when no item is touched
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterTouchNoItemCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTouchNoItem pfn,
    void                    *pUserData
);
#endif

/** WdgMenuRegisterItemChangeCb
* @brief        Register menu item change callback; CB will be triggered while menu item is changed.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterItemChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuWidgetItemChange pfn,
    void                    *pUserData
);


/** WdgMenuRegisterFlagChangeCb
* @brief        Register flag change callback; CB will be triggered while menu flag has changed.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterFlagChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuWidgetFlagChange pfn,
    void                    *pUserData
);

/** WdgMenuRegisterBoundTopNotifyCb
* @brief        Register callback : For list widget CB will be triggered when the focus move to the top item and can't wrap.
*
* @param[in]    pWDGMenu          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterBoundTopNotifyCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuBoundTop      pfn,
    void                    *pUserData
);

/** WdgMenuRegisterBoundBottomNotifyCb
* @brief        Register callback : For list widget, CB will be triggered when the focus move to the end item and can't wrap.
*
* @param[in]    pWDGMenu          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterBoundBottomNotifyCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuBoundBottom   pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterTitleDataChangeCb
* @brief        Deregister PfnWdgMenuTitleDataChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterTitleDataChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTitleDataChange pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterTitleVisibleChangeCb
* @brief        Deregister PfnWdgMenuTitleVisibleChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterTitleVisibleChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTitleVisibleChange pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterMenuSelectCb
* @brief        Deregister PfnWdgMenuMenuSelect callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterMenuSelectCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuMenuSelect pfn,
    void                    *pUserData
);


/** WDG_Menu_DeregisterMenuRequestOption2CB
* @brief        Deregister WDG_Menu_MenuRequestOption2_CB callback
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterMenuReqLayer2Cb
(
    IWidget *pWDGMenu,
    PfnWdgMenuMenuReqLayer2 pfn,
    void                    *pUserData
);


/** WdgMenuDeregisterMenuBackCb
* @brief        Deregister PfnWdgMenuMenuBack callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterMenuBackCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMenuBack pfn,
    void                    *pUserData
);


/** WDG_Menu_DeregisterBackToOption1CB
* @brief        Deregister WDG_Menu_BackToOption1_CB callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterBackToLayer1Cb
(
    IWidget *pWDGMenu,
    PfnWdgMenuBackToLayer1 pfn,
    void                    *pUserData
);


/** WdgMenuDeregisterOnFocusCb
* @brief        Deregister PfnWdgMenuOnFocus callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterOnFocusCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuOnFocus pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterMarkedNumberChangeCb
* @brief        Deregister PfnWdgMenuMarkedNumberChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterMarkedNumberChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuMarkedNumberChange pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterLayer2MarkedNumberChangeCb
* @brief        Deregister PfnWdgMenuMarkedNumberChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterLayer2MarkedNumberChangeCb
(
 IWidget                 *pWDGMenu,
 PfnWdgMenuMarkedNumberChange pfn,
 void                    *pUserData
 );


/** WdgMenuDeregisterLessMarkedBoundsCb
* @brief        Deregister PfnWdgMenuLessMarkedBounds callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgMenuDeregisterLessMarkedBoundsCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLessMarkedBounds pfn,
    void                    *pUserData
);


/** WdgMenuDeregisterExceedMarkedBoundsCb
* @brief        Deregister PfnWdgMenuExceedMarkedBounds callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterExceedMarkedBoundsCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuExceedMarkedBounds pfn,
    void                    *pUserData
);


/** WdgMenuDeregisterSizeChangeCb
* @brief        Deregister PfnWdgMenuSizeChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterSizeChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuSizeChange pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterSoftkeyActCb
* @brief        Deregister PfnWdgMenuSoftkeyAct callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterSoftkeyActCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuSoftkeyAct pfn,
    void                    *pUserData
);


#ifdef __TOUCH_SCREEN_MMI__
/** WdgMenuDeregisterTouchNoItemCb
* @brief        Deregister PfnWdgMenuTouchNoItem callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterTouchNoItemCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuTouchNoItem pfn,
    void                    *pUserData
);

#endif //__TOUCH_SCREEN_MMI__

/** WDG_Menu_DeregisterMenumdlChangeCB
* @brief        Deregister PfnWdgMenuWidgetItemChange callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterItemChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuWidgetItemChange pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterFlagChangeCb
* @brief        Deregister flag change callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterFlagChangeCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuWidgetFlagChange pfn,
    void                    *pUserData
);


/** WdgMenuRegisterSoftkeyCancelCb
* @brief        Register callback: When user touches/presses the softkey to be set as "Cancel"
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterSoftkeyCancelCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuSoftkeyCancel pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_RegisterLayer2SoftkeyCancelCB
* @brief        Register callback: When user touches/presses the softkey to be set as "Cancel"
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterLayer2SoftkeyCancelCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2SoftkeyCancel pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_RegisterLayer2SoftkeySelectCB
* @brief        Register callback : When user touches/presses the softkey to be set as SK_SELECT/SK_CHANGE/SK_OK, and the menu is the normal menu, the option menu of second layer, or first layer item without second option menu.
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterLayer2MenuSelectCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2MenuSelect pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_RegisterLayer2OnFocusCB
* @brief        Register callback : When the menu widget is focused or the user changes the highlight item.
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterLayer2OnFocusCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2OnFocus pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_RegisterLayer2SoftkeyAct_CB
* @brief        Register callback : CB will be triggered when no item is touched
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuRegisterLayer2SoftkeyActCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2SoftkeyAct pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_DeregisterLayer1SoftkeyCancelCB
* @brief        Deregister WDG_OptionMenu_Layer1SoftkeyCancel_CB callback
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterSoftkeyCancelCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuSoftkeyCancel pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_DeregisterLayer2SoftkeyCancelCB
* @brief        Deregister WDG_OptionMenu_Layer2SoftkeyCancel_CB callback
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterLayer2SoftkeyCancelCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2SoftkeyCancel pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_DeregisterLayer2SoftkeySelectCB
* @brief        Deregister WDG_OptionMenu_Layer2SoftkeySelect_CB callback
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterLayer2MenuSelectCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2MenuSelect pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_DeregisterLayer2OnFocusCB
* @brief        Deregister WDG_OptionMenu_Layer2OnFocus_CB callback
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterLayer2OnFocusCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2OnFocus pfn,
    void                    *pUserData
);


/** WDG_OptionMenu_DeregisterLayer2SoftkeyAct_CB
* @brief        Deregister WDG_OptionMenu_Layer2SoftkeyAct_CB callback
*
* @param[in]    pWDGMenu          The OptionMenu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterLayer2SoftkeyActCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuLayer2SoftkeyAct pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterBoundTopNotifyCb
* @brief        Deregister callback : For list widget CB will be triggered when the focus move to the top item and can't wrap.
*
* @param[in]    pWDGMenu          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterBoundTopNotifyCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuBoundTop      pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterBoundBottomNotifyCb
* @brief        Deregister callback : For list widget, CB will be triggered when the focus move to the end item and can't wrap.
*
* @param[in]    pWDGMenu          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgMenuDeregisterBoundBottomNotifyCb
(
    IWidget                 *pWDGMenu,
    PfnWdgMenuBoundBottom   pfn,
    void                    *pUserData
);

/** WdgMenuDeregisterMenuLongPressCb
* @brief        Deregister PfnWdgMenuMenuLongPress callback
*
* @param[in]    pWDGMenu          The Menu widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuDeregisterMenuLongPressCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuMenuSelect pfn,
    void                    *pUserData
);

/** WdgMenuRegisterLongPressEvtCb
* @brief        Register callback : CB will be triggered when menu item is long pressed.
*
* @param[in]    pWDGMenu          The Menu widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMenuRegisterMenuLongPressCb
(
    IWidget *pWDGMenu,
    PfnWdgMenuSoftkeyAct pfn,
    void                    *pUserData
);

#endif //__MMI_WDG_ITF_MENU_CB_H__

