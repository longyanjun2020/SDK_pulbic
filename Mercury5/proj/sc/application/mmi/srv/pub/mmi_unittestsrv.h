/**
* @file mmi_UnitTestSrv.h
*
* This header file defines the data structure of unittest service.
*
*/

#ifndef __MMI_UNITTESTSRV_H__
#define __MMI_UNITTESTSRV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#ifdef __SDK_SIMULATION__
#include "hook.h"
#endif
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define UTSRV_MAX_NAME_SIZE 40

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* UTSrvHdl_t;

typedef MAE_Ret (*UTSrvInitTest)(u32 *pTestData);
typedef boolean (*UTSrvRunCaseCb)(u32 nTestData);
typedef void (*UTSrvUninitTest)(u32 nTestData);

typedef s32 (*UTSrvHookCb)(u32 *pStack);

typedef struct UTSrvTestCase_t_
{
    u8 szCaseName[UTSRV_MAX_NAME_SIZE];
    UTSrvRunCaseCb pfnRunTestCase;
} UTSrvTestCase_t;

typedef struct UTSrvHookFunc_t_
{
    void *pTargetFunc;
    UTSrvHookCb pfnHookCb;
} UTSrvHookFunc_t;

typedef struct UTSrvTestSuite_t_
{
    u8 szSuiteName[UTSRV_MAX_NAME_SIZE];
    UTSrvInitTest pfnInitTest;
    UTSrvUninitTest pfnUninitTest;
    const UTSrvTestCase_t *pTestCase;
    u32 nCaseNum;
    const UTSrvHookFunc_t *pHookFunc;
    u32 nFuncNum;
} UTSrvTestSuite_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
/*The following APIs are only provided for mmi_unitTestApp.c*/
MAE_Ret UnitTestSrvCreate(UTSrvHdl_t *ppUTSrvHdl, void *pUserInstance);
MAE_Ret UnitTestSrvDestroy(UTSrvHdl_t pUTSrvHdl);
u32 UnitTestSrvGetSuiteNum(UTSrvHdl_t pUTSrvHdl);
UTSrvTestSuite_t *UnitTestSrvGetTestSuite(UTSrvHdl_t pUTSrvHdl, u32 nSuiteIdx);

#endif //__MMI_UNITTESTSRV_H__

