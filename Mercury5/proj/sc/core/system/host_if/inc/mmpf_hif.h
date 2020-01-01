//==============================================================================
//
//  File        : mmpf_hif.h
//  Description : INCLUDE File for the Firmware Host Interface Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_HIF_H_
#define _MMPF_HIF_H_

/** @addtogroup MMPF_HIF
@{
*/
//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_hif_cmd.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

/* Flag for HIF_CMD (SYS_Flag_Hif) */
#define SYS_FLAG_SYS                                (0x00000001)
#define SYS_FLAG_FS                                 (0x00000002)
#define SYS_FLAG_MEMDEV_ACK                         (0x00000008)
#define SYS_FLAG_LTASK                              (0x00000010)
#define SYS_FLAG_AGC                                (0x00000020)
#define SYS_FLAG_DEBUG_SF                           (0x00000040)
#define SENSOR_FLAG_DUAL_SNR_TRIG_RAWFETCH          (0x00010000)

/* Flag for Sensor/ISP (SENSOR_Flag) */
#define SENSOR_FLAG_VIF_GRAB_END                    (0x00000001)
#define SENSOR_FLAG_VIF_FRM_END                     (0x00000002)
#define SENSOR_FLAG_VIF_FRM_ST                      (0x00000004)
#define SENSOR_FLAG_VIF_LINE_NO                     (0x00000008)

#define SENSOR_FLAG_ISP_FRM_ST                      (0x00000010)
#define SENSOR_FLAG_ISP_FRM_END                     (0x00000020)

#define SENSOR_FLAG_SENSOR_CMD                      (0x00000200)
#define SENSOR_FLAG_ROTDMA                          (0x00000400) // For Front Cam only
#define SENSOR_FLAG_FDTC_DRAWRECT                   (0x00000800)
#define SENSOR_FLAG_PCAMOP                          (0x00001000)
#define SENSOR_FLAG_CHANGE_SENSOR_MODE              (0x00002000)
#define SENSOR_FLAG_CHECK_TVDEC_TYPE                (0x00004000)
#define SENSOR_FLAG_ROTDMA_PIPE2                    (0x00010000) // For Rear Cam
#define SENSOR_FLAG_ROTDMA_PIPE3                    (0x00020000)
#define SENSOR_FLAG_REINIT                          (0x00040000)
#define SENSOR_FLAG_BUF2JPG                         (0x00080000)

/* Flag for Scaler */
#define SCL0_FLAG_FRM_ACTIVE                        (0x00000001)
#define SCL1_FLAG_FRM_ACTIVE                        (0x00000002)

/* Flag for DSC (DSC_Flag) */
#define DSC_FLAG_DSC_CMD                            (0x00000001)
#define DSC_FLAG_WRITE_FILE                         (0x00000002)

/* Flag for JPEG Encode (JPEG_Enc_Flag) */
#define JPG_FLAG_EXE_ENCODE                         (0x00000001)
#define JPG_FLAG_DECODE_DONE                        (0x00000002)
#define JPG_FLAG_ENC_FLUSH_INPUT_Q                  (0x00000004)

/* Flag for JPEG Decode (JPEG_Dec_Flag) */
#define JPG_FLAG_EXE_DECODE                         (0x00000001)
#define JPG_FLAG_ENCODE_DONE                        (0x00000002)

/* Flag for LDC Control (LDC_Ctl_Flag) */
#define LDC_FLAG_EXE_LOOPBACK                       (0x00000001)
#define LDC_FLAG_DMA_MOVE_FRAME                     (0x00000002)
#define LDC_FLAG_DMA_MOVE_FRAME_DONE                (0x00000004)

/* Flag for H264E Control (H264E_Ctl_Flag) */
#define H264E_FLAG_EXE_ENCODE                       (0x00000001)
#define H264E_FLAG_FLUSH_INPUT_Q                    (0x00000002)
#define H264E_FLAG_MOVEGENBUF                       (0x00000003)

