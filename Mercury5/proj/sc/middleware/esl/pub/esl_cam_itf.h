/**
 *
 * @file    esl_cam_itf.h
 *
 * @brief   This file defines the camera interface for upper layer (like MMI) using.
 *
 * @author  Gary Lu
 * @version $Id: esl_cam_itf.h 16590 2008-11-18 05:33:54Z gary.lu $
 *
 */
#ifndef __ESL_CAM_ITF_H__
#define __ESL_CAM_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "srv_resmgr_mmlcamera_types.h"
#include "srv_resmgr_mmlvideo_types.h"
#include "srv_resmgr_mmlimage_types.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_CAM_ITF__
#define	DefExtern
#else
#define	DefExtern	extern
#endif

#define ESL_CAM_STORAGE_PATH   128 /**< The Maximum length of storage path */


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the return code of the amera interface function.
 */
typedef enum {
  ESL_CAM_OK,               /**< Function complete successfully */
  ESL_CAM_FAIL,			        /**< Function fail */
  ESL_CAM_SKIP,	            /**< Function skip */
  ESL_CAM_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_CAM_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_CAM_REJECT,           /**< Request reject because of other function's confliction */
  ESL_CAM_ABORT,            /**< Request abort because of incorrect sequence */
  ESL_CAM_TIMEOUT           /**< Request command to MMP is no response */
} esl_CamErrCode_e;

/**
 *  @brief The enumeration defines the device camera.
 */
typedef enum {
    ESL_CAM_ID_MAIN, /**< Main sensor */
    ESL_CAM_ID_SUB,  /**< Sub sensor */
    ESL_CAM_ID_ATV   /**< ATV device */
} esl_CamID_e;

/**
 *  @brief The enumeration defines the mode of camera preview.
 */
typedef enum {
    ESL_CAM_PREVIEW_OFF,            /**< Stop camera preview */
    ESL_CAM_PREVIEW_ON,             /**< Start camera preview */
    ESL_CAM_PREVIEW_CAMCORDER_ON,   /**< Start camcorder preview */
    ESL_CAM_PREVIEW_ASPECTRATIO_ON, /**< Start camera aspect ratio preview */
    ESL_CAM_PREVIEW_QRC_ON          /**< Start camera QR Code preview */
} esl_CamPreview_e;

/**
 *  @brief The enumeration defines the mode of camera service for still image or video recording
 */
typedef enum {
    ESL_CAMERA,    /**< Camera still image capturing mode */
    ESL_CAMCORDER, /**< Camcorder video recording mode   */
    ESL_QRC        /**< Camcorder video recording mode   */
} esl_CamMode_e;

/**
 *  @brief The enumeration defines the path of camera service for still image or video recording
 */
typedef enum {
    ESL_CAM_PATH_DIR,     /**< MMI decide folder only */
    ESL_CAM_PATH_PREFIX,  /**< MMI decide pre-fix of file name   */
    ESL_CAM_PATH_ABSOLUTE /**< MMI give full folder path and file name   */
} esl_CamPath_e;

/**
 *  @brief The enumeration defines the path of camera service for still image or video recording
 */
typedef enum {
    ESL_CAM_STORAGE_CARD, /**< Capture/Record to SD Card directly */
    ESL_CAM_STORAGE_BB,   /**< Capture/Record to BB */
    ESL_CAM_STORAGE_NAND  /**< Capture/Record to Nand directly */
} esl_CamStorage_e;

/**
 *  @brief The structure defines the camera/camcorder configuration - sourc, path.
 */
typedef struct {
  esl_CamStorage_e camStorage; /**< Storage selection SD, BB and Nand */
	esl_CamMode_e    camMode;    /**< Recording mode */
  esl_CamPath_e    camPath;    /**< file path in storage */
	u16		           *pCamBuf;   /**< file path or data buf */
	u32		           camLen;     /**< file path or data length */
} esl_CamMedium_t;

/**
 *  @brief The enumeration defines the mode of camera snapshot.
 */
typedef enum {
    ESL_CAM_SINGLE,      /**< Camera capture mode */
	ESL_CAM_ROTATION,  /**< Camera rotatition capture mode */
    ESL_CAM_PHOTOSTICKER,  /**< Camera sticker shot mode */
    ESL_CAM_PANORAMA,      /**< Camera panorama shot mode */
    ESL_CAM_LOMO_4LENS,    /**< Camera lomo 4lens shot mode */
    ESL_CAM_MIRROR         /**< Camera mirror shot mode */
} esl_CamShotMode_e;

typedef enum {
    ESL_CAM_LEFTTORIGHT = 0,   ///< Left to right
    ESL_CAM_RIGHTTOLEFT,       ///< Right to left
    ESL_CAM_TOPTODOWN,         ///< Top to down
    ESL_CAM_DOWNTOTOP,         ///< Down to top
} esl_CamPanoramaMode_e;

typedef enum {
    ESL_CAM_MIRRORMODE_VERTICAL = 0,      ///< Vertical
    ESL_CAM_MIRRORMODE_HORIZONTAL,        ///< Horizontal
} esl_CamMirrorMode_e;

