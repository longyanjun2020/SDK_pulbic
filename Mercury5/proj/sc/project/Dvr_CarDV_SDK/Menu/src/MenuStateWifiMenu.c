/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_display.h"
#include "AHC_MACRO.h"
#include "ahc_menu.h"
#include "ahc_common.h"
#include "ahc_gui.h"
#include "ahc_utility.h"
#include "ahc_video.h"
#include "AHC_WarningMSG.h"
#include "Ahc_Parameter.h"
#include "ahc_general_cardv.h"
#include "ahc_general.h"
#include "MenuCommon.h"
#include "MenuStateWifiMenu.h"
#include "MenuStateModeSelectMenu.h"
#include "MenuSetting.h"
#include "MenuStateMenu.h"
#include "MenuDrawingFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "ledcontrol.h"
#if (SD_UPDATE_FW_EN)
#include "SD_Updater.h"
#endif

#include "netconf.h"

/*===========================================================================
 * Local function
 *===========================================================================*/ 
AHC_BOOL MenuItemWifiMode(PSMENUITEM pItem, AHC_BOOL bIsHover);
#if (MENU_WIFI_MODE_AP_EN) 
AHC_BOOL MenuItemWifiAP(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN)
AHC_BOOL MenuItemWifiStation1(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_WIFI_STATION2_EN)
AHC_BOOL MenuItemWifiStation2(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_WIFI_STATION3_EN)
AHC_BOOL MenuItemWifiStation3(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_WIFI_STATION4_EN)
AHC_BOOL MenuItemWifiStation4(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_WIFI_STATION5_EN)
AHC_BOOL MenuItemWifiStation5(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#if (MENU_WIFI_STATION6_EN)
AHC_BOOL MenuItemWifiStation6(PSMENUITEM pItem, AHC_BOOL bIsHover);
#endif
#endif
UINT32   MenuGetDefault_WIFI(PSMENUSTRUCT pMenu);

/*===========================================================================
 * Global varible : Menu
 *===========================================================================*/

SMENUSTRUCT sMainMenuWifi;

SMENUSTRUCT sSubWifiMode;

SMENUSTRUCT sSubWifiAP_SSID;
SMENUSTRUCT sSubWifiAP_PSWD;

SMENUSTRUCT sSubWifiStation1_SSID;
SMENUSTRUCT sSubWifiStation1_PSWD;
SMENUSTRUCT sSubWifiStation2_SSID;
SMENUSTRUCT sSubWifiStation2_PSWD;
SMENUSTRUCT sSubWifiStation3_SSID;
SMENUSTRUCT sSubWifiStation3_PSWD;
SMENUSTRUCT sSubWifiStation4_SSID;
SMENUSTRUCT sSubWifiStation4_PSWD;
SMENUSTRUCT sSubWifiStation5_SSID;
SMENUSTRUCT sSubWifiStation5_PSWD;
SMENUSTRUCT sSubWifiStation6_SSID;
SMENUSTRUCT sSubWifiStation6_PSWD;

/*===========================================================================
 * Global varible : Item Structure
 *===========================================================================*/ 
#if (MENU_WIFI_MODE_EN)
SMENUITEM sItemWifiMode			   = { ITEMID_WIFI_MODE_1,  		 &BMICON_MOVIE_RES_VGA30P, 	IDS_DS_WIFI_MODE,	&sSubWifiMode, 0,		 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiMode_AP	   = { ITEMID_SUB_WIFI_MODE_AP, 	 &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiMode, 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiMode_STA	   = { ITEMID_SUB_WIFI_MODE_STATION, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiMode, 0, AHC_TRUE, NULL };
#endif


#if (MENU_WIFI_MODE_AP_EN)
#if (MENU_WIFI_AP_SSID_EN)
SMENUITEM sItemWifiAP_SSID  	= { ITEMID_WIFI_AP_SSID,  &BMICON_MOVIE_RES_VGA30P, 	IDS_DS_WIFI_AP_SSID,	&sSubWifiAP_SSID, 0, 		 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiAP_SSID      = { ITEMID_SUB_WIFI_AP_SSID, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiAP, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_AP_PSWD_EN)
SMENUITEM sItemWifiAP_PSWD  	= { ITEMID_WIFI_AP_PSWD, &BMICON_MOVIE_RES_VGA30P, 	IDS_DS_WIFI_AP_PASSWORD,	&sSubWifiAP_PSWD, 0, 		 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiAP_PSWD      = { ITEMID_SUB_WIFI_AP_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiAP, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN)
#if (MENU_WIFI_STATION1_SSID_EN)
SMENUITEM sItemWifiStation1_SSID  	= { ITEMID_WIFI_STATION1_SSID,  &BMICON_MOVIE_RES_VGA30P, 	IDS_DS_WIFI_STATION1_SSID,	&sSubWifiStation1_SSID, 0, 		 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation1_SSID      = { ITEMID_SUB_WIFI_STATION1_SSID, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation1, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION1_PSWD_EN)
SMENUITEM sItemWifiStation1_PSWD  	= { ITEMID_WIFI_STATION1_PSWD, &BMICON_MOVIE_RES_VGA30P, 	IDS_DS_WIFI_STATION1_PASSWORD,	&sSubWifiStation1_PSWD, 0, 		 0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation1_PSWD      = { ITEMID_SUB_WIFI_STATION1_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation1, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_STATION2_EN)
#if (MENU_WIFI_STATION2_SSID_EN)
SMENUITEM sItemWifiStation2_SSID  	= { ITEMID_WIFI_STATION2_SSID, 	&BMICON_QUALITY_SHQ, IDS_DS_WIFI_STATION2_SSID,	&sSubWifiStation2_SSID, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation2_SSID      = { ITEMID_SUB_WIFI_STATION2_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation2, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION2_PSWD_EN)
SMENUITEM sItemWifiStation2_PSWD    	= { ITEMID_WIFI_STATION2_PSWD, 		&BMICON_QUALITY_HQ,  IDS_DS_WIFI_STATION2_PASSWORD,	&sSubWifiStation2_PSWD, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation2_PSWD      = { ITEMID_SUB_WIFI_STATION2_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation2, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_STATION3_EN)
#if (MENU_WIFI_STATION3_SSID_EN)
SMENUITEM sItemWifiStation3_SSID  	= { ITEMID_WIFI_STATION3_SSID,	 	&BMICON_OPTION_CLOSE, 	IDS_DS_WIFI_STATION3_SSID,	&sSubWifiStation3_SSID, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation3_SSID      = { ITEMID_SUB_WIFI_STATION3_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation3, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION3_PSWD_EN)
SMENUITEM sItemWifiStation3_PSWD     = { ITEMID_WIFI_STATION3_PSWD, 	&BMICON_CLIPTIME_1MIN, 	IDS_DS_WIFI_STATION3_PASSWORD,	&sSubWifiStation3_PSWD, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation3_PSWD      = { ITEMID_SUB_WIFI_STATION3_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation3, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_STATION4_EN)
#if (MENU_WIFI_STATION4_SSID_EN)
SMENUITEM sItemWifiStation4_SSID 	= { ITEMID_WIFI_STATION4_SSID,  &BMICON_OFFTIME_0MIN, 	IDS_DS_WIFI_STATION4_SSID,	&sSubWifiStation4_SSID, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation4_SSID      = { ITEMID_SUB_WIFI_STATION4_SSID, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation4, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION4_PSWD_EN)
SMENUITEM sItemWifiStation4_PSWD  	= { ITEMID_WIFI_STATION4_PSWD, NULL, 					IDS_DS_WIFI_STATION4_PASSWORD, &sSubWifiStation4_PSWD, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation4_PSWD      = { ITEMID_SUB_WIFI_STATION4_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation4, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_STATION5_EN)
#if (MENU_WIFI_STATION5_SSID_EN)
SMENUITEM sItemWifiStation5_SSID 	= { ITEMID_WIFI_STATION5_SSID,  &BMICON_OFFTIME_5SEC, 	IDS_DS_WIFI_STATION5_SSID,	&sSubWifiStation5_SSID, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation5_SSID      = { ITEMID_SUB_WIFI_STATION5_SSID, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation5, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION5_PSWD_EN)
SMENUITEM sItemWifiStation5_PSWD 	= { ITEMID_WIFI_STATION5_PSWD, &BMICON_OFFTIME_10SEC, IDS_DS_WIFI_STATION5_PASSWORD,	&sSubWifiStation5_PSWD, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation5_PSWD      = { ITEMID_SUB_WIFI_STATION5_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation5, 0, AHC_TRUE, NULL };
#endif
#endif

#if (MENU_WIFI_STATION6_EN)
#if (MENU_WIFI_STATION6_SSID_EN)
SMENUITEM sItemWifiStation6_SSID 	= { ITEMID_WIFI_STATION6_SSID,  &BMICON_OFFTIME_5SEC, 	IDS_DS_WIFI_STATION6_SSID,	&sSubWifiStation6_SSID, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation6_SSID      = { ITEMID_SUB_WIFI_STATION6_SSID, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation6, 0, AHC_TRUE, NULL };
#endif
#if (MENU_WIFI_STATION6_PSWD_EN)
SMENUITEM sItemWifiStation6_PSWD 	= { ITEMID_WIFI_STATION6_PSWD, &BMICON_OFFTIME_10SEC, IDS_DS_WIFI_STATION6_PASSWORD,	&sSubWifiStation6_PSWD, 0, 		0, AHC_TRUE, NULL };
SMENUITEM sSubItemWifiStation6_PSWD      = { ITEMID_SUB_WIFI_STATION6_PSWD, &BMICON_MENU_REC_MODE, NULL, NULL, MenuItemWifiStation6, 0, AHC_TRUE, NULL };
#endif
#endif
#endif
/*===========================================================================
 * Global varible : Item Lists 
 *===========================================================================*/ 
	
PSMENUITEM	 sMenuLisWifiMode[] =
{
	&sSubItemWifiMode_AP,
	&sSubItemWifiMode_STA
};


#if (MENU_WIFI_MODE_AP_EN)
#if (MENU_WIFI_AP_SSID_EN)
PSMENUITEM   sMenuLisWifiAP_SSID[] =
{
    &sSubItemWifiAP_SSID
};
#endif

#if (MENU_WIFI_AP_PSWD_EN) 
PSMENUITEM   sMenuLisWifiAP_PSWD[] =
{   
    &sSubItemWifiAP_PSWD
};
#endif
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN)
#if (MENU_WIFI_STATION1_SSID_EN)
PSMENUITEM   sMenuLisWifiStation1_SSID[] =
{
    &sSubItemWifiStation1_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION1_EN)
#if (MENU_WIFI_STATION1_PSWD_EN) 
PSMENUITEM   sMenuLisWifiStation1_PSWD[] =
{   
    &sSubItemWifiStation1_PSWD
};
#endif
#endif

#if (MENU_WIFI_STATION2_EN)
#if (MENU_WIFI_STATION2_SSID_EN)
PSMENUITEM   sMenuLisWifiStation2_SSID[] =
{
    &sSubItemWifiStation2_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION2_EN)
#if (MENU_WIFI_STATION2_PSWD_EN)
PSMENUITEM   sMenuLisWifiStation2_PSWD[] =
{    
    &sSubItemWifiStation2_PSWD
};
#endif
#endif

#if (MENU_WIFI_STATION3_EN)
#if (MENU_WIFI_STATION3_SSID_EN)
PSMENUITEM   sMenuLisWifiStation3_SSID[] =
{
    &sSubItemWifiStation3_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION3_EN)
#if (MENU_WIFI_STATION3_PSWD_EN)
PSMENUITEM   sMenuLisWifiStation3_PSWD[] =
{    
    &sSubItemWifiStation3_PSWD
};
#endif
#endif

#if (MENU_WIFI_STATION4_EN)
#if (MENU_WIFI_STATION4_SSID_EN)
PSMENUITEM   sMenuLisWifiStation4_SSID[] =
{
    &sSubItemWifiStation4_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION4_EN)
#if (MENU_WIFI_STATION4_PSWD_EN)  
PSMENUITEM   sMenuLisWifiStation4_PSWD[] =
{  
    &sSubItemWifiStation4_PSWD
};
#endif
#endif

#if (MENU_WIFI_STATION5_EN)
#if (MENU_WIFI_STATION5_SSID_EN)
PSMENUITEM   sMenuLisWifiStation5_SSID[] =
{
    &sSubItemWifiStation5_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION5_EN)
#if (MENU_WIFI_STATION5_PSWD_EN)
PSMENUITEM   sMenuLisWifiStation5_PSWD[] =
{    
    &sSubItemWifiStation5_PSWD
};
#endif
#endif

#if (MENU_WIFI_STATION6_EN)
#if (MENU_WIFI_STATION6_SSID_EN)
PSMENUITEM   sMenuLisWifiStation6_SSID[] =
{
    &sSubItemWifiStation6_SSID
};
#endif
#endif

#if (MENU_WIFI_STATION6_EN)
#if (MENU_WIFI_STATION6_PSWD_EN)
PSMENUITEM   sMenuLisWifiStation6_PSWD[] =
{    
    &sSubItemWifiStation6_PSWD
};
#endif
#endif
#endif

PSMENUITEM   sMenuListMainWifi[] =
{
	&sItemWifiMode,

#if (MENU_WIFI_MODE_AP_EN)
#if (MENU_WIFI_AP_SSID_EN)
	&sItemWifiAP_SSID,
#endif
#if (MENU_WIFI_AP_PSWD_EN)
	&sItemWifiAP_PSWD,
#endif
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN)
#if (MENU_WIFI_STATION1_SSID_EN)
    &sItemWifiStation1_SSID,
#endif
#if (MENU_WIFI_STATION1_PSWD_EN)
    &sItemWifiStation1_PSWD,
#endif
#endif

#if (MENU_WIFI_STATION2_EN)
#if (MENU_WIFI_STATION2_SSID_EN)
    &sItemWifiStation2_SSID,
#endif
#if (MENU_WIFI_STATION2_PSWD_EN)
    &sItemWifiStation2_PSWD,
#endif
#endif

#if (MENU_WIFI_STATION3_EN)
#if (MENU_WIFI_STATION3_SSID_EN)
    &sItemWifiStation3_SSID,
#endif
#if (MENU_WIFI_STATION3_PSWD_EN)
    &sItemWifiStation3_PSWD,
#endif
#endif

#if (MENU_WIFI_STATION4_EN)
#if (MENU_WIFI_STATION4_SSID_EN)
    &sItemWifiStation4_SSID,
#endif
#if (MENU_WIFI_STATION4_PSWD_EN)
    &sItemWifiStation4_PSWD,
#endif
#endif

#if (MENU_WIFI_STATION5_EN)
#if (MENU_WIFI_STATION5_SSID_EN)
    &sItemWifiStation5_SSID,
#endif
#if (MENU_WIFI_STATION5_PSWD_EN)
    &sItemWifiStation5_PSWD,
#endif
#endif

#if (MENU_WIFI_STATION6_EN)
#if (MENU_WIFI_STATION6_SSID_EN)
    &sItemWifiStation6_SSID,
#endif
#if (MENU_WIFI_STATION6_PSWD_EN)
    &sItemWifiStation6_PSWD,
#endif
#endif
#endif
};

unsigned char ucWifiMode = 0;	

/*===========================================================================
 * Global variable : Menu Structure
 *===========================================================================*/

SMENUSTRUCT   sMainMenuWifi =
{
    MENUID_MAIN_MENU_WIFI,                               
    NULL,                                                 
    IDS_DS_MOVIE_MODE,                                 
    NULL,                                              
    sizeof(sMenuListMainWifi)/sizeof(PSMENUITEM),   
    sMenuListMainWifi,                               
    MainMenuEventHandler,                             
    MenuGetDefault,                                   
    0,                                                
    0,                                                
    0,                                                
    0                                               
};

//--------------SUB MENU-------------------

SMENUSTRUCT sSubWifiMode =
{
	MENUID_SUB_MENU_WIFI_MODE_1,
	NULL,
	IDS_DS_MOVIE_MODE,
	NULL,
	sizeof(sMenuLisWifiMode)/sizeof(PSMENUITEM),
	sMenuLisWifiMode,
	SubMenuEventHandler,
	MenuGetDefault_WIFI,
	0,
	IDS_DS_MOVIE_MODE_DESCRIPTION,
	AHC_FALSE,
	0
};

#if (MENU_WIFI_MODE_AP_EN)
#if (MENU_WIFI_AP_SSID_EN)
SMENUSTRUCT sSubWifiAP_SSID =
{
    MENUID_SUB_MENU_WIFI_AP_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiAP_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiAP_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_AP_PSWD_EN)
SMENUSTRUCT sSubWifiAP_PSWD =
{
    MENUID_SUB_MENU_WIFI_AP_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiAP_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiAP_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN)
#if (MENU_WIFI_STATION1_SSID_EN)
SMENUSTRUCT sSubWifiStation1_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION1_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation1_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation1_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION1_PSWD_EN)
SMENUSTRUCT sSubWifiStation1_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION1_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation1_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation1_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_STATION2_EN)
#if (MENU_WIFI_STATION2_SSID_EN)
SMENUSTRUCT sSubWifiStation2_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION2_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation2_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation2_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION2_PSWD_EN)
SMENUSTRUCT sSubWifiStation2_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION2_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation2_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation2_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_STATION3_EN)
#if (MENU_WIFI_STATION3_SSID_EN)
SMENUSTRUCT sSubWifiStation3_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION3_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation3_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation3_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION3_PSWD_EN)
SMENUSTRUCT sSubWifiStation3_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION3_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation3_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation3_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_STATION4_EN)
#if (MENU_WIFI_STATION4_SSID_EN)
SMENUSTRUCT sSubWifiStation4_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION4_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation4_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation4_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION4_PSWD_EN)
SMENUSTRUCT sSubWifiStation4_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION4_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation4_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation4_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_STATION5_EN)
#if (MENU_WIFI_STATION5_SSID_EN)
SMENUSTRUCT sSubWifiStation5_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION5_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation5_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation5_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION5_PSWD_EN)
SMENUSTRUCT sSubWifiStation5_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION5_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation5_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation5_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif

#if (MENU_WIFI_STATION6_EN)
#if (MENU_WIFI_STATION6_SSID_EN)
SMENUSTRUCT sSubWifiStation6_SSID =
{
    MENUID_SUB_MENU_WIFI_STATION6_SSID,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation6_SSID)/sizeof(PSMENUITEM),
    sMenuLisWifiStation6_SSID,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif

#if (MENU_WIFI_STATION6_PSWD_EN)
SMENUSTRUCT sSubWifiStation6_PSWD =
{
    MENUID_SUB_MENU_WIFI_STATION6_PSWD,
    NULL,
    IDS_DS_MOVIE_MODE,
    NULL,
    sizeof(sMenuLisWifiStation6_PSWD)/sizeof(PSMENUITEM),
    sMenuLisWifiStation6_PSWD,
    SubMenuEventHandler_Keyboard,//SubMenuEventHandler,
    MenuGetDefault_WIFI,
    0,
    IDS_DS_MOVIE_MODE_DESCRIPTION,
    AHC_FALSE,
    0
};
#endif
#endif
#endif
/*===========================================================================
 * Main body
 *===========================================================================*/
//unsigned char ucWifiMode = 0;
#if (MENU_WIFI_MODE_EN) 	
AHC_BOOL MenuItemWifiMode(PSMENUITEM pItem, AHC_BOOL bIsHover) 
{
    ucWifiMode = pItem->iItemId - ITEMID_SUB_WIFI_MODE_AP;
	printc("wifi mode is %d\n",ucWifiMode);
	
	return AHC_TRUE;
}
#endif

#if (MENU_WIFI_MODE_AP_EN) 
AHC_BOOL MenuItemWifiAP(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
	return AHC_TRUE;
}
#endif

#if (MENU_WIFI_MODE_STATION_EN)
#if (MENU_WIFI_STATION1_EN) 
AHC_BOOL MenuItemWifiStation1(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif

#if (MENU_WIFI_STATION2_EN) 
AHC_BOOL MenuItemWifiStation2(PSMENUITEM pItem, AHC_BOOL bIsHover)
{

    return AHC_TRUE;
}
#endif

#if (MENU_WIFI_STATION3_EN) 
AHC_BOOL MenuItemWifiStation3(PSMENUITEM pItem, AHC_BOOL bIsHover)
{

    return AHC_TRUE;
}
#endif

#if (MENU_WIFI_STATION4_EN) 
AHC_BOOL MenuItemWifiStation4(PSMENUITEM pItem, AHC_BOOL bIsHover)
{

    return AHC_TRUE;
}
#endif

#if (MENU_WIFI_STATION5_EN) 
AHC_BOOL MenuItemWifiStation5(PSMENUITEM pItem, AHC_BOOL bIsHover)
{

    return AHC_TRUE;
}
#endif

#if (MENU_WIFI_STATION6_EN) 
AHC_BOOL MenuItemWifiStation6(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}
#endif
#endif

UINT32 MenuGetDefault_WIFI(PSMENUSTRUCT pMenu)
{
	UINT32		 DefaultValue = 0;

	switch( pMenu->iMenuId )
	{
		case MENUID_SUB_MENU_WIFI_MODE_1:
			DefaultValue = ucWifiMode;
			break;

		default:
			DefaultValue = 0;
			break;
	}

	return DefaultValue;

}




