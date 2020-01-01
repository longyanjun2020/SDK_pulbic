/**
 *
 * @file    esl_tv_itf.h
 *
 * @brief   This file defines the tv interface for upper layer (like MMI) using.
 *
 * @author  Jack Hsieh
 * @version $Id: esl_tv_itf.h
 *
 */
#ifndef __ESL_TV_ITF_H__
#define __ESL_TV_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_TV_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif
#define EMA_LEVEL_TV            _CUS2 | LEVEL_12

#define ESL_TV_STORAGE_PATH   128 /**< The Maximum length of storage path */

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the return code of the TV interface function.
 */
typedef enum {
  ESL_TV_OK,               /**< Function complete successfully */
  ESL_TV_FAIL,             /**< Function fail */
  ESL_TV_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_TV_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_TV_REJECT,           /**< Request reject because of other function's confliction */
  ESL_TV_ABORT,            /**< Request abort because of incorrect sequence */
  ESL_TV_TIMEOUT           /**< Request command to MMP is no response */
} esl_TvErrCode_e;

/**
 *  @brief The enumeration defines the mode of tv preview.
 */
typedef enum {
  ESL_TV_PREVIEW_OFF,            /**< Stop tv preview */
  ESL_TV_PREVIEW_ON,             /**< Start tv preview */
} esl_TvPreview_e;

/**
 *  @brief The enumeration defines the type of TV module (Analog or Digital)
 */
typedef enum {
    ESL_TV_ATV,    /**< ATV (analog TV)   */
    ESL_TV_DTV,    /**< DTV (digital TV)  */
    ESL_TV_AUDIO,
    ESL_TV_LC_TEST,
		ESL_TV_MAX
} esl_TvType_e;


typedef enum{
  ESL_TV_LEFTCHANNEL,
  ESL_TV_RIGHTCHANNEL,
  ESL_TV_BOTHCHANNEL,
}esl_TvSoundChannel_e;


/**
 *  @brief The enumeration defines the path of tv service for still image or video recording
 */
typedef enum {
  ESL_TV_PATH_DIR,     /**< MMI decide folder only */
  ESL_TV_PATH_PREFIX,  /**< MMI decide pre-fix of file name   */
  ESL_TV_PATH_ABSOLUTE /**< MMI give full folder path and file name   */
} esl_TvPath_e;

/**
 *  @brief The enumeration defines the mode of tv snapshot.
 */
typedef enum {
  ESL_TV_SINGLE,      /**< Tv single shot mode */
  ESL_TV_CONSSINGLE,  /**< Tv continuous shot mode */
  ESL_TV_SINGLE_DTV        /**< Tv single shot mode and no shutter sound */
} esl_TvShotMode_e;

/**
 *  @brief The structure defines the tv capture resolution.
 */
typedef enum {
  ESL_TV_1600_1200,  /* 1600x1200(UXGA) */
  ESL_TV_1280_1024,  /* 1280x1024(1.3M pixel) */
  ESL_TV_1024_768,   /* 1024x768 */
  ESL_TV_800_600,    /* 800x600 */
  ESL_TV_640_480,    /* 640x480(VGA) */
  ESL_TV_480_320,    /* 480x320(HVGA ) */
  ESL_TV_400_240,    /* 400x240(WQVGA ) */
  ESL_TV_320_240,    /* 320x240(QVGA) */
  ESL_TV_240_320,    /* 240x320(Wallpaper) */
  ESL_TV_220_176,    /* 220x176(Wallpaper)*/
  ESL_TV_176_220,    /* 176x220(Wallpaper)*/
  ESL_TV_176_144,    /* 176x144(QCIF)*/
  ESL_TV_160_120,    /* 160x120(QQVGA) */
  ESL_TV_96_96       /* For Contact */
} esl_TvCaptureRes_e;

/**
 *  @brief The structure defines the tv capture resolution.
 */
typedef enum {
  ESL_TV_SIGNAL_LV_NONE = 0,  /* signal level 0 (not recieve signal) -- min */
  ESL_TV_SIGNAL_LV_1,         /* signal level 1  */
  ESL_TV_SIGNAL_LV_2,         /* signal level 2  */
  ESL_TV_SIGNAL_LV_3,         /* signal level 3  */
  ESL_TV_SIGNAL_LV_4,         /* signal level 4  */
  ESL_TV_SIGNAL_LV_5,         /* signal level 5  */
  ESL_TV_SIGNAL_LV_6,         /* signal level 6  */
  ESL_TV_SIGNAL_LV_7,         /* signal level 7  */
  ESL_TV_SIGNAL_LV_8,         /* signal level 8  (max)*/
  ESL_TV_SIGNAL_LV_MAX,       /* signal level max number(should not used)*/
} esl_TvSignalLv_e;

