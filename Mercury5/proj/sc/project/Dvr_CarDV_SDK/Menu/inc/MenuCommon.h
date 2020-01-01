
#ifndef _MENU_COMMON_H_
#define _MENU_COMMON_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Macro define 
 *===========================================================================*/ 

typedef struct sMENU*  PSMENUSTRUCT;
typedef struct sITEM*  PSMENUITEM;

typedef  AHC_BOOL	(*pfItemHandler)(PSMENUITEM pItem, AHC_BOOL bHover );
typedef  UINT32 	(*pfMenuEventHandler)(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam );
typedef  UINT32 	(*pfMenuGetDefault)(PSMENUSTRUCT pMenu );

/*===========================================================================
 * Macro define 
 *===========================================================================*/ 
 
#define  BUTTON_VIRTUAL_KEY_BASE 				(0x1000)
#define  BUTTON_VIRTUAL_KEY(X)      			(BUTTON_VIRTUAL_KEY_BASE+(X))

#define  BUTTON_VIRTUAL_RESET       			BUTTON_VIRTUAL_KEY(1)
#define  BUTTON_VIRTUAL_SET_ONE     			BUTTON_VIRTUAL_KEY(2)
#define  BUTTON_VIRTUAL_SELECT      			BUTTON_VIRTUAL_KEY(3)

#define  MENU_DEBUG 							(0)

/* MENU EVENT HANDLER ERROR CODE */
#define MENU_ERR_OK                             (0)
#define MENU_ERR_EXIT                           (1)
#define MENU_ERR_SLIDE_SHOW_EXIT                (2)
#define MENU_ERR_FORCE_BROWSER_EXIT             (3)
#define MENU_EXIT_DO_PARENT_EVENT				(4)


/* MENU OPERATION CONSTANTS */
#define MENU_NONE                               (0)
#define MENU_INIT                               (1)
#define MENU_UP                                 (2)
#define MENU_UP_RELEASE                         (3)
#define MENU_DOWN                               (4)
#define MENU_DOWN_RELEASE                       (5)
#define MENU_LEFT                               (6)
#define MENU_LEFT_RELEASE                       (7)
#define MENU_RIGHT                              (8)
#define MENU_RIGHT_RELEASE                      (9)
#define MENU_TOUCH                              (10)
#define MENU_TOUCH_MOVE                         (11)
#define MENU_TOUCH_RELEASE                      (12)
#define MENU_OK                                 (13)
#define MENU_OK_RELEASE                         (14)
#define MENU_MENU                               (15)
#define MENU_MENU_RELEASE                       (16)
#define MENU_SET_ONE                            (17)
#define MENU_REFRESH                            (18)
#define MENU_LCD_NORMAL							(19)
#define MENU_LCD_ROTATE							(20)
#define MENU_POWER_OFF							(21)
#define MENU_TELE							    (22)
#define MENU_TELE_RELEASE						(23)
#define MENU_WIDE							    (24)
#define MENU_WIDE_RELEASE						(25)
#define MENU_CIRCLE						        (26)
#define MENU_SDMMC_IN							(27)
#define MENU_SDMMC_OUT							(28)
#define	MENU_MUTE_PRESS							(29)
#define MENU_REC_PRESS							(30)
#define MENU_PLAY_PRESS							(31)
#define MENU_MODE_PRESS							(32)
#define MENU_PLAY_LPRESS						(33)
#define MENU_EXIT								(34)
#define MENU_TV_DETECT							(35)

#define MENU_BATTERY_DETECTION					(50)
#define MENU_UPDATE_MESSAGE					    (51)

#define MENU_NOT_MENU_EVENT					    (52)

/* ITEM FLAGS */
#define ITEM_FLAG_NONE                         	(0x00000000)
#define ITEM_FLAG_GOTO_MAIN                    	(0x00000001)
#define ITEM_FLAG_GOTO_SLIDESHOW               	(0x00000002)

/* MENU status */
#define MENU_STATUS_NONE                       	(0x00000000)
#define MENU_STATUS_PRESSED                    	(0x00000001)
#define MENU_STATUS_ITEM_TOUCHED               	(0x00000002)

/* Misc */
#define IS_POINT_IN_RECT_TOL(PT,RECT,t)
#define IS_FIT_IN_RANGE(X,LOW,HIGH)   			((X)<(LOW)|| (X)>(HIGH) )

/* For Edit File Status */
#define EDIT_FILE_SUCCESS						(0)
#define EDIT_FILE_NO_CARD						(1)
#define EDIT_FILE_CARD_LOCK						(2)
#define EDIT_FILE_CARD_ERROR					(3)
#define EDIT_FILE_DCF_ERROR						(4)
#define EDIT_FILE_NO_FILE						(5)

