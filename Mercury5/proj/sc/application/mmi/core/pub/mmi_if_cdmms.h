/**
* @file    mmi_if_cdmms.h
* @brief   The file handles the cd mms notify events
* 
* @version $Id: mmi_if_cdmms.h 12999 2008-08-01 03:13:11Z joe.hsu $
*/
#ifndef __MMI_IF_CDMMS_H__
#define __MMI_IF_CDMMS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_if_def.h"
#include "mmi_common_mms.h"

typedef struct
{
    s32  index;
	s32 contentSize;
    MMI_MmsStatus_e status;
	MMI_MMS_FS_MAILBOX_e    mailBox;
	boolean                 isSDKMsg;
} MMI_SaveMmsCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
    MMI_MMS_Receiver_List_t mmsRecvList;    
}MMI_GetMmsReceiverListCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
    u8 senderNum[MMI_MMS_MAX_RECEIVE_LIST+1];
}MMI_GetMmsSenderAddrCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
    MMI_MmsFs_itemInfo mmsItemInfo;
}MMI_GetMmsItemInfoCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
    u8 subjectInfo[MMI_MMS_MAX_SUBJECT_LEN+1];
}MMI_GetMmsSubjectInfoCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
    u8 mmsStatus;
}MMI_GetMmsStatusInfoCnf_t;

typedef struct
{
    MMI_MmsStatus_e     status;
    MMI_MMS_GET_SLIDES  *pSlideData;    
} MMI_GetMmsAllSlidesCnf_t;

typedef struct
{
    s32 index;
    u32 time;
    MMI_MmsStatus_e status;
    MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_SendMmsByBoxCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
}MMI_TransCancelCnf_t;

typedef struct
{
    MMI_MMS_CdMms_Info_t  pCdMmsInfo;   
}MMI_RecvMmsBodyCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
}MMI_DelMmsByIdCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
}MMI_DelMmsByBoxCnf_t;

typedef struct
{
    MMI_MmsStatus_e     status;
    MMI_MMS_GET_ATTACHES_t  *pAttachData;   
} MMI_GetMmsAllAttachesCnf_t;

typedef struct
{
    s32                     msgIdx;
    MMI_MMS_FS_MAILBOX_e    mailBox;
    MMI_MmsFs_headInfo      headInfo;
    MMI_MmsFs_itemInfo      itemInfo;
}MMI_NewMmsNoteCnf_t;

typedef struct
{
    s32     boxSum;
    MMI_MMS_CdMms_Info_t  *pCdMmsInfo;  
}MMI_RetrvCdMmsCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
}MMI_SetMmsUnreadCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;       
}MMI_SendNotiRespCnf_t;
#ifdef __MMS_READ_REPORT__
typedef struct
{
    MMI_MmsStatus_e status;       
}MMI_SendReadReplyCnf_t;
#endif
typedef struct
{
	s32             msgIdx;
	MMI_MMS_FS_MAILBOX_e   mailBox; //desnation box
    MMI_MmsStatus_e status;       
}MMI_MoveMmsCnf_t;

typedef struct
{
    MMI_MmsStatus_e status;
}MMI_BootupMmsCnf_t;

typedef struct
{
    u8                  *pAppId;
    u8                  *pReplyToAppId;
	s32                 msgIdx;
	s32                 status;
	s32                 contentSize;
    MMI_MMS_Header_t    mmsHeader;
    MMI_MMS_Body_t      mmsBody;
} MMI_RecvMmsBodySDKCnf_t;

typedef struct
{
    MMI_MMS_Header_t    mmsHeader;
    MMI_MMS_Body_t      mmsBody;
} MMI_MMS_RetrieveCnf_t;

typedef void (*pfnMmsRetrieveCnf_t)(u8 *pAppId, u8 nModuleId, MMI_MMS_RetrieveCnf_t *pRetrvCnf, u32 nCallerID);

#ifdef __MMS_MMI_CDMMS_STORAGE_SWITCH__
typedef struct
{
    s32     status;
    void    *headInfo;
    void    *itemInfo;
    u8      *buffer;
    u32     bufferLen;
} MMI_GetMmsRawItemCnf_t;

typedef struct
{
    s32     status;
    s32     msgIdx;
} MMI_SaveMmsRawItemCnf_t;
#endif

#if defined(__FT_AUTO_TEST__)
typedef struct
{
	u8 senderNum[MMI_MMS_MAX_RECEIVE_LIST];
    u8 subjectInfo[MMI_MMS_MAX_SUBJECT_LEN+1];
    u8 attachement[256];
	u8 eSIMModule; // for outbox saving to store imsi    
}MMI_MMSAutotestSendReq_t;
#endif

void mmi_cdmms_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void cdmms_request_not_supported(IBase* pRecipient, struct vm_msg *pData);

void mmi_mms_save_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_receiver_list_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_sender_addr_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_item_info_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_subject_info_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_status_info_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_all_slides_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_send_by_box_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_trans_cancel_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_recv_body_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_del_by_id_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_del_by_box_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_new_note_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_get_all_attach_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_retrv_cdmms_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_send_notify_resp_cnf(IBase* pRecipient, struct vm_msg *pData);
#ifdef __MMS_READ_REPORT__
void mmi_mms_send_read_reply_cnf(IBase* pRecipient, struct vm_msg *pData);
#endif
void mmi_cdmms_FreeCnfInfo(IBase *pOwner, u32 lParam, u32 dParam);
void mmi_mms_move_mms_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_bootup_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_mms_recv_body_jsr_cnf(IBase* pRecipient, struct vm_msg *pData);
#ifdef __MMS_MMI_CDMMS_STORAGE_SWITCH__
void mmi_mms_get_raw_item_cnf( IBase *pRecipient, struct vm_msg *pData );
void mmi_mms_save_raw_item_cnf( IBase *pRecipient, struct vm_msg *pData );
#endif

#endif /* __MMI_IF_CDMMS_H__ */
