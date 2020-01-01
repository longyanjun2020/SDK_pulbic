/**
 *
 * @file    esl_gss_itf.h
 *
 * @brief   This module defines Enchaced Service Layer interface of Gss service
 *
 * @author  Jack Hsieh
 * @version $Id: esl_gss_itf.h 10857 2008-05-22 10:09:54Z jack.hsieh $
 *
 */
#ifndef __ESL_GSS_ITF_H__
#define __ESL_GSS_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "srv_resmgr_mmlgame_types.h"
#include "srv_resmgr_mmlimage_types.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_GSS_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the ESL gss error code
 */
typedef enum {
  ESL_GSS_PARAMETER_ERROR  = (s32)-6,   /**< Bad parameters*/
  ESL_GSS_WRONG_HANDLE,                 /**< Gss image decode wrong decode handle */
  ESL_GSS_NOT_ENOUGH_MEMORY,            /**< Gss image decode memory (output buffer ?) not enough*/
  ESL_GSS_TOO_MUCH_EXECUTING_INSTANCE,  /**< Gss image decode too much executing instance*/
  ESL_GSS_DEC_ERR,                      /**< Gss image decode error*/
  ESL_GSS_FORMAT_UNSUPPORT,             /**< Gss image decode format not support*/
  ESL_GSS_FAIL,                         /**< Gss image decode error ( keep this be 0)*/
  ESL_GSS_OK,                           /**< Gss image decode success = 1*/
  ESL_GSS_SUCCESS_WAITING,              /**< By Montage, caller wait for IMGCODEC_MSG_DECODE_DONE or IMGCODEC_MSG_ERROR or callback function*/
  ESL_GSS_SUCCESS_MORE_FRAMES,          /**< GIFA, Caller wait for IMGCODEC_MSG_UPDATE_GIFA message*/
  ESL_GSS_REJECT,                       /**< Request reject because of other function's confliction */
  ESL_GSS_ABORT,                         /**< Request abort because of incorrect sequence */
  ESL_GSS_FILE_CORRUPT,				/**< File Corrupt >*/
  ESL_GSS_FILE_NOT_EXIST,			/**< File not exist*/
  ESL_GSS_FILE_SIZE_OVERFLOW           /**< File size over flow*/
} esl_GssErrCode_e;

/**
 *  @brief The enumeration defines the Gss file format
 */
typedef enum {
  ESL_GSS_JPG,              /**< Format Jpeg */
  ESL_GSS_BMP,              /**< Format BMP */
  ESL_GSS_PNG,              /**< Format PNG */
  ESL_GSS_GIF,              /**< Format GIF include animation GIF  */
  ESL_GSS_UNKNOW_FORMAT      /**<Unknown image format */
} esl_GssFormat_e;

/**
 *  @brief The enumeration defines the Gss file format
 */
typedef enum {
  ESL_GSS_EMU_BIN_DEFAULT,           /**< Bin is in the default path  */
  ESL_GSS_EMU_BIN_FILE,              /**< Bin is in the storage  */
  ESL_GSS_EMU_BIN_DATA,              /**< Data Bin*/
  ESL_GSS_EMU_BIN_NUM
} esl_GssEmuBinType_e;

typedef enum {
  ESL_GSS_LAYER_VDO,             /**< Layer V0 */
  ESL_GSS_LAYER_G0,              /**< Layer G0 */
  ESL_GSS_LAYER_G1,              /**< Layer G1 */
  ESL_GSS_LAYER_G3D,             /**< Layer G3D  */
  ESL_GSS_LAYER_UNKNOW           /**<Unknown image format */
} esl_GssLayer_e;

/**
 *  @brief The enumeration defines the Gss color format
 */
typedef enum {
  ESL_GSS_COLOR_RGB_565,              /**< RGB 565 format */
  ESL_GSS_COLOR_YUV_420,              /**< YUV 420 format */
  ESL_GSS_COLOR_UNKNOW_FORMAT         /**< Unknown pixel format */
} esl_GssColorFormat_e;

