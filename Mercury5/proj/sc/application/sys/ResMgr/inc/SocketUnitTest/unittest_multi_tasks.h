/**
* @socket UnitTest_MultiTasksItf.h
*
* This header file defines the interfaces of queue unit
* test cases.
*/

#ifndef __UNITTEST_SOCKET_MULTITASKSTF_H__
#define __UNITTEST_SOCKET_MULTITASKSTF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "Win32_FakeTaskItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UT_TEST_SUITE_NAME_LEN  60
#define UT_CMD_NUM(_CMD_)       sizeof(_CMD_)/sizeof(SocketTestData_t)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum SocketTestType_e_
{
    SOCKET__CMD,
	SOCKET__RSP,
    SOCKET__NUM
} SocketTestType_e;

typedef void (*SocketTestFunc_Fxp)(u8 nClientDataIdx);
typedef struct SocketCommand_t_
{
    u16 uClientTaskId;
    u16 uCmdDelay;
    SocketTestFunc_Fxp TestFunc;
} SocketCommand_t;

typedef void (*SocketTestRsp_Fxp)(void *pTestData);

typedef struct SocketRsp_t_
{
    u16 uMsgId;
    u16 uDummy;
    SocketTestRsp_Fxp TestRsp;
} SocketRsp_t;

typedef struct SocketTestData_t_
{
    SocketTestType_e eType;
    union
    {
        SocketCommand_t tCmd;
        SocketRsp_t tRsp;
    } uTestData;
} SocketTestData_t;

typedef SocketTestData_t* (*SocketGetTestData_Fxp)(void *pTestCmdHeader, u16 uCmdIdx);

typedef struct SocketTestDataHeader_t_
{
    char aName[UT_TEST_SUITE_NAME_LEN];
    u16 uCmdNum;
    u16 uRepeatNum;
    u16 uClientNum;
    u16 uDelay;
    SocketTestData_t *pTestData;
    SocketGetTestData_Fxp GetTestData;
} SocketTestDataHeader_t;

typedef struct SocketTask_t_
{
    Win32Task_t tTask;
    u16 uAppId;
    u16 uTermEvtIndex;
    u16 uClientNum;
    bool bTerm;
} SocketTask_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunMultiTasksTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_SOCKET_MULTITASKSTF_H__
