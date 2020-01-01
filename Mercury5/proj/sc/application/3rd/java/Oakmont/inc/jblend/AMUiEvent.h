/*
 * Copyright 2000-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMUiEvent.h
 *  Device Event Notification JBI
 *
 */
/**
 * @addtogroup Device_Event_Notification_JBI
 * @{
 */

#ifndef ___AMUIEVENT_H
#define ___AMUIEVENT_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Key event types
 */
/**
 *  Key pressed.
 *
 *  When this event is passed to JBlend, then if an object of the 
 *  <code>javax.microedition.lcdui.Canvas</code> class or its subclass is set as
 *  the current <code>Displayable</code>, the <code>keyPressed</code> method is called.
 */
#define AM_EVENT_KEY_PRESSED        0
/**
 *  Key released.
 *
 *  When this event is passed to JBlend, then if an object of the 
 *  <code>javax.microedition.lcdui.Canvas</code> class or its subclass is set as
 *  the current <code>Displayable</code>, the <code>keyReleased</code> method is called.
 */
#define AM_EVENT_KEY_RELEASED       1
/**
 *  Key repeated.
 *
 *  When this event is passed to JBlend, an operation is performed as follows
 *  with respect to the object set as current <code>Displayable</code>. 
 *  - If the object belongs to the <code>javax.microedition.lcdui.Canvas</code> class or its subclass,
 *    the <code>keyRepeated</code> method is called.
 *  - If the object belongs to the <code>javax.microedition.lcdui.Form</code> class or its 
 *    subclass, scrolling of the screen and/or the actions of GUI components on the screen 
 *    are executed.
 *  .
 */
#define AM_EVENT_KEY_REPEATED       2
/**
 *  Key action occurred.
 *
 *  When this event is passed to JBlend, an operation takes place as follows.
 *  - If an object belonging to the <code>javax.microedition.lcdui.Form</code> class or its subclass 
 *    is set as the current <code>Displayable</code>, scrolling of the screen and/or the actions of 
 *    GUI components on the screen are executed.
 *  - If this event is passed as an event for a soft key, JBlend calls the
 *    <code>commandAction</code> method of the <code>javax.microedition.lcdui.CommandListener</code>
 *    interface implemented in the object set as current <code>Displayable</code> by the Java
 *    application.
 */
#define AM_EVENT_KEY_CLICKED        3

/**
 */
/**
 *  The 0 key
 */
#define AM_KEYCODE_NUM0             0
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM0.
 */
#define AM_EVENT_KEY_NUM0           AM_KEYCODE_NUM0
/**
 *  The 1 key
 */
#define AM_KEYCODE_NUM1            0x01
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM1.
 */
#define AM_EVENT_KEY_NUM1           AM_KEYCODE_NUM1
/**
 *  The 2 key
 */
#define AM_KEYCODE_NUM2             0x02
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM2.
 */
#define AM_EVENT_KEY_NUM2           AM_KEYCODE_NUM2
/**
 *  The 3 key
 */
#define AM_KEYCODE_NUM3             0x03
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM3.
 */
#define AM_EVENT_KEY_NUM3           AM_KEYCODE_NUM3
/**
 *  The 4 key
 */
#define AM_KEYCODE_NUM4             0x04
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM4.
 */
#define AM_EVENT_KEY_NUM4           AM_KEYCODE_NUM4
/**
 *  The 5 key
 */
#define AM_KEYCODE_NUM5             0x05
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM5.
 */
#define AM_EVENT_KEY_NUM5           AM_KEYCODE_NUM5
/**
 *  The 6 key
 */
#define AM_KEYCODE_NUM6             0x06
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM6.
 */
#define AM_EVENT_KEY_NUM6           AM_KEYCODE_NUM6
/**
 *  The 7 key
 */
#define AM_KEYCODE_NUM7             0x07
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM7.
 */
#define AM_EVENT_KEY_NUM7           AM_KEYCODE_NUM7
/**
 *  The 8 key
 */
#define AM_KEYCODE_NUM8             0x08
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM8.
 */
#define AM_EVENT_KEY_NUM8           AM_KEYCODE_NUM8
/**
 *  The 9 key
 */
#define AM_KEYCODE_NUM9             0x09
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_NUM9.
 */
#define AM_EVENT_KEY_NUM9           AM_KEYCODE_NUM9
/**
 *  The * key
 */
#define AM_KEYCODE_ASTERISK         0x0a
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_ASTERISK.
 */
#define AM_EVENT_KEY_ASTERISK       AM_KEYCODE_ASTERISK
/**
 *  The # key
 */
#define AM_KEYCODE_POUND            0x0b
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_POUND.
 */
#define AM_EVENT_KEY_POUND          AM_KEYCODE_POUND
/**
 *  The Left key
 */