/**
 *  @brief The enumeration defines the Gss render type
 */
typedef enum {
  ESL_GSS_RENDER_PALETTE,        /**< PALETTE render type */
  ESL_GSS_RENDER_EM_TEST_LCD,    /**< EM TEST Display */
  ESL_GSS_RENDER_EMU,
  ESL_GSS_RENDER_MAX             /**< maximum render type */
} esl_GssRenderType_e;

/**
 *  @brief The enumeration defines the Gss get information type
 */
typedef enum {
  ESL_GSS_EMU_HASH_DATA = 0,        /**< EMU hash data */
  ESL_GSS_EMU_VERSION,              /**< EMU version */
  ESL_GSS_EMU_GAME_STATUS_SIZE,     /**< EMU Status Size */
  ESL_GSS_EMU_INFO_ALL,             /**< EMU all information */
  ESL_GSS_EMU_NUM
} esl_GssGetInfoType_e;

/**
 *  @brief The enumeration defines the tv capture recording quality.
 */
typedef enum {
  ESL_GSS_QUALITY_LOW,     /* Low quality */
  ESL_GSS_QUALITY_NORMAL,  /* Nomal quality */
  ESL_GSS_QUALITY_HIGH     /* High quality */
} esl_GssQuality_e;

/**
 *  @brief The enumeration defines the tv rotation angle
 */
typedef enum {
  ESL_GSS_ROTATE_NONE, /**< No Rotation */
  ESL_GSS_ROTATE_90,   /**< Rotate angle 90 degree */
  ESL_GSS_ROTATE_180,  /**< Rotate angle 180 degree */
  ESL_GSS_ROTATE_270,  /**< Rotate angle 270 degree */
  ESL_GSS_ROTATE_NUM
} esl_GssRotate_e;

/**
 *  @brief The structure defines the tv capture resolution.
 */
typedef enum {
  ESL_GSS_1024_768,   /* 1024x768 */
  ESL_GSS_800_600,    /* 800x600 */
  ESL_GSS_640_480,    /* 640x480(VGA) */
  ESL_GSS_320_240,    /* 320x240(QVGA) */
  ESL_GSS_240_320,    /* 240x320(Wallpaper) */
  ESL_GSS_176_220,    /* 176x220(Wallpaper)*/
  ESL_GSS_160_120,    /* 160x120(QQVGA) */
  ESL_GSS_96_96       /* For Contact */
} esl_GssCaptureRes_e;

/**
 *  @brief The structure sync lock type to reserve buffer.
 */
typedef enum {
  ESL_GSS_SYNC_OSD,   /* SYNC LOCK OSD TYPE */
} esl_GssSyncTyp_e;

/**
 *  @brief The structure sync lock status to reserve buffer.
 */
typedef enum {
  ESL_GSS_SYNC_STATUS_LOCK,     /* SYNC LOCK TYPE */
  ESL_GSS_SYNC_STATUS_UNLOCK,   /* SYNC UNLOCK TYPE */
} esl_GssSyncStatus_e;



/**
 *  @brief The structure defines the Graphic engine type.
 */
typedef enum {
  ESL_GSS_GE_SCALE,   /* Scale up/down */
  ESL_GSS_GE_MAX      /* GE max type */
} esl_GssGEtype_e;


/**
 *  @brief The structure defines the display quality.
 */
typedef enum {
  ESL_GSS_DQ_CONTRAST,        /* Contrast */
  ESL_GSS_DQ_BRIGHTNESS,      /* Brightness */
  ESL_GSS_DQ_SATURATION,      /* Saturation */
  ESL_GSS_DQ_GAMMAS,          /* Gamma */
  ESL_GSS_DQ_SHARPNESS,       /* Sharpness*/
  ESL_GSS_DQ_BEVEL,           /* Black level */
  ESL_GSS_DQ_WEVEL,           /* White level */
} esl_GssDisplayQualityType_e;

