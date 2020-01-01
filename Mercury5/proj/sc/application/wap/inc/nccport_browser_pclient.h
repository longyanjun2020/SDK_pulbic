
/**
 * @file
 * esmp client Porting Layer
 *
 * Basic support functions that are needed by esmp client.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_pclient Interface
 * - NCCPort_brwpclient_msgState()
 * - NCCPort_brwpclient_alert()
 * - NCCPort_brwpclient_confirm()
 * - NCCPort_brwpclient_prompt()
 * - NCCPort_brwpclient_promptNum()
 * - NCCPort_brwpclient_back()
 * - NCCPort_brwpclient_forward()
 * - NCCPort_brwpclient_go()
 * - NCCPort_brwpclient_loseFocus()
 * - NCCPort_brwpclient_focus()
 * - NCCPort_brwpclient_submit()
 * - NCCPort_brwpclient_reset()
 * - NCCPort_brwpclient_doTimeout()
 * - NCCPort_brwpclient_setTimeout()
 * - NCCPort_brwpclient_clearTimeout()
 * - NCCPort_brwpclient_clearAllTimeout()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_PCLIENT_H__
#define __NCCPORT_BROWSER_PCLIENT_H__

#include <ncc_types.h>
#include <wap_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/** script code param type when set timeout */
#define CJS_STRING_FLAG     0
/** function ref param type when set timeout */
#define CJS_FUNCTION_FLAG   1
/** invalid param type when set timeout */
#define CJS_INVALID_FLAG    -1

/**
  * Get block state of window, because all of the interfaces defined in this file
  * need be block interfaces.
  * \return  boolean flag<ul>
  *          <li>TRUE: blocked message</li>
  *          <li>FALSE: non-blocked message</li>
  *          </ul>
  * \attention maybe no use for some platform
  */
int32_t NCCPort_brwpclient_msgState(void);

/**
 * displays the given message to the user, and waits for user
 * confirmation of the message.
 * This method is modal, and blocks waiting for a response.
 * \param   message to display to user
 */
void NCCPort_brwpclient_alert(uint8_t *message);

/**
 * displays message and waits for user to select positive or negative
 * selection choice.
 * It is modal, and blocks waiting for a response.
 * \param   message the information to alert
 * \param   leftButton the value of left ok button
 * \param   rightButton the value of right ok button
 * \return  selection choice<ul>
 *           <li>TRUE: Confirm</li>
 *           <li>FALSE: Cancel</li>
 *           </ul>
 */
int32_t NCCPort_brwpclient_confirm(uint8_t * message, uint8_t* leftButton, uint8_t* rightButton);

/**
 * displays the given message as a dialog and prompts for user input.
 * If the user does not enter a reply, the defaultReply is returned as
 * the user input string. If the user replies, the user reply is returned.
 * This interface is modal, and blocks waiting for a response.
 * \param   message string to be used as a prompt.
 * \param   defstr  string that will be returned if there is no input.
 *                  it can be NULL.
 * \param   length  max length of text buffer
 * \return  whether input any value<ul>
 *           <li>TRUE: Confirm</li>
 *           <li>FALSE: Cancel</li>
 *           </ul>
 */
int32_t NCCPort_brwpclient_prompt(uint8_t *message, uint8_t *defstr, int32_t length);

/**
 * displays the given message as a dialog and prompts for user input.
 * If the user does not enter a reply, the defaultReply is returned as
 * the user input string. If the user replies, the user reply is returned.
 * This interface is modal, and blocks waiting for a response.
 * \param   message message string to be used as a prompt.
 * \param   num     the pointer of number, permit default data
 * \return  whether input any integer value<ul>
 *           <li>TRUE: Confirm</li>
 *           <li>FALSE: Cancel</li>
 *           </ul>
 * \attention the input is used to input number value
 */
int32_t NCCPort_brwpclient_promptNum(uint8_t *message, int32_t *num);

/**
 * executes a browser "navigate to history entry" to the previous entry in the
 * history list (if there is one).
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_back(void);

/**
 * executes a browser "navigate to history entry" to the next entry in the
 * history list (if there is one).
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_forward(void);

/**
 * Requests the browser to navigate to a URL using the indexed entry in the history list.
 * Note: A history.go(0) is NOT the same as a location.reload().
 * history.go(0) is more "gentle", preserving the state of all form variables
 * whenever possible.
 * \param   step a number(integer) which is the index to an ordered list of history entries.
 *               0 (zero) is the index to the current entry.
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_go(int32_t step);

/**
 * removes focus from the field. (text, password, textarea, button)
 * \param   sysid   system id  of a control
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_loseFocus(int32_t sysid);

/**
 * sets the input focus to the referenced input element.
 * (text, password, textarea, button)
 * \param sysid system id of a control
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_focus(int32_t sysid);

/**
 * initiates form content submission to the server according to form id
 * \param formid form id of a form
 * \attention This function must be implement if ECMASCRIPT is used.
 */
int32_t NCCPort_brwpclient_submit(int32_t formid);

/**
 * returns all referenced form elements to their default according to form.
 *  settings
 * \param   formid  form id of a form
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_reset(int32_t formid);

/**
 * execute script function when their timer arrive.
 * if it is implemented through real timer,
 * this interface is not necessary to implement.
 * just define it as a void macro.
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_doTimeout(void);

/**
 * specifies the duration to wait before calling the requested function.
 * It acts as if a delay function were inserted at the end of the currently
 * executing function.
 * \param   firstMilliSecs  represents first duration of the timeout
 *                          as specified in milliseconds
 * \param   intervalMilliSecs represents next duration of the timeout
 *                            as specified in milliseconds
 * \param   flag    type of function
 * \param   func    function ref or script code pointer
 * \param   argc    count of params
 * \param   argv    params array
 * \param   obj     scope object to execute script
 * \return  ID of timer
 * \attention This function must be implement if ECMASCRIPT is used.
 */
int32_t NCCPort_brwpclient_setTimeout(int32_t firstMilliSecs
                            ,int32_t intervalMilliSecs
                            ,int32_t flag
                            ,void *func
                            ,uint32_t argc
                            ,int32_t *argv,
                            void *obj);

/**
 * unset and clear an existing timeout
 * \param   timerid     ID of timer
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_clearTimeout(int32_t timerid);

/**
 * clear all timer
 * \param   none
 * \attention This function must be implement if ECMASCRIPT is used.
 */
void NCCPort_brwpclient_clearAllTimeout(void);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPORT_BROWSER_JS_H__ */
