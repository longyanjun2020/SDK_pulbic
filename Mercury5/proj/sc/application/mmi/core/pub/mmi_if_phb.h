
/**
 * @file    mmi_if_phb.h
 * @brief   The file handles the RIL PHB event and forward to PHB service
 * @author  ryb.chen@mstarsemi.com
 * 
 * @version $Id: mmi_if_phb.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_PHB_H__
#define __MMI_IF_PHB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_datamodel.h"
#include "mmi_phbsrv_def.h"
#include "mmi_req_phb.h"

void mmi_phb_msg_parser						(IBase* pRecipient, struct vm_msg *pData);

void mmi_phb_query_storage_status_cnf_if	(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_read_entry_cnf_if				(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_write_entry_cnf_if				(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_delete_entry_cnf_if			(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_delete_all_entry_cnf_if		(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_avoid_init_cnf_if				(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_set_voice_mail_number_cnf_if	(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_set_extended_mode_cnf_if		(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_sim_entry_ready_ind_if			(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_set_fdn_mode_cnf_if			(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_fdn_adn_swap_ready_ind_if		(IBase* pRecipient, struct vm_msg *pData);
void mmi_phb_checksum_ind_if		(IBase* pRecipient, struct vm_msg *pData);
#ifdef __3G_RIL_MMI__
void mmi_phb_ecc_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif // __3G_RIL_MMI__

void request_not_supported					(IBase* pRecipient, struct vm_msg *pData);


#endif /* __MMI_IF_PHB_H__ */

