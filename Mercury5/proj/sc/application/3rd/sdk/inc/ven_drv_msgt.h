/**
 *
 * @file    ven_drv_msgt.h
 * @brief   This file defines the structures for the user extend message
 * @author  Christine.tai
 * @version $Id: ven_drv_msgt.h 25432 2009-03-11 12:47:57Z steve.lee $
 *
 */

#ifndef __VEN_DRV_MSGT_H__
#define __VEN_DRV_MSGT_H__

#include "ven_drv.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_DRV_ACS_IND                                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : DRV to Vender                                               */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_drv_acs_ind_msg_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
    iVen_App_ID          VenAppId;
    ven_DrvAcsType_t     type;
    ven_DrvAcsStatus_t   status;
} iVen_drv_acs_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_DRV_USB_IND                                       */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor to MMI                                               */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_drv_usb_ind_msg_t                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
	iVen_App_ID          VenAppId;
	ven_DrvUsbType_t     type;
	ven_DrvUsbStatus_t   status;
} iVen_drv_usb_ind_t;

/****************************************************************************/
/*  Message :       I_VEN_DRV_BACKLIGHT_IND                                 */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor to MMI                                               */
/*                                                                          */
/*  Scope     :                                                             */
/*                                                                          */
/*  Structure : iVen_drv_backlight_ind_t                                    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/

typedef struct
{
	iVen_App_ID          VenAppId;
    ven_DrvBacklightCbType_t CbType;
	ven_DrvBacklightStatus_t   status;
} iVen_drv_backlight_ind_t;

typedef struct
{
   iVen_App_ID          VenAppId;
   u32     userData;
   u32     semID;
}iVen_drv_UsbInfo_t;
#endif /*__VEN_DRV_MSGT_H__ */

