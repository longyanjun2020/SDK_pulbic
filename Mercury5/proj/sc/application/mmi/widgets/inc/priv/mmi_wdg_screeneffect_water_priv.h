#ifdef __SCREEN_EFFECT_WATER_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_WATER_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_WATER_PRIV_H__

typedef struct
{
	float start_wt;
	IBitmap *bmp;
} WaterData_t;

// effect functions declare
MAERet_t ScreenEffectWater_OnCreate(void *pThis);
MAERet_t ScreenEffectWater_OnRelease(void *pThis);
MAERet_t ScreenEffectWater_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectWater_OnStop(void *pThis);
void ScreenEffectWater_OnTimer(void *pThis);
void ScreenEffectWater_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectWatet_SetProperty(void *pThiz, u32 P1, u32 P2);

#endif //__MMI_WDG_SCREENEFFECT_WATER_PRIV_H__
#endif //__SCREEN_EFFECT_WATER_SUPPORT__

