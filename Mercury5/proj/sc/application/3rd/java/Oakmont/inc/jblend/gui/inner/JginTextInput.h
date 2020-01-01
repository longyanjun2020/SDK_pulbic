/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Functions for modifying text input component properties.
 */

#ifndef ___GUI_INNER_TEXTINPUT_H
#define ___GUI_INNER_TEXTINPUT_H

#include <JkTypes.h>

#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>
#include <gui/common/JgTextInput.h>
#include <gui/inner/JginKeyEvent.h>
#include <gui/inner/JginPointerEvent.h>
#include <gui/inner/JginCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_TextInput
 * @{
 */

/**
 * Text was set in the text input component.
 *
 * When this event is processed by the event handler defined as
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 * structure passed to the event handler by JBlend are indicated in the
 * following parameters. The event handler return value should be as indicated
 * below.
 *
 * @param param1
 *         #JGString The text that was set
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
#define JG_TXT_EVT_TEXT_CHANGED         (JG_COM_EVT_END + 0x01)

/**
 * The maximum number of characters for the text input component was changed.
 *
 * When this event is processed by the event handler defined as
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 * structure passed to the event handler by JBlend are indicated in the
 * following parameters. The event handler return value should be as indicated
 * below.
 *
 * @param param1
 *        JKSint32 The current maximum number of characters
 * @param param2
 *        JKSint32 The previous setting
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
#define JG_TXT_EVT_MAX_SIZE_CHANGED     (JG_COM_EVT_END + 0x02)

/**
 * The text input component acceptable character type changed.
 *
 * When this event is processed by the event handler defined as
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 * structure passed to the event handler by JBlend are indicated in the
 * following parameters. The event handler return value should be as indicated
 * below.
 *
 * @param param1
 *              JKUint32 The current acceptable character type setting
 * @param param2
 *              JKUint32 The previous acceptable character type setting
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
#define JG_TXT_EVT_CONSTRAINTS_CHANGED  (JG_COM_EVT_END + 0x03)

/**
 * The input mode of the text input component changed.
 *
 * When this event is processed by the event handler defined as
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 * structure passed to the event handler by JBlend are indicated in the
 * following parameters. The event handler return value should be as indicated
 * below.
 *
 * @param param1
 *              #JGString The current input mode
 * @param param2 -
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
#define JG_TXT_EVT_INPUTMODE_TEXT_CHANGED   (JG_COM_EVT_END + 0x04)

/**
 * The editable mode of the text input component changed.
 *
 * When this event is processed by the event handler defined as
 * #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 * structure passed to the event handler by JBlend are indicated in the
 * following parameters. The event handler return value should be as indicated
 * below.
 *
 * @param param1
 *              JKBool The current editable mode
 * @param param2
 *              JKBool The previous editable mode
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
#define JG_TXT_EVT_EDITABLED_CHANGED    (JG_COM_EVT_END + 0x05)

/**
 *   The text input component password mode changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 JKBool
 *               The newly set password mode
 *   @param param2 JKBool
 *               The previous password mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_PASSWORD_MODE_CHANGED    (JG_COM_EVT_END + 0x06)

/**
 *   The text input component sensitive mode changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 JKBool The newly set sensitive mode
 *   @param param2 JKBool The previous mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_SENSITIVE_MODE_CHANGED   (JG_COM_EVT_END + 0x07)

/**
 *   The text input component predictive mode changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 JKBool The newly set predictive mode
 *   @param param2 JKBool The previous mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_PREDICTIVE_MODE_CHANGED  (JG_COM_EVT_END + 0x08)

/**
 *   The text input component capitalization mode changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 JKUint32 The newly set capitalization mode
 *   @param param2 JKUint32 The previous mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 *
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_CAPITAL_MODE_CHANGED     (JG_COM_EVT_END + 0x09)

/**
 *   The text input component linebreak allowed mode changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 JKBool The newly set linebreak allowed mode
 *   @param param2 JKBool The previous mode
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_ALLOWED_LINEBREAK_CHANGED    (JG_COM_EVT_END + 0x0a)

/**
 * The text input component title was changed.
 *
 *   When this event is processed by the event handler defined as
 *   #JGT_ComEvtHandler type, the values of the param members in the JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the
 *   following parameters. The event handler return value should be as indicated
 *   below.
 *
 *   @param param1 #JGString The text input component title
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * @see JGT_ComEvent::type
 */
#define JG_TXT_EVT_TITLE_TEXT_CHANGED           (JG_COM_EVT_END + 0x0b)


/**
 * @internal
 * The maximum valid component event value for the text input component.
 */
#define JG_TXT_EVT_END                  (JG_COM_EVT_END + 0x0c)

/**
 * Sets a text string in the text input component.
 *
 * @param textinput
 *        The text input component handle
 * @param text
 *        The character string to be set
 * @param length
 *        The number of elements in the character string (not the byte size)
 *
 * @return
 *         If the setting succeeded, 0 is returned; if short of memory, -1 is returned.
 *
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *    <li>When length is a negative value.</li>
 *    <li>When text is  #JK_NULL and length is not 0.</li>
 *   </ul>
 */
JKSint32 JginTextInputSetText(JGTextInput textinput, const JKWChar text[], JKSint32 length);

/**
 * Updates the current input position in the text input component.
 *
 * @param textinput
 *        The text input component handle
 * @param caretPosition
 *        The current input position
 *
 * @see JgTextInputGetCaretPosition()
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
void JginTextInputSetCaretPosition(JGTextInput textinput, JKSint32 caretPosition);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_TEXTINPUT_H */

