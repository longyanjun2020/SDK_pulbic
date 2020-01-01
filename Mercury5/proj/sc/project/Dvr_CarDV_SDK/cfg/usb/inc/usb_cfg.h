//------------------------------------------------------------------------------
//
//  File        : usb_cfg.h
//  Description : Header file of  USB descriptors and configuration
//  Author      : Alterman
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _USB_CFG_H_
#define _USB_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"
#if (SUPPORT_UVC_FUNC)
#include "mmpf_usb_h264.h"
#if (SUPPORT_UAC)
#include "mmp_aud_inc.h"
#endif
#endif
#include "mmp_usbctl_inc.h"
#include "mmp_usb_inc.h"
#include "fs_cfg.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
/*
 * USB 2.0 Standard
 */
/* Descriptor types (Table 9-5, USB 2.0) */
#define DESC_TYPE_STRING        (3)

/*
 * Mass Storage Class Standard, USB Mass Storage Class - UFI Command Spec
 */
/* Inquiry Data Length */
#define INQ_DATA_SIZE           (36)
/* Inquiry Data Bitmap */
#define INQ_RMB_OFST            (7)
#define INQ_ISO_VER_OFST        (6)
#define INQ_ECMA_VER_OFST       (3)
#define INQ_RES_DATA_FMT_MASK   (0xF)

/*
 * USB Device Class Definition for Video Devices
 */
/* Processing Unit Descriptor bmControls (Table 3-8, UVC 1.1) */
#define PU_CTLBIT_BRIGHTNESS        (0x0001) // Brightness
#define PU_CTLBIT_CONTRAST          (0x0002) // Contrast
#define PU_CTLBIT_HUE               (0x0004) // Hue
#define PU_CTLBIT_SATURATION        (0x0008) // Saturation
#define PU_CTLBIT_SHARPNESS         (0x0010) // Sharpness
#define PU_CTLBIT_GAMMA             (0x0020) // Gamma
#define PU_CTLBIT_WB_TEMP           (0x0040) // White Balance Temperature
#define PU_CTLBIT_WB_COMPON         (0x0080) // White Balance Component
#define PU_CTLBIT_BACKLIGHT_COMPENS (0x0100) // Backlight Compensation
#define PU_CTLBIT_GAIN              (0x0200) // Gain
#define PU_CTLBIT_PWR_LINE_FREQ     (0x0400) // Power Line Frequency
#define PU_CTLBIT_HUE_AUTO          (0x0800) // Hue, Auto
#define PU_CTLBIT_AWB_TEMP          (0x1000) // White Balance Temperature, Auto
#define PU_CTLBIT_AWB_COMPON        (0x2000) // White Balance Component, Auto

//==============================================================================
//
//                              CONFIG CONSTANTS
//
//==============================================================================
/*
 * Command Part
 */
/* bLength of String Descriptor Zero (Table 9-15, USB 2.0) */
#define STR_ZERO_LENGTH         (4)
/* bLength of Manufacturer in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define MFR_STR_LENGTH          (38)
/* bLength of Product in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define PROD_STR_LENGTH         (16)
/* bLength of SerialNumber in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define SN_STR_LENGTH           (34)

/* For detecting USB charger mode,
 * set the timeout value (ms) to wait the 1st EP0 transfer */
#define USB_OP_DTC_TIMEOUT      (1500)

/*
 * Mass Storage Class
 */
/* idVendor in Standard Device Descriptor (Table 9-8, USB 2.0) */
#define MSC_VENDOR_ID           (0x114D)
/* idProduct in Standard Device Descriptor (Table 9-8, USB 2.0) */
#define MSC_PRODUCT_ID          (0x8200)
/* bLength of Manufacturer in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define MSC_MFR_STR_LENGTH      (MFR_STR_LENGTH)
/* bLength of Product in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define MSC_PROD_STR_LENGTH     (PROD_STR_LENGTH)
/* bLength of SerialNumber in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define MSC_SN_STR_LENGTH       (SN_STR_LENGTH)

/*
 * USB Video Class
 */
/* idVendor in Standard Device Descriptor (Table 9-8, USB 2.0) */
#define UVC_VENDOR_ID           (0x114D)
/* idProduct in Standard Device Descriptor (Table 9-8, USB 2.0) */
#define UVC_PRODUCT_ID          (0x8C00)
/* bLength of Manufacturer in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define UVC_MFR_STR_LENGTH      (MFR_STR_LENGTH)
/* bLength of Product in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define UVC_PROD_STR_LENGTH     (PROD_STR_LENGTH)
/* bLength of VC Interface in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define UVC_VC_STR_LENGTH       (28)
/* bLength of VS Interface in UNICODE String Descriptor (Table 9-16, USB 2.0) */
#define UVC_VS_STR_LENGTH       (26)

#if (SUPPORT_USB_HOST_FUNC)
/* USB Host */
#define MAX_SUPPORT_YUV_WIDTH           (1280) //consider mjpg case. TBD
#define MAX_SUPPORT_YUV_HEIGHT          (720)
#define DEVICE_YUV_TYPE                 (ST_NV12)//ST_YUY2,ST_NV12
#define AIT_MJPEG_MAX_VIDEO_FRM_SIZE    (0x80000)
#define ISO_MJPEG_MAX_VIDEO_FRM_SIZE    (0x20000)//from SONiX descriptor AlternateSetting 6
#define UVC_DWMAXVIDEOFRAMESIZE_DESC(_a) \
                                        (_a & 0xFF),\
                                        ((_a>>8) & 0xFF),\
                                        ((_a>>16) & 0xFF),\
                                        ((_a>>24) & 0xFF)

