#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_RENDER_H_
#define _IMGCODEC_RENDER_H_

#include "imgcodec_common.h"
#include "imgcodec_color.h"
#include "imgcodec_surfmgr.h"

#define RENDER_MAX_ROW_HEIGHT  32
#define RENDER_MAX_PLANES      3

typedef enum
{
    RENDER_SCL_COLOR_NOOP,
    RENDER_SCL_COLOR_BYPASS,
    RENDER_SCL_COLOR_BY_TABLE
} RenderSclColorMode;

typedef struct Image_Render Image_Render_t;

typedef struct
{
    u32 srcWidth;
    u32 srcHeight;
    u32 maxRowHeight;
    u32 maxIramUsage;
    ImgRegion_t srcROI;
    Image_RotationAngle angle;
    u8 bMirrorX;
    u8 bForceSW;
    u8 bNoSclCloclCtl;
    u8 bInterlace;
    ColorConfigSrc_t srcColor;
    RenderSclColorMode sclColorMode;
} RenderConfig_t;

typedef struct
{
    u8 *buf[RENDER_MAX_PLANES][RENDER_MAX_ROW_HEIGHT];
    u32 height;
    u32 startY;
    u32 numPlane;
} RenderRowBuf_t;

Image_Render_t *render_open(PMSSURFACE dstSurf, RenderConfig_t *pConfig);
s32 render_close(Image_Render_t *pRender);
s32 render_clearDecBuf(Image_Render_t *pRender, u32 x, u32 y, u32 w, u32 h);
s32 render_configColorConv(Image_Render_t *pRender, ColorConfigSrc_t *pSrcColor);
s32 render_configFrame(Image_Render_t *pRender, ImgRegion_t *pSrcFrame);
s32 render_configLine(Image_Render_t *pRender, u32 width, u32 start, u32 inc);
s32 render_getRowBuf(Image_Render_t *pRender, RenderRowBuf_t *pRowBuf);
s32 render_finishFrame(Image_Render_t *pRender);
s32 render_finishRow(Image_Render_t *pRender);
s32 render_feedLine(Image_Render_t *pRender, u8 *lineBuf, u32 lineNum);
#endif
#endif

