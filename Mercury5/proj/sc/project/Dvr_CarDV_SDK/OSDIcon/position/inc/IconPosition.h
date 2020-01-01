#ifndef _ICON_POSITION_H_
#define _ICON_POSITION_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 
#include "Customer_config.h"

#include "MenuCommon.h"
#include "MenuSetting.h"
#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define OSD_MENU_ITEM_NUM			(4)

//make it possible to define this in config_xx.h
#ifndef DISP_WIDTH
#define DISP_WIDTH					(320)
#define DISP_HEIGHT					(240)
#endif

//NTSC
#define TV_MENU_WIDTH						(320)
#define TV_MENU_HEIGHT						(240)

#define HDMI_MENU_WIDTH_1080				(480)//(320)
#define HDMI_MENU_HEIGHT_1080				(270)//(240)

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
#define STRETCH_W(x)				((DISP_WIDTH*x/OSD_DISPLAY_SCALE_LCD)/ORIGINAL_OSD_W)
#define STRETCH_H(y)				((DISP_HEIGHT*y/OSD_DISPLAY_SCALE_LCD)/ORIGINAL_OSD_H)
#define STRETCH_FULL_SCALE_W(x)		((DISP_WIDTH*x)/ORIGINAL_OSD_W)
#define STRETCH_FULL_SCALE_H(y)		((DISP_HEIGHT*y)/ORIGINAL_OSD_H)
#define STRETCH_2X(v)				(v*2)

#define BG_CURTAIN_H             	STRETCH_H(36)
#define BG_CURTAIN_W            	(DISP_WIDTH/OSD_DISPLAY_SCALE_LCD)	//(320)
#define BG_CURTAIN_EDGE           	STRETCH_H(4)
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define STRETCH_W(x)				((DISP_HEIGHT*x/OSD_DISPLAY_SCALE_LCD)/ORIGINAL_OSD_W)//(x*2)//(x*2) icon position for 480*1280
#define STRETCH_H(y)				((DISP_WIDTH*y/OSD_DISPLAY_SCALE_LCD)/ORIGINAL_OSD_H)
#define STRETCH_FULL_SCALE_W(x)		((DISP_HEIGHT*x)/ORIGINAL_OSD_W)
#define STRETCH_FULL_SCALE_H(y)		((DISP_WIDTH*y)/ORIGINAL_OSD_H)
#define STRETCH_2X(v)				(v*2)

#define BG_CURTAIN_H             	STRETCH_H(36)
#define BG_CURTAIN_W            	(DISP_HEIGHT/OSD_DISPLAY_SCALE_LCD)	//(320)
#define BG_CURTAIN_EDGE           	STRETCH_H(4)
#endif

//#define BG_CURTAIN_H             	(36)
//#define BG_CURTAIN_W            	(320)
//#define BG_CURTAIN_EDGE           	(4)

#define OSD_MENU_EXIT_X				(2)
#define OSD_MENU_EXIT_Y				(0)
#define OSD_MENU_EXIT_W				(32)
#define OSD_MENU_EXIT_H				(32)

#define OSD_MENU_UP_X				(OSD_MENU_EXIT_X)
#define OSD_MENU_UP_Y				(48)
#define OSD_MENU_UP_W				(OSD_MENU_EXIT_W)
#define OSD_MENU_UP_H				(OSD_MENU_EXIT_H)

#define OSD_MENU_DOWN_X				(OSD_MENU_EXIT_X)
#define OSD_MENU_DOWN_Y				(156)
#define OSD_MENU_DOWN_W				(OSD_MENU_EXIT_W)
#define OSD_MENU_DOWN_H				(OSD_MENU_EXIT_H)

#define OSD_MENU_LEFT_X				(OSD_MENU_EXIT_X)
#define OSD_MENU_LEFT_Y				(206)
#define OSD_MENU_LEFT_W				(OSD_MENU_EXIT_W)
#define OSD_MENU_LEFT_H				(OSD_MENU_EXIT_H)

#define OSD_MENU_RIGHT_X			(OSD_MENU_EXIT_X+270)
#define OSD_MENU_RIGHT_Y			(OSD_MENU_LEFT_Y)
#define OSD_MENU_RIGHT_W			(OSD_MENU_EXIT_W)
#define OSD_MENU_RIGHT_H			(OSD_MENU_EXIT_H)

#if (MENU_DIR_KEY_NUM == 1)	
#define OSD_MENU_CATA_X				(OSD_MENU_EXIT_X)
#define OSD_MENU_CATA_Y				(OSD_MENU_EXIT_Y)
#else
#define OSD_MENU_CATA_X				(OSD_MENU_LEFT_X+50)
#define OSD_MENU_CATA_Y				(OSD_MENU_LEFT_Y)
#endif
#define OSD_MENU_CATA_W				(OSD_MENU_EXIT_W-2)
#define OSD_MENU_CATA_H				(OSD_MENU_EXIT_H+3)

#define OSD_MENU_EVDECREASE_X		(OSD_MENU_EXIT_X)
#define OSD_MENU_EVDECREASE_Y		(90)
#define OSD_MENU_EVDECREASE_W	    (OSD_MENU_EXIT_W + 4)
#define OSD_MENU_EVDECREASE_H		(OSD_MENU_EXIT_H + 4)

#define OSD_MENU_EVINCREASE_X		(OSD_MENU_LEFT_X + 272)
#define OSD_MENU_EVINCREASE_Y		(OSD_MENU_EVDECREASE_Y)
#define OSD_MENU_EVINCREASE_W	    (OSD_MENU_EXIT_W + 33)
#define OSD_MENU_EVINCREASE_H		(OSD_MENU_EXIT_H+ 33)

#define OSD_MENU_FLHIGH_X			(100)
#define OSD_MENU_FLHIGH_Y			(50)
#define OSD_MENU_FLHIGH_W	    	(120)
#define OSD_MENU_FLHIGH_H			(36)

#define OSD_MENU_FLNORMAL_X			(100)
#define OSD_MENU_FLNORMAL_Y			(104)
#define OSD_MENU_FLNORMAL_W			(120)
#define OSD_MENU_FLNORMAL_H			(36)

#define OSD_MENU_FLLOW_X			(100)
#define OSD_MENU_FLLOW_Y			(158)
#define OSD_MENU_FLLOW_W	    	(120)
#define OSD_MENU_FLLOW_H			(36)

#if defined(FONT_LARGE)
#define OSD_MENU_CONFIRM_X			(16)
#define OSD_MENU_CONFIRM_Y			(70)
#define OSD_MENU_CONFIRM_W	   	 	(320 - OSD_MENU_CONFIRM_X)
#define OSD_MENU_CONFIRM_H			(32)
#else
#define OSD_MENU_CONFIRM_X			(46)
#define OSD_MENU_CONFIRM_Y			(70)
#define OSD_MENU_CONFIRM_W	   	 	(170)
#define OSD_MENU_CONFIRM_H			(32)
#endif

#define OSD_MENU_CLOCKUP_X			(140)
#define OSD_MENU_CLOCKUP_Y			(50)
#define OSD_MENU_CLOCKUP_W			(OSD_MENU_EXIT_W)
#define OSD_MENU_CLOCKUP_H			(OSD_MENU_EXIT_H)

#define OSD_MENU_CLOCKDOWN_X		(OSD_MENU_CLOCKUP_X)
#define OSD_MENU_CLOCKDOWN_Y		(OSD_MENU_CLOCKUP_Y+106)
#define OSD_MENU_CLOCKDOWN_W		(OSD_MENU_EXIT_W)
#define OSD_MENU_CLOCKDOWN_H		(OSD_MENU_EXIT_H)

#define OSD_MENU_CLOCKLEFT_X		(OSD_MENU_EXIT_X)
#define OSD_MENU_CLOCKLEFT_Y		(100)
#define OSD_MENU_CLOCKLEFT_W        (OSD_MENU_EXIT_W)
#define OSD_MENU_CLOCKLEFT_H        (OSD_MENU_EXIT_H)

#define OSD_MENU_CLOCKRIGHT_X		(OSD_MENU_EXIT_X+272)
#define OSD_MENU_CLOCKRIGHT_Y		(OSD_MENU_CLOCKLEFT_Y)
#define OSD_MENU_CLOCKRIGHT_W		(OSD_MENU_EXIT_W)
#define OSD_MENU_CLOCKRIGHT_H		(OSD_MENU_EXIT_H)

#define OSD_MENU_CLOCKOK_X          (OSD_MENU_EXIT_X)
#define OSD_MENU_CLOCKOK_Y          (206)
#define OSD_MENU_CLOCKOK_W			(102)
#define OSD_MENU_CLOCKOK_H          (30)

#define OSD_MENU_CLOCKCANCEL_X		(OSD_MENU_EXIT_X+214)
#define OSD_MENU_CLOCKCANCEL_Y      (206)
#define OSD_MENU_CLOCKCANCEL_W      (102)
#define OSD_MENU_CLOCKCANCEL_H		(30)

#define OSD_QUICKMENU_OK_X          (OSD_MENU_EXIT_X)
#define OSD_QUICKMENU_OK_Y          (196)
#define OSD_QUICKMENU_OK_W          (OSD_MENU_EXIT_W + 88)
#define OSD_QUICKMENU_OK_H          (OSD_MENU_EXIT_H)

#define OSD_QUICKMENU_CANCEL_X		(OSD_QUICKMENU_OK_X+196)
#define OSD_QUICKMENU_CANCEL_Y		(OSD_QUICKMENU_OK_Y)
#define OSD_QUICKMENU_CANCEL_W		(OSD_QUICKMENU_OK_W)
#define OSD_QUICKMENU_CANCEL_H		(OSD_QUICKMENU_OK_H)

#define OSD_MENU_YES_X				(46)
#define OSD_MENU_YES_Y				(155)
#define OSD_MENU_YES_W				(102)
#define OSD_MENU_YES_H				(30)

#define OSD_MENU_NO_X				(190)
#define OSD_MENU_NO_Y				(155)
#define OSD_MENU_NO_W				(102)
#define OSD_MENU_NO_H				(30)

#ifndef OSD_MENU_TITLE_X
#define OSD_MENU_TITLE_X			(58)
#define OSD_MENU_TITLE_Y			(OSD_MENU_EXIT_Y)
#define OSD_MENU_TITLE_W       		(160)
#define OSD_MENU_TITLE_H			(OSD_MENU_EXIT_H)
#endif
#define OSD_MENU_ITEM_X				(OSD_MENU_TITLE_X - 4)
#define OSD_MENU_ITEM_Y				(OSD_MENU_UP_Y)
#define OSD_MENU_ITEM_W				(OSD_MENU_TITLE_W-30)
#define OSD_MENU_ITEM_H				(OSD_MENU_EXIT_H)

//Quik Menu Interval
#define OSD_QUICK_ITEMX_INTERVAL	(20)
#define OSD_QUICK_ITEMY_INTERVAL	(15)

//Main Menu Interval
#define OSD_MENU_ITEM_INTERVAL		(22)

//Sub Menu Interval
#define OSD_MENU_SUBITEM2X_INTERVAL	(42)
#define OSD_MENU_SUBITEM4X_INTERVAL	(48)
#define OSD_MENU_SUBITEM4Y_INTERVAL	(30)
#define OSD_MENU_SUBITEM6X_INTERVAL	(32)
#define OSD_MENU_SUBITEM6Y_INTERVAL	(23)

#define OSD_Y_BORDER 				(0)
#define OSD_X_BORDER 				(50)

//Quick Menu
#define OSD_QUICK_MENU_X			(30)
#define OSD_QUICK_MENU_Y			(210)
#define OSD_QUICK_MENU_W			(120)
#define OSD_QUICK_MENU_H			(30)

#define OSD_QUICK_SLIDESHOW_X		(170)
#define OSD_QUICK_SLIDESHOW_Y		(210)
#define OSD_QUICK_SLIDESHOW_W		(120)
#define OSD_QUICK_SLIDESHOW_H		(30)

#define OSD_QUICKMENU0_X			(30)
#define OSD_QUICKMENU0_Y			(60)
#define OSD_QUICKMENU0_W			(120)
#define OSD_QUICKMENU0_H			(30)

#define OSD_QUICKMENU1_X			(170)
#define OSD_QUICKMENU1_Y			(60)
#define OSD_QUICKMENU1_W			(120)
#define OSD_QUICKMENU1_H			(30)

#define OSD_QUICKMENU2_X			(30)
#define OSD_QUICKMENU2_Y			(105)
#define OSD_QUICKMENU2_W			(120)
#define OSD_QUICKMENU2_H			(30)

#define OSD_QUICKMENU3_X			(170)
#define OSD_QUICKMENU3_Y			(105)
#define OSD_QUICKMENU3_W			(120)
#define OSD_QUICKMENU3_H			(30)

#define OSD_QUICKMENU4_X			(30)
#define OSD_QUICKMENU4_Y            (150)
#define OSD_QUICKMENU4_W			(120)
#define OSD_QUICKMENU4_H			(30)

#define OSD_QUICKMENU5_X			(170)
#define OSD_QUICKMENU5_Y			(150)
#define OSD_QUICKMENU5_W			(120)
#define OSD_QUICKMENU5_H			(30)

//Main Menu
#define OSD_MAINMENU0_X				(54)
#define OSD_MAINMENU0_Y				(49)
#define OSD_MAINMENU0_W	       		(130)
#define OSD_MAINMENU0_H				(32)

#define OSD_MAINMENU1_X				(54)
#define OSD_MAINMENU1_Y				(103)
#define OSD_MAINMENU1_W	       		(130)
#define OSD_MAINMENU1_H				(32)

#define OSD_MAINMENU2_X				(54)
#define OSD_MAINMENU2_Y         	(157)
#define OSD_MAINMENU2_W		    	(130)
#define OSD_MAINMENU2_H				(32)

//Sub Menu
#define OSD_SUBMENU20_X				(46)
#define OSD_SUBMENU20_Y				(105)
#define OSD_SUBMENU20_W				(102)
#define OSD_SUBMENU20_H				(30)

#define OSD_SUBMENU21_X				(190)
#define OSD_SUBMENU21_Y				(105)
#define OSD_SUBMENU21_W	       		(102)
#define OSD_SUBMENU21_H				(30)

#define OSD_SUBMENU40_X				(40)
#define OSD_SUBMENU40_Y             (80)
#define OSD_SUBMENU40_W				(102)
#define OSD_SUBMENU40_H				(30)

#define OSD_SUBMENU41_X				(190)
#define OSD_SUBMENU41_Y				(80)
#define OSD_SUBMENU41_W				(102)
#define OSD_SUBMENU41_H				(30)

#define OSD_SUBMENU42_X				(40)
#define OSD_SUBMENU42_Y				(140)
#define OSD_SUBMENU42_W	       		(102)
#define OSD_SUBMENU42_H				(30)

#define OSD_SUBMENU43_X				(190)
#define OSD_SUBMENU43_Y             (140)
#define OSD_SUBMENU43_W				(102)
#define OSD_SUBMENU43_H				(30)

#define OSD_SUBMENU60_X				(80)
#define OSD_SUBMENU60_Y				(52)
#define OSD_SUBMENU60_W				(102)
#define OSD_SUBMENU60_H				(30)

#define OSD_SUBMENU61_X				(214)
#define OSD_SUBMENU61_Y				(52)
#define OSD_SUBMENU61_W	       		(102)
#define OSD_SUBMENU61_H				(30)

#define OSD_SUBMENU62_X				(80)
#define OSD_SUBMENU62_Y             (105)
#define OSD_SUBMENU62_W				(102)
#define OSD_SUBMENU62_H				(30)

#define OSD_SUBMENU63_X				(214)
#define OSD_SUBMENU63_Y				(105)
#define OSD_SUBMENU63_W				(102)
#define OSD_SUBMENU63_H				(30)

#define OSD_SUBMENU64_X				(80)
#define OSD_SUBMENU64_Y				(158)
#define OSD_SUBMENU64_W	       		(102)
#define OSD_SUBMENU64_H				(30)

#define OSD_SUBMENU65_X				(214)
#define OSD_SUBMENU65_Y             (158)
#define OSD_SUBMENU65_W				(102)
#define OSD_SUBMENU65_H				(30)

// Display Area.
#define POS_DISPLAY_W            	(320)
#define POS_DISPLAY_H           	(240)

