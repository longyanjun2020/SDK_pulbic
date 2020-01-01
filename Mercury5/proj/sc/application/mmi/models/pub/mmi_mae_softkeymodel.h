/**
 * @file    mae_softkeymodel.h
 * @author  steve.lee@mstarsemi.com
 *
 * @version $Id: mae_softkeymodel.h 38890 2009-08-29 16:22:38Z zinc.chen $
 * 
 * @brief   This file defines the interface of softkey model.
 *
 * <Interface Description>
 *     ISoftkeyModel is an interface to provide a mechanism to save the softkey id in every different view.
 *     It inherits from IModel and add interface methods to set and get different type of softkey id.
 *
 * <Interface ID>
 *     IID_SOFTKEYMODEL
 *
 * <Model Notification Event>
 *     =======================
 *     EVT_SKMDL_SKCHANGE: While the softkey id kept in softkey-model has changed, model event notifies this
 *                         event code. The value of dwParam in ModelEvent_t is the combination of 
 *                         MASK_LEFT_SOFTKEY_CHANGE, MASK_MIDDLE_SOFTKEY_CHANGE, and MASK_RIGHT_SOFTKEY_CHANGE.
 *
 * <Class Description>
 *     The CLSID_SOFTKEYMODEL class implements ISoftkeyModel interface. User can create a CLSID_SOFTKEYMODEL 
 *     class object via MAE_Shell by ISHELL_CreateInstance().
 *
 * <Class ID>
 *     CLSID_SOFTKEYMODEL
 *
 */
#ifndef __MMI_MAE_SOFTKEYMODEL_H__
#define __MMI_MAE_SOFTKEYMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum
{
LEFT_SK = 0,
MIDDLE_SK,
RIGHT_SK,
NUM_SK
} Softkey_Type;

typedef struct
{
    u32 nFirstIndex;            /* the absolutely index of first item on screen */
    u32 nHighlightedIndex;      /* the absolutely index of the highlighted item */
    u32 nSelectedID;            /* the item ID of the highlighted item */
} MaeSoftkeyMenuInf_t;

typedef struct
{
    u32 u32SoftkeyId;
    MaeSoftkeyMenuInf_t *psMenuExtInf;
} MaeSoftkeyEventInf_t;

#define MASK_LEFT_SOFTKEY_CHANGE        (1<<LEFT_SK)
#define MASK_MIDDLE_SOFTKEY_CHANGE      (1<<MIDDLE_SK)
#define MASK_RIGHT_SOFTKEY_CHANGE       (1<<RIGHT_SK)

#define GET_SOFTKEY_CHANGE_MASK_BY_TYPE(type)   (1<<type)

/*=============================================================*/
// interface
/*=============================================================*/
/**
 * INHERIT_ISoftkeyModel
 * @brief   INHERIT_ISoftkeyModel is ISoftkeyModel interface inheritance definition.
 */
#define INHERIT_ISoftkeyModel(IName) \
    INHERIT_IModel(IName); \
	MAE_Ret  (*GetEvtFirstListener)    (IName*, ModelEvtCode_t, PfnModelEvtListener*, void**, void**);\
    MAE_Ret  (*SetSoftkey)    (IName*, u32, u32);\
    MAE_Ret  (*GetSoftkey)    (IName*, u32, u32*);\
    boolean  (*SendEvtNotify) (IName*, ModelEvent_t*); \
    MAE_Ret  (*SetMenuExtInf) (IName*, MaeSoftkeyMenuInf_t*); \
    MAE_Ret  (*GetMenuExtInf) (IName*, MaeSoftkeyMenuInf_t**)

//Here define ISoftkeyModel interface
DEFINE_INTERFACE( ISoftkeyModel );


/*=============================================================*/
// methods of ISoftkeyModel
/*=============================================================*/

