//==============================================================================
//
//  File        : mmps_dsc.c
//  Description : Ritian DSC Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
 *  @file mmps_dsc.c
 *  @brief The DSC control functions
 *  @author Penguin Torng
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "ptz_cfg.h"
#include "snr_cfg.h"
#include "mmp_snr_inc.h"
#include "mmp_display_inc.h"
#include "mmps_dsc.h"
#include "mmps_3gprecd.h"
#include "mmpd_fctl.h"
#include "mmpd_ptz.h"
#include "mmpd_dsc.h"
#include "mmpd_dma.h"
#include "mmpf_scaler.h"
#include "mmpf_ringbuf.h"
#include "mmpf_jpeg_enc.h"
#include "mmpf_jpeg_enc_rc.h"
#include "mmpf_sensor.h"

#include "component_cfg.h"
#include "component_raws.h"
#include "component_scl.h"
#include "component_jpe.h"
#include "component_jpd.h"
#include "component_dip.h"
#include "component_pip.h"
#include "component_display.h"
#include "component_mfe.h"
#include "cust_component_cfg.h"

/** @addtogroup MMPS_DSC
@{
*/

#if defined(ALL_FW)

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_DSC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_DSC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define DSC_MAX_CAM_NUM (2) // (JPGENC_MAX_CAM_SEL_NUM)

#define THUMB_DIP_1ST_SCALE_OUT_W   864
#define THUMB_DIP_1ST_SCALE_OUT_H   480
#define THUMB_DIP_2ND_SCALE_OUT_W   256
#define THUMB_DIP_2ND_SCALE_OUT_H   192
#define THUMB_DIP_3RD_SCALE_OUT_W   192
#define THUMB_DIP_3RD_SCALE_OUT_H   128

#define DSC_PLAYBACK_DIP_1ST_SCALE_OUT_W   864
#define DSC_PLAYBACK_DIP_1ST_SCALE_OUT_H   480

//==============================================================================
//
//                              INTERNAL ENUMERATION
//
//==============================================================================

typedef enum
{
    MMPS_JPG_ENC_COMP_BUFFER = 0,
    MMPS_JPG_ENC_VR_CAPTURE_COMP_BUFFER,
    MMPS_JPG_ENC_LARGE_THUMB_COMP_BUFFER,
    MMPS_JPG_EXIF_WORK_BUFFER,
    MMPS_JPG_EXIF_STORE_BUFFER,
    MMPS_JPG_DEC_INT_BUFFER
} MMPS_JPG_BUF_TYPE;

//==============================================================================
//
//                              INTERNAL STRUCTURES
//
//==============================================================================

#if (VIDEO_DEC_TO_MJPEG)
static struct MMPS_TRANSCODE_CONFIG {
    MMP_ULONG   ulInFpsx10;
    MMP_ULONG   ulOutFpsx10;
    MMP_ULONG   ulBitrate;
} m_transcode;
#endif

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

/**@brief The DSC configuration

Use @ref MMPS_DSC_GetConfig to assign the field value of it.
You should read this functions for more information.
*/
static MMPS_DSC_CONFIG              m_stDscConfig;

/**@brief The DSC preview mode.

Use @ref MMPS_DSC_SetPreviewMode to set it.
It will be referred when accessing preview function.

For example :
    DSC Mode0: For 240 X 180 to LCD (Normal Mode)
    DSC Mode1: For 240 X 320 full screen to LCD (FullScreen Mode)
    DSC Mode2: For 720 X 480 to TV (TV Mode)
*/
static MMP_USHORT                   m_usDscPreviewMode = 0;

/**@brief The DSC decode mode.

Use @ref MMPS_DSC_SetPlaybackMode to set it.
It will be referred when accessing decode function.

For example :
    DSC_NORMAL_DECODE_MODE      0
    DSC_FULL_DECODE_MODE        1
    DSC_TV_NTSC_DECODE_MODE     2
    DSC_TV_PAL_DECODE_MODE      3
    DSC_HDMI_DECODE_MODE        4
    DSC_CCIR_DECODE_MODE        5
*/
static MMP_USHORT                   m_usDscDecMode = 0;

/**@brief The DSC capture mode.
Use @ref MMPS_DSC_SetShotMode to set it.
It will be referred when accessing capture function.
*/
static MMP_USHORT                   m_usDscShotMode[JPE_COMP_USAGE_NUM] = {JPE_COMP_SINGLE_SHOT, JPE_COMP_SINGLE_SHOT, JPE_COMP_SINGLE_SHOT};
static MMP_ULONG                    m_ulMaxShotCnt[JPE_COMP_USAGE_NUM] = {1, 1, 1};
static MMP_UBYTE                    m_ubJpeUIMode[JPE_COMP_USAGE_NUM] = {0, 0};

/**@brief The DSC capture JPEG resolution.

Use @ref MMPS_DSC_SetJpegEncResol to set it.
It will be referred when accessing preview and capture function.
*/
static MMP_USHORT                   m_usStillJpegWidth[JPE_COMP_USAGE_NUM]   = {320};
static MMP_USHORT                   m_usStillJpegHeight[JPE_COMP_USAGE_NUM]  = {240};

static MMP_UBYTE                    m_ubJpegEncRawFmt[JPE_COMP_USAGE_NUM] = {MMP_JPEG_ENC_RAW_YUYV};

/**@brief The Motion JPEG width / height.

Use @ref MMPS_DSC_SetVideo2MJpegResol to set it.
*/
static MMP_USHORT                   m_usVid2MJpegWidth  = 1920;
static MMP_USHORT                   m_usVid2MJpegHeight = 1080;

/**@brief The DSC current preview On/Off.

Use @ref MMPS_DSC_EnablePreviewDisplay to change it state.
And use @ref MMPS_DSC_GetPreviewPipeStatus to get the value
It will be referred when accessing preview function.
*/
static MMP_BOOL                     m_bDscPreviewActive[DSC_MAX_CAM_NUM]  = {MMP_FALSE, MMP_FALSE};

/**@brief The playback information for one picture

Use @ref MMPS_DSC_PlaybackJpeg will set the initial value.
*/
static MMPS_DSC_PLAYBACK_INFO       m_stJpegPlayInfo;

/**@brief The preview zoom information

Use @ref It will be adjusted or referred by @ref MMPS_DSC_SetPreviewZoom.
*/
static MMPS_DSC_ZOOM_INFO           m_DscPreviewZoomInfo;
static MMP_USHORT                   m_usDSCStaticZoomIndex = 0;

/**@brief The MJPEG encode done mode.
*/
static MMP_JPEG_ENC_DONE_MODE       m_eMjpegEncDoneMode = 0;

#if (DSC_SUPPORT_BASELINE_MP_FILE)
static MMP_BOOL                     m_bMultiPicFormatEnable = MMP_FALSE;        // Enable Multi-Picture Format.
static MMP_BOOL                     m_bEncLargeThumbEnable  = MMP_FALSE;        // Enable encode large thumbnail.
static MMP_ULONG                    m_ulLargeThumbWidth     = 1920;
static MMP_ULONG                    m_ulLargeThumbHeight    = 1080;
static MMP_UBYTE                    m_ubLargeThumbResMode   = MMP_DSC_LARGE_THUMB_RES_FHD;
static MMP_ULONG                    m_ulLargeThumbJpegCompStart;                // Capture buffer start address for large thumbnail
static MMP_ULONG                    m_ulLargeThumbJpegCompEnd;                  // Capture buffer end address for large thumbnail
static MMP_ULONG                    m_ulPrimaryJpeg4LargeThumbDecodeOutStart;   // The start address of the buffer which store decoded primary jpeg for large thumbnail
static MMP_ULONG                    m_ulPrimaryJpeg4LargeThumbDecodeOutSize;    // The size of decoded primary jpeg for large thumbnail
#endif

/**@brief The EXIF buffer.
*/
static MMP_ULONG                    m_ulExifHeaderBufAddr[DSC_MAX_CAM_NUM] = {0, 0};

/** @brief we use preview mode with rawproc, and its color depth of rawproc.
*/
static MMP_DSC_PREVIEW_PATH         m_eDscPreviewPath[DSC_MAX_CAM_NUM]      = {MMP_DSC_STD_PREVIEW, MMP_DSC_STD_PREVIEW};

/* For rate control */
static MMP_BOOL                     m_bUseCustomJpegQT          = MMP_FALSE;
static MMP_BOOL                     m_bUseCustomThumbQT         = MMP_FALSE;
static MMP_UBYTE                    m_ubCustomJpegQT[3][DSC_QTABLE_ARRAY_SIZE];
static MMP_UBYTE                    m_ubCustomThumbQT[3][DSC_QTABLE_ARRAY_SIZE];

/* For AHC layer use */
static MMPS_DSC_AHC_PREVIEW_INFO    m_stDscCustPrevInfo[DSC_MAX_CAM_NUM];
static MMPS_DSC_AHC_CAPTURE_INFO    m_stDscCustCaptInfo[DSC_MAX_CAM_NUM];
static MMPS_DSC_AHC_PLAYBACK_INFO   m_stDscCustPlayInfo;
static MMP_BOOL                     m_bAhcConfigDscZoom         = MMP_FALSE;

/* For playback attribute */
static MMP_ULONG                    m_ulJpegDecIntBufAddr[MAX_JPD_COMP_NUM] = {0, 0};
static MMP_ULONG                    m_ulJpegDecIntBufSize[MAX_JPD_COMP_NUM] = {0, 0};

/* For Ring buffer */
static MMP_ULONG                    m_ulMaxContiShotRingBufSize = 8 * 1024 * 1024;
static MMP_ULONG                    m_ulMaxMJPEGRingBufSize     = 4 * 1024 * 1024;

#if (EXIF_MANUAL_UPDATE)
static MMP_UBYTE                    m_ubExifSettingArray[EXIF_CONFIG_ARRAY_SIZE] = {0};
#endif

/* For Callback */
static MMP_DSC_CALLBACK             *MMP_JPEG_ENC_StartCaptureCallback   = NULL;
static MMP_DSC_CALLBACK             *MMP_JPEG_ENC_StartStoreCardCallback = NULL;
static MMP_DSC_CALLBACK             *MMP_JPEG_ENC_EndStoreCardCallback   = NULL;
MMP_DSC_CALLBACK                    *MMP_JPEG_ENC_ErrorStoreCardCallback = NULL;

static MMP_BOOL                     m_bDscPlaybackReScale = MMP_FALSE;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

#if (VIDEO_DEC_TO_MJPEG)
extern MMP_BOOL m_bEncodeMJpegFromVideo;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

static MMP_ERR MMPS_DSC_InitDigitalZoomParam(void);
static MMP_ERR MMPS_DSC_RestoreDigitalZoomRange(void);
static MMP_ERR MMPS_DSC_EncodeThumbnail(MMP_UBYTE               ubParentCompType,
                                        MMPS_DSC_CAPTURE_INFO   *pDscCaptInfo);

