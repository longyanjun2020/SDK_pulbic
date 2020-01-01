/**
* @file mmi_messageeditorapp_util.h
*
* Class Id: CLSID_SEA
*
*/

#ifndef __MMI_MESSAGEEDITORAPP_UTIL_H__
#define __MMI_MESSAGEEDITORAPP_UTIL_H__


#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_priv.h"
#include "mmi_common_dialog_id.h"
#include "mmi_launcher_common.h"

enum
{
    SEA_OptionMenuType_SKLEFT,
    SEA_OptionMenuType_SKACTION
};
typedef u8 SEA_OptionMenuType_e;

__SLDPM_FREE__ MAE_Ret SEA_DuplicateStartParam(IBase *pThis,SEA_EDITOR_Info_t *pInitData ,SEA_EDITOR_Info_t **pOutInitData );
__SLDPM_FREE__ MAE_Ret SEA_CheckAirplaneMode(MMI_SEA* pThis, boolean *pbAirplainMode);
__SLDPM_FREE__ MAE_Ret SEA_AirplaneSaveResultCallBack(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
__SLDPM_FREE__ MAE_Ret SEA_LoadDialog(MMI_SEA* pThis,u32 ntextID ,u32 COMMON_DIALOG_VIEWID ,PFN_DlgHandler fnCallback );
__SLDPM_FREE__ MAE_Ret SEA_CreateDualSimView(MMI_SEA* pThis);
__SLDPM_FREE__ MAE_Ret SEA_LoadProcessDialog(MMI_SEA* pThis, u32 nTextID, boolean bAutoClose);
__SLDPM_FREE__ MAE_Ret SEA_CloseDialogWithObjectListEvt(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__SLDPM_FREE__ MAE_Ret SEA_CloseDialogAndCloseApplet(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
__SLDPM_FREE__ MAE_Ret SEA_CloseDialog(void *pData);
__SLDPM_FREE__ MAE_Ret SEA_CloseInfoDialog(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
__SLDPM_FREE__ MAE_Ret SEA_CloseDialogorCloseApplet(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#if defined(__MMS_MMI_CDMMS__) && defined(__USER_FILE_DELETER__)
MAE_Ret SEA_CloseDialogAndFileManagerDeleteApp(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
__SLDPM_FREE__ MAE_Ret SEA_LoadSendResultDialog(MMI_SEA* pThis, boolean bAirplaneMode);

/*
 * mm_Task() regularly calls SEA_SmsUpdatePageNumber(),
 * which calls the functions marked by __SLDPM_FREE__.
 * 
 */
__SLDPM_FREE__ MAE_Ret SEA_InsertContactItem(MAE_WChar **ppNewData, u32 *pnTotalLen, u32 FieldTextID, MAE_WChar *pData);
__SLDPM_FREE__ MAE_Ret SEA_InsertContactDetail(void *pContactDetals, MAE_WChar **ppContent);
__SLDPM_FREE__ MAE_Ret SEA_LoadEditorOptionMenu(MMI_SEA *pThis, SEA_OptionMenuType_e eType, PfnWdgMenuSoftkeyCancel pOptHandleCB);
__SLDPM_FREE__ MAE_Ret SEA_LaunchTemplateApplet(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_LaunchFileManagerByMediatype(MMI_SEA *pThis, FileMgrApp_FilterType_e eContentType);
__SLDPM_FREE__ MAE_Ret SEA_LaunchCalendar(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_LaunchPhoneBookForInsertVCard(MMI_SEA *pThis);

__SLDPM_FREE__ void SEA_ProcessDialogTimerCB(void* pData);
__SLDPM_FREE__ void SEA_FreeStartParam(IBase *pIssuer, u32 Param);
__SLDPM_FREE__ void SEA_StartMSASendOptions(IBase *pObj, u32 Param);
__SLDPM_FREE__ void SEA_StartSVAFree(IBase *pIssuer, u32 Param);
__SLDPM_FREE__ void SEA_SavedMsgTransfer(SMI_MsgHdr_t MsgData, void **ppOutData, void *pUserData);
__SLDPM_FREE__ void SEA_GetSIMStatus(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_DualSimSoftkeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ void SEA_LoadSaveConfirmDialog(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_InputOptInputMenuL2SoftkeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ void SEA_MMSEditorOptionSoftkeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ void SEA_SMSEditorOptionSoftkeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ void SEA_HandleInsertTemplate(MMI_SEA *pThis, MAE_WChar *pTemplate);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
__SLDPM_FREE__ void SEA_HandleInsertVCard(MMI_SEA *pThis);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
__SLDPM_FREE__ void SEA_HandleInsertVCalendar(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_OperationExitApplet(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_HandleInsertObject(MMI_SEA *pThis, MMI_MmsObjectType_e type);

__SLDPM_FREE__ TextInfo SEA_GetContentInfo(MMI_SEA* pThis);
__SLDPM_FREE__ u32 SEA_GetSaveResultID(MMI_SEA* pThis, boolean bAirplaneMode);
__SLDPM_FREE__ boolean SEA_isUsbStorage(MMI_SEA *pThis, PFN_DlgHandler fnCallback);

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
MAE_Ret SEA_CreateSmsSelectSimMsgView(MMI_SEA* pThis, SmsSelectSimMsgMenuWndData_t *pData);
void SEA_SmsSelectSimMsgSoftkeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserved);
#endif

#endif
/*-------------------------------------------------------------------------*/
