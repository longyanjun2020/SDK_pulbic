#ifndef __VEN_GRAPHICS_DEFINE_H__
#define __VEN_GRAPHICS_DEFINE_H__
/**
 *
 * @file    ven_graphics.h
 * @brief   This file defines the graphics interface definition.
 *
 * @author  Code.Lin
 * @version $Id: ven_graphics.h 38996 2009-09-01 02:03:20Z code.lin $
 *
 */

#include "ven_font.h"

enum
{
    VEN_GRAPHICS_RET_SUCCESS        = 0, ///< operation completed successfully
    VEN_GRAPHICS_RET_BAD_PARAM      = 1, ///< invalid input parameters
    VEN_GRAPHICS_RET_FAILED         = 2, ///< WHAT? every code here is failed
    VEN_GRAPHICS_RET_OUT_OF_MEMORY  = 3, ///< memory is not enough to complete the operation
};
typedef u32 ven_graphics_ret_t;

enum
{
    VEN_CLR_TEXT                    = 0, ///< Text color
    VEN_CLR_TEXT_OUTLINE,                ///< Text outline color
    VEN_CLR_PEN,                         ///< Pen color
    VEN_CLR_BRUSH,                        ///< Brush color
    VEN_CLR_BG,                          ///< Background color
    VEN_CLR_TOTAL,
};
typedef u32 ven_ColorItem_t;

enum
{
    VEN_GRA_TRANS_NONE              = 0, ///< No transform
    VEN_GRA_TRANS_MIRROR_ROT180,         ///< Causes the Image to appear reflected about its vertical center and then rotated clockwise by 180 degrees
    VEN_GRA_TRANS_MIRROR,                ///< Causes the Image to appear reflected about its vertical center
    VEN_GRA_TRANS_ROT180,                ///< Causes the Image to appear rotated clockwise by 180 degrees
    VEN_GRA_TRANS_MIRROR_ROT270,         ///< Causes the Image to appear reflected about its vertical center and then rotated clockwise by 270 degrees
    VEN_GRA_TRANS_ROT90,                 ///< Causes the Image to appear rotated clockwise by 90 degrees
    VEN_GRA_TRANS_ROT270,                ///< Causes the Image to appear rotated clockwise by 270 degrees
    VEN_GRA_TRANS_MIRROR_ROT90,          ///< Causes the Image to appear reflected about its vertical center and then rotated clockwise by 90 degrees
};
typedef u32 ven_GraphicsTransform_t;

enum
{
    VEN_GRA_DRAWMODE_COPY           = 0,
    VEN_GRA_DRAWMODE_XOR,
    VEN_GRA_DRAWMODE_OR,
    VEN_GRA_DRAWMODE_AND,
    VEN_GRA_DRAWMODE_CLEAR,
    VEN_GRA_DRAWMODE_SETTO1,
    VEN_GRA_DRAWMODE_EQUIV,
    VEN_GRA_DRAWMODE_NOR,
    VEN_GRA_DRAWMODE_NAND,
    VEN_GRA_DRAWMODE_INVERT,
    VEN_GRA_DRAWMODE_COPYINVERTED,
    VEN_GRA_DRAWMODE_ORINVERTED,
    VEN_GRA_DRAWMODE_ANDINVERTED,
    VEN_GRA_DRAWMODE_ORREVERSE,
    VEN_GRA_DRAWMODE_ANDREVERSE,
    VEN_GRA_DRAWMODE_NOOP,
    VEN_GRA_DRAWMODE_ALPHA_SRC,
    VEN_GRA_DRAWMODE_ALPHA_DST,
    VEN_GRA_DRAWMODE_ALPHA_SRC_OVER,
};
typedef u32 ven_GraphicsDrawMode_t;

enum
{
    VEN_GRA_UPDATE_DEFER = 0,
    VEN_GRA_UPDATE_NORMAL,
    VEN_GRA_UPDATE_FORCE_FULLSCR,
    VEN_GRA_UPDATE_PARTIAL
};
typedef u32 ven_GraphicsUpdateMode_t;

