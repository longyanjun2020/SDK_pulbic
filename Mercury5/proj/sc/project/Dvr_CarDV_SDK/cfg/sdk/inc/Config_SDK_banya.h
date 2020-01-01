/*
 * PCBA config file
 */
#ifndef __CONFIG_SDK_SDK_EVB_C_TVDEC__
#define __CONFIG_SDK_SDK_EVB_C_TVDEC__

#include "ahc_rotation.h"
#include "mmps_3gprecd.h"
#include "mmp_gpio_inc.h"
#include "mmpf_sensor.h"
#include "ahc_common.h"
#include "ahc_macro.h"
#include "drv_gpio.h"
//#include "drv_ms_cus_sensor.h"

/*===========================================================================
 *  DBG Config
 *===========================================================================*/

#define AIT_HW_WATCHDOG_ENABLE      (0)
#define AIT_HW_WATCHDOG_TIMEOUT (4000) //Unit: ms.  Max value is about 4000.

/*===========================================================================
 *  OEM Config
 *===========================================================================*/

#undef  _OEM_                       // Trun ON OEM function, these function can release to customer
#undef  _OEM_DRAW_
#undef  _OEM_MENU_                  // Trun OFF OEM MENU function, these function can release to customer

/*===========================================================================
 *  OSD/Sensor Rotate Config
 *===========================================================================*/

#define FLIP_CTRL_METHOD            (CTRL_BY_MENU)

#define MENU_FLIP_SELECT            (FLIP_OSD_SNR)

#define KEY_FLIP_SELECT             (FLIP_NONE)
#define KEY_FLIP_LINK_MENU          (NOT_LINK_WITH_MENU)

#define HALL_SNR_FLIP_SELECT        (FLIP_NONE)
#define HALL_SNR_FLIP_LINK_MENU     (NOT_LINK_WITH_MENU)

#define G_SNR_FLIP_SELECT           (FLIP_NONE)
#define G_SNR_FLIP_LINK_MENU        (NOT_LINK_WITH_MENU)

/* For LCD/Sensor Rotate Config */
#define LCD_UPSIDE_DOWN
#ifdef LCD_UPSIDE_DOWN
#define LCD_0_DEGREE        (3)
#define LCD_180_DEGREE      (0)
#else
#define LCD_0_DEGREE        (0)// AHC_LCD_UPLEFT_DOWNRIGHT
#define LCD_180_DEGREE      (3)// AHC_LCD_DOWNRIGHT_UPLEFT
#endif

//#define   SENSOR_UPSIDE_DOWN
#ifdef  SENSOR_UPSIDE_DOWN
#define SENSOR_0_DEGREE     (3)
#define SENSOR_180_DEGREE   (0)
#define SENSOR_ROTATE_180   (1)
#else
#define SENSOR_0_DEGREE     (0)// AHC_SENSOR_NO_FLIP
#define SENSOR_180_DEGREE   (3)// AHC_SENSOR_COLROW_FLIP
#endif

/* For Rotate OSD/Sensor Method
   Note : It's suggested not to combine any of KEY/Hall-SNR/G-SNR Method */
#define CTRL_BY_ALL                     (CTRL_BY_MENU | CTRL_BY_KEY | CTRL_BY_HALL_SNR | CTRL_BY_G_SNR)

/* For Rotate OSD/Sensor Selection */
#define FLIP_OSD_SNR                    (FLIP_OSD | FLIP_SNR)

/* For Rotate OSD/Sensor Link With Menu Setting */
#define NOT_LINK_WITH_MENU              (0)
#define LINK_WITH_MENU                  (1)

#if 0
void ____Panel_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  Panel Config
 *===========================================================================*/

#undef  LCD_GPIO_BACK_LIGHT
//#define LCD_GPIO_BACK_LIGHT             (DRV_IO_PM_GPIO0)//SZDEMO
//#define LCD_GPIO_BACK_LIGHT             (DRV_IO_LCD_GPIO27)//YLK
#define LCD_GPIO_BACK_LIGHT             (DRV_IO_PM_GPIO0)//(MMP_GPIO5)    // AGPIO3 -->> LCD_BL

#define LCD_GPIO_BACK_LIGHT_ACT_LEVEL   (GPIO_HIGH)

//#define LCD_GPIO_RESET                  (MMP_GPIO63)  // PCGPIO31
//#define LCD_GPIO_RESET_ACT_LEVEL        (GPIO_LOW)

//#define LCD_GPIO_ENABLE                 (MMP_GPIO_MAX)
#define LCD_GPIO_ENABLE_ACT_LEVEL       (GPIO_HIGH)

#define SENSOR_GPIO_ODDEVEN_STATE    (MMP_GPIO_MAX)//uart2 multiplexing

//Panel size of different project
#define DISP_WIDTH                  (480)//(1080)   //(480)
#define DISP_HEIGHT                 (640)//(1920)   //(1280)

#define VERTICAL_PANEL          //DISP_HEIGHT > DISP_WIDTH

#define VERTICAL_LCD_DEGREE_0                (0)     // No rotate
#define VERTICAL_LCD_DEGREE_90               (1)     // 90 degree rotate
#define VERTICAL_LCD_DEGREE_270              (2)     // 270 degree rotate

#ifdef VERTICAL_PANEL
    #undef  FLM_GPIO_NUM
    //#define FLM_GPIO_NUM              (MMP_GPIO123) // PLCD_FLM -->> LCD_FLM
    #define VERTICAL_LCD                (VERTICAL_LCD_DEGREE_90)     // 0: Use Horizontal LCD
#else
    #define VERTICAL_LCD                (VERTICAL_LCD_DEGREE_0)     // 0: Use Horizontal LCD
#endif

// Temp. define
#define LCD_IF_NONE                     (0)
#define LCD_IF_SERIAL                   (1)
#define LCD_IF_PARALLEL                 (2)
#define LCD_IF_RGB                      (3)
#define LCD_IF                          (LCD_IF_RGB)

// Set up LCD display Width/Height ratio. The default is 4/3 if No these definition.
#define LCD_MODEL_RATIO_X               (16)
#define LCD_MODEL_RATIO_Y               (9)

#define CUS_LCD_BRIGHTNESS              80
#define CUS_LCD_CONTRAST                75
//Original OSD W&H in AIT SDK
#define ORIGINAL_OSD_W                  (320)
#define ORIGINAL_OSD_H                  (240)

#define OSD_DISPLAY_SCALE_HDMI_FHD      (4)
#define OSD_DISPLAY_SCALE_HDMI_HD       (2)
#define OSD_DISPLAY_SCALE_TV            (2)
#define OSD_PREVIEW_SCALE_HDMI          (1)

#if !defined(MINIBOOT_FW)
//Auto calulate OSD Multiples. if user want to use their own UI, please force OSD_DISPLAY_SCALE_LCD to 1.
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
#define OSD_DISPLAY_SCALE_LCD           (MIN((DISP_WIDTH/ORIGINAL_OSD_W),(DISP_HEIGHT/ORIGINAL_OSD_H)))
#else
#define OSD_DISPLAY_SCALE_LCD           (MIN((DISP_HEIGHT/ORIGINAL_OSD_W),(DISP_WIDTH/ORIGINAL_OSD_H)))
#endif

#if (OSD_DISPLAY_SCALE_LCD == 0)
#error "OSD_DISPLAY_SCALE_LCD can NOT be 0."
#endif
#endif

#if 0
void ____PIP_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  PIP Config
 *===========================================================================*/

#ifdef VERTICAL_PANEL
    #define PIP_WIDTH                   (240)
    #define PIP_HEIGHT                  (320)
#else
    #define PIP_WIDTH                   (320)
    #define PIP_HEIGHT                  (240)
#endif

#if 0
void ____Sensor_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  Sensor Config
 *===========================================================================*/

// Bayer RAW(MIPI or parallel)
#define BIND_SENSOR_AR0238              (0)
#define BIND_SENSOR_AR0239              (0)
#define BIND_SENSOR_AR0330              (0)
#define BIND_SENSOR_AR0330_2ND          (0)
#define BIND_SENSOR_AR0330_OTPM         (0)
#define BIND_SENSOR_AR0331              (0)
#define BIND_SENSOR_AR0832E             (0)
#define BIND_SENSOR_AR0835              (0)
#define BIND_SENSOR_AR1820              (0)
#define BIND_SENSOR_C2390               (0)
#define BIND_SENSOR_IMX123_MIPI         (0)
#define BIND_SENSOR_IMX175              (0)
#define BIND_SENSOR_IMX214              (0)
#define BIND_SENSOR_IMX291              (0)
#define BIND_SENSOR_IMX322              (0)
#define BIND_SENSOR_IMX323              (0)
#define BIND_SENSOR_IMX327              (0)
#define BIND_SENSOR_IMX307              (1)
#define BIND_SENSOR_OV2643              (0)
#define BIND_SENSOR_OV2710              (0)
#define BIND_SENSOR_OV2710_MIPI         (0)
#define BIND_SENSOR_OV2718_MIPI         (0)
#define BIND_SENSOR_OV2718_PARL         (0)
#define BIND_SENSOR_OV2735              (0)
#define BIND_SENSOR_OV4689              (0)
#define BIND_SENSOR_OV4689_2ND          (0)
#define BIND_SENSOR_OV4689_2LINE        (0)
#define BIND_SENSOR_OV5653              (0)
#define BIND_SENSOR_OV9712              (0)
#define BIND_SENSOR_OV10822             (0)
#define BIND_SENSOR_CP8210              (0)
#define BIND_SENSOR_H42_MIPI            (0)//JX-H42
#define BIND_SENSOR_OV9732_MIPI         (0)
#define BIND_SENSOR_JXF02               (0)
#define BIND_SENSOR_JXF22               (0)
#define BIND_SENSOR_PS5226              (0)
#define BIND_SENSOR_GC2023              (0)
#define BIND_SENSOR_BG0836              (0)
#define BIND_SENSOR_PS5280              (0)

