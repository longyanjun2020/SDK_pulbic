#ifdef __SCREEN_EFFECT_METEOR_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_METEOR_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_METEOR_PRIV_H__

#define MAX_METEOR_NUM	5

typedef struct
{
	bool enable;
	Point_t start;
	Point_t end;
	Point_t cur;
	Point_t cur_end;
	s32 diff;
} Star;

typedef struct
{
	float start_wt;
	Star *star_param;
	IBitmap *bmp;
} MeteorData_t;

// effect functions declare
MAERet_t ScreenEffectMeteor_OnCreate(void *pThis);
MAERet_t ScreenEffectMeteor_OnRelease(void *pThis);
MAERet_t ScreenEffectMeteor_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectMeteor_OnStop(void *pThis);
void ScreenEffectMeteor_OnTimer(void *pThis);
void ScreenEffectMeteor_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectMeteor_OnTouch(void *pThiz, MAEEvent_t evt, s32 x, s32 y);
boolean ScreenEffectMeteor_SetProperty(void *pThiz, u32 P1, u32 P2);

#endif //__MMI_WDG_SCREENEFFECT_Meteor_PRIV_H__
#endif //__SCREEN_EFFECT_METEOR_SUPPORT__