/**
 *  @brief The structure defines the window area property.
 */
typedef struct {
	u16		posX;			/**< Horizontal position of top-left */
  u16		posY;			/**< Vertical position of top-left */
	u16		width;	  /**< Horizontal width */
	u16		height;	  /**< Vertical height */
} esl_CamRegion_t;

/**
 *  @brief The enumeration defines the camera/camcorder rotation angle
 */
typedef enum {
  ESL_CAM_ROTATE_NONE, /**< No Rotation */
  ESL_CAM_ROTATE_90,   /**< Rotate angle 90 degree */
  ESL_CAM_ROTATE_180,  /**< Rotate angle 180 degree */
  ESL_CAM_ROTATE_270   /**< Rotate angle 270 degree */
} esl_CamRotate_e;

/**
 *  @brief The structure defines the Panel display, Preview and OSD windows property.
 */
typedef struct {
	esl_CamRegion_t winPreview; /**< Preview window area */
  esl_CamRegion_t winOSD;     /**< OSD windiow area */
  u16 					  sck;        /**< OSD transparency color */
  u16				  	  transLevel; /**< OSD transparency level */
  esl_CamRotate_e angle;      /**< Preview window rotation angle */
    bool              bLockAE;      /**< Preview AE function is locked or not */
    bool              bLockAWB;     /**< Preview AWB function is locked or not */
} esl_CamDispRegion_t;

/**
 *  @brief The structure defines the camera capture or video recording resolution.
 */
typedef struct {
	u16 width;	/**< Resolution width */
  u16	height;	/**< Resolution height */
} esl_CamSize_t;

/**
 *  @brief The structure defines the camera capture resolution.
 */
typedef enum {
  ESL_CAM_3264_2448,  /* 3264x2448(8M pixel) */
  ESL_CAM_3072_2304,  /* 3072x2304(7M pixel) */
  ESL_CAM_3032_2008,  /* 3032x2008(6M pixel) */
  ESL_CAM_2560_1920,  /* 2560x1920(5M pixel) */
  ESL_CAM_2240_1680,  /* 2240x1680(4M pixel) */
  ESL_CAM_2048_1536,  /* 2048x1536(3M pixel) */
	ESL_CAM_1600_1200,  /* 1600x1200(UXGA) */
	ESL_CAM_1280_1024,	/* 1280x1024(1.3M pixel) */
	ESL_CAM_1024_768,	  /* 1024x768 */
	ESL_CAM_800_600,	  /* 800x600 */
	ESL_CAM_640_480,	  /* 640x480(VGA) */
	ESL_CAM_320_240,	  /* 320x240(QVGA) */
	ESL_CAM_240_320,	  /* 240x320 */
	ESL_CAM_176_220,	  /* 176x220 */
  ESL_CAM_160_120, 	  /* 160x120(QQVGA) */
  ESL_CAM_128_128,    /* For large Contact */
  ESL_CAM_96_96, 	  /* For small Contact */
  ESL_CAM_WALLPAPER_PORTRAIT,  /* Wallpaper (Portait) */
  ESL_CAM_WALLPAPER_LANDSCAPE /* Wallpaper (Landscape) */
} esl_CamCaptureRes_e;

/**
 *  @brief The structure defines the camera video recording resolution.
 */
typedef enum {
  ESL_CAM_VDO_704_576, /* 704x576(4CIF) */
  ESL_CAM_VDO_352_288, /* 352x288(CIF) */
  ESL_CAM_VDO_176_144, /* 176x144(QCIF) */
  ESL_CAM_VDO_128_96,  /* 128x96(SUB-QCIF) */
  ESL_CAM_VDO_640_480, /* 640x480(VGA) */
  ESL_CAM_VDO_320_240, /* 320x240(QVGA) */
  ESL_CAM_VDO_400_240, /* 400x240(WQVGA) */
  ESL_CAM_VDO_480_320, /* 480x320(HVGA) */
  ESL_CAM_VDO_720_576, /* 720x480(DVD_PAL) */
  ESL_CAM_VDO_720_480  /* 720x480(DVD_NTSC) */
} esl_CamRecRes_e;

/**
 *  @brief The enumeration defines the camera capture and camcorder recording quality.
 */
typedef enum {
  ESL_CAM_QUALITY_LOW,     /* Low quality */
	ESL_CAM_QUALITY_NORMAL,  /* Nomal quality */
	ESL_CAM_QUALITY_HIGH     /* High quality */
} esl_CamQuality_e;

/**
 * @brief The enumeration defines the camera rotation angle.
 */
typedef enum {
    ESL_CAL_ROTATION_0,     /* Angle: 0 */
    ESL_CAL_ROTATION_90,    /* Angle: 90 */
    ESL_CAL_ROTATION_180,   /* Angle: 180 */
    ESL_CAL_ROTATION_270    /* Angle: 270 */
} esl_CamRotation_e;


/**
 *  @brief The structure defines the camera snapshot property.
 */