#ifdef __ATV_CMMB__
/** @ingroup    MMLayerTv
    @brief      CA access status
*/
typedef enum
{
    ESL_TV_CAACCESS_GRANTED = 0,
    ESL_TV_CAACCESS_DENIED = 2,
    ESL_TV_CAACCESS_CLEAR = 9
} esl_TvCaAccessStatus_e;
#endif

/**
 *  @brief The enumeration defines TV nations' region.
 */
typedef enum {
  ESL_TV_REGION_USA = 0,      /*USA*/
  ESL_TV_REGION_CANADA,       /*CANADA*/
  ESL_TV_REGION_KOREA,        /*KOREA*/
  ESL_TV_REGION_TAIWAN,       /*TAIWAN*/
  ESL_TV_REGION_MEXICO,       /*MEXICO*/
  ESL_TV_REGION_CHILE,        /*CHILE*/
  ESL_TV_REGION_VENEZUELA,    /*VENEZUELA*/
  ESL_TV_REGION_PHILIPPINES,  /*PHILIPPINES*/
  ESL_TV_REGION_JAMAICA,      /*JAMAICA*/
  ESL_TV_REGION_CHINA,        /*CHINA*/
  ESL_TV_REGION_SHENZHEN,     /*SHENZHE*/
  ESL_TV_REGION_VIETNAM,      /*VIETNAM*/
  ESL_TV_REGION_WESTERNEUROPE,/*WESTERNEUROPE*/
  ESL_TV_REGION_TURKEY,       /*TURKEY*/
  ESL_TV_REGION_UAE,          /*UAE*/
  ESL_TV_REGION_AFGHANISTAN,  /*AFGHANISTAN*/
  ESL_TV_REGION_SINGAPORE,    /*SINGAPORE*/
  ESL_TV_REGION_THAILAND,     /*THAILAND*/
  ESL_TV_REGION_CAMBODIA,     /*CAMBODIA*/
  ESL_TV_REGION_INDONESIA,    /*INDONESIA*/
  ESL_TV_REGION_MALAYSIA,     /*MALAYSIA*/
  ESL_TV_REGION_LAOS,         /*LAOS*/
  ESL_TV_REGION_PORTUGAL,     /*PORTUGAL*/
  ESL_TV_REGION_SWEDEN,       /*SWEDEN*/
  ESL_TV_REGION_PAKISTAN,     /*PAKISTAN*/
  ESL_TV_REGION_SPAIN,        /*SPAIN*/
  ESL_TV_REGION_JAPAN,        /*JAPAN*/
  ESL_TV_REGION_UK,           /*UK*/
  ESL_TV_REGION_HONGKONG,     /*HONGKONG*/
  ESL_TV_REGION_SOUTHAFRICA,  /*SOUTHAFRICA*/
  ESL_TV_REGION_BRAZIL,       /*BRAZIL*/
  ESL_TV_REGION_ARGENTINA,    /*ARGENTINA*/
  ESL_TV_REGION_INDIA,        /*INDIA*/
  ESL_TV_REGION_BURMA,        /*BURMA*/
  ESL_TV_REGION_SUDAN,        /*SUDAN*/
  ESL_TV_REGION_YEMEN,        /*YEMEN*/
  ESL_TV_REGION_PERU,         /*PERU*/
  ESL_TV_REGION_BOLIVIA,      /*BOLIVIA*/
  ESL_TV_REGION_ECUADOR,      /*ECUADOR*/
  ESL_TV_REGION_SURINAME,     /*SURINAME*/
  ESL_TV_REGION_AUSTRALIA,    /*AUSTRALIA*/
  ESL_TV_REGION_NEWZEALAND,   /*NEWZEALAND*/
  ESL_TV_REGION_COLUMBIA,     /*COLUMBIA*/
  ESL_TV_REGION_COSTARICA,    /*COSTARICA*/
  ESL_TV_REGION_HONDURAS,     /*HONDURAS*/
  ESL_TV_REGION_GERMAN,       /*GERMAN*/
  ESL_TV_REGION_ITALY,        /*ITALY*/
  ESL_TV_REGION_TOTAL         /*MAXIMUM REGION NUMBER*/
} esl_TvRegion_e;

