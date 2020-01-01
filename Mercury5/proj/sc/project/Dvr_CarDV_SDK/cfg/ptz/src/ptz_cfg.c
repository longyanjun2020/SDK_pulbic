//------------------------------------------------------------------------------
//
//  File        : ptz_cfg.c
//  Description : Source file of Pan/Tilt/Zoom configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "Customer_config.h"
#include "ptz_cfg.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Configure of Ptz
 */
PTZ_CFG gsVidPtzCfg = {
#if 0//(VIDEO_DIGIT_ZOOM_EN == 1) //TBD
    MMP_TRUE, 	// bEnable
#else
    MMP_FALSE, 	// bEnable
#endif
    8/*VIDEO_DIGIT_ZOOM_RATIO_MAX*/,	// usMaxZoomRatio
    400,     	// usMaxZoomSteps
    200,    	// sMaxPanSteps
    -200,   	// sMinPanSteps
    200,		// sMaxTiltSteps
	-200		// sMinTiltSteps
};

PTZ_CFG gsDscPtzCfg = {
#if 0//(DSC_DIGIT_ZOOM_ENABLE == 1)
    MMP_TRUE, 	// bEnable
#else
    MMP_FALSE, 	// bEnable
#endif
    4/*DSC_DIGIT_ZOOM_RATIO_MAX*/,	// usMaxZoomRatio
    400,     	// usMaxZoomSteps
    200,    	// sMaxPanSteps
    -200,   	// sMinPanSteps
    200,		// sMaxTiltSteps
	-200		// sMinTiltSteps
};

MMP_BOOL MMP_IsVidPtzEnable(void)
{
    return gsVidPtzCfg.bEnable;
}

MMP_BOOL MMP_IsDscPtzEnable(void)
{
    return gsDscPtzCfg.bEnable;
}

