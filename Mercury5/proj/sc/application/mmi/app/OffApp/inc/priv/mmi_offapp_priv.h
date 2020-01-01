////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
* @file mmi_offapp_priv.h
* Class Id: CLSID_OFFAPP
*/
#ifndef __MMI_OFFAPP_PRIV_H__
#define __MMI_OFFAPP_PRIV_H__

/*-------------------------------------------------------------------------*/
#include <stdlib.h>
#include "mmi_common_inttbl.h"
#include "mmi_common_dialog.h"
#include "mmi_common_vtm.h"
#include "abl_common.h"
#include "mmi_srv_header.h"
#include "mmi_secapp.h"
#include "mmi_baseapplet.h"

#include "mmi_offapp.h"
#include "mmi_offapp_view.h"
#include "mmi_offapp_id.h"
#include "offapp_resource.h"

#define OFFAPP_POWER_OFF_TIMER              15000
#define OFFAPP_POWER_OFF_MELODY_TIMER       8000
#define OFFAPP_LOW_BATTERY_DIALOG_TIMER     10000	//for dialog tiemr
#define OFFAPP_ANIMATION_FRAME_INTERVAL     100
#define OFFAPP_DONT_CARE_TIMER              10000

#define OFFAPP_FACTORY_POWER_ON_ALARM_TIMER 3  // Set an alarm to trigger the handset to power on when master restore is executed in factory mode.(MSZ requirement)

/**
 * Internal Events
 */
#define OFFEVT_EXIT				            (CLSID_OFFAPP << 16 | 1)
#define OFFEVT_MENUBACK						(CLSID_OFFAPP << 16 | 2)
#define OFFEVT_MENUSELECT					(CLSID_OFFAPP << 16 | 3)
#define OFFEVT_DIALOGEND					(CLSID_OFFAPP << 16 | 4)
#define OFFEVT_TIMEREXPIRED					(CLSID_OFFAPP << 16 | 5)
#define OFFEVT_MUSICEND			            (CLSID_OFFAPP << 16 | 6)
#define OFFEVT_AUTOOFFTIMEOUT               (CLSID_OFFAPP << 16 | 9)

#define SMEVT_ACTIVATECANCEL                (CLSID_SWITCHMODE << 16 | 1)
#define SMEVT_ACTIVATESELECT                (CLSID_SWITCHMODE << 16 | 2)
#define SMEVT_DIALOGEND                     (CLSID_SWITCHMODE << 16 | 3)
#define SMEVT_TIMEREXPIRED                  (CLSID_SWITCHMODE << 16 | 4)

typedef enum
{
  OFFCHECK_NOSTART           = -2,      /* offapp has be constructed, but suspended and not be started*/
  OFFCHECK_START             = -1,      /* offapp is started*/
  OFFCHECK_BEGIN             = 0,       /* begin power off procedure */
  OFFCHECK_DEACTIVATE_SIMREQ = 1 << 0,  /* have response from deactivate SIM card */
  OFFCHECK_ANIM_END          = 1 << 1,  /* power off animation is finished */
  OFFCHECK_BTOFFCNF          = 1 << 2,  /* BT trun off confirm */
  OFFCHECK_END               = (OFFCHECK_DEACTIVATE_SIMREQ|OFFCHECK_ANIM_END|OFFCHECK_BTOFFCNF) /* can jump to Stop mode if both deactivate SIM and power off animation are done */
}OffCheck_e;

typedef enum
{
    SM_NONE = 0,
    SM_ACTIVATE_MASTER,
    SM_DEACTIVATE_MASTER,
    SM_ACTIVATE_SLAVE,
    SM_DEACTIVATE_SLAVE
}SmChangeMode_e;
/*-------------------------------------------------------------------------*/

#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
typedef struct
{
    IWidget *pOsdWdg;
} VideoWndWdgList_t;

typedef struct
{
    VideoWndWdgList_t tWdgList;
    MAE_WChar   *stImageURL;
} PowerOffVideoWndData_t;

typedef enum
{
    OFF_VIDEO_STOP_CAUSE_NONE,
    OFF_VIDEO_STOP_CAUSE_HOTPLUG,
    OFF_VIDEO_STOP_CAUSE_MAX,
}OffVideoStopCause_e;
#endif // __USER_DEFINE_POWERONOFF_VIDEO__

