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

#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "drvOSAPI.h"
#include "drvList.h"

#define DEVICE_NAME_SIZE  24
#define BUS_ID_SIZE       24

struct device_s;

struct device_driver {
	char   name[DEVICE_NAME_SIZE];
	struct ms_bus_type    * bus;

	struct list_head  bus_list; // driver's bus's drivers list, added by Pliauo
	struct list_head  devices;  // driver's devices

	int  (*probe)  (struct device_s * dev);
	int  (*remove)  (struct device_s * dev);
};

// FIXME:
struct device_s {

	struct list_head node;        // node in device's parent's children list
	struct list_head bus_list;    // node in device's bus's list
	struct list_head driver_list; // node in device's driver's list
	struct list_head children;    // list of child devices

	struct device_s   *parent;

	atomic_t   dev_refcnt;
	char  dev_name[DEVICE_NAME_SIZE];
	char  bus_id[BUS_ID_SIZE];        // position on parent bus

	struct ms_bus_type  *bus_type;   // type of device bus
	struct device_driver *driver;     // this device allocated driver
	void   *driver_data;

	cyg_uint64    *dma_mask;          // for support dma device

	void  (*release_func)(struct device_s *dev);
};

static __inline__ int
ms_device_is_registered(struct device_s *dev)
{
	return (dev->driver != NULL);
}

static __inline__ void
ms_dev_set_drvdata (struct device_s *dev, void *data)
{
	dev->driver_data = data;
}

static __inline__ void *
ms_dev_get_drvdata (struct device_s *dev)
{
	return dev->driver_data;
}

extern void ms_device_initialize(struct device_s *dev);

static __inline__ struct device_s *ms_get_device(struct device_s *dev_ptr)
{
	osapi_atomic_inc(&dev_ptr->dev_refcnt);
	return dev_ptr;
}

struct usb_device_id {
	MS_U16    match_id_flags;

	MS_U16    idVendor;
	MS_U16    idProduct;
	MS_U16    bcdDevice_lo;
	MS_U16    bcdDevice_hi;

	MS_U8    bDeviceClass;
	MS_U8    bDeviceSubClass;
	MS_U8    bDeviceProtocol;

	MS_U8    bInterfaceClass;
	MS_U8    bInterfaceSubClass;
	MS_U8    bInterfaceProtocol;

	MS_U32  match_id_info;
};

struct ms_bus_type {
	struct list_head  drivers_list;
	struct list_head  devices_list;

	int (*match_func)(struct device_s * dev, struct device_driver * drv);
};

#define USBDEV_MATCH_ID_VENDOR        0x0001
#define USBDEV_MATCH_ID_PRODUCT       0x0002
#define USBDEV_MATCH_ID_DEV_LO        0x0004
#define USBDEV_MATCH_ID_DEV_HI        0x0008
#define USBDEV_MATCH_ID_DEV_CLASS     0x0010
#define USBDEV_MATCH_ID_DEV_SUBCLASS  0x0020
#define USBDEV_MATCH_ID_DEV_PROTOCOL  0x0040
#define USBDEV_MATCH_ID_INT_CLASS     0x0080
#define USBDEV_MATCH_ID_INT_SUBCLASS  0x0100
#define USBDEV_MATCH_ID_INT_PROTOCOL  0x0200

/* drvBus.c */
extern int  ms_driver_register(struct device_driver * drv);
extern void ms_driver_unregister(struct device_driver * drv);
extern void ms_device_unregister(struct device_s * dev);
extern int  ms_device_add(struct device_s *dev);
extern void ms_device_del(struct device_s *dev);
extern int ms_device_attach(struct device_s * dev);
extern void ms_device_bind_driver(struct device_s *);
extern int  ms_bus_add_device(struct device_s * dev);
extern int  ms_bus_add_driver(struct device_driver * drv);
extern void ms_bus_remove_driver(struct device_driver * drv);
extern void ms_bus_remove_device(struct device_s * dev);
extern void ms_device_release_driver(struct device_s *ms_gdev);
#endif
