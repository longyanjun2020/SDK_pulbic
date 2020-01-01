//==============================================================================
//
//  File        : ahc_common.h
//  Description : INCLUDE File for the AHC common function porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_COMMON_H_
#define _AHC_COMMON_H_

/*===========================================================================
 * Type define
 *===========================================================================*/

typedef unsigned char       AHC_BOOL;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT;
typedef unsigned int        UINT32;
typedef unsigned long       ULONG;
typedef unsigned long*      PULONG;
typedef unsigned long       ULONG32;
typedef unsigned long long  UINT64;
typedef unsigned char       UBYTE;
typedef long long           INT64;
typedef int                 INT;
typedef signed int          INT32;
typedef signed short        INT16;
typedef char                INT8;
#ifndef BYTE
typedef signed char         BYTE;
#endif
#ifndef PBYTE
typedef unsigned char*      PBYTE;
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define AHC_PRINT_RET_ERROR(force_stop, ret_val) { UartSendTrace(FG_RED("[%s] L:%d Err:0x%x!")"\r\n", __FUNCTION__, __LINE__, ret_val);\
                                                   if (force_stop) {while(1);}}

#define AHC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define AHC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define AHC_TRUE        (1)
#define AHC_FALSE       (0)

#define MODULE_ERR_SHIFT                    24

