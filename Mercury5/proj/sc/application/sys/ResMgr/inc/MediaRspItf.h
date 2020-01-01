/**
* @file MediaRspItf.h
*
* This header file defines the types of Media Response
*
*/

#ifndef __MEDIARSPITF_H__
#define __MEDIARSPITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_RspItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define MEDIA_RSP_START         RES_MGR__RSP_START(RES_MGR_RES_CATEGORY__MEDIA)

/* For uEvtMask parameter in ABL_RegisterEvtByMask() */
#define MEDIA_EVT_MASK__NONE                    ((u32)(0))
#define MEDIA_EVT_MASK__AUDIO_PLAY(evt)         (1<<(evt-MEDIA_RSP_ID__AUDIO_PLAY_BEGIN))
#define MEDIA_EVT_MASK__AUDIO_REC(evt)          (1<<(evt-MEDIA_RSP_ID__AUDIO_RECORD_BEGIN))
#define MEDIA_EVT_MASK__VIDEO(evt)              (1<<(evt-MEDIA_RSP_ID__VIDEO_BEGIN))
#define MEDIA_EVT_MASK__CAMERA(evt)             (1<<(evt-MEDIA_RSP_ID__CAMERA_BEGIN))
#define MEDIA_EVT_MASK__USB(evt)                (1<<(evt-MEDIA_RSP_ID__USB_BEGIN))
#define MEDIA_EVT_MASK__TV(evt)                 (1<<(evt-MEDIA_RSP_ID__TV_BEGIN))
#define MEDIA_EVT_MASK__FMR(evt)                (1<<(evt-MEDIA_RSP_ID__FMR_BEGIN))
#define MEDIA_EVT_MASK__GPS(evt)                (1<<(evt-MEDIA_RSP_ID__GPS_BEGIN))
#define MEDIA_EVT_MASK__VTM(evt)                (1<<(evt-MEDIA_RSP_ID__VTM_BEGIN))
#define MEDIA_EVT_MASK__SYS(evt)                (1<<(evt-MEDIA_RSP_ID__SYS_BEGIN))

#define MEDIA_RSP__NONE                         0x0000
#define MEDIA_RSP__GENERAL_INFO                 0x0001
#define MEDIA_RSP__INTERRUPT_INFO               0x0002
#define MEDIA_RSP__SESSION_HANDLE_INFO          0x0004
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum MediaEvtGroup_e_
{
    MEDIA_EVT_GROUP__AUDIO_PLAY,
    MEDIA_EVT_GROUP__AUDIO_REC,
    MEDIA_EVT_GROUP__VIDEO,
    MEDIA_EVT_GROUP__CAMERA,
    MEDIA_EVT_GROUP__USB,
    MEDIA_EVT_GROUP__TV,
    MEDIA_EVT_GROUP__FMR,
    MEDIA_EVT_GROUP__GPS,
    MEDIA_EVT_GROUP__VTM,
    MEDIA_EVT_GROUP__RES_MGR,
    MEDIA_EVT_GROUP__UNKNOWN,
    MEDIA_EVT_GROUP__NUM = MEDIA_EVT_GROUP__UNKNOWN
} MediaEvtGroup_e;

