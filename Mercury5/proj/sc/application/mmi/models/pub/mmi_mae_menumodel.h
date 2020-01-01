/**
 * @file    mae_menumodel.h
 * @brief   This file defines the interface of menu-model.
 * 
 * @version $Id: mae_menumodel.h 38890 2009-08-29 16:22:38Z zinc.chen $
 */
#ifndef __MMI_MAE_MENUMODEL_H__
#define __MMI_MAE_MENUMODEL_H__

#define __SMART_MENUMODEL__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_mae_softkey.h"
#include "Mmi_mae_softkeymodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define MENUMDL_LAST        (u32) 0xFFFFFFFF
#define MENUMDL_NOTIFY      (boolean) TRUE
#define MENUMDL_DIF_ENTITY  8
#define MENUMDL_MAX_ENTITY  (MENUMDL_DIF_ENTITY * 4)
#define MENUMDL_GROWBY      MENUMDL_DIF_ENTITY
#define MENUMDL_ISDATAMDL   0x10

#define MANUMDL_INVALID_INDEX 0xFFFFFFFF

/**
* Flag Mask
*/
enum
{
MENUMODEL_FLAG_ITEM_VISABLE = 0,
MENUMODEL_FLAG_ITEM_UNSELECTABLE,
MENUMODEL_FLAG_ITEM_SELECTED,
MENUMODEL_FLAG_ITEM_HAS_CHILD,
MENUMODEL_FLAG_ITEM_ONLY_BG,
MENUMODEL_FLAG_ITEM_HIDE_MARK_ICON,
MENUMODEL_FLAG_END
};  //Note: MENUMODEL_FLAG_END is 4 now.

typedef u32 ItemFlag_t;
#define MENUMODEL_ITEM_HIDE         0
#define MENUMODEL_ITEM_VISABLE      (1<<MENUMODEL_FLAG_ITEM_VISABLE)        /* indicate the item can be displayed or not */
#define MENUMODEL_ITEM_UNSELECTABLE (1<<MENUMODEL_FLAG_ITEM_UNSELECTABLE)   /* indicate the item can be displayed but can't be selected or highlighted */
#define MENUMODEL_ITEM_SELECTED     (1<<MENUMODEL_FLAG_ITEM_SELECTED)       /* indicate the item has been selected or marked */
#define MENUMODEL_ITEM_HAS_CHILD    (1<<MENUMODEL_FLAG_ITEM_HAS_CHILD)      /* indicate the item has sub menu */
#define MENUMODEL_ITEM_ONLY_BG      (1<<MENUMODEL_FLAG_ITEM_ONLY_BG)        /* indicate the item only display background */
#define MENUMODEL_ITEM_HIDE_MARK_ICON      (1<<MENUMODEL_FLAG_ITEM_HIDE_MARK_ICON)        /* indicate the item hide mark icon */
#define MENUMODEL_ITEM_ALL          0xFFFF                                  /* enable all the flag */

/**
* Macro to get flag value
*/
#define MENUMODEL_IS_ITEM_VISABLE(_flag) \
    (boolean)((_flag&MENUMODEL_ITEM_VISABLE)>>MENUMODEL_FLAG_ITEM_VISABLE)
#define MENUMODEL_IS_ITEM_UNSELECTABLE(_flag) \
    (boolean)((_flag&MENUMODEL_ITEM_UNSELECTABLE)>>MENUMODEL_FLAG_ITEM_UNSELECTABLE)
#define MENUMODEL_IS_ITEM_SELECTED(_flag) \
    (boolean)((_flag&MENUMODEL_ITEM_SELECTED)>>MENUMODEL_FLAG_ITEM_SELECTED)
#define MENUMODEL_IS_ITEM_HAS_CHILD(_flag) \
    (boolean)((_flag&MENUMODEL_ITEM_HAS_CHILD)>>MENUMODEL_FLAG_ITEM_HAS_CHILD)
#define MENUMODEL_IS_ITEM_ONLY_BG(_flag) \
    (boolean)((_flag&MENUMODEL_ITEM_ONLY_BG)>>MENUMODEL_FLAG_ITEM_ONLY_BG)    
#define MENUMODEL_IS_ITEM_HIDE_MARK_ICON(_flag) \
	(boolean)((_flag&MENUMODEL_ITEM_HIDE_MARK_ICON)>>MENUMODEL_FLAG_ITEM_HIDE_MARK_ICON)    

/**
* Macro to Set flag value
*/
#define MENUMODEL_SET_ITEM_VISABLE(_flag, _b) \
    (ItemFlag_t)((_flag&(~MENUMODEL_ITEM_VISABLE))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_VISABLE))
#define MENUMODEL_SET_ITEM_UNSELECTABLE(_flag, _b) \
    (ItemFlag_t)((_flag&(~MENUMODEL_ITEM_UNSELECTABLE))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_UNSELECTABLE))
#define MENUMODEL_SET_ITEM_SELECTED(_flag, _b) \
    (ItemFlag_t)((_flag&(~MENUMODEL_ITEM_SELECTED))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_SELECTED))
#define MENUMODEL_SET_ITEM_HAS_CHILD(_flag, _b) \
    (ItemFlag_t)((_flag&(~MENUMODEL_ITEM_HAS_CHILD))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_HAS_CHILD))
