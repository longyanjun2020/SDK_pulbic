
/****************************************************************************/
/*  File    : sys_sys_sem_def.h                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : define semaphore number                                       */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/****************************************************************************/

#ifndef __SYS_SYS_SEM_DEF_H__
#define __SYS_SYS_SEM_DEF_H__


#include "sys_rtk_config.h"
#include "vm_osdef.hc"
#include "vm_types.ht"  /* __MSTAR_DUAL_SIM_REDUCE_CODE__ */


/*
 ** =========================================================================
 **     SEMAPHORE DEFINITION
 ** =========================================================================
 */
/******* Warning: These constants must be synchronised with "cus_InitSem" (file init.c) ******/

/* 1. peterwei: collect semaphore definition here
 *    note that only 14 semaphores are allocated for CUS, do not exceed this limit
 * 2. more 10 custom semaphore added by CAMEL 24-FEB-2006 (14->24)
 */

/* Eric: to keep the consistency between the define order and init value,  */
/* DON'T WRAP THE COMPILE OPTION HERE BELOW!!                           */

#define VM_SEM_CUS_FIRST        0
#define VM_SEM_CUS_LAST         24
#define CUS_FIRST_SEM           VM_SEM_CUS_FIRST
#define CUS_LAST_SEM            VM_SEM_CUS_LAST

#define EMA_SEM                 (VM_SEM_CUS_FIRST)
#define AFO_CLASSTABLE_SEM      (VM_SEM_CUS_FIRST+1)
#define AFO_SORTCACHE_SEM       (VM_SEM_CUS_FIRST+2)
#define AFO_GLOBALCACHE_SEM     (VM_SEM_CUS_FIRST+3)
#define MSM_SEM                 (VM_SEM_CUS_FIRST+4)
#define LCD_DRIVER_SEM          (VM_SEM_CUS_FIRST+5)
#define ADC_CONVERT_SEM         (VM_SEM_CUS_FIRST+6)
#define MRL_SYNC_SERVICE_SEM    (VM_SEM_CUS_FIRST+7)    /* sempahore for mml synchronized service */
#define UI_SPEED_PROFILE_SEM    (VM_SEM_CUS_FIRST+8)
#define NET_RECV_BUFFER_SEM     (VM_SEM_CUS_FIRST+9)    /* add by Edward */
#define EMA_SYNC_RSP_SEM        (VM_SEM_CUS_FIRST+10)
#define MEMORY_SEM              (VM_SEM_CUS_FIRST+11)   /* semaphore for memory management mechanism */
#define MMI_VENDOR_SEM          (VM_SEM_CUS_FIRST+12)   /* add by Mark.Yang. used to implement IPTV integration interface */
#define USB_CDC_SEM             (VM_SEM_CUS_FIRST+13)     /* semaphore for USB CDC */
#define EMA_POWER_SAVING_SEM    (VM_SEM_CUS_FIRST+14)
#define GPD_SYNC_SEM            (VM_SEM_CUS_FIRST+15)     /* semaphore for GPD sync service */
#define VOC_SYNC_SEM            (VM_SEM_CUS_FIRST+16)     /* semaphore for VOC sync service */
#define VOC_MSG_SEM             (VM_SEM_CUS_FIRST+17)     /* semaphore for VOC service */
#define BT_OBEX_SEM             (VM_SEM_CUS_FIRST+18)
#define VFS_SEM                 (VM_SEM_CUS_FIRST+19)     /* semaphore for VFS layer */
#define VFS_TASK_SYNC_RSP_SEM   (VM_SEM_CUS_FIRST+20)
#define VOC_PCM_SEM             (VM_SEM_CUS_FIRST+21)     /* semaphore for VOC PCM service */
#define IPTV_RECV_SEM           (VM_SEM_CUS_FIRST+22)
#define IPTV_SYNC_SEM           (VM_SEM_CUS_FIRST+23)

/*#### Stack semaphore ###*/

#define SPV_SEM             CUS_LAST_SEM + 1 // 25
#define E2P_SEM             CUS_LAST_SEM + 2
#define I2C_SEM             CUS_LAST_SEM + 3
#define V24_SEM             CUS_LAST_SEM + 4
#define OBJ_SEM             CUS_LAST_SEM + 5
#define VML_SEM_1           CUS_LAST_SEM + 6 // 30
#define SPI1_SEM            CUS_LAST_SEM + 7
#define CUS_RECORD_SEM      CUS_LAST_SEM + 8
#define E2P_CACHE_SEM       CUS_LAST_SEM + 9
#define LOG_UTIL_SEM        CUS_LAST_SEM + 10
#define OBJ_HASH_SEM        CUS_LAST_SEM + 11 // 35
#define __LAST_SEM          CUS_LAST_SEM + 11

/***************  Add above new stack semaphore : modify these constants ******/
/***************  Add new semaphore in "cus_InitSem" file init.c  ******/
#define V24_UART2_SEM       __LAST_SEM + 1 // 36
#define V24_USB_SEM         __LAST_SEM + 2
#define ERASURE_SEM         __LAST_SEM + 3
#define RTC_SEM             __LAST_SEM + 4
#define DWL_SEM             __LAST_SEM + 5 // 40
#define RCM_SEM             __LAST_SEM + 6 // 41

