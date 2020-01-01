/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * Pointing device event definitions.
 */

#ifndef ___GUI_COMMON_POINTEREVENT_H
#define ___GUI_COMMON_POINTEREVENT_H

#include <JkTypes.h>
#include <AMUiEvent.h>

#include <JgCom.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PointerEvent
 * @{
 */

/**
 * The pointer moved (relative coordinates).
 */
#define JG_POINTER_EVT_ENTER        (AM_EVENT_POINTER_EVENT_END + 0x01)

/**
 * The pointer moved (relative coordinates).
 */
#define JG_POINTER_EVT_EXIT         (AM_EVENT_POINTER_EVENT_END + 0x02)

/**
 * The pointer moved (relative coordinates).
 */
#define JG_POINTER_EVT_DRAGGED      (AM_EVENT_POINTER_EVENT_END + 0x03)

/**
 * @internal
 * The maximum pointer event value.
 */
#define JG_POINTER_EVT_END          (AM_EVENT_POINTER_EVENT_END + 0x03)

/**
 * Pointer event
 */
typedef struct JGT_PointerEvent {
    /**
     * The handle of the component generating the event.
     */
    JGCom component;

    /**
     * The generated event (AM_EVENT_POINTER_PRESSED -- JG_POINTER_EVT_DRAGGED)
     */
    JKUint32 type;

    /**
     * Decoding
     */
    JKUint32 buttonNo;

    /**
     * The originating x coordinate
     */
    JKSint32 x;

    /**
     * The originating y coordinate
     */
    JKSint32 y;

} JGT_PointerEvent;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_POINTEREVENT_H */

