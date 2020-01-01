//==============================================================================
//
//  File        : mmps_dsc.h
//  Description : INCLUDE File for the Host Application for DSC.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmps_dsc.h
 *  @brief The header File for the Host DSC control functions
 *  @author Penguin Torng
 *  @version 1.0
 */

#ifndef _MMPS_DSC_H_
#define _MMPS_DSC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "ait_config.h"
#include "aitu_calendar.h"
#include "mmps_display.h"
#include "mmp_ptz_inc.h"
#include "mmp_dsc_inc.h"
#include "mmp_icon_inc.h"
#include "mmpf_jpeg_enc_rc.h"

/** @addtogroup MMPS_DSC
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define EXIF_MANUAL_UPDATE          (1)
#define EXIF_ASCII_LENGTH           (64)
#define EXIF_CONFIG_ARRAY_SIZE      (16*1024)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPS_DSC_CUSTOM_QTABLE_TYPE
{
    MMPS_DSC_CUSTOM_QTABLE_OFF,
    MMPS_DSC_CUSTOM_QTABLE_ALL,
    MMPS_DSC_CUSTOM_QTABLE_MAIN,
    MMPS_DSC_CUSTOM_QTABLE_THUMB
} MMPS_DSC_CUSTOM_QTABLE_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

// Still Capture information
typedef struct _MMPS_DSC_CAPTURE_INFO
{
    MMP_USHORT              usPrimaryW;
    MMP_USHORT              usPrimaryH;
    MMP_USHORT              usThumbWidth;
    MMP_USHORT              usThumbHeight;
    MMP_JPGENC_RC_QUALITY_CTL stQualityCtl;
    MMP_BYTE                *bFileName;
    MMP_ULONG               ulFileNameLen;
    MMP_BOOL                bCaptureEn;
    MMP_BOOL                bExifEn;                                        ///< Enable EXIF function or not
    MMP_BOOL                bThumbnailEn;                                   ///< Enable thumbnail function or not
    MMP_BOOL                bFirstShot;                                     ///< First shot or second shot
    MMP_UBYTE               ubShotMode;                                     ///< The shot mode
    MMP_USHORT              usMaxShotNum;                                   ///< The max shot count
    MMP_UBYTE               ubUiMode;                                       ///< The UI mode
    MMP_UBYTE               ubCamSel;                                       ///< The camera ID
    MMP_UBYTE               ubRawFmt;                                       ///< The Raw YUV format
    AUTL_DATETIME           stDateTime;                                     ///< The stamp date time
    /* Capture Done Information */
    MMP_ULONG               ulPrimaryJpgAddr;                               ///< JPEG compress buffer address
    MMP_ULONG               ulPrimaryJpgSize;                               ///< Captured JPEG size
    MMP_ULONG               ulThumbnailAddr;                                ///< JPEG compress buffer address
    MMP_ULONG               ulThumbnailSize;                                ///< Captured JPEG size
    MMP_ULONG               ulExifHdrAddr;                                  ///< EXIF buffer address
    MMP_ULONG               ulExifHdrSize;                                  ///< EXIF size
    MMP_ULONG               ulJpegFileSize;                                 ///< Captured JPEG total size
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    MMP_ULONG               ulMpfDataStartAddr;                             ///< MPF data start address
    MMP_ULONG               ulMpfDataSize;                                  ///< MPF data size
    MMP_ULONG               ulLargeThumbExifAddr;                           ///< Large thumbnail Exif start address
    MMP_ULONG               ulLargeThumbExifSize;                           ///< Large thumbnail Exif data size
    MMP_ULONG               ulLargeThumbJpegAddr;                           ///< Large thumbnail Jpeg start address
    MMP_ULONG               ulLargeThumbJpegSize;                           ///< Large thumbnail Jpeg size
    #endif
    /** @brief  Its to add ISP related Info for AHC.
                AHC team will assign the address and the size of the buffer by themself.
                If we dont wanna use the extra buffer, we must set the addr of the buffer is 0.*/
    MMP_ULONG               ulExtraBufAddr;                                 ///< The extra buf is written after primary jpeg
    MMP_ULONG               ulExtraBufSize;                                 ///< The size of the extra buffer
    MMP_USHORT              usReviewTime;                                   ///< The time of review time
    MMP_USHORT              usWindowsTime;                                  ///< The time of window disable time
} MMPS_DSC_CAPTURE_INFO;

