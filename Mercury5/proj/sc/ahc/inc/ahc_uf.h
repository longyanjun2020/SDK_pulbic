//==============================================================================
//
//  File        : AHC_UF.c
//  Description : INCLUDE File for the AHC UF(Universal File) function porting.
//  Author      : Rogers Chen
//  Revision    : 1.0
//
//=============================================================================

#ifndef _AHC_UF_H_
#define _AHC_UF_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"
#include "ahc_rtc.h"
#include "ahc_parameter.h"
#include "ahc_os.h"
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
#include "ahc_dcf.h"
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
#include "ahc_dcfdt.h"
#endif
#include "ahc_media.h"
#include "ahc_mimf.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//For Search File Format Char */
#define SEARCH_PHOTO                        "JPG"
#if (MTS_MUXER_EN)
#define SEARCH_MOVIE                        "AVI,MOV,TS"
#else
#define SEARCH_MOVIE                        "AVI,MOV"
#endif
#define SEARCH_PHOTO_MOVIE                  "AVI,MOV,JPG"

#define EXT_DOT                             "."
#define PHOTO_JPG_EXT                       "JPG"
#define MOVIE_3GP_EXT                       "MOV"
#define MOVIE_AVI_EXT                       "AVI"
#define MOVIE_TS_EXT                        "TS"

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef void        (AHC_UF_Callback) (UINT8 *);
typedef AHC_BOOL (*CusGetTotalFileCountCallback)(UINT32 *puiImgIndex);
typedef AHC_BOOL (*CusSetCurrentIndexCallback)(UINT32 uiImgIndex);
typedef AHC_BOOL (*CusGetCurrentIndexCallback)(UINT32 *puiImgIndex);
typedef AHC_BOOL (*CusGetFilePathNamebyIndexCallback)(UINT32 uiIndex, char* FilePathName);
typedef AHC_BOOL (*CusGetFileSizebyIndexCallback)(UINT32 uiIndex, UINT32* FileSize);
typedef AHC_BOOL (*CusGetFileTypebyIndexCallback)(UINT32 uiIndex, UINT8 *FileType);
typedef AHC_BOOL (*CusIsReadOnlybyIndexCallback)(UINT32 uiIndex, AHC_BOOL *bReadOnly);
typedef AHC_BOOL (*CusGetFileTimebyIndexCallback)(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime);
typedef AHC_BOOL (*CusIsCharLockbyIndexCallback)(UINT32 uiIndex, AHC_BOOL *bCharLock);
typedef AHC_BOOL (*CusGetFileNamebyIndexCallback)(UINT32 uiIndex, char* FileName);
typedef AHC_BOOL (*CusMoveFilebyIndexCallback)(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly);
typedef AHC_BOOL (*CusCheckFileCamStatusCallback)(UINT32 uiIndex, UINT8* status);

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _AHC_UFCB_TYPE {
    AHC_UFCB_GET_STORAGE_ALLOCATION_SETTING = 0,
    AHC_UFCB_CREATE_FORMAT_FREE_FILE,
    AHC_UFCB_NODE_OPERATION
} AHC_UFCB_TYPE;   

typedef enum _AHC_UF_CUSINDEXMAPFUNC_TYPE {
    AHC_UFCB_GETTOTALFILECOUNT = 0,
    AHC_UFCB_SETCURRENTINDEX,
    AHC_UFCB_GETCURRENTINDEX,    
    AHC_UFCB_GETFILEPATHNAMEBYINDEX,
    AHC_UFCB_GETFILESIZEBYINDEX,
    AHC_UFCB_GETFILETYPEBYINDEX,
    AHC_UFCB_ISREADONLYBYINDEX,
    AHC_UFCB_GETFILETIMEBYINDEX,
    AHC_UFCB_ISCHARLOCKBYINDEX,
    AHC_UFCB_GETFILENAMEBYINDEX,
    AHC_UFCB_MOVEFILEBYINDEX,
    AHC_UFCB_CHECKFILECAMSTATUS
} AHC_UF_CUSINDEXMAPFUNC_TYPE;

