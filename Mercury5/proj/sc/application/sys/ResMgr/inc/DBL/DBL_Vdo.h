/**
* @file DBL_Vdo.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of video.
*
*/

#ifndef __DBL_VDO_H__
#define __DBL_VDO_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "esl_vdo_itf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
s16 DBL_VdoOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_MmlVdoCmnCb(u16 uSenderId, u32 uUserValue, MmlVideoResult_e eErrCode, MmlVideoResponse_t *pVdoInfo);
s16 DBL_MmlVdoGetPosition(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoGetFileInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoSetPlaySpeed(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoSetPosition(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoResetWindow(ResMgr_CmdHdl_t pCurCmdHdl);
#ifdef __MMI_STEREO_VIDEO__
s16 DBL_MmlVdoSetConfiguration(ResMgr_CmdHdl_t pCurCmdHdl);
#endif
s16 DBL_MmlVdoStopPlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoPausePlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoResumePlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoGetMemInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoGetPlaybackCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoPlay(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoGetInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoDecodeFirstFrameAsync(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoCancelDecodeFirstFrame(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoSeek(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoCancelSeek(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_VdoErrCode_e DBL_MmlVdoRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_MmlVdoOpenUpdate(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
void DBL_MmlVdoUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
void DBL_MmlVdoEvtNotify(u16 uSenderId, u32 uUserValue, MmlVideoNotify_t *pNotifyInfo);
#endif //__DBL_VDO_H__

