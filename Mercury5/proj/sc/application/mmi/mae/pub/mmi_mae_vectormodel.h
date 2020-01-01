/**
 * @file    mmi_mae_vectormodel.h
 * @version $Id: mmi_mae_vectormodel.h 1684 2009-08-29 16:28:08Z zinc.chen $
 * @brief   This file defines IVectorModel interface.
 *
 */
#ifndef __MMI_MAE_VECTORMODEL_H__
#define __MMI_MAE_VECTORMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"
#include "mmi_mae_listmodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define VECTOR_LAST		((u32)0xFFFFFFFF)
#define VECTOR_NOTIFY	((boolean)TRUE)


///deprecated, => use ListDataType_e
//typedef u32 VectorDataType_e;


///deprecated, => use ListDataType
//typedef enum
//{
//	COMMON_VECTOR_DATA = 0,//deprecated, => use COMMON_LIST_DATA
//	VECTOR_DATATYPE_SUM    //deprecated, => use LIST_DATATYPE_SUM
//}VectorDataType;


///deprecated, => use ListModelEvent_t
/**
 * @brief   Event that the vector model sends out on changes
 */
//typedef struct {
//	ModelEvent_t    MEvtBase; ///< model event base structure
//	u32             pos;      ///< position at which change occurred
//	u32             oldSize;  ///< old size of list
//	u32             newSize;  ///< new size of list
//} VectorModelEvent_t;


///deprecated, => use LISTMODELEVENT_INIT()
/**
 * @brief   A macro to initialize VectorModelEvent_t
 */
/*
#define VECTORMODELEVENT_Init(pe, c, dwp, p, _oldSize, _newSize) do { 
		(pe)->MEvtBase.nEvtCode = c; 
		(pe)->MEvtBase.dwParam = dwp; 
		(pe)->pos = p; 
		(pe)->oldSize = _oldSize; 
		(pe)->newSize = _newSize; 
		}while(0)
*/

///deprecated, => use ListModelFree_t
/**
 * @brief   This structure is the return value of IVECTORMODEL_SetPfnFree().
 *          Keeping the pointer of free function and the object instance of data owner.
 */
//typedef struct VECTOR_MODEL_FREE_TAG
//{
//	PfnModelFree pFreeFunc;    /*!< A function pointer to keep free function which will be used
//                                          when release a model or deleting/replacing the data in the model.*/
//	IBase * pOwner;                  ///< An IBase object instance to indicate who is the owner of the data(object) in the model.
//}VectorModelFree_t;


/*=============================================================*/
// interface
/*=============================================================*/
// IVectorModel interface
#define INHERIT_IVectorModel(IName) \
    INHERIT_IListModel(IName); \
    MAE_Ret (*ReplaceAt)                (IName *po, u32 nIndex, void *pvItem, boolean bNotify); \
    MAE_Ret (*InsertAt)                 (IName *po, u32 nIndex, void *pvItem); \
    MAE_Ret (*DeleteAt)                 (IName *po, u32 nIndex); \
    void (*DeleteAll)                   (IName *po); \
    MAE_Ret (*EnsureCapacity)           (IName *po, u32 nRequired, u32 nGrowBy); \
    ListModelFree_t (*SetPfnFree)       (IName *po, PfnModelFree pfnFree, IBase *pItemOwner)

DEFINE_INTERFACE(IVectorModel);


