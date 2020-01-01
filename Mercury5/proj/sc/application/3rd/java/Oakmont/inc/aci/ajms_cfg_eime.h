/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/**
 * @file ajms_cfg_eime.h
 * External Input Method ACI
 */

#ifndef AJMS_CFG_EIME_HEADER
#define AJMS_CFG_EIME_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include "aj_type.h"

/*
 *
 *  Interfaces listed in the group are used for external input method, 
 *    including these functionalities:
 *
 *    - Registry the EIME launch and terminate function.
 *    - Function for EIME to return the user input data.
 *    .
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup External_Input_Method_ACI
 * An interface for using an External Input Method Environment (EIME) with AJSC.
 * This interface is implemented in AJSC.
 *
 * @par Include file 
 * \#include ajms_cfg_eime.h
 * @{
 */
/**
 * @name Acceptable Character Type
 * @{
 */
/** Acceptable character type: All (default) */
#define AJMS_EIME_CONSTRAINTS_ANY          (1)
/** Acceptable character type: Email address */
#define AJMS_EIME_CONSTRAINTS_EMAILADDR    (2)
/** Acceptable character type: Numerals */
#define AJMS_EIME_CONSTRAINTS_NUMERIC      (3)
/** Acceptable character type: Telephone numbers */
#define AJMS_EIME_CONSTRAINTS_PHONENUMBER  (4)
/** Acceptable character type: URL */
#define AJMS_EIME_CONSTRAINTS_URL          (5)
/** Acceptable character type: Decimal string */
#define AJMS_EIME_CONSTRAINTS_DECIMAL      (6)
/** @} */

/**
 * @name Capitalization Mode
 * @{
 */
/** Capitalization mode: Undefined (default) */
#define AJMS_EIME_CAPS_UNDEFINE            (1)
/** Capitalization mode: First letter of word */
#define AJMS_EIME_CAPS_WORD                (2)
/** Capitalization mode: First letter of sentence */
#define AJMS_EIME_CAPS_SENTENCE            (3)
/** @} */

/**
 * @name Result of Input by EIME
 * @{
 */
/** EIME Result: User canceled the EIME data */
#define AJMS_EIME_USER_CANCEL              (0)
/** EIME Result: User confirmed the EIME data */
#define AJMS_EIME_USER_CONFIRM             (1)
/** @} */

/** 
 * The data structure type for containing the data used for launching an EIME.
 */
typedef struct _AJMS_EimeData
{
    /** 
     * A pointer to a UCS2-encoded character string that should be used as the initial text in EIME dialog box. 
     * The character string is not NUL-terminated.
     * Furthermore, note that there may be NUL-character in the middle of the character string.
     */
    AJ_U16   *initText;
    /** 
     * The number of characters in the text designated by the <i>initText</i> member. 
     */
    AJ_S32    initTextLen;
    /** 
     * The maximum number of acceptable characters. 
     */
    AJ_S32    maxSize;
    /** 
     * The input constraint type.
     * One of the following values is set.
     * - #AJMS_EIME_CONSTRAINTS_ANY
     * - #AJMS_EIME_CONSTRAINTS_EMAILADDR
     * - #AJMS_EIME_CONSTRAINTS_NUMERIC
     * - #AJMS_EIME_CONSTRAINTS_PHONENUMBER
     * - #AJMS_EIME_CONSTRAINTS_URL
     * - #AJMS_EIME_CONSTRAINTS_DECIMAL
     */
    AJ_S32    constraints;
    /** 
     * A flag indicating whether or not line-break can be entered. 
     */
    AJ_BOOL   isAllowedLineBreak;
    /** 
     * A flag indicating whether or not the text input should be in the password mode. 
     */
    AJ_BOOL   isPasswordMode;
    /** 
     * A flag indicating whether or not the dictionary entry mode is disabled. 
     * Ignore this field if dictionary search is not supported. 
     * For details, see the description of <code>javax.microedition.lcdui.TextField.SENSITIVE</code> field.
     */
    AJ_BOOL   isSensitive;
    /** 
     * A flag indicating whether or not the predictive mode is enabled.
     * Ignore this field if dictionary search is not supported. 
     * For details, see the description of <code>javax.microedition.lcdui.TextField.NON_PREDICTIVE</code> field.
     */
    AJ_BOOL   isPredictive;
    /** 
     * The automatic capitalization mode.
     * One of the following values is set.
     * - #AJMS_EIME_CAPS_UNDEFINE
     * - #AJMS_EIME_CAPS_WORD
     * - #AJMS_EIME_CAPS_SENTENCE
     * .
     * Ignore this field if automatic capitalization is not supported. 
     * For details, see the descriptions of <code>javax.microedition.lcdui.TextField.INITIAL_CAPS_WORD</code> and 
     * <code>javax.microedition.lcdui.TextField.INITIAL_CAPS_SENTENCE</code> field.
     */
    AJ_S32    capitalMode;
    /** 
     * A pointer to the UCS2-encoded character string containing the initial input mode.
     * Ignore this field if no device-dependent input mode is supported. 
     * For details, see the description of <code>javax.microedition.lcdui.TextField.setInitialInputMode(String)</code> method.
     */
    AJ_U16   *inputModeText;
    /** 
     * The number of characters in the string indicated by <i>inputModeText</i>.
     */
    AJ_S32    inputModeTextLen;
    /** 
     * A pointer to the UCS2-encoded character string representing the EIME dialog title.
     * Ignore this field if target EIME dialog does not support title. 
     * For details, see 
     * the description of <code>label</code> parameter to the <code>javax.microedition.lcdui.TextField</code> class constructor and 
     * the description of <code>title</code> parameter to the <code>javax.microedition.lcdui.TextBox</code> class constructor.
     */
    AJ_U16   *titleText;
    /** 
     * The number of characters in the string indicated by <i>titleText</i>.
     */
    AJ_S32    titleTextLen;
    /** 
     * The X coordinate of the character drawing position. 
     */
    AJ_S32    contentX;
    /** 
     * The Y coordinate of the character drawing position. 
     */
    AJ_S32    contentY;
    /** 
     * The width of the character drawing area. 
     */
    AJ_S32    contentWidth;
    /** 
     * The height of the character drawing area. 
     */
    AJ_S32    contentHeight;
}
AJMS_EimeData;

