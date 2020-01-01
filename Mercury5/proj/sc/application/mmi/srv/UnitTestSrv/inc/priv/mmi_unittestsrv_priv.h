/**
* @file mmi_UnitTestSrv_priv.h
*
* This header file defines the data structure of unittest service.
*
*/

#ifndef __MMI_UNITTESTSRV_PRIV_H__
#define __MMI_UNITTESTSRV_PRIV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_UnitTestSrv.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define SIZE_OF_TABLE(_TABLE_) (sizeof(_TABLE_)/sizeof(_TABLE_[0]))
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef UTSrvTestSuite_t* (*UTSrvGetTestSuite)(void);

typedef u32 (*UTSrvScriptInit)(u32 nCusData, u32 nInitData);
typedef u32 (*UTSrvScriptRun)(u32 nCusData, u32 nInitResult);
typedef boolean (*UTSrvScriptCheck)(u32 nCusData, u32 nTestResult);

typedef struct UTSrvTestStep_t_
{
    u32 nInitData;
    UTSrvScriptInit pfnInit;
    UTSrvScriptRun pfnRun;
    UTSrvScriptCheck pfnCheck;
} UTSrvTestStep_t;

/*=============================================================*/
// Private Function Declaration
/*=============================================================*/

/*The following APIs are only provided for ut_srv_xxx.c*/
void *UTSrvGetInstance(void);
boolean UTSrvRunTestScript(u32 nCusData, const UTSrvTestStep_t *pTestScript, u32 nStepNum);
s32 UTSrvCmnHook(u32 *pStack);

#endif //__MMI_UNITTESTSRV_PRIV_H__

