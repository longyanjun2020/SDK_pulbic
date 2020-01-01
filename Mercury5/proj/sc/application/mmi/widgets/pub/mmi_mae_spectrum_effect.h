#ifndef __MMI_MAE_SPECTRUM_EFFECT_H__
#define __MMI_MAE_SPECTRUM_EFFECT_H__
#include "mmi_wdg_common_interface.h"

#ifdef __3D_UI_MPLAYER__

#include "mmi_mediasrv_common.h"

typedef void* MAE_SPECTRUM_EFFECT_INFO;

typedef MAE_SPECTRUM_EFFECT_INFO (*spectrum_effect_create)(void* pWidget, Pos_t *pPos, WidgetSize_t *pSize);  // return NULL when create fail
typedef MAE_Ret (*spectrum_effect_release)(MAE_SPECTRUM_EFFECT_INFO peffectdata);
typedef MAE_Ret (*spectrum_effect_draw)(MAE_SPECTRUM_EFFECT_INFO peffectdata, u32 nodeID, boolean bOpaque);
typedef MAE_Ret (*spectrum_effect_animation_timehandler)(void* pWidget, MAE_SPECTRUM_EFFECT_INFO peffectdata);
typedef MAE_Ret (*spectrum_effect_update_spectrum)(MAE_SPECTRUM_EFFECT_INFO peffectdata, MediaSrvSpectrumInfo_t *pSpectrumInfo);

typedef struct
{
	u32 eAnimationStyle;
    spectrum_effect_create fnCreate;     // create spectrum effect
    spectrum_effect_release fnRelease;  // release spectrum effect
    spectrum_effect_draw fnDraw;         // spectrum draw function
    spectrum_effect_animation_timehandler fnAnimation; // time handler for animation    
    spectrum_effect_update_spectrum fnSpectrum; // time handler for update spectrum
    u32 animation_timer; // time interval for animation, in ms
} SpectrumEffectEntry_t;

u32 SpectrumEffect_Total(void);

extern const SpectrumEffectEntry_t SpectrumEffect_tbl[];

#endif /* __3D_UI_MPLAYER__ */
#endif
