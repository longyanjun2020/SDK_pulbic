//==============================================================================
//
//  File        : aihc_dcf.h
//  Description : INCLUDE File for the AHC DCF function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AIHC_DCF_H_
#define _AIHC_DCF_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_dcf.h"
#include "ahc_parameter.h"
#include "ahc_fs.h"
#include "AHC_Config_SDK.h"

/*===========================================================================
 * Marco define
 *===========================================================================*/

#if (FW_DCF_BACKGROUND == 1)
#define DCFB_MUTEX_DB_PRIO		(24)
#define DCFB_MUTEX_PAGE_PRIO	(25)
#define DCFB_TASK_SLEEP_PERIOD	(300)
#endif 

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _DCFX_GOLDEN_PAGE_BUFFER
{
	UINT8*		pbyBuffer;
	AHC_BOOL	bFilled;///< the page is sorted or not.
	AHC_BOOL	bLock;

}DCFX_GOLDEN_PAGE_BUFFER;

typedef struct _DCFX_DB_PAGE{
	
	UINT32	uiPageID;			///< 4 bytes, It the Page ID and it also the position in the storage.
	UINT32	uiFirstItem;		///< 4 bytes.
	UINT32	uiLastItem;			///< 4 bytes.
	UINT32	uiUsedBufferOffset;	///< 4 bytes.
	UINT32	uiModified;			///< 4 bytes.
	
}DCFX_DB_PAGE;

typedef struct _DCFX_PAGE_CTL{

	UINT32	uiPageIndex;		///< 4 bytes.
	
	UINT32	uiPageTotalCount;	///< 4 bytes. the total number of page.
	
	UINT32	uiSortTotalCount;	///< 4 bytes. the total count of sorted page.
	
	UINT32	uiWritedPageCount;	///< 4 bytes.

}DCFX_PAGE_CTL;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL AIHC_DCF_LOCKDB(void);
AHC_BOOL AIHC_DCF_UNLOCKDB(void);
AHC_BOOL AIHC_DCF_LOCKPAGE(void);
AHC_BOOL AIHC_DCF_UNLOCKPAGE(void);

AHC_ERR AHC_DCF_GetFreeSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpFreeBytes);

AHC_ERR AHC_DCF_DirOpen(INT8 *bDirName, UINT32 ulNameSize, UINT32 *ulDirID);
AHC_ERR AHC_DCF_DirCreate(INT8 *bDirName, UINT32 ulNameSize);
AHC_ERR AHC_DCF_DirClose(UINT32 ulDirID);
AHC_ERR AHC_DCF_DirRemove(INT8 *bpDirName, UINT32 ulNameSize);
AHC_ERR AHC_DCF_DirGetNumFiles(UINT32 ulDirID, UINT32 *ulFileCount);
AHC_ERR AHC_DCF_FileDirGetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute);
AHC_ERR AHC_DCF_FileDirGetInfo(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME *timestructure, UINT32 *ulpFileSize);
AHC_ERR AHC_DCF_FileDirGetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME *timestructure);
AHC_ERR AHC_DCF_FileDirMove(INT8 *bpNameSrc, UINT32 ulSrcSize, INT8 *bpNameDest, UINT32 ulDestSize);
AHC_ERR AHC_DCF_FileDirRename(INT8 *bpOldName, UINT32 ulOldNameSize, INT8 *bpNewName, UINT32 ulNewNameSize);
AHC_ERR AHC_DCF_FileDirSetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE attribute);
AHC_ERR AHC_DCF_GetFileList(UINT32 ulDirId, UINT8 ubInfoMode, INT8* bBuffer,
                           AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME* filetime, UINT32* ulEntrySize);
