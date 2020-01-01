//==============================================================================
//
//  File        : AHC_Media.c
//  Description : AHC media function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "AHC_Config_SDK.h"
#include "ahc_media.h"
//#include "ahc_general.h"
#include "ahc_warningmsg.h"
#include "ahc_uf.h"
#include "ahc_gsensor.h"
#include "aihc_dcf.h"
#include "ahc_fs.h"
//#include "mmp_lib.h"
#include "mmps_fs.h"
#include "mmpf_fs_api.h"
//#include "mmpf_sf.h"
#include "ait_utility.h"
#include "ahc_gpio.h"
#include "ahc_pmu.h"
#include "ahc_os.h"
#include "ahc_menu.h"
//#include "mmpf_storage_api.h"
#include "ahc_message.h"
#include "ahc_callback.h"

#include "fs_cfg.h" //for SD pad setting.
#include "GSensor_ctrl.h"
#include "gps_ctl.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define MEDIA_ROOT_NAME_LEN  	16
#define SMC_ROOT			 	"SM:\\"
#define MMC_ROOT			 	"SD:\\"
#define MMC1_ROOT			 	"SD1:\\"
/*===========================================================================
 * Global varible
 *===========================================================================*/

static AHC_MEDIA_ID m_CurMountedMedia                       = AHC_MEDIA_MAX_ID;
static INT8         m_strMediaRootName[MEDIA_ROOT_NAME_LEN] = "SD:\\";
static UINT32		m_StorageSizeInCluster = 0;
static AHC_BOOL     m_CheckMediaWrite = AHC_TRUE;
UINT8  SDCardUsed	= 0;
AHC_BOOL	        m_EnterNoFitStorageAllocateQuery = AHC_FALSE;

#if 1
#if (ENABLE_SD_HOT_PLUGGING)
#if(defined(DEVICE_GPIO_2NDSD_PLUG))
static SDMMC_STATE                  m_eSDMMCState           = SDMMC_1STOUT_2NDOUT;
#else
static SDMMC_STATE                  m_eSDMMCState           = SDMMC_OUT;
#endif
static AHC_SD_MOUNT_STATUS          m_bSDMMCMountState      = AHC_FALSE;
#endif

static UINT8                        m_ubSDMMC_Class         = 0xFF;
static UINT8                        m_ub2ndSDMMC_Class      = 0xFF;
#endif
//Use to check AHC_MountStorageMedia SD physical mount done, TBD by Chuni Li
//Use for SDUpdateCheckFileExisted in SD_Updater.c to wait SD mount done
AHC_BOOL bWaitSDMountDone = AHC_FALSE;

/*===========================================================================
 * Extern function
 *===========================================================================*/

#if (MENU_MEDIA_EN)
extern AHC_BOOL     QuickMediaOperation(UINT8 Op);
#endif
extern AHC_BOOL     gbAhcDbgBrk;
extern AHC_BOOL		gAHC_InitialDone;


/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void __LOCAL_API__(){}
#endif

/**
 @brief Get the media storage name

 This function get the media storage name

 @retval Media storage name
*/
INT8* AIHC_GetMediaRootName(void)
{
    return m_strMediaRootName;
}

/**
 @brief Set the DCF root dir name

 This function set the DCF root dir name

 @retval AHC_BOOL;
*/
static AHC_BOOL AIHC_SetMediaRootName(INT8 *pRootname)
{
    STRCPY(m_strMediaRootName, pRootname);
    return AHC_TRUE;
}

