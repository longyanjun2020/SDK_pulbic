/**
 * @file ven_codec_msgt.h
 *
 * This file defines the MMI image and media related request vendor API and
 * MMI response API
 *
 * @version $Id: ven_codec_msgt.h 38996 2009-09-01 02:03:20Z code.lin $
 *
 */

#ifndef __VEN_CODEC_MSGT_H__
#define __VEN_CODEC_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__


#include "ven_codec.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_CODEC_OPEN_MEDIA_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to open media */
/*                                                                          */
/*  Structure : iVen_codec_open_media_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 *pMediaHandle;
    ven_codec_ret_t* pRetCode;
} iVen_codec_open_media_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_OPEN_MEDIA_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                                */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              opening media                                               */
/*                                                                          */
/*  Structure : iVen_codec_open_media_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 mediaHandle;
    ven_codec_ret_t retCode;

} iVen_codec_open_media_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_CLOSE_MEDIA_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to close      */
/*              media                                                       */
/*                                                                          */
/*  Structure : iVen_codec_close_media_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_ret_t* pRetCode;
} iVen_codec_close_media_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_CLOSE_MEDIA_RSP                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              closing media                                               */
/*                                                                          */
/*  Structure : iVen_codec_close_media_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;

} iVen_codec_close_media_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_FILE_INFO_RSP                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting file info                                           */
/*                                                                          */
/*  Structure : iVen_codec_get_file_info_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    ven_codec_mediaFileInfo_t* pFileInfo;
} iVen_codec_get_file_info_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_VDO_EXT_INFO_RSP                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting video extion file info                                           */
/*                                                                          */
/*  Structure : iVen_codec_get_vdo_ext_info_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    u32* pExtInfo;
    u32 nExtInfoLen;
} iVen_codec_get_vdo_ext_info_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_PLAYING_TIME_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get current*/
/*              playing time                                                */
/*                                                                          */
/*  Structure : iVen_codec_get_playing_time_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32  mediaHandle;
    u32* pPlayingTime;
    ven_codec_ret_t* pRetCode;
} iVen_codec_get_playing_time_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_RESOURCE_STATE_IND                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : RM to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting current playing time                                */
/*                                                                          */
/*  Structure : iVen_codec_Resouece_state_ind_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_codec_resource_state_t ResourceState;
} iVen_codec_resource_state_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_FILE_INFO_RSP                           */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting current playing time                                */
/*                                                                          */
/*  Structure : iVen_codec_get_playing_time_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    u32 playingTime;
} iVen_codec_get_playing_time_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio                                                       */
/*                                                                          */
/*  Structure : iVen_codec_play_audio_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u16* pURL;
    u16  urlLen;
    u32 position;
    ven_codec_mediaVolume_t volume;
    bool bLoop;
    void *pCBFunc;  //for play finished
    u32 UserData;   //for play finished
    ven_codec_ret_t* pRetCode;
} iVen_codec_play_audio_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              playing audio                                               */
/*                                                                          */
/*  Structure : iVen_codec_play_audio_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;

} iVen_codec_play_audio_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_RAW_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio                                                       */
/*                                                                          */
/*  Structure : iVen_codec_play_audio_raw_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_mediaFormat_t mediaFormat;
    u8 *pData;
    u32 dataLen;
    ven_codec_mediaVolume_t volume;
    bool bLoop;
    void *pCBFunc;  //for play finished
    u32 UserData;   //for play finished
    ven_codec_ret_t* pRetCode;
} iVen_codec_play_audio_raw_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_RAW_RSP                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              playing audio                                               */
/*                                                                          */
/*  Structure : iVen_codec_play_audio_raw_rsp_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;

} iVen_codec_play_audio_raw_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_MIDI_REQ                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio midi                                                  */
/*                                                                          */
/*  Structure : iVen_codec_play_midi_req_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
enum
{
    IVEN_MIDI_TYPE_TONE,
    IVEN_MIDI_TYPE_CH_VOLUME,
    IVEN_MIDI_TYPE_PROGRAM,
    IVEN_MIDI_TYPE_SHORT_EVENT,
    IVEN_MIDI_TYPE_LONG_EVENT
};

typedef u8 iVen_Midi_Type_t;

typedef struct
{
    u32 note;
    u32 duration;
    u32 volume;

} iVen_codec_midi_tone_t;

typedef struct
{
    u32 channel;
    u32 volume;

} iVen_codec_midi_chVolume_t;

typedef struct
{
    u32 channel;
    u32 bank;
    u32 program;

} iVen_codec_midi_program_t;

typedef struct
{
    u32 type;
    u32 param1;
    u32 param2;

} iVen_codec_midi_shortEvent_t;

typedef struct
{
    u8* pLongEvent;
    u32 length;

} iVen_codec_midi_longEvent_t;


typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;

    iVen_Midi_Type_t midiType;
    union
    {
        iVen_codec_midi_tone_t        midiTone;
        iVen_codec_midi_chVolume_t    midiChVolume;
        iVen_codec_midi_program_t     midiProgram;
        iVen_codec_midi_shortEvent_t  midiShortEvent;
        iVen_codec_midi_longEvent_t   midiLongEvent;
    } param;

    void *pCBFunc;  //for play finished
    u32 UserData;   //for play finished
    ven_codec_ret_t* pRetCode;

} iVen_codec_play_midi_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_MIDI_RSP                         */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio midi                                                  */
/*                                                                          */
/*  Structure : iVen_codec_play_midi_rsp_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;

} iVen_codec_play_midi_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_STREAMING_REQ                    */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio streaming                                             */
/*                                                                          */
/*  Structure : iVen_codec_init_audio_streaming_req_t                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u8 *pData;      //pointer to streaming data
    u32 dataLen;    //streaming data length in byte
    void *pCBFunc;  //for play finished
    u32 UserData;   //for play finished
    ven_codec_ret_t* pRetCode;

} iVen_codec_play_audio_streaming_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_AUDIO_STREAMING_RSP                    */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              audio streaming                                             */
/*                                                                          */
/*  Structure : iVen_codec_play_midi_rsp_t                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u8 *pData; //pointer to streaming data
    ven_codec_ret_t retCode;
} iVen_codec_play_audio_streaming_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_AVAILABLE_AUDIO_STREAM_BUFFER_SIZE_REQ  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get        */
/*              availavle audio streaming buffer size                       */
/*                                                                          */
/*  Structure : iVen_codec_get_available_audio_stream_buffer_size_req_t     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u32 *pAvailableSize; // sync output
    ven_codec_ret_t* pRetCode;

} iVen_codec_get_available_audio_stream_buffer_size_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_AVAILABLE_AUDIO_STREAM_BUFFER_SIZE_RSP  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get        */
/*              availavle audio streaming buffer size                       */
/*                                                                          */
/*  Structure : iVen_codec_get_available_audio_stream_buffer_size_rsp_t     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u32 nSize;
    ven_codec_ret_t retCode;

} iVen_codec_get_available_audio_stream_buffer_size_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_IS_AUDIO_STREAMING_REQ  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get        */
/*              availavle audio streaming buffer size                       */
/*                                                                          */
/*  Structure : iVen_codec_is_audio_streaming_req_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u32 *pStatus;    // sync output
    ven_codec_ret_t* pRetCode;

} iVen_codec_is_audio_streaming_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_IS_AUDIO_STREAMING_RSP  */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get        */
/*              availavle audio streaming buffer size                       */
/*                                                                          */
/*  Structure : iVen_codec_is_audio_streaming_rsp_t                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    u32 nStatus;
    ven_codec_ret_t retCode;

} iVen_codec_is_audio_streaming_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_PAUSE_AUDIO_REQ                             */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to pause      */
/*              audio                                                       */
/*                                                                          */
/*  Structure : iVen_codec_pause_audio_req_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_ret_t* pRetCode;
} iVen_codec_pause_audio_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_PAUSE_AUDIO_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              pausing audio                                               */
/*                                                                          */
/*  Structure : iVen_codec_pause_audio_rsp_t                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_pause_audio_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_RESUME_AUDIO_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to resume     */
/*              audio                                                       */
/*                                                                          */
/*  Structure : iVen_codec_resume_audio_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_ret_t* pRetCode;
} iVen_codec_resume_audio_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_RESUME_AUDIO_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              pausing audio                                               */
/*                                                                          */
/*  Structure : iVen_codec_resume_audio_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_resume_audio_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_STOP_AUDIO_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to stop       */
/*              audio                                                       */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_ret_t* pRetCode;
} iVen_codec_stop_audio_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_STOP_AUDIO_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              stopping audio                                              */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_stop_audio_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_SETPOS_AUDIO_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              setting audio position                                      */
/*                                                                          */
/*  Structure : iVen_codec_set_audio_pos_rsp_t                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_set_audio_pos_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_SET_VOLUME_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to set        */
/*              audio volume                                                */
/*                                                                          */
/*  Structure : iVen_codec_set_audio_volume_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_mediaVolume_t volume;
    ven_codec_ret_t* pRetCode;
} iVen_codec_set_audio_volume_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_SET_VOLUME_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              setting audio volume                                        */
/*                                                                          */
/*  Structure : iVen_codec_set_audio_volume_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_set_audio_volume_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_VOLUME_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get        */
/*              audio volume                                                */
/*                                                                          */
/*  Structure : iVen_codec_get_audio_volume_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_mediaVolume_t* pVolume;
    ven_codec_ret_t* pRetCode;
} iVen_codec_get_audio_volume_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_VOLUME_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              getting audio volume                                        */
/*                                                                          */
/*  Structure : iVen_codec_get_audio_volume_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_mediaVolume_t volume;
    ven_codec_ret_t retCode;

} iVen_codec_get_audio_volume_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_START_AUDIO_STREAM_RECORD_REQ               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to start      */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_start_audio_stream_record_req_t                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_mediaFormat_t format;
    ven_codec_mediaAudFreq_t audFreq;
    u32 bitRate;
    void *pfncb;
    ven_codec_ret_t *pRetCode;
} iVen_codec_start_audio_stream_record_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_START_AUDIO_STREAM_RECORD_RSP               */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI task to Vendor                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_start_audio_stream_record_rsp_t                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_start_audio_stream_record_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_STOP_AUDIO_STREAM_RECORD_REQ                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to stop       */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_stream_record_req_t                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    ven_codec_ret_t *pRetCode;
} iVen_codec_stop_audio_stream_record_req_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_STOP_AUDIO_STREAM_RECORD_RSP                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI task to Vendor                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_stream_record_rsp_t                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_stop_audio_stream_record_rsp_t;


