/**
 @file AHC_Config_SDK.h
 @brief Header File for the AHC configuration.
 @author 
 @version 1.0
*/

#ifndef _AHC_CONFIG_SDK_H_
#define _AHC_CONFIG_SDK_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "config_fw.h"
#include "Customer_config.h"
#include "ahc_os.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

// MIMF Configuration
#define MIMF_CUSTOMIZED_SORT_NONE               (0)
#define MIMF_CUSTOMIZED_SORT_DECREASE           (1)
#define MIMF_CUSTOMIZED_SORT_FILETYPE           (2)
#define MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE  (3)
#define MIMF_CUSTOMIZED_SORT_TYPE               (MIMF_CUSTOMIZED_SORT_NONE)

#if (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
#define MIMF_MULTI_DB_DECREASE_SELECT_DB        (0x01 << DCF_DB_TYPE_DB0_NORMAL | 0x01 << DCF_DB_TYPE_DB2_EVENT)
#endif

#define MIMF_CUSTOMIZED_SORT_MOV_ALL            (1)
#define MIMF_CUSTOMIZED_SORT_JPG_ALL            (1)

// Memory Configuration
#undef AHC_DRAM_SIZE
#define AHC_DRAM_SIZE                           (COMMON_DRAM_SIZE_128MB)

#define MALLOC_OSDBUFF_DOWN_GROWTH              (1)

#define AHC_SOUNDFILE_DRAM_ADDR                 (0x0000000) // 0: SOUNDFILE doesn't at DRAM
#define AHC_THUMB_BUF_NUM                       (2) //1 or 2
#define AHC_GUI_STRUCT_MEMORY_SIZE              (0x80000)
#define AHC_MENU_SETTING_TEMP_BUFFER_SIZE       (8192)

// OSD Configuration
#define DDOSD                                   (0) // Dynamic Download OSD

#define DATESTAMP_COLOR_BLACK                   (0x00000000) // Use ARGB format (So far alpha is skipped)
#define DATESTAMP_COLOR_YELLOW                  (0xFFFFFF00)
#define DATESTAMP_COLOR_ORANGE                  (0xFFFF8000)
#define DATESTAMP_COLOR_WHITE                   (0xFFFFFFFF)

#define MAX_OSD_NUM                             (32)
#define ENABLE_ALPHA_BLENDING                   (0)
#define DATESTAMP_COLOR                         (DATESTAMP_COLOR_WHITE)

#define STICKER_FRONT_1                         GUI_Font32B_1
#define STICKER_FRONT_2                         GUI_Font24B_1

// General Configuration
#define AHC_GENERAL_DBG_LEVEL                   (0x0)

#define AHC_MSG_QUEUE_SIZE                      (0xC0)
#define AHC_MSG_QUEUE_VIP_SIZE                  (0x10)
#define AHC_HP_MSG_QUEUE_SIZE                   (0x10)
#define AHC_MESSAGE_QUEUE_OVF                   (0)
#define AHC_AHL_MSGQ_TIMEOUT                    (MS_TO_TICK(100))

#define MAX_PURE_FILENAME_SIZE                  (64)
#define MAX_FULL_FILENAME_SIZE                  (256) // Full Path
#define AHC_DATA_DIR                            "DATA"

#define USE_INFO_FILE                           (0)
#define AHC_INFO_LOG                            "SD:\\DATA\\Info.txt"

// DCF Configuration
#define MAX_DCF_SUPPORT_FILE_TYPE               (16)

/**
@brief  the total memory space is about 512 kB
*/
#define MAX_DCF_MEM                             (512 * 1024)
#define AHC_DCF_BACKGROUND                      (0)
#define DCF_DB_COUNT                            (5)
#define DCF_SUB_DB                              (0)
#define DCF_DCFX                                (1)

/**
@brief  DCF file name
*/
#define DCF_FILE_NAME_TYPE_NORMAL               (0)     //Use AHC_DCF   (FILE0001.MOV)
#define DCF_FILE_NAME_TYPE_DATE_TIME            (1)     //Use AHC_DCFDT (FILE131005-092011.MOV)

