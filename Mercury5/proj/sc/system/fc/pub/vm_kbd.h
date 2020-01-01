/****************************************************************************/
/*  File    : vm_kbd.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Description:  Keyboard handler interface header file                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


#ifndef __VM_KBD_H__
#define __VM_KBD_H__


#include "vm_types.ht"
#include "vm_msgof.hc"


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum vm_kbd_Prim
{
#include "vm_kbd_message_define__.hi"
};



/*
** ---------------------------------------------------------------
**    Primitive structure between KBD driver and MMI
** ---------------------------------------------------------------
*/

typedef struct vm_kbdInd
{
   u8      KeyMode;
   u8      Row[2];
   u8      Col[2];
   u8      NbRow;
   u8      NbCol;
} vm_kbdInd_t;

typedef struct
{
   u8      Row;
   u8      Col;
} vm_kbdKey_t;


/*
** ---------------------------------------------------------------
**    Possible values for the field 'KeyMode'
** ---------------------------------------------------------------
*/

#define KEY_PRESSED             (u8) 1
#define KEY_RELEASED            (u8) 2
#define KEY_PRESSED_ON_OFF       	(u8) 3
#define KEY_RELEASED_ON_OFF		(u8) 4

#ifdef __HOTKEY_TRACE_DUMP__
#define KEY_NONE                (u8) 0xFF
#else
#define KEY_HOT_KEY_AUDIO_TRACE_ON   (u8)0xFD
#define KEY_HOT_KEY_AUDIO_TRACE_OFF  (u8)0xFE
#endif  /* __HOTKEY_TRACE_DUMP__ */

#endif  /* __VM_KBD_H__ */

