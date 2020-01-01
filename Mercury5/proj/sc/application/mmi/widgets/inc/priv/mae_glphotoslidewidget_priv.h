/**
* @file 	mae_glPhotoSlidewidget_priv.h
* @brief
*
* @version $Id:$
*/
#ifndef __MAE_GLPHOTOSLIDEWIDGET_PRIV_H__
#define __MAE_GLPHOTOSLIDEWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glphotoslidewidget.h"
#include "mae_widgetbase.h"
#include "mmi_common_util.h"
#include "mgl_Core_shape.h"
#include "mmi_base_util.h"

/*=============================================================*/
// type and define
/*=============================================================*/

enum
{
	GLPHOTOSLIDE_STATE_INIT,
	GLPHOTOSLIDE_STATE_NONE,
	GLPHOTOSLIDE_STATE_ANLGN,
	GLPHOTOSLIDE_STATE_DECODEING,
};
typedef u8 GlPhotoSlide_State_e;

typedef struct
{
	WidgetBaseEx_t WdgBase;
	Vertex2D size;
	s32 nDrawX;
	s32 nDrawY;
	IADirection_e   eMoveDirection;
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;	//< Touch service
	boolean	bTouched;
	s32 	nTS_CurrentX;
	s32 	nTS_MoveX;
#endif //__TOUCH_SCREEN_MMI__

	u16     u16SceneHandleId;
	u32     nodeID;
	VectorClass_t *pCoverBmpVector;
	u32				nFocusIdx;
	u32				nCoverVecSize;
	u8				u8AlignFrameStep;
	GlPhotoSlide_State_e	eState;
	u32				nDefaultImgId;
	IWIDGET			*pBackBtnWidget;


} GlPhotoSlideWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlPhotoSlideWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlPhotoSlideWdg_Ctor(GlPhotoSlideWdg_t *pThis);
static void GlPhotoSlideWdg_Dtor(GlPhotoSlideWdg_t *pThis);
static void GlPhotoSlideWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlPhotoSlideWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlPhotoSlideWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlPhotoSlideWdg_SetProperty(GlPhotoSlideWdg_t *pThis, u32 P1, u32 P2);
boolean _GlPhotoSlideWdg_GetProperty(GlPhotoSlideWdg_t *pThis, u32 P1, u32 P2);

#endif //__MAE_GLPHOTOSLIDEWIDGET_PRIV_H__