/* For Font/Size Selection */
#define NORMAL_SIZE								(0)
#define LARGE_SIZE								(1)

/* For Icon Magnification */
#define MAG_1X									(1)
#define MAG_2X									(2)
#define MAG_3X									(3)
#define MAG_4X									(4)

#if (VIRTUAL_KEY_BOARD)
#define KEYBOARD_EVENT_NONE     (0)
#define KEYBOARD_EVENT_CHG      (1)
#define KEYBOARD_EVENT_CTR      (2)
#define KEYBOARD_EVENT_ENTER    (3)

#define KEYBOARD_KEY_CTR        (0x00435452)//'CTR'
#define KEYBOARD_KEY_DEL        (0x0044454C)//'DEL'
#define KEYBOARD_KEY_CHG        (0x00434847)//'CHG'
#define KEYBOARD_KEY_ENT        (0x00454E54)//'ENT'
#endif

/*===========================================================================
 * Structure define 
 *===========================================================================*/
 typedef UINT32 TouchCallBackFunc(UINT16 x,UINT16 y); 

typedef struct sMENUTOUCHBUTTON
{
	RECT     			rcButton;			///< the region of touch button.
	UINT8    			ubOpTouchOffset;
	UINT32	 			ulOpTouch;
	UINT32	 			ulOpTouchMove;
	TouchCallBackFunc*	pTouchCallBack;
} SMENUTOUCHBUTTON, *PSMENUTOUCHBUTTON;

#if (VIRTUAL_KEY_BOARD)
typedef struct sKEY
{
    UINT32  uiASCIICode;
//    UINT32  uiKeyKind;
    RECT    rcUIRegion;
    RECT    rcTouchRegion;
    struct sKEY* psNextKey;
    struct sKEY* psPrevKey;
}SKEY, *PSKEY;

typedef struct sKEYBOARD
{
    UINT32 uiTop;
    UINT32 uiLeft;
    UINT32 uiKeyWidth;
    UINT32 uiKeyHeight;
    UINT32 uiHorizontalGap;
    UINT32 uiVerticalGap;
    UINT32 uiKeyNumber;
    struct sKEYBOARD* psNextRow;

}SKEYBOARD, *PSKEYBOARD;

typedef struct sKEYSPACE
{
    PSKEYBOARD sKeyBoard;
    PSKEY      sKey;
    struct sKEYSPACE* psNextSpace;
    struct sKEYSPACE* psPrevSpace;
}SKEYSPACE, *PSKEYSPACE;

#endif

typedef struct sITEM
{
    int           		iItemId;
    const GUI_BITMAP*   bmpIcon;
    UINT32        		uiStringId;
    struct sMENU* 		pSubMenu;
    pfItemHandler		pfItemSelect;
    UINT32				uiFlag;
    AHC_BOOL			bEnabled;
    void*				pIdvSetting;
	PSMENUTOUCHBUTTON	ptp;		// For Touch panel
} SMENUITEM, *PSMENUITEM;

typedef struct sMENU
{
    int                	iMenuId;
    const GUI_BITMAP*  	bmpIcon;
    UINT32             	uiStringId;
    struct sMENU*      	pParentMenu;
    int                	iNumOfItems;
    PSMENUITEM*        	pItemsList;
    pfMenuEventHandler 	pfEventHandler;
    pfMenuGetDefault   	pfMenuGetDefaultVal;
    UINT32             	uiFlag;
    UINT32             	uiStringDescription;
    AHC_BOOL           	bCustom;
    // Operation
    int                	iSelected;
    int                	iCurrentPos;
    AHC_BOOL           	bEnabled;
    UINT32             	uiStatus;
    AHC_BOOL           	bSetOne;
} SMENUSTRUCT, *PSMENUSTRUCT;

typedef struct 
{
	UINT32 		m_X0;
	UINT32 		m_Y0;
	UINT32 		m_X1;
	UINT32 		m_Y1;
} MENU_REGION, *PMENU_REGION;

typedef struct 
{
	UINT32		m_PageItemNum;
	MENU_REGION m_Region[3];
	GUI_COLOR 	m_BkClr[3]; //3 Regions
	GUI_COLOR 	m_TextClr;
	GUI_COLOR 	m_LineClr;				
	GUI_COLOR 	m_FocusClr;				
	UINT32 		m_PenSize;
	UINT32 		m_R2SepX;	
} MENU_ATTR, *PMENU_ATTR;

typedef struct 
{
	UINT32		m_Type;
	UINT32		m_PageItemNum;
	GUI_COLOR 	m_Layer1BkClr;
	GUI_COLOR 	m_Layer2BkClr;
	GUI_COLOR 	m_TextClr;
	GUI_COLOR 	m_LineClr;				
	GUI_COLOR 	m_FocusClr;				
	UINT32 		m_PenSize;
} SIDEMENU_ATTR, *PSIDEMENU_ATTR;

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 