/**
 *  @brief The enumeration defines the tv capture recording quality.
 */
typedef enum {
  ESL_TV_QUALITY_LOW,     /* Low quality */
  ESL_TV_QUALITY_NORMAL,  /* Nomal quality */
  ESL_TV_QUALITY_HIGH     /* High quality */
} esl_TvQuality_e;

/**
 *  @brief The enumeration defines the tv capture recording quality.
 */
typedef enum {
  ESL_TV_ESG_TYP_NORMAL,       /* Normal ESG data */
  ESL_TV_ESG_TYP_INFO_UPDATE,  /* ESG Information update */
  ESL_TV_ESG_TYP_BROADCAST     /* ESG Broadcasting */
} esl_TvEsgType_e;

/**
 *  @brief The enumeration defines for tv set frequency.
 */
typedef enum {
  ESL_TV_SET_FREQ_GET_INFO,    /* Notify Normal ESG data after setting frequency */
  ESL_TV_SET_FREQ_NO_INFO,     /* no ESG Information update  after setting frequency*/
} esl_TvSetFreqType_e;

/**
 *  @brief The structure defines the window area property.
 */
typedef struct {
  u16   posX;     /**< Horizontal position of top-left */
  u16   posY;     /**< Vertical position of top-left */
  u16   width;    /**< Horizontal width */
  u16   height;   /**< Vertical height */
} esl_TvRegion_t;

/**
 *  @brief The enumeration defines the tv rotation angle
 */
typedef enum {
  ESL_TV_ROTATE_NONE, /**< No Rotation */
  ESL_TV_ROTATE_90,   /**< Rotate angle 90 degree */
  ESL_TV_ROTATE_180,  /**< Rotate angle 180 degree */
  ESL_TV_ROTATE_270   /**< Rotate angle 270 degree */
} esl_TvRotate_e;

/**
 *  @brief The enumeration defines the tv rotation angle
 */
typedef enum {
  ESL_TV_CMD_TSP_START,             /**< Start  the play TV  (Time shift playback, only support in DTV(CMMB)  */
  ESL_TV_CMD_TSP_PAUSE,    /**< Pause the play TV  (Time shift playback, only support in DTV(CMMB)  */
  ESL_TV_CMD_TSP_RESUME,            /**< Resume the play TV (Time shift playback, only support in DTV(CMMB) */
  ESL_TV_CMD_TSP_STOP,              /**< Stop   the play TV  (Time shift playback, only support in DTV(CMMB)  */
  ESL_TV_CMD_COMMAND_CANCEL,    	/**< Cancel command  */
} esl_TvCmd_e;


/**
 *  @brief The enumeration defines the canel
 */
typedef enum {
  ESL_TV_CANCEL_SCAN,                /**< Cancel CMMB scan frequency command (only support in DTV(CMMB)  */
  ESL_TV_CANCEL_SET_FREQ,            /**< Cancel CMMB set frequency command (only support in DTV(CMMB)  */
} esl_TvCancelType_e;


/**
 *  @brief The structure defines the camera video recording resolution.
 */
typedef enum {
  ESL_TV_RES_352_288, /* 352x288(CIF) */
  ESL_TV_RES_176_144, /* 176x144(QCIF) */
  ESL_TV_RES_128_96   /* 128x96(SUB-QCIF) */
} esl_TvRes_e;

/**
 *  @brief The enumeration defines limit type of TV recording.
 */
typedef enum {
	ESL_TV_LIMIT_SIZE, /**< TV recorder recording size limit */
  ESL_TV_LIMIT_TIME  /**< TV recorder recording time limit*/
}esl_TvLimitType_e;

/**
 *  @brief The enumeration defines video recording limit of size and time.
 */
typedef struct {
  esl_TvLimitType_e     limitType;    /** The type of camcorder recording limit. */
  u32                   limitValue;   /** Unit of size limit: Byte, unit of time limit:  millisecond. */
} esl_TvRecLimit_t;

/**
 *  @brief The structure defines the preview action property.
 */