// YUV sensor
#define BIND_SENSOR_OV2643              (0)
#define BIND_SENSOR_AP1302              (0)
#define BIND_SENSOR_HM1375              (0)

// TV decoder(CVBS)
#define BIND_SENSOR_BIT1603             (0)
#define BIND_SENSOR_TW9992              (0)
#define BIND_SENSOR_CJC5150             (0)
#define BIND_SENSOR_DM5150              (0)
#define BIND_SENSOR_GM7150              (0)
#define BIND_SENSOR_TP2825              (0)

// AHD
#define BIND_SENSOR_NVP6124B            (0)
#define BIND_SENSOR_RN6778              (0)
#define BIND_SENSOR_RN6752              (0)

#define SNR_R_CHECK_SIG_STABLE_COUNT    (10)    // 10x20ms
#define SNR_R_CHECK_SIG_TYPE_PERIODIC   (500)   // ms

#define SNR_CLK_POWER_SAVING_SETTING     (0)    // 0: With HDR or 1080P@60, 1: Without HDR and 1080P@60

#if 0
void ____GSensor_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  G-sensor Module Config
 *===========================================================================*/

#define SUPPORT_GSENSOR             (1)
#define GSENSOR_CONNECT_ENABLE      (SUPPORT_GSENSOR)

//For KML/RAW File
#define GSENSOR_RAW_FILE_ENABLE     (SUPPORT_GSENSOR & 0)
#define GSENSOR_MODULE_DMARD        (0)
#define GSENSOR_MODULE_LIS3DH       (1)
#define GSENSOR_MODULE_GMA301       (2)     // GMA301 / GMA301C
#define GSENSOR_MODULE_GMA302       (3)     // GMA302F / GMA303 / GMA333
#define GSENSOR_MODULE_GMA305       (4)     // GMA305
#define GSENSOR_MODULE_RT3000       (5)
#define GSENSOR_MODULE_DA380ANDSC7A30E (6)
#define GSENSOR_MODULE_SC7A30E      (7)
#define GSENSOR_MODULE_DA312        (8)
#define GSENSOR_MODULE_MC3256       (9)

#define GSENSOR_MODULE              (GSENSOR_MODULE_SC7A30E) //GSENSOR_MODULE_RT3000 / GSENSOR_MODULE_LIS3DH /


#if (GSENSOR_CONNECT_ENABLE)
#define GSENSOR_MODULE_ATT_COMPILER (1)
#define GSENSOR_MODULE_ATT_GPIO     (0)
#define GSENSOR_MODULE_GPIO         (MMP_GPIO_MAX)
#else
// Don't change
#define GSENSOR_MODULE_ATT_COMPILER (0)
#define GSENSOR_MODULE_ATT_GPIO     (0)
#define GSENSOR_MODULE_GPIO         (MMP_GPIO_MAX)
#endif

#define GSENSOR_DETECT_DIRECT       (0)
#define GSNESOR_DETECT_DIFF         (1)
#define GSENSOR_DETECT_MODE         (GSENSOR_DETECT_DIRECT)

/*
 * The maximum of N in GR(N) is depended on GSensor IC, To modify it have to check IC spec.
 * For example, DMARD06 is 1.99 for 2G, DMARD07 is 7.99 for 8G (check Dynamic Range Register)
 * GSensor driver has to check the sensitive level and makes it in acceptable range
 */
 /* 6-Level Setting */
#define GSNR_SENS_5LEVEL0           3000//mg
#define GSNR_SENS_5LEVEL1           2500//mg
#define GSNR_SENS_5LEVEL2           2000//mg
#define GSNR_SENS_5LEVEL3           1500//mg
#define GSNR_SENS_5LEVEL4           1200//mg
#define GSNR_SENS_5LEVEL5           500//mg

/* 3-Level Setting */
#define GSNR_SENS_3LEVEL0           GR(1.50)
#define GSNR_SENS_3LEVEL1           GR(1.75)
#define GSNR_SENS_3LEVEL2           GR(2.0)

#define GSNR_SEN_PARK_3LEVEL0       GR(0.46) // Fix ADC gap issue
#define GSNR_SEN_PARK_3LEVEL1       GR(0.36) // Fix ADC gap issue
#define GSNR_SEN_PARK_3LEVEL2       GR(0.2)

#define GSNR_SEN_PARK_ENT_3LEVEL0   GR(0.2)
#define GSNR_SEN_PARK_ENT_3LEVEL1   GR(0.15)
#define GSNR_SEN_PARK_ENT_3LEVEL2   GR(0.1)

#define GSNR_USE_FILE_AS_DATABUF    (SUPPORT_GSENSOR & 1)// Buffer size 500 and supports only 500 samples. Means 500/4 = 125 sec.

#define POWER_ON_BY_GSENSOR_EN      (SUPPORT_GSENSOR & 1)

#if POWER_ON_BY_GSENSOR_EN
#define GSENSOR_INT                 (MMP_GPIO99)   // PI2S_SDI
#define GSENSOR_INT_LEVEL           (GPIO_LOW)//(GPIO_HIGH)

#define POWER_ON_GSNR_SENS_LEVEL0   GR(0.25)
#define POWER_ON_GSNR_SENS_LEVEL1   GR(0.5)
#define POWER_ON_GSNR_SENS_LEVEL2   GR(0.75)

#define GSNR_PWRON_ACT              GSNR_PWRON_REC_AUTO//Auto record or not after GSNR powering on
#define GSNR_PWRON_REC_BY           GSNR_PWRON_REC_BY_SHAKED//Which event can trigger recording
#define GSNR_PWRON_MOVIE_SHAKED_ACT GSNR_PWRON_MOVIE_UNLOCKED//Lock file or not after GSNR powering on

#define POWER_ON_GSNR_MOVIE_TIME    (10)//Uint: sec
#define POWER_ON_GSNR_IDLE_TIME     (10)//Uint: sec
#endif

#if (GSENSOR_MODULE == GSENSOR_MODULE_LIS3DH)
#define GSENSOR_INT_ACT_LEVEL       (GPIO_HIGH)
#else
#define GSENSOR_INT_ACT_LEVEL       (GPIO_LOW)
#endif

#define GSENSOR_FUNC                (FUNC_LOCK_FILE | FUNC_VIDEOSTREM_INFO)

#if (GSENSOR_MODULE == GSENSOR_MODULE_LIS3DH)
//  #define GSENSOR_SLAVE_ADDR      (0x18)          // LIS3DH, default is 0x19
//  #define GSENSOR_SLAVE_ADDR      (0x28)          // LIS3DE, 7-bits mode
    #define GSNR_GROUND_AXIS        (AHC_GSENSOR_AXIS_X)
#elif (GSENSOR_MODULE == GSENSOR_MODULE_GMA301)
    #define GSENSOR_SLAVE_ADDR      (0x19)          // GMA301, default is 0x18
    #define GSNR_GROUND_AXIS        (AHC_GSENSOR_AXIS_X)
#elif (GSENSOR_MODULE == GSENSOR_MODULE_GMA302)
//  #define GSENSOR_SLAVE_ADDR      (0x31)          // GMA30x, default is 0x30
    #define GSNR_GROUND_AXIS        (AHC_GSENSOR_AXIS_X)
#endif

#if 0
void ____GPS_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  GPS Module Config
 *===========================================================================*/

#define SUPPORT_GPS                 (0)
#define GPS_CONNECT_ENABLE          (SUPPORT_GPS)

#define GPS_USE_FILE_AS_DATABUF     (SUPPORT_GPS & 1)// Buffer size 500 and supports only 500 samples. Means 500/1 = 500 sec.

//For KML/RWA File
#define GPS_RAW_FILE_ENABLE         (SUPPORT_GPS & 0) // TBD
#define GPS_RAW_FILE_EMER_EN        (SUPPORT_GPS & 0) // TBD
#define GPS_KML_FILE_ENABLE         (SUPPORT_GPS & 0)

#define GPS_MODULE_NMEA0183         (0)
#define GPS_MODULE_GMC1030          (1)
#define GPS_MODULE                  (GPS_MODULE_NMEA0183)
#define GPS_MODULE_EN_GPIO          (MMP_GPIO_MAX)

#if (GPS_CONNECT_ENABLE)
#define GPS_MODULE_ATT_COMPILER     (1)
#define GPS_MODULE_ATT_GPIO         (0)
#define GPS_MODULE_GPIO             (MMP_GPIO_MAX)
#else
#define GPS_MODULE_ATT_COMPILER     (0)
#define GPS_MODULE_ATT_GPIO         (0)
#define GPS_MODULE_GPIO             (MMP_GPIO_MAX)
#endif

#define GPS_FUNC                    (FUNC_VIDEOSTREM_INFO)

#if 0
void ____RTC_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  RTC Module Config
 *===========================================================================*/
#define RTC_CHECK_INTERVAL          (0)
#define RTC_MAX_INTERVAL            (100)

#define RTC_CHECK_SF_BASETIME       (1)
#define RTC_BASETIME_FILE_NAME      "SF:2:\\RTCBaseTime.txt"

/*===========================================================================
 *  External Module Config
 *===========================================================================*/
#define EDOG_ENABLE                 (0)

#define SD_DB_UPDATER_BIN_NAME      ("SD:\\SpeedCam_Data.bin")
#define SPEED_CAM_DB_FILE_NAME      ("SF:1:\\SpeedCam_Data.bin") //TBD. Should be configed by API.
#define SPEEM_CAM_MANUAL_DB         ("SF:2:\\SpeedCam_Data_Manual.bin") //TBD. Should be configed by API.
#define MAPLAYOUT_HEADERNAME        ("SF:1:\\SpeedCam_FileHeader.bin")
#define MAPLAYOUT_BASENAME          ("SF:1:\\DB")
#define MAPLAYOUT_EXTNAME           (".bin")
#define EDOG_DB_DYNAMIC_SEGMENT     (0)
//////////////////////////////////////////////////////////
// Gyro Sensor
//////////////////////////////////////////////////////////
#define SUPPORT_GYROSENSOR          (0) //Sync with SUPPORT_EIS
#define GYROSENSOR_CONNECT_ENABLE   (SUPPORT_GYROSENSOR)
#define BIND_GYROSNR_ITG2020        (0)
#define BIND_GYROSNR_ICG20660       (1)

