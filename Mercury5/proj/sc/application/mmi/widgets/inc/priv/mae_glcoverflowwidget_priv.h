/**
* @file 	mae_glCoverFlowwidget_priv.h
* @brief
*
* @version $Id:$
*/
#ifndef __MAE_GLCOVERFLOWWIDGET_PRIV_H__
#define __MAE_GLCOVERFLOWWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glcoverflowwidget.h"
#include "mae_widgetbase.h"
#include "mmi_common_util.h"
#include "mgl_Core_shape.h"
#include "mmi_base_util.h"

/*=============================================================*/
// type and define
/*=============================================================*/

enum
{
	GLCOVERFLOW_ANIM_SLIDE,
	GLCOVERFLOW_ANIM_ANLGN,
	GLCOVERFLOW_ANIM_NONE,
};
typedef u8 GlCoverFlow_Anim_e;

typedef struct
{
	WidgetBaseEx_t WdgBase;
	s32 nDrawX;
	s32 nDrawY;
	Vertex2D size;
	boolean	bTouched;
	s32 	nTS_MoveX;
#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;	//< Touch service
	s32 	nTS_CurrentX;
#endif //__TOUCH_SCREEN_MMI__


	u16     u16SceneHandleId;
	u32     nodeID;
	VectorClass_t *pCoverBmpVector;
	mgl_float         nCurFrameIdx;
	u32				nFocusIdx;
	u32				nCoverVecSize;
	s32				nTouchOffsetX;
	u8				u8AlignFrameStep;
	s32				nAlignStartPosX;
	GlCoverFlow_Anim_e	eAnimState;
	u32				nNameDisplayIdx;
	u32				nDefaultImgId;
	u32             nNameBmpWidth;
	u32             nNameBmpHeight;
	IWidget			*pNameTxtWdg;

} GlCoverFlowWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlCoverFlowWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlCoverFlowWdg_Ctor(GlCoverFlowWdg_t *pThis);
static void GlCoverFlowWdg_Dtor(GlCoverFlowWdg_t *pThis);
static void GlCoverFlowWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlCoverFlowWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlCoverFlowWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlCoverFlowWdg_SetProperty(GlCoverFlowWdg_t *pThis, u32 P1, u32 P2);
boolean _GlCoverFlowWdg_GetProperty(GlCoverFlowWdg_t *pThis, u32 P1, u32 P2);

#endif //__MAE_GLCOVERFLOWWIDGET_PRIV_H__
