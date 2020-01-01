/**
* @file    mae_glflipeffectwidget.h
* @brief   
* @version $Id: mae_glflipeffectwidget.h 37664 2010-02-12 09:36:01Z Lih.Wang $
*/

#ifndef __MAE_GLFLIPEFFECTWIDGET_H__
#define __MAE_GLFLIPEFFECTWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

#define GL_FLIPEFFECT_TIMER 5
#define GL_FLIPEFFECT_QUICKRELEASE_THRESHOLD 100
#define GL_FLIPEFFECT_TOUCH_POS_Y 150
#define GL_FLIPEFFECT_TOUCH_MOVE_THRESHOLD 20

enum
{
    GL_FLIP_EFFECT_FLIP_OVER,
    GL_FLIP_EFFECT_FLIP_STOP,
};

typedef void (*PfnGlFlipEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////

IWidget* WdgGlFlipEffectCreate
(
    void
);

MAE_Ret WdgGlFlipEffectRegisterEventCb
(
 IWidget                         *pGlFlipEffectWdg,
 PfnGlFlipEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlFlipEffectDeregisterEventCb
(
 IWidget                         *pGlFlipEffectWdg,
 PfnGlFlipEffectWdgCallBack      pfn,
 void                            *pUserData
);


#endif /* __MAE_GLFLIPEFFECTWIDGET_H__ */
/*=============================================================*/
// end of file
