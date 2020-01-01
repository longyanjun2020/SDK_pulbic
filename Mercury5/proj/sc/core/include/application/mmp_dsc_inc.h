//==============================================================================
//
//  File        : mmp_dsc_inc.h
//  Description : INCLUDE File for the DSC Driver Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_DSC_INC_H_
#define _MMP_DSC_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_exif_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define INVALID_JPEG_FILE_ID            0xFFFFFFFF

#ifndef DSC_MAX_FILE_NAME_SIZE
#define DSC_MAX_FILE_NAME_SIZE          (256)
#endif

#define DSC_SUPPORT_BASELINE_MP_FILE    (0) // Support Baseline Multi-Picture Format, Only for SportCam

#define DSC_QTABLE_ARRAY_SIZE           (64)

#define DSC_CAPTURE_MAX_CAM_NUM         (3)

#define DSC_ENC_THUMBNAIL_OK            (1) // TBD. Wait Encode Thumbnail Ready

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_DSC_JPEG_FMT
{
    MMP_DSC_JPEG_FMT420 = 0,
    MMP_DSC_JPEG_FMT422,
    MMP_DSC_JPEG_FMT422_V,
    MMP_DSC_JPEG_FMT444,
    MMP_DSC_JPEG_FMT411,
    MMP_DSC_JPEG_FMT411_V,
    MMP_DSC_JPEG_FMT_NOT_3_COLOR,
    MMP_DSC_JPEG_FMT_NOT_BASELINE,
    MMP_DSC_JPEG_FMT_FORMAT_ERROR
} MMP_DSC_JPEG_FMT;

typedef enum _MMP_DSC_PREVIEW_PATH
{
    MMP_DSC_STD_PREVIEW = 0,
    MMP_DSC_RAW_PREVIEW,
    MMP_DSC_PREVIEW_PATH_NUM
} MMP_DSC_PREVIEW_PATH;

#if (DSC_SUPPORT_BASELINE_MP_FILE)
typedef enum _MMP_DSC_LARGE_THUMB_RES
{
    MMP_DSC_LARGE_THUMB_RES_FHD = 0,
    MMP_DSC_LARGE_THUMB_RES_VGA,
    MMP_DSC_LARGE_THUMB_RES_NUM
} MMP_DSC_LARGE_THUMB_RES;
#endif

typedef enum _MMP_DSC_JPEG_SETTYPE 
{
    MMP_MJPEG_CMD_NEW_ONE  = 0,             ///< New one stream JPEG
    MMP_MJPEG_CMD_SET_COMPBUF,              ///< Set compress buffer info
    MMP_MJPEG_CMD_STREAM_EN,                ///< JPEG encode for streaming
    MMP_MJPEG_CMD_CHECK_ENC_DONE,           ///< Check JPEG encode done
    MMP_MJPEG_CMD_SET_FPS,                  ///< Set frame rate
    MMP_MJPEG_CMD_SET_MODE                  ///< Set MJPG Mode ID
} MMP_DSC_JPEG_SETTYPE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _JPG_QUEUE_PTR
{
    MMP_ULONG               ulWrWrap;
    MMP_ULONG               ulRdWrap;
    MMP_ULONG               ulWrIdx;
    MMP_ULONG               ulRdIdx;
} JPG_QUEUE_PTR;

typedef struct _MMP_DSC_JPEGINFO 
{
    MMP_BYTE                bJpegFileName[DSC_MAX_FILE_NAME_SIZE];          ///< Input path (File mode)
    MMP_USHORT              usJpegFileNameLength;                           ///< Input path (File mode)
    MMP_ULONG               ulJpegBufAddr;                                  ///< Input path (Memory mode)
    MMP_ULONG               ulJpegBufSize;                                  ///< Input path (Memory mode)
    MMP_BOOL                bValid;                                         ///< bValid is true means that JPEG is the supported format.
    MMP_ULONG               ulFileSize;                                     ///< This indicate the JPEG file size.
    /* Primary Attribute */
    MMP_USHORT              usPrimaryWidth;                                 ///< This indicate the primary JPEG width.
    MMP_USHORT              usPrimaryHeight;                                ///< This indicate the primary JPEG height.
    MMP_DSC_JPEG_FMT        ePrimaryFormat;                                 ///< This indicate the primary JPEG color format.
    MMP_ULONG               ulPrimaryOffset;                                ///< This indicate the primary offset.
    MMP_ULONG               ulPrimarySize;                                  ///< This indicate the primary size.    
    /* Thumbnail Attribute */
    MMP_BOOL                bDecVRThumb;                                    ///< This indicate the decode VR thumbnail.
    MMP_BOOL                bDecPrm2Thumb;                                  ///< This indicate the decode primary JPEG as thumbnail.
    MMP_BOOL                bDecodeThumbnail;                               ///< This indicate the decode thumbnail or not.
    MMP_USHORT              usThumbWidth;                                   ///< This indicate the thumbnail width.
    MMP_USHORT              usThumbHeight;                                  ///< This indicate the thumbnail height.
    MMP_DSC_JPEG_FMT        eThumbFormat;                                   ///< This indicate the thumbnail color format.
    MMP_ULONG               ulThumbOffset;                                  ///< This indicate the thumbnail offset.
    MMP_ULONG               ulThumbSize;                                    ///< This indicate the thumbnail size.
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    /* Large Thumbnail Attribute */
    MMP_BOOL                bDecodeLargeThumb;                              ///< This indicate the decode large thumbnail or not.
    MMP_USHORT              usLargeThumbWidth;                              ///< This indicate the large thumbnail width.
    MMP_USHORT              usLargeThumbHeight;                             ///< This indicate the large thumbnail height.
    MMP_DSC_JPEG_FMT        eLargeThumbFormat;                              ///< This indicate the large thumbnail color format.
    MMP_ULONG               ulLargeThumbOffset;                             ///< This indicate the large thumbnail offset.
    MMP_ULONG               ulLargeThumbSize;                               ///< This indicate the large thumbnail size.	
    #endif
    MMP_BOOL                bPowerOffLogo;
    /* ReEncode Thumbnail Attribute */
    MMP_BOOL                bReEncodeThumb;
    MMP_ULONG               ulReEncodeThumbAddr;
    MMP_ULONG               ulReEncodeThumbSize;
} MMP_DSC_JPEG_INFO;

typedef MMP_ERR (MMP_DSC_CALLBACK)(void*);

#endif //_MMP_DSC_INC_H_