//////////////////////////////////////////////////////////
// Security IC
//////////////////////////////////////////////////////////
#define SUPPORT_SECURITY_IC         (0)

//////////////////////////////////////////////////////////
// IR
//////////////////////////////////////////////////////////
#define SUPPORT_IR_CONVERTER        (0)
#define SUPPORT_ONCHIP_IRDA         (0)
#define IR_MODULE                   (IR_MODULE_IRC120X)
#define IR_CUSTOMER_ID              (0x00FF)
#define IR_KEY_EN                   (SUPPORT_IR_CONVERTER)

#if (IR_KEY_EN)
#define IR_VALUE_U                  (0xCF)
#define IR_VALUE_D                  (0x8F)
#define IR_VALUE_L                  (0xEF)
#define IR_VALUE_R                  (0xAF)
#define IR_VALUE_ENTER              (0x6F)
#define IR_VALUE_REC                (0x11)
#define IR_VALUE_MENU               (0x78)
#define IR_VALUE_PLAY               (IR_VALUE_DEFAULT)
#define IR_VALUE_MODE               (0x90)
#define IR_VALUE_SOS                (0xD2)
#define IR_VALUE_MUTE               (0x50)
#define IR_VALUE_CAPTURE            (0x38)
#define IR_VALUE_TELE               (0x72)
#define IR_VALUE_WIDE               (0x30)
#define IR_VALUE_FUNC1              (IR_VALUE_DEFAULT)
#define IR_VALUE_FUNC2              (0x19)//LCD On/Off
#define IR_VALUE_FUNC3              (0x2F)//LED
#define IR_VALUE_POWER              (IR_VALUE_DEFAULT)
#endif

//#if (SUPPORT_ONCHIP_IRDA)
#define IRDA_VALUE_U                    (0x5F)
#define IRDA_VALUE_D                    (0xAF)
#define IRDA_VALUE_L                    (0x7F)
#define IRDA_VALUE_R                    (0x9F)
#define IRDA_VALUE_MENU                 (0xb7)
#define IRDA_VALUE_MODE                 (0x8f)
#define IRDA_VALUE_REC                  (0xbf)
#define IRDA_VALUE_POWER                (IR_VALUE_DEFAULT)
//#endif

#if 0
void ____DSC_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  DSC Config
 *===========================================================================*/

#define DSC_MODE_ENABLE             (1)

/* Zoom Setting */
#define DSC_DIGIT_ZOOM_ENABLE       (DSC_MODE_ENABLE & 0)
#define DSC_DIGIT_ZOOM_RATIO_MAX    (4)

#define DSC_SELFSHOT_EN             (0)

#define DSC_BURSTSHOT_EN            (1)

#define USE_SHUTTER_SOUND           (1)

#define DSC_MULTI_MODE              (DSC_MULTI_DIS)

#define TIMELAPSE_MODE              (TIMELAPSE_NONE)

#define SUPPORT_DSC_HDR_MODE        (0)

#if 0
void ____VideoRec_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  Video & Audio Record Config
 *===========================================================================*/

#define VR_VIDEO_TYPE               (COMMON_VR_VIDEO_TYPE_3GP)

//Note: Below options are needed to refer to MMPS_3GPRECD_AUDIO_OPTION

#if (SPEECH_RECOGNIZE_EN==0)
#define AHC_AAC_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_AAC_32K_128K
#define AHC_MP3_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_MP3_32K_128K     //not support 16k fs now
#define AHC_ADPCM_AUDIO_OPTION      MMPS_3GPRECD_AUDIO_ADPCM_32K_22K
#define AHC_AMR_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_AMR_12d2K        //only support 8kHz
#define AHC_PCM_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_PCM_32K
#else
#define AHC_AAC_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_AAC_16K_64K
#define AHC_MP3_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_MP3_32K_128K     //not support 16k fs now
#define AHC_ADPCM_AUDIO_OPTION      MMPS_3GPRECD_AUDIO_ADPCM_16K_22K
#define AHC_AMR_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_AMR_12d2K        //only support 8kHz
#define AHC_PCM_AUDIO_OPTION        MMPS_3GPRECD_AUDIO_PCM_16K
#endif
#define VR_AUDIO_TYPE_AAC           (0)
#define VR_AUDIO_TYPE_MP3           (1)
#define VR_AUDIO_TYPE_ADPCM         (2)
#define VR_AUDIO_TYPE_AMR           (3)
#define VR_AUDIO_TYPE_PCM           (4)
#define VR_AUDIO_TYPE               (VR_AUDIO_TYPE_ADPCM)
#if (defined(WIFI_PORT) && WIFI_PORT == 1)
/* For reducing CPU loading with WIFI streaming*/
#undef VR_AUDIO_TYPE
#define VR_AUDIO_TYPE               (VR_AUDIO_TYPE_ADPCM)
#endif

/* Zoom Setting */
#define VIDEO_DIGIT_ZOOM_EN         (0)
#define VIDEO_DIGIT_ZOOM_RATIO_MAX  (8)     // Max 8x
#define PREVIEW_ZOOM_STEP_BY_STEP (1)

/* Bitrate Setting */
// For WIFI
#define VR_BITRATE_SHD30P_SUPER     (24000000)
#define VR_BITRATE_SHD30P_FINE      ( 8000000)
#define VR_BITRATE_FHD60P_SUPER     (32000000)
#define VR_BITRATE_FHD60P_FINE      (16000000)
#define VR_BITRATE_FHD30P_SUPER     (12000000)
#define VR_BITRATE_FHD30P_FINE      ( 8000000)
#define VR_BITRATE_HD30P_SUPER      ( 7200000)
#define VR_BITRATE_HD30P_FINE       ( 4000000)
#define VR_BITRATE_HD60P_SUPER      (12000000)
#define VR_BITRATE_HD60P_FINE       ( 7200000)
#define VR_BITRATE_VGA30P_SUPER     ( 1200000)
#define VR_BITRATE_VGA30P_FINE      ( 1000000)

#define FLICKER_PWR_LED_AT_VR_STATE (1)

#define RESET_RECORDED_TIME         (1)
#define VIDEO_REC_TIMELAPSE_EN      (1)
#define CFG_BOOT_FORCE_TURN_ON_WIFI (0)
#define CFG_BOOT_FORCE_TURN_OFF_WIFI    (1)
#define NCFG_WIFI_DEFAULT_PIN \
        { DRV_IO_PM_GPIO2, 0, 0, 0, 0}

/* Lock File Setting */
#define FILE_RENAME_STRING          "SOS_"

#define AHC_EMERGENTRECD_SUPPORT    (1)
#define AHC_UVC_EMERGRECD_SUPPORT   (0)
#define AHC_SHAREENC_SUPPORT        (0)
#define AHC_MULTI_TRACK_EN          (0)
#if (AHC_SHAREENC_SUPPORT)
#define AHC_DUAL_EMERGRECD_SUPPORT  (0)
#define SHARERECD_FILE_LENGTH       (0x3200000)     // 50 MB // pre-allocate 0x19000000 (400 MB) space
#else
#define AHC_DUAL_EMERGRECD_SUPPORT  (1)
#define SHARERECD_FILE_LENGTH       (0x0)
#endif

#if (AHC_SHAREENC_SUPPORT)
#define VR_LOCK_FILE_TYPE           (LOCK_FILE_PREV_CUR)
#else
#define VR_LOCK_FILE_TYPE           (LOCK_FILE_PREV_CUR_NEXT)
#endif

#define LIMIT_MAX_LOCK_FILE_NUM     (1)
#define MAX_LOCK_FILE_NUM           (6)
#define MAX_LOCK_FILE_ACT           (LOCK_FILE_DEL_CYCLIC)

#if (MAX_LOCK_FILE_ACT == LOCK_FILE_DEL_CYCLIC)
#define FILE_DEL_RULE               (DEL_LOCKED_FILE)
#endif

// LOCK_DEL_RULE_PERCENT is *NOT* 0, *AND*, MAX_LOCK_FILE_ACT is (LOCK_FILE_DEL_CYCLIC)
// Locked file can be deleted when the total size of read only files (clusters) is larger then
// storage clusters * (percent of LOCK_DEL_RULE_PERCENT)
#define LOCK_DEL_RULE_PERCENT       (0)

#define LIMIT_MAX_LOCK_FILE_TIME    (1)
#define MAX_LOCK_FILE_TIME          (60)//Second

#define RESET_POWER_CNT_DURING_LOCK (0)

#define LOCK_NEXTFILE_AT_VR_RESTART (0) //For LTD38/LTD65/LTD68 special request

#define SW_STICKER_EN                   (0)
#define INFO_ISP_MSG_ON_PNL             (1)//INFO_ISP_MSG_ON_PNL_C must be enable also.

#define PRIMARY_DATESTAMP_WIDTH         600
#if defined(INFO_ISP_MSG_ON_PNL)&&(INFO_ISP_MSG_ON_PNL)
#define PRIMARY_DATESTAMP_HEIGHT        320
#else
#define PRIMARY_DATESTAMP_HEIGHT        32
#endif

#define PRIMARY_DATESTAMP_COLOR_FORMAT  OSD_COLOR_RGB565
#define THUMB_DATESTAMP_WIDTH           600
#define THUMB_DATESTAMP_HEIGHT          32
#define THUMB_DATESTAMP_COLOR_FORMAT    OSD_COLOR_RGB565

#define VR_PREENCODE_EN                 (1)

#undef  NOISE_REDUCTION_EN
#define NOISE_REDUCTION_EN              (1)

