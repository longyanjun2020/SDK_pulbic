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
 *  @file drv_scl_hvsp_ioctl.h
 *  @brief SCLHVSP Driver IOCTL interface
 */

/**
 * \defgroup sclhvsp_group  SCLHVSP driver
 * \note
 *
 * sysfs Node: /sys/devices/platform/mhvsp1.0/clk
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:print explain W:control clk by explain.
 *
 * sysfs Node: /sys/devices/platform/mhvsp1.0/ckcrop
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:print vsync count,err times W: if 0 close ptgen ,if echo 1 open check crop ,echo 2 open check hvsp and dma count
 *
 * sysfs Node: /sys/devices/platform/mhvsp1.0/ptgen
 *
 * sysfs R/W mode: R/W
 *
 * sysfs Usage & Description: R:print explain W: if 0 close ptgen ,if echo 1 open static ptgen ,echo 2 open dynamic ptgen,echo 3 open scl time gen
 *
 * @{
 */

#ifndef __DRV_SCL_HVSP_IOCTL_H__
#define __DRV_SCL_HVSP_IOCTL_H__

//=============================================================================
// Includs
//=============================================================================


//=============================================================================
// IOCTRL defines
//=============================================================================

#define IOCTL_SCLHVSP_SET_IN_CONFIG_NR           (0)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_IN_CONFIG
#define IOCTL_SCLHVSP_SET_OUT_CONFIG_NR          (1)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_OUT_CONFIG
#define IOCTL_SCLHVSP_SET_SCALING_CONFIG_NR      (2)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_SCALING_CONFIG
#define IOCTL_SCLHVSP_REQ_MEM_CONFIG_NR          (3)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_REQ_MEM_CONFIG
#define IOCTL_SCLHVSP_SET_MISC_CONFIG_NR         (4)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_MISC_CONFIG
#define IOCTL_SCLHVSP_SET_POST_CROP_CONFIG_NR    (5)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_POST_CROP_CONFIG
#define IOCTL_SCLHVSP_GET_PRIVATE_ID_CONFIG_NR   (6)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_GET_PRIVATE_ID_CONFIG
#define IOCTL_SCLHVSP_GET_INFORM_CONFIG_NR       (7)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_GET_INFORM_CONFIG
#define IOCTL_SCLHVSP_RELEASE_MEM_CONFIG_NR      (8)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_RELEASE_MEM_CONFIG
#define IOCTL_SCLHVSP_SET_OSD_CONFIG_NR          (9)   ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_OSD_CONFIG
#define IOCTL_SCLHVSP_SET_FB_MANAGE_CONFIG_NR    (10)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_FB_MANAGE_CONFIG
#define IOCTL_SCLHVSP_SET_PRIMASK_CONFIG_NR      (11)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_PRIMASK_CONFIG
#define IOCTL_SCLHVSP_PRIMASK_TRIGGER_CONFIG_NR  (12)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_PRIMASK_TRIGGER_CONFIG
#define IOCLT_SCLHVSP_GET_VERSION_CONFIG_NR      (13)  ///< The IOCTL NR definition for IOCLT_SCLHVSP_GET_VERSION_CONFIG
#define IOCTL_SCLHVSP_SET_ROTATE_CONFIG_NR       (14)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_ROTATE_CONFIG
#define IOCTL_SCLHVSP_SET_LOCK_CONFIG_NR         (15)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_LOCK_CONFIG
#define IOCTL_SCLHVSP_SET_UNLOCK_CONFIG_NR       (16)  ///< The IOCTL NR definition for IOCTL_SCLHVSP_SET_UNLOCK_CONFIG
#define IOCTL_SCLHVSP_MAX_NR                     (17)  ///< The Max IOCTL NR for SCLHVSP driver


