/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   API functions for modifying container properties.
 */

#ifndef ___GUI_INNER_CONTAINER_H
#define ___GUI_INNER_CONTAINER_H

#include <JkTypes.h>

#include <gui/inner/JginCom.h>
#include <gui/common/JgContainer.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Container
 * @{
 */

/**
 *   A new component was added to the container.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKSint32 The index of the component added
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_CONT_EVT_COM_INSERTED        (JG_COM_EVT_END + 0x01)

/**
 *   A component in container is being deleted.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the #JGT_ComEvent
 *   structure passed to the event handler by JBlend are indicated in the 
 *   following parameters. The event handler return value should be as indicated 
 *   below.
 *   
 *   @param param1 #JKSint32 Index of the component for deletion
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_CONT_EVT_COM_REMOVING        (JG_COM_EVT_END + 0x02)

/**
 *   A component in container was deleted.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   #JGT_ComEvent structure passed to the event handler by JBlend are 
 *   as indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 *   
 *   @param param1 #JKSint32 Index of the deleted component.
 *                 The current index either points to a different component than 
 *                 the one that was deleted or becomes invalid.
 *   @param param2 -
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_CONT_EVT_COM_REMOVED         (JG_COM_EVT_END + 0x03)

/**
 *   Notifies that focus has moved inside the container.
 *   
 *   When this event is processed by the event handler defined as 
 *   #JGT_ComEvtHandler type, the values of the param members in the 
 *   #JGT_ComEvent structure passed to the event handler by JBlend are 
 *   as indicated in the following parameters. The event handler return value 
 *   should be as indicated below.
 *   
 *   @param param1 #JKSint32 The current focus position
 *   @param param2 #JKSint32 The previous focus position
 *   @param param3 -
 *   @param param4 -
 *   @return Return 0.
 * 
 * @see JGT_ComEvent::type
 */
#define JG_CONT_EVT_FOCUS_CHANGED       (JG_COM_EVT_END + 0x04)

/**
 * @internal
 *   The maximum valid component event value for the container.
 */
#define JG_CONT_EVT_END                 (JG_COM_EVT_END + 0x04)

/**
 *   Sets the focus position inside the container.
 *   
 *   @param container The container handle.
 *   @param index The inner focus position.
 *                Index numbers are assigned starting from 0. 
 *   
 *   In the following case @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When <i>container</i> is an illegal handle. 
 *    <li>When <i>index</i> is an illegal value. 
 *   </ul>
 */
void JginContainerSetFocusedIndex(JGContainer container, JKSint32 index);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_CONTAINER_H */

