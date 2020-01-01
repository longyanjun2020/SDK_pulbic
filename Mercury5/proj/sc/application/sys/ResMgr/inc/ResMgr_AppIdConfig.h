/**
* @file ResMgr_Config.h
*
* This header file defines the config of resource manager.
*
*/

#ifndef __RESMGR_APPIDCONFIG_H__
#define __RESMGR_APPIDCONFIG_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "ResMgr_Common.h"
#include "MediaCmdItf.h"
#include "MediaPriorityCtrl.h"
#include "MediaCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/


/*=============================================================*/
// Type Declarations
/*=============================================================*/
// End of MediaAppIdConfig

typedef struct ResMgr_AppIdConfig_t_
{
    MediaCmdSuspend_e         eSuspend;
    MediaCmdResume_e          eReume;
    u8                        nMediaPriority;
    ResMgr_PriHandleType_e    ePriHandleType;
    ResMgr_LowPriHandleType_e eLowPriHandleType;
    ResMgr_TaskId_e           eTaskId;
}ResMgr_AppIdConfig_t;

typedef struct ResMgr_CfgSetContent_t_
{
    MediaCmdSuspend_e       eSuspend;
    MediaCmdResume_e        eReume;
    u8                      nMediaPriority;
    ResMgr_PriHandleType_e  ePriHandleType;
}ResMgr_CfgSetContent_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
__SLDPM_FREE__ ResMgr_AppIdConfig_t *ResMgr_GetConfigbyCfgId(ResMgr_ConfigId_e eConfigId);
void ResMgr_SetConfigByCfgId(ResMgr_ConfigId_e eConfigId, ResMgr_AppIdConfig_t *pConfig);
ResMgr_CfgSetContent_t ResMgr_GetConfigByCfgSet(ResMgr_ConfigSet_e eConfigSet);

#endif //__RESMGR_CONFIG_H__