#define COMMON_KEY_SCENE                    "SCENE"
#define COMMON_KEY_METER                    "METER"
#define COMMON_KEY_EV                       "EV"
#define COMMON_KEY_ISO                      "ISO"
#define COMMON_KEY_WB                       "WB"
#define COMMON_AUTO_POWER_OFF               "AutoPowerOff"
#define COMMON_DATE_TIME_FMT                "DateTimeFormat"
#define COMMON_KEY_TV_SYSTEM                "TVSYS"
#define COMMON_KEY_GPS_RECORD_ENABLE        "GPSRecEn"
#define COMMON_KEY_VR_CLIP_TIME             "VideoClipTime"
#define COMMON_KEY_POWER_OFF_DELAY          "VideoOffTime"
#define COMMON_KEY_VR_TIMELAPSE             "VideoTimelapseEn"  // VIDEO_REC_TIMELAPSE_EN
#define COMMON_KEY_LDWS_EN                  "LDWS_EN"
#define COMMON_KEY_FCWS_EN                  "FCWS_EN"
#define COMMON_KEY_SAG_EN                   "SAG_EN"
#define COMMON_KEY_WIFI_EN                  "WiFi"
#define COMMON_KEY_DRIVER_ID                "DriverID"
#define COMMON_KEY_STICKER_LOGO_TXT         "TimeStampLogoTXT"
#define COMMON_KEY_MIC_SENSITIVITY          "MicSensitivity"
#define COMMON_KEY_MOVIE_SIZE               "VideoSize"
#define COMMON_KEY_MOVIE_QUALITY            "VideoQuality"
#define COMMON_KEY_STILL_CAP_SIZE           "StillSize"
#define COMMON_KEY_STILL_QUALITY            "StillQuality"
#define COMMON_KEY_BURST_SHOT               "BurstShot"
#define COMMON_KEY_STILL_STABILIZE          "StillStabilize"
#define COMMON_KEY_STILL_FLASH              "StillFlash"
#define COMMON_KEY_STILL_FLASH_LEVEL        "StillFlashLevel"
#define COMMON_KEY_RED_EYE_REDUCE           "RedEyeReduce"
#define COMMON_KEY_SELF_TIMER               "SelfTimer"
#define COMMON_KEY_BURST_SHOT               "BurstShot"
#define COMMON_KEY_WDR_EN                   "WDR"
#define COMMON_KEY_HDR_EN                   "HDR"
#define COMMON_KEY_GSENSOR_PWR_ON_SENS      "GSensorPowerOnSens"
#define COMMON_KEY_MOTION_SENS              "MotionSensitivity"
#define COMMON_KEY_TIMELAPSE                "TimeLapse"
#define COMMON_KEY_FLICKER                  "Flicker"
#define COMMON_KEY_LCD_POWERS               "LCDPowerSaving"
#define COMMON_KEY_GSENSOR_SENS             "GSensorSensitivity"
#define COMMON_KEY_SPEED_CAR                "SpeedCar"
#define COMMON_KEY_DISTANCE_UINT            "DistanceUnit"
#define COMMON_KEY_SPEED_CAR_CRUISE_SETTING "SpeedCamCruiseSpeedSetting"
#define COMMON_KEY_FATIGUE_ALERT            "FatigueAlert"
#define COMMON_KEY_REMIND_HEADLIGHT         "RemindHeadlight"
#define COMMON_KEY_LANGUAGE                 "Language"
#define COMMON_KEY_STATUS_LIGHT             "StatusLight"
#define COMMON_KEY_PARK_TYPE                "ParkingType"
#define COMMON_KEY_CONTRAST                 "Contrast"
#define COMMON_KEY_SATURATION               "Saturation"
#define COMMON_KEY_SHARPNESS                "Sharpness"
#define COMMON_KEY_GAMMA                    "Gamma"
#define COMMON_KEY_SLOWMOTION_EN            "SlowMotion"
#define COMMON_KEY_WNR_EN                   "WNR"
#define COMMON_KEY_PREVIEW_MODE             "PreviewMode"//CarDV~
#define COMMON_KEY_UPSIDE_DOWN              "IMGUpSideDown"
#define COMMON_KEY_AUTO_RECORD              "AutoRec"
#define COMMON_KEY_BEEP                     "Beep"
#define COMMON_KEY_FACTOROY_RESET           "Factory_Reset"
#define COMMON_KEY_FW_RELEASE_DATE          "FwDate"
#define COMMON_KEY_STORAGEALLOCATION        "StorageAllocation"
#define COMMON_KEY_PMODE_DET_EN             "PModeDetectEn"
#define COMMON_KEY_PB_VOLUME                "PlaybackVolume"
#define COMMON_KEY_LED_FLASH                "LEDFlash"
#define COMMON_KEY_DST                      "DaylightSavingTime"
#define COMMON_KEY_USE_GPS_TIME             "UseGpsTime"
#define COMMON_KEY_IMG_EFFECT               "Effect"
#define COMMON_KEY_COLOR                    "Color"
#define COMMON_KEY_FACE_TOUCH               "FaceTouch"
#define COMMON_KEY_MEDIA_SELECT             "MediaSelect"
#define COMMON_KEY_HDMIOUT                  "HDMIOutput"
#define COMMON_KEY_LCD_ROTATE               "LCDRotate"
#define COMMON_KEY_RECD_SOUND               "RecordWithAudio"
#define COMMON_KEY_PRE_RECD                 "VideoPreRecord"
#define COMMON_KEY_MOV_FPS                  "MovFPS"
#define COMMON_KEY_PMODE_LFPS               "PModeLowFPS"
#define COMMON_KEY_VMD_REC_TIME             "MotionVideoTime"
#define COMMON_KEY_VMD_SHOT_NUM             "MotionShot"
#define COMMON_KEY_SLIDESHOW_FILE_TYPE      "SlideShowFileType"
#define COMMON_KEY_BOOT_MODE                "BootMode"
#define COMMON_KEY_USB_FUNC                 "USB"
#define COMMON_KEY_BAT_VOLTAGE              "BatteryVoltage"
#define COMMON_KEY_CYCLIC_RECORD            "CyclicRecord"
#define COMMON_KEY_TIME_ZONE                "TimeZone"
#define COMMON_KEY_VIDEO_STABILIZE          "VideoStabilize"
#define COMMON_KEY_SLOW_SHUTTER             "SlowShutter"
#define COMMON_KEY_REARCAM_TYPE             "RearCamType"
#define COMMON_KEY_PQCONTRAST				"PQContrast"
#define COMMON_KEY_PQBRIGHTNESS				"PQBrightness"
#define COMMON_KEY_PQSATURATION				"PQSaturation"
#define COMMON_KEY_PQCOLORTEMP				"PQColorTemp"
#define COMMON_KEY_NIGHT_MODE_EN 			"NightMode"

