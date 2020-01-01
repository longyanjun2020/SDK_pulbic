
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
* @file    mmi_calllogapp.h
* @version
* @brief   call log header file
*
*/

#ifndef __MMI_CALLLOGAPP_PRIV_H__
#define __MMI_CALLLOGAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_calllogapp.h"
#include "mmi_common_dialog.h"
#include "mmi_common_vtm.h"

#include "mmi_launcher_cc.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_security.h"
#ifdef __APP_MMI_EDIT_BEFORE_CALL__
#include "mmi_launcher_dialer.h"
#endif
#ifdef __APP_VIDEO_TELEPHONY__
#include "mmi_launcher_videotelephony.h"
#endif


#include "mmi_calllogapp_id.h"
#include "calllogapp_resource.h"

#ifdef __CALLLOGAPP_TEST__
#include "mmi_btsrv_def.h"
#endif
#ifdef __APP_MMI_PRIVATEPROTECT__ 
#include "mmi_srv_privateprotect.h"
#endif
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define WDG_ABSCONTAINER_WIDTH 240
#define WDG_ABSCONTAINER_HEIGHT 320
#define MMI_CALLLOG_AP_MAX_DATE_STR 20
#define MMI_CALLLOG_AP_MAX_TIME_STR 30
#define MMI_CALLLOG_AP_MAX_MISSED_COUNT_STR 10
#define MMI_CALLLOG_AP_MAX_EMPTY_STR 15
#define MMI_CALLLOG_AP_TIMER COMMON_DIALOG_AUTOCLOSE_TIME
#ifndef __LCM_LANDSCAPE_QVGA_MMI__
#define MMI_CALLLOG_AP_DETAIL_VIEW_ITEMS_NUM 8
#else
#define MMI_CALLLOG_AP_DETAIL_VIEW_ITEMS_NUM 6
#endif
#define MMI_CALLLOG_AP_SIM_NUM 2
#define MMI_CALLCOST_AP_MAX_STR 60

#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
#define	MMI_CALLLOG_AP_TAB_NUM 5
#else
#define	MMI_CALLLOG_AP_TAB_NUM 4
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
	MID_CALLLOG_LIST_OPTION = 1,
	MID_CALLLOG_LIST_OPTION_L2_DELETE_ALL,
	MID_CALLLOG_LIST_OPTION_L2_SEND
};

typedef enum
{
    CALLLOG_RECENT_CALLS_PROP_CNTR = APP_WDG_START,
    CALLLOG_RECENT_CALLS_NUM_MENU,
    CALLLOG_RECENT_CALLS_TIME_MENU,
} CalllogRecentCallsView_e;

typedef struct
{
    IWidget *pPropContainer;
    IWidget *pNumMenuWdg;
    IWidget *pTimeMenuWdg;
    IWidget *pCallerLocationWdg;
} CalllogRecentCallsViewWdgList_t;

typedef struct
{
    u8 nNumber[MMI_PHB_NUMBER_LEN];
    u8 nName[MMI_PHB_NAME_LEN];
    u8 nNumberLen;
    u8 nNameLen;
} CalllogAppListBuf_t;

typedef struct
{
    u8 nStatus;
    MAE_WChar strCCM[MAX_SS_CCM_LENGTH+1];              //Current call meter value
    MAE_WChar strACM[MAX_SS_ACM_LENGTH+1];              //Accumulated call meter value
    MAE_WChar strACMmax[MAX_SS_AMM_LENGTH+1];           //Accumulated call meter maximum value
    MAE_WChar strPpu[MAX_SS_PPU_LENGTH+1];              //Price per unit
    MAE_WChar strCurrency[MAX_SS_CURRENCY_LENGTH+1];    //Currency code
} CalllogAppCallCostSetting_t;

typedef enum
{
    CALLCOST_REQUEST_TYPE_NONE = 0,   //none
    CALLCOST_REQUEST_TYPE_AOC_SET,    //AoC set request
    CALLCOST_REQUEST_TYPE_AOC_QUE,    //AoC query request
    CALLCOST_REQUEST_TYPE_ACM,        //Accumulated Call Meter request
    CALLCOST_REQUEST_TYPE_AMM,        //ACMMax request
    CALLCOST_REQUEST_TYPE_PUC,        //Price per unit and currency request
} CallCostRequestType_e;