enum
{
    VEN_CLR_SCHEME_RGB565 = 0,
    VEN_CLR_SCHEME_RGB444,
    VEN_CLR_SCHEME_RGB888,
    VEN_CLR_SCHEME_RGB8888,
    VEN_CLR_SCHEME_BLACK_WHITE
};
typedef u32 ven_GraphicsColorScheme_t;

enum
{
    VEN_GRAPHICS_TRANS_NONE = 0,  ///< no transparent
    VEN_GRAPHICS_TRANS_COLOR,     ///< use transparent color
    VEN_GRAPHICS_TRANS_ALPHA,      ///< use alpha mask
    VEN_GRAPHICS_TRANSPARENCY,    ///< use alpha value
    VEN_GRAPHICS_TRANS_TOTAL      ///< total number of transparent type
};
typedef u32 ven_GraphicsTransType_t;

enum 
{
    VEN_GRAPHICS_DEFAULT_DISPMODE = 0,
    VEN_GRAPHICS_DISPMODE_PORTRAIT = 0,
	VEN_GRAPHICS_DISPMODE_LANDSCAPE_90, ///< handset rotate 90 degree CCW
	VEN_GRAPHICS_DISPMODE_LANDSCAPE_270, ///< handset rotate 270 degree CCW (90 degree CW)
    VEN_GRAPHICS_DISPMODE_PORTRAIT_ONLY,
    VEN_GRAPHICS_DISPMODE_LANDSCAPE_ONLY,
	VEN_GRAPHICS_DISPMODE_TOTAL,

	/// alias	
	VEN_GRAPHICS_DISPMODE_LANDSCAPE = VEN_GRAPHICS_DISPMODE_LANDSCAPE_90
};
typedef u8 ven_GraphicsDisplayMode_t;

typedef struct
{
    u32 width;                          ///< number of pixels per row
    u32 height;                         ///< number of pixels per column
    u32 nColorScheme;                   ///< color scheme
    u32 nColorDepth;                    ///< number of significant bits per pixel
} ven_GraphicBitmapInfo_t;

typedef struct
{
    u32         width;                  ///< pixel width
    u32         height;                 ///< pixel height
    u32         pitch;                  ///< Bytes per row in bytes
    u16         bpp;                    ///< Bits per pixel
    u8         *pData;                  ///< Pointer to bitmap raw data
} ven_GraphicDIB_t;

typedef struct
{
    s32 x;                              ///< X position of left
    s32 y;                              ///< Y position of top
    s32 w;                              ///< Rectangle width
    s32 h;                              ///< Rectangle height
} ven_GraphicsRect_t;

/**
 *  Degree definition for ellipse and arc
 *         90
 *         |
 *  180 ------- 0 (360)
 *         |
 *        270
 */
typedef struct
{
    s32 xc;                             ///< X position of the center of the ellipse
    s32 yc;                             ///< Y position of the center of the ellipse
    s32 rx;                             ///< Specifies the half width of the ellipse
    s32 ry;                             ///< Specifies the half height of the ellipse
} ven_GraphicsEllipse_t;

typedef struct
{
    s32 xc;                             ///< X position of the center of the arc
    s32 yc;                             ///< Y position of the center of the arc
    s32 rx;                             ///< Specifies the half width of the arc
    s32 ry;                             ///< Specifies the half height of the arc
    s16 startAngle;                     ///< Start angle (in degree 0~360)
    s16 endAngle;                       ///< End angle (in degree 0~360)
} ven_GraphicsArc_t;

typedef struct
{
    s32 x1;                             ///< X position of top vertex
    s32 y1;                             ///< Y position of top vertex
    s32 x2;                             ///< X position of left bottom vertex
    s32 y2;                             ///< Y position of left bottom vertex
    s32 x3;                             ///< X position of right bottom vertex
    s32 y3;                             ///< Y position of right bottom vertex
} ven_GraphicsTriangle_t;

typedef struct
{
    u16 width;                          ///< Screen width
    u16 height;                         ///< Screen height
    u16 bpp;                            ///< Bits per pixel
    ven_GraphicsRect_t statusBarRect;   ///< Size and position of status bar
    ven_GraphicsRect_t softkeyRect;     ///< Size and position of softkey
} ven_GraphicsDisplayInfo_t;