#define __FIRST_SEM_RPC     __LAST_SEM + 6
/***************  Avoid using compilation flag here ********************/
/***************  End modification                  ********************/

#define TASK_RTK_SLEEP_SEM (__FIRST_SEM_RPC + 1) // 42
#define SPV2_SEM           (__FIRST_SEM_RPC + 2)
#define SPARE_SEM          (__FIRST_SEM_RPC + 3)
#define FINTHISR_SEM       (__FIRST_SEM_RPC + 4) // 45

#define __FIRST_SEM_VEN    (__FIRST_SEM_RPC + 4)
/* !!!!!!!!!!!!!!!!!!! CHANGES ALLOWED FROM THERE !!!!!!!!!!!!!!!!!! */

#define VEN_FIRST_SEM      (__FIRST_SEM_VEN + 1) // 46
#define VEN_LAST_SEM       (__FIRST_SEM_VEN + 8) // 53

#define CUS_2_FIRST_SEM    (VEN_LAST_SEM + 1)    // 54
#define CUS_2_LAST_SEM     (VEN_LAST_SEM + 161)

#define VM_SEM_CUS_2_FIRST  CUS_2_FIRST_SEM      // 54
#define VM_SEM_VEN_LAST     VEN_LAST_SEM


#define GPD_REENTRY_LOCK_SEM                (VM_SEM_CUS_2_FIRST + 0) // 54
#define VOC_REENTRY_LOCK_SEM                (VM_SEM_CUS_2_FIRST + 1)
#define EMA_REENTRY_LOCK_SEM                (VM_SEM_CUS_2_FIRST + 2)
#define VFS_TASK_REENTRY_LOCK_SEM           (VM_SEM_CUS_2_FIRST + 3)
#define NAND_TRC_REENTRY_LOCK_SEM           (VM_SEM_CUS_2_FIRST + 4)
#define NAND_TRC_SYNC_RESPONSE_SEM          (VM_SEM_CUS_2_FIRST + 5)
#define DISP_SEM                            (VM_SEM_CUS_2_FIRST + 6) // 60
#define EXTMMI_CONTENTDB_SYNC_SEM           (VM_SEM_CUS_2_FIRST + 7)
#define BT_A2DP_LOCK_SEM                    (VM_SEM_CUS_2_FIRST + 8)
#define RAI_CACHE_REENTRY_LOCK_SEM          (VM_SEM_CUS_2_FIRST + 9)
#define MULTI_TASK_EMA_SEM                  (VM_SEM_CUS_2_FIRST + 10)
#define EFS_CMD_SEM                         (VM_SEM_CUS_2_FIRST + 11) // 65
//#define GSS_CMD_SEM                       (VM_SEM_CUS_2_FIRST + 12)
#define UDI_DRV_SEM01                       (VM_SEM_CUS_2_FIRST + 13)
#define AUDIOPLAY_DOUBLE_BUF_SEM            (VM_SEM_CUS_2_FIRST + 14)
#define READTHREAD_START_SEM                (VM_SEM_CUS_2_FIRST + 15)
#define SEM_MIDI_CONVERTING                 (VM_SEM_CUS_2_FIRST + 16) // 70
#define MIDI_STREAM_DONE                    (VM_SEM_CUS_2_FIRST + 17)
#define MDL_PM_CMD_QUEUE_SEM                (VM_SEM_CUS_2_FIRST + 18)
#define MDL_PM_SYNC_CMD_SEM                 (VM_SEM_CUS_2_FIRST + 19)
#define EFAT_FILEIO_LOCK_SEM01              (VM_SEM_CUS_2_FIRST + 20)
#define EFAT_FSTAB_LOCK_SEM01               (VM_SEM_CUS_2_FIRST + 21) // 75
#define EFAT_FSTAB_LOCK_SEM02               (VM_SEM_CUS_2_FIRST + 22)
#define EFAT_FSTAB_LOCK_SEM03               (VM_SEM_CUS_2_FIRST + 23)
#define EFAT_FSTAB_LOCK_SEM04               (VM_SEM_CUS_2_FIRST + 24)
#define EFAT_MTAB_LOCK_SEM01                (VM_SEM_CUS_2_FIRST + 25)
#define EFAT_MTAB_LOCK_SEM02                (VM_SEM_CUS_2_FIRST + 26) // 80
#define EFAT_MTAB_LOCK_SEM03                (VM_SEM_CUS_2_FIRST + 27)
#define EFAT_MTAB_LOCK_SEM04                (VM_SEM_CUS_2_FIRST + 28)
#define EFAT_MTAB_LOCK_SEM05                (VM_SEM_CUS_2_FIRST + 29)
#define EFAT_MTAB_LOCK_SEM06                (VM_SEM_CUS_2_FIRST + 30)
#define EFAT_MTAB_LOCK_SEM07                (VM_SEM_CUS_2_FIRST + 31) // 85
#define EFAT_MTAB_LOCK_SEM08                (VM_SEM_CUS_2_FIRST + 32)
#define EFAT_SHORTNAME_CACHE_LOCK_SEM01     (VM_SEM_CUS_2_FIRST + 33)
#define EFAT_SEM_DRAM_BUF_SEM01             (VM_SEM_CUS_2_FIRST + 34)
#define EFAT_SEM_DRAM_BUF_SEM02             (VM_SEM_CUS_2_FIRST + 35)
#define EFAT_DISK_COND_CM_SEM01             (VM_SEM_CUS_2_FIRST + 36) // 90
#define EFAT_DISK_COND_SEMSUM_SEM01         (VM_SEM_CUS_2_FIRST + 37)
#define EFAT_DISK_COND_SEMHAND_SEM01        (VM_SEM_CUS_2_FIRST + 38)
#define EFAT_CHDIR_WAIT_CM_SEM01            (VM_SEM_CUS_2_FIRST + 39)
#define EFAT_CHDIR_WAIT_SEMSUM_SEM01        (VM_SEM_CUS_2_FIRST + 40)
#define EFAT_CHDIR_WAIT_SEMHAND_SEM01       (VM_SEM_CUS_2_FIRST + 41) // 95
#define EFAT_FILE_LCOK_SEM01                (VM_SEM_CUS_2_FIRST + 42)
#define EFAT_FILE_LCOK_SEM02                (VM_SEM_CUS_2_FIRST + 43)
#define EFAT_FILE_LCOK_SEM03                (VM_SEM_CUS_2_FIRST + 44)
#define EFAT_FILE_LCOK_SEM04                (VM_SEM_CUS_2_FIRST + 45)
#define EFAT_FILE_LCOK_SEM05                (VM_SEM_CUS_2_FIRST + 46) // 100
#define EFAT_FILE_LCOK_SEM06                (VM_SEM_CUS_2_FIRST + 47)
#define EFAT_FILE_LCOK_SEM07                (VM_SEM_CUS_2_FIRST + 48)
#define EFAT_FILE_LCOK_SEM08                (VM_SEM_CUS_2_FIRST + 49)
#define EFAT_FILE_LCOK_SEM09                (VM_SEM_CUS_2_FIRST + 50)
#define EFAT_FILE_LCOK_SEM10                (VM_SEM_CUS_2_FIRST + 51) // 105
#define EFAT_FILE_LCOK_SEM11                (VM_SEM_CUS_2_FIRST + 52)
#define EFAT_FILE_LCOK_SEM12                (VM_SEM_CUS_2_FIRST + 53)
#define EFAT_FILE_LCOK_SEM13                (VM_SEM_CUS_2_FIRST + 54)
#define EFAT_FILE_LCOK_SEM14                (VM_SEM_CUS_2_FIRST + 55)
#define EFAT_FILE_LCOK_SEM15                (VM_SEM_CUS_2_FIRST + 56) // 110
#define EFAT_FILE_LCOK_SEM16                (VM_SEM_CUS_2_FIRST + 57)
#define EFAT_FILE_LCOK_SEM17                (VM_SEM_CUS_2_FIRST + 58)
#define EFAT_FILE_LCOK_SEM18                (VM_SEM_CUS_2_FIRST + 59)
#define EFAT_FILE_LCOK_SEM19                (VM_SEM_CUS_2_FIRST + 60)
#define EFAT_FILE_LCOK_SEM20                (VM_SEM_CUS_2_FIRST + 61) // 115
#define MAR_DOUBLE_BUF_SEM                  (VM_SEM_CUS_2_FIRST + 62)
#define SDIO_LOCK_SEM                       (VM_SEM_CUS_2_FIRST + 63)
#define JPE_GETBITS_SEM                     (VM_SEM_CUS_2_FIRST + 64)
#define MML_MANAGER_SEM                     (VM_SEM_CUS_2_FIRST + 65)
#define SCL_DONE_SEM                        (VM_SEM_CUS_2_FIRST + 66) // 120
#define VDR_RING_V_SEM_MUTEX                (VM_SEM_CUS_2_FIRST + 67)
#define VDR_RING_V_SEM_ITEM                 (VM_SEM_CUS_2_FIRST + 68)
#define VDR_RING_V_SEM_SPACE                (VM_SEM_CUS_2_FIRST + 69)
#define VDR_RING_A_SEM_MUTEX                (VM_SEM_CUS_2_FIRST + 70)
#define VDR_RING_A_SEM_ITEM                 (VM_SEM_CUS_2_FIRST + 71) // 125
#define VDR_RING_A_SEM_SPACE                (VM_SEM_CUS_2_FIRST + 72)
#define MDL_AVP_SEM_01                      (VM_SEM_CUS_2_FIRST + 73)
#define MDL_AVP_SEM_02                      (VM_SEM_CUS_2_FIRST + 74)
#define MDL_AVP_SEM_03                      (VM_SEM_CUS_2_FIRST + 75)
#define MDL_AVP_SEM_04                      (VM_SEM_CUS_2_FIRST + 76) // 130
#define MDL_AVP_SEM_05                      (VM_SEM_CUS_2_FIRST + 77)
#define MDL_AVP_SEM_06                      (VM_SEM_CUS_2_FIRST + 78)
#define MDL_AVP_SEM_07                      (VM_SEM_CUS_2_FIRST + 79)
#define MDL_AVP_SEM_08                      (VM_SEM_CUS_2_FIRST + 80)
#define MDL_AVP_SEM_09                      (VM_SEM_CUS_2_FIRST + 81) // 135
#define MDL_AVP_SEM_10                      (VM_SEM_CUS_2_FIRST + 82)
#define MDL_AVP_SEM_11                      (VM_SEM_CUS_2_FIRST + 83)
#define MDL_AVP_SEM_12                      (VM_SEM_CUS_2_FIRST + 84)
#define MDL_AVP_SEM_13                      (VM_SEM_CUS_2_FIRST + 85)
#define MDL_AVP_SEM_14                      (VM_SEM_CUS_2_FIRST + 86) // 140
#define MDL_AVP_SEM_15                      (VM_SEM_CUS_2_FIRST + 87)
#define MDL_AVP_SEM_16                      (VM_SEM_CUS_2_FIRST + 88)
#define MDL_AVP_SEM_17                      (VM_SEM_CUS_2_FIRST + 89)
#define MDL_AVP_SEM_18                      (VM_SEM_CUS_2_FIRST + 90)
#define MDL_AVP_SEM_19                      (VM_SEM_CUS_2_FIRST + 91) // 145
#define MDL_AVP_SEM_20                      (VM_SEM_CUS_2_FIRST + 92)
#define MDL_AVP_SEM_21                      (VM_SEM_CUS_2_FIRST + 93)
#define MDL_AVP_SEM_22                      (VM_SEM_CUS_2_FIRST + 94)
#define MDL_AVP_SEM_23                      (VM_SEM_CUS_2_FIRST + 95)
#define MDL_AVP_SEM_24                      (VM_SEM_CUS_2_FIRST + 96) // 150
#define MDL_AVP_SEM_25                      (VM_SEM_CUS_2_FIRST + 97)
#define MDL_AVP_SEM_26                      (VM_SEM_CUS_2_FIRST + 98)
#define MDL_AVP_SEM_27                      (VM_SEM_CUS_2_FIRST + 99)
#define MDL_AVP_SEM_28                      (VM_SEM_CUS_2_FIRST +100)
#define MDL_AVP_SEM_29                      (VM_SEM_CUS_2_FIRST +101) // 155
#define MDL_AVP_SEM_30                      (VM_SEM_CUS_2_FIRST +102)
#define MDL_AVP_SEM_31                      (VM_SEM_CUS_2_FIRST +103)
#define MDL_AVP_SEM_32                      (VM_SEM_CUS_2_FIRST +104)
#define A2DP_DOUBLE_BUF_SEM                 (VM_SEM_CUS_2_FIRST +105) /*Used for A2DP Ring buffer*/
#define DMA2D_FINISH_SEM                    (VM_SEM_CUS_2_FIRST +106) // 160
#define MDL_JPD_GETBITS_DONE_ERR_SEM        (VM_SEM_CUS_2_FIRST +107)
#define FCIE_LOCK_SEM                       (VM_SEM_CUS_2_FIRST +108)
#define USB_UVC_WAIT_ENCODE_SEM             (VM_SEM_CUS_2_FIRST +109) /* USB_UVC to wait encoding */
#define MDL_JPD_SCL_DONE_SEM                (VM_SEM_CUS_2_FIRST +110)
#define MDL_JPD_GETBITS_BUF_SEM             (VM_SEM_CUS_2_FIRST +111) // 165
#define DBB_I2C_SEM                         (VM_SEM_CUS_2_FIRST +112)
#define EFAT_DIRECTRW_SEM                   (VM_SEM_CUS_2_FIRST +113)
/**************************************************************
 * User can change the name of TO_BE_USE_XXX_SEM as user want. *
 **************************************************************/
