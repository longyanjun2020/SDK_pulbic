/*****************************************************************************\
This software is protected by Copyright and the information
contained herein is confidential. Distribution, reproduction
as well as exploitation and transmission of its contents is
not allowed except if expressly permitted. Infringments
result in damage claims.
Copyright : Morning Star 2006/11 ~ 2010

File    : msgdidef.h

Contents: Basic structures and constants here

Historical :
--------------------------------------------------------------------------
Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
29.12.06 | Alex   |      |  Create, seperated from DispBasicGraph.h
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#ifndef _MSTAR_GRAPHIC_BASIC_DEFINITION_H_
#define _MSTAR_GRAPHIC_BASIC_DEFINITION_H_

#include "vm_types.ht"

#ifdef __G3D_DRV__
#ifndef __SDK_SIMULATION__
//#define _USE_G2D_PERF_
#endif
#endif

#ifndef __VER_DMA2D__
//#define ENABLE_DMA2D_FPGA_VERIFY
#endif

#ifdef _USE_G2D_PERF_
#include "g3d.h"
#include "g2d.h"
#endif

//Control flags
//#define _ENABLE_BACKLIGHT_IN_GDI_   1
//===============================================
//    Constant
//===============================================
#ifdef _USE_G2D_PERF_
#define MIN_G3D_BLT_WIDTH 24
#define MIN_G3D_BLT_HEIGHT 24
#define MAX_G3D_BLT_WIDTH 512
#define MAX_G3D_BLT_HEIGHT 512
extern bool _g3dInitDone;
extern bool _g3dNeedWait;
#endif

#define MSGDI_MAX_DISPLAY_LAYER         4

#define MAIN_PANEL                      0
#define SUB_PANEL                       1

#define RGB332_R_MASK                   0xE0
#define RGB332_G_MASK                   0x1C
#define RGB332_B_MASK                   0x03

#define RGB565_R_MASK                   0xF800
#define RGB565_G_MASK                   0x07E0
#define RGB565_B_MASK                   0x001F

#define RGB4444_A_MASK                  0xF000
#define RGB4444_R_MASK                  0x0F00
#define RGB4444_G_MASK                  0x00F0
#define RGB4444_B_MASK                  0x000F

#define RGB888_R_MASK                   0xFF000000
#define RGB888_G_MASK                   0x00FF0000
#define RGB888_B_MASK                   0x0000FF00

#define RGB8888_A_MASK                  0xFF000000
#define RGB8888_R_MASK                  0x00FF0000
#define RGB8888_G_MASK                  0x0000FF00
#define RGB8888_B_MASK                  0x000000FF

#define MSSURFACE_SYSTEM_MEMORY           0x00000100
#define MSSURFACE_VIDEO_MEMORY_INT        0x00000200  //internal memory, for Montage, it means the internal 128K
#define MSSURFACE_VIDEO_MEMORY_EXT        0x00000400  //External, in general, it means memory embedded with panel.
#define MSSURFACE_VIRTUAL_MEMORY          0x00000800  //Prepare for Montage, because Montage doesnot need memory exactly.
#define MSSURFACE_GLASSBOARD              0x00001000
#define MSSURFACE_COLORKEY                0x00002000
//#define MSSURFACE_SHARE_DISPLAY_MEM       0x00004000
#define MSSURFACE_DISP_MEMORY             0x00008000

#define MSSURFACE_ALPHA                   0x00010000

#ifdef __DUAL_LCD__
#define MSSURFACE_LOCATION              ( MSSURFACE_SYSTEM_MEMORY| MSSURFACE_VIDEO_MEMORY_INT | MSSURFACE_VIDEO_MEMORY_EXT | MSSURFACE_VIRTUAL_MEMORY | MSSURFACE_DISP_MEMORY)
#else
#define MSSURFACE_LOCATION              ( MSSURFACE_SYSTEM_MEMORY| MSSURFACE_VIDEO_MEMORY_INT | MSSURFACE_VIDEO_MEMORY_EXT | MSSURFACE_VIRTUAL_MEMORY | MSSURFACE_DISP_MEMORY)
#endif

#define MSSURFACE_ANYLOCATION           ( MSSURFACE_SYSTEM_MEMORY| MSSURFACE_VIDEO_MEMORY_EXT )

typedef enum{
	MSCOLORFORMAT_RGB8_332 = 0,
	MSCOLORFORMAT_RGB16_565,
	MSCOLORFORMAT_RGB24_888,
	MSCOLORFORMAT_RGB24_8565,//ARGB
	MSCOLORFORMAT_IDX8_PALETTE8888,
	MSCOLORFORMAT_IDX8_PALETTE565,

	MAX_AVAILABLE_SURFACE_FORMAT_ID,

	MSCOLORFORMAT_CONST,//only have one RGB24 value, use for FillRect + Alpha blending
	MSCOLORFORMAT_MONO1,
	MSCOLORFORMAT_MONO2,
	MSCOLORFORMAT_MONO4,
	MSCOLORFORMAT_MONO8,
	MSCOLORFORMAT_PALETTE1,
	MSCOLORFORMAT_PALETTE2,
	MSCOLORFORMAT_PALETTE4,
	MSCOLORFORMAT_PALETTE8,

	//MSCOLORFORMAT_RGB8_332,
	//MSCOLORFORMAT_RGB16_565,
	MSCOLORFORMAT_RGB16_1555,
	MSCOLORFORMAT_RGB16_4444,
	//MSCOLORFORMAT_RGB24_888,
	MSCOLORFORMAT_RGB32_8888,       //ARGB

	MSCOLORFORMAT_BMP_MONO,         //0x324D // 'M2'
	MSCOLORFORMAT_BMP_GRAY,         //0x3247 // 'G2'
	MSCOLORFORMAT_BMP_COLOR_DIRECT, //0x3543 // 'C5'
	MSCOLORFORMAT_BMP_COLOR_PALETTE,//0x3443 // 'C4'
	MSCOLORFORMAT_BMP_COLOR_LZSS,   //0x3643 // 'C6'

	MSCOLORFORMAT_EMU_RENDER  /*Jack add for emu render format*/
}MSCOLOR_FORMAT;


