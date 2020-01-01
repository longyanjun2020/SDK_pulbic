/**
* @file    mmi_req_usb.h
* @brief   The file handles all the USB request function to EMA
* @author  allan.hsu@mstarsemi.com
* 
* @version $Id: mmi_req_usb.h 25328 2009-03-11 03:29:50Z otto.wu $
*/

#ifndef __MMI_REQ_USB_H__
#define __MMI_REQ_USB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_usbsrv.h"

/*
Function
*/

//MMI_USB_RESULT_E mmi_usb_open_req(MMI_USB_DEVICE_E usbDev);
void mmi_usb_open_req(MMI_USB_DEVICE_E usbDev, UsbSrvWebCamFlickerConfig_t eUsbCamFlickerConfig);
void mmi_usb_close_req(MMI_USB_DEVICE_E usbDev);
void mmi_usb_attach_req(void);

/*
MMI_USB_RESULT_E mmi_usb_Reg_notification_req(
#ifdef __USB_WITH_IMEI__
                                              u8 *pImeiCode);
#else
                                              void);
#endif
*/
MMI_USB_RESULT_E mmi_usb_common_Reg_notification_req(MMI_USB_RSP_TYPE_E eUSB_RSP_Type
#ifdef __USB_WITH_IMEI__
                                                  ,u8 *pIMEI
#endif
                                                  );


#ifdef __DUAL_CHARGER_MMI__

MMI_USB_RESULT_E mmi_usb_Reg_VBUS_Connect_notification_req(
    #ifdef __USB_WITH_IMEI__
                                                        u8 *pImeiCode );
    #else
                                                        void);
    #endif

MMI_USB_RESULT_E mmi_usb_Reg_VBUS_Remove_notification_req(
#ifdef __USB_WITH_IMEI__
                                                        u8 *pImeiCode);
#else
                                                        void);
#endif
    
MMI_USB_RESULT_E mmi_usb_RegUsbAttachAndPollingReg(void);
MMI_USB_RESULT_E mmi_usb_StopPolling(void);
#endif

#endif /* __MMI_REQ_USB_H__ */
