#ifdef __SCREEN_EFFECTS_SUPPORT__

#ifndef __MMI_WDG_SCREENEFFECT_H__
#define __MMI_WDG_SCREENEFFECT_H__
#include "mmi_mae_widget.h"

// for PROP_SCREENEFFECT_WDG_EFFECT_TYPE


// for PROP_SCREENEFFECT_WDG_SNOW_BLOW_DIR
#ifdef __SCREEN_EFFECT_SNOW_SUPPORT__
enum
{
    SCREENEFFECT_SNOW_BLOW_TOGGLE = 0,
    SCREENEFFECT_SNOW_BLOW_LEFWARD = 1,
    SCREENEFFECT_SNOW_BLOW_RIGHTWARD = 2,
};
#endif
IWidget* WdgScreenEffectCreateForWnd
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID
 );
#endif //__MMI_WDG_SCREENEFFECT_H__
#endif //__SCREEN_EFFECTS_SUPPORT__
