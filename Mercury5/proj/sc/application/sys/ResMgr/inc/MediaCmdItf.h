/**
* @file MediaCmdItf.h
*
* This header file defines the types of media commands
*
*/

#ifndef __MEDIACMDITF_H__
#define __MEDIACMDITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdItf.h"

/*=============================================================*/
// Macro Definition
/*=============================================================*/
#define MEDIA_RES_GROUP(_RES_INFO_)     (((0x1F00 & _RES_INFO_)) >> 8)
#define MEDIA_RES_TYPE(_RES_INFO_)      (0x00FF & (_RES_INFO_))
#define MEDIA_RES_INFO(_RES_INFO_)      (0x1FFF & (_RES_INFO_))

#define MEDIA_CONFLICT_RET__EXECUTE                 (0x0010)
#define MEDIA_CONFLICT_RET__WAIT_RSP                (0x0020)
#define MEDIA_CONFLICT_RET__LOW_PRI                 (0x0040)
#define MEDIA_CONFLICT_RET__WAIT_APPSTOP_PENDING    (0x0080)
#define MEDIA_CONFLICT_RET__WAIT_APPSTOP_DROP       (0x0100)

#define MEDIA_CMD_SET_ATTR(pMediaCmd, _FLAG_)       ((pMediaCmd)->uAttribute |= (_FLAG_))
#define MEDIA_CMD_CLEAR_ATTR(pMediaCmd, _FLAG_)     ((pMediaCmd)->uAttribute &= ~(_FLAG_))
#define MEDIA_CMD_CHECK_ATTR(pMediaCmd, _FLAG_)     (0 != ((pMediaCmd)->uAttribute & (_FLAG_)))

#define MEDIA_CMD_ATTR__EXTENSION                   0x10000000

#define MEDIA_CMD_SET_ATTR_EXT(pMediaCmd, _FLAG_)   ((pMediaCmd)->uAttributeExt |= (_FLAG_))
#define MEDIA_CMD_CLEAR_ATTR_EXT(pMediaCmd, _FLAG_) ((pMediaCmd)->uAttributeExt &= (~(_FLAG_) | MEDIA_CMD_ATTR__EXTENSION))
#define MEDIA_CMD_CHECK_ATTR_EXT(pMediaCmd, _FLAG_) (MEDIA_CMD_ATTR__EXTENSION != ((pMediaCmd)->uAttributeExt & (_FLAG_)))

#define MEDIA_CMD_IS_EXT_ATTR(_FLAG_)		    (MEDIA_CMD_ATTR__EXTENSION == ((_FLAG_) & MEDIA_CMD_ATTR__EXTENSION))

/*

*/
#define MEDIA_CMD_NEW_CMD(_ACT_)                    ((_ACT_) << 0)
#define MEDIA_CMD_DEL_CMD(_ACT_)                    ((_ACT_) << 8)
#define MEDIA_CMD_HDL_RSP(_RSP_)                    ((_RSP_) << 16)

#define MEDIA_CMD_GET_NEW_CMD(_PARAM_)              (((_PARAM_) & 0x000000FF) >> 0)
#define MEDIA_CMD_GET_DEL_CMD(_PARAM_)              (((_PARAM_) & 0x0000FF00) >> 8)
#define MEDIA_CMD_GET_RSP(_PARAM_)                  (((_PARAM_) & 0x00FF0000) >> 16)

#define MEDIA_CMD_IS_INFOMAPP(pMediaCmd, _FLAG_)    (((pMediaCmd)->uAttribute & MEDIA_CMD_ATTR__AUD_INFORM_APP_M2_CNF) && ((pMediaCmd)->uAttribute & MEDIA_CMD_ATTR__AUD_INFORM_APP_BT_CNF))
/*
    The flag definitions of media command attributes. Please notice that 0x0000~0x00FF
    are reserved for general media command attributes and 0x0100~0xFF00 are reserved
    for specific media command attributes
*/

/****************************************************************************/
/*                                                                          */
/*                     Media Command generic attributes                     */
/*                                                                          */
/****************************************************************************/
//
// Native attributes
// Since native attributes is exhausted, please add new attributes
//  to extension attributes

/* The command is interrupted by others or not. For automatic resume. */
#define MEDIA_CMD_ATTR__INTERRUPTED                     0x00000001

/*
The command is interrupted by same application or not.
To prevent B interrupt A, receive B's response, will find command A, then interrupt B
*/
#define MEDIA_CMD_ATTR__BEEN_INTERRUPTED                0x00000002

#define MEDIA_CMD_ATTR__BEEN_STOP                       0x00000004

/* The command is loop-played style */
#define MEDIA_CMD_ATTR__LOOP_PLAY                       0x00000008

/* The command is process restart- stop current BT/M2 */
#define MEDIA_CMD_ATTR__PROC_RESTART_STOP               0x00000010

/* The command is master command */
#define MEDIA_CMD_ATTR__MASTER_CMD                      0x00000020

/* The command is slave command */
#define MEDIA_CMD_ATTR__SLAVE_CMD                       0x00000040

/* The command is alive */
#define MEDIA_CMD_ATTR__ALIVE                           0x00000080

/* Following two commands are for interactive suspend when interrupt happened */
#define MEDIA_CMD_ATTR__WAIT_APP_STOP                   0x00000100

#define MEDIA_CMD_ATTR__DEFER_DELETE                    0x00000200

/* The command is loop playing */
#define MEDIA_CMD_ATTR__LOOP_PLAYING                    0x00000400

/*
    This attribute is for power off procedure. ResMgr will perform two actions:
    1. Mark executing commands as MEDIA_CMD_ATTR__FINALIZE, so that the command
       will not be queued even though it's resume type is MEDIA_CMD_RESUME
    2. Flush command queue.
*/
#define MEDIA_CMD_ATTR__FINALIZE                        0x00000800

#define MEDIA_CMD_ATTR__PROCESSING                      0x00001000
/****************************************************************************/
/*                                                                          */
/*                     Audio Command specific attributes                    */
/*                                                                          */
/****************************************************************************/
/* For audio play, we have to set media configuration (ex. PEQ) before automatic resume */

/*
    Resource manager will not update the audio volume if the following situations happen.
    1. Media command will sync the background volume.
    2. Media command will bring its own volume setting.
*/
#define MEDIA_CMD_ATTR__AUD_NON_UPDATE_VOLUME           0x00002000
/*
    Resource manager will not update the audio path if the following situations happen.
    1. Media command will sync the background volume.
    2. Media command will bring its own volume setting.
*/
#define MEDIA_CMD_ATTR__AUD_NON_UPDATE_PATH             0x00004000
/*
    Resource manager will update the temp volume if the following situations happen.
    1. Ap set temp volume already but ResMgr will set profile volume again when plugging in/out Headset .
       (PR#0084469, 0090128, 0087658)
*/
#define MEDIA_CMD_ATTR__AUD_UPDATE_TEMP_VOLUME          0x00008000
/*
    Resource manager will inform applications of interrupt happened once
    when interrupt happened and will inform applications of interrupt ended
    once when interrupt ended and won't inform applications confirmation of
    play command any more.
*/
#define MEDIA_CMD_ATTR__INFORM_APP_INTERRUPT_HAPPEN     0x00010000
#define MEDIA_CMD_ATTR__INFORM_APP_INTERRUPT_END        0x00020000

/*
    When command is in loop play session (play more than once), resource manager
    should not inform applications of confirm of proceeding play commands
*/
#define MEDIA_CMD_ATTR__INFORMED_APP                    0x00040000

/*
    BT related attributes
*/
#define MEDIA_CMD_ATTR__SUPPORT_BT                      0x00080000

#define MEDIA_CMD_ATTR__BT_STARTED                      0x00100000

#define MEDIA_CMD_ATTR__BT_STOP_PLAY                    0x00200000

#define MEDIA_CMD_ATTR__BT_STATUS_CHANGE                0x00400000

