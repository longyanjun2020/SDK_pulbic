/**
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkDevice.h
 * Device Control JSI
 */
/**
 * @addtogroup Device_Control_JSI
 * @{
 *
These API functions are for getting MIDP-specific device information and enabling use of the device features. Using these functions, JBlend can find out the soft key codes assigned to commands such as "OK" and "Cancel" and can control device features such as backlighting and vibration.<br>
Terminology used here is defined as follows.
<dl>
 <dt>command(s) (lower case)<br>
<dd>Actions corresponding to the Command types BACK, CANCEL, EXIT, HELP, OK, and STOP defined in the javax.microedition.lcdui.Command class, and actions for displaying on-screen menus.
 <dt>Command (capitalized)<br>
<dd>A javax.microedition.lcdui.Command class instance. It stores the label, command type, and priority information designated in parameters passed to the constructor.<br>
"Command class" means the javax.microedition.lcdui.Command class. (See the MIDP specifications for details of the Command class.)
 <dt>Soft key<br>
<dd>A button displayed on the screen (soft button).
 <dt>Key code<br>
<dd>A number mapped to a soft key.
This code is designated in the keyCode parameter of the #AmNotifyKeyEvent() function called to notify of key events.
 <dt>Command key<br>
<dd>A soft key to which a command is assigned.<br>
</dl>
The functions defined here must be implemented by the developer when JBlend is incorporated in the native system.
 */

#ifndef ___MIDPSYS_JK_DEVICE_H
#define ___MIDPSYS_JK_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * A structure holding the key codes mapped to command keys.
 *
The #back, #cancel, #help, #exit, #ok and #stop members of this structure correspond to the command types 
BACK, CANCEL, HELP, EXIT, OK and STOP defined for the javax.microedition.lcdui.Command class. 
For each of these command types, assign a soft key and set its key code in the corresponding member of the structure. <br>
Since there are more command types than soft keys, more than one command type will be assigned to each soft key. 
In the #menu member, set the key code of the soft key for menu display. 
This menu is used for displaying and selecting Commands when the Commands registered 
by a Java application cannot be assigned to individual soft keys. <br>
<br>
The number of soft keys must be set in the #numSoftkeys member of the #JKT_Video_Property structure requested 
by #JkVideoGetProperty(), as 0 or above and no more than the physical number of soft keys.<br>
Set the key codes for soft keys as follows in each of the #JKT_Device_CommandKeys structure members based on 
the value in the #numSoftkeys member.
<ul>
<li>When the #numSoftkeys member is 0, set key codes as follows.
<ul>
<li><b>When 0 is set in the #numSoftkeys member because the native system has no soft keys</b><br>
 Be sure to set #AM_KEYCODE_SOFT1 as the #menu member key code. Set -1 for the members other than #menu.<br>
In this case, in order for a Java application to execute a registered Command, 
it must notify a key event designating key code #AM_KEYCODE_SOFT1 in place of soft key 1 when some kind of user operation is performed.<br>
<li><b>When 0 is set in the #numSoftkeys member because the target device is using full-screen mode, 
even though the native system does have soft keys.</b><br>
Even though the soft keys are not displayed, key events must be notified using the same key codes as when they are displayed. 
Set the same key codes in each member as for normal screen mode.
</ul>
<li> When the #numSoftkeys member is 1, set #AM_KEYCODE_SOFT1 as the key code.
<li> When the #numSoftkeys member is 2, use #AM_KEYCODE_SOFT1 and #AM_KEYCODE_SOFT2 as the key codes.
<li> When the #numSoftkeys member is 3, use #AM_KEYCODE_SOFT1, #AM_KEYCODE_SOFT2 and #AM_KEYCODE_SOFT3 as the key codes.
<li> If it is not necessary to map soft keys to particular command types, set -1 as the key code.<br>
</ul>
If the number of Commands registered by the Java application in the Displayable derived class exceeds the number of soft keys, 
JBlend uses as a menu display key the soft key assigned to the #menu member. 
Soft keys other than the menu display key are assigned to Commands based on the assignments set in this structure 
and on the Command priorities registered by the Java application. 
The highest priority Commands are assigned directly to soft keys, while the rest are selected from the menu display. <br>
<br>
This structure is designated as an argument of #JkDeviceGetCommandKeys().<br>
 */
typedef struct JKT_Device_CommandKeys {
   /**
    *  The key code for the soft key corresponding to "BACK"
    */
    JKSint32 back;
   /**
    *  The key code for the soft key corresponding to "CANCEL"
    */
    JKSint32 cancel;
   /**
    *  The key code for the soft key corresponding to "HELP"
    */
    JKSint32 help;
   /**
    *  The key code for the soft key corresponding to "EXIT"
    */
    JKSint32 exit;
   /**
    *  The key code for the soft key corresponding to "OK"
    */
    JKSint32 ok;
   /**
    *  The key code for the soft key corresponding to "STOP"
    */
    JKSint32 stop;
   /**
    *  The key code for the soft key corresponding to "Menu"
    */
    JKSint32 menu;


} JKT_Device_CommandKeys;

