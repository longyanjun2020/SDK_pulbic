/**
 *  @file mmps_vidplay.c
 *  @brief The 3GP playback control functions
 *  @author Truman Yang
 *  @author Philip Lin
 *  @version 1.1 28-Jun-06 Implement the MMPS functions. Use IPC section, and use simple config functions.
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "lib_retina.h"
#include "mmps_display.h"
#include "mmps_system.h"
#include "mmps_vidplay.h"
#include "mmps_dsc.h"
#include "mmps_fs.h"
#include "mmpd_system.h"
#include "mmpd_fctl.h"
#include "mmpd_3gpparser.h"
#include "mmpd_aviparser.h"
#include "mmpd_mkvparser.h"
#include "mmpd_rmparser.h"
#include "mmpd_mp4vdec.h"
#include "mmpd_tsparser.h"
#include "mmpd_vidplayer.h"
#include "mmpf_scaler.h"
#include "mmp_3gpparser.h"
#include "mmp_tsparser.h"
#include "mmp_vidrec_inc.h"
#include "MsOS.h"
#include "drv_bdma_pub_types.h"
#include "drv_bdma_pub_forward.h"
#include "component_cfg.h"
#include "cust_component_cfg.h"
#include "component_dip.h"
#include "component_display.h"
#include "component_pip.h"
#include "apiVDEC.h"
#include "cam_os_wrapper.h"

/** @addtogroup MMPS_VIDPLAY
@{
@ait_only
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_VP_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_VP_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

/// Max file name length that firmware file system could handle
#define MAX_FILENAME_LENGTH         (512)

/**@brief The save place to transfer the filename

It should be any place which is not used before fopen and play
e.g. Frame buffer, Video buffer, etc.
It could be 0 to let the firmware decide.
*/

#define VPLAYER_BS_BUF_INFO_SIZE    (64)

#define DISPLAY_MAX_WIDTH           (1920)
#define DISPLAY_MAX_HEIGHT          (1088)

#define MMPS_VIDPLAY_MALLOC(size)   ulCurAddr; ulCurAddr += size; TotalSize += size

#if defined( __RTK_OS__ )
#define ALOC_VID_SYS_SIZE           (3 * 1024 * 1024)
#endif
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/** @brief The private variable of 3gp video player

These variables would be varied in run-time.
*/
typedef struct _MMPS_VIDPLAY_PRIVATE_DATA {
    MMP_VID_FILEVALIDATION      file_validation;        ///< The file validation, can be get form parser.
    MMP_BOOL                    bUseExternalMemory;     ///< If the video use external memory
    MMPS_VIDPLAY_DEBLOCK_TYPE   deblock_type;           ///< The deblock type
    MMP_USHORT                  usCurMode;              ///< The current mode index.
    MMP_UBYTE                   ubRotatetype;
    //===== Uninitialized fields =====
    MMP_BOOL                    bTVOut;                 ///< Enable tv output. Use man LCD
    MMP_BOOL                    bFileOpened;            ///< If there is a file opened or not.
    MMP_BOOL                    bConfigDuringPlaying;   ///< bConfig during playing
    MMP_UBYTE                   DMAbufferUsed;          ///< The number of DMA buffer used. It's used to config display
    MMPS_VIDEO_CONTAINER_INFO   container;              ///< mmpd level file information
    MMP_VID_AUDIOTYPE           supported_audio_type;   ///< The audio format supported in current firmware
    MMP_VID_VIDEOTYPE           supported_video_type;   ///< The video format supported in current firmware
    MMP_USHORT                  usFileNameLength;       ///< The File name string length
    MMP_ULONG                   ulVideoFileNameAddr;    ///< The null-terminated string address of file name in the firmware.
    MMP_ULONG                   ulCurYStartAddr;        ///< The current Y start address, used in get current frame.
    MMP_BYTE                    *pFileName;             ///< The pointer to a null-terminated string of the file name
    MMP_ULONG                   ulDramMallocAddr;       ///< The player memory should be allocated after this if it is not NULL
    MMP_ULONG                   ulBSAddress;            ///< Bitstream starting address. This field is used for host_parser mode only.
    MMP_ULONG                   ulBSSize;               ///< Bitstream size. This field is used for host_parser mode only.
    MMP_ULONG                   ulAudioBSAddress;       ///< Audio bitstream starting address. This field is used for host_parser mode only.
    MMP_ULONG                   ulAudioBSSize;          ///< Audio Bitstream size. This field is used for host_parser mode only.
    MMP_ULONG                   ulUDTAAddress;
    MMP_ULONG                   ulDisplayWidth;
    MMP_ULONG                   ulDisplayHeight;
} MMPS_VIDPLAY_PRIVATE_DATA;

typedef struct _MMPS_VIDPLAY_CROPPING_DATA {
    MMP_USHORT                  usTop;
    MMP_USHORT                  usBottom;
    MMP_USHORT                  usLeft;
    MMP_USHORT                  usRight;
} MMPS_VIDPLAY_CROPPING_DATA;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/** @name Module Variables
@{ Keep these variables here to make sure other modules would not access it directly.*/

MMPD_VIDPSR_FUNC                                m_sParser;

/// The private variable of 3gp video player
static MMPS_VIDPLAY_PRIVATE_DATA                m_3gpplayData;

static MMPS_VIDPLAY_CROPPING_DATA               m_VidCropping;

/// [default LCD setting] Default display window setting
static MMP_DISPLAY_WIN_ID                       m_defaultWinID = MMP_DISPLAY_WIN_PIP;

/// The predefined configs
static MMPS_SYSTEM_VIDEODECMODES                m_presetconfig;

static MMP_ULONG                                m_ulFwEndAddr      = NULL;

static MMP_ULONG                                m_ulCurrMemAddr;
static MMP_ULONG                                m_ulMemEndAddr = 0;
static MMPS_VIDPLAY_PLAYSPEED_MODE              m_PlaySpeed;

static MMP_ULONG                                m_BsBufType;
static MMP_BOOL                                 m_bVideoInPlay = MMP_FALSE;

static MMP_VIDEO_CONTAINER_INFO                 m_3GPInfo;
static MMP_VIDEO_CONTAINER_INFO                 m_ContainerInfo;
static MMP_SCAL_GRAB_CTRL                       m_GrabControl;
static MMPS_VIDPLAY_BUFFERADDRESS               m_VideoBufInfo;

// For scaler
static MMP_BOOL                                 m_bUseScaler = MMP_FALSE;
static MMP_SHORT                                m_usScaleWidth;
static MMP_SHORT                                m_usScaleHeight;

// For Graphics scaler
static MMP_BOOL                                 m_bGraphicsScalerEn = GRAPHIC_SCALER_SUPPORT;

// For HDMI
static MMP_DISPLAY_OUTPUT_SEL                   m_displaypanel = MMP_DISPLAY_SEL_NONE;
static MMP_BOOL                                 m_bIsInterlace = MMP_FALSE;

// For software decoder
static MMP_ULONG                                m_ulSWVIDBufSize;
static MMP_ULONG                                m_ulInternalBSSize;

static MMP_BOOL                                 m_bGetVideoFrame = MMP_FALSE;

static MMPS_VIDPLAY_DISPLAY                     m_DisplayConfig;

MMP_BOOL                                        m_ubDecH264Header = MMP_FALSE;
// For AHC
static MMP_BOOL                                 m_bAHCConfig = MMP_FALSE;
static MMP_ULONG                                m_ulVideoStartX;
static MMP_ULONG                                m_ulVideoStartY;
static MMP_ULONG                                m_ulVideoWidth;
static MMP_ULONG                                m_ulVideoHeight;
static MMP_UBYTE                                m_VideoTrack = 0;

// For graphic loop back max output size.
static MMP_USHORT                               m_MaxScaleOutWidth = 1920;
static MMP_USHORT                               m_MaxScaleOutHeight = 1080;
MMP_ULONG m_ulJpgSramAddr;

static MMP_ULONG                                m_ulVideoPlayMemoryEnd = 0;
#if (EN_SPEED_UP_VID & BROWSER_CASE)
static MMP_ULONG                                m_ulTargetThumbWidth;
static MMP_ULONG                                m_ulTargetThumbHeight;
#endif //#if (EN_SPEED_UP_VID & BROWSER_CASE)
#if defined( __RTK_OS__ )
static MMP_ULONG                                gulAlocMem4Rls[MMPS_VIDPLAY_ALOC_NUM] = {0};
static MMP_ULONG                                gulOpenScript[MMPS_VIDPLAY_ALOC_NUM] = {0};
static MMP_ULONG                                gulDbgMsgLevel = E_VDEC_DBG_LEVEL_ERR;

//[TS] Thumbnal:
static MMP_ULONG gulTsThumbBuf = 0x00000000;
static MMP_ULONG gulTsThumbBufSize = 0x00000000;
#endif

static MMP_ULONG                                m_ulThumbnailAddr;
static MMP_ULONG                                m_ulThumbnailSize;
static MMP_BOOL                                 m_bValidThumbnail = MMP_FALSE;

static MMP_BOOL                                 m_bVidPlaybackReScale = MMP_FALSE;

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_VID_VIDEOTYPE    m_MFDFormat;
extern MMP_ULONG            m_ulCodecType;
extern MMP_UBYTE            m_ubVideoDmxTrackNo;
extern MMP_UBYTE            m_ubVideoCurTrack;
#if !defined( __RTK_OS__ )
extern MMP_ULONG            m_ulVideoTrackTotalCnt;
#endif
extern MMP_UBYTE            gubIsVidDualTrks;
#if (EN_SPEED_UP_VID & CACHE_HDL)
extern MMP_UBYTE            m_ubIsPreDecSts;
#endif
#if (EN_SPEED_UP_VID & BROWSER_CASE)
extern MMP_VIDEO_CONTAINER_INFO         gVidFileInfo;
#endif
extern MMP_UBYTE            m_ubIsThumbNail;
#if (VIDEO_DEC_TO_MJPEG)
extern MMP_USHORT           m_usVid2MJpegWidth, m_usVid2MJpegHeight;
#endif
#if defined( __RTK_OS__ )
extern MMP_UBYTE            m_VideoInfo[2][256];
extern MMP_UBYTE            m_VideoInfoLength[2];
#endif

//===========================================================================
//                           Extern function
//===========================================================================

extern MMP_ERR MMPD_VIDPLAYER_SetColorFmt(MMP_ULONG ulFmt);
extern MMP_ERR MMPD_VIDPLAYER_GetColorFmt(MMP_ULONG *pCFmt);

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____Local_Functions_____(){}
#endif

/** @brief Allocate bitstream buffer

@param[in]   VidPlay        video player structure
@param[out]  pBuffers       The addresses buffer
@param[in]   ulStartAddr    Mem start address
@param[out]  ulCurrAddr     current start address
@param[in]   ulBufType      buffer type
@retval MMP_ERR_NONE
*/
static MMP_ERR MMPS_VIDPLAY_AllocBSBuf( MMPS_VIDPLAY_PRIVATE_DATA  *VidData,
                                        MMPS_VIDPLAY_BUFFERADDRESS *pBuffers,
                                        MMP_ULONG                  ulStartAddr,
                                        MMP_ULONG                  *ulCurrAddr,
                                        MMP_ULONG                  ulBufType)
{
    MMP_ULONG ulCurAddr, TotalSize = 0;
    MMP_ULONG DepackSize;

    MMPD_VIDPSR_GetDepackBufSize(&DepackSize);

    ulCurAddr                       = ulStartAddr;
    pBuffers->ulVideoAVDepackStart  = MMPS_VIDPLAY_MALLOC(DepackSize);

    // Allocate video buffers
    #if defined(__RTK_OS__)
    m_presetconfig.ulVideoStreamBufSize = (2 * 1024 * 1024);
    #endif
    pBuffers->ulVideoInSize         = m_presetconfig.ulVideoStreamBufSize;

    ulCurAddr                       = ALIGN32(ulCurAddr);
    if (m_ulCodecType == MMP_VID_VIDEO_MJPG) {
        ulCurAddr                   = ALIGN256(ulCurAddr);
    }

    pBuffers->ulVideoInStart        = MMPS_VIDPLAY_MALLOC(pBuffers->ulVideoInSize);
#if (DEBUG_VIDEO & LOG_VID_BUF)
    printc(FG_GREEN("CACHE_BUF addr=%x: size=%x\r\n"), pBuffers->ulVideoAVDepackStart, DepackSize);
    printc(FG_GREEN("BS_BUF addr=%x: size=%x\r\n"), pBuffers->ulVideoInStart, pBuffers->ulVideoInSize);
#endif
    if (VidData->bConfigDuringPlaying == MMP_FALSE) {

        // Set allocated address to the drivers
        if (pBuffers->ulVideoAVDepackStart != NULL) {
            MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_CACHE, 0, 0, pBuffers->ulVideoAVDepackStart, 0, 0, 0);
        }

        MMPD_VIDPSR_SetVideoBSAddr(pBuffers->ulVideoInStart, pBuffers->ulVideoInSize, ulBufType, m_bGetVideoFrame);
    }

    ulCurAddr = ((ulCurAddr + 0xfff) >> 12) << 12;
    *ulCurrAddr = ulCurAddr;
#if (DEBUG_VIDEO & LOG_VID_BUF)
    printc(FG_GREEN("FSEEK_BUF: addr=%x\r\n"), ulCurAddr);
#endif
    MMPD_VIDPSR_SetSWVidBuffer(ulCurAddr, 0, 0);

    return MMP_ERR_NONE;
}

/** @brief Allocate the buffer according to current format, size

@param[in]  VidPlay             video player structure
@param[out] pBuffers            The addresses buffer
@param[in]  rotate_type         specific rotate type of display buffer
@param[in]  bVideoAvailable     video available or not
@param[in]  bAudioAvailable     audio available or not
@param[in]  bUseScaler          use scaler or not
@param[in]  usScaleWidth        scale width
@param[in]  usScaleHeight       scale height
@param[in]  ulCurrMemEnd        current mem address
@param[out] MemEndAddr End of memory buffer address in firmware
@pre m_3gpplayData.container.usAllocatedWidth and height is calculated.
@retval MMP_ERR_NONE Success.
@retval MMP_3GPPLAY_ERR_INSUFFICIENT_RESOURCES The buffer is not enough for this size.
@retval MMP_3GPPLAY_ERR_UNSUPPORTED_SETTING The audio or video format is not supported.
*/
static MMP_ERR MMPS_VIDPLAY_AllocateBuffers(MMPS_VIDPLAY_PRIVATE_DATA   *VidPlay,
                                            MMPS_VIDPLAY_BUFFERADDRESS  *pBuffers,
                                            MMP_DISPLAY_ROTATE_TYPE     rotate_type,
                                            MMP_BOOL                    bVideoAvailable,
                                            MMP_BOOL                    bAudioAvailable,
                                            MMP_BOOL                    bUseScaler,
                                            MMP_USHORT                  usScaleWidth,
                                            MMP_USHORT                  usScaleHeight,
                                            MMP_ULONG                   *ulCurrMemEnd,
                                            MMP_ULONG                   *MemEndAddr)
{
    MMP_ULONG ulCurAddr,RotateBufNum;
    MMP_ULONG TotalSize = 0; // WHITE_BOX
    //MMP_ULONG YBufSize = 0, UVBufSize = 0;
    MMP_ULONG ulScaleYSize = 0, ulScaleUVSize = 0;

    ulCurAddr = *ulCurrMemEnd;

    if (bVideoAvailable) {

        pBuffers->usBufferUsed              = 3;
        pBuffers->usMPEG4BufUsed            = 3;

        RotateBufNum                        = m_presetconfig.ulRotateDMABufNum;

        if (m_bGraphicsScalerEn)
        {
            if (rotate_type == MMP_DISPLAY_ROTATE_NO_ROTATE)
                pBuffers->ulRotateBufNum        = 0;
            else
                pBuffers->ulRotateBufNum        = m_presetconfig.ulRotateDMABufNum;
            if (bUseScaler)
                pBuffers->ulScalerBufNum        = 3;
            else
                pBuffers->ulScalerBufNum        = 0;
        }
        else
        {
            if ((rotate_type == MMP_DISPLAY_ROTATE_NO_ROTATE) && (bUseScaler == MMP_FALSE))
                pBuffers->ulRotateBufNum        = 0;
            else
                pBuffers->ulRotateBufNum        = m_presetconfig.ulRotateDMABufNum;
        }

        // Will@20091021 DMA always turn on when video play
        MMPD_VIDPLAYER_SetVPPModuleClk(MMPD_3GPPLAY_VPP_DMAROTATE, MMP_TRUE);

        VidPlay->bUseExternalMemory         = MMP_TRUE; // all memory would uses DRAM

        if (pBuffers->ulRotateBufNum > RotateBufNum) {
            pBuffers->ulRotateBufNum = RotateBufNum;
        }
    }
#if (DEBUG_VIDEO & LOG_VID_BUF)
    printc(FG_GREEN("ulCurAddr:%x m_ulSWVIDBufSize=%x: m_ulInternalBSSize=%x\r\n"), ulCurAddr, m_ulSWVIDBufSize, m_ulInternalBSSize);
#endif
    ulCurAddr += (m_ulSWVIDBufSize + m_ulInternalBSSize);

    if (bVideoAvailable)
    {
        if (m_bGraphicsScalerEn) {
            ulScaleYSize = usScaleWidth * usScaleHeight;
#if (DEBUG_VIDEO & LOG_VID_BUF)
            printc(FG_GREEN("cfmt:%x W=%d: H=%d\r\n"), MMPS_VIDPLAY_GetColorFmt(), usScaleWidth, usScaleHeight);
#endif
        }
        else {
            ulScaleYSize = VidPlay->container.usAllocatedWidth * VidPlay->container.usAllocatedHeight;
#if (DEBUG_VIDEO & LOG_VID_BUF)
            printc(FG_GREEN("cfmt:%x W=%d: H=%d\r\n"), MMPS_VIDPLAY_GetColorFmt(), VidPlay->container.usAllocatedWidth , VidPlay->container.usAllocatedHeight);
#endif
        }

        ulScaleUVSize = (MMPS_VIDPLAY_GetColorFmt() == VID_FMT_YUV422) ? ulScaleYSize : (ulScaleYSize >> 1);
        if (VidPlay->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_H264)
        {
            // Output YUV buffers
            if (m_bGraphicsScalerEn)
            {
                pBuffers->ulDMAStartAddr    = MMPS_VIDPLAY_MALLOC(pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));      // Change to real scale down size for reduce memory.
                pBuffers->ulScalerStartAddr = MMPS_VIDPLAY_MALLOC(pBuffers->ulScalerBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));
#if (DEBUG_VIDEO & LOG_VID_BUF)
                printc(FG_GREEN("[H264]DMA_BUF addr=%x: RotNum=%x size=%x\r\n"), pBuffers->ulDMAStartAddr,
                                                                                 pBuffers->ulRotateBufNum,
                                                                                 (pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize)));
                printc(FG_GREEN("[H264]SCALER_BUF addr=%x: ScalNum=%x size=%x\r\n"), pBuffers->ulScalerStartAddr,
                                                                                     pBuffers->ulScalerBufNum,
                                                                                     (pBuffers->ulScalerBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize)));
#endif
            }
            else
            {
                pBuffers->ulDMAStartAddr   = MMPS_VIDPLAY_MALLOC(pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));
#if (DEBUG_VIDEO & LOG_VID_BUF)
                printc(FG_GREEN("[H264]DMA_BUF addr=%x: RotNum=%x size=%x\r\n"), pBuffers->ulDMAStartAddr,
                                                                                 pBuffers->ulRotateBufNum,
                                                                                 (pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize)));
#endif
            }
        }
        else if (VidPlay->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_MJPG)
        {
            // Output YUV buffers
            if (m_bGraphicsScalerEn)
            {
                pBuffers->ulDMAStartAddr    = MMPS_VIDPLAY_MALLOC(pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));      // Change to real scale down size for reduce memory.
                pBuffers->ulScalerStartAddr = MMPS_VIDPLAY_MALLOC(pBuffers->ulScalerBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));
#if (DEBUG_VIDEO & LOG_VID_BUF)
                printc(FG_GREEN("[MJPE]DMA_BUF addr=%x: RotNum=%x size=%x\r\n"), pBuffers->ulDMAStartAddr,
                                                                                 pBuffers->ulRotateBufNum,
                                                                                (pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize)));
                printc(FG_GREEN("[MJPE]SCALER_BUF addr=%x: BufNum=%x size=%x\r\n"), pBuffers->ulScalerStartAddr,
                                                                                    pBuffers->ulScalerBufNum,
                                                                                    pBuffers->ulScalerBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));
#endif
            }
            else
            {
                pBuffers->ulDMAStartAddr   = MMPS_VIDPLAY_MALLOC(pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize));