#define DCF_FILE_NAME_TYPE                      (DCF_FILE_NAME_TYPE_DATE_TIME)

#if (AHC_MULTI_TRACK_EN == 0)
#define DCF_DUAL_CAM_ENABLE                     (1)
#else
#define DCF_DUAL_CAM_ENABLE                     (0)
#endif

#define ALL_TYPE_FILE_BROWSER_PLAYBACK          ((DCF_DB_COUNT == 1) & 0)

#define DSC_DEFAULT_FLIE_FREECHAR               "IMAG"
#define SNAP_DEFAULT_FILE_FREECHAR              "SNAP"
#define VIDEO_DEFAULT_FLIE_FREECHAR             "MOV_"

/*
DB0
*/
#define DCF_ROOT_DIR_NAME                       "DCIM"
#define DCF_DEFAULT_DIR_FREECHAR                "_NOML"
#define DCF_DEFAULT_FILE_FREECHAR               (VIDEO_DEFAULT_FLIE_FREECHAR)
/*
DB1
*/
#define DCF_ROOT_DIR_NAME_2                     "PARK"
#define DCF_DEFAULT_DIR_FREECHAR_2              "_PARK"
#define DCF_DEFAULT_FILE_FREECHAR_2             "PARK"
/*
DB2
*/
#define DCF_ROOT_DIR_NAME_3                     "EMER"
#define DCF_DEFAULT_DIR_FREECHAR_3              "_EMER"
#define DCF_DEFAULT_FILE_FREECHAR_3             "EMER"
/*
DB3
*/
#define DCF_ROOT_DIR_NAME_4                     "IMAG"
#define DCF_DEFAULT_DIR_FREECHAR_4              "_IMAG"
#define DCF_DEFAULT_FILE_FREECHAR_4             DSC_DEFAULT_FLIE_FREECHAR

/*
DCFDT Configuration
*/
#define DCFDT_SD_NUM                            (2)
#define DCFDT_CAM_NUM                           (2)

// Important, this definition defines the customized mount DB flow and node operation
// if the DCFDT_CUSTOM_MODULE_MODE == DCFDT_MODULEMODE_DATETIME_INDEX,
// all FILENAME_NAMING_TYPE shall be DCFDT_FILENAME_NAMING_BYINDEX
#define DCFDT_MODULEMODE_STANDARD_DATETIME      (0)
#define DCFDT_MODULEMODE_DATETIME_INDEX         (1)
#define DCFDT_CUSTOM_MODULE_MODE                (DCFDT_MODULEMODE_DATETIME_INDEX)
// only use for Index Mode of DCFDT, when new file meets duplicate name in DB,
// what system will do to the situation.
#define DCFDT_INDEXMODE_DUPLICATE_REPLACE       (0)
#define DCFDT_INDEXMODE_DUPLICATE_SKIP          (1)
#define DCFDT_INDEXMODE_DUPLICATE_PROCESSTYPE   (DCFDT_INDEXMODE_DUPLICATE_SKIP)

#define DCFDT_FILENAME_NAMING_STANDARD          (0)//FREECHAR + TIMEFORMAT + FIXEDCHAR
#define DCFDT_FILENAME_NAMING_SINGLE_CAM        (1)
#define DCFDT_FILENAME_NAMING_BYINDEX           (2)