/**
 * Gets key code information for command keys.
 *
 * @param *commandkeys A pointer to the #JKT_Device_CommandKeys structure
 *                     for storing command key information.
 *
 * When this function is called, put the #JKT_Device_CommandKeys structure
 * information in the designated memory location.
 *
 */
void JkDeviceGetCommandKeys( JKT_Device_CommandKeys *commandkeys );

/**
 *  Game action type A.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class GAME_A field.
 */
#define JK_DEVICE_GAME_ACTION_GAME_A        9

/**
 *  Game action type B.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class GAME_B field.
 */
#define JK_DEVICE_GAME_ACTION_GAME_B        10

/**
 *  Game action type C.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class GAME_C field.
 */
#define JK_DEVICE_GAME_ACTION_GAME_C        11

/**
 *  Game action type D.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class GAME_D field.
 */
#define JK_DEVICE_GAME_ACTION_GAME_D        12

/**
 *  Game action type UP.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class UP field.
 */
#define JK_DEVICE_GAME_ACTION_UP            1

/**
 *  Game action type LEFT.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class LEFT field.
 */
#define JK_DEVICE_GAME_ACTION_LEFT          2

/**
 *  Game action type DOWN.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class DOWN field.
 */
#define JK_DEVICE_GAME_ACTION_DOWN          6

/**
 *  Game action type RIGHT.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class RIGHT field.
 */
#define JK_DEVICE_GAME_ACTION_RIGHT         5

/**
 *  Game action type FIRE.\ This type corresponds to that of the javax.microedition.lcdui.Canvas class FIRE field.
 */
#define JK_DEVICE_GAME_ACTION_FIRE          8

/**
 *  A structure mapping game actions to key codes.
 *
 *  This information is used by the getGameAction() method and getKeyCode() method in javax.microedition.lcdui.Canvas class.
 *  Each of the game actions below must be mapped to a member of this structure.
 *  <ul>
 *   <li> #JK_DEVICE_GAME_ACTION_GAME_A
 *   <li> #JK_DEVICE_GAME_ACTION_GAME_B
 *   <li> #JK_DEVICE_GAME_ACTION_GAME_C
 *   <li> #JK_DEVICE_GAME_ACTION_GAME_D
 *   <li> #JK_DEVICE_GAME_ACTION_UP
 *   <li> #JK_DEVICE_GAME_ACTION_LEFT
 *   <li> #JK_DEVICE_GAME_ACTION_DOWN
 *   <li> #JK_DEVICE_GAME_ACTION_RIGHT
 *   <li> #JK_DEVICE_GAME_ACTION_FIRE
 *  </ul>
 *  One game action may be mapped to more than one member of this structure.<br>
 *  A key code that is not mapped to any game action must have value 0.<br>
 *<br>
 *  This structure is designated as an argument of #JkDeviceGetGameAction().
 */
typedef struct JKT_Device_GameAction {
    /**
     *  The game action mapped to the 0 key.
     */
    JKSint32 key_num0;

    /**
     *  The game action mapped to the 1 key.
     */
    JKSint32 key_num1;

    /**
     *  The game action mapped to the 2 key.
     */
    JKSint32 key_num2;

    /**
     *  The game action mapped to the 3 key.
     */
    JKSint32 key_num3;

    /**
     *  The game action mapped to the 4 key.
     */
    JKSint32 key_num4;

    /**
     *  The game action mapped to the 5 key.
     */
    JKSint32 key_num5;

    /**
     *  The game action mapped to the 6 key.
     */
    JKSint32 key_num6;

    /**
     *  The game action mapped to the 7 key.
     */
    JKSint32 key_num7;

    /**
     *  The game action mapped to the 8 key.
     */
    JKSint32 key_num8;

    /**
     *  The game action mapped to the 9 key.
     */
    JKSint32 key_num9;

    /**
     *  The game action mapped to the asterisk (*) key.
     */
    JKSint32 key_asterisk;

    /**
     *  The game action mapped to the pound (#) key.
     */
    JKSint32 key_pound;

    /**
     *  The game action mapped to the Left key.
     */
    JKSint32 key_left;

    /**
     *  The game action mapped to the Up key.
     */
    JKSint32 key_up;

    /**
     *  The game action mapped to the Right key.
     */
    JKSint32 key_right;

    /**
     *  The game action mapped to the Down key.
     */
    JKSint32 key_down;

    /**
     *  The game action mapped to the Select key.
     */
    JKSint32 key_select;
} JKT_Device_GameAction;

/**
 * Gets game action information for key codes.
 *
 * @param *gameAction A pointer to the #JKT_Device_GameAction structure
 *                    for storing game action information.
 *
 * When this function is called, put the #JKT_Device_GameAction structure
 * information in the designated memory location.
 */
void JkDeviceGetGameAction( JKT_Device_GameAction *gameAction );

/**
 *  An alarm type sound.\ This type corresponds to that of the javax.microedition.lcdui.AlertType class ALARM field.
 */
#define JK_DEVICE_ALERT_TYPE_ALARM          0

