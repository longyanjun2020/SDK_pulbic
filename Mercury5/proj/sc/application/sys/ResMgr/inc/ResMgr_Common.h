/**
* @file ResMgr_Common.h
*
* This header file defines the common interfaces of resource manager.
*
*/

#ifndef __RESMGR_COMMON_H__
#define __RESMGR_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define RES_MGR__INVALID_MBX                    0xFF
#undef RES_MGR__IMPLEMENT_PAUSE_BY_STOP_MEDIA

#define RES_MGR__FLOW_CONTROL                   FALSE

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum ResMgr_ErrorCode_e_
{
    RES_MGR_ERR_OK,
    RES_MGR_ERR_FAIL,
    RES_MGR_ERR_SKIP,
    RES_MGR_ERR_PARAM_ERROR,
    RES_MGR_ERR_MEM_ALLOC_ERROR,
    RES_MGR_ERR_REJECT,
    RES_MGR_ERR_ABORT,
    RES_MGR_ERR_PATH_ERROR,
    RES_MGR_ERR_TIMEOUT,
	RES_MGR_ERR_FORMAT_NOT_SUPPORT,
} ResMgr_ErrorCode_e;

typedef enum ResMgr_AppId_e_
{
    RES_MGR_APP_ID__BEGIN = 0,
    RES_MGR_APP_ID__CCMTA = RES_MGR_APP_ID__BEGIN,
    RES_MGR_APP_ID__CCAPP,
    RES_MGR_APP_ID__FILEMGR,
    RES_MGR_APP_ID__PHB,
    RES_MGR_APP_ID__POWEROFF,
    RES_MGR_APP_ID__POWERON,
    RES_MGR_APP_ID__PROFILE,
    RES_MGR_APP_ID__SETTING,
    RES_MGR_APP_ID__COUNTDOWNTIMER,
    RES_MGR_APP_ID__EM,
    RES_MGR_APP_ID__VENDOR,
    RES_MGR_APP_ID__MPLAYER,
    RES_MGR_APP_ID__VIDEOPLAYER1,
    RES_MGR_APP_ID__VIDEOPLAYER2,
    RES_MGR_APP_ID__VIDEOPLAYER3,
    RES_MGR_APP_ID__VIDEOPLAYER4,
    RES_MGR_APP_ID__VIDEOPLAYER5,
    RES_MGR_APP_ID__VOICEMEMO,
    RES_MGR_APP_ID__EMUGAME,
    RES_MGR_APP_ID__NATIVEGAME,
    RES_MGR_APP_ID__FMRADIO,
    RES_MGR_APP_ID__CAMERA,
    RES_MGR_APP_ID__EVENTCENTER,
    RES_MGR_APP_ID__ATV,
    RES_MGR_APP_ID__USB,
    RES_MGR_APP_ID__JAVA,
    RES_MGR_APP_ID__RES_MGR,
    RES_MGR_APP_ID__SYS,
    RES_MGR_APP_ID__KEYPAD,
    RES_MGR_APP_ID__STK,
    RES_MGR_APP_ID__MMS,
    RES_MGR_APP_ID__WAP,
    RES_MGR_APP_ID__EMAIL,
    RES_MGR_APP_ID__QQ,
    RES_MGR_APP_ID__LBS,
    RES_MGR_APP_ID__TTS,
    RES_MGR_APP_ID__ALARM,
    RES_MGR_APP_ID__SDK1,
    RES_MGR_APP_ID__SDK2,
    RES_MGR_APP_ID__SDK3,
    RES_MGR_APP_ID__SDK4,
    RES_MGR_APP_ID__SDK5,
	RES_MGR_APP_ID__SDK6,
    RES_MGR_APP_ID__VTAPP,
    RES_MGR_APP_ID__GOGOBOXGAME,
    RES_MGR_APP_ID__SEARCH,
    RES_MGR_APP_ID__TUDOU,
    RES_MGR_APP_ID__RTSP,
    RES_MGR_APP_ID__HTTP,
    RES_MGR_APP_ID__NTPAPP,
    RES_MGR_APP_ID__OTHERAPP,
    RES_MGR_APP_ID__DUMMY,
    RES_MGR_APP_ID__NUM,
    RES_MGR_APP_ID__INVALID = 0xFF
} ResMgr_AppId_e;

