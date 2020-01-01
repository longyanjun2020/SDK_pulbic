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
* @file    mmi_srv_tv.h
* @brief
*
*/

#ifndef __MMI_SRV_TV_H__
#define __MMI_SRV_TV_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_tvsrv.h"
#include "ABL_Tv.h"
//#include "mmi_srv_client.h"

/**
 SrvTvOpenSession
@brief  The interface is use to open tv session
 */
MAE_Ret SrvTvOpenSession(void);

/**
 SrvTvCloseSession
@brief  The interface is use to close tv session
 */
MAE_Ret SrvTvCloseSession(void);

/**
 SrvTvOpen
@brief  The interface is use to open tv

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the Open request
 */
MAE_Ret SrvTvOpen(TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSetSetCaptureNotifyCb
@brief          Register the tv callback function to listen the event such as caputing tv.
@brief          deregister the tv callback function by pass NULL callback function

@param[out]    pfnTvSrvCb        TvSrvCaptureNotifyCb call back function point to handle these event
 */
MAE_Ret SrvTvSetSetCaptureNotifyCbEx(TvSrvCaptureNotifyCbEx pfnTvSrvCb);

/**
 SrvTvSetSetInterruptCb
@brief          Register the TV callback function to listen the event such as suspend or resume.
@brief          deregister the TV callback function by pass NULL callback function

@param[out]    pfnTvSrvCb        TvSrvNotifyCb call back function point to handle these event
 */
MAE_Ret SrvTvSetSetInterruptCb(TvSrvNotifyCb pfnTvSrvCb);

/**
 SrvTvCmmbWatch
@brief          The interface is use to start watch CMMB TV
@param[in]       pTvStartPreview
@param[out]    pfnTvSrvCb        TvSrvCommonCb call back function point to handle these event
 */
MAE_Ret SrvTvCmmbWatch(TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvCmmbStopWatch
@brief          The interface is use to stop watch CMMB TV
@param[in]      pTvStartPreview
@param[out]     pfnTvSrvCb        TvSrvCommonCb call back function point to handle these event
 */
MAE_Ret SrvTvCmmbStopWatch(TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvCmmbSyncStopWatch
@brief          The interface is use to stop watch CMMB TV
@param[in]      pTvStartPreview
@param[out]     pfnTvSrvCb        TvSrvCommonCb call back function point to handle these event
 */
MAE_Ret SrvTvCmmbSyncStopWatch(TvSrvStartPreview_t *pTvStartPreview, TvSrvCommonCb pfnTvSrvCb);
/**
 SrvTvWatch
@brief  The interface is use to start watch tv

@param[in]       pWatchConfig: watch window ratation and size
@param[in]       nCh: channel
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the watch request
 */
MAE_Ret SrvTvWatch(TvSrvWatchConfig_t *pWatchConfig, u32 nCh, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvStopWatch
@brief  The interface is use to stop watch tv

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the stop watch request
 */
MAE_Ret SrvTvStopWatch(TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSyncStopWatch
@brief  The interface is use to stop watch tv

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the stop watch request
 */
MAE_Ret SrvTvSyncStopWatch(TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSetDisplayParam
@brief  The interface is use to set display parameters

@param[in]       pWatchConfig: watch window ratation and size
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the setting request
 */
MAE_Ret SrvTvSetDisplayParam(TvSrvWatchConfig_t *pWatchConfig, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSetChannel
@brief  The interface is use to set CMMB channel

@param[in]      pTvSwitchingChannel
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the setting request
 */
MAE_Ret SrvTvCmmbSetChannel(TvSrvSwitchChannel_t *pTvSwitchingChannel, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSetChannel
@brief  The interface is use to set channel

@param[in]      nChannelIndex
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the setting request
 */
MAE_Ret SrvTvSetChannel(u32 nChannelIndex, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvCapturePictureEx
@brief  The interface is use to capture a tv image while watching Tv

@param[in]    tTvSetting       the confiure of capturation (resolution, quailty, shot mode)
@param[in]    pPath              the storage path of captured image
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the capturing request
 */
MAE_Ret SrvTvCapturePictureEx(TvSrvCaptureConfig_t *tTvSetting, const MAE_WChar *pPath, TvSrvShutterSoundSetting_t *pSoundSetting, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvClose
@brief  The interface is use to close tv

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the close request
 */
MAE_Ret SrvTvClose(TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvSetRegion
@brief  The interface is use to set tv nations' region

@param[in]       eTvType      Hybrid TV type
@param[in]       eArea        TV nations' region.
@param[out]      pfnTvSrvCb   TvSrvCommonCb call back function point to response the close request
 */
MAE_Ret SrvTvSetRegion(TvSrvHybridType_e eTvType, TvSrvRegion_e eArea, const MAE_WChar *pPath, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvCmmbGetSignalLevel
@brief  The interface is use to get total capacity of channels and signal level
@param[in]       pTvInfo
@param[out]      pfnTvSrvCb  TvSrvCmmbSignalLevelCb call back function point to response the getting signal level request
 */
MAE_Ret SrvTvCmmbGetSignalLevel(TvSrvGetTvInfo_t *pTvInfo, TvSrvCmmbSignalLevelCb pfnTvSrvCb);

/**
 SrvTvGetSignalLevel
@brief  The interface is use to get total capacity of channels and signal level

@param[out]      pfnTvSrvCb   TvSrvCommonCb call back function point to response the getting signal level request
 */
MAE_Ret SrvTvGetSignalLevel(TvSrvSignalLevelCb pfnTvSrvCb);

/**
 SrvTvSearchChannel
@brief  The interface is use to searching channel

@param[in]         nChannelIndex
@param[out]      pfnTvSrvCb   TvSrvCommonCb call back function point to response the searching request
 */
MAE_Ret SrvTvSearchChannel(u32 nChannelIndex, TvSrvChannelInfoCb pfnTvSrvCb);

/*The following APIs are v2.01 only*/
/**
 SrvTvTurnOnShutterSound
@brief  The interface is use to turn on shutter sound while caturing a tv picture

@param[in]    eSoundPath    the path of sound data source (default, download, card)
@param[in]    pData              the sound's raw data address
@param[in]    nLen                the length of raw data
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the turn on shutter sound request
 */
MAE_Ret SrvTvTurnOnShutterSound(TvSrvSoundPath_e eSoundPath, u8 *pData, u32 nLen, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvTurnOffShutterSound
@brief  The interface is use to turn off shutter sound while caturing a tv image

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the turn off shutter sound request
 */
MAE_Ret SrvTvTurnOffShutterSound(TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvCapturePicture
@brief  The interface is use to capture a tv image while watching Tv

@param[in]    tTvSetting       the confiure of capturation (resolution, quailty, shot mode)
@param[in]    pPath              the storage path of captured image
@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the capturing request
 */
MAE_Ret SrvTvCapturePicture(TvSrvCaptureConfig_t *tTvSetting, const MAE_WChar *pPath, TvSrvCommonCb pfnTvSrvCb);

/**
 SrvTvGetCapturedFileName
@brief  The interface is use to get the file names of captured images

@param[out]    pfnTvSrvCb   TvSrvCommonCb call back function point to response the request
 */
MAE_Ret SrvTvGetCapturedFileName(TvSrvCapturedFileNameCb pfnTvSrvCb);

/**
 SrvTvSetSetCaptureNotifyCb
@brief          Register the tv callback function to listen the event such as caputing tv.
@brief          deregister the tv callback function by pass NULL callback function

@param[out]    pfnTvSrvCb        TvSrvCaptureNotifyCb call back function point to handle these event
 */
MAE_Ret SrvTvSetSetCaptureNotifyCb(TvSrvCaptureNotifyCb pfnTvSrvCb);

/**
 SrvTvGetEmInfo
@brief  The interface is use to get engineer mode information.

@param[out]      pfnTvSrvCb   TvSrvEmInfoCb call back function point to response the getting engineer mode infomation request
 */
MAE_Ret SrvTvGetEmInfo(TvSrvEmInfoCb pfnTvSrvCb);

#endif //__MMI_SRV_TV_H__

