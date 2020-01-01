/**
* @file    mae_controllerbase.h
* @brief   This file is the header file for Controller base implementation
* 
* @version $Id: mae_controllerbase.h 19152 2008-12-25 04:38:01Z paul.ouyang $
*/


/*=============================================================
File name: mae_widgetbase.h
Description: 
=============================================================*/
#ifndef __MAE_CONTROLLERBASE_H__
#define __MAE_CONTROLLERBASE_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_controller.h"
#include "mmi_class.h"


/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	DECLARE_FUNCTBL(IController);    //function table pointer
	u32             RefCnt;             //reference count
	IWidget         *pIWidget;          //associated widget
	WidgetHandler_t   HdlData;            //a structure to keep the handle event function which is user provided.
	WHANDLER_HDL_FUNC_PTR DefHdlPtr;          //the original handle event function when this controller created.
} ControllerBase_t;


/*=============================================================*/
// functions
/*=============================================================*/
u32 ControllerBase_AddRef(IController *pIController);
u32 ControllerBase_Release(IController *pIController);
MAE_Ret ControllerBase_QueryInterface(IController *pIController, MAE_IId iId, void **ppObj, IBase *pOwner);
boolean ControllerBase_HandleEvent(IController *pIController, MAE_EventId evt, u32 P1, u32 P2);
void ControllerBase_SetHandler(IController *pIController, WidgetHandler_t *pHdlData);
u32 ControllerBase_SetWidget(IController *pIController, IWidget *pIWidget, IBase* pOwner);
boolean ControllerBase_DefHandleEvent(IController *pIController, MAE_EventId evt, u32 P1, u32 P2);
MAE_Ret ControllerBaseStrucCtor(ControllerBase_t *pThis, const FUNCTBL(IController) *FtblPtr, WHANDLER_HDL_FUNC_PTR pfnHandler);
void ControllerBaseStrucDtor(ControllerBase_t *pThis);

#endif   //__CONTROLLERBASE_H__