#define COLOR_FORMAT_MASK   0xFF // upto 255 corlor formats

typedef enum{
	MSDISPLAY_ERR_NOT_ENOUGH_MEMORY = (s32)-5,
	MSDISPLAY_ERR_BAD_PARAM,
	MSDISPLAY_ERR_COLORFORMAT_MISMATCH,
	MSDISPLAY_ERR_WRONG_COLORFORMAT,
	MSDISPLAY_ERR_COLORFORMAT_NOT_SUPPORT,
	MSDISPLAY_ERROR,
	MSDISPLAY_SUCCESS,
}MSDISPLAY_RETVAL;


//===============================================
//    Contrast
//===============================================
#define MSGDI_GET_POWERSTATE_MAX        0x0001
#define MSGDI_GET_POWERSTATE_MIN        0x0002
#define MSGDI_GET_POWERSTATE_DEFAULT    0x0004
#define MSGDI_GET_POWERSTATE_ACTIVE     0x0008

#define MSGDI_GET_CONTRAST_MAX          0x0010
#define MSGDI_GET_CONTRAST_MIN          0x0020
#define MSGDI_GET_CONTRAST_DEFAULT      0x0040
#define MSGDI_GET_CONTRAST_ACTIVE       0x0080

#define MSGDI_GET_BACKLIGHT_MAX         0x0100
#define MSGDI_GET_BACKLIGHT_MIN         0x0200
#define MSGDI_GET_BACKLIGHT_DEFAULT     0x0400
#define MSGDI_GET_BACKLIGHT_ACTIVE      0x0800

typedef enum
{
	CONTRAST_LEVEL_0 = 0,
	CONTRAST_LEVEL_1,
	CONTRAST_LEVEL_2,
	CONTRAST_LEVEL_3,
	CONTRAST_LEVEL_4,
	CONTRAST_LEVEL_5,
	CONTRAST_LEVEL_6
}MSGDICONTRASTLEVEL,*PMSGDICONTRASTLEVEL;
typedef enum
{
	POWER_LEVEL_0 = 0,
	POWER_LEVEL_1,
	POWER_LEVEL_2,
	POWER_LEVEL_3,
	POWER_LEVEL_4,
	POWER_LEVEL_5,
	POWER_LEVEL_6
}MSGDIPOWERLEVEL,*PMSGDIPOWERLEVEL;
#define POWER_MAIN_PANEL_OFF    POWER_LEVEL_0
#define POWER_MAIN_PANEL_ON     POWER_LEVEL_6

#if 0
#if _ENABLE_BACKLIGHT_IN_GDI_
typedef enum
{
	BACKLIGHT_LEVEL_0 = 0,
	BACKLIGHT_LEVEL_1,
	BACKLIGHT_LEVEL_2,
	BACKLIGHT_LEVEL_3,
	BACKLIGHT_LEVEL_4,
	BACKLIGHT_LEVEL_5,
	BACKLIGHT_LEVEL_6,
}MSGDIBACKLIGHTLEVEL,*PMSGDIBACKLIGHTLEVEL;
#define BACKLIGHT_LEVEL_OFF BACKLIGHT_LEVEL_0
#define BACKLIGHT_LEVEL_ON  BACKLIGHT_LEVEL_6
#endif//_ENABLE_BACKLIGHT_IN_GDI_
#endif
//===============================================
// Rotated angle
typedef enum {
	GDI_ROTATION_0 = 0,   //no rotation (captured image stored "as is")
	GDI_ROTATION_90,      //input image is rotated by +90?while stored in RAM
	GDI_ROTATION_270,     //input image is rotated by -90?(= +270? while stored in RAM
	GDI_ROTATION_180      // input image is rotated by +180?while stored in RAM
} MSROTATEDANGLE;

