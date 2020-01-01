/**
* @file    mmi_wdg_drag_priv.h
* @version $Id: mmi_wdg_drag_priv.h 2009-09-01 ken.zhou $
* @brief   This is the private header file for mmi_wdg_drag.c
*/
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
#ifndef MMI_WDG_DRAG_PRIV_H
#define MMI_WDG_DRAG_PRIV_H

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_abscontainer.h"
#include "mmi_wdg_abscontainer_priv.h"
#include "mmi_wdg_image.h"
#include "mmi_wdg_text.h"
#include "mmi_layout.h"
#include "mmi_mae_touchsrv.h"
#include "mmi_wdg_drag.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define DRAGWDG_SETDRAGMODE_TIMER 20
#define DRAGWDG_SETDRAGMODE_PHASE	4
#define DRAGWDG_TEXT_OFFSET_Y	3

///structure for a ImageText
typedef struct {
	AbsContainerBase_t AbsCntrBase;

	IWidget * pPreImgWdg;
	IWidget * pTextWdg;
	IWidget * pDownTextImageWdg;
	IModel *	pITextModel;

	IImage *	pIMainImage;
	IImage *	pFocusImage;
	IImage *	pDragImage;
	IImage *	pDonwImage;

#if 0
	IImage *	pLeftImage;
	IImage *	pRightImage;
#endif
	ModelListener_t    MdlListener;

	DRAGWDG_ANIMSTYLE_e  eAnimstyle;
	DRAGWDG_ANIM_DIRECTION_e	 eCurrentAnimDir;
	DRAGWDG_DISPLAY_STYLE_e	eCurrentStyle;
    DRAGWDG_DISPLAY_STYLE_e	ePreviousStyle;
	DRAGWDG_DOWNTEXT_STYLE_e	eDownTextStyle;

	u32	MainImgID;
	u32	LeftImgID;
	u32	RightImgID;
	u32	FocusImgID;
	u32	DragImgID;
	u32	DownTextImgID;
    u32 MaskImgID;
    u8 nAlpha;
    WidgetSize_t tDragSize;
	s8	nSetDragModePhase;
	boolean bAinamation:1;
	boolean bShowText :1;
	boolean bShowImage :1;
	boolean bDragTimerActive:1;
    boolean bEnableDragAnimatoion;
} DragWidget_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret DragWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean DragWidget_HandleEvent(IAbsContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgDragConstructor(DragWidget_t* pThis);
void 	_WdgDragDestructor(DragWidget_t* pThis);

void DragWidget_SetSize(IContainer *pIContainer, WidgetSize_t *pSize);
void DragWidget_Draw(IAbsContainer* pIContainer, IDispCanvas*pIDispCanvas, s32 x,s32  y);

MAE_Ret DragWidget_GetModel(IWidget *pIWidget, MAE_IId iId, IModel **ppObj, IBase* pOwner);
MAE_Ret DragWidget_SetModel(IAbsContainer *pIContainer, IModel *pIModel, IBase *pOwner);

static void _DragWdg_SetDragMode_TimerCB(void* pUser);
static void _DragWdg_SetDragMode(DragWidget_t *pThis, boolean bDragMode);

#endif //MMI_WDG_DRAG_PRIV_H
#endif //#ifdef __UI_STYLE_MMI_ANDROID__
/*=============================================================*/
// end of file
