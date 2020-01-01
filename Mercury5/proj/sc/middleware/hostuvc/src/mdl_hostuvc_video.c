#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include <drvUSBHost.h>
#include <drvAPIWrapper.h>
#include <drvErrno.h>
#include <drvKernel.h>//for min(),INT_MAX
#include "mdl_hostuvc_video.h"
#include "mdl_hostuvc.h"
#include "os_wrap.h"
#include "mmpf_hif.h"
#include "mmpf_usbh_ctl.h"

extern UVCH_XFER_CTL    uvch_xfer_ctl;

#if 0 // JF debug
static void Dump_cur_altsetting(struct usb_host_interface *cur_alt)
{
    diag_printf("\t\tH:intf:bInterfaceNumber %d\n", cur_alt->desc.bInterfaceNumber);
    diag_printf("\t\tH:intf:bAlternateSetting %d\n", cur_alt->desc.bAlternateSetting);
    diag_printf("\t\tH:intf:bNumEndpoints %d\n", cur_alt->desc.bNumEndpoints);
    diag_printf("\t\tH:intf:(C,S,P) (%x,%x,%x)\n",
        cur_alt->desc.bInterfaceClass,
        cur_alt->desc.bInterfaceSubClass,
        cur_alt->desc.bInterfaceProtocol);
    diag_printf("\t\tH:endp %p\n", cur_alt->endpoint);
    if (cur_alt->endpoint) {
        diag_printf("\t\tH:endp enable %x\n", (&cur_alt->endpoint[0])->enabled);
        diag_printf("\t\tH:endp BW %d\n", (&cur_alt->endpoint[0])->desc.wMaxPacketSize);
    }
    diag_printf("\t\tH:extralen %d\n", cur_alt->extralen);
    diag_printf("\t\tH:extra %p\n", cur_alt->extra);
}

static void Dump_altsetting(struct usb_host_interface *altsetting, int num)
{
    struct  usb_host_interface *cur_alt;
    int i;

    for (i = 0; i < num; i++) {
        cur_alt = &altsetting[i];
        Dump_cur_altsetting(cur_alt);
    }
}

static void Dump_interface_content(struct usb_interface *intf, int intfnum)
{
    diag_printf("====== %s %p(%d) ======\n",
         __FUNCTION__, intf, intfnum);
    diag_printf("\tI:act_altsetting %d\n", intf->act_altsetting);
    diag_printf("\tI:num_altsetting %d\n", intf->num_altsetting);
    diag_printf("\tI:max_altsetting %d\n", intf->max_altsetting);
    diag_printf("\tI:intf_assoc %p\n", intf->intf_assoc);
    //diag_printf("\tI:driver %p\n", intf->driver);
    diag_printf("\tI:dev_s %p\n", &intf->dev);
    diag_printf("\tI:dev_refcnt %d\n", atomic_read(&intf->dev.dev_refcnt));
    diag_printf("\tI:dev_name %s\n", intf->dev.dev_name);
    diag_printf("= active usb_host_interface ==\n");
    Dump_cur_altsetting(&intf->altsetting[0]);
    Dump_cur_altsetting(&intf->altsetting[3]);
    diag_printf("= end of usb_host_interface ==\n");
    diag_printf("====== end of %s ======\n", __FUNCTION__);
}

static void Dump_configure_content(struct usb_device *udev)
{
    struct usb_host_config *cp = NULL;
    int i;

    diag_printf("====== %s ======\n", __FUNCTION__);
    diag_printf("config # = %d\n", udev->descriptor.bNumConfigurations);
    if (udev->descriptor.bNumConfigurations != 1) {
        return;
    }
    cp = &udev->config[0];
    diag_printf("interface # = %d\n", cp->desc.bNumInterfaces);
    for (i = 0; i < cp->desc.bNumInterfaces; i++) {
        struct usb_interface *intf = cp->interface[i];

        diag_printf("I[%d]:act_altsetting %d\n", i, intf->act_altsetting);
        diag_printf("I:num_altsetting %d\n", intf->num_altsetting);
        diag_printf("I:max_altsetting %d\n", intf->max_altsetting);
        diag_printf("I:intf_assoc %p\n", intf->intf_assoc);
        //diag_printf("I:driver %p\n", intf->driver);
        diag_printf("I:dev_refcnt %d\n", atomic_read(&intf->dev.dev_refcnt));
        diag_printf("I[%d]:dev_name %s\n", i, intf->dev.dev_name);
        diag_printf("= usb_host_interface #%d==\n", intf->num_altsetting);
        Dump_altsetting(intf->altsetting, intf->num_altsetting);
        diag_printf("= end of usb_host_interface ==\n");
    }
    diag_printf("====== end of %s ======\n", __FUNCTION__);
}

