/**
* @file    mmi_wdg_notepaddesktop.h
* @brief   This file defines the interface of notepad desktopwidget.

*/

#ifndef __MMI_WDG_NOTEPADDESKTOP_H__
#define __MMI_WDG_NOTEPADDESKTOP_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__) && defined(__APP_MMI_NOTEPAD__)

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_headers.h"
#include "mmi_wdg_notepaddesktop_priv.h"


/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgNotepadDesktopWdgCallBack
* @brief      CB register by "WdgNotepadDesktopRegisterEventCb"
*             and will be triggered when user release touch inside the region of widget.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgNotepadDesktopWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** WdgNotepadDesktopRegisterEventCb
* @brief        Register callback : CB will be triggered when widget should be paused.
*
* @param[in]    pWDGNotepaddesktop The Notepad desktop widget which want to set callback
* @param[in]    pfn                 callback function
* @param[in]    pUsrData            User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgNotepadDesktopRegisterEventCb
(
    IWidget                 *pWDGNotepaddesktop,
    PfnWdgNotepadDesktopWdgCallBack pfn,
    void                    *pUserData
);

/** WdgNotepadDesktopDeregisterEventCb
* @brief        Deregister WdgNotepadDesktopRegisterEventCb callback
*
* @param[in]    pWDGNotepaddesktop The Notepad desktop widget which want to cancel callback
* @param[in]    pfn                 callback function
* @param[in]    pUsrData            User Data can be gotton when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgNotepadDesktopDeregisterEventCb
(
    IWidget                 *pWDGNotepaddesktop,
    PfnWdgNotepadDesktopWdgCallBack pfn,
    void                    *pUserData
);


#endif //__3D_UI_IDLE_MULTIPAGE__ && __APP_MMI_NOTEPAD__
#endif //__MMI_WDG_NOTEPADDESKTOP_H__
/*=============================================================*/
// end of file
