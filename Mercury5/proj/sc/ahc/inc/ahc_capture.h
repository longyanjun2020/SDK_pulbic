/**
 @file ahc_capture.h
 @brief Header File for the AHC capture API.
 @author 
 @version 1.0
*/

#ifndef _AHC_CAPTURE_H_
#define _AHC_CAPTURE_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "AHC_Config_SDK.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

// Debug after JPG, Test version debug only!
#define ENABLE_DEBUG_AFTER_JPG          (0)

#define AHC_CAPTURE_SYNC_STAMP_FILENAME (0)

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_EXIF_CONFIG {
    UINT32  AtomSize;   //AtomSize should be ALIGN32(DataSize + 18)
    UINT32  DataSize;
    UINT32  TagID;
    UINT32  IfdID;
    UINT32  TagType;
    UINT32  TagDataSize;
    UINT8   *Data;
} AHC_EXIF_CONFIG;

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _AHC_CAPTURE_MODE {
    STILL_CAPTURE_MODE,
    STILL_SET_ONLY_MODE,
    VIDEO_CAPTURE_MODE
} AHC_CAPTURE_MODE;

typedef enum _AHC_CAPTURE_CONFIG {
    ACC_DATE_STAMP,
    ACC_CUS_THUMB_W,
    ACC_CUS_THUMB_H,
} AHC_CAPTURE_CONFIG;

typedef enum _AHC_CUSTOMER_QT {
    CUSTOM_QT_OFF = 0,
    CUSTOM_QT_ALL,
    CUSTOM_QT_MAIN,
    CUSTOM_QT_THUMB
} AHC_CUSTOMER_QT;

typedef enum _AHC_ACC_TIMESTAMP_CONFIG {
    AHC_ACC_TIMESTAMP_DISABLE       = 0x0,
    AHC_ACC_TIMESTAMP_ENABLE        = 0x1,
    AHC_ACC_TIMESTAMP_DATE_ONLY     = (0x0 << 1),
    AHC_ACC_TIMESTAMP_TIME_ONLY     = (0x1 << 1),
    AHC_ACC_TIMESTAMP_DATE_AND_TIME = (0x2 << 1),
    AHC_ACC_TIMESTAMP_BOTTOM_RIGHT  = (0x0 << 3),
    AHC_ACC_TIMESTAMP_BOTTOM_LEFT   = (0x1 << 3),
    AHC_ACC_TIMESTAMP_TOP_RIGHT     = (0x2 << 3),
    AHC_ACC_TIMESTAMP_TOP_LEFT      = (0x3 << 3),
    AHC_ACC_TIMESTAMP_FORMAT_1      = (0x0 << 5), // YYYY MM DD hh:mm:ss
    AHC_ACC_TIMESTAMP_FORMAT_2      = (0x1 << 5), // YYYY/MM/DD hh:mm:ss
    AHC_ACC_TIMESTAMP_FORMAT_3      = (0x2 << 5), // DD/MM/YYYY hh:mm:ss
    AHC_ACC_TIMESTAMP_FORMAT_4      = (0x3 << 5), // MM/DD/YYYY hh:mm:ss
    AHC_ACC_TIMESTAMP_LOGOEX        = (0x1 << 7),
    AHC_ACC_TIMESTAMP_DATEEX        = (0x1 << 8)
} AHC_ACC_TIMESTAMP_CONFIG;

typedef enum _AHC_ACC_TIMESTAMP_CONFIG_MASK {
    AHC_ACC_TIMESTAMP_ENABLE_MASK   = 0x1,
    AHC_ACC_TIMESTAMP_DATE_MASK     = 0x6,
    AHC_ACC_TIMESTAMP_POSITION_MASK = 0x18,
    AHC_ACC_TIMESTAMP_FORMAT_MASK   = 0x60,
    AHC_ACC_TIMESTAMP_LOGOEX_MASK   = AHC_ACC_TIMESTAMP_LOGOEX,
    AHC_ACC_TIMESTAMP_DATEEX_MASK   = AHC_ACC_TIMESTAMP_DATEEX
} AHC_ACC_TIMESTAMP_CONFIG_MASK;