typedef enum {
	GDI_LAYER_VIDEO_TYPE = 0,   //no rotation (captured image stored "as is")
	GDI_LAYER_GRAPHIC_0_TYPE,      //input image is rotated by +90?while stored in RAM
	GDI_LAYER_GRAPHIC_1_TYPE,      //input image is rotated by +90?while stored in RAM
	GDI_LAYER_G3D_TYPE,     //input image is rotated by -90?(= +270? while stored in RAM
	GDI_LAYER_MAX      // input image is rotated by +180?while stored in RAM
} MSLAYERTYPE;

typedef enum {
	GDI_ALPHA_GLOBAL = 0,   //GLOBAL ALPHA
	GDI_ALPHA_PIXEL,        //PERPIXEL ALPHA
	GDI_ALPHA_MAX           //MAX ALPHA TYPE
} MSALPHATYPE;

typedef enum {
	GDI_ACTIVE_UPDATE = 0,     //updat the screen
	GDI_ACTIVE_NO_UPDATE,      //no update the screen
} MSACTIVEMODE;

typedef enum
{
	GSS_BITBLT_FLAG_NONE = 0,
	GSS_BITBLT_FLAG_OVERWRITE_DST_ALPHA = (1<<0),
	GSS_BITBLT_FLAG_MIRROR = (1<<1)
}MSBITBLTFLAG;

typedef enum
{
    MSUPDATE_NORMAL = 0,
    MSUPDATE_BUFFERLESS,
}MSUpdateType_e;

//===============================================
//    Structures
//===============================================
typedef struct tagMSRGBQUAD {
        u8    rgbBlue;
        u8    rgbGreen;
        u8    rgbRed;
        u8    alpha;
} MSRGBQUAD;

typedef struct _st_ms_point_{
	s32         x;
	s32         y;
}MSPOINT, *PMSPOINT;

typedef struct _st_ms_rectangle_{
	u16         left;
	u16         top;
	u16         right;
	u16         bottom;
}MSRECT, *PMSRECT;

typedef struct _st_ms_region_{
	s32     x;
	s32     y;
	s32     width;
	s32     height;
}MSREGION, *PMSREGION;

typedef struct _st_attribution_
{
	u32     PanelIndex;
	u32     attr;
	void*   pData;
}ATTRIBUTION, *PATTRIBUTION;

typedef struct _st_surface_{
	u32         caps;
	u16         width;
	u16         height;
	u32         bpp;
	u32         stride;
	u32         size; // in bytes
	u32         format;
	u32         addr;
	u8*         pAlphaMask;//store 8 bits aplette when format==MSCOLORFORMAT_IDX8_PALETTE8888
	u8*         pExtraData;
	u32         nPreAlphaFormat;  // the raw data is premultiplied alpha format or not
	u8          rbFieldInverse; // 0 : rgb, 1 : bgr
	u8          alphaBitsUsed;//0 : 8bits, 1 : 4bits
	u8			nGlobalAlhpa;//0~255,for dib format without alpha channel, use global alpha value instead.
	u8          reserve;
}MSSURFACE, *PMSSURFACE;

typedef struct _st_palette_surface_{
	MSSURFACE   header;
	u16         colors;
	u16         BytesPerColor;
	u32         addr;
}MSPALSURFACE, *PMSPALSURFACE;

//=====================================Point
typedef struct _dev_gdi_drawpoint_{
	PMSSURFACE  pSurf;
	MSPOINT     pos;
	u32         color;
}MSGDI_DRAWPOINT, *PMSGDI_DRAWPOINT;

typedef struct _dev_gdi_drawpixel_{
	PMSSURFACE  pSurf;
	u32         x;
	u32         y;
	u32         color;
	u32         rop;
}MSGDI_DRAWPIXEL, *PMSGDI_DRAWPIXEL;

typedef struct _dev_gdi_drawpixels_{
	PMSSURFACE  pSurf;
	u32         cnt;
	MSPOINT     *pixel;
	u32         color;
	u32         rop;
	MSREGION    inval;
}MSGDI_DRAWPIXELS, *PMSGDI_DRAWPIXELS;

//=====================================Line
typedef struct _st_paint_line_solid_
{
	PMSSURFACE  pSurf;
	u32         color;
	MSPOINT     start;
	MSPOINT     end;
} MSSOLIDLINE, *PMSSOLIDLINE;

