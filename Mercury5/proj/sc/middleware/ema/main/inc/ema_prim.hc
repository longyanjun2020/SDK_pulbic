/**
 *
 * @file    ema_prim.hc
 *
 * @brief   This module definies the message/primitive index of EMA (Enhanced Media Agent) task
 *
 * @author  Pauli Leong
 * @version $Id: ema_prim.hc 14384 2008-09-24 16:07:44Z xavier.fan $
 *
 */
#ifndef __EMA_PRIM_HC__
#define __EMA_PRIM_HC__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_msgof.hc"




/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/**
 *  @brief Primitive/Message ID Base Mask definition
 */
#define   EMA_MASK_BASE         (u16)(0xFFC0)
#define   EMA_MASK_SUB_BASE     (u16)(0xFFF0)


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "ema_message_define__.hi"
};


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_PRIM_HC__ */

