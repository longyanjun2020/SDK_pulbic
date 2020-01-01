/**
 @file AHC_DCFB.c
 @brief AHC DCF Background Delete File
 @author 
 @version 1.0
*/

#if 0
void __HEADER__(){}
#endif

#include "ahc_dcf.h"
#include "aihc_dcf.h"
#include "ait_utility.h"
#include "os_wrap.h"
#include "mmpf_fs_api.h"
#include "ahc_media.h"
#include "config_fw.h"
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if 0		 
void __VARIABLES__(){}
#endif

#if (FW_DCF_BACKGROUND == 1)
static MMPF_OS_MUTEXID  m_DCFDBMutex;
static MMPF_OS_MUTEXID  m_DCFCyclicMutex;
#endif
#if (FW_DCF_BACKGROUND == 1) || (AHC_DCF_BACKGROUND == 1)
static UINT64 			m_uiiNeededBytes = 0;
#endif
#if (AHC_DCF_BACKGROUND == 1)
extern MMP_FS_FILETIME 	FsOsTime;
#endif///< #if (AHC_DCF_BACKGROUND == 1)

AHC_BOOL bFirstTimeGetFreeSpace;

#if 0		 
void __DCFB_API__(){}
#endif

#if (FW_DCF_BACKGROUND == 1)
/**
@brief	the API of protecting the DB of DCF 

*/
AHC_BOOL AIHC_DCF_LOCKDB(void)
{
	return MMPF_OS_AcquireMutex(m_DCFDBMutex, 0);
}
/**
@brief	the API of protecting the DB of DCF 

*/
AHC_BOOL AIHC_DCF_UNLOCKDB(void)
{
	return MMPF_OS_ReleaseMutex(m_DCFDBMutex);
}

/**
@brief	the API of protecting the PAGE of DCF 

*/

AHC_BOOL AIHC_DCF_LOCKPAGE(void)
{
//	printc("Lock Cyclic\r\n");
	return MMPF_OS_AcquireMutex(m_DCFCyclicMutex, 0);
}

/**
@brief	the API of protecting the PAGE of DCF 

*/

AHC_BOOL AIHC_DCF_UNLOCKPAGE(void)
{
//	printc("UnLock Cyclic\r\n");
	return MMPF_OS_ReleaseMutex(m_DCFCyclicMutex);
}
#endif

#if (AHC_DCF_BACKGROUND == 1)
/**
@brief set the needed space of DCF background delete files

*/
AHC_BOOL AIHC_DCF_SetupNeededSpace(UINT64 uiBytes)
{
	m_uiiNeededBytes = uiBytes;
	
	return AHC_TRUE;
}



#if 0		 
void __FS_WRAP__(){}
#endif
/**
@brief the API likes AHC_FS_SetCreationTime()

*/
AHC_ERR AHC_DCFB_SetCreationTime(void)
{
	AHC_FS_FILETIME		sFileTime;
	UINT32				uiTimeStamp;
    
    MMPC_FS_BBGetRTC((MMPS_FS_FILETIME*)&sFileTime);
    AHC_FileTime2TimeStamp(&sFileTime, &uiTimeStamp);
	FS_TimeStampToFileTime(uiTimeStamp, &FsOsTime);
	
	return AHC_ERR_NONE;
}

/**
@brief the API of getting free space like the AHC_FS_GetFreeSpace()
MMPF_FS_API.c(FS_GET_FREE_SPACE)

*/

AHC_ERR AHC_DCFB_GetFreeSpace(INT8 *bpVolume, UINT32 ulNameSize, UINT64 *ulpFreeBytes)
{
	UINT32	uiError;

	if(bFirstTimeGetFreeSpace == AHC_TRUE){
	
    	uiError = MMPF_FS_GetVolumeFreeSpace(bpVolume, (MMP_ULONG64*)ulpFreeBytes, AHC_TRUE);
    	printc("GetFreeSpace by calculate FAT chain\r\n");
    	
    	if(uiError == 0) {
    	    bFirstTimeGetFreeSpace = AHC_FALSE;
    	}
    }
    else
    {
    	uiError = MMPF_FS_GetVolumeFreeSpace(bpVolume, (MMP_ULONG64*)ulpFreeBytes, AHC_FALSE);
    }
    
	if (uiError) {
    	printc("GetFreeSpace failed.\r\n");
    }
    
    return uiError;

}

