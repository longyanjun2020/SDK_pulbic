//==============================================================================
//
//  File        : AHC_DCFDT.c
//  Description : INCLUDE File for the AHC DCF function porting.
//  Author      : Caesar Chang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_DCFDT_H_
#define _AHC_DCFDT_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"
#include "ahc_os.h"
#include "ahc_dcf.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
// AHC_DCF_TEMP_BASE_ADDR
#define AHC_DTDCF_MEM_START     AHC_DCF_TEMP_BASE_ADDR //0x4C00000 //0x4E00000

#define SECONDS_PER_DAY         (24*60*60)
#define SECONDS_PER_HOUR        (60*60)
#define SECONDS_PER_MIN         (60)
#define DCFDT_UNKNOW_TYPE       (0xFF)

#define DCFDT_FILENAME_YEAR_OFFSET      (2000)
#define DCFDT_DEBUG                     0
    
#define DCF_DB_FORMAT_FREE_DB           (DCF_DB_TYPE_DB4_SHARE)

//define FileAttr Mask
#define DCFDT_FILEATTR_READONLY  (0x01 << 0)
#define DCFDT_FILEATTR_HIDDEN    (0x01 << 1)
#define DCFDT_FILEATTR_CHARLOCK  (0x01 << 2)
#define DCFDT_FILEATTR_ISDOWNLOAD (0x01 << 3)

#define DCFDT_FILEINDEX_MAXNUM      (999999)
#define DCFDT_FILEINDEX_START       (1)
#define DCFDT_FILEINDEX_MASTERCAMID (DCF_CAM_FRONT) //only master Cam can control File Index
#define DCFDT_Illegal_FREECHAR   "Illegal"
#define DCFDT_FILEINDEX_INVALID     (0xFFFFFFFF)
#define DCFDT_CONTISHOT_MAX_NUM  (10)

#if (GPS_RAW_FILE_ENABLE == 1)
#define DCFDT_DB0_FLAG                      (DCFDT_DB_FLAG_COUNT_PAYLOAD_INTO_TH|DCFDT_DB_FLAG_HAS_NMEA_FILE)
#define DCFDT_DB1_FLAG                      (DCFDT_DB_FLAG_HAS_NMEA_FILE)
#define DCFDT_DB2_FLAG                      (DCFDT_DB_FLAG_HAS_NMEA_FILE)
#define DCFDT_DB3_FLAG                      0
#define DCFDT_DB4_FLAG                      0
#else
#define DCFDT_DB0_FLAG                      DCFDT_DB_FLAG_COUNT_PAYLOAD_INTO_TH
#define DCFDT_DB1_FLAG                      0
#define DCFDT_DB2_FLAG                      0
#define DCFDT_DB3_FLAG                      0
#define DCFDT_DB4_FLAG                      0
#endif

#define _T(X)       X

#define DCFDT_DELETE_OLD_DUPLICATE          1

/*===========================================================================
 * Enum define
 *===========================================================================*/

//enum of Flag
typedef enum{
  DCFDT_DB_FLAG_COUNT_PAYLOAD_INTO_TH = 0x01,
  DCFDT_DB_FLAG_HAS_NMEA_FILE         = 0x02,
  DCFDT_DB_FLAG_HAS_REAR_CAM          = 0x04
} DCF_DB_FLAG;

//enum of node operation
typedef enum{
  DCFDT_NODE_INSERT,
  DCFDT_NODE_DELETE_SUB,
  DCFDT_NODE_DELETE_PARENT,
  DCDFT_NODE_UPDATE
} DCFDT_NODE_OPERATION;

//enum of node delte operation
typedef enum{
  DCFDT_DELETE_SUB,
  DCFDT_DELETE_PARENT  
} DCFDT_DELETE_MODE; 

//enum of statistics operation
typedef enum{
  DCFDT_STATISTICS_ADD,
  DCFDT_STATISTICS_DELETE,
  DCFDT_STATISTICS_RESET,
  DCFDT_STATISTICS_READONLY,
  DCFDT_STATISTICS_NON_READONLY,
  DCFDT_STATISTICS_UPDATE
} DCFDT_STATISTICS_OPERATION;

//enum of locktable operation
typedef enum{
  DCFDT_LOCKTABLE_LOCK,
  DCFDT_LOCKTABLE_UNLOCK
} DCFDT_LOCKTABLE_OP;

