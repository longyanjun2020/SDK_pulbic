/**
 * @file mmi_mae_display_types.h
 *
 * @version $Id: mmi_mae_display_types.h  $
 */
#ifndef __MMI_MAE_DISPLAY_TYPES_H__
#define __MMI_MAE_DISPLAY_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_graphic_forward.h"
#include "mmi_mae_graphic_types.h"
#include "mmi_mae_display_forward.h"


#define MAIN_DISPLAY MAE_DISPID_MAIN
#ifdef __DUAL_LCD__
#define SUB_DISPLAY MAE_DISPID_SUB
#endif
#define TOTAL_DISPLAY MAE_DISPID_SUM

enum DisplayProperty_e_
{
    DISP_PROP_DISPMODE = 0,
    DISP_PROP_CLIENTAREA,
    DISP_PROP_DISPID,      ///< The property id to get display ID
    DISP_PROP_CVRT_TO_ABS_RECT,
    DISP_PROP_CVRT_FROM_ABS_RECT,
    DISP_PROP_TOTAL
};

enum DisplayMode_e_
{
    DEFAULT_DISPMODE = 0,
    DISPMODE_PORTRAIT = 0,
	DISPMODE_LANDSCAPE_90, ///< handset rotate 90 degree CCW
	DISPMODE_LANDSCAPE_270, ///< handset rotate 270 degree CCW (90 degree CW)
    DISPMODE_PORTRAIT_ONLY,
    DISPMODE_LANDSCAPE_ONLY,
	DISPMODE_TOTAL, 

/// alias
	DISPMODE_LANDSCAPE = DISPMODE_LANDSCAPE_90
};

#define DISP_BRUSH_SMALL 	1
#define DISP_BRUSH_SIZE_2   2
#define DISP_BRUSH_MEDIUM 	3
#define DISP_BRUSH_LARGE 	5
#define DISP_BRUSH_MAX 		30

enum DisplayDottedType_e_
{
    DISP_SOLID_LINE = 0,
    DISP_DOTTED_LINE_1,
    DISP_DOTTED_LINE_2,
    DISP_DOTTED_LINE_3,
    DISP_DOTTED_LINE_4,
    DISP_DOTTED_TOTAL,
};

enum DisplayLayer_e_
{
    MMI_DISP_LAYER_0=0,
    MMI_DISP_LAYER_1,
    MMI_DISP_LAYER_2,
    MMI_DISP_LAYER_3,
    MMI_DISP_LAYER_TOTAL
};

enum MMIBuffer_e_
{
    MMI_BUFFER_0=0,
    MMI_BUFFER_1,
    MMI_BUFFER_TOTAL
};

enum DisplayDrawType_e_
{
    DISP_DRAWTYPE_BORDER = 0,
    DISP_DRAWTYPE_FILL,
    DISP_DRAWTYPE_FILL_BOLDER,
    DISP_DRAWTYPE_INVERT,
    DISP_DRAWTYPE_TOTAL
};

//deprecated
#define  DRAW_RECT_BORDER      DISP_DRAWTYPE_BORDER
#define  DRAW_RECT_FILL        DISP_DRAWTYPE_FILL
#define  DRAW_RECT_FILL_BORDER DISP_DRAWTYPE_FILL_BOLDER
#define  DRAW_RECT_INVERT      DISP_DRAWTYPE_INVERT
#define  DRAW_RECT_TOTAL       DISP_DRAWTYPE_TOTAL
#define  DRAW_ELLIPSE_BORDER       DISP_DRAWTYPE_BORDER
#define  DRAW_ELLIPSE_FILL         DISP_DRAWTYPE_FILL
#define  DRAW_ELLIPSE_FILL_BORDER  DISP_DRAWTYPE_FILL_BOLDER
#define  DRAW_ELLIPSE_TOTAL        DISP_DRAWTYPE_TOTAL
#define  DRAW_TRIANGLE_BORDER      DISP_DRAWTYPE_BORDER
#define  DRAW_TRIANGLE_FILL        DISP_DRAWTYPE_FILL
#define  DRAW_TRIANGLE_FILL_BORDER DISP_DRAWTYPE_FILL_BOLDER
#define  DRAW_TRIANGLE_TOTAL       DISP_DRAWTYPE_TOTAL
#define  DRAW_ARC_BORDER       DISP_DRAWTYPE_BORDER
#define  DRAW_ARC_FILL         DISP_DRAWTYPE_FILL
#define  DRAW_ARC_FILL_BORDER  DISP_DRAWTYPE_FILL_BOLDER
#define  DRAW_ARC_TOTAL        DISP_DRAWTYPE_TOTAL

/*
Display upadte type
*/
enum DisplayUpdateType_e_
{
    MMI_DISP_UPDATE_DEFER = 0,
    MMI_DISP_UPDATE_NORMAL,
    MMI_DISP_UPDATE_FORCE_FULLSCR
};

/*
Display upadte type
*/
enum DisplayUpdateMode_e_
{
    DISP_UPDATEMODE_NORMAL = 0,
    DISP_UPDATEMODE_PALETTE
};

struct DisplayPaletteConfig_t_
{
	ColorScheme_t nFormat;							/**< palette color format*/
	u32			nNumber;          				/**< palette number of entry*/
	u8   			*paletteBuffer;					/**< palette buffer */
	u32			nPaletteBufferLen;				/**< palette buffer length*/
};

struct LayerInvalidateInfo_t_
{
	Rect_t 			tRc;
	DisplayLayer_e 	     nLayer;
};

struct LayerCreateInfo_t_
{
	Rect_t 			tRc;
	u32			    nFormat;
	boolean		bTranspBGEnable;	// TRUE:if need to draw transparent background
};

struct G3DInfo_t_
{
    u32 width;    ///< Width in pixels
    u32 height;   ///< Height in pixels
    u32 pitch;    ///< Pitch, bytes per row
    u8 *pData;    ///< Buffer pointer
};

struct G3DWindow_t_
{
	Rect_t region;
	u32 pitch;
	void *data;
};

#endif /* __MMI_MAE_DISPLAY_TYPES_H__ */