/**
@brief the API likes AHC_FS_DirOpen()
MMPF_FS_API.c(FS_DIR_OPEN)

*/

AHC_ERR AHC_DCFB_DirOpen(INT8 *bDirName, UINT32 ulNameSize, UINT32 *ulDirID)
{
	return MMPF_FS_OpenDir(bDirName, ulDirID);

}

/**
@brief the API likes AHC_FS_DirCreate()
MMPF_FS_API.c(FS_DIR_CREATE)

*/

AHC_ERR AHC_DCFB_DirCreate(INT8 *bDirName, UINT32 ulNameSize)
{
	AHC_DCFB_SetCreationTime();
	return MMPF_FS_MkDir(bDirName);
}

/**
@brief the API likes AHC_FS_DirClose()
MMPF_FS_API.c(FS_DIR_CLOSE)

*/

AHC_ERR AHC_DCFB_DirClose(UINT32 ulDirID)
{
	return MMPF_FS_CloseDir(ulDirID);
}

/**
@brief the API likes AHC_FS_DirRemove()
MMPF_FS_API.c(FS_DIR_REMOVE)

*/

AHC_ERR AHC_DCFB_DirRemove(INT8 *bpDirName, UINT32 ulNameSize)
{
	return MMPF_FS_RmDir(bpDirName);
}

/**
@brief the API likes AHC_FS_DirGetNumFiles()
MMPF_FS_API.c(FS_DIR_GETNUMFILES)

*/
AHC_ERR AHC_DCFB_DirGetNumFiles(UINT32 ulDirID, UINT32 *ulFileCount)
{

	return MMPF_FS_GetNumFiles(ulDirID, ulFileCount);
}
/**
@brief the API likes AHC_FS_FileDirGetAttribute()
MMPF_FS_API.c(FS_FILE_DIR_GETATTRIBUTES)

*/
AHC_ERR AHC_DCFB_FileDirGetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute)
{
	return MMPF_FS_GetFileAttributes(bpName, (MMP_UBYTE*)attribute);
}

/**
@brief the API likes AHC_FS_FileDirGetInfo()
MMPF_FS_API.c(FS_FILE_DIR_GETINFO)

*/
AHC_ERR AHC_DCFB_FileDirGetInfo(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE *attribute, AHC_FS_FILETIME *timestructure, UINT32 *ulpFileSize)
{
	AHC_ERR sError;
	UINT32 	uiTimeStamp;
	sError = MMPF_FS_GetFileInfo(bpName, (MMP_UBYTE*)attribute, (MMP_U_LONG*)&uiTimeStamp, (MMP_U_LONG*)ulpFileSize);
	
	if (sError == AHC_ERR_NONE) {
        AHC_TimeStamp2FileTime(uiTimeStamp, timestructure);
    }
    
	return sError;
	
}

/**
@brief the API likes AHC_FS_FileDirGetTime()
MMPF_FS_API.c(FS_FILE_DIR_GETTIME)

*/
AHC_ERR AHC_DCFB_FileDirGetTime(INT8 *bpName, UINT32 ulNameSize, AHC_FS_FILETIME *timestructure)
{
    AHC_ERR sError;
    UINT32 	ulTimeStamp;

	sError = MMPF_FS_GetFileTime(bpName, (MMP_U_LONG*)&ulTimeStamp);	
	
    if (sError == AHC_ERR_NONE) {
        AHC_TimeStamp2FileTime(ulTimeStamp, timestructure);
    }
    
    return sError;
}

