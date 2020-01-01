#ifdef __SCREEN_EFFECT_BEZIER_SUPPORT__

#ifndef __MMI_WDG_SCREENEFFECT_BEZIER_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_BEZIER_PRIV_H__


#define MAX_BEZIER_CURVES 16

typedef struct
{
	s32 nVertX[4];
	s32 nVertY[4];
} ThreeBezierVertex_t;

typedef struct
{
	u32 nBezTotal;
	u32 nBezCurr;
	u32 nColor;
	ThreeBezierVertex_t BezBuf[MAX_BEZIER_CURVES];
	struct
	{
		s32 nVelX[4];
		s32 nVelY[4];
	} Velocity;
} ThreeBezierData_t;


// effect functions declare
MAERet_t ScreenEffectBezier_OnCreate(void *pThis);
MAERet_t ScreenEffectBezier_OnRelease(void *pThis);
MAERet_t ScreenEffectBezier_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectBezier_OnStop(void *pThis);
void ScreenEffectBezier_OnTimer(void *pThis);
void ScreenEffectBezier_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);

#endif //__MMI_WDG_SCREENEFFECT_BEZIER_PRIV_H__
#endif //__SCREEN_EFFECT_BEZIER_SUPPORT__
