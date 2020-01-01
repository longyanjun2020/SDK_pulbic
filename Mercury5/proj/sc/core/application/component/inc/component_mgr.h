//------------------------------------------------------------------------------
//
//  File        : component_mgr.h
//  Description : Header file of MGR configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_MGR_H_
#define _COMPONENT_MGR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "mmp_vidrec_inc.h"
#include "mmpf_3gpmgr.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_MGR_COMP_NUM    MGR_COMP_USAGE_NUM

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    MGR_COMP_PRM_RECD = 0,
    MGR_COMP_SCD_RECD,
    MGR_COMP_TRD_RECD,
    MGR_COMP_UVC_RECD,
    MGR_COMP_PRM_STREAM,
    MGR_COMP_SCD_STREAM,
    MGR_COMP_USAGE_NUM
} MGR_COMP_USAGE;

typedef enum
{
    MGR_COMP_PARAM_MULTI_TRACK = 0,
    MGR_COMP_PARAM_BUF_COUNT,
    MGR_COMP_PARAM_BUF_SIZE,
    MGR_COMP_PARAM_MAX
} MGR_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_MGR
{
    MMP_UBYTE           ubUseType;
    MMP_USHORT          usStreamType;
    MMPF_VID_MGR_INFO   *pContainer;
    MMP_BOOL            bMultiTrack;
    MMP_BOOL            bEncodeEn;
} MMP_COMPONENT_HANDLER_MGR;

typedef struct _MGR_COMP_EMPTY_BUF_INFO // Should Sync with VIDENC_DONE_ATTR
{
    MMP_ULONG           ulFrameType;
    MMP_ULONG           ulFrameSize;
    MMP_ULONG           ulFrameTime;
} MGR_COMP_EMPTY_BUF_INFO;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_MGR[];

extern MMP_COMPONENT_MEMORY_INFO Component_MGR_Memory[];
extern MMP_COMPONENT_HANDLER_MGR Component_MGR_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_MGR_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MGR_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_MGR_H_