/****************************************************************************/
/*  Message :       I_VEN_CODEC_START_RECORD_RSP                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI task to Vendor                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_stream_record_rsp_t                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_codec_audio_record_rsp_t sResultData;
} iVen_codec_audio_start_record_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_STOP_RECORD_RSP                */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI task to Vendor                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              audio streaming record                                      */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_stream_record_rsp_t                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
	iVen_AsyncRsp_BodyBase_t RspBase;
	ven_codec_audio_record_rsp_t sResultData;
} iVen_codec_audio_stop_record_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_AUDIO_STREAM_RECORD_IND                     */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI task to Vendor                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the indication of         */
/*              incoming data of audio streaming record                     */
/*                                                                          */
/*  Structure : iVen_codec_stop_audio_stream_record_rsp_t                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 mediaHandle;
    u8 *pData;
    u32 dataSize;
    void *pfncb;
} iVen_codec_audio_stream_record_ind_t;
/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_VIDEO_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to play       */
/*              video                                                       */
/*                                                                          */
/*  Structure : iVen_codec_play_video_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u16* pURL;
    u16 urlLen;
} iVen_codec_play_video_req_t;

#ifdef __MMI_OMA_DRM_V1__
typedef struct iVen_codec_check_drmrights_req_t_
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_codec_ret_t *pRetVal;
    u16 *pURL;
} iVen_codec_check_drmrights_req_t;

typedef struct iVen_codec_consume_drmrights_req_t_
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_codec_ret_t *pRetVal;
    u16 *pURL;
} iVen_codec_consume_drmrights_req_t;
#endif
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    Ven_Codec_VideoStreamingInfo_t *pVideoStreamingInfo;
    ven_codec_ret_t* pRetCode;
} iVen_codec_get_videostreaminginfo_req_t;


typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    Ven_Codec_VideoStreamingFileChange_t *pVideoStreamingFileChg;
} iVen_codec_videostreaming_filechange_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 mediaHandle;
    u16* pURL;
    u16 nUrlLen;
    ven_codec_videoStreamingMode_e eStreamingMode;
    bool bUseCusDownloadItf;
    ven_codec_mediaFormat_t nFormat;
    ven_codec_VideoStreaming_DLItf pDLItf;  
} iVen_codec_play_videostreaming_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
} iVen_codec_stop_video_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_codec_SeekMode_e eSeekMode;
} iVen_codec_set_video_seek_req_t;

typedef enum
{    
    IVEN_DOWNLOAD_EVENT_UNINIT = 0,               /// Init & Set parameters is delayed to start download stage
    IVEN_DOWNLOAD_EVENT_START_DOWNLOAD,
    IVEN_DOWNLOAD_EVENT_STOP_DOWNLOAD,
    IVEN_DOWNLOAD_EVENT_NUM
} iVen_codec_videostreaming_download_event_e;

typedef struct
{
    iVen_codec_videostreaming_download_event_e eDownloadEventId;
    s32 mediaHandle;
    struct
    {
        u16 *pUrl;
        u32 nBufferSize;
        u32 nThreshold;
        u32 nPosition;
        bool bSetBufferSize:1;
        bool bSetPosition:1;
        bool bSetThreshold:1;
        bool bSetInitialize:1;
    }sParam;
} iVen_codec_videostreaming_download_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_codec_downloadStatusInfo_t statusInfo;
} iVen_codec_videostreaming_status_change_notify_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_VIDEO_RSP                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              playing video                                               */
/*                                                                          */
/*  Structure : iVen_codec_play_video_rsp_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;

} iVen_codec_play_video_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_PLAY_VIDEO_IND                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the notify information    */
/*              of playing video                                            */
/*                                                                          */
/*  Structure : iVen_codec_play_video_ind_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_play_video_status_t tVideoInd;
} iVen_codec_play_video_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_OPEN_IMAGE_CODEC_REQ                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to open image */
/*                                                                          */
/*  Structure : iVen_codec_open_image_codec_req_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 *pHandle;
    ven_codec_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_codec_open_image_codec_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_OPEN_IMAGE_CODEC_RSP                        */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              opening image                                               */
/*                                                                          */
/*  Structure : iVen_codec_open_image_codec_rsp_t                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 imgCodecHandle;
    ven_codec_ret_t retCode;
} iVen_codec_open_image_codec_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_VideoStreamingProgress_e eProgress; ///< progress of given URL
    ven_codec_ret_t retCode;    
} iVen_codec_get_videostreaminginfo_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    u32 mmiErrCode;    
} iVen_codec_videostreaming_filechange_rsp_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    s32 mediaHandle;
    ven_codec_VideoStreaming_DLItf pDLItf;
    ven_codec_ret_t retCode;
    u32 mmiErrCode;    

    s32  VdoStmAvpEventType;
    u32  EventDataLen;
    union
    {
        vdo_streaming_avp_to_dm_open_t msg_open;
        vdo_streaming_stm_to_dm_init_t msg_init;
        vdo_streaming_stm_to_dm_uninit_t msg_uninit;
        vdo_streaming_stm_to_dm_play_t  msg_play;
        vdo_streaming_stm_to_dm_stop_t msg_stop;
        vdo_streaming_stm_to_dm_pause_t msg_pause;
        vdo_streaming_stm_to_dm_resume_t msg_resume;
        vdo_streaming_stm_to_dm_seek_t msg_seek;
        vdo_streaming_stm_to_dm_data_consumed_t msg_data_consumed;    
    }VdoStmMsg;
    
} iVen_codec_videostreaming_DLItf_rsp_t;
/****************************************************************************/
/*  Message :       I_VEN_CODEC_CLOSE_IMAGE_CODEC_REQ                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to close image*/
/*                                                                          */
/*  Structure : iVen_codec_close_image_codec_req_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 imgCodecHandle;
    ven_codec_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_codec_close_image_codec_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_CLOSE_IMAGE_CODEC_RSP                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              closing imiage                                              */
