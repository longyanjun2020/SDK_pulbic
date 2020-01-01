/**
*
* @file    mmi_tvsrv_def.h
*
* @brief   This file defines the mmi to call esl tv driver.
*
* @author  Sho Ding
* @version $Id: mmi_tvsrv_def.h
*
*/
#ifndef __MMI_TVSRV_DEF_H_
#define __MMI_TVSRV_DEF_H_

#include "mmi_mae_common_def.h"
#include "mmi_class.h"
#include "mmi_mediasrv_common.h"

#define TVSRV_STORED_PATH_LEN 100

#define TVSRV_CHANNEL_NAME_LEN  24

#define TVSRV_EVT_PLAY_SHUTTER_SOUND_IND (CLSID_TVSRV << 16 | 1)
#define TVSRV_EVT_CAPTURE_STOP_IND (CLSID_TVSRV << 16 | 2)
#define TVSRV_EVT_CAPTURE_ERROR_IND (CLSID_TVSRV << 16 | 3)
#define TVSRV_EVT_PREEMPT_NOTIFY (CLSID_TVSRV << 16 | 4)
#define TVSRV_EVT_RESUME_NOTIFY (CLSID_TVSRV << 16 | 5)
#define TVSRV_EVT_SUSPEND_NOTIFY (CLSID_TVSRV << 16 | 6)
#define TVSRV_EVT_ESG_IND (CLSID_TVSRV << 16 | 7)
#define TVSRV_EVT_INFO_UPDATE_IND (CLSID_TVSRV << 16 | 8)
#define TVSRV_EVT_BROADCAST_IND (CLSID_TVSRV << 16 | 9)
#define TVSRV_EVT_EM_DATA_IND (CLSID_TVSRV << 16 | 10)
#define TVSRV_EVT_SWITCH_CHANNEL_COMPLETE_IND (CLSID_TVSRV << 16 | 11)
#define TVSRV_EVT_SCAN_COMPLETE_IND (CLSID_TVSRV << 16 | 12)
#define TVSRV_EVT_SCAN_FAIL_IND (CLSID_TVSRV << 16 | 13)
#define TVSRV_EVT_SET_FREQ_COMPLETE_IND (CLSID_TVSRV << 16 | 14)
#define TVSRV_EVT_SET_FREQ_FAIL_IND (CLSID_TVSRV << 16 | 15)

/**
*  @brief The enumeration defines the mode of tv snapshot.
*/
typedef enum
{
    TVSRV_TV__SINGLE
   ,/**< Tv single shot mode */
    TVSRV_TV__CONSSINGLE
   ,/**< Tv continuous shot mode */
    TVSRV_TV__SINGLE_DTV
    /**< Tv single shot mode and no shutter sound */
} TvSrvShotMode_e;

typedef enum
{
    TVSRV_TV_CAPTURE_SOUND__OFF = 0
   ,TVSRV_TV_CAPTURE_SOUND__ON
} TvSrvShutterSound_e;

