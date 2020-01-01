/**
* file  mmi_remotecontrolapp_priv.h
*
*
*/

#ifndef __MMI_REMOTECONTROLAPP_PRIV_H__
#define __MMI_REMOTECONTROLAPP_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_baseapplet.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/




#define M_nSize_MenuItem(x) (sizeof(x)/sizeof(x[0]))


/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
    REMOTECONTROLAPP_WND_MAINMENU = WND_ID_APP_BASE,
    REMOTECONTROLAPP_WND_POP_CONTROL_FUNCTION,
    REMOTECONTROLAPP_WND_POP_NUMBER,
    REMOTECONTROLAPP_WND_POP_FIXED_NUMBER,
    REMOTECONTROLAPP_WND_COMMAND_EXAMPLE,
    REMOTECONTROLAPP_WND_NOTIFY_NUMBER,
    
}RemoteControlWndId_e;
/*
typedef enum
{
    ANTISTEAL_FIRST_INPUT = 0,
    ANTISTEAL_CONFIRM_INPUT,
    ANTISTEAL_LAND_INPUT,
}RemoteControlPassWordInputId_e;
*/
typedef enum
{
    REMOTECONTROL_MENU_LIST_CONTROL_FUNCTION = 0,
    REMOTECONTROL_MENU_LIST_NUMBER,
    REMOTECONTROL_MENU_LIST_COMMAND_EXAMPLE,
}RemoteControlMainMenuListId_e;


typedef enum
{
    REMOTECONTROL_MENU_LIST_ANY_NUMBER = 0,
    REMOTECONTROL_MENU_LIST_FIXED_NUMBER,
}RemoteControlNumberMenuListId_e;



/**
* Application structure
*/
typedef struct MMI_REMOTECONTROLAPP_TAG
{
    APPLET_BASE_ELEMENTS;
    /* Select Number Type  menu widget */
    IWidget     *pNumberTypeMenuWdg;
    IWidget     *pControlFunctionMenuWdg;
    u32 nSelectControlFunction;
	u8 nSelectNumberType;
    
    //IWidget   *pIMainMenuListWdg;
    //MAE_WChar *pPassWordNew;
    //RemoteControlMainMenuListId_e eMainMenuListId;
    //SMI_SmEncoding_t nEncoding;
} MMI_REMOTECONTROLAPP;
/*
typedef struct _RemoteControl_Control_Function_t
{
    boolean bPowerOff;
    boolean bCallTransfer;
    boolean bSMSTransfer;
    boolean bPhoneLock;
    boolean bFetchPhb;
    boolean bFetchSMS;
    boolean bDeletePhb;
    boolean bDeleteSMS;
    boolean bDeleteCallLog;
    boolean bFormatStorage;
}RemoteControl_Control_Function_t;
*/

/*=============================================================*/
// functions
/*=============================================================*/

MAE_Ret RemoteControlAppWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndCreateMainMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlAppWndNotifyNumberHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndCreateNotifyNumber(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndDestroyNotifyNumber(void *pCusHandle, void *pWndData);

//static void AntiStealAppPassWordInputCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

MAE_Ret RemoteControlWndControlFunctionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndCreateControlFunction(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret RemoteControlWndNumberHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndCreateSelectNumberType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlAppWndCmdExHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RemoteControlWndCreateCmdEx(void *pCusHandle, void *pWndData, u32 nWndInitParam);

#endif
