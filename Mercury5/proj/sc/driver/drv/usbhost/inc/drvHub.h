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

#ifndef _CORE_HUB_H_
#define _CORE_HUB_H_

#include "include/drvUSBHost.h"

#include "drvUsbHostConfig.h"

/* CPE device's data Sturcture */
struct cpe_dev {
	struct device_s dev;
	MS_U32  devid; //device id
	MS_U32 uhcbase; //device base address of memory mapping I/O
	MS_U32 utmibase; // new
	MS_U32 usbcbase; // new
	cyg_uint64 dma_mask;
	InterruptNum intNum;
	char *bus_name;
	char *product_desc;
	struct list_head *pHubEvent;
};

#define USB_RT_HUB  (USB_TYPE_CLASS | USB_RECIP_DEVICE) // root hub
#define USB_RT_PORT  (USB_TYPE_CLASS | USB_RECIP_OTHER) // root hub port

#define HUB_CLEAR_TT_BUFFER             8 // TT buffer clear

#define C_HUB_LOCAL_POWER               0 // hub power operation
#define C_HUB_OVER_CURRENT              1 // hub over-current operation

#define HUB_CHAR_LPSM                   0x0003
#define HUB_CHAR_COMPOUND               0x0004
#define HUB_CHAR_OCPM                   0x0018
#define HUB_CHAR_TTTT                   0x0060
#define HUB_CHAR_PORTIND                0x0080

#define USB_PORT_FEAT_ENABLE            1 // port bitmap port enable
#define USB_PORT_FEAT_SUSPEND           2 // port bitmap port suspend
#define USB_PORT_FEAT_OVER_CURRENT      3 // port bitmap port over current
#define USB_PORT_FEAT_RESET             4 // port bitmap port reset
#define USB_PORT_FEAT_POWER             8 // port bitmap port power
#define USB_PORT_FEAT_C_CONNECTION      16 // port clear bitmap clear port connection
#define USB_PORT_FEAT_C_ENABLE          17 //  port clear bitmap clear port enable
#define USB_PORT_FEAT_C_SUSPEND         18 // port clear bitmap clear port suspend
#define USB_PORT_FEAT_C_OVER_CURRENT    19 // port clear bitmap clear port over current
#define USB_PORT_FEAT_C_RESET           20 // port clear bitmap clear port reset

#define USB_PORT_STAT_CONNECTION        0x0001 // port state connection
#define USB_PORT_STAT_ENABLE            0x0002 // port state enable
#define USB_PORT_STAT_SUSPEND           0x0004 // port state suspend
#define USB_PORT_STAT_OVERCURRENT       0x0008 // port state over current
#define USB_PORT_STAT_RESET             0x0010 // port state reset
#define USB_PORT_STAT_POWER             0x0100 // port state power
#define USB_PORT_STAT_LOW_SPEED         0x0200 // port state low speed
#define USB_PORT_STAT_HIGH_SPEED        0x0400 // port state high speed

#define USB_PORT_STAT_C_CONNECTION      0x0001 // port clear port connection
#define USB_PORT_STAT_C_ENABLE          0x0002 // port clear port enable
#define USB_PORT_STAT_C_SUSPEND         0x0004 // port clear port suspend
#define USB_PORT_STAT_C_OVERCURRENT     0x0008 // port clear port over current
#define USB_PORT_STAT_C_RESET           0x0010 // port clear port reset

struct ms_usb_port_status {                 // port status
	MS_U16 wPortStatus;
	MS_U16 wPortChange;
} __attribute__((packed));

struct ms_usb_hub_status {                  // hub status
	MS_U16 wHubStatus;
	MS_U16 wHubChange;
} __attribute__((packed));

#define HUB_STATUS_LOCAL_POWER  0x0001
#define HUB_STATUS_OVERCURRENT  0x0002
#define HUB_CHANGE_LOCAL_POWER  0x0001
#define HUB_CHANGE_OVERCURRENT  0x0002


#define USB_DT_HUB      (USB_TYPE_CLASS | 0x09)             // hub descriptor
#define USB_DT_HUB_NONVAR_SIZE    7

struct usb_hub_descriptor {
	MS_U8  bDescLength;
	MS_U8  bDescriptorType;
	MS_U8  bNbrPorts;
	MS_U16 wHubCharacteristics;
	MS_U8  bPwrOn2PwrGood;
	MS_U8  bHubContrCurrent;
	MS_U8  DeviceRemovable[(USB_MAXCHILDREN + 1 + 7) / 8 + 1]; // add 1 to prevent warning message
	MS_U8  PortPwrCtrlMask[(USB_MAXCHILDREN + 1 + 7) / 8 + 1];
} __attribute__((packed));