#define MENUMODEL_SET_ITEM_ONLY_BG(_flag, _b) \
    (ItemFlag_t)((_flag&(~MENUMODEL_ITEM_ONLY_BG))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_ONLY_BG))   
#define MENUMODEL_SET_ITEM_HIDE_MARK_ICON(_flag, _b) \
	(ItemFlag_t)((_flag&(~MENUMODEL_ITEM_HIDE_MARK_ICON))|(((u32)_b)<<MENUMODEL_FLAG_ITEM_HIDE_MARK_ICON))   

enum
{
MENU_VECTOR_DATA = LIST_DATATYPE_SUM
};

typedef u32 MenuItemAccessType_t;
enum MenuItemAccessType_tag
{
MENUMODEL_ITEMTYPE_GET_START = 0,
MENUMODEL_GETITEMINDEX = MENUMODEL_ITEMTYPE_GET_START,
MENUMODEL_GETITEMID,
MENUMODEL_GETITEMFLAG,
MENUMODEL_GETITEMSK,
MENUMODEL_ITEMTYPE_SET_START,
MENUMODEL_SETITEMID = MENUMODEL_ITEMTYPE_SET_START,
MENUMODEL_SETITEMFLAG,
MENUMODEL_CLEARITEMFLAG,
MENUMODEL_CLEARALLITEFLAG,
MENUMODEL_SETITEMSK,
MENUMODEL_SETITEMVISIBLE,
MENUMODEL_SETITEMVISIBLE_BYID,
MENUMODEL_TOGGLEITEM,
MENUMODEL_TOUCHITEM,
MENUMODEL_SETITEMDISPBGONLY,
MENUMODEL_ITEMTYPE_SUM
};

typedef enum
{
CHECK_RADIO_STYLE_START = 0x00,
CHECK_RADIO_STYLE_NONE = 0x00,
CHECK_RADIO_STYLE_CHECK,
CHECK_RADIO_STYLE_MARK,
CHECK_RADIO_STYLE_ACTIVATE,
CHECK_RADIO_STYLE_RADIO,
CHECK_RADIO_STYLE_CAMERA_MARK,
CHECK_RADIO_STYLE_HIDE_RADIO,
CHECK_RADIO_STYLE_TOTAL,
CHECK_RADIO_STYLE_MASK = 0x0F
}Item_Style_e;

// Event that the menu model sends out on changes
typedef struct
{
    ModelEvent_t MEvtBase;    ///< model event base structure
    u32 pos;      ///< position at which change occurred
    u32 oldSize;  ///< old size of list
    u32 newSize;  ///< new size of list
} MenuModelEvent_t;

// Menu model structure (w/o index)
typedef struct
{
    ItemFlag_t eItemFlags;      //item flag: reference to ItemFlag_t
    u32 nSoftkey[NUM_SK];
    u32 u32UserData;
    u32 nItemId;                //item id: menu id for static menu
    void *pItemData;
} MenuModelData_t;

// Menu model structure (w/ index)
typedef struct
{
    void *pItemData;
    u32 nIndex;
} MenuModelIdxData_t;

// Menu model entity structure
typedef struct
{
    u32 nFirstEntityIdx;
    u32 nLastEntityIdx;
} MenuModelEntityData_t;

typedef struct
{
    u32 nIndex;
    ItemFlag_t eItemFlag;
} MenuModelFlagChangeData_t;

#define MENUMODELEVENT_Init(pe,c,dwp,p,oldS,newS) { (pe)->MEvtBase.nEvtCode=c; (pe)->MEvtBase.nParam=dwp; (pe)->pos=p; (pe)->oldSize=oldS; (pe)->newSize=newS; }

/*=============================================================*/
// interface
/*=============================================================*/
/* the free data function prototype for menu-model */
typedef void ( *MENUMODEL_FREE_FUNC_PTR ) ( void *pData, void *pUserData, u16 nIndex, IBase *pOwner );

//adapt get function prototype
typedef void ( *MENUMODEL_ADAPTGET_FUNC_PTR ) ( void **ppDataOut, void *pUserData, u16 nIndex );

//adapt get function prototype
typedef void ( *MENUMODEL_ADAPTGET_FREE_FUNC_PTR ) ( void *pData, void *pUserData, IBase *pOwner );

//adapt get function prototype
typedef void ( *MENUMODEL_ADAPTGET_FREE_USER_DATA_FUNC_PTR ) ( void *pUserData );


