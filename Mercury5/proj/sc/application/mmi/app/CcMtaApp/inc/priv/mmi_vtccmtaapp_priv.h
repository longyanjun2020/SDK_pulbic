/**
* @file mmi_vtccmtaapp_priv.h
*
* Class Id: CLSID_CCMTA
*
*/
#ifndef __MMI_VTCCMTAAPP_PRIV_H__
#define __MMI_VTCCMTAAPP_PRIV_H__

#include "mmi_common_dialog.h"
#include "mmi_mae_common_def.h"
#include "mmi_vtccmtaapp.h"

#include "mmi_phbapp.h"
#include "mmi_common_cfg.h"
#include "mmi_baseapplet.h"

#include "mmi_common_vtm.h"
#include "mmi_common_wdgvar.h"

#include "mmi_ccmtaapp_id.h"
#include "mmi_ccmtaapp_priv.h"
#include "ccmtaapp_resource.h"

#ifdef __APP_VIDEO_TELEPHONY__

#define VTCCAPP_NOTIFICATION_TIMER	2500
#define VTCCAPP_STOP_MEDIA_AGAIN_TIMER	200
#define VTCCMTA_AUTO_ANSWER_TIMER 2000
#define VTCCMTA_FALLBACK_WAITING_TIME 15000

/*
enum
{
	PickCall_None =0,
	PickCall_InComing,
	PickCall_Waiting,
};
typedef u8 PickCallType_e;
*/

enum
{
	VTCCMTA_STATUS_NONE = 0,
	VTCCMTA_STATUS_REQ,
	VTCCMTA_STATUS_CNF,
	VTCCMTA_STATUS_RET_ERROR
};
typedef u8 VTCCMTA_STOP_AUDIO_STATUS_e;



MAE_Ret VtCcMtaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret VtCcMtaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);

boolean VtCcMtaAppStartCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaKeyPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaKeyLongPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaKeyReleaseCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaAppResumeCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaAppSuspendCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean VtCcMtaAppStopCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);

void VtCcMtaSrvVtCcReleaseSpecificCallCB( void *pThis, boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcReleaseActiveCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcReleaseHoldCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcRejectWaitingCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcAcceptCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcReplaceActiveInWaitingCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcReplaceHoldInWaitingCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcTransferCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcHangUpCallCB( void *pThis,boolean bResult,u32 nCause );
void VtCcMtaSrvVtCcAllCallReleasedCB( void *pThis );
void VtCcMtaSrvVtCcInCallNotifyCB( void *pThis, u32 ServiceCode,u32 index,u32 nTonNpi,u8 *CalledNb );
void VtCcMtaSrvVtCcWaitingToIncomingCall( void *pThis );
void VtCcMtaSrvVtCcReleaseIncomingCallCB( void *pThis, u32 nCause );
void VtCcMtaSrvVtCcReleaseWaitingCallCB( void *pThis, u32 nCause );
void VtCcMtaSrvVtCcReleaseCB( void *pThis, u32 nCause );

MAE_Ret VtCcMtaWndCreateIncomingcall(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VtCcMtaWndDestroyIncomingcall(void* pWndHandle, void* pWndData);
MAE_Ret VtCcMtaWndShowIncomingcall(void* pWndHandle, void* pWndData);
MAE_Ret VtCcMtaWndHideIncomingcall(void* pWndHandle, void* pWndData);

MAE_Ret VtCcMtaWndCreateIncomingcallOptionmenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VtCcMtaWndDestroyIncomingcallOptionmenu(void* pCusHandle,void* pWndData);

MAE_Ret VtCcMtaWndCreateWaitingcall(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VtCcMtaWndDestroyWaitingcall(void* pCusHandle,void* pWndData);
MAE_Ret VtCcMtaWndShowWaitingcall(void* pCusHandle,void* pWndData);
MAE_Ret VtCcMtaWndHideWaitingcall(void* pCusHandle,void* pWndData);

MAE_Ret VtCcMtaWndCreateWaitingcallOptionmenu(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret VtCcMtaWndDestroyWaitingcallOptionmenu(void* pCusHandle,void* pWndData);
MAE_Ret VtCcMtaWndShowWaitingcallOptionmenu(void* pCusHandle,void* pWndData);
MAE_Ret VtCcMtaWndHideWaitingcallOptionmenu(void* pCusHandle,void* pWndData);

void VtCcMtaReplaceOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void VtCcMtaIncomingcallOptionMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifdef __BLUETOOTH_MMI__
void VtCcMtaSrvBtAudioLinkIndCB(void *pThis, u8 nItem, BTSRV_Link_Status_e eLinkStatus); //BTSRV_EVT_AudioCallInd
void VtCcMtaSrvBtAudioCallIndCB( void *pThis, BTSRV_StatusCode_e eResult, BTSRV_AudioCallType_e eType ); //BTSRV_EVT_AudioCallInd
void VtCcMtaSrvBtAtaCB( void *pThis ); //BTSRV_EVT_ATA
void VtCcMtaSrvBtAtchldCB( void *pThis, u32 value ); //BTSRV_EVT_ATCHLD
void VtCcMtaSrvBtAtchupCB( void *pThis ); //BTSRV_EVT_ATCHUP
#endif

MAE_Ret _VtCcMtaCreateIncomingCallView(HWIN hWin, CcMtaIncomingCallViewWdgList_t *pWdgList);
MAE_Ret _VtCcMtaCreatePetIncomingCallView(HWIN hWin, CcMtaPetIncomingCallViewWdgList_t *pWdgList);

void  VtCcMtaSrvVtCcFallbackRequestCB(void *pThis, boolean bResult);
void VtCcMtaFallbackTimerCB(void* data);

#endif
#endif /* __MMI_VTCCMTAAPP_PRIV_H__ */
