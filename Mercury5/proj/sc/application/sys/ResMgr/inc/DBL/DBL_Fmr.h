/**
* @file DBL_Fmr.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of FM Radio.
*
*/

#ifndef __DBL_FMR_H__
#define __DBL_FMR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "esl_fmr_itf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_FmrCmnCb(u16 uSenderId, u32 uUserValue, esl_FmrErrCode_e eErrCode, esl_FmrInfo_t *pFmrInfo);
void DBL_MmlFmrCmnCb(u16 uSenderId, u32 uUserValue, MmlRadioResult_e eErrCode, MmlRadioResponse_t *pFmrInfo);
s16 DBL_MmlFmrPowerOn(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrPowerOff(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetBand(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetFrequency(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetArea(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetMute(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetStereo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSearchChannel(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrCancelSearch(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrGetChanInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrGetChipInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_FmrErrCode_e DBL_MmlFmrRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_FmrErrCode_e DBL_FmrRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_MmlFmrUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
s16 DBL_MmlFmrSetCarrierThreshold(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrGetCapability(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_FmrEvtNotify(u16 uSenderId, u32 uUserValue, DBL_FmrNotifyInfo *pNotifyInfo);
s16 DBL_FmrRegNotify(u16 uEvtType, void *pCusData, DBL_FmrNotifyCb FmrNotifyCb);
s16 DBL_FmrRecStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrRecStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrRecSaveFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrRecDiscardFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_FmrGetRecFileName(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_FmrErrCode_e DBL_MmlFmrRecRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_MmlFmrRecStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrRecStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrTerminateRec(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlFmrSetRecordSetting(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_MmlFmrRecEvtNotify(u16 uSenderId, u32 uUserValue, MmlAudioNotify_t *pNotifyInfo);
void DBL_MmlFmrEvtNotify(u16 uSenderId, u32 uUserValue, MmlRadioNotify_t *pNotifyInfo);
s16 DBL_MmlFmrGetChanInfo(ResMgr_CmdHdl_t pCurCmdHdl);
#endif //__DBL_FMR_H__

