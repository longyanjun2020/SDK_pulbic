/**
* @file    mmi_mae_decorator.h
* @brief   This file defines the interface of decorator.
* 
* @version $Id: mmi_mae_decorator.h 8712 2008-04-08 08:28:42Z paul.ouyang $
*/
#ifndef __MMI_MAE_DECORATOR_H__
#define __MMI_MAE_DECORATOR_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_container.h"


/*=============================================================*/
// type and define
/*=============================================================*/





/*=============================================================*/
// interface
/*=============================================================*/
#define INHERIT_IDecorator(IName) \
	INHERIT_IContainer(IName)

DEFINE_INTERFACE(IDecorator);

/// IBase interface
#define IDECORATOR_QueryInterface(pIDecorator,id,pp,pOwner) \
	GET_FUNCTBL((pIDecorator),IDecorator)->QueryInterface(pIDecorator,id,pp,pOwner)
/// IHandler interface
#define IDECORATOR_HandleEvent(pIDecorator,e,p1,p2) \
	GET_FUNCTBL((pIDecorator),IDecorator)->HandleEvent(pIDecorator,e,p1,p2)
/// IWidget interface
#define IDECORATOR_SetHandler(pIDecorator,pHD) \
	GET_FUNCTBL((pIDecorator),IDecorator)->SetHandler(pIDecorator,pHD)


/*=============================================================*/
// functions
/*=============================================================*/


#endif //__MAE_DECORATOR_H__
/*=============================================================*/
// end of file
