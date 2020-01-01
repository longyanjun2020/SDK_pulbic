//------------------------------------------------------------------------------
//
//  File        : isp_cfg.c
//  Description : Source file of isp configuration
//  Author      : Andy Liu
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "isp_cfg.h"

#define MAX_SUPPORT_SENSOR_ISP3A_NUM     4

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
MMP_ULONG gISPCfgFramePeriodTotal[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {0, 0, 0, 0};
MMP_ULONG gISPCfgFrameCountDoAe[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {0, 0, 0, 0};
MMP_ULONG gISPCfgFrameCountDoAwb[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {0, 0, 0, 0};
MMP_ULONG gISPCfgFrameCountDoIq[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {1, 1, 1, 1};
MMP_ULONG gISPCfgFrameCountSetShutter[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {0, 0, 0, 0};
MMP_ULONG gISPCfgFrameCountSetGain[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {0, 0, 0, 0};
MMP_ULONG gISPCfgFrameCountShadowFrameStart[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {1, 1, 1, 1};
MMP_ULONG gISPCfgFrameCountShadowFrameEnd[MAX_SUPPORT_SENSOR_ISP3A_NUM] = {1, 1, 1, 1};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
