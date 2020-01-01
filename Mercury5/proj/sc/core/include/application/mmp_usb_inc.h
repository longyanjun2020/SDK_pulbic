//==============================================================================
//
//  File        : mmp_usb_inc.h
//  Description : INCLUDE File for the USB Driver Function
//  Author      : Bruce Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_USB_INC_H_
#define _MMP_USB_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "os_wrap.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================
/*
 * Definition for USB host & device
 */

/*
 * USB standard device reqeust & descriptors
 */
/* Characteristics of request [USB_20 - 9.3 Table 9-2] */
// Data transfer direction
#define DIR_OUT             (0x00)
#define DIR_IN              (0x80)

// Type
#define TYPE_STANDARD       (0x00)
#define TYPE_CLASS          (0x20)
#define TYPE_VENDOR         (0x40)
#define TYPE_MASK           (0x60)

// Recipient
#define RCPT_DEV            (0x00)
#define RCPT_IF             (0x01)
#define RCPT_EP             (0x02)
#define RCPT_OTHER          (0x03)
#define RCPT_MASK           (0x03)

/* Standard device request codes [USB_20 - 9.4 Table 9-4] */
#define GET_STATUS          (0)
#define CLEAR_FEATURE       (1)
#define SET_FEATURE         (3)
#define SET_ADDRESS         (5)
#define GET_DESCRIPTOR      (6)
#define SET_DESCRIPTOR      (7)
#define GET_CONFIGURATION   (8)
#define SET_CONFIGURATION   (9)
#define GET_INTERFACE       (10)
#define SET_INTERFACE       (11)
#define SYNCH_FRAME         (12)

/* Descriptor Types [USB_20 - 9.4 Table 9-5] */
#define DEVICE_DESCR                                (1)
#define CONFIG_DESCR                                (2)
#define STRING_DESCR                                (3)
#define INTERFACE_DESCR                             (4)
#define ENDPOINT_DESCR                              (5)
#define DEV_QUALIFIER_DESC                          (6)
#define OTHER_SPEED_DESC                            (7)
#define INTERFACE_PWR_DESC                          (8)
#define INTERFACE_ASSOCIATION_DESCR                 (0x0B)

/* Standard Feature Selectors [USB_20 - 9.4 Table 9-6] */
#define FEATURE_ENDPOINT_HALT                       (0)
#define FEATURE_DEV_REMOTE_WAKEUP                   (1)
#define FEATURE_TEST_MODE                           (2)

/* USB bus speed */

#define MMPF_USB_UNKNOWN_SPEED		(0)
#define MMPF_USB_LOW_SPEED       	(1)
#define MMPF_USB_FULL_SPEED      	(2)
#define MMPF_USB_HIGH_SPEED      	(3)


/*
 * USB hub class reqeust & descriptors
 */

/* Hub Class Code [USB_20 - 11.23.1] */
#define HUB_CLASS_CODE      (9)
#define HUB_SUBCLASS_CODE   (0)

/* Hub Class descriptor type [USB_20 - 11.23.2.1 Table 11-13] */
#define HUB_DESC            (0x29)

/* Hub Class request codes [USB_20 - 11.24.2 Table 11-16] */
#define CLEAR_TT_BUF        (8)
#define RESET_TT            (9)
#define GET_TT_STATE        (10)
#define STOP_TT             (11)

/* Hub Class Feature Selectors [USB_20 - 11.24.2 Table 11-17] */
#define C_HUB_LOCAL_POWER   (0)     // Hub
#define C_HUB_OVER_CUR      (1)     // Hub
#define HUB_PORT_CONNECT    (0)     // Port
#define HUB_PORT_EN         (1)     // Port
#define HUB_PORT_SUSPEND    (2)     // Port
#define HUB_PORT_OVER_CUR   (3)     // Port
#define HUB_PORT_RESET      (4)     // Port
#define HUB_PORT_POWER      (8)     // Port
#define HUB_PORT_LS         (9)     // Port
#define C_PORT_CONNECT      (16)    // Port
#define C_PORT_EN           (17)    // Port
#define C_PORT_SUSPEND      (18)    // Port
#define C_PORT_OVER_CUR     (19)    // Port
#define C_PORT_RESET        (20)    // Port
#define HUB_PORT_TEST       (21)    // Port
#define HUB_PORT_INDICATOR  (22)    // Port

/* USB Hub Port Status Bits [USB_20 - 11.24.2.7.1 Table 11-21] */
#define HUB_PORT_SR_CONNECT     (0x0001)
#define HUB_PORT_SR_EN          (0x0002)
#define HUB_PORT_SR_SUSPEND     (0x0004)
#define HUB_PORT_SR_OVER_CUR    (0x0008)
#define HUB_PORT_SR_RESET       (0x0010)
#define HUB_PORT_SR_POWER       (0x0100)
#define HUB_PORT_SR_LS          (0x0200)
#define HUB_PORT_SR_HS          (0x0400)
#define HUB_PORT_SR_TEST        (0x0800)
#define HUB_PORT_SR_INDICATOR   (0x1000)

/* USB Hub Port Status Change Bits [USB_20 - 11.24.2.7.12 Table 11-22] */
#define HUB_PORT_SR_C_CONNECT   (0x0001)
#define HUB_PORT_SR_C_EN        (0x0002)
#define HUB_PORT_SR_C_SUSPEND   (0x0004)
#define HUB_PORT_SR_C_OVER_CUR  (0x0008)
#define HUB_PORT_SR_C_RESET     (0x0010)

/*
 * USB mass storage class related definition
 */
#define MSDC_CTL_BUF_SIZE       (0x400)

