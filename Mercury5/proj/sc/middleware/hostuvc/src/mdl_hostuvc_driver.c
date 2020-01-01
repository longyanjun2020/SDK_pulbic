#include "sys_MsWrapper_cus_os_mem.h"
#include <drvUSBHost.h>
#include <drvAPIWrapper.h>
#include <drvErrno.h>
#include "mdl_hostuvc_video.h"
#include "mdl_hostuvc.h"
#include "mdl_hostuvc_media_entity.h"
#include "mmp_err.h"
#include "mmpf_usbh_ctl.h"
#include "mmp_component_ctl.h"

#define DRIVER_AUTHOR "MStar USB team"
#define DRIVER_DESC "USB Video Class Lite driver"
#define DRIVER_VERSION "2017.03.27"

#define GET_INTERFACE_INFO(cl,sc,pr) \
        USB_DEVICE_ID_MATCH_INT_INFO,0,0,0,0,0,0,0, (cl), (sc), (pr),0
#define DEMO_SUBCLASS 0x2
#define DEMO_PROTOCOL 0x0

#define _UVC_ALIGN_MASK(x, mask)        (((x) + (mask)) & ~(mask))
#define _UVC_ALIGN(x, a)                _UVC_ALIGN_MASK(x, (typeof(x))(a) - 1)

#define _UVC_JPG_EOI_LOOKUP_LENGTH      (16)        //length of packet tail part
#define _UVC_DMA_MOVE_THRESHOLD         (0xffff)    //0xffff means disable DMA,For test : VGA cam = 500, 720p = 700

static u8 m_ubHUVCDMASemErr = MMPF_OS_ERR_NONE;
static u32 m_ulHUVCDMASemId = MMPF_OS_ERR_CREATE_SEM_ERR;
static struct uvc_device * _gp_uvc = NULL;
static struct usb_device_id uvcl_usb_ids [] =
{
    /* Generic USB Video Class */
    {GET_INTERFACE_INFO (USB_CLASS_VIDEO, 0x1, 0x0) }, // VIDEO_CONTROL
    {0,0,0,0,0,0,0,0,0,0,0,0}
};

struct usb_driver uvcl_driver;
unsigned int uvc_timeout_param = UVC_CTRL_STREAMING_TIMEOUT;
struct urb * _gp_single_urb = NULL;

extern MMP_COMPONENT_BASE   *_gpsUVCComp;
extern MMP_BOOL gbCheckJpegEOIEveryPacket;
extern int ms_usb_string(struct usb_device *pDev, int index, char *pBuf, size_t size);//in usbhost driver

struct usb_host_endpoint *uvc_find_endpoint(
    struct usb_host_interface *alts,
    U8 epaddr
)
{
    struct usb_host_endpoint *ep;
    unsigned int i;

    for (i = 0; i < alts->desc.bNumEndpoints; ++i) {
        ep = &alts->endpoint[i];
        if (ep->desc.bEndpointAddress == epaddr)
            return ep;
    }

    return NULL;
}

static unsigned short get_unaligned_le16(const unsigned char * ptr)
{
    return (((ptr[1]) << 8) | (ptr[0]));
}

static unsigned int get_unaligned_le32(const unsigned char * ptr)
{
    return (((ptr[3]) << 24) | (ptr[2] << 16) | (ptr[1] << 8) | ptr[0]);
}

static void _uvc_dma_init(void)
{
    if(m_ulHUVCDMASemId < MMPF_OS_ERR_SEM_ID_EXCEED_MAX)
        return;

    m_ulHUVCDMASemId = MMPF_OS_CreateSem(0);
    if (m_ulHUVCDMASemId >= MMPF_OS_ERR_SEM_ID_EXCEED_MAX) {
        diag_printf("_uvc_dma_init Create Sem Failed\r\n");
    }
}

static void _uvc_dma_done(u32 argu)
{
    if (m_ubHUVCDMASemErr == MMPF_OS_ERR_NONE) {
        if (MMPF_OS_ReleaseSem(m_ulHUVCDMASemId) != MMPF_OS_ERR_NONE) {
            diag_printf("HUVC DMA semid[%d] Release Fail\r\n",m_ulHUVCDMASemId);
        }
    }
}

static void _uvc_dma_move_data(u32 ulDstAddr, u32 ulSrcAddr, u32 ulCount)
{
    MMP_USHORT  usSemCnt = 0;

    if (ulSrcAddr == 0 || ulDstAddr == 0 || ulCount == 0) {
        return;
    }

    if (MMPF_DMA_MoveData(ulSrcAddr, ulDstAddr, ulCount, _uvc_dma_done, NULL, MMP_FALSE, NULL)) {
        diag_printf("_uvc_dma_move_data Fail\r\n");
        return;
    }

    m_ubHUVCDMASemErr = MMPF_OS_AcquireSem(m_ulHUVCDMASemId, 1000);

    if (m_ubHUVCDMASemErr == MMPF_OS_ERR_SEM_IN_INTERRUPT) {
        m_ubHUVCDMASemErr = MMPF_OS_AcceptSem(m_ulHUVCDMASemId, &usSemCnt);
        if (m_ubHUVCDMASemErr) {
            diag_printf("_uvc_dma_move_data semid[%d] Accept Fail\r\n",m_ulHUVCDMASemId);
            return;
        }
    }
    else if (m_ubHUVCDMASemErr) {
        diag_printf("_uvc_dma_move_data sem[%d] Acquire Fail\r\n",m_ulHUVCDMASemId);
        return;
    }
}
/* ------------------------------------------------------------------------
 * Terminal and unit management
 */

static struct uvc_entity * _uvc_entity_by_id(struct uvc_device *dev, int id)
{
    struct uvc_entity *entity;

    list_for_each_entry(entity, &dev->entities, list) {
        if (entity->id == id)
            return entity;
    }

