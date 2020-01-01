/**
* @file mmi_messageeditorapp_sms.h
*
* Class Id: CLSID_SEA
*
*/

#ifndef __MMI_MESSAGEEDITORAPP_SMS_H__
#define __MMI_MESSAGEEDITORAPP_SMS_H__

#include <stdlib.h>
#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_priv.h"

//private interface
__SLDPM_FREE__ static MAE_Ret SEA_SmsSaveMsg(MMI_SEA *pThis, SMI_MsgLocation_e eLocation, MAE_WChar *pContent, MAE_WChar *pAddr, SMI_MsgID_t *msgID );
__SLDPM_FREE__ static void SEA_SmsUpdatePageNumber(void *pInstance, u32 page, u32 restChar);

__SLDPM_FREE__ void SEA_InputWdgLengthEncodingChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, SMSData_t *pSMSData, IWidget *pWidget);

//public interface
__SLDPM_FREE__ void SEA_SmsInitData(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_SmsReleaseData(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_SmsLoadEditorView( MMI_SEA *pThis);
__SLDPM_FREE__ void  SEA_SmsSetEditorData(MMI_SEA* pThis, SEA_EDITOR_Info_t* info, u8 *pSIMBuf, u32 nSimBufSize);
__SLDPM_FREE__ void SEA_SmsAddContent(MMI_SEA* pThis, MAE_WChar* pAddedText);
__SLDPM_FREE__ MAE_Ret SEA_SmsSendMsg(MMI_SEA* pThis, TextInfo tTextInfo);
__SLDPM_FREE__ MAE_Ret SEA_SmsOperationSaveSMSAndPopDialog(MMI_SEA *pThis);
__SLDPM_FREE__ MAE_Ret SEA_SmsOperationSaveSMS(MMI_SEA *pThis, MAE_WChar *pText);
MAE_Ret SEA_SmsOperationSendSMS(MMI_SEA *pThis);
__SLDPM_FREE__ void SEA_SmsCopyRecipient(MMI_SEA *pThis, SMS_MsgRecipLst *pMsgRecipLst,SMI_MsgHdr_t *pMsgHdr);
#ifdef __MMS_MMI_CDMMS__
__SLDPM_FREE__ MAE_Ret SEA_SmsOperationConvertToMMS(MMI_SEA *pThis,MMI_MmsObjectType_e eInertObj, MAE_WChar *pURL);
#endif
__SLDPM_FREE__ MAE_Ret SEA_SmsOperationSendSMS(MMI_SEA *pThis);

#endif
/*-------------------------------------------------------------------------*/
