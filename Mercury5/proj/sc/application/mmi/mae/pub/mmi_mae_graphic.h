/**
 * @file mmi_mae_graphic.h
 *
 * {Add descriptions here}
 *
 * @version $Id: mmi_mae_graphic.h $
 */
#ifndef __MMI_MAE_GRAPHIC_H__
#define __MMI_MAE_GRAPHIC_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_graphic_forward.h"

/* Color definitions */
#define MAKE_RGB(r, g, b)     (RGBColor_t) ( 0xFF000000 + ((u32)r << 16) + ((u32)g << 8) + (u32)b )
#define MAKE_RGBA(r, g, b, a) (RGBColor_t) ( ((u32)a << 24) + ((u32)r << 16) + ((u32)g << 8) + (u32)b )
#define IS_COLOR_FULL_TRANSP(clr)  (((clr)&0xFF000000)==0)
#define IS_COLOR_NONE_TRANSP(clr)  (((clr)&0xFF000000)==0xFF000000)

#define RGBCOLOR_BLACK     	(0xFF000000)
#define RGBCOLOR_WHITE     	(0xFFFFFFFF)
#define RGBCOLOR_RED       	(0xFFFF0000)
#define RGBCOLOR_GREEN     	(0xFF00FF00)
#define RGBCOLOR_BLUE      	(0xFF0000FF)
#define RGBCOLOR_TRANS     	(0x00FF00FF)
#define RGBCOLOR_GRAY      	(0xFF404040)

#define RGBCOLOR_OSD_TRANS	(0xFF080408)


#define RED_FROM_RGBCOLOR(c)    ((c>>16)&0xFF)
#define GREEN_FROM_RGBCOLOR(c)  ((c>>8)&0xFF)
#define BLUE_FROM_RGBCOLOR(c)   (c&0xFF)
#define ALPHA_FROM_RGBCOLOR(c)  ((c>>24)&0xFF)

/* Color conversion */
//RGB16
#define RGB24_TO_16_MASK_R 0x00F80000
#define RGB24_TO_16_MASK_G 0x0000FC00
#define RGB24_TO_16_MASK_B 0x000000F8

#define RGB16_8to5(c)       ((c)&0xF8)
#define RGB16_8to6(c)       ((c)&0xFC)

#define RGB16_5to8(c)       g_nRGB16_5to8[c];
#define RGB16_6to8(c)       g_nRGB16_6to8[c];

#ifdef COLOR_BIG_ENDIAN

#define RGB16_MASK_R   0x00F8
#define RGB16_MASK_GH  0x0007
#define RGB16_MASK_GL  0xE000
#define RGB16_MASK_B   0x1F00

#define RGB16_GET_RED(c)    g_nRGB16_5to8[(c&RGB16_MASK_R)>>3]
#define RGB16_GET_GREEN(c)  g_nRGB16_6to8[((c&RGB16_MASK_GH)<<3)|((c&RGB16_MASK_GL)>>13)]
#define RGB16_GET_BLUE(c)   g_nRGB16_5to8[(c&RGB16_MASK_B)>>8]

#define RGB_TO_RGB16(r,g,b) (u16)(((u16)RGB16_8to5(r))|(((u16)RGB16_8to6(g))<<11)|(((u16)RGB16_8to6(g))>>5)|(((u16)RGB16_8to5(b))<<5))
#define RGBCLR_TO_RGB16(c)  (u16)(((c&RGB24_TO_16_MASK_R)>>16)|((c&RGB24_TO_16_MASK_G)>>13)|(((c&RGB24_TO_16_MASK_G)<<3)&RGB16_MASK_GL)|((c&RGB24_TO_16_MASK_B)<<5))
#define RGB16_TO_RGBCLR(c)  MAKE_RGB((g_nRGB16_5to8[(c&RGB16_MASK_R)>>3]),(g_nRGB16_6to8[((c&RGB16_MASK_GH)>>13)|((c&RGB16_MASK_GL)<<3)]),(g_nRGB16_5to8[(c&RGB16_MASK_B)>>8]))

#else

#define RGB16_MASK_R 0xF800
#define RGB16_MASK_G 0x07E0
#define RGB16_MASK_B 0x001F

#define RGB16_GET_RED(c)    g_nRGB16_5to8[(c&RGB16_MASK_R)>>11]
#define RGB16_GET_GREEN(c)  g_nRGB16_6to8[(c&RGB16_MASK_G)>>5]
#define RGB16_GET_BLUE(c)   g_nRGB16_5to8[c&RGB16_MASK_B]