#if (DSC_SUPPORT_BASELINE_MP_FILE)
static MMP_ERR MMPS_DSC_EncodeLargeThumb(MMP_ULONG              ulThumbWidth,
                                         MMP_ULONG              ulThumbHeight,
                                         MMP_ULONG              *pThumbnailSize);
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____Config_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetConfig
//  Description :
//------------------------------------------------------------------------------
/** @brief Get the configuration for the DSC function, including parameters for preview/capture/zoom and playback.

@return It reports configuration of the DSC function.
*/
MMPS_DSC_CONFIG* MMPS_DSC_GetConfig(void)
{
    return &m_stDscConfig;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetCallbackFunc
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetCallbackFunc(MMP_ULONG ulEvent, void *pCallback)
{
    switch (ulEvent) {
        case MMP_JPEG_ENC_CALLBACK_CAPTURE_START:
            MMP_JPEG_ENC_StartCaptureCallback    = (MMP_DSC_CALLBACK *)pCallback;
            break;
        case MMP_JPEG_ENC_CALLBACK_STORECARD_START:
            MMP_JPEG_ENC_StartStoreCardCallback  = (MMP_DSC_CALLBACK *)pCallback;
            break;
        case MMP_JPEG_ENC_CALLBACK_STORECARD_END:
            MMP_JPEG_ENC_EndStoreCardCallback    = (MMP_DSC_CALLBACK *)pCallback;
            break;
        case MMP_JPEG_ENC_CALLBACK_STORECARD_ERROR:
            MMP_JPEG_ENC_ErrorStoreCardCallback  = (MMP_DSC_CALLBACK *)pCallback;
            break;
        default:
            break;
    }

    return MMP_ERR_NONE;
}

#if 0
void _____Memory_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetBufferSize
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_GetBufferSize(  MMP_UBYTE   ubBufType,
                                        MMP_USHORT  usWidth,
                                        MMP_USHORT  usHeight,
                                        MMP_ULONG   *pulSize)
{
    switch(ubBufType){

    case MMPS_JPG_ENC_COMP_BUFFER:
        // Includes primary jpeg and thumbnail (YUV420)
        *pulSize = (usWidth * usHeight * 3 / 4);
        break;
    case MMPS_JPG_ENC_VR_CAPTURE_COMP_BUFFER:
        // Includes primary jpeg and thumbnail (YUV420)
        *pulSize = (usWidth * usHeight * 3 / 4);
        break;
    case MMPS_JPG_ENC_LARGE_THUMB_COMP_BUFFER:
        *pulSize = (usWidth * usHeight) >> 1;
        break;
    case MMPS_JPG_EXIF_WORK_BUFFER:
        *pulSize = 0x20000;  // 128KB
        break;
    case MMPS_JPG_EXIF_STORE_BUFFER:
        *pulSize = 0x10000;  // 64KB
        break;
    case MMPS_JPG_DEC_INT_BUFFER:
        *pulSize = 0x400;    // 1KB
        break;
    default:
        MMPS_DSC_DBG_ERR(1, "UnSupported Buffer Type !!!\r\n");
        *pulSize = 0;
        return MMP_DSC_ERR_CAPTURE_FAIL;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : _MMPS_DSC_AllocExifEncWorkingBuf
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR _MMPS_DSC_AllocExifEncWorkingBuf(MMP_USHORT usExifNodeId, MMP_BOOL bMPFEnable)
{
    MMP_ULONG   ulCurExifBufAddr = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    void*       pvExifBufVirt = NULL;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetExifWorkingBuffer(usExifNodeId, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_FALSE);

    if (ulCurExifBufAddr == 0) {
        MMPS_DSC_GetBufferSize(MMPS_JPG_EXIF_WORK_BUFFER, 0, 0, &ulCurExifBufSize);

        eCamOsRet = CamOsDirectMemAlloc("EXIF_ENC", ulCurExifBufSize, &pvExifBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_DSC_SetExifWorkingBuffer(usExifNodeId, (MMP_UBYTE*)pvExifBufVirt, ulCurExifBufSize, MMP_FALSE);

        if (bMPFEnable) {
            MMPD_DSC_SetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, (MMP_UBYTE*)pvExifBufVirt, ulCurExifBufSize, MMP_FALSE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : _MMPS_DSC_FreeExifEncWorkingBuf
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR _MMPS_DSC_FreeExifEncWorkingBuf(MMP_USHORT usExifNodeId, MMP_BOOL bMPFEnable)
{
    MMP_ULONG   ulCurExifBufAddr = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetExifWorkingBuffer(usExifNodeId, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_FALSE);

    if (ulCurExifBufAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulCurExifBufAddr, ulCurExifBufSize);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_DSC_SetExifWorkingBuffer(usExifNodeId, 0, 0, MMP_FALSE);
    }

    if (bMPFEnable) {
        MMPD_DSC_GetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_FALSE);

        if (ulCurExifBufAddr) {
            eCamOsRet = CamOsDirectMemRelease((void*)ulCurExifBufAddr, ulCurExifBufSize);
            CAM_OS_RET_CHK(eCamOsRet);

            MMPD_DSC_SetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, 0, 0, MMP_FALSE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : _MMPS_DSC_AllocExifDecWorkingBuf
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR _MMPS_DSC_AllocExifDecWorkingBuf(MMP_USHORT usExifNodeId, MMP_BOOL bMPFEnable)
{
    MMP_ULONG   ulCurExifBufAddr = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    void*       pvExifBufVirt = NULL;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetExifWorkingBuffer(usExifNodeId, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_TRUE);

    if (ulCurExifBufAddr == 0) {
        MMPS_DSC_GetBufferSize(MMPS_JPG_EXIF_WORK_BUFFER, 0, 0, &ulCurExifBufSize);

        eCamOsRet = CamOsDirectMemAlloc("EXIF_DEC", ulCurExifBufSize, &pvExifBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_DSC_SetExifWorkingBuffer(usExifNodeId, (MMP_UBYTE*)pvExifBufVirt, ulCurExifBufSize, MMP_TRUE);

        if (bMPFEnable) {
            MMPD_DSC_SetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, (MMP_UBYTE*)pvExifBufVirt, ulCurExifBufSize, MMP_TRUE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : _MMPS_DSC_FreeExifDecWorkingBuf
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR _MMPS_DSC_FreeExifDecWorkingBuf(MMP_USHORT usExifNodeId, MMP_BOOL bMPFEnable)
{
    MMP_ULONG   ulCurExifBufAddr = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetExifWorkingBuffer(usExifNodeId, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_TRUE);

    if (ulCurExifBufAddr) {
        eCamOsRet = CamOsDirectMemRelease((void*)ulCurExifBufAddr, ulCurExifBufSize);
        CAM_OS_RET_CHK(eCamOsRet);

        MMPD_DSC_SetExifWorkingBuffer(usExifNodeId, 0, 0, MMP_TRUE);
    }

    if (bMPFEnable) {
        MMPD_DSC_GetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, &ulCurExifBufAddr, &ulCurExifBufSize, MMP_TRUE);

        if (ulCurExifBufAddr) {
            eCamOsRet = CamOsDirectMemRelease((void*)ulCurExifBufAddr, ulCurExifBufSize);
            CAM_OS_RET_CHK(eCamOsRet);

            MMPD_DSC_SetExifWorkingBuffer(EXIF_NODE_ID_LARGE_THUMB1, 0, 0, MMP_TRUE);
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AllocExifEncBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_AllocExifEncBuf(void)
{
    MMP_UBYTE   i = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    void*       pvExifStoreBufVirt = NULL;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        _MMPS_DSC_AllocExifEncWorkingBuf(EXIF_NODE_ID_PRIMARY, MMP_TRUE);
    }
    else
    #endif
    {
        _MMPS_DSC_AllocExifEncWorkingBuf(EXIF_NODE_ID_PRIMARY, MMP_FALSE);
    }

    MMPS_DSC_GetBufferSize(MMPS_JPG_EXIF_STORE_BUFFER, 0, 0, &ulCurExifBufSize);

    for (i = 0; i < DSC_MAX_CAM_NUM; i++) {
        if (m_ulExifHeaderBufAddr[i] == 0) {
            eCamOsRet = CamOsDirectMemAlloc("EXIF_STORE", ulCurExifBufSize, &pvExifStoreBufVirt, NULL, NULL);
            CAM_OS_RET_CHK(eCamOsRet);
            m_ulExifHeaderBufAddr[i] = (MMP_ULONG)pvExifStoreBufVirt;
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_FreeExifEncBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_FreeExifEncBuf(void)
{
    MMP_UBYTE   i = 0;
    MMP_ULONG   ulCurExifBufSize = 0;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        _MMPS_DSC_FreeExifEncWorkingBuf(EXIF_NODE_ID_PRIMARY, MMP_TRUE);
    }
    else
    #endif
    {
        _MMPS_DSC_FreeExifEncWorkingBuf(EXIF_NODE_ID_PRIMARY, MMP_FALSE);
    }

    MMPS_DSC_GetBufferSize(MMPS_JPG_EXIF_STORE_BUFFER, 0 ,0, &ulCurExifBufSize);

    for (i = 0; i < DSC_MAX_CAM_NUM; i++) {
        if (m_ulExifHeaderBufAddr[i]) {
            eCamOsRet = CamOsDirectMemRelease((void*)m_ulExifHeaderBufAddr[i], ulCurExifBufSize);
            CAM_OS_RET_CHK(eCamOsRet);
            m_ulExifHeaderBufAddr[i] = 0;
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CalculateJpeOBufAttr
//  Description : Call this function before open JPE component
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_CalculateJpeOBufAttr(MMP_UBYTE ubCompUseType, MMP_BOOL bVRCapture)
{
    MMP_ULONG           ulJpeBufSize = 0;
    MMP_UBYTE           ubJpeBufCount = 1;
    MMP_COMPONENT_BASE  *pJpeComp = &Component_JPE[ubCompUseType];

    /* Calculate compress buffer count and size */
    if (bVRCapture) {
        MMPS_DSC_GetBufferSize(MMPS_JPG_ENC_VR_CAPTURE_COMP_BUFFER,
                               m_usStillJpegWidth[ubCompUseType],
                               m_usStillJpegHeight[ubCompUseType],
                               &ulJpeBufSize);
    }
    else {
        MMPS_DSC_GetBufferSize( MMPS_JPG_ENC_COMP_BUFFER,
                                m_usStillJpegWidth[ubCompUseType],
                                m_usStillJpegHeight[ubCompUseType],
                                &ulJpeBufSize);
    }

    if (m_usDscShotMode[ubCompUseType] == JPE_COMP_SINGLE_SHOT) {
        ulJpeBufSize = ulJpeBufSize * 1;
    }
    else if (m_usDscShotMode[ubCompUseType] == JPE_COMP_CONTINUOUS_SHOT) {
        ulJpeBufSize = m_ulMaxContiShotRingBufSize;
    }
    else if (m_usDscShotMode[ubCompUseType] == JPE_COMP_MJPEG_MODE) {
        ulJpeBufSize = m_ulMaxMJPEGRingBufSize;
    }
    else {
        MMPS_DSC_DBG_ERR(1, "DSC_CalculateJpeOBufAttr => m_usDscShotMode error!\r\n");
        return MMP_ERR_NONE;
    }

    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_BUF_COUNT, (void*)&ubJpeBufCount);
    Component_JPE_SetParam(pJpeComp, JPE_COMP_PARAM_BUF_SIZE, (void*)&ulJpeBufSize);

    #if (DSC_SUPPORT_BASELINE_MP_FILE) // TBD
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        MMPS_DSC_GetBufferSize(MMPS_JPG_ENC_LARGE_THUMB_COMP_BUFFER, m_ulLargeThumbWidth, m_ulLargeThumbHeight, &ulJpeBufSize);

        m_ulLargeThumbJpegCompStart = ulDramCurPos;
        ulDramCurPos += ulBufSize;
        m_ulLargeThumbJpegCompEnd = ulDramCurPos;
    }
    #endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AllocFileNameBuf
//  Description : Allocate memory for DSC Filename
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_AllocFileNameBuf(void)
{
    MMP_ULONG           ulFileNameAddr = 0;
    const MMP_ULONG     ulFileNameSize = DSC_MAX_FILE_NAME_SIZE;
    void*               pvFileNameVirt = NULL;
    CamOsRet_e          eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetFileNameAddr(&ulFileNameAddr);

    if (ulFileNameAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("DSCFileName", ulFileNameSize, &pvFileNameVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPD_DSC_SetFileNameAddr((MMP_ULONG)pvFileNameVirt);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_FreeFileNameBuf
//  Description : Release memory for DSC Filename
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_FreeFileNameBuf(void)
{
    MMP_ULONG           ulFileNameAddr = 0;
    const MMP_ULONG     ulFileNameSize = DSC_MAX_FILE_NAME_SIZE;
    CamOsRet_e          eCamOsRet = CAM_OS_OK;

    MMPD_DSC_GetFileNameAddr(&ulFileNameAddr);

    if (ulFileNameAddr != 0) {
        eCamOsRet = CamOsDirectMemRelease(ulFileNameAddr, ulFileNameSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPD_DSC_SetFileNameAddr(0);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AllocDecIntBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_AllocDecIntBuf(MMP_UBYTE ubCompUseType)
{
    MMP_ULONG   ulIntBufSize = 0;
    void*       pvIntBufVirt = NULL;
    CamOsRet_e  eCamOsRet = CAM_OS_OK;

    if (m_ulJpegDecIntBufAddr[ubCompUseType] == 0) {

        MMPS_DSC_GetBufferSize(MMPS_JPG_DEC_INT_BUFFER, 0, 0, &ulIntBufSize);

        eCamOsRet = CamOsDirectMemAlloc("DecInt", ulIntBufSize, &pvIntBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf((MMP_ULONG)pvIntBufVirt, ulIntBufSize);

        m_ulJpegDecIntBufAddr[ubCompUseType] = (MMP_ULONG)pvIntBufVirt;
        m_ulJpegDecIntBufSize[ubCompUseType] = ulIntBufSize;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_FreeDecIntBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_FreeDecIntBuf(MMP_UBYTE ubCompUseType)
{
    CamOsRet_e eCamOsRet = CAM_OS_OK;

    if (m_ulJpegDecIntBufAddr[ubCompUseType]) {

        eCamOsRet = CamOsDirectMemRelease(m_ulJpegDecIntBufAddr[ubCompUseType], m_ulJpegDecIntBufSize[ubCompUseType]);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf(0, 0);

        m_ulJpegDecIntBufAddr[ubCompUseType] = 0;
        m_ulJpegDecIntBufSize[ubCompUseType] = 0;
    }

    return MMP_ERR_NONE;
}

#if 0
void _____Preview_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CustomedPreviewAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief The function set the display window for DSC
 @param[in] bUserConfig     Use user defined preview configuration.
 @param[in] bMirror         Use DIP scale to mirror preview buffer.
 @param[in] usBufWidth      Preview buffer width.
 @param[in] usBufHeight     Preview buffer height.
 @param[in] usStartX        The X Offset of the display window.
 @param[in] usStartY        The Y Offset of the display window.
 @param[in] usWinWidth      The width of the display window.
 @param[in] usWinHeight     The height of the display window.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_CustomedPreviewAttr(MMP_UBYTE  ubCamSel,
                                     MMP_BOOL   bMirror,
                                     MMP_UBYTE  sFitMode,
                                     MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                     MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                     MMP_USHORT usWinWidth, MMP_USHORT usWinHeight)
{
    m_stDscCustPrevInfo[ubCamSel].bPreviewMirror  = bMirror;
    m_stDscCustPrevInfo[ubCamSel].sFitMode        = sFitMode;
    m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW   = usBufWidth;   // Scale Out Buffer Width
    m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH   = usBufHeight;  // Scale Out Buffer Height
    m_stDscCustPrevInfo[ubCamSel].ulDispStartX    = usStartX;
    m_stDscCustPrevInfo[ubCamSel].ulDispStartY    = usStartY;
    m_stDscCustPrevInfo[ubCamSel].ulDispWidth     = usWinWidth;
    m_stDscCustPrevInfo[ubCamSel].ulDispHeight    = usWinHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetPreviewPipeWH
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetPreviewPipeWH(MMP_UBYTE ubCamSel, MMP_ULONG *pulAlignPrevW, MMP_ULONG *pulAlignPrevH)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    *pulAlignPrevW = m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW;
    *pulAlignPrevH = m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH;

    if (gbLCDRotate) {
        if (DIP_R_COMP_ALIGN_CHECK(m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW)) {
            *pulAlignPrevW = ALIGN_X(m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW, DIP_R_COMP_ALIGN_BASE);
        }
        if (DIP_R_COMP_ALIGN_CHECK(m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH)) {
            *pulAlignPrevH = ALIGN_X(m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH, DIP_R_COMP_ALIGN_BASE);
        }
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CheckPrimaryPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_CheckPrimaryPipe(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((ubCamSel == PRM_SENSOR) &&
        (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR))) {
    }
    else {
        eRetErr = MMP_HIF_ERR_PARAMETER;
        return eRetErr;
    }

    if (m_stDscCustCaptInfo[ubCamSel].ulEncBufW < m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW) {
        MMPS_DSC_DBG_ERR(1, "DSC Cam%d EncW [%d] < PrevW [%d]\r\n",
                        ubCamSel,
                        m_stDscCustCaptInfo[ubCamSel].ulEncBufW,
                        m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW);
        eRetErr = MMP_HIF_ERR_PARAMETER;
        return eRetErr;
    }

    if (m_stDscCustCaptInfo[ubCamSel].ulEncBufH < m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH) {
        MMPS_DSC_DBG_ERR(1, "DSC Cam%d EncH [%d] < PrevH [%d]\r\n",
                        ubCamSel,
                        m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                        m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH);
        eRetErr = MMP_HIF_ERR_PARAMETER;
        return eRetErr;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustPrmCapturePipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustPrmCapturePipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Scale In Error!", gubMmpDbgBk); return eRetErr; }

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL0,
                                        SCL0_COMP_PRM_CAM,
                                        1, 1, ulScaleInW, ulScaleInH,
                                        1, 1, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        SCL_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "SCL0 Comp Error!", gubMmpDbgBk); return eRetErr; }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustPrmCapturePipe_2IN2O
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustPrmCapturePipe_2IN2O(MMP_UBYTE ubCamSel)
{
    MMP_UBYTE           ubDipBufCnt = DIP_COMP_PREVW_BUF_COUNT;
    MMP_ULONG           ulAlignPrevW = 0, ulAlignPrevH = 0;
    //MMP_ULONG           ulDispWidth = 0, ulDispHeight = 0;
    //MMP_ULONG           ulDispStartX = 0, ulDispStartY = 0;
    //MMP_ULONG           ulAlignDispW = 0, ulAlignDispH = 0;
    //MMP_UBYTE           ubDipSUseIdx, ubDipRUseIdx;
    //MMP_UBYTE           ubCamSel = PRM_SENSOR;
    MMP_UBYTE           ubDipMirrorType = DIP_COMP_MIRROR_DIS;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    DIP_COMP_COLOR_FMT  ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
    MMPF_SENSOR_YUV_ORDER   order = MMPF_SENSOR_YUV_ORDER_YC;

    MMPS_DSC_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
    //MMPS_DSC_GetDisplayRes(ubCamSel, &ulDispWidth, &ulDispHeight);
    //MMPS_DSC_GetDisplayPosition(ubCamSel, &ulDispStartX, &ulDispStartY);

    //get YUV order from sensor, and select input color format
    eRetErr = MMPF_Sensor_GetSensorYuvOrder(SCD_SENSOR, &order);
    if (eRetErr == MMP_ERR_NONE){
        //mapping
        switch(order)
        {
            case MMPF_SENSOR_YUV_ORDER_YC:
                ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
            break;
            case MMPF_SENSOR_YUV_ORDER_CY:
            default:
                ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
            break;
        }
    }

    //ulAlignDispW = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
    //ulAlignDispH = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);

    //Fcam Pram capture
    MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_DSC_FCAM_CAPT_2IN2,
                                    0, 0, 1280, 720,
                                    0, 0, 1280, 720,
                                    0, 0, m_stDscCustCaptInfo[PRM_SENSOR].ulEncBufW, m_stDscCustCaptInfo[PRM_SENSOR].ulEncBufH,
                                    ubDIPSCLInColor,
                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                    ubDipMirrorType,
                                    0,
                                    ubDipBufCnt);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustPrmCaptureThumbPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustPrmCaptureThumbPipe(MMP_UBYTE ubCamSel, MMP_ULONG ulThumbW, MMP_ULONG ulThumbH)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_UBYTE           ubDipBufCount = 1;
    DIP_COMP_COLOR_FMT  eDipColor = DIP_COMP_COLOR_FMT_YUV420_UV;

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_PRE_SCL,
                                        0, 0, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        0, 0, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_MID_SCL,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_POST_SCL,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, ALIGN16(ulThumbW), ALIGN16(ulThumbH),
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustPrmPreviewPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustPrmPreviewPipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulAlignPrevW = 0, ulAlignPrevH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_DSC_GetPreviewPipeWH(ubCamSel, &ulAlignPrevW, &ulAlignPrevH);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Preview W,H error!", gubMmpDbgBk); return eRetErr; }

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL1,
                                        SCL1_COMP_PRM_CAM,
                                        1, 1, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        1, 1, ulAlignPrevW, ulAlignPrevH,
                                        SCL_COMP_PREVW_BUF_COUNT);

    if (MMP_GetScdCamType() == SCD_CAM_BAYER_SENSOR) {
        eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL1,
                                            SCL1_COMP_SCD_CAM,
                                            1, 1, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                            1, 1, ulAlignPrevW, ulAlignPrevH,
                                            SCL_COMP_PREVW_BUF_COUNT);
    }

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_DSC_DBG_ERR(1, "Set SCL1 Comp Error!\r\n");
        return eRetErr;
    }

    MMPS_Display_SetPrmPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_DSC, MMPS_DISPLAY_PREVIEW_FULL_SCREEN);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustScdAnaDecCapturePipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustScdAnaDecCapturePipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG               ulSensorOutW = 0, ulSensorOutH = 0;
    MMP_ULONG               ulScaleInW = 0, ulScaleInH = 0;
    MMP_ULONG               ulScaleInAlignedX = 0, ulScaleInAlignedY = 0;
    MMP_ULONG               ulScaleInAlignedW = 0, ulScaleInAlignedH = 0;
    MMP_UBYTE               ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSrc = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_UBYTE               ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV; //if YUV sensor, the order may be diff
    MMPF_SENSOR_YUV_ORDER   order = MMPF_SENSOR_YUV_ORDER_CY;

    MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrc);

    eRetErr = MMPS_Sensor_GetCurSensorOutputRes(ubCamSel, &ulSensorOutW, &ulSensorOutH);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Preview W,H error!", gubMmpDbgBk); return eRetErr; }

    eRetErr = MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Preview W,H error!", gubMmpDbgBk); return eRetErr; }

    if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_PAL) {
        ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
        ulScaleInAlignedX = 0;
        ulScaleInAlignedY = 2;
        ulScaleInAlignedW = 672;
        ulScaleInAlignedH = (ulScaleInH == 288) ? (ulScaleInH - 32) : ulScaleInH;
        ulScaleInAlignedH -= 2;
    }
    else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_NTSC) {
        ubSigType = RAWS_COMP_SIG_TYPE_INTERLACE;
        ulScaleInAlignedX = 0;
        ulScaleInAlignedY = 2;
        ulScaleInAlignedW = 672;
        ulScaleInAlignedH = 240;
        ulScaleInAlignedH -= 2;
    }
    else if (eAnaDecSrc == MMP_SNR_ANADEC_SRC_FHD ||
             eAnaDecSrc == MMP_SNR_ANADEC_SRC_HD) {
        ubSigType = RAWS_COMP_SIG_TYPE_PROGRESSIVE;
        ulScaleInAlignedW = ulScaleInW;
        ulScaleInAlignedH = ulScaleInH;
    }

    eRetErr = MMPD_RAWPROC_SetRawSCompAttr( RAWS_COMP_IDX,
                                            ubSigType,
                                            ulSensorOutW,
                                            ulSensorOutH,
                                            RAWS_COMP_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "RAWS Comp Error!", gubMmpDbgBk); return eRetErr; }

    //get YUV order from sensor, and select input color format
    eRetErr = MMPF_Sensor_GetSensorYuvOrder(ubCamSel, &order);
    if (eRetErr != MMP_ERR_NONE){
        return eRetErr;
    }
    //mapping
    switch(order)
    {
        case MMPF_SENSOR_YUV_ORDER_YC:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_UYVY;
        break;
        case MMPF_SENSOR_YUV_ORDER_CY:
        default:
            ubDIPSCLInColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
        break;
    }

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_RCAM_CAPTURE,
                                        0, 0, ulScaleInW, ulScaleInH,
                                        ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                        0, 0, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        ubDIPSCLInColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        DIP_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "DIP Comp Error!", gubMmpDbgBk); return eRetErr; }

    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        MMP_ULONG ulEncodeW = m_stDscCustCaptInfo[ubCamSel].ulEncW;
        MMP_ULONG ulEncodeH = m_stDscCustCaptInfo[ubCamSel].ulEncH;

        UartSendTrace(FG_YELLOW("[RearCam capture] %d x %d\r\n"), ulEncodeW, ulEncodeH);

        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_RECD_2IN1_INA, DIP_S_COMP_VR_RCAM_RECD, // Left image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    0, 0, ulEncodeW / 2, ulEncodeH, ulEncodeW,
                                    ubDIPSCLInColor,
                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                    DIP_COMP_MIRROR_DIS,
                                    MFE_SHARE_BUF_LINE_BIAS,
                                    0 /*DIP_COMP_RECORD_BUF_COUNT*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_RECD


        MMPD_Fctl_SetDIPCompAttr_LineOffset(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_VR_RCAM_RECD_2IN1_INB, DIP_S_COMP_VR_RCAM_RECD, // Right image
                                    0, 0, ulScaleInW, ulScaleInH, ulScaleInW,
                                    ulScaleInAlignedX, ulScaleInAlignedY, ulScaleInAlignedW, ulScaleInAlignedH,
                                    ulEncodeW / 2, 0, ulEncodeW / 2, ulEncodeH, ulEncodeW,
                                    ubDIPSCLInColor,
                                    DIP_COMP_COLOR_FMT_YUV420_UV,
                                    DIP_COMP_MIRROR_DIS,
                                    MFE_SHARE_BUF_LINE_BIAS,
                                    0 /*DIP_COMP_RECORD_BUF_COUNT*/); // Buffers will be allocated in DIP_S_COMP_VR_RCAM_RECD
    }

    if(MMP_GetRawStoreNum() == 2 && RAWS_COMP_IDX != RAWS_COMP_IDX2) {
        eRetErr = MMPD_RAWPROC_SetRawSCompAttr( RAWS_COMP_IDX2,
                                                ubSigType,
                                                ulSensorOutW,
                                                ulSensorOutH,
                                                RAWS_COMP_BUF_COUNT);
        if (eRetErr != MMP_ERR_NONE) {
            MMP_PRINT_RET_ERROR(0, eRetErr, "RAWS Comp Error!", gubMmpDbgBk);
            return eRetErr;
        }

        //TODO:other comp flow
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustScdBayerCapturePipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustScdBayerCapturePipe(MMP_UBYTE ubCamSel)
{
    MMP_ULONG   ulScaleInW = 0, ulScaleInH = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_Sensor_GetCurPrevScalInputRes(ubCamSel, &ulScaleInW, &ulScaleInH);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Scale In Error!", gubMmpDbgBk); return eRetErr; }

    eRetErr = MMPD_Fctl_SetSCLCompAttr( SCL_COMP_TYPE_ID_SCL0,
                                        SCL0_COMP_SCD_CAM,
                                        1, 1, ulScaleInW, ulScaleInH,
                                        1, 1, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        SCL_COMP_RECORD_BUF_COUNT);
    if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "SCL0 Comp Error!", gubMmpDbgBk); return eRetErr; }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustScdCapturePipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_AdjustScdCapturePipe(MMP_UBYTE ubCamSel)
{
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        return MMPS_DSC_AdjustScdBayerCapturePipe(ubCamSel);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) ||
             CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        return MMPS_DSC_AdjustScdAnaDecCapturePipe(ubCamSel);
    }
    else {
        return MMP_ERR_NONE;
    }
}

static MMP_ERR MMPS_DSC_AdjustScdCaptureThumbPipe_2INO(MMP_UBYTE ubCamSel, MMP_ULONG ulThumbW, MMP_ULONG ulThumbH)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_UBYTE           ubDipBufCount = 1;
    DIP_COMP_COLOR_FMT  eDipColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    DIP_COMP_COLOR_FMT  einColor = DIP_COMP_COLOR_FMT_YUV420_UV;
    MMP_UBYTE           ubDipUseIdx = DIP_S_COMP_DSC_FCAM_THUMB_2IN2;
    MMP_UBYTE           CamSel = 0;

    if(ubCamSel == JPE_COMP_PRM_THUMB){
        einColor        = DIP_COMP_COLOR_FMT_YUV420_UV;//DIP_COMP_COLOR_FMT_YUV422_UYVY;
        ubDipUseIdx     = DIP_S_COMP_DSC_FCAM_THUMB_2IN2;
        CamSel          = PRM_SENSOR;
    }
    else{
        einColor        = DIP_COMP_COLOR_FMT_YUV420_UV;
        ubDipUseIdx     = DIP_S_COMP_DSC_THUMB_PRE_SCL;
        CamSel          = SCD_SENSOR;
    }

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        ubDipUseIdx,
                                        0, 0, m_stDscCustCaptInfo[CamSel].ulEncBufW, m_stDscCustCaptInfo[CamSel].ulEncBufH,
                                        0, 0, m_stDscCustCaptInfo[CamSel].ulEncBufW, m_stDscCustCaptInfo[CamSel].ulEncBufH,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        einColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_MID_SCL,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_POST_SCL,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, ALIGN16(ulThumbW), ALIGN16(ulThumbH),
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    return eRetErr;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustScdCaptureThumbPipe
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_AdjustScdCaptureThumbPipe(MMP_UBYTE ubCamSel, MMP_ULONG ulThumbW, MMP_ULONG ulThumbH)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MMP_UBYTE           ubDipBufCount = 1;
    DIP_COMP_COLOR_FMT  eDipColor = DIP_COMP_COLOR_FMT_YUV420_UV;

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_PRE_SCL,
                                        0, 0, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        0, 0, m_stDscCustCaptInfo[ubCamSel].ulEncBufW, m_stDscCustCaptInfo[ubCamSel].ulEncBufH,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_MID_SCL,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    eRetErr = MMPD_Fctl_SetDIPCompAttr( DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_DSC_THUMB_POST_SCL,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, ALIGN16(ulThumbW), ALIGN16(ulThumbH),
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustScdPreviewPipe
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_AdjustScdPreviewPipe(MMP_UBYTE ubCamSel)
{
    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        return MMPS_Display_SetScdBayerPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_DSC,
                                                       MMPS_DISPLAY_PREVIEW_PIP_WIN);
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) ||
             CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        return MMPS_Display_SetScdAnaDecPreviewPipeAttr(MMPS_PREVIEW_UI_MODE_DSC,
                                                        MMPS_DISPLAY_PREVIEW_PIP_WIN);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_AdjustImagePipe
//  Description : Allocate preview buffer and config pipe.
//------------------------------------------------------------------------------
/** @brief Config the preview mode parameters needed
@return It reports the status of the configuration.
*/
static MMP_ERR MMPS_DSC_AdjustImagePipe(MMP_UBYTE ubCamSel)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if(MMP_GetANACamType() == ANA_CAM_2I2O){
        eRetErr = MMPS_DSC_AdjustPrmCapturePipe_2IN2O(ubCamSel);
        eRetErr |= MMPS_Display_SetPrmPreviewPipeAttr_Raw2I2O(MMPS_PREVIEW_UI_MODE_DSC,MMPS_DISPLAY_PREVIEW_FULL_SCREEN);
    }
    else if (MMPS_DSC_CheckPrimaryPipe(ubCamSel) == MMP_ERR_NONE) {
        eRetErr = MMPS_DSC_AdjustPrmCapturePipe(ubCamSel);
        eRetErr |= MMPS_DSC_AdjustPrmPreviewPipe(ubCamSel);
        if (eRetErr != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, eRetErr, "Prm Pipe Error!", gubMmpDbgBk); return eRetErr; }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetPreviewMode
//  Description : Configure DSC preview mode.
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetPreviewMode(MMP_USHORT usMode)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    m_usDscPreviewMode = usMode;

    if (usMode == (MMP_USHORT)(-1)) {
        if(ANA_CAM_2I2O == MMP_GetANACamType()){
            if (gbLCDRotate) {
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_SRC);         //DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
                                                                        //DIP_S0->DIP_R0/DIP_S4
                CloseScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_FULL);        //DIP_S0<-DIP_R0->DISP
                ClosePortScript(PORT_SCRIPT_VR_PREV_PRM_RAW_FULL);       //DIP_S0 open outport1
                //RAW_CH1 Open outport3=DIP_S0
            }
            else {
                MMPS_DSC_DBG_ERR(1, "TODO:%s,line#%d,ANA_CAM_2I2O\r\n",__FUNCTION__, __LINE__);
            }
        }
        else{
            if (gbLCDRotate) {
                ClosePortScript(PORT_SCRIPT_DSC_PREV_PRM_FULL);
                ClosePortScript(PORT_SCRIPT_DSC_PREV_PRM_PIP);
                CloseScript(COMPO_SCRIPT_DSC_R_PREV_PRM_FULL);
                CloseScript(COMPO_SCRIPT_DSC_R_PREV_PRM_PIP);
                CloseScript(COMPO_SCRIPT_DSC_R_PREV_PRM_SRC);
            }
            else {
                ClosePortScript(PORT_SCRIPT_DSC_PREV_PRM_FULL);
                ClosePortScript(PORT_SCRIPT_DSC_PREV_PRM_PIP);

                CloseScript(COMPO_SCRIPT_DSC_N_PREV_PRM_FULL);
                CloseScript(COMPO_SCRIPT_DSC_N_PREV_PRM_PIP);
                CloseScript(COMPO_SCRIPT_DSC_N_PREV_PRM_SRC);
            }
        }
    }
    else {
        /* Set Component Parameters */
        if (MMP_IsPrmCamExist()) {
            eRetErr = MMPS_DSC_AdjustImagePipe(PRM_SENSOR);
        }

        if(ANA_CAM_2I2O == MMP_GetANACamType()){
            if (gbLCDRotate) {
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_SRC);         //DIP_S14->MFE0/JPE3/DIP_S5/DIP_S7/DIP_S9
                                                                        //DIP_S0->DIP_R0/DIP_S4
                OpenScript(COMPO_SCRIPT_VR_R_PREV_PRM_RAW_FULL);        //DIP_S0<-DIP_R0->DISP
                OpenPortScript(PORT_SCRIPT_VR_PREV_PRM_RAW_FULL);       //DIP_S0 open outport1
                //RAW_CH1 Open outport3=DIP_S0
            }
            else {
                MMPS_DSC_DBG_ERR(1, "TODO:%s,line#%d,ANA_CAM_2I2O\r\n",__FUNCTION__, __LINE__);
            }
        }
        else{
            if (gbLCDRotate) {
                OpenScript(COMPO_SCRIPT_DSC_R_PREV_PRM_SRC);
                OpenScript(COMPO_SCRIPT_DSC_R_PREV_PRM_FULL);

                OpenPortScript(PORT_SCRIPT_DSC_PREV_PRM_FULL);
            }
            else {
                OpenScript(COMPO_SCRIPT_DSC_N_PREV_PRM_SRC);
                OpenScript(COMPO_SCRIPT_DSC_N_PREV_PRM_FULL);

                OpenPortScript(PORT_SCRIPT_DSC_PREV_PRM_FULL);
            }
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetPreviewPath
//  Description :
//------------------------------------------------------------------------------
/** @brief
@param[in] ePath        which kind of preview mode you use
@param[in] eRawColorFmt which kind of raw bit mode, the preview mode use.
@return It reports the status of the configuration.
*/
MMP_ERR MMPS_DSC_SetPreviewPath(MMP_UBYTE ubCamSel, MMP_DSC_PREVIEW_PATH ePath)
{
    if (MMP_IsDscPtzEnable()) {
        m_eDscPreviewPath[ubCamSel] = MMP_DSC_RAW_PREVIEW;
    }
    else {
        m_eDscPreviewPath[ubCamSel] = ePath;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_EnablePreviewDisplay
//  Description :
//------------------------------------------------------------------------------
/** @brief Enable and disable the DSC preview

The function enables or disables DSC preview display .

@param[in] bEnable          enable or disable
@param[in] bCheckFrameEnd   When "bEnable" is enable, the setting whill check frame end or not.

@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_EnablePreviewDisplay(MMP_UBYTE ubCamSel, MMP_BOOL bEnable, MMP_BOOL bCheckFrameEnd)
{
    MMP_BOOL bComplete = MMP_FALSE;

    if (!(bEnable ^ m_bDscPreviewActive[ubCamSel])) {
        return MMP_ERR_NONE;
    }

    if (bEnable) {

        if (MMPD_Fctl_EnablePreview(ubCamSel, MMP_TRUE, bCheckFrameEnd)) {
            MMPS_DSC_DBG_ERR(1, "DSC Enable Preview : Fail\r\n");
            return MMP_DISPLAY_ERR_FRAME_END;
        }
        m_bDscPreviewActive[ubCamSel] = MMP_TRUE;
    }
    else {

        MMPD_PTZ_SetDigitalZoom(1, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

        while (!bComplete) {
            MMPD_PTZ_CheckZoomComplete(1, &bComplete);
        }

        MMPD_Fctl_EnablePreview(ubCamSel, MMP_FALSE, MMP_TRUE);

        m_bDscPreviewActive[ubCamSel] = MMP_FALSE;
        m_usDSCStaticZoomIndex = 0;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetPreviewPipeStatus
//  Description :
//------------------------------------------------------------------------------
/** @brief Enable and disable the DSC preview

The function enables or disables DSC preview display .

@param[in] bEnable enable or disable
@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_GetPreviewPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable)
{
    *pbEnable = m_bDscPreviewActive[ubCamSel];

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetPreviewMirror
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetPreviewMirror(MMP_UBYTE ubCamSel, MMP_BOOL *pbMirror)
{
    if (pbMirror) {
        *pbMirror = m_stDscCustPrevInfo[ubCamSel].bPreviewMirror;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetPreviewRes
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetPreviewRes(MMP_UBYTE ubCamSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    if (pulWidth)
        *pulWidth = m_stDscCustPrevInfo[ubCamSel].ulPreviewBufW;
    if (pulHeight)
        *pulHeight = m_stDscCustPrevInfo[ubCamSel].ulPreviewBufH;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetDisplayRes
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetDisplayRes(MMP_UBYTE ubCamSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    if (pulWidth)
        *pulWidth = m_stDscCustPrevInfo[ubCamSel].ulDispWidth;
    if (pulHeight)
        *pulHeight = m_stDscCustPrevInfo[ubCamSel].ulDispHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetDisplayPosition
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetDisplayPosition(MMP_UBYTE ubCamSel, MMP_ULONG *pulPosStartX, MMP_ULONG *pulPosStartY)
{
    if (pulPosStartX)
        *pulPosStartX = m_stDscCustPrevInfo[ubCamSel].ulDispStartX;
    if (pulPosStartY)
        *pulPosStartY = m_stDscCustPrevInfo[ubCamSel].ulDispStartY;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_RestorePreview
//  Description :
//------------------------------------------------------------------------------
/** @brief The function use in restore preview

The function restore preview for multi-shot capture

@param[in] usWindowsTime     The time of review time
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_DSC_RestorePreview(MMP_UBYTE ubCamSel, MMP_USHORT usWindowsTime)
{
    return MMP_ERR_NONE;
}

#if 0
void _____Preview_PTZ_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetZoomConfig
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set zoom config

The function set zoom config, total step and max zoom ratio

@param[in] ubSteps      zoom total step
@param[in] ubMaxRatio   max zoom ratio
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_SetZoomConfig(MMP_USHORT usMaxSteps, MMP_USHORT usMaxRatio)
{
    m_DscPreviewZoomInfo.usMaxZoomSteps     = usMaxSteps;
    m_DscPreviewZoomInfo.usMaxZoomRatio     = usMaxRatio;

    m_bAhcConfigDscZoom                     = MMP_TRUE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_InitDigitalZoomParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_InitDigitalZoomParam(void)
{
    m_DscPreviewZoomInfo.scalerpath     = 1;
    m_DscPreviewZoomInfo.usCurZoomStep  = 0;
    m_DscPreviewZoomInfo.usMaxZoomRatio = gsDscPtzCfg.usMaxZoomRatio;
    m_DscPreviewZoomInfo.usMaxZoomSteps = gsDscPtzCfg.usMaxZoomSteps;
    m_DscPreviewZoomInfo.sMaxPanSteps   = gsDscPtzCfg.sMaxPanSteps;
    m_DscPreviewZoomInfo.sMinPanSteps   = gsDscPtzCfg.sMinPanSteps;
    m_DscPreviewZoomInfo.sMaxTiltSteps  = gsDscPtzCfg.sMaxTiltSteps;
    m_DscPreviewZoomInfo.sMinTiltSteps  = gsDscPtzCfg.sMinTiltSteps;

    MMPD_PTZ_InitPtzRange(m_DscPreviewZoomInfo.scalerpath,
                          m_DscPreviewZoomInfo.usMaxZoomRatio,
                          m_DscPreviewZoomInfo.usMaxZoomSteps,
                          m_DscPreviewZoomInfo.sMaxPanSteps,
                          m_DscPreviewZoomInfo.sMinPanSteps,
                          m_DscPreviewZoomInfo.sMaxTiltSteps,
                          m_DscPreviewZoomInfo.sMinTiltSteps);

    MMPD_PTZ_SetDigitalZoom(m_DscPreviewZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_RestoreDigitalZoomRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_RestoreDigitalZoomRange(void)
{
    if (m_usDSCStaticZoomIndex) {

        m_DscPreviewZoomInfo.usCurZoomStep = m_usDSCStaticZoomIndex;

        MMPD_PTZ_SetTargetPtzStep(m_DscPreviewZoomInfo.scalerpath,
                                  MMP_PTZ_ZOOM_INC_IN,
                                  m_DscPreviewZoomInfo.usCurZoomStep, 0, 0);

        MMPD_PTZ_SetDigitalZoomOP(PRM_SENSOR,
                                  m_DscPreviewZoomInfo.scalerpath,
                                  MMP_PTZ_ZOOMIN,
                                  MMP_TRUE);

        // Reset zoom index
        m_usDSCStaticZoomIndex = 0;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetCurZoomStep
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetCurZoomStep(MMP_USHORT *usCurZoomStep)
{
    MMP_USHORT  usCurStep = 0;
    MMP_ERR     status = MMP_ERR_NONE;

    status = MMPD_PTZ_GetCurPtzStep(m_DscPreviewZoomInfo.scalerpath,
                                    NULL, &usCurStep, NULL, NULL);

    *usCurZoomStep = usCurStep;

    if (m_bDscPreviewActive[0]) {
        m_DscPreviewZoomInfo.usCurZoomStep = usCurStep;
    }

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetCurZoomStatus
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE MMPS_DSC_GetCurZoomStatus(void)
{
    return MMPD_PTZ_GetCurPtzStatus();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetPreviewZoom
//  Description :
//------------------------------------------------------------------------------
/** @brief Setup the zoom parameter and start the zoom operation

The function configures the digital zoom parameter and starts the zoom operation
@param[in] zoomdir  the zoom in , zoom out or zoom stop
@param[in] usCurZoomStep
@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_SetPreviewZoom(MMP_PTZ_ZOOM_DIR sZoomDir, MMP_USHORT usCurZoomStep)
{
    MMP_BOOL            bComplete = MMP_FALSE;
    MMP_PTZ_ZOOM_INC    sZoomInc;

    if (!m_bDscPreviewActive[0]) {
        m_usDSCStaticZoomIndex = usCurZoomStep;
        return MMP_ERR_NONE;
    }

    /* Decide the zoom step increment */
    if (sZoomDir == MMP_PTZ_ZOOMIN) {
        sZoomInc = MMP_PTZ_ZOOM_INC_IN;
    }
    else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
        sZoomInc = MMP_PTZ_ZOOM_INC_OUT;
    }

    MMPD_PTZ_CheckZoomComplete(m_DscPreviewZoomInfo.scalerpath, &bComplete);

    if (!bComplete) {

        MMPD_PTZ_SetDigitalZoom(m_DscPreviewZoomInfo.scalerpath, MMP_PTZ_ZOOMSTOP, MMP_TRUE);

        do {
            MMPD_PTZ_CheckZoomComplete(m_DscPreviewZoomInfo.scalerpath, &bComplete);
        } while(!bComplete);
    }

    if (sZoomDir == MMP_PTZ_ZOOMIN) {
        MMPD_PTZ_SetTargetPtzStep(m_DscPreviewZoomInfo.scalerpath,
                                  sZoomInc,
                                  m_DscPreviewZoomInfo.usMaxZoomSteps, 0, 0);
    }
    else if (sZoomDir == MMP_PTZ_ZOOMOUT) {
        MMPD_PTZ_SetTargetPtzStep(m_DscPreviewZoomInfo.scalerpath,
                                  sZoomInc,
                                  0, 0, 0);
    }

    MMPD_PTZ_SetDigitalZoom(m_DscPreviewZoomInfo.scalerpath, sZoomDir, MMP_TRUE);

    return MMP_ERR_NONE;
}

#if 0
void _____Video2MJPEG_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetVideo2MJpegResol
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set Motion JPEG resolution.
@param[in] usW The width of image
@param[in] usH The height of image
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_DSC_SetVideo2MJpegResol(MMP_USHORT usW, MMP_USHORT usH)
{
#if (VIDEO_DEC_TO_MJPEG)
    m_usVid2MJpegWidth  = usW;
    m_usVid2MJpegHeight = usH;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetVideo2MJpegEnable
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set video decode to motion JPEG enable.
@param[in] bEnable enable Motion Jpeg encode.
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_DSC_SetVideo2MJpegEnable(MMP_BOOL bEnable)
{
#if (VIDEO_DEC_TO_MJPEG)
    m_bEncodeMJpegFromVideo = bEnable;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetTranscodeRate
//  Description :
//------------------------------------------------------------------------------
/** @brief Config transcoding Parameters
 *
 * @post This should be called before MMPS_VIDPLAY_Open
 * @param[in] fpsx10 frame per second x 10. So that it could be something like 7.5FPS
 * @param[in] ulBitrate The bit rate of the output file.
 * @return MMP_ERR_NONE
 */
MMP_ERR MMPS_DSC_SetTranscodeRate(MMP_ULONG ulInFpsx10, MMP_ULONG ulOutFpsx10, MMP_ULONG ulBitrate)
{
#if (VIDEO_DEC_TO_MJPEG)
    m_transcode.ulInFpsx10  = ulInFpsx10;
    m_transcode.ulOutFpsx10 = ulOutFpsx10;
    m_transcode.ulBitrate   = ulBitrate;
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetMjpegEncDoneMode
//  Description : Set the transmission type of MJPEG bitstream.
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetMjpegEncDoneMode(MMP_STREAM_UI_MODE_ID eStrmUiMode)
{
    if (eStrmUiMode >= MMP_STREAM_UI_MODE_ID_NUM) {
        return MMP_DSC_ERR_PARAMETER;
    }

    if (eStrmUiMode == MMP_STREAM_UI_MODE_WIFI_VR ||
        eStrmUiMode == MMP_STREAM_UI_MODE_WIFI_DSC) {
        m_eMjpegEncDoneMode = MMP_JPEG_ENC_DONE_WIFI_MJPG;
    }
    else if (eStrmUiMode == MMP_STREAM_UI_MODE_UVC_VR ||
             eStrmUiMode == MMP_STREAM_UI_MODE_UVC_DSC) {
        m_eMjpegEncDoneMode = MMP_JPEG_ENC_DONE_UVC_MJPG;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetMjpegEncDoneMode
//  Description : Get the transmission type of MJPEG bitstream.
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetMjpegEncDoneMode(MMP_UBYTE *pubEncDoneMode)
{
    if (m_eMjpegEncDoneMode != MMP_JPEG_ENC_DONE_UVC_MJPG &&
        m_eMjpegEncDoneMode != MMP_JPEG_ENC_DONE_WIFI_MJPG) {
        return MMP_DSC_ERR_PARAMETER;
    }

    if (pubEncDoneMode)
        *pubEncDoneMode = m_eMjpegEncDoneMode;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ConfigVideo2Mjpeg
//  Description : Config the WiFi transcoding Parameters (TBD)
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_ConfigVideo2Mjpeg(MMP_SHORT usInputW, MMP_USHORT usInputH)
{
#if (VIDEO_DEC_TO_MJPEG)
    MMP_ERR error = MMP_ERR_NONE;

    if (m_transcode.ulOutFpsx10 == 0) {
        return MMP_DSC_ERR_PARAMETER;
    }

    //ulTargetSize = ((m_transcode.ulBitrate * 10 / m_transcode.ulOutFpsx10) >> (3 + 10)) + 1;

    //error = MMPS_MJPEG_OpenStream(MMP_MJPEG_STREAM_FCAM_VIDEO, MMP_STREAM_UI_MODE_WIFI_VR, &handle);

    //MMPS_DSC_SetCaptureJpegQuality(MMP_JPGENC_RC_ID_PRM_MJPEG_STREAM, MMP_TRUE, MMP_FALSE,
    //                               ulTargetSize, ulTargetSize, 1, MMP_JPGENC_RC_QUALITY_SEL_HIGH);

    //MMPS_DSC_GetVid2MJpegCompBuf(&ulDramAddr, &ulBufSize);

    //MMPD_Streaming_SetCompBuf(VIDEO1_RING_STREAM, MMP_STREAM_UI_MODE_WIFI_VR, ulDramAddr, ulBufSize, MMP_STREAM_JPEG);

    //MMPD_DSC_InitGra2MJPEGAttr(fctllink, &bufAttr, &rect, &stFitRange, &stGrabCtl);
    //MMPD_Streaming_Enable(VIDEO1_RING_STREAM, MMP_TRUE, MMP_FALSE);

    return error;
#else
    return MMP_ERR_NONE;
#endif
}

#if 0
void _____Capture_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CustomedEncResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set VideoR encode resolution
 @param[in] ubEncIdx    encode instance ID
 @param[in] sFitMode    scaler fit mode
 @param[in] usWidth     encode width
 @param[in] usHeight    encode height
 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_DSC_CustomedEncResol(MMP_UBYTE ubCamSel, MMP_UBYTE sFitMode, MMP_USHORT usEncW, MMP_USHORT usEncH)
{
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    JPE_COMP_COLOR_FMT  eColorFmt = JPE_COMP_FMT_NV12;
    MMP_ULONG           ulWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;

    eRetErr = Component_JPE_GetParam(&Component_JPE[JPE_COMP_PRM_PRIMARY + ubCamSel], JPE_COMP_PARAM_FMT, (void*)&eColorFmt);

    if (eColorFmt == JPE_COMP_FMT_NV12 ||
        eColorFmt == JPE_COMP_FMT_NV21) {
        ulWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
        ulHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;
    }
    else {
        ulWAlignBase = JPE_COMP_W_ALIGN_BASE_YUV422;
        ulHAlignBase = JPE_COMP_H_ALIGN_BASE_YUV422;
    }

    m_stDscCustCaptInfo[ubCamSel].sFitMode  = sFitMode;
    m_stDscCustCaptInfo[ubCamSel].ulEncW    = usEncW;
    m_stDscCustCaptInfo[ubCamSel].ulEncH    = usEncH;
    m_stDscCustCaptInfo[ubCamSel].ulEncBufW = ALIGN_X(usEncW, ulWAlignBase);
    m_stDscCustCaptInfo[ubCamSel].ulEncBufH = ALIGN_X(usEncH, ulHAlignBase);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CheckContiShotWriteFileDone
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_DSC_CheckContiShotWriteFileDone(MMP_UBYTE ubCamSel)
{
    return MMPF_ContiShot_IsWriteFileDone(ubCamSel);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetContiShotInterval
//  Description : TBD
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetContiShotInterval(MMP_ULONG ulInterval)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetJpeUIMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetJpeUIMode(MMP_UBYTE ubCompType, MMP_UBYTE ubMode)
{
    m_ubJpeUIMode[ubCompType] = ubMode;

    Component_JPE_SetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_UI_MODE, (void*)&m_ubJpeUIMode[ubCompType]);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetShotMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetShotMode(MMP_UBYTE ubCompType, MMP_UBYTE ubMode)
{
    m_usDscShotMode[ubCompType] = (MMP_USHORT)ubMode;

    Component_JPE_SetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_SHOT_MODE, (void*)&m_usDscShotMode[ubCompType]);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetMaxShotNum
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetMaxShotNum(MMP_UBYTE ubCompType, MMP_ULONG ulMaxShotNum)
{
    m_ulMaxShotCnt[ubCompType] = ulMaxShotNum;

    Component_JPE_SetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_SHOT_NUM, (void*)&m_ulMaxShotCnt[ubCompType]);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetJpegEncFmt
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetJpegEncFmt(MMP_UBYTE ubCompType, MMP_UBYTE ubRawFmt)
{
    m_ubJpegEncRawFmt[ubCompType] = ubRawFmt;

    Component_JPE_SetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_FMT, (void*)&m_ubJpegEncRawFmt[ubCompType]);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetJpegEncResol
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetJpegEncResol(MMP_UBYTE ubCompType, MMP_USHORT usEncW, MMP_USHORT usEncH)
{
    MMP_ERR             eRetErr         = MMP_ERR_NONE;
    JPE_COMP_RESOL      stJpeResol;
    JPE_COMP_COLOR_FMT  eColorFmt       = JPE_COMP_FMT_NV12;
    MMP_ULONG           ulEncWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulEncHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;
    MMP_ULONG           ulBufWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
    MMP_ULONG           ulBufHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;

    eRetErr = Component_JPE_GetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_FMT, (void*)&eColorFmt);

    if (eColorFmt == JPE_COMP_FMT_NV12 ||
        eColorFmt == JPE_COMP_FMT_NV21) {

        if (m_ubJpeUIMode[ubCompType] == JPE_COMP_UI_MODE_VR &&
            m_usDscShotMode[ubCompType] != JPE_COMP_MJPEG_MODE) {
            // JPEG YUV420 Alignment (16,16) YUV422 Alignment (16,8)
            // But MFE YUV420 Need Align(32, 16)
            ulBufWAlignBase = MFE_COMP_W_ALIGN_BASE_NV12;
            ulBufHAlignBase = MFE_COMP_H_ALIGN_BASE_NV12;
        }
        else {
            ulBufWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
            ulBufHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;
        }

        ulEncWAlignBase = JPE_COMP_W_ALIGN_BASE_NV12;
        ulEncHAlignBase = JPE_COMP_H_ALIGN_BASE_NV12;
    }
    else {
        if (m_ubJpeUIMode[ubCompType] == JPE_COMP_UI_MODE_VR &&
            m_usDscShotMode[ubCompType] != JPE_COMP_MJPEG_MODE) {
            // JPEG YUV420 Alignment (16,16) YUV422 Alignment (16,8)
            // But MFE YUV420 Need Align(32, 16)
            ulBufWAlignBase = MFE_COMP_W_ALIGN_BASE_YUV422;
            ulBufHAlignBase = MFE_COMP_H_ALIGN_BASE_YUV422;
        }
        else {
            ulBufWAlignBase = JPE_COMP_W_ALIGN_BASE_YUV422;
            ulBufHAlignBase = JPE_COMP_H_ALIGN_BASE_YUV422;
        }

        ulEncWAlignBase = JPE_COMP_W_ALIGN_BASE_YUV422;
        ulEncHAlignBase = JPE_COMP_H_ALIGN_BASE_YUV422;
    }

    m_usStillJpegWidth[ubCompType]  = usEncW;
    m_usStillJpegHeight[ubCompType] = usEncH;

    stJpeResol.ulEncW       = usEncW;//ALIGN_X(usEncW, ulEncWAlignBase);
    stJpeResol.ulEncH       = usEncH;//ALIGN_X(usEncH, ulEncHAlignBase);
    stJpeResol.ulEncBufW    = ALIGN_X(usEncW, ulBufWAlignBase);
    stJpeResol.ulEncBufH    = ALIGN_X(usEncH, ulBufHAlignBase);

    Component_JPE_SetParam(&Component_JPE[ubCompType], JPE_COMP_PARAM_RES, (void*)&stJpeResol);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetCustomQTable
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set custom q table

The function set global custom q table(zigzag order)

@param[in] ubMode Set custom q table mode: Off/All/Main/Thumbnail
@param[in] pTable Q table value
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_DSC_SetCustomQTable(MMP_UBYTE ubMode, MMP_UBYTE *pTable, MMP_UBYTE *pTableU, MMP_UBYTE *pTableV)
{
    MMP_ULONG i = 0;

    switch(ubMode) {
        case MMPS_DSC_CUSTOM_QTABLE_OFF:
            m_bUseCustomJpegQT = MMP_FALSE;
            m_bUseCustomThumbQT = MMP_FALSE;
            break;
        case MMPS_DSC_CUSTOM_QTABLE_ALL:
            m_bUseCustomJpegQT = MMP_TRUE;
            m_bUseCustomThumbQT = MMP_TRUE;

            for (i = 0; i < DSC_QTABLE_ARRAY_SIZE; i++) {
                m_ubCustomJpegQT[0][i]  = pTable[i];
                m_ubCustomThumbQT[0][i] = pTable[i];

                m_ubCustomJpegQT[1][i]  = pTableU[i];
                m_ubCustomThumbQT[1][i] = pTableU[i];

                m_ubCustomJpegQT[2][i]  = pTableV[i];
                m_ubCustomThumbQT[2][i] = pTableV[i];
            }
            break;
        case MMPS_DSC_CUSTOM_QTABLE_MAIN:
            m_bUseCustomJpegQT = MMP_TRUE;

            for (i = 0; i < DSC_QTABLE_ARRAY_SIZE; i++) {
                m_ubCustomJpegQT[0][i] = pTable[i];
                m_ubCustomJpegQT[1][i] = pTableU[i];
                m_ubCustomJpegQT[2][i] = pTableV[i];
            }
            break;
        case MMPS_DSC_CUSTOM_QTABLE_THUMB:
            m_bUseCustomThumbQT = MMP_TRUE;

            for (i = 0; i < DSC_QTABLE_ARRAY_SIZE; i++) {
                m_ubCustomThumbQT[0][i] = pTable[i];
                m_ubCustomThumbQT[1][i] = pTableU[i];
                m_ubCustomThumbQT[2][i] = pTableV[i];
            }
            break;
        default:
            break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetCaptureJpegQuality
//  Description :
//------------------------------------------------------------------------------
/** @brief The function sets Jpeg output quality for image capturing

The function sets Jpeg output quality for image capturing.
The function calls MMPD_DSC_SetJpegQuality to set the Jpeg quality

@param[in] bTargetCtrl  the flag of target control
@param[in] bLimitCtrl   the flag of limit control
@param[in] ulTargetSize the rate control target size (Unit:KB)
@param[in] ulLimitSize  the rate control limit size (Unit:KB)
@param[in] usMaxCount   the maximum count for the Jpeg encode trial
@param[in] qualitylevel jpeg quality level

@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_SetCaptureJpegQuality( MMP_UBYTE                   ubRcIdx,
                                        MMP_BOOL                    bTargetCtrl,
                                        MMP_BOOL                    bLimitCtrl,
                                        MMP_ULONG                   ulTargetSize,
                                        MMP_ULONG                   ulLimitSize,
                                        MMP_USHORT                  usMaxCount,
                                        MMP_JPGENC_RC_QUALITY_SEL   eQualitySel)
{
    if (bTargetCtrl && bLimitCtrl && (ulLimitSize < ulTargetSize * 11 / 10)) {
        MMPS_DSC_DBG_ERR(1, "ulLimitSize should larger then ulTargetSize * 110%");
        return MMP_ERR_NONE;
    }

    if (bLimitCtrl == MMP_FALSE) {
        ulLimitSize = ulTargetSize;
    }

    MMPF_JPGENC_RC_SetQualityCtl(   ubRcIdx,
                                    bTargetCtrl,
                                    bLimitCtrl,
                                    ulTargetSize,
                                    ulLimitSize,
                                    usMaxCount);

    if (!m_bUseCustomJpegQT) {
        MMPF_JPGENC_RC_SetQTableInfo(   ubRcIdx,
                                        (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[eQualitySel],
                                        (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[eQualitySel] + DSC_QTABLE_ARRAY_SIZE,
                                        (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[eQualitySel] + DSC_QTABLE_ARRAY_SIZE,
                                        eQualitySel);
    }
    else {
        MMPF_JPGENC_RC_SetQTableInfo(   ubRcIdx,
                                        m_ubCustomJpegQT[0],
                                        m_ubCustomJpegQT[1],
                                        m_ubCustomJpegQT[2],
                                        MMP_JPGENC_RC_QTBL_CUSTOMER);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CaptureJPEG
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_CaptureJPEG(   MMP_UBYTE               ubCompUseType,
                                MMPS_DSC_CAPTURE_INFO   *pDscCaptInfo)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubRcIdx = MMP_JPGENC_RC_ID_PRM_CAPTURE;

    if (!pDscCaptInfo->bCaptureEn) {
        return MMP_ERR_NONE;
    }

    if (ubCompUseType == JPE_COMP_PRM_PRIMARY) {
        pDscCaptInfo->ulExifHdrAddr = m_ulExifHeaderBufAddr[MMP_JPEG_ENC_CAM_SEL_PRM];
        ubRcIdx = MMP_JPGENC_RC_ID_PRM_CAPTURE;
    }
    else if (ubCompUseType == JPE_COMP_SCD_PRIMARY) {
        pDscCaptInfo->ulExifHdrAddr = m_ulExifHeaderBufAddr[MMP_JPEG_ENC_CAM_SEL_SCD];
        ubRcIdx = MMP_JPGENC_RC_ID_SCD_CAPTURE;
    }
    else {
        MMPS_DSC_DBG_ERR(1, "UnSupport Type for JPEG Capture\r\n");
        return MMP_ERR_NONE;
    }

    if (pDscCaptInfo->ulExifHdrAddr == 0) {
        pDscCaptInfo->bExifEn = MMP_FALSE;
    }

    if (MMP_JPEG_ENC_StartCaptureCallback != NULL) {
        MMP_JPEG_ENC_StartCaptureCallback(pDscCaptInfo);
    }

    /* Set capture attributes */
    eRetErr = MMPS_DSC_SetJpeUIMode(ubCompUseType, pDscCaptInfo->ubUiMode);

    eRetErr = MMPS_DSC_SetShotMode(ubCompUseType, pDscCaptInfo->ubShotMode);
    eRetErr = MMPS_DSC_SetMaxShotNum(ubCompUseType, pDscCaptInfo->usMaxShotNum);

    eRetErr = MMPS_DSC_SetJpegEncFmt(ubCompUseType, pDscCaptInfo->ubRawFmt);
    eRetErr = MMPS_DSC_SetJpegEncResol(ubCompUseType, pDscCaptInfo->usPrimaryW, pDscCaptInfo->usPrimaryH);

    eRetErr = MMPS_DSC_SetCaptureJpegQuality(   ubRcIdx,
                                                pDscCaptInfo->stQualityCtl.bTargetCtl,
                                                pDscCaptInfo->stQualityCtl.bLimitCtl,
                                                pDscCaptInfo->stQualityCtl.ulTargetSize,
                                                pDscCaptInfo->stQualityCtl.ulLimitSize,
                                                pDscCaptInfo->stQualityCtl.usMaxTrialCnt,
                                                pDscCaptInfo->stQualityCtl.ubQualitySel);

    if (pDscCaptInfo->ubShotMode == JPE_COMP_CONTINUOUS_SHOT) {
        if (ubCompUseType == JPE_COMP_PRM_PRIMARY) {
            eRetErr = MMPF_ContiShot_InitParam(MMP_JPEG_ENC_CAM_SEL_PRM,
                                               pDscCaptInfo->ulExifHdrAddr,
                                               pDscCaptInfo->usMaxShotNum);
        }
        else if (ubCompUseType == JPE_COMP_SCD_PRIMARY) {
            eRetErr = MMPF_ContiShot_InitParam(MMP_JPEG_ENC_CAM_SEL_SCD,
                                               pDscCaptInfo->ulExifHdrAddr,
                                               pDscCaptInfo->usMaxShotNum);
        }

        if (pDscCaptInfo->bExifEn) {
            MMPD_DSC_SetCardModeExifEnc(EXIF_NODE_ID_PRIMARY,
                                        pDscCaptInfo->bExifEn,
                                        pDscCaptInfo->bThumbnailEn,
                                        pDscCaptInfo->usPrimaryW,
                                        pDscCaptInfo->usPrimaryH,
                                        pDscCaptInfo->usThumbWidth,
                                        pDscCaptInfo->usThumbHeight);
        }
    }

    /* Calculate JPE buffer attribute */
    if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR)
        MMPS_DSC_CalculateJpeOBufAttr(ubCompUseType, MMP_TRUE);
    else
        MMPS_DSC_CalculateJpeOBufAttr(ubCompUseType, MMP_FALSE);

    pDscCaptInfo->ulThumbnailAddr = 0;
    pDscCaptInfo->ulThumbnailSize = 0;
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        pDscCaptInfo->ulLargeThumbJpegAddr = 0;
        pDscCaptInfo->ulLargeThumbJpegSize = 0;
    }
    #endif

    /* Open Script */
    if (ubCompUseType == JPE_COMP_PRM_PRIMARY) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            OpenScript(COMPO_SCRIPT_VR_PRM_BAYER_CAPTURE);
            OpenPortScript(PORT_SCRIPT_VR_PRM_BAYER_CAPTURE);
        }
        else {
            if(MMP_GetANACamType() == ANA_CAM_2I2O){
                OpenScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_RAW1);
                OpenPortScript(PORT_SCRIPT_DSC_PRM_CAPTURE_RAW1);
            }
            else{
                OpenScript(COMPO_SCRIPT_DSC_PRM_CAPTURE);
                OpenPortScript(PORT_SCRIPT_DSC_PRM_CAPTURE);
            }
        }
    }
    else if (ubCompUseType == JPE_COMP_SCD_PRIMARY) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                OpenScript(COMPO_SCRIPT_VR_SCD_BAYER_CAPTURE);
                OpenPortScript(PORT_SCRIPT_VR_SCD_BAYER_CAPTURE);
            }
            else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
                OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_CAPTURE);
                OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_CAPTURE);
            }
            else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
                OpenScript(COMPO_SCRIPT_VR_USBH_CAPTURE);
                OpenPortScript(PORT_SCRIPT_VR_USBH_CAPTURE);
            }
            else if (CAM_CHECK_USB(USB_CAM_AIT)) {
            	OpenScript(COMPO_SCRIPT_VR_USBH_CAPTURE);
                OpenPortScript(PORT_SCRIPT_VR_USBH_CAPTURE);
            }
        }
        else {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                OpenScript(COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE);
                OpenPortScript(PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE);
            }
            else {
                OpenScript(COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE);        //DIP_S3<--JPE4-->JPEMGR4
                OpenPortScript(PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE);     //DIP_S3
            }
        }
    }

    if (pDscCaptInfo->ubShotMode == JPE_COMP_CONTINUOUS_SHOT) {
        pDscCaptInfo->ulJpegFileSize = 0xFFFFFFFF;
        return MMP_ERR_NONE;
    }

    /* Get the address and size of JPEG */
    MMPF_JPGENC_GetJpegSize(ubRcIdx, &(pDscCaptInfo->ulPrimaryJpgSize));
    MMPF_JPGENC_GetJpegBitBufAttr(ubRcIdx, &(pDscCaptInfo->ulPrimaryJpgAddr), NULL);
    MMPF_JPGENC_GetJpegStampInfo(ubRcIdx, &(pDscCaptInfo->stDateTime));

    pDscCaptInfo->ulJpegFileSize = pDscCaptInfo->ulPrimaryJpgSize;

    /* Encode EXIF and Thumbnail */
    if (pDscCaptInfo->bExifEn) {

        // JPEG YUV420 Alignment (16,16) YUV422 Alignment (16,8)
        pDscCaptInfo->usThumbWidth  = ALIGN_X(pDscCaptInfo->usThumbWidth, JPE_COMP_W_ALIGN_BASE_NV12);
        pDscCaptInfo->usThumbHeight = ALIGN_X(pDscCaptInfo->usThumbHeight, JPE_COMP_H_ALIGN_BASE_NV12);

        MMPD_DSC_SetCardModeExifEnc(EXIF_NODE_ID_PRIMARY,
                                    pDscCaptInfo->bExifEn,
                                    pDscCaptInfo->bThumbnailEn,
                                    pDscCaptInfo->usPrimaryW,
                                    pDscCaptInfo->usPrimaryH,
                                    pDscCaptInfo->usThumbWidth,
                                    pDscCaptInfo->usThumbHeight);

        if (pDscCaptInfo->bThumbnailEn) {

            eRetErr = MMPS_DSC_EncodeThumbnail( ubCompUseType,
                                                pDscCaptInfo);

            pDscCaptInfo->ulJpegFileSize += pDscCaptInfo->ulThumbnailSize;

            MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, IFD_IDX_IFD1, IFD1_THUMBNAIL_LENGTH, EXIF_TYPE_LONG, 1, (MMP_UBYTE*)(&pDscCaptInfo->ulThumbnailSize), 4, MMP_FALSE);
        }

        #if (EXIF_MANUAL_UPDATE)
        {
            MMP_ULONG i = 0;
            MMPS_DSC_EXIF_CONFIG Exif;

            for (i = 0; ; i++) {
                if (MMP_TRUE == MMPS_DSC_GetImageEXIF(i, &Exif)) {
                    MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, Exif.IfdID, Exif.TagID, Exif.TagType, Exif.TagDataSize, (MMP_UBYTE*)Exif.Data, Exif.DataSize, MMP_FALSE);
                }
                else {
                    break;
                }
            }
        }
        #endif

        MMPF_EXIF_FinishExif(EXIF_NODE_ID_PRIMARY,
                             pDscCaptInfo->ulExifHdrAddr,
                             &pDscCaptInfo->ulExifHdrSize,
                             pDscCaptInfo->ulThumbnailSize);

        MMPF_EXIF_KillExifForMS(EXIF_NODE_ID_PRIMARY);

        pDscCaptInfo->ulJpegFileSize += pDscCaptInfo->ulExifHdrSize;

        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        if (m_bMultiPicFormatEnable) {
            pDscCaptInfo->ulMpfDataStartAddr = 0;
        }
        #endif
    }

    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    /* Encode large thumbnail and its Exif */
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        pDscCaptInfo->ulLargeThumbJpegAddr = m_ulLargeThumbJpegCompStart;

        MMPS_DSC_EncodeLargeThumb(  m_ulLargeThumbWidth,
                                    m_ulLargeThumbHeight,
                                    &ulThumbnailSize);

        // Update MPF Entry and LargeThumb Exif
        MMPD_DSC_UpdateMpfEntry(IFD_IDX_MPF_INDEX_IFD,
                                MPF_ENTRY_ID_PRIMARY_IMG,
                                MPF_ATTR_FLAG_DEP_PARENT_IMG | MPF_ATTR_FLAG_DATA_FMT_JPEG | MPF_ATTR_FLAG_TYPE_BASELINE_PRI_IMG,
                                pDscCaptInfo->ulPrimaryJpgSize,
                                0,
                                2, 0,
                                MMP_FALSE);

        if (m_ubLargeThumbResMode == MMP_DSC_LARGE_THUMB_RES_FHD) {
            MMPD_DSC_UpdateMpfEntry(IFD_IDX_MPF_INDEX_IFD,
                                    MPF_ENTRY_ID_LARGE_THUMB1,
                                    MPF_ATTR_FLAG_DEP_CHILD_IMG | MPF_ATTR_FLAG_DATA_FMT_JPEG | MPF_ATTR_FLAG_TYPE_LARGE_THUMB_FHD,
                                    pDscCaptInfo->ulLargeThumbJpegSize + 0x4A /* Large Thumb Exif Size */,
                                    (pDscCaptInfo->ulPrimaryJpgSize +
                                     /* pDscCaptInfo->ulMpfDataSize - 6 */ 0x52),
                                    0, 0,
                                    MMP_FALSE);
        }
        else {
            MMPD_DSC_UpdateMpfEntry(IFD_IDX_MPF_INDEX_IFD,
                                    MPF_ENTRY_ID_LARGE_THUMB1,
                                    MPF_ATTR_FLAG_DEP_CHILD_IMG | MPF_ATTR_FLAG_DATA_FMT_JPEG | MPF_ATTR_FLAG_TYPE_LARGE_THUMB_VGA,
                                    pDscCaptInfo->ulLargeThumbJpegSize + 0x4A /* Large Thumb Exif Size */,
                                    (pDscCaptInfo->ulPrimaryJpgSize +
                                     /* pDscCaptInfo->ulMpfDataSize - 6 */ 0x52),
                                    0, 0,
                                    MMP_FALSE);
        }

        MMPF_MPF_FinishMpf(pDscCaptInfo->ulMpfDataStartAddr,
                           &(pDscCaptInfo->ulMpfDataSize));

        pDscCaptInfo->ulLargeThumbExifAddr = 0; // TBD

        MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_LARGE_THUMB1, IFD_IDX_EXIFIFD, EXIFIFD_PIXL_X_DIMENSION, EXIF_TYPE_SHORT, 1, (MMP_UBYTE *)(&m_ulLargeThumbWidth), 2, MMP_FALSE);
        MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_LARGE_THUMB1, IFD_IDX_EXIFIFD, EXIFIFD_PIXL_Y_DIMENSION, EXIF_TYPE_SHORT, 1, (MMP_UBYTE *)(&m_ulLargeThumbHeight), 2, MMP_FALSE);

        MMPF_EXIF_FinishExif(EXIF_NODE_ID_LARGE_THUMB1,
                             pDscCaptInfo->ulLargeThumbExifAddr,
                             &(pDscCaptInfo->ulLargeThumbExifSize),
                             0);
    }
    #endif

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CaptureDualJPEG
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_CaptureDualJPEG(MMPS_DSC_CAPTURE_INFO *pPrmCaptInfo, MMPS_DSC_CAPTURE_INFO *pScdCaptInfo)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubPrmCompUseType = JPE_COMP_PRM_PRIMARY;
    MMP_UBYTE   ubScdCompUseType = JPE_COMP_SCD_PRIMARY;

    if (!pPrmCaptInfo->bCaptureEn || !pScdCaptInfo->bCaptureEn) {
        return MMP_ERR_NONE;
    }

    pPrmCaptInfo->ulExifHdrAddr = m_ulExifHeaderBufAddr[MMP_JPEG_ENC_CAM_SEL_PRM];
    pScdCaptInfo->ulExifHdrAddr = m_ulExifHeaderBufAddr[MMP_JPEG_ENC_CAM_SEL_SCD];

    if (pPrmCaptInfo->ulExifHdrAddr == 0) {
        pPrmCaptInfo->bExifEn = MMP_FALSE;
    }
    if (pScdCaptInfo->ulExifHdrAddr == 0) {
        pScdCaptInfo->bExifEn = MMP_FALSE;
    }

    /* Set capture attributes */
    eRetErr = MMPS_DSC_SetJpeUIMode(ubPrmCompUseType, pPrmCaptInfo->ubUiMode);
    eRetErr = MMPS_DSC_SetJpeUIMode(ubScdCompUseType, pScdCaptInfo->ubUiMode);

    eRetErr = MMPS_DSC_SetShotMode(ubPrmCompUseType, pPrmCaptInfo->ubShotMode);
    eRetErr = MMPS_DSC_SetShotMode(ubScdCompUseType, pScdCaptInfo->ubShotMode);

    eRetErr = MMPS_DSC_SetMaxShotNum(ubPrmCompUseType, pPrmCaptInfo->usMaxShotNum);
    eRetErr = MMPS_DSC_SetMaxShotNum(ubScdCompUseType, pScdCaptInfo->usMaxShotNum);

    eRetErr = MMPS_DSC_SetJpegEncFmt(ubPrmCompUseType, pPrmCaptInfo->ubRawFmt);
    eRetErr = MMPS_DSC_SetJpegEncFmt(ubScdCompUseType, pScdCaptInfo->ubRawFmt);

    eRetErr = MMPS_DSC_SetJpegEncResol( ubPrmCompUseType,
                                        pPrmCaptInfo->usPrimaryW, pPrmCaptInfo->usPrimaryH);
    eRetErr = MMPS_DSC_SetJpegEncResol( ubScdCompUseType,
                                        pScdCaptInfo->usPrimaryW, pScdCaptInfo->usPrimaryH);

    eRetErr = MMPS_DSC_SetCaptureJpegQuality(   MMP_JPGENC_RC_ID_PRM_CAPTURE,
                                                pPrmCaptInfo->stQualityCtl.bTargetCtl,
                                                pPrmCaptInfo->stQualityCtl.bLimitCtl,
                                                pPrmCaptInfo->stQualityCtl.ulTargetSize,
                                                pPrmCaptInfo->stQualityCtl.ulLimitSize,
                                                pPrmCaptInfo->stQualityCtl.usMaxTrialCnt,
                                                pPrmCaptInfo->stQualityCtl.ubQualitySel);
    eRetErr = MMPS_DSC_SetCaptureJpegQuality(   MMP_JPGENC_RC_ID_SCD_CAPTURE,
                                                pScdCaptInfo->stQualityCtl.bTargetCtl,
                                                pScdCaptInfo->stQualityCtl.bLimitCtl,
                                                pScdCaptInfo->stQualityCtl.ulTargetSize,
                                                pScdCaptInfo->stQualityCtl.ulLimitSize,
                                                pScdCaptInfo->stQualityCtl.usMaxTrialCnt,
                                                pScdCaptInfo->stQualityCtl.ubQualitySel);

    /* Calculate JPE buffer attribute */
    if (pPrmCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
        MMPS_DSC_CalculateJpeOBufAttr(ubPrmCompUseType, MMP_TRUE);
        MMPS_DSC_CalculateJpeOBufAttr(ubScdCompUseType, MMP_TRUE);
    }
    else {
        MMPS_DSC_CalculateJpeOBufAttr(ubPrmCompUseType, MMP_FALSE);
        MMPS_DSC_CalculateJpeOBufAttr(ubScdCompUseType, MMP_FALSE);
    }

    pPrmCaptInfo->ulThumbnailAddr = 0;
    pPrmCaptInfo->ulThumbnailSize = 0;
    pScdCaptInfo->ulThumbnailAddr = 0;
    pScdCaptInfo->ulThumbnailSize = 0;
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    if (m_bMultiPicFormatEnable && m_bEncLargeThumbEnable)
    {
        pPrmCaptInfo->ulLargeThumbJpegAddr = 0;
        pPrmCaptInfo->ulLargeThumbJpegSize = 0;
        pScdCaptInfo->ulLargeThumbJpegAddr = 0;
        pScdCaptInfo->ulLargeThumbJpegSize = 0;
    }
    #endif

    /* Open Script */
    if (pPrmCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
        OpenScript(COMPO_SCRIPT_VR_PRM_BAYER_CAPTURE);

        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            OpenScript(COMPO_SCRIPT_VR_SCD_BAYER_CAPTURE);
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))
            OpenScript(COMPO_SCRIPT_VR_SCD_ANADEC_CAPTURE);
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264))
            OpenScript(COMPO_SCRIPT_VR_USBH_CAPTURE);
        else if (CAM_CHECK_USB(USB_CAM_AIT))
            OpenScript(COMPO_SCRIPT_VR_USBH_CAPTURE);

        OpenPortScript(PORT_SCRIPT_VR_PRM_BAYER_CAPTURE);

        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            OpenPortScript(PORT_SCRIPT_VR_SCD_BAYER_CAPTURE);
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))
            OpenPortScript(PORT_SCRIPT_VR_SCD_ANADEC_CAPTURE);
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264))
            OpenPortScript(PORT_SCRIPT_VR_USBH_CAPTURE);
        else if (CAM_CHECK_USB(USB_CAM_AIT))
            OpenPortScript(PORT_SCRIPT_VR_USBH_CAPTURE);
    }
    else {
        OpenScript(COMPO_SCRIPT_DSC_PRM_CAPTURE);
        OpenScript(COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE);
        OpenPortScript(PORT_SCRIPT_DSC_PRM_CAPTURE);
        OpenPortScript(PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE);
    }

    if (pPrmCaptInfo->ubShotMode == JPE_COMP_CONTINUOUS_SHOT) {
        pPrmCaptInfo->ulJpegFileSize = 0xFFFFFFFF;
        return MMP_ERR_NONE;
    }
    if (pScdCaptInfo->ubShotMode == JPE_COMP_CONTINUOUS_SHOT) {
        pScdCaptInfo->ulJpegFileSize = 0xFFFFFFFF;
        return MMP_ERR_NONE;
    }

    /* Get the address and size of JPEG */
    MMPF_JPGENC_GetJpegSize(MMP_JPGENC_RC_ID_PRM_CAPTURE, &(pPrmCaptInfo->ulPrimaryJpgSize));
    MMPF_JPGENC_GetJpegBitBufAttr(MMP_JPGENC_RC_ID_PRM_CAPTURE, &(pPrmCaptInfo->ulPrimaryJpgAddr), NULL);
    MMPF_JPGENC_GetJpegStampInfo(MMP_JPGENC_RC_ID_PRM_CAPTURE, &(pPrmCaptInfo->stDateTime));

    pPrmCaptInfo->ulJpegFileSize = pPrmCaptInfo->ulPrimaryJpgSize;

    MMPF_JPGENC_GetJpegSize(MMP_JPGENC_RC_ID_SCD_CAPTURE, &(pScdCaptInfo->ulPrimaryJpgSize));
    MMPF_JPGENC_GetJpegBitBufAttr(MMP_JPGENC_RC_ID_SCD_CAPTURE, &(pScdCaptInfo->ulPrimaryJpgAddr), NULL);
    MMPF_JPGENC_GetJpegStampInfo(MMP_JPGENC_RC_ID_SCD_CAPTURE, &(pScdCaptInfo->stDateTime));

    pScdCaptInfo->ulJpegFileSize = pScdCaptInfo->ulPrimaryJpgSize;

    /* Encode EXIF and Thumbnail */
    if (pPrmCaptInfo->bExifEn) {

        // JPEG YUV420 Alignment (16,16) YUV422 Alignment (16,8)
        pPrmCaptInfo->usThumbWidth  = ALIGN_X(pPrmCaptInfo->usThumbWidth, JPE_COMP_W_ALIGN_BASE_NV12);
        pPrmCaptInfo->usThumbHeight = ALIGN_X(pPrmCaptInfo->usThumbHeight, JPE_COMP_H_ALIGN_BASE_NV12);

        MMPD_DSC_SetCardModeExifEnc(EXIF_NODE_ID_PRIMARY,
                                    pPrmCaptInfo->bExifEn,
                                    pPrmCaptInfo->bThumbnailEn,
                                    pPrmCaptInfo->usPrimaryW,
                                    pPrmCaptInfo->usPrimaryH,
                                    pPrmCaptInfo->usThumbWidth,
                                    pPrmCaptInfo->usThumbHeight);

        if (pPrmCaptInfo->bThumbnailEn) {

            eRetErr = MMPS_DSC_EncodeThumbnail( ubPrmCompUseType,
                                                pPrmCaptInfo);

            pPrmCaptInfo->ulJpegFileSize += pPrmCaptInfo->ulThumbnailSize;

            MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, IFD_IDX_IFD1, IFD1_THUMBNAIL_LENGTH, EXIF_TYPE_LONG, 1, (MMP_UBYTE*)(&pPrmCaptInfo->ulThumbnailSize), 4, MMP_FALSE);
        }

        #if (EXIF_MANUAL_UPDATE)
        {
            MMP_ULONG i = 0;
            MMPS_DSC_EXIF_CONFIG Exif;

            for (i = 0; ; i++) {
                if (MMP_TRUE == MMPS_DSC_GetImageEXIF(i, &Exif)) {
                    MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, Exif.IfdID, Exif.TagID, Exif.TagType, Exif.TagDataSize, (MMP_UBYTE*)Exif.Data, Exif.DataSize, MMP_FALSE);
                }
                else {
                    break;
                }
            }
        }
        #endif

        MMPF_EXIF_FinishExif(EXIF_NODE_ID_PRIMARY,
                             pPrmCaptInfo->ulExifHdrAddr,
                             &pPrmCaptInfo->ulExifHdrSize,
                             pPrmCaptInfo->ulThumbnailSize);

        pPrmCaptInfo->ulJpegFileSize += pPrmCaptInfo->ulExifHdrSize;
    }
    if (pScdCaptInfo->bExifEn) {

        // JPEG YUV420 Alignment (16,16) YUV422 Alignment (16,8)
        pScdCaptInfo->usThumbWidth  = ALIGN_X(pScdCaptInfo->usThumbWidth, JPE_COMP_W_ALIGN_BASE_NV12);
        pScdCaptInfo->usThumbHeight = ALIGN_X(pScdCaptInfo->usThumbHeight, JPE_COMP_H_ALIGN_BASE_NV12);

        MMPD_DSC_SetCardModeExifEnc(EXIF_NODE_ID_PRIMARY,
                                    pScdCaptInfo->bExifEn,
                                    pScdCaptInfo->bThumbnailEn,
                                    pScdCaptInfo->usPrimaryW,
                                    pScdCaptInfo->usPrimaryH,
                                    pScdCaptInfo->usThumbWidth,
                                    pScdCaptInfo->usThumbHeight);

        if (pScdCaptInfo->bThumbnailEn) {

            eRetErr = MMPS_DSC_EncodeThumbnail( ubScdCompUseType,
                                                pScdCaptInfo);

            pScdCaptInfo->ulJpegFileSize += pScdCaptInfo->ulThumbnailSize;

            MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, IFD_IDX_IFD1, IFD1_THUMBNAIL_LENGTH, EXIF_TYPE_LONG, 1, (MMP_UBYTE*)(&pScdCaptInfo->ulThumbnailSize), 4, MMP_FALSE);
        }

        #if (EXIF_MANUAL_UPDATE)
        {
            MMP_ULONG i = 0;
            MMPS_DSC_EXIF_CONFIG Exif;

            for (i = 0; ; i++) {
                if (MMP_TRUE == MMPS_DSC_GetImageEXIF(i, &Exif)) {
                    MMPS_DSC_UpdateExifNode(EXIF_NODE_ID_PRIMARY, Exif.IfdID, Exif.TagID, Exif.TagType, Exif.TagDataSize, (MMP_UBYTE*)Exif.Data, Exif.DataSize, MMP_FALSE);
                }
                else {
                    break;
                }
            }
        }
        #endif

        MMPF_EXIF_FinishExif(EXIF_NODE_ID_PRIMARY,
                             pScdCaptInfo->ulExifHdrAddr,
                             &pScdCaptInfo->ulExifHdrSize,
                             pScdCaptInfo->ulThumbnailSize);

        pScdCaptInfo->ulJpegFileSize += pScdCaptInfo->ulExifHdrSize;
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_EncodeThumbnail
//  Description : TBD
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_EncodeThumbnail(MMP_UBYTE               ubParentCompType,
                                        MMPS_DSC_CAPTURE_INFO   *pDscCaptInfo)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE   ubCompUseType = JPE_COMP_PRM_THUMB;
    MMP_UBYTE   ubRcIdx = MMP_JPGENC_RC_ID_PRM_CAPTURE;

    if (!pDscCaptInfo->bThumbnailEn) {
        return eRetErr;
    }

    if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
        // NOT SUPPORT NOW
        return eRetErr;
    }

    if (ubParentCompType == JPE_COMP_PRM_PRIMARY) {
        ubCompUseType = JPE_COMP_PRM_THUMB;
        ubRcIdx = MMP_JPGENC_RC_ID_PRM_CAPTURE;
    }
    else if (ubParentCompType == JPE_COMP_SCD_PRIMARY) {
        ubCompUseType = JPE_COMP_SCD_THUMB;
        ubRcIdx = MMP_JPGENC_RC_ID_SCD_CAPTURE;
    }
    else {
        return eRetErr;
    }

    /* Update DIP parameter */
    if(MMP_GetANACamType() == ANA_CAM_2I2O){
        MMPS_DSC_AdjustScdCaptureThumbPipe_2INO(ubCompUseType, pDscCaptInfo->usThumbWidth, pDscCaptInfo->usThumbHeight);
    }
    else if (ubCompUseType == JPE_COMP_PRM_THUMB){
        MMPS_DSC_AdjustPrmCaptureThumbPipe(PRM_SENSOR, pDscCaptInfo->usThumbWidth, pDscCaptInfo->usThumbHeight);
    }
    else if (ubCompUseType == JPE_COMP_SCD_THUMB){
        MMPS_DSC_AdjustScdCaptureThumbPipe(SCD_SENSOR, pDscCaptInfo->usThumbWidth, pDscCaptInfo->usThumbHeight);
    }

    /* Set capture attributes */
    eRetErr = MMPS_DSC_SetJpeUIMode(ubCompUseType, pDscCaptInfo->ubUiMode);

    eRetErr = MMPS_DSC_SetShotMode(ubCompUseType, pDscCaptInfo->ubShotMode);
    eRetErr = MMPS_DSC_SetMaxShotNum(ubCompUseType, pDscCaptInfo->usMaxShotNum);

    eRetErr = MMPS_DSC_SetJpegEncFmt(ubCompUseType, pDscCaptInfo->ubRawFmt);
    eRetErr = MMPS_DSC_SetJpegEncResol( ubCompUseType,
                                        pDscCaptInfo->usThumbWidth, pDscCaptInfo->usThumbHeight);

    eRetErr = MMPF_JPGENC_RC_SetQTableInfo( ubRcIdx,
                                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_LOW],
                                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_LOW] + DSC_QTABLE_ARRAY_SIZE,
                                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_LOW] + DSC_QTABLE_ARRAY_SIZE,
                                            MMP_JPGENC_RC_QTBL_NORMAL);

    eRetErr = MMPF_JPGENC_RC_SetQualityCtl( ubRcIdx,
                                            MMP_FALSE,
                                            MMP_TRUE,
                                            m_stDscConfig.encParams.ulMaxThumbnailSize>>10,
                                            m_stDscConfig.encParams.ulMaxThumbnailSize>>10,
                                            1);

    /* Calculate JPE buffer attribute */
    if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR)
        MMPS_DSC_CalculateJpeOBufAttr(ubCompUseType, MMP_TRUE);
    else
        MMPS_DSC_CalculateJpeOBufAttr(ubCompUseType, MMP_FALSE);

    /* Open Script */
    if (ubCompUseType == JPE_COMP_PRM_THUMB) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            // TBD
        }
        else {
             if(MMP_GetANACamType() == ANA_CAM_2I2O){
                OpenScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1);
                OpenPortScript(PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1);
            }else{
                OpenScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB);
                OpenPortScript(PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB);
            }
        }
    }
    else if (ubCompUseType == JPE_COMP_SCD_THUMB) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            // TBD
        }
        else {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                OpenScript(COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB);
                OpenPortScript(PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB);
            }
            else {
                OpenScript(COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB);//DIP_S3<--DIP_S4-->DIP_S5-->DIP_S6-->JPE7-->JPEMGR7
                OpenPortScript(PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB);//DIP_S3
            }
        }
    }
    else {
        return MMP_ERR_NONE;
    }

    /* Get the address and size of JPEG */
    MMPF_JPGENC_GetJpegSize(ubRcIdx, &(pDscCaptInfo->ulThumbnailSize));
    MMPF_JPGENC_GetJpegBitBufAttr(ubRcIdx, &(pDscCaptInfo->ulThumbnailAddr), NULL);

    MMPS_DSC_DBG_MSG(0, "Thumb Addr[%x] Size[%d]\r\n", pDscCaptInfo->ulThumbnailAddr, pDscCaptInfo->ulThumbnailSize);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CaptureJPEGFinish
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_CaptureJPEGFinish(MMP_UBYTE               ubCompUseType,
                                   MMPS_DSC_CAPTURE_INFO   *pDscCaptInfo)
{
    /* Close script to release memory */
    if (ubCompUseType == JPE_COMP_PRM_PRIMARY) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            CloseScript(COMPO_SCRIPT_VR_PRM_BAYER_CAPTURE);
            if (pDscCaptInfo->bThumbnailEn) {
                // TBD
            }
        }
        else {
            if(MMP_GetANACamType() == ANA_CAM_2I2O){
                CloseScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_RAW1);
                if (pDscCaptInfo->bThumbnailEn) {
                    CloseScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1);
                }
            }else{
                CloseScript(COMPO_SCRIPT_DSC_PRM_CAPTURE);
                if (pDscCaptInfo->bThumbnailEn) {
                    CloseScript(COMPO_SCRIPT_DSC_PRM_CAPTURE_THUMB);
                }
            }
        }
    }
    else if (ubCompUseType == JPE_COMP_SCD_PRIMARY) {
        if (pDscCaptInfo->ubUiMode == JPE_COMP_UI_MODE_VR) {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                CloseScript(COMPO_SCRIPT_VR_SCD_BAYER_CAPTURE);
            else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))
                CloseScript(COMPO_SCRIPT_VR_SCD_ANADEC_CAPTURE);
            else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264))
                CloseScript(COMPO_SCRIPT_VR_USBH_CAPTURE);
            else if (CAM_CHECK_USB(USB_CAM_AIT))
                CloseScript(COMPO_SCRIPT_VR_USBH_CAPTURE);

            if (pDscCaptInfo->bThumbnailEn) {
                // TBD
            }
        }
        else {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
                CloseScript(COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE);
                if (pDscCaptInfo->bThumbnailEn) {
                    CloseScript(COMPO_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB);
                }
            }
            else {
                CloseScript(COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE);
                if (pDscCaptInfo->bThumbnailEn) {
                    CloseScript(COMPO_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB);
                }
            }
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_DeInitJpegEncModule
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_DeInitJpegEncModule(void)
{
    MMP_ERR     ret_err = MMP_ERR_NONE;
    MMP_ULONG   ulActiveInstNum = 0;

    ret_err = MMPF_JPGENC_GetActiveInstNum(&ulActiveInstNum);

    if (ulActiveInstNum == 0) {
        if (MMPF_JPGENC_IsModuleInit()) {
            ret_err = MMPF_JPGENC_DeinitModule();
        }
    }

    return ret_err;
}

