/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying the radio button component properties.
 */

#ifndef ___GUI_COMMON_RADIOBUTTON_H
#define ___GUI_COMMON_RADIOBUTTON_H

#include <JkTypes.h>

#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_RadioButton
 * @{
 */

/**
 * @internal
 * The maximum GUI radio button event value.
 */
#define JG_GUI_RDBTN_EVT_END                 (JG_GUI_LSTBX_EVT_END + 0x00)

/**
 * The radio button component type
 * 
 * @see JgComGetComponentType
 */
#define JG_RADIOBUTTON      3

/**
 * The radio button handle
 * 
 * A radio button handle is data identifying the radio button.<br>
 * The radio button handle can be used as a component handle or list handle.
 * 
 * @see JGListBox
 */
typedef JGListBox       JGRadioButton;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_RADIOBUTTON_H */

