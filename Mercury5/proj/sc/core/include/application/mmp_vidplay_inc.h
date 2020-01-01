//==============================================================================
//
//  File        : mmp_vidplay_inc.h
//  Description : INCLUDE File for the Firmware Scaler Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_VIDPLAY_INC_H_
#define _MMP_VIDPLAY_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "includes_fw.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define ATOM_LENGTH_SZ			(4)
#define ATOM_TYPE_SZ			(4)
#define ATOM_VER_FLAG_SZ		(4)

#define ATOM_UDTA_MAX_SIZE      (256)
#define ATOM_UDTA_MAX_NUM       (5)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/** @brief Video type of the 3GP file and the firmware.
    The type listed here does not imply that the firmware is able to play it. For example,
    the MPEG4 Advanced simple profile might be recognized but not able to be played.
    The lower level API might return either MMP_VID_VIDEO_MP4V_ASP or MMP_VID_VIDEO_UNSUPPORTED.
    The main purpose to enumerate this value is for futher support.
*/
typedef enum _MMP_VID_VIDEOTYPE {
    MMP_VID_VIDEO_NONE 		= 0,     	///< No video
    MMP_VID_VIDEO_H263 		= 0x1,   	///< H.263
    MMP_VID_VIDEO_MP4V_SP 	= 0x2,		///< MPEG4 Video Simple Profile
    MMP_VID_VIDEO_MP4V 		= 0x2,   	///< MPEG4 Video Simple Profile. MP4V is regarded as simple profile when not specified.
    MMP_VID_VIDEO_MP4V_ASP 	= 0x4,   	///< MPEG4 Video Advanced Simple Profile
    MMP_VID_VIDEO_H264 		= 0x8,    	///< H.264
    MMP_VID_VIDEO_RV 		= 0x10,		///< Real Video
    MMP_VID_VIDEO_WMV 		= 0x20,		///< WMV
    MMP_VID_VIDEO_DIVX 		= 0x40,		///< DIVX
    MMP_VID_VIDEO_MJPG 		= 0x80,  	///< MJPG Video
    MMP_VID_VIDEO_UNSUPPORTED = 0x100,  /**< Unsupported audio type goes here, including some audio type, which can be played
                                           alone only. e.g. RV */
    MMP_VID_VIDEOTYPE_MAX
} MMP_VID_VIDEOTYPE;

/** @brief Audio type of the 3GP file and the firmware
    The type listed here does not imply that the firmware is able to play it. For example,
    the WMA might be recognized but not able to be played with the video.
    The lower level API might return either MMP_VID_AUDIO_WMA or MMP_VID_AUDIO_UNSUPPORTED.
    The main purpose to enumerate this value is for futher support.
*/
typedef enum _MMP_VID_AUDIOTYPE {
    MMP_VID_AUDIO_NONE 		= 0,     	///< No audio
    MMP_VID_AUDIO_AMR_NB 	= 0x1, 		///< AMR-NB
    MMP_VID_AUDIO_AMR 		= 0x1,    	///< If not specified, then AMR means AMR-NB
    MMP_VID_AUDIO_AAC_LC 	= 0x2, 		///< AAC-LC
    MMP_VID_AUDIO_AAC 		= 0x2,    	///< If not specified, then AAC means AAC-LC
    MMP_VID_AUDIO_AAC_PLUS 	= 0x4,    	///< AAC+
    MMP_VID_AUDIO_MP3 		= 0x8,   	///< MP3
    MMP_VID_AUDIO_WMA 		= 0x10,  	///< Microsoft WMA
    MMP_VID_AUDIO_AC3 		= 0x20,   	///< AC3        
    MMP_VID_AUDIO_WAV 		= 0x40,   	///< WAV
    MMP_VID_AUDIO_RA 		= 0x80,  	///< Real Audio
    MMP_VID_AUDIO_UNSUPPORTED = 0x100,  /**< Unsupported audio type goes here, including some audio type, which can be played
                                          alone only. e.g. AMR-WB */
    MMP_VID_AUDIOTYPE_MAX
} MMP_VID_AUDIOTYPE;

/** @brief Indicate or change the component state
 *
 *  The MMP_STATETYPE enumeration is used to indicate or change the component
 *  state.  This enumeration reflects the current state of the component when
 *  used with the MMPS_3GPP_GetState or becomes the parameter in a state change
 *  command when used with the MMPS_3GPP_SendCommand.
 *
 *  The component will be in the Loaded state after the component is initially
 *  loaded into memory.  In the Loaded state, the component is not allowed to
 *  allocate or hold resources other than to build it's internal parameter
 *  and configuration tables.  The application will send one or more
 *  SetParameters/GetParameters and SetConfig/GetConfig commands to the
 *  component and the component will record each of these parameter and
 *  configuration changes for use later.  When the application sends the
 *  Idle command, the component will acquire the resources needed for the
 *  specified configuration and will transition to the idle state if the
 *  allocation is successful.  If the component cannot successfully
 *  transition to the idle state for any reason, the state of the component
 *  shall be fully rolled back to the Loaded state (e.g. all allocated 
 *  resources shall be released).  When the component receives the command
 *  to go to the Executing state, it shall begin processing buffers by
 *  sending all input buffers it holds to the application.  While
 *  the component is in the Idle state, the application may also send the
 *  Pause command.  If the component receives the pause command while in the
 *  Idle state, the component shall send all input buffers it holds to the 
 *  application, but shall not begin processing buffers.  This will allow the
 *  application to prefill buffers.
 *  @image html "image/Component States.png" Component States
 *  @todo GetParameters, GetParameters, SetConfig, GetConfig
 *  @todo Graphics
 */