// Common definition
#define COMMON_DRAM_SIZE_NG                 (0)
#define COMMON_DRAM_SIZE_32MB               (COMMON_DRAM_SIZE_NG + 1)
#define COMMON_DRAM_SIZE_64MB               (COMMON_DRAM_SIZE_32MB + 1)
#define COMMON_DRAM_SIZE_128MB              (COMMON_DRAM_SIZE_64MB + 1)
#define COMMON_DRAM_SIZE_256MB              (COMMON_DRAM_SIZE_128MB + 1)

#define COMMON_VR_VIDEO_TYPE_NG             (0)
#define COMMON_VR_VIDEO_TYPE_3GP            (COMMON_VR_VIDEO_TYPE_NG + 1)
#define COMMON_VR_VIDEO_TYPE_AVI            (COMMON_VR_VIDEO_TYPE_3GP + 1)
#define COMMON_VR_VIDEO_TYPE_TS             (COMMON_VR_VIDEO_TYPE_AVI + 1)

#define NON_CYCLING_TIME_LIMIT              (0xFFFFFFFF)

#define QUICK_PCCAM                         (QUICK_REC)

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct
{
    UINT16 PointX;
    UINT16 PointY;
} POINT, *PPOINT;

typedef struct _RECT
{
    UINT16 uiLeft;
    UINT16 uiTop;
    UINT16 uiWidth;
    UINT16 uiHeight;
} RECT, *PRECT;

typedef struct _RECTOFFSET
{
    INT16 uiOffX;
    INT16 uiOffY;
    INT16 uiOffW;
    INT16 uiOffH;
} RECTOFFSET, *PRECTOFFSET;

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _AHC_MODULE
{
    AHC_HIF         = 0,
    AHC_SD          = 15,
    AHC_FS          = 21,
} AHC_MODULE;

// DUPLICATED_DEFINITION: From _MMP_ERR in MMP_ERR.h.
typedef enum _AHC_ERR
{
    AHC_ERR_NONE = 0x00000000,

    // AHC_HIF
    AHC_HIF_ERR_PARAMETER = (AHC_HIF << MODULE_ERR_SHIFT) | 0x000001,
    AHC_HIF_ERR_MODE_NOT_SET,

    // AHC_SD
    AHC_SD_ERR_COMMAND_FAILED = (AHC_SD << MODULE_ERR_SHIFT) | 0x000001,
    AHC_SD_ERR_RESET,
    AHC_SD_ERR_PARAMETER,
    AHC_SD_ERR_DATA,
    AHC_SD_ERR_NO_CMD,
    AHC_SD_ERR_BUSY,
    AHC_SD_ERR_CARD_REMOVED,
    AHC_SD_ERR_COMMAND_SENDDONETIMEOUT,
    AHC_SD_ERR_TIMEOUT,
    AHC_SD_NO_SPACE,                    // AHC NEW

    // AHC_FS
    AHC_FS_ERR_PARAMETER = (AHC_FS << MODULE_ERR_SHIFT) | 0x000001,
    AHC_FS_ERR_TARGET_NOT_FOUND,
    AHC_FS_ERR_OPEN_FAIL,
    AHC_FS_ERR_CLOSE_FAIL,
    AHC_FS_ERR_READ_FAIL,
    AHC_FS_ERR_WRITE_FAIL,
    AHC_FS_ERR_FILE_SEEK_FAIL,
    AHC_FS_ERR_FILE_POS_ERROR,
    AHC_FS_ERR_FILE_COPY_FAIL,
    AHC_FS_ERR_FILE_ATTR_FAIL,
    AHC_FS_ERR_FILE_TIME_FAIL,
    AHC_FS_ERR_FILE_NAME_FAIL,
    AHC_FS_ERR_FILE_MOVE_FAIL,
    AHC_FS_ERR_FILE_REMOVE_FAIL,
    AHC_FS_ERR_FILE_REMNAME_FAIL,
    AHC_FS_ERR_INVALID_SIZE,
    AHC_FS_ERR_FILE_TRUNCATE_FAIL,
    AHC_FS_ERR_EXCEED_MAX_OPENED_NUM,
    AHC_FS_ERR_NO_MORE_ENTRY,
    AHC_FS_ERR_CREATE_DIR_FAIL,
    AHC_FS_ERR_DELETE_FAIL,
    AHC_FS_ERR_FILE_INIT_FAIL,
    AHC_FS_ERR_PATH_NOT_FOUND,
    AHC_FS_ERR_RESET_STORAGE,
    AHC_FS_ERR_EOF,
    AHC_FS_ERR_FILE_EXIST,
    AHC_FS_ERR_DIR_EXIST,
    AHC_FS_ERR_SEMAPHORE_FAIL,
    AHC_FS_ERR_NOT_SUPPORT,
    AHC_FS_ERR_GET_FREE_SPACE_FAIL,
    AHC_FS_ERR_IO_WRITE_FAIL,
    AHC_FS_ERR_WRITESIZE_OVERFLOW_FAIL,
    AHC_FS_ERR_FILE_HANDLE_INVALID,     // AHC NEW
    AHC_FS_ERR_COPY_FINISH,             // AHC NEW
    AHC_FS_ERR_COPY_NOT_FINISH,          // AHC NEW
    AHC_FS_ERR_SFUSER_FAIL
} AHC_ERR;

