/*
 * Copyright 2002-2005 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_PLATFORM_HEADER
#define KJAVA_PLATFORM_HEADER

/**
 *  @file ajsc_platform.h
 *  @if JAPANESE
 *  Event Process ACI
 *  @else
 *  Event Process ACI
 *  @endif
 */

#ifdef __cplusplus
extern "C"{
#endif

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/
#include <kjava_action.h>

/** 
 * @addtogroup Native_Event_Notification_ACI
 *
 * @par Include file 
 * \#include ajsc_platform.h
 * @{
 */
 
/** 
 * Key pressed. 
 * When this event is passed to JBlendia, then if an object of the 
 * <code>javax.microedition.lcdui.Canvas</code> class or its subclass is set as
 * the current <code>Displayable</code>, the <code>keyReleased</code> method is called.
 */
#define AJSC_EVENT_KEY_PRESSED        0

/** 
 * Key released. 
 * When this event is passed to JBlendia, an operation is performed as follows
 * with respect to the object set as current <code>Displayable</code>. 
 * - If the object belongs to the <code>javax.microedition.lcdui.Canvas</code> class or its subclass,
 *   the <code>keyRepeated</code> method is called.
 * - If the object belongs to the <code>javax.microedition.lcdui.Form</code> class or its 
 *   subclass, scrolling of the screen and/or the actions of GUI components on the screen 
 *   are executed.
 * .
 */
#define AJSC_EVENT_KEY_RELEASED       1

/** 
 * Key repeated.
 * When this event is passed to JBlendia, an operation takes place as follows.
 * - If an object belonging to the <code>javax.microedition.lcdui.Form</code> class or its subclass 
 *   is set as the current <code>Displayable</code>, scrolling of the screen and/or the actions of 
 *   GUI components on the screen are executed.
 * - If this event is passed as an event for a soft key, JBlendia calls the
 *   <code>commandAction</code> method of the <code>javax.microedition.lcdui.CommandListener</code>
 *   interface implemented in the object set as current <code>Displayable</code> by the Java
 *   application.
 * .
 */
#define AJSC_EVENT_KEY_REPEATED       2

/**
 * Key action occurred.
 * When this event is passed to JBlendia, an operation takes place as follows.
 * - If an object belonging to the <code>javax.microedition.lcdui.Form</code> class or its subclass 
 *   is set as the current <code>Displayable</code>, scrolling of the screen and/or the actions of 
 *   GUI components on the screen are executed.
 * - If this event is passed as an event for a soft key, JBlendia calls the
 *   <code>commandAction</code> method of the <code>javax.microedition.lcdui.CommandListener</code>
 *   interface implemented in the object set as current <code>Displayable</code> by the Java
 *   application.
 * .
 */
#define AJSC_EVENT_KEY_CLICKED        3

/** The 0 key. */
#define AJSC_KEYCODE_NUM0             0
/** The 1 key. */
#define AJSC_KEYCODE_NUM1             0x01
/** The 2 key. */
#define AJSC_KEYCODE_NUM2             0x02
/** The 3 key. */
#define AJSC_KEYCODE_NUM3             0x03
/** The 4 key. */
#define AJSC_KEYCODE_NUM4             0x04
/** The 5 key. */
#define AJSC_KEYCODE_NUM5             0x05
/** The 6 key. */
#define AJSC_KEYCODE_NUM6             0x06
/** The 7 key. */
#define AJSC_KEYCODE_NUM7             0x07
/** The 8 key. */
#define AJSC_KEYCODE_NUM8             0x08
/** The 9 key. */
#define AJSC_KEYCODE_NUM9             0x09
/** The * key. */
#define AJSC_KEYCODE_ASTERISK         0x0a
/** The # key. */
#define AJSC_KEYCODE_POUND            0x0b
/** The left key. */
#define AJSC_KEYCODE_LEFT             0x10
/** The up key. */
#define AJSC_KEYCODE_UP               0x11
/** The right key. */
#define AJSC_KEYCODE_RIGHT            0x12
/** The down key. */
#define AJSC_KEYCODE_DOWN             0x13
/** The select key. */
#define AJSC_KEYCODE_SELECT           0x14
/** The soft key 1. */
#define AJSC_KEYCODE_SOFT1            0x15
/** The soft key 2. */
#define AJSC_KEYCODE_SOFT2            0x16
/** The soft key 3. */
#define AJSC_KEYCODE_SOFT3            0x17
/** The send key. */
#define AJSC_KEYCODE_SEND             0x19
/** The power key. */
#define AJSC_KEYCODE_POWER            0x20
/** The clear key. */
#define AJSC_KEYCODE_CLEAR            0x1A
/** The SideKey UP. */
#define AJSC_KEYCODE_SD_UP            0x1B
/** The SideKey DOWN. */
#define AJSC_KEYCODE_SD_DN            0x1C
/** Pointer button pressed. */
#define AJSC_EVENT_POINTER_PRESSED    0
/** Pointer button released. */
#define AJSC_EVENT_POINTER_RELEASED   0x01
/** Pointer button clicked. */
#define AJSC_EVENT_POINTER_CLICKED    0x02
/** Pointer button moved (absolute coordinate).*/
#define AJSC_EVENT_POINTER_MOVED      0x03
/** Pointer button moved (relative coordinate).*/
#define AJSC_EVENT_POINTER_DELTA      0x04

/** @} */

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/** 
 * @addtogroup Thread_Control_ACI
 *
 * @par Include file 
 * \#include ajsc_platform.h
 * @{
 */
/**
 * Initializes JBlendia for KVE thread.
 *
 * Call this function in the context of the KVE thread
 * to indicate that the KVE thread is created and
 * begin to process requests.
 */
void ajsc_kve_initialize(void);

/**
 *        Processes an action command received in the KVE thread.
 * @param action_p
 *        A pointer to the structure holding the incoming action command.
 * @retval 0
 *         The function has processed the action normally.
 * @retval 1
 *         The function failed.
 *
 * Call this function in the KVE thread to pass the received action command to AJSC.
 *
 * Even if this function fails, discard the received action command.
 * Retry is not necessary,
 *
 * This function may perform a time-consuming processing depending on the
 * action command. For instance, when launching a MIDlet is requested by
 * the action command, the JVM is executed in this function and the function
 * does not return until the JVM terminates. 
 *
 */
int ajsc_kve_processAction(KJavaActionCommand *action_p);

/** @} */

/** @ingroup Native_Event_Notification_ACI  */
/**
 *        Notifies the Java execution environment of a key event.
 * @param type
 *        The key event type. Designate one of the following:
 *        - #AJSC_EVENT_KEY_PRESSED
 *        - #AJSC_EVENT_KEY_RELEASED
 *        - #AJSC_EVENT_KEY_REPEATED
 *        .
 * @param keyCode
 *        The key code. Designate one of the following:
 *        - #AJSC_KEYCODE_NUM0
 *        - #AJSC_KEYCODE_NUM1
 *        - #AJSC_KEYCODE_NUM2
 *        - #AJSC_KEYCODE_NUM3
 *        - #AJSC_KEYCODE_NUM4
 *        - #AJSC_KEYCODE_NUM5
 *        - #AJSC_KEYCODE_NUM6
 *        - #AJSC_KEYCODE_NUM7
 *        - #AJSC_KEYCODE_NUM8
 *        - #AJSC_KEYCODE_NUM9
 *        - #AJSC_KEYCODE_ASTERISK
 *        - #AJSC_KEYCODE_POUND
 *        - #AJSC_KEYCODE_LEFT
 *        - #AJSC_KEYCODE_UP
 *        - #AJSC_KEYCODE_RIGHT
 *        - #AJSC_KEYCODE_DOWN
 *        - #AJSC_KEYCODE_SELECT
 *        - #AJSC_KEYCODE_SOFT1
 *        - #AJSC_KEYCODE_SOFT2
 *        - #AJSC_KEYCODE_SOFT3
 *        - #AJSC_KEYCODE_SEND
 *        .
 * @param keyChar
 *        Always set to 0 (zero). 
 *        (This parameter is reserved for future use.)
 * @retval 1
 *         The function succeeded. The event was added into the queue.
 * @retval "Not 1"
 *         The function failed.
 *         The event could not be added into the queue or
 *         could not be processed by the function now.
 *
 * Even if this function fails, discard the event.
 * Retry is not necessary,
 */
int ajsc_keyEventHandler(int type, int keyCode, short keyChar);


/** @ingroup Native_Event_Notification_ACI  */
/**
 *        Notifies Java execution environment of an pointer event.
 * @param type
 *        The pointer event type. Designate one of the following:
 *        - #AJSC_EVENT_POINTER_PRESSED
 *        - #AJSC_EVENT_POINTER_RELEASED
 *        - #AJSC_EVENT_POINTER_CLICKED
 *        - #AJSC_EVENT_POINTER_MOVED
 *        - #AJSC_EVENT_POINTER_DELTA
 *        .
 * @param buttonNo
 *        The button number.
 * @param x
 *        The x coordinate of the point where the event was generated.
 * @param y
 *        The y coordinate of the point where the event was generated.
 * @retval 1
 *         The function succeeded. The event was added into the queue.
 * @retval "Not 1"
 *         The function failed.
 *         The event could not be added into the queue or
 *         could not be processed by the function now.
 *
 * Even if this function fails, discard the event.
 * Retry is not necessary,
 */
int ajsc_pointEventHandler(int type, int buttonNo, int x, int y);

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_PLATFORM_HEADER */

