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
* @file    srv_mmi_filemgr.c
* @version
* @brief
*
*/

#ifndef __SRV_MMI_FILEMGR_H__
#define __SRV_MMI_FILEMGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "srv_filemgr_data_types.h"
#include "srv_filemgr.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct
{
    FileMgrCallback_Fxp Callback;
    void *pCusData;
} MmiFileMgrCallbackData_t;

typedef struct
{
    s32 nErrCode;
    u8 *pBuffer;
    u32 nBufferLen;
} FileMgrStream_WriteCnf_Info_t;

typedef struct
{
    s32 nErrCode;
    u8 *pBuffer;
    u32 nBufferLen;
} FileMgrStream_ReadCnf_Info_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

//For media notify
MAE_Ret FileMgrNotifyFileOpened(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrURL, const u8 *pMode, void *pOwner);
MAE_Ret FileMgrNotifyFileClosed(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrDeleteFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

void FileMgrListNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrSortNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrSearchNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrCopyNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrMoveNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrDeleteNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrDeleteAllNotifyIf(void *pUserData, vm_msg_t *pMsg);
__SLDPM_FREE__ void FileMgrMonitorPathNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrRmDirNotifyIf(void *pUserData, vm_msg_t *pMsg);
void FileMgrFormatNotifyIf(void *pUserData, vm_msg_t *pData);
void FileMgrChkdskNotifyIf(void *pUserData, vm_msg_t *pData);
void FileMgrReadyNotifyIf(void *pUserData, vm_msg_t *pData);
void FileMgrSuspendNotifyIf(void *pUserData, vm_msg_t *pData);

void FileMgrReadyNotify(void);
MAE_Ret FileMgrNotifyBackLightOff(u8 bIsBackLightOff);

/*=============================================================*/
// File Stream functions
/*=============================================================*/
void FileMgrWriteNotifyIf(void *pRecipient, struct vm_msg *pData);
__SLDPM_FREE__ void FileMgrReadNotifyIf(void *pRecipient, struct vm_msg *pData);

/**
 *  FileMgr_Stream_WriteCnf
 *  @brief  Handle function of mmi_vfs_write_cnf_if(). Need to callback to AP user here.
 *
 *  @param  pStream   Pointer to the FStream interface
 *  @param  pWriteCnf	Messages returns from VFS
 */

void FileMgr_Stream_WriteCnf(void *pObj, FileMgrStream_WriteCnf_Info_t *pWriteCnf);

/**
 *  FileMgr_Stream_ReadCnf
 *  @brief  Handle function of mmi_vfs_read_cnf_if(). Need to callback to AP user here.
 *
 *  @param  pStream   Pointer to the FStream interface
 *  @param  pWriteCnf	Messages returns from VFS
 */

void FileMgr_Stream_ReadCnf(void *pObj, FileMgrStream_ReadCnf_Info_t *pReadCnf);

// ZINC: temporary solution for those typeless fstream callbacks
void FileMgrStream_write_cb(void *pIssuer, void *pObj, u32 nParam);

#endif //__SRV_MMI_FILEMGR_H__