typedef void* ven_GraphicsCanvas;
typedef void* ven_GraphicsBitmap;
typedef u32 RGB888Color_t;

typedef struct
{
    ven_font_size_e FontSize;     ///< font size for slide text
    ven_font_style_e FontStyle;   ///< font style for slide text
    u16 *pText;                   ///< text string
    u32 width;                    ///< display width for slide text
    u32 height;                   ///< display height for slide text
    s32 x;
    s32 y;
    u32 color;
    ven_GraphicsCanvas * pCanvas;
} ven_GraphicSlideTextInfo_t;

typedef struct
{
    u32 magicNum;                           ///< magic number of this kind of type
    u32 timerID;                            ///< the index of call back data
    s32 tailPositon;                        ///< last position of text
    s32 curPosition;                        ///< current position of text
    u32 textLength;                         ///< text length (pixel)
    u32 sdkHandler;                         ///< handler
    u16* pImagebuffer;                      ///< backup clip region buffer
    u16* pCanvasDIB;                        ///< canvas DIB of clip region buffer
    ven_GraphicSlideTextInfo_t textInfo;
} ven_graphicSlideHandle_t;

typedef struct
{
    u32 timerID;            ///< timer id
    u32 hSlideText;         ///< the handler id of this slider
    u32 UserData;           ///< user data
} ven_graphicSlideCBData_t;

/*
 * Slide text timeout callback function prototype
 */
typedef void (*VEN_GRA_SLIDETEXT_TIMEOUT_FUNC_PTR)(u32 hSlideText, u32 userData);

/**
 *  VEN_MAKE_RGB888
 *
 *  @brief  This macro will compose a RGB888 color value from given red, green, and blue.
 *
 *  @retval The RGB888Color_t composed from the given R, G, B colors
 */
#define VEN_MAKE_RGB888(_R, _G, _B) (0xff000000|(_R<<16)|(_G<<8)|_B)

/**
 *  ven_graphics_getDisplayInfo
 *
 *  @brief  This function will return screen information.
 *
 *  @param  pInfo  [out]Display information structure
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getDisplayInfo(ven_GraphicsDisplayInfo_t *pInfo);

/**
 *  ven_graaphics_createCanvas
 *
 *  @brief  This function will create a handle of graphics canvas.
 *
 *  @param  ppCanvas  [out]Handle of graphics canvas
 *  @param  width     [in]Width of the canvas
 *  @param  height    [in]Height of the canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_createCanvas(ven_GraphicsCanvas **ppCanvas, u32 width, u32 height);

/**
 *  ven_graphics_createCanvasNS
 *
 *  @brief  This function will create a handle of graphics canvas that frame buffer will not share with other task.
 *  @brief  If specified width/height are bigger than system width/height, then system canvas will be created.   
 *  @brief  Otherwise, canvas with specified width/height size will be created in DisplayManager Mode.   
 *
 *  @param  handle    [in]Handle of the task
 *  @param  ppCanvas  [out]Handle of graphics canvas
 *  @param  width     [in]Width of the canvas
 *  @param  height    [in]Height of the canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_createCanvasNS(u32 handle, ven_GraphicsCanvas **ppCanvas, u32 width, u32 height);

/**
 *  ven_graphics_createCanvasFromDIB
 *
 *  @brief  This function will create a handle of graphics canvas.
 *
 *  @param  ppCanvas  [out]Handle of graphics canvas
 *  @param  pVenDIB   [in]Destination DIB to be set to new canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 *
 *  @note Canvas will only keep the bitmap data in the DIB, user should
 *            NOT release the bitmap data in DIB before the canvas is released.
 */
ven_graphics_ret_t ven_graphics_createCanvasFromDIB(ven_GraphicsCanvas **ppCanvas, ven_GraphicDIB_t *pVenDIB);
/**
 *  ven_graphics_releaseCanvas
 *
 *  @brief  This function will release the resource of graphics canvas.
 *
 *  @param  pCanvas   [in]Handle of graphics canvas
 *
 *  @retval none
 */
