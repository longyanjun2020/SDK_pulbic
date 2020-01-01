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
* @file mmi_messagecenterapp.h
* @version
* @brief   MCA header file
*
*/

#ifndef __MMI_MESSAGECENTERAPP_H__
#define __MMI_MESSAGECENTERAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_messageeditorapp.h"
#include "mmi_messageviewerapp.h"
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
#include "mmi_launcher_mca.h"
#endif
#include "mmi_common_messagecenter_type.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/
#define MCA_EVT_NEXT_PREVIOUS_MSG				(CLSID_MCA << 16 | 1)

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/


typedef struct
{
	SMI_MsgID_t MsgId;
	SMI_MsgType_e MsgType;
	SMI_MsgLocation_e MsgStorage;
	SMI_MsgFlag MsgStatus;
	SMI_TimeStamp_t time;
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	SMI_SmsSimMsgBox_e SmsSimMsgBox;
#endif
#ifdef __MMI_SMS_SEARCH__
	SMS_MsgRecipAddr *pRecipient;
	MAE_WChar *pContactName;	
#endif
} McaMsgBoxItemData_t;

typedef struct
{
	u32 MsgIdx;
	u32 MsgTotal;
	McaMsgBoxItemData_t ItemData;
} McaFocusMsgInfo_t;

typedef struct
{
	boolean bChangeAbility;
	IBase *pRequester;      //MCA
	IDataModel *pDataModel; //Focus msg info (McaFocusMsgInfo_t *)
} McaChangeMessage_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** McaAppNew
* @brief        New function for create BMI Applet
*
* @param[in]    nClsId                 BMI class id
* @param[in]    ppObj               The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail
*
*/
MAE_Ret McaAppNew
(
	MAE_ClsId id,
	void **ppObj
);

void McaAppPreNew(void);

/** McaStartApFree
* @brief
*
* @param[in]		pIssuer
* @param[in]		Param
*
* @retval       void
*
*/
void McaStartApFree
(
	IBase *pIssuer,
	u32 Param
);

/** _McaMoveToNextOrPreviousMsg
* @brief
*
* @param[in]		pApplet
* @param[in]		bMoveToPrevious
* @param[in]		pReqMdl
*
* @retval       void
*
*/
void _McaMoveToNextOrPreviousMsg
(
	IApplet *pApplet,
	boolean bMoveToPrevious,
	IDataModel *pReqMdl
);

#endif /* __MMI_MESSAGECENTERAPP_H__ */
