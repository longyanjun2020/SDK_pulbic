/**
* @file    mmi_ccapp_crunch.h
* @brief   xxxx
* @version $Id: mmi_ccapp_crunch.h 1733 2007-09-05 09:27:04Z collin.chiang $
*/
#ifndef __MMI_CCAPP_CRUNCH_H__
#define __MMI_CCAPP_CRUNCH_H__

#include "mmi_ccapp_priv.h"

void CcAppMultipartyItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void CcAppMultipartyItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

boolean CcAppCrunchDrawOutgoingCallScreenImageArea(MMI_CCAPP* pThis, u8 u8OutgoingCallIdx);

void CcAppCrunchDrawOutgoingCallSoftkeyArea(MMI_CCAPP *pThis);
void CcAppCrunchOutgoingCallAudioPath(MMI_CCAPP *pThis, u32 nAudioPath);

#ifdef __IP_CALL_MMI__
void CcAppCrunchUpdateIPNumberEditorSK(IBase *pObj, boolean bEnable);
MAE_Ret CcAppCrunchHandleKeyPressforIPNumberEditor(MMI_CCAPP* pThis , u32 nKeyCode);
MAE_Ret CcAppCrunchGetCurrentIPNumberFromEditor(MMI_CCAPP *pThis, TextInfo *pTextInfo);
#endif

void CcAppCrunchDrawInCallScreenTextArea(MMI_CCAPP* pThis);
boolean CcAppCrunchDrawInCallScreenImageArea(MMI_CCAPP* pThis);
void CcAppCrunchDrawInCallSoftkeyArea(MMI_CCAPP *pThis, boolean bRecording);
void CcAppCrunchDrawSoftkeyArea(MMI_CCAPP *pThis, SoftkeyID_e ePreSoftkeyID);

void CcAppCrunchExitOptionMenu(MMI_CCAPP* pThis);


void CcAppCrunchDrawCallSetupNotificationView(MMI_CCAPP* pThis,u32 nServiceCode,u32 nIndex);
void CcAppCrunchDrawInCallNotificationDialog(MMI_CCAPP* pThis, u32 ServiceCode, u32 index);


void CcAppCrunchCallFailedDialog(MMI_CCAPP* pThis , u32 u32Cause, PFN_DlgHandler pfnDialogHdl);

void CcAppCrunchDrawDialogView(MMI_CCAPP* pThis,  u32 DialogType , u32 TextId );
void CcAppCrunchDrawNotificationView(MMI_CCAPP* pThis,  u32 DialogType , MAE_WChar* wStr );

void CcAppCrunchSetTimer(IWidget *pWDGTimerFormat , u32 timeTick);


void CcAppCrunchMakeCallFromEmbeddAPP(MMI_CCAPP* pThis,  u32 Pamra);

void CcAppCrunchInsertPublicMMIString(MMI_CCAPP* pThis , u32 keycode);


void CcAppCrunchSendKey(MMI_CCAPP* pThis, MAE_WChar* pWStr, u32 TextLen, boolean bIPCall);

void CcAppCrunchMake2ndCall(MMI_CCAPP* pThis, MAE_WChar* pWStr, MAE_WChar* pWIPStr);

boolean CcAppCrunchCheckDuo2ndCall(MMI_CCAPP* pThis , u8 CheckSessionID );

void CcAppCrunchSysSetPreferAudioPath(MMI_CCAPP* pThis);
boolean CcAppCrunchSysSetBTHeadsetAudioPath(MMI_CCAPP* pThis, boolean bShowDialog);
void CcAppCrunchSysSetHandsetAudioPath(MMI_CCAPP* pThis);


void CcAppCrunchSaveContact(MMI_CCAPP* pThis);

void CcAppCrunchSetVoiceChannel(MMI_CCAPP* pThis, AudioEnvSrvPrefAudPath_e Path);


void CcAppCrunchSetDefaultVolume(MMI_CCAPP* pThis);

void CcAppCrunchDrawVolumeDialog(MMI_CCAPP* pThis);

#ifdef __ANSWER_INDICATOR_MMI__
void CcAppCrunchStopAnswerReminder(MMI_CCAPP* pThis);
#endif

void CcAppCrunchSetSpeakerAudioPath(MMI_CCAPP* pThis);
void CcAppCrunchSetHandsetAudioPath(MMI_CCAPP* pThis);

void CcAppCrunchHangupCalltoIdle(MMI_CCAPP* pThis);
void CcAppCrunchHangupCalltoCallEndScreen(MMI_CCAPP* pThis);
void CcAppCrunchInCallSessionEndCall( MMI_CCAPP* pThis );

void CcAppCrunchGotoInCallScreenCB(void* data);
MAE_Ret CcAppGotoInCallScreenDialogCb(void *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);

void CcAppCrunchGotoOutgoingCallScreenCb(void *data);
void CcAppButtonDataFree(void *pData, IBase *pOwner);

void CcAppCrunchAcceptMTCall( MMI_CCAPP* pThis , MmiCCAPPIncomingCallInd_t* pMTCallInd );
void CcAppCrunchProgressInd( MMI_CCAPP* pThis, u32 nProgID);
void CcAppOutgoingToneTimerCb(void* data);
void CcAppCrunchCallEndScreen( MMI_CCAPP* pThis);
void CcAppCallEndTimerCB(void* data);
void CcAppCallEndToneTimerCB(void* data);	// Call end tone: work-around solution
void CcAppResumePlayCallEndTone(IBase* pUser, u32 Param);		// Call end tone: work-around solution

#ifdef __APP_MMI_ANSWERING_MACHINE__
#define ANSWERING_MACHINE_FILE_PREFIX L"AM_"
#define ANSWERING_MACHINE_FILE_AMR_POSTFIX L".AMR"
#define ANSWERING_MACHINE_FILE_MP3_POSTFIX L".MP3"
static void CcAppPlayGreetingSound(void* pData, boolean bPlayDefaultGreeting);
void CcAppAudioSrvStopCb(void *pData, MediaSrvErrCode_e eErrorCode);
void CcAppStopGreetingSound(void* pData);
void CcAppStartAnsweringMachine(void *pCusHandle);
static void CcAppAMAudioSrvCb(void *pData, MediaSrvErrCode_e eErrorCode);
static void CcAppAMAudioSrvPlayStatusCb(void *pData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
void CcAppAMRenameRecordedFile(MMI_CCAPP *pThis, AudioRecSrvFileInfo_t *pFileInfo);
#endif

#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
void CcAppCBSPlay(MMI_CCAPP *pThis);
void CcAppCBSStop(MMI_CCAPP *pThis);
static void CcAppCBSAudioSrvCb(void *pData, MediaSrvErrCode_e eErrorCode);
static void CcAppCBSAudioSrvPlayStatusCb(void *pData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
static void CcAppCBSAudioInterruptNotifyCb(void *pThis, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
static void CcAppCBSPlayIntervalTimerCB(void* data);
static void CcAppCBSStopAudioSrvCb(void *pData, MediaSrvErrCode_e eErrorCode);
#endif
#endif /* __MMI_CCAPP_CRUNCH_H__ */
