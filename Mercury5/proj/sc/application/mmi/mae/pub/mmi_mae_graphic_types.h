/**
 * @file mmi_mae_graphic_types.h
 *
 * {Add descriptions here}
 *
 * @version $Id: mmi_mae_graphic_types.h $
 */
#ifndef __MMI_MAE_GRAPHIC_TYPES_H__
#define __MMI_MAE_GRAPHIC_TYPES_H__
#include "mmi_mae_common_def.h"

struct Pos_t_
{
	s32    x;
	s32    y;
};

struct Rect_t_
{
   s32   x;
   s32   y;
   s32   w;
   s32   h;
};

struct Point_t_
{
	s32    x;
	s32    y;
};

struct Ellipse_t_
{
   s32   xc;
   s32   yc;
   s32   rx;
   s32   ry;
};

// Triangle definition: y1 >= y2 >= y3
struct Triangle_t_
{
   s32   x1;
   s32   y1;
   s32   x2;
   s32   y2;
   s32   x3;
   s32   y3;
};

struct Arc_t_
{
   s32   xc;
   s32   yc;
   s32   rx;
   s32   ry;
   u16   startAngle;
   u16   endAngle;
};

/* enum for Direction */

opaque_enum(Direction_e_)
{
    DIRECTION_LEFT     = 0x00,
    DIRECTION_RIGHT    = 0x01,
    DIRECTION_UP       = 0x02,
    DIRECTION_DOWN     = 0x03,
    DIRECTION_MAX      = 0x04
};

/* enum  for ColorItemId_t */
enum ColorItemId_t_
{
	CLR_TEXT = 0,
	CLR_TEXT_OUTLINE,
	CLR_LINE,
	CLR_RECT,
	CLR_BG,
	CLR_TOTAL
};

/* enum for ColorScheme_t */
enum ColorScheme_t_
{
    CLR_SCHEME_RGB565=0,
    CLR_SCHEME_RGB444,
    CLR_SCHEME_RGB888,
    CLR_SCHEME_RGB8888,
    CLR_SCHEME_BLACK_WHITE,
    CLR_SCHEME_PALETTE4,
    CLR_SCHEME_PALETTE8
};

/* enum for RasterOp_t */
enum RasterOp_t_
{
    ROP_COPYSRC = 0, // DST = SRC
    //	ROP_ANDNOTSRC,   // DST = DST & (!SRC)
    ROP_ANDSRC,      // DST = DST & SRC
    //	ROP_ANDSRCNOT,   // DST = (!DST) & SRC
    //	ROP_MERGENOTSRC, // DST = DST | (!SRC)
    ROP_MERGESRC,    // DST = DST | SRC
    //	ROP_MERGESRCNOT, // DST = (!DST) | SRC
    ROP_NOT,         // DST = !DST
    //	ROP_NOTCOPYSRC,  // DST = !SRC
    //	ROP_NOTANDSRC,   // DST = !(DST & SRC)
    //	ROP_NOTMERGESRC, // DST = !(DST | SRC)
    //	ROP_NOTXORSRC,   // DST = !(DST ^ STC)
    //	ROP_XORSRC,      // DST = DST ^ SRC
    ROP_TOTAL
};  //use RasterOp_t instead of this

/* enum for FadeoutLevel_t */
enum FadeoutLevel_t_
{
    FADEOUT_LEVEL_START = 0,
    FADEOUT_LEVEL_0 = FADEOUT_LEVEL_START,  ///< full transparent
    FADEOUT_LEVEL_1,      ///< 1/8 luminance
    FADEOUT_LEVEL_2,      ///< 2/8 luminance
    FADEOUT_LEVEL_3,      ///< 3/8 luminance
    FADEOUT_LEVEL_4,      ///< 4/8 luminance
    FADEOUT_LEVEL_5,      ///< 5/8 luminance
    FADEOUT_LEVEL_6,      ///< 6/8 luminance
    FADEOUT_LEVEL_7,      ///< 7/8 luminance
    FADEOUT_LEVEL_8,      ///< full opaque
    FADEOUT_LEVEL_END
};

opaque_enum(Mae_FadeoutSourceType_e_)
{
    FADEOUT_SOURCE_SAME_WITH_DESTINATION,
    FADEOUT_SOURCE_DEVICE_BITMAP
};

#endif /* __MMI_MAE_GRAPHIC_TYPES_H__ */