//timeformat of filename
typedef enum{
    DCFDT_TIMEFORMAT_TYPE0  //e.g. 160316-181355 , year month day - hour min sec
} DCFDT_TIMEFORMAT;

//if add more media num, add DCFDT_SD_NUM and define ROOTNAME
typedef enum{
  DCFDT_SD_CARD0,
  DCFDT_SD_CARD1
} DCFDT_SD_CARD_ID;

//File Index Ctrl Operation
typedef enum{
  DCFDT_INDEX_CTL_UPDATE_DELINDEX,
  DCFDT_INDEX_CTL_UPDATE_ADDINDEX,
  DCFDT_INDEX_CTL_SET_DELINDEX,
  DCFDT_INDEX_CTL_SET_ADDINDEX,
  DCFDT_INDEX_CTL_GET_DELINDEX,
  DCFDT_INDEX_CTL_GET_ADDINDEX,
  DCFDT_INDEX_CTL_RESET_ALL_INDEX,
  DCFDT_INDEX_CTL_MAX
} DCFDT_FILE_INDEX_CTL;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef unsigned int DATE_TIME;
//File Name Data
typedef struct sFILENAME_INFO{
    DATE_TIME  nDateTime;
    UINT32     uiFileIndex;
} SFILENAME_INFO;

//sub node struct 
typedef struct sSUBNODE{
    struct sSUBNODE* pNext;
    UINT8 byFileType;
    UINT8 byFileAttr;
    UINT32 nSizeInCluster;
    UINT8 byCamID;
} SSUBNODE, *PSSUBNODE;

//parent node struct
typedef struct sDATETIMEFILE{
    struct sDATETIMEFILE* pPrev;
    struct sDATETIMEFILE* pNext;
    PSSUBNODE pCamNodeHead;
    SFILENAME_INFO FileNameInfo;
    UINT8 byCamExist;
} SDATETIMEFILE,*PSDATETIMEFILE;

//define init Cam path config
typedef struct sDB_PATH_CONFIG{
    char* szCamFolder;
    char* szFileFreeChar;
    char* szFileFixedChar;
} SDB_PATH_CONFIG;

//define init DB attr config
typedef struct sDB_DBATTR_CONFIG{
    char* szCommonFolder;
    UINT8 byFolderLevel;
    UINT8 byNamingType;
    UINT8 byTimeFormat;
    UINT8 byFlag;
    SDB_PATH_CONFIG sPathConfig[DCF_CAM_MAX];
} SDB_DBATTR_CONFIG;

//define init DB config
typedef struct sDBINIT_CONFIG{
    UINT8      bySDCount;
    UINT8      byDBCount;
    UINT8      byCamNum;
    char*      szRootName[DCFDT_SD_NUM];
    SDB_DBATTR_CONFIG sDBAttrConfig[DCF_DB_TYPE_MAX_NUMBER];
} SDBINIT_CONFIG, *PSDBINIT_CONFIG;

//File Index Struct
typedef struct sFILE_INDEX_STRUCT{
    UINT32     uiNextDelIndex;
    UINT32     uiNextAddIndex;
} SFILE_INDEX_STRUCT;

//node operation package
typedef struct sNODE_OP_PAK{
    UINT8          byCamID;
    SFILENAME_INFO FileNameInfo;
    PSDATETIMEFILE psParentNode;
    PSSUBNODE      psSubNode;
    UINT8          byOperation;
} SNODE_OP_PAK;

//cus api of each DB
typedef struct sDCFDT_CUS_API{
    AHC_BOOL (*pfCusNodeOperation)(void*, SNODE_OP_PAK);
    AHC_BOOL (*pfCurGetPath)      (void*, AHC_RTC_TIME*, char*, char*);
    AHC_BOOL (*pfNornalGetPath)   (void*, AHC_RTC_TIME*, char*, char*);
    AHC_BOOL (*pfContiShotGetPath)(void*, AHC_RTC_TIME*, char*, char*);
} SDCFDT_CUS_API;

//unify api for unify flow
typedef struct sUNIFY_CUS_API{
    AHC_BOOL (*pfCusMountAllDB)(UINT32);
} SUNIFY_CUS_API;