// IMenuModel interface
#define INHERIT_IMenuModel(IName) \
    INHERIT_IVectorModel(IName); \
    void (*SetAdaptGet)             (IName *po, MENUMODEL_ADAPTGET_FUNC_PTR pAdaptGetFunc, void *pUserData); \
    void (*SetAdaptGetEx)           (IName *po, MENUMODEL_ADAPTGET_FUNC_PTR pAdaptGetFunc); \
    void (*SetAdaptGetFree)         (IName *po, MENUMODEL_ADAPTGET_FREE_FUNC_PTR pAdaptGetFunc); \
    void (*SetAdaptGetUserData)     (IName *po, MENUMODEL_ADAPTGET_FREE_USER_DATA_FUNC_PTR pAdaptGetFreeUserDataFunc, void *pUserData); \
    void* (*GetAdaptGetUserData)    (IName *po); \
    void (*SetTotalSize)            (IName *po, u32 nTotalSize); \
    void (*GetTotalSize)            (IName *po, u32 *pnTotalSize); \
    MAE_Ret (*UpdateAt)             (IName *po, u32 nIndex, boolean bNotify); \
    MAE_Ret (*AccessItemData)       (IName *po, MenuItemAccessType_t nType, u32 nItm, u32 nData); \
    MAE_Ret (*AccessItemSK)         (IName *po, MenuItemAccessType_t nType, u32 nIndex, Softkey_Type eSKType, u32 nData, boolean bNotify); \
    MAE_Ret (*AccessItemAllSK)      (IName *po, MenuItemAccessType_t nType, u32 nIndex, u32 nLSK, u32 nCSK, u32 nRSK); \
    void (*IsDataModel)             (IName *po, boolean bIsDataModel); \
    void (*SetModelStyle)           (IName *po, u8 nModelStyle); \
    void (*GetCheckStatus)          (IName *po, boolean **ppCheckStatus); \
    void (*SetCheckStatus)          (IName *po, boolean *pCheckStatus); \
    void (*GetEntityIndex)          (IName *po, MenuModelEntityData_t *pstEntityIdx); \
    void (*SetCacheInfo)            (IName *po, u16 nDiffEntity, u16 nMaxEntity); \
    MAE_Ret (*ClearCachedEntities)  (IName *po); \
    MAE_Ret (*ClearCachedUserData)  (IName *po); \
    boolean (*InCachedData)         (IName *po, u32 u32Index); \
    u32 (*GetRealIndex)             (IName *po, u32 u32Index); \
    u32 (*GetDisplayIndex)          (IName *po, u32 u32RealIndex); \
    u32 (*GetDisplaySize)           (IName *po); \
    boolean (*IsStaticMenu)         (IName *po); \
    void (*SetModelType)            (IName *po, u32 u32ModelType); \
    u32 (*GetModelType)             (IName *po)

DEFINE_INTERFACE( IMenuModel );

#define IMENUMODEL_TO_IVECTORMODEL(p) ((IVectorModel*)p)

#ifndef __MAE_VENEERED_INTERFACE__
// IModel interface
#define IMENUMODEL_QueryInterface(pIMenuModel,id,pp,pOwner) GET_FUNCTBL((pIMenuModel),IMenuModel)->QueryInterface(pIMenuModel,id,pp,pOwner)
#define IMENUMODEL_SendNotify(pIMenuModel,pMdlEvt)          GET_FUNCTBL((pIMenuModel),IMenuModel)->SendNotify(pIMenuModel,pMdlEvt)
#define IMENUMODEL_AddMdlListener(pIMenuModel,pMdlLsn)      GET_FUNCTBL((pIMenuModel),IMenuModel)->AddMdlListener(pIMenuModel,pMdlLsn)

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_AddEvtListener(pIMenuModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pIMenuModel),IMenuModel)->AddEvtListener(pIMenuModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IMENUMODEL_AddEvtListener( IMenuModel *pIMenuModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->AddEvtListener( pIMenuModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

//#define IMENUMODEL_CancelMdlListener(pIMenuModel,pMdlLsn) GET_FUNCTBL((pIMenuModel),IMenuModel)->CancelMdlListener(pIMenuModel,pMdlLsn)

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_CancelEvtListener(pIMenuModel,nEvtCode,pFnEvtCb,pData) \
    GET_FUNCTBL((pIMenuModel),IMenuModel)->CancelEvtListener(pIMenuModel,nEvtCode,pFnEvtCb,pData)
#else
__INLINE MAE_Ret IMENUMODEL_CancelEvtListener( IMenuModel *pIMenuModel, ModelEvtCode_t nEvtCode, PfnModelEvtListener pFnEvtCb, void *pData )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->CancelEvtListener( pIMenuModel , nEvtCode , pFnEvtCb , pData );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_CancelEvtAllListener(pIMenuModel,nEvtCode) \
    GET_FUNCTBL((pIMenuModel),IMenuModel)->CancelEvtAllListener(pIMenuModel,nEvtCode)
#else
__INLINE MAE_Ret IMENUMODEL_CancelEvtAllListener( IMenuModel *pIMenuModel, ModelEvtCode_t nEvtCode )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->CancelEvtAllListener( pIMenuModel , nEvtCode );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

// IVectorModel interface
#define IMENUMODEL_Size(pIMenuModel)                        GET_FUNCTBL((pIMenuModel),IMenuModel)->Size(pIMenuModel)
#define IMENUMODEL_GetAt(pIMenuModel,idx,ppo)               GET_FUNCTBL((pIMenuModel),IMenuModel)->GetAt(pIMenuModel,idx,MENU_VECTOR_DATA,ppo)
#define IMENUMODEL_ReplaceAt(pIMenuModel,idx,pv)            GET_FUNCTBL((pIMenuModel),IMenuModel)->ReplaceAt(pIMenuModel,idx,pv,MENUMDL_NOTIFY)
#define IMENUMODEL_InsertAt(pIMenuModel,idx,pv)             GET_FUNCTBL((pIMenuModel),IMenuModel)->InsertAt(pIMenuModel,idx,pv)       
#define IMENUMODEL_DeleteAt(pIMenuModel,idx)                GET_FUNCTBL((pIMenuModel),IMenuModel)->DeleteAt(pIMenuModel,idx)          
#define IMENUMODEL_DeleteAll(pIMenuModel)                   GET_FUNCTBL((pIMenuModel),IMenuModel)->DeleteAll(pIMenuModel)         
#define IMENUMODEL_EnsureCapacity(pIMenuModel,r,g)          GET_FUNCTBL((pIMenuModel),IMenuModel)->EnsureCapacity(pIMenuModel,r,g)
#define IMENUMODEL_SetPfnFree(pIMenuModel,pfn,pItemOwner)   GET_FUNCTBL((pIMenuModel),IMenuModel)->SetPfnFree(pIMenuModel,pfn,pItemOwner)
#define IMENUMODEL_Add(pIMenuModel,pv)                      GET_FUNCTBL((pIMenuModel),IMenuModel)->InsertAt(pIMenuModel,MENUMDL_LAST,pv)
#else
__INLINE MAERet_t IMENUMODEL_QueryInterface( IMenuModel *pIMenuModel, MAEIId_t id, void **pp, IBase *pOwner )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->QueryInterface( pIMenuModel , id , pp , pOwner );
}

__INLINE void IMENUMODEL_SendNotify( IMenuModel *pIMenuModel, ModelEvent_t *pMdlEvt )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SendNotify( pIMenuModel , pMdlEvt );
}
__INLINE MAE_Ret IMENUMODEL_AddMdlListener( IMenuModel *pIMenuModel, ModelListener_t *pMdlLsn )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->AddMdlListener( pIMenuModel , pMdlLsn );
}

