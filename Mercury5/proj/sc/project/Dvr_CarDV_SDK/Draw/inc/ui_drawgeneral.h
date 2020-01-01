
#ifndef	__UI_DRAW_GENERAL_H__
#define	__UI_DRAW_GENERAL_H__

/*===========================================================================
 * Include file
 *===========================================================================*/ 

#include "GUI_Type.h"
#include "ahc_common.h"

/*===========================================================================
 * Macor define
 *===========================================================================*/ 

#define NULL_PARAM				(0xFFFFFFFF)

#define POS_PAGEINFO(x, pos)  	(x<=4)?(pos-(x-1)*3):(pos)

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef	void (DRAW_FUNC) (UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);

typedef	void (UI_DRAW_FUNC) (UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);

typedef struct {

    UINT16      m_BlockID;
    UINT16      m_PosX;
    UINT16      m_PosY;
    UINT16      m_Enable;
    AHC_BOOL 	m_bLarge;
    UINT8 		m_ubMag;
    DRAW_FUNC*  m_DrawFunc;
} UI_DARW_SET;

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

typedef enum {

	VIDEO_GUI_MOVIE_RES = 0,
	VIDEO_GUI_UI_MODE,
	VIDEO_GUI_SD_STATE,
	VIDEO_GUI_WB_MODE,
	VIDEO_GUI_BATTERY,
	VIDEO_GUI_SCENE,
	VIDEO_GUI_FLASH,
	VIDEO_GUI_REC_STATE,
	VIDEO_GUI_ZOOM_BAR,
	VIDEO_GUI_EV,
	VIDEO_GUI_REMAIN_TIME,
	VIDEO_GUI_REC_TIME,
	VIDEO_GUI_RTC_TIME,
	VIDEO_GUI_LOCK_FILE,
	VIDEO_GUI_LOCK_NUM,
	VIDEO_GUI_MUTE,
	VIDEO_GUI_REC_POINT,
	VIDEO_GUI_GPS_STATE,
	VIDEO_GUI_VMD_STATE,
	VIDEO_GUI_VTL_STATE,		// VIDEO_REC_TIMELAPSE_EN
	VIDEO_GUI_DRIVER_ID,
	VIDEO_GUI_WIFI,
	VIDEO_GUI_WIFI_SWITCH,
	VIDEO_GUI_LDWS_LINE,
	VIDEO_GUI_FCWS_INFO,
	VIDEO_GUI_MAX,
	AUDIO_GUI_REC_TIME,
	AUDIO_GUI_REC_POINT

} VIDEO_GUI_BLOCK;

typedef enum {

	DSC_GUI_IMAGE_RES = 0,
	DSC_GUI_UI_MODE,
	DSC_GUI_SD_STATE,
	DSC_GUI_WB_MODE,
	DSC_GUI_BATTERY,
	DSC_GUI_SCENE,
	DSC_GUI_FLASH,
	DSC_GUI_SELF_TIMER,
	DSC_GUI_BURST,
	DSC_GUI_ZOOM_BAR,
	DSC_GUI_EV,
	DSC_GUI_REMAIN_NUM,
	DSC_GUI_RTC_TIME,
	DSC_GUI_GPS_STATE,
	DSC_GUI_VMD_STATE,
	DSC_GUI_DRIVER_ID,
	DSC_GUI_MAX

} DSC_GUI_BLOCK;

typedef enum {

	BROWSER_GUI_FILENAME = 0,
	BROWSER_GUI_UI_MODE,
	BROWSER_GUI_SD_STATE,
	BROWSER_GUI_FILE_DATE,	
	BROWSER_GUI_BATTERY,
	BROWSER_GUI_MOV_TOTAL_TIME,
	BROWSER_GUI_RESOLUTION,
	BROWSER_GUI_MAX

} BROWSER_GUI_BLOCK;

