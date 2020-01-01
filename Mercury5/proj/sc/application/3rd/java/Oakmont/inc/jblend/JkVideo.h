/**
 * Copyright 2002-2006 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkVideo.h
 * Graphics Drawing
 */
/**
 * @addtogroup Graphics_Drawing_JSI
 * @{
 */

#ifndef ___JK_VIDEO2_H
#define ___JK_VIDEO2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/* #include "JkFont.h" */
#include "JkGraphics.h"
/* #include "JkOffScreen.h" */
#include "JkImage.h"
#include "JkVideoComponent.h"

/**
 * Device information
 */
typedef struct JKT_Video_Property {
    /**
     * Off-screen buffer handle, identifying a virtual screen.<br>
     * This value must be a handle indicating the off-screen buffer that can be
     * used.
     */
    JKOffScreenHandle hScreen;

    /**
     * Whether color display is supported or not.<br>
     * This value must be JK_TRUE or JK_FALSE.
     */
    JKBool isColor;

    /**
     * The number of colors.<br>
     * This value must be 2 or greater.
     */
    JKSint32 numColors;

    /**
     * The number of alpha channel levels supported.<br>
     * This value must be between 2 and 256.
     */
    JKSint32 numAlphaLevels;

    /**
     * Existence of a key repeat event.<br>
     * This value must be JK_TRUE or JK_FALSE.
     */
    JKBool hasRepeatEvents;

    /**
     * Existence of a pointer event.<br>
     * This value must be JK_TRUE or JK_FALSE.
     */
    JKBool hasPointerEvents;

    /**
     * Existence of a pointer motion event.<br>
     * This value must be JK_TRUE or JK_FALSE.
     */
    JKBool hasPointerMotionEvents;

    /**
     * Whether wordwrap is required or not.
     * 
     * This member is defined for keeping backward compatibility and is not used currently. 
     */
    JKBool wordwrap;

    /**
     * The number of soft keys.<br>
     * This value must be 0 or greater.
     */
    JKSint32 numSoftkeys;

} JKT_Video_Property;

/**
 * Gets the video device properties.
 *
 * @param property
 *        The memory location for the video device information (allocated by JBlend)
 *
 * If the property settings do not match the actual platform specifications,
 * a Java application may behave in unexpected ways.
 */
void JkVideoGetProperty( JKT_Video_Property *property );

/**
 * Performs color reduction processing.
 *
 * @param color
 *        The original color (24-bit color)
 * @return
 *         The color after reduction (24-bit color)
 *
 * This function is used to check the color that will be displayed on the screen
 * when color reduction processing is applied to the color designated by the color
 * parameter.
 * If the system does not require color reduction, return the original value
 * unchanged.
 * If the display does not support 24-bit color but the system reduces the bit
 * count in color reduction processing, return a result obtained by reducing
 * the number of bits and then calculating the equivalent in 24-bit color.
 */
JKColor JkVideoGetReducedColor( JKColor color );



/**
 * Starts drawing on the virtual screen.
 *
 * From the time this function is called and until JkVideoEndPaintOnVirtual() is called,
 * drawing takes place on the virtual screen. During this time, drawing can be taking
 * place in other off-screen buffers as well.<br>
 * If exclusive control is necessary for the processing requested by the JVM task and
 * that by other tasks, implement to suppress draw processing by tasks other than the JVM
 * between the time this function is called and JkVideoEndPaintOnVirtual() is called.
 *
 * @see JkVideoEndPaintOnVirtual()
 */
void JkVideoBeginPaintOnVirtual( void );

/**
 * Ends drawing on the virtual screen.
 *
 * @param   bFlush
 *          When this flag is JK_FALSE, do not transfer the virtual screen contents to the real screen.
 *
 * Once this function completes its processing, treat drawing in the virtual screen
 * as temporarily stopped and send the drawing result to the real screen.
 * It is also possible to remember the area updated between the time
 * JkVideoBeginPaintOnVirtual() was called and this function was called, and to
 * update only that area. During this time, drawing can be taking place in other
 * off-screen buffers as well.
 *
 * @see JkVideoBeginPaintOnVirtual()
 */
