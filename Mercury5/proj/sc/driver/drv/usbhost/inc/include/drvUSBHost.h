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

#ifndef __DRV_USB_H
#define __DRV_USB_H

#define USB_MAJOR      180

#include "drvCompiler.h"
#include "drvDevice.h"
#include "drvList.h"
#include "drvPCIMEM.h"
#include "drvUSB_CH9.h"
#include "drvTimer.h"
#include "drvCompletion.h"
#include <drvUsbcommon.h> // public include, RTK

enum usb_interface_condition {
	USB_INTERFACE_UNBOUND = 0,
	USB_INTERFACE_BINDING,
	USB_INTERFACE_BOUND,
	USB_INTERFACE_UNBINDING,
};

struct usb_device;

struct usb_host_endpoint {
	struct usb_endpoint_descriptor  desc;
	/* urb_list and hcpriv are new */
	struct list_head urb_list;
	void *hcpriv;

	unsigned char *extra;   /* Extra descriptors */
	int extralen;
	int enabled;
};

struct usb_host_interface {
	struct usb_interface_descriptor  desc;
	struct usb_host_endpoint *endpoint;
	int extralen;
	unsigned char *extra;   /* Extra descriptors */
};

struct usb_interface {
	struct usb_host_interface *altsetting;

	MS_S32 act_altsetting;
	MS_S32 num_altsetting;
	MS_S32 max_altsetting;

	struct usb_interface_assoc_descriptor *intf_assoc;

	enum usb_interface_condition condition; /* binding state */
	unsigned needs_binding:1;

	//struct usb_driver *driver; /* obsolete */
	struct device_s dev;
};

static __inline__ void *ms_usb_get_intfdata (struct usb_interface *intf)
{
	return ms_dev_get_drvdata (&intf->dev);
}

static __inline__ void ms_usb_set_intfdata (struct usb_interface *intf, void *data)
{
	ms_dev_set_drvdata(&intf->dev, data);
}

#define USB_MAX_INTERFACES  32
#define USB_MAXIADS		USB_MAX_INTERFACES/2

struct usb_host_config {
	struct usb_config_descriptor  desc;

	struct usb_interface *interface[USB_MAX_INTERFACES];

};

/* -------------------------------------------------------------------------- */

struct ms_usb_devmap {
	MS_U32 usb_devicemap[128 / (8*sizeof(MS_U32))];
};

struct usb_bus {
	struct device_s *controller;
	MS_S32 busnum;
	char *bus_name;

	MS_S32 devnum_next;

	struct ms_usb_devmap devmap;
	struct usb_device *root_hub;
	struct list_head bus_list;
	void *hcpriv;
	void (*release)(struct usb_bus *bus);

	int bandwidth_allocated;
	//int bandwidth_int_reqs;
	int bandwidth_isoc_reqs;
};

#define USB_MAXCHILDREN    (16)

struct usb_tt;

struct usb_device {
	MS_S32    u32DevNum;
	char    devpath [16];
	enum usb_device_state  eState;
	enum usb_device_speed  eSpeed;

	struct usb_tt  *tt;
	MS_S32    u32TTPort;
	MS_U32 toggle[2];

	/* patch elements from linux */
	struct usb_host_endpoint *ep_in[16];
	struct usb_host_endpoint *ep_out[16];

	struct usb_device *parent;
	struct usb_bus *bus;
	struct usb_host_endpoint ep0;

	struct device_s dev;

	struct usb_device_descriptor descriptor;
	struct usb_host_config *config;
	struct usb_host_config *actconfig;

	char **pRawDescriptors;

	MS_U8 level; // to restric hub topo level

	MS_S32 u32HaveLangId;
	MS_S32 u32StringLangId;

	void *hcpriv;
	char *pProductString;
	char *pManufacturerString;
	char *pSerialNumberString;

	MS_S32 u32MaxChild;
	struct usb_device *children[USB_MAXCHILDREN];

#if 1 // API wrapper
#define devnum u32DevNum
#define speed eSpeed
#define product pProductString
#endif
};

static __inline__ struct usb_device *ms_to_usb_device(struct device_s *d)
{
	const struct usb_interface *__mptr = (struct usb_interface *)(d);
	return (struct usb_device *)( (char *)__mptr - (char *)offsetof(struct usb_device,dev));

}
static __inline__ struct usb_interface *get_usb_interface(struct device_s *d)
{
	const struct usb_interface *__mptr = (struct usb_interface *)(d);
	return (struct usb_interface *)((char *)__mptr - (char *)offsetof(struct usb_interface,dev));
}