__INLINE u32 IMENUMODEL_Size( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->Size( pIMenuModel );
}
__INLINE MAERet_t IMENUMODEL_GetAt( IMenuModel *pIMenuModel, u32 nIndex, void **ppoItem )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetAt( pIMenuModel , nIndex , MENU_VECTOR_DATA , ppoItem );
}
__INLINE MAE_Ret IMENUMODEL_ReplaceAt( IMenuModel *pIMenuModel, u32 nIndex, void *pvItem )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->ReplaceAt( pIMenuModel , nIndex , pvItem , MENUMDL_NOTIFY );
}
__INLINE MAE_Ret IMENUMODEL_InsertAt( IMenuModel *pIMenuModel, u32 nIndex, void *pvItem )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->InsertAt( pIMenuModel , nIndex , pvItem );
}
__INLINE MAE_Ret IMENUMODEL_DeleteAt( IMenuModel *pIMenuModel, u32 nIndex )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->DeleteAt( pIMenuModel , nIndex );
}
__INLINE void IMENUMODEL_DeleteAll( IMenuModel *pIMenuModel )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->DeleteAll( pIMenuModel );
}
__INLINE MAE_Ret IMENUMODEL_EnsureCapacity( IMenuModel *pIMenuModel, u32 nRequired, u32 nGrowBy )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->EnsureCapacity( pIMenuModel , nRequired , nGrowBy );
}
__INLINE ListModelFree_t IMENUMODEL_SetPfnFree( IMenuModel *pIMenuModel, PfnModelFree pfn, IBase *pItemOwner )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetPfnFree( pIMenuModel , pfn , pItemOwner );
}

#define IMENUMODEL_Add(pIMenuModel,pv)                      IMENUMODEL_InsertAt(pIMenuModel,MENUMDL_LAST,pv)


#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetAdaptGet
*  @brief  Set AdapteGet function for menu model to retrieve model data through this function
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] pfn          A MENUMODEL_ADAPTGET_FUNC_PTR pointer which indicates the AdaptGet function pointer
*  @param[in] pd           A void pointer which indicates the extra data information
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetAdaptGet(pIMenuModel,pfn,pd)          GET_FUNCTBL((pIMenuModel),IMenuModel)->SetAdaptGet(pIMenuModel,pfn,pd)
#else
__INLINE void IMENUMODEL_SetAdaptGet( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FUNC_PTR pfn, void *pd )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetAdaptGet( pIMenuModel , pfn , pd );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetAdaptGetEx
*  @brief  Set AdapteGet function for menu model to retrieve model data through this function
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] pfn          A MENUMODEL_ADAPTGET_FUNC_PTR pointer which indicates the AdaptGet function pointer
*  @param[in] pd           A void pointer which indicates the extra data information
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetAdaptGetEx(pIMenuModel,pfn)          GET_FUNCTBL((pIMenuModel),IMenuModel)->SetAdaptGetEx(pIMenuModel,pfn)
#else
__INLINE void IMENUMODEL_SetAdaptGetEx( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FUNC_PTR pfn )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetAdaptGetEx( pIMenuModel , pfn );
}
#endif /* __MAE_VENEERED_INTERFACE__ */


