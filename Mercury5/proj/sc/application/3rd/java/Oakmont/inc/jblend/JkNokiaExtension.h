/**
 * Copyright 2008 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkNokiaExtension.h
 * Nokia UI Extension JSI
 */

#ifndef ___JK_NOKIAEXSIONSION_H
#define ___JK_NOKIAEXSIONSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 * @defgroup DirectGraphics_JSI DirectGraphics JSI
 * An interface for performing graphics rendering features.
 *
 * This interface is used for implementing the features of the <code>com.nokia.mid.ui.DirectGraphics</code> interface.
 *
 * The interface defined here must be implemented by the developer incorporating JBlend into the target device.
 *
 * @par Header File
 * JkNokiaExtension.h
 * @{
 */

/**
 * @name Pixel Format
 * @anchor nokia_ui_pixel_format
 * Pixel format values for use in the following functions:
 * - JkNokiaGetNativePixelFormat()
 * - JkNokiaGetSupportedPixelFormat()
 * - JkNokiaDrawPixelsInt(), JkNokiaDrawPixelsByte(), JkNokiaDrawPixelsShort()
 * - JkNokiaGetPixelsInt(), JkNokiaGetPixelsByte(), JkNokiaGetPixelsShort()
 * .
 * @{
 */
/**
 * Pixel format: 1 bit format, 2 distinct color values (on/off), stored as a byte.\ 8 pixel values in a single byte, packed as closely as possible. 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_1_GRAY</code>.
 */
#define JK_NOKIA_BYTE_1_GRAY 1 
/**
 * Pixel format: 1 bit format, 2 distinct color values (on/off), stored as a byte.\ 8 vertical pixel values are stored in a single byte. 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_1_GRAY_VERTICAL</code>.
 */
#define JK_NOKIA_BYTE_1_GRAY_VERTICAL -1 
/**
 * Pixel format: 2 bit format, 4 gray scale colors. 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_2_GRAY</code>.
 */
#define JK_NOKIA_BYTE_2_GRAY 2 
/**
 * Pixel format: 3 bits for red, 3 bits for green, and 2 bits for blue component in a pixel, stored as a byte.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_332_RGB</code>.
 */
#define JK_NOKIA_BYTE_332_RGB 332 
/**
 * Pixel format: 4 bit format, 16 gray scale colors.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_1_GRAY</code>.
 */
#define JK_NOKIA_BYTE_4_GRAY 4 
/**
 * Pixel format: 8 bit format, 256 gray scale colors.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_BYTE_8_GRAY</code>.
 */
#define JK_NOKIA_BYTE_8_GRAY 8 
/**
 * Pixel format: 8 bits for red, green and blue component in a pixel (0x00RRGGBB). 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_INT_888_RGB</code>.
 */
#define JK_NOKIA_INT_888_RGB 888 
/**
 * Pixel format: 8 bits for alpha, red, green and blue component in a pixel (0xAARRGGBB). 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_INT_8888_ARGB</code>.
 */
#define JK_NOKIA_INT_8888_ARGB 8888 
/**
 * Pixel format: 1 bit for alpha, 5 bits for red, green and blue component in a pixel.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_USHORT_1555_ARGB</code>.
 */
#define JK_NOKIA_USHORT_1555_ARGB 1555 
/**
 * Pixel format: 4 bits for red, green and blue component in a pixel, stored as a short (0x0RGB). 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_USHORT_444_RGB</code>.
 */
#define JK_NOKIA_USHORT_444_RGB 444 
/**
 * Pixel format: 4 bits for alpha, red, green and blue component in a pixel, stored as a short (0xARGB). 
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_USHORT_4444_ARGB</code>.
 */
#define JK_NOKIA_USHORT_4444_ARGB 4444 
/**
 * Pixel format: 5 bits for red, green and blue component in a pixel.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_USHORT_555_RGB</code>.
 */
#define JK_NOKIA_USHORT_555_RGB 555 
/**
 * Pixel format: 5 bits for red, 6 bits for green and 5 bits for blue component in a pixel.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.TYPE_USHORT_565_RGB</code>.
 */
#define JK_NOKIA_USHORT_565_RGB 565 
/** @} Pixel Format */

/**
 * @name Image Manipulation
 * @anchor nokia_ui_manipulation
 * Pixel format values for use in the <i>manipulation</i> parameter to the following functions:
 * - JkNokiaDrawPixelsInt(), JkNokiaDrawPixelsByte(), JkNokiaDrawPixelsShort()
 * .
 * @{
 */
/**
 * Image Manipulation: Horizontal image flipping.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.FLIP_HORIZONTAL</code>.
 */
#define JK_NOKIA_FLIP_HORIZONTAL 0x2000 
/**
 * Image Manipulation: Vertical image flipping.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.FLIP_VERTICAL</code>.
 */
#define JK_NOKIA_FLIP_VERTICAL 0x4000 
/**
 * Image Manipulation: Rotate an image 90 degrees counter-clockwise.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.ROTATE_90</code>.
 */
#define JK_NOKIA_ROTATE_90 90 
/**
 * Image Manipulation: Rotate an image 180 degrees counter-clockwise.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.ROTATE_180</code>.
 */
#define JK_NOKIA_ROTATE_180 180  
/**
 * Image Manipulation: Rotate an image 270 degrees counter-clockwise.
 * Corresponds to <code>com.nokia.mid.ui.DirectGraphics.ROTATE_270</code>.
 */
#define JK_NOKIA_ROTATE_270 270  
/** @} Image Manipulation */

/** @} DirectGraphics JSI */

/**
 * @defgroup Nokia_Sound_JSI Sound JSI
 * An interface for retrieving sound playback capability of the native system.
 *
 * This interface is used for implementing the features of the <code>com.nokia.mid.sound.Sound</code> class.
 *
 * The interface defined here must be implemented by the developer incorporating JBlend into the target device.
 *
 * @par Header File
 * JkNokiaExtension.h
 * @{
 */
/**
 * Audio type: Tone.
 *
 * Corresponds to <code>com.nokia.mid.sound.Sound.FORMAT_TONE</code>.
 */
#define JK_NOKIA_FORMAT_TONE 1
/**
 * Audio type: WAV.
 *
 * Corresponds to <code>com.nokia.mid.sound.Sound.FORMAT_WAV</code>.
 */
#define JK_NOKIA_FORMAT_WAV  5
/** @} Sound JSI */

/**
 * @addtogroup DirectGraphics_JSI DirectGraphics JSI
 * @{
 */
/**
 * Returns the native pixel format of the implementation.
 * @return 
 *        A pixel format value defined at @ref nokia_ui_pixel_format "Pixel Format".
 *
 * Return the value of the most efficient pixel format supported by the native system.
 * The native system must support the format returned by this function by the following functions:
 * - JkNokiaDrawPixelsInt()
 * - JkNokiaDrawPixelsByte()
 * - JkNokiaDrawPixelsShort()
 * - JkNokiaGetPixelsInt()
 * - JkNokiaGetPixelsByte()
 * - JkNokiaGetPixelsShort()
 * .
 * The native system may also support other pixel formats by those functions.
 *
 * This function corresponds to the <code>com.nokia.mid.ui.DirectGraphics\#getNativePixelFormat</code> method.
 */
JKSint JkNokiaGetNativePixelFormat(void);

/**
 * Retrieves all the pixel formats supported by the native system.
 * @param formats
 *        A pointer to the array where this function stores the values of all the pixel formats supported by the native system.
 * @param length
 *        The number of the elements of the array indicated by <i>formats</i>.
 * 
 * The array elements have been filled with <code>0x00000000</code> when this function is called.
 * Set the values of all the supported @ref nokia_ui_pixel_format "pixel formats"
 * to the array from the initial element toward the end leaving the elements to which 
 * this function sets no specific value.
 *  Note that the length of the array is enough to hold all the values defined at @ref nokia_ui_pixel_format "Pixel Format." 
 *
 * The values set in the array must contain the value that is returned by JkNokiaGetNativePixelFormat().
 */
void JkNokiaGetSupportedPixelFormat(JKSint* formats, JKSint length);
/** @} DirectGraphics JSI */

/**
 * @addtogroup Nokia_Sound_JSI
 * @{
 */
/**
 * Returns the maximum number of concurrent sounds the device can play for an audio type.
 * @param type
 *        The audio type.
 *        Possible values:
 *        - #JK_NOKIA_FORMAT_TONE
 *        - #JK_NOKIA_FORMAT_WAV
 *        .
 * @return
 *        Return the maximum number of concurrent sounds for the given audio type.
 *        A value of 1 means that only one sound can be played at a time. 
 *        Return 1 always, as per July 2008.
 *
 * This function corresponds to the <code>com.nokia.mid.sound.Sound.getConcurrentSoundCount</code> method.
 */
JKSint JkNokiaGetConcurrentNum(JKSint type);
/** @} Sound JSI */

/**
 * @defgroup DeviceControl_JSI DeviceControl JSI
 * An interface for controlling UI devices such as vibrator, etc.
 *
 * This interface is used for implementing the features of the <code>com.nokia.mid.ui.DeviceControl</code> class.
 *
 * The interface defined here must be implemented by the developer incorporating JBlend into the target device.
 *
 * @par Header File
 * JkNokiaExtension.h
 * @{
 */

/**
 * Activates or deactivates a light on the device.
 * @param num 
 *        The identifier of the light. 
 *        A value of 0 indicates the display backlight.
 *        Other numbers are currently left unspecified.  
 * @param level
 *        The value representing the lighting level.
 *        A value from 0 to 100 can be passed. 
 *        0 means "off" or some other minimum lighting setting.
 *        For many devices, a value greater than 0 means "light on". 
 *
 * This function corresponds to the <code>com.nokia.mid.ui.DeviceControl\#setLights</code> method.
 *
 * Note that the <code>com.nokia.mid.ui.DeviceControl\#flashLights</code> method is implemented using 
 * the JBlend JSI functions <b>JkDeviceStartBacklightFlash()</b> and <b>JkDeviceStopBacklightFlash()</b>.
 * Those two JSI functions must be implemented with taking the setting made by this function into account.
 * See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of 
 * <b>JkDeviceStartBacklightFlash()</b> and <b>JkDeviceStopBacklightFlash()</b>.
 */
void JkNokiaSetLight(JKSint num, JKSint level);

/**
 * Activates vibration for a given length of time and frequency.
 * @param frequency
 *        The frequency of the vibration device. 
 *        A value of 0 can be passed to query whether 
 *        or not there is a vibration device. 
 *        A value of 100 means the maximum frequency value of the device. 
 *        A value of 1 must always result in a minimum non-zero vibration.
 * @param duration
 *        The length of time in milliseconds the vibration is active.
 * @return 
 *        - When frequency == 0<br>
 *          return 1 if the vibration feature is supported by the native system and it is currently allowed to use; 
 *          return 0 otherwise (e.g., it is not supported, it is currently disabled by the user, etc.).
 *        - When frequency > 0 <br>
 *              if the native system starts vibration successfully return 1, otherwise return 0;
 * 
 * If this function is called while the target device is vibrating, cancel the 
 * vibration and start new one using the new set of the parameters.
 *
 * The behavior of the native system when the JVM pauses during the time 
 * in which the vibrator is turned on is implementation-dependent.
 *
 * This function corresponds to the <code>com.nokia.mid.ui.DeviceControl\#startVibra</code> method.
 */
JKSint JkNokiaStartVibrate(JKSint frequency, JKSint duration);

/**
 * Stops any vibration.
 * This function corresponds to the <code>com.nokia.mid.ui.DeviceControl\#stopVibra</code> method.
 */
void JkNokiaStopVibrate(void);
/** @} DeviceControl JSI */

/**
 * @addtogroup DirectGraphics_JSI DirectGraphics JSI
 * @{
 */
/**
 * Draws a line.
 * @param x1 
 *        The x-coordinate of the start point of the line.
 * @param y1 
 *        The y-coordinate of the start point of the line.
 * @param x2 
 *        The x-coordinate of the end point of the line.
 * @param y2 
 *        The y-coordinate of the end point of the line.
 * @param argbColor
 *        The ARGB color value to be used in drawing the line.
 * @param graphicsContextHandle
 *        The handle of the graphics context in which drawing should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * Draw a line connecting points (x1, y1) and (x2, y2) on the graphics context <i>graphicsContextHandle</i>.
 * Draw a dot if (x1, y1) and (x2, y2) are the same point.
 *
 * Note that drawing must be performed using the line style and 
 * clip region currently set in the graphics context <i>graphicsContextHandle</i>. 
 *
 * This function is called when any of the following methods is called:
 * - <code>com.nokia.mid.ui.DirectGraphics\#drawTriangle</code> 
 * - <code>com.nokia.mid.ui.DirectGraphics\#drawPolygon</code> 
 * - <code>com.nokia.mid.ui.DirectGraphics\#fillPolygon</code>  
 *   (When drawing a dot or line because only one or two points are passed to the method)
 * .
 */
void JkNokiaDrawLine(JKSint x1, JKSint y1, JKSint x2, JKSint y2, JKSint argbColor,  JKSint graphicsContextHandle);


/**
 * Fills a closed polygon defined by the arrays of the x- and y-coordinates. 
 *
 * @param xPoints 
 *        A pointer to an array containing the x-coordinate values of the vertices.
 * @param xOffset 
 *        An offset to the first x point in <i>xPoints</i>
 * @param yPoints 
 *        A pointer to an array containing the y-coordinate values of the vertices.
 * @param yOffset 
 *        An offset to the first y point in <i>yPoints</i>.
 * @param nPoints  
 *        The total number of vertices.
 * @param argbColor
 *        The ARGB color value to be used in painting the polygon.
 * @param graphicsContextHandle
 *        The handle of the graphics context in which drawing should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * Draw the polygon defined by <i>nPoint</i> line segments, where the first <i>nPoint</i> - 1
 * line segments are line segments from <br>
 * (<i>xPoints</i>[<i>xOffset</i> + i - 1], <i>yPoints</i>[<i>yOffset</i> + i - 1]) to <br>
 * (<i>xPoints</i>[<i>xOffset</i> + i], <i>yPoints</i>[<i>yOffset</i> + i]), for 1 <= i < <i>nPoints</i>. <br>
 * The figure must be closed by drawing a line connecting the final point to the first point if those points are different. 
 *
 * The area inside the polygon is defined using an even-odd fill rule, which is also known as the alternating rule. 
 *
 * Note that drawing must be performed in the clip region currently set in the graphics context <i>graphicsContextHandle</i>. 
 *
 * This function corresponds to the <code>com.nokia.mid.ui.DirectGraphics\#fillPolygon</code> method. 
 */
 void JkNokiaFillPolygon(JKSint* xPoints, JKSint xOffset, JKSint* yPoints, JKSint yOffset, JKSint nPoints, JKSint argbColor, JKSint graphicsContextHandle);

/**
 * Copies or draws int-format pixel data to a graphics context to a specific location from 
 * the array starting from the specified offset.
 * @param pixels
 *        A pointer to an array of pixel values (0xAARRGGBB) to be drawn.
 * @param transparency
 *        A flag indicating whether to check the pixel's transparency value.
 *        If #JK_TRUE, drawing must be performed with the transparency value taken into account.
 *        If #JK_FALSE, draw the pixels to the graphics context without comparing the transparency values.
 * @param offset 
 *        The index of the first pixel to draw.
 * @param scanlength 
 *        The relative array offset (in pixels) between the corresponding pixels in consecutive rows.
 * @param x
 *        The horizontal rendering location in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The vertical rendering location in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width in pixels of the region to be rendered.
 * @param height
 *        The height in pixels of the region to be rendered.
 * @param manipulation
 *        The image manipulation to be performed on the image before drawing. 
 *        A value of 0 meaning no manipulation or 
 *        a value defined at @ref nokia_ui_manipulation "Image Manipulation" is specified.
 * @param format 
 *        The pixel format of the elements of the <i>pixels</i> array.
 *        One of the int-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context in which drawing should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 
 * Paint the pixel data in the graphics context <i>GraphicsContext</i> in the following fashion (assuming <i>manipulation</i>==0): 
 *
 * P(x1, y1) = <i>pixels</i>[<i>offset</i> + (x1 - <i>x</i>) + (y1 - <i>y</i>) * <i>scanlength</i>], <br>
 * for each P(x1, y1), where <br>
 * (<i>x</i> <= x1 < <i>x</i> + <i>width</i>) and <br>
 * (<i>y</i> <= y1 < <i>y</i> + <i>height</i>).
 *
 * Note that drawing must be performed in the clip region currently set in the graphics context <i>graphicsContextHandle</i>.
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#drawPixels(int[] pixels,
 *                     boolean transparency,
 *                     int offset,
 *                     int scanlength,
 *                     int x,
 *                     int y,
 *                     int width,
 *                     int height,
 *                     int manipulation,
 *                     int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is an int-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaDrawPixelsInt(JKSint* pixels, JKBool transparency, JKSint offset, 
			JKSint scanlength, JKSint x, JKSint y, JKSint width, JKSint height, JKSint   manipulation, JKSint format, JKSint GraphicsContext);
 
 /**
 * Copies or draws byte-format pixel data to a graphics context.
 * @param pixels
 *        A pointer to an array of pixel values to be drawn.
 * @param transparencyMask 
 *        A pointer to an array defining the transparency mask.
 * @param offset 
 *        The index of the first pixel and the mask value.
 * @param scanlength 
 *        The relative array offset (in number of pixels) between the corresponding pixels and the mask value in 
 *        consecutive rows
 * @param x
 *        The horizontal rendering location in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The vertical rendering location in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width in pixels of the region to be rendered.
 * @param height
 *        The height in pixels of the region to be rendered.
 * @param manipulation
 *        The image manipulation to be performed on the image before drawing.
 *        A value of 0 meaning no manipulation or 
 *        a value defined at @ref nokia_ui_manipulation "Image Manipulation" is specified.
 * @param format 
 *        The pixel format of the elements of the <i>pixels</i> array.
 *        One of the byte-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context in which drawing should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * Bytes in <i>pixels</i> and <i>transparencyMask</i> arrays will be passed in the same format. 
 * If <i>transparencyMask</i> is #JK_NULL, the image should be considered fully opaque. 
 *
 * For pixel formats #JK_NOKIA_BYTE_1_GRAY and #JK_NOKIA_BYTE_1_GRAY_VERTICAL bit value 0 means fully transparent pixel,
 * 1 means fully opaque pixel. For other byte formats the transparency information is as wide as color 
 * information for one pixel, for example, in #JK_NOKIA_BYTE_2_GRAY 2 bits are used for storing transparency 
 * information in the array <i>transparencyMask</i>.
 *
 * The semantics for mask values are same as in alpha channel use. Zero value indicates fully transparent pixel,
 * non-zero values are treated as non-transparent (largest possible value means fully opaque and values in 
 * between either fully opaque or semi-opaque). 
 *
 * Note that <i>scanlength</i> and <i>offset</i> parameters indicate the scanlength and offset in number of pixels. 
 * This is not necessarily the same as array indices since multiple pixels may be stored in a byte. 
 *
 * The mapping from the source to the target is the same as that described for JkNokiaDrawPixelsInt().
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#drawPixels(byte[] pixels,
 *                     byte[] transparencyMask,
 *                     int offset,
 *                     int scanlength,
 *                     int x,
 *                     int y,
 *                     int width,
 *                     int height,
 *                     int manipulation,
 *                     int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is a byte-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaDrawPixelsByte(JKSint8* pixels,JKSint8* transparencyMask,JKSint offset,JKSint scanlength,
			JKSint x,JKSint y,JKSint width,JKSint height, JKSint manipulation,JKSint format, JKSint GraphicsContext);

/**
 * Copies or draws short-format pixel data to a graphics context.
 * @param pixels
 *        A pointer to an array of pixel values to be drawn.
 * @param transparency
 *        A flag indicating whether to check the pixel's transparency value.
 *        If #JK_TRUE, drawing must be performed with the transparency value taken into account.
 *        If #JK_FALSE, draw the pixels to the graphics context without comparing the transparency values.
 * @param offset 
 *        The index of the first pixel to draw.
 * @param scanlength 
 *        The relative array offset (in pixels) between the corresponding pixels in consecutive rows.
 * @param x
 *        The horizontal rendering location in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The vertical rendering location in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width in pixels of the region to be rendered.
 * @param height
 *        The height in pixels of the region to be rendered.
 * @param manipulation
 *        The image manipulation to be performed on the image before drawing.
 *        A value of 0 meaning no manipulation or 
 *        a value defined at @ref nokia_ui_manipulation "Image Manipulation" is specified.
 * @param format 
 *        The pixel format of the elements of the <i>pixels</i> array.
 *        One of the short-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context in which drawing should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * The mapping from the source pixels to the target pixels is the same as that described for JkNokiaDrawPixelsInt().
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#drawPixels(short[] pixels,
 *                     boolean transparency,
 *                     int offset,
 *                     int scanlength,
 *                     int x,
 *                     int y,
 *                     int width,
 *                     int height,
 *                     int manipulation,
 *                     int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is a short-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaDrawPixelsShort(JKSint16* pixels,JKBool transparency,JKSint offset, JKSint scanlength,
			JKSint x,JKSint y,JKSint width,JKSint height,JKSint manipulation,JKSint format, JKSint GraphicsContext);

/**
 * Copies the pixel values in a region of a graphics context from a specific location to an array of int values. 
 * @param pixels
 *        A pointer to an array where this function stores the pixel information.
 * @param offset 
 *        The index to the <i>pixels</i> array where the first pixel value must be stored.
 * @param scanlength 
 *        The relative array offset (in pixels) between the corresponding pixels in consecutive rows.
 * @param x
 *        The x-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The y-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width of the region in the graphics context <i>GraphicsContext</i>.
 * @param height
 *        The height of the region in the graphics context <i>GraphicsContext</i>.
 * @param format 
 *        The pixel format in which pixel data is requested.
 *        One of the int-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context from which copy operation should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * The current clip region set in the graphics context <i>GraphicsContext</i> 
 * must not affect pixel values stored in the pixels array, i.e. 
 * even if a clip region is set and the region intersects the region queried with this method,
 * the clip region pixels must be stored in the <i>pixels</i> array. 
 *
 * The copy operation should be performed in the following fashion: <br>
 *
 * <i>pixels</i>[<i>offset</i> + (x1 - <i>x</i>) + (y1 - <i>y</i>) * <i>scanlength</i>] = P(x1, y1), <br>
 * for each P(x1, y1), where <br>
 * (<i>x</i> <= x1 < <i>x</i> + <i>width</i>) and <br>
 * (<i>y</i> <= y1 < <i>y</i> + <i>height</i>).
 *
 * When the pixels to be retrieved have been written using JkNokiaDrawPixelsInt() with the same pixel format, 
 * the retrieved pixel values have to be exactly the same as the values written.
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#getPixels(int[] pixels,
 *                    int offset,
 *                    int scanlength,
 *                    int x,
 *                    int y,
 *                    int width,
 *                    int height,
 *                    int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is an int-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaGetPixelsInt(JKSint* pixels, JKSint offset,JKSint scanlength,
            JKSint x, JKSint y, JKSint width, JKSint height,JKSint format, JKSint GraphicsContext);

/**
 * Copies the pixel (including any transparency mask) values in a region of a graphics 
 * context from a specific location to an array of byte values. 
 * @param pixels
 *        A pointer to an array where this function stores the pixel information.
 * @param transparencyMask
 *        A pointer to an array where this function stores the transparency mask.
 * @param offset 
 *        The offset of the array element where the first pixel value and mask value must be stored.
 * @param scanlength 
 *        The relative array offset (in pixels) between the corresponding pixels in consecutive rows.
 * @param x
 *        The x-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The y-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width of the region in the graphics context <i>GraphicsContext</i>.
 * @param height
 *        The height of the region in the graphics context <i>GraphicsContext</i>.
 * @param format 
 *        The pixel format in which pixel data is requested.
 *        One of the byte-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context from which copy operation should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * Note that the <i>scanlength</i> and <i>offset</i> parameters indicate the scanlength and offset in number of pixels.
 * This is not necessarily the same as array indices since multiple pixels may be stored in a byte. 
 *
 * The notes on the clip region of the graphics context and 
 * the mapping from the source pixels to the target pixels are the same as those described for JkNokiaGetPixelsInt().
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#getPixels(byte[] pixels,
 *                    byte[] transparencyMask,
 *                    int offset,
 *                    int scanlength,
 *                    int x,
 *                    int y,
 *                    int width,
 *                    int height,
 *                    int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is a byte-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaGetPixelsByte(JKSint8* pixels,JKSint8* transparencyMask,JKSint offset,
            JKSint scanlength,JKSint x,JKSint y,JKSint width, JKSint height, JKSint format, JKSint GraphicsContext);

/**
 * Copies the pixel values in a region of a graphics context from a specific location to an array of short values. 
 * @param pixels
 *        A pointer to an array where this function stores the pixel information.
 * @param offset 
 *        The index to the <i>pixels</i> array where the first pixel value must be stored.
 * @param scanlength 
 *        The relative array offset (in pixels) between the corresponding pixels in consecutive rows.
 * @param x
 *        The x-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param y
 *        The y-coordinate of the upper left corner of the region in the graphics context <i>GraphicsContext</i>.
 * @param width
 *        The width of the region in the graphics context <i>GraphicsContext</i>.
 * @param height
 *        The height of the region in the graphics context <i>GraphicsContext</i>.
 * @param format 
 *        The pixel format in which pixel data is requested.
 *        One of the short-based formats indicated by JkNokiaGetSupportedPixelFormat() is specified here.
 * @param GraphicsContext
 *        The handle of the graphics context from which copy operation should be performed.
 *        The value created by <b>JkGraphicsCreateContext()</b> is passed.
 *        See @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]" for details of <b>JkGraphicsCreateContext()</b>.
 *
 * The notes on the clip region of the graphics context and 
 * the mapping from the source pixels to the target pixels are the same as those described for JkNokiaGetPixelsInt().
 *
 * This function corresponds to the 
 * <code>com.nokia.mid.ui.DirectGraphics\#getPixels(short[] pixels,
 *                    int offset,
 *                    int scanlength,
 *                    int x,
 *                    int y,
 *                    int width,
 *                    int height,
 *                    int format)</code>.
 * This function is called only when the <code>format</code> parameter to the method is a short-based format 
 * indicated by JkNokiaGetSupportedPixelFormat().
 */
void JkNokiaGetPixelsShort(JKSint16* pixels, JKSint offset, JKSint scanlength,
            JKSint x, JKSint y, JKSint width, JKSint height, JKSint format, JKSint GraphicsContext);

/** @} DirectGraphics JSI */

#ifdef __cplusplus
}
#endif

#endif

