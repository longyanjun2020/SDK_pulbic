
//==============================================================================
//
//  File        : drawstatevideofunc.h
//  Description : INCLUDE File for the DrawStateVideoFunc function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _DRAWSTATEVIDEOFUNC_H_
#define _DRAWSTATEVIDEOFUNC_H_

#include "statevideofunc.h"
/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum _VideoPreviewPage{
    VIDEO_MAIN_PAGE,
    VIDEO_CONTROL_PAGE
}VideoPreviewPage;

typedef enum _VideoZoomDir{
    VIDEO_ZOOM_NONE,
    VIDEO_ZOOM_IN,
    VIDEO_ZOOM_OUT
}VideoZoomDir;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

void DrawStateVideoRecUpdate(UINT32 ubEvent);
void DrawVideoRecStateRecord(VIDEO_RECORD_STATUS status);
void DrawVideoRecStatePageSwitch(UINT8 ubPage);
void DrawVideoRecInfo(AHC_BOOL bClear);
void DrawStateVideoRecInit(void);
void DrawStateVideoRecPreview(void);
void UpdateVideoCurrentRecordTime(void);

void UpdateMotionRemindTime(int rTime);
void UpdateVideoRecordStatus(UINT8 ubStatus);
void DrawVideoRecStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoAvailableRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoCurrentRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoFileName(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoMuteRecord(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoMotionDtc(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoLockFileStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoLockFileNum(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoRecFlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoRecording(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoWiFi(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoLDWS_Line(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoFCWS_Info(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoTimeLapse(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);		// VIDEO_REC_TIMELAPSE_EN
void DrawAudioCurRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawAudioRecording(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void DrawVideoParkingMode( AHC_BOOL bEnable );
void UpdateVideoCurrentTimeStamp(AHC_BOOL bSetStickerEnable);
void DrawVideo_GetDualTimeStampPosition(UINT16 uiOSDid, UINT32 TimeStampOp, UINT32* uiSrcAddr, UINT16* uwSrcW, UINT16* uwSrcH, UINT16* uwTempColorFormat,
						 UINT32* StickerX, UINT32* StickerY);
void DrawVideo_TimeStamp(UINT16 uiOSDid, UINT32 TimeStampOp, AHC_RTC_TIME* sRtcTime, UINT32* uiSrcAddr, UINT16* uwSrcW, UINT16* uwSrcH, UINT16* uwTempColorFormat,
                         UINT32* StickerX, UINT32* StickerY);

#endif   // _DRAWSTATEVIDEOFUNC_H_ 