void ven_graphics_releaseCanvas(ven_GraphicsCanvas *pCanvas);

/**
 *  ven_graphics_getCanvasDIB
 *
 *  @brief  This function will return the DIB of the given canvas.
 *
 *  @param  pCanvas   [in]Handle of graphics canvas
 *
 *  @retval DIB of the given canvas
 *
 *  @note   The DIB should not be freed manually. It will be freed when the canvas is freed.
 */
ven_GraphicDIB_t* ven_graphics_getCanvasDIB(ven_GraphicsCanvas *pCanvas);

/**
 *  ven_graphics_clearCanvas
 *
 *  @brief  This function will reset the resources in the canvas.
 *
 *  @param  pCanvas   [in]Handle of graphics canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_clearCanvas(ven_GraphicsCanvas *pCanvas);

/**
 *  ven_graphics_getDirtyAraa
 *
 *  @brief  This function will return dirty area of canvas.
 *
 *  @param  pCanvas   [in]Handle of graphics canvas
 *  @param  pRect     [out]Pointer to the memory to store dirty area information
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getDirtyArea(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pRect);

/**
 *  ven_graphics_setDirtyAraa
 *
 *  @brief  This function will set dirty area to canvas.
 *
 *  @param  pCanvas   [in]Handle of graphics canvas
 *  @param  pRect     [in]New dirty area to set to the canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 *
 *  @note   If pRect is NULL, the dirty area will be set to full size of the canvas
 */
ven_graphics_ret_t ven_graphics_setDirtyArea(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pRect);

/**
 *  ven_graphics_setColor
 *
 *  @brief  This function will set graphic color according the input color item.
 *
 *  @param  pCanvas       [in]Handle of graphics canvas
 *  @param  ColorItem     [in]Enum value of color item. Refer to ven_ColorItem_t
 *  @param  RGB888_color  [in]Draw color of the input color item
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid

 */
ven_graphics_ret_t ven_graphics_setColor(ven_GraphicsCanvas *pCanvas, ven_ColorItem_t ColorItem, RGB888Color_t RGB888_color);

/**
 *  ven_graphics_getRGB888Color
 *
 *  @brief  This function will get graphic color according the input color item.
 *
 *  @param  pCanvas       [in]Handle of graphics canvas
 *  @param  ColorItem     [in]Enum value of color item. Refer to ven_ColorItem_t
 *  @param  RGB888_color  [out]Draw color of the input color item
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid

 */
ven_graphics_ret_t ven_graphics_getRGB888Color(ven_GraphicsCanvas *pCanvas, ven_ColorItem_t ColorItem, RGB888Color_t *RGB888_color);