typedef struct _st_paint_line_pattern_
{
	PMSSURFACE  pSurf;
	PMSSURFACE  pPattern;
	u32         color;
	MSPOINT     start;
	MSPOINT     end;
} MSPATTERNLINE, *PMSPATTERNLINE;

typedef struct _st_draw_line_
{
	PMSSURFACE  pSurf;
	u32         color;
	u32         x;
	u32         y;
	u32         len;
	u32         rop;
} MSDRAWLINE, *PMSDRAWLINE;
//=====================================Surface

typedef struct _st_picture_info_{
	u16     width;
	u16     height;
	u32     format;
	u32     caps;
}MSPICINFO, *PMSPICINFO;

typedef struct _st_disp_setting_{
	bool   isFire;
}MSDISPSET, *PMSDISPSET;

typedef struct _st_colorKey_info_{
	MSCOLOR_FORMAT     format;
	u32                color;
}MSCOLORKEY, *PMSCOLORKEY;

typedef struct _st_layer_config_{
	u8             transLevel;/*0~255*/
	u8             sckEnable;  /*1: enable, 0: disable*/
	MSALPHATYPE    alphaType;
	MSLAYERTYPE    type;
	MSACTIVEMODE   activeMode;
	MSREGION       window;
}MSLAYERCONFIG;

typedef struct _dev_blt_srccopy_{
	PMSSURFACE  pSrcSurf;
	PMSSURFACE  pDstSurf;
	MSREGION    AreaSrc;
	MSREGION    AreaDst;
    //bool    bUpdateQuick;
}MSBLT_SRCCOPY, *PMSBLT_SRCCOPY;

typedef struct _dev_blt_bitblt_{
	PMSSURFACE  pSrcSurf;
	PMSSURFACE  pDstSurf;
	MSREGION    AreaSrc;
	MSREGION    AreaDst;
	u8          Type;//should be removed, --->call mspGraphDev->Bitblt.RotateCopy instead
	u8          Trans;
	u8          Rop;
	u8          cntPalSrc;
	u32         Val1;           //pBmpSrc->clrTrans or pBmpSrc->ConstAlpha
	u32         *pPalSrc;
	MSBITBLTFLAG Flag;
}MSBLT_BITBLT, *PMSBLT_BITBLT;

typedef struct _dev_blt_perspectiveblt_{
	PMSSURFACE  pSrcSurf;
	PMSSURFACE  pDstSurf;
	MSREGION    AreaSrc;
	MSREGION    AreaDst;
	u8          Type;
	u8          Trans;
	u8          Rop;
	u8          cntPalSrc;
	u32         Val1;           //pBmpSrc->clrTrans or pBmpSrc->ConstAlpha
	u32         *pPalSrc;
	u16          nDir;
}MSBLT_PERSPECTIVEBLT, *PMSBLT_PERSPECTIVEBLT;

typedef void (*PfnUpdateQuickFinishNotify)(void);
typedef struct _update_quick_{
    bool    bUpdateQuick;
    PfnUpdateQuickFinishNotify pQuickNotify;
}MSUPDATEQUICK, *PMSUPDATEQUICK;


typedef struct _dev_update_layer_{
	PMSSURFACE  pSrcSurf;
	MSREGION    AreaSrc;
    MSREGION    DirectArea;
    MSUPDATEQUICK tUpdateQuickEnable;
    MSUpdateType_e UpdateType;
}MSUPDATELAYER, *PMSUPDATELAYER;

typedef struct _dev_update_{
	PMSSURFACE    pUpdateSurf[MSGDI_MAX_DISPLAY_LAYER];
	MSLAYERCONFIG LayerConfig[MSGDI_MAX_DISPLAY_LAYER];
	MSREGION      UpdateRegion;
	MSCOLORKEY    colorKey;
	MSDISPSET     dispSetting;
    MSUPDATEQUICK tUpdateQuickEnable;
}MSUPDATE, *PMSUPDATE;

typedef struct _dev_flip_{
	PMSSURFACE    pUpdateSurf[MSGDI_MAX_DISPLAY_LAYER];
	MSLAYERTYPE   layerType[MSGDI_MAX_DISPLAY_LAYER];
	MSREGION      UpdateRegion;
}MSFLIP, *PMSFLIP;

typedef struct _st_update_screen_{
	PMSSURFACE  pSurfFore;
	PMSSURFACE  pSufBack;
	MSREGION    AreaDst;
}MSBLT_UPDATESCR, *PMSBLT_UPDATESCR;

typedef struct _st_fillrect_solid_{
	PMSSURFACE  pDstSurf;
	MSREGION    AreaDst;
	u32         color;
	u32         Rop;
	u32         Flag;
}MSBLT_FILLSOLID, *PMSBLT_FILLSOLID;

