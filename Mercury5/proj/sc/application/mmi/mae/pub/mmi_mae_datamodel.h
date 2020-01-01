/**
* @file    mmi_mae_datamodel.h
* @version $Id: mmi_mae_datamodel.h 1684 2009-08-29 16:28:08Z zinc.chen $
*
* @brief   This file defines the IDataModel interface.
*
* <Interface Description>
*     IDataModel inherits from IModel and provides a mechanism to set/get data to/from the
*     data-model. IDataModel also provides adapt-set/adapt-get functionalities to convert data.
*     User can set an adapt-set function, and convert the data when the data really set to the
*     IDataModel interface object. Similarly, user can set an adapt-get function, and the data
*     would be converted when someone wants to get data from this IDataModel inerface object.
*     User should set a function to free the data in data-model. While the data-model released
*     or while the data changed by IDATAMODEL_SetData(), the free function will execute.
*     User can set any data to IDataModel model. Actually, IDataModel model only keeps a value,
*     the value could be an address of structure, an address of object , or just a value.
*
* <Interface ID>
*     IID_DATAMODEL
*
* <Model Notification Event>
*     =======================
*     EVT_MDL_DATA_CHANGE: While the data kept in this data-model has changed, model event notifies
*                          this event code.
*
* <Class Description>
*     The CLSID_DATAMODEL class implements IDataModel interface. User can create a CLSID_DATAMODEL
*     class object via MAE_Shell by ISHELL_CreateInstance().
*
* <Class ID>
*     CLSID_DATAMODEL
*/
#ifndef __MMI_MAE_DATAMODEL_H__
#define __MMI_MAE_DATAMODEL_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/**
* Adapt-Set function prototype
* @brief   The callback function prototype for adapt-set function
*
* @param   void *pCtxData(In)                  A context data pointer.
* @param   void *pDataIn(In)                   A pointer of input data.
* @param   s32 nLenIn(In)                      The length of input data.
* @param   void **ppDataOut(Out)               A pointer of void pointer to retrieve output data.
* @param   s32 *pLenOut(Out)                  A pointer of s32 to retrieve output data length.
* @param   PfnModelFree *pfnFreeFunc(Out) A pointer of free function pointer to retrieve a free function
which will be used to free output data.
* @param   IBase **ppOwner(Out)                A pointer of IBase pointer to retrieve the owner of output data.
*/
typedef void (*PfnAdaptSet) (void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pLenOut, PfnModelFree *pfnFreeFunc, IBase **ppOwner);

/**
* Adapt-Get function prototype
* @brief   The callback function prototype for adapt-get function
*
* @param   void *pCtxData(In)                  A context data pointer.
* @param   void *pDataIn(In)                   A pointer of input data.
* @param   s32 nLenIn(In)                      The length of input data.
* @param   void **ppDataOut(Out)               A pointer of void pointer to retrieve output data.
* @param   s32 *pLenOut(Out)                  A pointer of s32 to retrieve output data length.
*/
typedef void (*PfnAdaptGet) (void *pCtxData, void *pDataIn, s32 nLenIn, void **ppDataOut, s32 *pLenOut);

/*=============================================================*/
// interface
/*=============================================================*/
/**
* INHERIT_IDataModel
* @brief   INHERIT_IDataModel is IDataModel interface inheritance definition.
*/
#define INHERIT_IDataModel(IName) \
	INHERIT_IModel(IName); \
	void     (*SetData)    (IName *, void *, s32, u32, PfnModelFree, IBase *);\
	void *   (*GetData)    (IName *, s32 *); \
	void     (*SetAdaptSet)   (IName *, PfnAdaptSet, void*); \
	void     (*SetAdaptGet)   (IName *, PfnAdaptGet, void*)

//Here define IDataModel interface
DEFINE_INTERFACE(IDataModel);



/*=============================================================*/
// methods of IDataModel
/*=============================================================*/

