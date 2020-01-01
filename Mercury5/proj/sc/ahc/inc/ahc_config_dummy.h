/**
 @file ahc_config_dummy.h
 @brief Header File for the AHC configuration.
 @author
 @version 1.0
*/

#ifndef _AHC_CONFIG_DUMMY_H_
#define _AHC_CONFIG_DUMMY_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "config_fw.h"
#include "mmps_display.h"

/*===========================================================================
 * Marco define
 *===========================================================================*/

//UI Memory allocation++
//Default value is 64MB
#ifndef AHC_THUMB_TEMP_BASE_ADDR
#define AHC_THUMB_TEMP_BASE_ADDR                (0x2700000)
#endif
#ifndef AHC_THUMB_BUF_NUM
#define AHC_THUMB_BUF_NUM                       (2) // 1 or 2
#endif

#ifndef AHC_DCF_TEMP_BASE_ADDR
#define AHC_DCF_TEMP_BASE_ADDR                  (0x4C00000)
#endif

#ifndef AHC_GUI_TEMP_BASE_ADDR
#define AHC_GUI_TEMP_BASE_ADDR                  (0x4000000) //Add 4MB for ulVideoCompBufSize
#endif

#ifndef AHC_GUI_TEMP_BASE_ADDR_HDMI
#define AHC_GUI_TEMP_BASE_ADDR_HDMI             (0x4000000)//(0x3C00000) //Andy Liu.  It causes system lock up if it is in 0x3C00000.
#endif

#ifndef AHC_GUI_TEMP_BASE_ADDR_HDMI_PHOTO_PB
#define AHC_GUI_TEMP_BASE_ADDR_HDMI_PHOTO_PB    (0x4000000)//(0x3C00000)
#endif

#ifndef AHC_GUI_STRUCT_MEMORY_SIZE
#define AHC_GUI_STRUCT_MEMORY_SIZE              (0x80000)
#endif

#ifndef AHC_SOUNDFILE_DRAM_ADDR
#define AHC_SOUNDFILE_DRAM_ADDR                 (0x4D00000)
#endif
//UI Memory allocation--

#ifndef DDOSD
#define DDOSD                                   (0)
#endif


//General
#ifndef AHC_GENERAL_DBG_LEVEL
#define AHC_GENERAL_DBG_LEVEL           0x0
#endif

#ifndef AHC_MSG_QUEUE_SIZE
#define AHC_MSG_QUEUE_SIZE              0x40
#endif

#ifndef AHC_MSG_QUEUE_VIP_SIZE
#define AHC_MSG_QUEUE_VIP_SIZE          0
#endif

#ifndef AHC_HP_MSG_QUEUE_SIZE
#define AHC_HP_MSG_QUEUE_SIZE           0x08
#endif

#ifndef MAX_PURE_FILENAME_SIZE
#define MAX_PURE_FILENAME_SIZE          64
#endif

#ifndef MAX_FULL_FILENAME_SIZE
#define MAX_FULL_FILENAME_SIZE          256
#endif

#ifndef SHOW_ALL_MENU_FUNCTIONS
#define SHOW_ALL_MENU_FUNCTIONS         0
#endif

#ifndef AHC_DATA_DIR
#define AHC_DATA_DIR                    "DATA"
#endif

#ifndef AHC_MESSAGE_QUEUE_OVF
#define AHC_MESSAGE_QUEUE_OVF           (0)
#endif

#ifndef USE_INFO_FILE
#define USE_INFO_FILE                   (0)
#endif

#ifndef AHC_INFO_LOG
#define AHC_INFO_LOG                    "SD:\\DATA\\Info.txt"
#endif


//DCF
#ifndef MAX_DCF_SUPPORT_FILE_TYPE
#define MAX_DCF_SUPPORT_FILE_TYPE       15
#endif

/**
@brief  the total memory space is about 512 kB
*/
#ifndef MAX_DCF_MEM
#define MAX_DCF_MEM                 ( 512 * 1024 )
#endif

#ifndef AHC_DCF_BACKGROUND
#define AHC_DCF_BACKGROUND              (0)
#endif

#ifndef DCF_DB_COUNT
#define DCF_DB_COUNT                    (1)
#endif

#ifndef DCF_SUB_DB
#define DCF_SUB_DB                      (0)
#endif

#ifndef DCF_DCFX
#define DCF_DCFX                        (0)
#endif

#ifndef DCF_FILE_NAME_TYPE
#define DCF_FILE_NAME_TYPE              (0)
#endif