/**
 * ISOFTKEYMODEL_QueryInterface
 * @brief   This function queries another interface from an ISoftkeyModel object. 
 *          It will return an interface object which you want to query if successful.
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (MAE_IId)id                     An interface id to be queried.
 * @param   (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
 * @param   (IBase*)pOwner                  Shall be an IBase interface object to keep the return object.
 *
 * @retval  MAE_RET_SUCCESS         Successfully.
 * @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
 *
 * @note    Only support IID_SOFTKEYMODEL and IID_MODEL.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_QueryInterface(pSKModel,id,pp,pOwner) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->QueryInterface(pSKModel,id,pp,pOwner)
#else
__INLINE MAERet_t ISOFTKEYMODEL_QueryInterface( ISoftkeyModel *pSKModel, MAEIId_t id, void **pp, IBase *pOwner )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->QueryInterface( pSKModel , id , pp , pOwner );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * ISOFTKEYMODEL_SendNotify
 * @brief   This function sends the notify to all listeners which registered to this model. 
 *          An application or object could register listener by IMODEL_AddMdlListener()/ISOFTKEYMODEL_AddMdlListener() 
 *          to a specific model. When the model state is changed(such as data changed), the 
 *          model would notify all listeners by IMODEL_SendNotify()/ISOFTKEYMODEL_SendNotify().
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (ModelEvent_t*)pMdlEvt          A pointer to ModelEvent_t sturcture to indicate which event is 
 *                                          occured and what kind of data is changed.
 *
 * @retval  None.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_SendNotify(pSKModel,pMdlEvt) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->SendNotify(pSKModel,pMdlEvt)
#else
__INLINE void ISOFTKEYMODEL_SendNotify( ISoftkeyModel *pSKModel, ModelEvent_t *pMdlEvt )
{
    GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->SendNotify( pSKModel , pMdlEvt );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * ISOFTKEYMODEL_AddMdlListener
 * @brief   This function registers a listener to this model object.
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (ModelListener_t*)pMdlLsn       A pointer to ModelListener_t sturcture that will register to this model object.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_AddMdlListener(pSKModel,pMdlLsn) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->AddMdlListener(pSKModel,pMdlLsn)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_AddMdlListener( ISoftkeyModel *pSKModel, ModelListener_t *pMdlLsn )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->AddMdlListener( pSKModel , pMdlLsn );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_AddEvtListener(pISoftkeyModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pISoftkeyModel),ISoftkeyModel)->AddEvtListener(pISoftkeyModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_AddEvtListener( ISoftkeyModel *pISoftkeyModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pISoftkeyModel ) , ISoftkeyModel )->AddEvtListener( pISoftkeyModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

//#define ISOFTKEYMODEL_CancelMdlListener(pSKModel,pMdlLsn) \
//  GET_FUNCTBL((pSKModel),ISoftkeyModel)->CancelMdlListener(pSKModel,pMdlLsn)
// use MDLLISTENER_CANCEL() instead //
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_CancelEvtListener(pISoftkeyModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pISoftkeyModel),ISoftkeyModel)->CancelEvtListener(pISoftkeyModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_CancelEvtListener( ISoftkeyModel *pISoftkeyModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pISoftkeyModel ) , ISoftkeyModel )->CancelEvtListener( pISoftkeyModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_CancelEvtAllListener(pISoftkeyModel,nEvtCode) \
    GET_FUNCTBL((pISoftkeyModel),ISoftkeyModel)->CancelEvtAllListener(pISoftkeyModel,nEvtCode)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_CancelEvtAllListener( ISoftkeyModel *pISoftkeyModel, ModelEvtCode_t nEvtCode )
{
    return GET_FUNCTBL( ( pISoftkeyModel ) , ISoftkeyModel )->CancelEvtAllListener( pISoftkeyModel , nEvtCode );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * ISOFTKEYMODEL_SetSoftkey
 * @brief   This function set the softkey value to softkey-model
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (u32)type                       Softkey type, please refer to Softkey_Type in mae_softkey.h
 * @param   (u32)id                         Softkey id, please refer to SoftkeyID_e in mae_softkey.h
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_SetSoftkey(pSKModel,type,id) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->SetSoftkey(pSKModel, type, id)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_SetSoftkey( ISoftkeyModel *pSKModel, u32 type, u32 id )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->SetSoftkey( pSKModel , type , id );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * ISOFTKEYMODEL_GetSoftkey
 * @brief   This function get the softkey value from softkey-model
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (u32)type                       Softkey type, please refer to Softkey_Type in mae_softkey.h
 * @param   (u32*)pid                       An u32 pointer to retrieve Softkey id, please refer to SoftkeyID_e in mae_softkey.h
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_GetSoftkey(pSKModel,type,pid) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->GetSoftkey(pSKModel, type, pid)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_GetSoftkey( ISoftkeyModel *pSKModel, u32 type, u32 *pid )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->GetSoftkey( pSKModel , type , pid );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * ISOFTKEYMODEL_SendEvtNotify
 * @brief   This function sends the notify to all listeners which registered to this model. 
 *          An application or object could register listener by IMODEL_AddMdlListener()/ISOFTKEYMODEL_AddMdlListener() 
 *          to a specific model. When the model state is changed(such as data changed), the 
 *          model would notify all listeners by IMODEL_SendNotify()/ISOFTKEYMODEL_SendNotify().
 *
 * @param   (ISoftkeyModel*)pSKModel        A pointer of ISoftkeyModel interface object.
 * @param   (ModelEvent_t*)pMdlEvt          A pointer to ModelEvent_t sturcture to indicate which event is 
 *                                          occured and what kind of data is changed.
 *
 * @retval  None.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_SendEvtNotify(pSKModel,pMdlEvt) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->SendEvtNotify(pSKModel,pMdlEvt)
#else
__INLINE boolean ISOFTKEYMODEL_SendEvtNotify( ISoftkeyModel *pSKModel, ModelEvent_t *pMdlEvt )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->SendEvtNotify( pSKModel , pMdlEvt );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_SetMenuExtInf(pSKModel,pMenuExtInf) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->SetMenuExtInf(pSKModel,pMenuExtInf)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_SetMenuExtInf( ISoftkeyModel *pSKModel, MaeSoftkeyMenuInf_t *pMenuExtInf )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->SetMenuExtInf( pSKModel , pMenuExtInf );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_GetMenuExtInf(pSKModel,ppMenuExtInf) \
    GET_FUNCTBL((pSKModel),ISoftkeyModel)->GetMenuExtInf(pSKModel,ppMenuExtInf)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_GetMenuExtInf( ISoftkeyModel *pSKModel, MaeSoftkeyMenuInf_t **ppMenuExtInf )
{
    return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->GetMenuExtInf( pSKModel , ppMenuExtInf );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define ISOFTKEYMODEL_GetEvtFirstListener(pSKModel,nEvtCode,ppfnEvtListener,ppUserData1,ppUserData2) \
	GET_FUNCTBL((pSKModel),ISoftkeyModel)->GetEvtFirstListener(pSKModel,nEvtCode,ppfnEvtListener,ppUserData1,ppUserData2)
#else
__INLINE MAE_Ret ISOFTKEYMODEL_GetEvtFirstListener( ISoftkeyModel *pSKModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener *ppfnEvtListener, void **ppUserData1, void **ppUserData2 )
{
	return GET_FUNCTBL( ( pSKModel ) , ISoftkeyModel )->GetEvtFirstListener( pSKModel ,nEvtCode, ppfnEvtListener, ppUserData1, ppUserData2 );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/*=============================================================*/
// functions
/*=============================================================*/


#endif //__MMI_MAE_SOFTKEYMODEL_H__
/*=============================================================*/
// end of file
