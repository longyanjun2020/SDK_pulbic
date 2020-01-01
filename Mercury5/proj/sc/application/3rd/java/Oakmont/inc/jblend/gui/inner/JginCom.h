/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying Component properties.
 * 
 * The Component properties are included in all GUI components.
 */

#ifndef ___GUI_INNER_COMPONENT_H
#define ___GUI_INNER_COMPONENT_H

#include <JkTypes.h>
#include <JkFont.h>
#include <JkVideoComponent.h>

#include <JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Component
 * @{
 */

/**
 *   The GUI component state designated when GUI component default design is changed: Disabled 
 *   
 *   This constant and the constant representing the GUI component attribute are 
 *   designated in the <i>type</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type) as a bit-wise OR value.
 */
#define JG_COM_ATTR_STATE_DISABLED    (0x0100)

/**
 *   The GUI component state designated when GUI component default design is changed: Enabled
 *   
 *   This constant and the constant representing the GUI component attribute are 
 *   designated in the <i>type</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type) as a bit-wise OR value.
 */
#define JG_COM_ATTR_STATE_ENABLED     (0x0200)

/**
 *   The GUI component state designated when GUI component default design is changed: Focused
 *   
 *   This constant and the constant representing the GUI component attribute are 
 *   designated in the <i>type</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type) as a bit-wise OR value.
 */
#define JG_COM_ATTR_STATE_FOCUSED     (0x0400)

/**
 *   The GUI component state designated when GUI component default design is changed: Active
 *   
 *   This constant and the constant representing the GUI component attribute are 
 *   designated in the <i>type</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type) as a bit-wise OR value.
 */
#define JG_COM_ATTR_STATE_ACTIVE      (0x0800)

/**
 * @internal
 */
#define JG_COM_ATTR_STATE_MASK_BASE       (0xFF00)

/**
 * @internal
 */
#define JG_COM_ATTR_STATE_MASK_EXTEND     (0xFF0000)

/**
 * @internal
 */
#define JG_COM_ATTR_STATE_MASK            \
    (JG_COM_ATTR_STATE_MASK_BASE | JG_COM_ATTR_STATE_MASK_EXTEND)

/**
 * @internal
 */
#define JG_COM_ATTR_MASK                  (0xFF)

/**
 *   The GUI component line type attribute: Dotted line
 *   
 *   This is used for designating the line type when GUI component default design is changed.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_LINE_DOTTED      (0x01)

/**
 *   The GUI component line type attribute: Solid line
 *   
 *   This is used for designating the line type when GUI component default design is changed.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_LINE_SOLID       (0x02)

/**
 *   The GUI component line type attribute: None
 *   
 *   This is used for designating the line type when GUI component default design is changed.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_LINE_NONE        (0x03)

/**
 *   The GUI component color attribute value: Fixed color
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the fixed color. 
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 *   
 */
#define JG_COM_VAL_COLOR_FIXED                 (0x01)

/**
 *   GUI component color attribute value: Foreground color
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the GUI component 
 *   forefront color. 
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_COLOR_FOREGROUND            (0x02)

/**
 *   GUI component color attribute value: Background color
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the GUI component 
 *   background color. 
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_COLOR_BACKGROUND           (0x03)

/**
 *   GUI component color attribute value: Foreground color setting
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the color 
 *   of the "foreground" element.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_COLOR_FOREGROUND_SYNC    (0x04)

/**
 *   GUI component color attribute value: Background color setting
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the color 
 *   of the "background" element.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_COLOR_BACKGROUND_SYNC    (0x05)

/**
 *   GUI component color attribute value: Parent component background color
 *   
 *   This is used for designating the color when GUI component default design is changed.
 *   Indicates that the GUI component element is to be drawn with the parent component 
 *   background color. 
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_COLOR_CONTAINER_BACKGROUND    (0x06)

/**
 *   GUI component attribute value: Valid
 *   
 *   This is used for designating the attribute value when GUI component default design is changed.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_FLG_ON                 (0x01)

/**
 *   GUI component attribute value: Not valid
 *   
 *   This is used for designating the attribute value when GUI component default design is changed.
 *   This constant is designated in the <i>value1</i> parameter of JginXXXXSetStaticAttribute()
 *   (XXXX: GUI component type).
 */
#define JG_COM_VAL_FLG_OFF                (0x02)

/**
 * The GUI component position was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKSint32 The current x coordinate setting
 * @param param2
 *        JKSint32 The current y coordinate setting
 * @param param3
 *        JKSint32 The previous x coordinate setting
 * @param param4
 *        JKSint32 The previous y coordinate setting
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_MOVED                (0x00)

/**
 * The GUI component size was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The current width setting
 * @param param2
 *        JKUint32 The current height setting
 * @param param3
 *        JKUint32 The previous width setting
 * @param param4
 *        JKUint32 The previous height setting
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_SIZE_CHANGED         (0x01)

/**
 * The GUI component foreground color was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The current foreground color
 * @param param2
 *        JKUint32 The previous foreground color
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_FGCOLOR_CHANGED      (0x02)

/**
 * The GUI component background color was set.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The current background color
 * @param param2
 *        JKUint32 The previous background color
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_BGCOLOR_CHANGED      (0x03)

/**
 * @internal
 */
#define JG_COM_EVT_VISIBLE_CHANGED      (0x04)

/**
 * The GUI component state changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The new state
 * @param param2
 *        JKUint32 The previous state
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_STATE_CHANGED        (0x05)

/**
 * The GUI component font was changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKFontHandle The new font
 * @param param2
 *        JKFontHandle The previous font
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_FONT_CHANGED         (0x06)

/**
 * The horizontal alignment method of items inside the GUI component changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The new alignment method
 * @param param2
 *        JKUint32 The previous alignment method
 * @param param3 -
 * @param param4 -
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_ALIGN_X_CHANGED      (0x07)

/**
 * The vertical alignment method of items inside the GUI component changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The new alignment method
 * @param param2
 *        JKUint32 The previous alignment method
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_ALIGN_Y_CHANGED      (0x08)

/**
 * The horizontal alignment method changed because the GUI component items did not 
 * fit inside the component.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The new alignment method
 * @param param2
 *        JKUint32 The previous alignment method
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_CUT_POLICY_X_CHANGED     (0x09)

/**
 * The vertical alignment method changed because the GUI component items did not 
 * fit inside the component.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The new alignment method
 * @param param2
 *        JKUint32 The previous alignment method
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_CUT_POLICY_Y_CHANGED     (0x0a)

/**
 * The GUI component preferred size was changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The current width setting
 * @param param2
 *        JKUint32 The current height setting
 * @param param3
 *        JKUint32 The previous width
 * @param param4
 *        JKUint32 The previous height
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_PREFERRED_SIZE_CHANGED   (0x0b)

/**
 * The GUI component minimum size was changed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKUint32 The current width setting
 * @param param2
 *        JKUint32 The current height setting
 * @param param3
 *        JKUint32 The previous width
 * @param param4
 *        JKUint32 The previous height
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_MINIMUM_SIZE_CHANGED     (0x0c)

/**
 * The GUI component needs to be displayed.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKGraphicsContext The graphics context handle
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * The actual displaying is done when #JG_COM_EVT_PAINT is called subsequently.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_SHOW                (0x0d)

/**
 * GUI Component drawing is necessary.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1
 *        JKGraphicsContext The graphic context handle
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * If drawing is to be performed in the event handler, do so applying the clip 
 * area set for the graphics context designated in param1. It is not necessary 
 * to retrieve the state of the graphics context at the time this event was 
 * notified .
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_PAINT               (0x0e)

/**
 * The GUI component needs to be hidden.
 * 
 * When this event is processed by the event handler defined as 
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 * structure passed to the event handler by JBlend are indicated in the 
 * following parameters. The event handler return value should be as indicated 
 * below.
 *
 * @param param1 -
 * @param param2 -
 * @param param3 -
 * @param param4 -
 * 
 * @return
 *         Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_HIDE                (0x0f)

/**
 *   The GUI component focus policy changed.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 JKUint32 The newly set focus policy
 *   @param param2 JKUint32 The previous focus policy
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_FOCUS_POLICY_CHANGED     (0x10)

/**
 *   The preferred GUI component width for the designated height was requested.
 *
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 JKSint32 The designated height
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the preferred component width for the designated height.
 *   
 *    This event is issued when the event handler which handles 
 *    #JG_COM_EVT_GET_PREF_HEIGHT returns a height greater or equal to the 
 *    display size, or when only the height of the GUI component 
 *    is designated by the Java application and 
 *    JgComGetPreferredWidth() is called by the native system.
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 * @see JgComGetPrefWidthWithRespectToHeight
 */
#define JG_COM_EVT_GET_PREF_WIDTH_WITH_RESPECT_TO_HEIGHT     (0x11)

/**
 *   The preferred GUI component height for the designated width was requested.
 * 
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 * 
 *   @param param1 JKSint32 The designated width
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the preferred component height for the designated width.
 *   
 *    This event is issued when the event handler which handles 
 *    #JG_COM_EVT_GET_PREF_WIDTH returns a height greater or equal to the 
 *    display size, or when only the height of the GUI component 
 *    is designated by the Java application and 
 *    JgComGetPreferredHeight() is called by the native system.
 *   
 * 
 * @if NOT_READY
 * @endif
 * 
 * @see JGT_ComEvent::type
 * @see JgComGetPrefHeightWithRespectToWidth
 */
#define JG_COM_EVT_GET_PREF_HEIGHT_WITH_RESPECT_TO_WIDTH     (0x12)

/**
 *   Hidden GUI Component drawing is necessary.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 JKGraphicsContext The graphic context handle
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   
 *   @return Return 0.
 *   
 *   If drawing is to be performed in the event handler, do so applying the clip 
 *   area set for the graphics context designated in param1. It is not necessary 
 *   to retrieve the state of the graphics context at the time this event was 
 *   notified .
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_PAINT_HIDDEN         (0x13)

/**
 *   The preferred GUI component width was requested.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the preferred component width.
 *   
 *   This event is generated when #JgComGetPreferredWidth() is called.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_GET_PREF_WIDTH       (0x14)

/**
 *   The preferred GUI component height was requested.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the preferred component height.
 *   
 *   This event is generated when #JgComGetPreferredHeight() is called.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_GET_PREF_HEIGHT      (0x15)

/**
 *   The GUI component minimum width was requested.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the component minimum width.
 *   
 *   This event is generated when #JgComGetMinimumWidth() is called.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_GET_MIN_WIDTH        (0x16)

/**
 *   The GUI component minimum height was requested.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return JKSint32 Return the component minimum height.
 *   
 *   This event is generated when #JgComGetMinimumHeight() is called.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_GET_MIN_HEIGHT       (0x17)

/**
 *   Truncate mode of the GUI component has been set. 
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKBool The current truncate mode setting
 *   @param param2 #JKBool The previous truncate mode setting
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_TRUNCATE_MODE_CHANGED        (0x18)

/**
 *   Relayout of the inside of the GUI component was requested.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return       Return 1 if the native system performed relayout.
 *                 Return 0 if relayout was unnecessary.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_RELAYOUTING                  (0x19)

/**
 *   Relayout was performed in the GUI component.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_COM_EVT_RELAYOUTED                   (0x1a)

/**
 * @if SUPPORT_RTL
 *   The item layout direction of a GUI component has been set.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent 
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKUint The set layout direction.
 *   @param param2 #JKUint The previous layout direction setting
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 *
 * @endif
 */
#define JG_COM_EVT_ORIENTATION_CHANGED      (0x1b)

/**
 * @internal
 * The maximum value for component event definitions.
 */
#define JG_COM_EVT_END                  (0x1c)

/**
 * The component event
 */
typedef struct JGT_ComEvent {
    /**
     * Handle of the GUI component generating the event
     */
    JGCom component;
    
    /**
     * The generated event
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
    
} JGT_ComEvent;

/**
 * The component event handler
 * 
 * @param comEvent
 *        A pointer to the JGT_ComEvent structure holding the generated event 
 *        information.
 * 
 * @return
 *        Return the processing result.
 * 
 * The event information set in the parameter comEvent differs depending on the 
 * event to be processed. Refer to the individual event value definitions.
 * 
 */
typedef JKUint32 (*JGT_ComEvtHandler)(const JGT_ComEvent *comEvent);

/**
 *   Sets the GUI component focus policy.
 * 
 *   @param component The GUI component handle
 *   @param policy The focus policy. Designate one of the following.
 *                 <ul>
 *                  <li> #JG_COM_FOCUS_POLICY_OCCUPY
 *                  <li> #JG_COM_FOCUS_POLICY_SMOOTH
 *                 </ul>
 * 
 * <p>
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When policy is an illegal value.</li>
 *   </ul>
 * 
 * @see JgComGetFocusPolicy()
 * 
 */
void JginComSetFocusPolicy(JGCom component, JKUint32 policy);

/**
 *   Sets the inset values of a GUI component.
 *   
 *   @param component The GUI component handle
 *   @param top       The top inset value.
 *   @param left      The left inset value.
 *   @param right     The right inset value.
 *   @param bottom    The bottom inset value.
 *   
 *   The inset values must be in the range of 0 to 32767.
 *
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When top or left or right or bottom is a negative value.</li>
 *   </ul>
 */
void JginComSetInsets(JGCom component, JKSint32 top, JKSint32 left, JKSint32 right, JKSint32 bottom);

/**
 * Sets the GUI component size.
 * 
 * @param component
 *        The GUI component handle
 * @param width
 *        The width
 * @param height
 *        The height
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When width or height is a negative value.</li>
 *   </ul>
 * 
 * @see JgComGetWidth()
 * @see JgComGetHeight()
 * 
 */
void JginComSetSize(JGCom component, JKSint32 width, JKSint32 height);

/**
 * Sets the GUI component foreground color.
 * 
 * @param component
 *        The GUI component handle
 * @param color
 *        The foreground color setting. Designate this in ARGB format.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetForeground()
 * 
 */
void JginComSetForeground(JGCom component, JKColor color);

/**
 * Sets the GUI component background color.
 * 
 * @param component
 *        The GUI component handle
 * @param color
 *        The background color setting. Designate this in ARGB format.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetBackground()
 * 
 */
void JginComSetBackground(JGCom component, JKColor color);

/**
 @internal
 *  @internal
 * 
 */
void JginComSetVisible(JGCom component, JKBool visible);

/**
 * Sets the GUI component state.
 * 
 * @param component
 *        The GUI component handle
 * @param state
 *        The state setting. Designate one of the following.
 *     <ul>
 *      <li> #JG_COM_STATE_DISABLED
 *      <li> #JG_COM_STATE_ENABLED
 *      <li> #JG_COM_STATE_FOCUSED
 *      <li> #JG_COM_STATE_ACTIVE
 *     </ul>
 * 
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetState()
 * 
 */
void JginComSetState(JGCom component, JKUint32 state);

/**
 * Sets the GUI component font.
 * 
 * @param component
 *        The GUI component handle
 * @param font
 *        The handle of the font to be set
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When font is  #JK_INVALID_HANDLE</li>
 *   </ul>
 * 
 * @see JgComGetFont()
 */
void JginComSetFont(JGCom component, JKFontHandle font);

/**
 * Sets the horizontal alignment of items inside the GUI component.
 * 
 * @param component
 *        The GUI component handle
 * @param alignment
 *        The alignment method. Designate one of the following.
 *     <ul>
 *      <li> #JG_COM_ALIGN_X_CENTER
 *      <li> #JG_COM_ALIGN_X_LEFT
 *      <li> #JG_COM_ALIGN_X_RIGHT
 *     </ul>
 * 
 * <p>
 * Set the alignment of the items displayed in the GUI component (differs depending 
 * on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetAlignmentX()
 * 
 */
void JginComSetAlignmentX(JGCom component, JKUint32 alignment);

/**
 * Sets the vertical alignment of items inside the GUI component.
 * 
 * @param component
 *        The GUI component handle
 * @param alignment
 *        The alignment method. Designate one of the following.
 *     <ul>
 *      <li> #JG_COM_ALIGN_Y_CENTER
 *      <li> #JG_COM_ALIGN_Y_TOP
 *      <li> #JG_COM_ALIGN_Y_BOTTOM
 *     </ul>
 * 
 * <p>
 * Set the alignment of the items displayed in the GUI component (differs depending 
 * on the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetAlignmentY()
 */
void JginComSetAlignmentY(JGCom component, JKUint32 alignment);

/**
 * Sets the horizontal cutoff position when the GUI component items do not fit 
 * inside the component.
 * 
 * @param component
 *        The GUI component handle
 * @param cutPolicy
 *        The cutoff position. Designate one of the following.
 *     <ul>
 *      <li> #JG_COM_CUT_POLICY_X_RIGHT
 *      <li> #JG_COM_CUT_POLICY_X_LEFT
 *      <li> #JG_COM_CUT_POLICY_X_BOTH
 *     </ul>
 * 
 * <p>
 * Set the cutoff position when items displayed in the GUI component do not fit inside
 * it (differs depending on the the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetCutPolicyX()
 */
void JginComSetCutPolicyX(JGCom component, JKUint32 cutPolicy);

/**
 * Sets the vertical cutoff position when the GUI component items do not fit 
 * inside the component.
 * 
 * @param component
 *        The GUI component handle
 * @param cutPolicy
 *        The cutoff position. Designate one of the following.
 *     <ul>
 *      <li> #JG_COM_CUT_POLICY_Y_BOTTOM
 *      <li> #JG_COM_CUT_POLICY_Y_TOP
 *      <li> #JG_COM_CUT_POLICY_Y_BOTH
 *     </ul>
 * 
 * <p>
 * Set the cutoff position when items displayed in the GUI component do not fit inside
 * it (differs depending on the the type, whether text, image, etc.).
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JgComGetCutPolicyX()
 */
void JginComSetCutPolicyY(JGCom component, JKUint32 cutPolicy);

/**
 * Sets the GUI component preferred size.
 * 
 * @param component
 *        The GUI component handle
 * @param width
 *        The preferred width
 * @param height
 *        The preferred height
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When width or height is a negative value.</li>
 *   </ul>
 * 
 * @see JgComGetPreferredWidth()
 * @see JgComGetPreferredHeight()
 */
void JginComSetPreferredSize(JGCom component, JKSint32 width, JKSint32 height);

/**
 * Sets the GUI component minimum size.
 * 
 * @param component
 *        The GUI component handle
 * @param width
 *        The minimum width
 * @param height
 *        The minimum height
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *    <li>When width or height is a negative value.</li>
 *   </ul>
 * 
 * @see JgComGetMinimumWidth()
 * @see JgComGetMinimumHeight()
 */
void JginComSetMinimumSize(JGCom component, JKSint32 width, JKSint32 height);

/**
 * Sets a GUI component user-defined value.
 * 
 * @param component
 *        The GUI component handle
 * @param userData
 *        The user setting
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComGetUserData()
 */
void JginComSetUserData(JGCom component, JKUint32 userData);

/**
 * Gets the GUI component user-defined values.
 * 
 * @param component
 *        The GUI component handle
 * 
 * @return
 *        The user-defined values are returned, or 0 if none set.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When component is an illegal handle.</li>
 *   </ul>
 * 
 * @see JginComSetUserData()
 */
JKUint32 JginComGetUserData(JGCom component);

/**
 *   Sets the GUI component preferred color.
 *   
 *   @param color The preferred color setting. Designate in ARGB format.
 * 
 *   <b>Note</b> Call this function when the GUI component is created.
 *      This function cannot be used to change the setting while the 
 *      component is active.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When type is an illegal value.</li>
 *   </ul>
 * 
 * @see JgComGetPrefGlobalColor()
 * @see JG_COM_PREF_GLOBAL_COLOR_BACKGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOREGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BACKGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_FOREGROUND
 * @see JG_COM_PREF_GLOBAL_COLOR_BORDER
 * @see JG_COM_PREF_GLOBAL_COLOR_FOCUSED_BORDER
 */
void JginComSetPrefGlobalColor(JKUint32 type, JKColor color);

/**
 *  Sets the truncate mode of the GUI component.
 *
 *   @param component The GUI component handle.
 *   @param truncate Setting this value as following,
 *                   if the string is longer than the width of one line:
 *          <ul>
 *           <li> #JK_TRUE, latter part of the string needs to be truncated
 *                        and shown in one line.</li>
 *           <li> #JK_FALSE, the string needs to be folded
 *                         and shown in multiple lines.</li>
 *          </ul>
 *<p>
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When component is an illegal handle.</li>
 *  </ul>
 */
void JginComSetTruncateMode(JGCom component, JKBool truncate);

/**
 * @if SUPPORT_RTL
 *    Sets the item layout direction of a GUI component.
 *   
 *   @param component   The GUI component handle.
 *   @param orientation The layout direction. Designate one of the following values.
 *          - #JG_COM_ORIENTATION_UNKNOWN
 *          - #JG_COM_ORIENTATION_LTR
 *          - #JG_COM_ORIENTATION_RTL
 *          .
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When component is an illegal handle.</li>
 *     <li>When orientation is an illegal value.</li>
 *   </ul>
 * @see JgComGetOrientation
 *
 * @endif
 */
void JginComSetOrientation(JGCom component, JKUint orientation);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_COMPONENT_H */

