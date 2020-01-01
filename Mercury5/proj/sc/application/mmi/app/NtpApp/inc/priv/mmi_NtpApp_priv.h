#ifndef __MMI_NTPAPP_PRIV_H__
#define __MMI_NTPAPP_PRIV_H__


#include "mmi_mae_common_def.h"
#include "mmi_baseapplet.h"
#include "mmi_common_dialog.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_header.h"

#include "mmi_NtpApp_id.h"
#include "NtpApp_resource.h"
#include "mmi_ntp.h"

typedef enum _NtpAppSimStatus_e
{
    EN_NTP_NO_SIM = 0,
    EN_NTP_ONE_SIM,
    EN_NTP_DUAL_SIM,
    EN_NTP_SIM_MAX,    //error happened here
}NtpAppSimStatus_e;

typedef enum _NtpAppSimID_e
{
    EN_NTP_SIM_ID_0 = 0,
    EN_NTP_SIM_ID_1,
    EN_NTP_SIM_ID_NONE = 0xFF,
}NtpAppSimID_e;

typedef enum _NtpIpIdx_e
{
    EN_NTP_IP_NTSC = 0,
    EN_NTP_IP_MICROSOFT,
    EN_NTP_IP_MAX,          // for array or error handling
}NtpIpIdx_e;

typedef enum _NtpDialogType_e
{
    EN_NTP_DLG_GET_PROFILE_FAIL = 0,
    EN_NTP_DLG_NO_SIM_CARD_INSERTED,
    EN_NTP_DLG_ACTIVE_SIM_FIRST,
    EN_NTP_DLG_CREATE_DATALINK_FAIL,
    EN_NTP_DLG_CREATE_SOCKET_FAIL,
    EN_NTP_DLG_SEND_GETTIME_REQ_FAIL,
    EN_NTP_DLG_REG_RECV_CB_FAIL,
    EN_NTP_DLG_SYNC_TIME_CANCELED,
    EN_NTP_DLG_SYNC_TIME_TIMEOUT,
    EN_NTP_DLG_SYNC_TIME_FAIL,
    EN_NTP_DLG_CONVERT_TIME_FAIL,
    EN_NTP_DLG_SET_TIME_FAIL,
    EN_NTP_DLG_USB_MODEM_MODE_NTP_CANT_LAUNCH,
    EN_NTP_DLG_SYNC_TIME_OK,
    EN_NTP_DLG_MAX,
}NtpDialogType_e;


//===============

typedef struct _NtpMainWndDataTag
{
    MenuWdgList_t tMenuWdgList;
}NtpMainWndData_t;

typedef struct _NtpSelectSimWndDataTag
{
    SimSelectionWdgList_t tMenuWdgList;
}NtpSelectSimWndData_t;

typedef struct _NtpSelectServerWndDataTag
{
   PopUpSelectWdgList_t tPopUpSelectWdgList;
}NtpSelectServerWndData_t;


typedef struct _NtpIpMapTag
{   
    u8 nIpAdrr[16];
    u16 nNtpPort;
}NtpIpMap_t;



typedef struct
{
    APPLET_BASE_ELEMENTS;
	boolean bResumeToSyncTime;
    boolean bRecvTimePacket;
    MMI_USB_STATUS_E eUsbStatus;
    u8 nReqRetryTimes;
	NtpIpIdx_e enIpIdx;
	NtpAppSimID_e enSelSimID;
    MAE_DateTime_t tConvertTime;
    NTP_ServerSetting_e enNtpServerSetting;
    ConSetting_ConnectSet_e nConnectSetType;
    NtpIpMap_t tNtpIpMap; 
    NtpNetworkData_t tNtpData;
    boolean bDataLinkCreated;
    u32 nCreateDLCnt;   
 }NtpAppData_t;
/*=============================================================*/
// Internal Event
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean NtpAppStartCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean NtpAppStopCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean NtpAppSuspendCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean NtpAppResumeCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean NtpAppKeyPressCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret NtpAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NtpAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void NtpAppShowDialog(IApplet *pApplet, NtpDialogType_e enWDlgType);


/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret _NtpAppExitAppAutotimeoutDialogCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
boolean _NtpAppIsSIMEnbleFirst(COMMON_SIM_CARD_STATUS_e enSIMCardStatus);
NtpAppSimStatus_e _NtpAppGetSimStatus(NtpAppData_t *pThis, COMMON_SIM_CARD_STATUS_e *pEnSIMStatus);
u32 _NtpAppGetServerTextId(NtpAppData_t *pThis);
void _NtpAppSetNtpIpIdx(NtpAppData_t *pThis);
NTP_ServerSetting_e _NtpAppGetServerSettingByMenuID(NtpMenuId_e eMenuId);
MAE_Ret _NtpAppDlgCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);
boolean _NtpAppIsUsbStatusConflictWithNtp(void *pApplet);
void NtpAppNetworkStatusListenerCB(IBase *pApplet, void *pvUserData, SrvSocketNetworkStatus_e eStatus);
void _NtpAppCloseWaitingDlg(void *pOwner);
/*=============================================================*/
// Ntp related function definition
/*=============================================================*/
MAE_Ret _NtpAppSyncTime(void *pApplet);
MAE_Ret _NtpAppStartSyncTime(void *pApplet);
MAE_Ret _NtpAppStopSyncTime(void *pApplet);
MAE_Ret _NtpAppGetProfileData(void *pApplet);

MAE_Ret _NtpAppWaitingDialogKeyPressCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);

/*------------------------------*/
// Main Wnd handle
/*------------------------------*/
MAE_Ret _NtpAppMainWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndDestroyMain(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndShowMain(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndHideMain(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndConvertMain(void *pCusHandle, void *pWndData);

void _NtpAppMainMenuMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/*------------------------------*/
// Select Sim Wnd handle
/*------------------------------*/
MAE_Ret _NtpAppSelectSimWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndCreateSelectSim(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndDestroySelectSim(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndShowSelectSim(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndHideSelectSim(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndConvertSelectSim(void *pCusHandle, void *pWndData);

void _NtpAppSelectSimSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

/*------------------------------*/
// Select Server Wnd handle
/*------------------------------*/
MAE_Ret _NtpAppSelectServerWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndCreateSelectServer(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _NtpAppWndDestroySelectServer(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndShowSelectServer(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndHideSelectServer(void *pCusHandle, void *pWndData);
MAE_Ret _NtpAppWndConvertSelectServer(void *pCusHandle, void *pWndData);

void _NtpAppSelectServerSoftKeyCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);


#endif

