/**
* @file DBL_VdoChat.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of VideoChat.
*
*/
#ifndef __VENDOR_SMALLROM__
#ifndef __DBL_VDOCHAT_H__
#define __DBL_VDOCHAT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "ABL_VdoChat.h"
#include "esl_vc_itf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_VdoChatCmnCb(u16 uSenderId, u32 uUserValue, esl_VcErrCode_e eErrCode, esl_VcInfo_t *pCamInfo);
s16 DBL_VdoChatOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatInit(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatExit(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatPreviewStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatPreviewStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatPreviewGetFrame(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VdoChatConvertImage(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_VdoChatErrCode_e DBL_VdoChatRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_VdoChatErrCode_e DBL_MmlVdoChatRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_MmlVdoChatInit(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatExit(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatPreviewStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatPreviewStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatPreviewGetFrame(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatConvertImage(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVdoChatSetFrameBuffSize(ResMgr_CmdHdl_t pCurCmdHdl);
#endif
#endif
