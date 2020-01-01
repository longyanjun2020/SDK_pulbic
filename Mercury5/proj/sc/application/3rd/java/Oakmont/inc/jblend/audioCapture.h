/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file audioControl.h
 * Audio Capture Sample Implementation for Windows
 */

#ifndef __AUDIO_CAPTURE_H
#define __AUDIO_CAPTURE_H

#include "JkMediaControl.h"
#include "JkMediaCapture.h"

#define JKMEDIA_TYPE_AUDIO_CAPTURE  ( JKMEDIA_TYPE_DEVICE_BASE )

/* Mstar header - begin */

#include "jap_media.h"
#include "jap_head.h"

/* Mstar header - end */


extern u32 g_hSdk;

enum
{
	CODEC_OPEN_MEDIA,
	CODEC_CLOSE_MEDIA,
	CODEC_GET_FILE_INFO,
	CODEC_GET_RAW_INFO,
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

/**
 * Structure for Audio capturing control functions.
 */
extern const JKT_MediaControl audioCapture;

#endif /* !__AUDIO_CAPTURE_H */