//continuous shot info
typedef struct sContiShot_Info{
    UINT8 byIsInit;
    UINT8 byCurShotMode;
    UINT8 byCurShotCnt[DCFDT_CAM_NUM];
    UINT8 byTotalShotNum[DCFDT_CAM_NUM];
    char  CSFilename[DCFDT_CONTISHOT_MAX_NUM][DCFDT_CAM_NUM][DCF_MAX_FILE_NAME_SIZE];
} CONTISHOT_INFO;

//---------------------------------------------------------------------------------
typedef struct sDATETIMEDCFDB{
    //new
    UINT8 byFileNamingType;
    char  szFileFreeChar[DCFDT_CAM_NUM][16];  //size limit = 16,TBD
    UINT8 byTimeFormat;    
    char  szFileFixedChar[DCFDT_CAM_NUM][16]; //size limit = 16,TBD
    char  szFolderPath[DCFDT_CAM_NUM][DCF_MAX_FILE_NAME_SIZE];

    // �ݩ�:
    UINT32 uiFlag;
    // �ܼư�
    UINT uiCurrentIndex[DCFDT_CAM_NUM];
    // total object num of all cam file in DB
    UINT32 ulTotalObjectNum;
    // total parent node number
    UINT32 ulTotalParentNodeNum;
    // total object num by each cam, DCF Index depends on it!!!!!
    UINT32 ulTotalObjectNumByCam[DCFDT_CAM_NUM];
    // total hidden num by each cam
    UINT32 ulTotalHiddenNumByCam[DCFDT_CAM_NUM];
    // �Ҧ��ɮפj�p�`�M
    UINT64 ullTotalObjectSize;
    // �̤j�ɮפj�p�`�M
    UINT32 ulMaxSizeThresholdInCluster;
    // �ϺФ����ݩ�DCF Objects���ɮ�
    UINT32 ulPayloadInCluster;

    ULONG  ulClusterSize;
    ULONG  ulTotalLockedObjects;
    UINT64 ullTotalLockedObjectSize;
    ULONG  ulTotalUnlockedObjects;
    UINT64 ullTotalUnlockedObjectSize;

    UINT64 ullUnlockedObjectNum[MAX_DCF_SUPPORT_FILE_TYPE];
    UINT64 ullUnlockedObjectSize[MAX_DCF_SUPPORT_FILE_TYPE];
    UINT64 ullLockedObjectNum[MAX_DCF_SUPPORT_FILE_TYPE];
    UINT64 ullLockedObjectSize[MAX_DCF_SUPPORT_FILE_TYPE];

    INT8   chAllowedFileType[MAX_DCF_SUPPORT_FILE_TYPE];

    AHC_BOOL bThreadConsiderPayload;

    // Disk Size in Clusters
    ULONG  ullDiskClusters;

    // max time
    // min time
    AHC_OS_SEMID smLock;
    AHC_BOOL     bFormatFreeEnable;
    UINT8        ubDBIndex;
    struct sDATETIMEFILE* pFileHead;
    struct sDATETIMEFILE* pFileTail;
    //Table to storage LockFile node Memory location 
    UINT32 ulCharLockFileTable[MAX_LOCK_FILE_NUM];
    //visit node use
    PSDATETIMEFILE        psCurrParentNode;
    //add node use , to record last add node
    PSDATETIMEFILE        psLastAddParentNode;
    //use for search slot, last searched parent node by master camID
    PSDATETIMEFILE        psLastSearchedParentNode;

    SFILE_INDEX_STRUCT    FileIndexStruct;
    SDCFDT_CUS_API        *pCusAPI;
    CONTISHOT_INFO        m_ContiShotInfo;
    UINT8                 byCamStatus;
} SDATETIMEDCFDB,*PSDATETIMEDCFDB;

/*******************************************************************************
 *
 *   DEFINITIONS
 *
*******************************************************************************/

AHC_BOOL AHC_DCFDT_GetTotalFileCountByCurrCamID(UINT32 *puiImgIndex);
AHC_BOOL AHC_DCFDT_RenameFile(DCF_DB_TYPE sFromType, AHC_RTC_TIME* psRtcTimeOld, AHC_RTC_TIME* psRtcTimeNew);
AHC_BOOL AHC_DCFDT_RenameFileByCamID(PSDATETIMEDCFDB pSrcDb,
                                    char* szSrcFullPath   , char* szDstFullPath,
                                    DATE_TIME nDateTimeOld, DATE_TIME nDateTimeNew, 
                                    UINT32 *puiFolderNameLen, UINT8 byCamID);
