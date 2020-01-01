//------------------------------------------------------------------------------
//
//  File        : component_jpemgr.h
//  Description : Header file of JPE MGR configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_JPE_MGR_H_
#define _COMPONENT_JPE_MGR_H_

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

#define MAX_JPEMGR_COMP_NUM    JPEMGR_COMP_USAGE_NUM

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    JPEMGR_COMP_PRM_MJPEG = 0,
    JPEMGR_COMP_SCD_MJPEG,
    JPEMGR_COMP_TRD_MJPEG,
    JPEMGR_COMP_PRM_PRIMARY,
    JPEMGR_COMP_SCD_PRIMARY,
    JPEMGR_COMP_TRD_PRIMARY,
    JPEMGR_COMP_PRM_THUMB,
    JPEMGR_COMP_SCD_THUMB,
    JPEMGR_COMP_TRD_THUMB,
    JPEMGR_COMP_PRM_VR_THUMB,
    JPEMGR_COMP_SCD_VR_THUMB,
    JPEMGR_COMP_TRD_VR_THUMB,
    JPEMGR_COMP_USAGE_NUM
} JPEMGR_COMP_USAGE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_JPE_MGR
{
    MMP_UBYTE   ubUseType;
    MMP_UBYTE   ubShotMode;
} MMP_COMPONENT_HANDLER_JPE_MGR;

typedef struct _JPE_MGR_COMP_EMPTY_BUF_INFO // Sync with JPGENC_DONE_ATTR
{
    MMP_ULONG   ulBSSize;       // Encoded Bitstream Size
    MMP_ULONG   ulTotalSize;    // Encoded Total Size
    MMP_USHORT  usEncId;        // Encode Instance ID
    MMP_USHORT  usEncType;      // Encode Type
    MMP_USHORT  usEncDoneMode;  // Encode Done Mode
    MMP_ULONG   ulEncBufAddr;   // Encode Buffer Address
} JPE_MGR_COMP_EMPTY_BUF_INFO;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_JPEMGR[];

extern MMP_COMPONENT_MEMORY_INFO Component_JPEMGR_Memory[];
extern MMP_COMPONENT_HANDLER_JPE_MGR Component_JPEMGR_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

#endif // _COMPONENT_JPE_MGR_H_