#if (DSC_SUPPORT_BASELINE_MP_FILE)
//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_EncodeLargeThumb
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_DSC_EncodeLargeThumb(MMP_ULONG  ulThumbWidth,
                                         MMP_ULONG  ulThumbHeight,
                                         MMP_ULONG  *pThumbnailSize)
{
    if (!m_bMultiPicFormatEnable || !m_bEncLargeThumbEnable) {
        return MMP_ERR_NONE;
    }

    if (!m_bUseCustomJpegQT) {
        MMPF_JPGENC_RC_SetQTableInfo( MMP_JPGENC_RC_ID_PRM_CAPTURE,
                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_HIGH],
                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_HIGH] + DSC_QTABLE_ARRAY_SIZE,
                            (MMP_UBYTE *)m_stDscConfig.encParams.ubDscQtable[MMP_JPGENC_RC_QUALITY_SEL_HIGH] + DSC_QTABLE_ARRAY_SIZE,
                            MMP_JPGENC_RC_QTBL_NORMAL);
    }
    else {
        MMPF_JPGENC_RC_SetQTableInfo(MMP_JPGENC_RC_ID_PRM_CAPTURE, m_ubCustomJpegQT[0], m_ubCustomJpegQT[1], m_ubCustomJpegQT[2], MMP_JPGENC_RC_QTBL_NORMAL);
    }

    MMPF_JPGENC_RC_SetQualityCtl(   MMP_JPGENC_RC_ID_PRM_CAPTURE,
                                    MMP_TRUE,
                                    MMP_FALSE,
                                    m_stDscConfig.encParams.ulMaxLargeThumbSize>>10,
                                    m_stDscConfig.encParams.ulMaxLargeThumbSize>>10,
                                    2);

    MMPF_JPGENC_GetJpegSize(MMP_JPGENC_RC_ID_PRM_CAPTURE, pThumbnailSize);
    MMPF_JPGENC_GetJpegBitBufAttr(MMP_JPGENC_RC_ID_PRM_CAPTURE, &ulJpegCompStart, NULL);

    pDscCaptInfo->ulLargeThumbJpegAddr = ulJpegCompStart;
    pDscCaptInfo->ulLargeThumbJpegSize = *pThumbnailSize;

    return MMP_ERR_NONE;
}
#endif

#if 0
void _____Playback_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CustomedPlaybackAttr
//  Description :
//------------------------------------------------------------------------------
/**
 @brief The function set the display window for DSC
 @param[in] bUserConfig     Use user defined preview configuration.
 @param[in] bMirror         Use DIP scale to mirror preview buffer.
 @param[in] usBufWidth      Preview buffer width.
 @param[in] usBufHeight     Preview buffer height.
 @param[in] usStartX        The X Offset of the display window.
 @param[in] usStartY        The Y Offset of the display window.
 @param[in] usWinWidth      The width of the display window.
 @param[in] usWinHeight     The height of the display window.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_CustomedPlaybackAttr(MMP_BOOL  bMirror,
                                      MMP_UBYTE sFitMode,
                                      MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                      MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                      MMP_USHORT usWinWidth, MMP_USHORT usWinHeight)
{
    m_stDscCustPlayInfo.bMirror         = bMirror;
    m_stDscCustPlayInfo.sFitMode        = sFitMode;
    m_stDscCustPlayInfo.ulDecodeOutW    = usBufWidth;
    m_stDscCustPlayInfo.ulDecodeOutH    = usBufHeight;
    m_stDscCustPlayInfo.ulDispStartX    = usStartX;
    m_stDscCustPlayInfo.ulDispStartY    = usStartY;
    m_stDscCustPlayInfo.ulDispWidth     = usWinWidth;
    m_stDscCustPlayInfo.ulDispHeight    = usWinHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetPlaybackMode
//  Description : The function sets the DSC system into playback mode
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_SetPlaybackMode(MMP_USHORT usDecodeMode)
{
    MMPS_DSC_AllocFileNameBuf();

    m_usDscDecMode = usDecodeMode;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_PlaybackJpeg
//  Description : The function playback JPEG file on the display device
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_PlaybackJpeg(MMP_DSC_JPEG_INFO *pJpegInfo, MMP_ULONG ulScalOutW, MMP_ULONG ulScalOutH)
{
    MMP_ERR                         eRetErr = MMP_ERR_NONE;
    MMP_BOOL                        bDecDone = MMP_FALSE;
    MMP_SCAL_FIT_RANGE              stFitRange;
    MMP_SCAL_GRAB_CTRL              stGrabCtl;
    MMP_ULONG                       ulInputW = 0, ulInputH = 0;
    MMP_ULONG                       ulDesiredW = 0, ulDesiredH = 0;
    MMP_ULONG                       ulGrabOutW = 0, ulGrabOutH = 0;
    MMP_DSC_JPEG_FMT                eJpegFmt = MMP_DSC_JPEG_FMT_FORMAT_ERROR;
    MMP_ULONG                       ulBufSize = 0;
    CamOsRet_e                      eCamOsRet = CAM_OS_OK;

    MMP_UBYTE                       ubJpdUseType = JPD_COMP_STILL_DEC;
    MMP_COMPONENT_BASE              *pJpdComp = &Component_JPD[ubJpdUseType];
    MMP_UBYTE                       ubDecSrc = JPD_COMP_DEC_SRC_FILE;
    MMP_UBYTE                       ubDecImgType = JPD_COMP_IMG_TYPE_PRIMARY;
    JPD_COMP_RESOL                  stJpdRect;
    MMP_ULONG                       ulJpdRdBufSize = m_stDscConfig.decParams.ulDscDecMaxCompBufSize;
    MMP_ULONG                       ulJpdIntBufSize = m_stDscConfig.decParams.ulDscDecMaxInbufSize;
    void                            *pvJpdRdBufVirt = NULL;
    void                            *pvJpdIntBufVirt = NULL;
    MMP_ULONG                       ulJpdRdBufAddr = 0;
    MMP_ULONG                       ulJpdIntBufAddr = 0;
    MMP_UBYTE                       ubJpdBufCount = 1;

    DIP_COMP_COLOR_FMT              eDipColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    MMP_UBYTE                       ubDipBufCount = 1;
    PIP_COMP_RECT                   stPipRect;

    if (pJpegInfo->bDecodeThumbnail) {
        return eRetErr;
    }

    /* Allocate filename buffer, MRC/INT buffer */
    eRetErr = MMPS_DSC_AllocFileNameBuf();

    MMPF_JPEGD_GetDecodeInternalBuf(&ulJpdIntBufAddr, NULL);

    if (ulJpdIntBufAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("JPD_INT", ulJpdIntBufSize, &pvJpdIntBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf((MMP_ULONG)pvJpdIntBufVirt, ulJpdIntBufSize);
    }

    MMPF_JPEGD_GetDecodeInputBuf(&ulJpdRdBufAddr, NULL);

    if (ulJpdRdBufAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("JPD_MRC", ulJpdRdBufSize, &pvJpdRdBufVirt, NULL, NULL); // TBD, File Mode Only
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInputBuf((MMP_ULONG)pvJpdRdBufVirt, ulJpdRdBufSize);
    }

    /* Get JPEG information and check information */
    if (MMPD_DSC_OpenJpegFile(pJpegInfo) != MMP_ERR_NONE) {
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_PlayOut;
    }

    if (MMPD_DSC_GetJpegInfo(pJpegInfo) != MMP_ERR_NONE) {
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_PlayOut;
    }

    eJpegFmt = pJpegInfo->ePrimaryFormat;
    ulInputW = pJpegInfo->usPrimaryWidth;
    ulInputH = pJpegInfo->usPrimaryHeight;

    ubDecImgType = JPD_COMP_IMG_TYPE_PRIMARY;

    if ((pJpegInfo->ulJpegBufAddr) && (pJpegInfo->ulJpegBufSize)) {
        ubDecSrc = JPD_COMP_DEC_SRC_MEMORY;
    }
    else {
        ubDecSrc = JPD_COMP_DEC_SRC_FILE;
    }

    if (eJpegFmt == MMP_DSC_JPEG_FMT_NOT_BASELINE) {
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_PlayOut;
    }

    /* Get DIP or Scaler format setting */
    if ((eJpegFmt >= MMP_DSC_JPEG_FMT420) &&
        (eJpegFmt <= MMP_DSC_JPEG_FMT411_V))
        eDipColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    else
        eDipColor = DIP_COMP_COLOR_FMT_UNSUPPORT;

    if (eDipColor == DIP_COMP_COLOR_FMT_UNSUPPORT) {
        MMPS_DSC_DBG_ERR(1, "DSC_PlaybackJpeg => DIP UnSupport Color\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_PlayOut;
    }

    /* Calculate DIP or Scaler scale setting */
    if (ulScalOutW == 0 && ulScalOutH == 0) { // TBD : Consider other device
        MMPS_Display_GetDevWidthHeight(MMP_DISPLAY_SEL_MAIN_LCD, &ulDesiredW, &ulDesiredH);
    }
    else {
        ulDesiredW = ulScalOutW;
        ulDesiredH = ulScalOutH;
    }

    memset(&stFitRange, 0, sizeof(MMP_SCAL_FIT_RANGE));

    stFitRange.fitmode        = MMP_SCAL_FITMODE_OPTIMAL;
    stFitRange.scalerType     = MMP_SCAL_TYPE_SCALER;
    stFitRange.ulInWidth      = ulInputW;
    stFitRange.ulInHeight     = ulInputH;
    stFitRange.ulOutWidth     = ulDesiredW;
    stFitRange.ulOutHeight    = ulDesiredH;

    stFitRange.ulInGrabX      = 1;
    stFitRange.ulInGrabY      = 1;
    stFitRange.ulInGrabW      = stFitRange.ulInWidth;
    stFitRange.ulInGrabH      = stFitRange.ulInHeight;
    stFitRange.ubChoseLit     = 1;

    MMPF_Scaler_GetGCDBestFitScale(&stFitRange, &stGrabCtl);

    ulGrabOutW = stGrabCtl.ulOutEdX - stGrabCtl.ulOutStX + 1;
    ulGrabOutH = stGrabCtl.ulOutEdY - stGrabCtl.ulOutStY + 1;

    if (gbLCDRotate) {
        ulGrabOutW = ALIGN_X(ulGrabOutW, DIP_R_COMP_ALIGN_BASE);
        ulGrabOutH = ALIGN_X(ulGrabOutH, DIP_R_COMP_ALIGN_BASE);
    }
    else {
        ulGrabOutW = ALIGN_X(ulGrabOutW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulGrabOutH = ALIGN_X(ulGrabOutH, DIP_S_COMP_WIDTH_ALIGN_BASE);
    }

    if (stFitRange.ulInGrabW * 1000 / ulGrabOutW > DIP_S_COMP_WIDTH_MAX_RATIO ||
        stFitRange.ulInGrabH * 1000 / ulGrabOutH > DIP_S_COMP_HEIGHT_MAX_RATIO) {
        m_bDscPlaybackReScale = MMP_TRUE;

        /* Update component DIP/PIP setting */
        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_JPEG_PB,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_W, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_H,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);

        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_JPEG_PB_RE_SCAL,
                                    0, 0, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_W, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_H,
                                    0, 0, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_W, DSC_PLAYBACK_DIP_1ST_SCALE_OUT_H,
                                    0, 0, ulGrabOutW, ulGrabOutH,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);
    }
    else {
        m_bDscPlaybackReScale = MMP_FALSE;

        /* Update component DIP/PIP setting */
        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_JPEG_PB,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, ulGrabOutW, ulGrabOutH,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);
    }

    if (gbLCDRotate) {
        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                    DIP_R_COMP_JPEG_PB,
                                    0, 0, ulGrabOutW, ulGrabOutH,
                                    0, 0, ulGrabOutW, ulGrabOutH,
                                    0, 0, ulGrabOutH, ulGrabOutW,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);

        stPipRect.ulX = 0;
        stPipRect.ulY = 0;
        stPipRect.ulW = ulGrabOutH;
        stPipRect.ulH = ulGrabOutW;
    }
    else {
        stPipRect.ulX = 0;
        stPipRect.ulY = 0;
        stPipRect.ulW = ulGrabOutW;
        stPipRect.ulH = ulGrabOutH;
    }

    {
        MMP_ULONG ulPipBgWidth  = (stPipRect.ulW > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : stPipRect.ulW;
        MMP_ULONG ulPipBgHeight = (stPipRect.ulH > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : stPipRect.ulH;

        MMPS_Display_SetPIPCompAttr(PIP_COMP_PLAYBACK,
                                    stPipRect.ulX, stPipRect.ulY, stPipRect.ulW, stPipRect.ulH,
                                    stPipRect.ulX, stPipRect.ulY, ulPipBgWidth, ulPipBgHeight,
                                    MMP_FALSE, MMP_FALSE);
    }

    /* Update component JPD setting */
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_SRC, (void*)&ubDecSrc);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_IMG_TYPE, (void*)&ubDecImgType);

    stJpdRect.ulStartX = 0;
    stJpdRect.ulStartY = 0;
    stJpdRect.ulWidth  = ulInputW;
    stJpdRect.ulHeight = ulInputH;
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_RES, (void*)&stJpdRect);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_COUNT, (void*)&ubJpdBufCount);

    ulBufSize = JPD_COMP_BUF_SIZE_YUV422(ALIGN16(stJpdRect.ulWidth), ALIGN16(stJpdRect.ulHeight)); // JPD always output YUV422 format
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

    if ((pJpegInfo->ulJpegBufAddr) &&
        (pJpegInfo->ulJpegBufSize) &&
        (ubDecSrc == JPD_COMP_DEC_SRC_MEMORY)) {

        MMP_ULONG ulJpgBufAddrVA  = pJpegInfo->ulJpegBufAddr;
        MMP_ULONG ulJpgBufAlignSz = ALIGN_X(pJpegInfo->ulJpegBufSize, 256);

        Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_MEM_MODE_IN_ADDR, (void*)&ulJpgBufAddrVA);
        Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_MEM_MODE_IN_SIZE, (void*)&ulJpgBufAlignSz);
    }

    /* Open Script */
    if (gbLCDRotate) {
        if (m_bDscPlaybackReScale) {
            eRetErr = OpenScript(COMPO_SCRIPT_JPG_PB_RESCALE_R);
        }
        else {
            eRetErr = OpenScript(COMPO_SCRIPT_JPG_PB_R);
        }
    }
    else {
        if (m_bDscPlaybackReScale) {
            eRetErr = OpenScript(COMPO_SCRIPT_JPG_PB_RESCALE_N);
        }
        else {
            eRetErr = OpenScript(COMPO_SCRIPT_JPG_PB_N);
        }
    }

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_DSC_DBG_ERR(1, "=> Open JPD Script Err\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        goto L_PlayOut;
    }

    /* Decode JPEG to MWC buffer */
    eRetErr = Component_JPD_TriggerEmptyBuf(ubJpdUseType);

    if (eRetErr != MMP_ERR_NONE) {
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        goto L_PlayOut;
    }

    if (ubJpdUseType == JPD_COMP_STILL_DEC) {
        eRetErr = MMPF_JPEGD_GetDecDoneStatus(&bDecDone);
        if (!bDecDone) {
            MMPS_DSC_DBG_ERR(1, "Wait DecDone TimeOut\r\n");
        }
    }

    /* Fill the m_stJpegPlayInfo structure */
    m_stJpegPlayInfo.usJpegWidth          = pJpegInfo->usPrimaryWidth;
    m_stJpegPlayInfo.usJpegHeight         = pJpegInfo->usPrimaryHeight;
    m_stJpegPlayInfo.eFitMode             = stFitRange.fitmode;
    m_stJpegPlayInfo.usScalOutWidth       = ulGrabOutW;
    m_stJpegPlayInfo.usScalOutHeight      = ulGrabOutH;
    m_stJpegPlayInfo.usDispWinOfstX       = 0;
    m_stJpegPlayInfo.usDispWinOfstY       = 0;
    m_stJpegPlayInfo.usDisplayWidth       = m_stJpegPlayInfo.usScalOutWidth;
    m_stJpegPlayInfo.usDisplayHeight      = m_stJpegPlayInfo.usScalOutHeight;
    m_stJpegPlayInfo.stJpegInfo           = *pJpegInfo;
    m_stJpegPlayInfo.eRotateType          = MMP_DISPLAY_ROTATE_NO_ROTATE;
    m_stJpegPlayInfo.bMirror              = MMP_FALSE;