#define AM_KEYCODE_LEFT             0x10
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_LEFT.
 */
#define AM_EVENT_KEY_LEFT           AM_KEYCODE_LEFT
/**
 *  The Up key
 */
#define AM_KEYCODE_UP               0x11
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_UP.
 */
#define AM_EVENT_KEY_UP             AM_KEYCODE_UP
/**
 *  The Right key
 */
#define AM_KEYCODE_RIGHT            0x12
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_RIGHT.
 */
#define AM_EVENT_KEY_RIGHT          AM_KEYCODE_RIGHT
/**
 *  The Down key
 */
#define AM_KEYCODE_DOWN             0x13
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_DOWN.
 */
#define AM_EVENT_KEY_DOWN           AM_KEYCODE_DOWN
/**
 *  The Select key
 */
#define AM_KEYCODE_SELECT           0x14
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_SELECT.
 */
#define AM_EVENT_KEY_SELECT         AM_KEYCODE_SELECT
/**
 *  The Soft key 1
 */
#define AM_KEYCODE_SOFT1            0x15
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_SOFT1.
 */
#define AM_EVENT_KEY_SOFT1           AM_KEYCODE_SOFT1
/**
 *  The Soft key 2
 */
#define AM_KEYCODE_SOFT2            0x16
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_SOFT2.
 */
#define AM_EVENT_KEY_SOFT2          AM_KEYCODE_SOFT2
/**
 *  The Soft key 3
 */
#define AM_KEYCODE_SOFT3            0x17
/**
 * @deprecated
 *  Modified to #AM_KEYCODE_SOFT3.
 */
#define AM_EVENT_KEY_SOFT3          AM_KEYCODE_SOFT3
/**
 *  The Send key
 */
#define AM_KEYCODE_SEND             0x19
/**
 *  The Clear key
 */
#define AM_KEYCODE_CLEAR            0x1a

/**
 * The minimum value used for a native system original key code.
 *
 * To define a native system original key code, use integers of this value
 * or above, by assigning successive values starting from this value.
 * For details of defining native system original keys, see description of
 * AmSetKeyCodeTable() and #JKT_ExtKeyTable structure.
 */
#define AM_KEYCODE_USER_BASE       0x100

/**
 */
/**
 *  Pointer button pressed
 *
 *  When this event is passed to JBlend, then if an object of the 
 *  <code>javax.microedition.lcdui.Canvas</code> class or its subclass is set as
 *  the current <code>Displayable</code>, the <code>pointerPressed</code> method is called.
 */
#define AM_EVENT_POINTER_PRESSED    0
/**
 *  Pointer button released
 *
 *  When this event is passed to JBlend, then if an object of the 
 *  <code>javax.microedition.lcdui.Canvas</code> class or its subclass is set as
 *  the current <code>Displayable</code>, the <code>pointerReleased</code> method is called.
 */
#define AM_EVENT_POINTER_RELEASED   0x01
/**
 *  Pointer action occurred
 *
 *  When this event is passed to JBlend, then if an object 
 *  belonging to the <code>javax.microedition.lcdui.Form</code> class or its 
 *  subclass is set as the current <code>Displayable</code>, 
 *  scrolling of the screen and/or the actions of GUI components on the screen are executed.
 */
#define AM_EVENT_POINTER_CLICKED    0x02
/**
 *  Pointer moved (Absolute coordinate)
 *
 *  When this event is passed to JBlend, an operation is performed as follows
 *  with respect to the object set as current <code>Displayable</code>. 
 *  - If the object belongs to the <code>javax.microedition.lcdui.Canvas</code> class or its subclass,
 *    the <code>pointerDragged</code> method is called.
 *  - If the object belongs to the <code>javax.microedition.lcdui.Form</code> class or its 
 *    subclass, scrolling of the screen and/or the actions of GUI components on the screen 
 *    are executed.
 *  .
 */
#define AM_EVENT_POINTER_MOVED      0x03


#define AM_EVENT_POINTER_EVENT_END  0x04

/**
 */
/**
 *  Decode error occurred.
 */
#define AM_EVENT_IMAGE_DECODE_ERROR         0
/**
 *  Image size is now available.
 */
#define AM_EVENT_IMAGE_DECODE_SIZE_FIXED    0x01
/**
 *  Now redrawing available.
 */
#define AM_EVENT_IMAGE_DECODE_UPDATE        0x02
/**
 *  Decode complete
 */
#define AM_EVENT_IMAGE_DECODE_FINISHED      0x03