typedef struct {
    esl_CamSize_t  camShotRes;           /**< JPEG resolution */
    u8  burstShootNb; 	                  /**< Continuous shot number */
    u8 	jpegQuality;                      /**< JPEG quality */
    u16 storedPath[ESL_CAM_STORAGE_PATH]; /**< Storage path (Max length is 128 byte) */
    u32 pathLen;                          /**< Storage path length (Max length is 128 byte) */
    u32 captureSize;                      /**< Capture size */
    u16 fileNum;                          /**< Capture file number, Cooper add */

} esl_CamCapture_t;

typedef struct {
  esl_CamStorage_e  storage;
  u16 freeNorSpace;
  u16 resWidth;
  u16 resHeight;
  u16 jpegQuality;
} esl_CamGetQuota_t;

/**
 *  @brief The enumeration defines the Auto White Balance property.
 */
typedef enum {
	ESL_CAM_AWB_ON,          /**< Enable AWB */
	ESL_CAM_AWB_CLOUDY,      /**< Cloudy AWB */
	ESL_CAM_AWB_DAYLIGHT,    /**< Daylight AWB */
	ESL_CAM_AWB_FLUORESCENT, /**< Fluorescent AWB */
	ESL_CAM_AWB_TUNGSTEN     /**< Tungsten AWB */
} esl_CamAWB_e;

/**
 *  @brief The enumeration defines the Auto Exposure algorithm.
 */
typedef enum {
	ESL_CAM_AE_WHOLE_IMAGE,         /**< Whole image algorithm */
	ESL_CAM_AE_CENTRALWIN,          /**< Central window algorithm */
	ESL_CAM_AE_WEIGHTED_CENTRALWIN, /**< Weight Central window algorithm */
	ESL_CAM_AE_CENTRAL_POINT        /**< Central Point algorithm */
} esl_CamAE_e;

/**
 *  @brief The enumeration defines the digital zoom rate.
 */
typedef enum {
	ESL_CAM_ZOOM_MIN,    /**< The MIN Zoom rate */
	ESL_CAM_ZOOM_IN,     /**< Digital Zoom in */
	ESL_CAM_ZOOM_OUT,    /**< Digital Zoom out */
	ESL_CAM_ZOOM_MAX,    /**< The MAX Zoom rate */
	ESL_CAM_ZOOM_DEFAULT /**< Default Zoom rate */
} esl_CamZoom_e;

/**
 *  @brief The enumeration defines the exposure value.
 */
typedef enum {
	ESL_CAM_EV_MIN,    /**< MIN EV value */
	ESL_CAM_EV_INC,    /**< EV increase */
	ESL_CAM_EV_DEC,    /**< EV decrease */
	ESL_CAM_EV_MAX,    /**< MAX EV value */
	ESL_CAM_EV_DEFAULT /**< Default EV value */
} esl_CamEV_e;

/**
 *  @brief The enumeration defines light flicker frequency.
 */
typedef enum {
	ESL_CAM_ANTIFLICKER_OFF,     /**< Antiflicker off */
	ESL_CAM_ANTIFLICKER_ON_60HZ, /**< 60Hz light frequency */
	ESL_CAM_ANTIFLICKER_ON_50HZ  /**< 50Hz light frequency */
} esl_CamAntiFlicker_e;

/**
 *  @brief The enumeration defines camera image effect.
 */
typedef enum {
	ESL_CAM_IMG_NORMAL,       /**< Oil painting effect */
	ESL_CAM_IMG_MONO,         /**< Mono effect */
	ESL_CAM_IMG_SEPIA,        /**< Sepia effect */
	ESL_CAM_IMG_NEGATIVE,     /**< negative effect */
	ESL_CAM_IMG_SKETCH,       /**< Sketch effect */
	ESL_CAM_IMG_OIL_PAINTING, /**< Oil painting effect */
	ESL_CAM_IMG_AMBOS,        /**< Ambos effect */
	ESL_CAM_IMG_MOSAIC,       /**< Mosaic effect */
	ESL_CAM_IMG_ZIPPER,       /**< Zipper effect */
	ESL_CAM_IMG_BLUR,          /**< Blur effect */
	ESL_CAM_IMG_SEPIAGREEN,          /**< sepia green effect */
	ESL_CAM_IMG_SEPIABLUE,          /**< sepia blue effect */
	ESL_CAM_IMG_SEPIARED,          /**< sepia red effect */
	ESL_CAM_IMG_GRAYINVERSION,          /**< gray inversion effect */
	ESL_CAM_IMG_WHITEBOARD,          /**< whiteboard effect */
	ESL_CAM_IMG_COPPERCARVING,          /**< copper carving effect */
	ESL_CAM_IMG_BLUECARVING,          /**< blue carving effect */
	ESL_CAM_IMG_BLACKCARVING,          /**< black carving effect */
	ESL_CAM_IMG_WHITECARVING,          /**< white carving effect */
	ESL_CAM_IMG_CONTRAST,          /**< contrast effect */
	ESL_CAM_IMG_SOLARIZATION,          /**< solarization effect */
	ESL_CAM_IMG_USERDEFINED1,          /**< userdefined effect */
	ESL_CAM_IMG_USERDEFINED2,          /**< userdefined effect */
	ESL_CAM_IMG_USERDEFINED3,          /**< userdefined effect */
	ESL_CAM_IMG_USERDEFINED4,          /**< userdefined effect */
	ESL_CAM_IMG_USERDEFINED5          /**< userdefined effect */

} esl_CamImgEffect_e;