static void Dump_video_stream_setting(struct uvc_streaming_control *ctrl)
{

#if(1)
    diag_printf("====== start Dump_video_stream_setting ======\r\n");
    diag_printf("bmHint : %u\r\n",ctrl->bmHint);
    diag_printf("bFormatIndex : %u\r\n",ctrl->bFormatIndex);
    diag_printf("bFrameIndex : %u\r\n",ctrl->bFrameIndex);
    diag_printf("dwFrameInterval : %u\r\n",ctrl->dwFrameInterval);
    diag_printf("wKeyFrameRate : %u\r\n",ctrl->wKeyFrameRate);
    diag_printf("wPFrameRate : %u\r\n",ctrl->wPFrameRate);
    diag_printf("wCompQuality : %u\r\n",ctrl->wCompQuality);
    diag_printf("wCompWindowSize : %u\r\n",ctrl->wCompWindowSize);
    diag_printf("wDelay : %u\r\n",ctrl->wDelay);
    diag_printf("dwMaxVideoFrameSize : %u\r\n",ctrl->dwMaxVideoFrameSize);
    diag_printf("dwMaxPayloadTransferSize : %u\r\n",ctrl->dwMaxPayloadTransferSize);
    diag_printf("dwClockFrequency : %u\r\n",ctrl->dwClockFrequency);
    diag_printf("bmFramingInfo : %u\r\n",ctrl->bmFramingInfo);
    diag_printf("bPreferedVersion : %u\r\n",ctrl->bPreferedVersion);
    diag_printf("bMinVersion : %u\r\n",ctrl->bMinVersion);
    diag_printf("bMaxVersion : %u\r\n",ctrl->bMaxVersion);
    diag_printf("====== end of Dump_video_stream_setting ======\r\n");
#endif
    return;
}
#endif

/* ------------------------------------------------------------------------
 * UVC Controls
 */

/* be sure not input odd pointer */
static inline U16 le16_to_cpup(const void *_ptr)
{
    const U8 *ptr = _ptr;
    return ptr[0] | (ptr[1] << 8);
}

#if 0
static inline U32 le32_to_cpup(const void *_ptr)
{
    const U8 *ptr = _ptr;
    return ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
}
#endif

inline U32 get_unaligned_le32(const void *_ptr)
{
    const U8 *ptr = _ptr;
    return ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
}

inline void put_unaligned_le32(U32 val, void *_ptr)
{
    U8 *ptr = _ptr;
    *ptr++ = val;
    *ptr++ = val >>  8;
    *ptr++ = val >> 16;
    *ptr++ = val >> 24;
}

static int __uvc_query_ctrl(struct uvc_device *dev, U8 query, U8 unit,
            U8 intfnum, U8 cs, void *data, U16 size,
            int timeout)
{
    U8 type = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
    unsigned int pipe;

    pipe = (query & 0x80) ? usb_rcvctrlpipe(dev->udev, 0)
                  : usb_sndctrlpipe(dev->udev, 0);
    type |= (query & 0x80) ? USB_DIR_IN : USB_DIR_OUT;

    return usb_control_msg(dev->udev, pipe, query, type, cs << 8,
            unit << 8 | intfnum, data, size, timeout);
}


static int uvc_get_video_ctrl(struct uvc_streaming *stream,
    struct uvc_streaming_control *ctrl, int probe, U8 query)
{
    U8 *data;
    U16 size;
    int ret = 0;
#if 0
    size = stream->dev->uvc_version >= 0x0110 ? 34 : 26;
    #if 0
    if ((stream->dev->quirks & UVC_QUIRK_PROBE_DEF) &&
            query == UVC_GET_DEF)
        return -EIO;
    #endif

    data = MsAllocateMem(size);
    if (data == NULL)
        return -ENOMEM;

    ret = __uvc_query_ctrl(stream->dev, query, 0, stream->intfnum,
        probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
        size, uvc_timeout_param);

    if ((query == UVC_GET_MIN || query == UVC_GET_MAX) && ret == 2) {
        /* Some cameras, mostly based on Bison Electronics chipsets,
         * answer a GET_MIN or GET_MAX request with the wCompQuality
         * field only.
         */
        diag_printf("UVC non "
            "compliance - GET_MIN/MAX(PROBE) incorrectly "
            "supported. Enabling workaround.\n");
        memset(ctrl, 0, sizeof *ctrl);
        ctrl->wCompQuality = le16_to_cpup((U16 *)data);
        ret = 0;
        goto out;
    } else if (query == UVC_GET_DEF && probe == 1 && ret != size) {
        /* Many cameras don't support the GET_DEF request on their
         * video probe control. Warn once and return, the caller will
         * fall back to GET_CUR.
         */
        diag_printf("UVC non "
            "compliance - GET_DEF(PROBE) not supported. "
            "Enabling workaround.\n");
        ret = -EIO;
        goto out;
    } else if (ret != size) {
        diag_printf("Failed to query (%u) UVC %s control : "
            "%d (exp. %u).\n", query, probe ? "probe" : "commit",
            ret, size);
        ret = -EIO;
        goto out;
    }

