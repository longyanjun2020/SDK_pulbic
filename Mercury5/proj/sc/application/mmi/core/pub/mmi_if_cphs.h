/**
 * @file    mmi_if_cphs.h
 * @brief   The file handles the RIL CPHS event and forward to CPHS service
 * @author  cosmo.sung@mstarsemi.com
 * 
 * @version $Id:
 */
#ifndef __MMI_IF_CPHS_H__
#define __MMI_IF_CPHS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_cphssrv_def.h"

void mmi_cphssrv_ready_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_cphssrv_voice_mail_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_query_voice_mail_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_query_line_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_ready_ind_if(void *pData, IBase* pRecipient);
void mmi_cphssrv_query_mail_box_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_set_mail_box_number_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_set_response_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphssrv_read_functionality_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __3G_RIL_MMI__
void mmi_cphssrv_network_operator_name_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif // __3G_RIL_MMI__

void cphssrv_request_not_supported(IBase* pRecipient, struct vm_msg *pData);


#endif /* __MMI_IF_CPHS_H__ */
