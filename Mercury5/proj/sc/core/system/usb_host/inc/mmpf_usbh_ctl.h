//==============================================================================
//
//  File        : mmpf_usbh_ctl.h
//  Description : Header file for the USB HOST controller function
//  Author      : Bruce_Chien
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_USBH_CTL_H_
#define _MMPF_USBH_CTL_H_

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "lib_retina.h"
#include "mmpf_typedef.h"

#if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)
#include "mmpf_usbh_cfg.h"
#include "mmpf_usbh_core.h"
#include "mmpf_usbh_uvc.h"
#include "aitu_ringbuf.h"
#include "mmp_graphics_inc.h"

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef MMP_ULONG u32;

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

#define DMA3_RX_LAST_PKT_PATCH              (1)
#define EN_USBH_CHECK_RINGBUF_STS           (1)
#define EN_EP0_SEM                          (1)
#define EN_REMOVE_TRAN_HW_TIMER             (1)     // Remove CheckTranTimerAttr, merge transaction timer check into CheckFrmRxTimerAttr
#define EN_USBH_ALWAYS_INPUT_FRM            (1)     //1: always input frame to Mgr, 0: input frame depend on ubUVCRecdEn,
#define EN_DBGLOG_TRIGUSBDMA                (0)
#define EN_USB_EP_ISOLATION                 (1)     //0: disable, 1: enable semaphore to isolate endpoint 0 and endpoint 1, prevent work together
#define EN_MAINT_JPG_WIFI_WR_PTR            (0)     //0: disable, 1: enable MMPF_USBH self maintain WR/RD ptr for scheduled data

#define SEM_RES_0                           (0)
#define SEM_RES_1                           (1)

/* YUV420 color pattern */
#define YUV420_Y_BLACK_COLOR                (0x00)
#define YUV420_UV_BLACK_COLOR               (0x80)

/* USB Connect Speed */
#define USB_XFER_SPEED                      (MMPF_USB_HIGH_SPEED)

/* USB Max Packet Size */
#define EP0_MAX_PACKET_SIZE                 (64)
#if (USB_XFER_SPEED == MMPF_USB_FULL_SPEED)
#define BULK_MAX_PACKET_SIZE                (64)
#define BULK_PACKET_CNT(n)                  ((n+63) >> 6)
#elif (USB_XFER_SPEED == MMPF_USB_HIGH_SPEED)
#define BULK_MAX_PACKET_SIZE                (512)
#define BULK_PACKET_CNT(n)                  ((n+511) >> 9)
#endif

#define ISO_MAX_PACKET_SIZE                 (1024)

#if(ISO_MAX_PACKET_SIZE > BULK_MAX_PACKET_SIZE)
#define USB_RX_MAX_PACKET_SIZE              ISO_MAX_PACKET_SIZE
#else
#define USB_RX_MAX_PACKET_SIZE              BULK_MAX_PACKET_SIZE
#endif

/* bRequest (AIT specified) */
#define ROOT_DIR                            (0x00)
    #define ROOT_DIR_DATA_SZ                (0x04)
#define GET_FILE_LIST                       (0x01)
    #define FILE_ATTR_READ_ONLY             (0x01)
    #define FILE_ATTR_HIDDEN                (0x02)
    #define FILE_ATTR_DIR                   (0x10)
#define SELECT_ENTRY                        (0x02)
    #define SELECT_ENTRY_DATA_SZ            (0x08)
#define START_XFER                          (0x03)
    #define START_XFER_DATA_SZ              (0x04)
#define ABORT_XFER                          (0x04)
    #define ABORT_XFER_DATA_SZ              (0x04)

/* Descriptor size */
#define DEVICE_DESCR_SIZE                   (0x12)
#define CONFIG_DESCR_SIZE                   (0x09)
#define STRING_DESCR_SIZE                   (0x04)
#define INTERFACE_DESCR_SIZE                (0x09)
#define EP_DESCR_SIZE                       (0x07)
#define DEV_QUALIFIER_DESCR_SIZE            (0x0A)
#define OTHER_SPEED_DESCR_SIZE              (0x09)

#define MSDC_GET_MAX_LUN                    (0xFE)

/* Mass Storage Related */
#define CBW_PACKET_SIZE                     (0x1F)
#define CSW_PACKET_SIZE                     (0x0D)
#define REQ_SENSE_DATA_SIZE                 (0x12)
#define INQUIRY_DATA_SIZE                   (0x24)
#define RTL_BULKOUT_SIZE                    (118)

/* Mass Storage Device Command */
#define CMD_AIT_SCSI_OPCODE                 (0xFA)  /* AIT-Specific command */

/* OTG Example Related */
#define BULK_IN_EP                          (1)
#define BULK_OUT_EP                         (2)

/* Standard Feature Selectors @ USB 2.0 Table 9-6 */
#define DEV_REMOTE_WAKEUP                   (0x01)
#define EP_HALT                             (0x00)
#define DEV_TEST_MODE                       (0x02)