typedef enum _AHC_MODE_ID {
    AHC_MODE_IDLE                   = 0x00,
    AHC_MODE_CAPTURE_PREVIEW        = 0x10,
    AHC_MODE_STILL_CAPTURE          = 0x20,
    AHC_MODE_CONTINUOUS_CAPTURE     = 0x21,
    AHC_MODE_LONGTIME_FIRST_CAPTURE = 0x23,
    AHC_MODE_LONGTIME_NEXT_CAPTURE  = 0x24,
    AHC_MODE_LONGTIME_LAST_CAPTURE  = 0x25,
    AHC_MODE_USB_MASS_STORAGE       = 0x30,
    AHC_MODE_USB_WEBCAM             = 0x31,
    AHC_MODE_PLAYBACK               = 0x40,
    AHC_MODE_THUMB_BROWSER          = 0x50,
    AHC_MODE_VIDEO_RECORD           = 0x60,
    AHC_MODE_RECORD_PREVIEW         = 0x62,
    AHC_MODE_RECORD_PRERECD         = 0x63,
    AHC_MODE_RAW_PREVIEW            = 0x70,
    AHC_MODE_RAW_CAPTURE            = 0x71,
    AHC_MODE_NET_PLAYBACK           = 0x80,
    AHC_MODE_CALIBRATION            = 0xF0,
    AHC_MODE__NO_CHANGE,            // temp Special ID
    AHC_MODE_MAX                    = 0xFF
} AHC_MODE_ID;

