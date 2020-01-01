//==============================================================================
//
//  File        : mmp_display_inc.h
//  Description : INCLUDE File for the Firmware Display Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_DISPLAY_INC_H_
#define _MMP_DISPLAY_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define DISP_WHILE_TIMEOUT  (0x100000)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/* Display Attribute */
typedef enum _MMP_DISPLAY_CONTROLLER
{
    MMP_DISPLAY_PRM_CTL = 0,
    MMP_DISPLAY_SCD_CTL,
    MMP_DISPLAY_CTL_MAX
} MMP_DISPLAY_CONTROLLER;

typedef enum _MMP_DISPLAY_DEV_TYPE
{
	MMP_DISPLAY_NONE = 0,
    MMP_DISPLAY_P_LCD,
    MMP_DISPLAY_S_LCD,
    MMP_DISPLAY_P_LCD_FLM,
    MMP_DISPLAY_RGB_LCD,
    MMP_DISPLAY_TV,
    MMP_DISPLAY_HDMI,
    MMP_DISPLAY_CCIR
} MMP_DISPLAY_DEV_TYPE;

typedef enum _MMP_DISPLAY_OUTPUT_SEL 
{
	MMP_DISPLAY_SEL_NONE = 0,		///< Choose no output device
	MMP_DISPLAY_SEL_MAIN_LCD,		///< Choose MAIN LCD for output
	MMP_DISPLAY_SEL_SUB_LCD,		///< Choose SUB LCD for output
	MMP_DISPLAY_SEL_NTSC_TV,		///< Choose NTSC TV for output
	MMP_DISPLAY_SEL_PAL_TV,			///< Choose PAL TV for output
	MMP_DISPLAY_SEL_HDMI,      		///< Choose HDMI for output
	MMP_DISPLAY_SEL_CCIR  			///< Choose CCIR for output
} MMP_DISPLAY_OUTPUT_SEL;

typedef enum _MMP_DISPLAY_ROTATE_TYPE
{
    MMP_DISPLAY_ROTATE_NO_ROTATE = 0,
    MMP_DISPLAY_ROTATE_RIGHT_90,
    MMP_DISPLAY_ROTATE_RIGHT_180,
    MMP_DISPLAY_ROTATE_RIGHT_270,
    MMP_DISPLAY_ROTATE_MAX
} MMP_DISPLAY_ROTATE_TYPE;

typedef enum _MMP_DISPLAY_COLORMODE
{
	// Support color format for LCD controller.
    MMP_DISPLAY_COLOR_RGB565 = 0,
    MMP_DISPLAY_COLOR_RGB888,
    MMP_DISPLAY_COLOR_YUV422,
    MMP_DISPLAY_COLOR_YUV420,
    MMP_DISPLAY_COLOR_YUV420_TILE,
    MMP_DISPLAY_COLOR_YUV420_INTERLEAVE,
    MMP_DISPLAY_COLOR_UNSUPPORT
} MMP_DISPLAY_COLORMODE;

typedef enum _MMP_DISPLAY_WIN_COLOR
{
	// Support color for eacg window layer.
	MMP_DISPLAY_WIN_COLOR_RGB565 = 0,
	MMP_DISPLAY_WIN_COLOR_ARGB4444,
	MMP_DISPLAY_WIN_COLOR_ARGB8888,
	MMP_DISPLAY_WIN_COLOR_YUV422,
	// Un-support.
	MMP_DISPLAY_WIN_COLOR_UNSUPPORT
} MMP_DISPLAY_WIN_COLOR;

typedef enum _MMP_DISPLAY_SEMITP_FUNC
{
    MMP_DISPLAY_SEMITP_AVG = (0x00 << 2),
    MMP_DISPLAY_SEMITP_AND = (0x01 << 2),
    MMP_DISPLAY_SEMITP_OR  = (0x02 << 2),
    MMP_DISPLAY_SEMITP_INV = (0x03 << 2)
} MMP_DISPLAY_SEMITP_FUNC;

typedef enum _MMP_DISPLAY_WIN_COLORDEPTH
{
    MMP_DISPLAY_WIN_COLORDEPTH_4 = 0,
    MMP_DISPLAY_WIN_COLORDEPTH_8,
    MMP_DISPLAY_WIN_COLORDEPTH_16,
    MMP_DISPLAY_WIN_COLORDEPTH_ARGB3454,
    MMP_DISPLAY_WIN_COLORDEPTH_ARGB4444,
    MMP_DISPLAY_WIN_COLORDEPTH_24,
    MMP_DISPLAY_WIN_COLORDEPTH_YUV420,
    MMP_DISPLAY_WIN_COLORDEPTH_YUV422,
    MMP_DISPLAY_WIN_COLORDEPTH_32,
    MMP_DISPLAY_WIN_COLORDEPTH_YUV420_INTERLEAVE
} MMP_DISPLAY_WIN_COLORDEPTH;

