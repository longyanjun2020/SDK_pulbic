#ifndef __MMI_WDG_3DEFFECT_LIGHTING_H__
#define __MMI_WDG_3DEFFECT_LIGHTING_H__

#include "mae_wallpaper_effect.h"

MAE_WALLPAPER_EFFECT_INFO _3deffect_lightning_create(void* pWidget);  // return NULL when create fail
MAE_Ret _3deffect_lightning_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_lightning_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_lightning_configure(MAE_WALLPAPER_CONFIG_DATA *pCfg);
MAE_Ret _3deffect_lightning_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_lightning_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_lightning_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);

#endif
