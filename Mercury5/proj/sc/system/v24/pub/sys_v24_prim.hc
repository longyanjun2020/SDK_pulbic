/*                                                                          */
/*  Important : This software is protected by Copyright and the information */
/*              contained herein is confidential. Distribution, reproduction*/
/*              as well as exploitation and transmission of its contents is */
/*              not allowed except if expressly permitted. Infringments     */
/*              result in damage claims.                                    */
/*              Copyright Wavecom S.A. (c) 2004                             */
/*                                                                          */
/*                                                                          */

/****************************************************************************/
/* File     : v24_prim.hc                                                   */
/*--------------------------------------------------------------------------*/
/* Scope    : Definition of V24 primitive numbers                           */
/*                                                                          */
/* Content  :                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/* Date     | Author | Modification                                         */
/*----------+--------+------------------------------------------------------*/
/* 25/10/04 |  APH   | Ident                                                */
/****************************************************************************/
/*
$LogWavecom: U:\projet\gsm\pvcsarch\archives\v24\itf\v24_prim.hc-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 02.02.05 | mpr    | 1.1            | Resolution for 27548: New V24 archi
 *          |        |                | tecture (designed for CMUX and Blue
 *          |        |                | tooth)  .
 *----------+--------+----------------+-------------------------------------
 * 10.03.04 | mse    | 1.0            | Initial revision.  Resolution for 1
 *          |        |                | 9722: New V24
 *----------+--------+----------------+-------------------------------------
*/

#ifndef __SYS_V24_PRIM_HC__
#define __SYS_V24_PRIM_HC__

#include "msgofs.hc"  // Get V24_BASE


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Internal protocol V24 primitives
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif

enum
{
#include "sys_v24_message_define__.hi"
};
#endif  /*  __SYS_V24_PRIM_HC__  */

