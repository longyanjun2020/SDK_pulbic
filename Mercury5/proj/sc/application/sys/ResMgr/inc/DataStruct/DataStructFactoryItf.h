/**
* @file DataStructFactoryItf.h
*
* This header file defines the  APIs of double link list.
*
*/

#ifndef __DATASTRUCTFACTORYITF_H__
#define __DATASTRUCTFACTORYITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "DataStructItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/


/*=============================================================*/
// Function Declarations
/*=============================================================*/
DataStruct_t* DSF_InitDataStruct(DataStructType_e eType);
void DSF_UninitDataStruct(DataStruct_t* pDataCtnr);

#endif //__DATASTRUCTFACTORYITF_H__

