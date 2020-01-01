/**
* @file    mmi_ccmtaapp_crunch.h
* @brief   xxxx
* @version $Id: mmi_ccmta_crunch.h 1733 2007-09-05 09:27:04Z collin.chiang $
*/
#ifndef __MMI_CCMTAAPP_CRUNCH_H__
#define __MMI_CCMTAAPP_CRUNCH_H__

#include "mmi_ccmtaapp_priv.h"
#define CCMAT_VIBRATE_TIMER 2500
#define CCMAT_WAITINGCALLTONE_TIMER 3000
#define CCMAT_WAITINGCALL_DODO_TIMER 100
#define CCMAT_DELAY_RINGTONE_TIMER 1
#define CCMAT_DELAY_WAITINGCALL_TIMER 500

#if defined(__MMI_PHB_VIDEOTONE_SUPPORT__) && defined(__CCMTAAPP_SMALLROM__)
#define CCMAT_MIN_VIDEOTONE_FREE_HEAP (1300*1024) // 1300KB
#endif

void CcMtaDelayRingtoneTimerCB(void *pData, void *pUserData);
void CcMtaDelayWaitingCallTimerCB(void *pData);
void CcMtaWaitingCallDoDoTimerCB(void *pData);

void CcMtaIncomingCallView(MMI_CCMTA* pThis, u8 IncomingCallID);
void CcMtaIncomingCallViewExit(MMI_CCMTA* pThis);

void CcMtaCreateOptionMenu(MMI_CCMTA* pThis);
void CcMtaExitOptionMenu(MMI_CCMTA* pThis);

void CcMtaSaveCallAsReceivedCallbyStatus(MMI_CCMTA* pThis, MMI_CCSRV_Status_e status);

#define CcMtaSaveRejctIncomingCallAsReceivedCall(pThis) \
			CcMtaSaveCallAsReceivedCallbyStatus(pThis, MMI_CALL_INCOMING)

#define CcMtaSaveRejctWaitingCallAsReceivedCall(pThis) \
			CcMtaSaveCallAsReceivedCallbyStatus(pThis, MMI_CALL_WAITING)

void CcMtaDrawInCallNotificationView(MMI_CCMTA* pThis, u32 ServiceCode,u32 index/*,u32 nTonNpi,u8 *CalledNb*/);

void CcMtaInsertPublicMMIString(MMI_CCMTA* pThis , u32 keycode);

void CcMtaShortStringHandleforPublicMMI( MMI_CCMTA* pThis, u8* pStr );

void CcMtaDrawInComingPicture(MMI_CCMTA * pThis,u32 nImageID);
void CcMtaPlayIncomingRingtone(MMI_CCMTA * pThis,u32 nPhbRingID);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
void CcMtaVideoPlayProgressCb(void *pApplet, u32 nCusData, VideoPlayerSrvProgressInfo_t *pRspInfo);
void CcMtaVideoPlayStatusCb(void *pApplet, u32 nCusData, VideoPlayerSrvPlayStatusInfo_t *pRspInfo);
void CcMtaVideoPlayerErrorCb(void *pApplet, u32 nCusData, VideoPlayerSrvErrorInfo_t *pRspInfo);
void CcMtaPlayIncomingCallVideo(MMI_CCMTA * pThis, MAE_WChar *pURL);
void CcMtaStopIncomingCallVideo(MMI_CCMTA * pThis);
void CcMtaVibrateThenPlayVideoTimerCB(void *pData);
void CcMtaVideoGetFirstFrameCb(void *pApplet, u32 nCusData, VideoPlayerSrvFirstFrameInfo_t *pRspInfo);
void CcMtaSetVideoWindow(void);
void CcMtaVideoPlayerSetWindowCb(void *pApplet, u32 nCusData, VideoPlayerSrvWindSizeInfo_t *pRspInfo);
void CcMtaVideoPlayerCloseSession(MMI_CCMTA *pThis);
#endif

void CcMtaVibrateTimerCB(void *pData);
void CcMtaWaitingCallDoDo_TimerCB(void *pData);
void CcMtaWaitingCallTonePlayTimerCB(void *pData);
void CcMtaBtHandleforAtchld( MMI_CCMTA* pThis, u32 param );

void CcMtaFlushMissCall( MMI_CCMTA* pThis );

void CcMtaCloseCcMta( MMI_CCMTA* pThis );

void CcMtaStopWaitingTone(MMI_CCMTA* pThis);
void CcMtaStopAudio( MMI_CCMTA* pThis );
void CcMtaAcceptCall(MMI_CCMTA *pThis);
void CcMtaSrvCcAcceptCall(MMI_CCMTA* pThis);

void CcMtaHangupCalltoIdle(MMI_CCMTA* pThis);
MAE_Ret CcMtaPlayRingtone(MMI_CCMTA * pThis, SetRingToneVolume_e eRingVolume, SetRingToneRingType_e eRingType,u32 nPhbRingID);
MAE_Ret CcMtaPlayDefaultRingtone(MMI_CCMTA * pThis, SetRingToneRingType_e eRingType);

#ifdef __APP_MMI_ANSWERING_MACHINE__
MAE_Ret CcMtaCheckAMPrecondition(MMI_CCMTA* pThis);
#endif

#ifdef __APP_VIDEO_TELEPHONY__
boolean CcMtaAppIsFallbackSameCaller(MMI_CCMTA* pThis);
#endif

#ifdef __DUAL_LCD__
void CcMtaSubIncomingCallView(MMI_CCMTA* pThis, u8 IncomingCallID);
void CcMtaDrawSubInComingPicture(MMI_CCMTA *pThis);
#endif // __DUAL_LCD__

void CcMtaAppReReadProfileAndPlayRingtone(MMI_CCMTA* pThis);
#endif /* __MMI_CCMTAAPP_CRUNCH_H__ */
