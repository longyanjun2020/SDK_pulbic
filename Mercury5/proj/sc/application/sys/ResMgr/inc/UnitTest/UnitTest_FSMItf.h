/**
* @file UnitTest_FSMItf.h
*
* This header file defines the interfaces of finite state machines unit
* test cases.
*/

#ifndef __UNITTEST_FSMITF_H__
#define __UNITTEST_FSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum TestStates_e_
{
    TEST_STATE__1,
    TEST_STATE__2,
    TEST_STATE__NUM
} TestStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunFSMTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_FSMITF_H__