    ctrl->bmHint = le16_to_cpup((U16 *)&data[0]);
    ctrl->bFormatIndex = data[2];
    ctrl->bFrameIndex = data[3];
    ctrl->dwFrameInterval = le32_to_cpup((U32 *)&data[4]);
    ctrl->wKeyFrameRate = le16_to_cpup((U16 *)&data[8]);
    ctrl->wPFrameRate = le16_to_cpup((U16 *)&data[10]);
    ctrl->wCompQuality = le16_to_cpup((U16 *)&data[12]);
    ctrl->wCompWindowSize = le16_to_cpup((U16 *)&data[14]);
    ctrl->wDelay = le16_to_cpup((U16 *)&data[16]);
    ctrl->dwMaxVideoFrameSize = get_unaligned_le32(&data[18]);
    ctrl->dwMaxPayloadTransferSize = get_unaligned_le32(&data[22]);

    if (size == 34) {
        ctrl->dwClockFrequency = get_unaligned_le32(&data[26]);
        ctrl->bmFramingInfo = data[30];
        ctrl->bPreferedVersion = data[31];
        ctrl->bMinVersion = data[32];
        ctrl->bMaxVersion = data[33];
    } else {
        ctrl->dwClockFrequency = stream->dev->clock_frequency;
        ctrl->bmFramingInfo = 0;
        ctrl->bPreferedVersion = 0;
        ctrl->bMinVersion = 0;
        ctrl->bMaxVersion = 0;
    }

    //Dump_video_stream_setting(ctrl);
    /* Some broken devices return null or wrong dwMaxVideoFrameSize and
     * dwMaxPayloadTransferSize fields. Try to get the value from the
     * format and frame descriptors.
     */
    // FIXME
    //uvc_fixup_video_ctrl(stream, ctrl);
    ret = 0;

out:
    MsReleaseMemory(data);
#endif
    return ret;
}

static int uvc_set_video_ctrl(struct uvc_streaming *stream,
    struct uvc_streaming_control *ctrl, int probe)
{
    U8 *data;
    U16 size;
    int ret = 0;
#if 0
    size = stream->dev->uvc_version >= 0x0110 ? 34 : 26;

    data = MsAllocateMem(size);
    memset(data, 0, size);
    if (data == NULL)
        return -ENOMEM;

    *(U16 *)&data[0] = (ctrl->bmHint);
    data[2] = ctrl->bFormatIndex;
    data[3] = ctrl->bFrameIndex;
    *(U32 *)&data[4] = (ctrl->dwFrameInterval);
    *(U16 *)&data[8] = (ctrl->wKeyFrameRate);
    *(U16 *)&data[10] = (ctrl->wPFrameRate);
    *(U16 *)&data[12] = (ctrl->wCompQuality);
    *(U16 *)&data[14] = (ctrl->wCompWindowSize);
    *(U16 *)&data[16] = (ctrl->wDelay);
    put_unaligned_le32(ctrl->dwMaxVideoFrameSize, &data[18]);
    put_unaligned_le32(ctrl->dwMaxPayloadTransferSize, &data[22]);

    if (size == 34) {
        put_unaligned_le32(ctrl->dwClockFrequency, &data[26]);
        data[30] = ctrl->bmFramingInfo;
        data[31] = ctrl->bPreferedVersion;
        data[32] = ctrl->bMinVersion;
        data[33] = ctrl->bMaxVersion;
    }

    //Dump_video_stream_setting((struct uvc_streaming_control *)data);
    ret = __uvc_query_ctrl(stream->dev, UVC_SET_CUR, 0, stream->intfnum,
        probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
        size, uvc_timeout_param);
    if (ret != size) {
        diag_printf("Failed to set UVC %s control : "
            "%d (exp. %u).\n", probe ? "probe" : "commit",
            ret, size);
        ret = -EIO;
    }

    MsReleaseMemory(data);
#endif
    return ret;
}

int uvc_commit_video(struct uvc_streaming *stream,
                struct uvc_streaming_control *probe)
{
    return uvc_set_video_ctrl(stream, probe, 0);
}

#if MDL_HOSTUVC_ASSEMBLE_FRAME
static void uvc_video_save_all(struct uvc_streaming *stream,
        struct uvc_buffer *buf, const U8 *data, int len)
{
    unsigned int maxlen, nbytes;
    void *mem;

