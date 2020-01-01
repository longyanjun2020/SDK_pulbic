////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
* @file    mmi_vampiregame_priv.h
* @version
* @brief   VampireGame applet private header file
*
*/

#ifndef __MMI_VAMPIREGAME_PRIV_H__
#define __MMI_VAMPIREGAME_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_srv_audio.h"
#include "mmi_log.h"
#include "mmi_layout.h"
#include "mmi_srv_cfg.h"
#include "mmi_common_cfg.h"

#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"
#include "mgl_Scene_Environment.h"
#include "mmi_pgl_headers.h"
#include "mmi_srv_audioenv.h"

#include "VampireGame_resource.h"
#include "mmi_vampiregame_actors.h"

#include "rs_layout_id.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MAX_VAMPIRE_LEVEL    16
#define VAMPIRE_SCENE_SWITCH_STEP    20
#define MMI_LEVEL_VAMPIREGAME 	    MMI_LEVEL_23

#if defined(__LCM_QVGA_240_320_MMI__)
#define SIZE_SCALE_RATIO 0.675f
#define WIDTH_SCALE_RATIO 0.6666f
#define HEIGHT_SCALE_RATIO 0.75f
#endif

#if defined(__LCM_WQVGA_240_400_MMI__)
#define SIZE_SCALE_RATIO 0.78f
#define WIDTH_SCALE_RATIO 0.8333f
#define HEIGHT_SCALE_RATIO 0.75f
#endif

#if defined(__LCM_HVGA_320_480_MMI__)
#define SIZE_SCALE_RATIO 1.0f
#define WIDTH_SCALE_RATIO 1.0f
#define HEIGHT_SCALE_RATIO 1.0f
#endif

#define VAMPIREGAME_UPDATE_PERIOD       5
#define VAMPIREGAME_ENGINE_FPS          15
#define VAMPIREGAME_ENGINE_ITERATION    10
#define VAMPIREGAME_BAT_NUM             2
#define VAMPIREGAME_CLOUD_NUM           2
/*=============================================================*/
// Enumeration definition
/*=============================================================*/

enum
{
    eVAMPIRE_SCENE_MAIN = 0,
    eVAMPIRE_SCENE_LEVEL,
    eVAMPIRE_SCENE_GAME,
    eVAMPIRE_SCENE_END,
    eVAMPIRE_SCENE_MAX,
};
typedef pgl_u16 eVampireSceneType;

enum
{
    eVAMPIRE_BUTTOM_HOME,
    eVAMPIRE_BUTTOM_LEVEL,
    eVAMPIRE_BUTTOM_RESTART,
    eVAMPIRE_BUTTOM_SOUND,
    eVAMPIRE_BUTTOM_PREVIOUS,
    eVAMPIRE_BUTTOM_NEXT,
    eVAMPIRE_BUTTOM_LEVELS,
    eVAMPIRE_BUTTOM_MAX
};
typedef mgl_u16 eVAMPIRE_BUTTOM_TYPE;


/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pBgImgWdg;
}VampireGameWdgList;

typedef struct VampireGameWndData_t_
{
    VampireGameWdgList tWdgList;
} VampireGameWndData_t;

typedef struct
{
#ifndef C_MODEL
    APPLET_BASE_ELEMENTS;
    IWidget *pBgImgWdg;
    AudioEnvSrvVolLevel_e eCurVolume;
#endif
    EngineHandleID  engineID;
	SceneHandleID   sceneId[eVAMPIRE_SCENE_MAX];
	pgl_u8  u8CurLevID;
	pgl_u8  u8PassedLevID;                                                //Should come from .cfg....
    pgl_u32 u32lastBGtype;
    pgl_float   fTS_x, fTS_y;
	hActor actorLevel[MAX_VAMPIRE_LEVEL];
	//pgl_boolean   sg_Vampire_LevisPass[MAX_VAMPIRE_LEVEL];

	hActorCosHandler bWinhandle;// = PGL_COSHANDLER_NULL;
	hGuiActor 	actorOption[eVAMPIRE_BUTTOM_MAX];
    hGuiActor 	actorBat[VAMPIREGAME_BAT_NUM];
    hGuiActor 	actorCloud[VAMPIREGAME_CLOUD_NUM];
	pgl_boolean bPass;

	hTexRes texResID[VAMPIRE_MAX_TEXTURE_NUM];// = {0};
	boolean bSuspendMode;
    boolean bDraw;
    boolean bSound;
} VampireGameAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret VampireGameConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret VampireGameDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameTouchCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean VampireGameGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);
boolean VampireGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

#endif /* __MMI_VAMPIREGAME_PRIV_H__ */
