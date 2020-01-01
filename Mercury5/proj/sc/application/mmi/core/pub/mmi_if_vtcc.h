/**
 * @file    mmi_if_vtcc.h
 * @brief   The file handles the RIL VTCC event and forward to VTCC service
 * @author  
 * 
 * @version $Id: mmi_if_vtcc.h $
 */
#ifndef __MMI_IF_VTCC_H__
#define __MMI_IF_VTCC_H__

#ifdef __VT_3G324M__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_vtccsrv_def.h"
 
void mmi_vtcc_msg_parser(IBase* pRecipient, struct vm_msg *pData);

///VM_MRL_VT_CALLREF_IND
void mmi_vtcc_callref_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_ALERT_IND
void mmi_vtcc_alert_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_PROGRESS_IND
void mmi_vtcc_progress_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_TCH_IND
void mmi_vtcc_tch_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_CONNECT_IND
void mmi_vtcc_connected_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_DIALING_RSP
void mmi_vtcc_dialing_cnf_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_RING_IND
void mmi_vtcc_ring_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_ACCEPT_RSP
void mmi_vtcc_accept_cnf_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_REL_IND
void mmi_vtcc_rel_ind_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_HANGUP_RSP
void mmi_vtcc_hangup_cnf_if(IBase* pRecipient, struct vm_msg *pData);
///VM_MRL_VT_FALLBACK_RSP
void mmi_vtcc_fallback_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_chld_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_dtmf_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_hangup_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_hangup_outgoingcall_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_call_setup_notification_ind_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_incall_notification_ind_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_abort_dtmf_cnf_if(IBase* pRecipient, struct vm_msg *pData);
//void mmi_vtcc_call_oper_cnf_if(IBase* pRecipient, struct vm_msg *pData);		// Only allow to Hold, Retrieve or Swap call. (To avoid accept incoming call for AT+CHLD=2)
//void mmi_vtcc_clcc_cnf_if(IBase* pRecipient, struct vm_msg *pData);

#endif //__VT_3G324M__
#endif /* __MMI_IF_VTCC_H__ */

