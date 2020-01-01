/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   Functions for modifying popup list component properties.
 */

#ifndef ___GUI_COMMON_POPUPLIST_H
#define ___GUI_COMMON_POPUPLIST_H

#include <gui/common/JgList.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_PopupList
 * @{
 */

/**
 * @internal
 *   The maximum PUList event value.
 */
#define JG_GUI_PULST_EVT_END            (JG_GUI_LST_EVT_END + 0x00)

/**
 *   The PUList component type.
 * 
 * @see JgComGetComponentType
 */
#define JG_POPUPLIST     11

/**
 *   The PUList handle.
 *
 *   A PUList handle is data identifying the PUList.
 *   The PUList handle can be used as a component handle.
 * 
 * @see JGList
 */
typedef JGList      JGPopUpList;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_POPUPLIST_H */

