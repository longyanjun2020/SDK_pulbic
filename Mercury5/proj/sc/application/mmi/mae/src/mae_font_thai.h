#ifdef __THAI_FONT__
/**
 * \file    mae_font_thai.h
 * \brief   The document describes the interface of Thai font
 * \author  steve.lee@mstarsemi.com
 * @version $Id: mae_font_thai.h 1756 2009-09-10 14:13:56Z bill.pan $
 */
#ifndef __MAE_FONT_THAI_H__
#define __MAE_FONT_THAI_H__

#define IS_THAI(__Code) ((0x0E01 <= __Code && __Code <= 0x0E5B) || (0xE80D <= __Code && __Code <= 0xE810))
#define MAX_THAI_COMBINE_NUM 4

/* WTT 2.0 classifies characters in TIS-620 into 17 types. */
#define CTRL  0 /* control characters */
#define NON   1 /* non-Thai printable characters */
#define CONS  2 /* Thai consonants */
#define LV    3 /* leading vowels */
#define FV1   4 /* ordinary following vowels */
#define FV2   5 /* dependent following vowel (LAKKHANGYAO) */
#define FV3   6 /* special following vowels (RU, LU) */
#define BV1   7 /* short below vowel (SARA U) */
#define BV2   8 /* long below vowel (SARA UU) */
#define BD    9 /* below diacritic (PHINTHU) */
#define TONE 10 /* tone marks */
#define AD1  11 /* above diacritic 1 (THANTHAKHAT, NIKHAHIT) */
#define AD2  12 /* above diacritic 2 (MAITAIKHU) */
#define AD3  13 /* above diacritic 3 (YAMAKKARN) */
#define AV1  14 /* above vowel 1 (SARA I) */
#define AV2  15 /* above vowel 2 (MAIHAN-AKAT, SARA UE) */
#define AV3  16 /* above vowel 3 (SARA II, SARA UEE) */

u16 _FontThaiGetNextCodes(const u16*, u32, u16*, u32, u32*);
boolean _FontThaiGetNextCodeXOffset(u16 *pu16CurrentRefChar, u16 *pu16CurrentCharRefWidth, u16 u16NextChar, u16 u16NextCharWidth, s16 *ps16XOffset);

#ifdef __FEATURE_VECTOR_FONT__
u16 _FontThaiVectorGetNextCodes(const u16*, u32, u16*, u32, u32*);
#endif //__FEATURE_VECTOR_FONT__

#endif /* __MAE_FONT_THAI_H__ */

#endif //__THAI_FONT__
