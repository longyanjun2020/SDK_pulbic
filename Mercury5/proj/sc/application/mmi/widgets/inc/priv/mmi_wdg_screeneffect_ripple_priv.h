#ifdef __SCREEN_EFFECT_RIPPLE_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_RIPPLE_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_RIPPLE_PRIV_H__

typedef struct
{
    boolean speed_4x;
    short   radius;
    short   energy;
}ripplecfg_t;

typedef struct
{
	int w,h;
	short *buf1;
	short *buf2;
}ripple_t;
typedef struct
{
    ripple_t data;
    ripplecfg_t cfg;
} RippleData_t;

// effect functions declare
MAERet_t ScreenEffectRipple_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectRipple_OnStop(void *pThis);
void ScreenEffectRipple_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectRipple_OnTouch(void *pThis, MAE_EventId evt, s32 P1, s32 P2);


#endif //__MMI_WDG_SCREENEFFECT_RIPPLE_PRIV_H__
#endif //__SCREEN_EFFECT_RIPPLE_SUPPORT__

