//==============================================================================
/**
 @file AHC_UF.c
 @brief Universal File
 @author Rogers Chen
 @version 1.0
*/

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"
#include "ahc_parameter.h"
#include "ahc_datetime.h"
#include "mmpf_fs_api.h"
#include "ait_utility.h"
#include "ahc_fs.h"
#include "ahc_uf.h"
#include "ahc_macro.h"
#include "ahc_mempoolfixedsize.h"
#include "MenuSetting.h"
#include "ahc_utility.h"

AHC_UF_CUSINDEXMAPFUNC m_CusMappingFunc = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; 

#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
extern SMIMFBROWSEDB m_MIMFBrowseDB;
extern AHC_BOOL AHC_MIMF_MemPoolFSUninit(void);
extern AHC_BOOL AHC_MIMF_MemPoolFSInit(UINT32 uiMaxMemSize);
extern AHC_BOOL AHC_MIMF_NodeOperation(UINT8 byDB, SFILENAME_INFO FileNameInfo, UINT8 byOperation);
#endif

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
static INT8 chSD0RootName[5] = "SD:\\";
#if(defined(DEVICE_GPIO_2NDSD_PLUG))
static INT8 chSD1RootName[6] = "SD1:\\";
#endif
#endif

//registerfunc
AHC_BOOL AHC_UF_MappingFuncRegisterCallBack(UINT32 uiEvent, void *pCallback)
{
    AHC_BOOL ret = AHC_TRUE;

    switch(uiEvent){
    case AHC_UFCB_GETTOTALFILECOUNT:
        m_CusMappingFunc.GetTotalFileCount = (CusGetTotalFileCountCallback)pCallback;
        break;
    case AHC_UFCB_SETCURRENTINDEX:
        m_CusMappingFunc.SetCurrentIndex = (CusSetCurrentIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETCURRENTINDEX:
        m_CusMappingFunc.GetCurrentIndex = (CusGetCurrentIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETFILEPATHNAMEBYINDEX:
        m_CusMappingFunc.GetFilePathNamebyIndex = (CusGetFilePathNamebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETFILESIZEBYINDEX:
        m_CusMappingFunc.GetFileSizebyIndex = (CusGetFileSizebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETFILETYPEBYINDEX:
        m_CusMappingFunc.GetFileTypebyIndex = (CusGetFileTypebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_ISREADONLYBYINDEX:
        m_CusMappingFunc.IsReadOnlybyIndex = (CusIsReadOnlybyIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETFILETIMEBYINDEX:
        m_CusMappingFunc.GetFileTimebyIndex = (CusGetFileTimebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_ISCHARLOCKBYINDEX:
        m_CusMappingFunc.IsCharLockbyIndex = (CusIsCharLockbyIndexCallback)pCallback;
        break;
    case AHC_UFCB_GETFILENAMEBYINDEX:
        m_CusMappingFunc.GetFileNamebyIndex = (CusGetFileNamebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_MOVEFILEBYINDEX:
        m_CusMappingFunc.MovefilebyIndex = (CusMoveFilebyIndexCallback)pCallback;
        break;
    case AHC_UFCB_CHECKFILECAMSTATUS:
        m_CusMappingFunc.CheckFileCamStatus = (CusCheckFileCamStatusCallback)pCallback;
        break;
    default:
        printc("not support event!!\r\n");
        ret = AHC_FALSE;
        break;    
    }

    return ret;
}

void AHC_UF_SetRearCamPathFlag(AHC_BOOL bSetRearCam)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    AHC_DCFDT_SetRearCamPathFlag(bSetRearCam);
#endif
}
void AHC_UF_GetRearCamPathFlag(AHC_BOOL* bGetRearCam)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)

#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    AHC_DCFDT_GetRearCamPathFlag(bGetRearCam);
#endif
}
AHC_BOOL AHC_UF_GetTotalFileCount(UINT32 *puiImgIndex)
{
    if (m_CusMappingFunc.GetTotalFileCount)
    {
        return m_CusMappingFunc.GetTotalFileCount(puiImgIndex);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetTotalFileCount(puiImgIndex);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)   
    return AHC_DCFDT_GetTotalFileCountByCurrCamID(puiImgIndex);
#endif
}

AHC_BOOL AHC_UF_GetTotalFileCountByDB(DCF_DB_TYPE sDB, UINT32 *puiImgIndex)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_TRUE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)   
    return AHC_DCFDT_GetTotalFileCountByDB(sDB, puiImgIndex);
#endif
}

AHC_BOOL AHC_UF_SetCurrentIndex(UINT32 uiImgIndex)
{
    if(m_CusMappingFunc.SetCurrentIndex)
    {
        return m_CusMappingFunc.SetCurrentIndex(uiImgIndex);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_SetCurrentIndex(uiImgIndex);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_SetCurrentIndex(uiImgIndex);
#endif
}

AHC_BOOL AHC_UF_GetCurrentIndex(UINT32 *puiImgIndex)
{
    AHC_BOOL bResult;

    if(m_CusMappingFunc.GetCurrentIndex)
    {
        return m_CusMappingFunc.GetCurrentIndex(puiImgIndex);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    bResult = AHC_DCF_GetCurrentIndex(puiImgIndex);
    return bResult;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    bResult = AHC_DCFDT_GetCurrentIndex(puiImgIndex);
    return bResult;
#endif
}

AHC_BOOL AHC_UF_GetIndexbyName(INT8 *pchDirName,
                                INT8 *pchFileName,
                                UINT32 *puiIndex)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    AHC_BOOL bResult;

    bResult =  AHC_DCF_GetIndexbyName(pchDirName,
                                  pchFileName,
                                  puiIndex);
    return bResult;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_TRUE;
#endif
}

AHC_BOOL AHC_UF_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName) 
{
    if(m_CusMappingFunc.GetFilePathNamebyIndex)
    {
        return m_CusMappingFunc.GetFilePathNamebyIndex(uiIndex, FilePathName);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
    STRCPY(FilePathName, (char*)DcfInfo.FileName);

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFilePathNamebyIndex(uiIndex, FilePathName);
#endif
}

AHC_BOOL AHC_UF_GetFileNamebyIndex(UINT32 uiIndex, char* FileName) 
{
    if(m_CusMappingFunc.GetFileNamebyIndex)
    {
        return m_CusMappingFunc.GetFileNamebyIndex(uiIndex, FileName);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{
    INT8        byFilePathName[DCF_MAX_FILE_NAME_SIZE];
    INT8        DirName[DCF_MAX_FILE_NAME_SIZE];
    UINT32      uiFileNameLength;
    AHC_BOOL    ahc_ret;
    
    ahc_ret = AHC_UF_GetFilePathNamebyIndex(uiIndex, byFilePathName);
    if(ahc_ret == AHC_FALSE){
        return AHC_FALSE;
    }
    memset(DirName,0,sizeof(DirName));
    GetPathDirStr(DirName,sizeof(DirName),byFilePathName);
    uiFileNameLength = AHC_StrLen(byFilePathName) - AHC_StrLen(DirName) - 1;
    memcpy(FileName,byFilePathName + AHC_StrLen(DirName) + 1,uiFileNameLength);    
    return AHC_TRUE;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileNamebyIndex(uiIndex, FileName);
#endif

    return AHC_FALSE;
}

AHC_BOOL AHC_UF_GetFileSizebyIndex(UINT32 uiIndex, UINT32* FileSize) 
{
    if(m_CusMappingFunc.GetFileSizebyIndex)
    {
        return m_CusMappingFunc.GetFileSizebyIndex(uiIndex, FileSize);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
    *FileSize = DcfInfo.uiFileSize;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileSizebyIndex(uiIndex, FileSize);
#endif
}

AHC_BOOL AHC_UF_GetFileSizebyFullName(char* FullFileName, UINT32* FileSize)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_FALSE;//Not implemented yet
#else
    AHC_BOOL bFound = AHC_FALSE;
#if DCF_DB_COUNT >= 5
    DCF_DB_TYPE type = DCF_DB_FORMAT_FREE_DB;
#else
    //DCF_DB_TYPE type = DCF_DB_TYPE_MAX_NUMBER;
#endif

    if (FileSize == NULL)
        return AHC_FALSE;

#if DCF_DB_COUNT >= 5
    bFound = AHC_DCFDT_IsFullNameDbType(FullFileName, DCF_DB_FORMAT_FREE_DB);
    //bFound = AHC_DCFDT_GetDbTypeByFullName(FullFileName, &type);
    //if (bFound == AHC_TRUE && type == DCF_DB_FORMAT_FREE_DB)
    if (bFound)
    {//Found the file name in current DB
        *FileSize = AHC_DCFDT_GetDualEncFileSizeT(type, FullFileName);
    }
#else
    if (0) {}
#endif
    else {//Not found, use FS directly
        MMP_UBYTE               sFileAttribute;
        MMP_ULONG               ulpTimeStamp;
        if (MMPF_FS_GetFileInfo((char*)FullFileName,
                &sFileAttribute,
                (MMP_U_LONG*)&ulpTimeStamp,
                (MMP_U_LONG*)FileSize) == MMP_ERR_NONE) {
            bFound = AHC_TRUE;
        }
    }

    return bFound;
#endif
}

AHC_BOOL AHC_UF_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *FileType) 
{
    if(m_CusMappingFunc.GetFileTypebyIndex)
    {
        return m_CusMappingFunc.GetFileTypebyIndex(uiIndex, FileType);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
    *FileType = DcfInfo.FileType;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileTypebyIndex(uiIndex, FileType);
#endif
}

AHC_BOOL AHC_UF_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime) 
{
    if(m_CusMappingFunc.GetFileTimebyIndex)
    {
        return m_CusMappingFunc.GetFileTimebyIndex(uiIndex, pRtcTime);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
    pRtcTime->uwYear    = DcfInfo.uwYear;
    pRtcTime->uwMonth   = DcfInfo.uwMonth;
    pRtcTime->uwDay     = DcfInfo.uwDay;

    pRtcTime->uwHour    = DcfInfo.uwHour;
    pRtcTime->uwMinute  = DcfInfo.uwMinute;
    pRtcTime->uwSecond  = DcfInfo.uwSecond;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileTimebyIndex(uiIndex, pRtcTime);
#endif
}

AHC_BOOL AHC_UF_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly) 
{
    if(m_CusMappingFunc.IsReadOnlybyIndex)
    {
        return m_CusMappingFunc.IsReadOnlybyIndex(uiIndex, bReadOnly);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO DcfInfo = {0};

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
    *bReadOnly = DcfInfo.bReadOnly;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_IsReadOnlybyIndex(uiIndex,bReadOnly);
#endif
}

AHC_BOOL AHC_UF_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock) 
{
    AHC_BOOL ret;
    if(m_CusMappingFunc.IsCharLockbyIndex)
    {
        return m_CusMappingFunc.IsCharLockbyIndex(uiIndex, bCharLock);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);

    *bCharLock = DcfInfo.bCharLock;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    ret = AHC_DCFDT_IsCharLockbyIndex(uiIndex, bCharLock);
    return ret;
#endif
}

AHC_BOOL AHC_UF_GetDirKeybyIndex(UINT32 uiIndex, UINT16 *DirKey) 
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    DCF_INFO  DcfInfo;

    ret = AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);

    *DirKey = DcfInfo.uwDirKey;

    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_SetFreeChar(UINT8 byDir, UINT8 byOp, UINT8 byChars[]) 
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_SetFreeChar(byDir, byOp, byChars);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_SetFreeChar(byDir, byOp, byChars);
#endif
}

AHC_BOOL AHC_UF_GetAllowedChar(INT8* pbyChar, UINT32 uiLength)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetAllowedChar(pbyChar, uiLength);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetAllowedChar(pbyChar, uiLength); 
#endif
}

AHC_BOOL AHC_UF_EnableDB(DCF_DB_TYPE sType, AHC_BOOL bEnable)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_EnableDB(sType, bEnable);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_EnableDB(sType, bEnable); 
#endif
}

AHC_BOOL AHC_UF_GetDBStatus(DCF_DB_TYPE sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetDBStatus(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetDBStatus(sType); 
#endif
}

AHC_BOOL AHC_UF_SelectDB(DCF_DB_TYPE sType)
{  
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_SelectDB(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_SelectDB(sType); 
#endif
}

DCF_DB_TYPE AHC_UF_GetDB(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetDB();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetDB();
#endif
}

AHC_BOOL AHC_UF_UpdateLastFiles(DCF_DB_TYPE sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_TRUE; //TODO
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("%s,%d  not support this func!!!\r\n",__FUNCTION__, __LINE__);
    return AHC_TRUE; 
#endif
}

AHC_BOOL AHC_UF_WriteInfo(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_WriteInfo();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_TRUE;
#endif
}

//Unused
AHC_BOOL AHC_UF_SetCyclicDeletedMask(DCF_FILE_PROTECT sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_SetCyclicDeletedMask(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

//Unused
AHC_BOOL AHC_UF_GetCyclicDeletedMask(DCF_FILE_PROTECT* sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetCyclicDeletedMask(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_SetFileDeletedMask(DCF_FILE_PROTECT sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_SetFileDeletedMask(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_GetFileDeletedMask(DCF_FILE_PROTECT* sType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetFileDeletedMask(sType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_DeleteCyclicFilebySize(UINT64 uiSize)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_DeleteCyclicFilebySize(uiSize);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_DeleteCyclicFilebySize(uiSize);
#endif
}

AHC_BOOL AHC_UF_DeleteFilebyNum(UINT64 uiNum)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AIHC_DCFDT_DbDeleteCyclicFilebyNum(AIHC_DCFDT_GetDbByType(AHC_UF_GetDB()), uiNum);
#endif
}

AHC_BOOL AHC_UF_FileOperation(UINT8 *pPathName, 
                           UINT8 *pFileName, 
                           UINT8 byOperation, 
                           UINT8 *pDestPath, 
                           UINT8 *pDestFileName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_FileOperation(pPathName,
                           pFileName, 
                           byOperation, 
                           pDestPath, 
                           pDestFileName); 
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_FileOperation((char *)pPathName, 
                           (char *)pFileName, 
                           byOperation, 
                           (char *)pDestPath, 
                           (char *)pDestFileName); 

#endif
}                           

AHC_BOOL AHC_UF_MoveFile(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT16 uwDirKey, INT8 *pchFileName, AHC_BOOL bReadOnly)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_MoveFile(sFromType, sToType, uwDirKey, pchFileName, bReadOnly);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_MoveFileByFileName_AllCam(sFromType, sToType, uwDirKey, pchFileName, bReadOnly); 
#endif
}        

AHC_BOOL AHC_UF_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly)
{
    if(m_CusMappingFunc.MovefilebyIndex)
    {
        return m_CusMappingFunc.MovefilebyIndex(sFromType, sToType, uiIndex, bReadOnly);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_MoveFileByIndex(sFromType, sToType, uiIndex, bReadOnly); 
#endif
}  

AHC_BOOL AHC_UF_Rename(DCF_DB_TYPE sFromType, AHC_RTC_TIME* psRtcTimeOld, AHC_RTC_TIME* psRtcTimeNew)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_RenameFile(sFromType, psRtcTimeOld, psRtcTimeNew); 
#endif
}        

UINT32 AHC_UF_GetCyclicCluster(DCF_DB_TYPE sDB)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetCyclicCluster(sDB);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetCyclicCluster(sDB); 
#endif
}

UINT32 AHC_UF_GetFileCluster(DCF_DB_TYPE sDB)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetFileCluster(sDB);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileCluster(sDB); 
#endif
}

UINT32 AHC_UF_GetClusterTH(DCF_DB_TYPE sDB)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetClusterTH(sDB);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetClusterTH(sDB); 
#endif
}        

AHC_BOOL AHC_UF_AdjustAllocation(DCF_STORAGE_ALLOC eType)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_AdjustAllocation(eType);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_AdjustAllocation(eType); 
#endif
}    
//-------------------------------------------------

AHC_BOOL AHC_UF_MountDB(UINT32 uiMaxMem)
{
    //move srand seed to mountDB 
    {//for FS short name
        UINT64 FreeBytes;
        UINT32 TickCount;
        UINT32 seed;
        AHC_FS_GetStorageFreeSpace(AHC_GetMediaPath(), &FreeBytes);
        AHC_OS_GetTime(&TickCount);
        seed = (UINT16)(((FreeBytes>>32)+(FreeBytes%0xFFFFFFFF)+TickCount)%0xFFFFFFFF);
        srand(seed); 
    }
    #if (DEBUG_UART_TO_FILE)
    //enable log in sd by default.
    #if (FS_FORMAT_FREE_ENABLE)
    MMPS_FORMATFREE_EnableWrite(1); 
    MMPF_Debug_Enable(MMP_FALSE, MMP_TRUE, MMP_FALSE);
    #else
    MMPF_Debug_Enable(MMP_TRUE, MMP_TRUE, MMP_FALSE);
    #endif
    MMPF_Debug_CreateFile();
    #endif    
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DcfMountDB(uiMaxMem);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    #if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    //UF Mem is same as DCF buffer
    AHC_MIMF_MemPoolFSInit(uiMaxMem);
    AHC_UF_RegisterCallback(AHC_UFCB_NODE_OPERATION, (void*)AHC_MIMF_NodeOperation);
    #endif
    //module init
    AHC_DCFDT_ModuleInit();
    //mountDB
    return AHC_DCFDT_MountDCF(uiMaxMem); 
#endif
}

AHC_BOOL AHC_UF_UnmountDB(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DcfUnMountDB();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    #if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
    MEMSET(&m_MIMFBrowseDB, 0, sizeof(SMIMFBROWSEDB));
    AHC_MIMF_MemPoolFSUninit();
    #endif
    return AIHC_DCFDT_UnmountAllDB();
#endif
}

UINT32 AHC_UF_GetClusterSize(DCF_DB_TYPE sDB)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_GetClusterSize();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
{
    PSDATETIMEDCFDB pDB;
    pDB = (PSDATETIMEDCFDB)AIHC_DCFDT_GetDbByType(sDB);
    return pDB->ulClusterSize;
}
#endif
} 

void AHC_UF_DumpDB(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    AIHC_DCF_DumpDB();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    AIHC_DCFDT_DumpDB(); 
#endif
} 

AHC_BOOL AHC_UF_PreAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_PreAddFile(uwDirKey, pchFileName);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AIHC_DCFDT_PreAddFile(uwDirKey, pchFileName); 
#endif
}

AHC_BOOL AHC_UF_PostAddFile(UINT16 uwDirKey, INT8 *pchFileName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_PostAddFile(uwDirKey, pchFileName);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AIHC_DCFDT_PostAddFile(uwDirKey, pchFileName); 
#endif
}

AHC_BOOL AHC_UF_GetName(UINT16 *pDirKey, INT8 *DirName, INT8 *FileName, UINT8 *bCreateNewDir)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_GetName(pDirKey, DirName, FileName, bCreateNewDir);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE; 
#endif
}