typedef enum ResMgr_ConfigId_e_
{
    /* The following APP_IDs share the same config,RES_MGR_CFG_ID__DEFAULT.
    RES_MGR_APP_ID__ATV,
    */
    RES_MGR_CFG_ID__DEFAULT,
    /* The following APP_IDs share the same config,RES_MGR_CFG_ID__SUSPEND_AUTO.
    RES_MGR_APP_ID__SYS,
    RES_MGR_APP_ID__STK,
    RES_MGR_APP_ID__MMS,
    RES_MGR_APP_ID__OTHERAPP,
    RES_MGR_APP_ID__FILEMGR,
    RES_MGR_APP_ID__PHB,
    RES_MGR_APP_ID__POWERON,
    RES_MGR_APP_ID__COUNTDOWNTIMER
    */
    RES_MGR_CFG_ID__SUSPEND_AUTO,
    /* The following APP_IDs share the same config,RES_MGR_CFG_ID__RESUME_AUTO.
    RES_MGR_APP_ID__PROFILE,
    RES_MGR_APP_ID__SETTING,
    */
    RES_MGR_CFG_ID__RESUME_AUTO,

    /*Unique config for the following app_id*/
    RES_MGR_CFG_ID__CAMERA,
    RES_MGR_CFG_ID__CCMTA,
    RES_MGR_CFG_ID__CCAPP,
    RES_MGR_CFG_ID__VTAPP,
    RES_MGR_CFG_ID__EM,
    RES_MGR_CFG_ID__EVENTCENTER,
    RES_MGR_CFG_ID__FMRADIO,
    RES_MGR_CFG_ID__KEYPAD,
    RES_MGR_CFG_ID__MPLAYER,
    RES_MGR_CFG_ID__NATIVEGAME,
    RES_MGR_CFG_ID__EMUGAME,
    RES_MGR_CFG_ID__POWEROFF,
    RES_MGR_CFG_ID__RES_MGR,
    RES_MGR_CFG_ID__VENDOR,
    RES_MGR_CFG_ID__VOICEMEMO,
    RES_MGR_CFG_ID__USB,
    RES_MGR_CFG_ID__VIDEOPLAYER,
    RES_MGR_CFG_ID__JAVA,
    RES_MGR_CFG_ID__TTS,
    RES_MGR_CFG_ID__SDK1,
    RES_MGR_CFG_ID__SDK2,
    RES_MGR_CFG_ID__SDK3,
    RES_MGR_CFG_ID__SDK4,
    RES_MGR_CFG_ID__SDK5,
    RES_MGR_CFG_ID__SDK6,
    RES_MGR_CFG_ID__DUMMY,
    RES_MGR_CFG_ID__NUM,
    RES_MGR_CFG_ID__INVALID = 0xFF
}ResMgr_ConfigId_e;

typedef enum ResMgr_ConfigSet_e_
{
    RES_MGR_CFG_SET__DEFAULT,
	RES_MGR_CFG_SET__SUSPEND_AUTO,
	RES_MGR_CFG_SET__RESUME_AUTO,
	RES_MGR_CFG_SET__VIDEOCHAT,
	RES_MGR_CFG_SET__NUM
} ResMgr_ConfigSet_e;

typedef enum ResMgr_TaskId_e_
{
    RES_MGR_TASK_ID__MMI,
    RES_MGR_TASK_ID__JAVA,
    RES_MGR_TASK_ID__IPTV,
    RES_MGR_TASK_ID__WAP,
    RES_MGR_TASK_ID__EMAIL,
    RES_MGR_TASK_ID__QQ,
    RES_MGR_TASK_ID__LBS,
    RES_MGR_TASK_ID__MMS,
    RES_MGR_TASK_ID__SDK,
	RES_MGR_TASK_ID__RES_MGR,
	RES_MGR_TASK_ID__SDK1,
	RES_MGR_TASK_ID__SDK2,
	RES_MGR_TASK_ID__SDK3,
	RES_MGR_TASK_ID__SDK4,
	RES_MGR_TASK_ID__SDK5,
	RES_MGR_TASK_ID__SDK6,
	RES_MGR_TASK_ID__OTHERAPP,
    RES_MGR_TASK_ID__NUM,
    RES_MGR_TASK_ID__INVALID = 0xFF
} ResMgr_TaskId_e;