/* UVC tx flow status */
#define USBH_UVC_FRM_TO_MGR             (0)
#define USBH_UVC_FRM_TO_PIPE            (1)
#else
#define MAX_SUPPORT_YUV_WIDTH           (0)
#define MAX_SUPPORT_YUV_HEIGHT          (0)
#define DEVICE_YUV_TYPE                 (ST_UNDEF)
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    MMP_BOOL        bUseISOMode;
    MMP_BOOL        bSyncTime;
    MMP_BOOL        bDecMjpegToPreview;
    MMP_BOOL        bDecMjpegToEncH264;
} USBH_CAM_CFG;

extern USBH_CAM_CFG    gsUsbhCamCfg;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

/* Common Part */
extern unsigned char            gubStrDescZero[STR_ZERO_LENGTH];
extern unsigned char            gubManufacturStrDesc[MFR_STR_LENGTH];
extern unsigned char            gubProductStrDesc[PROD_STR_LENGTH];
extern unsigned char            gubSerialNumStrDesc[SN_STR_LENGTH];

extern unsigned int             gulUsbOpModeDtcTimeOut;

extern MMP_USBPHY_VREF          gususb_vref;
extern MMP_USBPHY_BIAS_CURRENT  gususb_bias_current;
extern MMP_USBPHY_TX_CUR        gususb_tx_cur;
extern MMP_USBPHY_TX_CUR_PLUS   gususb_tx_cur_plus;
extern MMP_USBPHY_SQ            gususb_sq_level;

/* Mass Storage Class */
extern unsigned short           gusMscVendorID;
extern unsigned short           gusMscProductID;

extern unsigned char            *gpMscMfrStrDesc;
extern unsigned char            *gpMscProdStrDesc;
extern unsigned char            *gpMscSnStrDesc;
extern unsigned char            gubMscInquiryData[MSDC_MAX_UNITS][INQ_DATA_SIZE];
extern unsigned char            gubMscUnitWriteProtect[MSDC_MAX_UNITS];

#if (SUPPORT_UVC_FUNC)
/* USB Video Class */
extern unsigned short           gusUvcVendorID;
extern unsigned short           gusUvcProductID;

extern unsigned char            *gpUvcMfrStrDesc;
extern unsigned char            *gpUvcProdStrDesc;
extern unsigned char            gubUvcVidCtrlStrDesc[UVC_VC_STR_LENGTH];
extern unsigned char            gubUvcVidStrmStrDesc[UVC_VS_STR_LENGTH];

extern unsigned short           gusUvcPuControls;
extern unsigned short           gusUvcYUY2MaxWidth;
extern unsigned short           gusUvcYUY2MaxHeight;
extern unsigned short           gusUvcMJPGMaxWidth;
extern unsigned short           gusUvcMJPGMaxHeight;
#endif

#if (SUPPORT_UVC_FUNC)&&(SUPPORT_UAC)
/* USB Audio Class */
extern MMP_AUD_INOUT_PATH       gUacInPath;
extern MMP_AUD_LINEIN_CH        gUacInCh;
extern unsigned char            gbUacDefaultVol;
extern unsigned char            gbUacMaxVol;
extern unsigned char            gbUacMinVol;
#endif

#if (SUPPORT_USB_HOST_FUNC)
/* USB Host */
extern unsigned char            gubusbh_ep0_tx_interval;
extern unsigned char            gubusbh_ep0_rx_interval;
extern unsigned char            gubusbh_ep_tx_interval;
extern unsigned char            gubusbh_ep_rx_interval;

extern MMP_USBPHY_VREF          gususbh_vref;
extern MMP_USBPHY_BIAS_CURRENT  gususbh_bias_current;
extern MMP_USBPHY_TX_CUR        gususbh_tx_cur;
extern MMP_USBPHY_TX_CUR_PLUS   gususbh_tx_cur_plus;
extern MMP_USBPHY_SQ            gususbh_sq_level;

/* UVC YUV(preview) max support setting */
extern unsigned short           gusUsbhMaxYuvWidth;
extern unsigned short           gusUsbhMaxYuvHeight;

/* UVC tx flow status */
extern unsigned char            gubUVCFrmFlowSts;

/* UVC Rx EP buffer count */
extern unsigned short           gusUVCRxEpBufCnt;

/* UVC Rx EP full buffer size */
extern unsigned int             gulUVCRxEpFullBufSz;

/* UVC record frame queue size */
extern unsigned short           gusUVCRecdFrmQSize;

/* UVC record frame buffer count */
extern unsigned short           gusUVCRecdFrmBufCnt;

/* UVC record frame buffer size */
extern unsigned int             gulUVCRecdFrmBufSize;

/* EP Isolation enable */
extern unsigned char            gbUsbEpIsolationEnable;

/* UVC device parsed info. */
extern USB_UVC_DEV_INFO         gUsbh_UvcDevInfo;

/* UVC(rear cam) Mjpeg WiFi Stream info. */
extern USB_UVC_MJPEG_WIFI_CFG   gUsbh_UvcMjpegWifiCfg;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMP_InitUSBHConfig(MMP_UBYTE ubRearCamSel);
MMP_BOOL MMP_IsUSBCamIsoMode(void);
MMP_BOOL MMP_IsSupportSyncUVCTime(void);
MMP_BOOL MMP_IsSupportDecMjpegToPreview(void);
MMP_BOOL MMP_IsSupportDecMjpegToEncH264(void);

#endif // _USB_CFG_H_

