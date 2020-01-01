////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    
* @version
* @brief   header file
*
*/

#ifndef __DROPLET_INC__
#define __DROPLET_INC__

/*=============================================================*/
// Platform definition
/*=============================================================*/
#ifdef C_MODEL
    #define DROPLET_ON_CMODEL
#else
    #define DROPLET_ON_MAE_PLATFORM
#endif
/*=============================================================*/
// Include files
/*=============================================================*/

#ifdef DROPLET_ON_MAE_PLATFORM
#include "mae_wallpaper_effect.h"
#else
//Commnet to avoid abuse api check
//#include "WinMain.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef DROPLET_ON_MAE_PLATFORM
MAE_WALLPAPER_EFFECT_INFO _3deffect_droplet_create(void* pWidget);
MAE_Ret _3deffect_droplet_release(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_droplet_release_cache(MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_droplet_draw(MAE_WALLPAPER_EFFECT_INFO peffectdata, IDispCanvas *pDispCanvas, s32 x, s32 y);
MAE_Ret _3deffect_droplet_animation_timehandler(void* pWidget, MAE_WALLPAPER_EFFECT_INFO peffectdata);
MAE_Ret _3deffect_droplet_touchevent_handler(MAE_EventId eventID, u32 param1, u32 param2, MAE_WALLPAPER_EFFECT_INFO peffectdata);
#else
MAE_Ret DropletWidget_New(void **ppObj);
boolean DropletWidget_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);
void DropletWidget_Draw(IWidget *pWdg, IDispCanvas *pIDispCanvas, s32 x, s32 y);
MAE_Ret DropletWidget_Release(void *ppObj);
#endif

#endif /* __DROPLET_INC__ */

