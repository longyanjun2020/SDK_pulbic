////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_WiFiApp_priv.h
*
* Class Id: CLSID_WiFiApp
*
* @version $Id$
*/
#ifndef __MMI_WIFIAPP_PRIV_H__
#define __MMI_WIFIAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_wifiApp.h"
#include "mmi_btsrv.h"
#include "mmi_btsrv_def.h"
#include "mmi_common_content.h"
#include "mae_textlabel.h"
#include "mmi_wdg_menu.h"
#include "mmi_wdg_input.h"
#include "mmi_wdg_doubleitem.h"
#include "mmi_srv_bt.h"
#include "mmi_srv_evtcenter.h"
#include "mmi_srv_filemgr.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_wlan.h"
#include "mmi_wifiapp_id.h"
#include "WiFiApp_resource.h"
#include "mmi_wlansrv.h"
#include "mmi_launcher_filemanager.h"


/* This option is used to turn the backlight on always for the test */
/* #define __WIFI_BACKLIGHT_ALWAYS_ON__ */
#ifdef __WIFI_BACKLIGHT_ALWAYS_ON__
#include "mmi_srv_core.h"
#endif


/*=============================================================*/
// Data type definition
/*=============================================================*/


/* */
#define WIFI_DIAlOG_RELEASE_TIMER               (2000)
#define WIFI_DIAlOG_RELEASE_TIMER_LONG          (5000)
#define WIFI_AUTO_CONNECT_TIMER                 (25000)
#define WIFI_MAX_NUM_OF_AP                      (16)
#define WIFI_SIGNAL_LEVEL_LOW_LOWER_BOUND       (-200)
#define WIFI_SIGNAL_LEVEL_LOW_UPPER_BOUND       (-70)
#define WIFI_SIGNAL_LEVEL_MEDIUM_LOWER_BOUND    WIFI_SIGNAL_LEVEL_LOW_UPPER_BOUND
#define WIFI_SIGNAL_LEVEL_MEDIUM_UPPER_BOUND    (-45)
#define WIFI_SIGNAL_LEVEL_GOOD_LOWER_BOUND      WIFI_SIGNAL_LEVEL_MEDIUM_UPPER_BOUND
#define WIFI_SIGNAL_LEVEL_GOOD_UPPER_BOUND      (-10)
#define WIFI_MODEL_INFRASTRUCTURE               (0)
#define WIFI_MODEL_AD_HOC                       (1)
#define WIFI_SPEED_11M                          (11)
#define WIFI_SPEED_54M                          (54)
#define WIFI_DETAIL_LEN                         (256)
#define WIFI_MAX_NUM_OF_OTHERMENUITEM           (9)
#define WIFI_CERT_FULL_PATH_HEAD                "fs:"


/* */
extern u8 g_SecurityMode;


/* */
typedef enum
{
    WIFI_OPTIONMENU_MAIN_CONNECT = 0,
    WIFI_OPTIONMENU_MAIN_DISCONNECT,
    WIFI_OPTIONMENU_MAIN_CHANGE,
    WIFI_OPTIONMENU_MAIN_CONNECT_SET,
    WIFI_OPTIONMENU_MAIN_REFRESH,
    WIFI_OPTIONMENU_MAIN_FILTER,
    WIFI_OPTIONMENU_MAIN_MAC_ADDRESS,
    WIFI_OPTIONMENU_MAIN_DETAILS,
    WIFI_OPTIONMENU_MAIN_INSTALL_CERT,
    WIFI_OPTIONMENU_MAIN_SIZE
} WiFiAppOptionMenu_e;


/* */
typedef enum
{
    WiFiApp_MODE_WIFI_ON = 0,
    WiFiApp_MODE_WIFI_OFF
} WiFiAppMode_e;


/* */
typedef enum
{
    WiFiApp_AP_IN_FILTER_LIST = 0,
    WiFiApp_AP_IN_CURRENT_LIST,
    WiFiApp_AP_IN_BOTH_LIST
}WiFiAppAPStatus_e;


/* */
typedef enum
{
    WIFIAPP_IP_INPUT_FOR_CONNECT_SET = 0,
    WIFIAPP_IP_INPUT_FOR_OTHER
} WiFiAppIpInputFor_e;


