/**
 * @file    mmi_if_atsync_phb.h
 * @brief   The file handles the ATSync Phonebook event and forward to ATSync service
 * @author  
 * 
 * @version $Id:
 */
#ifndef __MMI_IF_ATSYNC_PHB_H__
#define __MMI_IF_ATSYNC_PHB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_atsyncsrv.h"


void mmi_if_atsync_phb_query_storage_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_set_storage_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_query_total_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_query_used_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_read_all_fields_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_query_next_index_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_write_all_fields_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_delete_entry_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_if_atsync_phb_query_support_field_ind(IBase* pRecipient, struct vm_msg *pData);


void mmi_if_atsync_phb_query_storage_rsp(ATSYNCSRV_PHB_QueryStorageRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_set_storage_rsp(ATSYNCSRV_PHB_SetStorageRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_query_total_rsp(ATSYNCSRV_PHB_QueryTotalRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_query_used_rsp(ATSYNCSRV_PHB_QueryUsedRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_query_next_index_rsp(ATSYNCSRV_PHB_QueryNextIndexRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_write_all_fields_rsp(ATSYNCSRV_PHB_WriteAllFieldsRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_read_all_fields_rsp(ATSYNCSRV_PHB_ReadAllFieldsRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_delete_entry_rsp(ATSYNCSRV_PHB_DeleteEntryRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_query_support_field_rsp(ATSYNCSRV_PHB_QuerySupportFieldRsp_t* pRspData, u8 DualID);
void mmi_if_atsync_phb_delete_all_entry_rsp(ATSYNCSRV_PHB_DeleteEntryRsp_t* pRspData, u8 DualID);

#endif /* __MMI_IF_ATSYNC_PHB_H__ */