AHC_BOOL AHC_UF_GetName2(AHC_RTC_TIME* psRtcTime, INT8 *FileFullPath, INT8 *FileName, UINT8 byCamStatus)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetName(psRtcTime, FileFullPath, FileName, byCamStatus);
#endif
}

INT8* AHC_UF_GetRootName(void) 
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return (INT8*)AIHC_DCF_GetRootName();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))
    {
        if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
            return chSD0RootName;
        else if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD1)
            return chSD1RootName;
    }
    #else//DEVICE_GPIO_2NDSD_PLUG
    {
        return chSD0RootName;
    }
    #endif//DEVICE_GPIO_2NDSD_PLUG
#endif//DEVICE_GPIO_2NDSD_PLUG
}

INT8* AHC_UF_GetRootDirName(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return (INT8*)AIHC_DCF_GetRootName(); 
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return (INT8*)AHC_DCFDT_GetRootDirName();
#endif
}

AHC_BOOL AHC_UF_AddDir(INT8 *pchDirName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_AddDir(pchDirName);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_TRUE;
#endif
}

AHC_BOOL AHC_UF_IsDBMounted(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_IsDBMounted();
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_IsDBMounted();
#endif
}

AHC_BOOL AHC_UF_SetParam(AHC_PARAM_ID wParamID,UINT32 Param)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_SetParam(wParamID, Param);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_GetParam(AHC_PARAM_ID wParamID,UINT32 *Param)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AIHC_DCF_GetParam(wParamID, Param);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_UF_RegisterCallback(MMP_ULONG ulCBType, void *pCallback)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return AHC_DCF_RegisterCallback(ulCBType, pCallback);
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_RegisterCallback(ulCBType, pCallback);
#endif
}

