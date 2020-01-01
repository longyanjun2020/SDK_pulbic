/**
 * @file mmi_mae_font_base.h
 *
 * @version $Id: mmi_mae_font_base.h 1643 2009-08-24 09:22:48Z bill.pan $
 */
#ifndef __MMI_MAE_FONT_BASE_H__
#define __MMI_MAE_FONT_BASE_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_common_def.h"
#include "mmi_mae_graphic_forward.h"
#include "mmi_mae_bitmap_forward.h"
#include "mmi_mae_dib_forward.h"
#include "mmi_mae_font_forward.h"
#include "mmi_mae_langcode.h"

/******************************/
/*        DEFINITION          */
/******************************/
#define MAX_VECTOR_FONT_NUM 10
#define MAX_CODE_COUNT      10
#define OUTLINE_PIXEL       1
//Font types
#define FONT_TYPE_NORMAL    0x00000000
#define FONT_TYPE_OUTLINE   0x00000001
#define FONT_TYPE_UNDERLINE 0x00000002
#define FONT_TYPE_EXPAND1   0x00000004
#ifdef __MMI_SCRIPT_EASY__
#define FONT_TYPE_SE_ELLIPSE 0x00000010
#endif

typedef u32 FontType_t; //normal / outline / underline / expand1

#ifdef __FEATURE_VECTOR_FONT__
typedef void (*Change_Font_Result_CB) (void *pUserData, MAE_Ret nRetVal);
#endif

#define FONT_CONTROL_ZWNJ 0x200C
#define FONT_CONTROL_ZWJ  0x200D

#define EMPTY_CHAR(ch) (ch==0x0A || ch==0x0D)

typedef struct
{
	MAE_LANG_CODE_e nLangCode;
	u32 nCount;
    u32 *pFontId;
}CusDispLangData_t;

/**
* Flags in Font
*/
enum
{
	FONT_FLAG_START = 0,
	FONT_FLAG_NO_CONVERT_RTL = FONT_FLAG_START,
	FONT_FLAG_SUPPORT_MULTI_LINE,
	FONT_FLAG_END
};

/**
* Flag Mask
*/
#define FONT_MASK_NO_CONVERT_RTL				(1<<FONT_FLAG_NO_CONVERT_RTL)
#define FONT_MASK_SUPPORT_MULTI_LINE			(1<<FONT_FLAG_SUPPORT_MULTI_LINE)

/**
* Macro to get flag value
*/
#define FONT_IS_NO_CONVERT_RTL(_nFlags) \
	(boolean)((_nFlags&FONT_MASK_NO_CONVERT_RTL)>>FONT_FLAG_NO_CONVERT_RTL)
#define FONT_IS_SUPPORT_MULTI_LINE(_nFlags) \
	(boolean)((_nFlags&FONT_MASK_SUPPORT_MULTI_LINE)>>FONT_FLAG_SUPPORT_MULTI_LINE)

/**
* Macro to Set flag value
*/
#define FONT_SET_NO_CONVERT_RTL(_nFlags, _b) \
	_nFlags = (_nFlags&(~FONT_MASK_NO_CONVERT_RTL))|(((u32)_b)<<FONT_FLAG_NO_CONVERT_RTL)
#define FONT_SET_SUPPORT_MULTI_LINE(_nFlags, _b) \
	_nFlags = (_nFlags&(~FONT_MASK_SUPPORT_MULTI_LINE))|(((u32)_b)<<FONT_FLAG_SUPPORT_MULTI_LINE)


/* Font create functions */
MAE_Ret FONTBASE_New(MAE_ClsId nId, void **ppIFont);
MAE_Ret FONTBASE_Release(FontBase_t *pIfont);
/* Font API */
MAE_Ret FontBase_InitEx(boolean bLoadDefault);
MAE_Ret FontBase_FreeEx(void);
MAE_Ret FONTBASE_MeasureText(FontBase_t *pIFont, u32 nFontCate,u32 nFontSize, const u16 *pText, u32 nChars,
                         u32 nMaxWidth, u32 *pFits, u32 *pPixels, u32 nType, u32 nSkip);
MAE_Ret FONTBASE_MeasureTextBidi( FontBase_t *pIFont,
                                           u32 nFontCate,
                                           u32 nFontSize,
                                           const u16 *pText,
                                           u32 nChars,
                                           u32 nOffset,
                                           u32 nSubLen,
                                           u32 nMaxWidth,
                                           u32 *pFits,
                                           u32 *pPixels,
                                           u32 nType,
                                           u32 nSkip,
                                           boolean bDispStr );