#if (DEBUG_VIDEO & LOG_VID_BUF)
                printc(FG_GREEN("[MJPE]DMA_BUF addr=%x: RotNum=%x size=%x\r\n"), pBuffers->ulDMAStartAddr,
                                                                                 pBuffers->ulRotateBufNum,
                                                                                (pBuffers->ulRotateBufNum * ALIGN256(ulScaleYSize + ulScaleUVSize)));
#endif
            }
        }
    }

    if (bAudioAvailable)
    {
        if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_AAC_LC)   {
            pBuffers->ulAudioInSize = 0x4000; // 16KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_AMR_NB) {
            pBuffers->ulAudioInSize = 0x1000; // 4KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_MP3) {
            pBuffers->ulAudioInSize = 0x8000; // 32KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_RA) {
            pBuffers->ulAudioInSize = 0xA000; // 40KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_AC3) {
            pBuffers->ulAudioInSize = 0xA000; // 40KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_WMA) {
            pBuffers->ulAudioInSize = 0x4000; // 16KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_WAV) {
            pBuffers->ulAudioInSize = 0x8000; // 32KB
        }
        else if (VidPlay->container.audio_info.format == MMP_VID_AUDIO_NONE) {
            pBuffers->ulAudioInSize = 0x0000; // 0KB
        }
        else if (VidPlay->container.audio_info.format != MMP_VID_AUDIO_NONE) {
            return MMP_3GPPLAY_ERR_UNSUPPORTED_SETTING;
        }
        // Because IBC write unit are 32Bs,
        // Audio buffer need to be aligned 32/256 to avoid buffer overwrite.
        ulCurAddr                       = ALIGN256(ulCurAddr);
        pBuffers->ulAudioInStart        = MMPS_VIDPLAY_MALLOC(pBuffers->ulAudioInSize);
#if (DEBUG_VIDEO & LOG_VID_BUF)
        printc(FG_GREEN("AUDIO_BUF addr=%x: size=%x\r\n"), pBuffers->ulAudioInStart , pBuffers->ulAudioInSize);
#endif
    }

    *MemEndAddr = ulCurAddr;

    return MMP_ERR_NONE;
}

/** @brief Config scaler

@param[out]  usW                width
@param[out]  usH                height
@param[in]   usLCDW             LCD width
@param[in]   usLCDH             LCD height
@param[in]   usMode             mode
@param[out]  usScalerWidth      scaler width
@param[out]  usScalerHeight     scaler height
@retval MMP_ERR_NONE
*/
static void MMPS_VIDPLAY_ConfigScaler(MMP_BOOL  bIsThumbNail,
                                      MMP_BOOL  bIsRotate,
                                      MMP_ULONG ulSrcWidth,
                                      MMP_ULONG ulSrcHeight,
                                      MMPS_VIDPLAY_SCALERCONFIG *pScalerConfig)
{
#define THUMBNAIL_DIP_1ST_SCALE_OUT_W    864
#define THUMBNAIL_DIP_1ST_SCALE_OUT_H    480
#define THUMBNAIL_DIP_2ND_SCALE_OUT_W    256
#define THUMBNAIL_DIP_2ND_SCALE_OUT_H    192

    DIP_COMP_RECT       stDipRect;
    DIP_COMP_COLOR_FMT  eDipColor;
    DISPLAY_COMP_RECT   stDispRect;
    MMP_UBYTE           ubBufCnt = 1;
    MMP_ULONG           ulBufSize = 0;
    MMP_ULONG           ulAlignScaleOutW, ulAlignScaleOutH;
    MMP_ULONG           ulDispWidth, ulDispHeight;
    MMP_ULONG           ulAlignDispWidth, ulAlignDispHeight;
    MMP_ULONG           ulStartX, ulStartY;

    if (!pScalerConfig || pScalerConfig->ulOutWidth == 0 || pScalerConfig->ulOutHeight == 0) {
        printc(FG_RED("Set Component Before Open Script !!\r\n"));
        return;
    }

    #if (VIDEO_PLAYBACK_USE_PIP)
    if (bIsThumbNail) {
        ulDispWidth = pScalerConfig->ulOutWidth;
        ulDispHeight = pScalerConfig->ulOutHeight;
    }
    else {
        ulStartX = m_ulVideoStartX;
        ulStartY = m_ulVideoStartY;
        ulDispWidth = m_ulVideoWidth;
        ulDispHeight = m_ulVideoHeight;
    }
    #else
    ulDispWidth = pScalerConfig->ulOutWidth;
    ulDispHeight = pScalerConfig->ulOutHeight;
    #endif

    if (bIsRotate) {
        ulAlignDispWidth = ALIGN_X(ulDispWidth, DIP_R_COMP_ALIGN_BASE);
        ulAlignDispHeight = ALIGN_X(ulDispHeight, DIP_R_COMP_ALIGN_BASE);
    }
    else {
        ulAlignDispWidth = ALIGN_X(ulDispWidth, DIP_S_COMP_WIDTH_ALIGN_BASE);
        ulAlignDispHeight = ulDispHeight;
    }

    if (bIsRotate) {
        ulAlignScaleOutW = ulAlignDispHeight;
        ulAlignScaleOutH = ulAlignDispWidth;
    }
    else {
        ulAlignScaleOutW = ulAlignDispWidth;
        ulAlignScaleOutH = ulAlignDispHeight;
    }

    if (bIsThumbNail) {
        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_THUMB_SCL_PRE,
                                    0, 0, FLOOR_X(ulSrcWidth, DIP_S_COMP_WIDTH_ALIGN_BASE), ulSrcHeight,
                                    0, 0, FLOOR_X(ulSrcWidth, DIP_S_COMP_WIDTH_ALIGN_BASE), ulSrcHeight,
                                    0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                    DIP_COMP_COLOR_FMT_YUV420_T16X32_UV,
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    2);

        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_THUMB_SCL,
                                    0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                    0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                    0, 0, THUMBNAIL_DIP_2ND_SCALE_OUT_W, THUMBNAIL_DIP_2ND_SCALE_OUT_H,
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    2);

        if (bIsRotate) {
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        DIP_R_COMP_THUMB_ROT,
                                        0, 0, THUMBNAIL_DIP_2ND_SCALE_OUT_W, THUMBNAIL_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMBNAIL_DIP_2ND_SCALE_OUT_W, THUMBNAIL_DIP_2ND_SCALE_OUT_H,
                                        0, 0, THUMBNAIL_DIP_2ND_SCALE_OUT_H, THUMBNAIL_DIP_2ND_SCALE_OUT_W,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        2);
        }

        stDipRect.ulX = 0;
        stDipRect.ulY = 0;
        stDipRect.ulW = (bIsRotate ? THUMBNAIL_DIP_2ND_SCALE_OUT_H : THUMBNAIL_DIP_2ND_SCALE_OUT_W);
        stDipRect.ulH = (bIsRotate ? THUMBNAIL_DIP_2ND_SCALE_OUT_W : THUMBNAIL_DIP_2ND_SCALE_OUT_H);

        MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                    DIP_S_COMP_THUMB_SCL_POST,
                                    stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                    stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                    0, 0, ulAlignDispWidth, ulAlignDispHeight,
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                    DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                    DIP_COMP_MIRROR_DIS,
                                    0,
                                    2);
    }
    else {
        stDipRect.ulX = 0;
        stDipRect.ulY = 0;
        stDipRect.ulW = FLOOR_X(ulSrcWidth, DIP_S_COMP_WIDTH_ALIGN_BASE);
        stDipRect.ulH = ulSrcHeight;

        if (stDipRect.ulW * 1000 / ulAlignScaleOutW > DIP_S_COMP_WIDTH_MAX_RATIO ||
            stDipRect.ulH * 1000 / ulAlignScaleOutH > DIP_S_COMP_HEIGHT_MAX_RATIO) {
            m_bVidPlaybackReScale = MMP_TRUE;

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_MOVIE_PB,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                        DIP_COMP_COLOR_FMT_YUV420_T16X32_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        (ulSrcWidth < 1920) ? 5 : 4);

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_MOVIE_PB_RE_SCAL,
                                        0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                        0, 0, THUMBNAIL_DIP_1ST_SCALE_OUT_W, THUMBNAIL_DIP_1ST_SCALE_OUT_H,
                                        0, 0, ulAlignScaleOutW, ulAlignScaleOutH,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        #if (VIDEO_PLAYBACK_USE_PIP)
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        #else
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        #endif
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        (ulSrcWidth < 1920) ? 5 : 4);
        }
        else {
            m_bVidPlaybackReScale = MMP_FALSE;

            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_SCL,
                                        DIP_S_COMP_MOVIE_PB,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        0, 0, ulAlignScaleOutW, ulAlignScaleOutH,
                                        DIP_COMP_COLOR_FMT_YUV420_T16X32_UV,
                                        #if (VIDEO_PLAYBACK_USE_PIP)
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        #else
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        #endif
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        (ulSrcWidth < 1920) ? 5 : 4);
        }

        if (bIsRotate) {
            stDipRect.ulX = 0;
            stDipRect.ulY = 0;
            stDipRect.ulW = ulAlignScaleOutW;
            stDipRect.ulH = ulAlignScaleOutH;
            MMPD_Fctl_SetDIPCompAttr(   DIP_COMP_TYPE_ID_ROT,
                                        DIP_R_COMP_MOVIE_PB,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        stDipRect.ulX, stDipRect.ulY, stDipRect.ulW, stDipRect.ulH,
                                        0, 0, ulAlignScaleOutH, ulAlignScaleOutW,
                                        #if (VIDEO_PLAYBACK_USE_PIP)
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        DIP_COMP_COLOR_FMT_YUV422_YUYV,
                                        #else
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        DIP_COMP_COLOR_FMT_YUV420_UV,
                                        #endif
                                        DIP_COMP_MIRROR_DIS,
                                        0,
                                        (ulSrcWidth < 1920) ? 5 : 4);
        }

        #if (VIDEO_PLAYBACK_USE_PIP)
        {
            MMP_ULONG ulPipBgWidth  = (ulAlignDispWidth > RTNA_LCD_GetAttr()->usPanelW)? RTNA_LCD_GetAttr()->usPanelW : ulAlignDispWidth;
            MMP_ULONG ulPipBgHeight = (ulAlignDispHeight > RTNA_LCD_GetAttr()->usPanelH)? RTNA_LCD_GetAttr()->usPanelH : ulAlignDispHeight;
            MMPS_Display_SetPIPCompAttr(   PIP_COMP_PLAYBACK,
                                           0, 0, ulAlignDispWidth, ulAlignDispHeight,
                                           ulStartX, ulStartY, ulPipBgWidth, ulPipBgHeight,
                                           MMP_FALSE, MMP_FALSE);
        }                     
        #else
        MMPS_Display_SetDispCompAttr(   0, 0, ulAlignDispWidth, ulAlignDispHeight,
                                        0, 0, ulAlignDispWidth, ulAlignDispHeight,
                                        0, 0, ulDispWidth, ulDispHeight,
                                        0, 0, ulDispWidth, ulDispHeight,
                                        MMP_FALSE, MMP_FALSE);
        #endif
    }
}

/** @brief Config memory setting for the video player

@param[in]  pConfig             video player configuration
@param[in]  pBuffers            The addresses buffer
@param[in]  VidData             video player structure
@param[in]  VidInfo             video player information
@param[out] bUseScaler          use scaler or not
@param[out] usScalerWidth       scaler width
@param[out] usScalerHeight      scaler height
@param[in]  ulMemStartAddr      memory start address
@param[out] ulCurrMemAddr       current memory address
@param[out] ulMemEndAddr        memory end address
@param[out] ulBufType           bitstream buffer type

@retval MMP_ERR
*/
static MMP_ERR MMPS_VIDPLAY_ConfigMemory(MMPS_VIDPLAY_CONFIG        *pConfig,
                                         MMPS_VIDPLAY_BUFFERADDRESS *pBuffers,
                                         MMPS_VIDPLAY_PRIVATE_DATA  *VidData,
                                         MMP_VIDEO_CONTAINER_INFO   *VidInfo,
                                         MMP_BOOL                   *bUseScaler,
                                         MMP_SHORT                  *usScaleWidth,
                                         MMP_SHORT                  *usScaleHeight,
                                         MMP_ULONG                  ulMemStartAddr,
                                         MMP_ULONG                  *ulCurrMemAddr,
                                         MMP_ULONG                  *ulMemEndAddr,
                                         MMP_ULONG                  *ulBufType,
                                         MMPS_VIDPLAY_SCALERCONFIG  *pScalerConfig)
{
    MMP_ULONG   ulWidth = 0, ulHeight = 0;
    MMP_ERR     error = MMP_ERR_NONE;
    MMP_USHORT  usScaleW = 0, usScaleH = 0;
    MMP_ULONG   ulDisplayW = 0, ulDisplayH = 0;

    if (NULL == pConfig) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }

    m_ulVideoPlayMemoryEnd = 0;

    if ((VidData->usCurMode == VIDEOPLAY_MODE_PAL_TV)||(VidData->usCurMode == VIDEOPLAY_MODE_NTSC_TV))
    {
        VidData->ubRotatetype = 0;
    }

    if(VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_H264){
        MMPD_VIDPLAYER_SetVideoFormat(1);
    }
    else {
        MMPD_VIDPLAYER_SetVideoFormat(0);
    }

    pBuffers->ulRotateBufNum    = 0;

    VidData->DMAbufferUsed      = 0;

    // Avoid H.263 inconsistance with 3GP resolution
    if (VidInfo->is_video_available[m_VideoTrack]) {

        // calulate the allocated width
        VidData->container.usAllocatedWidth =  VidData->container.video_info[m_VideoTrack].width         +
                                               VidData->container.video_info[m_VideoTrack].cropping_left +
                                               VidData->container.video_info[m_VideoTrack].cropping_right;

        VidData->container.usAllocatedHeight = VidData->container.video_info[m_VideoTrack].height        +
                                               VidData->container.video_info[m_VideoTrack].cropping_top  +
                                               VidData->container.video_info[m_VideoTrack].cropping_bottom;

        ulWidth  = VidData->container.usAllocatedWidth;
        ulHeight = VidData->container.usAllocatedHeight;

        m_VidCropping.usTop    = VidData->container.video_info[m_VideoTrack].cropping_top;
        m_VidCropping.usLeft   = VidData->container.video_info[m_VideoTrack].cropping_left;
        m_VidCropping.usRight  = VidData->container.video_info[m_VideoTrack].cropping_right;
        m_VidCropping.usBottom = VidData->container.video_info[m_VideoTrack].cropping_bottom;
    }

    // For scale
    usScaleW = VidData->container.usAllocatedWidth;
    usScaleH = VidData->container.usAllocatedHeight;

    if (pScalerConfig != NULL && pScalerConfig->bUseScaler &&
        pScalerConfig->ulOutWidth != 0 && pScalerConfig->ulOutHeight != 0) {

        ulDisplayW = pScalerConfig->ulOutWidth;
        ulDisplayH = pScalerConfig->ulOutHeight;
        //Fix HDMI display issue: SrcSize (2688x1504).
        if (m_displaypanel == MMP_DISPLAY_SEL_HDMI) {
            ulDisplayW = MMPS_Display_GetConfig()->hdmi.usDisplayWidth;
            ulDisplayH = MMPS_Display_GetConfig()->hdmi.usDisplayHeight;
        }
    }
    else {
        if (m_displaypanel == MMP_DISPLAY_SEL_HDMI) {
            ulDisplayW = MMPS_Display_GetConfig()->hdmi.usDisplayWidth;
            ulDisplayH = MMPS_Display_GetConfig()->hdmi.usDisplayHeight;
        }
        else if (m_displaypanel == MMP_DISPLAY_SEL_CCIR) {
            ulDisplayW = MMPS_Display_GetConfig()->ccir.usDisplayWidth;
            ulDisplayH = MMPS_Display_GetConfig()->ccir.usDisplayHeight;
        }
        else if (m_displaypanel == MMP_DISPLAY_SEL_NTSC_TV) {
            ulDisplayW = MMPS_Display_GetConfig()->ntsctv.usDisplayWidth;
            ulDisplayH = MMPS_Display_GetConfig()->ntsctv.usDisplayHeight;
        }
        else if (m_displaypanel == MMP_DISPLAY_SEL_PAL_TV) {
            ulDisplayW = MMPS_Display_GetConfig()->paltv.usDisplayWidth;
            ulDisplayH = MMPS_Display_GetConfig()->paltv.usDisplayHeight;
        }
        else {
            ulDisplayW = MMPS_Display_GetConfig()->mainlcd.usWidth;
            ulDisplayH = MMPS_Display_GetConfig()->mainlcd.usHeight;
        }
    }

    if (m_bGraphicsScalerEn)
    {
        if (pScalerConfig != NULL && pScalerConfig->bUseScaler == MMP_FALSE) {
            *bUseScaler = MMP_FALSE;
            *usScaleWidth = 0;
            *usScaleHeight = 0;
        }
        else {
            if( VidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_90 ||
                VidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_270) {
                *bUseScaler = MMP_FALSE;
            }
            else {

                *bUseScaler = MMP_FALSE;
            }
        }

        if(*bUseScaler) {
            MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_FRAME_RESOLUTION, usScaleW, usScaleH,
                                       usScaleW, usScaleH, 0, 0);

            VidData->ulDisplayWidth = *usScaleWidth;
            VidData->ulDisplayHeight = *usScaleHeight;
        }
        else {
            VidData->ulDisplayWidth = 0;
            VidData->ulDisplayHeight = 0;
        }
    }
    else
    {
        *bUseScaler = MMP_FALSE;
    }

    MMPS_VIDPLAY_AllocBSBuf(VidData,pBuffers, ulMemStartAddr, ulCurrMemAddr, *ulBufType);
    // Modify for if scaler disable but still use dma. We need to set correct scaler width/height.
    if (*bUseScaler) {
        error = MMPS_VIDPLAY_AllocateBuffers( VidData,
                                              pBuffers,
                                              VidData->ubRotatetype,
                                              VidInfo->is_video_available[m_VideoTrack],
                                              VidInfo->is_audio_available,
                                              *bUseScaler,
                                              *usScaleWidth,
                                              *usScaleHeight,
                                              ulCurrMemAddr,
                                              ulMemEndAddr);
    }
    else {
        error = MMPS_VIDPLAY_AllocateBuffers( VidData,
                                              pBuffers,
                                              VidData->ubRotatetype,
                                              VidInfo->is_video_available[m_VideoTrack],
                                              VidInfo->is_audio_available,
                                              *bUseScaler,
                                              ulWidth,
                                              ulHeight,
                                              ulCurrMemAddr,
                                              ulMemEndAddr);
    }

    if (error != MMP_ERR_NONE)
        return error;

    VidData->DMAbufferUsed = pBuffers->ulRotateBufNum;

    if (VidData->bConfigDuringPlaying == MMP_FALSE) {

        if ( (VidInfo->is_audio_available)) {

            // Set allocated address to the drivers
            MMPD_VIDPSR_SetAudioBSAddr(pBuffers->ulAudioInStart, pBuffers->ulAudioInSize);
        }
    }

    if (VidInfo->is_video_available) {

        // this must be set after MMPD_MP4V_SetVideoAuxiliaryBuffers
        PRINTF("scale Width : %d\r\n", *usScaleWidth);
        PRINTF("scale Height : %d\r\n", *usScaleHeight);

        if (m_bGraphicsScalerEn)
        {
            MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_SCALER_BUFFER, pBuffers->usBufferUsed, pBuffers->ulScalerBufNum,
                                   *bUseScaler, pBuffers->ulScalerStartAddr, (MMP_USHORT)VidData->ulDisplayWidth, (MMP_USHORT)VidData->ulDisplayHeight);

            MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_VIDEO_BUFFER, pBuffers->usBufferUsed, VidData->DMAbufferUsed,
                                   VidData->ubRotatetype, pBuffers->ulDMAStartAddr, (MMP_USHORT)VidData->ulDisplayWidth/*0*/, (MMP_USHORT)VidData->ulDisplayHeight/*0*/);
        }
        else
        {
            MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_VIDEO_BUFFER, pBuffers->usBufferUsed, VidData->DMAbufferUsed,
                                   VidData->ubRotatetype, pBuffers->ulDMAStartAddr, *usScaleWidth, *usScaleHeight);
        }
    }

    if (VidData->bConfigDuringPlaying == MMP_FALSE) {
        if( (VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_H263)     ||
            (VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_MP4V_SP)  ||
            (VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_MP4V_ASP))
        {
            *ulBufType = RING_BUFFER;
        }
        else if( VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_H264) {
            //Will Ring
            *ulBufType = NEAR_RING_BUFFER;
        }
        else if(VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_WMV ||
                VidData->container.video_info[m_VideoTrack].format == MMP_VID_VIDEO_RV) {
            *ulBufType = NEAR_RING_BUFFER;
        }

        MMPD_VIDPSR_SetVideoBSAddr(pBuffers->ulVideoInStart, pBuffers->ulVideoInSize, *ulBufType, m_bGetVideoFrame);

        if (VidInfo->is_video_available) {
            MMPD_VIDPLAYER_ConfigMemDone(ulMemEndAddr);
            #if !defined( __RTK_OS__ )
            if ( (*ulMemEndAddr - ulMemStartAddr) > (26 * 1024 * 1024)) {
                return MMP_VIDPSR_ERR_INSUFFICIENT_RESOURCES;
            }
            #endif
        }
    }
