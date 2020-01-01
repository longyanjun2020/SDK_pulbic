/**
* @file mae_containerbase.h
*
* @version $Id: mae_containerbase.h 34530 2009-06-26 11:03:51Z bill.pan $
*/

/*=============================================================
File name: mae_containerbase.h
Description: 
=============================================================*/
#ifndef __MAE_CONTAINERBASE_H__
#define __MAE_CONTAINERBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mae_widgetcell.h"
#include "mmi_mae_container.h"
#include "mae_widgetbase.h"
#include "mmi_mae_containerbase_type.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*CONTAINER_DRAW_FUNC_PTR) (IContainer*, IDispCanvas*, s32, s32);

//Flags
enum
{
	CNTNR_BASE_FLAG_START = WDG_BASE_FLAG_END,
	CNTNR_BASE_FLAG_ENBALE_LAYOUT = CNTNR_BASE_FLAG_START,
	CNTNR_BASE_FLAG_IS_DOINGLAYOUT,
    CNTNR_BASE_FLAG_TOUCH_FOCUS_EVENT,
    CNTNR_BASE_FLAG_LAYOUT_IS_INVERSE_BY_LANG,
	CNTNR_BASE_FLAG_END
};

//Mask for flags
//#define CONTAINER_MASK_IS_FOCUSED		(1<<WDG_BASE_FLAG_IS_FOCUSED)       ///< for flag to keep if focused
#define CONTAINER_MASK_ENABLE_LAYOUT	(1<<CNTNR_BASE_FLAG_ENBALE_LAYOUT)  ///< enable / disable do layout
#define CONTAINER_MASK_IS_DOINGLAYOUT	(1<<CNTNR_BASE_FLAG_IS_DOINGLAYOUT) ///< Is doing layout or not
#define CONTAINER_MASK_TOUCH_FOCUS_EVENT (1<<CNTNR_BASE_FLAG_TOUCH_FOCUS_EVENT) ///< enable/disable to send touch focus event
#define CONTAINER_MASK_LAYOUT_IS_INVERSE_BY_LANG (1<<CNTNR_BASE_FLAG_LAYOUT_IS_INVERSE_BY_LANG) ///< enable/disable to send touch focus event


//Get flag macro
#define CONTAINER_GET_IS_FOCUSED(_pCntrBase) \
	(boolean)(((_pCntrBase)->WdgBase.Flags&WDG_MASK_IS_FOCUSED)>>WDG_BASE_FLAG_IS_FOCUSED)
#define CONTAINER_GET_ENABLE_LAYOUT(_pCntrBase) \
	(boolean)(((_pCntrBase)->WdgBase.Flags&CONTAINER_MASK_ENABLE_LAYOUT)>>CNTNR_BASE_FLAG_ENBALE_LAYOUT)
#define CONTAINER_GET_IS_DOINGLAYOUT(_pCntrBase) \
	(boolean)(((_pCntrBase)->WdgBase.Flags&CONTAINER_MASK_IS_DOINGLAYOUT)>>CNTNR_BASE_FLAG_IS_DOINGLAYOUT)
#define CONTAINER_GET_TOUCH_FOCUS_EVENT(_pCntrBase) \
	(boolean)(((_pCntrBase)->WdgBase.Flags&CONTAINER_MASK_TOUCH_FOCUS_EVENT)>>CNTNR_BASE_FLAG_TOUCH_FOCUS_EVENT)
#define CONTAINER_GET_LAYOUT_IS_INVERSE_BY_LANG(_pCntrBase) \
    (boolean)(((_pCntrBase)->WdgBase.Flags&CONTAINER_MASK_LAYOUT_IS_INVERSE_BY_LANG)>>CNTNR_BASE_FLAG_LAYOUT_IS_INVERSE_BY_LANG)
/*deprecated
#define CONTAINER_GET_SELECTED(_pCntrBase) \
    (boolean)(((_pCntrBase)->WdgBase.Flags&WDG_MASK_SELECTED)>>WDG_BASE_FLAG_SELECTED)
*/
//Set flag macro
#define CONTAINER_SET_IS_FOCUSED(_pCntrBase, _b) \
	(_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~WDG_MASK_IS_FOCUSED))|(((u32)_b)<<WDG_BASE_FLAG_IS_FOCUSED)
#define CONTAINER_SET_ENABLE_LAYOUT(_pCntrBase, _b)	\
	(_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~CONTAINER_MASK_ENABLE_LAYOUT))|(((u32)_b)<<CNTNR_BASE_FLAG_ENBALE_LAYOUT)
#define CONTAINER_SET_IS_DOINGLAYOUT(_pCntrBase, _b) \
	(_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~CONTAINER_MASK_IS_DOINGLAYOUT))|(((u32)_b)<<CNTNR_BASE_FLAG_IS_DOINGLAYOUT)
#define CONTAINER_SET_TOUCH_FOCUS_EVENT(_pCntrBase, _b) \
    (_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~CONTAINER_MASK_TOUCH_FOCUS_EVENT))|(((u32)_b)<<CNTNR_BASE_FLAG_TOUCH_FOCUS_EVENT)
#define CONTAINER_SET_LAYOUT_IS_INVERSE_BY_LANG(_pCntrBase, _b) \
    (_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~CONTAINER_MASK_LAYOUT_IS_INVERSE_BY_LANG))|(((u32)_b)<<CNTNR_BASE_FLAG_LAYOUT_IS_INVERSE_BY_LANG)
/*deprecated
#define CONTAINER_SET_SELECTED(_pCntrBase, _b) \
    (_pCntrBase)->WdgBase.Flags = ((_pCntrBase)->WdgBase.Flags&(~WDG_MASK_SELECTED)&(~WDG_MASK_CHILD_SELECTED))|(((u32)_b)<<WDG_BASE_FLAG_SELECTED)|(((u32)_b)<<WDG_BASE_FLAG_CHILD_SELECTED)
*/