/**
 * IVECTORMODEL_QueryInterface
 * @brief	This function queries another interface from an IVectorModel object.
 *          It will return an interface object which you want to query if successful.
 *
 * @param[in]   (IVectorModel*)pIVectorModel    A pointer of IVectorModel interface object.
 * @param[in]   (MAE_IId)nId                     An interface nId to be queried.
 * @param[out]  (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
 * @param[in]   (IBase*)pOwner                  Shall be an IBase interface object to keep the return object.
 *
 * @retval  MAE_RET_SUCCESS         Successfully.
 * @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface nId is not supported.
 *
 * @note    Only IID_VECTORMODEL, IID_LISTMODEL and IID_MODEL are supported.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_QueryInterface(pIVectorModel,nId,pp,pOwner) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->QueryInterface(pIVectorModel,nId,pp,pOwner)
#else
__INLINE MAERet_t IVECTORMODEL_QueryInterface (IVectorModel *pIVectorModel, MAEIId_t nId, void** pp , IBase* pOwner)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->QueryInterface(pIVectorModel,nId,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
 * IVECTORMODEL_SendNotify
 * @brief	This function sends the notify to all listeners which registered to this model.
 *          An application or object could register listener by IMODEL_AddMdlListener()/IVECTORMODEL_AddMdlListener()
 *          to a specific model. When the model state is changed(such as data changed), the
 *          model would notify all listeners by IMODEL_SendNotify()/IVECTORMODEL_SendNotify().
 *
 * @param[in]   (IVectorModel*)pIVectorModel  A pointer of IVectorModel interface object.
 * @param[in]   (ModelEvent_t*)pMdlEvt        A pointer to ModelEvent_t sturcture to indicate which event is occured and
 *                                            what kind of data is changed.
 *
 * @retval  None.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_SendNotify(pIVectorModel,pMdlEvt) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->SendNotify(pIVectorModel,pMdlEvt)
#else
__INLINE void IVECTORMODEL_SendNotify(IVectorModel *pIVectorModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIVectorModel),IVectorModel)->SendNotify(pIVectorModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param[in]   (IVectorModel*)pIVectorModel    A pointer of IVectorModel interface object.
* @param[in]   (ModelListener_t*)pMdlLsn       A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_AddMdlListener(pIVectorModel,pMdlLsn) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->AddMdlListener(pIVectorModel,pMdlLsn)
#else
__INLINE MAE_Ret IVECTORMODEL_AddMdlListener(IVectorModel *pIVectorModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->AddMdlListener(pIVectorModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_AddEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->AddEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IVECTORMODEL_AddEvtListener(IVectorModel *pIVectorModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->AddEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/*
#define IVECTORMODEL_CancelMdlListener(pIVectorModel,pMdlLsn) 
	GET_FUNCTBL((pIVectorModel),IVectorModel)->CancelMdlListener(pIVectorModel,pMdlLsn)
 use MDLLISTENER_CANCEL() instead 
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_CancelEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->CancelEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData)
#else
__INLINE MAE_Ret IVECTORMODEL_CancelEvtListener(IVectorModel *pIVectorModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->CancelEvtListener(pIVectorModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_CancelEvtAllListener(pIVectorModel,nEvtCode) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->CancelEvtAllListener(pIVectorModel,nEvtCode)
#else
__INLINE MAE_Ret IVECTORMODEL_CancelEvtAllListener(IVectorModel *pIVectorModel,ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->CancelEvtAllListener(pIVectorModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_Size
* @brief    This function returns the element count of the vectormodel.
*
* @param[in]    (IVectorModel*)pIVectorModel    A pointer of IVectortModel interface object.
*
* @retval       A u32 value to indicate how many items in this vectormodel.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_Size(pIVectorModel) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->Size(pIVectorModel)
#else
__INLINE u32 IVECTORMODEL_Size(IVectorModel *pIVectorModel)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->Size(pIVectorModel);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_GetAt
* @brief   This function returns a specific item from this vectormodel. User can decide
*          to get which item by index.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index to get.
* @param[out]  (void**)ppoItem                  A pointer of item to returned.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_GetAt(pIVectorModel,nIndex,ppoItem) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->GetAt(pIVectorModel,nIndex,COMMON_LIST_DATA,ppoItem)
#else
__INLINE MAERet_t IVECTORMODEL_GetAt(IVectorModel *pIVectorModel, u32 nIndex,  void **ppoItem)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->GetAt(pIVectorModel,nIndex,COMMON_LIST_DATA, ppoItem);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_ReplaceAt
* @brief   This function replace the item with users' new giving pointer at the position which specific by index.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of position which will be replaced.
* @param[in]   (void*)pvItem                    A pointer of item that will be set at the position of the vectormodel.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*
* @note    The original item at the specific position will be freed first so that avoid to send the same data
*          pointer with the original one.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_ReplaceAt(pIVectorModel,nIndex,pvItem) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->ReplaceAt(pIVectorModel,nIndex,pvItem,VECTOR_NOTIFY)
#else
__INLINE MAE_Ret IVECTORMODEL_ReplaceAt(IVectorModel *pIVectorModel, u32 nIndex, void *pvItem)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->ReplaceAt(pIVectorModel,nIndex,pvItem, VECTOR_NOTIFY);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_InsertAt
* @brief   This function insert a new item into the vectormodel at the position what idx specified. And if there is any item stay
*          or after the position idx, all of them will be moved to next position one bye one.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of the position which will be inserted.
* @param[in]   (void*)pvItem                    A pointer of item that will be inserted at the position of the vectormodel.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_OUT_OF_MEMORY       Insufficient memory.
*
* @note  Users should keep the data pointer (pv) since vectormodel only remembers the saves of the item instead of copying all the
*        data element into vectormodel's memory buffer.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_InsertAt(pIVectorModel,nIndex,pvItem) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->InsertAt(pIVectorModel,nIndex,pvItem)
#else
__INLINE MAE_Ret IVECTORMODEL_InsertAt(IVectorModel *pIVectorModel, u32 nIndex, void *pvItem)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->InsertAt(pIVectorModel,nIndex,pvItem);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_DeleteAt
* @brief   This function delete the specific item from the vectormodel, and it will free the item too.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of the position which will be removed.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_DeleteAt(pIVectorModel,nIndex) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->DeleteAt(pIVectorModel,nIndex)
#else
__INLINE MAE_Ret IVECTORMODEL_DeleteAt(IVectorModel *pIVectorModel, u32 nIndex)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->DeleteAt(pIVectorModel,nIndex);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_DeleteAll
* @brief   This function clear all items of the vectormodel.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_DeleteAll(pIVectorModel) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->DeleteAll(pIVectorModel)
#else
__INLINE void IVECTORMODEL_DeleteAll(IVectorModel *pIVectorModel)
{
	GET_FUNCTBL((pIVectorModel),IVectorModel)->DeleteAll(pIVectorModel);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_EnsureCapacity
* @brief   This function ensure the capacity (size) of the vectormodel, including the initial size and
*          the growth size.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (u32)nRequired                   Initial size. If the size of vectormodel is small than users'
*                                               requirement, it will allocate a memory buffer with size as
*                                               (nRequired x Item Size).
* @param[in]   (u32)nGrowBy                     Growth size. When users insert a new item into the vectormodel
*                                               and there's no more free slot to insert, it will enlarge the vectormodel
                                                with nGrowBy slots at a time.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           nGrowBy is zero.
* @retval  MAE_RET_OUT_OF_MEMORY       Insufficient memory.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_EnsureCapacity(pIVectorModel,nRequired,nGrowBy) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->EnsureCapacity(pIVectorModel,nRequired,nGrowBy)
#else
__INLINE MAE_Ret IVECTORMODEL_EnsureCapacity(IVectorModel *pIVectorModel, u32 nRequired, u32 nGrowBy)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->EnsureCapacity(pIVectorModel,nRequired,nGrowBy);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_SetPfnFree
* @brief   This function set the free function of the vectormodel, and it will be used when each item
*          is removed from the vectormodel.
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (PfnModelFree)pfn          A free function pointer to free data..
* @param[in]   (IBase*)pItemOwner               Shall be an IBase interface object to keep the return object..
*
* @retval  ListModelFree_t        The older free function pointer if available.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IVECTORMODEL_SetPfnFree(pIVectorModel,pfn,pItemOwner) \
	GET_FUNCTBL((pIVectorModel),IVectorModel)->SetPfnFree(pIVectorModel,pfn,pItemOwner)
#else
__INLINE ListModelFree_t IVECTORMODEL_SetPfnFree(IVectorModel *pIVectorModel, PfnModelFree pfn, IBase *pItemOwner)
{
	return GET_FUNCTBL((pIVectorModel),IVectorModel)->SetPfnFree(pIVectorModel,pfn,pItemOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IVECTORMODEL_Add
* @brief   This function add a new item into the vectormodel at the last position
*
* @param[in]   (IVectorModel*)pIVectorModel     A pointer of IVectorModel interface object.
* @param[in]   (void*)pv                        A pointer of item that will be inserted.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_OUT_OF_MEMORY       Insufficient memory.
*/
#define IVECTORMODEL_Add(p,pv) \
	IVECTORMODEL_InsertAt(p,VECTOR_LAST,pv)

/*=============================================================*/
// functions
/*=============================================================*/
//common function
void IVECTORMODEL_ChangeContentNotifyAt(IVectorModel *pIVectorModel, u32 nIndex);

#endif //__MAE_VECTORMODEL_H__
/*=============================================================*/
// end of file
