/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkOffScreen.h
 * Off-screen Image JSI
 */
/**
 * @addtogroup Off_screen_Image_JSI
 * @{
 */

#ifndef ___JK_OFFSCREEN_H
#define ___JK_OFFSCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkVideoComponent.h"

/**
 * The off-screen buffer handle
 */
typedef JKHandle JKOffScreenHandle;

/**
 * Creates an off-screen buffer of the specified size.
 *
 * @param width
 *        The width of the off-screen buffer
 * @param height
 *        The height of the off-screen buffer
 * @return 
 *        Return a handle identifying the created off-screen buffer, or  #JK_INVALID_HANDLE
 *        if creation failed due to a memory lack or other reason.
 *
 * The created off-screen buffer, like the virtual screen, becomes the object of 
 * drawing operations such as line drawing and rectangle transfer. The memory area 
 * should be readied in a way that facilitates processing by the platform.<br>
 * In the handle identifying the off-screen buffer, keep track of its association with a 
 * pointer to the memory area, it size and other information. 
 * JBlend does not specify the off-screen buffer data format or maximum values for its 
 * dimensions (height and width).
 * 
 * In no case is a value 0 or less designated in the width or height parameter.
 *
 * @see JkOffScreenDispose()
 */
JKOffScreenHandle JkOffScreenCreate( JKSint32 width, JKSint32 height );

/**
 * Disposes of the off-screen buffer.
 *
 * @param hScreen
 *        The handle of the off-screen buffer. This is the value returned by
 *        JkOffScreenCreate().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hScreen parameter.
 *
 * @see JkOffScreenCreate()
 */
void JkOffScreenDispose( JKOffScreenHandle hScreen );

/**
 * Gets the off-screen buffer width.

 *
 * @param hScreen
 *        The handle of the off-screen buffer. This is the value returned by
 *        JkOffScreenCreate().
 * @return 
 *         Return the width of the designated off-screen buffer.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hScreen parameter.
 *
 * @see JkOffScreenCreate
 */
JKSint32 JkOffScreenGetWidth( JKOffScreenHandle hScreen );

/**
 * Gets the off-screen buffer height.
 *
 * @param hScreen
 *        The handle of the off-screen buffer. This is the value returned by
 *        JkOffScreenCreate().
 * @return 
 *         Return the height of the designated off-screen buffer.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hScreen parameter.
 *
 * @see JkOffScreenCreate()
 */
JKSint32 JkOffScreenGetHeight( JKOffScreenHandle hScreen );

/**
 * Gets the data in the designated rectangle in the off-screen buffer, in ARGB format.
 *
 * @param hScreen
 *        The handle of the off-screen buffer. This is the value returned by
 *        JkOffScreenCreate().
 * @param argbData
 *        A pointer to the memory area for putting the initial ARGB data.
 * @param length
 *        The size of the memory area for putting ARGB data.
 *        This parameter is retained for the sake of compatibility. 
 *        The native system does not have to refer to this parameter. 
 * @param scanlen
 *        The number of elements in one row of ARGB data.
 *        A negative value may be passed. 
 * @param bounds
 *        A pointer to the structure holding the rectangular area cut out of the off-screen buffer.
 *
 * This function corresponds to the <code>getRGB</code> method of the Image object created for 
 * off-screen drawing. 
 * <i>argbData</i> is for designating a pointer to the element corresponding to <code>offset</code> in the 
 * array passed to the <code>getRGB</code> method in <code>rgbData</code>.
 * 
 * Following the procedure below, get the data in the rectangle indicated by <i>bounds</i> 
 * in the off-screen buffer designated by <i>hScreen</i>.
 * <ol>
 *  <li>Assume as the write pointer the position indicated by <i>argbData</i>. 
 *  <li>In the location indicated by the write pointer, store the amount of 
 *      off-screen buffer data indicated by <i>bounds->width</i>.
 *  <li>Advance the write pointer by <i>scanlen</i>.
 *  <li>Repeat steps 2 and 3 for <i>bounds->height</i> times.
 * </ol>
 *
 * Assign the fixed value 0xFF to the alpha channel.
 * 
 * The valid range of the memory area for storing the data indicated by 
 * <i>argbData</i> is indicated below. In the native system, be careful 
 * not to write data outside this range.
 * 
 * <dl>
 *  <dd><i>argbData</i> + min ~ <i>argbData</i> + max
 *  <p>
 *  <dt>When a positive value is designated in <i>scanlen</i>
 *  <dd>min = 0
 *  <dd>max = <i>scanlen</i> * (<i>bounds->height</i> - 1) + <i>bounds->width</i> - 1
 *  <dt>When a negative value is designated in <i>scanlen</i>
 *  <dd>min = <i>scanlen</i> * (<i>bounds->height</i> - 1)
 *  <dd>max = <i>bounds->width</i> - 1
 * </dl>
 *  
 * An example of the processing performed in this function is given below. 
 * 
 * @image html JkOffScreenGetARGB_en.gif
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the <i>hImage</i> parameter.
 *  <li>Designating a NULL pointer in the <i>argbData</i> parameter.
 *  <li>Designating an area in the <i>bounds</i> parameter that exceeds the 
 *      area of the off-screen image designated in the <i>hScreen</i> parameter.
 *  <li>Designating a value in <i>scanlen</i> whose absolute value is less than <i>bounds->width</i>.
 * </ul>
 *
 * @see JkOffScreenCreate()
 */
void JkOffScreenGetARGB( JKOffScreenHandle hScreen, JKUint32 *argbData,
                JKSint32 length, JKSint32 scanlen, const JKT_Rect *bounds );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
