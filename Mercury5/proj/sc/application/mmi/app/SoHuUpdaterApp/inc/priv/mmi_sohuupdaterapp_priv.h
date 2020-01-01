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
* @file    mmi_sohuupdaterapp_priv.h
* @version
* @brief   SoHu Updater applet private header file
*
*/

#ifndef __MMI_SOHUUPDATERAPP_PRIV_H__
#define __MMI_SOHUUPDATERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_event.h"

#include "mmi_wdg_headers.h"
#include "mmi_srv_header.h"

#include "mmi_common_cfg.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_launcher_common.h"
#include "mmi_launcher_sohuupdater.h"
#include "mmi_launcher_picviewer.h"

#include "mmi_sohuupdaterapp_id.h"
#include "mmi_sohuupdaterapp_cfg.h"
#include "SoHuUpdater_resource.h"

#include "publicfunc.h"
#include "encrpty.h"
#include "http_client.h"


#ifdef __APP_MMI_SOHU_UPDATER__

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

typedef u32 MenuItemID_e;

#define SOHU_DIR                             L"fs:/CARD/Sohu/"
#define SOHU_SKIN_DOWNLOAD_PATH         L"fs:/CARD/Sohu/Skin/"
#define SOHU_SKIN_BIN_DL                        L"fs:/CARD/Sohu/skin.bin"
#define SOHU_SKIN_BIN_DECODE                L"fs:/CARD/Sohu/skin_out.bin"
#define SOHU_SKIN_TMP_FILE                        L"fs:/CARD/Sohu/tmp.jpg"
#define SOHU_WORLD_LIB_DIR                      L"fs:/CARD/Sohu/wordlib.txt"
#define SOHU_CONFIG_FILE                     L"fs:/PHON/.system/sohuconfig.sgg"

#define SOHU_SKIN_BIN_BUF_SIZE          (1024*2) //skinbin ´óÐ¡wxd
#define SOHU_CONNECT_DURATION          30000
#define SOHU_SKIN_NAME_LEN          50
#define SOHU_SKIN_LEVEL          5
#define SOGOU_IME_WORDLIB_FIRST_UPDATE_START   (6 * 30)
#define SOGOU_SKIN_WORLD_LIB_BUF_SIZE             (50 * 1024)

#define SOGOU_UPDATE_PLATFORM_STR          "MSTAR"
/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    SOHU_NORMAL_MODE = 0,
    SOHU_AUTO_UPDATE_MODE,
} SoHuUpdatetrAppMode_e;

typedef struct
{
    SoHuUpdatetrAppMode_e eAppMode;
} tSohuStartParm;

typedef struct
{
    u32 nHandle;        // start list handle
    u32 nNumber;        // total file number in folder
} SoHuAppFileListInfo_t;

typedef struct {
    SG_UINT16 startpos;
    SG_UINT16 index;
    SG_UINT16 picID[SOHU_SKIN_NAME_LEN];
    SG_UINT16 picName[SOHU_SKIN_NAME_LEN];
    SG_UINT16 dirLevel[SOHU_SKIN_LEVEL];
    SG_UINT8 level;
} SoHuAppSkinInf;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    SoHuUpdatetrAppMode_e eAppMode;
    SoHuAppFileListInfo_t tFileListInfo;				// record file list info
    FocusInfo_t tFocusInfo;								// focused item's focus info
    MAE_WChar wszItemName[VFS_FAT_SPEC_FULLPATH_LEN];	// focused item's name
    MAE_WChar *pwstrFilePath;							// current file path
    u32 nConfirmDlgType;                // for handle confirm dialog

    SoHuAppSkinInf *pSkin;
    u8 *pDateHeader;             // buffer for skin.bin

    boolean bNeedToUpdateMenu;      // for skin selection window,  system update setting
    SohuFrequency_e eFrequency;     // for temp keep the value

    char sg_ime_timeStamp[SG_TIMESTAMP_LEN];        // timestamp
    u8 currentDLType;
	boolean bIsConnecting;
	boolean bMemoryCardPlug;
    boolean bSpace; //liguoyi
    u8 nSimId;  //liguoyi
    sg_http_client_struct http_client;
    boolean bAutoUpdateAlarm;
	boolean bCopySkinImg;
	u32 nPrevFocusIdx;
} SoHuUpdaterApp_t;

