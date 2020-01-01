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
* @file    mmi_voicemailapp_priv.h
* @version
* @brief   VoiceMail applet private header file
*
*/

#ifndef __MMI_VOICEMAILAPP_PRIV_H__
#define __MMI_VOICEMAILAPP_PRIV_H__

/*=============================================================*/
// Include files (New Add)
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_voicemailapp.h"
#include "mmi_simsrv.h"
#include "mmi_mmsrv.h"
#include "mmi_cphssrv.h"
#include "mmi_common_vtm.h"
#include "VoiceMailApp_resource.h"
#include "mmi_voicemailapp_rs.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define VOICE_MAIL_NUMBER_PLUS_CHAR 0x2B
#define VOICE_MAIL_REQUIRED_NUMBER_LENGTH	(3)

/*=============================================================*/
// Data type definition (New Add)
/*=============================================================*/

typedef struct
{
	PopUpInputWdgList_t tWdgList;
	PopUpInputData_t tInputData;
	boolean bDialVoicemail;
} VoiceMailSetNumberWndData_t;

typedef struct
{
	SimSelectionWdgList_t tWdgList;
	SimSelectionData_t tSelectData;
} VoiceMailSelectSimWndData_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	VMA_SELECT_SIM_e eSimMode;
    VMA_SELECT_SIM_e eStartSimMode;
	VMA_START_TYPE_e eStartType;
	MMI_MMSRV_Line_Service_e eLineStatus;
	MMI_CPHS_MailBoxNumber_t tMailBoxNum;
	u32 nNumberLen;
	boolean bIsPreviousEmpty;
} VoiceMailAppData_t;

/*=============================================================*/
// Global function definition (New Add)
/*=============================================================*/
MAE_Ret VoiceMailConstructor
(
	IApplet *pApplet,
	u32 nEvt,
	u32 param1,
	u32 param2
);

boolean VoiceMailStartCB
(
	IApplet *pApplet,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

boolean VoiceMailSuspendCB
(
	IApplet *pApplet,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

boolean VoiceMailResumeCB
(
	IApplet *pApplet,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

boolean VoiceMailKeyPressCB
(
	IApplet *pApplet,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

boolean VoiceMailEmbededApCloseCB
(
	IApplet *pApplet,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

void VoiceMailHandleSimStatusChangeCb
(
	void *pUsrData,
	COMMON_SIM_CARD_STATUS_e eSIMCardStatus
);


void VoiceMailSetNumberInputTextChangeCb
(
	void *pApplet,
	void *pUsrData,
	WidgetEvtCode_t nEvtCode,
	TextInfo *pTextInfo,
	IWidget *pWidget
);

void VoiceMailSelectSimMenuSoftKeyCb
(
	void *pApplet,
	void *pUsrData,
	WidgetEvtCode_t nEvtCode,
	HistoryInfo_t *pHistoryInfo,
	IWidget *pWidget
);


void VoiceMailSIMReadyIndCB
(
    void *pUsrData,
    u8 nActiveSIM
);

MAE_Ret VoiceMailDialogTimeOutCloseAppCb
(
	void *pData,
	u32 nEvt,
	u32 nParam1,
	u32 nParam2
);

MAE_Ret VoiceMailDialogTimeOutSaveSuccessCb
(
    void *pData,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

void VoiceMailSetCphsMailBoxNumberCB
(
	void *pUsrData,
	MMI_CPHSSRV_Result_e eResult,
	u32 nSimID
);

void VoiceMailLineReadyIndCB
(
    void *pUsrData,
    MMI_MMSRV_Line_CFU_e eLine,
    MAE_DualMode_t eDualMode
);
/*=============================================================*/
// Local function definition (New Add)
/*=============================================================*/

MAE_Ret _VoiceMailCreateSetNumberWnd
(
	void *pCusHandle,
	void* pWndData,
	u32 nWndInitParam
);

MAE_Ret _VoiceMailShowSetNumberWnd
(
    void *pCusHandle,
    void* pWndData,
    u32 nWndInitParam
);


MAE_Ret _VoiceMailCreateSimSelectWnd
(
	void *pCusHandle,
    void* pWndData,
	u32 nWndInitParam
);


MAE_Ret _VoiceMailSetNumberWndHdl
(
	void				*pCusHandle,
	const WindowMsg_t	*pWndMsg,
	void				*pWndData,
	u32 				nWndInitParam
);

MAE_Ret _VoiceMailSelectSimWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);


boolean _VoiceMailHandleSetNumberKeyPress
(
	IApplet *pApplet,
	MAE_WndId nWndId,
	u32 nParam
);



void _VoiceMailStartActive
(
    IApplet *pApplet
);



void _VoiceMailGetNumberAndSave
(
    IApplet *pApplet,
    VMA_SELECT_SIM_e eSimMode
);

void _VoiceMailGetInputedNumberAndSave
(
    IApplet *pApplet,
    VMA_SELECT_SIM_e eSimMode
);

MAE_Ret _VoiceMailGetInputedNumberFromWnd
(
	IApplet *pApplet,
	MAE_WndId nWndId,
	MMI_CPHS_MailBoxNumber_t *pMailBoxNum
);

void _VoiceMailSaveVoiceMailNumberToSim
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode,
	MMI_MMSRV_Line_Service_e eLineStatus,
	MMI_CPHS_MailBoxNumber_t *pMailBoxNum
);

MAE_Ret _VoiceMailSaveVoiceMailNumberToHandset
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode,
	MMI_MMSRV_Line_Service_e eLineStatus,
	MMI_CPHS_MailBoxNumber_t *pMailBoxNum
);



void _VoiceMailGetNumberAndDial
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode
);

MAE_Ret _VoiceMailGetLineStatus
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode,
	MMI_MMSRV_Line_Service_e *pLineStatus
);

MAE_Ret _VoiceMailGetNumber
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode,
	MMI_MMSRV_Line_Service_e eLineStatus,
	MMI_CPHS_MailBoxNumber_t *pMailBoxNum
);

void _VoiceMailDialNumber
(
	IApplet *pApplet,
	VMA_SELECT_SIM_e eSimMode,
	MMI_CPHS_MailBoxNumber_t *pMailBoxNum
);

#endif /* __MMI_VOICEMAILAPP_PRIV_H__ */