/**
 *  ven_graphics_drawPoint
 *
 *  @brief  This function will draw a point.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  x          [in]X position of point
 *  @param  y          [in]Y position of point
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawPoint(ven_GraphicsCanvas *pCanvas, s32 x, s32 y);

/**
 *  ven_graphics_drawLine
 *
 *  @brief  This function will draw a line from start point to end point.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  x1         [in]X position of start point
 *  @param  y1         [in]Y position of start point
 *  @param  x2         [in]X position of end point
 *  @param  y2         [in]Y position of end point
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawLine(ven_GraphicsCanvas *pCanvas, s32 x1, s32 y1, s32 x2, s32 y2);

/**
 *  ven_graphics_drawRectangle
 *
 *  @brief  This function will draw a hollow rectangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pRect      [in]Pointer to the input rectangle
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawRectangle(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pRect);

/**
 *  ven_graphics_drawRoundRectangle
 *
 *  @brief  This function will draw a hollow round rectangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pRect      [in]Pointer to the input rectangle
 *  @param  rx         [in]Specifies the half width of the ellipse used to draw the rounded corners
 *  @param  ry         [in]Specifies the half height of the ellipse used to draw the rounded corners
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawRoundRectangle(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pRect, s32 rx, s32 ry);

/**
 *  ven_graphics_drawEllipse
 *
 *  @brief  This function will draw a hollow ellipse.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pEllipse   [in]Pointer to the input ellipse
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawEllipse(ven_GraphicsCanvas *pCanvas, ven_GraphicsEllipse_t *pEllipse);

/**
 *  ven_graphics_drawArc
 *
 *  @brief  This function will draw a hollow arc.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pArc       [in]Pointer to the input arc
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawArc(ven_GraphicsCanvas *pCanvas, ven_GraphicsArc_t *pArc);

/**
 *  ven_graphics_drawTriangle
 *
 *  @brief  This function will draw a hollow triangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pTriangle  [in]Pointer to the input triangle
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawTriangle(ven_GraphicsCanvas *pCanvas, ven_GraphicsTriangle_t *pTriangle);

/**
 *  ven_graphics_fillRectangle
 *
 *  @brief  This function will draw a filled rectangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pRect      [in]Pointer to the input rectangle
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_fillRectangle(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pRect);

/**
 *  ven_graphics_fillRoundRectangle
 *
 *  @brief  This function will draw a filled round rectangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pRect      [in]Pointer to the input rectangle
 *  @param  rx         [in]Specifies the half width of the ellipse used to draw the rounded corners
 *  @param  ry         [in]Specifies the half height of the ellipse used to draw the rounded corners
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_fillRoundRectangle(ven_GraphicsCanvas * pCanvas, ven_GraphicsRect_t *pRect, s32 rx, s32 ry);

/**
 *  ven_graphics_fillEllipse
 *
 *  @brief  This function will draw a filled ellipse.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pEllipse   [in]Pointer to the input ellipse
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_fillEllipse(ven_GraphicsCanvas *pCanvas, ven_GraphicsEllipse_t *pEllipse);

/**
 *  ven_graphics_fillArc
 *
 *  @brief  This function will draw a filled arc.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pArc       [in]Pointer to the input arc
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_fillArc(ven_GraphicsCanvas *pCanvas, ven_GraphicsArc_t *pArc);

/**
 *  ven_graphics_fillTriangle
 *
 *  @brief  This function will draw a filled triangle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pTriangle  [in]Pointer to the input triangle
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_fillTriangle(ven_GraphicsCanvas *pCanvas, ven_GraphicsTriangle_t *pTriangle);

/**
 *  ven_graphics_bitBlt
 *
 *  @brief  This function will draw an image on the canvas.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pBitmap    [in]Pointer to bitmap
 *  @param  x          [in]X position to draw
 *  @param  y          [in]Y position to draw
 *  @param  transType  [in]Transform type. Refer to ven_GraphicsTransform_e
 *  @param  drawMode   [in]Drawing Mode. Refer to ven_GraphicsDrawMode_e
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_bitBlt(ven_GraphicsCanvas *pCanvas, ven_GraphicsBitmap *pBitmap, s32 x, s32 y, ven_GraphicsDrawMode_t drawMode);

/**
 *  ven_graphics_bitBlt_ex
 *
 *  @brief  This function will draw an image on the canvas.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pDstRect   [in]Pointer to the canvas rectangle
 *  @param  pBitmap    [in]Pointer to bitmap
 *  @param  pSrcRect   [in]Pointer to the bitmap rectangle
 *  @param  transType  [in]Transform type. Refer to ven_GraphicsTransform_e
 *  @param  drawMode   [in]Drawing Mode. Refer to ven_GraphicsDrawMode_e
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_bitBlt_ex(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pDstRect, ven_GraphicsBitmap *pBitmap, ven_GraphicsRect_t *pSrcRect, ven_GraphicsDrawMode_t drawMode);

/**
 *  ven_graphics_screenUpdate
 *
 *  @brief  This function will help to update the canvas to LCD.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  updateMode [in]LCD update mode. Refer to ven_GraphicsUpdateMode_t
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 *  @note  blocking mode
 */
ven_graphics_ret_t ven_graphics_screenUpdate(ven_GraphicsCanvas *pCanvas, ven_GraphicsUpdateMode_t updateMode);

