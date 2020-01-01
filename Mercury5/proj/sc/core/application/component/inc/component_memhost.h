//------------------------------------------------------------------------------
//
//  File        : component_memhost.h
//  Description : Header file of Sensor configuration
//  Author      : Mark
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_MEMHOST_H_
#define _COMPONENT_MEMHOST_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_MEMHOST_COMP_NUM    MEMHOST_COMP_USAGE_NUM

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    MEMHOST_COMP_BROWSER_THUMB = 0,
    MEMHOST_COMP_FCAM_VR_THUMB,
    MEMHOST_COMP_RCAM_VR_THUMB,
    MEMHOST_COMP_USAGE_NUM
} MEMHOST_COMP_USAGE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_MEMHOST
{
    MMP_UBYTE   ubUseType;
    MMP_BOOL    bEnableHandler;
} MMP_COMPONENT_HANDLER_MEMHOST;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_MemHost[];

extern MMP_COMPONENT_HANDLER_MEMHOST Component_MemHost_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_MemHost_Memory[];

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR Component_MEMHOST_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MEMHOST_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_MEMHOST_H_

