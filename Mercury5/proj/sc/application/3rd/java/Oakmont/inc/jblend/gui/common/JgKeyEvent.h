/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Key event definitions
 */

#ifndef ___GUI_COMMON_KEYEVENT_H
#define ___GUI_COMMON_KEYEVENT_H

#include <JkTypes.h>
#include <AMUiEvent.h>

#include <JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_KeyEvent
 * @{
 */

/**
 * @internal
 * The maximum key event value.
 */
#define JG_KEY_EVT_END          (AM_EVENT_KEY_CLICKED)

/**
 * The key event processing result.\ Focus kept.
 *
 * Return this value in the key event handler 
 * when it is necessary to suppress focus movement by JBlend. 
 *
 * This value should be used in the key event handler that 
 * processes #AM_EVENT_KEY_CLICKED or #AM_EVENT_KEY_REPEATED events
 * for the keys #AM_KEYCODE_UP, #AM_KEYCODE_DOWN, #AM_KEYCODE_RIGHT, or #AM_KEYCODE_LEFT.
 */
#define JG_KEY_RES_KEEP_FOCUS           0x00000001

/**
 * The key event processing result.\ Changed to Active state.
 *
 * This value can be used only when returning the result for 
 * key event processing in a state other than Active (#JG_COM_STATE_ACTIVE).
 * Moreover, this value cannot be used for the following keys.
 *   <ul>
 *     <li> #AM_KEYCODE_UP </li>
 *     <li> #AM_KEYCODE_LEFT </li>
 *     <li> #AM_KEYCODE_RIGHT </li>
 *     <li> #AM_KEYCODE_DOWN </li>
 *   </ul>
 */
#define JG_KEY_RES_SET_ACTIVE           0x00000002

/**
 * The structure type for representing key event information.
 */
typedef struct JGT_KeyEvent {
    /**
     * The handle of the component generating the event
     */
    JGCom component;
    
    /**
     * The type of the generated event.
     * 
     * One of the following values is set.
     * - #AM_EVENT_KEY_PRESSED 
     * - #AM_EVENT_KEY_RELEASED 
     * - #AM_EVENT_KEY_REPEATED 
     * - #AM_EVENT_KEY_CLICKED 
     * .
     * The value passed in the <i>type</i> parameter of #AmNotifyKeyEvent() 
     * by the native system is set.
     */
    JKUint32 type;
    
    /**
     * Key code
     * 
     * A constant whose name starts with AM_KEYCODE_, which is defined 
     * in @ref Device_Event_Notification_JBI "Device Event Notification JBI", 
     * or a constant added originally by the device manufacturer 
     * (a value greater than or equal to AM_KEYCODE_USER_BASE). 
     * The value passed in the <i>keyCode</i> parameter of #AmNotifyKeyEvent() 
     * by the native system is set.
     */
    JKUint32 keyCode;
    
    /**
     * The key label text
     * This member is reserved for future use.
     */
    JKWChar keyChar;
    
} JGT_KeyEvent;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_KEYEVENT_H */

