#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_SNOW_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_SNOW_PRIV_H__

#define MAX_SNOW_NUM	1000

typedef struct
{
	Point_t *ptSnow;
	u8 *pBorderInfo;
	s32 blow_x;
	s32 blow_y;
	u32 blow_count;

	// snow config
	u32 cfgSnowSpeed;
	u32 cfgSnowNum;
	u32 cfgBigSnowNum;
	u32 cfgBlowType;	// 0 - random, 1 - left, 2 - down, 3 - right
	u32 cfgBlowChange;	// blow_count overflow count
	u32 cfgPileSpeed;
	u32 cfgSnowColor;
} SnowData_t;

// effect functions declare
MAERet_t ScreenEffectSnow_OnCreate(void *pThis);
MAERet_t ScreenEffectSnow_OnRelease(void *pThis);
MAERet_t ScreenEffectSnow_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectSnow_OnStop(void *pThis);
void ScreenEffectSnow_OnTimer(void *pThis);
void ScreenEffectSnow_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectSnow_SetProperty(void *pThis, u32 P1, u32 P2);

#endif //__MMI_WDG_SCREENEFFECT_SNOW_PRIV_H__
#endif //__SCREEN_EFFECT_SNOW_SUPPORT__

