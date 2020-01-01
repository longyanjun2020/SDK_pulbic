#ifndef __MMI_IF_QQ_H__
#define __MMI_IF_QQ_H__

#ifdef __cplusplus
extern "C" {
#endif

void mmi_qq_msg_parser(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_InitQQClientCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_DestroyQQClientCnf(IBase *pRecipient, vm_msg_t *pMsg);



void mmi_qq_LoginCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_VerifyCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_LogoutCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_EvtUpdate(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_DelBuddyByIdCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_AddBuddyByIdCnf(IBase *pRecipient, vm_msg_t *pMsg);

void mmi_qq_GetBuddyInfoCnf(IBase *pRecipient, vm_msg_t *pMsg);

//void mmi_qq_ChangeStatusCnf(IBase *pRecipient, vm_msg_t *pMsg);

#ifdef __cplusplus
}
#endif

#endif //__MMI_IF_QQ_H__