typedef enum MediaRspId_e_
{
    MEDIA_RSP_ID__AUDIO_BEGIN = MEDIA_RSP_START,                                    //0
    MEDIA_RSP_ID__AUDIO_PLAY_BEGIN = MEDIA_RSP_ID__AUDIO_BEGIN,
    MEDIA_RSP_ID__AUDIO_VOICE_PLAY_END = MEDIA_RSP_ID__AUDIO_PLAY_BEGIN,            //0     ESL_AUD_NOTIFY_VOICE_PLAY_END
    MEDIA_RSP_ID__AUDIO_VOICE_PLAY_ERROR,                                           //1     ESL_AUD_NOTIFY_VOICE_PLAY_ERROR
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_END,                                            //2     ESL_AUD_NOTIFY_PLAY_END
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_ERROR,                                          //3     ESL_AUD_NOTIFY_PLAY_ERROR
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_POSITION_UPDATE,                                //4     ESL_AUD_NOTIFY_PLAY_POSITION_UPDATE
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_STREAM_UNDERRUN,                                //5     AUDIO_EVENT_PLAYBACK_STREAM_UNDERRUN
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_ADD_BUFFER_DONE,                                //6     ESL_AUD_NOTIFY_PLAY_ADD_BUFFER_DONE
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_BITRATE_CHANGE,                                 //7     ESL_AUD_NOTIFY_PLAY_BITRATE_CHANGE
    MEDIA_RSP_ID__AUDIO_STEREO_PLAY_LYRICS_UPDATE,                                  //8     ESL_AUD_NOTIFY_PLAY_LYRICS_UPDATE
    MEDIA_RSP_ID__AUDIO_STEREO_DEC_SBC_COMPLETE,                                    //9     ESL_AUD_NOTIFY_PLAY_STREAM_DECODE_COMPLETE
    MEDIA_RSP_ID__AUDIO_STEREO_SEEK_COMPLETE,                                       //10    ESL_AUD_NOTIFY_SEEK_COMPLETE
    MEDIA_RSP_ID__AUDIO_STEREO_TOTALPLAYTIME_UPDATE,                                //11    ESL_AUD_NOTIFY_TOTALPLAYTIME_UPDATE
    MEDIA_RSP_ID__AUDIO_PLAY_END = MEDIA_RSP_ID__AUDIO_STEREO_TOTALPLAYTIME_UPDATE, //11
    MEDIA_RSP_ID__AUDIO_RECORD_BEGIN,                                               //12
    MEDIA_RSP_ID__AUDIO_REC_END = MEDIA_RSP_ID__AUDIO_RECORD_BEGIN,                 //12    ESL_AUD_NOTIFY_REC_END
    MEDIA_RSP_ID__AUDIO_REC_SAPCE_FULL,                                             //13    ESL_AUD_NOTIFY_REC_SAPCE_FULL
    MEDIA_RSP_ID__AUDIO_REC_ERROR,                                                  //14    ESL_AUD_NOTIFY_REC_ERROR
    MEDIA_RSP_ID__AUDIO_REC_POSITION_UPDATE,                                        //15    ESL_AUD_NOTIFY_REC_POSITION_UPDATE
    MEDIA_RSP_ID__AUDIO_REC_GENERAL_UPDATE,                                         //16    ESL_AUD_NOTIFY_GENERAL_UPDATE
    MEDIA_RSP_ID__AUDIO_REC_PCM_DATA,                                               //17
    MEDIA_RSP_ID__AUDIO_REC_SAVE_FILE_COMPLETE,                                     //18
    MEDIA_RSP_ID__AUDIO_RECORD_END = MEDIA_RSP_ID__AUDIO_REC_SAVE_FILE_COMPLETE,    //18
    MEDIA_RSP_ID__AUDIO_END = MEDIA_RSP_ID__AUDIO_RECORD_END,                       //18
    MEDIA_RSP_ID__VIDEO_BEGIN,                                                      //19
    MEDIA_RSP_ID__VIDEO_PLAY_END = MEDIA_RSP_ID__VIDEO_BEGIN,                       //19    ESL_VDO_NOTIFY_PLAY_END
    MEDIA_RSP_ID__VIDEO_PLAY_ERROR,                                                 //20    ESL_VDO_NOTIFY_PLAY_ERROR
    MEDIA_RSP_ID__VIDEO_POSITION_UPDATE,                                            //21    ESL_VDO_NOTIFY_POSITION_UPDATE
    MEDIA_RSP_ID__VIDEO_BITRATE_CHANGE,                                             //22    ESL_VDO_NOTIFY_BITRATE_CHANGE
    MEDIA_RSP_ID__VIDEO_IPTV_PACKAGE,                                               //23    ESL_VDO_NOTIFY_IPTV_PACKAGE
    MEDIA_RSP_ID__VIDEO_STREAMING_WRITEBUFFER,                                      //24    ESL_VDO_NOTIFY_STREAMING_WRITEBUFFER
    MEDIA_RSP_ID__VIDEO_OPEN_COMPLETE,                                              //25
    MEDIA_RSP_ID__VIDEO_OPEN_ERROR,                                                 //26
    MEDIA_RSP_ID__VIDEO_DECODE_FIRST_FRAME_COMPLETE,                                //27
    MEDIA_RSP_ID__VIDEO_DECODE_FIRST_FRAME_ERROR,                                   //28
    MEDIA_RSP_ID__VIDEO_SEEK_COMPLETE,                                              //29
    MEDIA_RSP_ID__VIDEO_SEEK_ERROR,                                                 //30
    MEDIA_RSP_ID__VIDEO_REBUFFERING,                                                //31
    MEDIA_RSP_ID__VIDEO_REBUFFERING_DONE,                                           //32
    MEDIA_RSP_ID__VIDEO_REBUFFERING_PROGRESS,                                       //33
    MEDIA_RSP_ID__VIDEO_STREAMING_BYTE_UPDATE,                                      //34
    MEDIA_RSP_ID__VIDEO_STREAMING_TIME_UPDATE,                                      //35
    MEDIA_RSP_ID__VIDEO_DOWNLOAD_PROGRESS_UPDATE,                                   //36
    MEDIA_RSP_ID__VIDEO_DOWNLOAD_ERROR,                                             //37
    MEDIA_RSP_ID__VIDEO_END = MEDIA_RSP_ID__VIDEO_DOWNLOAD_ERROR,                   //37
    MEDIA_RSP_ID__CAMERA_BEGIN,                                                     //38
    MEDIA_RSP_ID__CAMERA_PLAY_SHUTTER_SOUND = MEDIA_RSP_ID__CAMERA_BEGIN,           //38    ESL_CAM_PLAY_SHUTTER_SOUND
    MEDIA_RSP_ID__CAMERA_CAPTURE_STOP,                                              //39    ESL_CAM_CAPTURE_STOP
    MEDIA_RSP_ID__CAMERA_VDO_POSITION_UPDATE,                                       //40    ESL_CAM_VDO_POSITION_UPDATE
    MEDIA_RSP_ID__CAMERA_VDO_REC_STOP,                                              //41    ESL_CAM_VDO_REC_STOP
    MEDIA_RSP_ID__CAMERA_VDO_REC_SPACE_FULL,                                        //42    ESL_CAM_VDO_REC_SPACE_FULL
    MEDIA_RSP_ID__CAMERA_QRC_REC_STOP,                                              //43    ESL_CAM_QRC_REC_STOP
    MEDIA_RSP_ID__CAMERA_REC_ERROR,                                                 //44    ESL_CAM_REC_ERROR
    MEDIA_RSP_ID__CAMERA_REC_SAVE,                                                  //45    ESL_CAM_VDO_REC_SAVE,
    MEDIA_RSP_ID__CAMERA_REC_DELETE,                                                //46    ESL_CAM_VDO_REC_DELETE,
    MEDIA_RSP_ID__CAMERA_REC_ABORT,                                                 //47    ESL_CAM_VDO_REC_ABORT,
    MEDIA_RSP_ID__CAMERA_AUTOFOCUS_COMPLETE,                                        //48    ESL_CAM_AUTOFOCUS_COMPLETE,
    MEDIA_RSP_ID__CAMERA_MOTION_DETECT_IND,                                         //49    ESL_CAM_MOTION_DETECT
    MEDIA_RSP_ID__CAMERA_END = MEDIA_RSP_ID__CAMERA_MOTION_DETECT_IND,              //49
    MEDIA_RSP_ID__USB_BEGIN,                                                        //50
    MEDIA_RSP_ID__USB_MSC_STOP = MEDIA_RSP_ID__USB_BEGIN,                           //50    ESL_USB_MSC_STOP
    MEDIA_RSP_ID__USB_VBUS_CONNECT,                                                 //51    ESL_USB_VBUS_CONNECT
    MEDIA_RSP_ID__USB_VBUS_REMOVE,                                                  //52    ESL_USB_VBUS_REMOVE
    MEDIA_RSP_ID__USB_END = MEDIA_RSP_ID__USB_VBUS_REMOVE,                          //52
    MEDIA_RSP_ID__TV_BEGIN,                                                         //53
    MEDIA_RSP_ID__TV_SHUTTER_SOUND = MEDIA_RSP_ID__TV_BEGIN,                        //53    ESL_TV_NOTIFY_SHUTTER_SOUND
    MEDIA_RSP_ID__TV_CAPTURE_STOP,                                                  //54    ESL_TV_NOTIFY_CAPTURE_STOP
    MEDIA_RSP_ID__TV_CAPTURE_ERROR,                                                 //55    ESL_TV_NOTIFY_CAPTURE_ERROR
    MEDIA_RSP_ID__TV_ESG_DATA,                                                      //56    ESL_TV_NOTIFY_ESG_DATA
    MEDIA_RSP_ID__TV_END = MEDIA_RSP_ID__TV_ESG_DATA,                               //56
    MEDIA_RSP_ID__FMR_BEGIN,                                                        //57
    MEDIA_RSP_ID__FMR_REC_END = MEDIA_RSP_ID__FMR_BEGIN,                            //57    ESL_FMR_NOTIFY_REC_END,
    MEDIA_RSP_ID__FMR_REC_SPACE_FULL,                                               //58    ESL_FMR_NOTIFY_REC_SPACE_FULL
    MEDIA_RSP_ID__FMR_REC_ERROR,                                                    //59    ESL_FMR_NOTIFY_REC_ERROR,
    MEDIA_RSP_ID__FMR_REC_POSITION_UPDATE, 					                        //60    ESL_FMR_NOTIFY_REC_POSITION_UPDATE,
    MEDIA_RSP_ID__FMR_SEARCH_COMPLETE,                                              //61    ESL_FMR_NOTIFY_FM_SEEK_COMPLETE,
    MEDIA_RSP_ID__FMR_SEARCH_ERROR,                                                 //62
    MEDIA_RSP_ID__FMR_END = MEDIA_RSP_ID__FMR_SEARCH_ERROR,                         //62
    MEDIA_RSP_ID__NORMAL_RSP_NUM,                                                   //63
    MEDIA_RSP_ID__BT_BEGIN = MEDIA_RSP_ID__NORMAL_RSP_NUM,                          //63
    MEDIA_RSP_ID__BT_PLAY_POSITION_UPDATE = MEDIA_RSP_ID__BT_BEGIN,                 //63
    MEDIA_RSP_ID__BT_PLAY_ERROR,                                                    //64
    MEDIA_RSP_ID__BT_END = MEDIA_RSP_ID__BT_PLAY_ERROR,                             //64
    MEDIA_RSP_ID__GPS_BEGIN,                                                        //65
    MEDIA_RSP_ID__GPS_GPRMC = MEDIA_RSP_ID__GPS_BEGIN,                              //65
    MEDIA_RSP_ID__GPS_GPGGA,                                                        //66
    MEDIA_RSP_ID__GPS_GPGSA,                                                        //67
    MEDIA_RSP_ID__GPS_GPGSV,                                                        //68
    MEDIA_RSP_ID__GPS_EM_RESP,                                                      //69
    MEDIA_RSP_ID__GPS_RAW,                                                          //70
    MEDIA_RSP_ID__GPS_EOF,                                                          //71
    MEDIA_RSP_ID__GPS_END =  MEDIA_RSP_ID__GPS_EOF,                                 //71
    MEDIA_RSP_ID__VTM_BEGIN,                                                        //72
    MEDIA_RSP_ID__VTM_POSITION_UPDATE = MEDIA_RSP_ID__VTM_BEGIN,                    //72
    MEDIA_RSP_ID__VTM_REC_STOP,                                                     //73
    MEDIA_RSP_ID__VTM_REC_SPACE_FULL,                                               //74
    MEDIA_RSP_ID__VTM_REC_ERROR,                                                    //75
    MEDIA_RSP_ID__VTM_ERROR,                                                        //76
    MEDIA_RSP_ID__VTM_END = MEDIA_RSP_ID__VTM_ERROR,                                //76
    /*========= Resource Manager system response =========*/
    /*
        Please do not add responses of normal commands in these area. This area is reserved
        for Resource Manager system responses !!!
    */
    MEDIA_RSP_ID__SYS_BEGIN,                                                        //77
    MEDIA_RSP_ID__SYS_RESUME = MEDIA_RSP_ID__SYS_BEGIN,                             //77
    MEDIA_RSP_ID__SYS_SUSPEND,                                                      //78
    MEDIA_RSP_ID__SYS_END = MEDIA_RSP_ID__SYS_SUSPEND,                              //78
    MEDIA_RSP_ID__NUM                                                               //79
} MediaRspId_e;

typedef struct MediaSuspendInfo_t_
{
    ResMgr_SuspendType_e eSuspend;
    ResMgr_ResumeType_e eResume;
    u32 uPosition;
} MediaSuspendInfo_t;

typedef struct MediaResumeInfo_t_
{
    ResMgr_SuspendType_e eSuspend;
    ResMgr_ResumeType_e eResume;
} MediaResumeInfo_t;

typedef struct MediaInterruptInfo_t_
{
    MediaRspId_e eRspId;
    union
    {
        MediaResumeInfo_t tResumeInfo;
        MediaSuspendInfo_t tSuspendInfo;
    } tParams;
} MediaInterruptInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIARSPITF_H__

