/**
* @file mmi_messagetemplateapp_priv.h
*
*
*/
#ifndef __MMI_MESSAGETEMPLATEAPP_PRIV_H__
#define __MMI_MESSAGETEMPLATEAPP_PRIV_H__

#include "mmi_baseapplet.h"
#include "mmi_base_util.h"
#include "mmi_messagetemplateapp.h"

#include "mmi_message_cfg.h"
#include "mmi_common_dialog.h"
#include "mmi_wdg_headers.h"
#include "mmi_UrlSrvClientHelper.h"
#include "mmi_messagetemplateapp_rs.h"

typedef struct {
    u8     TemplateId;          // idx:1~10
    boolean bSaved;             // TURE:saved message, FALSE:unsaved message
}EditTemplate_t;

typedef struct{
    u32 TempalteId;          //Template Id in IConfig(for Text Template)/SMI(for Meida Template)
    MAE_WChar *pText;
    u32 nTextLen;
}MsgTemplate_t;

typedef struct
{
    WdgStaticMenuItemInf_t sInfo;
    u32 nTextID;
}OptionMenuItem_t;
enum
{
    MTA_Status_Init,
    MTA_Status_DisplayList,
    MTA_Status_Editor,
    MTA_Status_EditorOption,
    MTA_Status_Save,
    MTA_Status_SaveConfirm, // for any interrupt close to ask user if svaing current content
    MTA_Status_DeleteAllConfirm,
    MTA_Status_DeleteConfirm,
    MTA_Status_TemplateMsg,
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
    MTA_Status_Preview,
#endif
};

typedef u8 MtaStatus_e;

/**
 * Application structure
 */
typedef struct MMI_MTA_TAG {
    APPLET_BASE_ELEMENTS;

    MtaStatus_e eCurrentStatus;
    EditTemplate_t *pEditTemp;
    boolean bParentAskClose; //After here Resume, AP should Exit;
    boolean bEndKeyAskClose; //After here Resume, AP should Exit;
   	u32 nHighlightedIndex;
    IImage *pTemIconImg;
    VectorClass_t   *pDataVector; //The Vector Model of Template
    MtaStartMode_e eStartMode;
    UrlSrvUrlRspInfo_t tRspInfo;
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
    boolean bTextTemplate;  //Text or Media Template
    boolean bMMSPreView;    
#endif
} MMI_MTA;

enum e_DialogType
{
  DIALOG_E_START=0x00,
  DIALOG_E_CONFIRM=0x00,
  DIALOG_E_INFO,
  DIALOG_E_WARNING,
  DIALOG_E_WAITING,
  DIALOG_E_TOTAL,
};


enum e_OptionMenu
{
    MTA_MAIN_OPTION_CREAT_MSG,
    MTA_MAIN_OPTION_EDIT,
    MTA_MAIN_OPTION_DELETE,
    MTA_MAIN_OPTION_NEW,
    MTA_EDIT_OPTION_SAVE,
    MTA_EDIT_OPTION_INPUTE
};
#define MTA_DIALOG_TIMER  1000
#define MTA_PROGRESS_NUM  3
#define MTA_MENU_EMPTY_ITEM 0xFFFFFFFF

