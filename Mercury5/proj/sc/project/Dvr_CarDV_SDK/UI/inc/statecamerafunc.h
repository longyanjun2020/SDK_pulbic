//==============================================================================
//
//  File        : statecamerafunc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATECAMERAFUNC_H_
#define _STATECAMERAFUNC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "MenuCommon.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/

void 		StateCaptureHDMIMode( UINT32 ulEvent );
void 		StateCaptureTVMode( UINT32 ulEvent );
UINT32      StateCaptureModeHnadler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

AHC_BOOL 	CaptureMode_PreviewUpdate(void);
AHC_BOOL 	CaptureMode_Start(void);
UINT32 		CaptureFunc_GetRemainCaptureNum(void);
UINT16 		CaptureFunc_GetSelfTime(void);
AHC_BOOL    CaptureFunc_PresetSensorMode(IMAGESIZE_SETTING ubResolution);
AHC_BOOL 	CaptureFunc_SetResolution(IMAGESIZE_SETTING ubResolution, AHC_BOOL bSetOnly);
AHC_BOOL 	CaptureFunc_CheckMemSizeAvailable(UINT64 *pFreeBytes, UINT32 *pRemainCaptureNum);
AHC_BOOL 	CaptureTimer_Start(UINT32 ulTime);
AHC_BOOL 	CaptureTimer_Stop(void);
AHC_BOOL 	CaptureFunc_Shutter(void);
UINT16 		CaptureFunc_CheckSelfTimer(void);
AHC_BOOL	CaptureFunc_Preview(void);

AHC_BOOL    StateCaptureModeInitLCD(void* pData);
AHC_BOOL    StateCaptureModeInitHDMI(void* pData);
AHC_BOOL    StateCaptureModeInitTV(void* pData);
AHC_BOOL    StateCaptureModeShutDown(void* pData);
AHC_BOOL    StateSelectFuncCameraMode(void);

#endif //_STATECAMERAFUNC_H_
