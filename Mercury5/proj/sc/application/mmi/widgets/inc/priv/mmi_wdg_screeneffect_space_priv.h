#ifdef __SCREEN_EFFECT_SPACE_SUPPORT__
#ifndef __MMI_WDG_SCREENEFFECT_SPACE_PRIV_H__
#define __MMI_WDG_SCREENEFFECT_SPACE_PRIV_H__

typedef struct
{
    float	m_Value;		 //当前值
    float	m_V;             //移动速度
    float	m_MinValue;      //下界
    float	m_MaxValue;      //上界
    float  m_MinV;          //最小速度
    float  m_MaxV;          //最大速度
}PointMover_t;

typedef struct
{
    long    m_DrawCount;
    long    m_SpotCount;        //固定点点数
    long    m_IteratCount;      //迭代次数
    long    m_dataLength;
    float  *m_S0x;
    float  * m_S0y;
    float  * m_S1x;
    float  * m_S1y;
    PointMover_t mover[2];
    u32 prevtm;
} SpaceData_t;

// effect functions declare
MAERet_t ScreenEffectSpace_OnCreate(void *pThis);
MAERet_t ScreenEffectSpace_OnRelease(void *pThis);
MAERet_t ScreenEffectSpace_OnStart(void *pThis,void *pCfgData);
MAERet_t ScreenEffectSpace_OnStop(void *pThis);
void ScreenEffectSpace_OnTimer(void *pThis);
void ScreenEffectSpace_OnDraw(void *pThis, IDisplay *pDisp, s32 x, s32 y);
boolean ScreenEffectSpace_SetProperty(void *pThis, u32 P1, u32 P2);
boolean ScreenEffectSpace_OnTouch(void *pThiz, MAEEvent_t evt, s32 x, s32 y);


#endif // __MMI_WDG_SCREENEFFECT_SPACE_PRIV_H__
#endif // __SCREEN_EFFECT_SPACE_SUPPORT__
