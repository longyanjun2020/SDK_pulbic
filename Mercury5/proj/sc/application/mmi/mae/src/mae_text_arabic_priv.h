/**
 * \file    mae_font_priv.h
 * \brief   The document describes the private data structure used in mae_font.c
 *
 * @version
 */
#ifdef __BIDI_TEXT__

#ifndef __MAE_TEXT_ARABIC_PRIV_H__
#define __MAE_TEXT_ARABIC_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_common_def.h"

/******************************/
/*        DEFINITION          */
/******************************/
/* Arabic ROW definition */
#define TEXT_ARABIC_ROW        0x06 /* Arabic row */
#define TEXT_ARABIC_FORM_B_ROW 0xFE /* Arabic presentation forms-B row */
#define TEXT_ARABIC_FORM_A_ROW 0xFB /* Arabic presentation forms-A row */

/* COL ranges definition in Arabic row */
#define TEXT_ARABIC_HAMZA_CHAR 0x21 /* HAMZA char is 0x06 0x21 | always in PL so not converted */
#define TEXT_ARABIC_GHAIN_CHAR 0x3A /* GHAIN char is 0x06 0x3A */
#define TEXT_ARABIC_FEH_CHAR   0x41 /* FEH   char is 0x06 0x41 */
#define TEXT_ARABIC_YEH_CHAR   0x4A /* YEH   char is 0x06 0x4A */
#define TEXT_ARABIC_WASLA_CHAR 0x71 /* WASLA char is 0x06 0x71 | always in PL so not converted */

#define TEXT_ARABIC_INDIC_DIGIT_ZERO     0x60 /* Arabic-indic digit zero is 0x06 0x60 */
#define TEXT_ARABIC_INDIC_DIGIT_NINE     0x69 /* Arabic-indic digit nine is 0x06 0x69 */
#define TEXT_ARABIC_INDIC_DIGIT_ASTERISK 0x6D /* Arabic-indic asterisk   is 0x06 0x6D */

/* For concatenation */
#define TEXT_ARABIC_LAM_CHAR_PL              0xDD /* LAM (PL) char is 0xFE 0xDD can be concatened  with: */
#define TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL 0x81 /* - ALEF with MADDA ABOVE (PL) is 0xFE 0x81  */
#define TEXT_ARABIC_ALEF_HAMZA_ABOVE_CHAR_PL 0x83 /* - ALEF with HAMZA ABOVE (PL) is 0xFE 0x83  */
#define TEXT_ARABIC_ALEF_HAMZA_BELOW_CHAR_PL 0x87 /* - ALEF with HAMZA BELOW (PL) is 0xFE 0x87  */
#define TEXT_ARABIC_ALEF_CHAR_PL             0x8D /* - ALEF                  (PL) is 0xFE 0x8D  */
#define TEXT_ARABIC_ALFB_WASLA_CHAR_PL       0x50 /* - ALFB with WASLA (PL) is 0xFB 0x50  */

#define TEXT_ARABIC_LIG_LAM_ALEF_MADDA_ABOVE_CHAR_PL 0xF5 /* - ligature LAM with ALEF with MADDA ABOVE (PL) is 0xFE 0xF5  */
#define TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_ABOVE_CHAR_PL 0xF7 /* - ligature LAM with ALEF with HAMZA ABOVE (PL) is 0xFE 0xF7  */
#define TEXT_ARABIC_LIG_LAM_ALEF_HAMZA_BELOW_CHAR_PL 0xF9 /* - ligature LAM with ALEF with HAMZA BELOW (PL) is 0xFE 0xF9  */
#define TEXT_ARABIC_LIG_LAM_ALEF_CHAR_PL             0xFB /* - ligature LAM with ALEF                  (PL) is 0xFE 0xFB  */

