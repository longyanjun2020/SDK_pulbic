/**
 * @file    mmi_if_acc.h
 * @brief   The file handles the RIL CC event and forward to CC service
 * @author  eric.chen@mstarsemi.com
 * 
 * @version $Id: mmi_if_acc.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_ACC_H__
#define __MMI_IF_ACC_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"


__SLDPM_FREE__ void mmi_acc_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_acc_ind_plug_if(IBase* pRecipient, struct vm_msg *pData);

void mmi_dev_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_dev_factory_default_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_dev_clear_password_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_ACC_H__ */
