#ifdef __TTS__
#ifndef __MMI_TTSSRV_DBL_H__
#define __MMI_TTSSRV_DBL_H__

#include "mmi_mae_common_def.h"
#include "tts_itf.h"

/// emit request api
void TtsSrv_EmitInitTts(void *pvCmd);
void TtsSrv_EmitUninitTts(void *pvCmd);
void TtsSrv_EmitPlay(void *pvCmd);
void TtsSrv_EmitStop(void *pvCmd);
void TtsSrv_EmitAdjustVolume(void *pvCmd);


/// emit response api
void TtsSrv_RspInitTts(TTSErrorCode eErrCode, void *pvUserData, u32 uVenHdl);
void TtsSrv_RspUninitTts(TTSErrorCode eErrCode, void *pvUserData, u32 uVenHdl);
void TtsSrv_RspPlay(TTSErrorCode eErrCode, void *pvUserData, u32 uVenHdl);
void TtsSrv_RspStop(TTSErrorCode eErrCode, void *pvUserData, u32 uVenHdl);
void TtsSrv_IndPlayEnd(TTSStatus_e eStatus, void *pvUserData, u32 uVenHdl);
void TtsSrv_IndPlayErr(TTSStatus_e eStatus, void *pvUserData, u32 uVenHdl);
#endif/* __MMI_TTSSRV_DBL_H__ */
#endif/* __TTS__ */
