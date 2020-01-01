/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright MStar S.A. (c) 2007
*/

/****************************************************************************/
/*  File    : vm_msgofs.hc                                                  */
/*--------------------------------------------------------------------------*/
/*  Description:  OPEN-MMI Message offset                                   */
/*                                                                          */
/*                                                                          */
/*  History :                                                               */
/*--------------------------------------------------------------------------*/
/*   Date   | Author     | Err  |  Modification                             */
/*----------+------------+------+-------------------------------------------*/
/****************************************************************************/

#ifndef __VM_MSGOF_HC__
#define __VM_MSGOF_HC__


#include "vm_types.ht"

/****************************************************************************/
/*      VM offset definition                                                */
/****************************************************************************/
/****************************************************************************/
/*
** =========================================================================
**     VM MESSAGE OFFSET DEFINITIONS
**
**     +--------+--------+
**     |                 |
**     +--------+--------+
**        ^        ^
**        |        +-------- Msg ID (0  .. 255)
**        +----------------- Base   (256.. 65535)
** =========================================================================
*/
/*** Base defined for message   VM <-> CUS ***/
#define VM_SIM_BASE         (u16) (0x2000)
#define VM_SMS_BASE         (u16) (0x2100)
#define VM_SS_BASE          (u16) (0x2200)
#define VM_CC_BASE          (u16) (0x2300)
#define VM_MM_BASE          (u16) (0x2400)
#define VM_RR_BASE          (u16) (0x2500)
#define VM_RTC_BASE         (u16) (0x2600)
#define VM_GPIO_BASE        (u16) (0x2700)
#define VM_BUS_BASE         (u16) (0x2800)
#define VM_BAT_BASE         (u16) (0x2900)
#define VM_DBG_BASE         (u16) (0x2A00)
#define VM_IR_BASE          (u16) (0x2B00)
#define VM_KBD_BASE         (u16) (0x2C00)
#define VM_DAT_BASE         (u16) (0x2D00)
#define VM_OS_TIMER_BASE    (u16) (0x2E00)
#define VM_SYS_BASE         (u16) (0x2F00)
#define VM_IP_BASE          (u16) (0x3000)
#define VM_HWL_BASE         (u16) (0x3100)
#define VM_V24_BASE         (u16) (0x3200)
#define VM_USB_BASE         (u16) (0x3300)
#define VM_OBX_BASE         (u16) (0x3400)
#define VM_FCM_BASE         (u16) (0x3500)
#define VM_SYS_RTK_BASE     (u16) (0x3600)
#define VM_WBT_BASE         (u16) (0x3700)
#define VM_MDL_BASE         (u16) (0x3800)
#define CUS_MMT_BASE        VM_MDL_BASE          //0x3800
#define VM_ATI_BASE         VM_MDL_BASE + (u16) (0x0200) //0x3A00
#define API_ATI_BASE        VM_MDL_BASE + (u16) (0x0400) //0x3C00

/*** Base defined for message   CUS <-> CUS ***/
#define VM_CUS_BASE         (u16) (0x4000)
#define VM_CUS1_BASE        (u16) (VM_CUS_BASE+0x0000)
#define VM_CUS2_BASE        (u16) (VM_CUS_BASE+0x0300)
#define VM_CUS3_BASE        (u16) (VM_CUS_BASE+0x0600)
#define VM_CUS4_BASE        (u16) (VM_CUS_BASE+0x0900)
#define VM_CUS5_BASE        (u16) (VM_CUS_BASE+0x0B00)
#define VM_CUS6_BASE        (u16) (VM_CUS_BASE+0x0D00)
#define VM_CUS7_BASE        (u16) (VM_CUS_BASE+0x0F00)
#define VM_CUS8_BASE        (u16) (VM_CUS_BASE+0x1100)
#define VM_CUS9_BASE        (u16) (VM_CUS_BASE+0x1300)
#define VM_CUS10_BASE       (u16) (VM_CUS_BASE+0x1500)
/*** GPRS Base defined for message   WM <-> CUS ***/
#define VM_SM_BASE         (u16) (0x5D00)
#define VM_SNDCP_BASE      (u16) (0x5E00)
#define VM_PPS_BASE        (u16) (0x5F00)
#define VM_LAST_BASE        (u16) (0x5FFF) /* Warning: Customer base cannot exceed VM_LAST_BASE value */

#ifdef __MSTAR_DUAL_SIM__
#ifdef __DUPLICATE_TASK__
#define VM_MDL_TIMER_BASE   (u16) (0xB100)
#define VM_ATI_TIMER_BASE   (u16) (0xB200) 
#else
#define VM_MDL_TIMER_BASE   VM_MDL_BASE
#define VM_ATI_TIMER_BASE   VM_ATI_BASE 
#endif
#endif


#define VM_UNSUBSCRIB_BASE  (u16) (0xFFFF)


#endif  /* __VM_MSGOF_HC__ */