void     AIHC_DCFDT_DumpDB(void);
AHC_BOOL AHC_DCFDT_SetCurrentIndex(UINT32 uiImgIndex);
AHC_BOOL AHC_DCFDT_GetCurrentIndex(UINT32 *puiImgIndex);
AHC_BOOL AHC_DCFDT_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName);
AHC_BOOL AHC_DCFDT_GetFileNamebyIndex(UINT32 uiIndex, char* FileName);
AHC_BOOL AHC_DCFDT_GetFileSizebyIndex(UINT32 uiIndex, UINT32* FileSize);
AHC_BOOL AHC_DCFDT_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *FileType) ;
AHC_BOOL AHC_DCFDT_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime);
AHC_BOOL AHC_DCFDT_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly);
AHC_BOOL AHC_DCFDT_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[]);
AHC_BOOL AHC_DCFDT_GetAllowedChar(INT8* pbyChar, UINT32 uiLength);
AHC_BOOL AHC_DCFDT_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable);
AHC_BOOL AHC_DCFDT_GetDBStatus(DCF_DB_TYPE sType);
AHC_BOOL AHC_DCFDT_SelectDB(DCF_DB_TYPE sType);
DCF_DB_TYPE AHC_DCFDT_GetDB(void);
PSDATETIMEDCFDB AIHC_DCFDT_GetDbByType(DCF_DB_TYPE sType);
AHC_BOOL AIHC_DCFDT_DbDeleteCyclicFilebySize(PSDATETIMEDCFDB pDB, UINT64 ulSize );
AHC_BOOL AIHC_DCFDT_DbDeleteCyclicFilebyNum(PSDATETIMEDCFDB pDB, UINT32 ulNum );
AHC_BOOL AHC_DCFDT_FileOperation(char *pPathName, 
                                 char *pFileName, 
                                 UINT8 byOperation, 
                                 char *pDestPath, 
                                 char *pDestFileName);
