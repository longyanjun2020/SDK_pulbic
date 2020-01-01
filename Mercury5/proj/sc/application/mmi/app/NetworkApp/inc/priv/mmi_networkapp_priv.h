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
* @file    mmi_networkapp_priv.h
* @version
* @brief   Network setting applet private header file
*
*/

#ifndef __MMI_NETWORKAPP_PRIV_H__
#define __MMI_NETWORKAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_header.h"
#include "mmi_common_dialog.h"

#include "mmi_wdg_headers.h"
#include "mmi_common_vtm.h"
#include "mmi_networkapp_id.h"
#include "mmi_networkapp_rs.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/
#ifdef  __DUAL_SIM_MMI__
#define NETWORKAPP_SIM_SLOT_NUM 2 //For support Dual SIM, Master/Slave
#else
#define NETWORKAPP_SIM_SLOT_NUM 1 //For support only One SIM
#endif

#define NETWORKAPP_ALLOWED_PREFER_PLMN_NUM      8  //From the sepc (3GPP 51.011), the EF(PLMNsel) contains the coding for n PLMNs, where n is at least eight. It means it has at least 8 records in SIM.
#define NETWORKAPP_MAX_STR_LENGTH              30


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef u32 MenuItemID_e;

typedef enum
{
    MMI_NETWORKAPP_APP_MODE_NORMAL=0,   //Normal created by setting
    MMI_NETWORKAPP_APP_MODE_SPECIFIC=1     //Created by MMSrv for Online mode

} MMI_NETWORKAPP_APP_MODE_e;

typedef struct MMI_NETWORKAPP_MAIN_LIST_TAG
{
    boolean     bLogHistory;
    u16         u16LogFirstItemIndex;
    u16         u16LogHighlightIndex;
    boolean     bLogHistory_Lev2;
    u16         u16LogFirstItemIndex_Lev2;
    u16         u16LogHighlightIndex_Lev2;
    u32         u32LogSelectedOptionMenuID;

} MMI_NETWORKAPP_MAIN_LIST;

typedef struct MMI_NETWORKAPP_SETTING_TAG
{
    //keep settings of network ap
    MMI_MMSRV_RegMode_e         NetSelection;
#ifdef __GPRS_MMI__
    MMI_MMSRV_NetAccess_Mode_e  NetAccess;
#endif //__GPRS_MMI__
    MMI_MMSRV_Band_e            Band;
    MMI_MMSRV_Line_Service_e    ActiveLine;
    MMI_MMSRV_RegMode_e         NetSelectionTemp;
#ifdef __GPRS_MMI__
    MMI_MMSRV_NetAccess_Mode_e  NetAccessTemp;
#endif //__GPRS_MMI__
#ifdef __3G_RIL_MMI__
    BandSelection_Mode_e         BandTemp;
#else
    MMI_MMSRV_Band_e            BandTemp;
#endif
    MMI_MMSRV_Line_Service_e    ActiveLineTemp;

} MMI_NETWORKAPP_SETTING;

typedef struct MMI_NETWORKAPP_PREFER_PLMN_TAG
{
    u32     PlmnIDList[MMI_MM_NBMAX_PLMN]; //MCC+MNC
    u32     CurrentPLMNID;
    u16     CurrentIndex;

} MMI_NETWORKAPP_PREFER_PLMN_INFO;

/**
* Application structure
*/
typedef struct NetworkAppData_t_
{
    APPLET_BASE_ELEMENTS;

    u8          currDualID;
    boolean     bIsWaitConfirm;

    MMI_NETWORKAPP_SETTING              NetworkSetting[NETWORKAPP_SIM_SLOT_NUM];  //for keep current settings
    MMI_NETWORKAPP_MAIN_LIST            *pMMIMainList;          //Profile List
    MMI_NETWORKAPP_APP_MODE_e           AppMode;                //for keep App mode
    MMI_NETWORKAPP_PREFER_PLMN_INFO     *pPreferPlmnData;        //for Prefer PLMN data

} NetworkAppData_t;

typedef enum NetworkWndId_e_
{
    NETWORK_WND_DUAL_SIM = WND_ID_APP_BASE,
    NETWORK_WND_NETWORK_SETTING,
    NETWORK_WND_PREFERRED_LIST,
    NETWORK_WND_PREFERRED_LIST_NETWORK_LIST,
    NETWORK_WND_PREFERRED_LIST_OPTION_MENU,
    NETWORK_WND_NET_SELECTION_MODE,
    NETWORK_WND_NET_SELECTION_MODE_NETWORK_LIST,
    NETWORK_WND_NET_ACCESS_MODE,
    NETWORK_WND_BAND_SELECTION,
    NETWORK_WND_LINE_SELECTION,

} NetworkWndId_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret NetworkConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret NetworkDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NetworkStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NetworkStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean NetworkKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#ifdef __GPRS_MMI__
void NetworkQueryWgprsCnfCb(void *pApplet, MMSRV_QueryWGPRSCnf_t *pData, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
void NetworkQueryLineCnfCb(void *pApplet, MMSRV_QueryLineCnf_t *pData, MAE_DualMode_t eDualMode);
void NetworkQueryBandCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MMI_MMSRV_Band_e eBand);
void NetworkQueryPreferredPLMNListCnfCb(void *pApplet, MMSRV_PreferredPLMNQuerytCnf_t *pData, MAE_DualMode_t eDualMode);
void NetworkUpdatePreferredPLMNListCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
void NetworkNetworkRegCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
void NetworkNetworkSearchCnfCb(void *pApplet, MMSRV_NetworkQuerytCnf_t *pData, MAE_DualMode_t eDualMode);
#ifdef __GPRS_MMI__
void NetworkChangeNetAccessModeCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
void NetworkChangeBandCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#ifdef __3G_RIL_MMI__
void NetworkChangeBandExCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif
void NetworkChangeLineCnfCb(void *pApplet, MMSRV_ChangeLineCnf_t *pData, MAE_DualMode_t eDualMode);
void NetworkAirplaneCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
boolean NetworkPreferredListRemoveConfirmDlgCb(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#ifdef __BLUETOOTH_MMI__
static MAE_Ret NetworkTurnOnAirplaneModeCb(void* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#endif

//Window manager related function
MAE_Ret _NetworkDualSimWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkNetworkSettingWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkPreferredListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkPreferredListNetworkListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkPreferredListOptionMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkNetSelectionModeWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkNetSelectionModeNetworkListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __GPRS_MMI__
MAE_Ret _NetworkNetAccessModeWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif //__GPRS_MMI__
MAE_Ret _NetworkBandSelectionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _NetworkLineSelectionWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif /* __MMI_NETWORKAPP_PRIV_H__ */