typedef struct
{
	APPLET_BASE_ELEMENTS;
    PowerOffType_e 	ePowerOffType; //sotre power off cause.
    s32             nOffStatus;    //check power off procedure status to decide to jump to Stop mode or not.
    boolean			bShutdown;
    boolean     bMusicEnd;
    boolean     bDefaultAnim;
    boolean     bShowWarning;
#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
    OffVideoStopCause_e eVideoStop;
#endif
}MMI_OFFAPP;
/*window id*/

typedef struct
{
	APPLET_BASE_ELEMENTS;
    SIMSRV_SIM_ID_e	eSIMIDforSec;
    boolean			bMasChgEnd;	        //check if finish activate/deactivate operation for Master SIM.
    boolean			bSlvChgEnd;		    //check if finish activate/deactivate operation for Slave SIM.
    boolean			bDeactCnfm;         //wait deactivating confirm
    boolean			bChkScur;           //wait SIM Ready To Check Security;
    boolean			bSecAppProcessing;
#ifdef __ANTI_STEAL_MMI__
    boolean			bSecAppAntiSteal;
#endif
	u32 			nSIMErrorModulID;
    SmChangeMode_e  eNextAction;	    //next action for change mode.
    u8  currDualID; // porting from networkapp, for airplane mode
    boolean bIsWaitAirplaneOnOff; // porting from networkapp, for airplane mode
    boolean bCloseAppByAirplaneMode;
    boolean bSimToAirplane; // press airplane mode from sim
}MMI_SWITCHMODEAPP;

typedef struct
{
    IWidget *pIfnAbsCntr;
    IWidget *pIfnBgImage;
    IWidget *pIfnFade;
    IWidget *pIfnBtnImage;
    IWidget *pIfnBtn;
    IWidget *pIfnSlide;
}IfnWndData_t;

typedef struct
{
    IWidget     *pImg;
    IWidget     *pPropCntr;
	u32 	    nCurrentAnimImgID;
    MAE_WChar   *stImageURL;
    MAE_WChar   *stRingerURL;
    IImage      *pIPowerOffImage;
}AniWndData_t;

#ifdef __DUAL_LCD__
typedef struct
{
    IWidget     *pImg;
    IWidget     *pPropCntr;
    boolean     bMusicEnd;
	u32 	    nCurrentAnimIdx;
}AniSubWndData_t;
#endif // __DUAL_LCD__

typedef struct
{
    IWidget         *pSmMenu;
    u32             nMnuSelId;
    u32             nLastMnuSelId;
}SmWndData_t;

enum
{
    OFFWARNING_NONE,
    OFFWARNING_MMS,
    OFFWARNING_WAP,
    OFFWARNING_BT,
};
typedef u8 OffWarning_e;


void    _PowerOffProcedure(MMI_OFFAPP* pThis);
void    OnSmSimRsp   (void *pAp, u8 nActiveSIM );
void    OnSmSimErrRsp(void *pAp, u8 nActiveSIM );
void    OnSmActCnfrm (void *pAp, SIMSRV_RESULT_e nCnfResult, SIMSRV_SIM_ID_e nModulID );

void    OffSimShutdown(void* pAp);
void    OffForceShutdown(void* pAp);
void    OffPlayMelodyCb(void *pUserData, MediaSrvErrCode_e eErrorCode);
void    OffPlayStatusCb(void *pUserData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);

static boolean OffTimerExpired(IApplet* pAp, u32 ev, u32 p1, u32 p2);
boolean OffTimerAutoOff(IApplet* pAp, u32 ev, u32 p1, u32 p2);
static boolean OffEndDialog   (IApplet* pAp, u32 ev, u32 p1, u32 p2);
boolean OffMeShutdown  (IApplet *pAp, u32 ev, u32 p1, u32 p2);
MAE_Ret OffAnimWndAction(void* pThis, const WindowMsg_t *pMsg, void* pData, u32 dwInit);
#ifdef __DUAL_LCD__
MAE_Ret OffAnimSubWndAction(void* pThis, const WindowMsg_t *pMsg, void* pData, u32 dwInit);
#endif // __DUAL_LCD__
__DLM_OFFAPP_FREE__ void _OffAppLoadDLM(void);
__DLM_OFFAPP_FREE__ void _OffAppUnloadDLM(void);
/*-------------------------------------------------------------------------*/
#endif /* __MMI_OFFAPP_PRIV_H__ */