    return NULL;
}

static int uvc_register_video(
    struct uvc_device *dev,
    struct uvc_streaming *stream
)
{
    int ret;

    diag_printf("[J] %s++\n", __FUNCTION__);
    /* Initialize the streaming interface with default streaming
     * parameters.
     */
    ret = uvc_video_init(stream);
    if (ret < 0) {
        diag_printf("Failed to initialize the device "
            "(%d).\n", ret);
        return ret;
    }
    atomic_inc(&dev->nstreams);
    return 0;
}

/*
 * Delete the UVC device.
 *
 * Called by the kernel when the last reference to the uvc_device structure
 * is released.
 *
 * As this function is called after or during disconnect(), all URBs have
 * already been canceled by the USB core. There is no need to kill the
 * interrupt URB manually.
 */
static void uvc_delete(struct uvc_device *dev)
{
    struct list_head *p, *n;

    _gp_uvc = NULL;
    MMPF_USBH_SetDeviceConnectedSts(MMP_FALSE);
    /* Stop check device alive timer */
    MMPF_USBH_StopCheckDevAliveTimer();
    /* stop frame RX timeout timer */
    MMPF_USBH_StopFrmRxTimer();
    /* stop transaction timeout timer */
    MMPF_USBH_StopTranTimer();

    diag_printf("++[%s] %s\n", __FUNCTION__, __FILE__);
    usb_put_intf(dev->intf);
    usb_put_dev(dev->udev);

    uvc_status_cleanup(dev);

    list_for_each_safe(p, n, &dev->entities) {
        struct uvc_entity *entity;
        entity = list_entry(p, struct uvc_entity, list);
        MsReleaseMemory(entity);
    }

    list_for_each_safe(p, n, &dev->streams) {
        struct uvc_streaming *streaming;
        streaming = list_entry(p, struct uvc_streaming, list);
#if 1 // TODO: free isoc urb
        uvc_video_enable(streaming, 0);
#endif
        //diag_printf("[J] driver release streaming->intf %p\n",
        //  streaming->intf);
        usb_driver_release_interface(&uvcl_driver,
            streaming->intf);
        usb_put_intf(streaming->intf);
        //MsReleaseMemory(streaming->format);
        //MsReleaseMemory(streaming->header.bmaControls);
        MsReleaseMemory(streaming);
    }

    MsReleaseMemory(dev);

}

/*
 * Unregister the video devices.
 */
static void uvc_unregister_video(struct uvc_device *dev)
{
    diag_printf("[J] %s++\n", __FUNCTION__);
    /* Unregistering all video devices might result in uvc_delete() being
     * called from inside the loop if there's no open file handle. To avoid
     * that, increment the stream count before iterating over the streams
     * and decrement it when done.
     */

    if(atomic_dec_and_test(&dev->nstreams))
        uvc_delete(dev);
}

static int uvc_parse_streaming(struct uvc_device *dev,
    struct usb_interface *intf)
{
    struct uvc_streaming *streaming = NULL;
    int ret = -EINVAL;

    diag_printf("[J] %s++\n", __FUNCTION__);
    if (intf->altsetting->desc.bInterfaceSubClass
        != UVC_SC_VIDEOSTREAMING) {
        diag_printf("device %d interface %d isn't a "
            "video streaming interface\n", dev->udev->u32DevNum,
            intf->altsetting[0].desc.bInterfaceNumber);
        return -EINVAL;
    }

    if (usb_driver_claim_interface(&uvcl_driver, intf, dev)) {
        diag_printf("device %d interface %d is already "
            "claimed\n", dev->udev->devnum,
            intf->altsetting[0].desc.bInterfaceNumber);
        return -EINVAL;
    }

    streaming = MsAllocateMem(sizeof *streaming);
    memset(streaming, 0, sizeof *streaming);
    if (streaming == NULL) {
        diag_printf("[J] streaming == NULL\n");
        usb_driver_release_interface(&uvcl_driver, intf);
        return -EINVAL;
    }
    //diag_printf("[J] stream %p\n", streaming);

    //mutex_init(&streaming->mutex);
    streaming->dev = dev;
    streaming->intf = usb_get_intf(intf);
    streaming->intfnum = intf->altsetting->desc.bInterfaceNumber;
    //diag_printf("[J] stream->intfnum %d\n", streaming->intfnum);

    /* Parse the alternate settings to find the maximum bandwidth. */

    list_add_tail(&streaming->list, &dev->streams);
    return 0;

//error:
    usb_driver_release_interface(&uvcl_driver, intf);
    usb_put_intf(intf);
    //MsReleaseMemory(streaming->format);
    //MsReleaseMemory(streaming->header.bmaControls);
    MsReleaseMemory(streaming);
    return ret;
}

static struct uvc_entity *uvc_alloc_entity(u16 type, u8 id,
        unsigned int num_pads, unsigned int extra_size)
{
    struct uvc_entity *entity;
    unsigned int num_inputs;
    unsigned int size;
    unsigned int i;

    extra_size = _UVC_ALIGN(extra_size, sizeof(*entity->pads));
    num_inputs = (type & UVC_TERM_OUTPUT) ? num_pads : num_pads - 1;
    size = sizeof(*entity) + extra_size + sizeof(*entity->pads) * num_pads + num_inputs;
    entity = MsAllocateMem(size);

    if (entity == NULL)
        return NULL;

    entity->id = id;
    entity->type = type;

    entity->num_links = 0;
    entity->num_pads = num_pads;
    entity->pads = ((void *)(entity + 1)) + extra_size;

    for (i = 0; i < num_inputs; ++i)
        entity->pads[i].flags = MEDIA_PAD_FL_SINK;
    if (!UVC_ENTITY_IS_OTERM(entity))
        entity->pads[num_pads-1].flags = MEDIA_PAD_FL_SOURCE;

    entity->bNrInPins = num_inputs;
    entity->baSourceID = (__u8 *)(&entity->pads[num_pads]);

    return entity;
}

