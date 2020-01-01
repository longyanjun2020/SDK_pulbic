//==============================================================================
//
//  File        : ahc_dcf.h
//  Description : INCLUDE File for the AHC DCF function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_DCF_H_
#define _AHC_DCF_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define DCF_MAX_FILE_NAME_SIZE		64//MAX_FULL_FILENAME_SIZE

/**
@brief	the dcfx region depends on the total space of media. unit: %.
*/
#define DCFX_REGION_2G				(50)	///< 50%
#define DCFX_REGION_4G				(50)	///< 50%
#define DCFX_REGION_8G				(50)	///< 50%
#define DCFX_REGION_16G				(50)	///< 50%
#define DCFX_REGION_32G				(50)	///< 50%
#define DCFX_REGION_64G				(50)	///< 50%
#define DCFX_REGION_128G			(50)	///< 50%

#define DCF_GOLDEN_PAGE_NUMBER		(2)

#define MIN_DCF_DIR_KEYNUM          (100)
#define MAX_DCF_DIR_KEYNUM          (999)

#define MIN_DCF_FILE_KEYNUM         (1)
#define MAX_DCF_FILE_KEYNUM         (9999)

#define MAX_DCF_DIR_NUM				(MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1)
#define MAX_DCF_FILE_NUM			(500)

#define FILE_EXT_LENGTH             (3) ///< the length of file extension 
//define MAX DIR FILE FREECHAR LENGTH and NUMBER
#define MAX_FILE_FREE_CHAR_NUMBER   (12) ///< the number of free char for file
#define MAX_FILE_CHAR_LENGTH        (16) ///< the length of file name
#define MAX_DIR_FREE_CHAR_NUMBER    (13) ///< the number of free char for dir
#define MAX_DIR_CHAR_LENGTH         (16) ///< the length of dir name

#define DCF_DEBUG_DIS				(0)
#define DCF_DEBUG_ERR				(1)
#define DCF_DEBUG_ALL				(2)
#define DCF_DEBUG					(DCF_DEBUG_ERR)

#define DCF_SUB_FILE_MAX_COUNT      (10)

#define DCF_SEACH_CACHE_SLOT_COUNT  (100)
#define DCF_SEACH_CACHE_SLOT_SIZE   (8)
//define number of getinfo cache
#define DCF_GETINFO_CACHE_COUNT     (12)

#ifndef DCF_CHARLOCK_PATTERN        // Maybe defined in AHC_Config_SDK.h
#define DCF_CHARLOCK_PATTERN        "MOVG"
#endif

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _FILE_ATTRI{
    char    FileName[MAX_FULL_FILENAME_SIZE];
    UINT16  uwAttrib;
    UINT32  ulFileSize; // maybe UINT64
    UINT16  uwYear;
	UINT16  uwMonth;
	UINT16  uwDay;
	UINT16  uwHour;
	UINT16  uwMinute;
	UINT16  uwSecond;
} FILE_ATTRI;

typedef struct _DCF_DB_ATTRIB{
    UINT32 uiFileCount;
    UINT16 uiDirCount;
    UINT16 uwDirKeyList[MAX_DCF_DIR_KEYNUM - MIN_DCF_DIR_KEYNUM + 1];
} DCF_DB_ATTRIB;

typedef struct _DCF_INFO{
	UINT32  uiFileSize;
    UINT16  uwDirKey;
    UINT16  uwFileKey;
    UINT8   DirFreeChar[MAX_DIR_CHAR_LENGTH + 1];
    UINT8   FileFreeChar[MAX_FILE_CHAR_LENGTH + 1];
    
    UINT8   FileType;///< DCF_OBG
    char    FileName[MAX_FULL_FILENAME_SIZE];
    char    FilePath[MAX_FULL_FILENAME_SIZE];
	
    UINT16  uwYear;
	UINT16  uwMonth;
	UINT16  uwDay;
	UINT16  uwHour;
	UINT16  uwMinute;
	UINT16  uwSecond;
	/**
	@brief	the file attribute of read only.
	*/
	AHC_BOOL   bReadOnly;
	/**
	@brief	the file with the locked file name.
	@brief	DCF_SET_LOCKED_FREECHAR
	*/
	AHC_BOOL   bCharLock;
    AHC_BOOL   bIsFileDownload;
} DCF_INFO;

