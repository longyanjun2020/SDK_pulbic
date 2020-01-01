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
* @file    mmi_voicemailapp.h
* @version
* @brief   VoiceMail header file
*
*/
#ifndef __MMI_VOICEMAILAPP_H__
#define __MMI_VOICEMAILAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum{
    VMA_E_START_TYPE_START=0x00,
    VMA_E_START_SETTING=VMA_E_START_TYPE_START,
    VMA_E_START_SET_NUMBER_WITH_SELECT_SIM,
    VMA_E_START_DIAL_NUMBER,
    VMA_E_START_DIAL_NUMBER_WITH_SELECT_SIM,
    VMA_E_START_TYPE_TOTAL
};
typedef u8 VMA_START_TYPE_e;

enum
{
    VMA_E_MASTER_SIM=0x00,
    VMA_E_SLAVE_SIM=0x01,
    VMA_E_SIM_UNKNOW
};
typedef u8 VMA_SELECT_SIM_e;

typedef struct
{
    VMA_START_TYPE_e StartType;
    VMA_SELECT_SIM_e SelectSIM;
}VMA_Start_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** VoiceMailAppNew
* @brief        New function for create VoiceMail Applet
*
* @param[in]    nClsId	VoiceMail class id
* @param[in]    ppObj	The pointer of pointer of Applet
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail
*
*/
MAE_Ret VoiceMailAppNew
(
    MAE_ClsId   nClsId,
    void        **ppObj
);

void VoiceMailPreNew(void);
void VoiceMailAppStartAPFree(IBase *pUser, u32 nParam);
#endif /* __MMI_VOICEMAILAPP_H__ */