typedef enum _AHC_CAPTURE_CALLBACK_TYPE // Sync With MMP_JPEG_ENC_CALLBACK_TYPE
{
    AHC_CAPTURE_CALLBACK_CAPTURE_START = 0,
    AHC_CAPTURE_CALLBACK_STORECARD_START,
    AHC_CAPTURE_CALLBACK_STORECARD_END,
    AHC_CAPTURE_CALLBACK_STORECARD_ERROR
} AHC_CAPTURE_CALLBACK_TYPE;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

/** @addtogroup AHC_CAPTURE
@{
*/

/* EXIF Function */
AHC_BOOL    AHC_Capture_SetImageEXIF(UINT8 *pData,UINT32 DataSize,UINT16 uwIfdIdx, UINT16 uwTagID, UINT16 uwType, UINT16 uwCount);
AHC_BOOL    AHC_Capture_GetImageEXIF(UINT32 Index, AHC_EXIF_CONFIG *pExif);
AHC_BOOL    AHC_Capture_OpenEXIFFileByName(UINT8 *sFileName);
AHC_BOOL    AHC_Capture_CloseEXIFFile(void);
AHC_BOOL    AHC_Capture_ConfigSysInfoEXIF(void);
AHC_BOOL    AHC_Capture_ConfigMenuEXIF(void);
AHC_BOOL    AHC_Capture_ConfigRtcEXIF(void);

/* Capture Config Function */
AHC_BOOL    AHC_Capture_SetConfig(AHC_CAPTURE_CONFIG byConfig, UINT16 u16Op);
AHC_BOOL    AHC_Capture_GetConfig(AHC_CAPTURE_CONFIG byConfig, UINT32 *pu32Op);
AHC_BOOL    AHC_Capture_SetCompressRatio(UINT8 u8CamSel, UINT16 u16Ratio);
UINT32      AHC_Capture_GetImageTargetSizeInKB(UINT8 u8CamSel);
AHC_BOOL    AHC_Capture_SetCompressionQuality(UINT32 u32Quality);
AHC_BOOL    AHC_Capture_SetReviewTime(UINT16 u16ReviewTime, UINT16 u16WindowsTime);
AHC_BOOL    AHC_Capture_SetImageSize(UINT8 u8CamSel, UINT16 wSizeX, UINT16 wSizeY);
AHC_BOOL    AHC_Capture_GetImageSize(UINT8 u8CamSel, UINT32 *wSizeX, UINT32 *wSizeY);
AHC_BOOL    AHC_Capture_IsScdCamConnect(void);
AHC_BOOL    AHC_Capture_SetScdCamCaptSetting(void);

/* Capture PTZ Function */
AHC_BOOL    AHC_Capture_GetCurZoomStep(UINT16 *pu16ZoomStepNum);
AHC_BOOL    AHC_Capture_GetMaxZoomStep(UINT16 *pu16ZoomStepNum);
AHC_BOOL    AHC_Capture_GetMaxZoomRatio(UINT16 *pu16ZoomRatio);
AHC_BOOL    AHC_Capture_GetDigitalZoomRatio(UINT32 *pu32ZoomRatio);
UINT8       AHC_Capture_GetCurZoomStatus(void);

/* Capture Function */
AHC_BOOL    AHC_Capture_SetDBGDataAfterJPEG(UINT8 *ubAddress, UINT32 *ulLength);
AHC_BOOL    AHC_Capture_SetPreviewMode(AHC_BOOL bRawPreview, AHC_BOOL bCaptureReturn);
AHC_BOOL    AHC_Capture_StopPreview(void);
AHC_BOOL    AHC_Capture_StartTakeJpeg(UINT8 u8Mode);

AHC_BOOL    AHC_Capture_GetFileName(UINT16 *CaptureDirKey, INT8 *pJpgFileName, UINT8 *CaptureFileName, UINT8 bCamSel);
AHC_BOOL    AHC_Capture_PreAddFile(UINT16 u16CaptureDirKey, UINT8 *pu8CaptureFileName);
AHC_BOOL    AHC_Capture_PostAddFile(UINT16 u16CaptureDirKey, UINT8 *pu8CaptureFileName);
UINT8       AHC_Capture_GetCamStatusForDCF(void);

/// @}

#endif //_AHC_CAPTURE_H_
