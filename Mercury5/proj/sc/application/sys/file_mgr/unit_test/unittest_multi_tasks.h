/**
* @file UnitTest_MultiTasksItf.h
*
* This header file defines the interfaces of queue unit
* test cases.
*/

#ifndef __UNITTEST_MULTITASKSTF_H__
#define __UNITTEST_MULTITASKSTF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

#if defined(RES_MGR_STANDALONE_DEBUG)
#include "Win32_FakeTaskItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UT_TEST_SUITE_NAME_LEN  60
#define UT_CMD_NUM(_CMD_)       sizeof(_CMD_)/sizeof(FileMgrTestData_t)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum FileMgrTestType_e_
{
    TEST__CMD,
    TEST__RSP,
    TEST__NUM
} FileMgrTestType_e;

typedef void (*FileMgrTestFunc_Fxp)(u8 nClientDataIdx);
typedef struct FileMgrCmd_t_
{
    u16 uClientTaskId;
    u16 uCmdDelay;
    FileMgrTestFunc_Fxp TestFunc;
} FileMgrCmd_t;

typedef void (*FileMgrTestRsp_Fxp)(void *pTestData);

typedef struct FileMgrRsp_t_
{
    u16 uMsgId;
    u16 uDummy;
    FileMgrTestRsp_Fxp TestRsp;
} FileMgrRsp_t;

typedef struct FileMgrTestData_t_
{
    FileMgrTestType_e eType;
    union
    {
        FileMgrCmd_t tCmd;
        FileMgrRsp_t tRsp;
    } uTestData;
} FileMgrTestData_t;

typedef FileMgrTestData_t* (*FileMgrGetTestData_Fxp)(void *pTestCmdHeader, u16 uCmdIdx);

typedef struct FileMgrTestDataHeader_t_
{
    char aName[UT_TEST_SUITE_NAME_LEN];
    u16 uCmdNum;
    u16 uRepeatNum;
    u16 uClientNum;
    u16 uDelay;
    FileMgrTestData_t *pTestData;
    FileMgrGetTestData_Fxp GetTestData;
} FileMgrTestDataHeader_t;

typedef struct FileMgrTask_t_
{
    Win32Task_t tTask;
    u16 uAppId;
    u16 uTermEvtIndex;
    u16 uClientNum;
    boolean bTerm;
} FileMgrTask_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunMultiTasksTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //RES_MGR_STANDALONE_DEBUG
#endif //__UNITTEST_MULTITASKSTF_H__
