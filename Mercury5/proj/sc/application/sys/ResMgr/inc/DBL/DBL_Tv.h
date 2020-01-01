/**
* @file DBL_Tv.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of analog TV.
*
*/
#ifndef __DBL_TV_H__
#define __DBL_TV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_TvErrCode_e DBL_TvRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_TvCmnCb(u16 uSenderId, u32 uUserValue, esl_TvErrCode_e eErrCode, esl_TvInfo_t *pTvInfo);
s16 DBL_TvOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvSetConfig(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvGetInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvGetEmInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvSwitchChannel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvScanChannel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvPreview(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvCapture(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvResetWindow(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvSetShutterSound(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvGetFileName(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_TvRegNotify(u16 uEvtType, void *pCusData, DBL_TvNotifyCb TvNotifyCb);
void DBL_TvEvtNotify(u16 uSenderId, u32 uUserValue, DBL_TvNotifyInfo *pNotifyInfo);
void DBL_MmlTvImageEvtNotify(u16 uSenderId, u32 uUserValue, MmlImageNotify_t *pNotifyInfo);
s16 DBL_MmlTvOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvSetConfig(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvGetInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvGetEmInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvSwitchChannel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvScanChannel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvPreview(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvCapture(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvGetFileName(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlTvResetWindow(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_TvErrCode_e DBL_MmlTvRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_TvErrCode_e DBL_MmlTvImageRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
#endif //__DBL_TV_H__