typedef struct {
	esl_TvType_e    type;   /**< TV type */
  esl_TvPreview_e action; /**< Preview action, on/off the tv power*/
  u32             freq;   /*   DTV frequency*/
  u32             ch;     /**< TV preview channel number */
} esl_TvPreview_t;

/**
 *  @brief The structure defines the set frequency property.
 */
typedef struct {
	esl_TvSetFreqType_e    type;   /**<  SET frequency type */
  u32                    freq;   /**<  TV frequency*/
} esl_TvSetFreq_t;

/**
 *  @brief The structure defines the information for channel scan
 */
typedef struct {
  esl_TvType_e    type;      /**< TV type */
  u32             ch;        /**< TV preview channel number (DTV is freq)*/
} esl_TvScanConfig_t;

/**
 *  @brief The structure defines the Panel display, Preview and OSD windows property.
 */
typedef struct {
  esl_TvRegion_t  winPreview; /**< Preview window area */
  esl_TvRegion_t  winOSD;     /**< OSD windiow area */
  u16             sck;        /**< OSD transparency color */
  u16             transLevel; /**< OSD transparency level */
  esl_TvRotate_e  angle;      /**< Preview window rotation angle */
} esl_TvDispRegion_t;

/**
 *  @brief The structure defines the tv capture or video recording resolution.
 */
typedef struct {
  u16 width;  /**< Resolution width */
  u16 height; /**< Resolution height */
} esl_TvSize_t;

/**
 *  @brief The structure defines the tv snapshot property.
 */
typedef struct {
    esl_TvSize_t  tvShotSize;             /**< JPEG resolution */
    u8  burstShootNb;                     /**< Continuous shot number */
    u8  jpegQuality;                      /**< JPEG quality */
    u8  storedPath[ESL_TV_STORAGE_PATH];  /**< Storage path (Max length is 128 byte) */
    u32 pathLen;                          /**< Storage path length (Max length is 128 byte) */
} esl_TvCapture_t;


typedef enum {
  ESL_TV_ORIENTATION_TOP_LEFT     = 0x00, /**< Top-Left Orientation */
  ESL_TV_ORIENTATION_TOP_RIGHT    = 0x01, /**< Top-Right Orientation */
  ESL_TV_ORIENTATION_BOTTOM_RIGHT = 0x02, /**< Bottom-Right Orientation */
  ESL_TV_ORIENTATION_BOTTOM_LEFT  = 0x03, /**< Bottom-Left Orientation */
  ESL_TV_ORIENTATION_LEFT_TOP     = 0x04, /**< Left-Top Orientation */
  ESL_TV_ORIENTATION_RIGHT_TOP    = 0x05, /**< Right-Top Orientation */
  ESL_TV_ORIENTATION_RIGHT_BOTTOM = 0x06, /**< Right-Bottom Orientation */
  ESL_TV_ORIENTATION_LEFT_BOTTOM  = 0x07  /**< Left-Bottom Orientation */
} esl_TvOrientationInfo_e;

typedef struct {
  esl_TvOrientationInfo_e oriInfo; /**< Exif Orientation information */
} esl_TvExifInfo_t;

/**
 *  @brief The sturcture defines the property of the jpeg capture.
 */
typedef struct {
  esl_TvCaptureRes_e tvCaptureRes;  /**< Tv snapshot resolution */
  esl_TvQuality_e    jpegQuality;   /**< JPEG quality: Low, Normal and High */
  esl_TvShotMode_e   mode;          /**< Single, continuous, or sticker shot mode. */
  esl_TvExifInfo_t   exifInfo;    /**< Exif information */
  struct {
    u16 pathLen;                    /**< Storage path length (UCS2)*/
    u16 *pPathName;                 /**< Storage path */
    esl_TvPath_e pathType;          /**< Indicate Tv capture or video recording path type - Directory, Prefix or Full Name. */
  } path;
} esl_TvJpegSetting_t;

/**
 *  @brief The sturcture defines the property of the tv capture path.
 */
typedef struct {
  u16          *pPath;      /**< Storage folder path pointer */
  u16          pathLen;     /**< Storage folder path length (UCS2) */
  esl_TvPath_e pathType;    /**< Indicate Tv capture or video recording path type - Directory, Prefix or Full Name. */
} esl_TvPathSetting_t;