typedef union
{
    SSSRV_AOCReq_t tAOCSetReq;
    SSSRV_AOCQueReq_t tAoCQueReq;
    SSSRV_ACMReq_t tACMReq;
    SSSRV_ACMMaxReq_t tAMMReq;
    SSSRV_PUCReq_t tPUCReq;
} CallCostUnionRequestInfo_t;

typedef struct
{
    CallCostRequestType_e eRequestType;    /*Record request type */
    CallCostUnionRequestInfo_t tRequestInfo;     /*Record request information */
} CallCostRequest_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    boolean bIsDeleteAll;
    boolean bSKShown;                   //check if Sk is shown.
    boolean bIsIdle;
    boolean bIsShowDetail;
    boolean bIsGetCurrentSetting;
    boolean bIsLaunchEmbeddedAP;
	boolean bIsUpdateSetting;
	u8		u8CurInputPinWnd;
    u16 nCallLogSize;
    u16 nFocusItem;
    u8 nSelectedSim;  // for call cost
    u8 nDeleteAllType;
    u8 nCurIMSI_M[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
    u8 nCurIMSI_S[MMI_CALLLOG_MAX_IMSI_LEN];  // 9 bytes
    CalllogAppParamData_t *ptAppParam;
    u32 nCallCostHighlightedIndex;
    MMI_CALLLOG_AP_SHOW_LIST_TYPE_E eTabViewType;
    MMI_CALLLOG_AP_FID_TYPE_E eCalllog_AP_Fid_Type;
    MmiPhbName_t tPhbName;
    COMMON_SIM_CARD_STATUS_e eSimStatus;
    CallCostRequest_t tReqData;
    Mmi_CallLogSimpRecord_t *pHighlightItemSimpRecord;
    CalllogAppCallCostSetting_t *ptCallCostSetting;
    HistoryInfo_t *ptHistory;
	void *pCalllogCnf;
    u32 nKeycode;
	MMI_CALLLOG_SIM_TYPE_E u8DisplaySimType;  // for dual sim selection 
    boolean bIsOpenPhbCache;
} CallLogAppData_t;

typedef struct
{
    CalllogRecentCallsViewWdgList_t tWdgList;
	u32 nPropValue;
	Mmi_CallLogSrvReadFullLogCnf_t *ptReadFullLogCnf;
} CallLogShowDetailWndData_t;

typedef struct
{
    TabMenuWdgList_t tWdgList;
} CallLogListWndData_t;

typedef MAE_Ret(*DIALOG_CB)(void *, u32, u32, u32);

/*=============================================================*/
// Variable definition
/*=============================================================*/

const MMI_CALLLOG_TYPE_E LISTTYPE_TO_LOGTYPE[MMI_CALLLOG_AP_TAB_NUM] = {MMI_CALLLOG_TYPE_ALL,
                                                                             MMI_CALLLOG_TYPE_MISSED,
                                                                             MMI_CALLLOG_TYPE_RECEIVED,
                                                                             MMI_CALLLOG_TYPE_DIALED
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
                                                                             ,MMI_CALLLOG_TYPE_BLOCK
#endif			
																		};

static u32 nImageId[] = {CALLHISTORY_IMG_TAB_ALL,
                         CALLHISTORY_IMG_TAB_MISSED,
                         CALLHISTORY_IMG_TAB_RECEIVED,
                         CALLHISTORY_IMG_TAB_DIALED
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
						 ,CALLHISTORY_IMG_TAB_BLOCKED
#endif
						};

static u32 nImageFocusId[] = {CALLHISTORY_IMG_TAB_ALL_FOCUS,
                              CALLHISTORY_IMG_TAB_MISSED_FOCUS,
                              CALLHISTORY_IMG_TAB_RECEIVED_FOCUS,
                              CALLHISTORY_IMG_TAB_DIALED_FOCUS
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
                              ,CALLHISTORY_IMG_TAB_BLOCKED_FOCUS
#endif
							 };

/*=============================================================*/
// private function definition
/*=============================================================*/