// Zoom Camera/Video Icon
#define POS_BUTTON_MENU_X0          (20)
#define POS_BUTTON_MENU_Y0          (160)
#define POS_BUTTON_MENU_W           (60)
#define POS_BUTTON_MENU_H           (40)

#define POS_BUTTON_MENU_2_X0        (5)
#define POS_BUTTON_MENU_2_Y0        (0)
#define POS_BUTTON_MENU_2_W         (40)
#define POS_BUTTON_MENU_2_H         (35)

#define POS_BUTTON_SWITCH_X0        (180)
#define POS_BUTTON_SWITCH_Y0        (160)
#define POS_BUTTON_SWITCH_W         (60)
#define POS_BUTTON_SWITCH_H         (40)

#define POS_BUTTON_FOCUS_X0         (110)
#define POS_BUTTON_FOCUS_Y0         (85)
#define POS_BUTTON_FOCUS_W          (100)
#define POS_BUTTON_FOCUS_H          (75)

#define POS_BUTTON_RET_X0           (40)
#define POS_BUTTON_RET_Y0           (0)
#define POS_BUTTON_RET_W            (240)
#define POS_BUTTON_RET_H            (240)

#define POS_BUTTON_CAP_X0           (80)
#define POS_BUTTON_CAP_Y0           (160)
#define POS_BUTTON_CAP_W            (60)
#define POS_BUTTON_CAP_H            (40)

#define POS_BUTTON_REC_X0           (80)
#define POS_BUTTON_REC_Y0           (160)
#define POS_BUTTON_REC_W            (60)
#define POS_BUTTON_REC_H            (40)

#define POS_BUTTON_CTRLPG_X0        (4)
#define POS_BUTTON_CTRLPG_Y0        (95)
#define POS_BUTTON_CTRLPG_W         (32)
#define POS_BUTTON_CTRLPG_H         (32)

#define POS_BUTTON_PB_X0            (5)
#define POS_BUTTON_PB_Y0            (208)
#define POS_BUTTON_PB_W             (32)
#define POS_BUTTON_PB_H             (32)

#define POS_BUTTON_UP_X0            (110)
#define POS_BUTTON_UP_Y0            (165)
#define POS_BUTTON_UP_W             (100)
#define POS_BUTTON_UP_H             (75)

#define POS_BUTTON_DOWN_X0          (110)
#define POS_BUTTON_DOWN_Y0          (5)
#define POS_BUTTON_DOWN_W           (100)
#define POS_BUTTON_DOWN_H           (75)

#define POS_STATE_CAPSIZE_X0        (220)
#define POS_STATE_CAPSIZE_Y0        (0)
#define POS_STATE_CAPSIZE_W         (24)
#define POS_STATE_CAPSIZE_H         (32)

#define POS_STATE_RECSIZE_X0        (195)
#define POS_STATE_RECSIZE_Y0        (0)
#define POS_STATE_RECSIZE_W         (50)
#define POS_STATE_RECSIZE_H         (32)

#define POS_STATE_FOCUS_X0          (135)
#define POS_STATE_FOCUS_Y0          (95)
#define POS_STATE_FOCUS_W           (24)
#define POS_STATE_FOCUS_H           (50)

#define POS_STATE_MODE_X0           (245)
#define POS_STATE_MODE_Y0           (0)
#define POS_STATE_MODE_W            (24)
#define POS_STATE_MODE_H            (32)

#define POS_STATE_MEDIA_X0          (270)
#define POS_STATE_MEDIA_Y0          (0)
#define POS_STATE_MEDIA_W           (24)
#define POS_STATE_MEDIA_H           (32)

#define POS_STATE_BATRY_X0          STRETCH_W(295)
#define POS_STATE_BATRY_Y0          STRETCH_H(0)
#define POS_STATE_BATRY_W           (24)
#define POS_STATE_BATRY_H           (32)

#define POS_STATE_SCENE_X0          (296)
#define POS_STATE_SCENE_Y0          (36)
#define POS_STATE_SCENE_W           (24)
#define POS_STATE_SCENE_H           (32)

#define POS_STATE_DVS_X0            (296)
#define POS_STATE_DVS_Y0            (134)
#define POS_STATE_DVS_W             (24)
#define POS_STATE_DVS_H             (32)

#define POS_STATE_FD_X0             (296)
#define POS_STATE_FD_Y0             (69)
#define POS_STATE_FD_W              (24)
#define POS_STATE_FD_H              (32)

#define POS_STATE_FOCUS_RANGE_X0    (296)
#define POS_STATE_FOCUS_RANGE_Y0    (102)
#define POS_STATE_FOCUS_RANGE_W     (24)
#define POS_STATE_FOCUS_RANGE_H     (32)

#define POS_STATE_SLFTIME_X0        (296)
#define POS_STATE_SLFTIME_Y0        (168)
#define POS_STATE_SLFTIME_W         (24)
#define POS_STATE_SLFTIME_H         (32)

#define POS_STATE_FLASH_X0          (272)
#define POS_STATE_FLASH_Y0          (45)
#define POS_STATE_FLASH_W           (24)
#define POS_STATE_FLASH_H           (32)

#define POS_STATE_SMILE_X0          (272)
#define POS_STATE_SMILE_Y0          (78)
#define POS_STATE_SMILE_W           (24)
#define POS_STATE_SMILE_H           (32)

#define POS_STATE_BSTSHOT_X0        (272)
#define POS_STATE_BSTSHOT_Y0        (111)
#define POS_STATE_BSTSHOT_W         (24)
#define POS_STATE_BSTSHOT_H         (32)

#define POS_STATE_RECVOLUME_X0        295
#define POS_STATE_RECVOLUME_X0_TVNTSC 320
#define POS_STATE_RECVOLUME_X0_TVPAL  320
#define POS_STATE_RECVOLUME_Y0         70
#define POS_STATE_RECVOLUME_W          24
#define POS_STATE_RECVOLUME_H          32

//////////////////////////////////////////////////////

// Zoom Wide Icon
#define POS_ZOOM_WIDE_X0            (0)
#define POS_ZOOM_WIDE_Y0            (5)
#define POS_ZOOM_WIDE_W             (32)
#define POS_ZOOM_WIDE_H             (56)

// Zoom Tele Icon
#define POS_ZOOM_TELE_X0            (0)
#define POS_ZOOM_TELE_Y0            (92)
#define POS_ZOOM_TELE_W             (32)
#define POS_ZOOM_TELE_H             (56)

// Zoom Bar Pos.
#define OPT_ZOOM_LENGTH             (42)
#define DIG_ZOOM_LENGTH             (15)
#define ZOOM_STEP_W                 (2)

#define POS_ZOOM_BAR_X0             (308)
#define POS_ZOOM_BAR_Y0             (60)
#define POS_ZOOM_BAR_W              (7)
#define POS_ZOOM_BAR_H              (OPT_ZOOM_LENGTH + DIG_ZOOM_LENGTH)*ZOOM_STEP_W    

//////////////////////////////////////////////////////

// Photo playback previous icon
#define POS_JPGPB_PREV_X0                3
#define POS_JPGPB_PREV_Y0               95
#define POS_JPGPB_PREV_W                56
#define POS_JPGPB_PREV_H                56

// Photo playback next icon
#define POS_JPGPB_NEXT_X0              261
#define POS_JPGPB_NEXT_Y0               95
#define POS_JPGPB_NEXT_W                56
#define POS_JPGPB_NEXT_H                56

// Photo playback zoom in icon
#define POS_JPGPB_ZOOMIN_X0              0
#define POS_JPGPB_ZOOMIN_Y0              0
#define POS_JPGPB_ZOOMIN_W               0
#define POS_JPGPB_ZOOMIN_H               0
// Photo playback zoom out icon
#define POS_JPGPB_ZOOMOUT_X0             0
#define POS_JPGPB_ZOOMOUT_Y0             0
#define POS_JPGPB_ZOOMOUT_W              0
#define POS_JPGPB_ZOOMOUT_H              0

// Photo playback rotate icon
#define POS_JPGPB_ROTATE_X0              0
#define POS_JPGPB_ROTATE_Y0              0
#define POS_JPGPB_ROTATE_W               0
#define POS_JPGPB_ROTATE_H               0

