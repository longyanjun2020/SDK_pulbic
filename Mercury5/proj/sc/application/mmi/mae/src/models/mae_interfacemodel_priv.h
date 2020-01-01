/**
* @file mae_interfacemodel_priv.h
* @version $Id: mae_interfacemodel_priv.h 1309 2009-07-06 14:00:16Z steve.lee $
* @brief This file defines the data structure and functions to implement a interface model.
*
*/

#ifndef __MAE_INTERFACEMODEL_PRIV_H__
#define __MAE_INTERFACEMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_modelbase.h"
#include "mmi_mae_interfacemodel.h"


/*=============================================================*/
// type and define
/*=============================================================*/
/**
* @brief   The structure for an IInterfaceModel object.
*/
typedef struct
{
	Model_t     tMdlBase;            ///< Base structure for a model.
	IBase       *pObjPtr;            ///< An IBase object pointer to keep the object.
} InterfaceModel_t;


/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/

void InterfaceModelStructCtor(InterfaceModel_t *pThis, const FUNCTBL(IInterfaceModel) *FtblPtr);
MAE_Ret InterfaceModel_New(MAE_ClsId nClsID, void **ppObj);





/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/

//Add reference => use Model_AddRef

u32 InterfaceModel_Release(IInterfaceModel *pIInterfaceModel);

MAE_Ret InterfaceModel_QueryInterface(IInterfaceModel *pIInterfaceModel, MAE_IId nIId, void **ppObj, IBase *pOwner);


/*------------------------------------------------------------------------------------------
* For IInterfaceModel interface
------------------------------------------------------------------------------------------*/

//send notify => use Model_SendNotify

//Add model listener => use Model_AddMdlListener

//cancel model listener => use Model_CancelMdlListener

void InterfaceModel_SetInterfaceObj(IInterfaceModel *pIInterfaceModel, IBase *pIObj, IBase* pOwner);

MAE_Ret InterfaceModel_GetInterfaceObj(IInterfaceModel *pIInterfaceModel, MAE_IId id, void **ppObj, IBase* pOwner);


#endif //__MAE_INTERFACEMODEL_PRIV_H__
/*=============================================================*/
// end of file
