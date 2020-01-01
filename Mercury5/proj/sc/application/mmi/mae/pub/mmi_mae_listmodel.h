/**
* @file    mmi_mae_listmodel.h
* @version $Id: mmi_mae_listmodel.h 978 2009-05-26 10:47:39Z elvis.chen $
* @brief   This file defines IListModel interface.
*
*/
#ifndef __MMI_MAE_LISTMODEL_H__
#define __MMI_MAE_LISTMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"
#include "mmi_mae_listmodel_types.h"
#include "mmi_mae_listmodel_forward.h"

/*=============================================================*/
// interface
/*=============================================================*/
// IListModel interface
#define INHERIT_IListModel(IName) \
	INHERIT_IModel(IName); \
	u32 (*Size)                         (IName *po); \
	MAERet_t (*GetAt)                    (IName *po, u32 nIndex, ListDataType_e nType, void **ppoItem)

DEFINE_INTERFACE(IListModel);


/*=============================================================*/
// methods of IListModel
/*=============================================================*/
/**
* ILISTMODEL_QueryInterface
* @brief   This function queries another interface from IListModel object. It will return an
*          interface object which you want to query if successful.
*
* @param[in]   pIListModel(IListModel*)   A pointer of IListModel interface object.
* @param[in]   id(MAE_IId)                An interface id to be queried.
* @param[out]  pp(void**)                 A pointer of void pointer to retrieve an interface object which you want to query.
* @param[in]   pOwner(IBase*)             Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS            Successfully.
* @retval  MAE_RET_NOT_SUPPORTED      Failed. The queried interface id is not supported.
*/
#define ILISTMODEL_QueryInterface(pIListModel,id,pp,pOwner) \
	GET_FUNCTBL((pIListModel),IListModel)->QueryInterface(pIListModel,id,pp,pOwner)

/**
* ILISTMODEL_SendNotify
* @brief   This function sends the notification to all listeners which registered to this model.
*          An application or object could register listener by ILISTMODEL_AddMdlListener() to
*          a specific model. When the model state is changed(such as data changed), the
*          model would notify all listeners by ILISTMODEL_SendNotify().
*
* @param[in]   pIListModel(IListModel*)       A pointer of IListModel interface object.
* @param[in]   pListMdlEvt(ListModelEvent_t*) A pointer to ListModelEvent_t sturcture to indicate which event is
*                                         occured and what kind of data is changed.
*
* @retval  None.
*/
#define ILISTMODEL_SendNotify(pIListModel,pMdlEvt) \
	GET_FUNCTBL((pIListModel),IListModel)->SendNotify(pIListModel,pMdlEvt)

/**
* ILISTMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param[in]   pIListModel(IListModel*)    A pointer of IListModel interface object.
* @param[in]   pMdlLsn(ModelListener_t*)   A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Invalid paramater.
*/
#define ILISTMODEL_AddMdlListener(pIListModel,pMdlLsn) \
	GET_FUNCTBL((pIListModel),IListModel)->AddMdlListener(pIListModel,pMdlLsn)

#ifndef __MAE_VENEERED_INTERFACE__
#define ILISTMODEL_AddEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData) \
	GET_FUNCTBL((pIListModel),IListModel)->AddEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ILISTMODEL_AddEvtListener(IListModel *pIListModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIListModel),IListModel)->AddEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/*
#define ILISTMODEL_CancelMdlListener(pIListModel,pMdlLsn) 
	GET_FUNCTBL((pIListModel),IListModel)->CancelMdlListener(pIListModel,pMdlLsn)
 use MDLLISTENER_CANCEL() instead 
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define ILISTMODEL_CancelEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData) \
	GET_FUNCTBL((pIListModel),IListModel)->CancelEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ILISTMODEL_CancelEvtListener(IListModel *pIListModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIListModel),IListModel)->CancelEvtListener(pIListModel,nEvtCode,pFnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ILISTMODEL_CancelEvtAllListener(pIListModel,nEvtCode) \
	GET_FUNCTBL((pIListModel),IListModel)->CancelEvtAllListener(pIListModel,nEvtCode)
#else
__INLINE MAE_Ret ILISTMODEL_CancelEvtAllListener(IListModel *pIListModel, ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIListModel),IListModel)->CancelEvtAllListener(pIListModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* ILISTMODEL_Size
* @brief   This function returns the size of this listmodel.
*
* @param[in]   pIListModel(IListModel*)    A pointer of IListModel interface object.
*
* @retval  A u32 value to indicate how many items in this listmodel.
*/
#define ILISTMODEL_Size(pIListModel) \
	GET_FUNCTBL((pIListModel),IListModel)->Size(pIListModel)

/**
* ILISTMODEL_GetAt
* @brief   This function returns a specific item from this listmodel. User can decide
*          to get which item by index.
*
* @param[in]   pIListModel(IListModel*)    A pointer of IListModel interface object.
* @param[in]   idx(u32)                    A zero-base index to get.
* @param[out]  ppo(void**)                 A pointer of item to returned.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*/
#define ILISTMODEL_GetAt(pIListModel,idx,ppo) \
	GET_FUNCTBL((pIListModel),IListModel)->GetAt(pIListModel,idx,COMMON_LIST_DATA,ppo)



/*=============================================================*/
// helper functions or macro functions
/*=============================================================*/
/**
* @brief   A macro to initialize ListModelEvent_t
*
* @param   _pLstMdlEvt(ModelEvent_t*) A pointer of ListModelEvent_t structure which want to initialize.
* @param   _evt(ModelEvtCode_t)       Model event code. Reference to mmi_mae_model_events.h.
* @param   _param(u32)                A certain of data, such as index, pointer of structure, pointer of object.
* @param   _pos(u32)                  Zero-base index position which listmodel changed.
* @param   _oldsize(u32)              size of listmodel before changed.
* @param   _newsize(u32)              size of listmodel after changed.
*/
#define LISTMODELEVENT_INIT(_pLstMdlEvt, _evt, _param, _pos, _oldsize, _newsize) do { \
	(_pLstMdlEvt)->tMEvtBase.nEvtCode = _evt; \
	(_pLstMdlEvt)->tMEvtBase.nParam = _param; \
	(_pLstMdlEvt)->nPos = _pos; \
	(_pLstMdlEvt)->nOldSize = _oldsize; \
	(_pLstMdlEvt)->nNewSize = _newsize; \
}while(0)


#endif //__MMI_MAE_LISTMODEL_H__
/*=============================================================*/
// end of file