/**
 *  @brief The enumeration defines the Gss encode destination type
 */
typedef enum {
  ESL_GSS_ENCODE_TO_FILE = 0,    /**< Gss encode to file */
  ESL_GSS_ENCODE_TO_MEM,         /**< Gss encode to memory*/
} esl_GssEncodeDstType_e;

/**
 *  @brief The enumeration defines the path of Gss service for still image
 */
typedef enum {
    ESL_GSS_PATH_DIR,     /**< MMI decide folder only */
    ESL_GSS_PATH_PREFIX,  /**< MMI decide pre-fix of file name   */
    ESL_GSS_PATH_ABSOLUTE /**< MMI give full folder path and file name   */
} esl_GssPath_e;

/**
 *  @brief Gss buffer information definition for first frame decode
 */
typedef struct  {
 u8   *pBuffer;                /**< Gss decode buffer point*/
 u32   bufferLen;              /**< Gss decode buffer length*/
} esl_GssBufferInfo_t;

/**
 *  @brief Gss buffer information definition for EMU emulator
 */
typedef struct  {
 u32   hashData;                /**< EMU hash data*/
} esl_GssEmuEmuInfo_t;

/**
 *  @brief The structure defines the window area property
 */
typedef struct {
  u16   posX;     /**< The origin (x=0) is top-left in rotate 0 (Horizontal), top-right in rotate 90 (Vertical)...etc*/
  u16   posY;     /**< The origin (y=0) is top-left in rotate 0 (Vertical), top-right in rotate 90 (Horizontal)...etc*/
  u16   width;    /**< Horizontal width */
  u16   height;   /**< Vertical height */
} esl_GssRegion_t;

/**
 *  @brief The structure defines the gssfilename information
 */
typedef struct {
  esl_GssFormat_e   fileFormat;       /**< Gss file format */
  u16               *pFileName;       /**< Gss file name in UCS2 format */
  u16               fileNameLen;      /**< Gss file name buffer length (number of bytes)*/
} esl_GssFileInfo_t;

/**
 *  @brief The enumeration defines the DQ action.
 */
typedef enum {
	ESL_GSS_DQ_MAX,      /**< Max display value */
	ESL_GSS_DQ_CURRENT  /**< Current display value */
} esl_GssDQType_e;


/**
 *  @brief The structure defines the bin source
 */
typedef struct {
  esl_GssEmuBinType_e   binType;       /**< Gss bin format type*/
  union {
    esl_GssBufferInfo_t binBuffer;
    struct {
     u16           *pEmuBinPath;          /**< EMU Bin file name in UCS2 format */
     u16           nEmuBinPathLen;        /**< EMU Bin file name buffer length (file name length (UCS2))*/
    } binFile;
  }param;
} esl_GssBinInfo_t;

/**
 *  @brief The structure defines the gssmedia file information
 */
typedef struct {
  esl_GssFormat_e    format;      /**< Gss format */
  u16                height;      /**< Gss resolution height */
  u16                width;       /**< Gss resolution width */
} esl_GssMediaInfo_t;

/**
 *  @brief The structure defines the palette configuration
 */
typedef struct {
  u32                   number;          /**< palette number of entry*/
  esl_GssColorFormat_e  format;          /**< palette color format*/
  esl_GssBufferInfo_t   paletteBuffer;   /**< palette buffer */
} esl_Gss_PaletteConfig_t;

/**
 *  @brief The structure defines the EMU emulator configuration
 */
typedef struct {
  esl_GssBufferInfo_t   gameStatus;             /**< The structure defines the EMU game status (status buffer and status buffer lens) */
  esl_GssBinInfo_t      binInfo;                /**< Gss bin infomation (only support in B2)*/
  u16                   *pEmuFileName;          /**< EMU Game file name in UCS2 format */
  u16                   nEmuFileNameLen;        /**< EMU Game file name buffer length (file name length (UCS2))*/
} esl_Gss_EmuConfig_t;

