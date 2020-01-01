/**
 * @file    mmi_if_h324m.h
 */
#ifndef __MMI_IF_H324M_H__
#define __MMI_IF_H324M_H__

#ifdef __VT_3G324M__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_vtccsrv_def.h"

void mmi_324m_msg_parser(IBase *pRecipient, struct vm_msg *pData);

///SIG_3G324M_MMI_LOOPBACK_CNF
void mmi_324m_loopback_cnf_if(IBase *pRecipient, struct vm_msg *pData);
///SIG_3G324M_MMI_CALL_STATE_IND
void mmi_324m_call_state_ind_if(IBase* pRecipient, struct vm_msg *pData);
///SIG_3G324M_MMI_USER_INPUT_DTMF_CNF
void mmi_324m_user_input_dtmf_cnf_if(IBase *pRecipient, struct vm_msg *pData);
///SIG_3G324M_MMI_CHANNEL_ONOFF_IND
void mmi_324m_channel_onoff_ind_if(IBase *pRecipient, struct vm_msg *pData);

#endif //__VT_3G324M__
#endif /* __MMI_IF_H324M_H__ */

