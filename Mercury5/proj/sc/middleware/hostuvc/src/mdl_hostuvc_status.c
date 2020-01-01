#include <drvErrno.h>
#include <drvUSBHost.h>
#include <drvAPIWrapper.h>
#include "mdl_hostuvc_video.h"

static U8 _gstatusbuffer[UVC_MAX_STATUS_SIZE];

/* --------------------------------------------------------------------------
 * Status interrupt endpoint
 */
static void uvc_event_streaming(struct uvc_device *dev, U8 *data, int len)
{
	if (len < 3) {
		diag_printf("Invalid streaming status event "
				"received.\n");
		return;
	}

	if (data[2] == 0) {
		if (len < 4)
			return;
		diag_printf("Button (intf %u) %s len %d\n",
			data[1], data[3] ? "pressed" : "released", len);
		//uvc_input_report_key(dev, KEY_CAMERA, data[3]);
	} else {
		diag_printf("Stream %u error event %02x %02x "
			"len %d.\n", data[1], data[2], data[3], len);
	}
}

static void uvc_event_control(struct uvc_device *dev, U8 *data, int len)
{
	char *attrs[3] = { "value", "info", "failure" };

	if (len < 6 || data[2] != 0 || data[4] > 2) {
		diag_printf("Invalid control status event "
				"received.\n");
		return;
	}

	diag_printf("Control %u/%u %s change len %d.\n",
		data[1], data[3], attrs[data[4]], len);
}

static void uvc_status_complete(struct urb *urb)
{
	struct uvc_device *dev = urb->context;
	int len, ret;

	switch (urb->s32Status) {
	case 0:
		break;

	case -ENOENT:		/* usb_kill_urb() called. */
	case -ECONNRESET:	/* usb_unlink_urb() called. */
	case -ESHUTDOWN:	/* The endpoint is being disabled. */
	case -MS_ERR_PROTOCAL:	/* Device is disconnected (reported by some
				 * host controller). */
		return;

	default:
		diag_printf("Non-zero status (%d) in status "
			"completion handler.\n", urb->status);
		return;
	}

	len = urb->actual_length;
	if (len > 0) {
		switch (dev->status[0] & 0x0f) {
		case UVC_STATUS_TYPE_CONTROL:
			uvc_event_control(dev, dev->status, len);
			break;

		case UVC_STATUS_TYPE_STREAMING:
			uvc_event_streaming(dev, dev->status, len);
			break;

		default:
			diag_printf("Unknown status event "
				"type %u.\n", dev->status[0]);
			break;
		}
	}

	/* Resubmit the URB. */
	urb->interval = dev->int_ep->desc.bInterval;
	if ((ret = usb_submit_urb(urb, 0)) < 0) {
		diag_printf("Failed to resubmit status URB (%d).\n",
			ret);
	}
}

int uvc_status_init(struct uvc_device *dev)
{
	struct usb_host_endpoint *ep = dev->int_ep;
	unsigned int pipe;
	int interval;

	diag_printf("[J] %s++\n", __FUNCTION__);
	if (ep == NULL)
		diag_printf("[J] ep NULL\n");
	if (ep == NULL)
		return 0;

	//uvc_input_init(dev);

	dev->status = _gstatusbuffer;
	memset(dev->status, 0, UVC_MAX_STATUS_SIZE);
	if (dev->status == NULL)
		return -ENOMEM;

	dev->int_urb = usb_alloc_urb(0, 0);
	if (dev->int_urb == NULL) {
		return -ENOMEM;
	}

	pipe = usb_rcvintpipe(dev->udev, ep->desc.bEndpointAddress);

	/* For high-speed interrupt endpoints, the bInterval value is used as
	 * an exponent of two. Some developers forgot about it.
	 */
	interval = ep->desc.bInterval;
	// FIXME:
	#if 0
	if (interval > 16 && dev->udev->eSpeed == USB_HIGH_SPEED &&
	    (dev->quirks & UVC_QUIRK_STATUS_INTERVAL))
		interval = fls(interval) - 1;
	#endif

	usb_fill_int_urb(dev->int_urb, dev->udev, pipe,
		dev->status, UVC_MAX_STATUS_SIZE, uvc_status_complete,
		dev, interval);

	return 0;
}

void uvc_status_cleanup(struct uvc_device *dev)
{
	diag_printf("[J] %s++\n", __FUNCTION__);

	usb_kill_urb(dev->int_urb);
	usb_free_urb(dev->int_urb);
	//uvc_input_cleanup(dev);
}

int uvc_status_start(struct uvc_device *dev)
{
	if (dev->int_urb == NULL)
		return 0;

	diag_printf("[J] %s++\n", __FUNCTION__);
	return usb_submit_urb(dev->int_urb, 0);
}