#define DISP_CTRL_SEM                       (VM_SEM_CUS_2_FIRST +114)

#define EFAT_DIRECTRW_SEM_2                 (VM_SEM_CUS_2_FIRST +115)
#define EFAT_DISK_COND_CM_SEM02             (VM_SEM_CUS_2_FIRST +116) // 170
#define EFAT_DISK_COND_SEMSUM_SEM02         (VM_SEM_CUS_2_FIRST +117)
#define EFAT_DISK_COND_SEMHAND_SEM02        (VM_SEM_CUS_2_FIRST +118)

#define IMGCODEC_SCL_SEM                    (VM_SEM_CUS_2_FIRST +119)
#define EML_SCL_SEM                         (VM_SEM_CUS_2_FIRST +120)
#define MDL_JPD_SCL_BUF_DONE_SEM            (VM_SEM_CUS_2_FIRST +121) // 175
#define MDL_CPU_SPEED                       (VM_SEM_CUS_2_FIRST +122)

#define EFAT_DIRECTRW_SEM_3                 (VM_SEM_CUS_2_FIRST +123)
#define EFAT_DISK_COND_CM_SEM03             (VM_SEM_CUS_2_FIRST +124)
#define EFAT_DISK_COND_SEMSUM_SEM03         (VM_SEM_CUS_2_FIRST +125)
#define EFAT_DISK_COND_SEMHAND_SEM03        (VM_SEM_CUS_2_FIRST +126) // 180

