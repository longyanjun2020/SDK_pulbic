//------------------------------------------------------------------------------
//
//  File        : component_raws.h
//  Description : Header file of Raw configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_RAWS_H_
#define _COMPONENT_RAWS_H_

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

#define RAWS_COMP_BUF_COUNT    (2)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    RAWS_COMP_SIG_TYPE_INTERLACE = 0,
    RAWS_COMP_SIG_TYPE_PROGRESSIVE,
    RAWS_COMP_SIG_TYPE_NUM
} RAWS_COMP_SIG_TYPE;

typedef enum
{
    RAWS_COMP_CH0 = 0,
    RAWS_COMP_CH1,
    RAWS_COMP_CH2,
    RAWS_COMP_USAGE_NUM
} RAWS_COMP_USAGE;

typedef enum
{
    RAWS_COMP_PARAM_WIDTH = 0,
    RAWS_COMP_PARAM_HEIGHT,
    RAWS_COMP_PARAM_SNR_SEL,
    RAWS_COMP_PARAM_SIGNAL_TYPE,
    RAWS_COMP_PARAM_BUF_COUNT,
    RAWS_COMP_PARAM_BUF_SIZE,
    RAWS_COMP_PARAM_MAX
} RAWS_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_RAW
{
    MMP_USHORT  usWidth;
    MMP_USHORT  usHeight;
    MMP_UBYTE   ubSnrSel;
    MMP_UBYTE   ubSigType;
    MMP_USHORT  usDropFrameCnt;
} MMP_COMPONENT_HANDLER_RAW;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_RawS[];

extern MMP_COMPONENT_HANDLER_RAW Component_RAWS_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_RAWS_Memory[];

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR Component_RawS_InitDevice(void *handler);
MMP_ERR Component_RawS_Ch0_OpenDevice(void *handler);
MMP_ERR Component_RawS_Ch1_OpenDevice(void *handler);
MMP_ERR Component_RawS_Ch2_OpenDevice(void *handler);
MMP_ERR Component_RawS_UnInitDevice(void *handler);
MMP_ERR Component_RawS_CloseDevice(void *handler);
MMP_ERR Component_RawS_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_RawS_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_RAWS_H_

