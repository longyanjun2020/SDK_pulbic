////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlimage_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLIMAGE_TYPES_H__
#define __SRV_RESMGR_MMLIMAGE_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayerImage Image
    Image Decoding and Encoding (Capture)
    @{
*/
    /** @defgroup MMLayerImageDecoding Image Decoding
        Image Decoding
        @{
    */
    /** @} */

    /** @defgroup MMLayerImageEncoding Image Encoding (Capture)
        Image Encording (Capture)
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
#include "srv_resmgr_mmlcamera_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerImage
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseImageId_e_)
{
    /* Image Init */
    MML_UCID_IMAGE_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_IMAGE),
    MML_UCID_IMAGE_REG_NOTIFY_CALLBACK = MML_UCID_IMAGE_INIT_BASE,          ///< 00030000 = Reg notify callback
    MML_UCID_IMAGE_UNREG_NOTIFY_CALLBACK,                                   ///< 00030001 = Unreg notify callback
    MML_UCID_IMAGE_INIT_CATEGORY,

    /* Image Get */
    MML_UCID_IMAGE_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_IMAGE),
    MML_UCID_IMAGE_GET_IMAGE_INFO = MML_UCID_IMAGE_GET_BASE,                ///< 00030100 = Get image information
    MML_UCID_IMAGE_GET_CAPTURE_INFO,                                        ///< 00030101 = Get capture information
    MML_UCID_IMAGE_GET_IMAGE_DATA,                                          ///< 00030102 = Get image data
    MML_UCID_IMAGE_GET_CAPTURE_CAPABILITY,                                  ///< 00030103 = Get capture capability
    MML_UCID_IMAGE_GET_DECODING_CAPABILITY,                                 ///< 00030104 = Get decoding capability
    MML_UCID_IMAGE_GET_CATEGORY,

    /* Image Set */
    MML_UCID_IMAGE_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_IMAGE),
    MML_UCID_IMAGE_SET_JPEG_EXIF_INFO = MML_UCID_IMAGE_SET_BASE,            ///< 00030200 = Set JPEG exif info
    MML_UCID_IMAGE_SET_CATEGORY,

    /* Image Execute */
    MML_UCID_IMAGE_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_IMAGE),
    MML_UCID_IMAGE_ENCODE_IMAGE = MML_UCID_IMAGE_EXECUTE_BASE,              ///< 00030300 = Encode image
    MML_UCID_IMAGE_DECODE_IMAGE,                                            ///< 00030301 = Decode image
    MML_UCID_IMAGE_DECODE_NEXT_FRAME,                                       ///< 00030302 = Decode next frame
    MML_UCID_IMAGE_ABORT_DECODING,                                          ///< 00030303 = Abort Decoding
    MML_UCID_IMAGE_STOP_CONTINUOUS_CAPTURE,                                 ///< 00030304 = Stop continuous capture
    MML_UCID_IMAGE_OPEN_DECODING_HANDLE,                                    ///< 00030305 = Open decoding handle
    MML_UCID_IMAGE_CLOSE_DECODING_HANDLE,                                   ///< 00030306 = Close decode handle
    MML_UCID_IMAGE_CONVERT_COLOR_FORMAT,                                    ///< 00030307 = Convert Color format
    MML_UCID_IMAGE_ABORT_ENCODING,                                          ///< 00030308 = Abort Encoding
    MML_UCID_IMAGE_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_IMAGE_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerImage
    @brief      Response results
*/
typedef enum
{
    /* Common */
    IMAGE_ERROR_SUCCESS = 0,
    IMAGE_ERROR_FAIL,
    IMAGE_ERROR_PARAMETER_INVALID,
    IMAGE_ERROR_STATE_CHANGE,
    IMAGE_ERROR_ACCEPT,
    IMAGE_ERROR_IGNORE,
    IMAGE_ERROR_REJECT,
    IMAGE_ERROR_ABORT,
    IMAGE_ERROR_MEMORY_FAILURE,
    /* Image Decoding */
    /* Image Encoding */
    IMAGE_ERROR_DISK_FULL,
    /* */
    IMAGE_ERROR_NUM
} MmlImageResult_e;