/**
 *  ven_graphics_screenUpdate_ex
 *
 *  @brief  This function will help to update the canvas to LCD.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  updateMode [in]LCD update mode. Refer to ven_GraphicsUpdateMode_t
 *  @param  bUpdateQuick 	[in]  TRUE: non-blocking during updating. It will return immediately after sending command to low level. This one is not suggested.
 * 							FALSE: blocking during updating. It will wait for that low level really finish its updating, then return.
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */

ven_graphics_ret_t ven_graphics_screenUpdate_ex(ven_GraphicsCanvas *pCanvas, ven_GraphicsUpdateMode_t updateMode, bool bUpdateQuick);

/**
 *  ven_graphics_isScreenUpdateFinish
 *
 *  @brief  This function will help to check screenupdate whether finish.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */

ven_graphics_ret_t ven_graphics_isScreenUpdateFinish(ven_GraphicsCanvas *pCanvas);


/**
 *  ven_graphics_setClipArea
 *
 *  @brief  This function will set the clip area into canvas handle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pClipArea  [in]Pointer to the clip area
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_setClipArea(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pClipArea);

/**
 *  ven_graphics_getClipArea
 *
 *  @brief  This function will set the clip area into canvas handle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pClipArea  [out]Rectangle information of clip area
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getClipArea(ven_GraphicsCanvas *pCanvas, ven_GraphicsRect_t *pClipArea);

/**
 *  ven_graphics_drawText
 *
 *  @brief  This function will set the clip area into canvas handle.
 *
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  pFontAttr  [in]Handle of font attribute
 *  @param  pText      [in]Pointer to the Unicode string buffer
 *  @param  x          [in]X position to draw
 *  @param  x          [in]Y position to draw
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_drawText(ven_GraphicsCanvas *pCanvas, ven_FontAttr *pFontAttr, u16 *pText, s32 x, s32 y);

/**
 *  ven_graaphics_createBitmap
 *
 *  @brief  This function will create a handle of bitmap.
 *
 *  @param  ppBitmap    [out]Handle of bitmap
 *  @param  pBitmapInfo [in]Information of the bitmap
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_createBitmap(ven_GraphicsBitmap **ppBitmap, ven_GraphicBitmapInfo_t *pBitmapInfo);

/**
 *  ven_graphics_releaseBitmap
 *
 *  @brief  This function will release the resource of bitmap.
 *
 *  @param  pBitmap   [in]Handle of bitmap
 *
 *  @retval none
 */
void ven_graphics_releaseBitmap(ven_GraphicsBitmap *pBitmap);

/**
 *  ven_graphics_getBitmapInfo
 *
 *  @brief  This function will return ven_GraphicBitmapInfo_t of the given ven_GraphicsBitmap.
 *
 *  @param  pBitmap     [in]Handle of bitmap
 *  @param  pBitmapInfo [in]Information of the bitmap
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getBitmapInfo(ven_GraphicsBitmap *pBitmap, ven_GraphicBitmapInfo_t *pBitmapInfo);

/**
 *  ven_graphics_getBitmapDIB
 *
 *  @brief  This function will return ven_GraphicDIB_t of the given ven_GraphicsBitmap.
 *
 *  @param  pBitmap     [in]Handle of bitmap
 *
 *  @retval DIB of the given bitmap
 *
 *  @note   The DIB should not be freed manually. It will be freed when the bitmap is freed.
 */
ven_GraphicDIB_t* ven_graphics_getBitmapDIB(ven_GraphicsBitmap *pBitmap);

/**
 *  ven_graphics_getBitmapAlphaMask
 *
 *  @brief  This function will return the alphamask (if exists) of the given ven_GraphicsBitmap.
 *
 *  @param  pBitmap     [in]Handle of bitmap
 *
 *  @retval pointer to the alpha mask
 *
 *  @note   The alpha mask should not be freed manually. It will be freed when the bitmap is freed.
 */
u8* ven_graphics_getBitmapAlphaMask(ven_GraphicsBitmap *pBitmap);

