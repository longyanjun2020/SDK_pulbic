

#ifndef _COMPONENT_PIP_H_
#define _COMPONENT_PIP_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO
//
//==============================================================================

#define COMPONENT_PIP_MAX_NUM   PIP_COMP_USAGE_NUM

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    PIP_COMP_PIP_PREVIEW = 0,
    PIP_COMP_PLAYBACK,
    PIP_COMP_USAGE_NUM
} PIP_COMP_USAGE;

typedef enum
{
    PIP_COMP_COLOR_FMT_RGB565 = 0,
    PIP_COMP_COLOR_FMT_BGR565,
    PIP_COMP_COLOR_FMT_ARGB8888,
    PIP_COMP_COLOR_FMT_ABGR8888,
    PIP_COMP_COLOR_FMT_YUYV422,
    PIP_COMP_COLOR_FMT_YVYU422,
    PIP_COMP_COLOR_FMT_UYVY422,
    PIP_COMP_COLOR_FMT_VYUY422,
    PIP_COMP_COLOR_FMT_UNSUPPORT
} PIP_COMP_COLOR_FMT;

typedef enum
{
    PIP_COMP_ALPHA_FMT_GLOBAL = 0,
    PIP_COMP_ALPHA_FMT_PIXEL,
    PIP_COMP_ALPHA_FMT_UNSUPPORT
} PIP_COMP_ALPHA_FMT;

typedef enum
{
    PIP_COMP_PARAM_FG_RECT = 0,
    PIP_COMP_PARAM_BG_RECT,
    PIP_COMP_PARAM_COLOR_FMT,
    PIP_COMP_PARAM_ALPHA_ATTR,
    PIP_COMP_PARAM_BUF_COUNT,
    PIP_COMP_PARAM_BUF_SIZE,
    PIP_COMP_PARAM_H_MIRROR,
    PIP_COMP_PARAM_V_FLIP,
    PIP_COMP_PARAM_MAX
} PIP_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _PIP_COMP_RECT
{
    MMP_ULONG                   ulX;
    MMP_ULONG                   ulY;
    MMP_ULONG                   ulW;
    MMP_ULONG                   ulH;
} PIP_COMP_RECT;

typedef struct _PIP_COMP_ALPHA_ATTR
{
    PIP_COMP_ALPHA_FMT          AlphaFmt;
    MMP_UBYTE                   Weight;
} PIP_COMP_ALPHA_ATTR;

typedef struct _MMP_COMPONENT_HANDLER_PIP
{
    PIP_COMP_RECT               stBgRect; // Background
    PIP_COMP_RECT               stFgRect; // Foreground
    PIP_COMP_COLOR_FMT          ColorFmt;
    PIP_COMP_ALPHA_ATTR         AlphaAttr;
    MMP_BOOL                    bMirror;
    MMP_BOOL                    bFlip;
    MMP_BYTE                    g_DropFrame;
} MMP_COMPONENT_HANDLER_PIP;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_PIP[];

extern MMP_COMPONENT_HANDLER_PIP Component_PIP_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_PIP_Memory[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_PIP_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_PIP_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_PIP_H_

