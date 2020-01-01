/**
 * @file mmi_mae_text_util.h
 *
 * @version $Id: mmi_mae_text_util.h $
 */
#ifndef __MMI_MAE_TEXT_UTIL_H__
#define __MMI_MAE_TEXT_UTIL_H__
#include "mmi_mae_common_def.h"

/*
@brief - to define a ucs2 code of white space character.
*/
#define TEXT_WHITE_SPACE 0x0020
#define TEXT_LINE_FEED   0x000A
#define TEXT_CARRIAGE_RETURN   0x000D

#define TEXT_CHINESE_UNICODE_SECTION1_START  0x4E00
#define TEXT_CHINESE_UNICODE_SECTION1_END    0x709D
#define TEXT_CHINESE_UNICODE_SECTION2_START  0x70AB
#define TEXT_CHINESE_UNICODE_SECTION2_END    0x9FA0
#define TEXT_THAI_UNICODE_SECTION_START      0x0E00
#define TEXT_THAI_UNICODE_SECTION_END        0x0F7F

#define TEXT_MAX_COMPOSED_SIZE 10

#define MAETEXTUTIL_IsReturnChar(_Char_) ((u16)_Char_ == 0x000A || (u16)_Char_ == 0x000D)

#define MAETEXUTIL_IsChineseChar(_Char_) ( ((_Char_ >= TEXT_CHINESE_UNICODE_SECTION1_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION1_END) || \
                                                (_Char_ >= TEXT_CHINESE_UNICODE_SECTION2_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION2_END)) )

#define MAETEXUTIL_IsChineseThaiChar(_Char_) ( ((_Char_ >= TEXT_CHINESE_UNICODE_SECTION1_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION1_END) || \
                                                (_Char_ >= TEXT_CHINESE_UNICODE_SECTION2_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION2_END)) || \
                                               (_Char_ >= TEXT_THAI_UNICODE_SECTION_START && _Char_ <= TEXT_THAI_UNICODE_SECTION_END) )
#ifdef __BIDI_TEXT__
/*
@brief - to check a input language is RTL or LTR display direction. ( ARABIC, HEBREW now )
*/
#define MAETEXTUTIL_BidiIsRTL( _Level_ ) ( (_Level_ % 2) == 1 )
#endif //__BIDI_TEXT__
typedef enum
{
    MAE_TEXTUTIL_BL_FORWARD,
    MAE_TEXTUTIL_BL_BACKWARD
}Mae_TextUtil_BLDirection_e;

typedef struct
{
    MAE_WChar nBLChar;
    boolean bBackwardBreak;
}Mae_TextUtil_BL_t;

typedef struct
{
    Mae_TextUtil_BL_t *pBLTable;
    u16 nBLTableSize;
}Mae_TextUtil_BLTable_t;

/****************/
/* Text convert */
/****************/

/*
@brief - Convert text to display string. note that only the first paragraph will be convert to display string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]ppu16DisplayStr: a double pointer of display string, allocate by this function and need to free it by caller.
@return - [out]u32: the length of display string
*/
u32     MAETEXTUTIL_TextToDisplayString( const MAE_WChar *pString, u32 nStrLen, boolean bDisplayRTL, MAE_WChar **ppwDisplayStr, boolean *pIsRTLStr, boolean bWithoutBidi );

/*
@brief - invert part of sequence characters in ucs2 string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string
@param - [in]nOffset: the start position that want to invert in this string
@param - [in]pSubLength: the length that want to invert
@param - [in][out]pSourcePos: Get the original string location position after invert.
                                 if doesn't get the information, assign to NULL
@return - none
*/
void    MAETEXTUTIL_UCS2Invert( MAE_WChar *pString, u32 nStrLen, u32 nOffset, u32 pSubLength, u16 *pSourcePos );

/*
@brief - remove a chararcter at x index in a ucs2 string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string after removed a character
@param - [in]nOffset: the position of character that want to remvoed in this string
@return - [out]u32: the remain string length after remove a character
*/
u32     MAETEXTUTIL_UCS2RemoveCharAt( MAE_WChar *pString, u32 nStrLen, u32 nOffset );

boolean MAETEXTUTIL_UCS2IsComposedNextChars( const MAE_WChar *pString, u32 nStrLen, u32 nOffset, MAE_WChar **ppComposedStr, u32 *pComposedLen, u32 *paConsumed, boolean bDispStr );
boolean MAETEXTUTIL_UCS2IsComposedPreChars( const MAE_WChar *pString, u32 nStrLen, u32 nOffset, MAE_WChar **ppComposedStr, u32 *pComposedLen, u32 *paConsumed, boolean bDispStr );