#define TEXT_GET_ROW(_CHAR_) ((u8)(_CHAR_ >> 8))
#define TEXT_GET_COL(_CHAR_) ((u8)(_CHAR_ & 0x00FF))
#define TEXT_SET_ROW(_CHAR_, _ROW_) (_CHAR_ = (u16)((_CHAR_ & 0x00FF) + ((u16)(_ROW_) << 8)))
#define TEXT_SET_COL(_CHAR_, _COL_) (_CHAR_ = (u16)((_CHAR_ & 0xFF00) + ((u16)(_COL_) & 0x00FF)))
#define TEXT_SET_CHAR(_ROW_, _COL_) ((((u16)(_ROW_)) << 8) + ((u16)(_COL_)))

#define TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT( _CHAR_ ) ((TEXT_GET_COL(_CHAR_) == 0x71) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x77) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x79) && (TEXT_GET_COL(_CHAR_) <= 0x7B)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x7E) && (TEXT_GET_COL(_CHAR_) <= 0x80)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x83) && (TEXT_GET_COL(_CHAR_) <= 0x84)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x86) && (TEXT_GET_COL(_CHAR_) <= 0x88)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0x8C) && (TEXT_GET_COL(_CHAR_) <= 0x8E)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x91) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0x98) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA4) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA6) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xA9) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xAD) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xAF) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xB1) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xB3) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xBA) && (TEXT_GET_COL(_CHAR_) <= 0xBB)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xBE) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xC0) && (TEXT_GET_COL(_CHAR_) <= 0xC1)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xC5) && (TEXT_GET_COL(_CHAR_) <= 0xC9)) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xCB) && (TEXT_GET_COL(_CHAR_) <= 0xCC)) || \
                                                               (TEXT_GET_COL(_CHAR_) == 0xD0) || \
                                                               ((TEXT_GET_COL(_CHAR_) >= 0xD2) && (TEXT_GET_COL(_CHAR_) <= 0xD3)))

#define TEXT_IS_ARABIC_ALPHA_FONTB_TO_CONVERT( _CHAR_ ) (((TEXT_GET_COL(_CHAR_) > TEXT_ARABIC_HAMZA_CHAR) && \
                                                      (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_GHAIN_CHAR)) || \
                                                     ((TEXT_GET_COL(_CHAR_) >= TEXT_ARABIC_FEH_CHAR) && \
                                                                 (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_YEH_CHAR)))

#define TEXT_IS_ARABIC_ALPHA_TO_CONVERT( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                                        (TEXT_IS_ARABIC_ALPHA_FONTB_TO_CONVERT(_CHAR_) || \
                                                         TEXT_IS_ARABIC_ALPHA_FONTA_TO_CONVERT(_CHAR_)))

#define TEXT_IS_ARABIC_ALPHA_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_FORM_B_ROW) || \
                                              ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                               ((TEXT_GET_COL(_CHAR_) < TEXT_ARABIC_INDIC_DIGIT_ZERO) || \
                                                (TEXT_GET_COL(_CHAR_) > TEXT_ARABIC_INDIC_DIGIT_ASTERISK))))

#define TEXT_IS_ARABIC_DIGIT_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                             (TEXT_GET_COL(_CHAR_) >= TEXT_ARABIC_INDIC_DIGIT_ZERO) && \
                                             (TEXT_GET_COL(_CHAR_) <= TEXT_ARABIC_INDIC_DIGIT_ASTERISK))

#define TEXT_IS_ARABIC_COMPOSED_CHAR( _CHAR_ ) ( (TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                                      (((TEXT_GET_COL(_CHAR_) >= 0x10) && (TEXT_GET_COL(_CHAR_) <= 0x1A)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0x4B) && (TEXT_GET_COL(_CHAR_) <= 0x5E)) || \
                                                       (TEXT_GET_COL(_CHAR_) == 0x70) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xD6) && (TEXT_GET_COL(_CHAR_) <= 0xDC)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xDF) && (TEXT_GET_COL(_CHAR_) <= 0xE4)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xE7) && (TEXT_GET_COL(_CHAR_) <= 0xE8)) || \
                                                       ((TEXT_GET_COL(_CHAR_) >= 0xEA) && (TEXT_GET_COL(_CHAR_) <= 0xED))) )