/**
 *  @brief The sturcture defines the property of the tv capture path.
 */
typedef struct {
  esl_TvPathSetting_t pathSet;    /**< Storage path seeting */
  esl_TvRegion_e      region;     /**< TV region seeting  */
} esl_TvConfig_t;

/**
 *  @brief The sturcture defines the file name and length of the last jpeg or 3gp file.
 */
typedef struct {
  u16 outLen;        /**< file name length */
  u16 *pFileNameOut; /**< file name buffer (MMI should release file name buffer after receiving response msg) */
} esl_TvFileName_t;


/**
 *  @brief The enumeration defines video codec format.
 */
typedef enum {
  ESL_TV_CODEC_H263,
  ESL_TV_CODEC_MPEG4
} esl_TvCodec_e;

/**
 *  @brief The structure defines the video record format
 */
typedef struct {
  esl_TvCodec_e tvVdoCodec;
} esl_TvFormat_t;

/**
 *  @brief The sturcture defines the property of the video recording.
 */
typedef struct {
  esl_TvRes_e          recRes;      /**< Video record resolution 176x144, 352x288 */
  esl_TvFormat_t       recFormat;   /**< Video record format - file type, video/audio codec */
  esl_TvQuality_e      recQuality;  /**< Video record quality: Low, Normal and High */
  esl_TvRecLimit_t     recLimit; /**< TV record limit - size(byte) or time(millisecond) */
  esl_TvFileName_t     fileName; /**< TV record file name (UCS2)*/
  esl_TvPath_e         pathType;    /**< TV record path type       */
  u16                  ch;       /**< TV record channel         */
} esl_TvRecSetting_t;

/**
 *  @brief The sturcture defines streaminf data information.
 */
typedef struct {
  esl_TvEsgType_e   type;              /**< ESG data type */
  u16 dataLen;           /**< Data length*/
  u16 *pData;            /**< Data pointer */
} esl_TvData_t;


/**
 *  @brief The sturcture defines EM data information.
 */
typedef struct {
  u16 dataLen;           /**< Data length*/
  u16 *pData;            /**< Data pointer */
} esl_TvEmData_t;


/**
 *  @brief The sturcture defines the return value for application layer (MMI) query.
 */
typedef struct {
  union {
    esl_TvFileName_t tvFileName;    /**< File name output information response from 'TV_Capture' Request */
    struct {
      u32 totalChn;                 /**< Total capacity of channels in current area */
      esl_TvSignalLv_e singalLv;    /**< Tv signal level */
    } info;                         /**< Information resonse from 'GetInfo' Request */
    struct {
        u16          tfCode;        /**< The tfcode of telegent chip*/
        u16          peakAgc;       /**< The peak of telegent chip*/
        u16          totalGain;     /**< The total gain of telegent chip*/
        bool         colorLock;     /**< The color lock bit of telegent chip*/
    } atvEmInfo;

#ifdef __ATV_CMMB__
    struct {
        u8                     *pCat;
        u32                    nCatSize;
        u8  	                 *pEsg;
        u32 	                 nEsgSize;
        u8  	                 *pCaCardNumber;
        u32                    nCaCardNumberSize;
        esl_TvCaAccessStatus_e  eCaPermission;
        esl_TvSignalLv_e     eSignalLevel;            ///< Indicate the received signal strength indication (RSSI)
    } cmmbTvInfo;
#endif

    struct {
        u32          *pChannelList;   /**< The total channel (CMMB frequency point) pointer array*/
        u16          totalChn;        /**< The number of scanned channel*/
    } cmmbInfo;
    struct {
        u32  ch;                     /**< the scanning channel */
        u8   isExist;                /**< this channel was found and exist in this scanning (TRUE: exist, FALSE: it not scanned*/
        u16  *pChannelName;          /**< for isdbt */
        u32  nChannelNameLen;        /**< for isdbt */
    } scan;                          /**< Information resonse from 'ScanChn' Request */
    struct {
        esl_TvData_t esgData;         /**< Return the ESG data to AP layer*/
        u32          *pChannel;       /**< The scanned channel pointer array*/
        u16          totalChn;    /**< The number of scanned channel*/
    } cmmbScanInfo;
    esl_TvData_t esgData;             /**< ESG data (broadcast)*/
  } param;
} esl_TvInfo_t;

/**
 *  @brief The enumeration defines type of the tv notification.
 */
