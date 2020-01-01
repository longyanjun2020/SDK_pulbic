/**
* @file    mmi_mae_propcontainer.h
* @version $Id: mmi_mae_propcontainer.h 38890 2009-08-29 16:22:38Z zinc.chen $
* @brief   This file defines the interface of IPropContainer
*/
#ifndef __MMI_MAE_PROPCONTAINER_H__
#define __MMI_MAE_PROPCONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_container.h"




/*=============================================================*/
// type and define
/*=============================================================*/

//these definitions are used for proportion
#define KEEP_WIDGET_SIZE            (0)
#define FIT_WIDGET_PREFERRED_SIZE   (-1)



///This structure is used when a widget will be set it's proportion to a PropContainer
typedef struct WProp_Tag {
	boolean isVisible;      ///> a boolean to indicate this widget is visible or not
	s16 Proportion;         ///> proportion of a container that a widget wants to occupy
} WProp_t;




/*=============================================================*/
// interface
/*=============================================================*/

//IPropContainer interface
#define INHERIT_IPropContainer(IName) \
	INHERIT_IContainer(IName)

DEFINE_INTERFACE(IPropContainer);

typedef void (*PROPCONTAINER_DRAW_FUNC_PTR) (IPropContainer*, IDispCanvas*, s32, s32);

#ifndef __MAE_VENEERED_INTERFACE__

#define IPROPCONTAINER_QueryInterface(pIC,id,ppObj,pOwner)         GET_FUNCTBL((pIC),IPropContainer)->QueryInterface(pIC,id,ppObj,pOwner)

#define IPROPCONTAINER_HandleEvent(pIC,e,p1,p2)					GET_FUNCTBL((pIC),IPropContainer)->HandleEvent(pIC,e,p1,p2)
#define IPROPCONTAINER_SetHandler(pIC,pHD)						GET_FUNCTBL((pIC),IPropContainer)->SetHandler(pIC,pHD)

#else
__INLINE MAERet_t IPROPCONTAINER_QueryInterface (IPropContainer *pIC, MAEIId_t id , void** pp , IBase* pOwner)
{
	return GET_FUNCTBL((pIC),IPropContainer)->QueryInterface(pIC,id,pp,pOwner);
}
__INLINE boolean IPROPCONTAINER_HandleEvent (IPropContainer *pIC, MAEEvent_t e, u32 p1, u32 p2)
{
	return GET_FUNCTBL((pIC),IPropContainer)->HandleEvent(pIC,e,p1,p2);
}
__INLINE void IPROPCONTAINER_SetHandler (IPropContainer *pIC, WidgetHandler_t *pHD)
{
	GET_FUNCTBL((pIC),IPropContainer)->SetHandler(pIC,pHD);
}
#endif

#endif	//__MAE_PROPCONTAINER_H__
/*=============================================================*/
// end of file