AHC_ERR AHC_DCF_FileOpen(INT8 *bFileName, UINT32 ulNameSize, INT8 *bMode, UINT32 ulModeSize, UINT32 *ulFileId);
AHC_ERR AHC_DCF_FileSeek(UINT32 ulFileId, INT64 llOffset, UINT32 ulOrigin);
AHC_ERR AHC_DCF_FileRead(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulReadCount);
AHC_ERR AHC_DCF_FileWrite(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulWriteCount);
AHC_ERR AHC_DCF_FileCopy(INT8 *bSrc, UINT32 ulSrcSize, INT8 *bDest, UINT32 ulDestSize);
AHC_ERR AHC_DCF_FileClose(UINT32 ulFileId);
AHC_ERR AHC_DCF_FileRemove(INT8 *bpFileName, UINT32 ulNameSize);
AHC_ERR AHC_DCF_FileGetSize(UINT32 ulFileId, UINT32 *ulFileSize);

#if (AHC_DCF_BACKGROUND == 0)
#define AHC_DCF_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes) AHC_FS_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes)
#define AHC_DCF_DirOpen(bDirName, ulNameSize, ulDirID)	AHC_FS_DirOpen(bDirName, ulNameSize, ulDirID)
#define AHC_DCF_DirCreate(bDirName, ulNameSize)			AHC_FS_DirCreate(bDirName, ulNameSize)
#define AHC_DCF_DirClose(ulDirID)						AHC_FS_DirClose(ulDirID)
#define AHC_DCF_DirRemove(bpDirName, ulNameSize)		AHC_FS_DirRemove(bpDirName, ulNameSize)
#define AHC_DCF_DirGetNumFiles(ulDirID, ulFileCount)	AHC_FS_DirGetNumFiles(ulDirID, ulFileCount)
#define AHC_DCF_FileDirGetAttribute(bpName, ulNameSize, attribute)					AHC_FS_FileDirGetAttribute(bpName, ulNameSize, attribute)
#define AHC_DCF_FileDirGetInfo(bpName, ulNameSize, attribute, timestructure, ulpFileSize)	AHC_FS_FileDirGetInfo(bpName, ulNameSize, attribute, timestructure, ulpFileSize)
#define AHC_DCF_FileDirGetTime(bpName, ulNameSize, timestructure)					AHC_FS_FileDirGetTime(bpName, ulNameSize, timestructure)
#define AHC_DCF_FileDirMove(bpNameSrc, ulSrcSize, bpNameDest, ulDestSize)           AHC_FS_FileDirMove(bpNameSrc, ulSrcSize, bpNameDest, ulDestSize)
#define AHC_DCF_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize)	AHC_FS_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize)
#define AHC_DCF_FileDirSetAttribute(bpName, ulNameSize, attribute) AHC_FS_FileDirSetAttribute(bpName, ulNameSize, attribute)
#define AHC_DCF_GetFileList(ulDirId, ubInfoMode, bBuffer, attribute, filetime, ulEntrySize) AHC_FS_GetFileList(ulDirId, ubInfoMode, bBuffer, attribute, filetime, ulEntrySize)
#define AHC_DCF_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId)		AHC_FS_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId)
#define AHC_DCF_FileSeek(ulFileId, llOffset, ulOrigin)					AHC_FS_FileSeek( ulFileId, llOffset, ulOrigin)
#define AHC_DCF_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount)		AHC_FS_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount)
#define AHC_DCF_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount)	AHC_FS_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount)
#define AHC_DCF_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize)			AHC_FS_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize)
#define	AHC_DCF_FileClose(ulFileId)										AHC_FS_FileClose(ulFileId)
#define AHC_DCF_FileRemove(bpFileName, ulNameSize)						AHC_FS_FileRemove(bpFileName, ulNameSize)
#define AHC_DCF_FileGetSize(ulFileId, ulFileSize) 						AHC_FS_FileGetSize(ulFileId, ulFileSize)

#else ///<(AHC_DCF_BACKGROUND == 0)