// define format free DB for one clip share function, only use for one clip share
#define DCF_DB_FORMAT_FREE_DB                   (DCF_DB_TYPE_DB4_SHARE)
#define DCF_SHARE_FOLDER_FILE_NUM               (10)
#define DCF_SHARE_FOLDER_STORAGE_BY_SPACE       (0)
#define DCF_SHARE_FOLDER_STORAGE_BY_NUMERATOR   (1)
#define DCF_SHARE_FOLDER_STORAGE_TYPE           (DCF_SHARE_FOLDER_STORAGE_BY_SPACE)
#define DCF_SHARE_FOLDER_SPACE                  (200)  //unit : MB
#define DCF_SHARE_FOLDER_PER_FILE_SIZE          (SHARERECD_FILE_LENGTH+0x00105500) //unit : Byte
// =====defined chars of file path================
// e.g. SD:\\Normal\F\FILE010101-010101F.MOV
// DCFDT_ROOTNAME_SD \\ DCFDT_DB0_COMMON_FOLDER_PATH \ DCFDT_DB0_CAM0_FOLDER_PATH \ DCFDT_FILENAME_NAMING_TYPE . ext
#define DCFDT_FREECHAR_DB0                      "FILE"
#define DCFDT_FREECHAR_DB1                      "PARK"
#define DCFDT_FREECHAR_DB2                      "EMER"
#define DCFDT_FREECHAR_DB3                      "IMG"
#define DCFDT_FREECHAR_DB4                      "SHARE"
#define DCFDT_FREECHAR_LOCK                     "LOCK"
#define DCFDT_FIXEDCHAR_CAM0                    "F"
#define DCFDT_FIXEDCHAR_CAM1                    "R"

#define DCFDT_TIMEFORMAT_TYPE                   (DCFDT_TIMEFORMAT_TYPE0)

// define of TIMEFORMAT_TYPE0
#define DCFDT_TIMEFORMAT_TYPE0_TEMPLATE         "%02d%02d%02d-%02d%02d%02d"
#define DCFDT_TIMEFORMAT_TYPE0_LEN              (13)

// if add SD card, define ROOTNAME_SD and add enum of DCFDT_SD_CARD_ID
#define DCFDT_ROOTNAME_SD                       "SD:"
#define DCFDT_ROOTNAME_SD1                      "SD1:"
// if add new DB, add COMMON_FOLDER_PATH and fill sDBInit_Config
// if add new Camera, add cam num and define specific CAM_FOLDER_PATH and fill sDBInit_Config

#define DCFDF_DB0_FOLDER_LEVEL                  (2)
#define DCFDT_DB0_COMMON_FOLDER_PATH            "Normal"
#define DCFDT_DB0_CAM0_FOLDER_PATH              "F"
#define DCFDT_DB0_CAM1_FOLDER_PATH              "R"
#define DCFDT_DB0_FILENAME_NAMING_TYPE          (DCFDT_FILENAME_NAMING_BYINDEX)

#define DCFDF_DB1_FOLDER_LEVEL                  (2)
#define DCFDT_DB1_COMMON_FOLDER_PATH            "Parking"
#define DCFDT_DB1_CAM0_FOLDER_PATH              "F"
#define DCFDT_DB1_CAM1_FOLDER_PATH              "R"
#define DCFDT_DB1_FILENAME_NAMING_TYPE          (DCFDT_FILENAME_NAMING_BYINDEX)

#define DCFDF_DB2_FOLDER_LEVEL                  (2)
#define DCFDT_DB2_COMMON_FOLDER_PATH            "Event"
#define DCFDT_DB2_CAM0_FOLDER_PATH              "F"
#define DCFDT_DB2_CAM1_FOLDER_PATH              "R"
#define DCFDT_DB2_FILENAME_NAMING_TYPE          (DCFDT_FILENAME_NAMING_BYINDEX)

#define DCFDF_DB3_FOLDER_LEVEL                  (2)
#define DCFDT_DB3_COMMON_FOLDER_PATH            "Photo"
#define DCFDT_DB3_CAM0_FOLDER_PATH              "F"
#define DCFDT_DB3_CAM1_FOLDER_PATH              "R"
#define DCFDT_DB3_FILENAME_NAMING_TYPE          (DCFDT_FILENAME_NAMING_BYINDEX)

#define DCFDF_DB4_FOLDER_LEVEL                  (1)
#define DCFDT_DB4_COMMON_FOLDER_PATH            "Share"
#define DCFDT_DB4_CAM0_FOLDER_PATH              "F"
#define DCFDT_DB4_CAM1_FOLDER_PATH              "R"
#define DCFDT_DB4_FILENAME_NAMING_TYPE          (DCFDT_FILENAME_NAMING_BYINDEX)
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
#define DCFDT_DBM_MULTI_FOLDER_PATH             "Multi"
#endif

