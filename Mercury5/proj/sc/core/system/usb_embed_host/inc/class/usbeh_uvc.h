/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                               USB VIDEO CLASS
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_uvc.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_UVC_H_
#define _USBEH_UVC_H_

#include "usbeh_core.h"
#include "usbeh_class.h"

extern USBEH_CLASS_DRV  g_uvc_drv;

/*
*-------------------------------------------------------------------------------
*                                  Error Codes
*-------------------------------------------------------------------------------
*/
#define USBEH_ERR_UVC_OPEN          (-1000)
#define USBEH_ERR_UVC_START         (-1001)

/*
*-------------------------------------------------------------------------------
*                              UVC Transfer Timeout
*-------------------------------------------------------------------------------
*/
#define USBEH_UVC_XFER_TIMEOUT  (2000)  /* UVC transfer timeout */

/*
*-------------------------------------------------------------------------------
*                           Video Device Class Codes
*-------------------------------------------------------------------------------
*/
/* Video Interface Class Code */
#define CC_VIDEO                (0x0E)

/* Video Interface Subclass Codes */
#if 0 //Andy Liu. Remove redundant definition. They are put in mmp_usb_inc.h.
#define SC_UNDEFINED                    (0x00)
#define SC_VIDEOCONTROL                 (0x01)
#define SC_VIDEOSTREAMING               (0x02)
#define SC_VIDEO_INTERFACE_COLLECTION   (0x03)
#endif

/* Video Interface Protocol Codes */
#define PC_PROTOCOL_UNDEFINED   (0x00)

#if 0 //Andy Liu. Remove redundant definition. They are put in mmp_usb_inc.h .
/* Video Class-Specific Descriptor Types */
#define CS_UNDEFINED            (0x20)
#define CS_DEVICE               (0x21)
#define CS_CONFIGURATION        (0x22)
#define CS_STRING               (0x23)
#define CS_INTERFACE            (0x24)
#define CS_ENDPOINT             (0x25)

/* Video Class-Specific VC Interface Descriptor Subtypes */
#define VC_DESCRIPTOR_UNDEFINED (0x00)
#define VC_HEADER               (0x01)
#define VC_INPUT_TERMINAL       (0x02)
#define VC_OUTPUT_TERMINAL      (0x03)
#define VC_SELECTOR_UNIT        (0x04)
#define VC_PROCESSING_UNIT      (0x05)
#define VC_EXTENSION_UNIT       (0x06)

/* Video Class-Specific VS Interface Descriptor Subtypes */
#define VS_UNDEFINED            (0x00)
#define VS_INPUT_HEADER         (0x01)
#define VS_OUTPUT_HEADER        (0x02)
#define VS_STILL_IMAGE_FRAME    (0x03)
#define VS_FORMAT_UNCOMPRESSED  (0x04)
#define VS_FRAME_UNCOMPRESSED   (0x05)
#define VS_FORMAT_MJPEG         (0x06)
#define VS_FRAME_MJPEG          (0x07)
#define VS_FORMAT_MPEG2TS       (0x0A)
#define VS_FORMAT_DV            (0x0C)
#define VS_COLORFORMAT          (0x0D)
#define VS_FORMAT_FRAME_BASED   (0x10)
#define VS_FRAME_FRAME_BASED    (0x11)
#define VS_FORMAT_STREAM_BASED  (0x12)
#endif

/* Video Class-Specific Request Codes */
#define RC_UNDEFINED            (0x00)
#define USBEH_SET_CUR                 (0x01)
#define USBEH_GET_CUR                 (0x81)
#define USBEH_GET_MIN                 (0x82)
#define USBEH_GET_MAX                 (0x83)
#define USBEH_GET_RES                 (0x84)
#define USBEH_GET_LEN                 (0x85)
#define USBEH_GET_INFO                (0x86)
#define USBEH_GET_DEF                 (0x87)

/* VideoStreaming Interface Control Selectors */
#define VS_CONTROL_UNDEFINED            (0x00)
#define VS_PROBE_CONTROL                (0x01)
#define VS_COMMIT_CONTROL               (0x02)
#define VS_STILL_PROBE_CONTROL          (0x03)
#define VS_STILL_COMMIT_CONTROL         (0x04)
#define VS_STILL_IMAGE_TRIGGER_CONTROL  (0x05)
#define VS_STREAM_ERROR_CODE_CONTROL    (0x06)
#define VS_GENERATE_KEY_FRAME_CONTROL   (0x07)
#define VS_UPDATE_FRAME_SEGMENT_CONTROL (0x08)
#define VS_SYNCH_DELAY_CONTROL          (0x09)

#define UVC10_VS_PROBE_LENGTH   (0x1A)
#define UVC11_VS_PROBE_LENGTH   (0x22)
#define UVC10_VS_COMMIT_LENGTH  (0x1A)
#define UVC11_VS_COMMIT_LENGTH  (0x22)

#define UVC_PAYLOAD_HEADER_SIZE (0x0C)