#define TEXT_IS_ISOLATED_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && (TEXT_GET_COL(_CHAR_) == 0x77))
#define TEXT_IS_JOIN_CAUSING_CHAR( _CHAR_ ) (((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && (TEXT_GET_COL(_CHAR_) == 0x40)) || _CHAR_ == 0x200D)
#define TEXT_IS_NON_JOINING_CHAR( _CHAR_ ) ((TEXT_GET_ROW(_CHAR_) == TEXT_ARABIC_ROW) && \
                                             ((TEXT_GET_COL(_CHAR_) == 0x21) || \
                                              (TEXT_GET_COL(_CHAR_) == 0x74) || \
                                              (TEXT_GET_COL(_CHAR_) == 0xDD)) || \
                                              _CHAR_ == 0x200C)

#define TEXT_IS_CONCATENATION( _CHAR_, _NEXT_CHAR_ ) ((_CHAR_ == 0x0644) && ((_NEXT_CHAR_ == 0x0622) || \
                                                                              (_NEXT_CHAR_ == 0x0623) || \
                                                                              (_NEXT_CHAR_ == 0x0625) || \
                                                                              (_NEXT_CHAR_ == 0x0627)))


/* 4 possible positions in an arabic word: PL, PF, PI, PM */
#define TEXT_ARABIC_PL_POSITION 0 /* Isolated form */
#define TEXT_ARABIC_PF_POSITION 1 /* Final form */
#define TEXT_ARABIC_PI_POSITION 2 /* Initial form */
#define TEXT_ARABIC_PM_POSITION 3 /* medial form */

typedef struct
{
   u8 nPlChar;       /* correspondind COL value in row FE for PL position */
   boolean bForceEnd;     /* Indicates if the char force word end */
} Text_ArabicConvertTable_t;

typedef struct
{
   u8 nChar;
   u8 nPlPosition;
} Text_FEArabicConvertTable_t;

#define TEXT_ARABIC_FORCE_END(_COL_)  _tTextArabicConvertTable[_COL_-(TEXT_ARABIC_HAMZA_CHAR+1)].bForceEnd
#define TEXT_ARABIC_CONVERT2PL(_COL_) _tTextArabicConvertTable[_COL_-(TEXT_ARABIC_HAMZA_CHAR+1)].nPlChar

#define TEXT_ARABIC_FONTA_FORCE_END(_COL_)  _tTextArabicConvertFontATable[_COL_-(TEXT_ARABIC_WASLA_CHAR)].bForceEnd
#define TEXT_ARABIC_FONTA_CONVERT2PL(_COL_) _tTextArabicConvertFontATable[_COL_-(TEXT_ARABIC_WASLA_CHAR)].nPlChar
#define TEXT_FEARABIC_CONVERT2PL(_COL_) _tTextFEArabicConvertTable[_COL_-TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL].nChar
#define TEXT_FEARABIC_PL(_COL_) _tTextFEArabicConvertTable[_COL_-TEXT_ARABIC_ALEF_MADDA_ABOVE_CHAR_PL].nPlPosition

#define TEXT_FBARABIC_FONTA_CONVERT2PL(_COL_) _tTextFBArabicConvertFontATable[_COL_-TEXT_ARABIC_ALFB_WASLA_CHAR_PL].nChar
#define TEXT_FBARABIC_FONTA_PL(_COL_) _tTextFBArabicConvertFontATable[_COL_-TEXT_ARABIC_ALFB_WASLA_CHAR_PL].nPlPosition

static u32 _TextArabicConvertToDisplay( MAE_WChar *pString, u32 nStrLen );
static boolean _TextArabicConvertFEFormat( MAE_WChar *pString, u32 nStrLen );
static boolean _TextArabicConvertFEChar( MAE_WChar *pwChar, MAE_WChar *pPreChar, boolean *pInWord, boolean *pPreCharIsFirst );
static u32 _TextArabicEFConcatenation( MAE_WChar *pEFString, u32 nStrLen );
static boolean _TextArabicFEConcatenationNextChar( MAE_WChar *pEFChar, MAE_WChar nEFNextChar );
static boolean _TextArabicConvertLastCodeType( const u16 nChar, u16 *pLastCodeType );

#endif //__MAE_TEXT_ARABIC_PRIV_H__

#endif //__BIDI_TEXT__