// Add a check for correct naming type
#if ((DCFDT_CUSTOM_MODULE_MODE == DCFDT_MODULEMODE_DATETIME_INDEX) && (DCFDT_DB0_FILENAME_NAMING_TYPE != DCFDT_FILENAME_NAMING_BYINDEX))
#error "DCFDT_MODULEMODE_DATETIME_INDEX only supports DCFDT_FILENAME_NAMING_BYINDEX!"
#endif

#define DCFDT_NEMA_FILE_EXTENTION               "NMEA"

/*
 if DCFDT_DB_FILENAME_NAMING_TYPE = DCFDT_FILENAME_NAMING_BYINDEX save file setting
*/
#if(FS_FORMAT_FREE_ENABLE)
#if(DCF_DUAL_CAM_ENABLE)
#define DCFDT_FILEINDEX_RENAMESRC_FIlENAME      "SD:\\Normal\\F\\FILE100101-000000-100000F.AVI"
#define DCFDT_FILEINDEX_INDEXSAVED_FIlENAME     "SD:\\Normal\\F\\IndexData.txt"
#else
#define DCFDT_FILEINDEX_RENAMESRC_FIlENAME      "SD:\\Normal\\FILE100101-000000-100000F.AVI"
#define DCFDT_FILEINDEX_INDEXSAVED_FIlENAME     "SD:\\Normal\\IndexData.txt"
#endif
#else
#define DCFDT_FILEINDEX_INDEXSAVED_FIlENAME     "SD:\\IndexData.txt"
#endif

/*
DCFX
*/
#define DCFX_DB_NAME                            "BASE.dat"

/*
DB Cluster TH
*/
#if (DCF_DB_COUNT > 4)
#define DCF_CLUSTER_NUMERATOR_DB0               (49)// NORMAL
#define DCF_CLUSTER_NUMERATOR_DB1               (20)// PARK
#define DCF_CLUSTER_NUMERATOR_DB2               (20)// EMER
#define DCF_CLUSTER_NUMERATOR_DB3               (1) // PICT
#define DCF_CLUSTER_NUMERATOR_DB4               (10)// SHARE
#else
#define DCF_CLUSTER_NUMERATOR_DB0               (59)// NORMAL
#define DCF_CLUSTER_NUMERATOR_DB1               (20)// PARK
#define DCF_CLUSTER_NUMERATOR_DB2               (20)// EMER
#define DCF_CLUSTER_NUMERATOR_DB3               (1) // PICT
#endif

#define DCF_CLUSTER_NUMERATOR1_DB0              (34)// NORMAL
#define DCF_CLUSTER_NUMERATOR1_DB1              (20)// PARK
#define DCF_CLUSTER_NUMERATOR1_DB2              (45)// EMER
#define DCF_CLUSTER_NUMERATOR1_DB3              (1) // PICT
#define DCF_CLUSTER_NUMERATOR1_DB4              (0)// SHARE

#define DCF_CLUSTER_NUMERATOR2_DB0              (39)// NORMAL
#define DCF_CLUSTER_NUMERATOR2_DB1              (30)// PARK
#define DCF_CLUSTER_NUMERATOR2_DB2              (30)// EMER
#define DCF_CLUSTER_NUMERATOR2_DB3              (1) // PICT
#define DCF_CLUSTER_NUMERATOR2_DB4              (0)// SHARE

#define DCF_CLUSTER_NUMERATOR3_DB0              (69)// NORMAL
#define DCF_CLUSTER_NUMERATOR3_DB1              (0) // PARK
#define DCF_CLUSTER_NUMERATOR3_DB2              (30)// EMER
#define DCF_CLUSTER_NUMERATOR3_DB3              (1) // PICT
#define DCF_CLUSTER_NUMERATOR3_DB4              (0)// SHARE

#define DCF_FILE_NUMERATOR2_DB0                 (500)// NORMAL
#define DCF_FILE_NUMERATOR2_DB1                 (500)// PARK
#define DCF_FILE_NUMERATOR2_DB2                 (500)// EMER
#define DCF_FILE_NUMERATOR2_DB3                 (500) // PICT

#define DCF_CLUSTER_DENOMINATOR                 (100)

