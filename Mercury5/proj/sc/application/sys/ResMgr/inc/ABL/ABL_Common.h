/**
* @file ABL_Aud.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of audio.
*
*/

#ifndef __ABL_COMMON_H__
#define __ABL_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_CusParms.h"
#include "esl_aud_itf.h"
#include "ResMgr_CmdMgrItf.h"
#include "ResMgr_AppIdConfig.h"
#include "ResMgr_AppListenerItf.h"
#include "MediaTaskClientMgrItf.h"
#include "MediaCmn.h"
#include "srv_ResMgr_Cmn.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define GET_BYTES_BY_FILE_LEN(_LEN_)    (((_LEN_) * 2) + 2)
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ABL_ClientTaskInfo_t_
{
    CmdMgrHdl_t pCmdMgrHdl;
    u32 uMailBox;
} ABL_ClientTaskInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
MediaResInfo_e ABL_RemapMediaFormat(ABL_AudFormat_e eAudFormat);
/*
For boundary check
*/
ABL_CmnErrCode_e ABL_CheckParam(u32 nParam, u32 nParamBound);
ResMgr_AppIdConfig_t *ABL_GetConfigbyAppId(ResMgr_AppId_e eAppId);
CmdMgrHdl_t ABL_GetCmdMgr(ResMgr_TaskId_e eTaskId);
CmdMgrHdl_t ABL_GetCmdMgrByAppId(ResMgr_AppId_e eAppId);

ABL_CmnErrCode_e ABL_CreateCmdThenHandle
(
    ResMgr_AppId_e eAppId,
    MediaCmdSuspend_e eSuspendType,
    MediaCmdResume_e eResume,
    MediaCmdActType_e eActType,
    const MediaCmdCusParm_t *pMediaCmdCusParms,
    bool bLoopPlay,
    bool bSync,
    void *pCusData
);

u16 *ABL_DuplicateWString(u16 *pString, u16 uStrLen);
//This API only support B3 for now
void ABL_RingBuffSetDataEnd(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl);
/*
To parse codec info from wave/mp3 header and remove it
*/
ABL_CmnErrCode_e ABL_RetrieveBuffInfo(ResMgr_AppId_e eAppId, Media_Format_e eDataFormat, void *pUserData, u32 uDataSize, u8 *pCacheBuf, Media_AudCodecInfo_t *pCodecInfo);
#endif
