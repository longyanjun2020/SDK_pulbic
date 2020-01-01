#ifndef __MAE_3DEFFECT_BEE_H__
#define __MAE_3DEFFECT_BEE_H__

//#include "mmi_wdg_3deffect_bee.h"
#include "mae_wallpaper_effect.h"

MAE_WALLPAPER_EFFECT_INFO _3deffect_bird_create(void* pWidget);  // return NULL when create fail
MAE_Ret _3deffect_bird_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_bird_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_bird_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
MAE_Ret _3deffect_bird_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_bird_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);

#endif // __MAE_3DEFFECT_BEE_H__