typedef enum _AHC_SYS_STATUS {
    AHC_SYS_VIDRECD_STATUS = 0x00,
    AHC_SYS_VIDRECD_START,              ///< Video record operation, start
    AHC_SYS_VIDRECD_PAUSE,              ///< Video record operation, pause
    AHC_SYS_VIDRECD_RESUME,             ///< Video record operation, resume
    AHC_SYS_VIDRECD_STOP,               ///< Video record operation, stop
    AHC_SYS_VIDRECD_PREVIEW_NORMAL,   
    AHC_SYS_VIDRECD_PREVIEW_ABNORMAL,

    AHC_SYS_VIDPLAY_STATUS = 0x10,
    AHC_SYS_VIDPLAY_INVALID,            /**< The component has detected that it's internal data
                                        structures are corrupted to the point that
                                        it cannot determine it's state properly */
    AHC_SYS_VIDPLAY_LOADED,             /**< The component has been loaded but has not completed
                                        initialization. */
    AHC_SYS_VIDPLAY_IDLE,               /**< The component initialization has been completed
                                        successfully and the component is ready to start.*/
    AHC_SYS_VIDPLAY_EXECUTING,          /**< The component has accepted the start command and
                                        is processing data (if data is available) */
    AHC_SYS_VIDPLAY_PAUSE,              /**< The component has received pause command */


    AHC_SYS_USB_STATUS      = 0x20,
    AHC_SYS_USB_NORMAL,
    AHC_SYS_USB_ISADAPTER,
    AHC_SYS_USB_IDLE,

    AHC_SYS_CAPTURE_STATUS  = 0x30,

    AHC_SYS_AUDPLAY_STATUS          = 0x40,
    AHC_SYS_AUDPLAY_START           = 0x41,
    AHC_SYS_AUDPLAY_PAUSE           = 0x42,
    AHC_SYS_AUDPLAY_STOP            = 0x44,
    AHC_SYS_AUDPLAY_INVALID         = 0x48,
    
    AHC_SYS_IDLE,
    AHC_SYS_ERROR,
    
    AHC_SYS_OPERATION_MAX
} AHC_SYS_STATUS;

typedef enum _AHC_MEMORY_LOCATION_ID {
    AHC_CCD_TG_MEM_LOCATION = 0,
    AHC_UART_WRITE_MEM_LOCATION,
    AHC_UART_READ_MEM_LOCATION,
    AHC_SET_PARAMARRAY_MEM_LOCATION,
    AHC_GET_PARAM_ARRAY_MEM_LOCATION,
    AHC_FLASH_BURST_MEM_LOCATION,
    AHC_GET_IMAGE_MEM_LOCATION,
    AHC_CURR_PATH_MEM_LOCATION,
    AHC_LUMA_HIST_MEM_LOCATION,
    AHC_GET_TIME_MEM_LOCATION,
    AHC_SET_FREE_PARAMS_MEM_LOCATION,
    AHC_GET_FREE_PARAMS_MEM_LOCATION,
    AHC_AWB_TAB_MEM_LOCATION ,
    AHC_TSMT_FILE_MEM_LOCATION,
    AHC_TSMT_THUMBNAIL_MEM_LOCATION,
    AHC_SET_EXIF_MEM_LOCATION,
    AHC_GET_EXIF_MEM_LOCATION,
    AHC_RCV_FILE_MEM_LOCATION,
    AHC_SET_DPOF_GET_HEADR_PARAM_MEM_LOCATION,
    AHC_SET_DPOF_GET_JOB_PARAM_STR_MEM_LOCATION,
    AHC_SET_DPOF_GET_SRC_PARAM_MEM_LOCATION,
    AHC_OSD_TEXT_OUT_MEM_LOCATION,
    AHC_OSD_DRAW_TEXT_MEM_LOCATION,
    AHC_WRITE_I2C_MEM_LOCATION,
    AHC_READ_I2C_MEM_LOCATION,
    AHC_DRAW_TEXT_MEM_LOCATION,
    AHC_MEMORY_LOCATION_MAX
} AHC_MEMORY_LOCATION_ID;



typedef enum {
    COMMON_MOVIE_CLIP_TIME_OFF  = 0,
    COMMON_MOVIE_CLIP_TIME_6SEC,
    COMMON_MOVIE_CLIP_TIME_1MIN,
    COMMON_MOVIE_CLIP_TIME_2MIN,
    COMMON_MOVIE_CLIP_TIME_3MIN,
    COMMON_MOVIE_CLIP_TIME_5MIN,
    COMMON_MOVIE_CLIP_TIME_10MIN,
    COMMON_MOVIE_CLIP_TIME_25MIN,
    COMMON_MOVIE_CLIP_TIME_30MIN,
    COMMON_MOVIE_CLIP_TIME_NUM,
    COMMON_MOVIE_CLIP_TIME_DEFAULT = 0
} COMMON_MOVIE_CLIPTIME;

