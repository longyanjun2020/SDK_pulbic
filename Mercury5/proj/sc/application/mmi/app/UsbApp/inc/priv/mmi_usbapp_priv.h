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
* @file    mmi_usbapp_priv.h
* @version
* @brief   USB applet private header file
*
*/

#ifndef __MMI_USBAPP_PRIV_H__
#define __MMI_USBAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_usbapp.h"
#include "mmi_common_vtm.h"
#include "mmi_common_inttbl.h"
#include "mmi_common_dialog_id.h"

#include "mmi_srv_atsync.h"
#include "mmi_srv_usb.h"
#include "mmi_srv_accessory.h"
#include "mmi_srv_btobex.h"
#include "mmi_usbapp_id.h"
#include "usbapp_resource.h"

#if defined(__DUAL_CAMERA_MMI__)
#include "mmi_common_cfg.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define USBAPP_DEFAULT_FAIL_DIALOG_TEXT_ID	TXT_PML_N_FAIL

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    APPLET_BASE_ELEMENTS;

	MMI_USB_DEVICE_E	eUsbDevice;

    u32					nSelectedID;
	u32					nFailTextID;
	boolean				bWaitingDialogShown;
	boolean				bLockScreenDialogShown;

	// Accessory service
	boolean				bIsCardInserted;
	boolean				bIsClosing;
	boolean				bIsStarted;
	boolean				bUsbRequested;
	boolean				bIsCableInserted;
    boolean             bDisconnectedWhenSuspend;
    boolean             bIsLaunchedByResumeFileMgr;
#ifdef __MSYNC_TOOL__
    // ATSync service
	boolean             bIsATSyncInitialized;
#endif
#ifdef __DUAL_CAMERA_MMI__
	DualCameraType_e 	eCamera_Id;
#endif
} UsbAppData_t;

typedef struct
{
    IWidget *pMenuWdg;
}UsbWndWdgList_t;

typedef struct
{
    UsbWndWdgList_t tWdgList;
} ConnectMenuWndData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret UsbAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean UsbAppStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean UsbAppStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean UsbAppSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppTimerCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppShowWaitingDialogTimerCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppShowNoItemInformDialogTimerCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppShowFailedConfirmDialogCheckCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppShowLockScreenConfirmDialogCheckCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UsbAppShowInterruptOthersConfirmDialogCheckCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#ifdef __BLUETOOTH_OBEX_MMI__
MAE_Ret UsbAppShowStopBtTransmittingConfirmDialogCheckCb(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

void UsbAppRecvFileCb(void *pApplet, BTSRV_TRANS_RESULT_e eResult);
void UsbAppSendFileCb(void *pApplet, BTSRV_TRANS_RESULT_e eResult); 
#endif
void UsbAppATSyncSrvStartStatusCb(void *pThis, ATSYNC_START_RESULT_e eResult);
void UsbAppATSyncSrvStopIndCb(void *pThis);
void UsbAppUsbSrvOpenReqCb(void *pThis, boolean bResult);
void UsbAppUsbSrvStopIndCb(void *pThis);
void UsbAppUsbSrvBackToIdleIndCb(void *pThis);
void UsbAppUsbSrvCloseReqCb(void *pThis, boolean bResult);
void UsbAppAccessoryPlugStatusCb(void *pData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
void UsbAppMenuSoftKeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

//Window manager related function
MAE_Ret UsbAppWndConnectMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);


#endif /* __MMI_USBAPP_PRIV_H__ */
