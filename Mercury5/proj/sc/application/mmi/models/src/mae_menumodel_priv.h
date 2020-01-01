/**
 * @file mae_menumodel_priv.h
 * @brief This file defines the data structure of a menu model and function prototype for implementation.
 *
 * @version $Id: mae_menumodel_priv.h 39819 2009-09-09 13:16:22Z ryan.chou $
 */
#ifndef __MAE_MENUMODEL_PRIV_H__
#define __MAE_MENUMODEL_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_menumodel.h"
#include "mmi_mae_modelbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/* the main structure for a Menu Model */
typedef struct
{
    void **ppItems;         //pointer to array of menu data
    u32 nItems;         //number of valid items in array
    u32 nSize;              //total number of allocation items(valid items and free items) in array
    u32 nGrowBy;            //grow-by size(number of items) for subsequent allocations
    PfnModelFree pfnFree;  //free function (called in Vector_Dtor)
    IBase *pItemOwner;      //a pointer of IBase obj to keeps the owner of the data in menu model
} MenuVector;

typedef struct
{
    u32 u32ArraySize;
    u32 u32CurrentSize;
    u32 *pItemArrayId;
} Menu_DisplayArray_s;

typedef struct
{
    Model_t MdlBase;
    MenuVector mvItemData;
    Menu_DisplayArray_s sDisplayItemList;
    void *pUserDataToAdaptGet;      //a pointer to keep parameter data which will be used when call adapt Get function
    MENUMODEL_ADAPTGET_FUNC_PTR AdaptGetFuncPtr;    //a pointer to keep adapt Get function
    MENUMODEL_ADAPTGET_FREE_FUNC_PTR AdaptGetFreeFuncPtr; 
    MENUMODEL_ADAPTGET_FREE_USER_DATA_FUNC_PTR AdaptGetFreeUserDataFuncPtr;
    MenuModelIdxData_t stIndexData;
    u32 nRealSize;
    u32 u32RealDisplaySize;
    u32 nModelStyle;
    boolean bHasSetTotalSize;       //flag to indicate the total size has been set or not
    boolean *pbCheck;
    u32 nHeadIndex;
    MenuModelEntityData_t stEntityInfo;
    u16 nDiffEntity;
    u16 nMaxEntity;
    u32 u32ModelType;
} MenuModel_t;

/*=============================================================*/
// functions
/*=============================================================*/
__SLDPM_FREE__ u32 MenuModel_Release( IMenuModel *pIMenuModel );
__SLDPM_FREE__ MAE_Ret MenuModel_QueryInterface( IMenuModel *pIMenuModel, MAE_IId iId, void **ppObj, IBase *pOwner );

__SLDPM_FREE__ MAE_Ret MenuModel_New( MAE_ClsId ClsID, void **ppObj );
__SLDPM_FREE__ void MenuModelStructInit( MenuModel_t *pThis, const FUNCTBL( IMenuModel ) * FtblPtr );

u32 MenuModel_Size( IMenuModel *pIMenuModel );
__SLDPM_FREE__ void MenuModel_SetTotalSize( IMenuModel *pIMenuModel, u32 nTotalSize );
__SLDPM_FREE__ void MenuModel_GetTotalSize( IMenuModel *pIMenuModel, u32 *pnTotalSize );
__SLDPM_FREE__ MAE_Ret MenuModel_GetAt( IMenuModel *pIMenuModel, u32 nIndex, ListDataType_e nType, void **ppvItem );
MAE_Ret MenuModel_ReplaceAt( IMenuModel *pIMenuModel, u32 nIndex, void *pvItem, boolean bNotify );
__SLDPM_FREE__ MAE_Ret MenuModel_InsertAt( IMenuModel *pIMenuModel, u32 nIndex, void *pvItem );
MAE_Ret MenuModel_UpdateAt( IMenuModel *pIMenuModel, u32 nIndex, boolean bNotify );

MAE_Ret MenuModel_DeleteAt( IMenuModel *pIMenuModel, u32 nIndex );
void MenuModel_DeleteAll( IMenuModel *pIMenuModel );
__SLDPM_FREE__ MAE_Ret MenuModel_EnsureCapacity( IMenuModel *pIMenuModel, u32 nRequired, u32 nGrowBy );

void MenuModel_SetAdaptGet( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FUNC_PTR pAdaptGetFunc, void *pUserData );
__SLDPM_FREE__ void MenuModel_SetAdaptGetEx( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FUNC_PTR pAdaptGetFunc );
__SLDPM_FREE__ void MenuModel_SetAdaptGetFree( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FREE_FUNC_PTR pAdaptGetFreeFunc );
__SLDPM_FREE__ void MenuModel_SetAdaptGetUserData( IMenuModel *pIMenuModel, MENUMODEL_ADAPTGET_FREE_USER_DATA_FUNC_PTR pAdaptGetFreeUserDataFunc, void *pUserData );
void* MenuModel_GetAdaptGetUserData( IMenuModel *pIMenuModel );

ListModelFree_t MenuModel_SetPfnFree( IMenuModel *pIMenuModel, PfnModelFree pfnFree, IBase *pItemOwner );

MAE_Ret MenuModel_AccessItemData( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nItm, u32 nData );
MAE_Ret MenuModel_AccessItemSK( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nIndex, Softkey_Type eSKType, u32 nData, boolean bNotify );
MAE_Ret MenuModel_AccessItemAllSK( IMenuModel *pIMenuModel, MenuItemAccessType_t nType, u32 nIndex, u32 nLSK, u32 nCSK, u32 nRSK );

__SLDPM_FREE__ void MenuModel_IsDataModel( IMenuModel *pIMenuModel, boolean bIsDataModel );
__SLDPM_FREE__ void MenuModel_SetModelStyle( IMenuModel *pIMenuModel, u8 nModelStyle );
void MenuModel_GetCheckStatus( IMenuModel *pIMenuModel, boolean **ppCheckStatus );
void MenuModel_SetCheckStatus( IMenuModel *pIMenuModel, boolean *pCheckStatus );
void MenuModel_GetEntityIndex( IMenuModel *pIMenuModel, MenuModelEntityData_t *pstEntityIdx );
__SLDPM_FREE__ void MenuModel_SetCacheInfo( IMenuModel *pIMenuModel, u16 nDiffEntity, u16 nMaxEntity );
__SLDPM_FREE__ MAE_Ret MenuModel_ClearCachedEntities( IMenuModel *pIMenuModel );
__SLDPM_FREE__ MAE_Ret MenuModel_ClearCachedUserData( IMenuModel *pIMenuModel );
__SLDPM_FREE__ boolean MenuModel_InCachedData( IMenuModel *pIMenuModel, u32 u32Index );
__SLDPM_FREE__ u32 MenuModel_GetRealIndex( IMenuModel *pIMenuModel, u32 u32Index );
__SLDPM_FREE__ u32 MenuModel_GetDisplayIndex( IMenuModel *pIMenuModel, u32 u32RealIndex );
__SLDPM_FREE__ u32 MenuModel_GetDisplaySize( IMenuModel *pIMenuModel );
__SLDPM_FREE__ boolean MenuModel_IsStaticMenu( IMenuModel *pIMenuModel );
__SLDPM_FREE__ void MenuModel_SetModelType( IMenuModel *pIMenuModel, u32 u32ModelType );
__SLDPM_FREE__ u32 MenuModel_GetModelType( IMenuModel *pIMenuModel );

#endif //__MAE_MENUMODEL_PRIV_H__
/*=============================================================*/
// end of file
