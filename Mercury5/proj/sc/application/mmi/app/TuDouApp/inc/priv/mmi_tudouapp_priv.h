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
* @file    mmi_tudouapp_priv.h
* @version
* @brief   TuDou applet private header file
*
*/

#ifndef __MMI_TUDOUAPP_PRIV_H__
#define __MMI_TUDOUAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_dialog.h"
#include "mmi_srv_header.h"

#include "mmi_common_vtm.h"
#include "mmi_tudouapp_id.h"
#include "tudouapp_resource.h"
#include "com_data_factory.h"
#include "http_client.h"

#define TUDOU_SEARCH_INPUT_MAX_LENGTH     (20)
#define TUDOU_SEARCH_AREA      (1)
#define TUDOUMAXINDEX(x, y) ((x) > (y)?(x):(y))
#define TUDOU_VIDEO_ID_LENGTH_MAX (20)
#define TUDOU_REQ_TIME_OUT_TIME (30000)
#define TUDOU_START_REQ_TIME_OUT_TIME (60000)
#define TUDOU_UPDATE_IMAGE_TIME (100)
#define TUDOU_SCROLL_FINISH_TIME (300)
#define TUDOU_IMAGE_DECODE_PARM_WIDTH (70)
#define TUDOU_IMAGE_DECODE_PARM_HEIGHT (60)
#define TUDOU_MIN_FREE_SPACE_SIZE (80) //KB
#define TUDOU_MIN_INIT_SPACE_SIZE (10) //KB
#define TUDOU_CONSTRUCT_MIN_MEMORY_FREE_SIZE (500000) //byte
#define TUDOU_MALLOC_MIN_MEMORY_SIZE (250000) //byte

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct ViewNote_tag
{
	IImage *pViewImg;
	boolean bStation;
	u32 nMenuIndex;
	struct ViewNote_tag *pPrev;
	struct ViewNote_tag *pNext;
}ViewNote_t;

typedef struct DownLoadNode_tag
{
	IImage *pViewImg;//
	struct DownLoadNode_tag *pNext;
}DownLoadNode_t;

typedef struct
{
    SimSelectionWdgList_t tSimSelectionWdgList;
} TuDouDualSimSelectWndData_t;

typedef struct
{
    MAE_WChar wKeyWord[TUDOU_SEARCH_INPUT_MAX_LENGTH+1];
} SearchHistoryWords_t;

typedef struct
{
    u32 nCount;
    SearchHistoryWords_t  pData[TUDOU_SEARCH_HISTORY_WORD_MAX_NUM];
} HistoryData_t;

typedef struct
{
    IWidget *pWelcImageWdg;
    IWidget *pStartTextWdg;
    IWidget *pAnimaImageWdg;
} TuDouStartWndData_t;

typedef struct
{
    s32 uPageSize;
} TuDouHotSpotWndData_t;

typedef struct
{
    IWidget *pChannelMenuWdg;
    IWidget *pVideoListMenu;
    u32 uCurrentPage;
    VectorClass_t  *vColumeType;
    boolean bIsInit;
    TuDouChannelParseType_e uParseType;
    char columnid[20];
    u32 uVideoListItemIndex;
    boolean bIsFreeType;
    boolean bIsFreeList;
} TuDouChannelWndData_t;

typedef struct
{
    IWidget *pInputWdg;
    IWidget *pInputBgImgWdg;
    IWidget *pSeachButtonWdg;
    //IWidget *pSearchResultTextWdg;
    IWidget *pSearchPopularTextWdg;
    IWidget *pSearchPopularMenuWdg;
    IWidget *pSearchHistoryTextWdg;
    IWidget *pSearchHistoryMenuWdg;
    IWidget *pHotSpotMenuWdg;
    #if defined(TUDOU_APP_FEATURE_WAP) && defined(__LCM_HVGA_320_480__)
    IWidget *pWapTitleTextWdg;
    IWidget *pWapVideoIntroWdg;
    #endif
    VectorClass_t  *vHotKeyList;
    u32 uHotKeyNum;
    TuDouSearchParseType_e uParseType;
    char cCurrentKey[(TUDOU_SEARCH_INPUT_MAX_LENGTH+1)*2];
    HistoryData_t *pHistoryData;
    TuDouSearchFocusType_e nFocusType;
} TuDouSearchWndData_t;