/** @ingroup    MMLayerImage
    @brief      States
*/
typedef enum
{
    /* Image Decoding */
    IMAGE_STATE_DECODING_IDLE = 0,
    IMAGE_STATE_DECODING_DECODING,
    /* Image Encoding */
    IMAGE_STATE_ENCODING_IDLE,
    IMAGE_STATE_ENCODING_ENCODING,
    /* */
    IMAGE_STATE_DONTCARE,
    IMAGE_STATE_NUM
} MmlImageState_e;

/** @ingroup    MMLayerImage
    @brief      Events
*/
typedef enum
{
    /* Common */
    IMAGE_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_IMAGE),
    IMAGE_EVENT_RUNTIME_ERROR,
    /* Image Decoding */
    IMAGE_EVENT_DECODING_STATE_CHANGE,
    IMAGE_EVENT_DECODING_RUNTIME_ERROR,
    IMAGE_EVENT_DECODE_COMPLETE,
    IMAGE_EVENT_DECODE_ONEFRAME_COMPLETE, /* To be removed, ck.wang@20100328*/
    IMAGE_EVENT_DECODE_ABORTED,
    /* Image Encoding */
    IMAGE_EVENT_ENCODING_STATE_CHANGE,
    IMAGE_EVENT_ENCODING_RUNTIME_ERROR,
    IMAGE_EVENT_ENCODE_COMPLETE,
    /* */
    IMAGE_EVENT_DONTCARE,
    IMAGE_EVENT_ALL,
    IMAGE_EVENT_NUM
} MmlImageEvent_e;

/** @ingroup    MMLayerImage
    @brief      Input source types
*/
typedef enum MmlImageInputType_e_
{
    IMAGE_INPUT_FILE = 0,      ///< Decode form filename based source
    IMAGE_INPUT_MEMORY,        ///< Decode form in-memory source
    IMAGE_INPUT_CAMERA,        ///< Encode from camera I/O device source
    IMAGE_INPUT_MEMORY_RAW,    ///< Encode from in-memory raw image source
    /* */
    IMAGE_INPUT_NUM
} MmlImageInputType_e;

/** @ingroup    MMLayerImage
    @brief      Output destination types
*/
typedef enum
{
    IMAGE_OUTPUT_FILE = 0,    ///< Encode to file-based destination
    IMAGE_OUTPUT_MEMORY,      ///< Encode/Decode to in-memory destination
    IMAGE_OUTPUT_DISPLAY,     ///< Decode to in-memory destination
    /* */
    IMAGE_OUTPUT_NUM
} MmlImageOutputType_e;

/** @ingroup    MMLayerImage
    @brief      Storage types
*/
typedef enum
{
    IMAGE_STORAGETYPE_CARD = 0,    ///< SD Card
    IMAGE_STORAGETYPE_NORFLASH,    ///< Nor flash
    IMAGE_STORAGETYPE_NANDFLASH,   ///< Nand flash
    /* */
    IMAGE_STORAGETYPE_NUM
} MmlImageStorageType_e;

/** @ingroup    MMLayerImage
    @brief      Image codecs
*/
typedef enum MmlImageImageCodec_e_
{
    IMAGE_IMAGECODEC_JPEG = 0,
    IMAGE_IMAGECODEC_GIF,
    IMAGE_IMAGECODEC_BMP,
    IMAGE_IMAGECODEC_PNG,
    IMAGE_IMAGECODEC_TIFF,
    IMAGE_IMAGECODEC_RAW,
    /* Decoding video first frame */
    IMAGE_IMAGECODEC_3GP,
    IMAGE_IMAGECODEC_MP4,
    IMAGE_IMAGECODEC_RM,
    IMAGE_IMAGECODEC_AVI,
    IMAGE_IMAGECODEC_MFS,
    IMAGE_IMAGECODEC_TS,
    IMAGE_IMAGECODEC_DONTCARE,
    /* */
    IMAGE_IMAGECODEC_NUM
} MmlImageImageCodec_e;

