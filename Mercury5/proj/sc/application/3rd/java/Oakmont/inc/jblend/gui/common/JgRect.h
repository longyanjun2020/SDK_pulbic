/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   API functions for rectangle.
 */

#ifndef ___GUI_COMMON_RECT_H
#define ___GUI_COMMON_RECT_H

#include <JkVideoComponent.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_Rectangle
 * @{
 */

/**
 * Checks if a rectangle contains a designated point.
 * 
 * @param rect A pointer to the rectangle.
 * @param x    The x coordinate of the point.
 * @param y    The y coordinate of the point.
 * @return     JK_TRUE if the point (x, y) is inside the designated rectangle; 
 *             JK_FALSE otherwise.
 *             If the width or height of the designated rectanlge is 
 *             a negative value, JK_FALSE is returned.
 *
 * The point means a position specified by coordinates.
 * The rectangle with upper-left corner (0, 0) with width and height 4 and 4, contains
 * points located at the upper-left coordinates of the white circles and balck 
 * circles in the figure below; thus, points of (0, 0) through (4, 4) are contained
 * in that rectangle.
 *
 * @image html JgRectContainsPoint.gif
 */
JKBool JgRectContainsPoint(const JKT_Rect *rect, JKSint32 x, JKSint32 y);

/**
 * Checks if a rectangle entirely contains another rectangle.
 *   
 * @param rect1 A pointer to a #JKT_Rect structure storing the rectangle 1.
 * @param rect2 A pointer to a #JKT_Rect structure storing the rectangle 2.
 * @return      #JK_TRUE if the rectangle 1 entirely contains the rectangle 2; 
 *              #JK_FALSE otherwise
 *              If width or height of the designated rectanlges is
 *              a negative value, JK_FALSE is returned.
 *
 * The rectangle with upper-left corner (0, 0) with width and height 4 and 4, contains
 * rectangles that fits in the white circles indicated in the figure below.
 * For example, the rectangle indicated by the black circle in the figure, 
 * i.e. the rectangle with upper-left corner (4, 4) with width and height 1 and 1,
 * is considered not contained in the white circle area.
 * @image html JgRectContains.gif
 */
JKBool JgRectContains(const JKT_Rect *rect1, const JKT_Rect *rect2);

/**
 * Checks if a rectangle intersects other rectangle.
 *   
 * @param rect1 A pointer to a #JKT_Rect structure storing the rectangle 1.
 * @param rect2 A pointer to a #JKT_Rect structure storing the rectangle 2.
 * @return      JK_TRUE if the designated two rectangles intersect each other; 
 *              JK_FALSE otherwise.
 *              If width or height of the designated rectanlges is
 *              a negative value, JK_FALSE is returned.
 *
 * When only the borders of the rectangles intersect, this function returns JK_FALSE.
 * However, in that case, if the width or the height of the rectangle is 0, this function returns JK_TRUE.
 */
JKBool JgRectIntersects(const JKT_Rect *rect1, const JKT_Rect *rect2);

/**
 *   Computes the intersection of two rectangles.
 *   
 *   @param rect1 A pointer to a #JKT_Rect structure storing the rectangle 1.
 *                The result of computation is stored to this memory area.
 *   @param rect2 A pointer to a #JKT_Rect structure storing the rectangle 2.
 *
 *   If the width or height of the rectangle indicated by the rect1 parameter 
 *   is a negative value, the 
 *   memory area pointed by rect1 does not change regardless of the 
 *   rectangle indicated by the rect2 parameter.
 *
 *   If the width or height of the rectangle indicated by the rect2 parameter 
 *   is a negative value, 
 *   the x and y members of the structure are not changed; 
 *   the width and height are set to 0.
 */
void JgRectIntersection(JKT_Rect *rect1, const JKT_Rect *rect2);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_RECT_H */