/**
 *  ven_graphics_getStatusBarVisibility
 *
 *  @brief  This function gets the visibility of status bar
 *
 *  @param  SdkHandle     [in]Handle of SDK
 *  @param  pbVisble      [out]Pointer to memory to store the visibility of status bar
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getStatusBarVisibility(u32 SdkHandle, bool *pbVisble);

/**
 *  ven_graphics_setStatusBarVisibility
 *
 *  @brief  This function changes the visibility of status bar
 *
 *  @param  SdkHandle     [in]Handle of SDK
 *  @param  bVisble       [in]New visibility of status bar
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_setStatusBarVisibility(u32 SdkHandle, bool bVisble);

/**
 *  ven_graphics_getSoftkeyVisibility
 *
 *  @brief  This function gets the visibility of softkey
 *
 *  @param  SdkHandle     [in]Handle of SDK
 *  @param  pbVisble      [out]Pointer to memory to store the visibility of softkey
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_getSoftkeyVisibility(u32 SdkHandle, bool *pbVisble);


/**
 *  ven_graphics_setSoftkeyVisibility
 *
 *  @brief  This function changes the visibility of softkey
 *
 *  @param  SdkHandle     [in]Handle of SDK
 *  @param  bVisble       [in]New visibility of softkey
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS if success
 *          VEN_GRAPHICS_RET_FAILED if failed
 *          VEN_GRAPHICS_RET_BAD_PARAM if input parameter is invalid
 */
ven_graphics_ret_t ven_graphics_setSoftkeyVisibility(u32 SdkHandle, bool bVisble);

/**
 *  ven_graphics_createSlideText
 *
 *  @brief  Create slide text handle with slide text info
 *
 *  @param  phSlideText   [out] Pointer to store output slide text handle
 *  @param  pSTextInfo    [in] Information of slide text
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Create handle successfully
 *          VEN_GRAPHICS_RET_FAILED    Create handle failed
 *
 *  @note   pSTextInfo could be NULL. User can use ven_graphics_setSlideTextInfo
 *          to set/change info in the future.
 */
ven_graphics_ret_t ven_graphics_createSlideText(u32 *phSlideText,
        ven_GraphicSlideTextInfo_t *pSTextInfo);

/**
 *  ven_graphics_setSlideTextInfo
 *
 *  @brief  Set slide text info to the given handle
 *
 *  @param  hSlideText    [in] Slide text handle
 *  @param  pSTextInfo    [in] Information of slide text
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Set slide text info successfully
 *          VEN_GRAPHICS_RET_FAILED    Set slide text info failed
 *
 */
ven_graphics_ret_t ven_graphics_setSlideTextInfo(u32 hSlideText,
        ven_GraphicSlideTextInfo_t *pSTextInfo);

/**
 *  ven_graphics_drawSlideText
 *
 *  @brief  Draw slide text
 *
 *  @param  pCanvas       [in] destination canvas
 *  @param  hSlideText    [in] handle of slide text
 *  @param  x             [in] x position to draw
 *  @param  y             [in] y position to draw
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Set slide text info successfully
 *          VEN_GRAPHICS_RET_FAILED    Set slide text info failed
 *
 */
ven_graphics_ret_t ven_graphics_drawSlideText(ven_GraphicsCanvas *pCanvas,
        u32 hSlideText,
        s32 x,
        s32 y);

/**
 *  ven_graphics_startSliding
 *
 *  @brief  Start sliding
 *
 *  @param  hSlideText      [in] Slide text handle of slide text
 *  @param  SdkHandle       [in] SDK handle of caller
 *  @param  UserData        [in] User data to be carried in callback function
 *  @param  pCB             [in] Callback function to be called when timeout
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Set slide text info successfully
 *          VEN_GRAPHICS_RET_FAILED    Set slide text info failed
 *
 *  @note  Start sliding will start a periodic timer. When the timer timeout,
 *         the pCB will be called to indicate user to call draw function
 */
ven_graphics_ret_t ven_graphics_startSliding(u32 hSlideText,
        u32 SdkHandle,
        u32 UserData,
        VEN_GRA_SLIDETEXT_TIMEOUT_FUNC_PTR pCB);

