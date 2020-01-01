#ifndef __MMI_EVTCENTERSRV_MICS_H__
#define __MMI_EVTCENTERSRV_MICS_H__

#include "mmi_evtcentersrv_priv.h"
#include "mmi_launcher_mca.h"

#define MMI_MMS_DIALOG_MAX__LEN 200
#define MMI_MMS_DIALOG_MAX_NAME__LEN 50
#define MMI_MMS_DIALOG_MAX_NUMBER_LEN 30

#define EVTCENTERSRVSWITCH_SIM_DIALOG_TIMER 5000 // __MMI_SWITCH_MODE_WHEN_NO_NETWORK__

void _EVTCENTERSRV_Dstor(MMI_EVTCENTERSRV *pThis);

boolean _EVTCENTERSRV_HandleMOI(MMI_EVTCENTERSRV *pThis, u32 pMsgHdr);
boolean _EVTCENTERSRV_HandleVoiceMailEvent(MMI_EVTCENTERSRV *pThis, MMI_CPHSSRV_VM_Status_e nCPHSStatus, u32 nCurrentDualID);
boolean _EVTCENTERSRV_HandleMOISrInd(MMI_EVTCENTERSRV *pThis, u32 param1, u32 param2);
boolean _EVTCENTERSRV_HandleMMEvent(MMI_EVTCENTERSRV *pThis, MAE_EventId eventID, u32 param1, u32 param2);

void _EVTCENTERSRV_SetEventReminderAlert(MMI_EVTCENTERSRV *pThis, EvtCenter_Dialog_Type_e eDialogType);
void _EVTCENTERSRV_CancelEventReminderAlert(MMI_EVTCENTERSRV *pThis, EvtCenter_Dialog_Type_e eDialogType);

MAE_Ret _EVTCENTERSRV_StartMCA(MMI_EVTCENTERSRV *pThis, u32 nMsgID, u32 nNewMsg, MsgType_e nViewerType);

boolean _EVTCENTERSRV_NotifyAliveWdgSrv(MMI_EVTCENTERSRV *pThis, EvtCenter_Model_Index_e eModelEvent, boolean bIsNew);
boolean _EVTCENTERSRV_HandleNewCBS(MMI_EVTCENTERSRV *pThis, u32 CBMsgID);
boolean _EVTCENTERSRV_HandleDelCBS(MMI_EVTCENTERSRV *pThis, u32 CBMsgID);

MAE_Ret _EVTCENTERSRV_ContextSwitchDoNotify(MMI_EVTCENTERSRV *pThis, u32 NotifyMask, MAE_EventId NotifyEvent, u32 Param1, u32 Param2, PfnEventCleanup pCleanFnc);
MAE_Ret _EVTCENTERSRV_DoNotify(MMI_EVTCENTERSRV *pThis, u32 NotifyMask, MAE_EventId NotifyEvent, u32 Param1, u32 Param2, PfnEventCleanup pCleanFnc);
void _EVTCENTERSRV_DoNotifyResumeCB(IBase *pObj, u32 Param);
void _EVTCENTERSRV_FlushAPStackCB_CB(IBase *pObj, u32 bCompleted);
void _EVTCENTERSRV_FlushAPStack(MMI_EVTCENTERSRV *pThis, EvtCenter_Model_Index_e eType);

//void _EVTCENTERSRV_StartMCA_CB(IBase *pIssuer, u32 Param);
//void _EVTCENTERSRV_StartCBMCA_CB(IBase *pIssuer, u32 Param);
void _EVTCENTERSRV_StartMCA_CB(void *pvUserData, MAE_Ret nRspCode);
void _EVTCENTERSRV_StartCBMCA_CB(void *pvUserData, MAE_Ret nRspCode);

void McaAppRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);
void McaAppRspCb(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);

MAE_Ret _EVTCENTERSRV_APNAutoDetection(MMI_EVTCENTERSRV *pThis, u8 nSIMModule, boolean bCurrentSIM);
void _EVTCENTERSRV_CheckEventReminderByCFG(MMI_EVTCENTERSRV *pThis);

void _EVTCENTERSRV_CFGSrvListener(void *pUserData, ModelEvent_t *pMdlEvt);
void _EVTCENTERSRV_AdaptNameOrNum(MMI_EVTCENTERSRV *pThis,u8 *PhbNumber,MAE_WChar *pDialogStr,MAE_WChar *pMemoStr);

#ifdef __APP_MMI_ANSWERING_MACHINE__
void _EVTCENTERSRV_ProcessAnsweringMachineFailedInd(MMI_EVTCENTERSRV *pThis, u32 u32AnsweringMachineFailedType);
void _EVTCENTERSRV_FlushAPStackCB_VoiceBox(IBase *pObj, u32 bCompleted);
#endif

#ifdef __MMI_SWITCH_MODE_WHEN_NO_NETWORK__
boolean _EVTCENTERSRV_HandleMMSrvNetworkRegInd(MMI_EVTCENTERSRV *pThis, u32 param1, u32 param2);
#endif // __MMI_SWITCH_MODE_WHEN_NO_NETWORK__

#ifdef __FT_AUTO_TEST__
static void _EVTCENTERSRV_CleanOSF (MMI_EVTCENTERSRV *pThis);
static MAE_Ret _EVTCENTERSRV_ParseOSF(MMI_EVTCENTERSRV *pThis, MccMnc_t *pMccMnc);
#endif //__FT_AUTO_TEST__

#if defined(__JAVA_LOW_MEM_CONCURRENT_HANDLE_MMI__) || defined(__MEMORY_LOW_KILL_3RD_VENDOR__)
void _EVTCENTERSRV_MemCheckSubjectListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
#endif // __JAVA_LOW_MEM_CONCURRENT_HANDLE_MMI__ || __MEMORY_LOW_KILL_3RD_VENDOR__

/** _EVTCENTERSRV_CheckDpmWithSlowMcp
@brief   Show prompt dialog if current configuration is slow MCP(Page-Page or SPI) with DPM enabled

@param[in]      pThis                       Pointer to EvtCenterSrv's instance

@retval None.
*/
void _EVTCENTERSRV_CheckDpmWithSlowMcp(MMI_EVTCENTERSRV *pThis);

#endif //__MMI_EVTCENTERSRV_MICS_H__
