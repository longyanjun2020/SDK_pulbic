/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_SYS_DEVICE_HEADER
#define KJAVA_SYS_DEVICE_HEADER

/**
 * @file kjava_sys_device.h
 * Device Control KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup device_control_ksi
 *  @{
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup Device_Control_Alarm_Sound Alarm Sound Control KSI
 * An interface for controlling the native alarm sound.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread. 
 *
 * @par Include file 
 * \#include kjava_sys_device.h
 * @{
 */

/**
 *  An alarm type sound.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.AlertType.ALARM</i> field.
 */
#define KJAVA_DEVICE_ALERT_TYPE_ALARM          0

/**
 *  A confirmation type sound.
 *
 *  This type corresponds to that of the
 *  <i>javax.microedition.lcdui.AlertType.CONFIRMATION</i> field.
 */
#define KJAVA_DEVICE_ALERT_TYPE_CONFIRM        1

/**
 *  An error beep type sound.
 *
 *  This type corresponds to that of the
 *  <i>javax.microedition.lcdui.AlertType.ERROR</i> field.
 */
#define KJAVA_DEVICE_ALERT_TYPE_ERROR          2

/**
 *  An informational type sound.
 *
 *  This type corresponds to that of the
 *  <i>javax.microedition.lcdui.AlertType.INFO</i> field.
 */
#define KJAVA_DEVICE_ALERT_TYPE_INFO           3

/**
 *  A warning type sound.
 *
 *  This type corresponds to that of the
 *  <i>javax.microedition.lcdui.AlertType.WARNING</i> field.
 */
#define KJAVA_DEVICE_ALERT_TYPE_WARNING        4

/** @} */

/**
 * @addtogroup Device_Control_Command_Key_Mapping Command Key Mapping KSI
 * An interface for retrieving command key mapping.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread. 
 *
 * @par Include file 
 * \#include kjava_sys_device.h
 * @{
 */

/**
 * Structure holding the key code for different function keys.
 * This structure type is used for passing command-key mapping via a parameter to kjava_device_getCommandKey().
 *
 * The {@link KJavaDeviceCommandKeys#back back}, {@link KJavaDeviceCommandKeys#cancel cancel},
 * {@link KJavaDeviceCommandKeys#help help}, {@link KJavaDeviceCommandKeys#exit exit}, {@link KJavaDeviceCommandKeys#ok ok} and
 * {@link KJavaDeviceCommandKeys#stop stop} members of this structure correspond to the command types
 * <code>BACK</code>, <code>CANCEL</code>, <code>HELP</code>, <code>EXIT</code>, <code>OK</code> and <code>STOP</code> defined for the
 * <code>javax.microedition.lcdui.Command</code> class.
 * For each of these command types, assign a soft key and set its key code in the corresponding member of the structure.
 *
 * Since there are more command types than soft keys, more than one command type will be assigned to each soft key.
 * In the {@link KJavaDeviceCommandKeys#menu menu} member, set the key code of the soft key for menu display.
 * This menu is used for displaying and selecting <code>Command</code>s when the <code>Command</code>s
 * registered by a Java application cannot be assigned to individual soft keys.
 *
 * The number of soft keys must be set in the {@link KJavaGfxInfo#numSoftkeys numSoftkeys} member of the #KJavaGfxInfo structure
 * requested by kjava_gfx_getInfo(), as 0 or above and no more than the physical number of soft keys.
 * Set the key codes for soft keys as follows in each of the KJavaDeviceCommandKeys structure members based on the value in the
 * {@link KJavaGfxInfo#numSoftkeys numSoftkeys} member.
 *
 * - When the numSoftkeys member is 0, set key codes as follows.
 *   - <b>When 0 is set in {@link KJavaGfxInfo#numSoftkeys KJavaGfxInfo#numSoftkeys} because the native system has no soft keys</b><br>
 *     Be sure to set #AJSC_KEYCODE_SOFT1 as the {@link KJavaDeviceCommandKeys#menu menu} member key code.
 *     Set -1 for the members other than menu.
 *     In this case, in order for a Java application to execute a registered <code>Command</code>, it must pass a key event designating key code
 *     #AJSC_KEYCODE_SOFT1 in place of soft key 1 when some kind of user operation is performed.
 *   - <b>When 0 is set in {@link KJavaGfxInfo#numSoftkeys KJavaGfxInfo#numSoftkeys} because the target device is using full-screen mode,
 *     even though the native system does have soft keys.</b><br>
 *     Even though the soft keys are not displayed, key events must be passed using the same key codes as when they are displayed.
 *     Set the same key codes in each member as for normal screen mode.
 *   .
 * - When {@link KJavaGfxInfo#numSoftkeys KJavaGfxInfo#numSoftkeys} is 1, set #AJSC_KEYCODE_SOFT1 as the key code.
 * - When {@link KJavaGfxInfo#numSoftkeys KJavaGfxInfo#numSoftkeys} is 2, use #AJSC_KEYCODE_SOFT1 and #AJSC_KEYCODE_SOFT2 as the key codes.
 * - When {@link KJavaGfxInfo#numSoftkeys KJavaGfxInfo#numSoftkeys} is 3, use #AJSC_KEYCODE_SOFT1, #AJSC_KEYCODE_SOFT2
 *   and #AJSC_KEYCODE_SOFT3 as the key codes.
 * - If it is not necessary to map soft keys to particular command types, set -1 as the key code.
 * .
 *
 * If the number of <code>Command</code>s registered by the Java application in the <code>Displayable</code> derived class exceeds
 * the number of soft keys, JBlendia uses as a menu display key the soft key assigned to the {@link KJavaDeviceCommandKeys#menu menu} member.
 * Soft keys other than the menu display key are assigned to <code>Command</code>s based on the assignments set in this structure and on the
 * <code>Command</code> priorities registered by the Java application.
 * The highest priority <code>Command</code>s are assigned directly to soft keys, while the rest are selected from the menu display.
 *
 */
