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
* @file    mmi_checkdiskapp_priv.h
* @version
* @brief   CheckDisk applet private header file
*
*/
#ifndef __MMI_CHECKDISKAPP_PRIV_H__
#define __MMI_CHECKDISKAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_clock.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_checkdiskapp_id.h"
#include "CheckDiskApp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef u32 (*CheckDiskSM_Fxp)(void  *pThis, u32 nEvtID, u32 nParm1, u32 nParm2);

typedef enum
{
    CHECKDISKAPP_MODE_UNKNOWN = 0,
    CHECKDISKAPP_MODE_CHECK_DISK,
    CHECKDISKAPP_MODE_FORMAT,
} CheckDiskMode_e;

typedef enum
{
    CHECKDISKAPP_EVT_UNKNOWN = 0,
    CHECKDISKAPP_EVT_INIT,
    CHECKDISKAPP_CHECK_EVT_NOTIFY_STOP_AP,
    CHECKDISKAPP_EVT_SUSPEND_FILEMGR,
    CHECKDISKAPP_EVT_RESUME_FILEMGR,
    CHECKDISKAPP_CHECK_EVT_CHECKING_DISK,
    CHECKDISKAPP_CHECK_EVT_QUERY_STOP_CHECKING,
    CHECKDISKAPP_CHECK_EVT_CHECK_DISK_FAILED,
    CHECKDISKAPP_CHECK_EVT_CHECK_DISK_FINISH,
    CHECKDISKAPP_FORMAT_EVT_NOTIFY_STOP_AP,
    CHECKDISKAPP_FORMAT_EVT_NOTIFY_CLEAR_ALL_DATA,
    CHECKDISKAPP_FORMAT_EVT_FORMATING,
    CHECKDISKAPP_FORMAT_EVT_FORMAT_FINISH,
    CHECKDISKAPP_FORMAT_EVT_FORMAT_FAILED,
    CHECKDISKAPP_EVT_CLOSE,
    CHECKDISKAPP_EVT_KEY,
} CheckDiskEvtID_e;

typedef enum
{
    CHECKDISKAPP_TYPE_UNKNOWN = 0,
    CHECKDISKAPP_TYPE_ALL,
    CHECKDISKAPP_TYPE_PHONE,
    CHECKDISKAPP_TYPE_SD1,
    CHECKDISKAPP_TYPE_SD2,
} CheckDiskType_e;

typedef enum
{
    CHECKDISKAPP_CONFRIM_DLG_NONE = 0,
    CHECKDISKAPP_CONFRIM_DLG_STOP_CHECKING_DISK,
    CHECKDISKAPP_CONFRIM_DLG_STORAGE_ERROR,
    CHECKDISKAPP_CONFRIM_DLG_FORMAT_WILL_CLEAR_ALL_DATA,
    CHECKDISKAPP_CONFRIM_DLG_CHECK_DISK_WILL_STOP_SOME_AP,
    CHECKDISKAPP_CONFRIM_DLG_FORMAT_STORAGE_WILL_STOP_SOME_AP,
    CHECKDISKAPP_INFO_DLG_DONE,
    CHECKDISKAPP_INFO_DLG_FORMAT_FAILED,
} CheckDiskAppDlg_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    CheckDiskSM_Fxp *pSM;
    u32 nState;
    CheckDiskMode_e eCheckDiskMode;
    CheckDiskType_e eCheckDiskType;
    u32 nCurrentCheckDiskMode;
    CheckDiskType_e eCurrentCheckDiskType;
    boolean bDoFormat;
    boolean bFileMgrSuspend;
    boolean bFileMgrResuming;
    boolean bIsSuspend;
    boolean bCheckDiskPause;
    boolean bFormatPause;
    u8 nSuspendReason;
    boolean bCheckingDisk;
    boolean bFormatingDisk;
    u32 nEvt;
    CheckDiskAppDlg_e eDlg;
    boolean bNotifyStopApp;
    boolean bPlugAbort;
    boolean bStopAP;
    boolean bIsStop;
    boolean bMakeDefaultDir;
    boolean bBadFormatPause;
    boolean bBadCheckDiskPause;
	boolean bWaitDefaultFolder;

    FileMgrHandleID_t nCheckDiskHandle;
    FileMgrHandleID_t nFormatHandle;
    FileMgrHandleID_t nSuspendHandle;

} CheckDiskAppData_t;