typedef struct _st_fill_pattern_{
	PMSSURFACE  pDstSurf;
	PMSSURFACE  pPattern;
	MSREGION    AreaDst;
	u32         color;
}MSBLT_FILLPATT, *PMSBLT_FILLPATT;

typedef struct _st_invert_detsination_{
	PMSSURFACE  pDstSurf;
	MSREGION    AreaDst;
}MSBLT_DSTINVERT, *PMSBLT_DSTINVERT;

typedef struct _dev_blt_mask_fill_{
	PMSSURFACE  pDstSurf;
	MSREGION    AreaDst;
	PMSSURFACE  pPattern;
	u32         color;
}MSBLT_MASKFILL, *PMSBLT_MASKFILL;

typedef struct _dev_blt_colorkey_{
	PMSSURFACE  pSrcSurf;
	PMSSURFACE  pDstSurf;
	MSREGION    AreaSrc;
	MSREGION    AreaDst;
	u32         colorkey;
}MSBLT_COLORKEY, *PMSBLT_COLORKEY;

typedef struct _dev_blt_pattern_paint__{
	PMSSURFACE  pDstSurf;
	PMSSURFACE  pPattern;
	PMSREGION   pDstRegion;
	PMSREGION   pPatRegion;
	u32         ForeColor;
	u32         BackColor;
} MSBLT_PATTPAINT, *PMSBLT_PATTPAINT;

typedef struct _dev_blt_pattern_copy__{
	PMSSURFACE  pDstSurf;
	PMSSURFACE  pPattern;
	PMSREGION   pDstRegion;
	PMSREGION   pPatRegion;
} MSBLT_PATTCOPY, *PMSBLT_PATTCOPY;


typedef struct _dev_blt_bitblt_alpha_mask{
	PMSSURFACE  pDstSurf;
	MSREGION    AreaSrc;
	MSREGION    AreaDst;
	u8			*pAlphaMask;
	u16			pitch;
	u32			ClrFG;
}MSBLT_BITBLT_ALPHA, *PMSBLT_BITBLT_ALPHA;

/*
typedef struct _st_bitblit_info_
{
    PMSSURFACE  pSrcSurf;
    PMSSURFACE  pDstSurf;
    PMSSURFACE  pPattern;
    MSREGION    AreaSrc;
    MSREGION    AreaDst;
    u32         rop;
}BITBLTINFO, *PBITBLTINFO;
*/
//===============================================
//    macro
//===============================================
#define SURFACE_ADDR(pFinalAddr, pSurf, left, top) {\
    u8* pByte = (u8*)(pSurf->addr);\
    pByte = pByte + (top) * (pSurf->stride + ((left*pSurf->bpp) >>3));\
    pFinalAddr = (void*)pByte;\
}
/*
  b1 == 0x47 && b2 == 0x49 Gif();
  b1 == 0x89 && b2 == 0x50 Png();
  b1 == 0xff && b2 == 0xd8 Jpeg();
  b1 == 0x42 && b2 == 0x4d Bmp();
  b1 == 0x0a && b2 < 0x06)  Pcx();
  b1 == 0x46 && b2 == 0x4f) Iff();
  b1 == 0x59 && b2 == 0xa6) Ras();
  b1 == 0x50 && b2 >= 0x31 && b2 <= 0x36) Pnm(b2 - '0');
  b1 == 0x38 && b2 == 0x42) Psd()
*/

//===============================================
//    From MAE BITMAP BASE
//===============================================

#define GSS_MakeRect(pDst, _X, _Y, _W, _H) \
        { (pDst)->x = (_X); \
          (pDst)->y = (_Y); \
          (pDst)->width = (_W); \
          (pDst)->height = (_H);}

// X & Y is the center point of the Rect.....
#define GSS_MakeRectEx(pDst, _X, _Y, _W, _H) \
        { (pDst)->x = (_X - (_W/2)); \
          (pDst)->y = (_Y - (_H/2)); \
          (pDst)->width = (_W); \
          (pDst)->height = (_H);}

#define	GSS_RectIntrsect(pDst, pSrc1, pSrc2) \
        { (pDst)->width = (pSrc1)->x+(pSrc1)->width>(pSrc2)->x+(pSrc2)->width ? (pSrc2)->x+(pSrc2)->width:(pSrc1)->x+(pSrc1)->width; \
          (pDst)->height = (pSrc1)->y+(pSrc1)->height>(pSrc2)->y+(pSrc2)->height ? (pSrc2)->y+(pSrc2)->height:(pSrc1)->y+(pSrc1)->height; \
          (pDst)->x = (pSrc1)->x < (pSrc2)->x ? (pSrc2)->x:(pSrc1)->x; \
          (pDst)->y = (pSrc1)->y < (pSrc2)->y ? (pSrc2)->y:(pSrc1)->y; \
          (pDst)->width = (pDst)->width>(pDst)->x? (pDst)->width-(pDst)->x:0; \
          (pDst)->height = (pDst)->height>(pDst)->y? (pDst)->height-(pDst)->y:0;}

