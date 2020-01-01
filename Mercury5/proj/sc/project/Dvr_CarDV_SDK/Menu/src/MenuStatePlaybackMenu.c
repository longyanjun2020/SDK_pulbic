/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_browser.h"
#include "ahc_media.h"
#include "ahc_warningmsg.h"
#include "ahc_macro.h"
#include "ahc_general.h"
#include "ahc_gui.h"
#include "ahc_common.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_utility.h"
#include "ahc_parameter.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "ahc_mimf.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "MenuCommon.h"
#include "MenuSetting.h"
#include "MenuTouchButton.h"
#include "MenuStatePlaybackMenu.h"
#include "MenuStatePlaybackMenu_inc.h"
#include "MenuDrawingPlaybackFunc.h"
#include "MenuDrawCommon.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "statebrowserfunc.h"
#include "mediaplaybackctrl.h"

/*===========================================================================
 * Local function
 *===========================================================================*/

UINT32 	 SubMenuEventHandler_Volume(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);
UINT32   MenuGetDefault_Playback(PSMENUSTRUCT pMenu);

AHC_BOOL MenuItemCut(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemRotate(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemResize(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemTrimming(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSlideShowFiles(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSlideShowEffects(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemSlideShowMusic(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemVolume(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemPlaybackVideoType(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global varible : Touch Menu
 *===========================================================================*/


/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern SMENUITEM 	sItemDelete;
extern SMENUITEM 	sItemProtect;
extern SMENUITEM	sItemConfirmOne_Yes;
extern SMENUITEM	sItemConfirmOne_No;

extern AHC_BOOL 	Deleting_InBrowser;
extern AHC_BOOL 	Protecting_InBrowser;
extern AHC_BOOL     bRefreshBrowser;
extern AHC_BOOL 	m_ubAtMenuTab;
extern AHC_BOOL		m_ubPlaybackRearCam;

/*===========================================================================
 * Global variable : Menu
 *===========================================================================*/ 
 
SMENUSTRUCT sMainMenuPlayback;

SMENUSTRUCT sSubCut;
SMENUSTRUCT sSubRotate;
SMENUSTRUCT sSubResize;
SMENUSTRUCT sSubTrimming;
SMENUSTRUCT sSubSlideShowFiles;
SMENUSTRUCT sSubSlideShowEffects;
SMENUSTRUCT sSubSlideShowMusic;
SMENUSTRUCT sSubVolume;
SMENUSTRUCT sSubPlaybackVideoType;

/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/ 

// Cut
#if (MENU_PLAYBACK_QM_CUT_EN)
SMENUITEM sItemQM_Cut         		= { ITEMID_CUT, &bmIcon_Cut, IDS_DS_CUT,	&sSubCut, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemQM_Cut_Yes       	= { ITEMID_CUT_YES, NULL, IDS_DS_YES, NULL, MenuItemCut, 0, AHC_TRUE, NULL };
SMENUITEM sItemQM_Cut_No       		= { ITEMID_CUT_NO,  NULL, IDS_DS_NO,  NULL, MenuItemCut, 0, AHC_TRUE, NULL };
#endif

// Rotate
#if (MENU_PLAYBACK_ROTATE_EN)
SMENUITEM sItemRotate         		= { ITEMID_ROTATE, NULL, IDS_DS_ROTATE,	&sSubRotate, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemRotate_Left         	= { ITEMID_ROTATE_LEFT,   NULL, NULL,			NULL, MenuItemRotate, 0, AHC_TRUE, NULL };
SMENUITEM sItemRotate_Right      	= { ITEMID_ROTATE_RIGHT,  NULL, NULL, 			NULL, MenuItemRotate, 0, AHC_TRUE, NULL };
SMENUITEM sItemRotate_OK       		= { ITEMID_ROTATE_OK, 	  NULL, IDS_DS_OK, 		NULL, MenuItemRotate, 0, AHC_TRUE, NULL };
SMENUITEM sItemRotate_Cancel       	= { ITEMID_ROTATE_CANCEL, NULL, IDS_DS_CANCEL, 	NULL, MenuItemRotate, 0, AHC_TRUE, NULL };
#endif

// Resize
#if (MENU_PLAYBACK_RESIZE_EN)
SMENUITEM sItemResize         		= { ITEMID_RESIZE, NULL, IDS_DS_RESIZE,	&sSubResize, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_14M       	= { ITEMID_RESIZE_SIZE_14M,  &BMICON_IMAGESIZE_14M, IDS_DS_IMAGE_SIZE_14M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_12M       	= { ITEMID_RESIZE_SIZE_12M,  &BMICON_IMAGESIZE_12M, IDS_DS_IMAGE_SIZE_12M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_8M       		= { ITEMID_RESIZE_SIZE_8M,   &BMICON_IMAGESIZE_8M,  IDS_DS_IMAGE_SIZE_8M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_5M       		= { ITEMID_RESIZE_SIZE_5M,   &BMICON_IMAGESIZE_5M, 	IDS_DS_IMAGE_SIZE_5M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_3M       		= { ITEMID_RESIZE_SIZE_3M,   &BMICON_IMAGESIZE_3M, 	IDS_DS_IMAGE_SIZE_3M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_2M_Wide       = { ITEMID_RESIZE_SIZE_2M,   &BMICON_IMAGESIZE_2M, 	IDS_DS_IMAGE_SIZE_2M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_1_2M       	= { ITEMID_RESIZE_SIZE_1_2M, &BMICON_IMAGESIZE_1_2M,IDS_DS_IMAGE_SIZE_1_2M,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
SMENUITEM sItemResize_VGA       	= { ITEMID_RESIZE_SIZE_VGA,  &BMICON_IMAGESIZE_VGA, IDS_DS_IMAGE_SIZE_VGA,	NULL, MenuItemResize, 0, AHC_TRUE, NULL };
#endif

// Trimming
#if (MENU_PLAYBACK_TRIMMING_EN)
SMENUITEM sItemTrimming         	= { ITEMID_TRIMMING, NULL, IDS_DS_TRIMMING,	&sSubTrimming, 0, 0, AHC_TRUE, NULL };
SMENUITEM sItemTrimming_OK       	= { ITEMID_TRIMMING_OK, 	NULL, IDS_DS_OK, 	 NULL, MenuItemTrimming, 0, AHC_TRUE, NULL };
SMENUITEM sItemTrimming_Cancel      = { ITEMID_TRIMMING_CANCEL, NULL, IDS_DS_CANCEL, NULL, MenuItemTrimming, 0, AHC_TRUE, NULL };
#endif

// Slide Show Files
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
SMENUITEM sItemSlideShowFiles       = { ITEMID_SLIDE_SHOW_FILES, NULL, IDS_DS_SLIDE_SHOW_FILES,	&sSubSlideShowFiles, 0, 0, AHC_TRUE, NULL };
#if (MENU_PLAYBACK_SLIDESHOW_FILE_ALL_EN)
SMENUITEM sItemSlideShowFiles_All   = { ITEMID_FILES_ALL,   NULL, IDS_DS_FFILES_ALL, NULL, MenuItemSlideShowFiles, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_STILL_EN)
SMENUITEM sItemSlideShowFiles_Still = { ITEMID_FILES_STILL, NULL, IDS_DS_FILE_STILL, NULL, MenuItemSlideShowFiles, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_MOVIE_EN)
SMENUITEM sItemSlideShowFiles_Movie = { ITEMID_FILES_MOVIE, NULL, IDS_DS_FILE_MOVIE, NULL, MenuItemSlideShowFiles, 0, AHC_TRUE, NULL };
#endif
#endif

// Slide Show Effects
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
SMENUITEM sItemSlideShowEffects         	= { ITEMID_SLIDE_SHOW_EFFECTS, NULL, IDS_DS_SLIDE_SHOW_EFFECTS,	&sSubSlideShowEffects, 0, 0, AHC_TRUE, NULL };
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_SIMPLE_EN)
SMENUITEM sItemSlideShowEffects_Simple      = { ITEMID_SLIDE_EFFECTS_SIMPLE, 	NULL, IDS_DS_SIMPLE, 			NULL, MenuItemSlideShowEffects, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_NOSTALGIC_EN)
SMENUITEM sItemSlideShowEffects_Nostalgic   = { ITEMID_SLIDE_EFFECTS_NOSTALGIC, NULL, IDS_DS_EFFECTS_NOSTALGIC, NULL, MenuItemSlideShowEffects, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_STYLISH_EN)
SMENUITEM sItemSlideShowEffects_Stylish     = { ITEMID_SLIDE_EFFECTS_STYLISH, 	NULL, IDS_DS_EFFECTS_STYLISH, 	NULL, MenuItemSlideShowEffects, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_ACTIVE_EN)
SMENUITEM sItemSlideShowEffects_Active      = { ITEMID_SLIDE_EFFECTS_ACTIVE, 	NULL, IDS_DS_EFFECTS_ACTIVE, 	NULL, MenuItemSlideShowEffects, 0, AHC_TRUE, NULL };
#endif
#endif

// Slide Show Music
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
SMENUITEM sItemSlideShowMusic       = { ITEMID_SLIDE_SHOW_MUSIC, NULL, IDS_DS_SLIDE_SHOW_MUSIC,	&sSubSlideShowMusic, 0, 0, AHC_TRUE, NULL };
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_ON_EN)
SMENUITEM sItemSlideShowMusic_On    = { ITEMID_MUSIC_ON,  NULL, IDS_DS_ON,  NULL, MenuItemSlideShowMusic, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_OFF_EN)
SMENUITEM sItemSlideShowMusic_Off   = { ITEMID_MUSIC_OFF, NULL, IDS_DS_OFF, NULL, MenuItemSlideShowMusic, 0, AHC_TRUE, NULL };
#endif
#endif

// Volume
#if (MENU_PLAYBACK_VOLUME_EN)
SMENUITEM sItemVolume         		= { ITEMID_VOLUME, &BMICON_MENU_VOLUME, IDS_DS_VOLUME,	&sSubVolume, 0, 0, AHC_TRUE, NULL };
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
SMENUITEM sItemVolume_00       		= { ITEMID_VOLUME_00, &BMICON_VOL_0,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)
SMENUITEM sItemVolume_01      		= { ITEMID_VOLUME_01, &BMICON_VOL_1,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)
SMENUITEM sItemVolume_02       		= { ITEMID_VOLUME_02, &BMICON_VOL_2,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)
SMENUITEM sItemVolume_03       		= { ITEMID_VOLUME_03, &BMICON_VOL_3,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)
SMENUITEM sItemVolume_04       		= { ITEMID_VOLUME_04, &BMICON_VOL_4,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)
SMENUITEM sItemVolume_05       		= { ITEMID_VOLUME_05, &BMICON_VOL_5,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)
SMENUITEM sItemVolume_06       		= { ITEMID_VOLUME_06, &BMICON_VOL_6,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)
SMENUITEM sItemVolume_07      		= { ITEMID_VOLUME_07, &BMICON_VOL_7,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)
SMENUITEM sItemVolume_08       		= { ITEMID_VOLUME_08, &BMICON_VOL_8,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)
SMENUITEM sItemVolume_09       		= { ITEMID_VOLUME_09, &BMICON_VOL_9,  NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };   
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)
SMENUITEM sItemVolume_10       		= { ITEMID_VOLUME_10, &BMICON_VOL_10, NULL,	NULL, MenuItemVolume, 0, AHC_TRUE, NULL };
#endif
#endif


// Video Type
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
SMENUITEM sItemVideoType       		= { ITEMID_SHOW_VIDEO_TYPE, NULL, IDS_DS_VIDEO_TYPE, &sSubPlaybackVideoType, 0, 0, AHC_TRUE, NULL };
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeNormal 		= { ITEMID_VIDEO_TYPE_NORMAL, NULL,  IDS_DS_VIDEO_TYPE_NORMAL, NULL, MenuItemPlaybackVideoType, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeParking		= { ITEMID_VIDEO_TYPE_PARKING, NULL,  IDS_DS_VIDEO_TYPE_PARKING, NULL, MenuItemPlaybackVideoType, 0, AHC_TRUE, NULL };
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
SMENUITEM sItemVideoTypeEmergency	= { ITEMID_VIDEO_TYPE_EMERGENCY, NULL,  IDS_DS_VIDEO_TYPE_EMERGENCY, NULL, MenuItemPlaybackVideoType, 0, AHC_TRUE, NULL };
#endif
#endif

/*===========================================================================
 * Global variable : Item List
 *===========================================================================*/ 

#if (MENU_PLAYBACK_QM_CUT_EN)
PSMENUITEM   sMenuListCut[] =
{
    &sItemQM_Cut_Yes,
    &sItemQM_Cut_No
};
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
PSMENUITEM   sMenuListRotate[] =
{
    &sItemRotate_OK,
    &sItemRotate_Cancel
};
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
PSMENUITEM   sMenuListResize[] =
{
    &sItemResize_14M,
    &sItemResize_5M,
    &sItemResize_3M,
    &sItemResize_2M_Wide,
    &sItemResize_1_2M,
    &sItemResize_VGA
};
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
PSMENUITEM   sMenuListTrimming[] =
{
    &sItemTrimming_OK,
    &sItemTrimming_Cancel
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
PSMENUITEM   sMenuListSlideShowFiles[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_FILE_ALL_EN)
    &sItemSlideShowFiles_All,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_STILL_EN)    
    &sItemSlideShowFiles_Still,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_FILE_MOVIE_EN)    
    &sItemSlideShowFiles_Movie
#endif    
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
PSMENUITEM   sMenuListSlideShowEffects[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_SIMPLE_EN)
    &sItemSlideShowEffects_Simple,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_NOSTALGIC_EN)    
    &sItemSlideShowEffects_Nostalgic,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_STYLISH_EN)    
    &sItemSlideShowEffects_Stylish,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_ACTIVE_EN)    
    &sItemSlideShowEffects_Active
#endif    
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
PSMENUITEM   sMenuListSlideShowMusic[] =
{
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_ON_EN)
    &sItemSlideShowMusic_On,
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_OFF_EN)    
    &sItemSlideShowMusic_Off
#endif    
};
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
PSMENUITEM   sMenuListVolume[] =
{
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
    &sItemVolume_00,
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)    
    &sItemVolume_01,
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)    
    &sItemVolume_02,
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)    
    &sItemVolume_03,
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)    
    &sItemVolume_04,
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)    
    &sItemVolume_05,
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)    
    &sItemVolume_06,
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)    
    &sItemVolume_07,
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)    
    &sItemVolume_08,
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)    
    &sItemVolume_09,    
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)    
    &sItemVolume_10,  
#endif
};
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
PSMENUITEM   sMenuListVideoType[] =
{
#if (MENU_PLAYBACK_VIDEO_TYPE_NORMAL_EN)
    &sItemVideoTypeNormal,
#endif
#if (MENU_PLAYBACK_VIDEO_TYPE_PARKING_EN)    
    &sItemVideoTypeParking,
#endif    
#if (MENU_PLAYBACK_VIDEO_TYPE_EMERGENCY_EN)    
    &sItemVideoTypeEmergency
#endif    
};
#endif

PSMENUITEM   sMenuListEditToolConfirm[] =
{
	&sItemConfirmOne_Yes,
	&sItemConfirmOne_No
};

PSMENUITEM   sMenuListMainPlayback[] =
{
#if (MENU_PLAYBACK_VOLUME_EN)
    &sItemVolume,
#endif
#if (MENU_EDIT_DELETE_EN)    
	&sItemDelete,
#endif
#if (MENU_EDIT_PROTECT_EN)    
    &sItemProtect,
#endif    
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
	&sItemSlideShowFiles,
#endif	
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
	&sItemVideoType
#endif	
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuPlayback =
{
    MENUID_MAIN_MENU_PLAYBACK,                                 		
    NULL,                                              				
    IDS_DS_PLAYBACK,                                                
    NULL,                                              				
    sizeof(sMenuListMainPlayback)/sizeof(PSMENUITEM),    			
    sMenuListMainPlayback,                                 			
    MainMenuEventHandler,                                  			
    MenuGetDefault,                                    				
    0,                                                 				
    0,                                                 				
    0,                                                 				
    0                                                  				
};

SMENUSTRUCT   sEditToolSelectMenu =
{
    MENUID_MAIN_MENU_PLAYBACK,                                 		
    &bmIcon_WMSG,                                              				
    IDS_DS_PLAYBACK,                                                
    NULL,                                              				
    sizeof(sMenuListEditToolConfirm)/sizeof(PSMENUITEM),    			
    sMenuListEditToolConfirm,                                 			
    MenuEditConfirmEventHandler,                                  			
    MenuGetDefault,                                    				
    0,                                                 				
    0,                                                 				
    0,                                                 				
    0                                                  				
};

//--------------SUB MENU-------------------

#if (MENU_PLAYBACK_QM_CUT_EN)
SMENUSTRUCT sSubCut =
{
    MENUID_SUB_MENU_CUT,
    &bmIcon_Cut,
    IDS_DS_CUT,
    NULL,
    sizeof(sMenuListCut)/sizeof(PSMENUITEM),
    sMenuListCut,
    QuickMenuSubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
SMENUSTRUCT sSubRotate =
{
    MENUID_SUB_MENU_ROTATE,
    NULL,
    IDS_DS_ROTATE,
    NULL,
    sizeof(sMenuListRotate)/sizeof(PSMENUITEM),
    sMenuListRotate,
    QuickMenuSubMenuEventHandler_Rotate,
    MenuGetDefault,
    0,
    NULL,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
SMENUSTRUCT sSubResize =
{
    MENUID_SUB_MENU_RESIZE,
    NULL,
    IDS_DS_RESIZE,
    NULL,
    sizeof(sMenuListResize)/sizeof(PSMENUITEM),
    sMenuListResize,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    IDS_DS_RESIZE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
SMENUSTRUCT sSubTrimming =
{
    MENUID_SUB_MENU_TRIMMING,
    NULL,
    IDS_DS_TRIMMING,
    NULL,
    sizeof(sMenuListTrimming)/sizeof(PSMENUITEM),
    sMenuListTrimming,
    QuickMenuSubMenuEventHandler_Trimming,
    MenuGetDefault,
    0,
    NULL,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
SMENUSTRUCT sSubSlideShowFiles =
{
    MENUID_SUB_MENU_SLIDE_SHOW_FILES,
    NULL,
    IDS_DS_SLIDE_SHOW_FILES,
    NULL,
    sizeof(sMenuListSlideShowFiles)/sizeof(PSMENUITEM),
    sMenuListSlideShowFiles,
    SubMenuEventHandler,
    MenuGetDefault_Playback,
    0,
    IDS_DS_SSHOWFILES_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
SMENUSTRUCT sSubSlideShowEffects =
{
    MENUID_SUB_MENU_SLIDE_SHOW_EFFECTS,
    NULL,
    IDS_DS_SLIDE_SHOW_EFFECTS,
    NULL,
    sizeof(sMenuListSlideShowEffects)/sizeof(PSMENUITEM),
    sMenuListSlideShowEffects,
    SubMenuEventHandler,
    MenuGetDefault_Playback,
    0,
    IDS_DS_SSHOWEFFECTS_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
SMENUSTRUCT sSubSlideShowMusic =
{
    MENUID_SUB_MENU_SLIDE_SHOW_MUSIC,
    NULL,
    IDS_DS_SLIDE_SHOW_MUSIC,
    NULL,
    sizeof(sMenuListSlideShowMusic)/sizeof(PSMENUITEM),
    sMenuListSlideShowMusic,
    SubMenuEventHandler,
    MenuGetDefault_Playback,
    0,
    IDS_DS_SSHOWMUSIC_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
SMENUSTRUCT sSubVolume =
{
    MENUID_SUB_MENU_VOLUME,
    NULL,
    IDS_DS_VOLUME,
    NULL,
    sizeof(sMenuListVolume)/sizeof(PSMENUITEM),
    sMenuListVolume,
    SubMenuEventHandler_Volume,//SubMenuEventHandler,
    MenuGetDefault_Playback,
    0,
    IDS_DS_VOLUME_DESCRIPTION,
    AHC_TRUE,
    0
};
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
SMENUSTRUCT sSubPlaybackVideoType =
{
    MENUID_SUB_MENU_VIDEO_TYPE,
    NULL,
    IDS_DS_VIDEO_TYPE,
    NULL,
    sizeof(sMenuListVideoType)/sizeof(PSMENUITEM),
    sMenuListVideoType,
    SubMenuEventHandler,
    MenuGetDefault_Playback,
    0,
    IDS_DS_VIDEO_TYPE,
    AHC_FALSE,
    0
};
#endif

/*===========================================================================
 * Global variable
 *===========================================================================*/

UINT16 m_ulVolume[] = //Unit:Percent
{
#if (MENU_PLAYBACK_VOLUME_LV0_EN)
	0, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV1_EN)	
	10, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV2_EN)	
	20, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV3_EN)	
	30, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV4_EN)	
	40, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV5_EN)	
	50, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV6_EN)	
	60, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV7_EN)	
	70, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV8_EN)	
	80, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV9_EN)	
	90, 
#endif
#if (MENU_PLAYBACK_VOLUME_LV10_EN)	
	100
#endif	
};

