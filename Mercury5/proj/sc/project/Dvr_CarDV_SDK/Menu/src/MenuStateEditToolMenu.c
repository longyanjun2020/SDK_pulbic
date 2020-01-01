/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_utility.h"
#include "ahc_macro.h"
#include "ahc_browser.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_menu.h"
#include "ahc_gui.h"
#include "ahc_general.h"
#include "ahc_parameter.h"
#include "ahc_warningmsg.h"
#include "ahc_display.h"
#include "ahc_media.h"
#include "ahc_general_cardv.h"

#include "MenuCommon.h"
#include "MenuSetting.h"
#include "MenuTouchButton.h"
#include "MenuStateEditToolMenu.h"
#include "MenuDrawingEditToolFunc.h"
#include "MenuDrawingFunc.h"
#include "MenuDrawCommon.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "statebrowserfunc.h"
#include "stateslideshowfunc.h"
#include "mediaplaybackctrl.h"
#include "keyparser.h"
#include "MenuStatePlaybackMenu.h"
#include "snr_cfg.h"
/*===========================================================================
 * Local function
 *===========================================================================*/ 

UINT32   SubMenuEventHandler_EditAllFile(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam);

AHC_BOOL MenuItemDeleteOne(PSMENUITEM pItem, AHC_BOOL bHover);
AHC_BOOL MenuItemDeleteAll(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemDeleteFile(PSMENUITEM pItem, AHC_BOOL bHover);
AHC_BOOL MenuItemUnProtectOne(PSMENUITEM pItem, AHC_BOOL bHover);
AHC_BOOL MenuItemProtectOne(PSMENUITEM pItem, AHC_BOOL bHover);
AHC_BOOL MenuItemProtectAll(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemUnProtectAll(PSMENUITEM pItem, AHC_BOOL bIsHover);
AHC_BOOL MenuItemEditOneConfirmOk(PSMENUITEM pItem, AHC_BOOL bHover);

UINT32 	 MenuGetFormatDefault(PSMENUSTRUCT pMenu);

/*===========================================================================
 * Extern varible
 *===========================================================================*/ 
//extern AHC_BOOL 	bForceSwitchBrowser;
extern UINT32   	ObjSelect;
extern AHC_BOOL     m_ubPlaybackRearCam; //play rearcam mode

#if (LIMIT_MAX_LOCK_FILE_NUM==1)
extern UINT32 		m_ulLockFileNum;
extern UINT32 		m_ulLockEventNum;
#endif


/*===========================================================================
 * Global varible
 *===========================================================================*/ 

AHC_BOOL Delete_File_Confirm   	= 0;
AHC_BOOL Deleting_InBrowser   	= 0;
AHC_BOOL Delete_Option 			= CONFIRM_NOT_YET;
AHC_BOOL Protect_File_Confirm   = 0;
AHC_BOOL Protecting_InBrowser 	= 0;
AHC_BOOL Protect_Option 		= CONFIRM_NOT_YET;
AHC_BOOL UnProtect_File_Confirm = 0;
AHC_BOOL UnProtect_Option 		= CONFIRM_NOT_YET;

/*===========================================================================
 * Global variable : Menu
 *===========================================================================*/ 

SMENUSTRUCT sMainMenuEdit;

SMENUSTRUCT sSubDelete;
SMENUSTRUCT sSubDeleteFile;
SMENUSTRUCT sSubDeleteAll;
SMENUSTRUCT sSubDeleteAll_Video;
SMENUSTRUCT sSubDeleteAll_Image;
SMENUSTRUCT sSubProtect;
SMENUSTRUCT sSubProtectAll;
SMENUSTRUCT sSubProtectAll_Video;
SMENUSTRUCT sSubProtectAll_Image;
SMENUSTRUCT sSubUnProtectAll;
SMENUSTRUCT sSubUnProtectAll_Video;
SMENUSTRUCT sSubUnProtectAll_Image;

SMENUSTRUCT sSubDeleteOne;
SMENUSTRUCT sSubProtectOne;
SMENUSTRUCT sSubUnProtectOne;

/*===========================================================================
 * Global variable : Item Structure
 *===========================================================================*/

// Delete
#if (MENU_EDIT_DELETE_EN)
SMENUITEM sItemDelete         = { ITEMID_DELETE, &BMICON_MENU_DELETE, IDS_DS_DELETE,	&sSubDelete, 0, 0, AHC_TRUE, NULL };

SMENUITEM sItemDeleteFile     = { ITEMID_DELETE_FILE, &BMICON_MENU_DELETE, IDS_DS_DELETE,	&sSubDeleteFile, 0,     0, AHC_TRUE, NULL };
SMENUITEM sItemDelete_Cancel  = { ITEMID_DELETE_CANCEL, 	NULL, IDS_DS_CANCEL, 		NULL, MenuItemDeleteFile, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteFileLast = { ITEMID_DELETE_FILE_LAST, 	NULL, IDS_DS_LAST,			NULL, MenuItemDeleteFile, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteFileAll  = { ITEMID_DELETE_FILE_ALL, 	NULL, IDS_DS_ALL,			NULL, MenuItemDeleteFile, 	0, AHC_TRUE, NULL };
#endif

// Delete One
#if (MENU_EDIT_DELETE_ONE_EN)

#if (MENU_EDIT_DELETE_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to delete */
SMENUITEM sItemDeleteOne       = { ITEMID_DELETE_ONE,  	  	&BMICON_DEL_ONE,    IDS_DS_DELETE_ONE, &sSubDeleteOne, 		0, 	 0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_Yes   = { ITEMID_DELETE_ONE_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, 	    NULL, NULL,				 0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_No    = { ITEMID_DELETE_ONE_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  	    NULL, NULL,				 0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_Video = { ITEMID_DELETE_VIDEO_ONE, &BMICON_MENU_MOVIE, IDS_VIDEO_FILE,		NULL, MenuItemDeleteOne, 0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_Image = { ITEMID_DELETE_IMAGE_ONE, &BMICON_MENU_CAMERA,IDS_IMAGE_FILE,		NULL, MenuItemDeleteOne, 0, AHC_TRUE, NULL };
#else
SMENUITEM sItemDeleteOne      = { ITEMID_DELETE_ONE,  	 &BMICON_DEL_ONE, IDS_DS_DELETE_ONE, 	NULL, MenuItemDeleteOne, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_Yes  = { ITEMID_DELETE_ONE_YES, &BMICON_OPTION_YES, 	IDS_DS_YES, 	NULL, NULL, 				0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteOne_No   = { ITEMID_DELETE_ONE_NO,  &BMICON_OPTION_NO, 	IDS_DS_NO,  	NULL, NULL, 				0, AHC_TRUE, NULL };
#endif

#endif

SMENUITEM sItemConfirmOne_Yes  = { ITEMID_DELETE_ONE_YES, &BMICON_OPTION_YES, 	IDS_DS_YES, 	NULL, MenuItemEditOneConfirmOk, 0, AHC_TRUE, NULL };
SMENUITEM sItemConfirmOne_No   = { ITEMID_DELETE_ONE_NO,  &BMICON_OPTION_NO, 	IDS_DS_NO,  	NULL, MenuItemEditOneConfirmOk,0, AHC_TRUE, NULL };

// Delete All
#if (MENU_EDIT_DELETE_ALL_EN)
SMENUITEM sItemDeleteAll      		= { ITEMID_DELETE_ALL, 	&BMICON_DEL_ALL, IDS_DS_DELETE_ALL,	&sSubDeleteAll, 0, 					0, AHC_TRUE, NULL };

// Delete All Video
SMENUITEM sItemDeleteAll_Video 		= { ITEMID_DELETE_ALL_VIDEO, 	 &BMICON_MENU_MOVIE, IDS_VIDEO_FILE,	&sSubDeleteAll_Video, 0, 				0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteAll_Video_Yes  = { ITEMID_DELETE_ALL_VIDEO_YES, &BMICON_OPTION_YES, IDS_DS_YES, 	NULL, 	MenuItemDeleteAll, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteAll_Video_No   = { ITEMID_DELETE_ALL_VIDEO_NO,  &BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, 	MenuItemDeleteAll, 	0, AHC_TRUE, NULL };

// Delete All Image
SMENUITEM sItemDeleteAll_Image 		= { ITEMID_DELETE_ALL_IMAGE, 	 &BMICON_MENU_CAMERA,IDS_IMAGE_FILE,	&sSubDeleteAll_Image, 0, 				0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteAll_Image_Yes  = { ITEMID_DELETE_ALL_IMAGE_YES, &BMICON_OPTION_YES, IDS_DS_YES, 	NULL, 	MenuItemDeleteAll, 	0, AHC_TRUE, NULL };
SMENUITEM sItemDeleteAll_Image_No   = { ITEMID_DELETE_ALL_IMAGE_NO,  &BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, 	MenuItemDeleteAll, 	0, AHC_TRUE, NULL };
#endif

// Protect
#if (MENU_EDIT_PROTECT_EN)
SMENUITEM sItemProtect        	= { ITEMID_PROTECT, &BMICON_MENU_PROTECT, IDS_DS_PROTECT,	&sSubProtect, 0, 0, AHC_TRUE, NULL };
#endif

// Protect One
#if (MENU_EDIT_PROTECT_ONE_EN)

#if (MENU_EDIT_PROTECT_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to protect */
SMENUITEM sItemProtectOne     	= { ITEMID_PROTECT_ONE, 		&BMICON_LOCK_ONE,   IDS_DS_PROTECT_ONE, 	&sSubProtectOne, NULL,  0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_Yes 	= { ITEMID_PROTECT_ONE_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, 	NULL, 	NULL, 					0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_No  	= { ITEMID_PROTECT_ONE_NO,  	&BMICON_OPTION_NO, 	IDS_DS_NO,  	NULL,	NULL, 					0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_Video = { ITEMID_PROTECT_VIDEO_ONE, 	&BMICON_MENU_MOVIE, IDS_VIDEO_FILE,	NULL, 	MenuItemProtectOne, 	0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_Image = { ITEMID_PROTECT_IMAGE_ONE, 	&BMICON_MENU_CAMERA,IDS_IMAGE_FILE,	NULL, 	MenuItemProtectOne, 	0, AHC_TRUE, NULL };
#else
SMENUITEM sItemProtectOne     	= { ITEMID_PROTECT_ONE, 	&BMICON_LOCK_ONE, IDS_DS_PROTECT_ONE, 	NULL, MenuItemProtectOne, 0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_Yes 	= { ITEMID_PROTECT_ONE_YES, &BMICON_OPTION_YES, IDS_DS_YES, 	NULL, NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemProtectOne_No  	= { ITEMID_PROTECT_ONE_NO,  &BMICON_OPTION_NO, 	IDS_DS_NO,  	NULL, NULL, 0, AHC_TRUE, NULL };
#endif

#endif

// UnProtect One
#if (MENU_EDIT_UNPROTECT_ONE_EN)

#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
/* Show a submenu to select video or photo file before selecting a file to unlock */
SMENUITEM sItemUnProtectOne     	= { ITEMID_UNPROTECT_ONE, 	  	&BMICON_UNLOCK_ONE, IDS_DS_UNPROTECT_ONE, 	&sSubUnProtectOne,  NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_Yes		= { ITEMID_UNPROTECT_ONE_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, 	NULL, NULL, 				0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_No  	= { ITEMID_UNPROTECT_ONE_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, NULL, 				0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_Video 	= { ITEMID_UNPROTECT_VIDEO_ONE, &BMICON_MENU_MOVIE, IDS_VIDEO_FILE,	NULL, MenuItemUnProtectOne,	0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_Image 	= { ITEMID_UNPROTECT_IMAGE_ONE, &BMICON_MENU_CAMERA,IDS_IMAGE_FILE, NULL, MenuItemUnProtectOne, 0, AHC_TRUE, NULL };
#else
SMENUITEM sItemUnProtectOne     = { ITEMID_UNPROTECT_ONE, 	  &BMICON_UNLOCK_ONE, IDS_DS_UNPROTECT_ONE, 	NULL, MenuItemUnProtectOne, 0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_Yes = { ITEMID_UNPROTECT_ONE_YES, &BMICON_OPTION_YES, IDS_DS_YES, 	NULL, NULL, 0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectOne_No  = { ITEMID_UNPROTECT_ONE_NO,  &BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, NULL, 0, AHC_TRUE, NULL };
#endif

#endif

// Protect All
#if (MENU_EDIT_PROTECT_ALL_EN)
SMENUITEM sItemProtectAll     		 = { ITEMID_PROTECT_ALL, 			&BMICON_LOCK_ALL, IDS_DS_PROTECT_ALL, &sSubProtectAll, 		0, 				0, AHC_TRUE, NULL };

// Protect All Video
SMENUITEM sItemProtectAll_Video 	 = { ITEMID_PROTECT_ALL_VIDEO, 	 	&BMICON_MENU_MOVIE, IDS_VIDEO_FILE,	&sSubProtectAll_Video, 	0, 				0, AHC_TRUE, NULL };
SMENUITEM sItemProtectAll_Video_Yes  = { ITEMID_PROTECT_ALL_VIDEO_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, 	NULL, 	MenuItemProtectAll, 0, AHC_TRUE, NULL };
SMENUITEM sItemProtectAll_Video_No   = { ITEMID_PROTECT_ALL_VIDEO_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, 	MenuItemProtectAll, 0, AHC_TRUE, NULL };

// Protect All Image
SMENUITEM sItemProtectAll_Image 	 = { ITEMID_PROTECT_ALL_IMAGE, 	  	&BMICON_MENU_CAMERA,IDS_IMAGE_FILE,	&sSubProtectAll_Image, 	0, 				0, AHC_TRUE, NULL };
SMENUITEM sItemProtectAll_Image_Yes  = { ITEMID_PROTECT_ALL_IMAGE_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, 	NULL, 	MenuItemProtectAll, 0, AHC_TRUE, NULL };
SMENUITEM sItemProtectAll_Image_No   = { ITEMID_PROTECT_ALL_IMAGE_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  	NULL, 	MenuItemProtectAll, 0, AHC_TRUE, NULL };
#endif

// UnProtect All
#if (MENU_EDIT_UNPROTECT_ALL_EN)
SMENUITEM sItemUnProtectAll     	   = { ITEMID_UNPROTECT_ALL, 			&BMICON_UNLOCK_ALL, IDS_DS_UNPROTECT_ALL, &sSubUnProtectAll, 		0, 						0, AHC_TRUE, NULL };

// UnProtect All Video
SMENUITEM sItemUnProtectAll_Video 	   = { ITEMID_UNPROTECT_ALL_VIDEO, 		&BMICON_MENU_MOVIE, IDS_VIDEO_FILE,	&sSubUnProtectAll_Video, 	0, 						0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectAll_Video_Yes  = { ITEMID_UNPROTECT_ALL_VIDEO_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, NULL, 	MenuItemUnProtectAll, 	0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectAll_Video_No   = { ITEMID_UNPROTECT_ALL_VIDEO_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  NULL, 	MenuItemUnProtectAll, 	0, AHC_TRUE, NULL };

// UnProtect All Image
SMENUITEM sItemUnProtectAll_Image 	   = { ITEMID_UNPROTECT_ALL_IMAGE, 		&BMICON_MENU_CAMERA, IDS_IMAGE_FILE,	&sSubUnProtectAll_Image, 	0, 						0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectAll_Image_Yes  = { ITEMID_UNPROTECT_ALL_IMAGE_YES, 	&BMICON_OPTION_YES, IDS_DS_YES, NULL, 	MenuItemUnProtectAll, 	0, AHC_TRUE, NULL };
SMENUITEM sItemUnProtectAll_Image_No   = { ITEMID_UNPROTECT_ALL_IMAGE_NO,  	&BMICON_OPTION_NO,  IDS_DS_NO,  NULL, 	MenuItemUnProtectAll, 	0, AHC_TRUE, NULL };
#endif

/*===========================================================================
 * Global varible : Item List
 *===========================================================================*/ 

#if (MENU_EDIT_DELETE_EN)
PSMENUITEM   sMenuListDelete[]=
{	
#if (MENU_EDIT_DELETE_ONE_EN)	
	&sItemDeleteOne,
#endif	
#if (MENU_EDIT_DELETE_ALL_EN)
    &sItemDeleteAll
#endif  
};

PSMENUITEM   sMenuListDeleteFile[]=
{	
	&sItemDelete_Cancel,
    &sItemDeleteFileLast,
	&sItemDeleteFileAll
};
#endif

#if (MENU_EDIT_DELETE_ONE_EN)
PSMENUITEM   sMenuListDeleteOne[]=
{
    &sItemDeleteOne_Yes,
    &sItemDeleteOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListDeleteOneFormat[]=
{
    &sItemDeleteOne_Video,
    &sItemDeleteOne_Image
};
#endif
#endif

#if (MENU_EDIT_DELETE_ALL_EN)
PSMENUITEM   sMenuListDeleteAll[]=
{
    &sItemDeleteAll_Video,
	#if (DSC_MODE_ENABLE)    
    &sItemDeleteAll_Image
	#endif
};

PSMENUITEM   sMenuListDeleteAll_Video[]=
{
    &sItemDeleteAll_Video_Yes,
    &sItemDeleteAll_Video_No
};

PSMENUITEM   sMenuListDeleteAll_Image[]=
{
    &sItemDeleteAll_Image_Yes,
    &sItemDeleteAll_Image_No
};
#endif

#if (MENU_EDIT_PROTECT_EN)
PSMENUITEM   sMenuListProtect[]=
{
#if (MENU_EDIT_PROTECT_ONE_EN)
	&sItemProtectOne,
#endif
#if (MENU_EDIT_UNPROTECT_ONE_EN)	
	&sItemUnProtectOne,
#endif	
#if (MENU_EDIT_PROTECT_ALL_EN)	
    &sItemProtectAll,
#endif    
#if (MENU_EDIT_UNPROTECT_ALL_EN)    
    &sItemUnProtectAll
#endif    
};
#endif

#if (MENU_EDIT_PROTECT_ONE_EN)
PSMENUITEM   sMenuListProtectOne[]=
{
    &sItemProtectOne_Yes,
    &sItemProtectOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListProtectOneFormat[]=
{
    &sItemProtectOne_Video,
    &sItemProtectOne_Image
};
#endif
#endif

#if (MENU_EDIT_UNPROTECT_ONE_EN)
PSMENUITEM   sMenuListUnProtectOne[]=
{
    &sItemUnProtectOne_Yes,
    &sItemUnProtectOne_No
};
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
PSMENUITEM   sMenuListUnProtectOneFormat[] =
{
    &sItemUnProtectOne_Video,
    &sItemUnProtectOne_Image
};
#endif
#endif

#if (MENU_EDIT_PROTECT_ALL_EN)
PSMENUITEM   sMenuListProtectAll[]=
{
    &sItemProtectAll_Video,
	#if (DSC_MODE_ENABLE)     
    &sItemProtectAll_Image
	#endif    
};

PSMENUITEM   sMenuListProtectAll_Video[]=
{
    &sItemProtectAll_Video_Yes,
    &sItemProtectAll_Video_No
};

PSMENUITEM   sMenuListProtectAll_Image[]=
{
    &sItemProtectAll_Image_Yes,
    &sItemProtectAll_Image_No
};
#endif

#if (MENU_EDIT_UNPROTECT_ALL_EN)  
PSMENUITEM   sMenuListUnProtectAll[]=
{
    &sItemUnProtectAll_Video,
	#if (DSC_MODE_ENABLE)     
    &sItemUnProtectAll_Image
	#endif
};

PSMENUITEM   sMenuListUnProtectAll_Video[]=
{
    &sItemUnProtectAll_Video_Yes,
    &sItemUnProtectAll_Video_No
};

PSMENUITEM   sMenuListUnProtectAll_Image[]=
{
    &sItemUnProtectAll_Image_Yes,
    &sItemUnProtectAll_Image_No
};
#endif

PSMENUITEM   sMenuListMainEdit[]=
{
#if (MENU_EDIT_DELETE_EN)
    &sItemDelete,
#endif
#if (MENU_EDIT_PROTECT_EN)    
    &sItemProtect 
#endif    
};

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuEdit =
{
    MENUID_MAIN_MENU_EDIT,                             
    NULL,                                             
    IDS_DS_EDIT_TOOL,                                  
    NULL,                                              
    sizeof(sMenuListMainEdit)/sizeof(PSMENUITEM),   
    sMenuListMainEdit,                                 
    MainMenuEventHandler,                              
    MenuGetDefault,                                   
    0,                                                 
    0,                                                
    0,                                                 
    0                                                  
};

//--------------SUB MENU-------------------

#if (MENU_EDIT_DELETE_EN)

SMENUSTRUCT sSubDeleteFile =
{
    MENUID_SUB_MENU_DELETE_FILE,
    NULL,
    IDS_DS_DELETE,
    NULL,
    sizeof(sMenuListDeleteFile)/sizeof(PSMENUITEM),
    sMenuListDeleteFile,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    IDS_DS_DELETE,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubDelete =
{
    MENUID_SUB_MENU_DELETE,
    NULL,
    IDS_DS_DELETE,
    NULL,
    sizeof(sMenuListDelete)/sizeof(PSMENUITEM),
    sMenuListDelete,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    IDS_DS_DELETE_ALL_DESCRIPTION,
    AHC_TRUE,
    0
};
#endif

#if (MENU_EDIT_DELETE_ALL_EN)
SMENUSTRUCT sSubDeleteAll =
{
    MENUID_SUB_MENU_DELETE_ALL,
    NULL,
    IDS_DS_DELETE_ALL,
    NULL,
    sizeof(sMenuListDeleteAll)/sizeof(PSMENUITEM),
    sMenuListDeleteAll,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubDeleteAll_Video =
{
    MENUID_SUB_MENU_DELETE_ALL_VIDEO,
    NULL,
    IDS_DS_DELETE_ALL,
    NULL,
    sizeof(sMenuListDeleteAll_Video)/sizeof(PSMENUITEM),
    sMenuListDeleteAll_Video,
    SubMenuEventHandler_EditAllFile, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubDeleteAll_Image =
{
    MENUID_SUB_MENU_DELETE_ALL_IMAGE,
    NULL,
    IDS_DS_DELETE_ALL,
    NULL,
    sizeof(sMenuListDeleteAll_Image)/sizeof(PSMENUITEM),
    sMenuListDeleteAll_Image,
    SubMenuEventHandler_EditAllFile,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_EDIT_PROTECT_EN)
SMENUSTRUCT sSubProtect =
{
    MENUID_SUB_MENU_PROTECT,
    NULL,
    IDS_DS_PROTECT,
    NULL,
    sizeof(sMenuListProtect)/sizeof(PSMENUITEM),
    sMenuListProtect,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    IDS_DS_PROTECT_ALL_DESCRIPTION,
    AHC_TRUE,
    0
};
#endif

#if (MENU_EDIT_PROTECT_ALL_EN)
SMENUSTRUCT sSubProtectAll =
{
    MENUID_SUB_MENU_PROTECT_ALL,
    NULL,
    IDS_DS_PROTECT_ALL,
    NULL,
    sizeof(sMenuListProtectAll)/sizeof(PSMENUITEM),
    sMenuListProtectAll,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubProtectAll_Video =
{
    MENUID_SUB_MENU_PROTECT_ALL_VIDEO,
    NULL,
    IDS_DS_PROTECT_ALL,
    NULL,
    sizeof(sMenuListProtectAll_Video)/sizeof(PSMENUITEM),
    sMenuListProtectAll_Video,
    SubMenuEventHandler_EditAllFile,//SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubProtectAll_Image =
{
    MENUID_SUB_MENU_PROTECT_ALL_IMAGE,
    NULL,
    IDS_DS_PROTECT_ALL,
    NULL,
    sizeof(sMenuListProtectAll_Image)/sizeof(PSMENUITEM),
    sMenuListProtectAll_Image,
    SubMenuEventHandler_EditAllFile, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_EDIT_UNPROTECT_ALL_EN)
SMENUSTRUCT sSubUnProtectAll =
{
    MENUID_SUB_MENU_UNPROTECT_ALL,
    NULL,
    IDS_DS_UNPROTECT_ALL,
    NULL,
    sizeof(sMenuListUnProtectAll)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll,
    SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubUnProtectAll_Video =
{
    MENUID_SUB_MENU_UNPROTECT_ALL_VIDEO,
    NULL,
    IDS_DS_UNPROTECT_ALL,
    NULL,
    sizeof(sMenuListUnProtectAll_Video)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll_Video,
    SubMenuEventHandler_EditAllFile, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubUnProtectAll_Image=
{
    MENUID_SUB_MENU_UNPROTECT_ALL_IMAGE,
    NULL,
    IDS_DS_UNPROTECT_ALL,
    NULL,
    sizeof( sMenuListUnProtectAll_Image)/sizeof(PSMENUITEM),
    sMenuListUnProtectAll_Image,
    SubMenuEventHandler_EditAllFile, //SubMenuEventHandler,
    MenuGetDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

#if (MENU_EDIT_DELETE_SELECT_FORMAT)
SMENUSTRUCT sSubDeleteOne =
{
    MENUID_SUB_MENU_DELETE_ALL,
    NULL,
    IDS_DS_DELETE_ALL,
    NULL,
    sizeof(sMenuListDeleteOneFormat)/sizeof(PSMENUITEM),
    sMenuListDeleteOneFormat,
    SubMenuEventHandler,
    MenuGetFormatDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubProtectOne =
{
    MENUID_SUB_MENU_PROTECT_ALL,
    NULL,
    IDS_DS_PROTECT_ALL,
    NULL,
    sizeof(sMenuListProtectOneFormat)/sizeof(PSMENUITEM),
    sMenuListProtectOneFormat,
    SubMenuEventHandler,
    MenuGetFormatDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};

SMENUSTRUCT sSubUnProtectOne =
{
    MENUID_SUB_MENU_UNPROTECT_ALL,
    NULL,
    IDS_DS_UNPROTECT_ALL,
    NULL,
    sizeof(sMenuListUnProtectOneFormat)/sizeof(PSMENUITEM),
    sMenuListUnProtectOneFormat,
    SubMenuEventHandler,
    MenuGetFormatDefault,
    0,
    NULL,
    AHC_TRUE,
    0
};
#endif

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern AHC_BOOL AHC_Thumb_DrawPage(AHC_BOOL bForce);
extern AHC_BOOL MovPBTimer_Stop(void);
extern AHC_BOOL PhotoPBTimer_Stop(void);
extern AHC_BOOL AudPBTimer_Stop(void);

/*===========================================================================
 * Main body
 *===========================================================================*/

UINT32 MenuGetFormatDefault(PSMENUSTRUCT pMenu)
{
	if (GetCurrentOpMode() == JPGPB_MODE)
		return 1;
		
	return 0;
}

AHC_BOOL DrawFileOperationResult(UINT8 status)
{
	switch(status)
	{
		case EDIT_FILE_NO_CARD:
			AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_CARD, 3);	
		break;
				
		case EDIT_FILE_CARD_LOCK:
			AHC_WMSG_Draw(AHC_TRUE, WMSG_CARD_LOCK, 3);
		break;
		
		case EDIT_FILE_CARD_ERROR:
			AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
		break;
		
		case EDIT_FILE_DCF_ERROR:
			AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
		break;
		
		case EDIT_FILE_NO_FILE:
			AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_FILE_IN_BROWSER, 3);
		break;	
		
		default:
		break;
	}
	return AHC_TRUE;
}

UINT8 QuickFileOperation(UINT8 Op)
{
    UINT32          CurObjIdx;
    UINT32          MaxDcfObj; 

    if(!AHC_IsSDInserted() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD) 
    {
    	return EDIT_FILE_NO_CARD;
    }

    if(AHC_IsSDWriteProtect() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD) 
    {
        return EDIT_FILE_CARD_LOCK;
    }
	#if (AHC_MULTI_TRACK_EN == 0)
    if ((MMP_IsScdCamExist() || MMP_IsUSBCamExist()) && m_ubPlaybackRearCam == AHC_TRUE) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    #endif
    AHC_UF_GetCurrentIndex(&CurObjIdx);
    AHC_UF_GetTotalFileCount(&MaxDcfObj);     
    if(MaxDcfObj == 0)
    	return EDIT_FILE_NO_FILE;

	if(!AHC_UF_FileOperation_ByIdx(CurObjIdx, Op, NULL, NULL))
	{
		#if (AHC_MULTI_TRACK_EN == 0)
	    if ((MMP_IsScdCamExist() || MMP_IsUSBCamExist()) && m_ubPlaybackRearCam == AHC_TRUE) {
	        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
	    }
	    #endif
		return EDIT_FILE_DCF_ERROR;
	}
  	else
	{
		#if (AHC_MULTI_TRACK_EN == 0)
	    if ((MMP_IsScdCamExist() || MMP_IsUSBCamExist()) && m_ubPlaybackRearCam == AHC_TRUE) {
	        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
	    }
	    #endif
		return EDIT_FILE_SUCCESS;
	}
}

AHC_BOOL QuickMediaOperation(UINT8 Op)
{
	AHC_BOOL	bPlayMode = AHC_FALSE;
	AHC_BOOL	bCleanWmsgDraw = AHC_TRUE;

	extern MMP_BOOL bFirstTimeGetFreeSpace;

	if(Op==MEDIA_CMD_FORMAT)
	{		
		AHC_BOOL ret = 0;

		CHARGE_ICON_ENABLE(AHC_FALSE);
		
		if(AHC_SDMMC_BasicCheck() == AHC_FALSE) {
		    bCleanWmsgDraw = AHC_FALSE;
			goto L_out;
		}
		
		if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
		{
			AHC_SetMode( AHC_MODE_IDLE );
			bPlayMode = AHC_TRUE;
		}
	
		bFirstTimeGetFreeSpace = AHC_TRUE;
		
		AHC_WMSG_Draw(AHC_TRUE, WMSG_FORMAT_SD_PROCESSING, 10);

        #if (FS_FORMAT_FREE_ENABLE)
        ret = AHC_FormatStorageMedia_FormatFree(AHC_MEDIA_MMC);   
        if( ret == AHC_TRUE )
        {
            SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 0;
        }
        #else
        ret = AHC_FormatStorageMedia(AHC_MEDIA_MMC);   
        #endif
        //why need to mount SD card twice? it cause create sem without releasing.TBD.
        //ret |= AHC_MountStorageMedia(AHC_MEDIA_MMC);
        ret |= AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
 
		AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
	
        if(!ret)
        {
        	AHC_WMSG_Draw(AHC_TRUE, WMSG_FORMAT_SD_CARD_FAIL, 3);
        }
        else   	
        	AHC_WMSG_Draw(AHC_TRUE, WMSG_FORMAT_SD_CARD_OK, 3);

		AHC_OS_SleepMs(2000);
		
L_out:
        if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER)) 
        {
            AHC_Thumb_DrawPage(AHC_TRUE); 
        }
        else if (AHC_CheckCurSysMode(AHC_MODE_PLAYBACK) || bPlayMode)
		{		
			AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
		
			if(GetCurrentOpMode()==MOVPB_MODE)
			{
				MovPBTimer_Stop();
				MovPlaybackParamReset();
			}
			else if(GetCurrentOpMode()==JPGPB_MODE)
			{
				PhotoPBTimer_Stop();
				JpgPlaybackParamReset();
			}
			else if(GetCurrentOpMode()==AUDPB_MODE)
			{
				AudPBTimer_Stop();
				AudPlaybackParamReset();
			}
			else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
			{
				MovPBTimer_Stop();
				MovPlaybackParamReset();
				PhotoPBTimer_Stop();
				JpgPlaybackParamReset();
			}
			else
			{			

			}
		
			Deleting_InBrowser = 1;
		}

		if (bCleanWmsgDraw)
			AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);
		
		CHARGE_ICON_ENABLE(AHC_TRUE);
    }
    else if(Op==MEDIA_CMD_GET_ATTRIBUTE)
	{
		AHC_SDMMC_GetClass(AHC_SD_0);
	}

    return AHC_TRUE;
}

AHC_BOOL MenuItemEditOneConfirmOk(PSMENUITEM pItem, AHC_BOOL bHover)
{
	if(pItem->iItemId == ITEMID_DELETE_ONE_YES){
		if(Deleting_InBrowser)
		{
			BrowserFunc_ThumbnailEditFile(DCF_FILE_DELETE_ALL_CAM);
		}
		else if((Protecting_InBrowser == 1)/* && Protect_File_Confirm*/)
		{
			BrowserFunc_ThumbnailEditFile(DCF_FILE_READ_ONLY_ALL_CAM);
		}
		else if((Protecting_InBrowser == 2)/* && UnProtect_File_Confirm*/)
		{
			if(AHC_IsCurFileCharLock())
				BrowserFunc_ThumbnailEditFile(DCF_FILE_CHAR_UNLOCK_ALL_CAM);
			else
				BrowserFunc_ThumbnailEditFile(DCF_FILE_NON_READ_ONLY_ALL_CAM);
		}
	}
	BrowserFunc_ThumbnailEditFilelComplete();
	
    return AHC_TRUE;
}

#if (MENU_EDIT_DELETE_ONE_EN)
AHC_BOOL MenuItemDeleteOne(PSMENUITEM pItem, AHC_BOOL bHover)
{
	UINT8	ret;

	if (pItem->iItemId == ITEMID_DELETE_ONE
#if (MENU_EDIT_DELETE_SELECT_FORMAT)
	||  pItem->iItemId == ITEMID_DELETE_VIDEO_ONE
	||  pItem->iItemId == ITEMID_DELETE_IMAGE_ONE
#endif
	   )
	{
		if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
		{
			// in Playback mode
			printc("Delete File Directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
			else
			{
				if(GetCurrentOpMode()==MOVPB_MODE)
				{
					MovPBTimer_Stop();
					MovPlaybackParamReset();
				}
				else if(GetCurrentOpMode()==JPGPB_MODE)
				{
					PhotoPBTimer_Stop();
	       		 	JpgPlaybackParamReset();
				}
				else if(GetCurrentOpMode()==AUDPB_MODE)
				{
					AudPBTimer_Stop();
	       		 	AudPlaybackParamReset();
				}
			    else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
				{
					MovPBTimer_Stop();
					MovPlaybackParamReset();
					PhotoPBTimer_Stop();
	       		 	JpgPlaybackParamReset();
				}
				
				Deleting_InBrowser = 1;

#if 0
		    	if(AHC_IsTVConnectEx())
		    		TVFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
		    	else if(AHC_IsHdmiConnect())
		    		HDMIFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);	  
#endif					
			}
		}
		#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_NO_CONFIRM)
		else if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
		{
			// In Browser Mode
			printc("Delete File Directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
			else
			{
				Deleting_InBrowser = 1; 

#if 0				
				if(AHC_IsTVConnectEx())
		    		TVFunc_ThumbnailEditOneFile();
		    	else if(AHC_IsHdmiConnect())
		    		HDMIFunc_ThumbnailEditOneFile();	 
#endif					
			}
		}
		#endif
		else
		{
			// In Browser Mode
			#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_WITH_CONFIRM)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
		        Delete_Option 	 	 = CONFIRM_NOT_YET; 
		        Deleting_InBrowser   = 1;
		        Delete_File_Confirm  = 1;  
			}
			else
			#elif (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_DISABLE)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
			}
			#endif
			{
	        	Delete_Option 	 	 = CONFIRM_NOT_YET; 
	        	Deleting_InBrowser   = 1;
	        	Delete_File_Confirm  = 1;      
			}
	
			//MenuDrawSubPage_EditOneFile(NULL);
			#if (MENU_EDIT_DELETE_SELECT_FORMAT)
		    /* for selecting file format before deleting */
		    if (pItem->iItemId == ITEMID_DELETE_VIDEO_ONE)
		    	SetCurrentOpMode(MOVPB_MODE);
		    else if (pItem->iItemId == ITEMID_DELETE_IMAGE_ONE)
		    	SetCurrentOpMode(JPGPB_MODE);
			#endif

		    #ifdef CFG_MENU_NOT_CHOOSE_FILE_AGAIN //may be defined in config_xxx.h
		    BrowserFunc_ThumbnailEditFile_Option(EVENT_THUMBNAIL_KEY_PLAYBACK);
		    #endif	 	
	    }
	}
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_DELETE_ALL_EN)
AHC_BOOL MenuItemDeleteAll(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT32          MaxDcfObj, i;
    UINT32          CurObjIdx;
    AHC_BOOL        bTmpPlaybackRearCam;
    //set m_ubPlaybackRearCam = False, that DcfObjnum can get all DCFobjnum
    //Otherwise, if m_ubPlaybackRearCam = true, DcfObjnum would only get rearcam file num 
    bTmpPlaybackRearCam = m_ubPlaybackRearCam;
    m_ubPlaybackRearCam = AHC_FALSE;
    if(pItem->iItemId == ITEMID_DELETE_ALL_VIDEO_YES)
    {
        MenuStatePlaybackSelectDB( MOVPB_MODE );
        SetCurrentOpMode(MOVPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if(pItem->iItemId == ITEMID_DELETE_ALL_IMAGE_YES)
    {
        MenuStatePlaybackSelectDB( JPGPB_MODE );
        SetCurrentOpMode(JPGPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else
    {
    	return AHC_TRUE;
    }
    
    if(AHC_SDMMC_BasicCheck() == AHC_FALSE)
    	return AHC_TRUE;

	if(MaxDcfObj == 0)
		return AHC_TRUE;
            
    AHC_UF_SetCurrentIndex(0); 
        
	for(i=0;i<MaxDcfObj;i++) 
	{  
		AHC_UF_GetCurrentIndex(&CurObjIdx);
            
		if(!AHC_UF_FileOperation_ByIdx(CurObjIdx, DCF_FILE_DELETE_ALL_CAM, NULL, NULL))
		{
			AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
			CurObjIdx++;
			AHC_UF_SetCurrentIndex(CurObjIdx); 
		}            
                        
		DrawProgressBar(i, MaxDcfObj, AHC_FALSE);    
	}

    if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER)) 
    {
	    if( JPGPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO);        
	    }
	    else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
	    }
    	else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO_MOVIE);
	    }

        AHC_Thumb_DrawPage(AHC_TRUE); 
    }
#if 1 //Andy Liu TBD. 
    //printc(FG_RED("\r\nPlease modify here!\r\n"));
    //AHC_PRINT_RET_ERROR(0, 0);
#else          
	#if (TVOUT_ENABLE)
	else if(AHC_TV_BROWSER_STATUS == TVFunc_Status() && AHC_IsTVConnectEx()) 
    {
	    if( JPGPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO);        
	    }
	    else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
	    }
    	else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode())
	    {
	        AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO_MOVIE);
	    }

        AHC_Thumb_DrawPage(AHC_TRUE); 
    }
#endif    
	#endif
	else if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
	{		
		printc("Delete All File Complete\r\n");
		
		if(GetCurrentOpMode()==MOVPB_MODE)
		{
			if(pItem->iItemId == ITEMID_DELETE_ALL_VIDEO_YES)
			{
				MovPBTimer_Stop();
				MovPlaybackParamReset();
				Deleting_InBrowser = 1;
#if 0				
		    	if(AHC_IsTVConnectEx())
		    		TVFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
		    	else if(AHC_IsHdmiConnect())
		    		HDMIFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
#endif					
			}
		}
		else if(GetCurrentOpMode()==JPGPB_MODE)
		{
			if(pItem->iItemId == ITEMID_DELETE_ALL_IMAGE_YES)
			{
				PhotoPBTimer_Stop();
				JpgPlaybackParamReset();
				Deleting_InBrowser = 1;
#if 0				
				if(AHC_IsTVConnectEx())
		    		TVFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
		    	else if(AHC_IsHdmiConnect())
		    		HDMIFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
#endif					
			}
		}
		else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
		{
			if(pItem->iItemId == ITEMID_DELETE_ALL_FILE_YES)
			{
				MovPBTimer_Stop();
				MovPlaybackParamReset();
				PhotoPBTimer_Stop();
				JpgPlaybackParamReset();
				Deleting_InBrowser = 1;
#if 0				
				if(AHC_IsTVConnectEx())
		    		TVFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
		    	else if(AHC_IsHdmiConnect())
		    		HDMIFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
#endif					
			}
		}
		else if(GetCurrentOpMode()==AUDPB_MODE)
		{
			AudPBTimer_Stop();
			AudPlaybackParamReset();
			Deleting_InBrowser = 1;
#if 0			
			if(AHC_IsTVConnectEx())
		    	TVFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
		    else if(AHC_IsHdmiConnect())
		    	HDMIFunc_PlaybackEditOneFile(DCF_FILE_DELETE_ALL_CAM);
#endif				
		}
		
		//bForceSwitchBrowser = AHC_TRUE;
	}
    //resume m_ubPlaybackRearCam status
    m_ubPlaybackRearCam = bTmpPlaybackRearCam;
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_DELETE_EN)
AHC_BOOL MenuItemDeleteFile(PSMENUITEM pItem, AHC_BOOL bHover)
{
	switch(pItem->iItemId)
	{
		case ITEMID_DELETE_CANCEL:
			return AHC_TRUE;
		break;

		case ITEMID_DELETE_FILE_LAST:
		{
			#define DEL_LAST_FILE_NUM	(5)
		
		    UINT32          MaxDcfObj, i;
		    UINT32          CurObjIdx;
		    UINT32			StartIdx = 0;

		    MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
		    
		    if(AHC_SDMMC_BasicCheck() == AHC_FALSE)
		    	return AHC_TRUE;

			if(MaxDcfObj == 0)
				return AHC_TRUE;
		    
		    if((int)MaxDcfObj-DEL_LAST_FILE_NUM >= 0)
		    	StartIdx = MaxDcfObj-DEL_LAST_FILE_NUM;
			else
				StartIdx = 0;
			
			AHC_UF_SetCurrentIndex(StartIdx); 
			        
			for(i=StartIdx; i<MaxDcfObj; i++) 
			{  
				AHC_UF_GetCurrentIndex(&CurObjIdx);
			            
				if(!AHC_UF_FileOperation_ByIdx(CurObjIdx, DCF_FILE_DELETE_ALL_CAM, NULL, NULL))
				{
					AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
					CurObjIdx++;
					AHC_UF_SetCurrentIndex(CurObjIdx); 
				}		
			}	
		}	
		break;
		
		case ITEMID_DELETE_FILE_ALL:
		{
		    UINT32          MaxDcfObj, i;
		    UINT32          CurObjIdx;

		    MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
		    
		    if(AHC_SDMMC_BasicCheck() == AHC_FALSE)
		    	return AHC_TRUE;

			if(MaxDcfObj == 0)
				return AHC_TRUE;
		            
		    AHC_UF_SetCurrentIndex(0); 
		        
			for(i=0;i<MaxDcfObj;i++) 
			{  
				AHC_UF_GetCurrentIndex(&CurObjIdx);
		            
				if(!AHC_UF_FileOperation_ByIdx(CurObjIdx, DCF_FILE_DELETE_ALL_CAM, NULL, NULL))
				{
					AHC_WMSG_Draw(AHC_TRUE, WMSG_CANNOT_DELETE, 3);
					CurObjIdx++;
					AHC_UF_SetCurrentIndex(CurObjIdx); 
				}		
			}
		}			
		break;
	}
	return AHC_TRUE;
}
#endif

#if (MENU_EDIT_PROTECT_ONE_EN)
AHC_BOOL MenuItemProtectOne(PSMENUITEM pItem, AHC_BOOL bHover)
{
	UINT8	ret;

	if (pItem->iItemId == ITEMID_PROTECT_ONE
#if (MENU_EDIT_PROTECT_SELECT_FORMAT)
	||  pItem->iItemId == ITEMID_PROTECT_VIDEO_ONE
	||  pItem->iItemId == ITEMID_PROTECT_IMAGE_ONE
#endif
		)
	{
		if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
		{
			printc("Protect File Directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
		}
		#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_NO_CONFIRM)
		else if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
		{
			printc("Protect File Directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
			else
			{
				Protecting_InBrowser = 1;  
#if 0
			    if(AHC_IsTVConnectEx())
			    	TVFunc_ThumbnailEditOneFile();
			    else if(AHC_IsHdmiConnect())
			    	HDMIFunc_ThumbnailEditOneFile();
#endif					
			}
		}
		#endif
		else
		{
			#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_WITH_CONFIRM)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
			    Protect_Option 	 	 = CONFIRM_NOT_YET; 
			    Protecting_InBrowser = 1;
			    Protect_File_Confirm = 1;  
			}
			else
			#elif (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_DISABLE)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
			}
			#endif
			{		
			    Protect_Option 	 	 = CONFIRM_NOT_YET; 
			    Protecting_InBrowser = 1;
			    Protect_File_Confirm = 0; 
		    }

		    
			//MenuDrawSubPage_EditOneFile(NULL);//need to modify ---lei.qin
			#if (MENU_EDIT_PROTECT_SELECT_FORMAT)
		    /* for selecting file format before protecting */
		    if (pItem->iItemId == ITEMID_PROTECT_VIDEO_ONE)
		    	SetCurrentOpMode(MOVPB_MODE);
		    else if (pItem->iItemId == ITEMID_PROTECT_IMAGE_ONE)
		    	SetCurrentOpMode(JPGPB_MODE);
			else if (pItem->iItemId == ITEMID_PROTECT_FILE_ONE)
		    	SetCurrentOpMode(JPGPB_MOVPB_MODE);
			#endif
		}
	}
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_PROTECT_ALL_EN)
AHC_BOOL MenuItemProtectAll(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT32 MaxDcfObj, i;

    if(pItem->iItemId == ITEMID_PROTECT_ALL_VIDEO_YES)
    {
        MenuStatePlaybackSelectDB( MOVPB_MODE );
        SetCurrentOpMode(MOVPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if(pItem->iItemId == ITEMID_PROTECT_ALL_IMAGE_YES)
    {
        MenuStatePlaybackSelectDB( JPGPB_MODE );
        SetCurrentOpMode(JPGPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else
    {
    	return AHC_TRUE;
    }

    if(AHC_SDMMC_BasicCheck() == AHC_FALSE)
    	return AHC_TRUE;

    if(MaxDcfObj == 0)
	{
    	//For clr thumbnail buffer, It need to run in AHC_Thumb_DrawPage() always. ---mantis#1086436
    	//return AHC_TRUE;
	}
	     
	for(i=0;i<MaxDcfObj;i++) 
    {   
		if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_READ_ONLY_ALL_CAM, NULL, NULL))
			return AHC_FALSE;
         		        	
		DrawProgressBar(i, MaxDcfObj, AHC_FALSE);
	}
           
	if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) ) 
	{	    		
		if( JPGPB_MODE == GetCurrentOpMode())
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
		}
		else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode() )
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
		}
		else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode() )
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
		}
	    if(MaxDcfObj >= 1){
    		if( ObjSelect > MaxDcfObj - 1)  
    			ObjSelect = MaxDcfObj - 1;
    	    
    		AHC_UF_SetCurrentIndex(ObjSelect);
        }
		AHC_Thumb_DrawPage(AHC_TRUE); 
	}
#if 0	
    if(AHC_IsTVConnectEx())
        TVFunc_ThumbnailEditOneFile();
    else if(AHC_IsHdmiConnect())
        HDMIFunc_ThumbnailEditOneFile();
#endif		
    
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_UNPROTECT_ONE_EN)
AHC_BOOL MenuItemUnProtectOne(PSMENUITEM pItem, AHC_BOOL bHover)
{
	UINT8 	ret;
	
	if (pItem->iItemId == ITEMID_UNPROTECT_ONE
#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
	|| pItem->iItemId == ITEMID_UNPROTECT_VIDEO_ONE
	|| pItem->iItemId == ITEMID_UNPROTECT_IMAGE_ONE
#endif
	   )
	{
		if(AHC_CheckCurSysMode(AHC_MODE_PLAYBACK))
		{
			printc("UnProtect file directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
		}
		#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_NO_CONFIRM)
		else if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
		{
			printc("UnProtect file directly\r\n");
			
			ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);
			
			if(ret!=EDIT_FILE_SUCCESS)
			{
				DrawFileOperationResult(ret);
			}
			else
			{
				Protecting_InBrowser = 2;  

#if 0
			    if(AHC_IsTVConnectEx())
			    	TVFunc_ThumbnailEditOneFile();
			    else if(AHC_IsHdmiConnect())
			    	HDMIFunc_ThumbnailEditOneFile();
#endif					
			}
		}
		#endif
		else
		{
			#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_WITH_CONFIRM)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
			    UnProtect_Option 	 	= CONFIRM_NOT_YET; 
			    Protecting_InBrowser 	= 2;
			    UnProtect_File_Confirm 	= 1;  
			}
			else
			#elif (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_DISABLE)
			if(AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
			{
				AHC_UF_GetCurrentIndex(&ObjSelect);
			}
			#endif
			{
			    UnProtect_Option 	 	= CONFIRM_NOT_YET; 
			    Protecting_InBrowser 	= 2;
			    UnProtect_File_Confirm 	= 0; 
		    }
		    

			//MenuDrawSubPage_EditOneFile(NULL);
			#if (MENU_EDIT_UNPROTECT_SELECT_FORMAT)
		    /* for selecting file format before protecting */
		    if (pItem->iItemId == ITEMID_UNPROTECT_VIDEO_ONE)
		    	SetCurrentOpMode(MOVPB_MODE);
		    else if (pItem->iItemId == ITEMID_UNPROTECT_IMAGE_ONE)
		    	SetCurrentOpMode(JPGPB_MODE);
			else if (pItem->iItemId == ITEMID_UNPROTECT_FILE_ONE)
		    	SetCurrentOpMode(JPGPB_MOVPB_MODE);
			#endif
		}
	}
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_UNPROTECT_ALL_EN)
AHC_BOOL MenuItemUnProtectAll(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    UINT32          MaxDcfObj, i;

    if(pItem->iItemId == ITEMID_UNPROTECT_ALL_VIDEO_YES)
    {
        MenuStatePlaybackSelectDB( MOVPB_MODE );
        SetCurrentOpMode(MOVPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE); 
    }
    else if(pItem->iItemId == ITEMID_UNPROTECT_ALL_IMAGE_YES)
    {
        MenuStatePlaybackSelectDB( JPGPB_MODE );
        SetCurrentOpMode(JPGPB_MODE);
    	MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO); 
    }
    else
    {
    	return AHC_TRUE;
    }
	
    if(AHC_SDMMC_BasicCheck() == AHC_FALSE)
    	return AHC_TRUE;

	if(MaxDcfObj == 0)
		return AHC_TRUE;
	
	for(i=0;i<MaxDcfObj;i++) 
	{      
		if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_NON_READ_ONLY_ALL_CAM, NULL, NULL))
			return AHC_FALSE;

		if(!AHC_UF_FileOperation_ByIdx(i, DCF_FILE_CHAR_UNLOCK_ALL_CAM, NULL, NULL))
			return AHC_FALSE;
        
		DrawProgressBar(i, MaxDcfObj, AHC_FALSE);
	}
       
	if( AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER) ) 
	{		
		if( JPGPB_MODE == GetCurrentOpMode())
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
		}
		else if ( MOVPB_MODE == GetCurrentOpMode() || AUDPB_MODE == GetCurrentOpMode() )
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);   
		}
		else if ( JPGPB_MOVPB_MODE == GetCurrentOpMode() )
		{
			MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);   
		}

        if(MaxDcfObj >= 1){
    		if( ObjSelect > MaxDcfObj - 1)  
    			ObjSelect = MaxDcfObj - 1;
    	    
    		AHC_UF_SetCurrentIndex(ObjSelect);
        }
		AHC_Thumb_DrawPage(AHC_TRUE); 
    }
#if 0	
    if(AHC_IsTVConnectEx())
        TVFunc_ThumbnailEditOneFile();
    else if(AHC_IsHdmiConnect())
        HDMIFunc_ThumbnailEditOneFile();
#endif
            
#if(LIMIT_MAX_LOCK_FILE_NUM==1)
	if(pItem->iItemId == ITEMID_UNPROTECT_ALL_VIDEO_YES)
	{
		m_ulLockFileNum  = 0;
		m_ulLockEventNum = 0;
	}
#endif    
    
    return AHC_TRUE;
}
#endif

#if (MENU_EDIT_DELETE_ALL_EN || MENU_EDIT_PROTECT_ALL_EN || MENU_EDIT_UNPROTECT_ALL_EN)
UINT32 SubMenuEventHandler_EditAllFile(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    INT32 	iPrevPos;
#if(SUPPORT_TOUCH_PANEL)       
    POINT  	TouchPoint;

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
        pMenu->uiStatus 	= MENU_STATUS_NONE;
		pMenu->iCurrentPos 	= pMenu->iSelected;
		pMenu->bSetOne     	= 0;


		#if (SUPPORT_TOUCH_PANEL)
		KeyParser_TouchItemRegister(&MenuConfirm_TouchButton[0], ITEMNUM(MenuConfirm_TouchButton));
		#endif
	    MenuDrawSubPage_ConfirmPage( pMenu );
	    
	break;

	#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_UP:
	#else
	case MENU_LEFT:	
	#endif
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif

        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, -1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
	break;
		
	#if (DIR_KEY_TYPE==KEY_TYPE_2KEY)
	case MENU_DOWN:
	#else
	case MENU_RIGHT:
	#endif
		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif
        
        iPrevPos = pMenu->iCurrentPos;
        pMenu->iCurrentPos = OffsetItemNumber( pMenu->iCurrentPos, 0, pMenu->iNumOfItems-1, 1, AHC_FALSE );

        MenuDrawChangeSubItem_ConfirmPage( pMenu, pMenu->iCurrentPos, iPrevPos, pMenu->iSelected );
	break;
	
	case MENU_OK            :
	case MENU_SET_ONE		:

		#ifdef SLIDE_MENU
		if(IsSlidingMenu())
			break;
		#endif
		
        if(ulEvent==MENU_SET_ONE)
        {
       		pMenu->iCurrentPos = ulParam;
        	pMenu->iSelected   = ulParam;
			pMenu->bSetOne   = 1;
        	pMenu->uiStatus |= MENU_STATUS_PRESSED;
        	pMenu->uiStatus |= MENU_STATUS_ITEM_TOUCHED;
		}
		else
		{	
			pMenu->bSetOne   = 1;
	        pMenu->iSelected = pMenu->iCurrentPos;
	        pMenu->uiStatus |= MENU_STATUS_PRESSED;		
		}
		       
        if( CommonMenuOK( pMenu, AHC_TRUE ) == AHC_TRUE )
        {	
        	if(Deleting_InBrowser || Protecting_InBrowser)
			{
				printc("Delete/Protect/UnProtect Change to Browser Mode1\r\n");
				// To check is there file in card, it no any file
				// to reset Delete/(Un)Protect file in broswer flags.
				// Otherwise those flag will make key/device events to
				// be NULL!! UI will be stuck
				BrowserFunc_ThumbnailEditCheckFileObj();
				return MENU_ERR_EXIT;
			}
        	else
        	{
    		    #if 0//#ifdef CFG_MENU_NOT_CHOOSE_FILE_AGAIN //may be defined in config_xxx.h
	        	if(AHC_IsTVConnectEx())
	        	{
	        		TVFunc_ThumbnailEditOneFile();
					return MENU_ERR_OK;
				}
				else	
	        	#endif
	        	{
		        	PSMENUSTRUCT pCurrMenu = NULL;
		        		        	
		        	SetCurrentMenu(&sMainMenuPlayback);
		        	
		        	pCurrMenu = GetCurrentMenu();

		    		if( pCurrMenu == NULL )
		    		{
		    			return MENU_ERR_EXIT;
		    		}

		    		pCurrMenu->pfEventHandler(pCurrMenu, MENU_INIT, 0);
				}
			}

            return MENU_ERR_OK;
        }
	break;
		
	case MENU_MENU          :
    {
        #if 0//defined(SLIDE_MENU) && (CUR_SUBMENU_STYLE==SUBMENU_SIDE_ICONPAGE)
        
		StartSlideMenu(POS_2NDMENU_SLIDEMENU_POS_X, SLIDE_SPEED, MENU_HIDE, 1);		
		
		#else    

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
        
    	#endif
    }
	break;


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