static MAE_Ret MTA_PrepareListData(MMI_MTA *pThis);
static MAE_Ret MTA_LoadMainListView(MMI_MTA *pThis);
static void MTA_VectorFreeItem(void *pData, void *pOwner);
static void MTA_MenuAdapterGetItem (WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
static void MTA_MainMenuHandleCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifdef __MMS_MMI_CDMMS_TEMPLATE__
static void MTA_TemplateTypeSelectionHandleCB( void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserved );
#endif
#ifdef __MMS_MMI_CDMMS__
static void MTA_ListOptMenuL2HandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
static void MTA_ListOptionMenuHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

static MAE_Ret MTA_LoadEditorView(MMI_MTA* pThis);
static void MTA_EditorTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
static void MTA_EditorOptMenuL2HandleCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void MTA_EditorOptionMenuHandleCB (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


static MAE_Ret MTA_SaveEditingTemplate(MMI_MTA *pThis);
static MAE_Ret MTA_EditTemplate(MMI_MTA* pThis, boolean bNew);

static MAE_Ret MTA_LoadDialogView(MMI_MTA *pThis, u8 DialogType, boolean bAuto, u32 TitleTextID, u32 InfoTextID,PFN_DlgHandler pfnDialogHdl);
void MTA_WaitingDialogTimeout(void *pData);
MAE_Ret MTA_CloseDialog(void *pData);
MAE_Ret MTA_CloseInfoDialog(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

static MAE_Ret MTA_OperationSaveEditedTemplate(MMI_MTA* pThis);
static MAE_Ret MTA_OperationDelete(MMI_MTA* pThis);
static MAE_Ret MTA_OperationDeleteAll(MMI_MTA* pThis);
static void  MTA_OperationSetOptionWdgToInputWdg(MMI_MTA* pThis);
static MAE_Ret MTA_OpeartionCloseAPSave(MMI_MTA* pThis);
static void MTA_OpeartionSelectTemplateAndCloseAp(MMI_MTA* pThis);
static void MTA_OperationExitApp(MMI_MTA *pThis);


static boolean MTA_SaveConfirmKeyPress(void *pUsrData, MAE_EventId evt, u32 param1, u32 param2);
static boolean MTA_DelAllConfirmKeyPress(void *pUsrData, MAE_EventId evt, u32 param1, u32 param2);
static boolean MTA_DelOneConfirmKeyPress(void *pUsrData, MAE_EventId evt, u32 param1, u32 param2);

typedef enum MtaWndId_e_
{
    MTA_WND_MAIN_LIST_VIEW = WND_ID_APP_BASE,
    MTA_WND_MAIN_LIST_OPTION_VIEW,
    MTA_WND_EDITOR_VIEW,
    MTA_WND_EDITOR_OPTION_VIEW,
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
    MTA_WND_TEMPLATE_TYPE_SELECTION_VIEW,
#endif
}MtaWndId_e;



MAE_Ret MtaConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret MtaDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);

//event Callback
static boolean MtaAppStartCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MtaAppStopCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MtaAppSuspendCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MtaAppResumeCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MtaKeyPressCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);
static boolean MtaAppEmbeddedCloseCB(IApplet* pApplet, u32 nEvt, u32 param1, u32 param2);

MAE_Ret _MTAWndMainListViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MTAWndMainListOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MTAWndEditorViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _MTAWndEditorOptionViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
MAE_Ret _MTAWndTemplateTypeSelectionViewHdl( void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam );
#endif

MAE_Ret MTA_WndCreateMainListView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MTA_WndDestroyMainListView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndShowMainListView (void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndHideMainListView (void* pCusHandle,void* pWndData);

MAE_Ret MTA_WndCreateMainListOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MTA_WndDestroyMainListOptionView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndShowMainListOptionView (void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndHideMainListOptionView (void* pCusHandle,void* pWndData);

MAE_Ret MTA_WndCreateEditorView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MTA_WndDestroyEditorView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndShowEditorView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndHideEditorView(void* pCusHandle,void* pWndData);

MAE_Ret MTA_WndCreateEditorOptionView(void* pCusHandle,void* pWndData, u32 nWndInitParam);
MAE_Ret MTA_WndDestroyEditorOptionView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndShowEditorOptionView(void* pCusHandle,void* pWndData);
MAE_Ret MTA_WndHideEditorOptionView(void* pCusHandle,void* pWndData);
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
MAE_Ret MTA_WndCreateTemplateTypeSelectionView( void *pCusHandle, void *pWndData, u32 nWndInitParam );
MAE_Ret MTA_WndDestroyTemplateTypeSelectionView( void *pCusHandle, void *pWndData );

void    MTA_LaunchMMSTemplateEditor( void *pCusHandle, u32 nTemplateIndex, boolean bPreviewOnly );
#endif

#endif /* __MMI_MESSAGETEMPLATEAPP_PRIV_H__ */
