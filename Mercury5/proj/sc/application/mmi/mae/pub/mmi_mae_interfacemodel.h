/**
* @file    mmi_mae_interfacemodel.h
* @version $Id: mmi_mae_interfacemodel.h 1684 2009-08-29 16:28:08Z zinc.chen $
*
* @brief   This file defines the IInterfaceModel interface.
*
* <Interface Description>
*     IInterfaceModel inherts from IModel and provides a mechanism to set/get an object to/from
*     IInterfaceModel model. IInterfaceModel object is a kind of data container. Application ONLY
*     could set interface object data to IInterfaceModel model. Application can set an object to
*     IInterfaceModel model by IINTERFACEMODEL_SetInterfaceObj(). Application can get an object
*     from IInterfaceModel model by IINTERFACEMODEL_GetInterfaceObj(). While setting an object to
*     this kind model, It will add the reference count of the object. And the object will be
*     released while this IInterfaceModel model released.
*
* <Interface ID>
*     IID_INTERFACEMODEL
*
* <Model Notification Event>
*     =======================
*     EVT_MDL_INTERFACE_CHANGE: While the object kept in interface-model has changed, it notifies
*                               this event code.
*
* <Class Description>
*     The CLSID_INTERFACEMODEL class implements IInterfaceModel interface. User can create a
*     CLSID_INTERFACEMODEL class object via MAE_Shell by ISHELL_CreateInstance(). And then,
*     application can use all IInterfaceModel interface methods with this object.
*
* <Class ID>
* CLSID_INTERFACEMODEL
*/
#ifndef __MMI_MAE_INTERFACEMODEL_H__
#define __MMI_MAE_INTERFACEMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// interface
/*=============================================================*/
/**
* INHERIT_IInterfaceModel
* @brief   INHERIT_IInterfaceModel is IInterfaceModel interface inheritance definition.
*/
#define INHERIT_IInterfaceModel(IName) \
	INHERIT_IModel(IName); \
	void        (*SetInterfaceObj) (IName *, IBase *, IBase*);\
	MAE_Ret     (*GetInterfaceObj) (IName *, MAE_IId, void**, IBase*)

//Here define IInterfaceModel interface
DEFINE_INTERFACE(IInterfaceModel);


/*=============================================================*/
// functions
/*=============================================================*/