// use 'm' as magic number
#define IOCTL_HVSP_MAGIC                       ('1')///< The Type definition of IOCTL for hvsp driver
/**
* Setup input configuration of SCLHVSP. The structure of input parameter is DrvSclHvspIoInputConfig_t.
*/
#define IOCTL_SCLHVSP_SET_IN_CONFIG             _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_IN_CONFIG_NR)
/**
* Setup output configuration of SCLHVSP. The structure of input parameter is DrvSclHvspIoOutputConfig_t.
*/
#define IOCTL_SCLHVSP_SET_OUT_CONFIG            _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_OUT_CONFIG_NR)
/**
* Setup scaling configuration, of SlcHvsp. The structure of input parameter is DrvSclHvspIoScalingConfig_t.
*/
#define IOCTL_SCLHVSP_SET_SCALING_CONFIG         _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_SCALING_CONFIG_NR)
/**
* Allocate Memory for SCLHVSP. The structure of input parameter is DrvSclHvspIoReqMemConfig_t.
*/
#define IOCTL_SCLHVSP_REQ_MEM_CONFIG             _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_REQ_MEM_CONFIG_NR)
/**
* Access the register of SCLHVSP. The structure of input parameter is DrvSclHvspIoMiscConfig_t.
*/
#define IOCTL_SCLHVSP_SET_MISC_CONFIG            _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_MISC_CONFIG_NR)
/**
* Setup post-crop configuration of SCLHVSP. The structure of input parameter is DrvSclHvspIoPostCropConfig_t.
*/
#define IOCTL_SCLHVSP_SET_POST_CROP_CONFIG       _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_POST_CROP_CONFIG_NR)
/**
* Get the private id of multiinst. The structure of output parameter is DrvSclHvspIoPrivateIdConfig_t.
*/
#define IOCTL_SCLHVSP_GET_PRIVATE_ID_CONFIG      _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_GET_PRIVATE_ID_CONFIG_NR)
/**
* Get the setting information of SCLHVSP. The structure of output parameter is DrvSclHvspIoScInformConfig_t.
*/
#define IOCTL_SCLHVSP_GET_INFORM_CONFIG          _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_GET_INFORM_CONFIG_NR)
/**
* Release allocated memory of SlcHvsp. There is no parameter
*/
#define IOCTL_SCLHVSP_RELEASE_MEM_CONFIG         _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_RELEASE_MEM_CONFIG_NR)
/**
* Setup the OSD configuration. The structure of input parameter is DrvSclHvspIoOsdConfig_t.
*/
#define IOCTL_SCLHVSP_SET_OSD_CONFIG             _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_OSD_CONFIG_NR)
/**
* Setup FB management configuration of SCLHVSP for debugging. The structure of input parameter is DrvSclHvspIoSetFbManageConfig_t.
*/
#define IOCTL_SCLHVSP_SET_FB_MANAGE_CONFIG       _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_FB_MANAGE_CONFIG_NR)
/**
* Get the version of SCLHVSP. The structure of output parameter is DrvSclHvspIoVersionConfig_t.
*/
#define IOCTL_HVSP_GET_VERSION_CONFIG            _IO(IOCTL_HVSP_MAGIC,  IOCLT_SCLHVSP_GET_VERSION_CONFIG_NR)
/**
* Setup the PrivateMask configuration of SlcHvsp. The structure of input parameter is DrvSclHvspIoPriMaskConfig_t.
*/
#define IOCTL_SCLHVSP_SET_PRIMASK_CONFIG         _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_PRIMASK_CONFIG_NR)
/**
* Setup the PrivateMask Trigger configuration of SCLHVSP. The structure of input parameter is DrvSclHvspIoPriMaskTriggerConfig_t.
*/
#define IOCTL_SCLHVSP_PRIMASK_TRIGGER_CONFIG     _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_PRIMASK_TRIGGER_CONFIG_NR)
/**
* Setup the rotate configuration. The structure of input parameter is DrvSclHvspIoRotateConfig_t
*/
#define IOCTL_SCLHVSP_SET_ROTATE_CONFIG          _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_ROTATE_CONFIG_NR)
/**
* Setup the Lock configuration. The structure of input parameter is DrvSclHvspIoLockConfig_t
*/
#define IOCTL_SCLHVSP_SET_LOCK_CONFIG           _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_LOCK_CONFIG_NR)
/**
* Setup the UnLock configuration. The structure of input parameter is DrvSclHvspIoLockConfig_t
*/
#define IOCTL_SCLHVSP_SET_UNLOCK_CONFIG         _IO(IOCTL_HVSP_MAGIC,  IOCTL_SCLHVSP_SET_UNLOCK_CONFIG_NR)

#endif //
/** @} */ // end of sclhvsp_group
