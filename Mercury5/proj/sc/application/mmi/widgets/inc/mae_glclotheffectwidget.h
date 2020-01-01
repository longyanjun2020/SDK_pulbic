/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mae_glclotheffectwidget.h
 *
 *
 * HISTORY
 *      2011.04.01       Evan Chang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __MAE_GLCLOTHEFFECTWIDGET_H__
#define __MAE_GLCLOTHEFFECTWIDGET_H__

#if defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_KEYGUARD_BEAUTY_CLK__)

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"
#include "mgl_Effect_ClothModeling.h"

typedef enum
{
	CLOTH_EFFECT_MOVE_TYPE_TOUCH,
	CLOTH_EFFECT_MOVE_TYPE_KEYGUARD,
	CLOTH_EFFECT_MOVE_TYPE_BCS,
} ClothMoveType_e;


typedef void (*PfnGlClothEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////

IWidget* WdgGlClothEffectCreate
(
    void
);

MAE_Ret WdgGlClothEffectRegisterEventCb
(
 IWidget                         *pGlClothEffectWdg,
 PfnGlClothEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlClothEffectDeregisterEventCb
(
 IWidget                         *pGlClothEffectWdg,
 PfnGlClothEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlClothEffectResetStatus(IWidget *pGlClothEffectWdg);

MAE_Ret WdgGlClothEffectUsingMglDraw(IWidget *pGlClothEffectWdg, boolean bUsing);

#endif /* defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_KEYGUARD_BEAUTY_CLK__) */

#endif /* __MAE_GLCLOTHEFFECTWIDGET_H__ */

/*=============================================================*/
// end of file
