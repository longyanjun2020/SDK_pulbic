/**
 * @file    mmi_if_bt.h
 * @brief   The file handles the BT event and forward to BT service
 * @author  christine.tai@mstarsemi.com
 * 
 */
#ifndef __MMI_IF_BT_H__
#define __MMI_IF_BT_H__

#ifdef __BLUETOOTH_MMI__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"



__SLDPM_FREE__ void mmi_bt_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_bt_poweronoff_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_inquiry_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_inquiry_cnf_if(IBase* pRecipient, struct vm_msg *pData);
__SLDPM_FREE__ void mmi_bt_name_query_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_delete_device_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_set_local_name_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_set_discovery_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_pin_code_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_pair_done_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_acl_link_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_acl_link_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_link_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_link_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_call_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_call_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_volume_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_atcmd_ind_if(IBase* pRecipient, struct vm_msg *pData);

#if defined (__BLUETOOTH_DRV_MSTAR__)
void mmi_bt_audio_call_pkt_type_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_audio_link_conn_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_acl_mode_change_ind_if(IBase* pRecipient, struct vm_msg *pData);
#endif //__BLUETOOTH_DRV_MSTAR__

static void mmi_bt_clean_info_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
static void mmi_bt_clean_addr_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
static void mmi_bt_clean_audio_link_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);

static void request_not_supported(IBase* pRecipient, struct vm_msg *pData);

__SLDPM_FREE__ void mmi_cb_bt_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_bt_obex_link_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_obex_send_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __BLUETOOTH_DRV_MSTAR_ACRUX2__
void mmi_bt_loopback_test_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif

void mmi_bt_obex_receive_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_obex_receive_cnf_if(IBase* pRecipient, struct vm_msg *pData);

void mmi_bt_obex_write_file_ind_if(IBase* pRecipient, struct vm_msg *pData);

static void mmi_bt_clean_ATCMD_Req(IBase* pIssuer, u32 nParam1, u32 nParam2);

#ifdef __BLUETOOTH_OBEX_MMI__
static void mmi_bt_clean_obex_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
#endif

void mmi_cb_bt_trans_status_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_bt_write_file_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_bt_obex_reset_ind_if(IBase* pRecipient, struct vm_msg *pData);

#ifdef __BLUETOOTH_A2DP_MMI__
void mmi_bt_a2dp_link_cnf_if(IBase* pRecipient,  struct vm_msg *pData);
void mmi_bt_a2dp_link_ind_if(IBase* pRecipient,  struct vm_msg *pData);
void mmi_bt_a2dp_action_cnf_if(IBase* pRecipient,  struct vm_msg *pData);
void mmi_cb_bt_a2dp_status_changed_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_bt_a2dp_unblock_bt_ind_if(IBase* pRecipient, struct vm_msg *pData);
static void mmi_bt_clean_a2dp_link_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
#ifdef __BLUETOOTH_AVRCP_MMI__
void mmi_bt_avrcp_action_ind_if(IBase* pRecipient,  struct vm_msg *pData);
void mmi_bt_avrcp_action_cnf_if(IBase* pRecipient,  struct vm_msg *pData);
#endif /* __BLUETOOTH_AVRCP_MMI__ */
#endif /* __BLUETOOTH_A2DP_MMI__ */
void mmi_bt_sdp_service_cnf_if(IBase* pRecipient,  struct vm_msg *pData);
void mmi_bt_rf_testmode_cnf(IBase* pRecipient, struct vm_msg *pData);

#ifdef _MSIM_
void _SimuRecvFileInd(IBase* pRecipient);
void mmi_sim_trigger_RECVFILEIND(u8 *Addr, u32 CoD, MAE_WChar *pwFilePath);
#endif

#endif // __BLUETOOTH_MMI__

#endif /* __MMI_IF_BT_H__ */
