//////////////////////////////////////////////////////////////////////////////////
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
* @file    srv_filemgr_batch.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_BATCH_H__
#define __SRV_FILEMGR_BATCH_H__
/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "srv_filemgr_data_types.h"

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// Single-files Operations
/*=============================================================*/
//Delete(Sync)
MAE_Ret FileMgrSyncDelete(FileMgr_WChar *pStrURL);
//Delete(ASync)
MAE_Ret FileMgrDelete(FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL, FileMgrCbData_t *pCbData);
//Move(ASync)
MAE_Ret FileMgrMove(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);
//MoveEx(Sync)
MAE_Ret FileMgrSyncMove(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL);
//Copy(ASync)
MAE_Ret FileMgrCopy(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);

/*=============================================================*/
// Multi-files Operations
/*=============================================================*/
//Delete(Multi-files)(Sync)
MAE_Ret FileMgrSyncDeleteFiles(FileMgr_FileList_t *pFileListCommand);

//Move(Multi-files)(Sync)
MAE_Ret FileMgrSyncMoveFiles(FileMgr_FileList_t *pFileListCommand);

//Move(Multi-files)(ASync)
MAE_Ret FileMgrMoveFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

//Move(Multi-files)(ASync)
MAE_Ret FileMgrCopyFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

//Copy(Multi-files)(Sync)
MAE_Ret FileMgrSyncCopyFiles(FileMgr_FileList_t *pFileListCommand);

//DeleteAll(Multi-files)(ASync)
MAE_Ret FileMgrDeleteAllFiles(VFS_PartialListFilter_t *pListFilter, FileMgr_WChar *pSrcURL, u32 *pHandleID, FileMgrCbData_t *pCbData);

//Delete(Multi-files)(ASync)
MAE_Ret FileMgrDeleteFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

//Delete for mark(Sync)
MAE_Ret FileMgrSyncDeleteMarkedFiles(u32 nMarkHandleID);

//Move for mark(Sync)
MAE_Ret FileMgrSyncMoveMarkedFiles(FileMgr_WChar *pDestURL, u32 nMarkHandleID);

//Copy for mark(Sync)
MAE_Ret FileMgrSyncCopyMarkedFiles(FileMgr_WChar *pDestURL, u32 nMarkHandleID);

/*=============================================================*/
// Multi-files Operations
/*=============================================================*/
//Copy for mark(ASync)
MAE_Ret FileMgrCopyMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);
//Move for mark(ASync)
MAE_Ret FileMgrMoveMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);
//Delete for mark(ASync)
MAE_Ret FileMgrDeleteMarkedFiles(FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

//Abort Batch command(Sync)
__SLDPM_FREE__ MAE_Ret FileMgrBatchCommandAbort(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrDeleteAbort(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrMoveAbort(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrCopyAbort(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrQueryBatchCommandStatus(ExecuteBatchCmdType_t *pBatchCmdType);

#endif //__SRV_FILEMGR_BATCH_H__
