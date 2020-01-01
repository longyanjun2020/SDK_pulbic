/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying opened popup list properties.
 */

#ifndef ___GUI_COMMON_POPUPLISTOPENED_H
#define ___GUI_COMMON_POPUPLISTOPENED_H

#include <JkTypes.h>

#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PopupListOpened
 * @{
 */

/**
 * @internal
 * The maximum value for PUListOpened events
 */
#define JG_GUI_PULSTOPENED_EVT_END                 (JG_GUI_LSTBX_EVT_END + 0x00)

/**
 * The PUListOpened component type
 * 
 * @see JgComGetComponentType
 */
#define JG_POPUPLISTOPENED      15

/**
 * The PUListOpened handle
 * 
 * A PUListOpened handle is data identifying the PUListOpened. <br>
 * The PUListOpened handle can be used as a component handle or list handle.
 * 
 * @see JGListBox
 */
typedef JGListBox       JGPopUpListOpened;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_POPUPLISTOPENED_H */