#define MSDC_R_FIRSTSIZE        (0x8000)    //< 1st buffer size for read
#define MSDC_R_SECONDSIZE       (0x8000)    //< 2nd buffer size for read
#define MSDC_R_THIRDSIZE        (0x0000)    //< 3rd buffer size for read
#define MSDC_R_FOURTHSIZE       (0x0000)    //< 4th buffer size for read

#define MSDC_W_FIRSTSIZE        (0x8000)    //< 1st buffer size for write
#define MSDC_W_SECONDSIZE       (0x8000)    //< 2nd buffer size for write
#define MSDC_W_THIRDSIZE        (0x0000)    //< 3rd buffer size for write
#define MSDC_W_FOURTHSIZE       (0x0000)    //< 4th buffer size for write
#define MSDC_R_MULTINUM         (2)         //< Count of MSDC multi-read
#define MSDC_W_MULTINUM         (2)         //< Count of MSDC multi-write

#define MSDC_R_TOTAL_SIZE       (MSDC_R_FIRSTSIZE + MSDC_R_SECONDSIZE + MSDC_R_THIRDSIZE + MSDC_R_FOURTHSIZE)
#define MSDC_W_TOTAL_SIZE       (MSDC_W_FIRSTSIZE + MSDC_W_SECONDSIZE + MSDC_W_THIRDSIZE + MSDC_W_FOURTHSIZE)
#if (MSDC_R_TOTAL_SIZE > MSDC_W_TOTAL_SIZE)
#define MSDC_RDWR_BUF_SIZE      (MSDC_R_TOTAL_SIZE)
#else
#define MSDC_RDWR_BUF_SIZE      (MSDC_W_TOTAL_SIZE)
#endif

/*
 * USB video/audio class related definition
 */
#define BFH_FID                                     (0)
#define BFH_EOF                                     (1)
#define BFH_PTS                                     (2)
#define BFH_SCR                                     (3)
#define BFH_RES                                     (4)
#define BFH_STI                                     (5)
#define BFH_ERR                                     (6)
#define BFH_EOH                                     (7)
#define BFH_BIT(x)                                  (1 << x)

#define UVC_EU0_ID                                  (0x05)
#define UVC_EU1_ID                                  (0x06)
#define UVC_EU2_ID                                  (0x02)
#define UVC_EU3_ID                                  (0x03)
#define UVC_OT_ID                                   (0x04)
#if 0 // For ISO Mode
#define UVC_PU_ID                                   (0x02)
#else
#define UVC_PU_ID                                   (0x03)
#endif
#define UVC_PU_ID_ISO                               (0x02)
#define UVC_PU_ID_BULK                              (0x03)
#define UVC_IT_ID                                   (0x01)
#define UAC_FU_ID                                   (0x05)

#define UVC_VC_VCI_EP                               (0x00)
#define UVC_VC_VSI_EP                               (0x01)
#define UAC_AC_AS_EP                                (0x02)

// for VC, AC
/* UVC setup field: bRequest */
#define SET_CUR_CMD                                 0x01
#define GET_CUR_CMD                                 0x81    //current setting attribute
#define GET_MIN_CMD                                 0x82    //minimum setting attribute
#define GET_MAX_CMD                                 0x83    //maximum setting attribute
#define GET_RES_CMD                                 0x84    //resolution attribute
#define GET_LEN_CMD                                 0x85    //data length attribute
#define GET_MEM_CMD                                 0x85
#define GET_INFO_CMD                                0x86    //information attribute
#define GET_DEF_CMD                                 0x87    //default setting attribute

#define CAP_SET_CUR_CMD                             (1 << 0)
#define CAP_GET_CUR_CMD                             (1 << 1)
#define CAP_GET_MIN_CMD                             (1 << 2)
#define CAP_GET_MAX_CMD                             (1 << 3)
#define CAP_GET_RES_CMD                             (1 << 4)
#define CAP_GET_LEN_CMD                             (1 << 5)
#define CAP_GET_MEM_CMD                             (1 << 5)
#define CAP_GET_INFO_CMD                            (1 << 6)
#define CAP_GET_DEF_CMD                             (1 << 7)
#define CAP_SET_MIN_CMD                             (1 << 8)
#define CAP_SET_MAX_CMD                             (1 << 9)
#define CAP_SET_RES_CMD                             (1 << 10)
#define CAP_SET_MEM_CMD                             (1 << 11)
#define CAP_GET_STA_CMD                             (1 << 11)

