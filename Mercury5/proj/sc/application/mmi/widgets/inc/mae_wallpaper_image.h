#ifndef __MAE_WALLPAPER_IMAGE_H__
#define __MAE_WALLPAPER_IMAGE_H__

#include "mae_wallpaper_effect.h"

MAE_WALLPAPER_EFFECT_INFO _wallpaper_image_create(void* pWidget);  // return NULL when create fail
MAE_Ret _wallpaper_image_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _wallpaper_image_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
//MAE_Ret _wallpaper_image_configure(MAE_WALLPAPER_CONFIG_DATA *pCfg);
MAE_Ret _wallpaper_image_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
//MAE_Ret _wallpaper_image_animation_timehandler(void);
MAE_Ret _wallpaper_image_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);

#endif
