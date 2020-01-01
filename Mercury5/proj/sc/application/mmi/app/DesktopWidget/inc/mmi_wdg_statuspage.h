/**
 * @file    mmi_wdg_statuspage.h
 * @brief   The document describes the interface of StatusPage Widget
 */
#ifndef __MMI_WDG_STATUSPAGE_H__
#define __MMI_WDG_STATUSPAGE_H__

#ifdef __DROPDOWN_STATUSPAGE__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

enum
{
    STATUSPAGE_SIGNAL_BG,
    STATUSPAGE_SIGNAL_SIM1TEXT,
    STATUSPAGE_SIGNAL_SIM1ICON,
    STATUSPAGE_SIGNAL_SIM1OPTEXT,
//#ifdef __DUAL_SIM_MMI__
    STATUSPAGE_SIGNAL_SIM2TEXT,
    STATUSPAGE_SIGNAL_SIM2ICON,
    STATUSPAGE_SIGNAL_SIM2OPTEXT,
//#endif
    STATUSPAGE_AIRPLANE_BG,
    STATUSPAGE_AIRPLANE_TEXT,
    STATUSPAGE_AIRPLANE_SWITCH,
    STATUSPAGE_AIRPLANE_SWITCHON,
    STATUSPAGE_AIRPLANE_SWITCHOFF,
    STATUSPAGE_AIRPLANE_SWITCHICON,
    STATUSPAGE_WIFI_BG,
    STATUSPAGE_WIFI_TEXT,
    STATUSPAGE_WIFI_SETTING_BG,
    STATUSPAGE_WIFI_APTEXT,
    STATUSPAGE_WIFI_APICON,
    STATUSPAGE_WIFI_SWITCH,
    STATUSPAGE_WIFI_SWITCHON,
    STATUSPAGE_WIFI_SWITCHOFF,
    STATUSPAGE_WIFI_SWITCHICON,
    STATUSPAGE_MESSAGE_BG,
    STATUSPAGE_MESSAGE_MSTEXT,
    STATUSPAGE_MESSAGE_MSNUM,
    STATUSPAGE_MESSAGE_VMTEXT,
    STATUSPAGE_MESSAGE_VMNUM,
    STATUSPAGE_VIBRATE_BG,
    STATUSPAGE_PROFILE_TEXT,
    STATUSPAGE_VIBRATE_CHANGE,
    STATUSPAGE_VIBRATE_CHANGELEFT,
    STATUSPAGE_VIBRATE_CHANGERIGHT,
    STATUSPAGE_VIBRATE_MODETEXT,
    STATUSPAGE_VIBRATE_TEXT,
    STATUSPAGE_VIBRATE_SWITCH,
    STATUSPAGE_VIBRATE_SWITCHON,
    STATUSPAGE_VIBRATE_SWITCHOFF,
    STATUSPAGE_VIBRATE_SWITCHICON,
    STATUSPAGE_BLUETOOTH_BG,
    STATUSPAGE_BLUETOOTH_TEXT,
    STATUSPAGE_BLUETOOTH_SETTING_BG,
    STATUSPAGE_BLUETOOTH_SETTING_TEXT,
    STATUSPAGE_BLUETOOTH_SWITCH,
    STATUSPAGE_BLUETOOTH_SWITCHON,
    STATUSPAGE_BLUETOOTH_SWITCHOFF,
    STATUSPAGE_BLUETOOTH_SWITCHICON,
    STATUSPAGE_ALARM_BG,
    STATUSPAGE_ALARM_TEXT,
    STATUSPAGE_ALARM_CHANGE,
    STATUSPAGE_ALARM_CHANGELEFT,
    STATUSPAGE_ALARM_CHANGERIGHT,
    STATUSPAGE_ALARM_MODETEXT,
    STATUSPAGE_ALARM_TIME,
    STATUSPAGE_ALARM_TIMETEXT,
    STATUSPAGE_ALARM_SWITCH,
    STATUSPAGE_ALARM_SWITCHON,
    STATUSPAGE_ALARM_SWITCHOFF,
    STATUSPAGE_ALARM_SWITCHICON,
    STATUSPAGE_BATTERY_BG,
    STATUSPAGE_BATTERY_TEXT,
    STATUSPAGE_BATTERY_STATUS,
    STATUSPAGE_BATTERY_STATUSTEXT,
//#ifdef __DUAL_BATTERY__
    STATUSPAGE_SLAVE_BATTERY_BG,
    STATUSPAGE_SLAVE_BATTERY_TEXT,
    STATUSPAGE_SLAVE_BATTERY_STATUS,
    STATUSPAGE_SLAVE_BATTERY_STATUSTEXT,
//#endif
    STATUSPAGE_COMP_BMPWDG_SUM,
    STATUSPAGE_DUMMY = STATUSPAGE_COMP_BMPWDG_SUM - 1, ///< do not modify this line
    STATUSPAGE_COMP_WDG_SUM
};

typedef u32 StatpageCompWdg_e;

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgStatuspageCreateForWnd
* @brief        Create Statuspage Widget and set the Statuspage value for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    bBGEnable           Set true or false to enable or disable
*
* @retval       The pointer of Statusbar    Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgStatusPageCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    boolean                 bBGEnable
);
/*=============================================================*/
/** WdgStatusbarCreate
* @brief        Create Statuspage widget
*
* @retval       The pointer of Statusbar    Success.
* @retval       NULL                        Failed.
*
*/
IWidget* WdgStatusPageCreate
(
    void
);

enum
{
	STATUSPAGE_AIRPLANE_MODE_REQUEST,
	STATUSPAGE_AIRPLANE_MODE_DONE,
	STATUSPAGE_AIRPLANE_MODE_FAIL_SIM_BUSY,
	STATUSPAGE_AIRPLANE_MODE_SHOW_STOP_BT_DLG,
};

typedef void (*PfnStatusPageCloseAnimDone) (void *pApplet/*, void *pUsrData, WidgetEvtCode_t nEvtCode, IWidget *pWidget*/);

typedef void (*PfnStatusPageLaunchApp) (void *pApplet);

typedef void (*PfnStatusPageAirplaneMode) (void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);

MAE_Ret StatusPageWidget_New(MAE_ClsId ClsID, void **ppObj);

MAE_Ret StatusPageRegisterCloseAnimDoneCb
(
    IWidget                 *pWDG,
    PfnStatusPageCloseAnimDone   pfn,
    void                    *pUserData
);

MAE_Ret StatusPageDeregisterCloseAnimDoneCb
(
    IWidget                 *pWDG,
    PfnStatusPageCloseAnimDone   pfn,
    void                    *pUserData
);

MAE_Ret StatusPageRegisterLaunchAppCb
(
    IWidget                 *pWDG,
    PfnStatusPageLaunchApp   pfn,
    void                    *pUserData
);

MAE_Ret StatusPageDeregisterLaunchAppCb
(
    IWidget                 *pWDG,
    PfnStatusPageLaunchApp   pfn,
    void                    *pUserData
);

MAE_Ret StatusPageRegisterAirplaneModeCb
(
    IWidget                 *pWDG,
    PfnStatusPageAirplaneMode   pfn,
    void                    *pUserData
);

MAE_Ret StatusPageDeregisterAirplaneModeCb
(
    IWidget                 *pWDG,
    PfnStatusPageAirplaneMode   pfn,
    void                    *pUserData
);
#endif // __DROPDOWN_STATUSPAGE__
#endif /*__MMI_WDG_STATUSPAGE_H__ */