/**
*  @brief The enumeration defines TV nations' region.
*/
typedef enum
{
    TVSRV_TV_REGION__USA = 0
   ,/*USA*/
    TVSRV_TV_REGION__CANADA
   ,/*CANADA*/
    TVSRV_TV_REGION__KOREA
   ,/*KOREA*/
    TVSRV_TV_REGION__TAIWAN
   ,/*TAIWAN*/
    TVSRV_TV_REGION__MEXICO
   ,/*MEXICO*/
    TVSRV_TV_REGION__CHILE
   ,/*CHILE*/
    TVSRV_TV_REGION__VENEZUELA
   ,/*VENEZUELA*/
    TVSRV_TV_REGION__PHILIPPINES
   ,/*PHILIPPINES*/
    TVSRV_TV_REGION__JAMAICA
   ,/*JAMAICA*/
    TVSRV_TV_REGION__CHINA
   ,/*CHINA*/
    TVSRV_TV_REGION__SHENZHEN
   ,/*SHENZHE*/
    TVSRV_TV_REGION__VIETNAM
   ,/*VIETNAM*/
    TVSRV_TV_REGION__WESTERNEUROPE
   ,/*WESTERNEUROPE*/
    TVSRV_TV_REGION__TURKEY
   ,/*TURKEY*/
    TVSRV_TV_REGION__UAE
   ,/*UAE*/
    TVSRV_TV_REGION__AFGHANISTAN
   ,/*AFGHANISTAN*/
    TVSRV_TV_REGION__SINGAPORE
   ,/*SINGAPORE*/
    TVSRV_TV_REGION__THAILAND
   ,/*THAILAND*/
    TVSRV_TV_REGION__CAMBODIA
   ,/*CAMBODIA*/
    TVSRV_TV_REGION__INDONESIA
   ,/*INDONESIA*/
    TVSRV_TV_REGION__MALAYSIA
   ,/*MALAYSIA*/
    TVSRV_TV_REGION__LAOS
   ,/*LAOS*/
    TVSRV_TV_REGION__PORTUGAL
   ,/*PORTUGAL*/
    TVSRV_TV_REGION__SWEDEN
   ,/*SWEDEN*/
    TVSRV_TV_REGION__PAKISTAN
   ,/*PAKISTAN*/
    TVSRV_TV_REGION__SPAIN
   ,/*SPAIN*/
    TVSRV_TV_REGION__JAPAN
   ,/*JAPAN*/
    TVSRV_TV_REGION__UK
   ,/*UK*/
    TVSRV_TV_REGION__HONGKONG
   ,/*HONGKONG*/
    TVSRV_TV_REGION__SOUTHAFRICA
   ,/*SOUTHAFRICA*/
    TVSRV_TV_REGION__BRAZIL
   ,/*BRAZIL*/
    TVSRV_TV_REGION__ARGENTINA
   ,/*ARGENTINA*/
    TVSRV_TV_REGION__INDIA
   ,/*INDIA*/
    TVSRV_TV_REGION__BURMA
   ,/*BURMA*/
    TVSRV_TV_REGION__SUDAN
   ,/*SUDAN*/
    TVSRV_TV_REGION__YEMEN
   ,/*YEMEN*/
    TVSRV_TV_REGION__PERU
   ,/*PERU*/
    TVSRV_TV_REGION__BOLIVIA
   ,/*BOLIVIA*/
    TVSRV_TV_REGION__ECUADOR
   ,/*ECUADOR*/
    TVSRV_TV_REGION__SURINAME
   ,/*SURINAME*/
    TVSRV_TV_REGION__AUSTRALIA
   ,/*AUSTRALIA*/
    TVSRV_TV_REGION__NEWZEALAND
   ,/*NEWZEALAND*/
    TVSRV_TV_REGION__COLUMBIA
   ,/*COLUMBIA*/
    TVSRV_TV_REGION__COSTARICA
   ,/*COSTARICA*/
    TVSRV_TV_REGION__HONDURAS
   ,/*HONDURAS*/
    TVSRV_TV_REGION__GERMAN
   ,/*GERMAN*/
    TVSRV_TV_REGION__ITALY
   ,/*ITALY*/
    TVSRV_TV_REGION__TOTAL
   ,/*MAXIMUM REGION NUMBER*/
} TvSrvRegion_e;

/**
*  @brief The enumeration defines TV Hybrid type.
*/
typedef enum
{
    TVSRV_TV_HYBRID_ANALOG = 0,
    TVSRV_TV_HYBRID_CMMB,
    TVSRV_TV_HYBRID_ISDBT,
    TVSRV_TV_HYBRID_NUM,
}TvSrvHybridType_e;

/**
*  @brief The structure defines the tv capture resolution.
*/
typedef enum
{
    TVSRV_RATIO__4_3
   ,TVSRV_RATIO__16_9
   ,TVSRV_RATIO__16_10
} TvSrvRatio_e;

/**
*  @brief The structure defines the window area property.
*/
typedef struct
{
    u16 nPosX;     /**< Horizontal position of top-left */
    u16 nPosY;     /**< Vertical position of top-left */
    u16 nWidth;    /**< Horizontal width */
    u16 nHeight;   /**< Vertical height */
} TvSrvRegion_t;

