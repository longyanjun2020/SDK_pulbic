/**
* @file    mmi_wdg_searchdesktop.h
* @brief   This file defines the interface of search desktopwidget.

*/

#ifndef __MMI_WDG_SEARCHDESKTOP_H__
#define __MMI_WDG_SEARCHDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_searchdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) 

/** PfnWdgSearchDesktopFocusChange
* @brief      CB register by "WdgSearchDesktopRegisterFocusChangeCb"
*             and will be trigger when the focus of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  bFocus            True
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgSearchDesktopFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);
/*=============================================================*/
// functions
/*=============================================================*/

/** WdgSearchDesktopRegisterFocusChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGSearchDesktop The SearchDesktop widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotten when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSearchDesktopRegisterFocusChangeCb
(
    IWidget                         *pWDGSearchDesktop,
    PfnWdgSearchDesktopFocusChange  pfn,
    void                            *pUserData
);

/** WdgSearchDesktopDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item
*
* @param[in]    pWDGSearchDesktop The SearchDesktop widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUsrData          User Data can be gotten when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgSearchDesktopDeregisterFocusChangeCb
(
    IWidget                         *pWDGSearchDesktop,
    PfnWdgSearchDesktopFocusChange  pfn,
    void                            *pUserData
);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__

#endif //__MMI_WDG_SEARCHDESKTOP_H__
/*=============================================================*/
// end of file