#define MEDIA_CMD_ATTR__BT_RESTART_STOPBT               0x00800000
#define MEDIA_CMD_ATTR__BT_RESTART_STARTBT              0x01000000
#define MEDIA_CMD_ATTR__BT_RESTART_STOPM2               0x02000000
#define MEDIA_CMD_ATTR__BT_RESTART_PLAYM2               0x04000000

/*
    For B3, to inform BT service of A2DP status
*/
#define MEDIA_CMD_ATTR__BT_STATUS_STARTED               0x08000000


// Extend attributes
// Please add new attributes here

/*
    Prefer path will be clean when master cmd been destroy or the master cmd execute fail.
    It need to clear prefer path when the master cmd was suspend and merged in queue.
    We use this attribute to mark the master cmd when put it into queue.
    When the cmd was merged, we will clear prefer path depend on this attribute.
    Use case:
    1. Fm set prefer path before open session
    2. Fm was interruped, put master cmd into queue.(mark here)
    3. Plug up headset, service will request close session.
    4. Open session will be merge.(clear here)
*/
#define MEDIA_CMD_ATTR__CLEAR_PREF_PATH_WHEN_DESTROY    0x10000001

// for resume process
#define MEDIA_CMD_ATTR__RESUME_PROCESS                  0x10000002

#define MEDIA_CMD_ATTR__DEFER_STOP                      0x10000004

#define MEDIA_CMD_ATTR__FORCE_RESUME                    0x10000008

// for resume restart
#define MEDIA_CMD_ATTR__RESUME_RESTART                  0x10000010

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaCmdType_e_
{
    MEDIA_CMD_TYPE__PLAY,
    MEDIA_CMD_TYPE__EXEC,
    MEDIA_CMD_TYPE__STOP,
    MEDIA_CMD_TYPE__EXEC_NO_RESTRICT,
    MEDIA_CMD_TYPE__RESTART,
    MEDIA_CMD_TYPE__SYS_STOP,
    MEDIA_CMD_TYPE__NUM,
    MEDIA_CMD_TYPE__INVALID,
    MEDIA_CMD_TYPE__ALL_TYPE = 0xFF
} MediaCmdType_e;

typedef enum MediaCmdSuspend_e_
{
    MEDIA_CMD_SUSPEND__AUTO,
    MEDIA_CMD_SUSPEND__INTERACTIVE,
    MEDIA_CMD_SUSPEND__NUM,
    MEDIA_CMD_SUSPEND__CONFIGURABLE = MEDIA_CMD_SUSPEND__NUM
} MediaCmdSuspend_e;

typedef enum MediaCmdResume_e_
{
    MEDIA_CMD_RESUME,
    MEDIA_CMD_RESUME__NONE,
    MEDIA_CMD_RESUME__NUM,
    MEDIA_CMD_RESUME__CONFIGURABLE = MEDIA_CMD_RESUME__NUM
} MediaCmdResume_e;

typedef struct MediaCmdAttribute_t_
{
    MediaCmdType_e eMediaCmdType;
    MediaCmdSuspend_e eMediaCmdSuspend;
    MediaCmdResume_e eMediaCmdResume;
} MediaCmdAttribute_t;

typedef enum MediaEvtActGroup_e_
{
    MEDIA_EVT_ACT_GROUP__AUD,
    MEDIA_EVT_ACT_GROUP__VDO,
    MEDIA_EVT_ACT_GROUP__CAM,
    MEDIA_EVT_ACT_GROUP__FMR,
    MEDIA_EVT_ACT_GROUP__USB,
    MEDIA_EVT_ACT_GROUP__GSS,
    MEDIA_EVT_ACT_GROUP__TV,
    MEDIA_EVT_ACT_GROUP__VFS,
    MEDIA_EVT_ACT_GROUP__VTM,
    MEDIA_EVT_ACT_GROUP__NUM,
    MEDIA_EVT_ACT_GROUP__UNKNOWN
} MediaEvtActGroup_e;

