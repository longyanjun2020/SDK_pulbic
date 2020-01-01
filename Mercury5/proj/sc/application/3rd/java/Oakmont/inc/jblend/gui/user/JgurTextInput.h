/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions related to the text input component.
 */

#ifndef ___GUI_USER_TEXTINPUT_H
#define ___GUI_USER_TEXTINPUT_H

#include <JkTypes.h>

#include <gui/common/JgTextInput.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_TextInput
 * @{
 */

/**
 * Starts an input method.
 * 
 * @param textinput
 *        The corresponding text input component.
 */
void JgurTextInputLaunchInputMethod(JGTextInput textinput);

/**
 * Terminates the text input method.
 * 
 * @param textinput
 *        The corresponding text input component.
 */
void JgurTextInputCancelInputMethod(JGTextInput textinput);

/**
 * Gets the maximum number of characters for text input.
 * 
 * @param textinput
 *        The corresponding text input component
 * @param maxSize
 *        The requested maximum number of characters
 * 
 * @return
 *        The maximum number of characters
 * 
 * The number returned for maxSize takes into account the size of memory that
 * can currently be allocated.
 */
JKSint32 JgurTextInputGetMaxSize(JGTextInput textinput, JKSint32 maxSize);

/**
 *   Checks whether the string contents and text input constraints are compatible.
 *   
 *   @param text The initial address of the text array containing the string
 *   @param length The length of the string (number of characters, not bytes)
 *   @param constraints The text input constraints
 *   @return Return #JK_TRUE if the string contents and input constraints are 
 *   compatible, else return #JK_FALSE.
 *   
 *   The character string passed in the text parameter is a string confirmed to be 
 *   in accord with the stipulations in the profile specification. If the native system 
 *   imposes its own restrictions outside the profile specifications, check 
 *   compatibility with those restrictions in this function.
 */
JKBool JgurTextInputVerifyText(const JKWChar text[], JKSint32 length, JKUint32 constraints);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_USER_TEXTINPUT_H */

