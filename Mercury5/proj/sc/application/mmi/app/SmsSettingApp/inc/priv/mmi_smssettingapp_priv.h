/**
* @file mmi_smssettingapp_priv.h
*
* Class Id: CLSID_MSA
*
*/
#ifndef __MMI_SMSSETTINGAPP_PRIV_H__
#define __MMI_SMSSETTINGAPP_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_smssettingapp_custom.h"
#include "mmi_message_cfg.h"
#include "mmi_common_sms.h"
#include "mmi_common_dialog.h"
#include "mmi_common_util.h"

#include "mmi_srv_cfg.h"
#include "mmi_srv_sms.h"
#include "mmi_srv_smstx.h"
#include "mmi_base_util.h"
#include "mmi_smssettingapp_id.h"
#include "SmsSettingApp_resource.h"

#define PrefixChar '+'
#define MSA_DIALOG_TIMER 1000


typedef struct
{
    u32 nMenuId;
    u32 nTextId;
}MSA_PopupRadiolistInitParm_t;

enum e_Dialog_Type
{
  DIALOG_E_START=0x00,
  DIALOG_E_CONFIRM=0x00,
  DIALOG_E_INFO,
  DIALOG_E_WARNING,
  DIALOG_E_WAITING,
  DIALOG_E_TOTAL,
};

typedef enum
{
    Disable_LEFTSK = 0,
    Enable_LEFTSK
}MsaUpdateSatus_e;


typedef struct
{
    u16 MenuID;
    union
    {
       u32 TextID;
       MAE_WChar pText[MSG_SMS_SERVICE_CENTER_MAX_CHAR+1];
    }value;
}MsaSettingItem_t;

typedef struct
{
    u32 nMenuItemID;
    u8  u8CfgValue;
    u32 nTextID;
}MsaCfgValueTextTable_t;

typedef struct
{
    u16	MenumodelId;
	u32	nCfgItem;
	u16	nSize;
    const MsaCfgValueTextTable_t	*pValueTextTable;
    u32 nTextTableSize;
} MsaCfgTable_t;


/**
 * Application structure
 */
typedef struct MMI_MSA_TAG {

    APPLET_BASE_ELEMENTS;

    u8 nCurrentModule;
    u16 nMenuId; // record current select menuId for get/save configure
    COMMON_SIM_CARD_STATUS_e eSIMCardStatus;
    MsaStartType_e StartType;
    u8 *pTempStorageCfg;
    VectorClass_t *pSettingList;
    MsaCfgTable_t *pMSA_Cfg_table_Tbl;

//    IModel *pAPNotifyMdl;
} MMI_MSA;

//event Callback
static boolean MsaAppStartCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MsaAppResumeCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MsaKeyPressCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MsaAppEmbeddedCloseCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);

MAE_Ret MsaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret MsaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);

MAE_Ret _MSAWndMainMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MSAWndDualSIMSelectMenuViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MSAWndPopupRadiolistViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MSAWndPopupEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret MSA_WndCreateMainMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MSA_WndDestroyMainMenuView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndShowMainMenuView (void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndHideMainMenuView (void* pCusHandle,void* pWndData);

MAE_Ret MSA_WndCreateDualSIMSelectMenuView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MSA_WndDestroyDualSIMSelectMenuView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndShowDualSIMSelectMenuView (void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndHideDualSIMSelectMenuView (void* pCusHandle,void* pWndData);

MAE_Ret MSA_WndCreatePopupRadiolistView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MSA_WndDestroyPopupRadiolistView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndShowPopupRadiolistView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndHidePopupRadiolistView(void* pCusHandle,void* pWndData);

MAE_Ret MSA_WndCreatePopupEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MSA_WndDestroyPopupEditorView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndShowPopupEditorView(void* pCusHandle,void* pWndData);
MAE_Ret MSA_WndHidePopupEditorView(void* pCusHandle,void* pWndData);


static void MSA_HandleSmsSIMChangeCB(void *pData,COMMON_SIM_CARD_STATUS_e eSimStatus);
static void MSA_HandleTxiSmsSetStatusReportCnfCB(void *pData,MMI_SMS_SetStatusReportCnf_t * pSetStatusReportCnf);
static void MSA_HandleCfgChangeCB(void *pData, SrvCfgItemStatusChangeType_e eIndType, SrvCfgItemUpdateResult_t tresult);

static MAE_Ret MSA_GetMenuIDbyCFGItem(MsaCfgTable_t * pMSA_Cfg_table_Tbl,u32 cfgItem, u32 *pMenuID);
static MAE_Ret MSA_GetTextIDByMenuId(MMI_MSA* pThis, u32 MenuID, u32 *pTextID);
static MAE_Ret MSA_GetTextIdFromCFG(u32 nCfgItemId, u8 u8CfgValue,u32 *nTextID,COMMON_SIM_CARD_STATUS_e eSIMStatus );
static MAE_Ret MSA_SetConfigByMenuID(MMI_MSA* pThis, u16 nMenuID, void* buffer);


void MSA_CheckSIMStatusAndInitSettingList(MMI_MSA* pThis);
void MSA_HandleMainMenuCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static MAE_Ret MSA_LoadMainMenuView(MMI_MSA *pThis);
static void MSA_FreeMainMenuListItem(void* pData, void* pOwner);
static void MSA_InitMainMenuList(MMI_MSA* pThis);
static void MSA_UpdateMainMenuList(MMI_MSA* pThis,MsaSettingItem_t *pItem);
static void MSA_InitMainMenuData(MMI_MSA *pThis);
static void MSA_UpdateMainMenuItemDataLine2(MMI_MSA* pThis, u32 MenuId, MAE_WChar* pTextLine2, u32 nMaxTextLen);
static void MSA_FreeMainMenuModelItem(void *pData, IBase *pOwner);
static void MSA_GetMainMenuListItem(MMI_MSA* pThis,u32 menuId, MsaSettingItem_t **pItem);

static MAE_Ret MSA_LoadPopupRadiolistView(MMI_MSA* pThis, MSA_PopupRadiolistInitParm_t *pInitData);
static void MSA_HandlePopupRadioListMenuCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

static MAE_Ret MSA_LoadPopupEditorView(MMI_MSA* pThis, MAE_WChar *pInitText);
static void MSA_HandlePopupEditorInputCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void  MSA_PopupEditorUpdateSoftKey(MMI_MSA* pThis, MsaUpdateSatus_e eStatus);

MAE_Ret MSA_CloseDialogView(MMI_MSA* pThis);
MAE_Ret MSA_DialogTimeOutCloseApplet(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret MSA_DialogTimeOutBackMainMenu(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
static MAE_Ret MSA_LoadDialogView(MMI_MSA *pThis, u8 DialogType, u32 TitleTextID, u32 InfoTextID,PFN_DlgHandler nDlgFunc);

static void MSA_HandleDualSimSelectionMenuCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static MAE_Ret MSA_LoadDualSimSelectionMenuView(MMI_MSA *pThis);

void MSA_OperationExitApp(MMI_MSA * pThis);


/*-------------------------------------------------------------------------*/
#endif /* __MMI_SMSSETTINGAPP_PRIV_H__ */
