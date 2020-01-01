/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * GUI Toolkit event definitions.
 */

#ifndef ___GUI_COMMON_GUIEVENT_H
#define ___GUI_COMMON_GUIEVENT_H

#include <JkTypes.h>

#include <JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_GUIEvent
 * @{
 */

/**
 * @internal
 * The event start
 */
#define JG_GUI_EVT_START                    (0x00010000)

/**
 * Component redrawing request
 * 
 * When requesting component redrawing, use #JginGUIEventPostEvent() to notify 
 * this event to JBlend. The area in which redrawing takes place is the 
 * entire area occupied by the component. <br>
 * The values of the param members of the JGT_GUIEvent structure passed to the
 * argument of #JginGUIEventPostEvent() are indicated in the parameters
 * below.
 * 
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_REPAINT                  (JG_GUI_EVT_START + 0x00)

/*#define JG_GUI_EVT_REPAINT_RECT             (JG_GUI_EVT_START + 0x01)*/

/**
 * Redrawing request of the entire screen
 * 
 * When requesting redrawing of the entire screen, use #JginGUIEventPostEvent()
 * to notify the event to JBlend.
 * The values of the param members of the JGT_GUIEvent structure passed to the
 * argument of #JginGUIEventPostEvent() are indicated in the parameters
 * below.
 * 
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_REPAINT_SCREEN           (JG_GUI_EVT_START + 0x02)

/*#define JG_GUI_EVT_REPAINT_SCREEN_RECT      (JG_GUI_EVT_START + 0x03)*/

/**
 * Occupies the screen for drawing beyond the current area.
 * 
 * When requesting screen occupation, use #JginGUIEventPostEvent() to notify the
 * event to JBlend. While the screen is occupied, JBlend performs no
 * screen updating.
 * 
 * This event can be used when screen occupation is requested by a GUI toolkit 
 * component or by a GUI component original to the native system. 
 * 
 * If a GUI toolkit component requests screen occupation, the values of the 
 * JGT_GUIEvent structure members passed in a parameter to #JginGUIEventPostEvent()
 * are indicated in the parameters below.
 * 
 *   @param component The handle of the component requesting screen occupation.
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 * 
 * If a native system original GUI component requests screen occupation, the values of the 
 * JGT_GUIEvent structure members passed in a parameter to #JginGUIEventPostEvent()
 * are indicated in the parameters below.
 * 
 *   @param component #JK_INVALID_HANDLE
 *   @param param1 The screen ID
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *  
 * When a native system original GUI component requests screen occupation, set
 * #JK_INVALID_HANDLE in the <i>component</i> member of the JGT_GUIEvent structure, and set
 * a unique screen ID in the <i>param1</i> member for identifying the GUI component. 
 * Set a screen ID value of 0x80000000 or greater.
 * When JBlend stops screen occupation, the screen ID is used to identify the
 * affected GUI component.
 * 
 * When a native system original GUI component requests screen occupation,
 * JginGUIEventPostEvent() can be called not only from the JVM task but also from a native system task.
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_OCCUPY_SCREEN            (JG_GUI_EVT_START + 0x04)

/**
 * Stops occupation of the screen.
 * 
 * When screen occupation is ended and control is passed to JBlend, use
 * #JginGUIEventPostEvent() to notify this event to JBlend. If the event
 * #JG_GUI_EVT_OCCUPY_SCREEN is notified, be sure to notify this event after
 * completing the necessary processing. 
 * 
 * This event can be used when screen occupation release is requested by a GUI toolkit 
 * component or by a GUI component original to the native system. 
 * 
 * If a GUI toolkit component requests screen occupation release,
 * the values of the JGT_GUIEvent structure members passed to #JginGUIEventPostEvent() 
 * are indicated in the parameters below.
 * 
 *   @param component The handle of the component requesting screen occupation release
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 * 
 * If a native system original GUI component requests screen occupation release, 
 * the values of the JGT_GUIEvent structure members passed to #JginGUIEventPostEvent()
 * are indicated in the parameters below.
 *  
 *   @param component #JK_INVALID_HANDLE
 *   @param param1 The screen ID
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *  
 * When a native system original GUI component requests screen occupation release, set
 * #JK_INVALID_HANDLE in the <i>component</i> member of the JGT_GUIEvent structure, and set
 * a unique screen ID in the <i>param1</i> member for identifying the GUI component. 
 *  Designate as the screen ID the same value as that notified by 
 * #JG_GUI_EVT_OCCUPY_SCREEN when screen occupation was requested.
 * 
 * When a native system original GUI component requests screen occupation release,
 * JginGUIEventPostEvent() can be called not only from a JVM task but also from a native system task.
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_RELEASE_SCREEN           (JG_GUI_EVT_START + 0x05)

/**
 * Occupies user input events.
 * 
 * When a component occupies user input events, notify this event to JBlend 
 * by calling #JginGUIEventPostEvent(). After receiving this event notification, 
 * JBlend will notify the component of all user input events.<br>
 * After completing the necessary processing, be sure to issue a 
 * #JG_GUI_EVT_RELEASE_INPUT_EVENT event releasing the user input event 
 * occupation. <br>
 * The values of the param members of the JGT_GUIEvent structure passed to the
 * event argument of #JginGUIEventPostEvent() are indicated in the parameters
 * below.
 * 
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_OCCUPY_INPUT_EVENT       (JG_GUI_EVT_START + 0x06)

/**
 * Stops user input event occupation.
 * 
 * When user input occupation is ended and control is passed to JBlend, use
 * #JginGUIEventPostEvent() to notify the event to JBlend. If the event
 * #JG_GUI_EVT_OCCUPY_INPUT_EVENT is notified, be sure to notify this event 
 * after completing the necessary processing. <br>
 * The values of the param members of the JGT_GUIEvent structure passed to the
 * event argument of #JginGUIEventPostEvent() are indicated in the parameters
 * below.
 * 
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_RELEASE_INPUT_EVENT      (JG_GUI_EVT_START + 0x07)

/**
 *   Changes the preferred size of a component.
 *   
 *   When the native system changes the preferred size of a component, 
 *   pass this event to JBlend by means of #JginGUIEventPostEvent(). 
 *   When this event is passed, JBlend performs re-layout for the component.
 *
 *   The values of the param members of the #JGT_GUIEvent structure passed to the
 *   event argument of #JginGUIEventPostEvent() are indicated in the parameters below.
 * 
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_EVT_NOTIFY_PREF_SIZE_CHANGED     (JG_GUI_EVT_START + 0x08)

/**
 * @internal
 * The maximum GUI event value
 */
#define JG_GUI_EVT_END                      (JG_GUI_EVT_START + 0x08)

/**
 * The GUI event
 */
typedef struct JGT_GUIEvent {
    /**
     * The event ID
     *
     * The ID designated here becomes a response handler argument and can be 
     * used to distinguish events.
     */
    JKUint32 id;
    
    /**
     * The handle of the component generating the event
     */
    JGCom component;
    
    /**
     * The event type
     */
    JKUint32 type;
    
    /**
     * Event-specific value 1
     */
    JKUint32 param1;
    
    /**
     * Event-specific value 2
     */
    JKUint32 param2;
    
    /**
     * Event-specific value 3
     */
    JKUint32 param3;
    
    /**
     * Event-specific value 4
     */
    JKUint32 param4;
    
} JGT_GUIEvent;

/**
 * The GUI event response handler type
 * 
 * @param guiEvent
 *        A pointer to the JGT_GUIEvent structure holding information about the
 *        processed GUI event. 
 *        There is no guarantee that this pointer will be the same as the pointer
 *        to the JGT_GUIEvent structure passed as the guiEvent argument with 
 *        #JginGUIEventPostEvent(), so do not perform processing that assumes
 *        the same pointer.
 * 
 *  The response handler type for the GUI event set with 
 *  #JginGUIEventPostEvent().
 */
typedef void (*JGT_GUIEvtResponseHandler)(const JGT_GUIEvent *guiEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_GUIEVENT_H */

