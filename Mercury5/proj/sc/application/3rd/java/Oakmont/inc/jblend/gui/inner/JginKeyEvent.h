/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Key event definitions.
 */

#ifndef ___GUI_INNER_KEYEVENT_H
#define ___GUI_INNER_KEYEVENT_H

#include <JkTypes.h>

#include <JgKeyEvent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_KeyEvent
 * @{
 */

/**
 * The key event handler
 * 
 * @param event
 *        A pointer to the JGT_KeyEvent structure holding the generated 
 *        event information
 * 
 * @return
 *        Return the processing result.
 */
typedef JKUint32 (*JGT_KeyEvtHandler)(const JGT_KeyEvent *event);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_KEYEVENT_H */