/* The data structure is used for storing the variables of the set auto update view. */
typedef struct
{
    IWidget *pIFrequencyWidget;
    IWidget *pITimeWidget;
    IWidget *pIMflContainer;
    IWidget *pIScrollBarWidget;
    SetPhoneTimeFormat_e eTimeFormat;
    ScrollData_t tScrollData;
    u32 nFocusIndex;
} SoHuSetAutoUpdateView_t;

/* The data structure is used for create datalink*/
typedef struct {
    Data_Account_t tAccount;
    u8 nSimId;
} SoHuDataAcnProfile_t;

typedef enum
{
    SOHU_CONNECT_RMD_TEXT = APP_WDG_START,
} ConnectRmdWndView_e;

typedef struct
{
	IWidget *pRmdTextWdg;
} ConnectRmdWndWdgList_t;

typedef struct
{
    ConnectRmdWndWdgList_t tWdgList;
} ConnectRmdWndData_t;

typedef enum
{
    SOHU_DLG_NORMAL = 0,				// normal style
    SOHU_DLG_DEL_SKIN_CONFIRM,              // confirm for delete skin file
    SOHU_DLG_DEL_SKIN_SUCCESS,              // delete skin file success
    SOHU_DLG_DEL_FAIL,						// delete fail
    SOHU_DLG_SET_SKIN_SUCCESS,				// set skin file success
    SOHU_DLG_INIT_FAIL,
    SOHU_DLG_CONNECT_FAIL,
} SoHuUpdaterAppDlgType_e;