/**
 *        The function type for starting external input method.
 * @param data 
 *        A pointer to an AJMS_EimeLaunch structure containing the information 
 *        for launching the external input method procedure. 
 *
 * If use of the native input method is desired for character entry on GUI components, 
 * implement a function of this callback function type to launch the native input method, 
 * and register the function through a parameter of ajms_cfg_registerEimeHandler().
 * 
 * When an input method is launched from a GUI component, the <i>contentX</i>, <i>contentY</i>,
 * <i>contentWidth</i> and <i>contentHeight</i> members in <i>{@link #AJMS_EimeData *data}</i>
 * indicate the virtual screen coordinates of the GUI component.
 *
 * If the native system input method can be drawn over the GUI component, 
 * the native system may draw it on the real screen portion that corresponds to the virtual 
 * screen area indicated by <i>contentX</i>, <i>contentY</i>,
 * <i>contentWidth</i> and <i>contentHeight</i> members in <i>{@link #AJMS_EimeData *data}</i>.
 * 
 * Using of the <i>contentX</i>, <i>contentY</i>, <i>contentWidth</i> and 
 * <i>contentHeight</i> members is optional. 
 * That is, the native system may use the full-screen regardless of these parameters.
 *
 * This function should request launching of the native input method only and 
 * return as soon as possible to avoid blocking of AJSC processing long time.
 * The input method must be launched in a separate thread.       
 *
 * @see ajms_cfg_registerEimeHandler
 */
typedef void (*AJMS_EimeLaunch)( AJMS_EimeData* data );

/**
 * The function type for finishing external input method.
 *
 * If use of the native input method is desired for character entry on GUI components, 
 * implement a function of this callback function type to finish the native input method, 
 * and register the function through a parameter of ajms_cfg_registerEimeHandler().
 *
 * The callback function is called to forcibly terminate the input method.
 * The native system must free the native system resources used for the input method when it is 
 * finished.
 *
 * When the native input method is terminated in response to the callback function, 
 * the native system should not call ajms_cfg_finalizeEime() to notify AJSC of completion
 * of the input method.
 *
 * @see ajms_cfg_registerEimeHandler
 */
typedef void (*AJMS_EimeTerminate)( void );

/*-----------------------------------------------------------------------------
 * Global Function Prototype
 *----------------------------------------------------------------------------*/

/**
 *        Registers callback functions for native input method.
 * @param launchCb
 *        The address of the callback function for starting the native input method.
 * @param terminateCb
 *        The address of the callback function for finishing the native input method.
 *
 * If use of the native input method is desired for character entry on GUI components, 
 * implement callback functions for starting and finishing the native input method, 
 * and register them through this function with AJSC.
 * 
 * Perform the registration by this function before launching the Java application 
 * by ajms_arc_runApp() or ajms_arc_runAppEx1(). 
 * Namely, it must be performed for each launch of Java application.
 * 
 * Only a set of callback functions can be used.
 * If this function is called multiple times, the callback functions passed in the last call are used.
 * 
 * If #AJ_NULL is passed in the <i>launchCb</i> parameter, the default input method implemented in AJSC 
 * is used. 
 */
void ajms_cfg_registerEimeHandler( AJMS_EimeLaunch    launchCb, 
                                   AJMS_EimeTerminate terminateCb);

/**
 *        Notifies AJSC of completion of the native input method. 
 * @param resultStr          
 *        A pointer to the buffer holding the result character string input by the user.
 *        The string must be UCS-2 encoded.
 * @param resultStrLen       
 *        The number of the characters in the string indicated by <i>resultStr</i>.
 * @param resultState        
 *        The result of user input.
 *        Pass one of the following values.
 *        - #AJMS_EIME_USER_CONFIRM
 *        - #AJMS_EIME_USER_CANCEL
 *
 * When the user finishes or cancels the native input method, end the input method and 
 * call this function to notify AJSC of the result. 
 *
 * @see AJMS_EimeLaunch, AJMS_EimeTerminate
 */

void ajms_cfg_finalizeEime(AJ_U16* resultStr, AJ_S32 resultStrLen, AJ_S32 resultState);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AJMS_EIM_HEADER */
