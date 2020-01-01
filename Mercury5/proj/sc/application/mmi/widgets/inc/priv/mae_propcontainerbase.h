/**
* @file    mae_propcontainerbase.h
* @version $Id: mae_propcontainerbase.h 11657 2008-06-14 11:51:29Z paul.ouyang $
* @brief   This is the private header file for mae_propcontainerbase.c
*/
#ifndef __MAE_PROPCONTAINERBASE_H__
#define __MAE_PROPCONTAINERBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mae_containerbase.h"
#include "mmi_mae_propcontainer.h"


/*=============================================================*/
// type and define
/*=============================================================*/
///structure for a Proportional container
typedef struct {
	ContainerBase_t    CntrBase;
	WdgLayoutStyle_t   nStyle;     //> the layout style. Vertical or Horizontal
} PropContainerBase_t;


///structure of widget cell used in PropContainer
typedef struct PropWidgetCell_Tag {
	WidgetCell_t    WCellBase;
	s16             Proportion;         //> keep the proportion of this widget
	u16             nBeforePadding;     //> padding pixels before this widget
	u16             nAfterPadding;      //> padding pixels after this widget
} PropWidgetCell_t;

/*=============================================================*/
// functions
/*=============================================================*/
__SLDPM_FREE__ boolean PropContainerBaseDefHandleEvent(IPropContainer *pIPropContainer, MAE_EventId evt, u32 P1, u32 P2);
__SLDPM_FREE__ MAE_Ret PropContainerBaseConstructor(PropContainerBase_t *pThis, LAYOUT_FUNC_PTR pfnLayout);
void PropContainerBaseDestructor(PropContainerBase_t *pThis);

MAE_Ret PropContainerBaseQueryInterface(IPropContainer *pIPropContainer, MAE_IId iId, void **ppObj, IBase *pOwner);
__SLDPM_FREE__ void PropContainerBaseInvalidate(IPropContainer *pIPropContainer, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
void PropContainerBaseGetPreferredSize(IPropContainer *pIPropContainer, WidgetSize_t *WSizePtr);

//Set the proportion of specific widget to container
MAE_Ret PropContainerBaseSetProp(IPropContainer *pIPropContainer, IWidget *WidgetPtr, const WProp_t *PropPtr);
//Get the proportion of specific widget from container
MAE_Ret PropContainerBaseGetProp(IPropContainer *pIPropContainer, IWidget *WidgetPtr, WProp_t *PropPtr);
//Set the padding of specific widget to container
MAE_Ret PropContainerBaseSetWidgetPadding(IPropContainer *pIPropContainer, IWidget *WidgetPtr, u16 nBeforePixels, u16 nAfterPixels);
//Get the padding of specific widget from container
MAE_Ret PropContainerBaseGetWidgetPadding(IPropContainer *pIPropContainer, IWidget *WidgetPtr, u16 *BeforePixelsPtr, u16 *AfterPixelsPtr);

/** PropContainerBaseAddToTopMost
* @brief        The function add a widget to top in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to add
* @param[in]    pProp       Proportion Setting to a PropContainer
*
* @retval       MAE_RET_SUCCESS       Success.
* @retval       others                Failed.
*
*/
__SLDPM_FREE__ MAE_Ret PropContainerBaseAddToTopMost(IPropContainer *pPropCntr, IWidget *pWidget, WProp_t *pProp);

/** PropContainerBaseAddToBottomMost
* @brief    The function add a widget to bottom in the PropContainer
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to add
* @param[in]    pProp       Proportion Setting to a PropContainer
*
* @retval       MAE_RET_SUCCESS        Success.
* @retval       others                 Failed.
*
*/
MAE_Ret PropContainerBaseAddToBottomMost(IPropContainer *pPropCntr, IWidget *pWidget, WProp_t *pProp);

/** PropContainerBaseMoveToTop
* @brief        The function move the widget to the top of container's widget stack
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS        Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM      Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED  Failed. Some kind of container does not support.
*
*/
MAE_Ret PropContainerBaseMoveToTop(IPropContainer *pPropCntr, IWidget *pWidget);

/** PropContainerBaseMoveToBottom
* @brief        The function move the widget to the bottom of container's widget stack
*
* @param[in]    pProCntr    The pointer of PropContainer
* @param[in]    pWidget     A pointer of IWidget interface object to be moved
*
* @retval       MAE_RET_SUCCESS         Success. Moving is successful.
* @retval       MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval       MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*
*/
MAE_Ret PropContainerBaseMoveToBottom(IPropContainer *pPropCntr, IWidget *pWidget);

#endif //__MAE_PROPCONTAINERBASE_H__
/*=============================================================*/
// end of file

