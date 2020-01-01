/*
*===============================================================================
*                                    USB-EH
*                          The USB Embedded Host Stack
*                               USB CLASS CONTROL
*
*              Copyright (c) 2014, Alpha Imaging Technology Corp.
*                             All Rights Reserved
*
* File    : usbeh_class.h
* Author  : Alterman
* Version : v1.0
*===============================================================================
*/

#ifndef _USBEH_CLASS_H_
#define _USBEH_CLASS_H_

#include "usbeh_core.h"

/*
*-------------------------------------------------------------------------------
*                         App Callbacks in Class Driver
*-------------------------------------------------------------------------------
*/
typedef INT (*App_Class_Callback)(void);

/*
*-------------------------------------------------------------------------------
*                           Class Driver Name Length
*-------------------------------------------------------------------------------
*/
#define CLASS_DRV_NAME_SIZE     (8)

/*
*-------------------------------------------------------------------------------
*                            Class Driver Structures
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_CLASS_DRV {
    UCHAR   name[CLASS_DRV_NAME_SIZE];  /* class driver name    */
    UCHAR   node;                       /* node num in drv list */
    BOOL    (*Class_ProbeDrv)(USBEH_STD_DEV_DESC *dev_desc,
                              USBEH_STD_CFG_DESC *cfg_desc);
} USBEH_CLASS_DRV;

/*
*-------------------------------------------------------------------------------
*                                 Class Handler
*-------------------------------------------------------------------------------
*/
typedef struct _USBEH_CLASS_HANDLE {
    UCHAR               drv_node;                       /* matched class drv  */
    USBEH_CLASS_DRV     *drv_list[USBEH_CLASS_DRV_NUM]; /* supported drv list */
    App_Class_Callback  conn_cb[USBEH_CLASS_DRV_NUM];   /* connected cb list  */
    App_Class_Callback  discon_cb[USBEH_CLASS_DRV_NUM]; /* disconnect cb list */
} USBEH_CLASS_HANDLE;

/*
*-------------------------------------------------------------------------------
*                      USB Embedded Host Class Functions
*-------------------------------------------------------------------------------
*/
extern void USBEH_Class_Init(void);
extern INT  USBEH_Class_UnRegDriver(UCHAR node);
extern INT  USBEH_Class_RegDriver(USBEH_CLASS_DRV *drv,
                                  App_Class_Callback conn_cb,
                                  App_Class_Callback discon_cb);
extern BOOL USBEH_Class_ProbeDriver(USBEH_STD_DEV_DESC *dev_desc,
                                    USBEH_STD_CFG_DESC *cfg_desc);
extern INT  USBEH_Class_Connect(void);
extern void USBEH_Class_Disconnect(void);

#endif //_USBEH_CLASS_H_