/**
 *  A confirmation type sound.\ This type corresponds to that of the javax.microedition.lcdui.AlertType class CONFIRMATION field.
 */
#define JK_DEVICE_ALERT_TYPE_CONFIRM        1

/**
 *  An error beep type sound.\ This type corresponds to that of the javax.microedition.lcdui.AlertType class ERROR field.
 */
#define JK_DEVICE_ALERT_TYPE_ERROR          2

/**
 *  An infomational type sound.\ This type corresponds to that of the javax.microedition.lcdui.AlertType class INFO field.
 */
#define JK_DEVICE_ALERT_TYPE_INFO           3

/**
 *  A warning type sound.\ This type corresponds to that of the javax.microedition.lcdui.AlertType class WARNING field.
 */
#define JK_DEVICE_ALERT_TYPE_WARNING        4

/**
 *  Alerts the user by playing a sound.
 *
 * @param alertType The type of sound used to alert the user.<br>
 *                  One of the following is designated.
 *                  <ul>
 *                   <li> #JK_DEVICE_ALERT_TYPE_ALARM
 *                   <li> #JK_DEVICE_ALERT_TYPE_CONFIRM
 *                   <li> #JK_DEVICE_ALERT_TYPE_ERROR
 *                   <li> #JK_DEVICE_ALERT_TYPE_INFO
 *                   <li> #JK_DEVICE_ALERT_TYPE_WARNING
 *                  </ul>
 * @return Return #JK_TRUE if the operation succeeds.<br>
 *         In case of failure, (e.g. sound support is lacking or
 *         the sound resource is in use, etc) return #JK_FALSE.
 *
 * Play the designated sound.<br>
 * This function corresponds to the javax.microedition.lcdui.AlertType
 * class playSound() method.
 */
JKBool JkDeviceAlertBySound( JKSint32 alertType );

/**
 *  Terminates the alert sound.
 *
 * Stop the alert sound started by JkDeviceAlertBySound().
 * If the sound is not playing when this function is called, 
 * exit this function without doing anything. 
 */
void JkDeviceStopAlertSound( void );

/**
 * Starts backlight flashing.
 *
 * @param duration The duration (in milliseconds) of backlight flashing
 * @return  Return #JK_TRUE if the operation succeeds.<br>
 *          If backlight support is lacking or the control failed, return
 *          #JK_FALSE.
 *
 * Flash the backlight for the designated duration. 
 * The blink cycle (durations of on and off periods) is implementation-dependent.
 * 
 * If this function is called while the backlight is flashing, cancel the previous
 * flashing duration designation and flash for the newly designated duration,
 * starting from the instant this function was called.<br>
 * Enable the flashing to be stopped forcibly when #JkDeviceStopBacklightFlash() is
 * called.
 * 
 * This function is called when the flash duration is designated as a parameter in
 * the javax.microedition.lcdui.Display class flashBacklight() method.
 *
 *
 * @see JkDeviceStopBacklightFlash()
 */
JKBool JkDeviceStartBacklightFlash( JKSint32 duration );

/**
 * Stops backlight flashing.
 *
 * @return  Return #JK_TRUE if the operation succeeds.<br>
 *          If backlight support is lacking or the control failed, return
 *          #JK_FALSE.
 *
 * Stop the backlight flashing. <br>
 * If this function is called when #JkDeviceStartBacklightFlash() has not been called
 * or the duration designated in #JkDeviceStartBacklightFlash() has elapsed, return
 * #JK_FALSE without performing any operation.<br>
 * This function is called when 0 was designated in a parameter of the javax.microedition.lcdui.Display class
 * flashBacklight() method.
 *
 */
JKBool JkDeviceStopBacklightFlash( void );

/**
 * Starts vibration.
 *
 * @param duration The duration of the vibration (in milliseconds)
 * @return  Return #JK_TRUE if the operation succeeds.<br>
 *          If vibration support is lacking or the control failed, return
 *          #JK_FALSE.
 *
 * Vibrate the target device for the designated duration.<br>
 * If this function is called while the target device is vibrating, cancel the previous
 * duration designation and vibrate for the newly designated duration, starting
 * from the instant this function was called.<br>
 * Enable vibration to be stopped forcibly when #JkDeviceStopVibration() is called.<br>
 * This function is called when the vibration duration is designated in a parameter of
 * the javax.microedition.lcdui.Display class vibrate() method.
 *
 *
 * @see JkDeviceStopBacklightFlash()
 */
JKBool JkDeviceStartVibration( JKSint32 duration );

/**
 * Stops vibration.
 *
 * @return  Return #JK_TRUE if the operation succeeds.<br>
 *          If vibration support is lacking or the control failed, return
 *          #JK_FALSE.
 *
 * Stop the target device vibration.<br>
 * If this function is called when #JkDeviceStartVibration() has not been called
 * or the duration designated in #JkDeviceStartVibration() has elapsed, return
 * #JK_FALSE without performing any operation.<br>
 * This function is called when 0 was designated in a parameter of the javax.microedition.lcdui.Display class
 * vibrate() method.
 */
JKBool JkDeviceStopVibration( void );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
