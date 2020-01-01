/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 1994, 1995, 1996
*/

/****************************************************************************/
/*  File    : osdefs.hc                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : GSM project global resources definition                       */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 10.01.95 |   YFE  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/
/* 11.06.96 |   PGU  |      |  Semaphore for RPC                            */
/*----------+--------+------+-----------------------------------------------*/
/* 13.06.96 |   CGU  |      |  Add DATA_MBX                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 22.08.96 |   PGU  |      |  Add E2P_SEM                                  */
/*----------+--------+------+-----------------------------------------------*/
/* 21.10.97 |   RDO  |      |  Add V24_SEM                                  */
/*----------+--------+------+-----------------------------------------------*/
/* 27.11.98 |   PGU  |      |  Add LCD_SEM                                  */
/*----------+--------+------+-----------------------------------------------*/
/* 03.09.99 |   FRK  |      |  Add IR_MBX                                   */
/*----------+--------+------+-----------------------------------------------*/
/* 30.05.00 |   RDO  |      |  Added hook for GPRS.                         */
/*----------+--------+------+-----------------------------------------------*/
/* 10.08.00 |   PBA  |      |  Added CUS and CON task and Mbox              */
/*----------+--------+------+-----------------------------------------------*/
/* 27.10.00 |   FRK  |      |  Add IP            task and Mbox              */
/*----------+--------+------+-----------------------------------------------*/
/* 15.11.00 |   JMH  |      |  Add OBJ_SEM semaphore                        */
/*----------+--------+------------------------------------------------------*/
/* 08.12.00 |RDO-DDO | - add new semaphore ATI_PWR_OFF_SEM to check v24     */
/*          |        |   state when at+cpof is received to avoid cancella   */
/*          |        |   tion of OK response (see ati_main.c for details)   */
/*----------+--------+------+-----------------------------------------------*/
/* 14.01.02 |  MTH   | WHAT2 adaptation : Add SPI_SEM                       */
/****************************************************************************/

#ifndef __OSDEFS_HC__
#define __OSDEFS_HC__

/*
** =========================================================================
**     MAILBOXES DEFINITION
** =========================================================================
*/

/* !!!!!!!!!!! DO NOT CHANGE ANYTHING STARTING FROM HERE !!!!!!!!!!!! */

#define HWL_MBX         0
#define MMI_MBX         1
#define LCD_MBX         2
#define SIM_MBX         3
#define CC_MBX          4
#define SS_MBX          5
#define SMS_MBX         6
#define MM_MBX          7
#define RR_MBX          8
#define LAPD_MBX        9
#define SPV_MBX         10
#define L1C_MBX         SPV_MBX
#define MSR_MBX         11
#define SIM_HAND_MBX    12
#define DATA_MBX        13
#define IR_MBX          14
#define IP_MBX          15
#define CON_MBX         16
#define CUS_MBX         17
#define __LAST_MBX      17  /* WARNING: must be updated if mailboxes are added */


/* !!!!!!!!!!!!!!!!!!! CHANGES ALLOWED FROM THERE !!!!!!!!!!!!!!!!!! */


/*
** =========================================================================
**     SEMAPHORES DEFINITION
** =========================================================================
*/

/* !!!!!!!!!!! DO NOT CHANGE ANYTHING STARTING FROM HERE !!!!!!!!!!!! */

#define SPV_SEM         0
#define E2P_SEM         1
#define I2C_SEM         2
#define V24_SEM         3
#define LCD_SEM         4
#define OBJ_SEM         5
#define ERASURE_SEM     6
#define ATI_PWR_OFF_SEM 7 

#define SPI_SEM         7
#define __LAST_SEM      7 /* WARNING: must be updated if semaphores are added */

#ifndef __TARGET__
#define RPC_FIRST_SEM   8
#define RPC_LAST_SEM    RPC_FIRST_SEM + 7
#else
#endif

/* !!!!!!!!!!!!!!!!!!! CHANGES ALLOWED FROM THERE !!!!!!!!!!!!!!!!!! */


/*
** =========================================================================
**     TASKS DEFINITION
** =========================================================================
*/

/* !!!!!!!!!!! DO NOT CHANGE ANYTHING STARTING FROM HERE !!!!!!!!!!!! */

/*                   !!!!!! BEWARE !!!!!!!!                            */
/* those tasks number *MUST* be the index in the init.c file (if used) */
/*                                                                     */

#define IDLE_TASK       0
#define SS_TASK         1
#define SMS_TASK        2
#define CC              3
#define SIM             4
#define MM              5
#define RR              6
#define DL              7
#define MSR             8
#define DAT             9
#define SPV            10
#define HWL            11
#define LCD            12
#define ATI            13
#define MMI            13
#define IRDA           14
#define IP             15
#define CON            16
#define CUS            17
#define __LAST_TASK    17 /* WARNING: must be updated if tasks are added */

/* !!!!!!!!!!!!!!!!!!! CHANGES ALLOWED FROM THERE !!!!!!!!!!!!!!!!!! */

#ifdef __GPRS__
#include "gosdefs.hc"
#endif


#endif /* __OSDEFS_HC__ */
