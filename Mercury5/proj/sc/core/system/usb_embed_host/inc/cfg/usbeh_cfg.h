/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                              CORE CONFIGURATIONS
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_cfg.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_CFG_H_
#define _USBEH_CFG_H_

#include "usbeh_cpu.h"
#include "usbeh_os_cfg.h"

/*
*-------------------------------------------------------------------------------
*                           Embedded Host Stack Verison
*-------------------------------------------------------------------------------
*/
#define USBEH_VERSION               (0x1000)
#define USBEH_VERSION_MAJOR         ((USBEH_VERSION & 0xF000) >> 12)
#define USBEH_VERSION_MINOR         ((USBEH_VERSION & 0x0F00) >> 8)
#define USBEH_VERSION_BUILD         (USBEH_VERSION & 0x00FF)

/*
*-------------------------------------------------------------------------------
*                           Maximum Endpoints Supported
*-------------------------------------------------------------------------------
*/
#define USBEH_MAX_LOG_EP_NUM        (5) /* the max logical EP number allowed */

/*
*-------------------------------------------------------------------------------
*                              Device Base Address
*-------------------------------------------------------------------------------
*/
#define USBEH_DEV_BASE_ADDR         (1)

/*
*-------------------------------------------------------------------------------
*                     Embedded Host Stack Working Buffer Size
*-------------------------------------------------------------------------------
*/
#define USBEH_EP0_DATA_BUF_SIZE     (512)
#define USBEH_DEV_DESC_BUF_SIZE     (64)
#define USBEH_CFG_DESC_BUF_SIZE     (2048)

/*
*-------------------------------------------------------------------------------
*                           USB Request Blocks Number
*-------------------------------------------------------------------------------
*/
#define USBEH_MAX_URB_NUM           (8)

/*
*-------------------------------------------------------------------------------
*                            Select Host Controller
*-------------------------------------------------------------------------------
*/
#define USBEH_HCD_MENTOR            (1)
#define USBEH_CONTROLLER            (USBEH_HCD_MENTOR)

/*
*-------------------------------------------------------------------------------
*                            Supported Class Driver
*-------------------------------------------------------------------------------
*/
#define USBEH_CLASS_UVC_EN          (1)
#define USBEH_CLASS_DRV_NUM         (USBEH_CLASS_UVC_EN/* + xx_EN + ... */)

/*
*-------------------------------------------------------------------------------
*                                     Misc
*-------------------------------------------------------------------------------
*/
#define USBEH_CHK_ARG_EN            (1)

#define USBEH_DBG_LEVEL_OFF         (0)
#define USBEH_DBG_LEVEL_ERR         (1)
#define USBEH_DBG_LEVEL_WARN        (2)
#define USBEH_DBG_LEVEL_INFO        (3)
#define USBEH_DBG_LEVEL_DBG         (4)
#define USBEH_DBG_LEVEL             (USBEH_DBG_LEVEL_INFO)
#define USBEH_PRINTF                USBEH_BSP_Printf

#if (USBEH_DBG_LEVEL >= USBEH_DBG_LEVEL_ERR)
    #define USBEH_ERR(...)          do {USBEH_PRINTF("UEH_Err: ");\
                                        USBEH_PRINTF(__VA_ARGS__);\
                                    } while(0)
#else
    #define USBEH_ERR(...)
#endif
#if (USBEH_DBG_LEVEL >= USBEH_DBG_LEVEL_WARN)
    #define USBEH_WARN(...)         do {USBEH_PRINTF("UEH_Warn:");\
                                        USBEH_PRINTF(__VA_ARGS__);\
                                    } while(0)
#else
    #define USBEH_WARN(...)
#endif
#if (USBEH_DBG_LEVEL >= USBEH_DBG_LEVEL_INFO)
    #define USBEH_INFO(...)         do {USBEH_PRINTF("UEH_Info:");\
                                        USBEH_PRINTF(__VA_ARGS__);\
                                    } while(0)
#else
    #define USBEH_INFO(...)
#endif
#if (USBEH_DBG_LEVEL >= USBEH_DBG_LEVEL_DBG)
    #define USBEH_DBG(...)          do {USBEH_PRINTF("UEH_Dbg: ");\
                                        USBEH_PRINTF(__VA_ARGS__);\
                                    } while(0)
#else
    #define USBEH_DBG(...)
#endif

#endif //_USBEH_CFG_H_