typedef enum{
	MENUID_QUICK_MENU_VIDEO = 1		,
	MENUID_QUICK_MENU_STILL         ,
	MENUID_QUICK_MENU_VIDEO_PLAYBACK,
	MENUID_QUICK_MENU_STILL_PLAYBACK,
	MENUID_MAIN_MENU_MANUAL         ,
	MENUID_MAIN_MENU_VIDEO          ,
	MENUID_MAIN_MENU_STILL          ,
	MENUID_MAIN_MENU_PLAYBACK       ,
	MENUID_MAIN_MENU_EDIT           ,
	MENUID_MAIN_MENU_MEDIA          ,
	MENUID_MAIN_MENU_GENERAL        ,
	MENUID_MODE_SELECT      		,
	MENUID_POWER_ON_SET				,
	MENUID_TOP_MENU					,
	MENUID_MAIN_LANGUAGE_SET		,
	MENUID_MAIN_MENU_EXIT			,
	MENUID_MAIN_MENU_BROWSER		,
	MENUID_USB_MODE_SELECT			,
#if (MENU_WIFI_PAGE_EN)
	MENUID_MAIN_MENU_WIFI			,
#endif

	MENUID_MAIN_MAX
}MENUID_MAIN;

typedef enum{
	MENUID_SUB_MENU_SCENCE       = 100   	,
	MENUID_SUB_MENU_FOCUSWINDOW          	,
	MENUID_SUB_MENU_FOCUSRANGE           	,
	MENUID_SUB_MENU_METERING             	,
	MENUID_SUB_MENU_EV                   	,
	MENUID_SUB_MENU_ISO                  	,
	MENUID_SUB_MENU_WB                   	,
	MENUID_SUB_MENU_COLOR                	,
	MENUID_SUB_MENU_EFFECT               	,
	MENUID_SUB_MENU_FACE_TOUCH           	,
	MENUID_SUB_MENU_SMILE_DETECTION      	,
	MENUID_SUB_MENU_SMILE_SENSITIVITY    	,
	MENUID_SUB_MENU_MOVIE_MODE           	,
	MENUID_SUB_MENU_MOVIE_QUALITY        	,
	MENUID_SUB_MENU_MOVIE_STABLEILIZATION	,
	MENUID_SUB_MENU_AUTO_SLOW_SHUTTER    	,
	MENUID_SUB_MENU_MIC_SENSITIVITY      	,
	MENUID_SUB_MENU_MOVIE_PRERECORD		 	,
	MENUID_SUB_MENU_MOVIE_POWER_OFF_TIME 	,
	MENUID_SUB_MENU_MOVIE_VMD_REC_TIME 		,
	MENUID_SUB_MENU_MOVIE_SOUND_RECORD   	,
    MENUID_SUB_MENU_MOVIE_CLIPTIME       	,
    MENUID_SUB_MENU_MOVIE_NIGHT_MODE        ,
    MENUID_SUB_MENU_MOVIE_AUTO_REC			,
	MENUID_SUB_MENU_STILL_IMAGE_SIZE     	,
	MENUID_SUB_MENU_STILL_QUALITY        	,
	MENUID_SUB_MENU_STILL_STABLEILIZATION	,
	MENUID_SUB_MENU_FLASH                	,
	MENUID_SUB_MENU_FLASH_LEVEL          	,
	MENUID_SUB_MENU_REDEYE_REDUCTION     	,
	MENUID_SUB_MENU_SELFTIMER            	,
	MENUID_SUB_MENU_BURST_CAPTURE        	,
	MENUID_SUB_MENU_VMD_SHOT_NUM        	,
	MENUID_SUB_MENU_TIMELAPSE_TIME        	,
	MENUID_SUB_MENU_QUICKM_DELETE        	,
	MENUID_SUB_MENU_QUICKM_PROTECT       	,
	MENUID_SUB_MENU_CUT                  	,
	MENUID_SUB_MENU_ROTATE               	,
	MENUID_SUB_MENU_RESIZE               	,
	MENUID_SUB_MENU_TRIMMING             	,
	MENUID_SUB_MENU_SLIDE_SHOW_FILES     	,
	MENUID_SUB_MENU_SLIDE_SHOW_EFFECTS   	,
	MENUID_SUB_MENU_SLIDE_SHOW_MUSIC     	,
	MENUID_SUB_MENU_VOLUME               	,
    MENUID_SUB_MENU_VIDEO_TYPE              ,
	MENUID_SUB_MENU_DELETE_FILE             ,
	MENUID_SUB_MENU_DELETE               	,
	MENUID_SUB_MENU_DELETE_ALL           	,
	MENUID_SUB_MENU_DELETE_ALL_VIDEO	 	,
	MENUID_SUB_MENU_DELETE_ALL_IMAGE	 	,
	MENUID_SUB_MENU_DELETE_GLOCK         	,
	MENUID_SUB_MENU_PROTECT              	,
	MENUID_SUB_MENU_PROTECT_ALL          	,
	MENUID_SUB_MENU_PROTECT_ALL_VIDEO	 	,
	MENUID_SUB_MENU_PROTECT_ALL_IMAGE	 	,
	MENUID_SUB_MENU_UNPROTECT_ALL	     	,
	MENUID_SUB_MENU_UNPROTECT_ALL_VIDEO	 	,
	MENUID_SUB_MENU_UNPROTECT_ALL_IMAGE	 	,
	MENUID_SUB_MENU_MEDIA_SELECT         	,
	MENUID_SUB_MENU_FORMAT_SD_CARD       	,
	MENUID_SUB_MENU_FORMAT_INTMEM        	,
	MENUID_SUB_MENU_SD_CARD_INFO         	,
	MENUID_SUB_MENU_INTMEM_INFO          	,
	MENUID_SUB_MENU_BEEP                 	,
	MENUID_SUB_MENU_LCD_BRIGHTNESS       	,
	MENUID_SUB_MENU_AUTO_POWER_OFF       	,
	MENUID_SUB_MENU_CLOCK_SETTINGS       	,
	MENUID_SUB_MENU_DRIVER_ID_SETTINGS		,
	MENUID_SUB_MENU_DATETIME_FORMAT      	,
	MENUID_SUB_MENU_DATELOGO_STAMP		 	,
	MENUID_SUB_MENU_GPS_STAMP		 		,
	MENUID_SUB_MENU_SPEED_STAMP		 		,
	MENUID_SUB_MENU_LANGUAGE             	,
	MENUID_SUB_MENU_TV_SYSTEM            	,
	MENUID_SUB_MENU_HDMI_OUTPUT          	,
	MENUID_SUB_MENU_RESET_SETUP          	,
	MENUID_SUB_MENU_FLICKER_FREQUENCY    	,
	MENUID_SUB_MENU_GSENSOR_SENSITIVITY  	,
	MENUID_SUB_MENU_MOTION_DTC_SENSITIVITY  ,
	MENUID_SUB_MENU_GPS_INFO             	,
	MENUID_SUB_MENU_LCD_ROTATE		     	,
	MENUID_SUB_MENU_USB_FUNCTION	     	,
	MENUID_SUB_MENU_LCD_POWER_SAVE	     	,
	MENUID_SUB_MENU_TIME_ZONE		     	,
	MENUID_SUB_MENU_LED_FLASH            	,
	MENUID_SUB_MENU_BOOT_UP_MODE			,
	MENUID_SUB_MENU_NIGHT_MODE				,
	MENUID_SUB_MENU_FW_VERSION_INFO			,
	MENUID_SUB_MENU_GSENSOR_POWERON_SENSITIVITY,
	MENUID_SUB_MENU_WIFI_MODE,
	MENUID_SUB_MENU_VIDEO_TIMELAPSE,		// VIDEO_REC_TIMELAPSE_EN
    MENUID_SUB_MENU_MOVIE_PARKING_MODE,
    MENUID_SUB_MENU_MOVIE_LDWS_MODE,
    MENUID_SUB_MENU_MOVIE_FCWS_MODE,
    MENUID_SUB_MENU_MOVIE_SAG_MODE,
    MENUID_SUB_MENU_MOVIE_HDR_MODE,
    MENUID_SUB_MENU_MOVIE_SLOWMOTION_MODE,
    MENUID_SUB_MENU_MOVIE_WNR_MODE,
#if (VIRTUAL_KEY_BOARD)
	MENUID_SUB_MENU_VURTUAL_KEYBOARD,
#endif
#if MENU_RD_LDWS_CALIBRATION_EN
	MENUID_SUB_MENU_LDWS_CALIBRATION,
#endif
#if (MENU_GENERAL_LDWS_CALIBRATION_EN)
	MENUID_SUB_MENU_USER_LDWS_CALIBRATION,
#endif
#if (MENU_WIFI_PAGE_EN)
	MENUID_SUB_MENU_WIFI_MODE_1,
	MENUID_SUB_MENU_WIFI_AP,
	MENUID_SUB_MENU_WIFI_AP_SSID,
	MENUID_SUB_MENU_WIFI_AP_PSWD,
	MENUID_SUB_MENU_WIFI_STATION,
	MENUID_SUB_MENU_WIFI_STATION1_SSID,	
	MENUID_SUB_MENU_WIFI_STATION1_PSWD,
	MENUID_SUB_MENU_WIFI_STATION2_SSID,
	MENUID_SUB_MENU_WIFI_STATION2_PSWD,
	MENUID_SUB_MENU_WIFI_STATION3_SSID,
	MENUID_SUB_MENU_WIFI_STATION3_PSWD,	
	MENUID_SUB_MENU_WIFI_STATION4_SSID,
	MENUID_SUB_MENU_WIFI_STATION4_PSWD,
	MENUID_SUB_MENU_WIFI_STATION5_SSID,
	MENUID_SUB_MENU_WIFI_STATION5_PSWD,
	MENUID_SUB_MENU_WIFI_STATION6_SSID,	
	MENUID_SUB_MENU_WIFI_STATION6_PSWD,
#endif
    MENUID_SUB_MENU_CONTRAST,
    MENUID_SUB_MENU_SATURATION,
    MENUID_SUB_MENU_SHARPNESS,
    MENUID_SUB_MENU_GAMMA,
 #if(MENU_REARCAM_TYPE_EN)
	MENUID_SUB_MENU_REAR_TYPE,
#endif
    MENUID_SUB_MENU_COLORTEMP,

	MENUID_SUB_MENU_PQ_CONTRAST,
	MENUID_SUB_MENU_PQ_BRIGHTNESS,
	MENUID_SUB_MENU_PQ_SATURATION,
	MENUID_SUB_MENU_PQ_COLORTEMP,

	MENUID_SUB_MENU_MAX
}MENU_SUB;