/* Error message info relatives */
#define USBH_ERR_MSG_QUEUE_SIZE             (64)    // Queue size of error mesage
#define USBH_ERR_STR_LEN                    (32)
#define USBH_ERR_NONE                       (0)
#define USBH_ERR_ROTE_DMA_FAIL              (1)     // Rotate DMA NG
#define USBH_ERR_MOVE_DMA_FAIL              (2)     // Move DMA NG
#define USBH_ERR_BAD_UVC_HDR_YUV            (3)     // No UVC header in transfer of YUV frame
#define USBH_ERR_BAD_UVC_HDR_H264           (4)     // No UVC header in transfer of H264 frame
#define USBH_ERR_BAD_JPG_HDR                (5)     // First packet of MJPEG frame not 0xFF 0xD8
#define USBH_ERR_BAD_PACKET_SIZE            (6)     // Packet size greater than max packet size
#define USBH_ERR_BAD_FRM_SIZE               (7)     // Video frame size greater than max video frame size
#define USBH_ERR_BAD_EOI                    (8)     // Can not find EOI (w/EOF) over MMPF_USBH_LOOKUP_MAX_CNT packet
#define USBH_ERR_WRONG_WR_PTR               (9)     // WR pointer wrong, check update case
#define USBH_ERR_DEC_BUF_FULL               (10)    // Decode JPG buffer full
#define USBH_ERR_RX_BUF_FULL                (11)    // USB Rx buffer full, not enough to receive one frame
#define USBH_ERR_RECD_INFO_Q_FULL           (12)    // Record frame info queue full(for size, timestamp, start offset)
#define USBH_ERR_RING_BUF_ST                (13)    // Ring buffer overflow/underflow status, status, size, rd, wr
#define USBH_ERR_RING_BUF_ST2               (14)    // Ring buffer overflow/underflow status2, rd_wrap. wr_wrap
#define USBH_ERR_PREVW_BUF_FULL             (15)    // Preview buffer full
#define USBH_ERR_PREVW_ROTE_BUF_FULL        (16)    // Preview rotate buffer full
#define USBH_ERR_OV_STRM_SZ                 (17)    // Over WiFi Limit size
#define USBH_ERR_BAD_EP0_RX_SZ              (18)    // Endpoint 0 Rx count > 64Byte
#define USBH_ERR_BAD_EP0_RX_ACC_SZ          (19)    // Endpoint 0 Rx accumulated size over 4096Byte
#define USBH_ERR_COMP_ERR          			(20)    // Component is not available

#if 1 // For ISO mode
/* Backup & restore memory, use to reduce MoveDMA operation */
#define USBH_BACKUP_DATA_NUM                (3)
#define USBH_BACKUP_DATA_FULL_SIZE          (12)
#endif

/* Endpoint 0 memory */
#define EP0_SETUP_PACKET_SIZE               (8)
#define EP0_DATA_PACKET_SIZE                (4096)

/* Receive packet memory */
#define EP_RX_TMP_BUF_SIZE                  (1024+32)   // Use when out of receive packet buffer
#define EP_RX_BUF_SIZE                      (8192)

#define EP_RX_BUF_CNT_ISO                   (192)       // From RECD_FRM_BUF_SZ*RECD_FRM_BUF_CNT/EP_RX_BUF_SIZE
#define EP_RX_BUF_CNT_BULK                  (8)
#if (EP_RX_BUF_CNT_ISO > EP_RX_BUF_CNT_BULK)
#define EP_RX_BUF_CNT                       (EP_RX_BUF_CNT_ISO)
#else
#define EP_RX_BUF_CNT                       (EP_RX_BUF_CNT_BULK)
#endif

/* Record frame memory */
#define RECD_FRM_BUF_SZ_ISO                 (ISO_MJPEG_MAX_VIDEO_FRM_SIZE)
#define RECD_FRM_BUF_SZ_BULK                (0x10000)
#if (RECD_FRM_BUF_SZ_ISO > RECD_FRM_BUF_SZ_BULK)
#define RECD_FRM_BUF_SZ                     (RECD_FRM_BUF_SZ_ISO)
#else
#define RECD_FRM_BUF_SZ                     (RECD_FRM_BUF_SZ_BULK)
#endif

#define RECD_FRM_BUF_CNT_ISO                (3)
#define RECD_FRM_BUF_CNT_BULK               (40)
#if (RECD_FRM_BUF_CNT_ISO > RECD_FRM_BUF_CNT_BULK)
#define RECD_FRM_BUF_CNT                    (RECD_FRM_BUF_CNT_ISO)
#else
#define RECD_FRM_BUF_CNT                    (RECD_FRM_BUF_CNT_BULK)
#endif

#define RECD_FRM_Q_SZ_ISO                   (48)
#define RECD_FRM_Q_SZ_BULK                  (40)
#if (RECD_FRM_Q_SZ_ISO > RECD_FRM_Q_SZ_BULK)
#define RECD_FRM_Q_SZ                       (RECD_FRM_Q_SZ_ISO)
#else
#define RECD_FRM_Q_SZ                       (RECD_FRM_Q_SZ_BULK)
#endif

#define RECD_FRM_CPLT_Q_SZ                  (40)    // # queue to keep(TRUE/FALSE) record frame if complete(one frame) by this moveDMA operation (cut UVC header), About (gulUVCRecdFrmBufSize/EP_RX_BUF_SIZE)
#define RECD_FRM_MAX_SZ_BULK                (RECD_FRM_BUF_CNT_BULK*RECD_FRM_BUF_SZ_BULK) // Estimate worst case: 10x (avg frame size 34953B/frame <= 8Mbps/30fps)

/* Preview frame memory */
#define PREVW_FRM_BUF_CNT                   (3)
#define PREVW_FRM_ROTE_BUF_CNT              (3)
#if (DEVICE_YUV_TYPE == ST_YUY2)
#define PREVW_FRM_CPLT_Q_SZ                 (75)    // About (PREVW_BUF_SIZE/EP_RX_BUF_SIZE)
#else
#define PREVW_FRM_CPLT_Q_SZ                 (57)    // About (PREVW_BUF_SIZE/EP_RX_BUF_SIZE), # queue to keep(TRUE/FALSE) preview frame if complete(one frame) by this moveDMA operation (cut UVC header)
#endif

/* Related constant */
#define AIT_H264_FRM_START_CODE             (0x00000001)
#define UVC_PH_LEN                          sizeof(UVC_VIDEO_PAYLOAD_HEADER)
#define PKT_64BYTE_LEN                      (64) // (UVC_PH_LEN + FRAME_PAYLOAD_HEADER_SZ)

/* Error handle limitation */
#define FRM_TRAN_TIMEOUT_MIN                (1) // Min timeout to check transaction transfer in millisecond
#define FRM_RX_TIMEOUT_HDL_0                (0) // Handle of check frame Rx lost TH
#define FRM_RX_TIMEOUT_HDL_1                (1) // Handle of check frame Rx lost TH2
#define FRM_RX_TIMEOUT_MAX_HDL              (2) // Max handles to check frame Rx lost
#define FRM_RX_LOST_MIN_TH                  (4) // Min threshold to check frame Rx lost count
#define FRM_SEQ_NO_LOST_MIN_TH              (1) // Min threshold to check frame seq. no lost count