typedef enum {
    COMMON_VR_TIMELAPSE_OFF  = 0,
    COMMON_VR_TIMELAPSE_1SEC,
    COMMON_VR_TIMELAPSE_5SEC,
    COMMON_VR_TIMELAPSE_10SEC,
    COMMON_VR_TIMELAPSE_30SEC,
    COMMON_VR_TIMELAPSE_60SEC,
    COMMON_VR_TIMELAPSE_NUM,
    COMMON_VR_TIMELAPSE_DEFAULT = 0
} COMMON_VR_TIMELAPSE;

typedef enum {
    COMMON_TV_SYSTEM_NTSC = 0,
    COMMON_TV_SYSTEM_PAL,
    COMMON_TV_SYSTEM_NUM,
    COMMON_TV_SYSTEM_DEFAULT = 0
} COMMON_TV_SYSTEM_NTSC_SETTING;

typedef enum {
    COMMON_GPS_REC_INFO_LOG_VIDEO = 0,
    COMMON_GPS_REC_INFO_VIDEO_ONLY,
    COMMON_GPS_REC_INFO_LOG_ONLY,
    COMMON_GPS_REC_INFO_OFF
} COMMON_GPS_REC_INFO;

typedef enum {
    COMMON_SCENE_AUTO = 0,
    COMMON_SCENE_SPORT,
    COMMON_SCENE_PORTRAIT,
    COMMON_SCENE_LANDSCAPE,
    COMMON_SCENE_TWILIGHT_PORTRAIT,
    COMMON_SCENE_TWILIGHT,
    COMMON_SCENE_SNOW,
    COMMON_SCENE_BEACH,
    COMMON_SCENE_FIREWORKS,
    COMMON_SCENE_NUM,
    COMMON_SCENE_DEFAULT = 0
 } COMMON_SCENE_SETTING;

typedef enum {
    COMMON_METERING_CENTER = 0,
    COMMON_METERING_CENTER_SPOT,
    COMMON_METERING_NUM,
    COMMON_METERING_AVERAGE,
    COMMON_METERING_MATRIX,
    COMMON_METERING_WEIGHTED,
    COMMON_METERING_MULTI,
    COMMON_METERING_DEFAULT = 0
} COMMON_METERING_SETTING;

typedef enum {
    COMMON_EVVALUE_N20 ,
    COMMON_EVVALUE_N17 ,
    COMMON_EVVALUE_N13 ,
    COMMON_EVVALUE_N10 ,
    COMMON_EVVALUE_N07 ,
    COMMON_EVVALUE_N03 ,
    COMMON_EVVALUE_00  ,
    COMMON_EVVALUE_P03 ,
    COMMON_EVVALUE_P07 ,
    COMMON_EVVALUE_P10 ,
    COMMON_EVVALUE_P13 ,
    COMMON_EVVALUE_P17 ,
    COMMON_EVVALUE_P20 ,
    COMMON_EVVALUE_NUM ,
    COMMON_EVVALUE_DEFAULT = COMMON_EVVALUE_00
} COMMON_EVVALUE_SETTING;

typedef enum {
    COMMON_ISO_AUTO = 0,
    COMMON_ISO_100,
    COMMON_ISO_200,
    COMMON_ISO_400,
    COMMON_ISO_800,
    COMMON_ISO_1200,
    COMMON_ISO_1600,
    COMMON_ISO_3200,
    COMMON_ISO_NUM,
    COMMON_ISO_DEFAULT = 0
} COMMON_ISOMode_SETTING;

typedef enum {
    COMMON_WB_AUTO,
    COMMON_WB_DAYLIGHT,
    COMMON_WB_CLOUDY,
    COMMON_WB_FLUORESCENT1,
    COMMON_WB_FLUORESCENT2,
    COMMON_WB_FLUORESCENT3,
    COMMON_WB_INCANDESCENT,
    COMMON_WB_FLASH,
    COMMON_WB_ONEPUSH,
    COMMON_WB_ONE_PUSH_SET,
    COMMON_WB_NUM,
    COMMON_WB_DEFAULT = 0
} COMMON_WB_SETTING;