/*===========================================================================
 * Main body
 *===========================================================================*/

#if (MENU_PLAYBACK_QM_CUT_EN)
AHC_BOOL MenuItemCut(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_ROTATE_EN)
AHC_BOOL MenuItemRotate(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_RESIZE_EN)
AHC_BOOL MenuItemResize(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_TRIMMING_EN)
AHC_BOOL MenuItemTrimming(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)
AHC_BOOL MenuItemSlideShowFiles(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSlideShowFile = pItem->iItemId - ITEMID_SLIDE_SHOW_FILES-1;
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)
AHC_BOOL MenuItemSlideShowEffects(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSlideShowEffect = pItem->iItemId - ITEMID_SLIDE_SHOW_EFFECTS-1;
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)
AHC_BOOL MenuItemSlideShowMusic(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiSlideShowMusic= pItem->iItemId - ITEMID_SLIDE_SHOW_MUSIC-1;
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_VOLUME_EN)
AHC_BOOL MenuItemVolume(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    MenuSettingConfig()->uiVolume= pItem->iItemId - ITEMID_VOLUME-1;
	Menu_SetVolume(MenuSettingConfig()->uiVolume);    
    return AHC_TRUE;
}
#endif

#if (MENU_PLAYBACK_VIDEO_TYPE_EN)
AHC_BOOL MenuItemPlaybackVideoType(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT8 byOption = pItem->iItemId - ITEMID_SHOW_VIDEO_TYPE-1;
    if( SystemSettingConfig()->byPlaybackVideoType != byOption )
    {
        SystemSettingConfig()->byPlaybackVideoType = byOption;
        bRefreshBrowser = AHC_TRUE;
    }
    return AHC_TRUE;
}
#endif

