/**
* @file UnitTest_Main.h
*
* This header file defines the interfaces of unit test entry
* 
*/

#ifndef __UNITTEST_MAIN_H__
#define __UNITTEST_MAIN_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UT__MAX_NAME_SIZE           40
#define UT__OUTPUT_FUNCTION         UnitTest_OutputMsg
#define UT__ASSERT(_EXPRESSION_) \
    GRM_ASSERT(_EXPRESSION_); \
    if (FALSE == (_EXPRESSION_)) \
    { \
        return FALSE; \
    } \

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef bool (*UnitTest_RunCaseCb)(void *cusData);
typedef u16 (*UnitTest_RunSuiteCb)(u16 *pPassNum, u16 *pFailNum);

typedef struct UnitTestCase_t_
{
    char testCaseName[UT__MAX_NAME_SIZE];
    UnitTest_RunCaseCb RunTestCase;
    void *cusData;
} UnitTestCase_t;

typedef struct UnitTestSuite_t_
{
    char testSuiteName[UT__MAX_NAME_SIZE];
    u16 testCasesNum;
    UnitTestCase_t *pTestCases;
} UnitTestSuite_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void UnitTest_StartTestSuites();
void UnitTest_OutputMsg(char* pMsg);
u16 UnitTest_RunTestSuite(UnitTestSuite_t *pTestSuites, u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_MAIN_H__