#ifdef __MMI_BIDI_UI__
boolean MAETEXTUTIL_IsRTLDisplayLanguage( void );
boolean MAETEXTUTIL_IsRTLLanguage( u8 nLan );
#endif //__MMI_BIDI_UI__

#ifdef __BIDI_TEXT__
/*
@brief - Check a paragraph text's display direction.
@param - [in]pu16String: a ucs2 string.
@param - [in]nStrLen: the length of ucs2 string.
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@return - [out]boolean: The paragraph text is display RTL or LTR. TRUE, is RTL.
*/
boolean MAETEXTUTIL_ParagraphIsRTL( const MAE_WChar *pString, u32 nStrLen, boolean bDisplayRTL );

/*
@brief - Check a character is an Arabic character.
@param - [in]u16Char: a ucs2 character
@return - [out]boolean: Is an Arabic character or not. TRUE, an Arabic character.
*/
u32     MAETEXTUTIL_MeasureMixedLine( const MAE_WChar *pString, u32 nStrLen, u32 nOffset, u32 nLineStrLen, boolean bDiffDirChangeLine );


#endif //__BIDI_TEXT__

boolean MAETEXTUTIL_MeasureTextToLineBreak( const MAE_WChar *pText, u32 nStrLen, u32 nWidth,u32 nFontCate, u32 nFontSize, u32 nFontType, boolean bDiffDirChangeLine, u32 *pu32FitLen, Mae_TextUtil_BLTable_t *pBLCodeTable );

#ifdef __BIDI_TEXT__

/**********/
/* Arabic */
/**********/
/*
@brief - conver a ucs2 arabic string to a display string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]u32: the display string length after convert to arabic string.
                   (the string length maybe changed after converting)
*/
u32     MAETEXTUTIL_ConvertToArabicStr( MAE_WChar *pString, u32 nStrLen, boolean bDispStr );

boolean MAETEXTUTIL_ConvertToArabicFEStr( MAE_WChar *pString, u32 nStrLen, boolean bDispStr );

u16 MAETEXTUTIL_ConvertToArabicFEChar( const MAE_WChar *pString, u32 nStrLen, u32 nOffset, boolean bDispStr, u16 *pNextFEChar );

/*
@brief - conver a ucs2 Europe number to a Arabic number.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]u32: the string length after converting.
*/
u32     MAETEXTUTIL_NumConvertToArabicNum( MAE_WChar *pString, u32 nStrLen );

/*
@brief - conver a ucs2 Arabic number to a Europe number.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]u32: the string length after converting.
*/
u32     MAETEXTUTIL_ArabicNumConvertToNum( MAE_WChar *pString, u32 nStrLen );

/*
@brief - Check text is include arabic characters in it.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]boolean: Is an arabic text or not. TRUE, an Arabic text.
*/
boolean MAETEXTUTIL_IsArabicText( const MAE_WChar *pString, u32 nStrLen );

/*
@brief - Check a character is an Arabic character.
@param - [in]u16Char: a ucs2 character
@return - [out]boolean: Is an Arabic character or not. TRUE, an Arabic character.
*/
boolean MAETEXTUTIL_IsArabicChar( MAE_WChar nChar );

/*
@brief - Check a character is concatenate to pre-character or next-character.
@param - [in][out]pu16Char: a ucs2 character that want to check. the return value the convered character for display
@param - [in]u16PreChar: the character before the checked character. If the checked character
                         is first and assign this value to 0.
@param - [in]u16NextChar: the character after the checked character. If the checked character
                          is last and assign this value to 0.
@param - [in][out]pbInWord: notic the check character is in a word (not the first or last character of a word)
                            if the check character is a first character of a word, assign to FALSE.
                            You maybe should keep the value for check a sequence string by it.
@param - [in][out]pbPreCharIsFirst: notic the pre-character is the first character in a word.
                                    if the check character is a first character of a word, assign to FALSE.
                                    You maybe should keep the value for check a sequence string by it.
@return - [out]boolean: Is an concatenatin character or not. TRUE, an concatenation character.
*/
boolean MAETEXTUTIL_ConcatenationArabicFEChar( MAE_WChar *pChar, MAE_WChar nNextChar );


/******************/
/* Bidi paragraph */
/******************/

/*
@brief - Check a character is an paragraph character.
@param - [in]u16Char: a ucs2 character
@return - [out]boolean: Is an paragraph character or not. TRUE, an paragraph character.
*/
boolean MAETEXTUTIL_BidiIsParagraphChar( MAE_WChar nChar );

__SLDPM_FREE__ boolean MAETEXTUTIL_BidiIsRTLChar( MAE_WChar nChar );

