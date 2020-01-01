
#ifndef ___MMI_MAE_IMAGEMODEL_H__
#define ___MMI_MAE_IMAGEMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_mae_model.h"
#include "mmi_mae_image_forward.h"


/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// interface
/*=============================================================*/
/**
* INHERIT_IImageModel
* @brief   INHERIT_IImageModel is IImageModel interface inheritance definition.
*/
#define INHERIT_IImageModel(IName) \
	INHERIT_IInterfaceModel(IName); \
	boolean  (*DecodeNextFrame) (IName *, ImgStatus_t)

//Here define IImageModel interface
DEFINE_INTERFACE(IImageModel);

/*=============================================================*/
// functions
/*=============================================================*/

/**
* IIMAGEMODEL_QueryInterface
* @brief	This function queries another interface from an IImageModel object.
*          It will return an image object which you want to query if successful.
*
* @param   (IImageModel*) pIImageModel  A pointer of IImageModel interface object.
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
#define IIMAGEMODEL_QueryInterface(pIImageModel,nId,pp,pOwner) \
	GET_FUNCTBL((pIImageModel),IImageModel)->QueryInterface(pIImageModel,nId,pp,pOwner)
#else
__INLINE MAE_Ret IIMAGEMODEL_QueryInterface(IImageModel *pIImageModel, MAE_IId nId, void **pp, IBase *pOwner)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->QueryInterface(pIImageModel,nId,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IIMAGEMODEL_SendNotify
* @brief   This function sends the notify to all listeners which registered to this model.
*          An application or object could register listener by IMODEL_AddMdlListener()/IIMAGEMODEL_AddMdlListener()
*          to a specific model. When the model state is changed(such as data changed), the
*          model would notify all listeners by IMODEL_SendNotify()/IIMAGEMODEL_SendNotify().
*
* @param   (IImageModel*)pIImageModel  A pointer of IImageModel interface object.
* @param   (ModelEvent_t*)pMdlEvt              A pointer to ModelEvent_t sturcture to indicate which event is
*                                              occured and what kind of data is changed.
*
* @retval  None.
*/

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_SendNotify(pIImageModel,pMdlEvt) \
	GET_FUNCTBL((pIImageModel),IImageModel)->SendNotify(pIImageModel,pMdlEvt)
#else
__INLINE void IIMAGEMODEL_SendNotify(IImageModel *pIImageModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIImageModel),IImageModel)->SendNotify(pIImageModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IIMAGEMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param   (IImageModel*)pIImageModel  A pointer of IImageModel interface object.
* @param   (ModelListener_t*)pMdlLsn           A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
*/

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_AddMdlListener(pIImageModel,pMdlLsn) \
	GET_FUNCTBL((pIImageModel),IImageModel)->AddMdlListener(pIImageModel,pMdlLsn)
#else
__INLINE MAE_Ret IIMAGEMODEL_AddMdlListener(IImageModel *pIImageModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->AddMdlListener(pIImageModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_AddEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIImageModel),IImageModel)->AddEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IIMAGEMODEL_AddEvtListener(IImageModel *pIImageModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->AddEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IIMAGEMODEL_CancelMdlListener
* @brief   This function cancels a registered listener from this model object.
*
* @param   (IImageModel*)pIImageModel  A pointer of IImageModel interface object.
* @param   (ModelListener_t*)pMdlLsn           A pointer to ModelListener_t sturcture that was registered to
*                                              this model object and want to cancel it.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
* @retval  MAE_RET_FAILED      Failed. The specific listener does not belong to this model object.
*/

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_CancelEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIImageModel),IImageModel)->CancelEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IIMAGEMODEL_CancelEvtListener(IImageModel *pIImageModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void* pData)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->CancelEvtListener(pIImageModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_CancelEvtAllListener(pIImageModel,nEvtCode) \
	GET_FUNCTBL((pIImageModel),IImageModel)->CancelEvtAllListener(pIImageModel,nEvtCode)
#else
__INLINE MAE_Ret IIMAGEMODEL_CancelEvtAllListener(IImageModel *pIImageModel, ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->CancelEvtAllListener(pIImageModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IIMAGEMODEL_SetImageObj
* @brief   User can set an image object to the image model by this function. The image model would
*          keeps the object and add the reference count of the object instance. When the image model
*          is released, the object instance would also be released.
*
* @param   (IImageModel*)pIImageModel  A pointer of IImageModel interface object.
* @param   (IBase*)pObj                       A IBase pointer of object which want to set to imagemodel.
* @param   (IBase*)pOwner                      The owner of the object instance.
*
* @retval  None.
*
* @note    This function will cause sending EVT_MDL_INTERFACE_CHANGE notification.
*/


#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_SetImageObj(pIImageModel,pObj,pOwner) \
	GET_FUNCTBL((pIImageModel),IImageModel)->SetInterfaceObj(pIImageModel,pObj,pOwner)
#else
__INLINE void IIMAGEMODEL_SetImageObj(IImageModel *pIImageModel, IBase *pObj, IBase *pOwner)
{
	GET_FUNCTBL((pIImageModel),IImageModel)->SetInterfaceObj(pIImageModel,pObj,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_GetImageObj(pIImageModel,nId,ppObj,pOwner) \
	GET_FUNCTBL((pIImageModel),IImageModel)->GetInterfaceObj(pIImageModel,nId,ppObj,pOwner)
#else
__INLINE MAE_Ret IIMAGEMODEL_GetImageObj(IImageModel *pIImageModel, MAE_IId nId, void** ppObj, IBase *pOwner)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->GetInterfaceObj(pIImageModel,nId,ppObj,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IIMAGEMODEL_DecodeNextFrame
* @brief   User this api to decide that need to decode or not.
*
* @param   (pIImageModel *) 	pIImageModel  A pointer of IImageModel interface object.
* @param   (ImgStatus_t) nState A boolean value to restore the result of decode or not.
*
*/

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMAGEMODEL_DecodeNextFrame(pIImageModel,nState) \
	GET_FUNCTBL((pIImageModel),IImageModel)->DecodeNextFrame(pIImageModel,nState)
#else
__INLINE boolean IIMAGEMODEL_DecodeNextFrame (IImageModel *pIImageModel, ImgStatus_t nState)
{
	return GET_FUNCTBL((pIImageModel),IImageModel)->DecodeNextFrame(pIImageModel,nState);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


#endif //___MMI_MAE_IMAGEMODEL_H__
 






