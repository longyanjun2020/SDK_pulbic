/**
* @file    mmi_wdg_wallpaper.h
* @brief   This file defines the interface of wallpaper widget
* @author  eric.wang@mstarsemi.com
* @version $Id: mmi_wdg_wallpaper.h$
*/
/*
Property:
PROP_WALLPAPER_WDG_STYLE
*/

#ifndef __MAE_WALLPAPERWIDGET_H__
#define __MAE_WALLPAPERWIDGET_H__

#include "mmi_mae_window.h"
#include "mmi_wdg_common_interface.h"

#include "mmi_setting_cfg.h"

typedef void (*PfnWdgWallpaperContentChanged) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bChanged, void *pReserve);
typedef void (*PfnWdgWallpaperContentTouched) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bTouched, void *pReserve);
typedef void (*PfnWdgWallpaperPlayAudio) (void *pUsrData1, void *pUsrData2, WidgetEvtCode_t nEvtCode, u32 dwParam, IWIDGET *pWdg);


IWidget* WdgWallpaperCreateForWnd(HWIN hWin, Pos_t *pPos, WidgetSize_t *pSize, u16 nWidgetID);
IWidget* WdgWallpaperCreate(void);

void WdgWallpaperStart(IWidget *pWallpaper);
void WdgWallpaperRestart(IWidget *pWallpaper);

MAE_Ret WdgWallpaperRegisterContentChangedCb(IWidget *pWallpaper, PfnWdgWallpaperContentChanged pfn, void *pUserData);
MAE_Ret WdgWallpaperDeregisterContentChangedCb(IWidget *pWallpaper, PfnWdgWallpaperContentChanged pfn, void *pUserData);

MAE_Ret WdgWallpaperRegisterContentTouchedCb(IWidget *pWallpaper, PfnWdgWallpaperContentTouched pfn, void *pUserData);
MAE_Ret WdgWallpaperDeregisterContentTouchedCb(IWidget *pWallpaper, PfnWdgWallpaperContentTouched pfn, void *pUserData);

MAE_Ret WdgWallpaperRegisterPlayAudioCb(IWidget *pWallpaper, PfnWdgWallpaperPlayAudio pfn, void *pUserData);
MAE_Ret WdgWallpaperDeregisterPlayAudioCb(IWidget *pWallpaper, PfnWdgWallpaperPlayAudio pfn, void *pUserData);

MAE_Ret WdgWallpaperSetPreviewMode(IWidget *pWallpaper, boolean bPreview);

MAE_INLINE MAE_Ret WdgWallpaperEnableAnim(IWidget *pWallpaper, boolean bAnim)
{
	return WdgCommonSetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_ANIM, (u32)bAnim);
}

MAE_INLINE MAE_Ret WdgWallpaperIsAnim(IWidget *pWallpaper, boolean *pAnim)
{
	return WdgCommonGetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_ANIM, (u32 *)pAnim);
}

MAE_INLINE MAE_Ret WdgWallpaperSetId(IWidget *pWallpaper, SetWallpaper_3DEffect_e eEffectId)
{
	return WdgCommonSetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_ID, (u32)eEffectId);
}

MAE_INLINE MAE_Ret WdgWallpaperGetId(IWidget *pWallpaper, SetWallpaper_3DEffect_e *pEffectId)
{
	return WdgCommonGetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_ID, (u32 *)pEffectId);
}

MAE_INLINE MAE_Ret WdgWallpaperSetEditMode(IWidget *pWallpaper, boolean bEdit)
{
	return WdgCommonSetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_EDIT, (u32)bEdit);
}

MAE_INLINE MAE_Ret WdgWallpaperIsEditMode(IWidget *pWallpaper, boolean *pEdit)
{
	return WdgCommonGetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_EDIT, (u32 *)pEdit);
}

MAE_INLINE MAE_Ret WdgWallpaperConfigure(IWidget *pWallpaper, boolean bConfigure)
{
	return WdgCommonSetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_CONFIGURE, (u32)bConfigure);
}

MAE_INLINE MAE_Ret WdgWallpaperSetWithStatusBar(IWidget *pWallpaper, boolean bWithStatusBar)
{
	return WdgCommonSetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_WITH_STATUS_BAR, (u32)bWithStatusBar);
}

MAE_INLINE MAE_Ret WdgWallpaperIsContentChanged(IWidget *pWallpaper, boolean *pContentChanged)
{
	return WdgCommonGetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_CONTENT_CHANGED, (u32 *)pContentChanged);
}

MAE_INLINE MAE_Ret WdgWallpaperIsContentTouched(IWidget *pWallpaper, boolean *pContentTouched)
{
	return WdgCommonGetProperty(pWallpaper, PROP_WALLPAPER_3D_EFFECT_CONTENT_TOUCHED, (u32 *)pContentTouched);
}
#endif /* __MAE_WALLPAPERWIDGET_H__ */