typedef struct _AHC_UF_CUSINDEXMAPFUNC {
    CusGetTotalFileCountCallback       GetTotalFileCount;
    CusSetCurrentIndexCallback         SetCurrentIndex;
    CusGetCurrentIndexCallback         GetCurrentIndex;
    CusGetFilePathNamebyIndexCallback  GetFilePathNamebyIndex;
    CusGetFileSizebyIndexCallback      GetFileSizebyIndex;
    CusGetFileTypebyIndexCallback      GetFileTypebyIndex;
    CusIsReadOnlybyIndexCallback       IsReadOnlybyIndex;
    CusGetFileTimebyIndexCallback      GetFileTimebyIndex;
    CusIsCharLockbyIndexCallback       IsCharLockbyIndex;
    CusGetFileNamebyIndexCallback      GetFileNamebyIndex;
    CusMoveFilebyIndexCallback         MovefilebyIndex;
    CusCheckFileCamStatusCallback      CheckFileCamStatus;
} AHC_UF_CUSINDEXMAPFUNC;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL AHC_UF_MappingFuncRegisterCallBack(UINT32 uiEvent, void *pCallback);
void     AHC_UF_SetRearCamPathFlag(AHC_BOOL bSetRearCam);
void AHC_UF_GetRearCamPathFlag(AHC_BOOL* bGetRearCam);
AHC_BOOL AHC_UF_GetTotalFileCount(UINT32 *puiImgIndex);
AHC_BOOL AHC_UF_SetCurrentIndex(UINT32 uiImgIndex);
AHC_BOOL AHC_UF_GetCurrentIndex(UINT32 *puiImgIndex);
AHC_BOOL AHC_UF_GetIndexbyName(INT8 *pchDirName, INT8 *pchFileName, UINT32 *puiIndex);
AHC_BOOL AHC_UF_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName);
AHC_BOOL AHC_UF_GetFileSizebyIndex(UINT32 uiIndex, UINT32* FileSize);
AHC_BOOL AHC_UF_GetFileSizebyFullName(char* FullFileName, UINT32* FileSize);
AHC_BOOL AHC_UF_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *FileType);
AHC_BOOL AHC_UF_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime);
AHC_BOOL AHC_UF_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly);
AHC_BOOL AHC_UF_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock);
AHC_BOOL AHC_UF_GetDirKeybyIndex(UINT32 uiIndex, UINT16 *DirKey);
AHC_BOOL AHC_UF_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[]);
AHC_BOOL AHC_UF_GetAllowedChar(INT8* pbyChar, UINT32 uiLength);
AHC_BOOL AHC_UF_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable);
AHC_BOOL AHC_UF_GetDBStatus(DCF_DB_TYPE sType);
AHC_BOOL AHC_UF_SelectDB(DCF_DB_TYPE sType);
DCF_DB_TYPE AHC_UF_GetDB(void);
AHC_BOOL AHC_UF_UpdateLastFiles(DCF_DB_TYPE sType);
AHC_BOOL AHC_UF_WriteInfo(void);
AHC_BOOL AHC_UF_SetCyclicDeletedMask(DCF_FILE_PROTECT sType);
AHC_BOOL AHC_UF_GetCyclicDeletedMask(DCF_FILE_PROTECT* sType);
AHC_BOOL AHC_UF_SetFileDeletedMask(DCF_FILE_PROTECT sType);
AHC_BOOL AHC_UF_GetFileDeletedMask(DCF_FILE_PROTECT* sType);
AHC_BOOL AHC_UF_DeleteCyclicFilebySize(UINT64 uiSize);
AHC_BOOL AHC_UF_DeleteFilebyNum(UINT64 uiNum);
AHC_BOOL AHC_UF_FileOperation(UINT8 *pPathName, UINT8 *pFileName, UINT8 byOperation, UINT8 *pDestPath, UINT8 *pDestFileName);
AHC_BOOL AHC_UF_Rename(DCF_DB_TYPE sFromType, AHC_RTC_TIME* psRtcTimeOld, AHC_RTC_TIME* psRtcTimeNew);
AHC_BOOL AHC_UF_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly);
AHC_BOOL AHC_UF_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly);
UINT32   AHC_UF_GetCyclicCluster(DCF_DB_TYPE sDB);
UINT32   AHC_UF_GetFileCluster(DCF_DB_TYPE sDB);
UINT32   AHC_UF_GetClusterTH(DCF_DB_TYPE sDB);
AHC_BOOL AHC_UF_AdjustAllocation(DCF_STORAGE_ALLOC eType);
AHC_BOOL AHC_UF_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status);

