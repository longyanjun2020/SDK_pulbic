#ifndef __MMI_IF_EMAIL_H__
#define __MMI_IF_EMAIL_H__

#ifdef __cplusplus
extern "C" {
#endif

void mmi_email_msg_parser(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_OpenEmailAccountCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_getEmailAccountListCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_ReadEmailAccountCfgCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_WriteEmailAccountCfgCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_WriteEmailAccountInfoCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_ReadEmailSettingCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_WriteEmailSettingCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_DeleteEmailAccountCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_OpenEmailCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_SaveEmailCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_SortEmailHeaderListCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_DeleteEmailCnf(IBase *pRecipient, vm_msg_t *pMsg) ;

void mmi_email_MarkEmailAsReadCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_email_AccountStatusChangeCnf(IBase *pRecipient, vm_msg_t *pMsg);

#ifdef __cplusplus
}
#endif

#endif //__MMI_IF_EMAIL_H__

