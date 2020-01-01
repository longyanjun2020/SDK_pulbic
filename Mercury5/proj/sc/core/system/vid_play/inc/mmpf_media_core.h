/**
 @file mmpf_media_core.h
 @brief Header function of component template
 @author Truman Yang
 @version 1.0 Original Version
*/

#ifndef _MMPF_M_COMPONENT_H_
#define _MMPF_M_COMPONENT_H_

#include "includes_fw.h"
#include "mmp_media_def.h"
#include "mmpf_media_struct.h"

//==============================================================================
//                              COMPILER OPTIONS
//==============================================================================

#if 0
void _____Player_Options_____(){}
#endif

/** @brief Enable to print out the time used by the hardware

Currently we've implemented to trace video hardware decoder only\n
 0: Trace none\n
 1: Trace video decode duration by hardware\n
 2: Trace video bitstream demuxing duration\n
 3: Trace video demuxing starting interval\n
 4: Trace LCD refresh time\n
 5: Trace video decode interval\n
 6: Trace video demuxing fucntion entering interval\n
 7: Trace the time interval waking up the demuxer in ping-pong bitstream buffer case\n
 8: Trace the duration of Deblock\n
 9: Trace the duration between VLD done and next load start\n
10: Trace one frame loading time.
11: Trace one frame seeking loading time.
*/


// ----- decoder performance measurement -----


/** Enable the field latch feature. This only works on Retina V1 and Diamond

MMPD_Display_SetTVOutput has to be set to the same option.\n
0:No field latch
1:Use field latch
*/

#define TV_FIELD_LATCH (1)

/** Enable to dump function in MMPF_3GPP_SetTVOutputEnable for host to print variable for debug via UART
set 0 to save 824 bytes code size, 1 to enable the debug print out.*/
#define DEBUG_DUMP (1)

#if 0 // for IDE function name list by section
void _____Parser_Options_____(){}
#endif

/// Enable large size file read DMA feature
#define LARGE_DMA (1)

/** @brief Number of zero attaching to the bitstream buffer

It must be a multiple of 4. We have to fill this data to avoid HW resync marker detection in the
tailing garbage.*/
#define RING_BUF_TAILING (4)

#if (VIDEO_DECODER == SW_H264) || (VIDEO_DECODER == HW_H264) || (VIDEO_DECODER == SW_MP4V)
#define USE_RING_BUFFER_WHEN_AVAILABLE (0)
#else
#define USE_RING_BUFFER_WHEN_AVAILABLE (1)
#endif

/* ===== buffer types =====
    Because it might be needed in compile time, use define instead of run-time
*/
#define MMP_MEDIA_NEAR_RING_BUFFER (2) ///< Near-ring buffer, no frame/sample is divided into 2 parts
#define MMP_MEDIA_RING_BUFFER (3)      ///< Ring buffer. Frame/sample might be divided into 2 parts.

    #if USE_RING_BUFFER_WHEN_AVAILABLE == 0
        /// If the frame which is larger then the bitstream buffer is supported
        #define SUPPORT_LARGE_FRAME (0)
        /// The current buffer type
        #define BUFFER_TYPE MMP_MEDIA_NEAR_RING_BUFFER
    #else
        /// If the frame which is larger then the bitstream buffer is supported
        #define SUPPORT_LARGE_FRAME (1)
        /// The current buffer type
        #define BUFFER_TYPE MMP_MEDIA_RING_BUFFER
    #endif

//==============================================================================
//                                IPC SECTION
//==============================================================================
/** @addtogroup MMPF_M
@{
*/

