/**
 * @file    mmi_wdg_statuspage_priv.h
 * @brief   The document describes internal declartion of StatusPage Widget
 * @author  andy.wang@mstarsemi.com
 *
 */

#ifndef __MMI_WDG_STATUSPAGE_PRIV_H__
#define __MMI_WDG_STATUSPAGE_PRIV_H__

#include "mmi_wdg_statuspage.h"
#include "mae_abscontainerbase.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_statusbarsrv.h"

#include "mmi_mmsrv_def.h"
#include "mmi_common_util.h"

#include "mmi_srv_mobilitymgr.h"
#include "mmi_evtcentersrv.h"
#include "mmi_alarmsrv.h"
#include "mmi_profilesrv.h"
#include "mmi_srv_cfg.h"
#include "mmi_cfgsrv.h"
#include "mmi_simsrv.h"
#include "mmi_mmsrv_def.h"
#include "mmi_srv_accessory.h"
#if defined(__BLUETOOTH_MMI__)
#include "mmi_srv_bt.h"
#endif
#if defined(__WLAN_MMI__)
#include "mmi_srv_wlan.h"
#endif
#ifdef __G_SENSOR_MMI__
#include "mmi_mae_sensormgr.h"
#endif
#include "mmi_shortcutssrv.h"
//#include "DesktopWidget_resource.h"

#include "rs_layout_id.h"

#define TestGSensor 0
#define NoSwitchAnimation 0
#define AirplaneSwitch 0

#define RS_STATUSPAGE_CAP_COLOR	(0xFF888888)
#define RS_STATUSPAGE_TEXT_COLOR      (0xFF000000)
#define RS_STATUSPAGE_SWITCHON_COLOR    (COLOR_WHITE)
#define RS_STATUSPAGE_SWITCHOFF_COLOR    (COLOR_WHITE)
#define RS_STATUSPAGE_MESSAGE_MSNUM_COLOR	(0xFF0F72BD)
#define RS_STATUSPAGE_MESSAGE_VMNUM_COLOR	(0xFF0F72BD)
#define RS_STATUSPAGE_SWITCH_TIMER_INTERVAL (1)
#define RS_STATUSPAGE_OPEN_TIMER_INTERVAL (1)
#define RS_STATUSPAGE_CLOSE_TIMER_INTERVAL (1)
#define RS_STATUSPAGE_ANIMIMAGE_NUM (5)
#define RS_STATUSPAGE_SWITCH_INTERVAL (4)

enum
{
	SPW_SWITCH_SLIDE_LEFT,
	SPW_SWITCH_SLIDE_RIGHT
};
typedef u8 SpgWdg_Switch_Slide_Dir_e;

typedef struct {
    u32 nWdgId;
    WPos_t tWPos;
    WidgetSize_t tWdgSize;
    u32 nAlignment;
}StatusPageImgType_t;


typedef struct {
    u32 nWdgId;
    WPos_t tWPos;
    WidgetSize_t tWdgSize;
    u32 nAlignment;
    u32 nTxtColor;
    u32 nFontType;
    u32 nFontCate;
}StatusPageTextType_t;

typedef union
{
    StatusPageTextType_t tTxtLayout;
    StatusPageImgType_t  tImgLayout;
}StatusPageItem_t;

typedef struct {
    u32 tType;
    u32 nResourceID;
    StatusPageItem_t tSPItem;
}StatusPageDataDef_t;

#define RS_STATUSPAGE_DATA_NUM 66
static StatusPageDataDef_t StatusPageLayout[RS_STATUSPAGE_DATA_NUM];
#define SET_STATUSPAGE_IMAGE_LAYOUT(n, p, a, b, c, d, e, f, g, h, i) {(p)[(n)].tType=(a); (p)[(n)].nResourceID=(b); (p)[(n)].tSPItem.tImgLayout.nWdgId=(c); (p)[(n)].tSPItem.tImgLayout.tWPos.isVisible=(d); (p)[(n)].tSPItem.tImgLayout.tWPos.x=(e); (p)[(n)].tSPItem.tImgLayout.tWPos.y=(f); (p)[(n)].tSPItem.tImgLayout.tWdgSize.width=(g); (p)[(n)].tSPItem.tImgLayout.tWdgSize.height=(h); (p)[(n)].tSPItem.tImgLayout.nAlignment=(i);}
#define SET_STATUSPAGE_TEXT_LAYOUT(n, p, a, b, c, d, e, f, g, h, i, j, k, l) {(p)[(n)].tType=(a); (p)[(n)].nResourceID=(b); (p)[(n)].tSPItem.tTxtLayout.nWdgId=(c); (p)[(n)].tSPItem.tTxtLayout.tWPos.isVisible=(d); (p)[(n)].tSPItem.tTxtLayout.tWPos.x=(e); (p)[(n)].tSPItem.tTxtLayout.tWPos.y=(f); (p)[(n)].tSPItem.tTxtLayout.tWdgSize.width=(g); (p)[(n)].tSPItem.tTxtLayout.tWdgSize.height=(h); (p)[(n)].tSPItem.tTxtLayout.nAlignment=(i); (p)[(n)].tSPItem.tTxtLayout.nTxtColor=(j); (p)[(n)].tSPItem.tTxtLayout.nFontType=(k); (p)[(n)].tSPItem.tTxtLayout.nFontCate=(l);}