#define SYNC_STORAGE_INIT_SEM               (VM_SEM_CUS_2_FIRST +127)
#define MTMGR_PARSER_SEM                    (VM_SEM_CUS_2_FIRST +128)
#define EFAT_REENTRY_PROTECT                (VM_SEM_CUS_2_FIRST +129)
#define MDL_MAR_SEM_INIT                    (VM_SEM_CUS_2_FIRST +130)
#define DISP_SYNC_LOCK_SEM                  (VM_SEM_CUS_2_FIRST +131) // 185
#define STORAGE_READY_SEM                   (VM_SEM_CUS_2_FIRST +132)
#define CUS_KERNELTEST_SEM_0                (VM_SEM_CUS_2_FIRST +133)
#define CUS_KERNELTEST_SEM_1                (VM_SEM_CUS_2_FIRST +134)
#define CUS_KERNELTEST_SEM_2                (VM_SEM_CUS_2_FIRST +135)
#define BITBLT_DMA2D_SEM                    (VM_SEM_CUS_2_FIRST +136) // 190
#define AUD_SPEC_BUF_SEM                    (VM_SEM_CUS_2_FIRST +137)
#define MMAP_DTLB_SEM                       (VM_SEM_CUS_2_FIRST +138)
#define MMAP_KERNEL_SEM                     (VM_SEM_CUS_2_FIRST +139)
#define MMAP_DTLB_SYNC_SEM                  (VM_SEM_CUS_2_FIRST +140)
#define AEC_RING_INBUF_SEM                  (VM_SEM_CUS_2_FIRST+141) // 195
#define AEC_RING_OUTBUF_SEM                 (VM_SEM_CUS_2_FIRST+142)
#define DPM_LOADUNLOAD_SEM                  (VM_SEM_CUS_2_FIRST +143)
#define SLDLM_REFCNT_SEM                    (VM_SEM_CUS_2_FIRST +144)
#define DPM_CONF_SEM                        (VM_SEM_CUS_2_FIRST +145)
#define DPM_SCHED_SEM                       (VM_SEM_CUS_2_FIRST +146) // 200
#define DPM_KERNEL_SEM                      (VM_SEM_CUS_2_FIRST +147)
#define DPM_SERIAL_SEM                      (VM_SEM_CUS_2_FIRST +148) //202
#define DISP_TASK_SEM                       (VM_SEM_CUS_2_FIRST +149)
#define DISP_TASK_DISP_FINISH_SEM           (VM_SEM_CUS_2_FIRST +150) //204
#define A2DP_RING_SEM                       (VM_SEM_CUS_2_FIRST +151) // 205
#define A2DP_REENTRY_LOCK_SEM               (VM_SEM_CUS_2_FIRST +152)
#define A2DP_SYNC_SEM                       (VM_SEM_CUS_2_FIRST +153)

