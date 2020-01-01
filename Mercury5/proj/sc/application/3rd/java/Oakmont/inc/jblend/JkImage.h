/**
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkImage.h
 * Immutable Image JSI
 */
/**
 * @addtogroup Immutable_Image_JSI
 * @{
 */

#ifndef ___JK_IMAGE_H
#define ___JK_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkVideoComponent.h"

/**
 * Image decoding: No error
 */
#define JK_IMAGE_NO_ERROR               (0)

/**
 * Image decoding: No enough memory
 */
#define JK_IMAGE_NO_ENOUGH_MEMORY       (-1)

/**
 * Image decoding: Image data format is wrong
 */
#define JK_IMAGE_WRONG_FORMAT           (-2)

/**
 * Image decoding: API parameters is wrong
 */
#define JK_IMAGE_PARAMETER_ERROR        (-3)

/**
 * Image decoding: Image decoding is interrupted to suspend the JVM.
 */
#define JK_IMAGE_INTERRUPTED        (-4)

/**
 * The handle of an immutable image
 */
typedef JKHandle JKImageHandle;

/**
 * Decodes image data and creates an immutable image.
 *
 * @param srcData
 *        The image data for decoding
 * @param length
 *        The image data size in bytes.
 * @param err
 *        A pointer of the memory area which stores an error code.
 * @return 
 *         Return a handle identifying the decoded immutable image.
 *         When the native system interrupts the image decoding to suspend the JVM, 
 *         store #JK_IMAGE_INTERRUPTED in the memory area pointed to by 
 *         the <i>err</i> parameter, and return #JK_INVALID_HANDLE.
 *         If image decoding failed, set one of the following error codes in the memory 
 *         area pointed by the <i>err</i>
 *         parameter and return #JK_INVALID_HANDLE.
 *         <ul>
 *           <li> #JK_IMAGE_NO_ENOUGH_MEMORY
 *           <li> #JK_IMAGE_WRONG_FORMAT
 *           <li> #JK_IMAGE_PARAMETER_ERROR
 *         </ul>
 * <p>
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating a NULL pointer in the srcData or <i>err</i> parameters.
 *  <li>Designating a value of 0 or less in the <i>length</i> parameter.
 * </ul>
 *
 * @par For compliance with JTWI 1.0:
 * This function must be implemented so as to enable decoding of the following image data. 
 *     - PNG image data of up to 32768 pixels at each of these color depths: 
 *       1, 2, 4, 8, 16, 24, 32 bits
 *     - JFIF/JPEG image data of up to 32768 pixels
 *     .
 *
 * @see JkImageDispose()
 * @see JkImageGetARGB()
 */
JKImageHandle JkImageCreate( const void *srcData, JKSint32 length, JKSint32 *err );

/**
 * Decodes ARGB image data and creates an immutable image.
 *
 * @param argbData
 *        The image data for decoding
 * @param width
 *        The image width
 * @param height
 *        The image height
 * @param processAlpha
 *        Alpha channel used or not ( #JK_TRUE if used)
 * @param err
 *        A pointer of the memory area which stores an error code.
 * @return 
 *        Return a handle identifying the decoded immutable image.
 *        When the native system interrupts the image decoding to suspend the JVM, 
 *        store #JK_IMAGE_INTERRUPTED in the memory area pointed to by 
 *        the <i>err</i> parameter, and return #JK_INVALID_HANDLE.
 *        If image decoding failed, set one of the following error codes in the memory 
 *        area pointed by the <i>err</i>
 *        parameter and return #JK_INVALID_HANDLE.
 *        <ul>
 *          <li> #JK_IMAGE_NO_ENOUGH_MEMORY
 *          <li> #JK_IMAGE_WRONG_FORMAT
 *          <li> #JK_IMAGE_PARAMETER_ERROR
 *        </ul>
 * <p>
 * ARGB format represents one pixel of image data as 32 bits, with 8 bits for each of
 * the RGB color information and 8 bits for alpha channel information.
 * If the value of parameter <i>processAlpha</i> is #JK_TRUE, alpha channel information 
 * must be stored.
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating a NULL pointer in the <i>argData</i> or <i>err</i> parameters.
 *  <li>Designating a value of 0 or less in the <i>width</i> or <i>height</i> parameter.
 * </ul>
 *
 * @see JkImageDispose()
 * @see JkImageGetARGB()
 */
JKImageHandle JkImageCreateFromARGB( const JKUint32 *argbData,
        JKSint32 width, JKSint32 height, JKBool processAlpha, JKSint32 *err );


