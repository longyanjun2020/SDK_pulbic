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
* @file    srv_filemgr_data_types.h
* @version
* @brief
*
*/

#ifndef __SRV_FILEMGR_DATA_TYPES_H__
#define __SRV_FILEMGR_DATA_TYPES_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mdl_vfs_struct.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
//Settings
#define FILEMGR_MAXIMUM_MARK_NUMBER						(1000)
#define FILEMGR_MAXIMUM_FILE_NUMBER						(0xffff)
#define FILEMGR_DELLETE_NUMBER_PER_TIME					(10)
#define FILEMGR_MAXIMUM_SORTING_NUMBER					(300)
#define FILEMGR_QUERY_NUMBER_PER_TIME					(90)
#define FILEMGR_DEFAULT_FOLDER_QUEUE_SIZE				(8)
#define FILEMGR_MAXIMUM_SEARCH_LEVEL                                    (150)
#define FILEMGR_FILESYSTEM_NAME_LENGTH      (3)
#define FILEMGR_MAX_FILEPATH_SIZE           (VFS_FAT_SPEC_FULLPATH_LEN + FILEMGR_FILESYSTEM_NAME_LENGTH) // include '\0'
#define FILEMGR_MAX_FILENAME_SIZE           (VFS_FAT_SPEC_FULLNAME_LEN)  // include '\0'

// This definition is for folder creation only.
// For Folder renaming case, please use fs API to get allowed length from file system.
#define FILEMGR_MAX_CREATEFOLDERPATH_SIZE   (250 + FILEMGR_FILESYSTEM_NAME_LENGTH + 1/* '\0' char */) // include '\0'

#define MAE_FILESYSTEM_NAME                 L"fs:"
#define FILEMGR_FILESYSTEM_NAME             L"fs:"
#define FILEMGR_BACKSLASH                   '\\'
#define FILEMGR_SLASH                       '/'
#define FILEMGR_SEPARATOR                   FILEMGR_SLASH
#define FILEMGR_FILENAME_DELIMITER          "\\"      /* We support both "\" and "/" */
#define FILEMGR_CURRENT_FOLDER              L"."          /* file name notation: stands for current directory*/
#define FILEMGR_PARENT_FOLDER               L".."          /* file name notation: stands for parrent directory*/
#define VOLUME_NAME_LEN                     (12) // refer to vfs_fat.ho

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef u32 FileMgrHandleID_t;
typedef u16 FileMgr_WChar;
typedef u8 FileMgrAttribute_e;

typedef void (*FileMgrCallback_Fxp) (void *pUser, void *pInfo);
typedef s32 (*FileMgrSortComp_Fxp) (void *pBase, void *pRef);
typedef s32 (*FileMgrFindComp_Fxp) (void *pBase, void *pInfo);
typedef s32 (*FileMgrMarkComp_Fxp) (void *pBase, void *pInfo);
typedef void (*FileMgrFileStatusCB_Fxp)(void *pUserData, void *pMessageBody);

typedef struct
{
	FileMgrCallback_Fxp Callback;
	void *pCusData;
}FileMgrCbData_t;

typedef struct
{
	u32 nRetCode; //MAE_Ret
	u32 nPosition;
    u32 nFileNum;
    u32 nCurIdx;
}MAEFILEMGR_Callback_Info_t;

typedef struct FileMgr_FileList_tag
{
	FileMgr_WChar *pSrcURL;
	FileMgr_WChar *pDestURL;
	u32 nFileNum;
	VFS_FileID_t *pFileID;
}FileMgr_FileList_t;

typedef enum FileMgr_MarkListType_e_
{
	UnMark = 0,
	Mark,
	For4ByteAlignment = 0x01ffff // Dummy value for 4-bytes alignment
}FileMgr_MarkListType_e;

typedef struct FileMgr_MarkListChange_tag
{
	FileMgr_WChar *pSrcURL;
	VFS_FileID_t nFileID;
	FileMgr_MarkListType_e nMarkFileType;
}FileMgrMarkListChange_t; //mark (for set)

typedef struct FileMgr_ListData_tag
{
	u32 nFiles;
	VFS_PartialListFileInfo_t *pListHead;
}FileMgr_ListData_t; //list (return)

typedef struct FileMgr_MarkListInfo_tag
{
	u32 nTotalFileNum;
	VFS_PartialListFileInfo_t *pListHead;
}FileMgr_MarkListInfo_t; //mark (return FileInfo)