#if 0
void __AHC_MEDIA_API__(){}
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
/**
 @brief Get date and time of the captured image.

 This function is used to get the date and time the current image was captured in.
 Parameters:
 @param[out] *puwYear: Return the year information of date.
 @param[out] *puwMonth: Return the month information of date.
 @param[out] *puwDay: Return the day information of date.
 @param[out] *puwHour: Return the hour information of time.
 @param[out] *puwMin: Return the minute information of time.
 @param[out] *puwSec: Return the second information of time.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetImageDateTime(UINT16 *puwYear, UINT8 *puwMonth, UINT8 *puwDay, UINT8 *puwHour, UINT8 *puwMin, UINT8 *puwSec)
{
    UINT32      Index = 0 ;
    AHC_RTC_TIME RtcTime;

    if ( AHC_TRUE == AHC_UF_GetCurrentIndex(&Index) ) {
        AHC_UF_GetFileTimebyIndex(Index, &RtcTime);

        *puwYear    = RtcTime.uwYear;
        *puwMonth   = RtcTime.uwMonth;
        *puwDay     = RtcTime.uwDay;
        *puwHour    = RtcTime.uwHour;
        *puwMin     = RtcTime.uwMinute;
        *puwSec     = RtcTime.uwSecond;

        return AHC_TRUE;
    }
    else {
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_CheckStorageAllocate(UINT8 ubMode)
{
    UINT32      i;
    #if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)

    if(ubMode ==  STORATE_CHECK_FILE_NUM){
        UINT32		FileCount;
        for(i = DCF_DB_TYPE_DB1_PARKING; i < DCF_DB_COUNT; i++){
            AHC_UF_SelectDB(i);
            AHC_UF_GetTotalFileCount(&FileCount);

            if(FileCount > AHC_UF_GetFileTH(i))
            {
                AHC_DBG_MSG(1, "DB[%d] file count > max file count %d!!\r\n",i,AHC_UF_GetFileTH(i));
                return AHC_FALSE;
            }
        }
    }
    else
    #endif
    {
        #if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
        for(i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_COUNT; i++)
        #else
        for(i = DCF_DB_TYPE_DB0_NORMAL; i < DCF_DB_TYPE_MAX_NUMBER; i++)
        #endif
        {
            if(AHC_UF_GetFileCluster(i) > AHC_UF_GetClusterTH(i)) {
                return AHC_FALSE;
            }
        }
    }
    return AHC_TRUE;
}

/**
 @brief Format the specified storage media.

 This function is used to format the specified media.
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_FormatStorageMedia(UINT8 byMediaID)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        AHC_UF_UnmountDB();
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        AHC_UF_UnmountDB();
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_RESOURCE_FAT:
        #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
            bpVolume = "SM:1:\\";
        #elif(STORAGE_FOR_FACTORY_INFO == INFO_SD_CARD)
            bpVolume = "SD:1:\\";
        #endif
        ulVolNameSize = 6;
        break;
    case AHC_MEDIA_FACTORY_FAT:
        #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
            bpVolume = "SM:3:\\";
        #elif(STORAGE_FOR_FACTORY_INFO == INFO_SD_CARD)
            bpVolume = "SD:3:\\";
        #elif (STORAGE_FOR_FACTORY_INFO == INFO_SERIAL_FLASH)
            bpVolume = "SF:1:\\";
        #endif

        ulVolNameSize = 6;
        break;
    case AHC_MEDIA_USER_FAT:
        #if (STORAGE_FOR_FACTORY_INFO == INFO_NAND_FLASH)
            bpVolume = "SM:5:\\";
        #elif(STORAGE_FOR_FACTORY_INFO == INFO_SD_CARD)
            bpVolume = "SD:5:\\";
        #elif (STORAGE_FOR_FACTORY_INFO == INFO_SERIAL_FLASH)
            bpVolume = "SF:2:\\";
        #endif

        ulVolNameSize = 6;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    AHC_DBG_MSG(1, "Format %s\r\n", bpVolume);

    err = MMPS_FS_HighLevelFormat(bpVolume, ulVolNameSize);

    return ((err == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE);
}

#if (FS_FORMAT_FREE_ENABLE)
/**
 @brief Format the specified storage media as FORMAT FREE type.

 This function is used to format the specified media as FORMAT FREE type.
 (Note: Noew only SD card is supported.)
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_FormatStorageMedia_FormatFree( UINT8 byMediaID )
{
    MMP_ERR err = MMP_ERR_NONE;
    UINT32  ulTickCount = 0, ulTickCount2 = 0;

    AHC_UF_UnmountDB();

    AHC_FormatFreeConfigInfo();

    if( AHC_FormatFreeFileNameCB != NULL )
    {
        MMPS_FORMATFREE_RegisterCallback( MMPS_FileSystem_EVENT_FileName_Require, (void*)AHC_FormatFreeFileNameCB );
    }

    MMPF_OS_GetTime(&ulTickCount);

    err = MMPS_FORMATFREE_Format(byMediaID);

    MMPF_OS_GetTime(&ulTickCount2);
    AHC_DBG_MSG(1, "MMPS_FORMATFREE_Format = 0x%x (%d)\r\n", err, ((ulTickCount2 - ulTickCount)*1000)/ OS_TICKS_PER_SEC);

    return ((err == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE);
}

/**
 @brief Check specified storage media if expected FORMAT FREE type.

 This function is used to check specified storage media if expected FORMAT FREE type.
 (Note: Noew only SD card is supported.)
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_CheckMedia_FormatFree( UINT8 byMediaID )
{
    MMP_ERR err = MMP_ERR_NONE;

    if( AHC_MountStorageMediaWithoutDCF( byMediaID ) == AHC_FALSE )
    {
        return AHC_FALSE;
    }

    AHC_FormatFreeConfigInfo();

    if( AHC_FormatFreeFileNameCB != NULL )
    {
        MMPS_FORMATFREE_RegisterCallback( MMPS_FileSystem_EVENT_FileName_Require, (void*)AHC_FormatFreeFileNameCB );
    }

    err = MMPS_FORMATFREE_CheckMedia(byMediaID);

    if (err !=MMP_ERR_NONE){
        AHC_DisMountStorageMedia(byMediaID);
    }

    return ((err == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE);
}
#endif

/**
 @brief Check storage media if it's writable

 This function is used to check storage media if it's writable or not.
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_CheckStorageMediaAccess(UINT8 byMediaID, MMP_BYTE *bpVolume)
{
    AHC_BOOL    bResult = AHC_FALSE;
    AHC_ERR     err;
    MMP_BYTE    bpTestFileName[32]={0};
    MMP_ULONG   ulTestFileID = 0;

    if ((byMediaID == AHC_MEDIA_MMC) ||
        (byMediaID == AHC_MEDIA_MMC1)) {

        STRCPY(bpTestFileName, bpVolume);
        STRCAT(bpTestFileName, "CheckSDFile.txt");

        err = AHC_FS_FileOpen(bpTestFileName, STRLEN(bpTestFileName), "wb", 2, &ulTestFileID);

        if (err) {
            if (ulTestFileID) {
                AHC_FS_FileClose(ulTestFileID);
            }
            AHC_DBG_ERR(1, "TestFileName FileOpen fail, Skip SD card check\r\n");
        }
        else {
            err = AHC_FS_FileClose(ulTestFileID);

            if (err) {
                AHC_DBG_ERR(1, "TestFileName FileClose fail\r\n");
            }
            else {

                MMPD_FS_CacheClear();
                MMPD_FS_CacheInvalidate();

                err = AHC_FS_FileDirGetInfo(bpTestFileName, STRLEN(bpTestFileName), NULL, NULL, NULL);

                if (err) {
                    AHC_DBG_ERR(1, "TestFileName FileGetInfo fail\r\n");
                }
                else {
                    err = AHC_FS_FileRemove(bpTestFileName, STRLEN(bpTestFileName));

                    if (err) {
                        AHC_DBG_ERR(1, "TestFileName FileRemove fail\r\n");
                    }
                    else {
                        bResult = AHC_TRUE;
                    }
                }
            }
        }
    }
    else {
        bResult = AHC_TRUE;
    }

    return bResult;
}

/**
 @brief Mount the specific storage media without DCF.

 This function is used to mount the specific storage media.
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_MountStorageMediaWithoutDCF(UINT8 byMediaID)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;
    MMP_UBYTE   ubMountCount = 3;
    #if (ENABLE_SD_HOT_PLUGGING)

    #else
    MMP_ULONG64 free_bytes;
    #endif

    m_CheckMediaWrite = AHC_TRUE;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    /**
    @brief	mount the physical device at first.
    */

    ubMountCount = 3;

    do{

        if(AHC_MountPhysicalDevice(byMediaID) == AHC_TRUE){
            break;
        }else{
            AHC_UnmountPhysicalDevice(byMediaID);
        }

        ubMountCount--;

    }while(ubMountCount > 0);

    /**
    @brief	mount the FS device at second.
    */
    ubMountCount = 3;

    do{
        err = MMPS_FS_MountVolume(bpVolume, ulVolNameSize);
        if(err != MMP_ERR_NONE){
            MMPS_FS_UnmountVolume(bpVolume, ulVolNameSize);
        }
        ubMountCount--;
    }while(err != MMP_ERR_NONE && ubMountCount != 0);

    //For some bad SD cards, can read, but can't write and could not reply any error from driver layer.
    if( AHC_CheckStorageMediaAccess( byMediaID, bpVolume ) == AHC_FALSE )
    {
        AHC_DBG_MSG(1, FG_RED("AHC_CheckStorageMediaAccess Failed!!!\r\n"));
        m_CheckMediaWrite = AHC_FALSE;
        return AHC_FALSE;
    }

    #if (!ENABLE_SD_HOT_PLUGGING)

    if(err != MMP_ERR_NONE)
    {
        free_bytes = 0;
        return AHC_FALSE;
    }

    if (err == MMP_ERR_NONE) {
        //Get free space only if mounting is successful.
        MMPF_FS_GetVolumeFreeSpace(bpVolume, &free_bytes, MMP_TRUE);
    }
    #else//ENABLE_SD_HOT_PLUGGING
    if (err == MMP_ERR_NONE)
    {

        #if (MENU_MEDIA_EN)
        QuickMediaOperation(MEDIA_CMD_GET_ATTRIBUTE);
        #endif
        AHC_DBG_MSG(1, "Mount SD %d Without DCF OK.\r\n", byMediaID);
        return AHC_TRUE;
    }
    #endif//ENABLE_SD_HOT_PLUGGING
    else
    {
        return AHC_FALSE;
    }
}

