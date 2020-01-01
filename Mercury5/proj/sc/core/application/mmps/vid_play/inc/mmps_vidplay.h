/**
 @file mmps_vidplay.h
 @brief Header File for the Host 3GP Player API.
 @author Truman Yang
 @version 1.0
*/

#ifndef _MMPS_VIDPLAY_H_
#define _MMPS_VIDPLAY_H_

//===============================================================================
//
//                               INCLUDE FILE
//
//===============================================================================

#include "mmp_lib.h"
#include "mmps_display.h"
#include "mmps_audio.h"
#include "ait_config.h"
#include "mmpd_3gpparser.h"
#include "mmp_vidplay_inc.h"
#include "mmp_graphics_inc.h"

//===============================================================================
//
//                               MACRO DEFINE
//
//===============================================================================

#define MMPS_VIDPSR_SEEK_NORMAL             (0x00000000)
#define MMPS_VIDPSR_SEEK_PRECISE            (0x00000001)
#define MMPS_VIDPSR_NEXT_KEYFRAME           (0x00000002)
#define MMPS_VIDPSR_SEEK_AUDIO_ONLY         (0x00000004)
#define MMPS_VIDPSR_SEEK_NEARESTKEY         (0x00000008)
#define MMPF_VIDPSR_SEEK_PRECISE_WITH_IDX   (0x00000010)
#define MMPF_VIDPSR_SEEK_PREPARE_FW         (0x00000020)
#define MMPF_VIDPSR_SEEK_PREPARE_BW         (0x00000040)
#define MMPS_VIDPSR_SEEK_FILE_START         (0x00000080)
#define MMPS_VIDPSR_SEEK_UNPREDECAUD        (0x01000000)
#define MMPS_VIDPSR_SEEK_SEEKMASK           (0x00FFFFFF)

//===============================================================================
//
//                               ENUMERATION
//
//===============================================================================

/** @addtogroup MMPS_VIDPLAY
@{
*/

/** The deblock type
*/
typedef enum MMPS_VIDPLAY_DEBLOCK_TYPE {
    MMPS_VIDPLAY_DEBLOCK_NONE,   ///< No deblocking
    MMPS_VIDPLAY_DEBLOCK_EN,     ///< Enable YUV deblocking.
    MMPS_VIDPLAY_DEBLOCK_Y_ONLY, ///< Enable Y-only deblocking.
    MMPS_VIDPLAY_DEBLOCK_TYPE_MAX
} MMPS_VIDPLAY_DEBLOCK_TYPE;

typedef enum MMPS_VIDPLAY_PLAYSPEED_MODE {
    MMPS_VIDPLAY_PLAYSPEED_NORMAL,
    MMPS_VIDPLAY_PLAYSPEED_FAST_FORWARD,
    MMPS_VIDPLAY_PLAYSPEED_FAST_BACKWARD,
    MMPS_VIDPLAY_PLAYSPEED_2X,
    MMPS_VIDPLAY_PLAYSPEED_DIVIDE_2,
    MMPS_VIDPLAY_PLAYSPEED_MAX
}MMPS_VIDPLAY_PLAYSPEED_MODE;

typedef enum MMPS_VIDPLAY_GETFRAME_TYPE{
    MMPS_VIDPLAY_GETFRAME_FIRST,
    MMPS_VIDPLAY_GETFRAME_CURRENT,
    MMPS_VIDPLAY_GETFRAME_LAST
} MMPS_VIDPLAY_GETFRAME_TYPE;

#if defined( __RTK_OS__ )
typedef enum _MMPS_VIDPLAY_ALOC_MEM_TYPE
{
    MMPS_VIDPLAY_ALOC_VID = 0,
    MMPS_VIDPLAY_ALOC_BROW,
    MMPS_VIDPLAY_ALOC_NUM
} MMPS_VIDPLAY_ALOC_MEM_TYPE;
#endif

//===============================================================================
//
//                          STRUCTURES
//
//===============================================================================

/** @brief The common video information in the 3GP video container/file

This information typically does not change during the playing
*/
typedef struct _MMPS_VIDEO_CONTAINER_INFO {
    MMP_VIDEO_INFO          video_info[2];          ///< The video information
    MMP_AUDIO_INFO          audio_info;             ///< The audio information
    MMP_UBYTE               is_video_available[2];  ///< Does video stream exist or not
    MMP_UBYTE               is_audio_available;     ///< Does audio stream exist or not
    MMP_USHORT              usAllocatedWidth;       ///< The width of the allocated output buffer
    MMP_USHORT              usAllocatedHeight;      ///< The height of the allocated output buffer
    MMP_ULONG64             file_size;              ///< The file size
    MMP_ULONG               total_file_time;        ///< The total file time in the container
    MMP_BYTE                is_video_seekable[2];
    MMP_UBYTE               drm_type;
    MMP_UBYTE               videoTrackNum;
}MMPS_VIDEO_CONTAINER_INFO;

