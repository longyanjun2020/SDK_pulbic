#ifndef _USB_IO_MSTAR_H
#define _USB_IO_MSTAR_H

#include "sys_MsWrapper_cus_os_mem.h"
#include <drvUSBHost.h>
#include <drvAPIWrapper.h>
struct usb_driver usb_drv;

typedef struct _USB_BUS_OPS{
	int (*rcvctrlpipe)(struct usb_device *dev, u32 endpoint);
	int (*sndctrlpipe)(struct usb_device *dev, u32 endpoint);
	int (*rcvbulkpipe)(struct usb_device *dev, u32 endpoint);
	int (*sndbulkpipe)(struct usb_device *dev, u32 endpoint); 
	int (*rcvintpipe)(struct usb_device *dev, u32 endpoint);
	struct urb * (*alloc_urb)(u16 iso_packets, int mem_flags);
	void (*free_urb)(struct urb *urb); 
	void (*init_urb)(struct urb *urb);
	void (*kill_urb)(struct urb *urb);
	int (*submit_urb)(struct urb *urb, int mem_flags);
	void (*fill_bulk_urb)(struct urb *urb,struct usb_device *pDev,u32 Pipe,void *pTransferBuffer,s32 Length,usb_complete_t tCompleteFunc,void *pContext); 
	int (*register_dev)(struct usb_device *dev);
	void (*deregister)(struct usb_device *dev);
	void (*set_intfdata)(struct usb_interface *intf, void *data);
	void* (*get_intfdata)(struct usb_interface *intf);
	void* (*buffer_alloc)(struct usb_device *dev, u32 size, int mem_flags, u32 *dma);
	void (*buffer_free)(struct usb_device *dev, u32 size, void *addr, u32 dma);
	struct usb_device *(*interface_to_dev)(struct usb_interface *ptr);
}USB_BUS_OPS;

extern USB_BUS_OPS rtw_usb_bus_ops;
#endif