typedef enum MediaCmdActType_e_
{
    /*=========== Audio ============*/
    MEDIA_CMD_ACT__AUD_BEGIN,
    MEDIA_CMD_ACT__AUD_SET_MUTE = MEDIA_CMD_ACT__AUD_BEGIN,
    MEDIA_CMD_ACT__AUD_SET_UNMUTE,
    MEDIA_CMD_ACT__AUD_ENABLE_SPEECH,
    MEDIA_CMD_ACT__AUD_DISABLE_SPEECH,
    MEDIA_CMD_ACT__AUD_OPEN_SPEECH_SESSION,
    MEDIA_CMD_ACT__AUD_CLOSE_SPEECH_SESSION,
    MEDIA_CMD_ACT__AUD_PLAY_KEYPAD_TONE,
    MEDIA_CMD_ACT__AUD_PLAY_TONE,
    MEDIA_CMD_ACT__AUD_PLAY_STREAM,
    MEDIA_CMD_ACT__AUD_PLAY_STREAM_ADD_BUFFER,
    MEDIA_CMD_ACT__AUD_PLAY_MEMORY,
    MEDIA_CMD_ACT__AUD_PLAY_FILE,
    MEDIA_CMD_ACT__AUD_GET_ID3_INFO,
    MEDIA_CMD_ACT__AUD_GET_ADV_INFO,
    MEDIA_CMD_ACT__AUD_GET_FILE_INFO,
    MEDIA_CMD_ACT__AUD_GET_STREAM_INFO,
    MEDIA_CMD_ACT__AUD_GET_MEMORY_INFO,
    MEDIA_CMD_ACT__AUD_GET_REC_REMAIN_TIME,
    MEDIA_CMD_ACT__AUD_SET_PEQ_TBL_ADDR,
    MEDIA_CMD_ACT__AUD_GET_PEQ_TBL_ADDR,
    MEDIA_CMD_ACT__AUD_SET_POS,
    MEDIA_CMD_ACT__AUD_GET_POS,
    MEDIA_CMD_ACT__AUD_SEEK_CANCEL,
    MEDIA_CMD_ACT__AUD_START_RECORD,
    MEDIA_CMD_ACT__AUD_STOP_RECORD,
    MEDIA_CMD_ACT__AUD_SET_PREPROCESS_TBL_ADDR,
    MEDIA_CMD_ACT__AUD_GET_PREPROCESS_TBL_ADDR,
    MEDIA_CMD_ACT__AUD_SET_RECORD_SETTING,
    MEDIA_CMD_ACT__AUD_SAVE_REC_FILE,
    MEDIA_CMD_ACT__AUD_DISCARD_REC_FILE,
    MEDIA_CMD_ACT__AUD_GET_PLAYBACK_CAPABILITY,
    MEDIA_CMD_ACT__AUD_GET_RECORDING_CAPABILITY,
    MEDIA_CMD_ACT__AUD_GET_RECORD_FILE,
    MEDIA_CMD_ACT__AUD_STOP_PLAY,
    MEDIA_CMD_ACT__AUD_PAUSE_PLAY,
    MEDIA_CMD_ACT__AUD_RESUME_PLAY,
    MEDIA_CMD_ACT__AUD_OPEN_SESSION,
    MEDIA_CMD_ACT__AUD_CLOSE_SESSION,
    MEDIA_CMD_ACT__AUD_OPEN_REC_SESSION,
    MEDIA_CMD_ACT__AUD_CLOSE_REC_SESSION,
    MEDIA_CMD_ACT__AUD_INIT_RECORDER,
    MEDIA_CMD_ACT__AUD_INIT_PCM_RECORDER,
    MEDIA_CMD_ACT__AUD_UNINIT_RECORDER,
    MEDIA_CMD_ACT__AUD_PCM_START_RECORD,
    MEDIA_CMD_ACT__AUD_PCM_STOP_RECORD,
    MEDIA_CMD_ACT__AUD_SET_MUSIC_MODE,
#ifdef __DISTORTED_VOICE_MMI__
    MEDIA_CMD_ACT__AUD_SET_DISTORTED_VOICE,
    MEDIA_CMD_ACT__AUD_END = MEDIA_CMD_ACT__AUD_SET_DISTORTED_VOICE,
#else
    MEDIA_CMD_ACT__AUD_END = MEDIA_CMD_ACT__AUD_SET_MUSIC_MODE,
#endif
    /*=========== Video ============*/
    MEDIA_CMD_ACT__VDO_BEGIN,
    MEDIA_CMD_ACT__VDO_OPEN_SESSION = MEDIA_CMD_ACT__VDO_BEGIN,
    MEDIA_CMD_ACT__VDO_CLOSE_SESSION,
    MEDIA_CMD_ACT__VDO_GET_POS,
    MEDIA_CMD_ACT__VDO_GET_FILE_INFO,
    MEDIA_CMD_ACT__VDO_SET_PLAY_SPEED,
    MEDIA_CMD_ACT__VDO_SET_POS,
    MEDIA_CMD_ACT__VDO_PLAY_RESET_WINDOW,
#ifdef __MMI_STEREO_VIDEO__
    MEDIA_CMD_ACT__VDO_SET_CONFIGURATION,
#endif
    MEDIA_CMD_ACT__VDO_STOP_PLAY,
    MEDIA_CMD_ACT__VDO_PAUSE_PLAY,
    MEDIA_CMD_ACT__VDO_RESUME_PLAY,
    MEDIA_CMD_ACT__VDO_GET_MEM_INFO,
    MEDIA_CMD_ACT__VDO_GET_PLAYBACK_CAPABILITY,
    MEDIA_CMD_ACT__VDO_OPEN,
    MEDIA_CMD_ACT__VDO_CLOSE,
    MEDIA_CMD_ACT__VDO_PLAY,
    MEDIA_CMD_ACT__VDO_GET_INFO,
    MEDIA_CMD_ACT__VDO_DECODE_FIRST_FRAME_ASYNC,
    MEDIA_CMD_ACT__VDO_CANCEL_DECODE_FIRST_FRAME,
    MEDIA_CMD_ACT__VDO_SEEK,
    MEDIA_CMD_ACT__VDO_CANCEL_SEEK,
    MEDIA_CMD_ACT__VDO_END = MEDIA_CMD_ACT__VDO_CANCEL_SEEK,
    /*=========== Camera ============*/
    MEDIA_CMD_ACT__CAM_BEGIN,
    MEDIA_CMD_ACT__CAM_OPEN_SESSION = MEDIA_CMD_ACT__CAM_BEGIN,
    MEDIA_CMD_ACT__CAM_CLOSE_SESSION,
    MEDIA_CMD_ACT__CAM_OPEN,
    MEDIA_CMD_ACT__CAM_CLOSE,
    MEDIA_CMD_ACT__CAM_SET_CONFIG,
    MEDIA_CMD_ACT__CAM_SET_ATTRIBUTE,
    MEDIA_CMD_ACT__CAM_PREVIEW,
    MEDIA_CMD_ACT__CAM_PREVIEW_STOP,
    MEDIA_CMD_ACT__CAM_CAPTURE,
    MEDIA_CMD_ACT__CAM_CAPTURE_STOP,
#ifdef __CAMERA_QRCODE_MMI__
    MEDIA_CMD_ACT__CAM_QRC_START,
    MEDIA_CMD_ACT__CAM_QRC_STOP,
#endif
    MEDIA_CMD_ACT__CAM_REC_START,
    MEDIA_CMD_ACT__CAM_REC_STOP,
    MEDIA_CMD_ACT__CAM_GET_FILE_NAME,
    MEDIA_CMD_ACT__CAM_SET_REC_SETTING,
    MEDIA_CMD_ACT__CAM_REC_SAVE_FILE,
    MEDIA_CMD_ACT__CAM_REC_DISCARD_FILE,
    MEDIA_CMD_ACT__CAM_GET_CAMERA_INFO,
    MEDIA_CMD_ACT__CAM_GET_CAPTURE_CAPABILITY,
    MEDIA_CMD_ACT__CAM_GET_RECORDING_CAPABILITY,
#ifdef __CAMERA_QRCODE_MMI__
    MEDIA_CMD_ACT__CAM_GET_QRC_INFO,
#endif
#ifdef __CAMERA_STICKER_MMI__
    MEDIA_CMD_ACT__CAM_SET_STICKER,
#endif
    MEDIA_CMD_ACT__CAM_GET_STATUS,
    MEDIA_CMD_ACT__CAM_GET_IMAGE,
    MEDIA_CMD_ACT__CAM_GET_CAPTURE_QUOTA,
    MEDIA_CMD_ACT__CAM_ENABLE_MOTION_DETECT,
    MEDIA_CMD_ACT__CAM_DISABLE_MOTION_DETECT,
    MEDIA_CMD_ACT__CAM_START_AUTOFOCUS,
    MEDIA_CMD_ACT__CAM_ABORT_PANORAMA_CAPTURE,
    MEDIA_CMD_ACT__CAM_END = MEDIA_CMD_ACT__CAM_ABORT_PANORAMA_CAPTURE,
    /*=========== FM Radio ============*/
    MEDIA_CMD_ACT__FMR_BEGIN,
    MEDIA_CMD_ACT__FMR_POWER_ON = MEDIA_CMD_ACT__FMR_BEGIN,
    MEDIA_CMD_ACT__FMR_POWER_OFF,
    MEDIA_CMD_ACT__FMR_SET_BAND,
    MEDIA_CMD_ACT__FMR_SET_MUTE,
    MEDIA_CMD_ACT__FMR_SET_UNMUTE,
    MEDIA_CMD_ACT__FMR_SET_STEREO,
    MEDIA_CMD_ACT__FMR_SET_FREQUENCY,
    MEDIA_CMD_ACT__FMR_SET_AREA,
    MEDIA_CMD_ACT__FMR_SET_CARRIERTHRESHOLD,
    MEDIA_CMD_ACT__FMR_SEARCH_CHANNEL,
    MEDIA_CMD_ACT__FMR_CANCEL_SEARCH,
    MEDIA_CMD_ACT__FMR_GET_CHAN_INFO,
    MEDIA_CMD_ACT__FMR_GET_CHIP_INFO,
    MEDIA_CMD_ACT__FMR_GET_CAPABILITY,
    MEDIA_CMD_ACT__FMR_REC_START,
    MEDIA_CMD_ACT__FMR_REC_STOP,
    MEDIA_CMD_ACT__FMR_SET_RECORD_SETTING,
    MEDIA_CMD_ACT__FMR_SAVE_REC_FILE,
    MEDIA_CMD_ACT__FMR_DISCARD_REC_FILE,
    MEDIA_CMA_ACT__FMR_GET_REC_FILE_NAME,
    MEDIA_CMD_ACT__FMR_OPEN_SESSION,
    MEDIA_CMD_ACT__FMR_CLOSE_SESSION,
    MEDIA_CMD_ACT__FMR_END = MEDIA_CMD_ACT__FMR_CLOSE_SESSION,
    /*=========== USB ============*/
    MEDIA_CMD_ACT__USB_BEGIN,
    MEDIA_CMD_ACT__USB_OPEN_SESSION = MEDIA_CMD_ACT__USB_BEGIN,
    MEDIA_CMD_ACT__USB_CLOSE_SESSION,
    MEDIA_CMD_ACT__USB_OPEN,
    MEDIA_CMD_ACT__USB_CLOSE,
    MEDIA_CMD_ACT__USB_ATTACH,
    MEDIA_CMD_ACT__USB_ATTACH_AND_POLLING,
    MEDIA_CMD_ACT__USB_STOP_POLLING,
    MEDIA_CMD_ACT__USB_END = MEDIA_CMD_ACT__USB_STOP_POLLING,
    /*=========== GSS(Codec) ============*/
    MEDIA_CMD_ACT__GSS_BEGIN,
    MEDIA_CMD_ACT__GSS_OPEN_SESSION = MEDIA_CMD_ACT__GSS_BEGIN,
    MEDIA_CMD_ACT__GSS_CLOSE_SESSION,
    MEDIA_CMD_ACT__GSS_SET_EXIF,
    MEDIA_CMD_ACT__GSS_DECODE_REGION,
    MEDIA_CMD_ACT__GSS_DECODE_EXT,
    MEDIA_CMD_ACT__GSS_ENCODE,
    MEDIA_CMD_ACT__GSS_OPEN,
    MEDIA_CMD_ACT__GSS_CLOSE,
    MEDIA_CMD_ACT__GSS_DECODE_SYNC,
    MEDIA_CMD_ACT__GSS_DECODE_NEXT_FRAME,
    MEDIA_CMD_ACT__GSS_GET_IMAGE_INFO,
    MEDIA_CMD_ACT__GSS_GET_RAPID_IMAGE_INFO,
    MEDIA_CMD_ACT__GSS_GET_DECODING_CAPABILITY,
    MEDIA_CMD_ACT__GSS_RENDER_START,
    MEDIA_CMD_ACT__GSS_RENDER_STOP,
    MEDIA_CMD_ACT__GSS_RENDER_INPUT,
    MEDIA_CMD_ACT__GSS_RENDER_GET_CAPABILITY,
    MEDIA_CMD_ACT__GSS_RENDER_GET_INFO,
    MEDIA_CMD_ACT__GSS_RENDER_CLEAN_UP,
    MEDIA_CMD_ACT__GSS_OPEN_PLAYER,
    MEDIA_CMD_ACT__GSS_CLOSE_PLAYER,
    MEDIA_CMD_ACT__GSS_OPEN_COLOR_CONVERT,
    MEDIA_CMD_ACT__GSS_CLOSE_COLOR_CONVERT,
    MEDIA_CMD_ACT__GSS_CONVERT_COLOR,
    MEDIA_CMD_ACT__GSS_END = MEDIA_CMD_ACT__GSS_CONVERT_COLOR,
#ifdef __ATV_MMI__
    /*=========== TV ============*/
    MEDIA_CMD_ACT__TV_BEGIN,
    MEDIA_CMD_ACT__TV_OPEN_SESSION = MEDIA_CMD_ACT__TV_BEGIN,
    MEDIA_CMD_ACT__TV_CLOSE_SESSION,
    MEDIA_CMD_ACT__TV_OPEN,
    MEDIA_CMD_ACT__TV_CLOSE,
    MEDIA_CMD_ACT__TV_SET_CONFIG,
    MEDIA_CMD_ACT__TV_GET_INFO,
    MEDIA_CMD_ACT__TV_GET_EM_INFO,
    MEDIA_CMD_ACT__TV_SWITCH_CHANNEL,
    MEDIA_CMD_ACT__TV_SCAN_CHANNEL,
    MEDIA_CMD_ACT__TV_PREVIEW,
    MEDIA_CMD_ACT__TV_PREVIEW_STOP,
    MEDIA_CMD_ACT__TV_CAPTURE,
    MEDIA_CMD_ACT__TV_RESET_WINDOW,
    MEDIA_CMD_ACT__TV_SET_SHUTTER_SOUND,
    MEDIA_CMD_ACT__TV_GET_FILE_NAME,
    MEDIA_CMD_ACT__TV_END = MEDIA_CMD_ACT__TV_GET_FILE_NAME,
#endif
    /*=========== VFS ============*/
    MEDIA_CMD_ACT__VFS_BEGIN,
    MEDIA_CMD_ACT__VFS_OPEN_SESSION = MEDIA_CMD_ACT__VFS_BEGIN,
    MEDIA_CMD_ACT__VFS_CLOSE_SESSION,
    MEDIA_CMD_ACT__VFS_END = MEDIA_CMD_ACT__VFS_CLOSE_SESSION,
#ifndef __VENDOR_SMALLROM__
    /*=========== VDOCHAT ============*/
    MEDIA_CMD_ACT__VDOCHAT_BEGIN,
    MEDIA_CMD_ACT__VDOCHAT_OPEN_SESSION = MEDIA_CMD_ACT__VDOCHAT_BEGIN,
    MEDIA_CMD_ACT__VDOCHAT_CLOSE_SESSION,
    MEDIA_CMD_ACT__VDOCHAT_INIT,
    MEDIA_CMD_ACT__VDOCHAT_EXIT,
    MEDIA_CMD_ACT__VDOCHAT_PREVIEW_START,
    MEDIA_CMD_ACT__VDOCHAT_PREVIEW_STOP,
    MEDIA_CMD_ACT__VDOCHAT_PREVIEW_GET_FRAME,
    MEDIA_CMD_ACT__VDOCHAT_CONVERT_IMAGE,
    MEDIA_CMD_ACT__VDOCHAT_SET_FRAME_BUFF_SIZE,
    MEDIA_CMD_ACT__VDOCHAT_END = MEDIA_CMD_ACT__VDOCHAT_SET_FRAME_BUFF_SIZE,
#endif
#ifdef __GPS__
    /*=========== GPS ============*/
    MEDIA_CMD_ACT__GPS_BEGIN,
    MEDIA_CMD_ACT__GPS_OPEN_SESSION = MEDIA_CMD_ACT__GPS_BEGIN,
    MEDIA_CMD_ACT__GPS_CLOSE_SESSION,
    MEDIA_CMD_ACT__GPS_OPEN,
    MEDIA_CMD_ACT__GPS_CLOSE,
    MEDIA_CMD_ACT__GPS_START,
    MEDIA_CMD_ACT__GPS_STOP,
    MEDIA_CMD_ACT__GPS_READ_DATA,
    MEDIA_CMD_ACT__GPS_IOCTL,
    MEDIA_CMD_ACT__GPS_CHANGE_PS_MODE,
    MEDIA_CMD_ACT__GPS_END = MEDIA_CMD_ACT__GPS_CHANGE_PS_MODE,
#endif
    /*=========== VTM ============*/
    MEDIA_CMD_ACT__VTM_BEGIN,
    MEDIA_CMD_ACT__VTM_OPEN_SESSION = MEDIA_CMD_ACT__VTM_BEGIN,
    MEDIA_CMD_ACT__VTM_CLOSE_SESSION,
    MEDIA_CMD_ACT__VTM_OPEN,
    MEDIA_CMD_ACT__VTM_CLOSE,
    MEDIA_CMD_ACT__VTM_START,
    MEDIA_CMD_ACT__VTM_STOP,
    MEDIA_CMD_ACT__VTM_SET_CONFIG,
    MEDIA_CMD_ACT__VTM_START_RECORD,
    MEDIA_CMD_ACT__VTM_STOP_RECORD,
    MEDIA_CMD_ACT__VTM_SAVE_RECORD_FILE,
    MEDIA_CMD_ACT__VTM_DISCARD_RECORD_FILE,
    MEDIA_CMD_ACT__VTM_ABORT_SAVING_FILE,
    MEDIA_CMD_ACT__VTM_END = MEDIA_CMD_ACT__VTM_ABORT_SAVING_FILE,
    MEDIA_CMD_ACT__NORMAL_CMD_NUM,
    /*========= Resource Manager system command action types =========*/
    /*
        Please do not add command types of normal commands in these area. This area is reserved
        for Resource Manager system commands !!!
    */
    MEDIA_CMD_ACT__SYS_FIRST_CMD = MEDIA_CMD_ACT__NORMAL_CMD_NUM,
    MEDIA_CMD_ACT__SYS_RESTART = MEDIA_CMD_ACT__SYS_FIRST_CMD,
    MEDIA_CMD_ACT__SYS_STOP,
    MEDIA_CMD_ACT__SYS_START_BT,
    MEDIA_CMD_ACT__SYS_PAUSE_BT,
    MEDIA_CMD_ACT__SYS_RESUME_BT,
    MEDIA_CMD_ACT__SYS_STOP_BT,
    MEDIA_CMD_ACT__SYS_END_BT,
    MEDIA_CMD_ACT__SYS_FORCE_STOP_BT,
    MEDIA_CMD_ACT__SYS_FORCE_STOP_M2,
    MEDIA_CMD_ACT__SYS_CMD_NUM,
    MEDIA_CMD_ACT__NUM = MEDIA_CMD_ACT__SYS_CMD_NUM,
    MEDIA_CMD_ACT__INVALID = 0xFF
} MediaCmdActType_e;