/** 
*  IMENUMODEL_SetAdaptGetEx
*  @brief  Set AdapteGet function for menu model to retrieve model data through this function
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] pfn          A MENUMODEL_ADAPTGET_FUNC_PTR pointer which indicates the AdaptGet function pointer
*  @param[in] pd           A void pointer which indicates the extra data information
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetAdaptGetFree(pIMenuModel,pfn)          GET_FUNCTBL((pIMenuModel),IMenuModel)->SetAdaptGetFree(pIMenuModel,pfn)
#else
__INLINE void IMENUMODEL_SetAdaptGetFree( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FREE_FUNC_PTR pfn )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetAdaptGetFree( pIMenuModel , pfn );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetAdaptGetFree
*  @brief  Set AdapteGetfree function for menu model to free the AdaptGet user data through this function
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] pfn          A MENUMODEL_ADAPTGET_FREE_FUNC_PTR pointer which indicates the AdaptGet function pointer
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetAdaptGetUserData(pIMenuModel,pfn,pd)          GET_FUNCTBL((pIMenuModel),IMenuModel)->SetAdaptGetUserData(pIMenuModel,pfn,pd)
#else
__INLINE void IMENUMODEL_SetAdaptGetUserData( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FREE_USER_DATA_FUNC_PTR pfn, void *pd )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetAdaptGetUserData( pIMenuModel , pfn , pd );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_GetAdaptGetFree
*  @brief  Get the user setting AdaptGet user data
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*
*  @retval void* AdaptGet user data pointer
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetAdaptGetUserData(pIMenuModel)          GET_FUNCTBL((pIMenuModel),IMenuModel)->GetAdaptGetUserData(pIMenuModel)
#else
__INLINE void* IMENUMODEL_GetAdaptGetUserData( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetAdaptGetUserData( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetTotalSize
*  @brief  Set the actual size of menu model.
*          This interface is for dynamic menu model (has AdaptGet function) ONLY.
*          The total size will be counted according to the real added entity numbers for static menu model.
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] size         A u32 value which indicates the actual menu model size
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetTotalSize(pIMenuModel,size)           GET_FUNCTBL((pIMenuModel),IMenuModel)->SetTotalSize(pIMenuModel,size)
#else
__INLINE void IMENUMODEL_SetTotalSize( IMenuModel *pIMenuModel, u32 size )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetTotalSize( pIMenuModel , size );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_GetTotalSize
*  @brief  Get the actual size of menu model.
*          This interface is for dynamic menu model (has AdaptGet function) ONLY.
*          The total size will be counted according to the real added entity numbers for static menu model.
*   
*  @param[in]  pIMenuModel  The pointer of IMenuModel interface object
*  @param[out] pnSize         A u32 value which indicates the actual menu model size
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetTotalSize(pIMenuModel,pSize)          GET_FUNCTBL((pIMenuModel),IMenuModel)->GetTotalSize(pIMenuModel,pSize)
#else
__INLINE void IMENUMODEL_GetTotalSize( IMenuModel *pIMenuModel, u32 *pSize )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetTotalSize( pIMenuModel , pSize );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IMENUMODEL_UpdateAt
*  @brief  Notify List and Menu widget which the specific index data has been updated.
*          Menu model will call AdaptGet function to ask caller to give the updated data for dynamic menu model.
*          This interface is for AP to update the display data ONLY, not including item flag.
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*
*  @retval MAE_RET_SUCCESS    Menu model successfully update the data
*  @retval MAE_RET_BAD_PARAM  Menu model fail to update the data due to wrong index
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_UpdateAt(pIMenuModel,idx)                GET_FUNCTBL((pIMenuModel),IMenuModel)->UpdateAt(pIMenuModel,idx,MENUMDL_NOTIFY)
#else
__INLINE MAE_Ret IMENUMODEL_UpdateAt( IMenuModel *pIMenuModel, u32 idx )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->UpdateAt( pIMenuModel , idx , MENUMDL_NOTIFY );
}
#endif /* __MAE_VENEERED_INTERFACE__ */



