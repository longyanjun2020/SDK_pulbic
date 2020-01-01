/**
 * @file mmi_mae_font_types.h
 *
 * @version $Id: mmi_mae_font_types.h $
 */
#ifndef __MMI_MAE_FONT_TYPES_H__
#define __MMI_MAE_FONT_TYPES_H__
#include "mmi_mae_common_def.h"

//Font id..
enum FontId_t_
{
    FONT_ID = 0,
    FONT_N,
    FONT_B,
};

//Font category..
enum FontCategory_t_
{
    FONT_CAT_START=0,

    FONT_CAT_NORMAL=FONT_CAT_START,
    FONT_CAT_MINI_NORMAL,    // for vector font.
    FONT_CAT_SMALL,          // for vector font.
    FONT_CAT_LARGE,          // deprecated font category
    FONT_CAT_SUPERSMALL,
    FONT_CAT_DATE_SMALL,     
    FONT_CAT_NUM_SUPERLARGE,
    FONT_CAT_NUM_LARGE,
    FONT_CAT_NUM_NORMAL,
    FONT_CAT_NUM_SMALL,
    FONT_CAT_NUM_TIMESMALL,  // deprecated font category
    FONT_CAT_NUM_EXTRASMALL, // NUM SUPPER SMALL
    FONT_CAT_NUM_TIME,       // deprecated font category

    FONT_CAT_BITMAP_TOTAL,
    FONT_CAT_VECTOR = FONT_CAT_BITMAP_TOTAL,
    FONT_CAT_TOTAL,
};

#define FONT_CAT_IME_NORMAL FONT_CAT_NORMAL
#define FONT_CAT_IME_SUPERSMALL FONT_CAT_SUPERSMALL

struct FontInfo_t_
{
	u16 nAscent;   //< Not reliable
	u16 nDescent;  //< Not reliable
	u16 nHeight;   //< Reliable
	u32 nTag;
};



#endif /* __MMI_MAE_FONT_TYPES_H__ */