/**
@brief the API likes AHC_FS_FileDirRename()
MMPF_FS_API.c(FS_FILE_DIR_RENAME)

*/
AHC_ERR AHC_DCFB_FileDirRename(INT8 *bpOldName, UINT32 ulOldNameSize, INT8 *bpNewName, UINT32 ulNewNameSize)
{

    AHC_ERR sResult;
    UINT32 uiFileId;
    
	sResult = AHC_DCFB_FileOpen(bpNewName, ulNewNameSize, "r", STRLEN("r"), &uiFileId);
	
	if (sResult == AHC_ERR_NONE) {
        AHC_DCFB_FileClose(uiFileId);
        return AHC_FS_ERR_FILE_EXIST;
	}


	sResult = MMPF_FS_Rename(bpOldName, bpNewName);
    if (sResult) {
        printc("FileDirRename failed.\r\n");
    }
    
    return AHC_ERR_NONE;
}
/**
@brief the API likes AHC_FS_FileDirSetAttribute()
MMPF_FS_API.c(FS_FILE_DIR_SETATTRIBUTES)

*/
AHC_ERR AHC_DCFB_FileDirSetAttribute(INT8 *bpName, UINT32 ulNameSize, AHC_FS_ATTRIBUTE attribute)
{
    AHC_ERR sResult;
	sResult = MMPF_FS_SetFileAttributes(bpName, attribute);
	if (sResult) {
		printc("FileDirSetAttributes failed.\r\n");
    }
    MMPF_FS_ClearCache();
    
    return sResult;
}
/**
@brief the API likes AHC_FS_GetFileList()
MMPF_FS_API.c(FS_GET_FILE_LIST)

*/
AHC_ERR AHC_DCFB_GetFileList(	UINT32 ulDirId, 
								UINT8 ubInfoMode, 
								INT8* bBuffer,
                           		AHC_FS_ATTRIBUTE* attribute, 
                           		AHC_FS_FILETIME* filetime, 
                           		UINT32* ulEntrySize)
{
    AHC_ERR			sResult;
	MMP_FS_FILETIME	file_time;
	MMP_U_LONG		time_stamp;


	sResult = MMPF_FS_DirEnt2Info(	ulDirId, 
									ubInfoMode,
									bBuffer, 
									(MMP_UBYTE*)attribute, 
									&file_time, 
									(MMP_ULONG*)ulEntrySize);
	if (sResult) {
        if (sResult == AHC_FS_ERR_NO_MORE_ENTRY) {
	        printc("GetFileList no more entry.\r\n");
        }
        else {
             printc("GetFileList failed.\r\n");
	    }
    }
    else {

        FS_FileTimeToTimeStamp(&file_time, &time_stamp);

	}
	        
	if (sResult ==  AHC_ERR_NONE) {

		AHC_TimeStamp2FileTime(time_stamp, filetime);
    }
    return sResult;

}

/**
@brief the API likes AHC_FS_FileOpen()
MMPF_FS_API.c(FS_FILE_OPEN)

*/

AHC_ERR AHC_DCFB_FileOpen(INT8 *bFileName, UINT32 ulNameSize, INT8 *bMode, UINT32 ulModeSize, UINT32 *ulFileId)
{
	AHC_DCFB_SetCreationTime();
	return MMPF_FS_FOpen(bFileName, bMode, (MMP_ULONG*)ulFileId);
}

/**
@brief the API likes AHC_FS_FileSeek()
MMPF_FS_API.c(FS_FILE_SEEK)
*/
AHC_ERR AHC_DCFB_FileSeek(UINT32 ulFileId, INT64 llOffset, UINT32 ulOrigin)
{
	return MMPF_FS_FSeek(ulFileId, llOffset, ulOrigin);
}

/**
@brief the API likes AHC_FS_FileRead()
MMPF_FS_API.c(FS_FILE_READ)
*/

AHC_ERR AHC_DCFB_FileRead(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulReadCount)
{
	AHC_ERR sResult;
	
    if (ulNumBytes == 0)
        return AHC_FS_ERR_READ_FAIL;

	sResult = MMPF_FS_FRead(ulFileId, ubData, ulNumBytes, ulReadCount);
	if (sResult == MMP_ERR_NONE) {

	}
	else if (sResult == MMP_FS_ERR_EOF) {
		printc("MMP_FS_ERR_EOF.\r\n");
	}
	else {
	    printc("MMPF_FS_FRead() failed.\r\n");
	}
	
	return sResult;
	
}
/**
@brief the API likes AHC_FS_FileWrite()
MMPF_FS_API.c(FS_FILE_WRITE)
*/

