//==============================================================================
//
//  File        : mmpf_usbh_hub.h
//  Description : Header file for the USB Host Hub
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_HUB_H_
#define _MMPF_USBH_HUB_H_

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#include "mmpf_usbh_core.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

/* The maximum ports supported for the connected hub device */
#define USB_HUB_MAX_PORT_NUM    (5)

/* Timeout for waiting interrupt data (hub status change) */
#define USB_HUB_INT_DATA_TO     (500)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _USB_HUB {
    USBH_DEVICE         *dev;
    USB_INTERFACE_DESC  IfDesc;
    USB_EP_DESC         EpDesc;
    USB_HUB_DESC        HubDesc;
    USB_HUB_PORT_STATUS PortStatus[USB_HUB_MAX_PORT_NUM];
    MMP_UBYTE           bNumPort;
    MMP_UBYTE           bChangeBitmap[3];
} USB_HUB;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern MMP_ERR MMPF_USBH_GetHubPortStatus(  USBH_DEVICE *UsbDev,
                                            MMP_UBYTE   ubPort,
                                            USB_HUB_PORT_STATUS *status);
extern MMP_ERR MMPF_USBH_SetHubPortFeature( USBH_DEVICE *UsbDev,
                                            MMP_UBYTE   ubPort,
                                            MMP_UBYTE   ubFeature);
extern MMP_ERR MMPF_USBH_ClrHubPortFeature( USBH_DEVICE *UsbDev,
                                            MMP_UBYTE   ubPort,
                                            MMP_UBYTE   ubFeature);
extern MMP_ERR MMPF_USBH_OpenHub(USBH_DEVICE *UsbDev);

#endif //(USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#endif //_MMPF_USBH_HUB_H_