L_PlayOut:

    /* Release INT/MRC Buffer */
    if (pvJpdRdBufVirt) {
        eCamOsRet = CamOsDirectMemRelease(pvJpdRdBufVirt, ulJpdRdBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInputBuf(0, 0);
    }
    if (pvJpdIntBufVirt) {
        eCamOsRet = CamOsDirectMemRelease(pvJpdIntBufVirt, ulJpdIntBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf(0, 0);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ExitJpegPlayback
//  Description : Release memory allocated by JPEG playback
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_ExitJpegPlayback(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_DSC_FreeFileNameBuf();

    if (gbLCDRotate) {
        if (m_bDscPlaybackReScale) {
            eRetErr = CloseScript(COMPO_SCRIPT_JPG_PB_RESCALE_R);
        }
        else {
            eRetErr = CloseScript(COMPO_SCRIPT_JPG_PB_R);
        }
    }
    else {
        if (m_bDscPlaybackReScale) {
            eRetErr = CloseScript(COMPO_SCRIPT_JPG_PB_RESCALE_N);
        }
        else {
            eRetErr = CloseScript(COMPO_SCRIPT_JPG_PB_N);
        }
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_PlaybackCalculatePTZ
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_PlaybackCalculatePTZ(MMP_ULONG ulZoomStep,
                                      MMP_ULONG *pulGrabX,  MMP_ULONG *pulGrabY,
                                      MMP_ULONG *pulGrabW,  MMP_ULONG *pulGrabH)
{
    const MMP_ULONG ulMaxZoomStep   = 10; //TBD
    MMP_ULONG   ulMaxZoomRatioX = 0, ulMaxZoomRatioY = 0;
    MMP_ULONG   ulZoomRatioX = 0, ulZoomRatioY = 0;
    MMP_ULONG   ulJpegW         = m_stJpegPlayInfo.usJpegWidth;
    MMP_ULONG   ulJpegH         = m_stJpegPlayInfo.usJpegHeight;
    MMP_ULONG   ulScaleOutW     = m_stJpegPlayInfo.usScalOutWidth;
    MMP_ULONG   ulScaleOutH     = m_stJpegPlayInfo.usScalOutHeight;

    ulMaxZoomRatioX = (ulJpegW * 1000) / ulScaleOutW;
    ulMaxZoomRatioY = (ulJpegH * 1000) / ulScaleOutH;

    ulZoomRatioX = 1000 + ((ulMaxZoomRatioX - 1000) * ulZoomStep) / ulMaxZoomStep;
    ulZoomRatioY = 1000 + ((ulMaxZoomRatioY - 1000) * ulZoomStep) / ulMaxZoomStep;

    *pulGrabW = (ulJpegW * 1000) / ulZoomRatioX;
    *pulGrabH = (ulJpegH * 1000) / ulZoomRatioY;

    *pulGrabX = (ulJpegW - *pulGrabW) / 2;
    *pulGrabY = (ulJpegH - *pulGrabH) / 2;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_PlaybackExecutePTZ
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_PlaybackExecutePTZ(MMP_ULONG ulGrabX, MMP_ULONG ulGrabY,
                                    MMP_ULONG ulGrabW, MMP_ULONG ulGrabH)
{
    MMP_SCAL_FIT_RANGE      stFitRange;
    MMP_SCAL_GRAB_CTRL      stGrabCtl;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMP_COMPONENT_BASE      *pDipSComp = &Component_DIP_Scale[DIP_S_COMP_JPEG_PB];
    DIP_COMP_RECT           stDipRect;

    /* Calculate the grab range of decode out image */
    memset(&stFitRange, 0, sizeof(MMP_SCAL_FIT_RANGE));

    stFitRange.fitmode        = m_stJpegPlayInfo.eFitMode;
    stFitRange.scalerType     = MMP_SCAL_TYPE_SCALER;
    stFitRange.ulInWidth      = m_stJpegPlayInfo.stJpegInfo.usPrimaryWidth;
    stFitRange.ulInHeight     = m_stJpegPlayInfo.stJpegInfo.usPrimaryHeight;
    stFitRange.ulOutWidth     = m_stJpegPlayInfo.usScalOutWidth;
    stFitRange.ulOutHeight    = m_stJpegPlayInfo.usScalOutHeight;

    stFitRange.ulInGrabX      = (ulGrabX == 0) ? (1) : (ulGrabX);
    stFitRange.ulInGrabY      = (ulGrabY == 0) ? (1) : (ulGrabY);
    stFitRange.ulInGrabW      = ulGrabW;
    stFitRange.ulInGrabH      = ulGrabH;
    stFitRange.ubChoseLit     = 1;

    if ((stFitRange.ulOutWidth > stFitRange.ulInWidth) &&
        (stFitRange.ulOutHeight > stFitRange.ulInHeight)) {

        stFitRange.ulOutWidth  = stFitRange.ulInWidth;
        stFitRange.ulOutHeight = stFitRange.ulInHeight;
    }

    MMPF_Scaler_GetGCDBestFitScale(&stFitRange, &stGrabCtl);

    /* Update component DIP or Scaler scale setting : The DIP W/H, Address must be 16x */
    stDipRect.ulX = ALIGN_X(stFitRange.ulInGrabX, DIP_S_COMP_WIDTH_ALIGN_BASE);
    stDipRect.ulY = ALIGN_X(stFitRange.ulInGrabY, DIP_S_COMP_WIDTH_ALIGN_BASE);
    stDipRect.ulW = ALIGN_X(stFitRange.ulInGrabW, DIP_S_COMP_WIDTH_ALIGN_BASE);
    stDipRect.ulH = ALIGN_X(stFitRange.ulInGrabH, DIP_S_COMP_WIDTH_ALIGN_BASE);
    Component_DIP_SetParam(pDipSComp, DIP_COMP_PARAM_SCL_CROP_RES, (void*)&stDipRect);

    /* Trigger JPEG pseudo decode done event */
    MMPF_JPEGD_TrigPseudoDecDone();

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_DecodeThumbnail
//  Description : The function decodes and playback the thumbnail picture
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_DecodeThumbnail(   MMP_DSC_JPEG_INFO *pJpegInfo,
                                    MMP_ULONG         ulScalOutW,
                                    MMP_ULONG         ulScalOutH)
{
    MMP_ERR                         eRetErr = MMP_ERR_NONE;
    MMP_BOOL                        bDecDone = MMP_FALSE;
    MMP_SCAL_FIT_RANGE              stFitRange;
    MMP_SCAL_GRAB_CTRL              stGrabCtl;
    MMP_ULONG                       ulInputW = 0, ulInputH = 0;
    MMP_ULONG                       ulDesiredW = 0, ulDesiredH = 0;
    MMP_ULONG                       ulGrabOutW = 0, ulGrabOutH = 0;
    MMP_DSC_JPEG_FMT                eJpegFmt = MMP_DSC_JPEG_FMT_FORMAT_ERROR;
    MMP_ULONG                       ulBufSize = 0;
    CamOsRet_e                      eCamOsRet = CAM_OS_OK;

    MMP_UBYTE                       ubJpdUseType = JPD_COMP_STILL_DEC;
    MMP_COMPONENT_BASE              *pJpdComp = &Component_JPD[ubJpdUseType];
    MMP_UBYTE                       ubDecSrc = JPD_COMP_DEC_SRC_FILE;
    MMP_UBYTE                       ubDecImgType = JPD_COMP_IMG_TYPE_PRIMARY;
    JPD_COMP_RESOL                  stJpdRect;
    MMP_ULONG                       ulJpdRdBufSize = m_stDscConfig.decParams.ulDscDecMaxCompBufSize;
    MMP_ULONG                       ulJpdIntBufSize = m_stDscConfig.decParams.ulDscDecMaxInbufSize;
    void                            *pvJpdRdBufVirt = NULL;
    void                            *pvJpdIntBufVirt = NULL;
    MMP_ULONG                       ulJpdRdBufAddr = 0;
    MMP_ULONG                       ulJpdIntBufAddr = 0;
    MMP_UBYTE                       ubJpdBufCount = 1;

    MMP_UBYTE                       ubJpeUseType = JPE_COMP_PRM_THUMB; // TBD
    MMP_COMPONENT_BASE              *pJpeComp = &Component_JPE[ubJpeUseType];
    MMPS_DSC_CAPTURE_INFO           stDscCaptInfo;
    MMP_UBYTE                       ubRcIdx = MMP_JPGENC_RC_ID_PRM_CAPTURE;

    DIP_COMP_COLOR_FMT              eDipColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    MMP_UBYTE                       ubDipBufCount = 1;

    if (!pJpegInfo->bDecodeThumbnail) {
        return eRetErr;
    }

    /* Allocate filename buffer, MRC/INT buffer */
    eRetErr = MMPS_DSC_AllocFileNameBuf();

    MMPF_JPEGD_GetDecodeInternalBuf(&ulJpdIntBufAddr, NULL);

    if (ulJpdIntBufAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("JPD_INT", ulJpdIntBufSize, &pvJpdIntBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf((MMP_ULONG)pvJpdIntBufVirt, ulJpdIntBufSize);
    }

    MMPF_JPEGD_GetDecodeInputBuf(&ulJpdRdBufAddr, NULL);

    if (ulJpdRdBufAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("JPD_MRC", ulJpdRdBufSize, &pvJpdRdBufVirt, NULL, NULL); // TBD, File Mode Only
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInputBuf((MMP_ULONG)pvJpdRdBufVirt, ulJpdRdBufSize);
    }

    /* Get JPEG information and check information */
    eRetErr = MMPD_DSC_OpenJpegFile(pJpegInfo);
    if (eRetErr) {
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_DecThumbOut;
    }

    if (pJpegInfo->bDecVRThumb) {
        pJpegInfo->bDecPrm2Thumb = MMP_FALSE;
    }
    else {
        eRetErr = MMPD_DSC_GetJpegInfo(pJpegInfo);
        if (eRetErr == MMP_DSC_ERR_EXIF_NO_THUMBNAIL) {
            pJpegInfo->bDecPrm2Thumb = MMP_TRUE;
        }
        else if (eRetErr) {
            pJpegInfo->bDecPrm2Thumb = MMP_FALSE;
            MMPD_DSC_CloseJpegFile(pJpegInfo);
            eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
            goto L_DecThumbOut;
        }
        else {
            pJpegInfo->bDecPrm2Thumb = MMP_FALSE;
        }
    }

    if ((pJpegInfo->bDecVRThumb) && (pJpegInfo->ulJpegBufAddr) && (pJpegInfo->ulJpegBufSize)) {
        // Video Browser VR Thumb Case
        eJpegFmt = pJpegInfo->ePrimaryFormat;   // This parameter is get from AHC
        ulInputW = pJpegInfo->usPrimaryWidth;   // This parameter is get from AHC
        ulInputH = pJpegInfo->usPrimaryHeight;  // This parameter is get from AHC

        ubDecImgType = JPD_COMP_IMG_TYPE_PRIMARY;
        ubDecSrc = JPD_COMP_DEC_SRC_MEMORY;
    }
    else {
        // Photo Browser Case
        if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE) {
            eJpegFmt = pJpegInfo->eThumbFormat;
            ulInputW = pJpegInfo->usThumbWidth;
            ulInputH = pJpegInfo->usThumbHeight;

            ubDecImgType = JPD_COMP_IMG_TYPE_THUMB;
            ubDecSrc = JPD_COMP_DEC_SRC_FILE;
        }
        else {
            pJpegInfo->bDecodeThumbnail = MMP_FALSE;
            eRetErr = MMPD_DSC_GetJpegInfo(pJpegInfo);
            if (eRetErr) {
                MMPS_DSC_DBG_ERR(1, "DecPrm2Thumb GetJpegInfo Fail\r\n");
            }

            eJpegFmt = pJpegInfo->ePrimaryFormat;
            ulInputW = pJpegInfo->usPrimaryWidth;
            ulInputH = pJpegInfo->usPrimaryHeight;

            ubDecImgType = JPD_COMP_IMG_TYPE_PRIMARY;
            ubDecSrc = JPD_COMP_DEC_SRC_FILE;
        }
    }

    if (ulInputW == 0 || ulInputH == 0) {
        MMPS_DSC_DBG_ERR(1, "DecodeThumbnail => W/H Zero\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_DecThumbOut;
    }

    if (eJpegFmt == MMP_DSC_JPEG_FMT_NOT_BASELINE) {
        MMPS_DSC_DBG_ERR(1, "DecodeThumbnail => Fmt Wrong\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_DecThumbOut;
    }

    /* Get DIP or Scaler format setting */
    if ((eJpegFmt >= MMP_DSC_JPEG_FMT420) &&
        (eJpegFmt <= MMP_DSC_JPEG_FMT411_V))
        eDipColor = DIP_COMP_COLOR_FMT_YUV422_YUYV;
    else
        eDipColor = DIP_COMP_COLOR_FMT_UNSUPPORT;

    if (eDipColor == DIP_COMP_COLOR_FMT_UNSUPPORT) {
        MMPS_DSC_DBG_ERR(1, "DecodeThumbnail => DIP UnSupport Color\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_DecThumbOut;
    }

    /* Calculate DIP or Scaler scale setting */
    if (ulScalOutW == 0 && ulScalOutH == 0) { // TBD : Consider other device
        MMPS_Display_GetDevWidthHeight(MMP_DISPLAY_SEL_MAIN_LCD, &ulDesiredW, &ulDesiredH);
    }
    else {
        ulDesiredW = ulScalOutW;
        ulDesiredH = ulScalOutH;
    }

    memset(&stFitRange, 0, sizeof(MMP_SCAL_FIT_RANGE));

    stFitRange.fitmode        = MMP_SCAL_FITMODE_OPTIMAL;
    stFitRange.scalerType     = MMP_SCAL_TYPE_SCALER;
    stFitRange.ulInWidth      = ulInputW;
    stFitRange.ulInHeight     = ulInputH;
    stFitRange.ulOutWidth     = ulDesiredW;
    stFitRange.ulOutHeight    = ulDesiredH;

    stFitRange.ulInGrabX      = 1;
    stFitRange.ulInGrabY      = 1;
    stFitRange.ulInGrabW      = stFitRange.ulInWidth;
    stFitRange.ulInGrabH      = stFitRange.ulInHeight;
    stFitRange.ubChoseLit     = 1;

    MMPF_Scaler_GetGCDBestFitScale(&stFitRange, &stGrabCtl);

    ulGrabOutW = stGrabCtl.ulOutEdX - stGrabCtl.ulOutStX + 1;
    ulGrabOutH = stGrabCtl.ulOutEdY - stGrabCtl.ulOutStY + 1;

    if (gbLCDRotate) {
        ulGrabOutW = ALIGN_X(ulGrabOutW, DIP_R_COMP_ALIGN_BASE);
        ulGrabOutH = ALIGN_X(ulGrabOutH, DIP_R_COMP_ALIGN_BASE);
    }
    else {
        ulGrabOutW = ALIGN_X(ulGrabOutW, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulGrabOutH = ALIGN_X(ulGrabOutH, DIP_S_COMP_WIDTH_ALIGN_BASE);
    }

    /* Update DIP component setting */
    if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE) {

        if (pJpegInfo->bReEncodeThumb) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_THUMB_SCL,
                                        0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                        0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                        0, 0, ulGrabOutW, ulGrabOutH,
                                        eDipColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV, // For Encode JPEG with NV12 Format
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);
        }
        else {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_THUMB_SCL,
                                        0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                        0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                        0, 0, ulGrabOutW, ulGrabOutH,
                                        eDipColor,
                                        eDipColor,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);

            if (gbLCDRotate) {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                            DIP_R_COMP_THUMB_ROT,
                                            0, 0, ulGrabOutW, ulGrabOutH,
                                            0, 0, ulGrabOutW, ulGrabOutH,
                                            0, 0, ulGrabOutH, ulGrabOutW,
                                            eDipColor,
                                            eDipColor,
                                            DIP_COMP_MIRROR_DIS,
                                            0,
                                            ubDipBufCount);
            }
        }
    }
    else {
        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_THUMB_SCL_PRE,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, stFitRange.ulInGrabW, stFitRange.ulInGrabH,
                                    0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);

        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_THUMB_SCL,
                                    0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                    0, 0, THUMB_DIP_1ST_SCALE_OUT_W, THUMB_DIP_1ST_SCALE_OUT_H,
                                    0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                    eDipColor,
                                    eDipColor,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    ubDipBufCount);

        if (pJpegInfo->bReEncodeThumb) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_THUMB_SCL_POST,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                        0, 0, ulGrabOutW, ulGrabOutH,
                                        eDipColor,
                                        DIP_COMP_COLOR_FMT_YUV420_UV, // For Encode JPEG with NV12 Format
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        ubDipBufCount);
        }
        else {
            /* Update component DIP Rotate setting for Vertical Panel */
            if (gbLCDRotate) {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                            DIP_R_COMP_THUMB_ROT,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_H, THUMB_DIP_2ND_SCALE_OUT_W,
                                            eDipColor,
                                            eDipColor,
                                            DIP_COMP_MIRROR_DIS,
                                            0,
                                            ubDipBufCount);

                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            DIP_S_COMP_THUMB_SCL_POST,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_H, THUMB_DIP_2ND_SCALE_OUT_W,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_H, THUMB_DIP_2ND_SCALE_OUT_W,
                                            0, 0, ulGrabOutH, ulGrabOutW,
                                            eDipColor,
                                            eDipColor,
                                            DIP_COMP_MIRROR_DIS,
                                            0,
                                            ubDipBufCount);
            }
            else {
                MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                            DIP_S_COMP_THUMB_SCL_POST,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                            0, 0, THUMB_DIP_2ND_SCALE_OUT_W, THUMB_DIP_2ND_SCALE_OUT_H,
                                            0, 0, ulGrabOutW, ulGrabOutH,
                                            eDipColor,
                                            eDipColor,
                                            DIP_COMP_MIRROR_DIS,
                                            0,
                                            ubDipBufCount);
            }
        }
    }

    /* Update component JPD setting */
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_SRC, (void*)&ubDecSrc);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_DEC_IMG_TYPE, (void*)&ubDecImgType);

    stJpdRect.ulStartX = 0;
    stJpdRect.ulStartY = 0;
    stJpdRect.ulWidth  = ulInputW;
    stJpdRect.ulHeight = ulInputH;
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_RES, (void*)&stJpdRect);
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_COUNT, (void*)&ubJpdBufCount);

    ulBufSize = JPD_COMP_BUF_SIZE_YUV422(ALIGN16(stJpdRect.ulWidth), ALIGN16(stJpdRect.ulHeight)); // JPD always output YUV422 format
    Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

    if ((pJpegInfo->ulJpegBufAddr) &&
        (pJpegInfo->ulJpegBufSize) &&
        (ubDecSrc == JPD_COMP_DEC_SRC_MEMORY)) {

        MMP_ULONG ulJpgBufAddrVA  = pJpegInfo->ulJpegBufAddr;
        MMP_ULONG ulJpgBufAlignSz = ALIGN_X(pJpegInfo->ulJpegBufSize, 256);

        Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_MEM_MODE_IN_ADDR, (void*)&ulJpgBufAddrVA);
        Component_JPD_SetParam(pJpdComp, JPD_COMP_PARAM_MEM_MODE_IN_SIZE, (void*)&ulJpgBufAlignSz);
    }

    /* Update component JPE setting */
    if (pJpegInfo->bReEncodeThumb) {

        stDscCaptInfo.usPrimaryW     = ulGrabOutW;
        stDscCaptInfo.usPrimaryH     = ulGrabOutH;
        stDscCaptInfo.usThumbWidth   = 0;
        stDscCaptInfo.usThumbHeight  = 0;

        stDscCaptInfo.stQualityCtl.bTargetCtl      = MMP_TRUE;
        stDscCaptInfo.stQualityCtl.bLimitCtl       = MMP_FALSE;
        stDscCaptInfo.stQualityCtl.ulTargetSize    = 200;
        stDscCaptInfo.stQualityCtl.ulLimitSize     = 0;
        stDscCaptInfo.stQualityCtl.usMaxTrialCnt   = 1;
        stDscCaptInfo.stQualityCtl.ubQualitySel    = MMP_JPGENC_RC_QUALITY_SEL_HIGH;

        stDscCaptInfo.bCaptureEn    = MMP_TRUE;
        stDscCaptInfo.bExifEn       = MMP_FALSE;
        stDscCaptInfo.bThumbnailEn  = MMP_FALSE;
        stDscCaptInfo.bFirstShot    = MMP_TRUE;
        stDscCaptInfo.ubShotMode    = JPE_COMP_SINGLE_SHOT;
        stDscCaptInfo.usMaxShotNum  = 1;
        stDscCaptInfo.ubUiMode      = JPE_COMP_UI_MODE_BROWSER;
        stDscCaptInfo.ubCamSel      = PRM_SENSOR;
        stDscCaptInfo.ubRawFmt      = JPE_COMP_FMT_NV12;
        stDscCaptInfo.usReviewTime  = 0;
        stDscCaptInfo.usWindowsTime = 0;

        /* Set capture attributes */
        eRetErr = MMPS_DSC_SetJpeUIMode(ubJpeUseType, stDscCaptInfo.ubUiMode);

        eRetErr = MMPS_DSC_SetShotMode(ubJpeUseType, stDscCaptInfo.ubShotMode);
        eRetErr = MMPS_DSC_SetMaxShotNum(ubJpeUseType, stDscCaptInfo.usMaxShotNum);

        eRetErr = MMPS_DSC_SetJpegEncResol( ubJpeUseType,
                                            stDscCaptInfo.usPrimaryW, stDscCaptInfo.usPrimaryH);

        eRetErr = MMPS_DSC_SetCaptureJpegQuality(   ubRcIdx,
                                                    stDscCaptInfo.stQualityCtl.bTargetCtl,
                                                    stDscCaptInfo.stQualityCtl.bLimitCtl,
                                                    stDscCaptInfo.stQualityCtl.ulTargetSize,
                                                    stDscCaptInfo.stQualityCtl.ulLimitSize,
                                                    stDscCaptInfo.stQualityCtl.usMaxTrialCnt,
                                                    stDscCaptInfo.stQualityCtl.ubQualitySel);

        /* Calculate JPE buffer attribute */
        MMPS_DSC_CalculateJpeOBufAttr(ubJpeUseType, MMP_FALSE);
    }

    /* Open Srcipt */
    if (pJpegInfo->bReEncodeThumb) {
        if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
            eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_REENCODE);
        else
            eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_REENCODE);
    }
    else {
        if (gbLCDRotate) {
            if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
                eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_R);
            else
                eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_R);
        }
        else {
            if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
                eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_N);
            else
                eRetErr = OpenScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_N);
        }
    }

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_DSC_DBG_ERR(1, "=> Open JPD Script Err\r\n");
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        goto L_DecThumbOut;
    }

    /* Decode JPEG to MWC buffer */
    eRetErr = Component_JPD_TriggerEmptyBuf(ubJpdUseType);

    if (eRetErr != MMP_ERR_NONE) {
        MMPD_DSC_CloseJpegFile(pJpegInfo);
        goto L_DecThumbOut;
    }

    if (ubJpdUseType == JPD_COMP_STILL_DEC) {
        eRetErr = MMPF_JPEGD_GetDecDoneStatus(&bDecDone);
        if (!bDecDone) {
            MMPS_DSC_DBG_ERR(1, "Wait DecDone TimeOut\r\n");
        }
    }

    if (pJpegInfo->bReEncodeThumb) {

        /* Get the address and size of JPEG */
        MMPF_JPGENC_GetJpegSize(ubRcIdx, &(stDscCaptInfo.ulPrimaryJpgSize));
        MMPF_JPGENC_GetJpegBitBufAttr(ubRcIdx, &(stDscCaptInfo.ulPrimaryJpgAddr), NULL);
        MMPF_JPGENC_GetJpegStampInfo(ubRcIdx, &(stDscCaptInfo.stDateTime));

        pJpegInfo->ulReEncodeThumbAddr = stDscCaptInfo.ulPrimaryJpgAddr;
        pJpegInfo->ulReEncodeThumbSize = stDscCaptInfo.ulPrimaryJpgSize;
    }

