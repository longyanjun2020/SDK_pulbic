/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkGraphics.h
 * Graphics Context JSI
 */
/**
 * @addtogroup Graphics_Context_JSI
 * @{
 */

#ifndef ___JK_GRAPHICS_H
#define ___JK_GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

#include "JkFont.h"
#include "JkOffScreen.h"
#include "JkVideoComponent.h"

/**
 * Normal line
 */
#define JK_GRAPHICS_LINE_STYLE_NORMAL       0

/**
 * Dotted line (spacing between dots is implementation-dependent)
 */
#define JK_GRAPHICS_LINE_STYLE_DOTTED       1

/**
 * A handle identifying the graphics context
 */
typedef JKHandle JKGraphicsContext;

/**
 * Creates a graphics context.
 *
 * @param hScreen
 *        The handle of the off-screen buffer for the graphics context
 * @return 
 *         Return the handle of the created graphics context, or  #JK_INVALID_HANDLE
 *         if it could not be created.
 *
 *  Create a graphics context for the off-screen buffer designated in the hScreen parameter.
 *  The graphics context should hold the following as drawing information.
 *  <ul>
 *   <li>Font
 *   <li>Drawing color
 *   <li>Line style
 *   <li>Clip area
 *  </ul>
 *  All the following settings should have been made at the time of creation.
 *  <ul>
 *   <li> #JkGraphicsSetFont(g, #JkFontGetDefault( #JK_FONT_TYPE_DEFAULT))
 *   <li> #JkGraphicsSetColor(g, 0)
 *   <li> #JkGraphicsSetLineStyle(g, #JK_GRAPHICS_LINE_STYLE_NORMAL)
 *  </ul>
 *  Set the entire area of the designated off-screen buffer as the clip area at 
 *  the time the graphics context is created.<br>
 *  Allow the creation of multiple contexts for one off-screen buffer handle, without
 *  setting an upper limit for the number of graphics contexts that can be created.
 *
 * @see JkGraphicsDisposeContext()
 * @see JkGraphicsSetFont()
 * @see JkGraphicsSetColor()
 * @see JkGraphicsSetLineStyle()
 * @see JkFontGetDefault()
 */
JKGraphicsContext JkGraphicsCreateContext( JKOffScreenHandle hScreen );

/**
 * Disposes of a graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 *
 * @see JkGraphicsCreateContext()
 */
void JkGraphicsDisposeContext( JKGraphicsContext g );

/**
 * Gets the font set for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @return 
 *        Return a handle indicating the font set for the graphics context.
 *        The handle indicating a font is the value that was returned by 
 *        JkFontGetDefault() or JkFontCreate()).
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 *
 * @see JkGraphicsCreateContext()
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKFontHandle JkGraphicsGetFont( JKGraphicsContext g );

/**
 * Sets the font for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @param hFont
 *        The handle indicating the font to be set. This is the value returned by
 *        JkFontGetDefault() or JkFontCreate().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 *
 * @see JkGraphicsCreateContext()
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
void JkGraphicsSetFont( JKGraphicsContext g, JKFontHandle hFont );

/**
 * Gets the drawing color set for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @return 
 *         Return the drawing color (24-bit color) set for the graphics context.
 *
 * If the drawing color set for the graphics context is color-reduced by the platform, 
 * convert it to 24-bit color by any workable method and return the resulting value.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 * 
 * @see JkGraphicsCreateContext()
 */
JKColor JkGraphicsGetColor( JKGraphicsContext g );

/**
 * Sets the drawing color for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @param newColor
 *        The new drawing color.
 *
 * Designate as a 24-bit color. Perform color reduction as appropriate for the system.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 * 
 * @see JkGraphicsCreateContext()
 */
void JkGraphicsSetColor( JKGraphicsContext g, JKColor newColor );

/**
 * Gets the line style set for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @return 
 *        Return the line style (JK_GRAPHICS_LINE_STYLE_XXXX) set for the graphics context.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the g parameter.
 * 
 * @see JkGraphicsCreateContext()
 */
JKSint32 JkGraphicsGetLineStyle( JKGraphicsContext g );

/**
 * Set the line style for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @param newLineStyle
 *        The new line style (JK_GRAPHICS_LINE_STYLE_XXXX).
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a values other than constants named starting with "JK_GRAPHICS_LINE_STYLE_" in the newLineStyle parameter.
 * </ul>
 * 
 * @see JkGraphicsCreateContext()
 */
void JkGraphicsSetLineStyle( JKGraphicsContext g, JKSint32 newLineStyle );

/**
 * Gets the clip area set for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @param clip
 *        The memory location of the clip area setting for the graphics context.
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a NULL pointer in the clip parameter.
 * </ul>
 * 
 * @see JkGraphicsCreateContext()
 */
void JkGraphicsGetClip( JKGraphicsContext g, JKT_Rect *clip );

/**
 * Sets the clip area for the graphics context.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by 
 *        JkGraphicsCreateContext()
 * @param newClip
 *        The new clip area
 *
 * A rectangle that fits inside the drawing area of the graphics context is 
 * designated as the clip area. 
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a NULL pointer in the newClip parameter.
 * </ul>
 * 
 * @see JkGraphicsCreateContext()
 */
void JkGraphicsSetClip( JKGraphicsContext g, const JKT_Rect *newClip );



#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
