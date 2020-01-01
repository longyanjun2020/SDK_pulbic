#ifndef _DRV_UVC_VIDEO_H_
#define _DRV_UVC_VIDEO_H_

#include "mdl_hostuvc_stream.h"


// 0 : Info Bulk task to handle frame data, 1 : handle frame data in mdl_hostuvc_video.c
#define MDL_HOSTUVC_ASSEMBLE_FRAME                  0
#define MDL_HOSTUVC_COPY_FULL_PACKET                1
//0 : Let UI flow commit and start streaming, 1 : open stream immediately
#define MDL_HOSTUVC_AUTO_OPEN_STREAM                0
#define MDL_HOSTUVC_FRAME_BUFFER_SIZE               (100 * 1024)
//max payload size for high speed
#define MDL_HOSTUVC_HS_MAX_PKT_SIZE                 ISO_MAX_PACKET_SIZE
//max payload size for normal speed
#define MDL_HOSTUVC_NS_MAX_PKT_SIZE                 (944)

#define MDL_HOSTUVC_PKT_NUM                         (16)

/* --------------------------------------------------------------------------
 * Media.h
 */
#define MEDIA_PAD_FL_SINK       (1 << 0)
#define MEDIA_PAD_FL_SOURCE     (1 << 1)
/* --------------------------------------------------------------------------
 * UVC constants
 */

#define UVC_TERM_INPUT          0x0000
#define UVC_TERM_OUTPUT         0x8000
#define UVC_TERM_DIRECTION(term)    ((term)->type & 0x8000)

#define UVC_ENTITY_TYPE(entity)     ((entity)->type & 0x7fff)
#define UVC_ENTITY_IS_UNIT(entity)  (((entity)->type & 0xff00) == 0)
#define UVC_ENTITY_IS_TERM(entity)  (((entity)->type & 0xff00) != 0)
#define UVC_ENTITY_IS_ITERM(entity) \
    (UVC_ENTITY_IS_TERM(entity) && \
    ((entity)->type & 0x8000) == UVC_TERM_INPUT)
#define UVC_ENTITY_IS_OTERM(entity) \
    (UVC_ENTITY_IS_TERM(entity) && \
    ((entity)->type & 0x8000) == UVC_TERM_OUTPUT)


#define UVC_JPG_EXIF_SOI                0xFFD8
#define UVC_JPG_EXIF_EOI                0xFFD9
/* Number of isochronous URBs. */
#define UVC_URBS        8
/* Number of bulk URBs. */
#define UVC_BULK_URBS        (1)
/* Maximum number of packets per URB. */
#define UVC_MAX_PACKETS     32
/* Maximum number of video buffers. */
#define UVC_MAX_VIDEO_BUFFERS   32
/* Maximum status buffer size in bytes of interrupt URB. */
#define UVC_MAX_STATUS_SIZE 16

#define UVC_CTRL_CONTROL_TIMEOUT    2000
#define UVC_CTRL_STREAMING_TIMEOUT  10000

/* Devices quirks */
#define UVC_QUIRK_STATUS_INTERVAL   0x00000001

/* Format flags */
#define UVC_FMT_FLAG_COMPRESSED     0x00000001
#define UVC_FMT_FLAG_STREAM         0x00000002

/* mapping mstar urb fill function */
#define usb_fill_int_urb ms_usb_stuff_intr_urb
#define usb_fill_control_urb ms_usb_stuff_control_urb
#define usb_fill_bulk_urb ms_usb_stuff_bulk_urb

struct uvc_device;

/* TODO: Put the most frequently accessed fields at the beginning of
 * structures to maximize cache efficiency.
 */
struct uvc_control_info {
    struct list_head mappings;

    __u8 entity[16];
    __u8 index; /* Bit index in bmControls */
    __u8 selector;

    __u16 size;
    __u32 flags;
};

struct uvc_control {
    struct uvc_entity *entity;
    struct uvc_control_info info;

    __u8 index; /* Used to match the uvc_control entry with a
               uvc_control_info. */
    __u8 dirty:1,
         loaded:1,
         modified:1,
         cached:1,
         initialized:1;

    __u8 *uvc_data;
};

struct uvc_format_desc {
    char *name;
    __u8 guid[16];
    __u32 fcc;
};

/* The term 'entity' refers to both UVC units and UVC terminals.
 *
 * The type field is either the terminal type (wTerminalType in the terminal
 * descriptor), or the unit type (bDescriptorSubtype in the unit descriptor).
 * As the bDescriptorSubtype field is one byte long, the type value will
 * always have a null MSB for units. All terminal types defined by the UVC
 * specification have a non-null MSB, so it is safe to use the MSB to
 * differentiate between units and terminals as long as the descriptor parsing
 * code makes sure terminal types have a non-null MSB.
 *
 * For terminals, the type's most significant bit stores the terminal
 * direction (either UVC_TERM_INPUT or UVC_TERM_OUTPUT). The type field should
 * always be accessed with the UVC_ENTITY_* macros and never directly.
 */

struct uvc_entity {
    struct list_head list;      /* Entity as part of a UVC device. */
    struct list_head chain;     /* Entity as part of a video device
                                 * chain. */
    __u8 id;
    __u16 type;
    char name[64];

    /* Media controller-related fields. */
    //struct video_device *vdev;
    //struct v4l2_subdev subdev;

    unsigned int num_pads;
    unsigned int num_links;
    struct media_pad *pads;

    union {
        struct {
            __u16 wObjectiveFocalLengthMin;
            __u16 wObjectiveFocalLengthMax;
            __u16 wOcularFocalLength;
            __u8  bControlSize;
            __u8  *bmControls;
        } camera;

        struct {
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  bTransportModeSize;
            __u8  *bmTransportModes;
        } media;

