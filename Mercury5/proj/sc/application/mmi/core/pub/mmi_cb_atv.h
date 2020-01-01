/**
* @file mmi_cb_atv.h
*
*
* @version $Id: mmi_cb_atv.h 36778 2009-07-29 10:50:17Z stone.shih $
*/
#ifndef __MMI_CB_ATV_H__
#define __MMI_CB_ATV_H__

#include "ABL_TV.h"
#include "mmi_log.h"

// Callback functions called by Media task
MAERet_t convertESLTVErrCodeToMAERet(ABL_TvErrCode_e errCode);
MAERet_t convertABLTVErrCodeToMAERet(ABL_TvErrCode_e errCode);

void ATV_OpenATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_CloseATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_WatchATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_StopWatchATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_ResetWindow_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_SwitchChannelATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_SetConfigeATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_GetATVInfo_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_GetEmInfo_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_ScanChannel_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_CaptureATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_RegNotifyATV_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_SetShutterSound_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_GetFilename_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_Capture_NotifyTv_Cb(u16 senderID, u32 userValue, ABL_TvNotifyInfo_t *pTvGetInfo);
void ATV_ResMgr_NotifyTv_Cb(u32 uCusData, void *pEvtInfo);
void ATV_OpenATVSession_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);
void ATV_CloseATVSession_Cb(u16 senderID, u32 userValue, ABL_TvErrCode_e errCode, ABL_TvInfo_t *pTvGetInfo);

#endif
