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
* @file    srv_filemgr_priv.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_PRIV_H__
#define __SRV_FILEMGR_PRIV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_msgof.hc"
#include "sys_rtk_vmoshi.h"
#include "sys_vm_dbg.ho"
#include "mdl_vfs_fat.ho"
#include "cus_os.hc"
#include "srv_filemgr.h"
#include "srv_filemgr_register_path.h"
#include "srv_filemgr_mark.h"
#include "srv_filemgr_list.h"
#include "srv_filemgr_fstream.h"
#include "srv_queue.h"
#include "srv_hashtable.h"
#include "srv_hashtable_util.h"
#include "mmi_mae_log.h"
#include "mmi_mae_helper.h"

#if defined(__PC_SIMULATOR__)
#include <assert.h> ///< included for assert on simulator
#endif

#if !defined(FILE_MGR_STANDALONE_DEBUG)
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "util_ucs2.hi"
#include "mmi_util_rtc.h"
#endif

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

//Options
#define FILEMGR_MAX_OPENED_FILES            15 // Currently it is 15
#define FILEMGR_DEBUG

#define FILEMGR_FIRST_LIST_CACHE_NUMBR                  (301)
#define FILEMGR_DEFAULT_LISTENER_NUMBER			    	(20)
#define FILEMGR_DEFAULT_REGISTER_PATH_HASHTABLE_SIZE	(20)
#define FILEMGR_DEFAULT_FOLDER_CACHE_HASHTABLE_SIZE		(20)
#define FILEMGR_DEFAULT_COMMAND_QUEUE_SIZE				(10)
#define FILEMGR_DEFAULT_LIST_QUEUE_SIZE					(10)
#define FILEMGR_DEFAULT_MARK_QUEUE_SIZE					(10)

#define FILEMGR_STEP_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                  (100)
#define FILEMGR_MIN_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                   (300)
#define FILEMGR_MAX_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                   (500)
#define FILEMGR_COMMAND_FINISH                          (100)
#define FILEMGR_SUSPEND_TIME_OUT_TIME					(10000)
#define FILEMGR_COMMON_FNCOL_SN_MAX                     (100) // append a serial # as suffix while filename collision occurring
#define FILEMGR_SLEEP_INTERRUPT_TIME                    (250) //Tick
#define FILEMGR_CHECK_INTERRUPT_INTERVAL                (1)
#define FILEMGR_COMMON_FNCOL_SN_FORMAT   L"(%d)"
#define FILEMGR_COMMON_FNCOL_SN_LEN      2   // for '(' and ')'

#define FILE_MGR_SEM__MAILBOX_REENTRY       FILEMGR_SEM_MARK_FOLDER
//#define FILE_MGR_SEM__MARK_FOLDER         FILEMGR_SEM_MARK_FOLDER // disable mark folder, then semaphore use by FILE_MGR_SEM__MAILBOX_REENTRY
#define FILE_MGR_SEM__MMI_WAIT_LIST         FILEMGR_SEM_DELETE_ALL

#if defined(FILE_MGR_STANDALONE_DEBUG)
#undef MALLOC
#undef FREE
#undef FREEIF

#undef SWPRINTF
#define SWPRINTF        swprintf
#define STRLEN          strlen

#define MALLOC(size)    malloc(size)
#define MEMSET(a,v,n)   memset(a,v,n)
#define MEMCPY          memcpy
#define MEMCMP          memcmp
#define MEMMOVE         memmove
#define FREE(p)         free(p)
#define FREEIF(p)       if(p != 0) {free((void*)p); p = 0;}
#define ASSERT          assert

#define MsGetHeapMemoryLr(x,y) malloc(x)
#define MsReleaseHeapMemory(p) FREEIF(p)

#else

#undef MALLOC
#undef FREE
#undef FREEIF
#define MALLOC(size)    MsAllocateMem(size)
#define FREE(p)         MsReleaseMemory(p)
#define FREEIF(p)       if(p != 0) {MsReleaseMemory(p); p = 0;}

#undef ASSERT
extern boolean g_bIgnoreAPBreakAssert;

#ifdef __PC_SIMULATOR__
#define ASSERT(x)  {assert(x);}
#else
#define ASSERT(x)       {if(!(x)){\
                        extern void ker_assert_func(u8 *str, u8 *file, u32 line);\
                        ker_assert_func(#x, __FILE__, __LINE__);}}
#endif

#endif

#define BREAK_IF(a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
        {\
            break;\
        }\
    }

#define FILE_MGR_IS_SUSPEND_BREAK\
    {\
        if(MAE_RET_FILE_SYSTEM_RUNNING != _QuerySystemSuspend())\
        {\
            nRet = MAE_RET_FILE_SYSTEM_SPSPEND;\
            break;\
        }\
    }

#define FILE_MGR_IS_SUSPEND\
    {\
    if(MAE_RET_FILE_SYSTEM_RUNNING != _QuerySystemSuspend())\
        {\
           return MAE_RET_FILE_SYSTEM_SPSPEND;\
        }\
    }

#define FILE_MGR_IS_SUSPEND_NO_RETURN\
    {\
    if(MAE_RET_FILE_SYSTEM_RUNNING != _QuerySystemSuspend())\
        {\
           return ;\
        }\
    }

#ifdef GETDIGITS
#undef GETDIGITS
#endif
#define GETDIGITS(n, digit) {   u32 nNum = n; digit = 0;   \
	do{   \
	nNum /= 10; digit++;    \
	}while(0 != nNum);    \
}


#define ENABLE_ASYNC_DELETE_ALL
#define SORTING_WITHOUT_USING_MARK
//#define ENABLE_FILEMGR_MARK_FOLDER
//#define ENABLE_MMI_WAIT_LIST_FOR_SORT
#define ENABLE_FILEMGR_DEBUG
#define ENABLE_SYNC_DELETE_WITHOUT_QUEUE

//Maximum length of file name. It is a physical limitation in current file system
#define MAX_FILE_NAME   255

#define FILEMGR_NOTIFY_ERROR 0xff

#if !defined(FILE_MGR_STANDALONE_DEBUG)

#ifdef ENABLE_FILEMGR_DEBUG
#define FMGR_TRACE       vm_dbgTrace
#define FMGR_ERROR       vm_dbgError
#define FMGR_WARN        vm_dbgTrace
#else //ENABLE_FILEMGR_DEBUG
#define FMGR_TRACE
#define FMGR_ERROR       vm_dbgError
#define FMGR_WARN
#endif //ENABLE_FILEMGR_DEBUG

#else
#define FMGR_TRACE       Win32_Trace
#define FMGR_ERROR       Win32_Trace
#define FMGR_WARN        Win32_Trace
#endif

#define FILE_MGR_SEM__DELETE_REENTRY        FILEMGR_SEM_1
#define FILE_MGR_SEM__DELETE                FILEMGR_SEM_2

#define FILE_MGR_SEM__LIST_REENTRY          FILEMGR_SEM_3
#define FILE_MGR_SEM__LIST                  FILEMGR_SEM_4

#define FILE_MGR_SEM__MAILBOX               FILEMGR_SEM_5

#define FILE_MGR_SEM__MOVE_EX_REENTRY        FILEMGR_SEM_6
#define FILE_MGR_SEM__MOVE_EX                FILEMGR_SEM_7

#define ErrorCase(nOldErrorCode, nNewErrorCode) case (nOldErrorCode): return (nNewErrorCode);

/*=============================================================*/
// Type Declarations
/*=============================================================*/
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "srv_filemgr_message_define__.hi"
} FileMgrMsg_e;

typedef struct
{
    u16 senderID;
    u32 userValue;
    VFS_NotifyInfo_t *pEfsInfo;
} FileMgr_UpdateFolder_Cnf_t;

typedef struct
{
    u32 userValue;
    VFS_NotifyInfo_t *pEfsInfo;
} FileMgr_SearchFolder_Cnf_t;