// Photo playback option icon
#define POS_JPGPB_OPTION_X0              0
#define POS_JPGPB_OPTION_Y0              0
#define POS_JPGPB_OPTION_W               0
#define POS_JPGPB_OPTION_H               0

// Photo OSD Display area.
#define POS_OSD_DISPLAY_X0               0
#define POS_OSD_DISPLAY_Y0               0
#define POS_OSD_DISPLAY_W              320
#define POS_OSD_DISPLAY_H              240

// Photo playback slide icon
#define POS_SLIDE_PLAY_X0              130
#define POS_SLIDE_PLAY_Y0              190
#define POS_SLIDE_PLAY_W                48
#define POS_SLIDE_PLAY_H                32

// Photo slide previous icon
#define POS_SLIDE_PREV_X0                3
#define POS_SLIDE_PREV_Y0              203
#define POS_SLIDE_PREV_W                48
#define POS_SLIDE_PREV_H                32

// Photo slide next icon
#define POS_SLIDE_NEXT_X0              261
#define POS_SLIDE_NEXT_Y0              203
#define POS_SLIDE_NEXT_W                48
#define POS_SLIDE_NEXT_H                32

// Photo Slide Show State
#define POS_STATE_SLIDE_X0             225
#define POS_STATE_SLIDE_Y0               0
#define POS_STATE_SLIDE_W               32
#define POS_STATE_SLIDE_H               32

// Photo File Name info
#define POS_JPGPB_INFO_X0              50
#define POS_JPGPB_INFO_Y0               5
#define POS_JPGPB_INFO_W              150
#define POS_JPGPB_INFO_H               10

// Photo File Playback info
#define POS_JPGPB_PLAY_X0             200
#define POS_JPGPB_PLAY_Y0              60
#define POS_JPGPB_PLAY_W              130
#define POS_JPGPB_PLAY_H               16

#define POS_JPGPB_INDEX_X0            250
#define POS_JPGPB_INDEX_Y0             40
#define POS_JPGPB_INDEX_W             100
#define POS_JPGPB_INDEX_H              16

//////////////////////////////////////////////////////

// Video Playback Icon
#define POS_MOVPB_OSD_W                 56
#define POS_MOVPB_OSD_H                 56

// Photo playback previous icon
#define POS_MOVPB_PREV_X0                3
#define POS_MOVPB_PREV_Y0               95


// Photo playback next icon
#define POS_MOVPB_NEXT_X0              261
#define POS_MOVPB_NEXT_Y0               95

// Video playback slide icon
#define POS_MOVPB_PLAY_X0              130
#define POS_MOVPB_PLAY_Y0              190

// Video playback forward icon
#define POS_MOVPB_FRWD_X0              261
#define POS_MOVPB_FRWD_Y0              190

// Video playback backward icon
#define POS_MOVPB_BKWD_X0                3
#define POS_MOVPB_BKWD_Y0              190

// Video playback rotate icon
#define POS_MOVPB_ROTATE_X0              0
#define POS_MOVPB_ROTATE_Y0              0

// Video playback option icon
#define POS_MOVPB_OPTION_X0              0
#define POS_MOVPB_OPTION_Y0              0

// Video playback total time
#define POS_MOVPB_PBTIME_X0            260
#define POS_MOVPB_PBTIME_Y0             60
#define POS_MOVPB_PBTIME_W             130
#define POS_MOVPB_PBTIME_H              16

// Video playback Current time
#define POS_MOVPB_CURTIME_X0           160
#define POS_MOVPB_CURTIME_Y0             5
#define POS_MOVPB_CURTIME_W             60
#define POS_MOVPB_CURTIME_H             16

//////////////////////////////////////////////////////

// Thumbnail mode icon

#define POS_CURPAGE_X                  16
#define POS_CURPAGE_Y                 100

#define POS_MAXPAGE_X                  29
#define POS_MAXPAGE_Y                 126

#define POS_PAGE_OFFSET                 9

#define POS_THUMB_NAME_X0             100
#define POS_THUMB_NAME_Y0               8
#define POS_THUMB_NAME_W              140
#define POS_THUMB_NAME_H               20

#define POS_THUMB_INFO_X0              65
#define POS_THUMB_INFO_Y0             214
#define POS_THUMB_INFO_W              120
#define POS_THUMB_INFO_H               20

#define POS_THUMB_TOTALTIME_X0        190
#define POS_THUMB_TOTALTIME_Y0        214
#define POS_THUMB_TOTALTIME_W          70
#define POS_THUMB_TOTALTIME_H          20

#define POS_THUMB_OBLIQUE_X0           14
#define POS_THUMB_OBLIQUE_Y0          125
#define POS_THUMB_OBLIQUE_W            25
#define POS_THUMB_OBLIQUE_H            10

#define POS_THUMBNAIL_MENU_X0          50
#define POS_THUMBNAIL_MENU_Y0           0
#define POS_THUMBNAIL_MENU_W           32
#define POS_THUMBNAIL_MENU_H           32

#define POS_THUMB_MODE_AREA_X0          0
#define POS_THUMB_MODE_AREA_Y0          0
#define POS_THUMB_MODE_AREA_W         320
#define POS_THUMB_MODE_AREA_H          37

#define POS_THUMB_INFO_AREA_X0          0
#define POS_THUMB_INFO_AREA_Y0         37
#define POS_THUMB_INFO_AREA_W          37
#define POS_THUMB_INFO_AREA_H         203

#define THUMB_PER_LINE                  3
#define THUMB_PER_COLUMN                2

#if 0
#define THUMB_HORIZ_GAP                STRETCH_W(12)
#define THUMB_VERTIC_GAP               STRETCH_H(12)

#define POS_THUMB_AREA_X0              STRETCH_W(60)
#define POS_THUMB_AREA_Y0              STRETCH_H(40)
#define POS_THUMB_AREA_W              STRETCH_W(260)
#define POS_THUMB_AREA_H              STRETCH_H(160)
#else 
#define THUMB_HORIZ_GAP               STRETCH_FULL_SCALE_W(12)
#define THUMB_VERTIC_GAP              STRETCH_FULL_SCALE_H(12)

#define POS_THUMB_AREA_X0             STRETCH_FULL_SCALE_W(60)
#define POS_THUMB_AREA_Y0             STRETCH_FULL_SCALE_H(40)
#define POS_THUMB_AREA_W              STRETCH_FULL_SCALE_W(260)
#define POS_THUMB_AREA_H              STRETCH_FULL_SCALE_H(160)
#endif

//#define POS_THUMB_AREA_W(w)              (w - 119)   //STRETCH_W(845 - 80)
//#define POS_THUMB_AREA_H(h)              (h - 89 -36)    //STRETCH_H(480 - 80)   //X 32 

#define POS_THUMNNAIL_W               ((POS_THUMB_AREA_W - THUMB_HORIZ_GAP*(THUMB_PER_LINE+1))/THUMB_PER_LINE)
#define POS_THUMBNAIL_H               ((POS_THUMB_AREA_H - THUMB_VERTIC_GAP*(THUMB_PER_COLUMN+1))/THUMB_PER_COLUMN)

#define POS_THUMB_ID_X(x)             (POS_THUMB_AREA_X0+(THUMB_HORIZ_GAP+POS_THUMNNAIL_W)*x) //+ (THUMB_HORIZ_GAP<<1))
#define POS_THUMB_ID_Y(x)             (POS_THUMB_AREA_Y0+(THUMB_VERTIC_GAP+POS_THUMBNAIL_H)*x)// + (THUMB_VERTIC_GAP<<1))
#define POS_THUMB_TOUCH_W             POS_THUMNNAIL_W+THUMB_HORIZ_GAP
#define POS_THUMB_TOUCH_Y             POS_THUMBNAIL_H+THUMB_VERTIC_GAP

#define POS_THUMBNAIL_MODE_W           32
#define POS_THUMBNAIL_MODE_H           25

#define POS_THUMBNAIL_DSC_X0          240
#define POS_THUMBNAIL_DSC_Y0            7

#define POS_THUMBNAIL_DV_X0           280
#define POS_THUMBNAIL_DV_Y0             7

#define POS_THUMBNAIL_NEXT_PG_X0        8
#define POS_THUMBNAIL_NEXT_PG_Y0      165

