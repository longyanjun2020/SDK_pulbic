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
* @file    mmi_fishfurygame_priv.h
* @version
* @brief   FishFuryGame applet private header file
*
*/

#ifndef __MMI_FISHFURYGAME_PRIV_H__
#define __MMI_FISHFURYGAME_PRIV_H__

/*=============================================================*/
// Platform definition
/*=============================================================*/
#ifdef C_MODEL
    #define FISHFURYGAME_ON_CMODEL
#else
    #define FISHFURYGAME_ON_MAE_PLATFORM
#endif

/*=============================================================*/
// Include files
/*=============================================================*/

#ifdef FISHFURYGAME_ON_MAE_PLATFORM
#include "mmi_baseapplet.h"
#include "mmi_srv_audio.h"
#include "mmi_audioenvsrv.h"
#include "mmi_srv_audioenv.h"
#include "mmi_log.h"
#include "mmi_layout.h"
#include "FishFuryGame_resource.h"
#else
//Commnet to avoid abuse api check
//#include "WinMain.h"
#endif

#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"
#include "mgl_Scene_Environment.h"
#include "mmi_pgl_headers.h"
#include "mmi_fishfurygame_actors.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#ifdef FISHFURYGAME_ON_CMODEL
#define RS_MAIN_LCD_WIDTH                                               (MAIN_LCD_WIDTH)
#define RS_MAIN_LCD_HEIGHT                                              (MAIN_LCD_HEIGHT)
#define MMI_LEVEL_23                                                    (23)                                                       
typedef void                                                            IApplet;
#endif

#define MGL_PICKING	0

#define MMI_LEVEL_FISHFURYGAME MMI_LEVEL_23
#define MAX_BIRD_NUM 5
#define MAX_DEMOCASE 1
#define FRAND   (float)rand()/(float)RAND_MAX
#define GRABABLE_MASK_BIT (1<<31)
#define NOT_GRABABLE_MASK (~GRABABLE_MASK_BIT)
#define SCENE_3DUI_ZOFFSET   -(mgl_float)(MGL_LCM_HEIGHT>>1) / (tan((22.5f) * DEGTORAD))

#define ANIMATION_TIME		10


#define IMG_NUM_0			IMG_SCORE_0
#define IMG_NUM_1			IMG_SCORE_1
#define IMG_NUM_2			IMG_SCORE_2
#define IMG_NUM_3			IMG_SCORE_3
#define IMG_NUM_4			IMG_SCORE_4
#define IMG_NUM_5			IMG_SCORE_5
#define IMG_NUM_6			IMG_SCORE_6
#define IMG_NUM_7			IMG_SCORE_7
#define IMG_NUM_8			IMG_SCORE_8
#define IMG_NUM_9			IMG_SCORE_9

//
#define IMG_START_BG		IMG_FISHFURY_START
#define IMG_MENU_BG			IMG_OPTIONMENU_BG
#define IMG_PLAY_BG			IMG_PLAYGAME_BG
#define IMG_PAUSE_BG		IMG_PAUSE_BG

#define IMG_PLAY			IMG_BUTTON_PLAY
#define IMG_PLAY_PRESS		IMG_BUTTON_PLAY_PRESS
#define IMG_SOUND			IMG_SOUND
#define IMG_SOUND_OFF		IMG_SOUND_CLOSE

#define IMG_BUTTON_AGAIN	IMG_BUTTON_AGAIN
#define IMG_BUTTON_MENU		IMG_BUTTON_MENU
#define IMG_BUTTON_NEXT		IMG_BUTTON_NEXT
#define IMG_BUTTON_PAUSE	IMG_BUTTON_PAUSE

#define IMG_MENU_OP_LOCK	IMG_OPTIONMENU_LOCK
#define IMG_MENU_OP_1		IMG_OPTIONMENU_POINTS_1
#define IMG_MENU_OP_2		IMG_OPTIONMENU_POINTS_2
#define IMG_MENU_OP_3		IMG_OPTIONMENU_POINTS_3
#define IMG_MENU_OP_4		IMG_OPTIONMENU_POINTS_4
#define IMG_MENU_OP_5		IMG_OPTIONMENU_POINTS_5
#define IMG_MENU_OP_6		IMG_OPTIONMENU_POINTS_6
#define IMG_MENU_OP_7		IMG_OPTIONMENU_POINTS_7
#define IMG_MENU_OP_8		IMG_OPTIONMENU_POINTS_8
#define IMG_MENU_OP_9		IMG_OPTIONMENU_POINTS_9
#define IMG_MENU_OP_10		IMG_OPTIONMENU_POINTS_10