static __inline__ struct usb_device *interface_to_usbdev(struct usb_interface *ptr)
{
	const struct usb_device *__mptr = (struct usb_device *)(ptr->dev.parent);
	return (struct usb_device *)((char *)__mptr - (char *)offsetof( struct usb_device, dev));
}

extern struct usb_device *ms_usb_alloc_dev(struct usb_device *parent, struct usb_bus *bus);
extern struct usb_device *ms_usb_get_dev(struct usb_device *dev);
extern void ms_usb_put_dev(struct usb_device *dev);

extern int ms_usb_reset_device(struct usb_device *dev);

extern struct usb_interface *ms_usb_ifnum_to_if(struct usb_device *dev, int ifnum);

/*-------------------------------------------------------------------------*/
#define USB_DEVICE_ID_MATCH_INT_INFO \
  (USBDEV_MATCH_ID_INT_CLASS | USBDEV_MATCH_ID_INT_SUBCLASS | USBDEV_MATCH_ID_INT_PROTOCOL)

struct usb_driver {
	char name[16];

	int (*probe_func) (struct usb_interface *intf,
		const struct usb_device_id *id);

	void (*discon_func) (struct usb_interface *intf);

	const struct usb_device_id *match_id_table;

	struct device_driver driver;

};

static __inline__ struct usb_driver *get_usb_driver(struct device_driver *dev_ptr)
{
	const struct device_driver *__mptr = (dev_ptr);
	return (struct usb_driver *)( (char *)__mptr - (char *)offsetof(struct usb_driver,driver) );
}

extern struct ms_bus_type usb_bus_type;

extern int ms_usb_register(struct usb_driver *);
extern void ms_usb_deregister(struct usb_driver *);
extern void ms_usb_driver_release_interface(struct usb_driver *, struct usb_interface *);
extern int ms_usb_driver_claim_interface(struct usb_driver *driver,
				struct usb_interface *iface, void *priv);
const struct usb_device_id *ms_usb_match_id(struct usb_interface *,
					 const struct usb_device_id *);
extern struct usb_interface *ms_usb_get_intf(struct usb_interface *);
extern void ms_usb_put_intf(struct usb_interface *);
extern void ms_usb_forced_unbind_intf(struct usb_interface *intf);
extern void ms_unbind_marked_interfaces(struct usb_device *udev);
extern void ms_rebind_marked_interfaces(struct usb_device *udev);

#define MS_FLAG_URB_SHORT_NOT_OK        0x0001  // short reads have errors
#define MS_FLAG_URB_ISO_ASAP		0x0002  // iso-only, urb->start_frame ignored
#define MS_FLAG_URB_NO_TRANSFER_DMA_MAP 0x0004  // set the bit if urb->transfer_dma valid
#define MS_FLAG_URB_NO_SETUP_DMA_MAP    0x0008  // set the bit if urb->setup_dma valid
#define MS_FLAG_URB_ASYNC_UNLINK        0x0010  // ms_hcd_unlink_urb() returns asap
#define MS_FLAG_URB_ZERO_PACKET         0x0040  // complete bulk OUTs transfer with short packet
#define MS_FLAG_URB_NO_INTERRUPT        0x0080  // no non-error interrupt needed

#define MS_FLAG_URB_MAP_LOCAL		0x00080000	// HCD-local-memory mapping

struct usb_iso_packet_descriptor {
	U32 offset;
	U32 length;    /* expected length */
	U32 u32ActualLength;
	S32 s32Status;
};

struct urb;

typedef void (*usb_complete_t)(struct urb *);

struct urb
{
	spinlock_t lock;
	atomic_t self_count;
	atomic_t use_count;
	atomic_t reject;
	int unlinked;
	void *hcpriv;
	struct list_head urb_list;

	struct usb_device *dev;
	struct usb_host_endpoint *ep;
	unsigned u32Pipe;
	int s32Status;
	unsigned u32TransferFlags;
	void *pTransferBuffer;
	dma_addr_t tTransferDma;
	U32 u32TransferBufferLength;
	U32 u32ActualLength;
	unsigned char *pSetupPacket;
	dma_addr_t tSetupDma;
	MS_U32 u32Interval;
	void *pContext;
	usb_complete_t complete_func;
	MS_S32  WaitFlag_storage;  //added by jonas
	MS_S32  WaitFlag_count0;
	//__Test
	void              *SetDMABuf; //Note, for DMA
	MS_S32            SetDMALen;
	void              *TxDMABuf;
	MS_S32            TxDMALen;
	//__Test
#if 1 //def ENABLE_EHCI_ISOC_PIPE
	int start_frame; // almost no useful
	int number_of_packets;
	int error_count;
	struct usb_iso_packet_descriptor iso_frame_desc[0];  /* (in) ISO ONLY */
	/* NOT add any element behind */
#endif

#if 1 // API wrapper
#define transfer_flags u32TransferFlags
#define transfer_buffer pTransferBuffer
#define transfer_buffer_length u32TransferBufferLength
#define actual_length u32ActualLength
#define transfer_dma tTransferDma
#define context pContext
#define pipe u32Pipe
#define interval u32Interval
#define complete complete_func
#define status s32Status
#endif
};

