//==============================================================================
//
//  File        : mmpf_usbh_enum.h
//  Description : Header file for the USB Host Enumeration
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_ENUM_H_
#define _MMPF_USBH_ENUM_H_

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#include "mmpf_usbh_core.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

#define CTL_XFER_DATA_BUF_SIZE      (4096)

//==============================================================================
//
//                              PUBLIC VARIABLES
//
//==============================================================================

extern MMP_UBYTE    gubCtlXferData[CTL_XFER_DATA_BUF_SIZE];

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern MMP_ERR MMPF_USBH_RootHubEnum(void);
extern MMP_ERR MMPF_USBH_ConnectDriver(USBH_DEVICE *UsbDev);

#endif //(USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#endif //_MMPF_USBH_ENUM_H_

