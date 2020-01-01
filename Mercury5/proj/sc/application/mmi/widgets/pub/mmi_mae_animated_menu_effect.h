/**
 * @file    mmi_mae_animated_menu_effect.h
 */

#ifndef __MMI_MAE_ANIMATED_MENU_EFFECT_H__
#define __MMI_MAE_ANIMATED_MENU_EFFECT_H__

#ifdef __MMI_ENABLE_ANIMATED_MENU_EFFECT__

#include "mmi_mae_common_def.h"
/*=============================================================*/
// type and define
/*=============================================================*/
#define ANIMATION_EFFECT_TIMER 50		//ms

enum
{
	ANIMATED_MENU_LIGHTNING_EFFECT = 0,
	ANIMATED_MENU_SPARKLERS_EFFECT,
	ANIMATED_MENU_DISCHARGE_EFFECT,
	ANIMATED_MENU_CLOUDRING_EFFECT,
	ANIMATED_MENU_SPARK_EFFECT,
	ANIMATED_MENU_BRILLIANT_EFFECT,
	ANIMATED_MENU_BURN_EFFECT,

	ANIMATED_MENU_TOTAL_EFFECT,		// new effect must be added before this
	ANIMATED_MENU_NO_EFFECT
};

typedef u8 AnimatedMenuEffectStyle_e;

typedef struct
{
	const u32 *pImageIDArray;
	u32 nFrames;
	boolean bUnderFocusImg;
	boolean bRandomPlay;
}AnimatedMenuEffect_t;

#endif	// __MMI_ENABLE_ANIMATED_MENU_EFFECT__
#endif	//__MMI_ANIMATED_MENU_EFFECT_H__