/** @ingroup    MMLayerImage
    @brief      Stereoscopy types
*/
typedef enum
{
    IMAGE_STEREOTYPE_NONE = 0,
    IMAGE_STEREOTYPE_RED_CYAN,
    IMAGE_STEREOTYPE_LEFT_RIGHT,
    IMAGE_STEREOTYPE_GLASSFREE,
    /* */
    IMAGE_STEREOTYPE_NUM
} MmlImageStereoType_e;

/** @ingroup    MMLayerImage
    @brief      Rotation angles
*/
typedef enum
{
    IMAGE_ROTATION_0 = 0,
    IMAGE_ROTATION_90,
    IMAGE_ROTATION_180,
    IMAGE_ROTATION_270,
    /* */
    IMAGE_ROTATION_NUM
} MmlImageRotationAngle_e;

/** @ingroup    MMLayerImage
    @brief      Exif orientations
*/
typedef enum
{
    IMAGE_EXIFORIENTATION_TOP_LEFT = 1,
    IMAGE_EXIFORIENTATION_TOP_RIGHT,
    IMAGE_EXIFORIENTATION_BOTTOM_RIGHT,
    IMAGE_EXIFORIENTATION_BOTTOM_LEFT,
    IMAGE_EXIFORIENTATION_LEFT_TOP,
    IMAGE_EXIFORIENTATION_RIGHT_TOP,
    IMAGE_EXIFORIENTATION_RIGHT_BOTTOM,
    IMAGE_EXIFORIENTATION_LEFT_BOTTOM
} MmlImageExifOrientation_e;

/** @ingroup    MMLayerImage
    @brief      File-based source
*/
typedef struct MmlImageFileParam_t_
{
    MmlImageImageCodec_e    eCodecId;
    MmlFilenameFormat_e     eFilenameFormat;
    u16                     *pFileName;
    u16  	                nFileNameSize;
} MmlImageFileParam_t;

/** @ingroup    MMLayerImage
    @brief      In-memory source/destination
*/
typedef	struct MmlImageMemoryParam_t_
{
    MmlImageImageCodec_e    eCodecId;
    u8                      *pBuffer;
    u32                     nBufferSize;
} MmlImageMemoryParam_t;

/** @ingroup    MMLayerImage
    @brief      A block of memory, used to hold input/output data
*/
typedef	struct
{
    u8                  *pBuffer;       ///< Pointer to the data buffer
    u32                 nBufferSize;    ///< Size in bytes of the data buffer
    u32                 nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlImageBufferParam_t;

/** @ingroup    MMLayerImage
    @brief      Display surface
*/
typedef void* MmlImageDisplayParam_t;    ///< Cast void pointer to PMSSURFACE

/** @ingroup    MMLayerImage
    @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} MmlImageRectangle_t;


/** @ingroup    MMLayerImage
    @brief      Image info
*/
typedef struct
{
    MmlImageImageCodec_e    eCodecId;     ///< Associated image codec
    u16                     nWidth;       ///< Image width in pixels
    u16                     nHeight;      ///< Image height in pixels
    u32                     nByteSize;    ///< Image size in bytes
} MmlImageInfo_t;

/** @ingroup    MMLayerImageDecoding
    @brief      Decode complete info
*/
typedef struct
{
    u16    bHasNextFrame;         ///< True/false falg to indicate whether image has next frame
    u32    nNextFrameDelayTime;   ///< Next frame's delay time, expressed in 10 ms
    u32    nFrameIndex;           ///< Next frame's index
} MmlImageDecodeCompleteInfo_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Encode complete info
*/
typedef struct
{
    u32                          nCaptureCount;    ///< Total number of pictures taken
    MmlImageOutputType_e         eOutputType;      ///< Output destination types
    /// union of MmlImageEncodeCompleteInfo_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;       ///< Output filename (full path, unicode)
        MmlImageMemoryParam_t    tMemoryParam;     ///< Output buffer address and size
    } uParam;
} MmlImageEncodeCompleteInfo_t;

