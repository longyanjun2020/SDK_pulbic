/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkVideoComponent.h
 * Low-Level Graphics Data Types
 */
/**
 * @addtogroup Low_Level_Graphics_Data_Types
 * @{
 */

#ifndef ___JK_VIDEO_COMPONENT_H
#define ___JK_VIDEO_COMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * The color
 */
typedef JKUint32            JKColor;

/**
 * A structure indicating a rectangular area
 *
 * @image html JKT_Rect.gif
 */
typedef struct JKT_Rect {
    /**
     * The top left x coordinate
     */
    JKSint32 x;

    /**
     * The top left y coordinate
     */
    JKSint32 y;

    /**
     * The area width
     */
    JKSint32 width;

    /**
     * The area height
     */
    JKSint32 height;
} JKT_Rect;

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