    //diag_printf("++[%s] %s:[len:%d]\n", __FUNCTION__, __FILE__, len);
    if (len <= 0 || len == 12){
//      buf->bytesused = 0;
//      buf->state = UVC_BUF_STATE_QUEUED;
//      buf->error = 0;
        return;
    }

    if (buf->length <= buf->bytesused){
        diag_printf("uvc_video_save_all : raw buffer is not enough,remain len = %d\n",buf->length - buf->bytesused);
        buf->bytesused = 0;
        buf->state = UVC_BUF_STATE_QUEUED;
        buf->error = 0;
        //return;
    }
#if 0
    {
    int i;

    diag_printf("[J] data\n");
    for (i = 0; i < 8; i++) {
        diag_printf("%2x ", data[i]);
    }
    diag_printf("\n");
    }
#endif
    /* Copy the video data to the buffer. */
    maxlen = buf->length - buf->bytesused;
    nbytes = min((unsigned int)len - 12, maxlen);

#if(1)
    mem = (void *)((U32)buf->mem + buf->bytesused);
    memcpy(mem, data + 12 , nbytes);
#endif

    if(buf->bytesused == 0 && uvc_find_tag(UVC_JPG_EXIF_SOI,data,len))
    {
        //diag_printf("Got SOI!!-%u\n",MsGetOsTick());
    }

    buf->bytesused += nbytes;

    if((data[1] & 0x02)){
        //diag_printf("Got EOF!! - %u\n",MsGetOsTick());
        //diag_printf("mem start = 0x%x.\n",buf->mem);
        //diag_printf("used bytes = %u.\n",buf->bytesused);
        //memset(buf->mem, 0, buf->length);
        buf->bytesused = 0;
        buf->state = UVC_BUF_STATE_QUEUED;
        buf->error = 0;
    }

#if(0)
    if(uvc_find_tag(UVC_JPG_EXIF_EOI,data,len)){
        diag_printf("Got JPG EOF!!\n");
        diag_printf("mem start = 0x%x.\n",buf->mem);
        diag_printf("used bytes = %u.\n",buf->bytesused);
        //memset(buf->mem, 0, buf->length);
        buf->bytesused = 0;
        buf->state = UVC_BUF_STATE_QUEUED;
        buf->error = 0;
    }
#endif

    /* Complete the current frame if the buffer size was exceeded. */
    if (len > maxlen) {
        diag_printf("Frame complete (overflow).\n");
        buf->state = UVC_BUF_STATE_READY;
        return;
    }
}
#endif
/* ------------------------------------------------------------------------
 * URB handling
 */

/*
 * Completion handler for video URBs.
 */
static void uvc_video_decode_isoc(struct urb *urb, struct uvc_streaming *stream,
    struct uvc_buffer *buf)
{
    //diag_printf("[J] %s++\n", __FUNCTION__);
#if MDL_HOSTUVC_ASSEMBLE_FRAME
    U8 *mem;
    S32 i;

    for (i = 0; i < urb->number_of_packets; ++i) {
        uvcl_check_iso_frame_status(urb,i);
        mem = (U8 *)((U32)urb->transfer_buffer + urb->iso_frame_desc[i].offset);
        //diag_printf("iso frame actual length[%u] %u\r\n",i,urb->iso_frame_desc[i].actual_length);
        uvc_video_save_all(stream, buf, mem,urb->iso_frame_desc[i].actual_length);
    }
#else
    #if(MDL_HOSTUVC_COPY_FULL_PACKET)
    //Queue urb and wait for processing in Bulk task
    list_add_tail(&urb->urb_list, &buf->queue);
    //Info Bulk task to copy frame data from each urb and trigger decode
    MMPF_OS_SetFlags(USB_OP_Flag, USB_FLAG_USBH_PROC_PKT_REQ, MMPF_OS_FLAG_SET);
    #else
    uvcl_set_single_urb(urb);
    MMPF_USBH_ProcPacketHandler(uvch_xfer_ctl.ubUVCRxState);
    #endif
#endif
}

static void uvc_video_decode_bulk(struct urb *urb, struct uvc_streaming *stream,
    struct uvc_buffer *buf)
{
    int ret;