#endif //__BIDI_TEXT__

/*
@brief - To get the first paragraph length from a input text.
@param - [in]pu16String: a ucs2 string.
@return - [out]u32: a paragraph string length.
*/
u32     MAETEXTUTIL_BidiGetParagraphLength( const MAE_WChar *pString, u32 nStrLen );

/*
@brief - To only order the first paragraph of a input text.
@param - [in][out]pu16String: a ucs2 string.
@param - [in][out]pStrLen: input string length and change to paragraph string length after calling.
@param - [in][out]pbDisplayRight2Left: the string display direction.
@param - [out]ppSeqPos: the paragraph logical order of ordering string.
                           Allocate memory in this function, and must free by caller.
@return - [out]boolean: success or not. TRUE, success.
*/
boolean MAETEXTUTIL_BidiOrderParagraph( MAE_WChar *pString, u32 *pStrLen, boolean bDisplayRight2Left, u16 **ppSeqPos, u8 **ppCharLevel );


/**********************/
/* Bidi order handler */
/**********************/

/*
@brief - To create a bidi handler.
@return - [out]void*: a pointer of bidi handler.
*/
__SLDPM_FREE__ void*   MAETEXTUTIL_BidiCreateHandler( void );

/*
@brief - To free a bidi handler.
@param - [in]pHandler: a pointer of bidi handler.
@return - none.
*/
void    MAETEXTUTIL_BidiFreeHandler( void *pHandler );

#ifdef __BIDI_TEXT__
/*
@brief - To order the input text. (support multi-paragraph)
         ordering result is record in bidi handler. you can access information by bidi handler.
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]pu16String: a ucs2 string.
@param - [in]nStrLen: input string length.
@param - [in]bDisplayRight2Left: the string display direction.
@return - [out]boolean: success or not. TRUE, success.
*/
__SLDPM_FREE__ boolean MAETEXTUTIL_BidiOrderText( void *pHandler, const MAE_WChar *pString, u32 nStrLen, boolean bDisplayRight2Left );
#endif //__BIDI_TEXT__
boolean MAETEXTUTIL_BidiInsertText( void *pHandler, const MAE_WChar *pString, u32 nStrLen, boolean bDisplayRight2Left );
boolean MAETEXTUTIL_BidiReorderText( void *pHandler, u32 nOffset, const MAE_WChar *pString, u32 nStrLen );

/*
@brief - To re-init the bidi hanlder's line table.
@param - [in]pHandler: a pointer of bidi handler.
@return - none.
*/
void    MAETEXTUTIL_BidiInitTable( void *pHandler );

/*
@brief - To add a new line information to bidi handler's line table.
         It will make the bidi order input string depend on your line information.
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]nOffset: the line begin offset in a text.
@param - [in]nStrLen: the line string length.
@param - [in]bRTL: the line display direction. (depend on current display language)
@return - [out]boolean: success or not. TRUE, success.
*/
__SLDPM_FREE__ boolean MAETEXTUTIL_BidiAddLine( void *pHandler, u32 nOffset, u32 nStrLen, boolean bRTL );

boolean MAETEXTUTIL_BidiModifyLineInfo( void *pHandler, u32 u32Line, u32 nOffset, u32 nStrLen, boolean bRTL );

/*
@brief - To get the bidi handler's line table size.
@param - [in]pHandler: a pointer of bidi handler.
@return - [out]u32: the table size.
*/
u32     MAETEXTUTIL_BidiGetTableSize( void *pHandler );

boolean MAETEXTUTIL_BidiSetTableSize( void *pHandler, u32 u32Size );

/*
@brief - To get a order line's information (after ordering a string by bidi).
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]u32Index: the index of line in handler's line table.
@param - [out]pOffset: the line string begin offset in a input text.
@param - [out]pLineStrLen: the line string length.
@param - [out]pbRTL: the line string display direction.
@param - [out]ppLineString: the line ordering string.
                               Allocate memory in this function, and must free by caller.
@param - [out]ppSeqInLine: the line logical order of ordering string.
                              Allocate memory in this function, and must free by caller.
@return - [out]boolean: success or not. TRUE, success.
*/
boolean MAETEXTUTIL_BidiGetLineInf( void *pHandler, u32 u32Index, u32 *pOffset, u32 *pLineStrLen, boolean *pbRTL, u16 **ppLineString, u16 **ppSeqInLine, u8 **pCharLevel );

u16* MAETEXTUTIL_BidiGetOrderStr( void *pHandler, u32 *pStrLen );

#endif /* __MAE_TEXT_UTIL_H__ */
