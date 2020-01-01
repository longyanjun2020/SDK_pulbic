/**
* @file    mmi_mae_model.h
* @version $Id: mmi_mae_model.h 1684 2009-08-29 16:28:08Z zinc.chen $
*
* @brief   This file defines the interface of IModel, the structure of Model event,
*          the structure of Model listener, the usage of Model event, Model listener,
*          and an object class which supports IModel interface.
*
* <Interface Description>
*     IModel is an interface, inherits from IBase, which provides a notification mechanism.
*     The basic funtionality is to register listener, cancel listener and send notification.
*     The interface nId of IModel is IID_MODEL.
*
* <Interface ID>
*     IID_MODEL
*
* <Class Description>
*     The CLSID_MODEL class implements IModel interface. User can create a CLSID_MODEL class object
*     via MAE_Shell by ISHELL_CreateInstance().
*
* <Class ID>
*     CLSID_MODEL
*/
#ifndef __MMI_MAE_MODEL_H__
#define __MMI_MAE_MODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model_forward.h"
#include "mmi_mae_model_types.h"
#include "mmi_mae_model_events.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// interface
/*=============================================================*/
/**
* INHERIT_IModel
* @brief   INHERIT_IModel is IModel interface inheritance definition.
*/
#define INHERIT_IModel(IName) \
	INHERIT_IBase(IName); \
	void (*SendNotify)              (IName*, ModelEvent_t*); \
	MAE_Ret (*AddEvtListener)       (IName*, ModelEvtCode_t, PfnModelEvtListener, void*); \
	MAE_Ret (*CancelEvtListener)    (IName*, ModelEvtCode_t, PfnModelEvtListener, void*); \
    MAE_Ret (*CancelEvtAllListener) (IName*, ModelEvtCode_t); \
	MAE_Ret (*AddMdlListener)       (IName*, ModelListener_t*); \
	MAE_Ret (*CancelMdlListener)    (IName*, ModelListener_t*)

//Here define IModel interface
DEFINE_INTERFACE(IModel);

/**
* @brief   The main structure for a model object.
*/
struct Model_t_
{
	DECLARE_FUNCTBL(IModel);   ///< Function table pointer
    
	u16               nRefCnt      : 15;        ///< Reference count
    u16               bStartNotify : 1;         ///< For avoid re-entry
	u8                nListenerMax;             ///< max size of the listener list
    u8                nListenerCnt;             ///< current size of the listener list
    ModelListener_t   *pMdlLsnListPtr;          /*!< This is a pointer of model listener link list
                                                   <pre>
                                                   +----+   +----+   +----+
                                                   Link-list  -->|root|-->|    |-->|    |--||
                                                   +----+   +----+   +----+
                                                   the most new one                    the most old one.
                                                   </pre>*/
    ModelListener_t   *pMdlLsnNext;             ///< To keep the next listener while sending notification.
	MdlListener_t     *pListenerList;           ///< dynamic array to store listener data
	MdlListener_t     tDefListener;             /// Default listener field, avoid to allocate another memory for model
};

/**
* MDLEVENT_INIT
* @brief   A macro to initialize a Model event structure.
*
* @param   pstMdlEvt(ModelEvent_t*)   A pointer of ModelEvent_t structure which want to initialize.
* @param   ec(ModelEvtCode_t)         Model event code. Reference to mmi_mae_model_events.h.
* @param   dwp(u32)                   A certain of data, such as index, pointer of structure, pointer of object.
*/
#define MDLEVENT_INIT(pstMdlEvt, ec, dwp) do{ \
	(pstMdlEvt)->nEvtCode = ec; \
	(pstMdlEvt)->nParam = dwp; \
}while(0)

/*=============================================================*/
// methods of IModel
/*=============================================================*/

