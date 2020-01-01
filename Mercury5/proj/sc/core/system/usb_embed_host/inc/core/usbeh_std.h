/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                            USB STANDARD STRUCTURES
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_std.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_STD_H_
#define _USBEH_STD_H_

#include "usbeh_cfg.h"

/*
*-------------------------------------------------------------------------------
*                              USB Max Packet Size
*-------------------------------------------------------------------------------
*/
#define FS_CTL_XFER_MAX_PKT_SIZE    (64)
#define HS_CTL_XFER_MAX_PKT_SIZE    (64)
#define SS_CTL_XFER_MAX_PKT_SIZE    (512)

#define FS_BULK_XFER_MAX_PKT_SIZE   (64)
#define HS_BULK_XFER_MAX_PKT_SIZE   (512)
#define SS_BULK_XFER_MAX_PKT_SIZE   (1024)

#define FS_INT_XFER_MAX_PKT_SIZE    (64)
#define HS_INT_XFER_MAX_PKT_SIZE    (1024)
#define SS_INT_XFER_MAX_PKT_SIZE    (1024)

#define FS_ISO_XFER_MAX_PKT_SIZE    (1023)
#define HS_ISO_XFER_MAX_PKT_SIZE    (1024)
#define SS_ISO_XFER_MAX_PKT_SIZE    (1024)

/*
*-------------------------------------------------------------------------------
*                       USB Request & Descriptor Macro Utility
*-------------------------------------------------------------------------------
*/
#define USBEH_GETB(w)           (w)
#define USBEH_SETB(w,v)         ((w) = (UCHAR)(v))
#define USBEH_GETW(w)           ((w)[0] | ((w)[1] << 8))
#define USBEH_SETW(w,v)         ((w)[0] = (UCHAR)(v),           \
                                 (w)[1] = (UCHAR)((v) >> 8))
#define USBEH_GETDW(w)          ((w)[0] | ((w)[1] << 8) |       \
                                ((w)[2] << 16) |                \
                                ((w)[3] << 24))
#define USBEH_SETDW(w,v)        ((w)[0] = (UCHAR)(v),           \
                                 (w)[1] = (UCHAR)((v) >> 8),    \
                                 (w)[2] = (UCHAR)((v) >> 16),   \
                                 (w)[3] = (UCHAR)((v) >> 24))
/*
*-------------------------------------------------------------------------------
*                          USB Device Request Structure
*-------------------------------------------------------------------------------
*/
#define DEV_REQ_SIZE            (8)

/* Standard Request Codes, refer to USB 2.0 Spec. Table 9-4 */
typedef enum _USBEH_STD_REQ_CODE {
    REQ_GET_STATUS          = 0,
    REQ_CLEAR_FEATURE       = 1,
    REQ_SET_FEATURE         = 3,
    REQ_SET_ADDRESS         = 5,
    REQ_GET_DESCRIPTOR      = 6,
    REQ_SET_DESCRIPTOR      = 7,
    REQ_GET_CONFIGURATION   = 8,
    REQ_SET_CONFIGURATION   = 9,
    REQ_GET_INTERFACE       = 10,
    REQ_SET_INTERFACE       = 11
} USBEH_STD_REQ_CODE;

/* Setup Data Format, refer to USB 2.0 Spec. Table 9-2 */
/* bmRequestType bitmap */
#define DEV_REQ_OUT             (0x00)
#define DEV_REQ_IN              (0x80)
#define DEV_REQ_DIR(p_req)      ((p_req)->bmRequestType & 0x80)
#define DEV_REQ_STD             (0x00)
#define DEV_REQ_CLASS           (0x20)
#define DEV_REQ_VENDOR          (0x40)
#define DEV_REQ_TYPE(p_req)     ((p_req)->bmRequestType & 0x60)
#define DEV_REQ_DEVICE          (0x00)
#define DEV_REQ_INTERFACE       (0x01)
#define DEV_REQ_ENDPOINT        (0x02)
#define DEV_REQ_OTHER           (0x03)
#define DEV_REQ_RCPT(p_req)     ((p_req)->bmRequestType & 0x1F)

/* Standard Feature Selectors, refer to USB 2.0 Spec. Table 9-6 */
#define DEV_REMOTE_WAKEUP       (0x01)
#define EP_HALT                 (0x00)
#define DEV_TEST_MODE           (0x02)

