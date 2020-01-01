/**
 * @file    mae_glcontainer.h
 * @version $Id$
 *
 * @brief   This file defines IGLContainer interface.
 **/
 
/*
 * <Interface Description>
 *    TODO: add description
 * <Interface ID>
 *     IID_GLCONTAINER
 */

/*
 * <Class Description>
 *     TODO: add description
 *
 * <Class ID>
 *     CLSID_GLCONTAINER
 *
 * <Supported Interface>
 *     IGLContainer -> IGLContainer -> IContainer -> IWidget -> IHandler -> IBase
 *
 * <Events Handle>
 *     Handles the following events:
 *<pre>
 *     =======================
 *     EVT_WIDGET_GET_PROPERTY: To get the property from GLContainer. To see more at <Properties> 
 *                              section.
 *     =======================
 *     EVT_WIDGET_SET_PROPERTY: To set the property to GLContainer. To see more at <Properties> section.
 *     =======================
 *     EVT_WIDGET_IS_ONFOCUS
 *     =======================
 *     EVT_WIDGET_CANBEFOCUSED
 *     =======================
 *     EVT_WIDGET_SET_FOCUS
 *     =======================
 *     EVT_WIDGET_PARENT_SET_FOCUS
 *     =======================
 *     EVT_CNTNR_CHILD_SET_FOCUS
 *     =======================
 *     EVT_CNTNR_SETLAYOUT
 *     =======================
 *     EVT_CNTNR_MOVE_FOCUS
 *     =======================
 *     EVT_CNTNR_GET_FOCUS_WDG
 *     =======================
 *     EVT_WIDGET_ACTIVE
 *     =======================
 *     EVT_WIDGET_INACTIVE
 *     =======================
 *     MAE_EVT_TS_PRESS
 *     MAE_EVT_TS_RELEASE
 *     MAE_EVT_TS_MOVE
 *     MAE_EVT_TS_UP
 *     MAE_EVT_TS_DOWN
 *     MAE_EVT_TS_LEFT
 *     MAE_EVT_TS_RIGHT
 *     MAE_EVT_TS_CLICK
 *     MAE_EVT_TS_DBL_CLICK
 *     MAE_EVT_TS_LONG_PRESS: These touch events will pass into a child widget who 
 *                            is located by touch position.
 *
 *</pre>
 *
 * <Properties>
 *     Allow to set the following properties:
 *     =======================
 *     PROP_CHILD_WDG_VISIBLE
 *     =======================
 *     PROP_PADDING_SIZE
 *     =======================
 *     PROP_PADDING_LEFT
 *     =======================
 *     PROP_PADDING_RIGHT
 *     =======================
 *     PROP_PADDING_TOP
 *     =======================
 *     PROP_PADDING_BOTTOM
 *
 *     Allow to get the following properties:
 *     =======================
 *     PROP_CHILD_WDG_VISIBLE
 *
 * <View Model Event>
 *     =======================
 *     EVT_VIEWMDL_SET_WIDGET_SIZE: Widget size changed.
 *     =======================
 *     EVT_VIEWMDL_SET_MODEL: Model object in this widget changed.
 *
 * <Supported Model>
 *     None.
 *
 * <Model Data>
 *     None.
 * 
 */
#ifndef __MMI_WDG_GLCONTAINER_H__
#define __MMI_WDG_GLCONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_container.h"
#include "mmi_mae_abscontainer.h"
#include "mmi_mae_window.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// interface
/*=============================================================*/

//IGLContainer interface
#define INHERIT_IGLContainer(IName) \
	INHERIT_IAbsContainer(IName); \
	MAE_Ret (*Test) (IName *, IWidget *, const WPos_t *)

DEFINE_INTERFACE(IGLContainer);


#ifndef __MAE_VENEERED_INTERFACE__
#define IGLCONTAINER_QueryInterface(pIC,id,pp,pOwner)          GET_FUNCTBL((pIC),IGLContainer)->QueryInterface(pIC,id,pp,pOwner)
#else
MAE_INLINE MAERet_t IGLCONTAINER_QueryInterface (IGLContainer *pIC, MAEIId_t id , void** pp , IBase* pOwner)
{
	return GET_FUNCTBL((pIC),IGLContainer)->QueryInterface(pIC,id,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IGLCONTAINER_HandleEvent(pIC,e,p1,p2)					GET_FUNCTBL((pIC),IGLContainer)->HandleEvent(pIC,e,p1,p2)
#else
MAE_INLINE boolean IGLCONTAINER_HandleEvent (IGLContainer *pIC, MAEEvent_t e, u32 p1, u32 p2)
{
	return GET_FUNCTBL((pIC),IGLContainer)->HandleEvent(pIC,e,p1,p2);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IGLCONTAINER_SetHandler(pIC,pHD)						GET_FUNCTBL((pIC),IGLContainer)->SetHandler(pIC,pHD)
#else
MAE_INLINE void IGLCONTAINER_SetHandler (IGLContainer *pIC, WidgetHandler_t *pHD)
{
	GET_FUNCTBL((pIC),IGLContainer)->SetHandler(pIC,pHD);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/*=============================================================*/
// functions
/*=============================================================*/

#define IGLCONTAINER_GetTopMostWidget(p,po)       IGLCONTAINER_GetWidget(p, NULL, FALSE, FALSE, po)
#define IGLCONTAINER_GetBottomMostWidget(p,po)    IGLCONTAINER_GetWidget(p, NULL, TRUE, FALSE, po)


//pIc: a object pointer of IGLContainer
//pW: a object pointer of IWidget to add
//d: description structure
#define IGLCONTAINER_AddToTopMost(pIc,pW,d)    IGLCONTAINER_Add(pIc, pW, NULL, FALSE, d)
#define IGLCONTAINER_AddToBottomMost(pIc,pW,d) IGLCONTAINER_Add(pIc, pW, NULL, TRUE, d)


/**
* IGLCONTAINER_MoveToTop
* @brief	The function move the widget to the top of container's widget stack.
*
* @param	pIGLContainer	The pointer of IGLContainer interface object.
* @param	pIWidget		A pointer of IWidget interface object to be moved.
*
* @retval	MAE_RET_SUCCESS		Success. Moving is successful.
* @retval	MAE_RET_BAD_PARAM	Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval	MAE_RET_NOT_SUPPORTED	Failed. Some kind of container does not support.
*/
#define IGLCONTAINER_MoveToTop(pIGLContainer,pIWidget)		IGLCONTAINER_Move(pIGLContainer,pIWidget,NULL,FALSE)



/**
* IGLCONTAINER_MoveToBottom
* @brief	The function move the widget to the bottom of container's widget stack.
*
* @param	pIGLContainer		The pointer of IGLContainer interface object.
* @param	pIWidget		A pointer of IWidget interface object to be moved.
*
* @retval	MAE_RET_SUCCESS		Success. Moving is successful.
* @retval	MAE_RET_BAD_PARAM	Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval	MAE_RET_NOT_SUPPORTED	Failed. Some kind of container does not support.
*/
#define IGLCONTAINER_MoveToBottom(pIGLContainer,pIWidget)	IGLCONTAINER_Move(pIGLContainer,pIWidget,NULL,TRUE)

//interface of widget
IWidget* WdgGlContainerCreateForWnd(HWIN hWin,Pos_t *pPos,WidgetSize_t *pSize);
IWidget* WdgGlContainerCreate(void);

#endif	//__MAE_GLCONTAINER_H__
/*=============================================================*/
// end of file
