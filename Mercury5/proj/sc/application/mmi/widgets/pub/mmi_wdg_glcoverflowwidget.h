/**
 * @file    mae_glcoverflowwidget.h
 * @author  david.peng@mstarsemi.com
 * 
 * @version $Id: mae_glcoverflowwidget.h 2010-02-23 17:20:00Z alison.chen $
 *
 *
 * @brief   
 *
 */
#ifndef __MAE_GLCOVERFLOWWIDGET_H__
#define __MAE_GLCOVERFLOWWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_common_interface.h"

typedef void (*PfnGlCoverFlowEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

typedef struct
{
    IBitmap		*pCoverBmp;
	u32		u32CoverTextureId;
	u32		u32NameTextureId;
	s32			s32DisplayPosX;
	s32			s32RealPosX;
	Rect_t		rImagRect;
} GlCoverFlowItem_t;


/////////////////////////////////////////////////////////////

IWidget* WdgGlCoverFlowCreate
(
    void
);
MAE_Ret WdgGlCoverFlowEffectRegisterEventCb
(
 IWidget                         *pGlCoverFlow,
 PfnGlCoverFlowEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlCoverFlowEffectDeregisterEventCb
(
 IWidget                         *pGlCoverFlow,
 PfnGlCoverFlowEffectWdgCallBack      pfn,
 void                            *pUserData
);

#endif /*__MAE_GLCOVERFLOWWIDGET_H__ */