/*
    All media related command responses are defined here. When Resource Manager execute
    DBL API, it will trigger driver API and receive response. The response is remapped
    and sent to Resource Manager.
*/
typedef enum MediaCmdRspType_e_
{
    /*=========== Audio ============*/
    MEDIA_CMD_RSP__AUD_SET_MUTE,
    MEDIA_CMD_RSP__AUD_SET_UNMUTE,
    MEDIA_CMD_RSP__AUD_SET_PATH,
    MEDIA_CMD_RSP__AUD_SET_VOL,
    MEDIA_CMD_RSP__AUD_ENABLE_SPEECH,
    MEDIA_CMD_RSP__AUD_DISABLE_SPEECH,
    MEDIA_CMD_RSP__AUD_OPEN_SPEECH_SESSION,
    MEDIA_CMD_RSP__AUD_CLOSE_SPEECH_SESSION,
    MEDIA_CMD_RSP__AUD_PLAY_KEYPAD_TONE,
    MEDIA_CMD_RSP__AUD_PLAY_TONE,
    MEDIA_CMD_RSP__AUD_PLAY_STREAM,
    MEDIA_CMD_RSP__AUD_PLAY_STREAM_ADD_BUFFER,
    MEDIA_CMD_RSP__AUD_PLAY_MEMORY,
    MEDIA_CMD_RSP__AUD_PLAY_FILE,
    MEDIA_CMD_RSP__AUD_GET_ID3V1_INFO,
    MEDIA_CMD_RSP__AUD_GET_ADVANCED_INFO,
    MEDIA_CMD_RSP__AUD_GET_FILE_INFO,
    MEDIA_CMD_RSP__AUD_GET_STREAM_INFO,
    MEDIA_CMD_RSP__AUD_GET_MEMORY_INFO,
    MEDIA_CMD_RSP__AUD_GET_REC_REMAIN_TIME,
    MEDIA_CMD_RSP__AUD_SET_PEQ_TBL_ADDR,
    MEDIA_CMD_RSP__AUD_GET_PEQ_TBL_ADDR,
    MEDIA_CMD_RSP__AUD_SET_POSITION,
    MEDIA_CMD_RSP__AUD_GET_POSITION,
    MEDIA_CMD_RSP__AUD_SEEK_CANCEL,
    MEDIA_CMD_RSP__AUD_REC_START,
    MEDIA_CMD_RSP__AUD_REC_STOP,
    MEDIA_CMD_RSP__AUD_SET_PREPROCESS_TBL_ADDR,
    MEDIA_CMD_RSP__AUD_GET_PREPROCESS_TBL_ADDR,
    MEDIA_CMD_RSP__AUD_SET_RECORD_SETTING,
    MEDIA_CMD_RSP__AUD_SAVE_REC_FILE,
    MEDIA_CMD_RSP__AUD_DISCARD_REC_FILE,
	MEDIA_CMD_RSP__AUD_GET_PLAYBACK_CAPABILITY,
    MEDIA_CMD_RSP__AUD_GET_RECORDING_CAPABILITY,
    MEDIA_CMD_RSP__AUD_REC_GET_FILE,
    MEDIA_CMD_RSP__AUD_STOP_PLAY,
    MEDIA_CMD_RSP__AUD_PAUSE_PLAY,
    MEDIA_CMD_RSP__AUD_RESUME_PLAY,
    MEDIA_CMD_RSP__AUD_OPEN_SESSION,
    MEDIA_CMD_RSP__AUD_CLOSE_SESSION,
    MEDIA_CMD_RSP__AUD_OPEN_REC_SESSION,
    MEDIA_CMD_RSP__AUD_CLOSE_REC_SESSION,
    MEDIA_CMD_RSP__AUD_INIT_RECORDER,
    MEDIA_CMD_RSP__AUD_INIT_PCM_RECORDER,
    MEDIA_CMD_RSP__AUD_UNINIT_RECORDER,
    MEDIA_CMD_RSP__AUD_PCM_REC_START,
    MEDIA_CMD_RSP__AUD_PCM_REC_STOP,
    MEDIA_CMD_RSP__AUD_SET_MUSIC_MODE,
#ifdef __DISTORTED_VOICE_MMI__
    MEDIA_CMD_RSP__AUD_SET_DISTORTED_VOICE,
#endif
    /*=================== VDO ===================*/
    MEDIA_CMD_RSP__VDO_OPEN_SESSION,
    MEDIA_CMD_RSP__VDO_CLOSE_SESSION,
    MEDIA_CMD_RSP__VDO_GET_POS,
    MEDIA_CMD_RSP__VDO_GET_FILE_INFO,
    MEDIA_CMD_RSP__VDO_SET_PLAY_SPEED,
    MEDIA_CMD_RSP__VDO_SET_POS,
    MEDIA_CMD_RSP__VDO_RESET_WINDOW,
#ifdef __MMI_STEREO_VIDEO__
    MEDIA_CMD_RSP__VDO_SET_CONFIGURATION,
#endif
    MEDIA_CMD_RSP__VDO_STOP_PLAY,
    MEDIA_CMD_RSP__VDO_PAUSE_PLAY,
    MEDIA_CMD_RSP__VDO_RESUME_PLAY,
    MEDIA_CMD_RSP__VDO_GET_MEM_INFO,
    MEDIA_CMD_RSP__VDO_GET_PLAYBACK_CAPABILITY,
    MEDIA_CMD_RSP__VDO_OPEN,
    MEDIA_CMD_RSP__VDO_CLOSE,
    MEDIA_CMD_RSP__VDO_PLAY,
    MEDIA_CMD_RSP__VDO_GET_INFO,
    MEDIA_CMD_RSP__VDO_DECODE_FIRST_FRAME_ASYNC,
    MEDIA_CMD_RSP__VDO_CANCEL_DECODE_FIRST_FRAME,
    MEDIA_CMD_RSP__VDO_SEEK,
    MEDIA_CMD_RSP__VDO_CANCEL_SEEK,
    /*================== Camera ===================*/
    MEDIA_CMD_RSP__CAM_OPEN_SESSION,
    MEDIA_CMD_RSP__CAM_CLOSE_SESSION,
    MEDIA_CMD_RSP__CAM_OPEN,
    MEDIA_CMD_RSP__CAM_CLOSE,
    MEDIA_CMD_RSP__CAM_SET_CONFIG,
    MEDIA_CMD_RSP__CAM_SET_ATTRIBUTE,
    MEDIA_CMD_RSP__CAM_PREVIEW,
    MEDIA_CMD_RSP__CAM_PREVIEW_STOP,
    MEDIA_CMD_RSP__CAM_CAPTURE,
    MEDIA_CMD_RSP__CAM_CAPTURE_STOP,
#ifdef __CAMERA_QRCODE_MMI__
    MEDIA_CMD_RSP__CAM_QRC_START,
    MEDIA_CMD_RSP__CAM_QRC_STOP,
#endif
    MEDIA_CMD_RSP__CAM_REC_START,
    MEDIA_CMD_RSP__CAM_REC_STOP,
    MEDIA_CMD_RSP__CAM_GET_FILE_NAME,
    MEDIA_CMD_RSP__CAM_SET_REC_SETTING,
    MEDIA_CMD_RSP__CAM_REC_SAVE_FILE,
    MEDIA_CMD_RSP__CAM_REC_DISCARD_FILE,
    MEDIA_CMD_RSP__CAM_GET_CAMERA_INFO,
    MEDIA_CMD_RSP__CAM_GET_CAPTURE_CAPABILITY,
    MEDIA_CMD_RSP__CAM_GET_RECORDING_CAPABILITY,
#ifdef __CAMERA_QRCODE_MMI__
    MEDIA_CMD_RSP__CAM_GET_QRC_INFO,
#endif
#ifdef __CAMERA_STICKER_MMI__
    MEDIA_CMD_RSP__CAM_SET_STICKER,
#endif
    MEDIA_CMD_RSP__CAM_GET_STATUS,
    MEDIA_CMD_RSP__CAM_GET_IMAGE,
    MEDIA_CMD_RSP__CAM_GET_CAPTURE_QUOTA,
    MEDIA_CMD_RSP__CAM_ENABLE_MOTION_DETECT,
    MEDIA_CMD_RSP__CAM_DISABLE_MOTION_DETECT,
    MEDIA_CMD_RSP__CAM_START_AUTOFOCUS,
    MEDIA_CMD_RSP__CAM_ABORT_PANORAMA_CAPTURE,
    /*============== FM Radio ===================*/
    MEDIA_CMD_RSP__FMR_POWER_ON,
    MEDIA_CMD_RSP__FMR_POWER_OFF,
    MEDIA_CMD_RSP__FMR_SET_BAND,
    MEDIA_CMD_RSP__FMR_SET_MUTE,
    MEDIA_CMD_RSP__FMR_SET_UNMUTE,
    MEDIA_CMD_RSP__FMR_SET_STEREO,
    MEDIA_CMD_RSP__FMR_SET_FREQUENCY,
    MEDIA_CMD_RSP__FMR_SET_AREA,
    MEDIA_CMD_RSP__FMR_SET_CARRIERTHRESHOLD,
    MEDIA_CMD_RSP__FMR_SEARCH_CHANNEL,
    MEDIA_CMD_RSP__FMR_CANCEL_SEARCH,
    MEDIA_CMD_RSP__FMR_GET_CHAN_INFO,
    MEDIA_CMD_RSP__FMR_GET_CHIP_INFO,
    MEDIA_CMD_RSP__FMR_GET_CAPABILITY,
    MEDIA_CMD_RSP__FMR_REC_START,
    MEDIA_CMD_RSP__FMR_REC_STOP,
    MEDIA_CMD_RSP__FMR_SET_RECORD_SETTING,
    MEDIA_CMD_RSP__FMR_SAVE_REC_FILE,
    MEDIA_CMD_RSP__FMR_DISCARD_REC_FILE,
    MEDIA_CMA_RSP__FMR_GET_REC_FILE_NAME,
    MEDIA_CMD_RSP__FMR_OPEN_SESSION,
    MEDIA_CMD_RSP__FMR_CLOSE_SESSION,
    /*=================== USB ===================*/
    MEDIA_CMD_RSP__USB_OPEN_SESSION,
    MEDIA_CMD_RSP__USB_CLOSE_SESSION,
    MEDIA_CMD_RSP__USB_OPEN,
    MEDIA_CMD_RSP__USB_CLOSE,
    MEDIA_CMD_RSP__USB_ATTACH,
    MEDIA_CMD_RSP__USB_ATTACH_AND_POLLING,
    MEDIA_CMD_RSP__USB_STOP_POLLING,
    /*================ GSS(Codec) =================*/
    MEDIA_CMD_RSP__GSS_OPEN_SESSION,
    MEDIA_CMD_RSP__GSS_CLOSE_SESSION,
    MEDIA_CMD_RSP__GSS_SET_EXIF,
    MEDIA_CMD_RSP__GSS_DECODE_REGION,
    MEDIA_CMD_RSP__GSS_DECODE_EXT,
    MEDIA_CMD_RSP__GSS_ENCODE,
    MEDIA_CMD_RSP__GSS_OPEN,
    MEDIA_CMD_RSP__GSS_CLOSE,
    MEDIA_CMD_RSP__GSS_DECODE_SYNC,
    MEDIA_CMD_RSP__GSS_DECODE_NEXT_FRAME,
    MEDIA_CMD_RSP__GSS_GET_IMAGE_INFO,
    MEDIA_CMD_RSP__GSS_GET_RAPID_IMAGE_INFO,
    MEDIA_CMD_RSP__GSS_GET_DECODING_CAPABILITY,
    MEDIA_CMD_RSP__GSS_RENDER_START,
    MEDIA_CMD_RSP__GSS_RENDER_STOP,
    MEDIA_CMD_RSP__GSS_RENDER_INPUT,
    MEDIA_CMD_RSP__GSS_RENDER_GET_CAPABILITY,
    MEDIA_CMD_RSP__GSS_RENDER_GET_INFO,
    MEDIA_CMD_RSP__GSS_RENDER_CLEAN_UP,
    MEDIA_CMD_RSP__GSS_OPEN_PLAYER,
    MEDIA_CMD_RSP__GSS_CLOSE_PLAYER,
    MEDIA_CMD_RSP__GSS_OPEN_COLOR_CONVERT,
    MEDIA_CMD_RSP__GSS_CLOSE_COLOR_CONVERT,
    MEDIA_CMD_RSP__GSS_CONVERT_COLOR,
    /*================ TV =================*/
    MEDIA_CMD_RSP__TV_OPEN_SESSION,
    MEDIA_CMD_RSP__TV_CLOSE_SESSION,
    MEDIA_CMD_RSP__TV_OPEN,
    MEDIA_CMD_RSP__TV_CLOSE,
    MEDIA_CMD_RSP__TV_SET_CONFIG,
    MEDIA_CMD_RSP__TV_GET_INFO,
    MEDIA_CMD_RSP__TV_GET_EM_INFO,
    MEDIA_CMD_RSP__TV_SWITCH_CHANNEL,
    MEDIA_CMD_RSP__TV_SCAN_CHANNEL,
    MEDIA_CMD_RSP__TV_PREVIEW,
    MEDIA_CMD_RSP__TV_PREVIEW_STOP,
    MEDIA_CMD_RSP__TV_CAPTURE,
    MEDIA_CMD_RSP__TV_RESET_WINDOW,
    MEDIA_CMD_RSP__TV_SET_SHUTTER_SOUND,
    MEDIA_CMD_RSP__TV_GET_FILE_NAME,
    /*================ TV =================*/
    MEDIA_CMD_RSP__VFS_OPEN_SESSION,
    MEDIA_CMD_RSP__VFS_CLOSE_SESSION,
#ifndef __VENDOR_SMALLROM__
    /*================ VDOCHAT =================*/
    MEDIA_CMD_RSP__VDOCHAT_OPEN_SESSION,
    MEDIA_CMD_RSP__VDOCHAT_CLOSE_SESSION,
    MEDIA_CMD_RSP__VDOCHAT_INIT,
    MEDIA_CMD_RSP__VDOCHAT_EXIT,
    MEDIA_CMD_RSP__VDOCHAT_PREVIEW_START,
    MEDIA_CMD_RSP__VDOCHAT_PREVIEW_STOP,
    MEDIA_CMD_RSP__VDOCHAT_PREVIEW_GET_FRAME,
    MEDIA_CMD_RSP__VDOCHAT_CONVERT_IMAGE,
    MEDIA_CMD_RSP__VDOCHAT_SET_FRAME_BUFF_SIZE,
#endif
#ifdef __GPS__
    /*=========== GPS ============*/
    MEDIA_CMD_RSP__GPS_OPEN_SESSION,
    MEDIA_CMD_RSP__GPS_CLOSE_SESSION,
    MEDIA_CMD_RSP__GPS_OPEN,
    MEDIA_CMD_RSP__GPS_CLOSE,
    MEDIA_CMD_RSP__GPS_START,
    MEDIA_CMD_RSP__GPS_STOP,
    MEDIA_CMD_RSP__GPS_READ_DATA,
    MEDIA_CMD_RSP__GPS_IOCTL,
    MEDIA_CMD_RSP__GPS_CHANGE_PS_MODE,
#endif
    /*================ VTM =================*/
    MEDIA_CMD_RSP__VTM_OPEN_SESSION,
    MEDIA_CMD_RSP__VTM_CLOSE_SESSION,
    MEDIA_CMD_RSP__VTM_OPEN,
    MEDIA_CMD_RSP__VTM_CLOSE,
    MEDIA_CMD_RSP__VTM_START,
    MEDIA_CMD_RSP__VTM_STOP,
    MEDIA_CMD_RSP__VTM_SET_CONFIG,
    MEDIA_CMD_RSP__VTM_START_RECORD,
    MEDIA_CMD_RSP__VTM_STOP_RECORD,
    MEDIA_CMD_RSP__VTM_SAVE_RECORD_FILE,
    MEDIA_CMD_RSP__VTM_DISCARD_RECORD_FILE,
    MEDIA_CMD_RSP__VTM_ABORT_SAVING_FILE,
    /*========= Resource Manager system command response =========*/
    /*
        Please do not add response of normal commands in these area. This area is reserved for
        Resource Manager system commands !!!
    */
    MEDIA_CMD_RSP__SYS_RESTART,
    MEDIA_CMD_RSP__SYS_STOP,
    MEDIA_CMD_RSP__SYS_START_BT,
    MEDIA_CMD_RSP__SYS_PAUSE_BT,
    MEDIA_CMD_RSP__SYS_RESUME_BT,
    MEDIA_CMD_RSP__SYS_STOP_BT,
    MEDIA_CMD_RSP__SYS_END_BT,
    MEDIA_CMD_RSP__SYS_FORCE_STOP_BT,
    MEDIA_CMD_RSP__SYS_FORCE_STOP_M2,
    /* Use for initial value */
    MEDIA_CMD_RSP__INVALID,
} MediaCmdRspType_e;