#if (SUPPORT_DEC_MJPEG_TO_PREVIEW)
/* gbDecJpgErrSts */
#define DEC_JPG_MARKER_ERR                  (0x04) /* SW status refer to JPG_INT_DEC_MARKER_ERR */
#define DEC_JPG_HUFFMAN_ERR                 (0x08) /* SW status refer to  JPG_INT_DEC_HUFFMAN_ERR */
#define DEC_JPG_NONBASELINE                 (0x10) /* SW status refer to  JPG_INT_DEC_NONBASELINE */
#define DEC_JPG_CLR_ERR_STS                 (0x00) /* Clear SW status */

#define MAX_MJPEG_DEC_COMPBUF_SLOT_NUM      (4)
#endif
//==============================================================================
//
//                              MACRO FUNC
//
//==============================================================================

#define UGETB(w) (w)
#define USETB(w,v) (w = v)
#define UGETW(w) ((w)[0] | ((w)[1] << 8))
#define USETW(w,v) ((w)[0] = (uByte)(v), (w)[1] = (uByte)((v) >> 8))
#define UGETDW(w) ((w)[0] | ((w)[1] << 8) | ((w)[2] << 16) | ((w)[3] << 24))
#define USETDW(w,v) ((w)[0] = (uByte)(v), \
             (w)[1] = (uByte)((v) >> 8), \
             (w)[2] = (uByte)((v) >> 16), \
             (w)[3] = (uByte)((v) >> 24))

// bTerminalID of Video Control Input Terminal ==> UVC_IT_ID
// bUnitID of Video Control Processing Unit ==> UVC_PU_ID
// bInterfaceNumber of Video Control Interface SubClass ==> UVC_VC_VCI_EP
// bInterfaceNumber of Video Streaming Interface ==> UVC_VC_VSI_EP
// bEndpointAddress of VS Video Input Header Descriptor ==> attribute->ep_num of RX
// bUnitID of Video Control Extension Unit ==> UVC_EU3_ID,UVC_EU2_ID,UVC_EU1_ID,UVC_EU0_ID
#define MMPF_USBH_SetVCCmd(ubReq,usVal,usLen,pubDataBuf)                MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetVCCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)     MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_SetVSCmd(ubReq,usVal,usLen,pubDataBuf)                MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVS), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetVSCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)     MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), (gUsbh_UvcDevInfo.bIfNoVS), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_SetCTCmd(ubReq,usVal,usLen,pubDataBuf)                MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdIT<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetCTCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)     MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdIT<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_SetPUCmd(ubReq,usVal,usLen,pubDataBuf)                MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdPU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetPUCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)     MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdPU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)

#define MMPF_USBH_SetEU0Cmd(ubReq,usVal,usLen,pubDataBuf)               MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetEU0Cmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_SetEU1Cmd(ubReq,usVal,usLen,pubDataBuf)               MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetEU1Cmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_SetEU2Cmd(ubReq,usVal,usLen,pubDataBuf)               MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetEU2Cmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)    MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((gUsbh_UvcDevInfo.bIdEU<<8)|gUsbh_UvcDevInfo.bIfNoVC), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)

#define MMPF_USBH_SetFUCmd(ubReq,usVal,usLen,pubDataBuf)                MMPF_USBH_SetClassIfCmd(ubReq, (usVal<<8), ((UAC_FU_ID<<8)|UAC_AC_AS_EP), usLen, (MMP_UBYTE *)pubDataBuf)
#define MMPF_USBH_GetFUCmd(ubReq,usVal,usLen,pulDataLen,pubDataBuf)     MMPF_USBH_GetClassIfCmd(ubReq, (usVal<<8), ((UAC_FU_ID<<8)|UAC_AC_AS_EP), usLen, (MMP_ULONG *)pulDataLen, (MMP_UBYTE *)pubDataBuf)

//------------------------------------------------------------------------------
//  Function    : _MMPF_USBH_ASSERT
//  Description : assert function
//------------------------------------------------------------------------------
#define _MMPF_USBH_ASSERT(expr, file, line)  {  do {                    \
                                                RTNA_DBG_Str(0, expr);  \
                                                RTNA_DBG_Str(0, file);  \
                                                RTNA_DBG_Long(0, line); \
                                                } while(1); }

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_InitRBufHandle
//  Description : Initialize the ring buffer handler
//------------------------------------------------------------------------------
#define MMPF_USBH_InitRBufHandle(psRHdl,pvBuf,pulSize)      AUTL_RingBuf_Init((AUTL_RINGBUF *)psRHdl, (void *)pvBuf, pulSize)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_StrictAdvRBufRdPtr
//  Description : Advance the read pointer of ring buffer
//------------------------------------------------------------------------------
#define MMPF_USBH_StrictAdvRBufRdPtr(psRHdl, pulSize)       AUTL_RingBuf_StrictCommitRead((AUTL_RINGBUF *)psRHdl, pulSize)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_StrictAdvRBufWrPtr
//  Description : Advance the write pointer of ring buffer
//------------------------------------------------------------------------------
#define MMPF_USBH_StrictAdvRBufWrPtr(psRHdl, pulSize)       AUTL_RingBuf_StrictCommitWrite((AUTL_RINGBUF *)psRHdl, pulSize)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_AdvRBufRdPtr
//  Description : Advance the read pointer of ring buffer
//------------------------------------------------------------------------------
#define MMPF_USBH_AdvRBufRdPtr(psRHdl, pulSize)             AUTL_RingBuf_CommitRead((AUTL_RINGBUF *)psRHdl, pulSize)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_AdvRBufWrPtr
//  Description : Advance the write pointer of ring buffer
//------------------------------------------------------------------------------
#define MMPF_USBH_AdvRBufWrPtr(psRHdl, pulSize)             AUTL_RingBuf_CommitWrite((AUTL_RINGBUF *)psRHdl, pulSize)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_IsRBufFull
//  Description : Check if ring buffer full
//------------------------------------------------------------------------------
#define MMPF_USBH_IsRBufFull(psRHdl)                        AUTL_RingBuf_Full((AUTL_RINGBUF *)psRHdl)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_GetRBufFreeSpace
//  Description : Get the available free space in ring buffer
//------------------------------------------------------------------------------
#define MMPF_USBH_GetRBufFreeSpace(psRHdl, pulSpace)        AUTL_RingBuf_SpaceAvailable((AUTL_RINGBUF *)psRHdl, (MMP_ULONG *)pulSpace)

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_CheckRBufSpaceSts
//  Description : Check the space status in ring buffer
//------------------------------------------------------------------------------
#if (EN_USBH_CHECK_RINGBUF_STS)
#define MMPF_USBH_CheckRBufSpaceSts(psRHdl) {   MMP_LONG    lRet;   \
                                                MMP_ULONG   ulFreeSize; \
                                                lRet = MMPF_USBH_GetRBufFreeSpace(psRHdl, &ulFreeSize);   \
                                                if(lRet < RINGBUF_SUCCESS)  \
                                                {   \
                                                MMPF_USBH_SendErrMsg(USBH_ERR_RING_BUF_ST, (MMP_ULONG)lRet, __LINE__,0,0);    \
                                                MMPF_USBH_SendErrMsg(USBH_ERR_RING_BUF_ST, ulFreeSize, __LINE__,0,0);    \
                                                MMPF_USBH_SendErrMsg(USBH_ERR_RING_BUF_ST, (MMP_ULONG)(psRHdl.ptr.rd), (MMP_ULONG)(psRHdl.ptr.wr),0,0);    \
                                                MMPF_USBH_SendErrMsg(USBH_ERR_RING_BUF_ST2, (MMP_ULONG)(psRHdl.ptr.rd_wrap), (MMP_ULONG)(psRHdl.ptr.wr_wrap),0,0);    }}
