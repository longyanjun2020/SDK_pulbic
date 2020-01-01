/**
* @file 	mmi_wdg_sheetcontainer_priv.h
* @brief   Sheet Container
* @version $Id: mmi_wdg_sheetcontainer_priv.h 8963 2008-04-11 05:10:25Z steve.lee $
*/
#ifndef __MMI_WDG_SHEETCONTAINER_PRIV_H__
#define __MMI_WDG_SHEETCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_sheetcontainer.h"
#include "mae_containerbase.h"
#include "mae_wdgbackground.h"


/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	ContainerBase_t     CntrBase;           ///< Use this as a base structure.
	ModelListener_t     ViewMdlLsn;         ///< model listener parent view model
	s32                 nFocusIdx;          ///< A zero-base index to keep focused index.
	boolean             bEnableSlide;
	u32                 nTotalStep;         //should not be zero
	u32                 nSlideStep;
	s32                 nStepTime;          //in msec.
	PfnMAE_Notify       pfnTimerCB;
	WidgetCell_t        *pLastWCell;
	boolean             bDirToRight;
} SheetContainer_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret SheetContainer_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean SheetContainer_DefHandleEvent(IContainer *pISheetContainer, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgSheetContainerConstructor(SheetContainer_t *pThis);
void _WdgSheetContainerDestructor(SheetContainer_t *pThis);
boolean SheetContainer_IntersectOpaque(IContainer *pISheetContainer, const Rect_t * pInRect, Rect_t * pOutRect);
MAERet_t SheetContainer_SetModel(IContainer *pISheetContainer, IModel *pIModel, IBase* pOwner);
__SLDPM_FREE__ void SheetContainer_Invalidate(IContainer *pISheetContainer,
							   IWidget *WidgetPtr, 
							   const Rect_t *WRectPtr, 
							   InvFlag_t Flags);
#endif //__MMI_WDG_SHEETCONTAINER_PRIV_H__
/*=============================================================*/
// end of file
