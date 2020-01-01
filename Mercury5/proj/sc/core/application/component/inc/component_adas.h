//------------------------------------------------------------------------------
//
//  File        : component_adas.h
//  Description : Header file of adas configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_ADAS_H_
#define _COMPONENT_ADAS_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "adas.h"
#include "ldws_cfg.h"
#include "mdtc_cfg.h"
#include "ahc_common.h"
#include "MenuSetting.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _ADAS_COMP_USAGE {
    ADAS_COMPONENT_STD,//432x240
    ADAS_COMPONENT_MAX
} ADAS_COMP_USAGE;

typedef enum _MDTC_COMP_USAGE {
    MDTC_COMPONENT_STD,
    MDTC_COMPONENT_MAX
} MDTC_COMP_USAGE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPF_ADAS_INBUF_INFO
{
    MMP_ULONG   ulInBufAddr;
    MMP_ULONG   ulInBufSize;
    MMP_UBYTE   ubColorFormat;
} MMP_ADAS_INBUF_INFO;

typedef struct _MMP_COMPONENT_HANDLER_ADAS
{
    COMMON_LDWS_EN bLdwsEnable;
    COMMON_FCWS_EN bFcwsEnable;
    COMMON_SAG_EN bSagEnable;
} MMP_COMPONENT_HANDLER_ADAS;

typedef struct _MMPF_MDTC_INBUF_INFO
{
    MMP_ULONG   ulInBufAddr;
    MMP_ULONG   ulInBufSize;
    MMP_UBYTE   ubColorFormat;
} MMP_MDTC_INBUF_INFO;

typedef struct _MMP_COMPONENT_HANDLER_MDTC
{
    UINT8   bParkingMode;
    UINT8   uiMotionDtcSensitivity;
    UINT8   uiVMDRecTime;
} MMP_COMPONENT_HANDLER_MDTC;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_Adas[];
extern MMP_COMPONENT_BASE Component_Mdtc[];

extern MMP_COMPONENT_HANDLER_ADAS Component_Adas_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_Adas_Memory[];
extern MMP_COMPONENT_HANDLER_MDTC Component_Mdtc_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_Mdtc_Memory[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

#endif // _COMPONENT_ADAS_H_