UINT32 MenuGetDefault_Playback(PSMENUSTRUCT pMenu)
{
    UINT32       DefaultValue = 0;

    switch( pMenu->iMenuId )
    {
#if (MENU_PLAYBACK_SLIDESHOW_FILE_EN)  
        case MENUID_SUB_MENU_SLIDE_SHOW_FILES:
            DefaultValue = MenuSettingConfig()->uiSlideShowFile;
            break;
#endif
#if (MENU_PLAYBACK_SLIDESHOW_EFFECT_EN)  
        case MENUID_SUB_MENU_SLIDE_SHOW_EFFECTS:
            DefaultValue = MenuSettingConfig()->uiSlideShowEffect;
            break;
#endif
#if (MENU_PLAYBACK_SLIDESHOW_MUSIC_EN)              
        case MENUID_SUB_MENU_SLIDE_SHOW_MUSIC:
            DefaultValue = MenuSettingConfig()->uiSlideShowMusic;
            break;
#endif
#if (MENU_PLAYBACK_VOLUME_EN)            
        case MENUID_SUB_MENU_VOLUME:
            DefaultValue = MenuSettingConfig()->uiVolume;
            break;
#endif            
#if (MENU_PLAYBACK_VIDEO_TYPE_EN)            
        case MENUID_SUB_MENU_VIDEO_TYPE:
            DefaultValue = SystemSettingConfig()->byPlaybackVideoType;
            break;
#endif            
    }

	return DefaultValue;
}

