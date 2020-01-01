/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                            OS LAYER CONFIGURATIONS
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_os_cfg.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_OS_CFG_H_
#define _USBEH_OS_CFG_H_

#define USBEH_KERNEL_UCOSII         (1)
#define USBEH_KERNEL                (USBEH_KERNEL_UCOSII)

#define USBEH_OS_ENUM_TASK_PRIO     (30)
#define USBEH_OS_XFER_TASK_PRIO     (31)
#define USBEH_OS_ENUM_TASK_STK_SIZE (512)
#define USBEH_OS_XFER_TASK_STK_SIZE (512)
#define USBEH_OS_ENUM_MSGQ_SIZE     (10)
#define USBEH_OS_XFER_MSGQ_SIZE     (10)

#endif //_USBEH_OS_CFG_H_