/* Container/Audio Format Setting */
/* use VR_CONTAINER_TYPE_3GP, the audio has to set AAC or ADPCM, but in ADPCM some player is no sound */
#define VR_CONTAINER_TYPE               (VR_VIDEO_TYPE)
#define VR_3GP_EXT_FILENAME             ("MOV")

/* LDWS setting */
#define LDWS_WARN_MIN_SPEED             (60)     // undefined: default is 60KM/H, 0: for test only
/* FCWS setting */
//#define FCWS_WARN_DISTANCE              (10)    // default is 10m

#define FS_FORMAT_FREE_ENABLE           ( FORMAT_FREE_ENABLE & 0x0)

#define AHC_VR_THUMBNAIL_JPG_ENABLE     (1)
#define AHC_VR_THUMBNAIL_CREATE_JPG_FILE (0)

#if 0
void ____Browser_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  Browser/Playback Config
 *===========================================================================*/

#define BROWSER_EVENT_MODE_EN           (0)
#define BROWSER_STYLE                   (BROWSER_ORIGINAL_STYLE)
#define FOCUS_ON_LATEST_FILE            (1)

#define AUDIO_REC_PLAY_EN               (0)

#define SUPPORT_SPEAKER                 (1)
#define SPEAKER_ENABLE_GPIO             (MMP_GPIO97) // PI2S_SCK -->> SPK_CE
#define SPEAKER_ENABLE_LEVEL            (GPIO_HIGH)

#define MOVIE_PB_FF_EOS_ACTION          (EOS_ACT_RESTART)

#if 0
void ____SD_Card_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  SD Card Config
 *===========================================================================*/

#define SD_DETECT_EN                    (1)
#define DEVICE_GPIO_SD_PLUG             (MMP_GPIO_MAX)  // CGPIO6 --> SD_PR
#define DEVICE_GPIO_SD_POWER            (MMP_GPIO_MAX)  // CGPIO7
#define DEVICE_GPIO_SD_POWER_LEVEL      (GPIO_LOW)

#define SD_WRITE_PROTECT_EN             (0)
#define SD_WRITE_PROTECT_GPIO           (MMP_GPIO_MAX)  // SD write protect Detect

// SD Update
#define SD_UPDATE_FW_EN                 (1)
#define SD_UPDATE_FW_FORCE_EN           (1)
#define SD_FW_REMOVE_SD_UPDATE_FILE     (1)

// SD PAD
//#define CFG_SD_PIN_PAD_NUM                (SD_SOCKET0_MAP_ID)  ///SD3_PIN_PAD_NUM
//#define CFG_SD1_PIN_PAD_NUM               (SD_SOCKET1_MAP_ID)

#define ENABLE_POWER_OFF_PICTURE        (1)

/*===========================================================================
 *  Menu Config
 *===========================================================================*/

#define EXIT_MENU_PAGE_EN           (0)
#define TOP_MENU_PAGE_EN            (0)
#define TOP_MENU_PAGE_EN2           (0)

//#define   SLIDE_STRING                // Running string when string length is longer then button width
#undef  SLIDE_MENU

/*===========================================================================
 * KeyPad Config
 *===========================================================================*/

#define KEYPAD_DETECT_METHOD        (KEYPAD_DETECT_TASK)
#define RMT_CTL_TYPE                (RMT_CTL_DISABLE)
#define KEYPAD_ROTATE_EN            (0)
#define DIR_KEY_CYCLIC_LPRESS_EN    (1)
#define DIR_KEY_TYPE                (KEY_TYPE_2KEY)
#define COMBO_KEY_EN                (0)
#define COMBO_KEY_FLAGSET1          (KEYFLAG_LP_PLAY | KEYFLAG_LP_MODE)
#define COMBO_KEY_FLAGSET2          (KEYFLAG_DUMMY)

#if 0
void ____USB_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * USB/Charger Config
 *===========================================================================*/

#define CHARGE_FULL_NOTIFY                  (0)
#define CHARGE_FULL_STATUS                  (0)
#define GPIO_CHARGE_STATUS                  (MMP_GPIO_MAX)

#define USB_MODE_SELECT_EN                  (1)
#define USB_MODE_SELECT_STYLE               (MENU_ORIGINAL)

#define CHARGER_IN_ACT_VIDEO_MODE           (ACT_RECORD_VIDEO)
#define CHARGER_IN_ACT_OTHER_MODE           (ACT_CHARGING_ONLY)
#define CHARGER_OUT_ACT_VIDEO_REC           (ACT_DELAY_POWER_OFF)
#define CHARGER_OUT_ACT_OTHER_MODE          (ACT_DELAY_POWER_OFF)

//#define DEVICE_GPIO_DC_INPUT              (MMP_GPIO24)       // BGPIO14
#define DEVICE_GPIO_DC_INPUT_LEVEL          (GPIO_LOW)

// For Rear-Camera
#define USB_PATH_SELECT_GPIO        (MMP_GPIO61) // CGPIO29 --> USB_PATH
#define USB_PATH_SELECT_SET       (GPIO_HIGH)

//Move to Config_SDK.h
#define POLLING_USB_INIT_INTERVAL           (2)
#define POLLING_VBUS_INTERVAL               (200)//(1000)//(500)//polling VBus interval
#define WAIT_OTG_SESSION_INTERVAL           (50)//(1000)//(500)//after VBus output HIGH, interval before OTG session
#define WAIT_CHECK_BDEVICE_CONN_INTERVAL    (1000)
#define WAIT_BDEVICE_DISCONN_INTERVAL       (100)
#define WAIT_CHECK_BDEVICE_DISCONN_DELAY_CNT    (8)

#define USB_IN_DETECT_VBUS_PIN              (MMP_GPIO_MAX)//B15
#define USB_IN_DETECT_VBUS_PIN_ACTIVE       (GPIO_HIGH)
#define USB_DETECTION_CUSTOM (0) //TBD
#define USB_OUT_PWR_SW_PIN                  (DRV_IO_PM_GPIO2)//(MMP_GPIO18)//B8
#define USB_OUT_PWR_SW_PIN_ACTIVE           (GPIO_HIGH)//(MMP_TRUE)

#if 0
void ____HDMI_TV_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * HDMI/TV Config
 *===========================================================================*/

#define HDMI_ENABLE                 (0)
#define SUPPORT_HDMI                (HDMI_ENABLE)
#define HDMI_PREVIEW_EN             (HDMI_ENABLE & 1)
#define HDMI_MENU_EN                (HDMI_ENABLE & 1)
#define HDMI_PREVIEW                (HDMI_PREVIEW_EN)
#define HDMI_PC_GPIO                (MMP_GPIO23) // BGPIO13 -->> HDMI_PC
#define HDMI_SINGLE_OSD_BUF         (HDMI_ENABLE & 0)

//#define TV_ONLY
#define TVOUT_ENABLE                (defined(TV_ONLY) | 0)
#define SUPPORT_TV                  (TVOUT_ENABLE)
#define TVOUT_PREVIEW_EN            (TVOUT_ENABLE & 1)
#define TV_MENU_EN                  (TVOUT_ENABLE & 1)
#define TVOUT_PREVIEW               (TVOUT_PREVIEW_EN)
#define TV_SINGLE_OSD_BUF           (TVOUT_ENABLE & 1)
#define CFG_TV_MOVPB_BACK_TO_BROWSER //Mantis: 1049398 Device need to return to Browser when TV-OUT playback end

#if TVOUT_ENABLE && !defined(TV_ONLY)
#define TV_OUT_DETECT_GPIO          (MMP_GPIO_MAX)
#define DEVICE_GPIO_TV              (TV_OUT_DETECT_GPIO)
#define TV_CONNECTED_STATE          (GPIO_HIGH)
#endif

#define TV_SPEAKER_OUT_EN
#define SWITCH_TVOUT_BY_KEY         (0)

/*===========================================================================
 * Misc Config
 *===========================================================================*/

#if defined(WIFI_PORT)
#define WIFI_SWITCH_CTRL            (WIFI_BY_KEY)
#endif

#define LED_FLASH_CTRL              (LED_BY_KEY)

#define QUICK_EDIT_BROWSER_FILE     (QUICK_EDIT_WITH_CONFIRM)

#define QUICK_FILE_EDIT_EN          (0)

#define QUICK_FORMAT_SD_EN          (0)

#define CYCLIC_MODE_CHANGE          (1)

#define POWER_OFF_CONFIRM_PAGE_EN   (0)

#define POWER_ON_BUTTON_ACTION      (1)

#define POWER_ON_MENU_SET_EN        (0)

#define DAY_NIGHT_MODE_SWITCH_EN    (0)

#define SHOW_HDMI_DIR_ICON          (0)

#define MOTION_DETECTION_EN         (SUPPORT_MDTC & 1)
#define MDT_REC_ALWAYS_BACKLIGHT_OFF (SUPPORT_MDTC & 1)

#define VMD_ACTION                  (VMD_RECORD_VIDEO)// | VMD_BURST_CAPTURE)
#define MVD_LO_MVTH                 (60) // sensitivity
#define MVD_LO_CNTH                 (10) // size_perct_thd_min
#define MVD_MI_MVTH                 (80) // sensitivity
#define MVD_MI_CNTH                 (10) // size_perct_thd_min
#define MVD_HI_MVTH                 (90) // sensitivity
#define MVD_HI_CNTH                 (5) // size_perct_thd_min

#define AUTO_HIDE_OSD_EN            (0)

/*===========================================================================
 * Global Used Button Config
 *===========================================================================*/

#define KEY_POWER_OFF               (BUTTON_POWER_LPRESS)   // See KeyParser

#define KEY_VIDEO_RECORD            (BUTTON_REC_REL)        // See KeyParser

#define KEY_VIDEO_CAPTURE           (BUTTON_REC_LPRESS)     // See KeyParser

#define KEY_DSC_CAPTURE             (BUTTON_REC_REL)        // See KeyParser