#define POS_THUMBNAIL_PREV_PG_X0        8
#define POS_THUMBNAIL_PREV_PG_Y0       50

#define POS_THUMBNAIL_PG_W             25
#define POS_THUMBNAIL_PG_H             25

#define POS_THUMBNAIL_LINE_W           25
#define POS_THUMBNAIL_LINE_H            1
#define POS_THUMBNAIL_LINE0_X0          8
#define POS_THUMBNAIL_LINE0_Y0         90
#define POS_THUMBNAIL_LINE1_X0          8
#define POS_THUMBNAIL_LINE1_Y0        110
#define POS_THUMBNAIL_LINE2_X0          8
#define POS_THUMBNAIL_LINE2_Y0        130
#define POS_THUMBNAIL_LINE3_X0          8
#define POS_THUMBNAIL_LINE3_Y0        150

//HDMI mode
#define POS_HDMI_1080P_BROWSER_OSD_X0         0
#define POS_HDMI_1080P_BROWSER_OSD_Y0         0
#define POS_HDMI_1080P_BROWSER_OSD_W       1920
#define POS_HDMI_1080P_BROWSER_OSD_H        160//320

#define POS_HDMI_1080I_BROWSER_OSD_X0         0
#define POS_HDMI_1080I_BROWSER_OSD_Y0         0
#define POS_HDMI_1080I_BROWSER_OSD_W       1920
#define POS_HDMI_1080I_BROWSER_OSD_H        160

#define POS_HDMI_720P_BROWSER_OSD_X0         0
#define POS_HDMI_720P_BROWSER_OSD_Y0         0
#define POS_HDMI_720P_BROWSER_OSD_W       1280
#define POS_HDMI_720P_BROWSER_OSD_H        108

#define POS_HDMI_480P_BROWSER_OSD_X0         0      // TBD
#define POS_HDMI_480P_BROWSER_OSD_Y0         0
#define POS_HDMI_480P_BROWSER_OSD_W        720
#define POS_HDMI_480P_BROWSER_OSD_H         50

#define POS_HDMI_PLAY_OSD_X0                 0
#define POS_HDMI_PLAY_OSD_Y0                 0
#define POS_HDMI_PLAY_OSD_W                320
#define POS_HDMI_PLAY_OSD_H                240

//TV mode
#define POS_TV_NTSC_BROWSER_OSD_X0           0
#define POS_TV_NTSC_BROWSER_OSD_Y0           0
#define POS_TV_NTSC_BROWSER_OSD_W          720
#define POS_TV_NTSC_BROWSER_OSD_H           70

#define POS_TV_PAL_BROWSER_OSD_X0            0
#define POS_TV_PAL_BROWSER_OSD_Y0            0
#define POS_TV_PAL_BROWSER_OSD_W           720
#define POS_TV_PAL_BROWSER_OSD_H            85

#define POS_TV_PLAY_OSD_X0                   0
#define POS_TV_PLAY_OSD_Y0                   0
#define POS_TV_PLAY_OSD_W                  320
#define POS_TV_PLAY_OSD_H                  240

// String display.
// Storage is not available
#define STR_STORAGE_NOT_AVAILABLE_X0   50
#define STR_STORAGE_NOT_AVAILABLE_Y0  115

// Stand by
#define STR_STANDBY_STATUS_X0         145
#define STR_STANDBY_STATUS_Y0          10

// Warning message
#define STR_WARNING_STATUS_X0          45
#define STR_WARNING_STATUS_Y0          80

// USB status
#define POS_USB_CONNECT_OSD_X0         140
#define POS_USB_CONNECT_OSD_Y0         95
#define POS_USB_CONNECT_OSD_W          39
#define POS_USB_CONNECT_OSD_H          50

#define POS_TEST              (POS_BUTTON_MENU_X0 ,    POS_BUTTON_MENU_Y0 ,      POS_BUTTON_MENU_W ,     POS_BUTTON_MENU_H )

//Menu
#define POS_MENU_EXIT         {        OSD_MENU_EXIT_X ,       OSD_MENU_EXIT_Y ,        OSD_MENU_EXIT_W ,       OSD_MENU_EXIT_H }
#define POS_MENU_UP           {          OSD_MENU_UP_X ,         OSD_MENU_UP_Y ,          OSD_MENU_UP_W ,         OSD_MENU_UP_H }
#define POS_MENU_DOWN         {        OSD_MENU_DOWN_X ,       OSD_MENU_DOWN_Y ,        OSD_MENU_DOWN_W ,       OSD_MENU_DOWN_H }
#define POS_MENU_LEFT         {        OSD_MENU_LEFT_X ,       OSD_MENU_LEFT_Y ,        OSD_MENU_LEFT_W ,       OSD_MENU_LEFT_H }
#define POS_MENU_RIGHT        {       OSD_MENU_RIGHT_X ,      OSD_MENU_RIGHT_Y ,       OSD_MENU_RIGHT_W ,      OSD_MENU_RIGHT_H }
#define POS_MENU_CATA         {        OSD_MENU_CATA_X ,       OSD_MENU_CATA_Y ,        OSD_MENU_CATA_W ,       OSD_MENU_CATA_H }
#define POS_MENU_EVDECREASE   {  OSD_MENU_EVDECREASE_X , OSD_MENU_EVDECREASE_Y ,  OSD_MENU_EVDECREASE_W , OSD_MENU_EVDECREASE_H }
#define POS_MENU_EVINCREASE   {  OSD_MENU_EVINCREASE_X , OSD_MENU_EVINCREASE_Y ,  OSD_MENU_EVINCREASE_W , OSD_MENU_EVINCREASE_H }
#define POS_MENU_FLHIGH       {      OSD_MENU_FLHIGH_X ,     OSD_MENU_FLHIGH_Y ,      OSD_MENU_FLHIGH_W ,     OSD_MENU_FLHIGH_H }
#define POS_MENU_FLNORMAL     {    OSD_MENU_FLNORMAL_X ,   OSD_MENU_FLNORMAL_Y ,    OSD_MENU_FLNORMAL_W ,   OSD_MENU_FLNORMAL_H }
#define POS_MENU_FLLOW        {       OSD_MENU_FLLOW_X ,      OSD_MENU_FLLOW_Y ,       OSD_MENU_FLLOW_W ,      OSD_MENU_FLLOW_H }
#define POS_MENU_CONFIRM      {     OSD_MENU_CONFIRM_X ,    OSD_MENU_CONFIRM_Y ,     OSD_MENU_CONFIRM_W ,    OSD_MENU_CONFIRM_H }
#define POS_MENU_CLOCKUP      {     OSD_MENU_CLOCKUP_X ,    OSD_MENU_CLOCKUP_Y ,     OSD_MENU_CLOCKUP_W ,    OSD_MENU_CLOCKUP_H }
#define POS_MENU_CLOCKDOWN    {   OSD_MENU_CLOCKDOWN_X ,  OSD_MENU_CLOCKDOWN_Y ,   OSD_MENU_CLOCKDOWN_W ,  OSD_MENU_CLOCKDOWN_H }
#define POS_MENU_CLOCKLEFT    {   OSD_MENU_CLOCKLEFT_X ,  OSD_MENU_CLOCKLEFT_Y ,   OSD_MENU_CLOCKLEFT_W ,  OSD_MENU_CLOCKLEFT_H }
#define POS_MENU_CLOCKRIGHT   {  OSD_MENU_CLOCKRIGHT_X , OSD_MENU_CLOCKRIGHT_Y ,  OSD_MENU_CLOCKRIGHT_W , OSD_MENU_CLOCKRIGHT_H }
#define POS_MENU_CLOCKOK      {     OSD_MENU_CLOCKOK_X ,    OSD_MENU_CLOCKOK_Y ,     OSD_MENU_CLOCKOK_W ,    OSD_MENU_CLOCKOK_H }
#define POS_MENU_CLOCKCANCEL  { OSD_MENU_CLOCKCANCEL_X ,OSD_MENU_CLOCKCANCEL_Y , OSD_MENU_CLOCKCANCEL_W ,OSD_MENU_CLOCKCANCEL_H }
#define POS_QUICKMENU_OK      {     OSD_QUICKMENU_OK_X ,    OSD_QUICKMENU_OK_Y ,     OSD_QUICKMENU_OK_W ,    OSD_QUICKMENU_OK_H }
#define POS_QUICKMENU_CANCEL  { OSD_QUICKMENU_CANCEL_X ,OSD_QUICKMENU_CANCEL_Y , OSD_QUICKMENU_CANCEL_W ,OSD_QUICKMENU_CANCEL_H }
#define POS_MENU_YES          {         OSD_MENU_YES_X ,        OSD_MENU_YES_Y ,         OSD_MENU_YES_W ,        OSD_MENU_YES_H }
#define POS_MENU_NO           {          OSD_MENU_NO_X ,         OSD_MENU_NO_Y ,          OSD_MENU_NO_W ,         OSD_MENU_NO_H }
#define POS_MENU_TITLE        {       OSD_MENU_TITLE_X ,      OSD_MENU_TITLE_Y ,       OSD_MENU_TITLE_W ,      OSD_MENU_TITLE_H }
#define POS_MENU_ITEM         {        OSD_MENU_ITEM_X ,       OSD_MENU_ITEM_Y ,        OSD_MENU_ITEM_W ,       OSD_MENU_ITEM_H }

