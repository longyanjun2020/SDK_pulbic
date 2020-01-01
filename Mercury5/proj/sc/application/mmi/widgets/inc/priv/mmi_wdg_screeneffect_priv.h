#ifdef __SCREEN_EFFECTS_SUPPORT__

#ifndef __MMI_WDG_SCREENEFFECT_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_PRIV_H__

#include "mae_decoratorbase.h"
#include "mmi_coresrv.h"

#include "mmi_wdg_screeneffect.h"
#define PI 				3.141592f

#include "mmi_wdg_screeneffect_bezier_priv.h"
#include "mmi_wdg_screeneffect_snow_priv.h"
#include "mmi_wdg_screeneffect_ripple_priv.h"
#include "mmi_wdg_screeneffect_fire_priv.h"
#include "mmi_wdg_screeneffect_firefly_priv.h"
#include "mmi_wdg_screeneffect_water_priv.h"
#include "mmi_wdg_screeneffect_meteor_priv.h"
#include "mmi_wdg_screeneffect_space_priv.h"

typedef enum
{
 #ifdef __SCREEN_EFFECT_BEZIER_SUPPORT__
 	PROP_SCREENEFFECT_BEZIER ,
 #endif
 #ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
 	PROP_SCREENEFFECT_SNOW ,
 #endif
 #ifdef __SCREEN_EFFECT_RIPPLE_SUPPORT__
 	PROP_SCREENEFFECT_RIPPLE ,
 #endif
 #ifdef __SCREEN_EFFECT_FIRE_SUPPORT__
 	PROP_SCREENEFFECT_FIRE ,
 #endif
 #ifdef __SCREEN_EFFECT_FIREFLY_SUPPORT__
 	PROP_SCREENEFFECT_FIREFLY ,
 #endif
 #ifdef __SCREEN_EFFECT_WATER_SUPPORT__
 	PROP_SCREENEFFECT_WATER ,
 #endif
 #ifdef __SCREEN_EFFECT_METEOR_SUPPORT__
 	PROP_SCREENEFFECT_METEOR ,
 #endif
 #ifdef __SCREEN_EFFECT_SPACE_SUPPORT__
 	PROP_SCREENEFFECT_SPACE ,
 #endif

	PROP_SCREENEFFECT_NO_EFFECT ,
} ScreenEffectType_e;
typedef struct _ScreenEffectWdg_t
{
    DecoratorEx_t   DecBase;

    // current selected effect type
    ScreenEffectType_e eEffectType;

    // time interval for animation, in ms, default is 1
    u32 uAnimTimerTimeout;

    // CoreSrv
    ICORESRV  *pICoreSrv;

    // many effects need another composition canvas, here it is.
    // they are independent of display screen
    IBITMAP *pBmp;
    IDisplay *pDisplay;

    // many actions are did during widget is drawn
    // widget drawn is triggered by timer, but also maybe triggered by other actions
    // this variable is to avoid do animate when drawn is triggered by other actions
    // it is set to TRUE when timer timeout, and is reset to FALSE after did animate when drawn
    boolean bDoNextStep;

    // for convenience, size of screen and main menu bitmap position
    s32 uScreenWidth;
    s32 uScreenHeight;
    s32 uClientX;
    s32 uClientY;
    ////////////////////////////////////////
    // datas for every types of screen effect:
	u8 PlaceHolder1[128];
    // for bezier curve
#ifdef __SCREEN_EFFECT_BEZIER_SUPPORT__
    ThreeBezierData_t BezierData;
#endif
    // for snow
#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
    SnowData_t SnowData;
#endif
    // for ripple
#ifdef __SCREEN_EFFECT_RIPPLE_SUPPORT__
    RippleData_t RippleData;
#endif

    // for fire
#ifdef __SCREEN_EFFECT_FIRE_SUPPORT__
    FireData_t FireData;
#endif

    // for firefly
#ifdef __SCREEN_EFFECT_FIREFLY_SUPPORT__
    FireFlyData_t FireflyData;
#endif
    // for water
#ifdef __SCREEN_EFFECT_WATER_SUPPORT__
    WaterData_t WaterData;
#endif

	// for meteor
#ifdef __SCREEN_EFFECT_METEOR_SUPPORT__
	MeteorData_t MeteorData;
#endif
#ifdef __SCREEN_EFFECT_SPACE_SUPPORT__
    SpaceData_t SpaceData;
#endif

    // snow effect is active
    boolean   bSnowEffectNeedActive;
    boolean   bNeedToDraw;
	IImage *pszEffectBkImage;

	u8 PlaceHolder2[128];
} ScreenEffectWdg_t;

#endif //__MMI_WDG_SCREENEFFECT_PRIV_H__

#endif //__SCREEN_EFFECTS_SUPPORT__