/* descriptor reference offset */
#define DEVICE_DESCR_VID_LO_OFST                    (0x08)      /* idVendor */
#define DEVICE_DESCR_VID_HI_OFST                    (0x09)
#define DEVICE_DESCR_PID_LO_OFST                    (0x0A)      /* idProduct */
#define DEVICE_DESCR_PID_HI_OFST                    (0x0B)
#define CONFIG_DESCR_SZ_LO_OFST	                    (0x02)      /* wTotalLength */
#define CONFIG_DESCR_SZ_HI_OFST	                    (0x03)
#define INTERFACE_ASSOCIATION_DESCR_IFCS_OFST       (0x04)      /* bFunctionClass */
#define INTERFACE_DESCR_IFNUM_OFST	                (0x02)      /* bInterfaceNumber */
#define INTERFACE_DESCR_IFCS_OFST                   (0x05)      /* bInterfaceClass */
#define INTERFACE_DESCR_IFSUBCS_OFST                (0x06)      /* bInterfaceSubClass */
#define CS_INTERFACE_DESCR_SUBTYPE_OFST	            (0x02)      /* bDescriptorSubType */
#define CS_INTERFACE_DESCR_ID_OFST                  (0x03)      /* bUnitID, bTerminalID */
#define CS_INTERFACE_DESCR_EC0_OFST	                (0x04)      /* guid of extension code 1_4 */
#define CS_INTERFACE_DESCR_EC1_OFST	                (0x08)      /* guid of extension code 2_4 */
#define CS_INTERFACE_DESCR_EC2_OFST	                (0x0C)      /* guid of extension code 3_4 */
#define CS_INTERFACE_DESCR_EC3_OFST	                (0x10)      /* guid of extension code 4_4 */
#define CS_INTERFACE_DESCR_EC_SZ_BASE               (0x19)      /* base size of VC_EXTENSION_UNIT descriptor subtype */
#define CS_INTERFACE_DESCR_EC_CTL_SZ_OFST           (0x17)      /* bmControlSz of VC_EXTENSION_UNIT descriptor subtype */
#define CS_INTERFACE_DESCR_IT_TP_OFST               (0x04)      /* Terminal Type */
#define CS_INTERFACE_DESCR_IT_SZ_BASE               (0x0F)      /* base size of VC_INPUT_TERMINAL descriptor subtype */
#define CS_INTERFACE_DESCR_IT_CTL_SZ_OFST           (0x0E)      /* bmControlSz of VC_INPUT_TERMINAL descriptor subtype */
#define CS_INTERFACE_DESCR_PU_SZ_BASE               (0x09)      /* base size of VC_PROCESSING_UNIT descriptor subtype */
#define CS_INTERFACE_DESCR_PU_CTL_SZ_OFST           (0x07)      /* bmControlSz of VC_PROCESSING_UNIT descriptor subtype */
#define CS_INTERFACE_DESCR_FMT_IDX_OFST             (0x03)      /* bFormatIndex */
#define CS_INTERFACE_DESCR_NUMBERS_OF_FRAME_OFST    (0x04)      /* bNumFrameDescriptors */
#define CS_INTERFACE_DESCR_FRM_IDX_OFST             (0x03)      /* bFrameIndex */
#define CS_INTERFACE_DESCR_FRM_W_LO_OFST            (0x05)      /* wWidth */
#define CS_INTERFACE_DESCR_FRM_W_HI_OFST            (0x06)      /* wWidth */
#define CS_INTERFACE_DESCR_FRM_H_LO_OFST            (0x07)      /* wHeight */
#define CS_INTERFACE_DESCR_FRM_H_HI_OFST            (0x08)      /* wHeight */
#define CS_INTERFACE_DESCR_DEF_FRM_INTVL_OFST       (0x15)      /* dwDefaultFrameInterval */
#define CS_INTERFACE_DESCR_FRM_INTVL_TYP_OFST       (0x19)      /* bFrameIntervalType */
#define ENDPOINT_DESCR_EP_OFST                      (0x02)      /* bEndpointAddress */
#define ENDPOINT_DESCR_XFER_TYP_OFST                (0x03)      /* bmAttributes */

/* Extension Unit Descriptor */
#define CS_INTERFACE_DESCR_GUID_SZ                  (0x10)      /* size of guidExtensionCode */

/* USB standard endpoint descriptor
 * [USB_20 - 9.6.6 Table 9-13]
 */
#define USB_EP_NUM(bEpAddr)	                        ((bEpAddr) & 0x0F)
#define USB_EP_DIR_IN(bEpAddr)	                    (((bEpAddr) & 0x80) == USB_IN_DIR)
#define USB_EP_DIR_OUT(bEpAddr)	                    (((bEpAddr) & 0x80) == USB_OUT_DIR)
#define USB_XFER_TYP(bAttr)	                        ((bAttr) & 0x03)
#define USB_XFER_TYP_ISO(bAttr)	                    (USB_XFER_TYP((bAttr)) == USB_ISO_XFER_TYPE)
#define USB_XFER_TYP_INT(bAttr)	                    (USB_XFER_TYP((bAttr)) == USB_INT_XFER_TYPE)
#define USB_XFER_TYP_CTL(bAttr)	                    (USB_XFER_TYP((bAttr)) == USB_CTL_XFER_TYPE)
#define USB_XFER_TYP_BULK(bAttr)                    (USB_XFER_TYP((bAttr)) == USB_BULK_XFER_TYPE)

// videocontrol interface control selectors
#define VC_CONTROL_UNDEFINED                        0x00
#define VC_VIDEO_POWER_MODE_CONTROL                 0x01
#define VC_REQUEST_ERROR_CODE_CONTROL               0x02
#define VC_RESERVED                                 0x03

// terminal control selectors
#define TE_CONTROL_UNDEFINED                        0x00

// selector unit control selectors
#define SU_CONTROL_UNDEFINED                        0x00
#define SU_INPUT_SELECT_CONTROL                     0x01

// camera terminal control selectors
#define CT_CONTROL_UNDEFINED                        0x00
#define CT_SCANNING_MODE_CONTROL                    0x01
#define CT_AE_MODE_CONTROL                          0x02
#define CT_AE_PRIORITY_CONTROL                      0x03
#define CT_EXPOSURE_TIME_ABSOLUTE_CONTROL           0x04
#define CT_EXPOSURE_TIME_RELATIVE_CONTROL           0x05
#define CT_FOCUS_ABSOLUTE_CONTROL                   0x06
#define CT_FOCUS_RELATIVE_CONTROL                   0x07
#define CT_FOCUS_AUTO_CONTROL                       0x08
#define CT_IRIS_ABSOLUTE_CONTROL                    0x09
#define CT_IRIS_RELATIVE_CONTROL                    0x0A
#define CT_ZOOM_ABSOLUTE_CONTROL                    0x0B
#define CT_ZOOM_RELATIVE_CONTROL                    0x0C
#define CT_PANTILT_ABSOLUTE_CONTROL                 0x0D
#define CT_PANTILT_RELATIVE_CONTROL                 0x0E
#define CT_ROLL_ABSOLUTE_CONTROL                    0x0F
#define CT_ROLL_RELATIVE_CONTROL                    0x10
#define CT_PRIVACY_CONTROL                          0x11
// CT support 
#define CT_CS_VAL (  ( 1 << (CT_AE_MODE_CONTROL - 1    )  ) \
                     ( 1 << (CT_AE_PRIORITY_CONTROL - 1)  ) \
                     ( 1 << (CT_EXPOSURE_TIME_ABSOLUTE_CONTROL - 1)  ) \
                  ) 