struct usb_device;

struct usb_tt {
	struct usb_device  *hub;
	int      multi;
	MS_U32   think_time;

	spinlock_t    lock;
	struct list_head  clear_list;
};

struct usb_tt_clear {
	struct list_head  clear_list;
	MS_U32    tt;
	MS_U16      devinfo;
};

extern void ms_usb_hub_tt_clear_buffer (struct usb_device *ms_dev, int ms_pipe);

struct usb_hub {
	struct usb_interface  *intf;
	struct urb    *urb;

	char      (*buffer)[(USB_MAXCHILDREN + 1 + 7) / 8];
	dma_addr_t    buffer_dma;
	union {
		struct ms_usb_hub_status  hub;
		struct ms_usb_port_status  port;
	}status;  // shared by hub and port

	int      error;
	int      nerrors;

	struct list_head  event_list;

	U32 busy_bits[1];
	U32 change_bits[1];
	U32 removed_bits[1];

	struct usb_hub_descriptor descriptor;
	//struct semaphore  khubd_sem;
	struct usb_tt    tt;
	MS_U32	limited_power:1;
	MS_U32	disconnected:1;
};

#define HUB_RESET_TRIES			5
#define HUB_PROBE_TRIES			3
#define HUB_ROOT_RESET_TIME		50
#define HUB_SHORT_RESET_TIME	10
#define HUB_BH_RESET_TIME		50
#define HUB_LONG_RESET_TIME		200
#define HUB_RESET_TIMEOUT		500
#define HUB_DEBOUNCE_STEP		100 //25
#define HUB_DEBOUNCE_STABLE		2 //4// # of counts

struct s_vPortRange
{
	MS_U32 vPortDevStart;
	MS_U32 vPortDevEnd;
};

struct stConnDevList
{
	struct usb_device *connDev;
};

/* root hub related variables */
struct s_gVar4UsbPort
{
	/* declaration initialized */
	char name[24];
	MS_U8 hostid;
	struct s_vPortRange vPortRange;
	char bus_name[24];
	char product_desc[24];
	MS_U8 *u8pHubStackBuffer;
	char usb_mutex_name[24];
	struct device_driver platform_device_driver;

	/* the following items not initialized */
	struct list_head hub_event; // to support multiple root hub
	struct cpe_dev cpe_ehci_dev;
	struct usb_hcd *p_UsbHcd; // for MDrv_UsbDeviceConnect()
	struct stConnDevList arConnDev[USB_MAXCHILDREN];
	MS_S32 _s32MutexUSB; // for critical section
	int pid; // for Task delete
	MS_BOOL taskRunning; // for Task delete
	MS_BOOL taskFinish; // for Task delete
	MS_BOOL bPark_ok; // for STR
};

#ifdef ENABLE_XHC_COMPANION
struct xhc_comp {
	MS_U8   port_index;
	MS_U32  xhci_port_addr;
	MS_U32  u3top_base;
	MS_U32  u3phy_A_base;
	MS_U32  u3phy_D_base;
};
#endif

struct s_RegMap
{
	MS_U32 iFlag;
	MS_U32 baseUTMI;
	MS_U32 baseUHC;
	MS_U32 baseUSBC;
	MS_U32 baseUSBBC;
	InterruptNum uhcIRQ;
	InterruptNum usbcIRQ;
#ifdef ENABLE_XHC_COMPANION
	struct xhc_comp xhci;
#endif
};

struct s_UsbcInfo
{
	MS_U8 portNum;
	MS_U8 int_pol;
	MS_U16 intEn;
	MS_U16 intSts;
	MS_U8 eventFlag;
	MS_U8 eventType;
};

struct s_ChipUsbHostDef
{
	MS_U8 chipID;
	char name[24];
	MS_U8 nRootHub;
	struct s_RegMap reg[NUM_OF_ROOT_HUB];
	struct s_gVar4UsbPort *p_roothub[NUM_OF_ROOT_HUB];
	struct s_UsbcInfo usbc_ip[NUM_OF_ROOT_HUB];
	MS_U8 u8Park;
};

/* drvHub.c */
extern int ms_hub_poll(struct s_gVar4UsbPort *pRootHub);

#endif
