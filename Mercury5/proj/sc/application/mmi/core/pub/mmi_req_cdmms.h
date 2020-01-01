/**
 * @file    mmi_req_cdmms.h
 * @brief   The file handles all the message request function to RIL
 * @author  joe.hsu
 * 
 * @version $Id: mmi_req_cdmms.h 13121 2008-08-07 09:39:22Z joe.hsu $
 */
#ifndef __MMI_REQ_CDMMS_H__
#define __MMI_REQ_CDMMS_H__


#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_common_mms.h"

typedef struct
{
	s32 msgIdx;	
	MMI_MMS_FS_MAILBOX_e mailBox;
	MMI_MMS_Composer_Cntx	*pMmsComposerCntx;
	u8 imsi[MMI_MMS_FS_MAX_IMSI_LEN];
    u8                      *pAppId;
    u8                      *pReplyToAppId;
	boolean                 isSDKMsg;
}MMI_MMS_SaveMmsReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsReceiverListReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsSenderAddrReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsItemInfoReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsSubjectInfoReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsStatusInfoReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsAllSlidesReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;	
	u8 SimModule;
	u8 imsi[MMI_MMS_FS_MAX_IMSI_LEN];
	MMI_MmsFs_Config mmsCnfg;
}MMI_MMS_SendMmsByBoxReq_t;

typedef struct
{
	MMI_MmsFs_Config mmsCnfg;
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
	u8 SimModule;	
#ifdef __MMS_DOWNLOAD_LIMIT__
    u32 nMaxDlmSize;
#endif
}MMI_MMS_RecvMmsBodyReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_DelMmsByIdReq_t;

typedef struct
{
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_DelMmsByBoxReq_t;

typedef struct
{
	s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_MMS_GetMmsAllAttachesReq_t;

typedef struct
{
	s32 DataLength;
	u8  imsi[MMI_MMS_FS_MAX_IMSI_LEN];
	u8	PduData[175*9]; //for WAP push data
	u8  nSimModule;
    u8  from[MMI_MMS_MAX_ADDR_INFO + 1];
	u8  allowAnon;
}MMI_NewMmsNote_t;

typedef struct
{
	MMI_MMS_FS_MAILBOX_e mailBox;
}MMI_RetrvCdMmsReq_t;

typedef struct
{
    MMI_MmsFs_Config mmsCnfg;
    s32 msgIdx;
    MMI_MMS_FS_MAILBOX_e mailBox;
    u8 SimModule;       
}MMI_SendNotiRespReq_t;   
#ifdef __MMS_READ_REPORT__
typedef struct
{
    MMI_MmsFs_Config mmsCnfg;
    s32 msgIdx;
    MMI_MMS_FS_MAILBOX_e mailBox;
    u8 SimModule;       
}MMI_SendReadReplyReq_t;   
#endif
typedef struct
{
    s32 msgIdx;
	MMI_MMS_FS_MAILBOX_e SourcemailBox;
    MMI_MMS_FS_MAILBOX_e DesmailBox;
}MMI_MoveMmsReq_t; 

typedef struct
{
    u8 pathLen;
    u8 path[128+1];
    u8 devType;
}MMI_SetMmsStorePathReq_t;

typedef struct
{
    MMI_MMS_Header_t    mmsHeader;
    MMI_MMS_Body_t      mmsBody;
} MMI_MMS_SendReq_t;


typedef void (*pfnMmsSendCnf_t)(u8 *pAppId, MMS_MmsResponseStatus_e eRespStatus, u16 *pRespText, u32 nCallerID);


MAE_Ret mmi_mms_save_req(MMI_MMS_SaveMmsReq_t *pSaveMmsReq);
void mmi_mms_get_receiver_list_req(MMI_MMS_GetMmsReceiverListReq_t *pGetMmsReceiverListReq);
void mmi_mms_get_sender_addr_req(MMI_MMS_GetMmsSenderAddrReq_t *pGetMmsSenderAddrReq);
void mmi_mms_get_item_info_req(MMI_MMS_GetMmsItemInfoReq_t *pGetMmsItemInfoReq);
void mmi_mms_get_subject_info_req(MMI_MMS_GetMmsSubjectInfoReq_t *pGetMmsSubjectInfoReq);
void mmi_mms_get_status_info_req(MMI_MMS_GetMmsStatusInfoReq_t *pGetMmsStatusInfoReq);
void mmi_mms_get_all_slides_req(MMI_MMS_GetMmsAllSlidesReq_t *pGetMmsAllSlidesReq);
void mmi_mms_send_by_box_req(MMI_MMS_SendMmsByBoxReq_t *pSendMmsByBoxReq);
void mmi_mms_trans_cancel_req(void);
void mmi_mms_recv_body_req(MMI_MMS_RecvMmsBodyReq_t *pRecvMmsBodyReq);
void mmi_mms_del_by_id_req(MMI_MMS_DelMmsByIdReq_t *pDelMmsByIdReq);
void mmi_mms_del_by_box_req(MMI_MMS_DelMmsByBoxReq_t *pDelMmsByBoxReq);
void mmi_mms_new_note(MMI_NewMmsNote_t *pNewMmsNote);
void mmi_mms_get_all_attach_req(MMI_MMS_GetMmsAllAttachesReq_t *pGetMmsAllAttachesReq);
void mmi_mms_retrv_cdmms_req(MMI_RetrvCdMmsReq_t *pRetrvCdMmsReq);
void mmi_mms_send_notify_resp_req(MMI_SendNotiRespReq_t *pSendNotiRespReq);
#ifdef __MMS_READ_REPORT__
void mmi_mms_send_read_reply_req(MMI_SendReadReplyReq_t *pSendReadReplyReq);
#endif
void mmi_mms_move_mms_req(MMI_MoveMmsReq_t *pMoveMmsReq);
void mmi_mms_bootup_req(void);
void mmi_mms_set_store_path_req(MMI_SetMmsStorePathReq_t *pSetStorePathReq);
void mmi_mms_FreeMmsAllAttachCnfInfo(void *pData);
void mmi_mms_FreeMmsAllSlidesCnfInfo(void *pData);
u8* mmi_mms_EncodeLocalString2UTF8(void *pData, s32 *Len);
void mmi_mms_FreeStringBuf(u8 *utf8String);
#ifdef __MMS_MMI_CDMMS_STORAGE_SWITCH__
void mmi_mms_get_raw_item_req( void *pData );
void mmi_mms_save_raw_item_req( void *pData );
#endif
#endif /* __MMI_REQ_CDMMS_H__ */