/**
 *  ven_graphics_stopSliding
 *
 *  @brief  Stop sliding
 *
 *  @param  hSlideText      [in] Slide text handle of slide text
 *  @param  SdkHandle       [in] SDK handle of caller
 *  @param  pCB             [in] Callback function to be called when timeout
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Set slide text info successfully
 *          VEN_GRAPHICS_RET_FAILED    Set slide text info failed
 *
 *  @note  Stop sliding will stop the periodic timer started in start function.
 */
ven_graphics_ret_t ven_graphics_stopSliding(u32 hSlideText,
        u32 SdkHandle,
        VEN_GRA_SLIDETEXT_TIMEOUT_FUNC_PTR pCB);

/**
 *  ven_graphics_releaseSlideText
 *
 *  @brief  Release slide text handle
 *
 *  @param  hSlideText      [in] Slide text handle of slide text
 *
 *  @retval VEN_GRAPHICS_RET_SUCCESS   Set slide text info successfully
 *          VEN_GRAPHICS_RET_FAILED    Set slide text info failed
 *
 */
ven_graphics_ret_t ven_graphics_releaseSlideText(u32 hSlideText);

/**
 *  ven_graphics_getTransType
 *
 *  @brief  This function will get the transparency type of the given ven_GraphicsBitmap.
 *  @param  pBitmap     [in]Handle of bitmap
 *  @param  pType     [out]transparency type of bitmap
 *  @retval VEN_GRAPHICS_RET_SUCCESS   get transparency type successfully
 *              VEN_GRAPHICS_RET_FAILED    get transparency type failed
 */
ven_graphics_ret_t ven_graphics_getTransType(ven_GraphicsBitmap *pBitmap, ven_GraphicsTransType_t *pType);

/**
 *  ven_graphics_setTransType
 *
 *  @brief  This function will set the transparency type of the given ven_GraphicsBitmap.
 *  @param  pBitmap     [in]Handle of bitmap
 *  @param  type     [in]transparency type of bitmap
 *  @retval VEN_GRAPHICS_RET_SUCCESS   get transparency type successfully
 *              VEN_GRAPHICS_RET_FAILED    get transparency type failed
 */
ven_graphics_ret_t ven_graphics_setTransType(ven_GraphicsBitmap *pBitmap, ven_GraphicsTransType_t type);

/**
 *  ven_graphics_getTransColor
 *
 *  @brief  This function will get the transparency color of the given ven_GraphicsBitmap.
 *  @param  pBitmap     [in]Handle of bitmap
 *  @param  pType        [out]transparency color
 *  @retval VEN_GRAPHICS_RET_SUCCESS   get transparency type successfully
 *              VEN_GRAPHICS_RET_FAILED    get transparency type failed
 */
ven_graphics_ret_t ven_graphics_getTransColor(ven_GraphicsBitmap *pBitmap, u32 *pColor);

/**
 *  ven_graphics_setDisplayMode
 *
 *  @brief  This function will set display mode to transform the coordinate of the canvas in SDK.
 *  @param  pCanvas    [in]Handle of graphics canvas
 *  @param  nDispMode [in]diaplay mode
 *  @retval VEN_GRAPHICS_RET_SUCCESS   
 *              VEN_GRAPHICS_RET_FAILED    
 */
ven_graphics_ret_t ven_graphics_setDisplayMode(ven_GraphicsCanvas *pCanvas, ven_GraphicsDisplayMode_t nDispMode);

/**
 *  ven_graphics_setMmiDisplayMode
 *
 *  @brief  This function will set the display mode by WndSetAppDisplayMode in MMI. 
 *  @param  nDispMode [in]diaplay mode
 *  @retval VEN_GRAPHICS_RET_SUCCESS   
 *              VEN_GRAPHICS_RET_FAILED 
 */
ven_graphics_ret_t ven_graphics_setMmiDisplayMode(ven_GraphicsDisplayMode_t nDispMode, ven_req_data_t *ptVenReq);

#endif // __VEN_GRAPHICS_DEFINE_H__