#ifndef DSC_DEFAULT_FLIE_FREECHAR
#define DSC_DEFAULT_FLIE_FREECHAR       "PICT"
#endif

#ifndef SNAP_DEFAULT_FILE_FREECHAR
#define SNAP_DEFAULT_FILE_FREECHAR      "SNAP"
#endif

#ifndef VIDEO_DEFAULT_FLIE_FREECHAR
#define VIDEO_DEFAULT_FLIE_FREECHAR     "FILE"
#endif
/*
DB0
*/
#ifndef DCF_ROOT_DIR_NAME
#define DCF_ROOT_DIR_NAME               "DCIM"
#endif

#ifndef DCF_DEFAULT_DIR_FREECHAR
#define DCF_DEFAULT_DIR_FREECHAR        "_NOML"
#endif

#ifndef DCF_DEFAULT_FILE_FREECHAR
#define DCF_DEFAULT_FILE_FREECHAR       "NOML"
#endif
/*
DB1
*/
#ifndef DCF_ROOT_DIR_NAME_2
#define DCF_ROOT_DIR_NAME_2             "EVSW"
#endif

#ifndef DCF_DEFAULT_DIR_FREECHAR_2
#define DCF_DEFAULT_DIR_FREECHAR_2      "_EVSW"
#endif

#ifndef DCF_DEFAULT_FILE_FREECHAR_2
#define DCF_DEFAULT_FILE_FREECHAR_2     "EVSW"
#endif
/*
DB2
*/
#ifndef DCF_ROOT_DIR_NAME_3
#define DCF_ROOT_DIR_NAME_3             "EVGS"
#endif

#ifndef DCF_DEFAULT_DIR_FREECHAR_3
#define DCF_DEFAULT_DIR_FREECHAR_3      "_EVGS"
#endif

#ifndef DCF_DEFAULT_FILE_FREECHAR_3
#define DCF_DEFAULT_FILE_FREECHAR_3     "EVGS"
#endif
/*
DB3
*/
#ifndef DCF_ROOT_DIR_NAME_4
#define DCF_ROOT_DIR_NAME_4             "PICT"
#endif

#ifndef DCF_DEFAULT_DIR_FREECHAR_4
#define DCF_DEFAULT_DIR_FREECHAR_4      "_PICT"
#endif

#ifndef DCF_DEFAULT_FILE_FREECHAR_4
#define DCF_DEFAULT_FILE_FREECHAR_4     "PICT"
#endif

/*
SubDB
*/
#ifndef DCF_SUB_ROOT_DIR_NAME
#define DCF_SUB_ROOT_DIR_NAME           "EMER"
#endif

/*
DCFX
*/
#ifndef DCFX_DB_NAME
#define DCFX_DB_NAME                    "BASE.dat"
#endif


/*
DB Cluster TH
*/
#ifndef DCF_CLUSTER_NUMERATOR_DB0
#define DCF_CLUSTER_NUMERATOR_DB0       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR_DB1
#define DCF_CLUSTER_NUMERATOR_DB1       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR_DB2
#define DCF_CLUSTER_NUMERATOR_DB2       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR_DB3
#define DCF_CLUSTER_NUMERATOR_DB3       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR_DB4
#define DCF_CLUSTER_NUMERATOR_DB4       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR1_DB0
#define DCF_CLUSTER_NUMERATOR1_DB0       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR1_DB1
#define DCF_CLUSTER_NUMERATOR1_DB1       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR1_DB2
#define DCF_CLUSTER_NUMERATOR1_DB2       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR1_DB3
#define DCF_CLUSTER_NUMERATOR1_DB3       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR2_DB0
#define DCF_CLUSTER_NUMERATOR2_DB0       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR2_DB1
#define DCF_CLUSTER_NUMERATOR2_DB1       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR2_DB2
#define DCF_CLUSTER_NUMERATOR2_DB2       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR2_DB3
#define DCF_CLUSTER_NUMERATOR2_DB3       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR3_DB0
#define DCF_CLUSTER_NUMERATOR3_DB0       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR3_DB1
#define DCF_CLUSTER_NUMERATOR3_DB1       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR3_DB2
#define DCF_CLUSTER_NUMERATOR3_DB2       (0)
#endif

#ifndef DCF_CLUSTER_NUMERATOR3_DB3
#define DCF_CLUSTER_NUMERATOR3_DB3       (0)
#endif

#ifndef DCF_CLUSTER_DENOMINATOR
#define DCF_CLUSTER_DENOMINATOR         (4)
#endif

#ifndef ALL_TYPE_FILE_BROWSER_PLAYBACK
#define ALL_TYPE_FILE_BROWSER_PLAYBACK  (0)
#endif

// OSD
#ifndef MAX_OSD_NUM
#define MAX_OSD_NUM                     32
#endif

#ifndef ENABLE_ALPHA_BLENDING
#define ENABLE_ALPHA_BLENDING           (0)
#endif

#ifndef DATESTAMP_COLOR
#define DATESTAMP_COLOR                 DATESTAMP_COLOR_YELLOW
#endif

// Multilingual Font
#ifndef LANGUAGE_FONT_ENGLISH
#define LANGUAGE_FONT_ENGLISH               GUI_FontEnglish12
#endif

#ifndef LANGUAGE_FONT_SPANISH
#define LANGUAGE_FONT_SPANISH               GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_PORTUGUESE
#define LANGUAGE_FONT_PORTUGUESE            GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_RUSSIAN
#define LANGUAGE_FONT_RUSSIAN               GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_SCHINESE
#define LANGUAGE_FONT_SCHINESE              GUI_FontSChinese12
#endif

#ifndef LANGUAGE_FONT_TCHINESE
#define LANGUAGE_FONT_TCHINESE              GUI_FontTChinese12
#endif

#ifndef LANGUAGE_FONT_GERMAN
#define LANGUAGE_FONT_GERMAN                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_ITALIAN
#define LANGUAGE_FONT_ITALIAN               GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_LATVIAN
#define LANGUAGE_FONT_LATVIAN               GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_POLISH
#define LANGUAGE_FONT_POLISH                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_ROMANIAN
#define LANGUAGE_FONT_ROMANIAN              GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_SLOVAK
#define LANGUAGE_FONT_SLOVAK                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_UKRANINIAN
#define LANGUAGE_FONT_UKRANINIAN            GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_FRENCH
#define LANGUAGE_FONT_FRENCH                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_JAPANESE
#define LANGUAGE_FONT_JAPANESE              GUI_FontJapanese12
#endif

#ifndef LANGUAGE_FONT_KOREAN
#define LANGUAGE_FONT_KOREAN                GUI_FontKorean12
#endif

#ifndef LANGUAGE_FONT_CZECH
#define LANGUAGE_FONT_CZECH                 GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_TURKISH
#define LANGUAGE_FONT_TURKISH               GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_DUTCH
#define LANGUAGE_FONT_DUTCH                 GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_DANISH
#define LANGUAGE_FONT_DANISH                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_GREEK
#define LANGUAGE_FONT_GREEK                 GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_ARABIC
#define LANGUAGE_FONT_ARABIC                GUI_FontWest12
#endif

#ifndef LANGUAGE_FONT_THAI
#define LANGUAGE_FONT_THAI                  GUI_FontWest12
#endif

// video
#ifndef AHC_VIDEO_STICKER_POS
#define AHC_VIDEO_STICKER_POS               AHC_ACC_TIMESTAMP_BOTTOM_RIGHT
#endif

#ifndef AHC_VIDEO_STICKER_X_DEFAULT_POS
#define AHC_VIDEO_STICKER_X_DEFAULT_POS     (160)
#endif

#ifndef AHC_VIDEO_STICKER_Y_DEFAULT_POS
#define AHC_VIDEO_STICKER_Y_DEFAULT_POS     (40)
#endif

#ifndef AHC_VIDEO_STICKER_Y_DELTA
#define AHC_VIDEO_STICKER_Y_DELTA           (60)
#endif

//capture
#ifndef AHC_CAPTURE_STICKER_POS
#define AHC_CAPTURE_STICKER_POS             AHC_ACC_TIMESTAMP_BOTTOM_RIGHT
#endif

#ifndef AHC_CAPTURE_STICKER_X_DEFAULT_POS
#define AHC_CAPTURE_STICKER_X_DEFAULT_POS   (160)
#endif

#ifndef AHC_CAPTURE_STICKER_Y_DEFAULT_POS
#define AHC_CAPTURE_STICKER_Y_DEFAULT_POS   (40)
#endif

#ifndef AHC_CAPTURE_STICKER_Y_DELTA
#define AHC_CAPTURE_STICKER_Y_DELTA         (60)
#endif


//gps
#ifndef AHC_GPS_STICKER_ENABLE
#define AHC_GPS_STICKER_ENABLE              (1)
#endif

#ifndef THUMBNAIL_OSD_COLOR_FORMAT
#define THUMBNAIL_OSD_COLOR_FORMAT          (OSD_COLOR_RGB565)
#endif

//Browser/Thumbnail
#ifndef MAX_DCF_IN_THUMB
#define MAX_DCF_IN_THUMB                    (256)
#endif

#ifndef VIDEO_BS_SIZE_FOR_THUMB
#define VIDEO_BS_SIZE_FOR_THUMB             (512 * 1024)
#endif

//Video Record
#ifndef MIN_VIDEO_ENC_WIDTH
#define MIN_VIDEO_ENC_WIDTH             64
#endif

#ifndef MIN_VIDEO_ENC_HEIGHT
#define MIN_VIDEO_ENC_HEIGHT            64
#endif

#ifndef MAX_VIDEO_ENC_WIDTH
#define MAX_VIDEO_ENC_WIDTH             1920
#endif

#ifndef MAX_VIDEO_ENC_HEIGHT
#define MAX_VIDEO_ENC_HEIGHT            1088
#endif

#ifndef ENABLE_DVS
#define ENABLE_DVS                      0
#endif

#ifndef ENABLE_VIDEO_ERR_LOG
#define ENABLE_VIDEO_ERR_LOG            0
#endif

#ifndef AHC_ENABLE_VIDEO_STICKER
#define AHC_ENABLE_VIDEO_STICKER        0
#endif

#ifndef VIDEO_STICKER_INDEX1_EN
#define VIDEO_STICKER_INDEX1_EN         0
#endif

#ifndef AHC_ENABLE_STILL_STICKER
#define AHC_ENABLE_STILL_STICKER        1
#endif

#ifndef PROTECT_FILE_TYPE
#define PROTECT_FILE_TYPE               PROTECT_FILE_NONE
#endif

#ifndef VR_SLOW_CARD_DETECT
#define VR_SLOW_CARD_DETECT             (0)
#endif

#ifndef VRCB_TOTAL_SKIP_FRAME
#define VRCB_TOTAL_SKIP_FRAME           (0xFFFFFFFF)
#endif

#ifndef VRCB_CONTINUOUS_SKIP_FRAME
#define VRCB_CONTINUOUS_SKIP_FRAME      (0xFFFFFFFF)
#endif

//Audio Record
#ifndef MAX_AUDIO_ENC_FORMAT
#define MAX_AUDIO_ENC_FORMAT            3
#endif

#ifndef AHC_DEFAULT_VR_MIC_DGAIN
#define AHC_DEFAULT_VR_MIC_DGAIN        DEFAULT_ADC_DIGITAL_GAIN
#endif

#ifndef AHC_DEFAULT_VR_MIC_AGAIN
#define AHC_DEFAULT_VR_MIC_AGAIN        DEFAULT_ADC_ANALOG_GAIN
#endif

//DSC DBG
#ifndef MAX_DBG_ARRAY_SIZE
#define MAX_DBG_ARRAY_SIZE              (64*1024)
#endif


//EXIF
#ifndef MAX_EXIF_ASCII_LENGTH
#define MAX_EXIF_ASCII_LENGTH           64
#endif

#ifndef MAX_EXIF_CONFIG_ARRAY_SIZE
#define MAX_EXIF_CONFIG_ARRAY_SIZE      (16 * 1024)
#endif

//STROBE
#ifndef ENABLE_STROBE
#define ENABLE_STROBE                   0
#endif
//IRIS
#define ENABLE_IRIS                     0

//M SHUTTER
#define ENABLE_MECHANICAL_SHUTTER       0

// USB
#ifndef MTP_FUNC
#define MTP_FUNC                        0///< SUPPORT_MTP_FUNC is connected with this definition
#endif

#ifndef UVC_HOST_VIDEO_ENABLE
#define UVC_HOST_VIDEO_ENABLE           (0)
#endif

#ifndef USB_DETECTION_CUSTOM
#define USB_DETECTION_CUSTOM            (0)
#endif

// SD Card
#ifndef ENABLE_SD_
#define ENABLE_SD_HOT_PLUGGING          1
#endif

//Battery
#ifndef ENABLE_BATTERY_DET_DEBUG
#define ENABLE_BATTERY_DET_DEBUG                (0)
#endif

#ifndef BATTERY_ICON_WITH_DIFF_STATE
#define BATTERY_ICON_WITH_DIFF_STATE            (1)
#endif

#ifndef BATTERY_ICON_PROC_DIFF_STATE_WITH_FUNC
#define BATTERY_ICON_PROC_DIFF_STATE_WITH_FUNC  (0)
#endif

//Speaker Control
#ifndef NEVER_TURN_OFF_SPEAKER
#define NEVER_TURN_OFF_SPEAKER          0
#endif

/* For RTC Default Time */
#ifndef RTC_DEFAULT_YEAR
#define RTC_DEFAULT_YEAR                (2011)
#endif

#ifndef RTC_DEFAULT_MONTH
#define RTC_DEFAULT_MONTH               (1)
#endif

#ifndef RTC_DEFAULT_DAY
#define RTC_DEFAULT_DAY                 (1)
#endif

#ifndef RTC_DEFAULT_HOUR
#define RTC_DEFAULT_HOUR                (0)
#endif

#ifndef RTC_DEFAULT_MIN
#define RTC_DEFAULT_MIN                 (0)
#endif

#ifndef RTC_DEFAULT_SEC
#define RTC_DEFAULT_SEC                 (0)
#endif

#ifndef RTC_MAX_YEAR
#define RTC_MAX_YEAR                    (2099)
#endif

#ifndef RTC_MAX_MONTH
#define RTC_MAX_MONTH                   (12)
#endif

#ifndef RTC_MAX_DAY_31
#define RTC_MAX_DAY_31                  (31)
#endif

#ifndef RTC_MAX_DAY_30
#define RTC_MAX_DAY_30                  (30)
#endif

#ifndef RTC_MAX_HOUR
#define RTC_MAX_HOUR                    (23)
#endif

#ifndef RTC_MAX_MIN
#define RTC_MAX_MIN                     (59)
#endif

#ifndef RTC_MAX_SEC
#define RTC_MAX_SEC                     (59)
#endif

#ifndef RTC_Default_Month
#define RTC_Default_Month               (RTC_DEFAULT_MONTH)
#endif
#ifndef RTC_Default_Day
#define RTC_Default_Day                 (RTC_DEFAULT_DAY)
#endif
#ifndef RTC_Default_Hour
#define RTC_Default_Hour                (RTC_DEFAULT_HOUR)
#endif
#ifndef RTC_Default_Minute
#define RTC_Default_Minute              (RTC_DEFAULT_MIN)
#endif
#ifndef RTC_Default_Second
#define RTC_Default_Second              (RTC_DEFAULT_SEC)
#endif

// Alloc Icon Stamp (for Date/Time) in SRAM region
#ifndef PRIMARY_DATESTAMP_WIDTH
#define PRIMARY_DATESTAMP_WIDTH         320
#endif

#ifndef PRIMARY_DATESTAMP_HEIGHT
#define PRIMARY_DATESTAMP_HEIGHT        64
#endif

#ifndef PRIMARY_DATESTAMP_COLOR_FORMAT
#define PRIMARY_DATESTAMP_COLOR_FORMAT  OSD_COLOR_RGB565
#endif

#ifndef THUMB_DATESTAMP_WIDTH
#define THUMB_DATESTAMP_WIDTH           320
#endif

#ifndef THUMB_DATESTAMP_HEIGHT
#define THUMB_DATESTAMP_HEIGHT          64
#endif

#ifndef THUMB_DATESTAMP_COLOR_FORMAT
#define THUMB_DATESTAMP_COLOR_FORMAT    OSD_COLOR_RGB332
#endif

#ifndef AHC_CAPTURE_STICKER_HEIGHT
#define AHC_CAPTURE_STICKER_HEIGHT      PRIMARY_DATESTAMP_HEIGHT
#endif

#ifndef AHC_BROWSER_THUMBNAIL_STYLE
#define AHC_BROWSER_THUMBNAIL_STYLE     AHC_BROWSER_THUMBNAIL_STYLE_0
#endif

#ifndef AHC_HD_VIDPLAY_MAX_WIDTH
#define AHC_HD_VIDPLAY_MAX_WIDTH        (800)
#endif

#ifndef AHC_HD_VIDPLAY_MAX_HEIGHT
#define AHC_HD_VIDPLAY_MAX_HEIGHT       (450)
#endif

#ifndef CLOCK_SETTING_TIMER_ENABLE
#define CLOCK_SETTING_TIMER_ENABLE      (0)
#endif

#ifndef CLOCK_SETTING_TIMER_DELAY
#define CLOCK_SETTING_TIMER_DELAY       (10)
#endif

#ifndef THUMBNAIL_BACKGROUND_COLOR
#define THUMBNAIL_BACKGROUND_COLOR          RGB565_COLOR_NA
#endif

#ifndef THUMBNAIL_FOCUS_COLOR
#define THUMBNAIL_FOCUS_COLOR               RGB565_COLOR_RED
#endif

#ifndef STICKER_PATTERN
#define STICKER_PATTERN                 (0)
#endif

#ifndef STICKER_FRONT_1
#define STICKER_FRONT_1   GUI_Font32B_1
#endif

#ifndef STICKER_FRONT_2
#define STICKER_FRONT_2   GUI_Font24B_1
#endif

#ifndef DATESTAMP_DUALENC_WIDTH
#define DATESTAMP_DUALENC_WIDTH         PRIMARY_DATESTAMP_WIDTH //(1920)
#endif

#ifndef DATESTAMP_DUALENC_HEIGHT
#define DATESTAMP_DUALENC_HEIGHT        PRIMARY_DATESTAMP_HEIGHT //(64)
#endif

#ifndef EMER_RECORD_DUAL_WRITE_ENABLE
#define EMER_RECORD_DUAL_WRITE_ENABLE   (0)
#endif

#ifndef EMER_RECORD_DUAL_WRITE_PRETIME
#define EMER_RECORD_DUAL_WRITE_PRETIME  (1) // 1s
#endif

#ifndef EMER_RECORD_DUAL_WRTIE_DELTA
#define EMER_RECORD_DUAL_WRTIE_DELTA    (0)
#endif

#ifndef EMER_RECORD_DUAL_WRITE_POSTTIME
#define EMER_RECORD_DUAL_WRITE_POSTTIME (0) //50s
#endif

#ifndef EMER_RECORD_DUAL_WRITE_INTERVAL
#define EMER_RECORD_DUAL_WRITE_INTERVAL (0) //60s
#endif

#ifndef EMER_RECORD_DUAL_WRTIE_MAX_TIME
#define EMER_RECORD_DUAL_WRTIE_MAX_TIME (0)//300s = 5mins
#endif

#ifndef EMER_RECORD_WRITE_INTERVAL
#define EMER_RECORD_WRITE_INTERVAL      (60)
#endif

#ifndef UUID_XML_FEATURE
#define UUID_XML_FEATURE                (0)
#endif

//#ifndef SD_DB_UPDATER_BIN_NAME
//#define SD_DB_UPDATER_BIN_NAME          ("SD:\\SpeedCam_Data.bin")
//#endif

//#ifndef SPEED_CAM_DB_FILE_NAME
//#define SPEED_CAM_DB_FILE_NAME          ("SF:1:\\SpeedCam_Data.bin")
//#endif

#ifndef LOAD_MENU_DEFFAULT_SETTING_FROM_FILE
#define LOAD_MENU_DEFFAULT_SETTING_FROM_FILE  0
#endif //LOAD_MENU_DEFFAULT_SETTING_FROM_FILE

#ifndef MENU_DEFAULT_SETTING_FILENAME
#define MENU_DEFAULT_SETTING_FILENAME         "SF:0:\\MenuSetting.bin"
#endif




// Bitrate Setting

#ifndef AHC_VIDEO_BITRATE_FHD30FPS_SUPPERFINE
#define AHC_VIDEO_BITRATE_FHD30FPS_SUPPERFINE  (13600000)
#endif
#ifndef AHC_VIDEO_BITRATE_FHD30FPS_FINE
#define AHC_VIDEO_BITRATE_FHD30FPS_FINE        (10880000)
#endif
#ifndef AHC_VIDEO_BITRATE_HD30FPS_SUPPERFINE
#define AHC_VIDEO_BITRATE_HD30FPS_SUPPERFINE    (9000000)
#endif
#ifndef AHC_VIDEO_BITRATE_HD30FPS_FINE
#define AHC_VIDEO_BITRATE_HD30FPS_FINE          (7200000)
#endif
#ifndef AHC_VIDEO_BITRATE_HD60FPS_SUPPERFINE
#define AHC_VIDEO_BITRATE_HD60FPS_SUPPERFINE    (9000000)
#endif
#ifndef AHC_VIDEO_BITRATE_HD60FPS_FINE
#define AHC_VIDEO_BITRATE_HD60FPS_FINE          (7200000)
#endif
#ifndef AHC_VIDEO_BITRATE_VGA30FPS_SUPPERFINE
#define AHC_VIDEO_BITRATE_VGA30FPS_SUPPERFINE   (3000000)
#endif
#ifndef AHC_VIDEO_BITRATE_VGA30FPS_FINE
#define AHC_VIDEO_BITRATE_VGA30FPS_FINE         (2400000)
#endif
#ifndef AHC_VIDEO_MAXBITRATE_PRERECORD
#define AHC_VIDEO_MAXBITRATE_PRERECORD          (8000000)
#endif

#ifndef VR_PREENCODE_EN
#define VR_PREENCODE_EN                                     (0)
#endif

#ifndef CFG_SOUND_EFFECT_SPECIAL_ENABLE
#define CFG_SOUND_EFFECT_SPECIAL_ENABLE                     (0)
#endif

#ifndef SPEAKER_ENABLE_LEVEL
#define SPEAKER_ENABLE_LEVEL                                (GPIO_HIGH)
#endif

#ifndef AHC_AHL_MSGQ_TIMEOUT
#define AHC_AHL_MSGQ_TIMEOUT                                (0)
#endif

#ifndef AHC_TV_HDMI_MENU_WIN_DUPLICTE
#define AHC_TV_HDMI_MENU_WIN_DUPLICTE                       (1)
#endif

#ifndef USB_OUT_PWR_SW_PIN_DELAY_TIME
#define USB_OUT_PWR_SW_PIN_DELAY_TIME                       (300)       // ms
#endif

#ifndef SUPPORT_BUZZER
#define SUPPORT_BUZZER                                      (0)
#endif

#ifndef BUZZER_SOUND_HZ
#define BUZZER_SOUND_HZ                                     (2600)
#endif

#ifndef BUZZER_USING_SW_PWMN
#define BUZZER_USING_SW_PWMN                                (0)
#endif

#define OSD_LAYER_WINDOW_ID                                 (MMP_DISPLAY_WIN_MAIN)
#define FRONT_CAM_WINDOW_ID                                 (MMP_DISPLAY_WIN_PIP)
#define REAR_CAM_WINDOW_ID                                  (MMP_DISPLAY_WIN_OVERLAY)
#define WMSG_LAYER_WINDOW_ID                                (MMP_DISPLAY_WIN_OSD)

#define UPPER_IMAGE_WINDOW_ID                               (MMP_DISPLAY_WIN_OVERLAY)
#define LOWER_IMAGE_WINDOW_ID                               (MMP_DISPLAY_WIN_PIP)

#ifndef TV_HDMI_WMG_WIDTH
#define TV_HDMI_WMG_WIDTH                                   (320)
#endif

#ifndef TV_HDMI_WMG_HEIGHT
#define TV_HDMI_WMG_HEIGHT                                  (240)
#endif

#ifdef ALL_FW
#define _AHC_PRINT_FUNC_ENTRY_()                            {printc(FG_BLUE(">>> %s -")"\r\n", __func__);}
#define _AHC_PRINT_FUNC_EXIT_()                             {printc(FG_PURPLE("<<< %s -")"\r\n", __func__);}
#define _AHC_PRINT_FUNC_LINE_()                             {printc(FG_GREEN(">>> %s, %d")"\r\n", __func__, __LINE__);}
#endif

#ifndef PLAY_SOUND_SEQUENTIALLY
#define PLAY_SOUND_SEQUENTIALLY                             (0)
#endif

#ifndef PLAY_SOUND_DELETE_SAME_AUDIO
#define PLAY_SOUND_DELETE_SAME_AUDIO                        (1)
#endif

#ifndef DRIVING_SAFETY_REMIND_HEADLIGHT
#define DRIVING_SAFETY_REMIND_HEADLIGHT (0)
#endif

#ifndef VR_TIME_LIMIT_OFFSET
#define VR_TIME_LIMIT_OFFSET                                (250)    //ms
#endif

#ifndef EM_VR_TIME_LIMIT_OFFSET
#define EM_VR_TIME_LIMIT_OFFSET                             (0)    //ms
#endif

#ifndef SET_MOTION_DETECTION_MOVIE_CLIP_TIME
#define SET_MOTION_DETECTION_MOVIE_CLIP_TIME                (0)
#endif

#ifndef MOTION_DETECTION_MOVIE_CLIP_TIME
#define MOTION_DETECTION_MOVIE_CLIP_TIME                    (120)
#endif

/*******************************************/
//  0x0500 0000 ~ 0x04FF CBE0       FS&SD&AUDIO��
//  0x04EA 0100 ~ 0x04FF CBE0       unused
//  0x04EA 0000 ~ 0x04EA 0100       boot status data
//  0x04E8 0000 ~ 0x04EA 0000       unused
//  0x4E00 0000 ~ 0x04E8 0000       DCF Mount DB
//  0x04DF FC00 ~ 0x4E00 0000       SFDATA
//  0x04DE E680 ~ 0x04DF FC00       unused
//  0x04B0 0000 ~ 0x04DE E680       OSD
//  0x0198 B400 ~ 0x04B0 0000       FREE ALLOC
//  0x0100 0000 ~ 0x0198 B400       FW
/*******************************************/
#ifndef TEMP_POWER_ON_SRC_INFO_ADDR
#define TEMP_POWER_ON_SRC_INFO_ADDR                         (AHC_DCF_TEMP_BASE_ADDR - 0x10)//(0x04EA0000)
#endif

#ifndef TEMP_POWER_ON_IMAGE_DMA_DEST_BUFF
#define TEMP_POWER_ON_IMAGE_DMA_DEST_BUFF                   (AHC_GUI_TEMP_BASE_ADDR - 0x100000)///(AHC_DCF_TEMP_BASE_ADDR + 0X1000)
#endif

#ifndef SUPPORT_HDMI_OUT_FOCUS
#define SUPPORT_HDMI_OUT_FOCUS                              (0)
#endif

#ifndef AHC_WMSG_BK_COLOR
#define AHC_WMSG_BK_COLOR               (0xFF646464)
#endif

#ifndef AHC_WMSG_BOUND_COLOR
#define AHC_WMSG_BOUND_COLOR            (0xFF848484)
#endif

#ifndef AHC_WMSG_FORE_COLOR
#define AHC_WMSG_FORE_COLOR             (0xFFFFFFFF)
#endif

#ifndef CONTRAST_CENTER
#define CONTRAST_CENTER     0       //Range -128~128
#endif

#ifndef SHARPNESS_CENTER
#define SHARPNESS_CENTER    0       //Range -128~128
#endif

#ifndef GAMMA_CENTER
#define GAMMA_CENTER        0       //Range -128~128
#endif

#ifndef SATURATE_CENTER
#define SATURATE_CENTER     0       //Range -128~128
#endif

#ifndef MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD
#define MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD      (0)
#endif

#ifndef MSDC_SUPPORT_SECRECY_LOCK
#define MSDC_SUPPORT_SECRECY_LOCK               (0)
#endif


#ifndef MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD
#define MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD      (0)
#endif

#ifndef MSDC_SUPPORT_SECRECY_LOCK
#define MSDC_SUPPORT_SECRECY_LOCK               (0)
#endif

#ifndef ADAS_FOCAL_LENGTH
#define ADAS_FOCAL_LENGTH           280 //390       // mm*100
#endif

#ifndef ADAS_PIXEL_SIZE
#define ADAS_PIXEL_SIZE             200 //300       // um*100
#endif

#ifndef ADAS_DZOOM_N
#define ADAS_DZOOM_N                9
#endif

#ifndef ADAS_DZOOM_M
#define ADAS_DZOOM_M                40
#endif

#ifndef ADAS_CAMERA_HEIGHT
#define ADAS_CAMERA_HEIGHT          120     // cm
#endif

#ifndef DRIVING_SAFETY_ECODRIVE
#define DRIVING_SAFETY_ECODRIVE             0
#endif

#ifndef ENABLE_RECORD_DEBUG_MSG
#define ENABLE_RECORD_DEBUG_MSG             0
#endif

#ifndef ENABLE_SHOWING_EXPOSURE_VALUE
#define ENABLE_SHOWING_EXPOSURE_VALUE       0
#endif

#ifndef DTV_UART_SEND_LDWS
#define DTV_UART_SEND_LDWS                  0
#endif

#ifndef DTV_UART_SEND_FCWS
#define DTV_UART_SEND_FCWS                  0
#endif

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    //NOP
#else
#define ncgi_op_feedback(handle,result) 0 //always return OK
#define CGI_SET_STATUS(e,s)
#define CGI_FEEDBACK()
#endif

#endif  // _AHC_CONFIG_DUMMY_H_