/** @brief Video player buffer address information

Used for assigning the memory map addresses.
*/
typedef struct _MMPS_VIDPLAY_BUFFERADDRESS {
    MMP_BOOL    bUseExternalMemory;     ///< If this buffer uses external memory
    MMP_USHORT  usBufferUsed;           ///< The number of buffers used
    MMP_USHORT  usMPEG4BufUsed;         ///< The number of Mpeg4 devode buffers used
    MMP_ULONG   ulVideoAVDepackStart;   ///< Video decode AV depack start buffer address
    MMP_ULONG   ulAudioInStart;         ///< Audio decode input start buffer address
    MMP_ULONG   ulAudioInSize;          ///< Audio decode input buffer size
    MMP_ULONG   ulVideoInStart;         ///< Video decode input start buffer address
    MMP_ULONG   ulVideoInSize;          ///< Video decode input buffer size
    MMP_ULONG   ulVideoOutYStart;       ///< Video decode output start Y ref buffer address
    MMP_ULONG   ulVideoOutUStart;       ///< Video decode output start U ref buffer address
    MMP_ULONG   ulVideoOutVStart;       ///< Video decode output start V ref buffer address
    MMP_ULONG   ulDMAStartAddr;         ///< rotate DMA start address
    MMP_ULONG   ulRotateBufNum;         ///< number of rotate buffers
    MMP_ULONG   ulVideoWorkingBuffer;   ///< Use by video decode and get frame buffer
    MMP_ULONG   ulScalerBufNum;
    MMP_ULONG   ulScalerStartAddr;
} MMPS_VIDPLAY_BUFFERADDRESS;

/** @brief Display description to config the way Video Player displays.

Used to assign target video position and the size.
*/
typedef struct _MMPS_VIDPLAY_DISPLAY {
    MMP_USHORT                  usX;            ///< x
    MMP_USHORT                  usY;            ///< y
    MMP_USHORT                  usWidth;        ///< width
    MMP_USHORT                  usHeight;       ///< height
    MMP_DISPLAY_ROTATE_TYPE     rotationtype;   /**< rotation degree in clockwise. The value could be 0, 90, 180 and 270.
                                                    Other values might result in unexpected effect.*/
    MMP_BOOL                    bFullyFilled;   /**< When the displaying aspect is not the same as the file,
                                                    It would fully filled the displaying window or not.*/
    MMP_BOOL                    bMirror;        ///< The display uses Mirror or not
    MMP_DISPLAY_DEV_TYPE        outputpanel;    ///< Output panel

    /** If the DMA rotation is used or not.
        If the player uses internal memory, it will ignore this value.*/
    MMP_BOOL                    bDMARotation;
    MMP_BOOL                    bKeepRatio;
    MMP_BOOL                    bUseScaler;
} MMPS_VIDPLAY_DISPLAY;

/** @brief 3GP video player configuration

This structure is used to setting the video play modes.
Used in MMPS_VIDPLAY_Config
*/
typedef struct _MMPS_VIDPLAY_CONFIG {
    MMPS_VIDPLAY_DISPLAY display; ///< Target display area to play the video
} MMPS_VIDPLAY_CONFIG;

/** @brief Structure to configurate the video decoding modes

This is a more detail mode setting compare with MMP_3GPPLAY_CONFIG.
The calling could use MMP_3GPPLAY_CONFIG to set these detail option.
@note This structure is used for advanced users.
*/
typedef struct _MMPS_SYSTEM_VIDEODECMODES {
    MMP_USHORT                  usMaxWidth;                         ///< The max width supported in current config.
    MMP_USHORT                  usMaxHeight;                        ///< The max height supported in current config.
    MMP_ULONG                   ulMaxInternalVideoOutBufferSize;    ///< Max buffer supported without external memory
    MMP_ULONG                   ulMaxVideoOutBufferSize;            /**< Max buffer supported with or without external memory.
                                                                         Note that this size includes DMA rotation buffer.*/
    MMPS_VIDPLAY_CONFIG         config[VIDEOPLAY_MODE_MAX];         ///< The preset configs.
    MMP_LCD_ATTR                display_mode[VIDEOPLAY_MODE_MAX];   ///< display mode
    MMPS_VIDPLAY_DEBLOCK_TYPE   deblock_type;                       ///< The deblock type
    MMP_ULONG                   ulVideoStreamBufSize;               ///< buffer size for video stream
    MMP_ULONG                   ulRotateDMABufNum;                  ///< buffer num for rotate DMA
    MMP_USHORT                  usMP4DecBufNum;
    MMP_DISPLAY_WIN_ID          window_type;
    MMPC_3GPPLAY_MODE           videoplay_mode;
} MMPS_SYSTEM_VIDEODECMODES;