typedef enum ResMgr_StgrType_e_
{
    RES_MGR_STGR_TYPE__APP,
    RES_MGR_STGR_TYPE__TASK,
    RES_MGR_STGR_TYPE__NUM
} ResMgr_StgrType_e;

typedef enum ResMgr_ResCategory_e_
{
    RES_MGR_RES_CATEGORY__MEDIA,
	RES_MGR_RES_CATEGORY__SOCKET,
    RES_MGR_RES_CATEGORY__NUM
} ResMgr_ResCategory_e;

typedef enum ResMgr_InformType_e_
{
    RES_MGR_INFORM_TYPE__NORMAL,
    RES_MGR_INFORM_TYPE__DENY,
    RES_MGR_INFORM_TYPE__MERGE,
    RES_MGR_INFORM_TYPE__STOP_SUCCESS,  //Only used for packing stop skip as success
    RES_MGR_INFORM_TYPE__FAILED,
    RES_MGR_INFORM_TYPE__WAIT_APPSTOP_DROP
} ResMgr_InformType_e;

typedef enum ResMgr_SuspendType_e_
{
    RES_MGR_SUSPEND_TYPE__AUTO,
    RES_MGR_SUSPEND_TYPE__INTERACTIVE,
    RES_MGR_SUSPEND_TYPE__NUM,
    RES_MGR_SUSPEND_TYPE__INVALID = 0xFF
} ResMgr_SuspendType_e;

typedef enum ResMgr_ResumeType_e_
{
    RES_MGR_RESUME_TYPE__AUTO,
    RES_MGR_RESUME_TYPE__INTERACTIVE,
    RES_MGR_RESUME_TYPE__NUM,
    RES_MGR_RESUME_TYPE__INVALID = 0xFF
} ResMgr_ResumeType_e;

typedef void* ResMgr_CmdHdl_t;
typedef void* ResMgr_RspHdl_t;
typedef void* ResMgr_CtrlHdl_t;
typedef void* ResMgr_EvtHdl_t;
typedef void* ResMgr_RingBuffHdl_t;

typedef struct ResMgr_RingBuff_t_
{
	ResMgr_RingBuffHdl_t pRingBuffHdl;
} ResMgr_RingBuff_t;

typedef enum ResMgr_CmdMgrConfigType_e_
{
    RES_MGR_CMDMGR_CONFIG_TYPE__LISTENER_TYPE,
    RES_MGR_CMDMGR_CONFIG_TYPE__NUM,
    RES_MGR_CMDMGR_CONFIG_TYPE__INVALID = 0XFF
} ResMgr_CmdMgrConfigType_e;

typedef enum ResMgr_ConfigListenerType_e_
{
    RES_MGR_CONFIG_LISTENER_TYPE__NOTIFY_FIRST,         /* LISTENER_TYPE__NOTIFY_FIRST, */
    RES_MGR_CONFIG_LISTENER_TYPE__NOTIFY_LAST,          /* LISTENER_TYPE__NOTIFY_LAST,  */
    RES_MGR_CONFIG_LISTENER_TYPE__NOTIFY_ALL,           /* LISTENER_TYPE__NOTIFY_ALL,   */
    RES_MGR_CONFIG_LISTENER_TYPE__NUM                   /* LISTENER_TYPE__NUM           */
} ResMgr_ConfigListenerType_e;

typedef struct ResMgr_CmdMgrConfig_t_
{
    ResMgr_CmdMgrConfigType_e eType;
    union
    {
        ResMgr_ConfigListenerType_e eListenerType;   /* RES_MGR_CONFIG_CMDMGR_TYPE__LISTENER_TYPE */
    } uParam;
} ResMgr_CmdMgrConfig_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ResMgr_SendMsg(u32 uTypeMsg, void *pCusData, u32 uParam, u32 uParamEx);
ResMgr_ErrorCode_e ResMgr_SendMsgWithThd(u32 uTypeMsg, void *pCusData, u32 uParam, u32 uParamEx);
u32 ResMgr_GetCurrentMsgNum(void);
ResMgr_ConfigId_e ResMgr_GetCfgIdByAppId(ResMgr_AppId_e eAppId);
void ResMgr_SetCfgIdByAppId(ResMgr_AppId_e eAppId, ResMgr_ConfigId_e eConfigId);

#endif //__RESMGR_COMMON_H__

