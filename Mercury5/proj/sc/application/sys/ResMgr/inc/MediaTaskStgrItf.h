/**
* @file MediaTaskStgrItf.h
*
* This header file defines the interfaces of media task command
* tStgr
*/

#ifndef __MEDIATASKSTGRITF_H__
#define __MEDIATASKSTGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_TaskStgr.h"
#include "MediaCmdItf.h"
#include "ResCtrlItf.h"
#include "HAL_AudResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define MEDIA_FIND_CMD__ALL_APP         0xFF
#define MEDIA_FIND_CMD__ALL_ACT         0xFF
#define MEDIA_FIND_CMD__ALL_RES_INFO    0xFF

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaCmdFindOpt_e_
{
    MEDIA_CMD_FIND_OPTION__EXACTLY,
    MEDIA_CMD_FIND_OPTION__GROUP,
    MEDIA_CMD_FIND_OPTION__NUM
} MediaCmdFindOpt_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
__SLDPM_FREE__ CmdMgrStgrHdl_t MediaTaskStgr_Init(ResMgrCommItf_t *pCommItf);
__SLDPM_FREE__ void MediaTaskStgr_Uninit(CmdMgrStgrHdl_t pHandle);
void MediaTaskStgr_Send(CmdMgrStgrHdl_t pHandle, u32 uDestMbx, u32 uTypeMsg, void *pMsgBody);

__SLDPM_FREE__ ResMgr_CmdHdl_t MediaTaskStgr_FindCmd
(
    CmdMgrStgrHdl_t pStgrHdl,
    ResMgr_AppId_e eAppId,
    MediaCmdType_e eFindCmdType,
    MediaCmdActType_e eActType,
    MediaResInfo_e eResInfo,
    MediaCmdFindOpt_e eFindOpt
);

typedef ResCtrl_DoAction Media_ResolveConflict;

__SLDPM_FREE__ MediaExecCheckRes_e MediaTaskStgr_IsConflict(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ ResMgr_CmdPreExecRes_e MediaTaskStgr_ResolveConflicts(CmdMgrStgrHdl_t pStgrHdl, Media_ResolveConflict ConflictResolver);
__SLDPM_FREE__ void MediaTaskStgr_InformApp(CmdMgrStgrHdl_t pHandle, ResMgr_RspHdl_t pRspHdl, u32 uCusFlags);
__SLDPM_FREE__ void MediaTaskStgr_SendResumeRsp(CmdMgrStgrHdl_t pHandle, ResMgr_RspHdl_t pRspHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_OccupyRes(CmdMgrStgrHdl_t pHandle, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_ReleaseRes(CmdMgrStgrHdl_t pHandle, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_CheckHighPriCmd(CmdMgrStgrHdl_t pHandle);
__SLDPM_FREE__ void MediaTaskStgr_FinalizeCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId);
__SLDPM_FREE__ void MediaTaskStgr_ResumeCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId);
__SLDPM_FREE__ void MediaTaskStgr_SetTempVolCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId);
u16 MediaTaskStgr_CheckHWScalar(u16 uIndex, void **ppOwner, void *pCusData);
__SLDPM_FREE__ void MediaTaskStgr_GetPath(CmdMgrStgrHdl_t pStgrHdl, AudPath_e *pPath, AudChannel_e *pChannel);
__SLDPM_FREE__ void MediaTaskStgr_SendEvt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, ResMgr_EvtHdl_t *pEvt);
__SLDPM_FREE__ ResMgr_ErrorCode_e MediaTaskStgr_SendEvtExt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, ResMgr_EvtHdl_t *pEvt);
__SLDPM_FREE__ void MediaTaskStgr_HandleHeadsetStatusChanged(CmdMgrStgrHdl_t pStgrHdl);
__SLDPM_FREE__ void MediaTaskStgr_HandleBtHeadsetStatusChanged(CmdMgrStgrHdl_t pStgrHdl);
__SLDPM_FREE__ void MediaTaskStgr_HandleResumeRestart(CmdMgrStgrHdl_t pStgrHdl);
ResMgr_CmdHdl_t MediaTaskStgr_FindRealExecCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCmdHdl);
ResMgr_ErrorCode_e MediaTaskStgr_IsHWScalarOccupied(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ bool MediaTaskStgr_IsRealExecCmd(ResMgr_CmdHdl_t pCmdHdl);
bool MediaTaskStgr_IsOccupyHWScalarCmd(ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_FindCmdAndCheckAudioPause(u16 uIndex, void **ppOwner, void *pCusData);
__SLDPM_FREE__ void MediaTaskStgr_SyncBackgroundVolume(CmdMgrStgrHdl_t pStgrHdl, u8 *pVolume, u8 *pRange);
__SLDPM_FREE__ void MediaTaskStgr_SwitchPathForVoiceChan(CmdMgrStgrHdl_t pStgrHdl);
__SLDPM_FREE__ void MediaTaskStgr_SetResourceConfig(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, ResMgr_ConfigId_e eCfgId, ResMgr_ConfigSet_e eCfgSet);
__SLDPM_FREE__ u16 MediaTaskStgr_StartBt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t *pCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_StopBt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t *pCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_EndBt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t *pCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_ForceStopBt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t *pCmdHdl);
__SLDPM_FREE__ u16 MediaTaskStgr_ForceStopM2(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t *pCmdHdl);
__SLDPM_FREE__ void MediaTaskStgr_InformBtStatusChangeComplete(CmdMgrStgrHdl_t pStgrHdl);
__SLDPM_FREE__ void MediaTaskStgr_InformBtCmdStatus(CmdMgrStgrHdl_t pStgrHdl, bool bBtStart);
#ifdef __BLUETOOTH_A2DP_MMI__
u16 MediaTaskStgr_RestartPlay(u16 uIndex, void **ppOwner, void *pCusData);
#endif
#endif //__MEDIATASKSTGRITF_H__