typedef struct
{
    u32 userValue;
    VFS_NotifyInfo_t *pEfsInfo;
} FileMgr_SortFolder_Cnf_t;

typedef struct
{
    VFS_PartialListFilter_t *pListFilter;
    FileMgrHandleID_t *pHandleID;
    FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgr_OpenFolder_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 *pFileNumber;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_Get_Folder_Number_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgrSortComp_Fxp pCompareFunc;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_Set_Sorting_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 nStartIndex;
    u32 nFileListSize;
    FileMgr_ListData_t *pListData;
    MAE_Ret *pRet;
} FileMgr_List_Folder_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    MAE_Ret *pRet;
} FileMgr_CloseFolder_Req_t;

typedef struct
{
    VFS_PartialListFilter_t *pListFilter;
    FileMgrHandleID_t *pHandleID;
    FileMgr_WChar *pStrURL;
    u32 *pFileNumber;
    FileMgrFindComp_Fxp pSearchFunc;
    FileMgrCbData_t *pCbData;
    u8 nTraversalLevel;
    MAE_Ret *pRet;
} FileMgr_Create_Search_Mark_list_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 nStartIndex;
    u32 nFileListSize;
    FileMgr_ListData_t *pListData;
    MAE_Ret *pRet;
} FileMgr_List_Searched_Folder_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 nStartIndex;
    u32 nListSize;
    FileMgrSearchURL_t *pListURL;
    MAE_Ret *pRet;
} FileMgr_List_Searched_Folder_GetURL_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 *pFileNumber;
    MAE_Ret *pRet;
} FileMgr_Get_Searched_File_Number_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    MAE_Ret *pRet;
} FileMgr_Destory_Search_MarkList_Req_t;

typedef struct
{
    FileMgr_WChar *pSrcURL;
    FileMgrHandleID_t *pHandleID;
    u32 nUpperBound;
    MAE_Ret *pRet;
} FileMgr_Create_Mark_List_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgrMarkListChange_t *pMarkListChangeIDData;
    MAE_Ret *pRet;
} FileMgr_Update_Mark_List_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgrMarkListChange_t *pMarkListChangeIDData;
    MAE_Ret *pRet;
} FileMgr_Update_Mark_List_Without_Subfolder_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 *pFileNumber;
    MAE_Ret *pRet;
} FileMgr_Query_Mark_List_NumberID_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    u32 nStartIndex;
    FileMgrMarkListID_t *pMarkListIDData;
    MAE_Ret *pRet;
} FileMgr_Query_Mark_ListID_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    VFS_FileID_t nFileID;
    MAE_Ret *pRet;
} FileMgr_Query_Is_Marked_Mark_ListID_Req_t;

typedef struct
{
    FileMgrHandleID_t nMarkHandleID;
    FileMgrHandleID_t nFolderHandleID;
    MAE_Ret *pRet;
} FileMgr_Mark_All_Req_t;

typedef struct
{
    FileMgrHandleID_t nMarkHandleID;
    FileMgrHandleID_t nFolderHandleID;
    FileMgrMarkComp_Fxp pCompFunc;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
}FileMgr_Mark_All_Ex_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgr_UnMark_All_By_URL_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    FileMgr_WChar *pStrURL;
    u32 *pMarkNumber;
    MAE_Ret *pRet;
} FileMgr_Query_File_Number_By_URL_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    MAE_Ret *pRet;
} FileMgr_Destory_Mark_List_Req_t;