/** 
*  IMENUMODEL_SetCacheInfo
*  @brief  Set maximum cache model size and different item numbers when request item isn't in cache
*          This function should be called before _SetAdaptGet due to the cache size will be create at that time
*
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] dif          A u16 value to indicate the different item numbers when request item isn't in cache
*  @param[in] max          A u16 value to indicate the maximum cache model size
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetCacheInfo(pIMenuModel,dif,max)        GET_FUNCTBL((pIMenuModel),IMenuModel)->SetCacheInfo(pIMenuModel,dif,max)
#else
__INLINE void IMENUMODEL_SetCacheInfo( IMenuModel *pIMenuModel, u16 dif, u16 max )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetCacheInfo( pIMenuModel , dif , max );
}

#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_ToggleAt
*  @brief  Toggle at specific index. If original MENUMODEL_ITEM_SELECTED flag is on, then toggle off the flag. vis versa.
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*
*  @retval MAE_RET_SUCCESS    Menu model successfully toggle the MENUMODEL_ITEM_SELECTED flag
*  @retval MAE_RET_NOT_FOUND  Menu model fail to toggle the MENUMODEL_ITEM_SELECTED flag
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_ToggleAt(pIMenuModel,idx)                GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_TOGGLEITEM,idx,0)
#else
__INLINE MAE_Ret IMENUMODEL_AccessItemData( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nItm, u32 nData )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->AccessItemData( pIMenuModel , nType , nItm , nData );
}
#define IMENUMODEL_ToggleAt(pIMenuModel,idx) IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_TOGGLEITEM,idx,0)
#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_GetItemIndex
*  @brief  Get absolutely index according to given item id
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] id           A u32 value which indicates the specific item id
*  @param[out] pidx        A u32 pointer which return the converted absolutely index
*
*  @retval MAE_RET_SUCCESS    Menu model successfully get the item index
*  @retval MAE_RET_NOT_FOUND  Menu model fail to get the item index
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetItemIndex(pIMenuModel,id,pidx)        GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_GETITEMINDEX,id,((u32)pidx))
#else
#define IMENUMODEL_GetItemIndex(pIMenuModel,id,pidx)        IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_GETITEMINDEX,id,((u32)pidx))
#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_SetItemIdAt
*  @brief  Set the item id with specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] id           A u32 value which indicates the specific item id
*
*  @retval MAE_RET_SUCCESS    Menu model successfully set the item id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to set the item id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetItemIdAt(pIMenuModel,idx,id)          GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_SETITEMID,idx,id)
#else
#define IMENUMODEL_SetItemIdAt(pIMenuModel,idx,id)          IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_SETITEMID,idx,id)
#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_GetItemIdAt
*  @brief  Get the item id according to the specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] pid          A u32 pointer which return the item id
*
*  @retval MAE_RET_SUCCESS    Menu model successfully get the item id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to get the item id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetItemIdAt(pIMenuModel,idx,pid)         GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_GETITEMID,idx,((u32)pid))
#else
#define IMENUMODEL_GetItemIdAt(pIMenuModel,idx,pid)         IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_GETITEMID,idx,((u32)pid))
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetItemFlagAt
*  @brief  Set the item flag as on according to the specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] e            A ItemFlag_t enum type, please refer to MENUMODEL_ITEM_XXX
*
*  @retval MAE_RET_SUCCESS          Menu model successfully set the item flag
*  @retval MAE_RET_NOT_FOUND        Menu model fail to set the item flag
*  @retval MAE_RET_NOT_SUPPORTED    Illegal operation if current menu style isn't check/radio style
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetItemFlagAt(pIMenuModel,idx,e)         GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_SETITEMFLAG,idx,e)
#else
#define IMENUMODEL_SetItemFlagAt(pIMenuModel,idx,e)         IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_SETITEMFLAG,idx,e)
#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_ClearItemFlagAt
*  @brief  Clear the item flag to off according to the specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] e            A ItemFlag_t enum type, please refer to MENUMODEL_ITEM_XXX
*
*  @retval MAE_RET_SUCCESS          Menu model successfully clear the item flag
*  @retval MAE_RET_NOT_FOUND        Menu model fail to clear the item flag
*  @retval MAE_RET_NOT_SUPPORTED    Illegal operation if current menu style isn't check/radio style
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_ClearItemFlagAt(pIMenuModel,idx,e)       GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_CLEARITEMFLAG,idx,e)
#else
#define IMENUMODEL_ClearItemFlagAt(pIMenuModel,idx,e)       IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_CLEARITEMFLAG,idx,e)
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_ClearAllItemFlag
*  @brief  Clear all items flag to off
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] e            A ItemFlag_t enum type, please refer to MENUMODEL_ITEM_XXX
*
*  @retval MAE_RET_SUCCESS          Menu model successfully clear the item flag
*  @retval MAE_RET_NOT_FOUND        Menu model fail to clear the item flag
*  @retval MAE_RET_NOT_SUPPORTED    Illegal operation if current menu style isn't check/radio style
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_ClearAllItemFlag(pIMenuModel,e)       GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_CLEARALLITEFLAG,0,e)
#else
#define IMENUMODEL_ClearAllItemFlag(pIMenuModel,e)       IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_CLEARALLITEFLAG,0,e)
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IMENUMODEL_GetItemFlagAt
*  @brief  Get the item flag according to the specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[out] pe          A ItemFlag_t enum pointer, please refer to MENUMODEL_ITEM_XXX
*
*  @retval MAE_RET_SUCCESS    Menu model successfully get the item flag
*  @retval MAE_RET_NOT_FOUND  Menu model fail to get the item flag
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetItemFlagAt(pIMenuModel,idx,pe)        GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_GETITEMFLAG,idx,((u32)pe))
#else
#define IMENUMODEL_GetItemFlagAt(pIMenuModel,idx,pe)        IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_GETITEMFLAG,idx,((u32)pe))
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IMENUMODEL_SetItemSKAt
*  @brief  Set the item softkey id according to the specific index and softkey type
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] id           A SoftkeyID_e enum value, please refer to mae_softkey.h
*  @param[in] type         A Softkey_Type enum value, please refer to mae_softkey.h
*
*  @retval MAE_RET_SUCCESS    Menu model successfully set the item softkey id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to set the item softkey id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetItemSKAt(pIMenuModel,idx,id,type)     GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemSK(pIMenuModel,MENUMODEL_SETITEMSK,idx,type,id,TRUE)
#else
__INLINE MAE_Ret IMENUMODEL_AccessItemSK( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nIndex, Softkey_Type eSKType, u32 nData, boolean bNotify )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->AccessItemSK( pIMenuModel , nType , nIndex , eSKType , nData , bNotify );
}
#define IMENUMODEL_SetItemSKAt(pIMenuModel,idx,id,type)     IMENUMODEL_AccessItemSK(pIMenuModel,MENUMODEL_SETITEMSK,idx,type,id,TRUE)
#endif /* __MAE_VENEERED_INTERFACE__ */
/** 
*  IMENUMODEL_GetItemSKAt
*  @brief  Get the item softkey id according to the specific index and softkey type
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] type         A Softkey_Type enum value, please refer to mae_softkey.h
*  @param[out] pid         A SoftkeyID_e enum pointer, please refer to mae_softkey.h
*
*  @retval MAE_RET_SUCCESS    Menu model successfully get the item softkey id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to get the item softkey id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetItemSKAt(pIMenuModel,idx,pid,type)    GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemSK(pIMenuModel,MENUMODEL_GETITEMSK,idx,type,((u32)pid),FALSE)
#else
#define IMENUMODEL_GetItemSKAt(pIMenuModel,idx,pid,type)    IMENUMODEL_AccessItemSK(pIMenuModel,MENUMODEL_GETITEMSK,idx,type,((u32)pid),FALSE)
#endif /* __MAE_VENEERED_INTERFACE__ */