#define KEY_ROTATE_OSD_SNR          (BUTTON_ID_UNKNOWN)

#define POWER_EN_GPIO               (MMP_GPIO_MAX) // PAD_POC_PWR_EN
#define POWER_EN_GPIO_LEVEL         (GPIO_HIGH)

#if 0
void ____LED_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * LED GPIO Config
 *===========================================================================*/

#define LED_GPIO_VIDEO                          (MMP_GPIO_MAX)
#define LED_GPIO_PLAYBACK                       (MMP_GPIO_MAX)
#define LED_GPIO_CAMERA                         (MMP_GPIO_MAX)
#define LED_GPIO_SELF_TIMER                     (MMP_GPIO_MAX)
#define LED_GPIO_AFLED_EN                       (MMP_GPIO_MAX)
#define LED_GPIO_CHARGER                        (MMP_GPIO_MAX)
#define LED_GPIO_POWER                          (MMP_GPIO3) // AGPIO1 -->> PWR_LED
#define LED_GPIO_POWER_ACT_LEVEL                (GPIO_HIGH)
//#define LED_GPIO_WIFI_STATE                     (MMP_GPIO22)  // BGPIO12
//#define LED_GPIO_WIFI_ACT_LEVEL                 (PIO_HIGH)
//#define LED_GPIO_FLASH_LIGHT                    (MMP_GPIO17)    // BGPIO7
//#define LED_GPIO_FLASH_LIGHT_ACT_LEVEL          (GPIO_LOW)

//Lens motor driver
#define AIT_LENS_TYPE_DUMMY                            0
#define AIT_LENS_TYPE_ZM726                            1
#define AIT_LENS_TYPE_ZM751                            2
#define AIT_LENS_TYPE                           AIT_LENS_TYPE_DUMMY
#define ENABLE_MOTOR_DRV_POWER_CTRL             0
#define LENS_MOTOR_DRV_MT_SPI_CLK               (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_SPI_DATA              (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_SPI_CS                (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_POW_EN                (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_RESET                 (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_MOB1                  (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_MOB2                  (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_EXT1                  (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_MT_EXT2                  (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_F_OUT                    (MMP_GPIO_MAX)
#define LENS_MOTOR_DRV_Z_OUT                    (MMP_GPIO_MAX)

#define USE_PWM_AS_MOTOR_OSC                    0
#define LENS_MOTOR_DRV_PWM_CLK                  (MMP_GPIO_MAX) // 1->0
#define LENS_MOTOR_DRV_PWM_UNIT_PIN             (MMP_GPIO_MAX) // UNIT 0
#define USE_PWM_FOR_LCD_BACKLIGHT               0
#define LCD_BACKLIGHT_PWM_UNIT_PIN              (MMP_PWM2_PIN_AGPIO3) // UNIT 2, PAGPIO3 -->> LCD_BL

// Uart
#undef  DEBUG_UART_PAD
#define DEBUG_UART_PAD                          (MMP_UART_PADSET_0)

// Storage path for ISP/Factory info
#define INFO_NAND_FLASH                         (0)
#define INFO_SERIAL_FLASH                       (1)
#define INFO_SD_CARD                            (2)
#define STORAGE_FOR_FACTORY_INFO                (INFO_SERIAL_FLASH)
#define STORAGE_FOR_ISP_INFO                    (INFO_SERIAL_FLASH)

//CHARGER IC
#define ENABLE_CHARGER_IC                       (0)
#define CHARGER_PGOOD_GPIO                      (MMP_GPIO_MAX)   //LOW active
#define CHARGER_CHG_GPIO                        (MMP_GPIO_MAX)   //LOW active
#define CHARGER_EN1_GPIO                        (MMP_GPIO_MAX)
#define CHARGER_EN2_GPIO                        (MMP_GPIO_MAX)
#define CHARGER_ENABLE_GPIO                     (MMP_GPIO_MAX)    //Output mode, High active
#define CHARGER_TEMP_CTL                        (MMP_GPIO_MAX)    //Output mode
#define CHARGER_STATUS                          (MMP_GPIO_MAX)    //Input mode
#define CHARGER_STATUS_ACT_LEVEL                (GPIO_LOW)

//Strobe
#define STROBE_CHG_RDY_GPIO                     (MMP_GPIO_MAX)
#define STROBE_TRIG_GPIO                        (MMP_GPIO_MAX)
#define STROBE_CHG_GPIO                         (MMP_GPIO_MAX)

#undef  BIND_MOTOR_R2A30440NP
#undef  BIND_MOTOR_R2A30423NP
#undef  BIND_MOTOR_DUMMY
#undef  MOTOR_PI_INVERT

#define BIND_MOTOR_R2A30440NP                   0
#define BIND_MOTOR_R2A30423NP                   0
#define MOTOR_PI_INVERT                         0
#define BIND_MOTOR_DUMMY                        1

#define ADC_SETTINGS_FOR_EP2                    1

#define POWER_KEY_DETECT_ADC                    (0)
#define POWER_KEY_DETECT_GPIO                   (1)
#define POWER_KEY_DETECTION                     (POWER_KEY_DETECT_GPIO)
#define POWER_OFF_PREPROCESS_EN                 (1)
#define POWER_OFF_WHEN_SD_REMOVE                (0)

//Sys Calibration
#define SUPPORT_SYS_CALIBRATION                 (0)
#define SYS_CALIBRATION_SIF_SAVE_EN             (0)

// Touch Panel list
#define TOUCH_PANEL_DUMMY                       (1)
#define TOUCH_PANEL_ZT2003                      (2)
#define TOUCH_PANEL_MSG213X                     (3)
#define TOUCH_PANEL_TSC2007                     (4)
#define TOUCH_PANEL_TSC2046                     (5)
#define TOUCH_PANEL_FT6X36                      (6)
#define TOUCH_PANEL_GT911                       (7)
//Touch Panel
#define SUPPORT_TOUCH_PANEL                     (0)
#define STYLE001_SUPPORT_TOUCH_PANEL            (0)
#define TOUCH_UART_FUNC_EN                      (0)
#define SUPPORT_TOUCH_KEY                       (1)

#define TOUCH_PANEL_DIR_0                       (0)
#define TOUCH_PANEL_DIR_1                       (1)
#define TOUCH_PANEL_DIR_2                       (2)
#define TOUCH_PANEL_DIR_3                       (3)

#if (SUPPORT_TOUCH_PANEL == 1)
#define TOUCH_IC_PLACEMENT_TYPE                 (TOUCH_PANEL_DIR_0)
#define DSC_TOUCH_PANEL                         (TOUCH_PANEL_ZT2003)
#endif
#define TOUCH_PANEL_INT_GPIO                    (DRV_IO_PM_GPIO5)//(MMP_GPIO52)


//Operation
#define VIDEO_CAMERA_DZOOM_SYNC                 (0)

#if 0
void ____ADC_Key_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * ADC Key Voltage Setting
 *===========================================================================*/
#define KEY_LCD_SENSOR_V17  (0)
#define KEY_LCD_SENSOR_V18  (1)

#define KEY_BOARD_IS     KEY_LCD_SENSOR_V17
/*
Note: If we don't want some key to be detected,
      we could just set the ADC_STATE_ID_XX to be "ADCPRESS_NONE"
      then the timer function will discard this key.
*/
#define ADC_KEY_EN                  (1)
#define MORE_ADC_KEY                (1)

#if 0 // EROY TEST
#define ADC_KEY_SARADC_CHANNEL      (1)
#define ADC_KEY_BOARD_TYPE          (1) //[0/1:V16/V17]

#define ADC_KEY_VOLT_U              (ADC_KEY_BOARD_TYPE)? (3284):(0)
#define ADC_KEY_VOLT_D              (ADC_KEY_BOARD_TYPE)? (1368):(2183)
#define ADC_KEY_VOLT_L              (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_R              (ADC_KEY_VOLT_DEFAULT)

#define ADC_KEY_VOLT_ENTER          (ADC_KEY_VOLT_DEFAULT)
#if (MORE_ADC_KEY==1)
#define ADC_KEY_VOLT_REC            (ADC_KEY_BOARD_TYPE)? (2810):(1083)
#define ADC_KEY_VOLT_MENU           (ADC_KEY_BOARD_TYPE)? (1877):(1961)
#define ADC_KEY_VOLT_PLAY           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_MODE           (ADC_KEY_BOARD_TYPE)? (2307):(1629)
#define ADC_KEY_VOLT_FUNC1          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_FUNC2          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_FUNC3          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_WIDE           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_TELE           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_SOS            (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_MUTE           (ADC_KEY_BOARD_TYPE)? (935):(935)
#define ADC_KEY_VOLT_CAPTURE        (ADC_KEY_VOLT_DEFAULT)
#endif

#define ADC_STATE_ID_U              (ADCPRESS_U)
#define ADC_STATE_ID_D              (ADCPRESS_D)
#define ADC_STATE_ID_L              (ADCPRESS_NONE)
#define ADC_STATE_ID_R              (ADCPRESS_NONE)
#define ADC_STATE_ID_ENTER          (ADCPRESS_NONE)
#if (MORE_ADC_KEY==1)
#define ADC_STATE_ID_REC            (ADCPRESS_REC) //(ADCPRESS_REC)
#define ADC_STATE_ID_MENU           (ADCPRESS_MENU)
#define ADC_STATE_ID_PLAY           (ADCPRESS_NONE)
#define ADC_STATE_ID_MODE           (ADCPRESS_MODE)
#define ADC_STATE_ID_FUNC1          (ADCPRESS_NONE)
#define ADC_STATE_ID_FUNC2          (ADCPRESS_NONE)
#define ADC_STATE_ID_FUNC3          (ADCPRESS_NONE)
#define ADC_STATE_ID_WIDE           (ADCPRESS_NONE)
#define ADC_STATE_ID_TELE           (ADCPRESS_NONE)
#define ADC_STATE_ID_SHUTTER        (ADCPRESS_NONE)
#define ADC_STATE_ID_SET            (ADCPRESS_NONE)
#define ADC_STATE_ID_SOS            (ADCPRESS_NONE)
#define ADC_STATE_ID_MUTE           (ADCPRESS_MUTE)
#define ADC_STATE_ID_CAPTURE        (ADCPRESS_NONE)
#endif