AHC_ERR AHC_UF_CopyFile(INT8* pchSource, INT8* pchDest)
{
    #define COPY_FILE_BUF_SIZE  4096

    UINT32      ulFileId = 0;
    UINT32      ulFileId2 = 0;
    AHC_ERR     err = 0;
    UINT8       ubData[COPY_FILE_BUF_SIZE] = {0};
    UINT32      ulReadCount = 0;
    UINT32      ulWriteCount =0;
    UINT32      ulFileSize = 0;
    UINT32      ulTempFileSize = 0;
    INT8        uchDirName[DCF_MAX_FILE_NAME_SIZE+1] = {0};
    INT8        uchDirName2[DCF_MAX_FILE_NAME_SIZE+1] = {0};
    UINT32      i = 0;
    UINT32      uiFolderID = 0;
    UINT64      ulpFreeBytes = 0;

    printc("Copy File Source:%s\r\nCopy File Dest: %s\r\n", pchSource, pchDest);

    for(i = 0; i < DCF_MAX_FILE_NAME_SIZE; i++)
    {
        uchDirName[i] = pchDest[i];

        if(i > 0 && uchDirName[i] == '\\' && uchDirName[i-1] != ':')
        {
            MEMCPY(uchDirName2, uchDirName, STRLEN(uchDirName) - 1);

            printc("Check folder: %s\r\n", uchDirName2);
            if(AHC_FS_DirOpen(uchDirName2, STRLEN(uchDirName2), &uiFolderID) != MMP_ERR_NONE)
            {
                AHC_FS_DirCreate(uchDirName2, STRLEN(uchDirName2));       ///< Create a new directory.   //Rogers:Add
            }
            else
            {
                AHC_FS_DirClose(uiFolderID);
            }
        }

        if(uchDirName[i] == '\0')
        {
            break;
        }
    }

    err |= AHC_FS_FileOpen(pchSource, STRLEN(pchSource), "rb", STRLEN("rb"), &ulFileId);
    if(err) {printc("Open CopyErr: %x with %s\r\n", err, pchSource);}

    err |= AHC_FS_FileOpen(pchDest, STRLEN(pchDest), "wb", STRLEN("wb"), &ulFileId2);
    if(err) {printc("Open CopyErr: %x with %s\r\n", err, pchDest);}

    err |= AHC_FS_FileGetSize(ulFileId, &ulFileSize);
    if(err) {printc("FileSize CopyErr: %x\r\n", err);}

    ulTempFileSize = ulFileSize;
    printc("Copy ulFileSize = %d\r\n", ulFileSize);

    AHC_FS_GetStorageFreeSpace(AHC_MEDIA_MMC1, &ulpFreeBytes);

    if(ulpFreeBytes < ulFileSize)
    {
        printc("2nd SD Card Full\r\n");
        AHC_FS_FileRemove(pchDest, STRLEN(pchDest));
        AHC_FS_FileClose(ulFileId);
        AHC_FS_FileClose(ulFileId2);
        return  AHC_SD_NO_SPACE;
    }

    while(ulTempFileSize != 0 && ulTempFileSize > 0)
    {
        if(!AHC_IsSDInserted())
        {
            printc("1st SD Not Inserted\r\n");
            AHC_FS_FileClose(ulFileId);
            AHC_FS_FileClose(ulFileId2);
            return  AHC_SD_ERR_CARD_REMOVED;
        }

        if(!AHC_Is2ndSDInserted())
        {
            printc("2nd SD Not Inserted\r\n");
            AHC_FS_FileClose(ulFileId);
            AHC_FS_FileClose(ulFileId2);
            return  AHC_SD_ERR_CARD_REMOVED;
        }

        if(!AHC_SDMMC_IsSD1MountDCF())
        {
            printc("1st SD Mount Failed\r\n");
            AHC_FS_FileClose(ulFileId);
            AHC_FS_FileClose(ulFileId2);
            return  AHC_SD_ERR_CARD_REMOVED;
        }

        err |= AHC_FS_FileRead(ulFileId, ubData,  COPY_FILE_BUF_SIZE, &ulReadCount);
        if(err) {printc("Read CopyErr: %x\r\n", err); break;}

        err |= AHC_FS_FileWrite(ulFileId2, ubData, ulReadCount, &ulWriteCount);
        if(err) {printc("Write CopyErr: %x\r\n", err); break;}

        if(ulReadCount != ulWriteCount) {printc("WriteSize CopyErr: R[%d] W[%d]\r\n", ulReadCount, ulWriteCount);}


        ulTempFileSize -= ulReadCount;
        //printc("Total:%d, Remain:%d, Read:%d, Write:%d\r\n", ulFileSize, ulTempFileSize, ulReadCount, ulWriteCount);
    }

    AHC_FS_FileClose(ulFileId);
    AHC_FS_FileClose(ulFileId2);

    if(err)
        printc("Copy File End with Error:%x\r\n", err);
    else
        printc("Copy File End\r\n");

    return err;
}

