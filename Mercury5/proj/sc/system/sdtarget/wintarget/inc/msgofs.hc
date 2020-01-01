/****************************************************************************/
/*  File    : msgofs.hc                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : GSM project message offset definition                         */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 01.12.97 |   ADA  |      |  Add DUMP_OFFSET definition.                  */
/*----------+--------+------+-----------------------------------------------*/
/* 26.08.97 |   RDO  |      |  Add V24_BASE definition                      */
/*----------+--------+------+-----------------------------------------------*/
/* 19.08.97 |   RDO  |      |  Add DAT_BASE definition                      */
/*----------+--------+------+-----------------------------------------------*/
/* 04.07.95 |   YFE  |      |  Change SS_BASE for codec consistency         */
/*----------+--------+------+-----------------------------------------------*/
/* 10.01.95 |   YFE  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/
/* 18.03.98 |   EWA  |      |  Adding RTK_BASE for semaphore with delay     */
/*----------+--------+------+-----------------------------------------------*/
/* 23.02.99 |   NHI  |      |  Add MMT_BASE definition                      */
/* 23.02.99 |   FRK  |      |  Add two IRDA bases (IRLAP, IRLMP)            */
/*----------+--------+------+-----------------------------------------------*/
/* 05.10.99 |   PBA  |      |  Add XMOD_BASE and DWL_BASE definition        */
/*----------+--------+------+-----------------------------------------------*/
/* 29.05.00 |   RDO  |      |  Put in hook to extend definitions for GPRS   */
/*----------+--------+------+-----------------------------------------------*/
/* 10.08.00 |   PBA  |      |  Add CUS_BASE and CON_BASE                    */
/*----------+--------+------+-----------------------------------------------*/
/* 27.10.00 |   FRK  |      |  Add IP and MMK    BASE                       */
/*----------+--------+------+-----------------------------------------------*/
/* 09.04.01 |   RDO  |      |  Add SYS_BASE for united flow control FCM     */
/*----------+--------+------+-----------------------------------------------*/
/* 11.04.01 |   RDO  |      |  Add bases for GPRS msg and RR sub-bases      */
/****************************************************************************/

#ifndef __MSGOFS_HC__
#define __MSGOFS_HC__


#include "stdcomp.h"


/*
** =========================================================================
**     MESSAGE OFFSET DEFINITIONS
**
**     +--------+--------+
**     |                 |
**     +--------+--------+
**        ^        ^
**        |        +-------- Msg sub ID (0 .. 255)
**        +----------------- Module ID  (service provider)
** =========================================================================
*/


#define LCD_BASE        (u16) (0x2000)
#define KBD_BASE        (u16) (0x2100)
#define SYS_BASE        (u16) (0x2200) /* New Base for SYS FCM */
#define SIM_BASE        (u16) (0x2F00)
#define MMI_BASE        (u16) (0x2C00)
#define SMS_BASE        (u16) (0x2D00)
#define SS_BASE         (u16) (0x2800)
#define CC_BASE         (u16) (0x2A00)
#define MM_BASE         (u16) (0x2900)
#define RR_BASE         (u16) (0x2700)
#define DL_BASE         (u16) (0x3000)
#define L1C_BASE        (u16) (0x3100)   /* for L1C-Prot communication   */
#define INTERN_L1C_BASE (u16) (0x0600)   /* for L1C intern communication */
#define HWL_BASE        (u16) (0x3300)
#define AT_BASE         (u16) (0x3200)
#define DAT_BASE        (u16) (0x3400)
#define V24_BASE        (u16) (0x3500)
#define IRLAP_BASE      (u16) (0x3600)
#define IRLMP_BASE      (u16) (0x3700)
#define MMT_BASE        (u16) (0x3800)	 /* internal MMT/MMI messages     */
#define DUMP_BASE       (u16) (0xE000)
#define RTK_BASE        (u16) (0x4000)  /* for RTK internal communication */
#define XMOD_BASE       (u16) (0x4100)
#define DWL_BASE        (u16) (0x4200)
#define CON_BASE        (u16) (0x4300)
#define CUS_BASE        (u16) (0x4400)
#define MMK_BASE        (u16) (0x4500)
#define IP_BASE         (u16) (0x3900)

#ifdef __GPRS__
#define GMM_BASE        (u16) (0x5000)
#define SM_BASE         (u16) (0x5100)
#define LLC_BASE        (u16) (0x5200)
#define SNDCP_BASE      (u16) (0x5300)
#define RLU_BASE        (u16) (0x5400)
#define RLD_BASE        (u16) (0x5500)
#define PPS_BASE        (u16) (0x5600)
#endif

////////////////// RR stuff ////////////////////////////////////////////////

/*
** =========================================================================
**     MSG SUB ID Definition for RR (use in ph_prim.hc and rr_prim.hc)
**
**     +-+-+-+-+-+-+-+-+
**     |D| MOD | MsgID |
**     +-+-+-+-+-+-+-+-+
**      ^   ^      ^
**      |   |      +------- Message Identity (0 .. 15)
**      |   +-------------- SUB_BASE of RR Module which sends or receives
**      |                    this message
**      +------------------ Direction (message "from RR" or "to RR")
** =========================================================================
*/
/*
** Direction
*/
#define FROM_EL            (u16) (0x0000)
#define TO_EL              (u16) (0x0080)

/*
** RR Modules
*/
#define RRX_SUB_BASE_MASK  (u16) (0x0070)
#define NO_RR_SUB_BASE     (u16) (0x0000)
#define RRM_SUB_BASE       (u16) (0x0010)
#define RRS_SUB_BASE       (u16) (0x0020)
#define RRD_SUB_BASE       (u16) (0x0030)
#define RRT_SUB_BASE       (u16) (0x0040)
#define RRP_SUB_BASE       (u16) (0x0050)
#define RRC_SUB_BASE       (u16) (0x0060)

#endif /* __MSGOFS_HC__ */


