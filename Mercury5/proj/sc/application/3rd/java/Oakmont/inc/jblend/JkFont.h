/**
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkFont.h
 * Fonts
 */
/**
 * @addtogroup Font_JSI
 * @{
 */

#ifndef ___JK_FONT_H
#define ___JK_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * Plain font
 */
#define JK_FONT_STYLE_PLAIN         0

/**
 * Bold font
 */
#define JK_FONT_STYLE_BOLD          1

/**
 * Italic font
 */
#define JK_FONT_STYLE_ITALIC        2

/**
 * Underline font
 */
#define JK_FONT_STYLE_UNDERLINE     4

/**
 * Monospace font
 */
#define JK_FONT_FACE_MONOSPACE      32

/**
 * Proportional font
 */
#define JK_FONT_FACE_PROPORTIONAL   64


/**
 * Font size
 */
typedef struct JKT_Font_Size {
    /**
     * SMALL font size
     */
    JKSint32 smallSize;

    /**
     * MEDIUM font size
     */
    JKSint32 mediumSize;

    /**
     * LARGE font size
     */
    JKSint32 largeSize;
} JKT_Font_Size;


/**
 * A handle for font identification
 */
typedef JKHandle JKFontHandle;

/**
 * The default font used for low-level graphics drawing
 */
#define JK_FONT_TYPE_DEFAULT        0

/**
 * The display font used by the GUI
 */
#define JK_FONT_TYPE_STATIC_TEXT    0x1000

/**
 * The editing font used by the GUI
 */
#define JK_FONT_TYPE_INPUT_TEXT     0x1001



/**
 * Gets the default font in use by the platform.
 *
 * @param type
 *        The font type
 *
 *         One of the following is designated.
 *         <ul>
 *          <li> #JK_FONT_TYPE_DEFAULT
 *          <li> #JK_FONT_TYPE_STATIC_TEXT
 *          <li> #JK_FONT_TYPE_INPUT_TEXT
 *         </ul>
 * @return
 *        Return a handle identifying the designated font.
 *
 * Of the fonts used by the platform, return that of the designated type.
 * Return the handle of a font defined in advance in the platform.
 * Even when a handle obtained by this function is no longer needed, there will be no 
 * request made for its disposal by JkFontDispose().
 * 
 * When only one font is available on the platform, or it is otherwise not 
 * possible to assign an individual font to each type, return the handle of an 
 * available font.
 * 
 * Values other than constants named starting with "JK_FONT_TYPE_" are never 
 * designated in the type parameter.
 *
 * @see JkFontCreate()
 * @see JkFontDispose()
 */
JKFontHandle JkFontGetDefault( JKSint32 type );


/**
 * Gets the fonts sizes for large, medium and small.
 *
 * @param size
 *        This is the memory location where the requested size information is to be put.
 *
 * In the designated memory location, put the sizes specified for large, medium and small fonts used by the platform.
 * The font size obtained by this function is designated to #JkFontCreate() as a parameter.
 * 
 * If the platform supports fewer than three font sizes, designate the same value for two or more members as follows.<br>
 * <dl>
 *   <dt>If there is only one font size</dt>
 *   <dd>Designate the same value for smallSize, mediumSize, and largeSize.</dd>
 *   <dt>If there are two font sizes</dt>
 *   <dd>Assign the smaller size to smallSize and mediumSize, and the larger font size to largeSize.</dd>
 *   <dd>Or, assign the smaller size to smallSize, and the larger size to mediumSize and largeSize.</dd>
 * </dl>
 * 
 * In no case is a NULL pointer designated in the size parameter.
 *
 * @see JkFontCreate()
 */
void JkFontGetDefaultSize( JKT_Font_Size *size );


/**
 * Creates a font of the designated type.
 *
 * @param size
 *        The font size
 * @param fontType
 *        The font type. This information is designated as the logical OR of
 *        JK_FONT_STYLE_XXXX and JK_FONT_FACE_XXXX.
 * @return
 *        Return a handle identifying the designated font.
 *
 * Return the font most similar to that designated, of those used in the platform.
 * When the handle obtained by this function is no longer needed, a request is
 * made to dispose of it by JkFontDispose().
 * 
 * Values other than the logical-OR of JK_FONT_STYLE_XXXX and JK_FONT_FACE_XXXX 
 * are never designated in the fontType parameter.
 * When neither JK_FONT_FACE_MONOSPACE nor JK_FONT_FACE_PROPOTIONAL is specified, 
 * please give as that Font.FACE_SYSTEM was specified to be by Java application. 
 *
 *  @par For compliance with JTWI 1.0:
 *  The implementation must enable use of the character fonts specified in Table 
 *  4, "Characters Supported by TextBox and TextField," Section 4.9,  "Supported 
 *  Characters in TextField and TextBox," in "Java  Technology for the Wireless 
 *  Industry Specification, Version 1.0."
 *
 * @see JkFontGetDefault()
 * @see JkFontDispose()
 */