/* */
typedef struct
{
    ABL_WiFiScanResult_t    tWiFiScanResult;
    boolean                 bIsConnect;                 /* Is connecting to this access point */
    boolean                 bIsFilter;                  /* Access point Is filtered */
    boolean                 bIsLimitedConnection;       /* Is this is limited connection */
}WiFiAccessPointInfo_t;


/* */
typedef enum
{
    WIFIAPP_MENU_SECURITY_NONE = 0,
    WIFIAPP_MENU_SECURITY_WEP,
    WIFIAPP_MENU_SECURITY_WPA,
    WIFIAPP_MENU_SECURITY_WPA2,
    WIFIAPP_MENU_SECURITY_WAPI_PSK,
    WIFIAPP_MENU_SECURITY_WAPI_CERT,
    WIFIAPP_MENU_SECURITY_SIZE
} WiFiAppSecurityId_e;


/* */
typedef enum
{
    WIFIAPP_CONNECT_TYPE_DHCP = 0,
    WIFIAPP_CONNECT_TYPE_STATIC
} WiFiAppConnectType_e;


/* */
typedef struct
{
    u32                     nIPValue_Addr;
    u32                     nIPValue_SubMask;
    u32                     nIPValue_Router;
    u32                     nIPValue_MasterDns;
    u32                     nIPValue_SlaveDns;
} WiFiAppStaticIP_t;


/* */
typedef enum
{
    WIFIAPP_CERT_PICKED_1 = 0,
    WIFIAPP_CERT_PICKED_2,
    WIFIAPP_CERT_PICKED_NOTSUPPORT
} WiFiAppCertPickMode_e;


/* */
typedef struct
{
    boolean                 bIsCaOK;
    boolean                 bIsClientOK;
    WiFiAppCertPickMode_e   eMode;
    WLANSRV_CertPath_t      tPathCa;
    WLANSRV_CertPath_t      tPathClient;
} WiFiAppCertPickData_t;


/* */
typedef struct
{
    WiFiAccessPointInfo_t   tPickedAPInfo;
}WiFiAppSelectedAP_t;


/* */
typedef struct
{
    APPLET_BASE_ELEMENTS;

    WiFiAppSecurityId_e     eSecurity;
    WiFiAppLaunchedMode_e   eLaunchedMode;
    WiFiAppConnectType_e    eConnectType;
    MenuItemId_e            eSetIpType;
    WiFiAppIpInputFor_e     eIpInputFor;

    u32                     nAPCount;
    u32                     nSelectedAPIndex;

    boolean                 bConnectingPwdExistedAP;
    boolean                 bIsDisconnecting;
    boolean                 bConnectSetInitEntry;

    MAE_WChar               *pTxtInputPwd;
    MAE_WChar               *pTxtInputName;

    WiFiAccessPointInfo_t   *ptAPListInfo;
    WiFiAccessPointInfo_t   tConnectedAPInfo;
    WiFiAppStaticIP_t       tStaticIP;

    /* Main menu widget */
    IWidget                 *pMainMenuWdg;
    IWidget                 *pMainMenuWdg_OnOff;

    /* Password input widget */
    IWidget                 *pPwdInputWdg;

    /* Name input widget */
    IWidget                 *pNameInputWdg;

    /* IP input widget */
    IWidget                 *pIpInputWdg;

    /* Hide-AP menu widget */
    IWidget                 *pHideAPMenuWdg;

    /* Connect Set menu widget */
    IWidget                 *pConnectSetMenuWdg;

    /* Other menu widget */
    IWidget                 *pOtherMenuWdg;

    /* Security menu widget */
    IWidget                 *pSecurityMenuWdg;

#ifdef __WIFI_BACKLIGHT_ALWAYS_ON__
    BKLInfo                 tBKLightDefaultInfo;
#endif

    /* Cert List munu widget */
    IWidget                 *pCertListMenuWdg;

    /* Cert List munu widget */
    IWidget                 *pCertOptionMenuWdg;

    /* User's selected certificate data */
    WiFiAppCertPickData_t   tPickData;

    /* How many installed certificate in it */
    u32                     nCertCount;

    /* Selected certificate record index */
    u32                     nSelectedCertIndex;

    /* Record the corresponding AP */
    WiFiAppSelectedAP_t     tSelectedAP;

    /* Record the highlighted item index */
    u32                     nHighlightedIndex;

    /* Record teh first item index */
    u32                     nFirstItemIndex;

    /* User trigger the refresh (scan) activity */
    boolean                 bIsSearchingDlgCreated;
} WiFiAppData_t;