#define MMPF_USBH_CheckRBufOvSts(plRet)     {   if(plRet < RINGBUF_SUCCESS)  \
                                                {   DBG_S(0, "[ERR]: Ring Buffer Ov:");   \
                                                    DBG_L(0, plRet); \
                                                    DBG_S(0, "! ");   \
                                                    DBG_S(0, __func__);   \
                                                    DBG_S(0, ",");   \
                                                    DBG_L(0, __LINE__);   \
                                                    DBG_S(0, ".\r\n");   }}
#define MMPF_USBH_CheckRBufUnSts(plRet)     {   if(plRet < RINGBUF_SUCCESS)  \
                                                {   DBG_S(0, "[ERR]: Ring Buffer Un:");   \
                                                    DBG_L(0, plRet); \
                                                    DBG_S(0, "! ");   \
                                                    DBG_S(0, __func__);   \
                                                    DBG_S(0, ",");   \
                                                    DBG_L(0, __LINE__);   \
                                                    DBG_S(0, ".\r\n");   }}
#else
#define MMPF_USBH_CheckRBufSpaceSts(psRHdl) {}
#define MMPF_USBH_CheckRBufOvSts(psRHdl)    {}
#define MMPF_USBH_CheckRBufUnSts(psRHdl)    {}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPF_USBH_GetRBufDatCnt
//  Description : Get how many data available in the ring buffer.
//------------------------------------------------------------------------------
#define MMPF_USBH_GetRBufDatCnt(psRHdl, pulCnt)           AUTL_RingBuf_DataAvailable((AUTL_RINGBUF *)psRHdl, (MMP_ULONG *)pulCnt)

//------------------------------------------------------------------------------
//  Function    : CurRBufRdPtr
//  Description : Get current read pointer of ring buffer
//------------------------------------------------------------------------------
#define CurRBufRdPtr(psRHdl)                                (psRHdl.ptr.rd)

//------------------------------------------------------------------------------
//  Function    : CurRBufRdWrap
//  Description : Get current read wrap of ring buffer
//------------------------------------------------------------------------------
#define CurRBufRdWrap(psRHdl)                               (psRHdl.ptr.rd_wrap)

//------------------------------------------------------------------------------
//  Function    : CurRBufWrPtr
//  Description : Get current write pointer of ring buffer
//------------------------------------------------------------------------------
#define CurRBufWrPtr(psRHdl)                                (psRHdl.ptr.wr)

//------------------------------------------------------------------------------
//  Function    : CurRBufWrWrap
//  Description : Get current read wrap of ring buffer
//------------------------------------------------------------------------------
#define CurRBufWrWrap(psRHdl)                               (psRHdl.ptr.wr_wrap)

//------------------------------------------------------------------------------
//  Function    : CurRBufSz
//  Description : Get size of ring buffer
//------------------------------------------------------------------------------
#define CurRBufSz(psRHdl)                                   (psRHdl.size)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* EP0 Control Transfer State Machine */
typedef enum _USB_EP0_STATE {
    EP0_IDLE,
    EP0_IN_DATA_PHASE,
    EP0_OUT_DATA_PHASE,
    EP0_IN_STATUS_PHASE,
    EP0_OUT_STATUS_PHASE,
    EP0_STALL
} USB_EP0_STATE;

/* UVC Host Stream Receive State Machine */
typedef enum _UVC_RX_STATE {
    RX_INACTIVE = 0x00,
    RX_UNKNOWN_PKT,
    RX_VALID_PKT,
    RX_1ST_DATA_PKT,
    RX_RES_DATA_PKT
} UVC_RX_STATE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/* Command Block Wrapper (CBW), exactly 31 bytes */
typedef struct __attribute__((packed)) _CMD_BLOCK_WRAPPER
{
    MMP_ULONG                   dCBWSignature;
        #define CBW_SIGANTURE       (0x43425355)
    MMP_ULONG                   dCBWTag;
    MMP_ULONG                   dCBWDataTxLength;
    MMP_UBYTE                   bmCBWFlags;
        #define DATA_DIR_IN         (0x80)
        #define DATA_DIR_OUT        (0x00)
    MMP_UBYTE                   bCBWLUN;
    MMP_UBYTE                   bCBWCBLength;
#if 1
    MMP_UBYTE                   bCBWCB[16];
#else
    // Inquiry
    MMP_UBYTE                   bOPCode;
    MMP_UBYTE                   bReserved;
    MMP_UBYTE                   bPageCode;
    MMP_USHORT                  bAllocLen;
    MMP_UBYTE                   bControl;
    MMP_UBYTE                   bPad[10];
#endif
} CMD_BLOCK_WRAPPER;