/**
* IINTERFACEMODEL_QueryInterface
* @brief	This function queries another interface from an IInterfaceModel object.
*          It will return an interface object which you want to query if successful.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (MAE_IId)nId                     An interface nId to be queried.
* @param   (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
* @param   (IBase*)pOwner                  Shall be an IBase interface object to keep the returned object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface nId is not supported.
*
* @note    Only support IID_INTERFACEMODEL and IID_MODEL.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_QueryInterface(pIInterfaceModel,nId,pp,pOwner) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->QueryInterface(pIInterfaceModel,nId,pp,pOwner)
#else
__INLINE MAERet_t IINTERFACEMODEL_QueryInterface (IInterfaceModel *pIInterfaceModel, MAEIId_t nId, void** pp, IBase* pOwner)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->QueryInterface(pIInterfaceModel,nId,pp,pOwner);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IINTERFACEMODEL_SendNotify
* @brief   This function sends the notify to all listeners which registered to this model.
*          An application or object could register listener by IMODEL_AddMdlListener()/IINTERFACEMODEL_AddMdlListener()
*          to a specific model. When the model state is changed(such as data changed), the
*          model would notify all listeners by IMODEL_SendNotify()/IINTERFACEMODEL_SendNotify().
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (ModelEvent_t*)pMdlEvt              A pointer to ModelEvent_t sturcture to indicate which event is
*                                              occured and what kind of data is changed.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_SendNotify(pIInterfaceModel,pMdlEvt) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->SendNotify(pIInterfaceModel,pMdlEvt)
#else
__INLINE void IINTERFACEMODEL_SendNotify(IInterfaceModel *pIInterfaceModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->SendNotify(pIInterfaceModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IINTERFACEMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (ModelListener_t*)pMdlLsn           A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_AddMdlListener(pIInterfaceModel,pMdlLsn) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->AddMdlListener(pIInterfaceModel,pMdlLsn)
#else
__INLINE MAE_Ret IINTERFACEMODEL_AddMdlListener(IInterfaceModel *pIInterfaceModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->AddMdlListener(pIInterfaceModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_AddEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->AddEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IINTERFACEMODEL_AddEvtListener(IInterfaceModel *pIInterfaceModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->AddEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IINTERFACEMODEL_CancelMdlListener
* @brief   This function cancels a registered listener from this model object.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (ModelListener_t*)pMdlLsn           A pointer to ModelListener_t sturcture that was registered to
*                                              this model object and want to cancel it.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_FAILED      Failed. The specific listener does not belong to this model object.
*/
/*
#define IINTERFACEMODEL_CancelMdlListener(pIInterfaceModel,pMdlLsn) \
		GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->CancelMdlListener(pIInterfaceModel,pMdlLsn)
 use MDLLISTENER_CANCEL() instead 
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_CancelEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->CancelEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IINTERFACEMODEL_CancelEvtListener(IInterfaceModel *pIInterfaceModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->CancelEvtListener(pIInterfaceModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_CancelEvtAllListener(pIInterfaceModel,nEvtCode) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->CancelEvtAllListener(pIInterfaceModel,nEvtCode)
#else
__INLINE MAE_Ret IINTERFACEMODEL_CancelEvtAllListener(IInterfaceModel *pIInterfaceModel, ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->CancelEvtAllListener(pIInterfaceModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IINTERFACEMODEL_SetInterfaceObj
* @brief   User can set an interface object to the interface model by this function. The interface model would
*          keeps the object and add the reference count of the object instance. When the interface model
*          is released, the object instance would also be released.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (IBase*)pObj                       A IBase pointer of object which want to set to interface model.
* @param   (IBase*)pOwner                      The owner of the object instance.
*
* @retval  None.
*
* @note    This function will cause sending EVT_MDL_INTERFACE_CHANGE notification.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_SetInterfaceObj(pIInterfaceModel,pObj,pOwner) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->SetInterfaceObj(pIInterfaceModel,pObj,pOwner)
#else
__INLINE void IINTERFACEMODEL_SetInterfaceObj(IInterfaceModel *pIInterfaceModel, IBase *pObj, IBase*pOwner)
{
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->SetInterfaceObj(pIInterfaceModel,pObj,pOwner);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IINTERFACEMODEL_GetInterfaceObj
* @brief   User can get a specific object from the interface model by this function. The reference count
*          of object would plus one if the object supports the specific interface nId.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
* @param   (MAE_IId)nId                         An interface nId to be queried.
* @param   (void**)ppObj                       A pointer of void pointer to retrieve the object which user want to get.
* @param   (IBase*)pOwner                      Shall be an IBase interface object to keep the returned object.
*
* @retval  MAE_RET_SUCCESS         Successfully.
* @retval  MAE_RET_BAD_PARAM       Failed. Bad parameter.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface nId is not supported.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IINTERFACEMODEL_GetInterfaceObj(pIInterfaceModel,nId,ppObj,pOwner) \
	GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->GetInterfaceObj(pIInterfaceModel,nId,ppObj,pOwner)
#else
__INLINE MAE_Ret IINTERFACEMODEL_GetInterfaceObj(IInterfaceModel *pIInterfaceModel, MAE_IId nId, void** ppObj, IBase* pOwner)
{
	return GET_FUNCTBL((pIInterfaceModel),IInterfaceModel)->GetInterfaceObj(pIInterfaceModel,nId,ppObj,pOwner);
}

#endif /* __MAE_VENEERED_INTERFACE__ */



/*=============================================================*/
// helper functions
/*=============================================================*/

/**
* IINTERFACEMODEL_Notify
* @brief   This inline function provide an easy way to send EVT_MDL_INTERFACE_CHANGE notification.
*
* @param   (IInterfaceModel*)pIInterfaceModel  A pointer of IInterfaceModel interface object.
*
* @retval  None
*/
__INLINE void IINTERFACEMODEL_Notify(IInterfaceModel *pIInterfaceModel)
{
	ModelEvent_t ModelEvt;

	if(pIInterfaceModel)
	{
		MDLEVENT_INIT(&ModelEvt, EVT_MDL_INTERFACE_CHANGE, 0);
		IINTERFACEMODEL_SendNotify(pIInterfaceModel, &ModelEvt);
	}
}

#endif //__MAE_INTERFACEMODEL_H__
/*=============================================================*/
// end of file