#define DELETION_BY_FILE_NUM                    (1)   //TBD, add it temporarily till SFN DB update, by Jerry Li

// Video Record Configuration
#define AHC_VIDEO_STICKER_POS                   AHC_ACC_TIMESTAMP_BOTTOM_RIGHT
#define STICKER_PATTERN                         (1)
#define STICKER_PATTERN_COLOR                   (DATESTAMP_COLOR_ORANGE)
#define AHC_VIDEO_STICKER_X_DEFAULT_POS         (160)
#define AHC_VIDEO_STICKER_Y_DEFAULT_POS         (40)
#define AHC_VIDEO_STICKER_Y_DELTA               (30)

#define PROTECT_FILE_NONE                       (0)
#define PROTECT_FILE_RENAME                     (1)
#define PROTECT_FILE_MOVE_SUBDB                 (2)
#define PROTECT_FILE_MOVE_DB                    (3)
#if (DCF_DB_COUNT == 1)
#define PROTECT_FILE_TYPE                       (PROTECT_FILE_RENAME)
#else
#define PROTECT_FILE_TYPE                       (PROTECT_FILE_MOVE_DB)
#endif

#define AHC_VIDEO_BITRATE_SHD30FPS_SUPPERFINE   (VR_BITRATE_SHD30P_SUPER)   //24000000
#define AHC_VIDEO_BITRATE_SHD30FPS_FINE         (VR_BITRATE_SHD30P_FINE)    // 8000000
#define AHC_VIDEO_BITRATE_FHD60FPS_SUPPERFINE   (VR_BITRATE_FHD60P_SUPER)   //32000000
#define AHC_VIDEO_BITRATE_FHD60FPS_FINE         (VR_BITRATE_FHD60P_FINE)    //16000000
#define AHC_VIDEO_BITRATE_FHD30FPS_SUPPERFINE   (VR_BITRATE_FHD30P_SUPER)   //16000000
#define AHC_VIDEO_BITRATE_FHD30FPS_FINE         (VR_BITRATE_FHD30P_FINE)    // 8000000
#define AHC_VIDEO_BITRATE_HD30FPS_SUPPERFINE    (VR_BITRATE_HD30P_SUPER)    // 7200000
#define AHC_VIDEO_BITRATE_HD30FPS_FINE          (VR_BITRATE_HD30P_FINE)     // 4000000
#define AHC_VIDEO_BITRATE_HD60FPS_SUPPERFINE    (VR_BITRATE_HD60P_SUPER)    //12000000
#define AHC_VIDEO_BITRATE_HD60FPS_FINE          (VR_BITRATE_HD60P_FINE)     // 7200000
#define AHC_VIDEO_BITRATE_VGA30FPS_SUPPERFINE   (VR_BITRATE_VGA30P_SUPER)   //12000000
#define AHC_VIDEO_BITRATE_VGA30FPS_FINE         (VR_BITRATE_VGA30P_FINE)    //10000000
#define AHC_VIDEO_BITRATE_900P30FPS_SUPPERFINE  (VR_BITRATE_900P30FPS_SUPER)
#define AHC_VIDEO_BITRATE_900P30FPS_FINE        (VR_BITRATE_900P30FPS_FINE)
#define AHC_VIDEO_BITRATE_960P30FPS_SUPPERFINE  (VR_BITRATE_960P30FPS_SUPER)
#define AHC_VIDEO_BITRATE_960P30FPS_FINE        (VR_BITRATE_960P30FPS_FINE)

#define AHC_VIDEO_MAXBITRATE_PRERECORD          (8000000)
#define AHC_VIDEO_MAXBITRATE_PRERECORD_SCD    	(6000000) // Modified by encode resolution

#define MIN_VIDEO_ENC_WIDTH                     (64)
#define MIN_VIDEO_ENC_HEIGHT                    (64)

#if (AHC_DRAM_SIZE == COMMON_DRAM_SIZE_32MB)
#define MAX_VIDEO_ENC_WIDTH                     (2304)
#define MAX_VIDEO_ENC_HEIGHT                    (1296)
#else
#define MAX_VIDEO_ENC_WIDTH                     (2304)
#define MAX_VIDEO_ENC_HEIGHT                    (1296)
#endif

