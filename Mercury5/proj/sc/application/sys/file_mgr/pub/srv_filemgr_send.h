/**
* @file filemgr_client.h
*
*
*
*/
#ifndef __SRV_FILEMGR_SEND_H__
#define __SRV_FILEMGR_SEND_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "srv_filemgr_data_types.h"

/*=============================================================*/
// Function Declarations
/*=============================================================*/

/*=============================================================*/
// List Folder Operations
// GetFolderFile+List+Soritng(ASync)
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret FileMgrSendOpenFolderHandle(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL);
__SLDPM_FREE__ MAE_Ret FileMgrSendGetFolderFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrSendSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc, FileMgrCbData_t *pCbData);
__SLDPM_FREE__ MAE_Ret FileMgrSendListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrSendCloseFolderHandle(FileMgrHandleID_t nHandleID);

/*=============================================================*/
// Search Operations
// Search(with partial list, filter, search)(Async)
/*=============================================================*/
MAE_Ret FileMgrSendCreateSearchMarkListWithLevel(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID,FileMgr_WChar *pStrURL, u32 *pFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData, u8 nTraversalLevel);
MAE_Ret FileMgrSendListSearchedFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrSendListSearchedFolderGetURL(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nListSize, FileMgrSearchURL_t *pListURL);
MAE_Ret FileMgrSendGetSearchedFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrSendDestorySearchMarkList(FileMgrHandleID_t nHandleID);

/*=============================================================*/
// File Command
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret FileMgrSendOpenFile(void **ppStreamResult, const FileMgr_WChar *pStrURL, const u8 *pMode, void *pOwner);
__SLDPM_FREE__ MAE_Ret FileMgrSendCloseFile(void *pStream);
MAE_Ret FileMgrSendNotifyOpenFile(void **ppStreamResult, const FileMgr_WChar *pStrURL, const u8 *pMode, void *pOwner);
MAE_Ret FileMgrSendNotifyCloseFile(void *pStream);

MAE_Ret FileMgrSendQueryOpenedFileStatus(const FileMgr_WChar *pStrURL);

//MarkAllFileByPath
MAE_Ret FileMgrSendMarkAll(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID);
//MarkAllFIlesByPath with compare func
MAE_Ret FileMgrSendMarkAllEx(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID, FileMgrMarkComp_Fxp pCompFunc, FileMgrCbData_t *pCbData);
//UnMarkAllFileByPath
MAE_Ret FileMgrSendUnMarkAllByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL);
//UnMarkQueryFileNumberByPath
MAE_Ret FileMgrSendQueryMarkedNumberByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL, u32 *pMarkNumber);

//Copy for mark(ASync)
MAE_Ret FileMgrSendCopyMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

//Delete files by filter (ASync)
MAE_Ret FileMgrSendDeleteFiles(FileMgr_FileList_t *pFileListCommand, u32 *pHandleID, FileMgrCbData_t *pCbData);

//Move(ASync)
MAE_Ret FileMgrSendMove(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);

//Copy(ASync)
MAE_Ret FileMgrSendCopy(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);

//Delete(ASync)
MAE_Ret FileMgrSendDelete(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, FileMgrCbData_t *pCbData);

//Delete(Sync)
MAE_Ret FileMgrSendSyncDelete(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, FileMgrCbData_t *pCbData);

//Move(Multi-files)(ASync)
MAE_Ret FileMgrSendMoveFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

//Copy(Multi-files)(ASync)
MAE_Ret FileMgrSendCopyFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

//Delete for mark(ASync)
MAE_Ret FileMgrSendDeleteAllFiles(VFS_PartialListFilter_t *pListFilter, FileMgr_WChar *pSrcURL, u32 *pHandleID, FileMgrCbData_t *pCbData);

//Delete for mark(ASync)
MAE_Ret FileMgrSendDeleteMarkedFiles(FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

//Move for mark(ASync)
MAE_Ret FileMgrSendMoveMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

//Abort Command
__SLDPM_FREE__ MAE_Ret FileMgrSendBatchCommandAbort(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrSendNotifyBackLightOff(u8 bIsBackLightOff);

MAE_Ret FileMgrSendPauseAsyncFormat(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrSendResumeAsyncFormat(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrSendPauseAsyncCheckDisk(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrSendResumeAsyncCheckDisk(FileMgrHandleID_t nHandleID);

#endif //__SRV_FILEMGR_SEND_H__
