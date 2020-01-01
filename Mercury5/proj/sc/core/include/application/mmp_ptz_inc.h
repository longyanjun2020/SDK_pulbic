//==============================================================================
//
//  File        : mmp_ptz_inc.h
//  Description : INCLUDE File for the Firmware PTZ Control driver function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_PTZ_INC_H_
#define _MMP_PTZ_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_scal_inc.h"

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_PTZ_ZOOM_INC {
    MMP_PTZ_ZOOM_INC_IN  = 1,
    MMP_PTZ_ZOOM_INC_OUT = -1
} MMP_PTZ_ZOOM_INC;

typedef enum _MMP_PTZ_ZOOM_DIR
{
    MMP_PTZ_ZOOMIN = 0,
	MMP_PTZ_ZOOMOUT,
	MMP_PTZ_ZOOMSTOP
} MMP_PTZ_ZOOM_DIR;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMP_PTZ_SCAL_INFO {
    MMP_SCAL_FIT_RANGE		sFitRange;
    MMP_SCAL_GRAB_CTRL 		sGrabCtlBase;
    MMP_SCAL_GRAB_CTRL 		sGrabCtlCur;
    
    MMP_USHORT 				usMaxZoomRatio;
    MMP_USHORT 				usMaxZoomSteps;
    MMP_USHORT 				usCurZoomStep;

    MMP_SHORT 				sMaxPanSteps;
    MMP_SHORT 				sMinPanSteps;
    MMP_SHORT 				sCurPanStep;

    MMP_SHORT 				sMaxTiltSteps;
    MMP_SHORT 				sMinTiltSteps;
    MMP_SHORT 				sCurTiltStep;
} MMP_PTZ_SCAL_INFO;

typedef struct _MMP_PTZ_STEP_INFO {
	MMP_SHORT				sZoomDir;
    MMP_USHORT 				usCurZoomStep;
    MMP_SHORT 				sCurPanStep;
    MMP_SHORT 				sCurTiltStep;
    MMP_USHORT 				usTarZoomStep;
    MMP_SHORT 				sTarPanStep;
    MMP_SHORT 				sTarTiltStep;
} MMP_PTZ_STEP_INFO;

#endif //_MMP_PTZ_INC_H_