JKFontHandle JkFontCreate( JKSint32 size, JKSint32 fontType );

/**
 * Disposes of a font.
 *
 * @param hFont
 *        The handle of the font to be disposed of. This is the value returned by JkFontCreate().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 * 
 * @see JkFontCreate()
 */
void JkFontDispose( JKFontHandle hFont );

/**
 * Gets the font type.
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @return
 *        The font type designated in the hFont parameter should be returned as the 
 *        bitwise OR of JK_FONT_STYLE_XXXX and JK_FONT_FACE_XXXX.
 *
 * Return the actual font state, not the value designated to JkFontCreate().<br>
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetType( JKFontHandle hFont );

/**
 * Gets the font leading.
 *
 * @image html FontImage.gif
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @return
 *        Return the font leading.
 *
 * Return a value based on actual font information, not a value based on the size
 * designated to JkFontCreate().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetLeading( JKFontHandle hFont );

/**
 * Gets the font ascent.
 *
 * @image html FontImage.gif
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @return
 *        Return the ascent for the designated font.
 *
 * Return a value based on actual font information, not a value based on the size
 * designated with JkFontCreate().<br>
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetAscent( JKFontHandle hFont );

/**
 * Gets the font descent.
 *
 * @image html FontImage.gif
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @return
 *        Return the font descent.
 *
 * Return a value based on actual font information, not a value based on the size
 * designated with JkFontCreate().<br>
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetDescent( JKFontHandle hFont );

/**
 * Gets the width of the designated character.
 * 
 * @image html FontImage2_en.gif
 * 
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @param c
 *        The character, in Unicode.
 * @return
 *        Return the width of the character in the designated font including the space
 *        up to the next character, in pixels.
 *        If the character is not defined in the platform, return the width of a 
 *        single blank space.
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetCharWidth( JKFontHandle hFont, JKWChar c );

/**
 * Gets the height of the designated font.
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @return
 *        Return the height of the designated font.
 *
 * Return a value based on actual font information, not a value based on the size
 * designeated to JkFontCreate().
 * 
 * In no case is #JK_INVALID_HANDLE designated in the hFont parameter.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetHeight( JKFontHandle hFont );

/**
 * Gets the width of the designated character string.
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or JkFontCreate().
 * @param str
 *        A pointer to the character string, given as Unicode.
 * @param length
 *        The number of characters in specified character string.
 * @return
 *        Return the width of the character string in the designated font.
 * 
 * If the string designated in the str parameter contains a character not defined in 
 * the platform, substitute a blank space for that character and continue processing. <br>
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the hFont parameter.
 *  <li>Designating a NULL pointer in the str parameter.
 *  <li>Designating a value less than 0 in the length parameters.
 * </ul>
 * 
 * If the platform text display specification requires kerning,
 * return the character string drawing width after kerning.
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontGetStringWidth( JKFontHandle hFont, const JKWChar *str, JKSint32 length );

/**
 * Gets the number of characters that fit in the designated width.
 *
 * @param hFont
 *        The font handle. This is the value returned by JkFontGetDefault() or 
 *        JkFontCreate().
 * @param str
 *        A pointer to the character string, given as Unicode.
 * @param length
 *        The number of characters in the designated character string.
 * @param width
 *        The width (in pixels).
 * @return
 *        Return the number of characters.
 *        If the string designated in the str parameter contains a character not 
 *        defined in the platform, treat it as a single blank space.
 *
 * Calculate the number of characters that will fit in the designated width when the
 * designated string is drawn in the designated font, starting from the beginning of the
 * width.
 * 
 * The following illegal parameters designations are not to be made.
 * <ul>
 *  <li>Designating #JK_INVALID_HANDLE in the hFont parameter.
 *  <li>Designating a NULL pointer in the str parameter.
 *  <li>Designating a value less than 0 in the length or width parameters.
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
 *
 * @see JkFontGetDefault()
 * @see JkFontCreate()
 */
JKSint32 JkFontCountChars( JKFontHandle hFont, const JKWChar *str,
                            JKSint32 length, JKSint32 width );

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */
