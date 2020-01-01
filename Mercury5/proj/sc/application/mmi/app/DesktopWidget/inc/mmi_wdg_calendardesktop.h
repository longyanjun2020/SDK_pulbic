/**
* @file    mmi_wdg_calendardesktop.h
* @brief   This file defines the interface of calendar desktopwidget.

*/

#ifndef __MMI_WDG_CALENDARDESKTOP_H__
#define __MMI_WDG_CALENDARDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_calendardesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgCalendarDesktopWdgCallBack
* @brief      CB register by "WdgCalendarDesktopRegisterEventCb"
*             and will be triggered when user release touch inside the region of widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgCalendarDesktopWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** WdgCalendarDesktopRegisterEventCb
* @brief        Register callback : CB will be triggered when widget should be paused.
*
* @param[in]    pWDGCalendardesktop The Calendar desktop widget which want to set callback
* @param[in]    pfn                 callback function
* @param[in]    pUsrData            User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgCalendarDesktopRegisterEventCb
(
    IWidget                 *pWDGCalendardesktop,
    PfnWdgCalendarDesktopWdgCallBack pfn,
    void                    *pUserData
);

/** WdgCalendarDesktopDeregisterEventCb
* @brief        Deregister WdgCalendarDesktopRegisterEventCb callback
*
* @param[in]    pWDGCalendardesktop The Calendar desktop widget which want to cancel callback
* @param[in]    pfn                 callback function
* @param[in]    pUsrData            User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgCalendarDesktopDeregisterEventCb
(
    IWidget                 *pWDGCalendardesktop,
    PfnWdgCalendarDesktopWdgCallBack pfn,
    void                    *pUserData
);

#endif

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__
/*=============================================================*/
// end of file