#if !defined( __RTK_OS__ )
    if (*ulMemEndAddr > VIDEO_WORKINGBUF_END) {
        return MMP_VIDPSR_ERR_INSUFFICIENT_RESOURCES;
    }
#endif
    VidData->ulCurYStartAddr = pBuffers->ulVideoOutYStart;

    m_ulVideoPlayMemoryEnd = *ulMemEndAddr;

    return MMP_ERR_NONE;
}

/** @brief Set the display of Video player to use display configuration

This function is used in MMPS_VIDPLAY module only.
This function set the registers according to the display settings.
These settings does not require MMPS_VIDPLAY_CONFIG structure.

@pre The MMP_DISPLAY_WIN_ATTR has already been filled correctly
@pre Use MMPS_VIDPLAY_Config to config these input parameters.

@return The status of the function call
@retval MMP_VIDPSR_ERR_FORMAT_NOT_DETECTED The H.263 is detected but the resolution is not supported
*/
static MMP_ERR MMPS_VIDPLAY_ConfigDisplay(  MMP_USHORT                  usX,
                                            MMP_USHORT                  usY,
                                            MMP_USHORT                  usWidth,
                                            MMP_USHORT                  usHeight,
                                            MMP_ULONG                   rotationtype,
                                            MMP_BOOL                    bMirror,
                                            MMP_BOOL                    bFullyFilled,
                                            MMP_DISPLAY_DEV_TYPE        outputpanel,
                                            MMP_BOOL                    bKeepRatio,
                                            MMP_BOOL                    bUseLCDScaler)
{
    MMP_DISPLAY_DISP_ATTR       dispattribute;
    MMP_DISPLAY_WIN_ATTR        winattribute;
    MMP_SCAL_GRAB_CTRL          grab_control;
    MMP_SCAL_FIT_RANGE          fitrange;
    MMP_BOOL                    bUseScaler = MMP_TRUE;
    MMP_ULONG                   FrameAddr[3];
    MMP_ULONG                   MaxOutWidth = usWidth;
    MMP_DISPLAY_ROTATE_TYPE     rotatetype;
    MMP_USHORT                  width,height,rotate_width,rotate_height,start_x,start_y;
    MMP_ERR                     error;
    MMP_BOOL                    bSquarePixel = MMP_TRUE;
    // For TV bandwidth limitation
    //if(m_3gpplayData.usCurMode == VIDEOPLAY_MODE_PAL_TV)
    //{
    //    if(MaxOutWidth >= 688)
    //        MaxOutWidth = 688;
    //}

    if(outputpanel == MMP_DISPLAY_P_LCD || outputpanel == MMP_DISPLAY_P_LCD_FLM || outputpanel == MMP_DISPLAY_RGB_LCD){
        if (!m_bAHCConfig) {
            if(((usX + usWidth) > MMPS_Display_GetConfig()->mainlcd.usWidth) ||
               ((usY + usHeight) > MMPS_Display_GetConfig()->mainlcd.usHeight)) {
                return MMP_3GPPLAY_ERR_PARAMETER;
            }
        }
    }

    if ((outputpanel == MMP_DISPLAY_TV)) {
        m_3gpplayData.bTVOut = MMP_TRUE;
    }
    else {
        m_3gpplayData.bTVOut = MMP_FALSE;
    }

    MMPD_VIDPLAYER_SetActivePanel(outputpanel, m_defaultWinID);

    if (outputpanel == MMP_DISPLAY_TV)
    {
        rotatetype = 0;
    }
    else
    {
        rotatetype = rotationtype;
    }

    if (!m_3GPInfo.is_video_available[m_VideoTrack]) {
        m_3gpplayData.container.video_info[m_VideoTrack].width  =
        m_3gpplayData.container.usAllocatedWidth  = m_presetconfig.config[m_3gpplayData.usCurMode].display.usWidth;
        m_3gpplayData.container.video_info[m_VideoTrack].height =
        m_3gpplayData.container.usAllocatedHeight = m_presetconfig.config[m_3gpplayData.usCurMode].display.usHeight;
        m_3gpplayData.container.video_info[m_VideoTrack].cropping_left = 0;
        m_3gpplayData.container.video_info[m_VideoTrack].cropping_top = 0;
    }

    if(m_bUseScaler == MMP_FALSE){
        width                   = m_3gpplayData.container.usAllocatedWidth;
        #if (HDMI_OUTPUT_EN == 1)
        if(!m_bIsInterlace) {
            height              = m_3gpplayData.container.usAllocatedHeight;
        }
        else {
            height              = m_3gpplayData.container.usAllocatedHeight / 2;
        }
        #else
        height                  = m_3gpplayData.container.usAllocatedHeight;
        #endif
        start_x                 = m_3gpplayData.container.video_info[m_VideoTrack].cropping_left;
        start_y                 = m_3gpplayData.container.video_info[m_VideoTrack].cropping_top;
    }
    else {
        width                   = m_usScaleWidth;
        height                  = m_usScaleHeight;
        start_x                 = 0;
        start_y                 = 0;
    }

    // When rotate 90 or 270 degree, exchange width and height
    if (m_bGraphicsScalerEn)
    {
        if ((rotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) ||
            (rotatetype == MMP_DISPLAY_ROTATE_RIGHT_270)){

            if(m_bUseScaler == MMP_FALSE){
                rotate_width        = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].height;
                rotate_height       = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].width;
            }
            else {
                rotate_width         = m_usScaleHeight;
                rotate_height        = m_usScaleWidth;
            }

            if (m_3gpplayData.DMAbufferUsed > 0) {// external DMA rotation
                if(m_bUseScaler == MMP_FALSE){
                    width           = m_3gpplayData.container.usAllocatedHeight;
                    height          = m_3gpplayData.container.usAllocatedWidth;

                    if (rotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) {
                        start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_bottom;
                        start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_left;
                    }
                    else {// 270
                        start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_top;
                        start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_right;
                    }
                }
                else {
                    width           = m_usScaleHeight;
                    height          = m_usScaleWidth;
                    start_x         = 0;
                    start_y         = 0;
                }
                rotatetype      = MMP_DISPLAY_ROTATE_NO_ROTATE;
            }
        }
        else {
            if(m_bUseScaler == MMP_FALSE){
                rotate_width        = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].width;
                rotate_height       = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].height;

                if (m_3gpplayData.DMAbufferUsed > 0) {
                    if(rotatetype == MMP_DISPLAY_ROTATE_RIGHT_180) {
                        start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_right;
                        start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_bottom;
                    }
                }
            }
            else {
                rotate_width         = m_usScaleWidth;
                rotate_height        = m_usScaleHeight;

                if (m_3gpplayData.DMAbufferUsed > 0) {
                    if(rotatetype == MMP_DISPLAY_ROTATE_RIGHT_180) {
                        start_x     = 0;
                        start_y     = 0;
                    }
                }
            }

            rotatetype      = MMP_DISPLAY_ROTATE_NO_ROTATE;
        }
    }
    else
    {
        if ((rotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) ||
            (rotatetype == MMP_DISPLAY_ROTATE_RIGHT_270)){

            rotate_width        = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].height;
            rotate_height       = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].width;

            if (m_3gpplayData.DMAbufferUsed > 0) {// external DMA rotation
                width           = m_3gpplayData.container.usAllocatedHeight;
                height          = m_3gpplayData.container.usAllocatedWidth;

                if (rotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) {
                    start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_bottom;
                    start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_left;
                }
                else {// 270
                    start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_top;
                    start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_right;
                }
                rotatetype      = MMP_DISPLAY_ROTATE_NO_ROTATE;
            }
        }
        else {
            if(m_bUseScaler == MMP_FALSE){
                rotate_width        = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].width;
                rotate_height       = (MMP_USHORT)m_3gpplayData.container.video_info[m_VideoTrack].height;
            }
            else {
                rotate_width        = m_usScaleWidth;
                rotate_height        = m_usScaleHeight;
            }

            if (m_3gpplayData.DMAbufferUsed > 0) {
                if(rotatetype == MMP_DISPLAY_ROTATE_RIGHT_180) {
                    start_x     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_right;
                    start_y     = m_3gpplayData.container.video_info[m_VideoTrack].cropping_bottom;
                }
            }
            rotatetype      = MMP_DISPLAY_ROTATE_NO_ROTATE;
        }
    }

    if (!m_3GPInfo.is_video_available) {
        FrameAddr[0] = m_ulMemEndAddr;
        FrameAddr[1] = FrameAddr[0] + width*height;
        FrameAddr[2] = FrameAddr[1] + (width*height)/4;
    }
    else {
        MMPD_VIDPLAYER_GetEmptyFrame(&FrameAddr[0],&FrameAddr[1],&FrameAddr[2]);//call MMPF_MJPGDEC_GetFreeFrame
    }

    // window attributes
    winattribute.ulBaseAddr     = FrameAddr[0];
    winattribute.ulBaseUAddr    = FrameAddr[1];
    winattribute.ulBaseVAddr    = FrameAddr[2];
    winattribute.usWidth        = width;
    winattribute.usHeight       = height;

    if (m_3gpplayData.usCurMode == VIDEOPLAY_MODE_CCIR) {
        winattribute.usLineOffset   = width * 2;
        winattribute.colordepth     = MMP_DISPLAY_WIN_COLORDEPTH_YUV422;
    }
    else {
        #if (HDMI_OUTPUT_EN == 1)
        if(!m_bIsInterlace) {
            winattribute.usLineOffset   = width;
        }
        else {
            winattribute.usLineOffset   = width * 2;
        }
        #endif

        winattribute.usLineOffset   = width;
        if (MMPS_VIDPLAY_GetColorFmt() == VID_FMT_I420) {
            winattribute.colordepth = MMP_DISPLAY_WIN_COLORDEPTH_YUV420;
        }
        else if (MMPS_VIDPLAY_GetColorFmt() == VID_FMT_YUV422) {
            winattribute.colordepth     = MMP_DISPLAY_WIN_COLORDEPTH_YUV422;
            winattribute.usLineOffset   = width * 2;
        }
        else {
            winattribute.colordepth = MMP_DISPLAY_WIN_COLORDEPTH_YUV420_INTERLEAVE;
        }
    }

    #if (HDMI_OUTPUT_EN == 1)
    if(m_bIsInterlace)
        rotate_height = rotate_height / 2;
    #endif

    // display attributes
    dispattribute.usStartX          = start_x;
    dispattribute.usStartY          = start_y;
    dispattribute.usDisplayWidth    = rotate_width;
    dispattribute.usDisplayHeight   = rotate_height;

    if ( m_bAHCConfig ) {
        dispattribute.usDisplayOffsetX  = usX;
        dispattribute.usDisplayOffsetY  = usY;
    }
    else {
        dispattribute.usDisplayOffsetX  = 0;
        dispattribute.usDisplayOffsetY  = 0;
    }
    dispattribute.rotatetype        = rotatetype;
    dispattribute.bMirror           = bMirror;

    if (m_bGraphicsScalerEn)
    {
        if (!bUseLCDScaler) {
            bUseScaler = MMP_FALSE;
        }
    }
    else
    {
        if (m_bUseScaler || !bUseLCDScaler){
            bUseScaler = MMP_FALSE;
        }
    }

    if(!bUseLCDScaler){

        if(rotate_width > usWidth) {
            dispattribute.usStartX += (rotate_width - usWidth) / 2;
            dispattribute.usStartX = dispattribute.usStartX - (dispattribute.usStartX & 0x01);
            dispattribute.usDisplayWidth = usWidth;
        }
        if(rotate_height > usHeight) {
            dispattribute.usStartY += (rotate_height - usHeight) / 2;
            dispattribute.usStartY = dispattribute.usStartY - (dispattribute.usStartY & 0x01);
            dispattribute.usDisplayHeight = usHeight;
        }
    }
//    if (!bUseScaler) {
//	    if (usWidth > dispattribute.usDisplayWidth) {
//        	dispattribute.usDisplayOffsetX = (usX + (usWidth - dispattribute.usDisplayWidth) / 2);
//        }
//        else {
//            dispattribute.usDisplayOffsetX = usX;
//        }
//        if (usHeight > dispattribute.usDisplayHeight) {
//        	dispattribute.usDisplayOffsetY = (usY + (usHeight - dispattribute.usDisplayHeight) / 2);
//        }
//        else {
//            dispattribute.usDisplayOffsetY = usY;
//        }
//	}
    //scaling
    fitrange.scalerType     = MMP_SCAL_TYPE_WINSCALER;
    fitrange.ulInWidth      = dispattribute.usDisplayWidth;
    fitrange.ulInHeight     = dispattribute.usDisplayHeight;

    if (m_MFDFormat == MMP_VID_VIDEO_MJPG) {
        fitrange.ulOutWidth  = fitrange.ulInWidth;
        fitrange.ulOutHeight = fitrange.ulInHeight;
    }
    else {
        fitrange.ulOutWidth  = MaxOutWidth;
        fitrange.ulOutHeight = usHeight;
    }

    fitrange.ulInGrabX      = 1;
    fitrange.ulInGrabY      = 1;
    fitrange.ulInGrabW      = fitrange.ulInWidth;
    fitrange.ulInGrabH      = fitrange.ulInHeight;
    fitrange.ubChoseLit     = 1;

    if (!m_bAHCConfig) {
        if (bFullyFilled) {
            if (bKeepRatio) {
                fitrange.fitmode = MMP_SCAL_FITMODE_OUT;
                //RTNA_DBG_Str0(FG_YELLOW("DSPY:FIT_OUT!\r\n"));

            }
            else {
                fitrange.fitmode = MMP_SCAL_FITMODE_OPTIMAL;
                //RTNA_DBG_Str0(FG_YELLOW("DSPY:FIT_OPTIMAL!\r\n"));
            }
        }
        else {
            if (bKeepRatio) {
                fitrange.fitmode = MMP_SCAL_FITMODE_IN;
                //RTNA_DBG_Str0(FG_YELLOW("DSPY:FIT_IN!\r\n"));
            }
            else {
                fitrange.fitmode = MMP_SCAL_FITMODE_OPTIMAL;
                MMP_PRINT_RET_ERROR(0, 0, "[WARRING] DSPY:The usage not verify yet! (fitmode=OPTIMAL)!", 0);
            }
        }
    }

    do
    {
        if ( bSquarePixel ) {
            MMPF_Scaler_GetGCDBestFitScale(&fitrange, &grab_control);
        }
        else {
            MMPF_Scaler_GetGCDBestFitScale(&fitrange, &grab_control);
        }

        error = MMP_ERR_NONE;

        if (bUseScaler) {
//			if (m_3gpplayData.container.video_info[m_VideoTrack].width *3 == m_3gpplayData.container.video_info[m_VideoTrack].height * 4) 
//			{
//				if(m_3gpplayData.usCurMode == VIDEOPLAY_MODE_PAL_TV || m_3gpplayData.usCurMode == VIDEOPLAY_MODE_NTSC_TV)
//				{
//					if(m_DisplayConfig.usWidth > (grab_control.ulOutEdX - grab_control.ulOutStX + 1)) {
//						dispattribute.usDisplayOffsetX = (m_DisplayConfig.usWidth - (grab_control.ulOutEdX - grab_control.ulOutStX + 1)) / 2;
//					}
//					
//		        	if(usHeight > (grab_control.ulOutEdY - grab_control.ulOutStY + 1)) {
//						dispattribute.usDisplayOffsetY = (m_DisplayConfig.usHeight - (grab_control.ulOutEdY - grab_control.ulOutStY + 1)) / 2;
//					}
//				}
//				else
//				{
//					if(m_DisplayConfig.usWidth > (grab_control.ulOutEdX - grab_control.ulOutStX + 1)) {
//						dispattribute.usDisplayOffsetX = (m_DisplayConfig.usWidth - (grab_control.ulOutEdX - grab_control.ulOutStX + 1)) / 2;
//		        	}
//		        	if(usHeight >= (grab_control.ulOutEdY - grab_control.ulOutStY + 1)) {
//		        	    dispattribute.usDisplayOffsetY = (usHeight - (grab_control.ulOutEdY - grab_control.ulOutStY + 1)) / 2;
//		        	}
//				}
//			}
//			else
            {
                MMP_USHORT usBigger, usSmaller;
                if(MaxOutWidth > (grab_control.ulOutEdX - grab_control.ulOutStX + 1)) {
                    usBigger = MaxOutWidth;
                    usSmaller = (grab_control.ulOutEdX - grab_control.ulOutStX + 1);
                }
                else {
                    //usBigger = (grab_control.ulOutEdX - grab_control.ulOutStX + 1);
                    usSmaller = usBigger = MaxOutWidth;
                }
                dispattribute.usDisplayOffsetX = usX + (usBigger - usSmaller)>>1;

                if(usHeight > (grab_control.ulOutEdY - grab_control.ulOutStY + 1)) {
                    usBigger = usHeight;
                    usSmaller = (grab_control.ulOutEdY - grab_control.ulOutStY + 1);
                }
                else{
                    //usBigger = (grab_control.ulOutEdY - grab_control.ulOutStY + 1);
                    usSmaller = usBigger = usHeight;
                }
                dispattribute.usDisplayOffsetY = usY + (usBigger - usSmaller)>>1;
#if 0
                printc(FG_YELLOW("MaxOutWidth/usHeight : [%d/%d]\r\n"), MaxOutWidth, usHeight );
                printc(FG_YELLOW("OutEdX/Y : [%d/%d]\r\n"), grab_control.ulOutEdX, grab_control.ulOutEdY );
                printc(FG_YELLOW("OutStX/Y [%d %d]\r\n"), grab_control.ulOutStX, grab_control.ulOutStY );
                printc(FG_YELLOW("usX/Y [%d %d]\r\n"), usX, usY );
                printc(FG_YELLOW("OffsetXY [%d %d]\r\n"), dispattribute.usDisplayOffsetX, dispattribute.usDisplayOffsetY );
#endif
            }
        }
        if (m_3gpplayData.bTVOut) {
            // offset = 4n, n != 0
            dispattribute.usDisplayOffsetX &= (~0x3);
        }

        MMPF_Display_SetWinAttributes(m_defaultWinID, &winattribute);

        if(m_3gpplayData.bTVOut && !m_bUseScaler && dispattribute.usDisplayWidth > 1280){
            MMPD_TV_SetInterlaceMode(MMP_TRUE);
        }

        MMPF_Display_SetWinToDisplay(m_defaultWinID, &dispattribute);

        if (bUseScaler) {

            if ( bSquarePixel ) {
                error = MMPF_Display_SetWinScaling(MMP_DISPLAY_WIN_PIP, &fitrange, &grab_control);
            }
            else {
                error = MMPF_Display_SetWinScaling(MMP_DISPLAY_WIN_PIP, &fitrange, &grab_control);
            }
        }

    }while(error != MMP_ERR_NONE);

    MEMCPY(&m_GrabControl, &grab_control, sizeof(MMP_SCAL_GRAB_CTRL));

    return MMP_ERR_NONE;
}