L_DecThumbOut:

    /* Release INT/MRC Buffer */
    if (pvJpdRdBufVirt) {
        eCamOsRet = CamOsDirectMemRelease(pvJpdRdBufVirt, ulJpdRdBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInputBuf(0, 0);
    }
    if (pvJpdIntBufVirt) {
        eCamOsRet = CamOsDirectMemRelease(pvJpdIntBufVirt, ulJpdIntBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf(0, 0);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ExitThumbReEncodeMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_ExitThumbReEncodeMode(MMP_DSC_JPEG_INFO *pJpegInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
        eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_REENCODE);
    else
        eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_REENCODE);

    MMPS_DSC_FreeFileNameBuf();

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ExitThumbDecodeMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_ExitThumbDecodeMode(MMP_DSC_JPEG_INFO *pJpegInfo)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if (gbLCDRotate) {
        if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
            eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_R);
        else
            eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_R);
    }
    else {
        if (pJpegInfo->bDecPrm2Thumb == MMP_FALSE)
            eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PURE_THUMB_N);
        else
            eRetErr = CloseScript(COMPO_SCRIPT_BROWSER_DSC_PRM2THUMB_N);
    }

    MMPS_DSC_FreeFileNameBuf();

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetJpegInfo
//  Description : Get the JPEG information
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_GetJpegInfo(MMP_DSC_JPEG_INFO *pstJpegInfo)
{
    MMP_ULONG   ulJpdIntBufSize = m_stDscConfig.decParams.ulDscDecMaxInbufSize;
    void        *pvJpdIntBufVirt = NULL;
    MMP_ULONG   ulJpdIntBufAddr = 0;
    MMP_USHORT  usExifNodeId = EXIF_NODE_ID_PRIMARY; // TBD
    CamOsRet_e  eCamOsRet = CAM_OS_OK;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_DSC_AllocFileNameBuf();

    eRetErr = _MMPS_DSC_AllocExifDecWorkingBuf(usExifNodeId, MMP_FALSE);

    MMPF_JPEGD_GetDecodeInternalBuf(&ulJpdIntBufAddr, NULL);

    if (ulJpdIntBufAddr == 0) {
        eCamOsRet = CamOsDirectMemAlloc("JPD_INT", ulJpdIntBufSize, &pvJpdIntBufVirt, NULL, NULL);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf((MMP_ULONG)pvJpdIntBufVirt, ulJpdIntBufSize);
    }

    eRetErr = MMPD_DSC_OpenJpegFile(pstJpegInfo);
    if (eRetErr) {
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_GetInfoOut;
    }

    eRetErr = MMPD_DSC_GetJpegInfo(pstJpegInfo);
    if (eRetErr == MMP_DSC_ERR_EXIF_NO_THUMBNAIL) {
        MMPD_DSC_CloseJpegFile(pstJpegInfo);
        eRetErr = MMP_DSC_ERR_EXIF_NO_THUMBNAIL;
        goto L_GetInfoOut;
    }
    else if (eRetErr) {
        MMPD_DSC_CloseJpegFile(pstJpegInfo);
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_GetInfoOut;
    }

    eRetErr = MMPD_DSC_CloseJpegFile(pstJpegInfo);
    if (eRetErr) {
        eRetErr = MMP_DSC_ERR_JPEGINFO_FAIL;
        goto L_GetInfoOut;
    }

L_GetInfoOut:

    if (pvJpdIntBufVirt) {
        eCamOsRet = CamOsDirectMemRelease(pvJpdIntBufVirt, ulJpdIntBufSize);
        CAM_OS_RET_CHK(eCamOsRet);
        MMPF_JPEGD_SetDecodeInternalBuf(0, 0);
    }

    _MMPS_DSC_FreeExifDecWorkingBuf(usExifNodeId, MMP_FALSE);

    MMPS_DSC_FreeFileNameBuf();

    if (eRetErr)
        return eRetErr;
    else
        return MMP_ERR_NONE;
}

