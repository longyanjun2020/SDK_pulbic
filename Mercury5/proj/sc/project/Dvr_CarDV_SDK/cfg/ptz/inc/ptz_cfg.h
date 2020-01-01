//------------------------------------------------------------------------------
//
//  File        : ptz_cfg.h
//  Description : Header file of Pan/Tilt/Zoom configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _PTZ_CFG_H_
#define _PTZ_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    MMP_BOOL	bEnable; // If set Enable, use raw path.
    MMP_USHORT	usMaxZoomRatio;
    MMP_USHORT	usMaxZoomSteps;
    MMP_SHORT	sMaxPanSteps;
    MMP_SHORT	sMinPanSteps;
    MMP_SHORT	sMaxTiltSteps;
    MMP_SHORT	sMinTiltSteps;
} PTZ_CFG;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern PTZ_CFG gsVidPtzCfg, gsDscPtzCfg;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_BOOL MMP_IsVidPtzEnable(void);
MMP_BOOL MMP_IsDscPtzEnable(void);

#endif // _PTZ_CFG_H_