#define EFAT_DIRECTRW_SEM_4                 (VM_SEM_CUS_2_FIRST +154)
#define EFAT_DISK_COND_CM_SEM04             (VM_SEM_CUS_2_FIRST +155)
#define EFAT_DISK_COND_SEMSUM_SEM04         (VM_SEM_CUS_2_FIRST +156) // 210
#define EFAT_DISK_COND_SEMHAND_SEM04        (VM_SEM_CUS_2_FIRST +157)
#define EFAT_FDLCOK_SEM01                   (VM_SEM_CUS_2_FIRST +158)
#define SLDLM_KERNEL_SEM                    (VM_SEM_CUS_2_FIRST +159)
#define FMRX_SEM01                          (VM_SEM_CUS_2_FIRST +160)


#define CUS_2_EXT_FIRST_SEM          (CUS_2_LAST_SEM+1) //200
#define CUS_2_EXT_LAST_SEM           (CUS_2_LAST_SEM+8) //207


#define CUS_FILEMGR_FIRST_SEM        (CUS_2_EXT_LAST_SEM + 1) //208
#define CUS_FILEMGR_LAST_SEM         (CUS_2_EXT_LAST_SEM + 10) //217

#define FILEMGR_SEM_MARK_FOLDER      (CUS_FILEMGR_FIRST_SEM+0)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_DELETE_ALL       (CUS_FILEMGR_FIRST_SEM+1)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_1                (CUS_FILEMGR_FIRST_SEM+2)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_2                (CUS_FILEMGR_FIRST_SEM+3)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_3                (CUS_FILEMGR_FIRST_SEM+4)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_4                (CUS_FILEMGR_FIRST_SEM+5)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_5                (CUS_FILEMGR_FIRST_SEM+6)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_6                (CUS_FILEMGR_FIRST_SEM+7)   /* semaphore for (filemgr) */
#define FILEMGR_SEM_7                (CUS_FILEMGR_FIRST_SEM+8)   /* semaphore for (filemgr) */
#define FS_TEST_CASE_WAIT_SEM        (CUS_FILEMGR_FIRST_SEM+9)

#define CUS_SOCKETMGR_FIRST_SEM      (CUS_FILEMGR_LAST_SEM+1) //218
#define CUS_SOCKETMGR_LAST_SEM       (CUS_FILEMGR_LAST_SEM+3) //220
#define SOCKETMGR_SOCKET_SEM         (CUS_SOCKETMGR_FIRST_SEM+0) /* semaphore for socket manager */
#define SOCKETMGR_CMD_SEM            (CUS_SOCKETMGR_FIRST_SEM+1) /* semaphore for socket manager */
#define SOCKETMGR_SRV_SEM            (CUS_SOCKETMGR_FIRST_SEM+2) /* semaphore for socket manager */