/* Flag for Video Record (VID_REC_Flag) */
#define CMD_FLAG_MGR3GP                             (0x00000001)
#define CMD_FLAG_VIDRECD                            (0x00000002)
#define SYS_FLAG_VIDENC                             (0x00000004)
#define SYS_FLAG_STREAMING_CB                       (0x00000008)
#define SYS_FLAG_STREAMING_FRONTSTOP                (0x00000010)
#define SYS_FLAG_STREAMING_REARSTOP                 (0x00000020)
#define SYS_FLAG_MGR3GP                             (0x00000040)
#define SYS_FLAG_VIDRECD_CB                         (0x00000080)
#define VID_FLAG_MFE_ENC_DONE                       (0x00000100)
#define SENSOR_FLAG_TRIGGER_DEINTERLACE             (0x00010000)
#define SENSOR_FLAG_TRIGGER_GRA_TO_PIPE             (0x00020000)
#define SYS_FLAG_DEBUG_INFO                         (0x00100000)

/* Flag for Wifi Streaming (Streaming_Flag) */
#define STREAM_FLAG_ADD_V1_FRAME                    (0x00000001)
#define STREAM_FLAG_ADD_V2_FRAME                    (0x00000002)
#define STREAM_FLAG_ADD_A1_FRAME                    (0x00000008)
#define STREAM_FLAG_ADD_A2_FRAME                    (0x00000010)
#define STREAM_FLAG_PUMP_STREAM                     (0x00000040)
#define STREAM_FLAG_MSG_STREAM                      (0x00000080)
#define STREAM_FLAG_RESET_AUDIO1                    (0x00001000)
#define STREAM_FLAG_RESET_AUDIO2                    (0x00002000)
#define STREAM_FLAG_RESET_VIDEO1                    (0x00004000)
#define STREAM_FLAG_RESET_VIDEO2                    (0x00008000)
#define STREAM_FLAG_DROP_V4L_H264_FRAME             (0x00010000)
#define STREAM_FLAG_RESET_ALL                       (0x0000F000)

/* Flags for Network */
#define SYS_FLAG_MSG_NETWORK_INIT                   (0x00000001)
#define SYS_FLAG_MSG_NETWORK_CMD                    (0x00000002)
#define SYS_FLAG_MSG_NETWORK_UNIN                   (0x00000004)
#define SYS_FLAG_MSG_NETWORK_RESET                  (0x00000008)
#define SYS_FLAG_MSG_NETWORK_UINOTIFY               (0x00000010)
#define SYS_FLAG_MSG_NETWORK_JOB                    (0x00000020)
#define SYS_FLAG_MSG_NETWORK_WIFILINK_IND           (0x00000040)
#define SYS_FLAG_MSG_NETWORK_WIFILINK_DOWN_IND      (0x00000080)

/* Flags for Http File reading */
#define SYS_FLAG_MSG_HTTP_FILE_TRIGGER_READING      (0x00000001)

/* Flag for Audio Play (AUD_PLAY_Flag) */
#define AUD_FLAG_AUDIOPLAY                              (0x00000001)
#define AUD_FLAG_AUDIO_PREVIEW                      (0x00000002)
#define AUD_FLAG_AUDIO_BYPASS                           (0x00000004)
#define AUD_FLAG_AUDIO_AMIXOP                       (0x00000008)
#define AUD_FLAG_AUDIO_AMIXEMPTY                       (0x00000010)
#define AUD_FLAG_AUDIO_AMIXUNDER                      (0x00000020)

/* Flag for Audio Record (AUD_REC_Flag) */
#define AUD_FLAG_AUDIOREC                           (0x00000001)
#define AUD_FLAG_GAPLESS_CB                         (0x00000002)

/* Flag for Audio Streaming (AUD_STREAM_Flag) */
#define AUD_FLAG_AUDIOWRITE_FILE                    (0x00000001)
#define AUD_FLAG_AUDIOREAD_FILE                     (0x00000002)
#define AUD_FLAG_MP3_GET_INFO                       (0x00000004)
#define AUD_FLAG_AUI_READ_FILE                      (0x00000008)

/* Flag for Video Play (VID_PLAY_Flag) */
#define SYS_FLAG_VIDPLAY                            (0x00000001)
#define SYS_FLAG_PSR3GP                             (0x00000002)
#define SYS_FLAG_VID_DEC                            (0x00000004)
#define SYS_FLAG_DEMUX                              (0x00000008)
#define SYS_FLAG_DEBUG                              (0x00000010)
#define SYS_FLAG_FW_VIDPLAY                         (0x00000020)
#define SYS_FLAG_VID_CMD                            (0x00000040)