//Quick Menu                                               
#define POS_MENU_MENU         {       OSD_QUICK_MENU_X ,      OSD_QUICK_MENU_Y ,       OSD_QUICK_MENU_W ,      OSD_QUICK_MENU_H }
#define POS_MENU_SLIDESHOW    {  OSD_QUICK_SLIDESHOW_X , OSD_QUICK_SLIDESHOW_Y ,  OSD_QUICK_SLIDESHOW_W , OSD_QUICK_SLIDESHOW_H }
#define POS_QUICKMENU0        {       OSD_QUICKMENU0_X ,      OSD_QUICKMENU0_Y ,       OSD_QUICKMENU0_W ,      OSD_QUICKMENU0_H }
#define POS_QUICKMENU1        {       OSD_QUICKMENU1_X ,      OSD_QUICKMENU1_Y ,       OSD_QUICKMENU1_W ,      OSD_QUICKMENU1_H }
#define POS_QUICKMENU2        {       OSD_QUICKMENU2_X ,      OSD_QUICKMENU2_Y ,       OSD_QUICKMENU2_W ,      OSD_QUICKMENU2_H }
#define POS_QUICKMENU3        {       OSD_QUICKMENU3_X ,      OSD_QUICKMENU3_Y ,       OSD_QUICKMENU3_W ,      OSD_QUICKMENU3_H }
#define POS_QUICKMENU4        {       OSD_QUICKMENU4_X ,      OSD_QUICKMENU4_Y ,       OSD_QUICKMENU4_W ,      OSD_QUICKMENU4_H }
#define POS_QUICKMENU5        {       OSD_QUICKMENU5_X ,      OSD_QUICKMENU5_Y ,       OSD_QUICKMENU5_W ,      OSD_QUICKMENU5_H }
                                                                                                                                 
//Main Menu                                                                                                                      
#define POS_MAINMENU0         {        OSD_MAINMENU0_X ,       OSD_MAINMENU0_Y ,        OSD_MAINMENU0_W ,       OSD_MAINMENU0_H }
#define POS_MAINMENU1         {        OSD_MAINMENU1_X ,       OSD_MAINMENU1_Y ,        OSD_MAINMENU1_W ,       OSD_MAINMENU1_H }
#define POS_MAINMENU2         {        OSD_MAINMENU2_X ,       OSD_MAINMENU2_Y ,        OSD_MAINMENU2_W ,       OSD_MAINMENU2_H }
                                                                                  
//Sub Menu                                                                        
#define POS_SUBMENU20         {        OSD_SUBMENU20_X ,       OSD_SUBMENU20_Y ,        OSD_SUBMENU20_W ,      OSD_SUBMENU20_H  }
#define POS_SUBMENU21         {        OSD_SUBMENU21_X ,       OSD_SUBMENU21_Y ,        OSD_SUBMENU21_W ,      OSD_SUBMENU21_H  }
                                                                                                                                 
#define POS_SUBMENU40         {        OSD_SUBMENU40_X ,       OSD_SUBMENU40_Y ,        OSD_SUBMENU40_W ,      OSD_SUBMENU40_H  }
#define POS_SUBMENU41         {        OSD_SUBMENU41_X ,       OSD_SUBMENU41_Y ,        OSD_SUBMENU41_W ,      OSD_SUBMENU41_H  }
#define POS_SUBMENU42         {        OSD_SUBMENU42_X ,       OSD_SUBMENU42_Y ,        OSD_SUBMENU42_W ,      OSD_SUBMENU42_H  }
#define POS_SUBMENU43         {        OSD_SUBMENU43_X ,       OSD_SUBMENU43_Y ,        OSD_SUBMENU43_W ,      OSD_SUBMENU43_H  }
                                                                                                                                 
#define POS_SUBMENU60         {        OSD_SUBMENU60_X ,       OSD_SUBMENU60_Y ,        OSD_SUBMENU60_W ,      OSD_SUBMENU60_H  }
#define POS_SUBMENU61         {        OSD_SUBMENU61_X ,       OSD_SUBMENU61_Y ,        OSD_SUBMENU61_W ,      OSD_SUBMENU61_H  }
#define POS_SUBMENU62         {        OSD_SUBMENU62_X ,       OSD_SUBMENU62_Y ,        OSD_SUBMENU62_W ,      OSD_SUBMENU62_H  }
#define POS_SUBMENU63         {        OSD_SUBMENU63_X ,       OSD_SUBMENU63_Y ,        OSD_SUBMENU63_W ,      OSD_SUBMENU63_H  }
#define POS_SUBMENU64         {        OSD_SUBMENU64_X ,       OSD_SUBMENU64_Y ,        OSD_SUBMENU64_W ,      OSD_SUBMENU64_H  }
#define POS_SUBMENU65         {        OSD_SUBMENU65_X ,       OSD_SUBMENU65_Y ,        OSD_SUBMENU65_W ,      OSD_SUBMENU65_H  }
                                                                                                                                 
// DSC Preview                                                                                                                   
#define POS_BUTTON_CAPTURE    {      POS_BUTTON_CAP_X0 ,     POS_BUTTON_CAP_Y0 ,       POS_BUTTON_CAP_W ,      POS_BUTTON_CAP_H }
#define POS_BUTTON_RECORD     {      POS_BUTTON_REC_X0 ,     POS_BUTTON_REC_Y0 ,       POS_BUTTON_REC_W ,      POS_BUTTON_REC_H }
#define POS_BUTTON_MENU       {     POS_BUTTON_MENU_X0 ,    POS_BUTTON_MENU_Y0 ,      POS_BUTTON_MENU_W ,     POS_BUTTON_MENU_H }
#define POS_BUTTON_CTRLPG     {   POS_BUTTON_CTRLPG_X0 ,  POS_BUTTON_CTRLPG_Y0 ,    POS_BUTTON_CTRLPG_W ,   POS_BUTTON_CTRLPG_H }
#define POS_BUTTON_PBSWITCH   {       POS_BUTTON_PB_X0 ,      POS_BUTTON_PB_Y0 ,        POS_BUTTON_PB_W ,       POS_BUTTON_PB_H }
#define POS_BUTTON_MODESWITCH {   POS_BUTTON_SWITCH_X0 ,  POS_BUTTON_SWITCH_Y0 ,    POS_BUTTON_SWITCH_W ,   POS_BUTTON_SWITCH_H }
#define POS_BUTTON_FOCUS      {    POS_BUTTON_FOCUS_X0 ,   POS_BUTTON_FOCUS_Y0 ,     POS_BUTTON_FOCUS_W ,    POS_BUTTON_FOCUS_H }
#define POS_BUTTON_MAINPG     {      POS_BUTTON_RET_X0 ,     POS_BUTTON_RET_Y0 ,       POS_BUTTON_RET_W ,      POS_BUTTON_RET_H }
#define POS_BUTTON_UP         {       POS_BUTTON_UP_X0 ,      POS_BUTTON_UP_Y0 ,        POS_BUTTON_UP_W ,       POS_BUTTON_UP_H }
#define POS_BUTTON_DOWN       {     POS_BUTTON_DOWN_X0 ,    POS_BUTTON_DOWN_Y0 ,      POS_BUTTON_DOWN_W ,     POS_BUTTON_DOWN_H }

