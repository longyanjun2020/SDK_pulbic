#ifndef __MAE_3DEFFECT_GRASSTRACE_INC__
#define __MAE_3DEFFECT_GRASSTRACE_INC__

#include "mae_wallpaper_effect.h"

MAE_WALLPAPER_EFFECT_INFO _3deffect_grasstrace_create(void* pWidget);
MAE_Ret _3deffect_grasstrace_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_grasstrace_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_grasstrace_configure(MAE_WALLPAPER_CONFIG_DATA *pCfg);
MAE_Ret _3deffect_grasstrace_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
MAE_Ret _3deffect_grasstrace_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_grasstrace_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);

#endif