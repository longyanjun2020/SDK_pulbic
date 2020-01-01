/**
* @file    mmi_wdg_phonebookdesktop.h
* @brief   This file defines the interface of phonebook desktopwidget.

*/

#ifndef __MMI_WDG_PHONEBOOKDESKTOP_H__
#define __MMI_WDG_PHONEBOOKDESKTOP_H__

#if defined (__GADGETS_MMI__) || defined(__3D_UI_IDLE_MULTIPAGE__)

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_phonebookdesktop_priv.h"
#include "mmi_wdg_headers.h"
#include "mmi_launcher_shortcutphb.h"

/*=============================================================*/
// functions
/*=============================================================*/
typedef void (*PfnWdgPhbDesktopWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** WdgPhonebookDesktopSetPhbSrvStatusReady
* @brief        Set phb service ready status to the Widget.
*
* @param[in]    pDesktopPhb         
* @param[in]    nImageId           Large Image ID.
*
* @retval       none
*
*/
__INLINE void WdgPhonebookDesktopSetPhbSrvStatusReady
(
    IWidget                 *pDesktopPhb,
    boolean                 bPhbSrvReady
)
{
    WdgCommonSetProperty(pDesktopPhb, PROP_PHBDESKTOP_WDG_PHBSRV_READY, (u32)bPhbSrvReady);
}

/** WdgPhonebookDesktopRegisterAniCompleteCb
* @brief        Register animation complete.
*
* @param[in]    pdesktop         
* @param[in]    pfn           callback funptr
*
* @retval       none
*
*/
MAE_Ret WdgPhonebookDesktopRegisterAniStatusCb(
    IWidget *pdesktop, 
    PfnWdgPhbDesktopWdgCallBack pfn,
    void *pUserData
);

/** WdgPhonebookDesktopDeregisterAniStatusCb
* @brief        Deregister animation complete.
*
* @param[in]    pdesktop         
* @param[in]    pfn           callback funptr
*
* @retval       none
*
*/
MAE_Ret WdgPhonebookDesktopDeregisterAniStatusCb(
    IWidget *pdesktop, 
    PfnWdgPhbDesktopWdgCallBack pfn,
    void *pUserData
);
#endif //__GADGETS_MMI__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_DCLOCKDESKTOP_H__
/*=============================================================*/
// end of file