typedef enum
{
    SOHU_SKIN_BIN = 0,
    SOHU_WORLD_BIN,
    SOHU_SKIN_PIC,
} SoHuDLType_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret SoHuUpdaterConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret SoHuUpdaterDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SoHuUpdaterStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SoHuUpdaterResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SoHuUpdaterSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SoHuUpdaterKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean SoHuUpdaterStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret SoHuUpdaterWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndSkinMgrHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSkinMgr(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndSkinSelectHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSkinSelect(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndDestroySkinSelect(void *pCusHandle, void *pWndData);

MAE_Ret SoHuUpdaterWndConnectRmdHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateConnectRmd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
boolean _SoHuHandleKeyPressConnectRmd(SoHuUpdaterApp_t *pThis, u32 nParam1, u32 nParam2);

MAE_Ret SoHuUpdaterWndSkinOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSkinOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndSkinDownloadHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSkinDownload(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndDestroySkinDownload(void *pCusHandle, void *pWndData);

MAE_Ret SoHuUpdaterWndSettingsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSettings(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndSysUpdateHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateSysUpdate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndShowSysUpdate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndRadioMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateRadioMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndRadioMenuAutoFreqHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateRadioMenuAutoFreq(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret SoHuUpdaterWndAutoUpdateHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateAutoUpdate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndShowAutoUpdate(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndDestroyAutoUpdate(void *pCusHandle, void *pWndData);

MAE_Ret SoHuUpdaterWndViewImageHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterWndCreateViewImage(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret SoHuUpdaterCopyImageToSystem(IApplet *pApplet);
void SoHuUpdaterFileCopyCB(void *pUser, void *pInfo);

void SoHuUpdaterMainMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSkinMgrSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterMenuOnFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void SoHuUpdaterSkinSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSkinDownloadSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterOptMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSettingsSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSysUpdateSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterRadioMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterRadioMenuAutoFreqSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void SoHuUpdaterMainMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSecondMenuBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SoHuUpdaterSkinDownloadBackCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void SoHuMenuItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void SoHuMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

void SoHuSkinDownloadMenuItemGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void SoHuSkinDownloadMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);
void SoHuSysUpdateMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

void SoHuRadioMenuItemFreeByType(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

//============================== Private Function ==============================//
MAE_Ret _SoHuUpdaterRefreshSkinSelectWnd(IApplet *pApplet);
MAE_Ret _SoHuUpdaterMenuItemCfgUpdate(IApplet *pApplet, MenuItemID_e eMenuID);

static void _SoHuUpdaterCreateDataLink(IApplet *pApplet, SoHuDLType_e DLType);
void _SoHuUpdaterCloseDatalinkCB(IBase *piCaller, void* pUserData, u32 result);

static void  _SoHuUpdaterDLSkinBin(IBase *piCaller, void *pUserData, MAE_Ret nResult);
void  _SoHuUpdaterDlSkinBinCb (void *pUser, void *msg, sg_http_cb_status error);
void _SoHuUpdaterDLSkinBinCloseDatalinkCB(IBase *piCaller, void* pUserData, u32 result);
void _SoHuUpdaterDLTimeOutCB(void *pData);

static void  _SoHuUpdaterDLSkin(IBase *piCaller, void *pUserData, MAE_Ret nResult);
void  _SoHuUpdaterDlSkinCb (void *pUser, void *msg, sg_http_cb_status error);
void _SoHuUpdaterDLSkinCloseDatalinkCB(IBase *piCaller, void* pUserData, u32 result);

static void  _SoHuUpdaterDLWorldLib(IBase *piCaller, void *pUserData, MAE_Ret nResult);
void  _SoHuUpdaterDLWorldLibCb (void *pUser, void *msg, sg_http_cb_status error);
static void   _SoHuUpdaterUpdateWordLib(IApplet *pApplet, SG_UINT8* pWorldData);
void _SoHuUpdaterDLWorldLibCloseDatalinkCB(IBase *piCaller, void* pUserData,  u32 result);

void _SoHuUpdaterReadConfig(IApplet *pApplet);
void _SoHuUpdaterStoreConfig(IApplet *pApplet);
void _SoHuUpdaterGetMsTimeStamp(SG_UINT32 num_of_day_before, SG_INT8 *time_stamp);
void _SoHuUpdaterMflContainerMFLFocusSelect(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _SoHuUpdaterMflContainerMFLFocusChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _SoHuUpdaterTimeAmPmChange(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TimePeriod_e eTimePeriod, IWidget *pWidget);

MAE_Ret _SoHuUpdaterGetCurrentDataInfo(IApplet *pApplet, SoHuDataAcnProfile_t *pDataAcnProfile);

void _SoHuUpdaterAutoUpdateProc(IApplet *pApplet);
MAE_Ret _SoHuUpdaterAutoUpdateConfirmCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _SoHuUpdaterAutoUpdateCloseCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _SoHuUpdaterCkeckUSBStatus(void *pApplet);

//============================== Common Function ==============================//

// create confirm dialog
void _SoHuCommonCreateDialog(IApplet *pApplet, u32 nDlgType);

// Confirm dialog call back
MAE_Ret _SoHuCommonConfirmDlgCb(IApplet *pApplet, u32 nEvt, u32 keyCode, u32 nParam2);

// dialog timeout
void _SoHuCommonDialogTimeOut(void* pUserData);

// malloc memory and copy content
void _SoHuCommonMemCopy(MAE_WChar **pwPath, const MAE_WChar *pwSource);

// start list file
MAE_Ret _SoHuCommonStartFileList(IApplet *pApplet, SoHuAppFileListInfo_t *pList, const MAE_WChar *pPath);

// end list file
MAE_Ret _SoHuCommonEndFileList(SoHuAppFileListInfo_t *pList);

// get fileinfo by index
void _SoHuCommonGetFileInfoById(u32 nHandle, u32 FileId, VFS_PartialListFileInfo_t *pInfo);

// delete a file
MAE_Ret _SoHuCommonDelItem(MAE_WChar *pPath, MAE_WChar *pName);

// get full path name
// it need to free the allocated memory
MAE_Ret _SoHuCommonGetFullPathName(MAE_WChar **pFullName, MAE_WChar *pPath, MAE_WChar *pName);

#endif
#endif /* __MMI_SOHUUPDATERAPP_PRIV_H__ */

