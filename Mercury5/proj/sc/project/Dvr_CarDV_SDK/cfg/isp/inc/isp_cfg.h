//------------------------------------------------------------------------------
//
//  File        : isp_cfg.h
//  Description :
//  Author      : Lucas
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _ISP_CFG_H_
#define _ISP_CFG_H_

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

#define CONTRAST_CENTER     (0)       //Range -128~127
#define SHARPNESS_CENTER    (0)       //Range -128~127
#define GAMMA_CENTER        (0)       //Range -128~127
#define SATURATE_CENTER     (0)       //Range -128~127

#define MENU_MANUAL_CONTRAST_MIN                    (-100)
#define MENU_MANUAL_CONTRAST_MAX                    (100)
#define MENU_MANUAL_CONTRAST_STEP                   (10)

#define MENU_MANUAL_SATURATION_MIN                  (-100)
#define MENU_MANUAL_SATURATION_MAX                  (100)
#define MENU_MANUAL_SATURATION_STEP                 (10)

#define MENU_MANUAL_SHARPNESS_MIN                   (-100)
#define MENU_MANUAL_SHARPNESS_MAX                   (100)
#define MENU_MANUAL_SHARPNESS_STEP                  (10)

#define MENU_MANUAL_GAMMA_MIN                       (-100)
#define MENU_MANUAL_GAMMA_MAX                       (100)
#define MENU_MANUAL_GAMMA_STEP                      (10)

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_ULONG gISPCfgFramePeriodTotal[];
extern MMP_ULONG gISPCfgFrameCountDoAe[];
extern MMP_ULONG gISPCfgFrameCountDoAwb[];
extern MMP_ULONG gISPCfgFrameCountDoIq[];
extern MMP_ULONG gISPCfgFrameCountSetShutter[];
extern MMP_ULONG gISPCfgFrameCountSetGain[];
extern MMP_ULONG gISPCfgFrameCountShadowFrameStart[];
extern MMP_ULONG gISPCfgFrameCountShadowFrameEnd[];

#endif