/** @ingroup    MMLayerImage
    @brief      State change info
*/
typedef	struct
{
    MmlImageState_e                     eState;    ///< The new state after the transition
    MmlImageEvent_e	                    eCause;    ///< The cause of state change, if any

    /// union of MmlImageStateChange_t parameters
    union
    {
   	    MmlImageFileParam_t             tFileParam;             ///< Filename of the saved file
        MmlImageEncodeCompleteInfo_t    tEncodeCompleteInfo;    ///< Encode complete info
        MmlImageDecodeCompleteInfo_t    tDecodeCompleteInfo;    ///< Decode complete info
        MmlImageResult_e                eErrCode;               ///< Run time error code
    } uParam;
} MmlImageStateChange_t;

/** @ingroup    MMLayerImage
    @brief      Notification payload
*/
typedef struct
{
    MmlImageEvent_e	                    eEvent;     ///< Specify the event you want to notify
    u32                                 nHandle;    ///< 32-bit decoding/encoding handle

    /// union of MmlImageNotify_t parameters
    union
    {
        MmlImageStateChange_t           tStateChange;           ///< Used with IMAGE_EVENT_STATE_CHANGE event
        MmlImageResult_e                eErrCode;               ///< Used with IMAGE_EVENT_RUNTIME_ERROR event
        MmlImageEncodeCompleteInfo_t    tEncodeCompleteInfo;    ///< Used with IMAGE_EVENT_ENCODE_COMPLETE event
        MmlImageDecodeCompleteInfo_t    tDecodeCompleteInfo;    ///< Used with IMAGE_EVENT_DECODE_COMPLETE event
	} uParam;
} MmlImageNotify_t;

/** @ingroup    MMLayerImage
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      MmlImageNotify_t  Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlImageNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlImageNotify_t *pImageNotify);

/** @ingroup    MMLayerImage
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;            ///< Sender's mailbox ID
    u32                             nUserValue;           ///< Interface self-reference
    PfnMmlImageNotifyCallback       pfnNotifyCallback;    ///< Callback function your want to register
} MmlImageNotifyCallback_t;

/** @ingroup    MMLayerImage
    @brief      Response callback prototype
    @param      nSenderID             Sender's mailbox ID
    @param      nUserValue            User self-reference
    @param      eErrCode              Returned result (error code)
    @param      MmlImageResponse_t    Pointer to the returned response payload
*/
struct MmlImageResponse_t_;
typedef void (*PfnMmlImageResponseCallback)(u16 nSenderID, u32 nUserValue, MmlImageResult_e eErrCode, struct MmlImageResponse_t_ *pImaegResponse);

/** @ingroup    MMLayerImage
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlImageResponseCallback     pfnResponseCallback;    ///< Callback function your want to register
} MmlImageResponseCallback_t;

/** @ingroup    MMLayerImage
    @brief      Register notification callback
*/
typedef struct
{
    MmlImageEvent_e                 eEvent;             ///< Specify which event you want to handle
    MmlImageNotifyCallback_t        tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlImageRegNotifyCallback_t;

/** @ingroup    MMLayerImage
    @brief      Get image info
*/
typedef struct
{
    MmlImageInputType_e          eInputType;            ///< Input source types

    /// union of MmlImageGetImageInfo_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;            ///< Get info from filename based source
        MmlImageMemoryParam_t    tMemoryParam;          ///< Get info from in-memory source
	} uParam;

} MmlImageGetImageInfo_t;

/** @ingroup    MMLayerImage
    @brief      Set jpeg exif info
*/
typedef struct
{
    MmlImageInputType_e          eInputType;            ///< Input source types
    MmlImageExifOrientation_e    eExifOrientation;      ///< Exif orientation tag value

    /// union of MmlImageSetJpegExifInfo_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;            ///< Decode from filename based source
        MmlImageMemoryParam_t    tMemoryParam;          ///< Decode from in-memory source
	} uParam;

} MmlImageSetJpegExifInfo_t;