/** There are too many parameters. Use this type to enumerate the types that are seldom used and
not listed in another group. By this type, all parameters with long can simply use MMPS_3GPPLAY_GetParameter
and MMPS_3GPPLAY_SetParameter to access. This can also reduce the MMPD layer interface.
*/
typedef enum MMPF_3GPPLAY_PARAMETER {
    MMPF_3GPPLAY_PARAMETER_GROUP = 0xF000,///< The mask used to classify the parameter group
    MMPF_3GPPLAY_PARAMETER_PARSER_BASE = 0x0000,
    MMPF_3GPPLAY_PARAMETER_STORAGE_PATH, /**< The storage path. MMP_FALSE: memory mode, MMP_TRUE:card mode, 
                                             2:host-parser memory mode*/
    MMPF_3GPPLAY_PARAMETER_SEEK_MODE,///< Current video player packback seek mode
    MMPF_3GPPLAY_PARAMETER_CACHE, ///< The addresses of cache buffers [1]FSCache [2]FS Cache size [3]Depack Buffer
    MMPF_3GPPLAY_PARAMETER_BITSTREAM, /**< The addresses of the bitstream [1]Video bitstream
                                          [2]Video bitstream size [3]Audio bitstream [4]Audio bitstrem size*/
    MMPF_3GPPLAY_PARAMETER_VIDEO_BITSTREAM,
    MMPF_3GPPLAY_PARAMETER_AUDIO_BITSTREAM,
    MMPF_3GPPLAY_PARAMETER_BITSTREAM_PTR, ///< The addresses of the video bitstream pointer
    MMPF_3GPPLAY_PARAMETER_AUDIO_BITSTREAM_PTR, ///< The addresses of the audio bitstream pointer
    MMPF_3GPPLAY_PARAMETER_MUTEX, ///< The mutex state.
    MMPF_3GPPLAY_PARAMETER_DECODE_DONE, ///< Return if it is decode done or not
    MMPF_3GPPLAY_PARAMETER_INT_THRESHOLD, /**< The data move interrupt threshold in bytes.
                                               0 for triggering per frame.*/
    MMPF_3GPPLAY_PARAMETER_SEEK_DIR,
    MMPF_3GPPLAY_PARAMETER_VIDEO_FRAMENUM,
    
    MMPF_3GPPLAY_PARAMETER_DECODER_BASE = 0x2000,
    MMPF_3GPPLAY_PARAMETER_AUXILIARY, /**< The addresses of the video auxiliary buffers
                                          [1]VLD_MVPred [2]DataPartition [3]Pred_H [4]Pred_V*/
    MMPF_3GPPLAY_PARAMETER_DECODER_CONFIG, ///< The decoder config parameters

    MMPF_3GPPLAY_PARAMETER_POSTPROCESSOR_BASE = 0x3000,
    MMPF_3GPPLAY_PARAMETER_DEBLOCK,///< The deblock value, see @ref MMPF_3GPPLAY_DEBLOCK_TYPE for information

    MMPF_3GPPLAY_PARAMETER_RENDERER_BASE = 0x4000,
    MMPF_3GPPLAY_PARAMETER_FRAME, ///< The addresses of the video frame buffers [1]Y [2]Cb[3]Cr[4]CbCr Size in bytes
    MMPF_3GPPLAY_PARAMETER_VIDEO_BUFFER, /**< The properties of the video frame buffers
                                             [1]Number of buffers used [2]Use external or not,
                                             1 for external, 0 for internal.*/
    MMPF_3GPPLAY_PARAMETER_SCALER_BUFFER,
    MMPF_3GPPLAY_PARAMETER_FRAME_RESOLUTION,
    MMPF_3GPPLAY_PARAMETER_CTRL_FRAME_BUFFER, ///< Allocate video frame buffer for video decode ctrl
    MMPF_3GPPLAY_PARAMETER_TV, ///< 1 for on and 0 for off.

    MMPF_3GPPLAY_PARAMETER_CLOCK_BASE = 0x5000,
    MMPF_3GPPLAY_PARAMETER_CURRENT_TIME, ///< The current playing time in millisecond
    MMPF_3GPPLAY_PARAMETER_REFERENCE_CLOCK,///< Current reference clock
    MMPF_3GPPLAY_PARAMETER_SPEED,///< Current video player packback speed
    MMPF_3GPPLAY_PARAMETER_SEEK_BY_FRAME,
    MMPF_3GPPLAY_PARAMETER_SEEK_BY_TIME,

    MMPF_3GPPLAY_PARAMETER_INFO_BASE = 0x6000,
    MMPF_3GPPLAY_PARAMETER_FILE_SIZE, ///< The file size of current parsed file
    MMPF_3GPPLAY_PARAMETER_AUDIO_TOTAL_TIME, ///< The current audio totoal time in millisecond
    MMPF_3GPPLAY_PARAMETER_VIDEO_TOTAL_TIME, ///< The current video totoal time in millisecond
    MMPF_3GPPLAY_PARAMETER_AUDIO_BITRATE, ///< The current audio bit-rate
    MMPF_3GPPLAY_PARAMETER_VIDEO_BITRATE, ///< The current video bit-rate
    MMPF_3GPPLAY_PARAMETER_AUDIO_FORMAT, ///< The current audio format
    MMPF_3GPPLAY_PARAMETER_VIDEO_FORMAT, ///< The current video format
    MMPF_3GPPLAY_PARAMETER_SUPPORTED_AUDIO,///< The supported audio type by the firmware
    MMPF_3GPPLAY_PARAMETER_FPS, ///< Frame per second in the 3GP file
    MMPF_3GPPLAY_PARAMETER_AUDIO_CHANNEL, ///< Number of Audio Channel
    MMPF_3GPPLAY_PARAMETER_AUDIO_SAMPLING_RATE, ///< Audio sampling rate
    MMPF_3GPPLAY_PARAMETER_AUDIO_LENGTH, ///< Audio length in bytes, write only
    MMPF_3GPPLAY_PARAMETER_AUDIO_TIME_BASE, ///< Audio time base
    MMPF_3GPPLAY_PARAMETER_VIDEO_WIDTH, ///< Video width
    MMPF_3GPPLAY_PARAMETER_VIDEO_HEIGHT,///< Video height
    MMPF_3GPPLAY_PARAMETER_OSD_ADDRESS, ///< OSD Starting Address. It's an 8-bytes alignment address.
    MMPF_3GPPLAY_PARAMETER_PLAYER_STATE, ///< Player state.
    MMPF_3GPPLAY_PARAMETER_VIDEO_AVAILABLE, ///< video available or not.
    MMPF_3GPPLAY_PARAMETER_AUDIO_AVAILABLE, ///< video available or not.
    MMPF_3GPPLAY_PARAMETER_DEBUG, ///< Debug information.
    MMPF_3GPPLAY_PARAMETER_AUDIO_OBJINDEX, ///< for aacplus, mp4ASC object index value 
    MMPF_3GPPLAY_PARAMETER_SBCTIME, ///< Set SBC Time
    MMPF_3GPPLAY_PARAMETER_DECODE_AUDIO,
    MMPF_3GPPLAY_PARAMETER_CURRENTTRACK, 
    MMPF_3GPPLAY_PARAMETER_MAX
} MMPF_3GPPLAY_PARAMETER;

