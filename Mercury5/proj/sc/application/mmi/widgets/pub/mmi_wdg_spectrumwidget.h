/**
 * @file    mmi_wdg_spectrumwidget.h
 * @brief   This file defines the interface of spectrum widget
 * @version $Id: mmi_wdg_spectrumwidget.h$
 */

#ifndef __MMI_WDG_SPECTRUMWIDGET_H__
#define __MMI_WDG_SPECTRUMWIDGET_H__

#ifdef __3D_UI_MPLAYER__

#include "mmi_mae_window.h"
#include "mmi_mae_spectrum_effect.h"

enum
{
    SPECTRUM_STYLE_CIRCLE_FLIP = 0,
    SPECTRUM_STYLE_CIRCLE_SCALE = 1,
    SPECTRUM_STYLE_RECTANGLE = 2,
    SPECTRUM_STYLE_BAR = 3,
    //SPECTRUM_STYLE_CIRCLE_2 = 4,
    //SPECTRUM_STYLE_RECTANGLE_3 = 5,
    SPECTRUM_STYLE_MAX,
};
typedef u16 SpectrumWidget_Stytle_e;

IWidget* WdgSpectrumCreateForWnd
(
 HWIN                hWin,
 Pos_t               *pPos,
 WidgetSize_t        *pSize,
 u16                 nWidgetID
 );

IWidget* WdgSpectrumCreate(void);

// enable spectrum or not
MAE_INLINE MAE_Ret WdgSpectrumEnableAnim(IWidget *pSpectrum, boolean bAnim)
{
    return WdgCommonSetProperty(pSpectrum, PROP_SPECTRUM_3D_EFFECT_ANIM, (u32)bAnim);
}

// set spectrum animation type
MAE_INLINE MAE_Ret WdgSpectrumSetId(IWidget *pSpectrum, SpectrumWidget_Stytle_e eEffectId)
{
    return WdgCommonSetProperty(pSpectrum, PROP_SPECTRUM_3D_EFFECT_ID, (u32)eEffectId);
}

// set spectrum as opaque
MAE_INLINE MAE_Ret WdgSpectrumSetOpaque(IWidget *pSpectrum, boolean bOpaque)
{
    return WdgCommonSetProperty(pSpectrum, PROP_SPECTRUM_BG_OPAQUE, (u32)bOpaque);
}

#endif /* __3D_UI_MPLAYER__ */
#endif /* __MMI_WDG_SPECTRUMWIDGET_H__ */

