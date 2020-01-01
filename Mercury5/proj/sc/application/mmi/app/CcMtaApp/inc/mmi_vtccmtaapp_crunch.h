/**
* @file    mmi_vtccmtaapp_crunch.h
* @brief   xxxx
* @version $Id: mmi_vtccmta_crunch.h
*/
#ifndef __MMI_VTCCMTAAPP_CRUNCH_H__
#define __MMI_VTCCMTAAPP_CRUNCH_H__

#include "mmi_vtccmtaapp_priv.h"

#ifdef __APP_VIDEO_TELEPHONY__
#define VTCCMTA_VIBRATE_TIMER 2500
#define VTCCMTA_WAITINGCALLTONE_TIMER 3000
#define VTCCMTA_WAITINGCALL_DODO_TIMER 100
#define VTCCMTA_MIN_MEM_FOR_VT_CALL (2650*1024) // 2650KB

void VtCcMtaWaitingCallDoDoTimerCB(void *pData);

void VtCcMtaIncomingCallView(MMI_CCMTA* pThis, u8 IncomingCallID);
void VtCcMtaIncomingCallViewExit(MMI_CCMTA* pThis);

void VtCcMtaCreateOptionMenu(MMI_CCMTA* pThis);
void VtCcMtaExitOptionMenu(MMI_CCMTA* pThis);

void VtCcMtaCreateIncomingcallOptionMenu(MMI_CCMTA* pThis);
void VtCcMtaExitIncomingcallOptionMenu(MMI_CCMTA* pThis);

void VtCcMtaSaveCallAsReceivedCallbyStatus(MMI_CCMTA* pThis, MMI_VTCCSRV_Status_e status);

#define VtCcMtaSaveRejctIncomingCallAsReceivedCall(pThis) \
			VtCcMtaSaveCallAsReceivedCallbyStatus(pThis, MMI_CALL_INCOMING)

#define VtCcMtaSaveRejctWaitingCallAsReceivedCall(pThis) \
			VtCcMtaSaveCallAsReceivedCallbyStatus(pThis, MMI_CALL_WAITING)

void VtCcMtaDrawInCallNotificationView(MMI_CCMTA* pThis, u32 ServiceCode,u32 index/*,u32 nTonNpi,u8 *CalledNb*/);

void VtCcMtaInsertPublicMMIString(MMI_CCMTA* pThis , u32 keycode);

void VtCcMtaShortStringHandleforPublicMMI( MMI_CCMTA* pThis, u8* pStr );

void VtCcMtaDrawInComingPicture(MMI_CCMTA * pThis,u32 nImageID);
void VtCcMtaPlayIncomingRingtone(MMI_CCMTA * pThis,u32 nPhbRingID);

void VtCcMtaVibrateTimerCB(void *pData);
void VtCcMtaWaitingCallDoDo_TimerCB(void *pData);
void VtCcMtaWaitingCallTonePlayTimerCB(void *pData);
void VtCcMtaBtHandleforAtchld( MMI_CCMTA* pThis, u32 param );

void VtCcMtaFlushMissCall( MMI_CCMTA* pThis );

void VtCcMtaCloseVtCcMta( MMI_CCMTA* pThis );

void VtCcMtaStopAudio( MMI_CCMTA* pThis );
void VtCcMtaAcceptCall(MMI_CCMTA *pThis);

void VtCcMtaHangupCalltoIdle(MMI_CCMTA* pThis);
#endif
#endif /* __MMI_CCMTAAPP_CRUNCH_H__ */