#define	GSS_RectUnion(pDst, pSrc1, pSrc2) \
        { if((pSrc1)->width==0 || (pSrc1)->height==0) *(pDst) = *(pSrc2); \
          else if((pSrc2)->width==0 || (pSrc2)->height==0) *(pDst) = *(pSrc1); \
          else \
          { (pDst)->width = (pSrc1)->x+(pSrc1)->width>(pSrc2)->x+(pSrc2)->width ? (pSrc1)->x+(pSrc1)->width:(pSrc2)->x+(pSrc2)->width; \
            (pDst)->height = (pSrc1)->y+(pSrc1)->height>(pSrc2)->y+(pSrc2)->height ? (pSrc1)->y+(pSrc1)->height:(pSrc2)->y+(pSrc2)->height; \
            (pDst)->x = (pSrc1)->x > (pSrc2)->x ? (pSrc2)->x:(pSrc1)->x; \
            (pDst)->y = (pSrc1)->y > (pSrc2)->y ? (pSrc2)->y:(pSrc1)->y; \
            (pDst)->width -= (pDst)->x; \
            (pDst)->height -= (pDst)->y;}}

enum
{
    GSS_TRANS_NONE = 0,  ///< no transparent
    GSS_TRANS_COLOR,     ///< use transparent color
    GSS_TRANS_ALPHA,      ///< use alpha mask
    GSS_TRANSPARENCY,    ///< use alpha value
    GSS_TRANS_TOTAL      ///< total number of transparent type
};

/* Color definitions */
#define GSS_MAKE_RGB(r, g, b)           (0xFF000000 + ((u32)r << 16) + ((u32)g << 8) + (u32)b)
#define GSS_MAKE_RGBA(r, g, b, a)       (((u32)a << 24) + ((u32)r << 16) + ((u32)g << 8) + (u32)b)
#define GSS_IS_COLOR_FULL_TRANSP(clr)   (((clr)&0xFF000000)==0)
#define GSS_IS_COLOR_NONE_TRANSP(clr)   (((clr)&0xFF000000)==0xFF000000)

#define GSS_RGBCOLOR_BLACK     	(0xFF000000)
#define GSS_RGBCOLOR_WHITE     	(0xFFFFFFFF)
#define GSS_RGBCOLOR_RED       	(0xFFFF0000)
#define GSS_RGBCOLOR_GREEN     	(0xFF00FF00)
#define GSS_RGBCOLOR_BLUE      	(0xFF0000FF)
#define GSS_RGBCOLOR_TRANS     	(0x00FF00FF)
#define GSS_RGBCOLOR_GRAY      	(0xFF404040)

#define GSS_RGBCOLOR_OSD_TRANS	(0x00080408)

#define GSS_RED_FROM_RGBCOLOR(c)    ((c>>16)&0xFF)
#define GSS_GREEN_FROM_RGBCOLOR(c)  ((c>>8)&0xFF)
#define GSS_BLUE_FROM_RGBCOLOR(c)   (c&0xFF)
#define GSS_ALPHA_FROM_RGBCOLOR(c)  ((c>>24)&0xFF)

#define GSS_NONE_TRANSP 255

/* Color conversion */
#ifdef COLOR_BIG_ENDIAN

#define GSS_RGB16_MASK_R   0x00F8
#define GSS_RGB16_MASK_GH  0x0007
#define GSS_RGB16_MASK_GL  0xE000
#define GSS_RGB16_MASK_B   0x1F00

#define GSS_RGB16_GET_RED(c)    g_nRGB16_5to8[(c&GSS_RGB16_MASK_R)>>3]
#define GSS_RGB16_GET_GREEN(c)  g_nRGB16_6to8[((c&GSS_RGB16_MASK_GH)<<3)|((c&GSS_RGB16_MASK_GL)>>13)]
#define GSS_RGB16_GET_BLUE(c)   g_nRGB16_5to8[(c&GSS_RGB16_MASK_B)>>8]

