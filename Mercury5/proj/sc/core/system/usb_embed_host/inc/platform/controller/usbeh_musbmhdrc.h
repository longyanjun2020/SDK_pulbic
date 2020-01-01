/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                       MENTOR DUAL ROLE CONTROLLER DRIVER
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_musbmhdrc.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_MUSBMHDRC_H_
#define _USBEH_MUSBMHDRC_H_

#include "usbeh_core.h"

/*
*-------------------------------------------------------------------------------
*                            Contoller Workaround
*-------------------------------------------------------------------------------
*/
#define USBEH_CNTL_RX_DMA_WA    (0)

/*
*-------------------------------------------------------------------------------
*                            Contoller Characteristics
*-------------------------------------------------------------------------------
*/
#define USBEH_CNTL_MAX_EP       (8)     /* including EP0 */
#define USBEH_CNTL_EP0_TIMEOUT  (2500)  /* EP0 transfer timeout in ms unit */
#define USBEH_CNTL_EP_TIMEOUT   (2000)  /* EP, not EP0, transfer timeout   */

/*
*-------------------------------------------------------------------------------
*                           Control Trasfer Error Codes
*-------------------------------------------------------------------------------
*/
#define USBEH_CNTL_ERR_EP_STALL     (-1)
#define USBEH_CNTL_ERR_EP_ERROR     (-2)
#define USBEH_CNTL_ERR_EP_NAK_LIMIT (-3)

/*
*-------------------------------------------------------------------------------
*                              Control Trasfer State
*-------------------------------------------------------------------------------
*/
typedef enum _USBEH_CTL_XFER_STATE {
    CTL_XFER_SETUP_STATE = 0,
    CTL_XFER_DATA_STATE,
    CTL_XFER_STATUS_STATE
} USBEH_CTL_XFER_STATE;

/*
*-------------------------------------------------------------------------------
*                       USB Embedded Host Controller Handler
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_CNTL_HANDLE {
    USBEH_EP_CFG            ep_cfg[USBEH_CNTL_MAX_EP];
    BOOL                    ep_opened[USBEH_CNTL_MAX_EP];
    BOOL                    ep_halt[USBEH_CNTL_MAX_EP];
    OS_SEM                  ep_sem[USBEH_CNTL_MAX_EP];
    INT                     ep0_err;
    USBEH_CTL_XFER_STATE    ep0_state;
    UCHAR                   dma_ep;
} USBEH_CNTL_HANDLE;

#endif //_USBEH_MUSBMHDRC_H_