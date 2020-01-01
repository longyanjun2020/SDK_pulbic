//==============================================================================
//
//  File        : mmp_graphics_inc.h
//  Description : INCLUDE File for the Firmware Graphic Driver.
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_GRAPHICS_INC_H_
#define _MMP_GRAPHICS_INC_H_

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_GRAPHICS_COLORDEPTH
{
    MMP_GRAPHICS_COLORDEPTH_8 		            = 1,
    MMP_GRAPHICS_COLORDEPTH_16 		            = 2,
    MMP_GRAPHICS_COLORDEPTH_24 		            = 3,
    MMP_GRAPHICS_COLORDEPTH_32 		            = 4,
    MMP_GRAPHICS_COLORDEPTH_YUV422_UYVY 	    = 5,
    MMP_GRAPHICS_COLORDEPTH_YUV422_VYUY         = 6,
    MMP_GRAPHICS_COLORDEPTH_YUV422_YUYV         = 7,
    MMP_GRAPHICS_COLORDEPTH_YUV422_YVYU         = 8,
	MMP_GRAPHICS_COLORDEPTH_YUV420 	            = 9,
	MMP_GRAPHICS_COLORDEPTH_YUV420_INTERLEAVE   = 10,
    MMP_GRAPHICS_COLORDEPTH_ARGB3454            = 11,
    MMP_GRAPHICS_COLORDEPTH_ARGB4444            = 12,
    MMP_GRAPHICS_COLORDEPTH_UNSUPPORT
} MMP_GRAPHICS_COLORDEPTH;

typedef enum _MMP_GRAPHICS_ROTATE_TYPE
{
    MMP_GRAPHICS_ROTATE_NO_ROTATE = 0,
    MMP_GRAPHICS_ROTATE_RIGHT_90,
    MMP_GRAPHICS_ROTATE_RIGHT_180,
    MMP_GRAPHICS_ROTATE_RIGHT_270
} MMP_GRAPHICS_ROTATE_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_GRAPHICS_BUF_ATTR {
    MMP_USHORT                      usWidth;
    MMP_USHORT                      usHeight;
    MMP_USHORT                      usLineOffset;
    MMP_GRAPHICS_COLORDEPTH        	colordepth;
	MMP_ULONG                       ulBaseAddr;
    MMP_ULONG                       ulBaseUAddr;
    MMP_ULONG                       ulBaseVAddr;
} MMP_GRAPHICS_BUF_ATTR;

typedef struct _MMP_GRAPHICS_RECT {
    MMP_USHORT          			usLeft;
    MMP_USHORT          			usTop;
    MMP_USHORT          			usWidth;
    MMP_USHORT          			usHeight;
} MMP_GRAPHICS_RECT;

typedef void GraphicScaleCallBackFunc(void);

#endif // _MMP_GRAPHICS_INC_H_
