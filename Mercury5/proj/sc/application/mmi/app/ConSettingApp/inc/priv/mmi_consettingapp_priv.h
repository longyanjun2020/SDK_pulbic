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
* @file    mmi_consettingapp_priv.h
* @version
* @brief   ConSetting applet private header file
*
*/

#ifndef __MMI_CONSETTINGAPP_PRIV_H__
#define __MMI_CONSETTINGAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_consettingapp.h"
#include "mmi_consettingapp_view_id.h"
#include "mmi_common_dialog.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_header.h"
#include "mmi_wdg_headers.h"
#include "mmi_consettingapp_id.h"
#include "consettingapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define SWPRINT_IP_FORMAT L"%d.%d.%d.%d"
#define PASSWORD_CHAR 0x2A //L"*"
#define IP_TEXT_LENGTH 15 //255.255.255.255
#define CON_DIALOG_TIMER 1000

#define CONSETTING_ARR_SIZE ARR_SIZE

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pAccountNameWdg;
    IWidget *pAPNWdg;
    IWidget *pUserNameWdg;
    IWidget *pPasswordWdg;
    IWidget *pAuthTypeWdg;
    IWidget *pDNSWdg;
}ConSettingMFLDataAccountWdgList_t;

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pHomePageWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLWAPSettingsWdgList_t;

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pMMSCWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLMMSSettingsWdgList_t;

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLJavaSettingsWdgList_t;

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLOtherSettingsWdgList_t;

typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLLBSSettingsWdgList_t;

#ifdef __EMAIL_MMI__
typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLEmailSettingsWdgList_t;
#endif // __EMAIL_MMI__

#ifdef __NCCQQ_MMI__
typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLQQSettingsWdgList_t;
#endif // __NCCQQ_MMI__

#ifdef __STREAMING_MODULE__
typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pConnectTypeWdg;
    IWidget *pProxyWdg;
    IWidget *pPortWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLStreamingSettingsWdgList_t;
#endif // __STREAMING_MODULE__

#ifdef __APP_MMI_NTP__
typedef struct
{
    IWidget *pScrollbarWdg;
    IWidget *pMflCntr;
    IWidget *pProfileNameWdg;
    IWidget *pDataAccountWdg;
}ConSettingMFLNtpSettingsWdgList_t;
#endif // __APP_MMI_NTP__


typedef struct
{
    union
    {
        ConSettingMFLDataAccountWdgList_t  tDataAccountWdgList;
        ConSettingMFLWAPSettingsWdgList_t  tWAPSettingsWdgList;
        ConSettingMFLMMSSettingsWdgList_t  tMMSSettingsWdgList;
        ConSettingMFLJavaSettingsWdgList_t tJavaSettingsWdgList;
        ConSettingMFLOtherSettingsWdgList_t tOtherSettingsWdgList;
        ConSettingMFLLBSSettingsWdgList_t  tLBSSettingsWdgList;

#ifdef __EMAIL_MMI__
        ConSettingMFLEmailSettingsWdgList_t tEmailSettingsWdgList;
#endif // __EMAIL_MMI__

#ifdef __NCCQQ_MMI__
        ConSettingMFLQQSettingsWdgList_t   tQQSettingsWdgList;
#endif // __NCCQQ_MMI__

#ifdef __APP_MMI_NTP__
        ConSettingMFLNtpSettingsWdgList_t tNtpSettingsWdgList;
#endif // __APP_MMI_NTP__ 


#ifdef __STREAMING_MODULE__
        ConSettingMFLStreamingSettingsWdgList_t   tStreamingSettingsWdgList;
#endif // __STREAMING_MODULE__

    } tWdgList;
    u32 nViewID;
} ConSettingMFLWndData_t;

typedef struct
{
    u32 nViewID;
} ConSettingListMenuWndData_t;