typedef struct
{
    esl_CamImgEffect_e  eCamLomoEffect_UpperLeft;
    esl_CamImgEffect_e  eCamLomoEffect_UpperRight;
    esl_CamImgEffect_e  eCamLomoEffect_LowerLeft;
    esl_CamImgEffect_e  eCamLomoEffect_LowerRight;
} esl_CamLomoInfo_t;

typedef struct
{
    esl_CamPanoramaMode_e    eCamPanoramaType;
    u8                       *pPanoramaBuffer;
    u32                      nPanoramaBufferSize;
    u32                      nTotalPicsNum;
    u32                      nCurrentPicsNum;
} esl_CamPanoramaInfo_t;
/**
 *  @brief The enumeration defines camera night mode.
 */
typedef enum {
	ESL_CAM_NORMAL_MODE, /**< Camera normal mode */
	ESL_CAM_NIGHT_MODE   /**< Camera night moe for low light environment */
} esl_CamNightMode_e;

/**
 *  @brief The enumeration defines flashlight switch.
 */
typedef enum {
	ESL_CAM_FLASHLIGHT_ON,   /**< Turn on flashlight */
	ESL_CAM_FLASHLIGHT_OFF   /**< Turn off flashlight */
} esl_CamFlashlightSwitch_e;

/**
 *  @brief The enumeration defines focus mode.
 */
typedef enum {
	ESL_CAM_FOCUS_MODE_AUTO_FOCUS,   /**< Auto focus */
	ESL_CAM_FOCUS_MODE_TOUCH_TO_FOCUS,   /**< Touch to focus */
	ESL_CAM_FOCUS_MODE_INVALID   /**< focus feature not support */
} esl_CamFocusMode_e;

/**
 *  @brief The enumeration defines videostabilizer switch.
 */
typedef enum {
	ESL_CAM_VIDEOSTABILIZZER_ON,   /**< Turn on VideoStabilizer */
	ESL_CAM_VIDEOSTABILIZZER_OFF   /**< Turn off VideoStabilizer */
} esl_CamVdoStabilizer_e;

/**
 *  @brief The enumeration defines limit type of video recording.
 */
typedef enum {
	ESL_CAM_VDO_SIZE_LIMIT, /**< camcorder recording size limit */
  ESL_CAM_VDO_TIME_LIMIT  /**< camcorder recording time limit*/
}esl_CamVdoLimitType_e;

/**
 *  @brief The enumeration defines video recording limit of size and time.
 */
typedef struct {
  esl_CamVdoLimitType_e vdoLimitType; /** The type of camcorder recording limit. */
  u32                   limitValue;   /** Unit of size limit: Byte, unit of time limit:  millisecond. */
} esl_CamVdoRecLimit_t;

/**
 *  @brief The enumeration defines type of the camera attributions.
 */
typedef enum {
	ESL_CAM_AWB,         /**< AWB */
	ESL_CAM_AE,          /**< AE */
	ESL_CAM_AF,          /**< AF */
	ESL_CAM_ZOOM,        /**< Zoom */
	ESL_CAM_EV,          /**< EV */
	ESL_CAM_ANTIFILCKER, /**< Antifilcker */
	ESL_CAM_IMGEFFECT,   /**< Image effect */
	ESL_CAM_NIGHT,        /**< Camera normal/night mode */
	ESL_CAM_FLASHLIGHT,  /** Flash light */
	ESL_CAM_FOCUSMODE,  /** Focus mode */
    ESL_CAM_VIDEOSTABILIZZER, /**Video Stabilizer*/
} esl_CamAttrType_e;


/**
 *  @brief The structure defines the camera attribution type and value.
 */
typedef struct {
	esl_CamAttrType_e    camAttrType;    /**< Attribution type */
	union {
	esl_CamZoom_e        camZoom;        /**< Zoom */
  esl_CamAWB_e  			 camAWB;         /**< AWB */
	esl_CamAE_e   			 camAE;          /**< AE */
	esl_CamEV_e   			 camEV;          /**< EV */
	esl_CamAntiFlicker_e camAntiFlicker; /**< Antifilcker */
	esl_CamImgEffect_e   camImgEffect;   /**< Image effect */
  esl_CamNightMode_e   camNightMode;   /**< Camera normal/night mode */
  esl_CamFlashlightSwitch_e     camFlashlightSwitch;    /**< Flashlight switch */
  esl_CamFocusMode_e            camFocusMode;          /**< Focus mode */
  esl_CamVdoStabilizer_e  camVideoStabilizer; /**<VideoStabilizer Switch*/
	} type;
} esl_CamAttr_t;

/**
 *  @brief The structure defines the camera GPS type.
 */
