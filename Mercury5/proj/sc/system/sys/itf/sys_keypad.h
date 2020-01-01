/****************************************************************************/
/*  File    : sys_keypad.h                                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   :  keypad handler                                         */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_KEYPAD_H__
#define __SYS_KEYPAD_H__

#include "kernel.h"
#include "vm_kbd.h"

#define MAX_HK_KEY_NUM  (3)

s32  sys_InitKeypadBuffer(u32 LowLimit, u32 UpLimit);
void sys_KeyProcessed(void);
void sys_KeypadIrqInit(void);
void sys_KeypadSubscribe(u8 mailbox);
void sys_KeypadPowerOnOffKey(bool pressed);
s32 sys_KeypadGetState(vm_kbdKey_t **pressed_keys);

#endif /* __SYS_KEYPAD_H__ */




