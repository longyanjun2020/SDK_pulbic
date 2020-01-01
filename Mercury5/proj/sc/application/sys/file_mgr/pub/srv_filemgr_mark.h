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
* @file    srv_filemgr_mark.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_MARK_H__
#define __SRV_FILEMGR_MARK_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "srv_filemgr_data_types.h"

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// Mark Operations
/*=============================================================*/
MAE_Ret FileMgrCreateMarkList(FileMgr_WChar *pSrcURL, FileMgrHandleID_t *pHandleID, u32 nUpperBound);
MAE_Ret FileMgrUpdateMarkList(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret FileMgrUpdateMarkListWithoutSubfolder(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret FileMgrQueryMarkListNumberID(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrQueryMarkListID(FileMgrHandleID_t nHandleID, u32 nStartIndex, FileMgrMarkListID_t *pMarkListIDData);
MAE_Ret FileMgrQueryIsMarkedMarkListID(FileMgrHandleID_t nHandleID, VFS_FileID_t nFileID);
MAE_Ret FileMgrMarkAll(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID);
MAE_Ret FileMgrMarkAllEx(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID, FileMgrMarkComp_Fxp pCompFunc, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrUnMarkAllByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL);
MAE_Ret FileMgrQueryMarkedNumberByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL, u32 *pMarkNumber);
MAE_Ret FileMgrDestoryMarkList(FileMgrHandleID_t nHandleID);

#endif// __SRV_FILEMGR_MARK_H__
