/**
* @file DataCtnrItf.h
*
* This header file defines the interfaces of data container.
*
*/

#ifndef __DATACTNRITF_H__
#define __DATACTNRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum DataCtnrType_e_
{
    DATA_CTNR__DLIST,
    DATA_CTNR__NUM
} DataCtnrType_e;

typedef void* DataCtnrHdl_t;
typedef void* DataCtnrPosHdl_t;

typedef bool (*DataCtnr_AddItem)(DataCtnrHdl_t pHandle, void *pItem);
typedef bool (*DataCtnr_RemoveItem)(DataCtnrHdl_t pHandle, void *pItem);
typedef bool (*DataCtnr_RemoveItemByIdx)(DataCtnrHdl_t pHandle, u16 idx);
typedef void (*DataCtnr_RemoveAllItem)(DataCtnrHdl_t pHandle);
typedef void* (*DataCtnr_RemoveItemByOrder)(DataCtnrHdl_t pHandle);
typedef void (*DataCtnr_FreeData)(void *pItem);
typedef void (*DataCtnr_RemoveAllItemEx)(DataCtnrHdl_t pHandle, DataCtnr_FreeData FreeItem);
typedef void* (*DataCtnr_GetItem)(DataCtnrHdl_t pHandle);
typedef DataCtnrPosHdl_t (*DataCtnr_CreatePosHdl)(DataCtnrHdl_t pHandle);
typedef bool (*DataCtnr_DestroyPosHdl)(DataCtnrPosHdl_t pPosHandle);
typedef bool (*DataCtnr_SetPosHdl)(DataCtnrPosHdl_t pPosHandle);
typedef void* (*DataCtnr_GetItemByPos)(DataCtnrPosHdl_t pPosHandle);
typedef void* (*DataCtnr_GetItemByIdx)(DataCtnrHdl_t pHandle, u16 idx);
typedef bool (*DataCtnr_FindItem)(DataCtnrHdl_t pHandle, DataCtnrPosHdl_t pPosHandle, void *pItem);
typedef u16 (*DataCtnr_GetItemNum)(DataCtnrHdl_t pHandle);

typedef struct DataCtnrItf_t_
{
    DataCtnr_AddItem AddItemToHead;
    DataCtnr_AddItem AddItemToTail;
    DataCtnr_RemoveItem RemoveItem;
    DataCtnr_RemoveItemByIdx RemoveItemByIdx;
    DataCtnr_RemoveAllItem RemoveAll;
    DataCtnr_RemoveAllItemEx RemoveAllEx;
    DataCtnr_RemoveItemByOrder RemoveFirst;
    DataCtnr_RemoveItemByOrder RemoveLast;
    DataCtnr_GetItem GetFirstItem;
    DataCtnr_GetItem GetLastItem;
    DataCtnr_CreatePosHdl CreatePosHdl;
    DataCtnr_DestroyPosHdl DestroyPosHdl;
    DataCtnr_SetPosHdl SetPosToHead;
    DataCtnr_SetPosHdl SetPosToTail;
    DataCtnr_SetPosHdl MoveToNextPos;
    DataCtnr_SetPosHdl MoveToPrevPos;
    DataCtnr_GetItemByPos GetCurItem;
    DataCtnr_GetItemByPos GetNextItem;
    DataCtnr_GetItemByPos GetPreviousItem;
    DataCtnr_GetItemByIdx GetItemByIdx;
    DataCtnr_FindItem FindItem;
    DataCtnr_GetItemNum GetItemNum;
} DataCtnrItf_t;

typedef struct DataCtnr_t_
{
    DataCtnrType_e eDataCtnrType;
    DataCtnrItf_t const *pDataCtnrItf;
} DataCtnr_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__DATACTNRITF_H__

