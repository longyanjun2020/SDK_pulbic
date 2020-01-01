/**
* @file 	mmi_wdg_pick_priv.h
* @version $Id: mmi_wdg_pick_priv.h 32623 2009-06-04 14:32:32Z jason.su $
* @brief
*
*/
#ifndef __MMI_WDG_PICK_PRIV_H__
#define __MMI_WDG_PICK_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_decoratorbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DecoratorEx_t		DecBase;
	u32						nStatusFlags;
	boolean					bDirectToggle;			// accpet to receive action key to toggle item.
	IWidget					*pSclIndWdg;		///< a scroll indicator widget
	IWidget					*pHorzListWdg;		///< a horizontal list widget
	//	u16						nIndicatorWidth;	///< the width for indicator
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
} PickWidget_t;

enum
{
	PICKWDG_FLAG_START = 0,
	PICKWDG_FLAG_IS_FOCUSED = PICKWDG_FLAG_START,	///< a flag to keep if focused
	PICKWDG_FLAG_CAN_BE_FOCUSED,					///< a flag to keep if widget can be focused
	PICKWDG_FLAG_DISABLE_INVALIDATE,				///< a flag to enable / disable invalidate
	PICKWDG_FLAG_END
};

/**
* Flag Mask
*/
#define PICKWDG_MASK_IS_FOCUSED			(1<<PICKWDG_FLAG_IS_FOCUSED)
#define PICKWDG_MASK_CAN_BE_FOCUSED		(1<<PICKWDG_FLAG_CAN_BE_FOCUSED)
#define PICKWDG_MASK_DISABLE_INVALIDATE	(1<<PICKWDG_FLAG_DISABLE_INVALIDATE)
/**
* Macro to get flag value
*/
#define PICKWDG_GET_IS_FOCUSED(_pstPickWdg) \
	(boolean)(((_pstPickWdg)->nStatusFlags&PICKWDG_MASK_IS_FOCUSED)>>PICKWDG_FLAG_IS_FOCUSED)
#define PICKWDG_GET_CAN_BE_FOCUSED(_pstPickWdg) \
	(boolean)(((_pstPickWdg)->nStatusFlags&PICKWDG_MASK_CAN_BE_FOCUSED)>>PICKWDG_FLAG_CAN_BE_FOCUSED)
#define PICKWDG_GET_DISABLE_INVALIDATE(_pstPickWdg) \
	(boolean)(((_pstPickWdg)->nStatusFlags&PICKWDG_MASK_DISABLE_INVALIDATE)>>PICKWDG_FLAG_DISABLE_INVALIDATE)
/**
* Macro to set flag value
*/
#define PICKWDG_SET_IS_FOCUSED(_pstPickWdg, _b) \
	(_pstPickWdg)->nStatusFlags = ((_pstPickWdg)->nStatusFlags&(~PICKWDG_MASK_IS_FOCUSED))|(((u32)_b)<<PICKWDG_FLAG_IS_FOCUSED)
#define PICKWDG_SET_CAN_BE_FOCUSED(_pstPickWdg, _b) \
	(_pstPickWdg)->nStatusFlags = ((_pstPickWdg)->nStatusFlags&(~PICKWDG_MASK_CAN_BE_FOCUSED))|(((u32)_b)<<PICKWDG_FLAG_CAN_BE_FOCUSED)
#define PICKWDG_SET_DISABLE_INVALIDATE(_pstPickWdg, _b)	\
	(_pstPickWdg)->nStatusFlags = ((_pstPickWdg)->nStatusFlags&(~PICKWDG_MASK_DISABLE_INVALIDATE))|(((u32)_b)<<PICKWDG_FLAG_DISABLE_INVALIDATE)

// RELOAD flag
enum
{
	PICK_WDG_RELOAD_FLAG_START = 0,
	PICK_WDG_RELOAD_FLAG_LEFT_ARROWWIDTH = PICK_WDG_RELOAD_FLAG_START,   ///< left arrow width
	PICK_WDG_RELOAD_FLAG_RIGHT_ARROWWIDTH,	///< right arrow width
	PICK_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define PICK_WDG_RELOAD_MASK_LEFT_ARROWWIDTH         (1<<PICK_WDG_RELOAD_FLAG_LEFT_ARROWWIDTH)
#define PICK_WDG_RELOAD_MASK_RIGHT_ARROWWIDTH        (1<<PICK_WDG_RELOAD_FLAG_RIGHT_ARROWWIDTH)
/**
* Macro to get flag value
*/
#define PICK_WDG_LEFT_ARROWWIDTH_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&PICK_WDG_RELOAD_MASK_LEFT_ARROWWIDTH)>>PICK_WDG_RELOAD_FLAG_LEFT_ARROWWIDTH)
#define PICK_WDG_RIGHT_ARROWWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&PICK_WDG_RELOAD_MASK_RIGHT_ARROWWIDTH)>>PICK_WDG_RELOAD_FLAG_RIGHT_ARROWWIDTH)
/**
* Macro to Set flag value
*/
#define PICK_WDG_LEFT_ARROWWIDTH_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~PICK_WDG_RELOAD_MASK_LEFT_ARROWWIDTH))|(((u32)_b)<<PICK_WDG_RELOAD_FLAG_LEFT_ARROWWIDTH)
#define PICK_WDG_RIGHT_ARROWWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~PICK_WDG_RELOAD_MASK_RIGHT_ARROWWIDTH))|(((u32)_b)<<PICK_WDG_RELOAD_FLAG_RIGHT_ARROWWIDTH)

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret PickWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean PickWidget_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgPickConstructor(PickWidget_t *pThis);
void _WdgPickDestructor(PickWidget_t *pThis);
//get size
static void PickWidget_GetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
//set size
static void PickWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
//get preferred size
static void PickWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
//IntersectOpaque function
static boolean PickWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
//Draw function
static void PickWidget_Draw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
//Get model
static MAE_Ret PickWidget_GetModel(IDecorator *pIDecorator, MAE_IId iId, IModel **ppObj, IBase* pOwner);
//Set model
static MAE_Ret PickWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
//Add event listener
static MAE_Ret PickWidget_AddEvtListener(IDecorator *pIDecorator, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
//Cancel event listener
static MAE_Ret PickWidget_CancelEvtListener(IDecorator *pIDecorator, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
//get view model
static MAE_Ret PickWidget_GetViewModel(IDecorator *pIDecorator, IModel **ppObj, IBase *pOwner);
//Delete widget function
MAE_Ret PickWidget_Delete(IDecorator *pIDecorator, IWidget *WidgetPtr);
//Invalidate function
static void PickWidget_Invalidate(IDecorator *pIDecorator,
								  IWidget *WidgetPtr,
								  const Rect_t *WRectPtr,
								  InvFlag_t Flags);
//Locate function
static MAE_Ret PickWidget_Locate(IDecorator *pIDecorator, WdgContainer_WdgLocate_t *pReq);

//Get decorator child widget
static void PickWidget_GetDecWidget(IDecorator *pIDecorator, IWidget **ppChild);
//Set decorator child widget
static void PickWidget_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _PickWidget_ReloadRC(PickWidget_t *pThis, DisplayMode_e nDispMode);
#endif

#endif //__MMI_WDG_PICK_PRIV_H__
/*=============================================================*/
// end of file