/* Command Status Wrapper (CSW), exactly 13 bytes */
typedef struct _CMD_STATUS_WRAPPER {
    MMP_ULONG                   dCSWSignature;
        #define CSW_SIGANTURE       (0x53425355)
    MMP_ULONG                   dCSWTag;
    MMP_ULONG                   dCSWDataResidue;
    MMP_UBYTE                   bCSWStatus;
        #define CMD_PASSED          (0x00)
        #define CMD_FAILED          (0x01)
        #define PHASE_ERR           (0x02)
} CMD_STATUS_WRAPPER;

/* USB OTG Handler for Example */
typedef struct __attribute__((packed)) _USB_OTG_HANDLE
{
    USB_EP0_STATE               ep0_state;
    MMP_UBYTE                   ep0_setup_buf[EP0_SETUP_PACKET_SIZE];
    MMP_UBYTE                   ep0_data_buf[EP0_DATA_PACKET_SIZE + EP0_MAX_PACKET_SIZE];
    MMP_ULONG                   recd_data_addr[RECD_FRM_BUF_CNT];
} USB_OTG_HANDLE;

/* EP Configuration Attribute */
typedef struct __attribute__((packed)) _USB_EP_ATR
{
    MMP_UBYTE                   ep_dir;
    MMP_UBYTE                   ep_speed;
    MMP_UBYTE                   ep_xfer_type;
    MMP_UBYTE                   ep_num;
    MMP_UBYTE                   ep_addr;
    MMP_UBYTE                   ep_interval;
    MMP_ULONG                   ep_maxP;
} USB_EP_ATR;

/* Slot buffer manager */
typedef struct __attribute__((packed)) _SLOT_BUF_CTL
{
    MMP_ULONG                   ulTmpBufAddr;
    MMP_ULONG                   ulBufAddr[EP_RX_BUF_CNT];
    MMP_ULONG                   ulBufSize;
    MMP_ULONG                   ulWritePtr;
    MMP_ULONG                   ulContentSize[EP_RX_BUF_CNT];
    MMP_UBYTE                   ulWriteBufIdx;
} SLOT_BUF_CTL;

/* Packet Transfer Control */
typedef struct __attribute__((packed)) _UVCH_XFER_CTL
{
    MMP_ULONG                   ulFrmSize;
    MMP_ULONG                   ulXferSize;
    MMP_ULONG                   ulUsbRxByte;
    MMP_ULONG                   ulUsbPktCnt;
    MMP_ULONG                   ulUsbLastPktByte;
    MMP_ULONG                   ulFrmCnt;
    MMP_ULONG                   ulFTarget;
    MMP_UBYTE                   ubFrmToggle;
    MMP_UBYTE                   ubUsbRxSkipEn;
    SLOT_BUF_CTL                buf_ctl;
    MMP_UBYTE                   ubUVCRxState;
    MMP_UBYTE                   ubUVCStreamEn;                  // Enable Move DMA Rx packet to EP buffer.
    MMP_UBYTE                   ubUVCPrevwEn;                   // Enable Move EP buffer to preview buffer.
    MMP_UBYTE                   ubUVCRecdEn;                    // Update by MMPS_HUVC_StartRecd, MMPS_HUVC_StopRecd, MMPS_3GPRECD_PreRecord and MMPF_USBH_NotifySlowCardCallBack,
    MMP_UBYTE                   ubUVCWiFiEn;
#if (EN_USBH_ALWAYS_INPUT_FRM)
    MMP_UBYTE                   ubRecdStopReqEx;                // Triggered by MMPS_HUVC_StopRecd,
    MMP_UBYTE                   ubRecdStopDone;                 // Update by MMPS_HUVC_StopRecd and MMPF_USBH_CheckNotify2StopUVCRecord,
    MMP_UBYTE                   ubRstRecdInfoWrReq;
    MMP_UBYTE                   ubRstRecdCpltWrReq;
    MMP_UBYTE                   ubRstRecdBufWrReq;
    MMP_UBYTE                   ubRstRecdInfoRdReq;
    MMP_UBYTE                   ubRstRecdCpltRdReq;
    MMP_UBYTE                   ubRstRecdBufRdReq;
    MMP_UBYTE                   ubNotifyRecdTriggerSt;          // Notify MMPF_USBH_PostProcess_Task recd start triggered,
#endif
    MMP_UBYTE                   ubRecdStopReleaseSemDone;
} UVCH_XFER_CTL;

/* Record ring buffer manager */
typedef struct __attribute__((packed)) _RECD_BUF_CTL
{
    MMP_ULONG                   ulRecdBufAddr[RECD_FRM_BUF_CNT];
    MMP_ULONG                   ulRecdBufSize;
    MMP_ULONG                   ulInputPtr;
    MMP_ULONG                   ulStOfst[RECD_FRM_Q_SZ];            // Frame start offset
    MMP_ULONG                   ulTargetFrmSize[RECD_FRM_Q_SZ];     // Xfer/received target frame size (w/ALIGN32 from device)
    MMP_ULONG                   ulFrmSize[RECD_FRM_Q_SZ];           // Exact frame size (w/o ALIGN32)
    MMP_ULONG                   ulFrmTimeStamp[RECD_FRM_Q_SZ];      // Frame timestamp
    MMP_UBYTE                   ubFrmType[RECD_FRM_Q_SZ];           // Frame type
    MMP_UBYTE                   ubInFrm[RECD_FRM_CPLT_Q_SZ];
    MMP_UBYTE                   ubTriggerSt[RECD_FRM_CPLT_Q_SZ];
    MMP_UBYTE                   ubInFrmCnt;                         // Remaining (received) frame # that wait to be write
} RECD_BUF_CTL;