    if(urb->actual_length == 0 || buf->error) {
    //if(0) {
        //error handle
        buf->error = 0;
        if(stream->plastbulkurb == urb) {
            if ((ret = usb_submit_urb(urb, 0)) < 0) {
                diag_printf("uvc_video_decode_bulk : Failed to resubmit video URB ret=%d.\n",ret);
            }
        }
        else {
            diag_printf("uvc_video_decode_bulk : Not single bulk Urb operation!\n");
        }
        return;
    }

#if(1)
    if(stream->plastbulkurb == urb) {
        //diag_printf("[J] %s URB all done \n", __FUNCTION__);
        //Info Bulk task to copy frame data from each urb and trigger decode
        MMPF_OS_SetFlags(USB_OP_Flag, USB_FLAG_USBH_PROC_PKT_REQ, MMPF_OS_FLAG_SET);
    }
#else
    if(stream->plastbulkurb == urb) {
        diag_printf("[J] %s URB all done \n", __FUNCTION__);
        MMPF_USBH_CompleteUrb_ProcBulkMode();
    }
#endif
}
static void uvc_video_complete(struct urb *urb)
{
    struct uvc_streaming *stream = urb->context;
    struct uvc_buffer *buf = NULL;
#if MDL_HOSTUVC_ASSEMBLE_FRAME
    int ret;
#endif

    buf = uvcl_get_buffer();
    buf->error = urb->status;

    if(urb->status)
        diag_printf("Non-zero status (%d) in video completion handler.\n", urb->status);

    switch (urb->status) {
    case 0:
        break;
    case -ENOENT:       /* usb_kill_urb() called. */
    case -ECONNRESET:   /* usb_unlink_urb() called. */
    case -ESHUTDOWN:    /* The endpoint is being disabled. */
        //uvc_queue_cancel(queue, urb->status == -ESHUTDOWN);
        return;
    default:
        break;
    }

    stream->decode(urb, stream, buf);

#if MDL_HOSTUVC_ASSEMBLE_FRAME
    //diag_printf("%d ",DrvTimerStdaTimerGetTick());
    // continue to submit urb
    if ((ret = usb_submit_urb(urb, 0)) < 0) {
        diag_printf("Failed to resubmit video URB (%d).\n",
            ret);
    }
#endif
}

/*
 * Free transfer buffers.
 */
static void uvc_free_urb_buffers(struct uvc_streaming *stream)
{
    unsigned int i;

    diag_printf("[J] %s++\n", __FUNCTION__);
    for (i = 0; i < UVC_URBS; ++i) {
        if (stream->urb_buffer[i]) {
#if(MDL_HOSTUVC_ASSEMBLE_FRAME || MDL_HOSTUVC_COPY_FULL_PACKET)
            MsReleaseMemory(stream->urb_buffer[i]);
#else
#endif
            stream->urb_buffer[i] = NULL;
        }
    }

    stream->urb_size = 0;
}

/*
 * Allocate transfer buffers. This function can be called with buffers
 * already allocated when resuming from suspend, in which case it will
 * return without touching the buffers.
 *
 * Limit the buffer size to UVC_MAX_PACKETS bulk/isochronous packets. If the
 * system is too low on memory try successively smaller numbers of packets
 * until allocation succeeds.
 *
 * Return the number of allocated packets on success or 0 when out of memory.
 */
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
static int uvc_alloc_urb_buffers(
    struct uvc_streaming *stream,
    unsigned int size,
    unsigned int psize,
    int gfp_flags
)
{
    unsigned int npackets;
    unsigned int i;

    //diag_printf("[J] %s++\n", __FUNCTION__);
    //diag_printf("[J] stream %p\n", stream);
    /* Buffers are already allocated, bail out. */
    if (stream->urb_size)
        return stream->urb_size / psize;

    /* Compute the number of packets. Bulk endpoints might transfer UVC
     * payloads across multiple URBs.
     */
    npackets = DIV_ROUND_UP(size, psize);
    if (npackets > UVC_MAX_PACKETS)
        npackets = UVC_MAX_PACKETS;

    /* Retry allocations until one succeed. */
    //not work when npackets is 1
    //for (; npackets > 1; npackets /= 2) {
    {
        for (i = 0; i < UVC_URBS; ++i) {
            stream->urb_size = psize * npackets;

#if(MDL_HOSTUVC_ASSEMBLE_FRAME || MDL_HOSTUVC_COPY_FULL_PACKET)
            stream->urb_buffer[i] = MsAllocateMem(stream->urb_size);
#else
            {
                SLOT_BUF_CTL    *pbctl = &uvch_xfer_ctl.buf_ctl;

                if( pbctl->ulWritePtr != 0 ||
                    pbctl->ulBufAddr[pbctl->ulWriteBufIdx] == 0){
                    //Check if buffer is valid
                    diag_printf("uvc_alloc_urb_buffers : uvch_xfer_ctl.buf_ctl is invalid!\n");
                }
                stream->urb_buffer[i] = (char *)(pbctl->ulBufAddr[pbctl->ulWriteBufIdx] + pbctl->ulWritePtr);
                diag_printf("uvc_alloc_urb_buffers : stream->urb_buffer[%d]=0x%x,ulWriteBufIdx=%d,ulWritePtr=%d\n",\
                            i,stream->urb_buffer[i],pbctl->ulWriteBufIdx,pbctl->ulWritePtr);
            }
#endif
            if (!stream->urb_buffer[i]) {
                uvc_free_urb_buffers(stream);
                break;
            }
        }

        if (i == UVC_URBS) {
            diag_printf("Allocated %u URB buffers "
                "of %ux%u bytes each.\n", UVC_URBS, npackets,
                psize);
            return npackets;
        }
    }

    diag_printf("Failed to allocate URB buffers (%u bytes "
        "per packet).\n", psize);

    return 0;
}