/** @brief Get the Video file type

This function initializes the modules required in video player application.
Currently it open and close the clocks of the components
@return Reports the status of the function call. Now it returns MMPS_3GP_SUCCESS.
@pre The firmware code needs to be downloaded into the code memory.
@pre The gSystem3GPPlayModes::bTVout has to be set before MMPS_VIDPLAY_Init so that
    it could use appropriate PLL setting.
*/
static MMP_ERR MMPS_VIDPLAY_GetFileType(MMP_BYTE *pFileName, MMP_ULONG ulFileNameLength, MMP_PSR_PARSERTYPE  *ParserType)
{
    MMP_ULONG   ulFileID;
    MMP_UBYTE   ubHeader[5];
    MMP_ULONG   ulRWCnt;
    MMP_ERR     err = MMP_ERR_NONE;

    ubHeader[4] = 0;

    if (1) {
        err = MMPS_FS_FileOpen(pFileName, ulFileNameLength, "rb", sizeof("rb"), &ulFileID);

        if(err != MMP_ERR_NONE){
            UartSendTrace("Please put the video file %s to SD card\r\n", pFileName);
            return err;
        }

        MMPS_FS_FileRead(ulFileID, ubHeader, 4, &ulRWCnt);

        UartSendTrace("read header : x%x\r\n", MAKE_TAG_BE(ubHeader[0], ubHeader[1], ubHeader[2], ubHeader[3]));

        if(ubHeader[0] == 'R' && ubHeader[1] == 'I' &&ubHeader[2] == 'F' &&ubHeader[3] == 'F') {
            *ParserType                             = MMP_PSR_AVIPARSER;
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_AVIPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_AVIPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_AVIPSR_SeekByTime;
        } 
        else if (ubHeader[0] == 0x1A && ubHeader[1] == 0x45 && ubHeader[2] == 0xDF && ubHeader[3] == 0xA3){
    	    *ParserType                             = MMP_PSR_MKVPARSER;
    	    m_sParser.MMPD_VIDPSR_Parse             = MMPD_3GPPSR_Parse;
    	    m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
    	    m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
	    }
        #if (MMP_TSPARSER_SUPPORT)
        else if(ubHeader[0] == 0x47 && ubHeader[1] == 0x40 &&ubHeader[2] == 0x00 &&ubHeader[3] == 0x10) {
            *ParserType                             = MMP_PSR_TSPARSER;
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_TSPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_TSPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_TSPSR_SeekByTime;
        }
        #endif
        else if(ubHeader[0] == '.' && ubHeader[1] == 'R' &&ubHeader[2] == 'M' &&ubHeader[3] == 'F') {
            *ParserType                             = MMP_PSR_RMPARSER;
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_3GPPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
        }
        else {
            MMPS_FS_FileRead(ulFileID, ubHeader, 4, &ulRWCnt);

            if((ubHeader[0] == 'f' && ubHeader[1] == 't' &&ubHeader[2] == 'y' &&ubHeader[3] == 'p') ||
               (ubHeader[0] == 'm' && ubHeader[1] == 'o' &&ubHeader[2] == 'o' &&ubHeader[3] == 'v')){
                *ParserType                         = MMP_PSR_3GPPARSER;
                m_sParser.MMPD_VIDPSR_Parse         = MMPD_3GPPSR_Parse;
                m_sParser.MMPD_VIDPSR_Predecode     = MMPD_3GPPSR_Predecode;
                m_sParser.MMPD_VIDPSR_SeekByTime    = MMPD_3GPPSR_SeekByTime;
            }
            else {
                err = MMP_VIDPSR_ERR_FORMAT_NOT_DETECTED;
            }
        }
        MMPS_FS_FileClose(ulFileID);
    }

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Parse
//  Description :
//------------------------------------------------------------------------------
/** @brief Parse a 3GP file from card or memory. Change the firmware if needed

Used in card mode. If the audio format is recognized and need to change firmware.
The caller should change the firmware. But now this function would change the firmware.
And the caller should reinitlize again.
@param[in] ubFilename C string of the file name. NULL as memory mode
@param[in] ulFileNameLength The length of the file name.
@return Reports the status of the function call.
@retval MMP_3GPPLAY_ERR_PARAMETER The file name pointer is invalid or the file name is too long.
@retval MMP_VIDPSR_ERR_CONTENT_PIPE_OPEN_FAILED The file function is invalid or file open error.
@pre The gSystem3GPPlayModes has already been filled with file name and length.
*/
static MMP_ERR MMPS_VIDPLAY_Parse(MMP_BYTE *ubFilename, MMP_ULONG ulFileNameLength)
{
    MMP_ERR                     error;
    MMP_PSR_PARSERTYPE          ParserType  = MMP_PSR_3GPPARSER;
    MMPS_VIDPLAY_BUFFERADDRESS  *pBuffers   = &m_VideoBufInfo;

    #if (OMA_DRM_EN == 1)
    MMP_USHORT                  drmEn;
    MMP_ULONG                   drmOffset;

    MMPD_AUDIO_GetDRMEnable(&drmEn, MMPD_OMADRM_FOR_PLAY);
    MMPD_AUDIO_GetDRMOffset(&drmOffset, MMPD_OMADRM_FOR_PLAY);
    #endif

    if (ubFilename == NULL) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }

    #if (FS_INPUT_ENCODE == UCS2)
    if ((MAX_FILENAME_LENGTH * 2) <= ulFileNameLength) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }
    #elif (FS_INPUT_ENCODE == UTF8)
    if (MAX_FILENAME_LENGTH <= ulFileNameLength) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }
    #endif

    m_3gpplayData.pFileName = (MMP_BYTE*)ubFilename;

    // Video player handshake buf, for mem mode
    MMPD_VIDPSR_SetHandShakeAddr(m_ulFwEndAddr, VPLAYER_BS_BUF_INFO_SIZE);
#if (DEBUG_VIDEO & LOG_VID_BUF)
    printc(FG_GREEN("HANDSHAKE addr=%x: size=%x\r\n"), m_ulFwEndAddr,  VPLAYER_BS_BUF_INFO_SIZE);
#endif
    m_ulFwEndAddr += ALIGN32(VPLAYER_BS_BUF_INFO_SIZE);

    // card mode
    m_3gpplayData.usFileNameLength = ulFileNameLength;

    m_3gpplayData.ulVideoFileNameAddr = m_ulFwEndAddr;
#if (DEBUG_VIDEO & LOG_VID_BUF)
    printc(FG_GREEN("MAXFILENAME addr=%x: size(align32)=%x(%x) \r\n"), m_3gpplayData.ulVideoFileNameAddr, (MAX_FILENAME_LENGTH * 3), ALIGN32(VPLAYER_BS_BUF_INFO_SIZE));
#endif
    m_ulFwEndAddr += ALIGN32(MAX_FILENAME_LENGTH * 3);

    // Use card mode
    MMPD_VIDPSR_SetCardMode(MMP_TRUE, NULL);

    MMPS_VIDPLAY_AllocBSBuf(&m_3gpplayData, pBuffers, m_ulFwEndAddr, &m_ulCurrMemAddr, m_BsBufType);

    // Set file name to play
    error = MMPD_VIDPSR_SetFileName(m_3gpplayData.ulVideoFileNameAddr, m_3gpplayData.pFileName,
                                    m_3gpplayData.usFileNameLength,(MMP_ULONG*)&ParserType);
#if (DEBUG_VIDEO & LOG_PARSE)
    printc(FG_YELLOW("PARSER=%x(1:3GP 2:AVI 6:TS)\r\n"), ParserType);
#endif
    if (error == MMP_ERR_NONE) {
        if (MMP_PSR_3GPPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_3GPPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
        }
        else if (MMP_PSR_AVIPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_AVIPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_AVIPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_AVIPSR_SeekByTime;
        }
        #if (MMP_TSPARSER_SUPPORT)
        else if (MMP_PSR_TSPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_TSPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_TSPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_TSPSR_SeekByTime;
        }
        #endif
        #if (MMP_MKVPARSER_SUPPORT)
        else if (MMP_PSR_MKVPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_3GPPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
        }
        #endif
        #if (MMP_RMPARSER_SUPPORT)
        else if (MMP_PSR_RMPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_RMPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
        }
        #endif
        #if (MMP_WMVPARSER_SUPPORT)
        else if (MMP_PSR_WMVPARSER == ParserType) {
            m_sParser.MMPD_VIDPSR_Parse             = MMPD_WMVPSR_Parse;
            m_sParser.MMPD_VIDPSR_Predecode         = MMPD_3GPPSR_Predecode;
            m_sParser.MMPD_VIDPSR_SeekByTime        = MMPD_3GPPSR_SeekByTime;
        }
        #endif


        // Notify the firmware to parse
        error = m_sParser.MMPD_VIDPSR_Parse(0, &m_3gpplayData.file_validation, MMP_TRUE);
    }

    MMPD_VIDPSR_GetSWVidBufferUsed(&m_ulSWVIDBufSize, &m_ulInternalBSSize);
#if (DEBUG_VIDEO & LOG_PARSE)
    printc(FG_YELLOW("SWVID:x%x InterBsSz=x%x\r\n"), m_ulSWVIDBufSize, m_ulInternalBSSize); 
#endif

    return error;
}

/** @brief Initializes Video module

This function initializes the modules required in video player application.
Currently it open and close the clocks of the components
@return Reports the status of the function call. Now it returns MMPS_3GP_SUCCESS.
@pre The firmware code needs to be downloaded into the code memory.
@pre The gSystem3GPPlayModes::bTVout has to be set before MMPS_VIDPLAY_Init so that
    it could use appropriate PLL setting.
*/
static MMP_ERR MMPS_VIDPLAY_Init(void)
{
    m_3gpplayData.bFileOpened           = MMP_FALSE;
    m_3gpplayData.bConfigDuringPlaying  = MMP_FALSE;

    memset(&m_3GPInfo, 0, sizeof(m_3GPInfo));

    MMPD_VIDPLAYER_Init();
    MMPD_VIDPLAYER_SetVPPModuleClk(MMPD_3GPPLAY_VPP_MAX, MMP_FALSE);
    return MMP_ERR_NONE;
}

/**@end_ait_only */

#if 0
void _____Playback_Control_____(){}
#endif

MMP_ERR MMPS_VIDPLAY_SetDramMallocAddr(MMP_ULONG ulDramMallocAddr)
{
    m_3gpplayData.ulDramMallocAddr = ulDramMallocAddr;
    return MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Open
//  Description : Function to open video
//------------------------------------------------------------------------------
/** @brief Open the video file and initial video codec.

This function opens the file, parse the information and change firmware if nessary and
initial video codec and allocate necessay memory.

@param[in] pFileName         file name
@param[in] ulFileNameLength  file name length
@param[in] ulTargetTime      target time
@param[in] bPreDecVideo      pre-decode video or not
@param[in] bPreDecAudio      pre-decode audio or not
@post It's able to play the file only after this operation.
@post The video file info was collected so that the caller could change configuration according to the info.
      Such as change hardware audio CODEC sampling rate.
*/
MMP_ERR MMPS_VIDPLAY_Open(MMP_BYTE *pFileName, MMP_ULONG ulFileNameLength,
                          MMP_ULONG ulTargetTime,
                          MMP_BOOL bPreDecVideo, MMP_BOOL bPreDecAudio,
                          MMPS_VIDPLAY_SCALERCONFIG *pScalerConfig)
{
    MMP_ERR             error = MMP_ERR_NONE;
    MMP_M_STATE         state;
    MMP_VID_AUDIOTYPE   audio_type;
    MMP_VID_VIDEOTYPE   video_type;
    MMP_ULONG           audio_samplerate=0;
    MMP_ULONG           ulMemStart;
    MMP_BOOL            bSeekable = MMP_TRUE;
//#if (EN_SPEED_UP_VID & CACHE_HDL)
//    MMP_ULONG           t1, t2;
//#endif
    m_bVideoInPlay = 1;

    error = MMPS_VIDPLAY_GetState(&state);

    if ((MMP_M_STATE_LOADED != state)) {
        return MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION;
    }

    MMPD_AUDIO_SetOutPath(MMPS_AUDIO_GetOutPath());

    // Parse and change the firmware if needed
    {
        MMPS_VIDPLAY_AllocFwEnd(MMPS_VIDPLAY_ALOC_VID);

        if (m_3gpplayData.ulDramMallocAddr != NULL) {
            m_ulFwEndAddr = ALIGN_X(m_3gpplayData.ulDramMallocAddr, 32);
        }

        video_type      = MMP_VID_VIDEO_H263 | MMP_VID_VIDEO_MP4V_SP | MMP_VID_VIDEO_H264 | MMP_VID_VIDEO_RV | MMP_VID_VIDEO_WMV | MMP_VID_VIDEO_DIVX | MMP_VID_VIDEO_MJPG;
        audio_type      = MMP_VID_AUDIO_AMR | MMP_VID_AUDIO_AAC | MMP_VID_AUDIO_MP3 | MMP_VID_AUDIO_AC3 | MMP_VID_AUDIO_WMA | MMP_VID_AUDIO_WAV | MMP_VID_AUDIO_RA;
        m_BsBufType     = NEAR_RING_BUFFER;

        // Enable the clock
        MMPS_VIDPLAY_Init();

        // Try to parse the file and check the result, change the firmware if necessary
        error = MMPS_VIDPLAY_Parse(pFileName, ulFileNameLength);
#if  !defined( __RTK_OS__ )
        if (pScalerConfig) {
            if (m_ulCodecType == MMP_VID_VIDEO_MJPG) {
                pScalerConfig->bUseScaler = MMP_TRUE;
            }

            if (m_3gpplayData.usCurMode == VIDEOPLAY_MODE_CCIR) {
                pScalerConfig->bUseScaler = MMP_TRUE;
            }
        }
#endif
        if (error != MMP_ERR_NONE) {
            printc(FG_RED("PARSE failed(x%x)\r\n"), error);
            #if defined( __RTK_OS__ )
            MMPS_VIDPLAY_ReleaseFwEnd();
            #endif
            return error;
        }

        m_3gpplayData.bFileOpened = MMP_TRUE;

        // Get the container info from the parser
        MMPS_VIDPLAY_GetFileInfo(pFileName, ulFileNameLength, &m_3gpplayData.container);
        MMPD_VIDPSR_GetUserDataInfo(&m_3gpplayData.ulUDTAAddress);
        if (m_3gpplayData.container.videoTrackNum) {
            if (m_VideoTrack > (m_3gpplayData.container.videoTrackNum -1)) {
                m_VideoTrack = (m_3gpplayData.container.videoTrackNum -1);
            }
        }
#if !defined( __RTK_OS__ )
        #if (EN_SPEED_UP_VID & PB_CASE)
        if (pScalerConfig->ulOutMaxHeight) {
            if ((m_3gpplayData.container.video_info[m_VideoTrack].height == 1088) && (1080 == pScalerConfig->ulOutHeight)) {
                // 1080P@60 VR v.s. 1080P output => no scaling
                pScalerConfig->ulOutWidth  = 0;
                pScalerConfig->ulOutHeight = 0;
                pScalerConfig->bUseScaler  = MMP_FALSE;
            }
            else if (pScalerConfig->ulOutHeight < m_3gpplayData.container.video_info[m_VideoTrack].height) {
                //DownScale:
                pScalerConfig->bUseScaler = MMP_TRUE;

                if (pScalerConfig->ulOutHeight > pScalerConfig->ulOutMaxHeight) {
                    pScalerConfig->ulOutWidth = pScalerConfig->ulOutMaxWidth;
                    pScalerConfig->ulOutHeight = pScalerConfig->ulOutMaxHeight;
                }
            }
            else {
                //UpScale:
                pScalerConfig->ulOutWidth  = 0;
                pScalerConfig->ulOutHeight = 0;
                pScalerConfig->bUseScaler = MMP_FALSE;
            }
        }
        #endif
//+++[VideoPlay]
        if (!(m_3gpplayData.ubRotatetype%2) &&
            !(m_DisplayConfig.usWidth%16) &&
            !(m_3gpplayData.container.video_info[m_VideoTrack].width%16) &&
            (m_3gpplayData.container.video_info[m_VideoTrack].width * m_DisplayConfig.usHeight) == (m_DisplayConfig.usWidth * m_3gpplayData.container.video_info[m_VideoTrack].height)) //AspectRatio equal
        {
            MMPS_VIDPLAY_SetColorFmt(VID_FMT_NV12);
        }
        else if ((m_3gpplayData.ubRotatetype%2) &&
                 !(m_DisplayConfig.usHeight%16) &&
                 !(m_3gpplayData.container.video_info[m_VideoTrack].width%16) &&
                 (m_3gpplayData.container.video_info[m_VideoTrack].width * m_DisplayConfig.usHeight) == (m_DisplayConfig.usWidth * m_3gpplayData.container.video_info[m_VideoTrack].height)) //AspectRatio equal
        {
            MMPS_VIDPLAY_SetColorFmt(VID_FMT_NV12);
        }
        else {
            if (!pScalerConfig->ulOutWidth && !pScalerConfig->ulOutHeight && !pScalerConfig->bUseScaler) {
                //There is a IC bug when GraScal make I420 up scaling. (NV12 is workable)
                //For this issue , not use GraScal at up scale case.
                if(m_3gpplayData.container.video_info[m_VideoTrack].height%16)      // 1920 * 1080
                {
                    MMPS_VIDPLAY_SetColorFmt(VID_FMT_I420);
                    if (m_3gpplayData.usCurMode != VIDEOPLAY_MODE_CCIR) {
                        pScalerConfig->bUseScaler = (!m_ubIsThumbNail)? MMP_TRUE : MMP_FALSE;
                    }
                }
                else
                {
                    MMPS_VIDPLAY_SetColorFmt(VID_FMT_NV12);
                }
            }
            else {
                MMPS_VIDPLAY_SetColorFmt(VID_FMT_I420);
                if (m_3gpplayData.usCurMode != VIDEOPLAY_MODE_CCIR) {
                    pScalerConfig->bUseScaler = (!m_ubIsThumbNail)? MMP_TRUE : MMP_FALSE;
                }
            }
        }
//---[VideoPlay]
#endif
        MMPD_VIDPSR_SetParameter(MMPD_VIDPLAY_PARAMETER_CURRENTTRACK, m_VideoTrack);
        m_ubVideoDmxTrackNo = m_VideoTrack;

        // Protection if no Emergency files in Browse mode
        if (!gubIsVidDualTrks && m_VideoTrack) {
            m_ubVideoDmxTrackNo = 0;
            error = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
            printc(FG_YELLOW("It's single track. Don't switch track\r\n"));
            #if defined( __RTK_OS__ )
            MMPS_VIDPLAY_ReleaseFwEnd();
            #endif
            return error;
        }
    }

    // Set audio codec format
    if ( (m_3GPInfo.is_audio_available)){

        if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_AAC) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VAAC_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_AMR) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VAMR_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_MP3) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VMP3_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_AC3) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VAC3_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_WMA) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VWMA_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_WAV){
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VWAV_PLAY);
        }
        else if (m_3gpplayData.container.audio_info.format == MMP_VID_AUDIO_RA) {
            MMPD_AUDIO_SetPlayFormat(MMP_AUDIO_VRA_PLAY);
        }
        #if defined( __RTK_OS__ )
        if(1) {
            MMP_ULONG ulAuiSampleR = 0x0000000000;
            MMPF_Aui_GetSampleRate(&ulAuiSampleR);
            if (ulAuiSampleR && ulAuiSampleR != m_ContainerInfo.audio_info.sampling_rate) {
                printc(FG_RED("\r\n\r\n ***** [NOTICE]Keytone SpR need to be synced [KEY:VID]/[%dK:%dK] *****\r\n\r\n"), (ulAuiSampleR/1000), (m_ContainerInfo.audio_info.sampling_rate/1000));
            }
        }
        #endif
        printc("AudFmt:x%x(x2:AAC x8:MP3 x40:WAV)SpR:%dK\r\n", m_3gpplayData.container.audio_info.format, (m_ContainerInfo.audio_info.sampling_rate/1000));
    }

    m_PlaySpeed = MMPS_VIDPLAY_PLAYSPEED_NORMAL;

    // Config memory
    ulMemStart = m_ulFwEndAddr;

    error = MMPS_VIDPLAY_ConfigMemory(&(m_presetconfig.config[m_3gpplayData.usCurMode]),
                                      &(m_VideoBufInfo),
                                      &(m_3gpplayData),
                                      &(m_3GPInfo),
                                      &m_bUseScaler,
                                      &m_usScaleWidth,
                                      &m_usScaleHeight,
                                      ulMemStart,
                                      &m_ulCurrMemAddr,
                                      &m_ulMemEndAddr,
                                      &m_BsBufType,
                                      pScalerConfig);

    if (error != MMP_ERR_NONE) {
        #if defined( __RTK_OS__ )
        MMPS_VIDPLAY_ReleaseFwEnd();
        #endif
        return error;
    }
