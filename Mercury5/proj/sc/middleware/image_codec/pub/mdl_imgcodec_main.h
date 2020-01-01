////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_IMGCODEC_MAIN_H_
#define _MDL_IMGCODEC_MAIN_H_

//---------------------------------------------------------------------------
// Include file.
//---------------------------------------------------------------------------
#include "vm_types.ht"
#include "msgdidef.h"

#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_timer.h"

#include "sys_MsWrapper_cus_os_sem.h"
#include "vm_msgof.hc"

#include "srv_ResMgr_MmlManager.h"
#include "srv_resmgr_mmlimage_types.h"

//---------------------------------------------------------------------------
// Preprocessor constant definition.
//---------------------------------------------------------------------------
#define _IMGCODEC_PNG_ALPHA_MASK_

//---------------------------------------------------------------------------
// Structure and enum.
//---------------------------------------------------------------------------
typedef enum{
#include "mdl_imgdecode_message_define__.hi"
}Mdl_ImgDecode_CtlMsgId_e;

// Image decode error code
typedef enum
{
    IMAGE_JPD_NOT_SUPP_PRECISION           = -11,
    IMAGE_JPD_NOT_SUPP_16BIT_QT            = -10,
    IMAGE_OPEN_FILE_FAILED                 = -9,
    IMAGE_JPD_RES_NOT_SUPPORT              = -8,
    IMAGE_RE_ENTRY_ABORT                   = -7,
    IMAGE_BAD_PARAMETERS                   = -6,    /**< Bad parameters*/
    IMAGE_WRONG_HANDLE                     = -5,    /**< Image decode wrong decode handle */
    IMAGE_NOT_ENOUGH_MEMORY                = -4,    /**< Image decode memory not enough*/
    IMAGE_TOO_MUCH_EXECUTING_INSTANCE      = -3,    /**< Image decode too much executing instance*/
    IMAGE_DEC_ERR                          = -2,    /**< Image decode error*/
    IMAGE_FORMAT_UNSUPPORT                 = -1,    /**< Image decode format not support*/
    IMAGE_ERROR                            = 0,     /**< Image decode error ( keep this be 0)*/
    IMAGE_SUCCESS,                                  /**< Image decode success = 1*/
    IMAGE_SUCCESS_WAITING,                          /**< By Montage, caller wait for IMGCODEC_MSG_DECODE_DONE or IMGCODEC_MSG_ERROR or callback function*/
    IMAGE_SUCCESS_MORE_FRAMES,                      /**< GIFA, Caller wait for IMGCODEC_MSG_UPDATE_GIFA message.*/
    IMAGE_SUCCESS_ABORTED,                          /**< Image Decoding is Done (aborted)*/
    IMAGE_REJECT,

    IMAGE_JPD_DECODE_TIME_OUT              = 0x4113,
    IMAGE_JPD_HWVLD_ECS_ERR                = 0x4114,
    IMAGE_JPGD_BAD_DHT_COUNTS              = 0x4130,
    IMAGE_JPGD_BAD_DHT_INDEX               = 0x4131,
    IMAGE_JPGD_BAD_DHT_MARKER              = 0x4132,
    IMAGE_JPGD_BAD_DQT_MARKER              = 0x4133,
    IMAGE_JPGD_BAD_DQT_TABLE               = 0x4134,
    IMAGE_JPGD_BAD_PRECISION               = 0x4135,
    IMAGE_JPGD_BAD_HEIGHT                  = 0x4136,
    IMAGE_JPGD_BAD_WIDTH                   = 0x4137,
    IMAGE_JPGD_TOO_MANY_COMPONENTS         = 0x4138,
    IMAGE_JPGD_BAD_SOF_LENGTH              = 0x4139,
    IMAGE_JPGD_BAD_VARIABLE_MARKER         = 0x413a,
    IMAGE_JPGD_BAD_DRI_LENGTH              = 0x413b,
    IMAGE_JPGD_BAD_SOS_LENGTH              = 0x413c,
    IMAGE_JPGD_BAD_SOS_COMP_ID             = 0x413d,
    IMAGE_JPGD_W_EXTRA_BYTES_BEFORE_MARKER = 0x413e,
    IMAGE_JPGD_NO_ARITHMITIC_SUPPORT       = 0x413f,
    IMAGE_JPGD_UNEXPECTED_MARKER           = 0x4140,
    IMAGE_JPGD_NOT_JPEG                    = 0x4141,
    IMAGE_JPGD_UNSUPPORTED_MARKER          = 0x4142,
    IMAGE_JPGD_BAD_DQT_LENGTH              = 0x4143,
    IMAGE_JPGD_TOO_MANY_BLOCKS             = 0x4144,
    IMAGE_JPGD_UNDEFINED_QUANT_TABLE       = 0x4145,
    IMAGE_JPGD_UNDEFINED_HUFF_TABLE        = 0x4146,
    IMAGE_JPGD_NOT_SINGLE_SCAN             = 0x4147,
    IMAGE_JPGD_UNSUPPORTED_COLORSPACE      = 0x4148,
    IMAGE_JPGD_UNSUPPORTED_SAMP_FACTORS    = 0x4149,
    IMAGE_JPGD_DECODE_ERROR                = 0x414a,
    IMAGE_JPGD_BAD_RESTART_MARKER          = 0x414b,
    IMAGE_JPGD_ASSERTION_ERROR             = 0x414c,
    IMAGE_JPGD_BAD_SOS_SPECTRAL            = 0x414d,
    IMAGE_JPGD_BAD_SOS_SUCCESSIVE          = 0x414e,
    IMAGE_JPGD_STREAM_READ                 = 0x414f,
    IMAGE_JPGD_NOTENOUGHMEM                = 0x4150,
    IMAGE_JPGD_GET_NULL_POINT              = 0x4151,
}image_Errmsg;