/*
 * Uninitialize isochronous/bulk URBs and free transfer buffers.
 */
void uvc_uninit_video(struct uvc_streaming *stream, int free_buffers)
{
    struct urb *urb;
    unsigned int i;

    diag_printf("[J] %s++\n", __FUNCTION__);
    //uvc_video_stats_stop(stream);
    if(stream->intf->num_altsetting > 1) {
        for (i = 0; i < UVC_URBS; ++i) {
            urb = stream->urb[i];
            if (urb == NULL)
                continue;
            usb_kill_urb(urb);
            usb_free_urb(urb);
            stream->urb[i] = NULL;
        }
    }
    else {
        for (i = 0; i < UVC_BULK_URBS; ++i) {
            urb = stream->bulkurb[i];
            if (urb == NULL)
                continue;
            usb_kill_urb(urb);
            usb_free_urb(urb);
            stream->bulkurb[i] = NULL;
        }
    }

    if (free_buffers)
        uvc_free_urb_buffers(stream);

}

/*
 * Compute the maximum number of bytes per interval for an endpoint.
 */
static unsigned int uvc_endpoint_max_bpi(
    struct usb_device *dev,
    struct usb_host_endpoint *ep
)
{
    U16 psize;

    diag_printf("dev->eSpeed=%u MaxPacketSize=%u\n",dev->eSpeed,ep->desc.wMaxPacketSize);
    switch (dev->eSpeed) {
    //case USB_SPEED_SUPER:
        //return ep->ss_ep_comp.wBytesPerInterval;
    case USB_SPEED_HIGH:
        //psize = usb_endpoint_maxp(&ep->desc);
        psize = ep->desc.wMaxPacketSize;
        return (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
    default:
        //psize = usb_endpoint_maxp(&ep->desc);
        psize = ep->desc.wMaxPacketSize;
        return psize & 0x07ff;
    }
}

/*
 * Initialize isochronous URBs and allocate transfer buffers. The packet size
 * is given by the endpoint.
 */
static int uvc_init_video_isoc(struct uvc_streaming *stream,
    struct usb_host_endpoint *ep, int gfp_flags)
{
    struct urb *urb;
    unsigned int npackets, i, j;
    struct uvc_buffer *buf;
    U16 psize;
    U32 size;

    //diag_printf("[J] %s++\n", __FUNCTION__);
    diag_printf("[J] isoc++ stream %p, best_ep %p\n", stream, ep);
    psize = uvc_endpoint_max_bpi(stream->dev->udev, ep);

    diag_printf("[J] isoc++ psize :%d,ep->wMaxPacketSize :%d\n", psize,ep->desc.wMaxPacketSize);

    size = ep->desc.wMaxPacketSize * MDL_HOSTUVC_PKT_NUM;
    diag_printf("[J] isoc++ stream dwMaxPayloadTransferSize=%u,used transfer size=%u\n", stream->ctrl.dwMaxPayloadTransferSize, size);

    //allocate memory and assigned stream->urb_buffer[i] , stream->urb_size
    npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);

    if (npackets == 0)
        return -ENOMEM;

    size = npackets * psize;

    for (i = 0; i < UVC_URBS; ++i) {

        urb = usb_alloc_urb(npackets, gfp_flags);
        if (urb == NULL) {
            uvc_uninit_video(stream, 1);
            return -ENOMEM;
        }

        urb->dev = stream->dev->udev;
        urb->context = stream;
        urb->pipe = usb_rcvisocpipe(stream->dev->udev,
                ep->desc.bEndpointAddress);
#if 0 //ndef CONFIG_DMA_NONCOHERENT
        urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
        urb->transfer_dma = stream->urb_dma[i];
#else

        urb->transfer_flags = MS_FLAG_URB_ISO_ASAP;
#endif
        urb->interval = ep->desc.bInterval;
        urb->transfer_buffer = stream->urb_buffer[i];
        urb->complete_func = uvc_video_complete;
        urb->number_of_packets = npackets;
        urb->transfer_buffer_length = size;

        for (j = 0; j < npackets; ++j) {
            urb->iso_frame_desc[j].offset = j * psize;
            urb->iso_frame_desc[j].length = psize;
            //diag_printf("URB[%d]urb->iso_frame_desc[%d]=0x%x \n",i,j,urb->transfer_buffer + urb->iso_frame_desc[j].offset);
        }

        stream->urb[i] = urb;
    }

    buf = uvcl_get_buffer();
    buf->length = buf->packetlen = psize;

    return 0;
}