typedef struct _MMPS_VIDPLAY_SCALERCONFIG {
    MMP_USHORT                  ulOutWidth;
    MMP_USHORT                  ulOutHeight;
    MMP_BOOL                    bUseScaler;
    MMP_USHORT                  ulOutMaxWidth;
    MMP_USHORT                  ulOutMaxHeight;
} MMPS_VIDPLAY_SCALERCONFIG;

/// @}

//===============================================================================
//
//                               FUNCTION PROTOTYPES
//
//===============================================================================

/** @addtogroup MMPS_VIDPLAY
@{
*/

//Playback_Control
MMP_ERR     MMPS_VIDPLAY_Play(void *VidPlayerCallBack, void *Context);
MMP_ERR     MMPS_VIDPLAY_Open(MMP_BYTE *pFileName, MMP_ULONG ulFileNameLength,MMP_ULONG ulTargetTime,MMP_BOOL bPreDecVideo,MMP_BOOL bPreDecAudio, MMPS_VIDPLAY_SCALERCONFIG *pScalerConfig);
MMP_ERR     MMPS_VIDPLAY_SetPlaySpeed(MMPS_VIDPLAY_PLAYSPEED_MODE mode, MMP_SHORT sSpeed);
MMP_ERR     MMPS_VIDPLAY_Pause(void);
MMP_ERR     MMPS_VIDPLAY_Resume(void);
MMP_ERR     MMPS_VIDPLAY_Stop(MMP_ULONG *LastKeyFrameNum);
MMP_ERR     MMPS_VIDPLAY_Close(void);
MMP_ERR     MMPS_VIDPLAY_SeekByTime(const MMP_ULONG ulTargetTime, MMP_ULONG ulSeekOption);

MMP_ERR     MMPS_VIDPLAY_GetFrame(  MMP_BYTE                        *pFileName,
                                    MMP_ULONG                       ulFileNameLength,
                                    MMP_USHORT                      *usWidth,
                                    MMP_USHORT                      *usHeight,
                                    MMP_GRAPHICS_COLORDEPTH         colorDepth,
                                    MMP_USHORT                      *Output,
                                    MMP_ULONG                       *ulSize,
                                    MMPS_VIDPLAY_GETFRAME_TYPE      GetFrameType);

MMP_ERR     MMPS_VIDPLAY_GetThumbnail(MMP_BYTE              *pFileName,
                                    MMP_ULONG               ulFileNameLength,
                                    MMP_ULONG               ulOutBufSize,
                                    MMP_UBYTE               **ubOutBuf,
                                    MMP_ULONG               *ulOutSize);

MMP_ERR     MMPS_VIDPLAY_SetMemoryMode(MMP_BOOL bMemMode);

MMP_ERR     MMPS_VIDPLAY_GetFileInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength, MMPS_VIDEO_CONTAINER_INFO *ppInfo);
MMP_ERR     MMPS_VIDPLAY_GetCurrentTime(MMP_ULONG *pulTime);
MMP_ERR     MMPS_VIDPLAY_SetSBCTime(MMP_ULONG ulTime);
MMP_ERR     MMPS_VIDPLAY_GetState(MMP_M_STATE *pState);

MMP_ERR     MMPS_VIDPLAY_SetDisplayMode(const MMP_USHORT usMode, const MMP_UBYTE ubRotatetype, MMP_BOOL bRedraw, MMPS_VIDPLAY_DISPLAY *pConfig, MMPS_VIDPLAY_SCALERCONFIG *pScalerConfig);

MMP_ERR     MMPS_VIDPLAY_InitConfig(MMPS_SYSTEM_VIDEODECMODES* pConfig);

MMPS_SYSTEM_VIDEODECMODES* MMPS_VIDPLAY_GetConfig(void);