/** @ingroup    MMLayerImageDecoding
    @brief      Decode modes
*/
typedef enum
{
    IMAGE_DECODEMODE_NORMAL = 0,         ///< Decoding standard format images
    IMAGE_DECODEMODE_JPEGPNGALPHA,       ///< Decoding 'jpeg' + 'png alpha' image
    IMAGE_DECODEMODE_RGBAPNG,            ///< Decoding 'rgba png' image
    /* */
    IMAGE_DECODEMODE_NUM
} MmlImageDecodeMode_e;

/** @ingroup    MMLayerImageDecoding
    @brief      Decode image (jpeg, bmp, png, rgba)
*/
typedef struct
{
    MmlImageDecodeMode_e         eDecodeMode;           ///< Decode modes
    u32                          nHandle;               ///< Decoding handle, previously obtained from 'Open decoding handle'
    MmlImageInputType_e          eInputType;            ///< Input source types
    MmlImageOutputType_e         eOutputType;           ///< Output destination types
    u16                          nWidth;                ///< Output image width in pixels, ignored in display mode
    u16                          nHeight;               ///< Output image height in pixels, ignored in display mode
    u16                          nOutputWindowPitch;    ///< Output window pitch, ignored in display mode
    MmlImageRotationAngle_e      eRotationAngle;        ///< 0, 90, 180, 270 degree
    u16                          bXAxisMirrorEnable;    ///< Enable x-axis mirror
    u16                          bYAxisMirrorEnable;    ///< Enable y-axis mirror
    u16                          bROIMode;              ///< Enable decoding the region of interest
    u16                          bUseSoftwareScalar;    ///< Force use software scalar
    MmlImageRectangle_t          tROI;                  ///< Crop image inside the region of interest of the source image
    MmlImageColorFormat_e        eColorFormat;          ///< Output pixel color format (todo)
    MmlImageStereoType_e         eImageStereoType;      ///< Image stereo types

    /// union of MmlImageDecodeImage_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;            ///< Decode from file-based source
        MmlImageMemoryParam_t    tMemoryParam;          ///< Decode from in-memory source
	} uInputParam;

	/// union of MmlImageDecodeImage_t parameters
    union
    {
        MmlImageDisplayParam_t   tDisplayParam;         ///< Decode to display surface
        MmlImageMemoryParam_t    tMemoryParam;          ///< Decode to in-memory destination (rgb buffer)
	} uOutputParam;

} MmlImageDecodeImage_t;

/** @ingroup    MMLayerImageDecoding
    @brief      Decode next frame (animation)
*/
typedef struct
{
    u32    nHandle;        ///< Decoding handle indicating which animation decoding instance
    //u16    nFrameIndex;    ///< Indicate which animation frame to be decoded
} MmlImageDecodeNextFrame_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Capture modes
*/
typedef enum
{
    IMAGE_CAPTUREMODE_CONTINUOUS = 0,   ///< Continuous capture
    IMAGE_CAPTUREMODE_ROTATIONCAPTURE,  ///< Rotation capture
    IMAGE_CAPTUREMODE_ATVSNAPSHOT,      ///< ATV snapshot
    IMAGE_CAPTUREMODE_PHOTOSTICKER,     ///< Photo sticker
    IMAGE_CAPTUREMODE_PANORAMA,         ///< Panorama
    IMAGE_CAPTUREMODE_LOMO_4LENS,       ///< LOMO 4 lens
    IMAGE_CAPTUREMODE_MIRROR,           ///< Mirror
    /* */
    IMAGE_CAPTUREMODE_NUM
} MmlImageCaptureMode_e;

