#ifdef __SCREEN_EFFECTS_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_TABLE_H__
#define __MMI_WDG_SCREENEFFECT_TABLE_H__

#include "mmi_wdg_screeneffect_priv.h"
/*************************************************************************/
/*   Type/Structure/Enum definitions                                     */
/*************************************************************************/
typedef MAERet_t (*pfnOnStart)(void *pThis,void *pCfgData);
typedef MAERet_t (*pfnOnStop)(void *pThis);
typedef void (*pfnOnTimer)(void *pThis);
typedef void (*pfnOnDraw)(void *pThis, IDisplay *pDisp, s32 x, s32 y);
typedef MAERet_t (*pfnOnCreate)(void *pThis);
typedef MAERet_t (*pfnOnRelease)(void *pThis);
typedef boolean (*pfnsetProperty)(void *pThis, u32 P1, u32 P2);
typedef boolean (*pfnTouchHandle)(void *pThis, MAE_EventId eventID, s32 P1, s32 P2);


typedef struct
{
	ScreenEffectType_e eStyle;
	pfnOnCreate Create;
	pfnOnRelease Release;
	pfnsetProperty setProperty;
	pfnOnStart	Start;
	pfnOnStop	Stop;
	pfnOnDraw  Draw;
	pfnOnTimer  TimeCB;
	pfnTouchHandle TouchCB;
} ScreenEffectEntry_t;

#ifdef __MMI_WDG_SCREENEFFECT_TABEL_C__
static const ScreenEffectEntry_t g_WdgScreenEffectEntryTbl[]=
{
#ifdef __SCREEN_EFFECT_BEZIER_SUPPORT__
	{PROP_SCREENEFFECT_BEZIER, ScreenEffectBezier_OnCreate, ScreenEffectBezier_OnRelease, NULL, ScreenEffectBezier_OnStart, ScreenEffectBezier_OnStop, ScreenEffectBezier_OnDraw, ScreenEffectBezier_OnTimer, NULL},
#endif
#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
	{PROP_SCREENEFFECT_SNOW, ScreenEffectSnow_OnCreate, ScreenEffectSnow_OnRelease, ScreenEffectSnow_SetProperty, ScreenEffectSnow_OnStart, ScreenEffectSnow_OnStop, ScreenEffectSnow_OnDraw, ScreenEffectSnow_OnTimer, NULL},
#endif
#ifdef __SCREEN_EFFECT_RIPPLE_SUPPORT__
	{PROP_SCREENEFFECT_RIPPLE, NULL, NULL, NULL, ScreenEffectRipple_OnStart, ScreenEffectRipple_OnStop, ScreenEffectRipple_OnDraw, NULL, ScreenEffectRipple_OnTouch},
#endif
#ifdef __SCREEN_EFFECT_FIRE_SUPPORT__
	{PROP_SCREENEFFECT_FIRE, ScreenEffectFire_OnCreate, ScreenEffectFire_OnRelease, NULL, ScreenEffectFire_OnStart, ScreenEffectFire_OnStop, ScreenEffectFire_OnDraw, ScreenEffectFire_OnTimer, ScreenEffectFire_OnTouch},
#endif
#ifdef __SCREEN_EFFECT_FIREFLY_SUPPORT__
	{PROP_SCREENEFFECT_FIREFLY, ScreenEffectFirefly_OnCreate, ScreenEffectFirefly_OnRelease, NULL, ScreenEffectFirefly_OnStart, ScreenEffectFirefly_OnStop, ScreenEffectFirefly_OnDraw, ScreenEffectFirefly_OnTimer, ScreenEffectFirefly_OnTouch},
#endif
#ifdef __SCREEN_EFFECT_WATER_SUPPORT__
	{PROP_SCREENEFFECT_WATER, ScreenEffectWater_OnCreate, ScreenEffectWater_OnRelease, ScreenEffectWatet_SetProperty, ScreenEffectWater_OnStart, ScreenEffectWater_OnStop, ScreenEffectWater_OnDraw, ScreenEffectWater_OnTimer, NULL},
#endif
#ifdef __SCREEN_EFFECT_METEOR_SUPPORT__
	{PROP_SCREENEFFECT_METEOR, ScreenEffectMeteor_OnCreate, ScreenEffectMeteor_OnRelease, ScreenEffectMeteor_SetProperty, ScreenEffectMeteor_OnStart, ScreenEffectMeteor_OnStop, ScreenEffectMeteor_OnDraw, ScreenEffectMeteor_OnTimer, ScreenEffectMeteor_OnTouch},
#endif
#ifdef __SCREEN_EFFECT_SPACE_SUPPORT__
	{PROP_SCREENEFFECT_SPACE, ScreenEffectSpace_OnCreate, ScreenEffectSpace_OnRelease, NULL, ScreenEffectSpace_OnStart, ScreenEffectSpace_OnStop, ScreenEffectSpace_OnDraw, ScreenEffectSpace_OnTimer, ScreenEffectSpace_OnTouch},
#endif

	{PROP_SCREENEFFECT_NO_EFFECT, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
};

u8 g_nWdgScreenEffectNum = sizeof(g_WdgScreenEffectEntryTbl)/sizeof(g_WdgScreenEffectEntryTbl[0]);
#else
extern const ScreenEffectEntry_t g_WdgScreenEffectEntryTbl[];
extern u8 g_nWdgScreenEffectNum;
#endif

#endif  //__MMI_WDG_SCREENEFFECT_TABLE_H__
#endif //__SCREEN_EFFECTS_SUPPORT__