/**
*  @brief The structure defines the tv capture resolution.
*/
typedef enum
{
    TVSRV_CAP_RES__UXGA_1600_1200,    /* 1600x1200(UXGA) */
    TVSRV_CAP_RES__1_3M_1280_1024,    /* 1280x1024(1.3M pixel) */
    TVSRV_CAP_RES__1024_768,          /* 1024x768 */
    TVSRV_CAP_RES__800_600,           /* 800x600 */
    TVSRV_CAP_RES__VGA_640_480,       /* 640x480(VGA) */
    TVSRV_CAP_RES__HVGA_480_320,      /* 480x320(HVGA ) */
    TVSRV_CAP_RES__WQVGA_400_240,     /* 400x240(WQVGA ) */
    TVSRV_CAP_RES__QVGA_320_240,      /* 320x240(QVGA) */
    TVSRV_CAP_RES__WALLPAPER_240_320, /* 240x320(Wallpaper) */
    TVSRV_CAP_RES__QCIF_PLUS_220_176, /* 220x176(Wallpaper)*/
    TVSRV_CAP_RES__WALLPAPER_176_220, /* 176x220(Wallpaper)*/
    TVSRV_CAP_RES__QCIF_176_144,      /* 176x144(QCIF)*/
    TVSRV_CAP_RES__QQVGA_160_120,     /* 160x120(QQVGA) */
    TVSRV_CAP_RES__CONTACT_96_96      /* For Contact */
} TvSrvCaptureRes_e;

/**
*  @brief The enumeration defines the path of loading shutter sound.
*/
typedef enum
{
    TVSRV_SOUND_PATH__DEFAULT
   ,/**< Using the default sound in MMP */
    TVSRV_SOUND_PATH__DOWNLOAD
   ,/**< Using the sound that load from BB */
    TVSRV_SOUND_PATH__CARD
   ,/**< Using the sound that save in card */
} TvSrvSoundPath_e;

/**
*  @brief The sturcture defines the property of the camera shutter sound.
*/
typedef struct
{
    TvSrvSoundPath_e eSoundPath; /**< The shutter sound path that want to use */
    u8 *pSound;   /**< PCM data buffer or file name in card (MMI should release buffer after receiving response msg)  */
    u32 nSoundLen;  /**< The length of PCM or filen name in card */
} TvSrv_Sound_t;

typedef struct
{
    TvSrvShutterSound_e eShutSound;
    TvSrvSoundPath_e eSoundPath; /**< The shutter sound path that want to use */
    u8 *pSound;   /**< PCM data buffer or file name in card (MMI should release buffer after receiving response msg)  */
    u32 nSoundLen;  /**< The length of PCM or filen name in card */
} TvSrvShutterSoundSetting_t;

typedef union
{
    TvSrvCaptureRes_e eTvPicRes;
} TvSrvResolution_t;

/**
*  @brief The enumeration defines the tv rotation angle
*/
typedef enum
{
    TVSRV_ROTATE__NONE
   ,/**< No Rotation */
    TVSRV_ROTATE__90
   ,/**< Rotate angle 90 degree */
    TVSRV_ROTATE__180
   ,/**< Rotate angle 180 degree */
    TVSRV_ROTATE__270   /**< Rotate angle 270 degree */
} TvSrvRotate_e;

/**
*  @brief The enumeration defines the tv capture recording quality.
*/
typedef enum
{
    TVSRV_IMG_QUALITY__LOW
   ,/* Low quality */
    TVSRV_IMG_QUALITY__NORMAL
   ,/* Nomal quality */
    TVSRV_IMG_QUALITY__HIGH     /* High quality */
} TvSrvImgQuality_e;

typedef enum
{
    TVSRV_CAP_STORAGE__CARD = 0
   ,TVSRV_CAP_STORAGE__PHONE
} TvSrvCaptureStorage_e;

/**
*  @brief The structure defines the tv signal.
*/
typedef enum
{
    TVSRV_SIGNAL_LV__NONE = 0
   ,/* signal level 0 (not recieve signal) */
    TVSRV_SIGNAL_LV__1
   ,/* signal level 1  */
    TVSRV_SIGNAL_LV__2
   ,/* signal level 2  */
    TVSRV_SIGNAL_LV__3
   ,/* signal level 3  */
    TVSRV_SIGNAL_LV__4
   ,/* signal level 4  */
    TVSRV_SIGNAL_LV__5
   ,/* signal level 5  */
    TVSRV_SIGNAL_LV__6
   ,/* signal level 6  */
    TVSRV_SIGNAL_LV__7
   ,/* signal level 7  */
    TVSRV_SIGNAL_LV__8
   ,/* signal level 8  */
    TVSRV_SIGNAL_LV__9
   ,/* signal level 9  */
    TVSRV_SIGNAL_LV__MAX
   ,/*signal level max */
} TvSrvSignalLv_e;

typedef enum
{
    TVSRV_CAACCESS_GRANTED = 0,
    TVSRV_CAACCESS_DENIED = 2,
    TVSRV_CAACCESS_CLEAR = 9
} TvSrvCaAccessStatus_e;