typedef struct _MMPS_DSC_PLAYBACK_INFO
{
    MMP_USHORT              usJpegWidth;                                    ///< JPEG picture original image width
    MMP_USHORT              usJpegHeight;                                   ///< JPEG picture original image height
    MMP_SCAL_FIT_MODE       eFitMode;                                       ///< Scaler fit mode
    MMP_USHORT              usScalOutWidth;                                 ///< JPEG picture scaled out width
    MMP_USHORT              usScalOutHeight;                                ///< JPEG picture scaled out height
    MMP_USHORT              usDispWinOfstX;                                 ///< JPEG picture GOP window offset X
    MMP_USHORT              usDispWinOfstY;                                 ///< JPEG picture GOP window offset Y
    MMP_USHORT              usDisplayWidth;                                 ///< JPEG picture GOP window width
    MMP_USHORT              usDisplayHeight;                                ///< JPEG picture GOP window height
    MMP_DSC_JPEG_INFO       stJpegInfo;                                     ///< JPEG file information
    MMP_DISPLAY_ROTATE_TYPE eRotateType;                                    ///< Rotation attribute when display
    MMP_BOOL                bMirror;                                        ///< LCD mirror or not
} MMPS_DSC_PLAYBACK_INFO;

typedef struct _MMPS_DSC_ZOOM_INFO
{
    MMP_UBYTE               scalerpath;

    MMP_USHORT              usMaxZoomRatio;
    MMP_USHORT              usMaxZoomSteps;
    MMP_USHORT              usCurZoomStep;

    MMP_SHORT               sMaxPanSteps;
    MMP_SHORT               sMinPanSteps;
    MMP_SHORT               sCurPanStep;

    MMP_SHORT               sMaxTiltSteps;
    MMP_SHORT               sMinTiltSteps;
    MMP_SHORT               sCurTiltStep;
} MMPS_DSC_ZOOM_INFO;

typedef struct _MMPS_DSC_ENC_PARAMS
{
    MMP_UBYTE               ubDscQtable[DSC_QTABLE_MAX_NUM][128];           ///< DSC capture, quality table
    MMP_ULONG               ulMaxThumbnailSize;                             ///< DSC capture, thumbnail maximum size
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    MMP_ULONG               ulMaxLargeThumbSize;                            ///< DSC capture, large thumbnail maximum size
    #endif
} MMPS_DSC_ENC_PARAMS;

typedef struct _MMPS_DSC_DEC_PARAMS
{
    MMP_ULONG               ulExifWorkingBufSize;                           ///< EXIF working buffer size
    MMP_ULONG               ulDscDecMaxCompBufSize;                         ///< DSC decode, reserve data input buffer size
    MMP_ULONG               ulDscDecMaxInbufSize;                           ///< DSC decode, reserve data temp buffer size
} MMPS_DSC_DEC_PARAMS;

typedef struct _MMPS_DSC_CONFIG
{
    MMPS_DSC_ENC_PARAMS     encParams;                                      ///< DSC capture related settings
    MMPS_DSC_DEC_PARAMS     decParams;                                      ///< DSC decode related settings
} MMPS_DSC_CONFIG;

#if (EXIF_MANUAL_UPDATE)
typedef struct _MMPS_DSC_EXIF_CONFIG
{
    MMP_ULONG               AtomSize;   //AtomSize should be ALIGN32(DataSize + 18)
    MMP_ULONG               DataSize;
    MMP_ULONG               TagID;
    MMP_ULONG               IfdID;
    MMP_ULONG               TagType;
    MMP_ULONG               TagDataSize;
    MMP_UBYTE               *Data;
} MMPS_DSC_EXIF_CONFIG;
#endif

typedef struct _MMPS_DSC_AHC_PREVIEW_INFO
{
    MMP_BOOL                bPreviewMirror;
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulPreviewBufW;
    MMP_ULONG               ulPreviewBufH;
    MMP_ULONG               ulDispStartX;
    MMP_ULONG               ulDispStartY;
    MMP_ULONG               ulDispWidth;
    MMP_ULONG               ulDispHeight;
    MMP_DISPLAY_COLORMODE   sDispColor;
} MMPS_DSC_AHC_PREVIEW_INFO;

typedef struct _MMPS_DSC_AHC_CAPTURE_INFO {
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulEncW;
    MMP_ULONG               ulEncH;
    MMP_ULONG               ulEncBufW;
    MMP_ULONG               ulEncBufH;
} MMPS_DSC_AHC_CAPTURE_INFO;