typedef struct _USBEH_DEV_REQ {
    UCHAR   bmRequestType;
    UCHAR   bRequest;
    UCHAR   wValue[2];
    UCHAR   wIndex[2];
    UCHAR   wLength[2];
} USBEH_DEV_REQ;

/*
*-------------------------------------------------------------------------------
*                         USB Device Descriptor Structure
*-------------------------------------------------------------------------------
*/
#define STD_DEV_DESC_SIZE       (18)

/* Standard Descriptor Types, refer to USB 2.0 Spec. Table 9-5 */
typedef enum _USBEH_STD_DESC_TYPE {
    DEVICE_DESC             = 0x0100,
    CONFIGURATION_DESC      = 0x0200,
    STRING_DESC             = 0x0300,
    INTERFACE_DESC          = 0x0400,
    ENDPOINT_DESC           = 0x0500,
    DEVICE_QUALIFIER_DESC   = 0x0600,
    OTHER_SPEED_CFG_DESC    = 0x0700
} USBEH_STD_DESC_TYPE;

/* Standard Device Descriptor, refer to USB 2.0 Spec. Table 9-8 */
typedef struct _USBEH_STD_DEV_DESC {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bcdUSB[2];
    UCHAR   bDeviceClass;
    UCHAR   bDeviceSubClass;
    UCHAR   bDeviceProtocol;
    UCHAR   bMaxPacketSize0;
    UCHAR   idVendor[2];
    UCHAR   idProduct[2];
    UCHAR   bcdDevice[2];
    UCHAR   iManufacturer;
    UCHAR   iProduct;
    UCHAR   iSerialNumber;
    UCHAR   bNumConfigurations;
} USBEH_STD_DEV_DESC;

/*
*-------------------------------------------------------------------------------
*                    USB Configuration Descriptor Structure
*-------------------------------------------------------------------------------
*/
#define STD_CHG_DESC_SIZE       (9)

/* Standard Configuration Descriptor, refer to USB 2.0 Spec. Table 9-10 */
typedef struct _USBEH_STD_CFG_DESC {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   wTotalLength[2];
    UCHAR   bNumInterface;
    UCHAR   bConfigurationValue;
    UCHAR   iConfiguration;
    UCHAR   bmAttributes;
    UCHAR   bMaxPower;
} USBEH_STD_CFG_DESC;

/*
*-------------------------------------------------------------------------------
*                      USB Interface Descriptor Structure
*-------------------------------------------------------------------------------
*/
#define STD_IF_DESC_SIZE        (9)

/* Standard Interface Descriptor, refer to USB 2.0 Spec. Table 9-12 */
typedef struct _USBEH_STD_IF_DESC {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bInterfaceNumber;
    UCHAR   bAlternateSetting;
    UCHAR   bNumEndpoints;
    UCHAR   bInterfaceClass;
    UCHAR   bInterfaceSubClass;
    UCHAR   bInterfaceProtocol;
    UCHAR   iInterface;
} USBEH_STD_IF_DESC;

/*
*-------------------------------------------------------------------------------
*                       USB Endpoint Descriptor Structure
*-------------------------------------------------------------------------------
*/
#define STD_EP_DESC_SIZE        (7)

/* bEndpointAddress bitmap */
#define EP_DESC_NUM(p_desc)     ((p_desc)->bEndpointAddress & 0x0F)
#define EP_DIR_OUT              (0x00)
#define EP_DIR_IN               (0x80)
#define EP_DIR(p_desc)          ((p_desc)->bEndpointAddress & 0x80)
/* bmAttributes bitmap */
#define EP_CTL_XFER             (0x00)
#define EP_ISO_XFER             (0x01)
#define EP_BULK_XFER            (0x02)
#define EP_INT_XFER             (0x03)
#define EP_XFER_TYPE(p_desc)    ((p_desc)->bmAttributes & 0x03)
/* wMaxPacketSize bitmap */
#define EP_DESC_PKT_SIZE_MASK   (0x07FF)
#define EP_0_MORE_TXN           (0x0000)
#define EP_1_MORE_TXN           (0x0800)
#define EP_2_MORE_TXN           (0x1000)

/* Standard Endpoint Descriptor, refer to USB 2.0 Spec. Table 9-13 */
typedef struct _USBEH_STD_EP_DESC {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bEndpointAddress;
    UCHAR   bmAttributes;
    UCHAR   wMaxPacketSize[2];
    UCHAR   bInterval;
} USBEH_STD_EP_DESC;

#endif //_USBEH_STD_H_