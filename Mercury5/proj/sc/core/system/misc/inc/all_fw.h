#ifndef _ALL_FW_H_
#define _ALL_FW_H_

#include "config_fw.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TASK_DIP_CTL_PRIO           (53)
#define TASK_SCL_PRIO               (53)
#define TASK_SCL_POLL_PRIO          (53)
#define TASK_SCL_IRQ_DAZA_PRIO      (52)
#define TASK_SYS_TIMER_PRIO         (51)

// RTK system task range is 2~54
#define OS_RTK_LOWEST_PRIO          (0)
#define OS_RTK_HIGHEST_PRIO         (50) // 55 can not be used.

// Reorder priority number for RTK.
#define TASK_VIP_DAZA_IST           (OS_RTK_HIGHEST_PRIO - 1)   // (49)
#define TASK_SYS_PRIO               (OS_RTK_HIGHEST_PRIO - 1)   // (49)
#define TASK_USBH_BULKIN_PRIO       (OS_RTK_HIGHEST_PRIO - 2)   // (48)
#define TASK_VIF_PRIO               (OS_RTK_HIGHEST_PRIO - 3)   // (47)
#define TASK_ISP_HIGH_PRIO          (OS_RTK_HIGHEST_PRIO - 3)   // (47)
#define TASK_JPEG_DEC_PRIO          (OS_RTK_HIGHEST_PRIO - 4)   // (46)
#define TASK_JPEG_ENC_PRIO          (OS_RTK_HIGHEST_PRIO - 4)   // (46)
#define TASK_VID_ENC_DONE_PRIO      (OS_RTK_HIGHEST_PRIO - 5)   // (45)
#define TASK_VID_ENC_TRIG_PRIO      (OS_RTK_HIGHEST_PRIO - 6)   // (44) // Change for Encode random have broken image.
#define TASK_VID_DMA_GEN_PRIO       (OS_RTK_HIGHEST_PRIO - 6)   // (44)
#define TASK_VIDMGR_PRIO            (OS_RTK_HIGHEST_PRIO - 7)   // (43)
#define TASK_USBH_POSTPROCESS_PRIO  (OS_RTK_HIGHEST_PRIO - 9)   // (41)
#define TASK_ISP_RDMA_PRIO          (OS_RTK_HIGHEST_PRIO - 10)  // (40)
#define TASK_HIGH_WORK_PRIO         (OS_RTK_HIGHEST_PRIO - 11)  // (39) // For high priority but short execution time work.
#define TASK_ISP_LOW_PRIO           (OS_RTK_HIGHEST_PRIO - 12)  // (38)
#if (AUDIO_STREAMING_EN == 1) || (AUI_STREAMING_EN == 1)
#define TASK_AUDIO_STREAM_PRIO      (OS_RTK_HIGHEST_PRIO - 13)  // (37)
#endif
#define TASK_UHC_EHCI0_PRIO         (OS_RTK_HIGHEST_PRIO - 14)  // (36)
#define TASK_UHC_EHCI1_PRIO         (OS_RTK_HIGHEST_PRIO - 14)  // (36)
#define TASK_VIDDEC_PRIO            (OS_RTK_HIGHEST_PRIO - 15)  // (35)
#define TASK_3GPPARSR_PRIO          (OS_RTK_HIGHEST_PRIO - 16)  // (34)
#define TASK_AUDIO_PLAY_PRIO        (OS_RTK_HIGHEST_PRIO - 17)  // (33)
#define TASK_VIDPLAY_PRIO           (OS_RTK_HIGHEST_PRIO - 18)  // (32)
#define TASK_SENSOR_PRIO            (OS_RTK_HIGHEST_PRIO - 19)  // (31)
#define TASK_DSC_PRIO               (OS_RTK_HIGHEST_PRIO - 20)  // (30)
#define TASK_AUDIO_RECORD_PRIO      (OS_RTK_HIGHEST_PRIO - 21)  // (29)
#if (MSDC_WR_FLOW_TEST_EN)
#define TASK_USB_WRITE_PRIO         (OS_RTK_HIGHEST_PRIO - 22)  // (28)
#else
#define TASK_USB_PRIO               (OS_RTK_HIGHEST_PRIO - 22)  // (28)
#endif
#define TASK_CYCLIC_JOB_PRIO        (OS_RTK_HIGHEST_PRIO - 23)  // (27)
#if (!AUDIO_STREAMING_EN) && (!AUI_STREAMING_EN)
#define TASK_AUDIO_STREAM_PRIO      (OS_RTK_HIGHEST_PRIO - 23)  // (27)
#endif
#define TASK_FS_PRIO                (OS_RTK_HIGHEST_PRIO - 24)  // (26)
#if (MSDC_WR_FLOW_TEST_EN)
#define TASK_USB_PRIO               (OS_RTK_HIGHEST_PRIO - 25)  // (25)
#endif
#define TASK_WIFI_STREAMING_PRIO    (OS_RTK_HIGHEST_PRIO - 26)  // (24)
#define TASK_HIGHFS_PRIO            (OS_RTK_HIGHEST_PRIO - 27)  // (23)
#define TASK_H264WIFICB_PRIO        (OS_RTK_HIGHEST_PRIO - 29)  // (21)
#define TASK_AHC_INIT_PRIO          (OS_RTK_HIGHEST_PRIO - 31)  // (19)
#define TASK_UART_BRUST_PRIO        (TASK_AHC_INIT_PRIO)
#define TASK_GYRO_PRIO              (OS_RTK_HIGHEST_PRIO - 35)  // (15)
#define TASK_V24_PRIO               (OS_RTK_HIGHEST_PRIO - 36)  // (14)
#define TASK_EIS_PRIO               (OS_RTK_HIGHEST_PRIO - 39)  // (11)
#define TASK_MDL_PRIO               (OS_RTK_HIGHEST_PRIO - 41)  // (9)
#define TASK_SPEECH_RECOG_PRIO      (OS_RTK_HIGHEST_PRIO - 42)  // (8)
#define TASK_CMD_MENU_PRIO          (OS_RTK_HIGHEST_PRIO - 49)  // (1)
#define TASK_IDLE_PRIO              (OS_RTK_LOWEST_PRIO)        // (0)

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