// processing unit control selectors
#define PU_CONTROL_UNDEFINED                        0x00
#define PU_BACKLIGHT_COMPENSATION_CONTROL           0x01
#define PU_BRIGHTNESS_CONTROL                       0x02
#define PU_CONTRAST_CONTROL                         0x03
#define PU_GAIN_CONTROL                             0x04
#define PU_POWER_LINE_FREQUENCY_CONTROL             0x05
#define PU_HUE_CONTROL                              0x06
#define PU_SATURATION_CONTROL                       0x07
#define PU_SHARPNESS_CONTROL                        0x08
#define PU_GAMMA_CONTROL                            0x09
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL        0x0A
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL   0x0B
#define PU_WHITE_BALANCE_COMPONENT_CONTROL          0x0C
#define PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL     0x0D
#define PU_DIGITAL_MULTIPLIER_CONTROL               0x0E
#define PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL         0x0F
#define PU_HUE_AUTO_CONTROL                         0x10
#define PU_ANALOG_VIDEO_STANDARD_CONTROL            0x11
#define PU_ANALOG_LOCK_STATUS_CONTROL               0x12

// extension unit control selectors
#define XU_CONTROL_UNDEFINED                        (0x00)
#if USB_UVC_H264==1 
// H264 XU for Customer begin
#define XU_ENCODER_VIDEO_FORMAT_CONTROL             (0x01)
    #define XU_ENCODER_VIDEO_FORMAT_LEN             (10)
#define XU_ENCODER_CONFIGURATION_CONTROL            (0x02)
    #define XU_ENCODER_CONFIGURATION_LEN            (25) 
#define XU_RATE_CONTROL                             (0x03)
    #define XU_RATE_CONTROL_LEN                     (8)
#define XU_FRAME_TYPE_CONTROL                       (0x04)
    #define XU_FRAME_TYPE_LEN                       (1)
#define XU_CAMERA_DELAY_CONTROL                     (0x05)
    #define XU_CAMERA_DELAY_LEN                     (2)
#define XU_FILTER_CONTROL                           (0x06)
    #define XU_FILTER_LEN                           (2)
#endif

// videostreaming interface control selectors
// Interface control request ( wValue )
#define VS_CONTROL_UNDEFINED                        0x00
#define VS_PROBE_CONTROL                            0x01
#define VS_COMMIT_CONTROL                           0x02
#define VS_STILL_PROBE_CONTROL                      0x03
#define VS_STILL_COMMIT_CONTROL                     0x04
#define VS_STILL_IMAGE_TRIGGER_CONTROL              0x05
#define VS_STREAM_ERROR_CODE_CONTROL                0x06
#define VS_GENERATE_KEY_FRAME_CONTROL               0x07
#define VS_UPDATE_FRAME_SEGMENT_CONTROL             0x08
#define VS_SYNCH_DELAY_CONTROL                      0x09

//VC descriptor type 
#define CS_UNDEFINED                                0x20
#define CS_DEVICE                                   0x21
#define CS_CONFIGURATION                            0x22
#define CS_STRING                                   0x23
#define CS_INTERFACE                                0x24
#define CS_ENDPOINT                                 0x25

//Video Interface Class Code
#define SC_UNDEFINED                                0x00
#define SC_VIDEOCONTROL                             0x01
#define SC_VIDEOSTREAMING                           0x02
#define SC_VIDEO_INTERFACE_COLLECTION               0x03

//VC Interface descriptor subtype 
#define VC_DESCRIPTOR_UNDEFINED                     0x00
#define VC_HEADER                                   0x01
#define VC_INPUT_TERMINAL                           0x02
#define VC_OUTPUT_TERMINAL                          0x03
#define VC_SELECTOR_UNIT                            0x04
#define VC_PROCESSING_UNIT                          0x05
#define VC_EXTENSION_UNIT                           0x06

//VS Interface descriptor type
#define VS_UNDEFINED                                0x00
#define VS_INPUT_HEADER                             0x01
#define VS_OUTPUT_HEADER                            0x02
#define VS_STILL_IMAGE_FRAME                        0x03
#define VS_FORMAT_UNCOMPRESSED                      0x04
#define VS_FRAME_UNCOMPRESSED                       0x05
#define VS_FORMAT_MJPEG                             0x06
#define VS_FRAME_MJPEG                              0x07
#define VS_FORMAT_MPEG2TS                           0x0A
#define VS_FORMAT_DV                                0x0C
#define VS_COLORFORMAT                              0x0D
#define VS_FORMAT_FRAME_BASED                       0x10
#define VS_FRAME_FRAME_BASED                        0x11
#define VS_FORMAT_STREAM_BASED                      0x12

//endpoint descriptor subtype
#define EP_UNDEFINED                                0x00
#define EP_GENERAL                                  0x01
#define EP_ENDPOINT                                 0x02
#define EP_INTERRUPT                                0x03