/** @ingroup    MMLayerImageEncoding
    @brief      Panorama modes
*/
typedef enum
{
    IMAGE_PANORAMAMODE_LEFTTORIGHT = 0, ///< Left to right
    IMAGE_PANORAMAMODE_RIGHTTOLEFT,     ///< Right to left
    IMAGE_PANORAMAMODE_TOPTODOWN,       ///< Top to down
    IMAGE_PANORAMAMODE_DOWNTOTOP,       ///< Down to top
    /* */
    IMAGE_PANORAMAMODE_NUM
} MmlImagePanoramaMode_e;

/** @ingroup    MMLayerImageEncoding
    @brief      Mirror modes
*/
typedef enum
{
    IMAGE_MIRRORMODE_VERTICAL = 0,      ///< Vertical
    IMAGE_MIRRORMODE_HORIZONTAL,        ///< Horizontal
    /* */
    IMAGE_MIRRORMODE_NUM
} MmlImageMirrorMode_e;

/** @ingroup    MMLayerImageEncoding
    @brief      In-memory raw image source
*/
typedef	struct
{
    MmlImageImageCodec_e     eCodecId;      ///< Must be IMAGE_IMAGECODEC_RAW
    MmlImageColorFormat_e    eColorFormat;  ///< Raw image color format
    u8                       *pBuffer;      ///< Pointer to the raw image buffer
    u32                      nBufferSize;   ///< Size in bytes of the raw image buffer
    u16                      nLeft;         ///< x-position of the top left corner of the image
    u16                      nTop;          ///< y-position of the top left corner of the image
    u16                      nWidth;        ///< Image width in pixels
    u16                      nHeight;       ///< Image height in pixels
    u16                      nStride;       ///< Number of bytes in a line of the image
} MmlImageRawMemoryParam_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Panorama mode capture parameters
*/
typedef struct
{
    MmlImagePanoramaMode_e  ePanoramaMode;
    u32                     nTotalPicsNum;
    u32                     nCurrentPicsNum;
    u8                      *pBuffer;
    u32                     nBufferSize;
} MmlImageCapturePanoramaParam_t;


/** @ingroup    MMLayerImageEncoding
    @brief      Mirror mode capture parameters
*/
typedef struct
{
    MmlImageMirrorMode_e    eMirroMode;
} MmlImageCaptureMirrorParam_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Lomo 4 lens mode capture parameters
*/
//typedef unsigned int MmlCameraImageEffect_e;
typedef struct
{
    MmlCameraImageEffect_e  eImageEffect_UpperLeft;
    MmlCameraImageEffect_e  eImageEffect_UpperRight;
    MmlCameraImageEffect_e  eImageEffect_LowerLeft;
    MmlCameraImageEffect_e  eImageEffect_LowerRight;
} MmlImageCaptureLomo4LensParam_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Capture settings
*/
typedef struct
{
    MmlImageCaptureMode_e       eCaptureMode;           ///< Capture modes
    u16                         nNumOfPicsTaken;        ///< Number of pictures taken, 1-16, single capture (number = 1)
    MmlImageRotationAngle_e     eRotationAngle;         ///< 0, 90, 180, 270 degree
    u16                         bShutterSoundEnable;    ///< Enable the shutter feedback
    u16                         bImageStabilizerEnable; ///< Enable image stabilizer
    MmlImageMemoryParam_t       tShutterSoundBuffer;    ///< Specify the shutter sound stream buffer
    u16                         nNumOfSkipFrame;        ///< Number of skip frame (0-15)
    u8                          *pStickerFramebuffer;   ///< Pointer to the photo-sticker frame buffer

    /// union of MmlImageEncodeImage_t parameters
    union
    {
        MmlImageCapturePanoramaParam_t  tPanoramaParam;
        MmlImageCaptureMirrorParam_t    tMirrorParam;
        MmlImageCaptureLomo4LensParam_t tLomo4LenParam;
    } uParam;
} MmlImageCaptureSettings_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Encode image (jpeg)
    @todo       Add EXIF maker/model, GPS, and RFID info