typedef struct _DCF_KEY_PAIR{
	UINT16 uwDirKey;
	UINT16 uwFileKey;
}DCF_KEY_PAIR;

typedef struct _DCF_INFO_CACHE{
    UINT32    uiIndexPlus;
    DCF_INFO  Info;
}DCF_INFO_CACHE;

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _DCF_DB_TYPE {
    DCF_DB_TYPE_DB0_NORMAL = 0,
    DCF_DB_TYPE_DB1_PARKING = 1,
    DCF_DB_TYPE_DB2_EVENT = 2,
    DCF_DB_TYPE_DB3_PHOTO = 3,
    DCF_DB_TYPE_DB4_SHARE = 4,
    DCF_DB_TYPE_MAX_NUMBER,
    DCF_DB_TYPE_SUB_DB////< EMER
} DCF_DB_TYPE;

typedef enum _DCF_FILE_PROTECT
{
	DCF_FILE_PROTECT_NONE     = 0x00,
	DCF_FILE_PROTECT_CHARLOCK = 0x01,
	DCF_FILE_PROTECT_READONLY = 0x02,
	DCF_FILE_PROTECT_TIME     = 0x04,
	DCF_FILE_PROTECT_NONLOCK  = 0x10

}DCF_FILE_PROTECT;

typedef enum _DCF_OBG{
    DCF_OBG_JPG = 0,
    DCF_OBG_TIF,
    DCF_OBG_AVI,
    DCF_OBG_MOV,
    DCF_OBG_MP4,
    DCF_OBG_3GP,
    DCF_OBG_WMV,
    DCF_OBG_MP3,
    DCF_OBG_OGG,
    DCF_OBG_WMA,
    DCF_OBG_WAV,
    DCF_OBG_ASF,
    DCF_OBG_THM,
    DCF_OBG_RAW,
	DCF_OBG_AAC,
    DCF_OBG_TS,
	
    DCF_OBG_MAX
} DCF_OBG;

typedef enum _DCF_OP{

    //GET_DCFDIR_MAX_DIR_KEY		= 0,
    //GET_DCFDIR_MAX_FILE_KEY,
    //DCF_OPEN_EXIST,
	//DCF_CREATE             = 2,
    DCF_SET_FREECHAR			= 0x04,
    DCF_SET_ALLOWED				= 0x08,	///< the allowed file type.
    /**
    @brief	setup the special file free char of file name.
    		the bNameLock of the the DCF_INFO is true when the free char of file name is like this setting.
    */
    DCF_SET_LOCKED_CHAR			= 0x10,
    DCF_SET_UNLOCKED_CHAR		= 0x20,
    /**
    @brief	the attribute of read only
    
    */
    DCF_FILE_READ_ONLY,
    DCF_FILE_NON_READ_ONLY,
    DCF_FILE_READ_ONLY_ALL_CAM,
    DCF_FILE_NON_READ_ONLY_ALL_CAM,
    
    DCF_FILE_CHAR_LOCK,
    DCF_FILE_CHAR_UNLOCK,
    DCF_FILE_CHAR_LOCK_ALL_CAM,
    DCF_FILE_CHAR_UNLOCK_ALL_CAM,
    DCF_FILE_MOVE_SUBDB,
    
    DCF_FILE_COPY,
    DCF_FILE_DELETE_ALL_CAM,
    DCF_FILE_DELETE_SUB_CAM,
    DCF_FILE_RENAME,
    DCF_FILE_DOWNLOADDONE,
    DCF_FILE_NONDOWNLOAD,
    DCF_SETMODE_CONTISHOT2P,
    DCF_SETMODE_CONTISHOT3P,
    DCF_SETMODE_CONTISHOT5P,
    DCF_SETMODE_SINGLEMODE
} DCF_OP;


typedef enum _DCF_STORAGE_ALLOC
{
    DCF_STORAGE_ALLOC_TYPE0,
    DCF_STORAGE_ALLOC_TYPE1,
    DCF_STORAGE_ALLOC_TYPE2,
    DCF_STORAGE_ALLOC_TYPE3

}DCF_STORAGE_ALLOC;

//enum of cam ID
typedef enum{
    DCF_CAM_FRONT,
    DCF_CAM_REAR,
    DCF_CAM_MAX
} DCF_CAM_ID;

