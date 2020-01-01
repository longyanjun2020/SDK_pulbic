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
#include "UnitTest_MainItf.h"
#include "UnitTest_AudResCtrlItf.h"
#include "UnitTest_BitStreamItf.h"
#include "UnitTest_CmdFacItf.h"
#include "UnitTest_CmdMgrItf.h"
#include "UnitTest_CmdMgrFacItf.h"
#include "UnitTest_CtrlFacItf.h"
#include "UnitTest_DListItf.h"
#include "UnitTest_EvtFacItf.h"
#include "UnitTest_FSMItf.h"
#include "UnitTest_GenResCtrlItf.h"
#include "UnitTest_ListenerItf.h"
#include "UnitTest_MediatorItf.h"
#include "UnitTest_MmpResCtrlItf.h"
#include "UnitTest_ObjArrayItf.h"
#include "UnitTest_QueueItf.h"
#include "UnitTest_RspFacItf.h"
#include "UnitTest_StackItf.h"
#include "UnitTest_PseduoDevResCtrlItf.h"
#include "UnitTest_CmdMgrItf_NoTask.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UNIT_TEST__ALL_SUITES \
    UT__SUITE_DECLARATION(UnitTest_RunAudResCtrlTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunBitStreamTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunCmdFacTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunCmdMgrFacTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunCtrlFacTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunDListTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunEvtFacTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunFSMTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunGenResCtrlTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunListenerTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunMediatorTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunMmpResCtrlTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunObjArrayTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunQueueTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunRspFacTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunStackTestSuite), \
    UT__SUITE_DECLARATION(UnitTest_RunCmdMgrTestSuiteNT), \
    UT__SUITE_DECLARATION(UnitTest_RunCmdMgrTestSuite), \


/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__UNITTEST_SUITES_H__
