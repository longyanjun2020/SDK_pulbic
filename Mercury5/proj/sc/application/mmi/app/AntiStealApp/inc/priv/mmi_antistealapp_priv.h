/**
* file  mmi_antistealapp_priv.h
*
*
*/

#ifndef __MMI_ANTISTEALAPP_PRIV_H__
#define __MMI_ANTISTEALAPP_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_common_vtm.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
    ANTISTEAL_WND_MAINMENU = WND_ID_APP_BASE,
    ANTISTEAL_WND_FIRST_PASSWORD, 
    ANTISTEAL_WND_CONFIRM_PASSWORD,
    ANTISTEAL_WND_LAND_PASSWORD,
    ANTISTEAL_WND_BACK_TRANSPARENCE,
    ANTISTEAL_WND_NOTIFY_NUMBER,
    ANTISTEAL_WND_NOTIFY_CONTENT,
    ANTISTEAL_WND_NOTIFY_CONTENT_OPTION,
    ANTISTEAL_WND_REMOTE_CONTROL,
    ANTISTEAL_WND_HELP,
}AntiStealWndId_e;

typedef enum
{
    ANTISTEAL_FIRST_INPUT = 0,
    ANTISTEAL_CONFIRM_INPUT,
    ANTISTEAL_LAND_INPUT,
}AntiStealPassWordInputId_e;

typedef enum
{
    ANTISTEAL_MENU_LIST_STATUS = 0,
#ifdef __ANTI_STEAL_REMOTE_CONTROL_MMI__	
    ANTISTEAL_MENU_LIST_REMOTE,
#endif	
    ANTISTEAL_MENU_LIST_NUMBER,
    ANTISTEAL_MENU_LIST_CONTENT,
    ANTISTEAL_MENU_LIST_PASSWORD,
    ANTISTEAL_MENU_LIST_HELP,
}AntiStealMainMenuListId_e;

typedef enum
{
    ANTISTEAL_CONTENT_OPTION_SAVE = 0,
}AntiStealNotifyContentOptionListId_e;
#ifdef __ANTI_STEAL_REMOTE_CONTROL_MMI__
typedef enum
{
    ANTISTEAL_CANCEL_CALL_DIVERT_NONE = 0,
    ANTISTEAL_CANCEL_CALL_DIVERT_MASTER,
    ANTISTEAL_CANCEL_CALL_DIVERT_SLAVE,
    ANTISTEAL_CANCEL_CALL_DIVERT_BOTH,
}AntiStealCancelCallDivert_e;
#endif //__ANTI_STEAL_REMOTE_CONTROL_MMI__

/**
* Application structure
*/
typedef struct MMI_ANTISTEALAPP_TAG
{
    APPLET_BASE_ELEMENTS;

    IWidget   *pIMainMenuListWdg;
    MAE_WChar *pPassWordNew;
    AntiStealMainMenuListId_e eMainMenuListId;
    SMI_SmEncoding_t nEncoding;
	InputVtmWdgList_t tWdgList;
} MMI_ANTISTEALAPP;

/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret AntiStealConstructCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AntiStealKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AntiStealStopCB(IApplet *pApplet, u32 nEvt, u32 lparam, u32 dparam);

static void AntiStealAppPassWordInputCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
static void AntiStealAppNotifyNumberInputCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

static void AntiStealAppMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
static void AntiStealAppContentOptionL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#endif
