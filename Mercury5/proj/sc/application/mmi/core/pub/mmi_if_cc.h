/**
 * @file    mmi_if_cc.h
 * @brief   The file handles the RIL CC event and forward to CC service
 * @author  collin.chiang@mstarsemi.com
 * 
 * @version $Id: mmi_if_cc.h 40036 2009-09-11 12:34:27Z lih.wang $
 */
#ifndef __MMI_IF_CC_H__
#define __MMI_IF_CC_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_ccsrv_def.h"
 
void mmi_cc_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_cc_callref_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_alert_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_progress_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_dialing_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_ring_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_accept_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_chld_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_rel_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_dtmf_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_hangup_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_hangup_outgoingcall_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_call_setup_notification_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_incall_notification_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_tch_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_connected_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_abort_dtmf_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cc_call_oper_cnf_if(IBase* pRecipient, struct vm_msg *pData);		// Only allow to Hold, Retrieve or Swap call. (To avoid accept incoming call for AT+CHLD=2)
void mmi_cc_clcc_cnf_if(IBase* pRecipient, struct vm_msg *pData);

static void request_not_supported(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_CC_H__ */
