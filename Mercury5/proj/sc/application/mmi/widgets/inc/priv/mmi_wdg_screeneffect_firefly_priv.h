#ifdef __SCREEN_EFFECT_FIREFLY_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_FIREFLY_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_FIREFLY_PRIV_H__

typedef struct
{
    Point_t 	start;
    Point_t 	end;
    s8 	life;
    float     	step;
    float     	t;
    s8 	type;
}FlyUnit_t;

typedef struct
{
    FlyUnit_t  * units;
#ifdef __TOUCH_SCREEN_MMI__
    FlyUnit_t * tsunits;
#endif
} FireFlyData_t;

// effect functions declare
MAERet_t ScreenEffectFirefly_OnCreate(void *pThis);
MAERet_t ScreenEffectFirefly_OnRelease(void *pThis);
MAERet_t ScreenEffectFirefly_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectFirefly_OnStop(void *pThis);
void ScreenEffectFirefly_OnTimer(void *pThis);
void ScreenEffectFirefly_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectFirefly_SetProperty(void *pThis, u32 P1, u32 P2);
boolean ScreenEffectFirefly_OnTouch(void *pThiz, MAEEvent_t evt, s32 x, s32 y);


#endif //__MMI_WDG_SCREENEFFECT_FIREFLY_PRIV_H__
#endif //__SCREEN_EFFECT_FIREFLY_SUPPORT__

