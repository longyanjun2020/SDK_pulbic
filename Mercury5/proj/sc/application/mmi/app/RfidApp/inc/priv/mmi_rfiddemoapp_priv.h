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
* @file    mmi_bmiapp_priv.h
* @version
* @brief   BMI applet private header file
*
*/
#ifndef __MMI_RFIDDEMOAPP_PRIV_H__
#define __MMI_RFIDDEMOAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"

#include "mmi_rs_macro_struct.h"
#include "mmi_rfiddemoapp.rs"
#include "mmi_rfiddemoapp_id.h"

#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_log.h"

#include "mae_shell.h"
#include "mmi_mae_rfidreader.h"
#include "mmi_srv_header.h"

#include "mmi_rfid_util.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef __SUPPORT_JSR257__
#define MF_KEY_LEN                (6)
#endif	//__SUPPORT_JSR257__

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	MAIN_ITEM_ISO15693,
	MAIN_ITEM_ISO15693_MSR3200,
	MAIN_ITEM_ISO15693_MSR3260,

#ifdef	__USE_MSR3110__
	MAIN_ITEM_ISO14443A,
	MAIN_ITEM_ISO14443B,
#endif	//__USE_MSR3110__

#if defined(__USE_MSR3330__) || defined(__USE_MSR3320__)
	MAIN_ITEM_C1G2,
#endif	//defined(__USE_MSR3330__) || defined(__USE_MSR3320__)

#ifdef __SUPPORT_SIM_SWITCH__
	MAIN_ITEM_SIM_SWITCH,
#endif //__SUPPORT_SIM_SWITCH__

#ifdef __BARCODE__
	MAIN_ITEM_BARCODE,
#endif	//__BARCODE__

#ifdef __GPS_MMI__
	MAIN_ITEM_GPS,
#endif	//__GPS_MMI__

#ifdef __SUPPORT_JSR257__
	MAIN_ITEM_JSR257_MENU,
#endif	//__SUPPORT_JSR257__

	MAIN_ITEM_FIRMWARE_VERSION,
	MAIN_ITEM_UPDATE_FIRMWARE,

	MAIN_ITEM_TOTAL
} RfidDemoMainListItem_e;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;
	IWidget *pTextWidget4;
	IWidget *pTextWidget5;
	IWidget *pTextWidget6;

} RfidDemoISO15693WdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget;
} RfidDemoUpdateFirmwareWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;
	IWidget *pTextWidget4;
	IWidget *pTextWidget5;
	IWidget *pTextWidget6;
} RfidDemoGetFWVerWdgList_t;

#if defined(__USE_MSR3330__) || defined(__USE_MSR3320__)
typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;	//EPC
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;	//Write
	IWidget *pTextWidget4;
	IWidget *pTextWidget5;	//Read
	IWidget *pTextWidget6;
} RfidDemoC1G2WdgList_t;
#endif	//defined(__USE_MSR3330__) || defined(__USE_MSR3320__)

#ifdef	__USE_MSR3110__
typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;    //UID
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;    //SAK
	IWidget *pTextWidget4;
	IWidget *pTextWidget5;    //Status

} RfidDemoISO14443AWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;    //Tag Type
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;    //Tag ID
	IWidget *pTextWidget4;
	IWidget *pTextWidget5;    //Status

} RfidDemoISO14443BWdgList_t;
#endif	//__USE_MSR3110__

#ifdef __SUPPORT_SIM_SWITCH__
typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;
	IWidget *pTextWidget2;
	IWidget *pTextWidget3;
} RfidDemoSimSwitchWdgList_t;
#endif //__SUPPORT_SIM_SWITCH__

#ifdef __SUPPORT_JSR257__

typedef enum
{
	NDEF_LISTENER,
	NDEF_READ,
	NDEF_WRITE,
	TARGET_LISTENER,

	ISO14443A_MF,

	JSR257_ITEM_TOTAL
} RfidDemoJSR257ListItem_e;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pTextWidget1;
	IWidget *pTextWidget2;    //AUTH
	IWidget *pTextWidget3;    //Write
	IWidget *pTextWidget4;    //Read
	IWidget *pTextWidget5;    //Increment
	IWidget *pTextWidget6;    //Decrement
	IWidget *pTextWidget7;    //Restore
	IWidget *pTextWidget8;    //Transfer
	IWidget *pTextWidget9;    //Status

} RfidDemoISO14443AMFWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelTest;
	IWidget *pTextTest;
} RfidDemoNDEFListenerWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelTest;
	IWidget *pTextTest;
} RfidDemoNDEFReadWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelTest;
	IWidget *pTextTest;
} RfidDemoTargetListenerWdgList_t;

typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelTest;
	IWidget *pTextTest;
} RfidDemoNDEFWriteWdgList_t;
#endif	//__SUPPORT_JSR257__