#define ADC_KEY_VOLT_MARGIN         (ADC_KEY_BOARD_TYPE)? (25):(100)
#define ADC_KEY_VOLT_MARGIN_REC     (25)

#define ADC_KEY_LONG_PRESS_CNT      (4)

#define ADC_REFERENCE_VOLTAGE       (3300)
#else/////////////////////////////////////////
#define ADC_KEY_SARADC_CHANNEL      (0)

#define ADC_KEY_VOLT_U              (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_D              (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_L              (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_R              (ADC_KEY_VOLT_DEFAULT)

#define ADC_KEY_VOLT_ENTER          (ADC_KEY_VOLT_DEFAULT)
#if (MORE_ADC_KEY==1)
#define ADC_KEY_VOLT_REC            (ADC_KEY_VOLT_DEFAULT)//(2730)
#define ADC_KEY_VOLT_MENU           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_PLAY           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_MODE           (ADC_KEY_VOLT_DEFAULT)  //(3130)//(1100)//(2312)
#define ADC_KEY_VOLT_FUNC1          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_FUNC2          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_FUNC3          (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_WIDE           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_TELE           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_SOS            (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_MUTE           (ADC_KEY_VOLT_DEFAULT)
#define ADC_KEY_VOLT_CAPTURE        (ADC_KEY_VOLT_DEFAULT)
#endif

#define ADC_STATE_ID_U              (ADCPRESS_U)
#define ADC_STATE_ID_D              (ADCPRESS_D)
#define ADC_STATE_ID_L              (ADCPRESS_NONE)
#define ADC_STATE_ID_R              (ADCPRESS_NONE)
#define ADC_STATE_ID_ENTER          (ADCPRESS_NONE)
#if (MORE_ADC_KEY==1)
#define ADC_STATE_ID_REC            (ADCPRESS_REC) //(ADCPRESS_REC)
#define ADC_STATE_ID_MENU           (ADCPRESS_MENU)
#define ADC_STATE_ID_PLAY           (ADCPRESS_NONE)
#define ADC_STATE_ID_MODE           (ADCPRESS_MODE)
#define ADC_STATE_ID_FUNC1          (ADCPRESS_NONE)
#define ADC_STATE_ID_FUNC2          (ADCPRESS_NONE)
#define ADC_STATE_ID_FUNC3          (ADCPRESS_NONE)
#define ADC_STATE_ID_WIDE           (ADCPRESS_NONE)
#define ADC_STATE_ID_TELE           (ADCPRESS_NONE)
#define ADC_STATE_ID_SHUTTER        (ADCPRESS_NONE)
#define ADC_STATE_ID_SET            (ADCPRESS_NONE)
#define ADC_STATE_ID_SOS            (ADCPRESS_NONE)
#define ADC_STATE_ID_MUTE           (ADCPRESS_MUTE)
#define ADC_STATE_ID_CAPTURE        (ADCPRESS_NONE)
#endif

#define ADC_KEY_VOLT_MARGIN         (32)
#define ADC_KEY_VOLT_MARGIN_REC     (32)

#define ADC_KEY_LONG_PRESS_CNT      (4)

#define ADC_REFERENCE_VOLTAGE       (3300)
#endif

#if 0
void ____GPIO_Key_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * Button/Device GPIO Setting
 *===========================================================================*/

/*
Note: If we don't want some key to be detected,
      we could just set the KEY_GPIO_XX to be "MMP_GPIO_MAX" or "MMP_GPIO_MAX"
      then the timer function will discard this key.
*/
#define MORE_GPIO_KEY               (0)

#define POWER_KEY_LONG_PRESS_CNT    (6)
#define OTHER_KEY_LONG_PRESS_CNT    (6)

#define KEY_GPIO_REC                (MMP_GPIO_MAX)//(MMP_GPIO84)    // MIPI_RX1_CKP     -->> OK_KEY
#define KEY_GPIO_MENU               (MMP_GPIO_MAX)//(MMP_GPIO101)   // PI2S_SD0     -->> MENU_KEY
#define KEY_GPIO_PLAY               (MMP_GPIO_MAX)
#define KEY_GPIO_MODE               (MMP_GPIO_MAX)//(MMP_GPIO81)    // MIPI_RX1_DA2P    -->> B_KKEY
#define KEY_GPIO_POWER              (MMP_GPIO_MAX)//(MMP_GPIO_MAX)  // CGPIO8           ---> PWR_KEY_IN
#define KEY_GPIO_CIRCLE             (MMP_GPIO_MAX)
#if (MORE_GPIO_KEY == 1)
#define KEY_GPIO_UP                 (MMP_GPIO_MAX)  // MIPI_RX1_DA1P    -->> UP_KEY
#define KEY_GPIO_DOWN               (MMP_GPIO_MAX)  // MIPI_RX1_DA1N    -->> DOWN_KEY
#define KEY_GPIO_LEFT               (MMP_GPIO_MAX)
#define KEY_GPIO_RIGHT              (MMP_GPIO_MAX)
#define KEY_GPIO_OK                 (MMP_GPIO_MAX)
#define KEY_GPIO_FUNC1              (MMP_GPIO_MAX)  //pip SW
#define KEY_GPIO_FUNC2              (MMP_GPIO_MAX)
#define KEY_GPIO_FUNC3              (MMP_GPIO_MAX)
#define KEY_GPIO_SOS                (MMP_GPIO_MAX)
#define KEY_GPIO_MUTE               (MMP_GPIO_MAX)  // MIPI_RX1_DA2N    -->> A_KEY
#define KEY_GPIO_CAPTURE            (MMP_GPIO_MAX)
#endif

// Key pad detect method
#define KEYPAD_DETECT_TASK          (1)
#define RMT_CTL_DISABLE             (0)
#define RMT_CTL_CANSONIC_89         (1)///< change USB_ADAPTER_GPIO from 69 to 63

//USB DC detection
#define DC_IN_STATUS_REG            (22)
#define V_BUS_STATUS_REG            (23)

//USB DC detection
#define DEVICE_GPIO_LCD_COV         (MMP_GPIO_MAX)
#define DEVICE_GPIO_LCD_INV         (MMP_GPIO_MAX)
#if GSENSOR_CONNECT_ENABLE
#define DEVICE_GPIO_GSENSOR_INIT    (MMP_GPIO_MAX)
#endif

#define TOUCH_RESET_GPIO            (DRV_IO_PM_GPIO4)//(MMP_GPIO_MAX)
#define TOUCH_RESET_GPIO_ACT_MODE   (GPIO_HIGH)

#define SENSOR_EN_GPIO              (MMP_GPIO_MAX)
#define SENSOR_EN_GPIO_ACT_MODE     (GPIO_HIGH)

#define KEY_PRESSLEVEL_REC          LEVEL_LOW
#define KEY_PRESSLEVEL_MENU         LEVEL_HIGH
#define KEY_PRESSLEVEL_PLAY         LEVEL_HIGH
#define KEY_PRESSLEVEL_MODE         LEVEL_HIGH
#define KEY_PRESSLEVEL_POWER        LEVEL_LOW

#define KEY_PRESSLEVEL_UP           LEVEL_LOW
#define KEY_PRESSLEVEL_DOWN         LEVEL_LOW
#define KEY_PRESSLEVEL_LEFT         LEVEL_HIGH
#define KEY_PRESSLEVEL_RIGHT        LEVEL_HIGH
#define KEY_PRESSLEVEL_OK           LEVEL_HIGH
#define KEY_PRESSLEVEL_SOS          LEVEL_HIGH
#define KEY_PRESSLEVEL_MUTE         LEVEL_HIGH
#define KEY_PRESSLEVEL_CAPTURE      LEVEL_HIGH
#define KEY_PRESSLEVEL_FUNC1        LEVEL_HIGH
#define KEY_PRESSLEVEL_FUNC2        LEVEL_HIGH
#define KEY_PRESSLEVEL_FUNC3        LEVEL_HIGH

#define KEY_PRESSLEVEL_TOUCH        LEVEL_LOW

#define KEY_LPRESS_TIME_REC         (200)
#define KEY_LPRESS_TIME_MENU        (200)
#define KEY_LPRESS_TIME_PLAY        (200)
#define KEY_LPRESS_TIME_MODE        (200)
#define KEY_LPRESS_TIME_POWER       (200)

#define KEY_LPRESS_TIME_UP          (200)
#define KEY_LPRESS_TIME_DOWN        (200)
#define KEY_LPRESS_TIME_LEFT        (200)
#define KEY_LPRESS_TIME_RIGHT       (200)
#define KEY_LPRESS_TIME_OK          (200)
#define KEY_LPRESS_TIME_SOS         (200)
#define KEY_LPRESS_TIME_MUTE        (200)
#define KEY_LPRESS_TIME_CAPTURE     (200)
#define KEY_LPRESS_TIME_FUNC1       (200)
#define KEY_LPRESS_TIME_FUNC2       (200)
#define KEY_LPRESS_TIME_FUNC3       (200)

/*===========================================================================
 * Battery Measure Config
 *===========================================================================*/

#ifdef FAT_BOOT
#define BATTERY_DETECTION_EN            (0)
#else
#define BATTERY_DETECTION_EN            (0)
#endif

#define BATTERY_LOW_BOOT_VOLT           (3600)
#define BATTERY_VOLTAGE_OFFSET          (110)
#define BATT_FULL_LEVEL                 (3782)
#define BATT_LEVEL_2                    (3618)
#define BATT_LEVEL_1                    (3536)
#define BATT_LEVEL_0                    (3450)

