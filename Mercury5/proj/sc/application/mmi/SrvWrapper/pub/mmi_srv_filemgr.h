/**
* @file    mmi_srv_filemgr.h
* @brief The document describes the service wrapper interface of filemgr
*
*/

#ifndef __MMI_SRV_FILEMGR_H__
#define __MMI_SRV_FILEMGR_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_filemgr.h"
#include "mdl_vfs_struct.h"

/*=============================================================*/
// Variable Declarations
/*=============================================================*/

/** SrvFileMgrCheckFreeSpace
@brief  Get free space information to this volume

@param[in]      pStrURL             File url
@param[out]     totalSize           Place holder of total size in this volume, the unit is 1KB.
@param[out]     remainSize          Place holder of remaining size in this volume, the unit is 1KB.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Invalid File url
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCheckFreeSpace(const MAE_WChar* pStrURL, u32* totalSize, u32 *remainSize);

/** SrvFileMgrIsExist
@brief  Change if associated directory of file exist
@param[in]      pStrURL             File url

@retval MAE_RET_FILE_EXISTS         If successful.
@retval MAE_RET_NO_FILE             If an error happen. not exist.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret SrvFileMgrIsExist(const MAE_WChar* pStrURL);

/** SrvFileMgrGetInfo
@brief  Get file information

@param[in]      pStrURL             File url
@param[out]     pInfo               Place holder to file information

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Failed.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrGetInfo(const MAE_WChar *pStrURL, VFS_PartialListFileInfo_t *pFileInfo);

/** SrvFileMgrSetFileAttr
@brief set file attribute

@param[in]      pStrURL             File url
@param[in]      fileAttr            file attribute

#define ATTR_NORMAL 0x00     ///< file is normal type
#define ATTR_RDONLY 0x01     ///< read only
#define ATTR_HIDDEN 0x02     ///< hidden
#define ATTR_SYSTEM 0x04     ///< system
#define ATTR_SUBDIR 0x10     ///< directory
#define ATTR_ARCH   0x20     ///< archive

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Failed.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSetFileAttr(const MAE_WChar *pStrURL, FileMgrAttribute_e fileAttr);

/** SrvFileMgrGetRenameLength
@brief  Return the possible maximum rename length of the file/folder

@param[in]      pStrURL             file name
@param[out]     nLength             possible maximum length

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              Error happen, Fail to get length.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrGetRenameLength(const MAE_WChar* pStrURL, u32* nLength);


/*===========================================================================================*/

/** SrvFileMgrOpenFile
@brief  Open a file and get its fstream class

@param[out]     ppStream            get the Client of FStream Service; it can use to operate the Fstream Service
@param[in]      pStrURL             File url
@param[in]      nMode               The open mode of file
@param[in]      pOwner              IBase


@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. do not open the file
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret SrvFileMgrOpenFile(FileMgr_Stream_t **ppStream, const MAE_WChar* pStrURL, const u8 *nMode, IBase *pOwner);


/** SrvFileMgrCloseFile
@brief  Close a file

@param[out]     pIFStream           close file stream

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. do not open the file
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret SrvFileMgrCloseFile(FileMgr_Stream_t *pIFStream);


/** SrvFileMgrRename
@brief  Rename a file

@param[in]      pSrcURL             Source file to be renamed
@param[in]      pStrDestName        Destination file name "abc.123", cannot be a path

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error renaming a file, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrRename(const MAE_WChar* pSrcURL, const MAE_WChar* pStrDestName);


/** SrvFileMgrDelete
@brief  Delete a file

@param[out]     pHandleID           handle ID for delete
@param[in]      pStrURL             File url
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error renaming a file, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDelete(FileMgrHandleID_t *pHandleID, MAE_WChar* pStrURL, FileMgrCbData_t *pCbData);

/** SrvFileMgrSyncDelete
@brief  Delete one file sync API
@param[in]      pStrPath            File url

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error delete a file, invalid path
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncDelete(MAE_WChar* pStrURL);

/** SrvFileMgrMove
@brief  Delete a file

@param[out]     pHandleID           handle ID for move
@param[in]      pStrSrcURL          source File url
@param[in]      pStrDestURL         dest File url
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error renaming a file, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMove(FileMgrHandleID_t *pHandleID, const MAE_WChar* pStrSrcURL, const MAE_WChar* pStrDestURL, FileMgrCbData_t *pCbData);

/** SrvFileMgrSyncMove
@brief  move a file in the same folder

@param[out]     pHandleID           handle ID for move
@param[in]      pStrSrcURL          source File url
@param[in]      pStrDestURL         dest File url

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED                 If an error happen. Error renaming a file, or invalid path.
@retval MAE_RET_BAD_PARAM         If input parameter error.
@retval MAE_RET_NOT_SUPPORTED If storage of source file and destination file is different
*/
MAE_Ret SrvFileMgrSyncMove(FileMgrHandleID_t *pHandleID, const MAE_WChar* pStrSrcURL, const MAE_WChar* pStrDestURL);