typedef struct
{
    AbsContainerBase_t ACntrBase;
    IVectorModel* pIStatusModel;
	SpgWdg_Switch_Slide_Dir_e eSlideDir[STATUSPAGE_COMP_WDG_SUM];
    IWidget *pCompWdg[STATUSPAGE_COMP_WDG_SUM];
    IWidget *pAnimImage;
    IWidget *pSwitchWdg;
    IWidget *pChangeWdg;
    IWidget *pLaunchWdg;
    ModelListener_t StatusModelListener;

    u16 uLastY;
    u16 uLastX;
    u16 uSwitchWdgLastX;
    u8 AnimInd;
    boolean bResize;
    boolean bResizeDraw;
    boolean bFirstRelease;
    u16 uStatusPageWdgNum;
    u8 uStatusPageAlarmID;
    s32 sStatusPageDisplayTop;
    s32 sStatusPageDisplayLeft;
    u16 uStatusPageDisplayWidth;
    u16 uStatusPageDisplayHeight;
    u16 uStatusPageDisplayHeight_1_3;
    u16 uStatusPageDisplayHeight_2_3;
    u16 uStatusPageHeightThreshold;
    boolean bAirplaneMode;
    boolean bDisableBTWifi;
    u16 uLastAnimImageY;
    u16 uStatusPageHeight;
    u16 uStatusPageOriginalHeight;
    boolean bInitDone;
    
    s32 sStatusPageSwitchLeft;
    s32 sStatusPageSwitchRight;
    s32 sStatusPageSwitchMiddle;
    u16 uStatusPageSignalBGHeight;
    u32 uStatusPageChangeLeft;
    u32 uStatusPageChangeRight;
    
#ifdef __G_SENSOR_MMI__
    ISensorMgr *pISensorMgr;
#endif
    IALARMSRV *pAlarmSrv;
    ITouchSrv    *pITouchSrv;
    IEVTCENTERSRV *pEvtCenterSrv;
    IPROFILESRV *pProfileSrv;
    ICFGSrv *pCFGSrv;
    ISIMSRV *pSIMSrv;
    IMMSRV *pIMMSrv;
    IACCESSORYSRV *pAccessorySrv;
#if defined(__BLUETOOTH_MMI__)
    IBTSRV *pBTSrv;
#endif
#if defined(__WLAN_MMI__)
    IWLANSRV *pWLanSrv;
#endif
    ISHORTCUTSSRV *pShortcutsSrv;

    boolean bDisableLaunchAp;
    boolean bDiableScroll;    
}_MAE_StatusPageWidget;

enum StatpageCompWdgType_tag
{
    STATUSPAGE_COMPWDGTYPE_SWITCH_BG,
    STATUSPAGE_COMPWDGTYPE_SWITCHICON,
    STATUSPAGE_COMPWDGTYPE_VIBRATE_CHANGE_BG,
    STATUSPAGE_COMPWDGTYPE_ALARM_CHANGE_BG,
    STATUSPAGE_COMPWDGTYPE_CHANGE,
    STATUSPAGE_COMPWDGTYPE_ELSE,
};

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
static boolean StatusPageWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
void StatusPageSetMessage(_MAE_StatusPageWidget* pThis);
void StatusPageSwitchLeftAnimationExtTimerCB(void *pOwner, void *pUserData);
void StatusPageSwitchRightAnimationExtTimerCB(void *pOwner, void *pUserData);
void StatusPageOpenAnimationExtTimerCB(void *pUser);
void StatusPageCloseAnimationExtTimerCB(void *pUser);
MAE_Ret _WdgStatusPageReloadRC(_MAE_StatusPageWidget *pThis);
MAE_Ret _WdgStatusPageConstructor(_MAE_StatusPageWidget *pThis);
void _WdgStatusPageDestructor(_MAE_StatusPageWidget *pThis);
static u32 _StatusPageGetCompWdgType(_MAE_StatusPageWidget *pThis, IWidget *pWidgetCell);
void StatusPageNetworkRegIndCb(void *pUserData, MMI_MMSRV_RegStat_e eState, MAE_DualMode_t eDualMode);
static MAE_Ret StatusPageWidget_Init(IAbsContainer * pIAbsContainer);
static void StatusPageWidget_StatusModelListener(void *pUsrData, ListModelEvent_t *pVectorMdlEvent);
static MAE_Ret StatusPageWidget_HandleBattStatus(_MAE_StatusPageWidget *pThis, u16* pData );
static MAE_Ret StatusPageWidget_HandleRSSIStatus(_MAE_StatusPageWidget *pThis, u16* pData );
static MAE_Ret StatusPageWidget_HandleWAPMsgStatus(_MAE_StatusPageWidget *pThis, u16* pData);
static MAE_Ret StatusPageWidget_HandleVibrateStatus(_MAE_StatusPageWidget *pThis, u16* pData);
static MAE_Ret StatusPageWidget_HandleBTStatus(_MAE_StatusPageWidget *pThis, u16* pData);
static MAE_Ret StatusPageWidget_HandleAlarmStatus(_MAE_StatusPageWidget *pThis, u16* pData);
static MAE_Ret StatusPageWidget_HandleProfileModeStatus(_MAE_StatusPageWidget *pThis, u16* pData);
#ifdef __WLAN_MMI__
static MAE_Ret StatusPageWidget_HandleWiFiStatus(_MAE_StatusPageWidget *pThis, u16* pData);
#endif
//static void _StatusPageWidget_ReloadRC(_MAE_StatusPageWidget *pThis, DisplayMode_e nDispMode);
#endif /*__MMI_WDG_STATUSPAGE_PRIV_H__ */