typedef enum MediaResInfo_e_
{
    /*MEDIA_RES__##Resource Group ##_##Resource Item*/
    MEDIA_RES__AUDIO = 0x0000,
    MEDIA_RES__AUDIO_VOICE,
    MEDIA_RES__AUDIO_FORMAT_BEGIN,
    MEDIA_RES__AUDIO_WAVE = MEDIA_RES__AUDIO_FORMAT_BEGIN,
    MEDIA_RES__AUDIO_MIDI,
    MEDIA_RES__AUDIO_IMY,
    MEDIA_RES__AUDIO_MP3,
    MEDIA_RES__AUDIO_AAC,
    MEDIA_RES__AUDIO_AMR,
    MEDIA_RES__AUDIO_ASF,
    MEDIA_RES__AUDIO_WMA,
    MEDIA_RES__AUDIO_WMV,
    MEDIA_RES__AUDIO_MP4,
    MEDIA_RES__AUDIO_3GP,
    MEDIA_RES__AUDIO_WAVE_EXT,
    MEDIA_RES__AUDIO_MIDI_EVENT,
    MEDIA_RES__AUDIO_PCM,
    MEDIA_RES__AUDIO_RA,
    MEDIA_RES__AUDIO_M4A,
    MEDIA_RES__AUDIO_FORMAT_END = MEDIA_RES__AUDIO_M4A,
    MEDIA_RES__AUDIO_DTMF,
    MEDIA_RES__AUDIO_REC_EXT,
    MEDIA_RES__AUDIO_MEDIA,
    MEDIA_RES__AUDIO_SESSION,
    MEDIA_RES__AUDIO_STEREO_CHANNEL,
    MEDIA_RES__AUDIO_NUM,
    MEDIA_RES__AUDIO_REC = 0x0100,
    MEDIA_RES__AUDIO_REC_VOICE,
    MEDIA_RES__AUDIO_REC_STEREO,
    MEDIA_RES__AUDIO_REC_SESSION,
    MEDIA_RES__AUDIO_REC_NUM,
    MEDIA_RES__AUDIO_VOC = 0x0200,
    MEDIA_RES__AUDIO_VOC_NUM,
    MEDIA_RES__VIDEO = 0x0300,
    MEDIA_RES__VIDEO_MUTE,
    MEDIA_RES__VIDEO_NON_PLAYBACK,
    MEDIA_RES__VIDEO_NUM,
    MEDIA_RES__CAMERA = 0x0400,
    MEDIA_RES__CAMERA_I2C,
    MEDIA_RES__CAMERA_NUM,
    MEDIA_RES__FM_RADIO = 0x0500,
    MEDIA_RES__FM_RADIO_NUM,
    MEDIA_RES__USB = 0x0600,
    MEDIA_RES__USB_MSC,
    MEDIA_RES__USB_CDC,
    MEDIA_RES__USB_NUM,
    MEDIA_RES__TV = 0x0700,
    MEDIA_RES__TV_SHUTTER_SOUND,
    MEDIA_RES__TV_NUM,
    MEDIA_RES__CODEC = 0x0800,
    MEDIA_RES__CODEC_EMU,
    MEDIA_RES__CODEC_SW,
    MEDIA_RES__CODEC_NUM,
    MEDIA_RES__VFS = 0x0900,
    MEDIA_RES__VFS_NUM,
    MEDIA_RES__VDOCHAT = 0x0A00,
    MEDIA_RES__VDOCHAT_NUM,
    MEDIA_RES__GPS = 0x0B00,
    MEDIA_RES__GPS_NUM,
    MEDIA_RES__AUDIO_DEV_CTRL = 0x0C00,
    MEDIA_RES__AUDIO_DEV_CTRL_NUM,
    MEDIA_RES__FM_RADIO_DEV_CTRL = 0x0D00,
    MEDIA_RES__FM_RADIO_DEV_CTRL_NUM,
    MEDIA_RES__VIDEO_DEV_CTRL = 0x0E00,
    MEDIA_RES__VIDEO_DEV_CTRL_NUM,
    MEDIA_RES__CAMERA_DEV_CTRL = 0x0F00,
    MEDIA_RES__CAMERA_DEV_CTRL_NUM,
    MEDIA_RES__USB_DEV_CTRL = 0x1000,
    MEDIA_RES__USB_DEV_CTRL_NUM,
    MEDIA_RES__CODEC_CTRL = 0x1100,
    MEDIA_RES__CODEC_CTRL_NUM,
    MEDIA_RES__VTM = 0x1200,
    MEDIA_RES__VTM_NUM,
    MEDIA_RES__GROUP_NUM = 0x1300,
    MEDIA_RES__ATTR_PLAY_FILE = 0x2000,
    MEDIA_RES__INVALID = 0xFFFF
} MediaResInfo_e;