typedef enum _MMP_DISPLAY_WIN_ID
{
    MMP_DISPLAY_WIN_MAIN       = 0,
    MMP_DISPLAY_WIN_PIP        = 1,
    MMP_DISPLAY_WIN_OSD        = 3,
    MMP_DISPLAY_WIN_OVERLAY    = 4,
    MMP_DISPLAY_WIN_MAX        = 5
} MMP_DISPLAY_WIN_ID;

typedef enum _MMP_DISPLAY_DUPLICATE 
{
    MMP_DISPLAY_DUPLICATE_1X = 0,
    MMP_DISPLAY_DUPLICATE_2X,
    MMP_DISPLAY_DUPLICATE_3X,
    MMP_DISPLAY_DUPLICATE_4X,
    MMP_DISPLAY_DUPLICATE_5X,
    MMP_DISPLAY_DUPLICATE_6X,
    MMP_DISPLAY_DUPLICATE_HALF,
    MMP_DISPLAY_DUPLICATE_NUM
} MMP_DISPLAY_DUPLICATE;

typedef enum _MMP_DISPLAY_ALPHA_FMT
{
    MMP_DISPLAY_ALPHA_RGBA = 0,
    MMP_DISPLAY_ALPHA_ARGB,
    MMP_DISPLAY_ALPHA_GLOBAL,
    MMP_DISPLAY_ALPHA_NONE		// Disable alpha blending
} MMP_DISPLAY_ALPHA_FMT;

typedef enum _MMP_DISPLAY_RGB_IF 
{
    MMP_DISPLAY_RGB_IF1 = 0,
    MMP_DISPLAY_RGB_IF2,
    MMP_DISPLAY_RGB_IF_BOTH
} MMP_DISPLAY_RGB_IF;

typedef enum _MMP_DISPLAY_SRC_CAM
{
    MMP_DISPLAY_SRC_FRONTCAM = 0,   ///< For PRM_SENSOR
    MMP_DISPLAY_SRC_REARCAM,        ///< For SCD_SENSOR or USBH_SENSOR
    MMP_DISPLAY_SRC_CAM_NUM
} MMP_DISPLAY_SRC_CAM;

/* LCD Attribute */
typedef enum _MMP_LCD_COLORDEPTH
{
    MMP_LCD_COLORDEPTH_16 = 0,  ///< Panel color is 16bit
    MMP_LCD_COLORDEPTH_18,      ///< Panel color is 18bit
    MMP_LCD_COLORDEPTH_24       ///< Panel color is 24bit
} MMP_LCD_COLORDEPTH;

typedef enum _MMP_LCD_CS_SEL
{
    MMP_LCD_CS_SEL_1 = 0,
    MMP_LCD_CS_SEL_2
} MMP_LCD_CS_SEL;

/* TV Attribute */
typedef enum _MMP_TV_TYPE {
    MMP_TV_TYPE_NTSC = 0,
    MMP_TV_TYPE_PAL
} MMP_TV_TYPE;

typedef enum _MMP_TV_SYNC_MODE
{
	MMP_TV_SYNC_FRAMESYNC = 0,
	MMP_TV_SYNC_FIELDSYNC
} MMP_TV_SYNC_MODE;

/* HDMI Attribute */
typedef enum _MMP_HDMI_OUTPUT_MODE
{
    MMP_HDMI_OUTPUT_UNSUPPORT 			= 0,
    MMP_HDMI_OUTPUT_USERDEF 			= 0x7FFFFFFF,
    MMP_HDMI_OUTPUT_640X480P 			= 0x00000001,
    MMP_HDMI_OUTPUT_720X480P 			= 0x00000002,
    MMP_HDMI_OUTPUT_720X576P 			= 0x00000004,
    MMP_HDMI_OUTPUT_1280X720P 			= 0x00000008,
    MMP_HDMI_OUTPUT_1280X720P_50FPS 	= 0x00000010,
    MMP_HDMI_OUTPUT_1280X720P_100FPS 	= 0x00000011,
    MMP_HDMI_OUTPUT_1280X720P_120FPS 	= 0x00000012,
    MMP_HDMI_OUTPUT_1920X1080P 			= 0x00000020,
    MMP_HDMI_OUTPUT_1920X1080P_30FPS	= 0x00000040,
    MMP_HDMI_OUTPUT_1920X1080P_50FPS	= 0x00000050,
    MMP_HDMI_OUTPUT_1920X1080I 			= 0x00000080
} MMP_HDMI_OUTPUT_MODE;