        struct {
        } output;

        struct {
            __u16 wMaxMultiplier;
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  bmVideoStandards;
        } processing;

        struct {
        } selector;

        struct {
            __u8  guidExtensionCode[16];
            __u8  bNumControls;
            __u8  bControlSize;
            __u8  *bmControls;
            __u8  *bmControlsType;
        } extension;
    };

    __u8 bNrInPins;
    __u8 *baSourceID;

    unsigned int ncontrols;
    struct uvc_control *controls;
};

struct uvc_frame {
    __u8  bFrameIndex;
    __u8  bmCapabilities;
    __u16 wWidth;
    __u16 wHeight;
    __u32 dwMinBitRate;
    __u32 dwMaxBitRate;
    __u32 dwMaxVideoFrameBufferSize;
    __u8  bFrameIntervalType;
    __u32 dwDefaultFrameInterval;
    __u32 *dwFrameInterval;
};

struct uvc_format {
    __u8 type;
    __u8 index;
    __u8 bpp;
    __u8 colorspace;
    __u32 fcc;
    __u32 flags;

    char name[32];

    unsigned int nframes;
    struct uvc_frame *frame;
};

struct uvc_video_chain {
    struct uvc_device *dev;
    struct list_head list;
};

struct uvc_streaming_header {
    U8 bNumFormats;
    U8 bEndpointAddress;
    U8 bTerminalLink;
    U8 bControlSize;
    U8 *bmaControls;
    /* The following fields are used by input headers only. */
    U8 bmInfo;
    U8 bStillCaptureMethod;
    U8 bTriggerSupport;
    U8 bTriggerUsage;
};

enum uvc_buffer_state {
    UVC_BUF_STATE_IDLE  = 0,
    UVC_BUF_STATE_QUEUED    = 1,
    UVC_BUF_STATE_ACTIVE    = 2,
    UVC_BUF_STATE_READY = 3,
    UVC_BUF_STATE_DONE  = 4,
    UVC_BUF_STATE_ERROR = 5,
};

struct uvc_buffer {
    // FIXME:
    //struct vb2_buffer buf;
    struct list_head queue;

    enum uvc_buffer_state state;
    int error;

    void *mem;
    unsigned int length;
    unsigned int bytesused;
    unsigned int packetlen;

    //Synced with UVC component infomation
    unsigned int pUVCFmrBufAddr[8];
    unsigned int framesize;
    unsigned int writeidx;
    unsigned int bufidx;
    unsigned int FoundSOICnt;
    unsigned char bframedrop;
    U32 pts;
};

#define UVC_QUEUE_STREAMING         (1 << 0)
#define UVC_QUEUE_DISCONNECTED      (1 << 1)
#define UVC_QUEUE_DROP_CORRUPTED    (1 << 2)

struct uvc_video_queue {
    //struct vb2_queue queue;
    //struct mutex mutex;           /* Protects queue */

    unsigned int flags;
    unsigned int buf_used;

    spinlock_t irqlock;         /* Protects irqqueue */
    struct list_head irqqueue;
};

struct uvc_streaming {
    struct list_head list;
    struct uvc_device *dev;
    atomic_t active;

    struct usb_interface *intf;
    int intfnum;
    U16 maxpsize;

    struct uvc_streaming_header header;

    struct uvc_streaming_control ctrl;

    /* Buffers queue. */
    void (*decode) (struct urb *urb, struct uvc_streaming *video,
            struct uvc_buffer *buf);

    /*ISO mode*/
    struct urb *urb[UVC_URBS];
    char *urb_buffer[UVC_URBS];
    /*Bulk mode*/
    struct urb *bulkurb[UVC_BULK_URBS];
    struct urb * plastbulkurb;
    unsigned int urb_size;

};

struct uvc_device {
    struct usb_device *udev;
    struct usb_interface *intf;
    U32 quirks;
    int intfnum;
    char name[32];

    /* Video control interface */
    U16 uvc_version;
    U32 clock_frequency;

    struct list_head entities;
    struct list_head chains;

    /* Video Streaming interfaces */
    struct list_head streams;
    atomic_t nstreams;

    /* Status Interrupt Endpoint */
    struct usb_host_endpoint *int_ep;
    struct urb *int_urb;
    U8 *status;
};

extern unsigned int uvc_timeout_param;

/* Core driver */
extern struct usb_driver uvcl_driver;

extern struct usb_host_endpoint *uvc_find_endpoint( \
        struct usb_host_interface *alts, \
        U8 epaddr);
extern void uvc_uninit_video(struct uvc_streaming *stream, int free_buffers);
extern int uvc_video_init(struct uvc_streaming *);
extern int uvc_video_enable(struct uvc_streaming *, int);
extern int uvc_commit_video(struct uvc_streaming *stream,struct uvc_streaming_control *probe);
extern int uvc_init_video(struct uvc_streaming *stream, int gfp_flags);
extern bool uvc_find_tag(U16 usTagID, U8 *pImgAddr, U32 ulLength);
/* Video buffers queue management and debugging. */
extern void uvcl_buffer_dump(struct uvc_buffer *buf, int size);
extern struct uvc_buffer *uvcl_get_buffer(void);
extern int uvcl_buffer_reset(void);
extern int uvcl_buffer_prepare(struct uvc_buffer *buf, int size);
extern struct uvc_buffer *uvc_queue_next_buffer(struct uvc_video_queue *queue,
        struct uvc_buffer *buf);

/* Status */
extern int uvc_status_init(struct uvc_device *dev);
extern void uvc_status_cleanup(struct uvc_device *dev);
extern int uvc_status_start(struct uvc_device *dev);
extern void uvc_status_stop(struct uvc_device *dev);

#endif