*/
typedef struct
{
    MmlImageImageCodec_e            eEncoderId;             ///< Specify the supported image encoder
    MmlImageInputType_e             eInputType;             ///< Input source types
    MmlImageOutputType_e            eOutputType;            ///< Output destination types
    u16                             nWidth;                 ///< Output image width in pixels
    u16                             nHeight;                ///< Output image height in pixels
    u16                             nQualityLevel;          ///< Compression level in 0-1000, 0: default, 1: best, 1000: worst (highest compression)
    MmlImageExifOrientation_e       eExifOrientation;       ///< Exif orientation tag value
    MmlImageColorFormat_e           eColorFormat;           ///< Output pixel color format (only used for RAW output)
    //MmlImageFileParam_t             tFileParam;             ///< Output filename (full path, unicode)

    /// union of MmlImageEncodeImage_t parameters
    union
    {
        MmlImageCaptureSettings_t   tCaptureSettings;       ///< Encode from camera I/O device source
        MmlImageRawMemoryParam_t    tRawMemoryParam;        ///< Encode from in-memory raw image source
    } uInputParam;

    /// union of MmlImageEncodeImage_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;                ///< Encode to file-based destination
        MmlImageMemoryParam_t    tMemoryParam;              ///< Encode to in-memory destination
    } uOutputParam;
} MmlImageEncodeImage_t;

/** @ingroup    MMLayerImage
    @brief      Convert color format
*/
typedef struct
{
    MmlImageRawMemoryParam_t    tRawMemoryParamInput;      ///< In-memroy raw image source
    MmlImageRawMemoryParam_t    tRawMemoryParamOutput;     ///< In-memory raw image destination
} MmlImageConvertColorFormat_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Capture info
*/
typedef struct
{
    u32    nPicturesRemaining;    ///< 32-bit number of pictures remaining
} MmlImageCaptureInfo_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Get capture info
*/
typedef struct
{
    u16                      nQualityLevel;    ///< Compression level in 0-1000, 0: default, 1: best, 1000: worst (highest compression)
    u16                      nWidth;           ///< Output image width in pixels
    u16                      nHeight;          ///< Output image height in pixels
    MmlImageStorageType_e    eStorageType;     ///< Specify what kind of storage is used to save the captured image
} MmlImageGetCaptureInfo_t;

#define MML_IMAGECAPTURE_FORMAT_BITMASK_JPEG                    ((u32) 0x00000001)
#define MML_IMAGECAPTURE_FORMAT_BITMASK_GIF                     ((u32) 0x00000002)
#define MML_IMAGECAPTURE_FORMAT_BITMASK_BMP                     ((u32) 0x00000004)
#define MML_IMAGECAPTURE_FORMAT_BITMASK_PNG                     ((u32) 0x00000008)
#define MML_IMAGECAPTURE_FORMAT_BITMASK_TIFF                    ((u32) 0x00000010)
#define MML_IMAGECAPTURE_FORMAT_BITMASK_RAW                     ((u32) 0x00000020)

/** @ingroup    MMLayerImageEncoding
    @brief      Image capture capability
*/
typedef struct
{
    u32     nFormatSupported;    ///< Image formats supported
    u16     nMaxImageWidth;      ///< Maximum image width in pixels = MmlCameraCameraInfo_t::nMaxInterpolatedWidth
    u16     nMaxImageHeight;     ///< Maximum image height in pixels = MmlCameraCameraInfo_t::nMaxInterpolatedHeight
} MmlImageCaptureCapability_t;

