#ifdef __SCREEN_EFFECT_FIRE_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_FIRE_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_FIRE_PRIV_H__

typedef struct
{
	u8 *Energy[2];
	u32 uCurEnergy;
	u8 *Fuel;
	u32 *clut;
	boolean bFullAlpha;
} FireData_t;


// effect functions declare
MAERet_t ScreenEffectFire_OnCreate(void *pThis);
MAERet_t ScreenEffectFire_OnRelease(void *pThis);
MAERet_t ScreenEffectFire_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectFire_OnStop(void *pThis);
void ScreenEffectFire_OnTimer(void *pThis);
void ScreenEffectFire_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectFire_OnTouch(void *pThis, MAE_EventId evt, s32 x, s32 y);

#endif //__MMI_WDG_SCREENEFFECT_FIRE_PRIV_H__
#endif  //__SCREEN_EFFECT_FIRE_SUPPORT__