/**
* IDATAMODEL_QueryInterface
* @brief	This function queries another interface from an IDataModel object.
*          It will return an interface object which you want to query if successful.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (MAE_IId)nId                     An interface nId to be queried.
* @param   (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
* @param   (IBase*)pOwner                  Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface nId is not supported.
*
* @note    Only support IID_DATAMODEL and IID_MODEL.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_QueryInterface(pIDataModel,nId,pp,pOwner) \
	GET_FUNCTBL((pIDataModel),IDataModel)->QueryInterface(pIDataModel,nId,pp,pOwner)
#else

__INLINE MAERet_t IDATAMODEL_QueryInterface (IDataModel *pIDataModel, MAEIId_t nId, void** pp, IBase* pOwner)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->QueryInterface(pIDataModel,nId,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IDATAMODEL_SendNotify
* @brief   This function sends the notify to all listeners which registered to this model.
*          An application or object could register listener by IMODEL_AddMdlListener()/IDATAMODEL_AddMdlListener()
*          to a specific model. When the model state is changed(such as data changed), the
*          model would notify all listeners by IMODEL_SendNotify()/IDATAMODEL_SendNotify().
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (ModelEvent_t*)pMdlEvt          A pointer to ModelEvent_t sturcture to indicate which event is
*                                          occured and what kind of data is changed.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_SendNotify(pIDataModel,pMdlEvt) \
	GET_FUNCTBL((pIDataModel),IDataModel)->SendNotify(pIDataModel,pMdlEvt)
#else
__INLINE void IDATAMODEL_SendNotify(IDataModel *pIDataModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIDataModel),IDataModel)->SendNotify(pIDataModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IDATAMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (ModelListener_t*)pMdlLsn       A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_AddMdlListener(pIDataModel,pMdlLsn) \
	GET_FUNCTBL((pIDataModel),IDataModel)->AddMdlListener(pIDataModel,pMdlLsn)
#else
__INLINE MAE_Ret IDATAMODEL_AddMdlListener(IDataModel *pIDataModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->AddMdlListener(pIDataModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_AddEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIDataModel),IDataModel)->AddEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IDATAMODEL_AddEvtListener(IDataModel *pIDataModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->AddEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IDATAMODEL_CancelMdlListener
* @brief   This function cancels a registered listener from this model object.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (ModelListener_t*)pMdlLsn       A pointer to ModelListener_t sturcture that was registered to
*                                          this model object and want to cancel it.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_FAILED      Failed. The specific listener does not belong to this model object.
*/
/*
#define IDATAMODEL_CancelMdlListener(pIDataModel,pMdlLsn) \
GET_FUNCTBL((pIDataModel),IDataModel)->CancelMdlListener(pIDataModel,pMdlLsn)
 use MDLLISTENER_CANCEL() instead 
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_CancelEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIDataModel),IDataModel)->CancelEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IDATAMODEL_CancelEvtListener(IDataModel *pIDataModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->CancelEvtListener(pIDataModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_CancelEvtAllListener(pIDataModel,nEvtCode) \
	GET_FUNCTBL((pIDataModel),IDataModel)->CancelEvtAllListener(pIDataModel,nEvtCode)
#else
__INLINE MAE_Ret IDATAMODEL_CancelEvtAllListener(IDataModel *pIDataModel, ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->CancelEvtAllListener(pIDataModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IDATAMODEL_SetData
* @brief   This function provides a functionality to set a pointer of data into this datamodel.
*          Datamodel object also keeps the length of data, a free function pointer and the data owner object instance.
*          The data will be freed or released, by calling free function, when the datamodel is released or
*          when a new pointer of data is set into this datamodel.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (void*)pData					A void pointer of data which want to be set into datamodel.
* @param   (s32)nLen                       The length of data.
* @param   (PfnModelFree)pfnFree      A free function pointer to free data.
* @param   (IBase*)pOwner                  A IBase pointer to indicate who is the owner of data.
*
* @retval  None
*
* @note    This function will cause sending EVT_MDL_DATA_CHANGE notification.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_SetData(pIDataModel,pData,nLen,pfnFree,pOwner) \
	GET_FUNCTBL((pIDataModel),IDataModel)->SetData(pIDataModel, pData, nLen, 0, pfnFree,pOwner)

#define IDATAMODEL_SetDataEx(pIDataModel,pData,nLen,nEvtParam,pfnFree,pOwner) \
	GET_FUNCTBL((pIDataModel),IDataModel)->SetData(pIDataModel, pData, nLen, nEvtParam, pfnFree, pOwner)

#else
#define IDATAMODEL_SetData(pIDataModel,pData,nLen,pfnFree,pOwner) \
	IDATAMODEL_SetDataEx(pIDataModel, pData, nLen, 0, pfnFree,pOwner)
__INLINE void IDATAMODEL_SetDataEx(IDataModel *pIDataModel, void *pData, s32 nLen, u32 nEvtParam, PfnModelFree pfnFree, IBase *pOwner)
{
	GET_FUNCTBL((pIDataModel),IDataModel)->SetData(pIDataModel, pData, nLen, nEvtParam, pfnFree, pOwner);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IDATAMODEL_GetData
* @brief   This function can retrieve a pointer of data which keeps in this datamodel.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (s32*)pLen                     A pointer of s32 to retrieve the length of data.
*                                          Could be NULL if do not want to know the length.
*
* @retval  void*       Returns the pointer of data which keeps in this datamodel.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_GetData(pIDataModel,pLen) \
	GET_FUNCTBL((pIDataModel),IDataModel)->GetData(pIDataModel, pLen)
#else
__INLINE void* IDATAMODEL_GetData(IDataModel *pIDataModel, s32 *pLen)
{
	return GET_FUNCTBL((pIDataModel),IDataModel)->GetData(pIDataModel, pLen);
}

#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IDATAMODEL_SetAdaptSetFunc
* @brief   This function can set an adapt-Set function to the datamodel. Adapt-Set will occur
*          only if an adapt-set function is already set to the datamodel and IDATAMODEL_SetData() executes.
*<pre>
*          +----+                      +---------+    +----+          +-----+
*          |Data| IDATAMODEL_SetData() |Adapt-Set|    |Data| set into |Data |
*          |A   |--------------------->|Func.    |--->|B   |--------->|Model|
*          +----+                      +---------+    +----+          +-----+
*</pre>
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (ADAPT_SET_FUNC_PTR)pfnAdaptSet          A ADAPT_SET_FUNC_PTR function pointer to set to this data model.
*                                          Adapt-Set function will be called if IDATAMODEL_SetData() is occured.
* @param   (void*)pCtx                     A context data pointer which will pass into Adapt-Set function.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_SetAdaptSetFunc(pIDataModel, pfnAdaptSet, pCtx) \
	GET_FUNCTBL((pIDataModel),IDataModel)->SetAdaptSet(pIDataModel, pfnAdaptSet, pCtx)

#else
__INLINE void IDATAMODEL_SetAdaptSetFunc(IDataModel *pIDataModel, PfnAdaptSet pfnAdaptSet, void* pCtx)
{
	GET_FUNCTBL((pIDataModel),IDataModel)->SetAdaptSet(pIDataModel, pfnAdaptSet, pCtx);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IDATAMODEL_SetAdaptGetFunc
* @brief   This function can set an adapt-Get function to the datamodel. Adapt-Get will occur
*          only if an adapt-get function is already set to the datamodel and IDATAMODEL_GetData() executes.
*<pre>
*          +------------+                      +---------+    +----+
*          |Data A      | IDATAMODEL_GetData() |Adapt-Get|    |Data|
*          |in datamodel|--------------------->|Func.    |--->|B   |
*          +------------+                      +---------+    +----+
*</pre>
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (ADAPT_GET_FUNC_PTR)pfnAdaptSet          A ADAPT_GET_FUNC_PTR function pointer to set to this data model.
*                                          Adapt-Get function will be called if IDATAMODEL_GetData() is occured.
* @param   (void*)pCtx                     A context data pointer which will pass into Adapt-Get function.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IDATAMODEL_SetAdaptGetFunc(pIDataModel, pfnAdaptGet, pCtx) \
	GET_FUNCTBL((pIDataModel),IDataModel)->SetAdaptGet(pIDataModel, pfnAdaptGet, pCtx)
#else
__INLINE void IDATAMODEL_SetAdaptGetFunc(IDataModel *pIDataModel, PfnAdaptGet pfnAdaptGet, void* pCtx)
{
	GET_FUNCTBL((pIDataModel),IDataModel)->SetAdaptGet(pIDataModel, pfnAdaptGet, pCtx);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/*=============================================================*/
