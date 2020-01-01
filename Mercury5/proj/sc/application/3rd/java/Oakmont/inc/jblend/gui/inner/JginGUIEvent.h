/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * GUI Toolkit event definitions.
 */

#ifndef ___GUI_INNER_GUIEVENT_H
#define ___GUI_INNER_GUIEVENT_H

#include <JgGUIEvent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_GUIEvent
 * @{
 */

/**
 * Generates a GUI event.
 * 
 * @param responseHandler
 *        The GUI event response handler
 * @param guiEvent
 *        Pointer to the JGT_GUIEvent structure in which event information is stored.
 * 
 * Call this function when notifying a GUI event to JBlend. In the 
 * responseHandler parameter set the response handler to be called when 
 * JBlend processed the GUI event designated in the guiEvent parameter.
 * 
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *    <li>When responseHandler is  #JK_NULL </li>
 *   </ul>
 */
void JginGUIEventPostEvent(JGT_GUIEvtResponseHandler responseHandler,
                           const JGT_GUIEvent *guiEvent);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_GUIEVENT_H */