typedef struct MediaCmdCusParm_t_
{
    MediaResInfo_e eResInfo;
    ResMgrCmdCusParm_t tResMgrCmdCusParm;
} MediaCmdCusParm_t;

typedef enum MediaExecCheckRes_e_
{
    MEDIA_EXEC_CHECK__EXECUTABLE,
    MEDIA_EXEC_CHECK__INEXEC_NO_REQ_CMD,
    MEDIA_EXEC_CHECK__INEXEC_UNACCEPT,
    MEDIA_EXEC_CHECK__INEXEC_CONFLICT,
    MEDIA_EXEC_CHECK__INEXEC_PRIORITY,
    MEDIA_EXEC_CHECK__INEXEC_WAIT_RSP,
    MEDIA_EXEC_CHECK__INEXEC_PENDING,
    MEDIA_EXEC_CHECK__INEXEC_FORCE_DROP,
    MEDIA_EXEC_CHECK__INEXEC_WAIT_APPSTOP_PENDING,
    MEDIA_EXEC_CHECK__INEXEC_WAIT_APPSTOP_DROP,
    MEDIA_EXEC_CHECK__NUM
} MediaExecCheckRes_e;

typedef enum MediaUpdateInfo_e_
{
    MEDIA_UPDATE_INFO__NONE = 0x0000,
    MEDIA_UPDATE_INFO__NORMALRSP,
    MEDIA_UPDATE_INFO__RESET,
    MEDIA_UPDATE_INFO__BTBITRATE,
    MEDIA_UPDATE_INFO__INTERRUPT,
    MEDIA_UPDATE_INFO__SESSION_INFO
} MediaUpdateInfo_e;