// Stack Size (Unit : Bytes)
#define TASK_SYS_STK_SIZE           (1024 << 2)
#define HIGH_WORK_STK_SIZE          (1024 << 2)
#define MID_WORK_STK_SIZE           (1024 << 2)
#define LOW_WORK_STK_SIZE           (1024 << 2)
#define LDC_CTL_STK_SIZE            (1024 << 2)
#define SENSOR_STK_SIZE             (2048 << 2)
#define FDTC_STK_SIZE               (2048 << 2)
#define FS_STK_SIZE                 (1024 << 2)

#define GYRO_STK_SIZE               (2048 << 2)
#define EIS_STK_SIZE                (2048 << 2)
#define SPEECH_STK_SIZE             (4096 << 2)
#define AHC_STK_SIZE                (6144 << 2)
#define DIP_CTL_STK_SIZE            (1024 << 2)

//JobDispatch task is created by os_wrap.c,so unit is long
#if defined(EXBOOT_FW)
#define TASK_JOB_DISPATCH_STK_SIZE  (4096)
#elif (SD_FW_UPDATER) && (!defined(ALL_FW))
#define TASK_JOB_DISPATCH_STK_SIZE  (1024)
#else
#define TASK_JOB_DISPATCH_STK_SIZE  (8192)
#endif

// JPEG Relative
#define DSC_STK_SIZE                (1024 << 2)
#define JPEG_ENC_STK_SIZE           (1024 << 2)
#define JPEG_DEC_STK_SIZE           (1024 << 2)

// Video Play Relative
#define PLAYER_STK_SIZE             (1024 << 2)
#define DECODER_STK_SIZE            (4096 << 2)
#define DEMUXER_STK_SIZE            (4096 << 2)
#if (VIDEO_BGPARSER_EN == 1)
#define BG_PARSER_STK_SIZE          (768 << 2)
#if (VIDEO_HIGHPRIORITY_FS == 1)
#define HIGH_PRIO_FS_STK_SIZE       (768 << 2)
#endif
#endif

// Video Encode Relative
#define VIDENC_TRIG_STK_SIZE        (2048 << 2)
#define VIDENC_DMA_GEN_STK_SIZE     (2048 << 2)
#define VIDENC_DONE_STK_SIZE        (2048 << 2)
#define VIDMGR_STK_SIZE             (2048 << 2)
#if (SUPPORT_H264_WIFI_STREAM)
#define WIFISTREAMCB_STK_SIZE       (1024 << 2)
#endif

// Audio Relative
#if (MP3HD_P_EN == 1)
#define AUDIO_PLAY_STK_SIZE         (5120 << 2)
#else
#define AUDIO_PLAY_STK_SIZE         (4096 << 2)
#endif
#define AUDIO_WRITEFILE_STK_SIZE    (4096 << 2)
#define AUDIO_RECORD_STK_SIZE       (4096 << 2)

// USB Relative
#define USB_STK_SIZE                (4096 << 2)
#define USB_UVCH_POSTPROC_STK_SIZE  (4096 << 2)
#define USB_UVCH_BULKIN_STK_SIZE    (4096 << 2)
#define USB_UHC_EHCI_STK_SIZE       (4096 << 2)

#define WIFI_STREAMING_STK_SIZE     (2048 << 2)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // _ALL_FW_H_