/*
*-------------------------------------------------------------------------------
*                          AIT-Specific, not UVC spec
*-------------------------------------------------------------------------------
*/
/* Extension Unit Control Selector */
#define XU1_SET_ISP             (0x01) //Name in slave device is EU1_SET_ISP
#define XU1_GET_ISP_RESULT      (0x02) //Name in slave device is EU1_GET_ISP_RESULT
#define XU1_SET_FW_DATA         (0x03) //Name in slave device is EU1_SET_FW_DATA
#define XU1_SET_MMP             (0x04) //Name in slave device is EU1_SET_MMP
#define XU1_GET_MMP_RESULT      (0x05) //Name in slave device is EU1_GET_MMP_RESULT
#define XU1_SET_ISP_EX          (0x06) //Name in slave device is EU1_SET_ISP_EX
#define XU1_GET_ISP_EX_RESULT   (0x07) //Name in slave device is EU1_GET_ISP_EX_RESULT
#define XU1_READ_MEM            (0x08) //Name in slave device is EU1_READ_MMP_MEM
#define XU1_WRITE_MEM           (0x09) //Name in slave device is EU1_WRITE_MMP_MEM
#define XU1_GET_CHIP_INFO       (0x0A) //Name in slave device is EU1_GET_CHIP_INFO
#define XU1_GET_DATA_32         (0x0B) //Name in slave device is EU1_GET_DATA_32
#define XU1_SET_DATA_32         (0x0C) //Name in slave device is EU1_SET_DATA_32
#define XU1_SET_MMP_CMD         (0x0E) //Name in slave device is EU1_SET_MMP_CMD16
#define XU1_GET_MMP_CMD_RESULT  (0x0F) //Name in slave device is EU1_GET_MMP_CMD16_RESULT

/* Format Index, depends on device's descriptors */
#define YUY2_FORMAT_INDEX       (0x01)
#define MJPG_FORMAT_INDEX       (0x02)
#define H264_FORMAT_INDEX       (0x03)

/* YUY2 Frame Index, depends on device's descriptors */
#define YUY2_640x480_30FPS      (0x01)
#define YUY2_1560x1920_30FPS    (0x02)
#define YUY2_320x240_30FPS      (0x03)
#define YUY2_1280x720_30FPS     (0x04)
#define YUY2_1920x1080_30FPS    (0x05)
#define YUY2_800x600_30FPS      (0x06)
#define YUY2_1440x1080_30FPS    (0x07)

/*
*-------------------------------------------------------------------------------
*                          USB Video Class Structures
*-------------------------------------------------------------------------------
*/
/* Video Probe and Commit Control */
typedef struct _USBEH_UVC_PROBE {
    USHORT  bmHint;
    UCHAR   bFormatIndex;
    UCHAR   bFrameIndex;
    UINT    dwFrameInterval;
    USHORT  wKeyFrameRate;
    USHORT  wPFrameRate;
    USHORT  wCompQuality;
    USHORT  wCompWindowSize;
    USHORT  wDelay;
    UCHAR   dwMaxVideoFrameSize[4];
    UCHAR   dwMaxPayloadXferSize[4];
} USBEH_UVC_PROBE;

#define USBEH_UVC_MAX_XU_NUM    (3)

/* Video Interface Collection */
typedef struct _USBEH_UVC_VIC {
    /* VideoControl interface number */
    UCHAR   bVidCtlIF;
    /* VideoStreaming interface number */
    UCHAR   bVidStreamIF;
    /* bTerminalID of TT_STREAMING */
    UCHAR   bStreamingTID;
    /* bTerminalID of ITT_CAMERA */
    UCHAR   bCameraTID;
    /* bUnitID of VC_PROCESSING_UNIT */
    UCHAR   bProcessingUID;
    /* bUnitID of VC_EXTENSION_UNIT */
    UCHAR   bExtensionUID[USBEH_UVC_MAX_XU_NUM];
    /* VideoStreaming endpoint */
    USBEH_EP_CFG    vidStreamEP;
    /* VideoControl interrupt endpoint */
    USBEH_EP_CFG    vidCtlEP;
    /* AudioStream endpoint */
    USBEH_EP_CFG    audStreamEP;
} USBEH_UVC_VIC;

/* Committed Frame Information */
typedef struct _USBEH_UVC_COMMIT {
    USHORT  wWidth;
    USHORT  wHeight;
    UINT    dwMaxPayload;
} USBEH_UVC_COMMIT;

/* UVC Device Handler */
typedef struct _USBEH_UVC {
    USBEH_UVC_VIC       vic;
    USBEH_UVC_COMMIT    yuy2;
    OS_SEM              vidStreamSem;
} USBEH_UVC;

/*
*-------------------------------------------------------------------------------
*                      USB Video Class Public Functions
*-------------------------------------------------------------------------------
*/
extern BOOL USBEH_UVC_Probe(USBEH_STD_DEV_DESC *dev_desc,
                            USBEH_STD_CFG_DESC *cfg_desc);
extern INT  USBEH_UVC_Open(void);
extern INT  USBEH_UVC_Close(void);
extern INT  USBEH_UVC_Start(void);
extern INT  USBEH_UVC_Stop(void);
extern INT  USBEH_UVC_InterfaceSetReq(UCHAR req, UCHAR if_no, UCHAR id,
                            UCHAR cs, USHORT length);
extern INT  USBEH_UVC_InterfaceGetReq(UCHAR req, UCHAR if_no, UCHAR id,
                            UCHAR cs, USHORT length);

extern INT  USBEH_UVC_GetEOF(UINT buf_addr, UINT *size);
extern INT  USBEH_UVC_GetYUY2Frame(UINT buf_addr, UINT *size);
#endif //_USBEH_UVC_H_