#if (MENU_PLAYBACK_VOLUME_EN)

UINT32 SubMenuEventHandler_Volume(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    int 		iPrevPos;
    AHC_BOOL 	bCycle = AHC_FALSE;
#if(SUPPORT_TOUCH_PANEL)       
    POINT  		TouchPoint;

    if( MENU_TOUCH == ulEvent || MENU_TOUCH_MOVE == ulEvent )
    {
        TouchPoint.PointX = ulParam & 0xFFFF;
        TouchPoint.PointY = (ulParam >> 16) & 0xFFFF;
    }
#endif

	switch(ulEvent)
	{
	case MENU_EXIT:
		return MENU_ERR_EXIT;
	break;	
	
	case MENU_INIT          :
        pMenu->uiStatus = MENU_STATUS_NONE;
	    
	    if( pMenu->pfMenuGetDefaultVal )
	    {
	    	#ifdef CFG_FIXED_INTERNAL_VOLUME_ID//may be defined in config_xxx.h
	    	pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu )/5;
	    	#else
		    pMenu->iSelected = pMenu->pfMenuGetDefaultVal( pMenu );
		    #endif
	    }
	    else
	    {
			pMenu->iSelected = 0;
	    }
		pMenu->iCurrentPos = pMenu->iSelected;
		pMenu->bSetOne     = 0;


		#if (SUPPORT_TOUCH_PANEL)
		KeyParser_TouchItemRegister(&MenuVolume_TouchButton[0], ITEMNUM(MenuVolume_TouchButton));
		#endif

	    MenuDrawSubPage_Volume( pMenu );
		break;

#if defined(CFG_FIXED_INTERNAL_VOLUME_ID)//may be defined in config_xxx.h
	case MENU_UP            :
		bCycle = AHC_TRUE;
#elif (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_DOWN          :
#else
	case MENU_LEFT          :
#endif	
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, bCycle );

		MenuItemVolume(sMenuListVolume[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Volume( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;

#if defined(CFG_FIXED_INTERNAL_VOLUME_ID)//may be defined in config_xxx.h
	case MENU_DOWN              :
		bCycle = AHC_TRUE;
#elif (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_UP          	:
#else
	case MENU_RIGHT         :
#endif	
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, bCycle );

		MenuItemVolume(sMenuListVolume[pMenu->iCurrentPos], AHC_FALSE);
        MenuDrawChangeSubItem_Volume( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		break;
				
	case MENU_OK            :
    case MENU_SET_ONE       :	
    
		pMenu->bSetOne   = 1;
        pMenu->iSelected = pMenu->iCurrentPos;
        pMenu->uiStatus |= MENU_STATUS_PRESSED;

		if(ulEvent==MENU_SET_ONE)
		{
	        pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
		}
        
        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {

			PSMENUSTRUCT pParentMenu;
			
			pParentMenu        = pMenu->pParentMenu;
			pMenu->pParentMenu = NULL;

 			if( pParentMenu == NULL )
			{
				return MENU_ERR_EXIT;
			}
        	
			SetCurrentMenu(pParentMenu);
			pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
				        	
        	
            return MENU_ERR_OK;
        }
		break;

	case MENU_MENU          :
    {
		
        PSMENUSTRUCT pParentMenu;
		
		pMenu->bSetOne     = 0;
        pParentMenu        = pMenu->pParentMenu;
        pMenu->pParentMenu = NULL;

        if( pParentMenu == NULL )
        {
	        return MENU_ERR_EXIT;
        }

        SetCurrentMenu(pParentMenu);
        pParentMenu->pfEventHandler( pParentMenu, MENU_INIT, 0 );
        
    }
		break;

#if (SUPPORT_TOUCH_PANEL)
	case MENU_TOUCH         :
       {
            UINT32 	TouchEvent;
            UINT32  uiNextEvent = MENU_NONE;

            TouchEvent = AhcCheckTouchButton(&TouchPoint, 0);

			switch( TouchEvent )
			{
				case MENU_EXIT_PRESS :
					uiNextEvent = MENU_MENU;
				break;
				case MENU_INCREASE_PRESS :
					#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
					uiNextEvent = MENU_UP;
					#else
					uiNextEvent = MENU_RIGHT;
					#endif
				break;
				case MENU_DECREASE_PRESS :
					#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
					uiNextEvent = MENU_DOWN;
					#else
					uiNextEvent = MENU_LEFT;
					#endif
				break;
				case MENU_OK_PRESS :
					uiNextEvent = MENU_SET_ONE;
				break;				
				default:
					uiNextEvent = MENU_NONE;
				break;
			}

			return SubMenuEventHandler_Volume(pMenu, uiNextEvent, ulParam);
		}
	break;
		
	case MENU_TOUCH_RELEASE:
		if( pMenu->uiStatus & MENU_STATUS_ITEM_TOUCHED )
		{
            iPrevPos = pMenu->iSelected;
			pMenu->uiStatus = 0;
	        MenuDrawChangeSubItem_Volume( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
		}
	break;
#endif

#if 0
	case MENU_POWER_OFF     :
        AHC_PowerOff_NormalPath();
	    break; 	
#endif

	default:
		break;
	}

    return MENU_ERR_OK;
}
#endif

void MenuStatePlaybackSelectDB( UINT8 byOpMode )
{
    switch( byOpMode )
    {
        case VIDEOREC_MODE  :
        case MOVPB_MODE     :
            #if (DCF_DB_COUNT >= 2)
                #if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
                {
                    //customized part
                    AHC_BOOL bSetMultiDBBrowse = AHC_FALSE;
                    if( SystemSettingConfig()->byPlaybackVideoType == (ITEMID_VIDEO_TYPE_NORMAL - ITEMID_VIDEO_TYPE_NORMAL)){
                        bSetMultiDBBrowse = AHC_TRUE;
                    }
                    else{
                        bSetMultiDBBrowse = AHC_FALSE;
                    }

					if(m_ubPlaybackRearCam){
						bSetMultiDBBrowse = AHC_FALSE;
					}
                    AHC_MIMF_SetMultiDBBrowseEnable(bSetMultiDBBrowse);
                }
                #endif
            AHC_UF_SelectDB( SystemSettingConfig()->byPlaybackVideoType );
            #endif
            break;
        
        case CAPTURE_MODE   :
        case JPGPB_MODE     :
            #if (DCF_DB_COUNT >= 4)
                #if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
                AHC_MIMF_SetMultiDBBrowseEnable(AHC_FALSE);
                #endif
            AHC_UF_SelectDB( DCF_DB_TYPE_DB3_PHOTO );
            #endif
            break;

		case JPGPB_MOVPB_MODE     :	
			AHC_UF_SelectDB( DCF_DB_TYPE_DB0_NORMAL );
            break;
    }
}

AHC_BOOL  MenuStatePlaybackModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;
    
    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);

    SetCurrentMenu(&sMainMenuPlayback);

    ulResult = MenuStateExecutionCommon(ulEvent, 0);

#if 0
    ahcRet = AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet);} 
#endif

    return ahcRet;
}

AHC_BOOL  MenuStatePlaybackModeShutDown(void* pData)
{
    return AHC_TRUE;
}

AHC_BOOL  MenuStateEditToolModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT32 ulEvent = 0, ulResult = 0;

    ulEvent = MenuButtonToMenuOp(BUTTON_VIRTUAL_RESET , 0);

    SetCurrentMenu(&sEditToolSelectMenu);

	if(Deleting_InBrowser)
	{
		sEditToolSelectMenu.uiStringId = IDS_DS_MSG_SURE_TO_DELETE_SELETED;
	}
	else if(Protecting_InBrowser==1){
		sEditToolSelectMenu.uiStringId = IDS_DS_MSG_SURE_TO_PROTECT_SELETED;
	}
	else if(Protecting_InBrowser==2){	
		sEditToolSelectMenu.uiStringId = IDS_DS_MSG_SURE_TO_UNPROTECT_SELETED;
	}
	
    ulResult = MenuStateExecutionCommon(ulEvent, 0);

    return ahcRet;
}

