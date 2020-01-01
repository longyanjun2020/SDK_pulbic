#ifndef __MAE_3DEFFECT_FARM_H__
#define __MAE_3DEFFECT_FARM_H__

#include "mae_wallpaper_effect.h"
#include "mmi_mae_graphic.h"

MAE_WALLPAPER_EFFECT_INFO _3deffect_farm_create(void* pWidget);
MAE_Ret _3deffect_farm_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_farm_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_farm_configure(MAE_WALLPAPER_CONFIG_DATA *pCfg);
MAE_Ret _3deffect_farm_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
MAE_Ret _3deffect_farm_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_farm_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);
#if 0
void _3deffect_aquaria_SetBGOffset(MAE_WALLPAPER_EFFECT_INFO peffectdata, Pos_t *pPos);
void _3deffect_aquaria_GetBGOffset(MAE_WALLPAPER_EFFECT_INFO peffectdata, Pos_t *pPos);
#endif

#endif
