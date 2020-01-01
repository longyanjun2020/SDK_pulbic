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
* @file    srv_filemgr_register_path.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_REGISTER_PATH_H__
#define __SRV_FILEMGR_REGISTER_PATH_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "srv_filemgr_data_types.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgrOperation_e Operation_e;
    FileMgr_WChar *pPath;
    u8 nVolumeID;
}RegisterData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// Query Operations
/*=============================================================*/
//QueryPathStatus
MAE_Ret FileMgrSendQueryURLStatus(FileMgr_WChar *pStrURL, FileMgrOperation_e *pOperation);
//QuerySingleOperation
MAE_Ret FileMgrSendIsURLAllowOperation(const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);

/*=============================================================*/
// Lock Operations
/*=============================================================*/
//LockPathStatus
MAE_Ret FileMgrSendLockURLStatus(FileMgrHandleID_t *pHandle, const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);
//UnLockPathStatus
MAE_Ret FileMgrSendUnLockURLStatus(FileMgrHandleID_t nHandle);

/*=============================================================*/
// Monitor Operations
/*=============================================================*/
//RegMonitorURL
MAE_Ret FileMgrSendMonitorURL(FileMgrHandleID_t *pHandle, FileMgr_WChar *pStrURL, FileMgrOperation_e nMode_e, FileMgrCbData_t *pCbData);
//DeRegMonitorURL
MAE_Ret FileMgrSendDeMonitorURL(FileMgrHandleID_t nHandle);

/*=============================================================*/
// Query Operations
/*=============================================================*/
//QueryPathStatus
MAE_Ret FileMgrQueryURLStatus(FileMgr_WChar *pStrURL, FileMgrOperation_e *pOperation);
//QuerySingleOperation
MAE_Ret FileMgrIsURLAllowOperation(const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);

/*=============================================================*/
// Lock Operations
/*=============================================================*/
//LockPathStatus
MAE_Ret FileMgrLockURLStatus(FileMgrHandleID_t *pHandle, const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);
//UnLockPathStatus
MAE_Ret FileMgrUnLockURLStatus(FileMgrHandleID_t nHandle);

/*=============================================================*/
// Monitor Operations
/*=============================================================*/
//RegMonitorPath
__SLDPM_FREE__ MAE_Ret FileMgrMonitorURL(FileMgrHandleID_t *pHandle, FileMgr_WChar *pStrURL, FileMgrOperation_e nMode_e, FileMgrCbData_t *pCbData);
//DeRegMonitorPath
__SLDPM_FREE__ MAE_Ret FileMgrDeMonitorURL(FileMgrHandleID_t nHandle);

#endif// __SRV_FILEMGR_REGISTER_PATH_H__
