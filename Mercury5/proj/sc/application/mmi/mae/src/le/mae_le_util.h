#ifndef __MAE_LG_UTIL_H__
#define __MAE_LG_UTIL_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "mae_le_types.h"

#define LE_ARRAY_NUM 1
#define LE_GLYPH_MASK     0x0000FFFF

#define LE_GET_BYTE(_p) (*((u8 *)(_p)))
#define LE_GET_SHORT(_p) ((((u16)(*((u8 *)(_p)))) << 8) | ((u16)(*(((u8 *)(_p)) + 1))))
#define LE_GET_LONG(_p) ((((u32)(*((u8 *)(_p)))) << 24) | (((u32)(*(((u8 *)(_p)) + 1))) << 16) | (((u32)(*(((u8 *)(_p)) + 2))) << 8) | ((u32)(*(((u8 *)(_p)) + 3))))

#define LE_SWAP_SHORT(_v) (((((u16)(_v)) & 0x00FF) << 8) | ((((u16)(_v)) & 0xFF00) >> 8))
#define LE_SWAP_LONG(_v) (((((u32)(_v)) & 0x000000FF) << 24) | ((((u32)(_v)) & 0x0000FF00) << 8) | ((((u16)(_v)) & 0x00FF0000) >> 8) | ((((u16)(_v)) & 0xFF000000) >> 24))

#define LE_GET_GLYPH(_gid) (u16)(_gid & LE_GLYPH_MASK)

#define LE_GET_VERSION      LE_GET_LONG
#define LE_GET_OFFSET       LE_GET_SHORT
#define LE_GET_TAG          LE_GET_LONG
#define LE_GET_GLYPHID      LE_GET_SHORT
#define LE_GET_FEATUREFLAGS LE_GET_LONG
#define LE_GET_CLASSCODE    LE_GET_BYTE
#define LE_GET_STATE        LE_GET_BYTE

typedef struct
{
    s32 s32X;
    s32 s32Y;
} LE_Points_t;

typedef struct
{
    u16 u16UnitsPerEM;
	
    u16 u16XPixelsPerEM;     /* horizontal pixels per EM               */
    u16 u16YPixelsPerEM;     /* vertical pixels per EM                 */

    s32 s32XScaleFactor;     /* scaling values used to convert font    */
    s32 s32YScaleFactor;
} LE_FontInstanceInf_t;

s32 LeFontXPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, s32 s32XPixel );
s32 LeFontYPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, s32 s32YPixel );
s32 LeFontXUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, s32 s32XUnit );
s32 LeFontYUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, s32 s32YUnit );
void LeFontPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, LE_Points_t *pPixel, LE_Points_t *pUnit );
void LeFontUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, LE_Points_t *pUnit, LE_Points_t *pPixel );
void LeFontTransformUnit( LE_FontInstanceInf_t *pFontInstanceInf, s32 s32XUnit, s32 s32YUnit, LE_Points_t *pPixel );
boolean LeFontGetGlyphPoint( u16 u16GlyphId, s32 s32PointNumber, LE_Points_t *pPoint );
boolean LeFontGetGlyphAdvance( u16 u16GlyphId, LE_Points_t *pAdvance );
boolean LeFontIsGlyphRightToLeft( LE_FontInstanceInf_t *pFontInstanceInf, u16 u16GlyphId );
#endif //__FEATURE_VECTOR_FONT__

#endif //__MAE_LG_UTIL_H__