AHC_ERR AHC_UF_CopyOneCardFiles(AHC_MEDIA_ID sMediaSrcID, AHC_MEDIA_ID sMediaDestID)
{
    AHC_ERR     err = AHC_ERR_NONE;

    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    {
        printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    }
    #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        #if(defined(DEVICE_GPIO_2NDSD_PLUG))
        {
            #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
            {
                #if(TWOSD_MASTER_SLAVE_MODE == TWOSD_MASTER_SLAVE_SLAVE_BACKUP_PLAYBACK_MENU_SEL)
                {
                    UINT32          uiMaxIdx = 0;
                    UINT32          uiCurIdx = 0;
                    UINT32          CurFileSize = 0;
                    INT8            chSrcFileName[DCF_MAX_FILE_NAME_SIZE+1] = {0};
                    INT8            chDestFileName[DCF_MAX_FILE_NAME_SIZE+1] = {0};
                    DCF_DB_TYPE     sCurDBType = 0;
                    DCF_DB_TYPE     sOldDBType = 0;
                    UINT64 TotalDbSize = 0;
                    UINT64 RestSize = 0;
                    RECT rc = {10, 100, 260, 50};
                    UINT32 TotalFile = 0, RestFile = 0;
                    UINT64 LastPos = 0;
                    UINT64 CurPos = 0;
                    UINT8 bID0, bID1;

                    if(!AHC_IsSDInserted())
                    {
                        printc("1st SD Not Inserted\r\n");
                        return  AHC_SD_ERR_CARD_REMOVED;
                    }

                    if(!AHC_Is2ndSDInserted())
                    {;
                        printc("2nd SD Not Inserted\r\n");
                        return  AHC_SD_ERR_CARD_REMOVED;
                    }

                    if(!AHC_SDMMC_IsSD1MountDCF())
                    {
                        printc("1st SD Mount Failed\r\n");
                        return  AHC_SD_ERR_CARD_REMOVED;
                    }

                    sOldDBType = AHC_UF_GetDB();

                    AHC_SendAHLMessageEnable(AHC_FALSE);

                    // Get total file size to be copied.
                    sOldDBType = AHC_UF_GetDB();
                    for(sCurDBType = 0; sCurDBType < DCF_DB_COUNT; sCurDBType++) {
                        AHC_UF_SelectDB(sCurDBType);
                        TotalDbSize += AHC_UF_GetClusterSize(sCurDBType);
                        AHC_UF_GetTotalFileCount(&uiMaxIdx);
                        TotalFile += uiMaxIdx;
                    }
                    AHC_UF_SelectDB(sOldDBType);
                    RestSize = TotalDbSize;
                    RestFile = TotalFile;

                    for(sCurDBType = 0; sCurDBType < DCF_DB_COUNT; sCurDBType++)
                    {
                        AHC_UF_SelectDB(sCurDBType);

                        AHC_UF_GetTotalFileCount(&uiMaxIdx);

                        for(uiCurIdx = 0; uiCurIdx < uiMaxIdx; uiCurIdx++)
                        {
                            MEMSET(chSrcFileName, 0, sizeof(chSrcFileName));
                            MEMSET(chDestFileName, 0, sizeof(chDestFileName));

                            AHC_UF_GetFilePathNamebyIndex(uiCurIdx, chSrcFileName);

                            MEMCPY(chDestFileName, chSrcFileName, 2);//Copy String "SD"
                            STRCAT(chDestFileName, "1");
                            MEMCPY(chDestFileName+3, chSrcFileName+2, strlen(chSrcFileName)-2);

                            printc("DB %d, Copy the %d/%d file: %s\r\n", sCurDBType, uiCurIdx, uiMaxIdx, chSrcFileName);
                            printc("DB %d, Copy to %s\r\n", sCurDBType, chDestFileName);

                            err = AHC_UF_CopyFile(chSrcFileName, chDestFileName);

                            if( err != AHC_ERR_NONE)
                            {
                                printc("Copy files stopping by err\r\n");

                                AHC_SendAHLMessageEnable(AHC_TRUE);
                                AHC_UF_SelectDB(sOldDBType);

                                return  AHC_SD_ERR_CARD_REMOVED;
                            }

                            RestFile--;

                            {
                                #include "ColorDefine.h"

                                AHC_UF_GetFileSizebyIndex(uiCurIdx, &CurFileSize);
                                RestSize -= CurFileSize;

                                OSDDraw_EnterMenuDrawing(&bID0, &bID1);

                                if (LastPos == 0) {
                                    LastPos = rc.uiLeft;
                                    CurPos = rc.uiLeft+rc.uiWidth - rc.uiWidth*((double)RestSize/(double)TotalDbSize);
                                    OSDDraw_ClearOvlDrawBuffer2(bID0, OSD_COLOR_DARKGRAY3);
                                    AHC_OSDSetColor(OSD_COLOR_WHITE);
                                    AHC_OSDDrawFillRect(bID0, rc.uiLeft, rc.uiTop, rc.uiLeft+rc.uiWidth, rc.uiTop+rc.uiHeight);
                                }
                                else {
                                    LastPos = CurPos;
                                    CurPos = rc.uiLeft+rc.uiWidth - rc.uiWidth*((double)RestSize/(double)TotalDbSize);;
                                }

                                AHC_OSDSetColor(OSD_COLOR_ORANGE);
                                AHC_OSDDrawFillRect(bID0, LastPos, rc.uiTop, CurPos, rc.uiTop+rc.uiHeight);

                                OSDDraw_ExitMenuDrawing(&bID0, &bID1);
                            }
                        }
                    }

                    AHC_SendAHLMessageEnable(AHC_TRUE);

                    AHC_UF_SelectDB(sOldDBType);
                }
                #else
                {

                }
                #endif//TWOSD_MASTER_SLAVE_MODE
            }
            #elif(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
            {
                #if(BOOTUP_MOUNT_CARD == BOOTUP_MOUNT_CARD_FIRST_CARD)
                {

                }
                #elif(BOOTUP_MOUNT_CARD == BOOTUP_MOUNT_CARD_BY_SIF_INFO)
                {

                }
                #endif//BOOTUP_MOUNT_CARD
            }
            #endif//TWOSD_WORK_MODEL
        }
        #else//DEVICE_GPIO_2NDSD_PLUG
        {

        }
        #endif//DEVICE_GPIO_2NDSD_PLUG
    }
    #endif//DCF_FILE_NAME_TYPE

    return err;
}