/** @brief Firmware Debug type

This enumeration is for Inter Process Communication. It belongs to no module.
Used for Debug in 3GP player. Generally it print out the state machine and the registers.
It could be dis-functioned by firmware compiler options.
It's a bad design that the debug and TV enable uses the same function.
But it saves code size and HIF command.
*/
typedef enum MMPF_3GPP_DEBUG {
    MMPF_DEBUG_DUMP_TV_REGISTER = 0x10, ///< Dump TV registers, 0x7000, 0x7040~0x7100, 0x7200~0x7300
    MMPF_DEBUG_DUMP_VLD_REGISTER, ///< Dump VLD registers, 0xB400~0xB44F
    MMPF_DEBUG_DUMP_AV_SYNC_VARIABLES, ///< Dump AV sync variables
    MMPF_DEBUG_DUMP_AUDIO_BUFFER, ///< Dump audio buffer
    MMPF_DEBUG_SHOW_TIMER ///< Show AV sync timer
}MMPF_3GPP_DEBUG;

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
/** @brief Buffer Pipeline Status

@image html "image/Buffer Pipeline FSM.png"
Currently it is used in RAW buffers only for managing the queue
*/
typedef enum MMPF_3GP_BUFFERSTATUS{
    BUFFER_REFRESH_DONE, /// finished and should be no use, default value
    BUFFER_PROCESSING,
    BUFFER_PROCESS_DONE,
    BUFFER_DBLK_PROCESSING,
    BUFFER_DBLK_PROCESS_DONE,
    BUFFER_POST_SCALING,
    BUFFER_POST_SCALE_DONE,
    BUFFER_POST_PROCESSING,
    BUFFER_POST_PROCESS_DONE,
    BUFFER_REFRESHING
} MMPF_3GP_BUFFERSTATUS;

/** @brief The video raw buffer information
*/
typedef struct MMPF_M_VIDEO_RAW_BUFFER_INFO {
    MMP_ULONG flag;              	///< The flag of this frame, used for EOS detection
    MMP_ULONG QP;                 	///< The QP of this frame for deblocking. It might be the QP address in Diamond.
    MMPF_3GP_BUFFERSTATUS status; 	///< The buffer status
    MMP_ULONG ulRequestTime;      	///< The request time to the media clock for av-sync.
    MMP_ULONG ulFrame;            	///< The Frame number of the output buffer. It could be used for resume feature
    MMP_MEDIA_FRAME addr;         	///< The YUV addresses of this frame
} MMPF_M_VIDEO_RAW_BUFFER_INFO;

