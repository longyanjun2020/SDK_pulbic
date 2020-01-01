////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 *  @file drv_scl_dma_ioctl.h
 *  @brief SCLDMA Driver IOCTL interface
 */


/**
 * \defgroup scldma_group  SCLDMA driver
 * \note
 *
 * sysfs Node: /sys/devices/platform/mscldma1.0/ckfrm
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:check trig off count and dma line count W: if 0 reset scldma status ,if echo 1 all reset
 *
 * sysfs Node: /sys/devices/platform/mscldma1.0/cksnp
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:check trig off count and dma line count ,W: if 0 reset scldma status ,if echo 1 all reset
 *
 * sysfs Node: /sys/devices/platform/mscldma2.0/ckfrm
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:check trig off count and dma line count W: if 0 reset scldma status ,if echo 1 all reset
 *
 * sysfs Node: /sys/devices/platform/mscldma3.0/ckfrmR
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:check trig off count and dma line count W: if 0 reset scldma status ,if echo 1 all reset
 *
 * sysfs Node: /sys/devices/platform/mscldma3.0/ckfrmW
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:check trig off count and dma line count W: if 0 reset scldma status ,if echo 1 all reset
 *
 * @{
 */

#ifndef __DRV_SCL_DMA_IOCTL_H__
#define __DRV_SCL_DMA_IOCTL_H__

//=============================================================================
// Includs
//=============================================================================


//=============================================================================
// IOCTRL defines
//=============================================================================
#define IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG_NR            (0)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG
#define IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG_NR           (1)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG
#define IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG_NR           (2)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG
#define IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG_NR          (3)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG
#define IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG_NR     (4)  ///< The IOCTL NR definition for IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG
#define IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG_NR    (5)  ///< The IOCTL NR definition for IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG
#define IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG_NR           (6)  ///< The IOCTL NR definition for IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG
#define IOCTL_SCLDMA_SET_LOCK_CONFIG_NR                 (7)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_LOCK_CONFIG
#define IOCTL_SCLDMA_SET_UNLOCK_CONFIG_NR               (8)  ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_UNLOCK_CONFIG
#define IOCLT_SCLDMA_GET_VERSION_CONFIG_NR              (9)  ///< The IOCTL NR definition for IOCLT_SCLDMA_GET_VERSION_CONFIG
#define IOCTL_SCLDMA_GET_INFORMATION_CONFIG_NR          (10) ///< The IOCTL NR definition for IOCTL_SCLDMA_GET_INFORMATION_CONFIG
#define IOCTL_SCLDMA_SET_EXTERNAL_INPUT_CONFIG_NR       (11) ///< The IOCTL NR definition for IOCTL_SCLDMA_SET_EXTERNAL_INPUT_CONFIG
#define IOCTL_SCLDMA_BUFFER_QUEUE_HANDLE_CONFIG_NR      (12) ///< The IOCTL NR definition for IOCTL_SCLDMA_BUFFER_QUEUE_HANDLE_CONFIG
#define IOCTL_SCLDMA_MAX_NR                             (13)  ///< The Max IOCTL NR for scldma driver

// use 'm' as magic number
#define IOCTL_SCLDMA_MAGIC                       ('2')   ///< The Type definition of IOCTL for scldma driver

/**
* Setup parameters of in buffer configurate ,buffer address, number,dma mode,color mode and resolution, The structure of parameter is DrvSclDmaIoBufferConfig_t.
*/
#define IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG           _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_IN_BUFFER_CONFIG_NR)

/**
* Setup in buffer trigger configuration of DMA. The structure of  parameter is DrvSclDmaIoTriggerConfig_t.
*/
#define IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG          _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_IN_TRIGGER_CONFIG_NR)

/**
* Setup output buffer configuration, buffer address, number ,dma mode,color mode and resolution. The structure of parameter is DrvSclDmaIoBufferConfig_t.
*/
#define IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG          _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_OUT_BUFFER_CONFIG_NR)

/**
* Setup output buffer trigger configuration of DMA. The structure of parameter is DrvSclDmaIoTriggerConfig_t.
*/
#define IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG         _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_OUT_TRIGGER_CONFIG_NR)

/**
* The buffer controlling option of DMA_R to setup the R-point(by OMX) and get Wpoint with warning flag for DMA_R. The structure of parameter is DrvSclDmaIoActiveBufferConfig_t.
*/
#define IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG    _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_GET_IN_ACTIVE_BUFFER_CONFIG_NR)

/**
* The buffer controlling option of DMA_W to setup Rpoint(by OMX) and get Wpoint with warning flag. The structure of parameter is DrvSclDmaIoActiveBufferConfig_t.
*/
#define IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG   _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_GET_OUT_ACTIVE_BUFFER_CONFIG_NR)

/**
* Peek queue information and set read flag. The structure of parameter is DrvSclDmaIoBufferQueueConfig_t.
*/
#define IOCTL_SCLDMA_BUFFER_QUEUE_HANDLE_CONFIG     _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_BUFFER_QUEUE_HANDLE_CONFIG_NR)
/**
* Get private id of multi-instant. The structure of parameter is DrvSclDmaIoPrivateIdConfig_t.
*/
#define IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG          _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_GET_PRIVATE_ID_CONFIG_NR)

/**
* Setup Lock Configuration of DMA. The structure of parameter is DrvSclDmaIoLockConfig_t.
*/
#define IOCTL_SCLDMA_SET_LOCK_CONFIG                _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_LOCK_CONFIG_NR)

/**
* Setup Unlock configuration of DMA. The structure of parameter is DrvSclDmaIoLockConfig_t.
*/
#define IOCTL_SCLDMA_SET_UNLOCK_CONFIG              _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_SET_UNLOCK_CONFIG_NR)
/**
* Get version configuration of DMA.The structure of parameter is DrvSclDmaIoVersionConfig_t.
*/
#define IOCTL_SCLDMA_GET_VERSION_CONFIG            _IO(IOCTL_SCLDMA_MAGIC,  IOCLT_SCLDMA_GET_VERSION_CONFIG_NR)
/**
* Get informaion of DMA. The structure of parameter is DrvSclDmaIoGetInformationConfig_t.
*/
#define IOCTL_SCLDMA_GET_INFORMATION_CONFIG         _IO(IOCTL_SCLDMA_MAGIC,  IOCTL_SCLDMA_GET_INFORMATION_CONFIG_NR)
/**
* Set external input configuration of DMA. The structure of parameter is DrvSclDmaIoExternalInputConfig_t.
*/
#define IOCTL_SCLDMA_SET_EXTERNAL_INPUT_CONFIG      _IO(IOCTL_SCLDMA_MAGIC, IOCTL_SCLDMA_SET_EXTERNAL_INPUT_CONFIG_NR)
#endif //

/** @} */ // end of scldma_group