MAE_Ret FONTBASE_MeasureTextEx(FontBase_t *pIFont,
                                        u32 nFontCate,                   // category
                                        u32 nFontSize,
                                        const u16 *pText,               // text buffer pointer
                                        u32 Chars,                      // number of text character
                                        u32 u32Offset,
                                        u32 u32SubLen,                  // still number of text character
                                        u32 MaxWidth,
                                        u32 *pFits,                     // [out]
                                        u32 *pPixels,                   // [out]
                                        u32 Type,
                                        u32 bSkip,
                                        boolean bDispStr);               // FALSE

MAE_Ret FONTBASE_DrawText(FontBase_t *pIFont, u32 nFontCate, u32 nFontSize, BitmapBase_t *pDst, s32 x,
                  s32 y, const u16 *pText, u32 nChars, RGBColor_t nFq,
                  RGBColor_t bg, const Rect_t *pRect, u32 nFlags, u32 *pColors, u8 nNumColor);
MAE_Ret FONTBASE_DrawTextEx(FontBase_t *pIFont,
                             u32 nFontCate,              // category
                             u32 nFontSize,              // size
                             BitmapBase_t *pDst,        // Destination BitmapBase
                             s32 xStart,                // start x
                             s32 yStart,                // start y
                             const u16 *pText,          // text buffer pointer
                             u32 Chars,                 // number of text character
                             RGBColor_t ClrFG,          // foreground color
                             RGBColor_t ClrOL,          // background color
                             const Rect_t *pRect,       // Client area
                             u32 nType,                  // Type
                             u32 *pColors,              // Color table for the random FG. (Random FG for each character. if this parameter is set the ClrFG param will be ignored)
                             u8 nNumColor);              // total number of colors in the Color table
MAE_Ret FONTBASE_GetInfo(FontBase_t *pIFont, u32 nFontCate,u32 nFontSize, u32 nType, FontInfo *pinfo);

MAE_Ret FONTBASE_GetInfoEx(FontBase_t *pIFont,
                           		  u32 nFontCate,           // Font Size to query
	                              u32 nFontSize,
			        			  u32 Type,
                                  FontInfo *pinfo);
MAE_Ret FONTBASE_CreateGlyphDib(FontBase_t *pIFont,
                            u32 FontCat,
                            u32 nFontSize,
                            u32 nType,
                            u16 nCode,
                            pDIB *pDib);
MAE_Ret FONTBASE_CreateGlyphDibEx(FontBase_t *pIFont,
                            u32 FontCate,
                            u32 nFontSize,
                            u32 Type,
                            u16 Code,
                            pDIB *ppDib);

#ifdef __FEATURE_VECTOR_FONT__

/* if u32BufferSize  < minimum buffer size, set buffer size as minimum 
   else if	u32BufferSize > defualt buffer size, set buffer size as default */
//void FONTBASE_VectorFontReInit(u32 u32BufferSize);
boolean FONTBASE_IsVectorFontExist(void);
boolean FONTBASE_IsVectorFontCombineBitmap(void);
MAE_Ret FONTBASE_MapToVectorFont(u32 FontCate, u32 FontSize);
MAE_Ret FONTBASE_ZoomVectorFont(float ZoomFactor);
MAE_Ret FONTBASE_CreateVectorFont(const void* data, u32 size);
MAE_Ret FONTBASE_GetGlyphDibInfo(FontBase_t *pIFont,
                            u32 FontCat,
                            u32 FontSize,
                            u32 Type,
                            u16 Code,
                            u8 *xDelta, u8 *yDelta, s8 *xAdvance, s8 *yAdvance);

MAE_Ret FONTBASE_VectorFontChangeFontFromFile(const MAE_WChar *pFileURL);
MAE_Ret FONTBASE_VectorFontChangeFontFromCard(const MAE_WChar *pFileURL, void *pUserData, Change_Font_Result_CB pResultCB);
MAE_Ret FONTBASE_VectorFontChangeFontFromCus(u32 nFontId);
void FONTBASE_VectorFontCancelChangeFont(void);

u32 FONTBASE_VectorFontLangCodeGetIndex(MAE_LANG_CODE_e eLangCode, u32 nFontId);
u32 FONTBASE_VectorFontLangCodeGetFontID(MAE_LANG_CODE_e eLangCode, u32 nIndex);
u32 FONTBASE_VectorFontGetCusFontCount(void);
u32 FONTBASE_VectorFontGetCusLangFontCount(MAE_LANG_CODE_e eLangCode);
#endif


#endif /* __MAE_FONT_BASE_H__ */