#define GSS_RGB_TO_RGB16(b,g,r) (u16)(((u16)GSS_RGB16_8to5(r))|(((u16)GSS_RGB16_8to6(g))<<11)|(((u16)GSS_RGB16_8to6(g))>>5)|(((u16)GSS_RGB16_8to5(b))<<5))
#define GSS_RGBCLR_TO_RGB16(c)  (u16)(((c&GSS_RGB24_TO_16_MASK_R)>>16)|((c&GSS_RGB24_TO_16_MASK_G)>>13)|(((c&GSS_RGB24_TO_16_MASK_G)<<3)&GSS_RGB16_MASK_GL)|((c&GSS_RGB24_TO_16_MASK_B)<<5))
#define GSS_RGB16_TO_RGBCLR(c)  GSS_MAKE_RGB((g_nRGB16_5to8[(c&GSS_RGB16_MASK_R)>>3]),(g_nRGB16_6to8[((c&GSS_RGB16_MASK_GH)>>13)|((c&GSS_RGB16_MASK_GL)<<3)]),(g_nRGB16_5to8[(c&GSS_RGB16_MASK_B)>>8]))

#define GSS_RGB16_To_GBR16(c) (((c & 0xF800) >> 11) | (c & 0x07E0) | ((c & 0x001F) << 11))
#else

#define GSS_RGB16_MASK_R 0xF800
#define GSS_RGB16_MASK_G 0x07E0
#define GSS_RGB16_MASK_B 0x001F

#define GSS_RGB16_GET_RED(c)    g_nRGB16_5to8[(c&GSS_RGB16_MASK_R)>>11]
#define GSS_RGB16_GET_GREEN(c)  g_nRGB16_6to8[(c&GSS_RGB16_MASK_G)>>5]
#define GSS_RGB16_GET_BLUE(c)   g_nRGB16_5to8[c&GSS_RGB16_MASK_B]

#define GSS_RGB_TO_RGB16(b,g,r) (u16)((((u16)GSS_RGB16_8to5(r))<<8)|(((u16)GSS_RGB16_8to6(g))<<3)|(((u16)GSS_RGB16_8to5(b))>>3))
#define GSS_RGBCLR_TO_RGB16(c)  (u16)(((c&GSS_RGB24_TO_16_MASK_R)>>8)|((c&GSS_RGB24_TO_16_MASK_G)>>5)|((c&GSS_RGB24_TO_16_MASK_B)>>3))
#define GSS_RGB16_TO_RGBCLR(c)  GSS_MAKE_RGB((g_nRGB16_5to8[c>>11]),(g_nRGB16_6to8[(c&GSS_RGB16_MASK_G)>>5]),(g_nRGB16_5to8[(c&GSS_RGB16_MASK_B)]))

#define GSS_RGB16_To_GBR16(c) (((c & 0xF800) >> 11) | (c & 0x07E0) | ((c & 0x001F) << 11))
#endif //COLOR_LITTLE_ENDIAN

//RGB16
#define GSS_RGB24_TO_16_MASK_R 0x00F80000
#define GSS_RGB24_TO_16_MASK_G 0x0000FC00
#define GSS_RGB24_TO_16_MASK_B 0x000000F8

#define GSS_RGB16_8to5(c)       ((c)&0xF8)
#define GSS_RGB16_8to6(c)       ((c)&0xFC)

#define GSS_RGB16_5to8(c)       g_nRGB16_5to8[c]
#define GSS_RGB16_6to8(c)       g_nRGB16_6to8[c]

                                           //BW
#define GSS_RGB24_TO_BW_MASK_R 0x00800000
#define GSS_RGB24_TO_BW_MASK_G 0x00008000
#define GSS_RGB24_TO_BW_MASK_B 0x00000080

#define GSS_RGBCLR_TO_BW(c)  (u8)(((c&GSS_RGB24_TO_BW_MASK_R) || (c&GSS_RGB24_TO_BW_MASK_G) || (c&GSS_RGB24_TO_BW_MASK_B))?1:0)
#define GSS_BW_TO_RGBCLR(c)  (c?0xFFFFFF:0)

#define GSS_BLIT_TYPE_NONE          0 //0x00000000
#define GSS_BLIT_TYPE_ROTATE_90CW   1 //0x80000000      // src rotate 90 degree clockwise and blit to dst
#define GSS_BLIT_TYPE_ROTATE_270CW  2 //0x20000000      // src rotate 270 degree clockwise and blit to dst
#define GSS_BLIT_TYPE_ROTATE_180CW  3 //0x20000000      // src rotate 180 degree clockwise and blit to dst
#define GSS_BLIT_TYPE_BW_MASK       4 //0x40000000      // for BW mask use only, draw 1 to dst bit if


#define SWAP(A,B) do{(A)^=(B);(B)^=(A);(A)^=(B);}while(0)

/*
	Convert coordinate of the given rect. 90 degree counter-clockwise.
 */
#define GSS_RcCvrt90CCW(_pRc,_W,_H) do{SWAP((_pRc)->x,(_pRc)->y); \
	                               (_pRc)->y=(_W)-(_pRc)->y-(_pRc)->width; \
	                               SWAP((_pRc)->width,(_pRc)->height);}while(0)