typedef struct {
  u32 latitudeRef;     /**< the value is 0x4E (N) or 0x53 (S) */
  u32 latitudeDegNum;  /**< degree numerator */
  u32 latitudeDegDen;  /**< degree denominator */
  u32 latitudeMinNum;  /**< minute numerator */
  u32 latitudeMinDen;  /**< minute denominator */
  u32 latitudeSecNum;  /**< second numerator */
  u32 latitudeSecDen;  /**< second denominator */
  u32 longitudeRef;    /**< the value is 0x45 (E) or 0x57 (W) */
  u32 longitudeDegNum; /**< degree numerator */
  u32 longitudeDegDen; /**< degree denominator */
  u32 longitudeMinNum; /**< minute numerator */
  u32 longitudeMinDen; /**< minute denominator */
  u32 longitudeSecNum; /**< second numerator */
  u32 longitudeSecDen; /**< second denominator */
} esl_CamGpsData_t;

typedef struct {
  bool             isGps;      /**< 0: No gps data, 1: Have gps data */
  esl_CamGpsData_t camGpsData; /**< GPS data */
} esl_CamGpsInfo_t;

typedef enum {
  ESL_ORIENTATION_TOP_LEFT     = 0x00, /**< Top-Left Orientation */
  ESL_ORIENTATION_TOP_RIGHT    = 0x01, /**< Top-Right Orientation */
  ESL_ORIENTATION_BOTTOM_RIGHT = 0x02, /**< Bottom-Right Orientation */
  ESL_ORIENTATION_BOTTOM_LEFT  = 0x03, /**< Bottom-Left Orientation */
  ESL_ORIENTATION_LEFT_TOP     = 0x04, /**< Left-Top Orientation */
  ESL_ORIENTATION_RIGHT_TOP    = 0x05, /**< Right-Top Orientation */
  ESL_ORIENTATION_RIGHT_BOTTOM = 0x06, /**< Right-Bottom Orientation */
  ESL_ORIENTATION_LEFT_BOTTOM  = 0x07  /**< Left-Bottom Orientation */
} esl_CamOrientationInfo_e;

typedef struct {
  esl_CamGpsInfo_t         camGpsInfo; /**< Exif GPS information */
  esl_CamOrientationInfo_e camOriInfo; /**< Exif Orientation information */
} esl_CamExifInfo_t;

/**
 *  @brief The enumeration defines the path of loading shutter sound.
 */
typedef enum {
	ESL_CAM_SOUND_DEFAULT,  /**< Using the default sound in MMP */
	ESL_CAM_SOUND_DOWNLOAD, /**< Using the sound that load from BB */
	ESL_CAM_SOUND_CARD,     /**< Using the sound that save in card */
} esl_CamSoundPath_e;

/**
 *  @brief The structure defines the property of the camera shutter sound.
 */
typedef struct {
	esl_CamSoundPath_e soundPath; /**< The shutter sound path that want to use */
	u8                 *pSound;   /**< PCM data buffer or file name in card (MMI should release buffer after receiving response msg)  */
	u32                soundLen;  /**< The length of PCM or filen name in card */
} esl_CamSound_t;

/**
 *  @brief The structure defines the property of the jpeg capture.
 */
typedef struct {
    esl_CamCaptureRes_e    eCamCaptureRes;    /**< Camera snapshot resolution */
    esl_CamQuality_e       eJpegQuality;      /**< JPEG quality: Low, Normal and High */
    esl_CamRotation_e      eAngle;            /**< Angle (0:0, 1:90, 2:180, 3:270) for rotation capture use only */
    esl_CamShotMode_e      eMode;             /**< Single, continuous, or sticker shot mode. */
    esl_CamMirrorMode_e    eCamMirrorInfo;    /** < * vertical mirror or horizontal mirror. */
    esl_CamLomoInfo_t      tCamLomoInfo;      /** < lomo effect attributes info. */
    esl_CamPanoramaInfo_t  tCamPanoramaInfo;  /** < panorama info. */
    u8                     nSkipFrameNb;      /**< 0 ~ 63: skip 0 ~ 63 frame, default = 5 */
    u8                     nContPicNb;        /**< 0 ~ 15: taking 1 ~ 16 pics, default = 3 */
    esl_CamExifInfo_t      tCamExifInfo;      /**< Exif information */
    bool                   bCamSound;         /**< 1: enable shutter sound, 0: disable shutter sound */
    esl_CamSound_t         tCamSound;         /**< Shutter information */
    bool                   bCamStablized;    /**< 1: enable camera stablized, 0: disable camera stablized */
	struct {
		u16 pathLen;                     /**< Storage path length */
		u16 *pPathName;                   /**< Storage path */
	} path;
} esl_CamJpegSetting_t;

/**
 *  @brief The structure defines the property of the QR Code recording.
 */
typedef struct {
	u32 qrCodeLimit; /**< QR Code recording time limit(millisecond) */
} esl_CamQRCSetting_t;

/**
 *  @brief The enumeration defines the size and data type of QR Code.
 */
typedef enum {
	ESL_CAM_QRC_SIZE, /**< get QR Code size */
  ESL_CAM_QRC_DATA  /**< get QR Code data */
} esl_CamQRCInfoType_e;

/**
 *  @brief The enumeration defines header of QR Code data.
 */
