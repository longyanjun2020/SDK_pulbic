//==============================================================================
/**
 @file AHC_DCFDT.c
 @brief Date Time Dcf
 @author Caesar Chang, Chuni Li
 @version 1.1
*/
/*===========================================================================
 * Include files
 *===========================================================================*/
#include "includes_fw.h"
#include "MenuSetting.h"
#include "ahc_datetime.h"
#include "ahc_uf.h"
#include "ahc_dcfdt.h"
#include "ahc_dcf.h"
#include "ait_utility.h"
#include "ahc_utility.h"
#include "ahc_fs.h"
#include "ahc_macro.h"
#include "ahc_mempoolfixedsize.h"
#include "mmps_fs.h"
#include "mmpf_fs_api.h"

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)

extern AHC_BOOL AHC_GetStorageMediaInfo(AHC_FS_DISK_INFO* sMediaInfo);

void* AHC_DCFDT_FileNodeAlloc( void );
void AHC_DCFDT_AddFile(PSDATETIMEDCFDB pDB,
                       UINT8 byCamID,
                       char* szFilename,
                       UINT32 ulSize,
                       AHC_FS_ATTRIBUTE sFileAttrib);
void AHC_DCFDT_UpdateFileData(PSDATETIMEDCFDB pDB,
                       UINT8 byCamID,
                       char* szFilename,
                       UINT32 ulSize,
                       AHC_FS_ATTRIBUTE sFileAttrib);