/* */
typedef enum
{
    WIFIAPP_WND_MAIN = WND_ID_APP_BASE,
    WIFIAPP_WND_WIFI_OFF,
    WIFIAPP_WND_MAIN_OPTIONMENU,
    WIFIAPP_WND_PASSWORD_INPUT,
    WIFIAPP_WND_HIDE_AP,
    WIFIAPP_WND_MAC_ADDRESS,
    WIFIAPP_WND_DETAILS,
    WIFIAPP_WND_HIDDENSSID_OTHER,
    WIFIAPP_WND_HIDDENSSID_NAME,
    WIFIAPP_WND_HIDDENSSID_PASSWORD_INPUT,
    WIFIAPP_WND_SECURITY,
    WIFIAPP_WND_CONNECT_SET,
    WIFIAPP_WND_IP_INPUT,
    WIFIAPP_WND_CERT_LIST,
    WIFIAPP_WND_CERT_LIST_OPTION,
    WIFIAPP_WND_CERT_LIST_OPTION_DETAILS
} WiFiAppWndId_e;


/* */
enum
{
    WiFiApp_MENU_PAIRED_LIST_OPTION_CONNECT = 0,
    WiFiApp_MENU_PAIRED_LIST_OPTION_DISCONNECT,
    WiFiApp_MENU_PAIRED_LIST_OPTION_REFRESH,
    WiFiApp_MENU_PAIRED_LIST_OPTION_FILTER_WLAN_NETWORK,
    WiFiApp_MENU_PAIRED_LIST_OPTION_DETAILS,
    WiFiApp_MENU_PAIRED_LIST_OPTION_SIZE
};


/*=============================================================*/
// Global function definition
/*=============================================================*/


/* */
MAE_Ret     WiFiAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret     WiFiAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean     WiFiAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean     WiFiAppStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean     WiFiAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean     WiFiAppResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean     WiFiAppSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);


/*=============================================================*/
// Local function definition
/*=============================================================*/


/* */
void        _WiFiInitData(WiFiAppData_t *pThis);


/* */
MAE_Ret     _WiFiLaunchWiFiConfirmDialogCB(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret     _WiFiSearchWiFiAP(WiFiAppData_t *pThis);
MAE_Ret     _WiFiShowWiFiListWnd(WiFiAppData_t *pThis, WiFiAppMode_e eMode);


/* */
MAE_Ret     _WiFiMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiMainWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiMainWndShow(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiMainWndHide(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiMainWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiMainWndConvert(void *pCusHandle, void *pWndData);
void        _WiFiMainWndOnOffWdgSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void        _WiFiMainWndApListWdgSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void        _WiFiMainWndSwitchWiFiOnOff(WiFiAppData_t *pThis);
void        _WiFiMainWndUpdateWiFiOnOffText(WiFiAppData_t *pThis);
MAE_Ret     _WiFiShowVisibleAPList(WiFiAppData_t *pThis);
void        _WiFiAPListFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);


/* */
MAE_Ret     _WiFiMainOptionMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiMainOptionMenuWndCreate(void *pCusHandle, void *pWndData);
void        _WiFiMainOptionMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


/* */
MAE_Ret     _WiFiPrepareToConnectAP(WiFiAppData_t *pThis);
MAE_Ret     _WiFiConnectToAP(WiFiAppData_t *pThis, u8 *pu8Password);


/* */
MAE_Ret     _WiFiConnectHiddenSSIDToAP(WiFiAppData_t *pThis);
MAE_Ret     _WiFiConnectToAPWaitingDialogCB(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret     _WiFiDisconnectFromAP(WiFiAppData_t *pThis);
MAE_Ret     _WiFiAcqNetworkAddrWaitingDialogCB(void *pData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);


/* */
MAE_Ret     _WiFiPasswordInputWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiPasswordInputWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiPasswordInputWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiPasswordInputWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);
MAE_Ret     _WiFiPasswordInputHiddenSSIDWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);
MAE_Ret     _WiFiCheckPassword(WiFiAppData_t *pThis, boolean bChkHiddenSSIDPwd);


/* */
MAE_Ret     _WiFiNameInputWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiNameInputWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiNameInputWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiNameInputHiddenSSIDWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);


