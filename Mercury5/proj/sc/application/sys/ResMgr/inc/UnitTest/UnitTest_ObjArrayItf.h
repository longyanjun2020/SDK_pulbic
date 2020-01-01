/**
* @file UnitTest_ObjArrayItf.h
*
* This header file defines the interfaces of object array unit
* test cases.
*/

#ifndef __UNITTEST_OBJARRAYITF_H__
#define __UNITTEST_OBJARRAYITF_H__

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
typedef struct ObjArrayTestItem_t_
{
    u16 uTestVal1;
    void *pTestData;
    u16 uTestVal2;
} ObjArrayTestItem_t;

typedef struct ObjArrayTravData_t_
{
    u16 uCurIdx;
    u16 uCusData;
} ObjArrayTravData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunObjArrayTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_OBJARRAYITF_H__