/** @ingroup    MMLayerImageEncoding
    @brief      Get capture capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlImageGetCaptureCapability_t;

#define MML_IMAGEDECODING_FORMAT_BITMASK_JPEG                   ((u32) 0x00000001)
#define MML_IMAGEDECODING_FORMAT_BITMASK_GIF                    ((u32) 0x00000002)
#define MML_IMAGEDECODING_FORMAT_BITMASK_BMP                    ((u32) 0x00000004)
#define MML_IMAGEDECODING_FORMAT_BITMASK_PNG                    ((u32) 0x00000008)
#define MML_IMAGEDECODING_FORMAT_BITMASK_TIFF                   ((u32) 0x00000010)


#define MML_IMAGE_STEREOTYPE_BITMASK_RED_CYAN                   ((u32) 0x00000001)
#define MML_IMAGE_STEREOTYPE_BITMASK_LEFT_RIGHT                 ((u32) 0x00000002)
#define MML_IMAGE_STEREOTYPE_BITMASK_GLASSFREE                  ((u32) 0x00000004)
/** @ingroup    MMLayerImageDecoding
    @brief      Image decoding capability
*/
typedef struct
{
    u32     nFormatSupported;     ///< Image formats supported
    u16     nMaxImageWidth;       ///< Maximum image width in pixels
    u16     nMaxImageHeight;      ///< Maximum image height in pixels
    u32     nImageStereoSupported;///< Image stereo supported bitmask
} MmlImageDecodingCapability_t;

/** @ingroup    MMLayerImageDecoding
    @brief      Get decoding capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;             ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlImageGetDecodingCapability_t;

/** @ingroup    MMLayerImage
    @brief      Response payload
*/
typedef struct MmlImageResponse_t_
{
    MmlImageState_e         eState;                     ///< Current state
    u32                     nHandle;                    ///< 32-bit decoding/encoding handle

    /// union of MmlImageResponse_t parameters
	union
	{
        u32                             nEstimatedByteSize;    ///< Used with 'Get estimated capture size'
        MmlImageInfo_t                  tImageInfo;            ///< Used with 'Get image info'
        MmlImageStateChange_t           tStateChange;          ///< Used with 'IMAGE_ERROR_STATE_CHANGE' result
        //u32                             nNextFrameDelayTime;   ///< Used with 'Decode next frame', expressed in 10 milliseconds
        MmlImageCaptureInfo_t           tCaptureInfo;          ///< Used with 'Get capture info'
        MmlImageCaptureCapability_t     tCaptureCapability;    ///< Used with 'Get capture capability'
        MmlImageDecodingCapability_t    tDecodingCapability;   ///< Used with 'Get decoding capability'
        MmlImageMemoryParam_t           tMemoryParam;          ///< Used with 'Convert color format'
    } uParam;
} MmlImageResponse_t;

/** @ingroup    MMLayerImage
    @brief      Image use case parameters
*/
typedef struct
{
	u32                                 nUseCaseID;            ///< Use case ID
	MmlImageResponseCallback_t          *pResponseCallback;    ///< Pointer to the response callback registration data
	MmlImageResponse_t                  *pResponse;            ///< Pointer to the response payload

    /// union of MmlImageUCParam_t parameters
    union
	{
	    /* No parameter: 'Open decoding handle' */
        u32                                 nHandle;                    ///< Used with 'Abort decoding', 'Stop continuous capture', 'Close decoding handle'
        MmlImageEncodeImage_t               tEncodeImage;               ///< Used with 'Encode image (jpeg)'
	    MmlImageDecodeImage_t               tDecodeImage;               ///< Used with 'Decode image (jpeg, bmp, png, rgba)'
	    MmlImageSetJpegExifInfo_t           tSetJpegExifInfo;           ///< Used with 'Set jpeg exif info'
	    MmlImageGetImageInfo_t              tGetImageInfo;              ///< Used with 'Get image info'
	    MmlImageDecodeNextFrame_t           tDecodeNextFrame;           ///< Used with 'Decode next frame'
	    MmlImageGetCaptureInfo_t            tGetCaptureInfo;            ///< Used with 'Get capture info'
        MmlImageGetDecodingCapability_t     tGetDecodingCapability;     ///< Used with 'Get decoding capability'
        MmlImageGetCaptureCapability_t      tGetCaptureCapability;      ///< Used with 'Get capture capability'
        MmlImageConvertColorFormat_t        tConvertColorFormat;        ///< Used with 'Convert color format'
	} uParam;
} MmlImageUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLIMAGE_TYPES_H__
