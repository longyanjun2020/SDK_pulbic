/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                             BOARD SUPPORT PACKAGE
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_bsp.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_BSP_H_
#define _USBEH_BSP_H_

#include "usbeh_cfg.h"

/*
*-------------------------------------------------------------------------------
*                                 ISR Prototype
*-------------------------------------------------------------------------------
*/
typedef void (*USBEH_ISR)(void);

/*
*-------------------------------------------------------------------------------
*                        USB Embedded Host Stack Version
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_RELEASE_VER {
    UCHAR   major;
    UCHAR   minor;
    UCHAR   build;
} USBEH_RELEASE_VER;

/*
*-------------------------------------------------------------------------------
*                        USB Embedded Host BSP Functions
*-------------------------------------------------------------------------------
*/
extern void USBEH_BSP_Init(void);
extern void USBEH_BSP_DrvVBus(BOOL drvOn);
extern void USBEH_BSP_RegISR(USBEH_ISR isr);
extern void USBEH_BSP_UnRegISR(void);
extern void USBEH_BSP_Printf(CHAR *fmt, ...);

#endif //_USBEH_BSP_H_