#define CUS_RESMGR_FIRST_SEM         (CUS_SOCKETMGR_LAST_SEM+1) //221
#define CUS_RESMGR_LAST_SEM          (CUS_SOCKETMGR_LAST_SEM+8) //228
#define RESMGR_SYNC_SEM              (CUS_RESMGR_FIRST_SEM+0)   /* semaphore for resource manager */
#define RESMGR_REENTRY_SEM           (CUS_RESMGR_FIRST_SEM+1)   /* semaphore for resource manager */
#define RESMGR_TASK_SYNC_SEM         (CUS_RESMGR_FIRST_SEM+2)   /* semaphore for resource manager */
#define RESMGR_RINGBUFF_SEM          (CUS_RESMGR_FIRST_SEM+3)   /* semaphore for resource manager */
#define RESMGR_GSS_SYNC_SEM          (CUS_RESMGR_FIRST_SEM+4)   /* semaphore for resource manager */
#define RESMGR_GSS_REENTRY_SEM       (CUS_RESMGR_FIRST_SEM+5)   /* semaphore for resource manager */
#define RESMGR_CTRL_SYNC_SEM         (CUS_RESMGR_FIRST_SEM+6)   /* semaphore for resource manager */
#define RESMGR_CTRL_REENTRY_SEM      (CUS_RESMGR_FIRST_SEM+7)   /* semaphore for resource manager */

#define CUS_NRAI_FIRST_SEM           (CUS_RESMGR_LAST_SEM+1)
#define CUS_NRAI_LAST_SEM            (CUS_RESMGR_LAST_SEM+1)
#define NRAI_SYNC_RSP_SEM            (CUS_NRAI_FIRST_SEM+0) //227

#define CUS_DLM_FIRST_SEM            (CUS_NRAI_LAST_SEM+1)
#define CUS_DLM_LAST_SEM             (CUS_NRAI_LAST_SEM+1)
#define DLM_ACTION_SEM               (CUS_DLM_FIRST_SEM+0) //228

#define MMI_FIRST_SEM                (CUS_DLM_LAST_SEM + 1) // 229
#define MMI_LAST_SEM                 (CUS_DLM_LAST_SEM + 7)  /// remember to update it when you add MMI semaphore
#define MMI_SEM1                     (MMI_FIRST_SEM + 0)
#define MMI_SEM2                     (MMI_FIRST_SEM + 1)
#define MMI_SEM3                     (MMI_FIRST_SEM + 2)
#define MMI_SEM4                     (MMI_FIRST_SEM + 3)
#define MMI_SEM5                     (MMI_FIRST_SEM + 4)
#define MMI_SEM6                     (MMI_FIRST_SEM + 5)    /* semaphore for font compression */
#define MMI_SEM7                     (MMI_FIRST_SEM + 6)    /* semaphore for KMX IME use */

#define MGL_FIRST_SEM                (MMI_LAST_SEM + 1)  // 235
#define MGL_LAST_SEM                 (MMI_LAST_SEM + 1)  // 235
#define MGL_SEM_POWER                (MGL_FIRST_SEM + 0) /* semaphore for g3d power on/off */

#define VT_FIRST_SEM                 (MGL_LAST_SEM+1) //236
#define VT_LAST_SEM                  (MGL_LAST_SEM+11) //246
#define VT_SEM_00                    (VT_FIRST_SEM+0)
#define VT_SEM_01                    (VT_FIRST_SEM+1)
#define VT_SEM_02                    (VT_FIRST_SEM+2)
#define VT_SEM_03                    (VT_FIRST_SEM+3)
#define VT_SEM_04                    (VT_FIRST_SEM+4)
#define VT_VDR_RING_V_SEM_MUTEX                (VT_FIRST_SEM + 5)
#define VT_VDR_RING_V_SEM_ITEM                 (VT_FIRST_SEM + 6)
#define VT_VDR_RING_V_SEM_SPACE                (VT_FIRST_SEM + 7)
#define VT_VDR_RING_A_SEM_MUTEX                (VT_FIRST_SEM + 8)
#define VT_VDR_RING_A_SEM_ITEM                 (VT_FIRST_SEM + 9)
#define VT_VDR_RING_A_SEM_SPACE                (VT_FIRST_SEM + 10)

#define SUP_WPA_FIRST_SEM            (VT_LAST_SEM + 1) //247
#define SUP_WPA_LAST_SEM             (VT_LAST_SEM + 7) //253
#define SUP_WPA_SEM_CTRL             (SUP_WPA_FIRST_SEM + 0)            //for wpa_supplicant UI interface
#define SUP_WPA_SEM_DRIVER           (SUP_WPA_FIRST_SEM + 1)            //for wpa_supplicant WIFI driver notify
#define SUP_WPA_SEM_OID              (SUP_WPA_FIRST_SEM + 2)            //for wpa_supplicant OID blocking
#define SUP_WPA_SEM_L2_PKT           (SUP_WPA_FIRST_SEM + 3)            //for wpa_supplicant L2 packet receiving
#define SUP_WPA_SEM_CLOSE            (SUP_WPA_FIRST_SEM + 4)            //for wpa_supplicant Driver Close
#define SUP_WPA_SEM_SCAN             (SUP_WPA_FIRST_SEM + 5)            //for wpa_supplicant SCAN
#define SUP_WPA_SEM_CONNECT          (SUP_WPA_FIRST_SEM + 6)            //for wpa_supplicant CONNECT