typedef enum {
  ESL_TV_NOTIFY_SHUTTER_SOUND = 0,      /**< Notify MMI that need to play the capture shutter sound */
  ESL_TV_NOTIFY_CAPTURE_STOP,           /**< Notify MMI that the capturing process is finished */
  ESL_TV_NOTIFY_CAPTURE_ERROR,          /**< Notify MMI that the TV captur recording had an unexpected error */
  ESL_TV_NOTIFY_ESG_DATA,               /**< Notify MMI that DTV ESG data */
  ESL_TV_NOTIFY_EM_DATA,                /**< Notify EM mode data */
  ESL_TV_NOTIFY_SCAN_COMPLETE,          /**< Notify MMI scanning complete  */
  ESL_TV_NOTIFY_SCAN_FAIL,              /**< Notify MMI scanning fail  */
  ESL_TV_NOTIFY_POSITION_UPDATE,        /**< Notify MMI position update */
  ESL_TV_NOTIFY_RECORD_FILE_SAVED,            /**< Notify MMI Record stop */
  ESL_TV_NOTIFY_RECORD_ERROR,           /**< Notify MMI Record error */
  ESL_TV_NOTIFY_RECORD_SPACE_FULL,           /**< Notify MMI Record error */
  ESL_TV_NOTIFY_SET_FREQ_COMPLETE,      /**< Notify MMI set frequency complete  */
  ESL_TV_NOTIFY_SET_FREQ_FAIL,          /**< Notify MMI set frequency fail  */
  ESL_TV_NOTIFY_TIMESHIFT_ERROR,		/**< Notify MMI Time shift error */
  ESL_TV_NOTIFY_ERROR,                  /**< Notify MMI error  */
  ESL_TV_NOTIFY_ALL                     /**< Notify numbers */
} esl_TvNotifyType_e;

/**
 *  @brief The enumeration defines type of the TV error.
 */
typedef enum {
  ESL_TV_ERROR_CAPTURE = 0,         /**< TV error type about file action fail */
  ESL_TV_ERROR_SPACE_FULL,          /**< Notify MMI that space full error */
  ESL_TV_ERROR_UNKNOWN,             /**< TV error type about unknown type */
  ESL_TV_ERROR_SETFREQ,             /**< TV error type about set frequency */
  ESL_TV_ERROR_NONE                 /**< TV error type about no error */
} esl_TvErrorType_e;

/**
 *  @brief The enumeration defines the path of loading shutter sound.
 */
typedef enum {
	ESL_TV_SOUND_DEFAULT = 0,  /**< Using the default sound in MMP */
	ESL_TV_SOUND_DOWNLOAD, /**< Using the sound that load from BB */
	ESL_TV_SOUND_CARD,     /**< Using the sound that save in card */
} esl_TvSoundPath_e;

/**
 *  @brief The sturcture defines the property of the camera shutter sound.
 */
typedef struct {
	esl_TvSoundPath_e  soundPath; /**< The shutter sound path that want to use */
	u8                 *pSound;   /**< PCM data buffer or file name in card (MMI should release buffer after receiving response msg)  */
	u32                soundLen;  /**< The length of PCM or filen name in card */
} esl_TvSound_t;

/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct {
  esl_TvNotifyType_e  notifyTyp;/**< notify type */
  esl_TvErrorType_e   errorTyp;     /**< TV playback error type */
  union {
      u32                  position;     /**< TV playback updated position, only valid when notifyType = ESL_TV_NOTIFY_POSITION_UPDATE */
      esl_TvData_t         esgData;      /**< Return the ESG data to AP layer*/
      esl_TvEmData_t       emData;
  } param;
} esl_TvNotifyInfo_t;

/**
 *  @brief Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param status        : The status return by Multimedia task to know process success or fail.
 * @param pTvGetInfo    : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_TvCb)(u16 senderID, u32 userValue, esl_TvErrCode_e errCode, esl_TvInfo_t *pTvGetInfo);

/**
 *  @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pTvNotifyInfo : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_TvNotifyCb)(u16 senderID, u32 userValue, esl_TvNotifyInfo_t *pTvNotifyInfo);


/**
 *  @brief Callback informatoin structure supported for application layer (MMI)
 */
