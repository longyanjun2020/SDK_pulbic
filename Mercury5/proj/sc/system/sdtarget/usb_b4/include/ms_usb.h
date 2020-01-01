#ifndef	_MSUSB_H_
#define	_MSUSB_H_

/*
 * Standard requests
 */
#define USB_REQ_GET_STATUS		    0x00
#define USB_REQ_CLEAR_FEATURE		0x01
#define USB_REQ_SET_FEATURE		    0x03
#define USB_REQ_SET_ADDRESS		    0x05
#define USB_REQ_GET_DESCRIPTOR		0x06
#define USB_REQ_SET_DESCRIPTOR		0x07
#define USB_REQ_GET_CONFIGURATION	0x08
#define USB_REQ_SET_CONFIGURATION	0x09
#define USB_REQ_GET_INTERFACE		0x0A
#define USB_REQ_SET_INTERFACE		0x0B
#define USB_REQ_SYNCH_FRAME		    0x0C

/*
 * USB Packet IDs (PIDs)
 */
#define USB_PID_OUT                 0xe1
#define USB_PID_ACK                 0xd2
#define USB_PID_IN                  0x69
#define USB_PID_STALL               0x1e

#define USB_ENDPOINT_DIR_MASK		0x80
#define USB_ENDPOINT_XFERTYPE_MASK	0x03	/* in bmAttributes */
#define USB_ENDPOINT_XFER_BULK		2
#define USB_ENDPOINT_XFER_INT		3

#define USB_ST_NOERROR			0
#define USB_ST_NORESPONSE		0xfc
#define USB_ST_STALL			0xec

#define USB_DIR_OUT			    0
#define USB_DIR_IN			    0x80

#define USB_TYPE_MASK			(0x03 << 5)
#define USB_TYPE_STANDARD		(0x00 << 5)
#define USB_TYPE_CLASS			(0x01 << 5)
#define USB_TYPE_VENDOR			(0x02 << 5)
#define USB_TYPE_RESERVED		(0x03 << 5)

#define USB_RECIP_MASK			0x1f
#define USB_RECIP_DEVICE		0x00
#define USB_RECIP_INTERFACE		0x01
#define USB_RECIP_ENDPOINT		0x02
#define USB_RECIP_OTHER			0x03

#define EP0C_SET_ADDRESS        1   /* 1st enum cmd is to set dev address */
#define EP0C_GET_MAX_EP0        2   /* fetch functions max EP0, 1st enum req */
#define EP0C_GET_STD_DEV_DESC   3   /* 2nd enum req, get std descriptor */
#define EP0C_GET_CONFIG         4   /* read config descriptor only */
#define EP0C_GET_FULL_CONFIG    5   /* read entire config descriptor */
#define EP0C_SET_CONFIG         6   /* set config 0 prior to probe */
#define EP0C_SET_FEATURE        7   /* set a feature, like OTG */
#define EP0C_CLEAR_FEATURE        8   /* set a feature, like OTG */

#define USB_DT_DEVICE			0x01
#define USB_DT_CONFIG			0x02
#define USB_DT_STRING			0x03
#define USB_DT_INTERFACE		0x04
#define USB_DT_ENDPOINT			0x05
#define	USB_DT_DEVICE_QUALIFIER		0x06
#define	USB_DT_OTHER_SPEED		    0X07
#define	USB_DT_INTERFACE_POWER		0x08
#define	USB_DT_OTG			        0x09
#define USB_DT_DEVICE_SIZE		     18
#define USB_DT_DEVICE_QUALIFIER_SIZE 10
#define USB_DT_CONFIG_SIZE		      9
#define USB_DT_INTERFACE_SIZE		  9
#define USB_DT_ENDPOINT_SIZE		  7
#define	USB_DT_OTG_SIZE			      3

#define	USB_OTG_SRP			0x01	/* bit 0 of bmAttributes */
#define	USB_OTG_HNP			0x02	/* bit 1 of bmAttributes */

#define MAX_BITS_BYTE    (8)
#define MAX_BITS_SHORT   (16)
#define MAX_BITS_3BYTE   (24)
#define MAX_BITS_INT     (32)

#define POSITION_VALUE_8    (0x100)
#define POSITION_VALUE_16   (U32)(0x10000)
#define POSITION_VALUE_24   (U32)(0x1000000)

#define BIT_MASK(n)    ( ~(~(0L)<<n) )

#define	ENDPOINT_HALT			0x00

#define usb_pipeout(pipe)	((((pipe) >> PIPEDEF_DIR) & 1) ^ 1)
#define usb_pipein(pipe)	(((pipe) >> PIPEDEF_DIR) & 1)
#define usb_pipeendpoint(pipe)	(((pipe) >> PIPEDEF_EP) & 0xf)
#define usb_pipetype(pipe)	(((pipe) >> PIPEDEF_ATTR) & 3)
#define usb_pipeisoc(pipe)	(usb_pipetype((pipe)) == PIPE_ISOCHRONOUS)
#define usb_pipebulk(pipe)	(usb_pipetype((pipe)) == PIPE_BULK)