#define WLAN_FIRST_SEM               (SUP_WPA_LAST_SEM + 1) //254
#define WLAN_LAST_SEM                (SUP_WPA_LAST_SEM + 5) //258
#define WLAN_TX_MEM_SEM              (WLAN_FIRST_SEM + 0)
#define WLAN_RX_MEM_SEM              (WLAN_FIRST_SEM + 1)
#define WLAN_TX_QUEUE_SEM            (WLAN_FIRST_SEM + 2)
#define WLAN_RX_QUEUE_SEM            (WLAN_FIRST_SEM + 3)
#define WLAN_DRV_SEM                 (WLAN_FIRST_SEM + 4)

#define MPIF_FIRST_SEM               (WLAN_LAST_SEM + 1) //259
#define MPIF_LAST_SEM                (WLAN_LAST_SEM + 2) //260
#define MPIF1_SEM                    (MPIF_FIRST_SEM  + 0)
#define MPIF2_SEM                    (MPIF_FIRST_SEM  + 1)

#define DRV_EXT_FIRST_SEM            (MPIF_LAST_SEM + 1) //261
#define DRV_EXT_LAST_SEM             (MPIF_LAST_SEM + 5) //265
#define SPI_SEM_1                    (DRV_EXT_FIRST_SEM + 0)
#define SPI_SEM_2                    (DRV_EXT_FIRST_SEM + 1)
#define SPI_SEM_3                    (DRV_EXT_FIRST_SEM + 2)
#define SPI_SEM_4                    (DRV_EXT_FIRST_SEM + 3)
#define CUS_CACHE_SEM                (DRV_EXT_FIRST_SEM + 4)

#define DRV_I2C_FIRST_SEM            (DRV_EXT_LAST_SEM + 1) //266
#define DRV_I2C_LAST_SEM             (DRV_EXT_LAST_SEM + 5) //270
#define DRV_I2C_GPIO_1_SEM           (DRV_I2C_FIRST_SEM + 0)
#define DRV_I2C_GPIO_2_SEM           (DRV_I2C_FIRST_SEM + 1)
#define DRV_I2C_GPIO_3_SEM           (DRV_I2C_FIRST_SEM + 2)
#define DRV_I2C_GPIO_4_SEM           (DRV_I2C_FIRST_SEM + 3)
#define DRV_I2C_GPIO_5_SEM           (DRV_I2C_FIRST_SEM + 4)

#define FMS_NVRAM_FIRST_SEM          (DRV_I2C_LAST_SEM + 1)
#define FMS_NVRAM_LAST_SEM           (DRV_I2C_LAST_SEM + 1)
#define FMS_NVRAM_SEM                (FMS_NVRAM_FIRST_SEM + 0)

#define GPS_FIRST_SEM                (FMS_NVRAM_LAST_SEM + 1)
#define GPS_LAST_SEM                 (FMS_NVRAM_LAST_SEM + 3)
#define GPS_COMMON_DATA_SEM          (GPS_FIRST_SEM + 0)
#define GPS_LOGGER_SEM               (GPS_FIRST_SEM + 1)
#define GPS_ALTE_SEM                 (GPS_FIRST_SEM + 2)

#define GDMA_FIRST_SEM               (GPS_LAST_SEM + 1)
#define GDMA_LAST_SEM                (GPS_LAST_SEM + 1)
#define GDMA_SEM                     (GDMA_FIRST_SEM + 0)

#define CLK_MIU_FIRST_SEM            (GDMA_LAST_SEM + 1)
#define CLK_MIU_LAST_SEM             (GDMA_LAST_SEM + 1)
#define CLK_MIU_SEM                  (CLK_MIU_FIRST_SEM + 0)
#define ADC_FIRST_SEM                (CLK_MIU_LAST_SEM+1)
#define ADC_LAST_SEM              (CLK_MIU_LAST_SEM+2)
#define ADC_SEM                      (ADC_FIRST_SEM+0)
#define ADC_RF_SEM                 (ADC_FIRST_SEM+1)


#define R2DMA_FIRST_SEM              (ADC_LAST_SEM + 1)
#define R2DMA_LAST_SEM               (ADC_LAST_SEM + 1)
#define R2DMA_SEM                    (R2DMA_FIRST_SEM + 0)

#define FCIE_FIRST_SEM               (R2DMA_LAST_SEM + 1)
#define FCIE_LAST_SEM                (R2DMA_LAST_SEM + 2)
#define FCIE_TIMER_SEM               (FCIE_FIRST_SEM + 0)
#define SDIO_TIMER_SEM               (FCIE_FIRST_SEM + 1)

#define FRO_FIRST_SEM               (FCIE_LAST_SEM + 1)
#define FRO_LAST_SEM                (FCIE_LAST_SEM + 1)
#define FRO_SEM                     (FRO_FIRST_SEM + 0)

