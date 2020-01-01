/*
 * Copyright 2005 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMKeyCode.h
 * Key Code Customization JBI
 */
/**
 * @addtogroup Module_KeyCode_Customize_JBI
 * @{
 */

#ifndef ___AMKEYCODE_H
#define ___AMKEYCODE_H

#include "JkTypes.h"
#include "JkTypesKeyCode.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 *         Gets information about customization of key code and key name to be passed 
 *         to a Canvas object.
 *  @param stdKeyTableAddr
 *         A pointer to the structure holding key code and key name of JBlend standard keys.
 *         The structure indicated by this pointer and the data indicated by 
 *         the structure's pointer type members must remain valid until the JVM exits.
 *         If JBlend standard setting is used, designate #JK_NULL.
 *  @param extKeyTableAddr
 *         A pointer to the structure holding key code and key name of native system original keys.
 *         The structure indicated by this pointer and the data indicated by 
 *         the structure's pointer type members must remain valid until the JVM exits.
 *         If native system original keys are not used, designate #JK_NULL.
 *  @return
 *         #JK_TRUE if the operation succeeds. <br>
 *         #JK_FALSE if it fails. This function fails if #JK_NULL is designated 
 *         in both of <i>stdKeyTableAddr</i> and  <i>extKeyTableAddr</i> parameters.
 *
 * In JBlend standard behavior,
 * if a key event is passed with JBlend standard key code (a key code 
 * constant named starting with <i>AM_KEYCODE_</i>) while an object  
 * of <code>javax.microedition.lcdui.Canvas</code> or its subclass is 
 * set as a <code>Displayable</code>, JBlend converts the key code passed in 
 * the AmNotifyKeyEvent() function <i>keyCode</i> parameter to 
 * a key code specified in MIDP by referring to an internal table,
 * then JBlend passes the result to the <code>keyCode</code> parameter of
 * a <code>Canvas</code> object method <code>keyPressed</code>, 
 * <code>keyReleased</code>, or <code>keyRepeated</code>.
 * When, after these methods are called, the Java application calls 
 * the <code>Canvas</code> object <code>getKeyName</code> method,
 * JBlend returns the key name corresponding to the key code by referring
 * to the internal table.
 * 
 * If a pointer value other than #JK_NULL is passed in the <i>stdKeyTableAddr</i>,
 * JBlend performs key code conversion for JBlend standard keys,
 * by using the structure indicated by the pointer in place of the JBlend internal table.
 * This enables the following customization:
 * - To change the key code passed in the <code>keyCode</code> parameter of
 *   the <code>Canvas</code> object methods <code>keyPressed</code>, 
 *   <code>keyReleased</code>, and <code>keyRepeated</code>.
 * - To change key name returned by the <code>Canvas</code> class <code>getKeyName</code> method.
 * .
 *  
 * If a pointer value other than #JK_NULL is passed in the <i>extKeyTableAddr</i>,
 * JBlend performs uses the designated structure as the key code conversion 
 * table for native system original keys.
 * This enables the following customization:
 * - To add key codes to be passed in the <code>keyCode</code> parameter of
 *   the <code>Canvas</code> object methods <code>keyPressed</code>, 
 *   <code>keyReleased</code>, and <code>keyRepeated</code>.
 * - To set key names to be returned by the <code>Canvas</code> class <code>getKeyName</code> method.
 * .
 * 
 * This function needs to be called in the event handler which receives
 * a #JK_VMEVENT_VMSTARTED JVM event, that is issued by JBlend after the native system 
 * calls AamsVmStartMIDP().
 * 
 * The native system must not change the values indicated by the 
 * structures <i>*stdKeyTableAddr</i> and <i>*extKeyTableAddr</i>
 * until the JVM terminates.
 * 
 * For details of key code and its name that are passed to Java 
 * when a key event occurs for a JBlend standard key, and details of
 * values to be set in the structure indicated by <i>stdKeyTableAddr</i>
 * for customizing those information, refer to the description of 
 * #JKT_StdKeyTable structure type.
 *
 * For details of implementation necessary for notifying Java application 
 * of a key event for native system original keys (i.e. not JBlend standard keys),
 * refer to the description of #JKT_ExtKeyTable structure type.
 * 
 * Note that JBlend does not verify the validity of the values set in the structures
 * indicated by <i>stdKeyTableAddr</i> and <i>extKeyTableAddr</i>.
 * Be sure to set appropriate values in those structures.
 * @see  AmNotifyKeyEvent()
 * @see  JkDeviceGetGameAction()
 */
JKBool AmSetKeyCodeTable( const JKT_StdKeyTable *stdKeyTableAddr, const JKT_ExtKeyTable *extKeyTableAddr);

/**
 * @} end of group
 */

#ifdef __cplusplus
}
#endif

#endif /* ___AMKEYCODE_H */