/* Flag for USB operation (USB_OP_Flag) */
#define USB_FLAG_GENOP                              (0x00000001)
#define USB_FLAG_CLASS_OP                           (0x00000002)
#define USB_FLAG_XU_CMD_OP                          (0x00000004)
#define USB_FLAG_UVC                                (0x00000008)
#define USB_FLAG_UVC_START_PREVIEW                  (0x00000010)
#define USB_FLAG_UVC_STOP_PREVIEW                   (0x00000020)
#define USB_FLAG_USBH_GET_PKT_REQ                   (0x00000040)
#define USB_FLAG_USBH_PROC_PKT_REQ                  (0x00000080)
#define USB_FLAG_USBH_STOP_UVC_REQ                  (0x00000100)
#define USB_FLAG_USBH_INPUT_FRAME_REQ               (0x00000200)
#define USB_FLAG_USBH_SYNC_UVC_TIME_REQ             (0x00000400)
#define USB_FLAG_USBH_COPY_FRM_REQ                  (0x00000800)
#define USB_FLAG_UAC_START                          (0x00001000)
#define USB_FLAG_UAC_STOP                           (0x00002000)
#define USB_FLAG_UAC_SAMPLE_RATE                    (0x00004000)
#define USB_FLAG_UAC_MUTE                           (0x00008000)
#define USB_FLAG_UAC_VOLUME                         (0x00010000)
#define USB_FLAG_USBH_DMA_RX_DONE_REQ               (0x00020000)
#define USB_FLAG_USBH_ROTE_FRM_REQ                  (0x00040000)
#define USB_FLAG_USBH_RX_JPG_FRM_RDY_REQ            (0x00080000)

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_ULONG    m_ulHifCmd[GRP_IDX_NUM];
extern MMP_ULONG    m_ulHifParam[GRP_IDX_NUM][MAX_HIF_ARRAY_SIZE];

typedef MMP_ULONG   MMPF_OS_FLAGID; //Ref:os_wrap.h

extern MMPF_OS_FLAGID   SYS_Flag_Hif;
extern MMPF_OS_FLAGID   AUD_PLAY_Flag;
extern MMPF_OS_FLAGID   SENSOR_Flag;
extern MMPF_OS_FLAGID   DSC_Flag;
extern MMPF_OS_FLAGID   JPEG_Enc_Flag;
extern MMPF_OS_FLAGID   JPEG_Dec_Flag;
extern MMPF_OS_FLAGID   AUD_REC_Flag;
extern MMPF_OS_FLAGID   AUD_STREAM_Flag;
extern MMPF_OS_FLAGID   VID_REC_Flag;
extern MMPF_OS_FLAGID   H264E_Ctl_Flag;
extern MMPF_OS_FLAGID   VID_PLAY_Flag;
extern MMPF_OS_FLAGID   USB_OP_Flag;
extern MMPF_OS_FLAGID   DSC_UI_Flag;
extern MMPF_OS_FLAGID   Streaming_Flag;
extern MMPF_OS_FLAGID   Network_Flag;
#if (HANDLE_LDC_EVENT_BY_QUEUE)
extern MMPF_OS_FLAGID   LDC_Ctl_Flag;
#endif

#if ((DSC_R_EN)||(VIDEO_R_EN))&&(SUPPORT_ADAS)
extern MMPF_OS_FLAGID   FDTC_Flag;
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_HIF_ResetCmdStatus(void);
void MMPF_HIF_SetCmdStatus(MMP_ULONG status);
void MMPF_HIF_ClearCmdStatus(MMP_ULONG status);
MMP_ULONG MMPF_HIF_GetCmdStatus(MMP_ULONG status);

void MMPF_HIF_FeedbackParamL(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_ULONG ulParamdata);
void MMPF_HIF_FeedbackParamW(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_USHORT usParamdata);
void MMPF_HIF_FeedbackParamB(MMP_UBYTE ubGroup, MMP_UBYTE ubParamnum, MMP_UBYTE ubParamdata);

#endif // _MMPF_HIF_H_
