/**
* @file    mmi_wdg_glAlbumSlidewidget.h
* @brief
* @version $Id: mmi_wdg_glAlbumSlidewidget.h 37664 2010-02-12 09:36:01Z Lih.Wang $
*/

#ifndef __MMI_WDG_GLALBUMSLIDEWIDGET_H__
#define __MMI_WDG_GLALBUMSLIDEWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

typedef void (*PfnGlAlbumSlideEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/////////////////////////////////////////////////////////////

IWidget* WdgGlAlbumSlideCreate
(
    void
);
MAE_Ret WdgGlAlbumSlideEffectRegisterEventCb
(
 IWidget                         *pGlAlbumSlide,
 PfnGlAlbumSlideEffectWdgCallBack      pfn,
 void                            *pUserData
);

MAE_Ret WdgGlAlbumSlideEffectDeregisterEventCb
(
 IWidget                         *pGlAlbumSlide,
 PfnGlAlbumSlideEffectWdgCallBack      pfn,
 void                            *pUserData
);

#endif /* __MMI_WDG_GLALBUMSLIDEWIDGET_H__ */
/*=============================================================*/
// end of file
