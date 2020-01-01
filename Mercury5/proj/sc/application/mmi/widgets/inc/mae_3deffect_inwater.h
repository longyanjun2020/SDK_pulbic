#ifndef __MAE_3DEFFECT_INWATER_H__
#define __MAE_3DEFFECT_INWATER_H__

/*=============================================================*/
// Platform definition
/*=============================================================*/
#ifdef C_MODEL
    #define INWATER_ON_CMODEL
#else
    #define INWATER_ON_MAE_PLATFORM
#endif

/*=============================================================*/
// Platform definition
/*=============================================================*/
#ifdef INWATER_ON_MAE_PLATFORM
#include "mae_wallpaper_effect.h"
#else
//Commnet to avoid abuse api check
//#include "WinMain.h"
#define IDLEAPP_LAYOUT_MULTIPAGE_BUTTON_CONTAINER_H     (0)
#endif

#define MAX_INWATER_LEVEL    30
#define INWATER_SCENE_SWITCH_STEP    60
#define MAX_BUBBLE_NUM 10
#define MAX_FISH_NUM 10
#define INWATER_EXPLOSION_SIZE   64.0f
#define BUTTON_X 280.0f
#define BUTTON_Y 90.0f

/*************************************************************************/
/*   Type/Structure/Enum definitions                                     */
/*************************************************************************/

#ifdef INWATER_ON_MAE_PLATFORM
MAE_WALLPAPER_EFFECT_INFO _3deffect_inwater_create(void* pWidget);  // return NULL when create fail
MAE_Ret _3deffect_inwater_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_inwater_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_inwater_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
MAE_Ret _3deffect_inwater_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_inwater_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_inwater_active(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_inwater_inactive(MAE_WALLPAPER_EFFECT_INFO peffectdata);
u32 _3deffect_inwater_getBGImage(MAE_WALLPAPER_EFFECT_INFO peffectdata);
#else
MAE_Ret InwaterWidget_New(void **ppObj);
boolean InwaterWidget_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);
void InwaterWidget_Draw(IWidget *pWdg, IDispCanvas *pIDispCanvas, s32 x, s32 y);
MAE_Ret InwaterWidget_Release(void *ppObj);
#endif

#endif // __MAE_3DEFFECT_INWATER_H__