#define RGB_TO_RGB16(r,g,b) (u16)((((u16)RGB16_8to5(r))<<8)|(((u16)RGB16_8to6(g))<<3)|(((u16)RGB16_8to5(b))>>3))
#define RGBCLR_TO_RGB16(c)  (u16)(((c&RGB24_TO_16_MASK_R)>>8)|((c&RGB24_TO_16_MASK_G)>>5)|((c&RGB24_TO_16_MASK_B)>>3))
#define RGB16_TO_RGBCLR(c)  MAKE_RGB((g_nRGB16_5to8[c>>11]),(g_nRGB16_6to8[(c&RGB16_MASK_G)>>5]),(g_nRGB16_5to8[(c&RGB16_MASK_B)]))

#endif //COLOR_LITTLE_ENDIAN

//BW
#define RGB24_TO_BW_MASK_R 0x00800000
#define RGB24_TO_BW_MASK_G 0x00008000
#define RGB24_TO_BW_MASK_B 0x00000080

#define RGBCLR_TO_BW(c)  (u8)(((c&RGB24_TO_BW_MASK_R) || (c&RGB24_TO_BW_MASK_G) || (c&RGB24_TO_BW_MASK_B))?1:0)
#define BW_TO_RGBCLR(c)  (c?0xFFFFFF:0)



/*
 * Redefine MakeRect macro to be a function call for reducing code size
 * 
 */
void makeRect(Rect_t *, s32, s32, s32, s32);
#define MakeRect(pDst, _X, _Y, _W, _H)	makeRect((pDst), (_X), (_Y), (_W), (_H));
void makeRectEx(Rect_t *, s32, s32, s32, s32);
#define MakeRectEx(pDst, _X, _Y, _W, _H) makeRectEx((pDst), (_X), (_Y), (_W), (_H));
void rectUnion(Rect_t *, Rect_t *, Rect_t *);
#define RectUnion(pDst, pSrc1, pSrc2) rectUnion((pDst), (pSrc1), (pSrc2)); 
/*
#define MakeRect(pDst, _X, _Y, _W, _H) \
        { (pDst)->x = (_X); \
          (pDst)->y = (_Y); \
          (pDst)->w = (_W); \
          (pDst)->h = (_H);}


// X & Y is the center point of the Rect.....
#define MakeRectEx(pDst, _X, _Y, _W, _H) \
        { (pDst)->x = (_X - (_W/2)); \
          (pDst)->y = (_Y - (_H/2)); \
          (pDst)->w = (_W); \
          (pDst)->h = (_H);}
*/

#define	RectIntrsect(pDst, pSrc1, pSrc2) \
        { (pDst)->w = (pSrc1)->x+(pSrc1)->w>(pSrc2)->x+(pSrc2)->w ? (pSrc2)->x+(pSrc2)->w:(pSrc1)->x+(pSrc1)->w; \
          (pDst)->h = (pSrc1)->y+(pSrc1)->h>(pSrc2)->y+(pSrc2)->h ? (pSrc2)->y+(pSrc2)->h:(pSrc1)->y+(pSrc1)->h; \
          (pDst)->x = (pSrc1)->x < (pSrc2)->x ? (pSrc2)->x:(pSrc1)->x; \
          (pDst)->y = (pSrc1)->y < (pSrc2)->y ? (pSrc2)->y:(pSrc1)->y; \
          (pDst)->w = (pDst)->w>(pDst)->x? (pDst)->w-(pDst)->x:0; \
          (pDst)->h = (pDst)->h>(pDst)->y? (pDst)->h-(pDst)->y:0;}
/*
#define	RectUnion(pDst, pSrc1, pSrc2) \
        { if((pSrc1)->w==0 || (pSrc1)->h==0) *(pDst) = *(pSrc2); \
          else if((pSrc2)->w==0 || (pSrc2)->h==0) *(pDst) = *(pSrc1); \
          else \
          { (pDst)->w = (pSrc1)->x+(pSrc1)->w>(pSrc2)->x+(pSrc2)->w ? (pSrc1)->x+(pSrc1)->w:(pSrc2)->x+(pSrc2)->w; \
            (pDst)->h = (pSrc1)->y+(pSrc1)->h>(pSrc2)->y+(pSrc2)->h ? (pSrc1)->y+(pSrc1)->h:(pSrc2)->y+(pSrc2)->h; \
            (pDst)->x = (pSrc1)->x > (pSrc2)->x ? (pSrc2)->x:(pSrc1)->x; \
            (pDst)->y = (pSrc1)->y > (pSrc2)->y ? (pSrc2)->y:(pSrc1)->y; \
            (pDst)->w -= (pDst)->x; \
            (pDst)->h -= (pDst)->y;}}
*/
#endif /* __MMI_MAE_GRAPHIC_H__ */

