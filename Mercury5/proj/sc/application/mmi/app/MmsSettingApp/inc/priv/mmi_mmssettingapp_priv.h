/**
* @file mmi_mmssettingapp_priv.h
*
* @version $Id$
*/
#ifndef __MMI_MMSSETTINGAPP_PRIV_H__
#define __MMI_MMSSETTINGAPP_PRIV_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mmssettingapp.h"
#include "mmi_baseapplet.h"

#ifdef __MMS_MMI_CDMMS__
#include "mmi_message_cfg.h"
#include "mmi_base_util.h"
#include "mmi_srv_cfg.h"
#include "mmi_wdg_headers.h"
#include "mmi_launcher_mmsa.h"
#include "mmi_mmssettingapp_id.h"
#include "MmsSettingApp_resource.h"
#define MMSA_DIALOG_TIMER 1000

typedef enum
{
	MNU_MSG_SET_MMS_PROFILE = 0,
	MNU_MSG_SET_FILTER,
	MNU_MSG_SET_EXPIRED_TIME,
	MNU_MSG_SET_REPLY_TYPE,
	MNU_MSG_SET_SIZE_LIMIT,
	MNU_MSG_SET_DEFERRED_DOWNLOAD,
	MNU_MSG_SET_DELIVERY_REPORT,
	MNU_MSG_SET_READ_REPORT,
	MNU_MSG_SET_MMS_PAGE_SETTINGS,
	MNU_MSG_SET_MMS_DURATION,
	MNU_MSG_SET_MMS_1SECOND,
	MNU_MSG_SET_MMS_3SECONDS,
	MNU_MSG_SET_MMS_5SECONDS,
	MNU_MSG_SET_MMS_10SECONDS,
	MNU_MSG_SET_MMS_USER_DEFINE,
	MNU_MSG_SET_MMS_TEXT_LOC,
	MNU_MSG_SET_MMS_PLACE_FIRST,
	MNU_MSG_SET_MMS_PLACE_LAST,
	MNU_MSG_SET_MMS_IMAGE_SIZE,
	MNU_MSG_SET_MMS_LARGE,
	MNU_MSG_SET_MMS_SMALL,
	MNU_MSG_SET_MMS_ORIGINAL,
	MNU_MSG_SET_MMS_SEND_OPTIONS,
	MNU_MSG_SET_MMS_MULTIMEDIA_RETRIEVAL,
	MNU_MSG_SET_MMS_ALWAYS_AUTOMATIC,
	MNU_MSG_SET_MMS_AUTO_IN_HOME,
	MNU_MSG_SET_MMS_MANUAL,
	MNU_MSG_SET_MMS_MR_OFF,
	MNU_MSG_SET_MMS_ALLOW_ANON_MSGS,
	MNU_MSG_SET_MMS_ANON_MSG_ON,
	MNU_MSG_SET_MMS_ANON_MSG_OFF,
	MNU_MSG_SET_MMS_RECEIVE_ADVERTS,
	MNU_MSG_SET_MMS_RA_ON,
	MNU_MSG_SET_MMS_RA_OFF,
	MNU_MSG_SET_MMS_STATUS_REPORT,
#ifdef __MMS_READ_REPORT__
	MNU_MSG_SET_MMS_READ_REPORT,
#endif
	MNU_MSG_SET_MMS_SR_ON,
	MNU_MSG_SET_MMS_SR_OFF,
	MNU_MSG_SET_MMS_DENY_REPORT_SENDING,
#ifdef __MMS_READ_REPORT__
	MNU_MSG_SET_MMS_DENY_READ_REPORT_SENDING,
#endif
	MNU_MSG_SET_MMS_DRS_ON,
	MNU_MSG_SET_MMS_DRS_OFF,
	MNU_MSG_SET_MMS_VALIDITY_PERIOD,
	MNU_MSG_SET_MMS_12_HOURS,
	MNU_MSG_SET_MMS_1_DAY,
	MNU_MSG_SET_MMS_3_DAYS,
	MNU_MSG_SET_MMS_1_WEEK,
	MNU_MSG_SET_MMS_MAX,
	MNU_MSG_SET_MMS_BACKUP_SENT_MSGS,
	MNU_MSG_SET_MMS_MMS_BS_ON,
	MNU_MSG_SET_MMS_MMS_BS_OFF,
}MmssettingMenuId_e;


