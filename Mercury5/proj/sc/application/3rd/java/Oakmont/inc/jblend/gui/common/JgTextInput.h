/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying text input component properties.
 */

#ifndef ___GUI_COMMON_TEXTINPUT_H
#define ___GUI_COMMON_TEXTINPUT_H

#include <JkTypes.h>

#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgString.h>
#include <gui/common/JgCom.h>

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
 * If a character string is set, notify the event using #JginGUIEventPostEvent().
 * The values of the param members in the JGT_GUIEvent structure passed as an
 * argument of JginGUIEventPostEvent() are as indicated in the following
 * parameters.
 *
 * @param param1
 *        #JGString The text that was set
 * @param param2 -
 * @param param3 -
 * @param param4 -
 *
 * @see JGT_GUIEvent::type
 */
#define JG_GUI_TXT_EVT_TEXT_CHANGED     (JG_GUI_EVT_END + 0x01)

/**
 * @internal
 * The maximum GUI text input component event value.
 */
#define JG_GUI_TXT_EVT_END              (JG_GUI_EVT_END + 0x01)

/**
 * The text input component handle
 *
 * A text input handle is data identifying the text input component.<br>
 * The text input handle can be used as a component handle.
 *
 * @see JGCom
 */
typedef JGCom       JGTextInput;

/**
 * Acceptable character types: All (default)
 */
#define JG_TXT_CONSTRAINTS_ANY          0x00000000

/**
 * Acceptable character type: Email address
 */
#define JG_TXT_CONSTRAINTS_EMAILADDR    0x00000001

/**
 * Acceptable character type: Numerals
 */
#define JG_TXT_CONSTRAINTS_NUMERIC      0x00000002

/**
 * Acceptable character type: Telephone numbers
 */
#define JG_TXT_CONSTRAINTS_PHONENUMBER  0x00000003

/**
 * Acceptable character type: URL
 */
#define JG_TXT_CONSTRAINTS_URL          0x00000004

/**
 * Acceptable character type: Numerals and symbols
 */
#define JG_TXT_CONSTRAINTS_DECIMAL      0x00000005



/**
 * Capitalization mode: Undefined (default)
 */
#define JG_TXT_CAPS_UNDEFINE            0x00000000

/**
 * Capitalization mode: First letter of word
 */
#define JG_TXT_CAPS_WORD                0x00000001

/**
 * Capitalization mode: First letter of sentence
 */
#define JG_TXT_CAPS_SENTENCE            0x00000002


/**
 * Gets the text in the text input component.
 *
 * @param textinput
 *        The text input component handle
 *
 * @return
 *         A handle is returned indicating a string with the text. If none is
 *         set,  #JK_INVALID_HANDLE is returned.
 *
 * The text string obtained must not be discarded. The GUI Toolkit takes care of that.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JGString JgTextInputGetText(JGTextInput textinput);

/**
 * Gets the maximum number of characters that can be set in the text input component.
 *
 * @param textinput
 *        The text input component handle
 *
 * @return
 *        The maximum number of characters is returned.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgTextInputGetMaxSize(JGTextInput textinput);

/**
 * Gets the character types acceptable in the text input component.
 *
 * @param textinput
 *        The text input component handle
 * @return
 *         One of following values is returned as acceptable character types.
 *     <br><br>
 *     <ul>
 *      <li> #JG_TXT_CONSTRAINTS_ANY
 *      <li> #JG_TXT_CONSTRAINTS_EMAILADDR
 *      <li> #JG_TXT_CONSTRAINTS_NUMERIC
 *      <li> #JG_TXT_CONSTRAINTS_PHONENUMBER
 *      <li> #JG_TXT_CONSTRAINTS_URL
 *      <li> #JG_TXT_CONSTRAINTS_DECIMAL
 *     </ul>
 *
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgTextInputGetConstraints(JGTextInput textinput);


/**
 *          Gets the character string representing the initial input mode.
 *
 *   @param textinput 
 *          The text input component handle.
 *   @return 
 *          A character string representing the initial input mode is returned.
 *          If no input mode is set yet, #JK_INVALID_HANDLE is returned.
 *
 *   This function gets the string representing the input mode initially set for the text input 
 *   component. 
 *     The input mode returned by this function indicates the string 
 *     representing the initial input mode set by 
 *     the <code>javax.microedition.lcdui.TextBox</code> class <code>setInitialInputMode</code> method
 *     or the <code>javax.microedition.lcdui.TextField</code> class <code>setInitialInputMode</code> method.
 *     For detail of input mode string, see specifications issued by Sun Microsystems, Inc.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JGString JgTextInputGetInputModeText(JGTextInput textinput);

/**
 *  Gets the title string of the text input component.
 * 
 *  @param textinput The text input component handle
 *  @return The title string is returned, or #JK_INVALID_HANDLE if none was set.
 *
 *  This function returns the title string of the text input component.
 *
 *    The string this function returns corresponds to 
 *    the label of javax.microedition.lcdui.TextField class or
 *    the title of javax.microedition.lcdui.TextBox class.
 *
 *  In the following case @ref page_gui_trouble_shooting "Error" results.
 *  <ul>
 *   <li>When textinput is an illegal handle.</li>
 *  </ul>
 */
JGString JgTextInputGetTitleText(JGTextInput textinput);

/**
 * Gets the current input position in the text input component.
 *
 * @param textinput
 *        The text input component handle
 * @return
 *         The current input position is returned.
 *
 * @see JginTextInputSetCaretPosition()
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgTextInputGetCaretPosition(JGTextInput textinput);

/**
 * Gets the editable state of the text input component.
 *
 * @param textinput
 *        The text input component handle
 * @return
 *         #JK_TRUE is returned if the text input component is editable, else #JK_FALSE.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKBool JgTextInputIsEditable(JGTextInput textinput);

/**
 *   Gets whether password mode is set for the text input component.
 *
 *   @param textinput
 *        The text input component handle
 *   @return
 *        #JK_TRUE is returned for password mode, else #JK_FALSE.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKBool JgTextInputIsPassword(JGTextInput textinput);

/**
 *   Gets whether sensitive mode is set for the text input component.
 *
 *   @param textinput
 *        The text input component handle
 *   @return
 *        #JK_TRUE is returned for sensitive mode, else #JK_FALSE.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKBool JgTextInputIsSensitive(JGTextInput textinput);

/**
 *   Gets whether predictive mode is set for the text input component.
 *
 *   @param textinput
 *        The text input component handle
 *   @return
 *        #JK_TRUE is returned for predictive mode, else #JK_FALSE.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKBool JgTextInputIsPredictive(JGTextInput textinput);

/**
 *   Gets the capitalization mode set for the text input component.
 *
 *   @param textinput
 *        The text input component handle
 *   @return
 *        One of the following values is returned indicating capitalization mode.
 * <br><br>
 * <ul>
 *  <li> #JG_TXT_CAPS_UNDEFINE
 *  <li> #JG_TXT_CAPS_WORD
 *  <li> #JG_TXT_CAPS_SENTENCE
 * </ul>
 *
 * <p>
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When textinput is an illegal handle.</li>
 *   </ul>
 */
JKUint32 JgTextInputGetCapitalMode(JGTextInput textinput);

/**
 *   Gets whether linebreak is allowed in the text input component.
 *
 *   @param textinput
 *        The text input component handle
 *   @return
 *        #JK_TRUE is returned if linebreak is allowed, else #JK_FALSE.
 */
JKBool JgTextInputIsAllowedLineBreak(JGTextInput textinput);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_TEXTINPUT_H */