/* */
MAE_Ret     _WiFiIpInputWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiIpInputWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiIpInputWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiIpInputWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);


/* */
MAE_Ret     _WiFiConnectSetWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiConnectSetWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiConnectSetWndDestroy(void *pCusHandle, void *pWndData);
void        _WiFiConnectSetWndSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void        _WiFiConnectSetTypeSelect(WiFiAppData_t *pThis);
MAE_Ret     _WiFiConnectSetShowMenu(WiFiAppData_t *pThis);
void        _WiFiConnectSetFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);


/* */
MAE_Ret     _WiFiFilterAccessPtWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiFilterAccessPtWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiFilterAccessPtWndDestroy(void *pCusHandle, void *pWndData);
void        _WiFiFilterAccessPtWndSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


/* */
MAE_Ret     _WiFiOtherWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiOtherWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiOtherWndDestroy(void *pCusHandle, void *pWndData);
void        _WiFiOtherWndSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret     _WiFiOtherShowMenu(WiFiAppData_t *pThis);
void        _WiFiOtherFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);


/* */
void        _WiFiMACAddressSelect(WiFiAppData_t *pThis);
MAE_Ret     _WiFiMACAddressWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiMACAddressWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiMACAddressWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);


/* */
MAE_Ret     _WiFiSecurityWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiSecurityWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiSecurityWndDestroy(void *pCusHandle, void *pWndData);
void        _WiFiSecurityTypeMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


/* */
MAE_Ret     _WiFiDetailsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiDetailsWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiDetailsWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);


/* */
MAE_Ret     _WiFiSetFilterAPList(WiFiAppData_t *pThis);
void        _WiFiFilterSetStatus(WiFiAppData_t *pThis);


/* */
MAE_Ret     _WiFiCertListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiCertListWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiCertListWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiCertListShowMenu(WiFiAppData_t *pThis);
void        _WiFiCertListWndSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void        _WiFiCertListSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void        _WiFiCertListFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
MAE_Ret     _WiFiCertListOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiCertListOptionWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiCertListOptionWndDestroy(void *pCusHandle, void *pWndData);
void        _WiFiCertListOptionSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret     _WiFiCertListOptionDetailsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret     _WiFiCertListOptionDetailsWndCreate(void *pCusHandle, void *pWndData);
MAE_Ret     _WiFiCertListOptionDetailsWndKeyEvtHdl(WiFiAppData_t *pThis, u32 nKeyCode);
MAE_Ret     _WiFiCertDoInstall(WiFiAppData_t *pThis);
MAE_Ret     _WiFiCertDoRemove(WiFiAppData_t *pThis);
MAE_Ret     _WiFiCertInstallPickFiles(WiFiAppData_t *pThis, WiFiAppCertPickMode_e eMode);
void        _WiFiCertGetFileByBrowseContentFilterCB(FileManagerFileInfo_t *pFileInfo, boolean *pReject, u32 *pWarningMsgTextId);
void        _WiFiCertGetFileByBrowseCB(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
MAE_Ret     _WiFiCertGetFileFullPath (void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb, MAE_WChar *pStrDestURL);
MAE_Ret     _WiFiConnectToAPWithCert(WiFiAppData_t *pThis);
MAE_Ret     _WiFiCertGetCertType(WLANSRV_CertPath_t *pPath, WLANSRV_CertType_e *pCertType);
MAE_Ret     _WiFiCertIsExpireValid(WLANSRV_CertPath_t *pPathCa, WLANSRV_CertPath_t *pPathClient, boolean *pIsValid);
MAE_Ret     _WiFiCertDoReplace(WiFiAppData_t *pThis);
void        _WiFiCertListShow(WiFiAppData_t *pThis);
boolean     _WiFiCertIsTypeValid(WLANSRV_CertType_e eCertType);
boolean     _WiFiCertIsInstalled(void);
boolean     _WiFiCertIsOverMax(void);


#endif /* __MMI_WIFIAPP_PRIV_H__ */
