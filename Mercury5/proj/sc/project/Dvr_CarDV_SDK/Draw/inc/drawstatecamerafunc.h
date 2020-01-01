
//==============================================================================
//
//  File        : drawstatecamerafunc.h
//  Description : INCLUDE File for the DrawStateVideoFunc function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _DRAWSTATECAMERAFUNC_H_
#define _DRAWSTATECAMERAFUNC_H_

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _CapturePreviewPage{
    CAPTURE_MAIN_PAGE,
    CAPTURE_CONTROL_PAGE
}CapturePreviewPage;

typedef enum _CaptureZoomDir{
    CAPTURE_ZOOM_NONE,
    CAPTURE_ZOOM_IN,
    CAPTURE_ZOOM_OUT
}CaptureZoomDir;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void DrawStateCaptureUpdate( UINT32 ubEvent);
void DrawCaptureStatePageSwitch( UINT8 ubPage );
void DrawCaptureStateEV(void);
void DrawCaptureEV(UINT8 ubID, AHC_BOOL bClear);

void DrawCaptureMotionDtc(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawCaptureZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawCaptureFlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawCaptureRemainNum(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);

#endif   // _DRAWSTATECAMERAFUNC_H_ 

