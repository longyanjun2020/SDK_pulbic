/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_fs.h"
#include "ahc_parameter.h"
#include "ahc_message.h"
#include "ahc_video.h"
#include "ahc_parameter.h"
#include "AHC_Config_SDK.h"
#include "ahc_version.h"
#include "ahc_media.h"
#include "ahc_utility.h"
#include "ahc_uf.h"
#include "ait_utility.h"
#include "aihc_protection_inc.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

static AHC_PROTECT_TYPE m_VRProtectType  = AHC_PROTECT_NONE;

/*===========================================================================
 * Main body
 *===========================================================================*/

/**
@brief  confirm the attribute of file is read only or not.

@param[in] wDcfObjIdx: the position of dcf object.

*/
AHC_BOOL AHC_Thumb_IsFileProtect(UINT32 wDcfObjIdx)
{
    AHC_BOOL bReadOnly = AHC_FALSE;

    AHC_UF_IsReadOnlybyIndex(wDcfObjIdx, &bReadOnly);

    if(bReadOnly == AHC_TRUE){
        return AHC_TRUE;

    }else{
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_Thumb_IsFileLocked(UINT32 wDcfObjIdx)
{
    AHC_BOOL bCharLock = AHC_FALSE;

    AHC_UF_IsCharLockbyIndex(wDcfObjIdx, &bCharLock);

    if(bCharLock == AHC_TRUE){
        return AHC_TRUE;

    }else{
        return AHC_FALSE;
    }
}

void AHC_Protect_SetType(AHC_PROTECT_TYPE Type)
{
    m_VRProtectType = Type;
}

AHC_PROTECT_TYPE AHC_Protect_GetType(void)
{
    return m_VRProtectType;
}

AHC_BOOL AHC_Protect_SpellFileName(char* FilePathName, INT8* pchDirName, INT8* pchFileName)
{
    UINT32  uiFileNameLength;
    INT8    tmpDirName[MAX_FULL_FILENAME_SIZE];
    GetPathDirStr(tmpDirName,sizeof(tmpDirName),FilePathName);
    memcpy(pchDirName,tmpDirName,AHC_StrLen(tmpDirName));
    uiFileNameLength = AHC_StrLen(FilePathName) - AHC_StrLen(pchDirName) - 1;
    memcpy(pchFileName,FilePathName + AHC_StrLen(pchDirName) + 1,uiFileNameLength);

    return AHC_TRUE;
}

AHC_BOOL AHC_Protect_SetVRFile(AHC_PROTECTION_OP Op, AHC_PROTECT_TYPE Type)
{
    #define MAX_NAME_LENGTH (32)

    UINT32              uiMaxObjNumber;
    char                FilePathName[MAX_FULL_FILENAME_SIZE];
    UINT16              DirKey;

    INT8                OldDirName[MAX_NAME_LENGTH];
    INT8                OldFileName[MAX_NAME_LENGTH];

    AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8*)SEARCH_MOVIE);

    AHC_UF_GetTotalFileCount(&uiMaxObjNumber);

    if (uiMaxObjNumber == 0) {
        return AHC_FALSE;
    }
    else if (uiMaxObjNumber == 1) {

        goto FINAL;
    }

    if ((Op & AHC_PROTECTION_PRE_FILE) != 0)
    {
        MEMSET(FilePathName, 0, sizeof(FilePathName));
        MEMCPY(FilePathName, AHC_VIDEO_GetPrevRecFullName(), MAX_FULL_FILENAME_SIZE);
        if(STRLEN(FilePathName) == 0)
        {
            AHC_DBG_ERR(1, "PreFileName == NULL,No continuous event!\r\n");
            goto FINAL;
        }
        AHC_DBG_MSG(1, "PreFileName: %s \n", FilePathName);

        MEMSET(OldDirName, 0, sizeof(OldDirName));
        MEMSET(OldFileName, 0, sizeof(OldFileName));

        AHC_Protect_SpellFileName(FilePathName, OldDirName, OldFileName);

        #if (PROTECT_FILE_TYPE == PROTECT_FILE_MOVE_SUBDB)///< #if (PROTECT_FILE_TYPE)

        if((Type & AHC_PROTECT_MENU) != 0){
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL, NULL);
        }

        if(((Type & AHC_PROTECT_G) != 0) || ((Type & AHC_PROTECT_MOVE) != 0)){

            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_MOVE_SUBDB, NULL, NULL);
        }

        #elif (PROTECT_FILE_TYPE == PROTECT_FILE_RENAME) ///< #if (PROTECT_FILE_TYPE)
        {
        INT8    NewFileName[MAX_NAME_LENGTH];

        MEMSET(NewFileName, 0, sizeof(NewFileName));

        STRCPY(NewFileName, OldFileName);

        if((Type & AHC_PROTECT_MENU) != 0){
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);
        }

        if((Type & AHC_PROTECT_G) != 0){
            MEMCPY(NewFileName, DCF_CHARLOCK_PATTERN, STRLEN(DCF_CHARLOCK_PATTERN));

            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_CHAR_LOCK_ALL_CAM, NULL, NULL);
        }
        //#if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT!=LOCK_FILE_STOP)
        //AHC_UF_UpdateLockFileTable(uiObjIndex,NULL); this act should be in ahc_dcf.h
        //#endif
        AHC_DBG_MSG(1, "NewFileName: %s \n", NewFileName);
        }

        #elif (PROTECT_FILE_TYPE == PROTECT_FILE_MOVE_DB) ///< #if (PROTECT_FILE_TYPE)
        if(!(AHC_UF_MoveFile(AHC_UF_GetDB(), DCF_DB_TYPE_DB2_EVENT, DirKey, OldFileName, AHC_FALSE)))
        {
            AHC_DBG_ERR(1, "MoveFile to DB %d failed\r\n",DCF_DB_TYPE_DB2_EVENT);
            AHC_DBG_ERR(1, "Replace it by ReadOnly Operation\r\n");
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);
        }

        #else///< #if (PROTECT_FILE_TYPE)

        AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);

        #endif///< #if (PROTECT_FILE_TYPE)
    }