/**
 @brief Mount the specific storage media.

 This function is used to mount the specific storage media.
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_MountStorageMedia(UINT8 byMediaID)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;
    MMP_UBYTE   ubMountCount = 3;
    MMP_ULONG64 free_bytes;
    #if (ENABLE_SD_HOT_PLUGGING)
    AHC_BOOL 	mount_status = AHC_FALSE;
    #endif

    m_CheckMediaWrite = AHC_TRUE;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_FACTORY_FAT:
        bpVolume = "SF:1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_USER_FAT:
        bpVolume = "SF:2:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    MEMSET(m_strMediaRootName,0, sizeof(m_strMediaRootName));
    STRCPY(m_strMediaRootName, bpVolume);

    /**
    @brief	mount the physical device at first.
    */

    ubMountCount = 3;

    do{

        if(AHC_MountPhysicalDevice(byMediaID) == AHC_TRUE){
            break;
        }else{
            AHC_UnmountPhysicalDevice(byMediaID);
        }

        ubMountCount--;

    }while(ubMountCount > 0);

    if(ubMountCount == 0)
    {
		AHC_DBG_MSG(1, FG_RED("AHC_MountPhysicalDevice %s Failed!\r\n"),bpVolume);
        m_CheckMediaWrite = AHC_FALSE;
        return AHC_FALSE;
    }
    /**
    @brief	mount the FS device at second.
    */
    ubMountCount = 3;

    do{
        err = MMPS_FS_MountVolume(bpVolume, ulVolNameSize);
        if(err != MMP_ERR_NONE){
            MMPS_FS_UnmountVolume(bpVolume, ulVolNameSize);
        }
        ubMountCount--;
    }while(err != MMP_ERR_NONE && ubMountCount != 0);
	if(err)
	{
		AHC_DBG_MSG(1, FG_RED("MMPS_FS_MountVolume Failed!\r\n"));
        m_CheckMediaWrite = AHC_FALSE;
        return AHC_FALSE;
	}

    //For some bad SD cards, can read, but can't write and could not reply any error from driver layer.
    if( AHC_CheckStorageMediaAccess( byMediaID, bpVolume ) == AHC_FALSE )
    {
        AHC_DBG_MSG(1, FG_RED("AHC_CheckStorageMediaAccess Failed!!!\r\n"));
        m_CheckMediaWrite = AHC_FALSE;
        return AHC_FALSE;
    }

    #if (!ENABLE_SD_HOT_PLUGGING)

    if(err != MMP_ERR_NONE)
    {
        free_bytes = 0;
    }

    if (err == MMP_ERR_NONE) {
        //Get free space only if mounting is successful.
        MMPF_FS_GetVolumeFreeSpace(bpVolume, &free_bytes, MMP_TRUE);
        m_CurMountedMedia = byMediaID;

        AHC_LoadSystemFile();

        AHC_EnableDir();

        if((AHC_MEDIA_MMC == byMediaID)|| (AHC_MEDIA_MMC1 == byMediaID)){

            //AHC_SDMMC_SetMountState(SDMMC_1STIN_2NDOUT);
            //only mount UF DB when byMediaID = AHC_MEDIA_MMC or AHC_MEDIA_MMC1
            err = AHC_UF_MountDB( MAX_DCF_MEM );
            AHC_DBG_MSG(1, "Clear SD space \r\n");
        }

        m_CheckMediaWrite = err;
        return err;
    }
    #else
    if (err == MMP_ERR_NONE) {

        m_CurMountedMedia = byMediaID;

        MMPF_FS_GetVolumeFreeSpace(bpVolume, &free_bytes, MMP_TRUE);
        #if (MENU_MEDIA_EN)
        QuickMediaOperation(MEDIA_CMD_GET_ATTRIBUTE);
        #endif

        AHC_EnableDir();

        bWaitSDMountDone = AHC_TRUE;
        if ((AHC_MEDIA_MMC == byMediaID)|| (AHC_MEDIA_MMC1 == byMediaID)) {
            //only mount UF DB when byMediaID = AHC_MEDIA_MMC or AHC_MEDIA_MMC1
            mount_status = AHC_UF_MountDB( MAX_DCF_MEM );

            if (AHC_TRUE == mount_status) {

                AHC_DBG_MSG(1, "Mount SD%d OK.\r\n", byMediaID);
                m_CheckMediaWrite = AHC_TRUE;
                return AHC_TRUE;
            }
            else {

                AHC_DisMountStorageMedia(byMediaID);
                m_CurMountedMedia = AHC_MEDIA_MAX_ID;
                AHC_DBG_MSG(1, "Mount SD%d FAIL.\r\n", byMediaID);
                m_CheckMediaWrite = AHC_FALSE;
                return AHC_FALSE;
            }
        }

        AHC_DBG_MSG(1, "Mount Media%d OK.\r\n", byMediaID);
        return AHC_TRUE;
    }
    #endif
    else {
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_GetMountStorageMediaStatus(void) {
    return m_CheckMediaWrite;
}

/**
 @brief Unmount the specific storage media.

 This function is used to ummount the specific storage media.
 Parameters:
 @param[in] byMediaID: The mounted storage media.
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_DisMountStorageMediaEx(UINT8 byMediaID, AHC_BOOL bUnmountPhysical )
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;

    #if 0 //Mark and Rogers Check!!
    if (byMediaID != m_CurMountedMedia) {
        return AHC_FALSE;
    }
    #endif

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_FACTORY_FAT:
        bpVolume = "SF:1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_USER_FAT:
        bpVolume = "SF:2:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    #if (ENABLE_SD_HOT_PLUGGING)
    if((AHC_MEDIA_MMC == byMediaID)|| (AHC_MEDIA_MMC1 == byMediaID))
    {
        //AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
    }
    #endif
    AHC_DBG_MSG(0, "byMediaID: %x, %x\r\n", byMediaID, m_CurMountedMedia);
    if (byMediaID == m_CurMountedMedia) {
        AHC_UnloadSystemFile();

        AHC_UF_UnmountDB();

        AHC_DBG_MSG(1, "Unmount SD%d DCF\r\n", byMediaID);
    }

    #if(defined(DEVICE_GPIO_2NDSD_PLUG))
    //NOP
    #else
    if( !bUnmountPhysical )
    {
        return AHC_TRUE;
    }
    #endif//DEVICE_GPIO_2NDSD_PLUG

    err = MMPS_FS_UnmountVolume(bpVolume, ulVolNameSize);

    if (err == MMP_ERR_NONE) {
        AHC_UnmountPhysicalDevice(byMediaID);

        if (m_CurMountedMedia == byMediaID)
            m_CurMountedMedia = AHC_MEDIA_MAX_ID; //reset

        AHC_DBG_MSG(1, "Unmount %s OK\r\n", bpVolume);

        if(AHC_SDMMC_GetMountState() == AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT && byMediaID == AHC_MEDIA_MMC1)
        {
            AHC_DisMountStorageMediaOnlyPhysical(AHC_MEDIA_MMC);
        }
        else if(AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT && byMediaID == AHC_MEDIA_MMC)
        {
            AHC_DisMountStorageMediaOnlyPhysical(AHC_MEDIA_MMC1);
        }

        AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);

#if(LIMIT_MAX_LOCK_FILE_NUM==1)
        {
            extern UINT32	m_ulLockFileNum;
            m_ulLockFileNum = 0;
            AHC_DBG_MSG(1, FG_YELLOW("%s:%d: reset m_ulLockFileNum to 0\r\n"), __FUNCTION__, __LINE__);
        }
#endif

        return AHC_TRUE;
    }
    else {
        AHC_DBG_MSG(1, "Unmount SD%d Failed\r\n", byMediaID);

        if(AHC_SDMMC_GetMountState() == AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT && byMediaID == AHC_MEDIA_MMC1)
        {
            AHC_DisMountStorageMediaOnlyPhysical(AHC_MEDIA_MMC);
        }
        else if(AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT && byMediaID == AHC_MEDIA_MMC)
        {
            AHC_DisMountStorageMediaOnlyPhysical(AHC_MEDIA_MMC1);
        }

        AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_DisMountStorageMediaOnlyPhysical(UINT8 byMediaID)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;

    #if 0 //Mark and Rogers Check!!
    if (byMediaID != m_CurMountedMedia) {
        return AHC_FALSE;
    }
    #endif

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    err = MMPS_FS_UnmountVolume(bpVolume, ulVolNameSize);

    if (err == MMP_ERR_NONE) {
        AHC_UnmountPhysicalDevice(byMediaID);

        if (m_CurMountedMedia == byMediaID)
            m_CurMountedMedia = AHC_MEDIA_MAX_ID; //reset

        AHC_DBG_MSG(1, "Unmount Physical SD%d OK\r\n", byMediaID);

        switch(byMediaID)
        {
            case AHC_MEDIA_MMC:
            {
                if(AHC_SDMMC_GetMountState() == AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT)
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT);
                }
            }
            break;
            case AHC_MEDIA_MMC1:
            {
                if(AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT)
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT);
                }
            }
            break;
        }

        return AHC_TRUE;
    }
    else {
        AHC_DBG_MSG(1, "Unmount Physical SD%d Failed\r\n", byMediaID);

        return AHC_FALSE;
    }
}

/**
 @brief Unmount the specific storage media.

 This function is used to ummount the specific storage media.
 Parameters:
 @param[in] byMediaID: The mounted storage media.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_DisMountStorageMedia(UINT8 byMediaID)
{
    return AHC_DisMountStorageMediaEx(byMediaID, AHC_TRUE);
}

/**
 @brief Get free space of the specific storage media.

 This function is used to get free space of the specific storage media.
 Parameters:
 @param[in] byMediaID: The specified storage media.
 @param[out] *pwSuccess: Return the result.
 @param[out] *pullFreeSize: Return the free space.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetStorageOtherMediaStatus(UINT8 byMediaID, UINT64 *pullFreeSize)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }
    err = MMPS_FS_IsVolumeMounted(bpVolume, ulVolNameSize);

    if (err == MMP_ERR_NONE) {
        err = MMPS_FS_GetFreeSpace(bpVolume, ulVolNameSize, pullFreeSize);
    }

    if (err == MMP_ERR_NONE) {
        return AHC_TRUE;
    }
    else {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

/**
 @brief Get geometry of the mounted storage media.

 This function is used to get BPB information of the mounted storage media.
 Parameters:
 @param[out] *pwSuccess: Return the result.
 @param[out] *pwBytesPerSec: Return number of bytes per sector.
 @param[out] *pwSecPerCluster: Return number of sectors per cluster.
 @param[out] *pwTotalCluster: Return total number of cluster.
 @param[out] *pwFreelCluster: Return the number of free cluster.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetStorageMediaGeometry(UINT16 *pwBytesPerSec, UINT16 *pwSecPerCluster, UINT32 *pwTotalCluster, UINT32 *pwFreelCluster)
{
    MMP_BYTE    		*bpVolume="";
    MMP_ULONG   		ulVolNameSize;
    MMPS_FS_DISK_INFO 	volinfo;

    *pwBytesPerSec 		= 0;
    *pwSecPerCluster 	= 0;
    *pwTotalCluster 	= 0;
    *pwFreelCluster 	= 0;

    switch(m_CurMountedMedia) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    if (MMPS_FS_GetVolumeInfo(bpVolume, ulVolNameSize, &volinfo) == MMP_ERR_NONE) {
        *pwBytesPerSec 		= volinfo.usBytesPerSector;
        *pwSecPerCluster 	= volinfo.usSecPerCluster;
        *pwTotalCluster 	= volinfo.ulTotalClusters;
        *pwFreelCluster 	= volinfo.ulFreeClusters;
    }
    else {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_GetStorageMediaInfo(AHC_FS_DISK_INFO* sMediaInfo)
{
    MMP_BYTE    		*bpVolume="";
    MMP_ULONG   		ulVolNameSize;

    switch(m_CurMountedMedia) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    if (AHC_FS_GetVolumeInfo(bpVolume, ulVolNameSize, sMediaInfo) != MMP_ERR_NONE) {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_SetMediaAttr(UINT8 byMediaID, AHC_MEDIA_ATTR bMediaAttr, UINT32 uiParam)
{
    MMP_BYTE    *bpVolume="";
    MMP_ULONG   ulVolNameSize;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    switch(bMediaAttr) {
    case AHC_MEDIA_ATTR_WP:
    case AHC_MEDIA_ATTR_VOL_ID:
    case AHC_MEDIA_ATTR_TYPE:
    case AHC_MEDIA_ATTR_STATUS:
    default:
        //Todo
        //Implementation
        break;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_GetMediaAttr(UINT8 byMediaID, AHC_MEDIA_ATTR bMediaAttr, UINT32 *puiParam)
{
    MMP_BYTE    *bpVolume;
    MMP_ULONG   ulVolNameSize;

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        ulVolNameSize = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        ulVolNameSize = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    switch(bMediaAttr) {
    case AHC_MEDIA_ATTR_WP:
    case AHC_MEDIA_ATTR_VOL_ID:
    case AHC_MEDIA_ATTR_TYPE:
    case AHC_MEDIA_ATTR_STATUS:
    default:
        //Todo
        //Implementation
        break;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_SetMediaPath(AHC_MEDIA_ID path)
{
    m_CurMountedMedia = path;
    return AHC_TRUE;
}

AHC_MEDIA_ID AHC_GetMediaPath(void)
{
    return m_CurMountedMedia;
}

void AHC_Media_GetFreeSpace(UINT64 *pFreeBytes)
{
    AHC_MEDIA_ID CurMedia;
    AHC_ERR      status;

    CurMedia = AHC_GetMediaPath();
    if(m_bSDMMCMountState == FALSE)
        status = FALSE;
    else
        status   = AHC_FS_GetStorageFreeSpace(CurMedia, pFreeBytes);

    if (AHC_ERR_NONE != status)
    {
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        *pFreeBytes = 0;
        AHC_DBG_MSG(1, "AHC_FS_GetStorageFreeSpace Error!!!!\r\n");
    }
}

AHC_BOOL AHC_GetVolumeName(INT8* pchVolume, UINT32* puiVolNameSize)
{
    switch(m_CurMountedMedia) {
    case AHC_MEDIA_MMC:
        //pchVolume = "SD:\\";
        *puiVolNameSize = 4;
        MEMCPY(pchVolume, "SD:\\", *puiVolNameSize);
        break;
    case AHC_MEDIA_MMC1:
        //pchVolume = "SD1:\\";
        *puiVolNameSize = 5;
        MEMCPY(pchVolume, "SD1:\\", *puiVolNameSize);
        break;
    case AHC_MEDIA_SMC:
        //pchVolume = "SM:\\";
        *puiVolNameSize = 4;
        MEMCPY(pchVolume, "SM:\\", *puiVolNameSize);
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_SwitchMediaPath(void) //SD->NAND, NAND->SD
{
    AHC_MEDIA_ID currentPath;
    AHC_BOOL	 status;

    currentPath = AHC_GetMediaPath();

    if(currentPath == AHC_MEDIA_MMC)
    {
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        AHC_SetMediaPath(AHC_MEDIA_SMC);
        AIHC_SetMediaRootName(SMC_ROOT);
        status = AHC_MountStorageMedia(AHC_MEDIA_SMC);
    }
    else
    {
        AHC_DisMountStorageMedia(AHC_MEDIA_SMC);
        AHC_SetMediaPath(AHC_MEDIA_MMC);
        AIHC_SetMediaRootName(MMC_ROOT);
        status = AHC_MountStorageMedia(AHC_MEDIA_MMC);

        if(!status)
        {
            AHC_SetMediaPath(AHC_MEDIA_SMC);
            AIHC_SetMediaRootName(SMC_ROOT);
            status = AHC_MountStorageMedia(AHC_MEDIA_SMC);
        }
    }
    return status;
}

AHC_BOOL AHC_CreateGsensorFolder(void)
{
#if (FS_FORMAT_FREE_ENABLE == 0) //Do NOT support GPS / Gsensor temp file in Format Free.
    #if (GPS_CONNECT_ENABLE && GPS_USE_FILE_AS_DATABUF && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))
    if (AHC_GPS_Module_Attached())
    {
        MMP_BYTE	bGpsInfoFileName[MAX_FULL_FILENAME_SIZE];
        MMP_ULONG	ulGpsInfoDirID;

        STRCPY(bGpsInfoFileName, (INT8*)AHC_UF_GetRootName());
        STRCAT(bGpsInfoFileName, GPS_TEMP_INFOFILE_DIR);

        if (AHC_FS_DirOpen(bGpsInfoFileName, sizeof(bGpsInfoFileName),&ulGpsInfoDirID) != AHC_ERR_NONE)
        {
            if(AHC_FS_DirCreate(bGpsInfoFileName, sizeof(bGpsInfoFileName)) == AHC_ERR_NONE)
                AHC_FS_FileDirSetAttribute(bGpsInfoFileName, sizeof(bGpsInfoFileName),AHC_FS_ATTR_HIDDEN);
        }
        else {
            AHC_FS_DirClose(ulGpsInfoDirID);
        }
    }
    #endif

    #if ((GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO) && GSNR_USE_FILE_AS_DATABUF)
    if (AHC_Gsensor_Module_Attached())
    {
        MMP_BYTE	bGsensorInfoFileName[MAX_FULL_FILENAME_SIZE];
        MMP_ULONG	ulGsensorInfoDirID;

        STRCPY(bGsensorInfoFileName, (INT8*)AHC_UF_GetRootName());
        STRCAT(bGsensorInfoFileName, GSNR_TEMP_INFOFILE_DIR);

        if(AHC_FS_DirOpen(bGsensorInfoFileName, sizeof(bGsensorInfoFileName),&ulGsensorInfoDirID) != AHC_ERR_NONE)
        {
            if(AHC_FS_DirCreate(bGsensorInfoFileName, sizeof(bGsensorInfoFileName)) == AHC_ERR_NONE)
                AHC_FS_FileDirSetAttribute(bGsensorInfoFileName, sizeof(bGsensorInfoFileName),AHC_FS_ATTR_HIDDEN);
        }
        else{
            AHC_FS_DirClose(ulGsensorInfoDirID);
        }
    }
    #endif
#endif

    return MMP_TRUE;
}

AHC_BOOL AHC_RemountDevices(MEDIASETING_SETTING media)
{
    AHC_BOOL	 status;
    UINT8 oriMedia;

    switch(media)
    {

#if USING_SF_IF
        case MEDIA_SETTING_USERFAT:
             AHC_DisMountStorageMedia(AHC_MEDIA_USER_FAT);
             status = AHC_MountStorageMedia(AHC_MEDIA_USER_FAT);
        break;
        case MEDIA_SETTING_FACFAT:
             AHC_DisMountStorageMedia(AHC_MEDIA_FACTORY_FAT);
             status = AHC_MountStorageMedia(AHC_MEDIA_FACTORY_FAT);
        break;
#endif

#if USING_SD_IF
        case MEDIA_SETTING_SD_CARD:
             AHC_DBG_MSG(1, "remount MMC\r\n");
             #if USING_SM_IF
             AHC_DisMountStorageMedia(AHC_MEDIA_SMC);
             #endif
             // Why we need to remount here ? //CZ patch...20160204
             if (MMPS_FS_IsVolumeMounted("SD:\\",4) != 0)
                AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
             #if USING_SD1_IF
             if (MMPS_FS_IsVolumeMounted("SD1:\\",5) != 0)
                AHC_DisMountStorageMedia(AHC_MEDIA_MMC1);
             #endif

             oriMedia = MenuSettingConfig()->uiMediaSelect;
             MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD; // Set to 1st SD card. Because user choose to remount DCF to 1st SD  card.

             AHC_SetMediaPath(AHC_MEDIA_MMC);
             AIHC_SetMediaRootName(MMC_ROOT);
             status = AHC_MountStorageMedia(AHC_MEDIA_MMC);

             if(status == AHC_TRUE || m_EnterNoFitStorageAllocateQuery == AHC_TRUE)
             {
                //MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD;

                AHC_CreateGsensorFolder();

                if(AHC_Is2ndSDInserted())
                {
                    status = AHC_MountStorageMediaWithoutDCF(AHC_MEDIA_MMC1);

                    if(status == AHC_TRUE)
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT);
                    }
                    else
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT);
                    }
                }
                else
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT);
                }
             }
             else
             {
                MenuSettingConfig()->uiMediaSelect = oriMedia; // Restore to original setting due to 1st SD card DCF mount failed!!

                #if(defined(DEVICE_GPIO_2NDSD_PLUG))
                #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
                if(AHC_Is2ndSDInserted())
                {
                    AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
                    status = AHC_MountStorageMedia(AHC_MEDIA_MMC1);

                    if(status == AHC_TRUE)
                    {
                        MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD1;
                        AHC_SetMediaPath(AHC_MEDIA_MMC1);
                        AIHC_SetMediaRootName(MMC1_ROOT);

                        if(AHC_IsSDInserted())
                        {
                            status = AHC_MountStorageMediaWithoutDCF(AHC_MEDIA_MMC1);
                            if(status == AHC_TRUE)
                            {
                                AHC_SDMMC_SetMountState(AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT);
                            }
                            else
                            {
                                AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT);
                            }
                        }
                        else
                        {
                            AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT);
                        }
                    }
                    else
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
                    }
                }
                else
                #endif//TWOSD_WORK_MODEL
                #endif//DEVICE_GPIO_2NDSD_PLUG
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
                }
             }
        break;
#endif
#if USING_SD1_IF
        case MEDIA_SETTING_SD_CARD1:
             AHC_DBG_MSG(1, "remount MMC1\r\n");
             #if USING_SM_IF
             AHC_DisMountStorageMedia(AHC_MEDIA_SMC);
             #endif
             #if USING_SD_IF
             AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
             #endif
             AHC_DisMountStorageMedia(AHC_MEDIA_MMC1);

             oriMedia = MenuSettingConfig()->uiMediaSelect;
             MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD1; // Set to 2nd SD card. Because user choose to remount DCF to 2nd SD  card.

             AHC_SetMediaPath(AHC_MEDIA_MMC1);
             AIHC_SetMediaRootName(MMC1_ROOT);
             status = AHC_MountStorageMedia(AHC_MEDIA_MMC1);

             if(status == AHC_TRUE)
             {
                //MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD1;

                if(AHC_IsSDInserted())
                {
                    status = AHC_MountStorageMediaWithoutDCF(AHC_MEDIA_MMC);

                    if(status == AHC_TRUE)
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT);
                    }
                    else
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT);
                    }
                }
                else
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT);
                }
             }
             else
             {
                MenuSettingConfig()->uiMediaSelect = oriMedia;

                #if(defined(DEVICE_GPIO_2NDSD_PLUG))
                #if(TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
                if(AHC_IsSDInserted())
                {
                    AHC_DisMountStorageMedia(AHC_MEDIA_MMC1);
                    status = AHC_MountStorageMedia(AHC_MEDIA_MMC);

                    if(status == AHC_TRUE)
                    {
                        MenuSettingConfig()->uiMediaSelect = MEDIA_SETTING_SD_CARD;

                        if(AHC_Is2ndSDInserted())
                        {
                            status = AHC_MountStorageMediaWithoutDCF(AHC_MEDIA_MMC1);
                            AHC_SetMediaPath(AHC_MEDIA_MMC);
                            AIHC_SetMediaRootName(MMC_ROOT);

                            if(status == AHC_TRUE)
                            {
                                AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT);
                            }
                            else
                            {
                                AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT);
                            }
                        }
                        else
                        {
                            AHC_SDMMC_SetMountState(AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT);
                        }
                    }
                    else
                    {
                        AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
                    }
                }
                else
                #endif//TWOSD_WORK_MODEL
                #endif
                {
                    AHC_SDMMC_SetMountState(AHC_SD1_NO_MOUNT_SD2_NO_MOUNT);
                }
             }
        break;
#endif
#if USING_SM_IF
        case MEDIA_SETTING_INTERNAL:
            AHC_DBG_MSG(1, "remount SMC\r\n");
            #if USING_SD_IF
            AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
            #endif
            #if USING_SD1_IF
            AHC_DisMountStorageMedia(AHC_MEDIA_MMC1);
            #endif
             AHC_DisMountStorageMedia(AHC_MEDIA_SMC);
             AHC_SetMediaPath(AHC_MEDIA_SMC);
             AIHC_SetMediaRootName(SMC_ROOT);
             status = AHC_MountStorageMedia(AHC_MEDIA_SMC);
        break;
#endif
        default:
            #if USING_SM_IF
            AHC_DisMountStorageMedia(AHC_MEDIA_SMC);
            #endif
            #if USING_SD_IF
            AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
            #endif
            #if USING_SD1_IF
            AHC_DisMountStorageMedia(AHC_MEDIA_MMC1);
            #endif

#if USING_SD_IF
            AHC_SetMediaPath(AHC_MEDIA_MMC);
            AIHC_SetMediaRootName(MMC_ROOT);
            status = AHC_MountStorageMedia(AHC_MEDIA_MMC);
#elif USING_SD1_IF
            AHC_SetMediaPath(AHC_MEDIA_MMC1);
            AIHC_SetMediaRootName(MMC1_ROOT);
            status = AHC_MountStorageMedia(AHC_MEDIA_MMC1);
#elif USING_SM_IF
            AHC_SetMediaPath(AHC_MEDIA_SMC);
            AIHC_SetMediaRootName(SMC_ROOT);
            status = AHC_MountStorageMedia(AHC_MEDIA_SMC);
#endif
        break;
    }

    AHC_DBG_MSG(1, "Media Path: %d\r\n", AHC_GetMediaPath());
    AHC_DBG_MSG(1, "Root Name: %s\r\n", AIHC_GetMediaRootName());
    AHC_DBG_MSG(1, "Mount Status: %d\r\n", AHC_SDMMC_GetMountState());
    AHC_DBG_MSG(1, "SDMMC Status: %d\r\n", AHC_SDMMC_GetState());
    AHC_DBG_MSG(1, "MediaSelect = %d\r\n", MenuSettingConfig()->uiMediaSelect);

    return status;
}

AHC_BOOL AHC_IsSDInserted(void)
{
#if (SD_DETECT_EN)
    MMP_BYTE            *pbyVolume = "SD:\\";
    UINT32              uiVolLength = 4;
    AHC_FS_IOCTL_PARA   sPara;
    UINT32              uiBuffer;

    // return value is card detect status. TBD
    return AHC_FS_IOCtl(pbyVolume, uiVolLength, AHC_FS_CMD_CARD_DETECT, &sPara, &uiBuffer);
#else
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_Is2ndSDInserted(void)
{
#if (SD_DETECT_EN && defined(DEVICE_GPIO_2NDSD_PLUG))
    MMP_UBYTE tempValue;

    if(DEVICE_GPIO_2NDSD_PLUG == MMP_GPIO_MAX)
        return AHC_FALSE;

    //MMPF_PIO_EnableOutputMode(DEVICE_GPIO_2NDSD_PLUG, MMP_FALSE, MMP_TRUE);
    AHC_GPIO_SetOutputMode(DEVICE_GPIO_2NDSD_PLUG, MMP_FALSE);
    AHC_GPIO_GetData(DEVICE_GPIO_2NDSD_PLUG, &tempValue);

    if(AHC_IsSDInserted())
    {
        SDCardUsed = 0;
    }else
    {
        if(!tempValue)
        SDCardUsed = 1;
    }


    return (tempValue)?(AHC_FALSE):(AHC_TRUE);

#else
    return AHC_FALSE;
#endif
}

AHC_BOOL AHC_IsSDWriteProtect(void)
{
#if (SD_WRITE_PROTECT_EN && defined(SD_WRITE_PROTECT_GPIO))
    MMP_UBYTE tempValue;

    if(SD_WRITE_PROTECT_GPIO == MMP_GPIO_MAX)
    return AHC_FALSE;

    //MMPF_PIO_EnableOutputMode(SD_WRITE_PROTECT_GPIO, MMP_FALSE, MMP_TRUE);
    AHC_GPIO_SetOutputMode(SD_WRITE_PROTECT_GPIO, MMP_FALSE);
    AHC_GPIO_GetData(SD_WRITE_PROTECT_GPIO, &tempValue);

    return (tempValue)?(AHC_TRUE):(AHC_FALSE);
#else
    return	AHC_FALSE;
#endif
}

AHC_BOOL AHC_MountPhysicalDevice(UINT8 byMediaID)
{
    MMP_BYTE    		*pbyVolume="";
    UINT32				uiVolLength = 0;
    AHC_FS_IOCTL_PARA 	sPara;
    UINT32				uiBuffer;

    switch(byMediaID) {

    case AHC_MEDIA_MMC:
        pbyVolume = "SD:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_MMC1:
        pbyVolume = "SD1:\\";
        uiVolLength = 5;
        break;
    case AHC_MEDIA_SMC:
        pbyVolume = "SM:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_FACTORY_FAT:
    case AHC_MEDIA_USER_FAT:
        return AHC_TRUE;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    if(AHC_FS_IOCtl(pbyVolume, uiVolLength, AHC_FS_CMD_MOUNT_MEDIUM, &sPara, &uiBuffer) == AHC_ERR_NONE){
        AHC_DBG_MSG(1, "Mount %s Success \r\n",pbyVolume);
        return AHC_TRUE;
    }else{
        AHC_DBG_MSG(1, "Mount %s Fail \r\n",pbyVolume);
        return AHC_FALSE;
    }
}

AHC_BOOL AHC_UnmountPhysicalDevice(UINT8 byMediaID)
{
    MMP_BYTE    		*pbyVolume="";
    UINT32				uiVolLength = 0;
    AHC_FS_IOCTL_PARA 	sPara;
    UINT32				uiBuffer;

    switch(byMediaID) {

    case AHC_MEDIA_MMC:
        pbyVolume = "SD:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_MMC1:
        pbyVolume = "SD1:\\";
        uiVolLength = 5;
        break;
    case AHC_MEDIA_SMC:
        pbyVolume = "SM:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    if(AHC_FS_IOCtl(pbyVolume, uiVolLength, AHC_FS_CMD_UNMOUNT_MEDIUM, &sPara, &uiBuffer) == AHC_ERR_NONE){
        AHC_DBG_MSG(1, "Unmount P Success \r\n");
        return AHC_TRUE;
    }else{
        AHC_DBG_MSG(1, "Unmount P Fail \r\n");
        return AHC_FALSE;
    }
    //reset bWaitSDMountDone
    bWaitSDMountDone = AHC_FALSE;
}

AHC_BOOL AHC_UnmountVolume(UINT8 byMediaID)
{
    MMP_BYTE    		*pbyVolume;
    UINT32				uiVolLength = 0;

    switch(byMediaID) {

    case AHC_MEDIA_MMC:
        pbyVolume = "SD:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_MMC1:
        pbyVolume = "SD1:\\";
        uiVolLength = 5;
        break;
    case AHC_MEDIA_SMC:
        pbyVolume = "SM:\\";
        uiVolLength = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    if(AHC_FS_IsVolumeMounted(pbyVolume, uiVolLength) == AHC_ERR_NONE)
    {
        AHC_DBG_MSG(1, "Unmount %s \r\n", pbyVolume);
        AHC_FS_UnmountVolume(pbyVolume, uiVolLength);

        return AHC_TRUE;
    }

    return AHC_TRUE;
}


/*
    @brief Reset SD device
*/
AHC_BOOL AHC_ResetPhysicalDevice(UINT8 byMediaID)
{
    //extern RTNA_LCD_InitMainLCD(void);

    MMP_BYTE    		*bpVolume="";
    MMP_BYTE			iVolLength = 0;
    AHC_FS_IOCTL_PARA 	sPara;
    MMP_BYTE			buffer[256];

    AHC_DBG_MSG(1, "Turn off LDO 1\r\n");
    AHC_PMUCtrl_LDO(AHC_PMU_LDO_ID_1, AHC_FALSE);
    AHC_OS_Sleep(10);
    AHC_DBG_MSG(1, "Turn on LDO 1\r\n");
    AHC_PMUCtrl_LDO(AHC_PMU_LDO_ID_1, AHC_TRUE);
    AHC_OS_Sleep(10);

    switch(byMediaID) {
    case AHC_MEDIA_MMC:
        bpVolume = "SD:\\";
        iVolLength = 4;
        break;
    case AHC_MEDIA_MMC1:
        bpVolume = "SD1:\\";
        iVolLength = 5;
        break;
    case AHC_MEDIA_SMC:
        bpVolume = "SM:\\";
        iVolLength = 4;
        break;
    case AHC_MEDIA_MEMDISK:
    default:
        return AHC_FALSE;
    }

    AHC_FS_IOCtl(bpVolume, iVolLength, AHC_FS_CMD_RESET_STORAGE, &sPara, buffer);

    return AHC_TRUE;
}

UINT32 AHC_GetStorageTotalCluster(void)
{
    AHC_DBG_MSG(1, "m_StorageSizeInCluster %d\r\n", m_StorageSizeInCluster);
    return m_StorageSizeInCluster;
}

AHC_BOOL AHC_EnableDir(void)
{
    UINT8 i;

    for(i = 0; i < DCF_DB_COUNT; i++)
    {
        AHC_UF_EnableDB(i,AHC_TRUE);
    }
    #if (DCF_DB_COUNT >= 3)
    if(!AHC_Gsensor_Module_Attached())
    AHC_UF_EnableDB(DCF_DB_TYPE_DB2_EVENT, AHC_FALSE);
    #endif
    #if (SUPPORT_PARKINGMODE == PARKINGMODE_NONE)
    AHC_UF_EnableDB(DCF_DB_TYPE_DB1_PARKING, AHC_FALSE);
    #endif

    return AHC_TRUE;
}


__inline const FS_DEVICE_TYPE* AIHC_MediaGetDriver( AHC_FLASH_ID id )
{
    const FS_DEVICE_TYPE *pFlashDriver = NULL;
    switch(id)
    {
        #if FS_USE_SFLASH_DRIVER
        case AHC_MEDIA_SERIAL_FLASH:  pFlashDriver = &FS_SFLASH_Driver;         break;
        #endif

        #if FS_USE_MMC_DRIVER
        case AHC_MEDIA_SDMMC:         pFlashDriver = &FS_MMC_CardMode_Driver;   break;
        #endif

        #if FS_USE_MMC1_DRIVER
        case AHC_MEDIA_SDMMC1:        pFlashDriver = &FS_MMC1_CardMode_Driver;  break;
        #endif

        #if FS_USE_SMC_DRIVER
        case AHC_MEDIA_NAND:          pFlashDriver = &FS_SMC_Driver;            break;
        #endif

        default:
            break;
    }

    return pFlashDriver;

}
extern void MMPF_MMU_FlushDCache(void);

AHC_BOOL AHC_MediaRead(AHC_FLASH_ID nFlashId, ULONG ulSectorAddr, ULONG ulSectorNum, BYTE* pbyBuffer )
{
    const FS_DEVICE_TYPE *pFlashDriver = AIHC_MediaGetDriver(nFlashId);

    if( pFlashDriver == NULL )
    {
        return AHC_FALSE;
    }

    MMPF_MMU_FlushDCache();
    if( 0 != pFlashDriver->pfReadBurst( STORAGE_DIRECTLY_ACCESS_UNIT, ulSectorAddr, ulSectorNum, pbyBuffer ) )
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;

}

AHC_BOOL AHC_MediaWrite(AHC_FLASH_ID nFlashId, ULONG ulSectorAddr, ULONG ulSectorNum, BYTE* pbyBuffer )
{

    const FS_DEVICE_TYPE *pFlashDriver = AIHC_MediaGetDriver(nFlashId);

    if( pFlashDriver == NULL )
    {
        return AHC_FALSE;
    }

    MMPF_MMU_FlushDCache();
    if( 0 != pFlashDriver->pfWriteBurst( STORAGE_DIRECTLY_ACCESS_UNIT, ulSectorAddr, ulSectorNum, pbyBuffer ) )
    {
        return AHC_FALSE;
    }

    return AHC_TRUE;
}

UINT32 AIHC_GetSectorCheckSum( AHC_FLASH_ID nFlashId, ULONG ulSectorAddr, BYTE* pbyBuffer )
{
    int i;
    UINT32 uiCheckSum = 0;
    UINT32* puiData   = (UINT32*)pbyBuffer;

    MEMSET( pbyBuffer, 0, 512 );

    if( AHC_MediaRead( nFlashId, ulSectorAddr, 1, pbyBuffer ) )
    {
        for( i=0; i<512/sizeof(UINT32); i++)
        {
            uiCheckSum += puiData[i];
        }
    }
    else
    {
        AHC_DBG_MSG(1, "Read failed %d\n", ulSectorAddr );
    }
    return uiCheckSum;
}


#if 1
SDMMC_STATE AHC_SDMMC_GetState(void)
{
    return m_eSDMMCState;
}

void AHC_SDMMC_SetState(SDMMC_STATE val)
{
    m_eSDMMCState = val;
}

#if (ENABLE_SD_HOT_PLUGGING)

AHC_SD_MOUNT_STATUS AHC_SDMMC_GetMountState(void)
{
    return m_bSDMMCMountState;
}

void AHC_SDMMC_SetMountState(AHC_SD_MOUNT_STATUS/*SDMMC_STATE*/ val)
{
    m_bSDMMCMountState = val;
}

AHC_BOOL AHC_SDMMC_IsSD1MountDCF(void)
{
    if (AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT ||
        AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT){
        return AHC_TRUE;
    }
    else{
        do{
            AHC_OS_SleepMs(100);
            if (AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_NO_MOUNT ||
                AHC_SDMMC_GetMountState() == AHC_SD1_MASTER_MOUNT_SD2_SLAVE_MOUNT){
                return AHC_TRUE;
            }
        }while(!gAHC_InitialDone);
    }
    return AHC_FALSE;
}

AHC_BOOL AHC_SDMMC_IsSD2MountDCF(void)
{
    if (AHC_SDMMC_GetMountState() == AHC_SD1_NO_MOUNT_SD2_MASTER_MOUNT ||
        AHC_SDMMC_GetMountState() == AHC_SD1_SLAVE_MOUNT_SD2_MASTER_MOUNT)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}
#endif

UINT8 AHC_SDMMC_GetClass(UINT32 id)
{
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))
    AHC_SDMMC_Get1stCardClass(SD_SOCKET0_MAP_ID);
    AHC_SDMMC_Get1stCardClass(SD_SOCKET1_MAP_ID);

    //AHC_DBG_MSG(1, "Main Media: %d\r\n", MenuSettingConfig()->uiMediaSelect);
    //AHC_DBG_MSG(1, "Current SD Card ID1 Class %d\r\n", m_ubSDMMC_Class);
    //AHC_DBG_MSG(1, "Current SD Card ID2 Class %d\r\n", m_ub2ndSDMMC_Class);

    if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
    {
        return m_ubSDMMC_Class;
    }
    else if(MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD1)
    {
        return m_ub2ndSDMMC_Class;
    }
    else
    {
        return 0xFF;
    }

    #else//DEVICE_GPIO_2NDSD_PLUG

    MMPS_FS_GetSDClass(id, &m_ubSDMMC_Class);

    //AHC_DBG_MSG(1, "Current SD Card ID%d Class %d\r\n", id, m_ubSDMMC_Class);

    return m_ubSDMMC_Class;

    #endif//DEVICE_GPIO_2NDSD_PLUG
}