AHC_ERR AHC_DCFB_FileWrite(UINT32 ulFileId, UINT8 *ubData, UINT32 ulNumBytes, UINT32 *ulWriteCount)
{
    if (ulNumBytes == 0)
        return MMP_FS_ERR_WRITE_FAIL;

    return MMPF_FS_FWrite(ulFileId, ubData, ulNumBytes, ulWriteCount);
}

/**
@brief the API likes AHC_FS_FileCopy()
MMPF_FS_API.c(FS_FILE_COPY)
*/

AHC_ERR AHC_DCFB_FileCopy(INT8 *bSrc, UINT32 ulSrcSize, INT8 *bDest, UINT32 ulDestSize)
{
	return MMPF_FS_FCopy(bSrc, bDest);
}

/**
@brief the API likes AHC_FS_FileClose()
MMPF_FS_API.c(FS_FILE_CLOSE)
*/

AHC_ERR AHC_DCFB_FileClose(UINT32 ulFileId)
{
	AHC_ERR sResult;
	
	sResult = MMPF_FS_FClose(ulFileId);
	if (sResult) {
		printc("MMPF_FS_FClose() failed.\r\n");
    }
    
	return sResult;
}

/**
@brief the API likes AHC_FS_FileRemove()
MMPF_FS_API.c(FS_FILE_REMOVE)
*/

AHC_ERR AHC_DCFB_FileRemove(INT8 *bpFileName, UINT32 ulNameSize)
{
	AHC_ERR sResult;
	
    sResult = MMPF_FS_Remove(bpFileName);
	if (sResult) {
		printc("FileRemove failed.\r\n");
    }
    
    return sResult;
}

/**
@brief the API likes AHC_FS_FileGetSize()
MMPF_FS_API.c(FS_FILE_GET_SIZE)
*/

AHC_ERR AHC_DCFB_FileGetSize(UINT32 ulFileId, UINT32 *ulFileSize)
{
	return MMPF_FS_GetFileSize(ulFileId, ulFileSize);
}

#endif ///<#if (AHC_DCF_BACKGROUND == 1)

#if 0		 
void __DCF_TASK__(){}
#endif
#if (FW_DCF_BACKGROUND == 1)
void AHC_DCF_Task(void *p_arg)
{
	m_DCFDBMutex = MMPF_OS_CreateMutex(DCFB_MUTEX_DB_PRIO); //reserve OS priority for mutex
	m_DCFCyclicMutex = MMPF_OS_CreateMutex(DCFB_MUTEX_PAGE_PRIO);
	
	while(1)
	{
		if( (AIHC_DCF_IsDBMounted() == AHC_TRUE) && (AIHC_DCF_CheckBackGround() == AHC_TRUE)){

			// Sorting start
			AIHC_DCF_LOCKPAGE();
			if(AIHC_DCF_NeedSort() == AHC_TRUE){
				
				UINT32 uiIndex;
				printc("XX S S XX \r\n");
				if(AIHC_DCF_GetGlodenPageIndex(&uiIndex, AHC_FALSE) == AHC_TRUE){
					AIHC_DCF_SortGoldenPage(uiIndex);
				}
				printc("XX S E XX \r\n");
			
			}///< Sorting end
			AIHC_DCF_UNLOCKPAGE();
			
			{///< background delete files start
			
			UINT64 uiiSize;

			
			AIHC_DCF_DetectFreeStorage(&uiiSize);
			
			if(uiiSize < m_uiiNeededBytes){

				// start delete files
				UINT32 uiFileSize;
				/**
				make sure that the storage is mounted.
				
				*/
				printc("D S \r\n");
				AHC_DCF_DeleteCyclicFile(&uiFileSize);
				printc("D E \r\n");
				
			}
			
			}///< background delete files end
		}
		//SetKeyPadEvent(92);
		MMPF_OS_Sleep(DCFB_TASK_SLEEP_PERIOD);
		
	}

}

#endif ///< #if (FW_DCF_BACKGROUND == 1)