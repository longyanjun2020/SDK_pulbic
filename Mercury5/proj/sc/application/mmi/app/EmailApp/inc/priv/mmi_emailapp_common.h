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
* @file    mmi_emailapp_common.h
* @version
* @brief  EMAIL common file
*
*/

#ifndef __MMI_EMAILAPP_COMMON_H__
#define __MMI_EMAILAPP_COMMON_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_accessorysrv.h"

#include "mmi_launcher_phb.h"

#include "mmi_srv_usb.h"

//#include "nccemail_fs.h"

#include "mmi_emailsrv.h"

#include "mmi_emailapp_id.h"
#include "EmailApp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    EMAIL_BOX_INBOX = EMAIL_FS_BOXID_INBOX,
    EMAIL_BOX_OUTBOX = EMAIL_FS_BOXID_OUTBOX,
    EMAIL_BOX_SENTBOX = EMAIL_FS_BOXID_SENTBOX,
    EMAIL_BOX_DRAFTBOX = EMAIL_FS_BOXID_DRAFT,
}EmailBoxType_e;

typedef struct PublicEditorStruct
{
    u32 nTitleID;
    u32 nInputMode;
    u32 nMaxLen;
    MAE_WChar *pPublicEditInitText;
    boolean bCannotSwitchInputMode;
    boolean bEditPassword;
    boolean bViewOnly;
    boolean bMultiLine;
}EmailInitPublicEditorStruct;

typedef enum
{
    EMAIL_MENU_ITEM_START = 0x00,
    EMAIL_MENU_SEND_RETRIEVE = 0x00,
    EMAIL_MENU_CREATE_NEW = 0x01,
    EMAIL_MENU_DRAFT_BOX = 0x02,
    EMAIL_MENU_INBOX = 0x03,
    EMAIL_MENU_OUT_BOX,
    EMAIL_MENU_SENT_BOX,
    EMAIL_MENU_EDIT_ACCOUNT,
    EMAIL_MENU_SETTINGS,
    EMAIL_MENU_ITEM_TOTAL,
} EmailMainMenuItem_e;

typedef struct
{
    EMAILSRV_Status status;

    u32 MenuID;
    u32 nTotal;
    u32 nRead;
    u32 nSending;
} EmailMainMenuItemData_t;

typedef enum {
    EMAIL_EDITOR_WND_TYPE_NEW = 0,
    EMAIL_EDITOR_WND_TYPE_EDIT,
    EMAIL_EDITOR_WND_TYPE_VIEW
} EmailEditorWndType;

typedef struct {
    u32 accountID;
    u32 boxID;
    u32 emailID;
    EMAIL_HANDLE emailHandle;    // for view and edit, emailHandle should not be NULL

    EmailEditorWndType type;
} EmailEditorWndInitData_t;

typedef struct {
    IWidget *pAttachIconWdg;
    IWidget *pSizeTxtWdg;
    IWidget *pFromTxtWdg;
    IWidget *pToTxtWdg;
    IWidget *pCcTxtWdg;
    IWidget *pBccTxtWdg;
    IWidget *pSubjectTxtWdg;
    IWidget *pContentTxtWdg;
    IWidget *pPropContainer;
    IWidget *pViewPortWdg;
    IWidget *pScrollBarWdg;

    WidgetHandler_t fromTxtWdgMdLsn;
    WidgetHandler_t toTxtWdgMdLsn;
    WidgetHandler_t ccTxtWdgMdLsn;
    WidgetHandler_t bccTxtWdgMdLsn;
    WidgetHandler_t subjectTxtWdgMdLsn;
    WidgetHandler_t contentTxtWdgMdLsn;
    WidgetHandler_t scrollWdgMdLsn;

    MAE_WChar *pFromStr;
    MAE_WChar *pToStr;
    MAE_WChar *pCcStr;
    MAE_WChar *pBccStr;
    MAE_WChar *pSubjectStr;
    MAE_WChar *pContentStr;

    VectorClass_t *pFromModel;    //T_EMAIL_MailBox
    VectorClass_t *pToModel;    //T_EMAIL_MailBox
    VectorClass_t *pCcModel;    //T_EMAIL_MailBox
    VectorClass_t *pBccModel;    //T_EMAIL_MailBox
    VectorClass_t *pAttachModel;    //T_EMAIL_Attachment_Content

    VectorClass_t *pFocusWdgList;

    u32 selectedWdg;

    // init data
    u32 accountID;
    u32 boxID;
    u32 emailID;
    u32 selectedMenuID;
    EmailEditorWndType type;
    u32 totalEmailSize;
} EmailEditorWndData_t;