void JkVideoEndPaintOnVirtual( JKBool bFlush );

/**
 * Draws a straight line joining two points.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param x1
 *        The starting x coordinate for the drawing.
 * @param y1
 *        The starting y coordinate for the drawing.
 * @param x2
 *        The ending x coordinate for the drawing.
 * @param y2
 *        The ending y coordinate for the drawing.
 *
 * Draw a straight line connecting the points (x1,y1) and (x2,y2) as illustrated.<br>
 * Use the line style setting of the graphics context.<br>
 * If the designated coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 *
 * In no case is a #JK_INVALID_HANDLE designated in the g parameter.
 * @image html DrawLine.gif
 */
void JkVideoDrawLine( JKGraphicsContext g, JKSint32 x1, JKSint32 y1,
                        JKSint32 x2, JKSint32 y2 );

/**
 * Draws a rectangle, but does not fill it.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The position and size of the rectangle to be drawn
 *
 * The coordinates, width and height are designated as in the figure below.
 * The pixels just inside lines along a rectangle having the four coordinates
 * (x,y), (x+width,y), (x+width, y+height), and (x, y+height) as vertices should
 * be set to the designated color. The pixel counts for the width and height of
 * the resulting rectangle will then be <_em>width+1</_em> and <_em>height+1</_em>, respectively.<br>
 * Use the line style setting of the graphics context.
 *
 * If the designated rectangle coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value less than 0 in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 * </ul>
 * @image html DrawRect.gif
 */
void JkVideoDrawRect( JKGraphicsContext g, const JKT_Rect *bounds );

/**
 * Draws and fills a rectangle.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The position and size of the rectangle to be drawn
 *
 * The coordinates, width and height are designated as in the figure below.
 * All the pixels enclosed by lines along a rectangle having the four coordinates
 * (x,y), (x+width,y), (x+width, y+height), and (x, y+height) as vertices should be
 * painted with the designated color. The pixel counts for the width and height of the
 * resulting rectangle are <_em>width</_em> and <_em>height</_em>, respectively.<br>
 *
 * If the designated rectangle coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value <_em>less or 0</_em> in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 * </ul>
 * @image html FillRect.gif
 */
void JkVideoFillRect( JKGraphicsContext g, const JKT_Rect *bounds );

/**
 * Draws a rounded rectangle, but does not fill it.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The bounding rectangle
 * @param arcW
 *        The horizontal rounding diameter
 * @param arcH
 *        The vertical rounding diameter
 *
 * The relation of bounds to arcW and arcW is as shown in the figure.
 * The pixels just inside rounded-corner lines bounded by a rectangle having the four
 * coordinates (x,y), (x+width,y), (x+width, y+height), and (x, y+height) as vertices
 * should set to the designated color. The pixel counts for the width and height of the
 * resulting rectangle are <_em>width+1</_em> and <_em>height+1</_em>, respectively.<br>
 * Use the line style setting of the graphics context.
 *
 * If the designated rectangle coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.<br>
 * If a value of <_em>0</_em> is designated for either arcW and arcH, draw using
 * a value of 0 for both arcW and arcH.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value <_em>less than 0</_em> in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 *  <li>Designating a value <_em>less than 0</_em> in the arcW parameter or arcH parameter.
 * </ul>
 * @image html DrawRoundRect.gif
 */
void JkVideoDrawRoundRect( JKGraphicsContext g, const JKT_Rect *bounds,
                            JKSint32 arcW, JKSint32 arcH );

