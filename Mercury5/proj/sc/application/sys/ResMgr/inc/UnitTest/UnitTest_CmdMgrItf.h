/**
* @file UnitTest_CmdMgrItf.h
*
* This header file defines the interfaces of command manager unit
* test cases.
*/

#ifndef __UNITTEST_CMDMGRITF_H__
#define __UNITTEST_CMDMGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

#if defined(RES_MGR_STANDALONE_DEBUG)
#include "Win32_FakeTaskItf.h"
#include "ResMgr_CmdMgrItf.h"
#include "ResMgr_CmdItf.h"
#include "MediaCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UT_CMD_NUM(_CMD_)       sizeof(_CMD_)/sizeof(CmdMgrTestCmd_t)
#define DUMMY                   0
#define UT_TEST_SUITE_NAME_LEN  60
#define INVALID_RSP_ID          0xFFFF

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum CmdMgrTestCmd_e_
{
    TEST_CMD__AUD_PLAY_FILE,
    TEST_CMD__AUD_PLAY_STREAM,
    TEST_CMD__AUD_REC,
    TEST_CMD__VDO_PLAY_FILE,
    TEST_CMD__VDO_PLAY_STREAM,
    TEST_CMD__VDO_PLAY_MEM,
    TEST_CMD__VDO_OPEN,
    TEST_CMD__VDO_DEC_FIRST_FRAME,
    TEST_CMD__VDO_SEEK,
    TEST_CMD__AUD_STOP_PLAY,
    TEST_CMD__NUM
} CmdMgrTestCmd_e;

typedef enum CmdMgrTestActType_e_
{
    TEST__CMD,
    TEST__RSP,
    TEST__CTRL_SET_DEV,
    TEST__CTRL_REG_VOL,
    TEST__CTRL_DEREG_VOL,
    TEST__CTRL_SET_VOL,
    TEST__CTRL_GET_VOL,
    TEST__CTRL_DTMF,
    TEST__CTRL_CONFIRM,
    TEST__CTRL_DEV_CB,
    TEST__CTRL_INIT_PROFILE,
    TEST__CTRL_SET_ACT_PROFILE,
    TEST__CTRL_GET_ACT_PROFILE,
    TEST__CTRL_FLUSH_CMD,
    TEST__CTRL_RESUME,
    TEST__NUM
} CmdMgrTestActType_e;

typedef struct CmdMgrTestParm_t_
{
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u16 uDummy4;
    u32 uDummy5;
    u32 uDummy6;
    u32 uDummy7;
    u16 uDummy8;
} CmdMgrTestParm_t;

typedef struct CmdMgrTestCmdParm_t_
{
    u16 eResume;
    u16 eAct;
    u16 eResInfo;
    bool bLoopPlay;
    ResMgr_CusFunc CusFunc;
    ResMgr_ExecCmd ExecFunc;
    ResMgr_TerminateCmd TerminFunc;
    u16 eSuspendType;
} CmdMgrTestCmdParm_t;

typedef struct CmdMgrTestRspParm_t_
{
    u16 eExecRes;
    u16 uGenRsp;
    u16 uDummy1;
    u16 uDummy2;
    u32 uDummy3;
    u32 uTypeMsg;
} CmdMgrTestRspParm_t;

typedef struct CmdMgrTestCtrlDevParm_t_
{
    u16 uDevice;
    u16 uStatus;
    u16 uDummy1;
    u16 uDummy2;
    u32 uDummy3;
    u32 uDummy4;
    u32 uDummy5;
} CmdMgrTestCtrlDevParm_t;

typedef struct CmdMgrTestCtrlRegVolParm_t_
{
    u16 uRegVolCtrlId;
    u16 uDefVol;
    u16 uVolRange;
    u16 uDummy2;
    u32 uDummy3;
    u32 uDummy4;
    u32 uDummy5;
} CmdMgrTestCtrlRegVolParm_t;

typedef struct CmdMgrTestCtrlDeregVolParm_t_
{
    u16 uRegVolCtrlId;
    u16 uDummy0;
    u16 uDummy1;
    u16 uDummy2;
    u32 uDummy3;
    u32 uDummy4;
    u32 uDummy5;
} CmdMgrTestCtrlDeregVolParm_t;

typedef struct CmdMgrTestCtrlSetVolParm_t_
{
    u16 uVolCtrlId;
    u16 uVolume;
    u16 uAppId;
    u16 uDummy2;
    u32 uDummy3;
    u32 uDummy4;
    u32 uDummy5;
} CmdMgrTestCtrlSetVolParm_t;

typedef struct CmdMgrTestCtrlGetVolParm_t_
{
    u16 uAppId;
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u32 uDummy4;
    u8 *pVolume;
    u8 *pVolRange;
} CmdMgrTestCtrlGetVolParm_t;

