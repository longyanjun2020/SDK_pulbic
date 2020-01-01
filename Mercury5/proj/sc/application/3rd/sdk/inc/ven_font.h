#ifndef __VEN_FONT_DEFINE_H__
#define __VEN_FONT_DEFINE_H__
/**
 *
 * @file    ven_font.h
 * @brief   This file defines the font interface definition.
 *
 * @author  Code.Lin
 * @version $Id: ven_font.h 26478 2009-03-24 08:02:41Z steve.lee $
 *
 */

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_FONT_RET_SUCCESS        = 0, ///< operation completed successfully
    VEN_FONT_RET_BAD_PARAM      = 1, ///< invalid input parameters
    VEN_FONT_RET_FAILED         = 2, ///< WHAT? every code here is failed
    VEN_FONT_RET_OUT_OF_MEMORY  = 3, ///< memory is not enough to complete the operation
    VEN_FONT_RET_NOT_SUPPORT    = 4, ///< Unsupported operation
};
typedef u32 ven_font_ret_t;

enum
{
    VEN_FONT_SIZE_START          = 0,
    VEN_FONT_SIZE_SMALL = VEN_FONT_SIZE_START,
    VEN_FONT_SIZE_NORMAL,
    VEN_FONT_SIZE_LARGE,                ///< Only for number
    VEN_FONT_SIZE_DYNAMIC,              ///< using vector font
    VEN_FONT_SIZE_TOTAL,
};
typedef u32 ven_font_size_e;

enum
{
    VEN_FONT_STYLE_PLAIN        = 0,    ///< Plain style
    VEN_FONT_STYLE_BOLD,                ///< Bold style. Not support now
    VEN_FONT_STYLE_ITALIC,              ///< Italicized style. Not support now
    VEN_FONT_STYLE_UNDERLINED,          ///< Underlined style
    VEN_FONT_STYLE_OUTLINE,             ///< Outline style
    VEN_FONT_STYLE_TOTAL,
};
typedef u32 ven_font_style_e;

typedef void* ven_FontAttr;

typedef struct
{
    u32         width;                  ///< pixel width
    u32         height;                 ///< pixel height
    u32         pitch;                  ///< Bytes per row in bytes
    u16         bpp;                    ///< Bits per pixel
    u8         *pData;                  ///< Pointer to glyph raw data
} ven_Glyph_t;

typedef struct
{
    s8   xdelta;                        ///< x-delta pixel
    s8   ydelta;                        ///< y-delta pixel
    s8   xadvance;                      ///< advance width in pixels
    s8   yadvance;                      ///< advance height in pixels
} ven_GlyphBitmapInfo_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
/**
 *  ven_font_createFontAttribute
 *
 *  @brief  This function will create a handle of font attribute.
 *
 *  @param  FontSize   [in]Font size
 *  @param  FontStyle  [in]Font style
 *  @param  ppFontAttr [out]Handle of font attribute
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 *          VEN_FONT_RET_NOT_SUPPORT if the operation is unsupported
 */
ven_font_ret_t ven_font_createFontAttribute(ven_font_size_e FontSize, ven_font_style_e FontStyle, ven_FontAttr **ppFontAttr);

/**
 *  ven_font_getFontAttribute
 *
 *  @brief  This function will return the attribute of the given handle.
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  FontSize   [out]Font size. Accept NULL if you don・t need it
 *  @param  FontStyle  [out]Font style. Accept NULL if you don・t need it
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 */
ven_font_ret_t ven_font_getFontAttribute(ven_FontAttr *pFontAttr, ven_font_size_e *pFontSize, ven_font_style_e *pFontStyle);

/**
 *  ven_font_releaseFontAttribute
 *
 *  @brief  This function will release the resource of font attribute.
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *
 *  @retval none
 */
void ven_font_releaseFontAttribute(ven_FontAttr *pFontAttr);

/**
 *  ven_font_zoomVectorFont
 *
 *  @brief  This function will set Font height by setting glyph transform
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  Ratio    [in]The Zooming ratio
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 *
 *  @note MMI will keep the zoom ratio,
 *            users SHOULD reset the ratio to 1.0f before leaving.
 */
