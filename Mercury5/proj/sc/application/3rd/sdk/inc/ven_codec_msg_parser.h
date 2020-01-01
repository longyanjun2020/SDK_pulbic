/**
 *
 * @file    ven_codec_msg_parser.h.
 * @brief   This file implement the message parser for codec related msg
 * @author  Code Lin
 * @version $Id: ven_codec_msg_parser.h 38996 2009-09-01 02:03:20Z code.lin $
 *
 */

#ifndef __VEN_CODEC_MSG_PARSER_H__
#define __VEN_CODEC_MSG_PARSER_H__

#include "ven_common_def.h"

void ven_codec_openMedia_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_closeMedia_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getFileInfo_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getVdoExtInfo_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getPlayingTime_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playAudio_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_Resource_State_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playAudioRaw_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playMidi_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_pauseAudio_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_resumeAudio_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_stopAudio_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_setAudioPos_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_setAudioVolume_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getAudioVolume_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_startAudioRecord_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_stopAudioRecord_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_startAudioStreamRecord_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_stopAudioStreamRecord_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playAudioStreaming_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getAvaiAudioStreamBufSize_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getAudioStreamBufSize_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_isAudioStreaming_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playVideo_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_playVideo_ind(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_openImageCodec_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_closeImageCodec_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_decodeImage_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_encodeImage_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getNextImageFrame_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_VideoStream_FileChange_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_VideoStream_DLItf_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
void ven_codec_getVideoStreamInfo_rsp(ven_msg_t MsgID, vm_msg_t *pMessage);
#endif //__VEN_CODEC_MSG_PARSER_H__
