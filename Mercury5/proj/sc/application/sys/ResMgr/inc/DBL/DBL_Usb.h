/**
* @file DBL_Usb.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of USB.
*
*/

#ifndef __DBL_USB_H__
#define __DBL_USB_H__

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
void DBL_UsbCmnCb(u16 uSenderId, u32 uUserValue, esl_UsbErrCode_e eErrCode, esl_UsbInfo_t *pUsbInfo);
s16 DBL_UsbOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbAttach(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbAttachAndPolling(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbStopPolling(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_UsbRegNotify(u16 uEvtType, void *pCusData, DBL_UsbNotifyCb UsbNotifyCb);
void DBL_UsbEvtNotify(u16 uSenderId, u32 uUserValue, DBL_UsbNotifyInfo *pNotifyInfo);
ABL_UsbErrCode_e DBL_UsbRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
ABL_UsbErrCode_e DBL_MmlUsbRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_MmlUsbUpdatePos(ResMgr_CmdHdl_t pCurCmdHdl, void *pRspData, u16 uAttribute);
s16 DBL_MmlUsbOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlUsbClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlUsbAttach(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_MmlUsbEvtNotify(u16 uSenderId, u32 uUserValue, MmlUsbNotify_t *pNotifyInfo);
#endif //__DBL_USB_H__

