/**
* @file    mmi_wdg_glmagnifywidget.h
* @brief
* @version $Id: mmi_wdg_glmagnifywidget.h 37664 2010-02-12 09:36:01Z Lih.Wang $
*/

#ifndef __MMI_WDG_GLMAGNIFYWIDGET_H__
#define __MMI_WDG_GLMAGNIFYWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

#define GL_Magnify_FRAME_TOTAL_NO 7  //max 16
#define GL_Magnify_FRAME_STOP_NO  5
#define GL_Magnify_TIMER 5
#define GLMAGNIFYWIDGET_RADIUS 43
#define GLMAGNIFYWIDGET_MAGNIMAGE_W_H 100
#define GLMAGNIFYWIDGET_MAGNIMAGE_OFFSET (GLMAGNIFYWIDGET_MAGNIMAGE_W_H -GLMAGNIFYWIDGET_RADIUS*2)

#define GLMAGNIFYWIDGET_IBITMAP_W 512
#define GLMAGNIFYWIDGET_IBITMAP_H 512

typedef void (*PfnGlMagnifyEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////

IWidget* WdgGlMagnifyCreate
(
    void
);
MAE_Ret WdgGlMagnifyEffectRegisterEventCb
(
 IWidget                         *pGlFlipEffectWdg,
 PfnGlMagnifyEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlMagnifyEffectDeregisterEventCb
(
 IWidget                         *pGlFlipEffectWdg,
 PfnGlMagnifyEffectWdgCallBack      pfn,
 void                            *pUserData
);

#endif /* __MMI_WDG_GLMAGNIFYWIDGET_H__ */
/*=============================================================*/
// end of file