typedef enum
{
    EMAIL_SORT_BY_DATE,
    EMAIL_SORT_BY_SUBJECT,
    EMAIL_SORT_BY_SENDER,
}EmailSortType_t;


typedef enum
{
    E_MARK_START=0x00,
    E_MARK_OFF=0x00,
    E_MARK_ON,
    E_MARK_FOCUS,
    E_MARK_ALL,
    E_UNMARK_ALL,
    E_MARK_TOTAL
} EmailMarkType_e;

typedef struct {
    u32 emailAccountID;
    u32 boxID;
    u32 msgID;
    u32 onlyRead;    // TRUE or FALSE
    u32 titleID;

    VectorClass_t *pMailboxList;
} EmailMailboxEditorWndInitData_t;

typedef struct {
    IWidget *pMnuWdg;
    IWidget *pBgImgWdg;
    IWidget *pButtonWdg;
    IWidget *pInputWdg;
    IWidget *pPropContainer;
    IWidget *pAbsContainer;

    WidgetHandler_t inputWdgHandler;

    VectorClass_t *pMailboxList;

    u32 selectedItem;
    u32 isEnterEmailAddr;

    u32 emailAccountID;
    u32 boxID;
    u32 msgID;
    u32 onlyRead;
    u32 titleID;
    EMAIL_HANDLE emailHandle;
} EmailMailboxEditorWndData_t;

typedef enum
{
    MAILBOX_EDITOR_WND_OPTION_MNU_SEND = 0,
    MAILBOX_EDITOR_WND_OPTION_MNU_ADD_FROM_PHONEBOOK,
    MAILBOX_EDITOR_WND_OPTION_MNU_ADD_TO_PHONEBOOK,
    MAILBOX_EDITOR_WND_OPTION_MNU_DELETE,
    MAILBOX_EDITOR_WND_OPTION_MNU_DELETE_ALL,
    MAILBOX_EDITOR_WND_OPTION_MNU_SAVE_TO_DRAFT
} MailboxEditorWndOptionMenuId_e;

typedef struct {
    VectorClass_t *pAttachModel;

    boolean onlyView;
} EmailAttachEditorWndInitData_t;

typedef struct {
    IWidget *pMenuWdg;

    VectorClass_t *pAttachModel;

    u32 selectedItem;

    boolean onlyView;
} EmailAttachEditorWndData_t;

typedef struct
{
    VectorClass_t       *pToList;
    VectorClass_t       *pAttachmentList;
} EmailStartData_t;

typedef enum {
    EMAIL_OP_NONE = 0,
    EMAIL_OP_OPEN,
    EMAIL_OP_SAVE,
    EMAIL_OP_DELETE,
    EMAIL_OP_SAVE_TO_DRAFT_CONFIRM,
    EMAIL_OP_CANCEL_SEND_OR_RECEIVE_CONFIRM,
    EMAIL_OP_CANCEL_CREATE_ACCOUNT_CONFIRM,
    EMAIL_OP_SEND_EMPTY_EMAIL_CONFIRM,
    EMAIL_OP_DELETE_EMAIL_CONFIRM,
    EMAIL_OP_DELETE_ACCOUNT_CONFIRM,
    EMAIL_OP_CANCELLING
} EMAIL_OPERATE_TYPE;

/*=============================================================*/
// Variable definition & declaration
/*=============================================================*/
#define EMAIL_MMI_MAX_SUBJECT_LEN    1000
#define EMAIL_MMI_MAX_CONTENT_LEN    10 * 1024
#define EMAIL_EDITOR_HEIGHT    (MAIN_DEFVIEW_HEIGHT - MAIN_TITLE_HEIGHT)
#define EMAIL_MAILBOX_MAX_NUMBER    20
#define EMAIL_REQUEST_FREE_SPACE    2048
#define EMAIL_SETTING_USERSIGNATURE_MAXLEN         512

#define EMAIL_MAX_RETRIEVAL_SIZE 300
#define EMAIL_MIN_RETRIEVAL_SIZE 20
#define EMAIL_MAX_RETRIEVAL_AMOUNT 100
#define EMAIL_MIN_RETRIEVAL_AMOUNT 1

#ifdef EMAIL_AUTORETRIEVE_ON
#define EMAIL_MAX_EMAIL_AUTORETRIEVE 120
#define EMAIL_MIN_EMAIL_AUTORETRIEVE 1
#endif