#define BACH_FIRST_SEM               (FRO_LAST_SEM + 1)
#define BACH_LAST_SEM                (FRO_LAST_SEM + 1)
#define BACH_POWER_SEM               (BACH_FIRST_SEM + 0)

#define SQLITE_FIRST_SEM             (BACH_LAST_SEM + 1)
#define SQLITE_LAST_SEM              (BACH_LAST_SEM + 1)
#define SQLITE_SEM1                  (SQLITE_FIRST_SEM+0)

#define M18_FIRST_SEM                (SQLITE_LAST_SEM +1)
#define M18_LAST_SEM                 (SQLITE_LAST_SEM +1)
#define M18_SEM                      (M18_FIRST_SEM+0)

#define BDMA_FIRST_SEM               (M18_LAST_SEM + 1)
#define BDMA_LAST_SEM                (M18_LAST_SEM + 1)
#define BDMA_SEM                     (BDMA_FIRST_SEM + 0)

#define SDK_FIRST_SEM                (BDMA_LAST_SEM + 1)
#define SDK_LAST_SEM                 (BDMA_LAST_SEM + 128)
#define SDK_SEM                      (SDK_FIRST_SEM + 0)

#define WAP_FIRST_SEM                (SDK_LAST_SEM + 1)
#define WAP_LAST_SEM                 (SDK_LAST_SEM + 1)
#define WAP_SEM                     (WAP_FIRST_SEM + 0)

#define CUS_ATV_FIRST_SEM               (WAP_LAST_SEM + 1)
#define CUS_ATV_LAST_SEM                (WAP_LAST_SEM + 2)
#define CUS_3RD_ATV_NMI_SEM0        (CUS_ATV_FIRST_SEM+0)
#define CUS_3RD_ATV_NMI_SEM1        (CUS_ATV_FIRST_SEM+1)

#define IP_FIRST_SEM          (CUS_ATV_LAST_SEM + 1)
#define IP_LAST_SEM            (CUS_ATV_LAST_SEM + 2)
#define IP1_QUEUE_SEM       (IP_FIRST_SEM + 0)
#define IP2_QUEUE_SEM       (IP_FIRST_SEM + 1)

#define DRM_FIRST_SEM          (IP_LAST_SEM + 1)
#define DRM_LAST_SEM           (IP_LAST_SEM + 1)
#define DRM_SEM       (DRM_FIRST_SEM + 0)

#define MFE_FIRST_SEM                (DRM_LAST_SEM + 1)
#define MFE_LAST_SEM                 (DRM_LAST_SEM + 1)
#define MFE_SEM               (MFE_FIRST_SEM + 0)

#define DIP_FIRST_SEM           (MFE_LAST_SEM + 1)
#define DIP_LAST_SEM            (MFE_LAST_SEM + 4)
#define DIP_SEM                 (DIP_FIRST_SEM + 0)
#define DIP_DRV_FIRST_SEM       (DIP_LAST_SEM + 1)
#define DIP_DRV_LAST_SEM        (DIP_LAST_SEM + 4)
#define DIP_DRV_SEM             (DIP_DRV_FIRST_SEM + 0)

//#if defined(ALL_FW) //AIT semaphore
#define AIT_FIRST_SEM                (DIP_DRV_LAST_SEM + 1)
#define AIT_LAST_SEM                 (DIP_DRV_LAST_SEM + 250) // Map to MMPF_OS_SEMID_MAX.
#define AIT_SEM               (AIT_FIRST_SEM + 0)

#define MSPI_FIRST_SEM          (AIT_LAST_SEM + 1)
#define MSPI_LAST_SEM           (AIT_LAST_SEM + 4)
#define MSPI_SEM                (MSPI_FIRST_SEM + 0)

#define I2C_CH_SEM_FRIST        (MSPI_LAST_SEM + 1)
#define I2C_CH_SEM_LAST         (MSPI_LAST_SEM + 4)
#define I2C_CH_SEM              (I2C_CH_SEM_FRIST + 0)

// quantity depens on FS_LOCK_ID_VOLUME,use 100 as default
#define FS_LOCK_SEM_FRIST       (I2C_CH_SEM_LAST + 1)
#define FS_LOCK_SEM_LAST        (I2C_CH_SEM_LAST + 100)
#define FS_LOCK_SEM             (FS_LOCK_SEM_FRIST + 0)

#define NET_SEM_FRIST           (FS_LOCK_SEM_LAST + 1)
#define NET_SEM_LAST            (FS_LOCK_SEM_LAST + 250)
#define NET_SEM                 (NET_SEM_FRIST + 0)

#define SENSOR_I2C_CH_SEM_FRIST        (NET_SEM_LAST + 1)
#define SENSOR_I2C_CH_SEM_LAST         (NET_SEM_LAST + 4)
#define SENSOR_I2C_CH_SEM              (SENSOR_I2C_CH_SEM_FRIST + 0)

#define LAST_CUS_SEM            (SENSOR_I2C_CH_SEM_LAST)        /* the last one semaphore user must update it */

#endif /* __SYS_SYS_SEM_DEF_H__ */
