
/******************************************************************/
/*  File    : RTKDEFI.H                                           */
/*-------------------------------------------------------------   */
/*  Scope   :  Internal RTK definitions                           */
/*                                                                */
/*  Contents:                                                     */
/*                                                                */
/*  Changes    :                                                  */
/*--------------------------------------------------------------  */
/*  Date       | Author |      Err  |         Modification        */
/*-------------+--------+-----------+---------------------------  */
/* 14/11/1994  |  E.W.  |           |        Creation             */
/*-------------+--------+-----------+---------------------------  */
/******************************************************************/
/*
 * $LogWavecom: G:\projet\gsm\pvcsarch\archives\rtk\inc\rtkdefi.h-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  24.10.02 | ddo    | 3.2            | Add define of RTK_HEAP_LINK_SHIFT, 
 *           |        |                | RTK_HEAP_LINK_COUNTER,  RTK_HEAP_LI
 *           |        |                | NK_MSK                             
 * ----------+--------+----------------+-------------------------------------
 *  30.08.02 | ddo    | 3.0            | integration dev tf V19             
 * ----------+--------+----------------+-------------------------------------
 * 
 *    Rev 1.3   Mar 22 2002 16:05:52   rdo
 * HEAP 32 BITS: Add defines 
 * 
 *    Rev 1.2   Sep 04 2001 14:45:48   ddo
 * RTK_BASE already defined in msgofs.hc
*/

#ifndef __SYS_RTK_DEFI_H__
#define __SYS_RTK_DEFI_H__


/******* Task states *******/

#define RTK_NON_SIGNIFICANT             0
#define RTK_WAIT_SEMAPHOR               1
#define RTK_WAIT_MAIL_BOX               2
#define RTK_WAIT_FLAG_OBJ               3 
#ifdef __RTK_SEND_SUSPENSION__
#define RTK_WAIT_SEND_MAIL_BOX          4
#endif
#define RTK_READY                       5
#define RTK_ACTIVE                      6
#define RTK_SUSPENDED                   7
#define RTK_WAIT_MUTEX                  8
#define RTK_NON_OPERATIONAL             0x80

// this must be always verified : 
// if state is the state of a task 
// ( state & RTK_NON_OPERATIONAL ) >= RTK_READY
// implies that the task can be scheduled now
// ( not waiting for any external event )


/******* Object parameters *******/
    
#define RTK_OBJ_TASK                    183
#define RTK_OBJ_QUEUE                   184
#define RTK_FREE_ENVELOP                190

/******* MAX parameters *******/

#define RTK_MIN_SEM_VALUE               -255
#define RTK_MAX_REGION_COUNT            255    /* NB interrupt pending */

/****** Other Parametres *******/

#define RTK_NULL_POINTER                0L      
#define RTK_NONSIGNIFICANT_OBJECT       195


/******* Version Number *********************/

#define  RTK_VERSION_EDITION            0x0119

/******** MSDOS INTERUPT VECTOR ************/

#define RTK_TIMER_INTERRUPT_VALUE       0x1C

/******** HEAP ALLOCATED BYTE ************/
#define RTK_HEAP_SIZE_UNIT		4 /* 1<<4 bytes */
#define RTK_HEAP_FOOTER_SIZE	8 /* in byes */
#define RTK_HEAP_SIZE_IN_WORD(s)	(((s)<<RTK_HEAP_SIZE_UNIT)>>2)
#define RTK_HEAP_ORIG_SIZE(s)	(((s)<<RTK_HEAP_SIZE_UNIT)-RTK_HEAP_FOOTER_SIZE)

#define RTK_HEAP_ALLOCATED	             0x1 /* DO NOT CHANGE THIS VALUE */
#define RTK_HEAP_ID_SHIFT               24  /* DO NOT CHANGE THIS VALUE */
#define RTK_HEAP_ID_MSK			          ((u32)0xFF << RTK_HEAP_ID_SHIFT)

#define RTK_HEAP_LINK_SHIFT           21
#define RTK_HEAP_LINK_COUNTER         ((u32)0x01 << RTK_HEAP_LINK_SHIFT)
#define RTK_HEAP_LINK_MSK             ((u32)0x07 << RTK_HEAP_LINK_SHIFT)

#ifndef __RTK_DIAGNOSE_ENHANCE__
/************** DEBUG ********************/
#define MAX_SAVED_MESSAGE 64
#define MAX_SAVED_SHRINKMSG 10
#endif
#endif          /* __SYS_RTK_DEFI_H__ */