/*                                                                          */
/*  Structure : iVen_codec_close_image_codec_rsp_t                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
} iVen_codec_close_image_codec_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_DECODE_IMAGE_REQ                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to decode     */
/*              image                                                       */
/*                                                                          */
/*  Structure : iVen_codec_deocde_image_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 imgCodecHandle;
    s32 frame;
    ven_codec_decode_param_t decodeParam;
    ven_GraphicsBitmap *pBitmap; // Bitmap to store decoded image
    const u8 *pSrcBuf; // Source buffer to decode
    u32 bufSize; // Size of source buffer
    u16 *pSrcFileURL; // URL of the source file
    ven_codec_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_codec_imageDecodeStatus_t *pDecodeStatus; //output: only useful if the ReqBase.bSync is TRUE
} iVen_codec_decode_image_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_DECODE_IMAGE_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              closing imiage                                              */
/*                                                                          */
/*  Structure : iVen_codec_deocde_image_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    s32 imgCodecHandle;
    ven_codec_imageDecodeStatus_t decodeStatus;
} iVen_codec_decode_image_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_ENCODE_IMAGE_RSP                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of             */
/*              response the encode message                                 */
/*                                                                          */
/*  Structure : iVen_codec_encode_image_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;   
    ven_codec_ret_t retCode;             ///< return code
    s32 imgCodecHandle;                  ///< the given image codec handle
    u8* pBuffer;                         ///< the mem addr of encoded bitstream
    u32 nBufferLen;                      ///< length of encoded bitstream
} iVen_codec_encode_image_rsp_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_NEXT_IMAGE_FRAME_REQ                    */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get next   */
/*              decodec image frame                                         */
/*                                                                          */
/*  Structure : iVen_codec_deocde_image_req_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    s32 imgCodecHandle;
    ven_codec_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
    ven_codec_imageDecodeStatus_t *pDecodeStatus; //output: only useful if the ReqBase.bSync is TRUE
} iVen_codec_get_next_image_frame_req_t;

/****************************************************************************/
/*  Message :       I_VEN_CODEC_GET_NEXT_IMAGE_FRAME_RSP                    */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the result of getting     */
/*              next decoded imiage                                         */
/*                                                                          */
/*  Structure : iVen_codec_deocde_image_rsp_t                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_codec_ret_t retCode;
    s32 imgCodecHandle;
    ven_codec_imageDecodeStatus_t decodeStatus;
} iVen_codec_get_next_image_frame_rsp_t;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_CODEC_MSGT_H__
