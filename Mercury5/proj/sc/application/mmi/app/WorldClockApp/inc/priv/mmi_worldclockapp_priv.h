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
* @file mmi_worldclockapp_priv.h
*
* Class Id: CLSID_WORLDCLOCKAPP
*
* @version $Id$
*/
#ifndef __MMI_WORLDCLOCKAPP_PRIV_H__
#define __MMI_WORLDCLOCKAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_dialog.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_custom.h"
#include "mmi_common_vtm.h"

#include "mmi_worldclockapp_id.h"
#include "worldclockapp_resource.h"


#include "mmi_baseapplet.h"
#include "mmi_worldclockapp.h"
#include "mmi_launcher_common.h"
#include "mmi_worldclockapp_view.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/

#define WORLDCLOCK_CITY_TIME_STR_FMT L"%s %s"
#define WORLDCLOCK_SLIDE_TIME 2000

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    MAE_TimeZone_e  eTzId;          // Timezone id
    u16             xPos;           // X position relative to bg map image
    u16             yPos;           // Y position relative to bg map image
    u32             nTxtId;         // city name text id
} WorldClockAppCityData_t;

typedef struct
{
    MAE_TimeZone_e  eTzId;          // Timezone id
    u32             xPos;           // X position
    u32             yPos;           // Y position
    MAE_WChar       *pStrCityName;  // Pointer to city name
} WorldClockAppCityInfo_t;

typedef struct
{
    WorldClockAppMainViewWdgList_t tWdgList;
    WorldClockAppMode_e     nMode;              // World Clock or Pickup timezone
    MAE_TimeZone_Field_e    nPickupTz;          // First or second timezone to pickup
    u32                     nCityIdx;           // Current index of city vector model
    MAE_TimeZone_e          eCurTZ;             // Current timezone
} WorldClockAppMainView_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
} WorldClockAppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret WorldClockAppConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret WorldClockAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean WorldClockAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean WorldClockAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean WorldClockAppTouchScreenPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

/*=============================================================*/
// Local function definition
/*=============================================================*/

MAE_Ret _WorldClockAppWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _WorldClockAppWndConvertMain(void *pCusHandle, void *pWndData);

MAE_Ret _WorldClockAppWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#if defined(__3D_UI_IDLE_MULTIPAGE__)
MAE_Ret _WorldClockAppWndCreateList(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret _WorldClockAppWndListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

/* Listener */
static void _WorldClockAppClockCB(void *pUsrData);
static void _WorldClockAppBacklightOnOffCB(void *pUsrData, boolean bBackLightOn);

/* Utility function */
static MAE_Ret _WorldClockAppDisplayTimezoneInfo(WorldClockAppData_t *pThis, u32 nCityIdx);
static MAE_Ret _WorldClockAppPickupTimezone(WorldClockAppData_t *pThis, u32 nCityIdx);
static MAE_Ret _WorldClockAppTimezoneToCityIdx(WorldClockAppData_t *pThis, MAE_TimeZone_e eTimeoneId, u32 *pCityIdx);
static MAE_Ret _WorldClockAppGetCityInfo(WorldClockAppCityInfo_t *pInfo, u32 nCityIdx);

/* Internal function */
static void _WorldClockAppSwitchTimeZone(WorldClockAppData_t *pThis, u32 nEvt, u32 nParam1, u32 nParam2);

/* Timer callback */
static void _WorldClockAppSlideTimerCB(void *pUsrData);

/* Draw info dialog */
static MAE_Ret _WorldClockAppDrawInfoDialogCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
static void _WorldClockAppDrawInfoDialog(IBase *pObj, u32 Param);

/* Pick up time zone confirm dialog */
static MAE_Ret _WorldClockAppPickupTimeZoneConfirmDialogCB(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);

#endif /* __MMI_WORLDCLOCKAPP_PRIV_H__ */
