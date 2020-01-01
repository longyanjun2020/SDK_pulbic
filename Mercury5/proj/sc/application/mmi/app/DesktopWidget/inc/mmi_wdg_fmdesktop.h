/**
* @file    mmi_wdg_fmdesktop.h
* @brief   This file defines the interface of fm desktopwidget.

*/

#ifndef __MMI_WDG_FMDESKTOP_H__
#define __MMI_WDG_FMDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_fmdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)
#if defined(__APP_MMI_FM_RADIO__)
/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgFmDesktopLaunchAdjustVolume
* @brief      CB register by "WdgFmDesktopRegisterLaunchAdjustVolumeCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgFmDesktopLaunchAdjustVolume) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgFmDesktopLaunchAirplaneMode
* @brief      CB register by "WdgFmDesktopRegisterLaunchAirplaneModeCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgFmDesktopLaunchAirplaneMode) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgFmDesktopPlugHeadset
* @brief      CB register by "WdgFmDesktopRegisterLaunchPlugHeadsetCb"
*             and will be trigger when widget be touched.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgFmDesktopPlugHeadset) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgFmDesktopRegisterLaunchAdjustVolumeCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching volume dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopRegisterLaunchAdjustVolumeCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopLaunchAdjustVolume   pfn,
    void                    *pUserData
);

/** WdgFmDesktopRegisterLaunchAirplaneModeCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching air plane mode dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopRegisterLaunchAirplaneModeCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopLaunchAirplaneMode   pfn,
    void                    *pUserData
);

/** WdgFmDesktopRegisterLaunchPlugHeadsetCb
* @brief        Register callback : CB will be triggered when widget be touched, the CB need to implement lunching headset plug dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopRegisterLaunchPlugHeadsetCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopPlugHeadset  pfn,
    void                    *pUserData
);

/** WdgFmDesktopDeregisterLaunchAdjustVolumeCb
* @brief        Deregister callback : CB will be triggered when widget be touched, the CB need to implement lunching volume dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopDeregisterLaunchAdjustVolumeCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopLaunchAdjustVolume   pfn,
    void                    *pUserData
);

/** WdgFmDesktopDeregisterLaunchAirplaneModeCb
* @brief        Deregister callback : CB will be triggered when widget be touched, the CB need to implement lunching air plane mode dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopDeregisterLaunchAirplaneModeCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopLaunchAirplaneMode   pfn,
    void                    *pUserData
);

/** WdgFmDesktopDeregisterLaunchPlugHeadsetCb
* @brief        Deregister callback : CB will be triggered when widget be touched, the CB need to implement lunching headset plug dialog function.
*
* @param[in]    pWDGFMDesktop     The FMDesktop widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgFmDesktopDeregisterLaunchPlugHeadsetCb
(
    IWidget                 *pWDGFMDesktop,
    PfnWdgFmDesktopPlugHeadset  pfn,
    void                    *pUserData
);


#endif // __APP_MMI_FM_RADIO__
#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_FMDESKTOP_H__
/*=============================================================*/
// end of file
