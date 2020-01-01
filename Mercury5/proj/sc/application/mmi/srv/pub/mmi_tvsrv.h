////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
*
* @file    mmi_tvapp_itv.h
*
* @brief   This file defines the mmi to call ABL tv driver.
*
*/
#ifndef __MMI_TVSRV_H__
#define __MMI_TVSRV_H__

#include "mmi_tvsrv_def.h"
#include "mmi_mae_applet.h"


#define INHERIT_ITVSRV(IName) \
    INHERIT_IHandler(IName)


DEFINE_INTERFACE(ITVSRV);


typedef struct
{
    DECLARE_FUNCTBL(ITVSRV); // function table pointer
    u32 nRefCnt;     // reference count
    TvSrvCusInfo_t *pShutterSoundRsp;
    TvSrvCusInfo_t *pGetFileRsp;
    TvSrvCusInfo_t *pNotifyRes;
    TvSrvCusInfo_t *pNotifyCapture;
    TvSrvShutterSoundSetting_t *pShutterSound;
    TvSrvFileName_t *pFilename;
    boolean bIsTerminated;
    boolean bIsSessionOpen;
}TvSrv_t;

MAE_Ret TvSrvOpenSession(TvSrv_t *pITVSRV, u32 nSrvClient);
MAE_Ret TvSrvCloseSession(TvSrv_t *pITVSRV, u32 nSrvClient);
MAE_Ret TvSrvOpen(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCommonCb pCallback);
MAE_Ret TvSrvClose(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCommonCb pCallback);
MAE_Ret TvSrvWatch(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnCallBack);
MAE_Ret TvSrvStopWatch(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnCallBack);
MAE_Ret TvSrvSyncStopWatch(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnCallBack);
MAE_Ret TvSrvSetChannel(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvSwitchChannel_t *pTvSwitchingChannel, TvSrvCommonCb pfnCallBack);
MAE_Ret TvSrvSetDisplayParam(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvWatchConfig_t *pWatchConfig, TvSrvCommonCb pCallback);
MAE_Ret TvSrvSetShutterSound(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvShutterSound_e eShutterSound, TvSrvSoundPath_e eSoundPath, u8 *pData, u32 nLen, TvSrvCommonCb pCallback);
MAE_Ret TvSrvGetCapturedFileName(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCapturedFileNameCb pCallback);
MAE_Ret TvSrvCapturePicture(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCaptureConfig_t *pCaptureSetting, const MAE_WChar *pPath, TvSrvCommonCb pCallback);
MAE_Ret TvSrvCapturePictureEx(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCaptureConfig_t *pCaptureSetting, const MAE_WChar *pPath, TvSrvShutterSoundSetting_t *pSoundSetting, TvSrvCommonCb pCallback);
MAE_Ret TvSrvSetRegion(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvHybridType_e eTvType, TvSrvRegion_e eArea, const MAE_WChar *pPath, TvSrvCommonCb pCallback);
MAE_Ret TvSrvSearchChannel(TvSrv_t *pITVSRV, u32 nSrvClient, u32 nChannel, TvSrvChannelInfoCb pCallback);
MAE_Ret TvSrvSetSetCaptureNotifyCb(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCaptureNotifyCb pfnCallBack);
MAE_Ret TvSrvSetSetCaptureNotifyCbEx(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvCaptureNotifyCbEx pCallback);
MAE_Ret TvSrvGetSignalLevel(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvGetTvInfo_t *pTvInfo, void* pfnCallBack);
MAE_Ret TvSrvGetEmInfo(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvEmInfoCb pCallback);
MAE_Ret TvSrvSetSetInterruptCb(TvSrv_t *pITVSRV, u32 nSrvClient, TvSrvNotifyCb pCallback);
void TvSrvInit(void);
MAE_Ret TvSrvNew(MAE_ClsId nId, void **ppObj);

#endif  /*__MMI_TVSRV_H_*/
