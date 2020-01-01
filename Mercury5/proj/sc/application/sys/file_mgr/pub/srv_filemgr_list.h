/**
* @file srv_filemgr_list.h
*
*
*
*/
#ifndef __SRV_FILEMGR_LIST_H__
#define __SRV_FILEMGR_LIST_H__

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
__SLDPM_FREE__ MAE_Ret FileMgrOpenFolderHandle(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL);
__SLDPM_FREE__ MAE_Ret FileMgrGetFolderFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber, FileMgrCbData_t *pCbData);
__SLDPM_FREE__ MAE_Ret FileMgrSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
__SLDPM_FREE__ MAE_Ret FileMgrCloseFolderHandle(FileMgrHandleID_t nHandleID);

/*=============================================================*/
// List Folder Operations
// GetFolderFile+List+Soritng(Sync)
/*=============================================================*/
MAE_Ret FileMgrSyncOpenFolderHandle(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL);
MAE_Ret FileMgrSyncGetFolderFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrSyncSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc);
MAE_Ret FileMgrSyncListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrSyncCloseFolderHandle(FileMgrHandleID_t nHandleID);

/*=============================================================*/
// Search Operations
// Search(with partial list, filter, search)(Async)
/*=============================================================*/
MAE_Ret FileMgrCreateSearchMarkListWithLevel(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID,FileMgr_WChar *pStrURL, u32 *pFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData, u8 nTraversalLevel);
MAE_Ret FileMgrCreateSearchMarkList(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID,FileMgr_WChar *pStrURL, u32 *pFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrListSearchedFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrListSearchedFolderGetURL(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nListSize, FileMgrSearchURL_t *pListURL);
MAE_Ret FileMgrGetSearchedFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrDestorySearchMarkList(FileMgrHandleID_t nHandleID);

/*=============================================================*/
// Search Operations
// Search(with partial list, filter, search)(Sync)
/*=============================================================*/
MAE_Ret FileMgrSyncCreateSearchMarkList(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID,FileMgr_WChar *pStrURL, u32 *pFileNumber, FileMgrFindComp_Fxp pSearchFunc);
MAE_Ret FileMgrSyncListSearchedFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrSyncListSearchedFolderGetURL(FileMgrHandleID_t nHandleID, u32 nStartIndex, FileMgr_WChar *pListURL);
MAE_Ret FileMgrSyncGetSearchedFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrSyncDestorySearchMarkList(FileMgrHandleID_t nHandleID);

#endif //__SRV_FILEMGR_LIST_H__