/**
 * Draws and fills a rounded rectangle.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The bounding rectangle
 * @param arcW
 *        The horizontal rounding diameter
 * @param arcH
 *        The vertical rounding diameter
 *
 * The relation of bounds to arcW and arcH is the same as for JkVideoDrawRoundRect().
 * All the pixels enclosed by rounded-corner lines bounded by a rectangle having
 * the four coordinates (x,y), (x+width,y), (x+width, y+height), and (x, y+height)
 * as vertices should be painted with the designated color. The pixel counts for the
 * width and height of the resulting rectangle are <_em>width</_em> and <_em>height</_em>, respectively.
 *
 * If the designated rectangle coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.<br>
 * If a value of 0 is designated for either arcW and arcH, draw using
 * a value of 0 for both arcW and arcH.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value of <_em>0 or less</_em> in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 *  <li>Designating a value <_em>less than 0</_em> in the arcW parameter or arcH parameter.
 * </ul>
 */
void JkVideoFillRoundRect( JKGraphicsContext g, const JKT_Rect *bounds,
                            JKSint32 arcW, JKSint32 arcH );

/**
 * Draws a character string.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param string
 *        A pointer to the character string to be drawn, given as Unicode
 * @param length
 *        The number of characters in the designated character string
 * @param x
 *        The x coordinate for drawing
 * @param y
 *        The y coordinate for drawing
 *
 * If the designated coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.<br>
 * Do not wrap the character string in the clip area even if the string drawing width
 * extends outside the clip area.
 * If the string contains a character not defined in the platform, substitute a blank
 * space or '?' or the like for that character when drawing. The substitute character is
 * platform dependent.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a NULL pointer in the string parameter.
 *  <li>Designating a value <_em>less than 0</_em> in the length parameters.
 * </ul>
 */
void JkVideoDrawString( JKGraphicsContext g, const JKWChar *string,
                        JKSint32 length, JKSint32 x, JKSint32 y );

/**
 * Draws an arc, but does not fill it.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The rectangle inscribing the ellipse of which the arc is a part
 * @param startAngle
 *        The angle (degree) from which to start drawing the arc (in counter-clockwise
 *        direction, with 0 as 3 o'clock)
 * @param endAngle
 *        The angle (degree) at which to end the arc drawing (in counter-clockwise
 *        direction, with 0 as 3 o'clock)
 *
 * The relation among bounds, startAngle and endAngle are as shown in the figure.
 * In this figure, the pixels just inside a line along an arc from the start and end
 * positions on the ellipse are set to the designated color. The pixel counts for width
 * and height of the ellipse drawn when startAngle is 0 and endangle is 360 are <_em>w+1</_em>
 * and <_em>h+1</_em>, respectively.<br>
 * Use the line style setting of the graphics context.
 *
 * If the designated arc coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value <_em>less than 0</_em>in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 * </ul>
 * The range of the startAngle and endAngle parameters is 0 to 360 degrees in
 * the counterclockwise direction.
 * @image html DrawArc.gif
 */
void JkVideoDrawArc( JKGraphicsContext g, const JKT_Rect *bounds,
                        JKSint32 startAngle, JKSint32 endAngle );

/**
 * Draws and fills an arc.
 * Angles are given in degrees counterclockwise from the first quadrant as the origin.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param bounds
 *        The rectangle inscribing the ellipse of which the arc is a part
 * @param startAngle
 *        The angle (degree) from which to start drawing the arc (in counter-clockwise
 *        direction, with 0 as 3 o'clock)
 * @param endAngle
 *        The angle (degree) at which to end the arc drawing (in counter-clockwise
 *        direction, with 0 as 3 o'clock)
 *
 * The relation among bounds, startAngle and endAngle are as shown in the figure.
 * In this figure, the pixels enclosed by an arc from the start and end positions on
 * the ellipse and the center of the ellipse are painted with the designated color.
 * The pixel counts for width and height of the filled ellipse when startAngle is 0
 * and endangle is 360 are w and h, respectively.
 *
 * If the designated arc coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a value of <_em>0 or less</_em> in the width member or height member of the JKT_Rect structure indicated by the bounds parameter.
 * </ul>
 * The range of the startAngle and endAngle parameters is 0 to 360 degrees in
 * the counterclockwise direction.
 * @image html FillArc.gif
 */
void JkVideoFillArc( JKGraphicsContext g, const JKT_Rect *bounds,
                        JKSint32 startAngle, JKSint32 endAngle );