AHC_ERR AHC_DCFB_SetCreationTime(void);
AHC_ERR AHC_DCFB_GetFreeSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpFreeBytes);
AHC_ERR AHC_DCFB_DirOpen(INT8 *bDirName, UINT32 ulNameSize, UINT32 *ulDirID);
AHC_ERR AHC_DCFB_DirCreate(INT8 *bDirName, UINT32 ulNameSize);
AHC_ERR AHC_DCFB_DirClose(UINT32 ulDirID);
AHC_ERR AHC_DCFB_DirRemove(INT8 *bpDirName, UINT32 ulNameSize);
AHC_ERR AHC_DCFB_DirGetNumFiles(UINT32 ulDirID, UINT32 *ulFileCount);
AHC_ERR AHC_DCFB_FileDirGetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute);
AHC_ERR AHC_DCFB_FileDirGetInfo(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME *timestructure, UINT32 *ulpFileSize);
AHC_ERR AHC_DCFB_FileDirGetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME *timestructure);
AHC_ERR AHC_DCFB_FileDirRename(INT8 *bpOldName, UINT32 ulOldNameSize, INT8 *bpNewName, UINT32 ulNewNameSize);
AHC_ERR AHC_DCFB_FileDirSetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE attribute);
AHC_ERR AHC_DCFB_GetFileList(UINT32 ulDirId, UINT8 ubInfoMode, INT8* bBuffer,
                           AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME* filetime, UINT32* ulEntrySize);
AHC_ERR AHC_DCFB_FileOpen(INT8 *bFileName, UINT32 ulNameSize, INT8 *bMode, UINT32 ulModeSize, UINT32 *ulFileId);
AHC_ERR AHC_DCFB_FileSeek(UINT32 ulFileId, INT64 llOffset, UINT32 ulOrigin);
AHC_ERR AHC_DCFB_FileRead(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulReadCount);
AHC_ERR AHC_DCFB_FileWrite(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulWriteCount);
AHC_ERR AHC_DCFB_FileCopy(INT8 *bSrc, UINT32 ulSrcSize, INT8 *bDest, UINT32 ulDestSize);
AHC_ERR AHC_DCFB_FileClose(UINT32 ulFileId);
AHC_ERR AHC_DCFB_FileRemove(INT8 *bpFileName, UINT32 ulNameSize);
AHC_ERR AHC_DCFB_FileGetSize(UINT32 ulFileId, UINT32 *ulFileSize);

#define AHC_DCF_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes) AHC_DCFB_GetFreeSpace(bpVolume, ulNameSize, ulpFreeBytes)
#define AHC_DCF_DirOpen(bDirName, ulNameSize, ulDirID)	AHC_DCFB_DirOpen(bDirName, ulNameSize, ulDirID)
#define AHC_DCF_DirCreate(bDirName, ulNameSize)			AHC_DCFB_DirCreate(bDirName, ulNameSize)
#define AHC_DCF_DirClose(ulDirID)						AHC_DCFB_DirClose(ulDirID)
#define AHC_DCF_DirRemove(bpDirName, ulNameSize)		AHC_DCFB_DirRemove(bpDirName, ulNameSize)
#define AHC_DCF_DirGetNumFiles(ulDirID, ulFileCount)	AHC_DCFB_DirGetNumFiles(ulDirID, ulFileCount)
#define AHC_DCF_FileDirGetAttribute(bpName, ulNameSize, attribute)					AHC_DCFB_FileDirGetAttribute(bpName, ulNameSize, attribute)
#define AHC_DCF_FileDirGetInfo(bpName, ulNameSize, attribute, timestructure, ulpFileSize)	AHC_DCFB_FileDirGetInfo(bpName, ulNameSize, attribute, timestructure, ulpFileSize)
#define AHC_DCF_FileDirGetTime(bpName, ulNameSize, timestructure)					AHC_DCFB_FileDirGetTime(bpName, ulNameSize, timestructure)
#define AHC_DCF_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize)	AHC_DCFB_FileDirRename(bpOldName, ulOldNameSize, bpNewName, ulNewNameSize)
#define AHC_DCF_FileDirSetAttribute(bpName, ulNameSize, attribute) AHC_DCFB_FileDirSetAttribute(bpName, ulNameSize, attribute)
#define AHC_DCF_GetFileList(ulDirId, ubInfoMode, bBuffer, attribute, filetime, ulEntrySize) AHC_DCFB_GetFileList(ulDirId, ubInfoMode, bBuffer, attribute, filetime, ulEntrySize)
#define AHC_DCF_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId)		AHC_DCFB_FileOpen(bFileName, ulNameSize, bMode, ulModeSize, ulFileId)
#define AHC_DCF_FileSeek(ulFileId, llOffset, ulOrigin)					AHC_DCFB_FileSeek( ulFileId, llOffset, ulOrigin)
#define AHC_DCF_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount)		AHC_DCFB_FileRead(ulFileId, ubData, ulNumBytes, ulReadCount)
#define AHC_DCF_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount)	AHC_DCFB_FileWrite(ulFileId, ubData, ulNumBytes, ulWriteCount)
#define AHC_DCF_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize)			AHC_DCFB_FileCopy(bSrc, ulSrcSize, bDest, ulDestSize)
#define	AHC_DCF_FileClose(ulFileId)										AHC_DCFB_FileClose(ulFileId)
#define AHC_DCF_FileRemove(bpFileName, ulNameSize)						AHC_DCFB_FileRemove(bpFileName, ulNameSize)
#define AHC_DCF_FileGetSize(ulFileId, ulFileSize) 						AHC_DCFB_FileGetSize(ulFileId, ulFileSize)