enum e_DialogType
{
  DIALOG_E_START=0x00,
  DIALOG_E_CONFIRM=0x00,
  DIALOG_E_INFO,
  DIALOG_E_WARNING,
  DIALOG_E_WAITING,
  DIALOG_E_TOTAL,
};


typedef struct
{
    u16 MenuID;
    u32 TextID;
}MmsaSettingItem_t;

typedef struct
{
    u8  u8CfgValue;
    u32 nTextID;

}MmsaCfgValueTextTable_t;

typedef struct
{
    u16	nMenuID;
	u32	nCfgItem;
	u16	nSize;
    const MmsaCfgValueTextTable_t	*pValueTextTable;
    u32 nTextTableSize;
} MmsaCfgTable_t;

typedef struct
{
    u8  u8CfgValue;
    u32 nTextID;
} MmsaValueTextTable_t;


typedef struct
{
    u32 nMenuID;
    u32 nCfgItem;
    u32 nTextID;
    u16 nCfgSize;
    const MmsaValueTextTable_t *pValueTextTable;
    u32 nTextTableSize;
} MmsaPageSettingTable_t;


typedef struct
{
    u32 nMenuID;
    u32 nTextID;
}MmsaSendOptionRadioListViewInit_t;

typedef struct MMI_MMSA_TAG {
    APPLET_BASE_ELEMENTS;

    u16 nMenuID;
    MmsaCfgTable_t *pMMSA_Cfg_table_Tbl;
    COMMON_SIM_CARD_STATUS_e eSIMCardStatus;

    /* for send options menu */
    VectorClass_t *pSendOptionContentList; // record menuID and cfg item textID
	u8 nCurrentModule;

    /*page setting*/
    u32 nDuration;                     // from cfg data or AP data so it must be record.
    u32 nPageSettingUpdateMenuType;     // record current editing item

    MmsaStartType_e StartType;
    MmsaGetDurationRspCbInfo_t tRspData;
#ifdef __MMS_MMI_CDMMS_STORAGE_SWITCH__
    u8 isSwitching;
#endif    
} MMI_MMSA;

//event Callback
static boolean MmsaAppStartCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MmsaKeyPressCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MmsaAppEmbeddedCloseCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);


MAE_Ret MmsaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret MmsaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);


MAE_Ret _MMSAWndMainMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndDualSIMSelectMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndSendOptionMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndSendOptionMenuRadiolistViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndPageSettingMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndPageSettingRadiolistViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MMSAWndPageSettingEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret MMSA_WndCreateMainMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroyMainMenuView(void* pCusHandle,void* pWndData);

MAE_Ret MMSA_WndCreateDualSIMSelectMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroyDualSIMSelectMenuView(void* pCusHandle,void* pWndData);

MAE_Ret MMSA_WndCreateSendOptionMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroySendOptionMenuView(void* pCusHandle,void* pWndData);

MAE_Ret MMSA_WndCreateSendOptionMenuRadiolistView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroySendOptionMenuRadiolistView(void* pCusHandle,void* pWndData);

 MAE_Ret MMSA_WndCreatePageSettingMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
 MAE_Ret MMSA_WndDestroyPageSettingMenuView(void* pCusHandle,void* pWndData);

MAE_Ret MMSA_WndCreatePageSettingRadiolistView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroyPageSettingRadiolistView(void* pCusHandle,void* pWndData);
MAE_Ret MMSA_WndShowPageSettingRadiolistView(void* pCusHandle,void* pWndData);
MAE_Ret MMSA_WndHidePageSettingRadiolistView(void* pCusHandle,void* pWndData);