typedef enum _MMP_HDMI_COLORMODE
{
    MMP_HDMI_COLORMODE_RGB888 = 0x00,
    MMP_HDMI_COLORMODE_RGB666,
    MMP_HDMI_COLORMODE_RGB565,
    MMP_HDMI_COLORMODE_RGB444,
    MMP_HDMI_COLORMODE_RGB333,
    MMP_HDMI_COLORMODE_RGB332,
    MMP_HDMI_COLORMODE_BGR888 = 0x08,
    MMP_HDMI_COLORMODE_BGR666,
    MMP_HDMI_COLORMODE_BGR565,
    MMP_HDMI_COLORMODE_BGR444,
    MMP_HDMI_COLORMODE_BGR333,
    MMP_HDMI_COLORMODE_BGR332,
    MMP_HDMI_COLORMODE_UY0VY1 = 0x20,
    MMP_HDMI_COLORMODE_VY0UY1,
    MMP_HDMI_COLORMODE_UY1VY0,
    MMP_HDMI_COLORMODE_VY1UY0,
    MMP_HDMI_COLORMODE_Y0UY1V,
    MMP_HDMI_COLORMODE_Y0VY1U,
    MMP_HDMI_COLORMODE_Y1UY0V,
    MMP_HDMI_COLORMODE_Y1VY0U
} MMP_HDMI_COLORMODE;

typedef enum _MMP_DDC_OPERATION_TYPE {
    MMP_DDC2B_PROTOCOL = 0,
    MMP_EDDC_PROTOCOL
} MMP_DDC_OPERATION_TYPE;

typedef enum _MMP_CCIR_TIMING_MODE
{
    MMP_CCIR_601_NTSC = 0,
    MMP_CCIR_601_PAL,
    MMP_CCIR_656_NTSC,
    MMP_CCIR_656_PAL,
    MMP_CCIR_CEA861_D
} MMP_CCIR_TIMING_MODE;

typedef enum _MMP_CCIR_COLORMODE
{
    MMP_CCIR656_YUV422_8BIT_UYVY = 0,
    MMP_CCIR656_YUV422_8BIT_VYUY,
    MMP_CCIR656_YUV422_8BIT_YUYV,
    MMP_CCIR656_YUV422_8BIT_YVYU
} MMP_CCIR_COLORMODE;

typedef enum _MMP_ASPECT_RATIO
{
    MMP_ASPECT_RATIO_UNSUPPORT = 0,
    MMP_ASPECT_RATIO_4_3,
    MMP_ASPECT_RATIO_3_2,
    MMP_ASPECT_RATIO_16_9,
    MMP_ASPECT_RATIO_16_10
} MMP_ASPECT_RATIO;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef MMP_BOOL MMP_DISPLAY_INIT_FUNC (MMP_BOOL bSoftReset);

typedef struct _MMP_DISPLAY_RECT {
    MMP_USHORT 					usLeft;
    MMP_USHORT 					usTop;
    MMP_USHORT 					usWidth;
    MMP_USHORT 					usHeight;
} MMP_DISPLAY_RECT;

typedef struct _MMP_DISPLAY_WIN_COLRMTX {
    MMP_SHORT          			sUVGainFactMtx[2][2];
    MMP_UBYTE          			ubRGBGAIN;
    MMP_SHORT          			ubRGBOFST;
} MMP_DISPLAY_WIN_COLRMTX;

typedef struct _MMP_DISPLAY_TV_GAMMA {
    MMP_USHORT 					usGamma0;
    MMP_USHORT 					usGamma1;
    MMP_USHORT 					usGamma2;
    MMP_USHORT 					usGamma3;
    MMP_USHORT 					usGamma4;
    MMP_USHORT 					usGamma5;
    MMP_USHORT 					usGamma6;
    MMP_USHORT 					usGamma7;
    MMP_USHORT 					usGamma8;
} MMP_DISPLAY_TV_GAMMA;

typedef struct _MMP_DISPLAY_WIN_ALPHA_ATTR
{
	MMP_DISPLAY_ALPHA_FMT	fmt;
	MMP_BYTE				ubAlphaWeight; // Only affect when fmt = MMP_DISPLAY_ALPHA_GLOBAL.
} MMP_DISPLAY_WIN_ALPHA_ATTR;

