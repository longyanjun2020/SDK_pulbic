/**
* @file mmi_wdg_rootcontainer_priv.h
*
* @version $Id: mmi_wdg_rootcontainer_priv.h 20863 2009-01-19 10:59:56Z paul.ouyang $
*/
#ifndef __MAE_ROOTCONTAINER_PRIV_H__
#define __MAE_ROOTCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_wdg_rootcontainer.h"
#include "mae_containerbase.h"
#include "mae_abscontainerbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
//structure for a root-container
typedef struct {
	AbsContainerBase_t  ACntrBase;              //a base structure

	IDispCanvas     *pIDispCanvas;          //keeps a display canvas to draw
	s32             Disp_x;                 //keeps the myself coordinate
	s32             Disp_y;                 //keeps the myself coordinate
	//Rect            InvalidRect;            //invalidate rectangle coordinate to this rootcontainer
} RootContainer_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret RootContainer_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgRootContainerDefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgRootContainerConstructor(RootContainer_t *pThis);
void _WdgRootContainerDestructor(RootContainer_t *pThis);

//invalidate
void RootContainer_Invalidate(IAbsContainer *pIRootContainer, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
void RootContainer_Draw(IAbsContainer *pIRootContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);
//do layout function
void RootContainer_DoLayout(ContainerBase_t *pThis, WidgetCell_t *pWCell, Rect_t* pInvRect);

//calculate the real rectangle for invalidate
boolean RootContainer_CalcInvalidRectForWidget(ContainerBase_t *pThis, IWidget *WidgetPtr, const Rect_t *prcInWidget, u32 Flags, Rect_t *prcInvalid);

#endif //__MAE_ROOTCONTAINER_PRIV_H__
/*=============================================================*/
// end of file