void _ConSettingConvertMFLViewDataAccount(HWIN hWin, ConSettingMFLDataAccountWdgList_t *pWdgList);
void _ConSettingCreateMFLViewDataAccount(HWIN hWin, ConSettingMFLDataAccountWdgList_t *pWdgList);
void _ConSettingConvertMFLViewWAPSettings(HWIN hWin, ConSettingMFLWAPSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewWAPSettings(HWIN hWin, ConSettingMFLWAPSettingsWdgList_t *pWdgList);
void _ConSettingConvertMFLViewMMSSettings(HWIN hWin, ConSettingMFLMMSSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewMMSSettings(HWIN hWin, ConSettingMFLMMSSettingsWdgList_t *pWdgList);
void _ConSettingConvertMFLViewJavaSettings(HWIN hWin, ConSettingMFLJavaSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewJavaSettings(HWIN hWin, ConSettingMFLJavaSettingsWdgList_t *pWdgList);
void _ConSettingConvertMFLViewOtherSettings(HWIN hWin, ConSettingMFLOtherSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewOtherSettings(HWIN hWin, ConSettingMFLOtherSettingsWdgList_t *pWdgList);
void _ConSettingConvertMFLViewLBSSettings(HWIN hWin, ConSettingMFLLBSSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewLBSSettings(HWIN hWin, ConSettingMFLLBSSettingsWdgList_t *pWdgList);
#ifdef __EMAIL_MMI__
void _ConSettingConvertMFLViewEmailSettings(HWIN hWin, ConSettingMFLEmailSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewEmailSettings(HWIN hWin, ConSettingMFLEmailSettingsWdgList_t *pWdgList);
#endif

#ifdef __NCCQQ_MMI__
void _ConSettingConvertMFLViewQQSettings(HWIN hWin, ConSettingMFLQQSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewQQSettings(HWIN hWin, ConSettingMFLQQSettingsWdgList_t *pWdgList);
#endif

#ifdef __STREAMING_MODULE__
void _ConSettingConvertMFLViewStreamingSettings(HWIN hWin, ConSettingMFLStreamingSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewStreamingSettings(HWIN hWin, ConSettingMFLStreamingSettingsWdgList_t *pWdgList);
#endif

#ifdef __APP_MMI_NTP__
void _ConSettingConvertMFLViewNtpSettings(HWIN hWin, ConSettingMFLNtpSettingsWdgList_t *pWdgList);
void _ConSettingCreateMFLViewNtpSettings(HWIN hWin, ConSettingMFLNtpSettingsWdgList_t *pWdgList);
#endif // __APP_MMI_NTP__

//*******************************************************************//

typedef struct
{
    u32 nViewID;
    CFGItemID_e eSetDataCFGID; //If only part of the config structure => set as SET_PART_OF_CFG,
                                //using the WDG_ID to identify which member of the structure is set
    CFGItemID_e eSortMenuCFGID;
    SetViewType_e eViewType;
}ConSettingMenuItem_t;

typedef struct
{
    ScrollData_t tScrollData;
    u32 nWdgId; //in MFL, the WDG visible could set false, so save the WdgId, but not the hightlightIdx
}ConSettingMFLHistory_t;

typedef union
{
    HistoryInfo_t tMenuData;
    ConSettingMFLHistory_t tMFLData;
}ConSetHistory_t;

typedef struct
{
    ConSetHistory_t tMenuPos;
    boolean bNewAdd;
    void *pSetData;  //Setting Structure, String, or Value(enum) pointer, if is sortmenu=> SortCfg Structure pointer
    ConSettingMenuItem_t tMenuItemData;
}ConSettingViewLog_t;

typedef struct
{
    ConSettingMenuItem_t tMenuItemInfo;
    WdgDynamicMenuItemPtr_t tMenuItem;
}ConSettingMenuData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    ConSettingViewLog_t *pCurrentLog;
    VectorClass_t *pHistoryLog;
    COMMON_SIM_CARD_STATUS_e eSIMStatus;// Sim status.
    IWidget * pDoubleWidget;
    u8 nIP[IPAddressSize];
    u32 nItemSize;
} ConSettingAppData_t;

typedef enum
{
    MEMBER_TYPE_NONE=0,
    MEMBER_TYPE_RADIO_SORT,
    MEMBER_TYPE_RADIO_LIST,
    MEMBER_TYPE_RADIO_STATIC,
    MEMBER_TYPE_INPUT_START,
    MEMBER_TYPE_INPUT_IP=MEMBER_TYPE_INPUT_START,
    MEMBER_TYPE_INPUT_NUMBER,
    MEMBER_TYPE_INPUT_DIAL_NUMBER,
    MEMBER_TYPE_INPUT_PASSWORD,
    MEMBER_TYPE_INPUT_TEXT,
    MEMBER_TYPE_INPUT_END=MEMBER_TYPE_INPUT_TEXT
}ConSettingMemberType_e;

/*Condition View Type*/
typedef enum
{
    CONDITION_ORG_VIEW,
    CONDITION_POP_COND_VIEW,
    CONDITION_ENTER_NEW_VIEW,
    CONDITION_PROMPT_DIALOG,
} ConSettingConditionResult_e;

typedef ConSettingConditionResult_e (*pfnCondition)(ConSettingAppData_t* pThis);

typedef struct
{
    u32 nViewID;
    pfnCondition EnterConditionFunc;
    pfnCondition BackConditionFunc;
}ConSettingConditionTransfer_t;


/*MFL View Type*/
typedef void (*pfnDataFree)(void *pData, IBase *pOwner);
typedef MAE_Ret (*pfnDataToSetItemTranfer)(void *pData, void *pSetStruct, u16 nItemOffset,  u16 nItemSize, IBase *pOwner);
typedef MAE_Ret (*pfnSetItemToDataTranfer)(void *pSetItem, u16 nItemOffset,  u16 nItemSize, MAE_WChar *pNewTitle, boolean bFreeNewTitle, void **ppData, IBase *pOwner);
typedef MAE_Ret (*pfnSetItemToWidget)(IWidget *pWDG, void *pSetStruct, u16 nItemOffset,  u16 nItemSize, IBase *pOwner);
typedef MAE_Ret (*pfnWidgetToItem)(IWidget *pWDG, void *pSetStruct, u16 nItemOffset,  u16 nItemSize, IBase *pOwner);

//MFL Data and Widget Init
typedef MAE_Ret (*pfnSetDataWidgetInit)(void *pSetStruct, IBase *pOwner);

#define NON_MFL_ITEM 0xFF
typedef struct
{
    u32 nWidgetID;
    pfnDataToSetItemTranfer pfnDataToItem; //Detail Eidt View SetData To Current View SetData member
    pfnSetItemToDataTranfer pfnItemToData; //SetData member To Detail Eidt View SetData
    pfnSetItemToWidget      pfnItemSetToWdg; //Set the SetData member to the Wdg
    pfnWidgetToItem         pfnWdgToItem;    //Get ItemSet from Wdg
    u16 nItemOffset;
    u16 nItemSize;
    ConSettingMemberType_e eWdgType;
    u16 nMaxSize; //Input Char Number, or Number of Pick Items
    ConSettingMenuItem_t   tMenuItemInfo;
}ConSettingMFLItem_t;

typedef struct
{
    u32 nViewID;
    pfnSetDataWidgetInit pfnDataWidgetInit;
    const ConSettingMFLItem_t * pTable;
    u8 nTableSize;
}ConSettingMFLViewToItem_t;

typedef MAE_Ret(*pfnGetStaticMenuListItem)(void **ppMenuData, u8 nIdx, boolean bMenuItem, IBase * pOwner);  //bMenuItem: TRUE => Menu Item; FALSE => List Items (for List widget in Pick widget)
typedef struct
{
    u32 nViewID;
    u32 nTitleTextID;
    u8  nMaxNumItems;
    pfnGetStaticMenuListItem pfnGetMenuData;
}ConSettingListMenuTransfer_t;

/*Save*/
typedef MAE_Ret(*pfnSaveDataTransfer)(void *pSetData, void **ppSaveCfgData, pfnDataFree *pfnSaveCfgDataFree, IBase *pOwner);

typedef struct
{
    u32 nViewIDStart;
    u32 nViewIDEnd;
    pfnSaveDataTransfer pfnSetDataToSaveData;
}ConSettingSetDataTransfer_t;

typedef struct
{
    u32 nViewID;
    u32 nTitleStrID;
}ConSettingPopupRadioMenuTitleStrID_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret ConSettingConstructor(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret ConSettingDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ConSettingStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ConSettingKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ConSettingSuspendCb(IApplet *pApplet, MAEEvent_t nEvt, u32 lparam, u32 dparam);

MAE_Ret ConSettingWndListMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateListMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConvertListMenu(void *pCusHandle, void *pWndData);

MAE_Ret ConSettingWndRadioMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateRadioMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConvertRadioMenu(void *pCusHandle, void *pWndData);

MAE_Ret ConSettingWndMFLHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateMFL(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConvertMFL(void *pCusHandle, void *pWndData);

MAE_Ret ConSettingWndOptHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateOpt(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConvertOpt(void *pCusHandle, void *pWndData);
MAE_Ret ConSettingWndDestroyOpt(void *pCusHandle, void *pWndData);

MAE_Ret ConSettingWndInputTextHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateInputText(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConvertInputText(void *pCusHandle, void *pWndData);

MAE_Ret ConSettingWndIPEditorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndCreateIPEditor(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret ConSettingWndConertIPEditor(void *pCusHandle, void *pWndData);

void ConSettingListSimMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingListMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingDynamicRadioMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingStaticRadioMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingNonEmptyInputTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void ConSettingInputNumberTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void ConSettingOptL2SoftkeyHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingOptHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ConSettingInputOptHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void ConSettingMflContainerScrollChangeCb (void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ScrollData_t *pScrollData, IWidget *ppContainer);
void ConSettingMflContainerFocusCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);

void ConSettingListItemGetByType(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
void ConSettingListItemFreeByType(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void ConSettingWdgPickRelease(void *pData, IBase *pOwner);

#endif /* __MMI_CONSETTINGAPP_PRIV_H__ */
