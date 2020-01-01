#ifndef __MMI_MAE_WALLPAPER_EFFECT_H__
#define __MMI_MAE_WALLPAPER_EFFECT_H__

#include "mmi_mae_common_def.h"
#include "mmi_setting_cfg.h"
#include "mmi_mae_widget.h"

typedef void* MAE_WALLPAPER_EFFECT_INFO;
typedef void* MAE_WALLPAPER_CONFIG_DATA;

typedef MAE_WALLPAPER_EFFECT_INFO (*effect_create)(void* pWidget);  // return NULL when create fail
typedef MAE_Ret (*effect_release)(MAE_WALLPAPER_EFFECT_INFO peffectdata);
typedef MAE_Ret (*effect_release_cache)(MAE_WALLPAPER_EFFECT_INFO peffectdata);
typedef MAE_Ret (*effect_configure)(MAE_WALLPAPER_CONFIG_DATA *pCfg, boolean bLoadCfg);
typedef MAE_Ret (*effect_edit)(MAE_WALLPAPER_EFFECT_INFO peffectdata, boolean bedit);
typedef MAE_Ret (*effect_draw)(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
typedef MAE_Ret (*effect_animation_timehandler)(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
typedef MAE_Ret (*effect_touchevent_handler)(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);

typedef enum
{
    WALLPAPER_IMAGE_STYLE_DEFAULT,
    WALLPAPER_IMAGE_STYLE_SYSTEM,
} WallpaperImageStyle_e;

typedef enum
{
    WALLPAPER_CREATEMODE_DEFAULT,
    WALLPAPER_CREATEMODE_PREVIEW,
} WallpaperCreateMode_e;

typedef struct{
	SetWallpaper_3DEffect_e eAnimationStyle;
    effect_create fnCreate;     // create wallpaper effect
    effect_release fnRelease;  // release wallpaper effect
    effect_release_cache fnReleaseCache;   // release cache of wallpaper effect
    effect_configure fnConfigure;   // config wallpaper effect
	effect_edit fnEdit;			// config wallpaper edit effect
    effect_draw fnDraw;         // wallpaper draw function
    effect_animation_timehandler fnAnimation; // time handler for animation    
    effect_touchevent_handler fnEventHandler;   // touch event handler
    u32 animation_timer; // time interval for animation, in ms
    WallpaperImageStyle_e eImageStyle;
    u32 nImageID;
} WallpaperEffectEntry_t;

u32 WallpaperEffect_Total(void);

extern const WallpaperEffectEntry_t WallpaperEffect_tbl[];

#endif // __MMI_MAE_WALLPAPER_EFFECT_H__