typedef struct
{
    FileMgr_WChar *pDestURL;
    FileMgrHandleID_t *pHandleID;
    u32 nMarkHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_CopyMarkedFiles_Req_t;

typedef struct
{
    FileMgr_FileList_t *pFileListCommand;
    FileMgrHandleID_t *pHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_CopyFiles_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    const FileMgr_WChar *pStrSrcURL;
    const FileMgr_WChar *pStrDestURL;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_CopySingleFile_Req_t;

typedef struct
{
    FileMgr_WChar *pDestURL;
    FileMgrHandleID_t *pHandleID;
    u32 nMarkHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_MoveMarkedFiles_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    const FileMgr_WChar *pStrSrcURL;
    const FileMgr_WChar *pStrDestURL;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_MoveSingeFile_Req_t;

typedef struct
{
    FileMgr_FileList_t *pFileListCommand;
    FileMgrHandleID_t *pHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_MoveFiles_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    u32 nMarkHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_DeleteMarkedFiles_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    const FileMgr_WChar *pStrSrcURL;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_DeleteSingleFile_Req_t;

typedef struct
{
    FileMgr_FileList_t *pFileListCommand;
    FileMgrHandleID_t *pHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_DeleteFiles_Req_t;

typedef struct
{
    VFS_PartialListFilter_t *pListFilter;
    FileMgr_WChar *pSrcURL;
    FileMgrHandleID_t *pHandleID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_DeleteAllFiles_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    MAE_Ret *pRet;
} FileMgr_BatchCommandAbort_Req_t;

typedef struct
{
    void *pFileStream;
    FileMgr_WChar *pStrURL;
    void *pOwner;
    u8 nMode;
    u8 nVol;
} FileMgr_UpdateFileOpened_Req_t;

typedef struct
{
    void *pFileStream;
} FileMgr_UpdateFileClosed_Req_t;

typedef struct
{
    s32 retCode;
    void *userData;
    VFS_NotifyInfo_t *pNotifyInfo;
} mmi_FileMgrMsgBody_t;

typedef struct
{
    u32 nHandleID;
    VFS_NotifyInfo_t tNotifyInfo;
} FileMgrSearchInd_t;

typedef struct
{
    FileMgr_WChar *pStrPath;
    FileMgrOperation_e *pOperation;
    MAE_Ret *pRet;
    u8 nVolumeID;
} FileMgrQueryPathStatus_t;

typedef struct
{
    FileMgr_WChar *pStrPath;
    FileMgrOperation_e eOperation;
    MAE_Ret *pRet;
    u8 nVolumeID;
} FileMgrIsPathAllowOperation_t;

typedef struct
{
    FileMgrHandleID_t *pHandle;
    FileMgr_WChar *pStrPath;
    FileMgrOperation_e eOperation;
    MAE_Ret *pRet;
    u8 nVolumeID;
} FileMgrLockPathStatus_t;

typedef struct
{
    FileMgrHandleID_t nHandle;
    MAE_Ret *pRet;
} FileMgrUnLockPathStatus_t;

typedef struct
{
    FileMgrHandleID_t *pHandle;
    FileMgr_WChar *pStrPath;
    FileMgrOperation_e nMode_e;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
    u8 nVolumeID;
} FileMgrMonitorPath_t;

typedef struct
{
    FileMgrHandleID_t nHandle;
    MAE_Ret *pRet;
} FileMgrDeMonitorPath_t;

typedef struct
{
    FileMgr_WChar *pStrPath;
    FileMgrOperation_e Operation_e;
    MAE_Ret *pRet;
} FileMgrNotifyPathStatus_t;

typedef struct
{
    char *pSbjName;
    u32 nSbjStatus;
    void *pUser;
} FileMgrSendDestoryAllCommand_t;

typedef struct
{
    void **ppStreamResult;
    const FileMgr_WChar *pStrURL;
    const u8 *pMode;
    void *pOwner;
    MAE_Ret *pRet;
} FileMgr_OpenFile_Req_t;

typedef struct
{
    void *pStream;
    MAE_Ret *pRet;
} FileMgr_CloseFile_Req_t;

typedef struct
{
    const FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgr_QueryFileStatus_Req_t;

typedef struct
{
    void *pStream;
    void *pBuffer;
    u32 nWordCnt;
    u32 *pByteRead;
    FileMgrCallback_Fxp pfnCallBackFuncPtr;
    MAE_Ret *pRet;
} FileMgr_FileRead_Req_t;

typedef struct
{
    void *pStream;
    const void *pBuffer;
    u32 nCount;
    FileMgrCallback_Fxp pfnCallBackFuncPtr;
    FileMgrFileCallback_t *pCallBackData;
    MAE_Ret *pRet;
} FileMgr_FileWrite_Req_t;

typedef struct
{
    u16 senderID;
    u32 userValue;
    VFS_NotifyInfo_t *pEfsInfo;
} FileMgr_FileRead_Cnf_t;

typedef struct
{
    u16 senderID;
    u32 userValue;
    VFS_NotifyInfo_t *pEfsInfo;
} FileMgr_FileWrite_Cnf_t;

typedef struct
{
    void *pStream;
    PfnFileMgr_StreamCallback pfnStreamCB;
    void *pUser;
} FileMgr_FileStreamSetCallBack_Cnf_t;

typedef struct
{
    void *pStream;
} FileMgr_FileStreamCancelCallBack_Cnf_t;

typedef struct
{
    void *pStream;
    MAE_Ret *pRet;
} FileMgr_FileStreamCheckSize_Cnf_t;

typedef struct
{
    void *pStream;
    s32 nOffset;
    FileMgrSeekType_e eSeekType;
    MAE_Ret *pRet;
} FileMgr_FileStreamSeek_Cnf_t;

typedef struct
{
    void *pStream;
    s32 *pErr;
} FileMgr_FileStreamGetCurrentPos_Cnf_t;

typedef struct
{
    void *pStream;
    MAE_Ret *pRet;
} FileMgr_FileStreamEOF_Cnf_t;

typedef struct
{
    FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgrMkDir_t;

typedef struct
{
    FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgrRmDir_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    FileMgr_WChar *pSrcURL;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgrAsyncRmDir_t;

typedef struct
{
    u32 nVolumeID;
    MAE_Ret *pRet;
} FileMgr_QueryVolumeStatus_Req_t;

typedef struct
{
    const FileMgr_WChar *pSrcURL;
    const FileMgr_WChar *pStrDestName;
    MAE_Ret *pRet;
} FileMgr_Rename_Req_t;

typedef struct
{
    u32 nVolumeID;
    MAE_Ret *pRet;
} FileMgr_Format_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    u8 bIsSuspend;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_Suspend_Req_t;

typedef struct
{
    MAE_Ret *pRet;
} FileMgr_QuerySuspend_Req_t;

typedef struct
{
    ExecuteBatchCmdType_t *pBatchCmdType;
    MAE_Ret *pRet;
} FileMgr_QueryBatchCommandStatus_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    u32 nVolumeID;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_AsyncFormat_Req_t;

typedef struct
{
    FileMgrHandleID_t *pHandleID;
    u32 nVolumeID;
    u32 nChkdskOperation;
    FileMgrCbData_t *pCbData;
    MAE_Ret *pRet;
} FileMgr_Chkdsk_Req_t;

typedef struct
{
    const FileMgr_WChar *pStrURL;
    u32 *pTotalSize;
    u32 *pRemainSize;
    MAE_Ret *pRet;
} FileMgr_CheckFreeSpace_Req_t;

typedef struct
{
    const FileMgr_WChar *pStrURL;
    MAE_Ret *pRet;
} FileMgr_Exist_Req_t;

typedef struct
{
    const FileMgr_WChar *pStrURL;
    VFS_PartialListFileInfo_t *pFileInfo;
    MAE_Ret *pRet;
} FileMgr_GetInfo_Req_t;

typedef struct
{
    VFS_VOL_TYPE eVolType;
    VFS_DiskStatus_e *pDiskState;
    MAE_Ret *pRet;
} FileMgr_QueryFsDiskState_Req_t;

typedef struct
{
    const FileMgr_WChar *pStrURL;
    u32 nFileAttr;
    MAE_Ret *pRet;
} FileMgr_SetFileAttr_Req_t;

typedef struct
{
    void **ppStreamResult;
    const FileMgr_WChar *pStrURL;
    const u8 *pMode;
    void *pOwner;
    MAE_Ret *pRet;
} FileMgr_NotifyOpenFile_Req_t;

typedef struct
{
    void *pStream;
    MAE_Ret *pRet;
} FileMgr_NotifyCloseFile_Req_t;

typedef struct
{
	u8 bIsBackLightOff;
	MAE_Ret *pRet;
} FileMgr_Backlight_Req_t;

typedef struct
{
    FileMgrHandleID_t nHandleID;
    MAE_Ret *pRet;
} FileMgr_PauseResume_Req_t;

typedef union
{
    FileMgr_UpdateFolder_Cnf_t UpdateListFolderCnf;
    FileMgr_SearchFolder_Cnf_t SearchListFolderCnf;
    FileMgr_SortFolder_Cnf_t SortListFolderCnf;

    FileMgr_OpenFolder_Req_t OpenFolderReq;
    FileMgr_Get_Folder_Number_Req_t GetFolderNumber;
    FileMgr_Set_Sorting_Req_t SetSortingReq;
    FileMgr_List_Folder_Req_t ListFolderReq;
    FileMgr_CloseFolder_Req_t CloseFolderReq;

    FileMgr_Create_Search_Mark_list_Req_t CreateSearchMarklistReq;
    FileMgr_List_Searched_Folder_Req_t ListSearchedFolderReq;
    FileMgr_List_Searched_Folder_GetURL_Req_t ListSearchedFolderGetURLReq;
    FileMgr_Get_Searched_File_Number_Req_t GetSearchedFileNumberReq;
    FileMgr_Destory_Search_MarkList_Req_t DestorySearchMarkListReq;

    FileMgr_Create_Mark_List_Req_t CreateMarkListReq;
    FileMgr_Update_Mark_List_Req_t UpdateMarkListReq;
    FileMgr_Update_Mark_List_Without_Subfolder_Req_t UpdateMarkListWithoutSubfolderReq;
    FileMgr_Query_Mark_List_NumberID_Req_t QueryMarkListNumberIDReq;
    FileMgr_Query_Mark_ListID_Req_t QueryMarkListIDReq;
    FileMgr_Query_Is_Marked_Mark_ListID_Req_t QueyrIsMarkedMarkListIDReq;
    FileMgr_Mark_All_Req_t MarkAllByHandle;
    FileMgr_Mark_All_Ex_Req_t MarkAllExByHandle;
    FileMgr_UnMark_All_By_URL_Req_t UnMarkAllByURL;
    FileMgr_Query_File_Number_By_URL_Req_t QueryFileNumberByURL;

    FileMgr_Destory_Mark_List_Req_t DestoryMarkListReq;

    FileMgr_CopyMarkedFiles_Req_t CopyMarkedFiles;
    FileMgr_CopyFiles_Req_t CopyFiles;
    FileMgr_CopySingleFile_Req_t CopySingeFile;

    FileMgr_MoveMarkedFiles_Req_t MoveMarkedFiles;
    FileMgr_MoveFiles_Req_t MoveFiles;
    FileMgr_MoveSingeFile_Req_t MoveSingleFile;

    FileMgr_DeleteMarkedFiles_Req_t DeleteMarkedFiles;
    FileMgr_DeleteFiles_Req_t DeleteFiles;
    FileMgr_DeleteSingleFile_Req_t DeleteSingleFile;

    FileMgr_DeleteAllFiles_Req_t DeleteAllFiles;
    FileMgr_BatchCommandAbort_Req_t BatchCommandAbort;

    VFS_NotifyInfo_t CopyCnf;
    VFS_NotifyInfo_t MoveCnf;
    VFS_NotifyInfo_t DeleteCnf;
    FileMgrSearchInd_t SearchCnf;
    VFS_NotifyInfo_t DeleteAllCnf;
    VFS_NotifyInfo_t SuspendCnf;
    VFS_NotifyInfo_t FormatCnf;
    VFS_NotifyInfo_t ChkdskCnf;

    FileMgr_UpdateFileOpened_Req_t FileOpenedInd;
    FileMgr_UpdateFileClosed_Req_t FileClosedInd;

    FileMgrQueryPathStatus_t QueryPathStatus;
    FileMgrIsPathAllowOperation_t IsPathAllowOperation;

    FileMgrLockPathStatus_t LockPathStatus;
    FileMgrUnLockPathStatus_t UnLockPathStatus;

    FileMgrMonitorPath_t MonitorPath;
    FileMgrDeMonitorPath_t DeMonitorPath;

    FileMgrNotifyPathStatus_t NotifyPathStatus;

    FileMgrSendDestoryAllCommand_t DestoryAllCommand;

    FileMgr_OpenFile_Req_t OpenFileReq;
    FileMgr_CloseFile_Req_t CloseFileReq;
    FileMgr_QueryFileStatus_Req_t QueeryFileStatus;

    FileMgr_FileRead_Req_t ReadReq;
    FileMgr_FileWrite_Req_t WriteReq;
    FileMgr_FileRead_Cnf_t ReadCnf;
    FileMgr_FileWrite_Cnf_t WriteCnf;

    FileMgr_FileStreamSetCallBack_Cnf_t SetCallBack;
    FileMgr_FileStreamCancelCallBack_Cnf_t CancelCallBack;
    FileMgr_FileStreamCheckSize_Cnf_t CheckSize;
    FileMgr_FileStreamSeek_Cnf_t StreamSeek;
    FileMgr_FileStreamGetCurrentPos_Cnf_t StreamGetCurrentPos;
    FileMgr_FileStreamEOF_Cnf_t StreamEOF;

    FileMgrMkDir_t MkDir;
    FileMgrRmDir_t RmDir;
    FileMgrAsyncRmDir_t AsyncRmDir;

    FileMgr_QueryVolumeStatus_Req_t QueryVolumeStatus;
    FileMgr_QueryFsDiskState_Req_t QueryFsDiskState;

    FileMgr_Format_Req_t Format;
    FileMgr_AsyncFormat_Req_t AsyncFormat;
    FileMgr_Chkdsk_Req_t Chkdsk;
    FileMgr_PauseResume_Req_t PauseResume;

    FileMgr_Rename_Req_t Rename;

    FileMgr_Suspend_Req_t Suspend;
    FileMgr_QuerySuspend_Req_t QuerySuspend;
    FileMgr_QueryBatchCommandStatus_Req_t CommandStatus;

    FileMgr_CheckFreeSpace_Req_t CheckFreeSpace;
    FileMgr_Exist_Req_t Exit;
    FileMgr_GetInfo_Req_t GetInfo;
    FileMgr_SetFileAttr_Req_t SetFileAttr;

	FileMgr_Backlight_Req_t BackLightOff;

    vm_osTimerMsgBody_t FileMgrTimerMsg;

    FileMgr_NotifyOpenFile_Req_t NotifyOpenFile;
    FileMgr_NotifyCloseFile_Req_t NotifyCloseFile;

    mmi_FileMgrMsgBody_t fileMgrRsp;
} vm_msgBody_t;

typedef struct
{
    FileMgr_WChar *pOpenFileURL;
    void *pOpenFile;
    void *pOpenFileOwner;
    FileMgrHandleID_t nHandleID;
    FileMgrOperation_e eMode;
    u8 nOpenFileVolume;
    u8 padding[3]; //Padding space for memory alignment
}file_monitor_info;

typedef struct
{
    file_monitor_info tFileInfo[FILEMGR_MAX_OPENED_FILES];
    Queue_t *pRegisterPath;
    Queue_t *pMonitorPath;
    u8 nCurrentOpenFileNumber;	//number of list file requested by user
    u8 nCurrentOpenFileNumberOnSD;	//number of list file requested by user which is located on SD card
    bool bIsSD1Access;
    bool bIsSD1LastAccess;
    bool bIsSD2Access;
    bool bIsSD2LastAccess;
} mmi_FileMgrFileMonitorData_t;

enum
{
    FILE_MGR_USB__UNPLUGGED = 0,
    FILE_MGR_USB__PCHOST_CDC, //Modem
    FILE_MGR_USB__PCHOST_MSC, //Mass storage
    FILE_MGR_USB__PCHOST_VDC  //WebCam
};


typedef struct FileMgr_BatchCommandFileList_tag
{
    FileMgr_WChar *pSrcURL;
    FileMgr_WChar *pDestURL;
    u32 nFileNum;
    u32 nFileExecNum;
    VFS_FileID_t *pFileID;
    FileMgrHandleID_t nHandleID;
    u32 nMarkHandleID;
    VFS_PartialListFilter_t *pListFilter;
    u32 nCommandSessionID; //Cancel command for m3
    u32 nPriority;
    union
    {
        u8 bIsSuspend;
    }param;
    u32 nVolumeID;
    u32 nChkdskOperation;
    MAEFILEMGR_Callback_Info_t Info;
    FileMgr_BatchCmdType_e eCmdType;
    u8 bIsDelayDeleteCmd;
}FileMgrBatchCmd_t; //Batch command

typedef enum
{
    FILE_MGR_PRI__LOW,
    FILE_MGR_PRI__NORMAL,
    FILE_MGR_PRI__HIGH,
    FILE_MGR_PRI__NUM,
}FileMgr_BatchCommandPriority;

typedef struct FileMgr_MarkListFolderInfo_tag
{
    FileMgr_WChar *pSrcURL;
    Queue_t *pListFolder; //FileMgr_MarkListFolderInfo_t
    struct FileMgr_MarkListFolderInfo_tag *pListFolderNext;
}FileMgrMarkListFolderInfo_t; //mark (for FileMgr_MarkListInfo_t)

typedef struct FileMgr_MarkListStoreInfo_tag
{
    FileMgr_WChar *pSrcURL;
    FileMgrHandleID_t nHandleID;
    u32 nListHandleID;
    u32 nTotalFileNum;
    u32 nUpperBound;
    FileMgrMarkListFolderInfo_t *pListHead;
    FileMgr_MarkListType_e MarkType_e;
}FileMgrMarkListStoreInfo_t; //mark (internal use)

typedef struct FileMgr_SortedListStoreInfo_tag
{
    FileMgr_WChar *pSrcURL;
    FileMgrHandleID_t nHandleID;
    u32 nTotalFileNum;
    FileMgrSortComp_Fxp pSortingComparator;
    FileMgrMarkListStoreInfo_t *pMarkListHead;
    FileMgrMarkListStoreInfo_t *pSortedListHead;
    FileMgrCbData_t tCbData;
    u8 bIsUpdatedMarkListHead;
}FileMgr_SortedListStoreInfo_t; //Sorting (for FileMgr_MarkListInfo_t)

typedef struct FileMgr_SearchListStoreInfo_tag
{
    FileMgr_WChar *pSrcURL;
    VFS_PartialListFilter_t *pListFilter;
    FileMgrHandleID_t nHandleID;
    u32 nListHandleID;
    u32 nTotalFileNum;
    u32 nCurrFolderIdx;
    FileMgrFindComp_Fxp pSearchFunc;
    FileMgrMarkListStoreInfo_t *pMarkListHead;
    FileMgrCbData_t tCbData; //user
    FileMgrHandleID_t nExtentionHandleID; //for mark folder(response)
    Queue_t *pFolderListQueue;
    Queue_t *pFolderListLevelQueue;
    u8 nTraversalLevel;
    u8 nCurrentLevel;
}FileMgr_SearchListStoreInfo_t; //Search

typedef struct FileMgr_ListCommand_tag
{
    FileMgr_WChar *pStrListURL;
    u32 nFileNum;
    VFS_PartialListFilter_t *pListFilter;
    FileMgrHandleID_t nHandleID;
    FileMgrHandleID_t nMonitorHandleID;
    FileMgr_SortedListStoreInfo_t *pSortHeaderHdl;
    FileMgrHandleID_t nExtentionHandleID; //for sorting, search(response)
    s32 nSessionID;
    u8 bIsListed;
    u8 bIsUnLocked;
}FileMgr_ListCommand_t; //List command

typedef struct
{
    Hashtable_t *pStrMarkCache;
    Hashtable_t *pIntListCache;
    Queue_t *pCmdQueue;
    Queue_t *pListQueue;
    Queue_t *pFileStatListener;
    bool bIsHaveVolume[VFS_VOL_MAX];
    bool bIsMounted[VFS_VOL_MAX];
    bool bIsDoCommand;
    bool bIsListing;
    bool bIsSystemSuspend;
	bool bIsBackLightOff;
}FileMgr_t;

typedef struct
{
    u32 *pRet;
} SyncOpenFolder_t;

typedef struct
{
    u32 *pRet;
} SyncDeleteFile_t;

typedef struct
{
    u32 *pRet;
}MoveEx_t;

typedef enum FileMgrNotifyType_e_
{
    FILE_MGR_NTF__DEFAULT_VALUE = 0,
    FILE_MGR_NTF__SUSPEND,
} FileMgrNotifyType_e;

typedef enum FileMgrEvt_e_
{
    FILE_MGR_EVT__DEFAULT_VALUE = 0,
    FILE_MGR_EVT__SD_ACCESS = (1 << 0),		    //1
    FILE_MGR_EVT__SD_FULL = (1 << 1),		    //2
    FILE_MGR_EVT__COPY = (1 << 2),		    	//4
    FILE_MGR_EVT__MOVE = (1 << 3),		    	//8
    FILE_MGR_EVT__DELETE = (1 << 4),	    	//16
    FILE_MGR_EVT__LIST = (1 << 5),		    	//32
    FILE_MGR_EVT__SORT = (1 << 6),		    	//64
    FILE_MGR_EVT__SEARCH = (1 << 7),	    	//128
    FILE_MGR_EVT__DELETE_ALL = (1 << 8),	    //256
    FILE_MGR_EVT__MONITOR_PATH = (1 << 9),   	//512
    FILE_MGR_EVT__RMDIR = (1 << 10),   	        //1024
    FILE_MGR_EVT__SUSPEND = (1 << 11),   	    //2048
    FILE_MGR_EVT__FORMAT = (1 << 12),   	    //4096
    FILE_MGR_EVT__CHKDSK = (1 << 13),   	    //8192
} FileMgrEvt_e;

typedef void (*pFuncFileMgrNotifyFailed)(u32, MAE_Ret, u32, u32);

/*=============================================================*/
// Function Declarations
/*=============================================================*/
//Get file manager instance
__SLDPM_FREE__ FileMgr_t *FileMgrGetInstance(void);
__SLDPM_FREE__ MAE_Ret FileMgrNewHandleID(FileMgrHandleID_t *pHandleID);
__SLDPM_FREE__ void FileMgrDeleteHandleID(FileMgrHandleID_t nHandleID);
//__inline void *FileMgrHandleID2HashKey(FileMgrHandleID_t nHandleID);
//Utility to notify file manager some file is opened by app


MAE_Ret FileListCommandHandling(FileMgr_FileList_t *pFileListCommand);
MAE_Ret _CmdMgrInsertBatchCmd(FileMgrBatchCmd_t *pFileListCmdHdl, FileMgrCbData_t *pCbData);
MAE_Ret _CmdMgrExecuteNextCmd(void);
MAE_Ret _CmdMgrFindFirstHigherCmd(FileMgrBatchCmd_t **ppFileListCmdHdl);
FileMgrBatchCmd_t* _CmdMgrCheckCmdSessionID(s32 nSessionID);
MAE_Ret _CmdMgrCancelBatchCmd(u32 nHandleID, bool bForceDeleteCmd); //CmdBuffer-Search(cancel)

//Batch Command
MAE_Ret _ExecEnvelopeSingleCmd(FileMgrBatchCmd_t **ppFileCmdHdl, const FileMgr_WChar *pSrcURL, const FileMgr_WChar *pDestURL, FileMgr_BatchCmdType_e nCommandType_e, u32 nPriority);
MAE_Ret _ExecEnvelopeBatchCmd(FileMgrBatchCmd_t **ppFileCmdHdl, FileMgr_FileList_t *pFileListCmd, FileMgr_BatchCmdType_e nCommandType_e);
MAE_Ret _ExecEnvelopeMarkedBatchCmd(u32 nMarkHandleID, FileMgrBatchCmd_t **ppFileCmdHdl, FileMgr_BatchCmdType_e eCmdType, FileMgr_WChar *pDestURL);
void FileMgrFreeBatchCommand(FileMgrBatchCmd_t *pFileListCmdHdl);

__SLDPM_FREE__ MAE_Ret _ExecQueryPathStatus(FileMgr_WChar *pStrPath, FileMgrOperation_e *pOperation, u8 nVolumeID);
__SLDPM_FREE__ MAE_Ret _ExecIsPathAllowOperation(FileMgr_WChar *pStrPath, FileMgrOperation_e eOperation);

__SLDPM_FREE__ MAE_Ret _ExecLockPathStatus(FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL, FileMgrOperation_e eOperation, u8 nVolumeID);
__SLDPM_FREE__ MAE_Ret _ExecUnLockPathStatus(FileMgrHandleID_t nHandleID);

MAE_Ret _ExecMonitorPath(FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrPath, FileMgrOperation_e nMode_e, FileMgrCbData_t *pCbData, u8 nVolumeID);
MAE_Ret _ExecDeMonitorPath(FileMgrHandleID_t nHandleID);

MAE_Ret _ExecNotifyPathOperation(FileMgrOperation_e eMode);
__SLDPM_FREE__ MAE_Ret _ExecNotifyPathStatus(FileMgr_WChar *pStrPath, FileMgrOperation_e Operation_e);
__SLDPM_FREE__ MAE_Ret _ExecNotifyVolume(u8 nVolumeID, bool bIsAccess);

//Listing Command
__SLDPM_FREE__ MAE_Ret FileMgrEnvelopeListCommand(FileMgr_ListCommand_t **ppListCommandHandle, VFS_PartialListFilter_t *pListFilter, FileMgr_WChar *pStrURL);
__SLDPM_FREE__ MAE_Ret _CmdMgrInsertListCmd(FileMgr_ListCommand_t *pFileListCmdHdl);
MAE_Ret _CmdMgrExecuteNextListCmd(void);
MAE_Ret _CmdMgrCancelListCmd(u32 nHandleID);
MAE_Ret _CmdMgrFreeCmd(u32 nHandleID);
__SLDPM_FREE__ MAE_Ret _CmdMgrExecuteQueryFileNum(FileMgr_WChar *pStrPath, VFS_PartialListFilter_t *pListFilter, u32 *pFileNumber);
MAE_Ret _CmdMgrExecuteListFolder(u32 nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);

//FileID compare & Assign
u8 FileMgrFileIDCompare(void *pSourceFileID, void *pDestFileID);
__SLDPM_FREE__ void FileMgrFileIDAssign(VFS_FileID_t *pDestFileID, VFS_FileID_t *pSourceFileID);
//List & Sort notify
void FileMgrUpdateFolderFileNumber(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
MAE_Ret FileMgrSortMarkList(u32 nHandleID);
MAE_Ret FileMgrSortListData(u32 nHandleID, FileMgr_ListData_t *pListData);
MAE_Ret FileMgrInitSorting(FileMgr_ListCommand_t *pListCmdHdl, FileMgrSortComp_Fxp pCompareFunc, FileMgrCbData_t *pCbData);
MAE_Ret _ExecSorting(FileMgr_ListCommand_t *pListCmdHdl);
MAE_Ret _ExecSortingWithoutMarkData(FileMgr_ListCommand_t *pListCmdHdl, u8 bIsNotify);
MAE_Ret FileMgrInsertionSort(u32 nFileNum, VFS_PartialListFileInfo_t *pListHead, u16 *pSortedList, FileMgrSortComp_Fxp pCompareFunc);
void FileMgrForFolderAccessNotifyCB(void *pUser, void *pInfo);
//File Read & Write notify
void FileMgrUpdateFileRead(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrUpdateFileWrite(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);

//Search
void FileMgrSearchListFolderNotify(void *pUser, void *pInfo);
MAE_Ret FileMgrSearchInsertResult(FileMgr_SearchListStoreInfo_t *pSearchHeaderHdl, VFS_NotifyInfo_t *pListUpdateInfo, u8 *pIsFinished, u16 nQueryFiles);
s32 FileMgrSearchDefaultFilter(void *pFileInfo);
//Mark
void FileMgrMarkSearchListFolderNotify(void *pUser, void *pInfo);
MAE_Ret FileMgrUpdateMarkListWithoutSearch(u32 nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret FileMgrProcessMarkFolder(FileMgrHandleID_t nHandleID, FileMgrMarkListStoreInfo_t *pMarkListHeaderHdl, FileMgr_ListData_t *pMarkListInfoData);

//Mics
__SLDPM_FREE__ u32 FileMgrConvertFSTimeToRTCTime(u32 nFsTime);

MAE_Ret FileMgrMatchVolumeID(FileMgr_WChar *pStrVol, u8 *pVol);
MAE_Ret FileMgrGetVolumeName(FileMgr_WChar *pStrVolumeName, u8 nVol);

//Init
void FileMgrInit(void);
//Psrser
__SLDPM_FREE__ void FileMgrParser(void *pReceivedMsg);
//Destory
void FileMgrDestory(void);
//DeleteAll
void FileMgrDeleteAllFilesNotify(void *pUser, void *pInfo);

void FileMgrTaskInit(void);
//SetCallBack
void FileMgrSendFileWrite(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsInfo);
void FileMgrSendFileRead(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsInfo);
void FileMgrSendUpdateFolderFileNumber(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pEfsInfo);
void FileMgrSendSearchListFolderNotify(void *pUser, void *pInfo);
void FileMgrSendSortingListFolderNotify(void *pUser, void *pInfo);
//ConcatenateWithCheckLenth
FileMgr_WChar* FileMgrPathStringConcatenateWithCheck(FileMgr_WChar *pStrA, FileMgr_WChar *pStrB, FileMgr_WChar *pStrC);
__SLDPM_FREE__ MAE_Ret _ExecConvertVolumeName(FileMgr_WChar *pStrURL);
//InitFilter
__SLDPM_FREE__ void FileMgrSetFilter(VFS_PartialListFilter_t **ppDestFilter, VFS_PartialListFilter_t *pSourceFilter);

//MailBox
__SLDPM_FREE__ MAE_Ret _ExecOpenFolderHdl(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID, FileMgr_WChar *pStrURL);
MAE_Ret _ExecGetFolderFileNum(FileMgrHandleID_t nHandleID, u32 *pFileNumber, FileMgrCbData_t *pCbData);
MAE_Ret _ExecSetSortingMethod(FileMgrHandleID_t nHandleID, FileMgrSortComp_Fxp pCompareFunc, FileMgrCbData_t *pCbData);
MAE_Ret _ExecListFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret _ExecCloseFolderHdl(FileMgrHandleID_t nHandleID);

MAE_Ret _ExecCreateSearchMarkList(VFS_PartialListFilter_t *pListFilter, FileMgrHandleID_t *pHandleID,FileMgr_WChar *pStrURL, u32 *pFileNumber, FileMgrFindComp_Fxp pSearchFunc, FileMgrCbData_t *pCbData, u8 nTraversalLevel);
MAE_Ret _ExecListSearchedFolder(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nFileListSize, FileMgr_ListData_t *pListData);
MAE_Ret _ExecListSearchedFolderGetURL(FileMgrHandleID_t nHandleID, u32 nStartIndex, u32 nListSize, FileMgrSearchURL_t *pListURL);
MAE_Ret _ExecGetSearchedFileNum(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret _ExecDestorySearchMarkList(FileMgrHandleID_t nHandleID);

__SLDPM_FREE__ MAE_Ret _ExecCreateMarkList(FileMgr_WChar *pSrcURL, FileMgrHandleID_t *pHandleID, u32 nUpperBound);
MAE_Ret _ExecCopy(u32 *pSessionID, FileMgr_WChar *pSrcURL, FileMgr_WChar *pStrDestURL);
MAE_Ret _ExecMove(u32 *pSessionID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL);
MAE_Ret _ExecUpdateMarkList(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret _ExecUpdateMarkListWithoutSubfolder(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret _ExecQueryMarkListNumID(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret _ExecQueryMarkListID(FileMgrHandleID_t nHandleID, u32 nStartIndex, FileMgrMarkListID_t *pMarkListIDData);
MAE_Ret _ExecQueryIsMarkedMarkListID(FileMgrHandleID_t nHandleID, VFS_FileID_t nFileID);
MAE_Ret _ExecMarkAllByPath(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID);
MAE_Ret _ExecMarkAllExByPath(FileMgrHandleID_t nMarkHandleID, FileMgrHandleID_t nFolderHandleID, FileMgrMarkComp_Fxp pCompFunc, FileMgrCbData_t *pCbData);
MAE_Ret _ExecUnMarkAllByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL);
MAE_Ret _ExecQueryMarkedNumberByURL(FileMgrHandleID_t nHandleID, FileMgr_WChar *pStrURL, u32 *pMarkNumber);
MAE_Ret _ExecDestoryMarkList(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrSendCreateMarkList(FileMgr_WChar *pSrcURL, FileMgrHandleID_t *pHandleID, u32 nUpperBound);
MAE_Ret FileMgrSendUpdateMarkList(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret FileMgrSendUpdateMarkListWithoutSubfolder(FileMgrHandleID_t nHandleID, FileMgrMarkListChange_t *pMarkListChangeIDData);
MAE_Ret FileMgrSendQueryMarkListNumberID(FileMgrHandleID_t nHandleID, u32 *pFileNumber);
MAE_Ret FileMgrSendQueryMarkListID(FileMgrHandleID_t nHandleID, u32 nStartIndex, FileMgrMarkListID_t *pMarkListIDData);
MAE_Ret FileMgrSendQueryIsMarkedMarkListID(FileMgrHandleID_t nHandleID, VFS_FileID_t nFileID);
MAE_Ret FileMgrSendDestoryMarkList(FileMgrHandleID_t nHandleID);

MAE_Ret FileMgrSendStreamRead(void *pStream, void *pBuffer, u32 nWordCnt, u32 *pByteRead, FileMgrCallback_Fxp pfnCallBackFuncPtr);
MAE_Ret FileMgrSendStreamSyncRead(void *pStream, void *pBuffer, u32 nWordCnt, u32 *pByteRead);
MAE_Ret FileMgrSendStreamWrite(void *pStream, const void *pBuffer, u32 nCount, FileMgrCallback_Fxp pfnCallBackFuncPtr, FileMgrFileCallback_t *pCallBackData);
MAE_Ret FileMgrSendStreamSyncWrite(void *pStream, const void *pBuffer, u32 nCount);
void FileMgrSendStreamSetCallBack(void *pStream, PfnFileMgr_StreamCallback pfnStreamCB, void *pUser);
void FileMgrSendStreamCancelCallBack(void *pStream);
__SLDPM_FREE__ MAE_Ret FileMgrSendStreamCheckStreamSize(void *pStream);
MAE_Ret FileMgrSendStreamSeek(void *pStream, s32 nOffset, FileMgrSeekType_e eSeekType);
s32 FileMgrSendStreamGetCurrentPos(void *pStream);
MAE_Ret FileMgrSendIsStreamEOF(void *pStream);

MAE_Ret FileMgrSendMkDir(const FileMgr_WChar *pStrURL);
MAE_Ret FileMgrSendAsyncRmDir(u32 *pHandleID, FileMgr_WChar *pSrcURL, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrSendRmDir(const FileMgr_WChar *pStrURL);

void FileMgrSendVolumeInit(void);
MAE_Ret FileMgrSendQueryVolumeStatus(u32 nVolumeID);

MAE_Ret FileMgrSendQueryFsDiskState(VFS_VOL_TYPE eVolType,VFS_DiskStatus_e * pDiskState);

MAE_Ret FileMgrSendRenameFile(const FileMgr_WChar *pSrcURL, const FileMgr_WChar *pStrDestName);
MAE_Ret FileMgrSendFormat(u32 nVolumeID);
MAE_Ret FileMgrSendSuspend(FileMgrHandleID_t *pHandleID, u8 bIsSuspend, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrSendQuerySuspend(void);
__SLDPM_FREE__ MAE_Ret FileMgrSendQueryBatchCommandStatus(ExecuteBatchCmdType_t *pBatchCmdType);
MAE_Ret FileMgrSendAsyncFormat(FileMgrHandleID_t pHandleID, u32 nVolumeID, FileMgrCbData_t *pCbData);
MAE_Ret FileMgrSendChkdsk(FileMgrHandleID_t pHandleID, u32 nVolumeID, u32 nChkdskOperation, FileMgrCbData_t *pCbData);

MAE_Ret FileMgrSendCheckFreeSpace(const FileMgr_WChar *pStrURL, u32 *pTotalSize, u32 *pRemainSize);
__SLDPM_FREE__ MAE_Ret FileMgrSendIsExist(const FileMgr_WChar *pStrURL);
__SLDPM_FREE__ MAE_Ret FileMgrSendGetInfo(const FileMgr_WChar *pStrURL, VFS_PartialListFileInfo_t *pFileInfo);
MAE_Ret FileMgrSendSetFileAttr(const FileMgr_WChar *pStrURL, u32 nFileAttr);

//File access operation
__SLDPM_FREE__ MAE_Ret _ExecOpenedFile(void **ppStreamResult, const FileMgr_WChar *pStrURL, const u8 *pMode, void *pOwner);
__SLDPM_FREE__ MAE_Ret _ExecClosedFile(void *pStream);
__SLDPM_FREE__ MAE_Ret _ExecNotifyOpenedFile(void **ppStreamResult, const FileMgr_WChar *pStrURL, const u8 *pMode, void *pOwner);
MAE_Ret _ExecNotifyClosedFile(void *pStream);
//For UnClosed file debug
void _ExecPrintUnClosedFiles(void);

MAE_Ret _ExecQueryOpenedFileStatus(const FileMgr_WChar *pStrURL);

__SLDPM_FREE__ MAE_Ret _ExecStreamNew(void **ppObj, FileMgrFileInit_t *pInit);
__SLDPM_FREE__ MAE_Ret _ExecStreamRelease(void *pObj);

__SLDPM_FREE__ MAE_Ret _ExecFileStreamRead(void *pObj, void *pBuffer, u32 nWordCnt, u32 *pByteRead, FileMgrCallback_Fxp pfnCallBackFuncPtr);
MAE_Ret _ExecFileStreamWrite(void *pObj, const void *pBuffer, u32 nCount, FileMgrCallback_Fxp pfnCallBackFuncPtr, FileMgrFileCallback_t *pCallBackData);

__SLDPM_FREE__ MAE_Ret _ExecStreamNew(void **ppObj, FileMgrFileInit_t *pInit);
MAE_Ret _ExecStreamRelease(void *pStream);
void _ExecFileStreamSetCallBack(void *pObj, PfnFileMgr_StreamCallback pfnStreamCB, void *pUser);
void _ExecFileStreamCancelCallBack(void *pObj);
__SLDPM_FREE__ MAE_Ret _ExecFileStreamCheckStreamSize(void *pObj);
__SLDPM_FREE__ MAE_Ret _ExecFileStreamSeek(void *pObj, s32 nOffset, FileMgrSeekType_e eSeekType);
s32 _ExecFileStreamGetCurrentPos(void *pObj);
MAE_Ret _ExecFileIsStreamEOF(void *pObj);
MAE_Ret _ExecFstreamCheckReadSessionID(s32 nSessionID);
MAE_Ret _ExecFstreamCheckWriteSessionID(s32 nSessionID);

MAE_Ret _ExecSyncMkDir(const FileMgr_WChar *pStrURL);
MAE_Ret _ExecSyncRmDir(const FileMgr_WChar *pStrURL);

//Delete(Multi-files)(ASync)
s32 _ExecDelete(FileMgr_WChar *pStrURL);
MAE_Ret _ExecAsyncDelete(u32 *pSessionID, FileMgr_WChar *pStrURL);
MAE_Ret _ExecDeleteAllFiles(VFS_PartialListFilter_t *pListFilter, FileMgr_WChar *pSrcURL, u32 *pHandleID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecDeleteFiles(FileMgr_FileList_t *pFileListCommand, u32 *pHandleID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecDeleteMarkedFiles(FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecDeleteSingleFile(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrURL, FileMgrCbData_t *pCbData);
MAE_Ret _ExecSyncDeleteSingleFile(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrURL, FileMgrCbData_t *pCbData);

MAE_Ret _ExecMoveMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecMoveFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecMoveSingleFile(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);

MAE_Ret _ExecCopyMarkedFiles(FileMgr_WChar *pDestURL, FileMgrHandleID_t *pHandleID, u32 nMarkHandleID, FileMgrCbData_t *pCbData);
__SLDPM_FREE__ MAE_Ret _ExecCopyFiles(FileMgr_FileList_t *pFileListCommand, FileMgrHandleID_t *pHandleID, FileMgrCbData_t *pCbData);
__SLDPM_FREE__ MAE_Ret _ExecCopySingleFile(FileMgrHandleID_t *pHandleID, const FileMgr_WChar *pStrSrcURL, const FileMgr_WChar *pStrDestURL, FileMgrCbData_t *pCbData);
MAE_Ret _ExecBatchCmdAbort(FileMgrHandleID_t nHandleID);

MAE_Ret _ExecRmDir(u32 *pHandleID, FileMgr_WChar *pSrcURL, FileMgrCbData_t *pCbData);
MAE_Ret _ExecSuspend(u32 *pHandleID, u8 bIsSuspend,FileMgrCbData_t *pCbData);

MAE_Ret FileMgrInternalSendCloseFolderHandle(FileMgrHandleID_t nHandleID);
MAE_Ret FileMgrInternalSendDestorySearchHandle(FileMgrHandleID_t nHandleID);
__SLDPM_FREE__ MAE_Ret FileMgrInternalSendNotifyPathStatus(FileMgr_WChar *pStrPath, FileMgrOperation_e Operation_e);

MAE_Ret FileMgrQueryOpenedFileStatus(const FileMgr_WChar *pStrURL);

MAE_Ret FileMgrProcessMarkedBatchCommand(FileMgrBatchCmd_t *pFileListCmdHdl, FileMgr_WChar **ppSrcURL, FileMgr_WChar **ppStrDestURL);
MAE_Ret FileMgrProcessBatchCommand(FileMgrBatchCmd_t *pFileListCmdHdl, FileMgr_WChar **ppSrcURL);
MAE_Ret FileMgrProcessDeleteAllCommand(FileMgrBatchCmd_t *pFileListCmdHdl);
MAE_Ret FileMgrProcessDeleteCommand(FileMgrBatchCmd_t *pFileListCmdHdl, FileMgr_WChar *pSrcURL);
MAE_Ret FileMgrProcessRmDirCommand(FileMgrBatchCmd_t *pFileListCmdHdl);
MAE_Ret FileMgrProcessSuspendCommand(FileMgrBatchCmd_t *pFileListCmdHdl);
MAE_Ret FileMgrProcessAsyncFormatCommand(FileMgrBatchCmd_t *pFileListCmdHdl);
MAE_Ret FileMgrProcessChkdskCommand(FileMgrBatchCmd_t *pFileListCmdHdl);
void FileMgrDeleteCurrentCommand(FileMgrBatchCmd_t *pFileListCmdHdl);

//CallBack
void FileMgrForVfsMoveNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsCopyNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsDeleteNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsDeleteAllNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsRmDirNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForSuspendNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsAsyncFormatNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForVfsChkdskNotifyCB(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);
void FileMgrForDeleteAllNRsp(u16 senderID, u32 userValue, VFS_NotifyInfo_t *pVfsNotifyInfo);

__SLDPM_FREE__ void FileMgrRegEvt(FileMgrHandleID_t nHandleId, u16 nRegEvtInfo, FileMgrFileStatusCB_Fxp pCallback, void *pUserData);
__SLDPM_FREE__ void FileMgrNotifyEvent(FileMgrHandleID_t nHandleID, FileMgrEvt_e eEvtInfo, void *pNotifyData);
FileMgrLisSetting_t *FileMgrGetRegEvt(FileMgrHandleID_t nHandleID, FileMgrEvt_e eEvtInfo);
__SLDPM_FREE__ void FileMgrDeregEvt(FileMgrHandleID_t nHandleId, u16 nRegEvtInfo);

//Ind
void FileMgr_CopyInd(VFS_NotifyInfo_t *pCopyInd);
void FileMgr_MoveInd(VFS_NotifyInfo_t *pMoveInd);
void FileMgr_DeleteInd(VFS_NotifyInfo_t *pDeleteInd);
void FileMgr_DeleteAllInd(VFS_NotifyInfo_t *pDeleteInd);
void FileMgr_RmDirInd(VFS_NotifyInfo_t *pRmDirInd);
void FileMgr_SuspendInd(VFS_NotifyInfo_t *pSuspendInd);
void FileMgr_SuspendTimeOutInd(void);
void FileMgr_AsyncFormatInd(VFS_NotifyInfo_t *pFormatInd);
void FileMgr_ChkdskInd(VFS_NotifyInfo_t *pFormatInd);

void MMI_ConvertErrorCode(VFS_NotifyInfo_t *pNotifyInfo);

__SLDPM_FREE__ void *FileMgrHandleID2HashKey(FileMgrHandleID_t nHandleID);

FileMgr_ListCommand_t *FileMgrCheckListSessionID(VFS_NotifyInfo_t *pListUpdateInfo);
FileMgr_ListCommand_t *FileMgrCheckListHandleID(VFS_NotifyInfo_t *pListUpdateInfo);
__SLDPM_FREE__ void FileMgrSendDestoryAllCommand(char *pSbjName, u32 nSbjStatus, void *pUser);
MAE_Ret FileMgrCheckSystemSuspend(void);
MAE_Ret FileMgrClearAll(char *pSbjName, u32 nSbjStatus, void *pUser);
MAE_Ret FileMgrClearAllBatchCmd(void);
MAE_Ret FileMgrClearAllListCmd(void);
MAE_Ret FileMgrClearAllOpenedFiles(void);
MAE_Ret FileMgrClearAllListener(void);

//Abort Command
MAE_Ret _ExecMoveAbort(u32 nVfsSessionID);
__SLDPM_FREE__ MAE_Ret _ExecCopyAbort(u32 nVfsSessionID);
MAE_Ret _ExecDeleteAbort(u32 nVfsSessionID);

//Utility to convert url to path and file name
//if argument is point of point, it must free the memory after use. EX:pStrPath, pStrFileName, ppDestPath, ppDestPath
__SLDPM_FREE__ MAE_Ret FileMgrProcessFilePath(const FileMgr_WChar *pStrDir, FileMgr_WChar **pStrPath, FileMgr_WChar **pStrFileName, u8 *pVolumeID);

void _ExecVolumeInit(void);
MAE_Ret _ExecQueryVolumeStatus(u32 nVolumeId);

MAE_Ret _ExecQueryFsDiskState(VFS_VOL_TYPE eVolType,VFS_DiskStatus_e * pDiskState);


MAE_Ret FileMgrSendSetSuspend(FileMgrHandleID_t *pHandleID, u8 bIsSuspend, FileMgrCbData_t *pCbData);
MAE_Ret _ExecRenameFile(const FileMgr_WChar *pSrcURL, const FileMgr_WChar *pStrDestName);

MAE_Ret _ExecFormat(u32 nVolumeID);
__SLDPM_FREE__ MAE_Ret _ExecPauseResume(FileMgrHandleID_t nHandleID, u8 bSetPause);

MAE_Ret _ExecSuspendNotify(MAE_Ret nResult, u8 bIsSetSuspend);
MAE_Ret _ExecCheckSuspendCondition(void);
MAE_Ret _ExecSetSuspend(u8 bIsSuspend);
__SLDPM_FREE__ MAE_Ret _QuerySystemSuspend(void);

MAE_Ret _ExecQueryBatchCommandStatus(ExecuteBatchCmdType_t *pBatchCmdType);
MAE_Ret _ExecAsyncFormat(FileMgrHandleID_t *pHandleID, u32 nVolumeID, FileMgrCbData_t *pCbData);
MAE_Ret _ExecChkdsk(FileMgrHandleID_t *pHandleID, u32 nVolumeID, u32 nChkdskOperation, FileMgrCbData_t *pCbData);


MAE_Ret _ExecCheckFreeSpace(const FileMgr_WChar *pStrURL, u32 *pTotalSize, u32 *pRemainSize);
__SLDPM_FREE__ MAE_Ret _ExecIsExist(const FileMgr_WChar *pStrURL);
__SLDPM_FREE__ MAE_Ret _ExecGetInfo(const FileMgr_WChar *pStrURL, VFS_PartialListFileInfo_t *pFileInfo);
MAE_Ret _ExecSetFileAttr(const FileMgr_WChar *pStrURL, u32 nFileAttr);

__SLDPM_FREE__ void _ExePrintPath(FileMgr_WChar *pPath);
__SLDPM_FREE__ void _ExecCheckDebounce(u8 nVolumeID, u8 bIsAccess);
__SLDPM_FREE__ void _ExecSD1AccessDebounce(void);
void _ExecSD2AccessDebounce(void);

//ErrorCode
MAE_Ret _ConvertVfsErrCode(s32 nErrorCode);

__SLDPM_FREE__ void* _InitMailHeader(u32 nTaskID, u32 nSize, u32 nTypMsg);
__SLDPM_FREE__ u32 _GetVolMappingNum(void);

MAE_Ret _ExecNotifyBackLightOff(u8 bIsBackLightOff);

MAE_Ret _FNCheckAndCatSNEx(MAE_WChar **ppFullpath, boolean *pbFNCollision, u32 *pu32FNLen, boolean bIsForceReName);

FileMgr_WChar * _FNUtil_RemoveExtension(const FileMgr_WChar *pFilename);
FileMgr_WChar * _FNUtil_CopyExtension(const FileMgr_WChar *pFilename);

/*=============================================================*/
// Variable Declarations
/*=============================================================*/
extern FileMgr_t *g_pFileMgr;
extern const FileMgr_VolMappingTbl_t _tFileMgr_VolMappingTbl[];

#endif //__SRV_FILEMGR_PRIV_H__