typedef enum
{
    CHECKDISK_SM__IDLE = 0,
    CHECKDISK_SM__SUSPENDING,
    CHECKDISK_SM__RESUMING,
    CHECKDISK_SM__PROCESSING,
    CHECKDISK_SM__PROCESS_SUSPEND,
    CHECKDISK_SM__ABORTING,
    CHECKDISK_SM__OPENDIALOG,
    CHECKDISK_SM__CLOSEDIALOG,
    CHECKDISK_SM__END,
} CheckDiskAppStateInfo_e;

typedef enum
{
    CHECKDISKAPP_CHECKDISK_PAUSE = 0,
    CHECKDISKAPP_CHECKDISK_RESUME,
} CheckDiskAppCheckDiskAction_e;

typedef enum
{
    CHECKDISKAPP_FORMAT_PAUSE = 0,
    CHECKDISKAPP_FORMAT_RESUME,
} CheckDiskAppFormatAction_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret CheckDiskAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CheckDiskAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CheckDiskAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CheckDiskAppStopCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CheckDiskAppResumeCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CheckDiskAppSuspendCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CheckDiskAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CheckDiskAppTextWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

MAE_Ret _CheckDiskAppCheckStopAPDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _CheckDiskAppCheckingDiskDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _CheckDiskAppStopCheckingDiskDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
void _CheckDiskCreateDialog(CheckDiskAppData_t *pThis);
MAE_Ret _CheckDiskAppFormatStopAPDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _CheckDiskAppFormatClearDataDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _CheckDiskAppDoneDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _CheckDiskAppQueryFormatStorageDialogCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret _CheckDiskAppSuspendFileMgr(CheckDiskAppData_t *pThis);
void _CheckDiskAppSuspendFileMgrCb(void *pUser, void *pInfo);
MAE_Ret _CheckDiskAppResumeFileMgr(CheckDiskAppData_t *pThis);
void _CheckDiskAppResumeFileMgrCb(void *pUser, void *pInfo);
MAE_Ret _CheckDiskAppCheckDisk(CheckDiskAppData_t *pThis);
void _CheckDiskAppCheckDiskCb(void *pUser, void *pInfo);
MAE_Ret _CheckDiskAppCheckDiskAction(CheckDiskAppData_t *pThis, CheckDiskAppCheckDiskAction_e eAction);
MAE_Ret _CheckDiskAppFormat(CheckDiskAppData_t *pThis);
void _CheckDiskAppFormatCb(void *pUser, void *pInfo);
MAE_Ret _CheckDiskAppFormatAction(CheckDiskAppData_t *pThis, CheckDiskAppFormatAction_e eAction);

void _CheckDiskAppToIdle(CheckDiskAppData_t *pThis);
void _CheckDiskAppShowCheckingDiskDialog(CheckDiskAppData_t *pThis);
void _CheckDiskAppShowStorageErrorDialog(CheckDiskAppData_t *pThis);
void _CheckDiskAppShowStopCheckingDisk(CheckDiskAppData_t *pThis);
void _CheckDiskAppMakeDefaultDir(CheckDiskAppData_t *pThis);
void _CheckDiskAppCloseDialog(CheckDiskAppData_t *pThis);
void _CheckDiskAppAccessoryPlugStatusCB(void *pThisData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
boolean _CheckDiskAppCheckMakeDefaultDir(CheckDiskAppData_t *pThis);
void _CheckDiskAppDelayDialogCB(void *pUser);

//The following is for test only
void _CheckDiskCheckDiskOKCb(void *pUser);
void _CheckDiskCheckDiskFailedCb(void *pUser);
void _CheckDiskFormatOKCb(void *pUser);
void _CheckDiskFormatFailedCb(void *pUser);

#endif /* __MMI_CHECKDISKAPP_PRIV_H__ */