#define ENABLE_DVS                              (0)
#define ENABLE_VIDEO_ERR_LOG                    (0)

#if (ENABLE_DVS == 1)
#define AHC_ENABLE_VIDEO_STICKER                (0)
#else
#define AHC_ENABLE_VIDEO_STICKER                (1)
#endif

#define VIDEO_STICKER_INDEX1_EN                 (0)

#define AHC_ENABLE_STILL_STICKER                (1)

#ifdef FILE_RENAME_STRING
#define DCF_CHARLOCK_PATTERN                    FILE_RENAME_STRING
#else
#define DCF_CHARLOCK_PATTERN                    "SOS_"
#endif

#define VR_SLOW_CARD_DETECT                     (1)
#define VRCB_TOTAL_SKIP_FRAME                   (100)
#define VRCB_CONTINUOUS_SKIP_FRAME              (5)

#define PARKINGMODE_NONE                        (0)
#define PARKINGMODE_STYLE_1                     (1)
#define PARKINGMODE_STYLE_2                     (2)
#define PARKINGMODE_STYLE_3                     (3)
#define PARKINGMODE_STYLE_4                     (4)
#define SUPPORT_PARKINGMODE                     (PARKINGMODE_STYLE_4)//(PARKINGMODE_NONE) ///(PARKINGMODE_STYLE_2)
#define PARKING_RECORD_WRITE_PRETIME            (5) // 10s  // Pre-recording time of paring mode
#define PARK_RECORD_WRTIE_MAX_TIME              (180)
#define PARK_RECORD_WRITE_POSTTIME              (10)
#define PARK_RECORD_INTERVAL                    (10)

#define EMER_RECORD_DUAL_WRITE_ENABLE           (AHC_EMERGENTRECD_SUPPORT & 1)
#define EMER_RECORD_DUAL_WRITE_PRETIME          (5)  // 5s  // Pre-recording time of emergency recording
#define EMER_RECORD_DUAL_WRTIE_DELTA            (5)
#define EMER_RECORD_DUAL_WRITE_POSTTIME         (10) //10s  // The increased time if triggered again and remaining emergency recording time <= EMER_RECORD_DUAL_WRTIE_DELTA
#define EMER_RECORD_DUAL_WRITE_INTERVAL         (20) //10s  // The emergency recorded time after 1st trigger (including pre-recording time)
#define EMER_RECORD_DUAL_WRTIE_MAX_TIME         (120)//120s = 2mins // Max time for an emergency recording
#define EMER_RECORD_WRITE_INTERVAL              (30)

#define DUAL_RECORD_WRITE_PRETIME               (5)     //  5s   // Pre-recording time of dualenc recording
#define DUAL_RECORD_WRITE_PRETIME_LIMIT         (10)    //  10s  // Pre-recording time of dualenc recording
#define DUAL_RECORD_WRITE_INTERVAL              (20)    //  10s  // The recorded time after 1st trigger (including pre-recording time)

#define SHARE_FILESIZE_OFFSET                   (28)    //  3gp file's "skip" field

// Capture Configuration
#define AHC_CAPTURE_STICKER_POS                 AHC_ACC_TIMESTAMP_BOTTOM_RIGHT
#define AHC_CAPTURE_STICKER_X_DEFAULT_POS       (160)
#define AHC_CAPTURE_STICKER_Y_DEFAULT_POS       (40)
#define AHC_CAPTURE_STICKER_Y_DELTA             (40)
#define AHC_CAPTURE_STICKER_HEIGHT              PRIMARY_DATESTAMP_HEIGHT

#define MAX_DBG_ARRAY_SIZE                      (64*1024)

#define MAX_EXIF_ASCII_LENGTH                   (64)
#define MAX_EXIF_CONFIG_ARRAY_SIZE              (16 * 1024)

// GPS Configuration
#define AHC_GPS_STICKER_ENABLE                  (0)
#define GPS_TO_RTC_TIME_OFFSET                  (0)