UINT64 AHC_UF_GetFileTH(DCF_DB_TYPE sType)
{
    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
        printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
        return AHC_ERR_NONE;
    #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        return AHC_DCFDT_GetFileTH(sType);
    #else
        return 0;
    #endif
}

/********************************************************************************

********************************************************************************/

#define COPY_FILE_BUF_SIZE2     (0x8000)
UINT8 m_ubData[COPY_FILE_BUF_SIZE2];

AHC_ERR AHC_UF_CopyFile2(UINT32 ulFileId, UINT32 ulFileId2, UINT32* SizeCopied)
{
    AHC_ERR     err = 0;
    UINT32      ulReadCount = 0;
    UINT32      ulWriteCount =0;

    if ((ulFileId == NULL) || (ulFileId2 == NULL)) {
        *SizeCopied = 0;
        return AHC_FS_ERR_FILE_HANDLE_INVALID;
    }

    if(!AHC_IsSDInserted()) {
        printc("1st SD Not Inserted\r\n");
        return  AHC_SD_ERR_CARD_REMOVED;
    }

    if(!AHC_Is2ndSDInserted()) {
        printc("2nd SD Not Inserted\r\n");
        return  AHC_SD_ERR_CARD_REMOVED;
    }

    if(!AHC_SDMMC_IsSD1MountDCF()) {
        printc("1st SD Mount Failed\r\n");
        return  AHC_SD_ERR_CARD_REMOVED;
    }

    err |= AHC_FS_FileRead(ulFileId, m_ubData,  COPY_FILE_BUF_SIZE2, &ulReadCount);
    if(err) printc("Read CopyErr: %x\r\n", err);

    err |= AHC_FS_FileWrite(ulFileId2, m_ubData, ulReadCount, &ulWriteCount);
    if(err) printc("Write CopyErr: %x\r\n", err);

    if(ulReadCount != ulWriteCount) {printc("WriteSize CopyErr: R[%d] W[%d]\r\n", ulReadCount, ulWriteCount);}

    *SizeCopied = ulReadCount;

    if (err != AHC_ERR_NONE) {

    }
    else if(ulReadCount < COPY_FILE_BUF_SIZE2) {
        err = AHC_FS_ERR_COPY_FINISH;
    }
    else {
        err = AHC_FS_ERR_COPY_NOT_FINISH;
    }

    return err;
}

