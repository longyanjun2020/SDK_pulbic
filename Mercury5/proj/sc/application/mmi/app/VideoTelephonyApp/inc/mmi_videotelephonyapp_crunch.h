/**
* @file    mmi_videotelephonyapp_crunch.h
* @brief   xxxx
* @version $Id: mmi_videotelephonyapp_crunch.h$
*/
#ifndef __MMI_VIDEOTELEPHONYAPP_CRUNCH_H__
#define __MMI_VIDEOTELEPHONYAPP_CRUNCH_H__

#include "mmi_videotelephonyapp_priv.h"

void VideoTelephonyAppMultipartyItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void VideoTelephonyAppMultipartyItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

boolean VideoTelephonyAppCrunchDrawOutgoingCallScreenImageArea(MMI_VIDEOTELEPHONYAPP* pThis, u8 u8OutgoingCallIdx);

void VideoTelephonyAppCrunchDrawOutgoingCallSoftkeyArea(MMI_VIDEOTELEPHONYAPP *pThis);
void VideoTelephonyAppCrunchOutgoingCallAudioPath(MMI_VIDEOTELEPHONYAPP *pThis, u32 nAudioPath);

#ifdef __IP_CALL_MMI__
void VideoTelephonyAppCrunchUpdateIPNumberEditorSK(IBase *pObj, boolean bEnable);
MAE_Ret VideoTelephonyAppCrunchHandleKeyPressforIPNumberEditor(MMI_VIDEOTELEPHONYAPP* pThis , u32 nKeyCode);
MAE_Ret VideoTelephonyAppCrunchGetCurrentIPNumberFromEditor(MMI_VIDEOTELEPHONYAPP *pThis, TextInfo *pTextInfo);
#endif

void VideoTelephonyAppCrunchDrawInCallScreenTextArea(MMI_VIDEOTELEPHONYAPP* pThis);
boolean VideoTelephonyAppCrunchDrawInCallScreenImageArea(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCrunchDrawInCallSoftkeyArea(MMI_VIDEOTELEPHONYAPP *pThis, boolean bRecording);


void VideoTelephonyAppCrunchExitOptionMenu(MMI_VIDEOTELEPHONYAPP* pThis);


void VideoTelephonyAppCrunchDrawCallSetupNotificationView(MMI_VIDEOTELEPHONYAPP* pThis,u32 nServiceCode,u32 nIndex);
void VideoTelephonyAppCrunchDrawInCallNotificationDialog(MMI_VIDEOTELEPHONYAPP* pThis, u32 ServiceCode, u32 index);


void VideoTelephonyAppCrunchCallFailedDialog(MMI_VIDEOTELEPHONYAPP* pThis , u32 u32Cause, PFN_DlgHandler pfnDialogHdl);

void VideoTelephonyAppCrunchDrawDialogView(MMI_VIDEOTELEPHONYAPP* pThis,  u32 DialogType , u32 TextId );
void VideoTelephonyAppCrunchDrawNotificationView(MMI_VIDEOTELEPHONYAPP* pThis,  u32 DialogType , MAE_WChar* wStr );

void VideoTelephonyAppCrunchSetTimer(IWidget *pWDGTimerFormat , u32 timeTick);


void VideoTelephonyAppCrunchMakeCallFromEmbeddAPP(MMI_VIDEOTELEPHONYAPP* pThis,  u32 Pamra);

void VideoTelephonyAppCrunchInsertPublicMMIString(MMI_VIDEOTELEPHONYAPP* pThis , u32 keycode);


void VideoTelephonyAppCrunchSendKey(MMI_VIDEOTELEPHONYAPP* pThis, MAE_WChar* pWStr, u32 TextLen, boolean bIPCall);

void VideoTelephonyAppCrunchMake2ndCall(MMI_VIDEOTELEPHONYAPP* pThis, MAE_WChar* pWStr, MAE_WChar* pWIPStr);

boolean VideoTelephonyAppCrunchCheckDuo2ndCall(MMI_VIDEOTELEPHONYAPP* pThis , u8 CheckSessionID );

void VideoTelephonyAppCrunchSysSetPreferAudioPath(MMI_VIDEOTELEPHONYAPP* pThis);
boolean VideoTelephonyAppCrunchSysSetBTHeadsetAudioPath(MMI_VIDEOTELEPHONYAPP* pThis, boolean bShowDialog);
void VideoTelephonyAppCrunchSysSetHandsetAudioPath(MMI_VIDEOTELEPHONYAPP* pThis);


void VideoTelephonyAppCrunchSaveContact(MMI_VIDEOTELEPHONYAPP* pThis);

void VideoTelephonyAppCrunchSetVoiceChannel(MMI_VIDEOTELEPHONYAPP* pThis, AudioEnvSrvPrefAudPath_e Path);


void VideoTelephonyAppCrunchSetDefaultVolume(MMI_VIDEOTELEPHONYAPP* pThis);

void VideoTelephonyAppCrunchDrawVolumeDialog(MMI_VIDEOTELEPHONYAPP* pThis);

#ifdef __ANSWER_INDICATOR_MMI__
void VideoTelephonyAppCrunchStopAnswerReminder(MMI_VIDEOTELEPHONYAPP* pThis);
#endif

void VideoTelephonyAppCrunchSetSpeakerAudioPath(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCrunchSetHandsetAudioPath(MMI_VIDEOTELEPHONYAPP* pThis);

void VideoTelephonyAppCrunchHangupCalltoIdle(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCrunchHangupCalltoCallEndScreen(MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCrunchInCallSessionEndCall( MMI_VIDEOTELEPHONYAPP* pThis );

void VideoTelephonyAppCrunchGotoInCallScreenCB(void* data);
MAE_Ret VideoTelephonyAppGotoInCallScreenDialogCb(void *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);

void VideoTelephonyAppCrunchGotoOutgoingCallScreenCb(void *data);
void VideoTelephonyAppButtonDataFree(void *pData, IBase *pOwner);

void VideoTelephonyAppCrunchAcceptMTCall( MMI_VIDEOTELEPHONYAPP* pThis , MmiVideoTelephonyAppIncomingCallInd_t* pMTCallInd );
void VideoTelephonyAppCrunchProgressInd( MMI_VIDEOTELEPHONYAPP* pThis, u32 nProgID);
void VideoTelephonyAppOutgoingToneTimerCb(void* data);
void VideoTelephonyAppCrunchCallEndScreen( MMI_VIDEOTELEPHONYAPP* pThis);
void VideoTelephonyAppCallEndTimerCB(void* data);
void VideoTelephonyAppCallEndToneTimerCB(void* data);	// Call end tone: work-around solution
void VideoTelephonyAppResumePlayCallEndTone(IBase* pUser, u32 Param);		// Call end tone: work-around solution

boolean VideoTelephonyAppIs3GNetworkAvailable(MMI_VIDEOTELEPHONYAPP* pThis); 
void VideoTelephonyAppMakeVoiceCall(MMI_VIDEOTELEPHONYAPP* pThis);

#endif /* __MMI_VIDEOTELEPHONYAPP_CRUNCH_H__ */