typedef enum {

	MOVPB_GUI_STATUS = 0,
	MOVPB_GUI_FILE_INDEX,
	MOVPB_GUI_UI_MODE,
	MOVPB_GUI_SD_STATE,
	MOVPB_GUI_BATTERY,
	MOVPB_GUI_VOL_BAR,
	MOVPB_GUI_LOCK_FILE,
	MOVPB_GUI_FILENAME,
	MOVPB_GUI_CUR_TIME,
	MOVPB_GUI_TOTAL_TIME,
	MOVPB_GUI_MAX

} MOVPB_GUI_BLOCK;

typedef enum {

	AUDPB_GUI_STATUS = 0,
	AUDPB_GUI_FILE_INDEX,
	AUDPB_GUI_UI_MODE,
	AUDPB_GUI_SD_STATE,
	AUDPB_GUI_BATTERY,
	AUDPB_GUI_VOL_BAR,
	AUDPB_GUI_LOCK_FILE,
	AUDPB_GUI_FILENAME,
	AUDPB_GUI_CUR_TIME,
	AUDPB_GUI_TOTAL_TIME,
	AUDPB_GUI_MAX

} AUDPB_GUI_BLOCK;

typedef enum {

	JPGPB_GUI_FILE_INDEX = 0,
	JPGPB_GUI_UI_MODE,
	JPGPB_GUI_SD_STATE,
	JPGPB_GUI_BATTERY,
	JPGPB_GUI_LOCK_FILE,
	JPGPB_GUI_FILENAME,
	JPGPB_GUI_FILEDATE,
	JPGPB_GUI_MAX

} JPGPB_GUI_BLOCK;

/*===========================================================================
 * Extern variable
 *===========================================================================*/ 

extern UI_DARW_SET m_VideoDraw_Lcd[];
extern UI_DARW_SET m_DSCDraw_Lcd[];
extern UI_DARW_SET m_BrowserDraw_Lcd[];
extern UI_DARW_SET m_MovPBDraw_Lcd[];
extern UI_DARW_SET m_AudPBDraw_Lcd[];
extern UI_DARW_SET m_JpgPBDraw_Lcd[];

extern UI_DARW_SET m_VideoDraw_Tv[];
extern UI_DARW_SET m_DSCDraw_Tv[];
extern UI_DARW_SET m_BrowserDraw_Tv[];
extern UI_DARW_SET m_MovPBDraw_Tv[];
extern UI_DARW_SET m_AudPBDraw_Tv[];
extern UI_DARW_SET m_JpgPBDraw_Tv[];

extern UI_DARW_SET m_VideoDraw_Hdmi_1080P[];
extern UI_DARW_SET m_HdmiVideoDraw_7200P[];
extern UI_DARW_SET m_DSCDraw_Hdmi_1080P[];
extern UI_DARW_SET m_DSCDraw_Hdmi_720P[];
extern UI_DARW_SET m_BrowserDraw_Hdmi[];
extern UI_DARW_SET m_MovPBDraw_Hdmi_1080P[];
extern UI_DARW_SET m_MovPBDraw_Hdmi_720P[];
extern UI_DARW_SET m_JpgPBDraw_Hdmi_1080P[];
extern UI_DARW_SET m_JpgPBDraw_Hdmi_720P[];

extern UI_DARW_SET m_AudPBDraw_Hdmi[];


/*===========================================================================
 * Function Prototype
 *===========================================================================*/ 

void UIDrawAudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawTV_AudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawHdmi_AudPBFuncEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
void UIDrawEx(UINT16 ubID, UINT8 idx, AHC_BOOL bClear, AHC_BOOL bShow, GUI_COLOR bkColor, INT32 Para1);
AHC_BOOL SwitchUIDrawSetVideoRecordMode(void);
#if (DSC_MODE_ENABLE)
AHC_BOOL SwitchUIDrawSetCameraMode(void);
#endif
AHC_BOOL SwitchUIDrawSetBrowserMode(void);
AHC_BOOL SwitchUIDrawSetPlaybackMode(void);
#endif	// __UI_DRAW_GENERAL_H__