// status                                                                                                                        
#define POS_STATE_RECSIZE     {   POS_STATE_RECSIZE_X0 ,  POS_STATE_RECSIZE_Y0 ,    POS_STATE_RECSIZE_W ,   POS_STATE_RECSIZE_H }
#define POS_STATE_CAPTSIZE    {   POS_STATE_CAPSIZE_X0 ,  POS_STATE_CAPSIZE_Y0 ,    POS_STATE_CAPSIZE_W ,   POS_STATE_CAPSIZE_H }
#define POS_STATE_FOCUS       {     POS_STATE_FOCUS_X0 ,    POS_STATE_FOCUS_Y0 ,      POS_STATE_FOCUS_W ,     POS_STATE_FOCUS_H }
#define POS_STATE_MODE        {      POS_STATE_MODE_X0 ,     POS_STATE_MODE_Y0 ,       POS_STATE_MODE_W ,      POS_STATE_MODE_H }
#define POS_STATE_MEDIA       {     POS_STATE_MEDIA_X0 ,    POS_STATE_MEDIA_Y0 ,      POS_STATE_MEDIA_W ,     POS_STATE_MEDIA_H }
#define POS_STATE_MEDIA_TVNTSC       {     POS_STATE_MEDIA_X0_TVNTSC ,    POS_STATE_MEDIA_Y0 ,      POS_STATE_MEDIA_W ,     POS_STATE_MEDIA_H }
#define POS_STATE_MEDIA_TVPAL        {     POS_STATE_MEDIA_X0_TVPAL  ,    POS_STATE_MEDIA_Y0 ,      POS_STATE_MEDIA_W ,     POS_STATE_MEDIA_H }
#define POS_STATE_BATTERY     {     POS_STATE_BATRY_X0 ,    POS_STATE_BATRY_Y0 ,      POS_STATE_BATRY_W ,     POS_STATE_BATRY_H }
#define POS_STATE_BATTERY_TVNTSC     {     POS_STATE_BATRY_X0_TVNTSC ,    POS_STATE_BATRY_Y0 ,      POS_STATE_BATRY_W ,     POS_STATE_BATRY_H }
#define POS_STATE_BATTERY_TVPAL      {     POS_STATE_BATRY_X0_TVPAL  ,    POS_STATE_BATRY_Y0 ,      POS_STATE_BATRY_W ,     POS_STATE_BATRY_H }
                                                                                                                                 
// Setting Display                                                                                                               
#define POS_STATE_SCENE       {     POS_STATE_SCENE_X0 ,    POS_STATE_SCENE_Y0 ,      POS_STATE_SCENE_W ,     POS_STATE_SCENE_H }
#define POS_STATE_SCENE_TVNTSC       {     POS_STATE_SCENE_X0_TVNTSC ,    POS_STATE_SCENE_Y0 ,      POS_STATE_SCENE_W ,     POS_STATE_SCENE_H }
#define POS_STATE_SCENE_TVPAL        {     POS_STATE_SCENE_X0_TVPAL  ,    POS_STATE_SCENE_Y0 ,      POS_STATE_SCENE_W ,     POS_STATE_SCENE_H }
#define POS_STATE_DVS         {       POS_STATE_DVS_X0 ,      POS_STATE_DVS_Y0 ,        POS_STATE_DVS_W ,       POS_STATE_DVS_H }
#define POS_STATE_SMILE       {     POS_STATE_SMILE_X0 ,    POS_STATE_SMILE_Y0 ,      POS_STATE_SMILE_W ,     POS_STATE_SMILE_H }
#define POS_STATE_FD          {        POS_STATE_FD_X0 ,       POS_STATE_FD_Y0 ,         POS_STATE_FD_W ,        POS_STATE_FD_H }
#define POS_STATE_FOCUS_RANGE {POS_STATE_FOCUS_RANGE_X0,POS_STATE_FOCUS_RANGE_Y0,POS_STATE_FOCUS_RANGE_W,POS_STATE_FOCUS_RANGE_H}
                                                                                                                                 
#define POS_STATE_FLASH       {     POS_STATE_FLASH_X0 ,    POS_STATE_FLASH_Y0 ,      POS_STATE_FLASH_W ,     POS_STATE_FLASH_H }

#define POS_STATE_SELFTIMER   {   POS_ICON_SELFTIMER_X ,  POS_ICON_SELFTIMER_Y ,    POS_STATE_SLFTIME_W ,   POS_STATE_SLFTIME_H }
#define POS_STATE_BURSTSHOT   {   165 ,                                      0 ,    POS_STATE_BSTSHOT_W ,   POS_STATE_BSTSHOT_H }

#define POS_STATE_RECVOLUME   { POS_STATE_RECVOLUME_X0 ,POS_STATE_RECVOLUME_Y0 ,  POS_STATE_RECVOLUME_W , POS_STATE_RECVOLUME_H }
#define POS_STATE_RECVOLUME_TVNTSC   { POS_STATE_RECVOLUME_X0_TVNTSC ,POS_STATE_RECVOLUME_Y0 ,  POS_STATE_RECVOLUME_W , POS_STATE_RECVOLUME_H }
#define POS_STATE_RECVOLUME_TVPAL   { POS_STATE_RECVOLUME_X0_TVPAL ,POS_STATE_RECVOLUME_Y0 ,  POS_STATE_RECVOLUME_W , POS_STATE_RECVOLUME_H }

                                                                                                                                 
// Zoom Control Icon                                                                                                             
#define POS_BUTTON_WIDE       {       POS_ZOOM_WIDE_X0 ,      POS_ZOOM_WIDE_Y0 ,        POS_ZOOM_WIDE_W ,       POS_ZOOM_WIDE_H }
#define POS_BUTTON_TELE       {       POS_ZOOM_TELE_X0 ,      POS_ZOOM_TELE_Y0 ,        POS_ZOOM_TELE_W ,       POS_ZOOM_TELE_H }
#define POS_ZOOM_BAR          {        POS_ZOOM_BAR_X0 ,       POS_ZOOM_BAR_Y0 ,         POS_ZOOM_BAR_W ,        POS_ZOOM_BAR_H }

// Thumbnail Mode
#define POS_BUTTON_MENU_2     {   POS_BUTTON_MENU_2_X0 ,  POS_BUTTON_MENU_2_Y0 ,    POS_BUTTON_MENU_2_W ,   POS_BUTTON_MENU_2_H }
#define POS_THUMB_NAME        {      POS_THUMB_NAME_X0 ,     POS_THUMB_NAME_Y0 ,       POS_THUMB_NAME_W ,      POS_THUMB_NAME_H }
#define POS_THUMB_INFO        {      POS_THUMB_INFO_X0 ,     POS_THUMB_INFO_Y0 ,       POS_THUMB_INFO_W ,      POS_THUMB_INFO_H }
#define POS_THUMB_TIME        { POS_THUMB_TOTALTIME_X0 ,POS_THUMB_TOTALTIME_Y0 ,  POS_THUMB_TOTALTIME_W , POS_THUMB_TOTALTIME_H }
#define POS_THUMB_OBLIQUE     {   POS_THUMB_OBLIQUE_X0 ,  POS_THUMB_OBLIQUE_Y0 ,    POS_THUMB_OBLIQUE_W ,   POS_THUMB_OBLIQUE_H }
#define POS_THUMB_PGUP        {          OSD_MENU_UP_X ,         OSD_MENU_UP_Y ,          OSD_MENU_UP_W ,         OSD_MENU_UP_H }
#define POS_THUMB_PGDOWN      {        OSD_MENU_DOWN_X ,       OSD_MENU_DOWN_Y ,        OSD_MENU_DOWN_W ,       OSD_MENU_DOWN_H }
#define POS_THUMB_AREA        {      POS_THUMB_AREA_X0 ,     POS_THUMB_AREA_Y0 ,       POS_THUMB_AREA_W ,      POS_THUMB_AREA_H }
#define POS_THUMB_FOCUS		  POS_THUMB_AREA