#if  defined( __RTK_OS__ )
    /* Set Component Parameters */
    MMPS_VIDPLAY_ConfigScaler(m_ubIsThumbNail,
                              gbLCDRotate,
                              m_ContainerInfo.video_info[m_VideoTrack].width,
                              m_ContainerInfo.video_info[m_VideoTrack].height,
                              pScalerConfig);

    if (m_ubIsThumbNail) {
        if (gbLCDRotate) {
            OpenScript(COMPO_SCRIPT_BROWSER_VID_THUMB_R);
        }
        else {
            OpenScript(COMPO_SCRIPT_BROWSER_VID_THUMB_N);
        }
        gulOpenScript[MMPS_VIDPLAY_ALOC_BROW] = MMP_TRUE;
    }
    else {
        if (gbLCDRotate) {
            if (m_bVidPlaybackReScale) {
                OpenScript(COMPO_SCRIPT_MOVIE_PB_RESCALE_R);
            }
            else {
                OpenScript(COMPO_SCRIPT_MOVIE_PB_R);
            }
        }
        else {
            if (m_bVidPlaybackReScale) {
                OpenScript(COMPO_SCRIPT_MOVIE_PB_RESCALE_N);
            }
            else {
                OpenScript(COMPO_SCRIPT_MOVIE_PB_N);
            }
        }

        gulOpenScript[MMPS_VIDPLAY_ALOC_VID] = MMP_TRUE;
    }

    {
        VDEC_DecCmd    pkQcmd = {0};
        MMP_ULONG      ulCodecAddr = (m_VideoBufInfo.ulVideoInStart + m_VideoBufInfo.ulVideoInSize - m_VideoInfoLength[0] - 1);

        pkQcmd.u32StAddr    = MS_VA2PA(ulCodecAddr);
        pkQcmd.u32Size      = m_VideoInfoLength[0];
        MEMCPY((MMP_UBYTE *)(ulCodecAddr), &m_VideoInfo[0][0], m_VideoInfoLength[0]);
        //DrvBdma_Transfer(DRV_BDMA_MIU2MIU, (void*)&m_VideoInfo[0][0], ulCodecAddr, pkQcmd.u32Size);
        //printc(FG_YELLOW("Push Codec AD:x%x SZ:x%x\r\n"), ulCodecAddr, m_VideoInfoLength[0]);
        MApi_VDEC_PushDecQ(&pkQcmd);
        MApi_VDEC_Play();
        MApi_VDEC_FireDecCmd();
    }
#endif

    // Predecode
    if(bPreDecVideo || bPreDecAudio) {
        //AHC_OS_GetTime(&t1);
        error = m_sParser.MMPD_VIDPSR_Predecode(MMP_TRUE, bPreDecAudio, bPreDecVideo ,&audio_samplerate);
        //AHC_OS_GetTime(&t2);
        //printc(FG_YELLOW("PRE_D_ED:%d %d\r\n"), t1, (t2-t1));
    }

    if (error != MMP_ERR_NONE) {
        #if defined( __RTK_OS__ )
        MMPS_VIDPLAY_ReleaseFwEnd();
        #endif
        return error;
    }

    if(ulTargetTime != 0 && (ulTargetTime < m_3gpplayData.container.total_file_time)) {
        // During video play on LCD and change to  HDMI playback lock up issue
        error = m_sParser.MMPD_VIDPSR_SeekByTime(ulTargetTime, MMP_TRUE, MMPS_VIDPSR_NEXT_KEYFRAME);

        if(error != MMP_ERR_NONE && error != MMP_VIDPSE_ERR_CONTENT_CANNOTSEEK) {
            #if defined( __RTK_OS__ )
            MMPS_VIDPLAY_ReleaseFwEnd();
            #endif
            return error;
        }

        if(error == MMP_VIDPSE_ERR_CONTENT_CANNOTSEEK) {
            bSeekable = MMP_FALSE;
            error = MMP_ERR_NONE;
        }
        else {
            //MMPD_System_GetTime(&t1);
            error = m_sParser.MMPD_VIDPSR_Predecode(MMP_TRUE, bPreDecAudio, bPreDecVideo ,&audio_samplerate);
            //MMPD_System_GetTime(&t2);
            //printc(FG_YELLOW("PRE_DI_ED:%d %d\r\n"), t1, (t2-t1));
        }
    }

    if (error != MMP_ERR_NONE) {
        #if defined( __RTK_OS__ )
        MMPS_VIDPLAY_ReleaseFwEnd();
        #endif
        return error;
    }
#if  !defined( __RTK_OS__ )
    if( !m_bGetVideoFrame )
    {
        MMPS_VIDPLAY_CONFIG *pConfig;

        pConfig = &(m_presetconfig.config[m_3gpplayData.usCurMode]);

        if ( m_bAHCConfig ) {
            error = MMPS_VIDPLAY_ConfigDisplay( m_ulVideoStartX,
                                                m_ulVideoStartY,
                                                m_ulVideoWidth,
                                                m_ulVideoHeight,
                                                m_3gpplayData.ubRotatetype,
                                                pConfig->display.bMirror,
                                                pConfig->display.bFullyFilled,
                                                pConfig->display.outputpanel,
                                                pConfig->display.bKeepRatio,
                                                pConfig->display.bUseScaler);

        }
        else {
            error = MMPS_VIDPLAY_ConfigDisplay( m_DisplayConfig.usX,
                                                m_DisplayConfig.usY,
                                                m_DisplayConfig.usWidth,
                                                m_DisplayConfig.usHeight,
                                                m_3gpplayData.ubRotatetype,
                                                pConfig->display.bMirror,
                                                pConfig->display.bFullyFilled,
                                                pConfig->display.outputpanel,
                                                pConfig->display.bKeepRatio,
                                                pConfig->display.bUseScaler);
        }
    }

    if(error == MMP_ERR_NONE && !bSeekable)
        return MMP_VIDPSE_ERR_CONTENT_CANNOTSEEK;
