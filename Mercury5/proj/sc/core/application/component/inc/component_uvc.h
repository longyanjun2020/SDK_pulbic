//------------------------------------------------------------------------------
//
//  File        : component_uvc.h
//  Description : Header file of UVC configuration
//  Author      :
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_UVC_H_
#define _COMPONENT_UVC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_UVC_MAX_NUM   (UVC_COMP_USAGE_NUM)

#define UVC_COMP_BUF_SIZE_YUV422(W, H)  (W) * (H) * 2

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    UVC_COMP_FCAM_PREVIEW = 0,
    UVC_COMP_RCAM_PREVIEW,
    UVC_COMP_USAGE_NUM
} UVC_COMP_USAGE;

typedef enum
{
    UVC_COMP_FORMAT_YUV422 = 0,
    UVC_COMP_FORMAT_YUV420,
    UVC_COMP_FORMAT_MJPEG,
    UVC_COMP_FORMAT_H264,
    UVC_COMP_FORMAT_NUM
} UVC_COMP_FORMAT;

typedef enum
{
    UVC_COMP_PARAM_RESOL = 0,
    UVC_COMP_PARAM_FORMAT,
    UVC_COMP_PARAM_BUF_COUNT,
    UVC_COMP_PARAM_BUF_SIZE,
    UVC_COMP_PARAM_MAX
} UVC_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _UVC_COMP_RECT
{
    MMP_ULONG           ulW;
    MMP_ULONG           ulH;
} UVC_COMP_RESOL;

typedef struct _MMP_COMPONENT_HANDLER_UVC
{
    UVC_COMP_RESOL      stResol;
    UVC_COMP_FORMAT     eColorFormat;
} MMP_COMPONENT_HANDLER_UVC;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_UVC[];

extern MMP_COMPONENT_MEMORY_INFO Component_UVC_Memory[];
extern MMP_COMPONENT_HANDLER_UVC Component_UVC_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_UVC_SetParameter(void *handler, int type, void* pParam);

#endif // _COMPONENT_UVC_H_