ven_font_ret_t ven_font_zoomVectorFont(ven_FontAttr *pFontAttr, float Ratio);

/**
 *  ven_font_setVectorFontSize
 *
 *  @brief  This function will set font size
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  Height [in]The Font height
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 *          VEN_FONT_RET_NOT_SUPPORT if the operation is unsupported
 */
ven_font_ret_t ven_font_setVectorFontSize(ven_FontAttr *pFontAttr, u32 Height);


/**
 *  ven_font_getGlyphInfo
 *
 *  @brief  This function will set Glyph bitmap infomation
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  nCode [in]The Font height
 *  @param  pInfo [out]Glyph bitmap infomation
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 */

ven_font_ret_t ven_font_getGlyphInfo(ven_FontAttr *pFontAttr, u16 nCode, ven_GlyphBitmapInfo_t *pInfo);

/**
 *  ven_font_getVectorFontSize
 *
 *  @brief  This function will set vector font Size
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *
 *  @retval vector font Size
 */
u32 ven_font_getVectorFontSize(ven_FontAttr *pFontAttr);

/**
 *  ven_font_getFontInfo
 *
 *  @brief  This function will return font information
 *
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  pHeight    [out]The storage of max height of all font rows related to the specified font ID. Accept NULL if you don・t need it
 *  @param  pAscent    [out]The storage of max ascent of all font rows related to the specified font ID. Accept NULL if you don・t need it
 *  @param  pDescent   [out]The storage of max descent of all font rows related to the specified font ID. Accept NULL if you don・t need it
 *  @param  pLeading   [out]For current font now, leading will always return 0. Accept NULL if you don・t need it
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 */
ven_font_ret_t ven_font_getFontInfo(ven_FontAttr *pFontAttr, u16 *pHeight, u16 *pAscent, u16 *pDescent, u16 *pLeading);

/**
 *  ven_font_getTextWidth
 *
 *  @brief  This function will return the pixel width of a string.
 *
 *  @param  pFontAttr   [in]Handle of font attribute
 *  @param  pText       [in]String buffer which contains what you want to show
 *  @param  pPixelWidth [out]Pixel width of the input text string
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 */
ven_font_ret_t ven_font_getTextWidth(ven_FontAttr *pFontAttr, u16 *pText, u32 *pPixelWidth);

/**
 *  ven_font_getTextFit
 *
 *  @brief  This function will return number of chars can fit in given width.
 *
 *  @param  pFontAttr   [in]Handle of font attribute
 *  @param  pText       [in]String buffer which contains what you want to calucate
 *  @param  pPixelWidth [in]Pixel width of to put the string buffer
 *  @param  pFitChar    [out]Number of chars can fit in given width
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 */
ven_font_ret_t ven_font_getTextFit(ven_FontAttr *pFontAttr, u16 *pText, u32 maxPixelWidth, u32 *pFitChar);

/**
 *  ven_font_createGlyph
 *
 *  @brief  This function will create a glyph data of the given unicode
 *
 *  @param  pFontAttr   [in]Handle of font attribute
 *  @param  nCode       [in]Unicode of glyph to get
 *  @param  ppGlyph    [out]Memory of glyph pointer to store the result
 *
 *  @retval VEN_FONT_RET_SUCCESS if success
 *          VEN_FONT_RET_FAILED if failed
 *          VEN_FONT_RET_BAD_PARAM if input parameter is invalid
 *          VEN_FONT_RET_OUT_OF_MEMORY if there is not enough memory to process the command
 */
ven_font_ret_t ven_font_createGlyph(ven_FontAttr *pFontAttr, u16 nCode, ven_Glyph_t **ppGlyph);

/**
 *  ven_font_releaseGlyph
 *
 *  @brief  This function will return number of chars can fit in given width.
 *
 *  @param  pGlyph   [in]Pointer to glyph to release
 *
 */
void ven_font_releaseGlyph(ven_Glyph_t *pGlyph);

#endif // __VEN_FONT_DEFINE_H__

