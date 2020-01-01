/**
* @file DBL_Vtm.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of video telephony.
*
*/

#ifndef __DBL_VTM_H__
#define __DBL_VTM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "ABL_Vtm.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_MmlVtmCmnCb(u16 uSenderId, u32 uUserValue, MmlVideoResult_e eErrCode, MmlVideoResponse_t *pVdoInfo);
s16 DBL_VtmOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VtmCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmSetConfig(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmStartRecord(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmStopRecord(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmSaveRecordFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmDiscardRecordFile(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlVtmAbortSavingFile(ResMgr_CmdHdl_t pCurCmdHdl);

void DBL_MmlVtmEvtNotify(u16 uSenderId, u32 uUserValue, MmlVideoNotify_t *pNotifyInfo);
void DBL_MmlVtmUpdateCusData(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
ABL_VtmErrCode_e DBL_MmlVtmRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);

#endif //__DBL_VTM_H__
