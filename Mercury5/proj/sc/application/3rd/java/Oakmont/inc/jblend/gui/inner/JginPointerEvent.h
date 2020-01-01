/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Pointing device event definitions.
 */

#ifndef ___GUI_INNER_POINTEREVENT_H
#define ___GUI_INNER_POINTEREVENT_H

#include <JkTypes.h>

#include <JgPointerEvent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PointerEvent
 * @{
 */

/**
 * The pointer event handler
 * 
 * @param event
 *        A pointer to the JGT_PointerEvent structure holding the generated 
 *        event information
 * 
 * @return
 *        Return the processing result.
 */
typedef JKUint32 (*JGT_PointerEvtHandler)(const JGT_PointerEvent *event);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_INNER_POINTEREVENT_H */