//enum of cam ID bitwise
typedef enum{
    DCF_CAM_EXIST_BASE  = 0x01,
    DCF_CAM_FRONT_EXIST = 0x01,
    DCF_CAM_REAR_EXIST  = 0x02
} DCF_CAM_EXIST_MASK;

typedef enum{
    DCF_NODE_VISIT_NODEHEAD,
    DCF_NODE_VISIT_FORWARD,  
    DCF_NODE_VISIT_NODETAIL,
    DCF_NODE_VISIT_REWIND
}DCF_NODE_VISIT_OP;

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL AHC_DCF_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable);
AHC_BOOL AHC_DCF_GetDBStatus(DCF_DB_TYPE sType);
AHC_BOOL AHC_DCF_SelectDB(DCF_DB_TYPE sType);
DCF_DB_TYPE AHC_DCF_GetDB(void);
AHC_BOOL AHC_DCF_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[]);
AHC_BOOL AHC_DCF_GetAllowedChar(INT8* pbyChar, UINT32 uiLength);
AHC_BOOL AHC_DCF_SwitchKey(UINT16 uwDirKey);
AHC_BOOL AHC_DCF_GetTotalFileCount(UINT32 *puiImgIndex);
AHC_BOOL AHC_DCF_SetCurrentIndex(UINT32 uiImgIndex);
AHC_BOOL AHC_DCF_GetCurrentIndex(UINT32 *puiImgIndex);
AHC_BOOL AHC_DCF_GetInfobyIndex(UINT32 uiIndex, DCF_INFO *Info);
AHC_BOOL AHC_DCF_GetDBInfo(DCF_DB_ATTRIB *pDcfAttrib);
AHC_BOOL AHC_DCF_SetCyclicDeletedMask(DCF_FILE_PROTECT sType);
AHC_BOOL AHC_DCF_GetCyclicDeletedMask(DCF_FILE_PROTECT* sType);
AHC_BOOL AHC_DCF_SetFileDeletedMask(DCF_FILE_PROTECT sType);
AHC_BOOL AHC_DCF_GetFileDeletedMask(DCF_FILE_PROTECT* sType);
AHC_BOOL AHC_DCF_DeleteCyclicFile(UINT32* uiSize);
AHC_BOOL AHC_DCF_DeleteCyclicFilebySize(UINT64 uiSize);
AHC_BOOL AHC_DCF_FileOperation(UINT8 *pPathName, UINT8 *pFileName, UINT8 byOperation, UINT8 *pDestPath, UINT8 *pDestFileName);
AHC_BOOL AHC_DCF_WriteInfo(void);
void 	 AHC_SetFindLockFileOnlyFlag(AHC_BOOL bEn);

AHC_BOOL AHC_DCF_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly);
UINT32   AHC_DCF_GetCyclicCluster(DCF_DB_TYPE sDB);
UINT32   AHC_DCF_GetReadOnlyCluster(DCF_DB_TYPE sDB);
UINT32   AHC_DCF_GetFileCluster(DCF_DB_TYPE sDB);
UINT32   AHC_DCF_GetTotalCluster(void);
UINT32   AHC_DCF_GetClusterSize(void);
UINT32   AHC_DCF_GetClusterTH(DCF_DB_TYPE sDB);
AHC_BOOL AHC_DCF_AdjustAllocation(DCF_STORAGE_ALLOC eType);
void AHC_DCF_DBInitFreeCharLength(UINT32 uiDBIndex,INT8* pchDirFreeChar,INT8* pchFileFreeChar);
AHC_BOOL AHC_DCF_GetIndexbyName(	INT8 *pchDirName, INT8 *pchFileName, UINT32 *puiIndex);
void     AIHC_GetTempDCFMemStartAddr(UINT32 *addr); 
AHC_BOOL AHC_DCF_RegisterCallback(MMP_ULONG ulCBType, void *pCallback);

AHC_BOOL AIHC_DCF_GetInfo(UINT32 uiIndex, DCF_INFO *Info);
void AHC_DCF_InitLockFileTable(void);
void AHC_DCF_UpdateLockFileTable(UINT16    uwDirKey,
                                 UINT16    uwFileKey,
                                 UINT8     byFileType,
                                 AHC_BOOL *bDeleteFile);
AHC_BOOL AHC_DCF_GetInfoFromCache(UINT32 uiIndex, DCF_INFO *Info);
#endif
