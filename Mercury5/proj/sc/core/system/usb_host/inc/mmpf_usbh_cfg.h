//==============================================================================
//
//  File        : mmpf_usbh_cfg.h
//  Description : Header file for the USB HOST configurations
//  Author      : Bruce_Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_CFG_H_
#define _MMPF_USBH_CFG_H_

#include "usb_cfg.h"
#include "mmpf_usb_h264.h"
//==============================================================================
//
//  USB Bus Timing
//
//==============================================================================

/* Wait for set port reset [USB20 - 7.1.7.5, 50ms for root, 10ms for hub] */
/* According to meter spec, reset signal must be kept for at least 20ms */
#define USB_SET_ROOT_PORT_RESET_STALL   (50 + 1)
#define USB_SET_PORT_RESET_STALL        (10 + 1)

/* Wait for reset recovery [USB20 - 7.1.7.3, 10ms] */
#define USB_PORT_RESET_RCY_STALL        (10 + 1)

/* Wait for reset recovery additional gap for ZZ1 device */
#define USB_PORT_RESET_RCY_STALL_ADDI   (33 + 1)

/* Wait for hub port power-on [USB20 - 11.23.2] */
#define USB_SET_PORT_POWER_STALL        (8)

/* Wait for hub port power-on to till power good additional gap */
#define USB_PWR_ON_2_PWR_GOOD_ADDI      (1)

/* Wait for set device address [USB20 - 9.2.6.3, 2ms] */
#define USB_SET_DEV_ADDR_STALL          (2 + 1)

//==============================================================================
//
//  UVC Device Option
//
//==============================================================================

#define USBH_UVC_DEVICE_BQL31       (0)     // 45
#define USBH_UVC_DEVICE_CC007       (1)     // 08
#define USBH_UVC_DEVICE_SR270       (2)     // 65
#define USBH_UVC_DEVICE_WV215       (3)     // 25
#define USBH_UVC_DEVICE_NONE        (0xFF)  // Remove from core, do not keep device/project dependency
#define USBH_UVC_DEVICE_OPT         (USBH_UVC_DEVICE_NONE) /* UVC device select, HARD CODE test */

//==============================================================================
//
//  Maximum Endpoints Supported
//
//==============================================================================

#define USBH_MAX_EP_NUM             (8)     /* USBOTG controllers has 8 EPs */

//==============================================================================
//
//  Endpoints Assignment
//
//==============================================================================

#define USBH_HOST_RX_EP_NUM         (1)     /* Endpoint that host receive video */
#define USBH_HOST_TX_EP_NUM         (2)     /* Endpoint that host transmit video */
#define USBH_DEVICE_TX_EP_NUM       (1)     /* Endpoint that device transmit video */
#define USBH_DEVICE_RX_EP_NUM       (2)     /* Endpoint that device receive video */

#define USBH_HUB_INT_EP             (7)     /* Endpoint used in host side */

//==============================================================================
//
//  Device Base Address
//
//==============================================================================

#define USBH_DEV_BASE_ADDR          (3)

//==============================================================================
//
//  USB Host Working Buffer Size
//
//==============================================================================

#define USBH_EP0_DATA_BUF_SIZE      (512)

//==============================================================================
//
//  Supported UVC Device YUV Config
//
//==============================================================================

#if (DEVICE_YUV_TYPE == ST_YUY2)
    #define DEVICE_TX_YUV_FRAME_SIZE    (gusUsbhMaxYuvWidth * gusUsbhMaxYuvHeight * 2)
#elif (DEVICE_YUV_TYPE == ST_NV12)
    #define DEVICE_TX_YUV_FRAME_SIZE    ((gusUsbhMaxYuvWidth * gusUsbhMaxYuvHeight * 3) >> 1)
#elif (DEVICE_YUV_TYPE == ST_UNDEF)
    #define DEVICE_TX_YUV_FRAME_SIZE    (gusUsbhMaxYuvWidth * gusUsbhMaxYuvHeight * 2)
#endif

#define PREVW_BUF_SIZE                  (DEVICE_TX_YUV_FRAME_SIZE)

//==============================================================================
//
//  UVC H264 NALU info
//  descriptions:
//  AIT_H264_SPS_TYPE_OFST  : From *UVC_HEADER to H264_SPS_TYPE_HDR, 
//  AIT_H264_SPS_SIZE       : Size of SPS_TYPE w/o start code, 
//  AIT_H264_PPS_TYPE_OFST  : From *UVC_HEADER to H264_PPS_TYPE_HDR, 
//  AIT_H264_PPS_SIZE       : Size of PPS_TYPE w/o start code, 
//  AIT_H264_IFRAME_HDR_OFST: From *PAYLOAD_DATA to H264_IDR_TYPE_HDR, 
//  AIT_H264_PFRAME_HDR_OFST: From *PAYLOAD_DATA to H264_NIDR_TYPE_HDR, 
//  AIT_H264_PFRAME_CNT     : GOP size, 
//==============================================================================

