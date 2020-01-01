/**
 * @file    mmi_mae_arraymodel.h
 * @version $Id: mmi_mae_arraymodel.h 1684 2009-08-29 16:28:08Z zinc.chen $
 * @brief   This file defines IArrayModel interface.
 *
 * <Interface Description>
 *     IArrayModel inherits from IListModel and provides a mechanism to insert/delete item to/from the
 *     array-model. Users need to set the item byte size first; each item in the array model has the same item byte size.
 *     When user inserts the item, array-mode will copy it to the array memory according to the item byte size.
 *     If user set the EnsureCapacity, the array-model will allocate the enough memory for the ensure number of items.
 *     User can set the item free function if they need to release some object or free some memory before
 *     array-model delete the item and free it's memory.
 *     Actually, IArrayModel model memory copy the item according to the item byte size, but not keeping the item pointer.
 *     So users need to free the item memory by themselves after calling the insert API.
 *
 * <Interface ID>
 *     IID_ARRAYMODEL
 *
 * <Model Notification Event>
 *     =======================
 *     EVT_LISTMDL_CHANGE: While a new item has been inserted in this array-model, or an items has been updated,
 *                         or some items has been deleted from this array-mode, model event notifies
 *                         this event code.
 *
 * <Class Description>
 *     The CLSID_ARRAYMODEL class implements IArrayModel interface. User can create a CLSID_ARRAYMODEL
 *     class object via MAE_Shell by ISHELL_CreateInstance().
 *
 * <Class ID>
 *     CLSID_ARRAYMODEL
 *
 */
#ifndef __MMI_MAE_ARRAYMODEL_H__
#define __MMI_MAE_ARRAYMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_listmodel.h"


/*=============================================================*/
// type and define
/*=============================================================*/
#define ARRAY_LAST		((u32)0xFFFFFFFF)
#define ARRAY_NOTIFY	((boolean)TRUE)

///deprecated, => use ListDataType_e
//typedef u32 ArrayDataType_e;


///deprecated, => use ListDataType
//typedef enum
//{
//	COMMON_ARRAY_DATA = 0,  //deprecated, => use COMMON_LIST_DATA
//	ARRAY_DATATYPE_SUM      //deprecated, => use LIST_DATATYPE_SUM
//}ArrayDataType;


///deprecated, => use ListModelEvent_t
/**
 * @brief   Event that the array model sends out on changes
 */
//typedef struct {
//	ModelEvent_t    MEvtBase; ///< model event base structure
//	u32             pos;      ///< position at which change occurred
//	u32             oldSize;  ///< old size of list
//	u32             newSize;  ///< new size of list
//} ArrayModelEvent_t;


///deprecated, => use LISTMODELEVENT_INIT()
/**
 * @brief   A macro to initialize ArrayModelEvent_t
 */
//#define ARRAYMODELEVENT_Init(pe, c, dwp, p, _oldSize, _newSize) do { \
//		(pe)->MEvtBase.nEvtCode = c; \
//		(pe)->MEvtBase.dwParam = dwp; \
//		(pe)->pos = p; \
//		(pe)->oldSize = _oldSize; \
//		(pe)->newSize = _newSize; \
//		}while(0)

/**
 * @brief   This structure is the return value of IARRAYMODEL_SetPfnFree().
 *          Keeping the pointer of free function and the object instance of data owner.
 */


///deprecated, => use ListModelFree_t
//typedef struct ARRAY_MODEL_FREE_TAG
//{
//	pfnModelFree pFreeFunc;    /*!< A function pointer to keep free function which will be used
//                                          when release a model or deleting/replacing the data in the model.*/
//	IBase * pOwner;                  ///< An IBase object instance to indicate who is the owner of the data(object) in the model.
//}ArrayModelFree_t;

/*=============================================================*/
// interface
/*=============================================================*/
// IArrayModel interface
#define INHERIT_IArrayModel(IName) \
    INHERIT_IListModel(IName); \
    MAE_Ret (*ReplaceAt)                (IName *po, u32 nIndex, void *pvItem, boolean bNotify); \
    MAE_Ret (*InsertAt)                 (IName *po, u32 nIndex, void *pvItem); \
    MAE_Ret (*DeleteAt)                 (IName *po, u32 nIndex); \
    void (*DeleteAll)                   (IName *po); \
    MAE_Ret (*EnsureCapacity)           (IName *po, u32 nRequired, u32 nGrowBy); \
    ListModelFree_t (*SetPfnFree)       (IName *po, PfnModelFree pfnFree, IBase *pItemOwner); \
    void (*SetItemByteSize)             (IName *po, u32 nItemByteSize); \
    u32     (*GetItemByteSize)          (IName *po)