#endif	///<(AHC_DCF_BACKGROUND == 0)

AHC_BOOL AIHC_DCF_NeedSort(void);
AHC_BOOL AIHC_DCF_DetectFreeStorage(UINT64* uiiSize);
AHC_BOOL AIHC_DcfMountDB(UINT32 uiMaxMem);
AHC_BOOL AIHC_DcfUnMountDB(void);
AHC_BOOL AIHC_DCF_GetName(UINT16 *pDirKey, INT8 *DirName, INT8 *FileName, UINT8 *bCreateNewDir);
AHC_BOOL AIHC_DCF_RemoveDir(UINT16 DirKey, INT8 *DirName);
AHC_BOOL AIHC_DCF_RemoveFile(UINT16 DirKey, UINT16 FileKey,INT8 *FileName);
AHC_BOOL AIHC_DCF_AddDir(INT8 *DirName);
AHC_BOOL AIHC_DCF_PreAddFile(UINT16 DirIndex,INT8 *FileName);
AHC_BOOL AIHC_DCF_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName);

void AIHC_DCF_DumpDCFxPage(UINT32 uiPageID);
void AIHC_DCF_DumpDCFxPage2(UINT32 uiIndex);
void AIHC_DCF_DumpDB(void);

AHC_BOOL AIHC_DCF_GetParam(AHC_PARAM_ID wParamID,UINT32 *Param);
AHC_BOOL AIHC_DCF_SetParam(AHC_PARAM_ID wParamID,UINT32 Param);
INT8*    AIHC_DCF_GetRootName(void);
AHC_BOOL AIHC_DCF_IsDBMounted(void);

AHC_BOOL AIHC_DCF_GetGlodenPageIndex(UINT32* uiIndex, AHC_BOOL bFilled);
AHC_BOOL AIHC_DCF_SortGoldenPage(UINT32 uiIndex);


typedef void PFuncDCFMountCallBack(	INT8*				pchFileName, 
									INT8* 				pchFileFreeChar, 
									UINT16 				uwFileKey, 
									DCF_OBG 			sFileType, 
									AHC_FS_ATTRIBUTE* 	psFileAttribute, 
									AHC_FS_FILETIME*	psFileTime, 
									UINT32 				uiFileSize);
										
void AIHC_DCF_SetMountCallBack(PFuncDCFMountCallBack* pCallBack);

AHC_BOOL AIHC_DCF_MountSubDB(INT8*  pchRootDirName);
AHC_BOOL AIHC_DCF_UnMountSubDB(void);
AHC_BOOL AIHC_DCF_SetupNeededSpace(UINT64 uiBytes);
#endif