typedef enum _MMP_M_STATE
{
    MMP_M_STATE_INVALID,			/**< component has detected that it's internal data 
                                		structures are corrupted to the point that
                                		it cannot determine it's state properly */
    MMP_M_STATE_LOADED, 			/**< component has been loaded but has not completed initialization. */
    MMP_M_STATE_IDLE,				/**< component initialization has been completed
                                		successfully and the component is ready to to start. */
    MMP_M_STATE_EXECUTING,			/**< component has accepted the start command and
                                		is processing data (if data is available) */
    MMP_M_STATE_PAUSE,    			/**< component has received pause command */
    MMP_M_STATE_WAIT_FOR_RECOURSES, /**< component is waiting for resources, either after 
                                  		preemption or before it gets the resources requested.*/
    MMP_M_STATE_MAX = 0X7FFFFFFF
} MMP_M_STATE;

typedef enum MMP_VID_COLOR_FMT{
    VID_FMT_NV12,
    VID_FMT_I420,   
    VID_FMT_YUV422
} _MMP_VID_COLOR_FMT;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_VIDEO_INFO
{
    MMP_VID_VIDEOTYPE	format;             	///< video format, such as H263, MPEG4, H264...etc
    MMP_ULONG   		bitrate;           		///< video bitrate, in Kbps
    MMP_USHORT  		width;              	///< video width
    MMP_USHORT  		height;           		///< video height
    MMP_USHORT  		fps;                	///< Frame per second, 0 means unknown
    MMP_USHORT			cropping_left;      	///< the distance between the left boundary and video frame
	MMP_USHORT			cropping_right;     	///< the distance between the right boundary and video frame
	MMP_USHORT			cropping_top;       	///< the distance between the top boundary and video frame
	MMP_USHORT			cropping_bottom;    	///< the distance between the bottom boundary and video frame
	MMP_LONG    		total_video_time;   	///< the duration of the whole video stream
	MMP_ULONG   		total_keyframe_num;		///< total keyframe numbers
	MMP_ULONG   		fccHandler;
	MMP_BOOL    		bInterlacedSequence;
} MMP_VIDEO_INFO;

typedef struct _MMP_AUDIO_INFO
{
    MMP_VID_AUDIOTYPE  	format;            		///< audio format, such as AMR, AAC, AACP...etc
    MMP_ULONG   		bitrate;            	///< audio bitrate, in Kbps
    MMP_ULONG   		sampling_rate;      	///< audio sampling-rate
    MMP_UBYTE   		channel_nums;       	///< number of channels
    MMP_ULONG   		block_align;
	MMP_ULONG   		bits_per_coded_sample;
    MMP_ULONG   		total_audio_time;   	///< the duration of the whole audio stream
} MMP_AUDIO_INFO;

typedef struct _MMP_VIDEO_CONTAINER_INFO {
    MMP_VIDEO_INFO		video_info[2];         	///< video information
    MMP_AUDIO_INFO		audio_info;         	///< audio information
    MMP_ULONG64   		audio_start_time;   	///< audio start time, time origin for A/V sync if audio timestamps are availabled
    MMP_UBYTE    		is_video_available[2]; 	///< Does video stream exist or not
    MMP_UBYTE  			is_audio_available; 	///< Does audio stream exist or not
    MMP_ULONG64  		file_size;          	///< The file size
    MMP_ULONG    		total_file_time;    	///< The total file time in the container (Unit:ms)
    MMP_UBYTE    		is_video_seekable[2];
    MMP_UBYTE  			drm_type;   			///< Which DRM is applied in the container.    
    MMP_UBYTE   		videoTrackNum;
} MMP_VIDEO_CONTAINER_INFO;

/** @brief The UDTA video information in the 3GP video container/file

This information typically does not change during the playing
*/
typedef struct _MMP_USERDATA_TAG {
    MMP_BYTE                bUDta[ATOM_UDTA_MAX_NUM][ATOM_UDTA_MAX_SIZE];
    MMP_ULONG               bUDtaFileOffset[ATOM_UDTA_MAX_NUM];
    MMP_ULONG               ulUDtaAtomname[ATOM_UDTA_MAX_NUM];  
    MMP_USHORT              usUDtaLength[ATOM_UDTA_MAX_NUM];  
    MMP_BOOL                bUDtaFound;
    MMP_BYTE                ubUDtaCount;
} MMP_USERDATA_TAG;

#endif // _MMP_VIDPLAY_INC_H_
