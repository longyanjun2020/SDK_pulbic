/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   API functions for the modifying container component properties.
 */

#ifndef ___GUI_COMMON_CONTAINER_H
#define ___GUI_COMMON_CONTAINER_H

#include <JkTypes.h>

#include <gui/common/JgCom.h>
#include <gui/common/JgGUIEvent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Container
 * @{
 */

/**
 * @internal
 *   The maximum GUI container event value
 */
#define JG_GUI_CONT_EVT_END         (JG_GUI_EVT_END + 0x00)

/**
 *   The container handle
 *   
 *   A container handle is data identifying the container. <br>
 *   The container handle can be used as a component handle.
 * @see JGCom
 */
typedef JGCom       JGContainer;

/**
 *   Gets the number of components registered for the container.
 *   
 *   @param container The container handle
 *   @return The number of registered components
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>container</i> is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgContainerGetSize(JGContainer container);

/**
 *   Gets a component in the container. 
 *   
 *   @param container  The container handle.
 *   @param index The index of the component in the container.  
 *                Index numbers are assigned starting from 0. 
 *   @return      The handle of the component indicated by the index parameter.
 *
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>container</i> is an illegal handle. 
 *    <li>When <i>index</i> is an illegal value. 
 *   </ul>
 */
JGCom JgContainerGetComponent(JGContainer container, JKSint32 index);

/**
 *   Gets the position of the first container component of the designated type. 
 *   
 *   @param container The container handle
 *   @param type The type of component 
 *   @return The position of the first component of the designated type is returned. 
 *           Positions are numbered starting from 0.
 *           If none is found, -1 is returned.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>container</i> is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgContainerGetSpecifiedTypeIndex(JGContainer container, JKUint32 type);

/**
 *   Gets the focus position in the container.
 *   
 *   @param container The container handle.
 *   @return The inner focus position, or -1 if no inner focus.
 *   
 *   This function returns the index (a number starting from 0) of the 
 *   component having the inner focus in the container.
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *     <li>When <i>container</i> is an illegal handle.</li>
 *   </ul>
 */
JKSint32 JgContainerGetFocusedIndex(JGContainer container);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_CONTAINER_H */

