/**
 * @file    mmi_if_atsync_sms.h
 * @brief   The file handles the ATSync SMS event and forward to ATSync service
 * @author  
 * 
 * @version $Id:
 */
#ifndef __MMI_IF_ATSYNC_SMS_H__
#define __MMI_IF_ATSYNC_SMS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"       
#include "mmi_atsyncsrv.h"

#define ATSYNC_SMS_FIELD_SIM_MASK_ALL  0x7FFF
#define ATSYNC_SMS_FIELD_ME_MASK_ALL   ATSYNC_SMS_FIELD_SIM_MASK_ALL

enum
{
    ATSYNC_SMS_STATUS_READ = 1,
    ATSYNC_SMS_STATUS_UNREAD = 3,
    ATSYNC_SMS_STATUS_SENT = 5,
    ATSYNC_SMS_STATUS_UNSENT = 7,
    ATSYNC_SMS_STATUS_SENDING = 9,
    ATSYNC_SMS_STATUS_SENDFAILED = 11,
    ATSYNC_SMS_STATUS_RETRY = 13,
    NUM_ATSYNC_SMS_STATUS
};

void mmi_if_atsync_sms_query_storage_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_set_storage_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_query_totalsize_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_query_used_number_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_read_entry_all_fields_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_send_write_entry_all_fields_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_query_next_index_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_delete_entry_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_sms_query_supported_field_ind(IBase* pRecipient, struct vm_msg *pData);

void mmi_if_atsync_sms_query_storage_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal);
void mmi_if_atsync_sms_set_storage_rsp(u8 nPort, u8 nModule, u8 nCmdResult);
void mmi_if_atsync_sms_query_capacity_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal);
void mmi_if_atsync_sms_query_usedsize_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal);
void mmi_if_atsync_sms_query_next_id_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal);
void mmi_if_atsync_sms_send_write_entry_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal, u8 nSrcWriteMulti, u8 nSrcMultiCount, ATSYNCSRV_SMS_Rsp_Evt_e SMSRspEvt);
void mmi_if_atsync_sms_delete_entry_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u16 nCmdVal);
void mmi_if_atsync_sms_read_entry_rsp(u8 nPort, u8 nModule, u8 nCmdResult, void* pCmdVal);
void mmi_if_atsync_sms_query_supported_field_rsp(u8 nPort, u8 nModule, u8 nCmdResult, u32 nCmdVal);

#endif /* __MMI_IF_ATSYNC_PHB_H__ */
