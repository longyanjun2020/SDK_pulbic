/// @ait_only
/**
 @file mmpd_vidplayer.h
 @brief Header File for the MPEG4 decoder Driver.
 @author Truman Yang
 @version 
    - 2.0 Seperate the playing file from parser
    - 1.1 [08-Jun-06] Updates the comments and change API to align with the System Software Architecture
*/

#ifndef _MMPD_VIDPLAYER_H_
#define _MMPD_VIDPLAYER_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
//#include "mmpd_display.h"
#include "mmp_media_def.h"
#include "mmp_vidplay_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/** @name IPC
Inter Process Communication section.
All definition and declaration here are used for host MMP inter process communication.
This section should be sync between the host and the firmware.
Most enumeration type has a _MAX value so that the host could verify the version of
the enumeration.
@{
*/

/** @brief Video type of the 3GP file and the firmware.
    The type listed here does not imply that the firmware is able to play it. For example,
    the MPEG4 Advanced simple profile might be recognized but not able to be played.
    The lower level API might return either MMP_3GP_VIDEO_MP4V_ASP or MMP_3GP_VIDEO_UNSUPPORTED.
    The main purpose to enumerate this value is for futher support.
    
    @note This parameter is used by both MMPD and MMPF
*/
typedef enum MMPD_3GP_VIDEOTYPE {
    MMPD_3GP_VIDEO_NONE = 0,   ///< No video
    MMPD_3GP_VIDEO_H263 = 1,   ///< H.263
    MMPD_3GP_VIDEO_MP4V_SP = 2,///< MPEG4 Video Simple Profile
    MMPD_3GP_VIDEO_MP4V = 2,   ///< MPEG4 Video Simple Profile. MP4V is regarded as simple profile when not specified.
    MMPD_3GP_VIDEO_MP4V_ASP,   ///< MPEG4 Video Advanced Simple Profile
    MMPD_3GP_VIDEO_H264,       ///< H.264
    MMPD_3GP_VIDEO_UNSUPPORTED,/**< Unsupported audio type goes here, including some audio type, which can be played
                                    alone only. e.g. MP3 */
    MMPD_3GP_VIDEOTYPE_MAX
} MMPD_3GP_VIDEOTYPE;

/** @brief Audio type of the 3GP file and the firmware
    The type listed here does not imply that the firmware is able to play it. For example,
    the WMA might be recognized but not able to be played with the video.
    The lower level API might return either MMP_3GP_AUDIO_WMA or MMP_3GP_AUDIO_UNSUPPORTED.
    The main purpose to enumerate this value is for futher support.

    @note This parameter is used by both MMPD and MMPF
*/
typedef enum MMPD_3GP_AUDIOTYPE {
    MMPD_3GP_AUDIO_NONE = 0,   ///< No audio
    MMPD_3GP_AUDIO_AMR_NB = 1, ///< AMR-NB
    MMPD_3GP_AUDIO_AMR = 1,    ///< If not specified, then AMR means AMR-NB
    MMPD_3GP_AUDIO_AAC_LC = 2, ///< AAC-LC
    MMPD_3GP_AUDIO_AAC = 2,    ///< If not specified, then AAC means AAC-LC
    MMPD_3GP_AUDIO_AAC_PLUS,   ///< AAC+
    MMPD_3GP_AUDIO_MP3,        ///< MP3
    MMPD_3GP_AUDIO_WMA,        ///< Microsoft WMA
    MMPD_3GP_AUDIO_UNSUPPORTED,/**< Unsupported audio type goes here, including some audio type, which can be played
                                    alone only. e.g. AMR-WB */
    MMPD_3GP_AUDIOTYPE_MAX
} MMPD_3GP_AUDIOTYPE;

/** @} */ // end of IPC

/** @addtogroup MMPD_3GPPLAY
 *  @{
 */

/** The deblock type
*/
typedef enum MMPD_3GPPLAY_DEBLOCK_TYPE {
    MMPD_3GPPLAY_DEBLOCK_NONE,   ///< No deblocking
    MMPD_3GPPLAY_DEBLOCK_EN,     ///< Enable the deblock, with Y and Cb,Cr
    MMPD_3GPPLAY_DEBLOCK_Y_ONLY, ///< Enable the Y-only deblocking
    MMPD_3GPPLAY_DEBLOCK_TYPE_MAX
} MMPD_3GPPLAY_DEBLOCK_TYPE;

typedef enum MMPD_3GPPLAY_PLAYSPEED_MODE {
    MMPD_3GPPLAY_PLAYSPEED_NORMAL,
    MMPD_3GPPLAY_PLAYSPEED_FAST_FORWARD,
    MMPD_3GPPLAY_PLAYSPEED_FAST_BACKWARD,
    MMPD_3GPPLAY_PLAYSPEED_2X,
    MMPD_3GPPLAY_PLAYSPEED_DIVIDE_2
}MMPD_3GPPLAY_PLAYSPEED_MODE;

typedef enum MMPD_3GPPLAY_VPP_MODULE {
    MMPD_3GPPLAY_VPP_DEBLOCK    = 0x01,
    MMPD_3GPPLAY_VPP_DMAROTATE  = 0x02,
    MMPD_3GPPLAY_VPP_GRAPHIC    = 0x04, 
    MMPD_3GPPLAY_VPP_MAX        = 0xFF
}MMPD_3GPPLAY_VPP_MODULE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPD_VIDPLAYER_SetPlaySpeed(MMPD_3GPPLAY_PLAYSPEED_MODE mode,MMP_BOOL bCardMode, MMP_SHORT sSpeed);
//MMP_ERR MMPD_VIDPLAYER_SetActivePanel(MMP_DISPLAY_DEV_TYPE PanelType, MMP_DISPLAY_WIN_ID WinID);
MMP_ERR MMPD_VIDPLAYER_GetCurrentFrame(MMP_ULONG *ulFrame,
                       MMP_ULONG *ulY, MMP_ULONG *ulU, MMP_ULONG *ulV);
MMP_ERR MMPD_VIDPLAYER_GetSupportedFormat(MMPD_3GP_AUDIOTYPE *supported_audio_format,
                                          MMPD_3GP_VIDEOTYPE *supported_video_format);
MMP_ERR MMPD_VIDPLAYER_SetDeblockMode(const MMPD_3GPPLAY_DEBLOCK_TYPE deblocktype);
MMP_ERR MMPD_VIDPLAYER_GetDeblockMode(MMPD_3GPPLAY_DEBLOCK_TYPE *deblocktype);
MMP_ERR MMPD_VIDPLAYER_RedrawLastRefresh(void);
MMP_ERR MMPD_VIDPLAYER_Redraw(void);
MMP_ERR MMPD_VIDPLAYER_GetState(MMP_M_STATE *pState);
MMP_ERR MMPD_VIDPLAYER_Init(void);
MMP_ERR MMPD_VIDPLAYER_GetEmptyFrame(MMP_ULONG *ulYAddr,MMP_ULONG *ulUAddr,MMP_ULONG *ulVAddr);
MMP_ERR MMPD_VIDPLAYER_ConfigMemDone(MMP_ULONG *ulMemEndAddr);
MMP_ERR MMPD_VIDPLAYER_Start(void *VidPlayerCallBack, void *Context);
MMP_ERR MMPD_VIDPLAYER_Pause(void);
MMP_ERR MMPD_VIDPLAYER_Resume(void);
MMP_ERR MMPD_VIDPLAYER_Stop(MMP_ULONG *KeyFrameNum);
MMP_ERR MMPD_VIDPLAYER_Close(void);
void    MMPD_VIDPLAYER_SetCurrentTime(const MMP_ULONG ulCurTime);
void    MMPD_VIDPLAYER_SetSBCTime(const MMP_ULONG ulCurTime);
MMP_ERR MMPD_VIDPLAYER_GetCurrentTime(MMP_ULONG *pulTime);
MMP_ERR MMPD_VIDPLAYER_InitVideoDec( MMP_ULONG dest_addr,MMP_UBYTE* const pStartAddress, const MMP_USHORT usSize, MMP_USHORT *pWidth,
                                        MMP_USHORT *pHeight, MMP_USHORT *pLeft, MMP_USHORT *pTop,
                                        MMP_USHORT *pRight, MMP_USHORT *pBottom,MMP_ULONG ulCodecFormat);

MMP_ERR MMPD_VIDPLAYER_Flush(const MMP_BOOL bFlushVideo, const MMP_BOOL bFlushAudio);
MMP_ERR MMPD_VIDPLAYER_SetVideoDecodeEnable(MMP_BOOL bEnable);
MMP_ERR MMPD_VIDPLAYER_SetVideoRefreshEnable(MMP_BOOL bEnable);
MMP_ERR MMPD_VIDPLAYER_DecodeData(MMP_ULONG *time);
MMP_ERR MMPD_VIDPLAYER_SetVPPModuleClk(MMPD_3GPPLAY_VPP_MODULE module, MMP_BOOL bEnable);
MMP_ERR MMPD_VIDPLAYER_GetVPPModuleClk(MMP_UBYTE *ubClkCtl);
MMP_ERR MMPD_VIDPLAYER_SetVideoFormat(MMP_UBYTE ubAVC);
MMP_ERR MMPD_VIDPLAYER_GetVideoFormat(MMP_UBYTE *ubAVC);
MMP_ERR MMPD_VIDPLAYER_DecodeVideoFrame(MMP_ULONG ulDestAddr, MMP_ULONG ulSrcAddr,MMP_ULONG ulFrameSize,MMP_ULONG ulTime);
MMP_ERR MMPD_VIDPLAYER_CloseCodec(void);
MMP_ERR MMPD_VIDPLAYER_Step(void);
MMP_ERR MMPD_VIDPLAYER_SetSearchSpeed(MMPD_3GPPLAY_PLAYSPEED_MODE mode, MMP_BOOL bCardMode, MMP_SHORT sSpeed);
MMP_ERR MMPD_VIDPLAYER_SetHDMIInterface(MMP_BOOL bInterlace, MMP_ULONG ulFreq);
MMP_ERR MMPD_VIDPLAYER_SetSearchFPS(MMP_ULONG ulDuration);
MMP_ERR MMPD_VIDPLAYER_SetGetFrameMode(MMP_BOOL bIsGetFrame);
MMP_ERR MMPD_VIDPLAYER_EnableGraphicsScaler(MMP_BOOL bEnable);
MMP_ERR MMPD_VIDPLAYER_AllowAVIListModifyAtom(MMP_BOOL bEnable, MMP_BYTE *pStr);
/// @}

#endif // _MMPD_VIDPLAYER_H_

/// @end_ait_only