#define EMAIL_MAX_SIZE  305156  // (298 * 1024) left 2K for email header, offset 4bytes for counting base64 encoding
#define EMAIL_MAX_CONTENT_LENGTH 10240 //(10*1024)
#define EMAIL_MAX_TEXTWDG_LEN 2048

typedef enum {
    EMAIL_ERROR_OK = 0x01,
    EMAIL_ERROR_NO_EXTCARD,
    EMAIL_ERROR_CORRUPTED_CFG_FILE,
    EMAIL_ERROR_NO_ACCOUNT,
    EMAIL_ERROR_USB_MASS_STORAGE,
    EMAIL_ERROR_USB_STATUS_PCHOST_VDC,
    EMAIL_ERROR_USB_STATUS_PCHOST_CDC_MODEM,
    EMAIL_ERROR_USB_STATUS_PCHOST_CDC_SYNCTOOL
} EMAIL_ERROR_TYPE;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret _Email_ReadAccountList(void *pApplet);

void _EmailNewAccountViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin,
    WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);

void _EmailNewAccountViewDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _EmailAccountListViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin,
    WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);

void _EmailAccountListViewDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _EmailAccountListWndMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

void _EmailNewAccountWndMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

void _EmailAccountListWndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailNewAccountWndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailAccountListOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailInputOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailInputOptionMenuLayer2SelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/**
 * get email address  from menu index.
 *
 * \param *pUserData [in]
 *
 * \param nMenuIndex [in]
 *
 *\param **ppEMailAddr[out]
 *
 *      The result of get email address  from menu index. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_GetEmailAddrByMenuIndex(void *pUserData, MAE_WChar **ppEMailAddr, u32 nMenuIndex);

/**
 * get AccountID from menu index.
 *
 * \param *pUserData [in]
 *
 * \param nMenuIndex [in]
 *
 *\param *emailAccountID[out]
 *
 *      The result of get AccountID from menu index. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret  Email_GetAccountIDByMenuIndex(void *pUserData, u32 nMenuIndex, u32 *emailAccountID);

/**
 * convert UTF8 to UCS2
 *
 * \param *pu8Str [in]
 *
 * \param **ppwStr [out]
 *
 *      The result of convert pUTF8 to pUCS2. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_CpyUtf8ToUcs2(u8 *pu8Str, MAE_WChar **ppwStr);

/**
 * convert UCS2 to UTF8
 *
 * \param *pwStr [in]
 *
 * \param **ppu8Str[out]
 *
 *\param *pBytesWritten[out]
 *
 *      The result of convert UCS2 to UTF8. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_CpyUcs2ToUtf8(MAE_WChar *pwStr, u8 **ppu8Str, size_t *pBytesWritten);

/**
 * save public editor content to struct.
 *
 * \param *pApplet [in]
 *
 *  The result of save public editor content to struct. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_SavePublicEditor(void *pApplet);

/**
 * init struct EmailInitPublicEditorStruct.
 *
 * \param *nTitleID[in]  string id of title
 *
 * \param nInputMode[in] input mode of public editor
 *
 *\param nMaxLen[in] max length of public editor
 *
 *\param *pPublicEditInitText[in] init text of public editor
 *
 *\param bCannotSwitchInputMode[in]  can not switch input mode ,if TRUE
 *
 *\param bEditPassword[in] password style ,if TRUE
 *
 *\param bViewOnly[in] view only ,if TRUE
 *
 *\param bMultiLine[in] MultiLine, if TRUE
 *
 *\param **pPubEditorInitStruct[out]
 *
 *  The result of init struct EmailInitPublicEditorStruct. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_InitPublicEditStruct(EmailInitPublicEditorStruct **pPubEditorInitStruct, u32 nTitleID,
    u32 nInputMode, u32 nMaxLen, MAE_WChar *pPublicEditInitText, boolean bCannotSwitchInputMode,
    boolean bEditPassword, boolean bViewOnly, boolean bMultiLine);

/**
 * save new account  to file system.
 *
 * \param *pUserData [in]
 *
 *  The result of save new account  to file system. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_SaveNewAccount(void * pUserData);

/**
 * save edited account  to file system.
 *
 * \param *pUserData [in]
 *
 *  The result of save edited account  to file system. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret  Email_SaveEditAccount(void * pUserData);

/**
 * save setting  to file system.
 *
 * \param *pUserData [in]
 *
 *  The result of  save setting . #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret Email_SaveEmailSetting(void * pUserData);

/**
 *delete account
 *
 * \param *pUserData [in]
 *
 *  The result of  delete account. #MAE_RET_SUCCESS, if success, otherwise #MAE_RET_FAILED.
 */
