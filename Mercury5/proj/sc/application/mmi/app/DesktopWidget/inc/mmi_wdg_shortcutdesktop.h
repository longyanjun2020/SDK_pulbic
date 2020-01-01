/**
* @file    mmi_shortcutesktopwidget.h
* @brief   This file defines the interface of ShortcutDesktopwidget.

*/

#ifndef __MMI_WDG_SHORTCUTDESKTOP_H__
#define __MMI_WDG_SHORTCUTDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_shortcutdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

/** WdgShortcutDesktop
* @brief        Init ShortcutDesktop widget
*
* @param[in]    pWDGShortcutDesktop  Pointer to the ShortcutDesktop widget
* @retval       NULL                                    Failed.
*
*/
void WdgShortcutDesktopInit
(
    IWidget                 *pWDGShortcutDesktop
);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_SHORTCUTDESKTOP_H__
/*=============================================================*/
// end of file
