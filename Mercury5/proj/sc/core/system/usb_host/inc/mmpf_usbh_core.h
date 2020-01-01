//==============================================================================
//
//  File        : mmpf_usbh_desc.h
//  Description : Header file for the USB HOST Core
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_CORE_H_
#define _MMPF_USBH_CORE_H_

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#include "mmp_usb_inc.h"
#include "mmpf_usbh_cfg.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

/* Allow max two device connected to USB bus (one for hub; one for UVC dev) */
#define USB_BUS_MAX_DEV_NUM     (2)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _USBH_DEVICE {
    MMP_UBYTE       ubAddr;
    MMP_UBYTE       ubSpeed;
    MMP_UBYTE       ubMaxPktSize0;
    MMP_UBYTE       ubNakLimit0;
    USB_DEV_DESC    devDesc;
    USB_CONFIG_DESC cfgDesc;
} USBH_DEVICE;

typedef struct _USBH_BUS {
    MMP_UBYTE       NumDeviceInUse;
    MMP_BOOL        DeviceInUse[USB_BUS_MAX_DEV_NUM];
    USBH_DEVICE     Device[USB_BUS_MAX_DEV_NUM];
} USBH_BUS;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_USBH_InitBus(void);
void MMPF_USBH_CreateDevice(USBH_DEVICE **UsbDev);
void MMPF_USBH_FreeDevice(USBH_DEVICE *dev);
void MMPF_USBH_FreeAllDevice(void);

MMP_UBYTE MMPF_USBH_GetDeviceAssignedAddr(USBH_DEVICE *dev);
MMP_ERR MMPF_USBH_SetDevAddr(USBH_DEVICE *dev, MMP_UBYTE addr);
MMP_ERR MMPF_USBH_GetDevStatus(USBH_DEVICE *dev, MMP_UBYTE *buf);

#endif //(USB_EN))&&(SUPPORT_USB_HOST_FUNC)
#endif //_MMPF_USBH_CORE_H_
