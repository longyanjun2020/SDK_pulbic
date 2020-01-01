/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Common API functions for the title component.
 */

#ifndef ___GUI_COMMON_TITLE_H
#define ___GUI_COMMON_TITLE_H

#include <JkTypes.h>

#include <gui/common/JgString.h>
#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Title
 * @{
 */

/**
 * @internal
 * The maximum value for GUI title events
 */
#define JG_GUI_TITLE_EVT_END              (JG_GUI_EVT_END + 0x00)

/**
 * The title component type
 * 
 * @see JgComGetComponentType
 */
#define JG_TITLE   6

/**
 * The title handle
 * 
 * A title handle is data identifying the title.
 * The title handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGTitle;

/**
 * Gets the title text.
 * 
 * @param title
 *        The title handle
 * @return
 *         A handle is returned indicating a string with the title text. If 
 *         none is set, JK_INVALID_HANDLE is returned.
 * 
 * The obtained text must not be discarded. It is disposed of by the GUI Toolkit.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When title is an illegal handle.</li>
 *   </ul>
 */
JGString JgTitleGetText(JGTitle title);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_TITLE_H */

