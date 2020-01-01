//==============================================================================
//
//  File        : ahc_motor.h
//  Description : INCLUDE File for the AHC Motor control function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MOTOR_H_
#define _AHC_MOTOR_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
//#include "ahc_general.h"

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _AHC_SENSOR_OPT_ZOOM_INDEX
{
    OPT_ZOOM_1_00X,
    OPT_ZOOM_1_25X,
    OPT_ZOOM_1_50X,
    OPT_ZOOM_1_75X,
    OPT_ZOOM_2_00X,
    OPT_ZOOM_2_25X,
    OPT_ZOOM_2_50X,
    OPT_ZOOM_3_00X,
    OPT_ZOOM_3_50X,
    OPT_ZOOM_4_00X,
    OPT_ZOOM_4_50X,
    OPT_ZOOM_5_00X,
	OPT_ZOOM_MAX
} AHC_SENSOR_OPT_ZOOM_INDEX;

typedef enum _AHC_OPTICALZOOM_STATUS
{
    OPT_ZOOM_IDLE,
    OPT_ZOOM_BUSY = 1
}AHC_OPTICALZOOM_STATUS;

typedef enum _AHC_ZOOM_DIRECTION
{
	AHC_SENSOR_ZOOM_IN = 0,
	AHC_SENSOR_ZOOM_OUT,
	AHC_SENSOR_ZOOM_STOP
} AHC_ZOOM_DIRECTION;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
 
AHC_BOOL AHC_GetOptocalZoomStatus( UINT8 *pwStatus );
AHC_BOOL AHC_SetOptocalZoom(AHC_ZOOM_DIRECTION byDirection);
AHC_BOOL AHC_SetOptocalZoomPos(UINT16 usPosIndex);
AHC_BOOL AHC_GetOptocalZoomPos(UINT16 *usPosIndex);
AHC_BOOL AHC_SetFocusPos(void);
AHC_BOOL AHC_GetFocusPos(UINT8 *bySteps);
AHC_BOOL AHC_SetOptocalZoomStop(void);
AHC_BOOL AHC_MotorParking(UINT uiArg);

#endif  //_AHC_MOTOR_H_