/* Preview ring buffer manager */
typedef struct __attribute__((packed)) _PREVW_BUF_CTL
{
    MMP_ULONG                   ulPrevwBufAddr[PREVW_FRM_BUF_CNT];
    MMP_ULONG                   ulPrevwBufSize;
    MMP_ULONG                   ulPrevwBufCnt;
    MMP_ULONG                   ulInputPtr;
    MMP_ULONG                   ulBufferWIdx;
    MMP_UBYTE                   ubWinID;
    MMP_ULONG                   ulFrmSize;
    MMP_GRAPHICS_ROTATE_TYPE    ubPrevwRoteType;
    MMP_UBYTE                   ubUpdFrm[PREVW_FRM_CPLT_Q_SZ];
    MMP_UBYTE                   ubSkipCopyPrevwBufEn;
    MMP_UBYTE                   ubMjpegFrmRdyCnt;                   // Remaining (received) frame # that wait to preview
} PREVW_BUF_CTL;

typedef struct __attribute__((packed)) _MMPF_USBH_POLLING_CFG
{
    MMPF_OS_TMR_CALLBACK        TriggerReadUSBIDCallback;
    MMPF_USBH_Callback          *OtgSessionTimeoutCallback;
    MMPF_USBH_Callback          *DevConnCallback;
    MMPF_USBH_Callback          *DevDisconnCallback;
} MMPF_USBH_POLLING_CFG;

typedef struct __attribute__((packed)) _MMPF_USBH_MD_CFG
{
    MMP_UBYTE                   ubDevMDEn; // Handle MD frame or not
    MMPF_USBH_Callback          *DevTriggerMDCallback;
} MMPF_USBH_MD_CFG;

/* USB UVC error handle manager (software) */
typedef struct __attribute__((packed)) _MMPF_USBH_ERROR_HANDLE_CFG
{
    MMP_UBYTE                   ubFirstFrmReceived;                                 //TRUE,FALSE
    MMP_UBYTE                   ubFrmRxTimerStart;                                  //TRUE,FALSE
    MMP_UBYTE                   ubTranTimerStart;                                   //TRUE,FALSE
    MMP_UBYTE                   ubCheckDevAliveTimerStart;                          //TRUE,FALSE
    MMP_UBYTE                   ubFrmRxTimeoutTHValid;                              //TRUE,FALSE
    MMP_UBYTE                   ubUpdFrmRxTimeoutParm;                              //TRUE,FALSE
    MMP_UBYTE                   ubFrmRxTimeoutCallbackDone[FRM_RX_TIMEOUT_MAX_HDL]; //TRUE,FALSE
    MMP_UBYTE                   ubTranTimeoutCallbackDone;                          //TRUE,FALSE
    MMP_UBYTE                   ubDevNoResponseTriggered;                             //TRUE,FALSE
    MMP_UBYTE                   ubFrmRxTimeoutTriggered[FRM_RX_TIMEOUT_MAX_HDL];      //TRUE,FALSE
    MMP_ULONG                   ulFrmRxLostTH[FRM_RX_TIMEOUT_MAX_HDL];              //#
    MMP_ULONG                   ulFrmSeqNoLostTH;                                   //#
    MMP_ULONG                   ulFrmRxFirstTimeoutInterval[FRM_RX_TIMEOUT_MAX_HDL];//ms
    MMP_ULONG                   ulFrmRxNextTimeoutInterval[FRM_RX_TIMEOUT_MAX_HDL]; //ms
    MMP_ULONG                   ulTranTimeoutInterval;                              //ms, exclude 1st transaction of frame
    MMP_ULONG                   ulCheckDevAliveInterval;                            //ms
    MMP_ULONG                   ulFrmRxCheckTimerId;
    #if (!EN_REMOVE_TRAN_HW_TIMER)
    MMP_ULONG                   ulTranTimerId;
    #endif
    MMP_ULONG                   ulCheckDevAliveTimerId;
    MMP_ULONG                   ulCurWaitRxDoneMsCnt;                               //ms
    #if (EN_REMOVE_TRAN_HW_TIMER)
    MMP_ULONG                   ulCurTranTimerStartMs;                              //ms
    #endif
    MMP_ULONG                   ulCurTranCnt;
    MMP_ULONG                   ulCurYUVFrmSeqNo;
    MMP_ULONG                   ulCurH264FrmSeqNo;
    MMP_ULONG                   ulCurMJPEGFrmSeqNo;
    MMP_ULONG                   ulLastYUVFrmSeqNo;
    MMP_ULONG                   ulLastH264FrmSeqNo;
    MMP_ULONG                   ulLastMJPEGFrmSeqNo;
    MMP_ULONG                   ulDropRxFrmCurCnt;
    MMP_ULONG                   ulDropRxFrmCurContinCnt;
    MMP_ULONG                   ulDropRxFrmTotalCnt; //How many frames are dropped in total
    MMP_ULONG                   ulDropRxFrmContinCnt;  //How many frames are dropped sequentially

    MMPF_USBH_Callback          *DevTranTimeoutCallback;
    MMPF_USBH_Callback          *DevFrmRxTimeoutCallback[FRM_RX_TIMEOUT_MAX_HDL];
    MMPF_USBH_Callback          *DevFrmSeqNoLostCallback;
    MMPF_USBH_Callback          *DevNoResponseCallback;
    MMPF_USBH_Callback          *DevDropRxFrmCallback;
} MMPF_USBH_ERROR_HANDLE_CFG;

/* Error message info structure */
typedef struct __attribute__((packed)) _MMPF_USBH_ERR_MSG_CFG
{
    MMP_UBYTE                   ubErrCase;
    MMP_ULONG                   ulParm0;
    MMP_ULONG                   ulParm1;
} MMPF_USBH_ERR_MSG_CFG;

/* Still rear cam structure */
typedef struct __attribute__((packed)) _MMPF_USBH_STILL_CFG
{
    MMP_ULONG                   ulJpgDstBufAddr;    // destination address to store stilled JPG
    MMP_ULONG                   ulJpgDstBufSize;    // destination reserved buffer size for store JPG
    MMP_BOOL                    bJpgStart;          // enable still JPG
    MMP_UBYTE                   ubJpgStartDelayCnt; // delay frame count before still
    MMP_ULONG                   ulCurJpgSize;       // still JPG size
    MMP_BOOL                    bJpgDone;           // still complete or not
    MMP_ERR                     mStillSR;           // still operation status
} MMPF_USBH_STILL_CFG;

