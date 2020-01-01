/**
 * @file mmi_messageeditorapp_recipients.h
 *
 */
#ifndef __MMI_MESSAGEEDITORAPP_RECIPIENTS_H__
#define __MMI_MESSAGEEDITORAPP_RECIPIENTS_H__

#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_priv.h"
#include "mmi_messageeditorapp_util.h"

__SLDPM_FREE__ void SEA_RecipientMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ static void SEA_RecipientMenuAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
__SLDPM_FREE__ static void SEA_RecipientUpdateSKOnEditor(MMI_SEA *pThis,SEA_UpdateSK_e eSKEnable);
__SLDPM_FREE__ MAE_Ret SEA_RecipientsDeleteOne(MMI_SEA* pThis, int idx);
__SLDPM_FREE__ void SEA_RecipientEditorTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void SEA_ClearRecipientEditor(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_RecipientsFreeModelItem(void* pData, void* pOwner);
__SLDPM_FREE__ MAE_Ret SEA_RecipientsDeleteAll(MMI_SEA* pThis);
__SLDPM_FREE__ MAE_Ret SEA_RecipientsAdd(MMI_SEA* pThis,SEA_Recipient_t* item);
__SLDPM_FREE__ void SEA_RecipientOptionMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
__SLDPM_FREE__ static boolean SEA_RecipientEditorHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
__SLDPM_FREE__ void SEA_RecipientEditorEventHandlerFree( MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_RecipientButtonClickHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
__SLDPM_FREE__ void SEA_RecipientUpdateViewData(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_RecipientInitMenuData(MMI_SEA *pThis,SEA_RecipientType_e eRecipientType);
__SLDPM_FREE__ MAE_Ret SEA_RecipientLoadOptionView(MMI_SEA *pThis, SEA_OptionMenuType_e eType, WdgStaticMenuItem_t *pOptionArry,u32 nOptionSize);
__SLDPM_FREE__ MAE_Ret SEA_RecipientLaunchPB(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_RecipientFocusOnEditor(MMI_SEA *pThis,MAE_EventId evt, u32 keycode);
__SLDPM_FREE__ void SEA_RecipientUnFocusEditor(MMI_SEA *pThis);
__SLDPM_FREE__ boolean SEA_RecipientAddOneFromEditor(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_RecipientOperationDelOne(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_RecipientOperationAddFromPHB(MMI_SEA *pThis);
__SLDPM_FREE__ u32 SEA_RecipientGetSizeByType(MMI_SEA *pThis, SEA_RecipientType_e eRecipient);

#ifdef __MMS_MMI_CDMMS__
__SLDPM_FREE__ static boolean SEA_RecipientIsVaildRecipientString(u32 nStrLen, MAE_WChar *pStr);
#endif

#endif /* __MMI_MESSAGEEDITORAPP_RECIPIENTS_H__ */

