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
* @file mmi_emapp_util.h
*
* Class Id:
*
* @version $Id: mmi_em_util.h 27716 2009-04-07 13:12:36Z eric.chen $
*/
#ifndef __MMI_EMAPP_UTIL_H__
#define __MMI_EMAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"
#include "mmi_emapp_menuinfo.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/


#define BUFFER_SIZE 32
#define SMS_UCS2_MAX_CHAR    603

#define SEPERATOR_TAG L";"
#define MMS_PROFILE_NAME_TAG L"Profile:"
#define MMS_PROFILE_MMSC_TAG L"MMSC:"
#define MMS_PROFILE_HOMEPAGE_TAG L"Homepage:"
#define MMS_PROFILE_CONTYPE_TAG L"Connection Type:"
#define MMS_PROFILE_CONTYPE_CONNECTION_ORIENTED_TAG L"WAP"
#define MMS_PROFILE_CONTYPE_HTTP_TAG L"HTTP"
#define MMS_PROFILE_PROXY_TAG L"Proxy:"
#define MMS_PROFILE_PORT_TAG L"Port:"
#define DATA_ACCOUNT_NAME_TAG L"Data Account:"
#define DATA_ACCOUNT_APN_TAG L"APN:"
#define DATA_ACCOUNT_USERNAME_TAG L"User name:"
#define DATA_ACCOUNT_PASSWORD_TAG L"Password:"
#define DATA_ACCOUNT_AUTH_TYPE_TAG L"Auth.Type:"
#define DATA_ACCOUNT_DNS_TAG L"DNS:"

//-----------

