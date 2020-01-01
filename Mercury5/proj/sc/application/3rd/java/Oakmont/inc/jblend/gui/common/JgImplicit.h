/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying IMPLICIT list properties.
 */

#ifndef ___GUI_COMMON_IMPLICITLIST_H
#define ___GUI_COMMON_IMPLICITLIST_H

#include <JkTypes.h>

#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_ImplicitList
 * @{
 */

/**
 * @internal
 * The maximum value for GUI IMPLICIT list events
 */
#define JG_GUI_IMPLICIT_EVT_END                 (JG_GUI_LSTBX_EVT_END + 0x00)

/**
 * The IMPLICIT list component type
 * 
 * @see JgComGetComponentType
 */
#define JG_IMPLICITLIST      7

/**
 * The implicit list handle
 * 
 * An implicit list handle is data identifying the implicit list. <br>
 * The implicit list handle can be used as a component handle or list handle.
 * 
 * @see JGListBox
 */
typedef JGListBox       JGImplicitList;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_IMPLICITLIST_H */