UINT8 AHC_SDMMC_Get1stCardClass(UINT32 id)
{
    MMPS_FS_GetSDClass(SD_SOCKET0_MAP_ID, &m_ubSDMMC_Class);

    return m_ubSDMMC_Class;
}

UINT8 AHC_SDMMC_Get2ndCardClass(UINT32 id)
{
    MMPS_FS_GetSDClass(SD_SOCKET1_MAP_ID, &m_ub2ndSDMMC_Class);

    return m_ubSDMMC_Class;
}
#endif

AHC_BOOL AHC_SDMMC_BasicCheck(void)
{
    #if(defined(DEVICE_GPIO_2NDSD_PLUG))

    #if (TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_MASTER_SLAVE)
    if (!AHC_IsSDInserted() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
    #elif (TWOSD_WORK_MODEL == TWOSD_WORK_MODEL_COMPLEMENTARY)
    if ((!AHC_IsSDInserted() && !AHC_Is2ndSDInserted()) && (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD || MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD1 ))
    #endif

    #else

    if (!AHC_IsSDInserted() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)

    #endif
    {
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_CARD, 3);
        return AHC_FALSE;
    }

    if (AHC_IsSDWriteProtect() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
    {
        AHC_WMSG_Draw(AHC_TRUE, WMSG_CARD_LOCK, 3);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}


#if defined(UI_MIO_AMY) && (UI_MIO_AMY == 1)
#define SUPPORT_AITBOOT_EX 	(1) // TBD, moved to Config_SDK.h?

#define STORAGE_TEMP_BUFFER (0x00106000)

static ULONG byCheckSumSector[512/sizeof(ULONG)];

UINT32 AHC_Media_SerialFlashFwCheckSum(void)
{
    //int i;
    int n = 0;
    UINT32 uiCheckSum = 0;
    UINT32 ulSifAddr = 0x0;
    AIT_STORAGE_INDEX_TABLE2 *pIndexTable = (AIT_STORAGE_INDEX_TABLE2 *)STORAGE_TEMP_BUFFER;

    /*
     * AitMiniBootloader
     */
    //ulSifAddr = 0x0;
    AHC_DBG_MSG(1, "dbg-%s ulSifAddr[0] = 0x%X Line%d\r\n", __FUNCTION__, ulSifAddr, __LINE__);
    MMPF_SF_FastReadData(ulSifAddr, STORAGE_TEMP_BUFFER, 512); // AitMiniBootloader Header Table
    {
        ULONG ulStartSec 	= pIndexTable->bt.ulStartBlock;
        ULONG ulSecSize 	= pIndexTable->bt.ulCodeSize >> 9;

        if ((PART_FLAG_VALID & pIndexTable->ulFlag) &&
            (ulStartSec) != 0 && (ulStartSec != 0xFFFFFFFF) &&
            (ulSecSize) != 0 && (ulSecSize  != 0xFFFFFFFF))
        {
            int j;

            for (j = ulStartSec; j < (ulStartSec + ulSecSize); j++)
            {
                uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, j, (BYTE*)byCheckSumSector);
                n++;
            }
            AHC_DBG_MSG(1, "CheckSum AitMiniBootloader 0x%X %d-%d\r\n", uiCheckSum, ulStartSec, ulSecSize);
        }
    }

    /*
     * AitBootloader
     */
    ulSifAddr = ulSifAddr + (0x1 << 12) * (pIndexTable->ulTotalSectorsInLayer);
    AHC_DBG_MSG(1, "dbg-%s ulSifAddr[1] = 0x%X Line%d\r\n", __FUNCTION__, ulSifAddr, __LINE__);
    MMPF_SF_ReadData(ulSifAddr, STORAGE_TEMP_BUFFER, 512); // AitBootloader Header Table
    {
        ULONG ulStartSec 	= pIndexTable->bt.ulStartBlock;
        ULONG ulSecSize 	= pIndexTable->bt.ulCodeSize >> 9;

        if ((PART_FLAG_VALID & pIndexTable->ulFlag) &&
            (ulStartSec) != 0 && (ulStartSec != 0xFFFFFFFF) &&
            (ulSecSize) != 0 && (ulSecSize  != 0xFFFFFFFF))
        {
            int j;

            for (j = ulStartSec; j < (ulStartSec + ulSecSize); j++)
            {
                uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, j, (BYTE*)byCheckSumSector);
                n++;
            }
            AHC_DBG_MSG(1, "CheckSum AitBootloader 0x%X %d-%d\n", uiCheckSum, ulStartSec, ulSecSize);
        }
    }

#if SUPPORT_AITBOOT_EX
    /*
     * AitBootloaderEX
     */
    ulSifAddr = ulSifAddr + (0x1 << 12) * (pIndexTable->ulTotalSectorsInLayer);
    AHC_DBG_MSG(1, "dbg-%s ulSifAddr[2] = 0x%X Line%d\r\n", __FUNCTION__, ulSifAddr, __LINE__);
    MMPF_SF_ReadData(ulSifAddr, STORAGE_TEMP_BUFFER, 512); // AitBootloaderEX Header Table
    {
        ULONG ulStartSec 	= pIndexTable->bt.ulStartBlock;
        ULONG ulSecSize 	= pIndexTable->bt.ulCodeSize >> 9;

        if ((PART_FLAG_VALID & pIndexTable->ulFlag) &&
            (ulStartSec) != 0 && (ulStartSec != 0xFFFFFFFF) &&
            (ulSecSize) != 0 && (ulSecSize  != 0xFFFFFFFF))
        {
            int j;

            for (j = ulStartSec; j < (ulStartSec + ulSecSize); j++)
            {
                uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, j, (BYTE*)byCheckSumSector);
                n++;
            }
            AHC_DBG_MSG(1, "CheckSum AitBootloaderEX 0x%X %d-%d\r\n", uiCheckSum, ulStartSec, ulSecSize);
        }
    }
