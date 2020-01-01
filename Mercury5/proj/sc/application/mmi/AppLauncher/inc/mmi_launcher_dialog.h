#ifndef __LAUNCHER_DIALOG_APP_H__
#define __LAUNCHER_DIALOG_APP_H__

#include "mmi_launcher_common.h"
//#include "mmi_evtcentersrv.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/
#define DIALOGAPP_EVT_LSKPressed				(CLSID_DIALOGAPP << 16 | 1)
#define DIALOGAPP_EVT_CSKPressed				(CLSID_DIALOGAPP << 16 | 2)
#define DIALOGAPP_EVT_RSKPressed				(CLSID_DIALOGAPP << 16 | 3)
#define DIALOGAPP_EVT_AutoTimeOut				(CLSID_DIALOGAPP << 16 | 4)
#define DIALOGAPP_EVT_DialogMerged				(CLSID_DIALOGAPP << 16 | 5)
#define DIALOGAPP_EVT_ENDPressed				(CLSID_DIALOGAPP << 16 | 6)
#define DIALOGAPP_EVT_StopRingtoneOnly				(CLSID_DIALOGAPP << 16 | 7)

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    DIALOG_AP_START_ACTIVE,
    DIALOG_AP_START_SUSPEND,
}Dialog_Start_e;

//typedef enum
//{
//    DIALOG_TYPE_BATT_NORMAL = 1
//    ,DIALOG_TYPE_BATT_URGENT
//    ,DIALOG_TYPE_SMS
//    ,DIALOG_TYPE_ACCESSORY
//    //no ring tone.
//    ,DIALOG_TYPE_MISSEDCALL
//    ,DIALOG_TYPE_CALENDAR
//    ,DIALOG_TYPE_ALARM
//    ,DIALOG_TYPE_TODO
//    ,DIALOG_TYPE_MM
//    ,DIALOG_TYPE_GENERAL
//    //no ring tone.
//    ,DIALOG_TYPE_SMS_STATUS_REPORT
//    ,DIALOG_TYPE_PHONEBOOK
//    ,DIALOG_TYPE_BT
//    ,DIALOG_TYPE_CB
//    ,DIALOG_TYPE_MMS
//} Dialog_Type_e;

//typedef u8 Dialog_Start_e;

typedef struct DialogRspData_t_
{
    Dialog_Start_e eStartStatus;
    boolean bPlayMelody;
    u32 nMelodyID;
}DialogRspData_t;
//typedef void (*pfnDialogLaunchRspCb) (void *pCBData, Dialog_Start_e StartStatus);
typedef void (*DialogRspDataFreeCb)(DialogRspData_t *pStatusData);
typedef void (*pfnDialogLaunchRspCb)(void *pvUserData, MAE_Ret nRspCode, DialogRspData_t *pStatusData, DialogRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
    void *pvUserData;
    pfnDialogLaunchRspCb pfnRspCb;
}DialogAppRspCbInfo_t;
/*
typedef struct DialogLaunchInfo_t_
{
MAE_WChar               *pDialogMsg;    //Pointer to the string which should be displayed if not set default Text is used
u16		                nDialogViewID;  //Dialog Type View ID: eg.COMMON_DIALOG_INFODIALOG 
u32                     nLSK;           //Will use default SK if this param is not set to another SK
u32                     nCSK;           //Will use default SK if this param is not set to another SK
u32                     nRSK;           //Will use default SK if this param is not set to another SK
u32                     nAutoCloseTimer;//Timer in mSec. If set to 0, auto close is turned off
u32                     MsgId;          //The MsgId Assigned by the caller to make sure the caller knows which Msg is being answered
IModel                  *pIModel;       //Model to inform the caller whether the dialog has been answered by the user or not
//EvtCenterDialogType_e   eDialogType;
boolean                 bPlayMelody;
u32                     nMelodyID;	
pfnDialogLaunchRspCb    pfnDialogStartCB;
void                    *pCBData;
}DialogLaunchInfo_t;*/
/////////////////////////////////////////////////////////////////
/// 1. EventCenter srv,        APM_Mode = APM_LAUNCH_INTERRUPTIVE,     param = DialogApp_DialogInfo_t,  Mode = ALARM_EMBEDDEDMODE_VIEWALARM

/// 1.
/// Launch Dialog App, then create a dialog for use.
/// "Dialog://StartDialog?APM_Mode=%d"
void LaunchAppToStartDialog
(
 AppLaunchMode_e eAppLaunchMode,
 // *pDialogLaunchInfo,
 MAE_WChar               *pDialogMsg,    //Pointer to the string which should be displayed if not set default Text is used
 u16		                nDialogViewID,  //Dialog Type View ID: eg.COMMON_DIALOG_INFODIALOG 
 u32                     nLSK,         //Will use default SK if this param is not set to another SK
 u32                     nCSK,           //Will use default SK if this param is not set to another SK
 u32                     nRSK,           //Will use default SK if this param is not set to another SK
 u32                     nAutoCloseTimer,//Timer in mSec. If set to 0, auto close is turned off
 u32                     MsgId,          //The MsgId Assigned by the caller to make sure the caller knows which Msg is being answered
 u32                     pIModel,       //Model to inform the caller whether the dialog has been answered by the user or not
 u32                     eDialogType,
 boolean                 bPlayMelody,
 u32                     nMelodyID,	  
 LaunchAppTransParam_t *psTransParam,
 DialogAppRspCbInfo_t    *pRspCbInfo
 );

#endif/* __LAUNCHER_DIALOG_APP_H__ */