/**
 *                Notifies the Java execution environment of a key event.
 * @param type    The key event type. Designate one of the following.<br>
 *                <ul>
 *                 <li>#AM_EVENT_KEY_PRESSED
 *                 <li>#AM_EVENT_KEY_RELEASED
 *                 <li>#AM_EVENT_KEY_REPEATED
 *                 <li>#AM_EVENT_KEY_CLICKED
 *                </ul>
 * @param keyCode The key code.
 *                Designate a value named starting with <i>AM_KEYCODE_</i>.
 * @param keyChar Always set to 0 (zero). (This parameter is reserved for future use.)
 * @return        #JK_TRUE: The event was added to the queue. (Success)<br>
 *                #JK_FALSE: The event could not be added to the queue because it was full. (Failure)
 * 
 * When an #AM_EVENT_KEY_PRESSED event or #AM_EVENT_KEY_RELEASED event is passed to
 * the Java execution environment, the native system must notify an #AM_EVENT_KEY_CLICKED 
 * event at either of the following timings:
 * - Immediately after notification of an #AM_EVENT_KEY_PRESSED event, or
 * - Immediately before notification of an #AM_EVENT_KEY_RELEASED event.
 * .
 *
 * If a key repeat event occurs while a key is held down continuously, notify an
 * #AM_EVENT_KEY_REPEATED event at regular intervals while the key continues to be held down.
 * The #AM_EVENT_KEY_REPEATED event notification interval is implementation dependent. 
 *
 * Soft key actions, as well as scrolling of the screen and the actions of GUI components on 
 * the screen displayed by the <code>javax.microedition.lcdui.Form</code> class, 
 * are triggered by an #AM_EVENT_KEY_CLICKED event or #AM_EVENT_KEY_REPEATED event.
 * The device manufacturer may choose to execute the GUI component action either when a key
 * is pressed or when it is released, depending on the #AM_EVENT_KEY_CLICKED event 
 * notification timing.
 * The order of key event notification in each case is as follows. 
 *
 * Order of key events when GUI component action is triggered by key press <br>
 * -# #AM_EVENT_KEY_PRESSED
 * -# #AM_EVENT_KEY_CLICKED
 * -# #AM_EVENT_KEY_REPEATED
 *    (If a key repeat occurs while a key is held down continuously, notification is repeated.) 
 * -# #AM_EVENT_KEY_RELEASED
 * .
 *
 * Order of key events when GUI component action is triggered by key release<br>
 * -# #AM_EVENT_KEY_PRESSED
 * -# #AM_EVENT_KEY_REPEATED
 *    (If a key repeat occurs while a key is held down continuously, notification is repeated.) 
 * -# #AM_EVENT_KEY_CLICKED
 * -# #AM_EVENT_KEY_RELEASED
 * .
 *
 */
JKBool AmNotifyKeyEvent( JKSint32 type, JKSint32 keyCode, JKWChar keyChar );


/**
 *                Notifies Java execution environment of pointer event.
 * @param type    The pointer event type. Designate one of following.<br>
 *                <ul>
 *                 <li>#AM_EVENT_POINTER_PRESSED
 *                 <li>#AM_EVENT_POINTER_RELEASED
 *                 <li>#AM_EVENT_POINTER_CLICKED
 *                 <li>#AM_EVENT_POINTER_MOVED
 *                </ul>
 * @param buttonNo The button number.
 * @param x        The x coordinate of the point where the event was generated.
 * @param y        The y coordinate of the point where the event was generated.
 * @return         #JK_TRUE if function succeeded.<br>
 *                 #JK_FALSE if function failed.
 *
 * #JK_FALSE is returned if event queue is full.
 */
JKBool AmNotifyPointerEvent( JKSint32 type, JKSint32 buttonNo, JKSint32 x, JKSint32 y );




/**
 *  Notifies Java execution environment of event that requests redrawing of entire screen.
 *
 * @return         #JK_TRUE if function succeeded.<br>
 *                 #JK_FALSE if function failed.
 *
 * The return value specification is preserved for backward compatibility.
 * The native system currently need not check the value.
 * 
 * This function returns #JK_FALSE when the event queue has not been created yet.
 * JBlend creates the event queue during the interval between passing
 * JVM events #JK_VMEVENT_VMPAINTREADY and #JK_VMEVENT_APPSTARTED to the native system.
 * Thus if the native system calls this function before the #JK_VMEVENT_APPSTARTED 
 * event is passed, this function may fail and return #JK_FALSE.
 * However, even in this case screen repainting is performed normally at
 * the time the Java application starts up. 
 */
JKBool AmNotifyRepaintEvent( void );



