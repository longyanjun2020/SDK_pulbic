/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   API functions for modifying command menu list properties.
 */

#ifndef ___GUI_COMMON_COMMANDMENU_H
#define ___GUI_COMMON_COMMANDMENU_H

#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_CommandMenu
 * @{
 */

/**
 *   Command selection was cancelled.
 * 
 *   When command selection is cancelled, notify the event using
 *   #JginGUIEventPostEvent().
 *   The values of the param members in the JGT_GUIEvent structure passed as an 
 *   argument of JginGUIEventPostEvent() are as indicated in the following 
 *   parameters.
 * 
 *   @param param1 -
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 */
#define JG_GUI_CMLST_EVT_CANCEL         (JG_GUI_LSTBX_EVT_END + 0x01)

/**
 * @internal
 *   The maximum value of GUI command menu list events.
 */
#define JG_GUI_CMLST_EVT_END            (JG_GUI_LSTBX_EVT_END + 0x01)

/**
 *   The command menu list component type.
 * 
 * @see JgComGetComponentType
 */
#define JG_COMMANDMENU     12

/**
 *   The command menu list handle.
 *
 *   A command menu list handle is data identifying the command menu list.<br>
 *   The command menu list handle may be used as a component handle or list handle or listbox handle.
 * 
 * @see JGListBox
 */
typedef JGListBox   JGCommandMenu;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_COMMANDMENU_H */