// ADC value = VBAT * REAL_BAT_VOLTAGE_RATIO_N / REAL_BAT_VOLTAGE_RATIO_M, mV
// Dependon PCBA
#define REAL_BAT_VOLTAGE_RATIO_N        (5)
#define REAL_BAT_VOLTAGE_RATIO_M        (54)

#define BATT_LEVEL_LOW                  (BATT_LEVEL_0)
#define POWER_ON_BATTERY_DETECTION      (BATTERY_DETECTION_EN & 1)      // For MBOOT Only
#define BATTERY_DETECT_ADC_CHANNEL      (3)     // 0: SARADC0, ...

#define BATTERY_LOW_WARNNING_TIME       (3)
#define BATTERY_DETECT_PERIOD           (35)

#define POWER_ON_BATTERY_OFFSET         (BATTERY_VOLTAGE_OFFSET)
#define POWER_ON_LOW_BATTERY_VOLTAGE    (BATTERY_LOW_BOOT_VOLT)

#if 0
void ____UI_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 * UI related Config
 *===========================================================================*/
#define SWITCH_MODE_FREEZE_WIN          (0)


#define UI_MENU_AUTO_VANISH             (0)
#define UI_MENU_SD_INIT_WARNING_CLOCK   (1)

//Cover (open,close) flow
#define COVER_CLOSE_POWER_OFF       (0)
#define COVER_CLOSE_BACKLIGHT_OFF   (1)
#define COVER_CLOSE_FLOW            (COVER_CLOSE_POWER_OFF)

#define ENABLE_DETECT_FLOW          (0)

//Key Flow
#define MAIN_SUB_SWITCH              (0)
#define EV_ADJUST_PLUS               (1)
#define EV_ADJUST_MINUS              (2)
#define LCD_BACKLIGHT_SWITCH         (3)
#define AF_LED_SWITCH                (4)
#define SELF_TIMER_SWITCH            (5)
#define INFORMATION_SWITCH           (6)
#define AF_MODE_SWITCH               (7)
#define KEY_FLOW_VR_L                (EV_ADJUST_MINUS)
#define KEY_FLOW_VR_R                (EV_ADJUST_PLUS)
#define KEY_FLOW_VR_U                (INFORMATION_SWITCH)
#define KEY_FLOW_CAMERA_L            (EV_ADJUST_MINUS)
#define KEY_FLOW_CAMERA_R            (EV_ADJUST_PLUS)
#define KEY_FLOW_CAMERA_U            (INFORMATION_SWITCH)
#define KEY_FLOW_CAMERA_D            (AF_MODE_SWITCH)

#define SWITCH_GPSINFO_BY_MENU_VR    (0)
//Exif
#define EXIF_ENABLE_MAKER_INFO              (1)
#if (EXIF_ENABLE_MAKER_INFO == 1)
    #define AHC_EXIF_DEFAULT_MAKER          "AIT Corp."
    #define AHC_EXIF_DEFAULT_MODEL          "AIT CarDV SDK"
    #define AHC_EXIF_DEFAULT_SOFTWARE       "AIT CarDV SDK"
    #define AHC_EXIF_DEFAULT_ARTIST         "AIT CarDV SDK"
    #define AHC_EXIF_DEFAULT_COPYRIGHT      "AIT Corp."
#endif

//UI OSD Draw Icon
#define DRAW_EV_MAIN_PAGE_ENABLE        (1)

//Menu Setting
#define MENU_STYLE                      (0)
#define MENU_AUDIO_DEFAULT_LOUD         (0)

//Capture Related
#define ENABLE_CAPTURE_STABILIZER       (0)
#define ENABLE_CAPTURE_WAIT_ICON        (0)
#define ENABLE_AUTO_LOCKFILE_JPG        (0)
#define ENABLE_LED_FOR_SELF_TIMER       (0)
#define ENABLE_SOUND_FOCUS              (0)
#define ENABLE_VIDEO_STILLCAPTURE_VIDEO (1)
#define CAPTURE_TIMES_WHILE_TURN_ON     (0) //UNIT: Frame
#define JPEG_INTO_AVI_WHILE_TURN_ON     (0)
#define PIR_CAPTURE_TIMES_WHILE_TURN_ON (0) //UNIT: Frame
#define PIR_JPEG_INTO_AVI_WHILE_TURN_ON (0)
#define FHD_REPLACE_2M                  (1)

//Video Related
#define ENABLE_VR_WHILE_TURN_ON         (1)
#define ENABLE_VR_ONLY_WHILE_TURN_ON    (0)
#define VR_TIME_WHILE_TURN_ON           (0) //UNIT:Sec
#define ENABLE_VIDEO_LED_ON_WHILE_VR    (0)
#define VIDEO_REC_WITH_MUTE_EN          (1)
#define ENABLE_LED_FOR_VR_STATUS        (0)
#define VR_LED_BLINK                    (1)
#define VR_LED_EVENT_BLINK              (0)
#define RECORD_TIME_CUMULATIVE          (0)
#define STICKER_DRAW_EDGE               (0)

#define SW_STICKER_EN                   (0)
#define VR_FLICK_UI_CIRCLE              (0)
#define SETTING_VR_VOLUME_EVERYTIME     (1)

//PIR
#define ENABLE_PIR_MODE                 (0)
#define PIR_POWEROFF_LCD_BACKLIGHT      (0)
#define DEVICE_GPIO_PIR_EN              (MMP_GPIO_MAX)
#define DEVICE_GPIO_PIR_INT             (MMP_GPIO_MAX)

//Edit Delete/Protect support Dir select
#define EDIT_PATH_SELECT                (0)
#define EDIT_FILE_ONLY_LCD_OUTPUT       (0)

//SD Info: Only show current setting
#define SDINFO_ONLY_CURRENT_SETTING     (0)

//UVC
//#define SUPPORT_AUTO_FOCUS                (0)
#define PCAM_UVC_MIX_MODE_ENABLE     (0) // Pcam Mix Mode ... UVC function work under Video/DSC mode

//Sound Effect Setting
#define SOUND_EFFECT_SPECIAL_ENABLE     (0)

//Normal Power off
#define POWER_OFF_DELAY_TIME_DEFAULT    (10)  //Sec.

//Virtual Power Off
#define SUPPORT_VIRTUAL_POWER_OFF       (0)

//ESD Recorver
#define SUPPORT_ESD_RECOVER_VR          (0)
#define SUPPORT_ESD_RECOVER_MOVIEPB     (0)

#define UPDATE_UI_USE_MULTI_TASK        (1)

/*===========================================================================
 *  PROJECT ID
 *===========================================================================*/
#define CUSTOMER_NAME                   "CarDV SDK"
#define CUS_CFG_UVC_OSD_TEXT            CUSTOMER_NAME
#define CUSTOMER_NAME_MAX_LENGTH        (18)

#define DST_TIMEZONE                    (0xFF)

/*===========================================================================
 * EXIF
 *===========================================================================*/

/* Maximum length is 31, refer EF_MAKER_LEN and EF_MODEL_LEN */
#define EXIF_MAKER                  " "
#define EXIF_MODEL                  " "

/*===========================================================================
 *
 *===========================================================================*/

#define HARDWARE_PLATFORM           0xFF
//#define CFG_BOOT_BYPASS_CLOCK_CHECK
//#define CFG_POWER_ON_ENTER_BROSWER_STATE
//#define MSDC_OUT_NOT_OFF
//#define PCCAM_OUT_NOT_OFF

#define FW_DCF_BACKGROUND           (0)
//#define CFG_BOOT_LCD_ALWAYS_REC_BY_CHARGER_IN
//#define CFG_BOOT_SKIP_POWER_ON_IMG

/*===========================================================================
 *
 *===========================================================================*/
#ifdef  USE_WAV_AS_SOUND_FILE
#define CFG_CUS_SOUNDEFFECT_BUTTON      "Button.wav"
#define CFG_CUS_SOUNDEFFECT_POWERON     "Power_On.wav"
#define CFG_CUS_SOUNDEFFECT_POWEROFF    "Power_Off.wav"
#define CFG_CUS_SOUNDEFFECT_SHUTTER     "Shutter.wav"
#define CFG_CUS_SOUNDEFFECT_FCWS        "FCWS_Warning.wav"
#define CFG_CUS_SOUNDEFFECT_FINDME      "findme.wav"
#define CFG_CUS_SOUNDEFFECT_LDWS        "LDWS_Warning.wav"

#else
#define CFG_CUS_SOUNDEFFECT_BUTTON      "Button.mp3"
#define CFG_CUS_SOUNDEFFECT_POWERON     "Power_On.mp3"
#define CFG_CUS_SOUNDEFFECT_POWEROFF    "Power_Off.mp3"
#define CFG_CUS_SOUNDEFFECT_SHUTTER     "Shutter.mp3"
#define CFG_CUS_SOUNDEFFECT_FCWS        "FCWS_Warning.mp3"
#define CFG_CUS_SOUNDEFFECT_FINDME      "findme.mp3"
#define CFG_CUS_SOUNDEFFECT_LDWS        "LDWS_Warning.mp3"

#endif

/*===========================================================================
 *  Net Application setting
 *===========================================================================*/
 #define NET_SYNC_PLAYBACK_MODE

#if 0
void ____Task_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  AHC task setting
 *===========================================================================*/
#if defined(__RTK_OS__)

#define OC_RTK_CUS_LOWEST_PRIO           (0)
#define OC_RTK_CUS_HIGHEST_PRIO          (199) //


#define TASK_NETWORK_BRUST_PRIO       (OC_RTK_CUS_HIGHEST_PRIO - 1)         //(198)

#define TASK_WIFI_INTERNAL_PRIO_START (OC_RTK_CUS_HIGHEST_PRIO - 2)         //(197)
#define TASK_WIFI_INTERNAL_PRIO_END   (OC_RTK_CUS_HIGHEST_PRIO - 11)        //(188)