DEFINE_INTERFACE(IArrayModel);


/**
 * IARRAYMODEL_QueryInterface
 * @brief	This function queries another interface from an IArrayModel object.
 *          It will return an interface object which you want to query if successful.
 *
 * @param[in]   (pIArrayModel*)pIArrayModel     A pointer of IArrayModel interface object.
 * @param[in]   (MAE_IId)id                     An interface id to be queried.
 * @param[out]  (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
 * @param[in]   (IBase*)pOwner                  Shall be an IBase interface object to keep the return object.
 *
 * @retval  MAE_RET_SUCCESS         Successfully.
 * @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
 *
 * @note    Only IID_ARRAYMODEL, IID_LISTMODEL and IID_MODEL are supported.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_QueryInterface(pIArrayModel,id,pp,pOwner) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->QueryInterface(pIArrayModel,id,pp,pOwner)
#else
__INLINE MAERet_t IARRAYMODEL_QueryInterface (IArrayModel *pIArrayModel, MAEIId_t nId, void** pp , IBase* pOwner)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->QueryInterface(pIArrayModel,nId,pp,pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
 * IARRAYMODEL_SendNotify
 * @brief	This function sends the notify to all listeners which registered to this model.
 *          An application or object could register listener by IMODEL_AddMdlListener()/IARRAYMODEL_AddMdlListener()
 *          to a specific model. When the model state is changed(such as data changed), the
 *          model would notify all listeners by IMODEL_SendNotify()/IARRAYMODEL_SendNotify().
 *
 * @param[in]   (IArrayModel*)pIArrayModel      A pointer of IArrayModel interface object.
 * @param[in]   (ModelEvent_t*)pMdlEvt          A pointer to ModelEvent_t sturcture to indicate which event is occured and
 *                                              what kind of data is changed.
 *
 * @retval  None.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_SendNotify(pIArrayModel,pMdlEvt) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->SendNotify(pIArrayModel,pMdlEvt)
#else
__INLINE void IARRAYMODEL_SendNotify(IArrayModel *pIArrayModel, ModelEvent_t *pMdlEvt)
{
	GET_FUNCTBL((pIArrayModel),IArrayModel)->SendNotify(pIArrayModel,pMdlEvt);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_AddMdlListener
* @brief   This function registers a listener to this model object.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (ModelListener_t*)pMdlLsn        A pointer to ModelListener_t sturcture that will register to this model object.
*
* @retval  MAE_RET_SUCCESS     Successfully.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_AddMdlListener(pIArrayModel,pMdlLsn) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->AddMdlListener(pIArrayModel,pMdlLsn)
#else
__INLINE MAE_Ret IARRAYMODEL_AddMdlListener(IArrayModel *pIArrayModel, ModelListener_t *pMdlLsn)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->AddMdlListener(pIArrayModel,pMdlLsn);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_AddEvtListener(pIArrayModel,nEvtCode,pFnEvtCb,pData) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->AddEvtListener(pIArrayModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IARRAYMODEL_AddEvtListener(IArrayModel *pIArrayModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->AddEvtListener(pIArrayModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


///use MDLLISTENER_CANCEL() instead
//#ifndef __MAE_VENEERED_INTERFACE__
//#define IARRAYMODEL_CancelMdlListener(pIArrayModel,pMdlLsn) \
//	GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelMdlListener(pIArrayModel,pMdlLsn)
//#else
//__INLINE MAE_Ret IARRAYMODEL_CancelMdlListener(IArrayModel *pIArrayModel, ModelListener_t *pMdlLsn)
//{
//	return GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelMdlListener(pIArrayModel,pMdlLsn);
//}
//#endif /* __MAE_VENEERED_INTERFACE__ */
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_CancelEvtListener(pIArrayModel,nEvtCode,pFnEvtCb,pData) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelEvtListener(pIArrayModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IARRAYMODEL_CancelEvtListener(IArrayModel *pIArrayModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pfnEvtCb, void *pData)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelEvtListener(pIArrayModel,nEvtCode,pfnEvtCb,pData);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_CancelEvtAllListener(pIArrayModel,nEvtCode) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelEvtAllListener(pIArrayModel,nEvtCode)
#else
__INLINE MAE_Ret IARRAYMODEL_CancelEvtAllListener(IArrayModel *pIArrayModel, ModelEvtCode_t nEvtCode)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->CancelEvtAllListener(pIArrayModel,nEvtCode);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
* IARRAYMODEL_Size
* @brief    This function returns the element count of the arraymodel.
*
* @param[in]    (IArrayModel*)pIArrayModel    A pointer of IArrayModel interface object.
*
* @retval       A u32 value to indicate how many items in this arraymodel.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_Size(pIArrayModel) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->Size(pIArrayModel)
#else
__INLINE u32 IARRAYMODEL_Size(IArrayModel *pIArrayModel)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->Size(pIArrayModel);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_GetAt
* @brief   This function returns a specific item from this arraymodel. User can decide
*          to get which item by index.
*
* @param[in]   (IArrayModel*)pIArrayModel     A pointer of IArrayModel interface object.
* @param[in]   (u32)nIndex                    A zero-base index to get.
* @param[out]  (void**)ppoItem                A pointer of item to returned.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*/
__INLINE MAERet_t IARRAYMODEL_GetAt(IArrayModel *pIArrayModel, u32 nIndex, void **ppItem)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->GetAt(pIArrayModel,nIndex,COMMON_LIST_DATA,ppItem);
}

