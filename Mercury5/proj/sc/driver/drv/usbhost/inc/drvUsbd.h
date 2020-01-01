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

#ifndef _CORE_HCD_H_
#define _CORE_HCD_H_

#include "include/drvUSBHost.h"

#include "drvHub.h"

#define HCD_FS   0x0010
#define HCD_HS   0x0020
#define HCD_SS   0x0040
#define HCD_MEM_POOLS  5

struct st_saved_ehci_state
{
	int iPsc;
	U32 usbsts;
	U32 usbcmd;
};

struct usb_hcd {

	struct usb_bus    self;
	int  hcd_flags;
	char    product_desc[24];  /* product/vendor string */

	struct timer_list  roothub_timer;
	struct urb		*hcd_status_urb;

	int  (*ms_urb_enqueue) (struct usb_hcd *hcd, struct urb *urb, int mem_flags);
	int  (*ms_urb_dequeue) (struct usb_hcd *hcd, struct urb *urb, int status);

	/* Check root hub registered */
	unsigned        roothub_registered:1;
	/* for the new root-hub polling mechanism. */
	unsigned        hcd_poll_pending:1;
	unsigned        rh_disconn:1;

	int      ehci_irq;
	U32      *uhc_regs;
	struct device_s    *controller;
	struct ms_mem_pool    *pool [HCD_MEM_POOLS];

	int      state;

	/* new to collect hcd related variables */
	U32 host_id;
	S32 USBWaitFlg; // OS wait flag
	U32 badDeviceCnt; // for Philips mp3 device
	BOOL isBadDevice; // backward compatible
	BOOL isBadDeviceRH; // bad device on the root hub
	BOOL isRootHubPortReset; // backward compatible, may be omitted
	BOOL isFSmode;
	struct list_head *phub_event;
	struct list_head tt_clear_list;
	struct st_saved_ehci_state saved_ehci_state;
	U32     ms_flag;
	/* ms_flag bit16 ~ bit31 for sw frame index  */
#define MS_FLAG_SW_FRM_IDX	(1<<2)
};

/* define usb_hcd.state */
#define  __ACTIVE    0x01
#define  __SLEEPY    0x02
#define  __SUSPEND    0x04
#define  __TRANSIENT    0x80

#define  HCD_STATE_HALT    0
#define  HCD_STATE_RUNNING  (__ACTIVE)
#define  HCD_STATE_READY    (__ACTIVE|__SLEEPY)
#define  HCD_STATE_QUIESCING  (__SUSPEND|__TRANSIENT|__ACTIVE)
#define  HCD_STATE_RESUMING  (__SUSPEND|__TRANSIENT)
#define  HCD_STATE_SUSPENDED  (__SUSPEND)

#define  HCD_IS_RUNNING(state) ((state) & __ACTIVE)
#define  HCD_IS_SUSPENDED(state) ((state) & __SUSPEND)

/* drvUsbd.c */
extern int ms_hcd_submit_urb (struct urb *, int);
extern int ms_hcd_unlink_urb (struct urb *, int);
extern void ms_usb_hcd_flush_endpoint(struct usb_device *, struct usb_host_endpoint *);
extern void ms_hcd_endpoint_disable (struct usb_device *, struct usb_host_endpoint *);
extern int ms_usb_hcd_link_urb_to_ep(struct usb_hcd *, struct urb *);
extern void ms_usb_hcd_unlink_urb_from_ep(struct usb_hcd *, struct urb *);
extern int ms_usb_hcd_check_unlink_urb(struct usb_hcd *, struct urb *, int);
extern void ms_usb_hcd_giveback_urb (struct urb *urb);
extern void ms_usb_bus_init (struct usb_bus *bus);
extern void ms_hcd_poll_rh_status(struct usb_hcd *pHcd);
extern int ms_hcd_get_frame_number(struct usb_device *);

/* drvHcdBuf.c */
int ms_hcd_buffer_create (struct usb_hcd *hcd);
void ms_hcd_buffer_destroy (struct usb_hcd *hcd);
void *ms_hcd_buffer_alloc (struct usb_bus *bus, size_t size,
	int mem_flags, dma_addr_t *dma);
void ms_hcd_buffer_free (struct usb_bus *bus, size_t size,
	void *addr, dma_addr_t dma);

#define usb_snddefctrl(dev)    (((U32)EP_CONTROL << 30))
#define usb_rcvdefctrl(dev)    (((U32)EP_CONTROL << 30) | USB_DIR_IN)

/*-------------------------------------------------------------------------*/

#define ms_CalcBitTime(bytes)  (7 * 8 * bytes / 6)  /* with ¾ã¼Æ truncation */

#define NS_2_US(ns)  ((ns + 500L) / 1000L)

#define USB2_EHCI_DELAY  5       // (ns)
#define EHCI_BW_DELAY    1000L   // (ns)
#define HUB_BW_LS_SETUP  333L    // (ns)

/* revised base on linux code */
#define HIGHSPEED_NS(bytes)  ( ((55 * 8 * 2083) \
	+ (2083UL * (3 + ms_CalcBitTime (bytes))))/1000 \
	+ USB2_EHCI_DELAY)

#define HIGHSPEED_NS_ISO(bytes)  ( ((38 * 8 * 2083) \
	+ (2083UL * (3 + ms_CalcBitTime (bytes))))/1000 \
	+ USB2_EHCI_DELAY)

#define HIGHSPEED_US(bytes) NS_2_US(HIGHSPEED_NS(bytes))
#define HIGHSPEED_US_ISO(bytes) NS_2_US(HIGHSPEED_NS_ISO(bytes))

extern int ms_usb_calc_bus_time (int, int, int, int);

/*-------------------------------------------------------------------------*/

#define Req_SetHubFeature     (0x2000 | USB_REQ_SET_FEATURE)
#define Req_SetPortFeature    (0x2300 | USB_REQ_SET_FEATURE)
#define Req_GetHubDescriptor  (0xa000 | USB_REQ_GET_DESCRIPTOR)
#define Req_GetHubStatus      (0xa000 | USB_REQ_GET_STATUS)
#define Req_GetPortStatus     (0xa300 | USB_REQ_GET_STATUS)
#define Req_ClearHubFeature   (0x2000 | USB_REQ_CLEAR_FEATURE)
#define Req_ClearPortFeature  (0x2300 | USB_REQ_CLEAR_FEATURE)

#define ReqType_Device \
	((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_DEVICE)<<8)
#define ReqType_DeviceOut \
	((USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_DEVICE)<<8)

#define ReqType_Interface \
	((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)<<8)

#define ReqType_Endpoint \
	((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)<<8)
#define ReqType_EndpointOut \
	((USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)<<8)

#define usb_endpoint_dir(ep_dir)  (!((ep_dir) & USB_DIR_IN))
/*-------------------------------------------------------------------------*/
/* drvUsbd.c */
extern int ms_usb_register_bus (struct usb_bus *);
extern void ms_usb_deregister_bus (struct usb_bus *);
extern int ms_register_root_hub (struct usb_hcd *hcd);
extern int ms_create_cpe_hcd(struct cpe_dev *dev);
extern void ms_usb_hcd_cpe_ehci_remove (struct usb_hcd *pHcd);

extern struct list_head usb_bus_list;

/* drvUSBEntry.c */
extern void ms_InitUSBIntr_EX(struct usb_hcd *, int);

#endif