/*
 * Initialize Bulk URBs.
 */
static int uvc_init_video_bulk(struct uvc_streaming *stream,
    struct usb_host_endpoint *ep, int gfp_flags)
{
    struct urb *urb;
    unsigned int npackets, i;

    diag_printf("[J] bulk++ max packets %d\n", UVC_BULK_URBS);
    for (i = 0; i < UVC_BULK_URBS; ++i) {
        urb = usb_alloc_urb(0, gfp_flags);
        if (urb == NULL) {
            uvc_uninit_video(stream, 0);
            return -ENOMEM;
        }

        urb->dev = stream->dev->udev;
        urb->context = stream;
        urb->pipe = usb_rcvbulkpipe(stream->dev->udev,USBH_HOST_RX_EP_NUM);
        urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
        urb->interval = gubusbh_ep_rx_interval;
       // urb->transfer_buffer = stream->urb_buffer[i];
        urb->complete_func = uvc_video_complete;
        urb->number_of_packets = 1;
        urb->transfer_buffer_length = BULK_MAX_PACKET_SIZE;
        stream->bulkurb[i] = urb;
    }
    return 0;
}

bool uvc_find_tag(U16 usTagID, U8 *pImgAddr, U32 ulLength)
{
    U32 i = 0;
    U8 ubPrefix = (usTagID>>8) & 0xFF;
    U8 ubSuffix = usTagID & 0xFF;

    for (i = 0; i < (ulLength-1); i++)
    {
        if ((ubPrefix == (*(U8*)(pImgAddr+i))) && (ubSuffix == (*(U8*)(pImgAddr+i+1))))
        {
            return true;
        }
    }
    return false;
}
/*
 * Initialize isochronous/bulk URBs and allocate transfer buffers.
 */
int uvc_init_video(struct uvc_streaming *stream, int gfp_flags)
{
    struct usb_interface *intf = stream->intf;
    struct usb_host_endpoint *ep;
    unsigned int i;
    int ret = 0;

    diag_printf("[J] %s++\n", __FUNCTION__);
    diag_printf("stream->intfnum %d\n", stream->intfnum);

    if (intf->num_altsetting > 1) {
        struct usb_host_endpoint *best_ep = NULL;
        unsigned int best_psize = 0;
        unsigned int bandwidth = 1;
        //unsigned int uninitialized_var(altsetting);
        unsigned int altsetting = 0;
        int intfnum = stream->intfnum;

        /* Isochronous endpoint, select the alternate setting. */
        bandwidth = stream->ctrl.dwMaxPayloadTransferSize;

        if (bandwidth == 0) {
            diag_printf("Device requested null "
                "bandwidth, defaulting to lowest.\n");
            bandwidth = 1;
        } else {
            diag_printf("Device requested %u "
                "B/frame bandwidth.\n", bandwidth);
        }

        for (i = 0; i < intf->num_altsetting; ++i) {
            struct usb_host_interface *alts;
            unsigned int psize;

            alts = &intf->altsetting[i];
            // FIXME
            ep = uvc_find_endpoint(alts,
                //stream->header.bEndpointAddress);
                0x81);//DIR_IN|RCPT_IF
            if (ep == NULL)
                continue;

            /* Check if the bandwidth is high enough. */
            psize = uvc_endpoint_max_bpi(stream->dev->udev, ep);
            if (psize <= bandwidth && psize >= best_psize) {
                altsetting = alts->desc.bAlternateSetting;
                best_psize = psize;
                best_ep = ep;
            }
        }

        if (best_ep == NULL) {
            diag_printf("No fast enough alt setting "
                "for requested bandwidth.\n");
            return -EIO;
        }

        diag_printf("Selecting alternate setting %u "
            "(%u B/frame bandwidth).\n", altsetting, best_psize);

        ret = usb_set_interface(stream->dev->udev, intfnum, altsetting);

        if (ret < 0) {
            diag_printf("[J] usb_set_interface ret %d\n", ret);
            return ret;
        }
#if 0 // JF debug
        Dump_interface_content(stream->intf, stream->intfnum);
#endif

        ret = uvc_init_video_isoc(stream, best_ep, gfp_flags);
#if 0 // JF debug
        diag_printf("[J] (I,D,R) = (%p, %p, %p)\n",
            stream->intf, &stream->intf->dev, (&stream->intf->dev)->driver);
#endif
    } else {
        /* Bulk endpoint, proceed to URB initialization. */
        uvc_init_video_bulk(stream, 0, gfp_flags);
    }

    if (ret < 0)
        return ret;

    if (intf->num_altsetting > 1) {
        /* Submit the URBs. */
        for (i = 0; i < UVC_URBS; ++i) {
            //diag_printf("[J] submit_urb[%d] %p\n", i, stream->urb[i]);
            if(stream->urb[i])
                ret = usb_submit_urb(stream->urb[i], gfp_flags);
            if (ret < 0) {
                diag_printf("Failed to submit URB %u "
                        "(%d).\n", i, ret);
                uvc_uninit_video(stream, 1);
                return ret;
            }
        }
    }
    return 0;
}
/* ------------------------------------------------------------------------
 * Video device
 */