typedef struct
{
    IWidget *pDownListMenuWdg;
    u32 nItemId;
    u32 nIndex;
    u32 nCount;
    u32 nCurrentDownIndex;
    u32 nSelectIndex;
    VectorClass_t  *vDownLoadVideoList;
    MAE_WChar *pSize;
    MAE_WChar *pTime;
} TuDouDownloadWndData_t;

typedef struct
{
    IImage *pSettingItemBgImg;
    IWidget *pMflContainer;
    IWidget *pNetWorkWdg;
    IWidget *pStorageWdg;
    u16 nSettingsFocusWdgId;
    IWidget *pMenuWdg;
} TuDouSettingsWndData_t;

typedef struct
{
    IWidget *pVideoImgWdg;
    IWidget *pTitleTextWdg;
    IWidget *pPlayNumWdg;
    IWidget *pPlayToTalNumWdg;
    IWidget *pPlayButtonWdg;
    IWidget *pDownLoadButtonWdg;
    IWidget *pLevelMenuWdg;
    IWidget *pIntroTitTextWdg;
    IWidget *pIntroTextWdg;
    IWidget *pReturnButtonBgImgWdg;
    IWidget *pReturnButtonWdg;
    #ifdef TUDOU_APP_FEATURE_WAP
    IWidget *pWapTitleTextWdg;
    IWidget *pWapVideoIntroWdg[2];
    #endif
    df_video_detail_data *pVideoDetailData;
    char VideoId[20];
    IWidget *pOnlineTextWdg;
} TuDouVideoDetailWndData_t;

/* The data structure is used for create datalink*/
typedef struct {
    u8 nSimId;
} TuDouDataAcnProfile_t;