/**
 * Draws with no transformation.
 */
#define JK_VIDEO_TRANS_NONE             0


/**
 * Draws flipping the image horizontally then rotating 180 degrees.
 */
#define JK_VIDEO_TRANS_MIRROR_ROT180    1

/**
 * Draws flipping the image horizontally.
 */
#define JK_VIDEO_TRANS_MIRROR           2

/**
 * Draws rotating the image 180 degrees.
 */
#define JK_VIDEO_TRANS_ROT180           3

/**
 * Draws flipping the image horizontally then rotating 270 degrees.
 */
#define JK_VIDEO_TRANS_MIRROR_ROT270    4

/**
 * Draws rotating the image 90 degrees.
 */
#define JK_VIDEO_TRANS_ROT90            5

/**
 * Draws rotating the image 270 degrees.
 */
#define JK_VIDEO_TRANS_ROT270           6

/**
 * Draws flipping the image horizontally then rotating 90 degrees.
 */
#define JK_VIDEO_TRANS_MIRROR_ROT90     7


/**
 * Draws an immutable image.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param hImage
 *        The handle of the immutable image to be drawn. This is the value returned by
 *        JkImageCreate().
 * @param x
 *        The x coordinate for drawing
 * @param y
 *        The y coordinate for drawing
 * @param trans
 *        The drawing orientation, designated as JK_VIDEO_TRANS_XXXX
 *
 *   Draw the designated immutable image, flipping and rotating it. The direction of
 *   rotation is clockwise.
 *  If the designated coordinates are outside the clip area set for the graphics context,
 *  draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g or hImage parameter.
 *  <li>Designating a values other than constants named starting with "JK_VIDEO_TRANS_" in the trans parameter.
 * </ul>
 *
 * @see JkImageCreate()
 */
void JkVideoDrawImage( JKGraphicsContext g, JKImageHandle hImage,
                        JKSint32 x, JKSint32 y, JKSint32 trans );

/**
 * Draws an off-screen image.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext()
 * @param hScreen
 *        The handle of the off-screen buffer. This is the value returned by
 *        JkOffScreenCreate().
 * @param x
 *        The x coordinate for drawing
 * @param y
 *        The y coordinate for drawing
 * @param trans
 *        The drawing orientation, as designated in JK_VIDEO_TRANS_XXXX
 *
 *   Draw the designated off-screen image, flipping and rotating it. The direction of
 *   rotation is clockwise.
 *  If the designated coordinates are outside the clip area set for the graphics context,
 *  draw only the portion inside the clip area.
 *  
 *  The off-screen which was designated when the graphics context <i>g</i>
 *  was created can be passed in the <i>hScreen</i> parameter. In this case, 
 *  #JK_VIDEO_TRANS_NONE is passed in the <i>trans</i> parameter.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g or hScreen parameter.
 *  <li>Designating a values other than constants named starting with "JK_VIDEO_TRANS_" in the trans parameter.
 * </ul>
 *
 * @see JkOffScreenCreate()
 */
void JkVideoDrawOffScreen( JKGraphicsContext g, JKOffScreenHandle hScreen,
                        JKSint32 x, JKSint32 y, JKSint32 trans );

/**
 * Draws an off-screen image to screen directly.
 * 
 * @param hImage
 *     The handle of the Image want to be display on the screen.
 * @param newClip
 *     The clip region on the image , Only the clip region will be display on screen directly.
 * @param bPending
 *     To check if the image is flushed on the screen, if (*bPending)==0 , the flushing is finished , else is pended.
 * @see JkOffScreenCreate()
 */
 
void JkVideoDrawOffScreenDirectly( JKOffScreenHandle hImage, const JKT_Rect *newClip,int* bPending);


/**
 * To check is the last drawing flush is still pending, if there are no pending flush request return 0 ,else return pengding count.
 * @see JkVideoDrawOffScreenDirectly()
 */
 
int JkVideoIsDrawOffScreenDirectlyPending(void);