/* Parse vendor-specific extensions. */
static int uvc_parse_vendor_control(struct uvc_device *dev,
    const unsigned char *buffer, int buflen)
{
//  struct usb_device *udev = dev->udev;
//  struct usb_host_interface *alts = dev->intf->altsetting;
//  struct uvc_entity *unit;
//  unsigned int n, p;
    int handled = 0;

    switch (le16_to_cpu(dev->udev->descriptor.idVendor)) {
    case 0x046d:        /* Logitech */
        if (buffer[1] != 0x41 || buffer[2] != 0x01)
            break;
#if(0)
        /* Logitech implements several vendor specific functions
         * through vendor specific extension units (LXU).
         *
         * The LXU descriptors are similar to XU descriptors
         * (see "USB Device Video Class for Video Devices", section
         * 3.7.2.6 "Extension Unit Descriptor") with the following
         * differences:
         *
         * ----------------------------------------------------------
         * 0        bLength     1    Number
         *  Size of this descriptor, in bytes: 24+p+n*2
         * ----------------------------------------------------------
         * 23+p+n   bmControlsType  N   Bitmap
         *  Individual bits in the set are defined:
         *  0: Absolute
         *  1: Relative
         *
         *  This bitset is mapped exactly the same as bmControls.
         * ----------------------------------------------------------
         * 23+p+n*2 bReserved   1   Boolean
         * ----------------------------------------------------------
         * 24+p+n*2 iExtension  1   Index
         *  Index of a string descriptor that describes this
         *  extension unit.
         * ----------------------------------------------------------
         */
        p = buflen >= 22 ? buffer[21] : 0;
        n = buflen >= 25 + p ? buffer[22+p] : 0;

        if (buflen < 25 + p + 2*n) {
            uvc_trace(UVC_TRACE_DESCR, "device %d videocontrol "
                "interface %d EXTENSION_UNIT error\n",
                udev->devnum, alts->desc.bInterfaceNumber);
            break;
        }

        unit = uvc_alloc_entity(UVC_VC_EXTENSION_UNIT, buffer[3],
                    p + 1, 2*n);
        if (unit == NULL)
            return -ENOMEM;

        memcpy(unit->extension.guidExtensionCode, &buffer[4], 16);
        unit->extension.bNumControls = buffer[20];
        memcpy(unit->baSourceID, &buffer[22], p);
        unit->extension.bControlSize = buffer[22+p];
        unit->extension.bmControls = (__u8 *)unit + sizeof(*unit);
        unit->extension.bmControlsType = (__u8 *)unit + sizeof(*unit)
                           + n;
        memcpy(unit->extension.bmControls, &buffer[23+p], 2*n);

        if (buffer[24+p+2*n] != 0)
            ms_usb_string(udev, buffer[24+p+2*n], unit->name,
                   sizeof unit->name);
        else
            sprintf(unit->name, "Extension %u", buffer[3]);

        list_add_tail(&unit->list, &dev->entities);
#endif
        handled = 1;
        break;
    }

    return handled;
}