/** @brief Undefined time

If the time is undefine, set this value
Set this time to Max MMP_ULONG to make sure it won't conflict when comparing times.
Reseved space for some offset comparasion*/
#define UNDEFINED_TIME (0xFFFF0000)
/** @brief Max video frame buffers

This should attach to the buffer though*/
#define MAX_VIDEO_BUFFER (5)

#define MAX_ROTATE_BUFFER (3)

#define MAX_SCALER_BUFFER (3)

/** @brief End of Stream Buffer Flag

This is a symbol to mark in a input bitstream to be identified
*/
#define BUFFERFLAG_EOS              (0x0001)
#define BUFFERFLAG_STARTTIME        (0x0002)
#define BUFFERFLAG_DECODEONLY       (0x0004)

/** @brief Data Corrupt Flag:

This flag is set when the player believes the data in the
associated buffer is corrupt. For Retina, when data > Bitstream buffer. It's regards as
corrupt */
#define BUFFERFLAG_DATACORRUPT      (0x0008)

/** @brief End of Frame

The buffer contains exactly one end of frame and no data
occurs after the end of frame. This flag is an optional hint. The absence
of this flag does not imply the absence of an end of frame within the buffer. 
Reserved for VLD module V1 or later.*/
#define BUFFERFLAG_EOF              (0x0010)

/// This frame needs wrap
#define BUFFERFLAG_NEED_WRAP        (0x0020)

/// The next frame is not loaded
#define BUFFERFLAG_UNKNOWN_WRAP     (0x0040)
#define BUFFERFLAG_KEEP_STATE       (0x0080)
#define BUFFERFLAG_SLICE            (0x0100)
#define BUFFERFLAG_NO_REORDER_TIME  (0x0200)
#define BUFFERFLAG_FRAME_EOS        (0x0400)
#define BUFFERFLAG_SRC_RELEASED     (0x0800)
#define BUFFERFLAG_DECODE_RV_HEADER (0x8000)

//==============================================================================
//
//                          STRUCTURES AND TYPES
//
//==============================================================================

/// The tick of the media
typedef MMP_ULONG64 MMP_3GP_TICK;

/** @brief The frame header 
It is the meta data of a video frame. The video player uses this metadata
*/
typedef struct _MMPF_M_FRAME_INFO {
    MMP_ULONG 	ulRequestTime; 		//< [0x03:0x00]The requesting time of this frame in milli-second
    MMP_ULONG 	ulSize;     		//< [0x07:0x04]The size of this frame, including header and padding
    MMP_ULONG 	ulBSSize;     		//< [0x0B:0x08]The size of this bitstream length only
    MMP_ULONG 	ulAddress;  		//< [0x0F:0x0C]The starting address of this frame
    MMP_ULONG 	ulFrameNum;			//< [0x13:0x10]The frame index
    MMP_USHORT 	ulFlag; 			//< [0x15:0x14]The flag of this frame, currently it is used as EOS only.
    MMP_UBYTE 	ubTrackNo; 			//< [0x16:0x16]The track No of this frame
    MMP_UBYTE 	ubIsDualTrack; 		//< [0x17:0x17]Is dual Track?
} MMPF_M_FRAME_INFO, *pFrameInfo;

/** @brief Reference clock type

Which clock to be used as reference in the system.
*/
typedef enum MMPF_M_REFERENCECLOCK{
    MMPF_M_REF_NONE, ///< Use no references
    MMPF_M_REF_AUDIO,///< Use audio or I2S time
    MMPF_M_REF_VIDEO ///< Use video time
}MMPF_M_REFERENCECLOCK;

/** @brief The video player clock

@note The current video reference clock should use timer
@todo Move to player later
*/
typedef struct MMPF_M_CLOCK{
    MMP_ULONG ulMediaTime; /**< The video player system time. Measured in ms. It's calculated by tick so it
                                has no error propagation problem.*/
    MMP_ULONG ulMicroTime;
    MMP_ULONG ulSpeed;
    MMPF_M_REFERENCECLOCK referenceclock; ///< Which  clock to be referenced, currently is no use at all.
}MMPF_M_CLOCK;

//==============================================================================
//                               MACRO
//==============================================================================

#define ASSIGN_HOST_RETURN_VALUE(index, value) MMPF_HIF_FeedbackParamL(GRP_IDX_VID ,index << 2, value)

#endif

/** @} */ // end of group MMPF_M