typedef struct
{
    MMP_ULONG                   ulDecompressStart;  // DeCompress buffer start address.
    MMP_ULONG                   ulDecompressSize;   // DeCompress buffer size.
    MMP_ULONG                   ulDecodeOutStart;   // Decoded output buffer start address.
    MMP_ULONG                   ulDecodeOutSize;    // Decoded output buffer size.
    MMP_ULONG                   ulStorageTmpStart;  // EXIF/Data buffer start address.
    MMP_ULONG                   ulStorageTmpSize;   // EXIF/Data buffer size.
} MMP_USBH_MJPEG_DEC_BUF;

typedef MMP_ERR (*pfMMPF_USBH_SetBulkDma3Rx)(MMP_UBYTE ep, MMP_ULONG fb_addr,MMP_ULONG rx_byte, MMP_BOOL bPktReq);
typedef MMP_ERR (*pfMMPF_USBH_TriggerDmaRxOnePkt)(void);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

extern AUTL_RINGBUF             mRecdFrmXferFsQHdl; //record frame xfer frame size queue
extern AUTL_RINGBUF             mRecdFrmFsQHdl;     //record frame valid frame size queue
extern AUTL_RINGBUF             mRecdFrmTstpQHdl;   //record frame time stamp queue
extern AUTL_RINGBUF             mRecdFrmTypQHdl;    //record frame type queue
extern AUTL_RINGBUF             mRecdFrmStOfstQHdl; //record frame start offset queue
extern AUTL_RINGBUF             mRecdFrmCpltQHdl;   //record frame if complete(one frame) by this moveDMA operation, before move into Mgr
extern AUTL_RINGBUF             mRecdTriggerStQHdl; //record trigger start by this moveDMA operation, before move into Mgr
extern AUTL_RINGBUF             mRecdFrmBufHdl;     //record frame data ring buffer
extern AUTL_RINGBUF             mPrevwFrmCpltQHdl;  //preview frame if complete(one frame)by this moveDMA operation, before refresh
extern AUTL_RINGBUF             mPrevwFrmBufHdl;    //preview frame data ring buffer
#if (SUPPORT_DEC_MJPEG_TO_PREVIEW)
extern AUTL_RINGBUF             mDecJpgRdyQHdl;     //JPG, frame ready queue, before trigger decode
extern AUTL_RINGBUF             mDecJpgInpQHdl;     //JPG, current input queue, before trigger decode
extern AUTL_RINGBUF             mJpgFrmXferFsQHdl;  //JPG xfer frame size queue
#endif
extern AUTL_RINGBUF             mJpgWiFiBufHdl;     //JPG2WiFi frame data ring buffer

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_USBH_SetBulkDma3Rx_ISOMode(MMP_UBYTE ep, MMP_ULONG fb_addr,MMP_ULONG rx_byte, MMP_BOOL bPktReq);
MMP_ERR MMPF_USBH_SetBulkDma3Rx_BulkMode(MMP_UBYTE ep, MMP_ULONG fb_addr,MMP_ULONG rx_byte, MMP_BOOL bPktReq);

MMP_ERR MMPF_USBH_TriggerDmaRxOnePkt_ISOMode(void);
MMP_ERR MMPF_USBH_TriggerDmaRxOnePkt_BulkMode(void);

MMP_ERR MMPF_USBH_SetITransferMode(MMP_BOOL bISOMode);

MMP_ERR MMPF_USBH_WaitEp0TxDone(void);
MMP_ERR MMPF_USBH_WaitEp0RxDone(void);
MMP_ERR MMPF_USBH_WaitEpTxDone(MMP_UBYTE ep);
MMP_ERR MMPF_USBH_WaitEpRxDone(MMP_UBYTE ep);
MMP_ERR MMPF_USBH_WriteEpFifo(MMP_UBYTE ep, MMP_UBYTE *data, MMP_ULONG size);
MMP_ERR MMPF_USBH_ReadEpFifo(   MMP_UBYTE   ep,
                                MMP_UBYTE   *buf,
                                MMP_USHORT  *psByteinFifo);

MMP_ERR MMPF_USBH_ConfigEp0(USBH_DEVICE *dev);
MMP_ERR MMPF_USBH_ConfigEp(MMP_UBYTE ep, USB_EP_ATR *attribute);
void    MMPF_USBH_EnableEpInterrupt(MMP_UBYTE           ep,
                                    MMP_UBYTE           dir,
                                    MMP_USB_EpCallback  *cb);
void    MMPF_USBH_DisableEpInterrupt(MMP_UBYTE ep, MMP_UBYTE dir);

MMP_ERR MMPF_USBH_InitCtlXferSem(void);
MMP_ERR MMPF_USBH_SendEp0Setup(EP0_REQUEST *setup_pkt);
MMP_ERR MMPF_USBH_ReceiveEp0Data(MMP_UBYTE *data_buf, MMP_ULONG *plDataBytes);
MMP_ERR MMPF_USBH_SendEp0Data(MMP_UBYTE *data_buf, MMP_ULONG size);
MMP_ERR MMPF_USBH_HandleEp0Status(MMP_UBYTE dir);
MMP_ERR MMPF_USBH_ControlTransfer(  USBH_DEVICE *dev,
                                    EP0_REQUEST *req,
                                    void        *buf,
                                    MMP_ULONG   *xfer_size);
void    MMPF_USBH_InterruptInTransfer(  USBH_DEVICE         *dev,
                                        MMP_UBYTE           ep,
                                        MMP_USB_EpCallback  *cb);


MMP_ERR MMPF_USBH_TriggerDmaRx64Byte(void);
MMP_ERR MMPF_USBH_TriggerDmaRx448Byte(void);
MMP_ERR MMPF_USBH_WaitDmaDone(MMP_UBYTE ch);
MMP_ERR MMPF_USBH_WaitDmaRxDone(MMP_UBYTE ep, MMP_UBYTE ch);
MMP_ERR MMPF_USBH_WaitDmaTxDone(MMP_UBYTE ep, MMP_UBYTE ch);
MMP_ERR MMPF_USBH_TriggerDmaRx(void);
MMP_ERR MMPF_USBH_ConfigDma3Tx( MMP_UBYTE   endpoint,
                                MMP_ULONG   fb_addr,
                                MMP_USHORT  pkt_byte,
                                MMP_USHORT  last_pkt_byte,
                                MMP_ULONG   pkt_sum,
                                MMP_ULONG   zero_end);
