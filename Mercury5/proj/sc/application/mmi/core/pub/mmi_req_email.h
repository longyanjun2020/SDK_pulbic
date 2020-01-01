#ifndef __MMI_REQ_EMAIL_H__
#define __MMI_REQ_EMAIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mmi_emailsrv.h"
/**
 * Open specified email account(Get mailbox info (inbox, draftbox, outbox, sentbox))
 *
 * \param accountID [in]
 *	The ID of email account
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_email_OpenEmailAccountReq(u32 accountID);

/**
 * Close specified email account(Get mailbox info (inbox, draftbox, outbox, sentbox))
 *
 * \param accountID [in]
 *	The ID of email account
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_email_CloseEmailAccountReq(u32 accountID);

/**
 * Get email header list for specified email account and mailbox
 *
 *
 * \return #TRUE if succeed, otherwise #FALSE
 */
s32 mmi_email_GetEmailAccountListReq(void);

s32 mmi_email_ReadEmailAccountCfgReq(u32 accountID);

s32 mmi_email_WriteEmailAccountCfgReq(u32 accountID, T_EMAIL_Account_Config *pEmailAccountCfg);

s32 mmi_email_WriteEmailAccountInfoReq(boolean NewAccount, u32 accountID, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList, T_EMAIL_Account_Config *pEmailAccountCfg);

s32 mmi_email_ReadEmailSettingReq(void);

s32 mmi_email_WriteEmailSettingReq(T_EMAIL_Account_Setting  *pEmailSetting);

s32 mmi_email_DeleteEmailAccountReq(u32 accountID, T_EMAIL_FS_ACCOUNT_HEAD_LIST *pEmailAccountList);

s32 mmi_email_OpenEmailReq(u32 accountID, u32 boxID, u32 msgID, u32 isOnlyHeader);

s32 mmi_email_SaveEmailReq(u32 accountID, u32 boxID, u32 msgID, boolean isNew, u8 *pBuf, u32 bufLen);

s32 mmi_email_SortEmailHeaderListReq(u32 accountID, u32 boxId, u32 sortBy);

s32 mmi_email_DeleteEmailReq(u32 accountID, u32 *emailList, u32 emailNum, u32 boxId);

s32 mmi_email_MarkEmailAsReadReq(u32 accountID, u32 boxID, u32 emailID, u8 isRead);

s32 mmi_email_SendReceiveReq(u32 accountID, EMAILSRV_ReqType reqType, u32 emailID);
#ifdef __cplusplus
}
#endif

#endif //__MMI_REQ_EMAIL_H__