void AHC_UF_CreateDCFDBFolder(void)
{
    //
    // Need to modify.
    //

    //UINT32 i;
    UINT32 uiFolderID;
    //UINT32 uiNameLength;
    //INT8* szFolder;
    //PSDATETIMEDCFDB pDB;
    
    /*
    for(i=0; i<DCF_DB_COUNT; i++) {

        pDB = AIHC_DCFDT_GetDbByType(i);
        szFolder = pDB->szFolderName;
        uiNameLength = STRLEN(szFolder);

        // Open directory
        if(AHC_FS_DirOpen(szFolder, uiNameLength, &uiFolderID) != MMP_ERR_NONE) {
            AHC_FS_DirCreate(szFolder, uiNameLength);
        }
    }*/

    if(AHC_FS_DirOpen((INT8*)"SD1:\\Video", sizeof("SD1:\\Video"), &uiFolderID) != MMP_ERR_NONE) {
            AHC_FS_DirCreate((INT8*)"SD1:\\Video", sizeof("SD1:\\Video"));
    }
    else {
        AHC_FS_DirClose(uiFolderID);
    }

    if(AHC_FS_DirOpen((INT8*)"SD1:\\Event", sizeof("SD1:\\Event"), &uiFolderID) != MMP_ERR_NONE) {
        AHC_FS_DirCreate((INT8*)"SD1:\\Event", sizeof("SD1:\\Event"));
    }
    else {
        AHC_FS_DirClose(uiFolderID);
    }

    if(AHC_FS_DirOpen((INT8*)"SD1:\\Parking", sizeof("SD1:\\Parking"), &uiFolderID) != MMP_ERR_NONE) {
            AHC_FS_DirCreate((INT8*)"SD1:\\Parking", sizeof("SD1:\\Parking"));
    }
    else {
        AHC_FS_DirClose(uiFolderID);
    }

    if(AHC_FS_DirOpen((INT8*)"SD1:\\Photo", sizeof("SD1:\\Photo"), &uiFolderID) != MMP_ERR_NONE) {
            AHC_FS_DirCreate((INT8*)"SD1:\\Photo", sizeof("SD1:\\Photo"));
    }
    else {
        AHC_FS_DirClose(uiFolderID);
    }
}