AHC_BOOL AHC_DCFDT_IsReadOnlybyFilename(char *pPathName);
AHC_BOOL AHC_DCFDT_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly);
AHC_BOOL AHC_DCFDT_MoveFileByFileName_AllCam(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly);
AHC_BOOL AHC_DCFDT_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly);
UINT32 AHC_DCFDT_GetCyclicCluster(DCF_DB_TYPE sDB);
UINT32 AHC_DCFDT_GetFileCluster(DCF_DB_TYPE sDB);
UINT32 AHC_DCFDT_GetClusterTH(DCF_DB_TYPE sDB);
AHC_BOOL AHC_DCFDT_AdjustAllocation(DCF_STORAGE_ALLOC eType);
UINT64   AHC_DCFDT_GetFileTH(DCF_STORAGE_ALLOC sType);
AHC_BOOL AIHC_DCFDT_MountAllDB(UINT32 uiMaxMemSize);
AHC_BOOL AIHC_DCFDT_UnmountAllDB(void);
AHC_BOOL AIHC_DCFDT_PreAddFile(UINT16 uwDirKey, INT8 *pchFileName);
AHC_BOOL AIHC_DCFDT_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName);
AHC_BOOL AHC_DCFDT_GetName(AHC_RTC_TIME* psRtcTime, INT8 *FileFullPath, INT8 *FileName, UINT8 byCamStatus);
AHC_BOOL AHC_DCFDT_IsDBMounted(void);
AHC_BOOL AHC_DCFDT_RegisterCallback(MMP_ULONG ulCBType, void *pCallback);
void AHC_DCFDT_SetRearCamPathFlag(AHC_BOOL bSetRearCam);
void AHC_DCFDT_GetRearCamPathFlag(AHC_BOOL *bGetRearCam);
AHC_BOOL AHC_DCFDT_SearchAvailableFileSlot(UINT8 byCamID, char* szFilePathName);
AHC_BOOL AHC_DCFDT_TemplateCmp( char* pInput, char* pTemplate );
AHC_BOOL AHC_DCFDT_IsFullNameDbType(char* fullFileName, DCF_DB_TYPE dbType);
AHC_BOOL AHC_DCFDT_GetDbTypeByFullName(char* fullFileName, DCF_DB_TYPE* dbType);
INT8* AHC_DCFDT_GetRootDirName(void);
AHC_BOOL AHC_DCFDT_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock);
AHC_BOOL AHC_DCFDT_DeleteCyclicFilebySize(UINT64 uiSize);
AHC_BOOL AHC_DCFDT_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status);
AHC_BOOL AHC_DCFDT_CheckFormatFreeFolderFileNum(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_UpdateFormatFreeMaxFileNum(PSDATETIMEDCFDB pDB, UINT32 *pulMaxFileNum);

INT8* AHC_DCFDT_GetRootDirNameT(DCF_DB_TYPE dbType, UINT8 byCamID);
INT32 AHC_DCFDT_CmpFormatFreeFolderFileNum(PSDATETIMEDCFDB pDB);
void AHC_DCFDT_ResetDBStatistics(PSDATETIMEDCFDB pDB);
MMP_ERR AHC_DCFDT_SizeinFile_Update(char* szFilename);
UINT32 AHC_DCFDT_GetDualEncFileSizeT(DCF_DB_TYPE dbType, char *pchFileName);
UINT32 AHC_DCFDT_GetDualEncFileSize(char *pchFileName);
MMP_BOOL AHC_DCFDT_CheckFormatFreeDBSizeTH(UINT DBIdx);

AHC_BOOL AHC_DCFDT_CheckFormatFreeFolderFileNum(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_UpdateFormatFreeMaxFileNum(PSDATETIMEDCFDB pDB, UINT32 *pulMaxFileNum);
AHC_BOOL AHC_DCFDT_GetIndexbyDBandFileNameInfo(UINT8 byDBIndex, SFILENAME_INFO FileNameInfo, UINT32* DCFIndex);
AHC_BOOL AHC_DCFDT_CheckShareFileNumForAddFile(PSDATETIMEDCFDB pDB, UINT8 byCamID);
AHC_BOOL AHC_DCFDT_GetFileInfoByVisitNode(DCF_DB_TYPE DBtype, DCF_CAM_ID CamID, DCF_INFO *Info, UINT8 Op);
AHC_BOOL AHC_DCFDT_GetFormatFreeFileSize(char *pchFileName, UINT32 *ulFileSize);
AHC_BOOL AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE sDB, UINT32 *puiImgIndex);
AHC_BOOL AHC_DCFDT_CheckFileIsOpened(INT8 *pchFilePath);
AHC_BOOL AHC_DCFDT_TransferIndexbyCamID(UINT32 SrcIndex, DCF_CAM_ID CamID, UINT32 *DstIndex);
AHC_BOOL AHC_DCFDT_FileIndexCtrl(PSDATETIMEDCFDB pDB, UINT32 *uiIndex, DCFDT_FILE_INDEX_CTL Operation);
AHC_BOOL AHC_DCFDT_UpdateFileIndexToSavedFile(void);
AHC_BOOL AHC_DCFDT_ReadFileIndexFromSavedFile(void);
UINT32   AHC_DCFDT_RecalculateIndexByOffset(SFILE_INDEX_STRUCT FileIndexStruct,UINT32 uiFileIndex);
AHC_BOOL AHC_DCFDT_UpdateNextIndexInFile(void);
void     AHC_DCFDT_ModuleInit(void);
AHC_BOOL AHC_DCFDT_MountDCF(UINT32 uiMaxMemSize);
AHC_BOOL AIHC_DCFDT_MountAllDB_IndexMode(UINT32 uiMaxMemSize);
AHC_BOOL AHC_DCFDT_AdjustNextAddIndex(PSDATETIMEDCFDB pDB);
UINT32 AHC_DCFDT_GetCurrentDBFlag(void);
UINT32 AHC_DCFDT_GetInitDBFlag(DCF_DB_TYPE sType);
AHC_BOOL AHC_DCFDT_FormatFree_RemoveAsymmetricFiles(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_GetPathWithoutEXT(PSDATETIMEDCFDB pDB, AHC_RTC_TIME* psRtcTime, char* szNameBuff, char* FileName);
AHC_BOOL AHC_DCFDT_GetContiShotPathWithoutEXT(PSDATETIMEDCFDB pDB, AHC_RTC_TIME* psRtcTime, char* szNameBuff, char* FileName);

#endif //_AHC_DCFDT_H_