#define	usb_sndctrlpipe(endpoint)	((PIPE_CONTROL << PIPEDEF_ATTR) | \
	(PIPE_OUT << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define	usb_rcvctrlpipe(endpoint)	((PIPE_CONTROL << PIPEDEF_ATTR) | \
	(PIPE_IN  << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define	usb_sndisopipe(endpoint)	((PIPE_ISOCHRONOUS<< PIPEDEF_ATTR) | \
	(PIPE_OUT << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define	usb_sndbulkpipe(endpoint)	((PIPE_BULK << PIPEDEF_ATTR) | \
	(PIPE_OUT << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define	usb_rcvbulkpipe(endpoint)	((PIPE_BULK << PIPEDEF_ATTR) | \
	(PIPE_IN << PIPEDEF_DIR) | (((endpoint) << PIPEDEF_EP) &0xf))

#define  MSD_BOT_CSW_LENGTH        0x0D
#define  MSD_BOT_CBW_LENGTH        0x1F
#define  MSD_BOT_CBW_CB_LENGTH     0x1F

/* All standard descriptors have these 2 fields in common */
typedef	struct {
	S8  bLength;
	S8  bDescriptorType;
} usb_descriptor_header;


/* Device descriptor */
struct usb_device_descriptor {
	U8  bLength;
	U8  bDescriptorType;
	U16 bcdUSB;
	U8  bDeviceClass;
	U8  bDeviceSubClass;
	U8  bDeviceProtocol;
	U8  bMaxPacketSize0;
	U16 idVendor;
	U16 idProduct;
	U16 bcdDevice;
	U8  iManufacturer;
	U8  iProduct;
	U8  iSerialNumber;
	U8  bNumConfigurations;
};

/* Endpoint descriptor */
typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U8  bEndpointAddress;
	U8  bmAttributes;
	U16 wMaxPacketSize;
	U8  bInterval;
	U8  bRefresh;
	U8  bSynchAddress;
   	U8  *extra;   /* Extra descriptors */
	S32 extralen;
} usb_endpoint_descriptor;

typedef	struct {
        U8  bLength;
        U8  bDescriptorType;
        U8  bEndpointAddress;
        U8  bmAttributes;
        U16 wMaxPacketSize;
        U8  bInterval;
} usb_function_endpoint_descriptor;

/* Interface descriptor */
typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U8  bInterfaceNumber;
	U8  bAlternateSetting;
	U8  bNumEndpoints;
	U8  bInterfaceClass;
	U8  bInterfaceSubClass;
	U8  bInterfaceProtocol;
	U8  iInterface;
  	usb_endpoint_descriptor *endpoint;
   	U8  *extra;   /* Extra descriptors */
	S32 extralen;
} usb_interface_descriptor;

typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U8  bInterfaceNumber;
	U8  bAlternateSetting;
	U8  bNumEndpoints;
	U8  bInterfaceClass;
	U8  bInterfaceSubClass;
	U8  bInterfaceProtocol;
	U8  iInterface;
} usb_function_interface_descriptor;

typedef	struct {
	usb_interface_descriptor *altsetting;
	S32 act_altsetting;		/* active alternate setting */
	S32 num_altsetting;		/* number of alternate settings */
	S32 max_altsetting;             /* total memory allocated */
 	struct usb_driver *driver;	/* driver */
	void *private_data;
} usb_interface;

/* Configuration descriptor information.. */
typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U16 wTotalLength;
	U8  bNumInterfaces;
	U8  bConfigurationValue;
	U8  iConfiguration;
	U8  bmAttributes;
	U8  MaxPower;
	usb_interface *interface;
   	U8 *extra;   /* Extra descriptors */
	S32 extralen;
} usb_config_descriptor;

typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U16 wTotalLength;
	U8  bNumInterfaces;
	U8  bConfigurationValue;
	U8  iConfiguration;
	U8  bmAttributes;
	U8  bMaxPower;
} usb_function_config_descriptor;

/* String descriptor */
typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U16 wData[1];
} usb_string_descriptor;

typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U8  bmAttributes;	/* bit 0=SRP; bit 1=HNP */
} usb_otg_descriptor;

typedef	struct {
	U8  bLength;
	U8  bDescriptorType;
	U16 bcdHID;
	U8  bCountryCode;
	U8  bNumDescriptors;
	U8  bClassDescriptorType;
	U16 wDescriptorLength;
} usb_hid_descriptor;

typedef	struct {
	U8  bDescriptorType;
	U16 wDescriptorLength;
} hid_optional_descriptor;


typedef struct {
    U8  bLength;
    U8  bDescriptorType;

    U16 bcdUSB;
    U8  bDeviceClass;
    U8  bDeviceSubClass;
    U8  bDeviceProtocol;
    U8  bMaxPacketSize0;
    U8  bNumConfigurations;
    U8  bRESERVED;
} usb_qualifier_descriptor;

struct usb_device{
	U8	core;
	struct	usb_device_descriptor descriptor;/* Descriptor */
	usb_config_descriptor *config;	/* All of the configs */
	usb_config_descriptor *actconfig;/* the active configuration */
	S8 **rawdescriptors;		/* Raw descriptors for each config */
};

void USB_Change_USB_State(U8 toUSB,USB_VAR *gUSBStruct);
void USB_SWOP_Setup(struct devrequest *sP);
void USB_SWOP_Device_Descriptor(void *vP);
void USB_SWOP_Endpoint_Descriptor(void *vP);
void USB_SWOP_Config_Descriptor(void *vP);
S8 USB_Send_Stall (U8 ep,USB_VAR *gUSBStruct);
U8 otgIsUSBConfiged(USB_VAR *gUSBStruct);

#endif	/* _MSUSB_H_	*/

