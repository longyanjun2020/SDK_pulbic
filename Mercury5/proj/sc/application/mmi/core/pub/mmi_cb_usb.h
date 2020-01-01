
/**
 * @file    mmi_cb_usb.h
 * @brief   The file handles all the USB callback function from EMA
 * @author  allan.hsu@mstarsemi.com
 * 
 * @version $Id: mmi_cb_usb.h 36778 2009-07-29 10:50:17Z stone.shih $
 */
 
#ifndef __MMI_CB_USB_H__
#define __MMI_CB_USB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "ABL_Usb.h"

/*
	Function
*/

void MMI_USB_CB_UsbReturnCB(u16 senderID, u32 userValue, ABL_UsbErrCode_e status, ABL_UsbInfo_t *pUsbGetInfo);

#endif /* __MMI_CB_USB_H__ */

