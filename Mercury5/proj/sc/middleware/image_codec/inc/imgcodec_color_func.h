#ifndef _IMGCODEC_COLOR_FUNC_H_
#define _IMGCODEC_COLOR_FUNC_H_

#include "imgcodec_color.h"

void color_r8g8b8_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_r8g8b8a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_r8g8b8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_xrgb1555_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_rgb565(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_xrgb1555_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_rgb565_a8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_rgb565_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_r8g8b8a8_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_b8g8r8x8_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette8a8_to_rgb565_a8_dither(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
void color_palette_to_palette8(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
#endif

