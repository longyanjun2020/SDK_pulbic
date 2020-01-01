/**
* @file mmi_wdg_screensaver_effect_priv.h
* @brief This file defines the data structure of screensaver-effect widget
* @version $Id: mmi_wdg_screensaver_effect_priv.h $
*/
#ifndef __MMI_WDG_SCREENSAVER_EFFECT_PRIV_H__
#define __MMI_WDG_SCREENSAVER_EFFECT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_log.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_event.h"
#include "mae_widget_common.h"
#include "mmi_mae_widgetbase.h"

#include "mmi_wdg_screensaver_effect.h"

#include "mmi_coresrv.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define SCREENSAVER_START_DELAY 5

typedef struct
{
	WidgetBaseEx_t   WdgBase;

	boolean bWdgActivate;
	boolean bWdgEnableAnimate;
	ICORESRV *pICoreSrv;

	u16 u16SceneHandleId;
	u32 u32NodeID;
	u32 nEffectIdx;

	LIVE_EFFECT_SCREENSAVER_INFO_PTR pEffectData;

}ScreensaverEffectWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret ScreensaverEffect_New(MAE_ClsId ClsID, void **ppObj);
boolean ScreensaverEffect_HandleEvent(IWidget *pWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static void _ScreensaverEffect_AnimationTimerCb(void* pWidget);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _ScreensaverEffect_ReloadRC(ScreensaverEffectWdg_t *pThis, DisplayMode_e nDispMode);
#endif // __AUTO_ROTATE_DISPLAY__

#endif //__MMI_WDG_SCREENSAVER_EFFECT_PRIV_H__
/*=============================================================*/
// end of file