// Browser Configuration
#define THUMBNAIL_OSD_COLOR_FORMAT              OSD_COLOR_RGB565
#define THUMBNAIL_BACKGROUND_COLOR              RGB565_COLOR_GRAY
#define THUMBNAIL_FOCUS_COLOR                   RGB565_COLOR_BLUE2

#define AHC_BROWSER_THUMBNAIL_STYLE_0           (0)
#define AHC_BROWSER_THUMBNAIL_STYLE_1           (1)
#define AHC_BROWSER_THUMBNAIL_STYLE             AHC_BROWSER_THUMBNAIL_STYLE_1

#define MAX_DCF_IN_THUMB                        (256)
#define VIDEO_BS_SIZE_FOR_THUMB                 (512 * 1024)

#define AHC_BROWSER_DRAW_GRAY_BORDER            (1)
#define AHC_BROWSER_DRAW_FOCUS_THICK_BORDER     (0)
#define AHC_BROWSER_DRAW_PROTECT_KEY            (1)
#define AHC_BROWSER_DRAW_DUAL_FILES             (0)

// Audio Record Configuration
#define MAX_AUDIO_ENC_FORMAT                    (3)

// USB Configuration
#define MTP_FUNC                                (0)
//#define CONFIG_USB_PRODUCT_STR                {'M','i','V','u','e',' ','D','V','R',' ',' ',' ',' ',' '}

#define UVC_HOST_VIDEO_ENABLE                   (SUPPORT_USB_HOST_FUNC & (AHC_DRAM_SIZE != COMMON_DRAM_SIZE_32MB) & 1)

// SD Card Configuration
#define ENABLE_SD_HOT_PLUGGING                  (1)
#define SUPPORT_LONGSYS_SMART_CARD              (0)

// Battery detection UART message
#define ENABLE_BATTERY_DET_DEBUG                (BATTERY_DETECTION_EN & 0)
#define ENABLE_BATTERY_TEMP_DEBUG               (BATTERY_DETECTION_EN & 0)

// Speaker Control Configuration
#define NEVER_TURN_OFF_SPEAKER                  (0)

// RTC Configuration
#ifndef RTC_DEFAULT_YEAR
#define RTC_DEFAULT_YEAR                        (2015)
#endif
#ifndef RTC_DEFAULT_YEAR
#define RTC_MAX_YEAR                            (2099)
#endif

// EDOG Configuration
#define AHC_EDOG_POI_DATA_SEGMENTATION          (1)     //1:for China, 0:for other

// Video Play Configuration
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
#define AHC_HD_VIDPLAY_MAX_WIDTH                (1280)
#define AHC_HD_VIDPLAY_MAX_HEIGHT               (720)
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define AHC_HD_VIDPLAY_MAX_WIDTH                (720)
#define AHC_HD_VIDPLAY_MAX_HEIGHT               (1280)
#endif

// Misc Configuration
#define UUID_XML_FEATURE                        (0)

//#define SPEEM_CAM_MANUAL_DB                   ("SF:2:\\SpeedCam_Data_Manual.bin")

#define LOAD_MENU_DEFFAULT_SETTING_FROM_FILE    (0)
#define MENU_DEFAULT_SETTING_FILENAME           "SF:0:\\MenuSetting.bin"

#define AHC_VIDEO_PLUG_OUT_AC                   (0)///(1)

//#define CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY
//#define CFG_ENABLE_MIN_VR_TIME                (1000)      // ms
#define LOCK_KEYPAD_UNDER_WIFI_STREAMING

#define SD_UPDATE_FW_SIZE                       (9*1024*1024)  // 9 MB

////////////////////////////////////
#include "ahc_config_dummy.h"
////////////////////////////////////

// Panel YUV Configuration
#define YUV_U2U                                 (0)   //default 0
#define YUV_V2U                                 (0)   //default 0
#define YUV_U2V                                 (0)   //default 0
#define YUV_V2V                                 (32)  //default 32
#define YUV_YGAIN                               (16)  //default 16  range 0~31
#define YUV_YOFFSET                             (0)   //default 0

#define ENABLE_SET_YUV_ATTRIBUTE                (0)

#endif  // __AHC_CONFIG_SDK_H__