typedef struct {
  u16        senderID;  /**< Sender ID */
  u32        userValue; /**< Reference value for indicating different sender in same task or check msg response. */
  esl_TvCb   pfnCb;     /**< Call back function that called by Media task after process finished. */
} esl_TvCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct {
  u16              senderID;   /**< Sender ID */
  u32              userValue;  /**< Reference value for indicating different sender in same task or check msg response. */
  esl_TvNotifyCb   pfnNotifyCb;/**< Notification call back function that called by Media task after receiving the notification. */
} esl_TvNotifyCb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/**
 * @brief Software content initial and hardware settings - LCD setting, GPIO control...
 *        This function must be called first before you call any tv interface function.
 *
 * @param tvType          : Indicate the TV type.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Open(esl_TvType_e tvType, esl_TvCb_t *pTvCb);


/**
 * @brief Use to free, re-setting software content or control hardware settings - LCD setting, GPIO control...
 *        This function is paired with esl_TvOpen, it must be called after you finised all of tv fuctions.
 *
 * @param tvType          : Indicate the TV type.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Close(esl_TvType_e tvType, esl_TvCb_t *pTvCb);


/**
 * @brief Get the tv information such as max channel...etc, the info is returned by callback function.
 *
 * @param tvType       : Indicate the TV type.
 * @param pTvCb        : Call back structure, include sender ID, userValue and call back function.
 *                       It uses to send response message that provide by application layer(MMI)
 *                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_GetInfo(esl_TvType_e tvType, esl_TvCb_t *pTvCb);


/**
 * @brief This interface is used for TV preload, it will preload content after call update and it will show out after preview success
 *
 * @param tvType          : Indicate the TV type.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK    : Open success.
 * @return ESL_TV_FAIL  : Open fail.
 */
esl_TvErrCode_e esl_TV_PreLoad(esl_TvType_e tvType, esl_TvCb_t *pTvCb);