/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;
    u32 uVideoListItemIndex;
    IImage *pPreViewImg;
    IImage *pPlayTimesImg;
    IImage *pTotalTimesImg;
    IImage *pVideoErrorViewImg;
    IImage *pVideoDetailErrorViewImg;
    IImage *pKbImg;

    VectorClass_t  *vVideoList;
    VectorClass_t  *vChannelVideoList;

    IWidget *pVideoListMenu;
    u32 uCurrentPage;
    StorageCfg_t eStorageCFG;
    char *cStorageType;// PHON OR CARD
	ConSetting_ConnectSet_e eConnectionType;
    s8 StreamingSim1Idx;
    s8 StreamingSim2Idx;

    boolean bIsNetWorkCfgUpdata;
    boolean bIsWaitComfirm;
    boolean bIsSignIn;
    u32 nIndex;
	u32 nDownLoadMenuSize;
	u32 nViewListLoopNum;
	u32 nPreFirstIndex;
	u32 nCurrenMaxIndex;
    boolean bStorageFull;
    boolean bConfirmCleanCache;
	boolean bTsPress;
    boolean bResumnView;
	ViewNote_t *pHead;
	ViewNote_t *pLast;
	DownLoadNode_t *pDownLoadHead;
	WidgetHandler_t MenuWdgHandler;
	MAE_WndId nLastWndId;
    TuDouWndId_e nCreateWndId[3];
	boolean bIsSuspend;
    boolean bIsFreeHttp;// sg_http_client_struct is free or not
    TuDouAppSuspendFreeId_e nFreeId;//memory free or not when suspend
	u32 nVideoListSelectIndex;
    u32 nLastDrawIndex;
    TuDouItemID_e  nMenuItemID;                // record the selected option menu item id
    boolean bIsBTSrvRegister;
    TuDouAppViewType_e eViewType;                  // to indicate which view is active
    u32 nMenuAdaptLastIndex;
    u32 nVectorItemNum;

    char cTempFilePath[FILEMGR_MAX_FILEPATH_SIZE];
    char cVideoDetailFilePath[FILEMGR_MAX_FILEPATH_SIZE];
    char cDownLoadVideoPath[FILEMGR_MAX_FILEPATH_SIZE];
    char cPicFilePath[FILEMGR_MAX_FILEPATH_SIZE];

    char cDownLoadVideoInforPath[FILEMGR_MAX_FILEPATH_SIZE];//downloading url
    char cVideoInforPath[FILEMGR_MAX_FILEPATH_SIZE];//
    char cPlayUrl[FILEMGR_MAX_FILEPATH_SIZE];
    //boolean bIsDownLoadVideoInfoExsit;

    sg_http_cb_status eStatus;
    u8 curImsi[MAX_IMSI_LEN+1];
    u8 curImei[COMMON_IMEI_NUM_LENGTH+1];
    COMMON_SIM_CARD_STATUS_e eSimStatus;

    boolean bIsTimeOutDialogShowed;
    boolean bIsLaunchVideoPlay;
    boolean bIsEndKeyPress;
    boolean bIsComfirmExit;
    df_download_video_infor tDownVideoInfo;
    DownLoadStatus_t eDownLoadStatus;
    TuDouAppDataLinkStatus_e eDatalinkStatus;
    char cDownLoadVideoId[TUDOU_VIDEO_ID_LENGTH_MAX];
    IImage *pCompleteImg;
    IImage *pStopImg;
    IImage *pDowningImg;

    FileMgrHandleID_t   nPhoneHandle;
    FileMgrHandleID_t   nMoviePhoneHandle;
    char *DownLoadId;
    FileMgr_Stream_t *pDownLoadVideoIFStream;

    //http
    boolean bIsHttpInit; // only int http one time
	boolean bIsConnecting;
    boolean bIsSimIdKnown; //only used for sim card selection
	u8 nSimId;
    sg_http_session_struct *pHttpJsonSession; //
    sg_http_session_struct *pHttpVideoDetailSession; //
    sg_http_session_struct *pHttpDownLoadVideoSession; // down load video
    sg_http_session_struct *pHttpPicSession; // down load pic
    sg_http_client_struct *sHttpClient;

    //#ifdef TUDOU_APP_FEATURE_WAP
    ConSetting_ConnectSet_e nWebConnectTypeIdx_bak;
    char* cur_wap_title[2];
    char* cur_wap_url[2];
    MAE_WChar* cur_sel_wap_url;
    //#endif
} TuDouAppData_t;


/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret _TuDouCreateDualSimSelectWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouCreateStartWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouShowStartWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouCreateHotSpotWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouShowHotSpotWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouHideHotSpotWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouHotSpotWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret _TuDouCreateChannelWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouShowChannelWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouHideChannelWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouChannelWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret _TuDouCreateSearchWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouShowSearchWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouHideSearchWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouSearchWndDestroy(void *pCusHandle, void *pWndData);
MAE_Ret _TuDouCreateDownLoadWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouCreateDownLoadOptionWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _TuDouCreateSettingsWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouCreatePlayTypeWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _TuDouCreateVideoDetailWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _TuDouCreateChannelVideoDetailWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _TuDouVideoDetailDestory(void *pCusHandle, void *pWndData);
MAE_Ret _TuDouChannelVideoDetailDestory(void *pCusHandle, void *pWndData);
MAE_Ret _TuDouDownLoadDestory(void *pCusHandle, void *pWndData);

