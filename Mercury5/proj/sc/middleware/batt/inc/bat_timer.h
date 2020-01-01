/**
 * \file bat_timer.h
 * Description:  Internal timers for state machine
*/

#ifndef __BAT_TIMER_H__
#define __BAT_TIMER_H__

#include "vm_msgof.hc"

/**
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "bar_timer_message_define__.hi"
};

#endif  /* __BAT_TIMER_H__ */

