/**
 * @file    mmi_if_mm.h
 * @brief   The file handles the RIL MM event and forward to MM service
 * @author  christoph.kuo@mstarsemi.com
 * 
 * @version $Id: mmi_if_mm.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_MM_H__
#define __MMI_IF_MM_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_mmsrv_def.h"
#include "mmi_mmsrv_util.h"

void mmi_mm_rr_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_pwon_msg_parser(IBase* pRecipient, struct vm_msg *pData);
#ifdef __GPRS_MMI__
void mmi_mm_gprs_msg_parser(IBase* pRecipient, struct vm_msg *pData);
#endif //__GPRS_MMI__
void mmi_cphs_ready_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_msg_parser(IBase* pRecipient, struct vm_msg *pData);

#ifdef __3G_RIL_MMI__
void mmi_ril_misc_msg_parser(IBase* pRecipient, struct vm_msg *pData);
#endif //__3G_RIL_MMI__

void mm_mm_clean_ba_list_cnf_if(IBase* pRecipient, struct vm_msg *pData);
MAE_Ret mmi_mm_if_CreateDataModel(IDataModel **ppDataModel, MMSRV_unMsg_t **ppData, IBase* pRecipient);
void mmi_mm_if_MsgDataModelFree(void* pData, IBase *pOwner);
void mmi_mm_if_ReleaseMsgDataModel(IBase* pOwner, u32 lParam, u32 dParam);
void mmi_mm_if_FreeMsgData(IBase* pOwner, u32 lParam, u32 dParam);

void mmi_mm_search_network_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_register_network_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_registered_plmn_info_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_network_reg_ind_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __GPRS_MMI__
void mmi_mm_gprs_network_reg_ind_if(IBase* pRecipient, struct vm_msg *pData);
#endif //__GPRS_MMI__
void mmi_mm_update_preferred_list_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_query_preferred_list_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_change_band_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_query_band_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_change_line_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_query_line_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_query_diverted_call_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_diverted_call_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_abort_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __GPRS_MMI__
void mmi_mm_gprs_attach_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_msclass_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_msclass_query_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_session_activate_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_session_deactivate_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_add_pdp_context_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_del_pdp_context_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_set_qos_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_gprs_que_qos_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_set_wgprs_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_query_wgprs_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif //__GPRS_MMI__
void mmi_mm_pwof_cfun_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_pwon_cfun_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_rssi_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_get_cell_info_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cphs_ready_ind_if(void *pData, IBase* pRecipient);
void mmi_mm_nitz_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mm_request_not_supported(IBase* pRecipient, struct vm_msg *pData);
#ifdef __PROGRAM_TEMP_IMEI_MMI__
void mmi_mm_store_imei_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif

#ifdef __3G_RIL_MMI__
void mmi_mm_cgmr_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_imei_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_sst_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_mgid_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_set_mcfg_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_query_mcfg_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_dbb_reboot_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_dbb_modem_error_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_misc_dbb_reset_factory_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_force_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_spn_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_mm_musermode_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif //__3G_RIL_MMI__

#endif /* __MMI_IF_MM_H__ */