/** SrvFileMgrCopy
@brief  Copy file

@param[in]      pHandleID
@param[in]      pStrPathSrc         Source file to be copied
@param[out]     pStrPathDest        Destination file name to copy
@param[in]      pfnFileMgrCB        Call back function pointer.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              Error renaming a file, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCopy(FileMgrHandleID_t *pHandleID, const MAE_WChar* pStrSrcURL, const MAE_WChar* pStrDestURL, FileMgrCbData_t *pCbData);

/** SrvFileMgrCopyAbort
@brief  Copy file abort

@param[in]      pHandleID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              Error happen, do not abort copy.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCopyAbort(u32 pHandleID);

/** SrvFileMgrMkDir
@brief  create a directory

@param[in]      pStrURL             File url

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. File url is invalid or no memory
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMkDir(const MAE_WChar* pStrURL);

/** SrvFileMgrAsyncRmDir(Async)
@brief  Delete a folder by url

@param[out]     pHandleID           handle for rmdir
@param[in]      pStrURL             File url
@param[in]      pfnFileMgrCB        Call back function pointer.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. File url is invalid or no memory
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrAsyncRmDir(FileMgrHandleID_t *pHandle, MAE_WChar* pStrURL, FileMgrCbData_t *pCbData);

/** SrvFileMgrRmDir(Sync)
@brief  Delete a folder; limit: if the folder have too many file, it may timeout.

@param[in]      pStrURL             File url to be deleted

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrRmDir(const MAE_WChar* pStrURL);

/** SrvFileMgrOpenFolderHandle(ASync)
@brief  open folder and set file filter, then get handle

@param[in]      pListFilter         list file filter
@param[out]     pHandleID           folder handle
@param[in]      pStrURL             File url

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrOpenFolderHandle(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, MAE_WChar *pStrURL);

/** SrvFileMgrGetFolderFileNumber(ASync)
@brief  get file number of folder

@param[in]      pHandleID           folder handle
@param[out]     pFileNumber         file number of folder
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrGetFolderFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber, FileMgrCbData_t *pCbData);

/** SrvFileMgrSetSortingMethod(ASync)
@brief  set sorting function

@param[in]      pHandleID           folder handle
@param[in]      pCompareFunc        compare function for sorting
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc, FileMgrCbData_t *pCbData);

/** SrvFileMgrListFolder(ASync)
@brief list folder data

@param[in]      pHandleID           folder handle
@param[in]      nStartIndex         start index for list folder
@param[in]      nFileListSize       size for list folder
@param[out]     pListData           file data for list result

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);

/** SrvFileMgrCloseFolderHandle(ASync)
@brief close folder for release data

@param[in]      pHandleID           folder handle

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCloseFolderHandle(FileMgrHandleID_t nHandleID);

/** SrvFileMgrSyncOpenFolderHandle(Sync)
@brief  open folder and set file filter, then get handle

@param[in]      pListFilter         list file filter
@param[out]     pHandleID           folder handle
@param[in]      pStrURL             File url

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncOpenFolderHandle(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, MAE_WChar *pStrURL);

/** SrvFileMgrSyncGetFolderFileNumber(Sync)
@brief  get file number of folder

@param[in]      pHandleID           folder handle
@param[out]     pFileNumber         file number of folder

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncGetFolderFileNumber(FileMgrHandleID_t nHandleID, u32 *pFileNumber);

/** SrvFileMgrSyncSetSortingMethod(Sync)
@brief  set sorting function

@param[in]      pHandleID           folder handle
@param[in]      pCompareFunc        compare function for sorting
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc);

/** SrvFileMgrSyncListFolder(Sync)
@brief list folder data

@param[in]      pHandleID           folder handle
@param[in]      nStartIndex         start index for list folder
@param[in]      nFileListSize       size for list folder
@param[out]     pListData           file data for list result

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);

/** SrvFileMgrSyncCloseFolderHandle(Sync)
@brief close folder for release data

@param[in]      pHandleID           folder handle

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSyncCloseFolderHandle(FileMgrHandleID_t nHandleID);

/** SrvFileMgrCreateMarkList(Sync)
@brief create list for mark

@param[in]      pListFilter         list file filter
@param[in]      pSrcURL             File url
@param[out]     pHandleID           mark handle
@param[in]      nUpperBound         UpperBound of mark

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
__SLDPM_FREE__ MAE_Ret SrvFileMgrCreateMarkList(VFS_PartialListFilter_t *pListFilter, MAE_WChar *pSrcURL, u32 *pHandleID, u32 nUpperBound);

/** SrvFileMgrUpdateMarkList(Sync)
@brief mark file by file id

@param[out]     pHandleID           mark handle
@param[in]      pMarkListChangeIDData file id for mark

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrUpdateMarkList(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);

/** SrvFileMgrQueryMarkListNumberID(Sync)
@brief query number of marked file

@param[in]     nHandleID           mark handle
@param[out]    pFileNumber         query number of mark

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryMarkListNumberID(FileMgrHandleID_t nHandleID, u32 *pFileNumber);

/** SrvFileMgrQueryIsMarkedMarkListID(Sync)
@brief close folder for release data

@param[in]     nHandleID            mark handle
@param[in]     nFileID              fileID
@param[out]    bMark                query status of fileID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryIsMarkedMarkListID(FileMgrHandleID_t nHandleID, VFS_FileID_t nFileID, boolean *bMark);

/** SrvFileMgrQueryMarkListID(Sync)
@brief query marked file data

@param[in]     nHandleID            mark handle
@param[in]     nStartIndex          start index of mark list
@param[in]     nFileListSize        number in one query
@param[out]    pMarkListIDData      result of query

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryMarkListID(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgrMarkListID_t *pMarkListIDData);

/** SrvFileMgrMarkAll(Sync)
@brief mark all file in one folder; it need to open folder for get folder handle

@param[in]     nHandleID            mark handle
@param[in]     nFolderHandleID      folder handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMarkAll(FileMgrHandleID_t nHandleID, FileMgrHandleID_t nFolderHandleID);


/** SrvFileMgrMarkAllEx(Sync)
@brief mark all file in one folder; it need to open folder for get folder handle

@param[in]     nHandleID               mark handle
@param[in]     nFolderHandleID     folder handle ID
@param[in]     pCompFunc             compare function for mark
@param[in]     pCbData                 call back function


@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED                 If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvFileMgrMarkAllEx(FileMgrHandleID_t nHandleID, FileMgrHandleID_t nFolderHandleID, FileMgrMarkComp_Fxp pCompFunc, FileMgrCbData_t *pCbData);


/** SrvFileMgrUnMarkAllByURL(Sync)
@brief remove all marked file by URL

@param[in]     nHandleID            mark handle
@param[in]     pStrURL              url of folder

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrUnMarkAllByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL);

/** SrvFileMgrQueryMarkedNumberByURL(Sync)
@brief query marked file number by URL

@param[in]     nHandleID            mark handle
@param[in]     pStrURL              url of folder
@param[out]    pMarkNumber          number of marked file

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryMarkedNumberByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL, u32 *pMarkNumber);

/** SrvFileMgrDestoryMarkList(Sync)
@brief destroy mark list

@param[in]     nHandleID            mark handle

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDestoryMarkList(FileMgrHandleID_t nHandleID);

/** SrvFileMgrIDToFileName(Sync)
@brief convert file ID to FileInfo

@param[in]     pMarkListIDData            file id & url
@param[out]    pMarkListInfoData          file info

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrIDToFileName(FileMgrMarkListID_t *pMarkListIDData, FileMgr_ListData_t *pMarkListInfoData);

/** SrvFileMgrCreateSearchMarkListWithLevel(ASync)
@brief create search handle with level condition

@param[in]     pListFilter          file filter
@param[out]    pHandleID            search handle
@param[in]     pStrURL              folder url
@param[in]     nFileNumber          file number
@param[in]     pSearchFunc          compare function
@param[in]     pCbData              callback function
@param[in]     nTraversalLevel      level condition

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCreateSearchMarkListWithLevel(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t*pHandleID, MAE_WChar *pStrURL, u32 *nFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData, u8 nTraversalLevel);

/** SrvFileMgrCreateSearchMarkList(ASync)
@brief create search handle

@param[in]     pListFilter          file filter
@param[out]    pHandleID            search handle
@param[in]     pStrURL              folder url
@param[in]     nFileNumber          file number
@param[in]     pSearchFunc          compare function
@param[in]     pCbData              callback function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Error removing a folder, or invalid path.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCreateSearchMarkList(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t*pHandleID, MAE_WChar *pStrURL, u32 *nFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData);

/** SrvFileMgrListSearchedFolder(ASync)
@brief list data by search result

@param[in]       nHandleID          search handle ID
@param[in]       nStartIndex        start index
@param[in]       nFileListSize      number in one query
@param[out]      pMarkListidData    result of query

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrListSearchedFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pMarkListidData);

/** SrvFileMgrDestorySearchMarkList(ASync)
@brief release search handle

@param[in]       nHandleID          search handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDestorySearchMarkList(FileMgrHandleID_t nHandleID);

/** SrvFileMgrDeleteFiles(ASync)
@brief Delete(Multi-files)

@param[in]       pFileListCommand   file url array
@param[out]      pHandleID          batch command handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDeleteFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrMoveFiles(ASync)
@brief Move(Multi-files)

@param[in]       pFileListCommand   file url array
@param[out]      pHandleID          batch command handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMoveFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrCopyFiles(ASync)
@brief Copy(Multi-files)

@param[in]       pFileListCommand   file url array
@param[out]      pHandleID          batch command handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCopyFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrDeleteMarkedFiles(ASync)
@brief Delete(Multi-files) for mark(ASync)

@param[out]      pHandleID          batch command handle ID
@param[in]       nMarkHandleID      mark handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDeleteMarkedFiles(FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrMoveMarkedFiles(ASync)
@brief Move(Multi-files) for mark(ASync)

@param[in]       pDestURL           dest url
@param[out]      pHandleID          batch command handle ID
@param[in]       nMarkHandleID      mark handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMoveMarkedFiles(MAE_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrCopyMarkedFiles(ASync)
@brief Copy(Multi-files) for mark(ASync)

@param[in]       pDestURL           dest url
@param[out]      pHandleID          batch command handle ID
@param[in]       nMarkHandleID      mark handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrCopyMarkedFiles(MAE_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrBatchCommandAbort(ASync)
@brief Delete all, for special used of FileMgrAP

@param[in]       pListFilter        filter file size, type, extension name
@param[in]       pSrcURL            file url
@param[out]      pHandleID          batch command handle ID
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDeleteAllFiles(VFS_PartialListFilter_t *pListFilter, FileMgr_WChar  *pSrcURL, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);

/** SrvFileMgrBatchCommandAbort(Sync)
@brief Abort Batch command

@param[in]       nHandleID          batch command handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrBatchCommandAbort(FileMgrHandleID_t nHandleID);

/** SrvFileMgrTransferFileIDToURL(Sync)
@brief Get Url form Path and FileID

@param[in]       pFileID            File ID
@param[in]       pSourctPath        File url
@param[out]      pStrDestURL        File URL with file name

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrTransferFileIDToURL(VFS_FileID_t *pFileID, MAE_WChar *pSourctPath, MAE_WChar *pStrDestURL);

/** SrvFileMgrIsURLAllowOperation(Sync)
@brief Path relate operation

@param[in]       pStrURL            url
@param[in]       eOperation         operation type

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryURLStatus(FileMgr_WChar *pStrURL, FileMgrOperation_e *pOperation);

/** SrvFileMgrIsURLAllowOperation(Sync)
@brief  query url status

@param[in]       pStrURL            url
@param[in]       eOperation         operation type

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrIsURLAllowOperation(const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);

/** SrvFileMgrLockURLStatus(Sync)
@brief  lock url, then got handle. it must be call SrvFileMgrUnLockURLStatus after used.

@param[out]      pHandle            lock url handleID
@param[in]       pStrURL            file url
@param[in]       eOperation         lock url type

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrLockURLStatus(FileMgrHandleID_t *pHandle, const FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation);

/** SrvFileMgrUnLockURLStatus(Sync)
@brief  unlock url

@param[in]      pHandle             lock url handleID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrUnLockURLStatus(FileMgrHandleID_t nHandle);

/** SrvFileMgrMonitorURL(Sync)
@brief  monitor url, then got handle. it must be call SrvFileMgrDeMonitorURL after used.

@param[out]      pHandle            Monitor handleID
@param[in]       pStrURL            Monitor url
@param[in]       nMode_e            Monitor type
@param[in]       pCbData            call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrMonitorURL(FileMgrHandleID_t *pHandle, FileMgr_WChar *pStrURL, FileMgrOperation_e nMode_e, FileMgrCbData_t *pCbData);

/** SrvFileMgrDeMonitorURL(Sync)
@brief  de-monitor url

@param[in]      nHandle             Monitor handleID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrDeMonitorURL(FileMgrHandleID_t nHandle);

/** SrvFileMgrQueryBatchCommandStatus(Sync)
@brief  query status of executing batch command

@param[out]      pBatchCmdType      current running batch command

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryBatchCommandStatus(ExecuteBatchCmdType_t *pBatchCmdType);

/** SrvFileMgrQuerySuspend(Sync)
@brief  query status of FileMgr.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQuerySuspend(void);

/** SrvFileMgrSetSuspend(Async)
@brief  suspend filemgr.

@param[out]    pHandleID            suspend handle
@param[in]     bIsSuspend           set suspend
@param[in]      pCbData             call back function

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrSetSuspend(FileMgrHandleID_t *pHandleID, u8 bIsSuspend, FileMgrCbData_t *pCbData);

/** SrvFileMgrFormat(Sync)
@brief  format by volume ID

@param[in]      nVolumeID           need to format volume ID; ref by vfs_sttuct.h

VFS_VOL_NOR
VFS_VOL_SD
VFS_VOL_NAND
VFS_VOL_SD2

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrFormat(u32 nVolumeID);

/** SrvFileMgrAsyncFormat(Async)
@brief  async format by volume ID

@param[out]     pHandleID           handle ID for format
@param[in]      nVolumeID           need to format volume ID; ref by vfs_sttuct.h
@param[in]      pCbData             call back function

VFS_VOL_NOR
VFS_VOL_SD
VFS_VOL_NAND
VFS_VOL_SD2

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrAsyncFormat(FileMgrHandleID_t *pHandleID, u32 nVolumeID, FileMgrCbData_t *pCbData);

/** SrvFileMgrAsyncCheckDisk(Async)
@brief  async check disk by volume ID

@param[out]     pHandleID           handle ID for format
@param[in]      nVolumeID           need to format volume ID; ref by vfs_sttuct.h
@param[in]      nChkdskOperation    call back function
@param[in]      pCbData             call back function

nVolumeID:
VFS_VOL_NOR
VFS_VOL_SD
VFS_VOL_NAND
VFS_VOL_SD2

nChkdskOperation:
VFS_CHKDSK_STOP_FS_NORMAL //Used when power-up after normal power-off, or disable mass storage
VFS_CHKDSK_QUICK_CHECK    //Used when power-up after abnormal power-off, or insert one SD card
VFS_CHKDSK_RECOVERY

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrAsyncCheckDisk(FileMgrHandleID_t *pHandleID, u32 nVolumeID, u32 nChkdskOperation, FileMgrCbData_t *pCbData);

/** SrvFileMgrPauseAsyncCheckDisk(Sync)
@brief pause check disk command

@param[in]       nHandleID          batch command handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrPauseAsyncCheckDisk(FileMgrHandleID_t nHandleID);

/** SrvFileMgrResumeAsyncCheckDisk(Sync)
@brief resume check disk command

@param[in]       nHandleID          batch command handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrResumeAsyncCheckDisk(FileMgrHandleID_t nHandleID);

/** SrvFileMgrPauseAsyncFormat(Sync)
@brief resume format command

@param[in]       nHandleID          batch command handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrPauseAsyncFormat(FileMgrHandleID_t nHandleID);


/** SrvFileMgrResumeAsyncFormat(Sync)
@brief resume format command

@param[in]       nHandleID          batch command handle ID

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrResumeAsyncFormat(FileMgrHandleID_t nHandleID);

/** SrvFileMgrQueryMountedVolToDev(Sync)
@brief  query device ID by volume ID after auto mount

@param[in]      nVolumeID           query by volume ID; ref by vfs_sttuct.h
@param[out]     pDeviceID           Result of device ID; ref by vfs_sttuct.h

VFS_VOL_NOR
VFS_VOL_SD
VFS_VOL_NAND
VFS_VOL_SD2

Example:
VFS_VOL_NOR  -> VFS_DEV_NOR
VFS_VOL_SD   -> VFS_DEV_SD or VFS_DEV_SD_2
VFS_VOL_NAND -> VFS_DEV_NAND
VFS_VOL_SD2  -> VFS_DEV_SD or VFS_DEV_SD_2

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryMountedVolToDev(u8 nVolumeID, u8 *pDeviceID);

/** SrvFileMgrQueryMountedDevToVol(Sync)
@brief  query volume ID by device ID after auto mount

@param[in]      nDeviceID           query by device ID; ref by vfs_sttuct.h
@param[out]     pVolumeID           Result of volume ID; ref by vfs_sttuct.h

VFS_DEV_NOR
VFS_DEV_SD
VFS_DEV_NAND
VFS_DEV_SD2

Example:
VFS_DEV_NOR  -> VFS_VOL_NOR
VFS_DEV_SD   -> VFS_VOL_SD or VFS_VOL_SD2
VFS_VOL_NAND -> VFS_VOL_NAND
VFS_DEV_SD_2 -> VFS_VOL_SD or VFS_VOL_SD2

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvFileMgrQueryMountedDevToVol(u8 nDeviceID, u8 *pVolumeID);

/** SrvFileMgrIsMounted(Sync)
@brief  mount SD

@param[in]      nVolumeID           mount by volume ID; ref by vfs_sttuct.h

VFS_VOL_NOR
VFS_VOL_SD
VFS_VOL_NAND
VFS_VOL_SD2

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen.
@retval MAE_RET_BAD_PARAM           If input parameter error.
@retval MAE_RET_NOT_MOUNTED_ERROR   If not mounted.

*/
MAE_Ret SrvFileMgrIsMounted(u8 nVolumeID);

/** SrvFileMgrQueryFsDiskState
@brief  Query disk state by input volume type

@param[in]       nVolumeID        VFS_VOL_TYPE
@param[out]     pDiskState         Disk state

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_FAILED              If an error happen. Failed.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/

MAE_Ret SrvFileMgrQueryFsDiskState(u32 nVolumeID,u8 * pDiskState);


//========================================================

/*-----------------------------------------------------*/
#endif //__MMI_SRV_FILEMGR_H__