/**
 * Draws a filled polygon.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext().
 * @param x
 *        Array of polygon vertex x coordinates
 * @param y
 *        Array of polygon vertex y coordinates
 * @param num
 *        The number of polygon coordinates.
 *        Only 3 coordinates are designated.
 *
 * If fewer than 3 coordinates are designated, do not perform any drawing.
 * If the designated polygon coordinates are outside the clip area designated for the
 * graphics context, draw only the portion inside the clip area.
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a NULL pointer in the x or y parameters.
 * </ul>
 */
void JkVideoFillPolygon( JKGraphicsContext g, const JKSint32 *x,
                                const JKSint32 *y, JKSint32 num );

/**
 * Draws ARGB data.
 *
 * @param g
 *        The handle of the graphics context. This is the value returned by #JkGraphicsCreateContext().
 * @param argbData
 *        A pointer to the memory holding the initial ARGB data to be drawn. 
 * @param length
 *        The size of the memory area holding the ARGB data to be drawn. 
 *        A multiple of the <i>scanlen</i> absolute value is designated.
 * @param scanlen
 *        The number of elements in one row of ARGB data to be drawn.
 *        A negative value may be passed.
 * @param x
 *        The x coordinate for drawing
 * @param y
 *        The y coordinate for drawing
 * @param processAlpha
 *        Use of alpha channel (JK_TRUE if used)
 *
 * This function corresponds to the <code>javax.microedition.lcdui.Graphics</code> 
 * class <code>drawRGB</code> method.
 * <i>argbData</i> is for designating a pointer to the element corresponding to 
 * <code>offset</code> in the array passed to the <code>getRGB</code> method in <code>rgbData</code>.
 * 
 * Following the procedure below, draw the ARGB data designated in <i>argbData</i> 
 * at the position indicated by <i>x</i> and <i>y</i>.
 * <ol>
 *  <li>Assume as the read pointer the position indicated by <i>argbData</i>.
 *  <li>Of the data extending from the read position up to a length of <i>scanlen</i>, 
 *     read and draw one row of data located inside the clip region.
 *  <li>Advance the read pointer by <i>scanlen</i>.
 *  <li>Keep repeating steps 2 and 3 until <i>length</i> data has been processed.
 * </ol>
 * The width and height of the image to be drawn are as follows. 
 * 
 * height = <i>length</i> / |<i>scanlen</i>|<br>
 * width = |<i>scanlen</i>|
 * 
 * The valid range of the memory area holding ARGB data is indicated below. 
 * In the native system, be careful not to read data outside this range. 
 * 
 * <dl>
 *  <dd><i>argbData</i> + min ~ <i>argbData</i> + max
 *  <p>
 *  <dt>When a positive value is designated in <i>scanlen</i>
 *  <dd>min = 0
 *  <dd>max = <i>scanlen</i> * (height - 1) + width - 1
 *  <dt>When a negative value is designated in <i>scanlen</i>
 *  <dd>min = <i>scanlen</i> * (height - 1) 
 *  <dd>max = width - 1
 * </dl>
 * 
 * An example of the processing performed in this function is given below. 
 * 
 * @image html JkVideoDrawRegionARGBImage_en.gif
 * 
 * 
 * If the designated coordinates are outside the clip area set for the graphics context,
 * draw only the portion inside the clip area.
 * Be careful not to access memory space for pixel data located outside the range of this clip region. 
 * 
 * In the example indicated below, a clip region is set in the graphics context 
 * described in the earlier example where <i>scanlen</i>=5.
 * 
 * @image html JkVideoDrawRegionARGBImage2_en.gif
 * 
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the g parameter.
 *  <li>Designating a NULL pointer in the <i>argbData</i> parameter.
 *  <li>Designating a value of <_em>0 or less</_em> in the <i>length</i> parameter.
 * </ul>
 */
void JkVideoDrawRegionARGBImage( JKGraphicsContext g,
                const JKSint32 *argbData, JKSint32 length, JKSint32 scanlen,
                JKSint32 x, JKSint32 y, JKBool processAlpha );


/**
 * Normal screen mode
 */