typedef enum{

	REGION_1 = 0,
	REGION_2,
	REGION_3,
	REGION_MAX
} MENU_REGION_NUM;

typedef enum{

	MENU_MAIN,
	MENU_SUBPAGE,
	MENU_SUBTEXT,
	MENU_SUBICON,
	MENU_MAX
} MENU_TYPE;

typedef enum{

	SUB_FULLPAGE,
	SUB_GRID,
	SUB_CONFIRM,
	SUB_SMALLPAGE
} SUBMENU_CURTAINTYPE;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern SMENUSTRUCT 	sPhotoMainMenu;
extern SMENUSTRUCT 	sShortCutMenuStill;

extern SMENUSTRUCT 	sMainMenuStill;
extern SMENUSTRUCT  sMainMenuManual;
extern SMENUSTRUCT  sMainMenuVideo;
extern SMENUSTRUCT  sMainMenuPlayback;
extern SMENUSTRUCT  sMainMenuEdit;
extern SMENUSTRUCT  sMainMenuMedia;
extern SMENUSTRUCT  sMainMenuGeneral;
extern SMENUSTRUCT 	sMainMenuExit;
extern SMENUSTRUCT  sMainLanguage;
#if (USB_MODE_SELECT_EN)
extern SMENUSTRUCT   sUSBModeSelectMenu;
#endif
#if (MENU_WIFI_PAGE_EN)
extern SMENUSTRUCT  sMainMenuWifi;
#endif
#ifdef TOP_MENU_PAGE_EN
#if (TOP_MENU_PAGE_EN)
extern SMENUSTRUCT  sTopMenu;
extern PSMENUITEM	sTopMenuList[];
extern SMENUSTRUCT	sGuideMenu;
extern PSMENUITEM	sGuideMenuList[];
extern SMENUITEM 	sItemTopMenu_Video;
extern SMENUITEM 	sItemTopMenu_Camera;
#endif
#endif