typedef struct _KJavaDeviceCommandKeysTag
{
    /** The key code for the soft key corresponding to "BACK" */
    int back;
    /** The key code for the soft key corresponding to "CANCEL" */
    int cancel;
    /** The key code for the soft key corresponding to "HELP" */
    int help;
    /** The key code for the soft key corresponding to "EXIT" */
    int exit;
    /** The key code for the soft key corresponding to "OK" */
    int ok;
    /** The key code for the soft key corresponding to "STOP" */
    int stop;
    /** The key code for the soft key corresponding to "Menu" */
    int menu;
}
KJavaDeviceCommandKeys;

/** @} */

/**
 * @addtogroup Device_Control_Game_Key_Mapping Game Key Mapping KSI
 * An interface for retrieving game key mapping.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread. 
 *
 * @par Include file 
 * \#include kjava_sys_device.h
 * @{
 */
/** The Up key. This is the Up key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_UP           (0x2)
/** The Left key. This is the Left key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_LEFT         (0x4)
/** The Right key. This is the Right key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_RIGHT        (0x20)
/** The Down key. This is the Down key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_DOWN         (0x40)
/** The Select key. This is the Select key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_FIRE         (0x100)
/** The A key. This is the A key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_A            (0x200)
/**  The B key. This is the B key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_B            (0x400)
/** The C key. This is the C key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_C            (0x800)
/** The D key. This is the D key bit in the value returned by kjava_device_getKeyState(). */
#define KJAVA_DEVICE_GAME_KEY_D            (0x1000)

/**
 *  Game action type A.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.GAME_A</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_GAME_A        9

/**
 *  Game action type B.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.GAME_B</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_GAME_B        10

/**
 *  Game action type C.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.GAME_C</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_GAME_C        11

/**
 *  Game action type D.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.GAME_D</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_GAME_D        12

/**
 *  Game action type UP.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.UP</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_UP            1

/**
 *  Game action type LEFT.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.LEFT</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_LEFT          2

/**
 *  Game action type DOWN.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.DOWN</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_DOWN          6

/**
 *  Game action type RIGHT.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.RIGHT</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_RIGHT         5

/**
 *  Game action type FIRE.
 *
 *  This type corresponds to that of the <i>javax.microedition.lcdui.Canvas.FIRE</i> field.
 */
#define KJAVA_DEVICE_GAME_ACTION_FIRE          8


/**
 * The structure type for holding the key code for different game action keys.
 */