#if 0
void _____Exif_Functions_____(){}
#endif

#if (DSC_SUPPORT_BASELINE_MP_FILE)
//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_EnableMultiPicFormat
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_EnableMultiPicFormat(MMP_BOOL bEnableMpf, MMP_BOOL bEnableLargeThumb)
{
    m_bMultiPicFormatEnable = bEnableMpf;
    m_bEncLargeThumbEnable  = bEnableLargeThumb;

    MMPF_MPF_EnableMpf(bEnableMpf);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ConfigLargeThumbRes
//  Description : The primary Jpeg width/height need to configurate first.
//------------------------------------------------------------------------------
/** @brief The function set the thumbnail width and height
@param[in] ulThumbWidth   The large thumbnail widht
@param[in] ulThumbHeight  The large thumbnail height

@return MMP_ERR_NONE.
*/
MMP_ERR MMPS_DSC_ConfigLargeThumbRes(MMP_UBYTE ubResMode)
{
    MMP_USHORT  usGCD = 0;
    MMP_ULONG   ulRatioH, ulRatioV;

    m_ubLargeThumbResMode = ubResMode;

    /* Calculate Jpeg ratio */
    usGCD = Greatest_Common_Divisor(m_usStillJpegWidth[], m_usStillJpegHeight[]);

    ulRatioH = m_usStillJpegWidth[] / usGCD;
    ulRatioV = m_usStillJpegHeight[] / usGCD;

    /* Calculate Large Thumbnail resolution */
    if (m_ubLargeThumbResMode == MMP_DSC_LARGE_THUMB_RES_FHD)
    {
        if (m_usStillJpegWidth[] >= m_usStillJpegHeight[]) {
            m_ulLargeThumbHeight    = 1080;
            m_ulLargeThumbWidth     = (m_ulLargeThumbHeight / ulRatioV) * ulRatioH;
        }
        else {
            // TBD
        }
    }
    else if (m_ubLargeThumbResMode == MMP_DSC_LARGE_THUMB_RES_VGA)
    {
        if (m_usStillJpegWidth[] >= m_usStillJpegHeight[]) {
            m_ulLargeThumbHeight    = 480;
            m_ulLargeThumbWidth     = (m_ulLargeThumbHeight / ulRatioV) * ulRatioH;
        }
        else {
            // TBD
        }
    }
    else {
        MMPS_DSC_DBG_ERR(1, "Wrong Large Thumbnail Mode\r\n");
    }

    return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_OpenEXIFFile
//  Description :
//------------------------------------------------------------------------------
/** @brief The function open exif file

The function open jpeg file for getting exif info

@param[in] pubFileName image file name
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_OpenEXIFFile(MMP_UBYTE *pubFileName, MMP_USHORT usExifNodeId)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_ULONG   ulFileNameLen = 0;

    eRetErr = MMPS_DSC_AllocFileNameBuf();

    eRetErr = _MMPS_DSC_AllocExifDecWorkingBuf(usExifNodeId, MMP_FALSE);

    ulFileNameLen = strlen((MMP_BYTE *)pubFileName);

    eRetErr = MMPD_DSC_OpenEXIFFile(pubFileName, ulFileNameLen, usExifNodeId);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_UpdateExifNode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function will update exif memory

The function will update exif memory which is pre-set by MMPS_DSC_SetExifWorkingBuffer

@param[in] pData the update data buffer
@param[in] ulDataSize update data size
@param[in] usTag the tag id for update or add
@param[in] usIfd the ifd id for update
usIfd = 0 Modify IFD0 TAG
usIfd = 1 Modify IFD1 TAG
usIfd = 2 Modify GPS TAG
usIfd = 3 Modify EXIF TAG
@param[in] usType updated tag data type
@param[in] ulCount updated tag data count
@param[in] bFotUpdate update the exif update buffer or capture buffer
@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_UpdateExifNode(MMP_USHORT    usExifNodeId,
                                MMP_USHORT    usIfd,  MMP_USHORT  usTag,
                                MMP_USHORT    usType, MMP_ULONG   ulCount,
                                MMP_UBYTE     *pData, MMP_ULONG   ulDataSize,
                                MMP_BOOL      bForUpdate)
{
    return MMPD_DSC_UpdateExifNode(usExifNodeId, usIfd, usTag, usType, ulCount, pData, ulDataSize, bForUpdate);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetImageEXIFInfo
//  Description :
//------------------------------------------------------------------------------
/** @brief The function get image exif info

The function get image exif info by ifd and tag id and return data size

@param[in]  usIfd   The IFD index of tag field
@param[in]  usTag   The ID of tag field
@param[out] pulSize The data size of image EXIF info
@param[out] pData   The data of image EXIF info

@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_GetImageEXIFInfo(MMP_USHORT usExifNodeId, MMP_USHORT usIfd, MMP_USHORT usTag, MMP_UBYTE *pData, MMP_ULONG *pulSize)
{
    return MMPF_DSC_GetEXIFInfo(usExifNodeId, usIfd, usTag, pData, pulSize);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_CloseEXIFFile
//  Description : The function close Exif file
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_CloseEXIFFile(MMP_USHORT usExifNodeId)
{
    _MMPS_DSC_FreeExifDecWorkingBuf(usExifNodeId, MMP_FALSE);

    MMPF_DSC_CloseEXIFFile(usExifNodeId);

    MMPS_DSC_FreeFileNameBuf();

    return MMP_ERR_NONE;
}

#if (EXIF_MANUAL_UPDATE)
//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_GetImageEXIF
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_DSC_GetImageEXIF(MMP_ULONG ulIndex, MMPS_DSC_EXIF_CONFIG *pOutExif)
{
    MMPS_DSC_EXIF_CONFIG    *pExif = NULL;
    MMP_ULONG               ulTemp = 0;
    MMP_ULONG               ulArrayEnd = (MMP_ULONG)m_ubExifSettingArray + EXIF_CONFIG_ARRAY_SIZE;
    MMP_ULONG               i = 0;

    pOutExif->Data = NULL;

    ulTemp = ALIGN4((MMP_ULONG)m_ubExifSettingArray);
    pExif  = (MMPS_DSC_EXIF_CONFIG*)(ulTemp);

    for(;;) {

        if (pExif->AtomSize != 0) {

            if (i >= ulIndex)
                break;

            pExif = (MMPS_DSC_EXIF_CONFIG*)((MMP_ULONG)pExif + pExif->AtomSize);

            i++;
        }
        else {
            return MMP_FALSE;
        }

        if (((MMP_ULONG)pExif) >= ulArrayEnd) {
            return MMP_FALSE;
        }
    }

    pOutExif->DataSize     = pExif->DataSize;
    pOutExif->TagID        = pExif->TagID;
    pOutExif->IfdID        = pExif->IfdID;
    pOutExif->TagType      = pExif->TagType;
    pOutExif->TagDataSize  = pExif->TagDataSize;
    pOutExif->Data         = (MMP_UBYTE*)((MMP_ULONG)pExif + sizeof(MMPS_DSC_EXIF_CONFIG) - 4);

    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_SetImageEXIF
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL MMPS_DSC_SetImageEXIF( MMP_UBYTE   *pData,
                                MMP_ULONG   ulDataSize,
                                MMP_USHORT  usIfdIdx,
                                MMP_USHORT  usTagID,
                                MMP_USHORT  usType,
                                MMP_USHORT  usCount)
{
    MMP_ERR                 error = MMP_ERR_NONE;
    MMPS_DSC_EXIF_CONFIG    *pExif = NULL;
    MMP_ULONG               ulTemp = 0;
    MMP_BOOL                bUpdate = MMP_FALSE;
    MMP_ULONG               ulArrayEnd = (MMP_ULONG)m_ubExifSettingArray + EXIF_CONFIG_ARRAY_SIZE;
    MMP_ULONG               ulAtomLen = 0;

    if (pData == NULL) {
        return MMP_FALSE;
    }

    if (EXIF_TYPE_ASCII == usType) {
        if (ulDataSize > 256) {
            return MMP_FALSE;
        }
    }

    ulTemp = ALIGN4((MMP_ULONG)m_ubExifSettingArray);
    pExif = (MMPS_DSC_EXIF_CONFIG*)(ulTemp);

    if (EXIF_TYPE_ASCII == usType) {
        ulAtomLen = ALIGN4(EXIF_ASCII_LENGTH + sizeof(MMPS_DSC_EXIF_CONFIG) - 4);
    }
    else {
        ulAtomLen = ALIGN4(ulDataSize + sizeof(MMPS_DSC_EXIF_CONFIG) - 4);
    }

    for(;;) {
        if (pExif->AtomSize != 0) {
            if ((pExif->TagID == usTagID) && (pExif->IfdID == usIfdIdx)) {
                bUpdate = MMP_TRUE;
                break;
            }

            pExif = (MMPS_DSC_EXIF_CONFIG*)((MMP_ULONG)pExif + pExif->AtomSize);
        }
        else {
            break;
        }

        if (((MMP_ULONG)pExif + ulAtomLen) >= ulArrayEnd) {
            return MMP_FALSE;
        }
    }

    if (EXIF_TYPE_ASCII == usType) {
        pExif->AtomSize = ALIGN4(EXIF_ASCII_LENGTH + sizeof(MMPS_DSC_EXIF_CONFIG) - 4);
    }
    else {
        pExif->AtomSize = ALIGN4(ulDataSize + sizeof(MMPS_DSC_EXIF_CONFIG) - 4);
    }

    pExif->DataSize      = ulDataSize;
    pExif->TagID         = usTagID;
    pExif->IfdID         = usIfdIdx;
    pExif->TagType       = usType;
    pExif->TagDataSize   = usCount;
    pExif->Data          = (MMP_UBYTE*)pExif + sizeof(MMPS_DSC_EXIF_CONFIG) - 4;

    memcpy(pExif->Data, pData, ulDataSize);

    if (!bUpdate) {
        pExif = (MMPS_DSC_EXIF_CONFIG*)((MMP_ULONG)pExif + pExif->AtomSize);
        pExif->AtomSize = 0;
    }

    return (error == MMP_ERR_NONE)? MMP_TRUE : MMP_FALSE;
}
#endif

#if 0
void _____Storage_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_JpegDram2Card
//  Description :
//------------------------------------------------------------------------------
/** @brief The function saved Jpeg data from DRAM to card

@param[in] pDscCaptInfo the capture file name and filename length information.

@return It reports the status of the operation.
*/
MMP_ERR MMPS_DSC_JpegDram2Card(MMPS_DSC_CAPTURE_INFO *pDscCaptInfo)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_BOOL    bEnableExtraBuf = MMP_FALSE;

    if (MMP_JPEG_ENC_StartStoreCardCallback != NULL) {
        MMP_JPEG_ENC_StartStoreCardCallback(pDscCaptInfo);
    }

    if (pDscCaptInfo->ulExtraBufAddr != 0)
        bEnableExtraBuf = MMP_TRUE;
    else
        bEnableExtraBuf = MMP_FALSE;

    MMPD_DSC_SetFileName(pDscCaptInfo->bFileName, pDscCaptInfo->ulFileNameLen);

    if (pDscCaptInfo->bExifEn) {

        // EXIF header
        eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulExifHdrAddr,
                                         pDscCaptInfo->ulExifHdrSize,
                                         MMP_TRUE, MMP_FALSE);

        if (eRetErr != MMP_ERR_NONE) {
            MMPS_DSC_DBG_ERR(1, "MMPF_DSC_JpegDram2Card-1 ERR[%x]\r\n", eRetErr);
            eRetErr = MMP_DSC_ERR_SAVE_CARD_FAIL;
            goto L_StoreOut;
        }

        // Thumbnail
        if (pDscCaptInfo->bThumbnailEn) {
            eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulThumbnailAddr,
                                             pDscCaptInfo->ulThumbnailSize,
                                             MMP_FALSE, MMP_FALSE);
        }

        if (eRetErr == MMP_ERR_NONE) {

            #if (DSC_SUPPORT_BASELINE_MP_FILE)
            if (m_bMultiPicFormatEnable)
            {
                eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulMpfDataStartAddr,
                                                 pDscCaptInfo->ulMpfDataSize,
                                                 MMP_FALSE, MMP_FALSE);

                // Primary JPEG, skip SOI marker
                eRetErr =  MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulPrimaryJpgAddr + 2,
                                                  pDscCaptInfo->ulPrimaryJpgSize,
                                                  MMP_FALSE, MMP_FALSE);

                if (m_bEncLargeThumbEnable) {

                    // Large Thumbnail with its Exif
                    eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulLargeThumbExifAddr,
                                                     pDscCaptInfo->ulLargeThumbExifSize,
                                                     MMP_FALSE, MMP_FALSE);

                    // Large Thumbnail, skip SOI marker
                    eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulLargeThumbJpegAddr + 2,
                                                     pDscCaptInfo->ulLargeThumbJpegSize,
                                                     MMP_FALSE, !bEnableExtraBuf);
                }
            }
            else
            #endif
            {
                // Primary JPEG, skip SOI marker
                eRetErr =  MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulPrimaryJpgAddr + 2,
                                                  pDscCaptInfo->ulPrimaryJpgSize,
                                                  MMP_FALSE, !bEnableExtraBuf);
            }
        }
        else {
            MMPS_DSC_DBG_ERR(1, "MMPF_DSC_JpegDram2Card-2 ERR[%x]\r\n", eRetErr);
            eRetErr = MMP_DSC_ERR_SAVE_CARD_FAIL;
            goto L_StoreOut;
        }
    }
    else
    {
        // Primary JPEG
        eRetErr =  MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulPrimaryJpgAddr,
                                          pDscCaptInfo->ulPrimaryJpgSize,
                                          MMP_TRUE, !bEnableExtraBuf);

        if (eRetErr != MMP_ERR_NONE) {
            MMPS_DSC_DBG_ERR(1, "MMPF_DSC_JpegDram2Card-3 ERR[%x]\r\n", eRetErr);
            eRetErr = MMP_DSC_ERR_SAVE_CARD_FAIL;
            goto L_StoreOut;
        }
    }

    if (bEnableExtraBuf) {
        eRetErr = MMPF_DSC_JpegDram2Card(pDscCaptInfo->ulExtraBufAddr, pDscCaptInfo->ulExtraBufSize, MMP_FALSE, MMP_TRUE);
    }

L_StoreOut:

    if (MMP_JPEG_ENC_EndStoreCardCallback != NULL) {
        MMP_JPEG_ENC_EndStoreCardCallback(pDscCaptInfo);
    }

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_DSC_ThumbDram2Card
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_DSC_ThumbDram2Card(MMPS_DSC_CAPTURE_INFO *pDscCaptInfo, MMP_ULONG ulStreamType)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    eRetErr = MMPD_DSC_SetThumbFileName(pDscCaptInfo->bFileName, pDscCaptInfo->ulFileNameLen);

    eRetErr = MMPF_VIDENC_StoreVRThumbToCard(ulStreamType);

    if (eRetErr != MMP_ERR_NONE) {
        MMPS_DSC_DBG_ERR(1, "MMPS_DSC_ThumbDram2Card ERR[%x]\r\n", eRetErr);
        eRetErr = MMP_DSC_ERR_SAVE_CARD_FAIL;
    }

    return eRetErr;
}

#endif //#if defined(ALL_FW)

/// @}
