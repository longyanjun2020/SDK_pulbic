//------------------------------------------------------------------------------
//
//  File        : component_display.h
//  Description : Header file of display configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_DISPLAY_H_
#define _COMPONENT_DISPLAY_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "mmp_display_inc.h"
#include "mmp_scal_inc.h"
#include "lcd_common.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    DISPLAY_COMP_PARAM_IN_RECT = 0,
    DISPLAY_COMP_PARAM_CROP_RECT,
    DISPLAY_COMP_PARAM_OUT_RECT,
    DISPLAY_COMP_PARAM_BK_COLOR_RECT,
    DISPLAY_COMP_PARAM_COLOR_FORMAT,
    DISPLAY_COMP_PARAM_BUF_COUNT,
    DISPLAY_COMP_PARAM_BUF_SIZE,
    DISPLAY_COMP_PARAM_SCL_CFG,
    DISPLAY_COMP_PARAM_MAX
} DISPLAY_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _DISPLAY_COMP_RECT
{
    MMP_ULONG               ulX;
    MMP_ULONG               ulY;
    MMP_ULONG               ulW;
    MMP_ULONG               ulH;
} DISPLAY_COMP_RECT;

typedef struct _DISPLAY_COMP_SCL_CFG
{
    MMP_BOOL                bSclHBypass;
    MMP_BOOL                bSclVBypass;
} DISPLAY_COMP_SCL_CFG;

typedef struct _MMP_COMPONENT_HANDLER_DISPLAY
{
    MMP_SCAL_FIT_MODE       eFitMode;
    DISPLAY_COMP_RECT       stInRect;
    DISPLAY_COMP_RECT       stCropRect;
    DISPLAY_COMP_RECT       stOutRect;
    DISPLAY_COMP_RECT       stBkColRect;
    MMP_BOOL                bMirror;
    MMP_DISPLAY_COLORMODE   eColorFormat;
    DISPLAY_COMP_SCL_CFG    stSclCfg;
} MMP_COMPONENT_HANDLER_DISPLAY;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_Display;

extern MMP_COMPONENT_MEMORY_INFO Component_Display_Memory[];
extern MMP_COMPONENT_HANDLER_DISPLAY Component_Display_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_Display_SetParameter(void *handler, int type, void* pParam);

#endif // _COMPONENT_DISPLAY_H_