typedef struct _KJavaDeviceGameActionTag
{
    /** The game action mapped to the 0 key. */
    int key_num0;
    /** The game action mapped to the 1 key. */
    int key_num1;
    /** The game action mapped to the 2 key. */
    int key_num2;
    /** The game action mapped to the 3 key. */
    int key_num3;
    /** The game action mapped to the 4 key. */
    int key_num4;
    /** The game action mapped to the 5 key. */
    int key_num5;
    /** The game action mapped to the 6 key. */
    int key_num6;
    /** The game action mapped to the 7 key. */
    int key_num7;
    /** The game action mapped to the 8 key. */
    int key_num8;
    /** The game action mapped to the 9 key. */
    int key_num9;
    /** The game action mapped to the asterisk (*) key. */
    int key_asterisk;
    /** The game action mapped to the pound (#) key. */
    int key_pound;
    /** The game action mapped to the Left key. */
    int key_left;
    /** The game action mapped to the Up key. */
    int key_up;
    /** The game action mapped to the Right key. */
    int key_right;
    /** The game action mapped to the Down key. */
    int key_down;
    /** The game action mapped to the Select key. */
    int key_select;
}
KJavaDeviceGameAction;

/** @} */

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup Device_Control_Alarm_Sound
 * @{
 */

/**
 * Alerts the user by playing a sound.
 * @param alertType
 *        The type of sound used to alert the user.
 *        One of the following is designated.
 *        - #KJAVA_DEVICE_ALERT_TYPE_ALARM
 *        - #KJAVA_DEVICE_ALERT_TYPE_CONFIRM
 *        - #KJAVA_DEVICE_ALERT_TYPE_ERROR
 *        - #KJAVA_DEVICE_ALERT_TYPE_INFO
 *        - #KJAVA_DEVICE_ALERT_TYPE_WARNING
 *        .
 * @retval 1 if the operation succeeds.
 * @retval 0 if the operation fails (e.g. sound support is lacking or the
 *           sound resource is in use, etc.).
 *
 * This function corresponds to the
 * <i>javax.microedition.lcdui.AlertType.playSound</i> method.
 */
int kjava_device_alertBySound(int alertType);

/**
 * Terminates the alert sound.
 *
 * Stop the alert sound started by kjava_device_alertBySound().
 * If the sound is not playing when this function is called, exit this
 * function without doing anything.
 */
void kjava_device_stopAlertSound(void);

/** @} */

/**
 * @addtogroup Device_Control_Back_Light Backlight Flash Control KSI
 * An interface for controlling the backlight device.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread. 
 *
 * @par Include file 
 * \#include kjava_sys_device.h
 * @{
 */

/**
 * Starts backlight flashing.
 * @param duration
 *        The duration (in milliseconds) of backlight flashing.
 * @retval 1 if the operation succeeds.
 * @retval 0 if backlight support is lacking or the control fails.
 *
 * Flash the backlight for the designated duration. The blink cycle
 * (durations of on and off periods) is platform-dependent.
 *
 * If this function is called while the backlight is flashing,
 * cancel the previous flashing duration designation and flash for
 * the newly designated duration, starting from the instant this function
 * was called. Enable the flashing to be stopped forcibly when
 * kjava_device_stopBacklightFlash() is called.
 *
 * This function is called when the flash duration is designated as a
 * parameter in the <i>javax.microedition.lcdui.Display.flashBacklight</i> method.
 *
 * After backlight flashing started, if an #AJMS_VMEVENT_VM_SUSPENDED 
 * or #AJMS_VMEVENT_VM_STOPPED event is received, the native system must
 * stop the flashing even if kjava_device_stopBacklightFlash() is not yet called.
 */
int kjava_device_startBacklightFlash(int duration);

/**
 * Stops backlight flashing.
 * @retval 1 if the operation succeeds.
 * @retval 0 if backlight support is lacking or the control fails.
 *
 * Stop the backlight flashing.
 *
 * If this function is called when kjava_device_startBacklightFlash() has
 * not been called or the duration designated in
 * kjava_device_startBacklightFlash() has elapsed, return 0 without
 * performing any operation.
 *
 * This function is called when 0 was designated in a parameter of the
 * <i>javax.microedition.lcdui.Display.flashBacklight</i> method.
 */
int kjava_device_stopBacklightFlash(void);

/** @} */

/**
 * @addtogroup Device_Control_Vibration Vibrator Control KSI
 * An interface for controlling the native vibrator.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread. 
 *
 * @par Include file 
 * \#include kjava_sys_device.h
 * @{
 */

/**
 * Starts vibration.
 * @param duration
 *        The duration of the vibration (in milliseconds).
 * @retval 1 if the operation succeeds.
 * @retval 0 if vibration support is lacking or the control fails.
 *
 * Vibrate the target device for the designated duration.
 *
 * If this function
 * is called while the target device is vibrating, cancel the previous
 * duration designation and vibrate for the newly designated duration,
 * starting from the instant this function was called.
 *
 * Enable vibration to be stopped forcibly when kjava_device_stopVibration() is
 * called.
 *
 * This function is called when the vibration duration is
 * designated in a parameter of the
 * <i>javax.microedition.lcdui.Display.vibrate</i> method.
 *
 * After vibration started, if an #AJMS_VMEVENT_VM_SUSPENDED 
 * or #AJMS_VMEVENT_VM_STOPPED event is received, the native system must
 * stop the vibrator even if kjava_device_stopVibration() is not yet called.
 */
int kjava_device_startVibration(int duration);

/**
 * Stops vibration.
 * @retval 1 if the operation succeeds.
 * @retval 0 if vibration support is lacking or the control fails.
 *
 * Stop the target device vibration.
 *
 * If this function is called when kjava_device_startVibration() has
 * not been called or the duration designated in
 * kjava_device_startVibration() has elapsed, return 0 without
 * performing any operation.
 *
 * This function is called when 0 was
 * designated in a parameter of the
 * <i>javax.microedition.lcdui.Display.vibrate</i> method.
 */
int kjava_device_stopVibration(void);

/** @} */

/**
 * @addtogroup Device_Control_Command_Key_Mapping
 * @{
 */

/**
 * Gets information of command-key mapping.
 * @param commandkeys
 *        A pointer to the KJavaDeviceCommandKeys structure for storing command key mapping information.
 *
 * This function is used to map the <code>Command</code>s to the target device keypad keys.
 * Usually, all the <code>Command</code>s should be mapped to one of the following AJSC key codes:
 * - #AJSC_KEYCODE_SOFT1 (Soft key 1)
 * - #AJSC_KEYCODE_SOFT2 (Soft key 2)
 * - #AJSC_KEYCODE_SOFT3 (Soft key 3)
 * .
 * Soft key 3 might not exit depending on the specification of the target device.
 * If a command is not supported, -1 should be set in the corresponding structure member.
 *
 * A typical implementation is as follows:
 * @code
 * commandkeys->back    = AJSC_KEYCODE_SOFT2;
 * commandkeys->cancel  = AJSC_KEYCODE_SOFT2;
 * commandkeys->help    = -1;
 * commandkeys->exit    = AJSC_KEYCODE_SOFT2;
 * commandkeys->ok      = AJSC_KEYCODE_SOFT1;
 * commandkeys->stop    = AJSC_KEYCODE_SOFT2;
 * commandkeys->menu    = AJSC_KEYCODE_SOFT1;
 * @endcode
 *
 * See the description of #KJavaDeviceCommandKeys for more details.
 */
void kjava_device_getCommandKey( KJavaDeviceCommandKeys* commandkeys );

/** @} */

/**
 * @addtogroup Device_Control_Game_Key_Mapping
 * @{
 */
/**
 *        Gets the game key states from the game input device.
 * @return
 * Return game key states as per the bit assignments below.<br>
 *   #KJAVA_DEVICE_GAME_KEY_UP<br>
 *   #KJAVA_DEVICE_GAME_KEY_DOWN<br>
 *   #KJAVA_DEVICE_GAME_KEY_LEFT<br>
 *   #KJAVA_DEVICE_GAME_KEY_RIGHT<br>
 *   #KJAVA_DEVICE_GAME_KEY_FIRE<br>
 *   #KJAVA_DEVICE_GAME_KEY_A<br>
 *   #KJAVA_DEVICE_GAME_KEY_B<br>
 *   #KJAVA_DEVICE_GAME_KEY_C<br>
 *   #KJAVA_DEVICE_GAME_KEY_D
 *
 * Return the game key states.
 * The purpose of this function is to prevent the key information
 * used by Java applications from lagging behind the actual hardware states.
 *
 * Set bits in the return value as in the table below.
 *
 * @htmlonly
 * <table border=1 cellspacing=0 cellpadding=2 width="100%">
 *  <tr>
 *   <td><b>Key state</b></td>
 *   <td><b>Return value bits</b></td>
 *  </tr>
 *  <tr>
 *   <td>
 *   @endhtmlonly
 *   Currently pressed, or pressed at least once since the previous time kjava_device_getKeyState() was called
 *   @htmlonly
 *   </td>
 *   <td> 1 </td>
 *  </tr>
 *  <tr>
 *   <td>
 *   @endhtmlonly
 *   Currently released, and not pressed since the previous time kjava_device_getKeyState() was called.
 *   @htmlonly
 *   </td>
 *   <td> 0 </td>
 *  </tr>
 * </table>
 * @endhtmlonly
 *
 * The first time kjava_device_getKeyState() is called, set this information based only on the state at that point in time.
 *
 * The mapping of game key bits to actual keys is dependent on the native system specifications.
 *
 * This function corresponds to the <code>javax.microedition.lcdui.game.GameCanvas</code> class <code>getKeyStates</code> method.
 *
 */
unsigned long kjava_device_getKeyState(void);

/**
 * Gets game action information for mapping to key codes.
 * @param gameAction
 *        A pointer to the #KJavaDeviceGameAction structure
 *        for storing key to game action mapping information.
 *
 * This function is used to map the game actions to the target device keypad keys.
 * All the keys in the #KJavaDeviceGameAction structure should be mapped to one of the following game actions:
 * - #KJAVA_DEVICE_GAME_ACTION_GAME_A
 * - #KJAVA_DEVICE_GAME_ACTION_GAME_B
 * - #KJAVA_DEVICE_GAME_ACTION_GAME_C
 * - #KJAVA_DEVICE_GAME_ACTION_GAME_D
 * - #KJAVA_DEVICE_GAME_ACTION_UP
 * - #KJAVA_DEVICE_GAME_ACTION_LEFT
 * - #KJAVA_DEVICE_GAME_ACTION_DOWN
 * - #KJAVA_DEVICE_GAME_ACTION_RIGHT
 * - #KJAVA_DEVICE_GAME_ACTION_FIRE
 * - <b>0</b>: Indicate the key is not mapping to any game action.
 * .
 *
 *
 * A typical implementation is as follows:
 * @code
 * gameAction->key_num0     = KJAVA_DEVICE_GAME_ACTION_GAME_A;
 * gameAction->key_num1     = KJAVA_DEVICE_GAME_ACTION_GAME_B;
 * gameAction->key_num2     = KJAVA_DEVICE_GAME_ACTION_UP;
 * gameAction->key_num3     = 0;
 * gameAction->key_num4     = KJAVA_DEVICE_GAME_ACTION_LEFT;
 * gameAction->key_num5     = KJAVA_DEVICE_GAME_ACTION_FIRE;
 * gameAction->key_num6     = KJAVA_DEVICE_GAME_ACTION_RIGHT;
 * gameAction->key_num7     = 0;
 * gameAction->key_num8     = KJAVA_DEVICE_GAME_ACTION_DOWN;
 * gameAction->key_num9     = 0;
 * gameAction->key_asterisk = KJAVA_DEVICE_GAME_ACTION_GAME_C;
 * gameAction->key_pound    = KJAVA_DEVICE_GAME_ACTION_GAME_D;
 * gameAction->key_left     = KJAVA_DEVICE_GAME_ACTION_LEFT;
 * gameAction->key_right    = KJAVA_DEVICE_GAME_ACTION_RIGHT;
 * gameAction->key_up       = KJAVA_DEVICE_GAME_ACTION_UP;
 * gameAction->key_down     = KJAVA_DEVICE_GAME_ACTION_DOWN;
 * gameAction->key_select   = KJAVA_DEVICE_GAME_ACTION_FIRE;
 * @endcode
 *
 * Check the specification of <i>javax.microedition.lcdui.Canvas</i> for more information.
 *
 */
void kjava_device_getGameAction( KJavaDeviceGameAction *gameAction );

#ifdef AJSC_SUPPORT_NOKIA_EXTENSION

/**
  * @description	Activates and deactivates the lights on the device. 
  * @para num	is the number or id for light, 0 is used for display backlight, other numbers are currently left unspecified.
  * @para level	the lighting level 0-100. 0 means "off" or some other minimum lighting setting. For many devices, a value greater than 0 means "light on". 
  */
void  kjava_device_setLight(int num, int level);

#endif /*AJSC_SUPPORT_NOKIA_EXTENSION*/

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_DEVICE_HEADER */