/**
* IARRAYMODEL_ReplaceAt
* @brief   This function replace the item with users' new giving item at the position which specific by index.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of position which will be replaced.
* @param[in]   (void*)pvItem                    A pointer of item that will be set at the position of the arraymodel.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_ReplaceAt(pIArrayModel,nIndex,pvItem) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->ReplaceAt(pIArrayModel,nIndex,pvItem,ARRAY_NOTIFY)
#else
__INLINE MAE_Ret IARRAYMODEL_ReplaceAt(IArrayModel *pIArrayModel, u32 nIndex, void *pItem)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->ReplaceAt(pIArrayModel,nIndex,pItem,ARRAY_NOTIFY);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_InsertAt
* @brief   This function insert a new item into the arraymodel at the position what nIndex specified. And if there is any item stay
*          or after the position nIndex, all of them will be moved to next position one bye one.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of the position which will be inserted.
* @param[in]   (void*)pvItem                    A pointer of item that will be inserted at the position of the arraymodel.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_OUT_OF_MEMORY       Insufficient memory.
*
* @note     Arraymodel keeps a copy of the item in its memory buffer so that users may free their data (pvItem) once the item is inserted
*           into arraymodel successfully.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_InsertAt(pIArrayModel,nIndex,pvItem) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->InsertAt(pIArrayModel,nIndex,pvItem)
#else
__INLINE MAE_Ret IARRAYMODEL_InsertAt(IArrayModel *pIArrayModel, u32 nIndex, void *pItem)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->InsertAt(pIArrayModel,nIndex,pItem);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_DeleteAt
* @brief   This function delete the specific item from the arraymodel.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (u32)nIndex                      A zero-base index of the position which will be removed.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           Wrong index.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_DeleteAt(pIArrayModel,nIndex) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->DeleteAt(pIArrayModel,nIndex)
#else
__INLINE MAE_Ret IARRAYMODEL_DeleteAt(IArrayModel *pIArrayModel, u32 nIndex)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->DeleteAt(pIArrayModel,nIndex);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_DeleteAll
* @brief   This function clear all items of the arraymodel.
*
* @param[in]   (IArrayModel*)pIArrayModel     A pointer of IArrayModel interface object.
*
* @retval  None.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_DeleteAll(pIArrayModel) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->DeleteAll(pIArrayModel)
#else
__INLINE void IARRAYMODEL_DeleteAll(IArrayModel *pIArrayModel)
{
	GET_FUNCTBL((pIArrayModel),IArrayModel)->DeleteAll(pIArrayModel);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_EnsureCapacity
* @brief   This function ensure the capacity (size) of the arraymodel, including the initial size and
*          the growth size.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (u32)nRequired                   Initial size. If the size of arraymodel is small than users'
*                                               requirement, it will allocate a memory buffer with size as
*                                               (nRequired x Item Size).
* @param[in]   (u32)nGrowBy                     Growth size. When users insert a new item into the arraymodel
*                                               and there's no more free slot to insert, it will enlarge the arraymodel
                                                with nGrowBy slots at a time.
*
* @retval  MAE_RET_SUCCESS             Successfully.
* @retval  MAE_RET_BAD_PARAM           nGrowBy is zero.
* @retval  MAE_RET_OUT_OF_MEMORY       Insufficient memory.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_EnsureCapacity(pIArrayModel,nRequired,nGrowBy) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->EnsureCapacity(pIArrayModel,nRequired,nGrowBy)
#else
__INLINE MAE_Ret IARRAYMODEL_EnsureCapacity(IArrayModel *pIArrayModel, u32 nRequired, u32 nGrowBy)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->EnsureCapacity(pIArrayModel,nRequired,nGrowBy);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
* IARRAYMODEL_SetPfnFree
* @brief   This function set the free function of the arraymodel, and it will be used when each item
*          is removed from the arraymodel.
*
* @param[in]   (IArrayModel*)pIArrayModel       A pointer of IArrayModel interface object.
* @param[in]   (PfnModelFree)pfn          A free function pointer to free data.
* @param[in]   (IBase*)pItemOwner               Shall be an IBase interface object to keep the return object.
*
* @retval  ListModelFree_t        The older free function pointer if available.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_SetPfnFree(pIArrayModel,pfn,pItemOwner) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->SetPfnFree(pIArrayModel,pfn,pItemOwner)
#else
__INLINE ListModelFree_t IARRAYMODEL_SetPfnFree(IArrayModel *pIArrayModel, PfnModelFree pfn, IBase *pItemOwner)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->SetPfnFree(pIArrayModel,pfn,pItemOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */












