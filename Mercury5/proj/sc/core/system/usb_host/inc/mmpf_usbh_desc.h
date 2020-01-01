//==============================================================================
//
//  File        : mmpf_usbh_desc.h
//  Description : Header file for the USB HOST Descriptor
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_DESC_H_
#define _MMPF_USBH_DESC_H_

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#include "mmpf_usbh_core.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

extern MMP_ERR MMPF_USBH_GetDesc(   USBH_DEVICE *UsbDev,
                                    MMP_UBYTE   ubDescType,
                                    MMP_UBYTE   ubDescIndex,
                                    MMP_USHORT  usLangId,
                                    MMP_USHORT  usXferLength,
                                    void        *buf,
                                    MMP_ULONG   *ulDataLength);
extern MMP_ERR MMPF_USBH_SetConfig(USBH_DEVICE *UsbDev, MMP_UBYTE ubIndex);
extern MMP_ERR MMPF_USBH_ParseConfigDesc(MMP_UBYTE *pConfigDesc);

#endif //(USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#endif //_MMPF_USBH_DESC_H_