MMP_ERR MMPF_USBH_StopFrmRxClrFIFO(void);
#if (DMA3_RX_LAST_PKT_PATCH)
MMP_ERR MMPF_USBH_ConfigDma3RxLP(MMP_UBYTE endpoint,MMP_ULONG fb_addr,MMP_USHORT pkt_byte,MMP_USHORT last_pkt_byte,MMP_ULONG pkt_sum,MMP_BOOL bPktReq);
#else
MMP_ERR MMPF_USBH_ConfigDma3Rx(MMP_UBYTE endpoint,MMP_ULONG fb_addr,MMP_USHORT pkt_byte,MMP_USHORT last_pkt_byte,MMP_ULONG pkt_sum);
#endif
MMP_ERR MMPF_USBH_SetBulkDma3Tx(MMP_UBYTE ep, MMP_ULONG fb_addr,MMP_ULONG size);
MMP_ERR MMPF_USBH_InitUVCPrevwRingBuf(void);
MMP_ERR MMPF_USBH_InitUVCRecdRingBuf(void);
MMP_ERR MMPF_USBH_InitFBMemory(void);
MMP_ERR MMPF_USBH_IsSetFBMemory(MMP_UBYTE *ubUVCFBMemSet);
MMP_ERR MMPF_USBH_SetUSBRXBuffer(void *pHandle, MMP_BOOL bIsBulkMode, MMP_BOOL bReset);
MMP_ERR MMPF_USBH_SetUSBRecordBuffer(void *pHandle, MMP_BOOL bReset);
MMP_ERR MMPF_USBH_ResetFBMemory(void);
MMP_ERR MMPF_USBH_GetTimerCount(MMP_ULONG *pulTimeUs);
MMP_ERR MMPF_USBH_StopOTGSession(void);
MMP_ERR MMPF_USBH_TriggerOTGSession(MMP_ULONG *pulTimerId);
MMP_ERR MMPF_USBH_ResetPort(void);
MMP_UBYTE MMPF_USBH_GetBusSpeed(void);
MMP_ERR MMPF_USBH_InitOTG(void);
MMP_ERR MMPF_USBH_SetTxBuf(MMP_ULONG fb_addr,MMP_USHORT size);
MMP_ERR MMPF_USBH_TestBulkOut(MMP_ULONG sec_num, MMP_UBYTE dma_ch);
MMP_ERR MMPF_USBH_GetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPF_USBH_SetClassIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPF_USBH_SetStdIfCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPF_USBH_SetStdEpCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPF_USBH_GetStdDevCmd(MMP_UBYTE bReq, MMP_USHORT wVal, MMP_USHORT wInd, MMP_USHORT wLen, MMP_ULONG *UVCDataLength, MMP_UBYTE *UVCDataBuf);
MMP_ERR MMPF_USBH_GetDeviceConnectedSts(MMP_BOOL *pbEnable);
MMP_ERR MMPF_USBH_SetDeviceConnectedSts(MMP_BOOL bEnable);
MMP_ERR MMPF_USBH_OpenUVCDevice(USBH_DEVICE *dev);
MMP_ERR MMPF_USBH_GetStreamReq(MMP_USHORT wMin);
MMPF_USBH_POLLING_CFG* MMPF_USBH_GetPollingCFG(void);
MMP_ERR MMPF_USBH_RegPollingCallBack(void *pReadUSBIDTimeoutCallback, void *pOtgSessionTimeoutCallback, void *pDevConnCallback, void *pDevDisconnCallback);
MMP_ERR MMPF_USBH_TriggerReadUSBID(MMP_ULONG *pulTimerId);
MMP_ERR MMPF_USBH_ReadUSBID(MMP_UBYTE *pubDevType);
MMPF_USBH_MD_CFG* MMPF_USBH_GetUVCMDCFG(void);
MMP_ERR MMPF_USBH_RegUVCMDCallBack(void *pDevTriggerMDCallback);
MMP_ERR MMPF_USBH_EnableUVCMD(void);
MMP_ERR MMPF_USBH_DisableUVCMD(void);

/* Error Handler */
MMPF_USBH_ERROR_HANDLE_CFG* MMPF_USBH_GetErrorHandleCFG(void);
MMP_ERR MMPF_USBH_StopCheckDevAliveTimer(void);
MMP_ERR MMPF_USBH_StartCheckDevAliveTimer(void);
MMP_ERR MMPF_USBH_SetCheckDevAliveCFG(MMP_ULONG ulCheckDevAliveInterval, void *pDevNoResponseCallback);
MMP_ERR MMPF_USBH_StopTranTimer(void);
MMP_ERR MMPF_USBH_RestartTranTimer(void);
MMP_ERR MMPF_USBH_SetTranTimeoutCFG(MMP_ULONG ulTranTimeoutInterval, void *pDevTranTimeoutCallback);
MMP_ERR MMPF_USBH_StopFrmRxTimer(void);
MMP_ERR MMPF_USBH_RestartFrmRxTimer(void);
MMP_ERR MMPF_USBH_SetFrmRxTimeoutCFG(MMP_ULONG ulFrmRxLostTH, MMP_ULONG ulFrmRxFirstAddGap, void *pDevFrmRxLostTHCallback);
MMP_ERR MMPF_USBH_SetFrmRxTimeout2CFG(MMP_ULONG ulFrmRxLostTH2, void *pDevFrmRxLostTH2Callback);
MMP_ERR MMPF_USBH_SetFrmSeqNoLostCFG(MMP_ULONG ulSeqNoLostTH, void *pDevSeqNoLostTHCallback);
MMP_ERR MMPF_USBH_SetDropRxFrmCFG(MMP_ULONG ulTotalCnt, MMP_ULONG ulContinCnt, void *pDropRxFrmCallback);

#endif //end of #if (USB_EN)&&(SUPPORT_USB_HOST_FUNC)

#endif // _MMPF_USBH_CTL_H_