static __inline__ void ms_usb_stuff_intr_urb (struct urb *urb,
	struct usb_device *pDev,
	MS_U32 u32Pipe,
	void *pTransferBuffer,
	MS_S32 u32Length,
	usb_complete_t tCompleteFunc,
	void *pContext,
	MS_S32 u32Interval)
{
	osapi_spin_lock_init(&urb->lock);
	urb->dev = pDev;
	urb->u32Pipe = u32Pipe;
	urb->pTransferBuffer = pTransferBuffer;
	urb->u32TransferBufferLength = u32Length;
	urb->complete_func = tCompleteFunc;
	urb->pContext = pContext;
	urb->u32Interval = (pDev->eSpeed == USB_HIGH_SPEED) ? (1 << (u32Interval - 1)) : u32Interval;
	urb->SetDMABuf = NULL;
	urb->SetDMALen = 0;
	urb->TxDMABuf = NULL;
	urb->TxDMALen = 0;
}

static __inline__ void ms_usb_stuff_bulk_urb (struct urb *urb,
              struct usb_device *pDev,
              MS_U32 u32Pipe,
              void *pTransferBuffer,
              MS_S32 u32Length,
              usb_complete_t tCompleteFunc,
              void *pContext)
{
	osapi_spin_lock_init(&urb->lock);
	urb->dev = pDev;
	urb->u32Pipe = u32Pipe;
	urb->pTransferBuffer = pTransferBuffer;
	urb->u32TransferBufferLength = u32Length;
	urb->complete_func = tCompleteFunc;
	urb->pContext = pContext;
	urb->SetDMABuf = NULL;
	urb->SetDMALen = 0;
	urb->TxDMABuf = NULL;
	urb->TxDMALen = 0;
}

static __inline__ void ms_usb_stuff_control_urb (struct urb *urb,
           struct usb_device *pDev,
           MS_U32 u32Pipe,
           unsigned char *pSetupPacket,
           void *pTransferBuffer,
           MS_S32 u32Length,
           usb_complete_t tCompleteFunc,
           void *pContext)
{
	osapi_spin_lock_init(&urb->lock);
	urb->dev = pDev;
	urb->u32Pipe = u32Pipe;
	urb->pSetupPacket = pSetupPacket;
	urb->pTransferBuffer = pTransferBuffer;
	urb->u32TransferBufferLength = u32Length;
	urb->complete_func = tCompleteFunc;
	urb->pContext = pContext;
	urb->SetDMABuf = NULL;
	urb->SetDMALen = 0;
	urb->TxDMABuf = NULL;
	urb->TxDMALen = 0;
}

/* urb operation rule:
 * alloc -> get -> put -> free
 */
extern struct urb *ms_usb_alloc_isoc_urb(int, int);
extern struct urb *ms_usb_alloc_urb(int mem_flags);
extern void ms_usb_kill_urb(struct urb *urb);
extern void ms_usb_free_urb(struct urb *urb);
#define usb_put_urb ms_usb_free_urb
extern struct urb *ms_usb_get_urb(struct urb *urb);
extern int ms_usb_submit_urb(struct urb *urb, int mem_flags);
extern int ms_usb_unlink_urb(struct urb *urb);

void *ms_usb_buffer_alloc (struct usb_device *dev, size_t size, int mem_flags, dma_addr_t *dma);
void ms_usb_buffer_free (struct usb_device *dev, size_t size, void *addr, dma_addr_t dma);

extern int ms_usb_control_cmd(struct usb_device *dev, unsigned int pipe,
	unsigned char request, unsigned char requesttype, unsigned short value, unsigned short index,
	void *data, unsigned short size, int timeout);
extern int ms_usb_bulk_msg(struct usb_device *usb_dev, unsigned int pipe,
	void *data, int len, int *actual_length, int timeout);


#define USB_CTRL_GET_TIMEOUT  5
#define USB_CTRL_SET_TIMEOUT  5

#define EP_CONTROL        0 // linux: 2
#define EP_BULK           1 // 3
#define EP_INTERRUPT      2 // 1
#define EP_ISOCHRONOUS    3 // 0

#define isolete_usb_maxpacket(dev, pipe, out)  (out \
        ? (dev)->pEpMaxPacketOut[usb_pipeendpoint(pipe)] \
        : (dev)->pEpMaxPacketIn [usb_pipeendpoint(pipe)] )

