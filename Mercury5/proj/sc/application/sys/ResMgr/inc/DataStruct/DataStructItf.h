/**
* @file DataStructItf.h
*
* This header file defines the interfaces of data structure.
*
*/

#ifndef __DATASTRUCTITF_H__
#define __DATASTRUCTITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "DataStructVisitorItf.h"
#include "DataCtnrItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum DataStructType_e_
{
    DATA_STRUCT__DLIST_QUEUE,
    DATA_STRUCT__DLIST_STACK,
    DATA_STRUCT__NUM
} DataStructType_e;

typedef void* DataStructHandle_t;
typedef bool (*DataStruct_Add)(DataStructHandle_t pHandle, void *pItem);
typedef void* (*DataStruct_Get)(DataStructHandle_t pHandle);
typedef void* (*DataStruct_Remove)(DataStructHandle_t pHandle);
typedef bool (*DataStruct_RemoveItem)(DataStructHandle_t pHandle, void *pItem);
typedef void (*DataStruct_RemoveAll)(DataStructHandle_t pHandle);
typedef void (*DataStruct_RemoveAllEx)(DataStructHandle_t pHandle, DataCtnr_FreeData FreeItem);
typedef u16 (*DataStruct_Transverse)(DataStructHandle_t pHandle, void *pCusData, DataStructVisitorItf_t const *pVisitorItf);
typedef u16 (*DataStruct_TransverseFrom)(DataStructHandle_t pHandle, void *pCusData, void *pStartItem, DataStructVisitorItf_t const *pVisitorItf);
typedef u16 (*DataStruct_GetItemNum)(DataStructHandle_t pHandle);

typedef struct DataStructItf_t_
{
    DataStruct_Add Add;
    DataStruct_Get Get;
    DataStruct_Remove Remove;
    DataStruct_RemoveItem RemoveItem;
    DataStruct_RemoveAll RemoveAll;
    DataStruct_RemoveAllEx RemoveAllEx;
    DataStruct_Transverse Transverse;
    DataStruct_TransverseFrom TransverseFrom;
    DataStruct_GetItemNum GetItemNum;
} DataStructItf_t;

typedef struct DataStruct_t_
{
    DataStructType_e eDataStructType;
    const DataStructItf_t *pInterface;
} DataStruct_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__DATASTRUCTITF_H__

