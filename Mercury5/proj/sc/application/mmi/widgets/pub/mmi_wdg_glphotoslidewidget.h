/**
* @file    mae_glphotoslidewidget.h
* @author  Jason-JS.Lin@mstarsemi.com
*
* @version $Id: mae_glphotoslidewidget.h 2011-12-26 17:20:00Z Jason-JS.Lin $
*
*
* @brief
*
*/
#ifndef __MAE_GLPHOTOSLIDEWIDGET_H__
#define __MAE_GLPHOTOSLIDEWIDGET_H__

#if defined(__FEATURE_MGL__)

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widget.h"
#include "mmi_wdg_common_interface.h"
#include "mgl_Utility_common.h"

typedef void (*PfnGlPhotoSlideEffectWdgCallBack) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

typedef struct
{
	IImage		*pImage;
	IBitmap		*pCoverBmp;
	mgl_u32		u32CoverTextureId;
	u32         uFileIndex;
	Rect_t		rImagRect;
} GlPhotoSlideItem_t;


/////////////////////////////////////////////////////////////

IWidget* WdgGlPhotoSlideCreate
(
 void
 );
MAE_Ret WdgGlPhotoSlideEffectRegisterEventCb
(
 IWidget                         *pGlPhotoSlide,
 PfnGlPhotoSlideEffectWdgCallBack      pfn,
 void                            *pUserData
 );

MAE_Ret WdgGlPhotoSlideEffectDeregisterEventCb
(
 IWidget                         *pGlPhotoSlide,
 PfnGlPhotoSlideEffectWdgCallBack      pfn,
 void                            *pUserData
 );

#endif /* __FEATURE_MGL__ */
#endif /*__MAE_GLPHOTOSLIDEWIDGET_H__ */