MAE_Ret  Email_DeleteAccount(void * pUserData);

/**
 *init menu of edit account tab widget
 *
 * \param *pUserData [in]
 *
 *\param nId[in]  index of tab widget
 */
void _EmailEditAccountSetMenuWidgetSize(void *pApplet, u32 nId);

void _EmailEditAccountTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);

MAE_Ret _EmailDeleteAccountConfirmDialogCB(void* pData, MAEEvent_t nEvt, u32 param1, u32 param2);

void _EmailSettingViewAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);

void _EmailSettingViewDataFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _EmailSettingTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);

void _EmailSettingWndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/**
 *init menu of setting tab widget
 *
 * \param *pUserData [in]
 *
 *\param nId[in]  index of tab widget
 */
void _EmailSettingSetMenuWidgetSize(void *pApplet, u32 nId);

void _EmailPopupSelectAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);

void _EmailPopupSelectAdaptGetFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _EmailPopupSelectSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailBoxListMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);

void _EmailBoxListMenuItemFree(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void _EmailBoxListMenuTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);

/**
 *init menu of BoxList tab widget
 *
 * \param *pUserData [in]
 *
 *\param nId[in]  index of tab widget
 */
void _EmailBoxListSetMenuWidgetSize(void *pApplet);

void _EmailBoxListWndMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailMainMenuAdapterGetItem(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);

void _EmailMainMenuItemFree(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

MAE_Ret _EmailLoadMainMenuView(void *pCusHandle, void *pWndData, void *pRC);

void EmailMainMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void EmailMainMenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret EmailCreateMainMenuWnd(void *pCusHandle, void *pWndData, void *pRC);

void _EmailUpdateMenuAt(IWidget *pMenuWdg, WdgMenuItemType_e eItemType, u32 nIndex, PfnWdgDynamicMenuGetDataPtr pfnMenuAdapterGet, void *pApplet);

void EmailApp_UpdateMainMenu(void *pCusHandle, void *pWndData);

boolean EmailApp_HandleKeyPressForMainMenuWnd(void *pApplet, u32 nParam1, u32 nParam2);


void _EmailDestroyMainMenuWnd(void *pWndHandle, void *pWndData);

void EmailApp_UpdateMainMenuItemInfo(void *pApplet, EmailMainMenuItemData_t *pMainMenuItem);

void _EmailApp_OpenAccount(void *pApplet);

void _EmailApp_OpenEditEmailWnd(void *pApplet, EmailEditorWndType type);

MAE_Ret EmailApp_InitEditEmailWndData(void *pCusHandle, EmailEditorWndData_t *pWndData, EmailEditorWndInitData_t *pInitData);

void EmailApp_DestroyEditEmailWnd(void *pCusHandle, void *pWndData);

MAE_WChar *_EmailAppGetMailboxStrByMailboxList(VectorClass_t *pMailboxList);

void _EmailBoxListOptionMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void _EmailBoxListBoxOptMenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret _EmailApp_SaveEmailDlgHandler(void *pApplet, MAEEvent_t eventID, u32 nParam1, u32 nParam2);

boolean EmailApp_HandleKeyPressForEditEmailWnd(void *pApplet, u32 nParam1, u32 nParam2);

void EmailApp_LoadEmailEditorOptionMenu(void *pApplet);

void EmailApp_EditEmailOptionSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserved);

boolean EmailApp_FromTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_FromTxtWdgEventHandlerFree(void *pApplet);

boolean EmailApp_ToTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_ToTxtWdgEventHandlerFree(void *pApplet);

boolean EmailApp_CcTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_CcTxtWdgEventHandlerFree(void *pApplet);

boolean EmailApp_BccTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_BccTxtWdgEventHandlerFree(void *pApplet);

boolean EmailApp_ShowInputWnd(void *pApplet, EmailEditMenuId_e menuID);

boolean EmailApp_SubjectTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_SubjectTxtWdgEventHandlerFree(void *pApplet);

boolean EmailApp_ContentTxtWdgEventHandler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_ContentTxtWdgEventHandlerFree(void *pApplet);

void EmailApp_EmailEditorSetFocus(void* pUserData, u32 newFocus);

boolean EmailApp_EmailEditorScrollbarWdgHandleEvent(void* pUserData, MAE_EventId event, u32 param1, u32 param2);

void EmailApp_EmailEditorScrollbarWdgHandleEventFree(void *pApplet);

