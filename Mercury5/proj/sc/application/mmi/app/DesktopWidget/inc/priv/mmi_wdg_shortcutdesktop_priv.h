/**
 * @file    mmi_basicdesktopwidget_priv.h
 * @brief   The internal structure of the basicdesktopwidget

 */

#ifndef __MMI_WDG_SHORTCUTDESKTOP_PRIV_H__
#define __MMI_WDG_SHORTCUTDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_cfgsrv.h"
#include "rs_layout_id.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

    DesktopWidget_DisplayMode_e eDisplayMode;

	// Subwidget codes
#if defined(__3D_UI_IDLE_MULTIPAGE__)
    IWidget *pLabelWidget;
    u32     u32ShortcutId;

    IWidget *pShadowWidget;
#endif    
} ShortcutDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__

#endif //__MMI_WDG_SHORTCUTDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
