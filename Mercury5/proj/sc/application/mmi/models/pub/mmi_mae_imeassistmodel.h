/**
* @file    mae_imeassistmodel.h
* @brief   This file defines the interface of imeassistmodel.
* 
* @version $Id: mae_imeassistmodel.h 38890 2009-08-29 16:22:38Z zinc.chen $
*/
#ifndef __MMI_MAE_IMEASSISTMODEL_H__
#define __MMI_MAE_IMEASSISTMODEL_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
IMEASST_COMPNT_ID_CS = 0,        ///< Input Candidate selection widget
IMEASST_COMPNT_MY_WORD,
#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
IMEASST_COMPNT_ID_SKB,        ///< SoftKeyboard widget
#endif //__IME_MMI_SOFTKEYBOARD__
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
IMEASST_COMPNT_ID_SKBHIGHLIGHT,        ///< SoftKeyboard highlight widget
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
IMEASST_COMPNT_ID_INPUTLIST, ///< Input Method list widget
IMEASST_COMPNT_ID_INPUTTOOLBOX, ////<Input toolbox
#endif

IMEASST_COMPNT_SUM
};

#define IMEASST_COMPNT_MSK(_id)   (1<<_id)

typedef struct
{
    boolean bVisible;           ///< visible property of the component widget
    boolean bFixedPostion;      ///< position is fixed or not of the component widget
    s32 PosX;               ///< start X position of the component widget, relative to RootContainer's coordinate if bFixedPostion is FALSE. else, relative to IMEAssistWidget.
    s32 PosY;               ///< start Y position of the component widget, relative to RootContainer's coordinate if bFixedPostion is FALSE. else, relative to IMEAssistWidget.
} IMEAsstWdgProp_t;

typedef struct
{
    IMEAsstWdgProp_t PropData[IMEASST_COMPNT_SUM];
} IMEAsstAllProp_t;

/*=============================================================*/
// interface
/*=============================================================*/
/**
 * INHERIT_IIMEAssistModel
 * @brief   INHERIT_IIMEAssistModel is IIMEAssistModel interface inheritance definition.
 */
#define INHERIT_IIMEAssistModel(IName) \
    INHERIT_IModel(IName); \
    MAE_Ret  (*SetPropData)    (IName *, u32, IMEAsstWdgProp_t*, boolean); \
    MAE_Ret  (*GetCurProp)     (IName *, IMEAsstAllProp_t*); \
    MAE_Ret  (*SetAsstWidget)  (IName *, u32, void*);\
    MAE_Ret  (*GetAsstWidget)  (IName *, u32, void**, IBase*)

//Here define IIMEAssistModel interface
DEFINE_INTERFACE( IIMEAssistModel );

/*=============================================================*/
// methods of IIMEAssistModel
/*=============================================================*/

/**
 * IIMEASSISTMODEL_QueryInterface(IIMEAssistModel *pIMEAsstModel, MAE_IId id, void **pp,IBase *pOwner)
 *
 * @brief   This function queries another interface from an IIMEAssistModel object. 
 *          It will return an interface object which you want to query if successful.
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel A pointer of IIMEAssistModel interface object.
 * @param   (MAE_IId)id                     An interface id to be queried.
 * @param   (void**)pp                      A pointer of void pointer to retrieve an interface object which you want to query.
 * @param   (IBase*)pOwner                  Shall be an IBase interface object to keep the return object.
 *
 * @retval  MAE_RET_SUCCESS         Successfully.
 * @retval  MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
 *
 * @note    Only support IID_IMEASSISTMODEL and IID_MODEL.
 */
#define IIMEASSISTMODEL_QueryInterface(pIMEAsstModel,id,pp,pOwner) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->QueryInterface(pIMEAsstModel,id,pp,pOwner)


/**
 * IIMEASSISTMODEL_SendNotify(IIMEAssistModel *pIIMEAssistModel, ModelEvent_t *pMdlEvt)
 *
 * @brief   This function sends the notify to all listeners which registered to this model. 
 *          An application or object could register listener by IMODEL_AddMdlListener()/IIMEASSISTMODEL_AddMdlListener() 
 *          to a specific model. When the model state is changed(such as data changed), the 
 *          model would notify all listeners by IMODEL_SendNotify()/IIMEASSISTMODEL_SendNotify().
 *
 * @param   (IIMEAssistModel*)pIIMEAssistModel        A pointer of IIMEAssistModel interface object.
 * @param   (ModelEvent_t*)pMdlEvt          A pointer to ModelEvent_t sturcture to indicate which event is 
 *                                          occured and what kind of data is changed.
 *
 * @retval  None.
 */
#define IIMEASSISTMODEL_SendNotify(pIIMEAssistModel,pMdlEvt) \
        GET_FUNCTBL((pIIMEAssistModel),IIMEAssistModel)->SendNotify(pIIMEAssistModel,pMdlEvt)


/**
 * IIMEASSISTMODEL_AddMdlListener(IIMEAssistModel *pIMEAsstModel, ModelListener_t *pMdlLsn)
 *
 * @brief   This function registers a listener to this model object.
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel  A pointer of IIMEAssistModel interface object.
 * @param   (ModelListener_t*)pMdlLsn           A pointer to ModelListener_t sturcture that will register to this model object.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#define IIMEASSISTMODEL_AddMdlListener(pIMEAsstModel,pMdlLsn) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->AddMdlListener(pIMEAsstModel,pMdlLsn)

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_AddEvtListener(pIIMEAssistModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pIIMEAssistModel),IIMEAssistModel)->AddEvtListener(pIIMEAssistModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_AddEvtListener( IIMEAssistModel *pIIMEAssistModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pIIMEAssistModel ) , IIMEAssistModel )->AddEvtListener( pIIMEAssistModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */


#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_CancelEvtListener(pIIMEAssistModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pIIMEAssistModel),IIMEAssistModel)->CancelEvtListener(pIIMEAssistModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_CancelEvtListener( IIMEAssistModel *pIIMEAssistModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pIIMEAssistModel ) , IIMEAssistModel )->CancelEvtListener( pIIMEAssistModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_CancelEvtAllListener(pIIMEAssistModel,nEvtCode) \
    GET_FUNCTBL((pIIMEAssistModel),IIMEAssistModel)->CancelEvtAllListener(pIIMEAssistModel,nEvtCode)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_CancelEvtAllListener( IIMEAssistModel *pIIMEAssistModel, ModelEvtCode_t nEvtCode )
{
    return GET_FUNCTBL( ( pIIMEAssistModel ) , IIMEAssistModel )->CancelEvtAllListener( pIIMEAssistModel , nEvtCode );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * IIMEASSISTMODEL_SetPropData(IIMEAssistModel *pIMEAsstModel, u32 id, IMEAsstWdgProp_t *pData)
 *
 * @brief   This function provides a functionality to set properties of widgets in IMEAssistWidget
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel   A pointer of IIMEAssistModel interface object.
 * @param   (u32)id                           Widget ID of the new property.
 * @param   (IMEAsstWdgProp_t*)pData          A pointer proprty data.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 *
 * @note    This function will cause sending EVT_MDL_DATA_CHANGE notification.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_SetPropData(pIMEAsstModel,id,pData) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->SetPropData(pIMEAsstModel,id,pData,TRUE)
#define IIMEASSISTMODEL_SetPropDataEx(pIMEAsstModel,id,pData,bNtfy) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->SetPropData(pIMEAsstModel,id,pData,bNtfy)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_SetPropDataEx( IIMEAssistModel *pIMEAsstModel, u32 id, IMEAsstWdgProp_t *pData, boolean bNtfy )
{
    return GET_FUNCTBL( ( pIMEAsstModel ) , IIMEAssistModel )->SetPropData( pIMEAsstModel , id , pData , bNtfy );
}
#define IIMEASSISTMODEL_SetPropData(pIMEAsstModel,id,pData) \
        IIMEASSISTMODEL_SetPropDataEx(pIMEAsstModel,id,pData,TRUE)
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * IIMEASSISTMODEL_GetCurProp(IIMEAssistModel *pIMEAsstModel, IMEAsstAllProp_t *pData)
 *
 * @brief   This function can retrieve all properties of widgets in the IMEAssistWidget
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel   A pointer of IIMEAssistModel interface object.
 * @param   (IMEAsstAllProp_t*)pData          A pointer of struct IMEAsstAllProp_t retrieve
 *                                            properties of widgets.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_GetCurProp(pIMEAsstModel,pData) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->GetCurProp(pIMEAsstModel,pData)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_GetCurProp( IIMEAssistModel *pIMEAsstModel, IMEAsstAllProp_t *pData )
{
    return GET_FUNCTBL( ( pIMEAsstModel ) , IIMEAssistModel )->GetCurProp( pIMEAsstModel , pData );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/**
 * IIMEASSISTMODEL_SetAsstWidget(IIMEAssistModel *pIMEAsstModel, u32 id, void *pWdgObj)
 *
 * @brief   Set assist widget to this IIMEAssistModel object.
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel   A pointer of IIMEAssistModel interface object.
 * @param   (u32)id                           Assist widget ID.
 * @param   (void*)pWdgObj                    The object of assist widgets.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_SetAsstWidget(pIMEAsstModel,id,pWdg) \
    GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->SetAsstWidget(pIMEAsstModel,id,pWdg)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_SetAsstWidget( IIMEAssistModel *pIMEAsstModel, u32 id, void *pWdg )
{
    return GET_FUNCTBL( ( pIMEAsstModel ) , IIMEAssistModel )->SetAsstWidget( pIMEAsstModel , id , pWdg );
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/**
 * IIMEASSISTMODEL_GetAsstWidget(IIMEAssistModel *pIMEAsstModel, u32 id, void **pp, IBase *pOwner)
 *
 * @brief   This function can retrieve a pointer of data which keeps in this datamodel.
 *
 * @param   (IIMEAssistModel*)pIMEAsstModel   A pointer of IIMEAssistModel interface object.
 * @param   (u32)id                           Widget ID.
 * @param   (void**)pp                        A double pointer to retrieve the widget pointer.
 * @param   (IBase*)pOwner                    The owner of the object instance.
 *
 * @retval  MAE_RET_SUCCESS     Successfully.
 * @retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
 */
#ifndef __MAE_VENEERED_INTERFACE__
#define IIMEASSISTMODEL_GetAsstWidget(pIMEAsstModel,id,pp,pOwner) \
        GET_FUNCTBL((pIMEAsstModel),IIMEAssistModel)->GetAsstWidget(pIMEAsstModel,id,pp,pOwner)
#else
__INLINE MAE_Ret IIMEASSISTMODEL_GetAsstWidget( IIMEAssistModel *pIMEAsstModel, u32 id, void **pp, IBase *pOwner )
{
    return GET_FUNCTBL( ( pIMEAsstModel ) , IIMEAssistModel )->GetAsstWidget( pIMEAsstModel , id , pp , pOwner );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

#endif /* __MMI_MAE_IMEASSISTMODEL_H__ */
