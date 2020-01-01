/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/***************************************************************************
 * FILE: kjava_sys_gfx.h
 *
 * DESCRIPTION:
 *      The module is one of KJava interface modules. It is for graphics
 *      operations.
 *
 * UPDATED DATE:
 *      2004/11/03
 *
 * REVISION:
 *      2004/09/19,  Yagamy,     draft version.
 *      2004/10/21,  Simon,      Add two element(viewRegion and softKeyRegion)
 *                               of GfxInfo
 *      2004/11/03,  Simon,      Change the parameter of getSuitableFont for
 *                               Default font
 *
 ***************************************************************************/

#ifndef KJAVA_SYS_GFX_HEADER
#define KJAVA_SYS_GFX_HEADER

/**
 * @file kjava_sys_gfx.h
 *  Low-Level Graphics KSI
 */

#ifdef __cplusplus
extern "C"{
#endif

/*
 *  Interfaces listed in the group are used for:
 *      - GUI information acquire.
 *      - Virtual screen buffer allocation and flushing.
 *      - Font information acquire and drawing.
 *      - Image codec.
 *      .
 */

/**
 * @defgroup GFX_Initialization_Finalization_KSI Graphic System Initialization and Finalization KSI
 * An interface for initialization and finalization of the native graphics system.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context in response to the following requests made via ACI functions.
 * - Application execution by @ref Application_Runtime_Control_ACI.
 * - TCK execution by @ref ajms_arc_tck.
 * - HTTP transaction by @ref ajsc_httplib_aci_main.
 * .
 *
 * @par Include file 
 * \#include kjava_sys_gfx.h
 *
 * @ingroup graphics_ksi
 */

/**
 * @defgroup Font_Drawing Font KSI
 * An interface for drawing font.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context.
 *
 * @par Include file 
 * \#include kjava_sys_gfx.h
 *
 * @ingroup graphics_ksi
 */

/**
 * @defgroup LCD_Drawing Low-Level LCD Control KSI
 * An interface for controlling low-level drawing buffers.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context.
 *
 * @par Include file 
 * \#include kjava_sys_gfx.h
 *
 * @ingroup graphics_ksi
 */

/**
 * @defgroup Image_Codec Image Codec KSI
 * An interface for analyzing and decoding an image.
 * This interface must be implemented by the device manufacturer.
 *
 * This interface is called in the KVE thread context.
 *
 * @par Include file 
 * \#include kjava_sys_gfx.h
 *
 * @ingroup graphics_ksi
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/**
 * @ingroup Font_Drawing
 */

/**
 * Plain font
 */
#define KJAVA_FONT_STYLE_PLAIN            0
/**
 * Bold font
 */
#define KJAVA_FONT_STYLE_BOLD             1
/**
 * Italic font
 */
#define KJAVA_FONT_STYLE_ITALIC           2
/**
 * Underline font
 */
#define KJAVA_FONT_STYLE_UNDERLINE        4

/**
 * Monospace font
 */
#define KJAVA_FONT_FACE_MONOSPACE         32
/**
 * Proportional font
 */
#define KJAVA_FONT_FACE_PROPORTIONALE     64

/**
 * The default font used for low-level graphics drawing
 */
#define KJAVA_FONT_TYPE_DEFAULT           0
/**
 * The default display font used by GUI
 */
#define KJAVA_FONT_TYPE_STATIC_TEXT       0x1000
/**
 * The default editing font used by GUI
 */
#define KJAVA_FONT_TYPE_INPUT_TEXT        0x1001


/**
 * Small size font
 */
#define KJAVA_FONT_SIZE_SMALL             1
/**
 * Medium size font
 */
#define KJAVA_FONT_SIZE_MEDIUM            2
/**
 * Large size font
 */
#define KJAVA_FONT_SIZE_LARGE             3

/**
 * @ingroup LCD_Drawing
 */

/**
 * Normal screen mode
 */
#define KJAVA_VIDEO_SCREEN_NORMAL         0
/**
 * Full screen mode
 */
#define KJAVA_VIDEO_SCREEN_FULL           1

/**
 * No Displayable set.
 *
 * This means that a <code>null</code> object was passed to <code>setCurrent</code> method.
 */
#define KJAVA_VIDEO_DISPLAYABLE_NULL      0
/**
 * Screen type set.
 *
 * This means that a <code>Screen</code> object was passed to <code>setCurrent</code> method.
 */
#define KJAVA_VIDEO_DISPLAYABLE_SCREEN    1
/**
 * Canvas type set.
 *
 * This means that a <code>Canvas</code> object was passed to <code>setCurrent</code> method.
 */
#define KJAVA_VIDEO_DISPLAYABLE_CANVAS    2
/**
 * A permission confirmation dialog displayed.
 *
 * This means that a permission confirmation dialog is currently displayed.
 */
#define KJAVA_VIDEO_DISPLAYABLE_PERMISSIONDIALOG      4

/**
 * @ingroup Image_Codec 
 */

/**
 * Image decoding or analysis succeeded
 */
#define KJAVA_CODEC_SUCCESS       0

/**
 * Unsupported image format
 */
#define KJAVA_CODEC_UNSUPPORT     1

/**
 * Bad source format
 */
#define KJAVA_CODEC_BAD_FORMAT    2

/**
 * Insufficient resource for image decoding
 */
#define KJAVA_CODEC_NO_RESOURCE   3

/**
 * The data type for storing a UCS2 character
 */
typedef unsigned short  KJavaUnicode;

#if defined(KJAVA_GFX_DISPLAY_565)
    /**
     * The type for storing a pixel data
     */
    typedef unsigned short  KJavaPixel;

#elif defined (KJAVA_GFX_DISPLAY_555)
    /**
     * The type for storing a pixel data
     */
    typedef unsigned short  KJavaPixel;

#elif defined (KJAVA_GFX_DISPLAY_666)
    /**
     * The type for storing a pixel data
     */
    typedef unsigned int    KJavaPixel;

#elif defined (KJAVA_GFX_DISPLAY_888)
    /**
     * The type for storing a pixel data
     */
    typedef unsigned int    KJavaPixel;

#else

#error You MUST define either pixel format of KJAVA_GFX_DISPLAY_565, KJAVA_GFX_DISPLAY_666, or KJAVA_GFX_DISPLAY_888 in the build settings.

#endif


/**
 * The structure type for containing the information of a screen buffer.
 */
typedef struct _KJavaImageTag
{
    /**
     * A pointer to the pixel buffer.
     *
     * Only when <i>isMutable</i> is 1, the data is mutable and this field should be converted
     * to <i>unsigned short *</i>.
     */
    const KJavaPixel *data;

    /**
     * The width of the screen buffer.
     */
    int         width;

    /**
     * The height of the screen buffer.
     */
    int         height;

    /**
     * A flag indicating whether or not the pixel buffer contains transparency information.
     */
    int         transparency;

    /**
     * A flag indicating whether of not the pixel buffer is mutable.
     */
    int         isMutable;
}
KJavaImage;

/**
 * @ingroup LCD_Drawing
 */

/**
 * The structure type for representing a clipping rectangle.
 */
typedef struct _KJavaClipTag
{
    /**
     * The x coordinate of the clipping rectangle.
     */
    int       x;

    /**
     * The y coordinate of the clipping rectangle.
     */
    int       y;

    /**
     * The width of the clipping rectangle.
     */
    int       width;

    /**
     * The height of the clipping rectangle.
     */
    int       height;
}
KJavaClip;

/**
 * @ingroup Font_Drawing
 */

/**
 * The structure type for containing font information.
 *
 * For details of the members
 * {@link KJavaFont#char_leading char_leading},
 * {@link KJavaFont#char_ascent char_ascent},
 * {@link KJavaFont#char_descent char_descent} and
 * {@link KJavaFont#char_height char_height}, see
 * Leading, Ascent, Descent and Height respectively in the following figure.
 *
 * @anchor fig_ksi_gfx_font
 * @image html ksi-gfx-font-1.jpg "Figure 1. KSI Font Parameters"
 */
typedef struct _KJavaFontTag
{
    /**
     * The font identifier. This is reserved for future use.
     */
    int         id;

    /**
     * The font face.
     * The value is set as a bitwise-OR of the following values.
     * - #KJAVA_FONT_FACE_MONOSPACE
     * - #KJAVA_FONT_FACE_PROPORTIONALE
     * .
     */
    int         face;

    /**
     * The font style.
     * The value is set as a bitwise-OR of the following values.
     * - #KJAVA_FONT_STYLE_PLAIN
     * - #KJAVA_FONT_STYLE_BOLD
     * - #KJAVA_FONT_STYLE_ITALIC
     * - #KJAVA_FONT_STYLE_UNDERLINE
     * .
     */
    int         style;

    /**
     * The font size.
     * One of the following values is set.
     * - #KJAVA_FONT_SIZE_SMALL
     * - #KJAVA_FONT_SIZE_MEDIUM
     * - #KJAVA_FONT_SIZE_LARGE
     * .
     */
    int         size;

    /**
     * The font leading.
     * See Leading in @ref fig_ksi_gfx_font "Figure 1. KSI Font Parameters."
     */
    int         char_leading;

    /**
     * The font ascent.
     * See Ascent in @ref fig_ksi_gfx_font "Figure 1. KSI Font Parameters."
     */
    int         char_ascent;

    /**
     * The font descent.
     * See Descent in @ref fig_ksi_gfx_font "Figure 1. KSI Font Parameters."
     */
    int         char_descent;

    /**
     * The font height.
     * See Height in @ref fig_ksi_gfx_font "Figure 1. KSI Font Parameters."
     */
    int         char_height;

    /**
     * A reserved field.
     */
    int         reserved;
}
KJavaFont;

/**
 * @ingroup LCD_Drawing
 */

/**
 * The structure type for containing the information about the graphics environment of the target device.
 */
typedef struct _KJavaGfxInfoTag
{
    /**
     * The off-screen buffer handle, identifying a virtual screen.
     *
     * This value must be the handle indicating an off-screen buffer that
     * can be used.
     */
    KJavaImage  *offscreen;

    /**
     * The clipping rectangle for Java application drawing.
     *
     * Java application cannot draw outside of this rectangle.
     */
    KJavaClip   viewRegion;

    /**
     * The clipping rectangle for softkey drawing.
     */
    KJavaClip   softKeyRegion;

    /**
     * Whether or not color display is supported.
     */
    int         isColor;

    /**
     * The number of colors.
     */
    int         numColors;

    /**
     * The number of alpha channel levels supported.
     */
    int         numAlphaLevels;

    /**
     * Whether or not the device has key repeat event
     */
    int         hasRepeatEvents;

    /**
     * Whether or not the device has pointer event
     */
    int         hasPointerEvents;

    /**
     * Whether or not the device has pointer motion event
     */
    int         hasPointerMotionEvents;

    /**
     * Whether or not word wrap is required
     */
    int         wordwrap;

    /**
     * The number of softkeys
     */
    int         numSoftkeys;
}
KJavaGfxInfo;

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup GFX_Initialization_Finalization_KSI
 * @{
 */

/**
 * Initializes the native system graphics component.
 *
 * The function needs to:
 *      - prepare the virtual screen for the device.
 *      - prepare the system fonts' information.
 *      .
 */
void kjava_gfx_init(void);

/**
 * Finalizes the native system graphics component.
 *
 * The function needs to release all the graphics system resources that are
 * allocated after kjava_gfx_init() is called.
 */
void kjava_gfx_fini(void);

/** @} */

/**
 * @addtogroup Font_Drawing
 * @{
 */

/**
 * Finds the suitable system font with given criteria (size, face, and style).
 * @param size
 *        The size for the criteria. One of the following is designated.
 *        - #KJAVA_FONT_SIZE_SMALL
 *        - #KJAVA_FONT_SIZE_MEDIUM
 *        - #KJAVA_FONT_SIZE_LARGE
 *        .
 * @param style
 *        The font style. One of the following is designated.
 *        - #KJAVA_FONT_STYLE_PLAIN
 *        - #KJAVA_FONT_STYLE_BOLD
 *        - #KJAVA_FONT_STYLE_ITALIC
 *        - #KJAVA_FONT_STYLE_UNDERLINE
 *        .
 * @param face
 *        The font face. One of the following is designated.
 *        - #KJAVA_FONT_FACE_MONOSPACE
 *        - #KJAVA_FONT_FACE_PROPORTIONALE
 *        .
 * @param defaultFont
 *        The default font. One of the following is designated.
 *        - #KJAVA_FONT_TYPE_DEFAULT
 *        - #KJAVA_FONT_TYPE_STATIC_TEXT
 *        - #KJAVA_FONT_TYPE_INPUT_TEXT
 *        .
 * @return
 *        Return a handle identifying the font that suits given criteria.
 *        If the suitable font is not found, return the handle for the
 *        default system font.
 *
 * Determine a font that suits given criteria and return its font handle.
 *
 * If <i>size</i> == <i>style</i> == <i>face</i> == 0, use <i>defaultFont</i>
 * as the criteria; otherwise, use <i>size</i>, <i>style</i>, and <i>face</i>
 * as the criteria and ignore <i>defaultFont</i>.
 *
 * When neither KJAVA_FONT_FACE_MONOSPACE nor KJAVA_FONT_FACE_PROPORTIONALE is specified, 
 * it means that <code>Font.FACE_SYSTEM</code> was specified by the Java application.
 *
 * @par For compliance with JTWI 1.0:
 * The implementation must enable use of the character fonts specified in 
 * Table 4, "Characters Supported by TextBox and TextField," Section 4.9, 
 * "Supported Characters in TextField and TextBox," in "Java Technology for 
 * the Wireless Industry Specification, Version 1.0."
 *
 */
const KJavaFont* kjava_gfx_getSuitableFont(int size, int style, int face, int defaultFont);

/**
 * Gets the width of given UCS2 string in the designated system font.
 * @param font
 *        The handle of the font to be used in the calculation.
 *        The font handle returned by kjava_gfx_getSuitableFont() is passed.
 * @param str
 *        A pointer to the UCS2 string for which the width should be calculated.
 * @param length
 *        The number of characters in the UCS2 string indicated by <i>str</i>.
 * @return
 *        Return the width in pixels of the UCS2 string.
 * 
 * If the string designated in the str parameter contains a character not defined in the platform, 
 * substitute a blank space for that character and continue processing. 
 * 
 * If the platform text display specification requires kerning, return the character string drawing width after kerning. 
 * 
 * The following illegal parameters designations are not to be made. 
 * - Designating an #AJ_NULL pointer in the <i>str</i> parameter. 
 * - Designating a value less than 0 in the <i>length</i> parameters. 
 * . 
 *
 */
int kjava_gfx_getCharsWidth (
        const KJavaFont *font, const KJavaUnicode *str, int length);

/**
 * Gets the number of characters that fit in the designated width.
 * @param font
 *        The handle of the font to be used in the calculation.
 *        The font handle returned by kjava_gfx_getSuitableFont() is passed.
 * @param str
 *        A pointer to the UCS2 string for which the number should be calculated.
 * @param length
 *        The number of characters in the UCS2 string indicated by <i>str</i>.
 * @param width
 *        The width in pixels.
 * @return
 *        Return the number of characters that fits in the designated width.
 *        If the string designated in the <i>str</i> parameter contains a character
 *        not defined in the platform, treat it as a single blank space.
 *
 * Calculate the number of characters that will fit in the designated width when the
 * designated string is drawn in the designated font.
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating an #AJ_NULL pointer in the <i>str</i> parameter.
 *  <li>Designating a value less than 0 in the <i>length</i> or <i>width</i> parameters.
 * </ul>
 * 
 * If the platform text display specification requires word wrap, then based on 
 * the word delimiter characters defined for the platform, return the number of 
 * characters up to and including the delimiter that will fit within the width 
 * limits. If the last delimiter consists of two or more successive characters, 
 * return the number of characters to the end of the delimiter.
 * 
 * If word wrap is required and there is no delimiter inside a character string that takes up the entire 
 * designated width (i.e., the word width exceeds the designated width) return 0.
 * If part of a delimiter consisting of successive characters exceeds the width 
 * limits, or if no word wrap is required, return the number of characters that 
 * will fit within the designated width.
 * 
 * @image html JkFontCountChars.gif
 *
 * The return values for each width indicated in the figure are as follows:
 * 
 * -# The designated width is less than the first word <br>
 *   No word wrap: 4<br>
 *   Word wrap: 0
 * -# The designated width covers the first word and successive delimiters<br>
 *   No word wrap: 7<br>
 *   Word wrap: 7
 * -# The designated width covers the first word and part of the second word<br>
 *   No word wrap: 9<br>
 *   Word wrap: 8
 * .
 */
int kjava_gfx_getCountChars (
        const KJavaFont *font, const KJavaUnicode *str, int length, int width);

/**
 * Draws a character string on a given offscreen buffer with
 *        designated clipping rectangle, font, and pixel color.
 * @param offscreen
 *        A pointer to the #KJavaImage structure holding the offscreen buffer information.
 * @param clip
 *        A pointer to the the #KJavaClip structure holding the clipping range for drawing.
 * @param font
 *        A pointer to the the #KJavaFont structure holding the font information.
 *        The font handle returned by kjava_gfx_getSuitableFont() is passed.
 * @param string
 *        A pointer to the UCS2 string to be drawn.
 * @param length
 *        The number of characters in the string indicated by <i>string</i>.
 * @param x
 *        The x coordinate of the string drawing position in the offscreen buffer.
 * @param y
 *        The y coordinate of the string drawing position in the offscreen buffer.
 * @param color
 *        The color for drawing. It is designated in the platform pixel
 *        format (e.g. RGB 565, RGB 666, or RGB 888) specified in the
 *        platform information matrix.
 *
 * If the designated coordinates are outside the clip area set for the graphics context, 
 * draw only the portion inside the clip area.
 *
 * Do not wrap the character string in the clip area even if the string drawing width extends outside the clip area. 
 * If the string contains a character not defined in the platform, substitute a blank space or '?' or the like for 
 * that character when drawing. The substitute character is platform dependent.
 *
 */
void kjava_gfx_drawChars (
        KJavaImage      *offscreen,
        const KJavaClip *clip,
        const KJavaFont *font,
        const KJavaUnicode *string, int length,
        int x, int y,
        const KJavaPixel color);

/** @} */

/**
 * @addtogroup LCD_Drawing
 * @{
 */

/**
 * Switches modes of the virtual screen size.
 * @param screenMode
 *        The screen mode. One of the following is designated:
 *        - #KJAVA_VIDEO_SCREEN_NORMAL
 *        - #KJAVA_VIDEO_SCREEN_FULL
 *        .
 * @retval 1 if the mode switch succeeds.
 * @retval 0 if it fails.
 *
 * AJSC assumes that the virtual screen size will change when the screen mode is switched by this function. 
 * The native system must perform the following processing depending on how this function is implemented. 
 *
 * @par When the virtual screen offscreen buffer is recreated in this function:
 * - If prior to recreating there is a graphics context using the virtual screen offscreen buffer as object of drawing, 
 *   switch the object of drawing of the graphics context to the recreated buffer. 
 * - If kjava_gfx_getInfo() is called after changing the screen mode by this function, 
 *   set the handle of the recreated offscreen buffer in the {@link KJavaGfxInfo#offscreen offscreen} member of the 
 *   #KJavaGfxInfo structure for setting video device information.
 *
 * @par When the virtual screen offscreen buffer is not recreated in this function:
 * - If kjava_gfx_getInfo() is called after changing the screen mode by this function, reflect the new screen mode into the 
 *   {@link KJavaImage#width KJavaImage#width} and {@link KJavaImage#height KJavaImage#height} members 
 *   indicated by {@link KJavaGfxInfo#offscreen offscreen} of the #KJavaGfxInfo structure passed via kjava_gfx_getInfo().
 *
 */
int kjava_gfx_requestScreenMode(int screenMode);

/**
 * Gets the video device properties.
 * @param info
 *        A pointer to the #KJavaGfxInfo structure for putting the video device information.
 *
 * The information passed through <i>info</i> must reflect the current virtual screen mode.
 */
void kjava_gfx_getInfo(KJavaGfxInfo *info);

/**
 * Gets the information of the virtual-screen.
 * @return
 *        Return a pointer to the #KJavaImage structure holding the virtual screen information.
 *        This pointer must remain valid until next time this function is called.
 *
 * The virtual screen is a graphics off-screen, with the same size as the real screen.
 */
KJavaImage* kjava_gfx_getVirtualScreen(void);

/**
 * Starts drawing on the virtual screen
 *
 * From the time this function is called and until
 * kjava_gfx_paintVirtualEnd() is called, drawing takes place on the virtual screen.
 * During this time, drawing can be taking place in other off-screen buffers as well.
 *
 * If exclusive control is necessary for the processing requested by the KVE thread and that by other tasks, 
 * implement to suppress draw processing by threads other than the KVE thread between the time this function is called 
 * and kjava_gfx_paintVirtualEnd() is called.
 */
void kjava_gfx_paintVirtualBegin(void);

/**
 * Ends drawing on the virtual screen.
 * @param flush
 *        When this flag is 0, do not transfer the virtual screen
 *        contents to the real screen.
 * @param clip
 *        The clipping range for updating screen.
 *
 * Once this function completes its processing, treat drawing in the virtual
 * screen as temporarily stopped and send the drawing result to the real screen.
 *
 * It is also possible to remember the area updated between the time 
 * kjava_gfx_paintVirtualBegin() was called and this function was called, 
 * and to update only that area. 
 * During this time, drawing can be taking place in other off-screen buffers as well. 
 *
 */
void kjava_gfx_paintVirtualEnd(int flush,const KJavaClip* clip);

/**
 * Sets the type of the current Displayable displayed by the Java application.
 * @param type
 *        The displayable type. One of the following is designated:
 *        - #KJAVA_VIDEO_DISPLAYABLE_NULL
 *        - #KJAVA_VIDEO_DISPLAYABLE_SCREEN
 *        - #KJAVA_VIDEO_DISPLAYABLE_CANVAS
 *        - #KJAVA_VIDEO_DISPLAYABLE_PERMISSIONDIALOG
 *
 * This function is called when a Java application has changed the
 * current <code>Displayable</code> by calling
 * <code>javax.microedition.lcdui.Display</code> class
 * <code>setCurrent(Displayable)</code> method, or when
 * JBlendia displays a permission confirmation dialog.
 *
 * If no use is made of the information designated in this function
 * for drawing or other purposes, it may be implemented as an empty function.
 */
void kjava_gfx_setDisplayableType(int type);

/** @} */

/**
 * @addtogroup Image_Codec
 * @{
 */

/**
 *  Determines whether or not the native system can decode a compressed image.
 * @param  srcBuf
 *         A pointer to the buffer holding the compressed image of unknown format.
 * @param  srcSize
 *         The size in bytes of the image data in the buffer indicated by <i>srcBuf</i>.
 * @param  width
 *         A pointer to the buffer for putting the width of the image.
 * @param  height
 *         A pointer to the buffer for putting the height of the image.
 * @retval #KJAVA_CODEC_SUCCESS if the image can be decoded by the native system.
 * @retval #KJAVA_CODEC_UNSUPPORT if the image is not decodeable by the native system.
 *
 * Check the image format of the image given by <i>srcBuf</i> and
 * if the image can be decoded by the native system, store its
 * width and height in the buffers indicated by <i>width</i> and
 * <i>height</i> and return #KJAVA_CODEC_SUCCESS.
 */
int kjava_gfx_imageAnalyze(const unsigned char* srcBuf, unsigned int srcSize, int* width, int* height);

/**
 * Decodes a compressed image.
 * @param srcBuf
 *        A pointer to the buffer holding the compressed image to be decoded.
 * @param srcSize
 *        The size in bytes of the image data in the buffer indicated by <i>srcBuf</i>.
 * @param pixelData
 *        A pointer to the memory area for putting the pixel data of decoded source image
 * @param alphaData
 *        A pointer to the memory area for putting the alpha data of decoded source image
 * @param dataLength
 *        The size of the memory area for putting ARGB data. 
 *        This value is the multiplication result of the width and height passed from kjava_gfx_imageAnalyze().
 * @param processAlpha
 *        A pointer to the buffer for putting a flag indicating whether the alpha 
 *        channel should be used or not when drawing this image to an offscreen.
 *        - 0: Not use the alpha channel
 *        - 1: Use
 * @retval #KJAVA_CODEC_SUCCESS  
 *         if the image was normally decoded.
 * @retval #KJAVA_CODEC_UNSUPPORT  
 *         if the native decoder can't decode the source data format.
 * @retval #KJAVA_CODEC_BAD_FORMAT  
 *         if the data contains bad format.
 * @retval #KJAVA_CODEC_NO_RESOURCE  
 *         if enough resource could not be allocated to decode this image.
 *
 * <p>
 * Only an image data determined as decodeable by kjava_gfx_imageAnalyze() is passed to this function.
 */
int kjava_gfx_imageDecode( const unsigned char* srcBuf,
                           unsigned int srcSize,
                           KJavaPixel* pixelData,
                           unsigned char* alphaData,
                           int dataLength,
                           int *processAlpha);

/** @} */

#ifdef __cplusplus
}
#endif


#endif /* KJAVA_SYS_CODEC_HEADER */