MAE_Ret MMSA_WndCreatePageSettingEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MMSA_WndDestroyPageSettingEditorView(void* pCusHandle,void* pWndData);

void  MMSA_SendOptionsCheckSimStatus(MMI_MMSA* pThis);

// setting main menu
static void MMSA_MainMenuHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret MMSA_LoadSettingMenu(MMI_MMSA* pThis);

// dual sim selection menu
static MAE_Ret MMSA_LoadDualSelectionView(MMI_MMSA *pThis);
static void MMSA_DualSelectionMenuCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

// send option menu view
static MAE_Ret  MMSA_LoadSendOptionMenuView(MMI_MMSA* pThis);
static void MMSA_InitSendOptMenuList(MMI_MMSA* pThis);
static void MMSA_FreeSendOptMenuListItem( void* pData, void* pOwner);
static void MMSA_UpdateSendOptMenuList(MMI_MMSA* pThis,MmsaSettingItem_t *pItem);
static void MMSA_GetSendOptMenuListItem(MMI_MMSA* pThis,u32 menuId, MmsaSettingItem_t **pItem);
static void MMSA_FreeSendOptMenuModelItem(void *pData, IBase *pOwner);
static void MMSA_SendOptionMenuHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

// send option radio list
static void MMSA_UpdateSendOptMenuWdgItem( MMI_MMSA* pThis, u32 idx, u32 nTextID);
static void MMSA_InitSendOptMenuWdgData(MMI_MMSA* pThis);
static void MMSA_FreeSendOptMenuWdgItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

static MAE_Ret MMSA_LoadSendOptionsRadioListView(MMI_MMSA* pThis,u32 viewId, u32 textId);
static void MMSA_SendOptionRadioListHandleCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

// page setting menu
void MMSA_PageSettingMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void MMSA_PageSettingMenuHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MMSA_PageSettingDurationRadioListFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
static void MMSA_PageSettingValueEditorHandleCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
static MAE_Ret MMSA_LoadPageSettingsMenuView(MMI_MMSA* pThis);
static MAE_Ret MMSA_LoadPageSettingsEditorView(MMI_MMSA* pThis);
static MAE_Ret MMSA_LoadPageSettingsRadioListView(MMI_MMSA* pThis, u32 nMenuType);
static void MMSA_UpdatePageSettingsMenuData( MMI_MMSA* pThis, u32 MenuId, MAE_WChar* pTextLine2, u32 nMaxTextLen);

void MMSA_PageSettingDurationRadioListHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MMSA_PageSettingCommonRadioListHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void  MMSA_PageSettingsSaveValueEditorData(MMI_MMSA* pThis);

static void MMSA_CFGSrvUpdateIndCB(void *pUserData,SrvCfgItemStatusChangeType_e IndType, SrvCfgItemUpdateResult_t tresult );
static MAE_Ret MMSA_GetMenuIDbyCFGItem(MmsaCfgTable_t * pMMSA_Cfg_table_Tbl,u32 cfgItem, u32 *pMenuID);
static MAE_Ret MMSA_GetTextIdFromCFG(u32 nCfgItemId, u8 u8CfgValue,u32 *nTextID,u8 u8CurrentModule );
static MAE_Ret MMSA_SetConfigByMenuID(MMI_MMSA* pThis, u16 nMenuId, void* buffer);

static MAE_Ret MMSA_LoadDialogView(MMI_MMSA *pThis, u8 DialogType, u32 TitleTextID, u32 InfoTextID);
MAE_Ret MMSA_CloseDialogView(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

void MMSA_OperationExitApp(MMI_MMSA* pThis);


static MAE_Ret MMSA_PageSettingGetDurationStr(MAE_WChar **pDurationStr, u32 nDuration);




#endif // __MMS_MMI_CDMMS__

#endif /* __MMI_MMSSETTINGAPP_PRIV_H__ */
