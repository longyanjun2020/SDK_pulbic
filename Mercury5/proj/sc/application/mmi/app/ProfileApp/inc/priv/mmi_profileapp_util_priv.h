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
* @file mmi_profileapp_util.h
*
* @version $Id:$
*/
#ifndef __MMI_UTIL_PROFILEAPP_PRIV_H__
#define __MMI_UTIL_PROFILEAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_profileapp.h"
#include "mmi_profileapp_priv.h"

#include "mmi_profilesrv.h"
#include "mmi_srv_audio.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define PROFILEAPP_DIALOG_TIMER 2000

#define PROFILEAPP_VOLUME_RETRY_TIMER (200)
#define PROFILEAPP_VOLUME_RETRY_COUNT (10)

#define PROFILEAPP_VOLUME_DELAY_STOP_AUDIO_TIME  1500

/*=============================================================*/
// Data type definition
/*=============================================================*/

enum
{
    PROFILEAPP_General,
    PROFILEAPP_Meeting,
    PROFILEAPP_Outdoor,
    PROFILEAPP_Silent,
    PROFILEAPP_Personal,
};

typedef struct
{
    MenuItemID_e    eMenuItemID;
    ProfileID_e     eProfileID;
} ProfileAppMainListTab_t;

typedef struct
{
    u32         u32TextLabelID;
    ProfileID_e eProfileID;
} ProfileAppTextIDTab_t;

typedef struct
{
    IWidget     **ppIMenuWdg;
    IMenuModel  **ppIMenuModel;
    IModel      **ppIViewModel;
    MAE_WChar   *pWTitleTextBuffer;
    u32         u32ResID;
    boolean     bHaveMenuWidget;
    u16         u16ViewID;
} ProfileAppViewData_t;

/*=============================================================*/
// Local function definition
/*=============================================================*/

MAE_Ret _ProfileAppTextIdFromProfileId(ProfileID_e eProfileID, u32 *u32TextID);
MAE_Ret _ProfileAppGetProfileMiidFromProfileId(ProfileID_e eProfileID, MenuItemID_e *eMIID);
MAE_Ret _ProfileAppGetProfileIdFromMiid(MenuItemID_e eMIID, ProfileID_e *eProfileID);

void _ProfileAppStartPlayVolMelody(void *pData);
void _ProfileAppStopPlayVolMelody(ProfileAppData_t *pThis, ProfileAppVolume_t *pData);

void _ProfileAppRestoreVolume(ProfileAppData_t *pThis);
void _ProfileAppSetVolume(ProfileAppData_t *pThis, u32 u32VolumeIndex);
void _ProfileAppPlayVolMelodyCb(void *pApplet, MediaSrvErrCode_e eErrorCode);
void _ProfileAppStopPlayVolMelodyCb(void *pApplet, MediaSrvErrCode_e eErrorCode);
void _ProfileAppVolMelodyPlayStatusCb(void *pApplet, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);

MAE_Ret _ProfileAppRestoreRadioListData(ProfileAppData_t *pThis, IWidget *pIMenuWdg, u8 u8SelectItemValue);
MAE_Ret _ProfileAppSaveRadioListData(ProfileAppData_t *pThis, u32 eEditMenuItemID, u8 u8SaveItemValue);
#ifdef __POWER_SAVING_PROFILE_MMI__
boolean _ProfileAppShowDialogIfNotAllowed(ProfileAppData_t *pThis, MenuItemId_e eSettingMenuID);
#endif

#endif//__MMI_UTIL_PROFILEAPP_PRIV_H__