typedef enum
{
    TVSRV_TYPE__ATV
   ,//ESL_TV_ATV
    TVSRV_TYPE__DTV
   ,//ESL_TV_DTV
    TVSRV_TYPE__AUDIO
   ,//ESL_TV_AUDIO
    TVSRV_TYPE__LC_TEST
   ,//ESL_TV_LC_TEST
    TVSRV_TYPE__MAX
   ,//ESL_TV_MAX
} TvSrvType_e;

/**
*  @brief The enumeration defines type of the TV error.
*/
typedef enum
{
    TVSRV_ERROR__CAPTURE = 0
   ,/**< TV error type about file action fail */
    TVSRV_ERROR__SPACE_FULL
   ,/**< Notify MMI that space full error */
    TVSRV_ERROR__UNKNOWN
   ,/**< TV error type about unknown type */
    TVSRV_ERROR__SETFREQ
   ,/**< TV error type about set frequency */
    TVSRV_ERROR__NONE
   ,/**< TV error type about no error */
    TVSRV_ERROR__MEMORY_INSUFFICIENT
   ,/**< Insufficient memory */
} TvSrvErrorType_e;

typedef enum
{
    TVSRV_CAPTURE_STOP__USER_STOP = 0
   ,TVSRV_CAPTURE_STOP__CAPTURE_END
   ,TVSRV_CAPTURE_STOP__RUNTIME_ERROR
} TvSrvCaptureStopType_e;

/**
*  @brief The enumeration defines type of the ESG type.
*/
typedef enum
{
    TVSRV_ESG_TYPE_NORMAL,       /* Normal ESG data */
    TVSRV_ESG_TYPE_INFO_UPDATE,  /* ESG Information update */
    TVSRV_ESG_TYPE_BROADCAST     /* ESG Broadcasting */
} TvSrvESGType_e;

/**
*  @brief The enumeration defines type of the language channel.
*/
typedef enum
{
    TVSRV_TV_LEFTCHANNEL,
    TVSRV_TV_RIGHTCHANNEL,
    TVSRV_TV_BOTHCHANNEL,
} TvSrvLanChannel_e;

typedef enum {
    TVSRV_REC_RES_352_288, /* 352x288(CIF) */
    TVSRV_REC_RES_176_144, /* 176x144(QCIF) */
    TVSRV_REC_RES_128_96   /* 128x96(SUB-QCIF) */
} TvSrvTvRecRes_e;

typedef enum {
    TVSRV_REC_CODEC_H263,
    TVSRV_REC_CODEC_MPEG4
} TvSrvRecCodec_e;

typedef enum {
    TVSRV_REC_QUALITY_LOW,     /* Low quality */
    TVSRV_REC_QUALITY_NORMAL,  /* Nomal quality */
    TVSRV_REC_QUALITY_HIGH     /* High quality */
} TvSrvRecQuality_e;

typedef enum {
    TVSRV_REC_LIMIT_SIZE, /**< TV recorder recording size limit */
    TVSRV_REC_LIMIT_TIME  /**< TV recorder recording time limit*/
}TvSrvLimitType_e;

typedef struct {
    TvSrvLimitType_e    limitType;    /** The type of camcorder recording limit. */
    u32                 limitValue;   /** Unit of size limit: Byte, unit of time limit:  millisecond. */
} TvSrvRecLimit_t;

typedef enum {
    TVSRV_REC_PATH_DIR,     /**< MMI decide folder only */
    TVSRV_REC_PATH_PREFIX,  /**< MMI decide pre-fix of file name   */
    TVSRV_REC_PATH_ABSOLUTE /**< MMI give full folder path and file name   */
} TvSrvRecPath_e;

typedef struct {
    TvSrvESGType_e eESGType;
    u16 *pESGDataPtr;
    u16 nESGdataLen;
} TvSrvESGData_t;

typedef struct
{
    u32 nSrvInstId;
    u32 nAppInstId;
    void *pfnCb;
    MAE_Ret eErrCode;
}TvSrvCusInfo_t;

typedef struct
{
    u32 nSrvInstId;
    u32 nAppInstId;
    u32 pfnCb;
    TvSrvCaptureStopType_e eStopType;
    TvSrvErrorType_e eNotifyErrCode;
} TvSrvGetFileCusInfo_t;