/**
 *  @brief The structure defines the render configuration
 */
typedef struct {
  esl_GssRenderType_e   type;       /**< Render type */
  esl_GssRegion_t       region;     /**< Render region */
  esl_GssRotate_e       angle;      /**< Rotate angle */
  union {
  esl_Gss_PaletteConfig_t paletteConfig;
  esl_Gss_EmuConfig_t     tEmuConfig;
  }param;
} esl_GssRenderConfig_t;

/**
 *  @brief The structure defines the game get information parameter
 */
typedef struct {
  esl_GssGetInfoType_e type;               /**< Gss get information type */
  esl_GssBinInfo_t     binInfo;            /**< Gss bin infomation (only support in B2)*/
    struct {
     u16           *pEmuFileName;          /**< EMU Game file name in UCS2 format */
     u16           nEmuFileNameLen;         /**< EMU Game file name buffer length (file name length (UCS2))*/
    } gameParam;                           /**< Game get information parameter */
} esl_GssGetInfoParam_t;


/**
 *  @brief The structure defines the render stop configuration
 */
typedef struct {
  esl_GssRenderType_e   type;       /**< Render type */
  union {
  esl_GssBufferInfo_t   tEmuStopConfig;
  }param;
} esl_GssRenderStopConfig_t;

/**
 *  @brief The structure defines the render input
 */
typedef struct {
  esl_GssRenderType_e   type;       /**< Render type */
  union {
    u16 nEmuKey;                  /**< EMU emulator bitwise key */
                                    /**< EMU_KEY_A       0x0001 */
                                    /**< EMU_KEY_B       0x0002 */
                                    /**< EMU_KEY_TURBO_A 0x0004 */
                                    /**< EMU_KEY_TURBO_B 0x0008 */
                                    /**< EMU_KEY_START   0x0010 */
                                    /**< EMU_KEY_SELECT  0x0020 */
                                    /**< EMU_KEY_RIGHT   0x0040 */
                                    /**< EMU_KEY_LEFT    0x0080 */
                                    /**< EMU_KEY_DOWN    0x0100 */
                                    /**< EMU_KEY_UP      0x0200 */
  }param;
} esl_GssRenderInput_t;


/**
 *  @brief The structure defines the gssmedia file information
 */
typedef struct {
  u8                orientation;      /**< EXIF orientation tag: 1. top left side, 2 top right side, 3 bottom right side
                                            4 bottom left side, 5 left side top, 6 right side top, 7 right side bottom
                                            8 left side bottom */
} esl_GssEXIF_Info_t;


/**
 *  @brief The structure defines the display quality setting
 */
typedef struct {
  u16 contrast;                /* Contrast value, 0-100,No changing: 0xFF*/
  u16 brightness;              /* Brightness value, 0-100,No changing: 0xFF*/
  u16 saturation;              /* Saturation value, 0-100,No changing: 0xFF*/
  u16 sharpness;               /* Sharpness value, 0-9,No changing: 0xFF*/
  u16 blackLevel;              /* Black level value, 0-100,No changing: 0xFF*/
  u16 whiteLevel;              /* White level value, 0-100,No changing: 0xFF*/
} esl_GssDisplayQuality_t;


/**
 *  @brief The structure defines the layer property setting
 */
typedef struct {
  u8 transLevel;              /* Transparency value(0: transparent 255: opaque) */
} esl_GssLayerProperty_t;


/**
 *  @brief The sturcture defines the property of image surface.
 */