// helper functions
/*=============================================================*/
/**
* IDATAMODEL_SetBool
* @brief   This function helps Application to set a boolean value to a IDataModel object easily.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
* @param   (boolean)bValue                 A boolean value to set.
*
* @retval  None.
*/
__INLINE void IDATAMODEL_SetBool(IDataModel *pIDataModel, boolean bValue)
{
	if (!pIDataModel)
	{
		return;
	}
	IDATAMODEL_SetData(pIDataModel, (*((void**)&bValue)), 0, NULL, NULL);
}


/**
* IDATAMODEL_GetBool
* @brief   This function helps Application to get a boolean value from a IDataModel object easily.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
*
* @retval  A boolean value.(TRUE/FALSE)
*/
__INLINE boolean IDATAMODEL_GetBool(IDataModel *pIDataModel)
{
	void *pData = NULL;
	if (!pIDataModel)
	{
		return FALSE;
	}
	pData = IDATAMODEL_GetData(pIDataModel, NULL);
	return (*((boolean *)&pData));
}


/**
* IDATAMODEL_NotifyDataChanged
* @brief   This function is an easy way to help application send EVT_MDL_DATA_CHANGE
*          notification of IDataModel object.
*
* @param   (IDataModel*)pIDataModel        A pointer of IDataModel interface object.
*
* @retval  None.
*/
__INLINE void IDATAMODEL_NotifyDataChanged(IDataModel *pIDataModel)
{
	ModelEvent_t stMdlEvt = {0};
	MDLEVENT_INIT(&stMdlEvt, EVT_MDL_DATA_CHANGE, 0);
	IDATAMODEL_SendNotify(pIDataModel, &stMdlEvt);
}


#endif //__MAE_DATAMODEL_H__
/*=============================================================*/
// end of file
