/**
* @file QueueStrategierItf.h
*
* This header file defines the interfaces of queue tStgr.
*
*/

#ifndef __QUEUESTRATEGIERITF_H__
#define __QUEUESTRATEGIERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "GenericStrategierItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef GenericStgr_t QueueStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
QueueStgr_t* QueueStgr_Init(DataStructType_e eDataStructType, DataCtnr_t *pDataCtnr);
DataCtnr_t* QueueStgr_Uninit(QueueStgr_t *pQueue);

#endif //__QUEUESTRATEGIERITF_H__