/**
* IMODEL_QueryInterface
* @brief	This function queries another interface from IModel object. It will return an
*          interface object which you want to query if successful.
*
* @param   pIModel(IModel*)   A pointer of IModel interface object.
* @param   nId(MAE_IId)       An interface nId to be queried.
* @param   pp(void**)         A pointer of void pointer to retrieve an interface object which you want to query.
* @param   pOwner(IBase*)     Shall be an IBase interface object to keep the return object.
*
* @retval  MAE_RET_SUCCESS      Success.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface Id is not supported.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_QueryInterface(pIModel,nId,pp,pOwner) \
	GET_FUNCTBL((pIModel),IModel)->QueryInterface(pIModel,nId,pp,pOwner)
#else
__INLINE MAERet_t IMODEL_QueryInterface (IModel *pIModel, MAEIId_t nId, void** pp, IBase* pOwner)
{
	return GET_FUNCTBL((pIModel),IModel)->QueryInterface(pIModel,nId,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IMODEL_SendNotify
* @brief   This function sends the notify to all listeners which registered to this model.
*          An application or object could register listener by IMODEL_AddMdlListener() to
*          a specific model. When the model state is changed(such as data changed), the
*          model would notify all listeners by IMODEL_SendNotify().
*
* @param   pIModel(IModel*)         A pointer of IModel interface object.
* @param   pMdlEvt(ModelEvent_t*)   A pointer to ModelEvent_t sturcture to indicate which event is
*                                   occured and what kind of data is changed.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_SendNotify(pIModel,pMdlEvt) \
	GET_FUNCTBL((pIModel),IModel)->SendNotify(pIModel,pMdlEvt)
#else
__INLINE void IMODEL_SendNotify(IModel *pIModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIModel),IModel)->SendNotify(pIModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param   pIModel(IModel*)            A pointer of IModel interface object.
* @param   pMdlLsn(ModelListener_t*)   A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS    Success.
* @retval  MAE_RET_BAD_PARAM   Invalid paramater.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_AddMdlListener(pIModel,pMdlLsn) \
	GET_FUNCTBL((pIModel),IModel)->AddMdlListener(pIModel,pMdlLsn)
#else
__INLINE MAE_Ret IMODEL_AddMdlListener(IModel *pIModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIModel),IModel)->AddMdlListener(pIModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_AddEvtListener(pIModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIModel),IModel)->AddEvtListener(pIModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IMODEL_AddEvtListener(IModel *pIModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIModel),IModel)->AddEvtListener(pIModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IMODEL_CancelMdlListener
* @brief   This function cancels a registered listener from this model object.
*
* @param   pIModel(IModel*)            A pointer of IModel interface object.
* @param   pMdlLsn(ModelListener_t*)   A pointer to ModelListener_t sturcture that was registered to
*                                      this model object and want to cancel it.
*
* @retval  MAE_RET_SUCCESS    Success.
* @retval  MAE_RET_BAD_PARAM   Invalid paramater.
* @retval  MAE_RET_FAILED     The specific listener does not belong to this model object.
*/
//#define IMODEL_CancelMdlListener(pIModel,pMdlLsn) GET_FUNCTBL((pIModel),IModel)->CancelMdlListener(pIModel,pMdlLsn)
// use MDLLISTENER_CANCEL() instead //

#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_CancelEvtListener(pIModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIModel),IModel)->CancelEvtListener(pIModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IMODEL_CancelEvtListener(IModel *pIModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIModel),IModel)->CancelEvtListener(pIModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMODEL_CancelEvtAllListener(pIModel,nEvtCode) \
    GET_FUNCTBL((pIModel),IModel)->CancelEvtAllListener(pIModel,nEvtCode)
#else
__INLINE MAE_Ret IMODEL_CancelEvtAllListener(IModel *pIModel, ModelEvtCode_t nEvtCode)
{
    return GET_FUNCTBL((pIModel),IModel)->CancelEvtAllListener(pIModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/*=============================================================*/
// helper functions or macros
/*=============================================================*/
/**
* MDLLISTENER_INIT
* @brief   A macro to initialize a Model listener structure.
*
* @param   pMdlLsn(ModelListener_t*)   A pointer of ModelListener_t structure which want to initialize
* @param   pfn(pfnModelListener)         A callback function pointer with PfnModelListener prototype
* @param   pData(void*)                A context data pointer which will be passed into callback function
*
* @note    Do not call this macro if pMdlLsn has already listened to someone model.
*/
#define MDLLISTENER_INIT(pMdlLsn, pfn, pData) do{ \
	(pMdlLsn)->pUsrData = (void*)(pData); \
	(pMdlLsn)->pMdlListener = (PfnModelListener)(pfn); \
	(pMdlLsn)->pNext = NULL; \
	(pMdlLsn)->pModel = NULL; \
}while(0)

/**
* @brief	A macro to cancel a model listener. This macro will check if the model object instance is NULL.
*
* @param	pLsn	A pointer of ModelListener_t structure.
*/
#ifndef __MAE_VENEERED_INTERFACE__

#define MDLLISTENER_CANCEL(pLsn) do{\
	if((pLsn)->pModel)\
{\
	GET_FUNCTBL(((pLsn)->pModel),IModel)->CancelMdlListener((pLsn)->pModel, pLsn);\
}\
}while(0)
#else
#define MDLLISTENER_CANCEL(pLsn) do{\
	if((pLsn)->pModel)\
{\
	IMODEL_CancelMdlListener((pLsn)->pModel, pLsn);\
}\
}while(0)

__INLINE MAE_Ret IMODEL_CancelMdlListener(IModel *pIModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIModel),IModel)->CancelMdlListener(pIModel,pMdlLsn);
}

#endif /* __MAE_VENEERED_INTERFACE__ */


#endif	//__MAE_MODEL_H__
/*=============================================================*/
// end of file