FINAL:

    if((Op & AHC_PROTECTION_CUR_FILE) != 0)
    {
        MEMSET(FilePathName, 0, sizeof(FilePathName));
        MEMCPY(FilePathName , (UINT8*)AHC_VIDEO_GetCurPrmRecdFileName(AHC_TRUE), sizeof(FilePathName));
        if(STRLEN(FilePathName) == 0)
        {
            AHC_DBG_ERR(1, "Cur FilePathName == NULL, Lock Current File failed\r\n");
            return AHC_FALSE;
        }
        AHC_DBG_MSG(1, "CurFileName: %s \n", FilePathName);

        MEMSET(OldDirName, 0, sizeof(OldDirName));
        MEMSET(OldFileName, 0, sizeof(OldFileName));

        AHC_Protect_SpellFileName(FilePathName, OldDirName, OldFileName);

        #if (PROTECT_FILE_TYPE == PROTECT_FILE_MOVE_SUBDB)///< #if (PROTECT_FILE_TYPE)

        if((Type & AHC_PROTECT_MENU) != 0) {
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);
        }

        if(((Type & AHC_PROTECT_G) != 0) || ((Type & AHC_PROTECT_MOVE) != 0)) {
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_MOVE_SUBDB, NULL, NULL);
        }

        #elif (PROTECT_FILE_TYPE == PROTECT_FILE_RENAME)///< #if (PROTECT_FILE_TYPE)
        {
        INT8    NewFileName[MAX_NAME_LENGTH];

        MEMSET(NewFileName, 0, sizeof(NewFileName));

        STRCPY(NewFileName, OldFileName);

        if((Type & AHC_PROTECT_MENU) != 0) {
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);
        }

        if((Type & AHC_PROTECT_G) != 0) {

            MEMCPY(NewFileName, DCF_CHARLOCK_PATTERN, STRLEN(DCF_CHARLOCK_PATTERN));

            #if (USE_INFO_FILE)
            STRCPY(AHC_InfoLog()->DCFCurVideoFileName, NewFileName);
            #endif

            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_CHAR_LOCK_ALL_CAM, NULL, NULL);
        }
        //#if (LIMIT_MAX_LOCK_FILE_NUM && MAX_LOCK_FILE_ACT!=LOCK_FILE_STOP)
        //AHC_UF_UpdateLockFileTable(uiObjIndex,NULL); this act should be in ahc_dcf.h
        //#endif
        AHC_DBG_MSG(1, "NewFileName: %s \n", NewFileName);
        }

        #elif (PROTECT_FILE_TYPE == PROTECT_FILE_MOVE_DB) ///< #if (PROTECT_FILE_TYPE)
        if(!(AHC_UF_MoveFile(AHC_UF_GetDB(), DCF_DB_TYPE_DB2_EVENT, DirKey, OldFileName, AHC_FALSE)))
        {
            AHC_DBG_ERR(1, "MoveFile to DB %d failed\r\n",DCF_DB_TYPE_DB2_EVENT);
            AHC_DBG_ERR(1, "Replace it by ReadOnly Operation\r\n");
            AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);
        }

        #else///< #if (PROTECT_FILE_TYPE)

        AHC_UF_FileOperation((UINT8*)OldDirName,(UINT8*)OldFileName, DCF_FILE_READ_ONLY_ALL_CAM, NULL,NULL);

        #endif///< #if (PROTECT_FILE_TYPE)
    }
    return AHC_TRUE;
}