#define sg_FPS	20
//static mgl_s32 sg_FPS=20;

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

/*=============================================================*/
// Enumeration definition
/*=============================================================*/
enum
{
    eFishFury_SCENE_MAIN = 0,
    eFishFury_SCENE_HELP,
    eFishFury_SCENE_MENU,
    eFishFury_SCENE_PLAY,
    eFishFury_SCENE_GAMEOVER,
    eFishFury_SCENE_MAX,
} ;
typedef pgl_u16 eFishFurySceneType;

typedef enum
{
#ifdef __G3D_MMI__
	SCENE_BG=0,
	SCENE_START,
#else
	SCENE_START=0,
#endif
	SCENE_MENU,
	SCENE_PLAY,
	SCENE_PICK,
	SCENE_LEVEL,
	SCENE_PAUSE,
	SCENE_MAX,
}SceneState_e;

typedef enum
{
	FISHFURY_GAME_START=0,
	FISHFURY_GAME_MENU,
	FISHFURY_GAME_PLAY,
	FISHFURY_GAME_PAUSE,
	FISHFURY_PAUSE_IDLE,
	FISHFURY_PAUSE_NEXT,
	FISHFURY_PAUSE_AGAIN,
	FISHFURY_PAUSE_MENU,
}GameState_e;

enum
{
	FISHFURY_MENU = 0,
	FISHFURY_CLICK,
	FISHFURY_FIRE,
	FISHFURY_PIG,
	FISHFURY_BREAKS,
};
typedef u8 eFISHFURY_SOUND;

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    IWidget *pBgImgWdg;
}FishFuryGameWdgList;

typedef struct FishFuryGameWndData_t_
{
    FishFuryGameWdgList tWdgList;
} FishFuryGameWndData_t;


typedef struct
{
#ifdef FISHFURYGAME_ON_MAE_PLATFORM
	APPLET_BASE_ELEMENTS;
    AudioEnvSrvVolLevel_e eCurVolume;
#endif
	boolean	bTouched;

	u16     u16SceneHandleId;
	u32     nodeID[eFishFury_SCENE_MAX];
	s32		nTS_CurrentX;
	s32		nTS_CurrentY;

    float   fCameraMoveX;
    float	fTouchMoveX;

    boolean bPickBird;
	boolean bSuspendMode;
	boolean bDraw;
	boolean	bStart;
	boolean	bPause;
	boolean bMenu;
	boolean bMusic;
	boolean	bReset;
	boolean bExit;
	boolean	bFireBird;

	u8		level;
	u32		score;
	u32		highscore[10];
	u32		GameState;
	u32		PauseState;

	s32		scale;
	s32		birdInitX;
	s32		birdInitY;
	u8		curBirdidx;

    mgl_u8 cfg_level;
    u32 cfg_data[11];
    EngineHandleID  engineID;
    SceneHandleID sg_FishFury_scene[eFishFury_SCENE_MAX];
    hTexRes sg_FishFuryTexResID[MAX_TEXTURE_NUM];
    boolean sg_fishfury_sound;
    hActor hhelp;
    int help_index;

    hGuiActor hGuiPauseBG;
    hGuiActor hGuiPausePlay;
    hGuiActor hGuiPauseSound;
    hGuiActor hGuiPauseMenu;
    hGuiActor hGuiPauseReplay;

    IWidget *pBgImgWdg;
    Vertex2D lastBGShift;
    Vertex2D BGShift;
    Vertex2D lastBGSize;
    Vertex2D BGSize;
}FishFuryGameAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef FISHFURYGAME_ON_MAE_PLATFORM
MAE_Ret FishFuryGameConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret FishFuryGameDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameTouchCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);
boolean FishFuryGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
void FishFuryGamePlayAudioOnce(void *pUser, eFISHFURY_SOUND audiotype);
SceneHandleID FishFuryGameGetSceneID(IApplet *pApplet, eFishFurySceneType sceneID);

#endif /* __MMI_FISHFURYGAME_PRIV_H__ */