typedef struct FileMgr_MarkListID_tag
{
	FileMgr_WChar *pSrcURL;
	VFS_FileID_t nFileID;
}FileMgrMarkListID_t; //mark (return ID) //for update date

typedef struct FileMgrLisSetting_t_
{
	FileMgrHandleID_t nHandleID;
	u16 nRegEvtInfo;
	FileMgrFileStatusCB_Fxp Callback;
	void *pUserData;
} FileMgrLisSetting_t;

typedef struct
{
	FileMgr_WChar SearchURL[FILEMGR_MAX_FILEPATH_SIZE];
} FileMgrSearchURL_t;

typedef struct FileMgrMarkAllExInfo_t_tag
{
    const FileMgr_WChar *pwszSrcURL;
    const VFS_PartialListFileInfo_t *pListHead;
}FileMgrMarkAllExInfo_t;

typedef enum
{
	FILE_MGR_CMD__SINGLE_DELETE = 10,
	FILE_MGR_CMD__SINGLE_MOVE,
	FILE_MGR_CMD__SINGLE_COPY,
	FILE_MGR_CMD__BATCH_DELETE = 20,
	FILE_MGR_CMD__BATCH_MOVE,
	FILE_MGR_CMD__BATCH_COPY,
	FILE_MGR_CMD__DELETE_ALL = 30,
	FILE_MGR_CMD__MARKED_BATCH_DELETE = 40,
	FILE_MGR_CMD__MARKED_BATCH_MOVE,
	FILE_MGR_CMD__MARKED_BATCH_COPY,
	FILE_MGR_CMD__RMDIR = 50,
	FILE_MGR_CMD__SUSPEND = 60,
	FILE_MGR_CMD__FORMAT = 70,
	FILE_MGR_CMD__CHKDSK = 80,
}FileMgr_BatchCmdType_e;

typedef enum
{
    FILE_MGR_OPR__DEFAULT = 0,                  //0
    FILE_MGR_OPR__RENAME = (1 << 0),            //1
    FILE_MGR_OPR__RMDIR = (1 << 1),             //2
    FILE_MGR_OPR__OPEN_WITH_READ = (1 << 2),    //4
    FILE_MGR_OPR__OPEN_WITH_WRITE = (1 << 3),   //8
    FILE_MGR_OPR__LIST = (1 << 4),              //16
    FILE_MGR_OPR__DELETE = (1 << 5),            //32
    FILE_MGR_OPR__COPY = (1 << 6),              //64
    FILE_MGR_OPR__MOVE = (1 << 7),              //128
    FILE_MGR_OPR__ADD_BY_FOLDER = (1 << 8),     //256
    FILE_MGR_OPR__MKDIR_BY_FOLDER = (1 << 9),   //512
    FILE_MGR_OPR__RENAME_BY_FOLDER = (1 << 10), //1024
    FILE_MGR_OPR__RMDIR_BY_FOLDER = (1 << 11),  //2048
    FILE_MGR_OPR__DELETE_BY_FOLDER = (1 << 12), //4096
    FILE_MGR_OPR__COPY_BY_FOLDER = (1 << 13),   //8192
    FILE_MGR_OPR__MOVE_BY_FOLDER = (1 << 14),   //16384
    FILE_MGR_OPR__DELETE_ALL_BY_FOLDER = (1 << 15), //32768
    FILE_MGR_OPR__SD = (1 << 16),               //65536
}FileMgrOperation_e; //Notify

typedef struct
{
    FileMgr_WChar strURL[FILEMGR_MAX_FILEPATH_SIZE];
    FileMgr_BatchCmdType_e eCmdType;
} ExecuteBatchCmdType_t;

typedef struct
{
    const FileMgr_WChar *pVolName;
    u8 nVolID;
    const FileMgr_WChar *pDevName;
}FileMgr_VolMappingTbl_t;

#define ATTR_NORMAL 0x00     ///< File is normal type
#define ATTR_RDONLY 0x01     ///< Read only
#define ATTR_HIDDEN 0x02     ///< Hidden
#define ATTR_SYSTEM 0x04     ///< System
#define ATTR_SUBDIR 0x10     ///< Directory
#define ATTR_ARCH   0x20     ///< Archive

#endif //__SRV_FILEMGR_DATA_TYPES_H__