/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
//constructor for a new style Container
MAE_Ret WdgContainerBaseConstructor(ContainerBase_t *pThis, CELL_MADE_FUNC_PTR pfnCellMade,LAYOUT_FUNC_PTR pfnLayout);
//destructor for a new style Container
void WdgContainerBaseDestructor(ContainerBase_t *pContainer);

MAE_Ret ContainerBase_Ctor(ContainerBase_t *pThis,
						   const FUNCTBL(IContainer) *FtblPtr,
						   WHANDLER_HDL_FUNC_PTR pfnHandler,
						   CELL_MADE_FUNC_PTR pfnCellMade,
						   LAYOUT_FUNC_PTR pfnLayout,
						   CONTAINER_DRAW_FUNC_PTR pfnDraw);

void ContainerBase_Dtor(ContainerBase_t *pThis);


/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/
//add reference function
//=> use widgetbase
//release function
u32 ContainerBase_Release(IContainer *pIContainer);
//query interface function
MAE_Ret ContainerBase_QueryInterface(IContainer *pIContainer, MAE_IId iId, void **ppObj, IBase *pOwner);


/*------------------------------------------------------------------------------------------
* For IContainer interface
------------------------------------------------------------------------------------------*/
//add a widget to container's widget stack
MAE_Ret ContainerBase_Add(IContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isUpper, const void *DescPtr);
//remove a widget from container's widget stack
MAE_Ret ContainerBase_Delete(IContainer *pIContainer, IWidget *WidgetPtr);
//move a widget in container's widget stack
MAE_Ret ContainerBase_Move(IContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isUpper);
//get a widget from container's widget stack
IWidget *ContainerBase_GetWidget(IContainer *pIContainer, IWidget *RefWidgetPtr, boolean isUpper, boolean isWrap, IBase *pOwner);
//container's invalidate function
void    ContainerBase_Invalidate(IContainer *pIContainer, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
//locate function
MAE_Ret ContainerBase_Locate(IContainer *pIContainer, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
//RequestUp function
MAERet_t ContainerBase_RequestUp(IContainer *pIContainer, MAEEvent_t evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
//handle event function
//=> use widgetbase

//set handle event function.
//=> use widgetbase

//get size function
//=> use widgetbase
//set size
void ContainerBase_SetSize(IContainer *pIContainer, WidgetSize_t *pSize);
//get preferred size
void ContainerBase_GetPreferredSize(IContainer *pIContainer, WidgetSize_t *pSize);
//get the container's parent
//=> use widgetbase
//set the container's parent
//=> use widgetbase
//calculate the intersection
boolean ContainerBase_IntersectOpaque(IContainer *pIContainer, const Rect_t *pInRect, Rect_t *pOutRect);
//draw function of the container
void ContainerBase_Draw(IContainer *pIContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);
void ContainerBase_DefDraw(IContainer *pIContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);
//get the container's model
//=> use widgetbase
//set the container's model
//=> use widgetbase
//get the view model
//=> use widgetbase




/*------------------------------------------------------------------------------------------
* Other functions
------------------------------------------------------------------------------------------*/
//default do layout function for container base
void ContainerBase_DefDoLayout(ContainerBase_t *pThis, WidgetCell_t *pCell, Rect_t *pInvalidRect);

//when layout of the container is changed, call this function to tell this container's parent that this container is invalidate.
void ContainerBase_LayoutInvalidate(ContainerBase_t *pThis, WidgetCell_t *pWCell);

//calculate the layout rectangle by designated widget(in widget cell).
void ContainerBase_DoLayout(ContainerBase_t *pThis, WidgetCell_t *pCell, Rect_t *prc);

//find the widget cell by widget pointer
MAE_Ret ContainerBase_FindWidget(ContainerBase_t *pThis, IWidget *pWidget, WidgetCell_t **ppCell);

//delete a widget cell from widget stack
void ContainerBase_DeleteWidgetCellFromStack(ContainerBase_t *pThis, WidgetCell_t *pCell);

//get property
boolean ContainerBase_GetProperty(ContainerBase_t *pThis, u32 P1, u32 P2);

//set property
boolean ContainerBase_SetProperty(ContainerBase_t *pThis, u32 P1, u32 P2);

//this is a default event handle function
//if there is no handleevent function pointer in construction
//this function would be used as default function
boolean ContainerBase_DefHandleEvent(IContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);

//
void ContainerBase_NoticeParentSetFocus(ContainerBase_t *pThis, boolean bFocus);

boolean ContainerBase_MoveFocusWidget(ContainerBase_t *pThis, 
									  WdgFlag_t nFlag, 
									  IWidget *pIWidgetToMove);
void ContainerBase_MoveFocusWidgetCell(ContainerBase_t *pThis, 
									   WidgetCell_t *pWCellToMove);

WidgetCell_t* ContainerBase_FindTopVisibleWidgetByXYPosition(ContainerBase_t *pThis,
															 s32 x,
															 s32 y);
void ContainerBase_RemoveAllLiftingWidget(ContainerBase_t *pThis);

void ContainerBase_HandleChildSetFocus(ContainerBase_t *pThis, boolean bFocus, IWidget *pIWidget);
void ContainerBase_HandleSetFocusMechanism(ContainerBase_t *pThis, boolean bFocus);

boolean ContainerBase_SetFocus( ContainerBase_t *pThis, boolean bFocus );
boolean ContainerBase_SetChildFocus( ContainerBase_t *pThis, WidgetCell_t *pWCellToMove, boolean bFocus );

#endif //__MAE_CONTAINERBASE_H__
/*=============================================================*/
// end of file