#endif

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Play
//  Description : Function to play video
//------------------------------------------------------------------------------
/** @brief Config display and play the file in predefined configuration

@retval MMP_M_ERR_UNSUPPORTED_SETTING The mode is out of range
@retval MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION The file is not opened or the video player is not stopped.
*/
MMP_ERR MMPS_VIDPLAY_Play(void *VidPlayerCallBack, void *Context)
{
    MMP_ERR             error;
    MMP_M_STATE         state;

    error = MMPS_VIDPLAY_GetState(&state);

    if ((MMP_M_STATE_IDLE != state)) {
        return MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION;
    }

    error = MMPD_VIDPLAYER_Start(VidPlayerCallBack, Context);

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Pause
//  Description : Function to pause video playback
//------------------------------------------------------------------------------
/** @brief Pause the playback

//@ait_only
@note This function could be used in another thread in memory mode
      while the AIT thread is serving the data.
//@end_ait_only
@return Reports the status of the function call.
*/
MMP_ERR MMPS_VIDPLAY_Pause(void)
{
    return MMPD_VIDPLAYER_Pause();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Resume
//  Description : Function to resume video playback
//------------------------------------------------------------------------------
/** @brief Resume the playback

//@ait_only
@note This function could be used in another thread in memory mode
      while the AIT thread is serving the data.
//@end_ait_only
@return Reports the status of the function call.
*/
MMP_ERR MMPS_VIDPLAY_Resume(void)
{
    return MMPD_VIDPLAYER_Resume();
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Stop
//  Description : Function to Stop video playback
//------------------------------------------------------------------------------
/** @brief Stop the playback

@param[out] LastKeyFrameNum      last key frame number

//@ait_only
@note This function could be used in another thread in memory mode
      while the AIT thread is serving the data.
//@end_ait_only
@return Reports the status of the function call.
*/
MMP_ERR MMPS_VIDPLAY_Stop(MMP_ULONG *LastKeyFrameNum)
{
    MMP_ERR error;

    error = MMPD_VIDPLAYER_Stop(LastKeyFrameNum);

    m_PlaySpeed = MMPS_VIDPLAY_PLAYSPEED_NORMAL;

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Close
//  Description : Function to Close video playback
//------------------------------------------------------------------------------
/** @brief Close the playback

@return Reports the status of the function call.
*/
MMP_ERR MMPS_VIDPLAY_Close(void)
{
    MMP_ERR error = MMP_ERR_NONE;

    if(m_3gpplayData.bFileOpened)
    {
        if (m_3GPInfo.is_video_available[m_ubVideoCurTrack]) {
            MMPD_VIDPLAYER_CloseCodec();
        }
        error = MMPD_VIDPLAYER_Close();
    }
#if defined( __RTK_OS__ )
    MMPS_VIDPLAY_ReleaseFwEnd();
#endif

    m_3gpplayData.bFileOpened   = MMP_FALSE;
    m_bVideoInPlay              = 0;
    m_bUseScaler                = MMP_FALSE;

    m_ulMemEndAddr              = NULL;
    m_ulFwEndAddr               = NULL;

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Step
//  Description : Function to jump to next frame
//------------------------------------------------------------------------------
/** @brief Jump to next frame

@return Reports the status of the function call.
*/
MMP_ERR MMPS_VIDPLAY_Step(void)
{
    MMP_ERR     error = MMP_ERR_NONE;
    MMP_M_STATE state;

    error = MMPS_VIDPLAY_GetState(&state);

    if (state != MMP_M_STATE_PAUSE && state != MMP_M_STATE_IDLE) {
        return MMP_3GPPLAY_ERR_INVALID_STATE;
    }

    if(!m_3gpplayData.bFileOpened)
        return MMP_3GPPLAY_ERR_INVALID_STATE;

    error = MMPD_VIDPLAYER_Step();
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetVideoInPlay
//  Description : Function to get video in play or not
//------------------------------------------------------------------------------
/** @brief Get m_bVideoInPlay is true or not. m_bVideoInPlay will be set true in
MMPS_VIDPLAY_Open and set false in MMPS_VIDPLAY_Close

@param[out] bEnable      m_bVideoInPlay is true or not

@return video in play status.
*/
MMP_ERR MMPS_VIDPLAY_GetVideoInPlay(MMP_BOOL*bEnable)
{
    *bEnable = m_bVideoInPlay;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetVideoInPlay
//  Description : Function to set video in play or not
//------------------------------------------------------------------------------
/** @brief Set m_bVideoInPlay is true or not.

@return video in play status.
*/
MMP_ERR MMPS_VIDPLAY_SetVideoInPlay(MMP_BOOL bEnable)
{
    m_bVideoInPlay = bEnable;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SeekByTime
//  Description : Function to seek video position
//------------------------------------------------------------------------------
/** @brief Seek the video by time in millisecond.

@param[in] ulTargetTime      Time in millisecond
@param[in] bSeekToPrecisePos Seek to precise position or not (I frame only)
@return The status of the function call
@retval MMP_3GPPLAY_ERR_PARAMETER When the percentage is out of range.
*/
MMP_ERR MMPS_VIDPLAY_SeekByTime(const MMP_ULONG ulTargetTime, MMP_ULONG ulSeekOption)
{
    MMP_ERR         error;
    MMP_M_STATE     state;
    MMP_ULONG       audio_samplerate;
    MMP_BOOL        bPredecAudio = MMP_TRUE;

    PRINTF("Go to:%dm%ds\r\n" ,ulTargetTime / 60000, (ulTargetTime % 60000) / 1000);

    if (ulTargetTime > m_3gpplayData.container.total_file_time) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }

    error = MMPS_VIDPLAY_GetState(&state);

    if (state != MMP_M_STATE_PAUSE && state != MMP_M_STATE_IDLE) {
        return MMP_3GPPLAY_ERR_INVALID_STATE;
    }

    if(!m_3gpplayData.bFileOpened)
        return MMP_3GPPLAY_ERR_INVALID_STATE;

    if(ulSeekOption & MMPS_VIDPSR_SEEK_UNPREDECAUD) {
        bPredecAudio = MMP_FALSE;
    }
    ulSeekOption = ulSeekOption & MMPS_VIDPSR_SEEK_SEEKMASK;

    error = m_sParser.MMPD_VIDPSR_SeekByTime(ulTargetTime, MMP_TRUE, ulSeekOption);

    if(error != MMP_ERR_NONE) {
        return error;
    }

    m_ubDecH264Header = (ulSeekOption == MMPS_VIDPSR_SEEK_FILE_START) ? TRUE : FALSE;
    error = m_sParser.MMPD_VIDPSR_Predecode(MMP_TRUE,
                                            bPredecAudio,
                                            MMP_TRUE,
                                            &audio_samplerate ); //MMPF_Player_Predecode
    m_ubDecH264Header = FALSE;

    #if !defined( __RTK_OS__ )
    if(!(ulSeekOption & MMPS_VIDPSR_SEEK_AUDIO_ONLY)) {
        printc(FG_YELLOW("MMPS_VIDPLAY_SeekByTime!\r\n"));
        MMPD_VIDPLAYER_RedrawLastRefresh();
    }
    #endif

    return error;
}

#if (SUPPORT_VR_THUMBNAIL)
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetThumbnail
//  Description : Function to get video thumbnail with the 3GP udta atom
//------------------------------------------------------------------------------
/** @brief Parse a 3GP file to get the video thumbnail with the 3GP udta atom.

Get the video thumbnail with the 3GP udta atom.

@param[in]  pFileName        The name of the video file to play.
@param[in]  ulFileNameLength File name length
@param[in]  ulOutBufSize     The size of thumbnail output buffer
@param[out] ubOutBuf         The output buffer address for thumbnail. Note that this pointer might be changed.
@param[out] ulOutSize        Output the size of the requested thumbnail.

@return It reports the status about the result.
*/
MMP_ERR MMPS_VIDPLAY_GetThumbnail(  MMP_BYTE    *pbFileName,
                                    MMP_ULONG   ulFileNameLength,
                                    MMP_ULONG   ulOutBufSize,
                                    MMP_UBYTE   **ppubOutBuf,
                                    MMP_ULONG   *pulThumbSize)
{
#define ATOM_SKIP_FILE_POS (0x24)

    MMP_ERR     err = MMP_ERR_NONE;
    MMP_ULONG   ulFileID = 0;
    MMP_ULONG   ulAtom = 0, ulAtomLen = 0, ulJpgSymbSt = 0;
    MMP_UBYTE   *ubOutBuf = *ppubOutBuf;
    MMP_UBYTE   *pubBuf = NULL;
    MMP_ULONG   ulCurFilePos = 0, ulBufRemain = 0;
    MMP_BOOL    bThumbnailFound = MMP_FALSE;
    MMP_BOOL    bSkipAtomFound = MMP_FALSE;

    *pulThumbSize = 0;

    pubBuf = ubOutBuf;

    if (MMPF_VIDENC_GetVRThumbEn() == MMP_FALSE) {
        err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
        return err;
    }

    if (ulOutBufSize < 512) {
        MMPS_VP_DBG_ERR(1, "Buffer is too small to parse thumbnail\r\n");
        return MMP_VIDPSR_ERR_INSUFFICIENT_RESOURCES;
    }

    err = MMPS_FS_FileOpen(pbFileName, ulFileNameLength, "rb", sizeof("rb"), &ulFileID);
    if (err != MMP_ERR_NONE) {
        MMPS_VP_DBG_ERR(1, "Open file %s fail\r\n", pbFileName);
        return err;
    }

    ulCurFilePos = 0;

    err = MMPS_FS_FileRead(ulFileID, ubOutBuf, 512, &ulBufRemain);
    if (err) {
        goto VIDEO_GETTHUMB_EXIT;
    }

    do {
        // Get atom & atom length
        ulAtomLen   = MAKE_TAG_BE(pubBuf[0], pubBuf[1], pubBuf[2], pubBuf[3]);
        ulAtom      = MAKE_TAG_BE(pubBuf[4], pubBuf[5], pubBuf[6], pubBuf[7]);

        if (ulAtomLen == 0) {
            return MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
        }

        switch(ulAtom) {
        case ATOM_FTYP:
            break;
        case ATOM_SKIP:
            //| atomlens | skip atom | 1clickshare | jpglenth | jpg data  |
            //|   4B     |    4B     |     8B      |   4B     | (64KB-4B) |
            bSkipAtomFound = MMP_TRUE;

            ulJpgSymbSt = MAKE_TAG_BE(pubBuf[20], pubBuf[21], pubBuf[22], pubBuf[23]);

            if (ulJpgSymbSt == 0xFFD8FFDB ||
                ulJpgSymbSt == 0xFFD8FFE0) {
                *pulThumbSize = MAKE_TAG_BE(pubBuf[16], pubBuf[17], pubBuf[18], pubBuf[19]);
                ulAtomLen = 8 + 12;
                bThumbnailFound = MMP_TRUE;
            }
            else {
                // How about just skip here? Because SKIP is a known MOV atom.
                // A big skip atom does not mean there is no thumbnail.
                if (ulAtomLen > MMPF_VIDENC_GetVRThumbMaxBufSize()) {
                    err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
                    goto VIDEO_GETTHUMB_EXIT;
                }
            }
            break;
        case ATOM_MOOV:
        case ATOM_UDTA:
            ulAtomLen = 8; // Just ignore the atom header
            break;
        case ATOM_PANA:
            *pulThumbSize = ulAtomLen - 8;
            ulAtomLen = 8; // Just ignore the atom header
            bThumbnailFound = MMP_TRUE;
            break;
        default:
            if (ulCurFilePos == 0) {
                err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
                goto VIDEO_GETTHUMB_EXIT;
            }
            break;
        }

        ulCurFilePos += ulAtomLen; // Update current file position

        if (bThumbnailFound) {
            break;
        }

        if ((!bSkipAtomFound) && (ulCurFilePos > ATOM_SKIP_FILE_POS)) {
            err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
            goto VIDEO_GETTHUMB_EXIT;
        }

        if ((ulAtomLen + 8) > ulBufRemain) {

            MMPS_FS_FileSeek(ulFileID, ulCurFilePos, MMPS_FS_SEEK_SET);
            err = MMPS_FS_FileRead(ulFileID, ubOutBuf, 512, &ulBufRemain);
            if (err && (err != MMP_FS_ERR_EOF)) {
                goto VIDEO_GETTHUMB_EXIT;
            }

            pubBuf = ubOutBuf;
        }
        else {
            pubBuf += ulAtomLen;
            ulBufRemain -= ulAtomLen;
        }

        if (ulBufRemain == 0)
            break;

    } while(!bThumbnailFound);

    if (bThumbnailFound) {
        if (*pulThumbSize <= ulOutBufSize) {
            MMPS_FS_FileSeek(ulFileID, ulCurFilePos, MMPS_FS_SEEK_SET);
            err = MMPS_FS_FileRead(ulFileID, ubOutBuf, *pulThumbSize, &ulBufRemain);
            MMPS_VP_DBG_MSG(0, "Read Thumb Addr [x%x] BUFSZ [x%x] SZ [x%x]\r\n", ubOutBuf, ulOutBufSize, (*pulThumbSize));
        }
        else {
            MMPS_VP_DBG_ERR(1, FG_RED("[ERR] Thumb Size OV %d\r\n"), *pulThumbSize);
        }
    }

VIDEO_GETTHUMB_EXIT:
    MMPS_FS_FileClose(ulFileID);

    return err;
}

MMP_ERR MMPS_VIDPLAY_GetTsThumbnail(  MMP_BYTE    *pbFileName,
                                    MMP_ULONG   ulFileNameLength,
                                    MMP_ULONG   ulOutBufSize,
                                    MMP_UBYTE   **ppubOutBuf,
                                    MMP_ULONG   *pulThumbSize)
{
    MMP_ERR     err = MMP_ERR_NONE;
    MMP_ULONG   ulFileID = 0;
    MMP_UBYTE   *ubOutBuf = *ppubOutBuf;
    MMP_UBYTE   *pubBuf = NULL;
    MMP_UBYTE   *srcBuf = NULL;
    MMP_ULONG   ulCurFilePos = 0, ulBufRemain = 0;
    MMP_ULONG   ulThumbTotalPkt = 0x00000000;
    MMP_UBYTE   ubData[12] = {0};

    *pulThumbSize = 0;

    pubBuf = ubOutBuf;

    if (MMPF_VIDENC_GetVRThumbEn() == MMP_FALSE) {
        err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
        return err;
    }
    
    if (ulOutBufSize < 512) {
        MMPS_VP_DBG_ERR(1, "Buffer is too small to parse thumbnail\r\n");
        return MMP_VIDPSR_ERR_INSUFFICIENT_RESOURCES;
    }

    err = MMPS_FS_FileOpen(pbFileName, ulFileNameLength, "rb", sizeof("rb"), &ulFileID);
    if (err != MMP_ERR_NONE) {
        MMPS_VP_DBG_ERR(1, "Open file %s fail\r\n", pbFileName);
        return err;
    }

    ulCurFilePos = TS_PKT_SIZE;
    MMPS_FS_FileSeek(ulFileID, ulCurFilePos, MMPS_FS_SEEK_SET);
    //(1)Read jpg total sizes in the 1st jpg pkt
    err = MMPS_FS_FileRead(ulFileID, ubData, (PKT_HEAD_SZ+8), &ulBufRemain);
    #if defined(__RTK_OS__)
    gulTsThumbBufSize = MAKE_TAG_BE(ubData[4], ubData[5], ubData[6], ubData[7]);
    if (!gulTsThumbBufSize) {
        gulTsThumbBufSize = ALOC_THUMB_TOTAL_PKT_SIZE;
    }
    #endif
    *pulThumbSize = MAKE_TAG_BE(ubData[8], ubData[9], ubData[10], ubData[11]);
    ulThumbTotalPkt = *pulThumbSize/(TS_PKT_SIZE-PKT_HEAD_SZ) + 1;

    if (ubData[0] == TS_PKT_SYMB && ubData[2] == PID_THUMB) {
        if (*pulThumbSize <= ulOutBufSize && *pulThumbSize) {
            //(2)Read RAW jpg data in the 1st jpg pkt
            err = MMPS_FS_FileRead(ulFileID, ubOutBuf, (TS_PKT_SIZE-PKT_HEAD_SZ-8), &ulBufRemain);
            if (pubBuf[0] != 0xff || pubBuf[1] != 0xd8) {
                MMPS_VP_DBG_MSG(1, FG_RED("xffd8 miss(x%x:x%x)\r\n"), pubBuf[0], pubBuf[1]);
                err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
            }
            else {
                if (!gulTsThumbBuf) {
                    MMP_ULONG* pInUserPtr;
                    MMP_ULONG64 nInMiuAddr;
                    MMP_ULONG64 nlInPhysAddr;
                    CAM_OS_RET_CHK(CamOsDirectMemAlloc("COLLECT_THUMB",
                                                       gulTsThumbBufSize,
                                                       &pInUserPtr,
                                                       &nInMiuAddr,
                                                       &nlInPhysAddr));
                    gulTsThumbBuf = (MMP_ULONG)pInUserPtr;
                    MMPS_VP_DBG_MSG(0, FG_PURPLE("THUMB_BUF:x%x ~ x%x(x%x)%dK\r\n"), gulTsThumbBuf, (gulTsThumbBuf+gulTsThumbBufSize), gulTsThumbBufSize, (gulTsThumbBufSize>>10));
                }
                //(3)Read Remaining: the 2nd jpg pkt to last jpg pkt.
                srcBuf = (MMP_UBYTE *)gulTsThumbBuf;
                err = MMPS_FS_FileRead(ulFileID, srcBuf, (ulThumbTotalPkt*TS_PKT_SIZE), &ulBufRemain);
                MMPF_TSPSR_DmaLineOffsetXfer((gulTsThumbBuf+PKT_HEAD_SZ),
                                             (ubOutBuf+(TS_PKT_SIZE-PKT_HEAD_SZ-8)),
                                             (ulThumbTotalPkt*TS_PKT_SIZE),
                                             (TS_PKT_SIZE - PKT_HEAD_SZ),
                                             (TS_PKT_SIZE),
                                             (TS_PKT_SIZE - PKT_HEAD_SZ),
                                             (TS_PKT_SIZE - PKT_HEAD_SZ));
                if (MMPF_TSPSR_CheckJpgReasonable(ubOutBuf, *pulThumbSize)) {
                    err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
                }
                MMPS_VP_DBG_MSG(0, "Xfer Thumb Addr [x%x] BUFSZ [x%x] SZ [x%x]\r\n", ubOutBuf, ulOutBufSize, (*pulThumbSize));
            }
        }
        else {
            MMPS_VP_DBG_ERR(1, FG_RED("[ERR] Thumb Size OV %d\r\n"), *pulThumbSize);
            err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
        }
    }
    else {
        err = MMP_VIDPSR_ERR_CONTENT_UNKNOWN_DATA;
    }
VIDEO_GETTHUMB_EXIT:
    MMPS_FS_FileClose(ulFileID);

    #if defined(__RTK_OS__)
    if (gulTsThumbBuf) {
        MMPS_VP_DBG_MSG(0, FG_PURPLE("THUMB_BUF RLS(x%x)\r\n"), gulTsThumbBufSize);
        CAM_OS_RET_CHK(CamOsDirectMemRelease(gulTsThumbBuf, gulTsThumbBufSize));
        gulTsThumbBuf = 0x00000000;
    }
    #endif
    
    return err;

}
#endif

MMP_ERR MMPS_VIDPLAY_SetTumbnaiInfo(MMP_ULONG uladdr, MMP_ULONG ulSize)
{
    m_ulThumbnailAddr = uladdr;
    m_ulThumbnailSize = ulSize;
    m_bValidThumbnail = MMP_TRUE;
    return MMP_ERR_NONE;
}

MMP_ERR MMPS_VIDPLAY_GetTumbnaiInfo(MMP_ULONG *uladdr, MMP_ULONG *ulSize)
{
    *uladdr = m_ulThumbnailAddr;
    *ulSize = m_ulThumbnailSize;
    m_bValidThumbnail = MMP_FALSE;
    return (*uladdr) ? MMP_ERR_NONE : MMP_H264D_ERR_NOT_READY;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetFrame
//  Description : Function to get video first frame or current play frame
//------------------------------------------------------------------------------
/** @brief Pre-decode a 3GP file and get the first frame of that video or get the
current play frame.

Get the first or current frame with requested color format and size.

@param[in]  pFileName        The name of the video file to play.
@param[in]  ulFileNameLength File name length
@param[in]  TargetWidth      The width of the requested frame.
@param[in]  TargetHeight     The height of the requested frame.
@param[in]  ColorFormat      MMP_GRAPHICS_COLORDEPTH_16 / MMP_GRAPHICS_COLORDEPTH_YUV422
@param[out] Output           The output starting address and the temp buffer.
@param[out] ulSize           Output:The size of the requested frame.
@param[in]  GetFrameType     MMPS_VIDPLAY_GETFRAME_FIRST / MMPS_VIDPLAY_GETFRAME_CURRENT

@return It reports the status about the result.
*/
MMP_ERR MMPS_VIDPLAY_GetFrame(  MMP_BYTE                    *pFileName,
                                MMP_ULONG                   ulFileNameLength,
                                MMP_USHORT                  *TargetWidth,
                                MMP_USHORT                  *TargetHeight,
                                MMP_GRAPHICS_COLORDEPTH     ColorFormat,
                                MMP_USHORT                  *Output,
                                MMP_ULONG                   *ulSize,
                                MMPS_VIDPLAY_GETFRAME_TYPE  GetFrameType)
{
    MMP_ERR                     error = MMP_ERR_NONE;
    MMP_GRAPHICS_BUF_ATTR       srcBufAttr, dstBufAttr;
    MMP_SCAL_GRAB_CTRL          grabctl;
    MMP_GRAPHICS_RECT           rect;
    MMP_SCAL_FIT_RANGE          fitrange;
    MMP_ULONG                   FrameAddr[3],frame_num;
    MMPS_VIDPLAY_CONFIG         *pConfig;
    MMP_ULONG                   ColorDepth;
    MMPS_VIDPLAY_PRIVATE_DATA   *pVidData;
    MMP_ULONG                   ulMemEnd;
    MMP_PSR_PARSERTYPE          ParserType = MMP_PSR_3GPPARSER;
    MMP_BOOL                    bConvertToARGB = MMP_FALSE;
    MMP_ULONG                   ulTimeOutTick = 16;

    if ( (GetFrameType != MMPS_VIDPLAY_GETFRAME_FIRST) &&
         (GetFrameType != MMPS_VIDPLAY_GETFRAME_CURRENT) ) {
         return MMP_VIDPSR_ERR_PARAMETER;
    }

    if (ColorFormat == MMP_GRAPHICS_COLORDEPTH_16 ||
        ColorFormat == MMP_GRAPHICS_COLORDEPTH_YUV422_UYVY ||
        ColorFormat == MMP_GRAPHICS_COLORDEPTH_YUV422_VYUY ||
        ColorFormat == MMP_GRAPHICS_COLORDEPTH_YUV422_YUYV ||
        ColorFormat == MMP_GRAPHICS_COLORDEPTH_YUV422_YVYU) {
        ColorDepth = 2;
    }
    else if (ColorFormat == MMP_GRAPHICS_COLORDEPTH_24) {
        ColorDepth = 3;
    }
    else if (ColorFormat == MMP_GRAPHICS_COLORDEPTH_32) {
        ColorDepth = 3;
        ColorFormat = MMP_GRAPHICS_COLORDEPTH_24;
        bConvertToARGB = MMP_TRUE;
    }
    else {
        return MMP_VIDPSR_ERR_PARAMETER;
    }

    m_bGetVideoFrame = MMP_TRUE;

    if (GetFrameType == MMPS_VIDPLAY_GETFRAME_FIRST) {

        MMPS_VIDPLAY_GetFileType(pFileName, ulFileNameLength, &ParserType);

        if (m_3gpplayData.bFileOpened == MMP_FALSE) {
            MMPS_VIDPLAY_SCALERCONFIG   ScalerConfig;
            MMPS_VIDPLAY_SetScalerCfg(&ScalerConfig, MMP_FALSE, m_ulTargetThumbWidth, m_ulTargetThumbHeight, 0, 0);
            MMPD_VIDPLAYER_SetGetFrameMode(MMP_TRUE);
            m_ubIsThumbNail = MMP_TRUE;
            error = MMPS_VIDPLAY_Open(pFileName, ulFileNameLength, 0, MMP_TRUE, MMP_FALSE, &ScalerConfig);
            m_ubIsThumbNail = MMP_FALSE;
#if (EN_SPEED_UP_VID & BROWSER_CASE)
            MMPS_VIDPLAY_Thumb_CalculateRatio( m_ContainerInfo.video_info[m_ubVideoCurTrack].width,
                                               m_ContainerInfo.video_info[m_ubVideoCurTrack].height,
                                               m_ulTargetThumbWidth,
                                               m_ulTargetThumbHeight,
                                               TargetWidth,
                                               TargetHeight );
#endif
            MMPD_VIDPLAYER_SetGetFrameMode(MMP_FALSE);

            if (error != MMP_ERR_NONE) {
                goto VIDEO_GETFRAME_EXIT;
            }
        }

        if (!m_3GPInfo.is_video_available) {
            goto VIDEO_GETFRAME_EXIT;
        }

        pConfig = &(m_presetconfig.config[m_3gpplayData.usCurMode]);
        pVidData = &m_3gpplayData;

        ulMemEnd = m_ulMemEndAddr;
    }
    else {
        pConfig = &(m_presetconfig.config[m_3gpplayData.usCurMode]);
        pVidData = &m_3gpplayData;

        ulMemEnd = m_ulMemEndAddr;
    }

    error = MMPD_VIDPLAYER_GetCurrentFrame(&frame_num, &FrameAddr[0], &FrameAddr[1], &FrameAddr[2]);

    if (error != MMP_ERR_NONE) {
        goto VIDEO_GETFRAME_EXIT;
    }

    if (m_bGraphicsScalerEn)
    {
        if (m_bUseScaler) {
            if ((pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_NO_ROTATE) ||
                (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_180))
             {
                srcBufAttr.usWidth  = m_usScaleWidth;
                srcBufAttr.usHeight = m_usScaleHeight;
            }
            else {
                srcBufAttr.usWidth  = m_usScaleHeight;
                srcBufAttr.usHeight = m_usScaleWidth;
            }
        }
        else {
            if ((pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_NO_ROTATE) ||
                (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_180) )
            {
                // Fix image bottom have Green line with video play browser mode and play 1080P file.
                srcBufAttr.usWidth  = pVidData->container.usAllocatedWidth - m_VidCropping.usRight - m_VidCropping.usLeft;
                srcBufAttr.usHeight = pVidData->container.usAllocatedHeight - m_VidCropping.usBottom - m_VidCropping.usTop;
            }
            else if ((pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) ||
                     (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_270) )
            {
                // Fix image bottom have Green line with video play browser mode and play 1080P file.
                srcBufAttr.usWidth  = pVidData->container.usAllocatedHeight - m_VidCropping.usBottom - m_VidCropping.usTop;
                srcBufAttr.usHeight = pVidData->container.usAllocatedWidth  - m_VidCropping.usRight - m_VidCropping.usLeft;
            }
        }
    }
    else
    {
        if ((pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_NO_ROTATE) ||
            (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_180) )
        {
            // Fix image bottom have Green line with video play browser mode and play 1080P file.
            srcBufAttr.usWidth  = pVidData->container.usAllocatedWidth - m_VidCropping.usRight - m_VidCropping.usLeft;
            srcBufAttr.usHeight = pVidData->container.usAllocatedHeight - m_VidCropping.usBottom - m_VidCropping.usTop;
        }
        else if ((pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_90) ||
                 (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_270) )
        {
            // Fix image bottom have Green line with video play browser mode and play 1080P file.
            srcBufAttr.usWidth  = pVidData->container.usAllocatedHeight - m_VidCropping.usBottom - m_VidCropping.usTop;
            srcBufAttr.usHeight = pVidData->container.usAllocatedWidth  - m_VidCropping.usRight - m_VidCropping.usLeft;
        }
    }

    srcBufAttr.usLineOffset = srcBufAttr.usWidth;
    srcBufAttr.colordepth   = MMP_GRAPHICS_COLORDEPTH_YUV420_INTERLEAVE;
    if (m_3gpplayData.usCurMode == VIDEOPLAY_MODE_CCIR) {
        srcBufAttr.colordepth   = MMP_GRAPHICS_COLORDEPTH_YUV422_UYVY;
        srcBufAttr.usLineOffset = srcBufAttr.usWidth * 2;
    }
    srcBufAttr.ulBaseAddr   = FrameAddr[0];
    srcBufAttr.ulBaseUAddr  = FrameAddr[1];
    srcBufAttr.ulBaseVAddr  = FrameAddr[2];

    if (Output == NULL) {
        printc(FG_RED("Get Frame , ulMemEnd : %X\r\n"), ulMemEnd);
        FrameAddr[0] = ulMemEnd;
        FrameAddr[1] = 0;
        FrameAddr[2] = 0;
    }
    else {
        PRINTF("Get Frame , Output : %X\r\n", (MMP_ULONG)Output);
        FrameAddr[0] = (MMP_ULONG)Output;
        FrameAddr[1] = 0;
        FrameAddr[2] = 0;
    }

    dstBufAttr.usWidth         = *TargetWidth;
    dstBufAttr.usHeight        = *TargetHeight;
    dstBufAttr.usLineOffset    = *TargetWidth * ColorDepth;
    dstBufAttr.colordepth      = ColorFormat;
    dstBufAttr.ulBaseAddr      = FrameAddr[0];
    dstBufAttr.ulBaseUAddr     = FrameAddr[1];
    dstBufAttr.ulBaseVAddr     = FrameAddr[2];

    *ulSize = (1 == bConvertToARGB) ? (*TargetWidth) * (*TargetHeight) * 4 : (*TargetWidth) * (*TargetHeight) * ColorDepth;

    fitrange.scalerType     = MMP_SCAL_TYPE_SCALER;
    fitrange.fitmode        = MMP_SCAL_FITMODE_OUT;
    fitrange.ulInWidth      = srcBufAttr.usWidth;
    fitrange.ulInHeight     = srcBufAttr.usHeight;
    fitrange.ulOutWidth     = *TargetWidth;
    fitrange.ulOutHeight    = *TargetHeight;

    fitrange.ulInGrabX      = 1;
    fitrange.ulInGrabY      = 1;
    fitrange.ulInGrabW      = fitrange.ulInWidth;
    fitrange.ulInGrabH      = fitrange.ulInHeight;
    fitrange.ubChoseLit     = 1;
    //MMPF_Scaler_DumpSetting: ulDummyOutPixelX/Y -> need to be initialized.
    //(ulDummyOutPixelX/Y -> Only used in bayer scaler)
    fitrange.ulDummyOutPixelX = fitrange.ulDummyOutPixelY = 0;

    MMPF_Scaler_GetGCDBestFitScale(&fitrange, &grabctl);

    rect.usLeft         = 0;
    rect.usTop          = 0;
    rect.usWidth        = srcBufAttr.usWidth;
    rect.usHeight       = srcBufAttr.usHeight;

    //MMPD_Fctl_RawBuf2IbcBuf(&fctllink, &srcBufAttr, &rect, &dstBufAttr, 1);

    if (m_ulCodecType == MMP_VID_VIDEO_MJPG) {
    }
    else {
        if (m_bGraphicsScalerEn) {
            // Restore Scaler Setting
            if(m_bUseScaler) {

                MMP_ULONG ulRotateWidth;
                MMP_ULONG ulRotateHeight;
                MMP_SHORT sTmpW, sTmpH;

                if (pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_90 ||
                    pVidData->ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_270) {
                    ulRotateWidth = MMPS_Display_GetConfig()->mainlcd.usHeight;
                    ulRotateHeight = MMPS_Display_GetConfig()->mainlcd.usWidth;
                }
                else {
                    ulRotateWidth = MMPS_Display_GetConfig()->mainlcd.usWidth;
                    ulRotateHeight = MMPS_Display_GetConfig()->mainlcd.usHeight;
                }
            }
        }
    }

    if (bConvertToARGB) {

        MMP_ULONG ulRGBEndAddr  = dstBufAttr.ulBaseAddr + ((*TargetWidth) * (*TargetHeight) * 3);
        MMP_ULONG ulARGBEndAddr = dstBufAttr.ulBaseAddr + ((*TargetWidth) * (*TargetHeight) * 4);
        MMP_UBYTE *pubRGB, *pubARGB;
        MMP_ULONG i;

        for(i = 0; i < (*TargetWidth) * (*TargetHeight); i++) {
            ulRGBEndAddr  -= 3;
            ulARGBEndAddr -= 4;
            pubRGB = (MMP_UBYTE *)ulRGBEndAddr;
            pubARGB = (MMP_UBYTE *)ulARGBEndAddr;

            pubARGB[0] = pubRGB[0];
            pubARGB[1] = pubRGB[1];
            pubARGB[2] = pubRGB[2];
            pubARGB[3] = 0xFF;
        }
    }

    /* Get Video thumbnail drirect from DIP component*/
    do {
        error = MMPS_VIDPLAY_GetTumbnaiInfo(Output, ulSize);
        MsSleep(1);
    } while (error && (--ulTimeOutTick > 0));
    if (!ulTimeOutTick) {
        printc(FG_RED("Wait Frame TMO!\r\n"));
    }

    //*Output = m_ulThumbnailAddr;
    //*ulSize = m_ulThumbnailSize;
VIDEO_GETFRAME_EXIT:

    // Stop the video to continue the next playing control command
    if (GetFrameType == MMPS_VIDPLAY_GETFRAME_FIRST) {
        MMPS_VIDPLAY_SetTumbnaiInfo(0, 0);
        MMPS_VIDPLAY_Close();
    }

    m_bGetVideoFrame = MMP_FALSE;
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetFileInfo
//  Description : Function to get video file info
//------------------------------------------------------------------------------
/** @brief Get the common information of current file

@pre The file is parsed
@param[in] szFilename Pointer to specific 3GP file name
@param[in] ulFileNameLength The filename length of the specified 3GP file
@param[in, out] info The pointer to internal container information.
                       Set NULL to get the information from the parser.
                       Otherwise to get the pointer of the info.
@return The status of the function call
*/
MMP_ERR MMPS_VIDPLAY_GetFileInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength, MMPS_VIDEO_CONTAINER_INFO *pInfo)
{
    MMP_ERR                     error;
    MMP_BOOL                    bFileOpened;
    MMPS_VIDPLAY_SCALERCONFIG   cfg;
    MMP_UBYTE                   i = 0;
    MMP_BOOL                    bVideoFormat = 0;

    MMPS_VIDPLAY_SetScalerCfg(&cfg, MMP_FALSE, 0, 0, 0, 0);
    if(pInfo == NULL) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }

    bFileOpened = m_3gpplayData.bFileOpened;

    if ( bFileOpened != MMP_TRUE ) {

        error = MMPS_VIDPLAY_Open(szFilename, ulFileNameLength, 0, MMP_FALSE,MMP_FALSE, &cfg);

        if (error != MMP_ERR_NONE) {
            MMPS_VIDPLAY_Close();
            return error;
        }
    }

    error = MMPD_VIDPSR_GetFileInfo(&m_3GPInfo, MMP_TRUE);

    if (error != MMP_ERR_NONE) {
        return error;
    }

    pInfo->videoTrackNum = m_3GPInfo.videoTrackNum;

    for (i = 0 ; i < m_3GPInfo.videoTrackNum; i++) {

        pInfo->video_info[i].format                 = (MMP_VID_VIDEOTYPE)m_3GPInfo.video_info[i].format;

        if (pInfo->video_info[i].format == MMP_VID_VIDEO_MJPG)
        {
            pInfo->video_info[i].bitrate            = m_3GPInfo.video_info[i].bitrate;
            pInfo->video_info[i].width              = m_3GPInfo.video_info[i].width;
            pInfo->video_info[i].height             = m_3GPInfo.video_info[i].height;
            pInfo->video_info[i].fps                = m_3GPInfo.video_info[i].fps;
            pInfo->video_info[i].cropping_left      = 0;
            pInfo->video_info[i].cropping_right     = 0;
            pInfo->video_info[i].cropping_top       = 0;
            pInfo->video_info[i].cropping_bottom    = 0;
            pInfo->video_info[i].total_video_time   = m_3GPInfo.video_info[i].total_video_time;
            pInfo->video_info[i].total_keyframe_num = m_3GPInfo.video_info[i].total_keyframe_num;

            pInfo->audio_info.format             = (MMP_VID_AUDIOTYPE)m_3GPInfo.audio_info.format;
            pInfo->audio_info.bitrate            = m_3GPInfo.audio_info.bitrate;
            pInfo->audio_info.sampling_rate      = m_3GPInfo.audio_info.sampling_rate;
            pInfo->audio_info.channel_nums       = m_3GPInfo.audio_info.channel_nums;
            pInfo->audio_info.total_audio_time   = m_3GPInfo.audio_info.total_audio_time;

            pInfo->is_video_available[i]            = m_3GPInfo.is_video_available[i];
            pInfo->is_audio_available            = m_3GPInfo.is_audio_available;
            pInfo->file_size                     = m_3GPInfo.file_size;
            pInfo->total_file_time               = m_3GPInfo.total_file_time;
            pInfo->is_video_seekable[i]             = m_3GPInfo.is_video_seekable[i];
        }
        else
        {
            pInfo->video_info[i].bitrate            = m_3GPInfo.video_info[i].bitrate;
            pInfo->video_info[i].width              = m_3GPInfo.video_info[i].width;
            pInfo->video_info[i].height             = m_3GPInfo.video_info[i].height;
            pInfo->video_info[i].fps                = m_3GPInfo.video_info[i].fps;
            pInfo->video_info[i].cropping_left      = m_3GPInfo.video_info[i].cropping_left;
            pInfo->video_info[i].cropping_right     = m_3GPInfo.video_info[i].cropping_right;
            pInfo->video_info[i].cropping_top       = m_3GPInfo.video_info[i].cropping_top;
            pInfo->video_info[i].cropping_bottom    = m_3GPInfo.video_info[i].cropping_bottom;
            pInfo->video_info[i].total_video_time   = m_3GPInfo.video_info[i].total_video_time;
            pInfo->video_info[i].total_keyframe_num = m_3GPInfo.video_info[i].total_keyframe_num;

            pInfo->audio_info.format             = (MMP_VID_AUDIOTYPE)m_3GPInfo.audio_info.format;
            pInfo->audio_info.bitrate            = m_3GPInfo.audio_info.bitrate;
            pInfo->audio_info.sampling_rate      = m_3GPInfo.audio_info.sampling_rate;
            pInfo->audio_info.channel_nums       = m_3GPInfo.audio_info.channel_nums;
            pInfo->audio_info.total_audio_time   = m_3GPInfo.audio_info.total_audio_time;

            pInfo->is_video_available[i]         = m_3GPInfo.is_video_available[i];
            pInfo->is_audio_available            = m_3GPInfo.is_audio_available;
            pInfo->file_size                     = m_3GPInfo.file_size;
            pInfo->total_file_time               = m_3GPInfo.total_file_time;
            pInfo->is_video_seekable[i]          = m_3GPInfo.is_video_seekable[i];

            if (pInfo->video_info[i].format == MMP_VID_VIDEO_H264) {
                bVideoFormat = MMP_TRUE;
            }
        }
    }

    MMPD_VIDPLAYER_SetVideoFormat(bVideoFormat);
    MMPD_VIDPLAYER_GetSupportedFormat((MMPD_3GP_AUDIOTYPE*)&m_3gpplayData.supported_audio_type,
                                      (MMPD_3GP_VIDEOTYPE*)&m_3gpplayData.supported_video_type);

    if (bFileOpened != MMP_TRUE ) {
        MMPS_VIDPLAY_Close();
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetUserdataInfo
//  Description : Function to get video UDATA info
//------------------------------------------------------------------------------
/** @brief Get the udta atom information of current file

@pre The file was parsed
@param[out] pUdta information of all data in UDTA atom

@return The status of the function call
*/
MMP_ERR MMPS_VIDPLAY_GetUserDataInfo(MMP_USERDATA_TAG **pUdta)
{
    *pUdta = (MMP_USERDATA_TAG *)m_3gpplayData.ulUDTAAddress;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetVideoAvailable
//  Description : Function to get if video is available or not
//------------------------------------------------------------------------------
/** @brief Check if video chunks are available in the file

@param[out] bAvail video chunks are available or not

@return The status of the function call
*/
MMP_ERR MMPS_VIDPLAY_GetVideoAvailable(MMP_BOOL *bAvail)
{
    *bAvail = m_3GPInfo.is_video_available[m_VideoTrack];
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetContainerInfo
//  Description : Function to get video container info
//------------------------------------------------------------------------------
/** @brief Get the common information of current file in container


@param[in]          szFilename          Pointer to specific video file name
@param[in]          ulFileNameLength    The filename length of the specified video file
@param[in, out]     info                The pointer to internal container information.
@return The status of the function call
*/
MMP_ERR MMPS_VIDPLAY_GetContainerInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength, MMPS_VIDEO_CONTAINER_INFO *info)
{
    MMP_ERR     error;
    MMP_UBYTE   i = 0;
    MMP_ULONG   ulTempAddr;

    MMPS_VIDPLAY_AllocFwEnd(MMPS_VIDPLAY_ALOC_BROW);
    ulTempAddr = gulAlocMem4Rls[MMPS_VIDPLAY_ALOC_BROW];

    if (info == NULL) {
        return MMP_3GPPLAY_ERR_PARAMETER;
    }
    MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_CACHE, 0, 0, (const MMP_ULONG)ulTempAddr, 0, 0, 0);

    MEMSET(&m_ContainerInfo, 0, sizeof(m_ContainerInfo));

    error = MMPD_3GPPSR_GetContainerInfo(szFilename, ulFileNameLength, &m_ContainerInfo);

    if (error != MMP_ERR_NONE) {
        #if  defined( __RTK_OS__ )
        MMPS_VIDPLAY_ReleaseFwEnd();
        #endif
        return error;
    }

    info->videoTrackNum = m_ContainerInfo.videoTrackNum;

    for (i = 0; i < info->videoTrackNum; i++) {

        info->video_info[i].format              = (MMP_VID_VIDEOTYPE)m_ContainerInfo.video_info[i].format;
        info->video_info[i].bitrate             = m_ContainerInfo.video_info[i].bitrate;
        info->video_info[i].width               = m_ContainerInfo.video_info[i].width;
        info->video_info[i].height              = m_ContainerInfo.video_info[i].height;
        info->video_info[i].fps                 = m_ContainerInfo.video_info[i].fps;
        info->video_info[i].cropping_left       = m_ContainerInfo.video_info[i].cropping_left;
        info->video_info[i].cropping_right      = m_ContainerInfo.video_info[i].cropping_right;
        info->video_info[i].cropping_top        = m_ContainerInfo.video_info[i].cropping_top;
        info->video_info[i].cropping_bottom     = m_ContainerInfo.video_info[i].cropping_bottom;
        info->video_info[i].total_video_time    = m_ContainerInfo.video_info[i].total_video_time;
        info->video_info[i].total_keyframe_num  = m_ContainerInfo.video_info[i].total_keyframe_num;
        info->video_info[i].fccHandler          = m_ContainerInfo.video_info[i].fccHandler;

        info->audio_info.format                 = (MMP_VID_AUDIOTYPE)m_ContainerInfo.audio_info.format;
        info->audio_info.bitrate                = m_ContainerInfo.audio_info.bitrate;
        info->audio_info.sampling_rate          = m_ContainerInfo.audio_info.sampling_rate;
        info->audio_info.channel_nums           = m_ContainerInfo.audio_info.channel_nums;
        info->audio_info.total_audio_time       = m_ContainerInfo.audio_info.total_audio_time;

        info->is_video_available[i]             = m_ContainerInfo.is_video_available[i];
        info->is_audio_available                = m_ContainerInfo.is_audio_available;
        info->file_size                         = m_ContainerInfo.file_size;
        info->total_file_time                   = m_ContainerInfo.total_file_time;
        info->is_video_seekable[i]              = m_ContainerInfo.is_video_seekable[i];
        info->drm_type                          = m_ContainerInfo.drm_type;
    }
    #if  defined( __RTK_OS__ )
    MMPS_VIDPLAY_ReleaseFwEnd();
    #endif

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetPlaySpeed
//  Description : Function to set fast forward or backward
//------------------------------------------------------------------------------
/** @brief Play video file in fast forward or backward.

Both FF and FW use this function.
@param[in] mode   Mode of play speed, forward or backward or normal playback.
@param[in] sSpeed Only use in fast forward or backward. 100 means jump to next key frame,
                  200 means jump to next 2 frames...so on.
@return It reports the status about the command result.
@retval MMP_M_ERR_BAD_PARAMETER The video doesn't support fast forward.
        Which means its number of key frames is less than a certain number.
*/
MMP_ERR MMPS_VIDPLAY_SetPlaySpeed(MMPS_VIDPLAY_PLAYSPEED_MODE mode, MMP_SHORT sSpeed)// MMPF_Player_SetPlaySpeed
{
    MMP_ERR     error;
    MMP_M_STATE state;
    MMP_ULONG   audio_samplerate;
    #if (CHANGE_VIDEO_SPEED_NO_GAP == 1)
    MMP_BOOL    bNeedPause = MMP_FALSE;
    #endif

    if ( mode >= MMPS_VIDPLAY_PLAYSPEED_MAX)
    {
        return MMP_VIDPSR_ERR_NOT_IMPLEMENTED;
    }

    if( mode == m_PlaySpeed ) {
        if(mode == MMPS_VIDPLAY_PLAYSPEED_NORMAL)
            return MMP_ERR_NONE;
        if(mode == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || mode == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD){
            error = MMPD_VIDPLAYER_SetSearchSpeed(mode, MMP_TRUE,sSpeed);
            return error;
        }
    }

    error = MMPS_VIDPLAY_GetState(&state);

    if (state == MMP_M_STATE_LOADED) {
        return MMP_ERR_NONE;
    }
    if(mode == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || mode == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD) {
        if(!m_3GPInfo.is_video_available)
            return MMP_3GPPLAY_ERR_PARAMETER;
    }

    #if (CHANGE_VIDEO_SPEED_NO_GAP == 1)
    if(m_PlaySpeed == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || m_PlaySpeed == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD){
        bNeedPause = MMP_TRUE;
    } else if(mode == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || mode == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD){
        bNeedPause = MMP_TRUE;
    }
    #endif

    //PAUSE
    #if (CHANGE_VIDEO_SPEED_NO_GAP == 1)
    if ((state == MMP_M_STATE_EXECUTING) && (bNeedPause == MMP_TRUE))
    #else
    if (state == MMP_M_STATE_EXECUTING)
    #endif
    {
        error = MMPS_VIDPLAY_Pause();
        if (error != MMP_ERR_NONE) {
            return error;
        }
    }

    if (mode == MMPS_VIDPLAY_PLAYSPEED_NORMAL) {
        error = MMPD_VIDPLAYER_SetPlaySpeed(mode, MMP_TRUE, sSpeed);
        if(error != MMP_ERR_NONE) {
            return error;
        }
        #if (CHANGE_AV_SPEED)
        if(m_PlaySpeed == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || m_PlaySpeed == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD)
        #endif
        {
            error = m_sParser.MMPD_VIDPSR_Predecode(MMP_TRUE, MMP_TRUE, MMP_TRUE, &audio_samplerate );
        }
    }
    else {
        error = MMPD_VIDPLAYER_SetPlaySpeed(mode, MMP_TRUE, sSpeed);
        if(error != MMP_ERR_NONE) {
            return error;
        }
        if(mode == MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD || mode == MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD) {
            error = m_sParser.MMPD_VIDPSR_Predecode(MMP_TRUE, MMP_FALSE, MMP_TRUE, &audio_samplerate );
        }
    }

    m_PlaySpeed = mode;

    if (error != MMP_ERR_NONE) {
        return error;
    }

    //RESUME
    #if (CHANGE_VIDEO_SPEED_NO_GAP == 1)
    if ((state == MMP_M_STATE_EXECUTING) && (bNeedPause == MMP_TRUE)) {
        error = MMPS_VIDPLAY_Resume();
        if (error != MMP_ERR_NONE) {
            return error;
        }
    }
    #endif
    #if (CHANGE_VIDEO_SPEED_NO_GAP == 0)
    if (state == MMP_M_STATE_EXECUTING) {
        error = MMPS_VIDPLAY_Resume();
        if (error != MMP_ERR_NONE) {
            return error;
        }
    }
    #endif

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetVideoDecodeEnable
//  Description : Function to set video decode enable or not
//------------------------------------------------------------------------------
/** @brief Enable/Disable video decode

@param[in] bEnable Enable/Disable
@retval MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_SetVideoDecodeEnable(MMP_BOOL bEnable)
{
    return MMPD_VIDPLAYER_SetVideoDecodeEnable(bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetVideoRefreshEnable
//  Description : Function to set video refresh enable or not
//------------------------------------------------------------------------------
/** @brief Enable/Disable video refresh

@param[in] bEnable Enable/Disable
@retval MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_SetVideoRefreshEnable(MMP_BOOL bEnable)
{
    return MMPD_VIDPLAYER_SetVideoRefreshEnable(bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetDisplayMode
//  Description : Function to set display mode
//------------------------------------------------------------------------------
/** @brief Set current play mode, stardard mode, full screen mode, zoom mode or
actual mode

@param[in] usMode       The play mode index. Set VIDEOPLAY_MODE_MAX means no change
@param[in] ubRotatetype Rotate type: no rotate, 90 , 180 or 270. Set
MMP_DISPLAY_ROTATE_MAX means no change
@param[in] bRedraw      Redraw the video frame or not
@param[in] pConfig      User define config. If want to use default setting, set null
@retval MMP_3GPPLAY_ERR_PARAMETER The mode is out of range
*/
MMP_ERR MMPS_VIDPLAY_SetDisplayMode(const MMP_USHORT usMode, const MMP_UBYTE ubRotatetype, MMP_BOOL bRedraw, MMPS_VIDPLAY_DISPLAY *pConfig, MMPS_VIDPLAY_SCALERCONFIG *pScalerConfig)
{
    MMP_ERR                     error;
    MMPS_VIDPLAY_BUFFERADDRESS  *pBuffers = &(m_VideoBufInfo);
    MMP_M_STATE                 state;
    MMP_BOOL                    bSetRotate = MMP_TRUE, bSetDisplay = MMP_TRUE;
    MMP_ULONG                   ulOldDMABufUsed = 0;

    if ((usMode >= VIDEOPLAY_MODE_MAX) && (pConfig == NULL)) {
        bSetDisplay = MMP_FALSE;
    }

    if(usMode < VIDEOPLAY_MODE_MAX){
        if((usMode == m_3gpplayData.usCurMode) && (pConfig == NULL)){
            if(m_DisplayConfig.usWidth == m_presetconfig.config[m_3gpplayData.usCurMode].display.usWidth &&
               m_DisplayConfig.usHeight == m_presetconfig.config[m_3gpplayData.usCurMode].display.usHeight) {
                bSetDisplay = MMP_FALSE;
            }
        } else {
            m_3gpplayData.usCurMode = usMode;
        }
    }

    if((ubRotatetype >= MMP_DISPLAY_ROTATE_MAX) || (ubRotatetype == m_3gpplayData.ubRotatetype)){
        bSetRotate = MMP_FALSE;
    }
    else {
        m_3gpplayData.ubRotatetype = ubRotatetype;
    }

    if(pScalerConfig != NULL)
        bSetDisplay = MMP_TRUE;
    if(!bSetDisplay && !bSetRotate)
        return MMP_ERR_NONE;

    if(bSetDisplay){
        if(pConfig == NULL){
            m_DisplayConfig.usX = m_presetconfig.config[m_3gpplayData.usCurMode].display.usX;
            m_DisplayConfig.usY = m_presetconfig.config[m_3gpplayData.usCurMode].display.usY;
            m_DisplayConfig.usWidth = m_presetconfig.config[m_3gpplayData.usCurMode].display.usWidth;
            m_DisplayConfig.usHeight = m_presetconfig.config[m_3gpplayData.usCurMode].display.usHeight;
        } else {
            m_DisplayConfig.usX = pConfig->usX;
            m_DisplayConfig.usY = pConfig->usY;
            m_DisplayConfig.usWidth = pConfig->usWidth;
            m_DisplayConfig.usHeight = pConfig->usHeight;
        }
    }

    error = MMPS_VIDPLAY_GetState(&state);
    if (error != MMP_ERR_NONE) {
        return error;
    }

    if (state != MMP_M_STATE_LOADED)
    {
        // Config Display
        if(bSetRotate || pScalerConfig != NULL){

            MMP_USHORT ulRotateWidth = 0, ulRotateHeight = 0;

            ulOldDMABufUsed = m_3gpplayData.DMAbufferUsed;
            if (m_3gpplayData.ubRotatetype == MMP_DISPLAY_ROTATE_NO_ROTATE)
                m_3gpplayData.DMAbufferUsed        = 0;
            else
                m_3gpplayData.DMAbufferUsed        = m_presetconfig.ulRotateDMABufNum;

            if (m_bGraphicsScalerEn)
            {
                if(pScalerConfig != NULL && pScalerConfig->bUseScaler == MMP_FALSE) {
                    m_bUseScaler = MMP_FALSE;
                    m_usScaleWidth = 0;
                    m_usScaleHeight = 0;
                }
                else {
                    if(m_3gpplayData.ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_90 ||
                        m_3gpplayData.ubRotatetype == MMP_DISPLAY_ROTATE_RIGHT_270) {
                        if(pScalerConfig != NULL && pScalerConfig->ulOutWidth != 0 && pScalerConfig->ulOutHeight != 0) {
                            ulRotateWidth = pScalerConfig->ulOutHeight;
                            ulRotateHeight = pScalerConfig->ulOutWidth;
                        } else {
                            ulRotateWidth = MMPS_Display_GetConfig()->mainlcd.usHeight;
                            ulRotateHeight = MMPS_Display_GetConfig()->mainlcd.usWidth;
                        }
                    } else {
                        if(pScalerConfig != NULL && pScalerConfig->ulOutWidth != 0 && pScalerConfig->ulOutHeight != 0) {
                            ulRotateWidth = pScalerConfig->ulOutWidth;
                            ulRotateHeight = pScalerConfig->ulOutHeight;
                        } else {
                            ulRotateWidth = MMPS_Display_GetConfig()->mainlcd.usWidth;
                            ulRotateHeight = MMPS_Display_GetConfig()->mainlcd.usHeight;
                        }
                    }
                    m_bUseScaler = MMP_FALSE;
                }

                if(m_usScaleWidth != 0 && m_usScaleHeight != 0){
                    MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_FRAME_RESOLUTION, m_usScaleWidth, m_usScaleHeight,
                                       m_3gpplayData.container.usAllocatedWidth, m_3gpplayData.container.usAllocatedHeight, 0, 0);
                } else {
                    MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_FRAME_RESOLUTION, m_3gpplayData.container.usAllocatedWidth, m_3gpplayData.container.usAllocatedHeight,
                                       m_3gpplayData.container.usAllocatedWidth, m_3gpplayData.container.usAllocatedHeight, 0, 0);
                }

                m_3gpplayData.ulDisplayWidth = DISPLAY_MAX_WIDTH;
                m_3gpplayData.ulDisplayHeight = DISPLAY_MAX_HEIGHT;
            }
        }

        if ( m_bAHCConfig ) {
            error = MMPS_VIDPLAY_ConfigDisplay(
                                     m_ulVideoStartX,
                                     m_ulVideoStartY,
                                     m_ulVideoWidth,
                                     m_ulVideoHeight,
                                     m_3gpplayData.ubRotatetype,
                                     m_presetconfig.config[m_3gpplayData.usCurMode].display.bMirror,
                                     m_presetconfig.config[m_3gpplayData.usCurMode].display.bFullyFilled,
                                     m_presetconfig.config[m_3gpplayData.usCurMode].display.outputpanel,
                                     m_presetconfig.config[m_3gpplayData.usCurMode].display.bKeepRatio,
                                     m_presetconfig.config[m_3gpplayData.usCurMode].display.bUseScaler);

        }
        else {
            error = MMPS_VIDPLAY_ConfigDisplay(  m_DisplayConfig.usX,
                                                 m_DisplayConfig.usY,
                                                 m_DisplayConfig.usWidth,
                                                 m_DisplayConfig.usHeight,
                                                 m_3gpplayData.ubRotatetype,
                                                 m_presetconfig.config[m_3gpplayData.usCurMode].display.bMirror,
                                                 m_presetconfig.config[m_3gpplayData.usCurMode].display.bFullyFilled,
                                                 m_presetconfig.config[m_3gpplayData.usCurMode].display.outputpanel,
                                                 m_presetconfig.config[m_3gpplayData.usCurMode].display.bKeepRatio,
                                                 m_presetconfig.config[m_3gpplayData.usCurMode].display.bUseScaler
                                                 );
        }

        if(error != MMP_ERR_NONE) {

            if(bSetRotate || pScalerConfig != NULL)
                m_3gpplayData.DMAbufferUsed = ulOldDMABufUsed;
            return error;
        }

        if(bSetRotate || pScalerConfig != NULL){

            if (m_bGraphicsScalerEn)
            {
                MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_SCALER_BUFFER, pBuffers->usBufferUsed, pBuffers->ulScalerBufNum,
                                       m_bUseScaler, pBuffers->ulScalerStartAddr, (MMP_USHORT)m_3gpplayData.ulDisplayWidth, (MMP_USHORT)m_3gpplayData.ulDisplayHeight);

                MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_VIDEO_BUFFER, pBuffers->usBufferUsed, m_3gpplayData.DMAbufferUsed,
                                       m_3gpplayData.ubRotatetype, pBuffers->ulDMAStartAddr, 0, 0);
            }
            else
            {
                MMPD_VIDPSR_SetParameters(MMPD_VIDPLAY_PARAMETER_VIDEO_BUFFER, pBuffers->usBufferUsed, m_3gpplayData.DMAbufferUsed,
                                          m_3gpplayData.ubRotatetype, pBuffers->ulDMAStartAddr,0,0);
            }
        }

        if(bRedraw){
            if(bSetRotate){
                MMPD_VIDPLAYER_Redraw();
            }
            else {
                MMPD_VIDPLAYER_RedrawLastRefresh();
            }
        }
    }
    else {
        MMPD_VIDPLAYER_SetActivePanel(m_presetconfig.config[m_3gpplayData.usCurMode].display.outputpanel, m_defaultWinID);
    }

    return error;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetCurrentTrack
//  Description : Function to set video track
//------------------------------------------------------------------------------
/** @brief Select the video track for play, need to call before MMPS_VIDPLAY_Open

@param[in] ubCurrentTrack Can set to 0 for track 0, 1 for track 1. If video have only one track and set 1. Auto change to track 0.
@retval MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_SetCurrentTrack(MMP_UBYTE ubCurrentTrack)
{
    m_VideoTrack = ubCurrentTrack;
    m_ubVideoCurTrack = ubCurrentTrack;
    //printc(FG_YELLOW("MMPS_VIDPLAY_SetCurrentTrack(%x)\r\n"), ubCurrentTrack);
    return MMP_ERR_NONE;
}
#if 0
void _____Property_Interface_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_EnableGraphicsScaler
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set graphics to scaler enable.

The function set graphics to scaler enable.

@param[in] bEnable enable graphics to scaler.
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_EnableGraphicsScaler(MMP_BOOL bEnable)
{
    m_bGraphicsScalerEn = bEnable;
    MMPD_VIDPLAYER_EnableGraphicsScaler(bEnable);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetScaleOutMaxSize
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set graphics to scaler out max resolution.

The function set graphics to scaler out max resolution. Can use this function to
reduce memory usage in some case.

@param[in] usWidth max scaler output width.
@param[in] usHeight max scaler output height.
@return MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_SetScaleOutMaxSize(MMP_USHORT usWidth, MMP_USHORT usHeight)
{
    m_MaxScaleOutWidth = usWidth;
    m_MaxScaleOutHeight = usHeight;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetMemoryMode
//  Description :
//------------------------------------------------------------------------------
/** @brief Set current play mode

@param[in] bMemMode The memory mode index. The index is defined in ait_config.h
@retval MMP_3GPPLAY_ERR_UNSUPPORTED_SETTING The mode is out of range
*/
MMP_ERR MMPS_VIDPLAY_SetMemoryMode(MMP_BOOL bMemMode)
{
    if(bMemMode)
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_MEM);
    else
        MMPD_AUDIO_SetPlayPath(MMPD_AUDIO_PLAY_FROM_CARD);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_InitConfig
//  Description : Function to initial m_3gpplayData and m_DisplayConfig
//------------------------------------------------------------------------------
/** @brief Initial the video player to use certain configuration.

@param[in] pConfig The pointer to a MMPS_SYSTEM_VIDEODECMODES.
@retval MMP_ERR_NONE Success
*/
MMP_ERR MMPS_VIDPLAY_InitConfig(MMPS_SYSTEM_VIDEODECMODES* pConfig)
{
    m_3gpplayData.file_validation       = MMP_VID_UNKNOWN_INVALIDATION;
    m_3gpplayData.bUseExternalMemory    = MMP_FALSE;
    m_3gpplayData.usCurMode             = pConfig->videoplay_mode;
    m_3gpplayData.deblock_type          = pConfig->deblock_type;
    m_3gpplayData.bFileOpened           = MMP_FALSE;
    m_3gpplayData.bConfigDuringPlaying  = MMP_FALSE;
    m_3gpplayData.ulDramMallocAddr      = NULL;
    m_3gpplayData.ubRotatetype          = MMP_DISPLAY_ROTATE_NO_ROTATE;

    m_defaultWinID                      = pConfig->window_type;

    m_DisplayConfig.usX = pConfig->config[m_3gpplayData.usCurMode].display.usX;
    m_DisplayConfig.usY = pConfig->config[m_3gpplayData.usCurMode].display.usY;
    m_DisplayConfig.usWidth = pConfig->config[m_3gpplayData.usCurMode].display.usWidth;
    m_DisplayConfig.usHeight = pConfig->config[m_3gpplayData.usCurMode].display.usHeight;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetDisplayType
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetDisplayType(MMP_DISPLAY_OUTPUT_SEL displaypanel)
{
    m_displaypanel = displaypanel;

    if (m_displaypanel == MMP_DISPLAY_SEL_HDMI)
    {
        if(MMPS_Display_GetConfig()->hdmi.ubOutputMode == MMP_HDMI_OUTPUT_1920X1080I){
            m_bIsInterlace = MMP_TRUE;

            MMPD_VIDPLAYER_SetHDMIInterface(MMP_TRUE, 74250);
        }
        else {
            m_bIsInterlace = MMP_FALSE;

            switch (MMPS_Display_GetConfig()->hdmi.ubOutputMode) {
            case MMP_HDMI_OUTPUT_640X480P:
                MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 25200);
                break;
            case MMP_HDMI_OUTPUT_720X480P:
            case MMP_HDMI_OUTPUT_720X576P:
                MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 27000);
                break;
            case MMP_HDMI_OUTPUT_1280X720P:
            case MMP_HDMI_OUTPUT_1280X720P_50FPS:
            case MMP_HDMI_OUTPUT_1920X1080P_30FPS:
            case MMP_HDMI_OUTPUT_1920X1080I:
            case MMP_HDMI_OUTPUT_1920X1080P_50FPS:
                MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 74250);
                break;
            case MMP_HDMI_OUTPUT_1920X1080P:
            case MMP_HDMI_OUTPUT_1280X720P_100FPS:
            case MMP_HDMI_OUTPUT_1280X720P_120FPS:
                MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 148500);
                break;
            default:
                MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 74250);
                return MMP_VIDPSR_ERR_PARAMETER;
                break;
            }
        }
    }
    else {
        m_bIsInterlace = MMP_FALSE;
        MMPD_VIDPLAYER_SetHDMIInterface(MMP_FALSE, 0);
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetSearchFPS
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetSearchFPS(MMP_ULONG ulDuration)
{
    return MMPD_VIDPLAYER_SetSearchFPS(ulDuration);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurFileDuration
//  Description : Get the file duration in the parsed card mode file
//------------------------------------------------------------------------------
/** @brief Get the file duration in the parsed card mode file
 *
 * @param[out] ulDuration The pointer to the duration
 * @return MMP_ERR_NONE;
 */
MMP_ERR MMPS_VIDPLAY_GetCurFileDuration(MMP_ULONG *ulDuration)
{
    *ulDuration = m_3GPInfo.total_file_time;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurFileFps
//  Description : Get the file duration in the parsed card mode file
//------------------------------------------------------------------------------
/** @brief Get the file FPS for video in the parsed card mode file
 *
 * @param[out] ulFps The pointer to the FPS
 * @return MMP_ERR_NONE;
 */
MMP_ERR MMPS_VIDPLAY_GetCurFileFps(MMP_ULONG *ulFps)
{
    *ulFps = m_3GPInfo.video_info[m_VideoTrack].fps;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurAudioBuffer
//  Description :
//------------------------------------------------------------------------------
/** @brief Get current audio buffer size

@post MMPS_VIDPLAY_ConfigMemory() must be called
@param[out] ulAddr The starting address of the audio
@param[out] ulSize The size the buffer
*/
MMP_ERR MMPS_VIDPLAY_GetCurAudioBuffer(MMP_ULONG *ulAddr, MMP_ULONG *ulSize)
{
    *ulAddr = m_VideoBufInfo.ulAudioInStart;
    *ulSize = m_VideoBufInfo.ulAudioInSize;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetConfig
//  Description : Function to get configuration
//------------------------------------------------------------------------------
/** @brief Get detailed config

@return The pointer of the detailed config
Refer @ref MMPS_SYSTEM_VIDEODECMODES for more detailed return value description.
*/
MMPS_SYSTEM_VIDEODECMODES* MMPS_VIDPLAY_GetConfig(void)
{
    return &m_presetconfig;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurrentTime
//  Description : Function to get current play time
//------------------------------------------------------------------------------
/** @brief Get the current time of the player

@param[out] pulTime The pointer to the current time in millisecond
@return The status of the function call from the firmware
*/
MMP_ERR MMPS_VIDPLAY_GetCurrentTime(MMP_ULONG *pulTime)
{
    return MMPD_VIDPLAYER_GetCurrentTime(pulTime);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetSBCTime
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetSBCTime(MMP_ULONG ulTime)
{
    MMPD_VIDPLAYER_SetSBCTime(ulTime);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetState
//  Description : Function to get player state
//------------------------------------------------------------------------------
/** @brief Get the current status of the player

@param[out] pState The pointer to the current status of the player
@return The status of the function call from the firmware
*/
MMP_ERR MMPS_VIDPLAY_GetState(MMP_M_STATE *pState)
{
    MMP_M_STATE state;
    MMP_ERR     error;

    error = MMPD_VIDPLAYER_GetState(&state);
    *pState = state;
    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurDisplayMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_GetCurDisplayMode(MMP_ULONG *ulMode)
{
    *ulMode = m_3gpplayData.usCurMode;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetMemoryEnd
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_GetMemoryEnd(MMP_ULONG *ulMemoryAddr)
{
    *ulMemoryAddr = m_ulVideoPlayMemoryEnd;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetDisplayWindow
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetDisplayWindow(MMP_BOOL Use,MMP_USHORT StartX,MMP_USHORT StartY,MMP_USHORT Width,MMP_USHORT Height)
{
    m_bAHCConfig    = Use;
    m_ulVideoStartX = StartX;
    m_ulVideoStartY = StartY;
    m_ulVideoWidth  = Width;
    m_ulVideoHeight = Height;

    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetCurrentTrack
//  Description : Function to set video track
//------------------------------------------------------------------------------
/** @brief Select the video track for play, need to call before MMPS_VIDPLAY_Open

@param[in] ubCurrentTrack Can set to 0 for track 0, 1 for track 1. If video have only one track and set 1. Auto change to track 0.
@retval MMP_ERR_NONE
*/
MMP_ERR MMPS_VIDPLAY_GetCurrentTrack(MMP_ULONG *ulCurrentTrackNo)
{
    *ulCurrentTrackNo = m_ubVideoCurTrack;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_AllowAVIListModifyAtom
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Decode for Allowing LIST Atom for AVI format.

 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_VIDPLAY_AllowAVIListModifyAtom(MMP_BOOL bEnable, MMP_BYTE *pStr)
{
    return MMPD_VIDPLAYER_AllowAVIListModifyAtom(bEnable, pStr);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetColorFmt
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Force fmt for Color format.

 @retval MMP_ERR_NONE Success.
*/
MMP_ERR MMPS_VIDPLAY_SetColorFmt(MMP_ULONG ulFmt)
{
    if (ulFmt == VID_FMT_NV12) {
        RTNA_DBG_Str0(FG_YELLOW("Set CFmt(0: NV12)"));
    }
    else if (ulFmt == VID_FMT_I420) {
        RTNA_DBG_Str0(FG_YELLOW("Set CFmt(1: I420)"));
    }
    else if (ulFmt == VID_FMT_YUV422) {
        RTNA_DBG_Str0(FG_YELLOW("Set CFmt(2: YUV422)"));
    }
    RTNA_DBG_Str0("\r\n");
    return MMPD_VIDPLAYER_SetColorFmt(ulFmt);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetColorFmt
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Force fmt for Color format.

 @retval MMP_ERR_NONE Success.
*/
MMP_ULONG MMPS_VIDPLAY_GetColorFmt(void)
{
    MMP_ULONG ulFmt;
    MMPD_VIDPLAYER_GetColorFmt(&ulFmt);
    return ulFmt;
}

#if (EN_SPEED_UP_VID & BROWSER_CASE)
MMP_ERR MMPS_VIDPLAY_Thumb_CalculateRatio(  MMP_ULONG ulImageWidth, MMP_ULONG ulImageHeight,
                                            MMP_ULONG ulTargetWidth, MMP_ULONG ulTargetHeight,
                                            MMP_USHORT* puwThumbWidth, MMP_USHORT* puwThumbHeight)
{
    MMP_BOOL  bSquarePixel;
    MMP_ULONG ulPixelWidth;
    MMP_ULONG uiWidth, uiHeight;

#if defined(CCIR656_OUTPUT_ENABLE)&&(CCIR656_OUTPUT_ENABLE)
    //AHC_DISPLAY_OUTPUTPANEL sOutputDevice;
    //AHC_GetDisplayOutputDev(&sOutputDevice);

    if(m_displaypanel == MMP_DISPLAY_SEL_CCIR){
        *puwThumbWidth = ulTargetWidth;
        *puwThumbHeight = ulTargetHeight;
        return MMP_ERR_NONE;
    }
#endif

    MMPS_Display_CheckPixelRatio(MMP_DISPLAY_PRM_CTL, &bSquarePixel, &ulPixelWidth);

    uiWidth = ulTargetHeight * ulImageWidth / ulImageHeight;

    // If not square pixel, calculate resolution domain value.
    if (bSquarePixel == MMP_FALSE)
    {
        uiWidth = (uiWidth << 16) / ulPixelWidth;
    }

    // Make sure width is less equal to uiTargetWidth
    if (uiWidth > ulTargetWidth)
    {
        uiWidth  = ulTargetWidth;
    }

    // Calculate height
    uiHeight = uiWidth * ulImageHeight / ulImageWidth;

    // If not square pixel, calculate resolution domain value.
    if (bSquarePixel == MMP_FALSE)
    {
        uiHeight = (uiHeight * ulPixelWidth) >> 16;
    }

    *puwThumbWidth   = ALIGN16((MMP_USHORT)ulTargetWidth);
    *puwThumbHeight  = ALIGN16((MMP_USHORT)ulTargetHeight);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_GetThumbSize
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetThumbSize(MMP_USHORT Width,MMP_USHORT Height)
{
    m_ulTargetThumbWidth  = Width;
    m_ulTargetThumbHeight = Height;

    return MMP_ERR_NONE;
}
#endif //#if (EN_SPEED_UP_VID & BROWSER_CASE)

//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_SetScalerCfg
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_VIDPLAY_SetScalerCfg(MMPS_VIDPLAY_SCALERCONFIG *pScaConfig, MMP_BOOL bUseScaler, MMP_ULONG ulOutWidth,MMP_ULONG ulOutHeight,MMP_ULONG ulOutMaxWidth,MMP_ULONG ulOutMaxHeight)
{
    pScaConfig->bUseScaler = bUseScaler;
    pScaConfig->ulOutWidth = ulOutWidth;
    pScaConfig->ulOutHeight = ulOutHeight;
    pScaConfig->ulOutMaxWidth = ulOutMaxWidth;
    pScaConfig->ulOutMaxHeight = ulOutMaxHeight;
    return MMP_ERR_NONE;
}
//------------------------------------------------------------------------------
//  Function    : MMPS_VIDPLAY_Get3gpConTnerVidInfo
//  Description : Function to get 3GP container
//------------------------------------------------------------------------------
MMP_VIDEO_INFO* MMPS_VIDPLAY_Get3gpConTnerVidInf(void)
{
    return &m_3gpplayData.container.video_info[m_VideoTrack];
}

#if  defined( __RTK_OS__ )
MMP_ERR MMPS_VIDPLAY_AllocFwEnd(MMPS_VIDPLAY_ALOC_MEM_TYPE AlocType)
{
    MMP_ULONG* pInUserPtr;
    MMP_ULONG64  nInMiuAddr;
    MMP_ULONG64  nlInPhysAddr;

    if (!gulAlocMem4Rls[AlocType]) {
        CAM_OS_RET_CHK(CamOsDirectMemAlloc("ALOC_FW_END",
                                           ALOC_VID_SYS_SIZE,
                                           &pInUserPtr,
                                           &nInMiuAddr,
                                           &nlInPhysAddr));
        if (AlocType == MMPS_VIDPLAY_ALOC_VID) {
            gulAlocMem4Rls[AlocType] = m_ulFwEndAddr = (MMP_ULONG)pInUserPtr;
            printc(FG_PURPLE("PSR:x%x ~ x%x(x%x)%dM\n"), m_ulFwEndAddr, (m_ulFwEndAddr+ALOC_VID_SYS_SIZE), ALOC_VID_SYS_SIZE, (ALOC_VID_SYS_SIZE>>20));
        }
        else if (AlocType == MMPS_VIDPLAY_ALOC_BROW) {
            gulAlocMem4Rls[AlocType] = (MMP_ULONG)pInUserPtr;
        }
        //printc(FG_YELLOW("RS(%d)x%x\n"), AlocType, gulAlocMem4Rls[AlocType]);
    }
    else {
        printc(FG_RED("NoRls(%d) x%x\n"), AlocType, gulAlocMem4Rls[AlocType]);
        printc(FG_RED("DbgAlc:x%x x%x\n"), gulAlocMem4Rls[MMPS_VIDPLAY_ALOC_VID], gulAlocMem4Rls[MMPS_VIDPLAY_ALOC_BROW]);
    }

    return MMP_ERR_NONE;
}

MMP_ERR MMPS_VIDPLAY_ReleaseFwEnd(void)
{
    MMP_ULONG i, ulRlsNum = 0;
    CamOsRet_e camret = CAM_OS_OK;

    for (i = 0; i<MMPS_VIDPLAY_ALOC_NUM; i++) {
        if (gulAlocMem4Rls[i]) {
            //printc(FG_YELLOW("RE(%d)x%x\n"), i, gulAlocMem4Rls[i]);
            camret = CamOsDirectMemRelease(gulAlocMem4Rls[i], ALOC_VID_SYS_SIZE);
            if(camret != CAM_OS_OK) { UartSendTrace("[%s,%d] failed.\n",__FUNCTION__, __LINE__);}
            gulAlocMem4Rls[i] = m_ulFwEndAddr = 0;
            ulRlsNum++;
        }
        if (gulOpenScript[i]) {
            if (i == MMPS_VIDPLAY_ALOC_VID) {
                if (gbLCDRotate) {
                    if (m_bVidPlaybackReScale) {
                        CloseScript(COMPO_SCRIPT_MOVIE_PB_RESCALE_R);
                    }
                    else {
                        CloseScript(COMPO_SCRIPT_MOVIE_PB_R);
                    }
                }
                else {
                    if (m_bVidPlaybackReScale) {
                        CloseScript(COMPO_SCRIPT_MOVIE_PB_RESCALE_N);
                    }
                    else {
                        CloseScript(COMPO_SCRIPT_MOVIE_PB_N);
                    }
                }
            }
            else if (i == MMPS_VIDPLAY_ALOC_BROW) {
                if (gbLCDRotate) {
                    CloseScript(COMPO_SCRIPT_BROWSER_VID_THUMB_R);
                }
                else {
                    CloseScript(COMPO_SCRIPT_BROWSER_VID_THUMB_N);
                }
            }
            gulOpenScript[i] = MMP_FALSE;
        }
    }
    if (ulRlsNum > 1) {
        printc(FG_RED("err RlsNum=x%x\n"), ulRlsNum);
    }

    return MMP_ERR_NONE;
}

MMP_ERR MMPS_VIDPLAY_SetHvdDbgLv(void)
{
    #if 1
    gulDbgMsgLevel = E_VDEC_DBG_LEVEL_FW;
    #else
    gulDbgMsgLevel++;
    gulDbgMsgLevel %= (E_VDEC_DBG_LEVEL_FW + 1);
    #endif
    UartSendTrace(FG_GREEN("[0:Non 1:Err 2:Inf 3:Dbg 4:Trc 5:Fw]=%d\n"), gulDbgMsgLevel);
    return MMP_ERR_NONE;
}

MMP_ULONG MMPS_VIDPLAY_GetHvdDbgLv(void)
{
    return gulDbgMsgLevel;
}
#endif

//@end_ait_only
/** @} */