// capability info 
#define INFO_GET_SUPPORT                            0x01
#define INFO_SET_SUPPORT                            0x02
#define INFO_AUTO_MODE_SUPPORT                      0x04
#define INFO_AUTOUPDATE_CONTROL_SUPPORT             0x08
#define INFO_ASYNC_CONTROL_SUPPORT                  0x10

// extension unit command relatives 
#define EU_ISP_CMD_OK                               0x00
#define EU_ISP_CMD_NOT_SUPPORT                      0x80

#define EU0_CMD0_SKYPE_LASTERR                      (0x00)
#define EU0_CMD0_LEN                                (0x0002)
#define EU0_CMD0_MIN                                (0x0000)
#define EU0_CMD0_MAX                                (0x0003)
#define EU0_CMD0_DEF                                (0x0000)
#define EU0_CMD0_RES                                (0x0001)

#define EU0_CMD1_SKYPE_ENCRES                       (0x01)
#define EU0_CMD1_LEN                                (0x0001)
#define EU0_CMD1_MIN                                (0x01)
#define EU0_CMD1_MAX                                (0x0A)
#define EU0_CMD1_DEF                                (0x0A)
#define EU0_CMD1_RES                                (0x01)

#define EU0_CMD2_SKYPE_FRAMERATE                    (0x02)
#define EU0_CMD2_LEN                                (0x0001)
#define EU0_CMD2_MIN                                (0x01)
#define EU0_CMD2_MAX                                (0x1E)
#define EU0_CMD2_DEF                                (0x1E)
#define EU0_CMD2_RES                                (0x01)

#define EU0_CMD3_SKYPE_BITRATE                      (0x03)
#define EU0_CMD3_LEN                                (0x0002)
#define EU0_CMD3_MIN                                (0x0032)
#define EU0_CMD3_MAX                                (0x0BB8)
#define EU0_CMD3_DEF                                (0x01F4)
#define EU0_CMD3_RES                                (0x0032)

#define EU0_CMD4_SKYPE_ENFORCEKEY                   (0x04)
#define EU0_CMD4_LEN                                (0x0001)
#define EU0_CMD4_MIN                                (0x00)
#define EU0_CMD4_MAX                                (0x01)
#define EU0_CMD4_DEF                                (0x00)
#define EU0_CMD4_RES                                (0x01)
                                                    
#define EU0_CMD5_SKYPE_MINQP                        (0x05)
#define EU0_CMD5_LEN                                (0x0001)
#define EU0_CMD5_MIN                                (0x00)
#define EU0_CMD5_MAX                                (0x33)
#define EU0_CMD5_DEF                                (0x1E)
#define EU0_CMD5_RES                                (0x01)

#define EU0_CMD6_SKYPE_MAXQP                        (0x06)
#define EU0_CMD6_LEN                                (0x0001)
#define EU0_CMD6_MIN                                (0x00)
#define EU0_CMD6_MAX                                (0x33)
#define EU0_CMD6_DEF                                (0x32)
#define EU0_CMD6_RES                                (0x01)

#define EU0_CMD7_SKYPE_CABAC                        (0x07)
#define EU0_CMD7_LEN                                (0x0001)
#define EU0_CMD7_MIN                                (0x00)
#define EU0_CMD7_MAX                                (0x01)
#define EU0_CMD7_DEF                                (0x00)
#define EU0_CMD7_RES                                (0x01)

#define EU0_CMDa_SKYPE_FWDAYS                       (0x0A)
#define EU0_CMDa_LEN                                (0x0002)
#define EU0_CMDa_MIN                                (0x0F00)
#define EU0_CMDa_MAX                                (0xFFFF)
#define EU0_CMDa_DEF                                (0x0F00)
#define EU0_CMDa_RES                                (0x0001)

#define EU0_CMDb_SKYPE_PROFILE                      (0x0B)
#define EU0_CMDb_LEN                                (0x0002)
#define EU0_CMDb_MIN                                (0x0000)
#define EU0_CMDb_MAX                                (0xFFFF)
#define EU0_CMDb_DEF                                (0x0000)
#define EU0_CMDb_RES                                (0x0001)

#define EU0_CMDc_SKYPE_LEVEL                        (0x0C)
#define EU0_CMDc_LEN                                (0x0001)
#define EU0_CMDc_MIN                                (0x0A)
#define EU0_CMDc_MAX                                (0x33)
#define EU0_CMDc_DEF                                (0x00)
#define EU0_CMDc_RES                                (0x01)

#define EU0_CMDd_SKYPE_SUPPROFILE                   (0x0D)
#define EU0_CMDd_LEN                                (0x0002)
#define EU0_CMDd_MIN                                (0x0000)
#define EU0_CMDd_MAX                                (0xFFFF)
#define EU0_CMDd_DEF                                (0x0000)
#define EU0_CMDd_RES                                (0x0001)

#define EU0_CMDe_SKYPE_UVCVER                       (0x0E)
#define EU0_CMDe_LEN                                (0x0001)
#define EU0_CMDe_MIN                                (0x10)
#define EU0_CMDe_MAX                                (0x12)
#define EU0_CMDe_DEF                                (0xFF)
#define EU0_CMDe_RES                                (0x01)

#define EU0_CMDf_SKYPE_MODE                         (0x0F)
#define EU0_CMDf_LEN                                (0x0001)
#define EU0_CMDf_MIN                                (0x01)
#define EU0_CMDf_MAX                                (0x04)
#define EU0_CMDf_DEF                                (0x01)
#define EU0_CMDf_RES                                (0x01)