typedef enum {
  ESL_CAM_QRC_TYPE_SIZE = 0x00,     /**< QR Code data size */
	ESL_CAM_QRC_TYPE_NUM = 0x01,      /**< Numeric */
  ESL_CAM_QRC_TYPE_ALPHANUM = 0x02, /**< Alphanumeric */
  ESL_CAM_QRC_TYPE_CBYTE = 0x04,    /**< Character */
  ESL_CAM_QRC_TYPE_KANJI = 0x08,    /**< Kanji */
  ESL_CAM_QRC_TYPE_NONE = 0xFF
} esl_CamQRCHeaderType_e;

/**
 *  @brief The structure defines the getting type of the QR Code (size or data).
 */
typedef struct {
	esl_CamQRCInfoType_e camQRCInfoType; /**< To get QR code size or data selection */
  u8                   *pCamQRCBuf;    /**< Data buffer (MMI should release this buffer after receiving response msg) */
  u32                  bufLen;         /**< Allocated buf size */
} esl_CamGetQRC_t;

/**
 *  @brief The structure defines the QR Code data package of header, length and buffer.
 */
typedef struct {
  esl_CamQRCHeaderType_e headerTyp; /**< Header of QR Code data */
  u16 dataLen;                      /**< Length of QR Code data */
	u8  *pDataBuf;                    /**< Data buffer */
} esl_CamQRCData_t;

#define MAX_QRC_PACKAGE_NUM 5 /**< Max package number of QR Code data */

/**
 *  @brief The structure defines the returns of QR Code data.
 */
typedef struct {
  u8 packNum;                                        /**< Indicate how many packages of QR code data */
  esl_CamQRCData_t camQRCData[MAX_QRC_PACKAGE_NUM];  /**< QR code data package */
} esl_CamQRCInfo_t;

/**
 *  @brief The enumeration defines video codec format.
 */
typedef enum {
  ESL_CAM_VDO_CODEC_H263,
  ESL_CAM_VDO_CODEC_MPEG4
} esl_CamVdoCodec_e;

/**
 *  @brief The enumeration defines audio codec format.
 */
typedef enum {
  ESL_CAM_AUD_CODEC_AMR_NB,
  ESL_CAM_AUD_CODEC_AMR_WB
} esl_CamAudCodec_e;

/**
 *  @brief The enumeration defines video file format.
 */
typedef enum {
  ESL_CAM_VDO_FILE_TYPE_3GP,
  ESL_CAM_VDO_FILE_TYPE_MP4
} esl_CamVdoFileType_e;

/**
 *  @brief The structure defines the video record format
 */
typedef struct {
  esl_CamVdoCodec_e camVdoCodec;
  esl_CamAudCodec_e camAudCodec;
  esl_CamVdoFileType_e camVdoFileType;
} esl_CamVdoFormat_t;

/**
 *  @brief The structure defines the property of the video recording.
 */
typedef struct {
	esl_CamRecRes_e      vdoRecRes;   /**< Video record resolution 176x144, 352x288 */
	esl_CamQuality_e     vdoQuality;  /**< Video record quality: Low, Normal and High */
  esl_CamVdoRecLimit_t vdoRecLimit; /**< Video record limit - size(byte) or time(millisecond) */
  esl_CamVdoFormat_t   vdoRecFormat; /**< Video record format - file type, video/audio codec */
  bool                 vdoRecAudio; /**< Video record sound setting - 0: no sound, 1: sound. */
	struct{
		u16 pathLen;              /**< Storage path length */
		u16 *pPathName;            /**< Storage path */
	} path;
} esl_CamVdoSetting_t;

/**
 *  @brief The structure defines the file name and length of the last jpeg or 3gp file.
 */
typedef struct {
	u16 outLen;        /**< file name length */
	u32 fileNameOutAddr; /**< file name buffer address (MMI should release file name buffer after receiving response msg) */
} esl_CamFileName_t;

/**
 *  @brief The enumeration defines the image type.
 */
typedef enum {
	ESL_CAM_IMAGE_RAW, /**< Raw data image */
	ESL_CAM_IMAGE_JPEG /**< Jpeg data image */
} esl_CamImgType_e;

/**
 *  @brief The structure defines the image data and length of the last jpeg or 3gp file.
 */
typedef struct {
  esl_CamImgType_e imgType; /**< image type */
	u32 outLen;   /**< image buffer length */
	u32 imgOutAddr; /**< image buffer address (MMI should release file name buffer after receiving response msg) */
} esl_CamImg_t;

/**
 *  @brief The enumeration defines type of the camera status.
 */
typedef enum {
	ESL_CAM_STATUS_SETTING, /**< Setting status selection */
	ESL_CAM_DETECT_SENSOR   /**< Detect sensor selection */
} esl_CamStatus_e;

/**
 *  @brief The enumeration defines the camera recoding save mode.
 */
