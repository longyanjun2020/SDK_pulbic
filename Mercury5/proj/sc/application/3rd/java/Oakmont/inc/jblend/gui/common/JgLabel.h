/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Common API functions for the label component.
 */

#ifndef ___GUI_COMMON_LABEL_H
#define ___GUI_COMMON_LABEL_H

#include <JkTypes.h>

#include <gui/common/JgString.h>
#include <gui/common/JgGUIEvent.h>
#include <gui/common/JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Label
 * @{
 */

/**
 * @internal
 * The maximum GUI label event value.
 */
#define JG_GUI_LBL_EVT_END              (JG_GUI_EVT_END + 0x00)

/**
 * The label component type
 * 
 * @see JgComGetComponentType
 */
#define JG_LABEL   5

/**
 * The label handle
 * 
 * A label handle is data identifying the label.<br>
 * The label handle can be used as a component handle.
 * 
 * @see JGCom
 */
typedef JGCom       JGLabel;

/**
 * Gets the label text string.
 * 
 * @param label
 *        The label handle
 * 
 * @return
 *        A handle is returned indicating the string with the label text. If no 
 *        text is set, JK_INVALID_HANDLE is returned.
 * 
 * The obtained text must not be discarded. This is done by the GUI Toolkit.
 * 
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When label is an illegal handle.</li>
 *   </ul>
 */
JGString JgLabelGetText(JGLabel label);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_LABEL_H */