/* Parse vendor-specific extensions. */
static int uvc_parse_standard_control(struct uvc_device *dev,
    const unsigned char *buffer, int buflen)
{
    struct usb_device *udev = dev->udev;
    struct uvc_entity *unit, *term;
    struct usb_interface *intf;
    struct usb_host_interface *alts = dev->intf->altsetting;
    unsigned int i, n, p, len;
    __u16 type;

    diag_printf("uvc_parse_standard_control : Type=%d,remain buflen=%d\n",buffer[2],buflen);

    switch (buffer[2]) {
        case UVC_VC_HEADER:
            n = buflen >= 12 ? buffer[11] : 0;

            if (buflen < 12 || buflen < 12 + n) {
                diag_printf("device %d videocontrol "
                        "interface %d HEADER error\n", udev->devnum,
                        alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            dev->uvc_version = get_unaligned_le16(&buffer[3]);
            dev->clock_frequency = get_unaligned_le32(&buffer[7]);

            /* Parse all USB Video Streaming interfaces. */
            for (i = 0; i < n; ++i) {
                intf = usb_ifnum_to_if(udev, buffer[12+i]);
                if (intf == NULL) {
                    diag_printf( "device %d "
                            "interface %d doesn't exists\n",
                            udev->devnum, i);
                    continue;
                }

                uvc_parse_streaming(dev, intf);
            }
            break;

        case UVC_VC_INPUT_TERMINAL:
            if (buflen < 8) {
                diag_printf( "device %d videocontrol "
                        "interface %d INPUT_TERMINAL error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            /* Make sure the terminal type MSB is not null, otherwise it
             * could be confused with a unit.
             */
            type = get_unaligned_le16(&buffer[4]);
            if ((type & 0xff00) == 0) {
                diag_printf( "device %d videocontrol "
                        "interface %d INPUT_TERMINAL %d has invalid "
                        "type 0x%04x, skipping\n", udev->devnum,
                        alts->desc.bInterfaceNumber,
                        buffer[3], type);
                return 0;
            }

            n = 0;
            p = 0;
            len = 8;

            if (type == UVC_ITT_CAMERA) {
                n = buflen >= 15 ? buffer[14] : 0;
                len = 15;

            } else if (type == UVC_ITT_MEDIA_TRANSPORT_INPUT) {
                n = buflen >= 9 ? buffer[8] : 0;
                p = buflen >= 10 + n ? buffer[9+n] : 0;
                len = 10;
            }

            if (buflen < len + n + p) {
                diag_printf( "device %d videocontrol "
                        "interface %d INPUT_TERMINAL error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            term = uvc_alloc_entity(type | UVC_TERM_INPUT, buffer[3],
                    1, n + p);
            if (term == NULL)
                return -ENOMEM;

            if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA) {
                term->camera.bControlSize = n;
                term->camera.bmControls = (__u8 *)term + sizeof *term;
                term->camera.wObjectiveFocalLengthMin =
                        get_unaligned_le16(&buffer[8]);
                term->camera.wObjectiveFocalLengthMax =
                        get_unaligned_le16(&buffer[10]);
                term->camera.wOcularFocalLength =
                        get_unaligned_le16(&buffer[12]);
                memcpy(term->camera.bmControls, &buffer[15], n);
            } else if (UVC_ENTITY_TYPE(term) ==
                    UVC_ITT_MEDIA_TRANSPORT_INPUT) {
                term->media.bControlSize = n;
                term->media.bmControls = (__u8 *)term + sizeof *term;
                term->media.bTransportModeSize = p;
                term->media.bmTransportModes = (__u8 *)term
                             + sizeof *term + n;
                memcpy(term->media.bmControls, &buffer[9], n);
                memcpy(term->media.bmTransportModes, &buffer[10+n], p);
            }

            if (buffer[7] != 0)
                ms_usb_string(udev, buffer[7], term->name,
                        sizeof term->name);
            else if (UVC_ENTITY_TYPE(term) == UVC_ITT_CAMERA)
                sprintf(term->name, "Camera %u", buffer[3]);
            else if (UVC_ENTITY_TYPE(term) == UVC_ITT_MEDIA_TRANSPORT_INPUT)
                sprintf(term->name, "Media %u", buffer[3]);
            else
                sprintf(term->name, "Input %u", buffer[3]);

            list_add_tail(&term->list, &dev->entities);
            break;

        case UVC_VC_OUTPUT_TERMINAL:
            if (buflen < 9) {
                diag_printf( "device %d videocontrol "
                        "interface %d OUTPUT_TERMINAL error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            /* Make sure the terminal type MSB is not null, otherwise it
             * could be confused with a unit.
             */
            type = get_unaligned_le16(&buffer[4]);
            if ((type & 0xff00) == 0) {
                diag_printf( "device %d videocontrol "
                        "interface %d OUTPUT_TERMINAL %d has invalid "
                        "type 0x%04x, skipping\n", udev->devnum,
                        alts->desc.bInterfaceNumber, buffer[3], type);
                return 0;
            }

            term = uvc_alloc_entity(type | UVC_TERM_OUTPUT, buffer[3],
                    1, 0);
            if (term == NULL)
                return -ENOMEM;

            memcpy(term->baSourceID, &buffer[7], 1);

            if (buffer[8] != 0)
                ms_usb_string(udev, buffer[8], term->name,
                        sizeof term->name);
            else
                sprintf(term->name, "Output %u", buffer[3]);

            list_add_tail(&term->list, &dev->entities);
            break;

        case UVC_VC_SELECTOR_UNIT:
            p = buflen >= 5 ? buffer[4] : 0;

            if (buflen < 5 || buflen < 6 + p) {
                diag_printf( "device %d videocontrol "
                        "interface %d SELECTOR_UNIT error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, 0);
            if (unit == NULL)
                return -ENOMEM;

            memcpy(unit->baSourceID, &buffer[5], p);

            if (buffer[5+p] != 0)
                ms_usb_string(udev, buffer[5+p], unit->name,
                        sizeof unit->name);
            else
                sprintf(unit->name, "Selector %u", buffer[3]);

            list_add_tail(&unit->list, &dev->entities);
            break;

        case UVC_VC_PROCESSING_UNIT:
            n = buflen >= 8 ? buffer[7] : 0;
            p = dev->uvc_version >= 0x0110 ? 10 : 9;

            if (buflen < p + n) {
                diag_printf( "device %d videocontrol "
                        "interface %d PROCESSING_UNIT error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            unit = uvc_alloc_entity(buffer[2], buffer[3], 2, n);
            if (unit == NULL)
                return -ENOMEM;

            memcpy(unit->baSourceID, &buffer[4], 1);
            unit->processing.wMaxMultiplier =
                    get_unaligned_le16(&buffer[5]);
            unit->processing.bControlSize = buffer[7];
            unit->processing.bmControls = (__u8 *)unit + sizeof *unit;
            memcpy(unit->processing.bmControls, &buffer[8], n);
            if (dev->uvc_version >= 0x0110)
                unit->processing.bmVideoStandards = buffer[9+n];

            if (buffer[8+n] != 0)
                ms_usb_string(udev, buffer[8+n], unit->name,
                        sizeof unit->name);
            else
                sprintf(unit->name, "Processing %u", buffer[3]);

            list_add_tail(&unit->list, &dev->entities);
            break;

        case UVC_VC_EXTENSION_UNIT:
            p = buflen >= 22 ? buffer[21] : 0;
            n = buflen >= 24 + p ? buffer[22+p] : 0;

            if (buflen < 24 + p + n) {
                diag_printf( "device %d videocontrol "
                        "interface %d EXTENSION_UNIT error\n",
                        udev->devnum, alts->desc.bInterfaceNumber);
                return -EINVAL;
            }

            unit = uvc_alloc_entity(buffer[2], buffer[3], p + 1, n);
            if (unit == NULL)
                return -ENOMEM;

            memcpy(unit->extension.guidExtensionCode, &buffer[4], 16);
            unit->extension.bNumControls = buffer[20];
            memcpy(unit->baSourceID, &buffer[22], p);
            unit->extension.bControlSize = buffer[22+p];
            unit->extension.bmControls = (__u8 *)unit + sizeof *unit;
            memcpy(unit->extension.bmControls, &buffer[23+p], n);

            if (buffer[23+p+n] != 0)
                ms_usb_string(udev, buffer[23+p+n], unit->name,
                        sizeof unit->name);
            else
                sprintf(unit->name, "Extension %u", buffer[3]);

            list_add_tail(&unit->list, &dev->entities);
            break;

        default:
            diag_printf( "Found an unknown CS_INTERFACE "
                    "descriptor (%u)\n", buffer[2]);
            break;
    }

    return 0;
}

/**
 * usb_endpoint_dir_in - check if the endpoint has IN direction
 * @epd: endpoint to be checked
 *
 * Returns true if the endpoint is of type IN, otherwise it returns false.
 */
static inline int usb_endpoint_dir_in(const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN);
}

/**
 * usb_endpoint_xfer_int - check if the endpoint has interrupt transfer type
 * @epd: endpoint to be checked
 *
 * Returns true if the endpoint is of type interrupt, otherwise it returns
 * false.
 */
static inline int usb_endpoint_xfer_int(
                const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
        USB_ENDPOINT_XFER_INT);
}

/**
 * usb_endpoint_is_int_in - check if the endpoint is interrupt IN
 * @epd: endpoint to be checked
 *
 * Returns true if the endpoint has interrupt transfer type and IN direction,
 * otherwise it returns false.
 */
static inline int usb_endpoint_is_int_in(
                const struct usb_endpoint_descriptor *epd)
{
    return usb_endpoint_xfer_int(epd) && usb_endpoint_dir_in(epd);
}

static int uvc_parse_control(struct uvc_device *dev)
{
    struct usb_host_interface *alts = dev->intf->altsetting;
    unsigned char *buffer = alts->extra;
    int buflen = alts->extralen;
    int ret;

    diag_printf("[J] %s++\n", __FUNCTION__);
    /* Parse the default alternate setting only, as the UVC specification
     * defines a single alternate setting, the default alternate setting
     * zero.
     */

    while (buflen > 2) {
        if (uvc_parse_vendor_control(dev, buffer, buflen) ||
            buffer[1] != USB_DT_CS_INTERFACE)
            goto next_descriptor;

        if ((ret = uvc_parse_standard_control(dev, buffer, buflen)) < 0)
            return ret;

next_descriptor:
        buflen -= buffer[0];
        buffer += buffer[0];
    }

    /* Check if the optional status endpoint is present. Built-in iSight
     * webcams have an interrupt endpoint but spit proprietary data that
     * don't conform to the UVC status endpoint messages. Don't try to
     * handle the interrupt endpoint for those cameras.
     */
    if (alts->desc.bNumEndpoints == 1 /*&&
        !(dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)*/) {
        struct usb_host_endpoint *ep = &alts->endpoint[0];
        struct usb_endpoint_descriptor *desc = &ep->desc;

        if (usb_endpoint_is_int_in(desc) &&
            (desc->wMaxPacketSize) >= 8 &&
            desc->bInterval != 0) {
            diag_printf("Found a Status endpoint "
                "(addr %02x).\n", desc->bEndpointAddress);
            dev->int_ep = ep;
        }
    }

    return 0;
}

/*
 * Register all video devices in all chains.
 */
static int uvc_register_terms(struct uvc_device *dev,
    struct uvc_video_chain *chain)
{
    struct uvc_streaming *stream;
    int ret;

    diag_printf("[J] %s++\n", __FUNCTION__);
    // FIXME
    stream = list_entry(dev->streams.next, struct uvc_streaming, list);
    ret = uvc_register_video(dev, stream);
    if (ret < 0)
        return ret;
    return 0;
}

static int uvc_register_chains(struct uvc_device *dev)
{
    struct uvc_video_chain *chain;
    int ret;

    diag_printf("[J] %s++\n", __FUNCTION__);
    // FIXME
    ret = uvc_register_terms(dev, chain);
    if (ret < 0)
        return ret;
    return 0;
}

static int uvcl_probe(
    struct usb_interface *intf,
    const struct usb_device_id *id
)
{
    struct usb_device *udev = interface_to_usbdev(intf);
    struct uvc_device *dev;
    int ret = 0;

    diag_printf("%s %s\n", DRIVER_DESC, DRIVER_VERSION);
    dev = MsAllocateMem(sizeof *dev);
    if (dev == NULL)
        return -ENOMEM;
    memset(dev, 0, sizeof *dev);

    INIT_LIST_HEAD(&dev->entities);
    INIT_LIST_HEAD(&dev->streams);
    atomic_set(&dev->nstreams, 0);

    dev->udev = usb_get_dev(udev);
    dev->intf = usb_get_intf(intf);
    // FIXME: current?
    dev->intfnum = intf->altsetting->desc.bInterfaceNumber;

    #if 0
    if (udev->product != NULL)
        strlcpy(dev->name, udev->product, sizeof dev->name);
    else
        snprintf(dev->name, sizeof dev->name,
            "UVC Camera (%04x:%04x)",
            (udev->descriptor.idVendor),
            (udev->descriptor.idProduct));
    #endif

    /* Parse the Video Class control descriptor. */
    if (uvc_parse_control(dev) < 0) {
        diag_printf("Unable to parse UVC descriptors.\n");
        goto error;
    }
    diag_printf("Found UVC %u.%02x device %s (%04x:%04x)\n",
        dev->uvc_version >> 8, dev->uvc_version & 0xff,
        udev->product ? udev->product : "<unnamed>",
        le16_to_cpu(udev->descriptor.idVendor),
        le16_to_cpu(udev->descriptor.idProduct));

    /* Register the media and V4L2 devices. */

    /* Initialize controls. */

    /* Scan the device for video chains. */

    /* Register video device nodes. */
    if (uvc_register_chains(dev) < 0)
        goto error;

    /* Save our data pointer in the interface data. */
    usb_set_intfdata(intf, dev);

    /* Initialize the interrupt URB. */
    if ((ret = uvc_status_init(dev)) < 0) {
        diag_printf("Unable to initialize the status "
            "endpoint (%d), status interrupt will not be "
            "supported.\n", ret);
    }

    diag_printf("[J] %s--\n", __FUNCTION__);

// TODO:
#if 1 // test video streaming open only
    {
    struct uvc_streaming *streaming;

    streaming = list_entry(dev->streams.next, struct uvc_streaming, list);
    uvc_status_start(streaming->dev); // status pipe switch
    uvc_video_enable(streaming, 1);
    }
#endif

    _gp_uvc = dev;
    return 0;

error:
    uvc_unregister_video(dev);
    diag_printf("[J] %s--\n", __FUNCTION__);
    return -ENODEV;
}

static void uvcl_disconnect(struct usb_interface *intf)
{
    struct uvc_device *dev = usb_get_intfdata(intf);
    //struct usb_device *udev = interface_to_usbdev(intf);

    diag_printf("[J] %s++\n", __FUNCTION__);
    //uvcl_buffer_dump(uvcl_get_buffer(), 512);

    /* Set the USB interface data to NULL. This can be done outside the
     * lock, as there's no other reader.
     */
    usb_set_intfdata(intf, NULL);

    //dev->state |= UVC_DEV_DISCONNECTED;

    uvc_unregister_video(dev);
}

/*
 * */
static void uvcl_process_URB_ISO(struct urb *urb, struct uvc_buffer *buf)
{
    int i;

    for (i = 0; i < urb->number_of_packets; ++i) {
        U32 nLookupLength;
        int payloadlen;
        void *pSrcMem ,*pDstMem ,*pSrcHdrMem;

        payloadlen = urb->iso_frame_desc[i].actual_length;
        payloadlen -= UVC_PH_LEN;

        if (payloadlen <= 0){
            continue;
        }

        if(buf->packetlen < urb->iso_frame_desc[i].actual_length){
            diag_printf("======uvcl_process_URB_ISO : packet over size!!=======\n");
        }

        uvcl_check_iso_frame_status(urb,i);
        pSrcHdrMem = (U8 *)((U32)urb->transfer_buffer + urb->iso_frame_desc[i].offset);
        pSrcMem = (U8 *)pSrcHdrMem + UVC_PH_LEN;
        pDstMem = (U8 *) (buf->pUVCFmrBufAddr[buf->bufidx] + buf->writeidx);

        if(buf->FoundSOICnt == 0){
            if(uvc_find_tag(UVC_JPG_EXIF_SOI, pSrcMem, 8)){
                //diag_printf("uvcl_process_URB_ISO : Got JPG SOI!!\n");
                buf->FoundSOICnt++;
            }
        }

        if(buf->bframedrop) {
            if(buf->FoundSOICnt)
                buf->bframedrop = 0;
            else
                continue;
        }

        buf->writeidx += payloadlen;
        if (buf->framesize - buf->packetlen < buf->writeidx) {
            diag_printf("======uvcl_process_URB_ISO : FF:%d FP:%d ulXferSize:%d======\n",\
                    buf->framesize,buf->packetlen,buf->writeidx);

            buf->bframedrop = 1;
            buf->FoundSOICnt = 0;
            buf->writeidx = 0;
            continue;
        }
        else {
            if (payloadlen >= _UVC_DMA_MOVE_THRESHOLD)
                _uvc_dma_move_data(pDstMem, pSrcMem , payloadlen);
            else
                memcpy(pDstMem, pSrcMem , payloadlen);
        }

        if (gbCheckJpegEOIEveryPacket && buf->FoundSOICnt) {
            nLookupLength = (payloadlen > _UVC_JPG_EOI_LOOKUP_LENGTH) ? _UVC_JPG_EOI_LOOKUP_LENGTH : (payloadlen);

            if (uvc_find_tag(UVC_JPG_EXIF_EOI, pSrcMem + payloadlen - nLookupLength, nLookupLength)) {

                //diag_printf("Got JPG EOF!!\n");

                //Titan Test
                if (buf->writeidx == 0) {
                    buf->bframedrop = 1;
                    diag_printf("======uvcl_process_URB_ISO : ulXferSize:0======\n");
                }
                else if (MMP_ERR_NONE == MMP_CompCtl_StoreBufferDone(_gpsUVCComp, buf->writeidx, NULL)) {
                    //Sync write index with component
                    buf->bufidx = _gpsUVCComp->MemoryInfo->memctl.frm.ubWBufIndex;
                }

                buf->FoundSOICnt = 0;
                buf->writeidx = 0;
            }
        }
        else if (*((char *)pSrcHdrMem + 1) & UVC_STREAM_EOF) {

            nLookupLength = (payloadlen > _UVC_JPG_EOI_LOOKUP_LENGTH) ? _UVC_JPG_EOI_LOOKUP_LENGTH : (payloadlen);

            if (uvc_find_tag(UVC_JPG_EXIF_EOI, pSrcMem + payloadlen - nLookupLength, nLookupLength)) {

                //diag_printf("Got JPG EOF!!\n");

                //Titan Test
                if (buf->writeidx == 0) {
                    buf->bframedrop = 1;
                    diag_printf("======uvcl_process_URB_ISO : ulXferSize:0======\n");
                }
                else if (buf->FoundSOICnt == 0) {
                    buf->bframedrop = 1;
                    diag_printf("======uvcl_process_URB_ISO : No JPG SOI tag!!=======\n");
                }
                else if (MMP_ERR_NONE == MMP_CompCtl_StoreBufferDone(_gpsUVCComp, buf->writeidx, NULL)) {
                    //Sync write index with component
                    buf->bufidx = _gpsUVCComp->MemoryInfo->memctl.frm.ubWBufIndex;
                }

                buf->FoundSOICnt = 0;
                buf->writeidx = 0;
            }
            else {
                buf->bframedrop = 1;
                buf->FoundSOICnt = 0;
                buf->writeidx = 0;
                //diag_printf("=======uvcl_process_URB_ISO : No JPG EOI tag in EOF UVC Pkt!!=======\n");
            }
        }
    }
}

int uvcl_init(void)
{
    int ret;

    uvcl_driver.name[0] = 0;
    strcpy(uvcl_driver.name,"uvcl-driver");
    uvcl_driver.probe_func = uvcl_probe;
    uvcl_driver.discon_func = uvcl_disconnect;
    uvcl_driver.match_id_table = uvcl_usb_ids;

    ret = usb_register(&uvcl_driver);
    if (ret)
        diag_printf("usb register fail, err #%d\n", ret);
    diag_printf("RTK "DRIVER_DESC"\n");
    _uvc_dma_init();

    return ret;
}

void uvcl_cleanup(void)
{
    usb_deregister(&uvcl_driver);
}

void uvcl_check_iso_frame_status(struct urb *urb,int Index)
{
    int iso_status_msg = 1;
    int iso_msg_once = 1;
    struct uvc_buffer *pbuf ;

    pbuf = uvcl_get_buffer();

    if (urb->iso_frame_desc[Index].status < 0) {
        if ((urb->iso_frame_desc[Index].status == -EXDEV) ||
            (urb->iso_frame_desc[Index].status == -71)) {
            if (Index == (urb->number_of_packets - 1)){
                iso_status_msg = 1;
            }
            else if (iso_msg_once) {
                iso_status_msg = 1;
                iso_msg_once = 0;
            }
            iso_status_msg = 0;
        }
        if (iso_status_msg) {
            diag_printf("[%2d] ", Index);
            diag_printf("USB iso frame lost (%d).\n",urb->iso_frame_desc[Index].status);
        }

        /* Mark the buffer as faulty. */
        if (pbuf != NULL)
            pbuf->error = 1;
    }

    /*if (!urb->iso_frame_desc[Index].actual_length)
        diag_printf("[%2d] iso frame actual length 0\n");*/

}

struct urb * uvcl_get_single_urb(void)
{
    return _gp_single_urb;
}

void uvcl_set_single_urb(struct urb * urb)
{
    _gp_single_urb = urb;
}

/*
 * Trigger one bulk Urb
 * */
int uvcl_trigger_bulk_urb(u32 srcaddr, u32 totalbytes)
{
	u8 * pbuffer;
	struct uvc_streaming *streaming;
	struct urb *urb;
	int ret;

	if(!_gp_uvc)
		return -1;

	streaming = list_entry(_gp_uvc->streams.next, struct uvc_streaming, list);
	streaming->plastbulkurb = NULL;
	pbuffer = srcaddr;

	urb = streaming->bulkurb[0];

	urb->transfer_buffer_length = totalbytes;
	if(urb->transfer_buffer_length & 0x1F)//size must align 32
		urb->transfer_buffer_length = ALIGN32(urb->transfer_buffer_length);
	urb->transfer_buffer = pbuffer;
	streaming->plastbulkurb = urb;

    if ((ret = usb_submit_urb(urb, 0)) < 0) {
        diag_printf("uvcl_trigger_bulk_urb : Failed to resubmit video URB ret=%d.\n",ret);
        return -1;
    }
}

/*
 * Trigger multiple Urbs
 * */
int uvcl_trigger_bulk_urb_ex(u32 srcaddr, u16 each_pkt_byte, u16 last_pkt_byte, u32 totalpkt)
{
	u8 * pbuffer;
	struct uvc_streaming *streaming;
	struct urb *urb;
	int i, ret;

	if(!_gp_uvc)
		return -1;
	if(totalpkt > UVC_BULK_URBS) {
		diag_printf("uvcl_trigger_bulk_urb : no enough Bulk URBs(%d-%d)\n",totalpkt,UVC_BULK_URBS);
		return -1;
	}

	streaming = list_entry(_gp_uvc->streams.next, struct uvc_streaming, list);
	streaming->plastbulkurb = NULL;
	pbuffer = srcaddr;

#if(UVC_BULK_URBS == 1)
	urb = streaming->bulkurb[0];

	if(totalpkt == 1)
		urb->transfer_buffer_length = last_pkt_byte;
	else
		urb->transfer_buffer_length = each_pkt_byte*(totalpkt-1) + last_pkt_byte;

	if(urb->transfer_buffer_length & 0x1F)//size must align 32
		urb->transfer_buffer_length = ALIGN32(urb->transfer_buffer_length);
	urb->transfer_buffer = pbuffer;
	streaming->plastbulkurb = urb;

    if ((ret = usb_submit_urb(urb, 0)) < 0) {
        diag_printf("uvcl_trigger_bulk_urb : Failed to resubmit video URB ret=%d,i=%d.\n",ret ,i);
        return -1;
    }
#else
	for(i = 0 ; i < totalpkt; i++) {
		urb = streaming->bulkurb[i];
		if(i == totalpkt - 1) {
			urb->transfer_buffer_length = last_pkt_byte;
			streaming->plastbulkurb = urb;
		}
		else {
			urb->transfer_buffer_length = each_pkt_byte;
		}

		if(urb->transfer_buffer_length & 0x1F)//size must align 32
			urb->transfer_buffer_length = ALIGN32(urb->transfer_buffer_length);
		urb->transfer_buffer = pbuffer;

	    if ((ret = usb_submit_urb(urb, 0)) < 0) {
	        diag_printf("uvcl_trigger_bulk_urb : Failed to resubmit video URB ret=%d,i=%d.\n",ret ,i);
	        return -1;
	    }

	    pbuffer += urb->transfer_buffer_length;
	}
#endif
	return 0;
}

void uvcl_streaming_enable(bool en)
{
    struct uvc_streaming *streaming;

    if(!_gp_uvc)
        return;

    streaming = list_entry(_gp_uvc->streams.next, struct uvc_streaming, list);

    if(en){
        int ret = 0;

    #if(MDL_HOSTUVC_ASSEMBLE_FRAME)
        /* Initialize the video buffers queue. */
        ret = uvcl_buffer_prepare(uvcl_get_buffer(), MDL_HOSTUVC_FRAME_BUFFER_SIZE);
    #elif(MDL_HOSTUVC_COPY_FULL_PACKET)
        uvcl_buffer_reset();
    #endif

        if (ret){
            diag_printf("uvcl prepare buffer failed.\n");
            return;
        }

        /* Commit the streaming parameters. */
        if ((ret = uvc_commit_video(streaming, &streaming->ctrl)) < 0){
            diag_printf("uvcl stream commit failed.\n");
            return;
        }

        ret = uvc_init_video(streaming, 0);
        if (ret < 0){
            diag_printf("uvcl uvc_init_video failed.\n");
            return;
        }

    }
    else{

        if (streaming->intf->num_altsetting > 1) {
        	uvc_uninit_video(streaming, 1);
        	usb_set_interface(streaming->dev->udev, streaming->intfnum, 0);
        }
        else {
        	uvc_uninit_video(streaming, 0);
        	//MUST disable RX endpoint
        	ms_hcd_endpoint_disable (_gp_uvc->udev, ms_usb_pipe_endpoint(_gp_uvc->udev, usb_rcvbulkpipe(_gp_uvc->udev,USBH_HOST_RX_EP_NUM)));
        }

    }
}

void uvcl_trigger_urb(u32 ulStartAddr)
{
    struct urb *purb;
    int ret;

    //diag_printf("trigger_urb addr=0x%x\n",ulStartAddr);

    purb = uvcl_get_single_urb();

    purb->transfer_buffer = (void *)ulStartAddr;

    // continue to submit urb
    if ((ret = usb_submit_urb(purb, 0)) < 0) {
        diag_printf("uvcl_trigger_urb :Failed to resubmit video URB (%d).\n",ret);
    }
}

/*
 * uvcl_get_VIDPID
 * @param [in] bEndian      0 - do not auto transfer byte order, 1 - do byte order transfer
 * @param [in] pDstaddr     User's buffer to store VID&PID data
 * @return -1 as error,ow 0
 * */
int uvcl_get_VIDPID(unsigned char bEndian,void * pDstaddr)
{
    if(!_gp_uvc || !pDstaddr)
        return -1;

    if(bEndian){
        __u16 *pdst16 = pDstaddr;
        *pdst16++ = _gp_uvc->udev->descriptor.idVendor;
        *pdst16 = _gp_uvc->udev->descriptor.idProduct;
    }
    else{
        __u8 *pdst8 = pDstaddr;
        *pdst8++ = _gp_uvc->udev->descriptor.idVendor & 0xff;
        *pdst8++ = (_gp_uvc->udev->descriptor.idVendor >> 8) & 0xff;
        *pdst8++ = _gp_uvc->udev->descriptor.idProduct & 0xff;
        *pdst8 = (_gp_uvc->udev->descriptor.idProduct >> 8) & 0xff;
    }

    return 0;
}

unsigned char uvcl_find_entity_id_by_type(unsigned short type)
{
    struct uvc_entity *entity;

    if(!_gp_uvc)
        return 0xFF;

    list_for_each_entry(entity, &_gp_uvc->entities, list) {
        if (entity->type == type)
            return entity->id;
    }

    return 0xFF;
}

unsigned char uvcl_find_interface_num(unsigned char subclass)
{
    if(!_gp_uvc)
        return 0xFF;

    if(subclass == UVC_SC_VIDEOCONTROL){
        return _gp_uvc->intfnum;
    }
    else if(subclass == UVC_SC_VIDEOSTREAMING){
        struct uvc_streaming *streaming;
        streaming = list_entry(_gp_uvc->streams.next, struct uvc_streaming, list);
        return streaming->intfnum;
    }

    return 0xFF;
}

int uvcl_control_transfer(unsigned char reqtype, unsigned char query,\
                            unsigned short idx, unsigned short val,\
                            void *data, unsigned short size)
{
    unsigned int pipe;

    if(!_gp_uvc)
        return -EBADF;

    pipe = (reqtype & 0x80) ? usb_rcvctrlpipe(_gp_uvc->udev, 0)
                  : usb_sndctrlpipe(_gp_uvc->udev, 0);
    //reqtype |= (query & 0x80) ? USB_DIR_IN : USB_DIR_OUT;

    return usb_control_msg(_gp_uvc->udev, pipe, query, reqtype, val,
            idx, data, size, 5000/*5s*/);
}

int uvcl_is_mdl_done(void)
{
    return _gp_uvc ? 1 : 0;
}

void uvcl_process_URB(bool bISOMode)
{
    int ret;
    struct urb *urb;
    struct list_head *p,*n;
    struct uvc_buffer *pbuf;
    MsIntMask_e eIntMask;

    pbuf = uvcl_get_buffer();

    list_for_each_safe(p, n, &pbuf->queue) {

        urb = list_entry(p, struct urb, urb_list);
        uvcl_process_URB_ISO(urb, pbuf);
        eIntMask = MsDisableInterrupt();
        list_del_init(&urb->urb_list);
        MsEnableInterrupt(eIntMask);

        // continue to submit urb
        if ((ret = usb_submit_urb(urb, 0)) < 0) {
            diag_printf("Failed to resubmit video URB (%d).\n", ret);
            if (ret == -ENOMEM) {
                eIntMask = MsDisableInterrupt();
                list_add_tail(&urb->urb_list, &pbuf->queue);
                MsEnableInterrupt(eIntMask);
            }
        }
    }
}
