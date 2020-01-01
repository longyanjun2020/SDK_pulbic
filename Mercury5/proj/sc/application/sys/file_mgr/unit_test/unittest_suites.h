/**
* @file UnitTest_Suites.h
*
* This header file defines unit test suites
* 
*/

#ifndef __UNITTEST_SUITES_H__
#define __UNITTEST_SUITES_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "unittest_main.h"
#include "unittest_hashtable.h"
#include "unittest_queue.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UNIT_TEST__ALL_SUITES \
	UT__SUITE_DECLARATION(UnitTest_RunHashtableTestSuite), \
	UT__SUITE_DECLARATION(UnitTest_RunQueueTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunMultiTasksTestSuite), \

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__UNITTEST_SUITES_H__
