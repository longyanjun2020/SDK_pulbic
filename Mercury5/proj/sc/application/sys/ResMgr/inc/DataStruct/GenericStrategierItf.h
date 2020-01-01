/**
* @file GenericStrategierItf.h
*
* This header file defines the interfaces of Generic strategier.
*
*/

#ifndef __GENERICSTRATEGIERITF_H__
#define __GENERICSTRATEGIERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "DataCtnrStrategier.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct GenericStgr_t_
{
    DataCtnrStgr_t tStgr;
} GenericStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
bool GenericStgr_Add(DataStructHandle_t pHandle, void *pItem);
void* GenericStgr_Get(DataStructHandle_t pHandle);
void* GenericStgr_Remove(DataStructHandle_t pHandle);
bool GenericStgr_RemoveItem(DataStructHandle_t pHandle, void *pItem);
void GenericStgr_RemoveAll(DataStructHandle_t pHandle);
void GenericStgr_RemoveAllEx(DataStructHandle_t pHandle, DataCtnr_FreeData FreeItem);
u16 GenericStgr_Transverse(DataStructHandle_t pHandle, void *pCusData, DataStructVisitorItf_t const *pVisitorItf);
u16 GenericStgr_TransverseFrom(DataStructHandle_t pHandle, void *pCusData, void *pRefItem, DataStructVisitorItf_t const *pVisitorItf);
u16 GenericStgr_GetItemNum(DataStructHandle_t pHandle);

#endif //__GENERICSTRATEGIERITF_H__