typedef u32  (* EM_REQUEST_FUNC_PTR)(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
typedef EmAppResRet_e  (* EM_REPONSE_FUNC_PTR)(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
typedef u32 (* EM_EXIT_FUNC_PTR)(EmAppData_t *pThis, u32 param1);

typedef enum
{
    EM_MENU,
    EM_RADIO_MENU,
    EM_EDIT,
    EM_SYNC_INFO,
    EM_ASYNC_INFO,
    EM_LAUNCH_AP,
    EM_SPECIFIC,
    EM_SYSTEM_INFO,
#ifdef __3G_RIL_MMI__
    EM_CUSTOMIZE,
#if defined (__UPGRADE_GENIE_OVER_SHMCONN__)
    EM_FILE_SEL_LIST,
#endif //#if defined (__UPGRADE_GENIE_OVER_SHMCONN__)
#endif //#ifdef __3G_RIL_MMI__
} EmAppNextFormType_e;

//Each menu item info
typedef struct EM_Menu_Item_Info_TAG
{
    EM_REQUEST_FUNC_PTR     pRequestFunc;
    EM_REPONSE_FUNC_PTR     pReposnseFunc;
    EM_EXIT_FUNC_PTR        pExitFunc;
    EmAppMenuId_e           eMenuID;
    EmAppNextFormType_e     eNextFormType;
    MAE_WChar               *pWStrMenuItemName;
    //EM_Operation_Table_t  pOperationTable;
} EmAppMenuItemInfo_t;

typedef struct
{
    EmAppMenuId_e eParentMenuID;
    EmAppMenuId_e eMenuID;
    s32 sValue;
} EM_Radio_Menu_Item_Value_Info_t;

//This struct is stored menu item and menu item info.
//It used to create mapping table
typedef struct EM_Menu_Table_Info_TAG
{
    const EmAppMenuItemInfo_t   *pMenuTable;
    EmAppMenuId_e               eMenuID;
    u8                          u8MenuTableSize;
    MAE_WChar *pWStrMenuTitle;
} EmAppMenuInfo_t;

//This struct is used to create view
typedef struct
{
    IWidget     **ppIMenuWdg;
    IWidget     **ppIInputWdg;
    MAE_WChar   *pWTitleTextBuffer;
    boolean     bHaveMenuWidget;
    u16         u16ViewID;
} EmAppViewData_t;

//This struct is used to store menu history
typedef struct
{
    //u8  eMenuItem;
    const EmAppMenuInfo_t *pMenuInfo;
    u32 u32LogFirstItemIndex;
    u32 u32LogHighlightIndex;
} EmAppMenuHistoryData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret GetIMEI(void);
MAE_Ret EmAppUCS2ToAscii(const u16 *pUnicode, u8 **ppAscii);

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
MAE_Ret _EmAppAutoTest(EmAppData_t* pThis);
void _EmAppLaunchAp(EmAppData_t* pThis, u32 param1);
MAE_Ret _EmAppSwitchToWindow(EmAppData_t *pThis, EmAppWndId_e eWndId, u32 nWndParam);

void _EmAppGeneralSubMenuAllocatesSubMenuRes(EmAppData_t* pThis, int nParam);

void _EmAppCheckEvent(EmAppData_t *pThis, EmAppEventInfo_t *pEventInfo, EmAppCheckEventType_e eCheckEventType);

void _EmAppDisplayResult(EmAppData_t* pThis, EmAppEventInfo_t *pEventInfo);

MAE_Ret _EmAppGetMenuInfo(EmAppData_t *pThis, EmAppMenuId_e eMenuID, const EmAppMenuInfo_t **ppMenuTableInfo);
MAE_Ret _EmAppGetRadioMenuValueInfo(EmAppData_t *pThis, EmAppMenuId_e eMenuID, s32 *pValue);
MAE_Ret _EmAppGetRadioMenuSettingValueInfo(EmAppData_t *pThis, EmAppMenuId_e eParentMenuID, s32 nValue, EmAppMenuId_e *pSettingMenuID);
MAE_Ret _EmAppLoadPickMenuItem(EmAppData_t* pThis, const EmAppMenuItemInfo_t *pEMInfoTable, u16 u16MenuItemNum);
void _EmAppPickMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
MAE_Ret _EmAppShowMenuList(EmAppData_t *pThis, void *pWndData, int param1, int param2);

MAE_Ret _EmAppGetTopViewSK(EmAppData_t *pThis, SoftkeyID_e *eLSK, SoftkeyID_e *eCSK, SoftkeyID_e *eRSK);
void _EmAppDisplayRSK(EmAppData_t *pThis, SoftkeyID_e eRSK);
void _EmAppDisplaySK(EmAppData_t *pThis, Softkey_Type eType, SoftkeyID_e eSK);
void _EmAppGetLeafNodeSK(EmAppData_t *pThis, EmAppMenuId_e eMenuID, SoftkeyID_e *eLSK, SoftkeyID_e *eCSK, SoftkeyID_e *eRSK);
void _EmAppSetEditInputMode(EmAppData_t *pThis ,EmAppMenuId_e eMenuID, IWidget *pInputWdg);

//Stack function
void  _EmAppMenuHistoryVectorItemFree(void *pItemData, void *pUseData);
MAE_Ret _EmAppPushMenuHistory(VectorClass_t *pIVctModel,void *pData);
MAE_Ret _EmAppPopMenuHistory(VectorClass_t *pIVctModel, void **ppData);
boolean _EmAppHaveMenuHistory(VectorClass_t *pIVctModel);

void _EmAppMainListViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _EmAppLevel2ListViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __GPRS_MMI__
//GPRS
void _EmAppFillGSMandGPRSDefault(EmAppGsmGprs_t *pThis);
#endif //__GPRS_MMI__
//KEY PAD

MAE_Ret _EmAppGotoEMLeafNode(EmAppData_t *pThis, const EmAppMenuItemInfo_t *pMenuItemInfo);

MAE_Ret _EmAppAutoTestTestItem(EmAppData_t *pThis, u8 nTestItem);
void _EmAppAutoTestFillSuccessValueForAutoCheck(EmAppData_t *pThis);
MAE_Ret _EmAppDisplayAutoTestResult(EmAppData_t *pThis, MAE_WChar *pWStrResult, SoftkeyID_e eLSK, SoftkeyID_e eCSK, SoftkeyID_e eRSK);
void _EmAppDisplayAutoTestSummary(EmAppData_t *pThis);
void _EmAppResetAutoTestInfo(EmAppData_t *pThis);
void _EmAppEnableUSBSrv(EmAppData_t* pThis, boolean bEnable);

#ifndef __EM_KEYPAD_TEST_FUN__
void _EndKeyBtnWdgViewMdlLsn(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
void _SendKeyBtnWdgViewMdlLsn(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#endif//__EM_KEYPAD_TEST_FUN__

#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI__)
u32 _EMAPP_SendProfile(EmAppData_t *pThis, u32 nSimModule, MAE_WChar *pTelNo, u16 nTelNoSize);
u32 _EMAPP_GetMMSProfileSettings(EmAppData_t *pThis, MAE_WChar *pContent, u32 nMaxLength, boolean *pbMore, u32 *pnProfileId);
u32 _EMAPP_GetWAPProfileSettings(EmAppData_t *pThis, MAE_WChar *pContent, u32 nMaxLength, boolean *pbMore, u32 *pnProfileId);
void _EMAPP_SendSMSCallback(IBase *pObj, u32 userData, SMS_Send_Result_t *pResult);
MAE_Ret _EMAPP_SendSmsWithoutNotify(u8 nSimModule, MAE_WChar *pTelNo, u16 nTelNoSize, MAE_WChar *pSMSContent, u16 nContentSize, SMI_SmEncoding_t nEncoding, pfn_sms_send_CB pFnSendCb, u32 userData);
#endif
void _EmPrint2InputWdg(EmAppData_t *pThis, MAE_WChar *pwszTextBuffer);

#endif//__MMI_EMAPP_UTIL_H__