#define usb_pipein(ms_pipe)  ((ms_pipe) & USB_DIR_IN)
#define usb_pipeout(ms_pipe)  (!usb_pipein(ms_pipe))
#define usb_pipedevice(ms_pipe)  (((ms_pipe) >> 8) & 0x7f)
#define usb_pipeendpoint(ms_pipe)  (((ms_pipe) >> 15) & 0xf)
#define usb_pipetype(ms_pipe)  (((ms_pipe) >> 30) & 3)
#define usb_pipeint(ms_pipe)  (usb_pipetype((ms_pipe)) == EP_INTERRUPT)
#define usb_pipecontrol(ms_pipe)  (usb_pipetype((ms_pipe)) == EP_CONTROL)
#define usb_pipebulk(ms_pipe)  (usb_pipetype((ms_pipe)) == EP_BULK)
#define usb_pipetype_str(ms_pipe) (usb_pipebulk(ms_pipe) ? "bulk" : usb_pipeint(ms_pipe) ? "int" : usb_pipecontrol(ms_pipe) ? "control" : "isoc")

static inline U16
usb_maxpacket(struct usb_device *udev, int pipe, int is_out)
{
	struct usb_host_endpoint	*ep;
	unsigned			epnum = usb_pipeendpoint(pipe);

	if (is_out) {
		ep = udev->ep_out[epnum];
	} else {
		ep = udev->ep_in[epnum];
	}
	if (!ep)
		return 0;

	/* NOTE:  only 0x07ff bits are for packet size... */
	//return usb_endpoint_maxp(&ep->desc);
	return (&ep->desc)->wMaxPacketSize;
}

static __inline__ MS_U32 __pack_pipe(struct usb_device *dev, MS_U32 endpoint)
{
	return (dev->u32DevNum << 8) | (endpoint << 15);
}

#define usb_gettoggle(dev, ms_ep, out) (((dev)->toggle[out] >> (ms_ep)) & 1)
#define usb_dotoggle(dev, ms_ep, out)  ((dev)->toggle[out] ^= (1 << (ms_ep)))
#define usb_settoggle(dev, ms_ep, out, bit) ((dev)->toggle[out] = ((dev)->toggle[out] & ~(1 << (ms_ep))) | ((bit) << (ms_ep)))

#define usb_sndctrlpipe(dev,ms_ep)  (((MS_U32)EP_CONTROL << 30) | __pack_pipe(dev,ms_ep))
#define usb_rcvctrlpipe(dev,ms_ep)  (((MS_U32)EP_CONTROL << 30) | __pack_pipe(dev,ms_ep) | USB_DIR_IN)
#define usb_sndbulkpipe(dev,ms_ep)  (((MS_U32)EP_BULK << 30) | __pack_pipe(dev,ms_ep))
#define usb_rcvbulkpipe(dev,ms_ep)  (((MS_U32)EP_BULK << 30) | __pack_pipe(dev,ms_ep) | USB_DIR_IN)
#define usb_rcvintpipe(dev,ms_ep)  (((MS_U32)EP_INTERRUPT << 30) | __pack_pipe(dev,ms_ep) | USB_DIR_IN)
#define usb_sndisocpipe(dev, endpoint)	\
	((EP_ISOCHRONOUS << 30) | __pack_pipe(dev, endpoint))
#define usb_rcvisocpipe(dev, endpoint)	\
	((EP_ISOCHRONOUS << 30) | __pack_pipe(dev, endpoint) | USB_DIR_IN)

static inline struct usb_host_endpoint *
ms_usb_pipe_endpoint(struct usb_device *udev, unsigned int pipe)
{
	struct usb_host_endpoint **eps;
	eps = usb_pipein(pipe) ? udev->ep_in : udev->ep_out;
	return eps[usb_pipeendpoint(pipe)];
}

extern int ms_usb_get_descriptor(struct usb_device *ms_dev, unsigned char desctype,
  unsigned char descindex, void *buf, int size);
extern int ms_usb_get_dev_descriptor(struct usb_device *ms_dev);
extern int ms_usb_string(struct usb_device *ms_dev, int index, char *buf, size_t size);

extern int ms_usb_clear_halt(struct usb_device *ms_dev, int pipe);
extern int ms_usb_set_config(struct usb_device *ms_dev, int configuration);
extern int ms_usb_set_interface(struct usb_device *ms_dev, int ifnum, int alternate);
extern void ms_usb_set_device_state(struct usb_device *udev, enum usb_device_state new_state);

#define MSC_STRING_LEN 32

extern int ms_usb_get_current_frame_number (struct usb_device *);

/* to support class driver */
#define MS_IOBUF_SIZE   64
#endif