#endif

    /*
     * AitALL
     */
    ulSifAddr = ulSifAddr + (0x1 << 12) * (pIndexTable->ulTotalSectorsInLayer);
    AHC_DBG_MSG(1, "dbg-%s ulSifAddr[3] = 0x%X Line%d\r\n", __FUNCTION__, ulSifAddr, __LINE__);
    MMPF_SF_ReadData(ulSifAddr, STORAGE_TEMP_BUFFER, 512); // AitALL Header Table
#if 1 // TBD
    uiCheckSum = 0;
#endif
    {
        ULONG ulStartSec 	= pIndexTable->bt.ulStartBlock;
        ULONG ulSecSize 	= pIndexTable->bt.ulCodeSize >> 9;

        if ((PART_FLAG_VALID & pIndexTable->ulFlag) &&
            (ulStartSec) != 0 && (ulStartSec != 0xFFFFFFFF) &&
            (ulSecSize) != 0 && (ulSecSize  != 0xFFFFFFFF))
        {
            int j;

            for (j = ulStartSec; j < (ulStartSec + ulSecSize); j++)
            {
                uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, j, (BYTE*)byCheckSumSector);
                n++;
            }
            AHC_DBG_MSG(1, "CheckSum AitALL 0%X %d-%d\r\n", uiCheckSum, ulStartSec, ulSecSize);
        }
    }

    AHC_DBG_MSG(1, "CheckSum caculate sectors number %d\n", n);

    return uiCheckSum;
}
#else
/*
 * old for AIT8427 platform
 */