#define EU1_SET_ISP                                 (0x1)   //control selector
#define EU1_SET_ISP_LEN                             (0x08)
#define EU1_SET_ISP_MIN                             (0x0)
#define EU1_SET_ISP_MAX                             (0xFFFFFFFFFFFFFFFF)
#define EU1_SET_ISP_DEF                             (0x0000000000000000)

#define EU1_GET_ISP_RESULT                          (0x2)
#define EU1_GET_ISP_RESULT_LEN                      (0x08)
#define EU1_GET_ISP_RESULT_MIN                      (0x0)
#define EU1_GET_ISP_RESULT_MAX                      (0xFFFFFFFFFFFFFFFF)
#define EU1_GET_ISP_RESULT_DEF                      (0x0000000000000000)

#define EU1_SET_FW_DATA                             (0x03)
#define EU1_SET_FW_DATA_LEN                         (0x20)  //32bytes

#define EU1_SET_MMP                                 (0x04)  //control selector
#define EU1_SET_MMP_LEN                             (0x08)
#define EU1_SET_MMP_MIN                             (0x0)
#define EU1_SET_MMP_MAX                             (0xFFFFFFFFFFFFFFFF)
#define EU1_SET_MMP_DEF                             (0x0000000000000000)

#define EU1_GET_MMP_RESULT                          (0x5)
#define EU1_GET_MMP_RESULT_LEN                      (0x08)
#define EU1_GET_MMP_RESULT_MIN                      (0x0)
#define EU1_GET_MMP_RESULT_MAX                      (0xFFFFFFFFFFFFFFFF)
#define EU1_GET_MMP_RESULT_DEF                      (0x0000000000000000)

#define EU1_SET_ISP_EX                              (0x6)
#define EU1_SET_ISP_EX_LEN                          (0x10)

#define EU1_GET_ISP_EX_RESULT                       (0x7)
#define EU1_GET_ISP_EX_RESULT_LEN                   (0x10)

#define EU1_READ_MMP_MEM                            (0x08)
#define EU1_READ_MMP_MEM_LEN                        (0x10)

#define EU1_WRITE_MMP_MEM                           (0x09)
#define EU1_WRITE_MMP_MEM_LEN                       (0x10)

#define EU1_GET_CHIP_INFO                           (0xA)
#define EU1_GET_CHIP_INFO_LEN                       (0x10)
#define EU1_GET_CHIP_INFO_MIN                       (0x0)
#define EU1_GET_CHIP_INFO_MAX                       (0xFFFFFFFFFFFFFFFF)
#define EU1_GET_CHIP_INFO_DEF                       (0x0000000000000000)

#define EU1_GET_DATA_32			                    (0x0B)
#define EU1_GET_DATA_32_LEN                         (0x20)

#define EU1_SET_DATA_32			                    (0x0C)
#define EU1_SET_DATA_32_LEN                         (0x20)

#define EU1_SET_MMP_CMD16                           (0x0E)
#define EU1_SET_MMP_CMD16_LEN                       (0x10)
#define EU1_SET_MMP_CMD16_MIN                       (0x0)
#define EU1_SET_MMP_CMD16_MAX                       (0xFFFFFFFFFFFFFFFF)
#define EU1_SET_MMP_CMD16_DEF                       (0x0000000000000000)

#define EU1_GET_MMP_CMD16_RESULT                    (0x0F)
#define EU1_GET_MMP_CMD16_RESULT_LEN                (0x10)
#define EU1_GET_MMP_CMD16_RESULT_MIN                (0x0)
#define EU1_GET_MMP_CMD16_RESULT_MAX                (0xFFFFFFFFFFFFFFFF)
#define EU1_GET_MMP_CMD16_RESULT_DEF                (0x0000000000000000)

#define EU1_SET_MMP_CMD64                           (0x0D)
#define EU1_SET_MMP_CMD64_LEN                       (0x40)

// banding filter
#define BAND_DISBALE                                0x00
#define BAND_50HZ                                   0x01
#define BAND_60HZ                                   0x02

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/// USB Events for mass storage class
typedef enum _MMP_USB_EVENT {
    MMP_USB_EVENT_MSDC_READ = 0,
    MMP_USB_EVENT_MSDC_WRITE,
    MMP_USB_EVENT_WR_CALI2SIF,
    MMP_USB_EVENT_NUM
} MMP_USB_EVENT;

typedef enum _MMP_USBH_UPD_UVC_CFG_OP {
    MMP_USBH_UPD_OP_NONE           = 0,
    MMP_USBH_UPD_OPEN_UVC_CB       = 1,
    MMP_USBH_UPD_START_UVC_CB      = 2,
    MMP_USBH_UPD_NALU_TBL          = 3,
    MMP_USBH_UPD_OP_MAX            = 4
} MMP_USBH_UPD_UVC_CFG_OP;

typedef enum _MMP_USBH_REG_UVC_ADDI_CFG_TYP {
    MMP_USBH_REG_TYP_NONE          = 0,
    MMP_USBH_REG_TYP_GUID_EU       = 1,
    MMP_USBH_REG_TYP_MAX           = 2
} MMP_USBH_REG_UVC_ADDI_CFG_TYP;

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void (MMP_USB_Callback) (MMP_USB_EVENT event);
typedef void (MMP_USB_EpCallback) (MMP_UBYTE ep);

typedef MMP_UBYTE uByte;
typedef MMP_UBYTE uWord[2];
typedef MMP_UBYTE uDWord[4];

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/* USB standard device reqeust
 * [USB_20 - 9.3 Table 9-2]
 */
