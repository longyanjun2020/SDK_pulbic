/**
* @file DataCtnrStrategier.h
*
* This header file defines the declarations of data container tStgr proto-type.
*
*/

#ifndef __DATACTNRSTRATEGIER_H__
#define __DATACTNRSTRATEGIER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "DataStructItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* DataCtnrStrategierHandle_t;
typedef bool (*DataCtnrStrategier_Init)(DataStructHandle_t pHandle, DataCtnr_t *pDataCtnr);

typedef enum DataCtnrStrategierType_e_
{
    DATA_CTNR_STRATEGIER__QUEUE,
    DATA_CTNR_STRATEGIER__STACK,
    DATA_CTNR_STRATEGIER__NUM
} DataCtnrStrategierType_e;

typedef struct DataCtnrStgr_t_
{
    DataStruct_t dataStruct;
    DataCtnrStrategierType_e eStgrType;
    DataCtnr_t *pDataCtnr;
} DataCtnrStgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__DATACTNRSTRATEGIER_H__

