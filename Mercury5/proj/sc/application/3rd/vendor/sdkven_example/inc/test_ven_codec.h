#ifndef __VEN__TEST_CODEC_DEFINE_H__
#define __VEN__TEST_CODEC_DEFINE_H__

/**
 *
 * @file    test_ven_codec.h
 * @brief   This file defines the test cases for codec interface.
 *
 * @author  sam.chen
 * @version $Id: test_ven_codec.h 45468 2009-11-13 05:13:00Z Mobile_CM $
 *
 */

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_codec.h"

enum
{
	CODEC_OPEN_MEDIA,
	CODEC_CLOSE_MEDIA,
	CODEC_GET_FILE_INFO,
	CODEC_GET_RAW_INFO,
	CODEC_GET_VDO_EXT_INFO,
	CODEC_GET_AUD_RAW_INFO,
	CODEC_GET_PLAYING_TIME,
	CODEC_PLAY_AUDIO,
	CODEC_PLAY_AUDIO_RAW,
	CODEC_PLAY_AUDIO_STREAM,
	CODEC_PAUSE_AUDIO,
	CODEC_RESUME_AUDIO,
	CODEC_STOP_AUDIO,
	CODEC_SET_AUDIO_POS,
	CODEC_SET_VOLUME,
	CODEC_GET_VOLUME,
	CODEC_PLAY_MIDI_TONE,
	CODEC_SET_CH_VOLUME,
	CODEC_SET_PROGRAM,
	CODEC_SEND_SHORT_EVENT,
	CODEC_SEND_LONG_EVENT,
	CODEC_PLAY_TONE,
	CODEC_PLAY_VIDEO,
	CODEC_OPEN_IMAGE_CODEC,
	CODEC_CLOSE_IMAGE_CODEC,
    CODEC_DECODE_IMAGE,
    CODEC_GET_NEXT_IMAGE_FRAME,
    CODEC_AUDIO_RECORD,
    CODEC_STOP_AUDIO_RECORD,
    CODEC_AUDIO_STREAM_RECORD,
    CODEC_STOP_AUDIO_STREAM_RECORD,
};


typedef struct{
    u8 APType;
    u32 Data1;
    u32 Data2;
}ven_video_cb_data_t;

typedef void (*AsyncCB)(void);

ven_codec_ret_t ms_ven_codec_testcase_media_open(s32* pHandle, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_close(s32 handle, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_getFileInfo(s32 mediaHandle, u16* pURL, u16 urlLen, ven_codec_mediaFileInfo_t* pInfo, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_getPlayingTime(s32 mediaHandle, u32* pPlayingTime, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_playmidi(s32 mediaHandle, u32 noteNo, u32 duration, u32 volume, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_playAudio(s32 mediaHandle, u16* pURL, u16 urlLen, u32 position, ven_codec_mediaVolume_t volume, bool loop, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_pauseAudio(s32 mediaHandle, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_resumeAudio(s32 mediaHandle, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_stopAudio(s32 mediaHandle, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_setAudioPos(s32 mediaHandle, u32 position, ven_req_data_t reqData);

ven_codec_ret_t ms_ven_codec_testcase_media_setVolume(s32 mediaHandle, u8 volume, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_getVolume(s32 mediaHandle, u8* pVolume, ven_req_data_t reqData);
ven_codec_ret_t ms_ven_codec_testcase_media_playVideo(s32 mediaHandle, u16* pURL, u16 urlLen, ven_req_data_t reqData);



void ms_ven_codec_image_test_sync(s32 nHandle);
void ms_ven_codec_image_test_async(s32 nHandle, AsyncCB pFnCB);
void ms_ven_codec_image_resize_sync(s32 nHandle, u32 panel_w, u32 panel_h);
void ms_ven_codec_image_resize_encode_to_mem(s32 nHandle, u32 panel_w, u32 panel_h, bool bSync);
void ms_ven_codec_image_resize_encode_to_file(s32 nHandle, u32 panel_w, u32 panel_h,bool bSync);
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif // __VEN__TEST_CODEC_DEFINE_H__
