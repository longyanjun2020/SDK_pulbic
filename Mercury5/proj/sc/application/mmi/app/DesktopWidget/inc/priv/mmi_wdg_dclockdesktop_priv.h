/**
 * @file    mmi_wdg_dclockdesktop_priv.h
 * @brief   The internal structure of the digital clock desktopwidget

 */

#ifndef __MMI_WDG_DCLOCKDESKTOP_PRIV_H__
#define __MMI_WDG_DCLOCKDESKTOP_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_settingapp.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"
#include "rs_layout_id.h"
#include "mmi_coresrv.h"
#include "mmi_mae_clock_types.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__) || defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#define __DCLOCK_DESKTOPWDG_3D_UI_STYLE__ // 3D UI without 3D effect
#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
#define __DCLOCK_DESKTOPWDG_3D_UI_CIRCLESTYLE__ // Use 3D effect
#endif // Use 3D effect
#endif // Use 3D UI

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
	DClockDesktopWidget_Style_e  eDClockStyle;
#if defined(__DCLOCK_DESKTOPWDG_3D_UI_STYLE__)
	DesktopWidget_DisplayMode_e eDisplayMode;
#endif //#if defined(__DCLOCK_DESKTOPWDG_3D_UI_STYLE__)

	IWidget			*pITextWidget;
    IWidget         *pIImageWidget[4];
    IWidget         *pIImage12HWidget;

#if defined(__DCLOCK_DESKTOPWDG_3D_UI_STYLE__)
#ifdef __DCLOCK_DESKTOPWDG_3D_UI_CIRCLESTYLE__
    IWidget         *pITimeIndWidget;
#endif // __DCLOCK_DESKTOPWDG_3D_UI_CIRCLESTYLE__

    boolean         bPauseTimeUpdate;

    // World clock
    MAE_TimeZone_e  eTimeZone;
    IWidget         *pTimeZoneTextWdg;

    IWidget         *pIText12HWidget;

#endif //#if defined(__DCLOCK_DESKTOPWDG_3D_UI_STYLE__)

	ClockListener_t IClockListener;
	IClock			*pIClock;
	SetPhoneTimeFormat_e	eTimeFormat;
#if defined(__G3D_MMI__)
	ICORESRV	*pICoreSrv;
#endif
} DclockDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__
#endif //__MMI_WDG_DCLOCKDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
