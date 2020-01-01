/**
 *
 * @file    fmr_prim.hc
 *
 * @brief   This module definies the message/primitive index of FM radio task
 *
 * @author  Roger Lai
 * @version $Id
 *
 */

#ifndef __FMR_PRIM_HC__
#define __FMR_PRIM_HC__
#if 0
#ifdef __ONCHIP_FMRX_ENABLE__
//#include "ema_prim.hc"
#else
#include "cus_msg.hc"
#endif


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "fmr_message_define__.hi"
};
#endif
#endif /* __FMR_PRIM_HC__ */

