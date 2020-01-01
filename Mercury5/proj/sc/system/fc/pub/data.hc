/****************************************************************************/
/*  File    : DATA.HC                                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Definition constants used in the DATA task.                   */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Changes    :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 12/06/96 | RDO CGU|      |  creation                                     */
/* 10/09/96 | RDO    |      |  deletion of unused types                     */
/* 04/05/99 | JSU    |      |  add 14400 speed                              */
/****************************************************************************/
/*
$LogWavecom: G:\projet\gsm\pvcsarch\archives\fc\itf\data.hc-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  02.10.02 | ddo    | 3.0            | integration dev tf V19             
 * ----------+--------+----------------+-------------------------------------
*/

#ifndef __DATA_HC__
#define __DATA_HC__

#include "stdcomp.h"     /* Portability purpose standards definition */


/* definition of process identifiers */
/*************************************/
#define PROCESS_DATA   DATA_MBX

/* Constants used for the bitmap "Order" */
/*****************************************/
#define DATA_ORDER_ENCODE        0x1
#define DATA_ORDER_DECODE        0x2
#define DATA_ORDER_ERROR_DECODE  0x4

/* Constants giving the number of data bytes according to the rate used */
/************************************************************************/
#define DATA_NB_BYTES_2400        9
#define DATA_NB_BYTES_4800       15
#define DATA_NB_BYTES_9600       30
#define DATA_NB_BYTES_14400      38
#define DATA_MAX_FRAME_LENGTH    DATA_NB_BYTES_14400

#endif