typedef struct CmdMgrTestCtrlDtmfParm_t_
{
    bool bEnable;
    u16 uDummy2;
    u16 uDummy3;
    u16 uDummy4;
    u32 uDummy5;
    u32 uDummy6;
    u32 uDummy7;
} CmdMgrTestCtrlDtmfParm_t;

typedef struct CmdMgrTestCtrlResumeParm_t_
{
    bool bResume;
    u16 uDummy2;
    u16 uDummy3;
    u16 uDummy4;
    u32 uDummy5;
    u32 uDummy6;
    u32 uDummy7;
} CmdMgrTestCtrlResumeParm_t;

typedef struct CmdMgrTestCtrlDevCbParm_t_
{
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u16 uDummy4;
    u32 uDummy5;
    u32 uCusData;
    void *pDevChgCallback;
} CmdMgrTestCtrlDevCbParm_t;

typedef struct CmdMgrTestInitProfileParm_t_
{
    u16 eVolCtrlId;
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u32 uDummy4;
    MediaProfileVol_t *pDefProfiles;
    u32 uDummy5;
} CmdMgrTestInitProfileParm_t;

typedef struct CmdMgrTestSetActProfileParm_t_
{
    u16 eVolCtrlId;
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u32 uDummy4;
    MediaProfileType_e *pActProfile;
    u32 uDummy5;
} CmdMgrTestSetActProfileParm_t;

typedef struct CmdMgrTestGetActProfileParm_t_
{
    u16 eVolCtrlId;
    u16 uDummy1;
    u16 uDummy2;
    u16 uDummy3;
    u32 uDummy4;
    MediaProfileType_e *pActProfile;
    u32 uDummy5;
} CmdMgrTestGetActProfileParm_t;

typedef struct CmdMgrTestCmd_t_
{
    CmdMgrTestActType_e eType;
    u16 uAppId;
    u16 uCmdDelay;
    union
    {
        CmdMgrTestParm_t tParm;
        CmdMgrTestRspParm_t tRspParm;
        CmdMgrTestCmdParm_t tCmdParm;
        CmdMgrTestCtrlDevParm_t tChgDevParm;
        CmdMgrTestCtrlRegVolParm_t tRegVolParm;
        CmdMgrTestCtrlDeregVolParm_t tDeregVolParm;
        CmdMgrTestCtrlSetVolParm_t tSetVolParm;
        CmdMgrTestCtrlGetVolParm_t tGetVolParm;
        CmdMgrTestCtrlDtmfParm_t tDtmfParm;
        CmdMgrTestCtrlResumeParm_t tResumeParm;
        CmdMgrTestCtrlDevCbParm_t tDevCbParm;
        CmdMgrTestInitProfileParm_t tInitProfileParm;
        CmdMgrTestSetActProfileParm_t tSetActProfileParm;
        CmdMgrTestGetActProfileParm_t tGetActProfileParm;
    };
} CmdMgrTestCmd_t;

typedef CmdMgrTestCmd_t* (*UT_CmdMgrGetCmd)(void *pTestCmdHeader, u16 uCmdIdx);

typedef struct CmdMgrTestCmdHeader_t_
{
    char aName[UT_TEST_SUITE_NAME_LEN];
    u16 uCmdNum;
    u16 uRepeatNum;
    u16 uAppCmdMgrNum;
    u16 uDelay;
    CmdMgrTestCmd_t *pCmds;
    UT_CmdMgrGetCmd GetCmd;
} CmdMgrTestCmdHeader_t;

typedef struct CmdMgrTask_t_
{
    Win32Task_t tTask;
    u16 uAppId;
    u16 uTermEvtIndex;
    u16 uAppCmdMgrNum;
    CmdMgrHdl_t pCmdMgrHdl;
} CmdMgrTask_t;

typedef struct CmdMgrTestTimerData_t_
{
    Win32Task_t *pDestTask;
    bool bProRsp;
    u32 uRspId;
    u32 uCusData;
    void *pRspData;
    Win32Timer_t *pTimer;
    ResMgr_CmdHdl_t pCurCmdHdl;
} CmdMgrTestTimerData_t;

typedef enum CmdMgrTestCase_e_
{
    CMD_MGR_TEST_CASE__BASIC_CMD,
    CMD_MGR_TEST_CASE__STOP_CMD,
    CMD_MGR_TEST_CASE__CONFLICT_CMD,
    CMD_MGR_TEST_CASE__PRIORITY,
    CMD_MGR_TEST_CASE__AUTO_RESUME,
    CMD_MGR_TEST_CASE__MULTIPLE_CLIENT,
    CMD_MGR_TEST_CASE__NUM
} CmdMgrTestCase_e;

#endif //#if defined(RES_MGR_STANDALONE_DEBUG)

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunCmdMgrTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_CMDMGRITF_H__