/**
 @brief 
 AHC_UF_FileOperation_ByIdx
*/

AHC_BOOL AHC_UF_FileOperation_ByIdx(UINT32 ulCurIdx, 
                                     UINT8 Op, 
                                     UINT8 *pDestPath, 
                                     UINT8 *pDestFileName)
{
    AHC_BOOL        ahc_ret = AHC_TRUE;
    UINT32          uiFileNameLength;
    INT8            DirName[DCF_MAX_FILE_NAME_SIZE];
    INT8            FileName[DCF_MAX_FILE_NAME_SIZE];
    INT8            FilePathName[DCF_MAX_FILE_NAME_SIZE];
    
    ahc_ret = AHC_UF_GetFilePathNamebyIndex(ulCurIdx,FilePathName);
    
    if(ahc_ret == AHC_FALSE){
        return AHC_FALSE;
    }
    memset(DirName,0,sizeof(DirName));
    memset(FileName,0,sizeof(FileName));
    GetPathDirStr(DirName,sizeof(DirName),FilePathName);
    uiFileNameLength = AHC_StrLen(FilePathName) - AHC_StrLen(DirName) - 1;
    memcpy(FileName,FilePathName + AHC_StrLen(DirName) + 1,uiFileNameLength);
    
    return AHC_UF_FileOperation((UINT8 *)DirName,(UINT8 *)FileName, Op, pDestPath, pDestFileName);
}

