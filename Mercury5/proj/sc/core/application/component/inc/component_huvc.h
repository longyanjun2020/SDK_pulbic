//------------------------------------------------------------------------------
//
//  File        : component_huvc.h
//  Description : Header file of Sensor configuration
//  Author      : Titan
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_HUVC_H_
#define _COMPONENT_HUVC_H_

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

#define MAX_UVC_COMP_NUM    UVC_COMP_USAGE_NUM

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    HUVC_COMP_UVC = 0,
    HUVC_COMP_USAGE_NUM
} HUVC_COMP_USAGE;

typedef enum
{
    HUVC_COMP_PARAM_USB_MODE = 0,
    HUVC_COMP_PARAM_ENCODE_RES,
    HUVC_COMP_PARAM_BUF_SIZE,
    HUVC_COMP_PARAM_BUF_NUM,
    HUVC_COMP_PARAM_RUNTIME_WBUF_AVAILABLE,
    HUVC_COMP_PARAM_MAX
} HUVC_COMP_PARAM;

typedef enum
{
    HUVC_COMP_USB_MODE_ISO = 0,
    HUVC_COMP_USB_MODE_BULK,
    HUVC_COMP_USB_MODE_NUM
} HUVC_COMP_MODE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _HUVC_COMP_RESOL
{
    MMP_ULONG       ulW;
    MMP_ULONG       ulH;
} HUVC_COMP_RESOL;

typedef struct _MMP_COMPONENT_HANDLER_HUVC
{
    MMP_UBYTE       ubUsbMode;
    MMP_UBYTE       uFrameDropThreshold;
    HUVC_COMP_RESOL stEncWH;
} MMP_COMPONENT_HANDLER_HUVC;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_HUVC[];

extern MMP_COMPONENT_HANDLER_HUVC Component_HUVC_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_HUVC_Memory[];

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR Component_HUVC_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_HUVC_GetParam(void *handler, int type, void* pParam);

MMP_BOOL Component_HUVC_CheckRdyStatus(void);

#endif // _COMPONENT_HUVC_H_