typedef enum {
    COMMON_LDWS_EN_ON = 0,
    COMMON_LDWS_EN_OFF,
    COMMON_LDWS_EN_NUM,
    COMMON_LDWS_EN_DEFAULT = COMMON_LDWS_EN_OFF
} COMMON_LDWS_EN;

typedef enum {
    COMMON_SLOWMOTION_EN_X1 = 0,
    COMMON_SLOWMOTION_EN_X3,
    COMMON_SLOWMOTION_EN_X5,
    COMMON_SLOWMOTION_EN_X7,
    COMMON_SLOWMOTION_EN_DEFAULT = COMMON_SLOWMOTION_EN_X1
} COMMON_SLOWMOTION_EN;

typedef enum {
    COMMON_FCWS_EN_ON = 0,
    COMMON_FCWS_EN_OFF,
    COMMON_FCWS_EN_NUM,
    COMMON_FCWS_EN_DEFAULT = COMMON_FCWS_EN_OFF
} COMMON_FCWS_EN;

typedef enum {
    COMMON_SAG_EN_ON = 0,
    COMMON_SAG_EN_OFF,
    COMMON_SAG_EN_NUM,
    COMMON_SAG_EN_DEFAULT = COMMON_SAG_EN_OFF
} COMMON_SAG_EN;

typedef enum {
    COMMON_HDR_EN_ON = 0,
    COMMON_HDR_EN_OFF,
    COMMON_HDR_EN_NUM,
    COMMON_HDR_EN_DEFAULT = COMMON_HDR_EN_OFF
} COMMON_HDR_EN;

typedef enum {
    COMMON_WDR_EN_ON = 0,
    COMMON_WDR_EN_OFF,
    COMMON_WDR_EN_NUM,
    COMMON_WDR_EN_DEFAULT = COMMON_WDR_EN_OFF
} COMMON_WDR_EN;

typedef enum {
    COMMON_FLICKER_50HZ = 0,
    COMMON_FLICKER_60HZ,
    COMMON_FLICKER_NUM,
    COMMON_FLICKER_DEFAULT = COMMON_FLICKER_50HZ
} COMMON_FLICKER_MODE;

typedef enum {
    COMMON_WNR_EN_OFF = 0,
    COMMON_WNR_EN_ON,
    COMMON_WNR_EN_NUM,
    COMMON_WNR_EN_DEFAULT = COMMON_WNR_EN_OFF
} COMMON_WNR_EN;

typedef enum {
    COMMON_NIGHT_MODE_EN_ON = 0,
    COMMON_NIGHT_MODE_EN_OFF,
    COMMON_NIGHT_MODE_EN_NUM,
    COMMON_NIGHT_MODE_EN_DEFAULT = COMMON_NIGHT_MODE_EN_OFF
}COMMON_NIGHT_MODE_EN;	

typedef enum {
    COMMON_STORAGE_ALLOCATION_TYPE0  = 0,
    COMMON_STORAGE_ALLOCATION_TYPE1,
    COMMON_STORAGE_ALLOCATION_TYPE2,
    COMMON_STORAGE_ALLOCATION_NUM,
    COMMON_STORAGE_ALLOCATION_DEFAULT = COMMON_STORAGE_ALLOCATION_TYPE1    
} COMMON_STORAGE_ALLOCATION;

typedef enum {
    COMMON_USE_GPS_TIME_ON = 0,
    COMMON_USE_GPS_TIME_OFF,
    COMMON_USE_GPS_TIME_NUM
} COMMON_USE_GPS_TIME;

typedef enum {
    COMMON_DST_TIME_OFF,
    COMMON_DST_ADD_1HOUR,
    COMMON_DST_ADD_30MIN,
    COMMON_DST_DEL_1HOUR,
    COMMON_DST_DEL_30MIN,
    COMMON_DST_NUM,
    COMMON_DST_DEFAULT = 0
} COMMON_DST;

extern AHC_BOOL gbAhcDbgBrk;

#endif // _AHC_COMMON_H_