MAE_Ret EmailApp_InitEmailEditorWnd(void *pCusHandle, EmailEditorWndData_t *pWndData, EmailEditorWndInitData_t *pInitData);

MAE_Ret EmailApp_InitMailboxEditorWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

void EmailApp_MailboxEditorButtonWdgCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

void EmailApp_ShowMailboxEditorWnd(void *pApplet, u32 type);

boolean EmailApp_HandleMailboxEditorKeyPress(void *pApplet, u32 nParam1, u32 nParam2);

void EmailApp_LoadMailboxEditorOptionMenu(void *pApplet, void *pWndData, u32 nWndInitParam);

void EmailApp_MailboxEditorOptionSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserved);

void EmailApp_MailboxMenuAdapterGet(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);

void EmailApp_MailboxMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

void EmailApp_MailboxMenuSoftKeyHandleCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

boolean EmailApp_MailboxEditorHandleEvent(void *pUserData, MAE_EventId evt, u32 param1, u32 param2);

void EmailApp_MailboxEditorEventHandlerFree(void *pUserData);

#ifndef __SMALL_PHB_MMI__
void EmailApp_LaunchPhoneBook(void *pApplet, EmailMailboxEditorWndData_t *pWndData);

void EmailApp_PhbGetContactCb(void *pvUserData, MAE_Ret nRspCode, PhoneBookGetContactRecord_t *psRspData,
    PhoneBookGetContactRspDataFreeCb pfnRspDataFreeCb);
#endif

void EmailApp_MailboxEditorTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

void EmailApp_MailboxFocusedOnEditor(void *pApplet, MAE_EventId evt, u32 keycode);

void _EmailShowEmailNewAccountWnd( void *pCusHandle,void *pWndData);

void _EmailBoxMarkOptUpdateMenu (void *pApplet, IWidget *pOptMenuWdg);

//sort email
void _EmailSort(void *pApplet, u32 sortBy);

void _Email_deleteEmail(void *pApplet);

MAE_Ret _EmailDeleteEmailConfirmDialogCB(void* pData, MAEEvent_t nEvt, u32 param1, u32 param2);

void _deleteEmail(void *pApplet);

void EmailApp_SendReceiveCB(void *pApplet, EMAILSRV_AccountStatusInfo_t *pProgressInfo);

void EmailApp_SendReceive(void *pApplet, u32 accountID, u32 reqType);

MAE_Ret EmailApp_CreateAttachEditorWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//boolean EmailApp_HandleAttachEditorKeyPress(void *pApplet, u32 nParam1, u32 nParam2);

MAE_Ret EmailApp_CreateAttachEditorOptionMenuWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);

//change email status.
void _EmailMarkEmailAsRead(void *pApplet, u32 boxID, u32 emailID, u8 isRead);

// nParam1 means error code
MAE_Ret EmailApp_BootupFailed(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

void EmailApp_AccessoryPlugStatusCB(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

void _EmailBoxListWndMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

void EmailApp_UsbStatusChangedCB(void *pApplet, MMI_USB_STATUS_E eUsbStatus);

//get base-64 email size.
s32 _EmailApp_GetCurEmailSize(EmailEditorWndData_t *pEditorWndData);

MAE_Ret _EmailApp_SaveEmailConfirmDlgHandler(void *pApplet, MAEEvent_t eventID, u32 nParam1, u32 nParam2);

/**
 * Check if need to load save email confirm dialog, if return TRUE, that means the confirm dialog has been pop up.
 */
boolean EmailApp_loadSaveConfirmDialog(void *pApplet);

void EmailApp_handleAppResumeStoppingCB(void *pApplet);

MAE_Ret EmailApp_BoxListMenuSetMarkedNumOnTitle(IWidget *pMenuWdg, IWidget *pTitleWdg);

void EmailApp_BoxListMenuMarkedNumberChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);

void _EmailSetDefaultAccount(void *pApplet, u32 Index);

void _EmailApp_FreeMailboxContent(void *pData, void *pOwner);

void _EmailApp_FreeAttachment(void *pData, void *pOwner);

void EmailApp_OpenAttachment(void *pApplet, T_EMAIL_Attachment_Content *pAttachItem);

void EmailApp_StopPlayHandler(void *pData);

void EmailApp_SetEmailListPrevCountAsCurrent(void *pApplet, u32 boxId);

void EmailApp_AudioStopCB(void *pData, MediaSrvErrCode_e eErrorCode);
#endif // #define __MMI_EMAILAPP_COMMON_H__

