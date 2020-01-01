/**
* @file    mmi_mmi_mae_abscontainer.h
* @version $Id: mmi_mmi_mae_abscontainer.h 38890 2009-08-29 16:22:38Z zinc.chen $
*
* @brief   This file defines IAbsContainer interface.
**/

/*
* <Interface Description>
*     IAbsContainer is an interface designed for container component which layout
*     the child widget by (x,y) coordinate. IAbsContainer inherits from IContainer. 
*     It provides two more interface methods to get/set the position of child widget.
*
* <Interface ID>
*     IID_ABSCONTAINER
*/

/*
* <Class Description>
*     AbsContainer is a container object with IAbsContainer interface. It provides
*     the functionality to layout chlid widget by (x,y) coordinate. The (x,y) coordinate 
*     is relative to the left and top position of AbsContainer object. Application can
*     create an AbsContainer by class ID CLSID_ABSCONTAINER via Shell.
*
* <Class ID>
*     CLSID_ABSCONTAINER
*
* <Supported Interface>
*     IAbsContainer -> IContainer -> IWidget -> IHandler -> IBase
*
* <Events Handle>
*     Handles the following events:
*<pre>
*     =======================
*     EVT_WIDGET_GET_PROPERTY: To get the property from AbsContainer. To see more at <Properties> 
*                              section.
*     =======================
*     EVT_WIDGET_SET_PROPERTY: To set the property to AbsContainer. To see more at <Properties> section.
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
#ifndef __MMI_MAE_ABSCONTAINER_H__
#define __MMI_MAE_ABSCONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_container.h"

/*=============================================================*/
// type and define
/*=============================================================*/

//position of a widget
//This structure is used when a widget will be set it's position in a AbsContainer
typedef struct WPos_Tag {
	boolean isVisible;
	s32 x;
	s32 y;
} WPos_t;

/*=============================================================*/
// interface
/*=============================================================*/

//IAbsContainer interface
#define INHERIT_IAbsContainer(IName) \
	INHERIT_IContainer(IName)

DEFINE_INTERFACE(IAbsContainer);

typedef void (*ABSCONTAINER_DRAW_FUNC_PTR) (IAbsContainer*, IDispCanvas*, s32, s32);

#ifndef __MAE_VENEERED_INTERFACE__
#define IABSCONTAINER_QueryInterface(pIC,id,pp,pOwner)          GET_FUNCTBL((pIC),IAbsContainer)->QueryInterface(pIC,id,pp,pOwner)
#else
__INLINE MAERet_t IABSCONTAINER_QueryInterface (IAbsContainer *pIC, MAEIId_t id , void** pp , IBase* pOwner)
{
	return GET_FUNCTBL((pIC),IAbsContainer)->QueryInterface(pIC,id,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IABSCONTAINER_HandleEvent(pIC,e,p1,p2)					GET_FUNCTBL((pIC),IAbsContainer)->HandleEvent(pIC,e,p1,p2)
#else
__INLINE boolean IABSCONTAINER_HandleEvent (IAbsContainer *pIC, MAEEvent_t e, u32 p1, u32 p2)
{
	return GET_FUNCTBL((pIC),IAbsContainer)->HandleEvent(pIC,e,p1,p2);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IABSCONTAINER_SetHandler(pIC,pHD)						GET_FUNCTBL((pIC),IAbsContainer)->SetHandler(pIC,pHD)
#else
__INLINE void IABSCONTAINER_SetHandler (IAbsContainer *pIC, WidgetHandler_t *pHD)
{
	GET_FUNCTBL((pIC),IAbsContainer)->SetHandler(pIC,pHD);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#endif	//__MAE_ABSCONTAINER_H__
/*=============================================================*/
// end of file