AHC_BOOL AHC_UF_MountDB(UINT32 uiMaxMem);
AHC_BOOL AHC_UF_UnmountDB(void);
void     AHC_UF_DumpDB(void);
AHC_BOOL AHC_UF_PreAddFile(UINT16 uwDirKey, INT8 *pchFileName);
AHC_BOOL AHC_UF_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName);
AHC_BOOL AHC_UF_GetName(UINT16 *pDirKey, INT8 *DirName, INT8 *FileName, UINT8 *bCreateNewDir);
AHC_BOOL AHC_UF_GetName2(AHC_RTC_TIME* psRtcTime, INT8 *FileFullPath, INT8 *FileName, UINT8 byCamStatus);
INT8*    AHC_UF_GetRootName(void);
INT8*    AHC_UF_GetRootDirName(void);
AHC_BOOL AHC_UF_AddDir(INT8 *pchDirName);
AHC_BOOL AHC_UF_IsDBMounted(void);
AHC_BOOL AHC_UF_SetParam(AHC_PARAM_ID wParamID,UINT32 Param);
AHC_BOOL AHC_UF_GetParam(AHC_PARAM_ID wParamID,UINT32 *Param);
AHC_BOOL AHC_UF_RegisterCallback(MMP_ULONG ulCBType, void *pCallback); 
UINT32   AHC_UF_GetClusterSize(DCF_DB_TYPE sDB);
AHC_BOOL AHC_UF_GetFileNamebyIndex(UINT32 uiIndex, char* FileName);
AHC_ERR  AHC_UF_CopyFile(INT8* pchSource, INT8* pchDest);
AHC_ERR  AHC_UF_CopyOneCardFiles(AHC_MEDIA_ID sMediaSrcID, AHC_MEDIA_ID sMediaDestID);
AHC_ERR  AHC_UF_CopyFile2(UINT32, UINT32, UINT32*);
void     AHC_UF_CreateDCFDBFolder(void);

UINT64   AHC_UF_GetFileTH(DCF_DB_TYPE sType);
AHC_BOOL AHC_UF_FileOperation_ByIdx(UINT32 ulCurIdx, UINT8 Op, UINT8 *pDestPath, UINT8 *pDestFileName);
void     AHC_UF_InitLockFileTable(void);
void     AHC_UF_UpdateLockFileTable(UINT32 uiIndex,AHC_BOOL *bDeleteFile);
AHC_BOOL AHC_UF_GetInfobyIndex(UINT32 uiIndex, DCF_INFO *Info);
AHC_BOOL AHC_UF_GetAllDBInfobyIndex(UINT32 uiIndex, DCF_INFO *Info);
AHC_BOOL AHC_UF_GetAllDBTotalFileCount(UINT32 *puiImgIndex);
AHC_BOOL AHC_UF_SearchAvailableFileSlot(UINT8 byCamID, char* szFilePathName);
AHC_BOOL AHC_UF_SizeinFile_Update(INT8 *pchFileName);
UINT32 AHC_UF_GetDualEncFileSize(INT8 *pchFileName);
AHC_BOOL AHC_UF_GetFileInfoByVisitNode(DCF_DB_TYPE DBtype, DCF_CAM_ID CamID, DCF_INFO *Info, UINT8 Op);
AHC_BOOL AHC_UF_GetTotalFileCountByDB(DCF_DB_TYPE sDB, UINT32 *puiImgIndex);

AHC_BOOL AHC_UnloadSystemFile(void);
UINT32 AHC_UF_GetCurrentDBFlag(void);

#endif //_AHC_UF_H_