void AHC_UF_InitLockFileTable(void)
{
    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
        AHC_DCF_InitLockFileTable();
    #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    #endif
}

void AHC_UF_UpdateLockFileTable(UINT32 uiIndex,AHC_BOOL *bDeleteFile)
{
    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    {
        DCF_INFO  DcfInfo;
        AHC_DCF_GetInfoFromCache(uiIndex, &DcfInfo);
        AHC_DCF_UpdateLockFileTable(DcfInfo.uwDirKey,
                                    DcfInfo.uwFileKey,
                                    DcfInfo.FileType,
                                    bDeleteFile);
    }
    #elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        //printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    #endif
}

AHC_BOOL AHC_UF_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status)
{
    if(m_CusMappingFunc.CheckFileCamStatus)
    {
        return m_CusMappingFunc.CheckFileCamStatus(uiIndex, status);
    }
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_CheckFileCamStatus(uiIndex, status);
#endif 
}

AHC_BOOL AHC_UF_SearchAvailableFileSlot(UINT8 byCamID, char* szFilePathName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_SearchAvailableFileSlot(byCamID, szFilePathName);
#endif    
}

AHC_BOOL AHC_UF_GetInfobyIndex(UINT32 uiIndex, DCF_INFO *Info) 
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
{   
    AHC_BOOL ret;
    ret = AHC_DCF_GetInfoFromCache(uiIndex, Info);
    return ret;
}
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
{
    AHC_RTC_TIME    RTCtime;
    if( AHC_UF_GetFilePathNamebyIndex(uiIndex, Info->FileName) == AHC_FALSE)
    {
        return AHC_FALSE;
    }
    AHC_DCFDT_IsReadOnlybyIndex(uiIndex, &Info->bReadOnly);
    AHC_UF_GetFileSizebyIndex(uiIndex, &Info->uiFileSize);
    AHC_UF_GetFileTypebyIndex(uiIndex, &Info->FileType);
    AHC_UF_GetFileTimebyIndex(uiIndex, &RTCtime);
    Info->uwYear   = RTCtime.uwYear;
    Info->uwMonth  = RTCtime.uwMonth;
    Info->uwDay    = RTCtime.uwDay;
    Info->uwHour   = RTCtime.uwHour;
    Info->uwMinute = RTCtime.uwMinute;
    Info->uwSecond = RTCtime.uwSecond;
    return AHC_TRUE;
}
#endif
}

AHC_BOOL AHC_UF_GetAllDBInfobyIndex(UINT32 uiIndex, DCF_INFO *Info)
{
    UINT32 uiCurDB;
    UINT32 i;
    UINT32 uiTotalCount = 0;
    uiCurDB = AHC_UF_GetDB();
    for( i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_COUNT; i++)
    {
        UINT32 uiTotalCountinDB;
        AHC_UF_SelectDB(i);
        AHC_UF_GetTotalFileCount( &uiTotalCountinDB );
        uiTotalCount += uiTotalCountinDB;
        if((uiIndex < uiTotalCount) && (uiTotalCountinDB != 0))
        {
            UINT32 uiIndexinDB = uiIndex - ( uiTotalCount - uiTotalCountinDB ) ;
            AHC_BOOL ret;
            ret = AHC_UF_GetInfobyIndex(uiIndexinDB, Info);
            AHC_UF_SelectDB(uiCurDB);
            return ret;
        }
    }
    printc("Index %d exceed TotalFileNumber %d\r\n", uiIndex, uiTotalCount);
    AHC_UF_SelectDB(uiCurDB);
    return AHC_FALSE;
}

AHC_BOOL AHC_UF_GetAllDBTotalFileCount(UINT32 *puiImgIndex)
{
    UINT32 uiCurDB;
    UINT32 i;
    uiCurDB = AHC_UF_GetDB();
    *puiImgIndex = 0;
    for( i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_COUNT; i++)
    {
        UINT32 uiTotalCountinDB;
        AHC_UF_SelectDB(i);
        AHC_UF_GetTotalFileCount( &uiTotalCountinDB );
        *puiImgIndex += uiTotalCountinDB;
    }
    AHC_UF_SelectDB(uiCurDB);
    if(*puiImgIndex > 0)
    {
        return AHC_TRUE;
    }
    else
    {
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_UF_SizeinFile_Update(INT8 *pchFileName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_SizeinFile_Update(pchFileName); 
#endif
}

UINT32 AHC_UF_GetDualEncFileSize(INT8 *pchFileName)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetDualEncFileSize(pchFileName); 
#endif
}

AHC_BOOL AHC_UF_GetFileInfoByVisitNode(DCF_DB_TYPE DBtype, DCF_CAM_ID CamID, DCF_INFO *Info, UINT8 Op)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    printc("[%s] Not Support Yet!\r\n", __FUNCTION__);
    return AHC_FALSE;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetFileInfoByVisitNode(DBtype, CamID, Info, Op);
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_UF_GetCurrentDBFlag
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_UF_GetCurrentDBFlag(void)
{
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    return 0;
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    return AHC_DCFDT_GetCurrentDBFlag();
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_UnloadSystemFile
//  Description : Write the system required file back to the SD card
//------------------------------------------------------------------------------
AHC_BOOL AHC_UnloadSystemFile(void)
{
    AHC_UF_WriteInfo();
    return AHC_TRUE;
}