// helper
#define IARRAYMODEL_Add(p,pv) \
	IARRAYMODEL_InsertAt(p,ARRAY_LAST,pv)


/*
 * @par IARRAYMODEL_SetItemByteSize:
 * <PRE>
 *       This function will set the item byte size for the further insert item
 *       (1) delete all the items that has been inserted before
 *           a. call the Free function if user has set the IARRAYMODEL_SetPfnFree
 *           b. free the items
 *       (2) Reset the item byte size as the parameter nItemByteSize
 *       (3) The ensure capacity will reset as 0
 *
 * </PRE>
 * @par Prototype:
 *           void IARRAYMODEL_SetItemByteSize(IArrayModel *pIArrayModel, u32 nItemByteSize);
 *
 * @param[in] pIArrayModel      Pointer to the IArrayModel interface object.
 * @param[in] nItemByteSize     The new byte size of each items further insert in the array model
 *
 * @retval None
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_SetItemByteSize(pIArrayModel,nItemByteSize) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->SetItemByteSize(pIArrayModel,nItemByteSize)
#else
__INLINE void IARRAYMODEL_SetItemByteSize(IArrayModel *pIArrayModel, u32 nItemByteSize)
{
	GET_FUNCTBL((pIArrayModel),IArrayModel)->SetItemByteSize(pIArrayModel,nItemByteSize);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


#ifndef __MAE_VENEERED_INTERFACE__
#define IARRAYMODEL_GetItemByteSize(pIArrayModel) \
	GET_FUNCTBL((pIArrayModel),IArrayModel)->GetItemByteSize(pIArrayModel)
#else
__INLINE u32 IARRAYMODEL_GetItemByteSize(IArrayModel *pIArrayModel)
{
	return GET_FUNCTBL((pIArrayModel),IArrayModel)->GetItemByteSize(pIArrayModel);
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/*=============================================================*/
// functions
/*=============================================================*/
//common function
void IARRAYMODEL_ChangeContentNotifyAt(IArrayModel *pIArrayModel, u32 nIndex);

#endif //__MAE_ARRAYMODEL_H__
/*=============================================================*/
// end of file