#define JK_VIDEO_SCREEN_NORMAL      0

/**
 * Full-screen mode
 */
#define JK_VIDEO_SCREEN_FULL        1

/**
 * Switches modes of the virtual screen size available to Java.
 *
 * @param screenMode
 *        The screen mode (JK_VIDEO_SCREEN_XXXX).
 * @return
 *         Return #JK_TRUE if the mode switch succeeded, or #JK_FALSE if it failed.
 *
 * JBlend assumes that the virtual screen size will change when the screen mode is
 * switched by this function. The native system must perform the following processing 
 * depending on how this function is implemented. 
 * 
 * <dl>
 *  <dt> When the virtual screen offscreen buffer is recreated in this function 
 *  <dd>
 *   - If prior to recreating there is a graphics context using the virtual screen offscreen 
 *     buffer as object of drawing, switch the object of drawing of the graphics context to 
 *     the recreated buffer. 
 *   - If JkVideoGetProperty() is called after changing the screen mode by this function, set 
 *     the handle of the recreated offscreen buffer in the <i>hScreen</i> member of the 
 *     JKT_Video_Property structure for setting video device information.
 *   .
 *  
 *  <p>
 *  <dt> When the virtual screen offscreen buffer is not recreated in this function
 *  <dd>
 *   - If JkVideoGetProperty() is called after changing the screen mode by this function, 
 *     enable the width and height to be acquired in accord with the screen mode passed 
 *     to this function.
 *   .
 * </dl>
 *
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating a value other than constants named starting with "JK_VIDEO_SCREEN_" in the screenMode parameter.
 * </ul>
 *
 * @see JkVideoGetProperty()
 */
JKBool JkVideoRequestScreenMode( JKSint32 screenMode );


/**
 * No Displayable set
 *
 * This means that a null object was passed to <code>setCurrent()</code>.
 */
#define JK_VIDEO_DISPLAYABLE_NULL        0

/**
 * Screen type set
 *
 * This means that a Screen object was passed to <code>setCurrent()</code>.
 */
#define JK_VIDEO_DISPLAYABLE_SCREEN      1

/**
 * Canvas type set
 *
 * This means that a Canvas object was passed to <code>setCurrent()</code>.
 */
#define JK_VIDEO_DISPLAYABLE_CANVAS      2

/**
 * Permission Confirmation Dialog is displayed
 *
 * This means that displaying the Permission Confirmation Dialog.
 */
#define JK_VIDEO_DISPLAYABLE_PERMISSIONDIALOG      4

/**
 * Platform screen is displayed
 *
 * This means that a native system screen is displayed.
 */
#define JK_VIDEO_DISPLAYABLE_PLATFORM      5

/**
 * GameCanvas screen is displayed
 *
 * This means that a GameCanvas object was passed to <code>setCurrent()</code>. 
 */
#define JK_VIDEO_DISPLAYABLE_GAMECANVAS    6

/**
 *  Sets the type of the current Displayable displayed by the Java application.
 *
 * @param displayableType One of the Displayable types defined in 
 *          <ul>
 *           <li> #JK_VIDEO_DISPLAYABLE_NULL
 *           <li> #JK_VIDEO_DISPLAYABLE_SCREEN
 *           <li> #JK_VIDEO_DISPLAYABLE_CANVAS
 *           <li> #JK_VIDEO_DISPLAYABLE_PERMISSIONDIALOG
 *           <li> #JK_VIDEO_DISPLAYABLE_PLATFORM
 *           <li> #JK_VIDEO_DISPLAYABLE_GAMECANVAS
 *          </ul>
 * <p>
 * This function is called when a Java application has changed the current 
 * <code>Displayable</code> by calling <code>javax.microedition.lcdui.Display</code>
 * class <code>setCurrent(Displayable)</code> method, or when JBlend 
 * displays a permission confirmation dialg.
 * 
 * If no use is made of the information designated in this function for drawing or other
 * purposes, it may be implemented as an empty function.
 * 
 */
void JkVideoSetDisplayableType( JKSint32 displayableType );


#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