// Image formats
typedef enum
{
    IMAGE_FORMAT_ERR = 0,
    IMAGE_FORMAT_BMP,
    IMAGE_FORMAT_PNG,
    IMAGE_FORMAT_GIF,
    IMAGE_FORMAT_JPG,
    IMAGE_FORMAT_GIFA,
    IMAGE_FORMAT_MMP,
    IMAGE_FORMAT_WAVBMP,
    IMAGE_FORMAT_WAPBMP,
    IMAGE_FORMAT_TOTAL
}IMGCODEC_FORMAT, *PIMGCODEC_FORMAT;

// Rotatation angle
typedef enum
{
    ROTATION_ANGLE_0 = 0,
    ROTATION_ANGLE_90,
    ROTATION_ANGLE_270,
    ROTATION_ANGLE_180,
    ROTATION_ANGLE_NUM
}Image_RotationAngle;

// ROI
typedef struct
{
    u16     x;          /**< Horizontal position of top-left */
    u16     y;          /**< Vertical position of top-left */
    u16     width;      /**< Horizontal width */
    u16     height;     /**< Vertical height */
} ImgRegion_t;

// Dispatch mode
typedef enum
{
    IMAGE_DISPATCH_DONT_CARE = 0,
    IMAGE_DISPATCH_FORCE_SOFTWARE,
    IMAGE_DISPATCH_REJECT_HARDWARE,
    IMAGE_DISPATCH_REJECT_JPG,
    IMAGE_DISPATCH_BOOT_UP
}Image_DispatchMode;

// Stereo mode
typedef enum
{
    IMAGE_STEREO_NONE = 0,
    IMAGE_STEREO_RED_CYAN
}Image_StereoMode;

// Decode configuration
typedef struct
{
    Image_DispatchMode  dispatch;
    Image_RotationAngle angle;
    ImgRegion_t         ROI;
    u8                  bEnableROI;
    u8                  bMirrorX;
    u8                  bMirrorY;
    Image_StereoMode    stereoMode;
}Image_Config_t;

// Input parameters
typedef struct
{
    u8   bIsFile;
    u32  bufferSize;
    void *buffer;
}Image_Input_t;

// Exif data
typedef enum
{
    IMAGE_LATITUDE_NORTH,  /**< North latitude*/
    IMAGE_LATITUDE_SOUTH,  /**< South latitude*/
    IMAGE_LATITUDE_NONE
} IMGCODEC_GPS_LATITUDE;

typedef enum
{
    IMAGE_LONGITUDE_EAST,  /**< East latitude*/
    IMAGE_LONGITUDE_WEST,  /**< West latitude*/
    IMAGE_LONGITUDE_NONE
} IMGCODEC_GPS_LONGITUDE;

