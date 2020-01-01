/**
 * @file    mmi_req_tts.h
 * @brief   This file defines the interface to send tts request.
 * @author  mstarsemi.com
 *
 * 
 */
#ifndef __MMI_REQ_TTS_H__
#define __MMI_REQ_TTS_H__

#ifdef __TTS__

#include "tts_itf.h"
#include "mmi_mae_common_def.h"

    
void mmi_tts_init_req(void *pvUserData, TtsRspCB pfnRspCb);
void mmi_tts_release_req(void *pvUserData, TtsRspCB pfnRspCb);
void mmi_tts_playText_req(TTSParam_t *psParam, u16 *pText, u16 nLen, void *pvUserData, u32 uPlayTi, TTSPlayVolumn_e ePlayVolume,TtsRspCB pfnRspCb);
void mmi_tts_stopPlay_req(void *pvUserData, u32 uStopTi, TtsRspCB pfnRspCb);
void mmi_tts_adjustVolume_req(u32 uPlayTi, TTSPlayVolumn_e eVolume);

#endif /* __TTS__ */

#endif /* __MMI_REQ_TTS_H__ */
