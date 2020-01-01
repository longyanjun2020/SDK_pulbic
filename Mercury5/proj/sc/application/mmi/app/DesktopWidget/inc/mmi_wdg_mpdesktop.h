/**
* @file    mmi_wdg_mpdesktop.h
* @brief   This file defines the interface of mp desktopwidget.

*/

#ifndef __MMI_WDG_MPDESKTOP_H__
#define __MMI_WDG_MPDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_wdg_mpdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgMpDesktopLaunchAdjustVolume
* @brief      CB register by "WdgMpDesktopRegisterLaunchAdjustVolumeCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pLaunchInfo       The info of launch application, refer to DesktopWdg_LaunchApp_Info_t
* @param[in]  nReserve          Reserve for enhancement in the future
*
*/
typedef void (*PfnWdgMpDesktopLaunchAdjustVolume) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
/*=============================================================*/
// functions
/*=============================================================*/

/** WdgMpDesktopRegisterLaunchAdjustVolumeCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching volume dialog function.
*
* @param[in]    pWDGMpDesktop     The MpDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMpDesktopRegisterLaunchAdjustVolumeCb
(
    IWidget                 *pWDGMpDesktop,
    PfnWdgMpDesktopLaunchAdjustVolume   pfn,
    void                    *pUserData
);

/** WdgMpDesktopDeregisterLaunchAdjustVolumeCb
* @brief        Deregister callback : CB will be triggered when widget be touched, the CB need to implement lunching volume dialog function.
*
* @param[in]    pWDGMpDesktop     The MpDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMpDesktopDeregisterLaunchAdjustVolumeCb
(
    IWidget                 *pWDGMpDesktop,
    PfnWdgMpDesktopLaunchAdjustVolume   pfn,
    void                    *pUserData
);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_MPDESKTOP_H__
/*=============================================================*/
// end of file
