/**
* @file    mmi_mae_controller.h
* @brief   This file is the collection of widget property definitions.
* 
* @version $Id: mmi_mae_controller.h 8741 2008-04-08 13:22:30Z paul.ouyang $
*/
#ifndef __MMI_MAE_CONTROLLER_H__
#define __MMI_MAE_CONTROLLER_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// interface
/*=============================================================*/
///
/// IController interface
///
/// Although IController is derived from IHandler, it is not directly handled by Shell as IApplet or
/// IService and is not considered as an individual execution unit. The HandleEvent method is
/// controlled by View, which passes the events of an applet to the specific widget's handler.
///
/// methods of IController interface
#define INHERIT_IController(IName) \
	INHERIT_IHandler(IName); \
	void (*SetHandler) (IName*, WidgetHandler_t*); \
	MAE_Ret      (*SetWidget)   (IName *, IWidget *, IBase *)


DEFINE_INTERFACE(IController);



#define ICONTROLLER_QueryInterface(pICtlr,id,pp,pOwner)	GET_FUNCTBL((pICtlr),IController)->QueryInterface(pICtlr,id,pp,pOwner)
#define ICONTROLLER_HandleEvent(pICtlr,e,p1,p2)			GET_FUNCTBL((pICtlr),IController)->HandleEvent(pICtlr,e,p1,p2)
#define ICONTROLLER_SetHandler(pICtlr,pHd)				GET_FUNCTBL((pICtlr),IController)->SetHandler(pICtlr,pHd)
#define ICONTROLLER_SetWidget(pICtlr,pW,pOwner)			GET_FUNCTBL((pICtlr),IController)->SetWidget(pICtlr,pW,pOwner)



/*=============================================================*/
// functions
/*=============================================================*/


#endif	//__MAE_CONTROLLER_H__
/*=============================================================*/
// end of file