MMP_ERR     MMPS_VIDPLAY_SetVideoInPlay(MMP_BOOL bEnable);
MMP_ERR     MMPS_VIDPLAY_GetVideoInPlay(MMP_BOOL*bEnable);
MMP_ERR     MMPS_VIDPLAY_SetVideoDecodeEnable(MMP_BOOL bEnable);
MMP_ERR     MMPS_VIDPLAY_SetVideoRefreshEnable(MMP_BOOL bEnable);
MMP_ERR     MMPS_VIDPLAY_Step(void);
MMP_ERR     MMPS_VIDPLAY_GetContainerInfo(MMP_BYTE *szFilename, MMP_ULONG ulFileNameLength, MMPS_VIDEO_CONTAINER_INFO *info);
MMP_ERR     MMPS_VIDPLAY_GetUserDataInfo(MMP_USERDATA_TAG **pUdta);
MMP_ERR     MMPS_VIDPLAY_GetVideoAvailable(MMP_BOOL *bAvail);

MMP_ERR     MMPS_VIDPLAY_GetCurDisplayMode(MMP_ULONG *ulMode);

MMP_ERR     MMPS_VIDPLAY_SetDisplayWindow(MMP_BOOL Use,MMP_USHORT StartX,MMP_USHORT StartY,MMP_USHORT Width,MMP_USHORT Height);
MMP_ERR     MMPS_VIDPLAY_SetDisplayType(MMP_DISPLAY_OUTPUT_SEL displaypanel);
MMP_ERR     MMPS_VIDPLAY_SetSearchFPS(MMP_ULONG ulDuration);
MMP_ERR     MMPS_VIDPLAY_EnableGraphicsScaler(MMP_BOOL bEnable);

MMP_ERR     MMPS_VIDPLAY_SetDramMallocAddr(MMP_ULONG ulDramMallocAddr);
MMP_ERR     MMPS_VIDPLAY_GetCurFileDuration(MMP_ULONG *ulDuration);
MMP_ERR     MMPS_VIDPLAY_GetCurFileFps(MMP_ULONG *ulFps);
MMP_ERR     MMPS_VIDPLAY_GetCurFileResolution(MMP_USHORT *usW, MMP_USHORT *usH);
MMP_ERR     MMPS_VIDPLAY_GetCurAudioBuffer(MMP_ULONG *ulAddr, MMP_ULONG *ulSize);

MMP_ERR     MMPS_VIDPLAY_SetCurrentTrack(MMP_UBYTE ubCurrentTrack);
MMP_ERR     MMPS_VIDPLAY_GetCurrentTrack(MMP_ULONG *ulCurrentTrack);
MMP_ERR     MMPS_VIDPLAY_SetScaleOutMaxSize(MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR     MMPS_VIDPLAY_GetTotalTrackNum(MMP_ULONG *ulTotalTrackNum);
MMP_ERR     MMPS_VIDPLAYER_AllowAVIListModifyAtom(MMP_BOOL bEnable, MMP_BYTE *pStr);
MMP_ERR     MMPS_VIDPLAY_SetColorFmt(MMP_ULONG ulFmt);
MMP_ULONG   MMPS_VIDPLAY_GetColorFmt(void);
#if (EN_SPEED_UP_VID & BROWSER_CASE)
MMP_ERR     MMPS_VIDPLAY_Thumb_CalculateRatio(MMP_ULONG ulImageWidth, MMP_ULONG ulImageHeight,
                                              MMP_ULONG ulTargetWidth, MMP_ULONG ulTargetHeight,
                                              MMP_USHORT* puwThumbWidth, MMP_USHORT* puwThumbHeight);
MMP_ERR     MMPS_VIDPLAY_SetThumbSize(MMP_USHORT Width,MMP_USHORT Height);
#endif //#if (EN_SPEED_UP_VID & BROWSER_CASE)
MMP_ERR     MMPS_VIDPLAY_SetScalerCfg(MMPS_VIDPLAY_SCALERCONFIG *pScaConfig,
                                      MMP_BOOL bUseScaler,
                                      MMP_ULONG ulOutWidth,
                                      MMP_ULONG ulOutHeight,
                                      MMP_ULONG ulOutMaxWidth,
                                      MMP_ULONG ulOutMaxHeight);
MMP_VIDEO_INFO* MMPS_VIDPLAY_Get3gpConTnerVidInf(void);
#if defined( __RTK_OS__ )
MMP_ERR MMPS_VIDPLAY_AllocFwEnd(MMPS_VIDPLAY_ALOC_MEM_TYPE AlocType);
MMP_ERR MMPS_VIDPLAY_ReleaseFwEnd(void);
#endif
/// @} // end of MMPS_VIDPLAY

#endif //  _MMPS_VIDPLAY_H_
