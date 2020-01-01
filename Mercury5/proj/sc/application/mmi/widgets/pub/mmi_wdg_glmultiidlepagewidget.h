/**
* @file    mmi_wdg_glmultiidlepagewidget.h
* @brief
* @version $Id: mmi_wdg_glmultiidlepagewidget.h 37664 2010-02-12 09:36:01Z Lih.Wang $
*/

#ifndef __MMI_WDG_GLMULTIIDLEPAGEWIDGET_H__
#define __MMI_WDG_GLMULTIIDLEPAGEWIDGET_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"


//#define MULTIIDLEPAGE_ROTATE
#define MULTIIDLEPAGE_INSERT
#define MULTIIDLEPAGE_PAGE_NUM 5

typedef void (*PfnGlMultiIdlePageEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////
// focus->draggin -> (shift) ->focus.
enum
{
    GLMULTIIDLEPAGE_FLYIN = 0,
    GLMULTIIDLEPAGE_FOCUS,
    GLMULTIIDLEPAGE_DRAGGIN,
    GLMULTIIDLEPAGE_SHIFT,
    GLMULTIIDLEPAGE_FLYOUT
};
typedef u16 GLMULTIIDLEPAGEEFFECT;


IWidget* WdgGlMultiIdlePageCreate
(
    void
);
MAE_Ret WdgGlMultiIdlePageEffectRegisterEventCb
(
 IWidget                         *pGlWdg,
 PfnGlMultiIdlePageEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlMultiIdlePageEffectDeregisterEventCb
(
 IWidget                         *pGlWdg,
 PfnGlMultiIdlePageEffectWdgCallBack      pfn,
 void                            *pUserData
);
MAE_Ret WdgGlMultiIdlePageEffectRegisterUpdateCFGEventCb
(
 IWidget                         *pGlWdg,
 PfnGlMultiIdlePageEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlMultiIdlePageEffectDeregisterUpdateCFGEventCb
(
 IWidget                         *pGlWdg,
 PfnGlMultiIdlePageEffectWdgCallBack      pfn,
 void                            *pUserData
);


#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif // __MMI_WDG_GLMULTIIDLEPAGEWIDGET_H__
/*=============================================================*/
// end of file