/*===========================================================================
 * Function prototype 
 *===========================================================================*/
 
PSMENUSTRUCT 	GetCurrentMenu(void);
void         	SetCurrentMenu(PSMENUSTRUCT pMenu);
void         	ResetCurrentMenu(void);
int 			RemoveMenuItem(SMENUSTRUCT *plist, SMENUITEM *pItem);
UINT32       	MenuButtonToMenuOp(UINT32 ulEvent,UINT32 ulPosition );
int 		 	OffsetItemNumber(int iCur, int iMin, int iMax, int iOffset, AHC_BOOL bWrap );
int 		 	OffsetItemNumber_Menu(int iCur, int iMin, int iMax, int iOffset, AHC_BOOL bWrap );

/* For SlideMenu Speed */
#define SLIDE_SPEED				(12)

#define MENU_HIDE				(0)
#define MENU_SHOW				(1)

/* For Item Selection */
#define	CONFIRM_OPT_YES			(0)
#define CONFIRM_OPT_NO			(1)
#define CONFIRM_NOT_YET			(0xFF)

/* For Bar Size Type */
#define	BAR_NORMAL_TYPE			(0)
#define	BAR_WIDE_TYPE			(1)
#define BAR_NARROW_TYPE			(2)

/* For Bar State Type */
#define	BAR_STATE_WHT			(0)
#define	BAR_STATE_WHT_DEF		(1)
#define	BAR_STATE_YEL			(2)
#define	BAR_STATE_YEL_DEF		(3)
#define	BAR_STATE_NUM			(4)