typedef struct _MMPS_DSC_AHC_PLAYBACK_INFO
{
    MMP_BOOL                bMirror;
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulDecodeOutW;
    MMP_ULONG               ulDecodeOutH;
    MMP_ULONG               ulDispStartX;
    MMP_ULONG               ulDispStartY;
    MMP_ULONG               ulDispWidth;
    MMP_ULONG               ulDispHeight;
    MMP_DISPLAY_COLORMODE   sDispColor;
} MMPS_DSC_AHC_PLAYBACK_INFO;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* Config Function */
MMPS_DSC_CONFIG* MMPS_DSC_GetConfig(void);
MMP_ERR MMPS_DSC_SetCallbackFunc(MMP_ULONG ulEvent, void *pCallback);

/* Memory Function */
MMP_ERR MMPS_DSC_CalculateJpeOBufAttr(MMP_UBYTE ubCompType, MMP_BOOL bVRCapture);
MMP_ERR MMPS_DSC_AllocFileNameBuf(void);
MMP_ERR MMPS_DSC_FreeFileNameBuf(void);
MMP_ERR MMPS_DSC_AllocExifEncBuf(void);
MMP_ERR MMPS_DSC_FreeExifEncBuf(void);

/* Preview Function */
MMP_ERR MMPS_DSC_AdjustScdCapturePipe(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_DSC_AdjustScdPreviewPipe(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_DSC_SetPreviewMode(MMP_USHORT usMode);
MMP_ERR MMPS_DSC_SetPreviewPath(MMP_UBYTE ubCamSel, MMP_DSC_PREVIEW_PATH ePath);
MMP_ERR MMPS_DSC_CustomedPreviewAttr(MMP_UBYTE  ubCamSel,
                                     MMP_BOOL   bMirror,
                                     MMP_UBYTE  sFitMode,
                                     MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                     MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                     MMP_USHORT usWinWidth, MMP_USHORT usWinHeight);
MMP_ERR MMPS_DSC_EnablePreviewDisplay(MMP_UBYTE ubCamSel, MMP_BOOL bEnable, MMP_BOOL bCheckFrameEnd);
MMP_ERR MMPS_DSC_GetPreviewPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable);
MMP_ERR MMPS_DSC_RestorePreview(MMP_UBYTE ubCamSel, MMP_USHORT usWindowsTime);
MMP_ERR MMPS_DSC_GetDisplayRes(MMP_UBYTE ubCamSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight);
MMP_ERR MMPS_DSC_GetDisplayPosition(MMP_UBYTE ubCamSel, MMP_ULONG *pulPosStartX, MMP_ULONG *pulPosStartY);

/* PTZ Function */
MMP_ERR MMPS_DSC_SetZoomConfig(MMP_USHORT usSteps, MMP_USHORT ubMaxRatio);
MMP_ERR MMPS_DSC_GetCurZoomStep(MMP_USHORT *usCurZoomStep);
MMP_ERR MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOM_DIR sZoomDir, MMP_USHORT usCurZoomStep);
MMP_UBYTE   MMPS_DSC_GetCurZoomStatus(void);

/* MJPEG Function */
MMP_ERR MMPS_DSC_SetVideo2MJpegResol(MMP_USHORT usW, MMP_USHORT usH);
MMP_ERR MMPS_DSC_SetVideo2MJpegEnable(MMP_BOOL bEnable);
MMP_ERR MMPS_DSC_SetTranscodeRate(MMP_ULONG InFpsx10, MMP_ULONG OutFpsx10, MMP_ULONG ulBitrate);
MMP_ERR MMPS_DSC_ConfigVideo2Mjpeg(MMP_SHORT usInputW, MMP_USHORT usInputH);

