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
* @file    srv_filemgr.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_H__
#define __SRV_FILEMGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "srv_filemgr_data_types.h"
#include "mmi_mae_retcode.h"

#if defined(__SDK_SIMULATION__) && (_MSC_VER >= 1500) && defined(FILE_MGR_STANDALONE_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VC_MEM_DBG
#include "memory.h"
#include "string.h"
#include "assert.h"
#include "ut_utility.h"
#else
#include "mmi_mae_common_def.h"
#endif

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define FMGR_LEVEL      (_SYS | LEVEL_30)

/*=============================================================*/
// Disc Related Operations
/*=============================================================*/
MAE_Ret FileMgrCheckFreeSpace(const FileMgr_WChar *pStrURL, u32 *pTotalSize, u32 *pRemainSize);
MAE_Ret FileMgrIsExist(const FileMgr_WChar *pStrURL);
MAE_Ret FileMgrGetInfo(const FileMgr_WChar *pStrURL, VFS_PartialListFileInfo_t *pFileInfo);
MAE_Ret FileMgrSetFileAttr(const FileMgr_WChar *pStrURL, u32 nFileAttr);
MAE_Ret FileMgrGetRenameLength(const FileMgr_WChar *pStrURL, u32 *pLength);

//Rename(Sync)
MAE_Ret FileMgrRenameFile(const FileMgr_WChar *pSrcURL, const FileMgr_WChar *pStrDestName);
//Format(Sync)
MAE_Ret FileMgrFormat(u32 nVolumeID);

MAE_Ret FileMgrAsyncFormat(FileMgrHandleID_t *pHandleID, u32 nVolumeID, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrAsyncCheckDisk(FileMgrHandleID_t *pHandleID, u32 nVolumeID, u32 nChkdskOperation, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrPauseAsyncCheckDisk(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrResumeAsyncCheckDisk(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrPauseAsyncFormat(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrResumeAsyncFormat(FileMgrHandleID_t nHandleID);

//Suspend(Sync)
MAE_Ret FileMgrSetSuspend(FileMgrHandleID_t *pHandleID, u8 bIsSuspend, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrQuerySuspend(void);

/*=============================================================*/
// Folder Operations
/*=============================================================*/
//Folder-mkdir(Sync)
MAE_Ret FileMgrMkDir(const FileMgr_WChar *pStrURL);

//Folder-rmdir(ASync)
MAE_Ret FileMgrAsyncRmDir(u32 *pHandleID, FileMgr_WChar *pSrcURL, FileMgrCbData_t *pCbData);

//Folder-rmdir(Sync)
MAE_Ret FileMgrRmDir(const FileMgr_WChar *pStrURL);

/*=============================================================*/
// ID to File Convert Operations
/*=============================================================*/
MAE_Ret FileMgrIDToFileName(FileMgrMarkListID_t *pMarkListIDData, FileMgr_ListData_t *pMarkListInfoData);

//FileID+Path To URL (single)(Sync)
MAE_Ret FileMgrTransferFileIDToURL(VFS_FileID_t *pFileID, FileMgr_WChar *pSourctPath, FileMgr_WChar *pStrDestURL);

/*=============================================================*/
// Mount Operations
/*=============================================================*/
MAE_Ret FileMgrSDMount(u8 nVolumeID);
MAE_Ret FileMgrSDUnMount(u8 nVolumeID);
MAE_Ret FileMgrIsMounted(u8 nVolumeID);

MAE_Ret FileMgrSDMountVolume(u8 nVolumeID, u8 nSlot);
MAE_Ret FileMgrSDUnMountVolume(u8 nVolumeID);

MAE_Ret FileMgrQueryMountedVolToDev(u8 nVolumeID, u8 *pDeviceID);
MAE_Ret FileMgrQueryMountedDevToVol(u8 nDeviceID, u8 *pVolumeID);

/*=============================================================*/
// Destroy all command
/*=============================================================*/
void FileMgrDestoryAllCommand(char *pSbjName, u32 nSbjStatus, void *pUser);

//QueryVolumeStatus
MAE_Ret FileMgrQueryVolumeStatus(u32 eVolumeID);

//Query File system Disk State
MAE_Ret FileMgrQueryFsDiskState(VFS_VOL_TYPE eVolType,VFS_DiskStatus_e * pDiskState);

#endif //__SRV_FILEMGR_H__
