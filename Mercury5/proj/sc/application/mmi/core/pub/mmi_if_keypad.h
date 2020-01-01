/**
 * @file    mmi_if_keypad.h
 * @brief   The document describes the event dispatcher of keypad related signals
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id: mmi_if_keypad.h 28768 2009-04-17 08:19:25Z william.lien $
 */
#ifndef __MMI_IF_KEYPAD_H__
#define __MMI_IF_KEYPAD_H__

#include "mmi_if_def.h"
#include "mmi_mae_forward.h"

/*  Definitions */
#define MMI_KEYPAD_LONGPRESS_DURATION   900
#define MMI_KEYPAD_REPEAT_DURATION  500

/**
 * \fn      : mmi_kbd_data_if
 * \brief   : Parse keypad related signal and post event to kernel.
 * \param   : Message from RTK
 * \return  : None
 */
void mmi_kbd_data_if(IBASE *pRecipient, struct vm_msg *pMessage);

/**
 * \fn      : mmi_kbd_timer_expired
 * \brief   : Keypad manager would trigger two timers once key pressed. One is MMI_KEYPAD_REPEAT_TIMER and the other is MMI_KEYPAD_LONGPRESS_TIMER.
 *			  After this timer expired, it would post MAE_EVT_KEY_REPEAT. The duration of this timer is defined by MMI_KEYPAD_LONGPRESS_DURATION.
 * \return  : None

		vKey Parser         MMI Mae                 AP
            |   Key 1 pressed   |                   |
            |------------------>|  EVT_KEY_PRESS    |
            |                   |------------------>|
            |                   |  EVT_KEY_REPEAT   |
            |                   |------------------>|
            |                   |  EVT_KEY_REPEAT   |
            |                   |------------------>|
            |                   |                   |
            |                   |                   |
            |   Key 1 released  |                   |
            |------------------>|  EVT_KEY_RELEASE  |
            |                   |------------------>|
*/

void mmi_kbd_repeat_timer_expired(void *userdata);

/**
 * @fn      : mmi_kbd_longpress_timer_expired
 * @brief   : After this timer MMI_KEYPAD_LONGPRESS_TIMER expired, it would post MAE_EVT_KEY_REPEAT.
 *            The duration of this timer is defined by MMI_KEYPAD_LONGPRESS_DURATION.
 * @return  : None

		vKey Parser         MMI Mae                 AP
            |   Key 1 pressed   |                   |
            |------------------>|  EVT_KEY_PRESS    |
            |                   |------------------>|
            |                   |                   |
            |                   |                   |  
            |                   |  EVT_KEY_LONG     |
            |                   |------------------>|
            |                   |                   |
            |                   |                   |
            |   Key 1 relesaed  |                   |
            |------------------>|  EVT_KEY_RELEASE  |
            |                   |------------------>|
*/

void mmi_kbd_longpress_timer_expired(void *userdata);

boolean mmi_kbd_coresrv_hook_msg_parser(IBASE *pRecipient, struct vm_msg *pMessage);

void mmi_kbd_stksrv_hook_msg_parser(IBASE *pRecipient, struct vm_msg *pMessage);

/**
 * @fn      : mmi_kbd_ccapp_hook_msg_parser
 * @brief   : Request from CCAPP, it may register keypad message when it interrupted by other AP , ex: PHB, SMS, Notepad.
 *            CCAPP needs to receive HOOK key event to end call.
 *
 * @return  : None
*/
void mmi_kbd_ccapp_hook_msg_parser(IBASE *pRecipient, struct vm_msg *pMessage);


/**
 * @fn      : mmi_kbd_queryNumPressed
 * @brief   : Request from coresrv, it needs to  query number of key pressed to disable backlight off
 *              if there are key pressed.
 * @return  : Number of key pressed.
*/

u16 mmi_kbd_queryNumPressed(void);

/**
 * @fn      : mmi_kbd_reset
 * @brief   : Request from vendor srv, 3rd party may register keypad message, so MMI won't receive it any more.
 *               It may lead to unpaired kaypad state in MMI, and produce unexpected key repeated event.
 *             
 * @return  : None
*/


void mmi_kbd_resetCtxt(void);

#endif /* __MMI_IF_KEYPAD_H__ */

