/**
 * @file    mmi_if_usb.h
 * @brief   The document describes all the time out action of the timer used in MMI
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id $
 */
 
#ifndef __MMI_IF_USB_H__
#define __MMI_IF_USB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_datamodel.h"

#define VM_DEV_USB_RETURN		(VM_USB_BASE + 0x00)

void mmi_usb_msg_parser(IBase* pRecipient, struct vm_msg *pData);

//void mmi_usb_return_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_attach_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_open_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_close_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_reg_notification_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_notify_if(u32 uCusData, void *pNotifyInfo);

#ifdef __DUAL_CHARGER_MMI__
void mmi_usb_vbus_connect_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_vbus_remove_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_usb_stop_polling_if(IBase* pRecipient, struct vm_msg *pData);
#endif

#endif /* __MMI_IF_USB_H__ */