static AHC_BOOL AIHC_DCFDT_GetMediaInfo(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_LockInit(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_LockUninit(PSDATETIMEDCFDB pDB);
AHC_BOOL AHC_DCFDT_LockEx(PSDATETIMEDCFDB pDB, UINT32 uiTimeOutTick );
AHC_BOOL AHC_DCFDT_Lock(PSDATETIMEDCFDB pDB );
AHC_BOOL AHC_DCFDT_Unlock(PSDATETIMEDCFDB pDB);
PSDATETIMEFILE AIHC_DCFDT_GetParentNodeByIndex(PSDATETIMEDCFDB pDB, UINT uiIndex );
void* AHC_DCFDT_FileNodeAlloc( void );
AHC_BOOL AHC_DCFDT_FileNodeFree( void* pbyBuff );
AHC_BOOL AHC_DCFDT_GetFileNameByParentNode(PSDATETIMEDCFDB pDB,
                                 UINT8 byCamID,
                                 PSDATETIMEFILE psParentNode,
                                 char* szNameBuff);
PSDATETIMEDCFDB AHC_DCFDT_GetDBByFolderName(char* szFolderName);
AHC_BOOL AHC_DCFDT_AdjustAllocation(DCF_STORAGE_ALLOC eType);
AHC_BOOL AHC_DCFDT_DbRemoveFileByParentNode(PSDATETIMEDCFDB pDB,
                                            PSDATETIMEFILE  psParentNode,
                                            AHC_BOOL bDeleteInFS);
AHC_BOOL AHC_DCFDT_GetFullPathBySubNode(PSDATETIMEDCFDB pDB,
                                        SFILENAME_INFO FileNameInfo,
                                        PSSUBNODE psSubNode,
                                        char* szNameBuff,
                                        UINT uiBuffLength );
AHC_BOOL AHC_DCFDT_GetFullPathByParentNode(PSDATETIMEDCFDB pDB,
                                           UINT8 byCamID,
                                           PSDATETIMEFILE psParentNode,
                                           char* szNameBuff,
                                           UINT uiBuffLength);
//for only DCFDT use
void AIHC_DCFDT_UpdateLockFileTable(PSDATETIMEFILE psParentNode, AHC_BOOL *bDeleteFile, UINT8 byOperation);
AHC_BOOL AHC_DCFDT_NodeOperation(void* pDBset,
                                 SNODE_OP_PAK    NodeOpPak);
AHC_BOOL AHC_DCFDT_NodeOperation_Index(void* pDBset,
                                       SNODE_OP_PAK    NodeOpPak);
AHC_BOOL AHC_DCFDT_GetCamIDByFileName(PSDATETIMEDCFDB pDB, INT8 *pchFileName, UINT8 *pbyCamID);
PSDATETIMEFILE AHC_DCFDT_GetParentNodeByDateTime(PSDATETIMEDCFDB pDB, DATE_TIME nDateTime );
AHC_BOOL AHC_DCFDT_UpdateDBStatistics(PSDATETIMEDCFDB pDB,
                                      UINT8 byCamID,
                                      PSSUBNODE psSubNode,
                                      UINT8 byOperation);
PSDATETIMEFILE AHC_DCFDT_GetParentNodeByFilename(PSDATETIMEDCFDB pDB, char* szFilename );
PSSUBNODE AIHC_DCFDT_GetSubNodeByParentNode(PSDATETIMEDCFDB pDB, PSDATETIMEFILE psParentNode, UINT8 byCamID);
AHC_BOOL AHC_DCFDT_ParseFileName(PSDATETIMEDCFDB pDB,
                                 UINT8           byCamID,
                                 char            *szFilename,
                                 SFILENAME_INFO  *FileNameInfo,
                                 AHC_BOOL        *bIsCharLock);
AHC_BOOL AHC_DCFDT_GetDateTimeByFileName(PSDATETIMEDCFDB pDB,
                                         char            *szFilename,
                                         UINT32          uiFreeCharLen,
                                         DATE_TIME       *nDateTime,
                                         UINT32          *uiTimeStrLen);
AHC_BOOL AHC_DCFDT_GetFileNameBySubNode(PSDATETIMEDCFDB pDB, SFILENAME_INFO FileNameInfo, PSSUBNODE psSubNode, char* szNameBuff);
AHC_BOOL AHC_DCFDT_CreateFileTimeStrByDateTime(PSDATETIMEDCFDB pDB, DATE_TIME nDateTime, char* szFileTimeStr);
AHC_UF_Callback        *AHC_DCFDT_CB_GetStorageAllocationSetting = NULL;
AHC_UF_Callback        *AHC_DCFDT_CB_CreatFormatFreeFile = NULL;
AHC_MIMF_CB_NodeOperation *AHC_DCFDT_CB_NodeOperation = NULL;
#if ( UUID_XML_FEATURE == 1 )
AHC_BOOL UI_WriteSdUuidXML(void);
#endif
int sprintc( char* szOutput, char* szFormat, ... );
AHC_BOOL VideoFunc_GetRecordStatus(void);
/*******************************************************************************
 *
 *   DCFDT
 *
*******************************************************************************/
#define MAX_DCF_SUPPORT_FILE_TYPE       (16)

extern INT8                 m_DcfSupportFileType[MAX_DCF_SUPPORT_FILE_TYPE][4];
extern AHC_FS_DISK_INFO     m_sMediaInfo;
extern UINT32               m_uiBytesPerCluster;
PSMEMPOOLFIXEDSIZE          hFileNodeMemPool;
static DCF_STORAGE_ALLOC    m_AllocType = DCF_STORAGE_ALLOC_TYPE0;
static UINT32               m_uiModuleMode = DCFDT_CUSTOM_MODULE_MODE;

typedef struct tagDCFDTSETTING
{
  SDATETIMEDCFDB            m_sDB[DCF_DB_COUNT];
  AHC_BOOL                  m_bDBEnable[DCF_DB_COUNT];
  AHC_BOOL                  m_bMountDCF[DCF_DB_COUNT];
  UINT                      m_uiCurrDBIdx;
  UINT8                     m_byCurrCamID;
  DCF_DB_TYPE               m_sDBType;
  SUNIFY_CUS_API            *m_pUniCusAPI;
} SDCFDTSETTING,*PSDCFDTSETTING;

static SDCFDTSETTING sDcfDtSet=
{
  {0},             // SDATETIMEDCFDB
  {
    AHC_TRUE,
    #if ( DCF_DB_COUNT >= 2 )
    AHC_TRUE,
    #endif
    #if ( DCF_DB_COUNT >= 3 )
    AHC_TRUE,
    #endif
    #if ( DCF_DB_COUNT >= 4 )
    AHC_TRUE,
    #endif
  },               // AHC_BOOL                    m_bDBEnable[DCF_DB_COUNT];
  {0},             // AHC_BOOL                    m_bMountDCF[DCF_DB_COUNT];
  0,               // UINT                        m_uiCurrDBIdx;
  DCF_CAM_FRONT,
  0,               // DCF_DB_TYPE                 m_sDBType;
  NULL
};

static SDBINIT_CONFIG sDBInit_Config =
{
    DCFDT_SD_NUM,
    DCF_DB_COUNT,
    DCFDT_CAM_NUM,
    {DCFDT_ROOTNAME_SD, DCFDT_ROOTNAME_SD1},
    {
        //DB0
        {
            DCFDT_DB0_COMMON_FOLDER_PATH,
            DCFDF_DB0_FOLDER_LEVEL,
            DCFDT_DB0_FILENAME_NAMING_TYPE,
            DCFDT_TIMEFORMAT_TYPE,
            DCFDT_DB0_FLAG,
            {
                {DCFDT_DB0_CAM0_FOLDER_PATH, DCFDT_FREECHAR_DB0, DCFDT_FIXEDCHAR_CAM0},
                {DCFDT_DB0_CAM1_FOLDER_PATH, DCFDT_FREECHAR_DB0, DCFDT_FIXEDCHAR_CAM1}
            }
        },
        //DB1
        {
            DCFDT_DB1_COMMON_FOLDER_PATH,
            DCFDF_DB1_FOLDER_LEVEL,
            DCFDT_DB1_FILENAME_NAMING_TYPE,
            DCFDT_TIMEFORMAT_TYPE,
            DCFDT_DB1_FLAG,
            {
                {DCFDT_DB1_CAM0_FOLDER_PATH, DCFDT_FREECHAR_DB1, DCFDT_FIXEDCHAR_CAM0},
                {DCFDT_DB1_CAM1_FOLDER_PATH, DCFDT_FREECHAR_DB1, DCFDT_FIXEDCHAR_CAM1}
            }
        },
        //DB2
        {
            DCFDT_DB2_COMMON_FOLDER_PATH,
            DCFDF_DB2_FOLDER_LEVEL,
            DCFDT_DB2_FILENAME_NAMING_TYPE,
            DCFDT_TIMEFORMAT_TYPE,
            DCFDT_DB2_FLAG,
            {
                {DCFDT_DB2_CAM0_FOLDER_PATH, DCFDT_FREECHAR_DB2, DCFDT_FIXEDCHAR_CAM0},
                {DCFDT_DB2_CAM1_FOLDER_PATH, DCFDT_FREECHAR_DB2, DCFDT_FIXEDCHAR_CAM1}
            }
        },
        //DB3
        {
            DCFDT_DB3_COMMON_FOLDER_PATH,
            DCFDF_DB3_FOLDER_LEVEL,
            DCFDT_DB3_FILENAME_NAMING_TYPE,
            DCFDT_TIMEFORMAT_TYPE,
            DCFDT_DB3_FLAG,
            {
                {DCFDT_DB3_CAM0_FOLDER_PATH, DCFDT_FREECHAR_DB3, DCFDT_FIXEDCHAR_CAM0},
                {DCFDT_DB3_CAM1_FOLDER_PATH, DCFDT_FREECHAR_DB3, DCFDT_FIXEDCHAR_CAM1}
            }
        },
        //DB4
        {
            DCFDT_DB4_COMMON_FOLDER_PATH,
            DCFDF_DB4_FOLDER_LEVEL,
            DCFDT_DB4_FILENAME_NAMING_TYPE,
            DCFDT_TIMEFORMAT_TYPE,
            DCFDT_DB4_FLAG,
            {
                {DCFDT_DB4_CAM0_FOLDER_PATH, DCFDT_FREECHAR_DB4, DCFDT_FIXEDCHAR_CAM0},
                {DCFDT_DB4_CAM1_FOLDER_PATH, DCFDT_FREECHAR_DB4, DCFDT_FIXEDCHAR_CAM1}
            }
        }
    }
};
//-------------------------------------------------
static SDCFDT_CUS_API StandardDateTimeModeFunc =
{
    AHC_DCFDT_NodeOperation,
    AHC_DCFDT_GetPathWithoutEXT,
    AHC_DCFDT_GetPathWithoutEXT,
    AHC_DCFDT_GetPathWithoutEXT //datetime mode dose not support contishot tmp
};

static SDCFDT_CUS_API CusDateTime_IndexModeFunc =
{
    AHC_DCFDT_NodeOperation_Index,
    AHC_DCFDT_GetPathWithoutEXT,
    AHC_DCFDT_GetPathWithoutEXT,
    AHC_DCFDT_GetContiShotPathWithoutEXT
};
//--------------------------------------------------
static SUNIFY_CUS_API UniStandardModeFunc =
{
    AIHC_DCFDT_MountAllDB
};

static SUNIFY_CUS_API UniCusDateTime_IndexFunc =
{
    AIHC_DCFDT_MountAllDB_IndexMode
};
//--------------------------------------------------
#if (AHC_SHAREENC_SUPPORT)
INT32   formatfreefilenum = 0;
extern MMP_ULONG m_ulShareRecdRepackAuxWriteFileSize;
extern MMP_ULONG m_ulShareRecdTotalWriteFileSize;
#endif
//if index lock = true , Add/Del File Index can't be changed
static AHC_BOOL bFileIndexLock = AHC_FALSE;

/*******************************************************************************
 *
 *   START DATETIME
 *
*******************************************************************************/
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_InitFolderPathPool
//  Description : This function inits folder path of all permutation combination of all DB
//  @param[out]  DcfFolderPathPool output folder path
//  @param[in]   psDBInit_Config   init config setting by definition
//------------------------------------------------------------------------------
static void AHC_DCFDT_InitFolderPathPool(INT8 DcfFolderPathPool[], PSDBINIT_CONFIG psDBInit_Config)
{
    UINT32 i, j, k;
    //make all permutation combination of folder path
    for(i = 0; i < DCFDT_SD_NUM; i++)
    {
        for(j = 0; j < DCF_DB_COUNT; j++)
        {
            for(k = 0; k < DCFDT_CAM_NUM; k++)
            {
                MEMCPY(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), psDBInit_Config->szRootName[i], sizeof(psDBInit_Config->szRootName));
                STRCAT(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), "\\");
                STRCAT(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), psDBInit_Config->sDBAttrConfig[j].szCommonFolder);
                if(psDBInit_Config->sDBAttrConfig[j].byFolderLevel == 2)
                {
                    STRCAT(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), "\\");
                    STRCAT(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), psDBInit_Config->sDBAttrConfig[j].sPathConfig[k].szCamFolder);
                }
                else if(psDBInit_Config->sDBAttrConfig[j].byFolderLevel > 2)
                {
                    AHC_DBG_MSG(1, "Folder level error, please check define FOLDER_LEVEL\r\n");
                }
                STRCAT(&(DcfFolderPathPool[(i*DCF_DB_COUNT*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(j*DCFDT_CAM_NUM*DCF_MAX_FILE_NAME_SIZE)+(k*DCF_MAX_FILE_NAME_SIZE)]), "\0");

            }
        }
    }
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_CreateFilename
//  Description : This function creates filename by input DateTime when this file
//                 doesn't exist in the DB. It used for create filename which does
//                 not exist
//  @param[in]  pDb        use template in DB
//  @param[in]  nDateTime  datetime to create
//  @param[out] szFilename create filename
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_DCFDT_CreateFilename( PSDATETIMEDCFDB pDb,
                                           UINT8 byCamID,
                                           SFILENAME_INFO  FileNameInfo,
                                           char* szFilename,
                                           AHC_BOOL bIsCharLock )
{
    switch(pDb->byFileNamingType)
    {
        case DCFDT_FILENAME_NAMING_STANDARD:
        {
            char szFileTimeStr[DCF_MAX_FILE_NAME_SIZE];
            MEMSET(szFilename, 0, sizeof(pDb->szFileFreeChar[byCamID]));
            //copy szFileFreeChar
            if(bIsCharLock){
                MEMCPY( szFilename, DCFDT_FREECHAR_LOCK, STRLEN(DCFDT_FREECHAR_LOCK));
            }
            else{
                MEMCPY( szFilename, pDb->szFileFreeChar[byCamID], STRLEN(pDb->szFileFreeChar[byCamID]));
            }
            //create filetime str by datetime
            if(!AHC_DCFDT_CreateFileTimeStrByDateTime(pDb, FileNameInfo.nDateTime, szFileTimeStr))
            {
                AHC_DBG_MSG(1, "\r\n");
                return AHC_FALSE;
            }
            //strcat szFileTimeStr
            STRCAT(szFilename, szFileTimeStr);
            //strcat szFileFixedChar
            STRCAT(szFilename, pDb->szFileFixedChar[byCamID]);
            szFilename[STRLEN(szFilename)] = '\0';

            return AHC_TRUE;
        }
        break;
        case DCFDT_FILENAME_NAMING_SINGLE_CAM:
        {
            char szFileTimeStr[DCF_MAX_FILE_NAME_SIZE];
            MEMSET(szFilename, 0, sizeof(szFilename));
            //copy szFileFreeChar
            if(bIsCharLock){
                MEMCPY( szFilename, DCFDT_FREECHAR_LOCK, STRLEN(DCFDT_FREECHAR_LOCK));
            }
            else{
                MEMCPY( szFilename, pDb->szFileFreeChar[byCamID], STRLEN(pDb->szFileFreeChar[byCamID]));
            }
            //create filetime str by datetime
            if(!AHC_DCFDT_CreateFileTimeStrByDateTime(pDb, FileNameInfo.nDateTime, szFileTimeStr))
            {
                AHC_DBG_MSG(1, "\r\n");
                return AHC_FALSE;
            }
            //strcat szFileTimeStr
            STRCAT(szFilename, szFileTimeStr);
            szFilename[STRLEN(szFilename)] = '\0';

            return AHC_TRUE;
        }
        break;
        case DCFDT_FILENAME_NAMING_BYINDEX:
        {
            char szIndexStr[DCF_MAX_FILE_NAME_SIZE];
            char szFileTimeStr[DCF_MAX_FILE_NAME_SIZE];
            MEMSET(szFilename, 0, sizeof(szFilename));
            szIndexStr [0] = '\0';
            szFileTimeStr[0] = '\0';
            //copy szFileFreeChar
            if(bIsCharLock){
                MEMCPY( szFilename, DCFDT_FREECHAR_LOCK, STRLEN(DCFDT_FREECHAR_LOCK));
                szFilename[STRLEN(DCFDT_FREECHAR_LOCK)]='\0';
            }
            else{
                MEMCPY( szFilename, pDb->szFileFreeChar[byCamID], STRLEN(pDb->szFileFreeChar[byCamID]));
                szFilename[STRLEN(pDb->szFileFreeChar[byCamID])]='\0';
            }

            //create filetime str by datetime
            if(!AHC_DCFDT_CreateFileTimeStrByDateTime(pDb, FileNameInfo.nDateTime, szFileTimeStr))
            {
                AHC_DBG_MSG(1, "%s error %d\r\n", __FUNCTION__, __LINE__);
                return AHC_FALSE;
            }

            //strcat szFileTimeStr
            STRCAT(szFilename, szFileTimeStr);
            //strcat dash
            STRCAT(szFilename, "-");
            //transfer index to str
            sprintf(szIndexStr, "%06d", FileNameInfo.uiFileIndex);
            //strcat index str
            STRCAT(szFilename, szIndexStr);
            //strcat szFileFixedChar
            STRCAT(szFilename, pDb->szFileFixedChar[byCamID]);

            szFilename[STRLEN(szFilename)] = '\0';

            return AHC_TRUE;
        }
        break;
        default:
            AHC_DBG_MSG(1, "UnIdentify FileNameType");
            return AHC_FALSE;
        break;
    }
    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_DeleteFileInFS
//  Description : Given file full path, delete it in FS
//  @param[in]  pDB              input DB
//  @param[in]  szFullPath       Fullpath of delete file
//  @param[in]  bIsFileReadOnly  Is file read only, if is read only, change its attr
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_DeleteFileInFS(PSDATETIMEDCFDB pDB, char* szFullPath, AHC_BOOL bIsFileReadOnly )
{
    if(pDB->bFormatFreeEnable)
    {
        AHC_FS_ATTRIBUTE attrib;
        AHC_FS_FileDirGetAttribute(szFullPath,
                                       STRLEN(szFullPath), &attrib );
        attrib |= AHC_FS_ATTR_HIDDEN;
        if( bIsFileReadOnly )
        {
            attrib &= ~(AHC_FS_ATTR_READ_ONLY);
        }
        AHC_FS_FileDirSetAttribute(szFullPath,
                                       STRLEN(szFullPath), attrib );
    }
    else
    {
        if( bIsFileReadOnly )
        {
            // Remove read only attribute
            AHC_FS_ATTRIBUTE attrib;
            AHC_FS_FileDirGetAttribute(szFullPath,
                                       STRLEN(szFullPath), &attrib );

            attrib &= ~(AHC_FS_ATTR_READ_ONLY|AHC_FS_ATTR_HIDDEN|AHC_FS_ATTR_SYSTEM);
            AHC_FS_FileDirSetAttribute(szFullPath,
                                       STRLEN(szFullPath), attrib );
        }

        if( AHC_ERR_NONE != AHC_FS_FileRemove(szFullPath,
                                              STRLEN(szFullPath)))
        {
            AHC_DBG_MSG(1, "Remove file %s failed!\n", szFullPath );
            return AHC_FALSE;
        }
        //AHC_DBG_MSG(1, "%s Delete %s\n", __FUNCTION__,szFullPath);
    }

    return AHC_TRUE;

}

//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_ChangeToNmeaName
//  Description : Change original file full path to NMEA path
//  @param[in]  szFullPath Fullpath which would change to NMEA filepath
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_DCFDT_ChangeToNmeaName(char* szFilePath )
{
    char* ptr;

    // Change the extention name to .NMEA file path
    // Rear find the char '.'
    ptr = AHC_Strrchr(szFilePath, '.' );
    if( ptr == NULL )
    {
        return AHC_FALSE;
    }

    // Make path end at '.'
    ptr++;
    *ptr = '\0';

    // Paste 'NMEA' at the end.
    STRCAT(ptr, DCFDT_NEMA_FILE_EXTENTION);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_MakeNmeaName
//  Description : Given original file full path,and make NMEA path
//  @param[in]   szFullPath Fullpath which would change to NMEA filepath
//  @param[out]  szFullPath Fullpath which would change to NMEA filepath
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_DCFDT_MakeNmeaName(char* szFilePath, char* szNmeaFilePath )
{
    char* ptr;

    if( szNmeaFilePath == NULL )
    {
        return AHC_FALSE;
    }

    STRCPY( szNmeaFilePath, szFilePath );

    // Change the extention name to .NMEA file path
    // Rear find the char '.'
    ptr = AHC_Strrchr(szNmeaFilePath, '.' );
    if( ptr == NULL )
    {
        return AHC_FALSE;
    }

    // Make path end at '.'
    ptr++;
    *ptr = '\0';

    // Paste 'NMEA' at the end.
    STRCAT(ptr, DCFDT_NEMA_FILE_EXTENTION);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_DeleteNmeaFileInFS
//  Description : this file deletes NMEA file in filesystem
//  @param[in]   szFullPath      Fullpath which would change to NMEA filepath
//  @param[in]   bIsFileReadOnly is file read only?need to cancel its readonly attr
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------

static AHC_BOOL AIHC_DCFDT_DeleteNmeaFileInFS( char* szFullPath, AHC_BOOL bIsFileReadOnly )
{

    char  szNmeaFilePath[DCF_MAX_FILE_NAME_SIZE];

    // Get NMEA file path
    if( !AIHC_DCFDT_MakeNmeaName(szFullPath, szNmeaFilePath ) )
    {
        return AHC_FALSE;
    }

    if( bIsFileReadOnly )
    {
        // Remove read only attribute
        AHC_FS_ATTRIBUTE attrib;
        AHC_FS_FileDirGetAttribute(szNmeaFilePath,
                                   STRLEN(szNmeaFilePath), &attrib );

        attrib &= ~(AHC_FS_ATTR_READ_ONLY|AHC_FS_ATTR_HIDDEN|AHC_FS_ATTR_SYSTEM);
        AHC_FS_FileDirSetAttribute(szNmeaFilePath,
                                   STRLEN(szNmeaFilePath), attrib );

    }

    if( AHC_ERR_NONE != AHC_FS_FileRemove(szNmeaFilePath,
                                          STRLEN(szNmeaFilePath)))
    {
        AHC_DBG_MSG(1, "Remove Nmea file %s failed!\n", szNmeaFilePath );
        return AHC_FALSE;
    }

    //AHC_DBG_MSG(1, "Delete %s\n", szNmeaFilePath);
    return AHC_TRUE;
}

/**************************************************************************************************

DCFDT

***************************************************************************************************/
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_RegisterCallback
//  Description : This Function made for expansion customized functions
//  @param[in]  ulCBType  CB type
//  @param[in]  pCallback callback pointer
//  @retval    MMP_ERR_NONE               Success.
//  @retval    MMP_SYSTEM_ERR_PARAMETER   Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_RegisterCallback(MMP_ULONG ulCBType, void *pCallback)
{
    MMP_ERR ret = MMP_ERR_NONE;

    switch(ulCBType) {
    case AHC_UFCB_GET_STORAGE_ALLOCATION_SETTING:
        AHC_DCFDT_CB_GetStorageAllocationSetting = (AHC_UF_Callback *)pCallback;
    break;
    case AHC_UFCB_CREATE_FORMAT_FREE_FILE:
        AHC_DCFDT_CB_CreatFormatFreeFile = (AHC_UF_Callback *)pCallback;
    break;
    case AHC_UFCB_NODE_OPERATION:
        AHC_DCFDT_CB_NodeOperation = (AHC_MIMF_CB_NodeOperation *)pCallback;
    break;
    default:
        ret = MMP_SYSTEM_ERR_PARAMETER;
    }
    return ret;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_InitDB
//  Description : This Function inits DB,
//  @param[in]  pDB    input DB
//  @param[in]  uiFlag flag for the DB attr
//------------------------------------------------------------------------------
void AHC_DCFDT_InitDB(PSDATETIMEDCFDB pDB, UINT uiFlag)
{
    MEMSET(pDB, 0, sizeof(SDATETIMEDCFDB) );

    pDB->uiFlag = uiFlag;

    if( uiFlag & DCFDT_DB_FLAG_COUNT_PAYLOAD_INTO_TH )
    {
        pDB->bThreadConsiderPayload = AHC_TRUE;
    }

    // Read file system cluster info
    // Get Info
    AIHC_DCFDT_GetMediaInfo(pDB);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_InitDB_PathName
//  Description : This Function inits PathName of each DB and Cam
//  @param[in]  pDB              input DB
//  @param[in]  szFolderPath     szFolderPath to put into pDB->szFolderPath
//  @param[in]  byCamID          byCamID to switch cam
//  @param[in]  byFileNamingType byFileNamingType of the DB, ref DCFDT_FILENAME_NAMING_TYPE
//  @param[in]  szFileFreeChar   szFileFreeChar, e.g. FILE010101-010101F.mov , szFileFreeChar is FILE
//  @param[in]  byTimeFormat     byTimeFormat, e.g. FILE010101-010101F.mov , byTimeFormat is 010101-010101
//  @param[in]  szFileFixedChar  szFileFixedChar, e.g. FILE010101-010101F.mov , szFileFixedChar is F
//------------------------------------------------------------------------------
void AHC_DCFDT_InitDB_PathName(PSDATETIMEDCFDB pDB, UINT8 byCamID, char* szFolderPath, UINT8 byFileNamingType, char* szFileFreeChar, UINT8 byTimeFormat, char* szFileFixedChar)
{
    // Init
    strcpy(pDB->szFolderPath[byCamID], szFolderPath);
    pDB->byFileNamingType = byFileNamingType;
    strcpy(pDB->szFileFreeChar[byCamID], szFileFreeChar);
    pDB->byTimeFormat = byTimeFormat;
    strcpy(pDB->szFileFixedChar[byCamID], szFileFixedChar);
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MultiFolderHandler
//  Description : This function helps ParseFolder to check folder level and
//                check each level of folder exist or not?If the folder doesn't
//                exist, create it.At last,keeps the last level of folder open,
//                and return the folderID.
//  @param[in] szFolder    Full folder name
//  @param[in] puiFolderID pointer of FolderID
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AHC_DCFDT_MultiFolderHandler(char* szFolder, UINT32* puiFolderID)
{
    #define             DCF_FOLDER_MAX_LEVEL  3
    #define             DCF_DIVIDE_CHAR       '\\'
    UINT32              uiFullPathLength;
    char*               ptr;
    INT8                byFolderLevel = 0;
    int                 i = 0,j = 0;
    char                szTempFolderPath[DCF_MAX_FILE_NAME_SIZE];
    char                szDirFolderPath[DCF_MAX_FILE_NAME_SIZE];
    UINT8               byPathLength = 0;
    UINT8               byTempLength = 0;
    UINT8               byLevelCount = 0;
    UINT8               byDelPathLength = 0;
    uiFullPathLength    = STRLEN(szFolder);
    if(uiFullPathLength == 0)
    {
        AHC_DBG_MSG(1, "Warning!! %s length = 0\r\n", szFolder);
    }
    //Calculate Folder Level
    i = STRLEN(szFolder) - 1;
    while( i >= 0 && szFolder[i] != '\0')
    {
        if( szFolder[i] == DCF_DIVIDE_CHAR )
        {
            byFolderLevel++;
        }
        i--;
    }
    //check folder level
    if(byFolderLevel > DCF_FOLDER_MAX_LEVEL)
    {
        AHC_DBG_MSG(1, "Warning!!%s FolderLevel = %d, maxlevel = %d\r\n", szFolder, byFolderLevel, DCF_FOLDER_MAX_LEVEL);
    }
    // Open directory for each level, if curlevel !=  last level, close it
    // 1.SD:\\Normal
    // 2.SD:\\Normal\\F
    // etc.
    for(i=0; i<byFolderLevel; i++)
    {
        byPathLength    = 0;
        byDelPathLength = 0;
        byTempLength = uiFullPathLength;
        byLevelCount = byFolderLevel - 1 - i;
        memset(szDirFolderPath, 0, sizeof(szDirFolderPath));
        //calculate length and get folder path by each level count
        for(j=0; j< byLevelCount ; j++)
        {
            memset(szTempFolderPath, 0, sizeof(szTempFolderPath));
            memcpy(szTempFolderPath, szFolder, byTempLength);
            ptr = StrChrReverse(szTempFolderPath,DCF_DIVIDE_CHAR);
            byTempLength = ptr - szTempFolderPath;
            byDelPathLength += (STRLEN(szTempFolderPath) - byTempLength);
        }

        byPathLength = uiFullPathLength - byDelPathLength;
        memcpy(szDirFolderPath, szFolder, byPathLength);
        //open folder or create it
        if(AHC_FS_DirOpen(szDirFolderPath, byPathLength, puiFolderID) != MMP_ERR_NONE)
        {
            //if open folder failed, create it
            AHC_FS_DirCreate(szDirFolderPath, byPathLength);       ///< Create a new directory
            //if create file at last level folder, return false and stop parsing
            if((i + 1) == byFolderLevel)
            {
                return AHC_FALSE;
            }
        }
        else
        {
            //if file open folder successful, close current folder
            //or the folder is the parsing folder,should not close it
            if(i != byFolderLevel -1 )
            {
                AHC_FS_DirClose(*puiFolderID);

            }
        }
    }
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_ParseFolder
//  Description : This function parse folder from specific DB
//  @param[in] pDB     input DB
//  @param[in] byCamID CamID means which cam file would be parsing
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_ParseFolder( PSDATETIMEDCFDB pDB ,UINT8 byCamID)
{
    char*               szFolder;
    UINT32              error;
    UINT32              uiFolderID;
    AHC_FS_FILETIME     FileTimeStruct;
    UINT32              uiFileSize = 0;
    UINT8               byFileMode;
    AHC_FS_ATTRIBUTE    sFileAttrib;
    char                szFilename[DCF_MAX_FILE_NAME_SIZE];
    int                 i=0;
    byFileMode      =   AHC_FILE_NAME | AHC_ATTRIBUTE | AHC_ENTRY_SIZE;

    //temp, TBD
    szFolder = pDB->szFolderPath[byCamID];

    if(!AHC_DCFDT_MultiFolderHandler(szFolder, &uiFolderID))
    {
        return AHC_TRUE;//AHC_FALSE;
    }

    while(1)
    {
        error = AHC_FS_GetFileList( uiFolderID,
                                 byFileMode,
                                 szFilename,
                                 &sFileAttrib,
                                 &FileTimeStruct,
                                 &uiFileSize );

        if ( AHC_FS_ERR_NO_MORE_ENTRY == error )
        {
            break;
        }

        // Skip first two items
        if( szFilename[0] == '.')
        {
            continue;
        }
        //get share file size
        #if (AHC_SHAREENC_SUPPORT)
        if(pDB->ubDBIndex == DCF_DB_FORMAT_FREE_DB)
        {
            if(!AHC_DCFDT_GetFormatFreeFileSize(szFilename, &uiFileSize)){
                AHC_DBG_MSG(1, "AHC_DCFDT_GetFormatFreeFileSize failed!\r\n");
                return AHC_FALSE;
            }
        }
        #endif
        if(AHC_FS_ATTR_DIRECTORY & sFileAttrib)
        {
            // Folder
        }
        else
        {
            // Added file
            AHC_DCFDT_AddFile(pDB, byCamID, szFilename, uiFileSize, sFileAttrib);
            i++;
        }
    }
    error = AHC_FS_DirClose(uiFolderID);
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_UnmountDB
//  Description : This function unmounts DB, clear DB all data
//  @param[in] pDB     input DB
//------------------------------------------------------------------------------
void AHC_DCFDT_UnmountDB(PSDATETIMEDCFDB pDB)
{
    // free all file unit
    // clear db

    AHC_DCFDT_LockUninit(pDB);

    MEMSET( pDB, 0, sizeof(SDATETIMEDCFDB) );

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MountDB
//  Description : This function mounts DB by given pDB
//  @param[in] pDB     input DB
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MountDB(PSDATETIMEDCFDB pDB)
{
    // Check if umount yet
    // If not, umount it.
    AHC_DCFDT_LockInit(pDB);

    // Get Info
    AIHC_DCFDT_GetMediaInfo(pDB);

    // Add file to db
    // update db stastics data
    AHC_DCFDT_Lock(pDB);
    if (AHC_DCFDT_ParseFolder(pDB, DCF_CAM_FRONT) == MMP_FALSE)
    {
        AHC_DCFDT_Unlock(pDB);
        return MMP_FALSE;
    }

    if (pDB->uiFlag & DCFDT_DB_FLAG_HAS_REAR_CAM)
    {
        if(AHC_DCFDT_ParseFolder(pDB, DCF_CAM_REAR) == MMP_FALSE){
            AHC_DCFDT_Unlock(pDB);
            return MMP_FALSE;
        }
    }
    AHC_DCFDT_Unlock(pDB);

    return MMP_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileExtension
//  Description : This function gets file ext from given filename
//  @param[in]  szFilename input file name
//  @param[out] szExt      output extension
//  @param[out] nExtSize   ext size
//  @retval    AHC_TRUE    Success.
//  @retval    AHC_FALSE   Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileExtension(char* szFilename, char* szExt, int nExtSize )
{
    int nLength = STRLEN(szFilename);
    int nTmp    = nLength;
    int i;

    // find dot
    while( nTmp && szFilename[nTmp] != '.' )
    {
        nTmp--;
    }

    if(nTmp==0) return AHC_FALSE;

    nTmp++;

    if( nExtSize < nLength - nTmp )
    {
        return AHC_FALSE;
    }

    nExtSize = nLength - nTmp;

    for( i=0; i< nExtSize; i++ )
    {
        szExt[i] = szFilename[nTmp+i];
    }

    szExt[i] = '\0';

#if (DCFDT_DEBUG)
    AHC_DBG_MSG(1, "szExt=%s\n",szExt );
#endif

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileExtType
//  Description : This function gets filetype from given extension
//  @param[in]  szExt input file ext
//  @retval     filetype
//------------------------------------------------------------------------------
BYTE AHC_DCFDT_GetFileExtType(char* szExt )
{
    int i;
    int type = DCFDT_UNKNOW_TYPE;
    for( i=0; i< MAX_DCF_SUPPORT_FILE_TYPE; i++ )
    {
        if( STRCMP( m_DcfSupportFileType[i], szExt ) == 0 )
        {
            type = i;
            break;
        }
    }

    return type;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileType
//  Description : This function gets filetype from given filename
//  @param[in]  szFilename input file name
//  @retval     filetype
//------------------------------------------------------------------------------
UINT8 AHC_DCFDT_GetFileType(char* szFilename)
{
    #define FILE_EXTENSION_SIZE     5
    char szExt[FILE_EXTENSION_SIZE]={0};
    BYTE  type;

    if( AHC_DCFDT_GetFileExtension(szFilename, szExt, FILE_EXTENSION_SIZE ) == AHC_FALSE )
    {
        return (UINT8) DCFDT_UNKNOW_TYPE;
    }

    // Get file type
    type = AHC_DCFDT_GetFileExtType(szExt);

    return type;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DumpDb
//  Description : This function dumps all DB data to UART
//  @param[in] pDB     input DB
//------------------------------------------------------------------------------
void AHC_DCFDT_DumpDb(PSDATETIMEDCFDB pDB)
{
    PSDATETIMEFILE psParentNode;
    UINT           uiTotalClusters =0;
    UINT           uiTotalFileNum  =0;
    UINT           uiClustersPerMB = 1024*1024 / pDB->ulClusterSize;

    AHC_DCFDT_Lock(pDB);
    psParentNode = pDB->pFileHead;
    while(psParentNode)
    {
        PSSUBNODE psSubNode;
        char      szFilename[DCF_MAX_FILE_NAME_SIZE];
        char      szFilepath[DCF_MAX_FILE_NAME_SIZE];
        UINT8     bReadOnly;
        UINT8     bCharLock;
        UINT8     bHidden;
        MMPS_FS_ATTRIBUTE FileAttribute = 0;
        MMPS_FS_FILETIME  FileTimestructure = {0};
        UINT32    ulsize;

        psSubNode = psParentNode->pCamNodeHead;
        while(psSubNode)
        {
            uiTotalClusters += psSubNode->nSizeInCluster;
            uiTotalFileNum  ++;
            MEMSET(szFilename, 0, sizeof(szFilename));
            MEMSET(szFilepath, 0, sizeof(szFilepath));
            AHC_DCFDT_GetFileNameByParentNode(pDB, psSubNode->byCamID, psParentNode, szFilename);
            AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNode->byCamID, psParentNode, szFilepath, sizeof(szFilepath));
            bReadOnly = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY)?AHC_TRUE : AHC_FALSE;
            bCharLock = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK)?AHC_TRUE : AHC_FALSE;
            bHidden   = (psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN  )?AHC_TRUE : AHC_FALSE;
            AHC_DBG_MSG(1, "\r\n\t%s Ty%d R%d CL%d H%d RealSize %d Bytes\r\n", szFilename,
                                           psSubNode->byFileType,
                                           bReadOnly,
                                           bCharLock,
                                           bHidden,
                                           psSubNode->nSizeInCluster * pDB->ulClusterSize);
            if(pDB->ubDBIndex == DCF_DB_FORMAT_FREE_DB)
            {
                MMPS_FS_FileDirGetInfo(szFilepath, sizeof(szFilepath), &FileAttribute, &FileTimestructure, &ulsize);
                AHC_DBG_MSG(1, " FileSize %d Bytes", ulsize);
            }
            psSubNode = psSubNode->pNext;
        }
        //AHC_DBG_MSG(1, "psParentNode->byCamExist 0x%x\r\n", psParentNode->byCamExist);
        psParentNode = psParentNode->pNext;
    }
    AHC_DBG_MSG(1, "\r\n");

#if (DCFDT_DEBUG)
    AHC_DBG_MSG(1,  "Cluster Size=%d\n", pDB->ulClusterSize );
    AHC_DBG_MSG(1,  "Threshold   =%d (%dMB) \n", pDB->ulMaxSizeThresholdInCluster, pDB->ulMaxSizeThresholdInCluster/uiClustersPerMB);
    AHC_DBG_MSG(1,  "Payload     =%d (%dMB)\n", pDB->ulPayloadInCluster, pDB->ulPayloadInCluster/uiClustersPerMB);

    AHC_DBG_MSG(1,  "Number of Objects %d \n", pDB->ulTotalObjectNum);
    AHC_DBG_MSG(1,  "Total Size of Objects %d (%dMB)\n", (UINT32)(pDB->ullTotalObjectSize / pDB->ulClusterSize), (UINT32)(pDB->ullTotalObjectSize/1024/1024)  );
    AHC_DBG_MSG(1,  "Sum of total files num %d\n", uiTotalFileNum );
    AHC_DBG_MSG(1,  "Sum of total files clusters %d\n", uiTotalClusters );
#endif
    AHC_DCFDT_Unlock(pDB);
}

//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_GetMediaInfo
//  Description : This function gets MediaInfo from FS
//  @param[out] pDB         DB to storage cluster info
//  @retval     AHC_TRUE    Success.
//  @retval     AHC_FALSE   Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AIHC_DCFDT_GetMediaInfo(PSDATETIMEDCFDB pDB)
{

    UINT64 uiiTotalBytes;

    // Get the info of media
    AHC_GetStorageMediaInfo(&m_sMediaInfo);

    m_uiBytesPerCluster = m_sMediaInfo.usBytesPerSector*m_sMediaInfo.usSecPerCluster;


    uiiTotalBytes = (UINT64)m_sMediaInfo.ulTotalClusters*m_uiBytesPerCluster;

    pDB->ulClusterSize    = ((ULONG)m_sMediaInfo.usBytesPerSector)*m_sMediaInfo.usSecPerCluster;
    pDB->ullDiskClusters  = m_sMediaInfo.ulTotalClusters;

#if (DCFDT_DEBUG)
    AHC_DBG_MSG(1, "BytesPerSec     : %d, \r\n", m_sMediaInfo.usBytesPerSector);
    AHC_DBG_MSG(1, "SecPerCluster   : %d, \r\n", m_sMediaInfo.usSecPerCluster);
    AHC_DBG_MSG(1, "TotalCluster    : %d, \r\n", m_sMediaInfo.ulTotalClusters);
    AHC_DBG_MSG(1, "FreelCluster    : %d, \r\n", m_sMediaInfo.ulFreeClusters);
    AHC_DBG_MSG(1, "BytesPerCluster : %d, \r\n", m_uiBytesPerCluster);
    AHC_DBG_MSG(1, "uiiTotalBytes    : %d, \r\n", uiiTotalBytes);
#endif

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DeleteSubNode
//  Description : This function delete sub node by given parent node and CamID
//  @param[in] pDB          input DB
//  @param[in] byCamID      select CamID to delete
//  @param[in] psParentNode select psParentNode
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
static AHC_BOOL AHC_DCFDT_DeleteSubNode(PSDATETIMEDCFDB pDB,
                                    UINT8 byCamID,
                                    PSDATETIMEFILE psParentNode)
{
    AHC_BOOL  bFound = AHC_FALSE;
    PSSUBNODE psSubNodeCur, psSubNodePrev;
    PSSUBNODE psSubNodeCurTmp, psSubNodePrevTmp;
    UINT8     bySubNodeCount = 0;
    psSubNodeCur = psParentNode->pCamNodeHead;
    while(psSubNodeCur)
    {
        bySubNodeCount++;
        psSubNodePrevTmp = psSubNodeCur;
        psSubNodeCurTmp  = psSubNodeCur->pNext;

        if(psSubNodeCur->byCamID == byCamID)
        {
            bFound = AHC_TRUE;
            if(pDB->bFormatFreeEnable)
            {
                psSubNodeCur->byFileAttr |= DCFDT_FILEATTR_HIDDEN;
            }
            else
            {
                //unlink sub node and free it
                //head node
                if(psSubNodeCur == psParentNode->pCamNodeHead){
                    psParentNode->pCamNodeHead = psSubNodeCur->pNext;
                }
                //tail node
                else if(psSubNodeCur->pNext == NULL){
                    psSubNodePrev->pNext = NULL;
                }
                //middle node
                else{
                    psSubNodePrev->pNext = psSubNodeCur->pNext;
                }
                AHC_DCFDT_FileNodeFree((void*)psSubNodeCur);
            }
            psParentNode->byCamExist &= ~(DCF_CAM_EXIST_BASE << byCamID);
        }

        psSubNodePrev = psSubNodePrevTmp;
        psSubNodeCur  = psSubNodeCurTmp;
    }
    //if there's only one sub node, delete parent node
    if((bySubNodeCount == 1) && (!pDB->bFormatFreeEnable))
    {
        //unlink & free parent node
        PSDATETIMEFILE psParentNodePrev =psParentNode->pPrev;
        PSDATETIMEFILE psParentNodeNext =psParentNode->pNext;
        if(psParentNodePrev == NULL )
        {
        //Head
            //if pFileTail = pFileHead, it means only one node in DB
            if(pDB->pFileTail == pDB->pFileHead){
                pDB->pFileTail = psParentNodeNext;
            }
            pDB->pFileHead = psParentNodeNext;
            if(psParentNodeNext){
                psParentNodeNext->pPrev = NULL;
            }
            //prevent psLastAddParentNode point to illegal(released) location
            if(pDB->psLastAddParentNode != NULL)
            {
                pDB->psLastAddParentNode = pDB->pFileTail;
            }
        }
        else
        {
            psParentNodePrev->pNext = psParentNodeNext;
            if(psParentNodeNext){
                psParentNodeNext->pPrev = psParentNodePrev;
            }
            else{
                pDB->pFileTail = psParentNodePrev;
            }
            //prevent psLastAddParentNode point to illegal(released) location
            if(pDB->psLastAddParentNode != NULL)
            {
                pDB->psLastAddParentNode = psParentNodePrev;
            }
        }
        AHC_DCFDT_FileNodeFree((void*)psParentNode);
        pDB->ulTotalParentNodeNum--;
    }

    if(bFound == AHC_FALSE){
        AHC_DBG_MSG(1, "[Warning] Sub Node not found!!CamID %d\r\n", byCamID);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DeleteParentNode
//  Description : This function delete parent node by given parent node
//  @param[in] pDB          input DB
//  @param[in] psParentNode select psParentNode to delete
//------------------------------------------------------------------------------
static void AHC_DCFDT_DeleteParentNode(PSDATETIMEDCFDB pDB,
                                       PSDATETIMEFILE psParentNode)
{
    PSSUBNODE psSubNodeCur, psTempSubNode;
    psSubNodeCur = psParentNode->pCamNodeHead;
    while(psSubNodeCur)
    {
        psTempSubNode = psSubNodeCur->pNext;
        if(pDB->bFormatFreeEnable){
            psSubNodeCur->byFileAttr |= DCFDT_FILEATTR_HIDDEN;
        }
        else{
            AHC_DCFDT_FileNodeFree((void*)psSubNodeCur);
        }
        psSubNodeCur = psTempSubNode;
    }

    if(!pDB->bFormatFreeEnable)
    {
        //unlink & free parent node
        PSDATETIMEFILE psParentNodePrev = psParentNode->pPrev;
        PSDATETIMEFILE psParentNodeNext = psParentNode->pNext;
        if(psParentNodePrev == NULL )
        {
        //Head
            //if pFileTail = pFileHead, it means only one node in DB
            if(pDB->pFileTail == pDB->pFileHead){
                pDB->pFileTail = psParentNodeNext;
            }
            pDB->pFileHead = psParentNodeNext;
            if(psParentNodeNext){
                psParentNodeNext->pPrev = NULL;
            }
            //prevent psLastAddParentNode point to illegal(released) location
            if(pDB->psLastAddParentNode != NULL)
            {
                pDB->psLastAddParentNode = pDB->pFileTail;
            }
        }
        else
        {
            psParentNodePrev->pNext = psParentNodeNext;
            if(psParentNodeNext){
                psParentNodeNext->pPrev = psParentNodePrev;
            }
            else{
                pDB->pFileTail = psParentNodePrev;
            }
            //prevent psLastAddParentNode point to illegal(released) location
            if(pDB->psLastAddParentNode != NULL)
            {
                pDB->psLastAddParentNode = psParentNodePrev;
            }
        }
        AHC_DCFDT_FileNodeFree((void*)psParentNode);
        pDB->ulTotalParentNodeNum--;
    }
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_NodeOperation
//  Description : This function operates nodes by para Operation,
//                Insert : given sub node & DateTime, insert to proper position
//                Delete Sub : given CamID,psParentNode or nDateTime, delete its sub node
//                Delete Parent : given psParentNode or nDateTime, delete parent node
//  @param[in] pDB          input DB
//  @param[in] byCamID      select CamID to operate
//  @param[in] psParentNode select psParentNode
//  @param[in] psSubNode    select psSubNode
//  @param[in] byOperation  insert/ delete subnode/delete parent node
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_NodeOperation(void* pDBset,
                                 SNODE_OP_PAK    NodeOpPak)
{
    PSDATETIMEDCFDB pDB = (PSDATETIMEDCFDB)pDBset;
    UINT8           byCamID      = NodeOpPak.byCamID;
    SFILENAME_INFO  FileNameInfo = NodeOpPak.FileNameInfo;
    PSDATETIMEFILE  psParentNode = NodeOpPak.psParentNode;
    PSSUBNODE       psSubNode    = NodeOpPak.psSubNode;
    UINT8           byOperation  = NodeOpPak.byOperation;

    //notice this call back func use only for single cam
    if(AHC_DCFDT_CB_NodeOperation != NULL)
    {
        SFILENAME_INFO  nOpFileNameInfo;
        UINT8     byCBOperation;
        //assign datetime
        if(FileNameInfo.nDateTime != NULL && FileNameInfo.uiFileIndex != NULL){
            nOpFileNameInfo = FileNameInfo;}
        else{
            nOpFileNameInfo = psParentNode->FileNameInfo;}
        // if delete sub, in this case delete all
        if(byOperation == DCFDT_NODE_DELETE_SUB){
            byCBOperation = DCFDT_NODE_DELETE_PARENT;}
        else{
            byCBOperation = byOperation;
        }
        AHC_DCFDT_CB_NodeOperation(pDB->ubDBIndex, nOpFileNameInfo, byCBOperation);
    }
    switch(byOperation)
    {
        // input pDB, CamID, nDateTime, psSubNode, byOperation DCFDT_NODE_INSERT
        case DCFDT_NODE_INSERT:
        {
            if( pDB->pFileHead == NULL )
            {
                PSDATETIMEFILE psParentNode;
                psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                if(psParentNode == NULL )
                {
                    AHC_DBG_MSG(1, "%s: Failed!!DCFDT_NODE_INSERT\r\n", __FUNCTION__);
                    return AHC_FALSE;
                }
                //First
                psParentNode->pCamNodeHead = psSubNode;
                psParentNode->FileNameInfo.nDateTime = FileNameInfo.nDateTime;
                psParentNode->FileNameInfo.uiFileIndex = DCFDT_FILEINDEX_INVALID;
                if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                    psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                }
                pDB->pFileHead = psParentNode;
                pDB->pFileTail = psParentNode;
                pDB->ulTotalParentNodeNum++;
            }
            else
            {
                //Search from tail to head
                PSDATETIMEFILE psParentNodeCur = pDB->pFileTail;
                while(psParentNodeCur)
                {
                    //AHC_DBG_MSG(1, "psParentNodeCur 0x%x\r\n",psParentNodeCur);
                    //it means parent node exist,
                    if(FileNameInfo.nDateTime == psParentNodeCur->FileNameInfo.nDateTime)
                    {
                        PSSUBNODE psSubNodeCur;
                        PSSUBNODE psSubNodeTail;
                        psSubNodeCur = psParentNodeCur->pCamNodeHead;
                        while(psSubNodeCur)
                        {
                            //it means same parent node and same subnode(CamID)
                            if(psSubNodeCur->byCamID == byCamID)
                            {
                                AHC_DBG_MSG(1, "Duplicate FileName!!\r\n");
                                return AHC_FALSE;
                            }
                            if(psSubNodeCur->pNext == NULL){
                                psSubNodeTail = psSubNodeCur;
                            }
                            psSubNodeCur = psSubNodeCur->pNext;
                        }
                        //if there's no same CamID, insert subnode to parent node
                        {
                            if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                                psParentNodeCur->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                            }
                            psSubNodeTail->pNext = psSubNode;
                            break;
                        }
                    }
                    else if(FileNameInfo.nDateTime > psParentNodeCur->FileNameInfo.nDateTime)
                    {
                        PSDATETIMEFILE psParentNode;
                        psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                        //insert parent node
                        psParentNode->pPrev = psParentNodeCur;
                        if(psParentNodeCur == pDB->pFileTail)
                        {
                            // Insert at tail
                            pDB->pFileTail = psParentNode;
                        }
                        else
                        {
                            psParentNode->pNext = psParentNodeCur->pNext;
                            psParentNodeCur->pNext->pPrev= psParentNode;
                        }
                        psParentNodeCur->pNext = psParentNode;
                        //insert sub node and set date time
                        psParentNode->pCamNodeHead = psSubNode;
                        psParentNode->FileNameInfo.nDateTime = FileNameInfo.nDateTime;
                        psParentNode->FileNameInfo.uiFileIndex = DCFDT_FILEINDEX_INVALID;
                        if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                            psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                        }
                        pDB->ulTotalParentNodeNum++;
                        break;
                    }
                    psParentNodeCur = psParentNodeCur->pPrev;
                }
                //add at head
                if( psParentNodeCur == NULL )
                {

                    PSDATETIMEFILE psParentNode;
                    psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                    //insert parent node
                    psParentNode->pPrev     = NULL;
                    psParentNode->pNext     = pDB->pFileHead;
                    if( pDB->pFileHead == NULL ) {
                        pDB->pFileHead = psParentNode;
                    }
                    else {
                        pDB->pFileHead->pPrev = psParentNode;
                    }
                    pDB->pFileHead = psParentNode;
                    //insert sub node and set date time
                    psParentNode->pCamNodeHead = psSubNode;
                    psParentNode->FileNameInfo.nDateTime = FileNameInfo.nDateTime;
                    psParentNode->FileNameInfo.uiFileIndex = DCFDT_FILEINDEX_INVALID;
                    if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                        psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                    }
                    pDB->ulTotalParentNodeNum++;
                }
            }
        }
        break;
        // input pDB, CamID,psParentNode or nDateTime, byOperation DCFDT_NODE_DELETE_SUB
        case DCFDT_NODE_DELETE_SUB:
        {
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else if(psParentNode != NULL)
            {
                if(!AHC_DCFDT_DeleteSubNode(pDB, byCamID, psParentNode)){
                    AHC_DBG_MSG(1, "Delete SubNode failed, CamID %d\r\n", byCamID);
                }
            }
            else
            {
                //Search from head to tail
                AHC_BOOL  bFound = AHC_FALSE;
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.nDateTime == FileNameInfo.nDateTime)
                    {
                        bFound = AHC_TRUE;
                        if(!AHC_DCFDT_DeleteSubNode(pDB, byCamID, psParentNodeCur)){
                            AHC_DBG_MSG(1, "Delete SubNode failed, CamID %d\r\n", byCamID);
                        }
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
                if(bFound == AHC_FALSE){
                    AHC_DBG_MSG(1, "[Warning] Parent Node not found!!CamID %d DateTime %d\r\n", byCamID, FileNameInfo.nDateTime);
                }
            }
        }
        break;
        // input pDB,psParentNode or nDateTime, byOperation DCFDT_NODE_DELETE_PARENT
        case DCFDT_NODE_DELETE_PARENT:
        {
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else if(psParentNode != NULL)
            {
                AHC_DCFDT_DeleteParentNode(pDB, psParentNode);
            }
            else
            {
                //Search from head to tail
                AHC_BOOL  bFound = AHC_FALSE;
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.nDateTime == FileNameInfo.nDateTime)
                    {
                        bFound = AHC_TRUE;
                        AHC_DCFDT_DeleteParentNode(pDB, psParentNodeCur);
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
                if(bFound == AHC_FALSE){
                    AHC_DBG_MSG(1, "[Warning] Parent Node not found!!CamID %d DateTime %d\r\n", byCamID, FileNameInfo.nDateTime);
                }
            }
        }
        break;
        case DCDFT_NODE_UPDATE:
        {
            PSDATETIMEFILE psParentNodeCur = pDB->pFileTail;
            AHC_BOOL       bFound = AHC_FALSE;
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else
            {
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.nDateTime == FileNameInfo.nDateTime)
                    {
                        PSSUBNODE psSubNodeCur = psParentNodeCur->pCamNodeHead;
                        while(psSubNodeCur)
                        {
                            //node found, update psSubNodeCur data
                            if(psSubNodeCur->byCamID == byCamID)
                            {
                                psSubNodeCur->nSizeInCluster = psSubNode->nSizeInCluster;
                                psSubNodeCur->byFileAttr     = psSubNode->byFileAttr;
                                bFound = AHC_TRUE;
                                break;
                            }
                            psSubNodeCur = psSubNodeCur->pNext;
                        }
                        if(bFound)
                            break;
                    }
                    psParentNodeCur = psParentNodeCur->pPrev;
                }
            }
            if(bFound == AHC_FALSE){
                AHC_DBG_MSG(1, "Update Node failed, Node not found!\r\n");
            }
        }
        break;
        default:
        break;
    }
    return AHC_TRUE;
}
//
AHC_BOOL AHC_DCFDT_NodeOperation_Index(void* pDBset,
                                       SNODE_OP_PAK    NodeOpPak)
{
    PSDATETIMEDCFDB pDB = (PSDATETIMEDCFDB)pDBset;
    UINT8           byCamID      = NodeOpPak.byCamID;
    SFILENAME_INFO  FileNameInfo = NodeOpPak.FileNameInfo;
    PSDATETIMEFILE  psParentNode = NodeOpPak.psParentNode;
    PSSUBNODE       psSubNode    = NodeOpPak.psSubNode;
    UINT8           byOperation  = NodeOpPak.byOperation;
    PSDATETIMEFILE  psTmpParentNode = NULL; //for update last add parent node

    UINT32 uiOffsetFileIndex; //to cheat node operation

    uiOffsetFileIndex = AHC_DCFDT_RecalculateIndexByOffset(pDB->FileIndexStruct, FileNameInfo.uiFileIndex);
    //notice this call back func use only for single cam
    //TBD, the interface should change!!!!Chuni Li
    if(AHC_DCFDT_CB_NodeOperation != NULL)
    {
        SFILENAME_INFO  nOpFileNameInfo;
        UINT8     byCBOperation;
        //assign datetime
        if(FileNameInfo.nDateTime != NULL){
            nOpFileNameInfo = FileNameInfo;}
        else{
            nOpFileNameInfo = psParentNode->FileNameInfo;}
        // if delete sub, in this case delete all
        if(byOperation == DCFDT_NODE_DELETE_SUB){
            byCBOperation = DCFDT_NODE_DELETE_PARENT;}
        else{
            byCBOperation = byOperation;
        }
        AHC_DCFDT_CB_NodeOperation(pDB->ubDBIndex, nOpFileNameInfo, byCBOperation);
    }
    ///
    switch(byOperation)
    {
        // input pDB, CamID, nDateTime, psSubNode, byOperation DCFDT_NODE_INSERT
        case DCFDT_NODE_INSERT:
        {
            if( pDB->pFileHead == NULL )
            {
                PSDATETIMEFILE psParentNode;
                psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                if(psParentNode == NULL )
                {
                    AHC_DBG_MSG(1, "%s: Failed!!DCFDT_NODE_INSERT\r\n", __FUNCTION__);
                    return AHC_FALSE;
                }
                //First
                psParentNode->pCamNodeHead = psSubNode;
                psParentNode->FileNameInfo = FileNameInfo;
                if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                    psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                }
                pDB->pFileHead = psParentNode;
                pDB->pFileTail = psParentNode;
                pDB->ulTotalParentNodeNum++;
                //if master cam && not hidden , record its mode
                if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                    psTmpParentNode = psParentNode;
                    AHC_DCFDT_FileIndexCtrl(pDB, &(pDB->pFileHead->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_SET_DELINDEX);
                }
            }
            else
            {
                //Search from tail to head
                PSDATETIMEFILE psParentNodeCur = pDB->pFileTail;
                UINT32 uiParentOffsetIndex;
                while(psParentNodeCur)
                {
                    //AHC_DBG_MSG(1, "psParentNodeCur 0x%x\r\n",psParentNodeCur);
                    //it means parent node exist,
                    uiParentOffsetIndex = AHC_DCFDT_RecalculateIndexByOffset(pDB->FileIndexStruct, psParentNodeCur->FileNameInfo.uiFileIndex);
                    if(uiOffsetFileIndex == uiParentOffsetIndex &&
                       psParentNodeCur->FileNameInfo.nDateTime == FileNameInfo.nDateTime)
                    {
                        PSSUBNODE psSubNodeCur;
                        PSSUBNODE psSubNodeTail = NULL;
                        psSubNodeCur = psParentNodeCur->pCamNodeHead;
                        while(psSubNodeCur)
                        {
                            //it means same parent node and same subnode(CamID)
                            if(psSubNodeCur->byCamID == byCamID)
                            {
                                char     szFilepath[DCF_MAX_FILE_NAME_SIZE];
                                AHC_BOOL bReadOnly;
                                AHC_DBG_MSG(1, "Duplicate Index!!\r\n");
                                //1.spell old path
                                if(!AHC_DCFDT_GetFullPathByParentNode(pDB, byCamID, psParentNodeCur, szFilepath, DCF_MAX_FILE_NAME_SIZE ) )
                                {
                                    return AHC_FALSE;
                                }
                                //2.delete old file in FS
                                bReadOnly = (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
                                if(!AIHC_DCFDT_DeleteFileInFS(pDB, szFilepath, bReadOnly))
                                {
                                    return AHC_FALSE;
                                }
                                //3.give new node data to old node and release new sub node
                                psParentNodeCur->FileNameInfo = FileNameInfo;
                                psSubNodeCur->byFileAttr = psSubNode->byFileAttr;
                                psSubNodeCur->byFileType = psSubNode->byFileType;
                                psSubNodeCur->nSizeInCluster = psSubNode->nSizeInCluster;
                                AHC_DCFDT_FileNodeFree((void*)psSubNode);
                                //if master cam && not hidden , record its mode
                                if((psSubNodeCur->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNodeCur->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                                    psTmpParentNode = psParentNodeCur;
                                }
                                return AHC_FALSE;
                            }
                            if(psSubNodeCur->pNext == NULL){
                                psSubNodeTail = psSubNodeCur;
                            }
                            psSubNodeCur = psSubNodeCur->pNext;
                        }
                        //if there's no same CamID, insert subnode to parent node
                        if(psSubNodeTail != NULL)
                        {
                            if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                                psParentNodeCur->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                            }
                            psSubNodeTail->pNext = psSubNode;
                            //if master cam && not hidden , record its mode
                            if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                                psTmpParentNode = psParentNodeCur;
                            }
                            break;
                        }
                    }
                    else if(uiOffsetFileIndex > uiParentOffsetIndex ||
                            (uiOffsetFileIndex == uiParentOffsetIndex && FileNameInfo.nDateTime > psParentNodeCur->FileNameInfo.nDateTime))
                    {
                        PSDATETIMEFILE psParentNode;
                        psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                        //insert parent node
                        psParentNode->pPrev = psParentNodeCur;
                        if(psParentNodeCur == pDB->pFileTail)
                        {
                            // Insert at tail
                            pDB->pFileTail = psParentNode;
                        }
                        else
                        {
                            psParentNode->pNext = psParentNodeCur->pNext;
                            psParentNodeCur->pNext->pPrev= psParentNode;
                        }
                        psParentNodeCur->pNext = psParentNode;
                        //insert sub node and set date time
                        psParentNode->pCamNodeHead = psSubNode;
                        psParentNode->FileNameInfo = FileNameInfo;
                        if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                            psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                        }
                        //if master cam && not hidden , record its mode
                        if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                            psTmpParentNode = psParentNode;
                        }
                        pDB->ulTotalParentNodeNum++;
                        break;
                    }
                    psParentNodeCur = psParentNodeCur->pPrev;
                }
                //add at head
                if( psParentNodeCur == NULL )
                {

                    PSDATETIMEFILE psParentNode;
                    psParentNode = (PSDATETIMEFILE)AHC_DCFDT_FileNodeAlloc();
                    //insert parent node
                    psParentNode->pPrev     = NULL;
                    psParentNode->pNext     = pDB->pFileHead;
                    if( pDB->pFileHead == NULL ) {
                        pDB->pFileHead = psParentNode;
                    }
                    else {
                        pDB->pFileHead->pPrev = psParentNode;
                    }
                    pDB->pFileHead = psParentNode;
                    //insert sub node and set date time
                    psParentNode->pCamNodeHead = psSubNode;
                    psParentNode->FileNameInfo = FileNameInfo;
                    if(!(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                        psParentNode->byCamExist |= (DCF_CAM_EXIST_BASE << byCamID);
                    }
                    pDB->ulTotalParentNodeNum++;
                    if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN)){
                        AHC_DCFDT_FileIndexCtrl(pDB, &(pDB->pFileHead->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_SET_DELINDEX);
                        psTmpParentNode = psParentNode;
                    }
                }
            }
            if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN) && (psTmpParentNode != NULL)){
                AHC_DCFDT_FileIndexCtrl(pDB, &(FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_UPDATE_ADDINDEX);
                pDB->psLastAddParentNode = psTmpParentNode;
            }
        }
        break;
        // input pDB, CamID,psParentNode or nDateTime, byOperation DCFDT_NODE_DELETE_SUB
        case DCFDT_NODE_DELETE_SUB:
        {
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else if(psParentNode != NULL)
            {
                //delete index would be update when all cams are be deleted
                if((!pDB->bFormatFreeEnable) &&
                   (psParentNode->pCamNodeHead->pNext == NULL))
                {
                    AHC_DCFDT_FileIndexCtrl(pDB, &(psParentNode->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_UPDATE_DELINDEX);
                }
                if(!AHC_DCFDT_DeleteSubNode(pDB, byCamID, psParentNode)){
                    AHC_DBG_MSG(1, "Delete SubNode failed, CamID %d\r\n", byCamID);
                }
            }
            else
            {
                //Search from head to tail
                AHC_BOOL  bFound = AHC_FALSE;
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.uiFileIndex == FileNameInfo.uiFileIndex)
                    {
                        bFound = AHC_TRUE;
                        //delete index would be update when all cams are be deleted
                        if((!pDB->bFormatFreeEnable) &&
                           (psParentNode->pCamNodeHead->pNext == NULL))
                        {
                            AHC_DCFDT_FileIndexCtrl(pDB, &(psParentNode->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_UPDATE_DELINDEX);
                        }
                        if(!AHC_DCFDT_DeleteSubNode(pDB, byCamID, psParentNodeCur)){
                            AHC_DBG_MSG(1, "Delete SubNode failed, CamID %d\r\n", byCamID);
                        }
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
                if(bFound == AHC_FALSE){
                    AHC_DBG_MSG(1, "[Warning] Parent Node not found!!CamID %d DateTime %d\r\n", byCamID, FileNameInfo.nDateTime);
                }
            }
        }
        break;
        // input pDB,psParentNode or nDateTime, byOperation DCFDT_NODE_DELETE_PARENT
        case DCFDT_NODE_DELETE_PARENT:
        {
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else if(psParentNode != NULL)
            {
                if(!pDB->bFormatFreeEnable && byCamID == DCFDT_FILEINDEX_MASTERCAMID){
                    AHC_DCFDT_FileIndexCtrl(pDB, &(psParentNode->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_UPDATE_DELINDEX);
                }
                AHC_DCFDT_DeleteParentNode(pDB, psParentNode);
            }
            else
            {
                //Search from head to tail
                AHC_BOOL  bFound = AHC_FALSE;
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.uiFileIndex == FileNameInfo.uiFileIndex)
                    {
                        bFound = AHC_TRUE;
                        if(!pDB->bFormatFreeEnable && psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID){
                            AHC_DCFDT_FileIndexCtrl(pDB, &(psParentNode->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_UPDATE_DELINDEX);
                        }
                        AHC_DCFDT_DeleteParentNode(pDB, psParentNodeCur);
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
                if(bFound == AHC_FALSE){
                    AHC_DBG_MSG(1, "[Warning] Parent Node not found!!CamID %d DateTime %d\r\n", byCamID, FileNameInfo.nDateTime);
                }
            }
        }
        break;
        case DCDFT_NODE_UPDATE:
        {
            PSDATETIMEFILE psParentNodeCur = pDB->pFileTail;
            AHC_BOOL       bFound = AHC_FALSE;
            if( pDB->pFileHead == NULL )
            {
                AHC_DBG_MSG(1, "%s Failed, pFileHead == NULL", __FUNCTION__);
            }
            else
            {
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.uiFileIndex == FileNameInfo.uiFileIndex)
                    {
                        PSSUBNODE psSubNodeCur = psParentNodeCur->pCamNodeHead;
                        while(psSubNodeCur)
                        {
                            //node found, update psSubNodeCur data
                            if(psSubNodeCur->byCamID == byCamID)
                            {
                                psSubNodeCur->nSizeInCluster = psSubNode->nSizeInCluster;
                                psSubNodeCur->byFileAttr     = psSubNode->byFileAttr;
                                bFound = AHC_TRUE;
                                break;
                            }
                            psSubNodeCur = psSubNodeCur->pNext;
                        }
                        if(bFound)
                            break;
                    }
                    psParentNodeCur = psParentNodeCur->pPrev;
                }
            }
            if(bFound == AHC_FALSE){
                AHC_DBG_MSG(1, "Update Node failed, Node not found!\r\n");
            }

        }
        break;
        default:
        break;
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_UpdateDBStatistics
//  Description : This function updates statistics of DB by para Operation
//  @param[in] pDB          input DB
//  @param[in] byCamID      select CamID to operate
//  @param[in] psSubNode    select psSubNode
//  @param[in] byOperation  Add/Delete
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_UpdateDBStatistics(PSDATETIMEDCFDB pDB,
                                      UINT8 byCamID,
                                      PSSUBNODE psSubNode,
                                      UINT8 byOperation)
{
    ULONG ulSizeAligned = psSubNode->nSizeInCluster * pDB->ulClusterSize;
    switch(byOperation)
    {
        case DCFDT_STATISTICS_ADD:
        {
            if( psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN )
            {
                pDB->ulTotalHiddenNumByCam[byCamID]++;
            }
            else
            {
                pDB->ulTotalObjectNum++;
                pDB->ulTotalObjectNumByCam[byCamID]++;
                pDB->ullTotalObjectSize += ulSizeAligned;

                if( psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY )
                {
                    pDB->ulTotalLockedObjects++;
                    pDB->ullTotalLockedObjectSize += ulSizeAligned;
                    pDB->ullLockedObjectNum[psSubNode->byFileType]++;
                    pDB->ullLockedObjectSize[psSubNode->byFileType]+= ulSizeAligned;

                }
                else
                {
                    pDB->ulTotalUnlockedObjects++;
                    pDB->ullTotalUnlockedObjectSize += ulSizeAligned;

                    pDB->ullUnlockedObjectNum[psSubNode->byFileType]++;
                    pDB->ullUnlockedObjectSize[psSubNode->byFileType]+= ulSizeAligned;
                }
            }
        }
        break;
        case DCFDT_STATISTICS_UPDATE:
        {
            pDB->ullTotalObjectSize += ulSizeAligned;
            if( psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY )
            {
                pDB->ullTotalLockedObjectSize += ulSizeAligned;
                pDB->ullLockedObjectSize[psSubNode->byFileType]+= ulSizeAligned;

            }
            else
            {
                pDB->ullTotalUnlockedObjectSize += ulSizeAligned;
                pDB->ullUnlockedObjectSize[psSubNode->byFileType]+= ulSizeAligned;
            }
        }
        break;
        case DCFDT_STATISTICS_DELETE:
        {
            if( psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN )
            {
                pDB->ulTotalHiddenNumByCam[byCamID]--;
            }
            else
            {
                pDB->ulTotalObjectNum--;
                pDB->ulTotalObjectNumByCam[byCamID]--;
                pDB->ullTotalObjectSize -= ulSizeAligned;
                if(  psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY  )
                {
                    pDB->ulTotalLockedObjects--;
                    pDB->ullTotalLockedObjectSize -= ulSizeAligned;

                    pDB->ullLockedObjectNum[psSubNode->byFileType]--;
                    pDB->ullLockedObjectSize[psSubNode->byFileType]-= ulSizeAligned;

                }
                else
                {
                    pDB->ulTotalUnlockedObjects--;
                    pDB->ullTotalUnlockedObjectSize -= ulSizeAligned;

                    pDB->ullUnlockedObjectNum[psSubNode->byFileType]--;
                    pDB->ullUnlockedObjectSize[psSubNode->byFileType]-= ulSizeAligned;
                }
            }
        }
        break;
        case DCFDT_STATISTICS_RESET:
        {
            pDB->ulTotalObjectNum           = 0;
            pDB->ulTotalParentNodeNum       = 0;
            pDB->ullTotalObjectSize         = 0;
            pDB->ulTotalLockedObjects       = 0;
            pDB->ullTotalLockedObjectSize   = 0;
            pDB->ulTotalUnlockedObjects     = 0;
            pDB->ullTotalUnlockedObjectSize = 0;
            MEMSET(pDB->ulTotalObjectNumByCam, 0, sizeof(pDB->ulTotalObjectNumByCam));
            MEMSET(pDB->ullUnlockedObjectNum,  0, sizeof(pDB->ullUnlockedObjectNum));
            MEMSET(pDB->ullUnlockedObjectSize, 0, sizeof(pDB->ullUnlockedObjectSize));
            MEMSET(pDB->ullLockedObjectNum,    0, sizeof(pDB->ullLockedObjectNum));
            MEMSET(pDB->ullLockedObjectSize,   0, sizeof(pDB->ullLockedObjectSize));
        }
        break;
        case DCFDT_STATISTICS_READONLY:
        {
            UINT8 byFileType;
            byFileType = psSubNode->byFileType;

            pDB->ulTotalLockedObjects++;
            pDB->ullTotalLockedObjectSize += ulSizeAligned;

            pDB->ullLockedObjectNum[byFileType]++;
            pDB->ullLockedObjectSize[byFileType] += ulSizeAligned;

            pDB->ulTotalUnlockedObjects--;
            pDB->ullTotalUnlockedObjectSize -= ulSizeAligned;

            pDB->ullUnlockedObjectNum[byFileType]--;
            pDB->ullUnlockedObjectSize[byFileType] -= ulSizeAligned;
        }
        break;
        case DCFDT_STATISTICS_NON_READONLY:
        {
            UINT8 byFileType;
            byFileType = psSubNode->byFileType;

            pDB->ulTotalLockedObjects--;
            pDB->ullTotalLockedObjectSize -= ulSizeAligned;

            pDB->ullLockedObjectNum[byFileType]--;
            pDB->ullLockedObjectSize[byFileType] -= ulSizeAligned;

            pDB->ulTotalUnlockedObjects++;
            pDB->ullTotalUnlockedObjectSize += ulSizeAligned;

            pDB->ullUnlockedObjectNum[byFileType]++;
            pDB->ullUnlockedObjectSize[byFileType] += ulSizeAligned;
        }
        break;
        default:
        break;
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_ParseFileName
//  Description : This function parse filename, and get the datetime, ischarlock by filename type
//  @param[in]  pDB          input DB
//  @param[in]  byCamID      given camID
//  @param[in]  szFilename   input filename
//  @param[out] nDateTime    out datetime
//  @param[out] bIsCharLock  is the file charlock?
//  @retval     AHC_TRUE     Success. the input filename is legal
//  @retval     AHC_FALSE    Failed.  the input filename is illegal
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_ParseFileName(PSDATETIMEDCFDB pDB,
                                 UINT8           byCamID,
                                 char            *szFilename,
                                 SFILENAME_INFO  *FileNameInfo,
                                 AHC_BOOL        *bIsCharLock)
{
    char    szCmpString[DCF_MAX_FILE_NAME_SIZE] = {0};
    UINT32  uiTimeStrLen;
    switch(pDB->byFileNamingType)
    {
        case DCFDT_FILENAME_NAMING_STANDARD:
        {
            // 1.compare FreeChar
            MEMCPY(szCmpString, szFilename, sizeof(pDB->szFileFreeChar[byCamID]));
            *bIsCharLock = AHC_FALSE;
            if(!AHC_DCFDT_TemplateCmp(szCmpString, pDB->szFileFreeChar[byCamID]))
            {
                if(!AHC_DCFDT_TemplateCmp(szCmpString, DCFDT_FREECHAR_LOCK))
                {
                    //AHC_DBG_MSG(1, "0template string not matched!! %s\n", szFilename);
                    return AHC_FALSE;
                }
                else
                {
                    *bIsCharLock = AHC_TRUE;
                }
            }
            // 2.get timeformat and compare timeformat and get time
            if(!AHC_DCFDT_GetDateTimeByFileName(pDB, szFilename, STRLEN(pDB->szFileFreeChar[byCamID]), &(FileNameInfo->nDateTime), &uiTimeStrLen))
            {
                //AHC_DBG_MSG(1, "1template string not matched!! %s\n", szFilename);
                return AHC_FALSE;
            }
            // 3.compare FixedChar
            MEMSET(szCmpString, 0, sizeof(szCmpString));
            MEMCPY(szCmpString, (szFilename + STRLEN(pDB->szFileFreeChar[byCamID]) + uiTimeStrLen), STRLEN(pDB->szFileFixedChar[byCamID]));
            if(!AHC_DCFDT_TemplateCmp(szCmpString, pDB->szFileFixedChar[byCamID]))
            {
                //AHC_DBG_MSG(1, "2template string not matched!! %s\n", szFilename);
                return AHC_FALSE;
            }
            FileNameInfo->uiFileIndex = DCFDT_FILEINDEX_INVALID;
        }
        break;
        case DCFDT_FILENAME_NAMING_SINGLE_CAM:
        {
            // 1.compare FreeChar
            MEMCPY(szCmpString, szFilename, sizeof(pDB->szFileFreeChar[byCamID]));
            *bIsCharLock = AHC_FALSE;
            if(!AHC_DCFDT_TemplateCmp(szCmpString, pDB->szFileFreeChar[byCamID]))
            {
                if(!AHC_DCFDT_TemplateCmp(szCmpString, DCFDT_FREECHAR_LOCK))
                {
                    //AHC_DBG_MSG(1, "0template string not matched!! %s\n", szFilename);
                    return AHC_FALSE;
                }
                else
                {
                    *bIsCharLock = AHC_TRUE;
                }
            }
            // 2.get timeformat and compare timeformat and get time
            if(!AHC_DCFDT_GetDateTimeByFileName(pDB, szFilename, STRLEN(pDB->szFileFreeChar[byCamID]), &(FileNameInfo->nDateTime), &uiTimeStrLen))
            {
                //AHC_DBG_MSG(1, "1template string not matched!! %s\n", szFilename);
                return AHC_FALSE;
            }
            FileNameInfo->uiFileIndex = DCFDT_FILEINDEX_INVALID;
        }
        break;
        case DCFDT_FILENAME_NAMING_BYINDEX:
        {
            UINT32 uiFileIndex;
            UINT32 uiMaxNum = DCFDT_FILEINDEX_MAXNUM;
            UINT32 uiOrder = 0;
            char   szDash = '-';
            UINT8  i;
            // 1.compare FreeChar
            MEMCPY(szCmpString, szFilename, sizeof(pDB->szFileFreeChar[byCamID]));
            *bIsCharLock = AHC_FALSE;
            if(!AHC_DCFDT_TemplateCmp(szCmpString, pDB->szFileFreeChar[byCamID]))
            {
                if(!AHC_DCFDT_TemplateCmp(szCmpString, DCFDT_FREECHAR_LOCK))
                {
                    //AHC_DBG_MSG(1, "0template string not matched!! %s\n", szFilename);
                    return AHC_FALSE;
                }
                else
                {
                    *bIsCharLock = AHC_TRUE;
                }
            }
            // 2.get timeformat and compare timeformat and get time
            if(!AHC_DCFDT_GetDateTimeByFileName(pDB, szFilename, STRLEN(pDB->szFileFreeChar[byCamID]), &(FileNameInfo->nDateTime), &uiTimeStrLen))
            {
                //AHC_DBG_MSG(1, "1template string not matched!! %s\n", szFilename);
                return AHC_FALSE;
            }
            //cmp str "-"
            MEMSET(szCmpString, 0, sizeof(szCmpString));
            MEMCPY(szCmpString, (szFilename + STRLEN(pDB->szFileFreeChar[byCamID]) + uiTimeStrLen), 1); //hard code
            if(!AHC_DCFDT_TemplateCmp(szCmpString, &szDash))
            {
                return AHC_FALSE;
            }
            //calculate order
            for (;;)
            {
                uiMaxNum /= 10;
                uiOrder++;
                if (uiMaxNum == 0) break;
            }
            //cpy str
            MEMSET(szCmpString, 0, sizeof(szCmpString));
            MEMCPY(szCmpString, (szFilename + STRLEN(pDB->szFileFreeChar[byCamID]) + uiTimeStrLen + 1), uiOrder); //hard code
            //check every char is legal?
            for(i = 0; i < uiOrder; i++)
            {
                if((szCmpString[i] < '0') || (szCmpString[i] > '9'))
                {
                    return AHC_FALSE;
                }
            }
            //3.get File Index
            sscanfl(szCmpString , "%d", &uiFileIndex);
            if(uiFileIndex <= DCFDT_FILEINDEX_MAXNUM){
                FileNameInfo->uiFileIndex = uiFileIndex;
            }else{
                return AHC_FALSE;
            }
            // 3.compare FixedChar
            MEMSET(szCmpString, 0, sizeof(szCmpString));
            MEMCPY(szCmpString, (szFilename + STRLEN(pDB->szFileFreeChar[byCamID]) + uiTimeStrLen + 1 + uiOrder), STRLEN(pDB->szFileFixedChar[byCamID]));
            if(!AHC_DCFDT_TemplateCmp(szCmpString, pDB->szFileFixedChar[byCamID]))
            {
                //AHC_DBG_MSG(1, "2template string not matched!! %s\n", szFilename);
                return AHC_FALSE;
            }
            //check next str is legal?
            if(AHC_Strncmp(szFilename + STRLEN(pDB->szFileFreeChar[byCamID]) + uiTimeStrLen + 1 + uiOrder + STRLEN(pDB->szFileFixedChar[byCamID]), ".", 1))
            {
                return AHC_FALSE;
            }
        }
        break;
        default:
            AHC_DBG_MSG(1, "UnIdentify FileNameType");
            return AHC_FALSE;
        break;
    }
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_AddFile(new)
//  Description : This function adds file by given CamID, filename, filesize, attr
//  @param[in] szFilename  file name
//  @param[in] byCamID     byCamID
//  @param[in] ulSize      ulSize
//  @param[in] sFileAttrib sFileAttrib hidden/readonly
//------------------------------------------------------------------------------
void AHC_DCFDT_AddFile(PSDATETIMEDCFDB pDB,
                       UINT8 byCamID,
                       char* szFilename,
                       UINT32 ulSize,
                       AHC_FS_ATTRIBUTE sFileAttrib)
{
    PSDATETIMEFILE psParentNode;
    PSSUBNODE      psSubNode;
    UINT8          byFileType;
    ULONG          ulSizeAligned;
    AHC_BOOL       bIsCharLock = AHC_FALSE; //default
    SFILENAME_INFO FileNameInfo;
    SNODE_OP_PAK   NodeOpPak;
    // check file type
    byFileType = AHC_DCFDT_GetFileType(szFilename);
    if( byFileType == DCFDT_UNKNOW_TYPE )
    {
        // Unknown type
        AHC_DBG_MSG(1, "AHC_DCFDT_AddFile: Unknow Type %s\n", szFilename );
        return;
    }

    //AHC_DCFDT_ParseFileName
    if(!AHC_DCFDT_ParseFileName(pDB, byCamID, szFilename, &FileNameInfo, &bIsCharLock))
    {
        return;
    }
    psSubNode = (PSSUBNODE)AHC_DCFDT_FileNodeAlloc();
    psSubNode->byCamID = byCamID;
    if(bIsCharLock)
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_CHARLOCK;
    }
    psSubNode->byFileType = byFileType;
    if( sFileAttrib & AHC_FS_ATTR_READ_ONLY )
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_READONLY;
    }
    if( sFileAttrib & AHC_FS_ATTR_HIDDEN )
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_HIDDEN;
    }
    // fill Size
    ulSizeAligned = ALIGN_UP(ulSize, pDB->ulClusterSize);
    psSubNode->nSizeInCluster = ulSizeAligned/pDB->ulClusterSize;
    // Update DB statistics
    AHC_DCFDT_UpdateDBStatistics(pDB, byCamID, psSubNode, DCFDT_STATISTICS_ADD);
    //set NodeOpPak value
    {
        NodeOpPak.byCamID      = byCamID;
        NodeOpPak.FileNameInfo = FileNameInfo;
        NodeOpPak.psParentNode = NULL;
        NodeOpPak.psSubNode    = psSubNode;
        NodeOpPak.byOperation  = DCFDT_NODE_INSERT;
    }
    //Node Operation
    if(!pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak))
    {
        AHC_DCFDT_UpdateDBStatistics(pDB, byCamID, psSubNode, DCFDT_STATISTICS_DELETE);
        AHC_DCFDT_FileNodeFree((void*)psSubNode);
        AHC_DBG_MSG(1, "NodeOperation Failed!!\r\n");
        return;
    }
    //add get parent node by date
    {
        psParentNode = AHC_DCFDT_GetParentNodeByDateTime(pDB, FileNameInfo.nDateTime);
    }
    //Update LockFileTable
    if(bIsCharLock)
    {
        AIHC_DCFDT_UpdateLockFileTable(psParentNode, NULL, DCFDT_LOCKTABLE_LOCK);
    }
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_UpdateFileData
//  Description : This function updates file data by given CamID, filename, filesize, attr
//                The node would not be insert/delete
//  @param[in] szFilename  file name
//  @param[in] byCamID     byCamID
//  @param[in] ulSize      ulSize
//  @param[in] sFileAttrib sFileAttrib hidden/readonly
//------------------------------------------------------------------------------
void AHC_DCFDT_UpdateFileData(PSDATETIMEDCFDB pDB,
                              UINT8 byCamID,
                              char* szFilename,
                              UINT32 ulSize,
                              AHC_FS_ATTRIBUTE sFileAttrib)
{
    PSDATETIMEFILE psParentNode;
    PSSUBNODE      psSubNode;
    UINT8          byFileType;
    ULONG          ulSizeAligned;
    AHC_BOOL       bIsCharLock = AHC_FALSE; //default
    SFILENAME_INFO FileNameInfo;
    SNODE_OP_PAK   NodeOpPak;
    // check file type
    byFileType = AHC_DCFDT_GetFileType(szFilename);
    if( byFileType == DCFDT_UNKNOW_TYPE )
    {
        // Unknown type
        AHC_DBG_MSG(1, "AHC_DCFDT_AddFile: Unknow Type %s\n", szFilename );
        return;
    }

    //AHC_DCFDT_ParseFileName
    if(!AHC_DCFDT_ParseFileName(pDB, byCamID, szFilename, &FileNameInfo, &bIsCharLock))
    {
        return;
    }
    psSubNode = (PSSUBNODE)AHC_DCFDT_FileNodeAlloc();
    psSubNode->byCamID = byCamID;
    if(bIsCharLock)
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_CHARLOCK;
    }
    psSubNode->byFileType = byFileType;
    if( sFileAttrib & AHC_FS_ATTR_READ_ONLY )
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_READONLY;
    }
    if( sFileAttrib & AHC_FS_ATTR_HIDDEN )
    {
        psSubNode->byFileAttr |= DCFDT_FILEATTR_HIDDEN;
    }
    // fill Size
    ulSizeAligned = ALIGN_UP(ulSize, pDB->ulClusterSize);
    psSubNode->nSizeInCluster = ulSizeAligned/pDB->ulClusterSize;
    // Update DB statistics
    AHC_DCFDT_UpdateDBStatistics(pDB, byCamID, psSubNode, DCFDT_STATISTICS_UPDATE);
    //set NodeOpPak value
    {
        NodeOpPak.byCamID      = byCamID;
        NodeOpPak.FileNameInfo = FileNameInfo;
        NodeOpPak.psParentNode = NULL;
        NodeOpPak.psSubNode    = psSubNode;
        NodeOpPak.byOperation  = DCDFT_NODE_UPDATE;
    }
    //Node Operation
    if(!pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak))
    {
        AHC_DCFDT_UpdateDBStatistics(pDB, byCamID, psSubNode, DCFDT_STATISTICS_DELETE);
        AHC_DCFDT_FileNodeFree((void*)psSubNode);
        AHC_DBG_MSG(1, "NodeOperation Failed!! %s\r\n", szFilename);
        return;
    }
    AHC_DCFDT_FileNodeFree((void*)psSubNode);
}
//  Function    : AHC_DCFDT_GetPathWithoutEXT
//  Description : This function creates full path without ext, it used for getname
//  @param[in] pDB          Input DB
//  @param[in] psRtcTime    RtcTime for filename
//  @param[out]szNameBuff   Full file path without ext
//  @param[out]FileName     File name without ext
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetPathWithoutEXT(PSDATETIMEDCFDB pDB, AHC_RTC_TIME* psRtcTime, char* szNameBuff, char* FileName)
{
    AHC_BOOL  bIsCharLock;
    SFILENAME_INFO  FileNameInfo;
    char*     pTemp;

    //check if RTC time valid
    if( !AHC_DT_IsDateValid( psRtcTime->uwYear - DCFDT_FILENAME_YEAR_OFFSET, psRtcTime->uwMonth, psRtcTime->uwDay ) ||
        !AHC_DT_IsTimeValid( psRtcTime->uwHour, psRtcTime->uwMinute, psRtcTime->uwSecond ) )
    {
        // Date or time is invalid.
        AHC_DBG_MSG(1, "%s: Date Time Valid\r\n", __FUNCTION__);
        return AHC_FALSE;
    }

    AHC_DCFDT_Lock(pDB);
    STRCPY( szNameBuff, pDB->szFolderPath[sDcfDtSet.m_byCurrCamID]);

    STRCAT( szNameBuff, "\\" );
    //transfer RTCtime to nDateTime

    //point to start of filename
    pTemp = szNameBuff + STRLEN(szNameBuff);
    //to create a normal file, so charlock is false
    bIsCharLock = AHC_FALSE;
    //transfer RTC time to DateTime
    FileNameInfo.nDateTime = AHC_DT_GetSecondsOffset(psRtcTime->uwYear,
                                                     psRtcTime->uwMonth,
                                                     psRtcTime->uwDay,
                                                     psRtcTime->uwHour,
                                                     psRtcTime->uwMinute,
                                                     psRtcTime->uwSecond);
    AHC_DCFDT_FileIndexCtrl(pDB, &FileNameInfo.uiFileIndex, DCFDT_INDEX_CTL_GET_ADDINDEX);
    //create file name
    if(!AIHC_DCFDT_CreateFilename(pDB, sDcfDtSet.m_byCurrCamID, FileNameInfo, pTemp, bIsCharLock))
    {
        AHC_DBG_MSG(1, "%s CreateFilename failed\r\n", __FUNCTION__);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    if(FileName != NULL)
    {
        STRCPY( FileName, pTemp );
    }
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_InitContiShotFileName_IndexMode
//  Description : This function init filenames and store in contishot info
//  @param[in] psRtcTime     input RtcTime
//------------------------------------------------------------------------------
void AHC_DCFDT_InitContiShotFileName_IndexMode(PSDATETIMEDCFDB pDB, AHC_RTC_TIME* psRtcTime)
{
    char   szFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char   szFileName[DCF_MAX_FILE_NAME_SIZE]={0};
    UINT16 uwDirKey = 0;
    UINT8  byCurCamID = DCF_CAM_FRONT;
    AHC_BOOL bGetPathDone[DCFDT_CAM_NUM] = {0};
    UINT8  byDoneNum = 0;
    UINT8  i;
    UINT8  byFileCnt[DCFDT_CAM_NUM] = {0};
    while(1)
    {
        memset(szFileName, 0, sizeof(szFileName));
        sDcfDtSet.m_byCurrCamID = byCurCamID; //set curCamID
        if(byFileCnt[byCurCamID] <= pDB->m_ContiShotInfo.byTotalShotNum[byCurCamID] - 1)
        {
            //getpath
            AHC_DCFDT_GetPathWithoutEXT(pDB, psRtcTime, szFullPath, szFileName);
            memcpy(pDB->m_ContiShotInfo.CSFilename[byFileCnt[byCurCamID]][byCurCamID],
                   szFileName, STRLEN(szFileName));
            //AHC_DBG_MSG(1, "==[%d][%d] %s\r\n", byFileCnt[byCurCamID], byCurCamID, szFileName);
            //cam ctrl and file num ctrl
            byFileCnt[byCurCamID]++;
        }
        else
        {
            bGetPathDone[byCurCamID] = AHC_TRUE;
        }
        //check is all bGetPathDone are finished?
        for(i = 0; i < DCFDT_CAM_NUM; i++)
        {
            if(bGetPathDone[i] == AHC_TRUE){
                byDoneNum++;
            }
        }
        //if all finished, then break
        if(byDoneNum == DCFDT_CAM_NUM){
            //AHC_DBG_MSG(1, "~=~=~=~=break~=~=~=~=~=~=\r\n");
            break;
        }
        else{
            byDoneNum = 0; //reset
        }
        //switch cam, if camID = max, turn to first cam
        //and preadd file
        byCurCamID++;
        if(byCurCamID == DCFDT_CAM_NUM){
            UINT8 byAddIndex = 0;
            byCurCamID = DCF_CAM_FRONT;
            //preadd all file in previus index
            for(i = 0; i < DCFDT_CAM_NUM; i++){
                byAddIndex = byFileCnt[i] - 1;
                if(pDB->m_ContiShotInfo.CSFilename[byAddIndex][i][0] != NULL){
                    memset(szFileName, 0, sizeof(szFileName));
                    memcpy(szFileName,
                           pDB->m_ContiShotInfo.CSFilename[byAddIndex][i],
                           sizeof(pDB->m_ContiShotInfo.CSFilename[byAddIndex][i]));
                    //add ext,tmp add "jpg", TBD.
                    STRCAT(szFileName, ".");
                    STRCAT(szFileName, m_DcfSupportFileType[DCF_OBG_JPG]);
                    //if camstatus does not exist, do not add file
                    if(pDB->byCamStatus & (DCF_CAM_EXIST_BASE << i)){
                        AIHC_DCFDT_PreAddFile(uwDirKey, szFileName);
                    }
                }
            }
        }
    }
    //set init == true
    pDB->m_ContiShotInfo.byIsInit = AHC_TRUE;

    return;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_CreateContiShotPathWithoutEXT
//  Description : This function creates Conti Shot name by given rtc time, and return fullspath and filename
//  @param[in] psRtcTime     input RtcTime
//  @param[out]FileFullPath  created fullpath
//  @param[out]FileName      created filename
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetContiShotPathWithoutEXT(PSDATETIMEDCFDB pDB, AHC_RTC_TIME* psRtcTime, char* szNameBuff, char* FileName)
{
    UINT8 i;
    UINT8 byCurShotCnt = pDB->m_ContiShotInfo.byCurShotCnt[sDcfDtSet.m_byCurrCamID];
    UINT8 byFileNameLen;
    UINT8 byCurCamID = sDcfDtSet.m_byCurrCamID;
    if(pDB->m_ContiShotInfo.byCurShotCnt[byCurCamID] >=
       pDB->m_ContiShotInfo.byTotalShotNum[byCurCamID]){
        AHC_DBG_MSG(1, "Warning CurShotCnt[%d]%d >= TotalShotNum[%d]%d\r\n",
               byCurCamID,
               pDB->m_ContiShotInfo.byCurShotCnt[byCurCamID],
               byCurCamID,
               pDB->m_ContiShotInfo.byTotalShotNum[byCurCamID]);
        AHC_DBG_MSG(1, "Please set shot mode again\r\n");
        return AHC_FALSE;
    }
    //do init
    if(pDB->m_ContiShotInfo.byIsInit != AHC_TRUE)
    {
        UINT8 x,y;
        AHC_DCFDT_InitContiShotFileName_IndexMode(pDB, psRtcTime);
        //for(x = 0; x < 10; x++){
        //  for(y = 0; y < 2; y++){
        //      AHC_DBG_MSG(1, "filename[%d][%d] %s\r\n", x, y, pDB->m_ContiShotInfo.CSFilename[x][y]);
        //  }
        //}
    }
    //AHC_DBG_MSG(1, "CSFilename[%d][%d] %s\r\n", byCurShotCnt, byCurCamID, pDB->m_ContiShotInfo.CSFilename[byCurShotCnt][byCurCamID]);
    byFileNameLen = STRLEN(pDB->m_ContiShotInfo.CSFilename[byCurShotCnt][byCurCamID]);

    memcpy(FileName, pDB->m_ContiShotInfo.CSFilename[byCurShotCnt][byCurCamID], byFileNameLen);
    STRCPY(szNameBuff, pDB->szFolderPath[byCurCamID]);
    STRCAT(szNameBuff, "\\" );
    STRCAT(szNameBuff, FileName);
    pDB->m_ContiShotInfo.byCurShotCnt[byCurCamID]++;
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbRemoveFileByParentNode
//  Description : This function removes file by parent node, so all of sub node would be deleted
//  @param[in] pDB           Input DB
//  @param[in] psParentNode  psParentNode to delete
//  @param[in] bDeleteInFS   is this node need to delete its file in FS
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DbRemoveFileByParentNode(PSDATETIMEDCFDB pDB,
                                            PSDATETIMEFILE  psParentNode,
                                            AHC_BOOL bDeleteInFS)
{
    AHC_BOOL        bReturn = AHC_FALSE;
    SNODE_OP_PAK    NodeOpPak;
    if( psParentNode == NULL )
    {
        return bReturn;
    }
    // 1. FS operation
    //delete file in FS
    if(bDeleteInFS)
    {
        char            szFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
        AHC_BOOL        bErr = AHC_FALSE;
        PSSUBNODE       psSubNodeCur = psParentNode->pCamNodeHead;
        AHC_BOOL        bReadOnly;
        while(psSubNodeCur)
        {
            AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNodeCur, szFullPath, sizeof(szFullPath));
            bReadOnly = (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
            if( AHC_FALSE == AIHC_DCFDT_DeleteFileInFS(pDB, szFullPath, bReadOnly) ){
                AHC_DBG_MSG(1, "Remove file %s failed!\n", szFullPath );
                bErr = AHC_TRUE;
            }
            if( pDB->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE ){
                AIHC_DCFDT_DeleteNmeaFileInFS(szFullPath, bReadOnly);
            }
            if( bErr == AHC_TRUE){
                return AHC_FALSE;
            }
            psSubNodeCur = psSubNodeCur->pNext;
        }
    }

    if( pDB->ulTotalObjectNum == 0 )
    {
        AHC_DBG_MSG(1, "pDB->ulTotalObjectNum error\n");
    }
    // step 2. Update DB statistics, delete all sub node
    {
    PSSUBNODE psSubNodeCur = psParentNode->pCamNodeHead;
        while(psSubNodeCur)
        {
            AHC_DCFDT_UpdateDBStatistics(pDB, psSubNodeCur->byCamID, psSubNodeCur, DCFDT_STATISTICS_DELETE);
            psSubNodeCur = psSubNodeCur->pNext;
        }
    }
    //set NodeOpPak value
    {
        NodeOpPak.byCamID      = NULL;
        NodeOpPak.FileNameInfo = psParentNode->FileNameInfo;
        NodeOpPak.psParentNode = psParentNode;
        NodeOpPak.psSubNode    = NULL;
        NodeOpPak.byOperation  = DCFDT_NODE_DELETE_PARENT;
    }
    // step 3. node operation
    pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);

    bReturn = AHC_TRUE;

    return bReturn;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbRemoveSubFileByParentNode
//  Description : This function removes sub node by given parent node and CamID
//  @param[in] pDB           Input DB
//  @param[in] psParentNode  ParentNode to delete its sub node
//  @param[in] byCamID       byCamID to find and delete its subnode in linking
//  @param[in] bDeleteInFS   is this node need to delete its file in FS
//  @retval    AHC_TRUE     Success.
//  @retval    AHC_FALSE    Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DbRemoveSubFileByParentNode(PSDATETIMEDCFDB pDB,
                                               PSDATETIMEFILE  psParentNode,
                                               UINT8 byCamID,
                                               AHC_BOOL bDeleteInFS)
{
    AHC_BOOL        bReturn = AHC_FALSE;
    SNODE_OP_PAK    NodeOpPak;
    if( psParentNode == NULL )
    {
        return bReturn;
    }
    // 1. FS operation
    //delete file in FS
    if(bDeleteInFS)
    {
        char            szFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
#if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        char            *pThumbFullPath;
#endif
        AHC_BOOL        bErr = AHC_FALSE;
        PSSUBNODE       psSubNodeCur = psParentNode->pCamNodeHead;
        AHC_BOOL        bReadOnly;
        while(psSubNodeCur)
        {
            if(psSubNodeCur->byCamID == byCamID)
            {
                AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNodeCur, szFullPath, sizeof(szFullPath));
                bReadOnly = (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
                if( AHC_FALSE == AIHC_DCFDT_DeleteFileInFS(pDB, szFullPath, bReadOnly) ){
                    AHC_DBG_MSG(1, "Remove file %s failed!\n", szFullPath );
                    bErr = AHC_TRUE;
                }

#if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                if (!bErr) {
                    pThumbFullPath = STRTOK(szFullPath, ".");
                    STRCAT(pThumbFullPath, EXT_DOT);
                    STRCAT(pThumbFullPath, PHOTO_JPG_EXT);
                    if( AHC_FALSE == AIHC_DCFDT_DeleteFileInFS(pDB, pThumbFullPath, bReadOnly) ){
                        bErr = AHC_TRUE;
                    }
                }
#endif
                if( pDB->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE ){
                    AIHC_DCFDT_DeleteNmeaFileInFS(szFullPath, bReadOnly);
                }
                if( bErr == AHC_TRUE){
                    return AHC_FALSE;
                }
                break;
            }
            psSubNodeCur = psSubNodeCur->pNext;
        }
    }
    if( pDB->ulTotalObjectNum == 0 )
    {
        AHC_DBG_MSG(1, "pDB->ulTotalObjectNum error\n");
    }
    // step 2. Update DB statistics, delete all sub node
    {
    PSSUBNODE psSubNodeCur = psParentNode->pCamNodeHead;
        while(psSubNodeCur)
        {
            if(psSubNodeCur->byCamID == byCamID){
                AHC_DCFDT_UpdateDBStatistics(pDB, psSubNodeCur->byCamID, psSubNodeCur, DCFDT_STATISTICS_DELETE);
                break;
            }
            psSubNodeCur = psSubNodeCur->pNext;
        }
    }
    //set NodeOpPak value
    {
        NodeOpPak.byCamID      = byCamID;
        NodeOpPak.FileNameInfo = psParentNode->FileNameInfo;
        NodeOpPak.psParentNode = psParentNode;
        NodeOpPak.psSubNode    = NULL;
        NodeOpPak.byOperation  = DCFDT_NODE_DELETE_SUB;
    }
    // step 3. node operation
    pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);
    bReturn = AHC_TRUE;
    return bReturn;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbRemoveFileByIndex
//  Description : This function removes files by given Index
//                byDeleteMode decide to delete sub or parent node of spec. index.
//  @param[in] pDB           Input DB
//  @param[in] uiIndex       Index of file which would be deleted
//  @param[in] bDeleteInFS   Is this node need to delete its file in FS
//  @param[in] byDeleteMode  DeleteMode : DCFDT_DELETE_PARENT/DCFDT_DELETE_SUB
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DbRemoveFileByIndex(PSDATETIMEDCFDB pDB, UINT uiIndex, AHC_BOOL bDeleteInFS, UINT8 byDeleteMode )
{

    PSDATETIMEFILE  psParentNode;
    AHC_BOOL        bReturn = AHC_FALSE;
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB,uiIndex);
    if( psParentNode == NULL )
    {
        return bReturn;
    }
    if(byDeleteMode == DCFDT_DELETE_PARENT){
        return AHC_DCFDT_DbRemoveFileByParentNode(pDB, psParentNode, bDeleteInFS);
    }
    else if(byDeleteMode == DCFDT_DELETE_SUB){
        return AHC_DCFDT_DbRemoveSubFileByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID, bDeleteInFS);
    }
    AHC_DBG_MSG(1, "%s DeleteMode error %d\r\n", __FUNCTION__, byDeleteMode);
    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbRemoveFileByFileName
//  Description : This function removes files by given Filename
//  @param[in] pDB           Input DB
//  @param[in] szFilename    Filename which would be deleted
//  @param[in] bDeleteInFS   Is this node need to delete its file in FS
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DbRemoveFileByFileName(PSDATETIMEDCFDB pDB, char* szFilename, AHC_BOOL bDeleteInFS)
{
    PSDATETIMEFILE  psParentNode;
    UINT8           byCamID;

    psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, szFilename);
    if(psParentNode ==NULL){
        AHC_DBG_MSG(1, "psParentNode not found, szFilename %s\r\n", szFilename);
        return AHC_FALSE;
    }
    if(!AHC_DCFDT_GetCamIDByFileName(pDB, szFilename, &byCamID)){
        AHC_DBG_MSG(1, "GetCamIDByFileName failed!!%s\r\n", szFilename);
        return AHC_FALSE;
    }
    return AHC_DCFDT_DbRemoveSubFileByParentNode(pDB, psParentNode, byCamID, bDeleteInFS);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetParentNodeByDateTime
//  Description : This function get parent node by given datetime
//  @param[in] pDB           Input DB
//  @param[in] nDateTime     Input nDateTime
//  @retval    psParentNode  Found ParentNode
//------------------------------------------------------------------------------
PSDATETIMEFILE AHC_DCFDT_GetParentNodeByDateTime(PSDATETIMEDCFDB pDB, DATE_TIME nDateTime )
{
    PSDATETIMEFILE  psParentNode = NULL;
    if( pDB->pFileHead == NULL )
    {
        // Empty
        return psParentNode;
    }
    else
    {
        PSDATETIMEFILE psNodeCurr;
        psNodeCurr = pDB->pFileHead;
        while( psNodeCurr )
        {
            if( nDateTime == psNodeCurr->FileNameInfo.nDateTime )
            {
                psParentNode  = psNodeCurr;
                break;
            }
            psNodeCurr = psNodeCurr->pNext;
        }

    }
    return psParentNode;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetDateTimeByFileName
//  Description : This function gets datetime by given filename,
//                it can be costomized by diff time format type
//  @param[in]  pDB           Input DB
//  @param[in]  szFilename    Input filename
//  @param[in]  uiFreeCharLen free char length
//  @param[out] nDateTime     parse datetime from filename
//  @param[out] uiTimeStrLen  datetime length
//  @retval     AHC_TRUE      Success.
//  @retval     AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetDateTimeByFileName(PSDATETIMEDCFDB pDB,
                                         char            *szFilename,
                                         UINT32          uiFreeCharLen,
                                         DATE_TIME       *nDateTime,
                                         UINT32          *uiTimeStrLen)
{
    switch(pDB->byTimeFormat)
    {
        case DCFDT_TIMEFORMAT_TYPE0:
        {
            int   var[6];
            char  szCmpString[DCF_MAX_FILE_NAME_SIZE] = {0};
            MEMCPY(szCmpString, szFilename + uiFreeCharLen, DCFDT_TIMEFORMAT_TYPE0_LEN);
            sscanfl(szCmpString, DCFDT_TIMEFORMAT_TYPE0_TEMPLATE, &var[0]
                                                                , &var[1]
                                                                , &var[2]
                                                                , &var[3]
                                                                , &var[4]
                                                                , &var[5]);
            // Check if date time is valid.
            if(!AHC_DT_IsDateValid(var[0], var[1], var[2])||
               !AHC_DT_IsTimeValid(var[3], var[4], var[5]))
            {
                AHC_DBG_MSG(1, "%s Invalid date %s\n", __FUNCTION__, szFilename);
                return AHC_FALSE;
            }
            var[0] += DCFDT_FILENAME_YEAR_OFFSET;
            *nDateTime = AHC_DT_GetSecondsOffset(var[0],
                                                 var[1],
                                                 var[2],
                                                 var[3],
                                                 var[4],
                                                 var[5]);
            *uiTimeStrLen = DCFDT_TIMEFORMAT_TYPE0_LEN;
        }
        break;
        default :
            AHC_DBG_MSG(1, "UnIdentify TimeFormat");
            return AHC_FALSE;
        break;
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_CreateFileTimeStrByDateTime
//  Description : This function creates datetime str by given date time
//                it can be costomized by diff time format type
//  @param[in] pDB           Input DB
//  @param[in] nDateTime     Input nDateTime
//  @param[out]szFileTimeStr out szFileTimeStr
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_CreateFileTimeStrByDateTime(PSDATETIMEDCFDB pDB, DATE_TIME nDateTime, char* szFileTimeStr)
{
    AHC_RTC_TIME sRtcTime={0};
    if( !AHC_DT_SecondsToDateTime(nDateTime, &sRtcTime ))
    {
        AHC_DBG_MSG(1, "%s AHC_DT_SecondsToDateTime failed\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    switch(pDB->byTimeFormat)
    {
        case DCFDT_TIMEFORMAT_TYPE0:
        {
            sprintc(szFileTimeStr, DCFDT_TIMEFORMAT_TYPE0_TEMPLATE, sRtcTime.uwYear - DCFDT_FILENAME_YEAR_OFFSET
                                                                  , sRtcTime.uwMonth
                                                                  , sRtcTime.uwDay
                                                                  , sRtcTime.uwHour
                                                                  , sRtcTime.uwMinute
                                                                  , sRtcTime.uwSecond );
        }
        break;
        default:
        break;
    }
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetParentNodeByFilename
//  Description : This function gets parent node by given filename
//  @param[in] pDB           Input DB
//  @param[in] szFilename    Input Filename
//  @retval    parent node
//------------------------------------------------------------------------------
PSDATETIMEFILE AHC_DCFDT_GetParentNodeByFilename(PSDATETIMEDCFDB pDB, char* szFilename )
{
    BYTE            byFileType;
    UINT8           byCamID;
    AHC_BOOL        IsCharLock;
    PSDATETIMEFILE  psParentNode = NULL;
    SFILENAME_INFO  FileNameInfo;

    byFileType = AHC_DCFDT_GetFileType(szFilename);

    if( byFileType == DCFDT_UNKNOW_TYPE )
    {
        // Unknown type
        return psParentNode;
    }
    AHC_DCFDT_GetCamIDByFileName(pDB, szFilename, &byCamID);

    if(!AHC_DCFDT_ParseFileName(pDB, byCamID, szFilename, &FileNameInfo, &IsCharLock))
    {
        AHC_DBG_MSG(1, "ParseFileName failed %s szFilename %s\r\n", __FUNCTION__, szFilename);
        return psParentNode;
    }


    if( pDB->pFileHead == NULL )
    {
        // Empty
        return psParentNode;
    }
    else
    {
        PSDATETIMEFILE psNodeCurr;
        psNodeCurr = pDB->pFileHead;
        while( psNodeCurr )
        {
            if((FileNameInfo.nDateTime == psNodeCurr->FileNameInfo.nDateTime)
            && (FileNameInfo.uiFileIndex == psNodeCurr->FileNameInfo.uiFileIndex))
            {
                PSSUBNODE psSubNodeCur = psNodeCurr->pCamNodeHead;
                while(psSubNodeCur)
                {
                    if(psSubNodeCur->byCamID == byCamID)
                    {
                        psParentNode  = psNodeCurr;
                        goto SearchEnd;
                    }
                    psSubNodeCur = psSubNodeCur->pNext;
                }
            }
            psNodeCurr = psNodeCurr->pNext;
        }
    }
    SearchEnd:
    return psParentNode;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_GetSubNodeByParentNode
//  Description : This function gets subnode in spec. parent node selected by camID
//  @param[in] pDB           Input DB
//  @param[in] psParentNode  ParentNode
//  @param[in] byCamID       selected camID
//  @retval    SubNode       SubNode, if returns NULL means no subnode has been found
//------------------------------------------------------------------------------
PSSUBNODE AIHC_DCFDT_GetSubNodeByParentNode(PSDATETIMEDCFDB pDB, PSDATETIMEFILE psParentNode, UINT8 byCamID)
{
    PSSUBNODE psSubNodeCur = psParentNode->pCamNodeHead;
    while(psSubNodeCur)
    {
        if(psSubNodeCur->byCamID == byCamID)
        {
            return psSubNodeCur;
        }
        psSubNodeCur = psSubNodeCur->pNext;
    }
    AHC_DBG_MSG(1, "SubNode not Found!! byCamID %d\r\n", byCamID);
    return NULL;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_GetParentNodeByIndex
//  Description : This function gets parent node by seleted index
//  @param[in] pDB           Input DB
//  @param[in] uiIndex       Input uiIndex, Index means each cam ID index, not by parent node
//  @retval    ParentNode    ParentNode, if returns NULL means no parent node has been found
//------------------------------------------------------------------------------
PSDATETIMEFILE AIHC_DCFDT_GetParentNodeByIndex(PSDATETIMEDCFDB pDB, UINT uiIndex )
{

    PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
    INT32          nFileCount = -1;
    // Check index range
    if( uiIndex >= pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] )
    {
        AHC_DBG_MSG(1, "Index %d out of range %d!!\r\n", uiIndex, pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID]);
        return NULL;
    }

    while(psParentNodeCur)
    {
        if(pDB->bFormatFreeEnable)
        {
            PSSUBNODE psSubNodeCur;
            psSubNodeCur = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNodeCur, sDcfDtSet.m_byCurrCamID);
            if((psSubNodeCur == NULL) || (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_HIDDEN))
            {
                psParentNodeCur = psParentNodeCur->pNext;
                continue;
            }
        }
        //if the parent node exist the cam file, index++
        if(psParentNodeCur->byCamExist & (DCF_CAM_EXIST_BASE << sDcfDtSet.m_byCurrCamID)){
            nFileCount++;
        }
        //if Index == count
        if( uiIndex == nFileCount )
        {
            // The node found.
            return psParentNodeCur;
        }
        psParentNodeCur = psParentNodeCur->pNext;
    }
    AHC_DBG_MSG(1, "Can't found Parent Node, uiIndex %d\r\n", uiIndex);
    return NULL;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileNameByParentNode
//  Description : This function gets filename by given parent node and camID
//  @param[in] pDB           Input DB
//  @param[in] byCamID       Input byCamID
//  @param[in] psParentNode  Input psParentNode
//  @param[out]szNameBuff    out szNameBuff
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileNameByParentNode(PSDATETIMEDCFDB pDB,
                                           UINT8 byCamID,
                                           PSDATETIMEFILE psParentNode,
                                           char* szNameBuff)
{
    AHC_BOOL bFound = AHC_FALSE;
    PSSUBNODE psSubNodeCur = psParentNode->pCamNodeHead;
    while(psSubNodeCur)
    {
        if(psSubNodeCur->byCamID == byCamID)
        {
            bFound = AHC_TRUE;
            break;
        }
        psSubNodeCur = psSubNodeCur->pNext;
    }
    if(!bFound){
        AHC_DBG_MSG(1, "SubNode not found!%s\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    return AHC_DCFDT_GetFileNameBySubNode(pDB, psParentNode->FileNameInfo, psSubNodeCur, szNameBuff);

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileNameBySubNode
//  Description : This function gets filename by given sub node
//  @param[in] pDB           Input DB
//  @param[in] nDateTime     Input nDateTime
//  @param[out]szFileTimeStr out szFileTimeStr
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileNameBySubNode(PSDATETIMEDCFDB pDB, SFILENAME_INFO FileNameInfo, PSSUBNODE psSubNode, char* szNameBuff)
{
    AHC_BOOL bIsCharLock;
    bIsCharLock = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
    if(!AIHC_DCFDT_CreateFilename(pDB, psSubNode->byCamID, FileNameInfo, szNameBuff, bIsCharLock))
    {
        AHC_DBG_MSG(1, "%s CreateFilename failed\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    STRCAT( szNameBuff, "." );
    // Ext
    STRCAT( szNameBuff, m_DcfSupportFileType[psSubNode->byFileType] );
    szNameBuff[STRLEN(szNameBuff)]='\0';
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFullPathBySubNode
//  Description : This function gets file full path by given sub node
//  @param[in] pDB           Input DB
//  @param[in] nDateTime     Input nDateTime
//  @param[in] psSubNode     Input SubNode
//  @param[out]szNameBuff    out szNameBuff(full file path)
//  @param[in] uiBuffLength  Input uiBuffLength(length of full file path)
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFullPathBySubNode(PSDATETIMEDCFDB pDB, SFILENAME_INFO FileNameInfo, PSSUBNODE psSubNode, char* szNameBuff, UINT uiBuffLength )
{
    char* pTemp;
    AHC_BOOL bIsCharLock;

    MEMSET( szNameBuff, 0x00, uiBuffLength );
    STRCPY( szNameBuff, pDB->szFolderPath[psSubNode->byCamID] );
    STRCAT( szNameBuff, "\\" );
    pTemp = szNameBuff + STRLEN(szNameBuff);
    bIsCharLock = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
    if(!AIHC_DCFDT_CreateFilename(pDB, psSubNode->byCamID, FileNameInfo, pTemp, bIsCharLock))
    {
        AHC_DBG_MSG(1, "%s CreateFilename failed\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    STRCAT( pTemp, "." );
    // Ext
    STRCAT( pTemp, m_DcfSupportFileType[psSubNode->byFileType] );
    pTemp[STRLEN(pTemp)]='\0';
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFullPathByParentNode
//  Description : This function gets file full path by given parent node and CamID
//  @param[in] pDB           Input DB
//  @param[in] byCamID       Input byCamID
//  @param[in] psParentNode  Input psParentNode
//  @param[out]szNameBuff    out szNameBuff(full file path)
//  @param[in] uiBuffLength  Input uiBuffLength(length of full file path)
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFullPathByParentNode(PSDATETIMEDCFDB pDB, UINT8 byCamID, PSDATETIMEFILE psParentNode, char* szNameBuff, UINT uiBuffLength )
{
    AHC_BOOL bFound = AHC_FALSE;
    PSSUBNODE psSubNodeCur = psParentNode->pCamNodeHead;

    while(psSubNodeCur)
    {
        if(psSubNodeCur->byCamID == byCamID)
        {
            bFound = AHC_TRUE;
            break;
        }
        psSubNodeCur = psSubNodeCur->pNext;
    }
    if(!bFound){
        AHC_DBG_MSG(1, "SubNode not found!%s\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    return AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNodeCur, szNameBuff, uiBuffLength);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFullPathByParentNode
//  Description : This function gets filename by given Index
//  @param[in] pDB           Input DB
//  @param[in] uiIndex       Input uiIndex, Index means each cam ID index, not by parent node
//  @param[out]szNameBuff    out szNameBuff(file name)
//  @param[in] uiBuffLength  Input uiBuffLength(length of file name)
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DbGetFileNameByIndex( PSDATETIMEDCFDB pDB, UINT32 uiIndex, char* szNameBuff, UINT uiBuffLength )
{
    PSDATETIMEFILE psParentNodeCur;

    // Check index range
    if( uiIndex >= pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] )
    {
        MEMSET( szNameBuff, 0x00, uiBuffLength );
        AHC_DBG_MSG(1, "Index %d out of range %d!!\r\n", uiIndex, pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID]);
        return AHC_FALSE;
    }

    psParentNodeCur = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex);

    if( psParentNodeCur != NULL )
    {
        if( AHC_DCFDT_GetFileNameByParentNode(pDB, sDcfDtSet.m_byCurrCamID, psParentNodeCur, szNameBuff ) )
        {
            return AHC_TRUE;
        }
    }

    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFullPathByParentNode
//  Description : This function gets filename by given Index
//  @param[in] pDB           Input DB
//  @param[in] uiIndex       Input uiIndex, Index means each cam ID index, not by parent node
//  @param[out]szNameBuff    out szNameBuff(full file path)
//  @param[in] uiBuffLength  Input uiBuffLength(length of full file path)
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFullPathByIndex( PSDATETIMEDCFDB pDB, UINT32 uiIndex, char* szNameBuff, UINT uiBuffLength )
{
    PSDATETIMEFILE psParentNodeCur;

    // Check index range
    if( uiIndex >= pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] )
    {
        MEMSET( szNameBuff, 0x00, uiBuffLength );
        AHC_DBG_MSG(1, "Index %d out of range %d!!\r\n", uiIndex, pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID]);
        return AHC_FALSE;
    }

    psParentNodeCur = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex);

    if( psParentNodeCur != NULL )
    {
        if( AHC_DCFDT_GetFullPathByParentNode(pDB, sDcfDtSet.m_byCurrCamID, psParentNodeCur, szNameBuff, uiBuffLength ) )
        {
            return AHC_TRUE;
        }
    }

    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_GetInfo
//  Description : This function gets file info by given Index
//  @param[in] pDB           Input DB
//  @param[in] uiIndex       Input uiIndex, Index means each cam ID index, not by parent node
//  @param[out]Info          out file info
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_GetInfo(PSDATETIMEDCFDB pDB, UINT32 uiIndex, DCF_INFO *Info)
{
    PSDATETIMEFILE psParentNode;
    PSSUBNODE      psSubNode;

    if( uiIndex >= pDB->ulTotalObjectNumByCam[DCF_CAM_FRONT] )
    {
        MEMSET( Info, 0x00, sizeof(Info) );
        return AHC_FALSE;
    }

    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID);

    if(psSubNode)
    {
        AHC_RTC_TIME sRtcTime={0};
        AHC_DT_SecondsToDateTime(psParentNode->FileNameInfo.nDateTime, &sRtcTime );

        Info->uiFileSize  = psSubNode->nSizeInCluster * pDB->ulClusterSize ;
        Info->FileType    = psSubNode->byFileType;
        Info->bReadOnly   = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
        Info->bCharLock   = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;

        Info->uwYear      = sRtcTime.uwYear;
        Info->uwMonth     = sRtcTime.uwMonth;
        Info->uwDay       = sRtcTime.uwDay;
        Info->uwHour      = sRtcTime.uwHour;
        Info->uwMinute    = sRtcTime.uwMinute;
        Info->uwSecond    = sRtcTime.uwSecond;
        Info->bIsFileDownload = (psSubNode->byFileAttr & DCFDT_FILEATTR_ISDOWNLOAD) ? AHC_TRUE : AHC_FALSE;

        if(!AHC_DCFDT_GetFileNameByParentNode(pDB, sDcfDtSet.m_byCurrCamID, psParentNode, Info->FileName)){
            AHC_DBG_MSG(1, "%s failed uiIndex %d\r\n", __FUNCTION__, uiIndex);
            return AHC_FALSE;
        }


        #if DCFDT_DEBUG
        {
            int nNameLength = STRLEN(Info->FileName);
            if( nNameLength < 20 ||
                nNameLength > 30 )
            {
                AHC_DBG_MSG(1, "[WARN] Name length might be abnormal !\n");
            }

            AHC_DBG_MSG(1,  "File name:%s\n", Info->FileName );
        }

        if( !AHC_DT_IsDateValid( sRtcTime.uwYear, sRtcTime.uwMonth, sRtcTime.uwDay ) ||
            !AHC_DT_IsTimeValid( sRtcTime.uwHour, sRtcTime.uwMinute, sRtcTime.uwSecond )    )
        {
            AHC_DBG_MSG(1, "[ERR] Datetime is incorrect!\n");
        }


        if( psParentNode->uwYear      != sRtcTime.uwYear  ||
            psParentNode->uwMonth     != sRtcTime.uwMonth  ||
            psParentNode->uwDay       != sRtcTime.uwDay  ||
            psParentNode->uwHour      != sRtcTime.uwHour  ||
            psParentNode->uwMinute    != sRtcTime.uwMinute  ||
            psParentNode->uwSecond    != sRtcTime.uwSecond     )
        {
            AHC_DBG_MSG(1, "The date time is incorrect! %d");
        }

        #endif //DCFDT_DEBUG

    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetTotalCluster
//  Description : This function gets ulTotalClusters from media info
//  @retval       AHC_TRUE      Success.
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_GetTotalCluster(void)
{
    return  m_sMediaInfo.ulTotalClusters;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_LockInit
//  Description : This function inits DCFDT sem
//  @param[in] pDB           Input DB
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_LockInit(PSDATETIMEDCFDB pDB)
{
    pDB->smLock = AHC_OS_CreateSem(1);

    if (pDB->smLock >= MMPF_OS_ERR_SEM_ID_EXCEED_MAX) {
        return AHC_FALSE;
    }

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_LockUninit
//  Description : This function uninits DCFDT sem
//  @param[in] pDB           Input DB
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_LockUninit(PSDATETIMEDCFDB pDB)
{
    if (AHC_OS_DeleteSem(pDB->smLock) != MMPF_OS_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_LockEx
//  Description : This function acquires sem with timeouttick
//  @param[in] pDB           Input DB
//  @param[in] uiTimeOutTick Input uiTimeOutTick
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_LockEx(PSDATETIMEDCFDB pDB, UINT32 uiTimeOutTick )
{
    if (AHC_OS_AcquireSem(pDB->smLock, uiTimeOutTick) != MMPF_OS_ERR_NONE)
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_Lock
//  Description : This function acquires sem
//  @param[in] pDB           Input DB
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_Lock(PSDATETIMEDCFDB pDB )
{
    // Wait forever
    if (AHC_OS_AcquireSem(pDB->smLock, 0) != MMPF_OS_ERR_NONE)
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_Unlock
//  Description : This function release sem
//  @param[in] pDB           Input DB
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_Unlock(PSDATETIMEDCFDB pDB)
{
    if (AHC_OS_ReleaseSem(pDB->smLock) != MMPF_OS_ERR_NONE)
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbGetReadOnlyCluster
//  Description : This function gets read only objs clusters
//  @param[in] pDB           Input DB
//  @retval    read only objs clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_DbGetReadOnlyCluster(PSDATETIMEDCFDB pDB)
{
    return pDB->ullTotalLockedObjectSize/pDB->ulClusterSize;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbGetReadOnlyCluster
//  Description : This function gets unlock objs clusters
//  @param[in] pDB           Input DB
//  @retval    unlock objs clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_DbGetCyclicCluster(PSDATETIMEDCFDB pDB)
{
    // The size can be cyclic usage.
    return pDB->ullTotalUnlockedObjectSize/pDB->ulClusterSize;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_DbDeleteCyclicFilebySize
//  Description : This function visit all parentnode and subnode, if there's any normal file, delete it till size enough
//  @param[in] pDB           Input DB
//  @param[in] ulSize        total size need to delete
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_DbDeleteCyclicFilebySize(PSDATETIMEDCFDB pDB, UINT64 ulSize )
{
    UINT64         ulSizeDeleted = 0;
    UINT32         uiSize;
    PSDATETIMEFILE psParentNode,psTmpParentNode;//psTmpParentNode is used to storage original subnode
    PSSUBNODE      psSubNode,psTmpSubNode; //psTmpSubNode is used to storage original subnode
    AHC_BOOL       bReadOnly, bCharLock, bIsFileOpened;
    char           szFullPath[MAX_FULL_FILENAME_SIZE];
    if(pDB->pFileHead == NULL){
        AHC_DBG_MSG(1, "pDB->pFileHead == NULL\r\n");
        return AHC_FALSE;
    }
    psParentNode = pDB->pFileHead;
    //visit all parent node
    while(psParentNode)
    {
        psSubNode = psParentNode->pCamNodeHead;
        psTmpParentNode = psParentNode->pNext;
        //visit all sub node
        while(psSubNode)
        {
            //storage sub node next before delete node
            psTmpSubNode = psSubNode->pNext;
            bReadOnly   = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
            bCharLock   = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
            //check file is opened
            AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, szFullPath, MAX_FULL_FILENAME_SIZE);
            bIsFileOpened = AHC_DCFDT_CheckFileIsOpened(szFullPath);
            //if not readonly and not charlock, delete sub node
            if((!bReadOnly) && (!bCharLock) && (!bIsFileOpened))
            {
                uiSize = psSubNode->nSizeInCluster * pDB->ulClusterSize;
                AHC_DCFDT_DbRemoveSubFileByParentNode(pDB, psParentNode, psSubNode->byCamID, AHC_TRUE);
                ulSizeDeleted += uiSize;
            }
            //if ulSizeDeleted >= ulSize,
            //and the all file in same datetime have been deleted ,break
            if(ulSizeDeleted >= ulSize && psTmpSubNode == NULL)
            {
                goto DeleteEnd;
            }
            psSubNode = psTmpSubNode;
        }
        psParentNode = psTmpParentNode;
    }
    DeleteEnd:
    if(ulSizeDeleted >= ulSize){
        return AHC_TRUE;
    }
    else{
        AHC_DBG_MSG(1, "Delete size not enough!\r\n");
        AHC_DBG_MSG(1, "ulSizeDeleted %d, ulSize %d\r\n", ulSizeDeleted, ulSize);
        return AHC_FALSE;
    }
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_DbDeleteCyclicFilebyNum
//  Description : This function visits all parentnode and subnode, if there's any normal file, delete it till number enough
//  @param[in] pDB           Input DB
//  @param[in] ulNum         total num need to delete
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_DbDeleteCyclicFilebyNum(PSDATETIMEDCFDB pDB, UINT32 ulNum )
{
    UINT32         ulNumDeleted = 0;
    PSDATETIMEFILE psParentNode,psTmpParentNode;//psTmpParentNode is used to storage original subnode
    PSSUBNODE      psSubNode,psTmpSubNode; //psTmpSubNode is used to storage original subnode
    AHC_BOOL       bReadOnly, bCharLock, bIsFileOpened;
    char           szFullPath[MAX_FULL_FILENAME_SIZE];

    AHC_DCFDT_Lock(pDB);
    if(pDB->pFileHead == NULL){
        AHC_DBG_MSG(1, "pDB->pFileHead == NULL\r\n");
        return AHC_FALSE;
    }
    psParentNode = pDB->pFileHead;
    //visit all parent node
    while(psParentNode)
    {
        psSubNode = psParentNode->pCamNodeHead;
        psTmpParentNode = psParentNode->pNext;
        //visit all sub node
        while(psSubNode)
        {
            //storage sub node next before delete node
            psTmpSubNode = psSubNode->pNext;
            bReadOnly   = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
            bCharLock   = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
            //check file is opened
            AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, szFullPath, MAX_FULL_FILENAME_SIZE);
            bIsFileOpened = AHC_DCFDT_CheckFileIsOpened(szFullPath);
            //if not readonly and not charlock, delete sub node
            if((!bReadOnly) && (!bCharLock) && (!bIsFileOpened))
            {
                AHC_DCFDT_DbRemoveSubFileByParentNode(pDB, psParentNode, psSubNode->byCamID, AHC_TRUE);
                ulNumDeleted++;
            }
            //if ulNumDeleted >= ulNum, break
            if(ulNumDeleted >= ulNum && psTmpSubNode == NULL)
            {
                goto DeleteEnd;
            }
            psSubNode = psTmpSubNode;
        }
        psParentNode = psTmpParentNode;
    }
    DeleteEnd:
    if(ulNumDeleted >= ulNum){
        AHC_DCFDT_Unlock(pDB);
        return AHC_TRUE;
    }
    else{
        AHC_DBG_MSG(1, "Delete num not enough!\r\n");
        AHC_DBG_MSG(1, "ulNumDeleted %d, ulNum %d\r\n", ulNumDeleted, ulNum);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbGetFileCluster
//  Description : This function gets total file clusters
//  @param[in] pDB           Input DB
//  @retval    ulClusters    total file clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_DbGetFileCluster(PSDATETIMEDCFDB pDB)
{
    UINT32 ulClusters;
    if(pDB->ullTotalObjectSize == 0){
        ulClusters = 0 ;
    }
    else{
        ulClusters  = pDB->ullTotalObjectSize  / pDB->ulClusterSize;
    }
    return ulClusters;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DbGetClusterTH
//  Description : This function gets threshold cluster by DB
//  @param[in] pDB           Input DB
//  @retval    ulClusters    threshold cluster
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_DbGetClusterTH(PSDATETIMEDCFDB pDB)
{
    UINT32 ulClusters;
    ulClusters  = pDB->ulMaxSizeThresholdInCluster;
    return ulClusters;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MemPoolFSInit
//  Description : This function inits mem pool for DCF DB storage
//  @param[in] uiMaxMemSize  given uiMaxMemSize
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MemPoolFSInit(UINT32 uiMaxMemSize)
{
    AHC_BOOL bInit = AHC_FALSE;
    AHC_BOOL bRet  = AHC_FALSE;
    UINT32 ulDcfMem;

    AIHC_GetTempDCFMemStartAddr(&ulDcfMem);

    if( !bInit )
    {
        hFileNodeMemPool = AHC_MemPoolFS_InitPool((PBYTE)ulDcfMem, uiMaxMemSize, sizeof(SDATETIMEFILE) );
        if( hFileNodeMemPool != NULL )
        {
            bRet = AHC_TRUE;
        }
    }
    return bRet;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MemPoolFSUninit
//  Description : This function uninits mem pool for DCF DB storage
//  @param[in] uiMaxMemSize  given uiMaxMemSize
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MemPoolFSUninit(void)
{
    if( hFileNodeMemPool )
    {
        AHC_MemPoolFS_UninitPool(hFileNodeMemPool);
        hFileNodeMemPool = NULL;
        return AHC_TRUE;
    }
    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_FileNodeAlloc
//  Description : This function uninits mem pool for DCF DB storage
//  @retval       pointer of alloc node
//------------------------------------------------------------------------------
void* AHC_DCFDT_FileNodeAlloc( void )
{
    if(hFileNodeMemPool != NULL)
        return AHC_MemPoolFS_Calloc(hFileNodeMemPool);
    else
        return NULL;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_FileNodeFree
//  Description : This function frees node
//  @param[in]    pbyBuff node needs to free
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_FileNodeFree( void* pbyBuff )
{
    MEMSET(pbyBuff, 0xFF, hFileNodeMemPool->uiChunkSize);
    return AHC_MemPoolFS_Free(hFileNodeMemPool,pbyBuff);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_SetShotMode
//  Description : This function set shot mode which init contishot info value by mode
//                and select pfCurGetPath func pointer by mode
//  @param[in]    input Mode to set shot mode
//------------------------------------------------------------------------------
void AHC_DCFDT_SetShotMode(PSDATETIMEDCFDB pDB,DCF_OP Mode)
{
    UINT8 i;
    UINT8 byShotNum;
    //set shotnum
    switch(Mode){
    case DCF_SETMODE_CONTISHOT2P:
        byShotNum= 2;
    break;
    case DCF_SETMODE_CONTISHOT3P:
        byShotNum= 3;
    break;
    case DCF_SETMODE_CONTISHOT5P:
        byShotNum= 5;
    break;
    default:
    break;
    }
    //set info value
    switch(Mode){
    case DCF_SETMODE_CONTISHOT2P:
    case DCF_SETMODE_CONTISHOT3P:
    case DCF_SETMODE_CONTISHOT5P:
    {
        AHC_DBG_MSG(1, "Set ContiShot Mode\r\n");
        //set init value of m_ContiShotInfo
        MEMSET(&(pDB->m_ContiShotInfo), 0, sizeof(pDB->m_ContiShotInfo));
        pDB->m_ContiShotInfo.byCurShotMode = Mode;
        pDB->m_ContiShotInfo.byIsInit = AHC_FALSE;
        for(i = 0; i < DCFDT_CAM_NUM; i++){
            pDB->m_ContiShotInfo.byTotalShotNum[i] = byShotNum;
            pDB->m_ContiShotInfo.byCurShotCnt[i] = 0;
        }
        //point func pointer to contishot func
        pDB->pCusAPI->pfCurGetPath = (pDB->pCusAPI->pfContiShotGetPath);
    }
    break;
    case DCF_SETMODE_SINGLEMODE:
    {
        AHC_DBG_MSG(1, "Set SingleShot Mode\r\n");
        pDB->m_ContiShotInfo.byCurShotMode = Mode;
        //point func pointer to normal func
        pDB->pCusAPI->pfCurGetPath = (pDB->pCusAPI->pfNornalGetPath);
    }
    break;
    default:
    break;
    }
}
/*
DCF_FILE_READ_ONLY: �]�w�ɮ׬���Ū
DCF_FILE_NON_READ_ONLY: �]�w�ɮ׬��D��Ū
DCF_FILE_COPY: �����ɮ�
x DCF_FILE_CHAR_LOCK: ��wG-sensor lock�ɮ�
x DCF_FILE_CHAR_UNLOCK: ����G-sensor lock�ɮ�
x DCF_FILE_MOVE_SUBDB: �����ɮר�SubDB
DCF_FILE_DELETE_ALL_CAM: �R��all�ɮ�
DCF_FILE_RENAME: ���ɦW
*/
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_FileOperation
//  Description : This function operates files by instruction op
//  @param[in] pPathName      src path name(only folder path)
//  @param[in] pFileName      src file name
//  @param[out]byOperation    Operation of files
//  @param[out]pDestPath      dst path name(only folder path)
//  @param[out]pDestFileName  dst file name
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_FileOperation(char *pPathName,
                                   char *pFileName,
                                   UINT8 byOperation,
                                   char *pDestPath,
                                   char *pDestFileName)

{
    UINT32              error = MMP_ERR_NONE;
    char                szSrcFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char                szDstFullPath[DCF_MAX_FILE_NAME_SIZE]={0};

    MEMSET(szSrcFullPath , 0, sizeof(szSrcFullPath));
    MEMSET(szDstFullPath, 0, sizeof(szDstFullPath));

    switch(byOperation){

    case DCF_FILE_READ_ONLY:
    case DCF_FILE_NON_READ_ONLY:
    {
        PSDATETIMEDCFDB pSrcDb;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        UINT8           byCamID;
        AHC_BOOL        bReadOnlyOld;
        AHC_BOOL        bReadOnlyNew;

        bReadOnlyNew = (byOperation == DCF_FILE_READ_ONLY ? AHC_TRUE : AHC_FALSE);

        pSrcDb = AHC_DCFDT_GetDBByFolderName((char*)pPathName);

        if( pSrcDb == NULL )
        {
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pSrcDb);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pSrcDb, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }
        //get CamID
        if(!AHC_DCFDT_GetCamIDByFileName(pSrcDb, pFileName, &byCamID)){
            AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }
        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pSrcDb, psParentNode, byCamID);
        if( psSubNode == NULL ){
            AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }

        //get old read only
        bReadOnlyOld   = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
        //set new read only
        if(bReadOnlyNew){
            psSubNode->byFileAttr |= DCFDT_FILEATTR_READONLY;
        }
        else{
            psSubNode->byFileAttr &= ~DCFDT_FILEATTR_READONLY;
        }
        if( bReadOnlyNew != bReadOnlyOld )
        {

            // Remove read only attribute
            ULONG            ulSizeAligned;
            BYTE             byFileType;
            AHC_FS_ATTRIBUTE attrib;

            STRCPY( szSrcFullPath, pPathName );
            STRCAT( szSrcFullPath, "\\" );
            STRCAT( szSrcFullPath, (char*)pFileName );

            AHC_FS_FileDirGetAttribute(szSrcFullPath,
                                       STRLEN(szSrcFullPath), &attrib );

            byFileType    = psSubNode->byFileType;

            ulSizeAligned = psSubNode->nSizeInCluster * pSrcDb->ulClusterSize;

            if( bReadOnlyNew )
            {
                AHC_DCFDT_UpdateDBStatistics(pSrcDb, byCamID, psSubNode, DCFDT_STATISTICS_READONLY);
                attrib |= AHC_FS_ATTR_READ_ONLY;
            }
            else
            {
                AHC_DCFDT_UpdateDBStatistics(pSrcDb, byCamID, psSubNode, DCFDT_STATISTICS_NON_READONLY);
                attrib &= ~(AHC_FS_ATTR_READ_ONLY);
            }

            AHC_FS_FileDirSetAttribute(szSrcFullPath,
                                       STRLEN(szSrcFullPath), attrib );

        }
        AHC_DCFDT_Unlock(pSrcDb);

    }
    break;
    case DCF_FILE_READ_ONLY_ALL_CAM:
    case DCF_FILE_NON_READ_ONLY_ALL_CAM:
    {
        PSDATETIMEDCFDB pSrcDb;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        UINT8           byCamID;
        AHC_BOOL        bReadOnlyOld;
        AHC_BOOL        bReadOnlyNew;

        bReadOnlyNew = (byOperation == DCF_FILE_READ_ONLY_ALL_CAM ? AHC_TRUE : AHC_FALSE);

        pSrcDb = AHC_DCFDT_GetDBByFolderName((char*)pPathName);

        if( pSrcDb == NULL )
        {
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pSrcDb);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pSrcDb, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }
        //assign head subnode
        psSubNode = psParentNode->pCamNodeHead;

        while(psSubNode)
        {
            //get old read only
            bReadOnlyOld   = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
            //set new read only
            if(bReadOnlyNew){
                psSubNode->byFileAttr |= DCFDT_FILEATTR_READONLY;
            }
            else{
                psSubNode->byFileAttr &= ~DCFDT_FILEATTR_READONLY;
            }
            if( bReadOnlyNew != bReadOnlyOld )
            {

                // Remove read only attribute
                ULONG            ulSizeAligned;
                BYTE             byFileType;
                AHC_FS_ATTRIBUTE attrib;
                //char             szFullPath[MAX_FULL_FILENAME_SIZE];
                //MEMSET(szSrcFullPath, 0, sizeof(szSrcFullPath));
                //STRCPY( szSrcFullPath, pPathName );
                //STRCAT( szSrcFullPath, "\\" );
                //STRCAT( szSrcFullPath, (char*)pFileName );
                AHC_DCFDT_GetFullPathBySubNode(pSrcDb, psParentNode->FileNameInfo, psSubNode, szSrcFullPath, DCF_MAX_FILE_NAME_SIZE);
                AHC_FS_FileDirGetAttribute(szSrcFullPath,
                                        STRLEN(szSrcFullPath), &attrib );

                byFileType    = psSubNode->byFileType;

                ulSizeAligned = psSubNode->nSizeInCluster * pSrcDb->ulClusterSize;

                if( bReadOnlyNew )
                {
                    AHC_DCFDT_UpdateDBStatistics(pSrcDb, byCamID, psSubNode, DCFDT_STATISTICS_READONLY);
                    attrib |= AHC_FS_ATTR_READ_ONLY;
                }
                else
                {
                    AHC_DCFDT_UpdateDBStatistics(pSrcDb, byCamID, psSubNode, DCFDT_STATISTICS_NON_READONLY);
                    attrib &= ~(AHC_FS_ATTR_READ_ONLY);
                }

                AHC_FS_FileDirSetAttribute(szSrcFullPath,
                                        STRLEN(szSrcFullPath), attrib );

            }

            psSubNode = psSubNode->pNext;

        }
        AHC_DCFDT_Unlock(pSrcDb);
    }
    break;
    case DCF_FILE_COPY:
    {
        PSDATETIMEDCFDB pDstDb;

        STRCPY( szSrcFullPath, pPathName );
        STRCAT( szSrcFullPath, "\\" );
        STRCAT( szSrcFullPath, pFileName );

        STRCPY( szDstFullPath, pDestPath );
        STRCAT( szDstFullPath, "\\" );
        STRCAT( szDstFullPath, pDestFileName );

        error = AHC_FS_FileCopy(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));

        if( error == MMP_ERR_NONE )
        {
            AHC_FS_ATTRIBUTE    sFileAttrib;
            UINT32              uiFileSize;
            AHC_FS_FILETIME     sFileTime;
            UINT8               byCamID;
            pDstDb = AHC_DCFDT_GetDBByFolderName((char*)pDestPath);

            if( pDstDb == NULL )
            {
                return AHC_FALSE;
            }

            AHC_DCFDT_Lock(pDstDb);
            if( pDstDb->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE )
            {
                AIHC_DCFDT_ChangeToNmeaName(szSrcFullPath);
                AIHC_DCFDT_ChangeToNmeaName(szDstFullPath);
                AHC_FS_FileCopy(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));
            }


            if(!AHC_DCFDT_GetCamIDByFileName(pDstDb, pDestFileName, &byCamID)){
                AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
                AHC_DCFDT_Unlock(pDstDb);
                return AHC_FALSE;
            }
            if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szDstFullPath,
                                                      STRLEN(szDstFullPath),
                                                      &sFileAttrib,
                                                      &sFileTime,
                                                      &uiFileSize))
            {
                AHC_DBG_MSG(1, "%s file info failed!\n", szDstFullPath );
                AHC_DCFDT_Unlock(pDstDb);
                return AHC_FALSE;
            }
            AHC_DCFDT_AddFile(pDstDb, byCamID, pDestFileName, uiFileSize, sFileAttrib);
        }
        AHC_DCFDT_Unlock(pDstDb);
    }
    break;
    case DCF_FILE_CHAR_LOCK:
    case DCF_FILE_CHAR_UNLOCK:
    {
        PSDATETIMEDCFDB pDB;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        UINT8           byCamID;
        char            szFilepath[DCF_MAX_FILE_NAME_SIZE];
        char            szNewFilepath[DCF_MAX_FILE_NAME_SIZE];
        AHC_BOOL        bCharLockOld;
        AHC_BOOL        bCharLockNew;

        //get new attr
        bCharLockNew = (byOperation == DCF_FILE_CHAR_LOCK ? AHC_TRUE : AHC_FALSE);

        pDB = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
        if( pDB == NULL ){
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pDB);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get CamID
        if(!AHC_DCFDT_GetCamIDByFileName(pDB, pFileName, &byCamID)){
            AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, byCamID);
        if( psSubNode == NULL ){
            AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get original attr
        bCharLockOld   = (psSubNode->byFileAttr & DCF_FILE_CHAR_LOCK) ? AHC_TRUE : AHC_FALSE;

        //get original filename
        if(!AHC_DCFDT_GetFullPathByParentNode(pDB, byCamID, psParentNode, szFilepath, DCF_MAX_FILE_NAME_SIZE)){
            AHC_DBG_MSG(1, "GetFullPath failed!!\r\n");
        }

        if(bCharLockNew != bCharLockOld)
        {
            UINT8 byUpdateOp;
            //set attr
            if(bCharLockNew)
            {
                psSubNode->byFileAttr |= DCFDT_FILEATTR_CHARLOCK;
                byUpdateOp = DCFDT_LOCKTABLE_LOCK;
            }
            else
            {
                psSubNode->byFileAttr &= ~DCFDT_FILEATTR_CHARLOCK;
                byUpdateOp = DCFDT_LOCKTABLE_UNLOCK;
            }
            //get new filename
            if(!AHC_DCFDT_GetFullPathByParentNode(pDB, byCamID, psParentNode, szNewFilepath, DCF_MAX_FILE_NAME_SIZE)){
                AHC_DBG_MSG(1, "GetFullPath failed!!\r\n");
            }
            //Rename
            error = AHC_FS_FileDirRename(szFilepath, STRLEN(szFilepath), szNewFilepath, STRLEN(szNewFilepath));
            if(error != MMP_ERR_NONE){
                AHC_DBG_MSG(1, "%s failed!! szFilepath %s\r\n", __FUNCTION__, szFilepath);
            }

            AIHC_DCFDT_UpdateLockFileTable(psParentNode, NULL, byUpdateOp);
        }
        else
        {
            AHC_DBG_MSG(1, "Warning!! %s File can't be lock/unlock\r\n", __FUNCTION__);
        }
        AHC_DCFDT_Unlock(pDB);
    }
    break;
    case DCF_FILE_CHAR_LOCK_ALL_CAM:
    case DCF_FILE_CHAR_UNLOCK_ALL_CAM:
    {
        PSDATETIMEDCFDB pDB;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        char            szFilepath[DCF_MAX_FILE_NAME_SIZE];
        char            szNewFilepath[DCF_MAX_FILE_NAME_SIZE];
        AHC_BOOL        bCharLockOld;
        AHC_BOOL        bCharLockNew;
        UINT8           byUpdateOp;
        AHC_BOOL        bUpdateLockFileTbl = AHC_FALSE;

        //get new attr
        bCharLockNew = (byOperation == DCF_FILE_CHAR_LOCK_ALL_CAM ? AHC_TRUE : AHC_FALSE);

        pDB = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
        if( pDB == NULL ){
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pDB);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //assign head subnode
        psSubNode = psParentNode->pCamNodeHead;
        //visit all sub node
        while(psSubNode)
        {
            MEMSET(szFilepath, 0, sizeof(szFilepath));
            MEMSET(szNewFilepath, 0, sizeof(szNewFilepath));

            //get original attr
            bCharLockOld   = (psSubNode->byFileAttr & DCF_FILE_CHAR_LOCK_ALL_CAM) ? AHC_TRUE : AHC_FALSE;

            //get original filename
            if(!AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNode->byCamID, psParentNode, szFilepath, DCF_MAX_FILE_NAME_SIZE)){
                AHC_DBG_MSG(1, "GetFullPath failed!!\r\n");
            }
            if(bCharLockNew != bCharLockOld)
            {
                //set attr
                if(bCharLockNew)
                {
                    psSubNode->byFileAttr |= DCFDT_FILEATTR_CHARLOCK;
                    byUpdateOp = DCFDT_LOCKTABLE_LOCK;
                }
                else
                {
                    psSubNode->byFileAttr &= ~DCFDT_FILEATTR_CHARLOCK;
                    byUpdateOp = DCFDT_LOCKTABLE_UNLOCK;
                }
                //get new filename
                if(!AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNode->byCamID, psParentNode, szNewFilepath, DCF_MAX_FILE_NAME_SIZE)){
                    AHC_DBG_MSG(1, "GetFullPath failed!!\r\n");
                }
                //Rename
                error = AHC_FS_FileDirRename(szFilepath, STRLEN(szFilepath), szNewFilepath, STRLEN(szNewFilepath));
                if(error != MMP_ERR_NONE){
                    AHC_DBG_MSG(1, "%s failed!! szFilepath %s\r\n", __FUNCTION__, szFilepath);
                }

                bUpdateLockFileTbl = AHC_TRUE;
            }
            else
            {
                AHC_DBG_MSG(1, "Warning!! %s File %s can't be lock/unlock\r\n", __FUNCTION__, szFilepath);
            }

            psSubNode = psSubNode->pNext;
        }

        if (bUpdateLockFileTbl)
            AIHC_DCFDT_UpdateLockFileTable(psParentNode, NULL, byUpdateOp);

        AHC_DCFDT_Unlock(pDB);
    }
    break;
    case DCF_FILE_RENAME:
    case DCF_FILE_MOVE_SUBDB:
    {
        PSDATETIMEDCFDB pSrcDb;
        PSDATETIMEFILE  psSrcParentNode;
        PSDATETIMEDCFDB pDstDb;
        PSDATETIMEFILE  psDstParentNode;

        STRCPY( szSrcFullPath, pPathName );
        STRCAT( szSrcFullPath, "\\" );
        STRCAT( szSrcFullPath, pFileName );

        STRCPY( szDstFullPath, pDestPath );
        STRCAT( szDstFullPath, "\\" );
        STRCAT( szDstFullPath, pDestFileName );

        pSrcDb = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
        if( pSrcDb == NULL ){
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pSrcDb);
        //get src parent node from filename
        psSrcParentNode = AHC_DCFDT_GetParentNodeByFilename(pSrcDb, (char*)pFileName );
        if( psSrcParentNode == NULL ){
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }

        pDstDb = AHC_DCFDT_GetDBByFolderName((char*)pDestPath);
        if( pDstDb == NULL ){
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pDstDb);
        //get dst parent node
        psDstParentNode = AHC_DCFDT_GetParentNodeByFilename(pDstDb, (char*)pDestFileName );
        if( psDstParentNode != NULL ){
            // Delete target exist file
            AHC_DCFDT_DbRemoveFileByFileName(pDstDb, pDestFileName, AHC_TRUE);
        }
        // file move
        error = AHC_FS_FileDirMove(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));

        if( pDstDb->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE )
        {
            AIHC_DCFDT_ChangeToNmeaName(szSrcFullPath);
            AIHC_DCFDT_ChangeToNmeaName(szDstFullPath);
            AHC_FS_FileDirMove(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));
        }

        if( error == MMP_ERR_NONE )
        {
            AHC_FS_ATTRIBUTE    sFileAttrib;
            UINT32              uiFileSize;
            AHC_FS_FILETIME     sFileTime;
            UINT8               byCamID;
            //remove original file
            AHC_DCFDT_DbRemoveFileByFileName(pSrcDb, pFileName, AHC_FALSE);
            //add file parent/sub node in dst DB
            AHC_DCFDT_GetCamIDByFileName(pDstDb, pDestFileName, &byCamID);
            if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szDstFullPath,
                                                      STRLEN(szDstFullPath),
                                                      &sFileAttrib,
                                                      &sFileTime,
                                                      &uiFileSize))
            {
                AHC_DBG_MSG(1, "%s file info failed!\n", szDstFullPath );
                AHC_DCFDT_Unlock(pSrcDb);
                AHC_DCFDT_Unlock(pDstDb);
                return AHC_FALSE;
            }
            AHC_DCFDT_AddFile(pDstDb, byCamID, pDestFileName, uiFileSize, sFileAttrib);
        }
        AHC_DCFDT_Unlock(pSrcDb);
        AHC_DCFDT_Unlock(pDstDb);
    }
    break;

    case DCF_FILE_DELETE_ALL_CAM:
    {
        PSDATETIMEDCFDB pDB;
        PSDATETIMEFILE  psParentNode;
        UINT8           byCamID;
        PSSUBNODE       psSubNode;

        pDB = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
        if( pDB == NULL ){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_ALL_CAM: Fail0\r\n");
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pDB);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get CamID
        if(!AHC_DCFDT_GetCamIDByFileName(pDB, pFileName, &byCamID)){
            AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }

        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, byCamID);
        if( psSubNode == NULL ){
            AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }

        if(psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_SUB_CAM: This file is Read only!!\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }

        if(!AHC_DCFDT_DbRemoveFileByParentNode(pDB, psParentNode, AHC_TRUE)){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_ALL_CAM: Fail\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        AHC_DCFDT_Unlock(pDB);
    }
    break;
    case DCF_FILE_DELETE_SUB_CAM:
    {
        PSDATETIMEDCFDB pDB;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        UINT8           byCamID;

        pDB = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
        if( pDB == NULL ){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_SUB_CAM: Fail0\r\n");
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pDB);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get CamID
        if(!AHC_DCFDT_GetCamIDByFileName(pDB, pFileName, &byCamID)){
            AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, byCamID);
        if( psSubNode == NULL ){
            AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }

        if(psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_SUB_CAM: This file is Read only!!\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }

        if(psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_SUB_CAM: This file is Char Lock!!\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        if(!AHC_DCFDT_DbRemoveFileByFileName(pDB, pFileName, AHC_TRUE)){
            AHC_DBG_MSG(1, "DCF_FILE_DELETE_SUB_CAM: Fail2\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
        AHC_DCFDT_Unlock(pDB);
    }
    break;

    case DCF_FILE_DOWNLOADDONE:
    case DCF_FILE_NONDOWNLOAD:
    {
        PSDATETIMEDCFDB pSrcDb;
        PSDATETIMEFILE  psParentNode;
        PSSUBNODE       psSubNode;
        UINT8           byCamID;
        AHC_BOOL        bDownloadNew;
        AHC_BOOL        bDownloadOld;

        bDownloadNew = (byOperation == DCF_FILE_DOWNLOADDONE ? AHC_TRUE : AHC_FALSE);

        pSrcDb = AHC_DCFDT_GetDBByFolderName((char*)pPathName);

        if( pSrcDb == NULL )
        {
            return AHC_FALSE;
        }

        AHC_DCFDT_Lock(pSrcDb);
        //get parent node
        psParentNode = AHC_DCFDT_GetParentNodeByFilename(pSrcDb, (char*)pFileName);
        if( psParentNode == NULL ){
            AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }
        //get CamID
        if(!AHC_DCFDT_GetCamIDByFileName(pSrcDb, pFileName, &byCamID)){
            AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }
        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pSrcDb, psParentNode, byCamID);
        if( psSubNode == NULL ){
            AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
            AHC_DCFDT_Unlock(pSrcDb);
            return AHC_FALSE;
        }

        //get old read only
        bDownloadOld   = (psSubNode->byFileAttr & DCFDT_FILEATTR_ISDOWNLOAD) ? AHC_TRUE : AHC_FALSE;

        if(bDownloadNew != bDownloadOld)
        {
            //set new download attr
            if(bDownloadNew){
                psSubNode->byFileAttr |= DCFDT_FILEATTR_ISDOWNLOAD;
            }
            else{
                psSubNode->byFileAttr &= ~DCFDT_FILEATTR_ISDOWNLOAD;
            }
        }
        else
        {
            //AHC_DBG_MSG(1, "Same Download attr setting\r\n");
        }
        AHC_DCFDT_Unlock(pSrcDb);
    }
    break;
    case DCF_SETMODE_CONTISHOT2P:
    case DCF_SETMODE_CONTISHOT3P:
    case DCF_SETMODE_CONTISHOT5P:
    case DCF_SETMODE_SINGLEMODE:
    {
        PSDATETIMEDCFDB pDB;
        pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];
        AHC_DCFDT_SetShotMode(pDB, byOperation);
    }
    break;
    default:
        AHC_DBG_MSG(1, "%s Unidentified Operation!!\r\n", __FUNCTION__);
    break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_IsReadOnlybyFilename
//  Description : This function return file read-only flag
//  @param[in] sType          FilePath
//  @retval    AHC_TRUE       read-only
//  @retval    AHC_FALSE      not read-only or file failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_IsReadOnlybyFilename(char *pPathName)
{
    char    *pFileName;
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;
    UINT8           byCamID;

    pFileName = strrchr(pPathName, '\\');
    if (!pFileName) return AHC_FALSE;
    *pFileName = 0;
    pFileName++;
    pDB = AHC_DCFDT_GetDBByFolderName((char*)pPathName);
    if( pDB == NULL ){
        AHC_DBG_MSG(1, "DCF_FILE_DELETE: Fail0\r\n");
        return AHC_FALSE;
    }
    //get parent node
    psParentNode = AHC_DCFDT_GetParentNodeByFilename(pDB, (char*)pFileName);
    if( psParentNode == NULL ){
        AHC_DBG_MSG(1, "Get ParentNode failed!!pFileName %s\r\n", pFileName);
        return AHC_FALSE;
    }
    //get CamID
    if(!AHC_DCFDT_GetCamIDByFileName(pDB, pFileName, &byCamID)){
        AHC_DBG_MSG(1, "Get CamID failed!!pFileName %s\r\n", pFileName);
        return AHC_FALSE;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, byCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!pFileName %s\r\n", pFileName);
        return AHC_FALSE;
    }

    if(psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY){
        //AHC_DBG_MSG(1, "DCF_FILE_ATTR: This file is Read only!!\r\n");
        return AHC_TRUE;
    }
    //AHC_DBG_MSG(1, "DCF_FILE_ATTR: This file is not Read only!!\r\n");
    return AHC_FALSE;
}


//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_SelectDB
//  Description : This function select DB to set cur DB index
//  @param[in] sType          DB index to select
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_SelectDB(DCF_DB_TYPE sType)
{
    switch(sType){
    case DCF_DB_TYPE_DB0_NORMAL:
        sDcfDtSet.m_uiCurrDBIdx = 0;
        break;
    #if (DCF_DB_COUNT >= 2)
    case DCF_DB_TYPE_DB1_PARKING:
        sDcfDtSet.m_uiCurrDBIdx = 1;
        break;
    #endif
    #if (DCF_DB_COUNT >= 3)
    case DCF_DB_TYPE_DB2_EVENT:
        sDcfDtSet.m_uiCurrDBIdx = 2;
        break;
    #endif
    #if (DCF_DB_COUNT >= 4)
    case DCF_DB_TYPE_DB3_PHOTO:
        sDcfDtSet.m_uiCurrDBIdx = 3;
        break;
    #endif
    #if (DCF_DB_COUNT >= 5)
    case DCF_DB_TYPE_DB4_SHARE:
        sDcfDtSet.m_uiCurrDBIdx = 4;
        break;
    #endif
    default:
        AHC_DBG_ERR(1, "[DCFDT ERR] DB NONE\r\n");
        return AHC_FALSE;
        break;
    }

    sDcfDtSet.m_sDBType = sType;

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetDBByFolderName
//  Description : This function gets DB by given foldername
//  @param[in] szFolderName   given FolderName
//  @retval    pDB            pDB
//------------------------------------------------------------------------------
PSDATETIMEDCFDB AHC_DCFDT_GetDBByFolderName(char* szFolderName)
{

    PSDATETIMEDCFDB pDB = NULL;
    INT i, j;
    for(i=0; i<DCF_DB_COUNT; i++)
    {
        for(j = 0; j < DCFDT_CAM_NUM; j++)
        {
            if( 0 == STRCMP(sDcfDtSet.m_sDB[i].szFolderPath[j], szFolderName ) )
            {
                pDB = &sDcfDtSet.m_sDB[i];
                break;
            }
        }
    }

    return pDB;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_GetDbByType
//  Description : This function gets DB by given DB index
//  @param[in] sType   given DB index
//  @retval    pDB            pDB
//------------------------------------------------------------------------------
PSDATETIMEDCFDB AIHC_DCFDT_GetDbByType(DCF_DB_TYPE sType)
{
    PSDATETIMEDCFDB pDB = NULL;

    if( sType< DCF_DB_COUNT )
    {
        pDB = &sDcfDtSet.m_sDB[sType];
    }

    return pDB;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetDB
//  Description : This function gets current DB
//  @retval    pDB     ccurrent pDB
//------------------------------------------------------------------------------
DCF_DB_TYPE AHC_DCFDT_GetDB(void)
{
    // Get DB Type
    return sDcfDtSet.m_sDBType;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetTotalFileCountByCurrCamID
//  Description : This function gets total file count by current CamID
//  @param[in]puiImgIndex     total file count
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetTotalFileCountByCurrCamID(UINT32 *puiImgIndex)
{
    *puiImgIndex    = 0;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        AHC_DBG_MSG(1, "GetTotalFileCount Failed At DB:%d\r\n", sDcfDtSet.m_uiCurrDBIdx);
        return AHC_FALSE;
    }

    *puiImgIndex = sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx].ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID];

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetTotalFileCountByDB
//  Description : This function gets total file count by current CamID
//  @param[in]sDB             Select DB
//  @param[in]puiImgIndex     total file count
//  @retval    AHC_sTRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE sDB, UINT32 *puiImgIndex)
{
    *puiImgIndex    = 0;

    if( sDB >= DCF_DB_COUNT )
    {
        AHC_DBG_MSG(1, "%s GetTotalFileCount Failed At DB:%d\r\n", __FUNCTION__, sDB);
        return AHC_FALSE;
    }

    *puiImgIndex = sDcfDtSet.m_sDB[sDB].ulTotalObjectNum;

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_SetCurrentIndex
//  Description : This function set current "object index"
//  @param[in]uiImgIndex      object index to set
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_SetCurrentIndex(UINT32 uiImgIndex)
{

    PSDATETIMEDCFDB pDB;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];
    if(pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] == 0)
    {
        AHC_DBG_MSG(1, "%s No Objs in DB%d, Cam%d\r\n", __FUNCTION__, sDcfDtSet.m_uiCurrDBIdx, sDcfDtSet.m_byCurrCamID);
        return AHC_FALSE;
    }
    else if( uiImgIndex >= pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] )
    {
        AHC_DBG_MSG(1, "Current DB%d, CamID%d, Index%d \r\n",sDcfDtSet.m_uiCurrDBIdx, sDcfDtSet.m_byCurrCamID, pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID]);
        AHC_DBG_MSG(1, "[ERR] %s is out of range: %d >= %d\r\n", __FUNCTION__, uiImgIndex, pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID]);
        return AHC_FALSE;
    }

    pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID] = uiImgIndex;
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetCurrentIndex
//  Description : This function get current "object index"
//  @param[in]puiImgIndex     object index to set
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetCurrentIndex(UINT32 *puiImgIndex)
{
    PSDATETIMEDCFDB pDB;

    *puiImgIndex    = 0;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    if(pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] == 0)
    {
        AHC_DBG_MSG(1, "%s No Objs in DB%d, Cam%d\r\n", __FUNCTION__, sDcfDtSet.m_uiCurrDBIdx, sDcfDtSet.m_byCurrCamID);
        return AHC_FALSE;
    }
    else if( pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID] >= pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID] )
    {
        AHC_DBG_MSG(1, "Current DB%d, CamID%d, Index%d \r\n",sDcfDtSet.m_uiCurrDBIdx, sDcfDtSet.m_byCurrCamID, pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID]);
        AHC_DBG_MSG(1, "[ERR]%s is out of range! %d >= %d \r\n", __FUNCTION__, pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID], pDB->ulTotalObjectNumByCam[sDcfDtSet.m_byCurrCamID]);
        pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID] = 0;
    }

    *puiImgIndex = pDB->uiCurrentIndex[sDcfDtSet.m_byCurrCamID];

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFilePathNamebyIndex
//  Description : This function gets FilePathName(full path name) by object index
//  @param[in]uiIndex         object index to get path
//  @param[out]FilePathName   FilePathName
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName)
{
    PSDATETIMEDCFDB pDB;
    AHC_BOOL        bRet = AHC_FALSE;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return bRet;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    bRet = AHC_DCFDT_GetFullPathByIndex(pDB, uiIndex, FilePathName, DCF_MAX_FILE_NAME_SIZE );
    AHC_DCFDT_Unlock(pDB);

    return bRet;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileNamebyIndex
//  Description : This function gets FileName(only file name) by object index
//  @param[in]uiIndex         object index to get path
//  @param[out]FilePathName   FilePathName
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileNamebyIndex(UINT32 uiIndex, char* FileName)
{
    PSDATETIMEDCFDB pDB;
    AHC_BOOL        bRet = AHC_FALSE;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return bRet;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    bRet = AHC_DCFDT_DbGetFileNameByIndex(pDB, uiIndex, FileName, DCF_MAX_FILE_NAME_SIZE );
    AHC_DCFDT_Unlock(pDB);

    return bRet;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileSizebyIndex
//  Description : This function gets file size by object index
//  @param[in]uiIndex         object index to get path
//  @param[out]FileSize       FileSize
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileSizebyIndex(UINT32 uiIndex, UINT32* FileSize)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ){
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //get parent node
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    if( psParentNode == NULL ){
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!uiIndex %d\r\n", uiIndex);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    *FileSize = psSubNode->nSizeInCluster * pDB->ulClusterSize;
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileTypebyIndex
//  Description : This function gets file type by object index
//  @param[in]uiIndex         object index to get path
//  @param[out]FileType       FileType
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *FileType)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ){
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //get parent node
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    if( psParentNode == NULL ){
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!uiIndex %d\r\n", uiIndex);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    *FileType = psSubNode->byFileType;
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileTimebyIndex
//  Description : This function gets file RTC time by object index
//  @param[in]uiIndex         object index to get path
//  @param[out]pRtcTime       pRtcTime
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ||
        pRtcTime == NULL                           )
    {
        return AHC_FALSE;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    if( psParentNode == NULL ){
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    AHC_DCFDT_Unlock(pDB);

    return AHC_DT_SecondsToDateTime(psParentNode->FileNameInfo.nDateTime, pRtcTime);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_IsReadOnlybyIndex
//  Description : This function checks the file of the object index is read only
//  @param[in]uiIndex         object index to get path
//  @param[out]bReadOnly      is file read only
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ){
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //get parent node
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    if( psParentNode == NULL ){
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!uiIndex %d\r\n", uiIndex);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    *bReadOnly = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_IsCharLockbyIndex
//  Description : This function checks the file of the object index is char lock
//  @param[in]uiIndex         object index to get path
//  @param[out]bReadOnly      is file char lock
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ){
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //get parent node
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex );
    if( psParentNode == NULL ){
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNode, sDcfDtSet.m_byCurrCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!uiIndex %d\r\n", uiIndex);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    *bCharLock = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//Unused
AHC_BOOL AHC_DCFDT_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[])
{
    return AHC_TRUE;
}
//Unused
AHC_BOOL AHC_DCFDT_GetAllowedChar(INT8* pbyChar, UINT32 uiLength)
{
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_EnableDB
//  Description : This function enables the selected DB
//  @param[in]sType        DB to enable
//  @param[in]bEnable      enable or disable
//  @retval    AHC_TRUE       Success.
//  @retval    AHC_FALSE      Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable)
{
    if( sType >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }
    sDcfDtSet.m_bDBEnable[sType] = bEnable;
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetDBStatus
//  Description : This function gets the selected DB status. if the DB is enable or not?
//  @param[out]sType        DB index
//  @retval    bEnable
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetDBStatus(DCF_DB_TYPE sType)
{
    // return enable or not
    if( sType >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }
    return sDcfDtSet.m_bDBEnable[sType];
}

//Unused
AHC_BOOL AHC_DCFDT_WriteInfo(void)
{
    return AHC_TRUE;
}

//Unused
AHC_BOOL AHC_DCFDT_SetCyclicDeletedMask(DCF_FILE_PROTECT sType)
{
    return AHC_TRUE;
}

//Unused
AHC_BOOL AHC_DCFDT_GetCyclicDeletedMask(DCF_FILE_PROTECT* sType)
{

    return AHC_TRUE;
}
//Unused
AHC_BOOL AHC_DCFDT_SetFileDeletedMask(DCF_FILE_PROTECT sType)
{

    return AHC_TRUE;
}
//Unused
AHC_BOOL AHC_DCFDT_GetFileDeletedMask(DCF_FILE_PROTECT* sType)
{
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_DeleteCyclicFilebySize
//  Description : This function visit all parentnode and subnode, if there's any normal file, delete it till size enough
//  @param[in] ulSize        total size need to delete
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_DeleteCyclicFilebySize(UINT64 uiSize)
{
    PSDATETIMEDCFDB pDB;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    AIHC_DCFDT_DbDeleteCyclicFilebySize(pDB, uiSize );
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MoveFileByIndex
//  Description : This function moves file from fromDB to toDB by index and OpCam
//  @param[in]sFromType    file move From DB
//  @param[in]sToType      file move To DB
//  @param[in]uiIndex      file object index
//  @param[in]OpCam        operation CamID(to select which cam should be moved)
//  @param[in]bReadOnly    is file read only?
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly)
{
    PSDATETIMEDCFDB pDB;
    char            szFilename[DCF_MAX_FILE_NAME_SIZE]={0};
    PSDATETIMEFILE  psParentNodeCur;
    UINT32          i;
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    psParentNodeCur = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex);
    if(psParentNodeCur == NULL)
    {
        AHC_DBG_MSG(1, "%s ParentNode not found!! Index %d\r\n", __FUNCTION__, uiIndex);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //prefer use for loop
    for(i = 0; i < DCF_CAM_MAX; i++)
    {
        if(psParentNodeCur->byCamExist & (DCF_CAM_EXIST_BASE << i))
        {
            MEMSET(szFilename, 0, sizeof(szFilename));

            if(!AHC_DCFDT_GetFileNameByParentNode(pDB, i, psParentNodeCur, szFilename )){
                AHC_DBG_MSG(1, "%s failed uiIndex %d\r\n", __FUNCTION__, uiIndex);
                AHC_DCFDT_Unlock(pDB);
                return AHC_FALSE;
            }

            if(!AHC_DCFDT_MoveFile(sFromType, sToType, NULL, szFilename, bReadOnly)){
                AHC_DBG_MSG(1, "%s error %d\r\n", __FUNCTION__, __LINE__);
                AHC_DCFDT_Unlock(pDB);
                return AHC_FALSE;
            }
        }
    }
    AHC_DCFDT_Unlock(pDB);
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MoveFileByFileName_AllCam
//  Description : This function moves file from fromDB to toDB by filename, and this func moves "all cam files"
//  @param[in]sFromType    file move From DB
//  @param[in]sToType      file move To DB
//  @param[in]uwDirKey     uwDirKey to switch cam folder, TBD
//  @param[in]pchFileName  filename which be moved
//  @param[in]bReadOnly    is file read only?
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MoveFileByFileName_AllCam(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly)
{
    PSDATETIMEDCFDB pDB;
    char            szFilename[DCF_MAX_FILE_NAME_SIZE]={0};
    PSDATETIMEFILE  psParentNodeCur;
    UINT32          i;
    UINT8           byTmpCamExist;
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    psParentNodeCur = AHC_DCFDT_GetParentNodeByFilename(pDB, pchFileName);
    if(psParentNodeCur == NULL)
    {
        AHC_DBG_MSG(1, "%s ParentNode not found!! %s\r\n", __FUNCTION__, pchFileName);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //save CamExist,because psParentNodeCur would be deleted
    byTmpCamExist = psParentNodeCur->byCamExist;
    //prefer use for loop
    for(i = 0; i < DCF_CAM_MAX; i++)
    {
        if(byTmpCamExist & (DCF_CAM_EXIST_BASE << i))
        {
            MEMSET(szFilename, 0, sizeof(szFilename));

            if(!AHC_DCFDT_GetFileNameByParentNode(pDB, i, psParentNodeCur, szFilename )){
                AHC_DBG_MSG(1, "%s failed pchFileName %s\r\n", __FUNCTION__, pchFileName);
                AHC_DCFDT_Unlock(pDB);
                return AHC_FALSE;
            }

            if(!AHC_DCFDT_MoveFile(sFromType, sToType, NULL, szFilename, bReadOnly)){
                AHC_DBG_MSG(1, "%s error %d pchFileName %s\r\n", __FUNCTION__, __LINE__, pchFileName);
                AHC_DCFDT_Unlock(pDB);
                return AHC_FALSE;
            }

            //Caution: if there's only one sub node, parent node should be delete��
            //if((bySubNodeCount == 1) && (!pDB->bFormatFreeEnable))
        }
    }
    AHC_DCFDT_Unlock(pDB);
    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_MoveFileByIndex
//  Description : This function moves file from fromDB to toDB
//  @param[in]sFromType    file move From DB
//  @param[in]sToType      file move To DB
//  @param[in]uwDirKey     uwDirKey to switch cam folder, TBD
//  @param[in]pchFileName  filename which be moved
//  @param[in]bReadOnly    is file read only?
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly)
{
    UINT32          error;
    PSDATETIMEDCFDB pSrcDb = AIHC_DCFDT_GetDbByType(sFromType);
    PSDATETIMEFILE  psSrcParentNode;
    PSSUBNODE       psSubNode;
    UINT8           byCamID;
    PSDATETIMEFILE  psDstParentNode;
    PSDATETIMEDCFDB pDstDb = AIHC_DCFDT_GetDbByType(sToType);
    char            szSrcFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char            szDstFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char            szDstFilename[DCF_MAX_FILE_NAME_SIZE]={0};
    AHC_FS_ATTRIBUTE attrib;
    AHC_BOOL        bRet = AHC_FALSE;
    AHC_BOOL        bIsCharLock;
    if( pSrcDb == NULL || pDstDb == NULL )
    {
        AHC_DBG_MSG(1, "DCFDT_MoveFile failed!! SrcDb or DstDb = NULL\r\n");
        return bRet;
    }

    //get parent node
    psSrcParentNode = AHC_DCFDT_GetParentNodeByFilename(pSrcDb, (char*)pchFileName);
    if( psSrcParentNode == NULL ){
        AHC_DBG_MSG(1, "Get ParentNode failed!!pchFileName %s\r\n", pchFileName);
        return bRet;
    }
    //get CamID
    if(!AHC_DCFDT_GetCamIDByFileName(pSrcDb, pchFileName, &byCamID)){
        AHC_DBG_MSG(1, "Get CamID failed!!pchFileName %s\r\n", pchFileName);
        return bRet;
    }
    //get sub node
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pSrcDb, psSrcParentNode, byCamID);
    if( psSubNode == NULL ){
        AHC_DBG_MSG(1, "Get SubNode failed!!pchFileName %s\r\n", pchFileName);
        return bRet;
    }

    bIsCharLock = (psSubNode->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;

    //strcat src path
    STRCPY( szSrcFullPath, pSrcDb->szFolderPath[byCamID] );
    STRCAT( szSrcFullPath, "\\" );
    STRCAT( szSrcFullPath, (char*)pchFileName );
    //strcat dst path
    STRCPY( szDstFullPath, pDstDb->szFolderPath[byCamID] );
    STRCAT( szDstFullPath, "\\" );

    if( !AIHC_DCFDT_CreateFilename(pDstDb,
                                   psSubNode->byCamID,
                                   psSrcParentNode->FileNameInfo,
                                   szDstFilename,
                                   bIsCharLock))
    {
        AHC_DBG_MSG(1, "DCFDT_MoveFile failed!! CreateFilename Failed!!\r\n");
        return bRet;
    }
    //STRCAT ext
    STRCAT( szDstFilename, "." );
    STRCAT( szDstFilename, m_DcfSupportFileType[psSubNode->byFileType] );

    STRCAT( szDstFullPath, (char*)szDstFilename );

    psDstParentNode = AHC_DCFDT_GetParentNodeByFilename(pDstDb,szDstFilename);
    if(psDstParentNode){
        AHC_DCFDT_DbRemoveFileByFileName(pDstDb, szDstFilename, AHC_TRUE);
    }
    //move
    error = AHC_FS_FileDirMove(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));
    if(error != MMP_ERR_NONE){
        AHC_DBG_MSG(1, "DCFDT_MoveFile DirMove failed!! DstFullPath %s\r\n",szDstFullPath);
        return bRet;
    }
    // Read Only or not
    AHC_FS_FileDirGetAttribute(szDstFullPath,
                               STRLEN(szDstFullPath), &attrib );

    if( bReadOnly )
    {
        attrib |= AHC_FS_ATTR_READ_ONLY;
    }
    else
    {
        attrib &= ~(AHC_FS_ATTR_READ_ONLY);
    }

    AHC_FS_FileDirSetAttribute(szDstFullPath,
                               STRLEN(szDstFullPath), attrib );

    if( error == MMP_ERR_NONE )
    {
        AHC_FS_ATTRIBUTE    sFileAttrib;
        UINT32              uiFileSize;
        AHC_FS_FILETIME     sFileTime;
        UINT8               byCamID;

        AHC_DCFDT_DbRemoveFileByFileName(pSrcDb, pchFileName, AHC_FALSE);
        //add file in DB
        AHC_DCFDT_GetCamIDByFileName(pDstDb, szDstFilename, &byCamID);
        if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szDstFullPath,
                                                  STRLEN(szDstFullPath),
                                                  &sFileAttrib,
                                                  &sFileTime,
                                                  &uiFileSize))
        {
            AHC_DBG_MSG(1, "%s file info failed!\n", szDstFullPath );
            return AHC_FALSE;
        }
        AHC_DCFDT_AddFile(pDstDb, byCamID, szDstFilename, uiFileSize, sFileAttrib);
        bRet = AHC_TRUE;
    }

    if( pSrcDb->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE )
    {
        AIHC_DCFDT_ChangeToNmeaName(szSrcFullPath);
        AIHC_DCFDT_ChangeToNmeaName(szDstFullPath);
        AHC_FS_FileRemove(szDstFullPath, STRLEN(szDstFullPath));
        AHC_FS_FileDirMove(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));
    }

    return bRet;

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_RenameFile
//  Description : This function renames file, replace oldtime by newtime,it use sDcfDtSet.m_byCurrCamID as byCamID input, temp
//  @param[in]sFromType    file rename From DB
//  @param[in]psRtcTimeOld RtcTimeOld of filename
//  @param[in]psRtcTimeNew RtcTimeNew of filename
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_RenameFile(DCF_DB_TYPE sFromType, AHC_RTC_TIME* psRtcTimeOld, AHC_RTC_TIME* psRtcTimeNew)
{
    DATE_TIME       nDateTimeOld, nDateTimeNew;
    char            szSrcFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char            szDstFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    UINT32          uiFolderNameLen = 0;
    PSDATETIMEDCFDB pSrcDb = AIHC_DCFDT_GetDbByType(sFromType);

    PSDATETIMEFILE  psDstParentNode;
    AHC_BOOL        bRet = AHC_FALSE;

    AHC_FS_ATTRIBUTE    sFileAttrib;
    UINT32              uiFileSize;
    AHC_FS_FILETIME     sFileTime;
    PSSUBNODE           psSubNode;
    AHC_BOOL            bFormatFree;

    if( pSrcDb == NULL )
    {
        return bRet;
    }

    if(psRtcTimeOld->uwYear   == psRtcTimeNew->uwYear   &&
       psRtcTimeOld->uwMonth  == psRtcTimeNew->uwMonth  &&
       psRtcTimeOld->uwDay    == psRtcTimeNew->uwDay    &&
       psRtcTimeOld->uwHour   == psRtcTimeNew->uwHour   &&
       psRtcTimeOld->uwMinute == psRtcTimeNew->uwMinute &&
       psRtcTimeOld->uwSecond == psRtcTimeNew->uwSecond
      )
    {
        return AHC_TRUE;
    }

    AHC_DT_GetSecondsOffsetFromRtc(psRtcTimeOld,&nDateTimeOld);
    AHC_DT_GetSecondsOffsetFromRtc(psRtcTimeNew,&nDateTimeNew);
    //if sub node exist, delete sub node in DB and FS

    AHC_DCFDT_Lock(pSrcDb);
    psDstParentNode = AHC_DCFDT_GetParentNodeByDateTime(pSrcDb,nDateTimeNew);
    if(psDstParentNode)
    {
        //get sub node
        psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pSrcDb, psDstParentNode, sDcfDtSet.m_byCurrCamID);
        if(psSubNode){
            AHC_DCFDT_DbRemoveSubFileByParentNode(pSrcDb, psDstParentNode, sDcfDtSet.m_byCurrCamID, AHC_TRUE);
        }
    }

    //rename
    bRet = AHC_DCFDT_RenameFileByCamID(pSrcDb,
                                      szSrcFullPath, szDstFullPath,
                                      nDateTimeOld, nDateTimeNew,
                                      &uiFolderNameLen,sDcfDtSet.m_byCurrCamID);
    //delete old file sub node
    //force node operation to remove sub node
    bFormatFree = pSrcDb->bFormatFreeEnable;
    pSrcDb->bFormatFreeEnable = AHC_FALSE;
    AHC_DCFDT_DbRemoveFileByFileName(pSrcDb, szSrcFullPath+uiFolderNameLen, AHC_FALSE);
    //return ori status
    pSrcDb->bFormatFreeEnable = bFormatFree;

    //add file in DB
    if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szDstFullPath,
                                              STRLEN(szDstFullPath),
                                              &sFileAttrib,
                                              &sFileTime,
                                              &uiFileSize))
    {
        AHC_DBG_MSG(1, "%s file info failed!\n", szDstFullPath );
        AHC_DCFDT_Unlock(pSrcDb);
        return AHC_FALSE;
    }
    AHC_DCFDT_AddFile(pSrcDb, sDcfDtSet.m_byCurrCamID, szDstFullPath+uiFolderNameLen, uiFileSize, sFileAttrib);
    //NMEA
    if( pSrcDb->uiFlag & DCFDT_DB_FLAG_HAS_NMEA_FILE )
    {
        AIHC_DCFDT_ChangeToNmeaName(szSrcFullPath);
        AIHC_DCFDT_ChangeToNmeaName(szDstFullPath);
        AHC_FS_FileRemove(szDstFullPath, STRLEN(szDstFullPath));
        AHC_FS_FileDirRename(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));
    }
    AHC_DCFDT_Unlock(pSrcDb);
    return bRet;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_RenameFileByCamID
//  Description : This function renames file, replace oldtime by newtime,it use sDcfDtSet.m_byCurrCamID as byCamID input, temp
//  @param[in]pSrcDb            file rename From DB
//  @param[in]szSrcFullPath     SrcFullPath of filename
//  @param[out]szDstFullPath    DstFullPath of filename
//  @param[in]nDateTimeOld      old datetime of filename
//  @param[out]nDateTimeNew     old datetime of filename
//  @param[out]puiFolderNameLen folder name length
//  @param[in]byCamID           operate CamID
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_RenameFileByCamID(PSDATETIMEDCFDB pSrcDb,
                                    char* szSrcFullPath   , char* szDstFullPath,
                                    DATE_TIME nDateTimeOld, DATE_TIME nDateTimeNew,
                                    UINT32 *puiFolderNameLen, UINT8 byCamID)
{
    UINT32          error;
    AHC_BOOL        bRet = AHC_FALSE;
    char            szFolderName[DCF_MAX_FILE_NAME_SIZE]  = {0};
    char            szSrcFileName[DCF_MAX_FILE_NAME_SIZE] = {0};
    char            szDstFileName[DCF_MAX_FILE_NAME_SIZE] = {0};
    PSDATETIMEFILE  psSrcParentNode;
    PSSUBNODE       psSubNode;
    SFILENAME_INFO  FileNameInfo;

    //get source parent node
    psSrcParentNode = AHC_DCFDT_GetParentNodeByDateTime(pSrcDb,nDateTimeOld);
    if( psSrcParentNode == NULL ){
        AHC_DBG_MSG(1, "%s get parent node failed\r\n", __FUNCTION__);
        return bRet;
    }
    //get sub node by Cam ID
    psSubNode = AIHC_DCFDT_GetSubNodeByParentNode(pSrcDb, psSrcParentNode, byCamID);
    if( psSubNode== NULL ){
        AHC_DBG_MSG(1, "%s get sub node failed\r\n", __FUNCTION__);
        return bRet;
    }
    //create Src full path by datetime
    MEMCPY(szFolderName, pSrcDb->szFolderPath[byCamID], sizeof(pSrcDb->szFolderPath[byCamID]));
    STRCPY( szSrcFullPath, szFolderName );
    STRCAT( szSrcFullPath, "\\" );
    *puiFolderNameLen = STRLEN(szSrcFullPath);
    if( !AIHC_DCFDT_CreateFilename(pSrcDb,
                                   byCamID,
                                   psSrcParentNode->FileNameInfo,
                                   szSrcFileName,
                                   AHC_FALSE)){

        return bRet;
    }

    STRCAT( szSrcFullPath, szSrcFileName );
    STRCAT( szSrcFullPath, "." );
    STRCAT( szSrcFullPath, m_DcfSupportFileType[psSubNode->byFileType] );

    //create Dst full path by datetime
    STRCPY( szDstFullPath, szFolderName );
    STRCAT( szDstFullPath, "\\" );
    FileNameInfo.nDateTime = nDateTimeNew;
    FileNameInfo.uiFileIndex = psSrcParentNode->FileNameInfo.uiFileIndex;
    if( !AIHC_DCFDT_CreateFilename(pSrcDb,
                                   byCamID,
                                   FileNameInfo,
                                   szDstFileName,
                                   AHC_FALSE)){
        return bRet;
    }

    STRCAT( szDstFullPath, szDstFileName );
    STRCAT( szDstFullPath, "." );
    STRCAT( szDstFullPath, m_DcfSupportFileType[psSubNode->byFileType] );

    error = AHC_FS_FileDirRename(szSrcFullPath, STRLEN(szSrcFullPath), szDstFullPath, STRLEN(szDstFullPath));

    if( error == MMP_ERR_NONE ){
        bRet = AHC_TRUE;
    }else{
        AHC_DBG_MSG(1, "error = 0x%x, %s\r\n", error, __FUNCTION__);
        AHC_DBG_MSG(1, "szSrcFullPath %s\r\n", szSrcFullPath);
        AHC_DBG_MSG(1, "szDstFullPath %s\r\n", szDstFullPath);
    }

    return bRet;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetCyclicCluster
//  Description : This function gets unlock objs clusters by selected DB type
//  @param[in]sDB            selected DB type
//  @retval                  unlock objs clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_GetCyclicCluster(DCF_DB_TYPE sDB)
{
    PSDATETIMEDCFDB pDB = AIHC_DCFDT_GetDbByType(sDB);
    return AHC_DCFDT_DbGetCyclicCluster(pDB);
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileCluster
//  Description : This function gets total file clusters by selected DB type
//  @param[in]sDB            selected DB type
//  @retval                  total file clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_GetFileCluster(DCF_DB_TYPE sDB)
{
    PSDATETIMEDCFDB pDB = AIHC_DCFDT_GetDbByType(sDB);
    UINT32 uiClusters;
    uiClusters = AHC_DCFDT_DbGetFileCluster(pDB);
    //AHC_DBG_MSG(1, "DCF_File%d =%d\n", sDB, uiClusters);
    return uiClusters;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetClusterTH
//  Description : This function gets threshold cluster by selected DB
//  @param[in]sDB            selected DB type
//  @retval                  total file clusters
//------------------------------------------------------------------------------
UINT32 AHC_DCFDT_GetClusterTH(DCF_DB_TYPE sDB)
{
    PSDATETIMEDCFDB pDB = AIHC_DCFDT_GetDbByType(sDB);
    UINT32 uiClusters;
    uiClusters = AHC_DCFDT_DbGetClusterTH(pDB);
    //AHC_DBG_MSG(1, "DCF_Th%d = %d\n", sDB, uiClusters);
    return uiClusters;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_PreAddFile
//  Description : tmp no use
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_PreAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
    PSDATETIMEDCFDB     pDB;
    AHC_FS_ATTRIBUTE    sFileAttrib;
    UINT32              uiFileSize;
    UINT8               byCamID;
    char                szFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char                szFolderName[DCF_MAX_FILE_NAME_SIZE]={0};

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        AHC_DBG_MSG(1, "CurrDBIdx is out of range!!\r\n");
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //cmp szfilename and switch CamID
    if(!AHC_DCFDT_GetCamIDByFileName(pDB, pchFileName, &byCamID))
    {
        AHC_DBG_MSG(1, "AHC_DCFDT_GetCamIDByFileName failed! pchFileName %s\r\n", pchFileName);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    if(!AHC_DCFDT_CheckShareFileNumForAddFile(pDB, byCamID)){
        //return AHC_FALSE;
    }
    //because file doesn't exist yet, size and attr tmp = 0
    uiFileSize  = 0;
    sFileAttrib = 0;
    AHC_DCFDT_AddFile(pDB, byCamID, pchFileName, uiFileSize, sFileAttrib);
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetCamIDByFileName
//  Description : This function gets CamID by given filename, using the file to parse filename by for loop,
//                if parse name returns true, it means the filename matched the CamID(i)
//  @param[in] pDB           Input DB
//  @param[in] pchFileName   Given filename to match CamID
//  @param[out]pbyCamID      matched CamID
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetCamIDByFileName(PSDATETIMEDCFDB pDB, INT8 *pchFileName, UINT8 *pbyCamID)
{
    AHC_BOOL       bIsCharLock = AHC_FALSE; //default
    SFILENAME_INFO FileNameInfo;

    INT i;
    for(i = 0; i < DCFDT_CAM_NUM; i++)
    {
        if(AHC_DCFDT_ParseFileName(pDB, i, pchFileName, &FileNameInfo, &bIsCharLock))
        {
            //found
            *pbyCamID = i;
            return AHC_TRUE;
        }
    }
    return AHC_FALSE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_PostAddFile
//  Description : This function post add file after recording/capturing files,
//                this function would recognize the CamID of filename and add it to proper folder
//  @param[in] uwDirKey      interface(useless)
//  @param[in] pchFileName   Given filename to add file
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
    PSDATETIMEDCFDB     pDB;
    AHC_FS_ATTRIBUTE    sFileAttrib;
    UINT32              uiFileSize;
    AHC_FS_FILETIME     sFileTime = {0};
    UINT8               byCamID;
    char                szFullPath[DCF_MAX_FILE_NAME_SIZE]={0};
    char                szFolderName[DCF_MAX_FILE_NAME_SIZE]={0};
    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        AHC_DBG_MSG(1, "CurrDBIdx is out of range!!\r\n");
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //cmp szfilename and switch CamID
    if(!AHC_DCFDT_GetCamIDByFileName(pDB, pchFileName, &byCamID))
    {
        AHC_DBG_MSG(1, "AHC_DCFDT_GetCamIDByFileName failed! pchFileName %s\r\n", pchFileName);
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
    //
    STRCPY(szFolderName, pDB->szFolderPath[byCamID]);
    STRCPY(szFullPath, szFolderName);
    STRCAT(szFullPath, "\\");
    STRCAT(szFullPath, pchFileName);
    //AHC_DBG_MSG(1, "%s szFullPath %s\r\n", __FUNCTION__, szFullPath);

    #if (FS_FORMAT_FREE_ENABLE == 1) // Improve system performance becasue all info of Format Free files is the same
    if( VideoFunc_GetRecordStatus() == AHC_TRUE )
    {
        static UINT uiFileSize_Backup[DCF_DB_TYPE_MAX_NUMBER] = {0};
        static AHC_FS_ATTRIBUTE  sFileAttrib_Backup[DCF_DB_TYPE_MAX_NUMBER] = {0};

        if( uiFileSize_Backup[sDcfDtSet.m_uiCurrDBIdx] == 0 ) {
            if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szFullPath,
                                                      STRLEN(szFullPath),
                                                      &sFileAttrib,
                                                      &sFileTime,
                                                      &uiFileSize)     )
            {
                AHC_DBG_MSG(1, "PostAddFile get %s file info failed!\n", szFullPath );
                AHC_DCFDT_Unlock(pDB);
                return AHC_FALSE;
            }
            uiFileSize_Backup[sDcfDtSet.m_uiCurrDBIdx]  = uiFileSize;
            sFileAttrib_Backup[sDcfDtSet.m_uiCurrDBIdx] = sFileAttrib;
        }
        else
        {
            uiFileSize  = uiFileSize_Backup[sDcfDtSet.m_uiCurrDBIdx];
            sFileAttrib = sFileAttrib_Backup[sDcfDtSet.m_uiCurrDBIdx];
        }
    }
    else
    {
        if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szFullPath,
                                                  STRLEN(szFullPath),
                                                  &sFileAttrib,
                                                  &sFileTime,
                                                  &uiFileSize)     )
        {
            AHC_DBG_MSG(1, "PostAddFile get %s file info failed!\n", szFullPath );
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
    }

    #else

    if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szFullPath,
                                              STRLEN(szFullPath),
                                              &sFileAttrib,
                                              &sFileTime,
                                              &uiFileSize)     )
    {
        AHC_DBG_MSG(1, "PostAddFile get %s file info failed!\n", szFullPath );
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }

    #endif

    //get share file size
    #if (AHC_SHAREENC_SUPPORT)
    if(pDB->ubDBIndex == DCF_DB_FORMAT_FREE_DB)
    {
        if(!AHC_DCFDT_GetFormatFreeFileSize(pchFileName, &uiFileSize)){
            AHC_DBG_MSG(1, "AHC_DCFDT_GetFormatFreeFileSize failed!\r\n");
            AHC_DCFDT_Unlock(pDB);
            return AHC_FALSE;
        }
    }
    #endif
    AHC_DCFDT_UpdateFileData(pDB, byCamID, pchFileName, uiFileSize, sFileAttrib);
    AHC_DCFDT_Unlock(pDB);
    //AHC_DCFDT_FileOperation has AHC_DCFDT_Lock/AHC_DCFDT_Unlock
    AHC_DCFDT_FileOperation(szFolderName, pchFileName, DCF_FILE_DOWNLOADDONE, NULL, NULL);

#if 0   //mantis : 1219044/1223597
    pchFileName[STRLEN(pchFileName)-5] = 'R';

    //cmp szfilename and switch CamID
    if(!AHC_DCFDT_GetCamIDByFileName(pDB, pchFileName, &byCamID))
    {
        return AHC_FALSE;
    }
    //
    if(!AHC_DCFDT_CheckShareFileNumForAddFile(pDB, byCamID)){
        return AHC_FALSE;
    }
    //
    STRCPY(szFolderName, pDB->szFolderPath[byCamID]);
    STRCPY(szFullPath, szFolderName);
    STRCAT(szFullPath, "\\");
    STRCAT(szFullPath, pchFileName);
    if( AHC_ERR_NONE != AHC_FS_FileDirGetInfo(szFullPath,
                                              STRLEN(szFullPath),
                                              &sFileAttrib,
                                              &sFileTime,
                                              &uiFileSize)     )
    {
        return AHC_FALSE;
    }
    AHC_DCFDT_AddFile(pDB, byCamID, pchFileName, uiFileSize, sFileAttrib);
#endif

    return AHC_TRUE;

}
//----------------------------------
//
//----------------------------------
void AHC_DCFDT_CusFunc_Register(PSDCFDTSETTING pDBSet, UINT32 uiMode)
{
    UINT32 i;
    SDCFDT_CUS_API *CusAPI;
    SUNIFY_CUS_API *UniAPI;
    //
    switch(uiMode)
    {
        case DCFDT_MODULEMODE_DATETIME_INDEX:
            UniAPI = &UniCusDateTime_IndexFunc;
            CusAPI = &CusDateTime_IndexModeFunc;
        break;
        case DCFDT_MODULEMODE_STANDARD_DATETIME:
            UniAPI = &UniStandardModeFunc;
            CusAPI = &StandardDateTimeModeFunc;
        break;
        default:
            UniAPI = &UniStandardModeFunc;
            CusAPI = &StandardDateTimeModeFunc;
        break;
    }
    //
    pDBSet->m_pUniCusAPI = UniAPI;
    for(i = 0; i < DCF_DB_COUNT; i++)
    {
        pDBSet->m_sDB[i].pCusAPI = CusAPI;
    }
}
//----------------------------------
//
//----------------------------------
void AHC_DCFDT_ModuleInit(void)
{
    UINT32 i;
    //config sDBInit_Config flag
    //check DCF_DUAL_CAM_ENABLE
    //share folder does not support dual cam
    #if (DCF_DUAL_CAM_ENABLE == 1 && DCFDT_CAM_NUM > 1)
    for(i = 0; i < 4; i++){
        sDBInit_Config.sDBAttrConfig[i].byFlag |= DCFDT_DB_FLAG_HAS_REAR_CAM;
    }
    #elif(AHC_MULTI_TRACK_EN == 1)
    //only photo has dual file when multi track = 1
    sDBInit_Config.sDBAttrConfig[DCF_DB_TYPE_DB3_PHOTO].byFlag |= DCFDT_DB_FLAG_HAS_REAR_CAM;
    #endif
    //init DB value
    for(i = 0; i < DCF_DB_COUNT; i++){
        AHC_DCFDT_InitDB(&sDcfDtSet.m_sDB[i], sDBInit_Config.sDBAttrConfig[i].byFlag);
    }
    //register DB cus API and unify API
    AHC_DCFDT_CusFunc_Register(&sDcfDtSet, m_uiModuleMode);
}
//
//
//
AHC_BOOL AHC_DCFDT_MountDCF(UINT32 uiMaxMemSize)
{
    return sDcfDtSet.m_pUniCusAPI->pfCusMountAllDB(uiMaxMemSize);
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_MountAllDB
//  Description : This function inits mem pool, and folder name, filename chars, and mounts all DB
//  @param[in] uwDirKey      interface(useless)
//  @param[in] uiMaxMemSize  given max mem size for DB storage
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_MountAllDB(UINT32 uiMaxMemSize)
{
    INT i, j;
    UINT8  bySDCardNum;
    UINT32 uiClustersInDb = 0;
    UINT32 uiPayloadClusters;
    INT8   DcfFolderPathPool[DCFDT_SD_NUM][DCF_DB_COUNT][DCFDT_CAM_NUM][DCF_MAX_FILE_NAME_SIZE] = {0};
    // Init memory pool
    AHC_DCFDT_MemPoolFSInit(uiMaxMemSize);
    // Init all permutation combination of customized folder path
    AHC_DCFDT_InitFolderPathPool(DcfFolderPathPool[0][0][0], &sDBInit_Config);
    //select media
    if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD){
        bySDCardNum = DCFDT_SD_CARD0;
    }
    else if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD1){
        bySDCardNum = DCFDT_SD_CARD1;
    }
    // i for DB_COUNT, j for CAM_NUM
    for(i = 0; i < DCF_DB_COUNT; i++)
    {
        //AHC_DCFDT_InitDB(&sDcfDtSet.m_sDB[i], sDBInit_Config.sDBAttrConfig[i].byFlag);
        for(j = 0; j < DCFDT_CAM_NUM; j++)
        {
            AHC_DCFDT_InitDB_PathName(&sDcfDtSet.m_sDB[i],
                                      j,
                                      DcfFolderPathPool[bySDCardNum][i][j],
                                      sDBInit_Config.sDBAttrConfig[i].byNamingType,
                                      sDBInit_Config.sDBAttrConfig[i].sPathConfig[j].szFileFreeChar,
                                      sDBInit_Config.sDBAttrConfig[i].byTimeFormat,
                                      sDBInit_Config.sDBAttrConfig[i].sPathConfig[j].szFileFixedChar
                                      );
        }
    }

    // Mount each db
    for(i=0; i < DCF_DB_COUNT; i++)
    {
        //mount DB
        if( sDcfDtSet.m_bDBEnable[i] )
        {
            //assign index to DB;
            sDcfDtSet.m_sDB[i].ubDBIndex = i;
            #if(FS_FORMAT_FREE_ENABLE)// if format free, all DB enable
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_TRUE;
            #else
            //set format free DB attr
            if( i == DCF_DB_FORMAT_FREE_DB){
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_TRUE;
            }
            else{
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_FALSE;
            }
            #endif
            //mount DB
            if (AHC_DCFDT_MountDB(&sDcfDtSet.m_sDB[i]) == MMP_FALSE)
            {
                sDcfDtSet.m_bMountDCF[i] = AHC_TRUE;
                return MMP_FALSE;
            }
            //total statistics
            uiClustersInDb += sDcfDtSet.m_sDB[i].ullTotalObjectSize/sDcfDtSet.m_sDB[i].ulClusterSize;
            sDcfDtSet.m_bMountDCF[i] = AHC_TRUE;
        }
    }

    #if(FS_FORMAT_FREE_ENABLE)
    if(DCFDT_CAM_NUM >= 2)
    {
        for(i = 0; i < DCF_DB_COUNT; i++)
        {
            for(j = 0; j < (DCFDT_CAM_NUM - 1); j++)
            {
                UINT32 uiTotalNodeNum = sDcfDtSet.m_sDB[i].ulTotalHiddenNumByCam[j] + sDcfDtSet.m_sDB[i].ulTotalObjectNumByCam[j];
                UINT32 uiTotalNodeNumNextCam = sDcfDtSet.m_sDB[i].ulTotalHiddenNumByCam[j+1] + sDcfDtSet.m_sDB[i].ulTotalObjectNumByCam[j+1];
                if(uiTotalNodeNum != uiTotalNodeNumNextCam &&
                   uiTotalNodeNum != 0 &&
                   uiTotalNodeNumNextCam != 0)
                {
                    AHC_BOOL ret;
                    //visit all parent node and remove asymmetric file nodes, and rename filenammes to illgal filenames
                    ret = AHC_DCFDT_FormatFree_RemoveAsymmetricFiles(&sDcfDtSet.m_sDB[i]);
                    if(!ret) return AHC_FALSE;
                }
            }
        }
    }
    #endif


    // Threshold setting
    {
        UINT8 nSetting =0 ;
        if( AHC_DCFDT_CB_GetStorageAllocationSetting )
        {
            AHC_DCFDT_CB_GetStorageAllocationSetting(&nSetting);
        }

        AHC_DCFDT_AdjustAllocation(nSetting);
    }
    //process format free folder
    for(i=0; i < DCF_DB_COUNT; i++)
    {
        if(sDcfDtSet.m_sDB[i].bFormatFreeEnable){
            //check formatfree folder file num
            if(!AHC_DCFDT_CheckFormatFreeFolderFileNum(&sDcfDtSet.m_sDB[i])){
                AHC_DBG_MSG(1, "%s CheckFormatFreeFolderFileNum failed\r\n", __FUNCTION__);
            }
        }
    }
    //  AHC_DBG_MSG(1, "TotalCluster    : %d, \r\n", m_sMediaInfo.ulTotalClusters);
    //  AHC_DBG_MSG(1, "FreelCluster    : %d, \r\n", m_sMediaInfo.ulFreeClusters);
    uiPayloadClusters = m_sMediaInfo.ulTotalClusters
                        - m_sMediaInfo.ulFreeClusters
                        - uiClustersInDb;

    for(i=0; i<DCF_DB_COUNT; i++)
    {
        if( sDcfDtSet.m_sDB[i].bThreadConsiderPayload )
        {
            sDcfDtSet.m_sDB[i].ulPayloadInCluster = uiPayloadClusters;
            break;
        }
    }

    // Check if need to create device.xml
    #if ( UUID_XML_FEATURE == 1 )
    {
        if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
        {
            if( !UI_WriteSdUuidXML() )
            {
                return AHC_FALSE;
            }
        }
    }
    #endif

    // Dump
#if (DCFDT_DEBUG)
    for(i=0; i<DCF_DB_COUNT; i++)
    {
        AHC_DCFDT_DumpDb(&sDcfDtSet.m_sDB[i]);
    }
#endif
    // Get Payload size
    // Set payload to DB

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_MountAllDB
//  Description : This function inits mem pool, and folder name, filename chars, and mounts all DB
//  @param[in] uwDirKey      interface(useless)
//  @param[in] uiMaxMemSize  given max mem size for DB storage
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_MountAllDB_IndexMode(UINT32 uiMaxMemSize)
{
    INT i, j;
    UINT8  bySDCardNum;
    UINT32 uiClustersInDb = 0;
    UINT32 uiPayloadClusters;
    INT8   DcfFolderPathPool[DCFDT_SD_NUM][DCF_DB_COUNT][DCFDT_CAM_NUM][DCF_MAX_FILE_NAME_SIZE] = {0};
    // Init memory pool
    AHC_DCFDT_MemPoolFSInit(uiMaxMemSize);
    // Init all permutation combination of customized folder path
    AHC_DCFDT_InitFolderPathPool(DcfFolderPathPool[0][0][0], &sDBInit_Config);
    //select media
    if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD){
        bySDCardNum = DCFDT_SD_CARD0;
    }
    else if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD1){
        bySDCardNum = DCFDT_SD_CARD1;
    }
    // i for DB_COUNT, j for CAM_NUM
    for(i = 0; i < DCF_DB_COUNT; i++)
    {
        //AHC_DCFDT_InitDB(&sDcfDtSet.m_sDB[i], sDBInit_Config.sDBAttrConfig[i].byFlag);
        for(j = 0; j < DCFDT_CAM_NUM; j++)
        {
            AHC_DCFDT_InitDB_PathName(&sDcfDtSet.m_sDB[i],
                                      j,
                                      DcfFolderPathPool[bySDCardNum][i][j],
                                      sDBInit_Config.sDBAttrConfig[i].byNamingType,
                                      sDBInit_Config.sDBAttrConfig[i].sPathConfig[j].szFileFreeChar,
                                      sDBInit_Config.sDBAttrConfig[i].byTimeFormat,
                                      sDBInit_Config.sDBAttrConfig[i].sPathConfig[j].szFileFixedChar
                                      );
        }
    }
    //read txt file from SD card, only for DB1 for loop record, Chuni Li
    {
        char fileName[DCF_MAX_FILE_NAME_SIZE] = {0};
        AHC_BOOL ret;

        MEMCPY(fileName, DCFDT_FILEINDEX_INDEXSAVED_FIlENAME, sizeof(DCFDT_FILEINDEX_INDEXSAVED_FIlENAME));
        if(AHC_IsFileExist(fileName))
        {
            ret = AHC_DCFDT_ReadFileIndexFromSavedFile();
            if(ret == AHC_TRUE)
            {
                //hidden file exist
                //lock index in file ctrl
                //and use index in file
                bFileIndexLock = AHC_TRUE;

            }
            else
            {
                //for( i = 0 ; i < DCF_DB_COUNT ; i++)
                //{
                //  AHC_DCFDT_FileIndexCtrl(&sDcfDtSet.m_sDB[i], NULL, DCFDT_INDEX_CTL_RESET_ALL_INDEX);
                //}
                AHC_DBG_MSG(1, "%s err line %d\r\n", __FUNCTION__, __LINE__);
            }
        }
        else
        {
            //set index value to init
            for( i = 0 ; i < DCF_DB_COUNT ; i++)
            {
                AHC_DCFDT_FileIndexCtrl(&sDcfDtSet.m_sDB[i], NULL, DCFDT_INDEX_CTL_RESET_ALL_INDEX);
            }
        }
    }
    // Mount each db
    for(i=0; i < DCF_DB_COUNT; i++)
    {
        //mount DB
        if( sDcfDtSet.m_bDBEnable[i] )
        {
            //assign index to DB;
            sDcfDtSet.m_sDB[i].ubDBIndex = i;
            #if(FS_FORMAT_FREE_ENABLE)// if format free, all DB enable
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_TRUE;
            #else
            //set format free DB attr
            if( i == DCF_DB_FORMAT_FREE_DB){
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_TRUE;
            }
            else{
                sDcfDtSet.m_sDB[i].bFormatFreeEnable = AHC_FALSE;
            }
            #endif
            //mount DB
            if (AHC_DCFDT_MountDB(&sDcfDtSet.m_sDB[i]) == MMP_FALSE)
            {
                sDcfDtSet.m_bMountDCF[i] = AHC_TRUE;
                return MMP_FALSE;
            }
            //total statistics
            uiClustersInDb += sDcfDtSet.m_sDB[i].ullTotalObjectSize/sDcfDtSet.m_sDB[i].ulClusterSize;
            sDcfDtSet.m_bMountDCF[i] = AHC_TRUE;
        }
    }
    //process format free folder
    for(i=0; i < DCF_DB_COUNT; i++)
    {
        if(sDcfDtSet.m_sDB[i].bFormatFreeEnable){
            //check formatfree folder file num
            if(!AHC_DCFDT_CheckFormatFreeFolderFileNum(&sDcfDtSet.m_sDB[i])){
                AHC_DBG_MSG(1, "%s CheckFormatFreeFolderFileNum failed\r\n", __FUNCTION__);
            }
        }
    }
    //after mount, adjust add/del to valid position
    AHC_DCFDT_UpdateNextIndexInFile();
    // unlock file index locker
    bFileIndexLock = AHC_FALSE;
    //if format free, check F/R file number equal or not?
    #if(FS_FORMAT_FREE_ENABLE)
    if(DCFDT_CAM_NUM >= 2)
    {
        for(i = 0; i < DCF_DB_COUNT; i++)
        {
            for(j = 0; j < (DCFDT_CAM_NUM - 1); j++)
            {
                UINT32 uiTotalNodeNum = sDcfDtSet.m_sDB[i].ulTotalHiddenNumByCam[j] + sDcfDtSet.m_sDB[i].ulTotalObjectNumByCam[j];
                UINT32 uiTotalNodeNumNextCam = sDcfDtSet.m_sDB[i].ulTotalHiddenNumByCam[j+1] + sDcfDtSet.m_sDB[i].ulTotalObjectNumByCam[j+1];
                if(uiTotalNodeNum != uiTotalNodeNumNextCam &&
                   uiTotalNodeNum != 0 &&
                   uiTotalNodeNumNextCam != 0)
                {
                    AHC_BOOL ret;
                    //visit all parent node and remove asymmetric file nodes, and rename filenammes to illgal filenames
                    ret = AHC_DCFDT_FormatFree_RemoveAsymmetricFiles(&sDcfDtSet.m_sDB[i]);
                    if(!ret) return AHC_FALSE;
                }
            }
        }
    }
    #endif
    // Threshold setting
    {
        UINT8 nSetting =0 ;
        if( AHC_DCFDT_CB_GetStorageAllocationSetting )
        {
            AHC_DCFDT_CB_GetStorageAllocationSetting(&nSetting);
        }

        AHC_DCFDT_AdjustAllocation(nSetting);
    }
    //  AHC_DBG_MSG(1, "TotalCluster    : %d, \r\n", m_sMediaInfo.ulTotalClusters);
    //  AHC_DBG_MSG(1, "FreelCluster    : %d, \r\n", m_sMediaInfo.ulFreeClusters);
    uiPayloadClusters = m_sMediaInfo.ulTotalClusters
                        - m_sMediaInfo.ulFreeClusters
                        - uiClustersInDb;

    for(i=0; i<DCF_DB_COUNT; i++)
    {
        if( sDcfDtSet.m_sDB[i].bThreadConsiderPayload )
        {
            sDcfDtSet.m_sDB[i].ulPayloadInCluster = uiPayloadClusters;
            break;
        }
    }

    // Check if need to create device.xml
    #if ( UUID_XML_FEATURE == 1 )
    {
        if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
        {
            if( !UI_WriteSdUuidXML() )
            {
                return AHC_FALSE;
            }
        }
    }
    #endif
    // Dump
#if (DCFDT_DEBUG)
    for(i=0; i<DCF_DB_COUNT; i++)
    {
        AHC_DCFDT_DumpDb(&sDcfDtSet.m_sDB[i]);
    }
#endif

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_UnMountAllDB
//  Description : This function unmounts all DB, to clear all DB data, set mount disable
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AIHC_DCFDT_UnmountAllDB(void)
{
    INT i;
    for(i=0; i<DCF_DB_COUNT; i++)
    {

        if( sDcfDtSet.m_bMountDCF[i])
        {
            AHC_DCFDT_UnmountDB(&sDcfDtSet.m_sDB[i]);
            sDcfDtSet.m_bMountDCF[i] = AHC_FALSE;
        }
    }

    AHC_DCFDT_MemPoolFSUninit();

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_IsDBMounted
//  Description : This function check the current DB is mount
//  @retval    m_bMountDCF   is the current DB is mount
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_IsDBMounted(void)
{

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }

    return sDcfDtSet.m_bMountDCF[sDcfDtSet.m_uiCurrDBIdx];

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetName
//  Description : This function creates name by given rtc time, and return fullspath and filename
//  @param[in] psRtcTime     input RtcTime
//  @param[out]FileFullPath  created fullpath
//  @param[out]FileName      created filename
//  @param[in]byCamStatus    camera status, if camera is exist or not
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetName(AHC_RTC_TIME* psRtcTime, INT8 *FileFullPath, INT8 *FileName, UINT8 byCamStatus)
{
    PSDATETIMEDCFDB pDB;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT )
    {
        return AHC_FALSE;
    }

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];
    pDB->byCamStatus = byCamStatus;
    return pDB->pCusAPI->pfCurGetPath(pDB, psRtcTime, (char*)FileFullPath, (char*)FileName);
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_DumpDB
//  Description : This function dumps all DB info. and show it on the UART
//------------------------------------------------------------------------------
void AIHC_DCFDT_DumpDB(void)
{
    INT i;
    for(i=0; i<DCF_DB_COUNT; i++)
    {
        AHC_DBG_MSG(1, "\n\nDB[%d]\n", i );
        AHC_DCFDT_DumpDb(&sDcfDtSet.m_sDB[i]);
    }

    AHC_DBG_MSG(1, "Total Clusters = %d\n", m_sMediaInfo.ulTotalClusters );

}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_AdjustAllocation
//  Description : This function changes the numerator setting by given type
//  @param[in] eType         input eType
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------

AHC_BOOL AHC_DCFDT_AdjustAllocation(DCF_STORAGE_ALLOC eType)
{
    UINT32 uiNumeratorDB[5];
    UINT32 uiDenominator;
    UINT64 uiTotalFileSize = 0;
    INT8 i;
    PSDATETIMEDCFDB pDB;
    UINT64 temp;

    switch(eType){

    case DCF_STORAGE_ALLOC_TYPE1:
        uiNumeratorDB[0] = DCF_CLUSTER_NUMERATOR1_DB0;
        uiNumeratorDB[1] = DCF_CLUSTER_NUMERATOR1_DB1;
        uiNumeratorDB[2] = DCF_CLUSTER_NUMERATOR1_DB2;
        uiNumeratorDB[3] = DCF_CLUSTER_NUMERATOR1_DB3;
        uiNumeratorDB[4] = DCF_CLUSTER_NUMERATOR1_DB4;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;

    case DCF_STORAGE_ALLOC_TYPE2:
        uiNumeratorDB[0] = DCF_CLUSTER_NUMERATOR2_DB0;
        uiNumeratorDB[1] = DCF_CLUSTER_NUMERATOR2_DB1;
        uiNumeratorDB[2] = DCF_CLUSTER_NUMERATOR2_DB2;
        uiNumeratorDB[3] = DCF_CLUSTER_NUMERATOR2_DB3;
        uiNumeratorDB[4] = DCF_CLUSTER_NUMERATOR2_DB4;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;

    case DCF_STORAGE_ALLOC_TYPE3:
        uiNumeratorDB[0] = DCF_CLUSTER_NUMERATOR3_DB0;
        uiNumeratorDB[1] = DCF_CLUSTER_NUMERATOR3_DB1;
        uiNumeratorDB[2] = DCF_CLUSTER_NUMERATOR3_DB2;
        uiNumeratorDB[3] = DCF_CLUSTER_NUMERATOR3_DB3;
        uiNumeratorDB[4] = DCF_CLUSTER_NUMERATOR3_DB4;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;

    case DCF_STORAGE_ALLOC_TYPE0:
    default:
        uiNumeratorDB[0] = DCF_CLUSTER_NUMERATOR_DB0;
        uiNumeratorDB[1] = DCF_CLUSTER_NUMERATOR_DB1;
        uiNumeratorDB[2] = DCF_CLUSTER_NUMERATOR_DB2;
        uiNumeratorDB[3] = DCF_CLUSTER_NUMERATOR_DB3;
        uiNumeratorDB[4] = DCF_CLUSTER_NUMERATOR_DB4;
        uiDenominator = DCF_CLUSTER_DENOMINATOR;
        break;
    }

    m_AllocType = eType;
    //Notice : if share folder storage type = fixed space, there won't calculate the space
    for( i=0; i< DCF_DB_COUNT; i++)
    {
        pDB = &sDcfDtSet.m_sDB[i];
        if(!pDB->bFormatFreeEnable){
            uiTotalFileSize += pDB->ullTotalObjectSize;
        }
        else{
            //CamID use front cam tmp, TBD.
            uiTotalFileSize += (pDB->ulTotalObjectNumByCam[DCF_CAM_FRONT] + pDB->ulTotalHiddenNumByCam[DCF_CAM_FRONT])
                               * DCF_SHARE_FOLDER_PER_FILE_SIZE;
        }
    }
    for( i=0; i< DCF_DB_COUNT; i++)
    {
        //change ulTotalClusters to DCF total cluster + total Free space
        //Notice: It must make sure that all DB has been mounted
        pDB = &sDcfDtSet.m_sDB[i];

#if (DCFDT_DEBUG)
        AHC_DBG_MSG(1, "uiTotalFileSize=%x\r\n",uiTotalFileSize);
        AHC_DBG_MSG(1, "pDB->ulClusterSize=%x;",pDB->ulClusterSize);
        AHC_DBG_MSG(1, " = %x\r\n",(uiTotalFileSize / pDB->ulClusterSize));
        AHC_DBG_MSG(1, "m_sMediaInfo.ulFreeClusters %d\r\n", m_sMediaInfo.ulFreeClusters);
#endif

        #if(DCF_SHARE_FOLDER_STORAGE_TYPE == DCF_SHARE_FOLDER_STORAGE_BY_SPACE)
        {
            temp = (m_sMediaInfo.ulFreeClusters + (uiTotalFileSize/pDB->ulClusterSize) - (DCF_SHARE_FOLDER_SPACE << 20 / pDB->ulClusterSize) );
            temp *= uiNumeratorDB[i];
            temp /= uiDenominator;

            sDcfDtSet.m_sDB[i].ulMaxSizeThresholdInCluster = temp;
            //sDcfDtSet.m_sDB[i].ulMaxSizeThresholdInCluster = (m_sMediaInfo.ulFreeClusters + ((uiTotalFileSize -  (DCF_SHARE_FOLDER_SPACE * 1024 * 1024)) / pDB->ulClusterSize) )
            //                                                 *uiNumeratorDB[i] / uiDenominator;
        }
        #elif(DCF_SHARE_FOLDER_STORAGE_TYPE == DCF_SHARE_FOLDER_STORAGE_BY_NUMERATOR)
        {
            sDcfDtSet.m_sDB[i].ulMaxSizeThresholdInCluster = (m_sMediaInfo.ulFreeClusters + (uiTotalFileSize / pDB->ulClusterSize))
                                                             *uiNumeratorDB[i] / uiDenominator;
        }
        #endif
#if (DCFDT_DEBUG)
        AHC_DBG_MSG(1, "DB[%d].ulMaxSizeThresholdInCluster=%d\r\n\r\n", i, sDcfDtSet.m_sDB[i].ulMaxSizeThresholdInCluster);
#endif
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileTH
//  Description : This function gets file number numerator threshold by seleted DB
//  @param[in] sType         input sType
//  @retval    AHC_TRUE      Success.
//  @retval    AHC_FALSE     Failed.
//------------------------------------------------------------------------------
UINT64 AHC_DCFDT_GetFileTH(DCF_STORAGE_ALLOC sType)
{
    switch(sType){
        case DCF_STORAGE_ALLOC_TYPE0:
            return DCF_FILE_NUMERATOR2_DB0;
            break;
         case DCF_STORAGE_ALLOC_TYPE1:
            return DCF_FILE_NUMERATOR2_DB1;
            break;
        case DCF_STORAGE_ALLOC_TYPE2:
            return DCF_FILE_NUMERATOR2_DB2;
            break;
         case DCF_STORAGE_ALLOC_TYPE3:
            return DCF_FILE_NUMERATOR2_DB3;
            break;
        default:
            return DCF_FILE_NUMERATOR2_DB0;
            break;

    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_SetRearCamPathFlag(for tmp use)
//  Description : This function set CamID to front / rear
//  @param[in] bSetRearCam   input CamID
//------------------------------------------------------------------------------
void AHC_DCFDT_SetRearCamPathFlag(AHC_BOOL bSetRearCam)
{
    if ((AHC_DCFDT_GetCurrentDBFlag() & DCFDT_DB_FLAG_HAS_REAR_CAM)) {
        sDcfDtSet.m_byCurrCamID = bSetRearCam;
    }
    else {
        if (bSetRearCam)
            AHC_DBG_ERR(1, "DCF_DUAL_CAM_ENABLE Disabled!\r\n");
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetRearCamPathFlag(for tmp use)
//  Description : This function gets CamID to front / rear
//  @param[in] bSetRearCam   input CamID
//------------------------------------------------------------------------------
void AHC_DCFDT_GetRearCamPathFlag(AHC_BOOL *bGetRearCam)
{
    *bGetRearCam = sDcfDtSet.m_byCurrCamID ;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_SearchAvailableFileSlot
//  Description : (Format Free)This function search the available file name and use it to add file
//  @param[out]   szFilePathName   output FilePathName which can be use to add new file
//  @param[in]    byCamID          input select camID
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_SearchAvailableFileSlot(UINT8 byCamID, char* szFilePathName)
{
    PSDATETIMEDCFDB pDB;
    SFILENAME_INFO  FileNameInfo;
    SNODE_OP_PAK    NodeOpPak;

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    //if camID = master, process normal search flow,
    //else
    if(byCamID == DCFDT_FILEINDEX_MASTERCAMID)
    {
        if( pDB->pFileHead == NULL )
        {
            AHC_DBG_MSG(1, "There's no file node !!\n");
            return AHC_FALSE;
        }
        else
        {
            PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
            PSSUBNODE      psSubNodeCur; //only for front Cam
            while(psParentNodeCur)
            {
                psSubNodeCur = psParentNodeCur->pCamNodeHead;
                while(psSubNodeCur)
                {
                    if((psSubNodeCur->byFileAttr & DCFDT_FILEATTR_HIDDEN) && (byCamID == psSubNodeCur->byCamID))
                    {
                        AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNodeCur->byCamID, psParentNodeCur, szFilePathName, DCF_MAX_FILE_NAME_SIZE);
                        AHC_DCFDT_UpdateDBStatistics(pDB, psSubNodeCur->byCamID, psSubNodeCur, DCFDT_STATISTICS_DELETE);
                        //delete sub node in DB
                        //force node operation to remove sub node
                        pDB->bFormatFreeEnable = AHC_FALSE;
                        //set NodeOpPak value
                        {
                            NodeOpPak.byCamID      = psSubNodeCur->byCamID;
                            NodeOpPak.FileNameInfo = FileNameInfo;
                            NodeOpPak.psParentNode = psParentNodeCur;
                            NodeOpPak.psSubNode    = NULL;
                            NodeOpPak.byOperation  = DCFDT_NODE_DELETE_SUB;
                        }
                        pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);
                        //resume
                        pDB->bFormatFreeEnable = AHC_TRUE;
                        pDB->psLastSearchedParentNode = psParentNodeCur;
                        AHC_DCFDT_Unlock(pDB);
                        return AHC_TRUE;
                    }
                    psSubNodeCur = psSubNodeCur->pNext;
                }
                psParentNodeCur = psParentNodeCur->pNext;
            }
            //if there's no hidden file, search the pFileHead(the earliest file)
            if(psParentNodeCur == NULL)
            {
                psParentNodeCur = pDB->pFileHead;
                while( psParentNodeCur )
                {
                    psSubNodeCur = psParentNodeCur->pCamNodeHead;
                    while((psSubNodeCur != NULL) && (byCamID == psSubNodeCur->byCamID))
                    {
                        AHC_BOOL bIsCharLock = (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_CHARLOCK) ? AHC_TRUE : AHC_FALSE;
                        if(!bIsCharLock)
                        {
                            AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNodeCur->byCamID, psParentNodeCur, szFilePathName, DCF_MAX_FILE_NAME_SIZE);
                            AHC_DCFDT_UpdateDBStatistics(pDB, psSubNodeCur->byCamID, psSubNodeCur, DCFDT_STATISTICS_DELETE);

                            //delete sub node in DB
                            //force node operation to remove sub node
                            pDB->bFormatFreeEnable = AHC_FALSE;
                            {
                                NodeOpPak.byCamID      = psSubNodeCur->byCamID;
                                NodeOpPak.FileNameInfo = FileNameInfo;
                                NodeOpPak.psParentNode = psParentNodeCur;
                                NodeOpPak.psSubNode    = NULL;
                                NodeOpPak.byOperation  = DCFDT_NODE_DELETE_SUB;
                            }
                            pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);
                            //resume
                            pDB->bFormatFreeEnable = AHC_TRUE;
                            pDB->psLastSearchedParentNode = psParentNodeCur;
                            AHC_DCFDT_Unlock(pDB);
                            return AHC_TRUE;
                        }
                        psSubNodeCur = psSubNodeCur->pNext;
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
            }
        }
    }
    else
    {
        if(pDB->psLastSearchedParentNode != NULL)
        {
            AHC_BOOL sRet;
            sRet = AHC_DCFDT_GetFullPathByParentNode(pDB, byCamID, pDB->psLastSearchedParentNode, szFilePathName, DCF_MAX_FILE_NAME_SIZE);
            //if sub node not found, search next available sub node which parent node do not have master sub node
            AHC_DBG_MSG(1, "\r\n");
            if(!sRet)
            {
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                PSDATETIMEFILE psParentNodeWithoutMaster = NULL;
                while(psParentNodeCur)
                {
                    if(!(psParentNodeCur->byCamExist & (DCF_CAM_EXIST_BASE << DCFDT_FILEINDEX_MASTERCAMID)))
                    {
                        psParentNodeWithoutMaster = psParentNodeCur;
                        break;
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }
                if(psParentNodeWithoutMaster){
                    sRet = AHC_DCFDT_GetFullPathByParentNode(pDB, byCamID, psParentNodeWithoutMaster, szFilePathName, DCF_MAX_FILE_NAME_SIZE);
                    if(!sRet){
                        AHC_DBG_MSG(1, "%s Available node illegal\r\n", __FUNCTION__);
                        AHC_DCFDT_Unlock(pDB);
                        return AHC_FALSE;
                    }
                    pDB->psLastSearchedParentNode = psParentNodeWithoutMaster;
                }
                else{
                    //not found ParentNodeWithoutMaster, it means sub nodes are asymmetric
                    AHC_DBG_MSG(1, "No available file node to use\r\n");
                    AHC_DCFDT_Unlock(pDB);
                    return AHC_FALSE;
                }

            }
            //remove node
            pDB->bFormatFreeEnable = AHC_FALSE;
            {
                NodeOpPak.byCamID      = byCamID;
                NodeOpPak.FileNameInfo = FileNameInfo;
                NodeOpPak.psParentNode = pDB->psLastSearchedParentNode;
                NodeOpPak.psSubNode    = NULL;
                NodeOpPak.byOperation  = DCFDT_NODE_DELETE_SUB;
            }
            pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);
            //resume
            pDB->bFormatFreeEnable = AHC_TRUE;
            //clean node
            pDB->psLastSearchedParentNode = NULL;
            AHC_DCFDT_Unlock(pDB);
            return AHC_TRUE;
        }
        AHC_DBG_MSG(1, "Warning : psLastSearchedParentNode = NULL, master cam ID should search first\r\n");
    }
    AHC_DCFDT_Unlock(pDB);

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_TemplateCmp
//  Description : Given a input and template, this fuction would cmp them if the input match the template?
//                If matched,
//  @param[in] pInput        input string
//  @param[in] pTemplate     template string
//  @retval    AHC_TRUE      the input matched template.
//  @retval    AHC_FALSE     not matched
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_TemplateCmp( char* pInput, char* pTemplate )
{
    while( *pTemplate && *pInput )
    {
        if( *pTemplate == '%' )
        {
            pTemplate++;
            while(*pTemplate)
            {
                pInput++;
                pTemplate++;
                if( (*pTemplate == 'X') || (*pTemplate == 'x') || (*pTemplate == 'd')
                 || (*pTemplate == 'z') || (*pTemplate == 's') )
                 {
                    pTemplate++;
                    break;
                 }
            }
        }
        else if( *pTemplate == *pInput )
        {
            pInput++;
            pTemplate++;
        }
        else
        {
            return AHC_FALSE;
        }
    }

    return AHC_TRUE;
}

//Get Root Dir Name with DB Type
INT8* AHC_DCFDT_GetRootDirNameT(DCF_DB_TYPE dbType, UINT8 byCamID)
{
    PSDATETIMEDCFDB pDB;

    if (dbType >= DCF_DB_COUNT) {
        AHC_DBG_MSG(1, "Invalid dbType\r\n");
        return NULL;
    }
    pDB = &sDcfDtSet.m_sDB[dbType];
    return pDB->szFolderPath[byCamID];
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_IsFullNameDbType
//  Description : This function returns if fullfilename is dbType
//  @retval AHC_TRUE If the input name matches any of DCF DB
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_IsFullNameDbType(char* fullFileName, DCF_DB_TYPE dbType)
{
    INT32 len;
    INT32 cam;
    INT8* rootDir = NULL;
    AHC_BOOL bFound = AHC_FALSE;

    for (cam = 0; cam < DCFDT_CAM_NUM; ++cam) {
        rootDir = AHC_DCFDT_GetRootDirNameT(dbType, cam);
        if (rootDir == NULL) {
            break;
        }
        len = STRLEN(rootDir);
        if (0 == strncmp(rootDir, fullFileName, len)) {
            bFound = AHC_TRUE;
            break;
        }
    }
    return bFound;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetDbTypeByFullName
//  Description : This function returns dbType with fill file name
//  @retval AHC_TRUE If the input name matches any of DCF DB
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetDbTypeByFullName(char* fullFileName, DCF_DB_TYPE* dbType)
{
    DCF_DB_TYPE type;
    AHC_BOOL bFound = AHC_FALSE;

    if (dbType) {
            *dbType = DCF_DB_TYPE_MAX_NUMBER;
    }
    for (type = DCF_DB_TYPE_DB0_NORMAL; type < DCF_DB_COUNT; ++type) {
        if (AHC_TRUE == AHC_DCFDT_IsFullNameDbType(fullFileName, type)) {
            bFound = AHC_TRUE;
            break;
        }
#if 0
        for (cam = 0; cam < DCFDT_CAM_NUM; ++cam) {
            rootDir = AHC_DCFDT_GetRootDirNameT(type, cam);
            if (rootDir == NULL) {
                break;
            }
            len = STRLEN(rootDir);
            if (0 == strncmp(rootDir, fullFileName, len)) {
                if(dbType)
                    *dbType = type;
                bFound = AHC_TRUE;
                break;
            }
        }
        if (bFound)
            break;
#endif
    }

    return bFound;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetRootDirName
//  Description : This function returns root dir folder path of current DB
//  @retval       root dir folder path of current DB
//------------------------------------------------------------------------------
INT8* AHC_DCFDT_GetRootDirName(void)
{
    PSDATETIMEDCFDB pDB;
    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];
    return pDB->szFolderPath[sDcfDtSet.m_byCurrCamID];
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_CheckFileCamStatus
//  Description : This Function checks the file status by index in current CamID,
//                the status would show which Cam does exist
//  @param[in]    uiIndex in current CamID
//  @param[out]   status : DCF_CAM_FRONT_EXIST, DCF_CAM_REAR_EXIST....
//  @retval       AHC_TRUE  find the parent node
//  @retval       AHC_FALSE failed
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode = NULL;

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    AHC_DCFDT_Lock(pDB);
    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB, uiIndex);
    if(psParentNode != NULL)
    {
        *status = psParentNode->byCamExist;
        AHC_DCFDT_Unlock(pDB);
        return AHC_TRUE;
    }
    else{
        AHC_DCFDT_Unlock(pDB);
        return AHC_FALSE;
    }
}
//------------------------------------------------------------------------------
//  Function    : AIHC_DCFDT_UpdateLockFileTable
//  Description : This function used for Char lock. When file operation is going to char lock file
//                , it would call this function to update lock file table, if the table is full
//                , it would delete the earlist file and update it.(for DCFDT inside use)
//  @param[in] psParentNode  the ParentNode which would like to add to lock table
//  @param[out]bDeleteFile   if the function delete the earlist file, bDeleteFile = true
//  @param[in] byOperation   operation to LOCKFILE/UNLOCKFILE
//------------------------------------------------------------------------------
void AIHC_DCFDT_UpdateLockFileTable(PSDATETIMEFILE psParentNode, AHC_BOOL *bDeleteFile, UINT8 byOperation)
{
    #define LOCKFILETABLE_EMPTY 0x0

    UINT32          i, j, k;
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psDelNode = NULL;
    UINT32          ulLockFileNum;
    AHC_BOOL        bRet;
    AHC_BOOL        bSort = AHC_FALSE;

    if (bDeleteFile)
        *bDeleteFile = AHC_FALSE;

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];
    //update node into table
    switch(byOperation)
    {
    //add node to lock table
    case DCFDT_LOCKTABLE_LOCK:
    {
        for( i = 0; i < MAX_LOCK_FILE_NUM; i ++)
        {
            //if repeated node, do not update
            if(pDB->ulCharLockFileTable[i] == (UINT32)psParentNode)
            {
                AHC_DBG_MSG(1, "Repeated LockFile\r\n");
                //pDB->ulCharLockFileTable[i] = LOCKFILETABLE_EMPTY;
                break;
            }
            //put node into empty slot
            if(pDB->ulCharLockFileTable[i] == LOCKFILETABLE_EMPTY)
            {
                pDB->ulCharLockFileTable[i] = (UINT32)psParentNode;
                ulLockFileNum = i;
                bSort = AHC_TRUE;
                break;
            }
            //if there's no slot in this table
            if(i == (MAX_LOCK_FILE_NUM - 1) && pDB->ulCharLockFileTable[i] != LOCKFILETABLE_EMPTY)
            {
                #if (DCFDT_CUSTOM_MODULE_MODE != DCFDT_MODULEMODE_DATETIME_INDEX)
                PSDATETIMEFILE psCurNode;
                //compare all node datetime in table
                UINT32 uiCmpCount = 0;
                for(j = 0; j < MAX_LOCK_FILE_NUM; j++)
                {
                    psCurNode = (PSDATETIMEFILE)pDB->ulCharLockFileTable[j];
                    if(psCurNode->FileNameInfo.nDateTime > psParentNode->FileNameInfo.nDateTime)
                    {
                        uiCmpCount++;
                    }
                }
                //if add node Dateime smaller than all node in table, delete add node
                if(uiCmpCount == MAX_LOCK_FILE_NUM)
                {
                    psDelNode = psParentNode;
                }
                else
                #endif
                {
                    psDelNode = (PSDATETIMEFILE)pDB->ulCharLockFileTable[0];
                    //shift addr from j+1 to j
                    for(j = 0; j < MAX_LOCK_FILE_NUM-1; j++)
                    {
                        pDB->ulCharLockFileTable[j] = pDB->ulCharLockFileTable[j+1];
                    }
                    pDB->ulCharLockFileTable[i] = (UINT32)psParentNode;
                    ulLockFileNum = MAX_LOCK_FILE_NUM;
                    bSort = AHC_TRUE;
                }
            }
        }

        //Bobble Sort
        if(bSort)
        {
            AHC_BOOL bSwap = AHC_TRUE;
            PSDATETIMEFILE psCurNodePlus,psCurNode;
            UINT32         ulTmpNodeAddr;

            //Bobble Sort
            for(j = 0; j < ulLockFileNum && bSwap; j++)
            {
                bSwap = AHC_FALSE;
                for(k = 0; k < ulLockFileNum - j - 1; k++)
                {
                    psCurNodePlus = (PSDATETIMEFILE)pDB->ulCharLockFileTable[k+1];
                    psCurNode     = (PSDATETIMEFILE)pDB->ulCharLockFileTable[k];
                    if(psCurNodePlus->FileNameInfo.nDateTime < psCurNode->FileNameInfo.nDateTime)
                    {
                        //swap
                        ulTmpNodeAddr = pDB->ulCharLockFileTable[k+1];
                        pDB->ulCharLockFileTable[k+1] = pDB->ulCharLockFileTable[k];
                        pDB->ulCharLockFileTable[k]   = ulTmpNodeAddr;
                        bSwap = AHC_TRUE;
                    }
                }
            }
        }

        if(psDelNode != NULL)
        {
            AHC_DBG_MSG(1, "delete file\r\n");
            bRet = AHC_DCFDT_DbRemoveFileByParentNode(pDB, psDelNode, AHC_TRUE);
            if(!bRet){
                AHC_DBG_MSG(1, "Remove node error!!\r\n");
            }

            if (bDeleteFile)
                *bDeleteFile = AHC_TRUE;
        }
    }
    break;
    //unlock node from lock table, rollback to normal file, so not need to delete file
    case DCFDT_LOCKTABLE_UNLOCK:
    {
        AHC_BOOL bFound = AHC_FALSE;
        for( i = 0; i < MAX_LOCK_FILE_NUM; i ++)
        {
            if(pDB->ulCharLockFileTable[i] == (UINT32)psParentNode)
            {
                bFound = AHC_TRUE;
                //shift addr from j+1 to j
                for(j = i; j < MAX_LOCK_FILE_NUM-1; j++)
                {
                    pDB->ulCharLockFileTable[j] = pDB->ulCharLockFileTable[j+1];
                }
                //set last addr = LOCKFILETABLE_EMPTY
                pDB->ulCharLockFileTable[MAX_LOCK_FILE_NUM - 1] = LOCKFILETABLE_EMPTY;
                break;
            }
        }
        if(!bFound){
            AHC_DBG_MSG(1, "Unlock failed!! There's no node matched!!\r\n");
        }
    }
    break;
    default:
    break;
    }
}

AHC_BOOL AHC_DCFDT_ResetDualWriteBytes(void)
{
    #if (AHC_SHAREENC_SUPPORT)
    m_ulShareRecdRepackAuxWriteFileSize = 0;
    m_ulShareRecdTotalWriteFileSize = 0;
    #endif

    return AHC_TRUE;
}

//ResetDBStatistics
void AHC_DCFDT_ResetDBStatistics(PSDATETIMEDCFDB pDB)
{
    pDB->ulTotalObjectNum           = 0;
    //pDB->ulTotalRearCamObjectNum    = 0;
    pDB->ullTotalObjectSize         = 0;
    pDB->ulTotalLockedObjects       = 0;
    pDB->ullTotalLockedObjectSize   = 0;
    pDB->ulTotalUnlockedObjects     = 0;
    pDB->ullTotalUnlockedObjectSize = 0;

    MEMSET(pDB->ullUnlockedObjectNum,  0, sizeof(pDB->ullUnlockedObjectNum));
    MEMSET(pDB->ullUnlockedObjectSize, 0, sizeof(pDB->ullUnlockedObjectSize));
    MEMSET(pDB->ullLockedObjectNum,    0, sizeof(pDB->ullLockedObjectNum));
    MEMSET(pDB->ullLockedObjectSize,   0, sizeof(pDB->ullLockedObjectSize));
}

MMP_ERR AHC_DCFDT_SizeinFile_Update(char* szFilename)
{
    MMP_ERR     err = MMP_ERR_NONE;

#if (AHC_SHAREENC_SUPPORT) //Ask Jerry???
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulActualSize;
    MMP_BYTE    b2ndFullName[MAX_FULL_FILENAME_SIZE];

    MEMSET(b2ndFullName, 0, sizeof(b2ndFullName));
    STRCPY(b2ndFullName,(INT8*)AHC_UF_GetRootDirName());
    STRCAT(b2ndFullName,"\\");
    STRCAT(b2ndFullName, szFilename);

    err = MMPS_FS_FileOpen(b2ndFullName, strlen(b2ndFullName), "a+b", strlen("a+b"),  &ulFileId );
    err |= MMPS_FS_FileSeek(ulFileId, SHARE_FILESIZE_OFFSET, MMPS_FS_SEEK_SET);
    #if 1
    err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&m_ulShareRecdRepackAuxWriteFileSize, sizeof(m_ulShareRecdRepackAuxWriteFileSize), &ulActualSize);
    #else
    err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&m_ulShareRecdTotalWriteFileSize, sizeof(m_ulShareRecdTotalWriteFileSize), &ulActualSize);
    #endif
    err |= MMPS_FS_FileClose(ulFileId);

    AHC_DCFDT_ResetDualWriteBytes();

    if (MMP_ERR_NONE != err)
    {
        AHC_DBG_MSG(1, FG_RED("Update %s error - 1 \r\n"), szFilename);
    }
#endif
    return err;
}

UINT32 AHC_DCFDT_GetDualEncFileSizeT(DCF_DB_TYPE dbType, char *pchFileName)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulWriteCnt = 0;
    UINT32      ulWriteByte = 0;
    MMP_BYTE    b2ndFileName[MAX_FULL_FILENAME_SIZE];
    char*       pos;

    STRCPY(b2ndFileName,(INT8*)AHC_DCFDT_GetRootDirNameT(dbType, 0));
    STRCAT(b2ndFileName,"\\");
    pos = strstr(pchFileName, b2ndFileName);
    if (pos != NULL) {//input parameter is a full path, skip root
        pchFileName += STRLEN(b2ndFileName);
    }
    STRCAT(b2ndFileName,(INT8*)pchFileName);

    err = MMPS_FS_FileOpen(b2ndFileName, strlen(b2ndFileName), "a+b", strlen("a+b"),  &ulFileId );
    err |= MMPS_FS_FileSeek(ulFileId, SHARE_FILESIZE_OFFSET, MMPS_FS_SEEK_SET);
    err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&ulWriteByte, sizeof(ulWriteByte), &ulWriteCnt);

    err |= MMPS_FS_FileClose(ulFileId);

    if (MMP_ERR_NONE != err)
    {
        AHC_DBG_MSG(1, FG_RED("Fetch %s fs error - 1 \r\n"), b2ndFileName);
        return 0;
    }
    return ulWriteByte;
}

UINT32 AHC_DCFDT_GetDualEncFileSize(char *pchFileName)
{
    //DCF_DB_TYPE sDB = AHC_DCFDT_GetDB();
    UINT32 size;

    //AHC_DCFDT_SelectDB(DCF_DB_FORMAT_FREE_DB);

    size = AHC_DCFDT_GetDualEncFileSizeT(DCF_DB_FORMAT_FREE_DB, pchFileName);

    //AHC_DCFDT_SelectDB(sDB);

    return size;
}

MMP_BOOL AHC_DCFDT_CheckFormatFreeDBSizeTH(UINT DBIdx)
{
    #if (AHC_SHAREENC_SUPPORT)
    UINT64  allocatedcluster, requiredcluster;
    if (DBIdx > DCF_DB_COUNT)
        return MMP_FALSE;

    if ( (sDcfDtSet.m_bDBEnable[DBIdx]) && (DBIdx == DCF_DB_FORMAT_FREE_DB) )
    {
        allocatedcluster = (sDcfDtSet.m_sDB[DBIdx].ullDiskClusters * DCF_CLUSTER_NUMERATOR_DB4) / DCF_CLUSTER_DENOMINATOR;
        //requiredcluster = DCF_SHARE_FOLDER_FILE_NUM * SHARERECD_FILE_LENGTH / sDcfDtSet.m_sDB[DBIdx].ulClusterSize;
        requiredcluster = formatfreefilenum* SHARERECD_FILE_LENGTH / sDcfDtSet.m_sDB[DBIdx].ulClusterSize;
        //AHC_DBG_MSG(1, "allocated: %llu; required: %llu\r\n", allocatedcluster, requiredcluster);

        if (allocatedcluster < requiredcluster)
        {
            AHC_DBG_MSG(1, FG_RED("Allocated: %llu < Required: %llu \r\n"), allocatedcluster, requiredcluster);
            AHC_DCFDT_ResetDBStatistics(&sDcfDtSet.m_sDB[DBIdx]);
            sDcfDtSet.m_bDBEnable[DBIdx] = AHC_FALSE;
            sDcfDtSet.m_bMountDCF[DBIdx] = AHC_FALSE;
            return AHC_FALSE;
        }
    }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_CheckFormatFreeFolderFileNum
//  Description : This function do several steps to check the file num in format free folder is equal to
//                Max file num. If equal, it would pass. If file num exceed Max num, disable the folder.
//                If need more file, it would create legal file tile the file num is enough.
//  @param[in] pDB  input DB
//  @retval    AHC_TRUE      operate sucess
//  @retval    AHC_FALSE     invalid DB or illegal DB index
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_CheckFormatFreeFolderFileNum(PSDATETIMEDCFDB pDB)
{
#if (AHC_SHAREENC_SUPPORT) //Ask Jerry???
    //check if format free folder satisfy folder num condition
    INT32  iNeedFileNum;
    UINT32 uiMaxFormatFreeFileNum;
    //get uiMaxFormatFreeFileNum by SD card free space and numerator,
    //if space enough ,the uiMaxFormatFreeFileNum equal to DCF_SHARE_FOLDER_FILE_NUM
    if (!AHC_DCFDT_UpdateFormatFreeMaxFileNum(pDB, &uiMaxFormatFreeFileNum)){
        AHC_DBG_MSG(1, " DCFDT_UpdateFormatFreeMaxFileNum failed.\r\n");
        return AHC_FALSE;
    }
    formatfreefilenum = uiMaxFormatFreeFileNum;
    //get need file num
    iNeedFileNum = uiMaxFormatFreeFileNum - (pDB->ulTotalHiddenNumByCam[DCF_CAM_FRONT] + pDB->ulTotalObjectNumByCam[DCF_CAM_FRONT]); //only support front cam,TBD
    //if need num exceed max num, disable DB
    if(iNeedFileNum < 0)
    {
        AHC_DCFDT_UpdateDBStatistics(pDB, NULL, NULL, DCFDT_STATISTICS_RESET);
        sDcfDtSet.m_bDBEnable[pDB->ubDBIndex] = AHC_FALSE;
        AHC_DBG_MSG(1, FG_RED("Too many files in DB:%d (%d)\r\n"), DCF_DB_FORMAT_FREE_DB, DCF_SHARE_FOLDER_FILE_NUM);
    }
    //if need num equal, do nothing
    //if need num > 0, call CB func to make need file
    else if(iNeedFileNum > 0)
    {
        //call callback of create format free file func
        if(AHC_DCFDT_CB_CreatFormatFreeFile){
        //AHC_DBG_MSG(1, "need share num=%d\r\n", iNeedFileNum);
            AHC_DCFDT_CB_CreatFormatFreeFile((UINT8*)(&iNeedFileNum));
        }
        else{
            AHC_DBG_MSG(1, "AHC_DCFDT_CB_CreatFormatFreeFile does not registed\r\n");
            AHC_DBG_MSG(1, "mount DB[%d] failed\r\n", pDB->ubDBIndex);
        }
        //parse DB again
        //AHC_DCFDT_ParseFolder(pDB, DCF_CAM_FRONT);
        //format free does not support dual cam by Chuni Li ,TBD
        //#if (DCF_DUAL_CAM_ENABLE && DCFDT_CAM_NUM > 1)
        //AHC_DCFDT_ParseFolder(pDB, DCF_CAM_REAR);
        //#endif
    }
    else if(iNeedFileNum == 0)
    {
        AHC_DBG_MSG(1, "Format Free File Num satisfy DCF_SHARE_FOLDER_FILE_NUM %d\r\n", uiMaxFormatFreeFileNum);
    }
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_UpdateFormatFreeMaxFileNum
//  Description : This function updates the max file num of format free folder,
//                if SD card free space is not enough for DCF_SHARE_FOLDER_FILE_NUM,
//                if would recalculate max num by free space
//  @param[in] pDB           input DB
//  @param[out]pulMaxFileNum output Max File Num determine by SD card free space and define max file num
//  @retval    AHC_TRUE      operate sucess
//  @retval    AHC_FALSE     invalid DB or illegal DB index
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_UpdateFormatFreeMaxFileNum(PSDATETIMEDCFDB pDB, UINT32 *pulMaxFileNum)
{
    if (pDB->ubDBIndex > DCF_DB_COUNT){
        AHC_DBG_MSG(1, "Input DB Index illegal %d\r\n", pDB->ubDBIndex);
        return AHC_FALSE;
    }

    if ((sDcfDtSet.m_bDBEnable[pDB->ubDBIndex]) && (pDB->ubDBIndex == DCF_DB_FORMAT_FREE_DB))
    {
        UINT32 ulMaxFileSize;
        UINT32 ulShareRecdFileLength = SHARERECD_FILE_LENGTH;

        //TBD.
        #if(DCF_SHARE_FOLDER_STORAGE_TYPE == DCF_SHARE_FOLDER_STORAGE_BY_SPACE)
        {
            ulMaxFileSize = DCF_SHARE_FOLDER_SPACE * 1024 * 1024;
        }
        #elif(DCF_SHARE_FOLDER_STORAGE_TYPE == DCF_SHARE_FOLDER_STORAGE_BY_NUMERATOR)
        {
            ulMaxFileSize = pDB->ulMaxSizeThresholdInCluster * sDcfDtSet.m_sDB[pDB->ubDBIndex].ulClusterSize;
        }
        #endif

        if (ulShareRecdFileLength != 0) {
            *pulMaxFileNum = ulMaxFileSize / ulShareRecdFileLength;
        }
        else {
            *pulMaxFileNum = ulMaxFileSize;
        }

        if (*pulMaxFileNum > DCF_SHARE_FOLDER_FILE_NUM) {
            *pulMaxFileNum = DCF_SHARE_FOLDER_FILE_NUM;
        }

        return AHC_TRUE;
    }
    #if (AHC_SHAREENC_SUPPORT)
    AHC_DBG_MSG(1, "DB[%d], not FormatFree Folder\r\n", pDB->ubDBIndex);
    #endif
    return AHC_FALSE;
}

INT32 AHC_DCFDT_UpdateFormatFreeDBFileNum(UINT8 DBIdx)
{
    #if (AHC_SHAREENC_SUPPORT)
    UINT64  allocatedcluster;

    if (DBIdx > DCF_DB_COUNT)
        return MMP_FALSE;

    if ( (sDcfDtSet.m_bDBEnable[DBIdx]) && (DBIdx == DCF_DB_FORMAT_FREE_DB) )
    {
        allocatedcluster = (sDcfDtSet.m_sDB[DBIdx].ullDiskClusters * DCF_CLUSTER_NUMERATOR_DB4) / DCF_CLUSTER_DENOMINATOR;
        formatfreefilenum = allocatedcluster * sDcfDtSet.m_sDB[DBIdx].ulClusterSize / SHARERECD_FILE_LENGTH;
        AHC_DBG_MSG(1, "Support %d share files\r\n", formatfreefilenum);

        if (formatfreefilenum > DCF_SHARE_FOLDER_FILE_NUM)
            formatfreefilenum = DCF_SHARE_FOLDER_FILE_NUM;

        return formatfreefilenum;
    }
    #endif

    return 0;
}

INT32 AHC_DCFDT_GetFormatFreeDBFileNum(UINT DBIdx)
{
    #if (AHC_SHAREENC_SUPPORT)
        return formatfreefilenum;
    #endif

    return 0;
}

//This func customized for multi DB browser which used in MIMF (Notice : only use for single cam)
AHC_BOOL AHC_DCFDT_GetIndexbyDBandFileNameInfo(UINT8 byDBIndex, SFILENAME_INFO FileNameInfo, UINT32* DCFIndex)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;
    INT32           nFileCount = -1;
    AHC_BOOL        bfound      = AHC_FALSE;

    if( sDcfDtSet.m_uiCurrDBIdx >= DCF_DB_COUNT ){
        return AHC_FALSE;
    }
    pDB = &sDcfDtSet.m_sDB[byDBIndex];
    psParentNode = pDB->pFileHead;

    while(psParentNode)
    {
        //if the parent node exist the cam file, index++
        if(psParentNode->byCamExist & (DCF_CAM_EXIST_BASE << sDcfDtSet.m_byCurrCamID)){
            nFileCount++;
        }

        if(FileNameInfo.nDateTime == psParentNode->FileNameInfo.nDateTime &&
           FileNameInfo.uiFileIndex == psParentNode->FileNameInfo.uiFileIndex){
            *DCFIndex = nFileCount;
            bfound = AHC_TRUE;
            break;
        }
        psParentNode = psParentNode->pNext;
    }

    if(!bfound){
        AHC_DBG_MSG(1, "%s Index not found by DateTime %d Index %d\r\n", __FUNCTION__, FileNameInfo.nDateTime, FileNameInfo.uiFileIndex);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}
//
AHC_BOOL AHC_DCFDT_CheckShareFileNumForAddFile(PSDATETIMEDCFDB pDB, UINT8 byCamID)
{
    UINT32 ulMaxFileNum;
    UINT32 ulTotalFileNum = pDB->ulTotalObjectNumByCam[byCamID] + pDB->ulTotalHiddenNumByCam[byCamID];

    AHC_DCFDT_UpdateFormatFreeMaxFileNum(pDB, &ulMaxFileNum);
    if(pDB->ubDBIndex == DCF_DB_FORMAT_FREE_DB && ulTotalFileNum != (ulMaxFileNum - 1))
    {
        AHC_DBG_MSG(1, "Error!!Wrong File number in Share folder %d\r\n", ulTotalFileNum);
        if(ulTotalFileNum > (ulMaxFileNum - 1))
        {
            AHC_DBG_MSG(1, "UI Flow did not call AHC_DCFDT_SearchAvailableFileSlot before getname2\r\n");
            AHC_DBG_MSG(1, "Or switch wrong DB and add file to Share DB\r\n");
            AHC_DBG_MSG(1, "Please check UI flow\r\n");
        }
        else if(ulTotalFileNum < (ulMaxFileNum - 1))
        {
            AHC_DBG_MSG(1, "Repeated call func AHC_DCFDT_SearchAvailableFileSlot\r\n");
        }
        return AHC_FALSE;
    }

    return AHC_TRUE;
}
//------------------------------------------------------------------------------
//  Function    : AHC_DCFDT_GetFileInfoByVisitNode
//  Description : This function visits node by operation, and get info by current node.
//                And this function is thread save.
//  @param[in] DBtype        input DB
//  @param[in] CamID         input CamID
//  @param[out]Info          file info
//  @param[in] Op            operation
//  @retval    AHC_TRUE      operate sucess
//  @retval    AHC_FALSE     invalid operate or no more node
//------------------------------------------------------------------------------
AHC_BOOL AHC_DCFDT_GetFileInfoByVisitNode(DCF_DB_TYPE DBtype, DCF_CAM_ID CamID, DCF_INFO *Info, UINT8 Op)
{
    PSDATETIMEDCFDB pDB;
    AHC_BOOL        bFound = AHC_FALSE;
    AHC_RTC_TIME    RTCtime;
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;

    pDB = &sDcfDtSet.m_sDB[DBtype];

    if(DBtype >= DCF_DB_TYPE_MAX_NUMBER){
        AHC_DBG_MSG(1, "%s Illegal DB%d\r\n", __FUNCTION__, DBtype);
        return AHC_FALSE;
    }
    if(pDB->ulTotalObjectNum == 0){
        AHC_DBG_MSG(1, "%s No file in DB%d\r\n", __FUNCTION__, DBtype);
        return AHC_TRUE;
    }
    if(pDB->pFileHead == NULL || pDB->pFileTail == NULL){
        AHC_DBG_MSG(1, "DB nodehead/tail == NULL\r\n");
        return AHC_TRUE;
    }

    AHC_DCFDT_Lock(pDB);
    if(Op == DCF_NODE_VISIT_NODEHEAD || Op == DCF_NODE_VISIT_NODETAIL)
    {
        PSDATETIMEFILE pStartNode;
        pStartNode = (Op == DCF_NODE_VISIT_NODEHEAD) ? pDB->pFileHead : pDB->pFileTail;
        //visit filehead/filetail
        if(pStartNode != NULL)
        {
            psParentNode = pStartNode;
            while(psParentNode)
            {
                psSubNode = psParentNode->pCamNodeHead;
                while(psSubNode)
                {
                    if(psSubNode->byCamID == CamID && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN))
                    {

                        AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, Info->FilePath, sizeof(Info->FilePath));
                        AHC_DCFDT_GetFileNameBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, Info->FileName);
                        Info->bReadOnly  = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
                        Info->FileType   = psSubNode->byFileType;
                        Info->uiFileSize = psSubNode->nSizeInCluster * pDB->ulClusterSize;
                        AHC_DT_SecondsToDateTime(psParentNode->FileNameInfo.nDateTime, &RTCtime);
                        Info->uwYear     = RTCtime.uwYear;
                        Info->uwMonth    = RTCtime.uwMonth;
                        Info->uwDay      = RTCtime.uwDay;
                        Info->uwHour     = RTCtime.uwHour;
                        Info->uwMinute   = RTCtime.uwMinute;
                        Info->uwSecond   = RTCtime.uwSecond;
                        Info->bIsFileDownload = (psSubNode->byFileAttr & DCFDT_FILEATTR_ISDOWNLOAD) ? AHC_TRUE : AHC_FALSE;
                        pDB->psCurrParentNode = psParentNode;
                        bFound = AHC_TRUE;
                        goto SearchEnd;
                    }
                    psSubNode = psSubNode->pNext;
                }

                if(Op == DCF_NODE_VISIT_NODEHEAD){
                    psParentNode = psParentNode->pNext;
                }
                else if(Op == DCF_NODE_VISIT_NODETAIL){
                    psParentNode = psParentNode->pPrev;
                }
            }
        }
        else
        {
            AHC_DBG_MSG(1, "There's no Node in DB %d\r\n", pDB->ubDBIndex);
        }
    }
    else if(Op == DCF_NODE_VISIT_FORWARD || Op == DCF_NODE_VISIT_REWIND)
    {
        if(pDB->psCurrParentNode == NULL)
        {
            AHC_DBG_MSG(1, "Wrong Operation Order, should start from FileHead/FileTail\r\n");
            goto SearchEnd;
        }

        if(Op == DCF_NODE_VISIT_FORWARD)
            psParentNode = pDB->psCurrParentNode->pNext;
        else if(Op == DCF_NODE_VISIT_REWIND)
            psParentNode = pDB->psCurrParentNode->pPrev;

        while(psParentNode)
        {
            psSubNode = psParentNode->pCamNodeHead;
            while(psSubNode)
            {
                if(psSubNode->byCamID == CamID && !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN))
                {

                    AHC_DCFDT_GetFullPathBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, Info->FilePath, sizeof(Info->FilePath));
                    AHC_DCFDT_GetFileNameBySubNode(pDB, psParentNode->FileNameInfo, psSubNode, Info->FileName);
                    Info->bReadOnly  = (psSubNode->byFileAttr & DCFDT_FILEATTR_READONLY) ? AHC_TRUE : AHC_FALSE;
                    Info->FileType   = psSubNode->byFileType;
                    Info->uiFileSize = psSubNode->nSizeInCluster * pDB->ulClusterSize;
                    AHC_DT_SecondsToDateTime(psParentNode->FileNameInfo.nDateTime, &RTCtime);
                    Info->uwYear     = RTCtime.uwYear;
                    Info->uwMonth    = RTCtime.uwMonth;
                    Info->uwDay      = RTCtime.uwDay;
                    Info->uwHour     = RTCtime.uwHour;
                    Info->uwMinute   = RTCtime.uwMinute;
                    Info->uwSecond   = RTCtime.uwSecond;
                    Info->bIsFileDownload = (psSubNode->byFileAttr & DCFDT_FILEATTR_ISDOWNLOAD) ? AHC_TRUE : AHC_FALSE;

                    pDB->psCurrParentNode = psParentNode;
                    bFound = AHC_TRUE;
                    goto SearchEnd;
                }
                psSubNode = psSubNode->pNext;
            }

            if(Op == DCF_NODE_VISIT_FORWARD)
                psParentNode = psParentNode->pNext;
            else if(Op == DCF_NODE_VISIT_REWIND)
                psParentNode = psParentNode->pPrev;
        }
        //if not found
        {
            AHC_DBG_MSG(1, "No more file node\r\n");
        }
    }
    else
    {
        AHC_DBG_MSG(1, "Wrong Operation Para\r\n");
    }

    SearchEnd:
    AHC_DCFDT_Unlock(pDB);
    if(!bFound){
        AHC_DBG_MSG(1, "%s Node not found!!\r\n", __FUNCTION__);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}
//only use for format free file(share folder)
AHC_BOOL AHC_DCFDT_GetFormatFreeFileSize(char *pchFileName, UINT32 *ulFileSize)
{
    MMP_ERR         err = MMP_ERR_NONE;
    MMP_ULONG       ulFileId;
    MMP_ULONG       ulWriteCnt = 0;
    char            szFullPath[MAX_FULL_FILENAME_SIZE];
    char*           pos;
    PSDATETIMEDCFDB pDB = &sDcfDtSet.m_sDB[DCF_DB_FORMAT_FREE_DB];

    MEMSET(szFullPath, 0x00, MAX_FULL_FILENAME_SIZE);
    STRCPY(szFullPath,pDB->szFolderPath[sDcfDtSet.m_byCurrCamID]);
    STRCAT(szFullPath,"\\");
    pos = strstr(pchFileName, szFullPath);
    if (pos != NULL) {//input parameter is a full path, skip root
        pchFileName += STRLEN(szFullPath);
    }
    STRCAT(szFullPath,(INT8*)pchFileName);

    err = MMPS_FS_FileOpen(szFullPath, strlen(szFullPath), "a+b", strlen("a+b"),  &ulFileId );
    err |= MMPS_FS_FileSeek(ulFileId, SHARE_FILESIZE_OFFSET, MMPS_FS_SEEK_SET);
    err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)ulFileSize, sizeof(*ulFileSize), &ulWriteCnt);

    err |= MMPS_FS_FileClose(ulFileId);


    if (MMP_ERR_NONE != err)
    {
        AHC_DBG_MSG(1, FG_RED("Get %s size error\r\n"), szFullPath);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_DCFDT_CheckFileIsOpened(INT8 *pchFilePath)
{
    MMP_ULONG       FileHandleNum = 0;
    char            szOpenFullPath[MAX_FULL_FILENAME_SIZE];
    extern FS_FILE  FS__aFilehandle[FS_NUM_FILE_HANDLES];

    for(FileHandleNum = 0; FileHandleNum < FS_NUM_FILE_HANDLES; FileHandleNum++){
        if( FS__aFilehandle[FileHandleNum].InUse ){
            STRCPY(szOpenFullPath, (char*)FS__aFilehandle[FileHandleNum].FileNameMark);
            if( 0 == STRCMP(szOpenFullPath, pchFilePath ) )
            {
                AHC_DBG_MSG(1, "%s file is opening\r\n", pchFilePath);
                return AHC_TRUE;
            }
        }
    }
    return AHC_FALSE;
}
//
static AHC_BOOL AHC_DCFDT_GetIndexbyParentNodeAndCamID(PSDATETIMEDCFDB pDB, PSDATETIMEFILE  psParentNode, DCF_CAM_ID CamID, UINT32 *uiIndex)
{
    PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
    INT32          nFileCount = -1;
    while(psParentNodeCur)
    {
        if(pDB->bFormatFreeEnable)
        {
            PSSUBNODE psSubNodeCur;
            psSubNodeCur = AIHC_DCFDT_GetSubNodeByParentNode(pDB, psParentNodeCur, CamID);
            if((psSubNodeCur == NULL) || (psSubNodeCur->byFileAttr & DCFDT_FILEATTR_HIDDEN))
            {
                psParentNodeCur = psParentNodeCur->pNext;
                continue;
            }
        }

        if(psParentNodeCur->byCamExist & (DCF_CAM_EXIST_BASE << CamID)){
            nFileCount++;
        }

        if(psParentNodeCur->FileNameInfo.uiFileIndex == psParentNode->FileNameInfo.uiFileIndex &&
           psParentNodeCur->FileNameInfo.nDateTime   == psParentNode->FileNameInfo.nDateTime)
        {
            *uiIndex = nFileCount;
            return AHC_TRUE;
        }
        psParentNodeCur = psParentNodeCur->pNext;
    }
    return AHC_FALSE;
}
//
AHC_BOOL AHC_DCFDT_TransferIndexbyCamID(UINT32 SrcIndex, DCF_CAM_ID CamID, UINT32 *DstIndex)
{
    PSDATETIMEDCFDB pDB;
    PSDATETIMEFILE  psParentNode;

    pDB = &sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx];

    psParentNode = AIHC_DCFDT_GetParentNodeByIndex(pDB,SrcIndex);

    if(psParentNode == NULL){
        AHC_PRINT_RET_ERROR(0,0);
        return AHC_FALSE;
    }

    if(!AHC_DCFDT_GetIndexbyParentNodeAndCamID(pDB, psParentNode, CamID, DstIndex)){
        AHC_PRINT_RET_ERROR(0,0);
        return AHC_FALSE;
    }

    return AHC_TRUE;
}
AHC_BOOL AHC_DCFDT_FileIndexCtrl(PSDATETIMEDCFDB pDB, UINT32 *uiIndex, DCFDT_FILE_INDEX_CTL Operation)
{
    //rule
    switch(Operation)
    {
    //each time delete file should update
    case DCFDT_INDEX_CTL_UPDATE_DELINDEX:
        if(!bFileIndexLock)
        {
            if(pDB->FileIndexStruct.uiNextDelIndex == *uiIndex)
            {
                PSDATETIMEFILE psParentNodeCur = pDB->pFileHead;
                while(psParentNodeCur)
                {
                    if(psParentNodeCur->FileNameInfo.uiFileIndex == pDB->FileIndexStruct.uiNextDelIndex)
                    {
                        if(psParentNodeCur->pNext != NULL){
                            pDB->FileIndexStruct.uiNextDelIndex = psParentNodeCur->pNext->FileNameInfo.uiFileIndex;
                            break;
                        }
                        else{
                            if(pDB->FileIndexStruct.uiNextDelIndex > pDB->FileIndexStruct.uiNextAddIndex){
                                pDB->FileIndexStruct.uiNextDelIndex = pDB->pFileHead->FileNameInfo.uiFileIndex;
                                break;
                            }
                            else{
                                //TBD
                                pDB->FileIndexStruct.uiNextDelIndex = DCFDT_FILEINDEX_START;
                                break;
                            }
                        }
                    }
                    psParentNodeCur = psParentNodeCur->pNext;
                }

                AHC_DCFDT_UpdateFileIndexToSavedFile();
            }
        }
    break;
    //add file each time
    case DCFDT_INDEX_CTL_UPDATE_ADDINDEX:
        if(!bFileIndexLock)
        {
            if(pDB->FileIndexStruct.uiNextAddIndex <= *uiIndex)
            {
                if(*uiIndex < DCFDT_FILEINDEX_MAXNUM){
                    pDB->FileIndexStruct.uiNextAddIndex = *uiIndex + 1;
                }
                else if(*uiIndex == DCFDT_FILEINDEX_MAXNUM){
                    pDB->FileIndexStruct.uiNextAddIndex = DCFDT_FILEINDEX_START;
                }
                else if(*uiIndex > DCFDT_FILEINDEX_MAXNUM){
                    AHC_DBG_MSG(1, "illegal index! %d\r\n", *uiIndex);
                    pDB->FileIndexStruct.uiNextAddIndex = DCFDT_FILEINDEX_START;
                }

                AHC_DCFDT_UpdateFileIndexToSavedFile();
            }
        }
    break;
    case DCFDT_INDEX_CTL_SET_DELINDEX:
        if(!bFileIndexLock)
        {
            pDB->FileIndexStruct.uiNextDelIndex = *uiIndex;
            AHC_DCFDT_UpdateFileIndexToSavedFile();
        }
    break;
    case DCFDT_INDEX_CTL_SET_ADDINDEX:
        if(!bFileIndexLock)
        {
            pDB->FileIndexStruct.uiNextAddIndex = *uiIndex;
            AHC_DCFDT_UpdateFileIndexToSavedFile();
        }
    break;
    case DCFDT_INDEX_CTL_GET_DELINDEX:
        *uiIndex = pDB->FileIndexStruct.uiNextDelIndex;
    break;
    case DCFDT_INDEX_CTL_GET_ADDINDEX:
        //adjust next add index
        #if(DCFDT_INDEXMODE_DUPLICATE_PROCESSTYPE == DCFDT_INDEXMODE_DUPLICATE_SKIP)
        AHC_DCFDT_AdjustNextAddIndex(pDB);
        #endif
        *uiIndex = pDB->FileIndexStruct.uiNextAddIndex;
    break;
    case DCFDT_INDEX_CTL_RESET_ALL_INDEX:
        pDB->FileIndexStruct.uiNextDelIndex = DCFDT_FILEINDEX_START;
        pDB->FileIndexStruct.uiNextAddIndex = DCFDT_FILEINDEX_START;
    break;
    default:
    break;
    }
    return AHC_TRUE;
}
AHC_BOOL AHC_DCFDT_UpdateFileIndexToSavedFile(void)
{
    UINT32             uiFileID;
    AHC_ERR            err;
    AHC_FS_ATTRIBUTE   attrib;
    char fileName[DCF_MAX_FILE_NAME_SIZE] = {0};
    SFILE_INDEX_STRUCT FileIndexStruct[DCF_DB_COUNT] = {0};
    UINT32             i;
    MMP_UBYTE          TmpWriteEn;
    #if(FS_FORMAT_FREE_ENABLE)
    //set format free para
    MMPS_FORMATFREE_GetWriteEnable(&TmpWriteEn);
    MMPS_FORMATFREE_EnableWrite(1);
    #endif
    //
    for( i = 0; i < DCF_DB_COUNT; i++)
    {
        FileIndexStruct[i] = sDcfDtSet.m_sDB[i].FileIndexStruct;
        if(FileIndexStruct[i].uiNextDelIndex > DCFDT_FILEINDEX_MAXNUM || FileIndexStruct[i].uiNextDelIndex < DCFDT_FILEINDEX_START
        || FileIndexStruct[i].uiNextAddIndex > DCFDT_FILEINDEX_MAXNUM || FileIndexStruct[i].uiNextAddIndex < DCFDT_FILEINDEX_START)
        {
            AHC_DBG_MSG(1, "%s FileIndex out of range\r\n", __FUNCTION__);
        }
    }
    MEMCPY(fileName, DCFDT_FILEINDEX_INDEXSAVED_FIlENAME, sizeof(DCFDT_FILEINDEX_INDEXSAVED_FIlENAME));
    err = AHC_FS_FileOpen((INT8 *)fileName, AHC_StrLen(fileName), "a+b", AHC_StrLen("a+b"), &uiFileID);

    if (err != MMP_ERR_NONE){
        AHC_DBG_MSG(1, "ERR:file open fails...\r\n");
        return AHC_FALSE;
    }
    else{
        //AHC_DBG_MSG(1, "File open : %s\r\n", fileName);
    }
    //set hidden
    AHC_FS_FileDirGetAttribute(fileName, STRLEN(fileName), &attrib );
    attrib |= AHC_FS_ATTR_HIDDEN;
    AHC_FS_FileDirSetAttribute(fileName, STRLEN(fileName), attrib );
    if(err == AHC_ERR_NONE)
    {
        UINT32   uiWriteCount;

        //seek
        AHC_FS_FileSeek(uiFileID, 0, AHC_FS_SEEK_SET);
        //write
        AHC_FS_FileWrite(uiFileID, (UINT8*)FileIndexStruct, sizeof(FileIndexStruct), &uiWriteCount);
        //close
        AHC_FS_FileClose(uiFileID);
    }
    #if(FS_FORMAT_FREE_ENABLE)
    //set format free para
    MMPS_FORMATFREE_EnableWrite(TmpWriteEn);
    #endif
    return AHC_TRUE;
}
AHC_BOOL AHC_DCFDT_ReadFileIndexFromSavedFile(void)
{
    UINT32             uiFileID;
    AHC_ERR            err;
    char fileName[DCF_MAX_FILE_NAME_SIZE] = {0};
    SFILE_INDEX_STRUCT FileIndexStruct[DCF_DB_COUNT] = {0};
    UINT32             i;

    MEMCPY(fileName, DCFDT_FILEINDEX_INDEXSAVED_FIlENAME, sizeof(DCFDT_FILEINDEX_INDEXSAVED_FIlENAME));
    //open and write file
    err = AHC_FS_FileOpen((INT8 *)fileName, AHC_StrLen(fileName), "a+b", AHC_StrLen("a+b"), &uiFileID);

    if (err != MMP_ERR_NONE){
        AHC_DBG_MSG(1, "ERR:file open fails...\r\n");
        return AHC_FALSE;
    }
    else{
        //AHC_DBG_MSG(1, "File open : %s\r\n", fileName);
    }

    if(err == AHC_ERR_NONE)
    {
        UINT32 ulReadCount;
        //seek
        AHC_FS_FileSeek(uiFileID, 0, AHC_FS_SEEK_SET);
        AHC_FS_FileRead(uiFileID, (UINT8*)FileIndexStruct, sizeof(SFILE_INDEX_STRUCT) * DCF_DB_COUNT, &ulReadCount);
        AHC_FS_FileClose(uiFileID);
    }
    //
    for( i = 0; i < DCF_DB_COUNT; i++)
    {
        if(FileIndexStruct[i].uiNextDelIndex > DCFDT_FILEINDEX_MAXNUM || FileIndexStruct[i].uiNextDelIndex < DCFDT_FILEINDEX_START
        || FileIndexStruct[i].uiNextAddIndex > DCFDT_FILEINDEX_MAXNUM || FileIndexStruct[i].uiNextAddIndex < DCFDT_FILEINDEX_START)
        {
            AHC_DBG_MSG(1, "%s FileIndex out of range\r\n", __FUNCTION__);
            FileIndexStruct[i].uiNextDelIndex = DCFDT_FILEINDEX_START;
            FileIndexStruct[i].uiNextAddIndex = DCFDT_FILEINDEX_START;
        }
        sDcfDtSet.m_sDB[i].FileIndexStruct = FileIndexStruct[i];
    }

    return AHC_TRUE;
}
//calculate Offset of FileIndex, and recal Index to cheat node operation
UINT32 AHC_DCFDT_RecalculateIndexByOffset(SFILE_INDEX_STRUCT FileIndexStruct,UINT32 uiFileIndex)
{
    //take add index as starting point.08/10 chuni.li
    UINT32 uiOffset = 1 + DCFDT_FILEINDEX_MAXNUM - FileIndexStruct.uiNextAddIndex;;
    if(FileIndexStruct.uiNextDelIndex > FileIndexStruct.uiNextAddIndex)
    {
        if(uiFileIndex >= FileIndexStruct.uiNextDelIndex){
            uiFileIndex -= FileIndexStruct.uiNextAddIndex;
        }
        else if(uiFileIndex < FileIndexStruct.uiNextDelIndex && uiFileIndex > FileIndexStruct.uiNextAddIndex){
            uiFileIndex -= FileIndexStruct.uiNextAddIndex;
        }
        else{
            uiFileIndex += uiOffset;
        }
        return uiFileIndex;
    }
    else
    {
        //if file index/del index has been modified, index < del index should be += offset
        //if index < delindex, put it to original pos, and cyclic delete can delete it.08/10 chuni.li
        //if(uiFileIndex < FileIndexStruct.uiNextDelIndex){
        //    uiFileIndex += uiOffset;
        //}
        return uiFileIndex;
    }
}
AHC_BOOL AHC_DCFDT_UpdateNextIndexInFile(void)
{
    PSDATETIMEFILE  psParentNode;
    PSSUBNODE       psSubNode;
    AHC_BOOL        bTmpLock;
    UINT32          i;
    PSDATETIMEDCFDB pDB;
    AHC_BOOL        bIsDelIndexFound = AHC_FALSE;
    AHC_BOOL        bIsAddIndexFound = AHC_FALSE;

    for(i = 0; i < DCF_DB_COUNT ; i++)
    {
        pDB = &sDcfDtSet.m_sDB[i];

        AHC_DCFDT_Lock(pDB);
        psParentNode = pDB->pFileHead;
        while(psParentNode)
        {
            if(psParentNode->byCamExist & (DCF_CAM_EXIST_BASE << DCFDT_FILEINDEX_MASTERCAMID))
            {
                AHC_BOOL bSubNodeFound = AHC_FALSE;

                psSubNode = psParentNode->pCamNodeHead;
                while(psSubNode)
                {
                    if((psSubNode->byCamID == DCFDT_FILEINDEX_MASTERCAMID) &&
                       !(psSubNode->byFileAttr & DCFDT_FILEATTR_HIDDEN))
                    {
                        bSubNodeFound = AHC_TRUE;
                        break;
                    }
                    psSubNode = psSubNode->pNext;
                }
                if(bSubNodeFound)
                {
                    if(psParentNode->FileNameInfo.uiFileIndex >= pDB->FileIndexStruct.uiNextDelIndex &&
                       bIsDelIndexFound == AHC_FALSE)
                    {
                        bTmpLock       = bFileIndexLock;
                        bFileIndexLock = AHC_FALSE;
                        AHC_DCFDT_FileIndexCtrl(pDB, &(psParentNode->FileNameInfo.uiFileIndex), DCFDT_INDEX_CTL_SET_DELINDEX);
                        bFileIndexLock = bTmpLock;
                        bIsDelIndexFound = AHC_TRUE;
                    }
                    //assign the node addr of index in file to last add node
                    if(bIsAddIndexFound == AHC_FALSE && bFileIndexLock == AHC_TRUE)
                    {
                        if(psParentNode->FileNameInfo.uiFileIndex >= pDB->FileIndexStruct.uiNextAddIndex)
                        {
                            bIsAddIndexFound = AHC_TRUE;
                        }
                        else
                        {
                            pDB->psLastAddParentNode = psParentNode;
                        }
                    }
                }
            }

            if(bIsDelIndexFound && bIsAddIndexFound){break;}
            psParentNode = psParentNode->pNext;
        }

        if(!bIsAddIndexFound)
        {
            pDB->psLastAddParentNode = NULL;
        }
        AHC_DCFDT_Unlock(pDB);
    }
    return AHC_TRUE;
}
//skip exist file which has the same name in DB and find the empty slot for new next add index
AHC_BOOL AHC_DCFDT_AdjustNextAddIndex(PSDATETIMEDCFDB pDB)
{
    PSDATETIMEFILE  psParentNode = NULL;
    UINT32 ulDcfMemStart;
    UINT32 ulLAParentNodeAddr;
    if(pDB->psLastAddParentNode != NULL)
    {
        psParentNode = pDB->psLastAddParentNode->pNext;
        ulLAParentNodeAddr = (UINT32)pDB->psLastAddParentNode;
    }
    //mem addr check
    AIHC_GetTempDCFMemStartAddr(&ulDcfMemStart);
    if(ulLAParentNodeAddr > (ulDcfMemStart + MAX_DCF_MEM - 1) || (ulLAParentNodeAddr < ulDcfMemStart))
    {
        AHC_DBG_ERR(0, "LastAddParentNodeAddr 0x%x out of DCF mem location\r\n", ulLAParentNodeAddr);
        return AHC_FALSE;
    }

    while(psParentNode)
    {
        if(psParentNode->FileNameInfo.uiFileIndex == pDB->FileIndexStruct.uiNextAddIndex)
        {
            psParentNode = psParentNode->pNext;
            AHC_DBG_MSG(1, "Skip Index %d\r\n", pDB->FileIndexStruct.uiNextAddIndex);
            //try ++
            pDB->FileIndexStruct.uiNextAddIndex++;

        }
        else
        {
            break;
        }
    }

    return AHC_TRUE;
}

UINT32 AHC_DCFDT_GetCurrentDBFlag(void)
{
    return sDcfDtSet.m_sDB[sDcfDtSet.m_uiCurrDBIdx].uiFlag;
}
UINT32 AHC_DCFDT_GetInitDBFlag(DCF_DB_TYPE sType)
{
    if( sType >= DCF_DB_COUNT )
    {
        return 0;
    }
    return sDBInit_Config.sDBAttrConfig[sType].byFlag;
}

//visit all parent node and remove asymmetric file nodes, and rename filenammes to illgal filenames
AHC_BOOL AHC_DCFDT_FormatFree_RemoveAsymmetricFiles(PSDATETIMEDCFDB pDB)
{
    //start from filetail would be more efficiency
    PSDATETIMEFILE  psParentNodeCur = pDB->pFileTail;
    PSDATETIMEFILE  psTmpParentNodeCurPrev;
    PSSUBNODE       psSubNodeCur;
    UINT32          i;
    char            szSrcFilepath[DCF_MAX_FILE_NAME_SIZE];
    char            szDstFilepath[DCF_MAX_FILE_NAME_SIZE];
    SNODE_OP_PAK    NodeOpPak;
    UINT32          error;
    UINT8           ubSubNodeNum;

    AHC_DCFDT_Lock(pDB);
    while(psParentNodeCur)
    {
        //if NoneHiddenFileExist, do no rename this file
        AHC_BOOL bIsNoneHiddenExist = AHC_FALSE;
        //backup parent node next
        psTmpParentNodeCurPrev = psParentNodeCur->pPrev;

        ubSubNodeNum = 1;
        psSubNodeCur = psParentNodeCur->pCamNodeHead->pNext;
        while(psSubNodeCur)
        {
            if(psSubNodeCur->byFileAttr & DCFDT_FILEATTR_HIDDEN){
                ubSubNodeNum++;
            }
            else{
                bIsNoneHiddenExist = AHC_TRUE;
            }
            psSubNodeCur = psSubNodeCur->pNext;
        }
        if(ubSubNodeNum != DCFDT_CAM_NUM && bIsNoneHiddenExist == AHC_FALSE)
        {
            psSubNodeCur = psParentNodeCur->pCamNodeHead;
            while(psSubNodeCur)
            {
                //rename files
                AHC_DCFDT_GetFullPathByParentNode(pDB, psSubNodeCur->byCamID, psParentNodeCur, szSrcFilepath, DCF_MAX_FILE_NAME_SIZE);
                MEMCPY(szDstFilepath, szSrcFilepath, DCF_MAX_FILE_NAME_SIZE);
                MEMCPY(szDstFilepath + STRLEN(pDB->szFolderPath[psSubNodeCur->byCamID]) + 1, DCFDT_Illegal_FREECHAR, STRLEN(DCFDT_Illegal_FREECHAR));
                error = AHC_FS_FileDirRename(szSrcFilepath, STRLEN(szSrcFilepath), szDstFilepath, STRLEN(szDstFilepath));
                if(MMP_ERR_NONE != error)
                {
                    AHC_DBG_MSG(1, "Rename file failed %s %s\r\n", szSrcFilepath, szDstFilepath);
                    AHC_DCFDT_Unlock(pDB);
                    return AHC_FALSE;
                }
                psSubNodeCur = psSubNodeCur->pNext;
            }
            //delete parent node in DB
            //force node operation to remove parent node
            pDB->bFormatFreeEnable = AHC_FALSE;
            {
                NodeOpPak.byCamID      = NULL;
                NodeOpPak.FileNameInfo = psParentNodeCur->FileNameInfo;
                NodeOpPak.psParentNode = psParentNodeCur;
                NodeOpPak.psSubNode    = NULL;
                NodeOpPak.byOperation  = DCFDT_NODE_DELETE_PARENT;
            }
            pDB->pCusAPI->pfCusNodeOperation((void*)pDB, NodeOpPak);
            //resume
            pDB->bFormatFreeEnable = AHC_TRUE;
            //
        }
        psParentNodeCur = psTmpParentNodeCurPrev;
    }
    AHC_DCFDT_Unlock(pDB);

    return AHC_TRUE;
}
#endif