/**
*  @brief The sturcture defines the file name and length of the last jpeg or 3gp file.
*/
typedef struct
{
    u16 nOutLen;        /**< file name length */
    u16 *pFileNameOut; /**< file name buffer (MMI should release file name buffer after receiving response msg) */
} TvSrvFileName_t;

typedef struct
{
    u32 nEvtCode;
    TvSrvErrorType_e eErrCode;
} TvSrvCaptureNotifyCbData_t;

typedef struct
{
    u32 nEvtCode;
    TvSrvErrorType_e eErrCode;
    TvSrvFileName_t tFileName;
} TvSrvCaptureNotifyCbDataEx_t;

typedef struct
{
    u32 nTotalChn;                 /**< Total capacity of channels in current area */
    TvSrvSignalLv_e eSingalLv;    /**< Tv signal level */
} TvSrvSignalLevel_t;

typedef enum
{
    TVSRV_INFOTYPE_NORMAL = 0,     ///< Normal TV info
    TVSRV_INFOTYPE_ENGINEERING,    ///< Engineering mode TV info
    TVSRV_INFOTYPE_CMMB,           ///< CMMB TV info
    TVSRV_INFOTYPE_ALL,            ///< All of the TV info (Normal + Engineering)
} TvSrvInfoType_e;

typedef struct
{
    u8                     *pCat;
    u32                    nCatSize;
    u8  	                 *pEsg;
    u32 	                 nEsgSize;
    u8  	                 *pCaCardNumber;
    u32                    nCaCardNumberSize;
    TvSrvCaAccessStatus_e  eCaPermission;
    TvSrvSignalLv_e eSingalLv;    /**< Tv signal level */
} TvSrvCmmbTvInfo_t;

typedef struct
{
    union
    {
        TvSrvSignalLevel_t tSignal;
        TvSrvCmmbTvInfo_t tCmmbTvInfo;
    }uParam;
} TvSrvTvInfo_t;

typedef struct
{
    u32             nFrequency;
    u32             nProgramServiceID;
    u8              *pProgramServiceTimeSlot;
    u8              nProgramServiceTimeSlotLength;
    u32             nEmmServiceID;
    u8              *pEmmServiceTimeSlot;
    u8              nEmmServiceTimeSlotLength;
} TvSrvCmmbFrequency_t;

typedef struct
{
    union{
      u32                         nAtvChannel;             ///< 32-bit channel number
      TvSrvCmmbFrequency_t        tFrequency;              ///< Frequency information Structure (Only used for DTV)
    } uParam;
} TvSrvSwitchChannel_t;

typedef struct
{
    TvSrvInfoType_e             eInfoType;       ///< Indicate what type of the TV info to get
    union
    {
        TvSrvCmmbTvInfo_t       tCmmbTvInfo;    ///< Pointer to the output CMMB TV info buffer
   	} uParam;
} TvSrvGetTvInfo_t;

typedef struct
{
    TvSrvRegion_t        tDisplayOutput;          ///< Display output
    TvSrvRotate_e        eRotationAngle;          ///< Rotation angle
    union{
      u32                         nAtvChannel;                ///< 32-bits channel number
      TvSrvCmmbFrequency_t        tFrequency;                 ///< 32-bits DTV frequency (in 1KHz)
    } uParam;
} TvSrvStartPreview_t;

typedef struct
{
    u32 nCh;       /**< the scanning channel */
    boolean bIsExist;  /**< this channel was found and exist in this scanning (TRUE: exist, FALSE: it not scanned*/
    MAE_WChar *pChannelName;  /**< for ISDBT >**/
    u32 nChannelNameLen;      /**< for ISDBT >**/
} TvSrvChannelInfo_t;            /**< Information resonse from 'ScanChn' Request */

typedef struct
{
    u32 channelID;
    u32 frequency;
    u8  *pTimeSlotBuffer;
    u8  nTimeSlotLength;
} TvSrvTvChannel_t;            /**< Information resonse from 'ScanChn' Request */
/**
*  @brief The sturcture defines the return value for application layer (MMI) query.
*/
typedef struct
{
    union
    {
        TvSrvFileName_t tFileName; /**< File name output information response from 'TV_Capture' Request */
        TvSrvSignalLevel_t tSignalLevel;
        TvSrvChannelInfo_t tChannelInfo;
    } uParam;
} TvSrvInfo_t;

