#ifndef __MMI_MAE_LIVE_EFFECT_H__
#define __MMI_MAE_LIVE_EFFECT_H__

#if defined(__FEATURE_MGL__)

#include "mmi_mae_common_def.h"
#include "mmi_rs_macro_struct.h"
//#include "rs_layout.rs"

/// screensaver begin

enum
{
	SCREENSAVER_STYLE_BEGIN = 0,

	SCREENSAVER_STYLE_ROAMING = SCREENSAVER_STYLE_BEGIN,
	SCREENSAVER_STYLE_BUBBLING,
	SCREENSAVER_STYLE_FALLING,
	SCREENSAVER_STYLE_VECTOR,

	SCREENSAVER_STYLE_END,
};
typedef u16 ScreensaverStytle_e;

typedef void* LIVE_EFFECT_SCREENSAVER_INFO_PTR;

typedef LIVE_EFFECT_SCREENSAVER_INFO_PTR (*live_effect_screensaver_create)(void* pWidget, Pos_t *pPos, WidgetSize_t *pSize); 
typedef MAE_Ret (*live_effect_screensaver_release)(LIVE_EFFECT_SCREENSAVER_INFO_PTR pEffectdata);
typedef MAE_Ret (*live_effect_screensaver_draw)(LIVE_EFFECT_SCREENSAVER_INFO_PTR pEffectdata, u32 nNodeID);
typedef MAE_Ret (*live_effect_screensaver_animation)(void* pWidget, LIVE_EFFECT_SCREENSAVER_INFO_PTR pEffectdata);

typedef struct
{
	ScreensaverStytle_e eEffectStyle;                        // style idenifier, in eNum
	u32 nAnimationInterval;                                  // time interval for animation, in ms    
	live_effect_screensaver_create    pfnCreate;             // create effect
	live_effect_screensaver_release   pfnRelease;            // release effect
	live_effect_screensaver_draw      pfnDraw;               // draw effect
	live_effect_screensaver_animation pfnAnimation;          // time out handler for animation    

} LiveEffectScreensaverEntry_t;

extern const LiveEffectScreensaverEntry_t LiveEffect_Screensaver_tbl[];

extern u32 LiveEffect_GetScreensaverCount(void);

#define LIVE_EFFECT_TOTAL_SCREENSAVER       LiveEffect_GetScreensaverCount()

/// screensaver end

#endif
#endif