/**
 * @brief Set the configurations for JPEG capture or Video recording mode -  Like storage folder name.
 *
 * @param tvType       : Indicate the TV type.
 * @param pConfig      : Indicate Tv configuration setting.
 * @param pTvCb        : Call back structure, include sender ID, userValue and call back function.
 *                       It uses to send response message that provide by application layer(MMI)
 *                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_SetConfig(esl_TvType_e tvType,esl_TvConfig_t *pConfig, esl_TvCb_t *pTvCb);


/**
 * @brief Start or Stop tv preview mode.
 *
 * @param tvPreview       : preview config include channel, on/off preview mode.
 * @param tvDispRegion    : Set display property - display area, rotation..., this parameter is used when tv not turn on.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Preview(esl_TvType_e tvType,esl_TvPreview_t tvPreview, esl_TvDispRegion_t tvDispRegion, esl_TvCb_t *pTvCb);


/**
 * @brief Get the tv engineer mode information such as signal gain code...etc, the info is returned by callback function.
 *
 * @param tvType       : Indicate the TV type.
 * @param pTvCb        : Call back structure, include sender ID, userValue and call back function.
 *                       It uses to send response message that provide by application layer(MMI)
 *                       to inform application layer(MMI) the process in EMA is success or fail.
 * @param frequency    : frequency (CMMB only)
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_GetEmInfo(esl_TvType_e tvType,u16 frequency, esl_TvCb_t *pTvCb);


/**
 * @brief Switch the TV channel.
 *
 * @param ch              : channel number of TV
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_SwitchChannel(esl_TvType_e tvType,u32 ch, esl_TvCb_t *pTvCb);


/**
 * @brief Set the TV frequency.
 *
 * @param setFreq             : set frequency structure
 * @param pTvCb               : Call back structure, include sender ID, userValue and call back function.
 *                              It uses to send response message that provide by application layer(MMI)
 *                              to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_SetFrequency(esl_TvType_e tvType,esl_TvSetFreq_t setFreq, esl_TvCb_t *pTvCb);


/**
 * @brief Scan the TV channel.
 *
 * @param scanConfig      : Scanning config include channel number and action
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI)the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_ScanChannel(esl_TvType_e tvType,esl_TvScanConfig_t scanConfig, esl_TvCb_t *pTvCb);


/**
 * @brief TV sanpshot functionality. Format: JPEG Only.
 *
 * @param tvJpegSetting   : Property setting - Quality...
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Capture(esl_TvType_e tvType,esl_TvJpegSetting_t tvJpegSetting, esl_TvCb_t *pTvCb);


/**
 * @brief Get the file name, after JPEG capture.
 *
 * @param pTvFileName     : File name lengthe and file name buffer, MMI should release file name buffer after receiving response msg.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                          It uses to send response message that provide by application layer(MMI)
 *                          to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_GetFileName(esl_TvType_e tvType,esl_TvFileName_t *pTvFileName, esl_TvCb_t *pTvCb);


/**
 * @brief Set the TV shutter sound.
 *
 * @param isEnable                     : 1:Enable, 0:Disable shutter sound.
 * @param camShutterSound              : PCM sound property: sound path and data buffer.
 * @param pTvCb                        : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_SetShutterSound(esl_TvType_e tvType,u8 isEnable, esl_TvSound_t sound, esl_TvCb_t *pTvCb);


/**
 * @brief This function is used to reset TV window
 *
 * @param  region                       : TV resize region
 * @param  rotateAngle                  : TV resize rotate angle
 * @param  pVdoCb                       : TV call back structure pointer (It will return the media information 'esl_VdoMediaInfo_t')
 *
 * @return ESL_TV_OK                    : function request success
 * @return ESL_TV_FAIL                  : function request fail
 * @return ESL_TV_PARAM_ERROR           : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR       : Can't allocate available memory from OS
 * @return ESL_TV_REJECT                : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                 : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT               : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_ResetWindowReq(esl_TvType_e tvType,esl_TvRegion_t region,esl_TvRotate_e rotateAngle, esl_TvCb_t *pTvCb);


/**
 * @brief This function is used to set position for time shift mode
 *
 * @param  position                     : TV set position
 * @param  pVdoCb                       : TV call back structure pointer
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_SetPositionReq(esl_TvType_e tvType,u32 position, esl_TvCb_t *pTvCb);


/**
 * @brief Register notification for TV capturing and video recording
 *
 * @param notifyType      : The type of register notification.
 * @param notifyCb        : Notification call back to inform MMI when Multimedia task receivd notification.
 * @param pTvCb           : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_RegNotify(esl_TvType_e tvType,esl_TvNotifyType_e notifyType, esl_TvNotifyCb_t notifyCb, esl_TvCb_t *pTvCb);


/**
 * @brief Set the TV command.
 *
 * @param  cmd                         : TV play command (pause/resume ...)
 * @param  pTvCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI)the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Command(esl_TvType_e tvType,esl_TvCmd_e cmd, esl_TvCb_t *pTvCb);


/**
 * @brief TV record start.
 *
 * @param  recSetting                  : Property setting
 * @param  pTvCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI)the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_RecordStart(esl_TvType_e tvType,esl_TvRecSetting_t recSetting, esl_TvCb_t *pTvCb);


/**
 * @brief TV record stop.
 *
 * @param pTvCb                        : Call back structure, include sender ID, userValue and call back function.
 *                                       It uses to send response message that provide by application layer(MMI)
 *                                       to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_RecordStop(esl_TvType_e tvType,esl_TvCb_t *pTvCb);


/**
 * @brief This function is used to set position of TV media file (Time-Shift playback)
 *
 * @param  position                     : TV set position in milli-second
 * @param  pTvCb                        : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
esl_TvErrCode_e esl_TV_SetPositionReq(esl_TvType_e tvType,u32 position, esl_TvCb_t *pTvCb);

/**
 * @brief Canel the TV command.
 *
 * @param  type                          : TV play command (pause/resume ...)
 * @param  pTvCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                                 It uses to send response message that provide by application layer(MMI)
 *                                                 to inform application layer(MMI)the process in EMA is success or fail.
 *
 * @return ESL_TV_OK                   : function request success
 * @return ESL_TV_FAIL                 : function request fail
 * @return ESL_TV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_TV_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_TV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_TV_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_TV_TIMEOUT              : Request no response timeout, this error is returned by call back function

 */
esl_TvErrCode_e esl_TV_Cancel(esl_TvType_e tvType,esl_TvCancelType_e type, esl_TvCb_t *pTvCb);


esl_TvErrCode_e esl_TV_MultiLanguage(esl_TvType_e tvType,esl_TvSoundChannel_e tvSoundChannel, esl_TvCb_t *pTvCb);

#endif /* __ESL_TV_ITF_H__ */