typedef struct
{
    u32 numerator;       /**< numerator of gps data */
    u32 denominator;     /**< denominator of gps data */
} Imgage_gpsData_t;

typedef struct
{
  IMGCODEC_GPS_LATITUDE   latitude;       /**< Latitude of GPS info in EXIF */
  Imgage_gpsData_t        latDegree;      /**< Degree of latitude */
  Imgage_gpsData_t        latMin;         /**< Minute of latitude */
  Imgage_gpsData_t        latSec;         /**< Second of latitude */

  IMGCODEC_GPS_LONGITUDE  longitude;      /**< longitude of GPS info in EXIF */
  Imgage_gpsData_t        lonDegree;      /**< Degree of longitude */
  Imgage_gpsData_t        lonMin;         /**< Minute of longitude */
  Imgage_gpsData_t        lonSec;         /**< Second of longitude */
} Imgage_EXIF_t;

// Image information
typedef struct
{
    IMGCODEC_FORMAT format;      // file format
    u16             width_p;     // image width
    u16             height_p;    // image height
    u32             TotalFrames;
    u32             size_p;      // bytes of entire file.
    Imgage_EXIF_t   exifInfo;    // EXIF information
    u8              orientation; // Jpeg orientation tag
    bool            bIsFile;
    bool            bIsProgressive;
    bool            bHasAlpha;
    bool            bSupportPaletteOutput;
    u16             maxHSampFactor;
    u16             maxVSampFactor;
}Image_Info_t;

// Next-frame information
typedef struct
{
    u8  hasNextFrame;
    u32 nextFrameDelay;
    u32 nextFrameIndex;
}Image_FrameInfo_t;


//---------------------------------------------------------------------------
// Deprecated structure.
//---------------------------------------------------------------------------
typedef Image_Info_t Image_RapidInfo_t;

typedef struct
{
    s32     CodecHandle;
    u32     uValue;
}IMGCODEC_MSGBODY, *PIMGCODEC_MSGBODY;

typedef struct
{
    ImgRegion_t         region;
    Image_RotationAngle angle;
}Image_decodeParm_t;

//---------------------------------------------------------------------------
// Special-purpose API.
//---------------------------------------------------------------------------
void ImageResponseCallback(u16 nSenderID,
    u32                    nUserValue,
    MmlImageResult_e       eErrCode,
    MmlImageResponse_t     *pImageResponse
);

image_Errmsg imageCodec_displayTuningReq(int start);

//---------------------------------------------------------------------------
// Generic API.
//---------------------------------------------------------------------------
u32 imageCodec_open(void);
image_Errmsg imageCodec_close(u32 hHandle);
image_Errmsg imageCodec_decodeFirst(u32 hHandle, Image_Input_t *pInput, PMSSURFACE pOutSurf, Image_Config_t *pConfig);
image_Errmsg imageCodec_decodeNext(u32 hHandle);
image_Errmsg imageCodec_getFrameInfo(u32 hHandle, Image_FrameInfo_t *pFrameInfo);
image_Errmsg imageCodec_getInfo(Image_Input_t *pInput, Image_Info_t *pInfo);
image_Errmsg imageCodec_decodeAbort(u32 handle);

s32 imageCodec_rotateScaleFit(PMSSURFACE dstSurf, PMSSURFACE srcSurf,
							  Image_RotationAngle angle, u8 bMirror, u8 bForceSW);
s32 imageCodec_rotateScaleROI(PMSSURFACE dstSurf, PMSSURFACE srcSurf, ImgRegion_t dstROI, ImgRegion_t srcROI,
							  Image_RotationAngle angle, u8 bMirror, u8 bForceSW);

//---------------------------------------------------------------------------
// Deprecated API.
//---------------------------------------------------------------------------
image_Errmsg imageCodec_getImageinfo(s32 hHandle, u8* pInBuffer, Image_Info_t* pInfo);
image_Errmsg imageCodec_decode(s32 hHandle, u8 *pInBuffer, PMSSURFACE pOutSurf, Image_RotationAngle imgRotateAngle);
image_Errmsg imageCodec_decodeNextFrame(s32 hHandle, u32 *delayTime);

u32 imageCodec_getNextFrameDelayTime(s32 hHandle);
u8  imageCodec_hasNextFrame(s32 hHandle);

#endif