/**
 * Creates an Immutable image from an existing image data. 
 *
 * @param hImage
 *        The handle of the source image. This is the value returned by
 *        JkImageCreate(), JkImageCreateFromARGB() or JkOffScreenCreate().
 * @param isOffScreen
 *        If the sourece image is a off-screen, #JK_TRUE is designated.
 * @param bounds
 *        The rectangular area to be extracted from the source image.
 * @param trans
 *        The orientation of rotation and flipping. 
 *        A constant value whose name is starting with JK_VIDEO_TRANS_ is designated.
 * @param err
 *        A pointer to the memory area for putting an error code.
 * @return 
 *         Return a handle identifying the created immutable image.
 *         When the native system interrupts the image decoding to suspend the JVM, 
 *         store #JK_IMAGE_INTERRUPTED in the memory area pointed to by 
 *         the <i>err</i> parameter, and return #JK_INVALID_HANDLE.
 *         If image creation failed, set one of the following error codes in 
 *         the memory area pointed to by the <i>err</i>
 *         parameter and return #JK_INVALID_HANDLE.
 *         <ul>
 *           <li> #JK_IMAGE_NO_ENOUGH_MEMORY
 *           <li> #JK_IMAGE_WRONG_FORMAT
 *           <li> #JK_IMAGE_PARAMETER_ERROR
 *         </ul>
 * <p>
 * Make a copy the source image region designated in the <i>bounds</i> parameter,
 * and create a new Immutable image with that image data after 
 * rotating and flipping it in accordance with the <i>trans</i> parameter. 
 * 
 * This function is called when the JBlend customization 
 * property "midp_enhance_create_cropped_image" is set as "1." 
 * When the property value is a value other than "1," 
 * store #JK_IMAGE_WRONG_FORMAT in the memory area designated in 
 * the <i>err</i> parameter without performing any image operation 
 * and return #JK_INVALID_HANDLE.
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the <i>hImage</i> parameter.
 *  <li>Designating a NULL pointer in the <i>bounds</i> parameter and the <i>err</i> parameter.
 *  <li>Designating in the <i>bounds</i> parameter an area that exceeds the 
 *      area of the image designated in the <i>hImage</i> parameter.
 * </ul>
 * @see JkImageDispose()
 */
JKImageHandle JkImageCreateCroppedImage(JKImageHandle hImage, JKBool isOffScreen, 
                              const JKT_Rect *bounds, JKSint32 trans, JKSint32 *err);



/**
 * Dispose of an immutable image.
 *
 * @param hImage
 *        The handle of the immutable image. This is the value returned by
 *        JkImageCreate() or JkImageCreateFromARGB().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the <i>hImage</i> parameter.
 *
 * @see JkImageCreate()
 * @see JkImageCreateFromARGB()
 */
void JkImageDispose( JKImageHandle hImage );

/**
 * Gets the immutable image width.
 *
 * @param hImage
 *        The handle of the immutable image. This is the value returned by
 *        JkImageCreate().
 * @return 
 *        Return the immutable image width.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the <i>hImage</i> parameter.
 *
 * @see JkImageCreate()
 */
JKSint32 JkImageGetWidth( JKImageHandle hImage );

/**
 * Gets the immutable image height.
 *
 * @param hImage
 *        The handle of the immutable image. This is the value returned by
 *        JkImageCreate().
 * @return 
 *        Return the immutable image height
 * 
 * In no case is #JK_INVALID_HANDLE designated in the <i>hImage</i> parameter.
 *
 * @see JkImageCreate()
 */
JKSint32 JkImageGetHeight( JKImageHandle hImage );

/**
 * Gets the data in the designated rectangle in the immutable image, in ARGB format.
 *
 * @param hImage
 *        The handle of the immutable image. This is the value returned by
 *        JkImageCreate() or JkImageCreateFromARGB().
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
 *        A pointer to the structure holding the rectangular area cut out of the immutable image.
 *
 * This function corresponds to the <code>getRGB</code> method of the <code>Image</code> 
 * object created as an immutable image.
 * <i>argbData</i> is for designating a pointer to the element corresponding to <code>offset</code> 
 * in the array passed to the <code>getRGB</code> method in <code>rgbData</code>.
 * 
 * Following the procedure below, get the data in the rectangle indicated by <i>bounds</i> 
 * in the immutable image designated by <i>hImage</i>.
 * <ol>
 *  <li>Assume as the write pointer the position indicated by <i>argbData</i>. 
 *  <li>In the location indicated by the write pointer, store the amount of immutable 
 *      image data indicated by <i>bounds->width</i>.
 *  <li>Advance the write pointer by <i>scanlen</i>.
 *  <li>Repeat steps 2 and 3 for <i>bounds->height</i> times.
 * </ol>
 *
 * Store also alpha channel information with the data.
 * If, however, an image was created designating #JK_FALSE in the <i>processAlpha</i> parameter passed to 
 * JkImageCreateFromARGB(), invalidating alpha channel information, or if the image contains no
 * alpha channel information to begin with, set the alpha channel to a fixed value of 0xFF. 
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
 * @image html JkImageGetARGB_en.gif
 * 
 * The following illegal parameter designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the <i>hImage</i> parameter.
 *  <li>Designating a NULL pointer in the <i>argbData</i> parameter.
 *  <li>Designating an area in the <i>bounds</i> parameter that exceeds the area of 
 *      the Immutable image designated in the <i>hImage</i> parameter.
 *  <li>Designating a value in <i>scanlen</i> whose absolute value is less than <i>bounds->width</i>.
 * </ul>
 *
 * @see JkImageCreate()
 * @see JkImageCreateFromARGB()
 */
void JkImageGetARGB( JKImageHandle hImage, JKUint32 *argbData,
                JKSint32 length, JKSint32 scanlen, const JKT_Rect *bounds );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
