#include "sys_traces.ho"
#include "filemgr.h"

#define DBEG _TRACE
#define DEMSG _CUS10 | LEVEL_2

#define dir_url L"fs:/CARD/abc"
#define file_url L"fs:/CARD/abc.txt"

void fileMgr_test_Disk_Operation();
void fileMgr_test_Single_File_Operation();
void fileMgr_test_Rename();
void fileMgr_test_SyncDelete();
void fileMgr_test_AsyncDelete();
void fileMgr_test_MarkList();
void fileMgr_test_MarkList1();
void fileMgr_test_ASYNC_SORT_LIST();
void fileMgr_test_SYNC_SORT_LIST();
void fileMgr_test_ASYNC_SEARCH();
void fileMgr_test_Mount();
void fileMgr_test_ASYNC_Move();
void fileMgr_test_MkDir();
void fileMgr_test_RmDir();
void fileMgr_test_RemoveAll();
void fileMgr_test_ASYNC_Copy();
void fileMgr_test_ASYNC_MarkList_Delete();
void fileMgr_test_ASYNC_MarkList_Copy();
void fileMgr_test_ASYNC_MarkList_Move();
void fileMgr_test_Un_Mount();
void fileMgr_test_FileMgrGetInstance();
void fileMgr_test_FileMgrVolumeInit();
void fileMgr_test_ASYNC_DELETE_FILES();
void fileMgr_test_ASYNC_COPY_FILES();
void fileMgr_test_ASYNC_MOVE_FILES();
void fileMgr_test_MarkList_IDToFileName();

enum{
	API_FileMgrNotifyFileOpened_Normal,
#ifdef	FILEMGR_DEBUG
#ifdef	__SDK_SIMULATION__
	API_FileMgrNotifyFileOpened_Dbg,
#endif
#endif
//	API_FileMgrNotifyCloseFile,
	API_FileMgrNotifyFolderChanged,
//Disk	Operation(Sync)
	API_FileMgrCheckFreeSpace,
	API_FileMgrExist,
	API_FileMgrGetInfo,
	API_FileMgrSetFileAttr,
	API_FileMgrGetRenameLength,
//Single	File	Operation(Sync)
	API_FileMgrOpenFile,
	API_FileMgrCloseFile,
//Rename(Sync)
	API_FileMgrRename,
//Delete(Sync)
	API_FileMgrSyncDelete,
//Delete(ASync)
	API_FileMgrDelete,
//Move(ASync)
	API_FileMgrMove,
//Copy(ASync)
	API_FileMgrCopy,
//For	multi-file	delete
//Delete(Multi-files)(Sync)
//	API_FileMgrSyncDeleteFiles,
//Delete(Multi-files)(ASync)
	API_FileMgrDeleteFiles,
//Move(Multi-files)(Sync)
//	API_FileMgrSyncMoveFiles,
//Move(Multi-files)(ASync)
	API_FileMgrMoveFiles,
//Copy(Multi-files)(Sync)
//	API_FileMgrSyncCopyFiles,
//Copy(Multi-files)(ASync)
	API_FileMgrCopyFiles,
//DeleteAll(Multi-files)(ASync)
	API_FileMgrDeleteAllFiles,
//For	mark
//Delete	for	mark(Sync)
//	API_FileMgrSyncDeleteMarkedFiles,
//Delete	for	mark(ASync)
	API_FileMgrDeleteMarkedFiles,
//Move	for	mark(Sync)
//	API_FileMgrSyncMoveMarkedFiles,
//Move	for	mark(ASync)
	API_FileMgrMoveMarkedFiles,
//Copy	for	mark(Sync)
//	API_FileMgrSyncCopyMarkedFiles,
//Copy	for	mark(ASync)
	API_FileMgrCopyMarkedFiles,
//Abort	Batch	command(Sync)
	API_FileMgrBatchCommandAbort,
/////////////////////////////////////////////////////////////////////////////
//Folder	Operation
//Folder-mkdir(Sync)
	API_FileMgrMkDir,
//Folder-rmdir(Sync)
	API_FileMgrRmDir,
//Folder-rename(Sync)
//use	API_FileMgrRename
/////////////////////////////////////////////////////////////////////////////
//List	API
//GetFolderFile+List+Soritng(ASync)
	API_FileMgrOpenFolderHandle,
	API_FileMgrGetFolderFileNumber,
	API_FileMgrSetSortingMethod,
	API_FileMgrListFolder,
	API_FileMgrCloseFolderHandle,
//GetFolderFile+List+Soritng(Sync)
	API_FileMgrSyncOpenFolderHandle,
	API_FileMgrSyncGetFolderFileNumber,
	API_FileMgrSyncSetSortingMethod,
	API_FileMgrSyncListFolder,
	API_FileMgrSyncCloseFolderHandle,
/////////////////////////////////////////////////////////////////////////////
//Mark(Sync)
	API_FileMgrCreateMarkList,
	API_FileMgrUpdateMarkList,
	API_FileMgrUpdateMarkListWithoutSubfolder,
	API_FileMgrQueryMarkListNumberID,
	API_FileMgrQueryMarkListID,
	API_FileMgrQueryIsMarkedMarkListID,
	API_FileMgrDestoryMarkList,
//ID	to	FileInfo(Sync)
	API_FileMgrIDToFileName,
//FileID+Path	To	URL	(single)(Sync)
	API_FileMgrTransferFileIDToURL,
/////////////////////////////////////////////////////////////////////////////
//Search(with	partial	list,	filter,	search)(Async)
	API_FileMgrCreateSearchMarkList,
	API_FileMgrListSearchedFolder,
	API_FileMgrListSearchedFolderGetURL,
	API_FileMgrGetSearchedFileNumber,
	API_FileMgrDestorySearchMarkList,
//Search(with	partial	list,	filter,	search)(Sync)
//	API_FileMgrSyncCreateSearchMarkList,
//	API_FileMgrSyncListSearchedFolder,
//	API_FileMgrSyncListSearchedFolderGetURL,
//	API_FileMgrSyncGetSearchedFileNumber,
//	API_FileMgrSyncDestorySearchMarkList,
//Mount
	API_FileMgrSDMount,
	API_FileMgrSDUnMount,

//GetGlobalData
	API_FileMgrGetInstance,
//InitVolume
	API_FileMgrVolumeInit,
};