// Define SEC_BOOT2 boot code position and size
#define SEC_BOOT_START      0
#define SEC_BOOT_SIZE       32

static ULONG byCheckSumSector[512/sizeof(ULONG)];
static ULONG byBootSector[512/sizeof(ULONG)];

UINT32 AHC_Media_SerialFlashFwCheckSum(void)
{
    int i;
    int n = 0;
    UINT32 uiCheckSum = 0;
    //AIT_STORAGE_INDEX_TABLE * pAITStorInfo;
    AIT_STORAGE_INDEX_TABLE2 *pIndexTable;

    // 1. SEC_BOOT2 16KB
    for( i=SEC_BOOT_START; i<SEC_BOOT_SIZE; i++ )
    {
        uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, i, (BYTE*) byCheckSumSector);

        AHC_DBG_MSG(1, "BOOT CheckSum[%d]  %x\n", i, uiCheckSum );
        n++;
    }

    AHC_DBG_MSG(1, "1. CheckSum  %x\n", uiCheckSum );


    // 2. BOOT SECTOR (Partition table)
    uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, SF_BOOT_OFFSET, (BYTE*)byBootSector);
    AHC_DBG_MSG(1, "2. CheckSum  %x\n", uiCheckSum );
    n++;

    // 3. AIT_BOOT
    //pAITStorInfo = (AIT_STORAGE_INDEX_TABLE *)byBootSector;
    pIndexTable = (AIT_STORAGE_INDEX_TABLE2 *)byBootSector;


    //for(i=0; i< 10; i++ )
    {
        ULONG ulStartSec = pIndexTable->bt.ulStartBlock/*pAITStorInfo->it[i].ulStartSec*/;
        ULONG ulSecSize  = pIndexTable->bt.ulCodeSize/*pAITStorInfo->it[i].ulSecSize*/;

        if( (PART_FLAG_VALID & pIndexTable->ulFlag/*pAITStorInfo->it[i].ulFlag0*/ ) &&
             ulStartSec != 0 && ulStartSec != 0xFFFFFFFF     &&
             ulSecSize != 0  && ulSecSize  != 0xFFFFFFFF        )
        {

            int j;
            for( j = ulStartSec; j< ulStartSec + ulSecSize ; j++ )
            {
                uiCheckSum += AIHC_GetSectorCheckSum(AHC_MEDIA_SERIAL_FLASH, j, (BYTE*)byCheckSumSector);
                n++;
            }
            AHC_DBG_MSG(1, "CheckSum[%d]  %x %d-%d\n",i, uiCheckSum, ulStartSec, ulSecSize );

        }
    }

    AHC_DBG_MSG(1, "CheckSum caculate sectors number %d\n", n );

    return uiCheckSum;
}
#endif