typedef struct __attribute__((packed)) _USB_REQUEST
{
    uByte   bmRequestType;
    uByte   bRequest;
    uWord   wValue;
    uWord   wIndex;
    uWord   wLength;
} EP0_REQUEST;

/* USB standard device descriptor
 * [USB_20 - 9.6.1 Table 9-8]
 */
typedef struct __attribute__((packed)) _USB_DEV_DESC
{
    uByte   bLength;
    uByte   bDescriptorType;
    uWord   bcdUSB;
    uByte   bDeviceClass;
    uByte   bDeviceSubClass;
    uByte   bDeviceProtocol;
    uByte   bMaxPacketSize0;
    uWord   idVendor;
    uWord   idProduct;
    uWord   bcdDevice;
    uByte   iManufacturer;
    uByte   iProduct;
    uByte   iSerialNumber;
    uByte   bNumConfigurations;
} USB_DEV_DESC;

/* USB standard device qualifier descriptor
 * [USB_20 - 9.6.2 Table 9-9]
 */
typedef struct __attribute__((packed)) _USB_DEV_QUAL_DESC
{
    uByte   bLength;
    uByte   bDescriptorType;
    uWord   bcdUSB;
    uByte   bDeviceClass;
    uByte   bDeviceSubClass;
    uByte   bDeviceProtocol;
    uByte   bNumConfigurations;
    uByte   bReserved;
} USB_DEV_QUAL_DESC;

/* USB standard configuration descriptor
 * [USB_20 - 9.6.3 Table 9-10]
 */
typedef struct __attribute__((packed)) _USB_CONFIG_DESC
{
    uByte   bLength;
    uByte   bDescriptorType;
    uWord   wTotalLength;
    uByte   bNumInterfaces;
    uByte   bConfigurationValue;
    uByte   iConfiguration;
    uByte   bmAttributes;
    uByte   bMaxPower;
} USB_CONFIG_DESC;

/* USB standard other speed configuration descriptor
 * [USB_20 - 9.6.4 Table 9-11]
 */
typedef USB_CONFIG_DESC USB_OTHER_SPEED_CONFIG_DESC;

/* USB standard interface descriptor
 * [USB_20 - 9.6.5 Table 9-12]
 */
typedef struct __attribute__((packed)) _USB_INTERFACE_DESC
{
    uByte   bLength;
    uByte   bDescriptorType;
    uByte   bInterfaceNumber;
    uByte   bAlternateSetting;
    uByte   bNumEndpoints;
    uByte   bInterfaceClass;
    uByte   bInterfaceSubClass;
    uByte   bInterfaceProtocol;
    uByte   iInterface;
} USB_INTERFACE_DESC;

/* USB standard endpoint descriptor
 * [USB_20 - 9.6.6 Table 9-13]
 */
typedef struct __attribute__((packed)) _USB_EP_DESC
{
    uByte   bLength;
    uByte   bDescriptorType;
    uByte   bEndpointAddress;
    uByte   bmAttributes;
    uWord   wMaxPacketSize;
    uByte   bInterval;
} USB_EP_DESC;

/* USB standard descriptor head
 */
typedef struct __attribute__((packed)) _USB_DESC_HEAD
{
    uByte   bLength;
    uByte   bDescriptorType;
} USB_DESC_HEAD;

/*
 * USB Hub Class related structure
 */
 
/* USB Hub Descriptor
 * [USB_20 - 11.23.2.1 Table 11-13], The last two fields are variable length
 */
typedef struct __attribute__((packed)) _USB_HUB_DESC
{
    uByte   bDescLength;
    uByte   bDescriptorType;
    uByte   bNbPorts;
    uWord   wHubCharacteristics;
    uByte   bPwrOn2PwrGood;
    uByte   bHubContrCurrent;
    uByte   bTailer[4];
} USB_HUB_DESC;

/* USB Hub Port Status Field, Port Change Field
 * [USB_20 - 11.24.2.7]
 */
typedef struct __attribute__((packed)) _USB_HUB_PORT_STATUS
{
    uWord   wPortStatus;
    uWord   wPortChange;
} USB_HUB_PORT_STATUS;

/*
 * USB video class related structure
 */

/* USB standard video interface collection IAD descriptor
 * [USB_Video_Class_1.1 - 3.6 Table 3-1]
 */
typedef struct __attribute__((packed)) _UVC_INTERFACE_ASSOCIATION_DESC
{
    uByte       bLength;
    uByte       bDescriptorType;
    uByte       bFirstInterface;
    uByte       bInterfaceCount;
    uByte       bFunctionClass;
    uByte       bFunctionSubClass;
    uByte       bFunctionProtocol;
    uByte       iFunction;
} UVC_INTERFACE_ASSOCIATION_DESC;

typedef struct {
    MMP_USHORT  bmHint;
    MMP_USHORT  wIndex; //H byte -> Format Index, L Byte -> Frame Index 
    MMP_USHORT  wIntervalLo;
    MMP_USHORT  wIntervalHi;
    MMP_USHORT  wKeyFrameRate;
    MMP_USHORT  wPFrameRate;
    MMP_USHORT  wCompQuality;
    MMP_USHORT  wCompWinSize;
    MMP_USHORT  wDelay;
    MMP_USHORT  wMaxFrameSizeLo;
    MMP_USHORT  wMaxFrameSizeHi;    
    MMP_USHORT  wMaxPayloadSizeLo;
    MMP_USHORT  wMaxPayloadSizeHi;
} VIDEO_PROBE;

typedef struct {
    MMP_UBYTE   bFormatIndex;
    MMP_UBYTE   bFrameIndex;
    MMP_UBYTE   bCompressIndex;
    MMP_UBYTE   bMaxFrameSize[4];
    MMP_UBYTE   bMaxPayloadSize[4];
} STILL_PROBE;

