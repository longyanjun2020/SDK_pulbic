/**
 * @file    mmi_if_atsync.h
 * @brief   The file handles the ATSync event and forward to ATSync service
 * @author  
 * 
 * @version $Id:
 */
#ifndef __MMI_IF_ATSYNC_H__
#define __MMI_IF_ATSYNC_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_class.h"
#include "mmi_atsyncsrv.h"

/* For build successfully for merge BNW and 1.05io */
#define DISABLE_AT_SYNC

void mmi_if_atsync_mrl_phb_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_mrl_sms_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_mrl_calllog_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_ati_msg_parser(IBase* pRecipient, struct vm_msg *pData);

MAE_Ret mmi_if_atsync_CreateAndSetDataModel(IDataModel **ppDataModel, void *pData, u32 nSize, PfnModelFree pfnFree, IBase* pRecipient);
void mmi_if_atsync_MsgDataModel_SimpleStruct_Free(void* pData, IBase *pOwner);
void mmi_if_atsync_PostEventExDataFree(IBase* pOwner, u32 pModel, u32 dParam);

MAE_Ret mmi_if_atsync_SendAtiSrcWithEvent(IBase* pRecipient, MAE_EventId nEvtId, u8 nPortId, u8 nModuleId, u32 nArg);
MAE_Ret mmi_if_atsync_SetAtiSrcInfo(ATSYNCSRV_ATI_Src_t **ppSrcInfo, u8 nPortId, u8 nModuleId);

MAE_Ret mmi_if_atsync_PrepareMsgToSend(struct vm_msg **ppMsg, u8 nDualID);

#endif /* __MMI_IF_ATSYNC_H__ */
