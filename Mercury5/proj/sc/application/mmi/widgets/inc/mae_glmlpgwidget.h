/**
* @file    mae_glmlpgwidget.h
* @brief
* @version $Id: mae_glmlpgwidget.h $
*/

#ifndef __MAE_GLMLPGWIDGET_H__
#define __MAE_GLMLPGWIDGET_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widget.h"
#include "mmi_wdg_common_interface.h"


IWidget* WdgGlMlpgCreate(void);
MAE_Ret WdgGlMlpgRegEventCb(IWidget *pGlEffectWdg, PFN_WIDGET_EVT_LISTENER pfn,void *pUserData);
MAE_Ret WdgGlMlpgDeregEventCb(IWidget *pGlEffectWdg, PFN_WIDGET_EVT_LISTENER pfn,void *pUserData);

#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif // __MAE_GLMLPGWIDGET_H__
/*=============================================================*/
// end of file