#define AIT_H264_INVALID_HDR_OFST   (0x7F) // Becareful, this value DO NOT be the same as glUvcNaluTbl[]

#if (USBH_UVC_DEVICE_OPT == USBH_UVC_DEVICE_BQL31)
#define AIT_H264_SPS_TYPE_OFST      (0x30)
#define AIT_H264_PPS_TYPE_OFST      (0x3F)
#define AIT_H264_SPS_SIZE           (0x0B)
#define AIT_H264_PPS_SIZE           (0x04)
#define AIT_H264_IF_ADD_NALU_NUM    (0)
#define AIT_H264_PF_ADD_NALU_NUM    (0)
#define AIT_H264_IFRAME_HDR_OFST    (0x1B)
#define AIT_H264_PFRAME_HDR_OFST    (0x04)
#define AIT_H264_PFRAME_CNT         (30)
#elif (USBH_UVC_DEVICE_OPT == USBH_UVC_DEVICE_CC007)
#define AIT_H264_SPS_TYPE_OFST      (0x30)
#define AIT_H264_PPS_TYPE_OFST      (0x58)
#define AIT_H264_SPS_SIZE           (0x24)
#define AIT_H264_PPS_SIZE           (0x04)
#define AIT_H264_IF_ADD_NALU_NUM    (1)
#define AIT_H264_PF_ADD_NALU_NUM    (1)
#define AIT_H264_IF_ADD_01_SIZE     (0x17)
#define AIT_H264_PF_ADD_01_SIZE     (0x0C)
#define AIT_H264_IFRAME_HDR_OFST    (0x4F)
#define AIT_H264_PFRAME_HDR_OFST    (0x14)
#define AIT_H264_PFRAME_CNT         (300)
#elif (USBH_UVC_DEVICE_OPT == USBH_UVC_DEVICE_SR270)
#define AIT_H264_SPS_TYPE_OFST      (0x30)
#define AIT_H264_PPS_TYPE_OFST      (0x3F)//1080p:0x3F, 720p:0x3E, 480p:0x3D
#define AIT_H264_SPS_SIZE           (0x0B)//1080p:0x0B, 720p:0x0A, 480p:0x09
#define AIT_H264_PPS_SIZE           (0x04)
#define AIT_H264_IF_ADD_NALU_NUM    (0)
#define AIT_H264_PF_ADD_NALU_NUM    (0)
#define AIT_H264_IFRAME_HDR_OFST    (0x1B)//1080p:0x1B, 720p:0x1A, 480p:0x19
#define AIT_H264_PFRAME_HDR_OFST    (0x04)
#define AIT_H264_PFRAME_CNT         (30)
#elif (USBH_UVC_DEVICE_OPT == USBH_UVC_DEVICE_WV215)
#define AIT_H264_SPS_TYPE_OFST      (0x30)
#define AIT_H264_PPS_TYPE_OFST      (0x3E)
#define AIT_H264_SPS_SIZE           (0x0A)
#define AIT_H264_PPS_SIZE           (0x04)
#define AIT_H264_IF_ADD_NALU_NUM    (0)
#define AIT_H264_PF_ADD_NALU_NUM    (0)
#define AIT_H264_IFRAME_HDR_OFST    (0x1A)
#define AIT_H264_PFRAME_HDR_OFST    (0x04)
#define AIT_H264_PFRAME_CNT         (30)
#endif

//==============================================================================
//
//  Timeout
//
//==============================================================================

#define USBH_ADT_CFG_LINK_INFO_WTID         (1)//0x0C
#define USBH_CHECK_ID_TIMEOUT               (6)//60
#define USBH_WAIT_DEV_CONN_TIMEOUT_CNT      (10)
#define USBH_WAIT_DEV_CONN_CHECK_INTERVAL   (100)
#define USBH_SEM_TIMEOUT_CNT                (1000)
#define USBH_SEM_PERM_WAIT                  (0)         // Permanent wait
#define USBH_EP0_TX_TIMEOUT_CNT             (0x50000)   // 0x000E8C, ~3724us, 
#define USBH_EP0_RX_TIMEOUT_CNT             (0x2D00000) // 0x0DA340, ~893760us
#define USBH_SYNC_UVC_TIME_INTERVAL         (60000)

//==============================================================================
//
//  MISC.
//
//==============================================================================

#define USBH_INIT_UVC_MD_EN                 (0) // 0: initialize disable, 1: initialize enable

#define USBH_OPT_DBG_LOG_EN                 (0) // 0: disable, 1: enable USBH optional debug log
#define USBH_ADDI_CHECK_EN                  (0) // 0: disable, 1: check more but CPU take more loading, recommend for debug only

#endif //_MMPF_USBH_CFG_H_
