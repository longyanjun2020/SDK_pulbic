/**
* @file DBL_Gss.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of GSS.
*
*/

#ifndef __DBL_GSS_H__
#define __DBL_GSS_H__

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
void DBL_MmlGssRenderCb(u16 uSenderId, u32 uUserValue, MmlGameResult_e eErrCode, MmlGameResponse_t *pGssInfo);
__SLDPM_FREE__ void DBL_MmlGssImageCmnCb(u16 uSenderId, u32 uUserValue, MmlImageResult_e eErrCode, MmlImageResponse_t *pGssInfo);
void DBL_GssCmnCb(u16 uSenderId, u32 uUserValue, esl_GssErrCode_e eErrCode, esl_GssInfo_t *pGssInfo);
s16 DBL_GssOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GssCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GssSetEXIF(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderInput(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssImageGetDecodingCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderGetCapability(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderGetInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssRenderCleanUp(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_GssErrCode_e DBL_MmlGssRenderRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_GssErrCode_e DBL_GssRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_MmlGssUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
__SLDPM_FREE__ ABL_GssErrCode_e DBL_MmlGssImageRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_MmlGssSetEXIF(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssDecodeRegion(ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ s16 DBL_MmlGssDecodeExt(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssDecodeSync(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssEncode(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssGetImageInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssGetRapidInfo(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssDecodeNextFrame(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssOpenConvertPlayer(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssCloseConvertPlayer(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssOpenConvert(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssCloseConvert(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGssConvertColor(ResMgr_CmdHdl_t pCurCmdHdl);
#endif //__DBL_GSS_H__