//HDMI mode
#define POS_HDMI_1080P_BROWSER_OSD  {POS_HDMI_1080P_BROWSER_OSD_X0 ,POS_HDMI_1080P_BROWSER_OSD_Y0,  POS_HDMI_1080P_BROWSER_OSD_W, POS_HDMI_1080P_BROWSER_OSD_H} 
#define POS_HDMI_1080I_BROWSER_OSD  {POS_HDMI_1080I_BROWSER_OSD_X0 ,POS_HDMI_1080I_BROWSER_OSD_Y0,  POS_HDMI_1080I_BROWSER_OSD_W, POS_HDMI_1080I_BROWSER_OSD_H} 
#define POS_HDMI_720P_BROWSER_OSD   {POS_HDMI_720P_BROWSER_OSD_X0 ,POS_HDMI_720P_BROWSER_OSD_Y0,  POS_HDMI_720P_BROWSER_OSD_W, POS_HDMI_720P_BROWSER_OSD_H}
#define POS_HDMI_PLAY_OSD     		{POS_HDMI_PLAY_OSD_X0 ,POS_HDMI_PLAY_OSD_Y0,  POS_HDMI_PLAY_OSD_W, POS_HDMI_PLAY_OSD_H} 

//TV mode
#define POS_TV_NTSC_BROWSER_OSD  {POS_TV_NTSC_BROWSER_OSD_X0 ,POS_TV_NTSC_BROWSER_OSD_Y0,  POS_TV_NTSC_BROWSER_OSD_W, POS_TV_NTSC_BROWSER_OSD_H} 
#define POS_TV_PAL_BROWSER_OSD   {POS_TV_PAL_BROWSER_OSD_X0 ,POS_TV_PAL_BROWSER_OSD_Y0,  POS_TV_PAL_BROWSER_OSD_W, POS_TV_PAL_BROWSER_OSD_H}
#define POS_TV_PLAY_OSD     	 {POS_TV_PLAY_OSD_X0 ,POS_TV_PLAY_OSD_Y0,  POS_TV_PLAY_OSD_W, POS_TV_PLAY_OSD_H} 

// Photo playback
#define POS_BUTTON_EXIT          POS_MENU_EXIT
#define POS_OSD_DISPLAY_AREA     {   POS_OSD_DISPLAY_X0 ,   POS_OSD_DISPLAY_Y0 ,      POS_OSD_DISPLAY_W ,    POS_OSD_DISPLAY_H  }

#define POS_BUTTON_JPGPB_PREV    {    POS_JPGPB_PREV_X0 ,    POS_JPGPB_PREV_Y0 ,       POS_JPGPB_PREV_W ,     POS_JPGPB_PREV_H  }
#define POS_BUTTON_JPGPB_NEXT    {    POS_JPGPB_NEXT_X0 ,    POS_JPGPB_NEXT_Y0 ,       POS_JPGPB_NEXT_W ,     POS_JPGPB_NEXT_H  }
#define POS_BUTTON_JPGPB_ZOOMIN  {  POS_JPGPB_ZOOMIN_X0 ,  POS_JPGPB_ZOOMIN_Y0 ,     POS_JPGPB_ZOOMIN_W ,   POS_JPGPB_ZOOMIN_H  }
#define POS_BUTTON_JPGPB_ZOOMOUT { POS_JPGPB_ZOOMOUT_X0 , POS_JPGPB_ZOOMOUT_Y0 ,    POS_JPGPB_ZOOMOUT_W ,  POS_JPGPB_ZOOMOUT_H  }
#define POS_BUTTON_JPGPB_ROTATE  {  POS_JPGPB_ROTATE_X0 ,  POS_JPGPB_ROTATE_Y0 ,     POS_JPGPB_ROTATE_W ,   POS_JPGPB_ROTATE_H  }
#define POS_BUTTON_JPGPB_OPTION  {  POS_JPGPB_OPTION_X0 ,  POS_JPGPB_OPTION_Y0 ,     POS_JPGPB_OPTION_W ,   POS_JPGPB_OPTION_H  }

#define POS_BUTTON_SLIDE_PLAY    {    POS_SLIDE_PLAY_X0 ,    POS_SLIDE_PLAY_Y0 ,       POS_SLIDE_PLAY_W ,     POS_SLIDE_PLAY_H  }
#define POS_BUTTON_SLIDE_PREV    {    POS_SLIDE_PREV_X0 ,    POS_SLIDE_PREV_Y0 ,       POS_SLIDE_PREV_W ,     POS_SLIDE_PREV_H  }
#define POS_BUTTON_SLIDE_NEXT    {    POS_SLIDE_NEXT_X0 ,    POS_SLIDE_NEXT_Y0 ,       POS_SLIDE_NEXT_W ,     POS_SLIDE_NEXT_H  }

#define POS_STATE_JPGPB          {   POS_STATE_SLIDE_X0 ,   POS_STATE_SLIDE_Y0 ,      POS_STATE_SLIDE_W ,    POS_STATE_SLIDE_H  }
#define POS_STATE_CURRENTTIME    { POS_MOVPB_CURTIME_X0 , POS_MOVPB_CURTIME_Y0 ,    POS_MOVPB_CURTIME_W ,  POS_MOVPB_CURTIME_H  }
#define POS_STATE_TOTALTIME      {  POS_MOVPB_PBTIME_X0 ,  POS_MOVPB_PBTIME_Y0 ,     POS_MOVPB_PBTIME_W ,   POS_MOVPB_PBTIME_H  }
#define POS_STATE_FILEINFO       {    POS_JPGPB_INFO_X0 ,    POS_JPGPB_INFO_Y0 ,       POS_JPGPB_INFO_W ,     POS_JPGPB_INFO_H  }
#define POS_STATE_FILEINDEX      {   POS_JPGPB_INDEX_X0 ,   POS_JPGPB_INDEX_Y0 ,      POS_JPGPB_INDEX_W ,    POS_JPGPB_INDEX_H  }

// Movie playback
#define POS_BUTTON_MOVPB_PREV    {    POS_MOVPB_PREV_X0 ,    POS_MOVPB_PREV_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_BKWD    {    POS_MOVPB_BKWD_X0 ,    POS_MOVPB_BKWD_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_PLAY    {    POS_MOVPB_PLAY_X0 ,    POS_MOVPB_PLAY_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_FRWD    {    POS_MOVPB_FRWD_X0 ,    POS_MOVPB_FRWD_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_NEXT    {    POS_MOVPB_NEXT_X0 ,    POS_MOVPB_NEXT_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_ROTATE  {  POS_MOVPB_ROTATE_X0 ,  POS_MOVPB_ROTATE_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }
#define POS_BUTTON_MOVPB_OPTION  {  POS_MOVPB_OPTION_X0 ,  POS_MOVPB_OPTION_Y0 ,        POS_MOVPB_OSD_W ,  POS_MOVPB_OSD_H  }

//USB status
#define POS_STATE_USB_CONNECT    { POS_USB_CONNECT_OSD_X0 , POS_USB_CONNECT_OSD_Y0 ,        POS_USB_CONNECT_OSD_W ,  POS_USB_CONNECT_OSD_H  }

#define TOUCH_OFFSET         3
/*
#define TOUCH_RANGE(iRECT)   ((iRECT.uiLeft > TOUCH_OFFSET)?(iRECT.uiLeft - TOUCH_OFFSET):0, \
                              (iRECT.uiTop  > TOUCH_OFFSET)?(iRECT.uiTop  - TOUCH_OFFSET):0, \
                              (iRECT.uiLeft+iRECT.uiWidth+TOUCH_OFFSET > DISP_WIDTH)?1:0, \
                              (iRECT.uiTop+iRECT.uiHeight+TOUCH_OFFSET > DISP_HEIGHT)?1:0 )
*/
#define TOUCH_RANGE(iRECT)   {iRECT.uiLeft+5,  iRECT.uiTop+5, iRECT.uiWidth+5, iRECT.uiHeight+5}

#include "CarDV_IconPosition.h"

/*===========================================================================
 * Extern variable
 *===========================================================================*/ 

extern POINT	gPoint_Menu;
extern POINT	gPoint_Size;
extern POINT	gPoint_Flash;
extern POINT	gPoint_Media;
extern POINT	gPoint_SmileDetection;
extern POINT	gPoint_Mode;
extern POINT	gPoint_REC_PB;

#endif//_ICON_POSITION_H_