/*
	Convert coordinate of the given rect. 90 degree clockwise.
 */
#define GSS_RcCvrt90CW(_pRc,_W,_H) do{SWAP((_pRc)->x,(_pRc)->y); \
	                              (_pRc)->x=(_H)-(_pRc)->x-(_pRc)->height; \
	                              SWAP((_pRc)->width,(_pRc)->height);}while(0)
/*
	Convert coordinate of the given rect. 180 degree clockwise.
 */
#define GSS_RcCvrt180(_pRc,_W,_H) do{(_pRc)->x=(_W)-(_pRc)->x-(_pRc)->width; \
	                             (_pRc)->y=(_H)-(_pRc)->y-(_pRc)->height;}while(0)

/*
	Convert coordinate of the given point. 90 degree counter-clockwise.
 */
#define GSS_PntCvrt90CCW(_x,_y,_W,_H) do{SWAP((_x),(_y)); \
                                     (_y) = (_W)-1-(_y);}while(0)
/*
	Convert coordinate of the given point. 90 degree clockwise.
 */
#define GSS_PntCvrt90CW(_x,_y,_W,_H) do{SWAP((_x),(_y)); \
                                    (_x) = (_H)-1-(_x);}while(0)
/*
	Convert coordinate of the given point. 180 degree clockwise.
 */
#define GSS_PntCvrt180(_x,_y,_W,_H) do{(_x) = (_W)-1-(_x); \
                                   (_y) = (_H)-1-(_y);}while(0)

/*=============================================================*/
// types and definitions
/*=============================================================*/

/* enum for RasterOp_t */
enum
{
	GSS_ROP_COPYSRC = 0, // DST = SRC
//	ROP_ANDNOTSRC,   // DST = DST & (!SRC)
	GSS_ROP_ANDSRC,      // DST = DST & SRC
//	ROP_ANDSRCNOT,   // DST = (!DST) & SRC
//	ROP_MERGENOTSRC, // DST = DST | (!SRC)
	GSS_ROP_MERGESRC,    // DST = DST | SRC
//	ROP_MERGESRCNOT, // DST = (!DST) | SRC
	GSS_ROP_NOT,         // DST = !DST
//	ROP_NOTCOPYSRC,  // DST = !SRC
//	ROP_NOTANDSRC,   // DST = !(DST & SRC)
//	ROP_NOTMERGESRC, // DST = !(DST | SRC)
//	ROP_NOTXORSRC,   // DST = !(DST ^ STC)
//	ROP_XORSRC,      // DST = DST ^ SRC
	GSS_ROP_TOTAL
};  //use RasterOp_t instead of this

/* enum for FadeoutLevel_t */
enum
{
	GSS_FADEOUT_LEVEL_START = 0,
	GSS_FADEOUT_LEVEL_0 = GSS_FADEOUT_LEVEL_START,  ///< full transparent
	GSS_FADEOUT_LEVEL_1,      ///< 1/8 luminance
	GSS_FADEOUT_LEVEL_2,      ///< 2/8 luminance
	GSS_FADEOUT_LEVEL_3,      ///< 3/8 luminance
	GSS_FADEOUT_LEVEL_4,      ///< 4/8 luminance
	GSS_FADEOUT_LEVEL_5,      ///< 5/8 luminance
	GSS_FADEOUT_LEVEL_6,      ///< 6/8 luminance
	GSS_FADEOUT_LEVEL_7,      ///< 7/8 luminance
	GSS_FADEOUT_LEVEL_8,      ///< full opaque
	GSS_FADEOUT_LEVEL_END
};

typedef u32 GSS_RGBColor_t;

extern const u8 g_nBitMask[];
extern const u8 g_nRGB16_5to8[];
extern const u8 g_nRGB16_6to8[];
extern const u8 g_nAlpha8[];

#ifdef _USE_G2D_PERF_
extern G2D_ROP _G2D_GetG2dRop(u32 rop);
extern s32 _G2D_GetG2dColorFormat(u32 ColorScheme, G2D_FORMAT *g2dfromat);
extern void _G2D_GetG2dRect(const PMSREGION tRc, G2D_RECT *g2dRect);
extern U32 _G2D_ColorFromRgb(u8 red, u8 green, u8 blue);
#endif

enum
{
	GSS_TRANDIR_UP,
	GSS_TRANDIR_DOWN,
	GSS_TRANDIR_LEFT,
	GSS_TRANDIR_RIGHT,
	GSS_TRANDIR_IN,
	GSS_TRANDIR_OUT,
	GSS_TRANDIR_TOTAL
};

#endif //_MSTAR_GRAPHIC_BASIC_DEFINITION_H_
