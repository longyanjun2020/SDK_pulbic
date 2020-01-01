/**
* @file mmi_mae_modelbase.h
* @version $Id: mmi_mae_modelbase.h 1309 2009-07-06 14:00:16Z steve.lee $
* @brief This file defines the base structure of a Model object and the base function prototypes
*/

#ifndef __MMI_MAE_MODELBASE_H__
#define __MMI_MAE_MODELBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model_forward.h"
#include "mmi_mae_model.h"
/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
/**
* ModelBaseStructCtor
* @brief   To initilize model structure(Model_t).
*
* @param   pThis(Model_t*)   A pointer of structure Model_t.
* @param   pFtblPtr           Function table pointer of IModel interface.
*
* @retval  None
*/
void ModelBaseStructCtor(Model_t *pThis, const FUNCTBL(IModel) *pFtblPtr);

/**
* ModelBaseStructDtor
* @brief   A destructor for model structure(Model_t).
*
* @param   pThis(Model_t*)   A pointer of structure Model_t.
*
* @retval  None
*/
void ModelBaseStructDtor(Model_t *pThis);

/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/
/**
* ModelBase_AddRef
* @brief   This function is the implementation of add reference function in IModel interface.
*
* @param   pIModel(IModel*)   A pointer of IModel interface object.
*
* @retval  Return the reference count.
*/
u32 ModelBase_AddRef(IModel *pIModel);

/**
* ModelBase_Release
* @brief   This function is the implementation of release function in IModel interface.
*
* @param   pIModel(IModel*)   A pointer of IModel interface object.
*
* @retval  Return the reference count.
*/
u32 ModelBase_Release(IModel *pIModel);

/**
* ModelBase_QueryInterface
* @brief   This function is the implementation of query interface function in IModel interface.
*
* @param   pIModel(IModel*)   A pointer of IModel interface object.
* @param   nIId(MAE_IId)       An interface id to be queried.
* @param   ppObj(void**)      A pointer of void pointer to retrieve an interface object which you want to query.
* @param   pOwner(IBase*)     Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS      Success.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*
* @note    Only supports IID_MODEL to query.
*/
MAE_Ret ModelBase_QueryInterface(IModel *pIModel, MAE_IId nIId, void **ppObj, IBase *pOwner);

/*------------------------------------------------------------------------------------------
* For IModel interface
------------------------------------------------------------------------------------------*/
/**
* ModelBase_SendNotify
* @brief   This function is the implementation of send notify function in IModel interface.
*
* @param   pIModel(IModel*)          A pointer of IModel interface object.
* @param   EventPtr(ModelEvent_t*)   A pointer to ModelEvent_t sturcture to indicate which event occured
*                                    and what kind of data is changed.
*
* @retval  None.
*
* @note    This function sends the notify to all listeners which registered to this model.
*          nEvtCode and dwParam in parameter EventPtr were filled before calling this function.
*          This function will fill the field pThisModel and then send EventPtr to listener callback.
*/
void ModelBase_SendNotify(IModel *pIModel, ModelEvent_t *EventPtr);

/**
* ModelBase_SendEvtNotify
* @brief   This function is the implementation of send notify function in IModel interface.
*
* @param   pIModel(IModel*)          A pointer of IModel interface object.
* @param   EventPtr(ModelEvent_t*)   A pointer to ModelEvent_t sturcture to indicate which event occured
*                                    and what kind of data is changed.
*
* @retval  None.
*
* @note    This function sends the notify to all listeners which registered to this model.
*          nEvtCode and dwParam in parameter EventPtr were filled before calling this function.
*          This function will fill the field pThisModel and then send EventPtr to listener callback.
*/
boolean ModelBase_SendEvtNotify(IModel *pIModel, ModelEvent_t *EventPtr);


/**
* ModelBase_AddMdlListener
* @brief   This function is the implementation of add model listener function in IModel interface.
*
* @param   pIModel(IModel*)              A pointer of IModel interface object.
* @param   pMdlLsnPtr(ModelListener_t*)   A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS    Success.
* @retval  MAE_RET_BAD_PARAM   Invalid paramater.
*
* @note    The listener structure will add at the root of link-list.
*<pre>
*                       +----+   +----+   +----+
*          Link-list -->|root|-->|    |-->|    |--||
*                       +----+   +----+   +----+
*          the most new one                    the most old one.
*</pre>
*/
MAE_Ret ModelBase_AddMdlListener(IModel *pIModel, ModelListener_t *pMdlLsnPtr);

/**
* ModelBase_CancelMdlListener
* @brief   This function is the implementation of cancel model listener function in IModel interface.
*          Remove the Model Listener structure from the link-list.
*
* @param   pIModel(IModel*)                 A pointer of IModel interface object.
* @param   pLsnToCancel(ModelListener_t*)   A pointer to ModelListener_t sturcture to cancel.
*
* @retval  MAE_RET_SUCCESS    Success.
* @retval  MAE_RET_BAD_PARAM   Invalid paramater.
* @retval  MAE_RET_FAILED     The specific listener does not belong to this model object.
*
*/
MAE_Ret ModelBase_CancelMdlListener(IModel *pIModel, ModelListener_t *pMdlLsnPtr);

MAE_Ret ModelBase_AddEvtListener(IModel *pIModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtListener, void *pUsrData);
MAE_Ret ModelBase_CancelEvtListener(IModel *pIModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtListener, void *pUsrData);
MAE_Ret ModelBase_CancelEvtAllListener(IModel *pIModel, ModelEvtCode_t nEvtCode);

#endif //__MAE_MODELBASE_H__
/*=============================================================*/
// end of file