typedef struct _MMP_LCD_ATTR {
    MMP_DISPLAY_DEV_TYPE		lcdtype;		        ///< LCD type
    MMP_LCD_CS_SEL      		cssel;			        ///< LCD CS control signal connection
    MMP_DISPLAY_INIT_FUNC       *initialfx;		        ///< LCD related setting in AIT controller side
    MMP_DISPLAY_INIT_FUNC       *reinitialfx;	        ///< LCD related setting in AIT controller side
    MMP_USHORT          		usWidth;                ///< LCD total width (unit:pixel)
    MMP_USHORT          		usHeight;               ///< LCD total height (unit:pixel)
    MMP_LCD_COLORDEPTH			colordepth;             ///< LCD colordepth
    MMP_ULONG					ulBgColor;              ///< LCD background color, when no window is enabled in that pixel
    MMP_ULONG                   ulPanelXratio; 	        ///< LCD panel real width ratio
	MMP_ULONG                   ulPanelYratio;	        ///< LCD panel real height ratio
    MMP_BOOL            		bFLMType;               ///< LCD FLM Type
    MMP_BOOL            		bRotateVerticalLCD;     ///< LCD rotate vertical panel for use 
} MMP_LCD_ATTR;

typedef struct _MMP_TV_ATTR {
    MMP_TV_TYPE        			tvtype;
    MMP_USHORT					usStartX;				///< TV display offset X, start from left of TV view region  
    MMP_USHORT 					usStartY;				///< TV display offset Y, start from top of TV view region  
    MMP_USHORT 					usDisplayWidth;			///< Display width 
    MMP_USHORT 					usDisplayHeight;		///< Display height
    MMP_ULONG  					ulDspyBgColor;			///< Display background color, when no window is enabled in that pixel
    MMP_UBYTE  					ubTvBgYColor;			///< TV background Y color, outside usDisplayWidth/usDisplayHeight 
    MMP_UBYTE 	 				ubTvBgUColor;			///< TV background U color, outside usDisplayWidth/usDisplayHeight 
    MMP_UBYTE  					ubTvBgVColor;			///< TV background V color, outside usDisplayWidth/usDisplayHeight
} MMP_TV_ATTR;

typedef struct _MMP_HDMI_ATTR {
    MMP_HDMI_COLORMODE  		ubColorType;
    MMP_USHORT 					usDisplayWidth;
    MMP_USHORT 					usDisplayHeight;
    MMP_ULONG  					ulDspyBgColor;
    MMP_HDMI_OUTPUT_MODE  		ubOutputMode;
} MMP_HDMI_ATTR;

typedef struct _MMP_CCIR_ATTR {
    MMP_CCIR_TIMING_MODE        ubCCIRMode;
    MMP_CCIR_COLORMODE			ubColorType;
    MMP_USHORT 					usDisplayWidth;
    MMP_USHORT 					usDisplayHeight;
    MMP_UBYTE 					ubClockDiv;
    MMP_BOOL 					ubHSyncClkInv;
    MMP_BOOL 					ubVSyncClkInv;
} MMP_CCIR_ATTR;

typedef struct _MMP_DISPLAY_WIN_PALETTE
{
	MMP_ULONG					ulPaletteSize;
	MMP_ULONG					ulPaletteAddr;
} MMP_DISPLAY_WIN_PALETTE;

typedef struct _MMP_DISPLAY_WIN_ATTR {
	/**/
    MMP_USHORT          		usWidth;
    MMP_USHORT          		usHeight;
    MMP_USHORT          		usLineOffset;
	/**/
	MMP_DISPLAY_WIN_COLOR		ColorFmt;
	MMP_DISPLAY_WIN_COLORDEPTH	colordepth;
	/**/
    MMP_ULONG           		ulBaseAddr;
    MMP_ULONG           		ulBaseUAddr;
    MMP_ULONG          	 		ulBaseVAddr;
    MMP_DISPLAY_CONTROLLER  	bindController;
	/**/
	MMP_BOOL					bTransColorEn;
	MMP_ULONG					ulTransColor;
	/**/
	MMP_DISPLAY_WIN_ALPHA_ATTR	AlphaAttr;
	/*Palette*/
	MMP_DISPLAY_WIN_PALETTE		Palette;
	/**/
    MMP_BOOL                    bWindowOn;
} MMP_DISPLAY_WIN_ATTR;

typedef struct _MMP_DISPLAY_DISP_ATTR {
    MMP_USHORT                  usStartX;           // Desired start offset X within the window buffer (Rotated/Mirrored buffer domain)
    MMP_USHORT                  usStartY;           // Desired start offset Y within the window buffer (Rotated/Mirrored buffer domain)
    MMP_USHORT                  usDisplayWidth;     // Desired display width within the window buffer  (Rotated/Mirrored buffer domain)
    MMP_USHORT                  usDisplayHeight;    // Desired display height within the window buffer (Rotated/Mirrored buffer domain)
    MMP_USHORT                  usDisplayOffsetX;   // Window offset X relative to device boundary
    MMP_USHORT                  usDisplayOffsetY;   // Window offset Y relative to device boundary
    MMP_BOOL                    bMirror;
    MMP_DISPLAY_ROTATE_TYPE    	rotatetype;
} MMP_DISPLAY_DISP_ATTR;

#endif // _MMP_DISPLAY_INC_H_