typedef struct
{
    TvSrvRotate_e eLastRotate;
    TvSrvRegion_t tLastRegion;
} TvSrvWatchConfig_t;

typedef struct
{
    TvSrvResolution_t tTvResolution;        // *Image Size
    TvSrvImgQuality_e eTvImgQty;            // Currently, both image quality and video quality set the same config, jpegQuality!
    TvSrvShotMode_e eShotMode;
} TvSrvCaptureConfig_t;

typedef struct
{
    TvSrvTvRecRes_e eTVRecRes;
    TvSrvRecCodec_e eTVRecCodec;
    TvSrvRecQuality_e eTVRecQuality;
    TvSrvRecLimit_t tRecLimit;
    TvSrvFileName_t tFileName;
    TvSrvRecPath_e  eRecPath;
    u16             nCh;
} TvSrvRecordConfig_t;

// Config definition
typedef struct TvSrvConfig_t_
{
    MAE_WChar pTvStoredPath[TVSRV_STORED_PATH_LEN + 1]; // *Storage
    u16 nPathLen;                               // Storage
    TvSrvShutterSound_e eTvShutterSound;
    TvSrvSoundPath_e eSoundPath;
    TvSrvCaptureConfig_t tCaptureConfig;
} TvSrvConfig_t;

typedef struct TvSrvEmInfo_t_
{
    u16          nTfCode;        /**< The tfcode of telegent chip*/
    u16          nPeakAgc;       /**< The peak of telegent chip*/
    u16          nTotalGain;     /**< The total gain of telegent chip*/
    bool         bColorLock;     /**< The color lock bit of telegent chip*/
} TvSrvEmInfo_t;

/**
 *  @brief The structure defines the layer property setting
 */
typedef struct {
  u8 transLevel;              /* Transparency value(0: transparent 255: opaque) */
} TvSrvLayerProperty_t;

typedef enum {
  TVSRV_LAYER_VDO,             /**< Layer V0 */
  TVSRV_LAYER_G0,              /**< Layer G0 */
  TVSRV_LAYER_G1,              /**< Layer G1 */
  TVSRV_LAYER_G3D,             /**< Layer G3D  */
  TVSRV_LAYER_UNKNOW           /**<Unknown image format */
} TvSrvGssLayer_e;

/**
 *  @brief The structure defines the PEQ config setting
 */
typedef struct {
    s8	band1;							/**< Band 1 Magnitude +50~-50 */
    s8	band2;							/**< Band 2 Magnitude +50~-50 */
    s8	band3;							/**< Band 3 Magnitude +50~-50 (invalid for EQ6 type)*/
    s8	band4;							/**< Band 4 Magnitude +50~-50 (invalid for EQ6 type)*/
    s8	band5;							/**< Band 5 Magnitude +50~-50 (invalid for EQ6 type)*/
} TvSrvPEQConfig_t;

typedef enum {
	TVSRV_AUD_3D_DISABLE = 0,      /**< 3D effect disable */
	TVSRV_AUD_3D_NORMAL,       /**< 3D effect normal level enable */
	TVSRV_AUD_3D_HIGH          /**< 3D effect high level enable */
} TvSrvAud3D_e;

typedef void (*TvSrvCommonCb)(void *pThis, u32 nRetCode);
typedef void (*TvSrvCapturedFileNameCb)(void *pThis, u32 nRetCode, TvSrvFileName_t *pFileName);
typedef void (*TvSrvChannelInfoCb)(void *pThis, u32 nRetCode, TvSrvChannelInfo_t *pChInfo);
typedef void (*TvSrvCmmbSignalLevelCb)(void *pThis, u32 nRetCode, TvSrvCmmbTvInfo_t *pCmmbTvInfo);
typedef void (*TvSrvSignalLevelCb)(void *pThis, u32 nRetCode, TvSrvSignalLevel_t *pSignal);
typedef void (*TvSrvEmInfoCb)(void *pThis, u32 nRetCode, TvSrvEmInfo_t *pEmInfo);
typedef void (*TvSrvNotifyCb)(void *pThis, MediaSrvInterruptStatus_e eStatus);
typedef void (*TvSrvCaptureNotifyCb)(void *pThis, TvSrvCaptureNotifyCbData_t *pCaptureNotifyCbData);
typedef void (*TvSrvCaptureNotifyCbEx)(void *pThis, TvSrvCaptureNotifyCbDataEx_t *pCaptureNotifyCbData);

#endif

