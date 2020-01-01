#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_COLOR_H_
#define _IMGCODEC_COLOR_H_

#include "imgcodec_common.h"


#define IMGCODEC_DEFAULT_COLORKEY_RGB565   ((u16)(0xFB5F))
#define IMGCODEC_DEFAULT_COLORKEY_RED      ((u8)((IMGCODEC_DEFAULT_COLORKEY_RGB565 >> 8) & 0xF8))
#define IMGCODEC_DEFAULT_COLORKEY_GREEN    ((u8)((IMGCODEC_DEFAULT_COLORKEY_RGB565 >> 3) & 0xFC))
#define IMGCODEC_DEFAULT_COLORKEY_BLUE     ((u8)((IMGCODEC_DEFAULT_COLORKEY_RGB565 << 3) & 0xF8))
#define IMGCODEC_DEFAULT_COLORKEY_ARGB8888 (((u32)0xFF                            << 24 | \
                                             (u32)IMGCODEC_DEFAULT_COLORKEY_RED   << 16 | \
                                             (u32)IMGCODEC_DEFAULT_COLORKEY_GREEN << 8  | \
                                             (u32)IMGCODEC_DEFAULT_COLORKEY_BLUE))

#define ASSIGN_BYTE(dst, byte)   (*((u8  *)(dst)) = (byte))
#define ASSIGN_WORD(dst, word)   (*((u16 *)(dst)) = (word))
#define ASSIGN_DWORD(dst, dword) (*((u32 *)(dst)) = (dword))

#define COPY_BYTE(dst, src)      (*((u8 *)(dst)) = *((u8 *)(src)))
#define COPY_WORD(dst, src)      (*((u16 *)(dst)) = *((u16 *)(src)))
#define COPY_DWORD(dst, src)     (*((u32 *)(dst)) = *((u32 *)(src)))
#define COPY_3_BYTES(dst, src)   ((dst)[0] = (src)[0], (dst)[1] = (src)[1], (dst)[2] = (src)[2])
#define COPY_4_BYTES(dst, src)   ((dst)[0] = (src)[0], (dst)[1] = (src)[1], (dst)[2] = (src)[2], (dst)[3] = (src)[3])

#define GET_WORD(src)            (*(u16 *)(src))
#define GET_DWORD(src)           (*(u32 *)(src))

#define R8_G8_B8_TO_GRXB8838(R, G, B)  ((u32)(G) << 19 | (u32)(R) << 11 | (u32)(B))
#define RGB888_A8_TO_ARGB888(RGB, A)   ((u32)(A) << 24 | (RGB))
#define R8_G8_B8_TO_RGB888(R, G, B)    ((u32)(R) << 16 | (u32)(G) << 8  | (u32)(B))
#define R8_G8_B8_TO_RGB565(R, G, B)    (((u32)(R) & 0xF8) << 8 | ((u32)(G) & 0xFC) << 3 | (u32)(B) >> 3)
#define RGB565_TO_RGB888(RGB)          (((u32)(RGB) & 0xF800) << 8 | ((u32)(RGB) & 0x07E0) << 5 | ((u32)(RGB) & 0x001F) << 3)
#define RGB888_TO_RGB565(RGB)          ((((RGB)  >> 8) & 0xF800) | (((RGB)  >> 5 ) & 0x07E0) | (((RGB)  >> 3 ) & 0x001F))
#define GRXB8838_TO_RGB565(GRXB)       ((((GRXB) >> 3) & 0xF81F) | (((GRXB) >> 16) & 0x07E0))
#define XRGB1555_TO_RGB565(XRGB)       ((((XRGB) << 1) & 0xFFC0) | ((XRGB) & 0x001F))

#define RGB888_DITHER_PREPARE(RGB)     ((RGB) - (((RGB) >> 5) & 0x070707))
#define GRXB8838_DITHER_PREPARE(GRXB)  ((GRXB) - (((GRXB) >> 5) & 0x383807))


typedef enum
{
    COLOR_DST_R8G8B8,
    COLOR_DST_R8G8B8A8,
    COLOR_DST_RGB565,
    COLOR_DST_RGB565_A8,
    COLOR_DST_PALETTE8
} ColorFormatDst;

typedef enum
{
    COLOR_SRC_R8G8B8,
    COLOR_SRC_B8G8R8,
    COLOR_SRC_R8G8B8A8,
    COLOR_SRC_B8G8R8X8,
    COLOR_SRC_XRGB1555,
    COLOR_SRC_PALETTE,
    COLOR_SRC_GRAY,
    COLOR_SRC_GRAY8A8,
    COLOR_SRC_YUV444,
    COLOR_SRC_YUV422I,
    COLOR_SRC_YUV422P,
    COLOR_SRC_YUV420P
} ColorFormatSrc;

typedef struct
{
    ColorFormatDst fmt;
    u8 enableTrans;
    u8 transRGB[3];
} ColorConfigDst_t;

typedef struct
{
    ColorFormatSrc fmt;
    u8 depth;
    u8 enableBlending;
    u8 enableTrans;
    u8 enableDither;
    u8 transGray;
    u8 transRGB[3];
    u8 clutRGBA[256*4];
} ColorConfigSrc_t;

typedef struct Image_ColorConv Image_ColorConv_t;
struct Image_ColorConv
{
    ColorFormatDst dstFmt;
    ColorFormatSrc srcFmt;
    void (*process)(Image_ColorConv_t *, u8 *, u8 *, u32, u8 *);

    u32 *dstOffsetByte;
    u32 *dstOffsetPixel;
    u32 palette[256];
    u32 iWidth;
    u32 iLow;
    u32 iHigh;
    u16 isContinuousPixel;
    u16 srcDepth;
    u16 dstPixelBytes;

    u8  enableBlending;
    u8  enableDither;
    u8  enableSrcTrans;
    u8  enableDstTrans;
    u8  srcTransGray;
    u8  srcTransR;
    u8  srcTransG;
    u8  srcTransB;
    u8  dstTransR;
    u8  dstTransG;
    u8  dstTransB;
};

Image_ColorConv_t *colorConv_open(ColorConfigDst_t *pDstCfg, ColorConfigSrc_t *pSrcCfg);
void colorConv_close(Image_ColorConv_t *pColorConv);
void colorConv_configLine(Image_ColorConv_t *pColorConv, u32 *dstOffsetPixel, u32 width, u32 iLow, u32 iHigh);
void colorConv_processLine(Image_ColorConv_t *pColorConv, u8 *dstLine, u8 *dstLineAlpha, u32 dstLineNum, u8 *srcLine);
int colorConv_isAlphaRequired(ColorConfigSrc_t *pSrcCfg);

void colorConv_initPalette(Image_ColorConv_t *pColorConv, u8 *clutRGBA);
void colorConv_loadFunc(Image_ColorConv_t *pColorConv);
#endif
#endif

