/**
 @file ahc_ptz.h
 @brief Header File for the ahc ptz(pan tilt zoom)API.
 @author 
 @version 1.0
*/

#ifndef _AHC_PTZ_H_
#define _AHC_PTZ_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_motor.h"
#include "ahc_capture.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL AHC_SetPreviewZoomConfig(UINT16 bySteps, UINT8 byMaxRatio);
AHC_BOOL AHC_SetPreviewZoom(AHC_CAPTURE_MODE CaptureMode, AHC_ZOOM_DIRECTION byDirection, UINT8 bySteps);
AHC_BOOL AHC_PlaybackZoom(UINT16 uwStartX, UINT16 uwStartY, UINT16 uwWidth, UINT16 uwHeight);


#endif // _AHC_PTZ_H_