static void _TuDouDownloadWndVectorItemFree(void *pItemData, void *pUseData);
static void _TuDouSearchWndVectorItemFree(void *pItemData, void *pUseData);
static void _TuDouChannelWndVectorItemFree(void *pItemData, void *pUseData);
static void _TuDouAppVideoListVectorItemFree(void *pItemData, void *pUseData);
static void _TuDouAppChannelVideoListVectorItemFree(void *pItemData, void *pUseData);
static void _TuDouHotSpotGridMenuWdgView(HWIN hWin, Pos_t* pPos, WidgetSize_t* pSize, u32 nFoucsItemId);
static void _TuDouSetTitleAndWndBgView(HWIN hWin);
static MAE_Ret _TuDouVideoListMenuView(HWIN hWin,Pos_t *pPos, WidgetSize_t *pSize);
static void _TuDouChannelListMenuView(HWIN hWin,Pos_t *pPos, WidgetSize_t *pSize);
static MAE_Ret _TuDouChannelVideoListMenuView(HWIN hWin,Pos_t *pPos, WidgetSize_t *pSize);

static void _TuDouSearchHotKeyMenuView(HWIN hWin, TuDouSearchWndData_t *pWdgList);
static void _TuDouSearchInputView(HWIN hWin, TuDouSearchWndData_t *pWdgList);
static MAE_Ret _TuDouVideoDetailView(HWIN hWin, TuDouVideoDetailWndData_t *pWdgList);
static MAE_Ret _TuDouVideoDetailViewReturnButton(HWIN hWin, TuDouVideoDetailWndData_t *pWdgList);

static MAE_Ret _TuDouSettingsView(HWIN hWin, TuDouSettingsWndData_t *pWdgList);
static MAE_Ret _TuDouDownLoadView(HWIN hWin, TuDouDownloadWndData_t *pWdgList);
#ifdef __ONBOARD_USER_STORAGE_MMI__
static MAE_Ret _TuDouSettingSetRecordStorageWnd(void *pCusHandle);
#endif
static void _TuDouChannelListMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void _TuDouChannelListMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouSearchPopularMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void _TuDouSearchPopularMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouSearchHistoryMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void _TuDouSearchHistoryMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void _TuDouCreateTimeOutDialogTimerCb(void * pUser);
static void _TuDouCreateStartTimerCb(void * pUser);
MAE_Ret _TuDouTimeOutDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
MAE_Ret _TuDouCreateStartTimeOutDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
#ifdef TUDOU_APP_FEATURE_WAP
MAE_Ret _TuDouWebSettingConfirmDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
static void _TuDouWapTextWdgLinkListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nNodeIndex, IWidget *pWidget);
#endif

void _TuDouVideoDetailImgDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouVideoListMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
 void _TuDouVideoListMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouDownLoadVideoListMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void _TuDouDownLoadVideoListMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouChannelVideoListMenuAdaptGet (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
 void _TuDouChannelVideoListMenuFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void _TuDouITWdgSetItemAlignment(IWidget *pWDGIT, WdgAlignment_e nImgAlignment, WdgAlignment_e nTextAlignment);
static MAE_Ret _TuDouCreateTempFile(TuDouAppData_t* pThis ,sg_http_string entity_body, char *cTempUrl);

//static MAE_Ret _TuDouCreateVideoFile(TuDouAppData_t* pThis ,sg_http_string entity_body);
static MAE_Ret _TuDouCreatePicFile(TuDouAppData_t* pThis ,sg_http_string entity_body);

static MAE_Ret _TuDouCreateInforFile(TuDouAppData_t* pThis ,const void *pBuffer, u32 nSize, MAE_WChar* pStrURL);
MAE_Ret _TuDouReadInforFile(TuDouAppData_t* pThis, void *pReadBuffer, u32 nReadSize ,MAE_WChar* pStrURL);
void _TuDouUpdateIndicatorProgress(void * pUser);

static void _TuDouOpenFoldHandle(TuDouAppData_t *pThis, MAE_WChar *pStrURL);
static void _TuDouOpenVideoFoldHandle(TuDouAppData_t *pThis, MAE_WChar *pStrURL);

MAE_Ret TuDouWriteHistoryRai(TuDouSearchWndData_t *pWdgList, MAE_WChar *pwText);


//down load moive
void _TuDouStopDownLoadMovieCb(void * pUser);
void _TuDouDownLoadOptionMenuAction(TuDouAppData_t *pThis, u32 nSelectedID);
static MAE_Ret _TuDouDownloadMenuUpdateItemByIndex(TuDouAppData_t *pThis, IWidget *pMenuWdg, u32 u32Index, df_download_video_infor *pVideoData);
void _TuDouUpdateVideoListImage(void *user);
void _TuDouUpdateVideoListMenuImage(void *user);
void _TuDouHttpGetPictureCompleteCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouMenuReleaseCompleteCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
static boolean _TuDouMenuWdgHandleEvent(void *pUserData, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _TuDouMenuWdgHandleFree(TuDouAppData_t *pThis);
void _TuDouInitMenuDataAfterTsRelease(TuDouAppData_t *pThis);
void _TuDouInitVideoListData(TuDouAppData_t *pThis);
void _TuDouInitVideoList(TuDouAppData_t *pThis);
void _TuDouInitVideoUpdateList(TuDouAppData_t *pThis);
void _TuDouConstrcutVideoList(TuDouAppData_t *pThis);
void _TuDouDestructorVideoList(TuDouAppData_t *pThis);
void _TuDouConstrcutDownLoadList(TuDouAppData_t *pThis, u32 nNodeNum);
void _TuDouDestructorDownLoadList(TuDouAppData_t *pThis);
void _TuDouUpDateVideoDetailyImage(TuDouAppData_t *pThis);
void _TuDouUSBStatusChangeCb(void *pData, MMI_USB_STATUS_E eUsbStatus);
void _TuDouUpdateDownLoadListMenuImage(TuDouAppData_t *pThis);
void _TuDouMenuScrollFinishCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _TuDouVideoListUpdateImageLoopCb(void *user);
void _TuDouVideoListScrollFinishTimerCb(void *user);
boolean _TuDouSpaceNotEnough(TuDouAppData_t *pThis, char *cStorageType, u32 AlarmFreeSize);
boolean _TuDouMemoryNotEnough(TuDouAppData_t *pThis, u32 AlarmFreeSize);//kb
void _TuDouTestDisconnect(TuDouAppData_t *pThis,sg_http_cb_status eStatus, MAE_WndId nWndId);
void _TuDouFreeHttp(TuDouAppData_t *pThis);
boolean _TuDouTestImageSupportView(MAE_WChar *pStrUrl);
static void _TuDouImgDecodeNotify(IImage *pImage, IBase *pData, ImgStatus_t nStatus);

void _TuDouMakeSureItemImageIsValid(TuDouAppData_t *pThis, IImage *pViewImg);

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret TuDouConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret TuDouDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret TuDouEnter(IApplet *pApplet);
MAE_Ret TuDouInit(IApplet *pApplet);
boolean TuDouStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean TuDouKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean TuDouSuspendCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean TuDouResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean TuDouStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void TuDouCfgSrvUpdateCb(void *pUserData, SrvCfgItemStatusChangeType_e eIndType, SrvCfgItemUpdateResult_t tResult);
void TuDouAccessoryPlugStatusCB(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void TuDouNetworkStatusCB(IBase *pApplet, void *pvUserData, SrvSocketNetworkStatus_e eStatus);
//void TuDouCreateStartWndTimerCb(void* pUserData);
void TuDouHotSpotGridMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouVideoListMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouVideoChannelListMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouChannelTypeMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

void TuDouDownLoadVideoListMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouDownLoadOptionMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouVideoListMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret TuDouDownLoadOptionMenuSoftkeyCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void TuDouVideoDetailReturnButtonSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void TuDouVideoDetailDownLoadButtonSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void TuDouSearchHotKeyMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void TuDouSearchHistoryMenuWdgSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
void _TuDouSearchHistoryMenuBoundTopCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void _TuDouSearchHistoryMenuBoundBottomCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void _TuDouSearchPopularMenuBoundTopCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void _TuDouSearchPopularMenuBoundBottomCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void TuDouDualSimSelectMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _TuDouSwitchMenuWdg(IWidget *pFromMenuWdg, IWidget *pToMenuWdg, u32 nIndex);
void TuDouSearchButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void TuDouExitButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
MAE_Ret _TuDouExitAppConfirmDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#ifdef __BLUETOOTH_OBEX_MMI__
MAE_Ret _TuDouStopBtOppConfirmDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif
#ifdef TUDOU_APP_FEATURE_KING_MOVIE
#ifndef __SUPPORT_HTTP_MEMORY_STREAMING__
MAE_Ret _TuDouPlayKmvDialogCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
#endif
#endif
MAE_Ret _TuDouCleanCacheConfirmDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);

MAE_Ret _TuDouStorageFullDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret _TuDouVideoDeleteConfirmDialogCb(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);

static void _TuDouMflContainerFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _TuDouMflContainerFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _TuDouHttpGetSignInDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);

static void _TuDouHttpCloseDatalinkCB(IBase *piCaller, void* pUserData, u32 result);
//static void _TuDouHttpSampleTimeOutCB(void *pData);
void _TuDouHttpCreateDataLink(IApplet *pApplet, SrvSocketCreateDatalinkCB pfnSocketCreateDatalinkCb);
static MAE_Ret _TuDouHttpNetworkSelection(TuDouAppData_t *pThis, SrvSocketNetworkProfile_t **pNetworkProfile, TuDouConnectType_e nType);

static void _TuDouHttpCreateDataLinkCb(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
//void _TuDouHttpGetHotVideoListCreateDataLinkCb(IBase *piCaller, void *pvUserData, MAE_Ret nResult);

static MAE_Ret _TuDouHttpGetCurrentDataInfo(IApplet *pApplet, Data_Account_t *pDataAcnProfile);

void _TuDouHttpGetPictureCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouHttpGetVideoListDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouHttpGetVideoDetailDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);
MAE_Ret _TuDouCreateDataLinkErrorCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void _TuDouHttpGetDownLoadVideoDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouHttpGetChannelTypeDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouHttpGetChannelListDataCb(void *pUser, void *msg, sg_http_cb_status eStatus);
void _TuDouHttpGetPlayTransformUrlCb(void *pUser, void *msg, sg_http_cb_status eStatus);
MAE_Ret TuDouHttpParamIsBad(void *pUser, void *msg, sg_http_cb_status eStatus);

void TuDouVideoPlayButtonSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void TuDouSelectPlayTypeSoftkeyActCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

static void TuDouDeleteOptionItemByID(IWidget* pIWidget, u32 s32MenuId);
void TuDouVideoPlay(TuDouAppData_t *pThis, MAE_WChar *pFileUrl);
MAE_Ret _TuDouPlayTransformUrl(TuDouAppData_t *pThis, char *url);
static boolean TuDouIsBlockSubject(u32 u32CheckId);

#ifdef __BLUETOOTH_OBEX_MMI__
void TuDouBtSendFileCb(void *pUserData, BTSRV_TRANS_RESULT_e eResult);
void TuDouBtRecvFileCb(void *pUserData, BTSRV_TRANS_RESULT_e eResult);
#endif

//Window manager related function

MAE_Ret TuDouDualSimSelectWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouStartWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouHotSpotWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouChannelWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouSearchWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouDownLoadWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouSettingsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouVideoDetailWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouChannelVideoDetailWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouDownLoadOptionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret TuDouPlayTypeWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);


#endif /* __MMI_TUDOUAPP_PRIV_H__ */