/**
*  IMENUMODEL_SetItemAllSKAt
*  @brief  Set the item softkey id according to the specific index for all softkey type
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] lid          A SoftkeyID_e enum value for left softkey, please refer to mae_softkey.h
*  @param[in] mid          A SoftkeyID_e enum value for middle softkey, please refer to mae_softkey.h
*  @param[in] rid          A SoftkeyID_e enum value for right softkey, please refer to mae_softkey.h
*
*  @retval MAE_RET_SUCCESS    Menu model successfully set the item softkey id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to set the item softkey id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetItemAllSKAt(pIMenuModel,idx,lid,mid,rid)      GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemAllSK(pIMenuModel,MENUMODEL_SETITEMSK,idx,lid,mid,rid)
#else

__INLINE MAE_Ret IMENUMODEL_AccessItemAllSK( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nIndex, u32 nLSK, u32 nCSK, u32 nRSK )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->AccessItemAllSK( pIMenuModel , nType , nIndex , nLSK , nCSK , nRSK );
}

#define IMENUMODEL_SetItemAllSKAt(pIMenuModel,idx,lid,mid,rid)      IMENUMODEL_AccessItemAllSK(pIMenuModel,MENUMODEL_SETITEMSK,idx,lid,mid,rid)
#endif /* __MAE_VENEERED_INTERFACE__ */


/** 
*  IMENUMODEL_GetItemAllSKAt
*  @brief  Get the item softkey id according to the specific index for all softkey type
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[out] plid         A SoftkeyID_e enum pointer for left softkey, please refer to mae_softkey.h
*  @param[out] pmid         A SoftkeyID_e enum pointer for middle softkey, please refer to mae_softkey.h
*  @param[out] prid         A SoftkeyID_e enum pointer for right softkey, please refer to mae_softkey.h
*
*  @retval MAE_RET_SUCCESS    Menu model successfully get the item softkey id
*  @retval MAE_RET_NOT_FOUND  Menu model fail to get the item softkey id
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetItemAllSKAt(pIMenuModel,idx,plid,pmid,prid)   GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemAllSK(pIMenuModel,MENUMODEL_GETITEMSK,idx,((u32)plid),((u32)pmid),((u32)prid))
#else
#define IMENUMODEL_GetItemAllSKAt(pIMenuModel,idx,plid,pmid,prid)   IMENUMODEL_AccessItemAllSK(pIMenuModel,MENUMODEL_GETITEMSK,idx,((u32)plid),((u32)pmid),((u32)prid))
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetItemDispBGOnly
*  @brief  Set the item flag as on according to the specific index
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] idx          A u32 value which indicates the specific index
*  @param[in] e            A ItemFlag_t enum type, please refer to MENUMODEL_ITEM_XXX
*
*  @retval MAE_RET_SUCCESS          Menu model successfully set the item flag
*  @retval MAE_RET_NOT_FOUND        Menu model fail to set the item flag
*  @retval MAE_RET_NOT_SUPPORTED    Illegal operation if current menu style isn't check/radio style
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetItemDispBGOnly(pIMenuModel,idx,e)         GET_FUNCTBL((pIMenuModel),IMenuModel)->AccessItemData(pIMenuModel,MENUMODEL_SETITEMDISPBGONLY,idx,e)
#else
#define IMENUMODEL_SetItemDispBGOnly(pIMenuModel,idx,e)         IMENUMODEL_AccessItemData(pIMenuModel,MENUMODEL_SETITEMDISPBGONLY,idx,e)
#endif /* __MAE_VENEERED_INTERFACE__ */