#define TASK_NET_INTERNAL_PRIO_START  (TASK_WIFI_INTERNAL_PRIO_END - 1)     //(187)
#define TASK_NET_INTERNAL_PRIO_END    (TASK_WIFI_INTERNAL_PRIO_END - 20)    //(168)

#define TASK_MID_WORK_PRIO            (TASK_NET_INTERNAL_PRIO_END - 1)      //(167)
#define TASK_KEYPAD_PRIO              (TASK_MID_WORK_PRIO - 1)              //(166)

#define TASK_REALIDKEYPAD_PRIO        (TASK_KEYPAD_PRIO - 1)                //(165)

#define TASK_MOTOR_CTRL_PRIO          (TASK_REALIDKEYPAD_PRIO - 1)          //(164)

#define TASK_UART_CTRL_PRIO           (TASK_MOTOR_CTRL_PRIO - 1)            //(163)

#if (FW_DCF_BACKGROUND == 1)
#define DCF_DB_MUTEX_PRIO             (TASK_UART_CTRL_PRIO - 1)             //(162)
#else
#define DCF_DB_MUTEX_PRIO             (TASK_UART_CTRL_PRIO)                 //(163)
#endif

#if (FW_DCF_BACKGROUND == 1)
#define DCF_CYCLIC_MUTEX_PRIO         (DCF_DB_MUTEX_PRIO - 1)               //(161)
#else
#define DCF_CYCLIC_MUTEX_PRIO         (DCF_DB_MUTEX_PRIO)                   //(163)
#endif

#define TASK_AHC_DCF_PRIO             (DCF_CYCLIC_MUTEX_PRIO - 1)           //(160)

#define TASK_NETWORK_PRIO             (TASK_AHC_DCF_PRIO - 1)               //(159)

#define TASK_AHC_PRIO                 (TASK_NETWORK_PRIO - 1)               //(158)

#define TASK_AHC_WORK_PRIO            (TASK_AHC_PRIO - 1)                   //(157)

#define TASK_AHC_WORK2_PRIO           (TASK_AHC_WORK_PRIO - 1)              //(156)

#if (VIDEO_BGPARSER_EN == 1)
#define TASK_BG_PARSER_PRIO           (TASK_AHC_WORK2_PRIO - 1)             //(155)
extern OS_STK  BG_PARSER_Task_Stk[];
#else
#define TASK_BG_PARSER_PRIO           (TASK_AHC_WORK2_PRIO)                 //(156)
#endif

#define TASK_JOB_DISPATCH_PRIO        (TASK_BG_PARSER_PRIO - 1)             //(155)

#define TASK_UART_LOG_TX_PRIO        (TASK_JOB_DISPATCH_PRIO - 1)           //(154)

#define TASK_FDTC_PRIO                (TASK_UART_LOG_TX_PRIO - 1)           //(153)

#define TASK_LOW_WORK_PRIO            (OC_RTK_CUS_LOWEST_PRIO + 5)          //(5)

#else
#define TASK_WIFI_INTERNAL_PRIO_START (37)
#define TASK_WIFI_INTERNAL_PRIO_END (52)

#define TASK_STREAMING_PRIO            (12) //Wifi //Andy Liu TBD

#define TASK_NETWORK_BRUST_PRIO      (TASK_AHC_INIT_PRIO + 1)

#if (TASK_NETWORK_BRUST_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_NETWORK_BRUST_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_NETWORK_BRUST_PRIO
#define TASK_NETWORK_BRUST_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_KEYPAD_PRIO             (TASK_NETWORK_BRUST_PRIO + 1) //(28)
#if (TASK_KEYPAD_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_KEYPAD_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_KEYPAD_PRIO
#define TASK_KEYPAD_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#if ( KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK )
#define TASK_REALIDKEYPAD_PRIO       (TASK_KEYPAD_PRIO + 1) //(29)
#else
#define TASK_REALIDKEYPAD_PRIO       (TASK_KEYPAD_PRIO) //(29)
#endif
#if (TASK_REALIDKEYPAD_PRIO >= TASK_WIFI_INTERNAL_PRIO_START)\
    && (TASK_REALIDKEYPAD_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_REALIDKEYPAD_PRIO
#define TASK_REALIDKEYPAD_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_MOTOR_CTRL_PRIO         (TASK_REALIDKEYPAD_PRIO + 1) //(30)
#if (TASK_MOTOR_CTRL_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_MOTOR_CTRL_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_MOTOR_CTRL_PRIO
#define TASK_MOTOR_CTRL_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_UART_CTRL_PRIO           (TASK_MOTOR_CTRL_PRIO + 1) //(31)

#if (TASK_UART_CTRL_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_UART_CTRL_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_UART_CTRL_PRIO
#define TASK_UART_CTRL_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#if (FW_DCF_BACKGROUND == 1)
#define DCF_DB_MUTEX_PRIO            (TASK_UART_CTRL_PRIO + 1) //(32)
#else
#define DCF_DB_MUTEX_PRIO            (TASK_UART_CTRL_PRIO) //(32)
#endif
#if (DCF_DB_MUTEX_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (DCF_DB_MUTEX_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef DCF_DB_MUTEX_PRIO
#define DCF_DB_MUTEX_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#if (FW_DCF_BACKGROUND == 1)
#define DCF_CYCLIC_MUTEX_PRIO      (DCF_DB_MUTEX_PRIO + 1) //  (33)
#else
#define DCF_CYCLIC_MUTEX_PRIO      (DCF_DB_MUTEX_PRIO) //  (33)
#endif
#if (DCF_CYCLIC_MUTEX_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (DCF_CYCLIC_MUTEX_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef DCF_CYCLIC_MUTEX_PRIO
#define DCF_CYCLIC_MUTEX_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#if (FW_DCF_BACKGROUND == 1)
#define TASK_AHC_DCF_PRIO            (DCF_CYCLIC_MUTEX_PRIO + 1) //(37)
#else
#define TASK_AHC_DCF_PRIO            (DCF_CYCLIC_MUTEX_PRIO)//(37)
#endif
#if (TASK_AHC_DCF_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_AHC_DCF_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_AHC_DCF_PRIO
#define TASK_AHC_DCF_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_NETWORK_PRIO            (TASK_AHC_DCF_PRIO+1) //(54) //Wifi
#if (TASK_NETWORK_PRIO <= TASK_WIFI_INTERNAL_PRIO_END) //Network task is lower than internal Wifi task.
#undef TASK_NETWORK_PRIO
#define TASK_NETWORK_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_AHC_PRIO                (TASK_NETWORK_PRIO + 1) //(55)
#if (TASK_AHC_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_AHC_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_AHC_PRIO
#define TASK_AHC_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_AHC_WORK_PRIO           (TASK_AHC_PRIO + 1)//(56)
#if (TASK_AHC_WORK_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_AHC_WORK_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_AHC_WORK_PRIO
#define TASK_AHC_WORK_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#define TASK_AHC_WORK2_PRIO          (TASK_AHC_WORK_PRIO + 1)//(57)
#if (TASK_AHC_WORK2_PRIO >= TASK_WIFI_INTERNAL_PRIO_START) \
    && (TASK_AHC_WORK2_PRIO <= TASK_WIFI_INTERNAL_PRIO_END)
#undef TASK_AHC_WORK2_PRIO
#define TASK_AHC_WORK2_PRIO (TASK_WIFI_INTERNAL_PRIO_END + 1)
#endif

#endif

#define TASK_MID_WORK_STK_SIZE       (1024)
#define TASK_LOW_WORK_STK_SIZE       (1024)
#define TASK_KEYPAD_STK_SIZE         (2048)
#define TASK_MOTOR_STK_SIZE          (2048)
//#define TASK_AHC_STK_SIZE            (2048)
#define TASK_AHC_RTC_UPDATE_SIZE     (2048)
#define TASK_AHC_WORK_STK_SIZE       (2048)
#define TASK_UART_LOG_STK_SIZE       (1024)
#define TASK_JOB_DISPATCH_STK_SIZE   (8192)

#if (FW_DCF_BACKGROUND == 1)
#define TASK_AHC_DCF_STK_SIZE        (2048)
#endif

#if (KEYPAD_DETECT_METHOD == KEYPAD_DETECT_TASK)
#define TASK_REALIDKEYPAD_STK_SIZE   (2048)
#endif

#define TASK_UARTCRTL_STK_SIZE       (2048)


//Wifi
#define TASK_NETWORK_STK_SIZE        (2048)

//MDTC/ADAS
#define TASK_FDTC_STK_SIZE           (2048)

#if 0
void ____IQ_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  IQ setting
 *===========================================================================*/
#if 0
#define CUS_AE_BIAS_TBL             "Dvr_CarDV_SDK/IQ/CUS_AE_BIAS_TBL_OV4689_F20.h"
#define CUS_ISP_8428_IQ_DATA        "Dvr_CarDV_SDK/IQ/isp_8428_iq_data_v2_OV4689_v1_F20.xls.ciq.txt"

#define CUS_LCD_BRIGHTNESS          80
#define CUS_LCD_CONTRAST            75
#endif

/*===========================================================================
 *
 *===========================================================================*/
extern void CUS_VideoProtectProcess(void);
#define CFG_CUS_VIDEO_PROTECT_PROC    CUS_VideoProtectProcess

//extern void PMUCtrl_Power_Gpio_En(MMP_BOOL bGPIOEnable);
//#define CFG_CUS_EXCEPTION_POWER_OFF()   {PMUCtrl_Power_Gpio_En(MMP_FALSE);}

#if 0
void ____ADAS_Config____(){ruturn;} //dummy
#endif

/*===========================================================================
 *  ADAS setting
 *===========================================================================*/

#define ENABLE_ADAS_LDWS  (SUPPORT_ADAS_LDWS & 1)
#define ENABLE_ADAS_FCWS  (SUPPORT_ADAS_FCWS & 1)
#define ENABLE_ADAS_SAG   (SUPPORT_ADAS_SAG  & 1)

#endif // __CONFIG_SDK_SDK_EVB_C_TVDEC__