typedef struct {
  u16                   posX;           /**< Image x-axis coordination*/
  u16                   posY;           /**< Image y-axis coordination*/
  u16                   width;          /**< Image width*/
  u16                   height;         /**< Image height*/
  u32                   stride;         /**< Image stride (= pitch)*/
  u32                   size;           /**< Image data size (bytes)*/
  u32                   addr;           /**< data address*/
  esl_GssColorFormat_e  format;         /**< Image format*/
} esl_GssSurface;

/**
 *  @brief The sturcture defines the property of Image Scale.
 */
typedef struct {
  esl_GssSurface InputSurf;
  esl_GssSurface OutputSurf;
} esl_GssScaleParam_t;


/**
 *  @brief The sturcture defines the property of the jpeg encoding.
 */
typedef struct {
  esl_GssQuality_e       jpegQuality;   /**< JPEG quality: Low, Normal and High */
  esl_GssSurface         inputData;     /**< Encoded image data */
  esl_GssEncodeDstType_e dstTyp;        /**< Encode destination type */
  union {
    struct {
      esl_GssPath_e pathOption;
      u16 pathLen;                      /**< Storage path length (UCS2), width/height is the same as input*/
      u16 *pPathName;                   /**< Storage path */
    } path;
    esl_GssBufferInfo_t  outPutBuffer;  /**< Encode destation buffer*/
  }dst;
} esl_GssEncodeSetting_t;

/**
 *  @brief The sturcture defines the property of the jpeg encoding.
 */
typedef struct {
    u32 b2SyncFlag;        /**< streaming data length */
    u32 mmpSyncFlag;       /**<                       */
} esl_GssSyncFlg_t;

/**
 *  @brief The sturcture defines the property of the Graphic engine.
 */
typedef struct {
  esl_GssGEtype_e       geTyp;         /**< capture resolution */
  union {
  esl_GssScaleParam_t   scaleConfig;  /**< scale parameters */
  }param;
} esl_GssGESetting_t;

/**
    @brief      Game capability(the original form is from MmlGameCapability_t, if the definition is different , there wiil be risk)
*/
typedef MmlGameCapability_t esl_GssGameCapability_t;
/**
    @brief      Image decoding capability (the original form is from MmlImageDecodingCapability_t, if the definition is different , there wiil be risk)
*/
typedef MmlImageCaptureCapability_t esl_GssImageDecodingCapability_t;
/**
 *  @brief The sturcture defines the return information of gssmedia file
 */
typedef struct {
  union {
    esl_GssBufferInfo_t                 decodeBuffInfo;             /**< Gss decode 1st frame buffer information response */
    esl_GssBufferInfo_t                 encodeBuffInfo;             /**< Gss encode Dst buffer information response */
    esl_GssBufferInfo_t                 gameStatusInfo;             /**< EMU game status buffer information response */
    u32                                 nEmuHashData;               /**< EMU game hash data */
    u32                                 nEmuVersion;                /**< EMU version b31~b16 is major version number, b16~b0 is minor version number */
    esl_GssDisplayQuality_t             DQInfo;                     /**< Display quality value*/
    esl_GssGameCapability_t             tGameCapability;            /**< game capability */
    esl_GssImageDecodingCapability_t    tImageDecodingCapability;   /**< image decoding capability */
  } param;
} esl_GssInfo_t;

/**
 *  @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID       : Sender task id.
 * @param userValue      : Reference value for indicating different sender in same task or check msg response
 * @param errCode        : The error code return by Multimedia task to know process success or fail
 * @param pGssInfo       : Callback information returned by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_GssCb)(u16 senderID, u32 userValue, esl_GssErrCode_e errCode, esl_GssInfo_t *pGssInfo);

/**
 *  @brief The gssplayback call back function structure definition
 */
typedef struct {
  u16           senderID;     /**< Task id of sender */
  u32           userValue;    /**< userValue of sender for checking msg response to realted applicatoin */
  esl_GssCb     pfnCb;        /**< Done call back function that called by EMA */
} esl_GssCb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __ESL_GSS_ITF_H__ */