MAE_Ret CalllogConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalllogDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalllogStartCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalllogResumeCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalllogSuspendCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalllogKeyPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void CalllogSetAOCCnfCb(void *pApplet, SSSRV_AOCCnf_t *pAdviseOfCharge);
void CalllogACMCnfCb(void *pApplet, SSSRV_ACMCnf_t *pAccumulatedCallMeter);
void CalllogAMMCnfCb(void *pApplet, SSSRV_ACMMaxCnf_t *pfnSSAccumulatedCallMeterMax);
void CalllogPUCCnfCb(void *pApplet, SSSRV_PUCCnf_t *pPriceUnit);
void CalllogReady_CB(void* pUserdata);
void CalllogGetReady(CallLogAppData_t *pThis);
static boolean CalllogPhoneLockSucessCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalllogTimeOutSettingProcessScreenCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalllogKeyPressGetAccountLimitCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalllogTimeOutResetProcessScreenCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void CalllogListWndMenuCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CalllogListWndOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void CalllogTimerMenuSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CalllogCostMenuSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CalllogMenuReqOp2Cb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret CalllogOption2MenuSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void CalllogSelectSimSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CalllogCostSettingSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CalllogShowDetailSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret CalllogSelectSimWndMenuCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret CalllogTimeOutDialogCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

#ifndef __MMI_PHB_DISABLE_BLACKLIST__
MAE_Ret CalllogAddBKTimeOutDialogCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalllogAddToBlackListConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__

MAE_Ret CalllogOptionMenuSoftkeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
///Calllog Srvice Callback function
void CalllogVerifyPin2TextInputCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
static void CallLogReadFullLogCb(void *pThis, Mmi_CallLogSrvReadFullLogCnf_t *ptCnf);
static void CallLogDeleteOneLogCb(void *pThis, Mmi_CallLogSrvDeleteOneLogCnf_t *ptCnf);
static void CallLogDeleteAllLogsCb(void *pThis, Mmi_CallLogSrvDeleteAllLogsCnf_t *ptCnf);
static void CallLogResetCallTimeACCb(void *pThis, Mmi_CallLogSrvResetCallTimeACCnf_t *ptCnf);
#ifdef __APP_MMI_PRIVATEPROTECT__ 
void _CalllogPrivateProtectStatusCB(void *pIApplet, PrivateProtectAuthResult_e eAuthResult);
#endif

MAE_Ret CalllogWndListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndTimerMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostSettingMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostSettingSetUnitHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostSettingSetCurrencyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostSettingSetMaxUnitHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndTimerSelecSimtHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndListShowOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndDetailTimeShowOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndDetailTimeShowDetailHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalllogWndCostSelecSimtHdl(void *pCusHandle , const WindowMsg_t *pWndMsg , void *pWndData , u32 nWndInitParam);
#ifdef __CALLLOG_SELECT_DISPLAY_SIM__
MAE_Ret CalllogWndSelectDisplaySIMHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

void CalllogTabMenuGetMenuItemData(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
void CalllogTabMenuFreeMenuItemData(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void CalllogMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
void CalllogMenuItemDTFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
void CallLogLaunchSecInfoCb(void *pvUserData, MAE_Ret nRspCode, SecurityLaunchRspData_t *psRspData, SecurityLaunchRspDataFreeCb pfnRspDataFreeCb);
MAE_Ret CalllogReplaceMenuItemLine2DataByText(IWidget *pMenuWdg, u32 nMenuItemID, MAE_WChar *pWStr);

static MAE_Ret _CalllogWndConvertList(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertCostMenu(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertSetMenuLayout(void *pCusHandle , void *pScenData , u32 nScenInitParam, CallogWndId_e eCallogWndId);
static MAE_Ret _CalllogWndConvertCostSettingSetUnit(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertCostSettingMenu(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertRecentCallView(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertListShowOption(void *pCusHandle , void *pScenData , u32 nScenInitParam);
static MAE_Ret _CalllogWndConvertDetailTimeShowOption(void *pCusHandle , void *pScenData , u32 nScenInitParam);

#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
void CallLogBlockedCallCountChangedCb(void * pUserData, u32 nBlockedCount);
MAE_Ret CalllogSetTabWidgetBgImage(CallLogAppData_t *pThis, IWidget *pTabWidget);
static MAE_Ret _CalllogGetNameFromBlacklist(CallLogAppData_t *pThis, u8 *pnNumber, u8 nNumLen);
#endif
#endif /* __MMI_CALLLOGAPP_PRIV_H__ */