typedef enum
{
	ESL_CAM_DEFERRING_SAVE,     /**< Deferring Save, defer the decision to save or abort the clip */
	ESL_CAM_DECIDING_SAVE,      /**< Deciding Save */
	ESL_CAM_DEFERRING_CHECK     /**< Deferring Check, check if there is clip not saved completely */

} esl_CamRecSaveMode_e;
/*
typedef enum
{
    ESL_CAM_SENSORSTATUS_ALL = 0,    ///< Primary and secondary sensors are available
    ESL_CAM_SENSORSTATUS_PRIMARY,    ///< Only primary sensor is available
    ESL_CAM_SENSORSTATUS_SECONDARY,  ///< Only secondary sensor is available
    ESL_CAM_SENSORSTATUS_NONE,       ///< No sensor is available
    ESL_CAM_SENSORSTATUS_NUM
} esl_CamSensorStatus_e;
*/
/**
 *  @brief The structure defines camera recording save action.
 */
typedef struct
{
    u8  saveClip;       /**< Decision (0: Cancel to save the clip, 1: Confirm to save the clip) */

} esl_CamRecSaveAction_t;

/**
 *  @brief The structure defines camera recording save information
 */
typedef struct
{
    esl_CamRecSaveMode_e    recSaveMode;    /**< Camera recoding save mode */
    esl_CamRecSaveAction_t  recSaveAction;  /**< Camera recoding save information */

} esl_CamRecSaveInfo_t;


/**
 *  @brief The structure defines the property of the camera zoom.
 */
typedef struct {
    u8                  steps;      /**< Number of Zoom Level Step, 0 = 1 step, 1 = 2 steps, ..., 63 = 64 steps */
    u8                  status;     /**< Zoom Level Setting Status */
    u8                  ratio;      /**< Zoom Ratio (i.e. 10~40, 10=1x) */
} esl_CamZoomInfo_t;

/**
 *  @brief The structure defines the property of getting camera zoom info. [Cooper add]
 */
typedef struct {
    esl_CamRotate_e     rotate;     /**< Rotate 90 degree (0: No, 1: Yes) */
    u8                  mode;       /**< Mode (0: Simple <Format 0>, 1: Advanced <Format 1>) */
    u16                 width;      /**< 16-bit width of capture size */
    u16                 height;     /**< 16-bit height of capture size */
} esl_CamGetZoomInfo_t;

/**
 *   @brief      Get Camera Information
*/
typedef MmlCameraZoomInfo_t esl_CameraZoomInfo_t;
/**
 *  @brief The structure defines the camera zoom info with the specified resolution.
 */
/*
typedef struct
{
    u16     nResolutionType;
    u16     nWidth;                 // Output width in pixels
    u16     nHeight;                // Output height in pixels
    u16     nMaxZoomLevel;          // Maximum zoom level (1000: 1x, 1300: 1.3x, ..., 4000: 4x)
    u16     nNumZoomLevelSteps;     // Number of zoom level steps supported (0: 1 step, 1: 2 steps, ..., 63: 64 steps)
    u16     bMultiShootSupported;   ///< Multi shoot supported ?
} esl_CameraZoomInfo_t;
*/
/**
 *  @brief The structure defines the camera info for the application to query.
 */
typedef struct
{
    u16                        nZoomInfoListSize;          ///< Size in elements of the pZoomInfoList
    esl_CameraZoomInfo_t       *pZoomInfoList;             ///< Pointer to a list of zoom info queried
    u16                        nSensorWidth;               ///< Sensor width
    u16                        nSensorHeight;              ///< Sensor height
    u16                        nMaxInterpolatedWidth;      ///< Maximum interpolated width
    u16                        nMaxInterpolatedHeight;     ///< Maximum interpolated height
    u16                        bImageEffectSupported;      ///< Special image effect supported ?
    u16                        bSensorImageEffectSupported;    ///< Sensor special image effect supported ?
    u16                        bVideoStabilizerSupported;      ///< Video stabilizer supported ?
    u16                        bAutoFocusSupported;             ///< Auto focus supported ?
    u32                        nImageEffectSupported;          ///< Special image effects supported (chip + sensor)
    MmlCameraSensorStatus_e    eSensorStatus;                  ///< Result of sensor detection
} esl_CamCameraInfo_t;

/**
 *   @brief      Video recording capability
*/
typedef MmlVideoRecordingCapability_t   esl_CamRecordingCapability_t;

/**
 *  @brief      Image capture capability
*/
typedef MmlImageCaptureCapability_t     esl_CamCaptureCapability_t;

/**
 *  @brief The structure defines the return value for application layer (MMI) query.
 */
typedef struct {
    //u16 typMsg;   /**< Primitive/Message requested ID */
    union {
        esl_CamFileName_t camFileName; /**< File name output (MMI should release file name buffer after receiving response msg) */
        esl_CamImg_t      camImg;      /**< Image output (MMI should release file name buffer after receiving response msg) */
        esl_CamQRCInfo_t  camQRCInfo;  /**< QR Code information data output (MMI should release data buffer after receiving response msg) */
        esl_CamZoomInfo_t   camZoomInfo; /**< Zoom information, Cooper add */
        u32               camRemainQuota;
        esl_CamCameraInfo_t   camCameraInfo;
        esl_CamCaptureCapability_t tCamCaptureCapability;
        esl_CamRecordingCapability_t tCamRecordingCapability;
        struct {
            u8 camSensorSts;    /**< Sensor Detect (0: No sensor,   1: Detected) */
            u8 camDevSts;       /**< CAM Device (0: Idle,   1: Busy) */
            u8 camPwrSts;       /**< Power Switch Value (0: off,   1: on) */
        } status;
    } param;
} esl_CamInfo_t;