AHC_BOOL AHC_DCF_IsNoFitStorageAlloc(void)
{
    return m_EnterNoFitStorageAllocateQuery;
}

#if (SUPPORT_LONGSYS_SMART_CARD)
AHC_BOOL AHC_Media_GetSmartCardInfo(PSMART_CARD_STATUS ptSmartCardInfo)
{
    static UINT8 SmartBin[1024] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x22, 0x80, 0xF0, 0xB1, 0xAB, 0xAD, 0xF1, 0xB3, 0xC3, 0xD1, 0xF2,
    0xBC, 0xAB, 0xBA, 0xB1, 0xB0, 0xBC, 0xB2, 0xB0, 0xB0, 0xAD, 0xAB, 0xB1, 0xCF, 0xD1, 0xC3, 0xB3,
    0x23, 0x29, 0x01, 0x67, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xBE, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x4F, 0x9C, 0x69, 0x53, 0x47, 0x00, 0xFE,
    };
    UINT8 buffGet[1024] = {0};
    UINT8 buffTmp[1024] = {0};

    UINT32		dwTmpFileID;
    AHC_ERR		err;
    UINT32 		dwRead = 0;
    UINT32 		dwWrite = 0;
    UINT32 		dwWriteAllSecNumH;
    UINT32 		dwWriteAllSecNumL;
    UINT32 		dwXorValue;
    //SMART_CARD_STATUS tSmart;

    err = AHC_FS_FileOpen("SD:\\tmp.txt", AHC_StrLen("SD:\\tmp.txt"), "wb+", AHC_StrLen("wb+"), &dwTmpFileID);

    err |= AHC_FS_FileWrite(dwTmpFileID, (UINT8 *)buffTmp, 1024, (UINT32*)&dwWrite);

    err |= AHC_FS_FileSeek(dwTmpFileID, 0, AHC_FS_SEEK_SET);

    err |= AHC_FS_FileWrite(dwTmpFileID, SmartBin+512, 512, (UINT32*)&dwWrite);

    err |= AHC_FS_FileSeek(dwTmpFileID, 0, AHC_FS_SEEK_SET);

    err |= AHC_FS_FileRead(dwTmpFileID, buffGet, 1024, &dwRead);

    err |= AHC_FS_FileClose(dwTmpFileID);

    if(err){
        AHC_DBG_MSG(1, "Get LONGSYS Smart Card Info Err : %#x\n", err);
        return AHC_FALSE;
    }

    memset(ptSmartCardInfo, 0, sizeof(SMART_CARD_STATUS));
    memcpy(ptSmartCardInfo, buffGet + 512, sizeof(SMART_CARD_STATUS));
    dwWriteAllSecNumH = (UINT32)(ptSmartCardInfo->lwWriteAllSectNum >> 32);
    dwWriteAllSecNumL = (UINT32)(ptSmartCardInfo->lwWriteAllSectNum);
    //У�����ݰ�
    dwXorValue = ptSmartCardInfo->dwDevSMARTTag^
                        ptSmartCardInfo->dwDevSMARTVersions^
                        ptSmartCardInfo->dwSizeOfDevSMART^
                        ptSmartCardInfo->dwOriginalBadBlock^
                        ptSmartCardInfo->dwIncreaseBadBlock^
                        dwWriteAllSecNumH^
                        dwWriteAllSecNumL^
                        ptSmartCardInfo->dwReplaceBlockLeft^
                        ptSmartCardInfo->dwDegreOfWear^
                        ptSmartCardInfo->dwSectorTotal;

    if (dwXorValue == ptSmartCardInfo->dwXorValue &&
        ptSmartCardInfo->dwDevSMARTTag == 0x96325870)
    {
        return AHC_TRUE;
    }
    else
    {
        AHC_DBG_MSG(1, "Get Smart Info ERROR or It's not Longsys Smart Card\r\n");
        return AHC_FALSE;
    }
}
#endif
