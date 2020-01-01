////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file DBL_Gps.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of GPS.
*
*/

#ifndef __DBL_GPS_H__
#define __DBL_GPS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
#include "esl_gps_itf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_GpsEvtNotify(u16 uSenderId, u32 uUserValue, ABL_GpsInfo_t *pNotifyInfo);
void DBL_GpsCmnCb(u16 uSenderId, u32 uUserValue, esl_GpsInfo_t *pGpsInfo);
void DBL_GpsStopCnfCb(u16 uSenderId, u32 uUserValue, esl_GpsInfo_t *pGpsInfo);
ABL_GpsErrCode_e DBL_GpsRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_GpsOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsReadData(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGpsIoctl(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_GpsChangePSMode(ResMgr_CmdHdl_t pCurCmdHdl);
ABL_GpsErrCode_e DBL_MmlGpsRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
s16 DBL_MmlGpsOpen(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGpsClose(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGpsStart(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGpsStop(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_MmlGpsReadData(ResMgr_CmdHdl_t pCurCmdHdl);
void DBL_MmlGpsEvtNotify(u16 uSenderId, u32 uUserValue, MmlGpsNotify_t *pNotifyInfo);
#endif //__DBL_GPS_H__

