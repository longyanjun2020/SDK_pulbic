/**
 * @file    mmi_if_ss.h
 * @brief   The file handles the RIL SS event and forward to SS service
 * @author  lih.wang@mstarsemi.com
 * 
 * @version $Id: mmi_if_ss.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */

#ifndef __MMI_IF_SS_H__
#define __MMI_IF_SS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_datamodel.h"

#include "mmi_sssrv_def.h"

void mmi_ss_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void ss_request_not_supported(IBase* pRecipient, struct vm_msg *pData);


MAE_Ret mmi_ss_if_CreateDataModel(IShell *pIShell, IDataModel **ppDataModel, SSSRV_unMsg_t **ppData, IBase* pRecipient);
void mmi_ss_if_MsgDataModelFree(void* pData, IBase *pOwner);
void mmi_ss_if_ReleaseMsgDataModel(IBase* pOwner, u32 lParam, u32 dParam);


void mmi_ss_call_divert_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_call_barring_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_call_waiting_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_ussd_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_ussd_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_ussd_err_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_ussd_not_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_change_barring_pwd_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_set_cug_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_que_cug_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_set_aoc_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_que_aoc_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_acm_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_amm_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_puc_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_ss_clx_cnf_if(IBase* pRecipient, struct vm_msg *pData);
    
#endif /* __MMI_IF_SS_H__ */
