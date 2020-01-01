/**
* @file mmi_messageeditorapp_handler.h
*
* Class Id: CLSID_SEA
*
*/

#ifndef __MMI_MESSAGEEDITORAPP_HANDLER_H__
#define __MMI_MESSAGEEDITORAPP_HANDLER_H__


#include "mmi_messageeditorapp.h"
#include "mmi_messageeditorapp_priv.h"
#include "mmi_messageeditorapp_mms.h"
#include "mmi_messageeditorapp_sms.h"
#include "mmi_if_cdmms.h"


// event callback
void SEA_HandleSmsEditorAutoClose(void *pData);
#ifdef __MMS_MMI_CDMMS__
void SEA_HandlerMmstxGetAllSlideCnf(void *pInstance,MMI_GetMmsAllSlidesCnf_t *pCnfData);
void SEA_HandlerMmstxGetSubjectCnf(void *pInstance,MMI_GetMmsSubjectInfoCnf_t *pCnfData);
void SEA_HandlerMmstxGetAttachesCnf(void *pInstance,MMI_GetMmsAllAttachesCnf_t *pCnfData);
void SEA_HandlerMmstxGetRecvlistCnf(void * pInstance,MMI_GetMmsReceiverListCnf_t * pRecipients);
void SEA_MmsSaveMessageCnf( void *pData, MMI_SaveMmsCnf_t *pSaveMmsCnf);
void SEA_MmsSaveMessageCnfAndSend(void *pData, MMI_SaveMmsCnf_t *pSaveMmsCnf);
#endif
void SEA_HandleAccpetCallCB(void *pData, boolean bResult, u32 nCause);
void SEA_HandlerSmiRetrvMsgDataFromSIMCnf( void *pInstance,SMI_MsgMgrStatus_e eStatus,SMI_SIMData_t *pSIMData);

#endif
/*-------------------------------------------------------------------------*/
