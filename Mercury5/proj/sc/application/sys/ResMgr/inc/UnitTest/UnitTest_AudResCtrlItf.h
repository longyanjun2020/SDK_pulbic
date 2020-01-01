/**
* @file UnitTest_AudResCtrlItf.h
*
* This header file defines the interfaces of audio resource control
* unit test cases.
*/

#ifndef __UNITTEST_AUDRESCTRLITF_H__
#define __UNITTEST_AUDRESCTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "ResMgr_Common.h"
#include "MediaCmdItf.h"
#include "HAL_AudResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define UT_AUD_RES_CTRL__MAX_VOL_RANGE  8

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct UpdatePathTestInfo_t_
{
    ResMgr_AppId_e eAppId;
    u16 uBTConfig;
    u16 uSpeakerConfig;
    u16 uHeadsetConfig;
    MediaResInfo_e eResInfo;
} UpdatePathTestInfo_t;

typedef struct UpdatePrefPathTestInfo_t_
{
    ResMgr_AppId_e eAppId;
    AudPath_e ePath;
    MediaResInfo_e eResInfo;
} UpdatePrefPathTestInfo_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 UnitTest_RunAudResCtrlTestSuite(u16 *pPassNum, u16 *pFailNum);

#endif //__UNITTEST_AUDRESCTRLITF_H__
