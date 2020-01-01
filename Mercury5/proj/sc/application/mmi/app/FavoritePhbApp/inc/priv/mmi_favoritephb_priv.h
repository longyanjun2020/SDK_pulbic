////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_favoritephb_priv.h
* @version $Id: mmi_favoritephb_priv.h
*/




#ifndef __MMI_FAVORITEPHB_PRIV_H__
#define __MMI_FAVORITEPHB_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_favoritephb.h"

/*-------------------------------------------------------------------------*/
#include "mmi_srv_header.h"
#include "mmi_favoritephb_id.h"
#include "mmi_common_vtm.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_dialog.h"
#include "mmi_launcher_common.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_cc.h"
#include "mmi_launcher_em.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_security.h"
#include "mmi_launcher_ussd.h"
#include "mae_textlabel.h"

typedef struct
{
	MmiPhbNumber_t	atNumber[FAVORITE_PHB_ITEM_MAX_NUM];
} MmiPhbData_t;

typedef struct
{
	MenuWdgList_t	tMenuWdgList;
	MenuData_t		tMenuData;
	MenuCB_t 		tMenuCB;
	//WdgStaticMenuItem_t tMenuItemData[FAVORITE_PHB_ITEM_MAX_NUM];
}FavoritePhbMainWdgList_t;

typedef struct
{
    FavoritePhbMainWdgList_t tWdgList;
}FavoritePhbMainWndData_t;

typedef struct FAVORITEPHB_TAG {
    APPLET_BASE_ELEMENTS;
	MmiPhbData_t tPhbData;
	MmiPhbContactContent_t tPhbContact;
	u32 nFocusIdx;
} FavoritePhbData_t;





/*-------------------------------------------------------------------------*/
MAE_Ret FavoritePhbConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret FavoritePhbDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean FavoritePhbStartCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
boolean FavoritePhbSuspendCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean FavoritePhbResumeCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean FavoritePhbKeyPressCB(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);

//Pre declaration
static MAE_Ret _FavoritePhbCreateMainWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FavoritePhbDestroyMainWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FavoritePhbConvertMainWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
void _FavoritePhbMenuGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr,HWIN hWin,WdgMenuItemType_e eItemType,IWidget *pMenu,u32 u32Index);
void _FavoritePhbMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr,HWIN hWin,WdgMenuItemType_e eItemType);
void _FavoritePhbMenuSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
void _FavoritePhbMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
static MAE_Ret _FavoritePhbReadPhbFile(FavoritePhbData_t *pThis);
static IImage * _FavoritePhbLoadContactImage(IApplet * pThis, u32 ImgId);
MAE_Ret FavoritePhbMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _FavoritePhbSearchContactbyNum(FavoritePhbData_t *pThis, MmiPhbNumber_t *ptNumber, boolean bIsFull, boolean bIsGrid);
MAE_Ret _FavoritePhbDeleteConfirmCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean _FavoritePhbKeyPressCBMainWnd(IApplet* pApplet,MAEEvent_t nEvt, u32 lparam, u32 dparam);
void _FavoritePhbDeleteButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
static MAE_Ret _FavoritePhbMakePhoneCall(FavoritePhbData_t* pThis, MMI_SSSRV_USSD_SIM_Type_e eSimType);
static MAE_Ret _FavoritePhbLaunchCCAP(FavoritePhbData_t* pThis, u8* pDialStr, CcAppCallType_e eCallType);
static MAE_Ret _FavoritePhbLaunchUSSD(FavoritePhbData_t* pThis, MMI_SSSRV_USSD_Action_Type_e eType, MMI_SSSRV_USSD_SIM_Type_e eSimType);
void _FavoritePhbGetContactRspCb(void *pvUserData, MAE_Ret nRspCode, PhoneBookGetContactRecord_t *psRspData, PhoneBookGetContactRspDataFreeCb pfnRspDataFreeCb);
MAE_Ret _FavoritePhbDialogTimeOutCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
void _FavoritePhbAddFavoriteContact(FavoritePhbData_t *pThis);
void _FavoritePhbNotifyPhbSrvReadyCB(void* pUserdata);


/*-------------------------------------------------------------------------*/
#endif /* __MMI_FAVORITEPHB_PRIV_H__ */
