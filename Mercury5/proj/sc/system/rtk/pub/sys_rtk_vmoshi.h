/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright VMTS S.A. (c) 2001
*/

/****************************************************************************/
/*  File    : vm_os.hi                                                      */
/*--------------------------------------------------------------------------*/
/*  Description:  Define interface structure messages for OS layer          */
/*                                                                          */
/*                                                                          */
/*  History :                                                               */
/*--------------------------------------------------------------------------*/
/*   Date   | Author     | Err  |  Modification                             */
/*----------+------------+------+-------------------------------------------*/
/* 15/09/01 |  ach       |      |  Creation                                 */
/*----------+------------+------+-------------------------------------------*/
/*
 *$LogWavecom: G:\projet\gsm\pvcsarch\archives\rtk\itf_open\vm_os.hi-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 30.08.02 | ddo    | 1.0            | Initial revision.
 *----------+--------+----------------+-------------------------------------
*
* Add $log tag for comments
*/
/****************************************************************************/

#ifndef __SYS_RTK_VMOSHI_H__
#define __SYS_RTK_VMOSHI_H__

#include "vm_msgof.hc"
#include "vm_types.ht"


/* OS Message Types */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "sys_rtk_vmoshi_message_define__.hi"
};
/*****************************************/
/*      Timer Body Message               */
/*****************************************/

typedef struct
{
  u32        Ident;    /* Timer identifier */
} vm_osTimerMsgBody_t;


#endif  /* __SYS_RTK_VMOSHI_H__ */