/**
 * The type of the callback function for notifying the start of key event or pointer event processing.
 * @param category The event category.  One of the following is designated.
 *                 <ul>
 *                   <li>0: Key event
 *                   <li>1: Pointer event
 *                  </ul>
 * @param type    The event type. One of the following is designated.
 *                <ul>
 *                 <li>#AM_EVENT_KEY_PRESSED
 *                 <li>#AM_EVENT_KEY_RELEASED
 *                 <li>#AM_EVENT_KEY_REPEATED
 *                 <li>#AM_EVENT_KEY_CLICKED
 *                 <li>#AM_EVENT_POINTER_PRESSED
 *                 <li>#AM_EVENT_POINTER_RELEASED
 *                 <li>#AM_EVENT_POINTER_CLICKED
 *                 <li>#AM_EVENT_POINTER_MOVED
 *                </ul>
 * @param numParams The number of event parameters.
 * @param params    A pointer to an array holding the event parameters.<br>
 *                  Key event:
 *                  <table>
 *                   <tr><td>*(<i>params</i> + 0)</td><td>the <i>keyCode</i> parameter of #AmNotifyKeyEvent()</td></tr>
 *                   <tr><td>*(<i>params</i> + 1)</td><td>the <i>keyChar</i> parameter of #AmNotifyKeyEvent()</td></tr>
 *                  </table>
 *                  Pointer event:
 *                  <table>
 *                   <tr><td>*(<i>params</i> + 0)</td><td>the <i>buttonNo</i> parameter of #AmNotifyPointerEvent()</td></tr>
 *                   <tr><td>*(<i>params</i> + 1)</td><td>the <i>x</i> parameter of #AmNotifyPointerEvent()</td></tr>
 *                   <tr><td>*(<i>params</i> + 2)</td><td>the <i>y</i> parameter of #AmNotifyPointerEvent()</td></tr>
 *                  </table>
 *
 * This is the type of the callback function that JBlend uses to notify the
 * start of processing for key events or pointer events.
 * Designate a function of this type in a parameter passed to #AmUiEventRegisterCallback(), 
 * only for events requiring a callback.
 * @see AmNotifyKeyEvent()
 */
typedef void (*JKUiEventCallback) ( JKSint32 category, JKSint32 type, JKSint32 numParams, JKSint32 *params );

/**
 *                 Registers an event callback function in the Java execution environment.
 * @param category The event category.  Designate one of the following.
 *                 <ul>
 *                  <li>0: Key event
 *                  <li>1: Pointer event
 *                 </ul>
 * @param type     The event type. Designate one of the following.
 *                 <ul>
 *                  <li>#AM_EVENT_KEY_PRESSED
 *                  <li>#AM_EVENT_KEY_RELEASED
 *                  <li>#AM_EVENT_KEY_REPEATED
 *                  <li>#AM_EVENT_KEY_CLICKED
 *                  <li>#AM_EVENT_POINTER_PRESSED
 *                  <li>#AM_EVENT_POINTER_RELEASED
 *                  <li>#AM_EVENT_POINTER_CLICKED
 *                  <li>#AM_EVENT_POINTER_MOVED
 *                 </ul>
 * @param uiEventCallback
 *                 A pointer to a callback function for key event or pointer 
 *                 event processing notification. The type parameter of the
 *                 callback function takes the same value as the type 
 *                 parameter of #AmNotifyKeyEvent() or #AmNotifyPointerEvent().
 * @return         #JK_TRUE if the operation succeeded.<br>
 *                 #JK_FALSE if the operation failed 
 *                 (invalid parameter or mismatching of parameters).
 *
 * This function registers in JBlend an entry of the callback function 
 * designated in the <i>uiEventCallback</i> parameter. The function entry that has been 
 * already registered in JBlend is overwritten by this function.
 * Just before processing UI events, JBlend calls the callback 
 * function in the JVM task context. Then JBlend processes UI events and
 * distributes them.
 * 
 * The native system must perform the function registration by this function 
 * after it has received a 
 * #JK_VMEVENT_VMSTARTED
 * JVM event.
 *
 * The registration should be performed only for types of events on which
 * the native system should receive callback; no registration is required 
 * for events that does not have to be informed to the native system.
 * When it becomes unnecessary to receive callback on an event on 
 * which a callback function has been registered, cancel that registration 
 * by calling this function, passing #JK_NULL to the <i>uiEventCallback</i> parameter.
 *
 * JBlend calls the callback function in the JVM context, and therefore
 * the call may affect the performance of JBlend. Thus, in order to 
 * avoid that problem, the processing time in the callback function should 
 * be as short as possible. This may suggest that, for the processing 
 * that requires long period, the callback function should transfer that 
 * processing to a separated asynchronous task. In this case, perform 
 * exclusion between the asynchronous task and the processing requested 
 * by a JSI, when necessary.
 */
JKBool AmUiEventRegisterCallback( JKSint32 category, JKSint32 type, JKUiEventCallback uiEventCallback );

#ifdef __cplusplus
}
#endif

#endif


/**
 * @} end of group
 */
