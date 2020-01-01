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
 *  @file drv_scl_pnl_ioctl.h
 *  @brief PNL Driver IOCTL interface
 */

/**
 * \defgroup sclpnl_group  SCLPNL driver
 * @{
 */
#ifndef __DRV_SCL_PNL_IOCTL_H__
#define __DRV_SCL_PNL_IOCTL_H__

//=============================================================================
// Includs
//=============================================================================


//=============================================================================
// IOCTRL defines
//=============================================================================


#define IOCTL_SCLPNL_SET_TIMING_CONFIG_NR          (0)///< The IOCTL NR definition for IOCTL_PNL_SET_TIMING_CONFIG
#define IOCTL_SCLPNL_SET_LPLL_CONFIG_NR            (1)///< The IOCTL NR definition for IOCTL_PNL_SET_TIMING_CONFIG
#define IOCLT_SCLPNL_GET_VERSION_CONFIG_NR         (2)///< The IOCTL NR definition for IOCTL_PNL_GET_VERSION_CONFIG
#define IOCTL_SCLPNL_SET_OUPUT_CONFIG_NR           (3)///< THe IOCTL NR definition for IOCTL_PNL_SET_OUPUT_CONFIG
#define IOCTL_SCLPNL_MAX_NR                        (4)///< The Max IOCTL NR for pnl driver

// use 'm' as magic number
#define IOCTL_SCLPNL_MAGIC                         ('8')///< The Type definition of IOCTL for pnl driver

/**
* Setup timing configuration for SCLPNL. The structure of input parameter is DrvSclPnlIoTimingConfig_t.
*/
#define IOCTL_SCLPNL_SET_TIMING_CONFIG             _IO(IOCTL_SCLPNL_MAGIC,  IOCTL_SCLPNL_SET_TIMING_CONFIG_NR)

/**
* Setup lpll configuration for SCLPNL. The structure of input parameter is DrvSclPnlIoTimingConfig_t.
*/
#define IOCTL_SCLPNL_SET_LPLL_CONFIG             _IO(IOCTL_SCLPNL_MAGIC,  IOCTL_SCLPNL_SET_LPLL_CONFIG_NR)


/**
* Get the version of SCLPNL. The structure of output parameter is DrvSclPnlIoVersionConfig_t.
*/
#define IOCTL_SCLPNL_GET_VERSION_CONFIG            _IO(IOCTL_SCLPNL_MAGIC,  IOCLT_SCLPNL_GET_VERSION_CONFIG_NR)

/**
* Set ouput configuration of SCLPNL. The structure of output parameter is DrvSclPnlIoOuputConfig_t.*/

#define IOCTL_SCLPNL_SET_OUTPUT_CONFIG             _IO(IOCTL_SCLPNL_MAGIC,  IOCTL_SCLPNL_SET_OUPUT_CONFIG_NR)
#endif //
/** @} */ // end of sclpnl_group