typedef struct {
		const GUI_BITMAP*	bar[BAR_STATE_NUM];
} BAR_SET;

extern BAR_SET			vBarSet[];
extern PSMENUSTRUCT 	LongStringMenu[];

#define	MAKE_BAR_ID(t, s)	((int)((t) << 8) + (int)((s)))

#define	BAR_STATE(bar)		(bar & 0xff)

#define	PBAR(i)				vBarSet[(i >> 8)].bar[(i & 0xff)]

#define	BAR(i)				(*(vBarSet[(i >> 8)].bar[(i & 0xff)]))

#define	BAR_TYPE(bt, ms)	{ int i; bt = BAR_NORMAL_TYPE;										\
							  for (i = 0; LongStringMenu[i]; i++) {								\
								if (LongStringMenu[i] == ms) { bt = BAR_WIDE_TYPE; break; }}	\
							}

/* For Menu Drawing */
#define REGION_W(r)							(r.m_X1-r.m_X0)
#define REGION_H(r)							(r.m_Y1-r.m_Y0)

#define GET_ITEM_XSTART(a)					(a.m_R2SepX + a.m_PenSize)
#define GET_ITEM_XEND(a)					(a.m_Region[REGION_2].m_X1 -1)
#define GET_ITEM_YSTART(a, it, off)			(a.m_Region[REGION_2].m_Y0 + (it)*off + a.m_PenSize)
#define GET_ITEM_YEND(a, it, off)			(a.m_Region[REGION_2].m_Y0 + (it+1)*off -1)

#define SET_REG_BOUND(r0, r1) 				r0.m_X0 = r1.m_X0; r0.m_Y0 = r1.m_Y0; r0.m_X1 = r1.m_X1; r0.m_Y1 = r1.m_Y1;

#define	SET_SUBRECT(p, l, t, w, h) 		 	p->uiLeft = l; p->uiTop = t; p->uiWidth = w; p->uiHeight = h;

extern MENU_ATTR 		m_MainMenuAttr;
extern MENU_ATTR		m_SubPageMenuAttr;
extern SIDEMENU_ATTR 	m_SubIconTextMenuAttr;

extern MENU_REGION 		R1;
extern MENU_REGION 		R2;
extern MENU_REGION 		R3;

extern UINT8 			m_ubSubPageType;
extern UINT32 			m_ulSubItemNum;
extern GUI_COLOR		m_SubTextClr;
extern GUI_COLOR		m_SubLineClr;
extern GUI_COLOR		m_SubFocusClr;
extern UINT32			m_ulR2SepX;
extern UINT32			m_ulPenSize;
				
/* For Touch Panel */
#define PRESS_ICONSTATE(x, e)        		if(x) { return e; }
#define RELEASE_ICONSTATE(x, e)      		if(x) { x=AHC_FALSE; return e; }				

extern AHC_BOOL   		bIconCaptPressed;
extern AHC_BOOL   		bIconRecPressed;
extern AHC_BOOL   		bIconWidePressed;
extern AHC_BOOL   		bIconTelePressed;
extern AHC_BOOL   		bIconZoomPressed;
extern AHC_BOOL   		bIconPageSwitch;
extern AHC_BOOL   		bIconNextPressed;
extern AHC_BOOL   		bIconPrevPressed;

extern SMENUTOUCHBUTTON VideoMainPage_TouchButton[3];
extern SMENUTOUCHBUTTON VideoCtrlPage_TouchButton[6];
extern SMENUTOUCHBUTTON CaptureMainPage_TouchButton[3];
extern SMENUTOUCHBUTTON CaptureCtrlPage_TouchButton[6];
extern SMENUTOUCHBUTTON Browser_TouchButton[5];
extern SMENUTOUCHBUTTON MovPBMainPage_TouchButton[6];
extern SMENUTOUCHBUTTON MovPBCtrlPage_TouchButton[6];
extern SMENUTOUCHBUTTON JpgPBMainPage_TouchButton[6];
extern SMENUTOUCHBUTTON JpgPBCtrlPage_TouchButton[6];
extern SMENUTOUCHBUTTON TopPage_TouchButton[6];

