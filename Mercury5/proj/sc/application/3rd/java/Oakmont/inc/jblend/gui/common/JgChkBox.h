/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for modifying checkbox properties.
 */

#ifndef ___GUI_COMMON_CHECKBOX_H
#define ___GUI_COMMON_CHECKBOX_H

#include <JkTypes.h>

#include <gui/common/JgListBox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_CheckBox
 * @{
 */

/**
 * @internal
 * The maximum GUI checkbox event value.
 */
#define JG_GUI_CKBX_EVT_END                 (JG_GUI_LSTBX_EVT_END + 0x00)

/**
 * The checkbox component type.
 * 
 * @see JgComGetComponentType
 */
#define JG_CHECKBOX       2

/**
 * The checkbox handle.
 * 
 * A checkbox handle is data identifying the checkbox.<br>
 * The checkbox handle can be used as a component handle or list handle.
 * 
 * @see JGListBox
 */
typedef JGListBox       JGChkBox;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_CHECKBOX_H */