/**
 *  @brief The enumeration defines type of the camera notification.
 */
typedef enum {
    ESL_CAM_PLAY_SHUTTER_SOUND,  /**< Notify MMI that need to play the capture shutter sound */
    ESL_CAM_CAPTURE_STOP,        /**< Notify MMI that the capturing process is finished */
    ESL_CAM_VDO_POSITION_UPDATE, /**< Notify MMI that need to draw the progress bar when video recording */
    ESL_CAM_VDO_REC_STOP,        /**< Notify MMI that the video recording process is finished(stop) */
    ESL_CAM_VDO_REC_SPACE_FULL,  /**< Notify MMI that the space of storage is full when video recording */
    ESL_CAM_QRC_REC_STOP,        /**< Notify MMI that the QR code decoding process is finished */
    ESL_CAM_REC_ERROR,           /**< Notify MMI that the camera capture/camcorder recording had an unexpected error */
    ESL_CAM_VDO_REC_SAVE,        /**< Notify MMI that the camera recording save completely */
    ESL_CAM_VDO_REC_DELETE,      /**< Notify MMI that the camera recording delete completely */
    ESL_CAM_VDO_REC_ABORT,       /**< Notify MMI that the camera recording abort completely */
    ESL_CAM_AUTOFOCUS_COMPLETE, /**< Notify MMI that the camera do auto focus completely */
    ESL_CAM_MOTION_DETECT,       /**< Notify MMI that Camera motion detection */
    ESL_CAM_NOTIFY_ALL,
    ESL_CAM_NOTIFY_NUM = ESL_CAM_NOTIFY_ALL /**< Notify numbers */
} esl_CamNotifyType_e;

/**
 *  @brief The enumeration defines type of the camera/camcorder recording error.
 */
typedef enum {
    ESL_CAM_REC_ERROR_NONE,                 /**< Notify MMI that no error */
    ESL_CAM_REC_ERROR_SPACE_FULL,           /**< Notify MMI that space full error */
    ESL_CAM_REC_ERROR_UNKNOW,               /**< Notify MMI that error unknow */
    ESL_CAM_REC_ERROR_TIMEOUT,              /**< Notify MMI that time's up (for QR Cdoe only) */
    ESL_CAM_REC_ERROR_NOT_SUPPORT,          /**< Notify MMI that format is unsupport (for QR Cdoe only) */
    ESL_CAM_REC_ERROR_SDCARD_NOT_DETECTED,  /**< Notify MMI that SD card not detected */
    ESL_CAM_REC_ERROR_SAVE_COMPLETE,        /**< Notify MMI that saved completely before deferring save */
    ESL_CAM_REC_ERROR_OVER_SIZE,            /**< Notify MMI that recording over size limitation */
    ESL_CAM_REC_ERROR_MEMORY_INSUFFICIENCY, /**< Notify MMI that memory isn't enough for the command */
    ESL_CAM_REC_ERROR_NUM                   /**< Error numbers */
} esl_CamRecError_e;

/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct {
    esl_CamNotifyType_e     camNotifyType;  /**< message primitive */
    union {
        u32                 position;       /**< video recording position for ESL_CAM_VDO_POSITION_UPDATE */
        esl_CamRecError_e   recError;       /**< error type for ESL_CAM_REC_ERROR */
	} notify;
} esl_CamNotifyInfo_t;

/**
 *  @brief Call back function, MMI need to provide the function entity
 *
 * @param senderID		  : Sender task id.
 * @param userValue      : Reference value for indicating different sender in same task or check msg response.
 * @param status            : The status return by Multimedia task to know process success or fail.
 * @param pCamGetInfo : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_CamCb)(u16 senderID, u32 userValue, esl_CamErrCode_e errCode, esl_CamInfo_t *pCamGetInfo);

/**
 *  @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID		  : Sender task id.
 * @param userValue      : Reference value for indicating different sender in same task or check msg response.
 * @param pCamGetInfo : Notification value return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_CamNotifyCb)(u16 senderID, u32 userValue, esl_CamNotifyInfo_t *pCamGetInfo);


/**
 *  @brief Callback informatoin structure supported for application layer (MMI)
 */
typedef struct {
	u16        senderID;	/**< Sender ID */
	u32        userValue; /**< Reference value for indicating different sender in same task or check msg response. */
	esl_CamCb  pfnCb;     /**< Call back function that called by Media task after process finished. */
} esl_CamCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct {
	u16              senderID;	 /**< Sender ID */
	u32              userValue;  /**< Reference value for indicating different sender in same task or check msg response. */
	esl_CamNotifyCb  pfnNotifyCb;/**< Notification call back function that called by Media task after receiving the notification. */
} esl_CamNotifyCb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/



#endif /* __ESL_CAM_ITF_H__ */