extern SMENUTOUCHBUTTON MainMenu_TouchButton[8];
extern SMENUTOUCHBUTTON SubMenu2_TouchButton[3];
extern SMENUTOUCHBUTTON SubMenu4_TouchButton[5];
extern SMENUTOUCHBUTTON SubMenu6_TouchButton[7];
extern SMENUTOUCHBUTTON MenuConfirm_TouchButton[3];
extern SMENUTOUCHBUTTON MenuInfo_TouchButton[1];
extern SMENUTOUCHBUTTON MenuEV_TouchButton[4];
extern SMENUTOUCHBUTTON MenuVolume_TouchButton[4];

extern SMENUTOUCHBUTTON Browser_FileEditTouchButton[2];
extern SMENUTOUCHBUTTON MenuClockSetting_TouchButton[4];
extern SMENUTOUCHBUTTON MenuDriverIdSetting_TouchButton[20];

/* For Touch Menu */
#define	MENU_EXIT_PRESS				1
#define	MENU_EXIT_MOVE				101
#define	MENU_RETURN_PRESS			2
#define	MENU_RETURN_MOVE			102
#define	MENU_OK_PRESS				3
#define	MENU_OK_MOVE				103
#define	MENU_UP_PRESS				4
#define	MENU_UP_MOVE				104
#define	MENU_DOWN_PRESS				5
#define	MENU_DOWN_MOVE				105
#define	MENU_LEFT_PRESS				6
#define	MENU_LEFT_MOVE				106
#define	MENU_RIGHT_PRESS			7
#define	MENU_RIGHT_MOVE				107

//Main Menu
#define	MENU_MAIN0_PRESS			8    
#define	MENU_MAIN0_MOVE				108
#define	MENU_MAIN1_PRESS			9
#define	MENU_MAIN1_MOVE				109
#define	MENU_MAIN2_PRESS			10
#define	MENU_MAIN2_MOVE				110

//Sub Menu
#define	MENU_SUB20_PRESS			11   
#define	MENU_SUB20_MOVE				111
#define	MENU_SUB21_PRESS			12
#define	MENU_SUB21_MOVE				112
#define	MENU_SUB40_PRESS			13
#define	MENU_SUB40_MOVE				113
#define	MENU_SUB41_PRESS			14
#define	MENU_SUB41_MOVE				114
#define	MENU_SUB42_PRESS			15
#define	MENU_SUB42_MOVE				115
#define	MENU_SUB43_PRESS			16
#define	MENU_SUB43_MOVE				116
#define	MENU_SUB60_PRESS			17
#define	MENU_SUB60_MOVE				117
#define	MENU_SUB61_PRESS			18
#define	MENU_SUB61_MOVE				118
#define	MENU_SUB62_PRESS			19
#define	MENU_SUB62_MOVE				119
#define	MENU_SUB63_PRESS			20
#define	MENU_SUB63_MOVE				120
#define	MENU_SUB64_PRESS			21
#define	MENU_SUB64_MOVE				121
#define	MENU_SUB65_PRESS			22
#define	MENU_SUB65_MOVE				122
						
//EV/Volume
#define	MENU_DECREASE_PRESS	        23
#define	MENU_DECREASE_MOVE		    123
#define	MENU_INCREASE_PRESS		    24
#define	MENU_INCREASE_MOVE		    124

//Confirm Page
#define	MENU_YES_PRESS	        	25
#define	MENU_YES_MOVE		    	125
#define	MENU_NO_PRESS	        	26
#define	MENU_NO_MOVE		    	126    
							
//////////////////////////////////////////////////////////////////////////////////////////////////////							

void 	 TouchButtonInit_MenuConfirm(void);
void     TouchButtonInit_EditMenuConfirm(void);
void 	 TouchButtonInit_MenuInfo(void);

AHC_BOOL IsCurrentTopMenu(PSMENUSTRUCT pMenu);
AHC_BOOL IsCurrentMainMenu(PSMENUSTRUCT pMenu);
AHC_BOOL IsCurMultiLayerMenu(PSMENUSTRUCT pMenu);
AHC_BOOL IsTopSubMenuLinked(PSMENUSTRUCT pMenu);
UINT8 	 GetSubMenuType(void);
void 	 SetSubMenuType(UINT8 ubType);

void 	 MenuDraw_SD_Status(void);
void 	 MenuDraw_UIMode(UINT16 uwDispID);
void 	 MenuDraw_MediaType(UINT16 uwDispID);
void 	 MenuDraw_BatteryStatus(UINT16 uwDispID);

