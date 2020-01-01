/**
* @file    mmi_wdg_opdesktop.h
* @brief   This file defines the interface of op desktopwidget.

*/

#ifndef __MMI_WDG_OPDESKTOP_H__
#define __MMI_WDG_OPDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_opdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

/** WdgOpDesktopSetMasterUpdate
* @brief        Set the pointer of string to the text master
*
* @param[in]    pWDGOpDesktop     Pointer to the OpDesktop widget
* @param[in]    pText             A pointer of string to set text master
*
* @retval       void
*
*/
__INLINE void WdgOpDesktopSetMasterUpdate
(
    IWidget                 *pWDGOpDesktop,
    MAE_WChar               *pText
)
{
    WdgCommonSetProperty(pWDGOpDesktop, PROP_OPDESKTOP_WDG_MASTER_UPDATE, (u32)pText);
}

/** WdgOpDesktopSetSlaveUpdate
* @brief        Set the pointer of string to the text slave
*
* @param[in]    pWDGOpDesktop     Pointer to the OpDesktop widget
* @param[in]    pText             A pointer of string to set text slave
*
* @retval        void
*
*/
__INLINE void WdgOpDesktopSetSlaveUpdate
(
    IWidget                 *pWDGOpDesktop,
    MAE_WChar               *pText
)
{
    WdgCommonSetProperty(pWDGOpDesktop, PROP_OPDESKTOP_WDG_SLAVE_UPDATE, (u32)pText);
}

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_OPDESKTOP_H__
/*=============================================================*/
// end of file