/*
 * Initialize the UVC video device by switching to alternate setting 0 and
 * retrieve the default format.
 *
 * Some cameras (namely the Fuji Finepix) set the format and frame
 * indexes to zero. The UVC standard doesn't clearly make this a spec
 * violation, so try to silently fix the values if possible.
 *
 * This function is called before registering the device with V4L.
 */
int uvc_video_init(struct uvc_streaming *stream)
{
    struct uvc_streaming_control *probe = &stream->ctrl;
    //unsigned int i;
    int ret;

    diag_printf("[J] %s++\n", __FUNCTION__);

    /* Select the video decoding function */
    // FIXME:
    if (1) {
        if (stream->intf->num_altsetting > 1)
            stream->decode = uvc_video_decode_isoc;
        else
            stream->decode = uvc_video_decode_bulk;
    }
#if 0 // JF debug
    //Dump_configure_content(stream->dev->udev);
    Dump_interface_content(stream->intf, stream->intfnum);
#endif
    /* Alternate setting 0 should be the default, yet the XBox Live Vision
     * Cam (and possibly other devices) crash or otherwise misbehave if
     * they don't receive a SET_INTERFACE request before any other video
     * control request.
     */
    if (stream->intf->num_altsetting > 1)
        usb_set_interface(stream->dev->udev, stream->intfnum, 0);

    /* Set the streaming probe control with default streaming parameters
     * retrieved from the device. Webcams that don't suport GET_DEF
     * requests on the probe control will just keep their current streaming
     * parameters.
     */
    if (stream->intf->num_altsetting > 1)
        if (uvc_get_video_ctrl(stream, probe, 1, UVC_GET_DEF) == 0)
            uvc_set_video_ctrl(stream, probe, 1);

    /* Initialize the streaming parameters with the probe control current
     * value. This makes sure SET_CUR requests on the streaming commit
     * control will always use values retrieved from a successful GET_CUR
     * request on the probe control, as required by the UVC specification.
     */
    if (stream->intf->num_altsetting > 1) {
        ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
        if (ret < 0)
            return ret;
    }
    return 0;
}

/*
 * Enable or disable the video stream.
 */
int uvc_video_enable(struct uvc_streaming *stream, int enable)
{
    int ret = 0;
    int IsISOMode;

    diag_printf("[J] %s++ %d\n", __FUNCTION__, enable);

    if (stream->intf->num_altsetting > 1)
        IsISOMode = 1;
    else
        IsISOMode = 0;

    if (!enable) {

        if(IsISOMode)
            uvc_uninit_video(stream, 1);
        else
            uvc_uninit_video(stream, 0);
        return 0;
    }

    //Titan : select streaming format as MJEPG
    stream->ctrl.bFormatIndex = 2;

    if (stream->dev->udev->eSpeed == USB_SPEED_HIGH){
        stream->ctrl.dwMaxPayloadTransferSize = MDL_HOSTUVC_HS_MAX_PKT_SIZE;
    }
    else{
        diag_printf("Not support High-Speed Mode!\n");
        stream->ctrl.dwMaxPayloadTransferSize = MDL_HOSTUVC_NS_MAX_PKT_SIZE;
    }

#if(MDL_HOSTUVC_AUTO_OPEN_STREAM)
    /* Commit the streaming parameters. */
    ret = uvc_commit_video(stream, &stream->ctrl);
    if (ret < 0)
        goto error_commit;


    ret = uvc_init_video(stream, 0);
    if (ret < 0)
        goto error_video;
#endif
    return 0;

error_video:
    if(IsISOMode)
        usb_set_interface(stream->dev->udev, stream->intfnum, 0);
error_commit:
    //uvc_queue_enable(&stream->queue, 0);

    return ret;
}
