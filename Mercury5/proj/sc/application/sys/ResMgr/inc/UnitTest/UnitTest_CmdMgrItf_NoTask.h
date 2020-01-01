/**
* @file UnitTest_CmdMgrItf_NoTask.h
*
* This header file defines the interfaces of command manager unit
* test cases.
*/

#ifndef __UNITTEST_CMDMGRITF_NT_H__
#define __UNITTEST_CMDMGRITF_NT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#if defined(RES_MGR_STANDALONE_DEBUG)
#include "UnitTest_CmdMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef bool (*UnitTest_RunCaseNTCb)(void *pCmdMgrHdl, void *tCmdParms);

typedef struct CmdMgrTestCmdHeaderNT_t_
{
    char aName[UT_TEST_SUITE_NAME_LEN];
    //u16 uCmdNum;
    UnitTest_RunCaseNTCb RunTestCase;
    //CmdMgrTestCmdNT_t *pCmds;
} CmdMgrTestCmdHeaderNT_t;

#endif //#if defined(RES_MGR_STANDALONE_DEBUG)

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunCmdMgrTestSuiteNT(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_CMDMGRITF_NT_H__