void 	 MenuDrawItemPosBar(UINT16 uwDispID, UINT32 item, MENU_ATTR attr, AHC_BOOL bClear);
void 	 MenuDrawDirection(UINT16 uwDispID, UINT8 dir, UINT16 x, UINT16 y, GUI_COLOR color);
void 	 MenuDrawSubBackCurtain(UINT16 uwDispID, GUI_COLOR bkColor);
void 	 MenuDrawSubBackCurtainGrid(UINT16 uwDispID);
void 	 MenuDrawSubBackCurtainConfirm(UINT16 uwDispID);
void 	 MenuDrawSubPageInfo(UINT16 uwDispID, int uiCurrentPage, int uiTotalPage);

void 	 QuickDrawItem_GPSInfo(UINT16 uwID, GUI_COLOR bkColor);
void 	 OSDDraw_GPSStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 QuickDrawGPSInfoPage(UINT8 ubID,AHC_BOOL bFlag);

void 	 OSDDraw_MainTouchButton(UINT16 ubID, UINT8 uiMode);
void 	 OSDDraw_CtrlTouchButton(UINT16 ubID, UINT8 uiMode);

void 	 OSDDraw_ClearPanel(UINT16 ubID, GUI_COLOR color);

void 	 OSDDraw_DigitZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1, UINT8 ubMode);
void 	 OSDDraw_DateTime(UINT8 ubID, int x, int y, int WordWidth, void* ptime);
void	 OSDDraw_CurrentRTCTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_EV(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_WB_Mode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_UIMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_ImageSize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_FlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_SelfTimer(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_BurstShot(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_MovieSize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_MediaType(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_FocusRange(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_SmileDetect(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_SceneMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_Battery(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_BatteryDummy(UINT16 ubID,UINT32 x, UINT32 y,AHC_BOOL bLarge, UINT8 ubMag);
void 	 OSDDrawSetting_BatteryStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_VideoStablize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_ImageStablize(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void 	 OSDDrawSetting_DriverId(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);
void	 DrawVideoWiFiStreaming(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1);

#if (VIRTUAL_KEY_BOARD)
void KEYBOARD_INIT(void);
AHC_BOOL KEYBOARD_AddKey(PSKEY* psKeyHead, PSKEY psKey);
PSKEY KEYBOARD_GetKeyHead(void);
UINT32 KEYBOARD_GetWordLength(void);
AHC_BOOL KEYBOARD_DelKey(PSKEY pKey);
AHC_BOOL KEYBOARD_AdjustPosition(PSKEYBOARD psKeySpace, PSKEY psKey);
AHC_BOOL KEYBOARD_CheckTouchButton(PSKEY* psKey, PPOINT pPoint);

UINT32 KEYBOARD_EventHandler(PSKEY psKey);
void KEYBOARD_ResetWord(void);
AHC_BOOL KEYBOARD_IpnputWord(INT8* pchWord, UINT32 uiWordLength);
INT8* KEYBOARD_GetWord(void);
AHC_BOOL KEYBOARD_DelWord(UINT32 uiWordLength);

#if VIRTUAL_KEY_BOARD_BY_KEY
#if VIRTUAL_KEY_BOARD_FOR_CAR_ID
void KEYBOARD_CarNo(void);
#endif
#if VIRTUAL_KEY_BOARD_FOR_WIFI
#if MENU_WIFI_AP_SSID_EN
void KEYBOARD_WifiAPSSID(void);
#endif
#if MENU_WIFI_AP_PSWD_EN
void KEYBOARD_WifiAPPSWD(void);
#endif
#if MENU_WIFI_STATION2_SSID_EN
void KEYBOARD_WifiSTA2SSID(void);
#endif
#if MENU_WIFI_STATION2_PSWD_EN
void KEYBOARD_WifiSTA2PSWD(void);
#endif
#if MENU_WIFI_STATION3_SSID_EN
void KEYBOARD_WifiSTA3SSID(void);
#endif
#if MENU_WIFI_STATION3_PSWD_EN
void KEYBOARD_WifiSTA3PSWD(void);
#endif
#if MENU_WIFI_STATION4_SSID_EN
void KEYBOARD_WifiSTA4SSID(void);
#endif
#if MENU_WIFI_STATION4_PSWD_EN
void KEYBOARD_WifiSTA4PSWD(void);
#endif
#if MENU_WIFI_STATION5_SSID_EN
void KEYBOARD_WifiSTA5SSID(void);
#endif
#if MENU_WIFI_STATION5_PSWD_EN
void KEYBOARD_WifiSTA5PSWD(void);
#endif
#if MENU_WIFI_STATION6_SSID_EN
void KEYBOARD_WifiSTA6SSID(void);
#endif
#if MENU_WIFI_STATION6_PSWD_EN
void KEYBOARD_WifiSTA6PSWD(void);
#endif
#endif
unsigned char KEYBOARD_GetKeyMount(void);
#endif

#endif

#endif //_MENU_COMMON_H_