typedef enum MediaUpdateAudEnv_e_
{
    AUD_ENV__NONE = 0x0000,
    AUD_ENV__PLAYBACK,
    AUD_ENV__RECORD,
} MediaUpdateAudEnv_e;

typedef enum
{
    /* Audio Recording */
    MEDIA_OUTPUT_FILE = 0,    ///< Record to file-based destination
    MEDIA_OUTPUT_MEMORY,      ///< Record to in-memory destination
    MEDIA_OUTPUT_STREAMING,   ///< Record to streaming destination
    MEDIA_OUTPUT_CALLBACK,    ///< Record to callback-based destination
    /* Audio Playback */
    MEDIA_OUTPUT_IIS,         ///< Decode (playback) to IIS
    MEDIA_OUTPUT_A2DP,        ///< Decode (playback) to A2DP
    /* */
    MEDIA_OUTPUT_NUM
} MediaAudioOutputType_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
u16 Media_QueryChan(ResMgr_CmdHdl_t pCmdHdl);

bool Media_IsCmdWaitRsp(ResMgr_CmdHdl_t pCurCmdHdl);
void Media_BindMasterCmd(ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pMasterCmdHdl);

u16 Media_HandleEvt(CmdMgrStgrHdl_t pStgrHdl, ResMgr_RspHdl_t pRspHdl);
__SLDPM_FREE__ void Media_DenyCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_RspHdl_t pRspHdl);
__SLDPM_FREE__ bool Media_IsCmdRemovable(CmdMgrStgrHdl_t pStgrHdl, ResMgr_RspHdl_t pRspHdl);
void Media_HandleExecFailed(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ ResMgr_ExecCheckRes_e Media_CheckReqCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_PostExecRes_e Media_WaitCmdRsp(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_MergeRes_e Media_CheckMergePairCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pWaitCmdHdl);
ResMgr_ExecCheckRes_e Media_CheckRes(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

/*
    Play command APIs
*/
ResMgr_ExecCheckRes_e Media_CheckPlay(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_CmdPreExecRes_e Media_PrePlay(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_PostExecRes_e Media_PostPlay(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

/*
    Exec command APIs
*/
ResMgr_MergeRes_e Media_CheckMergeExecCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pWaitCmdHdl);
ResMgr_PostExecRes_e Media_PostExec(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

void Media_MergeCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

/*
    Stop command APIs
*/
ResMgr_ExecCheckRes_e Media_CheckStopCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_CmdPreExecRes_e Media_PreStop(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_PostExecRes_e Media_PostStop(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

/*
    ExecNoRst command APIs
*/
__SLDPM_FREE__ ResMgr_ExecCheckRes_e Media_CheckExecNoRst(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ ResMgr_CmdPreExecRes_e Media_PreExecNoRst(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ ResMgr_PostExecRes_e Media_PostExecNoRst(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

/*
    System restart command APIs
*/
ResMgr_ExecCheckRes_e Media_CheckRestart(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_CmdPreExecRes_e Media_PreRestart(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_PostExecRes_e Media_PostRestart(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_MergeRes_e Media_CheckMergeRestartCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pWaitCmdHdl);
/*
    System stop command APIs
*/
ResMgr_ExecCheckRes_e Media_CheckSysStop(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_CmdPreExecRes_e Media_PreSysStop(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
ResMgr_PostExecRes_e Media_PostSysStop(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);

__SLDPM_FREE__ MediaCmdRspType_e Media_GetMediaCmdRsp(ResMgr_CmdHdl_t pCurCmdHdl);
u32 Media_RemapRspOnInterruptOccur(ResMgr_CmdHdl_t pCmdHdl);
bool Media_IsCmdInterrupted(ResMgr_CmdHdl_t pCmdHdl);

bool Media_IsProcRestartStop(ResMgr_CmdHdl_t pCmdHdl);

u32 Media_GetAttribute(ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ void Media_SetAttribute(ResMgr_CmdHdl_t pCurCmdHdl, u32 uAttribute);
void Media_ClearAttribute(ResMgr_CmdHdl_t pCmdHdl, u32 uAttribute);
__SLDPM_FREE__ bool Media_CheckAttribute(ResMgr_CmdHdl_t pCmdHdl, u32 uAttribute);
u32 Media_GetAttributeExt(ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ void Media_SetAttributeExt(ResMgr_CmdHdl_t pCmdHdl, u32 uAttribute);
void Media_ClearAttributeExt(ResMgr_CmdHdl_t pCmdHdl, u32 uAttribute);
__SLDPM_FREE__ bool Media_CheckAttributeExt(ResMgr_CmdHdl_t pCmdHdl, u32 uAttribute);

__SLDPM_FREE__ MediaCmdActType_e Media_GetActionType(ResMgr_CmdHdl_t pCurCmdHdl);
__SLDPM_FREE__ ResMgr_AppId_e Media_GetAppId(ResMgr_CmdHdl_t pCurCmdHdl);
MediaUpdateAudEnv_e Media_GetAudEnvType(ResMgr_CmdHdl_t pCurCmdHdl);

ResMgr_CmdHdl_t Media_FindActCmd(u16 uCmdAct, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_SyncBackgroundVolume(CmdMgrStgrHdl_t pStgrHdl, u8 *pVolume, u8 *pRange, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_SyncBackgroundPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_NonUpdateVolume(ResMgr_CmdHdl_t pCurCmdHdl);
void* Media_GetMergeCmdParms(CmdMgrStgrHdl_t pStgrHdl);
bool Media_HasInformAppInterruptHappen(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_MarkHasInformAppInterruptHappen(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_ClearHasInformAppInterruptHappen(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
bool Media_HasInformAppInterruptEnd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_MarkHasInformAppInterruptEnd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
void Media_ClearHasInformAppInterruptEnd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl);
MediaExecCheckRes_e Media_CheckWaitAPPStop(ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CmdHdl_t pMasterCmd);
void *Media_PackSuspendParms(ResMgr_CmdHdl_t pCurCmdHdl, u32 uPosition);
ResMgr_CmdHdl_t Media_GetRealExecCmd(ResMgr_CmdHdl_t pCmdHdl);
ResMgr_CmdHdl_t Media_GetMasterCmd(ResMgr_CmdHdl_t pCmdHdl);
__SLDPM_FREE__ void Media_TerminateLastPlayCmd(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pMasterCmdHdl);
void Media_GetCurPath(CmdMgrStgrHdl_t pStgrHdl, u32 *pPath, u32 *pChannel);
ResMgr_ErrorCode_e Media_IsHWScalarOccupied(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, bool *pIsHWScalarOccupied);
void Media_SetResumeRestartOutputType(CmdMgrStgrHdl_t pStgrHdl, u8 nOutputType);
ResMgr_CmdHdl_t Media_FindLastPlayCmdByMasterCmd(ResMgr_CmdHdl_t pMasterCmdHdl);

void Media_InformBtCmdStatus(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, bool bBtStart);
void Media_InformBtCmdPauseResume(CmdMgrStgrHdl_t pStgrHdl, bool bBtStart);
#endif //__MEDIACMDITF_H__

