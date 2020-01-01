//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
//Copyright (C) 2008 MStar  All Rights Reserved.

/*! \file  drvUSBHwCtl.h
        \brief  Functions for accessing the USB hardware.


 \n\b History:
        \n\b Date: 2008/11/20
        \n\b Author: Colin Tsai
        \n\b Reason: Create
        \n
*/
//=============================================================================

#ifndef DRV_USB_HWCTL_H
#define DRV_USB_HWCTL_H

#include "drvUsbHostConfig.h"
#include "drvUsbd.h"

#define usb_readb(addr)    (*(volatile unsigned char *) (addr))
#define usb_readw(addr)    (*(volatile unsigned short *) (addr))
#define usb_readl(addr)    (*(volatile unsigned int *) (addr))
#define usb_writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
#define usb_writew(b,addr) ((*(volatile unsigned short *) (addr)) = (b))
#define usb_writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))

#define HOST20_USBCMD_FrameListSize_1024                  0x00
#define HOST20_USBCMD_FrameListSize_512                   0x01
#define HOST20_USBCMD_FrameListSize_256                   0x02

#define HOST20_Enable                  0x01
#define HOST20_Disable                 0x00

#define HOST20_USBEVENT_USB_CDC_CTRL                      0x100
#define HOST20_USBEVENT_USB_CDC_BUILK_IN                  0x80
#define HOST20_USBEVENT_USB_CDC_BUILK_OUT                 0x40
#define HOST20_USBINTR_IntOnAsyncAdvance                  0x20
#define HOST20_USBINTR_SystemError                        0x10
#define HOST20_USBINTR_FrameRollover                      0x08
#define HOST20_USBINTR_PortChangeDetect                   0x04
#define HOST20_USBINTR_USBError                           0x02
#define HOST20_USBINTR_CompletionOfTransaction            0x01
#define USBWAITEVENTS   (HOST20_USBINTR_CompletionOfTransaction|HOST20_USBINTR_USBError|HOST20_USBINTR_PortChangeDetect|HOST20_USBINTR_SystemError)

#define USBCINTR_IDChange                                 0x08
#define USBCINTR_BValidChange                             0x04
#define USBCINTR_AValidChange                             0x02
#define USBCINTR_VBusValidChange                          0x01

extern void ms_ehci_interrupt_enable (struct usb_hcd *hcd, int str_on);
extern void ms_ehci_interrupt_disable (struct usb_hcd *hcd);
extern void ms_init_usbc_intr(MS_U8 p);
extern void ms_RH_force_FSmode(struct usb_hcd *, int);
extern void ms_ResetMstarUsb(struct usb_hcd *);
extern BOOL ms_RoothubPortConnected(struct usb_hcd *);
extern BOOL ms_RoothubPortConnectChg(struct usb_hcd *);
extern BOOL ms_RoothubPortEnabled(struct usb_hcd *);
extern BOOL ms_isHcdRunning(struct usb_hcd *);
extern BOOL ms_isHcdHighSpeed(struct usb_hcd *);
extern void ms_forceHcdRun(struct usb_hcd *);
extern void ms_roothub_disconn_reinit(struct usb_hcd *);
extern void ms_bus_reset_adjust_eye_pattern(U32 u32RegUTMI, U8 mode);
extern void ms_adjust_EOF1_byspeed(struct usb_hcd *pHcd, U32 u32Speed);
extern void ms_adjust_hub_driving_timing(U32 u32RegUTMI, U32 u32Speed);

#ifdef _USB_ENABLE_BDMA_PATCH
extern void m_BDMA_write(unsigned int, unsigned int);
extern void set_64bit_OBF_cipher(void);
extern int get_64bit_OBF_cipher(void);
#endif

#ifdef ENABLE_XHC_COMPANION
//------- xHCI --------
#define PORT_PE                 (1 << 1)
#define PORT_PLS_MASK           (0xf << 5)
#define PORT_LINK_STROBE        (1 << 16)

#define XHCI_PORT_RO    ((1<<0) | (1<<3) | (0xf<<10) | (1<<30))
#define XHCI_PORT_RWS   ((0xf<<5) | (1<<9) | (0x3<<14) | (0x7<<25))

#define USB_SS_PORT_LS_SS_DISABLED      0x0080
#define USB_SS_PORT_LS_RX_DETECT        0x00a0

void xhci_ppc(struct xhc_comp *xhci, int bOn);
void xhci_enable_clock(void);
void xhci_ssport_set_state(struct xhc_comp *xhci, int bOn);
//--------------------
#endif
#endif  //#define DRV_USB_HWCTL_H