/* Capture Function */
MMP_ERR MMPS_DSC_CustomedEncResol(MMP_UBYTE ubCamSel, MMP_UBYTE sFitMode, MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPS_DSC_SetContiShotInterval(MMP_ULONG ulInterval);
MMP_ERR MMPS_DSC_SetJpeUIMode(MMP_UBYTE ubCompType, MMP_UBYTE ubMode);
MMP_ERR MMPS_DSC_SetMaxShotNum(MMP_UBYTE ubCompType, MMP_ULONG ulMaxShotNum);
MMP_ERR MMPS_DSC_SetJpegEncResol(MMP_UBYTE ubCompType, MMP_USHORT usEncW, MMP_USHORT usEncH);
MMP_ERR MMPS_DSC_SetShotMode(MMP_UBYTE ubCompType, MMP_UBYTE ubMode);
MMP_ERR MMPS_DSC_SetCustomQTable(MMP_UBYTE ubMode, MMP_UBYTE *pTable, MMP_UBYTE *pTableU, MMP_UBYTE *pTableV);
MMP_ERR MMPS_DSC_SetCaptureJpegQuality(MMP_UBYTE              ubRcIdx,
                                       MMP_BOOL               bTargetCtrl,
                                       MMP_BOOL               bLimitCtrl,
                                       MMP_ULONG              ulTargetSize,
                                       MMP_ULONG              ulLimitSize,
                                       MMP_USHORT             usMaxCount,
                                       MMP_JPGENC_RC_QUALITY_SEL   qualitylevel);
MMP_ERR MMPS_DSC_CaptureJPEG(   MMP_UBYTE               ubCompUseType,
                                MMPS_DSC_CAPTURE_INFO   *pCaptureInfo);

MMP_BOOL MMPS_DSC_CheckContiShotWriteFileDone(MMP_UBYTE ubCamSel);

/* Playback Function */
MMP_ERR MMPS_DSC_SetPlaybackMode(MMP_USHORT usDecodeMode);
MMP_ERR MMPS_DSC_CustomedPlaybackAttr(MMP_BOOL  bMirror,
                                      MMP_UBYTE sFitMode,
                                      MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                      MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                      MMP_USHORT usWinWidth, MMP_USHORT usWinHeight);
MMP_ERR MMPS_DSC_PlaybackJpeg(MMP_DSC_JPEG_INFO *pJpegInfo, MMP_ULONG ulScalOutW, MMP_ULONG ulScalOutH);
MMP_ERR MMPS_DSC_PlaybackCalculatePTZ(MMP_ULONG ulZoomStep,
                                      MMP_ULONG *pulGrabX,  MMP_ULONG *pulGrabY,
                                      MMP_ULONG *pulGrabW,  MMP_ULONG *pulGrabH);
MMP_ERR MMPS_DSC_PlaybackExecutePTZ(MMP_ULONG ulGrabX, MMP_ULONG ulGrabY,
                                    MMP_ULONG ulGrabW, MMP_ULONG ulGrabH);
MMP_ERR MMPS_DSC_ExitJpegPlayback(void);
MMP_ERR MMPS_DSC_GetJpegInfo(MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPS_DSC_DecodeThumbnail( MMP_DSC_JPEG_INFO *pJpegInfo,
                                  MMP_ULONG         ulOutputW,
                                  MMP_ULONG         ulOutputH);
MMP_ERR MMPS_DSC_ExitThumbDecodeMode(MMP_DSC_JPEG_INFO *pJpegInfo);
MMP_ERR MMPS_DSC_ExitThumbReEncodeMode(MMP_DSC_JPEG_INFO *pJpegInfo);

/* Exif Function */
MMP_ERR MMPS_DSC_EnableMultiPicFormat(MMP_BOOL bEnableMpf, MMP_BOOL bEnableLargeThumb);
MMP_ERR MMPS_DSC_ConfigLargeThumbRes(MMP_UBYTE ubResMode);
MMP_ERR MMPS_DSC_ConfigThumbnail(MMP_ULONG ThumbWidth, MMP_ULONG ThumbHeight);
MMP_ERR MMPS_DSC_OpenEXIFFile(MMP_UBYTE *pubFileName, MMP_USHORT usExifNodeId);
MMP_ERR MMPS_DSC_UpdateExifNode(MMP_USHORT    usExifNodeId,
                                MMP_USHORT    usIfd,  MMP_USHORT  usTag,
                                MMP_USHORT    usType, MMP_ULONG   ulCount,
                                MMP_UBYTE     *pData, MMP_ULONG   ulDataSize,
                                MMP_BOOL      bForUpdate);
MMP_ERR MMPS_DSC_GetImageEXIFInfo(MMP_USHORT usExifNodeId, MMP_USHORT usIfd, MMP_USHORT usTag, MMP_UBYTE *pData, MMP_ULONG *pulSize);
MMP_ERR MMPS_DSC_CloseEXIFFile(MMP_USHORT usExifNodeId);

#if (EXIF_MANUAL_UPDATE)
MMP_BOOL MMPS_DSC_GetImageEXIF(MMP_ULONG Index, MMPS_DSC_EXIF_CONFIG *pExif);
MMP_BOOL MMPS_DSC_SetImageEXIF(MMP_UBYTE *pData, MMP_ULONG DataSize, MMP_USHORT uwIfdIdx, MMP_USHORT uwTagID,
                               MMP_USHORT uwType, MMP_USHORT uwCount);
#endif

/* Storage Function */
MMP_ERR MMPS_DSC_JpegDram2Card(MMPS_DSC_CAPTURE_INFO *pCaptureInfo);
MMP_ERR MMPS_DSC_ThumbDram2Card(MMPS_DSC_CAPTURE_INFO *pCaptureInfo, MMP_ULONG ulStreamType);

/// @}

#endif // _MMPS_DSC_H_
