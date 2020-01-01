//==============================================================================
//
//  File        : ZoomContorl.h
//  Description : INCLUDE File for the Zoom Control function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _ZOOMCONTROL_H_
#define _ZOOMCONTROL_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_sensor.h"
#include "ahc_general.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MAX_DIGITAL_ZOOMSTEP         (25)

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

UINT16 		ZoomCtrl_GetVideoDigitalZoomLevel(void);
UINT16 		ZoomCtrl_GetVideoDigitalZoomMax(void);
UINT16 		ZoomCtrl_GetStillDigitalZoomLevel(void);
UINT16 		ZoomCtrl_GetStillDigitalZoomMax(void);
AHC_BOOL 	ZoomCtrl_DigitalZoom(AHC_CAPTURE_MODE iMode, AHC_ZOOM_DIRECTION bZoomDir);
AHC_BOOL 	ZoomCtrl_GetDigitalZoomRatio(UINT32 *ZoomRatio);

#endif //_ZOOMCONTROL_H_