#ifdef __BARCODE__
typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelWidget;
	IWidget *pTextWidget;
} RfidDemoBarcodeWdgList_t;
#endif	//__BARCODE__

#ifdef __GPS_MMI__
typedef struct
{
	IWidget *pTitleWidget;
	IWidget *pLabelWidget;
	IWidget *pTextWidget;
} RfidDemoGpsWdgList_t;
#endif	//__GPS_MMI__


/**
 * Application structure
 */
typedef struct
{
	APPLET_BASE_ELEMENTS;

	//reader
	IRFIDREADER			*pIRfidReader;
	esl_RFID_TagType_e	eTagType;
	esl_RFID_ErrCode_e	eRfidErrCode;
	esl_RFID_Info_t		tRfidInfo;
	esl_RFID_TagInfo_t	RfidTagInfo[TAG_MAX_ID_SIZE];
	esl_RFID_ReadParam_t	tRfidReadParam;
	esl_RFID_WriteParam_t	tRfidWriteParam;
	esl_RFID_ModuleInfo_t	tRfidModuleInfo;
	esl_RFID_UpgradeParam_t tRfidUpgradeParam;
	esl_RFID_driver_Req_t	tRfidReq;

	boolean	bTagResult;
	u8	TagBlock[TAG_MAX_BLOCK_SIZE];
	u8	TagEPC[UHF_EPC_LEN];
	u8	TagTID[UHF_TID_LEN];
	u8	TagUID[HF_UID_LEN];
	u8  TagUIDLength;
	MAE_WChar	TagDispStr[TAG_MAX_BLOCK_SIZE+1];

	u32	nMainListIndex;
	IWidget	*pProgressWdg;
	BKLInfo	tBKLightDefaultInfo;
	RfidDemoUpdateFirmwareWdgList_t  tUpdateFirmwareWdgList;
	RfidDemoGetFWVerWdgList_t	tGetFWVerWdgList;
	RfidDemoISO15693WdgList_t	tISO15693WdgList;

#ifdef __SUPPORT_SIM_SWITCH__
	RfidDemoSimSwitchWdgList_t	tSimSwitchWdgList;
	esl_SIM_Switch_e 		eSimSwitchType;
	esl_RFID_SIMSwitch_t	tRfidSimSwitch; //Sim Switch Parameter
#endif //__SUPPORT_SIM_SWITCH__

#ifdef	__USE_MSR3110__
	RfidDemoISO14443AWdgList_t	tISO14443AWdgList;
	RfidDemoISO14443BWdgList_t	tISO14443BWdgList;
#endif	//__USE_MSR3110__

#if defined(__USE_MSR3330__) || defined(__USE_MSR3320__)
	RfidDemoC1G2WdgList_t		tC1G2WdgList;
#endif	//defined(__USE_MSR3330__) || defined(__USE_MSR3320__)

#ifdef __BARCODE__
	RfidDemoBarcodeWdgList_t	tBarcodeWdgList;
	u8	Barcode[BARCODE_MAX_BYTE+1];
	u8	BarcodeLen;
#endif	//__BARCODE__

#ifdef __SUPPORT_JSR257__
	u32	nJSR257ListIndex;

	RfidDemoISO14443AMFWdgList_t  tISO14443AMFWdgList;

	RfidDemoNDEFListenerWdgList_t	tNDEFListenerWdgList;
	RfidDemoNDEFReadWdgList_t	tNDEFReadWdgList;
	RfidDemoNDEFWriteWdgList_t	tNDEFWriteWdgList;
	RfidDemoTargetListenerWdgList_t tTargetListenerWdgList;

	esl_RFID_TagProperties_t	tTagProperty;
	esl_RFID_ReadNDEF_t 		tNDEF;
	void	*connHandle;

	esl_RFID_MFCommand_t		tMFCmdParam;
#endif //__SUPPORT_JSR257__

#ifdef __GPS_MMI__
	RfidDemoGpsWdgList_t	tGpsWdgList;
	GPSSrvData_t			tGpsSrvData;
	boolean 				bIsGpsPowerOn;
	u32						nGpsSearchCount;
#endif	//__GPS_MMI__

} RfidDemoAppData_t;

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
MAE_Ret RfidUpdateFirmwareProgressDialogHdl(void * pUser,MAEEvent_t nEvtCode,u32 param1,u32 param2);

#ifdef __SUPPORT_SIM_SWITCH__
MAE_Ret RfidDemoSimSwitchWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif //__SUPPORT_SIM_SWITCH__

#ifdef __SUPPORT_JSR257__
static void _RfidDemoReaderMFAuth(RfidDemoAppData_t *pThis);
#endif	//__SUPPORT_JSR257__

#ifdef __GPS_MMI__
static void	_RfidDemoGpsTimerTO(void *pData);
static void	_RfidDemoCloseGps(RfidDemoAppData_t *pThis);
#endif	//__GPS_MMI__

#endif /* __MMI_RFIDDEMOAPP_PRIV_H__ */

