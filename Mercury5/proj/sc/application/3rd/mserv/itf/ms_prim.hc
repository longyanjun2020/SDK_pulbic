/****************************************************************************/
/*  File    : ms_prim.hc                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : MServices Application primitives id definition                */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 */

#ifndef __MS_PRIM_HC__
#define __MS_PRIM_HC__

#ifdef __MSERVICES__

#include "cus_msg.hc"
#include "ms_primitem.h"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
#define CUS_MSERV_BASE       (u16) (VM_CUS7_BASE + 0x0000)  /* (u16) (0x3F00) */
typedef enum
{
#include "ms_message_define__.hi"

#define MAKE_PRIM_ITEM(_Name, _Parser)  _Name
    MS_IN_PRIM_SRV_ITEMS    /* for requests */
    MS_OUT_PRIM_SRV_ITEMS   /* for responses */
#undef MAKE_PRIM_ITEM
    I_MSERV_SOCKET_LAST,

    CUS_MSERV_BASE_END,     //always keep this at bottom
}Mserv_MsgDef_t;

#endif
#endif /* __MS_PRIM_HC__ */


