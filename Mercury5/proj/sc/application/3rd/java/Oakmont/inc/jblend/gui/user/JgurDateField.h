/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying date field properties.
 */

#ifndef ___GUI_USER_DATEFIELD_H
#define ___GUI_USER_DATEFIELD_H

#include <JkTypes.h>

#include <JkOffScreen.h>
#include <JkVideo.h>
#include <JkSoftkey.h>
#include <JgString.h>
#include <JgDateField.h>
#include <JgKeyEvent.h>
#include <JginDateField.h>
#include <JginGUIEvent.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_DateField
 * @{
 */

/**
 * Activates date input control.
 * 
 * @param datefield
 *        The date field
 */
void JgurDateFieldLaunchDateModule(JGDateField datefield);

/**
 * Terminates date input control.
 * 
 * @param datefield
 *        The date field
 */
void JgurDateFieldCancelDateModule(JGDateField datefield);

/**
 *  Gets the character string indicating the date (year-month-day, day 
 *  of the week) or time (hour-minute) set in the date field.
 *
 *   @param datefield The date field 
 *   @param part      The type of string to be acquired.
 *                    One of the following values is designated.
 *                    <ul>
 *                     <li>#JG_DFIELD_INPUTMODE_DATE
 *                     <li>#JG_DFIELD_INPUTMODE_TIME
 *                    </ul>
 *   @param strBuf    The handle of the string buffer for putting the acquired
 *                    string. The buffer is cleared when this function is called.
 */
void JgurDateFieldGetString(JGDateField datefield, JKUint32 part, JGStrBuf strBuf);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_USER_DATEFIELD_H */

