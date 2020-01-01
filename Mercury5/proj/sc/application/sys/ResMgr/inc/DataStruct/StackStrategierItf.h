/**
* @file StackStrategierItf.h
*
* This header file defines the interfaces of Stack strategier.
*
*/

#ifndef __STACKSTRATEGIERITF_H__
#define __STACKSTRATEGIERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "GenericStrategierItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef GenericStgr_t StackStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StackStgr_t* StackStgr_Init(DataStructType_e eDataStructType, DataCtnr_t *pDataCtnr);
DataCtnr_t* StackStgr_Uninit(StackStgr_t *pStack);
bool StackStgr_Add(DataStructHandle_t pHandle, void *pItem);

#endif //__STACKSTRATEGIERITF_H__

