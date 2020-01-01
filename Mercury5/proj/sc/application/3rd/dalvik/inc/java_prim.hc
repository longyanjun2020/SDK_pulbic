/****************************************************************************/
/*  File    : java_prim.hc                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : java Application primitives id definition                */
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

#ifndef __JAVA_PRIM_HC__
#define __JAVA_PRIM_HC__



#include "cus_msg.hc"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif

typedef enum
{
#include "java_message_define__.hi"
}
Java_MsgDef_t;


#endif