/** 
*  IMENUMODEL_IsDataModel
*  @brief  Notify menu model if the data is data model or pure data
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] b            A boolean value.
*                          Set TRUE to notify menu model the data is data model.
*                          Set FALSE to notify menu model the data is pure data
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_IsDataModel(pIMenuModel,b)               GET_FUNCTBL((pIMenuModel),IMenuModel)->IsDataModel(pIMenuModel,b)
#else
__INLINE void IMENUMODEL_IsDataModel( IMenuModel *pIMenuModel, boolean b )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->IsDataModel( pIMenuModel , b );
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetModelStyle
*  @brief  Notify menu model if the data is treat as check/radio/mark item widget
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] style        A u8 value which indicate the model style, please refer to e_Item_Style
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetModelStyle(pIMenuModel,style)         GET_FUNCTBL((pIMenuModel),IMenuModel)->SetModelStyle(pIMenuModel,style)
#else
__INLINE void IMENUMODEL_SetModelStyle( IMenuModel *pIMenuModel, u8 style )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetModelStyle( pIMenuModel , style );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_GetCheckStatus
*  @brief  Get check/radio/mark select status
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[out] ppstatus     A boolean double pointer to store the whole menu model selected status
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetCheckStatus(pIMenuModel,ppstatus)     GET_FUNCTBL((pIMenuModel),IMenuModel)->GetCheckStatus(pIMenuModel,ppstatus)
#else
__INLINE void IMENUMODEL_GetCheckStatus( IMenuModel *pIMenuModel, boolean **ppstatus )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetCheckStatus( pIMenuModel , ppstatus );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_SetCheckStatus
*  @brief  Set check/radio/mark select status
*   
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*  @param[in] pstatus      A boolean pointer which indicate the whole menu model selected status
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetCheckStatus(pIMenuModel,pstatus)      GET_FUNCTBL((pIMenuModel),IMenuModel)->SetCheckStatus(pIMenuModel,pstatus)
#else
__INLINE void IMENUMODEL_SetCheckStatus( IMenuModel *pIMenuModel, boolean *pstatus )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetCheckStatus( pIMenuModel , pstatus );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_GetEntityIndex
*  @brief  Get the cached data in current dynamic menu model
*   
*  @param[in] pIMenuModel   The pointer of IMenuModel interface object
*  @param[out] pstEntityIdx A MenuModelEntityData_t pointer to store the cached data range
*
*  @retval None
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetEntityIndex(pIMenuModel,pstEntityIdx) GET_FUNCTBL((pIMenuModel),IMenuModel)->GetEntityIndex(pIMenuModel,pstEntityIdx)
#else
__INLINE void IMENUMODEL_GetEntityIndex( IMenuModel *pIMenuModel, MenuModelEntityData_t *pstEntityIdx )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetEntityIndex( pIMenuModel , pstEntityIdx );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** 
*  IMENUMODEL_ClearCachedEntities
*  @brief  Clear all the entities stored in cache without changing the model size and entity index
*
*  @param[in] pIMenuModel  The pointer of IMenuModel interface object
*
*  @retval MAE_RET_SUCCESS    Menu model successfully clear the cached entities
*  @retval MAE_RET_NOT_FOUND  Menu model fail to clear the cached entities
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_ClearCachedEntities(pIMenuModel)         GET_FUNCTBL((pIMenuModel),IMenuModel)->ClearCachedEntities(pIMenuModel)
#else
__INLINE MAE_Ret IMENUMODEL_ClearCachedEntities( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->ClearCachedEntities( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_ClearCachedUserData(pIMenuModel)         GET_FUNCTBL((pIMenuModel),IMenuModel)->ClearCachedUserData(pIMenuModel)
#else
__INLINE MAE_Ret IMENUMODEL_ClearCachedUserData( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->ClearCachedUserData( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_InCachedData(pIMenuModel, u32Index)         GET_FUNCTBL((pIMenuModel),IMenuModel)->InCachedData(pIMenuModel, u32Index)
#else
__INLINE MAE_Ret IMENUMODEL_InCachedData( IMenuModel *pIMenuModel, u32 u32Index )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->InCachedData( pIMenuModel, u32Index );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetRealIndex(pIMenuModel, u32Index)         GET_FUNCTBL((pIMenuModel),IMenuModel)->GetRealIndex(pIMenuModel, u32Index)
#else
__INLINE u32 IMENUMODEL_GetRealIndex( IMenuModel *pIMenuModel, u32 u32Index )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetRealIndex( pIMenuModel, u32Index );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetDisplayIndex(pIMenuModel, u32RealIndex)         GET_FUNCTBL((pIMenuModel),IMenuModel)->GetDisplayIndex(pIMenuModel, u32RealIndex)
#else
__INLINE u32 IMENUMODEL_GetDisplayIndex( IMenuModel *pIMenuModel, u32 u32RealIndex )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetDisplayIndex( pIMenuModel, u32RealIndex );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetDisplaySize(pIMenuModel)         GET_FUNCTBL((pIMenuModel),IMenuModel)->GetDisplaySize(pIMenuModel)
#else
__INLINE u32 IMENUMODEL_GetDisplaySize( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetDisplaySize( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_IsStaticMenu(pIMenuModel)         GET_FUNCTBL((pIMenuModel),IMenuModel)->IsStaticMenu(pIMenuModel)
#else
__INLINE u32 IMENUMODEL_IsStaticMenu( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->IsStaticMenu( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_SetModelType(pIMenuModel,u32ModelType)         GET_FUNCTBL((pIMenuModel),IMenuModel)->SetModelType(pIMenuModel,u32ModelType)
#else
__INLINE void IMENUMODEL_SetModelType( IMenuModel *pIMenuModel, u32 u32ModelType )
{
    GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->SetModelType( pIMenuModel, u32ModelType );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#ifndef __MAE_VENEERED_INTERFACE__
#define IMENUMODEL_GetModelType(pIMenuModel)         GET_FUNCTBL((pIMenuModel),IMenuModel)->GetModelType(pIMenuModel)
#else
__INLINE u32 IMENUMODEL_GetModelType( IMenuModel *pIMenuModel )
{
    return GET_FUNCTBL( ( pIMenuModel ) , IMenuModel )->GetModelType( pIMenuModel );
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/*=============================================================*/
// functions
/*=============================================================*/


#endif //__MMI_MAE_MENUMODEL_H__
/*=============================================================*/
// end of file