typedef struct _VC_CMD_CFG {
    MMP_ULONG   bCmdCap;
    MMP_UBYTE   bInfoCap;
    MMP_USHORT  bCmdLen;
    MMP_UBYTE   bInfoLen;
    /*If cmd > 4, the following data is a pointer*/
    MMP_ULONG   dwResVal;
    MMP_ULONG   dwDefVal;
    MMP_ULONG   dwMinVal;
    MMP_ULONG   dwMaxVal;
    MMP_ULONG   dwCurVal;
} VC_CMD_CFG;

typedef struct _UVC_VIDEO_PAYLOAD_HEADER {
    MMP_UBYTE   bHLE;
    MMP_UBYTE   bBFH;
    MMP_UBYTE   bPTS[4];
    MMP_UBYTE   bSCR[4];
    MMP_UBYTE   bSOFNUM[2];
} UVC_VIDEO_PAYLOAD_HEADER;

/* USB Host parsed UVC device infomation */
typedef struct __attribute__((packed)) _USB_UVC_DEV_INFO
{
    MMP_ULONG   ulVIDPID;
    MMP_UBYTE   bEnumCplt;              /* status of UVC enum complete or not */
    MMP_UBYTE   bParseDone;             /* status of parse CONFIGURATION Descriptor done or not */
    /* Below information filled by driver parsing */
    MMP_USHORT  wSzConfigDesc;          /* wTotalLength of CONFIGURATION Descriptor Type */
    MMP_UBYTE   bIfNoVC;                /* bInterfaceNumber of SC_VIDEOCONTROL Subclass */
    MMP_UBYTE   bIfNoVS;                /* bInterfaceNumber of SC_VIDEOSTREAMING Subclass */
    MMP_UBYTE   bIdEU;                  /* bUnitID of VC_EXTENSION_UNIT descriptor subtype */
    MMP_UBYTE   bIdIT;                  /* bTerminalID of VC_INPUT_TERMINAL descriptor subtype */
    MMP_UBYTE   bIdPU;                  /* bUnitID of VC_PROCESSING_UNIT descriptor subtype */
    MMP_UBYTE   bXferTyp;               /* Transfer Type of SC_VIDEOSTREAMING */
    MMP_UBYTE   bXferEpNum;             /* bEndpointAddress of SC_VIDEOSTREAMING */
    MMP_UBYTE   bPrevwFmtIdx;           /* bFormatIndex of VS_FORMAT_xxx descriptor subtype which used to preview */
    MMP_UBYTE   bPrevwMaxResFrmIdx;     /* bFrameIndex of VS_FRAME_xxx descriptor subtype which is the max resolution */
    MMP_USHORT  wPrevwMaxWidth;         /* wWidth of bPrevwMaxResFrmIdx */
    MMP_USHORT  wPrevwMaxHeight;        /* wHeight of bPrevwMaxResFrmIdx */
    MMP_ULONG   dwPrevwFrmIntvl;        /* dwFrameInterval of bPrevwMaxResFrmIdx */
} USB_UVC_DEV_INFO;

/* AIT rear cam MJPEG WIFI infomation filled by AP */
typedef struct __attribute__((packed)) _USB_UVC_MJPEG_WIFI_CFG
{
    MMP_BOOL    bEnWiFi;
    MMP_ULONG   dwTargetWidth;
    MMP_ULONG   dwTargetHeight;
    MMP_BOOL    bTargetCtl;
    MMP_BOOL    bLimitCtl;
    MMP_ULONG   dwTargetSz;
    MMP_ULONG   dwLimitSz;
    MMP_USHORT  wMaxTrialCnt;
    MMP_UBYTE   mQlty;
    MMP_USHORT  wFps;
    MMP_ULONG   dwkbps;
} USB_UVC_MJPEG_WIFI_CFG;

typedef struct __attribute__((packed)) _USBH_UVC_H264_NALU_CFG
{
    MMP_UBYTE                   ubSpsOfst;          // From *UVC_HDR to SPS_TYPE_HDR(0x67)
    MMP_UBYTE                   ubPpsOfst;          // From *UVC_HDR to PPS_TYPE_HDR(0x68)
    MMP_UBYTE                   ubSpsSize;          // Size of SPS_TYPE w/o startcode
    MMP_UBYTE                   ubPpsSize;          // Size of PPS_TYPE w/o startcode
    MMP_UBYTE                   ubIFAddNaluSize;    // Size of additional nalu w/o startcode in IDR frame
    MMP_UBYTE                   ubPFAddNaluSize;    // Size of additional nalu w/o startcode in NIDR frame
    MMP_UBYTE                   ubIFOfst;           // From *PAYLOAD_DATA(1st startcode) to IDR_TYPE_HDR(0x65)
    MMP_UBYTE                   ubPFOfst;           // From *PAYLOAD_DATA(1st startcode) to NIDR_TYPE_HDR(0x41)
} USBH_UVC_H264_NALU_CFG;

typedef struct __attribute__((packed)) _USBH_UVC_CB_FUNC_CFG
{
    MMP_UBYTE                   ubCamSel;
    MMP_USHORT                  usStreamResIdx;     // Ref : PCAM_RESOL_ID
    MMP_USHORT                  usStreamW;
    MMP_USHORT                  usStreamH;
    MMP_USHORT                  usStreamFmt;        // Ref : MMPS_3GPRECD_VIDEO_FORMAT
} USBH_UVC_CB_FUNC_CFG;

#endif //_MMP_USB_INC_H_
